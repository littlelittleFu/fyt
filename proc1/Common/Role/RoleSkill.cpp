#include "stdafx.h"
#include "RoleSkill.h"

#include "Role.h"
#include "MapRoleMgr.h"
#include "Map.h"
#include "MapMgr.h"
#include "ITimeHelper.h"
#include "PlayerDoplganr.h"
#include "LuaGmMgr.h"

RoleSkill::RoleSkill(Role* master) : RoleAction(master)
{

}

RoleSkill::~RoleSkill()
{
    ClearTimeridmap();
}

bool RoleSkill::Init()
{
	return true;
}

void RoleSkill::Update(int32_t delta)
{
    bool needUpdate = false;

    for (auto &skillData : mSkillList) {

        if (skillData.InCD() || skillData.IsInFireTime()) {
            needUpdate = true;
            skillData.Update(delta);
        }

        if (skillData.FireTimeExpired()) {
            skillData.StopFireTimeCountDown();

            auto *self = GetMaster();
            if (self && self->IsPlayer()) {
                auto *player = static_cast<Player*>(self);
                player->SendSkillStatusNtfToGS(skillData.GetID(), false);
            }
        }
    }

    UpdateCastSkillPubCD(delta);

    if (!needUpdate && mCastSkillPubCDTime == 0) {

        ResetNeedUpdate(skill_need_update_flag);
    }

    UpdateTimeridmap();
}

int RoleSkill::AddSkill(uint16_t id, bool active, uint32_t proficiency, string cfg)
{
    auto *self = GetMaster();
    if (!self) return ERR_UNKNOW;

	auto skillTable = sSkillConfig.Get(id);
	if (nullptr == skillTable) {
		return ERR_SKILL_NOT_EXIST;
	}

    if (IsSkillExist(id)) return ERR_SKILL_ALREADY_EXIST;

    if (skillTable->SkillChainID != 0 &&
        IsSkillExistByChainID(skillTable->SkillChainID))
        return ERR_SKILL_EXIST_SAME_CHAIN;

    auto skillCfg = DecodeSkillCfg(std::move(cfg));

    mSkillList.push_back(SkillData());
    SkillData& data = mSkillList.back();
	data.Init(this, id, active, proficiency, skillTable, skillCfg);
    if (skillTable->SkillType == skill_type_status)
        data.SetFireTime(skillTable->SkillTypeParam);

    TRIGGER_EVENT(self, trigger_add_skill, self->GetGUIDAsString(), id);
    return ERR_OK;
}

void RoleSkill::RemoveSkill(uint16_t id)
{
    for (auto iter = mSkillList.begin(); iter != mSkillList.end(); ++iter) {
        if (iter->GetID() == id) {
            mSkillList.erase(iter);
            break;
        }
    }
}

bool RoleSkill::IsSkillExist(uint16_t id)
{
    return std::find_if(mSkillList.begin(), mSkillList.end(),
        [&](auto &skill) { return skill.GetID() == id; }) != mSkillList.end();
}

bool RoleSkill::IsSkillExistByChainID(uint32_t skillChainID)
{
    for (auto &skillData : mSkillList) {
        auto *cfg = skillData.GetSkillCfg();
        if (!cfg) continue;
        if (cfg->SkillChainID == skillChainID) return true;
    }
    return false;
}

uint16_t RoleSkill::GetSkillList(SKILL_INFO *pSkillInfo, uint16_t num)
{
    if (!pSkillInfo || num == 0) return 0;

    uint16_t i = 0;
    uint16_t count = std::min<uint16_t>((uint16_t)mSkillList.size(), num);
    for (auto iter = mSkillList.begin(); i < count && iter != mSkillList.end(); ++iter,++i) {
        pSkillInfo[i].id = iter->GetID();
        pSkillInfo[i].active = iter->IsActive();
        pSkillInfo[i].proficiency = iter->GetProficiency();
        string cfg = EncodeSkillCfg(iter->GetSkillCfgModifyMap());
        if (!cfg.empty()) strcpy_s(pSkillInfo[i].cfg, cfg);
    }

    return i;
}

std::vector<uint16_t> RoleSkill::GetSkillIDsByChainID(uint32_t skillChainID)
{
    std::vector<uint16_t> skillIDs;
    for (auto &skillData : mSkillList) {
        const auto *cfg = skillData.GetSkillCfg();
        if (!cfg) continue;
        if (cfg->SkillChainID == skillChainID)
            skillIDs.push_back(cfg->Id);
    }
    return skillIDs;
}

bool RoleSkill::SetSkillActive(uint16_t nSkillID, uint8_t active)
{
    auto pSkillData = GetSkillData(nSkillID);
    if (!pSkillData) return false;
    pSkillData->SetActive(active);
    return true;
}

void RoleSkill::ApplySkillOnTarget(uint16_t skillID, uint64_t targetGUID, uint16_t clientSN)
{
    auto *cfg = GetSkillCfg(skillID);
    if (!cfg) return;

    uint16_t x = 0;
    uint16_t y = 0;

    if (cfg->SpecialEffectType == skill_special_fly) {      // 弹道类取当前目标坐标

        auto *target = MapRoleMgr::GetInstance()->FindRole(targetGUID);
        if (target) {   // 为空继续往下走，后面会返回错误码
            x = target->GetRolePosX();
            y = target->GetRolePosY();
        }
    }

    ApplySkill(skillID, targetGUID, x, y, clientSN, 0);
}

void RoleSkill::ApplySkillOnGrid(uint16_t skillID, uint64_t targetGUID, uint16_t x, uint16_t y, uint16_t clientSN, uint8_t extraInfo)
{
    ApplySkill(skillID, targetGUID, x, y, clientSN, extraInfo);
}

void RoleSkill::ApplySkill(uint16_t skillID, uint64_t targetGUID, uint16_t x, uint16_t y, uint16_t clientSN, uint8_t extraInfo)
{
    SAFE_BEGIN;

    auto *cfg = GetSkillCfg(skillID);
    if (!cfg) return;

    auto *self = GetMaster();
    if (!self) return;

    if (cfg->SkillType != skill_type_direct) {

        bool checkCD = true;
        bool checkMP = true;

        if (cfg->SkillType == skill_type_status && (x != 0 || y != 0)) {    // 使用状态类技能
            checkCD = false;
            checkMP = false;
        }

        auto result = ConditionCheck(skillID, checkCD, checkMP);
        if (result != ERR_OK) {
            SendSpellAck(result, skillID, clientSN);
            return;
        }

        result = CheckDistance(skillID, x, y);
        if (result != ERR_OK) {
            SendSpellAck(result, skillID, clientSN);
            return;
        }
    }

    DoApplySkill(skillID, x, y, targetGUID, clientSN, extraInfo);

    SAFE_END;
}

uint16_t RoleSkill::BeforeApplySkill(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID)
{
    auto *cfg = GetSkillCfg(skillID);
    if (!cfg) return ERR_UNKNOW;

    if (cfg->Script.empty() || cfg->Script == "0") return ERR_OK;

    auto *self = GetMaster();
    if (!self) return ERR_UNKNOW;

    std::string func = cfg->Script + ".pre_apply";

    if (!CLuaEngineMgr()->IsLuaFuncExist(func)) return ERR_OK;

    bool result = false;
    LuaBindCallRet(result, func, self->GetGUIDAsString(), skillID, x, y, std::to_string(targetGUID));

    return result ? ERR_OK : ERR_SKILL_CANT_USE;
}

void RoleSkill::AfterApplySkill(uint16_t skillID, const AttackResults& res)
{
    auto *cfg = GetSkillCfg(skillID);
    if (!cfg) return;

    if (cfg->Script.empty() || cfg->Script == "0") return;

    auto *self = GetMaster();
    if (!self) return;

    std::string func = cfg->Script + ".post_apply";

    if (!CLuaEngineMgr()->IsLuaFuncExist(func)) return;

    auto table = NewLuaObj();
    int i = 1;
    for (auto iter = res.begin(); iter != res.end(); ++iter) 
    {
        table[i] = to_string(iter->targetGUID);
        ++i;
    }

    LuaBindCallVoid(func, self->GetGUIDAsString(), skillID, table);
}

void RoleSkill::DoApplySkill(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN, uint8_t extraInfo)
{
    SAFE_BEGIN;

    auto *self = GetMaster();
    if (!self) return;

    auto result = BeforeApplySkill(skillID, x, y, targetGUID);

    if (result != ERR_OK) {
        SendSpellAck(result, skillID, clientSN);
        return;
    }

    auto *cfg = GetSkillCfg(skillID);
    bool decreaseHPMP = true;
    bool startCD = true;
    bool addProficiency = true;

    if (self->IsPlayerDoplganr()) decreaseHPMP = false;

    if (cfg->SpecialEffectType == skill_special_trap_trigger ||
        cfg->SpecialEffectType == skill_special_trap_rt) {

        result = DoApplySkill_Trap(skillID, x, y, targetGUID, clientSN);
    }
    else if (cfg->SpecialEffectType == skill_special_repell) {

        if (cfg->SkillType == skill_type_cast)
            result = DoApplySkill_Repel(skillID, x, y, targetGUID, clientSN);
        else if (cfg->SkillType == skill_type_fixed)
            result = DoApplySkill_Collide(skillID, x, y, targetGUID, clientSN);
    }
    else if (cfg->SpecialEffectType == skill_special_fly) {

        result = DoApplySkill_Fly(skillID, x, y, targetGUID, clientSN);
    }
    else if (cfg->SpecialEffectType == skill_special_summon) {

        result = DoApplySkill_Summon(skillID, x, y, targetGUID, clientSN);
    }
    else if (cfg->SpecialEffectType == skill_special_doplganr) {

        result = DoApplySkill_Doplganr(skillID, x, y, targetGUID, clientSN);
    }
    else if (cfg->SkillType == skill_type_status) {

        if (!x && !y) {
            addProficiency = false;
        }
        else {
            decreaseHPMP = false;       // 状态类技能第一次点击时已扣除蓝量，走SpellTarget协议，x、y都为0
            startCD = false;            // 下一次普攻时使用该技能不扣蓝量，走SpellGrid协议，x、y不为0
        }

        result = DoApplySkill_Status(skillID, x, y, targetGUID, clientSN);
    }
    else if (cfg->SkillType == skill_type_direct) {

        result = DoApplySkill_Direct(skillID, x, y, targetGUID, clientSN);
    }
    else if (cfg->Name.find("刺杀剑术") != std::string::npos) {

        result = DoApplySkill_Stab(skillID, x, y, targetGUID, clientSN);
    }
    else {

        result = DoApplySkill_Normal(skillID, x, y, targetGUID, clientSN, extraInfo);
    }

    if (result != ERR_OK) {
        SendSpellAck(result, skillID, clientSN);
        return;
    }

    if (decreaseHPMP) DecreaseActorHPMP(skillID);

    if (startCD) StartCD(skillID);


    //公共cd   不应该只有类型为施法才有公共cd  
    //如果为非施法技能或者公共cd为0   那么是否可以一帧内释放多个技能
    //战士公共cd 暂时用攻速代替    法师公共cd  以施法速度代替
	//尝试一下
    if (cfg->SkillType == skill_type_cast)
    {
        StartCastSkillPubCD(self->GetRoleProp(role_casting_speed) * 0.9);
    }
    else
    {
        StartCastSkillPubCD(self->GetRoleProp(role_attack_speed) * 0.9);
    }


    if (addProficiency) {
        AddProficiency(skillID);
        TRIGGER_EVENT(self, trigger_after_apply_skill, self->GetGUIDAsString(), skillID, x, y, std::to_string(targetGUID));
    }

    AttackResults atkResults;
    result = GetSkillCastTargets(skillID, x, y, targetGUID, atkResults);
    if (result != ERR_OK) return;

    AfterApplySkill(skillID, atkResults);

    // 非伤害类技能不会改变角色信息
    if (!cfg->AttackRatio)return;


    for (auto& iter : atkResults)
    {
        AddFightInfoWhenAttack(iter.skillId, iter.targetGUID);
        AddFightInfoWhenBeAttacked(iter.skillId, iter.targetGUID, iter.actorGUID);
        AddHateValue(iter.skillId,iter.targetGUID);
        AddPetTarget(iter.targetGUID);
        AddBackStatus(iter.targetGUID);
    }

    SAFE_END;
}

uint16_t RoleSkill::DoApplySkill_Trap(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN)
{
    PositionList posList;

    auto result = GetSkillCastPositionList(skillID, x, y, posList);
    if (result != ERR_OK) return result;

    auto *cfg = GetSkillCfg(skillID);

    auto *actor = GetMaster();
    if (!actor) return ERR_UNKNOW;
    auto actorGUID = actor->GetGUID();

    auto *map = actor->GetCurMap();
    if (!map) return ERR_UNKNOW;

    SendSpellAck(ERR_OK, skillID, clientSN);

    auto delay = GetApplySkillDelayTime(skillID, x, y);
    auto expireTime = GetTrapSkillExpireTime(skillID);
    if (delay != 0)
    {
        AttackResults atkResults;
        actor->NotifyAroundPlayers_SpellNtf(atkResults, skillID, x, y);
        map->AddTrapEffect(skillID, x, y, cfg->MagicID, expireTime);

        auto callback = [=](const TimerData& param) mutable {
            auto itr = mTimeridmap.find(param.id);
            if (itr != mTimeridmap.end())
            {
                mTimeridmap.erase(itr);
            }
            mNeedTimerUpdate = true;
            auto* actor1 = MapRoleMgr::GetInstance()->FindRole(actorGUID);
            if (actor1 == nullptr) return;
            if (actor1 != actor || !actor->CheckAlive()) return;
            auto* map1 = actor->GetCurMap();
            if (map1 != map) return;
            if (!map->AddMonitorRegionForTrapSkill(skillID, expireTime, actorGUID, std::move(posList)))
                return;
            };

        auto Timerid = ITimeHelper::GetInstance()->AddTimer(delay, false, callback);
        //ITimeHelper::GetInstance()->AddStrData(Timerid, "name", "DoApplySkill_Trap");
        mTimeridmap[Timerid] = delay;
    }
    else
    {
        if (!map->AddMonitorRegionForTrapSkill(skillID, expireTime, actorGUID, std::move(posList)))
            return ERR_SKILL_NO_TARGET;

        AttackResults atkResults;
        actor->NotifyAroundPlayers_SpellNtf(atkResults, skillID, x, y);
        map->AddTrapEffect(skillID, x, y, cfg->MagicID, expireTime);
    }
    return ERR_OK;
}

uint16_t RoleSkill::DoApplySkill_Status(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN)
{
    Player *player = GetPlayer();
    if (!player) return ERR_UNKNOW;

    uint16_t result = ERR_OK;

    if (!x && !y) {

        StartFireTimeCountDown(skillID);
        player->SendSkillStatusNtfToGS(skillID, true);            // 通知客户端处于激活状态
        SendSpellAck(ERR_OK, skillID, clientSN);
    }
    else {

        auto *skillData = GetSkillData(skillID);
        if (!skillData) return ERR_UNKNOW;

        if (!skillData->IsInFireTime()) return ERR_SKILL_FIRE_EXPIRE;

        result = DoApplySkill_Normal(skillID, x, y, targetGUID, clientSN);
        StopFireTimeCountDown(skillID);
        player->SendSkillStatusNtfToGS(skillID, false);
    }

    return result;
}

uint16_t RoleSkill::DoApplySkill_Normal(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN, uint8_t extraInfo)
{
    auto *actor = GetMaster();
    if (!actor) return ERR_UNKNOW;

    AttackResults atkResults;

    auto result = GetSkillCastTargets(skillID, x, y, targetGUID, atkResults);
    if (result != ERR_OK) return result;

    SendSpellAck(ERR_OK, skillID, clientSN);

    actor->NotifyAroundPlayers_SpellNtf(atkResults, skillID, x, y, extraInfo);

    auto delay = GetApplySkillDelayTime(skillID, x, y);

    if (delay == 0) {
        for (auto &it : atkResults) {
            RoleSkill::CalculateHarmData(it);

            ApplyBuffOnTarget(skillID, it.targetGUID);
            if (it.type > 0 && it.decreaseHP > 0)
            {
                AddGrayBuff(it.targetGUID);
            }
        }

        OnSkillApplyResult(atkResults);
    }
    else {
        auto actorGUID = actor->GetGUID();

        auto callback = [=](const TimerData & param) mutable {
            auto itr = mTimeridmap.find(param.id);
            if (itr != mTimeridmap.end())
            {
                mTimeridmap.erase(itr);
            }
            mNeedTimerUpdate = true;
            auto *actor1 = MapRoleMgr::GetInstance()->FindRole(actorGUID);
            if (actor1 == nullptr) return;
            if (actor1 != actor || !actor->CheckAlive()) return;

            for (auto &it : atkResults) {
                RoleSkill::CalculateHarmData(it);
                ApplyBuffOnTarget(skillID, it.targetGUID);
                if (it.type > 0 && it.decreaseHP > 0)
                {
                    AddGrayBuff(it.targetGUID);
                }
            }

            OnSkillApplyResult(atkResults);
        };

        auto Timerid = ITimeHelper::GetInstance()->AddTimer(delay, false, callback);
        //ITimeHelper::GetInstance()->AddStrData(Timerid, "name", "DoApplySkill_Normal");
        mTimeridmap[Timerid] = delay;
    }

    return ERR_OK;
}

uint16_t RoleSkill::DoApplySkill_Collide(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN)
{
    auto *cfg = GetSkillCfg(skillID);
    auto *self = GetMaster();
    if (!self) return ERR_UNKNOW;

    auto dx = 0, dy = 0;
    auto dir = self->GetRoleDir();

    switch (dir) {
    case dir_up: dx = 0; dy = -1; break;
    case dir_right_up: dx = 1; dy = -1; break;
    case dir_right: dx = 1; dy = 0; break;
    case dir_right_down: dx = 1; dy = 1; break;
    case dir_down: dx = 0; dy = 1; break;
    case dir_left_down: dx = -1; dy = 1; break;
    case dir_left: dx = -1; dy = 0; break;
    case dir_left_up: dx = -1; dy = -1; break;
    default: return ERR_UNKNOW;
    }

    auto actorGUID = self->GetGUID();
    const auto &actorName = self->GetName();
    auto actorLevel = self->GetRoleProp(role_level);
    auto *map = self->GetCurMap();
    auto curMapGuid = map->GetGUID();

    if (cfg->SpecialEffectParam.size() < 2) return ERR_UNKNOW;

    auto &maxCastDist = cfg->RangeParam;
    auto &maxTargets = cfg->SpecialEffectParam[1];
    auto &beatGrid = cfg->SpecialEffectParam[0];

    auto CalledBeforeExit = [=](uint64_t targetGUID) {

        auto *target = MapRoleMgr::GetInstance()->FindRole(targetGUID);
        if (!target) return;

        AttackResult res;
        res.actorGUID = actorGUID;
        res.actorName = actorName;
        res.targetGUID = targetGUID;
        res.skillId = skillID;
        RoleSkill::CalculateHarmData(res);
        if (res.type > 0 && res.decreaseHP > 0)
        {
            AddGrayBuff(res.targetGUID);
        }
        target->AttackedByRole(res);
    };

    struct CollideContext {
        uint16_t x0                     = 0;
        uint16_t y0                     = 0;
        uint16_t gridMoved              = 0;
        uint16_t gridMovedWithTarget    = 0;
        std::vector<std::pair<uint64_t, uint32_t>> roles;
        uint16_t buffToApplyTargetIdx   = 0;
    };

    auto context = std::make_shared<CollideContext>();
    context->roles.emplace_back(actorGUID, 0);
    context->x0 = self->GetRolePosX();
    context->y0 = self->GetRolePosY();

    auto CanMove = [=]{

        if (context->gridMoved >= maxCastDist) return false;
        if (context->gridMovedWithTarget >= beatGrid) return false;

        auto *map = MapMgr::GetInstance()->FindMapByGUID(curMapGuid);
        if (!map) return false;

        while (true) {

            auto rolesNum = context->roles.size();
            auto targetsNum = rolesNum - 1;

            auto x = context->x0 + dx * rolesNum;
            auto y = context->y0 + dy * rolesNum;

            if (map->IsGridAvail(x, y)) return true;

            auto *target = map->GetRoleInPoint(x, y);
            if (!target) return false;                  // 有阻挡
            if (!target->CheckAlive())return true;
            if (self != target)
            {
                if (target->IsPlayer() || target->IsPet() || target->IsPlayerDoplganr())
                {
                    if (map->IsTypeRegion(target->GetRolePosX(), target->GetRolePosY(), region_safe))return true; //在安全区里面的目标不会触发效果
                }
            }

            if (context->gridMoved > 0) return false;   // 玩家与怪物之间有间隔，冲到怪物跟前停止

            if (!CanApplySkillOnTarget(skillID, target)) return false;

            auto targetLevel = target->GetRoleProp(role_level);

            if (cfg->LevelCompare == skill_level_compare_greater) {
                if (actorLevel <= targetLevel) return false;
            }
            else if (cfg->LevelCompare == skill_level_compare_ge) {
                if (actorLevel < targetLevel) return false;
            }

            if (targetsNum >= maxTargets) return false;     // 这行判断不要提前

            auto targetGUID = target->GetGUID();
            auto funcID = target->AddEventHandler_RoleExit([=]{ CalledBeforeExit(targetGUID); });
            context->roles.emplace_back(targetGUID, funcID);
        }
    };

    auto ApplyBuffToNewTargets = [=]{
        auto *actor = MapRoleMgr::GetInstance()->FindRole(actorGUID);
        if (!actor) return;

        auto actorDir = actor->GetRoleDir();
        auto targetDir = (actorDir + 4) % 8;    // 怪物朝向玩家

        auto &idx = context->buffToApplyTargetIdx;
        while (++idx < context->roles.size()) {
            auto targetGUID = context->roles[idx].first;
            ApplyBuffOnTarget(skillID, targetGUID);

            auto *target = MapRoleMgr::GetInstance()->FindRole(targetGUID);
            if (!target) continue;
            if (!target->CheckAlive())continue;
            auto *map = target->GetCurMap();
            if (!map) continue;
            if (self != target)
            {
                if (target->IsPlayer())
                {
                    if (map->IsTypeRegion(target->GetRolePosX(), target->GetRolePosY(), region_safe))continue; //在安全区里面的目标不会触发效果
                }
            }

            target->SetRoleDir(targetDir);
            target->SetRoleProp(role_has_repelled, 1);
            target->GetRoleAttr()->SendPropertyModyNtf();

            ProtoGS_TurnNtf ntf;
            ntf.guid = targetGUID;
            ntf.dir = targetDir;

            map->SendRoleDirChangeNtf(target, ntf);
        }
    };

    auto MoveRolesByOneGrid = [=]{
        int32_t cnt = context->roles.size();
        for (auto i = cnt - 1; i >= 0; --i) {

            auto x = context->x0 + (i + 1) * dx;
            auto y = context->y0 + (i + 1) * dy;

            auto targetGUID = context->roles[i].first;
            auto *target = MapRoleMgr::GetInstance()->FindRole(targetGUID);
            if (target) {
                if (!target->CheckAlive())continue;
                if (target->IsPlayer()) {
                    if (self != target)
                    {
                        if (target->IsPlayer())
                        {
                            auto map = target->GetCurMap();
                            if (map)
                            {
                                if (map->IsTypeRegion(target->GetRolePosX(), target->GetRolePosY(), region_safe))continue;
                            }
                        }
                    }
                    auto *player = static_cast<Player *>(target);
                    player->NotifyPlayer_StartMove(x, y);
                }
                target->SetRolePos(x, y);
                // 冲撞时去掉buff
                target->RemoveBuffWhenMove();
            }
            else {
                context->roles.erase(context->roles.begin() + i);
                context->buffToApplyTargetIdx -= 1;
                break;
            }
        }

        context->x0 += dx;
        context->y0 += dy;
        context->gridMoved += 1;
        if (context->roles.size() > 1) {
            context->gridMovedWithTarget += 1;
        }
    };

    auto DecreaseTargetsHP = [=]{
        for (auto i = 1; i < context->roles.size(); ++i) {
            auto targetGUID = context->roles[i].first;
            auto *target = MapRoleMgr::GetInstance()->FindRole(targetGUID);
            if (!target) continue;

            AttackResult res;
            res.actorGUID = actorGUID;
            res.actorName = actorName;
            res.targetGUID = targetGUID;
            res.skillId = skillID;
            RoleSkill::CalculateHarmData(res);
            if (res.type > 0 && res.decreaseHP > 0)
            {
                AddGrayBuff(res.targetGUID);
            }
            target->AttackedByRole(res);

            target->SetRoleProp(role_has_repelled, 0);
        }
    };

    auto RemoveTargetsCalledBeforeExitFunc = [=]{
        for (auto i = 1; i < context->roles.size(); ++i) {
            auto targetGUID = context->roles[i].first;
            auto *target = MapRoleMgr::GetInstance()->FindRole(targetGUID);
            if (!target) continue;
            target->RemoveEventHandler_RoleExit(context->roles[i].second);
        }
    };

    auto TimerCallback = [=](const TimerData &param){
        auto *actor = MapRoleMgr::GetInstance()->FindRole(actorGUID);
        if (actor == nullptr)
        {
            ITimeHelper::GetInstance()->RemoveTimer(param.id);
            return;
        }
        if (actor != self || !actor->CheckAlive()) {
            ITimeHelper::GetInstance()->RemoveTimer(param.id);
            auto itr = mTimeridmap.find(param.id);
            if (itr != mTimeridmap.end())
            {
                mTimeridmap.erase(itr);
            }
            mNeedTimerUpdate = true;
            DecreaseTargetsHP();
            RemoveTargetsCalledBeforeExitFunc();
            return;
        }

        if (CanMove()) {
            ApplyBuffToNewTargets();
            MoveRolesByOneGrid();
        }
        else {
            ITimeHelper::GetInstance()->RemoveTimer(param.id);
            auto itr = mTimeridmap.find(param.id);
            if (itr != mTimeridmap.end())
            {
                mTimeridmap.erase(itr);
            }
            mNeedTimerUpdate = true;
            DecreaseTargetsHP();
            RemoveTargetsCalledBeforeExitFunc();
            RemoveBuffFromTarget(skillID, actorGUID);
            actor->SetRoleProp(role_has_collide, 0);
            if (context->gridMoved < maxCastDist && context->gridMovedWithTarget < beatGrid) {      // 冲撞打断
                if (actor->IsPlayer()) {
                    auto *player = static_cast<Player *>(actor);
                    player->SendErrorAck(ERR_SKILL_REPEL_COLLIDE, "");
                }
            }
        }
    };

    auto Timerid = ITimeHelper::GetInstance()->AddTimer(200, true, TimerCallback);
    //ITimeHelper::GetInstance()->AddStrData(Timerid, "name", "DoApplySkill_Collide");
    mTimeridmap[Timerid] = 200;
    SendSpellAck(ERR_OK, skillID, clientSN);        // 先发ACK

    ApplyBuffOnTarget(skillID, actorGUID);
    self->SetRoleProp(role_has_collide, 1);
    self->GetRoleAttr()->SendPropertyModyNtf();     // 再发属性

    if (CanMove()) {
        ApplyBuffToNewTargets();
        MoveRolesByOneGrid();
    }

    return ERR_OK;
}

uint16_t RoleSkill::DoApplySkill_Repel(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN)
{
    auto *actor = GetMaster();
    if (!actor)return ERR_UNKNOW;
    auto *cfg = GetSkillCfg(skillID);

    AttackResults atkResults;
    auto result = GetSkillCastTargets(skillID, x, y, targetGUID, atkResults);

    SendSpellAck(ERR_OK, skillID, clientSN);
    actor->NotifyAroundPlayers_SpellNtf(atkResults, skillID, x, y);

    if (atkResults.empty()) return ERR_OK;

    auto x0 = actor->GetRolePosX();
    auto y0 = actor->GetRolePosY();
    auto actorGUID = actor->GetGUID();
    const auto &actorName = actor->GetName();
    auto actorLevel = actor->GetRoleProp(role_level);
    auto *map = actor->GetCurMap();
    auto mapGUID = map->GetGUID();

    auto CalledBeforeExit = [=](uint64_t targetGUID) {

        auto *target = MapRoleMgr::GetInstance()->FindRole(targetGUID);
        if (!target) return;

        AttackResult res;
        res.actorGUID = actorGUID;
        res.actorName = actorName;
        res.targetGUID = targetGUID;
        res.skillId = skillID;
        RoleSkill::CalculateHarmData(res);
        if (res.type > 0 && res.decreaseHP > 0)
        {
            AddGrayBuff(res.targetGUID);
        }
        target->AttackedByRole(res);
    };

    struct TargetInfo {
        uint64_t targetGUID = 0;
        uint32_t funcID     = 0;
        int16_t  dx         = 0;
        int16_t  dy         = 0;

        TargetInfo(uint64_t guid, uint32_t func, int16_t deltaX, int16_t deltaY) :
            targetGUID(guid), funcID(func), dx(deltaX), dy(deltaY) {}
    };

    struct RepelContext {
        uint16_t gridMoved      = 0;
        std::vector<TargetInfo> targetsInfo;
    };

    auto context = std::make_shared<RepelContext>();

    auto CanRepelTarget = [=](uint64_t targetGUID) {

        auto *target = MapRoleMgr::GetInstance()->FindRole(targetGUID);
        if (!target) return false;

        auto targetLevel = target->GetRoleProp(role_level);

        if (cfg->LevelCompare == skill_level_compare_greater) {
            if (actorLevel <= targetLevel) return false;
        }
        else if (cfg->LevelCompare == skill_level_compare_ge) {
            if (actorLevel < targetLevel) return false;
        }

        if (target->IsPlayer() || target->IsPet() || target->IsPlayerDoplganr())
        {
            if (target->IsInSafeRegion())return false;
        }

        return true;
    };

    for (auto &it : atkResults) {

        auto *target = MapRoleMgr::GetInstance()->FindRole(it.targetGUID);
        if (!target) continue;
        if (target == actor) continue;

        if (CanRepelTarget(it.targetGUID)) {

            ApplyBuffOnTarget(skillID, it.targetGUID);

            auto funcID = target->AddEventHandler_RoleExit([=]{ CalledBeforeExit(it.targetGUID); });
            auto dx = target->GetRolePosX() - x0;
            auto dy = target->GetRolePosY() - y0;
            context->targetsInfo.emplace_back(it.targetGUID, funcID, dx, dy);

            uint8_t targetDir = 0;

            if (dx == 0) {
                if (dy > 0) targetDir = dir_up;
                else if (dy < 0) targetDir = dir_down;
            }
            else if (dx > 0) {
                if (dy > 0) targetDir = dir_left_up;
                else if (dy == 0) targetDir = dir_left;
                else targetDir = dir_left_down;
            }
            else {
                if (dy > 0) targetDir = dir_right_up;
                else if (dy == 0) targetDir = dir_right;
                else targetDir = dir_right_down;
            }

            auto *map = target->GetCurMap();
            if (!map) continue;

            target->SetRoleDir(targetDir);
            target->SetRoleProp(role_has_repelled, 1);
        }
        else {
            RoleSkill::CalculateHarmData(it);
            if (it.type > 0 && it.decreaseHP > 0)
            {
                AddGrayBuff(it.targetGUID);
            }
            target->AttackedByRole(it);
        }
    }

    if (context->targetsInfo.empty()) return ERR_OK;

    auto MoveTargetsByOneGrid = [=]{

        auto *map = MapMgr::GetInstance()->FindMapByGUID(mapGUID);
        if (!map) return;

        for (auto iter = context->targetsInfo.crbegin(); iter != context->targetsInfo.crend();++ iter) {

            const auto& it = *iter;
            auto &targetGUID = it.targetGUID;
            auto *target = MapRoleMgr::GetInstance()->FindRole(targetGUID);
            if (!target) continue;

            auto x = target->GetRolePosX() + it.dx;
            auto y = target->GetRolePosY() + it.dy;

            if (!map->IsGridAvail(x, y)) continue;

            if (target->IsPlayer()) {
                auto *player = static_cast<Player *>(target);
                player->NotifyPlayer_StartMove(x, y);
            }
            target->SetRolePos(x, y);
            // 移动时解除buff
            target->RemoveBuffWhenMove();
        }
    };

    auto DecreaseTargetsHP = [=]{
        for (const auto &it : context->targetsInfo) {

            auto &targetGUID = it.targetGUID;
            auto *target = MapRoleMgr::GetInstance()->FindRole(targetGUID);
            if (!target) continue;

            AttackResult res;
            res.actorGUID = actorGUID;
            res.actorName = actorName;
            res.targetGUID = targetGUID;
            res.skillId = skillID;
            RoleSkill::CalculateHarmData(res);
            if (res.type > 0 && res.decreaseHP > 0)
            {
                AddGrayBuff(res.targetGUID);
            }
            target->AttackedByRole(res);

            target->SetRoleProp(role_has_repelled, 0);
        }
    };

    auto RemoveTargetsCalledBeforeExitFunc = [=]{
        for (const auto &it : context->targetsInfo) {
            auto *target = MapRoleMgr::GetInstance()->FindRole(it.targetGUID);
            if (!target) continue;
            target->RemoveEventHandler_RoleExit(it.funcID);
        }
    };

    auto beatGrid = cfg->SpecialEffectParam[0];

    auto TimerCallback = [=](const TimerData &param) {
        auto *actor1 = MapRoleMgr::GetInstance()->FindRole(actorGUID);
        mNeedTimerUpdate = true;
        if (actor1 == nullptr)
        {
            ITimeHelper::GetInstance()->RemoveTimer(param.id);
            return;
        }
        if (actor1 != actor || !actor->CheckAlive() || ++context->gridMoved >= beatGrid) {
            ITimeHelper::GetInstance()->RemoveTimer(param.id);
            auto itr = mTimeridmap.find(param.id);
            if (itr != mTimeridmap.end())
            {
                mTimeridmap.erase(itr);
            }
            DecreaseTargetsHP();
            RemoveTargetsCalledBeforeExitFunc();
        }
        else {
            MoveTargetsByOneGrid();
        }
    };

    auto Timerid = ITimeHelper::GetInstance()->AddTimer(200, true, TimerCallback);
    //ITimeHelper::GetInstance()->AddStrData(Timerid, "name", "DoApplySkill_Repel");
    mTimeridmap[Timerid] = 200;
    MoveTargetsByOneGrid();

    return ERR_OK;
}

uint16_t RoleSkill::DoApplySkill_Fly(uint16_t skillID, uint16_t x1, uint16_t y1, uint64_t targetGUID, uint16_t clientSN)
{
    auto *cfg = GetSkillCfg(skillID);
    if (!cfg) return ERR_UNKNOW;

    auto *target = MapRoleMgr::GetInstance()->FindRole(targetGUID);
    if (!target) return ERR_SKILL_NO_TARGET;

    auto role = GetMaster();
    if (!role)return ERR_UNKNOW;

    auto x0 = role->GetRolePosX();
    auto y0 = role->GetRolePosY();

    auto* map = role->GetCurMap();

    if (!map) return ERR_UNKNOW;

    // 玩家释放的话 返回技能释放ack
    SendSpellAck(ERR_OK, skillID, clientSN);

    bool checkBlock = true;
    if (cfg->SpecialEffectParam.size() >= 3 && cfg->SpecialEffectParam[2] != 0) {
        checkBlock = false;
    }

    if (checkBlock) {
        auto pt = map->GetMForbidPoint(x0, y0, x1, y1);
        if (pt.first != 0 || pt.second != 0) {          // 有魔法阻挡
            role->NotifyAroundPlayers_SpellNtf(0, skillID, pt.first, pt.second);
            return ERR_OK;
        }
    }

    role->NotifyAroundPlayers_SpellNtf(targetGUID, skillID, x1, y1);

    auto actorGUID = role->GetGUID();

    auto callback = [=](const TimerData & data) {
        auto itr = mTimeridmap.find(data.id);
        if (itr!= mTimeridmap.end())
        {
            mTimeridmap.erase(itr);
        }
        mNeedTimerUpdate = true;
        auto *actor = MapRoleMgr::GetInstance()->FindRole(actorGUID);
        if (actor == nullptr) return;
        if (actor != role || !actor->CheckAlive()) return;

        auto *target = MapRoleMgr::GetInstance()->FindRole(targetGUID);
        if (!CanApplySkillOnTarget(skillID, target)) return;

        auto *cfg = GetSkillCfg(skillID);
        if (!cfg) return;

        if (!cfg->SpecialEffectParam.empty()) {                     // 有误差参数
            auto devDist = target->DistanceFromPos(x1, y1);
            if (devDist > cfg->SpecialEffectParam[0]) return;       // 大于误差范围
        }

        AttackResult atkResult;
        atkResult.actorGUID = actorGUID;
        atkResult.actorName = actor->GetName();
        atkResult.targetGUID = targetGUID;
        atkResult.skillId = skillID;

        RoleSkill::CalculateHarmData(atkResult);
        if (atkResult.type > 0 && atkResult.decreaseHP > 0)
        {
            AddGrayBuff(atkResult.targetGUID);
        }
        ApplyBuffOnTarget(skillID, targetGUID);
        OnSkillApplyResult(atkResult);
    };

    auto delayTime = GetApplySkillDelayTime(skillID, x1, y1);
    auto Timerid = ITimeHelper::GetInstance()->AddTimer(delayTime, false, callback);
    //ITimeHelper::GetInstance()->AddStrData(Timerid, "name", "DoApplySkill_Fly");
    mTimeridmap[Timerid] = delayTime;
    return ERR_OK;
}

uint16_t RoleSkill::DoApplySkill_Stab(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN)
{
    auto *self = GetMaster();
    if (!self) return ERR_UNKNOW;

    auto x0 = self->GetRolePosX();
    auto y0 = self->GetRolePosY();

    auto *map = self->GetCurMap();
    if (!map) return ERR_UNKNOW;

    Role *firstRole = nullptr;
    Role *secondRole = nullptr;

    auto dir = self->GetRoleDir();

    switch (dir) {

    case dir_up:
        firstRole = map->GetRoleInPoint(x0, y0 - 1);
        secondRole = map->GetRoleInPoint(x0, y0 - 2);
        break;

    case dir_right_up:
        firstRole = map->GetRoleInPoint(x0 + 1, y0 - 1);
        secondRole = map->GetRoleInPoint(x0 + 2, y0 - 2);
        break;

    case dir_right:
        firstRole = map->GetRoleInPoint(x0 + 1, y0);
        secondRole = map->GetRoleInPoint(x0 + 2, y0);
        break;

    case dir_right_down:
        firstRole = map->GetRoleInPoint(x0 + 1, y0 + 1);
        secondRole = map->GetRoleInPoint(x0 + 2, y0 + 2);
        break;

    case dir_down:
        firstRole = map->GetRoleInPoint(x0, y0 + 1);
        secondRole = map->GetRoleInPoint(x0, y0 + 2);
        break;

    case dir_left_down:
        firstRole = map->GetRoleInPoint(x0 - 1, y0 + 1);
        secondRole = map->GetRoleInPoint(x0 - 2, y0 + 2);
        break;

    case dir_left:
        firstRole = map->GetRoleInPoint(x0 - 1, y0);
        secondRole = map->GetRoleInPoint(x0 - 2, y0);
        break;

    case dir_left_up:
        firstRole = map->GetRoleInPoint(x0 - 1, y0 - 1);
        secondRole = map->GetRoleInPoint(x0 - 2, y0 - 2);
        break;

    default:
        return ERR_UNKNOW;
    }

    SendSpellAck(ERR_OK, skillID, clientSN);

    auto delay = GetApplySkillDelayTime(skillID, x, y);

    auto HurtRole = [&](Role *target, uint16_t skillID) {

        AttackResult atkResult;
        atkResult.actorGUID = self->GetGUID();
        atkResult.actorName = self->GetName();
        atkResult.targetGUID = target->GetGUID();
        atkResult.skillId = skillID;

        if (delay == 0) {
            RoleSkill::CalculateHarmData(atkResult);
            if (atkResult.type > 0 && atkResult.decreaseHP > 0)
            {
                AddGrayBuff(atkResult.targetGUID);
            }
            ApplyBuffOnTarget(skillID, atkResult.targetGUID);
            OnSkillApplyResult(atkResult);
        }
        else {
            auto callback = [=](const TimerData & data) mutable {
                auto itr = mTimeridmap.find(data.id);
                if (itr != mTimeridmap.end())
                {
                    mTimeridmap.erase(itr);
                }
                mNeedTimerUpdate = true;
                auto *actor = MapRoleMgr::GetInstance()->FindRole(atkResult.actorGUID);
                if (actor == nullptr) return;
                if (actor != self || !actor->CheckAlive()) return;

                RoleSkill::CalculateHarmData(atkResult);
                if (atkResult.type > 0 && atkResult.decreaseHP > 0)
                {
                    AddGrayBuff(atkResult.targetGUID);
                }
                ApplyBuffOnTarget(skillID, atkResult.targetGUID);
                OnSkillApplyResult(atkResult);
            };

            auto Timerid = ITimeHelper::GetInstance()->AddTimer(delay, false, callback);
            //ITimeHelper::GetInstance()->AddStrData(Timerid, "name", "DoApplySkill_Stab");
            mTimeridmap[Timerid] = delay;
        }
    };

    self->NotifyAroundPlayers_SpellNtf(targetGUID, skillID, x, y);

    if (CanApplySkillOnTarget(skillID, firstRole)) {                // 使用普攻
        HurtRole(firstRole, sGlobalConfig.GetData()->CommonAttackSkillID);
    }

    if (CanApplySkillOnTarget(skillID, secondRole)) {               // 使用刺杀
        HurtRole(secondRole, skillID);
    }

    return ERR_OK;
}

uint16_t RoleSkill::DoApplySkill_Summon(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN)
{
    auto *skillCfg = GetSkillCfg(skillID);
    if (!skillCfg) return ERR_UNKNOW;

    auto *self = GetPlayer();
    if (!self) return ERR_UNKNOW;
    auto curRoleLevel = self->GetRoleProp(role_level);

    const auto &SummonParams = skillCfg->SummonParams;
    auto it = std::find_if(SummonParams.rbegin(), SummonParams.rend(), [&](auto &param){
        return param.RoleLevel <= curRoleLevel;
    });
    if (it == SummonParams.rend()) return ERR_NOMONSTER;

    const auto &summonParam = *it;
    auto *monstCfg = sMonsterConfig.Get(summonParam.MonsterName);
    if (!monstCfg) return ERR_NOMONSTER;

    auto delayTime = GetApplySkillDelayTime(skillID, x, y);
    if (delayTime == 0) {
        auto &petMgr = self->GetPetMgr();
        auto petNum = petMgr.GetPetNum();

        if (petNum >= summonParam.MaxNum) {
            petMgr.PetTeleportToMaster();
        }
        else {
            auto *pet = petMgr.PetMonsterByID(monstCfg->Id);
            if (!pet) return ERR_NOMONSTER;
            pet->SetRoleProp(role_level, summonParam.MonsterLevel);
            TRIGGER_EVENT(self, trigger_summon, self->GetGUIDAsString(), pet->GetGUIDAsString());
        }

        SendSpellAck(ERR_OK, skillID, clientSN);
        self->NotifyAroundPlayers_SpellNtf(targetGUID, skillID, x, y);
    }
    else {
        SendSpellAck(ERR_OK, skillID, clientSN);
        self->NotifyAroundPlayers_SpellNtf(targetGUID, skillID, x, y);

        auto actorGUID = self->GetGUID();
        auto petTemplateID = monstCfg->Id;
        auto MaxNum = summonParam.MaxNum;
        auto MonsterLevel = summonParam.MonsterLevel;

        auto callback = [=](const TimerData & data) {
            auto itr = mTimeridmap.find(data.id);
            if (itr != mTimeridmap.end())
            {
                mTimeridmap.erase(itr);
            }
            mNeedTimerUpdate = true;
            auto *actor = MapRoleMgr::GetInstance()->FindPlayer(actorGUID);
            if (actor == nullptr) return;
            if (actor != self || !self->CheckAlive()) return;

            auto &petMgr = actor->GetPetMgr();
            auto petNum = petMgr.GetPetNum();

            if (petNum >= MaxNum) {
                petMgr.PetTeleportToMaster();
            }
            else {
                auto *pet = petMgr.PetMonsterByID(petTemplateID);
                if (!pet) return;
                pet->SetRoleProp(role_level, MonsterLevel);
                TRIGGER_EVENT(self, trigger_summon, self->GetGUIDAsString(), pet->GetGUIDAsString());
            }
        };

        auto Timerid = ITimeHelper::GetInstance()->AddTimer(delayTime, false, callback);
        //ITimeHelper::GetInstance()->AddStrData(Timerid, "name", "DoApplySkill_Summon");
        mTimeridmap[Timerid] = delayTime;
    }

    return ERR_OK;
}

uint16_t RoleSkill::DoApplySkill_Doplganr(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN)
{
    auto *skillCfg = GetSkillCfg(skillID);
    if (!skillCfg) return ERR_NO_CFG;

    auto *player = GetPlayer();
    if (!player) return ERR_UNKNOW;

    auto *map = player->GetCurMap();
    if (!map) return ERR_UNKNOW;

    if (skillCfg->SpecialEffectParam.size() < 1)
        return ERR_INVALID_CFG;

    const auto &maxNum = skillCfg->SpecialEffectParam[0];

    auto &doplganrMgr = player->GetDoplganrMgr();
    if (!doplganrMgr) doplganrMgr = std::make_unique<PlayerDoplganrMgr>(player);

    auto delayTime = GetApplySkillDelayTime(skillID, x, y);

    if (delayTime == 0) {

        auto existNum = doplganrMgr->GetDoplganrNum();
		if (existNum >= maxNum)
        {
            auto& DoplganrList = player->GetDoplganrMgr()->GetDoplganrList();
            for (auto i : DoplganrList)
            {
                if (!i)continue;
                i->JumpToMaster();
            }
            return ERR_SKILL_REACH_UPLIMIT;
        }


        if (!map->FindJumpablePos(x, y)) return ERR_SKILL_NO_TARGET;

        auto *doplganr = MapRoleMgr::GetInstance()->CreatePlayerDoplganr(player->GetGUID());
        if (!doplganr) return ERR_SYSTEM;

        doplganr->SetMasterGUID(player->GetGUID());
        doplganr->SetName(player->GetName() + "的分身");
        doplganr->OnEnterMap(map);
        doplganr->SetRolePosNoEvent(x, y);
        doplganr->CloneMaster();
     
        doplganrMgr->AddDoplganr(doplganr);
        map->RoleEnter(doplganr);
    }
    else {
        auto playerGUID = player->GetGUID();

        auto callback = [=](const TimerData &data) {
            auto itr = mTimeridmap.find(data.id);
            if (itr != mTimeridmap.end())
            {
                mTimeridmap.erase(itr);
            }
            mNeedTimerUpdate = true;
            auto *player1 = MapRoleMgr::GetInstance()->FindPlayer(playerGUID);
            if (player1 == nullptr) return;
            if (player1 != player || !player->CheckAlive()) return;

            auto *map = player->GetCurMap();
            if (!map) return;

            auto &doplganrMgr = player->GetDoplganrMgr();
            if (!doplganrMgr) return;

            auto existNum = doplganrMgr->GetDoplganrNum();
            if (existNum >= maxNum)
            {
                auto& DoplganrList = player->GetDoplganrMgr()->GetDoplganrList();
                for (auto i : DoplganrList)
                {
                    if (!i)continue;
                    i->JumpToMaster();
                }
                return;
            }

            auto x0 = x;
            auto y0 = y;
            if (!map->FindJumpablePos(x0, y0)) return;

            auto *doplganr = MapRoleMgr::GetInstance()->CreatePlayerDoplganr(playerGUID);
            if (!doplganr) return;

            doplganr->SetName(player->GetName() + "的分身");
            doplganr->OnEnterMap(map);
            doplganr->SetRolePosNoEvent(x0, y0);
            
            doplganr->CloneMaster();
            
            doplganrMgr->AddDoplganr(doplganr);

            map->RoleEnter(doplganr);
        };

        auto Timerid = ITimeHelper::GetInstance()->AddTimer(delayTime, false, callback);
        //ITimeHelper::GetInstance()->AddStrData(Timerid, "name", "DoApplySkill_Doplganr");
        mTimeridmap[Timerid] = delayTime;
    }
    SendSpellAck(ERR_OK, skillID, clientSN);
    return ERR_OK;
}

uint16_t RoleSkill::DoApplySkill_Direct(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN)
{
    return DoApplySkill_Normal(skillID, x, y, targetGUID, clientSN);
}

void RoleSkill::ApplyBuffOnTarget(uint16_t skillID, uint64_t targetGUID)
{
    auto *cfg = GetSkillCfg(skillID);
    auto* actor = GetMaster();
    auto* role = MapRoleMgr::GetInstance()->FindRole(targetGUID);
    if (!cfg || !actor || !role) return;

    auto target = (actor == role) ? skill_buff_self : skill_buff_target;

    for (const auto &buff : cfg->AttachedBuff) {
        if (buff.Target == target || buff.Target == skill_buff_all) {
            role->AddBuffByRole(buff.BuffID, actor, skillID);
        }
    }
}

void RoleSkill::RemoveBuffFromTarget(uint16_t skillID, uint64_t targetGUID)
{
    auto *cfg = GetSkillCfg(skillID);
    auto *actor = GetMaster();
    auto *role = MapRoleMgr::GetInstance()->FindRole(targetGUID);
    if (!cfg || !actor || !role) return;

    auto target = (actor == role) ? skill_buff_self : skill_buff_target;

    for (const auto &buff : cfg->AttachedBuff) {
        if (buff.Target == target) {
            role->RemoveBuff(buff.BuffID);
        }
    }
}

DATA::Skill* RoleSkill::GetSkillCfg(uint16_t nSkillID)
{
    auto skillData = GetSkillData(nSkillID);
    if (skillData) return skillData->GetSkillCfg();
    return nullptr;
}

SkillData* RoleSkill::GetSkillData(uint16_t nSkillID)
{
    for (auto iter = mSkillList.begin(); iter != mSkillList.end(); ++iter) {
        if (iter->GetID() == nSkillID) {
            return &(*iter);
        }
    }
    return nullptr;
}

uint16_t RoleSkill::ConditionCheck(uint16_t skillID, bool checkCD, bool checkMP)
{
    auto result = CheckRoleState(skillID);
    if (result != ERR_OK) return result;

    result = CheckSkill(skillID, checkCD);
    if (result != ERR_OK) return result;

    if (checkMP) {
        result = CheckHPMP(skillID);
        if (result != ERR_OK) return result;
    }

    return ERR_OK;
}

uint16_t RoleSkill::CheckRoleState(uint16_t skillID)
{
    Role* pMaster = GetMaster();
    if (!pMaster || !pMaster->CheckAlive()) return ERR_SKILL_ROLE_DEAD;

    RoleState* pRoleState = pMaster->GetRoleState();
    if (!pRoleState)  return ERR_UNKNOW;

    auto state = pRoleState->GetState();

    switch (state) {
    case role_state_stall: return ERR_SKILL_CANT_USE;

    case role_state_rush: return ERR_SKILL_CANT_USE;

    case role_state_back: return ERR_SKILL_CANT_USE;

    default: break;
    }

    auto *cfg = GetSkillCfg(skillID);
    if (!cfg) return ERR_UNKNOW;

    switch (cfg->HurtType) {

    case skill_hurt_type_phy:
        if (pMaster->GetRoleProp(role_can_phy_atk) <= 0)
            return ERR_SKILL_CANT_PHY_ATK;
        break;

    case skill_hurt_type_mag:
        if (pMaster->GetRoleProp(role_can_mag_atk) <= 0)
            return ERR_SKILL_CANT_MAG_ATK;
        break;

    case skill_hurt_type_tao:
        if (pMaster->GetRoleProp(role_can_mag_atk) <= 0)
            return ERR_SKILL_CANT_MAG_ATK;
        break;

    default:
        break;
    }

    if (pMaster->GetRoleProp(role_can_use_skill) <= 0)
        return ERR_SKILL_CANT_USE;

    if (pMaster->GetRoleProp(role_has_collide) >= 1)
        return ERR_SKILL_COLLIDE;

    if (pMaster->GetRoleProp(role_has_repelled) >= 1)
        return ERR_SKILL_REPELLED;

    return ERR_OK;
}

uint16_t RoleSkill::CheckSkill(const uint16_t nSkillID, bool checkCD)
{
    auto pSkillConfig = GetSkillCfg(nSkillID);
    if (!pSkillConfig) return ERR_SKILL_NOT_EXIST;


    auto pSkillData = GetSkillData(nSkillID);
    if (!pSkillData) return ERR_SKILL_NOT_EXIST;

    if (pSkillConfig->SkillType == skill_type_switch && !pSkillData->IsActive())    // 开关技能未打开
        return ERR_SKILL_SWITCH;

    if (checkCD && pSkillData->InCD()) return ERR_SKILL_CD_CHAIN;       // 未冷却

    auto* cfg = GetSkillCfg(nSkillID);
    if (cfg)
    {
        if (cfg->CD == 0 && IsCastSkillInPubCD())
            return ERR_SKILL_CD_CHAIN;
    }
    return ERR_OK;
}

uint16_t RoleSkill::CheckHPMP(uint16_t skillID)
{
    auto *self = GetMaster();
    if (!self) return ERR_UNKNOW;

    auto hp = self->GetRoleProp(role_hp);
    auto hpcost = GetSkillCostAttValue(skillID, role_hp);
    auto mp = self->GetRoleProp(role_mp);
    auto mpcost = GetSkillCostAttValue(skillID, role_mp);

    return (hp >= hpcost && mp >= mpcost) ? ERR_OK : ERR_SKILL_COST_ATTR;
}

uint16_t RoleSkill::CheckDistance(uint16_t skillID, uint16_t x, uint16_t y)
{
    auto *cfg = GetSkillCfg(skillID);
    if (!cfg) return ERR_SKILL_NOT_EXIST;

    auto *self = GetMaster();
    if (!self) return ERR_UNKNOW;

    if (x == 0 && y == 0) return ERR_OK;
    if (cfg->CastDistance == 0) return ERR_OK;

    if (self->DistanceFromPos(x, y) > cfg->CastDistance)
        return ERR_SKILL_CAST_DISTANCE;

    return ERR_OK;
}

bool RoleSkill::CanApplySkillOnTarget(uint16_t skillID, Role *target)
{
    if (!target) return false;
    if (target->IsNpc()) return false;
    if (target->IsStallDummy()) return false;

    if (target->IsMonster()) {
        auto *monster = static_cast<Monster *>(target);
        if (monster->IsTreasureMonster()) return false;
    }

    auto* self = GetMaster();
    if (!self) return false;

    auto* cfg = GetSkillCfg(skillID);
    if (!cfg) return false;

    if ((target->IsInSafeRegion() || self->IsInSafeRegion()) && target != self) {
        bool res = (self->GetType() != target->GetType() && (self->IsMonster() || target->IsMonster()));
        if (res) return true;

        if (!cfg->SafeRangeEffect) return false;
    }

    //if (self->GetRoleAttr()->GetRoleProp(role_camp) && 
    //    self->GetRoleAttr()->GetRoleProp(role_camp) == target->GetRoleAttr()->GetRoleProp(role_camp))
    //    return false;

    if (self->IsPlayer()) {
        return CanApplySkillOnTarget_SelfIsPlayer(skillID, target);
    }
    else if (self->IsPet() || self->IsPlayerDoplganr()) {
        return CanApplySkillOnTarget_SelfIsServant(skillID, target);
    }
    else if (self->IsMonster()) {
        return CanApplySkillOnTarget_SelfIsMonster(skillID, target);
    }
    else {
        return false;
    }
}

bool RoleSkill::CanApplySkillOnTarget_SelfIsPlayer(uint16_t skillID, Role *target)
{
    auto *self = GetMaster();
    if (!self) return false;

    bool tarIsSelf = (target == self);
    bool tarIsPlayer = target->IsPlayer();
    bool tarIsMonster = target->IsMonster();
    bool tarIsPet = target->IsPet();
    bool tarIsBiaoChe = target->IsBiaoChe();
    bool tarIsPlayerDoplganr = target->IsPlayerDoplganr();
    bool tarIsServant = self->IsMyServant(target);

    auto *cfg = GetSkillCfg(skillID);
    auto &targetType = cfg->TargetType;

    if (targetType == skill_target_all) {

        auto atkMode = self->GetAttackMode();

        switch (atkMode) {

        case atk_mode_all: return true;

        case atk_mode_peace: return !(tarIsPlayer || tarIsPet || tarIsPlayerDoplganr || tarIsBiaoChe);

        case atk_mode_team: return !self->IsInSameTeam(target);

        case atk_mode_guild: return !self->IsInSameGuild(target);

        case atk_mode_pk: return (tarIsMonster && !tarIsBiaoChe) || target->IsGrayOrRedName();

        case atk_mode_camp: return !self->IsInSameCamp(target);

        default: return true;
        }
    }
    else if (targetType == skill_target_self) {
        return tarIsSelf;
    }
    else if (targetType == skill_target_friend) {
        if (tarIsSelf || tarIsServant) return true;

        auto atkMode = self->GetAttackMode();

        switch (atkMode) {

        case atk_mode_team: return self->IsInSameTeam(target);

        case atk_mode_guild: return self->IsInSameGuild(target);

        default: return false;
        }
    }
    else if (targetType == skill_target_monster) {
        return tarIsMonster;
    }
    else if (targetType == skill_target_player) {
        if (tarIsSelf || tarIsServant) return false;
        auto atkMode = self->GetAttackMode();

        switch (atkMode) {

        case atk_mode_team:
            if (self->IsInSameTeam(target)) return false;
            return tarIsPlayer || tarIsPet || tarIsPlayerDoplganr || tarIsBiaoChe;

        case atk_mode_guild:
            if (self->IsInSameGuild(target)) return false;
            return tarIsPlayer || tarIsPet || tarIsPlayerDoplganr || tarIsBiaoChe;

        default:
            return tarIsPlayer || tarIsPet || tarIsPlayerDoplganr || tarIsBiaoChe;
        }
    }

    return false;
}

bool RoleSkill::CanApplySkillOnTarget_SelfIsServant(uint16_t skillID, Role *target)
{
    auto *self = GetMaster();
    if (!self) return false;

    Player *master = nullptr;
    if (self->IsPet()) {
        auto *pet = static_cast<Pet *>(self);
        master = pet->GetMaster();
    }
    else if (self->IsPlayerDoplganr()) {
        auto *doplganr = static_cast<PlayerDoplganr *>(self);
        master = doplganr->GetMaster();
    }
    if (!master) return false;

    bool tarIsSelf = (target == self);
    bool tarIsPlayer = target->IsPlayer();
    bool tarIsMonster = target->IsMonster();
    bool tarIsPet = target->IsPet();
    bool tarIsPlayerDoplganr = target->IsPlayerDoplganr();
    bool tarIsBiaoChe = target->IsBiaoChe();
    bool tarIsMaster = false;
    bool tarSameMaster = false;
    Player *tarMaster = nullptr;

    if (tarIsPlayer) {
        if (target == master) tarIsMaster = true;
    }
    else if (tarIsPet || tarIsBiaoChe) {
        auto *monster = static_cast<Monster *>(target);
        tarMaster = monster->GetMaster();
        if (tarMaster == master) tarSameMaster = true;
    }
    else if (tarIsPlayerDoplganr) {
        auto *doplganr = static_cast<PlayerDoplganr *>(target);
        tarMaster = doplganr->GetMaster();
        if (tarMaster == master) tarSameMaster = true;
    }

    auto *cfg = GetSkillCfg(skillID);
    auto &targetType = cfg->TargetType;

    if (targetType == skill_target_all) {

        auto atkMode = master->GetAttackMode();

        switch (atkMode) {

        case atk_mode_all: return true;

        case atk_mode_peace: return !(tarIsPlayer || tarIsPet || tarIsPlayerDoplganr || tarIsBiaoChe);

        case atk_mode_team: return !master->IsInSameTeam(target);

        case atk_mode_guild: return !master->IsInSameGuild(target);

        case atk_mode_pk: return (tarIsMonster && !tarIsBiaoChe) || target->IsGrayOrRedName();

        case atk_mode_camp: return !master->IsInSameCamp(target);

        default: return true;
        }
    }
    else if (targetType == skill_target_self) {
        return tarIsSelf;
    }
    else if (targetType == skill_target_friend) {       // 目标是友方
        if (tarIsSelf || tarIsMaster || tarSameMaster) return true;

        auto atkMode = master->GetAttackMode();

        switch (atkMode) {

        case atk_mode_team: return master->IsInSameTeam(target);

        case atk_mode_guild: return master->IsInSameGuild(target);

        default: return false;
        }
    }
    else if (targetType == skill_target_monster) {
        return tarIsMonster;
    }
    else if (targetType == skill_target_player) {
        if (tarIsSelf || tarIsMaster || tarSameMaster) return false;
        auto atkMode = master->GetAttackMode();

        switch (atkMode) {

        case atk_mode_team:
            if (master->IsInSameTeam(target)) return false;
            return tarIsPlayer || tarIsPet || tarIsPlayerDoplganr || tarIsBiaoChe;

        case atk_mode_guild:
            if (master->IsInSameGuild(target)) return false;
            return tarIsPlayer || tarIsPet || tarIsPlayerDoplganr || tarIsBiaoChe;

        default:
            return tarIsPlayer || tarIsPet || tarIsPlayerDoplganr || tarIsBiaoChe;
        }
    }

    return false;
}

bool RoleSkill::CanApplySkillOnTarget_SelfIsMonster(uint16_t skillID, Role *target)
{
    auto *self = GetMaster();
    if (!self) return false;

    bool tarIsSelf = (target == self);
    bool tarIsPlayer = target->IsPlayer();
    bool tarIsMonster = target->IsMonster();
    bool tarIsPet = target->IsPet();
    bool tarIsPlayerDoplganr = target->IsPlayerDoplganr();
    bool tarIsBiaoChe = target->IsBiaoChe();

    auto *cfg = GetSkillCfg(skillID);
    auto &targetType = cfg->TargetType;

    if (targetType == skill_target_all) {
        return true;
    }
    else if (targetType == skill_target_self) {
        return tarIsSelf;
    }
    else if (targetType == skill_target_friend) {
        return tarIsMonster;
    }
    else if (targetType == skill_target_monster) {
        return tarIsMonster;
    }
    else if (targetType == skill_target_player) {
        return tarIsPlayer || tarIsPet || tarIsPlayerDoplganr || tarIsBiaoChe;
    }

    return false;
}

uint16_t RoleSkill::GetSkillCastTargets(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, AttackResults &atkResults)
{
    auto *cfg = GetSkillCfg(skillID);
    if (!cfg) return ERR_UNKNOW;

    if (cfg->TargetType == skill_target_friend)
        return GetSkillCastTargets_Friend(skillID, x, y, targetGUID, atkResults);

    auto *self = GetMaster();
    if (!self) return ERR_UNKNOW;

    auto *map = self->GetCurMap();
    if (!map) return ERR_UNKNOW;

    if (!x && !y && cfg->CastWay == skill_cast_target) {

        auto *target = MapRoleMgr::GetInstance()->FindRole(targetGUID);
        if (!target) return ERR_SKILL_NO_TARGET;

        x = target->GetRolePosX();
        y = target->GetRolePosY();
    }

    PositionList posList;

    auto result = GetSkillCastPositionList(skillID, x, y, posList);
    if (result != ERR_OK) return result;

    for (const auto &it : posList) {

        const auto &x1 = it.first;
        const auto &y1 = it.second;

        auto *target = map->GetRoleInPoint(x1, y1);
        if (!target) continue;

        if (!CanApplySkillOnTarget(skillID, target)) continue;

        AttackResult res;
        res.actorGUID = self->GetGUID();
        res.actorName = self->GetName();
        res.targetGUID = target->GetGUID();
        res.skillId = skillID;
        atkResults.emplace_back(res);
    }

    if (cfg->CastWay == skill_cast_target && atkResults.empty())
        return ERR_OK;

    return ERR_OK;
}

uint16_t RoleSkill::GetSkillCastTargets_Friend(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, AttackResults &atkResults)
{
    auto *cfg = GetSkillCfg(skillID);
    if (!cfg) return ERR_UNKNOW;

    auto *self = GetMaster();
    if (!self) return ERR_UNKNOW;

    AttackResult res;
    res.actorGUID = self->GetGUID();
    res.actorName = self->GetName();
    res.skillId = skillID;

    if (cfg->RangeType == skill_range_type_point) {

        auto *target = MapRoleMgr::GetInstance()->FindRole(targetGUID);
        if (!target) {
            res.targetGUID = self->GetGUID();
            atkResults.emplace_back(res);
            return ERR_OK;
        }

        bool tarIsPlayer = target->IsPlayer();
        bool tarIsPet = target->IsPet();
        bool tarIsPlayerDoplganr = target->IsPlayerDoplganr();
        Player *tarMaster = nullptr;

        if (self->IsPlayer()) {
            bool tarIsServant = false;

            if (tarIsPet) {
                auto *pet = static_cast<Pet *>(target);
                tarMaster = pet->GetMaster();
                if (tarMaster == self) tarIsServant = true;
            }
            else if (tarIsPlayerDoplganr) {
                auto *doplganr = static_cast<PlayerDoplganr *>(target);
                tarMaster = doplganr->GetMaster();
                if (tarMaster == self) tarIsServant = true;
            }

            if (tarIsServant) {     // 自己的宠物
                res.targetGUID = targetGUID;
                atkResults.emplace_back(res);
                return ERR_OK;
            }

            bool tarIsOK = false;
            auto atkMode = self->GetAttackMode();
            auto *player = static_cast<Player *>(self);

            switch (atkMode) {

            case atk_mode_team:
                if (tarIsPlayer && player->IsInSameTeam(target))        // 同一队
                    tarIsOK = true;
                else if ((tarIsPet || tarIsPlayerDoplganr) && player->IsInSameTeam(tarMaster))      // 队友的宠物
                    tarIsOK = true;
                break;

            case atk_mode_guild:
                if (tarIsPlayer && player->IsInSameGuild(target))       // 同一工会
                    tarIsOK = true;
                else if ((tarIsPet || tarIsPlayerDoplganr) && player->IsInSameGuild(tarMaster))     // 同一工会的宠物
                    tarIsOK = true;
                break;

            default:
                break;
            }

            res.targetGUID = tarIsOK ? targetGUID : self->GetGUID();
            atkResults.emplace_back(res);
        }
        else if (self->IsPlayerDoplganr() || self->IsPet()) {
            Player *master = nullptr;
            if (self->IsPlayerDoplganr()) {
                auto *doplganr = static_cast<PlayerDoplganr *>(self);
                master = doplganr->GetMaster();
            }
            else {
                auto *pet = static_cast<Pet *>(self);
                master = pet->GetMaster();
            }
            if (!master) return ERR_UNKNOW;

            bool tarIsMaster = false;
            bool tarSameMaster = false;

            if (tarIsPlayer) {
                if (target == master) tarIsMaster = true;
            }
            else if (tarIsPet) {
                auto *pet = static_cast<Pet *>(target);
                tarMaster = pet->GetMaster();
                if (tarMaster == master) tarSameMaster = true;
            }
            else if (tarIsPlayerDoplganr) {
                auto *doplganr = static_cast<PlayerDoplganr *>(target);
                tarMaster = doplganr->GetMaster();
                if (tarMaster == master) tarSameMaster = true;
            }

            if (tarIsMaster || tarSameMaster) {     // 自己的主人或同一主人
                res.targetGUID = targetGUID;
                atkResults.emplace_back(res);
                return ERR_OK;
            }

            bool tarIsOK = false;
            auto atkMode = master->GetAttackMode();

            switch (atkMode) {

            case atk_mode_team:
                if (tarIsPlayer && master->IsInSameTeam(target))        // 同一队
                    tarIsOK = true;
                else if ((tarIsPet || tarIsPlayerDoplganr) && master->IsInSameTeam(tarMaster))      // 队友的宠物
                    tarIsOK = true;
                break;

            case atk_mode_guild:
                if (tarIsPlayer && master->IsInSameGuild(target))       // 同一工会
                    tarIsOK = true;
                else if ((tarIsPet || tarIsPlayerDoplganr) && master->IsInSameGuild(tarMaster))     // 同一工会的宠物
                    tarIsOK = true;
                break;

            default:
                break;
            }

            res.targetGUID = tarIsOK ? targetGUID : self->GetGUID();
            atkResults.emplace_back(res);
        }
        else {
            res.targetGUID = self->GetGUID();
            atkResults.emplace_back(res);
        }

        return ERR_OK;
    }

    PositionList posList;
    auto result = GetSkillCastPositionList(skillID, x, y, posList);
    if (result != ERR_OK) return result;

    auto *map = self->GetCurMap();
    if (!map) return ERR_UNKNOW;

    for (const auto &it : posList) {

        const auto &x1 = it.first;
        const auto &y1 = it.second;

        auto *target = map->GetRoleInPoint(x1, y1);
        if (!target) continue;

        if (!CanApplySkillOnTarget(skillID, target)) continue;

        res.targetGUID = target->GetGUID();
        atkResults.emplace_back(res);
    }

    return ERR_OK;
}

uint16_t RoleSkill::GetSkillCastPositionList(uint16_t skillID, uint16_t x, uint16_t y, PositionList &posList)
{
    auto *cfg = GetSkillCfg(skillID);
    if (!cfg) return ERR_SKILL_NOT_EXIST;

    switch (cfg->RangeType) {

    case skill_range_type_point:
        return GetSkillCastPositionList_Point(skillID, x, y, posList);

    case skill_range_type_line:
        return GetSkillCastPositionList_Line(skillID, x, y, posList);

    case skill_range_type_rect:
        return GetSkillCastPositionList_Rect(skillID, x, y, posList);

    case skill_range_type_cust:
        return GetSkillCastPositionList_Cust(skillID, x, y, posList);

    default: return ERR_UNKNOW;
    }
}

uint16_t RoleSkill::GetSkillCastPositionList_Point(uint16_t skillID, uint16_t x, uint16_t y, PositionList &posList)
{
    auto *cfg = GetSkillCfg(skillID);
    if (!cfg) return ERR_SKILL_NOT_EXIST;

    if (cfg->TargetType == skill_target_self) {

        auto *self = GetMaster();
        if (!self) return ERR_UNKNOW;

        x = self->GetRolePosX();
        y = self->GetRolePosY();
    }

    posList.emplace_back(x, y);
    return ERR_OK;
}

uint16_t RoleSkill::GetSkillCastPositionList_Line(uint16_t skillID, uint16_t x, uint16_t y, PositionList &posList)
{
    auto *cfg = GetSkillCfg(skillID);
    if (!cfg) return ERR_SKILL_NOT_EXIST;

    auto *self = GetMaster();
    if (!self) return ERR_UNKNOW;

    auto x0 = self->GetRolePosX();
    auto y0 = self->GetRolePosY();
    auto dir = self->GetRoleDir();

    auto distLeft = cfg->RangeParam;
    if (distLeft == 0) return ERR_SKILL_NO_TARGET;

    while (distLeft-- > 0) {

        switch (dir) {

        case dir_up: --y0; break;

        case dir_right_up: ++x0; --y0; break;

        case dir_right: ++x0; break;

        case dir_right_down: ++x0; ++y0; break;

        case dir_down: ++y0; break;

        case dir_left_down: --x0; ++y0; break;

        case dir_left: --x0; break;

        case dir_left_up: --x0; --y0; break;

        default: return ERR_SKILL_NO_TARGET;
        }

        posList.emplace_back(x0, y0);
    }

    return ERR_OK;
}

uint16_t RoleSkill::GetSkillCastPositionList_Rect(uint16_t skillID, uint16_t x, uint16_t y, PositionList &posList)
{
    auto *cfg = GetSkillCfg(skillID);
    if (!cfg) return ERR_SKILL_NOT_EXIST;

    auto n = cfg->RangeParam;

    if (!x && !y) {

        auto *self = GetMaster();
        if (!self) return ERR_UNKNOW;

        x = self->GetRolePosX();
        y = self->GetRolePosY();
    }

    for (auto i = x - n; i <= x + n; ++i)
        for (auto j = y - n; j <= y + n; ++j)
            posList.emplace_back(i, j);

    return ERR_OK;
}

uint16_t RoleSkill::GetSkillCastPositionList_Cust(uint16_t skillID, uint16_t x, uint16_t y, PositionList &posList)
{
    auto *cfg = GetSkillCfg(skillID);
    if (!cfg) return ERR_SKILL_NOT_EXIST;

    auto *self = GetMaster();
    if (!self) return ERR_UNKNOW;

    auto dir = self->GetRoleDir();
    auto rotate = dir - dir_up;

    int16_t dx, dy;

    if (cfg->SkillType != skill_type_cast || x == 0 && y == 0) {
        x = self->GetRolePosX();
        y = self->GetRolePosY();
    }

    for (auto seq : cfg->CustomShape) {     // 不要用引用

        if (cfg->SkillType != skill_type_cast)
            seq = RotateSeq(seq, rotate);

        Tools::GetRelativePos(seq, dx, dy);
        posList.emplace_back(x + dx, y + dy);
    }

    return ERR_OK;
}

uint32_t RoleSkill::GetTrapSkillExpireTime(uint16_t skillID)
{
    const auto *cfg = GetSkillCfg(skillID);
    if (!cfg) return 0;

    if (cfg->SpecialEffectType == skill_special_trap_trigger) {

        if (cfg->SpecialEffectParam.size() < 4) return 0;

        auto *self = GetMaster();
        if (!self) return 0;
        uint32_t param;

        switch (cfg->HurtType) {

        case skill_hurt_type_phy:
            param = self->GetRoleProp(role_max_phy_atk);
            break;

        case skill_hurt_type_mag:
            param = self->GetRoleProp(role_max_mag_atk);
            break;

        case skill_hurt_type_tao:
            param = self->GetRoleProp(role_max_tao_atk);
            break;

        default: return 0;
        }

        auto baseTime = cfg->SpecialEffectParam[1];
        auto maxTime = cfg->SpecialEffectParam[2];
        auto coff = cfg->SpecialEffectParam[3];

        auto expireTime = baseTime + uint32_t(param * coff / 10000. + 0.5);
        if (expireTime > maxTime) expireTime = maxTime;

        return expireTime;
    }
    else if (cfg->SpecialEffectType == skill_special_trap_rt) {

        if (cfg->SpecialEffectParam.size() < 2) return 0;

        return cfg->SpecialEffectParam[0];
    }

    return 0;
}

int32_t RoleSkill::GetSkillCostAttValue(uint16_t skillID, uint16_t att)
{
    auto *cfg = GetSkillCfg(skillID);
    if (!cfg) return 0;

    switch (att)
    {
    case role_hp: return cfg->ConsumeHP;
    case role_mp: return cfg->ConsumeMP;
    default: return 0;
    }
}

void RoleSkill::CalculateHarmData(AttackResult& res,uint32_t round)
{
    CLuaObject retHarmData = NewLuaObj();
    //是否触发特定技能事件
    auto monster = MapRoleMgr::GetInstance()->FindMonster(res.targetGUID);
    if (monster && monster->GetAIMonster())
    {
        auto& monsterTriggerMap = monster->GetAIMonster()->GetAIBehaviourMap();
        if (monsterTriggerMap.find(monster_ai_self_harmed_by_special_skill) != monsterTriggerMap.end())
        {
            auto cfg = monster->GetConfig();
            if (cfg)
            {
                auto map = cfg->SkillDamageCoff;
                if (map.find(res.skillId) != map.end())
                {
                    LuaBindCallVoid(monsterTriggerMap[monster_ai_self_harmed_by_special_skill].callback, monster->GetGUIDAsString(), monster->GetAIMonster()->GetTarGuid());
                }
            }
        }
    }

    if (LuaGmMgr::GetInstance()->IsLuaGM(res.targetGUID))
    {
        return;
    }

    //if (monster && monster->GetRoleAttr() && monster->GetRoleAttr()->GetRoleProp(role_max_hp) != 0)
    {
        TRIGGER_EVENT_RET<CLuaObject>(retHarmData, trigger_role_pre_harm, std::to_string(res.actorGUID), std::to_string(res.targetGUID), res.skillId, round);
        if (luabind::type(retHarmData["Harm"]) == LUA_TNUMBER
            && luabind::type(retHarmData["Type"]) == LUA_TNUMBER) {
            res.decreaseHP = luabind::object_cast<int32_t>(retHarmData["Harm"]);
            res.type = luabind::object_cast<int32_t>(retHarmData["Type"]);
        }
    }
}

void RoleSkill::CaculateHatedValue(uint16_t skillID, uint64_t tarGuid)
{
    if (!mMaster)return;
    auto role = MapRoleMgr::GetInstance()->FindRole(tarGuid);
    if (!role)return;
    auto guid = mMaster->GetGUID();
    if (guid == tarGuid)return;
    auto pSkillConfig = GetSkillCfg(skillID);
    if (!pSkillConfig) return;

    if (role->IsPlayer())
    {
        auto player = static_cast<Player*>(role);
        auto &petlist = player->GetPetMgr().GetPetList();
        for (auto i : petlist)
        {
            auto pet = MapRoleMgr::GetInstance()->FindPet(i);
            if (!pet)continue;
            pet->AddHatedValue(guid, pSkillConfig->Hatred);
        }
       
        if (player->GetDoplganrMgr())
        {
            auto& DoplganrList = player->GetDoplganrMgr()->GetDoplganrList();
            for (auto i : DoplganrList)
            {
                if (!i)continue;
                i->AddHatedValue(guid, pSkillConfig->Hatred);
            }
        }
    }
    else if(role->IsMonster())
    {
        auto monster = static_cast<Monster*>(role);
        if (!monster)return;
        monster->AddHatedValue(guid, pSkillConfig->Hatred);
    }
    else if (role->IsPet())
    {
        auto pet = static_cast<Pet*>(role);
        if (!pet||pet->GetPetType() != pet_type_taoist)return;
        if (pet->GetMasterGUID() == mMaster->GetGUID())return;
        pet->AddHatedValue(guid, pSkillConfig->Hatred);
    }
    else if (role->IsPlayerDoplganr())
    {
        auto pet = static_cast<PlayerDoplganr*>(role);
        if (!pet || pet->GetType() != role_type_player_doplganr)return;
        if (pet->GetMasterGUID() == mMaster->GetGUID())return;
        pet->AddHatedValue(guid, 1);
    }
    auto attrole = MapRoleMgr::GetInstance()->FindRole(guid);
    if (attrole->IsPlayer())
    {
        //如果是玩家主动攻击对方   分身一起攻击
        auto player = static_cast<Player*>(attrole);
        if (player && player->GetDoplganrMgr())
        {
            auto& DoplganrList = player->GetDoplganrMgr()->GetDoplganrList();
            for (auto i : DoplganrList)
            {
                if (!i)continue;
                i->AddHatedValue(tarGuid, pSkillConfig->Hatred * 5);
            }
        }
        
    }
}

void RoleSkill::StartCD(uint16_t nSkillID)
{
    auto pSkillData = GetSkillData(nSkillID);
    if (pSkillData) pSkillData->StartCD();
}

bool RoleSkill::IsInCD(uint16_t nSkillID)
{
    auto pSkillData = GetSkillData(nSkillID);
    if (pSkillData) return pSkillData->InCD();
    return false;
}

void RoleSkill::SetSkillProp(uint16_t skillID, uint16_t propType, const std::string& propValue)
{
    auto* skillData = GetSkillData(skillID);
    if (!skillData) return;

    if (!skillData->ModifyCfg(sSkillConfig.Get(skillID), { propType ,propValue }))
        return;

    string cfg = EncodeSkillCfg(skillData->GetSkillCfgModifyMap());
    if (cfg.empty()) return;

    auto* self = GetMaster();
    if (self && self->IsPlayer()) {
        auto* player = static_cast<Player*>(self);
        if (!player) return;
        player->SendSkillPropChangedNtfToGS(skillID, cfg);
    }
}

bool RoleSkill::GetSkillProp(uint16_t skillID, uint16_t propType)
{
    return ::GetSkillProp(GetSkillCfg(skillID), propType);
}

void RoleSkill::StartFireTimeCountDown(uint16_t nSkillID)
{
    auto pSkillData = GetSkillData(nSkillID);
    if (pSkillData) pSkillData->StartFireTimeCountDown();
}

void RoleSkill::StopFireTimeCountDown(uint16_t nSkillID)
{
    auto pSkillData = GetSkillData(nSkillID);
    if (pSkillData) pSkillData->StopFireTimeCountDown();
}

uint16_t RoleSkill::GetApplySkillDelayTime(uint16_t skillID, uint16_t x, uint16_t y)
{
    auto *cfg = GetSkillCfg(skillID);
    if (!cfg) return 0;

    auto *self = GetMaster();
    if (!self) return 0;

    if (cfg->SkillType == skill_type_cast)
        return cfg->FixedDelay + self->GetRoleProp(role_casting_speed);
    else
        return cfg->FixedDelay;
}

void RoleSkill::SendSpellAck(int32_t ecode, uint16_t skillID, uint16_t clientSN)
{
    auto *self = GetMaster();
    if (!self) return;

    Player *player = nullptr;

    if (self->IsPlayer()) {
        player = static_cast<Player *>(self);
    }
    /*else if (self->IsPlayerDoplganr()) {
        auto *doplganr = static_cast<PlayerDoplganr *>(self);
        player = doplganr->GetMaster();
    }*/

    if (player) {
        auto actorGUID = self->GetGUID();
        player->SendSpellAck(actorGUID, ecode, skillID, clientSN);
    }
}

void RoleSkill::DecreaseActorHPMP(uint16_t skillID)
{
    auto *player = GetPlayer();
    if (!player) return;

    auto decreaseHP = GetSkillCostAttValue(skillID, role_hp);
    auto decreaseMP = GetSkillCostAttValue(skillID, role_mp);
    TRIGGER_EVENT_RET(decreaseMP, player, trigger_pre_decrease_mp,
                      player->GetGUIDAsString(), skillID, decreaseMP);
    player->OnRoleUpdateHPMP(-decreaseHP, -decreaseMP);
}

void RoleSkill::AddProficiency(uint16_t skillID)
{
    auto *player = GetPlayer();
    if (!player) return;

    auto *globalCfg = sGlobalConfig.GetData();
    if (!globalCfg) return;

    if (skillID == globalCfg->CommonAttackSkillID) return;

    auto *skillData = GetSkillData(skillID);
    if (!skillData) return;

    auto *skillCfg = skillData->GetSkillCfg();
    if (!skillCfg) return;

    if (skillCfg->NeedProficiency == 0 && skillCfg->NextLevelID == 0) return;

    auto curProficiency = skillData->GetProficiency();
    if (curProficiency >= skillCfg->NeedProficiency && skillCfg->NextLevelID == 0) return;      // 满级

    unsigned int gainProficiency = 0;
    if (CLuaLib::GetInstance()->IsHaveEvent(trigger_proficiency_pre_changed)) {
        TRIGGER_EVENT_RET(gainProficiency, player, trigger_proficiency_pre_changed, 
            player->GetGUIDAsString(), skillID, globalCfg->GainProficiencyMin, globalCfg->GainProficiencyMax);
    }
    else {
        gainProficiency = Tools::GenerateRandomInteger(globalCfg->GainProficiencyMin, globalCfg->GainProficiencyMax);
    }

    auto newProficiency = curProficiency + gainProficiency;

    if (skillCfg->NextLevelID == 0 && newProficiency > skillCfg->NeedProficiency)
        newProficiency = skillCfg->NeedProficiency;

    skillData->SetProficiency(newProficiency);
    player->SendSkillProficiencyNtfToGS(skillID, newProficiency);
    TRIGGER_EVENT(player, trigger_proficiency_changed, player->GetGUIDAsString(), skillID, newProficiency - curProficiency);

    if (newProficiency < skillCfg->NeedProficiency) return;

    auto roleLevel = player->GetRoleProp(role_level);
    if (roleLevel < skillCfg->NeedRoleLevel) return;

    // 满足升级条件
    auto NextLevelID = skillCfg->NextLevelID;   // 保存NextLevelID，AlterSkill之后skillCfg会被删除
    player->AlterSkill(skillID, NextLevelID);
    TRIGGER_EVENT(player, trigger_skill_level_up, player->GetGUIDAsString(), skillID, NextLevelID);
}

bool RoleSkill::AddProficiencyValue(uint16_t skillID, uint32_t value)
{
    auto* player = GetPlayer();
    if (!player) return false;

    auto* globalCfg = sGlobalConfig.GetData();
    if (!globalCfg) return false;

    if (skillID == globalCfg->CommonAttackSkillID) return false;

    auto* skillData = GetSkillData(skillID);
    if (!skillData) return false;

    auto* skillCfg = skillData->GetSkillCfg();
    if (!skillCfg) return false;

    if (skillCfg->NeedProficiency == 0 && skillCfg->NextLevelID == 0) return false;
    auto curProficiency = skillData->GetProficiency();
    if (curProficiency >= skillCfg->NeedProficiency && skillCfg->NextLevelID == 0) return false;      // 满级

    auto newProficiency = curProficiency + value;

    if (skillCfg->NextLevelID == 0 && newProficiency > skillCfg->NeedProficiency)
        newProficiency = skillCfg->NeedProficiency;

    skillData->SetProficiency(newProficiency);
    player->SendSkillProficiencyNtfToGS(skillID, newProficiency);
    TRIGGER_EVENT(player, trigger_proficiency_changed, player->GetGUIDAsString(), skillID, newProficiency - curProficiency);

    if (newProficiency < skillCfg->NeedProficiency) return true;

    auto roleLevel = player->GetRoleProp(role_level);
    if (roleLevel < skillCfg->NeedRoleLevel) return true;

    // 满足升级条件
    auto NextLevelID = skillCfg->NextLevelID;   // 保存NextLevelID，AlterSkill之后skillCfg会被删除
    player->AlterSkill(skillID, NextLevelID);
    TRIGGER_EVENT(player, trigger_skill_level_up, player->GetGUIDAsString(), skillID, NextLevelID);
    return true;
}

bool RoleSkill::SetSkillLevel(uint16_t skillID)
{
    auto* player = GetPlayer();
    if (!player) return false;

    auto skillTable = sSkillConfig.Get(skillID);
    if (nullptr == skillTable) return false;

    if (IsSkillExist(skillID)) return true;

    if (skillTable->SkillChainID != 0)
    {
        std::vector<uint16_t> vec = GetSkillIDsByChainID(skillTable->SkillChainID);
        if (vec.empty()) return false;

        player->AlterSkill(vec[0], skillID);
        TRIGGER_EVENT(player, trigger_skill_level_up, player->GetGUIDAsString(), vec[0], skillID);
        return true;
    }
     
    return false;
}

uint16_t RoleSkill::RotateSeq(uint16_t seq, uint8_t by)
{
    if (seq == 0) return 0;
    if (by == 0) return seq;
    if (by > 7) by = by % 8; 

    auto square = [](uint16_t x) { return x * x; };

    uint16_t n = 1;

    while (seq >= square(2 * n + 1)) ++n;

    seq += by * n;

    auto min = square(2 * n - 1);
    auto max = square(2 * n + 1) - 1;

    if (seq > max) {
        seq = seq - max - 1 + min;
    }

    return seq;
}

void RoleSkill::StartCastSkillPubCD(uint32_t cdTime)
{
    mCastSkillPubCDTime = cdTime;
    mCastSkillPubCDCur = 0;
    SetNeedUpdate(skill_need_update_flag);
}

bool RoleSkill::IsCastSkillInPubCD()
{
    return (mCastSkillPubCDTime != 0);
}

void RoleSkill::UpdateCastSkillPubCD(int32_t delta)
{
    if (mCastSkillPubCDTime == 0) return;

    mCastSkillPubCDCur += delta;
    if (mCastSkillPubCDCur >= mCastSkillPubCDTime) {
        mCastSkillPubCDTime = 0;
        mCastSkillPubCDCur = 0;
    }
}

void RoleSkill::AddHateValue(uint32_t skillID, uint64_t tarGuid)
{
    auto role = MapRoleMgr::GetInstance()->FindRole(tarGuid);
    if (!role)return;
    if (role->IsMonster())
    {
        if (mMaster->IsMonster())return;
        auto monster = static_cast<Monster*>(role);
        if (monster->GetRoleState()->GetState() != role_state_die)
        {
            monster->GetRoleState()->SetState(role_state_damage);
        }
    }
    CaculateHatedValue(skillID, tarGuid);
}

void RoleSkill::AddGrayBuff(uint64_t tarGuid)
{
    if (!mMaster) return;
    if (!mMaster->IsPlayer())return;
    auto role = MapRoleMgr::GetInstance()->FindRole(tarGuid);
    if (!role)return;
    //玩家打灰名不变灰
    if (role->GetRoleProp(role_is_gray) != 0) return;

    if (role->IsPlayer() && !role->IsInSafeRegion())
    {
        auto player = static_cast<Player*>(role);
        ////增加灰名
        //if (PKValueMgr::IsWhiteName(player->GetGUID()) || PKValueMgr::IsYellowName(player->GetGUID()))

        //非红名状态下加灰名buff
        if (player->IsRedName()) {
            return;
        }

        if (!mMaster->IsRedName())
        {
            mMaster->AddBuffByRole(sGlobalConfig.GetData()->GrayBuffID, mMaster, 0);
        }
    }
}

void RoleSkill::AddPetTarget(uint64_t tarGuid)
{
    auto taoistPetAddTargetFunc = [=](Pet* pet,Role* tar,bool isDefend) {
        auto petAI = pet->GetAIPet();
        if (!petAI)return;

        if (pet->GetPetType() != pet_type_taoist)return;

        if (petAI->IsFollowMasterAttack()) {
            if (!isDefend) {
                if (pet->GetGUID() == tarGuid)return;
                auto dis = pet->DistanceFromRole(tar);
                if (!petAI->IsInTraRange(dis)) return;
                petAI->SetTarGuid(tarGuid);
                return;
            }
            if (petAI->GetTarGuid())return;
        }

        auto finalTarGuid = tar->GetGUID();
        if (tar->IsPlayer())
        {
            auto tarPlayer = static_cast<Player*>(tar);
            if (!tarPlayer)return;
            if (tarPlayer->GetRoleProp(role_is_stealth) >= 1)return;
            auto& tarPetlist = tarPlayer->GetPetMgr().GetPetList();
            if (!tarPetlist.empty())
            {
                auto dis = pet->DistanceFromRole(tarPlayer);
                for (auto j : tarPetlist)
                {
                    auto tmpPet = MapRoleMgr::GetInstance()->FindPet(j);
                    if (!tmpPet)return;
                    if (pet->DistanceFromRole(tmpPet) < dis)
                    {
                        finalTarGuid = tmpPet->GetGUID();
                    }
                }
            }
        }
        else if (tar->IsPet())
        {
            auto finalPet = static_cast<Pet*>(tar);
            if (!finalPet || finalPet->GetMasterGUID() == pet->GetMasterGUID())return;
        }
        else if (tar->IsMonster()) {
            auto tarMonster = static_cast<Monster*>(tar);
            if (tarMonster->GetMasterGUID() == pet->GetMasterGUID())return;
        }

        auto finalTar = MapRoleMgr::GetInstance()->FindRole(finalTarGuid);
        if (!finalTar)return;

        if (!petAI->IsInTraRange(pet->DistanceFromRole(finalTar)))return;

        auto curTar = MapRoleMgr::GetInstance()->FindRole(petAI->GetTarGuid());
        if (!curTar || !curTar->CheckAlive())
        {
            petAI->SetTarGuid(finalTarGuid);
            return;
        }

        if (pet->DistanceFromRole(finalTar) < pet->DistanceFromRole(curTar))
        {
            petAI->SetTarGuid(finalTarGuid);
            return;
        }
    };

    auto role = MapRoleMgr::GetInstance()->FindRole(tarGuid);
    if (!role)return;
    if (role->IsInSafeRegion())return;
    if (role->IsMonster() && static_cast<Monster*>(role)->IsTreasureMonster())return;

    if (!mMaster)return;
    // 不是对着自己放技能
    if (mMaster->GetGUID() == tarGuid) return;

    if (mMaster->IsPlayer())
    {
        // 给技能释放者的宠物增加攻击目标
        auto player = static_cast<Player*>(mMaster);
        if (!player)return;
        auto& petlist = player->GetPetMgr().GetPetList();
        if (!petlist.empty())
        {
            for (auto i : petlist)
            {
                auto pet = MapRoleMgr::GetInstance()->FindPet(i);
                if (!pet)continue;
                if (pet->GetPetType() == pet_type_taoist)
                {
                    taoistPetAddTargetFunc(pet, role, false);
                }
            }
        }
    }

    // 给被攻击角色的宠物增加攻击目标
    if (mMaster->GetRoleProp(role_is_stealth) >= 1)return;
    if (role->IsPlayer()) 
    {
        auto player = static_cast<Player*>(role);
        if (!player)return;
        auto& petlist = player->GetPetMgr().GetPetList();
        if (petlist.empty())return;

        for (auto i : petlist)
        {
            auto pet = MapRoleMgr::GetInstance()->FindPet(i);
            if (!pet)continue;
            if (pet->GetPetType() == pet_type_normal)
            {
                auto petAI = pet->GetAIPet();
                if (!petAI)continue;

                if (pet->GetPetType() != pet_type_normal)continue;

                if (petAI->GetActivityStatus() != pet_activity_status_defend)continue;
                if (!petAI->GetTarGuid())
                {
                    petAI->SetTarGuid(mMaster->GetGUID());
                    continue;
                }
                if (petAI->GetTarGuid() == mMaster->GetGUID())continue;


                auto curtar = MapRoleMgr::GetInstance()->FindRole(petAI->GetTarGuid());
                if (!curtar || !curtar->CheckAlive())
                {
                    petAI->SetTarGuid(mMaster->GetGUID());
                    continue;
                }
                auto curdis = pet->DistanceFromRole(curtar);
                auto newdis = pet->DistanceFromRole(mMaster);
                if (newdis < curdis)
                {
                    petAI->SetTarGuid(mMaster->GetGUID());
                }
            }
            else if (pet->GetPetType() == pet_type_taoist)
            {
                taoistPetAddTargetFunc(pet, mMaster, true);
            }
        }
    }
    else if (role->IsPet())
    {
        auto pet = static_cast<Pet*>(role);
        if (!pet)return;
        if (pet->GetPetType() != pet_type_taoist)return;
        if (pet->GetMasterGUID() == mMaster->GetGUID())return;
        taoistPetAddTargetFunc(pet, mMaster, true);
    }
}

void RoleSkill::AddFightInfoWhenAttack(uint32_t skillID, uint64_t tarGuid)
{
    if (!mMaster)return;
    if (mMaster->IsPlayer())
    {
        auto player = static_cast<Player*>(mMaster);
        if (!player)return;
        player->GetFightInfo().AddAttackTargetInfo(tarGuid,skillID);
        player->SetNeedUpdateFlag(fight_info_need_update_flag);

    }
    else if (mMaster->IsMonster())
    {
        auto monster = static_cast<Monster*>(mMaster);
        if (!monster)return;
        monster->GetFightInfo().AddAttackTargetInfo(tarGuid, skillID);
        monster->SetNeedUpdateFlag(fight_info_need_update_flag);
    }
}

void RoleSkill::AddFightInfoWhenBeAttacked(uint32_t skillID, uint64_t ownerGuid, uint64_t actorGuid)
{
    auto role = MapRoleMgr::GetInstance()->FindRole(ownerGuid);
    if (!role)return;
    if (role->IsPlayer())
    {
        auto player = static_cast<Player*>(role);
        if (!player)return;
        player->GetFightInfo().AddBeAttackedInfo(actorGuid, skillID);
        player->SetNeedUpdateFlag(fight_info_need_update_flag);
    }
    else if (role->IsMonster())
    {
        auto monster = static_cast<Monster*>(role);
        if (!monster)return;
        monster->GetFightInfo().AddBeAttackedInfo(actorGuid, skillID);
        monster->SetNeedUpdateFlag(fight_info_need_update_flag);
    }
}

void RoleSkill::AddBackStatus(uint64_t targetGuid)
{
    auto role = MapRoleMgr::GetInstance()->FindRole(targetGuid);
    if (!role)return;
    if (role->IsMonster()) {
        auto monster = static_cast<Monster*>(role);
        if (monster)monster->SetBackStatus();
    }
    else if (role->IsPet()) {
        auto pet = static_cast<Pet*>(role);
        if (pet)pet->SetBackStatus();
    }

}

std::map<uint16_t, string> RoleSkill::DecodeSkillCfg(std::string cfg)
{
    std::map<uint16_t, string> skillCfg;
    if (!cfg.empty())
    {
        Json::Value jsondata;
        Json::Reader reader;
        if (!reader.parse(cfg, jsondata)) return skillCfg;

        Json::Value::Members mem = jsondata.getMemberNames();
        for (auto it = mem.begin(); it != mem.end(); ++it)
        {
            uint16_t nPropType = atoi((*it).c_str());
            if (!::CanModifySkillProp(nPropType)) continue;

            skillCfg[nPropType] = jsondata[*it].asString();
        }
    }
    return skillCfg;
}

std::string RoleSkill::EncodeSkillCfg(const std::map<uint16_t, string>& skillCfg)
{
    Json::Value json_info;
    if (!skillCfg.empty())
    {
        for (auto it = skillCfg.begin(); it != skillCfg.end(); ++it)
        {
            if (!::CanModifySkillProp(it->first)) continue;

            json_info[std::to_string(it->first)] = it->second;
        }
    }
    return json_info.toFastString();
}

void RoleSkill::OnSkillApplyResult(AttackResults &atkResults)
{
    for (auto &result : atkResults) {
        auto *target = MapRoleMgr::GetInstance()->FindRole(result.targetGUID);
        if (!target) continue;
        target->AttackedByRole(result);
    }
}

void RoleSkill::OnSkillApplyResult(AttackResult &atkResult)
{
    auto *target = MapRoleMgr::GetInstance()->FindRole(atkResult.targetGUID);
    if (target) target->AttackedByRole(atkResult);
}

void RoleSkill::ClearTimeridmap()
{
    for (std::map<unsigned int, int>::iterator itr = mTimeridmap.begin(); itr != mTimeridmap.end(); itr++)
    {
        if (itr->second > 0)
        {
            ITimeHelper::GetInstance()->RemoveTimer(itr->first);
        }
    }
    mTimeridmap.clear();
}
void RoleSkill::UpdateTimeridmap()
{
    if (mNeedTimerUpdate)
    {
        mNeedTimerUpdate = false;
        for (std::map<unsigned int, int>::iterator itr = mTimeridmap.begin(); itr != mTimeridmap.end();)
        {
            if (itr->second == 0)
            {
                mTimeridmap.erase(itr++);
            }
            else
            {
                itr++;
            }
        }
    }
}
