#include"stdafx.h"
#include"MonsterAI_Type3.h"

MonsterAI_Type3::MonsterAI_Type3()
{

}

MonsterAI_Type3::~MonsterAI_Type3()
{

}

uint16_t MonsterAI_Type3::ChangeIdleState(int delta)
{
	if (mTarGUID || IsEnterAttackState())return ai_state_attack;
	return ai_state_none;
}

void MonsterAI_Type3::OnIdleProc(int delta)
{

}
void MonsterAI_Type3::ExitIdleState(uint16_t newStateType)
{
	SetAIState(newStateType);
}

uint16_t MonsterAI_Type3::ChangeAttackState(int delta)
{
	auto role = Monster_GetFlushTarRole(delta);
	if (!mTarGUID || (role && role->GetGUID() != mTarGUID)) return ai_state_attack_idle;
	return ai_state_none;
}

void MonsterAI_Type3::OnAttackProc(int delta)
{
	UpdateAISchedule(delta, ai_schedule_AttackReadyTime);
	if (IsAIStateScheduleIng(ai_schedule_AttackReadyTime))return;

	ActiveAttack(delta);
}

void MonsterAI_Type3::ExitAttackState(uint16_t newStateType)
{
	int tab[3] = { ai_schedule_AttackTime ,ai_schedule_AttackReadyTime ,ai_schedule_attack };
	ResetAISchedule(tab, 3);
	SetAIState(newStateType);
}

bool MonsterAI_Type3::BehaviourAttack(int delta)
{
	auto cfg = mSelf->GetConfig();
	if (cfg == nullptr)return false;
	if (cfg->Enable.find(monster_enable_canTurn) == cfg->Enable.end())
	{
		SetCurAttackDir();
	}
	ApplySkill();
	mTriggerSpecialSkill = false;
	return true;
}

bool MonsterAI_Type3::ActiveAttack(int delta)
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

	if (IsAIStateScheduleReady(ai_schedule_attack)) {
		StartAISchedule(ai_schedule_attack);
	}

	if (IsAIStateScheduleEnd(ai_schedule_AttackTime)) {
		StartAISchedule(ai_schedule_AttackReadyTime);
		return false;
	}

	// 获取技能
	if (!CanHitTarget()) {
		mTarGUID = 0;
		return false;
	};

	if (BehaviourAttack(delta)) {
		StartAISchedule(ai_schedule_AttackTime);
		return true;
	}

	return false;
}