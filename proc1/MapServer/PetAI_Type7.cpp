#include "stdafx.h"
#include "PetAI_Type7.h"

PetAI_Type7::PetAI_Type7(): mHateTime(0)
{

}

void PetAI_Type7::DefendStatusLogic(int delta)
{

}

bool PetAI_Type7::IsHateTime(int delta)
{
	auto hateTime = sGlobalConfig.GetData()->PetHateTime;
	auto role = MapRoleMgr::GetInstance()->FindRole(mTarGUID);
	if (!role)return false;

	auto &hatevalue = mSelf->GetHateValueMap();
	auto iter = hatevalue.find(mTarGUID);
	if (iter != hatevalue.end())
	{
		mHateTime = 0;
		return true;
	}

	mHateTime += delta;
	if (mHateTime >= hateTime)
	{
		mTarGUID = 0;
		mHateTime = 0;
		return false;
	}
	return true;
}

uint16_t PetAI_Type7::ChangeIdleStateInActiveLogic(int delta)
{
	auto dis = mSelf->DistanceFromRole(mSelf->GetMaster());
	if(mTarGUID || Pet_IsMonsterEnterVieRange())return ai_state_attack;
	if (IsCanPickItem())return ai_state_pickitem;
	if (dis > FOLLOW_DIS && dis < FOLLOW_RANGE)return ai_state_follow;
	return ai_state_none;
}

void PetAI_Type7::OnIdleProc(int delta)
{
	JumpToMasterWhenOutOfRange();
}

uint16_t PetAI_Type7::ChangeFollowStateInActiveLogic(int delta)
{
	auto dis = mSelf->DistanceFromRole(mSelf->GetMaster());
	if (mTarGUID || Pet_IsMonsterEnterVieRange())return ai_state_attack;
	if (IsCanPickItem())return ai_state_pickitem;
	if (dis <= FOLLOW_DIS || dis > FOLLOW_RANGE)return ai_state_idle;
	return ai_state_none;
}

uint16_t PetAI_Type7::ChangePickItemStateInActiveLogic(int delta)
{
	if (mTarGUID || Pet_IsMonsterEnterVieRange())return ai_state_attack;
	if (!IsCanPickItem())return ai_state_idle;
	return ai_state_none;
}

uint16_t PetAI_Type7::ChangePursureStateInActiveLogic(int delta)
{
	if (CanHitTarget())return ai_state_attack;       // 进入攻击
	if (LossTarget()) return ai_state_attack_idle;   // 进入攻击待机
	return ai_state_none;
}

uint16_t PetAI_Type7::ChangeAttackStateInActiveLogic(int delta)
{
	if (!mTarGUID) return ai_state_attack_idle;   // 进入攻击待机
	if (mIsPursueAttacking)return ai_state_pursure;
	return ai_state_none;
}

uint16_t PetAI_Type7::ChangeAttackIdleStateInActiveLogic(int delta)
{
	if (!Pet_IsMonsterEnterVieRange())return ai_state_idle;
	if (mTarGUID) return ai_state_attack; //进入攻击
	return ai_state_none;
}
