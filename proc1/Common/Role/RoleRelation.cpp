#include "stdafx.h"
#include "RoleRelation.h"

RoleRelation::RoleRelation(Role* master) : RoleAction(master)
{
	memset(family_name, 0, sizeof(family_name));
	memset(castle_name, 0, sizeof(castle_name));
	memset(family_title, 0, sizeof(family_title));
	memset(master_name, 0, sizeof(master_name));
	memset(lover_name, 0, sizeof(lover_name));

}

RoleRelation::~RoleRelation()
{

}

bool RoleRelation::Init()
{
	return true;
}

void RoleRelation::Update(int32_t delta)
{

}