#pragma once
#include "title_table.hpp"

enum eTitlePropType {
	TITLE_PROP_TYPE_MIN = 0,

    TITLE_PROP_ID,
    TITLE_PROP_NAME,
    TITLE_PROP_KEYNAME,
    TITLE_PROP_TYPE,

    TITLE_PROP_ICON,
    TITLE_PROP_BIGICONEFFECT,
    TITLE_PROP_EFFECT,
    TITLE_PROP_SIZE,
    TITLE_PROP_PRIORITY,
    TITLE_PROP_UNIQUE,
    TITLE_PROP_BUFFID,
    TITLE_PROP_MERGEDEL,
    TITLE_PROP_TIPS,
    TITLE_PROP_TIPSSHOURCE,
    TITLE_PROP_TETLESHOW,
    TITLE_PROP_COLOR,
    TITLE_PROP_HASSHOWNAME,
    TITLE_PROP_TIMELIMIT,
    TITLE_PROP_USEABSTIME,
    TITLE_PROP_COLORSTRING,
    TITLE_PROP_HP,
    TITLE_PROP_MP,
    TITLE_PROP_MINPHYDEF,
    TITLE_PROP_MAXPHYDEF,
    TITLE_PROP_MINMAGDEF,
    TITLE_PROP_MAXMAGDEF,
    TITLE_PROP_MINPHYATK,
    TITLE_PROP_MAXPHYATK,
    TITLE_PROP_MINMAGATK,
    TITLE_PROP_MAXMAGATK,
    TITLE_PROP_MINTAOATK,
    TITLE_PROP_MAXTAOATK,
    TITLE_PROP_HIT,
    TITLE_PROP_MISS,
    TITLE_PROP_SPECIALATTR,
    TITLE_PROP_SKILLID,

    TIILE_PROP_TYPE_MAX,
};

inline bool GetTitleProp(DATA::Title* pConfig, uint16_t nPropType)
{
    if (nPropType <= TITLE_PROP_TYPE_MIN || nPropType >= TIILE_PROP_TYPE_MAX) return false;

    LUA_SAFE_BEGIN();

    switch (nPropType) {

        SETCASE(TITLE_PROP_ID, Id);
        SETCASE(TITLE_PROP_NAME, Name);
        SETCASE(TITLE_PROP_KEYNAME, KeyName);
        SETCASE(TITLE_PROP_TYPE, type);
        SETCASE(TITLE_PROP_ICON, Icon);
        SETCASE(TITLE_PROP_BIGICONEFFECT, BigIconEffect);
        SETCASE(TITLE_PROP_EFFECT, Effect);
        SETCASE(TITLE_PROP_SIZE, Size);
        SETCASE(TITLE_PROP_PRIORITY, Priority);
        SETCASE(TITLE_PROP_UNIQUE, Unique);
        SETCASE(TITLE_PROP_BUFFID, BuffID);
        SETCASE(TITLE_PROP_MERGEDEL, MergeDel);
        SETCASE(TITLE_PROP_TIPS, Tips);
        SETCASE(TITLE_PROP_TIPSSHOURCE, TipsSource);
        SETCASE(TITLE_PROP_TETLESHOW, TetelShow);
        SETCASE(TITLE_PROP_COLOR, Color);
        SETCASE(TITLE_PROP_HASSHOWNAME, HasShowName);
        SETCASE(TITLE_PROP_TIMELIMIT, TimeLimit);
        SETCASE(TITLE_PROP_USEABSTIME, UseAbsTime);
        SETCASE(TITLE_PROP_COLORSTRING, ColorString);
        SETCASE(TITLE_PROP_HP, HP);
        SETCASE(TITLE_PROP_MP, MP);
        SETCASE(TITLE_PROP_MINPHYDEF, MinPhyDef);
        SETCASE(TITLE_PROP_MAXPHYDEF, MaxPhyDef);
        SETCASE(TITLE_PROP_MINMAGDEF, MinMagDef);
        SETCASE(TITLE_PROP_MAXMAGDEF, MaxMagDef);
        SETCASE(TITLE_PROP_MINPHYATK, MinPhyAtk);
        SETCASE(TITLE_PROP_MAXPHYATK, MaxPhyAtk);
        SETCASE(TITLE_PROP_MINMAGATK, MinMagAtk);
        SETCASE(TITLE_PROP_MAXMAGATK, MaxMagAtk);
        SETCASE(TITLE_PROP_MINTAOATK, MinTaoAtk);
        SETCASE(TITLE_PROP_MAXTAOATK, MaxTaoAtk);
        SETCASE(TITLE_PROP_HIT, Hit);
        SETCASE(TITLE_PROP_MISS, Miss);
        SETCASE_MAP(TITLE_PROP_SPECIALATTR, SpecialAttr);
        SETCASE(TITLE_PROP_SKILLID, SkillId);
    }

    LUA_SAFE_END(false);

    return true;
}

inline bool GetTitleProp(uint16_t titleID, uint16_t nPropType)
{
    auto pConfig = sTitleConfig.Get(titleID);
    if (!pConfig) return false;

    return GetTitleProp(pConfig, nPropType);
}

inline bool GetTitleProp(const std::string& keyName, uint16_t nPropType)
{
    auto pConfig = sTitleConfig.Get(keyName);
    if (!pConfig) return false;

    return GetTitleProp(pConfig, nPropType);
}