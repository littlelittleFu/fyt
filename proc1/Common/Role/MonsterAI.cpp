#include "stdafx.h"
#include "MonsterAI.h"
#include "Monster.h"

#include "RoleMove.h"
#include "Map.h"
#include "Map.h"

#include "ItemMap.h"
#include <queue>
#include <list>

#define BC_MAX_PATH 500       //怪物寻路最多寻路点
#define BC_MAX_DEPTH 500         //怪物寻路最大深度

const uint8_t max_dis_from_owner = 10;

MonsterAI::MonsterAI()
{
}

MonsterAI::~MonsterAI()
{

}

bool MonsterAI::Init(Monster* monster, DATA::Monster* cfg)
{
	if (nullptr == monster || nullptr == cfg) {
		return false;
	}
	auto type = cfg->MonsterAIType;//新建的类型
	mSelf = monster;

	mVieRange              = cfg->VieRange;
	mMovRange              = cfg->MovRange;
	mTraRange              = cfg->TraRange;
    mBornPosX              = 0;
    mBornPosY              = 0;
    mTarGUID               = 0;
	mTarItem               = 0;
	mAttackRange           = 0;
	mTarPlayerTime         = 0;
	mAIState               = ai_state_idle;
	mKeepMaxAttackDising   = false;
	mIsPursueAttacking     = false;
	mAttackPAursuitType = static_cast<pursue_attack_type>(type);
	if (!cfg->SkillCastingRate.empty())
	{
		mCurSkillGroup = cfg->SkillCastingRate[0];
	}
	if (type == all_type_stay_put) mSelf->SetWayFinding(false);

	for (int i = 0; i < ai_schedule_max; ++i) {
		mAISchedule[i] = 0;
		mAIScheduleState[i] = ai_schedule_state_ready;
	}
	mAIScheduleTime[ai_schedule_MovTime] = cfg->MovTime;
	mAIScheduleTime[ai_schedule_MovStepTime] = cfg->StepWait;
	mAIScheduleTime[ai_schedule_MovReadyTime] = cfg->MoveReady;
	mAIScheduleTime[ai_schedule_AttackReadyTime] = cfg->AttackReady;
	mAIScheduleTime[ai_schedule_AttackTime] = cfg->AttackSpeed;
	mAIScheduleTime[ai_schedule_MoveDelayTime] = cfg->MoveSpeed;
	mAIScheduleTime[ai_schedule_BackTime] = cfg->Back;
	mAIScheduleTime[ai_schedule_Type2StayTime] = 1000;
	mAIScheduleTime[ai_schedule_DecreaseHateTime] = DECREASE_HATE_TIME;
	mAIScheduleTime[ai_schedule_MoveStep] = cfg->Step;

	return true;
}

void MonsterAI::RegisterBehaviour(const CLuaObject& info)
{
	for (luabind::iterator it(info), end; it != end; ++it)
	{
		auto obj = *it;
		if (luabind::type(obj[1]) != LUA_TNUMBER) continue;
		auto index = luabind::object_cast<monster_behaviour_trigger>(obj[1]);

		RegisterInfo info;
		info.params = luabind::object_cast<std::string>(obj[2]);
		info.callback = luabind::object_cast<std::string>(obj[3]);
		mBehaviorMap[index] = info;
	}
}

void MonsterAI::RegisterAttribute(const CLuaObject& info)
{
	for (luabind::iterator it(info), end; it != end; ++it)
	{
		if (luabind::type(*it) != LUA_TNUMBER) continue;
		auto index = luabind::object_cast<MonsterAI_Attribute>(*it);
		mAttributeMap[index] = true;
	}
}

void MonsterAI::RemoveBehaviour(uint16_t behaviourID)
{
	auto iter = mBehaviorMap.find((monster_behaviour_trigger)behaviourID);
	if (iter != mBehaviorMap.end())
	{
		mBehaviorMap.erase(iter);
	}
}

const std::string & MonsterAI::GetScriptName()
{
	if (nullptr != mSelf) {
		return mSelf->GetScriptName();
	}
	return EMPTYSTR;
}

bool MonsterAI::CheckSelfState()
{
	if (!mSelf) return false;

	if (!mSelf->CheckAlive()) return false;

	if (!mSelf->IsWayFinding()) return false;

	if (mSelf->GetRoleProp(role_has_repelled))return false;

	return true;
}

void MonsterAI::ApplySkill()
{
	auto skill = sSkillConfig.GetByID(mCurSkillID);
	if (!skill) return;

	auto belong = mSelf->GetMaster();
	if (belong) {
		auto roleskill = belong->GetRoleSkill();
		if (roleskill)
			roleskill->AddGrayBuff(mTarGUID);
	}

	auto roleskill = mSelf->GetRoleSkill();
	if (!roleskill)return;
	roleskill->AddSkill(mCurSkillID, true, 0);
	auto stamp = GetTimeStampMillisecond2();
	if (skill->CastWay == skill_cast_target)
	{
		mSelf->ApplySkillOnTarget(mCurSkillID, mTarGUID, stamp);
	}
	else if (skill->CastWay == skill_cast_grid)
	{
		auto role = MapRoleMgr::GetInstance()->FindRole(mTarGUID);
		if (!role)return;
		mSelf->ApplySkillOnGrid(mCurSkillID, mTarGUID, role->GetRolePosX(), role->GetRolePosY(), stamp);
	}
	else if (skill->CastWay == skill_cast_direct)
	{
		mSelf->ApplySkillOnGrid(mCurSkillID, 0, mSelf->GetRolePosX(), mSelf->GetRolePosY(), stamp);
	}
}

void MonsterAI::SetBackStatus()
{
	if (IsAIStateScheduleReady(ai_schedule_back)) {
		StartAISchedule(ai_schedule_back);
	};
}

void MonsterAI::SetIsPursueAttackingStatus(bool ref)
{
	if (mIsPursueAttacking == ref)return;
	if (!mSelf->IsMonster())return;
	mIsPursueAttacking = ref;
	ProtoMS_MonsterPursureAttackingNtf info;
	info.guid = mSelf->GetGUID();
	mIsPursueAttacking == true ? info.status = 1 : info.status = 0;

	auto pMap = mSelf->GetCurMap();
	if (!pMap) return;

	auto x = mSelf->GetRolePosX();
	auto y = mSelf->GetRolePosY();

	auto f = [&](Role* pRole) {
		NotifyAroundPlayers_PursureStatusChanged(pRole,info);
	};

	pMap->ApplyFuncToAllPlayersInAroundRegions(x, y, f);
}

void MonsterAI::NotifyAroundPlayers_PursureStatusChanged(Role* role, ProtoMS_MonsterPursureAttackingNtf& info)
{
	if (!role || !role->IsPlayer()) return;
	auto pPlayer = static_cast<Player*>(role);
    if (!pPlayer->IsOnline()) return;
	info.sessionid = pPlayer->GetClSessionID();
	SendDataBySessionID(pPlayer->GetGsSessionID(), info);
}

void MonsterAI::NotifyAroundPlayers_BackStatusChanged(Role* role, ProtoMS_MonsterBackNtf& info)
{
	if (!role || !role->IsPlayer()) return;
	auto pPlayer = static_cast<Player*>(role);
    if (!pPlayer->IsOnline()) return;
	info.sessionid = pPlayer->GetClSessionID();
	SendDataBySessionID(pPlayer->GetGsSessionID(), info);
}

void MonsterAI::GetAroundTarget(uint16_t tarRoleposX, uint16_t tarRoleposY, std::vector<pair<uint16_t, uint16_t>>& canTakePos)
{
	auto cfg = mSelf->GetConfig();
	canTakePos.clear();
	for (int i = dir_up; i < dir_max; ++i)
	{
		auto tmpPosX = tarRoleposX + DirOffsetData[i % dir_max].XOffset;
		auto tmpPosY = tarRoleposY + DirOffsetData[i % dir_max].YOffset;
		if (mSelf->CheckTakeGrid(tmpPosX, tmpPosY))
		{
			if (mSelf->IsMonster())
			{
				if (!IsInMoveRange(tmpPosX, tmpPosY))continue;

			}
			else if(mSelf->IsPet())
			{
				if (!IsInMoveRange(tmpPosX, tmpPosY))continue;
			}
			canTakePos.emplace_back(tmpPosX, tmpPosY);
		}
	}
}

void MonsterAI::GetSelfAroundTarget(uint16_t tarRoleposX, uint16_t tarRoleposY, std::vector<pair<uint16_t, uint16_t>>& canTakePos)
{
	auto cfg = mSelf->GetConfig();
	uint16_t maxdis = 999;
	for (int i = dir_up; i < dir_max; ++i)
	{
		auto tmpPosX = mSelf->GetRolePosX() + DirOffsetData[i % dir_max].XOffset;
		auto tmpPosY = mSelf->GetRolePosY() + DirOffsetData[i % dir_max].YOffset;
		if (mSelf->CheckTakeGrid(tmpPosX, tmpPosY))
		{
			if (mSelf->IsMonster())
			{
				if (!IsInMoveRange(tmpPosX, tmpPosY))continue;

			}
			else if (mSelf->IsPet())
			{
				if (!IsInMoveRange(tmpPosX, tmpPosY))continue;
			}
			auto dis = Utility::CalcLongerDistance(tmpPosX, tmpPosY, tarRoleposX, tarRoleposY);
			//auto dis = (tmpPosX - tarRoleposX) * (tmpPosX - tarRoleposX) + (tmpPosY - tarRoleposY) * (tmpPosY - tarRoleposY);
			if (dis == 0)
			{
				canTakePos.emplace_back(tmpPosX, tmpPosY);
				return;
			}
			else
			{
				if (maxdis > dis)
				{
					maxdis = dis;
					canTakePos.clear();
					canTakePos.emplace_back(tmpPosX, tmpPosY);
				}
				else if (maxdis == dis)
				{
					canTakePos.emplace_back(tmpPosX, tmpPosY);
				}
			}
			
		}
	}
}

bool MonsterAI::FindPathByDir(uint16_t curX, uint16_t curY, uint16_t& dir, uint16_t& tarX, uint16_t& tarY)
{
	auto curDir = dir;
	auto tmpPosX = curX + DirOffsetData[curDir].XOffset;
	auto tmpPosY = curY + DirOffsetData[curDir].YOffset;
	if (!mSelf->CheckTakeGrid(tmpPosX, tmpPosY)) {
		curDir = (dir - 1 + dir_max) % dir_max;
		tmpPosX = curX + DirOffsetData[curDir].XOffset;
		tmpPosY = curY + DirOffsetData[curDir].YOffset;
		if (!mSelf->CheckTakeGrid(tmpPosX, tmpPosY)) {
			curDir = (dir + 1) % dir_max;
			tmpPosX = curX + DirOffsetData[curDir].XOffset;
			tmpPosY = curY + DirOffsetData[curDir].YOffset;
			return false;
		}
	}
	dir = curDir;
	tarX = tmpPosX;
	tarY = tmpPosY;
	return true;
}

bool MonsterAI::FindPathByDis(uint16_t posX, uint16_t posY, uint16_t IndirectTarPosX, uint16_t IndirectTarPosY, uint16_t& dir, uint16_t& tarX, uint16_t& tarY)
{
	vector<pair<uint16_t, uint16_t>>canTakePos;
	GetAroundTarget(posX, posY, canTakePos);
	if (canTakePos.empty())return false;
	auto curdis = mSelf->DistanceFromPos(IndirectTarPosX, IndirectTarPosY);
	uint16_t clockWise = 1;
	auto result = Tools::GenerateRandomInteger<uint16_t>(0, clockWise);
	if (result == clockWise)
	{
		uint16_t increment = 0;
		while (increment <= dir_max / 2)
		{
			auto curDir = (dir + increment + dir_max) % dir_max;
			auto tmpPosX = posX + DirOffsetData[curDir].XOffset;
			auto tmpPosY = posY + DirOffsetData[curDir].YOffset;
			if (Utility::CalcLongerDistance(tmpPosX, tmpPosY, IndirectTarPosX, IndirectTarPosY) > curdis)break;
			if (mSelf->CheckTakeGrid(tmpPosX, tmpPosY))
			{
				tarX = tmpPosX;
				tarY = tmpPosY;
				dir = curDir;
				return true;
			}
			++increment;
		}

		uint16_t back_increment = 1;
		for (; back_increment < increment; ++back_increment)
		{
			auto curDir = (dir - back_increment + dir_max) % dir_max;
			auto tmpPosX = posX + DirOffsetData[curDir].XOffset;
			auto tmpPosY = posY + DirOffsetData[curDir].YOffset;
			if (Utility::CalcLongerDistance(tmpPosX, tmpPosY, IndirectTarPosX, IndirectTarPosY) > curdis)break;
			if (mSelf->CheckTakeGrid(tmpPosX, tmpPosY))
			{
				tarX = tmpPosX;
				tarY = tmpPosY;
				dir = curDir;
				return true;
			}
		}

		for (int i = increment; i <= dir_max / 2; ++i)
		{
			auto curDir = (dir + i + dir_max) % dir_max;
			auto tmpPosX = posX + DirOffsetData[curDir].XOffset;
			auto tmpPosY = posY + DirOffsetData[curDir].YOffset;
			if (mSelf->CheckTakeGrid(tmpPosX, tmpPosY))
			{
				tarX = tmpPosX;
				tarY = tmpPosY;
				dir = curDir;
				return true;
			}
		}

		for (int i = back_increment; i <= dir_max / 2; ++i)
		{
			auto curDir = (dir - i + dir_max) % dir_max;
			auto tmpPosX = posX + DirOffsetData[curDir].XOffset;
			auto tmpPosY = posY + DirOffsetData[curDir].YOffset;
			if (mSelf->CheckTakeGrid(tmpPosX, tmpPosY))
			{
				tarX = tmpPosX;
				tarY = tmpPosY;
				dir = curDir;
				return true;
			}
		}

		return false;
	}
	else
	{
		uint16_t increment = 0;
		while (increment <= dir_max / 2)
		{
			auto curDir = (dir - increment + dir_max) % dir_max;
			auto tmpPosX = posX + DirOffsetData[curDir].XOffset;
			auto tmpPosY = posY + DirOffsetData[curDir].YOffset;
			if (Utility::CalcLongerDistance(tmpPosX, tmpPosY, IndirectTarPosX, IndirectTarPosY) > curdis)break;
			if (mSelf->CheckTakeGrid(tmpPosX, tmpPosY))
			{
				tarX = tmpPosX;
				tarY = tmpPosY;
				dir = curDir;
				return true;
			}
			++increment;
		}

		uint16_t back_increment = 1;
		for (; back_increment < increment; ++back_increment)
		{
			auto curDir = (dir + back_increment + dir_max) % dir_max;
			auto tmpPosX = posX + DirOffsetData[curDir].XOffset;
			auto tmpPosY = posY + DirOffsetData[curDir].YOffset;
			if (Utility::CalcLongerDistance(tmpPosX, tmpPosY, IndirectTarPosX, IndirectTarPosY) > curdis)break;
			if (mSelf->CheckTakeGrid(tmpPosX, tmpPosY))
			{
				tarX = tmpPosX;
				tarY = tmpPosY;
				dir = curDir;
				return true;
			}
		}

		for (int i = increment; i <= dir_max / 2; ++i)
		{
			auto curDir = (dir - i + dir_max) % dir_max;
			auto tmpPosX = posX + DirOffsetData[curDir].XOffset;
			auto tmpPosY = posY + DirOffsetData[curDir].YOffset;
			if (mSelf->CheckTakeGrid(tmpPosX, tmpPosY))
			{
				tarX = tmpPosX;
				tarY = tmpPosY;
				dir = curDir;
				return true;
			}
		}

		for (int i = back_increment; i <= dir_max / 2; ++i)
		{
			auto curDir = (dir + i + dir_max) % dir_max;
			auto tmpPosX = posX + DirOffsetData[curDir].XOffset;
			auto tmpPosY = posY + DirOffsetData[curDir].YOffset;
			if (mSelf->CheckTakeGrid(tmpPosX, tmpPosY))
			{
				tarX = tmpPosX;
				tarY = tmpPosY;
				dir = curDir;
				return true;
			}
		}

		return false;
	}

}

bool MonsterAI::FindPathByAStar(uint16_t posX, uint16_t posY, uint16_t IndirectTarPosX, uint16_t IndirectTarPosY,uint16_t& dir, uint16_t& tarX, uint16_t& tarY, uint16_t max_path, uint16_t Max_Depth) 
{
	if (mSelf == nullptr) {
		return false;
	}
	if (!mSelf->GetCurMap()) return false;

    auto *pathFinder = CAStarPathFinder::GetInstance();
	if (!pathFinder) return false;

    bool res = false;
	auto result = pathFinder->FindPathToTarget(make_pair(posX, posY), make_pair(IndirectTarPosX, IndirectTarPosY), Max_Depth, IsAIAttrSet(monster_ai_mAvoidTrap),mSelf->GetCurMap());
	vector<pair<int, int>>finalPath;
	if (result == path_found_target) {
        pathFinder->GetFinalPath(finalPath);
		tarX = finalPath[1].first;
		tarY = finalPath[1].second;
		dir = Utility::CalcRelativeDir(posX, posY, tarX, tarY);
		res = finalPath.size() > max_path ? false : true;
	}
    pathFinder->Clear();
	return res;
}

bool MonsterAI::GetWalkablePos(uint16_t& dir,uint16_t tarRoleposX, uint16_t tarRoleposY,uint16_t& tarX,uint16_t& tarY)
{
	if (nullptr == mSelf || !mSelf->CheckAlive()) {
		return false;
	}

	auto map = mSelf->GetCurMap();
	if (nullptr == map) {
		return false;
	}

	auto posX = mSelf->GetRolePosX();
	auto posY = mSelf->GetRolePosY();
	vector<pair<uint16_t, uint16_t>>canTakePos;
	GetAroundTarget(tarRoleposX, tarRoleposY, canTakePos);
	if (canTakePos.empty()) {
		return FindPathByDis(posX, posY, tarRoleposX, tarRoleposY, dir, tarX, tarY);
	}
	else {
		if (mSelf->CheckCross() || CAStarPathFinder::IsStraightPath(posX, posY, tarRoleposX, tarRoleposY, mSelf,dir)) {
			tarX = posX + DirOffsetData[dir].XOffset;
			tarY = posY + DirOffsetData[dir].YOffset;
			return true;
		}
		if(mAttackPAursuitType == type5_biaoche_non_master)
			return FindPathByAStar(posX, posY, tarRoleposX, tarRoleposY, dir, tarX, tarY, BC_MAX_PATH, BC_MAX_DEPTH);
		else
			return FindPathByAStar(posX, posY, tarRoleposX, tarRoleposY, dir, tarX, tarY);
	}
}

bool MonsterAI::TryMoveToTarget(uint16_t tarX,uint16_t tarY)
{
	if (nullptr == mSelf) {
		return false;
	}

	auto posX = mSelf->GetRolePosX();
	auto posY = mSelf->GetRolePosY();
	auto dir = Utility::CalcRelativeDir(posX, posY, tarX, tarY);
	dir = dir % dir_max;
	uint16_t tmpPosX = 0;
	uint16_t tmpPosY = 0;
	if (GetWalkablePos(dir, tarX, tarY, tmpPosX, tmpPosY) && mSelf->GetRoleMove()->MoveTo(tmpPosX, tmpPosY) == error_ok) {
		mSelf->SetRoleDir(dir);
		mSelf->GetRoleState()->SetState(role_state_walk);
		return true;
	}

	return false;
}

bool MonsterAI::CanHitTarget()
{
	if (!mSelf) return false;
    auto *target = MapRoleMgr::GetInstance()->FindRole(mTarGUID);
    if (!target) return false;

	if (!target->CheckAlive())return false;

	if (!mTriggerSpecialSkill)
	{
		mCurSkillID = GetSkillNumber();
	}
	else
	{
		auto roleskill = mSelf->GetRoleSkill();
		if (!roleskill)return false;
		if (roleskill->IsInCD(mCurSkillID))
		{
			mCurSkillID = GetSkillNumber();
		}
	}

	auto skill = sSkillConfig.GetByID(mCurSkillID);
	if (!skill) return false;

	auto dis = mSelf->DistanceFromRole(target);

	if (dis > skill->CastDistance)
	{
		mCurSkillID = GetMaxDisSkill();
		auto curSkill = sSkillConfig.GetByID(mCurSkillID);
		if (!curSkill) return false;
	}

    auto *skillcfg = sSkillConfig.GetByID(mCurSkillID);
    if (!skillcfg) return false;

    if (dis > skillcfg->CastDistance) return false;

    if (skillcfg->RangeType == skill_range_type_line) {
        if (!mSelf->IsInSameLine(target)) return false;
    }

    return true;
}

bool MonsterAI::LossTarget()
{
	if (nullptr == mSelf)return true;
	auto* target = MapRoleMgr::GetInstance()->FindRole(mTarGUID);
	if (!target) return true;

	if (!target->CheckAlive())return true;

	auto dis = mSelf->DistanceFromRole(target);
	if (mSelf->IsTarInHateValueMap(mTarGUID)) {
		if (dis > mTraRange)return true;
	}
	else {
		if (dis > mVieRange)return true;
	}


	return false;
}

bool MonsterAI::FindTarget(std::string params)
{
	if (mTarGUID)return true;
	//if ((mAttackStatus == monster_attack_non) && IsRoleEnterVieRange())
	//{
	//	auto tar = Monster_GetTarRoleInRange();
	//	if (!tar)return false;
	//	mTarGUID = tar->GetGUID();
	//	return true;
	//}
	return false;
}
bool MonsterAI::TargetHP(std::string params)
{
	auto tar = Monster_GetTarRoleInRange();
	if (!tar)return false;
	auto paramList = str_split(params, ",");
	if (paramList.empty())return false;
	if (paramList.size()!= 2)return false;
	return Utility::CompareFunc(std::stoi(paramList.front()), tar->GetRoleProp(role_hp), tar->GetRoleProp(role_max_hp) * std::stoi(paramList.back()) / 100);

}
bool MonsterAI::SelfHP(std::string params)
{

	if (!mSelf)return false;
	auto paramList = str_split(params, ",");
	if (paramList.empty())return false;
	if (paramList.size() != 2)return false;
	return Utility::CompareFunc(std::stoi(paramList.front()), mSelf->GetRoleProp(role_hp), mSelf->GetRoleProp(role_max_hp) * std::stoi(paramList.back()) / 100);
}
bool MonsterAI::OnDie(std::string params)
{
	if (!mSelf)return false;
	if (mSelf->GetRoleState()->GetState() == role_state_die)return true;
	return false;
}

bool MonsterAI::CurDistance(std::string params)
{
	if (!mSelf)return false;
	auto tar = Monster_GetTarRoleInRange();
	if (!tar)return false;
	auto paramList = str_split(params, ",");
	if (paramList.empty())return false;
	if (paramList.size() != 2)return false;
	auto dis = mSelf->DistanceFromRole(tar);
	return Utility::CompareFunc(std::stoi(paramList.front()), dis, std::stoi(paramList.back()));
}
bool MonsterAI::TargetObj(std::string params)
{
	if (!mSelf)return false;
	auto tar = Monster_GetTarRoleInRange();
	if (!tar)return false;
	auto job = tar->GetRoleProp(role_job);
	return Utility::CompareFunc(charactor_decode::equal, job, std::stoi(params));
}
bool MonsterAI::HarmedBySpecialSkill(std::string params)
{
	//被攻击时触发
	return false;
}

void MonsterAI::SwapSkillGroup(uint16_t id)
{
	if (!mSelf)return;
	auto cfg = sMonsterConfig.GetByKeyName(mSelf->GetName());
	if (cfg == nullptr)return;
	if (cfg->SkillCastingRate.find(id) != cfg->SkillCastingRate.end())
	{
		mCurSkillGroup = cfg->SkillCastingRate[id];
	}
}

void MonsterAI::Escape(uint16_t dis)
{
	auto map = mSelf->GetCurMap();
	if (!map)return;
	auto mapx = map->GetWidth();
	auto mapy = map->GetHeight();
	int x = mSelf->GetRolePosX();
	int y = mSelf->GetRolePosY();
	std::vector<std::pair<int,int>>vec;
	for (auto i = x - dis; i <= x + dis; ++i)
	{
		if (y + dis > mapy) break;
		if (x < 0||x > mapx)continue;
		vec.push_back(std::make_pair(i, y + dis));
	}
	for (auto i = x - dis; i <= x + dis; ++i)
	{
		if (y - dis < 0) break;
		if (x < 0 || x > mapx)continue;
		vec.push_back(std::make_pair(i, y - dis));
	}
	for (auto i = y - dis; i < y + dis; ++i)
	{
		if (x - dis+1 < 0) break;
		if (y < 0 || y > mapy)continue;
		vec.push_back(std::make_pair(x - dis+1,i));
	}
	for (auto i = y - dis; i < y + dis; ++i)
	{
		if (x - dis+1 < 0) break;
		if (x < 0 || x > mapx)continue;
		vec.push_back(std::make_pair(x + dis+1, i));
	}

	if (vec.empty())return;
	auto index = Tools::GenerateRandomInteger<uint32_t>(0,vec.size()-1);

	mTriggerEscape = true;
    mEscapeX = vec[index].first;
    mEscapeY = vec[index].second;
}

Role* MonsterAI::GetNearestRoleByType(uint8_t roleType)
{
	auto map = mSelf->GetCurMap();
	if (!map) return nullptr;
	auto posX = mSelf->GetRolePosX();
	auto posY = mSelf->GetRolePosY();
	if (mSelf->GetConfig()->Enable.find(monster_enable_invDetect) != mSelf->GetConfig()->Enable.end()) {
		return map->GetNearstRoleByType(posX, posY, true, roleType, mSelf);
	}
	else {
		return map->GetNearstRoleByType(posX, posY, false, roleType, mSelf);
	}
}

Role* MonsterAI::Monster_GetTarRoleInRange()
{
	//仇恨值列表不为空
	if (!mSelf->IsEmptyHateValueMap())
	{
		//在视野内仇恨值最大的玩家
		auto role = mSelf->GetMaxHatedValueRole();
	    return role;
	}

	auto player = GetNearestRoleByType(role_type_player);
	auto pet = GetNearestRoleByType(role_type_pet);
    auto doplganr = GetNearestRoleByType(role_type_player_doplganr);

    Role *role = player;
    if (mSelf->DistanceFromRole(pet) < mSelf->DistanceFromRole(player))
        role = pet;

    if (mSelf->DistanceFromRole(doplganr) < mSelf->DistanceFromRole(role))
        role = doplganr;

	return role;
}

Role* MonsterAI::Monster_GetFlushTarRole(int delta)
{
	if (!mTarGUID)
	{
		return Monster_GetTarRoleInRange();
	}
	else
	{
        mTarPlayerTime += delta;
		if (mTarPlayerTime < FLASH_TAR_PLAYER)
		{
			return MapRoleMgr::GetInstance()->FindRole(mTarGUID);
		}
		else
		{
            mTarPlayerTime = 0;
			return Monster_GetTarRoleInRange();
		}
	}
}

bool MonsterAI::GetAssassinatePos(uint16_t x, uint16_t y, std::pair<uint16_t, uint16_t>& pos)
{
	auto player = MapRoleMgr::GetInstance()->FindRole(mTarGUID);
	if (!player)return false;
	auto curx = mSelf->GetRolePosX();
	auto cury = mSelf->GetRolePosY();
	auto tarx = player->GetRolePosX();
	auto tary = player->GetRolePosY();
	auto curdir = Utility::CalcRelativeDir(curx, cury, tarx,tary);
	vector<pair<uint16_t, uint16_t>>canTakePos;
	GetAroundTarget(tarx, tary, canTakePos);
	if (canTakePos.empty())return false;
	for (auto& i : canTakePos)
	{
		auto dir = Utility::CalcRelativeDir( i.first, i.second ,tarx,tary);
		if (dir == curdir)
		{
			pos = std::move(i);
			return true;
		}
	}
	std::sort(canTakePos.begin(), canTakePos.end(), 
		[=](const std::pair<uint16_t, uint16_t>&fir, const std::pair<uint16_t, uint16_t>& sec) {
			return Utility::CalcLongerDistance(curx, cury, fir.first, fir.second) < Utility::CalcLongerDistance(curx, cury, sec.first, sec.second);
		});
	pos = std::move(*canTakePos.begin());
	return true;
}

bool MonsterAI::KeepMaxAttackDis()
{
	if (mSelf->GetRolePosX() == mTarX && mSelf->GetRolePosY()== mTarY)
	{
		mKeepMaxAttackDising = false;
		return true;
	}

	if (TryMoveToTarget(mTarX, mTarY))
	{
		mSelf->GetRoleState()->SetState(role_state_walk);
		return false;
	}
	mKeepMaxAttackDising = false;
	return true;
}

uint16_t MonsterAI::GetSkillNumber()
{
	if (!mSelf)return 0;

	if (mCurSkillGroup.empty())return 0;

	auto tempSkillGroup = mCurSkillGroup;

	auto roleskill = mSelf->GetRoleSkill();
	if (!roleskill)return 0;

	for (auto iter = tempSkillGroup.begin();iter!= tempSkillGroup.end(); )
	{
		if (roleskill->IsInCD(iter->first))
		{
			iter = tempSkillGroup.erase(iter);
			continue;
		}
		++iter;
	}

	uint32_t sum = 0;
	for (auto &i : tempSkillGroup)
	{
		sum += i.second;
	}
	auto randomWeight = Tools::GenerateRandomInteger<uint32_t>(1, sum);
	uint32_t result = 0;
	for (auto &j : tempSkillGroup)
	{
		if ((result += j.second) >= randomWeight)
		{
			return j.first;
		}
	}
	return 0;
}

uint16_t MonsterAI::GetMaxDisSkill()
{
	if (!mSelf) return 0;

	auto *roleskill = mSelf->GetRoleSkill();
	if (!roleskill) return 0;

    uint16_t maxDisSkillID = 0;
    int32_t maxCastDistance = 0;

	for (const auto &iter : mCurSkillGroup)
	{
        const auto &skillID = iter.first;
		if (roleskill->IsInCD(skillID)) continue;

		const auto *skillCfg = sSkillConfig.GetByID(skillID);
        if (!skillCfg) continue;

		if (skillCfg->CastDistance > maxCastDistance)
		{
            maxDisSkillID = skillID;
            maxCastDistance = skillCfg->CastDistance;
		}
	}

	return maxDisSkillID;
}

bool MonsterAI::GetMaxDisPoint()
{
	auto role = MapRoleMgr::GetInstance()->FindRole(mTarGUID);
	if (!role) return false;
	auto tarPoint = std::make_pair(-1,-1);
	auto skillCfg = sSkillConfig.GetByID(mCurSkillID);
	if (!skillCfg) return false;
	auto dis = skillCfg->CastDistance;
	auto dir = Utility::CalcRelativeDir(mSelf->GetRolePosX(), mSelf->GetRolePosY(), role->GetRolePosX(), role->GetRolePosY());
	auto turndir = (dir + 4) % dir_max;

	for (int i = -dis; i < dis; ++i)
	{

		auto tmpPosX = role->GetRolePosX() + i*DirOffsetData[turndir].XOffset;
		auto tmpPosY = role->GetRolePosY() + i*DirOffsetData[turndir].YOffset;
		if (mSelf->CheckTakeGrid(tmpPosX, tmpPosY))
		{
			//if (!IsInMoveRange(tmpPosX, tmpPosY))continue;
			if (!IsInMoveRange(tmpPosX, tmpPosY))continue;
			if (tarPoint.first == -1 && tarPoint.second == -1)
			{
				tarPoint.first = tmpPosX;
				tarPoint.second = tmpPosY;
			}
			else
			{
				auto curDis = mSelf->DistanceFromPos(tarPoint.first, tarPoint.second);
				auto TmpDis = mSelf->DistanceFromPos(tmpPosX, tmpPosY);
				if (TmpDis < curDis)
				{
					tarPoint.first = tmpPosX;
					tarPoint.second = tmpPosY;
				}
			}
		}
	}
	if (tarPoint.first == -1 && tarPoint.second == -1)
		return false;

    mTarX = tarPoint.first;
    mTarY = tarPoint.second;
	return true;
}


///condition
bool MonsterAI::IsRoleEnterVieRange()
{
	auto player = GetNearestRoleByType(role_type_player);
	if (player)
	{
		auto dis = mSelf->DistanceFromRole(player);
		if (dis <= mVieRange)
		{
			if (mAttackPAursuitType % 2 == 1)
			{
				return true;
			}
		}
	}

	auto pet = GetNearestRoleByType(role_type_pet);
	if (pet)
	{
		auto dis = mSelf->DistanceFromRole(pet);
		if (dis <= mVieRange)
		{
			if (mAttackPAursuitType % 2 == 1)
			{
				return true;
			}
		}
	}

	return false;
}

bool MonsterAI::IsHateValueRoleInTraRange()
{
	auto& HateValueMap = mSelf->GetHateValueMap();
	if (HateValueMap.empty())return false;
	for (auto& i : HateValueMap)
	{
		if (i.second.hated_value == 0)continue;
		auto role = MapRoleMgr::GetInstance()->FindRole(i.first);
		if (!role)continue;
		auto dis = mSelf->DistanceFromRole(role);
		if (dis <= mTraRange)
		{
			return true;
		}
	}
	return false;
}

bool MonsterAI::IsEnterAttackState()
{
	if (IsRoleEnterVieRange() || IsHateValueRoleInTraRange())return true;
	return false;
}

bool MonsterAI::IsTrapPoint(uint16_t posx, uint16_t posy)
{
	if (!mSelf)return false;
	auto curmap = mSelf->GetCurMap(); 
	if (!curmap)return false;
	return curmap->IsTrapPoint(posx, posy);
}

bool MonsterAI::IsInVieRange(uint64_t tarGuid)
{
	auto role = MapRoleMgr::GetInstance()->FindRole(tarGuid);
	if (!role) return false;
	auto dis = mSelf->DistanceFromRole(role);
	if (dis > mVieRange)
	{
		return false;
	}
	return true;
}

bool MonsterAI::IsInTraRange(uint64_t tarGuid)
{
	auto role = MapRoleMgr::GetInstance()->FindRole(tarGuid);
	if (!role) return false;
	auto dis = mSelf->DistanceFromRole(role);
	if (dis > mTraRange)
	{
		return false;
	}
	return true;
}

bool MonsterAI::IsInMoveRange(uint16_t x, uint16_t y)
{
	if (mAttackPAursuitType == type4_biaoche_active || mAttackPAursuitType == type4_biaoche_non_active)return true;
	if (mAttackPAursuitType == type5_biaoche_non_master)return true;
	auto dis = mSelf->DistanceFromPos(x, y);
	if ( dis > mMovRange )
	{
		return false;
	}
	return true;
}

bool MonsterAI::IsAIAttrSet(MonsterAI_Attribute attr)
{
    auto it = mAttributeMap.find(attr);
    return it == mAttributeMap.end() ? false : it->second;
}

void MonsterAI::SetCurAttackDir()
{
	auto tarRole = MapRoleMgr::GetInstance()->FindRole(mTarGUID);
	if (!tarRole)return;
	auto dir = Utility::CalcRelativeDir(mSelf->GetRolePosX(), mSelf->GetRolePosY(), tarRole->GetRolePosX(), tarRole->GetRolePosY());
	mSelf->SetRoleDir(dir);
}

void MonsterAI::AddSkill(uint32_t skillID, uint32_t Weight)
{
	auto *skill = sSkillConfig.Get(skillID);
	if (!skill)return;
	auto iter = find_if(mCurSkillGroup.begin(), mCurSkillGroup.end(), [=](const std::pair<int,int>&info) {
		if (info.first == skillID)return true;
		return false;
		});
	if (iter == mCurSkillGroup.end())
	{
		mCurSkillGroup.push_back(std::make_pair(skillID, Weight));
	}
	else
	{
		if (iter->second != Weight)
		{
			iter->second = Weight;
		}
	}
}

void MonsterAI::RemoveSkill(uint32_t skillID)
{
	auto iter = find_if(mCurSkillGroup.begin(), mCurSkillGroup.end(), [=](const std::pair<int, int>& info) {
		if (info.first == skillID)return true;
		return false;
		});
	if (iter != mCurSkillGroup.end())
	{
		mCurSkillGroup.erase(iter);
	}
}

void MonsterAI::UpdateBiaocheAIState()
{
	mAIState = ai_state_idle;
	for (int i = 0; i < ai_schedule_max; ++i) {
		mAISchedule[i] = 0;
		mAIScheduleState[i] = ai_schedule_state_ready;
	}
}

void MonsterAI::UpdateHatedValue(int delta)
{
	if (!mSelf) return;

	if (mSelf->IsEmptyHateValueMap()) {
		ResetAISchedule(ai_schedule_DecreaseHateTime);
		return;
	}

	//mSelf->ClearInvalidHateValue();

	if (IsAIStateScheduleReady(ai_schedule_DecreaseHateTime)) {
		StartAISchedule(ai_schedule_DecreaseHateTime);
	}

	UpdateAISchedule(delta, ai_schedule_DecreaseHateTime);
    
	if (IsAIStateScheduleEnd(ai_schedule_DecreaseHateTime)) {
		mSelf->DecreaseHateValue();
	}
}

void MonsterAI::Update(int delta)
{
	// always update schedule
	AlwaysUpdateSchedule(delta);

	// always run func
	AlwaysRunFunc();

	if (!IsCanEnterState())return;

	switch (mAIState) {
	case ai_state_idle:
		OnStateIdleProc(delta);
		break;
	case ai_state_patrol:
		OnStatePatrolProc(delta);
		break;
	case ai_state_pursure:
		OnStatePursureProc(delta);
		break;
	case ai_state_escape:
		OnStateEscapeProc(delta);
		break;
	case ai_state_attack:
		OnStateAttackProc(delta);
		break;
	case ai_state_attack_idle:
		OnStateAttackIdleProc(delta);
		break;
	case ai_state_follow:
		OnStateFollowProc(delta);
		break;
	case ai_state_reserve_1:
		OnStateReserve1(delta);
		break;
	case ai_state_reserve_2:
		OnStateReserve2(delta);
		break;
	default:
		break;
	}
}

void MonsterAI::SetAIState(uint16_t state)
{
	if (nullptr == mSelf) return;
	if (state == mAIState) return;

	mAIState = state;
	//mTarGUID = 0;
    //mTarItem = 0;

	// 进入状态初始化部分 = enterStateFunc
	switch (state) {
	case ai_state_idle:
		mTarGUID = 0;
	case ai_state_patrol:
		break;
	case ai_state_pursure:
		EnterPursureState();
		break;
	case ai_state_escape:
		break;
	case ai_state_attack_idle:
		mTarGUID = 0;
	default:
		break;
	}
}

void MonsterAI::AlwaysUpdateSchedule(int delta)
{
	UpdateHatedValue(delta);
	UpdateBackState(delta);
	int table[] = { ai_schedule_MoveDelayTime , ai_schedule_AttackTime };
	UpdateAISchedule(delta, table, 2);
}

void MonsterAI::AlwaysRunFunc()
{
	// 防止其他函数改变镖车状态 导致无法移动
	if (mSelf->IsBiaoChe()) {
		if (mAIState != ai_state_idle && mAIState != ai_state_follow) {
			LOG_ERROR("other func change state!!! Cur State:%d", mAIState);
			mAIState = ai_state_follow;
		}
	}
}

bool MonsterAI::IsCanEnterState()
{
	if (IsMoving() || IsAttacking() || IsBacking())return false;

	return CheckSelfState();
}

void MonsterAI::UpdateAISchedule(int delta, int* table, int num)
{
	for (int i = 0; i < num; ++i) {
		if (mAIScheduleState[table[i]] == ai_schedule_state_ready)continue;
		if (mAIScheduleState[table[i]] == ai_schedule_state_end) {
			mAIScheduleState[table[i]] = ai_schedule_state_ready;
			continue;
		}
		if (table[i] > AI_SCHEDULE_DELTAMAX)continue;
		mAISchedule[table[i]] += delta;
		if (mAISchedule[table[i]] > mAIScheduleTime[table[i]]) {
			mAIScheduleState[table[i]] = ai_schedule_state_end;
			mAISchedule[table[i]] = 0;

		}
		else {
			mAIScheduleState[table[i]] = ai_schedule_state_ing;
		}
		
	}
}

void MonsterAI::UpdateAISchedule(int delta, uint16_t idx)
{
	if (mAIScheduleState[idx] == ai_schedule_state_ready) return;
	if (mAIScheduleState[idx] == ai_schedule_state_end) {
		mAIScheduleState[idx] = ai_schedule_state_ready;
		return;
	}
	mAISchedule[idx] += delta;
	if (mAISchedule[idx] > mAIScheduleTime[idx]) {
		mAIScheduleState[idx] = ai_schedule_state_end;
		mAISchedule[idx] = 0;
	}
	else {
		mAIScheduleState[idx] = ai_schedule_state_ing;
	}

}

void MonsterAI::UpdateAIScheduleByStep(int step, int* table, int num)
{
	for (int i = 0; i < num; ++i) {
		if (mAIScheduleState[table[i]] == ai_schedule_state_ready)continue;
		if (mAIScheduleState[table[i]] == ai_schedule_state_end) {
			mAIScheduleState[table[i]] = ai_schedule_state_ready;
			continue;
		}
		if (table[i] < AI_SCHEDULE_STEPMIN || table[i] > AI_SCHEDULE_STEPMAX)continue;
		mAISchedule[table[i]] += step;
		if (mAISchedule[table[i]] >= mAIScheduleTime[table[i]]) {
			mAIScheduleState[table[i]] = ai_schedule_state_end;
			mAISchedule[table[i]] = 0;
		}
		else {
			mAIScheduleState[table[i]] = ai_schedule_state_ing;
		}

	}
}

void MonsterAI::UpdateAIScheduleByStep(int step, uint16_t idx)
{
	if (mAIScheduleState[idx] == ai_schedule_state_ready) return;
	if (mAIScheduleState[idx] == ai_schedule_state_end) {
		mAIScheduleState[idx] = ai_schedule_state_ready;
		return;
	}
	mAISchedule[idx] += step;
	if (mAISchedule[idx] >= mAIScheduleTime[idx]) {
		mAIScheduleState[idx] = ai_schedule_state_end;
		mAISchedule[idx] = 0;
	}
	else {
		mAIScheduleState[idx] = ai_schedule_state_ing;
	}
}

void MonsterAI::ResetAISchedule(int* table, int num)
{
	for (int i = 0; i < num; ++i) {
		mAISchedule[table[i]] = 0;
		mAIScheduleState[table[i]] = ai_schedule_state_ready;
	}
}

void MonsterAI::StartAISchedule(int* table, int num)
{
	for (int i = 0; i < num; ++i) {
		mAIScheduleState[table[i]] = ai_schedule_state_start;
	}
}

bool MonsterAI::IsAIStateScheduleReady(int* table, int num)
{
	for (int i = 0; i < num; ++i) {
		if (mAIScheduleState[table[i]] != ai_schedule_state_ready)
			return false;
	}
	return true;
}

void MonsterAI::OnStateIdleProc(int delta)
{
	auto newState = ChangeIdleState(delta);
	if (newState) {
		ExitIdleState(newState);
		return;
	}
	OnIdleProc(delta);
}

void MonsterAI::OnStatePatrolProc(int delta)
{
	auto newState = ChangePatrolState(delta);
	if (newState) {
		ExitPatrolState(newState);
		return;
	}
	OnPatrolProc(delta);
}

void MonsterAI::OnStatePursureProc(int delta)
{
	auto newState = ChangePursureState(delta);
	if (newState) {
		ExitPursureState(newState);
		return;
	}
	OnPursureProc(delta);
}

void MonsterAI::OnStateAttackIdleProc(int delta)
{
	auto newState = ChangeAttackIdleState(delta);
	if (newState) {
		ExitAttackIdleState(newState);
		return;
	}
	OnAttackIdleProc(delta);
}

void MonsterAI::OnStateAttackProc(int delta)
{
	auto newState = ChangeAttackState(delta);
	if (newState) {
		ExitAttackState(newState);
		return;
	}
	OnAttackProc(delta);
}

void MonsterAI::OnStateEscapeProc(int delta)
{
	auto newState = ChangeEscapeState(delta);
	if (newState) {
		ExitEscapeState(newState);
		return;
	}
	OnEscapeProc(delta);
}

void MonsterAI::OnStateFollowProc(int delta)
{
	auto newState = ChangeFollowState(delta);
	if (newState) {
		ExitFollowState(newState);
		return;
	}
	OnFollowProc(delta);
}

void MonsterAI::OnStatePickItemProc(int delta)
{
	auto newState = ChangePickItemState(delta);
	if (newState) {
		ExitPickItemState(newState);
		return;
	}
	OnPickItemProc(delta);
}

uint16_t MonsterAI::ChangeIdleState(int delta)
{
	// 有目标进入攻击
	if (mTarGUID || IsEnterAttackState())return ai_state_attack;
	// 活动间隔时间走完 判断是否进入巡逻
	if (IsAIStateScheduleEnd(ai_schedule_MovTime)) {
		if (MonsterAI_Type1::GetRandomState())return ai_state_patrol; 
	}
	return ai_state_none;
}

void MonsterAI::OnIdleProc(int delta)
{
	UpdateAISchedule(delta, ai_schedule_MovTime);

	if (IsAIStateScheduleReady(ai_schedule_MovTime)) {
		StartAISchedule(ai_schedule_MovTime);
	}
}

void MonsterAI::ExitIdleState(uint16_t newStateType)
{
	int table[2] = { ai_schedule_MovTime, ai_schedule_idle };
	ResetAISchedule(table, 2);
	SetAIState(newStateType);
}

uint16_t MonsterAI::ChangePatrolState(int delta)
{
	if (IsMoving())return ai_state_none;
	if (mTarGUID || IsEnterAttackState())return ai_state_attack; // 进入攻击
	if (IsAIStateScheduleEnd(ai_schedule_patrol)) return ai_state_idle; //进入待机
	return ai_state_none;
}

void MonsterAI::OnPatrolProc(int delta)
{
	if (IsAIStateScheduleReady(ai_schedule_patrol)){
		StartAISchedule(ai_schedule_patrol);
	}
	// 巡逻动作
	if (ActivePatrol(delta)) {
		ChangeAIStateScheduleState(ai_schedule_patrol, ai_schedule_state_end);
	}
}

void MonsterAI::ExitPatrolState(uint16_t newStateType)
{
	int table[3] = { ai_schedule_MovReadyTime,ai_schedule_patrol,ai_schedule_move };
	ResetAISchedule(table, 3);
	SetAIState(newStateType);
}

uint16_t MonsterAI::ChangePursureState(int delta)
{
	auto newTar = Monster_GetTarRoleInRange();
	if (newTar && newTar->GetGUID() != mTarGUID)return ai_state_attack_idle;
	if (CanHitTarget())return ai_state_attack;       // 进入攻击
	if (LossTarget()) return ai_state_attack_idle;   // 进入攻击待机
	return ai_state_none;
}

void MonsterAI::OnPursureProc(int delta)
{
	UpdateAISchedule(delta, ai_schedule_MovStepTime);

	if (IsAIStateScheduleIng(ai_schedule_MovStepTime)) return;

	// 开始追击状态
	if (IsAIStateScheduleReady(ai_schedule_pursure)){
		StartAISchedule(ai_schedule_pursure);
	}

	// 到达步长 间隔 进入步长间隔等待
	if (IsAIStateScheduleEnd(ai_schedule_MoveStep)&& IsAIStateScheduleEnd(ai_schedule_MoveDelayTime)) {
		StartAISchedule(ai_schedule_MovStepTime);
		StartAISchedule(ai_schedule_MoveStep);
		return;
	}

	// 成功 步长+1
	if (ActivePursure(delta)) {
		if (IsAIStateScheduleReady(ai_schedule_MoveStep)) {
			StartAISchedule(ai_schedule_MoveStep);
		}
		UpdateAIScheduleByStep(1, ai_schedule_MoveStep);
	}
}

void MonsterAI::ExitPursureState(uint16_t newStateType)
{
	int table[3] = { ai_schedule_MoveStep ,ai_schedule_MovStepTime ,ai_schedule_move };
	ResetAISchedule(table, 3);
	SetAIState(newStateType);

	// 达到目标后界定新的活动范围起始点
	SetTmpStayPos(mSelf->GetRolePosX(), mSelf->GetRolePosY());

	SendPursureStateToCl(broadcast_pusure_exit);
}

void MonsterAI::EnterPursureState()
{
	mIsPursueAttacking = false;
	SendPursureStateToCl(broadcast_pursure_enter);
}

uint16_t MonsterAI::ChangeAttackIdleState(int delta)
{
	if (!IsEnterAttackState())return ai_state_idle; // 进入待机
	if (mTarGUID) return ai_state_attack; //进入攻击
	return ai_state_none;
}

void MonsterAI::OnAttackIdleProc(int delta)
{
	auto role = Monster_GetTarRoleInRange();
	if (!role || !role->CheckAlive())return;
	mTarGUID = role->GetGUID();
}

void MonsterAI::ExitAttackIdleState(uint16_t newStateType)
{
	SetAIState(newStateType);
}

uint16_t MonsterAI::ChangeAttackState(int delta)
{
	auto role = Monster_GetFlushTarRole(delta);
	if (!mTarGUID || (role && role->GetGUID() != mTarGUID)) return ai_state_attack_idle;
	if (mIsPursueAttacking)return ai_state_pursure;
	return ai_state_none;
}

void MonsterAI::OnAttackProc(int delta)
{
	UpdateAISchedule(delta, ai_schedule_AttackReadyTime);
	if (IsAIStateScheduleIng(ai_schedule_AttackReadyTime))return;

	ActiveAttack(delta);
	
}

void MonsterAI::ExitAttackState(uint16_t newStateType)
{
	int tab[3] = { ai_schedule_AttackTime ,ai_schedule_AttackReadyTime ,ai_schedule_attack };
	ResetAISchedule(tab, 3);
	SetAIState(newStateType);
}

uint16_t MonsterAI::ChangeEscapeState(int delta)
{
	if (IsAIStateScheduleEnd(ai_schedule_escape))return ai_state_idle;
	return ai_state_none;
}

void MonsterAI::OnEscapeProc(int delta)
{
	if (mSelf && mSelf->GetRolePosX() == mEscapeX && mSelf->GetRolePosY() == mEscapeY){
		ChangeAIStateScheduleState(ai_schedule_escape, ai_schedule_state_end);
		return;
	}

	UpdateAISchedule(delta, ai_schedule_MovStepTime);
	if (IsAIStateScheduleIng(ai_schedule_MovStepTime)) return;

	// 开始逃跑状态
	if (IsAIStateScheduleReady(ai_schedule_escape)) {
		StartAISchedule(ai_schedule_escape);
	}

	// 到达步长 间隔 进入步长间隔等待
	if (IsAIStateScheduleEnd(ai_schedule_MoveStep) && IsAIStateScheduleEnd(ai_schedule_MoveDelayTime)) {
		StartAISchedule(ai_schedule_MovStepTime);
		StartAISchedule(ai_schedule_MoveStep);
		return;
	}

	// 成功 步长+1
	if (ActiveEscape(delta)) {
		if (IsAIStateScheduleReady(ai_schedule_MoveStep)) {
			StartAISchedule(ai_schedule_MoveStep);
		}
		UpdateAIScheduleByStep(1, ai_schedule_MoveStep);
	}
}

void MonsterAI::ExitEscapeState(uint16_t newStateType)
{
	int tab[1] = { ai_schedule_escape };
	ResetAISchedule(tab, 1);
	SetAIState(newStateType);
}

bool MonsterAI::ActiveAttack(int delta)
{
	auto tar = MapRoleMgr::GetInstance()->FindRole(mTarGUID);
	if (!tar || !tar->CheckAlive()){
		mTarGUID = 0;
		return false;
	}

	auto dis = mSelf->DistanceFromRole(tar);
	if (dis > mTraRange){
		mTarGUID = 0;
		return false;
	}

	if (!CanHitTarget()){
		mIsPursueAttacking = true;
		return false;
	}

	if (IsAIStateScheduleReady(ai_schedule_attack)) {
		StartAISchedule(ai_schedule_attack);
	}

	if (IsAIStateScheduleEnd(ai_schedule_AttackTime)) {
		StartAISchedule(ai_schedule_AttackReadyTime);
		return false;
	}

	if (BehaviourAttack(delta)) {
		StartAISchedule(ai_schedule_AttackTime);
		return true;
	}

	return false;
}

bool MonsterAI::ActivePatrol(int delta)
{
	if (!mSelf) return false;

	auto curposX = mSelf->GetRolePosX();
	auto curposY = mSelf->GetRolePosY();

	std::vector<std::pair<uint16_t, uint16_t>> can_walk_point;
	GetAroundTarget(curposX, curposY, can_walk_point);
	auto can_walk_point_num = can_walk_point.size();
	//周围不能走
	if (!can_walk_point_num)
	{
		//改变朝向为随机方向
		auto dir = Tools::GenerateRandomInteger<uint16_t>(dir_up, dir_max - 1);
		mSelf->SetRoleDir(dir);
		return true;
	}

	auto point_index = Tools::GenerateRandomInteger<uint32_t>(0, can_walk_point_num - 1);
	auto tarposX = can_walk_point[point_index].first;
	auto tarposY = can_walk_point[point_index].second;

	if (BehaviourMove(delta, tarposX, tarposY)) return true;
	return false;
}

bool MonsterAI::ActivePursure(int delta)
{
	if (mSelf->GetRoleMove()->IsMoving()) {
		return false;
	}

	auto tarRole = MapRoleMgr::GetInstance()->FindRole(mTarGUID);
	if (!tarRole)return false;
	auto tarX = tarRole->GetRolePosX();
	auto tarY = tarRole->GetRolePosY();

	if (BehaviourMove(delta, tarX, tarY))return true;
	return false;
}

bool MonsterAI::ActiveEscape(int delta)
{
	if (BehaviourMove(delta, mEscapeX, mEscapeY))return true;
	return false;
}

bool MonsterAI::ActiveFollow(int delta)
{
	return false;
}

bool MonsterAI::BehaviourMove(int delta, uint16_t x, uint16_t y)
{
	UpdateAISchedule(delta, ai_schedule_MovReadyTime);

	if (IsAIStateScheduleIng(ai_schedule_MovReadyTime))return false;

	int table[2] = { ai_schedule_MoveDelayTime ,ai_schedule_MovReadyTime };
	if (IsAIStateScheduleReady(table,2)){
		StartAISchedule(ai_schedule_MovReadyTime);
		return false;
	}

	if (IsAIStateScheduleEnd(ai_schedule_MovReadyTime)&&
		IsAIStateScheduleReady(ai_schedule_MoveDelayTime)) {
		// 向目标移动
		if (TryMoveToTarget(x, y)) {
			ChangeAIStateScheduleState(ai_schedule_move, ai_schedule_state_ing);
			StartAISchedule(ai_schedule_MoveDelayTime);
			return true;
		}
	}
	return false;
}

bool MonsterAI::BehaviourAttack(int delta)
{
	auto curSkill = sSkillConfig.GetByID(mCurSkillID);
	if (!curSkill) return false;

	// 保持最大距离
	//if (IsAIAttrSet(monster_ai_mKeepMaxAttackDis) && dis < curSkill->CastDistance)
	//{
	//	if (GetMaxDisPoint())
	//	{
	//		mKeepMaxAttackDising = true;
	//		return;
	//	}
	//}
	
	//2.4.2 释放技能
	SetCurAttackDir();
	ApplySkill();
	//SetAttackTime();
	mTriggerSpecialSkill = false;
	return true;
}

void MonsterAI::SendPursureStateToCl(uint16_t state)
{
	if (!mSelf->IsMonster())return;
	ProtoMS_MonsterPursureAttackingNtf info;
	info.guid = mSelf->GetGUID();
	info.status = state;

	auto pMap = mSelf->GetCurMap();
	if (!pMap) return;

	auto x = mSelf->GetRolePosX();
	auto y = mSelf->GetRolePosY();

	auto f = [&](Role* pRole) {
		NotifyAroundPlayers_PursureStatusChanged(pRole, info);
	};

	pMap->ApplyFuncToAllPlayersInAroundRegions(x, y, f);
}

void MonsterAI::SendBackStateToCl(uint16_t state)
{
	if (!mSelf->IsMonster())return;
	ProtoMS_MonsterBackNtf info;
	info.guid = mSelf->GetGUID();
	info.status = state;

	auto pMap = mSelf->GetCurMap();
	if (!pMap) return;

	auto x = mSelf->GetRolePosX();
	auto y = mSelf->GetRolePosY();

	auto f = [&](Role* pRole) {
		NotifyAroundPlayers_BackStatusChanged(pRole, info);
	};

	pMap->ApplyFuncToAllPlayersInAroundRegions(x, y, f);
}

void MonsterAI::UpdateBackState(int delta)
{
	if (IsMoving() || IsAttacking())return;

	if (IsAIStateScheduleStart(ai_schedule_back)) {
		StartAISchedule(ai_schedule_BackTime);
		ChangeAIStateScheduleState(ai_schedule_back, ai_schedule_state_ing);
		SendBackStateToCl(broadcast_back_enter);
	}

	UpdateAISchedule(delta, ai_schedule_BackTime);

	if (IsAIStateScheduleEnd(ai_schedule_BackTime)) {
		int table[2] = { ai_schedule_BackTime ,ai_schedule_back };
		ResetAISchedule(table, 2);
		SendBackStateToCl(broadcast_back_exit);
	}
}