#pragma once
#include"MonsterAI.h"
#include"Monster.h"
#include"logic_def.hpp"

#define WAITING_ATTACK_INTERVAL 1000   ///�ȴ�ʱ����

//��������
class MonsterAI_Type2 :public MonsterAI
{
public:
	MonsterAI_Type2();
	~MonsterAI_Type2();

	//�Ƿ��ֹ���Ŀ��
	bool Type2_IsEnterPursureOrAttackState();
	bool Type2_IsRedNameEnterVieRange();

	Role* Type2_GetFlushTarPlayer(int delta);
	Role* Type2_GetTarRoleInRange();

	bool Type2_ActiveAttack(int delta);

	uint16_t ChangeIdleState(int delta) override;
	void OnIdleProc(int delta) override;
	void ExitIdleState(uint16_t newStateType) override;

	uint16_t ChangeAttackState(int delta) override;
	void OnAttackProc(int delta) override;
	void ExitAttackState(uint16_t newStateType) override;

	uint16_t ChangeAttackIdleState(int delta) override;
	void OnAttackIdleProc(int delta) override;
	void ExitAttackIdleState(uint16_t newStateType) override;

};