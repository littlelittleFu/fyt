#include "stdafx.h"
#include "RolePack.h"
#include "ProtoMS.h"
#include "RolePack.h"
#include "item_table.hpp"
#include "skill_table.hpp"
#include "Player.h"
#include "Map.h"
#include "ItemMap.h"
#include "CustomEquipSiteAndSub.h"
#include "playerdrop_table.hpp"

RolePack::RolePack(Role* master) : RoleAction(master), mSuitCounter(master)
{
    mItemList.resize(site_end, nullptr);
    mCustVarList.clear();
    mDybAttrsList.clear();
}

RolePack::~RolePack()
{
	for (int32_t i = 0; i < site_end;++i) {

        if (mItemList.at(i)) {
            ItemMap::GetInstance()->RemoveItem(mItemList.at(i)->GetGUID());
        }

		SAFE_RELEASE(mItemList.at(i));
	}
}

bool RolePack::Init()
{
    mSuitCounter.ClearAllSuit();
    InitEquipUpdateProp();
	return true;
}

void RolePack::Update(int32_t delta)
{
}

void RolePack::ClearAllItems()
{
    for (int32_t i = 0; i < site_end; ++i) {
        SAFE_RELEASE(mItemList.at(i));
    }
}

void RolePack::CopyFromOwner(RoleAction* ra)
{
    if (!mMaster) return;
    auto rolePack = static_cast<RolePack*>(ra);
    if (!rolePack) return;

    static const std::pair<item_site, item_site> siteRanges[] = {{ site_weapon,site_equip_end }, {site_glasses,site_equip_custom_end }, { site_fashion_helmet,site_fashion_end }};
    for (auto& siteRange : siteRanges)
    {
        for (uint16_t site = siteRange.first; site < siteRange.second; ++site)
        {
            if (!rolePack->mItemList[site]) continue;

            RoleItem* addItem = new RoleItem(rolePack->mItemList[site]);
            // rolePack
            addItem->SetGUID(rolePack->mItemList[site]->GetGUID());
            addItem->SetRoleid(mMaster->GetGUID());
            mItemList[site] = addItem;
        }
    }

    mCustVarList = rolePack->mCustVarList;
    mDybAttrsList = rolePack->mDybAttrsList;
}

uint16_t RolePack::GetEquipSiteByType(int32_t type)
{
    if (type >= equip_custom_0 && type < equip_custom_end)
    {
        vector<uint16_t>vec;
        if (!CustomEquipSiteAndSub::GetInstance()->FindSiteBySub(type, vec)) return site_nullptr;
        for (auto i : vec)
        {
            if (mItemList.at(i))continue;
            return i;
        }
        return *vec.begin();
    }
	switch (type) {
	case equip_weapon:
		return site_weapon;
	case equip_helmet:
		return site_helmet;
	case equip_wrist:
		return uint16_t(mItemList.at(site_wrist_0) ? site_wrist_1 : site_wrist_0);
	case equip_armor:
		return site_armor;
	case equip_juju:
		return site_juju;
	case equip_shoes:
		return site_shoes;
	case equip_shoulder:
		return site_shoulder;
	case equip_necklace:
		return site_necklace;
	case equip_ring:
		return uint16_t(mItemList.at(site_ring_0) ? site_ring_1 : site_ring_0);
	case equip_medal:
		return site_medal;
	case equip_gem:
		return site_gem;
	case equip_wings:
		return site_wings;
	case equip_amulet:
		return site_amulet;
	case equip_mount:
		return site_mount;
	case equip_shield:
		return site_shield;
	case equip_fashion:
		return site_fashion;
	case equip_hat:
		return site_hat;
	case equip_gloves:
		return site_gloves;
	case equip_jewelry:
		return site_jewelry;

	default:
		return site_nullptr;
	}
}

uint16_t RolePack::GetItemSite(const uint64_t itemGUID)
{
	if (itemGUID > 0) {
		for (uint16_t i = site_weapon; i < site_end; ++i) {
			if (nullptr != mItemList.at(i) && mItemList.at(i)->GetGUID() == itemGUID) {
				return i;
			}
		}
	}
	return INVALID_ITEM_SITE;
}

uint16_t RolePack::GetItemSiteInEquip(const uint64_t itemGUID)
{
    if (itemGUID > 0) {
        for (uint16_t i = site_weapon; i < site_equip_end; ++i) {
            if (nullptr != mItemList.at(i) && mItemList.at(i)->GetGUID() == itemGUID) {
                return i;
            }
        }
    }
    return INVALID_ITEM_SITE;
}

uint16_t RolePack::GetItemSiteInBag(const uint64_t itemGUID)
{
	if (itemGUID > 0) {
		for (uint16_t i = site_bag_0; i < site_warehouse; ++i) {
			if (nullptr != mItemList.at(i) && mItemList.at(i)->GetGUID() == itemGUID) {
				return i;
			}
		}
	}
	return INVALID_ITEM_SITE;
}

uint16_t RolePack::GetItemSiteInWareHouse(const uint64_t itemGUID)
{
    if (itemGUID > 0) {
        for (uint16_t i = site_warehouse; i < site_warehouse_adv; ++i) {
            if (nullptr != mItemList.at(i) && mItemList.at(i)->GetGUID() == itemGUID) {
                return i;
            }
        }
    }
    return INVALID_ITEM_SITE;
}

uint16_t RolePack::GetItemSiteInAdvWareHouse(const uint64_t itemGUID)
{
    if (itemGUID > 0) {
        for (uint16_t i = site_warehouse_adv; i < site_bag_end; ++i) {
            if (nullptr != mItemList.at(i) && mItemList.at(i)->GetGUID() == itemGUID) {
                return i;
            }
        }
    }
    return INVALID_ITEM_SITE;
}

uint16_t RolePack::GetIdleBagSite()
{
    auto count = GetTotalBagCount();
	for (uint16_t i = site_bag_0; i < site_bag_0 + count; ++i) {
		if (nullptr == mItemList.at(i)) {
			return i;
		}
	}
	return INVALID_ITEM_SITE;
}

uint16_t RolePack::GetIdleBagCount()
{
    auto total = GetTotalBagCount();

    uint16_t count = 0;
	for (uint16_t i = site_bag_0; i < site_bag_0 + total; ++i) {
		if (nullptr == mItemList.at(i)) {
			++count;
		}
	}
	return count;
}

uint16_t RolePack::GetTotalBagCount()
{
    auto *master = GetMaster();
    if (!master) return 0;

    uint16_t count = 0;
    for (uint16_t i = 0; i < 5; ++i) {
        auto num = master->GetRoleProp(role_bag_size_0 + i);
        count += static_cast<uint16_t>(num);
    }

    return count;
}
#define CASE(type) case equip_##type: return site_##type == site;

bool RolePack::IsCanUseEquipSiteByType(uint32_t type, uint32_t site)
{
    if (type >= equip_custom_0 && type < equip_custom_end)
    {
        vector<uint16_t>vec;
        if (!CustomEquipSiteAndSub::GetInstance()->FindSiteBySub(type, vec)) return false;
        if (vec.empty())return false;
        if (find(vec.begin(), vec.end(), site) == vec.end())return false;
        return true;
    }

    #define CASE(type) case equip_##type: return site_##type == site;
    #define CASE1(type) case equip_##type: return (site_##type##_0 == site) || (site_##type##_1 == site);

    switch (type) {
        CASE(weapon)
        CASE(helmet)
        CASE1(wrist)
        CASE(armor)
        CASE(juju)
        CASE(shoes)
        CASE(shoulder)
        CASE(necklace)
        CASE1(ring)
        CASE(medal)
        CASE(gem)
        CASE(wings)
        CASE(amulet)
        CASE(mount)
        CASE(shield)
        CASE(fashion)
        CASE(hat)
        CASE(gloves)
        CASE(jewelry)

        CASE(glasses)
        CASE1(bracelet)
        CASE(mask)
        CASE(kneelet)
        CASE(chestplate)
        CASE(cloak)
        CASE(earrings)
        CASE(headwear)
        CASE(legguard)
        CASE(jade)
        CASE(instrument)
        CASE(hangings)
        CASE(fashion_weapon)

        CASE(fashion_helmet)
        CASE1(fashion_wrist)
        CASE(fashion_armor)
        CASE(fashion_juju)
        CASE(fashion_shoes)
        CASE(fashion_shoulder)
        CASE(fashion_necklace)
        CASE1(fashion_ring)
        CASE(fashion_medal)
        CASE(fashion_gem)
        CASE(fashion_wings)
        CASE(fashion_amulet)
        CASE(fashion_mount)
        CASE(fashion_shield)
        CASE(fashion_hat)
        CASE(fashion_gloves)
        CASE(fashion_jewelry)

        CASE(fashion_glasses)
        CASE1(fashion_bracelet)
        CASE(fashion_mask)
        CASE(fashion_kneelet)
        CASE(fashion_chestplate)
        CASE(fashion_cloak)
        CASE(fashion_earrings)
        CASE(fashion_headwear)
        CASE(fashion_legguard)
        CASE(fashion_jade)
        CASE(fashion_instrument)
        CASE(fashion_hangings)
    default:
        return false;
    }
}

bool RolePack::IsItemExist(const uint64_t itemGUID)
{
    return GetItemSite(itemGUID) != INVALID_ITEM_SITE;
}

bool RolePack::IsItemExistInEquip(const uint64_t itemGUID)
{
    return GetItemSiteInEquip(itemGUID) != INVALID_ITEM_SITE;
}

bool RolePack::IsItemExistInBag(const uint64_t itemGUID)
{
    return GetItemSiteInBag(itemGUID) != INVALID_ITEM_SITE;
}

bool RolePack::IsItemExistInWareHouse(const uint64_t itemGUID)
{
    return GetItemSiteInWareHouse(itemGUID) != INVALID_ITEM_SITE;
}

bool RolePack::IsItemExistInAdvWareHouse(const uint64_t itemGUID)
{
    return GetItemSiteInAdvWareHouse(itemGUID) != INVALID_ITEM_SITE;
}

uint16_t RolePack::AddItemToBag(uint16_t tempID, const log_params& lp)
{
	auto itemCfg = sItemConfig.Get(tempID);
	if (nullptr == itemCfg) {
		return INVALID_ITEM_SITE;
	}

	auto site = GetIdleBagSite();
    if (site == INVALID_ITEM_SITE) {
        return INVALID_ITEM_SITE;
    }

    RoleItem* addItem = GenerateRoleItemByItemCfg(itemCfg, site);
    if (nullptr == addItem) return INVALID_ITEM_SITE;

	mItemList.at(site) = addItem;
	NtfMasterAddItem(site);
    OnAddItem(site, lp);

	return site;
}

uint16_t RolePack::AddItemToBag(RoleItem& item, const log_params& lp)
{
	return AddItemToBag(&item, lp);
}

uint16_t RolePack::AddItemToBag(RoleItem* item, const log_params& lp)
{
	if (nullptr == item) {
		return INVALID_ITEM_SITE;
	}

	if (IsItemExistInBag(item->GetGUID())) {
		return INVALID_ITEM_SITE;
	}

	auto site = GetIdleBagSite();
    if (site == INVALID_ITEM_SITE) {
        return INVALID_ITEM_SITE;
    }

    RoleItem* addItem = GenerateRoleItemByRoleItem(item, site);
    if (nullptr == addItem) return INVALID_ITEM_SITE;

    mItemList.at(site) = addItem;
	NtfMasterAddItem(site);
    OnAddItem(site, lp);

	return site;
}

bool RolePack::AddItem(const ITEM_INFO& item, const log_params& lp)
{
	return AddItem(&item, lp);
}

bool RolePack::AddItem(const ITEM_INFO* item, const log_params& lp)
{
	if (nullptr == item || item->base_info.site >= site_end) {
		return false;
	}

	if (nullptr != mItemList.at(item->base_info.site)) {
		return false;
	}

	if (IsItemExist(item->base_info.guid)) {
		return false;
	}

	mItemList.at(item->base_info.site) = new RoleItem(item);
    InitItemCustVarList(item->base_info.guid);
    InitItemDynAttrsList(item->base_info.guid);

	NtfMasterAddItem(item->base_info.site);
    OnAddItem(item->base_info.site, lp);
	return true;
}

int RolePack::AddItem(uint16_t nTemplateID, uint16_t nNum, bind_type nBind, site_range nSiteRange, const log_params& lp)
{
    auto pItemCfg = sItemConfig.Get(nTemplateID);
    if (!pItemCfg) return ERR_ITEM_NO_DATA_ROW;

    auto &nStack = pItemCfg->Stack;
    int nLeft = nNum;

    int nSiteBegin, nSiteEnd;
    GetSiteRange(nSiteRange, nSiteBegin, nSiteEnd);

    for (auto i = nSiteBegin; i < nSiteEnd && nLeft > 0; ++i) {

        auto pItem = mItemList.at(i);

        if (!pItem) {
            nLeft -= nStack;
            continue;
        }

        if (pItem->GetTemplateID() != nTemplateID) continue;

        if ((pItem->GetIsBind() > 0) == (nBind == bind_on_pick_up ? true : false))
            nLeft -= nStack - pItem->GetAmount();
    }

    if (nLeft > 0) return ERR_BAG_SPACE_NOT_ENOUGH;

    auto nOwnerID = GetMaster()->GetGUID();
    nLeft = nNum;

    std::vector<int> freeSitevec;
    for (auto i = nSiteBegin; i < nSiteEnd && nLeft > 0; ++i) {

        auto &pItem = mItemList.at(i);

        if (!pItem)
        {
            freeSitevec.push_back(i);
            continue;
        }

        if (pItem->GetTemplateID() != nTemplateID) continue;

        if ((pItem->GetIsBind() > 0) != (nBind == bind_on_pick_up ? true : false)) continue;

        auto curAmount = pItem->GetAmount();
        auto nCapacity = nStack - curAmount;
        if (nCapacity == 0) continue;

        if (nLeft > nCapacity) {
            pItem->SetAmount(nStack);
            OnUpdateItem(pItem->GetSite(), nCapacity, curAmount, lp);
            nLeft -= nCapacity;
        }
        else {
            pItem->SetAmount(curAmount + nLeft);
            OnUpdateItem(pItem->GetSite(), nLeft, curAmount, lp);
            nLeft = 0;
        }

        const_cast<log_params*>(&lp)->site = pItem->GetSite();
        NtfMasterUpdateItem(pItem->GetSite());
    }
    auto iter = freeSitevec.begin();
    for (; iter != freeSitevec .end() && nLeft > 0; ++iter)
    {
        auto i = *iter;
        auto& pItem = mItemList.at(i);
        if (pItem) continue;

        pItem = GenerateRoleItemByItemCfg(pItemCfg, i);
        if (!pItem) return ERR_ITEM_ADD;
        pItem->SetIsBind(nBind);

        if (nLeft > nStack) {
            pItem->SetAmount(nStack);
            nLeft -= nStack;
        }
        else {
            pItem->SetAmount(nLeft);
            nLeft = 0;
        }

        const_cast<log_params*>(&lp)->site = i;
        NtfMasterAddItem(i);
        OnAddItem(i, lp);
    }
    return ERR_OK;
}

int RolePack::AddItemByKeyName(const std::string &sKeyName, uint16_t nNum, uint8_t bBind, uint8_t nJob, uint16_t nSite, site_range nSiteRange, const log_params& lp)
{
    auto pItemCfg = sItemConfig.Get(sKeyName);
    if (!pItemCfg) return ERR_ITEM_NO_DATA_ROW;

    int res = AddItem(pItemCfg->Id, nNum, static_cast<bind_type>(bBind), nSiteRange, lp);
    if (res == ERR_OK && site_nullptr != nSite && mItemList.at(lp.site))
    {
        MoveItem(mItemList.at(lp.site)->GetGUID(), nSite);
    }
    return res;// TODO: consider nJob
}

uint64_t RolePack::AddSingleItem(uint16_t nTemplateID, uint16_t nNum, bind_type nBind, const log_params& lp)
{
    auto pItemCfg = sItemConfig.Get(nTemplateID);
    if (!pItemCfg) return 0;
    if (nNum > pItemCfg->Stack) return 0;
    auto site = GetIdleBagSite();

    auto& pItem = mItemList.at(site);
    if (pItem) return 0;

    pItem = GenerateRoleItemByItemCfg(pItemCfg, site);
    if (!pItem) return ERR_ITEM_ADD;
    pItem->SetIsBind(nBind);
    pItem->SetAmount(nNum);

    NtfMasterAddItem(site);
    OnAddItem(site, lp);

    return pItem->GetGUID();
}

int RolePack::AddItems(const CLuaObject &luaObj, site_range nSiteRange, const log_params& lp)
{
    struct ItemInfo
    {
        DATA::Item *pItemCfg        = nullptr;
        uint16_t    nNum            = 0;
        bool        bBind           = false;
        uint8_t     nJob            = 0;
    };

    std::list<ItemInfo> itemInfoList;

    ItemInfo itemInfo;

    for (luabind::iterator it(luaObj), end; it != end; ++it) {

        auto obj = *it;

        const auto &itemKeyName = obj[1];
        if (luabind::type(itemKeyName) != LUA_TSTRING) return ERR_ITEM_ADD;
        auto sItemKeyName = luabind::object_cast<std::string>(itemKeyName);
        itemInfo.pItemCfg = sItemConfig.Get(sItemKeyName);
        if (!itemInfo.pItemCfg) return ERR_ITEM_NO_DATA_ROW;

        const auto &itemNum = obj[2];
        if (luabind::type(itemNum) != LUA_TNUMBER) return ERR_ITEM_ADD;
        itemInfo.nNum = luabind::object_cast<uint16_t>(itemNum);

        const auto &bind = obj[3];
        if (luabind::type(bind) != LUA_TNUMBER) return ERR_ITEM_ADD;
        itemInfo.bBind = luabind::object_cast<uint8_t>(bind);

        const auto &job = obj[4];
        if (luabind::type(job) != LUA_TNUMBER) return ERR_ITEM_ADD;
        itemInfo.nJob = luabind::object_cast<uint8_t>(job);

        bool bMerged = false;
        for (auto &it : itemInfoList) {

            if (it.pItemCfg == itemInfo.pItemCfg && it.bBind == itemInfo.bBind && it.nJob == itemInfo.nJob) {

                it.nNum += itemInfo.nNum;
                bMerged = true;
                break;
            }
        }

        if (!bMerged) itemInfoList.push_back(itemInfo);
    }

    if (itemInfoList.empty()) return ERR_OK;

    std::list<ItemInfo> itemInfoListCopy = itemInfoList;

    int nSiteBegin, nSiteEnd;
    GetSiteRange(nSiteRange, nSiteBegin, nSiteEnd);

    for (auto i = nSiteBegin; i < nSiteEnd && !itemInfoListCopy.empty(); ++i) {

        auto pItem = mItemList.at(i);

        if (!pItem) {
            auto it = itemInfoListCopy.begin();
            auto &nStack = it->pItemCfg->Stack;
            if (it->nNum > nStack)
                it->nNum -= nStack;
            else
                itemInfoListCopy.erase(it);
            continue;
        }

        auto nTempID = pItem->GetTemplateID();
        auto bBind = pItem->GetIsBind();

        for (auto it = itemInfoListCopy.begin(); it != itemInfoListCopy.end(); ++it) {

            if (it->pItemCfg->Id != nTempID || it->bBind != (bBind > 0))     // 未考虑其他属性：durability usetime 等
                continue;

            auto &nStack = it->pItemCfg->Stack;
            auto nCapacity = nStack - pItem->GetAmount();

            if (it->nNum > nCapacity)
                it->nNum -= nCapacity;
            else
                itemInfoListCopy.erase(it);
            break;
        }
    }

    if (!itemInfoListCopy.empty()) return ERR_BAG_SPACE_NOT_ENOUGH;

    auto nOwnerID = GetMaster()->GetGUID();

    for (auto i = nSiteBegin; i < nSiteEnd && !itemInfoList.empty(); ++i) {

        auto &pItem = mItemList.at(i);

        if (!pItem) {
            auto it = itemInfoList.begin();
            pItem = GenerateRoleItemByItemCfg(it->pItemCfg, i);
            if (!pItem) return ERR_ITEM_NO_DATA_ROW;
            pItem->SetIsBind(it->bBind);

            auto &nStack = it->pItemCfg->Stack;
            if (it->nNum > nStack) {
                pItem->SetAmount(nStack);
                it->nNum -= nStack;
            }
            else {
                pItem->SetAmount(it->nNum);
                itemInfoList.erase(it);
            }

            NtfMasterAddItem(i);
            OnAddItem(i, lp);
            continue;
        }

        auto nTempID = pItem->GetTemplateID();
        auto bBind = pItem->GetIsBind();

        for (auto it = itemInfoList.begin(); it != itemInfoList.end(); ++it) {

            if (it->pItemCfg->Id != nTempID || it->bBind != (bBind > 0))     // 未考虑其他属性：durability usetime 等
                continue;

            auto &nStack = it->pItemCfg->Stack;
            auto curAmount = pItem->GetAmount();
            auto nCapacity = nStack - curAmount;

            if (it->nNum > nCapacity) {
                pItem->SetAmount(nStack);
                OnUpdateItem(pItem->GetSite(), nCapacity, curAmount, lp);
                it->nNum -= nCapacity;
            }
            else {
                pItem->SetAmount(curAmount + it->nNum);
                OnUpdateItem(pItem->GetSite(), it->nNum, curAmount, lp);
                itemInfoList.erase(it);
            }

            NtfMasterUpdateItem(pItem->GetSite());
            break;
        }
    }

    return ERR_OK;
}

int RolePack::RemoveItem(uint16_t nTemplateID, uint16_t nNum, uint8_t bindRequire, site_range nSiteRange, const log_params& lp)
{
    int nSiteBegin, nSiteEnd;
    GetSiteRange(nSiteRange, nSiteBegin, nSiteEnd);

    std::set<uint16_t> removeSite;
    uint16_t deductSite = INVALID_ITEM_SITE;
    uint16_t deductAmount = 0;
    int nLeft = nNum;
    for (auto i = nSiteBegin; i < nSiteEnd; ++i) {

        auto& pItem = mItemList.at(i);

        if (!pItem) continue;
        if (pItem->GetTemplateID() != nTemplateID) continue;
        if (bind_require_any != bindRequire && pItem->GetIsBind() != bindRequire) continue;

        auto nAmount = pItem->GetAmount();
        if (nAmount <= nLeft)
        {
            nLeft -= nAmount;
            removeSite.insert(i);
        }
        else
        {
            deductAmount = nLeft;
            nLeft = 0;
            deductSite = i;
        }

        if (nLeft == 0) break;
    }

    if (nLeft > 0) return ERR_ITEM_DESTROY;

    if (!removeSite.empty())
    {
        for (auto iter = removeSite.begin(); iter != removeSite.end(); ++iter)
        {
            RemoveItem(*iter, lp);
        }
    }
    if (deductSite != INVALID_ITEM_SITE)
    {
        auto& pItem = mItemList.at(deductSite);
        auto nAmount = pItem->GetAmount();
        pItem->SetAmount(nAmount - deductAmount);
        NtfMasterUpdateItem(deductSite);
        OnUpdateItem(deductSite, -deductAmount, nAmount, lp);
    }

    return ERR_OK;
}
// nNum = 0删除该guid
int RolePack::RemoveItem(uint64_t itemGuid, uint16_t nNum, const log_params& lp)
{
    auto site = GetItemSite(itemGuid);

    if (site == INVALID_ITEM_SITE)  return ERR_ITEM_DESTROY;
    auto& pItem = mItemList.at(site);
    if (nullptr == pItem) return ERR_ITEM_DESTROY;
    auto master = GetMaster();
    if (!master->IsPlayer()) return ERR_NOROLEDATA;

    auto nAmount = pItem->GetAmount();
    if (nNum == 0) nNum = nAmount;
    nNum = std::min<uint16_t>(nAmount, nNum);
    if (nAmount <= nNum)
    {
        RemoveItem(pItem->GetSite(), lp);
    }
    else
    {
        pItem->SetAmount(nAmount - nNum);
        OnUpdateItem(pItem->GetSite(), -nNum, nAmount, lp);
        NtfMasterUpdateItem(pItem->GetSite());
    }

    return ERR_OK;
}

void RolePack::RemoveItem(uint16_t site, const log_params& lp)
{
    auto master = GetMaster();
    if (!master) return;
	if (site < site_weapon || site >= site_end) {
		return;
	}

	if (nullptr == mItemList.at(site)) {
		return;
	}

	auto *player = GetPlayer();
	if (player) {
		player->SendDestroyItem(mItemList.at(site)->GetGUID());
		player->SendDelItemNtf(*mItemList.at(site), lp.beTrade);
	}

    // 在身上的更新属性
    if (CheckWearEquipSite(site))
    {
        UpdateParam up;
        up.beWear = false;
        up.site = site;
        OnUpdateRoleProp(mItemList.at(site)->GetTemplateID(), up);
        OnUpdateRolePropBySuit(mItemList.at(site)->GetTemplateID(), up);
        TRIGGER_EVENT(master, trigger_post_un_equip, mMaster->GetGUIDAsString(), mItemList.at(site)->GetGUIDAsString(), mItemList.at(site)->GetTemplateID());
    }
    OnRemoveItem(site, lp);
	SAFE_RELEASE(mItemList.at(site));

    OnUnloadEquip(site, site);
}

int RolePack::RemoveAllItem(rolepack_opt_type type)
{
    log_params lp;
    switch (type)
    {
    case bag_type:
        lp.info = "清空背包";
        for (int i = site_bag_0; i < site_warehouse; ++i)
        {
            RemoveItem(i, lp);
        }
        break;
    case warehouse_type:
        lp.info =  "清空仓库";
        for (int i = site_warehouse; i < site_warehouse_adv; ++i)
        {
            RemoveItem(i, lp);
        }
        break;
    case adv_warehouse_type:
        lp.info = "清空高级仓库";
        for (int i = site_warehouse_adv; i < site_bag_end; ++i)
        {
            RemoveItem(i, lp);
        }
        break;
    default:
        return ERR_ITEM_DESTROY;
        break;
    }
    return ERR_OK;
}

int RolePack::CanAddItems(const ItemParams &items, site_range nSiteRange)
{
    int nSiteBegin, nSiteEnd;
    GetSiteRange(nSiteRange, nSiteBegin, nSiteEnd);

    auto itemsCopy = items;

    for (auto i = nSiteBegin; i < nSiteEnd && !itemsCopy.empty(); ++i) {

        const auto *pItem = mItemList.at(i);

        if (!pItem) {
            auto it = itemsCopy.begin();

            const auto *pItemCfg = sItemConfig.Get(it->nItemID);
            if (!pItemCfg) return ERR_ITEM_NO_DATA_ROW;

            auto &nStack = pItemCfg->Stack;

            if (it->nNum > nStack)
                it->nNum -= nStack;
            else
                itemsCopy.erase(it);
            continue;
        }

        auto nTempID = pItem->GetTemplateID();
        auto bBind = pItem->GetIsBind();

        for (auto it = itemsCopy.begin(); it != itemsCopy.end(); ++it) {

            const auto *pItemCfg = sItemConfig.Get(it->nItemID);
            if (!pItemCfg) return ERR_ITEM_NO_DATA_ROW;

            if (pItemCfg->Id != nTempID) continue;

            auto _bind = (it->nBind == bind_on_pick_up ? true : false);
            if (_bind != (bBind > 0)) continue;

            auto &nStack = pItemCfg->Stack;
            auto nCapacity = nStack - pItem->GetAmount();

            if (it->nNum > nCapacity)
                it->nNum -= nCapacity;
            else
                itemsCopy.erase(it);
            break;
        }
    }

    if (!itemsCopy.empty()) return ERR_BAG_SPACE_NOT_ENOUGH;

    return ERR_OK;
}

int RolePack::CanRemoveItems(const ItemParams &items, site_range nSiteRange)
{
    int nSiteBegin, nSiteEnd;
    GetSiteRange(nSiteRange, nSiteBegin, nSiteEnd);

    auto itemsCopy = items;

    for (auto i = nSiteBegin; i < nSiteEnd && !itemsCopy.empty(); ++i) {

        const auto *pItem = mItemList.at(i);
        if (!pItem) continue;

        auto it = std::find_if(itemsCopy.begin(), itemsCopy.end(), [&](const auto &item) {

            if (item.nItemID != pItem->GetTemplateID()) return false;

            bool _bind = (item.nBind == bind_on_pick_up ? true : false);

            return (_bind == (pItem->GetIsBind() > 0));
        });

        if (it == itemsCopy.end()) continue;

        auto nAmount = pItem->GetAmount();
        if (it->nNum <= nAmount)
            itemsCopy.erase(it);
        else
            it->nNum -= nAmount;
    }

    if (!itemsCopy.empty()) return ERR_ITEM_DESTROY;

    return ERR_OK;
}

int RolePack::AddItems(const ItemParams &items, site_range nSiteRange, const log_params& lp)
{
    int nSiteBegin, nSiteEnd;
    GetSiteRange(nSiteRange, nSiteBegin, nSiteEnd);

    auto itemsCopy = items;

    auto nOwnerID = GetMaster()->GetGUID();

    for (auto i = nSiteBegin; i < nSiteEnd && !itemsCopy.empty(); ++i) {

        auto &pItem = mItemList.at(i);

        if (!pItem) {
            auto it = itemsCopy.begin();

            auto *pItemCfg = sItemConfig.Get(it->nItemID);
            if (!pItemCfg) return ERR_ITEM_NO_DATA_ROW;

            pItem = GenerateRoleItemByItemCfg(pItemCfg, i);
            if (!pItem) return ERR_ITEM_ADD;

            pItem->SetIsBind(it->nBind);

            auto &nStack = pItemCfg->Stack;
            if (it->nNum > nStack) {
                pItem->SetAmount(nStack);
                it->nNum -= nStack;
            }
            else {
                pItem->SetAmount(it->nNum);
                itemsCopy.erase(it);
            }

            NtfMasterAddItem(i);
            OnAddItem(i, lp);
            continue;
        }

        auto nTempID = pItem->GetTemplateID();
        auto bBind = pItem->GetIsBind();

        for (auto it = itemsCopy.begin(); it != itemsCopy.end(); ++it) {

            const auto *pItemCfg = sItemConfig.Get(it->nItemID);
            if (!pItemCfg) return ERR_ITEM_NO_DATA_ROW;

            if (pItemCfg->Id != nTempID) continue;

            bool _bind = (it->nBind == bind_on_pick_up ? true : false);
            if ( _bind != (bBind > 0)) continue;

            auto &nStack = pItemCfg->Stack;
            auto curAmount = pItem->GetAmount();
            auto nCapacity = nStack - curAmount;

            if (it->nNum > nCapacity) {
                pItem->SetAmount(nStack);
                OnUpdateItem(pItem->GetSite(), nCapacity, curAmount, lp);
                it->nNum -= nCapacity;
            }
            else {
                pItem->SetAmount(curAmount + it->nNum);
                OnUpdateItem(pItem->GetSite(), it->nNum, curAmount, lp);
                itemsCopy.erase(it);
            }

            NtfMasterUpdateItem(pItem->GetSite());
            break;
        }
    }

    if (!itemsCopy.empty()) return ERR_BAG_SPACE_NOT_ENOUGH;

    return ERR_OK;
}

int RolePack::RemoveItems(const ItemParams &items, site_range nSiteRange, const log_params& lp)
{
    int nSiteBegin, nSiteEnd;
    GetSiteRange(nSiteRange, nSiteBegin, nSiteEnd);

    auto itemsCopy = items;

    for (auto i = nSiteBegin; i < nSiteEnd && !itemsCopy.empty(); ++i) {

        auto &pItem = mItemList.at(i);
        if (!pItem) continue;

        auto it = std::find_if(itemsCopy.begin(), itemsCopy.end(), [&](const auto &item) {

            if (item.nItemID != pItem->GetTemplateID()) return false;

            bool _bind = (item.nBind == bind_on_pick_up ? true : false);
            return (_bind == (pItem->GetIsBind() > 0));
        });

        if (it == itemsCopy.end()) continue;

        auto nAmount = pItem->GetAmount();

        if (nAmount <= it->nNum) {
            RemoveItem(pItem->GetSite(), lp);
        }
        else {
            pItem->SetAmount(nAmount - it->nNum);
            OnUpdateItem(pItem->GetSite(), -it->nNum, nAmount, lp);
            NtfMasterUpdateItem(pItem->GetSite());
        }

        if (it->nNum <= nAmount)
            itemsCopy.erase(it);
        else
            it->nNum -= nAmount;
    }

    if (!itemsCopy.empty()) return ERR_ITEM_DESTROY;

    return ERR_OK;
}

RoleItem* RolePack::FindItem(const uint64_t itemGUID)
{
    auto site = GetItemSite(itemGUID);
    return GetItem(site);
}

RoleItem* RolePack::FindItemInEquip(const uint64_t itemGUID)
{
    auto site = GetItemSiteInEquip(itemGUID);
    return GetItem(site);
}

RoleItem* RolePack::FindItemInBag(const uint64_t itemGUID)
{
    auto site = GetItemSiteInBag(itemGUID);
    return GetItem(site);
}

RoleItem* RolePack::FindItemInWareHouse(const uint64_t itemGUID)
{
    auto site = GetItemSiteInWareHouse(itemGUID);
    return GetItem(site);
}

RoleItem* RolePack::FindItemInAdvWareHouse(const uint64_t itemGUID)
{
    auto site = GetItemSiteInAdvWareHouse(itemGUID);
    return GetItem(site);
}

uint32_t RolePack::GetItemNum(uint16_t nItemTemplateID, uint8_t bindRequire, site_range nSiteRange)
{
    int nSiteBegin, nSiteEnd;
    GetSiteRange(nSiteRange, nSiteBegin, nSiteEnd);

    uint32_t nItemNum = 0;
    for (auto i = nSiteBegin; i < nSiteEnd; ++i) {

        auto &pItem = mItemList.at(i);
        if (!pItem || pItem->GetTemplateID() != nItemTemplateID) continue;
        if (bind_require_any != bindRequire && pItem->GetIsBind() != bindRequire) continue;

        nItemNum += pItem->GetAmount();
    }

    return nItemNum;
}

void RolePack::OnRecvItemFromCS(ProtoCS_SendItemNtf& ntf)
{
    log_params lp{ LOG_PARAMS_INFO_INIT };
    for (int32_t i = 0; i < ntf.item_num; ++i) {
        AddItem(ntf.item_info[i], lp);
    }
}

void RolePack::InitItemCustVarList(uint64_t guid)
{
    auto* item = FindItem(guid);
    if (!item) return;

    auto iter = mCustVarList.begin();
    for (; iter != mCustVarList.end();)
    {
        if ((*iter)->belong == guid)
        {
            item->AddCustVar(std::move(*iter));
            iter = mCustVarList.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

void RolePack::InitItemDynAttrsList(uint64_t guid)
{
    auto iter = std::find_if(mDybAttrsList.begin(), mDybAttrsList.end(), [guid](const ITEM_DYN_ATTRS_LIST::value_type& item) {
        return item.guid == guid;
    });
    if (iter == mDybAttrsList.end()) return;
    auto* item = FindItem(guid);
    if (!item) return;

    item->SetDynAttrs(std::move(iter->dyn_attrs));
    mDybAttrsList.erase(iter);
}
void RolePack::InitEquipUpdateProp()
{
    for (uint16_t site = site_weapon; site < site_equip_end; ++site)
    {
        UpdateEquipBySite(site);
    }

    for (uint16_t site = site_glasses; site < site_equip_reserved_end; ++site)
    {
        UpdateEquipBySite(site);
    }
    for (uint16_t site = site_fashion_helmet; site < site_fashion_end; ++site)
    {
        UpdateEquipBySite(site);
    }
    for (uint16_t site = site_equip_custom_0; site < site_equip_custom_end; ++site)
    {
        UpdateEquipBySite(site);
    }
}


bool RolePack::SetAmount(const std::string& guid, uint32_t num, const log_params& lp)
{
    auto item = FindItem(std::stoull(guid));
    if (item == nullptr)return false;

    auto itemCfg = sItemConfig.Get(item->GetTemplateID());
    if (num > itemCfg->Stack)return false;

    auto amount = item->GetAmount();
    if (num == 0)
    {
        RemoveItem(item->GetSite(), lp);
        return true;
    }
    else
    {
        item->SetAmount(num);
        NtfMasterUpdateItem(item->GetSite());

        if (num > amount)
        {
            SendDBLogData(log_type_item_update, LogItemUpdate(GetMaster()->GetGUID(), item->GetGUID(), item->GetTemplateID(),
                item->GetSite(), item_att_amount, amount, num - amount, num, item->GetName(), 0, lp.info));
        }
        else
        {
            SendDBLogData(log_type_item_update, LogItemUpdate(GetMaster()->GetGUID(), item->GetGUID(), item->GetTemplateID(),
                item->GetSite(), item_att_amount, amount, amount - num, num, item->GetName(), 0,  lp.info));
        }

        return true;
    }

    return false;
}

void RolePack::SetDynAttr(uint16_t site, uint16_t index, uint16_t attr, int32_t value)
{
    auto item = GetItem(site);
    if (item == nullptr) return;
    auto dynAttr = item->GetDynAttr(index);
    if (dynAttr.attr == attr && dynAttr.value== value)
    {
        return;
    }
    bool bCalculate = true;
    if (mMaster && mMaster->IsPlayer())
    {
        auto* player = static_cast<Player*>(mMaster);
        if (player&& player->NeedCalculate())
        {
            //bCalculate = false;
        }
    }

    // 穿在身上的需要立即更新属性
    if (CheckWearEquipSite(site) && bCalculate)
    {
        UpdateParam up;
        up.beWear = false;
        up.site = site;
        OnUpdateRoleProp(item->GetTemplateID(), up);
        item->SetDynAttr(index, attr, value);
        up.beWear = true;
        OnUpdateRoleProp(item->GetTemplateID(), up);
    }
    else
    {
        item->SetDynAttr(index, attr, value);
    }
    NtfMasterUpdateItem(site);
    // 每次更新都要记录
    SendDBLogData(log_type_item_dyn_attr, LogItemDynAttr(item->GetGUID(), index, attr, value));
}

bool RolePack::SetItemCfg(uint64_t guid, const CLuaObject& tab)
{
    auto* master = GetMaster();
    if (!master) return false;
    auto item = FindItem(guid);
    if (!item)return false;
    auto site = item->GetSite();

    std::string name = "";
    uint32_t color = 0;
    std::string icon = "";
    uint32_t quality = 0;
    uint32_t subtype = 0;
    uint16_t isSet = 0x0000000;
    for (luabind::iterator it(tab), end; it != end; ++it)
    {
        if (it.key() == "Name")
        {
            if (luabind::type(*it) != LUA_TSTRING)return false;
            name = luabind::object_cast<std::string>(*it);
            isSet += 0x0000001 << (0);
        }
        else if (it.key() == "Color")
        {
            if (luabind::type(*it) != LUA_TNUMBER)return false;
            color = luabind::object_cast<uint32_t>(*it);
            isSet += 0x0000001 << (1);
        }
        else if (it.key() == "Icon")
        {
            if (luabind::type(*it) != LUA_TSTRING)return false;
            icon = luabind::object_cast<std::string>(*it);
            isSet += 0x0000001 << (2);
        }
        else if (it.key() == "Quality")
        {
            if (luabind::type(*it) != LUA_TNUMBER)return false;
            quality = luabind::object_cast<uint32_t>(*it);
            isSet += 0x0000001 << (3);
        }
        else if (it.key() == "SubType")
        {
            if (luabind::type(*it) != LUA_TNUMBER)return false;
            subtype = luabind::object_cast<uint32_t>(*it);
            isSet += 0x0000001 << (4);
        }
    }

    if (isSet & (0x0000001 << (0)))
    {
        auto oldName = item->GetName();
        item->SetName(name);
        SendDBLogData(log_type_item_update, LogItemUpdate(master->GetGUID(), item->GetGUID(), item->GetTemplateID(),
            site, item_att_name, 0, 0, 0, oldName, 0, "bef:"+ oldName + "|aft:" + item->GetName()));
    }
    if (isSet & (0x0000001 << (1)))
    {
        auto oldColor = item->GetColor();
        item->SetColor(color);
        SendDBLogData(log_type_item_update, LogItemUpdate(master->GetGUID(), item->GetGUID(), item->GetTemplateID(),
            site, item_att_color, 0, 0, 0, item->GetName(), 0, "bef:" + to_string(oldColor) + "|aft:" + to_string(item->GetColor())));
    }
    if (isSet & (0x0000001 << (2)))
    {
        auto oldIcon = item->GetIcon();
        item->SetIcon(std::stoull(icon));
        SendDBLogData(log_type_item_update, LogItemUpdate(master->GetGUID(), item->GetGUID(), item->GetTemplateID(),
            site, item_att_icon, 0, 0, 0, item->GetName(), 0, "bef:" + to_string(oldIcon) + "|aft:" + to_string(item->GetIcon())));
    }
    if (isSet & (0x0000001 << (3)))
    {
        auto oldQuality = item->GetQuality();
        item->SetQuality(quality);
        SendDBLogData(log_type_item_update, LogItemUpdate(master->GetGUID(), item->GetGUID(), item->GetTemplateID(),
            site, item_att_quality, 0, 0, 0, item->GetName(), 0, "bef:" + to_string(oldQuality) + "|aft:" + to_string(item->GetQuality())));
    }
    if (isSet & (0x0000001 << (4)))
    {
        auto oldSubType = item->GetSubType();
        item->SetSubType(subtype);
        SendDBLogData(log_type_item_update, LogItemUpdate(master->GetGUID(), item->GetGUID(), item->GetTemplateID(),
            site, item_att_subtype, 0, 0, 0, item->GetName(), 0, "bef:" + to_string(oldSubType) + "|aft:" + to_string(item->GetSubType())));
    }
    NtfMasterUpdateItem(site);

    return true;
}


bool RolePack::OnUpdateUseItem(uint16_t id, UpdateParam& up)
{
    auto itemCfg = sItemConfig.Get(id);
    if (nullptr == itemCfg) return false;
    switch (itemCfg->Type)
    {
        case item_type_equip:return OnUpdateEquipItem(id, up);
        case item_type_consumable:return OnUpdateConsumabItem(id, up);
        case item_type_finite:return OnUpdateFinitebItem(id, up);
        case item_type_material:return false;
        case item_type_sundries:return false;
        case item_type_bag:return false;
        case item_type_warehouse_adv:return false;
        case item_type_gold:return false;
        case item_type_bundle:return false;
        case item_type_skill:return false;
        case item_type_script:return OnUpdateScriptItem(id, up);
        default:return false;
    }
    return false;
}

uint64_t RolePack::GetItemGuidBySite(uint32_t site)
{
    auto item = GetItem(site);
    if (item == nullptr) return 0;
    return item->GetGUID();
}

bool RolePack::CheckWearEquipSite(uint16_t site)
{
    return (site >= site_weapon && site < site_equip_end) || (site >= site_equip_custom_0 && site < site_equip_custom_end)
        || (site >= site_glasses && site < site_equip_reserved_end) || (site >= site_fashion_helmet && site < site_fashion_end);
}

void RolePack::SetAutoStack(bool b)
{
    mBeAutoStack = b;
}

void RolePack::CalcDropItems(uint64_t killerGUID)
{
    if (!mMaster)return;

    if (!mMaster->IsPlayer())return;
    auto player = static_cast<Player*>(mMaster);
    if (!player)return;

    auto map = player->GetCurMap();
    if (nullptr == map) {
        return;
    }

    auto mcfg = map->GetMapConfig();
    if (!CLuaLib::GetInstance()->IsHaveEvent(trigger_player_pre_drop)) return;
    auto retPreDropTab = NewLuaObj();

    TRIGGER_EVENT_RET<CLuaObject>(retPreDropTab, trigger_player_pre_drop, mMaster->GetGUIDAsString(), std::to_string(killerGUID));

    if (luabind::type(retPreDropTab) != LUA_TTABLE){
        LOG_ERROR("Player Drop Pre Ret Table is not table!");
        return;
    }

    auto retDropTab = NewLuaObj();
    int idx = 1;
    for (luabind::iterator it(retPreDropTab), end; it != end; ++it) {
        if (luabind::type((*it)[1]) != LUA_TNUMBER)continue;
        if (luabind::type((*it)[2]) != LUA_TNUMBER)continue;
        auto site = luabind::object_cast<int>((*it)[1]);
        auto rate = luabind::object_cast<int>((*it)[2]);
        if(mItemList.at(site) == nullptr)continue;
        if (Tools::GenerateRandomInteger<uint16_t>(1, 10000) <= rate) {
            auto dropData = NewLuaObj();
            dropData[1] = site;
            dropData[2] = mItemList.at(site)->GetGUIDAsString();
            retDropTab[idx] = dropData;
            ++idx;
        }
    }

    if (!CLuaLib::GetInstance()->IsHaveEvent(trigger_player_drop)) return;

    LuaRet = retDropTab;
    auto retFinalDropTab = NewLuaObj();
    TRIGGER_EVENT_RET<CLuaObject>(retFinalDropTab, trigger_player_drop, mMaster->GetGUIDAsString(), std::to_string(killerGUID));

    if (luabind::type(retFinalDropTab) != LUA_TTABLE) {
        LOG_ERROR("Player Drop Ret Table is not table!");
        return;
    }

    std::vector<int>keys;
    for (luabind::iterator it(retFinalDropTab), end; it != end; ++it) {
        if (luabind::type(*it) != LUA_TNUMBER)continue;
        auto site = luabind::object_cast<std::int32_t>(*it);
        keys.push_back(site);
    }

    if (keys.empty())return;

    //是否随机
    if (sGlobalConfig.GetData()->PlayerDropIsRandom)
    {
        static std::random_device rd;
        std::shuffle(keys.begin(), keys.end(), rd);
    }
    uint16_t posX, posY;

    uint64_t kGuid = killerGUID;
    Role* role = MapRoleMgr::GetInstance()->FindRole(kGuid);
    if (role)
    {
        Player* belongPlayer = nullptr;
        if (role->IsPet()) {
            auto pet = static_cast<Pet*>(role);
            belongPlayer = pet->GetMaster();
        }
        else if (role->IsPlayerDoplganr()) {
            auto* doplganr = static_cast<PlayerDoplganr*>(role);
            belongPlayer = doplganr->GetMaster();
        }
        if (belongPlayer) kGuid = belongPlayer->GetGUID();;
    }
    CLuaObject realDropList = NewLuaObj();
	int index = 1;
	uint32_t maxDropNum = sGlobalConfig.GetData()->PlayerDropSiteItemMaxCount;
    for (auto i : keys) {
        if (mItemList.at(i) == nullptr)continue;
		if (map->GetBlankSceneItemPos(player->GetRolePosX(), player->GetRolePosY(), posX, posY)) {
            if (maxDropNum <= 0)
            {
                auto sceneItem = map->AddSceneItem(posX, posY, mItemList.at(i));
                if (!sceneItem)continue;
                uint16_t oMType = GUID_TYPE_PART(player->GetGUID());
                if (mcfg) SendDBLogData(log_type_drop_item, LogDropItem(mcfg->Id, mcfg->MapType, kGuid, player->GetGUID(),
                    oMType, player->GetRoleProp(role_job), log_drop_item_type_item, sceneItem->GetTemplateID(), mItemList.at(i)->GetAmount(), sceneItem->GetName()));
                RemoveItem(i, log_params{ "掉落后删除" });
            }
            else
            {
                // 根据PlayerDropSiteItemMaxCount配置掉落堆叠数量
                auto pitem = new RoleItem(mItemList.at(i));
                uint32_t curNum = pitem->GetAmount();
                uint32_t dropNum = 1;
                if (curNum <= maxDropNum)
                {
                    dropNum = Tools::GenerateRandomInteger<uint16_t>(1, curNum);
                }
                else
                {
                    dropNum = Tools::GenerateRandomInteger<uint16_t>(1, maxDropNum);
                }
                pitem->SetAmount(dropNum);

                auto sceneItem = map->AddSceneItem(posX, posY, pitem);
                if (!sceneItem)continue;
                uint16_t oMType = GUID_TYPE_PART(player->GetGUID());
                if (mcfg) SendDBLogData(log_type_drop_item, LogDropItem(mcfg->Id, mcfg->MapType, kGuid, player->GetGUID(),
                    oMType, player->GetRoleProp(role_job), log_drop_item_type_item, sceneItem->GetTemplateID(), dropNum, sceneItem->GetName()));
                RemoveItem(pitem->GetGUID(), dropNum, log_params{ "掉落后删除" });
                CLuaObject dropSiteItem = NewLuaObj();
				dropSiteItem[1] = sceneItem->GetTemplateID();
				dropSiteItem[2] = dropNum;
                realDropList[index] = dropSiteItem;
                index++;
            }
        }
    }
    if (maxDropNum > 0)
    {
        LuaRet = realDropList;
        TRIGGER_EVENT(trigger_player_drop_item_list, mMaster->GetGUIDAsString(), std::to_string(killerGUID));
    }
    
}

void RolePack::DropItemByDropProcess(uint16_t type, uint64_t killerGUID)
{
    if (!mMaster)return;
    if (!mMaster->IsPlayer())return;
    auto player = static_cast<Player*>(mMaster);
    if (!player)return;
    auto map = player->GetCurMap();
    if (!map)return;

    auto mcfg = map->GetMapConfig();

    uint64_t kGuid = killerGUID;
    Role* role = MapRoleMgr::GetInstance()->FindRole(kGuid);
    if (role)
    {
        Player* belongPlayer = nullptr;
        if (role->IsPet()) {
            auto pet = static_cast<Pet*>(role);
            belongPlayer = pet->GetMaster();
        }
        else if (role->IsPlayerDoplganr()) {
            auto* doplganr = static_cast<PlayerDoplganr*>(role);
            belongPlayer = doplganr->GetMaster();
        }
        if (belongPlayer) kGuid = belongPlayer->GetGUID();;
	}
	uint32_t maxDropNum = sGlobalConfig.GetData()->PlayerDropSiteItemMaxCount;
    // 死亡必掉时要传掉落事件
    if (type == player_drop_type_die) {
        auto retDropTab = NewLuaObj();
        int idx = 1;
        for (int i = 0; i < site_end; ++i) {
            if (i >= site_warehouse && i < site_bag_end)continue;
            if (nullptr == mItemList.at(i))continue;
            auto itemCfg = sItemConfig.GetByID(mItemList.at(i)->GetTemplateID());
            if (!itemCfg)continue;
            auto iter = itemCfg->DropType.find(type);
            if (iter == itemCfg->DropType.end())continue;
            auto dropData = NewLuaObj();
            dropData[1] = i;
            dropData[2] = mItemList.at(i)->GetGUIDAsString();
            retDropTab[idx] = dropData;
            ++idx;

        }

        if (!CLuaLib::GetInstance()->IsHaveEvent(trigger_player_drop)) return;
        LuaRet = retDropTab;
        auto retFinalDropTab = NewLuaObj();
        TRIGGER_EVENT_RET<CLuaObject>(retFinalDropTab, trigger_player_drop, mMaster->GetGUIDAsString(), std::to_string(killerGUID));


		CLuaObject realDropList = NewLuaObj();
		int index = 1;
        for (luabind::iterator it(retFinalDropTab), end; it != end; ++it) {
            if (luabind::type(*it) != LUA_TNUMBER)continue;
            auto site = luabind::object_cast<std::int32_t>(*it);
            if (mItemList.at(site) == nullptr)continue;

            uint16_t posX, posY;
            if (map->GetBlankSceneItemPos(player->GetRolePosX(), player->GetRolePosY(), posX, posY)) {
                if (maxDropNum <= 0)    // 按site全掉
                {
                    auto sceneItem = map->AddSceneItem(posX, posY, mItemList.at(site));
                    if (!sceneItem)continue;
                    uint16_t oMType = GUID_TYPE_PART(player->GetGUID());
                    if (mcfg) SendDBLogData(log_type_drop_item, LogDropItem(mcfg->Id, mcfg->MapType, kGuid, player->GetGUID(),
                        oMType, player->GetRoleProp(role_job), log_drop_item_type_item, sceneItem->GetTemplateID(), mItemList.at(site)->GetAmount(), sceneItem->GetName()));
                    RemoveItem(site, log_params{ "掉落后删除" });
                }
                else        // 按site掉部分
                {
                    auto pitem = new RoleItem(mItemList.at(site));
                    uint32_t curNum = pitem->GetAmount();
                    uint32_t dropNum = 1;
                    if (curNum <= maxDropNum)
                    {
                        dropNum = Tools::GenerateRandomInteger<uint16_t>(1, curNum);
                    }
                    else
                    {
                        dropNum = Tools::GenerateRandomInteger<uint16_t>(1, maxDropNum);
                    }
                    pitem->SetAmount(dropNum);

                    auto sceneItem = map->AddSceneItem(posX, posY, pitem);
                    if (!sceneItem)continue;
                    uint16_t oMType = GUID_TYPE_PART(player->GetGUID());
                    if (mcfg) SendDBLogData(log_type_drop_item, LogDropItem(mcfg->Id, mcfg->MapType, kGuid, player->GetGUID(),
                        oMType, player->GetRoleProp(role_job), log_drop_item_type_item, sceneItem->GetTemplateID(), dropNum, sceneItem->GetName()));
                    RemoveItem(pitem->GetGUID(), dropNum, log_params{ "掉落后删除" });
					CLuaObject dropSiteItem = NewLuaObj();
					dropSiteItem[1] = sceneItem->GetTemplateID();
					dropSiteItem[2] = dropNum;
					realDropList[index] = dropSiteItem;
					index++;
                }
            }
        }
		if (maxDropNum > 0)
		{
			LuaRet = realDropList;
			TRIGGER_EVENT(trigger_player_drop_item_list, mMaster->GetGUIDAsString(), std::to_string(killerGUID));
		}
        return;
    }

	CLuaObject realDropList = NewLuaObj();
	int index = 1;
    for (int i = 0; i < site_end; ++i) {
        if (i >= site_warehouse && i < site_bag_end)continue;
        if (nullptr == mItemList.at(i))continue;
        auto itemCfg = sItemConfig.GetByID(mItemList.at(i)->GetTemplateID());
        if (!itemCfg)continue;
        auto iter = itemCfg->DropType.find(type);
        if (iter == itemCfg->DropType.end())continue;

        uint16_t posX, posY;
		if (map->GetBlankSceneItemPos(player->GetRolePosX(), player->GetRolePosY(), posX, posY)) {
            if (maxDropNum <= 0)    // 按site全掉
            {
                auto sceneItem = map->AddSceneItem(posX, posY, mItemList.at(i));
                if (!sceneItem)continue;
                uint16_t oMType = GUID_TYPE_PART(player->GetGUID());
                if (mcfg) SendDBLogData(log_type_drop_item, LogDropItem(mcfg->Id, mcfg->MapType, kGuid, player->GetGUID(),
                    oMType, player->GetRoleProp(role_job), log_drop_item_type_item, sceneItem->GetTemplateID(), mItemList.at(i)->GetAmount(), sceneItem->GetName()));
                RemoveItem(i, log_params{ "掉落后删除" });
            }
            else        // 按site掉随机数量
            {
                auto pitem = new RoleItem(mItemList.at(i));
                uint32_t curNum = pitem->GetAmount();
                uint32_t dropNum = 1;
                if (curNum <= maxDropNum)
                {
                    dropNum = Tools::GenerateRandomInteger<uint16_t>(1, curNum);
                }
                else
                {
                    dropNum = Tools::GenerateRandomInteger<uint16_t>(1, maxDropNum);
                }
                pitem->SetAmount(dropNum);

                auto sceneItem = map->AddSceneItem(posX, posY, pitem);
                if (!sceneItem)continue;
                uint16_t oMType = GUID_TYPE_PART(player->GetGUID());
                if (mcfg) SendDBLogData(log_type_drop_item, LogDropItem(mcfg->Id, mcfg->MapType, kGuid, player->GetGUID(),
                    oMType, player->GetRoleProp(role_job), log_drop_item_type_item, sceneItem->GetTemplateID(), dropNum, sceneItem->GetName()));
                RemoveItem(pitem->GetGUID(), dropNum, log_params{ "掉落后删除" });

				CLuaObject dropSiteItem = NewLuaObj();
				dropSiteItem[1] = sceneItem->GetTemplateID();
				dropSiteItem[2] = dropNum;
				realDropList[index] = dropSiteItem;
				index++;
            }
        }
	}
	if (maxDropNum > 0)
	{
		LuaRet = realDropList;
		TRIGGER_EVENT(trigger_player_drop_item_list, mMaster->GetGUIDAsString(), std::to_string(killerGUID));
	}
}

void RolePack::GetItemList(CLuaObject& list, uint16_t min, uint16_t max)
{
    int idx = 1;
    uint16_t MAX = max > site_item_quick_bar_end ? site_item_quick_bar_end : max;
    for (int i = min; i < MAX; ++i) {
        if (nullptr == mItemList.at(i))continue;
        auto obj = NewLuaObj();
        obj[1] = i;
        obj[2] = mItemList.at(i)->GetGUIDAsString();
        list[idx++] = obj;
    }
}

// ---------------------------------------------------------------------------
bool RolePack::OnUpdateEquipItem(uint16_t id, const UpdateParam& up)
{
    OnTriggerScript(id, up);
    OnUpdateRoleProp(id, up);
    OnUpdateRolePropBySuit(id, up);
    OnUpdateEquipProp(id, up);
    return true;
}

bool RolePack::OnUpdateConsumabItem(uint16_t id, UpdateParam& up)
{
    int use_num = OnTriggerScript(id, up);
    if (use_num == 0){
        return true;
    }
    else if (use_num < 0 ){
        return false;
    }
    up.num = use_num;
    OnTriggerEffect(id, up);
    OnUpdateItemProp(id, up);
    return true;
}

bool RolePack::OnUpdateFinitebItem(uint16_t id, UpdateParam& up)
{
    int use_num = OnTriggerScript(id, up);
    if (use_num == 0) {
        return true;
    }
    else if (use_num < 0) {
        return false;
    }
    up.num = use_num;
    OnTriggerEffect(id, up);
    OnUpdateItemProp(id, up);
    return true;
}

bool RolePack::OnUpdateScriptItem(uint16_t id, const UpdateParam& up)
{
    OnTriggerScript(id, up);
    return true;
}
// ---------------------------------------------------------------------------
int RolePack::OnTriggerScript(uint16_t id, const UpdateParam& up)
{
    auto* master = GetMaster();
    if (nullptr == master) return false;
    auto itemCfg = sItemConfig.Get(id);
    if (nullptr == itemCfg) return false;
    std::string scriptName(itemCfg->Script);
    if (scriptName.empty() || scriptName == "0") return false;

    int ret = up.num;
    scriptName += ".main";
    LuaBindCallRet(ret, scriptName, master->GetGUIDAsString(), mItemList.at(up.site)->GetGUIDAsString(), mItemList.at(up.site)->GetTemplateID(), up.num);
    return ret;
    // 不走事件,直接调用脚本
    // TRIGGER_EVENT(master, trigger_item_script, std::to_string(master->GetGUID()), std::to_string(mItemList.at(up.site)->GetGUID()), mItemList.at(up.site)->GetTemplateID());
}

void RolePack::OnUpdateItemProp(uint16_t id, const UpdateParam& up)
{
    auto* master = GetMaster();
    if (nullptr == master) return;
    auto itemCfg = sItemConfig.Get(id);
    if (nullptr == itemCfg) return;
    if (!mItemList.at(up.site)) return;

    int32_t amountDiff = 0;
    int32_t useCnt = 0;
    int32_t befUseCount = mItemList.at(up.site)->GetUse_count();
    int32_t befAmount = mItemList.at(up.site)->GetAmount();
    int32_t tmpCurUseCount = befUseCount;
    int32_t tmpCurAmount = befAmount;
    for (uint16_t i = 0; i < up.num; ++i)
    {
        if (itemCfg->Type == item_type_finite)
        {
            tmpCurUseCount -= 1;
            mItemList.at(up.site)->SetUse_count(tmpCurUseCount);
            useCnt--;
        }
        // 有限品计算使用次数再扣除数量
        if (item_type_finite != itemCfg->Type || tmpCurUseCount <= 0)
        {
            if (tmpCurAmount <= 1)
            {
                if (useCnt) SendDBLogData(log_type_item_update, LogItemUpdate(master->GetGUID(), mItemList.at(up.site)->GetGUID(), mItemList.at(up.site)->GetTemplateID(),
                    up.site, item_att_use_count, befUseCount, useCnt, tmpCurUseCount, mItemList.at(up.site)->GetName(), 0, up.reason));
                RemoveItem(up.site, log_params{ up.reason });
                return;
            }
            tmpCurAmount -= 1;
            tmpCurUseCount = itemCfg->UseCount;
            amountDiff--;
        }
    }
    mItemList.at(up.site)->SetUse_count(tmpCurUseCount);
    mItemList.at(up.site)->SetAmount(tmpCurAmount);
    if (amountDiff) OnUpdateItem(up.site, amountDiff, befAmount, log_params{ up.reason });
    if (useCnt) SendDBLogData(log_type_item_update, LogItemUpdate(master->GetGUID(), mItemList.at(up.site)->GetGUID(), mItemList.at(up.site)->GetTemplateID(),
        up.site, item_att_use_count, befUseCount, useCnt, tmpCurUseCount, mItemList.at(up.site)->GetName(), 0, up.reason));
    
    mItemList.at(up.site)->SetUseTime(GetTimeStampMillisecond());
    if (itemCfg->BindType == bind_on_use && !mItemList.at(up.site)->GetIsBind()) {
        int32_t bef = mItemList.at(up.site)->GetIsBind();
        mItemList.at(up.site)->SetIsBind(bind_on_pick_up);

        SendDBLogData(log_type_item_update, LogItemUpdate(master->GetGUID(), mItemList.at(up.site)->GetGUID(), mItemList.at(up.site)->GetTemplateID(),
            up.site, item_att_is_bound, bef, 0, mItemList.at(up.site)->GetIsBind(), mItemList.at(up.site)->GetName(), 0, up.reason));
    }
    NtfMasterUpdateItem(up.site);
}

void RolePack::OnUpdateEquipProp(uint16_t id, const UpdateParam& up)
{
    auto *player = GetPlayer();
    if (!player) return;

    auto itemCfg = sItemConfig.Get(id);
    if (nullptr == itemCfg) return;
    if (!mItemList.at(up.site)) return;

    if (up.beWear)
    {
        //判断装备类型 若为使用绑定类型则更改绑定状态
        if (itemCfg->BindType == bind_on_use && !mItemList.at(up.site)->GetIsBind())
        {
            int32_t bef = mItemList.at(up.site)->GetIsBind();
            mItemList.at(up.site)->SetIsBind(bind_on_pick_up);
            player->SendItemAttrNtf(mItemList.at(up.site)->GetGUID(), item_att_is_bound, bind_on_pick_up);

            if (LOG_PARAMS_INFO_INIT != up.reason)
            {
                SendDBLogData(log_type_item_update, LogItemUpdate(player->GetGUID(), mItemList.at(up.site)->GetGUID(),
                    mItemList.at(up.site)->GetTemplateID(), up.site, item_att_is_bound, bef,
                    0, mItemList.at(up.site)->GetIsBind(), mItemList.at(up.site)->GetName(), 0, up.reason));
            }
        }
    }
}

void RolePack::OnTriggerEffect(uint16_t id, const UpdateParam& up)
{
    auto* master = GetMaster();
    if (nullptr == master) return;
    auto itemCfg = sItemConfig.Get(id);
    if (nullptr == itemCfg) return;
    // 触发的技能
    auto skillCfg = sSkillConfig.Get(itemCfg->SkillId);
    if (nullptr != skillCfg)
    {
        auto roleSkillAction = master->GetRoleSkill();
        if (nullptr != roleSkillAction)
        {
            roleSkillAction->ApplySkillOnTarget(skillCfg->Id, up.targetGuid, 0);
        }
    }
    // 触发的buff
    auto* target = MapRoleMgr::GetInstance()->FindRole(up.targetGuid);
    if (nullptr != target && !itemCfg->BuffId.empty())
    {
        auto iter = itemCfg->BuffId.begin();
        for (; iter != itemCfg->BuffId.end(); ++iter)
        {
            if (*iter == 0) continue;
            auto bufflCfg = sBuffConfig.Get(*iter);
            if (nullptr == bufflCfg)
            {
                LOG_ERROR("buffid:%d not exist.", *iter);
                continue;
            }
            target->AddBuffByRole(bufflCfg->Id, master, 0);
        }
    }
    return;
}

void RolePack::OnUpdateRoleProp(uint16_t id, const UpdateParam& up)
{
    auto* master = GetMaster();
    if (nullptr == master) return;
    auto* item = GetItem(up.site);
    if (nullptr == item) return;

    // 走配置里有的字段
    // 属性->配置
    static const std::pair<int32_t, int32_t> equipUpdateProp[] =
    {
        // 最大HP\MP
        {role_base_max_hp,                  ITEM_PROP_HP},
        {role_base_max_mp,                  ITEM_PROP_MP},
        // 物防
        {role_base_max_phy_def,             ITEM_PROP_MAXPHYDEF},
        {role_base_min_phy_def,             ITEM_PROP_MINPHYDEF},
        // 魔防
        {role_base_max_mag_def,             ITEM_PROP_MAXMAGDEF},
        {role_base_min_mag_def,             ITEM_PROP_MINMAGDEF},
        // 物攻
        {role_base_max_phy_atk,             ITEM_PROP_MAXPHYATK},
        {role_base_min_phy_atk,             ITEM_PROP_MINPHYATK},
        // 魔攻
        {role_base_max_mag_atk,             ITEM_PROP_MAXMAGATK},
        {role_base_min_mag_atk,             ITEM_PROP_MINMAGATK},
        // 道术攻击
        {role_base_max_tao_atk,             ITEM_PROP_MAXTAOATK},
        {role_base_min_tao_atk,             ITEM_PROP_MINTAOATK},
        // 命中、闪避、暴击率、攻速
        {role_hit,                          ITEM_PROP_HIT},
        {role_miss,                         ITEM_PROP_MISS},
        {role_burst,                        ITEM_PROP_BURST},
        {role_base_attack_speed,            ITEM_PROP_ATTACKSPEED},
    };
    static const int32_t propCnt = _countof(equipUpdateProp);

    for (int32_t i = 0; i < propCnt; ++i)
    {
        if (::GetItemProp(id, equipUpdateProp[i].second))
        {            
            int32_t updateValue = luabind::object_cast<int32_t>(LuaRet);
            if (0 != updateValue)
            {
                updateValue *= up.beWear ? 1 : -1;
                master->AddRoleProp(equipUpdateProp[i].first, updateValue);
            }
        }
    }
    // 特殊属性字段
    if (::GetItemProp(id, ITEM_PROP_SPECIALATTR))
    {
        luabind::iterator iter(LuaRet), end;
        for (; iter != end; iter++) 
        {
            luabind::adl::object objKey = iter.key();
            luabind::adl::object objVal = *iter;
            int32_t key = luabind::object_cast<int32_t>(objKey);
            int32_t val = luabind::object_cast<int32_t>(objVal);
            if (0 != val)
            {
                val *= up.beWear ? 1 : -1;
                master->AddRoleProp(key, val);
            }
        }
    }

    // 动态属性
    const auto& DynAttrList = item->GetDynAttrs();
    if (!DynAttrList.empty())
    {
        for (auto& attrItem : DynAttrList)
        {
            int32_t updateValue = attrItem.value;
            if (0 != updateValue)
            {
                updateValue *= up.beWear ? 1 : -1;
                master->AddRoleProp(attrItem.attr, updateValue);
            }
        }
    }
}

void RolePack::OnUpdateRolePropBySuit(uint16_t id, const UpdateParam &up)
{
    if (up.beWear)
        mSuitCounter.OnLoadEquip(id);
    else
        mSuitCounter.OnUnloadEquip(id);
}

// ---------------------------------------------------------------------------
int RolePack::UseItem(uint64_t itemGUID, uint32_t num)
{
    // role
    auto master = GetMaster();
    if (nullptr == master) return ERR_NOROLEDATA;

    if (!master->CheckAlive()) return  ERR_ITEM_APPLY;

    auto site = GetItemSite(itemGUID);
    // site
	if (site == INVALID_ITEM_SITE) return ERR_ITEM_NOT_EXIST;
    // 判空
    if (nullptr == mItemList.at(site)) return ERR_ITEM_NOT_EXIST;
    // 配置
	auto itemCfg = sItemConfig.Get(mItemList.at(site)->GetTemplateID());
	if (nullptr == itemCfg) return ERR_ITEM_NO_DATA_ROW;
    // 使用限制
    if (itemCfg->Gender != gender_nullptr && master->GetRoleProp(role_gender) != itemCfg->Gender) return ERR_ITEM_EQUIP_GENDER;
    if (itemCfg->Job != job_nullptr && master->GetRoleProp(role_job) != itemCfg->Job) return ERR_ITEM_EQUIP_JOB;

	if (item_type_equip == itemCfg->Type) 
    {
		return DoUseEquip(site);
	}

	return DoUseItem(site, num);
}

int RolePack::DoUseEquip(int16_t site)
{
    auto *player = GetPlayer();
    if (!player) return ERR_NOROLEDATA;

	auto itemCfg = sItemConfig.Get(mItemList.at(site)->GetTemplateID());
	if (nullptr == itemCfg) return ERR_ITEM_NO_DATA_ROW;

    // 目标位 如果自定义装备子类型了 则使用自定义的子类型
	auto site1 = GetEquipSiteByType(mItemList.at(site)->GetSubType()? mItemList.at(site)->GetSubType():itemCfg->SubType);
    if (!CheckWearEquipSite(site1)) return ERR_ITEM_EQUIP_NOT_SUIT_SITE;

    bool ret = true;
    // 目标位置上已经有装备，判断是否允许脱下
    if (mItemList.at(site1)) {
        TRIGGER_EVENT_RET<bool>(ret, player, trigger_pre_un_equip, mMaster->GetGUIDAsString(), mItemList.at(site1)->GetGUIDAsString(), mItemList.at(site1)->GetTemplateID(), site1);
        if (!ret) return ERR_ITEM_CANT_EQUIP;
    }

    // 当前装备是否允许穿上
    if (mItemList.at(site)) {
        TRIGGER_EVENT_RET<bool>(ret, player, trigger_pre_equip, mMaster->GetGUIDAsString(), mItemList.at(site)->GetGUIDAsString(), mItemList.at(site)->GetTemplateID(), site);
        if (!ret) return ERR_ITEM_CANT_EQUIP;
    }

    auto tm1 = ITimeHelper::GetInstance()->GetTimeStamp();

	std::swap(mItemList.at(site), mItemList.at(site1));

    UpdateParam up;
    up.reason = "使用更新";
    // 角色脱下装备
	if (nullptr != mItemList.at(site)) {
        TRIGGER_EVENT(player, trigger_post_un_equip, mMaster->GetGUIDAsString(), mItemList.at(site)->GetGUIDAsString(), mItemList.at(site)->GetTemplateID(), site);
		mItemList.at(site)->SetSite(site);
		player->SendItemAttrNtf(mItemList.at(site)->GetGUID(), item_att_pos, mItemList.at(site)->GetSite());
        up.beWear = false;
        up.site = site;
        OnUpdateUseItem(mItemList.at(site)->GetTemplateID(), up);
	}
    //角色穿上装备
	if (nullptr != mItemList.at(site1)) {
        mItemList.at(site1)->SetSite(site1);
		player->SendItemAttrNtf(mItemList.at(site1)->GetGUID(), item_att_pos, mItemList.at(site1)->GetSite());
        up.beWear = true;
        up.site = site1;
        OnUpdateUseItem(mItemList.at(site1)->GetTemplateID(), up);
        TRIGGER_EVENT(player, trigger_post_equip, mMaster->GetGUIDAsString(), mItemList.at(site1)->GetGUIDAsString(), mItemList.at(site1)->GetTemplateID(), site1);
	}
    OnSwapItem(site, site1, log_params{ "使用更新" });
    OnUseEquip(site, site1);

    auto tm2 = ITimeHelper::GetInstance()->GetTimeStamp();

    if (tm2 - tm1 >= 300) {
        LOG_WARN("cur item name:%s, cur item site:%d", itemCfg->KeyName.c_str(), site);
    }

	return ERR_OK;
}

int RolePack::DoUseItem(int16_t site, uint32_t num)
{
	auto master = GetMaster();
	if (nullptr == master) return ERR_NOROLEDATA;

    auto itemCfg = sItemConfig.Get(mItemList.at(site)->GetTemplateID());
    if (nullptr == itemCfg)  return ERR_ITEM_NO_DATA_ROW;

	if (0 == mItemList.at(site)->GetAmount() || mItemList.at(site)->GetAmount() < num) return ERR_ITEM_AMOUNT;

	if (!master->IsCanUseItem(mItemList.at(site)->GetGUID()))	return ERR_ITEM_APPLY;

    // CD
    const auto &skillID = itemCfg->SkillId;
    if (skillID != 0) {
        auto *roleSkill = master->GetRoleSkill();
        if (!roleSkill) return ERR_ITEM_APPLY;

        if (!roleSkill->IsSkillExist(skillID)) return ERR_ITEM_APPLY;

        if (roleSkill->GetSkillProp(skillID, SKILL_PROP_CD))
        {
            auto cd = luabind::object_cast<int32_t>(LuaRet);
            if (cd > 0) {
                auto curTime = GetTimeStampMillisecond();
                auto lastTime = mItemList.at(site)->GetUseTime();
                if (curTime - lastTime < cd) return ERR_ROLE_REQUEST_SEG_TO_FAST;
            }
        }
    }

    auto tm1 = ITimeHelper::GetInstance()->GetTimeStamp();

    // 更新使用物品
    UpdateParam up;
    up.reason = "使用更新";
    up.num = num;
    up.site = site;
    up.targetGuid = master->GetGUID();
    if (!OnUpdateUseItem(mItemList.at(site)->GetTemplateID(), up))
    {
        return ERR_ITEM_APPLY;
    }

    auto tm2 = ITimeHelper::GetInstance()->GetTimeStamp();
    if (tm2 - tm1 >= 300) {
        LOG_WARN("cur item name:%s, cur item site:%d", itemCfg->KeyName.c_str(), site);
    }

	return ERR_OK;
}

int RolePack::MoveItem(const uint64_t fromItemGUID, uint16_t toSite)
{
	auto *self = GetMaster();
	if (!self) return ERR_NOROLEDATA;

    auto *fromItem = FindItem(fromItemGUID);
    if (!fromItem) return ERR_ITEM_NOT_EXIST;

    auto *fromCfg = sItemConfig.Get(fromItem->GetTemplateID());
    if (!fromCfg) return ERR_ITEM_NO_DATA_ROW;

    uint16_t fromSite = fromItem->GetSite();
	if (fromSite == INVALID_ITEM_SITE) return ERR_ITEM_SITE;

    if (toSite <= site_nullptr || toSite >= site_end) return ERR_ITEM_SITE;
    if (toSite == fromSite) return ERR_OK;

    auto result = CheckSite(fromCfg, toSite);
    if (result != ERR_OK) return result;

    auto *toItem = mItemList.at(toSite);
    DATA::Item *toCfg = nullptr;
    if (toItem) {
        toCfg = sItemConfig.Get(toItem->GetTemplateID());
        if (!toCfg) return ERR_ITEM_NO_DATA_ROW;
        result = CheckSite(toCfg, fromSite);
        if (result != ERR_OK) return result;
    }
    
    bool ret = true;
    if (CheckWearEquipSite(toSite)) {
        if(fromCfg->Type != item_type_equip) return ERR_ITEM_CANT_EQUIP;

        auto subtype = fromItem->GetSubType() ? fromItem->GetSubType() : fromCfg->SubType;
        if (!IsCanUseEquipSiteByType(subtype, toSite)) return ERR_ITEM_EQUIP_NOT_SUIT_SITE;

        if (fromCfg->Gender != gender_nullptr && self->GetRoleProp(role_gender) != fromCfg->Gender) return ERR_ITEM_EQUIP_GENDER;
        if (fromCfg->Job != job_nullptr && self->GetRoleProp(role_job) != fromCfg->Job) return ERR_ITEM_EQUIP_JOB;

        if (toItem) {
            TRIGGER_EVENT_RET<bool>(ret, self, trigger_pre_un_equip, self->GetGUIDAsString(), toItem->GetGUIDAsString(), toCfg->Id, toSite);
            if (!ret) return ERR_ITEM_MOVE;
        }

        TRIGGER_EVENT_RET<bool>(ret, self, trigger_pre_equip, self->GetGUIDAsString(), fromItem->GetGUIDAsString(), fromCfg->Id, fromSite);
        if (!ret) return ERR_ITEM_MOVE;
    }
    else if (CheckWearEquipSite(fromSite)) {
        if (toItem) {
            if (toCfg->Type != item_type_equip) return ERR_ITEM_CANT_EQUIP;

            auto subtype = toItem->GetSubType() ? toItem->GetSubType() : toCfg->SubType;
            if (!IsCanUseEquipSiteByType(subtype, fromSite)) return ERR_ITEM_EQUIP_NOT_SUIT_SITE;

            if (toCfg->Gender != gender_nullptr && self->GetRoleProp(role_gender) != toCfg->Gender) return ERR_ITEM_EQUIP_GENDER;
            if (toCfg->Job != job_nullptr && self->GetRoleProp(role_job) != toCfg->Job) return ERR_ITEM_EQUIP_JOB;
        }

        TRIGGER_EVENT_RET<bool>(ret, self, trigger_pre_un_equip, self->GetGUIDAsString(), fromItem->GetGUIDAsString(), fromCfg->Id, fromSite);
        if (!ret) return ERR_ITEM_MOVE;

        if (toItem) {
            TRIGGER_EVENT_RET<bool>(ret, self, trigger_pre_equip, self->GetGUIDAsString(), toItem->GetGUIDAsString(), toCfg->Id, toSite);
            if (!ret) return ERR_ITEM_MOVE;
        }
    }

	std::swap(mItemList.at(toSite), mItemList.at(fromSite));
    fromItem->SetSite(toSite);
    if (toItem) toItem->SetSite(fromSite);

    OnSwapItem(toSite, fromSite, log_params{ "移动更新" });
    OnUnloadEquip(fromSite, toSite);

    UpdateParam up;
    up.reason = "移动更新";


    auto CheckUpdate = [&](uint16_t toSite, uint16_t fromSite) {
        if (!mItemList.at(fromSite) || !mItemList.at(toSite)) return false;
        if (!CheckWearEquipSite(fromSite) || !CheckWearEquipSite(toSite)) return false;
            
        return true;
        };
    if (CheckUpdate(toSite, fromSite))
    {
        // 不更新
    }
    else if (CheckWearEquipSite(toSite)) {
        if (mItemList.at(fromSite)) {
            up.beWear = false;
            up.site = fromSite;
            OnUpdateUseItem(mItemList.at(fromSite)->GetTemplateID(), up);
            TRIGGER_EVENT(self, trigger_post_un_equip, self->GetGUIDAsString(), mItemList.at(fromSite)->GetGUIDAsString(), mItemList.at(fromSite)->GetTemplateID());
        }
        if (mItemList.at(toSite)) {
            up.beWear = true;
            up.site = toSite;
            OnUpdateUseItem(mItemList.at(toSite)->GetTemplateID(), up);
            TRIGGER_EVENT(self, trigger_post_equip, self->GetGUIDAsString(), mItemList.at(toSite)->GetGUIDAsString(), mItemList.at(toSite)->GetTemplateID(), toSite);
        }
    }
    else  if (CheckWearEquipSite(fromSite)) {
        if (mItemList.at(toSite)) {
            up.beWear = false;
            up.site = toSite;
            OnUpdateUseItem(mItemList.at(toSite)->GetTemplateID(), up);
            TRIGGER_EVENT(self, trigger_post_un_equip, self->GetGUIDAsString(), mItemList.at(toSite)->GetGUIDAsString(), mItemList.at(toSite)->GetTemplateID());
        }
        if (mItemList.at(fromSite)) {
            up.beWear = true;
            up.site = fromSite;
            OnUpdateUseItem(mItemList.at(fromSite)->GetTemplateID(), up);
            TRIGGER_EVENT(self, trigger_post_equip, self->GetGUIDAsString(), mItemList.at(fromSite)->GetGUIDAsString(), mItemList.at(fromSite)->GetTemplateID(), fromSite);
        }
    }
    
	if (self->IsPlayer()) {
		auto player = static_cast<Player*>(self);
		auto item = mItemList.at(toSite);
		if (nullptr != item) {
			player->SendItemAttrNtf(item->GetGUID(), item_att_pos, item->GetSite());
		}
		item = mItemList.at(fromSite);
		if (nullptr != item) {
			player->SendItemAttrNtf(item->GetGUID(), item_att_pos, item->GetSite());
		}
	}

	return ERR_OK;
}

int RolePack::SplitItem(uint64_t fromItemGUID, uint16_t amount, uint16_t toSite)
{
    auto* self = GetMaster();
    if (!self) return ERR_NOROLEDATA;

    auto* fromItem = FindItem(fromItemGUID);
    if (!fromItem) return ERR_ITEM_NOT_EXIST;

    auto* fromCfg = sItemConfig.Get(fromItem->GetTemplateID());
    if (!fromCfg) return ERR_ITEM_NO_DATA_ROW;

    uint16_t fromSite = fromItem->GetSite();
    if (fromSite == INVALID_ITEM_SITE) return ERR_ITEM_SITE;

    // 只能是背包或者仓库
    if (toSite < site_bag_0 || toSite >= site_bag_end) return ERR_ITEM_SITE;
    if (fromSite < site_bag_0 || fromSite >= site_bag_end) return ERR_ITEM_SITE;
    if (toSite == fromSite) return ERR_OK;

    auto result = CheckSite(fromCfg, toSite);
    if (result != ERR_OK) return result;

    uint16_t fromAmount = fromItem->GetAmount();
    amount = amount >= fromAmount ? fromAmount : amount;
    if (!amount) return  ERR_OK;

    auto* toItem = mItemList.at(toSite);
    if (toItem)
    {
        if (toItem->GetTemplateID() != fromItem->GetTemplateID()) return ERR_ITEM_SPLIT;

        uint16_t toAmount = toItem->GetAmount();
        int16_t leftAmount = fromCfg->Stack - toAmount;
        if (leftAmount <= 0) return ERR_OK;
        amount = amount >= leftAmount ? leftAmount : amount;

        RemoveItem(fromItemGUID, amount, log_params{ "拆分更新" });
        toItem->SetAmount(toAmount + amount);
        OnUpdateItem(toSite, amount, toAmount, log_params{ "拆分更新" });
        NtfMasterUpdateItem(toSite);
    }
    else
    {
        if (amount == fromItem->GetAmount()) 
            return MoveItem(fromItemGUID, toSite);

        RoleItem* addItem = GenerateRoleItemByRoleItem(fromItem, toSite);
        if (nullptr == addItem) return ERR_ITEM_SPLIT;
        addItem->SetGUID(GenerateObjID(E_OBJ_ITEM, ConfigInfo::GetInstance()));
        addItem->SetAmount(amount);
        RemoveItem(fromItemGUID, amount, log_params{ "拆分更新" });
        mItemList.at(toSite) = addItem;
        NtfMasterAddItem(toSite);
        OnAddItem(toSite, log_params{ "拆分更新" });
    }
    return ERR_OK;
}

int RolePack::DropItem(uint64_t itemGUID)
{
	auto master = GetMaster();
	if (nullptr == master) return ERR_NOROLEDATA;

	auto site = GetItemSite(itemGUID);
	if (site == INVALID_ITEM_SITE) return ERR_ITEM_NOT_EXIST;

    auto itemCfg = sItemConfig.Get(mItemList.at(site)->GetTemplateID());
    if (nullptr == itemCfg) return ERR_ITEM_NO_DATA_ROW;

    // 判断是否可以丢弃
    if (!itemCfg->CheckEnable(item_enable_drop)) return ERR_ITEM_DROP_ITEM;

    // 安全区域不可丢弃
    if (master->IsInSafeRegion()) return ERR_ITEM_DROP;


    //丢弃物品是否销毁
    bool destroyItem = false;
    TRIGGER_EVENT_RET<bool>(destroyItem, trigger_drop_item_whether_destroy, master->GetGUIDAsString(), mItemList[site]->GetGUIDAsString(), mItemList[site]->GetIsBind());
	//if (!mItemList[site]->GetIsBind()) {
    if (!destroyItem) {

		auto map = master->GetCurMap();
		if (nullptr == map || !map->OnRoleDropItem(master, mItemList.at(site))) {
			return ERR_ROLE_DROP_GRID;
		}
	}

    RemoveItem(itemGUID, 0, log_params{ "丢弃消失" });
	return ERR_OK;
}

void RolePack::Arrange(uint16_t start, uint16_t end)
{
    if (std::max<uint16_t>(start, end) >= site_end) return;
    auto* player = GetPlayer();
    if (!player) return;

    std::vector<uint16_t> sameSet;
    std::set<uint16_t> beSet;
    
    auto CheckCanMerge = [&](RoleItem* x, RoleItem* y, DATA::Item* cfg) {
        if (!x || !y || !cfg) return false;
        if (x->GetTemplateID() != y->GetTemplateID()) return false;
        if (x->GetIsBind() != y->GetIsBind()) return false;
        if (beSet.find(y->GetSite()) != beSet.end()) return false;

        beSet.insert(y->GetSite());
        if (y->GetAmount() >= cfg->Stack) return false;

        return true;
    };

    log_params lp{ "背包整理" };
    for (uint16_t i = start; i < end; i++)
    {
        if (!mItemList.at(i)) continue;

        auto cfg = sItemConfig.Get(mItemList.at(i)->GetTemplateID());
        if (!cfg) continue;
        if (cfg->Stack <= 1) continue;
        if (mItemList.at(i)->GetAmount() >= cfg->Stack) continue;

        sameSet.clear();
        sameSet.push_back(i);
        for (uint16_t j = i + 1; j < end; ++j)
        {
            if (CheckCanMerge(mItemList.at(i), mItemList.at(j), cfg))
                sameSet.push_back(j);
        }
        if (sameSet.size() <= 1) continue;

        uint16_t mergeToIdx = 0, mergeFromIdx = sameSet.size() - 1;
        for (; mergeToIdx < mergeFromIdx;)
        {
            uint16_t toLeft = mItemList.at(sameSet[mergeToIdx])->GetAmount();
            uint16_t fromLeft = mItemList.at(sameSet[mergeFromIdx])->GetAmount();
            bool beMerge = true;
            if (toLeft >= cfg->Stack)
            {
                mergeToIdx++;
                beMerge = false;
            }
            if (!fromLeft)
            {
                RemoveItem(sameSet[mergeFromIdx], lp);
                mergeFromIdx--;
                beMerge = false;
            }
            if (!beMerge) continue;

            uint16_t toNeed = cfg->Stack - toLeft;
            uint16_t changeNum = fromLeft <= toNeed ? fromLeft : toNeed;
            // 配置出错导致toNeed可能为0,导致changeNum为0会出现死循环
            if (!changeNum)
            {
                mergeToIdx++;
                continue;
            }
            mItemList.at(sameSet[mergeToIdx])->SetAmount(toLeft + changeNum);
            OnUpdateItem(sameSet[mergeToIdx], changeNum, toLeft, lp);
            mItemList.at(sameSet[mergeFromIdx])->SetAmount(fromLeft - changeNum);
            OnUpdateItem(sameSet[mergeFromIdx], -changeNum, fromLeft, lp);
        }
    }

    sort(mItemList.begin() + start, mItemList.begin() + end, [](RoleItem* x, RoleItem* y) {
        if (!x) return false;
        if (!y) return true;
        auto xCfg = sItemConfig.Get(x->GetTemplateID());
        auto yCfg = sItemConfig.Get(y->GetTemplateID());
        if (!xCfg) return false;
        if (!yCfg) return true;
        if (xCfg->LS2 != yCfg->LS2) return xCfg->LS2 < yCfg->LS2;
        if (x->GetIsBind() != y->GetIsBind()) return x->GetIsBind() < y->GetIsBind();
        if (xCfg->Id != yCfg->Id) return xCfg->Id < yCfg->Id;
        return x->GetAmount() > y->GetAmount();
    });
    /*
    uint16_t head = start, tail = start;
    while (tail < end && head < end)
    {
        if (head == tail || nullptr == mItemList.at(tail))
        {
            tail++;
            continue;
        }
        if (nullptr != mItemList.at(head))
        {
            head++;
            continue;
        }
        swap(mItemList.at(tail), mItemList.at(head));
        head++;
        tail++;
    }
    */
    for (int16_t i = start; i < end; i++) {
        if (nullptr != mItemList.at(i)) {
            mItemList.at(i)->SetSite(i);
            player->SendItemAttrNtf(mItemList.at(i)->GetGUID(), item_att_pos, mItemList.at(i)->GetSite()); 
            player->SendItemAttrNtf(mItemList.at(i)->GetGUID(), item_att_amount, mItemList.at(i)->GetAmount());
        }
    }

    return;
}

// 整理背包  仓库  高级仓库          没有给类别增加枚举，如果后续需要在logic_def中添加并修改本处
int RolePack::ItemArrange(unsigned char type)
{
    auto master = GetMaster();
    if (!master || !master->IsPlayer())  return ERR_NOROLEDATA;

    switch (type)
    {
    case 0:     // 0是背包
        Arrange(site_bag_0, site_warehouse);
        break;
    case 1:     // 1是仓库
        //LOG_ERROR("暂未实现");
        Arrange(site_warehouse, site_warehouse_adv);
        break;
    case 2:     // 2是高级仓库
        Arrange(site_warehouse_adv, site_bag_end);
        //LOG_ERROR("暂未实现");
        break;
    default:
        break;
    }

    return ERR_OK;
}

int RolePack::PickUpItem()
{
	auto master = GetMaster();
	if (nullptr == master) return ERR_NOROLEDATA;

	auto map = master->GetCurMap();
	if (nullptr == map) {
		return ERR_ITEM_PICK_UP_NO_SHOW;
	}

	auto sceneItem = map->GetSceneItem(master->GetRolePosX(), master->GetRolePosY());
	if (nullptr == sceneItem) {
		return ERR_ITEM_PICK_UP_NON;
	}

    return PickUpItem(sceneItem);
}

int RolePack::PickUpItem(SceneItem *item)
{
    if (!item) return ERR_ITEM_PICK_UP_NON;

    auto *master = GetMaster();
    if (!master) return ERR_NOROLEDATA;

    auto *map = master->GetCurMap();
    if (!map) return ERR_ITEM_PICK_UP_NO_SHOW;

    auto itemCfg = sItemConfig.Get(item->GetTemplateID());
    if (nullptr == itemCfg) return ERR_ITEM_PICK_UP_NO_SHOW;

    auto err = item->IsCanPickupWithErr(master);
    if (err != ERR_OK)return err;
    //if (!item->IsCanPickup(master)) return ERR_ITEM_PICKUP;

    bool prePickUp = true;
    TRIGGER_EVENT_RET<bool>(prePickUp, trigger_pre_item_pickup, master->GetGUIDAsString(), item->GetGUIDAsString(), item->GetTemplateID(), item->GetPosX(), item->GetPosY());
    if (!prePickUp) return ERR_ITEM_PICK_UP_NO_SHOW;

    uint16_t site = INVALID_ITEM_SITE;
    if (mBeAutoStack && item_type_equip != itemCfg->Type)
    {
        log_params lp{ "拾取获得", 0 };
        int32_t res = AddItem(item->GetTemplateID(), item->GetAmount(), bind_type(item->GetIsBind()), site_range_bag, lp);
        site = lp.site;
        if (res != ERR_OK) return (res == ERR_BAG_SPACE_NOT_ENOUGH) ? res : ERR_ITEM_PICK_UP_NO_SHOW;
    }
    else
    {
        site = AddItemToBag(item, log_params{ "拾取获得" });
    }
    if (site == INVALID_ITEM_SITE) return ERR_BAG_SPACE_NOT_ENOUGH;
    auto roleItem = GetItem(site);
    if (!roleItem) return ERR_ITEM_PICK_UP_NO_SHOW;

    TRIGGER_EVENT(trigger_item_pickup, master->GetGUIDAsString(), roleItem->GetGUIDAsString(), roleItem->GetTemplateID(), roleItem->GetAmount());

    if (!map->DestroySceneItem(item->GetGUID(),item->GetPosX(), item->GetPosY()))
        return ERR_ITEM_PICK_UP_NO_SHOW;

    return ERR_OK;
}

int RolePack::AutoPickupItem(const Point *pos, uint8_t num)
{
    if (!pos) return ERR_UNKNOW;

    auto *player = GetPlayer();
    if (!player) return ERR_NOROLEDATA;

    auto *map = player->GetCurMap();
    if (!map || !map->SupportAutoPickItem()) return ERR_ITEM_PICKUP;

    const auto &autoPickupSettings = player->GetRoleSettings().auto_pickup;

    auto interval = autoPickupSettings.interval;
    if (interval == 0) interval = AUTO_PICKUP_DEFINTVL;

    auto curTimestamp = GetTimeStampMillisecond();
    if (curTimestamp - mLastAutoPickTime < interval)
        return ERR_ITEM_PICKUP;

    int ret = ERR_OK;
    for (uint8_t i = 0; i < num; ++i) {
        auto err = AutoPickupItem(pos[i].x, pos[i].y);
        if (err == ERR_OK) {
            continue;
        }

        if (err != ERR_OK && err != ERR_ITEM_RANGE_PICK_UP_NON && err != ERR_ITEM_PICK_UP_NO_SHOW) {
            ret = ERR_ITEM_PICKUP;
        }
        else if (err == ERR_ITEM_RANGE_PICK_UP_NON && ret == ERR_OK)
        {
            ret = ERR_ITEM_RANGE_PICK_UP_NON;
        }
    }

    mLastAutoPickTime = curTimestamp;
    return ret;
}

int RolePack::AutoPickupItem(uint16_t x, uint16_t y)
{
    auto *player = GetPlayer();

    const auto &autoPickupSettings = player->GetRoleSettings().auto_pickup;
    switch (autoPickupSettings.mode) {

    case auto_pick_item_mode_around:
        if (player->DistanceFromPos(x, y) > autoPickupSettings.radius)
            return ERR_ITEM_PICKUP;
        break;

    case auto_pick_item_mode_designated:
    {
        auto dx = x - player->GetRolePosX();
        auto dy = y - player->GetRolePosY();
        Point pt(static_cast<int16_t>(dx), static_cast<int16_t>(dy));

        const auto *begin = autoPickupSettings.relpos;
        const auto *end = begin + autoPickupSettings.numpos;
        const auto *it = std::find(begin, end, pt);
        if (it == end) return ERR_ITEM_PICKUP;
        break;
    }

    default:
        return ERR_ITEM_PICKUP;
    }

    auto *map = player->GetCurMap();
    auto *sceneItem = map->GetSceneItem(x, y);
    if (!sceneItem) return ERR_ITEM_RANGE_PICK_UP_NON;
    return AutoPickupItem(sceneItem);
}

int RolePack::AutoPickupItem(SceneItem *item)
{
    if (!item) return ERR_UNKNOW;

    auto *self = GetMaster();
    if (!self) return ERR_NOUSERDATA;

    auto *map = self->GetCurMap();
    if (!map) return ERR_ITEM_PICKUP;

    const auto *itemCfg = sItemConfig.Get(item->GetTemplateID());
    if (!itemCfg) return ERR_ITEM_NO_DATA_ROW;

    auto err = item->IsCanPickupWithErr(self);
    if (err != ERR_OK)return err;
    //if (!item->IsCanPickup(self)) return ERR_ITEM_PICKUP;

    bool canPickup = true;
    TRIGGER_EVENT_RET<bool>(canPickup, trigger_pre_item_pickup, self->GetGUIDAsString(),
        item->GetGUIDAsString(), item->GetTemplateID(), item->GetPosX(), item->GetPosY());
    if (!canPickup) return ERR_ITEM_PICKUP;

    uint16_t site = INVALID_ITEM_SITE;
    if (mBeAutoStack && item_type_equip != itemCfg->Type)
    {
        log_params lp{ "自动拾取获得", 0 };
        int32_t res = AddItem(item->GetTemplateID(), item->GetAmount(), bind_type(item->GetIsBind()), site_range_bag, lp);
        site = lp.site;
        if (res != ERR_OK) return ERR_ITEM_PICKUP;
    }
    else
    {
        site = AddItemToBag(item, log_params{ "自动拾取获得" });
    }
    if (site == INVALID_ITEM_SITE) return ERR_ITEM_PICK_UP_NO_SHOW;
    auto roleItem = GetItem(site);
    if (!roleItem) return ERR_ITEM_PICKUP;

    NotifyAroundPlayers_PickupItem(item);
    TRIGGER_EVENT(trigger_item_pickup, self->GetGUIDAsString(), roleItem->GetGUIDAsString(), roleItem->GetTemplateID(), roleItem->GetAmount());

    map->DestroySceneItem(item->GetGUID(),item->GetPosX(), item->GetPosY());
    return ERR_OK;
}

void RolePack::NotifyAroundPlayers_PickupItem(SceneItem *item)
{
    if (!item) return;

    auto *self = GetMaster();
    if (!self) return;

    auto *map = self->GetCurMap();
    if (!map) return;

    auto x = item->GetPosX();
    auto y = item->GetPosY();

    ProtoMS_ItemPickupNtf data;
    data.role_guid = self->GetGUID();
    data.item_guid = item->GetGUID();

    auto f = [&](Role *role)
    {
        if (!role || !role->IsPlayer()) return;
        auto *player = static_cast<Player *>(role);
        data.clsessid = player->GetClSessionID();
        SendDataBySessionID(player->GetGsSessionID(), data);
    };

    map->ApplyFuncToAllPlayersInAroundRegions(x, y, f);
}

void RolePack::NtfMasterAddItem(uint16_t site, bool isPackItem)
{
	if (site < 0 || site >= site_end) {
		return;
	}

	auto item = mItemList.at(site);
	if (nullptr == item) {
		return;
	}

	auto *player = GetPlayer();
    if (!player) return;

	auto& ack = gProtoMS_ItemAddAck;
	ack.isPackItem = isPackItem;
    item->GenerateItemInfo(ack.info);

	//LOG_NORMAL("@@@@@ NtfMasterAddItem %d : %" PRIu64, ack.info.base_info.site, ack.info.base_info.guid);
	player->SendAddItem(ack);
}

void RolePack::NtfMasterUpdateItem(uint16_t site)
{
    if (site < 0 || site >= site_end) {
        return;
    }

    auto item = mItemList.at(site);
    if (nullptr == item) {
        return;
    }

    auto *player = GetPlayer();
    if (!player) return;

    auto& ntf = gProtoMS_ItemUpdateNtf;

    item->GenerateItemInfo(ntf.info);

    player->SendItemUpdateNtf(ntf);
}

void RolePack::OnAddItem(uint16_t nSite, const log_params& lp)
{
    auto *item = GetItem(nSite);
    if (!item) return;

    ItemMap::GetInstance()->AddItem(item);

    auto *pPlayer = GetPlayer();
    if (!pPlayer) return;
    //pPlayer->OnAddItem(nSite);

    if (!mItemList.at(nSite)) return;
    TRIGGER_EVENT(trigger_add_item, pPlayer->GetGUIDAsString(), mItemList.at(nSite)->GetGUIDAsString(), mItemList.at(nSite)->GetTemplateID(), nSite);
    OnUpdateItem(nSite, mItemList.at(nSite)->GetAmount(), 0, lp);
}

void RolePack::OnRemoveItem(uint16_t nSite, const log_params& lp)
{
    auto *item = GetItem(nSite);
    if (!item) return;

    auto *itemMap = ItemMap::GetInstance();
    if (!itemMap) return;

    auto id = item->GetGUID();
    auto *cur = itemMap->GetItem(id);

    if (item == cur) {      // 丢弃物品时cur为场景物品
        itemMap->RemoveItem(id);
    }

    auto *pPlayer = GetPlayer();
    if (!pPlayer) return;
    //pPlayer->OnRemoveItem(nSite);

    if (!mItemList.at(nSite)) return;
    OnUpdateItem(nSite, -mItemList.at(nSite)->GetAmount(), mItemList.at(nSite)->GetAmount(), lp);
}

void RolePack::OnUpdateItem(uint16_t nSite, int32_t nNum, int32_t bef, const log_params& lp)
{
    auto *pPlayer = GetPlayer();
    if (!pPlayer) return;
    //pPlayer->OnUpdateItem(nSite, nNum);

    if (!mItemList.at(nSite)) return;

    if (LOG_PARAMS_INFO_INIT != lp.info)
    {
        SendDBLogData(log_type_item_update, LogItemUpdate(pPlayer->GetGUID(), mItemList.at(nSite)->GetGUID(),
            mItemList.at(nSite)->GetTemplateID(), nSite, item_att_amount, bef, nNum, bef + nNum, mItemList.at(nSite)->GetName(), 0, lp.info));
    }
}

void RolePack::OnSwapItem(uint16_t nSite1, uint16_t nSite2, const log_params& lp)
{
    auto *pPlayer = GetPlayer();
    if (!pPlayer) return;
    //pPlayer->OnSwapItem(nSite1, nSite2);

    if (mItemList.at(nSite1))
    {
        SendDBLogData(log_type_item_update, LogItemUpdate(pPlayer->GetGUID(), mItemList.at(nSite1)->GetGUID(), 
            mItemList.at(nSite1)->GetTemplateID(), nSite2, item_att_pos, nSite2, 0, nSite1, mItemList.at(nSite1)->GetName(), 0, lp.info));
    }
    if (mItemList.at(nSite2))
    {
        SendDBLogData(log_type_item_update, LogItemUpdate(pPlayer->GetGUID(), mItemList.at(nSite2)->GetGUID(),
            mItemList.at(nSite2)->GetTemplateID(), nSite1, item_att_pos, nSite1, 0, nSite2, mItemList.at(nSite2)->GetName(), 0, lp.info));
    }
}

void RolePack::OnUseEquip(uint16_t site, uint16_t toSite)
{
    auto *player = GetPlayer();
    if (!player) return;
    if (!CheckWearEquipSite(site) && !CheckWearEquipSite(toSite)) return;

    player->OnUseEquip(site);
}

void RolePack::OnUnloadEquip(uint16_t site, uint16_t toSite)
{
    auto *player = GetPlayer();
    if (!player) return;
    if (!CheckWearEquipSite(site) && !CheckWearEquipSite(toSite)) return;

    player->OnUnloadEquip(site);
}

void RolePack::UpdateEquipBySite(uint16_t site)
{
    auto* master = GetMaster();
    if (!master) return;
    auto* item = GetItem(site);
    if (nullptr == item) return;
    master->temp_attr_type = 3;
    master->temp_attr_id = item->GetTemplateID();
    UpdateParam up;
    up.beWear = true;
    up.site = site;
    up.reason = LOG_PARAMS_INFO_INIT;
    OnUpdateUseItem(item->GetTemplateID(), up);
    TRIGGER_EVENT(master, trigger_post_equip, master->GetGUIDAsString(), item->GetGUIDAsString(), item->GetTemplateID(), site);
    master->temp_attr_type =0;
    master->temp_attr_id = 0;
}

void RolePack::GetSiteRange(site_range nSiteRange, int &nSiteBegin, int &nSiteEnd)
{
    switch (nSiteRange) {

    case site_range_all:
        nSiteBegin = site_weapon;
        nSiteEnd = site_end;
        break;

    case site_range_bag:
        nSiteBegin = site_bag_0;
        nSiteEnd = site_bag_0 + GetTotalBagCount();
        break;

    case site_range_equip:
        nSiteBegin = site_weapon;
        nSiteEnd = site_equip_end;
        break;
    case site_range_quick:
        nSiteBegin = site_item_quick_bar_0;
        nSiteEnd = site_item_quick_bar_end;
    default:
        nSiteBegin = 0;
        nSiteEnd = 0;
        break;
    }
}

bool RolePack::IsInSiteRange(uint16_t nSite, site_range nSiteRange)
{
    int nSiteBegin, nSiteEnd;
    GetSiteRange(nSiteRange, nSiteBegin, nSiteEnd);
    return (nSite >= nSiteBegin && nSite < nSiteEnd);
}

RoleItem * RolePack::GetItem(uint16_t nSite)
{
    return (nSite < mItemList.size()) ? mItemList.at(nSite) : nullptr;
}

uint16_t RolePack::GetItemID(uint16_t site)
{
    auto *item = GetItem(site);
    if (!item) return 0;
    return item->GetTemplateID();
}

std::vector<RoleItem *> RolePack::GetAllEquipments()
{
    std::pair<int, int> ranges[] = {
        {site_weapon, site_equip_end},
        {site_glasses, site_equip_reserved_end},
        {site_equip_custom_0, site_equip_custom_end},
        {site_fashion_helmet, site_fashion_end}
    };

    std::vector<RoleItem *> items;

    for (const auto &range : ranges) {
        for (auto i = range.first; i < range.second; ++i) {
            auto *item = mItemList.at(i);
            if (!item) continue;
            items.push_back(item);
        }
    }

    return items;
}


RoleItem* RolePack::GenerateRoleItemByItemCfg(DATA::Item* itemCfg, int16_t site)
{
    auto master = GetMaster();
    if (nullptr == master) return nullptr;

    if (nullptr == itemCfg)  return nullptr;

    RoleItem* item = new RoleItem();
    item->SetGUID(GenerateObjID(E_OBJ_ITEM, ConfigInfo::GetInstance()));
    item->SetName(itemCfg->Name);
    item->SetLife(itemCfg->TimeLimit);
    item->SetAmount(1);
    item->SetTemplateID(itemCfg->Id);
    item->SetRoleid(master->GetGUID());
    item->SetSite(site);
    item->SetDurability(itemCfg->Durability);
    item->SetMaxDurability(itemCfg->Durability);
    item->SetUse_count(itemCfg->UseCount);
    item->SetIsBind(itemCfg->BindType);
    return item;
}

RoleItem* RolePack::GenerateRoleItemByRoleItem(RoleItem* item, int16_t site)
{
    auto master = GetMaster();
    if (nullptr == master) return nullptr;

    RoleItem* addItem = new RoleItem(item);
    addItem->SetRoleid(master->GetGUID());
    addItem->SetSite(site);
    return addItem;
}

int32_t RolePack::CheckSite(DATA::Item* itemCfg, uint16_t site)
{
    auto master = GetMaster();
    if (nullptr == master) return ERR_NOROLEDATA;

    if (site >= site_bag_0 && site < site_warehouse)
    {
        if (site < site_bag_1 && (master->GetRoleProp(role_bag_size_0) + site_bag_0 <= site)) return ERR_ITEM_MOVE;
        else if (site < site_bag_2 && (master->GetRoleProp(role_bag_size_1) + site_bag_1 <= site)) return ERR_ITEM_MOVE;
        else if (site < site_bag_3 && (master->GetRoleProp(role_bag_size_2) + site_bag_2 <= site)) return ERR_ITEM_MOVE;
        else if (site < site_bag_4 && (master->GetRoleProp(role_bag_size_3) + site_bag_3 <= site)) return ERR_ITEM_MOVE;
        else if (site < site_warehouse && (master->GetRoleProp(role_bag_size_4) + site_bag_4 <= site)) return ERR_ITEM_MOVE;
    }
    // 判断是否可以放入仓库
    else if (site >= site_warehouse && site < site_bag_end)
    {
        if (!itemCfg) return ERR_OK;
        if (!itemCfg->CheckEnable(item_enable_warehousing)) return ERR_ITEM_FORBID_WAREHOUS;
        // 普通仓库格子是否足够
        if (site < site_warehouse_adv && (master->GetRoleProp(role_warehouse_size) + site_warehouse <= site)) return ERR_ITEM_MOVE;
        // 高级仓库格子是否足够
        else if (site < site_bag_end && (master->GetRoleProp(role_warehouse_adv_size) + site_warehouse_adv <= site)) return ERR_ITEM_MOVE;
    }
    else if (site >= site_item_quick_bar_0 && site < site_item_quick_bar_end)
    {
        if (!itemCfg) return ERR_OK;
       //开接口给脚本  判断能不能放
        bool issued = true;
        TRIGGER_EVENT_RET<bool>(issued,trigger_item_CheckSite, itemCfg->Id,site);
        if (!issued)
        {
            return ERR_ITEM_MOVE;
        }
    }
    return ERR_OK;
}