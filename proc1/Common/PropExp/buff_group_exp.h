#pragma once

#include "buff_group_table.hpp"

enum eBuffGroupPropType {
    BUFF_GROUP_PROP_TYPE_MIN = 0,

    BUFF_GROUP_PROP_ID,
    BUFF_GROUP_GROUPID_1,
    BUFF_GROUP_GROUPID_2,
    BUFF_GROUP_GROUPRELATION,

    BUFF_GROUP_PROP_TYPE_MAX,
};

inline bool GetBuffGroupProp(uint16_t g1, uint16_t g2, uint16_t nPropType)
{
    DATA::GroupIdKey key(g1, g2);
    auto pConfig = sBuffGroupConfig.GetByGroupIdKey(key);
    if (!pConfig) return false;

    if (nPropType <= BUFF_GROUP_PROP_TYPE_MIN || nPropType >= BUFF_GROUP_PROP_TYPE_MAX) return false;

    LUA_SAFE_BEGIN();

    switch (nPropType) {

        SETCASE(BUFF_GROUP_PROP_ID, Id);
        SETCASE(BUFF_GROUP_GROUPID_1, GroupId1);
        SETCASE(BUFF_GROUP_GROUPID_2, GroupId2);
        SETCASE(BUFF_GROUP_GROUPRELATION, GroupRelation);
    }

    LUA_SAFE_END(false);

    return true;
}
