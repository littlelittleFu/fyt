#include "stdafx.h"
#include "RoleAvatar.h"

RoleAvatar::RoleAvatar(Role* master) : RoleAction(master)
, HelmetID(0)
, ClothesID(0)
, WeaponID(0)
, ManWeaponID(0)
, WManWeaponID(0)
, WeaponItemID(0)
, WingsID(0)
, MountID(0)
, MountShadowID(0)
, MountItemID(0)
, ShadowID(0)
, WeaponEffect(0)
, BodyEffect(0)
, MountEffect(0)
, MagicWeapID(0)
, ShieldID(0)
, HairColor(0)
, HairStyle(0)
, Header(0)
{

}

RoleAvatar::~RoleAvatar()
{
}

bool RoleAvatar::Init()
{
	return true;
}

void RoleAvatar::Update(int32_t delta)
{

}