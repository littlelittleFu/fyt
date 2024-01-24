#include "stdafx.h"
#include "RoleTeam.h"

RoleTeam::RoleTeam(Role* master) : RoleAction(master)
{

}

RoleTeam::~RoleTeam()
{

}

bool RoleTeam::Init()
{
	return true;
}

void RoleTeam::Update(int32_t delta)
{
}

void RoleTeam::Clear()
{
	 mTeamGUID = 0;
	 if (!mMaster || !mMaster->IsPlayer()) return;
	 TRIGGER_EVENT(mMaster, trigger_team, mMaster->GetGUIDAsString(), std::to_string(mTeamGUID));
}

void RoleTeam::SetTeamGUID(uint64_t guid)
{ 
	mTeamGUID = guid;
	if (!mMaster || !mMaster->IsPlayer()) return;
	TRIGGER_EVENT(mMaster, trigger_team, mMaster->GetGUIDAsString(), std::to_string(mTeamGUID));
}

uint64_t RoleTeam::GetTeamGUID()
{ 
	return mTeamGUID;
}