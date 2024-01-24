#include "stdafx.h"
#include "ProtoMS.h"
#include "SessionFactory.h"
#include "CNetManager.h"

QuestDataMgr::QuestDataMgr(Player* player) : m_player(player)
{
}

QuestDataMgr::~QuestDataMgr()
{

}

void QuestDataMgr::SetQuestInfo(const QUEST_INFO& questInfo)
{
	auto* pRoleTask = m_player->GetRoleTask();
	if (!pRoleTask) return;

	pRoleTask->SetQuestInfo(questInfo);
}

void QuestDataMgr::SetQuestAchieves(const QUEST_ACHIEVE* pQuestAchieve, uint8_t num)
{
	auto* pRoleTask = m_player->GetRoleTask();
	if (!pRoleTask) return;

	pRoleTask->SetQuestAchieves(pQuestAchieve, num);
}

void QuestDataMgr::ResumeQuest()
{
    auto* pRoleTask = m_player->GetRoleTask();
    if (!pRoleTask) return;

    auto* pQuestCfg = pRoleTask->GetCurQuestConfig();
    if (!pQuestCfg) return;

    auto& nCurQuestID = pQuestCfg->id;

    auto nCurTime = time(nullptr);
    auto nTimestamp = pRoleTask->GetTimestamp();

    switch (pQuestCfg->time_limit_type) {

    case quest_relative_time:       // 相对时间
        pRoleTask->SetTimestamp(nCurTime);    // 更新时间戳
        break;

    case quest_abs_time:            // 绝对时间
    {
        if (nCurTime < nTimestamp) return;

        auto nTimeElapsed = nCurTime - nTimestamp;
        auto nTimeLeft = pRoleTask->GetTimeLeftS();

        if (nTimeElapsed < nTimeLeft) {
            nTimeLeft -= nTimeElapsed;
            pRoleTask->SetTimeLeftS(nTimeLeft);
            pRoleTask->SetTimestamp(nCurTime);
        }
        else {
            OnQuestTimeout(nCurQuestID);
            return;
        }

        break;
    }

    case quest_period_time:         // 固定时间段
        if (nCurTime > pQuestCfg->end_time) {
            OnQuestTimeout(nCurQuestID);
            return;
        }

        pRoleTask->SetTimeLeftS(pQuestCfg->end_time - nCurTime);
        break;

    default:
        return;
    }

    SendQuestAddNtfToGS(nCurQuestID);
    pRoleTask->SetQuestState(quest_state_doing);

    if (pQuestCfg->accept_type == quest_accept_from_npc) {
        SendQuestNpcStateNtfToGS(pQuestCfg->accept_from, npc_tip_icon_none);
    }

    if (pQuestCfg->deliver_type == quest_deliver_to_npc) {
        SendQuestNpcStateNtfToGS(pQuestCfg->deliver_to, npc_tip_icon_gray_quest);
    }

    LuaBindCallVoid(LUA_SCRIPT_FUNC(m_player, "OnResumeQuest"), m_player->GetGUIDAsString(), nCurQuestID);

    if (pRoleTask->IsQuestReady()) {
        OnQuestReady();
    }
}

void QuestDataMgr::AcceptQuest(uint16_t nQuestID)
{
    auto* pRoleTask = m_player->GetRoleTask();
    if (!pRoleTask) return;

    auto* pQuestCfg = sQuestTemplate.get_config(nQuestID);
    if (!pQuestCfg) return;

    if (!pQuestCfg->consume_items.empty() ||
        !pQuestCfg->acquire_items.empty()) {

        auto* pRolePack = m_player->GetRolePack();
        if (!pRolePack) return;

        ItemParams removeItems, addItems;

        for (const auto& item : pQuestCfg->consume_items) {
            removeItems.emplace_back(item.id, item.n, item.require);
        }

        for (const auto& item : pQuestCfg->acquire_items) {
            addItems.emplace_back(item.id, item.n, item.require);
        }

        auto result = pRolePack->CanAddItems(addItems);
        if (result != ERR_OK) {
            m_player->SendErrorAck(result);
            return;
        }

        result = pRolePack->CanRemoveItems(removeItems);
        if (result != ERR_OK) {
            m_player->SendErrorAck(ERR_QUEST_REQ_ITEM);
            return;
        }

        pRolePack->RemoveItems(removeItems, site_range_bag, log_params{ "任务消耗" });
        pRolePack->AddItems(addItems, site_range_bag, log_params{ "任务发放" });
    }

    auto nCurTime = time(nullptr);
    uint32_t nTimeLeft = 0;

    switch (pQuestCfg->time_limit_type) {

    case quest_relative_time:       // 相对时间
    case quest_abs_time:            // 绝对时间
        nTimeLeft = pQuestCfg->fixed_time;
        break;

    case quest_period_time:         // 固定时间段
        if (nCurTime < pQuestCfg->start_time || nCurTime > pQuestCfg->end_time) {
            OnQuestTimeout(nQuestID);
            return;
        }

        nTimeLeft = pQuestCfg->end_time - nCurTime;
        break;

    default:
        return;
    }

    pRoleTask->SetCurQuestID(nQuestID);
    pRoleTask->SetTimestamp(nCurTime);
    pRoleTask->SetTimeLeftS(nTimeLeft);
    pRoleTask->SetQuestState(quest_state_doing);
    pRoleTask->RemoveAchieves(nQuestID);

    SendQuestAddNtfToGS(nQuestID);

    if (pQuestCfg->accept_type == quest_accept_from_npc) {
        SendQuestNpcStateNtfToGS(pQuestCfg->accept_from, npc_tip_icon_none);
    }

    if (pQuestCfg->deliver_type == quest_deliver_to_npc) {
        SendQuestNpcStateNtfToGS(pQuestCfg->deliver_to, npc_tip_icon_gray_quest);
    }

    LuaBindCallVoid(LUA_SCRIPT_FUNC(m_player, "OnAcceptQuest"), m_player->GetGUIDAsString(), nQuestID);

    InitQuestAchieve(pRoleTask, pQuestCfg);
}

void QuestDataMgr::AccomplishQuest(uint16_t nQuestID)
{
    auto* pRoleTask = m_player->GetRoleTask();
    if (!pRoleTask) return;

    auto* pQuestCfg = pRoleTask->GetCurQuestConfig();
    if (!pQuestCfg) return;

    if (pQuestCfg->id != nQuestID) return;

    // 扣除收集物品
    for (auto& it : pQuestCfg->collect_items) {
        auto nResult = m_player->RemoveItem(it.id, it.n, bind_require_any, site_range_bag, log_params{ "任务收集" });
        if (nResult != ERR_OK) {      // TODO: 提示用户
            LOG_NORMAL("RemoveItem failed with error %d", nResult);
        }
    }

    // 领取奖励
    log_params lp{ "任务奖励" };
    for (auto& it : pQuestCfg->reward_attrs) {
        if (it.att == role_exp)
            m_player->AddPlayerExperience(it.n, lp);
        else
            m_player->AddRoleProp64(it.att, it.n, lp);
    }

    for (auto& item : pQuestCfg->reward_items) {
        auto nResult = m_player->AddItem(item.id, item.n, static_cast<uint8_t>(item.require), static_cast<uint8_t>(site_range_bag), lp);
        if (nResult != ERR_OK) {      // TODO: 提示用户
            LOG_NORMAL("AddItem failed with error %d", nResult);
        }
    }

    SendQuestStateNtfToGS(nQuestID, quest_state_complete);

    if (pQuestCfg->deliver_type == quest_deliver_to_npc) {
        SendQuestNpcStateNtfToGS(pQuestCfg->deliver_to, npc_tip_icon_none);
    }

    pRoleTask->SetPreQuestID(nQuestID);
    pRoleTask->ResetCurQuest();

    LuaBindCallVoid(LUA_SCRIPT_FUNC(m_player, "OnAccomplishQuest"), m_player->GetGUIDAsString(), nQuestID);
}

void QuestDataMgr::DropQuest(uint16_t nQuestID)
{
    auto* pRoleTask = m_player->GetRoleTask();
    if (!pRoleTask) return;

    const auto* pQuestCfg = pRoleTask->GetCurQuestConfig();
    if (!pQuestCfg) return;

    if (pQuestCfg->id != nQuestID) return;

    if (pQuestCfg->type == quest_cannot_abort) return;      // 不可放弃

    pRoleTask->ResetCurQuest();

    SendQuestDropNtfToGS(nQuestID);

    // TODO: save quest_abort_cannot_accept quest id to db
}

void QuestDataMgr::SaveQuest()
{
    auto* pRoleTask = m_player->GetRoleTask();
    if (!pRoleTask) return;

    if (pRoleTask->IsDoingQuest()) {
        pRoleTask->SetTimestamp(time(nullptr));
    }

    m_player->SendSyncQuestReqToCS();
}

void QuestDataMgr::QuestQueryCanAccept()
{
    auto* pRoleTask = m_player->GetRoleTask();
    if (!pRoleTask) return;

    std::vector<uint16_t> questIDs;
    auto nQuestState = pRoleTask->GetQuestState();

    if (nQuestState == quest_state_accepting) {
        questIDs = pRoleTask->GetAcceptableQuests();
    }
    else if (nQuestState == quest_state_idle) {
        questIDs = GetAcceptableQuestsFromScript();
        pRoleTask->SetAcceptableQuests(questIDs);
    }

    SendQuestQueryCanAcceptNtfToGS(questIDs);

    if (nQuestState == quest_state_idle && !questIDs.empty())
        pRoleTask->SetQuestState(quest_state_accepting);
}

void QuestDataMgr::OnQuestReady()
{
    auto* pRoleTask = m_player->GetRoleTask();
    if (!pRoleTask) return;

    if (pRoleTask->GetQuestState() == quest_state_ready) return;

    auto* pQuestCfg = pRoleTask->GetCurQuestConfig();
    if (!pQuestCfg) return;

    SendQuestStateNtfToGS(pQuestCfg->id, quest_state_ready);

    if (pQuestCfg->deliver_type == quest_deliver_to_npc) {
        SendQuestNpcStateNtfToGS(pQuestCfg->deliver_to, npc_tip_icon_quest);
    }

    pRoleTask->SetQuestState(quest_state_ready);
}

void QuestDataMgr::OnQuestDoing()
{
    auto* pRoleTask = m_player->GetRoleTask();
    if (!pRoleTask) return;

    if (pRoleTask->GetQuestState() == quest_state_doing) return;

    SendQuestStateNtfToGS(pRoleTask->GetCurQuestID(), quest_state_doing);

    pRoleTask->SetQuestState(quest_state_doing);
}

void QuestDataMgr::OnQuestTimeout(uint16_t nQuestID)
{
    SendQuestTimeoutNtfToGS(nQuestID);

    auto* pRoleTask = m_player->GetRoleTask();
    if (!pRoleTask) return;

    const auto* pQuestCfg = pRoleTask->GetCurQuestConfig();
    if (!pQuestCfg) return;

    if (pQuestCfg->id == nQuestID)
        pRoleTask->ResetCurQuest();

    if (pQuestCfg->deliver_type == quest_deliver_to_npc) {
        SendQuestNpcStateNtfToGS(pQuestCfg->deliver_to, npc_tip_icon_none);
    }
}

void QuestDataMgr::OnQuestUpdateDisplay(uint16_t nQuestID, int nDataType, int nID, int nValue)
{
    SendQuestUpdateNtfToGS(nQuestID, nDataType, nID, nValue);
}

bool QuestDataMgr::IsDoingQuest()
{
    const auto* pRoleTask = m_player->GetRoleTask();
    if (!pRoleTask) return false;
    return pRoleTask->IsDoingQuest();
}

int QuestDataMgr::GetQuestState()
{
    const auto* pRoleTask = m_player->GetRoleTask();
    if (!pRoleTask) return quest_state_idle;
    return pRoleTask->GetQuestState();
}

CLuaObject QuestDataMgr::GetAcceptableQuests()
{
    auto quests = NewLuaObj();

    const auto* pRoleTask = m_player->GetRoleTask();
    if (!pRoleTask) return quests;

    auto& savedQuests = pRoleTask->GetAcceptableQuests();
    for (size_t i = 0; i < savedQuests.size(); ++i)
        quests[i + 1] = savedQuests[i];

    return quests;
}

uint16_t QuestDataMgr::GetCurQuestID()
{
    const auto* pRoleTask = m_player->GetRoleTask();
    if (!pRoleTask) return 0;
    return pRoleTask->GetCurQuestID();
}

uint16_t QuestDataMgr::GetPreQuestID()
{
    const auto* pRoleTask = m_player->GetRoleTask();
    if (!pRoleTask) return 0;
    return pRoleTask->GetPreQuestID();
}

void QuestDataMgr::StartQuestDialog(Role* pNpc, uint16_t nQuestID, uint8_t nState)
{
    ProtoMS_QuestNpcTalkAck questNpcTalkAck;
    questNpcTalkAck.clientSessionID = m_player->GetClSessionID();
    questNpcTalkAck.npc_guid = pNpc->GetGUID();
    questNpcTalkAck.quest_state_num = 1;
    questNpcTalkAck.quest_states[0].num = 1;
    questNpcTalkAck.quest_states[0].item[0].template_id = nQuestID;
    questNpcTalkAck.quest_states[0].item[0].state = nState;

    SendDataBySessionID(m_player->GetGsSessionID(), questNpcTalkAck);
}

void QuestDataMgr::AddToQuestAchieve(quest_achieve_type nAchevType, uint16_t nID, int32_t nNum)
{
    if (m_player->IsInDgnMap()) return;

    auto* pRoleTask = m_player->GetRoleTask();
    if (!pRoleTask) return;

    pRoleTask->AddAchieve(nAchevType, nID, nNum);
}

std::vector<uint16_t> QuestDataMgr::GetAcceptableQuestsFromScript()
{
    std::vector<uint16_t> questIDs;

    CLuaObject ary;
    LuaBindCallRet(ary, LUA_SCRIPT_FUNC(m_player, "OnQueryAcceptableQuests"), m_player->GetGUIDAsString());

    if (!ary.is_valid()) return questIDs;

    for (luabind::iterator it(ary), end; it != end; ++it) {

        auto obj = *it;
        if (luabind::type(obj) != LUA_TNUMBER) continue;

        auto id = luabind::object_cast<uint16_t>(obj);
        questIDs.push_back(id);
    }

    return questIDs;
}

void QuestDataMgr::SendQuestAddNtfToGS(uint16_t nQuestID)
{
    const auto* pRoleTask = m_player->GetRoleTask();
    if (!pRoleTask) return;

    const auto* pQuestCfg = sQuestTemplate.get_config(nQuestID);
    if (!pQuestCfg) return;

    ProtoGS_QuestAddNtf questAddNtf;
    questAddNtf.sessionid = m_player->GetClSessionID();
    questAddNtf.quest_id = nQuestID;
    strcpy_s(questAddNtf.quest_name, _countof(questAddNtf.quest_name), pQuestCfg->name.c_str());
    questAddNtf.quest_type = pQuestCfg->type;

    auto& i = questAddNtf.group_huntings_len;
    for (auto& id : pQuestCfg->group_huntings.ids) {
        questAddNtf.group_huntings[i].id = id;
        questAddNtf.group_huntings[i].required = pQuestCfg->group_huntings.n;
        questAddNtf.group_huntings[i].count = pRoleTask->GetAchieveNum(nQuestID, quest_achev_kill_monster, id);
        ++i;
    }

    auto& j = questAddNtf.huntings_len;
    for (auto& it : pQuestCfg->huntings) {
        questAddNtf.huntings[j].id = it.id;
        questAddNtf.huntings[j].required = it.n;
        questAddNtf.huntings[j].count = pRoleTask->GetAchieveNum(nQuestID, quest_achev_kill_monster, it.id);
        ++j;
    }

    auto& k = questAddNtf.collect_items_len;
    for (auto& it : pQuestCfg->collect_items) {
        questAddNtf.collect_items[k].id = it.id;
        questAddNtf.collect_items[k].required = it.n;
        questAddNtf.collect_items[k].count = pRoleTask->GetAchieveNum(nQuestID, quest_achev_collect_item, it.id);
        ++k;
    }

    auto& l = questAddNtf.apply_items_len;
    for (auto& it : pQuestCfg->consume_items) {
        questAddNtf.apply_items[l].id = it.id;
        questAddNtf.apply_items[l].count = it.n;
        ++l;
    }

    if (pQuestCfg->deliver_to) {
        questAddNtf.npcs_len = 1;
        questAddNtf.npcs[0].id = pQuestCfg->deliver_to;
        questAddNtf.npcs[0].count = 1;
    }

    questAddNtf.life = pRoleTask->GetTimeLeftS();
    SendDataBySessionID(m_player->GetGsSessionID(), questAddNtf);
}

void QuestDataMgr::SendQuestNpcStateNtfToGS(uint16_t nNpcID, QuestNpcTipIcon icon)
{
    ProtoMS_QuestNpcStateNtf questNpcStateNtf;
    questNpcStateNtf.sessionid = m_player->GetClSessionID();
    questNpcStateNtf.npc_id = nNpcID;
    questNpcStateNtf.state = static_cast<uint8_t>(icon);

    SendDataBySessionID(m_player->GetGsSessionID(), questNpcStateNtf);
}

void QuestDataMgr::SendQuestStateNtfToGS(uint16_t nQuestID, uint8_t nState)
{
    ProtoMS_QuestStateNtf questStateNtf;
    questStateNtf.sessionid = m_player->GetClSessionID();
    questStateNtf.quest_id = nQuestID;
    questStateNtf.state = nState;

    SendDataBySessionID(m_player->GetGsSessionID(), questStateNtf);
}

void QuestDataMgr::SendQuestDropNtfToGS(uint16_t nQuestID)
{
    ProtoMS_QuestDropNtf questDropNtf;
    questDropNtf.sessionid = m_player->GetClSessionID();
    questDropNtf.quest_id = nQuestID;

    SendDataBySessionID(m_player->GetGsSessionID(), questDropNtf);
}

void QuestDataMgr::SendQuestUpdateNtfToGS(uint16_t nQuestID, int nDataType, int nID, int nValue)
{
    ProtoMS_QuestUpdateNtf questUpdateNtf;
    questUpdateNtf.client_sessionid = m_player->GetClSessionID();
    questUpdateNtf.quest_id = nQuestID;
    questUpdateNtf.data_type = nDataType;
    questUpdateNtf.id = nID;
    questUpdateNtf.value = nValue;

    SendDataBySessionID(m_player->GetGsSessionID(), questUpdateNtf);
}

void QuestDataMgr::SendQuestTimeoutNtfToGS(uint16_t nQuestID)
{
    ProtoMS_QuestTimeoutNtf questTimeoutNtf;
    questTimeoutNtf.client_sessionid = m_player->GetClSessionID();
    questTimeoutNtf.quest_id = nQuestID;

    SendDataBySessionID(m_player->GetGsSessionID(), questTimeoutNtf);
}

void QuestDataMgr::SendQuestQueryCanAcceptNtfToGS(const std::vector<uint16_t>& questIDs)
{
    if (questIDs.empty()) return;

    ProtoGS_QuestQueryCanAcceptNtf questQueryCanAcceptNtf;
    questQueryCanAcceptNtf.sessionid = m_player->GetClSessionID();
    questQueryCanAcceptNtf.num = std::min<int>(questIDs.size(), _countof(questQueryCanAcceptNtf.quests));
    std::copy(questIDs.begin(), questIDs.begin() + questQueryCanAcceptNtf.num, questQueryCanAcceptNtf.quests);

    SendDataBySessionID(m_player->GetGsSessionID(), questQueryCanAcceptNtf);
}

void QuestDataMgr::InitQuestAchieve(RoleTask* pRoleTask, const QuestHolder* pQuestCfg)
{
    switch (pQuestCfg->achieve_type) {

    case quest_achev_talk_to_npc:
        OnQuestReady();
        break;

    case quest_achev_collect_item:
        InitQuestAchieve_CollectItem(pRoleTask, pQuestCfg);
        break;

    default:
        break;
    }
}

void QuestDataMgr::InitQuestAchieve_CollectItem(RoleTask* pRoleTask, const QuestHolder* pQuestCfg)
{
    auto* pRolePack = m_player->GetRolePack();
    if (!pRolePack) return;

    for (const auto& item : pQuestCfg->collect_items) {

        auto nNum = pRolePack->GetItemNum(item.id);
        if (nNum == 0) continue;

        AddToQuestAchieve(quest_achev_collect_item, item.id, nNum);
    }
}
