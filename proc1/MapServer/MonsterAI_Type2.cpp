#include"stdafx.h"
#include"MonsterAI_Type2.h"

MonsterAI_Type2::MonsterAI_Type2()
{
}

MonsterAI_Type2::~MonsterAI_Type2()
{

}

bool MonsterAI_Type2::Type2_IsEnterPursureOrAttackState()
{
	//是否有红名玩家在视野范围
	if (Type2_IsRedNameEnterVieRange())
		return true;
	if (!mSelf->IsEmptyHateValueMap())
	{
		auto player = mSelf->GetMaxHatedValueRole();
		if (player)
		{
			return true;
		}
	}
	return false;
}

bool MonsterAI_Type2::Type2_IsRedNameEnterVieRange()
{
	auto map = mSelf->GetCurMap();
	if (!map) return false;
	auto posX = mSelf->GetRolePosX();
	auto posY = mSelf->GetRolePosY();
	auto player = map->GetNeatstRoleByCustType(posX, posY, cust_role_red_name, mSelf);
	if (!player) return false;
	auto dis = player->DistanceFromPos(posX, posY);
	if (dis > mVieRange)
	{
		return false;
	}
	return true;
}

Role* MonsterAI_Type2::Type2_GetFlushTarPlayer(int delta)
{
	if (!mTarGUID)
	{
		return Type2_GetTarRoleInRange();
	}
	else
	{
        mTarPlayerTime += delta;
		if (mTarPlayerTime < FLASH_TAR_PLAYER)
		{
			return MapRoleMgr::GetInstance()->FindPlayer(mTarGUID);
		}
		else
		{
            mTarPlayerTime = 0;
			return Type2_GetTarRoleInRange();
		}
	}
}

Role* MonsterAI_Type2::Type2_GetTarRoleInRange()
{
	Player* player = nullptr;
	//仇恨值列表不为空
	if (!mSelf->IsEmptyHateValueMap())
	{
		//在视野内仇恨值最大的玩家
		player = mSelf->GetMaxHatedValueRedNameRole();
		if (player)
		{
			if(player->IsRedName())return player;
		}
	}
	auto curmap = mSelf->GetCurMap();
	auto tmplayer = curmap->GetNeatstRoleByCustType(mSelf->GetRolePosX(), mSelf->GetRolePosY(), cust_role_red_name, mSelf);
	if (tmplayer)
	{
		if (IsInVieRange(tmplayer->GetGUID()))return tmplayer;
	}
	return player;

}

bool MonsterAI_Type2::Type2_ActiveAttack(int delta)
{
	auto tar = MapRoleMgr::GetInstance()->FindRole(mTarGUID);
	if (!tar || !tar->CheckAlive()) {
		mTarGUID = 0;
		return false;
	}

	auto dis = mSelf->DistanceFromRole(tar);
	if (dis > mTraRange || dis > mVieRange) {
		mTarGUID = 0;
		return false;
	}

	UpdateAISchedule(delta, ai_schedule_Type2StayTime);
	UpdateAISchedule(delta, ai_schedule_AttackReadyTime);
	if (IsAIStateScheduleIng(ai_schedule_Type2StayTime))return false;
	if (IsAIStateScheduleIng(ai_schedule_AttackReadyTime))return false;

	// 攻击完成回到原地等待
	if (IsAIStateScheduleEnd(ai_schedule_AttackTime)) {
		if (mSelf->GetRolePosX() != mBornPosX || mSelf->GetRolePosY() != mBornPosY)
		{
			if (!mSelf->JumpMap(mBornPosX, mBornPosY))return false;
		}
		StartAISchedule(ai_schedule_Type2StayTime);
		return false;
	}

	// 等待完成 进入攻击流程
	if (IsAIStateScheduleEnd(ai_schedule_Type2StayTime)|| IsAIStateScheduleReady(ai_schedule_attack)){
		StartAISchedule(ai_schedule_attack);
		if (dis > 1){
			auto pos = std::pair<uint16_t, uint16_t>();
			if (!GetAssassinatePos(tar->GetRolePosX(), tar->GetRolePosY(), pos)) {
				mTarGUID = 0;
				return false;
			}
			if (!mSelf->JumpMap(pos.first, pos.second)) {
				mTarGUID = 0;
				return false;
			}
		}
		StartAISchedule(ai_schedule_AttackReadyTime);
		return false;
	}

	// 攻击
	if (IsAIStateScheduleEnd(ai_schedule_AttackReadyTime)) {
		// 获取技能
		CanHitTarget();
		if (BehaviourAttack(delta)) {
			StartAISchedule(ai_schedule_AttackTime);
			return true;
		}
	}
	return true;
}

uint16_t MonsterAI_Type2::ChangeIdleState(int delta)
{
	if (mTarGUID || Type2_IsEnterPursureOrAttackState())return ai_state_attack;
	return ai_state_none;
}

void MonsterAI_Type2::OnIdleProc(int delta)
{

}

void MonsterAI_Type2::ExitIdleState(uint16_t newStateType)
{
	SetAIState(newStateType);
}

uint16_t MonsterAI_Type2::ChangeAttackState(int delta)
{
	auto role = Type2_GetFlushTarPlayer(delta);
	if (!mTarGUID || (role && role->GetGUID() != mTarGUID)) return ai_state_attack_idle;
	return ai_state_none;
}

void MonsterAI_Type2::OnAttackProc(int delta)
{
	UpdateAISchedule(delta, ai_schedule_AttackReadyTime);
	if (IsAIStateScheduleIng(ai_schedule_AttackReadyTime))return;

	Type2_ActiveAttack(delta);
}

void MonsterAI_Type2::ExitAttackState(uint16_t newStateType)
{
	int tab[3] = { ai_schedule_AttackTime ,ai_schedule_AttackReadyTime ,ai_schedule_attack };
	ResetAISchedule(tab, 3);
	SetAIState(newStateType);
}

uint16_t MonsterAI_Type2::ChangeAttackIdleState(int delta)
{
	if (!Type2_IsEnterPursureOrAttackState())return ai_state_idle; // 进入待机
	if (mTarGUID) return ai_state_attack; //进入攻击
	return ai_state_none;
}

void MonsterAI_Type2::OnAttackIdleProc(int delta)
{
	auto role = Type2_GetTarRoleInRange();
	if (!role || !role->CheckAlive())return;
	mTarGUID = role->GetGUID();
}

void MonsterAI_Type2::ExitAttackIdleState(uint16_t newStateType)
{
	SetAIState(newStateType);
}
