#include "stdafx.h"
#include "FightInfoMgr.h"

void FightInfo::Update(int32_t delta)
{
	curTime += delta;
	if (curTime < 2000) return;
	
	for (auto iter = mAttackTargetInfoList.begin(); iter != mAttackTargetInfoList.end();)
	{
		if (!MapRoleMgr::GetInstance()->FindRole(iter->guid))
		{
			iter = mAttackTargetInfoList.erase(iter);
			continue;
		}
		iter->remainedtime += curTime;
		if (iter->remainedtime > INFOREMAINEDTIME)
		{
			iter = mAttackTargetInfoList.erase(iter);
			continue;
		}
		++iter;
	}

	for (auto iter = mBeAttackedInfoList.begin(); iter != mBeAttackedInfoList.end();)
	{ 
		if (!MapRoleMgr::GetInstance()->FindRole(iter->guid))
		{
			iter = mBeAttackedInfoList.erase(iter);
			continue;
		}
		iter->remainedtime += curTime;
		if (iter->remainedtime > INFOREMAINEDTIME)
		{
			iter = mBeAttackedInfoList.erase(iter);
			continue;
		}
		++iter;
	}

	if (mAttackTargetInfoList.empty() && mBeAttackedInfoList.empty())
	{
		mMaster->ResetNeedUpdateFlag(fight_info_need_update_flag);
	}
	curTime = 0;
}

void FightInfo::AddAttackTargetInfo(uint64_t guid, uint32_t skillID)
{
	auto iter = find_if(mAttackTargetInfoList.begin(), mAttackTargetInfoList.end(), [=](const Info & info) {
		if (guid == info.guid)
			return true;
		return false;
		});
	if (iter != mAttackTargetInfoList.end())
	{
		iter->remainedtime = 0;
		iter->skillID = skillID;
	}
	else
	{
		Info tmpinfo(guid,skillID);
		mAttackTargetInfoList.push_back(tmpinfo);
	}
}

void FightInfo::AddBeAttackedInfo(uint64_t guid, uint32_t skillID)
{
	auto iter = find_if(mBeAttackedInfoList.begin(), mBeAttackedInfoList.end(), [=](const Info& info) {
		if (guid == info.guid)
			return true;
		return false;
		});
	if (iter != mBeAttackedInfoList.end())
	{
		iter->remainedtime = 0;
		iter->skillID = skillID;
	}
	else
	{
		Info tmpinfo(guid, skillID);
		mBeAttackedInfoList.push_back(tmpinfo);
	}
}

void FightInfo::GetLatestAttackTarget(std::vector<Info>& vec)
{
	if (mAttackTargetInfoList.empty())return;
	for_each(mAttackTargetInfoList.begin(), mAttackTargetInfoList.end(), [&](const Info&info ) {
		if (vec.empty())
		{
			vec.push_back(info);
			return;
		}

		if (info.remainedtime < vec[0].remainedtime)
		{
			vec.clear();
			vec.push_back(info);
		}
		else if (info.remainedtime == vec[0].remainedtime)
		{
			vec.push_back(info);
		}
	});
}

void FightInfo::GetLatestBeAttackedOwner(std::vector<Info>& vec)
{
	if (mBeAttackedInfoList.empty())return;
	for_each(mBeAttackedInfoList.begin(), mBeAttackedInfoList.end(), [&](const Info& info) {
		if (vec.empty())
		{
			vec.push_back(info);
			return;
		}

		if (info.remainedtime < vec[0].remainedtime)
		{
			vec.clear();
			vec.push_back(info);
		}
		else if (info.remainedtime == vec[0].remainedtime)
		{
			vec.push_back(info);
		}
	});
}
