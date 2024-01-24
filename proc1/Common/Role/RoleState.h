#pragma once

#include "RoleAction.h"
enum Role_State
{
	role_state_none,						//��Ч״̬
	role_state_idle,						//����
	role_state_battle_idle,					//ս������
	role_state_walk,						//��·
	role_state_run,							//�ܲ�
	role_state_gather,						//�ɼ�
	role_state_attack,						//����
	role_state_skill,						//����
	role_state_damage,						//������
	role_state_die,							//����
	role_state_rush,						//��ײ
	role_state_back,						//����
	role_state_follow,						//����
	role_state_stall,						//��̯
	role_state_trade,						//����
	role_state_joinhit,						//�ϻ�
};

class RoleState : public RoleAction
{
public:
	RoleState(Role* master = nullptr);
	~RoleState();

public:
	bool Init() override;
	void Update(int32_t delta) override;

	void SetState(uint8_t state) { mState = state; }
	uint8_t GetState() { return mState; }

	void UpdateOtherStatusByProp(int32_t prop, int32_t predValue, int32_t curValue);
	bool CheckAlive() { return mState != role_state_die; }
protected:
	uint8_t mState;
};
