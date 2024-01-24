#pragma once

#include "buff_table.hpp"

enum eBuffPropType {
    BUFF_PROP_TYPE_MIN = 0,

    BUFF_PROP_ID,
    BUFF_PROP_NAME,
    BUFF_PROP_KEYNAME,
    BUFF_PROP_ICON,
    BUFF_PROP_SHOWICON,
    BUFF_PROP_INDEX,
    BUFF_PROP_MAGICID,
    BUFF_PROP_DESC,
    BUFF_PROP_TYPE,
    BUFF_PROP_GROUPID,
    BUFF_PROP_GROUPRELATION,
    BUFF_PROP_STACK,
    BUFF_PROP_LEVEL,
    BUFF_PROP_TIMETYPE,
    BUFF_PROP_INTERVAL,
    BUFF_PROP_DURATION,
    BUFF_PROP_TIMEFACTOR,
    BUFF_PROP_ATTR,
    BUFF_PROP_SCRIPT,
    BUFF_PROP_OFFLINESAVE,
    BUFF_PROP_DIEDELETE,

    BUFF_PROP_TYPE_MAX,
};

inline bool GetBuffProp(uint16_t nBuffID, uint16_t nPropType)
{
    auto pConfig = sBuffConfig.Get(nBuffID);
    if (!pConfig) return false;

    if (nPropType <= BUFF_PROP_TYPE_MIN || nPropType >= BUFF_PROP_TYPE_MAX) return false;

    LUA_SAFE_BEGIN();

    switch (nPropType) {

        SETCASE(BUFF_PROP_ID, Id);
        SETCASE(BUFF_PROP_NAME, Name);
        SETCASE(BUFF_PROP_KEYNAME, KeyName);

        SETCASE(BUFF_PROP_ICON, Icon);
        SETCASE(BUFF_PROP_SHOWICON, ShowIcon);
        SETCASE(BUFF_PROP_INDEX, Index);
        SETCASE(BUFF_PROP_MAGICID, MagicID);
        SETCASE(BUFF_PROP_DESC, Desc);
        SETCASE(BUFF_PROP_TYPE, Type);
        SETCASE(BUFF_PROP_GROUPID, GroupId);
        SETCASE(BUFF_PROP_GROUPRELATION, GroupRelation);
        SETCASE(BUFF_PROP_STACK, Stack);
        SETCASE(BUFF_PROP_LEVEL, Level);
        SETCASE(BUFF_PROP_TIMETYPE, TimeType);
        SETCASE(BUFF_PROP_INTERVAL, Interval);
        SETCASE(BUFF_PROP_DURATION, Duration);
        SETCASE(BUFF_PROP_TIMEFACTOR, TimeFactor);
        SETCASE_MAP_VECTOR(BUFF_PROP_ATTR, Attr);
        SETCASE(BUFF_PROP_SCRIPT, Script);
        SETCASE(BUFF_PROP_OFFLINESAVE, OfflineSave);
        SETCASE(BUFF_PROP_DIEDELETE, DieDelete);
    }

    LUA_SAFE_END(false);

    return true;
}
