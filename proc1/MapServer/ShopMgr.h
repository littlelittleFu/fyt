#pragma once
#include <map>


class ShopMgr
{
    DECL_SINGLETON(ShopMgr)

private:
    using ShopItems = std::map<uint8_t, SHOP_ITEM_INFO>;        // item index -> shop item info
    using Shops = std::map<uint16_t, ShopItems>;                // shop id -> shop items

public:
    bool InitShop(uint16_t nShopID);

    const ShopItems * GetShopItems(uint16_t nShopID);

    SHOP_ITEM_INFO * GetShopItem(uint16_t nShopID, uint8_t nItemIndex);

private:
    ShopMgr() {}

private:
    Shops   m_Shops;
};
