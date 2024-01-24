#include "stdafx.h"
#include "RoleState.h"

RoleState::RoleState(Role* master) : RoleAction(master)
, mState(role_state_idle)
{
}

RoleState::~RoleState()
{

}

bool RoleState::Init()
{
	return true;
}

void RoleState::Update(int32_t delta)
{
	
}

void RoleState::UpdateOtherStatusByProp(int32_t prop, int32_t predValue, int32_t curValue)
{
	switch (prop)
	{
		case role_hp: break;
	}
}
