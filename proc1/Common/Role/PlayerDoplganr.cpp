#include "stdafx.h"
#include "PlayerDoplganr.h"
#include "Player.h"
#include "CastleWarMgr.h"

PlayerDoplganr::PlayerDoplganr() : Role(role_type_player_doplganr)
{
}

PlayerDoplganr::~PlayerDoplganr()
{
    mRolePack->ClearAllItems();
}

void PlayerDoplganr::Init()
{
    mRoleAttr   = new RoleAttr(this);
    mRoleState  = new RoleState(this);
    mRoleMove   = new RoleMove(this);
    mRoleSkill  = new RoleSkill(this);
    mRoleBuff   = new RoleBuff(this);
    mRolePack   = new RolePack(this);
    CopyBuffFromMaster();
    Role::Init();
	mVieRange              = 10;
	mMovRange              = 20;
	mTraRange              = 12;
    SetNeedUpdateFlag(ai_need_update_flag);     // 不能放在构造函数中，因为构造时GUID为0
}

Role* PlayerDoplganr::GetNearestRoleByType(uint8_t roleType,Role* role)
{
    auto map = GetCurMap();
    if (!map) return nullptr;
    auto posX = role->GetRolePosX();
    auto posY = role->GetRolePosY();
    return map->GetNearstRoleByType(posX, posY, false, roleType, this);
}



bool PlayerDoplganr::CanHitTarget(int mCurSkillID)
{
    auto* target = MapRoleMgr::GetInstance()->FindRole(mTarGUID);
    if (!target) return false;

    if (!target->CheckAlive())return false;

    auto skill = sSkillConfig.GetByID(mCurSkillID);
    if (!skill) return false;

    auto dis = DistanceFromRole(target);
    auto* skillcfg = sSkillConfig.GetByID(mCurSkillID);
    if (!skillcfg) return false;

    if (dis > skillcfg->CastDistance) return false;

    if (skillcfg->RangeType == skill_range_type_line) {
        if (!IsInSameLine(target)) return false;
    }
    return true;
}

void PlayerDoplganr::Update(int32_t deltaTimeMS)
{
    auto *master = GetMaster();
    if (!master) return;

    if (!CheckAlive()) return;

    Role::Update(deltaTimeMS);

    if (GetTimeStampMillisecond2() < TimeElapsed())
    {
        return;
    }

    auto state = GetAIState();

    switch (state) {

    case ai_state_idle:
        HandleAIState_idle(deltaTimeMS);
        break;
    case ai_state_follow:
        HandleAIState_follow(deltaTimeMS);
        break;
    case ai_state_attack:
        HandleAIState_Attack(deltaTimeMS);
        break;
    case ai_state_pursure:
        HandleAIState_Pursure(deltaTimeMS);
        break;
    case ai_state_attack_idle:
        HandleAIState_attack_idle(deltaTimeMS);
        break;
    default:
        break;
    }


    //几秒清空一次目标  重新获取
    //仇恨列表  改成遇见怪物增加一点仇恨
  
    if (GetTimeStampMillisecond2() > mEndLifeTime)
    {
        SetRoleProp(role_hp, 0);
        AttackResult res;
        res.actorGUID = GetGUID();
        res.actorName = GetName();
        res.targetGUID = GetGUID();
        res.skillId = 0;
        res.decreaseHP = 1;            // target扣hp
        res.remainHP = 0;            // target剩余hp
        res.type = 0;            // 伤害类型
        AttackedByRole(res);
        //OnRoleDie(GetGUID());
    }
}


void PlayerDoplganr::ApplySkill(int mCurSkillID)
{
    auto skill = sSkillConfig.GetByID(mCurSkillID);
    if (!skill) return;

    auto roleskill = GetRoleSkill();
    if (!roleskill)return;

    auto stamp = GetTimeStampMillisecond2();
    if (skill->CastWay == skill_cast_target)
    {
        ApplySkillOnTarget(mCurSkillID, mTarGUID, stamp);
    }
    else if (skill->CastWay == skill_cast_grid)
    {
        auto role = MapRoleMgr::GetInstance()->FindRole(mTarGUID);
        if (!role)return;
        ApplySkillOnGrid(mCurSkillID, mTarGUID, role->GetRolePosX(), role->GetRolePosY(), stamp);
    }
    else if (skill->CastWay == skill_cast_direct)
    {
        ApplySkillOnGrid(mCurSkillID, 0,GetRolePosX(),GetRolePosY(), stamp);
    }
}

void PlayerDoplganr::SetCurAttackDir()
{
    auto tarRole = MapRoleMgr::GetInstance()->FindRole(mTarGUID);
    if (!tarRole)return;
    auto dir = Utility::CalcRelativeDir(GetRolePosX(), GetRolePosY(), tarRole->GetRolePosX(), tarRole->GetRolePosY());
    SetRoleDir(dir);
}

bool PlayerDoplganr::IsInTraRange(uint64_t tarGuid)
{
    auto role = MapRoleMgr::GetInstance()->FindRole(tarGuid);
    if (!role) return false;
    auto dis = DistanceFromRole(role);
    if (dis > mTraRange)
    {
        return false;
    }
    return true;
}

bool PlayerDoplganr::IsInVieRange(uint64_t tarGuid)
{
    auto role = MapRoleMgr::GetInstance()->FindRole(tarGuid);
    if (!role) return false;
    auto dis = DistanceFromRole(role);
    if (dis > mVieRange)
    {
        return false;
    }
    return true;
}

bool PlayerDoplganr::GetWalkablePos(uint16_t& dir, uint16_t tarRoleposX, uint16_t tarRoleposY, uint16_t& tarX, uint16_t& tarY, uint16_t todir)
{
    auto curDir = (dir + todir + dir_max) % dir_max;
    tarX = tarRoleposX + DirOffsetData[curDir].XOffset;
    tarY = tarRoleposY + DirOffsetData[curDir].YOffset;
    return true;
}

bool PlayerDoplganr::IsEmptyHateValueMap()
{
    return this->HatedVauleMap.empty();
}

bool PlayerDoplganr::IsTarInHateValueMap(uint64_t tarGuid)
{
    if (HatedVauleMap.empty())return false;
    auto it = HatedVauleMap.find(tarGuid);
    if (it != HatedVauleMap.end())return true;
    return false;
}

Role* PlayerDoplganr::GetMaxHatedValueRole()
{
    Hated_Value tmpdata;
    uint64_t tmpGuid = 0;
    std::map<uint64_t, Hated_Value>::iterator iter;
    for (auto& i : HatedVauleMap)
    {
        // if (!IsInTraRange(i.first))
        // {
        //     continue;
        // }
       
        if (i.second.hated_value > tmpdata.hated_value)
        {
            tmpGuid = i.first;
            tmpdata = i.second;
        }
        else if (i.second.hated_value == tmpdata.hated_value)
        {
            if (i.second.timer < tmpdata.timer)
            {
                tmpGuid = i.first;
                tmpdata = i.second;
            }
        }
    }
    if (tmpGuid)
    {
        auto role = MapRoleMgr::GetInstance()->FindRole(tmpGuid);
        if (!role || !role->CheckAlive() || !IsInTraRange(tmpGuid))
        {
            DeleteMaxHateValue(tmpGuid);
        }
        
        return role;
    }
    return nullptr;
}

Player* PlayerDoplganr::GetMaxHatedValueRedNameRole()
{
    Hated_Value tmpdata;
    uint64_t tmpGuid = 0;
    Hated_Value tmpRedData;
    uint64_t TmpRedGUID = 0;
    std::map<uint64_t, Hated_Value>::iterator iter;
    for (auto& i : HatedVauleMap)
    {
        if (!IsInTraRange(i.first)) continue;
        auto tarPlayer = MapRoleMgr::GetInstance()->FindPlayer(i.first);
        if (!tarPlayer)continue;
        if (tarPlayer->IsRedName())
        {
            if (i.second.hated_value > tmpRedData.hated_value)
            {
                TmpRedGUID = i.first;
                tmpRedData = i.second;
            }
            else if (i.second.hated_value == tmpRedData.hated_value)
            {
                if (i.second.timer < tmpRedData.timer)
                {
                    TmpRedGUID = i.first;
                    tmpRedData = i.second;
                }
            }
        }
        else
        {
            if (i.second.hated_value > tmpdata.hated_value)
            {
                tmpGuid = i.first;
                tmpdata = i.second;
            }
            else if (i.second.hated_value == tmpdata.hated_value)
            {
                if (i.second.timer < tmpdata.timer)
                {
                    tmpGuid = i.first;
                    tmpdata = i.second;
                }
            }
        }

    }
    auto finalGuid = TmpRedGUID ? TmpRedGUID : tmpGuid;
    auto tarPlayer = MapRoleMgr::GetInstance()->FindPlayer(finalGuid);
    return tarPlayer;
}


void PlayerDoplganr::AddHatedValue(uint64_t guid, uint32_t hatevalue)
{
    if (guid == GetGUID())
    {
        return;
    }
    Hated_Value tmpdata;
    auto curtime = time(nullptr);
    tmpdata.hated_value = hatevalue;
    auto iter = HatedVauleMap.find(guid);
    if (iter != HatedVauleMap.end())
    {
        if ((iter->second.hated_value += hatevalue) >= MAX_HATED_VALUE)
        {
            iter->second.hated_value = MAX_HATED_VALUE;
            iter->second.timer = time(nullptr);
        }
        return;
    }
    if (hatevalue >= MAX_HATED_VALUE)
    {
        tmpdata.timer = time(nullptr);
    }
    HatedVauleMap.insert(std::make_pair(guid, tmpdata));
}

void PlayerDoplganr::DeleteMaxHateValue(uint64_t guid)
{
    auto iter = HatedVauleMap.find(guid);
    if (iter == HatedVauleMap.end())return;
    HatedVauleMap.erase(iter);
}

void PlayerDoplganr::DecreaseHateValue()
{
    for (auto iter = HatedVauleMap.begin(); iter != HatedVauleMap.end();)
    {
        if (iter->second.hated_value * DECREASE_PERCENTAGE < 0.1)
        {
            iter = HatedVauleMap.erase(iter);
            continue;
        }
        iter->second.hated_value *= DECREASE_PERCENTAGE;
        ++iter;
    }
}

CLuaObject PlayerDoplganr::GetHateValueMapToLua()
{
    auto luaObj = NewLuaObj();
    int index = 1;

    for (auto& i : HatedVauleMap)
    {
        CLuaObject table = NewLuaObj();
        table[1] = i.first;
        table[2] = i.second.hated_value;
        table[3] = i.second.timer;
        luaObj[index] = table;
    }
    return luaObj;
}

void PlayerDoplganr::HandleAIState_idle(int32_t deltaTimeMS)
{
    auto *master = GetMaster();
    if (!master) return;

    auto dist = DistanceFromRole(master);
    if (dist > START_FOLLOW_DIST) {
        SetAIState(ai_state_follow);
        GenStopFollowDist();
        return;
    }

    std::string Doplganr_State = master->GetCustVar(mStateKey);
    if (Doplganr_State == "1")
    {
        ResetTarGuid();
        SetAIState(ai_state_follow);
        return;
    }

    auto role = GetMaxHatedValueRole();
    if (role)
    {
        SetTarGuid(role->GetGUID());
        SetAIState(ai_state_attack);
    }
    else
    {
        ResetTarGuid();
        SetAIState(ai_state_follow);
    }
}


void PlayerDoplganr::HandleAIState_follow(int32_t deltaTimeMS)
{
    auto* master = GetMaster();
    if (!master) return;
    auto dist = DistanceFromRole(master);
    if (dist <= StopFollowDist()) {
        SetAIState(ai_state_idle);
        AddTimeElapsed(RunDelayTime);
        return;
    }

    if (dist > JUMP_DIST) {
        JumpToMaster();
        AddTimeElapsed(RunDelayTime);
    }
    else {
        if (FollowMaster() == move_type_walk)
            AddTimeElapsed(WalkDelayTime);
        else
            AddTimeElapsed(RunDelayTime);
    }
    SetAIState(ai_state_idle);
}


void PlayerDoplganr::HandleAIState_Pursure(int32_t deltaTimeMS)
{
    auto role = MapRoleMgr::GetInstance()->FindRole(GetTarGuid());
    //如果有目标  就攻击或者移动
    if (role && role->CheckAlive())
    {
        auto move = moveto(role->GetRolePosX(), role->GetRolePosY());
        if (move == WalkDelayTime)
            AddTimeElapsed(WalkDelayTime);
        else if (move == RunDelayTime)
            AddTimeElapsed(RunDelayTime);
    }
    SetAIState(ai_state_attack_idle);
}

void PlayerDoplganr::HandleAIState_attack_idle(int32_t deltaTimeMS)
{
    auto* master = GetMaster();
    if (!master) return;

    auto dist = DistanceFromRole(master);
    if (dist > ATTACK_FOLLOW_DIST) {
        SetAIState(ai_state_follow);
        GenStopAttackFollowDist();
        return;
    }
    bool needchange = false;
    auto Tarrole = MapRoleMgr::GetInstance()->FindRole(GetTarGuid());
    if (!Tarrole || !Tarrole->CheckAlive())
    {
        needchange = true;
    }
    else
    {
        if (mChangeTargTime > GetTimeStampMillisecond2())
        {
            needchange = true;
        }
    }

    if (needchange)
    {
        Tarrole = GetMaxHatedValueRole();
    }
    if (Tarrole)
    {
        SetTarGuid(Tarrole->GetGUID());
        if (DistanceFromRole(Tarrole) <= 2)
        {
            auto posX = GetRolePosX();
            auto posY = GetRolePosY();
            auto dir = Utility::CalcRelativeDir(posX, posY, Tarrole->GetRolePosX(), Tarrole->GetRolePosY());
            uint16_t tmpPosX = 0;
            uint16_t tmpPosY = 0;
            uint16_t tmpDir = dir_down;
        
            if (GetWalkablePos(dir, posX, posY, tmpPosX, tmpPosY, tmpDir))
            {
                if (tmpPosX == mMovPosX && mMovPosY == tmpPosY)
                {
                    if (mMovDir == dir_right_down)
                    {
                        GetWalkablePos(dir, posX, posY, tmpPosX, tmpPosY, dir_left_down);
                    }
                    else if (mMovDir == dir_left_down)
                    {
                        GetWalkablePos(dir, posX, posY, tmpPosX, tmpPosY, dir_right);
                    }
                    else if (mMovDir == dir_right)
                    {
                        GetWalkablePos(dir, posX, posY, tmpPosX, tmpPosY, dir_left);
                    }
                    else if (mMovDir == dir_left || mMovDir == dir_down)
                    {
                        GetWalkablePos(dir, posX, posY, tmpPosX, tmpPosY, dir_right_down);
                    }
                }
                mMovDir = tmpDir;
                if (mMovDir == dir_down)
                {
                    mMovPosX = tmpPosX;
                    mMovPosY = tmpPosY;
                }
               
                auto move = moveto(tmpPosX, tmpPosY);
                if (move == move_type_walk)
                    AddTimeElapsed(WalkDelayTime);
                else if (move == move_type_walk)
                    AddTimeElapsed(RunDelayTime);
            }
            SetAIState(ai_state_attack);
        }
        else
        {
            SetAIState(ai_state_attack);
            mChangeTargTime = GetTimeStampMillisecond2() + TARGET_RESP_TIME;
        }
        
    }
    else
    {
        ResetTarGuid();
        SetAIState(ai_state_follow);
    }
}


void PlayerDoplganr::HandleAIState_Attack(int32_t deltaTimeMS)
{
    auto role = MapRoleMgr::GetInstance()->FindRole(GetTarGuid());
    //如果有目标  就攻击或者移动
    SetAIState(ai_state_attack_idle);
    if (role && role->CheckAlive())
    {
        auto dist = DistanceFromRole(role);
        //附近有没有其他目标
        //GetRolesInSameCircle(uint16_t x0, uint16_t y0, uint8_t radius, uint8_t roleType)
        auto map = GetCurMap();
        auto monsternum = 0;
        auto playernum = 0;
        if (map)
        {
            auto monvec = map->GetRolesInSameCircle(role->GetRolePosX(), role->GetRolePosY(), 1, role_type_monster);
            monsternum = monvec.size();

            auto playervec = map->GetRolesInSameCircle(role->GetRolePosX(), role->GetRolePosY(), 1, role_type_player);
            playernum = playervec.size();
        }
      
        std::string mskill = "";
        //根据距离选择技能
        int maxdist = 0;
        int32_t skillid = 0;
        int skillAttackRatio = 0;
        auto* mySkill = GetRoleSkill();
        if (mySkill)
        {
            auto& skillList = mySkill->GetSkillList();
            for (auto& skillData : skillList) {
                //所有可以释放的技能
                if (!skillData.InCD())
                {
                    auto* cfg = skillData.GetSkillCfg();
                    if (cfg && (cfg->CastDistance >= dist || cfg->CastDistance == 0))
                    {
                        if (maxdist < cfg->CastDistance)
                        {
                            maxdist = cfg->CastDistance;
                        }
                        if (skillAttackRatio < skillData.GetSkillCfg()->AttackRatio)
                        {
                            skillid = skillData.GetID();
                        }
                        mskill = mskill + std::to_string(skillData.GetID()) + "|" + std::to_string(skillData.GetSkillCfg()->CD) + "|" + std::to_string(skillData.GetSkillCfg()->AttackRatio) + "|" + std::to_string(skillData.GetSkillCfg()->RangeParam) + "|" + std::to_string(skillData.GetSkillCfg()->RangeType) + "_";
                    }
                }
            }
        }
        if (maxdist < dist)
        {
            SetAIState(ai_state_pursure);
        }
        else
        {
            //根据攻击速度  增加时间
            //发送lua 可释放技能
            CLuaObject upgradeRet = NewLuaObj();
            auto* master = GetMaster();
            if (master)
            {
                TRIGGER_EVENT_RET<CLuaObject>(upgradeRet, trigger_pre_Doplganr_choose_skill, GetGUIDAsString(), master->GetGUIDAsString(), monsternum, playernum, mskill);
                if (luabind::type(upgradeRet) == LUA_TTABLE && luabind::type(upgradeRet["skillid"]) == LUA_TNUMBER)
                {
                    int32_t luaskillid = luabind::object_cast<int32_t>(upgradeRet["skillid"]);
                    if (luaskillid > 0)
                    {
                        skillid = luaskillid;
                    }
                }
            }

            //使用技能
            SetCurAttackDir();
            ApplySkill(skillid);
            AddTimeElapsed(GetRoleProp(role_casting_speed)+ 150);
        }
    }
}

uint8_t PlayerDoplganr::FollowMaster()
{
    auto *roleMove = GetRoleMove();
    if (!roleMove) return 0;
    if (roleMove->IsMoving()) return 0;

    auto x0 = GetRolePosX();
    auto y0 = GetRolePosY();

    auto *master = GetMaster();
    if (!master) return 0;

    auto x1 = master->GetRolePosX();
    auto y1 = master->GetRolePosY();

    auto *pathFinder = CAStarPathFinder::GetInstance();
    if (!pathFinder) return 0;

    auto result = pathFinder->FindPathToTarget(make_pair(x0, y0), make_pair(x1, y1), MAX_DEPTH, true, GetCurMap());
    if (result != path_found_target) return 0;

    std::vector<std::pair<int, int>> finalPath;
    pathFinder->GetFinalPath(finalPath);
    pathFinder->Clear();
    if (finalPath.size() < 2) return 0;

    auto xt = static_cast<uint16_t>(finalPath[1].first);
    auto yt = static_cast<uint16_t>(finalPath[1].second);
    auto dir = Utility::CalcRelativeDir(x0, y0, xt, yt);
    SetRoleDir(dir);

    uint8_t moveType = move_type_walk;
    auto *masterAttr = master->GetRoleAttr();
    if (masterAttr && masterAttr->GetMoveType() == move_type_run) {
        moveType = move_type_run;
    }

    roleMove->MoveTo(xt, yt, moveType);
    return moveType;
}
uint8_t PlayerDoplganr::moveto(uint16_t x1, uint16_t y1)
{
    auto* roleMove = GetRoleMove();
    if (!roleMove) return 2;
    if (roleMove->IsMoving()) return 2;

    auto x0 = GetRolePosX();
    auto y0 = GetRolePosY();

    
    auto* pathFinder = CAStarPathFinder::GetInstance();
    if (!pathFinder) return 2;

    auto result = pathFinder->FindPathToTarget(make_pair(x0, y0), make_pair(x1, y1), MAX_DEPTH, true, GetCurMap());
    if (result != path_found_target) return 2;

    std::vector<std::pair<int, int>> finalPath;
    pathFinder->GetFinalPath(finalPath);
    pathFinder->Clear();
    if (finalPath.size() < 2) return 2;

    auto xt = static_cast<uint16_t>(finalPath[1].first);
    auto yt = static_cast<uint16_t>(finalPath[1].second);
    auto dir = Utility::CalcRelativeDir(x0, y0, xt, yt);
    SetRoleDir(dir);

    uint8_t moveType = move_type_walk;
    auto* masterAttr = GetRoleAttr();
    if (masterAttr && masterAttr->GetMoveType() == move_type_run) {
        moveType = move_type_run;
    }
    roleMove->MoveTo(xt, yt, moveType);
    return moveType;
}

void PlayerDoplganr::JumpToMaster()
{
    auto *master = GetMaster();
    if (!master) return;

    auto x = master->GetRolePosX();
    auto y = master->GetRolePosY();
    auto *map = master->GetCurMap();
    JumpMap(map, x, y);
    auto dir = master->GetRoleDir();
    SetRoleDir(dir);
    TRIGGER_EVENT(this, trigger_player_doplganr_jump_to_master, GetGUIDAsString(), master->GetGUIDAsString());
}

void PlayerDoplganr::GenStopFollowDist()
{
    mStopFollowDist = Tools::GenerateRandomInteger<uint16_t>(1, START_FOLLOW_DIST);
}
void PlayerDoplganr::GenStopAttackFollowDist()
{
    mStopFollowDist = Tools::GenerateRandomInteger<uint16_t>(1, ATTACK_FOLLOW_DIST);
}

void PlayerDoplganr::SendAppearNtf(Role *toRole)
{
    if (!toRole || !toRole->IsPlayer()) return;

    auto *master = GetMaster();
    if (!master && mMasterGUID > 0) return;

    auto &data = gProtoMS_PlayerAppearNtf;
    data.Reset();
    data.player_guid    = GetGUID();
    if(master)
        data.master_guid = master->GetGUID();
    else
        data.master_guid = 0;
    data.status         = CheckAlive() ? 0 : 1;
    data.body           = GetEquipID(site_armor);
    data.weapon         = GetEquipID(site_weapon);
    data.level          = GetRoleProp(role_level);
    data.hp             = GetRoleProp(role_hp);
    data.max_hp         = GetRoleProp(role_max_hp);
    data.mp             = GetRoleProp(role_mp);
    data.max_mp         = GetRoleProp(role_max_mp);
    data.model_id       = GetRoleProp(role_changed_modelid);
    data.gender         = static_cast<uint8_t>(GetRoleProp(role_gender));
    data.job            = static_cast<uint8_t>(GetRoleProp(role_job));
    data.dir            = static_cast<uint8_t>(GetRoleDir());
    data.dst_x          = static_cast<uint16_t>(GetRolePosX());
    data.dst_y          = static_cast<uint16_t>(GetRolePosY());
    data.head           = static_cast<uint16_t>(GetRoleProp(role_head));
    data.hair           = static_cast<uint16_t>(GetRoleProp(role_hair));
    data.hair_color     = static_cast<uint16_t>(GetRoleProp(role_hair_color));
    data.move_speed     = static_cast<uint16_t>(GetRoleProp(role_move_speed));
    data.attack_speed   = static_cast<uint16_t>(GetRoleProp(role_attack_speed));
    data.casting_speed  = static_cast<uint16_t>(GetRoleProp(role_casting_speed));
    data.show_fashion   = static_cast<uint16_t>(GetRoleProp(role_is_show_fashion));
    strcpy_s(data.name,  GetName());
    strcpy_s(data.alias, GetAlias());

    if (master)
    {
        const auto& guildName = master->GetGuildName();
        if (!guildName.empty()) {
            auto guildMember = master->GetGuildDataMgr().GetGuildMember();
            if (guildMember && guildMember->status != guild_member_status_removed) {
                strcpy_s(data.family_name, guildName);
            }

            auto* shabak = CastleWarMgr::GetInstance();
            if (shabak && shabak->IsWinnerGuild(guildName)) {
                auto* sbkcfg = shabak->GetCfg();
                if (sbkcfg) strcpy_s(data.castle_name, sbkcfg->MainCityMap);
            }
        }
    }
    else
    {
        strcpy_s(data.family_name, family_name);
        strcpy_s(data.castle_name, castle_name);
    }
   

    auto *player = static_cast<Player *>(toRole);
    data.sessid = player->GetClSessionID();
    SendDataBySessionID(player->GetGsSessionID(), data);
}

void PlayerDoplganr::SendRoleAppNtf(Role *toRole)
{
    if (!toRole || !toRole->IsPlayer()) return;
    auto *player = static_cast<Player *>(toRole);

    auto &data = gProtoMS_RoleAppNtf;
    data.Reset();
    data.player_guid    = GetGUID();
    data.sessionid      = player->GetClSessionID();
    data.body           = GetEquipID(site_armor);
    data.weapon         = GetEquipID(site_weapon);
    data.wings          = GetEquipID(site_wings);
    data.mount          = GetEquipID(site_mount);
    data.amulet         = GetEquipID(site_amulet);
    data.hair           = static_cast<uint16_t>(GetRoleProp(role_hair));
    data.hair_color     = static_cast<uint16_t>(GetRoleProp(role_hair_color));
    data.is_first       = 1;

    std::pair<item_site, item_site> ext[] = {
        {site_weapon, site_equip_end},
        {site_glasses, site_equip_reserved_end},
        {site_equip_custom_0, site_equip_custom_end},
        {site_fashion_helmet, site_fashion_end},
    };

    bool needSend = true;
    auto &i = data.equip_num;

    for (const auto& siteRang : ext)
    {
        for (uint16_t site = siteRang.first; site < siteRang.second; ++site) {
            auto id = GetEquipID(site);
            if (id == 0) continue;

            auto &equip = data.equips[i];
            equip.site = static_cast<uint16_t>(site);
            equip.id = id;

            needSend = true;

            if (++i == _countof(data.equips)) {
                SendDataBySessionID(player->GetGsSessionID(), data);
                i = 0;
                needSend = false;
                data.is_first = 0;
            }
        }
    }

    if (needSend) {
        SendDataBySessionID(player->GetGsSessionID(), data);
    }
}

bool PlayerDoplganr::CheckTakeGrid(uint16_t x, uint16_t y)
{
    auto *mgr = CastleWarMgr::GetInstance();
    auto *master = GetMaster();
    if (mgr && master) {
        const auto &guild = master->GetGuildName();
        if (mgr->IsWinnerGuild(guild) && mgr->IsPalaceFrontDoorMonsterSpot(x, y)) {
            return true;        // 皇宫归属行会成员可穿过正门怪物
        }
    }

    auto *map = GetCurMap();
    if (!map) return false;

    return !map->GetMapGrid().IsForbid_PlayerMoveAck(x, y, this);
}

void PlayerDoplganr::OnRoleEnter(Role *role)
{
    if (!role) return;
    if (role->IsMonster()) {
        //mAttackableRoles.insert(role->GetGUID());
        auto* monster = static_cast<Monster*>(role);
        if (monster->IsTreasureMonster()) return;
        if (monster->IsBiaoChe()) return;

        AddHatedValue(role->GetGUID(), 1);
    }
}

void PlayerDoplganr::OnRoleLeave(Role *role)
{
    if (!role) return;
    if (role->IsMonster()) {
        //mAttackableRoles.erase(role->GetGUID());
        DeleteMaxHateValue(role->GetGUID());
    }
}

void PlayerDoplganr::OnRoleExit(Role *role)
{
    OnRoleLeave(role);
}

void PlayerDoplganr::OnRoleMove(Role *role)
{
}

void PlayerDoplganr::OnRoleDie(uint64_t killedBy)
{
    Role::OnRoleDie(killedBy);
    ResetNeedUpdateFlag(ai_need_update_flag);

    auto *master = GetMaster();
    if (!master) return;

    auto &doplganrMgr = master->GetDoplganrMgr();
    if (!doplganrMgr) return;

    doplganrMgr->RemoveDoplganr(this);
}

bool PlayerDoplganr::IsInSameTeam(Role *role)
{
    auto *master = GetMaster();
    if (!master) return false;
    return master->IsInSameTeam(role);
}

bool PlayerDoplganr::IsInSameGuild(Role *role)
{
    auto *master = GetMaster();
    if (!master) return false;
    return master->IsInSameGuild(role);
}

bool PlayerDoplganr::IsInSameCamp(Role *role)
{
    auto *master = GetMaster();
    if (!master) return false;
    return master->IsInSameCamp(role);
}

bool PlayerDoplganr::IsGrayName()
{
    auto *master = GetMaster();
    if (!master) return false;
    return master->IsGrayName();
}

bool PlayerDoplganr::IsRedName()
{
    auto *master = GetMaster();
    if (!master) return false;
    return master->IsRedName();
}

void PlayerDoplganr::CloneMaster()
{
    Init();
    CopyEquipFromMaster();
    CopySkillFromMaster();
    CopyPropFromMaster();
}

Player *PlayerDoplganr::GetMaster()
{
    return MapRoleMgr::GetInstance()->FindPlayer(mMasterGUID);
}


void  PlayerDoplganr::SetMasterGUID(uint64_t masterGUID)
{ 
    if (masterGUID == 0)
    {
        auto* master = GetMaster();
        if (master)
        {
            const auto& guildName = master->GetGuildName();
            if (!guildName.empty()) {
                auto guildMember = master->GetGuildDataMgr().GetGuildMember();
                if (guildMember && guildMember->status != guild_member_status_removed) {
                    strcpy_s(family_name, guildName);
                }

                auto* shabak = CastleWarMgr::GetInstance();
                if (shabak && shabak->IsWinnerGuild(guildName)) {
                    auto* sbkcfg = shabak->GetCfg();
                    if (sbkcfg) strcpy_s(castle_name, sbkcfg->MainCityMap);
                }
            }
        }
    }
    mMasterGUID = masterGUID;
    
}

void PlayerDoplganr::CopyPropFromMaster()
{
    auto *master = GetMaster();
    if (!master) return;
    SetRoleProp(role_is_show_fashion, 0);
    int32_t props1[] = {
        role_gender, role_job, role_level,role_atk_mode,
        role_head, role_hair, role_hair_color,role_changed_modelid,
          role_move_speed, role_attack_speed, role_casting_speed,
        role_can_walk, role_can_run, role_can_turn,
        role_can_through, role_can_through_monster,
        role_can_phy_atk, role_can_mag_atk, role_can_use_skill,role_avatar
    };
    for (const auto& prop : props1) {
        SetRoleProp(prop, master->GetRoleProp(prop));
    }
    int32_t props[] = {
        role_max_hp, role_max_mp,                // max_hp要在hp前面
        role_base_max_hp, role_base_max_mp,
        role_base_max_phy_def, role_base_min_phy_def,
        role_base_max_mag_def, role_base_min_mag_def,
        role_base_max_phy_atk, role_base_min_phy_atk,
        role_base_max_mag_atk, role_base_min_mag_atk,
        role_hit, role_miss, 
        role_base_max_hp_pct,role_base_min_phy_def_pct,role_base_max_phy_def_pct,role_base_min_mag_def_pct,
        role_base_max_mag_def_pct,role_base_min_mag_atk_pct,role_base_max_mag_atk_pct, role_hp, role_mp,
    };
    for (const auto& prop : props) {
        SetRoleProp(prop, master->GetRoleProp(prop));
    }

    //通过lua取得
    CLuaObject upgradeRet = NewLuaObj();
    CLuaObject TableData = NewLuaObj();
    int64_t nDuration = 120000;
    
    TRIGGER_EVENT_RET<CLuaObject>(upgradeRet, trigger_pre_Get_Doplganr_Att, master->GetGUIDAsString());
    if (luabind::type(upgradeRet) == LUA_TTABLE && luabind::type(upgradeRet["Duration"]) == LUA_TNUMBER && luabind::type(upgradeRet["Add"]) == LUA_TTABLE && luabind::type(upgradeRet["State"]) == LUA_TSTRING)
    {
        nDuration = luabind::object_cast<int64_t>(upgradeRet["Duration"]);
        TableData = upgradeRet["Add"];
        mStateKey = luabind::object_cast<string>(upgradeRet["State"]);
    }
    mEndLifeTime = nDuration*1000 + GetTimeStampMillisecond2();
   
    int ncount = 0;
    int32_t value1 = 0;
    int32_t value2 = 0;
    for (luabind::iterator iter(TableData), end; iter != end; ++iter)
    {
        auto inobj = *iter;
        if (luabind::type(inobj) != LUA_TNUMBER) break;
        auto Fvalue = luabind::object_cast<int32_t>(inobj);
        if (ncount % 2 == 0)
        {
            value1 = Fvalue;
        }
        else
        {
            value2 = Fvalue;
            if(value1> role_attr_min && value1< role_attr_max && value2 > 0)
                SetRoleProp(value1, master->GetRoleProp(value1) * (value2 / 10000.0));
            value1 = 0;
            value2 = 0;
        }
        ncount++;
    }
    SetRoleDir(master->GetRoleDir());
}

void PlayerDoplganr::CopyEquipFromMaster()
{
    auto *master = GetMaster();
    if (!master) return;

    auto *masterPack = master->GetRolePack();
    if (!masterPack) return;

    auto *myRolePack = GetRolePack();
    if (!myRolePack) return;

    myRolePack->CopyFromOwner(masterPack);
}

void PlayerDoplganr::CopySkillFromMaster()
{
    auto *master = GetMaster();
    if (!master) return;

    auto *masterSkill = master->GetRoleSkill();
    if (!masterSkill) return;

    auto *mySkill = GetRoleSkill();
    if (!mySkill) return;

    const auto &skillList = masterSkill->GetSkillList();
    for (const auto &skillData : skillList) {
        mySkill->AddSkill(skillData.GetID(), skillData.IsActive(), skillData.GetProficiency(),
            RoleSkill::EncodeSkillCfg(skillData.GetSkillCfgModifyMap()));
    }

    SendSkillAddAck();
}


void PlayerDoplganr::CopyBuffFromMaster()
{
    auto* master = GetMaster();
    if (!master) return;
    std::list<BUFF_INFO_DB> list;
    master->GetRoleBuff()->GetAllBuffInfo(list);
    BUFF_INFO_DB                buffs[50];
    int buffNum = 0;
    if (!list.empty())
    {
        auto iter = list.begin();
        for (; iter != list.end();)
        {
            buffs[buffNum] = *iter;
            buffs[buffNum].actor_id = GetGUID();
            strcpy_s(buffs[buffNum].actor_name, _countof(buffs[buffNum].actor_name), GetName().c_str());
            buffNum++; iter++;
            if (buffNum == _countof(buffs) || iter == list.end())
            {
                OnGetBuffAck(buffs, buffNum);
                buffNum = 0;
            }
        }
    }
}

uint16_t PlayerDoplganr::GetEquipID(uint32_t site)
{
    auto *rolePack = GetRolePack();
    if (!rolePack) return 0;
    return rolePack->GetItemID(site);
}

void PlayerDoplganr::SendSkillAddAck()
{
    auto *master = GetMaster();
    if (!master) return;

    auto *roleSkill = GetRoleSkill();
    if (!roleSkill) return;

    const auto &skillList = roleSkill->GetSkillList();
    if (skillList.empty()) return;

    const auto *globalCfg = sGlobalConfig.GetData();
    if (!globalCfg) return;

    ProtoMS_SkillAddAck data;
    data.role_guid = GetGUID();
    data.nClientSessionID = master->GetClSessionID();

    auto &i = data.num;
    for (const auto &skillData : skillList) {
        uint16_t nSkillID = skillData.GetID();
        if (nSkillID == globalCfg->CommonAttackSkillID) continue;       // 普攻客户端不用显示

        data.info[i].id = nSkillID;
        data.info[i].active = skillData.IsActive();
        data.info[i].proficiency = skillData.GetProficiency();
        string cfg = RoleSkill::EncodeSkillCfg(skillData.GetSkillCfgModifyMap());
        strcpy_s(data.info[i].cfg, cfg);
        if (++i == _countof(data.info)) break;
    }

    SendDataBySessionID(master->GetGsSessionID(), data);
}

void PlayerDoplganr::SendSetAutoModeReq(bool enable)
{
    auto *master = GetMaster();
    if (!master) return;

    ProtoMS_SetAutoModeReq data;
    data.clsessid = master->GetClSessionID();
    data.role_guid = GetGUID();
    data.enable = enable;

    SendDataBySessionID(master->GetGsSessionID(), data);
}

bool PlayerDoplganr::ExistAttackTarget()
{
    for (const auto &guid : mAttackableRoles) {
        auto *role = MapRoleMgr::GetInstance()->FindRole(guid);
        if (role && role->CheckAlive()) {
            auto dist = DistanceFromRole(role);
            if (dist < ATTACK_DIST) {
                return true;
            }
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//
// PlayerDoplganrMgr
//

PlayerDoplganrMgr::PlayerDoplganrMgr(Player *player) : mPlayer(player)
{

}

PlayerDoplganrMgr::~PlayerDoplganrMgr()
{
}

void PlayerDoplganrMgr::DoplganrEnterMap(Map *map)
{
    if (!map) return;
    for (auto *doplganr : mDoplganrs) {
        if (!doplganr) continue;
        map->RoleEnter(doplganr);
    }
}

void PlayerDoplganrMgr::DoplganrLeaveMap()
{
    for (auto *doplganr : mDoplganrs) {
        if (!doplganr) continue;
        auto *map = doplganr->GetCurMap();
        if (!map) continue;
        map->RoleLeave(doplganr);
    }
}

void PlayerDoplganrMgr::DestroyDoplganr()
{
    for (auto *doplganr : mDoplganrs) {
        if (!doplganr) continue;
        auto guid = doplganr->GetGUID();
        MapRoleMgr::GetInstance()->RemovePlayerDoplganr(guid);
    }
    mDoplganrs.clear();
}

void PlayerDoplganrMgr::RemoveDoplganr(PlayerDoplganr *doplganr)
{
    for (auto it = mDoplganrs.begin(); it != mDoplganrs.end(); ++it) {
        if (*it == doplganr) {
            mDoplganrs.erase(it);
            break;
        }
    }
}