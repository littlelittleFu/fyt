#pragma once

#include "role_table.hpp"

enum eRolePropType {
    ROLE_PROP_TYPE_MIN = 0,

    ROLE_PROP_LEVEL,         /// ��ǰ�ȼ�
    ROLE_PROP_JOB,           /// ְҵ
    ROLE_PROP_UPGRADEEXP,    /// ��������
    ROLE_PROP_HP,            /// ��������
    ROLE_PROP_MP,            /// ����ħ��
    ROLE_PROP_WEIGHT,        /// ���ñ�������
    ROLE_PROP_EQUIPWEIGHT,   /// ����װ������
    ROLE_PROP_BRAWN,         /// ��������
    ROLE_PROP_MAXPHYDEF,     /// �����������
    ROLE_PROP_MINPHYDEF,     /// �����������
    ROLE_PROP_MAXMAGDEF,     /// ����ħ������
    ROLE_PROP_MINMAGDEF,     /// ����ħ������
    ROLE_PROP_MAXPHYATK,     /// ���ù���������
    ROLE_PROP_MINPHYATK,     /// ���ù���������
    ROLE_PROP_MAXMAGATK,     /// ����ħ������
    ROLE_PROP_MINMAGATK,     /// ����ħ������
    ROLE_PROP_MAXTAOATK,     /// ���õ�������
    ROLE_PROP_MINTAOATK,     /// ���õ�������
    ROLE_PROP_HIT,           /// ����׼ȷ�����У�
    ROLE_PROP_MISS,          /// �������ݣ����ܣ�
    ROLE_PROP_MAGMISS,       /// �������ݣ����ܣ�
    ROLE_PROP_LC,            /// ��������/����
    ROLE_PROP_BURST,         /// ���ñ�����
    ROLE_PROP_INTERVAL,      /// �ظ����
    ROLE_PROP_MOVESPEED,     /// �ƶ��ٶ�
    ROLE_PROP_ATTACKSPEED,   /// ��ͨ�����ٶ�
    ROLE_PROP_CASTINGSPEED,   /// ʩ���ٶ�
    ROLE_PROP_HPREC,            /// �����ظ�ֵ
    ROLE_PROP_MPREC,            /// ħ���ظ�ֵ
    ROLE_PROP_POISONREC,     /// �ж��ָ�
    ROLE_PROP_PALSYREC,      /// ��Իָ�
    ROLE_PROP_MAXLEVEL,         /// ְҵ���ȼ�
    ROLE_PROP_SPECIALATTR,      /// ��������

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