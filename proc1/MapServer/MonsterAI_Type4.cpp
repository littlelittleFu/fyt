#include"stdafx.h"
#include "MonsterAI_Type4.h"

MonsterAI_Type4::MonsterAI_Type4()
{
	mRange      = 0;
	mFinished   = false;
	mFinalRange = FINAL_RANGE_4;
}

MonsterAI_Type4::~MonsterAI_Type4()
{

}

bool MonsterAI_Type4::TarIsInRange()
{
	auto player = mSelf->GetMaster();

	if (!player) return false;

	auto dis = mSelf->DistanceFromRole(player);
	if (dis > mRange) return false;

	return true;
}

void MonsterAI_Type4::InitParams(const std::string& guid, uint32_t X, uint32_t Y, uint32_t range, uint16_t finalRange)
{
	mSelf->SetMasterGUID(std::stoull(guid));
    mTarX = X;
    mTarY = Y;
	mRange = range;
	mFinalRange = finalRange;
}

bool MonsterAI_Type4::IsFinshed()
{
	if (mFinished)return true;
	if (!mSelf) return true;
	auto dis = mSelf->DistanceFromPos(mTarX, mTarY);
	if (dis <= mFinalRange)
	{
		mFinished = true;
		TRIGGER_EVENT(mSelf, trigger_monster_biaoche_arrived, mSelf->GetGUIDAsString(), mSelf->GetConfig()->Id,
			mSelf->GetRolePosX(), mSelf->GetRolePosY());
		return true;
	}
	return false;
}

uint16_t MonsterAI_Type4::ChangeIdleState(int delta)
{
	if (IsFinshed())return ai_state_none;
	if (TarIsInRange())return ai_state_follow;
	return ai_state_none;
}

void MonsterAI_Type4::OnIdleProc(int delta)
{

}

void MonsterAI_Type4::ExitIdleState(uint16_t newStateType)
{
	SetAIState(newStateType);
}

uint16_t MonsterAI_Type4::ChangeFollowState(int delta)
{
	if (IsFinshed() || !TarIsInRange() || IsAIStateScheduleEnd(ai_schedule_follow))return ai_state_idle;
	return ai_state_none;
}

void MonsterAI_Type4::OnFollowProc(int delta)
{

	UpdateAISchedule(delta, ai_schedule_MovStepTime);
	if (IsAIStateScheduleIng(ai_schedule_MovStepTime)) return;

	// 开始跟随
	if (IsAIStateScheduleReady(ai_schedule_follow)) {
		StartAISchedule(ai_schedule_follow);
	}

	// 到达步长 间隔 进入步长间隔等待
	if (IsAIStateScheduleEnd(ai_schedule_MoveStep) && IsAIStateScheduleEnd(ai_schedule_MoveDelayTime)) {
		StartAISchedule(ai_schedule_MovStepTime);
		StartAISchedule(ai_schedule_MoveStep);
		return;
	}

	// 成功 步长+1
	if (ActiveFollow(delta)) {
		if (IsAIStateScheduleReady(ai_schedule_MoveStep)) {
			StartAISchedule(ai_schedule_MoveStep);
		}
		UpdateAIScheduleByStep(1, ai_schedule_MoveStep);
	}
}

void MonsterAI_Type4::ExitFollowState(uint16_t newStateType)
{
	int table[4] = { ai_schedule_MovReadyTime, ai_schedule_follow ,
		ai_schedule_MoveStep ,ai_schedule_MovStepTime };
	ResetAISchedule(table, 4);
	SetAIState(newStateType);
}

bool MonsterAI_Type4::ActiveFollow(int delta)
{
	//主动移动型镖车
	if (mAttackPAursuitType == type4_biaoche_active)
	{
		if (BehaviourMove(delta, mTarX, mTarY))return true;
		return false;
	}

	//被动移动型镖车
	auto player = mSelf->GetMaster();
	if (!player) return false;
	auto dis = mSelf->DistanceFromRole(player);
	if (dis <= 1)
	{
		ChangeAIStateScheduleState(ai_schedule_follow, ai_schedule_state_end);
		return false;
	}

	if (BehaviourMove(delta, player->GetRolePosX(), player->GetRolePosY()))return true;
	return false;
}

