#include "stdafx.h"
#include "RoleEquip.h"

RoleEquip::RoleEquip(Role* master) : RoleAction(master)
{

}

RoleEquip::~RoleEquip()
{

}

bool RoleEquip::Init()
{
	return true;
}

void RoleEquip::Update(int32_t delta)
{

}