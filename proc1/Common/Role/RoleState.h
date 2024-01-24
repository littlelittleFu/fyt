#pragma once

#include "RoleAction.h"
enum Role_State
{
	role_state_none,						//无效状态
	role_state_idle,						//待机
	role_state_battle_idle,					//战斗待机
	role_state_walk,						//走路
	role_state_run,							//跑步
	role_state_gather,						//采集
	role_state_attack,						//攻击
	role_state_skill,						//技能
	role_state_damage,						//被攻击
	role_state_die,							//死亡
	role_state_rush,						//冲撞
	role_state_back,						//击退
	role_state_follow,						//跟随
	role_state_stall,						//摆摊
	role_state_trade,						//交易
	role_state_joinhit,						//合击
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
