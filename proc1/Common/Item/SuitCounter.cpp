#include "stdafx.h"
#include "SuitCounter.h"

#define FOR_ALL_SUIT_ATTR(F) F(1) F(2) F(3) F(4) F(5) F(6) F(7) F(8) F(9) F(10) F(11) \
    F(12) F(13) F(14) F(15) F(16) F(17) F(18) F(19) F(20) F(21) F(22) F(23) F(24) F(25)

#define CHECK_THEN_ADD_PROP(N) if (suitCfg->AttSize##N == suitNum) role->AddRoleProp(suitCfg->Att##N, suitCfg->AttValue##N);
#define CHECK_THEN_SUB_PROP(N) if (suitCfg->AttSize##N == suitNum + 1) role->AddRoleProp(suitCfg->Att##N, -suitCfg->AttValue##N);

////////////////////////////////////////////////////////////////////////////////
//
// Suit
//

void Suit::IncSuitNum()
{
    mSuitNum += 1;
    OnIncSuitNum();
}

void Suit::DecSuitNum()
{
    if (mSuitNum == 0) return;
    mSuitNum -= 1;
    OnDecSuitNum();
}

void Suit::OnIncSuitNum()
{
    auto *role = GetRole();
    if (!role) return;

    auto suitID = GetSuitID();
    const auto *suitCfg = sSuitConfig.Get(suitID);
    if (!suitCfg) return;

    auto suitNum = GetSuitNum();
    if (suitNum == 0) return;
    if (suitCfg->SuitBuffID > 0)
    {
        if (suitNum == suitCfg->AttSize0)
        {
            role->AddBuffByRole(suitCfg->SuitBuffID, role, 0);
        }
    }
    else
    {
    	FOR_ALL_SUIT_ATTR(CHECK_THEN_ADD_PROP);
    }
}

void Suit::OnDecSuitNum()
{
    auto *role = GetRole();
    if (!role) return;

    auto suitID = GetSuitID();
    const auto *suitCfg = sSuitConfig.Get(suitID);
    if (!suitCfg) return;

    auto suitNum = GetSuitNum();
    if (suitCfg->SuitBuffID > 0 )
    {
        if ((suitNum + 1) == suitCfg->AttSize0)
        {
            role->RemoveBuff(suitCfg->SuitBuffID);
        }
    }
    else
    {
    	FOR_ALL_SUIT_ATTR(CHECK_THEN_SUB_PROP);
    }
}

////////////////////////////////////////////////////////////////////////////////
//
// SuitBySubType
//

SuitBySubType::SuitBySubType(Role *role, uint16_t suitID) : Suit(role, suitID)
{
    Init();
}

void SuitBySubType::Init()
{
    auto suitID = GetSuitID();
    auto *suitCfg = sSuitConfig.Get(suitID);
    if (!suitCfg || suitCfg->SuitCountType != count_suit_by_sub_type) return;

    const auto &allItemCfg = sItemConfig.GetData();

    mItemNumMap.clear();
    for (const auto &itemCfg : allItemCfg)
        if (itemCfg->Suit == suitID)
            mItemNumMap.emplace(itemCfg->SubType, 0);
}

void SuitBySubType::OnLoadEquip(uint16_t templateID)
{
    const auto *itemCfg = sItemConfig.Get(templateID);
    if (!itemCfg) return;
    auto it = mItemNumMap.find(itemCfg->SubType);
    if (it == mItemNumMap.end()) return;
    auto &itemNum = it->second;
    itemNum += 1;
    CheckSuitNum();
}

void SuitBySubType::OnUnloadEquip(uint16_t templateID)
{
    const auto *itemCfg = sItemConfig.Get(templateID);
    if (!itemCfg) return;
    auto it = mItemNumMap.find(itemCfg->SubType);
    if (it == mItemNumMap.end()) return;
    auto &itemNum = it->second;
    if (itemNum == 0) return;
    itemNum -= 1;
    CheckSuitNum();
}

void SuitBySubType::CheckSuitNum()
{
    uint16_t newSuitNum = 0;

    for (const auto &it : mItemNumMap) {
        const auto &itemNum = it.second;
        if (itemNum) ++newSuitNum;
    }

    auto oldSuitNum = GetSuitNum();

    if (newSuitNum < oldSuitNum)
        DecSuitNum();
    else if (newSuitNum > oldSuitNum)
        IncSuitNum();
}

////////////////////////////////////////////////////////////////////////////////
//
// SuitByTemplateID
//

SuitByTemplateID::SuitByTemplateID(Role *role, uint16_t suitID) : Suit(role, suitID)
{
    Init();
}

void SuitByTemplateID::Init()
{
    auto suitID = GetSuitID();
    auto *suitCfg = sSuitConfig.Get(suitID);
    if (!suitCfg || suitCfg->SuitCountType != count_suit_by_template_id) return;

    const auto &allItemCfg = sItemConfig.GetData();

    mItemNumMap.clear();
    for (const auto &itemCfg : allItemCfg)
        if (itemCfg->Suit == suitID)
            mItemNumMap.emplace(itemCfg->Id, 0);
}

void SuitByTemplateID::OnLoadEquip(uint16_t templateID)
{
    auto it = mItemNumMap.find(templateID);
    if (it == mItemNumMap.end()) return;
    auto &itemNum = it->second;
    itemNum += 1;
    CheckSuitNum();
}

void SuitByTemplateID::OnUnloadEquip(uint16_t templateID)
{
    auto it = mItemNumMap.find(templateID);
    if (it == mItemNumMap.end()) return;
    auto &itemNum = it->second;
    if (itemNum == 0) return;
    itemNum -= 1;
    CheckSuitNum();
}

void SuitByTemplateID::CheckSuitNum()
{
    uint16_t newSuitNum = 0;

    for (const auto &it : mItemNumMap) {
        const auto &itemNum = it.second;
        if (itemNum) ++newSuitNum;
    }

    auto oldSuitNum = GetSuitNum();

    if (newSuitNum < oldSuitNum)
        DecSuitNum();
    else if (newSuitNum > oldSuitNum)
        IncSuitNum();
}

////////////////////////////////////////////////////////////////////////////////
//
// SuitCounter
//

void SuitCounter::OnLoadEquip(uint16_t templateID)
{
    const auto *itemCfg = sItemConfig.Get(templateID);
    if (!itemCfg) return;

    uint16_t suitID = static_cast<uint16_t>(itemCfg->Suit);
    if (suitID == 0) return;
    auto* suitCfg = sSuitConfig.Get(suitID);
    if (!suitCfg) return;
    auto it = mSuitMap.find(suitID);
    switch (suitCfg->SuitCountType) {
        case count_suit_by_num:
        {
            auto msuitgroup = sSuitConfig.GetMapByGroup(suitCfg->SuitGroup);
            for (auto itr : msuitgroup)
            {
                if (itr.first <= suitCfg->SuitLevel)
                {
                    auto it = mSuitMap.find(itr.second);

                    if (it == mSuitMap.end()) {
                        mSuitMap.emplace(itr.second, std::make_unique<SuitByNum>(mRole, itr.second));
                    }
                    it = mSuitMap.find(itr.second);
                    if (it == mSuitMap.end())
                        continue;

                    auto& suitPtr = it->second;
                    suitPtr->OnLoadEquip(templateID);
                }
            }
            return;
        }
        break;
        case count_suit_by_sub_type:
            if (it == mSuitMap.end()) {
                mSuitMap.emplace(suitID, std::make_unique<SuitBySubType>(mRole, suitID));
                it = mSuitMap.find(suitID);
            }
            break;

        case count_suit_by_template_id:
            if (it == mSuitMap.end()) {
                mSuitMap.emplace(suitID, std::make_unique<SuitByTemplateID>(mRole, suitID));
                it = mSuitMap.find(suitID);
            }
            break;

        default:
            break;
    }

    

   

    if (it == mSuitMap.end()) return;

    auto &suitPtr = it->second;
    suitPtr->OnLoadEquip(templateID);
}

void SuitCounter::OnUnloadEquip(uint16_t templateID)
{
    const auto *itemCfg = sItemConfig.Get(templateID);
    if (!itemCfg) return;

    uint16_t suitID = static_cast<uint16_t>(itemCfg->Suit);
    if (suitID == 0) return;

    auto* suitCfg = sSuitConfig.Get(suitID);
    if (!suitCfg) return;
    if (suitCfg->SuitCountType == count_suit_by_num)
    {
        auto msuitgroup = sSuitConfig.GetMapByGroup(suitCfg->SuitGroup);
        for (auto itr : msuitgroup)
        {
            if (itr.first <= suitCfg->SuitLevel)
            {
                auto it = mSuitMap.find(itr.second);
                if (it == mSuitMap.end()) continue;

                auto& suitPtr = it->second;
                suitPtr->OnUnloadEquip(templateID);
            }
        }
    }
    else
    {
        auto it = mSuitMap.find(suitID);
        if (it == mSuitMap.end()) return;

        auto& suitPtr = it->second;
        suitPtr->OnUnloadEquip(templateID);
    }
}
