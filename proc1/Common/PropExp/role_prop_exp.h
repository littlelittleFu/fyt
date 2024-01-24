#pragma once

#include "role_table.hpp"

enum eRolePropType {
    ROLE_PROP_TYPE_MIN = 0,

    ROLE_PROP_LEVEL,         /// 当前等级
    ROLE_PROP_JOB,           /// 职业
    ROLE_PROP_UPGRADEEXP,    /// 升级经验
    ROLE_PROP_HP,            /// 配置生命
    ROLE_PROP_MP,            /// 配置魔法
    ROLE_PROP_WEIGHT,        /// 配置背包负重
    ROLE_PROP_EQUIPWEIGHT,   /// 配置装备负重
    ROLE_PROP_BRAWN,         /// 腕力重量
    ROLE_PROP_MAXPHYDEF,     /// 配置物防上限
    ROLE_PROP_MINPHYDEF,     /// 配置物防下限
    ROLE_PROP_MAXMAGDEF,     /// 配置魔防上限
    ROLE_PROP_MINMAGDEF,     /// 配置魔防下限
    ROLE_PROP_MAXPHYATK,     /// 配置攻击力上限
    ROLE_PROP_MINPHYATK,     /// 配置攻击力下限
    ROLE_PROP_MAXMAGATK,     /// 配置魔攻上限
    ROLE_PROP_MINMAGATK,     /// 配置魔攻下限
    ROLE_PROP_MAXTAOATK,     /// 配置道术上限
    ROLE_PROP_MINTAOATK,     /// 配置道术下限
    ROLE_PROP_HIT,           /// 配置准确（命中）
    ROLE_PROP_MISS,          /// 配置敏捷（闪避）
    ROLE_PROP_MAGMISS,       /// 配置敏捷（闪避）
    ROLE_PROP_LC,            /// 配置幸运/诅咒
    ROLE_PROP_BURST,         /// 配置暴击率
    ROLE_PROP_INTERVAL,      /// 回复间隔
    ROLE_PROP_MOVESPEED,     /// 移动速度
    ROLE_PROP_ATTACKSPEED,   /// 普通攻击速度
    ROLE_PROP_CASTINGSPEED,   /// 施法速度
    ROLE_PROP_HPREC,            /// 生命回复值
    ROLE_PROP_MPREC,            /// 魔法回复值
    ROLE_PROP_POISONREC,     /// 中毒恢复
    ROLE_PROP_PALSYREC,      /// 麻痹恢复
    ROLE_PROP_MAXLEVEL,         /// 职业最大等级
    ROLE_PROP_SPECIALATTR,      /// 特殊属性

    ROLE_PROP_TYPE_MAX,
};

inline bool GetRoleProp(uint32_t nLevel, uint8_t njob, uint16_t nPropType)
{
    if (ROLE_PROP_MAXLEVEL == nPropType)
    {
        LuaRet = sRoleConfig.GetMaxLevel(njob);
        return true;
    }

    auto pConfig = sRoleConfig.Get(nLevel, njob);
    if (!pConfig) return false;

    if (nPropType <= ROLE_PROP_TYPE_MIN || nPropType >= ROLE_PROP_TYPE_MAX) return false;

    LUA_SAFE_BEGIN();

    switch (nPropType) {

        SETCASE(ROLE_PROP_LEVEL, Level);
        SETCASE(ROLE_PROP_JOB, Job);
        SETCASE(ROLE_PROP_UPGRADEEXP, UpgradeExp);
        SETCASE(ROLE_PROP_HP, HP);
        SETCASE(ROLE_PROP_MP, MP);
        SETCASE(ROLE_PROP_WEIGHT, Weight);
        SETCASE(ROLE_PROP_EQUIPWEIGHT, EquipWeight);
        SETCASE(ROLE_PROP_BRAWN, Brawn);
        SETCASE(ROLE_PROP_MAXPHYDEF, MaxPhyDef);
        SETCASE(ROLE_PROP_MINPHYDEF, MinPhyDef);
        SETCASE(ROLE_PROP_MAXMAGDEF, MaxMagDef);
        SETCASE(ROLE_PROP_MINMAGDEF, MinMagDef);
        SETCASE(ROLE_PROP_MAXPHYATK, MaxPhyAtk);
        SETCASE(ROLE_PROP_MINPHYATK, MinPhyAtk);
        SETCASE(ROLE_PROP_MAXMAGATK, MaxMagAtk);
        SETCASE(ROLE_PROP_MINMAGATK, MinMagAtk);
        SETCASE(ROLE_PROP_MAXTAOATK, MaxTaoAtk);
        SETCASE(ROLE_PROP_MINTAOATK, MinTaoAtk);
        SETCASE(ROLE_PROP_HIT, Hit);
        SETCASE(ROLE_PROP_MISS, Miss);
        SETCASE(ROLE_PROP_MAGMISS, MagMiss);
        SETCASE(ROLE_PROP_LC, LC);
        SETCASE(ROLE_PROP_BURST, Burst);
        SETCASE(ROLE_PROP_INTERVAL, Interval);
        SETCASE(ROLE_PROP_MOVESPEED, MoveSpeed);
        SETCASE(ROLE_PROP_ATTACKSPEED, AttackSpeed);
        SETCASE(ROLE_PROP_CASTINGSPEED, CastingSpeed);
        SETCASE(ROLE_PROP_HPREC, HPRec);
        SETCASE(ROLE_PROP_MPREC, MPRec);
        SETCASE(ROLE_PROP_POISONREC, PoisonRec);
        SETCASE(ROLE_PROP_PALSYREC, PalsyRec);
        SETCASE_MAP(ROLE_PROP_SPECIALATTR, SpecialAttr);
    }

    LUA_SAFE_END(false);

    return true;
}