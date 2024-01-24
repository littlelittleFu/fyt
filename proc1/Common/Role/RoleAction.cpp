#include "stdafx.h"
#include "RoleAction.h"
#include "Role.h"

RoleAction::RoleAction(Role* master) : mMaster(master) {
	Register(master);
}

RoleAction::~RoleAction() {
	auto master = GetMaster();
	if (nullptr != master) {
		this->UnRegister(master);
	}
}

const std::string & RoleAction::GetScriptName()
{
	if (nullptr != mMaster) {
		return mMaster->GetScriptName();
	}
	return EMPTYSTR;
}

void RoleAction::SetNeedUpdate(int flag)
{
    auto *master = GetMaster();
    if (!master) return;
    master->SetNeedUpdateFlag(flag);
}

void RoleAction::ResetNeedUpdate(int flag)
{
    auto *master = GetMaster();
    if (!master) return;
    master->ResetNeedUpdateFlag(flag);
}

Player * RoleAction::GetPlayer()
{
    auto *self = GetMaster();
    if (!self || !self->IsPlayer()) return nullptr;
    return static_cast<Player *>(self);
}

PlayerDoplganr * RoleAction::GetPlayerDoplganr()
{
    auto *self = GetMaster();
    if (!self || !self->IsPlayerDoplganr()) return nullptr;
    return static_cast<PlayerDoplganr *>(self);
}
