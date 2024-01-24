#pragma once

#include "skill_table.hpp"

enum eSkillPropType {
    SKILL_PROP_TYPE_MIN = 0,

    SKILL_PROP_ID,
    SKILL_PROP_NAME,
    SKILL_PROP_HURTTYPE,
    SKILL_PROP_SKILLTYPE,
    SKILL_PROP_SKILLTYPEPARAM,
    SKILL_PROP_SCRIPT,
    SKILL_PROP_CD,
    SKILL_PROP_ICON,
    SKILL_PROP_UIORDER,
    SKILL_PROP_MAGICID,
    SKILL_PROP_CASTWAY,
    SKILL_PROP_RANGETYPE,
    SKILL_PROP_RANGEPARAM,
    SKILL_PROP_CUSTOMSHAPE,
    SKILL_PROP_TARGETTYPE,
    SKILL_PROP_CASTDISTANCE,
    SKILL_PROP_SPECIALEFFECTTYPE,
    SKILL_PROP_SPECIALEFFECTPARAM,
    SKILL_PROP_LEVELCOMPARE,
    SKILL_PROP_ATTACHEDBUFF,
    SKILL_PROP_FIXEDDELAY,
    SKILL_PROP_CONSUMEHP,
    SKILL_PROP_CONSUMEMP,
    SKILL_PROP_ATTACKRATIO,
    SKILL_PROP_DEFEFFECTRATIO,
    SKILL_PROP_BASERANDVALMIN,
    SKILL_PROP_BASERANDVALMAX,
    SKILL_PROP_HATRED,
    SKILL_PROP_NEEDROLELEVEL,
    SKILL_PROP_NEEDPROFICIENCY,
    SKILL_PROP_NEXTLEVELID,
    SKILL_PROP_SKILLCHAINID,
    SKILL_PROP_SUMMONPARAMS,
    SKILL_PROP_SAFERANGEEFFECT,

    SKILL_PROP_TYPE_MAX,
};

inline bool GetSkillProp(DATA::Skill* pConfig, uint16_t nPropType)
{
    if (!pConfig) return false;

    if (nPropType <= SKILL_PROP_TYPE_MIN || nPropType >= SKILL_PROP_TYPE_MAX) return false;

    LUA_SAFE_BEGIN();

    switch (nPropType) {

        SETCASE(SKILL_PROP_ID, Id);
        SETCASE(SKILL_PROP_NAME, Name);
        SETCASE(SKILL_PROP_HURTTYPE, HurtType);
        SETCASE(SKILL_PROP_SKILLTYPE, SkillType);
        SETCASE(SKILL_PROP_SKILLTYPEPARAM, SkillTypeParam);
        SETCASE(SKILL_PROP_SCRIPT, Script);
        SETCASE(SKILL_PROP_CD, CD);
        SETCASE(SKILL_PROP_ICON, Icon);
        SETCASE(SKILL_PROP_UIORDER, UIOrder);
        SETCASE(SKILL_PROP_MAGICID, MagicID);
        SETCASE(SKILL_PROP_CASTWAY, CastWay);
        SETCASE(SKILL_PROP_RANGETYPE, RangeType);
        SETCASE(SKILL_PROP_RANGEPARAM, RangeParam);
        SETCASE_VECTOR(SKILL_PROP_CUSTOMSHAPE, CustomShape);
        SETCASE(SKILL_PROP_TARGETTYPE, TargetType);
        SETCASE(SKILL_PROP_CASTDISTANCE, CastDistance);
        SETCASE(SKILL_PROP_SPECIALEFFECTTYPE, SpecialEffectType);
        SETCASE_VECTOR(SKILL_PROP_SPECIALEFFECTPARAM, SpecialEffectParam);
        SETCASE(SKILL_PROP_LEVELCOMPARE, LevelCompare);

    case SKILL_PROP_ATTACHEDBUFF:
    {
        CLuaObject luaRet = NewLuaObj();
        int i = 0;

        for (auto &s : pConfig->AttachedBuff) {
            CLuaObject obj = NewLuaObj();
            obj["BuffID"] = s.BuffID;
            obj["Target"] = s.Target;
            obj["Duration"] = s.Duration;
            luaRet[++i] = obj;
        }

        LuaRet = luaRet;
        break;
    }

        SETCASE(SKILL_PROP_FIXEDDELAY, FixedDelay);
        SETCASE(SKILL_PROP_CONSUMEHP, ConsumeHP);
        SETCASE(SKILL_PROP_CONSUMEMP, ConsumeMP);
        SETCASE(SKILL_PROP_ATTACKRATIO, AttackRatio);
        SETCASE(SKILL_PROP_DEFEFFECTRATIO, DefEffectRatio);
        SETCASE(SKILL_PROP_BASERANDVALMIN, BaseRandValMin);
        SETCASE(SKILL_PROP_BASERANDVALMAX, BaseRandValMax);
        SETCASE(SKILL_PROP_HATRED, Hatred);
        SETCASE(SKILL_PROP_NEEDROLELEVEL, NeedRoleLevel);
        SETCASE(SKILL_PROP_NEEDPROFICIENCY, NeedProficiency);
        SETCASE(SKILL_PROP_NEXTLEVELID, NextLevelID);
        SETCASE(SKILL_PROP_SKILLCHAINID, SkillChainID);

        SETCASE(SKILL_PROP_SAFERANGEEFFECT, SafeRangeEffect);
    case SKILL_PROP_SUMMONPARAMS:
    {
        CLuaObject luaRet = NewLuaObj();
        int i = 0;

        for (auto &s : pConfig->SummonParams) {
            CLuaObject obj = NewLuaObj();
            obj["RoleLevel"] = s.RoleLevel;
            obj["MonsterName"] = s.MonsterName;
            obj["MaxNum"] = s.MaxNum;
            obj["MonsterLevel"] = s.MonsterLevel;
            luaRet[++i] = obj;
        }

        LuaRet = luaRet;
        break;
    }
    }

    LUA_SAFE_END(false);

    return true;
}

inline bool GetSkillProp(uint16_t nSkillID, uint16_t nPropType)
{
    return GetSkillProp(sSkillConfig.Get(nSkillID), nPropType);
}

inline bool CanModifySkillProp(uint16_t nPropType)
{
    if (nPropType <= SKILL_PROP_TYPE_MIN || nPropType >= SKILL_PROP_TYPE_MAX) return false;

    switch (nPropType) 
    {
        case SKILL_PROP_CD:
        case SKILL_PROP_MAGICID:
        case SKILL_PROP_RANGETYPE:
        case SKILL_PROP_RANGEPARAM:
        case SKILL_PROP_CUSTOMSHAPE:
        case SKILL_PROP_CASTDISTANCE:
        case SKILL_PROP_LEVELCOMPARE:
        case SKILL_PROP_ATTACHEDBUFF:
        case SKILL_PROP_SUMMONPARAMS:
        return true;
    }

    return false;
}
