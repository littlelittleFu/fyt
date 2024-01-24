#pragma once

#include "item_table.hpp"

enum eItemPropType {
    ITEM_PROP_TYPE_MIN = 0,

    ITEM_PROP_ID,
    ITEM_PROP_NAME,
    ITEM_PROP_KEYNAME,
    ITEM_PROP_DESC,
    ITEM_PROP_TYPE,
    ITEM_PROP_SUBTYPE,
    ITEM_PROP_WEAPONTYPE,
    ITEM_PROP_COLOR,
    ITEM_PROP_ICON,
    ITEM_PROP_BIGICON,
    ITEM_PROP_BIGICONEFFECT,
    ITEM_PROP_AVATARMAN,
    ITEM_PROP_AVATARWOMEN,
    ITEM_PROP_AVATAREFFECT,
    ITEM_PROP_DROPEFFECT,
    ITEM_PROP_QUALITY,
    ITEM_PROP_LEVEL,
    ITEM_PROP_GENDER,
    ITEM_PROP_JOB,
    ITEM_PROP_PHYLIMIT,
    ITEM_PROP_MAGLIMIT,
    ITEM_PROP_TAOLIMIT,
    ITEM_PROP_STACK,
    ITEM_PROP_SCRIPT,
    ITEM_PROP_DROPTYPE,
    ITEM_PROP_HP,
    ITEM_PROP_MP,
    ITEM_PROP_MAXPHYDEF,
    ITEM_PROP_MINPHYDEF,
    ITEM_PROP_MAXMAGDEF,
    ITEM_PROP_MINMAGDEF,
    ITEM_PROP_MAXPHYATK,
    ITEM_PROP_MINPHYATK,
    ITEM_PROP_MAXMAGATK,
    ITEM_PROP_MINMAGATK,
    ITEM_PROP_MAXTAOATK,
    ITEM_PROP_MINTAOATK,
    ITEM_PROP_HIT,
    ITEM_PROP_MISS,
    ITEM_PROP_SPECIALATTR,
    ITEM_PROP_SKILLID,
    ITEM_PROP_BUFFID,
    ITEM_PROP_LS2,
    ITEM_PROP_BINDTYPE,
    ITEM_PROP_ENABLE,
    ITEM_PROP_USECOUNT,
    ITEM_PROP_JUJUTYPE,
    ITEM_PROP_TIMELIMIT,
    ITEM_PROP_TIMETYPE,
    ITEM_PROP_SUIT,
    ITEM_PROP_BAGSIZE,
    ITEM_PROP_WAREHOUSESIZE,
    ITEM_PROP_BURST,
    ITEM_PROP_ATTACKSPEED,
    ITEM_PROP_USER,
    ITEM_PROP_FASHIONID,
    ITEM_PROP_DURABILITY,
    ITEM_PROP_TRACK,

    ITEM_PROP_TYPE_MAX,
};

inline bool GetItemProp(DATA::Item* pConfig, uint16_t nPropType)
{
    if (nPropType <= ITEM_PROP_TYPE_MIN || nPropType >= ITEM_PROP_TYPE_MAX) return false;

    LUA_SAFE_BEGIN();

    switch (nPropType) {

        SETCASE(ITEM_PROP_ID, Id);
        SETCASE(ITEM_PROP_NAME, Name);
        SETCASE(ITEM_PROP_KEYNAME, KeyName);
        SETCASE(ITEM_PROP_DESC, Desc);
        SETCASE(ITEM_PROP_TYPE, Type);
        SETCASE(ITEM_PROP_SUBTYPE, SubType);
        SETCASE(ITEM_PROP_WEAPONTYPE, WeaponType);
        SETCASE(ITEM_PROP_COLOR, Color);
        SETCASE(ITEM_PROP_ICON, Icon);
        SETCASE(ITEM_PROP_BIGICON, BigIcon);
        SETCASE(ITEM_PROP_BIGICONEFFECT, BigIconEffect);
        SETCASE(ITEM_PROP_AVATARMAN, AvatarMan);
        SETCASE(ITEM_PROP_AVATARWOMEN, AvatarWomen);
        SETCASE(ITEM_PROP_AVATAREFFECT, AvatarEffect);
        SETCASE(ITEM_PROP_DROPEFFECT, DropEffect);
        SETCASE(ITEM_PROP_QUALITY, Quality);
        SETCASE(ITEM_PROP_LEVEL, Level);
        SETCASE(ITEM_PROP_GENDER, Gender);
        SETCASE(ITEM_PROP_JOB, Job);
        SETCASE(ITEM_PROP_PHYLIMIT, PhyLimit);
        SETCASE(ITEM_PROP_MAGLIMIT, MagLimit);
        SETCASE(ITEM_PROP_TAOLIMIT, TaoLimit);
        SETCASE(ITEM_PROP_STACK, Stack);
        SETCASE(ITEM_PROP_SCRIPT, Script);
        SETCASE_SET(ITEM_PROP_DROPTYPE, DropType);
        SETCASE(ITEM_PROP_HP, HP);
        SETCASE(ITEM_PROP_MP, MP);
        SETCASE(ITEM_PROP_MAXPHYDEF, MaxPhyDef);
        SETCASE(ITEM_PROP_MINPHYDEF, MinPhyDef);
        SETCASE(ITEM_PROP_MAXMAGDEF, MaxMagDef);
        SETCASE(ITEM_PROP_MINMAGDEF, MinMagDef);
        SETCASE(ITEM_PROP_MAXPHYATK, MaxPhyAtk);
        SETCASE(ITEM_PROP_MINPHYATK, MinPhyAtk);
        SETCASE(ITEM_PROP_MAXMAGATK, MaxMagAtk);
        SETCASE(ITEM_PROP_MINMAGATK, MinMagAtk);
        SETCASE(ITEM_PROP_MAXTAOATK, MaxTaoAtk);
        SETCASE(ITEM_PROP_MINTAOATK, MinTaoAtk);
        SETCASE(ITEM_PROP_HIT, Hit);
        SETCASE(ITEM_PROP_MISS, Miss);
        SETCASE_MAP(ITEM_PROP_SPECIALATTR, SpecialAttr);
        SETCASE(ITEM_PROP_SKILLID, SkillId);
        SETCASE_SET(ITEM_PROP_BUFFID, BuffId);
        SETCASE(ITEM_PROP_LS2, LS2);
        SETCASE(ITEM_PROP_BINDTYPE, BindType);
        SETCASE_SET(ITEM_PROP_ENABLE, Enable);
        SETCASE(ITEM_PROP_USECOUNT, UseCount);
        SETCASE(ITEM_PROP_JUJUTYPE, JuJuType);
        SETCASE(ITEM_PROP_TIMELIMIT, TimeLimit);
        SETCASE(ITEM_PROP_TIMETYPE, TimeType);
        SETCASE(ITEM_PROP_SUIT, Suit);
        SETCASE(ITEM_PROP_BAGSIZE, BagSize);
        SETCASE(ITEM_PROP_WAREHOUSESIZE, WarehouseSize);
        SETCASE(ITEM_PROP_BURST, Burst);
        SETCASE(ITEM_PROP_ATTACKSPEED, AttackSpeed);
        SETCASE(ITEM_PROP_USER, User);
        SETCASE(ITEM_PROP_FASHIONID, FashionId);
        SETCASE(ITEM_PROP_DURABILITY, Durability);
        SETCASE(ITEM_PROP_TRACK, Track);
    }

    LUA_SAFE_END(false);

    return true;
}

inline bool GetItemProp(uint16_t nItemID, uint16_t nPropType)
{
    auto pConfig = sItemConfig.Get(nItemID);
    if (!pConfig) return false;

    return GetItemProp(pConfig, nPropType);
}

inline bool GetItemProp(const std::string& keyName, uint16_t nPropType)
{
    auto pConfig = sItemConfig.Get(keyName);
    if (!pConfig) return false;

    return GetItemProp(pConfig, nPropType);
}
