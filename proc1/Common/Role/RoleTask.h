#pragma once
#include "RoleAction.h"

#include <list>
#include "quest_template_parser.hpp"


class RoleTask : public RoleAction
{
public:
    RoleTask(Role* master = nullptr);
    ~RoleTask();

public:
    bool Init() override;
    void Update(int32_t delta) override;

    void SetQuestInfo(const QUEST_INFO &questInfo);
    QUEST_INFO GetQuestInfo() const;

    void SetPreQuestID(uint16_t nPreQuestID) { mPreQuestID = nPreQuestID; }
    uint16_t GetPreQuestID() const { return mPreQuestID; }

    void SetCurQuestID(uint16_t nCurQuestID) { mCurQuestID = nCurQuestID; }
    uint16_t GetCurQuestID() const { return mCurQuestID; }

    void SetTimeLeftMS(uint32_t nTimeLeft);
    uint32_t GetTimeLeftMS() const { return mTimeLeftMS; }

    void SetTimeLeftS(uint32_t nTimeLeft);
    uint32_t GetTimeLeftS() const { return uint32_t(mTimeLeftMS / 1000.0 + 0.5); }

    void SetTimestamp(uint64_t nTimestamp) { mTimestampS = nTimestamp; }
    uint64_t GetTimestamp() const { return mTimestampS; }

    void SetQuestAchieves(const QUEST_ACHIEVE *pQuestAchieve, uint8_t num);
    void GetQuestAchieves(QUEST_ACHIEVE *pQuestAchieve, uint8_t &num) const;

    void SetQuestState(quest_state state) { mQuestState = state; }
    quest_state GetQuestState() const { return mQuestState; }

    void SetAcceptableQuests(const std::vector<uint16_t> &quests) { mAcceptableQuests = quests; }
    const std::vector<uint16_t> & GetAcceptableQuests() const { return mAcceptableQuests; }

    void ResetCurQuest();

    int32_t GetAchieveNum(uint16_t nQuestID, quest_achieve_type nAchevType, uint16_t nAchevID) const;

    bool IsDoingQuest() const { return mCurQuestID != 0; }

    void AddAchieve(quest_achieve_type nAchevType, uint16_t nID, int32_t nNum);

    const QuestHolder * GetCurQuestConfig() const { return sQuestTemplate.get_config(GetCurQuestID()); }

    void RemoveAchieves(uint16_t nQuestID);

    bool IsQuestReady();

private:
    void OnQuestTimeout();

    void AddAchieve_KillMonster(const QuestHolder *pQuestCfg, uint16_t nID, int32_t nNum);
    void AddAchieve_Huntings(const QuestIdValuePairs &huntings, uint16_t nID, int32_t nNum);
    void AddAchieve_GroupHuntings(const QuestGroupData &group_huntings, uint16_t nID, int32_t nNum);
    void AddAchieve_CollectItem(const QuestHolder *pQuestCfg, uint16_t nID, int32_t nNum);
    int32_t AddToAchieveList(quest_achieve_type nAchevType, uint16_t nID, int32_t nNum);

    void CheckQuestReady(const QuestIdValuePairs &cfg, quest_achieve_type nAchevType);

    void UpdateClientDisplay(quest_track_state nDataType, uint16_t nID, int32_t nNum);

    bool IsQuestReady_KillMonster(const QuestHolder *pQuestCfg);
    bool IsQuestReady_CollectItem(const QuestHolder *pQuestCfg);
    bool IsQuestReady(const QuestIdValuePairs &cfg, quest_achieve_type nAchevType);
    bool IsQuestReady(const QuestGroupData &cfg, quest_achieve_type nAchevType);

private:
    uint16_t mPreQuestID    = 0;
    uint16_t mCurQuestID    = 0;
    uint32_t mTimeLeftMS    = 0;
    uint64_t mTimestampS    = 0;

    std::list<QUEST_ACHIEVE> mQuestAchieves;

    quest_state mQuestState = quest_state_idle;

    std::vector<uint16_t> mAcceptableQuests;
};
