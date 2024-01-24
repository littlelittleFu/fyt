#include"stdafx.h"
#include "MonsterAI_Type5.h"

MonsterAI_Type5::MonsterAI_Type5()
{
	mFinalRange = FINAL_RANGE_5;
	mFinished = false;
	mPosRange = 0;
}

MonsterAI_Type5::~MonsterAI_Type5()
{

}

void MonsterAI_Type5::InitParams(const std::string& guid,uint32_t X, uint32_t Y, uint16_t finalRange,  const std::string& func, uint8_t posRange, const CLuaObject posTable)
{
	mSelf->SetMasterGUID(std::stoull(guid));
    mTarX = X;
    mTarY = Y;
	mFunc = func;
	mFinalRange = finalRange;
	mPosRange = posRange;
	if (luabind::type(posTable) != LUA_TTABLE)return;
	std::pair<uint32_t, uint32_t> pos;
	for (luabind::iterator it(posTable), end; it != end; ++it) {
		if (luabind::type(*it) != LUA_TTABLE)return;
		if (luabind::type((*it)[1]) != LUA_TNUMBER)return;
		if (luabind::type((*it)[2]) != LUA_TNUMBER)return;
		pos.first = luabind::object_cast<uint32_t>((*it)[1]);
		pos.second = luabind::object_cast<uint32_t>((*it)[2]);
		mPos.emplace_back(pos);
	}
}

bool MonsterAI_Type5::IsFinshed()
{
	if (mFinished)return true;
	if (!mSelf) return true;
	auto dis = mSelf->DistanceFromPos(mTarX, mTarY);
	if (dis <= mFinalRange)
	{
		mFinished = true;
		LuaBindCallVoid(mFunc, mSelf->GetGUIDAsString());
		TRIGGER_EVENT(mSelf, trigger_monster_biaoche_arrived, mSelf->GetGUIDAsString(), mSelf->GetConfig()->Id,
			mSelf->GetRolePosX(), mSelf->GetRolePosY());
		return true;
	}
	return false;
}

uint16_t MonsterAI_Type5::ChangeIdleState(int delta)
{
	if (!IsFinshed())return ai_state_follow;
	return ai_state_none;
}

void MonsterAI_Type5::OnIdleProc(int delta)
{

}

void MonsterAI_Type5::ExitIdleState(uint16_t newStateType)
{
	SetAIState(newStateType);
}

uint16_t MonsterAI_Type5::ChangeFollowState(int delta)
{
	if (IsFinshed())return ai_state_idle;
	return ai_state_none;
}

void MonsterAI_Type5::OnFollowProc(int delta)
{

	UpdateAISchedule(delta, ai_schedule_MovStepTime);
	if (IsAIStateScheduleIng(ai_schedule_MovStepTime)) return;

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

void MonsterAI_Type5::ExitFollowState(uint16_t newStateType)
{
	int table[3] = { ai_schedule_MovReadyTime ,
		ai_schedule_MoveStep ,ai_schedule_MovStepTime };
	ResetAISchedule(table, 3);
	SetAIState(newStateType);
}

bool MonsterAI_Type5::ActiveFollow(int delta)
{
	if (nullptr == mSelf)return false;

	if (mPos.empty()) {
		if (BehaviourMove(delta, mTarX, mTarY))return true;
	}
	else{
		auto dis = mSelf->DistanceFromPos(mPos[0].first, mPos[0].second);
		if (dis <= mPosRange) {
			mPos.erase(mPos.begin());
			if (mPos.empty()) {
				if (BehaviourMove(delta, mTarX, mTarY))return true;
			}
			else {
				if (BehaviourMove(delta, mPos[0].first, mPos[0].second))return true;
			}
		}
		else{
			if (BehaviourMove(delta, mPos[0].first, mPos[0].second))return true;

		}
	}

	return false;
}