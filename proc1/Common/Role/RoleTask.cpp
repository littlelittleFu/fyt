#include "stdafx.h"
#include "RoleTask.h"
#include "Role.h"


RoleTask::RoleTask(Role* master) : RoleAction(master)
{
    mQuestAchieves.clear();
    mAcceptableQuests.clear();
}

RoleTask::~RoleTask()
{

}

bool RoleTask::Init()
{
	return true;
}

void RoleTask::Update(int32_t delta)
{
    if (mTimeLeftMS > delta) {
        mTimeLeftMS -= delta;
    }
    else if (mTimeLeftMS > 0) {
        mTimeLeftMS = 0;
        OnQuestTimeout();
        ResetNeedUpdate(quest_need_update_flag);
    }
}

void RoleTask::SetTimeLeftMS(uint32_t nTimeLeft)
{
    mTimeLeftMS = nTimeLeft;
    if (nTimeLeft > 0) SetNeedUpdate(quest_need_update_flag);
}

void RoleTask::SetTimeLeftS(uint32_t nTimeLeft)
{
    SetTimeLeftMS(S2MS(nTimeLeft));
}

void RoleTask::SetQuestInfo(const QUEST_INFO &questInfo)
{
    SetPreQuestID(questInfo.pre_quest);
    SetCurQuestID(questInfo.cur_quest);
    SetTimeLeftS(questInfo.timeleft);
    SetTimestamp(questInfo.timestamp);
}

QUEST_INFO RoleTask::GetQuestInfo() const
{
    QUEST_INFO questInfo;
    questInfo.pre_quest = GetPreQuestID();
    questInfo.cur_quest = GetCurQuestID();
    questInfo.timeleft = GetTimeLeftS();
    questInfo.timestamp = GetTimestamp();

    return questInfo;
}

void RoleTask::SetQuestAchieves(const QUEST_ACHIEVE *pQuestAchieve, uint8_t num)
{
    if (!pQuestAchieve) return;

    mQuestAchieves.clear();
    mQuestAchieves.assign(pQuestAchieve, pQuestAchieve + num);
}

void RoleTask::GetQuestAchieves(QUEST_ACHIEVE *pQuestAchieve, uint8_t &num) const
{
    if (!pQuestAchieve) return;

    num = std::min<uint8_t>(num, static_cast<uint8_t>(mQuestAchieves.size()));
    auto it = mQuestAchieves.begin();

    for (uint8_t i = 0; i < num; ++i) {
        pQuestAchieve[i] = *it++;
    }
}

void RoleTask::ResetCurQuest()
{
    RemoveAchieves(GetCurQuestID());

    SetCurQuestID(0);
    SetTimeLeftMS(0);
    SetTimestamp(0);
    SetQuestState(quest_state_idle);
}

void RoleTask::RemoveAchieves(uint16_t nQuestID)
{
    auto it = std::remove_if(mQuestAchieves.begin(), mQuestAchieves.end(), [&](const auto &achev) {
        return achev.quest == nQuestID;
    });
    mQuestAchieves.erase(it, mQuestAchieves.end());
}

int32_t RoleTask::GetAchieveNum(uint16_t nQuestID, quest_achieve_type nAchevType, uint16_t nAchevID) const
{
    auto it = std::find_if(mQuestAchieves.begin(), mQuestAchieves.end(), [&](const auto &achev) {
        return (achev.quest == nQuestID && achev.achev_type == nAchevType && achev.achev_id == nAchevID);
    });

    return (it == mQuestAchieves.end()) ? 0 : it->achev_num;
}

void RoleTask::OnQuestTimeout()
{
    auto *pMaster = GetMaster();
    if (!pMaster) return;
    if (!pMaster->IsPlayer()) return;
    auto player = static_cast<Player*>(pMaster);
    if (player) player->GetQuestDataMgr().OnQuestTimeout(GetCurQuestID());
}

void RoleTask::AddAchieve(quest_achieve_type nAchevType, uint16_t nID, int32_t nNum)
{
    auto *pQuestCfg = GetCurQuestConfig();
    if (!pQuestCfg) return;

    if (pQuestCfg->achieve_type != nAchevType) return;

    auto nQuestState = GetQuestState();

    if (nQuestState != quest_state_doing &&
        nQuestState != quest_state_ready) return;

    switch (nAchevType) {
    case quest_achev_kill_monster:
        AddAchieve_KillMonster(pQuestCfg, nID, nNum);
        break;

    case quest_achev_collect_item:
        AddAchieve_CollectItem(pQuestCfg, nID, nNum);
        break;

    default:
        break;
    }
}

void RoleTask::AddAchieve_KillMonster(const QuestHolder *pQuestCfg, uint16_t nID, int32_t nNum)
{
    if (!pQuestCfg->huntings.empty()) {
        AddAchieve_Huntings(pQuestCfg->huntings, nID, nNum);
    }
    else if (!pQuestCfg->group_huntings.ids.empty()) {
        AddAchieve_GroupHuntings(pQuestCfg->group_huntings, nID, nNum);
    }
}

void RoleTask::AddAchieve_Huntings(const QuestIdValuePairs &huntings, uint16_t nID, int32_t nNum)
{
    auto it = std::find_if(huntings.begin(), huntings.end(), [&](auto &cfg) { return (cfg.id == nID); });
    if (it == huntings.end()) return;

    auto nAccum = AddToAchieveList(quest_achev_kill_monster, nID, nNum);
    UpdateClientDisplay(quest_track_state_hunting, nID, nAccum);

    if (nAccum < it->n) return;

    // 判断任务是否已完成
    CheckQuestReady(huntings, quest_achev_kill_monster);
}

void RoleTask::AddAchieve_GroupHuntings(const QuestGroupData &group_huntings, uint16_t nID, int32_t nNum)
{
    auto &ids = group_huntings.ids;
    auto it = std::find(ids.begin(), ids.end(), nID);
    if (it == ids.end()) return;

    AddToAchieveList(quest_achev_kill_monster, nID, nNum);
    UpdateClientDisplay(quest_track_state_group_hunting, nID, nNum);    // 发增量

    if (!IsQuestReady(group_huntings, quest_achev_kill_monster)) return;

    auto *pMaster = GetMaster();
    if (!pMaster->IsPlayer()) return;
    auto player = static_cast<Player*>(pMaster);
    if (player) player->GetQuestDataMgr().OnQuestReady();
}

void RoleTask::AddAchieve_CollectItem(const QuestHolder *pQuestCfg, uint16_t nID, int32_t nNum)
{
    auto &items = pQuestCfg->collect_items;

    auto it = std::find_if(items.begin(), items.end(), [&](const auto &cfg) { return (cfg.id == nID); });
    if (it == items.end()) return;

    auto nAccum = AddToAchieveList(quest_achev_collect_item, nID, nNum);

    if (nAccum < it->n) {

        if (GetQuestState() == quest_state_ready) {
            // 玩家丢弃物品，由ready转为doing
            auto *pMaster = GetMaster();
            if (!pMaster->IsPlayer()) return;
            auto player = static_cast<Player*>(pMaster);
            if (player) player->GetQuestDataMgr().OnQuestDoing();
        }
    }

    UpdateClientDisplay(quest_track_state_item, nID, nAccum);
    CheckQuestReady(items, quest_achev_collect_item);
}

int32_t RoleTask::AddToAchieveList(quest_achieve_type nAchevType, uint16_t nID, int32_t nNum)
{
    auto nCurQuestID = GetCurQuestID();

    auto it = std::find_if(mQuestAchieves.begin(), mQuestAchieves.end(), [&](const auto &achev) {
        return (achev.quest == nCurQuestID && achev.achev_type == nAchevType && achev.achev_id == nID);
    });

    if (it == mQuestAchieves.end())
        it = mQuestAchieves.insert(mQuestAchieves.end(), {nCurQuestID, static_cast<uint8_t>(nAchevType), nID, nNum});
    else
        it->achev_num += nNum;

    return it->achev_num;
}

void RoleTask::UpdateClientDisplay(quest_track_state nDataType, uint16_t nID, int32_t nNum)
{
    if (GetQuestState() != quest_state_doing) return;

    auto *pMaster = GetMaster();
    if (!pMaster->IsPlayer()) return;
    auto player = static_cast<Player*>(pMaster);
    if (player) player->GetQuestDataMgr().OnQuestUpdateDisplay(GetCurQuestID(), nDataType, nID, nNum);
}

void RoleTask::CheckQuestReady(const QuestIdValuePairs &cfg, quest_achieve_type nAchevType)
{
    if (GetQuestState() != quest_state_doing) return;

    if (!IsQuestReady(cfg, nAchevType)) return;

    // 已完成
    auto *pMaster = GetMaster();
    if (!pMaster->IsPlayer()) return;
    auto player = static_cast<Player*>(pMaster);
    if (player) player->GetQuestDataMgr().OnQuestReady();
}

bool RoleTask::IsQuestReady()
{
    auto *pQuestCfg = GetCurQuestConfig();
    if (!pQuestCfg) return false;

    switch (pQuestCfg->achieve_type) {
    case quest_achev_talk_to_npc:
        return true;

    case quest_achev_kill_monster:
        return IsQuestReady_KillMonster(pQuestCfg);

    case quest_achev_collect_item:
        return IsQuestReady_CollectItem(pQuestCfg);

    default:
        return false;
    }
}

bool RoleTask::IsQuestReady_KillMonster(const QuestHolder *pQuestCfg)
{
    if (!pQuestCfg->huntings.empty()) {
        return IsQuestReady(pQuestCfg->huntings, quest_achev_kill_monster);
    }
    else if (!pQuestCfg->group_huntings.ids.empty()) {
        return IsQuestReady(pQuestCfg->group_huntings, quest_achev_kill_monster);
    }
    return false;
}

bool RoleTask::IsQuestReady(const QuestIdValuePairs &cfg, quest_achieve_type nAchevType)
{
    auto nCurQuestID = GetCurQuestID();

    for (auto &quest : cfg) {
        auto nAchevNum = GetAchieveNum(nCurQuestID, nAchevType, quest.id);
        if (nAchevNum < quest.n) return false;
    }
    return true;
}

bool RoleTask::IsQuestReady(const QuestGroupData &cfg, quest_achieve_type nAchevType)
{
    auto nCurQuestID = GetCurQuestID();

    int32_t nSum = 0;
    for (auto &id : cfg.ids) {
        nSum += GetAchieveNum(nCurQuestID, nAchevType, id);
    }

    return (nSum >= cfg.n);
}

bool RoleTask::IsQuestReady_CollectItem(const QuestHolder *pQuestCfg)
{
    return IsQuestReady(pQuestCfg->collect_items, quest_achev_collect_item);
}
