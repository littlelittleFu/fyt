#include"stdafx.h"
#include"MonsterAI_Type1.h"

#define MON_MAX_PATH 6       //怪物寻路最多寻路点
#define MON_MAX_DEPTH 50         //怪物寻路最大深度

MonsterAI_Type1::RandomState  MonsterAI_Type1::mAss;

MonsterAI_Type1::RandomState::RandomState()
{
	GenerateRandomState();
}

MonsterAI_Type1::RandomState::~RandomState()
{

}


bool MonsterAI_Type1::ActivePursure(int delta)
{
	if (mSelf->GetRoleMove()->IsMoving()) {
		return false;
	}

	auto tarRole = MapRoleMgr::GetInstance()->FindRole(mTarGUID);
	if (!tarRole)return false;
	auto tarX = tarRole->GetRolePosX();
	auto tarY = tarRole->GetRolePosY();
	//寻路4步   然后能走到  就走寻路  如果走不到就随机
	uint16_t tmpDir = 0;
	uint16_t tmpPosX = 0;
	uint16_t tmpPosY = 0;
	auto randomnum = Tools::GenerateRandomInteger<uint16_t>(0, 100);
	if (randomnum > 80 && FindPathByAStar(mSelf->GetRolePosX(), mSelf->GetRolePosY(), tarX, tarY, tmpDir,tmpPosX, tmpPosY, MON_MAX_PATH, MON_MAX_DEPTH))
	{
		return MonsterAI::ActivePursure(delta);
	}
	else
	{
		//取怪物身边的点 和目标最近的点作为目标点
		std::vector<std::pair<uint16_t, uint16_t>> can_walk_point;
		GetSelfAroundTarget(tarX, tarY, can_walk_point);
		if (can_walk_point.size() > 0)
		{
			randomnum = Tools::GenerateRandomInteger<uint16_t>(0, can_walk_point.size() - 1);

			if (BehaviourMove(delta, can_walk_point[randomnum].first, can_walk_point[randomnum].second))return true;
		}
		return false;
	}
}

void MonsterAI_Type1::RandomState::GenerateRandomState()
{
	mIdx = 0;
	bt = Tools::GenerateRandomInteger<uint64_t>(UINT64_MAX / 2, UINT64_MAX);
}

bool MonsterAI_Type1::RandomState::GetRandomState()
{
	bool res = bt.test(mIdx++);
	if (mIdx >= bt.size())
	{
		GenerateRandomState();
	}
	return res;
}

MonsterAI_Type1::MonsterAI_Type1()
{

}

MonsterAI_Type1::~MonsterAI_Type1()
{

}

bool MonsterAI_Type1::GetRandomState()
{
	return mAss.GetRandomState();
}