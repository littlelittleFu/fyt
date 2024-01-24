#pragma once

#include <unordered_map>


class ItemBase;

class ItemMap
{
    DECL_SINGLETON(ItemMap);

public:
    void AddItem(ItemBase *item);
    ItemBase * GetItem(uint64_t id);
    void RemoveItem(uint64_t id) { mItems.erase(id); }

private:
    ItemMap() {}
    ~ItemMap() {}

private:
    std::unordered_map<uint64_t, ItemBase *> mItems;
};
