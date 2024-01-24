#include "stdafx.h"
#include "Role.h"
#include "Map.h"
#include "ISubject.h"
#include "CNetManager.h"
#include "ITimeHelper.h"
#include "item_table.hpp"
#include "SessionFactory.h"
#include "CustVarMgr.h"


static const DoHandlerNotify HandlerNotify[] = {
    {ROLE_ACTION_ATTR_START,    ROLE_ACTION_ATTR_END,     HandlerNotifyAttr },
    {ROLE_ACTION_STATE_START,   ROLE_ACTION_STATE_END,    HandlerNotifyState },
    {ROLE_ACTION_MOVE_START,    ROLE_ACTION_MOVE_END,     HandlerNotifyMove },
    {ROLE_ACTION_SKILL_START,   ROLE_ACTION_SKILL_END,    HandlerNotifySkill },
    {ROLE_ACTION_BUFF_START,    ROLE_ACTION_BUFF_END,     HandlerNotifyBuff },
    {ROLE_ACTION_PACK_START,    ROLE_ACTION_PACK_END,     HandlerNotifyPack },
    {ROLE_ACTION_AVATAR_START,  ROLE_ACTION_AVATAR_END,   HandlerNotifyAvatar },
    {ROLE_ACTION_RELATION_START,ROLE_ACTION_RELATION_END, HandlerNotifyRelation },
    {ROLE_ACTION_TASK_START,    ROLE_ACTION_TASK_END,     HandlerNotifyTask },
    {ROLE_ACTION_TASK_START,    ROLE_ACTION_TASK_END,     HandlerNotifyTask },
    {ROLE_ACTION_TASK_START,    ROLE_ACTION_TASK_END,     HandlerNotifyTask },
    {ROLE_ACTION_EQUIP_START,   ROLE_ACTION_EQUIP_END,    HandlerNotifyEquip },
    {ROLE_ACTION_TEAM_START,    ROLE_ACTION_TEAM_END,     HandlerNotifyTeam },
    {ROLE_ACTION_VIP_START,     ROLE_ACTION_VIP_END,      HandlerNotifyVip }
};

void HandlerNotifyAttr(uint16_t type)
{
    switch (type) {
    case role_action_attr_role_id:
        LOG_NORMAL("role attr id is update!");
        break;
    case role_action_attr_role_name:
        LOG_NORMAL("role attr name is update!");
        break;
    case role_action_attr_role_alias:
        LOG_NORMAL("role attr alias is update!");
        break;
    case role_action_attr_role_status:
        LOG_NORMAL("role attr status is update!");
        break;
    case role_action_attr_role_posx:
        LOG_NORMAL("role attr posx is update!");
        break;
    case role_action_attr_role_posy:
        LOG_NORMAL("role attr posy is update!");
        break;
    case role_action_attr_role_dir:
        LOG_NORMAL("role attr dir is update!");
        break;
    case role_action_attr_role_property:
        LOG_NORMAL("role attr pro is update!");
        break;
    case role_action_attr_role_property64:
        LOG_NORMAL("role attr pro64 is update!");
        break;
    default:
        break;
    }


}
void HandlerNotifyState(uint16_t)
{
}
void HandlerNotifyMove(uint16_t)
{
}
void HandlerNotifySkill(uint16_t)
{
}
void HandlerNotifyBuff(uint16_t)
{
}
void HandlerNotifyPack(uint16_t)
{
}
void HandlerNotifyAvatar(uint16_t)
{
}
void HandlerNotifyRelation(uint16_t)
{
}
void HandlerNotifyTask(uint16_t)
{
}
void HandlerNotifyEquip(uint16_t)
{
}
void HandlerNotifyTeam(uint16_t)
{
}
void HandlerNotifyVip(uint16_t)
{
}

Role::Role(uint32_t type) : mType(type)
, mCurMap(nullptr)
, mCamp(0)
, mInvalid(false)
, mFightInfo(this)
{
}

Role::~Role()
{
	SAFE_RELEASE(mRoleAttr);
	SAFE_RELEASE(mRoleState);
	SAFE_RELEASE(mRoleMove);
	SAFE_RELEASE(mRoleSkill);
	SAFE_RELEASE(mRoleBuff);
	SAFE_RELEASE(mRolePack);
	SAFE_RELEASE(mRoleAvatar);
	SAFE_RELEASE(mRoleRelation);
	SAFE_RELEASE(mRoleTask);
	SAFE_RELEASE(mRoleTeam);
    SAFE_RELEASE(mRoleVip);
	for (int i = role_action_min; i < role_action_max; i++) {
		mRoleAction[i] = nullptr;
	}
    std::set<uint32_t> tmpTimerId = mTimerId;
	for (auto it = tmpTimerId.begin(); it != tmpTimerId.end();) {
		RemoveLuaTimer(*it);
        ++it;
	}

    switch (GUID_TYPE_PART(mGUID)) {
    case E_OBJ_MONSTER:
    case E_OBJ_NPC:
    case E_OBJ_MAP:
    case E_OBJ_PET:
    case E_OBJ_PLAYER_DOPLGANR:
        CustVarMgr::GetInstance()->DelTempVar(mGUID);
    }

    mGUID = 0;
}

void Role::Update(int32_t delta)
{
    if (mNeedUpdateFlags.test(event_map_need_update_flag)) {
        UpdateEventMap();
        ResetNeedUpdateFlag(event_map_need_update_flag);
    }

    for (int i = role_action_min; i < role_action_max; ++i)
        if (mRoleAction[i]) mRoleAction[i]->Update(delta);

    if (mNeedUpdateFlags.none())
        MapRoleMgr::GetInstance()->RemoveFromNeedUpdateList(this);
}

void Role::ChangeName(std::string name)
{
    Object::SetName(name);
    NotifyAroundPlayers_RoleInfoChange((uint16_t)RoleInfoChangeKey::rick_name, name);
}

void Role::ChangeAlias(std::string name)
{
    Object::SetAlias(name);
    NotifyAroundPlayers_RoleInfoChange((uint16_t)RoleInfoChangeKey::rick_alias, name);
    if (IsPlayer())
    {
        auto player = static_cast<Player*>(this);
        if (player) player->SetCustVar(CUST_VAR_ALIAS_KEY, name, cust_var_type_normal);
    }
}

void Role::Notify(ISubject* sub)
{
    if (nullptr == sub) {
        LOG_ERROR("subject is null,exit!!");
        return;
    }

    auto ntyset = this->GetNtfType();
    auto subtype = sub->GetNtfType();
    if ((ntyset.count(subtype) != 1)) {
        LOG_ERROR("notify type not match,exit!!");
        return;
    }

    //逻辑写在这里
    for (int i = 0; i < sizeof(HandlerNotify) / sizeof(HandlerNotify[0]); ++i) {
        if (subtype > HandlerNotify[i].start && subtype < HandlerNotify[i].end) {
            if (nullptr != HandlerNotify[i].func) {
                HandlerNotify[i].func(subtype);
            }
        }
    }
}

void Role::OnRemoveTrigger()
{
    SetNeedUpdateFlag(event_map_need_update_flag);
}

void Role::AddInvisibleEffect()
{
    auto &attackInfoList = GetFightInfo().GetAttackTargetInfoList();
    for (auto& i : attackInfoList)
    {
        auto role = MapRoleMgr::GetInstance()->FindRole(i.guid);
        if (!role)continue;
        if (role->IsMonster() || role->IsPet())
        {
            auto monster = static_cast<Monster*>(role);
            if (!monster)continue;
            auto &hateValue = monster->GetHateValueMap();
            if (hateValue.empty())continue;
            auto iter = hateValue.find(GetGUID());
            if (iter != hateValue.end())
            {
                hateValue.erase(iter);
            }
        }

    }

    auto &beAttackedInfoList = GetFightInfo().GetBeAttackedTargetInfoList();
    for (auto& i : beAttackedInfoList) {
        auto role = MapRoleMgr::GetInstance()->FindRole(i.guid);
        if (!role)continue;

        if (role->IsMonster()) {
            auto monster = static_cast<Monster*>(role);
            if (nullptr == monster)continue;
            auto AI = monster->GetAIMonster();
            if (nullptr == AI)continue;
            if (AI->GetTarGuid() == GetGUID()) {
                AI->ResetTarGuid();
            }
        }
        else if (role->IsPet()) {
            auto pet = static_cast<Pet*>(role);
            if (nullptr == pet)continue;
            auto AI = pet->GetAIPet();
            if (nullptr == AI)continue;
            if (AI->GetTarGuid() == GetGUID()) {
                AI->ResetTarGuid();
            }
        }
    }

    auto map = GetCurMap();
    if (!map)return;
    auto f = [=](Role* role) {
        if (!role)return;
        if (!role->IsMonster())return;
        auto monster = static_cast<Monster*>(role);
        if (!monster)return;
        auto AI = monster->GetAIMonster();
        if (!AI)return;
        AI->ResetTarGuid();
    };
    map->ApplyFuncToAllRolesInAroundRegions(GetRolePosX(), GetRolePosY(), f);
}

bool Role::JumpMap(Map* tarMap, uint16_t x, uint16_t y)
{
    auto curMap = GetCurMap();
    if (!curMap)return false;
    if (!tarMap->FindJumpablePos(x, y)) return false;

    std::string fromMapGuid = "", toMapGuid = "";
    if (curMap == tarMap)
    {
        fromMapGuid = toMapGuid = GetCurMap()->GetGUIDAsString();
        auto rolemove = GetRoleMove();
        if (rolemove)
        {
            rolemove->StopMove(false);
        }

        auto roleAttr = GetRoleAttr();
        if (roleAttr) roleAttr->SetMoveType(move_type_jump);
        SetRolePos(x, y);
        tarMap->GetMapAoi().RoleEnter(this);
        if (roleAttr->GetMoveType() == move_type_jump) roleAttr->SetMoveType(move_type_walk);

        TRIGGER_EVENT(trigger_post_enter_jump, GetGUIDAsString(), fromMapGuid, toMapGuid, x, y, (uint16_t)jump_map_type::default_type_null);
        return true;
    }


    DATA::Map* fromMapCfg = nullptr;
    DATA::Map* toMapCfg = nullptr;

    if (GetCurMap())
    {
        fromMapCfg = GetCurMap()->GetMapConfig();
        fromMapGuid = GetCurMap()->GetGUIDAsString();
    }

    // 离开地图
    curMap->RoleLeave(this);
    curMap->RemoveMonitorRegionForTrapSkill(GetGUID());
    Role::OnLeaveCurMap();
    // 进入地图
    OnEnterMap(tarMap);
    SetRolePosNoEvent(x, y);
    tarMap->RoleEnter(this);


    if (GetCurMap())
    {
        toMapCfg = GetCurMap()->GetMapConfig();
        toMapGuid = GetCurMap()->GetGUIDAsString();
    }

    if (fromMapCfg && toMapCfg && fromMapCfg != toMapCfg)
    {
        SendDBLogData(log_type_entery_exit_map, LogEnteryExitMap(GetGUID(), fromMapCfg->Id, fromMapCfg->MapType, toMapCfg->Id, toMapCfg->MapType, std::string("进入地图 ") + std::string(toMapCfg->Name)));
    }
    TRIGGER_EVENT(trigger_post_enter_jump, GetGUIDAsString(), fromMapGuid, toMapGuid, x, y, (uint16_t)jump_map_type::default_type_null);
    return true;
}

bool Role::RandJumpMap(uint64_t mapGuid)
{
    // 暂无实现单人副本跳转
    Map* tarMap = MapMgr::GetInstance()->FindMapByGUID(mapGuid);
    if (nullptr == tarMap) {
        LOG_ERROR("Role rand jump by Guid: tar map instance not exist. ");
        return false;
    }

    auto width = tarMap->GetWidth();
    auto height = tarMap->GetHeight();

    uint16_t x, y;
    if (!tarMap->GetRandBlankPointInRange(0, 0, width, height, x, y)) {
        LOG_ERROR("Role rand jump by Guid: GetRandBlankPointInRange failed. ");
        return false;
    }
    JumpMap(tarMap, x, y);
    return true;
}

////////////////////////////// 
// virtual
void Role::StartMove(uint16_t x, uint16_t y)
{
    auto *roleAttr = GetRoleAttr();
    if (!roleAttr) return;

    auto moveType = roleAttr->GetMoveType();

	TRIGGER_EVENT(this, trigger_move, GetGUIDAsString(), x, y, moveType);

    ApplyEventHandlers_StartMove();
}

void Role::EndMove(bool success)
{
    auto *map = GetCurMap();
    if (map) map->OnEndMove(this);
}

void Role::OnRoleExit(Role* role)
{
    if (role != this) return;
    ApplyEventHandlers_RoleExit();
}

void Role::OnRoleDie(uint64_t killerGUID)
{
    ReleaseGrid();
    ApplyEventHandlers_RoleDie();
}

void Role::OnAddBuff(const BUFF_INFO& pBuffInfo, uint16_t nActorSkill)
{
    TRIGGER_EVENT(this, trigger_add_buff, GetGUIDAsString(), pBuffInfo.id, std::to_string(pBuffInfo.host));
    std::list<BUFF_INFO> list;
    list.push_back(pBuffInfo);
    NotifyAroundPlayers_AddBuff(list);    
}

void Role::OnUpdateBuff(const BUFF_INFO& pBuffInfo, uint16_t nActorSkill)
{
    TRIGGER_EVENT(this, trigger_update_buff, GetGUIDAsString(), pBuffInfo.id, std::to_string(pBuffInfo.host));
    std::list<BUFF_INFO> list;
    list.push_back(pBuffInfo);
    NotifyAroundPlayers_AddBuff(list);
}

void Role::OnRemoveBuff(uint16_t nBuffID, uint64_t nActorID)
{
    auto t1 = TimeHelper::GetInstance()->GetTimeStamp();
    TRIGGER_EVENT(this, trigger_remove_buff, GetGUIDAsString(), nBuffID);
    NotifyAroundPlayers_RemoveBuff(nBuffID);
    auto t2 = TimeHelper::GetInstance()->GetTimeStamp();
    if (t2 - t1 >= 200) {
        LOG_WARN("delete buff buffid:%d ,actor:%llu", nBuffID, nActorID);
    }
    SetNeedUpdateFlag(buff_need_update_flag);
}

void Role::ApplySkillOnTarget(uint16_t skillID, uint64_t targetGUID, uint16_t clientSN)
{
    auto *roleSkill = GetRoleSkill();
    if (!roleSkill) return;
    roleSkill->ApplySkillOnTarget(skillID, targetGUID, clientSN);
}

void Role::ApplySkillOnGrid(uint16_t skillID, uint64_t targetGUID, uint16_t x, uint16_t y,
    uint16_t clientSN, uint8_t extraInfo)
{
    auto *roleSkill = GetRoleSkill();
    if (!roleSkill) return;
    roleSkill->ApplySkillOnGrid(skillID, targetGUID, x, y, clientSN, extraInfo);
}

////////////////////////////// 
void Role::Init()
{
    memset(mRoleAction, 0, sizeof(mRoleAction));
    mRoleAction[role_action_attr] = mRoleAttr;
    mRoleAction[role_action_state] = mRoleState;
    mRoleAction[role_action_move] = mRoleMove;
    mRoleAction[role_action_skill] = mRoleSkill;
    mRoleAction[role_action_buff] = mRoleBuff;
    mRoleAction[role_action_pack] = mRolePack;
    mRoleAction[role_action_avatar] = mRoleAvatar;
    mRoleAction[role_action_relation] = mRoleRelation;
    mRoleAction[role_action_task] = mRoleTask;
    mRoleAction[role_action_team] = mRoleTeam;
    mRoleAction[role_action_vip] = mRoleVip;

    for (int i = role_action_min; i < role_action_max; ++i) {
        if (nullptr != mRoleAction[i]) {
            mRoleAction[i]->Init();
        }
    }
}

const std::string & Role::GetCurMapKeyName()
{
    auto *map = GetCurMap();
    if (!map) return EMPTYSTR;
    return map->GetName();
}

bool Role::IsInSameMap(Role *role)
{
    if (!role) return false;

    auto *map = GetCurMap();
    if (!map) return false;

    return map == role->GetCurMap();
}

bool Role::IsInSameLine(Role *role)
{
    if (!role) return false;

    auto x0 = GetRolePosX();
    auto y0 = GetRolePosY();

    auto x1 = role->GetRolePosX();
    auto y1 = role->GetRolePosY();

    return (x0 == x1) ||
           (y0 == y1) ||
           abs(x0 - x1) == abs(y0 - y1);
}

void Role::LeaveMap()
{
    auto *map = GetCurMap();
    if (!map) return;
    map->RoleLeave(this);
}

int32_t Role::SetRoleProp(int32_t prop, int32_t value)
{
    if (nullptr == this->GetRoleAttr()) {
        return 0;
    }
    return this->GetRoleAttr()->SetRoleProp(prop, value);
}

void  Role::SetRoleProp64(int32_t prop, int64_t value, const log_params& lp)
{
    if (nullptr == this->GetRoleAttr()) {
        return;
    }
    this->GetRoleAttr()->SetProp64(prop, value, lp);
}

int32_t Role::GetRoleProp(int32_t prop)
{
    if (nullptr == this->GetRoleAttr()) {
        return 0;
    }
    return this->GetRoleAttr()->GetRoleProp(prop);
}

int64_t Role::GetRoleProp64(int32_t prop)
{
    if (nullptr == this->GetRoleAttr()) {
        return 0;
    }
    return this->GetRoleAttr()->GetProp64(prop);
}

int32_t Role::AddRoleProp(int32_t prop, int32_t value)
{
    if (nullptr == this->GetRoleAttr()) {
        return 0;
    }
    return this->GetRoleAttr()->AddRoleProp(prop, value);
}

void Role::AddRoleProp64(int32_t prop, int64_t value, const log_params& lp)
{
    if (nullptr == this->GetRoleAttr()) {
        return;
    }
    this->GetRoleAttr()->AddProp64(prop, value, lp);
}

bool Role::CheckProp64Amount(int32_t prop, const std::string& needNum)
{
    int64_t nPropVal = GetRoleProp64(prop);
    int64_t nNeedNum = std::stoll(needNum);
    return nPropVal >= nNeedNum;
}

void Role::SetUpGradeExp(uint64_t exp)
{
    if (nullptr == this->GetRoleAttr()) {
        return;
    }
    this->GetRoleAttr()->SetUpGradeExp(exp);
}

uint64_t Role::GetUpGradeExp(void)
{
    if (nullptr == this->GetRoleAttr()) {
        return 0;
    }
    return this->GetRoleAttr()->GetUpGradeExp();
}

void Role::SetRolePos(uint16_t x, uint16_t y)
{
    if (nullptr != this->GetRoleAttr()) {
        this->GetRoleAttr()->SetRolePos(x, y);
    }
}

void Role::SetRolePosNoEvent(uint16_t x, uint16_t y)
{
    if (nullptr != this->GetRoleAttr()) {
        this->GetRoleAttr()->SetRolePos(x, y, false);
    }
}

void Role::SetRolePosNoTakeGrid(uint16_t x, uint16_t y)
{
    if (nullptr != this->GetRoleAttr()) {
        this->GetRoleAttr()->SetRolePos(x, y, true,false);
    }
}

uint16_t Role::GetRolePosX() {
    if (nullptr == this->GetRoleAttr()) {
        return 0;
    }
    return this->GetRoleAttr()->GetRolePosX();
}

uint16_t Role::GetRolePosY() {
    if (nullptr == this->GetRoleAttr()) {
        return 0;
    }
    return this->GetRoleAttr()->GetRolePosY();
}

void Role::SetRoleDir(uint8_t dir)
{
    if (nullptr == this->GetRoleAttr()) {
        return;
    }
    if (GetRoleProp(role_can_turn) <= 0) {
        return;
    }
    GetRoleAttr()->SetRoleDir(dir);
}

uint8_t Role::GetRoleDir()
{
    if (nullptr == this->GetRoleAttr()) {
        return dir_max;
    }
    return GetRoleAttr()->GetRoleDir();
}

bool Role::IsInSafeRegion()
{
    auto *map = GetCurMap();
    if (!map) return false;

    auto x = GetRolePosX();
    auto y = GetRolePosY();

    return map->IsSafeRegion(x, y);
}

////////////////////////////// 
bool Role::CheckAlive()
{
    if (mRoleState) {
        return mRoleState->CheckAlive();
    }
    return false;
}

bool Role::CheckCross()
{
    auto roleType = GetType();

    auto map = GetCurMap();
    if (map == nullptr)
        return false;

    return map->CheckCross(roleType);
}

uint32_t Role::AddLuaTimer(uint32_t interval, bool loop, const std::string& call_back)
{
    auto id = ITimeHelper::GetInstance()->AddTimer(interval, loop, [=](const TimerData &timer) {
        if (!call_back.empty()) {
            LuaBindCallVoid(call_back, timer.id);
        }
        if (!loop)
        {
            mTimerId.erase(timer.id);
        }
    });

    mTimerId.insert(id);
    return id;
}

uint32_t Role::AddLuaTimerEx(uint32_t interval, bool loop, CLuaObject call_back)
{
    auto id = ITimeHelper::GetInstance()->AddTimer(interval, loop, [=](const TimerData &timer) {
        if (call_back.is_valid()) {
            LuaBindCallExVoid(call_back, timer.id);
        }
        if (!loop)
        {
            mTimerId.erase(timer.id);
        }
    });

    mTimerId.insert(id);
    return id;
}

void Role::RemoveLuaTimer(uint32_t id)
{
    ITimeHelper::GetInstance()->RemoveTimer(id);
    mTimerId.erase(id);
}

bool Role::AddBuffByRole(uint16_t nBuffID, Role* pActor, uint16_t nSkillID, std::string attrStr, uint32_t time)
{
    auto* roleBuff = GetRoleBuff();
    if (!roleBuff) return false;

    return roleBuff->AddBuffByRole(nBuffID, pActor, nSkillID, attrStr, time);
}

bool Role::RemoveBuff(uint16_t nBuffID)
{
    auto* roleBuff = GetRoleBuff();
    if (!roleBuff) return false;

    return roleBuff->RemoveBuff(nBuffID);
}

bool Role::RemoveBuffWithActorID(uint16_t nBuffID, std::string sActorID)
{
    auto* roleBuff = GetRoleBuff();
    if (!roleBuff) return false;

    return roleBuff->RemoveBuff(nBuffID, std::stoull(sActorID));
}

void Role::RemoveBuffWhenDie()
{
    auto* roleBuff = GetRoleBuff();
    if (!roleBuff) return;

    roleBuff->OnRoleDead();
}

void Role::RemoveBuffWhenMove()
{
    auto* roleBuff = GetRoleBuff();
    if (!roleBuff) return;

    roleBuff->OnRoleMove();
}

bool Role::BuffExist(uint16_t nBuffID)
{
    auto* roleBuff = GetRoleBuff();
    if (!roleBuff) return false;

    return roleBuff->BuffExist(nBuffID);
}

bool Role::BuffExistByGroupID(uint16_t buffGroupID)
{
    auto* roleBuff = GetRoleBuff();
    if (!roleBuff) return false;

    return roleBuff->BuffExistByGroupID(buffGroupID);
}

std::vector<uint16_t> Role::GetValidBuffIDList()
{
    auto *roleBuff = GetRoleBuff();
    if (!roleBuff) return {};
    return roleBuff->GetValidBuffIDList();
}

int64_t Role::GetBuffLeftTime(uint16_t buffID)
{
    auto* roleBuff = GetRoleBuff();
    if (!roleBuff) return -1;

    return roleBuff->GetBuffLeftTime(buffID);
}

uint16_t Role::GetBuffStack(uint16_t buffID)
{
    auto* roleBuff = GetRoleBuff();
    if (!roleBuff) return 0;

    return roleBuff->GetBuffStack(buffID);
}

void Role::UpdateBuffStack(uint16_t buffID, int16_t diff)
{
    auto* roleBuff = GetRoleBuff();
    if (!roleBuff) return;

    roleBuff->UpdateBuffStack(buffID, diff);
}

std::string Role::GetBuffActorGuid(uint16_t buffID)
{
    auto* roleBuff = GetRoleBuff();
    if (!roleBuff) return EMPTYSTR;

    return roleBuff->GetBuffActorGuid(buffID);
}

const std::string & Role::GetBuffActorName(const std::string& actorGuid, uint16_t buffID)
{
    auto* roleBuff = GetRoleBuff();
    if (!roleBuff) return EMPTYSTR;

    return roleBuff->GetBuffActorName(actorGuid, buffID);
}

uint8_t Role::GetBuffActorJob(const std::string& actorGuid, uint16_t buffID)
{
    auto* roleBuff = GetRoleBuff();
    if (!roleBuff) return 0;

    return roleBuff->GetBuffActorJob(actorGuid, buffID);
}

uint32_t Role::GetBuffActorLevel(const std::string& actorGuid, uint16_t buffID)
{
    auto* roleBuff = GetRoleBuff();
    if (!roleBuff) return 0;

    return roleBuff->GetBuffActorLevel(actorGuid, buffID);
}

uint16_t Role::GetBuffActorSkill(const std::string& actorGuid, uint16_t buffID)
{
    auto* roleBuff = GetRoleBuff();
    if (!roleBuff) return 0;

    return roleBuff->GetBuffActorSkill(actorGuid, buffID);
}
/////////////////////////
void Role::TakeGrid()
{
    auto attr = GetRoleAttr();
    auto map = GetCurMap();
    if (nullptr != attr && nullptr != map) {
        uint16_t x, y;
        attr->GetRolePos(x, y);
        if (IsPlayer() || IsPlayerDoplganr())
        {
            map->GetMapGrid().SetDPForbid(x, y);
        }
        else if (IsMonster() || IsPet())
        {
            map->GetMapGrid().SetDMForbid(x, y);
        }
        else if (IsNpc())
        {
            map->GetMapGrid().SetNPCForbid(x, y);
        }
        else if (IsStallDummy())
        {
            map->GetMapGrid().SetSDForbid(x, y);
        }
    }
}

void Role::ReleaseGrid()
{
    auto attr = GetRoleAttr();
    auto map = GetCurMap();
    if (nullptr != attr && nullptr != map) {

        std::array<uint16_t, role_type_cnt> num{ 0 };
        uint16_t x, y;
        attr->GetRolePos(x, y);
        map->GetMapAoi().IsHaveRoleInPoint(role_type_none, x, y, num);
        
        if ((IsPlayer() || IsPlayerDoplganr()) && (num.at(role_type_player) + num.at(role_type_player_doplganr)) <= 1)
        {
            map->GetMapGrid().RemoveDPForbid(x, y);
        }
        else if ((IsMonster() || IsPet()) && ((num.at(role_type_monster) + num.at(role_type_pet)) <= 1))
        {
            map->GetMapGrid().RemoveDMForbid(x, y);
        }
        else if (IsNpc() && num.at(role_type_npc) <= 1)
        {
            map->GetMapGrid().RemoveNPCForbid(x, y);
        }
        else if (IsStallDummy() && num.at(role_type_stall_dummy) <= 1)
        {
            map->GetMapGrid().RemoveSDForbid(x, y);
        }
    }
}

uint16_t Role::DistanceFromRole(Role* role)
{
    if (!role) return UINT16_MAX;

    if (role->GetCurMap() != GetCurMap()) return UINT16_MAX;

    auto x0 = GetRolePosX();
    auto y0 = GetRolePosY();

    auto x1 = role->GetRolePosX();
    auto y1 = role->GetRolePosY();

    return Utility::CalcLongerDistance(x0, y0, x1, y1);
}

uint16_t Role::DistanceFromPos(uint16_t x, uint16_t y)
{
    auto x0 = GetRolePosX();
    auto y0 = GetRolePosY();

    return Utility::CalcLongerDistance(x0, y0, x, y);
}

Point Role::PosRelativeToCurRole(uint16_t x, uint16_t y)
{
    auto x0 = GetRolePosX();
    auto y0 = GetRolePosY();

    int dx = x - x0;
    int dy = y - y0;

    return Point(static_cast<int16_t>(dx), static_cast<int16_t>(dy));
}

void Role::UpdateHPMP(int32_t hpAmount, int32_t mpAmount, uint8_t type, bool notify)
{
    hpAmount = AddRoleProp(role_hp, hpAmount);
    auto totalHP = GetRoleProp(role_hp);
    mpAmount = AddRoleProp(role_mp, mpAmount);
    auto totalMP = GetRoleProp(role_mp);

    if (hpAmount == 0 && mpAmount == 0) return;

    if (notify) NotifyAroundPlayers_UpdateHPMP(hpAmount, totalHP, mpAmount, totalMP, type);
}

uint16_t Role::MoveTo(uint16_t x, uint16_t y, uint8_t type)
{
    if (nullptr == this->GetRoleMove()) return error_nullptr;

    return this->GetRoleMove()->MoveTo(x, y, type);
}

void Role::AttackedByRole(AttackResult& res)
{
    if (!CheckAlive()) return;

    res.decreaseHP = AddRoleProp(role_hp, -res.decreaseHP);
    res.decreaseMP = AddRoleProp(role_mp, -res.decreaseMP);
    res.remainHP = GetRoleProp(role_hp);
    res.remainMP = GetRoleProp(role_mp);

    OnRoleBeAttacked(res.actorGUID);
    NotifyAroundPlayers_Attacked(res);

    if (res.remainHP > 0) {
        TRIGGER_EVENT(trigger_role_post_harm, std::to_string(res.actorGUID), std::to_string(res.targetGUID),
                      res.skillId, -res.decreaseHP, res.type);
    }
    else {
        bool isDead = true;
        TRIGGER_EVENT_RET(isDead, this, trigger_pre_die, std::to_string(res.targetGUID), std::to_string(res.actorGUID));
        if (!isDead) {
            if (mRoleState && mRoleState->GetState() == role_state_die)
                mRoleState->SetState(role_state_idle);
            res.remainHP = GetRoleProp(role_hp);
            return;
        }

        if (mRoleState) mRoleState->SetState(role_state_die);

        auto *map = GetCurMap();
        if (map) {
            auto x = GetRolePosX();
            auto y = GetRolePosY();
            map->ApplyFuncToAllPlayersInAroundRegions(x, y, [&](Role* pRole) { NotifyPlayer_RoleDie(pRole, res); });
        }

        MapRoleMgr::GetInstance()->DelaySendRoleDisappearNtfToAroundPlayers(res.targetGUID);
        OnRoleDie(res.actorGUID);
        RemoveBuffWhenDie();
        TRIGGER_EVENT(this, trigger_post_die, std::to_string(res.targetGUID), std::to_string(res.actorGUID));
    }
}

void Role::NotifyAroundPlayers_AddBuff()
{
    auto roleBuff = GetRoleBuff();
    if (!roleBuff) return;

    std::list<BUFF_INFO> list;
    roleBuff->GetInUseBuffInfo(list);
    NotifyAroundPlayers_AddBuff(list);
}

void Role::NotifyAroundPlayers_AddBuff(const std::list<BUFF_INFO>& list)
{
    if (list.empty()) return;
    auto map = GetCurMap();
    if (!map) return;
    auto clsessidsMap = map->GetAroundPlayerCLSessionID(this);

    ProtoMS_BuffAddAck ack;
    ack.role_guid = GetGUID();
    auto iter = list.begin();
    for (; iter != list.end();)
    {
        ack.info[ack.num] = (*iter);
        ack.num++; iter++;
        if (ack.num == _countof(ack.info) || iter == list.end())
        {
            SendDataBySessionID(clsessidsMap, ack);
            ack.num = 0;
        }
    }
}

void Role::NotifyOnePlayer_AddBuff(Role *pRoleToNotify, const uint64_t &nRoleIDSrc, const std::list<BUFF_INFO>& list)
{
    if (list.empty()) return;
    if (!pRoleToNotify || !pRoleToNotify->IsPlayer()) return;
    auto pPlayer = static_cast<Player *>(pRoleToNotify);

    ProtoMS_BuffAddAck ack;
    ack.nClientSessionID = pPlayer->GetClSessionID();
    ack.role_guid = nRoleIDSrc;
    auto iter = list.begin();
    for (; iter != list.end();)
    {
        ack.info[ack.num] = (*iter);
        ack.num++; iter++;
        if (ack.num == _countof(ack.info) || iter == list.end())
        {
            SendDataBySessionID(pPlayer->GetGsSessionID(), ack);
            ack.num = 0;
        }
    }
}

void Role::NotifyOnePlayer_AddBuff(Role *pRoleToNotify, Role *pRoleBuffSrc)
{
    if (!pRoleToNotify || !pRoleBuffSrc) return;
    auto roleBuff = pRoleBuffSrc->GetRoleBuff();
    if (!roleBuff) return;

    std::list<BUFF_INFO> list;
    roleBuff->GetInUseBuffInfo(list);

    NotifyOnePlayer_AddBuff(pRoleToNotify, pRoleBuffSrc->GetGUID(), list);
}

void Role::NotifyAroundPlayers_RemoveBuff(uint16_t nBuffID)
{
    auto map = GetCurMap();
    if (!map) return;
    auto clsessidsMap = map->GetAroundPlayerCLSessionID(this);
    ProtoMS_BuffDestroyAck ack;
    ack.role_guid = GetGUID();
    ack.id = nBuffID;
    
    SendDataBySessionID(clsessidsMap, ack);
}

void Role::NotifyAroundPlayers_Attacked(AttackResult& res)
{
    auto pMap = GetCurMap();
    if (!pMap) return;

    auto clsessidsMap = pMap->GetAroundPlayerCLSessionID(this);

    if (res.type == skill_harm_type_miss ||
        res.type == skill_harm_type_immunity) {

        ProtoMS_MissNtf data;
        data.actor = res.actorGUID;
        data.target = res.targetGUID;
        data.skill_id = res.skillId;
        data.type = (res.type == skill_harm_type_miss) ? miss_ntf_type_miss : miss_ntf_type_immunity;

        SendDataBySessionID(clsessidsMap, data, true);
    }
    else {
        ProtoMS_AttrShowNtfEx2 attrShowNtf;
        attrShowNtf.actor = res.actorGUID;
        attrShowNtf.target = res.targetGUID;
        attrShowNtf.skill_id = res.skillId;
        attrShowNtf.type = res.type;
        attrShowNtf.actor_hp_ref = 0;                   // 血量减少
        attrShowNtf.actor_mp_ref = 0;                   // 蓝量减少
        attrShowNtf.target_hp_ref = res.decreaseHP;     // 目标血量减少
        attrShowNtf.target_hp = res.remainHP;           // 目标剩余血量
        attrShowNtf.target_mp_ref = res.decreaseMP;     // 目标蓝量减少
        attrShowNtf.target_mp = res.remainMP;           // 目标剩余蓝量
        attrShowNtf.reserve_size = 0;

        SendDataBySessionID(clsessidsMap, attrShowNtf, true);
    }
}

void Role::NotifyPlayer_RoleDie(Role *pRoleToNotify, const AttackResult& res)
{
    if (!pRoleToNotify || !pRoleToNotify->IsPlayer()) return;
    auto pPlayer = static_cast<Player *>(pRoleToNotify);
    if (!pPlayer->IsOnline()) return;

    auto role = MapRoleMgr::GetInstance()->FindRole(res.actorGUID);
    //if (!role) return;

    ProtoMS_ObjDieNtf objDieNtf;
    objDieNtf.die_guid = res.targetGUID;
    objDieNtf.kill_guid = res.actorGUID;
    strcpy_s(objDieNtf.kill_name, _countof(objDieNtf.kill_name), res.actorName.c_str());
    if (role && (role->IsMonster() || role->IsPet()))
    {
        Monster* monster = static_cast<Monster*>(role);
        if (monster && monster->IsSummonMonster())
        {
            sprintf_s(objDieNtf.kill_name, _countof(objDieNtf.kill_name), "%s(%s)",
                monster->GetName().c_str(), monster->GetMasterName().c_str());
        }
    }

    objDieNtf.clientSessionID = pPlayer->GetClSessionID();

    SendDataBySessionID(pPlayer->GetGsSessionID(), objDieNtf);
}

void Role::NotifyAroundPlayers_UpdateHPMP(int32_t hpAmount, int32_t hpTotal, int32_t mpAmount, int32_t mpTotal, uint8_t type)
{
    auto* map = GetCurMap();
    if (!map) return;

    ProtoMS_AttrShowNtfEx2 data;
    data.target = GetGUID();
    data.target_hp_ref = hpAmount;
    data.target_hp = hpTotal;
    data.target_mp_ref = mpAmount;
    data.target_mp = mpTotal;
    data.type = type;

    auto clsessidsMap = map->GetAroundPlayerCLSessionID(this);
    SendDataBySessionID(clsessidsMap, data, true);
}

void Role::NotifyAroundPlayers_RoleInfoChange(uint16_t type, const string& value)
{
    auto* map = GetCurMap();
    if (!map) return;

    MSG_BUFFER_DATA(ProtoMS_RoleInfoChangeNtf, ntf);
    ntf.role_guid = GetGUID();
    ntf.num = 1;
    ntf.custom << type << value;

    auto f = [&](Role* role) {
        if (!role || !role->IsPlayer()) return;
        auto* player = static_cast<Player*>(role);
        if (!player) return;

        ntf.sessid = player->GetClSessionID();
        SendDataBySessionID(player->GetGsSessionID(), ntf);
    };
    map->ApplyFuncToAllPlayersInAroundRegions(GetRolePosX(), GetRolePosY(), f);
}

void Role::NotifyAroundPlayers_SpellNtf(const AttackResults &atkResults, uint16_t skillID, uint16_t x, uint16_t y, uint8_t extraInfo)
{
    auto *map = GetCurMap();
    if (!map) return;

    auto clsessidsMap = map->GetAroundPlayerCLSessionID(this);

    ProtoMS_SpellNtf data;
    data.actor = GetGUID();
    data.id = skillID;
    data.target_x = x;
    data.target_y = y;
    data.extra = extraInfo;
    data.num = 0;

    if (atkResults.empty()) {
        SendDataBySessionID(clsessidsMap, data, true);
        return;
    }

    auto &n = data.num;
    for (const auto &result : atkResults) {
        data.targets[n++] = result.targetGUID;
        if (n == _countof(data.targets)) {
            //SendDataBySessionID(clsessidsMap, data, true);
            //n = 0;
            break;
        }
    }

    if (n) SendDataBySessionID(clsessidsMap, data, true);
}

void Role::NotifyAroundPlayers_SpellNtf(uint64_t targetGUID, uint16_t skillID, uint16_t x, uint16_t y, uint8_t extraInfo)
{
    auto *map = GetCurMap();
    if (!map) return;

    ProtoMS_SpellNtf data;
    data.actor = GetGUID();
    data.id = skillID;
    data.target_x = x;
    data.target_y = y;
    data.extra = extraInfo;
    data.num = 1;
    data.targets[0] = targetGUID;

    auto clsessidsMap = map->GetAroundPlayerCLSessionID(this);
    SendDataBySessionID(clsessidsMap, data, true);
}

std::vector<RoleItem *> Role::GetAllEquipments()
{
    std::vector<RoleItem *> items;
    auto *rolePack = GetRolePack();
    if (!rolePack) return items;
    items = rolePack->GetAllEquipments();
    return items;
}

RoleAction* Role::GetAction(int actionType)
{
    if ((actionType >= role_action_min) && (actionType < role_action_max)) {
        return mRoleAction[actionType];
    }
    return nullptr;
}

void Role::OnGetBuffAck(const BUFF_INFO_DB* pBuffInfo, uint16_t num)
{
    for (uint16_t i = 0; i < num; ++i)
    {
        mRoleBuff->AddBuffFromCache(pBuffInfo + i);
    }
}

void Role::SendUpdateTopList()
{
    ProtoMS_UpdateTopListAck ack;
    ack.role = GetGUID();
    strcpy_s(ack.nowRole.player_name, _countof(ack.nowRole.player_name), GetName().c_str());
    ack.nowRole.gender = GetRoleProp(role_gender);
    ack.nowRole.level = GetRoleProp(role_level);
    ack.nowRole.job = GetRoleProp(role_job);
    SendDataBySessionType(SESSION_TYPE_MS2CS, ack);
}
void Role::UpgradeUpdateRoleProp(DATA::Role* preCfg, DATA::Role* curCfg)
{
    if (!preCfg || !curCfg) return;

    AddRoleProp(role_base_max_hp, curCfg->HP - preCfg->HP);
    AddRoleProp(role_base_max_mp, curCfg->MP - preCfg->MP);
    AddRoleProp(role_max_weight, curCfg->Weight - preCfg->Weight);
    AddRoleProp(role_max_equip_weight, curCfg->EquipWeight - preCfg->EquipWeight);
    AddRoleProp(role_max_brawn, curCfg->Brawn - preCfg->Brawn);
    AddRoleProp(role_base_max_phy_def, curCfg->MaxPhyDef - preCfg->MaxPhyDef);
    AddRoleProp(role_base_min_phy_def, curCfg->MinPhyDef - preCfg->MinPhyDef);
    AddRoleProp(role_base_max_mag_def, curCfg->MaxMagDef - preCfg->MaxMagDef);
    AddRoleProp(role_base_min_mag_def, curCfg->MinMagDef - preCfg->MinMagDef);
    AddRoleProp(role_base_max_phy_atk, curCfg->MaxPhyAtk - preCfg->MaxPhyAtk);
    AddRoleProp(role_base_min_phy_atk, curCfg->MinPhyAtk - preCfg->MinPhyAtk);
    AddRoleProp(role_base_max_mag_atk, curCfg->MaxMagAtk - preCfg->MaxMagAtk);
    AddRoleProp(role_base_min_mag_atk, curCfg->MinMagAtk - preCfg->MinMagAtk);
    AddRoleProp(role_base_max_tao_atk, curCfg->MaxTaoAtk - preCfg->MaxTaoAtk);
    AddRoleProp(role_base_min_tao_atk, curCfg->MinTaoAtk - preCfg->MinTaoAtk);
    AddRoleProp(role_base_attack_speed, curCfg->AttackSpeed - preCfg->AttackSpeed);
    AddRoleProp(role_base_casting_speed, curCfg->CastingSpeed - preCfg->CastingSpeed);
    AddRoleProp(role_base_move_speed, curCfg->MoveSpeed - preCfg->MoveSpeed);
    AddRoleProp(role_hit, curCfg->Hit - preCfg->Hit);
    AddRoleProp(role_miss, curCfg->Miss - preCfg->Miss);
    AddRoleProp(role_mag_miss, curCfg->MagMiss - preCfg->MagMiss);
    //AddRoleProp(role_poison_miss, 0);
    //AddRoleProp(role_palsy_miss, 0);
    AddRoleProp(role_burst, curCfg->Burst - preCfg->Burst);
    //AddRoleProp(role_burst_harm, 0);
    //AddRoleProp(role_burst_def, 0);
    //AddRoleProp(role_burst_harm_def, 0);
    AddRoleProp(role_base_hp_rec, curCfg->HPRec - preCfg->HPRec);
    AddRoleProp(role_base_mp_rec, curCfg->MPRec - preCfg->MPRec);
    //AddRoleProp(role_poison_rec, curCfg->PoisonRec - preCfg->PoisonRec);
    //AddRoleProp(role_palsy_rec, curCfg->PalsyRec - preCfg->PalsyRec);
    //AddRoleProp(role_drug_rec, 0);

    // 特殊属性
    auto iter = preCfg->SpecialAttr.begin();
    for (; iter != preCfg->SpecialAttr.end(); ++iter)
    {
        AddRoleProp(iter->first, -1 * iter->second);
    }
    iter = curCfg->SpecialAttr.begin();
    for (; iter != curCfg->SpecialAttr.end(); ++iter)
    {
        AddRoleProp(iter->first, iter->second);
    }
}

void Role::InitRoleProp(DATA::Role* pRoleConfig)
{
    if (!pRoleConfig) return;

    SetRoleProp(role_base_max_hp, pRoleConfig->HP);
    SetRoleProp(role_base_max_mp, pRoleConfig->MP);
    SetRoleProp(role_max_weight, pRoleConfig->Weight);
    SetRoleProp(role_max_equip_weight, pRoleConfig->EquipWeight);
    SetRoleProp(role_max_brawn, pRoleConfig->Brawn);
    SetRoleProp(role_base_max_phy_def, pRoleConfig->MaxPhyDef);
    SetRoleProp(role_base_min_phy_def, pRoleConfig->MinPhyDef);
    SetRoleProp(role_base_max_mag_def, pRoleConfig->MaxMagDef);
    SetRoleProp(role_base_min_mag_def, pRoleConfig->MinMagDef);
    SetRoleProp(role_base_max_phy_atk, pRoleConfig->MaxPhyAtk);
    SetRoleProp(role_base_min_phy_atk, pRoleConfig->MinPhyAtk);
    SetRoleProp(role_base_max_mag_atk, pRoleConfig->MaxMagAtk);
    SetRoleProp(role_base_min_mag_atk, pRoleConfig->MinMagAtk);
    SetRoleProp(role_base_max_tao_atk, pRoleConfig->MaxTaoAtk);
    SetRoleProp(role_base_min_tao_atk, pRoleConfig->MinTaoAtk);
    SetRoleProp(role_base_attack_speed, pRoleConfig->AttackSpeed);
    SetRoleProp(role_base_casting_speed, pRoleConfig->CastingSpeed);
    SetRoleProp(role_base_move_speed, pRoleConfig->MoveSpeed);
    SetRoleProp(role_hit, pRoleConfig->Hit);
    SetRoleProp(role_miss, pRoleConfig->Miss);
    SetRoleProp(role_mag_miss, pRoleConfig->MagMiss);
    //SetRoleProp(role_poison_miss, 0);
    //SetRoleProp(role_palsy_miss, 0);
    SetRoleProp(role_burst, pRoleConfig->Burst);
    //SetRoleProp(role_burst_harm, 0);
    //SetRoleProp(role_burst_def, 0);
    //SetRoleProp(role_burst_harm_def, 0);
    SetRoleProp(role_base_hp_rec, pRoleConfig->HPRec);
    SetRoleProp(role_base_mp_rec, pRoleConfig->MPRec);
//    SetRoleProp(role_poison_rec, pRoleConfig->PoisonRec);
//    SetRoleProp(role_palsy_rec, pRoleConfig->PalsyRec);
    //SetRoleProp(role_drug_rec, 0);

    // 特殊属性,用Add防止属性有配置和字段重了的导致被覆盖
    auto iter = pRoleConfig->SpecialAttr.begin();
    for (; iter != pRoleConfig->SpecialAttr.end(); ++iter)
    {
        AddRoleProp(iter->first, iter->second);
    }
}

void Role::InitRoleProp(DATA::Npc* cfg)
{
    if (!cfg) return;

    SetRoleProp(role_can_turn, 1);
}

void Role::InitRoleProp(DATA::Monster* pConfig)
{
    if (!pConfig) return;

    SetRoleProp(role_base_max_hp, pConfig->HP);
    SetRoleProp(role_base_max_mp, pConfig->MP);
    //SetRoleProp(role_max_weight, 0);
    //SetRoleProp(role_max_equip_weight, 0);
    //SetRoleProp(role_max_brawn, 0);
    SetRoleProp(role_base_max_phy_def, pConfig->MaxPhyDef);
    SetRoleProp(role_base_min_phy_def, pConfig->MinPhyDef);
    SetRoleProp(role_base_max_mag_def, pConfig->MaxMagDef);
    SetRoleProp(role_base_min_mag_def, pConfig->MinMagDef);
    SetRoleProp(role_base_max_phy_atk, pConfig->MaxPhyAtk);
    SetRoleProp(role_base_min_phy_atk, pConfig->MinPhyAtk);
    SetRoleProp(role_base_max_mag_atk, pConfig->MaxMagAtk);
    SetRoleProp(role_base_min_mag_atk, pConfig->MinMagAtk);
    //SetRoleProp(role_base_max_tao_atk, 0);
    //SetRoleProp(role_base_min_tao_atk, 0);
    SetRoleProp(role_base_attack_speed, pConfig->AttackSpeed);
    //SetRoleProp(role_base_casting_speed, 0);
    SetRoleProp(role_base_move_speed, pConfig->MoveSpeed);
    SetRoleProp(role_hit, pConfig->Hit);
    SetRoleProp(role_miss, pConfig->Miss);
    SetRoleProp(role_can_phy_atk, 1);
    SetRoleProp(role_can_mag_atk, 1);
    SetRoleProp(role_can_use_skill, 1);
    //SetRoleProp(role_mag_miss, 0);
    //SetRoleProp(role_poison_miss, 0);
    //SetRoleProp(role_palsy_miss, 0);
    //SetRoleProp(role_burst, 0);
    //SetRoleProp(role_burst_harm, 0);
    //SetRoleProp(role_burst_def, 0);
    //SetRoleProp(role_burst_harm_def, 0);
    //SetRoleProp(role_base_hp_rec, 0);
    //SetRoleProp(role_base_mp_rec, 0);
    //SetRoleProp(role_poison_rec, 0);
    //SetRoleProp(role_palsy_rec, 0);
    //SetRoleProp(role_drug_rec, 0);

    SetRoleProp(role_level, pConfig->Level);
    SetRoleProp(role_hp, pConfig->HP);
    SetRoleProp(role_mp, pConfig->MP);
    SetRoleProp(role_atk_mode, pConfig->AtkType);

    SetRoleProp(role_can_turn, 1);
    if (pConfig->MovRange > 1 && pConfig->MoveSpeed > 0) {
        SetRoleProp(role_can_walk, 1);
        SetRoleProp(role_can_run, 1);
    }

    // 特殊属性
    auto iter = pConfig->SpecialAttr.begin();
    for (; iter != pConfig->SpecialAttr.end(); ++iter)
    {
        SetRoleProp(iter->first, iter->second);
    }
}

uint32_t Role::AddEventHandlerToMap(EventHandlerMap &handlerMap, EventHandler handler)
{
    auto handlerID = Tools::GenerateUINT32();
    handlerMap.emplace(handlerID, std::move(handler));
    return handlerID;
}

void Role::RemoveEventHandlerFromMap(EventHandlerMap &handlerMap, uint32_t handlerID)
{
    auto it = handlerMap.find(handlerID);
    if (it == handlerMap.end()) return;
    it->second = nullptr;   // 不能直接删除，假如在回调中调用会导致迭代器失效
}

void Role::ApplyEventHandlersInMap(EventHandlerMap &handlerMap)
{
    SAFE_BEGIN;

    for (auto it = handlerMap.begin(); it != handlerMap.end(); ) {
        if (it->second) {
            it->second();
            ++it;
        }
        else {
            it = handlerMap.erase(it);
        }
    }

    SAFE_END;
}

uint32_t Role::AddEventHandler_RoleExit(EventHandler hander)
{
    return AddEventHandlerToMap(mHandlersRoleExit, std::move(hander));
}

void Role::RemoveEventHandler_RoleExit(uint32_t handlerID)
{
    RemoveEventHandlerFromMap(mHandlersRoleExit, handlerID);
}

void Role::ApplyEventHandlers_RoleExit()
{
    ApplyEventHandlersInMap(mHandlersRoleExit);
}

uint32_t Role::AddEventHandler_RoleDie(EventHandler hander)
{
    return AddEventHandlerToMap(mHandlersRoleDie, std::move(hander));
}

void Role::RemoveEventHandler_RoleDie(uint32_t handlerID)
{
    RemoveEventHandlerFromMap(mHandlersRoleDie, handlerID);
}

void Role::ApplyEventHandlers_RoleDie()
{
    ApplyEventHandlersInMap(mHandlersRoleDie);
}

uint32_t Role::AddEventHandler_StartMove(EventHandler hander)
{
    return AddEventHandlerToMap(mHandlersStartMove, std::move(hander));
}

void Role::RemoveEventHandler_StartMove(uint32_t handlerID)
{
    RemoveEventHandlerFromMap(mHandlersStartMove, handlerID);
}

void Role::ApplyEventHandlers_StartMove()
{
    ApplyEventHandlersInMap(mHandlersStartMove);
}

uint32_t Role::AddEventHandler_RoleOnline(EventHandler hander)
{
    return AddEventHandlerToMap(mHandlersRoleOnline, std::move(hander));
}

void Role::RemoveEventHandler_RoleOnline(uint32_t handlerID)
{
    RemoveEventHandlerFromMap(mHandlersRoleOnline, handlerID);
}

void Role::ApplyEventHandlers_RoleOnline()
{
    ApplyEventHandlersInMap(mHandlersRoleOnline);
}

uint32_t Role::AddEventHandler_RoleOffline(EventHandler hander)
{
    return AddEventHandlerToMap(mHandlersRoleOffline, std::move(hander));
}

void Role::RemoveEventHandler_RoleOffline(uint32_t handlerID)
{
    RemoveEventHandlerFromMap(mHandlersRoleOffline, handlerID);
}

void Role::ApplyEventHandlers_RoleOffline()
{
    ApplyEventHandlersInMap(mHandlersRoleOffline);
}

void Role::SetSkillProp(uint16_t skillID, uint16_t propType, const std::string& cfg)
{
    auto* roleSkill = GetRoleSkill();
    if (!roleSkill) return;

    roleSkill->SetSkillProp(skillID, propType, cfg);
}

bool Role::GetSkillProp(uint16_t skillID, uint16_t propType)
{
    auto* roleSkill = GetRoleSkill();
    if (!roleSkill) return false;

    return roleSkill->GetSkillProp(skillID, propType);
}

void Role::SetNeedUpdateFlag(std::size_t pos)
{
    if (pos >= mNeedUpdateFlags.size()) return;
    if (mNeedUpdateFlags.none())
        MapRoleMgr::GetInstance()->AddToNeedUpdateList(this);
    mNeedUpdateFlags.set(pos);
}

void Role::ResetNeedUpdateFlag(std::size_t pos)
{
    if (pos >= mNeedUpdateFlags.size()) return;
    if (mNeedUpdateFlags.none()) return;
    mNeedUpdateFlags.reset(pos);
    if (mNeedUpdateFlags.any()) return;
    MapRoleMgr::GetInstance()->RemoveFromNeedUpdateList(this);
}

void Role::SetInvalid()
{
    mInvalid = true;
    SetNeedUpdateFlag(invalid_role_need_update_flag);
    if (IsPlayer())
    {
        MapRoleMgr::GetInstance()->CreateImageByPlayer(GetGUID());
    }
    MapRoleMgr::GetInstance()->RemoveRole_Fast(GetGUID());
}
