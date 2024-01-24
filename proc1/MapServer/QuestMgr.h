#pragma once

enum QuestNpcTipIcon            // 做任务时NPC头顶图标
{
    npc_tip_icon_none,          // 无
    npc_tip_icon_quest,         // 任务可交
    npc_tip_icon_excl,          // 任务可接
    npc_tip_icon_gray_quest     // 任务已接不可交
};

class Player;
class QuestDataMgr
{
    friend Player;
public:
    QuestDataMgr(Player* player);
    virtual ~QuestDataMgr();

    void SetQuestInfo(const QUEST_INFO& questInfo);
    void SetQuestAchieves(const QUEST_ACHIEVE* pQuestAchieve, uint8_t num);
    void ResumeQuest();
    void AcceptQuest(uint16_t nQuestID);
    void AccomplishQuest(uint16_t nQuestID);
    void DropQuest(uint16_t nQuestID);
    void SaveQuest();
    void QuestQueryCanAccept();

    void OnQuestReady();
    void OnQuestDoing();
    void OnQuestTimeout(uint16_t nQuestID);
    void OnQuestUpdateDisplay(uint16_t nQuestID, int nDataType, int nID, int nValue) ;



    bool IsDoingQuest();
    int GetQuestState();
    CLuaObject GetAcceptableQuests();
    uint16_t GetCurQuestID();
    uint16_t GetPreQuestID();

    void StartQuestDialog(Role* pNpc, uint16_t nQuestID, uint8_t nState);
    void AddToQuestAchieve(quest_achieve_type nAchevType, uint16_t nID, int32_t nNum);
    std::vector<uint16_t> GetAcceptableQuestsFromScript();
protected:
    // send
    void SendQuestAddNtfToGS(uint16_t nQuestID);
    void SendQuestNpcStateNtfToGS(uint16_t nNpcID, QuestNpcTipIcon icon);
    void SendQuestStateNtfToGS(uint16_t nQuestID, uint8_t nState);
    void SendQuestDropNtfToGS(uint16_t nQuestID);
    void SendQuestUpdateNtfToGS(uint16_t nQuestID, int nDataType, int nID, int nValue);
    void SendQuestTimeoutNtfToGS(uint16_t nQuestID);
    void SendQuestQueryCanAcceptNtfToGS(const std::vector<uint16_t>& questIDs);
private:
    void InitQuestAchieve(RoleTask* pRoleTask, const QuestHolder* pQuestCfg);
    void InitQuestAchieve_CollectItem(RoleTask* pRoleTask, const QuestHolder* pQuestCfg);
protected:
    Player* m_player;
};