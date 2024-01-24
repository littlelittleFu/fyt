#pragma once

#include "group_attr.hpp"

enum eGroupAttrPropType 
{
    GROUP_ATTR_PROP_TYPE_MIN = 0,

    GROUP_ATTR_PROP_ID,
    GROUP_ATTR_PROP_DESC,
    GROUP_ATTR_PROP_GROUPINFO,

    GROUP_ATTR_PROP_TYPE_MAX,
};

inline bool GetGroupAttrProp(uint16_t nGroupID, uint16_t nPropType)
{
    if (nPropType <= GROUP_ATTR_PROP_TYPE_MIN || nPropType >= GROUP_ATTR_PROP_TYPE_MAX) return false;

    auto pConfig = sGroupAttrConfig.Get(nGroupID);
    if (!pConfig) return false;

    LUA_SAFE_BEGIN();

    switch (nPropType) 
    {
        SETCASE(GROUP_ATTR_PROP_ID, Id);
        SETCASE(GROUP_ATTR_PROP_DESC, Desc);
        SETCASE_MAP(GROUP_ATTR_PROP_GROUPINFO, GroupInfo);
    }

    LUA_SAFE_END(false);

    return true;
}
