#pragma once
#include"MonsterAI.h"
#include"Monster.h"
#include"logic_def.hpp"

// ÿ≥«Œ¿±¯–Õ
class MonsterAI_Type3 :public MonsterAI
{
public:
	MonsterAI_Type3();
	~MonsterAI_Type3();

	uint16_t ChangeIdleState(int delta) override;
	void OnIdleProc(int delta) override;
	void ExitIdleState(uint16_t newStateType) override;

	uint16_t ChangeAttackState(int delta) override;
	void OnAttackProc(int delta) override;
	void ExitAttackState(uint16_t newStateType) override;

	bool BehaviourAttack(int delta) override;
	bool ActiveAttack(int delta) override;


};