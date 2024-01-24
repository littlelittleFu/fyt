#include "stdafx.h"
#include "RoleItem.h"

RoleItem::RoleItem(const RoleItem& item) : ItemBase(&item)
{
	InitWithRoleItem(&item);
    SetCategory(item_cat_player);
}

RoleItem::RoleItem(const RoleItem* item) : ItemBase(item)
{
	InitWithRoleItem(item);
    SetCategory(item_cat_player);
}

RoleItem::RoleItem(const ITEM_INFO& item) : ItemBase(&item)
{
	InitWithItemInfo(&item);
    SetCategory(item_cat_player);
}

RoleItem::RoleItem(const ITEM_INFO* item) : ItemBase(item)
{
	InitWithItemInfo(item);
    SetCategory(item_cat_player);
}

void RoleItem::UpdateDurability(int mount)
{
	int32_t max = 0;
	if (mount > 0)
	{
		max = mMax_durability - mDurability;
		mount > max ? mount = max : 1;
	}
	else if (mount < 0)
	{
		max = -mDurability;
		mount < max ? mount = max : 1;
	}
	mDurability += mount;
}

void RoleItem::GenerateItemInfo(ITEM_INFO& item)
{
	GenerateBaseItemInfo(item);

	item.base_info.role = mRoleid;
	item.base_info.site = mSite;
	item.base_info.amount = mAmount;
	item.base_info.durability = mDurability;
	item.base_info.max_durability = mMax_durability;
	item.base_info.use_count = mUse_count;
	item.base_info.is_bound = mIsBind;
	item.base_info.item_cfg_var.subtype = mItem_Cfg_Var.subtype;
	item.base_info.item_cfg_var.color = mItem_Cfg_Var.color;
	item.base_info.item_cfg_var.icon = mItem_Cfg_Var.icon;
	item.base_info.item_cfg_var.quality = mItem_Cfg_Var.quality;
}

void RoleItem::InitWithRoleItem(const RoleItem* item)
{
	if (nullptr == item) {
		return;
	}

	mCD = item->GetCD();
	mRoleid = item->GetRoleid();
	mSite = item->GetSite();
	mAmount = item->GetAmount();
	mDurability = item->GetDurability();
	mMax_durability = item->GetMaxDurability();
	mUse_count = item->GetUse_count();
	mIsBind = item->GetIsBind();
	mUseTime = item->GetUseTime();
	mItem_Cfg_Var.subtype = item->GetSubType();
	mItem_Cfg_Var.color = item->GetColor();
	mItem_Cfg_Var.icon = item->GetIcon();
	mItem_Cfg_Var.quality = item->GetQuality();
}

void RoleItem::InitWithItemInfo(const ITEM_INFO* item)
{
	if (nullptr == item) {
		return;
	}

	mCD = 0;
	mRoleid = item->base_info.role;
	mSite = item->base_info.site;
	mAmount = item->base_info.amount;
	mDurability = item->base_info.durability;
	mMax_durability = item->base_info.max_durability;
	mUse_count = item->base_info.use_count;
	mIsBind = item->base_info.is_bound;
	mUseTime = 0;
	mItem_Cfg_Var.color = item->base_info.item_cfg_var.color;
	mItem_Cfg_Var.icon = item->base_info.item_cfg_var.icon;
	mItem_Cfg_Var.quality = item->base_info.item_cfg_var.quality;
	mItem_Cfg_Var.subtype = item->base_info.item_cfg_var.subtype;

}

