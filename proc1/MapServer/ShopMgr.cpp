#include "stdafx.h"
#include "ShopMgr.h"

IMPL_SINGLETON(ShopMgr)

bool ShopMgr::InitShop(uint16_t nShopID)
{
    if (m_Shops.find(nShopID) != m_Shops.end()) return true;

    auto pShopConfig = sShopConfig.GetShop(nShopID);
    if (!pShopConfig) return false;

    auto &rShop = m_Shops[nShopID];

    for (auto it : *pShopConfig) {

        if (it.second->NotSell) continue;

        auto pItemConfig = sItemConfig.GetByKeyName(it.second->ItemKeyName);
        if (!pItemConfig) continue;

        auto &rItem = rShop[it.first];
        rItem.index = it.first;
        rItem.id = pItemConfig->Id;
        rItem.num = it.second->ItemNum ? it.second->ItemNum : INFINITE_ITEM_NUM;
        // 后面配在npc脚本里
        rItem.value = 0;
    }

    return true;
}

const ShopMgr::ShopItems * ShopMgr::GetShopItems(uint16_t nShopID)
{
    auto it = m_Shops.find(nShopID);
    if (it == m_Shops.end()) return nullptr;
    return &it->second;
}

SHOP_ITEM_INFO * ShopMgr::GetShopItem(uint16_t nShopID, uint8_t nItemIndex)
{
    auto it = m_Shops.find(nShopID);
    if (it == m_Shops.end()) return nullptr;

    auto it2 = it->second.find(nItemIndex);
    if (it2 == it->second.end()) return nullptr;

    return &it2->second;
}
