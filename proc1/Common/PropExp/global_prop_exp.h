#pragma once

#include "global.hpp"

enum eGlobalPropType {
    GLOBAL_PROP_TYPE_MIN = 0,

    GLOBAL_PROP_SCENE_ITEM_SURVIVAL_TIME,           /// ������Ʒ������ʱ��
    GLOBAL_PROP_SCENE_ITEM_DEAD_TIME,               /// ������Ʒ������ʱ��
    GLOBAL_PROP_TEAM_BENEFIT_RANGE,                 /// ��������ͬһ�ӼӾ��顢����Χ
    GLOBAL_PROP_REMOTE_OPEN_WAREHOUSE,
    GLOBAL_PROP_TOP_LIST_FLASH_TIME,                /// ���а�ˢ��ʱ��
    GLOBAL_PROP_JOIN_GUILD_LEVEL,                   /// �����������л�ȼ�

    GLOBAL_PROP_RECOVERY_PROPERTY_TIME,             /// �ָ����Լ��ʱ��
    GLOBAL_PROP_CORPSE_TIME,                        /// ����������ʧʱ��
    GLOBAL_PROP_TRADE_DELEGATE_TIME,                /// ������ί��ʱ��(Сʱ)
    GLOBAL_PROP_DROP_IS_RANDOM,                     /// ���������Ʒ˳���������
    GLOBAL_PROP_ROLE_BASE_DROP_RATE,                /// ����Ĭ�ϵı���
    GLOBAL_PROP_PRECISION,                          /// ���Ա�������(1:�ٷֱ�,2:��ֱ�)
    GLOBAL_PROP_SYNCDATA_INTERVAL_TIME,             /// ͬ�����ݼ��ʱ��   
    GLOBAL_PROP_COMMON_ATTACK_SKILLID,              /// �չ�ID
    GLOBAL_PROP_SKILL_PRIORITY,                     /// �������ȼ�

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
