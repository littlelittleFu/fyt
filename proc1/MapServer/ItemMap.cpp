#include "stdafx.h"
#include "ItemMap.h"
#include "ItemBase.h"

IMPL_SINGLETON(ItemMap)

void ItemMap::AddItem(ItemBase *item)
{
    if (!item) return;

    auto id = item->GetGUID();
    mItems[id] = item;
}

ItemBase * ItemMap::GetItem(uint64_t id)
{
    auto it = mItems.find(id);
    return it == mItems.end() ? nullptr : it->second;
}
