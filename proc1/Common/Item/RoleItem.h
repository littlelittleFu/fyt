#pragma once

#include <string.h>
#include "ItemBase.h"


class RoleItem :public ItemBase
{
public:
	RoleItem() {SetCategory(item_cat_player);};
	RoleItem(const RoleItem& item);
	RoleItem(const RoleItem* item);
	RoleItem(const ITEM_INFO& item);
	RoleItem(const ITEM_INFO* item);
	 ~RoleItem() {};

	void SetCD(unsigned short guid) { mCD = guid; }
	unsigned short GetCD() const { return mCD; }
	
	void SetRoleid(uint64_t  tempid) { mRoleid = tempid; }
	uint64_t  GetRoleid() const { return mRoleid; }

	void SetSite(unsigned short   tempid) { mSite = tempid; }
	unsigned short   GetSite() const { return mSite; }

	void SetAmount(unsigned short mount) { mAmount = mount; }
	unsigned short GetAmount() const { return mAmount; }

	void SetDurability(int  mount) { mDurability = mount; }
	void UpdateDurability(int  mount);
	int  GetDurability() const { return mDurability; }

	void SetMaxDurability(int  mount) { mMax_durability = mount; }
	int  GetMaxDurability() const { return mMax_durability; }

	void SetUse_count(unsigned short mount) { mUse_count = mount; }
	unsigned short GetUse_count() const { return mUse_count; }

	void SetIsBind(unsigned char  mount) { mIsBind = (mount == bind_on_pick_up ? true : false); }
	unsigned char  GetIsBind() const { return mIsBind; }

	void SetUseTime(uint64_t time) { mUseTime = time; }
	uint64_t  GetUseTime() const { return mUseTime; }

	void SetSubType(uint32_t subtype) { mItem_Cfg_Var.subtype = subtype; };
	uint32_t GetSubType()const { return mItem_Cfg_Var.subtype; };

	void SetColor(uint32_t color) { mItem_Cfg_Var.color = color; }
	uint32_t GetColor()const { return mItem_Cfg_Var.color; }

	void SetIcon(uint64_t icon) { mItem_Cfg_Var.icon = icon; }
	uint64_t GetIcon()const { return mItem_Cfg_Var.icon; }

	void SetQuality(uint32_t quality) { mItem_Cfg_Var.quality = quality; }
	uint32_t GetQuality()const { return mItem_Cfg_Var.quality; }

	void GenerateItemInfo(ITEM_INFO& item);
protected:
	void InitWithRoleItem(const RoleItem* item);
	void InitWithItemInfo(const ITEM_INFO* item);

protected:
	unsigned short			  mCD = 0;
	uint64_t                  mRoleid = 0;
	unsigned short            mSite = 0; 
	unsigned short            mAmount = 0;
	int                       mDurability = 0;
	int                       mMax_durability=0; 
	unsigned short            mUse_count=0; 
	unsigned char             mIsBind = 0;
	uint64_t                  mUseTime = 0;
	ITEM_CFG_VAR              mItem_Cfg_Var;
};


