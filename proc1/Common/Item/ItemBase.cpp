#include "stdafx.h"
#include "ItemBase.h"
#include "CustVarMgr.h"

ItemBase::ItemBase(const ItemBase* item)
{
	InitWithBaseItem(item);
}

ItemBase::ItemBase(const ITEM_INFO* item)
{
    InitWithBaseItemInfo(item);
}

void ItemBase::InitWithBaseItem(const ItemBase* item)
{
	if (nullptr == item) {
		return;
	}

	SetGUID(item->GetGUID());
    SetName(item->GetName());
	mLife = item->GetLife();
    mTempid = item->GetTemplateID();
    mCategory = item->GetCategory();
    mCustVars.insert(item->mCustVars.begin(), item->mCustVars.end());
    mDynAttrs.assign(item->mDynAttrs.begin(),item->mDynAttrs.end());
}

void ItemBase::InitWithBaseItemInfo(const ITEM_INFO* item)
{
    if (nullptr == item) {
        return;
    }

    SetGUID(item->base_info.guid);
    SetName(item->base_info.name);
    mLife = item->base_info.life;
    mTempid = item->base_info.id;
    //mCategory = item->GetCategory();

    CUST_VAR_LIST custVarsList;
    DYN_ATTRS dynAttrsList;
    (*const_cast<ITEM_INFO*>(item)).custom >> custVarsList;
    (*const_cast<ITEM_INFO*>(item)).custom >> dynAttrsList;
    for (auto& var : custVarsList)
    {
        SetCustVar(var);
    }
    for (auto& var : dynAttrsList)
    {
        SetDynAttr(var.index, var.attr, var.value);
    }
}

void ItemBase::GenerateBaseItemInfo(ITEM_INFO& item)
{
    item.base_info.guid = GetGUID();
    item.base_info.id = mTempid;
    strcpy_s(item.base_info.name, sizeof(item.base_info.name), GetName().c_str());
    item.base_info.life = mLife;
    item.custom.num = 0;
    item.custom << mCustVars;
    item.custom << mDynAttrs;
}

void ItemBase::SetCustVar(std::string name, std::string value, const uint8_t &type, bool& beDelete)
{
    CustVarMgr::GetInstance()->SetValue(mCustVars, GetGUID(), std::move(name), std::move(value), type, beDelete);
}

void ItemBase::SetCustVar(CUST_VAR& cv)
{
    CustVarMgr::GetInstance()->SetValue(mCustVars, cv);
}

const std::string & ItemBase::GetCustVar(const std::string &name, bool& beDelete)
{
    return CustVarMgr::GetInstance()->GetValue(mCustVars, name, beDelete);
}

const CUST_VAR_SP& ItemBase::GetCustVarSP(const std::string& name, bool& beDelete)
{
    return CustVarMgr::GetInstance()->GetCustVarSP(mCustVars, name, beDelete);
}
void ItemBase::SetDynAttr(uint16_t index, uint16_t attr, int32_t value)
{
    auto it = std::find_if(mDynAttrs.begin(), mDynAttrs.end(), [&](const auto &attr) { return attr.index == index; });
    if (it == mDynAttrs.end()) {
        mDynAttrs.emplace_back(index, attr, value);
    }
    else {
        it->attr = attr;
        it->value = value;
    }
}

DYN_ATTR ItemBase::GetDynAttr(uint16_t index)
{
    DYN_ATTR dynAttr;

    auto it = std::find_if(mDynAttrs.begin(), mDynAttrs.end(), [&](const auto &attr) { return attr.index == index; });
    if (it == mDynAttrs.end()) return dynAttr;

    dynAttr = *it;
    return dynAttr;
}
