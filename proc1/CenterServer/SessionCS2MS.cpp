#include "stdafx.h"
#include "SessionCS2MS.h"
#include "SessionFactory.h"

#include "ILogHelper.h"
#include "CNetManager.h"
#include <string>
#include "AssignMapServer.h"

#include "UserMgr.h"
#include "GuildData.h"
#include "CustVarData.h"
#include "TopList.h"
#include "TradeData.h"
#include "GameMallMgr.h"
#include "WantedList.h"
#include "Title.h"
#include "RedemptionCodeMgr.h"

#include "ProtoCS.h"
#include "ProtoMS.h"
#include "ProtoDB.h"
#include "ProtoClient.h"
#include "MonitorChatMsgMgr.h"
#include "GMCmdHandler.h"
#include "CustListMgr.h"


SessionCS2MS::SessionCS2MS()
{

}

SessionCS2MS::~SessionCS2MS()
{

}

void SessionCS2MS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionCS2MS::OnLost()
{
	LOG_NORMAL("SessionCS2MS server OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
	//DoClose();
}

void SessionCS2MS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    MsgCostStat::GetInstance()->BeginHandleMsg();

    OnHeartBeat();

	switch (moduleid) {
		case MODULE_TYPE_MS:
			HandleMapServMsg(protoid, _pData);
			break;

        case MODULE_TYPE_GS:
            HandleGateServMsg(protoid, _pData);
            break;

        case MODULE_TYPE_CS:
            HandleCenterServMsg(protoid, _pData);
		default:
			LOG_WARN("Unhandled moduleid: %d", moduleid);
			break;
	}

    MsgCostStat::GetInstance()->EndHandleMsg(moduleid, protoid);
}

void SessionCS2MS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionCS2MS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionCS2MS::DoHeartBeat()
{

}

void SessionCS2MS::HandleMapServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_MS_HEART_BEAT_REQ, HandleMapServMsg_HeartBeatReq)
        HANDLE_MSG(PROTO_MS_ENTER_MS_ACK, HandleMapServMsg_EnterMSAck)
        HANDLE_MSG(PROTO_MS_ENTER_MS_NTF, HandleMapServMsg_EnterMSNtf)
        HANDLE_MSG(PROTO_MS_GET_INFO_REQ, HandleMapServMsg_GetInfoReq)
        HANDLE_MSG(PROTO_MS_ITEM_ACK, HandleMapServMsg_ItemAck)
        HANDLE_MSG(PROTO_MS_SYNC_BUFF_REQ, HandleMapServMsg_SyncBuffReq)
        HANDLE_MSG(PROTO_MS_SYNC_SKILL_REQ, HandleMapServMsg_SyncSkillReq)
        HANDLE_MSG(PROTO_MS_SEND_SYNC_ITEM_NTF, HandleMapServMsg_SendSyncItemNtf)
        HANDLE_MSG(PROTO_MS_SEND_DEL_ITEM_NTF, HandleMapServMsg_SendDelItemNtf)
        HANDLE_MSG(PROTO_MS_GET_ROLE_INFO_REQ, HandleMapServMsg_GetRoleInfoReq)
        HANDLE_MSG(PROTO_MS_CLEAR_ROLE_INFO_NTF, HandleMapServMsg_ClearRoleInfoReq)
        HANDLE_MSG(PROTO_MS_DELETE_ROLE_INFO_NTF, HandleMapServMsg_DeleteRoleInfoReq)
        HANDLE_MSG(PROTO_MS_INSERT_ROLE_INFO_NTF, HandleMapServMsg_InsertRoleInfoReq)
        HANDLE_MSG(PROTO_MS_UPDATE_ROLE_INFO_NTF, HandleMapServMsg_UpdateRoleInfoReq)
        HANDLE_MSG(PROTO_MS_SYNC_ROLE_INFO_REQ, HandleMapServMsg_SyncRoleInfoReq)
        HANDLE_MSG(PROTO_MS_SYNC_QUEST_REQ, HandleMapServMsg_SyncQuestReq)
        HANDLE_MSG(PROTO_MS_GET_GUILDS_REQ, HandleMapServMsg_GetGuildsReq)
        HANDLE_MSG(PROTO_MS_GET_GUILD_MEMBERS_REQ, HandleMapServMsg_GetGuildMembersReq)
        HANDLE_MSG(PROTO_MS_GET_GUILD_APPLICANTS_REQ, HandleMapServMsg_GetGuildApplicantsReq)
        HANDLE_MSG(PROTO_MS_SYNC_PLAYER_CUST_VAR, HandleMapServMsg_SyncPlayerCustVar)
        HANDLE_MSG(PROTO_MS_SYNC_PLAYER_ITEM_CUST_VAR, HandleMapServMsg_SyncPlayerItemCustVar)
        HANDLE_MSG(PROTO_MS_GET_CUST_VAR_REQ, HandleMapServMsg_GetCustVarReq)
        HANDLE_MSG(PROTO_MS_SET_CUST_VAR, HandleMapServMsg_SetCustVar)
        HANDLE_MSG(PROTO_MS_QUICK_BAR_SET, HandleMapServMsg_QuickBarSet)
        HANDLE_MSG(PROTO_MS_DGN_BIND_INFO, HandleMapServMsg_DgnBindInfo)
        HANDLE_MSG(PROTO_MS_UPDATE_TOPLIST_ACK, HandleMapServMsg_GetTopListAck)
        HANDLE_MSG(PROTO_MS_SYNC_GUILD_APPLICANT, HandleMapServMsg_SyncGuildApplicant)
        HANDLE_MSG(PROTO_MS_SYNC_GUILD_MEMBER, HandleMapServMsg_SyncGuildMember)       
        HANDLE_MSG(PROTO_MS_ADD_SYS_NEW_MAIL, HandleMapServMsg_AddSysNewMail)
        HANDLE_MSG(PROTO_MS_SYNC_MAIL_INFO_STATUS, HandleMapServMsg_SyncMailInfoStatus)
        HANDLE_MSG(PROTO_MS_MAIL_DEL_REQ, HandleMapServMsg_DelMailReq)
        HANDLE_MSG(PROTO_MS_SYNC_GUILD_INFO, HandleMapServMsg_SyncGuildInfo)
        HANDLE_MSG(PROTO_MS_SYNC_GUILD_RELATION, HandleMapServMsg_SyncGuildRelation)
        HANDLE_MSG(PROTO_MS_SYNC_ITEM_DYN_ATTRS, HandleMapServMsg_SyncItemDynAttrs)
        HANDLE_MSG(PROTO_MS_SYNC_ROLE_DYN_ATTRS, HandleMapServMsg_SyncRoleDynAttrs)
        HANDLE_MSG(PROTO_MS_GET_TRADE_DELEGATE_REQ, HandleMapServMsg_GetTradeDelegateReq)
        HANDLE_MSG(PROTO_MS_GET_TRADE_RECORDS_REQ, HandleMapServMsg_GetTradeRecordsReq)
        HANDLE_MSG(PROTO_MS_DELEGATE_CANCEL_REQ, HandleMapServMsg_DelegateCancelReq)
        HANDLE_MSG(PROTO_MS_DELEGATE_SELL_CMD, HandleMapServMsg_DelegateSellCmd)
        HANDLE_MSG(PROTO_MS_DELEGATE_BUY_CMD, HandleMapServMsg_DelegateBuyCmd)
        HANDLE_MSG(PROTO_MS_MARKET_SELL_CMD, HandleMapServMsg_MarketSellCmd)
        HANDLE_MSG(PROTO_MS_MARKET_BUY_CMD, HandleMapServMsg_MarketBuyCmd)
        HANDLE_MSG(PROTO_MS_GET_MAIL_ATTACHMENT_REQ, HandleMapServMsg_GetMailAttachmentReq)
        HANDLE_MSG(PROTO_MS_AUCTION_ADD_ITEM_INFO, HandleMapServMsg_SynAuctionInfo)
        HANDLE_MSG(PROTO_MS_AUCTION_GET_FINISH_INFO_REQ, HandleMapServMsg_GetAuctionFinishedInfoReq)
        HANDLE_MSG(PROTO_MS_AUCTION_HOUSE_REQ, HandleMapServMsg_GetAuctionHouseReq)
        HANDLE_MSG(PROTO_MS_GET_CONSTANT_CFG_REQ, HandleMapServMsg_GetConstantCfgReq)
        HANDLE_MSG(PROTO_MS_UPDATE_CONSTANT_CFG_REQ, HandleMapServMsg_UpdateConstantCfgReq)
        HANDLE_MSG(PROTO_MS_SET_SERVER_STATUS, HandleMapServMsg_SetServerStatus)
        HANDLE_MSG(PROTO_MS_MALL_LIMIT_INFO_UPDATE, HandleMapServMsg_UpdateMallLimitInfo)
        HANDLE_MSG(PROTO_MS_MALL_LIMIT_INFO_REQ, HandleMapServMsg_GetMallLimitInfoReq)
        HANDLE_MSG(PROTO_MS_DELETE_MALL_REMAINED_DATA, HandleMapServMsg_DeleteMallRemainedData)
        HANDLE_MSG(PROTO_MS_ADD_LOGIN_IP_TYPE, HandleMapServMsg_AddLoginIpType)
        HANDLE_MSG(PROTO_MS_DEL_LOGIN_IP_TYPE, HandleMapServMsg_DelLoginIpType)
        HANDLE_MSG(PROTO_MS_UPDATE_SUPPORT_PLAYER, HandleMapServMsg_UpdateSupportPlayer)
        HANDLE_MSG(PROTO_MS_ADD_LOCK_PLAYER, HandleMapServMsg_AddLockPlayer)
        HANDLE_MSG(PROTO_MS_ADD_LOCK_ROLE, HandleMapServMsg_AddLockRole)
        HANDLE_MSG(PROTO_MS_DEL_LOCK_PLAYER, HandleMapServMsg_DelLockPlayer)
        HANDLE_MSG(PROTO_MS_DEL_LOCK_ROLE, HandleMapServMsg_DelLockRole)
        HANDLE_MSG(PROTO_MS_GET_PROHIBIT_CHAT_INFO_REQ, HandleMapServMsg_GetProhibitChatInfoReq)
        HANDLE_MSG(PROTO_MS_DEL_PROHIBIT_INFO, HandleMapServMsg_DelProhibitInfo)
        HANDLE_MSG(PROTO_MS_ADD_PROHIBIT_CHAT_INTO, HandleMapServMsg_AddProhibitChatInfo)
        HANDLE_MSG(PROTO_MS_GET_WANTED_LIST_REQ, HandleMapServMsg_GetWantedListReq)
        HANDLE_MSG(PROTO_MS_POST_BOUNTY_REQ, HandleMapServMsg_PostBountyReq)
        HANDLE_MSG(PROTO_MS_CHECK_ROLE_EXISTENCE_REQ, HandleMapServMsg_CheckRoleExistenceReq)
        HANDLE_MSG(PROTO_MS_SAVE_GOODS_ISSUE_RECORD, HandleMapServMsg_SaveGoodsIssueRecord)
        HANDLE_MSG(PROTO_MS_GOODS_ISSUED_NTF, HandleMapServMsg_GoodsIssuedNtf)
        HANDLE_MSG(PROTO_MS_REBATE_MONDY_USED_NTF, HandleMapServMsg_RebateMoneyUsedNtf)
        HANDLE_MSG(PROTO_MS_PLAYER_SET_NAME_REQ, HandleMapServMsg_PlayerSetNameReq)
        HANDLE_MSG(PROTO_MS_ITEM_TIP, HandleMapServMsg_ItemTip)
        HANDLE_MSG(PROTO_MS_MONITOR_CHAT_MSG, HandleMapServMsg_MonitorChatMsg)
        HANDLE_MSG(PROTO_MS_ADD_TITLE, HandleMapServMsg_AddTitle)
        HANDLE_MSG(PROTO_MS_DEL_TITLE, HandleMapServMsg_DelTitle)
        HANDLE_MSG(PROTO_MS_TITLE_WEAR_TYPE, HandleMapServMsg_ChangeTitleWearType)
        HANDLE_MSG(PROTO_MS_SYNC_TITLE_INFO, HandleMapServMsg_SyncTitleInfo)
        HANDLE_MSG(PROTO_MS_PLAYER_ACTIVATION_CODE, HandleMapServMsg_AddActivationCodeTask)
        HANDLE_MSG(PROTO_MS_ADD_PLAYER_PROHIBIT_CHAT, HandleMapServMsg_AddPlayerProhibitChat)
        HANDLE_MSG(PROTO_MS_DEL_PLAYER_PROHIBIT_CHAT, HandleMapServMsg_DelPlayerProhibitChat)
        HANDLE_MSG(PROTO_MS_RUNGMCMD, HandleMapServMsg_RunGMCmd)
        HANDLE_MSG(PROTO_MS_CUSTOM_HTTP, HandleMapServMsg_RunLuaHttp)
        HANDLE_MSG(PROTO_MS_DEL_ROLE_ACK, HandleMapServMsg_DelRole)
        HANDLE_MSG(PROTO_MS_SYNC_CUST_LIST, HandleMapServMsg_SyncCustList)
        HANDLE_MSG(PROTO_MS_GET_CUST_LIST_REQ, HandleMapServMsg_GetCustListReq)
        HANDLE_MSG(PROTO_MS_SYNC_GOODS_POST_RECORD, HandleMapServMsg_GoodsPostRecord)
        HANDLE_MSG(PROTO_MS_SET_PLAYER_GENDER, HandleMapServMsg_SetPlayerGender)


    END_MSG_HANDLER()
}

void SessionCS2MS::HandleMapServMsg_GetTopListAck(void* pData)
{
    ProtoMS_UpdateTopListAck* ack = (ProtoMS_UpdateTopListAck*)pData;
    TopList::GetInstance()->Update(ack);
}

void SessionCS2MS::HandleMapServMsg_ItemAck(void* pData)
{
	auto pItemAddAck = (ProtoMS_ItemAddAck*)pData;
	SendDataBySessionID(pItemAddAck->nGS2CSSessionID, *pItemAddAck);
}

void SessionCS2MS::HandleMapServMsg_SyncBuffReq(void *pData)
{
    auto pSyncBuffReq = (ProtoMS_SyncBuffReq *)pData;

	auto user = UserMgr::GetInstance()->FindUser(pSyncBuffReq->playerid);
	if (nullptr == user) {
		LOG_ERROR("sync role buff failed. cant find user:%" PRIu64, pSyncBuffReq->playerid);
		return;
	}

    user->SetBuffList(pSyncBuffReq->roleid, pSyncBuffReq->buffs, pSyncBuffReq->buffNum, pSyncBuffReq->beFirstPack);
}

void SessionCS2MS::HandleMapServMsg_SyncSkillReq(void *pData)
{
    auto pSyncSkillReq = (ProtoMS_SyncSkillReq *)pData;

    auto user = UserMgr::GetInstance()->FindUser(pSyncSkillReq->playerid);
    if (nullptr == user) {
        LOG_ERROR("sync skill failed. can't find user: %" PRIu64, pSyncSkillReq->playerid);
        return;
    }

    user->SyncSkillList(pSyncSkillReq->roleid, pSyncSkillReq->skillInfo, pSyncSkillReq->skillNum);
}

void SessionCS2MS::HandleMapServMsg_HeartBeatReq(void* pData)
{
	ProtoMS_HeartBeatAck ack;
	SendPkg(&ack, sizeof(ack));
}

void SessionCS2MS::HandleMapServMsg_EnterMSAck(void* pData)
{
	auto pEnterMSAck = (ProtoMS_EnterMSAck*)pData;
	SendDataBySessionID(pEnterMSAck->nCS2GSSessionID, *pEnterMSAck);
}

void SessionCS2MS::HandleMapServMsg_EnterMSNtf(void* pData)
{
	auto pEnterMSNtf = (ProtoMS_EnterMSNtf*)pData;
	auto pUser = UserMgr::GetInstance()->FindUser(pEnterMSNtf->token);
	if (!pUser) {
		LOG_ERROR("pUser is NULL");
		return;
	}
	SendDataBySessionID(pUser->GetCS2GSSessionID(), *pEnterMSNtf);
}

void SessionCS2MS::HandleMapServMsg_GetInfoReq(void* pData)
{
	MapServer mapserver;
	mapserver.m_Ip = GetRemoteIp();
	mapserver.m_Port = GetRemotePort();
	mapserver.mSessionID = GetID();

	//AssignMapServer::GetInstance()->AddMapServerTable(255, mapserver);//"255"-->"新手村“
}

void SessionCS2MS::HandleMapServMsg_SendSyncItemNtf(void* pData)
{
	auto pntf = (ProtoMS_SendSyncItemNtf*)pData;
	auto user = UserMgr::GetInstance()->FindUser(pntf->token);
	if (nullptr != user) {
		user->HandleMapServMsg_SendSyncItemNtf(pntf);
	}
    else
    {
        user = UserMgr::GetInstance()->FindUserByRoleGUID(pntf->role_guid);
        if (nullptr != user) {
            user->HandleMapServMsg_SendSyncItemNtf(pntf);
        }
    }
}

void SessionCS2MS::HandleMapServMsg_SendDelItemNtf(void* pData)
{
    const auto *msg = static_cast<ProtoMS_SendDelItemNtf *>(pData);
    auto *user = UserMgr::GetInstance()->FindUser(msg->user_guid);
    if (!user) return;
    user->DeleteItem(msg->role_guid, msg->item_guid, msg->tradeDel);
}

void SessionCS2MS::HandleMapServMsg_GetRoleInfoReq(void* pdata)
{
	auto pntf = (ProtoCS_GetRoleInfoReq*)pdata;
	auto user = UserMgr::GetInstance()->FindUser(pntf->token);
	if (nullptr != user) {
		user->HandleMapServMsg_GetRoleInfoReq(pntf);
	}
	
}

void SessionCS2MS::HandleMapServMsg_ClearRoleInfoReq(void* pData)
{
	auto pntf = (ProtoCS_ClearRoleInfoNtf*)pData;
	auto user = UserMgr::GetInstance()->FindUser(pntf->token);
	if (nullptr != user) {
		user->HandleMapServMsg_ClearRoleInfoNtf(pntf);
	}
}

void SessionCS2MS::HandleMapServMsg_DeleteRoleInfoReq(void* pData)
{
	auto pntf = (ProtoCS_DeleteRoleInfoNtf*)pData;
	auto user = UserMgr::GetInstance()->FindUser(pntf->token);
	if (nullptr != user) {
		user->HandleMapServMsg_DelRoleInfoNtf(pntf);
	}
}

void SessionCS2MS::HandleMapServMsg_UpdateRoleInfoReq(void* pData)
{
	auto pntf = (ProtoCS_UpdateRoleInfoNtf*)pData;
	auto user = UserMgr::GetInstance()->FindUser(pntf->token);
	if (nullptr != user) {
		user->HandleMapServMsg_UpdateRoleInfoNtf(pntf);
	}
}

void SessionCS2MS::HandleMapServMsg_InsertRoleInfoReq(void* pData)
{
	auto pntf = (ProtoCS_InsertRoleInfoNtf*)pData;
	auto user = UserMgr::GetInstance()->FindUser(pntf->token);
	if (nullptr != user) {
		user->HandleMapServMsg_InsertRoleInfoNtf(pntf);
	}
}

void SessionCS2MS::HandleMapServMsg_SyncRoleInfoReq(void *pData)   //信息发往数据库
{
    auto pSyncRoleInfoReq = (ProtoMS_SyncRoleInfoReq *)pData;
    auto pUser = UserMgr::GetInstance()->FindUser(pSyncRoleInfoReq->userid);
    if (!pUser) {
        LOG_ERROR("pUser is NULL. userid: %" PRIu64, pSyncRoleInfoReq->userid);
        return;
    }

    // 截取退出玩家排行榜信息，更新进排行榜待更新区域
    TopList::GetInstance()->AddTmpTopList(pSyncRoleInfoReq->roleBriefInfo);

    pUser->SyncRoleInfo(pSyncRoleInfoReq->roleid, pSyncRoleInfoReq->roleBriefInfo,
        pSyncRoleInfoReq->roleExtraInfo, pSyncRoleInfoReq->roleSettings);
}

void SessionCS2MS::HandleMapServMsg_SyncQuestReq(void *pData)
{
    auto *pSyncQuestReq = static_cast<ProtoMS_SyncQuestReq *>(pData);

    auto *pUser = UserMgr::GetInstance()->FindUser(pSyncQuestReq->playerid);
    if (!pUser) {
        LOG_ERROR("sync quest failed. can't find user: %" PRIu64, pSyncQuestReq->playerid);
        return;
    }

    pUser->SyncQuestInfo(pSyncQuestReq->roleid, pSyncQuestReq->quest_info, pSyncQuestReq->quest_achevs, pSyncQuestReq->quest_achev_num);
}

void SessionCS2MS::HandleMapServMsg_GetConstantCfgReq(void* pData)
{
    auto* msg = static_cast<ProtoMS_GetConstantCfgReq*>(pData);

    if (ConfigInfo::GetInstance()->m_beInited)
    {
        ProtoCS_GetConstantCfgAck cfgAck;
        cfgAck.custom << ConfigInfo::GetInstance()->m_constantCfgMap;
        SendPkg(&cfgAck, sizeof(cfgAck));
    }
    else {
        SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
    }
}

void SessionCS2MS::HandleMapServMsg_UpdateConstantCfgReq(void* pData)
{
    // 相同key用ms的
    auto* msg = static_cast<ProtoMS_UpdateConstantCfgReq*>(pData);
    CONSTANT_CFG_MAP& constantCfgMap = ConfigInfo::GetInstance()->m_constantCfgMap;
    CONSTANT_CFG_MAP m;
    msg->custom >> m;
    for (auto& ele : m)
    {
        constantCfgMap[ele.first] = std::move(ele.second);
    }
}

void SessionCS2MS::HandleMapServMsg_SetServerStatus(void* pData)
{
    auto* msg = static_cast<ProtoMS_SetServerStatus*>(pData);
    if (msg->status == server_status_close)
    {
        // 转发
        SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
        SendDataBySessionType(SESSION_TYPE_CS2LS, *msg);
        // 延迟关闭
        TimerData timer;
        timer.interval = CLOSE_CUR_SERVER_DELAY_TIME;
        timer.loop = false;
        timer.callBack = [this](const TimerData&) {
            CenterServer::GetInstance()->Quit();
        };
        TimeHelper::GetInstance()->AddTimer(timer);

    }
}

void SessionCS2MS::HandleMapServMsg_UpdateMallLimitInfo(void* pData)
{
    auto* msg = static_cast<ProtoMS_MallLimitInfoUpdate*>(pData);
    GameMallMgr::GetInstance()->UpdateMallInfoToDB(*msg);
}

void SessionCS2MS::HandleMapServMsg_GetMallLimitInfoReq(void* pData)
{
    auto* msg = static_cast<ProtoMS_MallLimitInfoReq*>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_DeleteMallRemainedData(void* pData)
{
    auto* msg = static_cast<ProtoMS_DeleteMallRemainedData*>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}
void SessionCS2MS::HandleMapServMsg_AddLoginIpType(void* pData)
{
    auto* msg = static_cast<ProtoMS_AddLoginIpType*>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_DelLoginIpType(void* pData)
{
    auto* msg = static_cast<ProtoMS_DelLoginIpType*>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_UpdateSupportPlayer(void* pData)
{
    auto* msg = static_cast<ProtoMS_UpdateSupportPlayer*>(pData);
    std::list<uint64_t> l;
    for (auto i = 0; i < msg->num; ++i)
    {
        auto user = UserMgr::GetInstance()->FindUser(std::string(msg->name[i]).c_str());
        if (user)
        {
            user->UpdateSupport(msg->type);
            const auto& roles = user->GetRoleDataMap();
            for (auto& role : roles) l.push_back(role.first);
        }
    }
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);

    msg->num = 0;
    for (auto& id : l)
    {
        msg->guid[msg->num++] = id;
        if (msg->num >= _countof(msg->guid))
        {
            SendPkg(msg, sizeof(*msg));
            msg->num = 0;
        }
    }
    if (msg->num) SendPkg(msg, sizeof(*msg));
}

void SessionCS2MS::HandleMapServMsg_AddLockPlayer(void* pData)
{
    auto* msg = static_cast<ProtoMS_AddLockPlayer*>(pData);
    for (auto i = 0; i < msg->num; ++i)
    {
        auto user = UserMgr::GetInstance()->FindUser(std::string(msg->name[i]));
        if (user && (user->GetOnlineState() == online_state_logged_in))
        {
            ProtoGS_KickOutByLock data;
            data.info = E_EXIT_EXITGS;
            data.sessionid = user->GetGS2CLSessionID();
            data.token = user->GetToken();
            SendDataBySessionID(user->GetCS2GSSessionID(), data);
        }
    }
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_DelRole(void* pData)
{
    auto* msg = static_cast<ProtoMS_Del_Role_By_GM*>(pData);
    ProtoGS_DeleteRoleReq req;
    auto user = UserMgr::GetInstance()->FindUser(msg->pid);
    if (user)
    {
        req.sessionid = user->GetCS2GSSessionID();
        req.token = user->GetToken();
        user->SyncUserData();
    }
    req.playerid = msg->pid;
    req.roleid = msg->guid;
    req.status = role_status_permanent_deleted;
    TradeData::GetInstance()->HandleAllDelegateCancel(msg->guid);
    SendDataBySessionType(SESSION_TYPE_CS2DB, req);
}

void SessionCS2MS::HandleMapServMsg_SyncCustList(void* pData)
{
    auto* msg = static_cast<ProtoMS_SyncCustList*>(pData);
    CustListInfoMgr::GetInstance()->SyncCustInfoFromMS(msg->type, msg->num, msg->data);
}

void SessionCS2MS::HandleMapServMsg_GetCustListReq(void* pData)
{
    auto* msg = static_cast<ProtoMS_GetCustListReq*>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_AddLockRole(void* pData)
{
    auto* msg = static_cast<ProtoMS_AddLockRole*>(pData);
    for (int i = 0; i < msg->num; ++i) {
        auto user = (*UserMgr::GetInstance())[msg->guid[i]];
        if (nullptr == user)continue;
        auto& roleDataMap = user->GetRoleDataMap();
        auto iter = roleDataMap.find(msg->guid[i]);
        if (iter != roleDataMap.end()) {
            iter->second.GetBriefInfo().is_lock = 1;
        }

        if (user && (user->GetOnlineState() == online_state_logged_in))
        {
            ProtoGS_KickOutByLock data;
            data.info = E_EXIT_EXITGS;
            data.sessionid = user->GetGS2CLSessionID();
            data.token = user->GetToken();
            SendDataBySessionID(user->GetCS2GSSessionID(), data);
        }
    }
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_DelLockPlayer(void* pData)
{
    auto* msg = static_cast<ProtoMS_DelLockPlayer*>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_DelLockRole(void* pData)
{
    auto* msg = static_cast<ProtoMS_DelLockRole*>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_GetProhibitChatInfoReq(void* pData)
{
    auto* msg = static_cast<ProtoMS_GetProhibitChatInfoReq*>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_DelProhibitInfo(void* pData)
{
    auto* msg = static_cast<ProtoMS_DelProhibitInfo*>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_AddProhibitChatInfo(void* pData)
{
    auto* msg = static_cast<ProtoMS_AddProhibitChatInfo*>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}
void SessionCS2MS::HandleMapServMsg_GetTradeDelegateReq(void* pData)
{
    auto* msg = static_cast<ProtoMS_GetTradeDelegateReq*>(pData);

    if (TradeData::GetInstance()->HasBuyDelegate() && TradeData::GetInstance()->HasSellDelegate())
    {
        TradeData::GetInstance()->SendTradeDelegateToMS();
    }
    else {
        SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
    }
}

void SessionCS2MS::HandleMapServMsg_GetTradeRecordsReq(void* pData)
{
    auto* msg = static_cast<ProtoMS_GetTradeRecordsReq*>(pData);

    if (TradeData::GetInstance()->HasRecords())
    {
        TradeData::GetInstance()->SendTradeRecordsToMS();
    }
    else {
        SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
    }
}

void SessionCS2MS::HandleMapServMsg_DelegateCancelReq(void* pData)
{
    auto* msg = static_cast<ProtoMS_DelegateCancelReq*>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_DelegateSellCmd(void* pData)
{
    auto* msg = static_cast<ProtoMS_DelegateSellCmd*>(pData);
    TradeData::GetInstance()->GenerateCurTime(msg->sellItem.trade_time);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_DelegateBuyCmd(void* pData)
{
    auto* msg = static_cast<ProtoMS_DelegateBuyCmd*>(pData);
    TradeData::GetInstance()->GenerateCurTime(msg->buyItem.trade_time);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_MarketSellCmd(void* pData)
{
    auto* msg = static_cast<ProtoMS_MarketSellCmd*>(pData);
    TradeData::GetInstance()->HandleMarketSellCmd(*msg);
}

void SessionCS2MS::HandleMapServMsg_MarketBuyCmd(void* pData)
{
    auto* msg = static_cast<ProtoMS_MarketBuyCmd*>(pData);
    TradeData::GetInstance()->HandleMarketBuyCmd(*msg);
}

void SessionCS2MS::HandleMapServMsg_GetMailAttachmentReq(void* pData)
{
    auto* msg = static_cast<ProtoMS_GetMailAttachmentReq*>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_GetAuctionFinishedInfoReq(void* pData)
{
    auto* msg = static_cast<ProtoMS_AuctionGetFinishedInfoReq*>(pData);
    ProtoCS_AuctionGetFinishedInfoAck data;
    strcpy_s(data.func, _countof(data.func), msg->func);
    AuctionHouseMgr::GetInstance()->GetFinishedItemInfo(data,msg->time);
    SendDataBySessionType(SESSION_TYPE_CS2MS, data);
}

void SessionCS2MS::HandleMapServMsg_GetAuctionHouseReq(void* pData)
{
    auto* msg = static_cast<ProtoMS_GetAuctionHouseReq*>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_GetGuildsReq(void *pData)
{
    auto *msg = static_cast<ProtoMS_GetGuildsReq *>(pData);

    if (GuildData::GetInstance()->HasGuilds()) {
        ProtoCS_GetGuildsAck data;
        data.guilds = GuildData::GetInstance()->GetGuilds();

        SendDataBySessionType(SESSION_TYPE_CS2MS, data);
    }
    else {
        SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
    }
}

void SessionCS2MS::HandleMapServMsg_GetGuildMembersReq(void *pData)
{
    auto *msg = static_cast<ProtoMS_GetGuildMembersReq *>(pData);

    if (GuildData::GetInstance()->HasMembers()) {
        ProtoCS_GetGuildMembersAck data;
        data.members = GuildData::GetInstance()->GetMembers();

        SendDataBySessionType(SESSION_TYPE_CS2MS, data);
    }
    else {
        SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
    }
}

void SessionCS2MS::HandleMapServMsg_GetGuildApplicantsReq(void *pData)
{
    auto *msg = static_cast<ProtoMS_GetGuildApplicantsReq *>(pData);

    if (GuildData::GetInstance()->HasApplicants()) {
        ProtoCS_GetGuildApplicantsAck data;
        data.applicants = GuildData::GetInstance()->GetApplicants();

        SendDataBySessionType(SESSION_TYPE_CS2MS, data);
    }
    else {
        SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
    }
}

void SessionCS2MS::HandleMapServMsg_SyncPlayerCustVar(void *pData)
{
    auto *msg = static_cast<ProtoMS_SyncPlayerCustVar *>(pData);

    std::unique_ptr<CUST_VAR_MAP> vars(msg->vars);

    auto *user = UserMgr::GetInstance()->FindUser(msg->playerid);
    if (!user) {
        LOG_ERROR("sync player cust var failed. can't find user: %" PRIu64, msg->playerid);
        return;
    }

    user->SyncCustVars(msg->roleid, std::move(*vars));
}

void SessionCS2MS::HandleMapServMsg_SyncPlayerItemCustVar(void *pData)
{
    auto *msg = static_cast<ProtoMS_SyncPlayerItemCustVar *>(pData);

    std::unique_ptr<CUST_VAR_SP_LIST> vars(msg->vars);

    auto *user = UserMgr::GetInstance()->FindUser(msg->playerid);
    if (!user) {
        LOG_ERROR("sync player cust var failed. can't find user: %" PRIu64, msg->playerid);
        return;
    }

    user->SyncItemCustVars(msg->roleid, std::move(*vars));
}

void SessionCS2MS::HandleMapServMsg_GetCustVarReq(void *pData)
{
    auto *msg = static_cast<ProtoMS_GetCustVarReq *>(pData);

    if (CustVarData::GetInstance()->HasData()) {
        ProtoDB_GetCustVarAck data;
        data.vars = &CustVarData::GetInstance()->GetCustVars();

        SendDataBySessionType(SESSION_TYPE_CS2MS, data);
    }
    else {
        SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
    }
}

void SessionCS2MS::HandleMapServMsg_SetCustVar(void *pData)
{
    auto *msg = static_cast<ProtoMS_SetCustVar *>(pData);

    CUST_VAR_SP var(msg->var);

    CustVarData::GetInstance()->SetCustVar(var);

    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_QuickBarSet(void* pData)
{
    auto* msg = static_cast<ProtoMS_QuickBarSet*>(pData);
    auto user = UserMgr::GetInstance()->FindUser(msg->userid);
    if (nullptr != user&&msg->num!=0) {
        user->HandleMapServMsg_SyncQuickBarSet(msg);
    }
}

void SessionCS2MS::HandleMapServMsg_DgnBindInfo(void* pData)
{
    auto* msg = static_cast<ProtoMS_DgnBindInfo*>(pData);
    auto user = UserMgr::GetInstance()->FindUser(msg->userid);
    if (nullptr != user)
    {
        user->HandleMapServMsg_SyncDgnBindInfo(msg);
    }
}

void SessionCS2MS::HandleMapServMsg_SyncGuildApplicant(void *pData)
{
    const auto *msg = static_cast<ProtoMS_SyncGuildApplicant *>(pData);

    SPGUILD_APPLICANT applicant(msg->applicant);

    GuildData::GetInstance()->SyncGuildApplicant(applicant, msg->type);

    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_SyncGuildMember(void *pData)
{
    const auto *msg = static_cast<ProtoMS_SyncGuildMember *>(pData);

    SPGUILD_MEMBER member(msg->member);

    GuildData::GetInstance()->SyncGuildMember(member, msg->type);

    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_AddSysNewMail(void* pData)
{
    auto msg = (ProtoMS_AddSysNewMail*)pData;
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_SyncGuildInfo(void *pData)
{
    const auto *msg = static_cast<ProtoMS_SyncGuildInfo *>(pData);

    SPGUILD guild(msg->guild);

    GuildData::GetInstance()->SyncGuildInfo(guild, msg->type);

    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_SyncMailInfoStatus(void* pData)
{
    auto msg = (ProtoMS_SyncMailInfoStatus*)pData;
    vector<MAIL_INFO> Vmail_info;
    mail::GetInstance()->GetMailInfo(msg->playerguid, Vmail_info);
    ProtoMS_SyncMailInfoStatus data;
    data.playerguid = msg->playerguid;
    for (int i = 0,j = 0; i < msg->num; i++){
        auto mailid = msg->info_status[i].mailid;
        auto it = find_if(Vmail_info.begin(), Vmail_info.end(), [&mailid](MAIL_INFO info) {return mailid == info.mail_id; });
        if (it == Vmail_info.end()) continue;
        if (it->status != msg->info_status[i].status) {
            ++data.num; 
            data.info_status[j].mailid = msg->info_status[i].mailid;
            data.info_status[j].status = msg->info_status[i].status;
            ++j;
        }
    }
    if (msg->num) {
        SendDataBySessionType(SESSION_TYPE_CS2DB, data);
    }
}

void SessionCS2MS::HandleMapServMsg_DelMailReq(void* pData)
{
    auto msg = (ProtoMS_DeleteMailReq*)pData;
    mail::GetInstance()->DeleteMail(msg->playerguid,msg->id);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_SyncGuildRelation(void *pData)
{
    const auto *msg = static_cast<ProtoMS_SyncGuildRelation *>(pData);
    GuildData::GetInstance()->SyncGuildRelation(msg->type, msg->my_guild_guid, msg->peer_guild_guid, msg->relation);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_SyncItemDynAttrs(void *pData)
{
    const auto *msg = static_cast<ProtoMS_SyncItemDynAttrs *>(pData);

    std::unique_ptr<ITEM_DYN_ATTRS_LIST> attrsList(msg->attrs_list);

    auto *user = UserMgr::GetInstance()->FindUser(msg->playerid);
    if (!user) {
        LOG_ERROR("sync item dynamic attributes failed. can't find user: %" PRIu64, msg->playerid);
        return;
    }

    user->SetItemDynAttrsList(msg->roleid, std::move(*attrsList), false);
}

void SessionCS2MS::HandleMapServMsg_SyncRoleDynAttrs(void* pData)
{
    const auto* msg = static_cast<ProtoMS_SyncRoleDynAttrs*>(pData);

    std::unique_ptr<ROLE_DYN_ATTRS_LIST> attrsList(msg->attrs_list);

    auto* user = UserMgr::GetInstance()->FindUser(msg->playerid);
    if (!user) {
        LOG_ERROR("sync role dynamic attributes failed. can't find user: %" PRIu64, msg->playerid);
        return;
    }

    if (!attrsList->empty())
        SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);

    user->SetRoleDynAttrsList(msg->roleid, std::move(*attrsList));
}

void SessionCS2MS::HandleMapServMsg_SynAuctionInfo(void* pData)
{
    auto* msg = static_cast<ProtoMS_SynAuctionItemInfo*>(pData);
    AuctionHouseMgr::GetInstance()->SynAuctionItemInfo(*msg);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_GetWantedListReq(void *pData)
{
    const auto *msg = static_cast<ProtoMS_GetWantedListReq *>(pData);

    if (WantedList::GetInstance()->HasRecvFromDB()) {

        ProtoMS_GetWantedListAck ack;
        ack.pwanted_list = &WantedList::GetInstance()->GetWantedList();

        SendPkg(&ack, sizeof(ack));
    }
    else {
        SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
    }
}

void SessionCS2MS::HandleMapServMsg_PostBountyReq(void *pData)
{
    const auto *msg = static_cast<ProtoMS_PostBountyReq *>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_CheckRoleExistenceReq(void *pData)
{
    const auto *msg = static_cast<ProtoMS_CheckRoleExistenceReq *>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_SaveGoodsIssueRecord(void *pData)
{
    const auto *msg = static_cast<ProtoMS_SaveGoodsIssueRecord *>(pData);
    const auto &record = msg->record;

    if (!record.issued) {

        User *user = nullptr;

        if (msg->player_guid != 0) {
            user = UserMgr::GetInstance()->FindUser(msg->player_guid);
        }
        else {
            user = UserMgr::GetInstance()->FindUserByRoleGUID(record.role_guid);
        }

        if (!user) {
            LOG_ERROR("user is NULL. player_guid: %llu, role_guid: %llu",
                      msg->player_guid, record.role_guid);
        }
        else {
            user->AddGoodsNotIssuedRecord(record.role_guid, record);
        }
    }

    if (!record.isPost) {

        User* user = nullptr;

        if (msg->player_guid != 0) {
            user = UserMgr::GetInstance()->FindUser(msg->player_guid);
        }
        else {
            user = UserMgr::GetInstance()->FindUserByRoleGUID(record.role_guid);
        }

        if (!user) {
            LOG_ERROR("user is NULL. player_guid: %llu, role_guid: %llu",
                msg->player_guid, record.role_guid);
        }
        else {
            user->AddGoodsNotPostRecord(record.role_guid, record);
        }
    }

    if (!SendDataBySessionType(SESSION_TYPE_CS2DB, *msg)) {
        LOG_ERROR("Send SaveGoodsIssueRecord to db failed. "
            "order_no: %s, role_guid: %llu, pay_type: %u, goods_id: %u, goods_num: %u, pay_amount: %u, issued: %u, isPost: %u",
            record.order_no, record.role_guid, record.pay_type, record.goods_id, record.goods_num, record.pay_amount,
            record.issued, record.isPost);
    }
}

void SessionCS2MS::HandleMapServMsg_GoodsIssuedNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_GoodsIssuedNtf *>(pData);

    auto *user = UserMgr::GetInstance()->FindUser(msg->player_guid);
    if (!user) {
        LOG_ERROR("user is NULL. player_guid: %llu", msg->player_guid);
    }
    else {
        user->RemoveGoodsNotIssuedRecords(msg->role_guid, msg->order_no, msg->num);
    }

    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_GoodsPostRecord(void* pData)
{
    const auto* msg = static_cast<ProtoMS_SyncGoodsPostRecord*>(pData);

    auto* user = UserMgr::GetInstance()->FindUser(msg->player_guid);
    if (!user) {
        LOG_ERROR("user is NULL. player_guid: %llu", msg->player_guid);
    }
    else {
        user->SyncGoodsPostRecords(msg->role_guid, msg->order_no, msg->num);
    }

    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_SetPlayerGender(void* pData)
{
    const auto* msg = static_cast<ProtoMS_SetPlayerGender*>(pData);
    auto* user = UserMgr::GetInstance()->FindUser(msg->guid);
    if (!user) {
        LOG_ERROR("user is NULL. player_guid: %llu", msg->guid);
    }
    else {
        user->SyncPlayerGender(msg->guid, msg->gender);
    }

    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_RebateMoneyUsedNtf(void* pData)
{
    auto* msg = static_cast<ProtoMS_RebateMoneyUsedNtf*>(pData);
    if (!msg) return;

    auto* user = UserMgr::GetInstance()->FindUser(msg->record.account_id);
    if (!user) {
        LOG_ERROR("user is NULL. player_guid: %llu", msg->record.account_id);
    }
    else {
        user->SetRebateMoneyUsedRecord(*msg);
    }
}

void SessionCS2MS::HandleMapServMsg_PlayerSetNameReq(void* pData)
{
    const auto* msg = static_cast<ProtoMS_PlayerSetNameReq*>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_ItemTip(void* pData)
{
    const auto* msg = static_cast<ProtoMS_ItemTip*>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_MonitorChatMsg(void* pData)
{
    const auto* msg = static_cast<ProtoMS_MonitorChatMsg*>(pData);
    MonitorChatMsgMgr::SendToPlatform(msg->info);
}

void SessionCS2MS::HandleMapServMsg_AddTitle(void* pData)
{
    const auto* msg = static_cast<ProtoMS_AddTitle*>(pData);
    Title::GetInstance()->AddTitle(msg->guid, msg->info);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_DelTitle(void* pData)
{
    const auto* msg = static_cast<ProtoMS_DelTitle*>(pData);
    Title::GetInstance()->DelTitle(msg->guid, msg->num, msg->id);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_ChangeTitleWearType(void* pData)
{
    const auto* msg = static_cast<ProtoMS_TitleWearType*>(pData);
    Title::GetInstance()->ChangeWearType(msg->guid, msg->id, msg->wearType);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_SyncTitleInfo(void* pData)
{
    const auto* msg = static_cast<ProtoMS_SyncTitleInfo*>(pData);
    Title::GetInstance()->UpdateTiltleInfo(msg->guid, msg->num, msg->info);
    Title::GetInstance()->SyncPlayerTitleInfo(msg->guid, msg->num, msg->info);
    //SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_AddActivationCodeTask(void* pData)
{
    const auto* msg = static_cast<ProtoMS_PlayerActivationCode*>(pData);
    RedemptionCodeMgr::SendToPlatform(msg->info);
}

void SessionCS2MS::HandleMapServMsg_AddPlayerProhibitChat(void* pData)
{
    const auto* msg = static_cast<ProtoMS_AddPlayerProhibitChat*>(pData);
    auto user = UserMgr::GetInstance()->FindUser(msg->userID);
    if (nullptr != user)
    {
        user->SetProhibitChat(msg->stamp);
    }
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_DelPlayerProhibitChat(void* pData)
{
    const auto* msg = static_cast<ProtoMS_DelPlayerProhibitChat*>(pData);
    auto user = UserMgr::GetInstance()->FindUser(msg->userID);
    if (nullptr != user)
    {
        user->SetProhibitChat(0);
    }
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleMapServMsg_RunGMCmd(void *pData)
{
    const auto *msg = static_cast<ProtoMS_RunGMCmd *>(pData);
    GMCmdHandler::HandleCmd(msg->cmd, msg->param);
}

void SessionCS2MS::HandleGateServMsg(uint16_t protoid, void *pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_GS_UPDATE_ONLINE_STATE, HandleGateServMsg_UpdateOnlineState)
    END_MSG_HANDLER()
}

void SessionCS2MS::HandleGateServMsg_UpdateOnlineState(void *pData)
{
    const auto *msg = static_cast<ProtoGS_UpdateOnlineState *>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}

void SessionCS2MS::HandleCenterServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_CS_GET_MAIL_ATTACHMENT_ACK, HandleCenterServMsg_GetMailAttachmentAck)
    END_MSG_HANDLER()
}

void SessionCS2MS::HandleCenterServMsg_GetMailAttachmentAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_GetMailAttachmentAck*>(pData);

    auto user = (*UserMgr::GetInstance())[msg->item.base_info.role];
    if (nullptr == user)
    {
        LOG_ERROR("user is NULL. roleid: %" PRIu64, msg->item.base_info.role);
        return;
    }
    // 置为未领取，再删除
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
    user->DelRoleItem(msg->item.base_info.role, msg->item.base_info.guid);
}

void SessionCS2MS::HandleMapServMsg_RunLuaHttp(void* pData)
{
    const auto* msg = static_cast<ProtoMS_CustomHttp*>(pData);
    auto* cfg = ConfigInfo::GetInstance();
    if (!cfg) return;

    auto url = cfg->m_sPlatformDomain + msg->cmd;

    ctpl::task_t task = [=](int) {
        const int HTTP_MSG_LENGTH = 10240;
        char data[HTTP_MSG_LENGTH] = { 0 };

        if (!ComposeHttpRequest( data, _countof(data), msg->param))
            return;

        auto* curl = curl_easy_init();
        if (!curl) {
            LOG_ERROR("curl_easy_init failed");
            return;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CURLWriteCallback);
        std::vector<char> resp;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        ParseResult(resp,msg->callBackFunc);
    };

    auto& threadPool = CenterServer::GetInstance()->GetThreadPool();
    threadPool.push(std::move(task));
}


bool SessionCS2MS::ComposeHttpRequest(char* buf, int bufsz,const char* custom)
{
    ConfigInfo* cfg = ConfigInfo::GetInstance();
    if (!cfg) return false;

    auto gameID = cfg->GetCurAgentId();
    auto regionID = cfg->GetCurAreaId();
    auto serverID = regionID * 1000 + cfg->GetCurAreaServerId();

    sprintf_s(buf, bufsz, "gameId=%u&regionId=%u&serverId=%u&%s",
        gameID, regionID, serverID, custom);

    return true;
}

size_t SessionCS2MS::CURLWriteCallback(void* data, size_t size, size_t nmemb, void* userp)
{
    auto len = size * nmemb;

    auto* resp = static_cast<std::vector<char> *>(userp);

    auto oldSize = resp->size();
    auto newSize = oldSize + len + 1;

    resp->resize(newSize);

    memcpy(resp->data() + oldSize, data, len);

    return len;

}


void SessionCS2MS::ParseResult(std::vector<char>& resp, const char* callBackFunc)
{
    if (resp.empty()) return;

    const char* raw = resp.data();
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(raw, raw + strlen(raw), root)) {
        LOG_ERROR("parse failed, raw: %s", raw);
        return;
    }

    if (!root.isMember("code")) {
        LOG_ERROR("No code member, raw: %s", raw);
        return;
    }
    ProtoCS_CustomHttpAck data;
    strcpy_s(data.func, _countof(data.func), callBackFunc);
    strcpy_s(data.data, _countof(data.data), raw);
    callable_t func = [=] {
        
        SendDataBySessionType(SESSION_TYPE_CS2MS, data);
    };
    auto& queue = CenterServer::GetInstance()->GetCallableQueue();
    queue.push(func);
}