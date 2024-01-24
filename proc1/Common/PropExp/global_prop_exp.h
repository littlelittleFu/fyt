#pragma once

#include "global.hpp"

enum eGlobalPropType {
    GLOBAL_PROP_TYPE_MIN = 0,

    GLOBAL_PROP_SCENE_ITEM_SURVIVAL_TIME,           /// 场景物品的生存时间
    GLOBAL_PROP_SCENE_ITEM_DEAD_TIME,               /// 场景物品的死亡时间
    GLOBAL_PROP_TEAM_BENEFIT_RANGE,                 /// 怪物死亡同一队加经验、任务范围
    GLOBAL_PROP_REMOTE_OPEN_WAREHOUSE,
    GLOBAL_PROP_TOP_LIST_FLASH_TIME,                /// 排行榜刷新时间
    GLOBAL_PROP_JOIN_GUILD_LEVEL,                   /// 创建、加入行会等级

    GLOBAL_PROP_RECOVERY_PROPERTY_TIME,             /// 恢复属性间隔时间
    GLOBAL_PROP_CORPSE_TIME,                        /// 怪物死亡消失时间
    GLOBAL_PROP_TRADE_DELEGATE_TIME,                /// 交易行委托时间(小时)
    GLOBAL_PROP_DROP_IS_RANDOM,                     /// 怪物掉落物品顺序随机打乱
    GLOBAL_PROP_ROLE_BASE_DROP_RATE,                /// 人物默认的爆率
    GLOBAL_PROP_PRECISION,                          /// 属性比例精度(1:百分比,2:万分比)
    GLOBAL_PROP_SYNCDATA_INTERVAL_TIME,             /// 同步数据间隔时间   
    GLOBAL_PROP_COMMON_ATTACK_SKILLID,              /// 普攻ID
    GLOBAL_PROP_SKILL_PRIORITY,                     /// 技能优先级

    GLOBAL_PROP_TYPE_MAX,
};

inline bool GetGlobalProp(uint16_t nPropType)
{
    const auto *pConfig = sGlobalConfig.GetData();
    if (!pConfig) return false;

    if (nPropType <= GLOBAL_PROP_TYPE_MIN || nPropType >= GLOBAL_PROP_TYPE_MAX) return false;

    LUA_SAFE_BEGIN();

    switch (nPropType) {

        SETCASE(GLOBAL_PROP_SCENE_ITEM_SURVIVAL_TIME, SceneItemSurvivalTime);
        SETCASE(GLOBAL_PROP_SCENE_ITEM_DEAD_TIME, SceneItemDeadTime);
        SETCASE(GLOBAL_PROP_TEAM_BENEFIT_RANGE, TeamBenefitRange);
        SETCASE(GLOBAL_PROP_REMOTE_OPEN_WAREHOUSE, RemoteOpenWarehouse);
        SETCASE(GLOBAL_PROP_TOP_LIST_FLASH_TIME, TopListFlashTime);
        SETCASE(GLOBAL_PROP_JOIN_GUILD_LEVEL, JoinGuildLevel);
        SETCASE(GLOBAL_PROP_RECOVERY_PROPERTY_TIME, RecoveryPropertyTime);
        SETCASE(GLOBAL_PROP_CORPSE_TIME, CorpseTime);
        SETCASE(GLOBAL_PROP_TRADE_DELEGATE_TIME, TradeDelegateTime);
        SETCASE(GLOBAL_PROP_DROP_IS_RANDOM, DropIsRandom);
        SETCASE(GLOBAL_PROP_ROLE_BASE_DROP_RATE, RoleBaseDropRate);
        SETCASE(GLOBAL_PROP_PRECISION, Precision);
        SETCASE(GLOBAL_PROP_SYNCDATA_INTERVAL_TIME, SyncDataIntervalTime);
        SETCASE(GLOBAL_PROP_COMMON_ATTACK_SKILLID, CommonAttackSkillID);
        SETCASE_VECTOR(GLOBAL_PROP_SKILL_PRIORITY, SkillPriority);
    }

    LUA_SAFE_END(false);

    return true;
}
