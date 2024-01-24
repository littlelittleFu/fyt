#pragma once

#include "quest_template_parser.hpp"

enum eQuestPropType {
    QUEST_PROP_TYPE_MIN = 0,

    QUEST_PROP_ID,
    QUEST_PROP_TYPE,
    QUEST_PROP_NAME,
    QUEST_PROP_ABORT,
    QUEST_PROP_PREVID,
    QUEST_PROP_NEXTID,
    QUEST_PROP_MIN_LEVEL,
    QUEST_PROP_MAX_LEVEL,
    QUEST_PROP_ACCEPT_TYPE,
    QUEST_PROP_ACCEPT_FROM,
    QUEST_PROP_DELIVER_TYPE,
    QUEST_PROP_DELIVER_TO,
    QUEST_PROP_ACHIEVE_TYPE,
    QUEST_PROP_TIME_LIMIT_TYPE,
    QUEST_PROP_FIXED_TIME,
    QUEST_PROP_START_TIME,
    QUEST_PROP_END_TIME,

    QUEST_PROP_TYPE_MAX,
};

inline bool GetQuestProp(uint16_t nQuestID, uint16_t nPropType)
{
    const auto *pConfig = sQuestTemplate.get_config(nQuestID);
    if (!pConfig) return false;

    if (nPropType <= QUEST_PROP_TYPE_MIN || nPropType >= QUEST_PROP_TYPE_MAX) return false;

    LUA_SAFE_BEGIN();

    switch (nPropType) {

        SETCASE(QUEST_PROP_ID, id);
        SETCASE(QUEST_PROP_TYPE, type);
        SETCASE(QUEST_PROP_NAME, name);
        SETCASE(QUEST_PROP_ABORT, abort);
        SETCASE(QUEST_PROP_PREVID, previd);
        SETCASE(QUEST_PROP_NEXTID, nextid);
        SETCASE(QUEST_PROP_MIN_LEVEL, min_level);
        SETCASE(QUEST_PROP_MAX_LEVEL, max_level);
        SETCASE(QUEST_PROP_ACCEPT_TYPE, accept_type);
        SETCASE(QUEST_PROP_ACCEPT_FROM, accept_from);
        SETCASE(QUEST_PROP_DELIVER_TYPE, deliver_type);
        SETCASE(QUEST_PROP_DELIVER_TO, deliver_to);
        SETCASE(QUEST_PROP_ACHIEVE_TYPE, achieve_type);
        SETCASE(QUEST_PROP_TIME_LIMIT_TYPE, time_limit_type);
        SETCASE(QUEST_PROP_FIXED_TIME, fixed_time);
        SETCASE(QUEST_PROP_START_TIME, start_time);
        SETCASE(QUEST_PROP_END_TIME, end_time);
    }

    LUA_SAFE_END(false);

    return true;
}
