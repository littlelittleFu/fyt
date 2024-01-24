#include "stdafx.h"
#include "SessionGS2CL.h"
#include "ILogHelper.h"
#include "ITimeHelper.h"
#include "CNetManager.h"
#include "SessionFactory.h"
#include "SessionContextMgr.h"
#include "ProtoGS.h"
#include "ProtoClient.h"
#include "ProtoClient2.h"
#include "ProtoClient3.h"
#include <Tools/StringHelper.h>
#include "SessionManager.h"
#include "GateServer.h"


SessionGS2CL::SessionGS2CL()
{
	m_spSessionContext = std::make_shared<SessionContext>();
	m_spSessionContext->nSessionID = GetID();

	SessionContextMgr::GetInstance()->AddSessionContext(m_spSessionContext);
}

SessionGS2CL::~SessionGS2CL()
{
}

void SessionGS2CL::OnEstablish(SOCKET _Socket)
{
	LOG_NORMAL("Connection established. Remote host: %s:%u, session id: %u",
		GetRemoteIp().c_str(), GetRemotePort(), GetID());
	Session::OnEstablish(_Socket);
}

void SessionGS2CL::OnLost()
{
	uint32_t nSessionID = GetID();
	LOG_WARN("Lost connection with remote host: %s:%u, session id: %u", GetRemoteIp().c_str(), GetRemotePort(), nSessionID);

	if (!IsLoggedIn()) {        // 包括未登录、已登录主动登出
		SessionContextMgr::GetInstance()->DelSessionContext(nSessionID);
		return;
	}

	SetOnlineState(online_state_disconnected);
	SendUpdateOnlineStateToLS(GetRoleGUID(), GetToken(), (uint8_t)online_state_disconnected);
	StartReserveContextTimer();   // 已登录情况下断开连接保留玩家数据一段时间
}

void SessionGS2CL::StartReserveContextTimer()
{
    auto &timerID = m_spSessionContext->nReserveContextTimerID;
    if (timerID) return;

    const auto *cfg = ConfigInfo::GetInstance();
    if (!cfg) return;

    auto sessid = m_spSessionContext->nSessionID;
    auto token = m_spSessionContext->nToken;

    auto callback = [=](const TimerData &){

        SessionGS2CL::SendLogoutReqToLS(sessid, token, 0);
        SessionContextMgr::GetInstance()->DelSessionContext(sessid);
    };

    timerID = ITimeHelper::GetInstance()->AddTimer(S2MS(cfg->m_nSessCtxRsvTime), false, callback);
}

void SessionGS2CL::StopReserveContextTimer(SPSessionContext &context)
{
    if (context && context->nReserveContextTimerID) {
        ITimeHelper::GetInstance()->RemoveTimer(context->nReserveContextTimerID);
        context->nReserveContextTimerID = 0;
    }
}

void SessionGS2CL::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    MsgCostStat::GetInstance()->BeginHandleMsg();

	switch (moduleid) {
		case MODULE_TYPE_CLIENT:
			HandleClientMsg(protoid, _pData);
			break;

        case MODULE_TYPE_CLIENT2:
            HandleClient2Msg(protoid, _pData);
            break;

		case MODULE_TYPE_CLIENT3:
			HandleClient3Msg(protoid, _pData);
			break;

		default:
			LOG_WARN("Unhandled moduleid: %u. Remote host: %s:%u, session id: %u",
				moduleid, GetRemoteIp().c_str(), GetRemotePort(), GetID());
			break;
	}

    MsgCostStat::GetInstance()->EndHandleMsg(moduleid, protoid);
}

void SessionGS2CL::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode: %u, remote host: %s:%u, session id: %u",
		_ErrorCode, GetRemoteIp().c_str(), GetRemotePort(), GetID());
}

#define HEART_BEAT_INTERVAL		30000
void SessionGS2CL::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);

	if (m_Socket.IsConnected()) {
		m_nHeartBeatTimeOut += _Delta;
		if (m_nHeartBeatTimeOut >= HEART_BEAT_INTERVAL * 3) {
			/*CLogger::GetInstance()->LogWarning("[%s:%d] 心跳超时。HeartBeat=%d ID=%%d", FUNC_LINE, m_nHeartBeatTimeOut,GetID());
			DoClose();*/
			DoClose();
			OnLost();
		}

		m_nHeartBeatPulse += _Delta;
		if (m_nHeartBeatPulse >= HEART_BEAT_INTERVAL) {
			m_nHeartBeatPulse = 0;
			DoHeartBeat();
		}
	}
}

void SessionGS2CL::DoHeartBeat()
{
}

void SessionGS2CL::HandleClientMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_CLIENT_CONN_REQ, HandleClientMsg_ConnReq)
        HANDLE_MSG(PROTO_CLIENT_HEART_BEAT_REQ, HandleClientMsg_HeartBeatReq)
        HANDLE_MSG(PROTO_CLIENT_LOGIN_REQ, HandleClientMsg_LoginReq)
        HANDLE_MSG(PROTO_CLIENT_THIRD_LOGIN_REQ, HandleClientMsg_ThirdLoginReq)
        HANDLE_MSG(PROTO_CLIENT_LOGOUT_REQ, HandleClientMsg_LogoutReq)
        HANDLE_MSG(PROTO_CLIENT_GET_ROLE_LIST_REQ, HandleClientMsg_GetRoleListReq)
        HANDLE_MSG(PROTO_CLIENT_CREATE_ROLE_REQ, HandleClientMsg_CreateRoleReq)
		HANDLE_MSG(PROTO_CLIENT_CREATE_ROLE_REQ_EX, HandleClientMsg_CreateRoleReqEx)
        HANDLE_MSG(PROTO_CLIENT_DEL_ROLE_REQ, HandleClientMsg_DeleteRoleReq)
		HANDLE_MSG(PROTO_CLIENT_RECOVER_ROLE_REQ, HandleClientMsg_RestoreRoleReq)
        HANDLE_MSG(PROTO_CLIENT_RELOGIN_REQ, HandleClientMsg_ReloginReq)
    END_MSG_HANDLER()
}

void SessionGS2CL::HandleClient2Msg(uint16_t protoid, void *pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_CLIENT2_PRIVATE_CHAT_NTF, HandleClient2Msg_PrivateChatNtf)
        HANDLE_MSG(PROTO_CLIENT2_RELATION_CHAT_REQ, HandleClient2Msg_RelationChatReq)
        HANDLE_MSG(PROTO_CLIENT2_SPEAKER_MSG_REQ, HandleClient2Msg_SpeakerMsgReq)
        HANDLE_MSG(PROTO_CLIENT2_TEAM_OPERATION, HandleClient2Msg_Teamoperation)
        HANDLE_MSG(PROTO_CLIENT2_TEAM_INVITE, HandleClient2Msg_TeamInvite)
        HANDLE_MSG(PROTO_CLIENT2_TEAM_INVITE_RSP, HandleClient2Msg_TeamInviteRsp)
        HANDLE_MSG(PROTO_CLIENT2_TEAM_LEAVE_REQ, HandleClient2Msg_TeamLeaveReq)
        HANDLE_MSG(PROTO_CLIENT2_TEAM_KICK_REQ, HandleClient2Msg_TeamKickReq)
		HANDLE_MSG(PROTO_CLIENT2_TEAM_JOIN, HandleClient2Msg_TeamJoin)
		HANDLE_MSG(PROTO_CLIENT2_TEAM_JOIN_RSP, HandleClient2Msg_TeamJoinRsp)
        HANDLE_MSG(PROTO_CLIENT2_GET_FAMILY_INFO_REQ, HandleClient2Msg_GetFamilyInfoReq)
		HANDLE_MSG(PROTO_CLIENT2_TOPLIST_REQ, HandleClient2Msg_TopListReq)

        HANDLE_MSG(PROTO_CLIENT2_FAMILY_JOIN_REQ, HandleClient2Msg_FamilyJoinReq)
        HANDLE_MSG(PROTO_CLIENT2_CANCEL_FAMILY_JOIN_REQ, HandleClient2Msg_CancelFamilyJoinReq)
        HANDLE_MSG(PROTO_CLIENT2_FAMILY_JOIN_ACK, HandleClient2Msg_FamilyJoinAck)
        HANDLE_MSG(PROTO_CLIENT2_FAMILY_TITLE_AWARD_REQ, HandleClient2Msg_FamilyTitleAwardReq)
        HANDLE_MSG(PROTO_CLIENT2_FAMILY_EXPELL_REQ, HandleClient2Msg_FamilyExpellReq)
        HANDLE_MSG(PROTO_CLIENT2_FAMILY_NOTICE_EDIT_REQ, HandleClient2Msg_FamilyNoticeEditReq)
		HANDLE_MSG(PROTO_CLIENT2_MAIL_LIST_REQ, HandleClient2Msg_MailListReq)
		HANDLE_MSG(PROTO_CLIENT2_MAIL_OPEN_REQ, HandleClient2Msg_MailOpenReq)
		HANDLE_MSG(PROTO_CLIENT2_MAIL_ATTACHMENT_GET_REQ, HandleClient2Msg_MailAttachmentGetReq)
		HANDLE_MSG(PROTO_CLIENT2_MAIL_DEL_REQ, HandleClient2Msg_MailDelReq)  
        HANDLE_MSG(PROTO_CLIENT2_FRIEND_ADD_REQ, HandleClient2Msg_FriendAddReq)
        HANDLE_MSG(PROTO_CLIENT2_FAMILY_LEAVE_OR_LAST_MSG_REQ, HandleClient2Msg_FamilyLeaveOrLastMsgReq)
        HANDLE_MSG(PROTO_CLIENT2_FAMILY_DESTROY_REQ, HandleClient2Msg_FamilyDestroyReq)

	END_MSG_HANDLER()
}

void SessionGS2CL::HandleClient3Msg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_CLIENT3_RELIVE_REQ, HandleClient3Msg_ReliveReq)
        HANDLE_MSG(PROTO_CLIENT3_EXIT_GS_REQ, HandleClient3Msg_ExitGSReq)
        HANDLE_MSG(PROTO_CLIENT3_ENTER_GS_REQ, HandleClient3Msg_EnterGSReq)
        HANDLE_MSG(PROTO_CLIENT3_MOVE_REQ, HandleClient3Msg_MoveReq)
        HANDLE_MSG(PROTO_CLIENT3_TURN_REQ, HandleClient3Msg_TurnReq)
        HANDLE_MSG(PROTO_CLIENT3_SPELL_TARGET, HandleClient3Msg_SpellTarget)
        HANDLE_MSG(PROTO_CLIENT3_SPELL_GRID, HandleClient3Msg_SpellGrid)
        HANDLE_MSG(PROTO_CLIENT3_SKILL_SWITCH, HandleClient3Msg_SkillSwitch)
        HANDLE_MSG(PROTO_CLIENT3_ITEM_APPLY, HandleClient3Msg_ItemApply)
        HANDLE_MSG(PROTO_CLIENT3_ITEM_PICK_UP, HandleClient3Msg_ItemPickUp)
        HANDLE_MSG(PROTO_CLIENT3_ITEM_DROP, HandleClient3Msg_ItemDrop)
		HANDLE_MSG(PROTO_CLIENT3_ITEM_ARRANGE, HandleClient3Msg_ItemArrange)
        HANDLE_MSG(PROTO_CLIENT3_ITEM_MOVE, HandleClient3Msg_ItemMove)
		HANDLE_MSG(PROTO_CLIENT3_ITEM_SPLIT, HandleClient3Msg_ItemSplit)
        HANDLE_MSG(PROTO_CLIENT3_RUN_SERV_SCRIPT_REQ, HandleClient3Msg_RunServScriptReq)
        HANDLE_MSG(PROTO_CLIENT3_TRADE_MALL_BUY, HandleClient3Msg_TradeMallBuy)
        HANDLE_MSG(PROTO_CLIENT3_TRADE_MALL_LIST_REQ, HandleClient3Msg_TradeMallListReq)
        HANDLE_MSG(PROTO_CLIENT3_NPC_SELECT, HandleClient3Msg_NpcSelect)
        HANDLE_MSG(PROTO_CLIENT3_NPC_TALK_REQ, HandleClient3Msg_NpcTalkReq)
        HANDLE_MSG(PROTO_CLIENT3_TRADE_NPC_BUY, HandleClient3Msg_TradeNpcBuy)
        HANDLE_MSG(PROTO_CLIENT3_ATK_MODE_REQ, HandleClient3Msg_AtkModeReq)
        HANDLE_MSG(PROTO_CLIENT3_QUEST_QUERY_CAN_ACCEPT, HandleClient3Msg_QuestQueryCanAccept)
        HANDLE_MSG(PROTO_CLIENT3_QUEST_ACCEPT, HandleClient3Msg_QuestAccept)
        HANDLE_MSG(PROTO_CLIENT3_QUEST_DROP, HandleClient3Msg_QuestDrop)
        HANDLE_MSG(PROTO_CLIENT3_QUEST_ACCOMPLISH, HandleClient3Msg_QuestAccomplish)
        HANDLE_MSG(PROTO_CLIENT3_PLAYER_SWITCH_REQ, HandleClient3Msg_PlayerSwitchReq)
        HANDLE_MSG(PROTO_CLIENT3_GET_ARROUND_TEAM_REQ, HandleClient3Msg_GetAroundTeamReq)
        HANDLE_MSG(PROTO_CLIENT3_PLAYER_QUERY, HandleClient3Msg_PlayerQuery)
        HANDLE_MSG(PROTO_CLIENT3_QUICK_BAR_SET, HandleClient3Msg_QuickBarSet)
		HANDLE_MSG(PROTO_CLIENT3_GOLD_TAKE, HandleClient3Msg_GoldTake)
		HANDLE_MSG(PROTO_CLIENT3_GOLD_DEPOSIT, HandleClient3Msg_GoldDeposit)
		HANDLE_MSG(PROTO_CLIENT3_GM_COMMAND_REQ, HandleClient3Msg_GMCommandReq)
		HANDLE_MSG(PROTO_CLIENT3_RECORDS_MIN_REQ, HandleClient3Msg_RecordsMineReq)
		HANDLE_MSG(PROTO_CLIENT3_ROLE_CUST_VAR_REQ, HandleClient3Msg_RoleCustVarReq)
		HANDLE_MSG(PROTO_CLIENT3_DELEGATE_MINE_REQ, HandleClient3Msg_DelegateMineReq)
		HANDLE_MSG(PROTO_CLIENT3_DELEGATE_SELL_LIST_REQ, HandleClient3Msg_DelegateSellListReq)
		HANDLE_MSG(PROTO_CLIENT3_DELEGATE_BUY_LIST_REQ, HandleClient3Msg_DelegateBuyListReq)
		HANDLE_MSG(PROTO_CLIENT3_DELEGATE_CANCEL, HandleClient3Msg_DelegateCancelReq)
		HANDLE_MSG(PROTO_CLIENT3_DELEGATE_SELL_CMD, HandleClient3Msg_DelegateSellCmd)
		HANDLE_MSG(PROTO_CLIENT3_DELEGATE_BUY_CMD, HandleClient3Msg_DelegateBuyCmd)
		HANDLE_MSG(PROTO_CLIENT3_MARKET_SELL_CMD, HandleClient3Msg_MarketSellCmd)
		HANDLE_MSG(PROTO_CLIENT3_MARKET_BUY_CMD, HandleClient3Msg_MarketBuyCmd)
		HANDLE_MSG(PROTO_CLIENT3_QUERY_EX, HandleClient3Msg_QueryEx)
		HANDLE_MSG(PROTO_CLIENT3_JUMP_MAP_REQ, HandleClient3Msg_JumpMapReq)
		HANDLE_MSG(PROTO_CLIENT3_GET_NPC_POS_REQ, HandleClient3Msg_GetNpcPosReq)
        HANDLE_MSG(PROTO_CLIENT3_START_DIG_REQ, HandleClient3Msg_StartDigReq)
        HANDLE_MSG(PROTO_CLIENT3_RANGE_PICKUP, HandleClient3Msg_RangePickup)
		HANDLE_MSG(PROTO_CLIENT3_SYNC_CLIENT_BASE_SETTING, HandleClient3Msg_SyncClientBaseSetting)
        HANDLE_MSG(PROTO_CLIENT3_VERIFY_BUY_ITEM_INFO_REQ, HandleClient3Msg_VerifyBuyItemInfoReq)
        HANDLE_MSG(PROTO_CLIENT3_ITEM_REFRESH_REQ, HandleClient3Msg_ItemRefreshReq)
		HANDLE_MSG(PROTO_CLIENT3_ITEM_TIP, HandleClient3Msg_ItemTip)
		HANDLE_MSG(PROTO_CLIENT3_TITLE_REMOVE, HandleClient3Msg_TitleRemove)
		HANDLE_MSG(PROTO_CLIENT3_TITLE_APPLY, HandleClient3Msg_TitleApply)
		HANDLE_MSG(PROTO_CLIENT3_TITLE_UNAPPLY, HandleClient3Msg_TitleUnApply)
        HANDLE_MSG(PROTO_CLIENT3_SET_AUTO_MODE_ACK, HandleClient3Msg_SetAutoModeAck)
		HANDLE_MSG(PROTO_CLIENT3_TITLE_GET_LIST_REQ, HandleClient3Msg_TitleGetListReq)
		HANDLE_MSG(PROTO_CLIENT3_GOODS_POST_RECORD_ACK, HandleClient3Msg_GoodsPostRecordAck)

    END_MSG_HANDLER()
}

void SessionGS2CL::HandleClient3Msg_ItemMove(void* pData)
{
	ProtoClient3_ItemMove* move = (ProtoClient3_ItemMove*)pData;

	ProtoGS_ItemMove gsmove;
	gsmove.item_guid = move->item_guid;
	gsmove.dest_site = move->dest_site;
	gsmove.token = GetToken();
	if (!SendDataBySessionType(SESSION_TYPE_GS2MS, gsmove))      // 发送到登录服务器
	{
		LOG_WARN("HandleClient3Msg_ItemMove: ");
		return;
	}
}

void SessionGS2CL::HandleClient3Msg_ItemSplit(void* pData)
{
	ProtoClient3_ItemSplit* split = (ProtoClient3_ItemSplit*)pData;

	ProtoGS_ItemSplit gssplit;
	gssplit.item_guid = split->item_guid;
	gssplit.item_amount = split->item_amount;
	gssplit.dest_site = split->dest_site;
	gssplit.token = GetToken();
	if (!SendDataBySessionType(SESSION_TYPE_GS2MS, gssplit))
	{
		LOG_WARN("HandleClient3Msg_ItemSplit: ");
		return;
	}
}

void SessionGS2CL::HandleClient3Msg_RunServScriptReq(void *pData)
{
    auto pRunServScript = (ProtoClient3_RunServScriptReq *)pData;

    ProtoGS_RunServScriptReq runServScript;
    runServScript.sessionid = GetID();
    runServScript.token = GetToken();
    runServScript.playerid = GetPlayerGUID();
    runServScript.form_count = pRunServScript->form_count;
    CopyArray(runServScript.script_name, pRunServScript->script_name);       // 必须采用内存拷贝，因为已加密为二进制
    CopyArray(runServScript.function_name, pRunServScript->function_name);
    runServScript.num = pRunServScript->num;
    CopyArray(runServScript.info, pRunServScript->info);

    SendDataBySessionType(SESSION_TYPE_GS2MS, runServScript);
}

void SessionGS2CL::HandleClient3Msg_ItemApply(void* pData)
{
	ProtoClient3_ItemApply* apply = (ProtoClient3_ItemApply*)pData;

	ProtoGS_ItemApply gsapply;
	gsapply.sessid = GetID();
	gsapply.item_guid = apply->item_guid;
	gsapply.num = apply->num;
	gsapply.token = GetToken();
    gsapply.role_guid = GetRoleGUID();
	if (!SendDataBySessionType(SESSION_TYPE_GS2MS, gsapply))      // 发送到登录服务器
	{
		LOG_WARN("ProtoClient3_ItemApply: ");
		return;
	}
}

void SessionGS2CL::HandleClient3Msg_ItemPickUp(void* pData)
{
	ProtoClient3_ItemPickUp* pickup = (ProtoClient3_ItemPickUp*)pData;

	ProtoGS_ItemPickUp gsup;
	gsup.sessid = GetID();
	gsup.token = GetToken();
	if (!SendDataBySessionType(SESSION_TYPE_GS2MS, gsup))      // 发送到登录服务器
	{
		LOG_WARN("ProtoClient3_ItemDrop: ");
		return;
	}

}

void SessionGS2CL::HandleClient3Msg_ItemDrop(void* pData)
{
	ProtoClient3_ItemDrop* drop = (ProtoClient3_ItemDrop*)pData;

	ProtoGS_ItemDrop gsdrop;
	gsdrop.sessid = GetID();
	gsdrop.item_guid = drop->item_guid;
	gsdrop.token = GetToken();
	if (!SendDataBySessionType(SESSION_TYPE_GS2MS, gsdrop))      // 发送到登录服务器
	{
		LOG_WARN("ProtoClient3_ItemDrop: ");
		return;
	}

}

void SessionGS2CL::HandleClient3Msg_ItemArrange(void* pData)
{
	ProtoClient3_ItemArrange* arrange = (ProtoClient3_ItemArrange*)pData;

	ProtoGS_ItemArrange gsarrange;
	gsarrange.sessid = GetID();
	gsarrange.type = arrange->type;
	gsarrange.token = GetToken();
	if (!SendDataBySessionType(SESSION_TYPE_GS2MS, gsarrange))      // 发送到登录服务器
	{
		LOG_WARN("ProtoClient3_ItemArrange: ");
		return;
	}
}

void SessionGS2CL::HandleClient3Msg_TradeMallBuy(void* pData)
{
	auto req1 = (ProtoClient3_TradeMallBuy*)pData;
	ProtoGS_TradeMallBuy req2;
	req2.sessionid = GetID();
	req2.token = GetToken();
	req2.item_index = req1->item_index;
	req2.item_amount = req1->item_amount;
	SendDataBySessionType(SESSION_TYPE_GS2MS, req2);
}

void SessionGS2CL::HandleClient3Msg_TradeMallListReq(void* pData)
{
	auto req1 = (ProtoClient3_TradeMallListReq*)pData;
	ProtoGS_TradeMallListReq req2;
	req2.sessionid = GetID();
	req2.token = GetToken();
	req2.page_id = req1->page_id;
	SendDataBySessionType(SESSION_TYPE_GS2MS, req2);
}

void SessionGS2CL::HandleClientMsg_ConnReq(void* pData)
{
	ProtoClient_ConnAck connAck;
    connAck.overload = SessionContextMgr::GetInstance()->GetOnlineNum();
	SendPkg(&connAck, sizeof(connAck));
}

void SessionGS2CL::HandleClientMsg_HeartBeatReq(void* pData)
{
	OnHeartBeat();

	ProtoClient_HeartBeatAck heartBeatAck;
	SendPkg(&heartBeatAck, sizeof(heartBeatAck));
}

bool SessionGS2CL::MaxClientReached()
{
    const auto &maxClientNum = ConfigInfo::GetInstance()->m_nMaxClientNum;
    if (maxClientNum == 0) return false;    // 不限制

    auto curClientNum = SessionContextMgr::GetInstance()->GetOnlineNum();
    return (curClientNum > maxClientNum);
}

bool SessionGS2CL::IsGMAccount(uint64_t userid)
{
    return (userid == 18446744073709551615) ||
           (userid == 18446744073709551614);
}

void SessionGS2CL::HandleClientMsg_LoginReq(void* pData)
{
	ProtoClient_LoginReq* pLoginReq = (ProtoClient_LoginReq*)pData;

	// 接收到关服GM后无法登录
	if (GateServer::GetInstance()->IsCloseServerState()) {
		SendLoginAckToClient(ERR_SYSTEM, EMSG_CLOSE, 0);
		return;
	}

	ProtoGS_LoginReq loginReq;
	loginReq.clsessid = GetID();
	strcpy_s(loginReq.username, _countof(loginReq.username), pLoginReq->username);
	loginReq.ip = Utility::IpStr2UInt(GetRemoteIp());// pLoginReq->ip;
	memcpy(loginReq.password, pLoginReq->password, pLoginReq->pwdlen);  // pLoginReq->password不一定以0结尾，不能用strcpy_s
	strcpy_s(loginReq.hwid, _countof(loginReq.hwid), pLoginReq->hwid);

	if (!SendDataBySessionType(SESSION_TYPE_GS2LS, loginReq)) {
		SendLoginAckToClient(ERR_SYSTEM, EMSG_GS2LS_CONN_ERROR, 0);
		return;
	}
}

void SessionGS2CL::HandleClientMsg_ThirdLoginReq(void *pData)
{
    const auto *msg = static_cast<ProtoClient_ThirdLoginReq *>(pData);

	// 接收到关服GM后无法登录
	if (GateServer::GetInstance()->IsCloseServerState()) {
		SendLoginAckToClient(ERR_SYSTEM, EMSG_CLOSE, 0);
		return;
	}

    ProtoGS_ThirdLoginReq data;

    data.sessionid = GetID();

    ASSIGN_STRING_MEMBER(channel);
    ASSIGN_MEMBER(gameid);
    ASSIGN_STRING_MEMBER(token);
    ASSIGN_STRING_MEMBER(user_name);
    ASSIGN_MEMBER(login_ip);
    ASSIGN_STRING_MEMBER(hwid);

	data.login_ip = Utility::IpStr2UInt(GetRemoteIp());
    if (!SendDataBySessionType(SESSION_TYPE_GS2LS, data)) {
        SendLoginAckToClient(ERR_SYSTEM, EMSG_GS2LS_CONN_ERROR, 0);
        return;
    }
}

void SessionGS2CL::HandleClientMsg_LogoutReq(void* pData)
{
	ProtoClient_LogoutReq* pLogoutReq = (ProtoClient_LogoutReq*)pData;

    SetOnlineState(online_state_not_logged_in);

    SendLogoutReqToLS(GetID(), GetToken(), pLogoutReq->info);
}

void SessionGS2CL::HandleClientMsg_ReloginReq(void* pData)
{
    const auto *msg = static_cast<ProtoClient_ReloginReq *>(pData);

	// 接收到关服GM后无法登录
	if (GateServer::GetInstance()->IsCloseServerState()) {
		SendLoginAckToClient(ERR_SYSTEM, EMSG_CLOSE, 0);
		return;
	}

    ProtoGS_ReloginReq data;
    data.cl2gs_sessid = GetID();

	data.ip = Utility::IpStr2UInt(GetRemoteIp());
	//strcpy_s(data.hwid, _countof(data.hwid), msg->hwid);
    ASSIGN_MEMBER(player_guid);
    ASSIGN_MEMBER(role_guid);
    ASSIGN_STRING_MEMBER(randkey);

    SendDataBySessionType(SESSION_TYPE_GS2LS, data);
}

void SessionGS2CL::HandleClientMsg_GetRoleListReq(void* pData)
{
	ProtoClient_GetRoleListReq* pGetRoleListReq = (ProtoClient_GetRoleListReq*)pData;

	ProtoGS_GetRoleListReq getRoleListReq;
	getRoleListReq.sessionid = GetID();
	getRoleListReq.token = GetToken();
	getRoleListReq.playerid = GetPlayerGUID();

	if (!SendDataBySessionType(SESSION_TYPE_GS2CS, getRoleListReq)) {
		SendGetRoleListAckToClient(ERR_SYSTEM, EMSG_GS2CS_CONN_ERROR);
	}
}

void SessionGS2CL::HandleClientMsg_CreateRoleReq(void* pData)
{
	ProtoClient_CreateRoleReq* pCreateRoleReq = (ProtoClient_CreateRoleReq*)pData;

	if (!IsLoggedIn()) {
		SendCreateRoleAckToClient(ERR_NOUSERDATA, EMSG_NOT_LOGGED_IN);
		return;
	}

	ProtoGS_CreateRoleReq createRoleReq;
	createRoleReq.sessionid = GetID();
	createRoleReq.token = GetToken();
	createRoleReq.playerid = GetPlayerGUID();
	createRoleReq.createrole = pCreateRoleReq->createrole;

	if (!SendDataBySessionType(SESSION_TYPE_GS2CS, createRoleReq)) {
		SendCreateRoleAckToClient(ERR_SYSTEM, EMSG_GS2CS_CONN_ERROR);
	}
}

void SessionGS2CL::HandleClientMsg_CreateRoleReqEx(void* pData)
{
	ProtoClient_CreateRoleReqEx* pCreateRoleReq = (ProtoClient_CreateRoleReqEx*)pData;

	if (!IsLoggedIn()) {
		SendCreateRoleAckToClient(ERR_NOUSERDATA, EMSG_NOT_LOGGED_IN);
		return;
	}
	ProtoGS_CreateRoleReq createRoleReq;
	createRoleReq.sessionid = GetID();
	createRoleReq.token = GetToken();
	createRoleReq.playerid = GetPlayerGUID();
	createRoleReq.createrole = pCreateRoleReq->createrole;
	createRoleReq.digCode = pCreateRoleReq->digCode;

	if (!SendDataBySessionType(SESSION_TYPE_GS2CS, createRoleReq)) {
		SendCreateRoleAckToClient(ERR_SYSTEM, EMSG_GS2CS_CONN_ERROR);
	}
}

void SessionGS2CL::HandleClientMsg_DeleteRoleReq(void* pData)
{
	auto pDeleteRoleReq = (ProtoClient_DeleteRoleReq*)pData;

	if (!IsLoggedIn()) {
		SendDeleteRoleAckToClient(pDeleteRoleReq->guid, ERR_NOUSERDATA, EMSG_NOT_LOGGED_IN);
		return;
	}

	ProtoGS_DeleteRoleReq deleteRoleReq;
	deleteRoleReq.sessionid = GetID();
	deleteRoleReq.token = GetToken();
	deleteRoleReq.playerid = GetPlayerGUID();
	deleteRoleReq.roleid = pDeleteRoleReq->guid;

	if (!SendDataBySessionType(SESSION_TYPE_GS2CS, deleteRoleReq)) {
		SendDeleteRoleAckToClient(pDeleteRoleReq->guid, ERR_SYSTEM, EMSG_GS2CS_CONN_ERROR);
	}
}

void SessionGS2CL::HandleClientMsg_RestoreRoleReq(void* pData)
{
	auto pRestoreRoleReq = (ProtoClient_RestoreRoleReq*)pData;

	if (!IsLoggedIn()) {
		SendRestoreRoleAckToClient(pRestoreRoleReq->guid, ERR_NOUSERDATA, EMSG_NOT_LOGGED_IN, ROLE_BRIEF_INFO());
		return;
	}

	ProtoGS_RestoreRoleReq restoreRoleReq;
	restoreRoleReq.sessionid = GetID();
	restoreRoleReq.token = GetToken();
	restoreRoleReq.playerid = GetPlayerGUID();
	restoreRoleReq.roleid = pRestoreRoleReq->guid;

	if (!SendDataBySessionType(SESSION_TYPE_GS2CS, restoreRoleReq)) {
		SendRestoreRoleAckToClient(pRestoreRoleReq->guid, ERR_SYSTEM, EMSG_GS2CS_CONN_ERROR, ROLE_BRIEF_INFO());
	}
}

void SessionGS2CL::HandleClient3Msg_MoveReq(void* pData)
{
	auto pMoveReq = (ProtoClient3_MoveReq*)pData;

	ProtoGS_MoveReq moveReq;
    moveReq.clsessid = m_spSessionContext->nSessionID;
	moveReq.role_guid = pMoveReq->role_guid;
	moveReq.type = pMoveReq->type;
	moveReq.dst_x = pMoveReq->dst_x;
	moveReq.dst_y = pMoveReq->dst_y;
	moveReq.idx = pMoveReq->idx;
	moveReq.movetime = GetTimeStampMillisecond2();
	if (!SendDataBySessionType(SESSION_TYPE_GS2MS, moveReq)) {
		SendMoveAckToClient(pMoveReq->role_guid, move_result_fail, pMoveReq->idx);
	}
}

void SessionGS2CL::HandleClient2Msg_PrivateChatNtf(void *pData)
{
    auto pPrivateChatNtf = (ProtoClient2_PrivateChatNtf *)pData;

    LOG_TRACE("[CHAT] type: %u, role_name: %s, message: %s",
        pPrivateChatNtf->type, pPrivateChatNtf->chat_message.role_name, pPrivateChatNtf->chat_message.message);

    ProtoGS_PrivateChatNtf privateChatNtf;
    privateChatNtf.token = GetToken();
    privateChatNtf.type = pPrivateChatNtf->type;
    privateChatNtf.chat_message = pPrivateChatNtf->chat_message;

    SendDataBySessionType(SESSION_TYPE_GS2MS, privateChatNtf);
}

void SessionGS2CL::HandleClient2Msg_RelationChatReq(void *pData)
{
    auto pRelationChatReq = (ProtoClient2_RelationChatReq *)pData;

    LOG_TRACE("[CHAT] type: %u, message: %s", pRelationChatReq->type, pRelationChatReq->message);

    ProtoGS_RelationChatReq relationChatReq;
    relationChatReq.token = GetToken();
    relationChatReq.type = pRelationChatReq->type;
    strcpy_s(relationChatReq.message, _countof(relationChatReq.message), pRelationChatReq->message);

    SendDataBySessionType(SESSION_TYPE_GS2MS, relationChatReq);
}

void SessionGS2CL::HandleClient2Msg_SpeakerMsgReq(void *pData)
{
    auto pSpeakerMsgReq = (ProtoClient2_SpeakerMsgReq *)pData;

    LOG_TRACE("[CHAT] speaker msg: %s", pSpeakerMsgReq->msg);

    ProtoGS_SpeakerMsgReq speakerMsgReq;
    speakerMsgReq.token = GetToken();
    strcpy_s(speakerMsgReq.msg, _countof(speakerMsgReq.msg), pSpeakerMsgReq->msg);

    SendDataBySessionType(SESSION_TYPE_GS2MS, speakerMsgReq);
}

void SessionGS2CL::HandleClient2Msg_Teamoperation(void* pData)
{
	auto pteam = (ProtoClient2_Teamoperation*)pData;

	LOG_TRACE("@@@@@@@@@@[TEAM] team msg: %s", pteam->content);
	ProtoGS_Teamoperation TeamoperationReq;
	TeamoperationReq.token = GetToken();
	TeamoperationReq.operation = pteam->operation;
	strcpy_s(TeamoperationReq.content, _countof(TeamoperationReq.content), pteam->content);

	SendDataBySessionType(SESSION_TYPE_GS2MS, TeamoperationReq);
	
}

void SessionGS2CL::HandleClient2Msg_TeamInvite(void* pData)
{
	auto pteam = (ProtoClient2_TeamInvite*)pData;
	LOG_TRACE("@@@@@@@@@@[TEAM] invitee_name : %s", pteam->invitee_name);
	ProtoGS_TeamInvite TeamInviteReq;
	TeamInviteReq.token = GetToken();
	strcpy_s(TeamInviteReq.invitee_name, _countof(TeamInviteReq.invitee_name), pteam->invitee_name);
	SendDataBySessionType(SESSION_TYPE_GS2MS, TeamInviteReq);
}

void SessionGS2CL::HandleClient2Msg_TeamInviteRsp(void* pData)
{
	auto pteam = (ProtoClient2_TeamInviteRsp*)pData;

	LOG_TRACE("@@@@@@@@@@[TEAM] invitee_name : %s,accept: %u", pteam->inviter_name,pteam->accepted);
	ProtoGS_TeamInviteRsp TeamInviteRsp;
	TeamInviteRsp.token = GetToken();
	TeamInviteRsp.accepted = pteam->accepted;
	strcpy_s(TeamInviteRsp.inviter_name, _countof(TeamInviteRsp.inviter_name), pteam->inviter_name);
	SendDataBySessionType(SESSION_TYPE_GS2MS, TeamInviteRsp);
}

void SessionGS2CL::HandleClient2Msg_TeamLeaveReq(void* pData)
{
	auto pteam = (ProtoClient2_TeamLeaveEx*)pData;

	ProtoGS_TeamLeaveEx TeamLeaveEx;
	TeamLeaveEx.token = GetToken();
	SendDataBySessionType(SESSION_TYPE_GS2MS, TeamLeaveEx);
}

void SessionGS2CL::HandleClient2Msg_TeamKickReq(void* pData)
{
	auto pteam = (ProtoClient2_TeamKickEx*)pData;

	ProtoGS_TeamKickEx TeamEx;
	strcpy_s(TeamEx.name, _countof(TeamEx.name), pteam->name);
	TeamEx.token = GetToken();
	SendDataBySessionType(SESSION_TYPE_GS2MS, TeamEx);
}

void SessionGS2CL::HandleClient2Msg_TeamJoin(void* pData)
{
	auto pteam = (ProtoClient2_TeamJoin*)pData;

	ProtoGS_TeamJoin TeamEx;
	//name是utf code 需要转码
	auto name = utf8_to_gbk(pteam->team_member);
	strcpy_s(TeamEx.team_member, _countof(TeamEx.team_member), name.c_str());
	
	TeamEx.token = GetToken();
	SendDataBySessionType(SESSION_TYPE_GS2MS, TeamEx);
}

void SessionGS2CL::HandleClient2Msg_TeamJoinRsp(void* pData)
{
	auto pteam = (ProtoClient2_TeamJoinResponse*)pData;

	LOG_TRACE("@@@@@@@@@@[TEAM] joiner name : %s,accept: %u", pteam->joiner, pteam->accepted);
	ProtoGS_TeamJoinResponse TeamJoinRsp;
	TeamJoinRsp.token = GetToken();
	TeamJoinRsp.accepted = pteam->accepted;
	strcpy_s(TeamJoinRsp.joiner, _countof(TeamJoinRsp.joiner), pteam->joiner);
	SendDataBySessionType(SESSION_TYPE_GS2MS, TeamJoinRsp);
}

void SessionGS2CL::HandleClient2Msg_GetFamilyInfoReq(void *pData)
{
    const auto *msg = static_cast<ProtoClient2_GetFamilyInfoReq *>(pData);

    ProtoGS_GetFamilyInfoReq data;
    data.roleid = GetRoleGUID();
    data.token = GetToken();
    data.reqType = msg->reqType;
    data.start_index = msg->start_index;
    data.req_count = msg->req_count;
    data.req_group = msg->req_group;
    strcpy_s(data.info, _countof(data.info), msg->info);

    SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient2Msg_TopListReq(void* pData)
{
	const auto* msg = static_cast<ProtoClient2_TopListReq*>(pData);

	ProtoGS_TopListReq data;
	data.type = msg->type;
	data.sessionid = m_spSessionContext->nSessionID;
	SendDataBySessionType(SESSION_TYPE_GS2CS, data);
}

void SessionGS2CL::HandleClient2Msg_FamilyJoinReq(void *pData)
{
    const auto *msg = static_cast<ProtoClient2_FamilyJoinReq *>(pData);

    ProtoGS_FamilyJoinReq data;
    data.roleid = GetRoleGUID();
    data.token = GetToken();
    data.guid = msg->guid;

    SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient2Msg_FamilyJoinAck(void *pData)
{
    const auto *msg = static_cast<ProtoClient2_FamilyJoinAck *>(pData);

    ProtoGS_FamilyJoinAck data;
    data.leader_guid = GetRoleGUID();
    data.player_guid = msg->guid;
    data.is_allow = msg->is_allow;

    SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient2Msg_CancelFamilyJoinReq(void *pData)
{
    const auto *msg = static_cast<ProtoClient2_CancelFamilyJoinReq *>(pData);

    ProtoGS_CancelFamilyJoinReq data;
    data.roleid = GetRoleGUID();
    data.token = GetToken();
    data.guid = msg->guid;

    SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient2Msg_FamilyTitleAwardReq(void *pData)
{
    const auto *msg = static_cast<ProtoClient2_FamilyTitleAwardReq *>(pData);

    ProtoGS_FamilyTitleAwardReq data;
    data.leader_guid = GetRoleGUID();
    data.player_guid = msg->guid;
    data.title_id = msg->title_id;

    SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient2Msg_MailListReq(void* pData)
{
	auto msg = (ProtoClient2_MaillistReq*)pData;
	ProtoGS_MaillistReq data;
	data.mail_id = msg->mail_id;
	data.type = msg->type;
	data.role_id = GetRoleGUID();
	SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient2Msg_FamilyExpellReq(void *pData)
{
    const auto *msg = static_cast<ProtoClient2_FamilyExpellReq *>(pData);

    ProtoGS_FamilyExpellReq data;
    data.kicker_guid = GetRoleGUID();
    data.player_guid = msg->player_guid;

    SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient2Msg_FamilyNoticeEditReq(void *pData)
{
    const auto *msg = static_cast<ProtoClient2_FamilyNoticeEditReq *>(pData);

    ProtoGS_FamilyNoticeEditReq data;
    data.roleid = GetRoleGUID();
    data.token = GetToken();
    data.notice_len = msg->notice_len;
    strcpy_s(data.notice, _countof(data.notice), msg->notice);

    SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}
void SessionGS2CL::HandleClient2Msg_MailOpenReq(void* pData)
{
	auto msg = (ProtoClient2_MailOpenReq*)pData;
	ProtoGS_MailOpenReq data;
	data.id = msg->id;
	data.role_id = GetRoleGUID();
	SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient2Msg_MailAttachmentGetReq(void* pData)
{
	auto msg = (ProtoClient2_MailAttachmentGetReq*)pData;
	ProtoGS_MailAttachmentGetReq data;
	data.mail_id = msg->mail_id;
	data.index = msg->index;
	data.role_id = GetRoleGUID();
	SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient2Msg_MailDelReq(void* pData)
{
	auto msg = (ProtoClient2_MailDeleteReq*)pData;
	ProtoGS_MailDeleteReq data;
	data.id = msg->id;
	data.role_id = GetRoleGUID();
	SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient2Msg_FriendAddReq(void *pData)
{
    const auto *msg = static_cast<ProtoClient2_FriendAddReq *>(pData);

    ProtoGS_FriendAddReq data;
    data.roleid = GetRoleGUID();
    data.token = GetToken();
    strcpy_s(data.player_name, _countof(data.player_name), msg->player_name);

    SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient2Msg_FamilyLeaveOrLastMsgReq(void *pData)
{
    const auto *msg = static_cast<ProtoClient2_FamilyLeaveOrLastMsgReq *>(pData);

    ProtoGS_FamilyLeaveOrLastMsgReq data;
    data.roleid = GetRoleGUID();
    data.token = GetToken();
    strcpy_s(data.byebye, _countof(data.byebye), msg->byebye);

    SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient2Msg_FamilyDestroyReq(void *pData)
{
    const auto *msg = static_cast<ProtoClient2_FamilyDestroyReq *>(pData);

    ProtoGS_FamilyDestroyReq data;
    data.roleid = GetRoleGUID();
    data.token = GetToken();

    SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient3Msg_TurnReq(void* pData)
{
	auto pTurnReq = (ProtoClient3_TurnReq*)pData;

	LOG_TRACE("[TurnReq] session: %u, token: %u, player: %" PRIu64 ", dir: %u",
		m_spSessionContext->nSessionID, GetToken(), GetPlayerGUID(), pTurnReq->dir);

	if (!IsLoggedIn()) {
		LOG_ERROR("[TurnReq] Not logged in");
		return;
	}

	ProtoGS_TurnReq turnReq;
	turnReq.role_guid = pTurnReq->role_guid;
	turnReq.dir = pTurnReq->dir;

	SendDataBySessionType(SESSION_TYPE_GS2MS, turnReq);
}

void SessionGS2CL::HandleClient3Msg_SpellTarget(void* pData)
{
	auto pSpellTarget = (ProtoClient3_SpellTarget*)pData;

	LOG_TRACE("[SpellTarget] session: %u, token: %u, player: %" PRIu64 ", skill: %u, target: %" PRIu64,
		GetID(), GetToken(), GetPlayerGUID(), pSpellTarget->id, pSpellTarget->target);

	if (!IsLoggedIn()) {
		LOG_ERROR("[SpellTarget] Not logged in");
		return;
	}

	ProtoGS_SpellTarget spellTarget;
	spellTarget.role_guid = pSpellTarget->role_guid;
	spellTarget.id = pSpellTarget->id;
	spellTarget.target = pSpellTarget->target;
	spellTarget.idx = pSpellTarget->idx;

	if (!SendDataBySessionType(SESSION_TYPE_GS2MS, spellTarget)) {
		LOG_ERROR("[SpellTarget] Send to map server failed");
		SendSpellAckToClient(pSpellTarget->role_guid, pSpellTarget->id, ERR_SYSTEM, EMSG_GS2MS_CONN_ERROR, pSpellTarget->idx);
	}
}

void SessionGS2CL::HandleClient3Msg_SpellGrid(void* pData)
{
	auto pSpellGrid = (ProtoClient3_SpellGrid*)pData;

	LOG_TRACE("[SpellGrid] session: %u, token: %u, player: %" PRIu64 ", skill: %u, x: %u, y: %u, idx: %u, target: %" PRIu64,
		GetID(), GetToken(), GetPlayerGUID(), pSpellGrid->id, pSpellGrid->target_x,
		pSpellGrid->target_y, pSpellGrid->idx, pSpellGrid->ref_target);

	if (!IsLoggedIn()) {
		LOG_ERROR("[SpellGrid] Not logged in");
		return;
	}

	ProtoGS_SpellGrid spellGrid;
	spellGrid.role_guid = pSpellGrid->role_guid;
	spellGrid.id = pSpellGrid->id;
	spellGrid.target_x = pSpellGrid->target_x;
	spellGrid.target_y = pSpellGrid->target_y;
	spellGrid.idx = pSpellGrid->idx;
	spellGrid.ref_target = pSpellGrid->ref_target;
    spellGrid.extra = pSpellGrid->extra;

	if (!SendDataBySessionType(SESSION_TYPE_GS2MS, spellGrid)) {
		LOG_ERROR("[SpellGrid] Send to map server failed");
		SendSpellAckToClient(pSpellGrid->role_guid, pSpellGrid->id, ERR_SYSTEM, EMSG_GS2MS_CONN_ERROR, pSpellGrid->idx);
	}
}

void SessionGS2CL::HandleClient3Msg_SkillSwitch(void* pData)
{
	auto pSkillSwitch = (ProtoClient3_SkillSwitch*)pData;

	LOG_TRACE("[SkillSwitch] session: %u, token: %u, skill: %u, active: %u",
		GetID(), GetToken(), pSkillSwitch->id, pSkillSwitch->active);

	ProtoGS_SkillSwitch skillSwitch;
	skillSwitch.token = GetToken();
	skillSwitch.clientSessionID = GetID();
	skillSwitch.id = pSkillSwitch->id;
	skillSwitch.active = pSkillSwitch->active;

	SendDataBySessionType(SESSION_TYPE_GS2MS, skillSwitch);
}

void SessionGS2CL::SendRandKeyNtfToClient(const char *randkey)
{
    if (!randkey) return;

	ProtoClient_RandKeyNtf randKeyNtf;
	randKeyNtf.codelen = strlen(randkey);
	strcpy_s((char*)randKeyNtf.code, _countof(randKeyNtf.code), randkey);

	SendPkg(&randKeyNtf, sizeof(randKeyNtf));
}

void SessionGS2CL::SendLoginAckToClient(int32_t errcode, const char* errmsg, uint64_t playerid)
{
	ProtoClient_LoginAck loginAck;

	loginAck.errcode = errcode;
	strcpy_s(loginAck.errmsg, _countof(loginAck.errmsg), errmsg);
	loginAck.playerid = playerid;

	SendPkg(&loginAck, sizeof(loginAck));
}

void SessionGS2CL::SendKickUserNtfToClient()
{
	if (!IsLoggedIn()) return;

	ProtoClient_KickUserNtf kickUserNtf;
	kickUserNtf.errcode = ERR_GS_KICK_PLAYER;
	strcpy_s(kickUserNtf.errmsg, _countof(kickUserNtf.errmsg), EMSG_LOGGED_IN_ELSEWHERE);

	SendPkg(&kickUserNtf, sizeof(kickUserNtf));
}

void SessionGS2CL::SendGetRoleListAckToClient(int32_t errcode, const char* errmsg)
{
	ProtoClient_GetRoleListAck ack;
	ack.errcode = errcode;
	strcpy_s(ack.errmsg, _countof(ack.errmsg), errmsg);

	SendPkg(&ack, sizeof(ack));
}

void SessionGS2CL::SendCreateRoleAckToClient(int32_t errcode, const char* errmsg)
{
	ProtoClient_CreateRoleAck createRoleAck;
	createRoleAck.errcode = errcode;
	strcpy_s(createRoleAck.errmsg, _countof(createRoleAck.errmsg), errmsg);

	SendPkg(&createRoleAck, sizeof(createRoleAck));
}

void SessionGS2CL::SendDeleteRoleAckToClient(const uint64_t& roleid, int32_t errcode, const char* errmsg)
{
	ProtoClient_DeleteRoleAck deleteRoleAck;
	deleteRoleAck.guid = roleid;
	deleteRoleAck.errcode = errcode;
	strcpy_s(deleteRoleAck.errmsg, _countof(deleteRoleAck.errmsg), errmsg);

	SendPkg(&deleteRoleAck, sizeof(deleteRoleAck));
}

void SessionGS2CL::SendRestoreRoleAckToClient(const uint64_t& roleid, int32_t errcode, const char* errmsg, const ROLE_BRIEF_INFO& role)
{
	ProtoClient_RestoreRoleAck restoreRoleAck;
	restoreRoleAck.errcode = errcode;
	strcpy_s(restoreRoleAck.errmsg, _countof(restoreRoleAck.errmsg), errmsg);
	restoreRoleAck.role = role;

	SendPkg(&restoreRoleAck, sizeof(restoreRoleAck));
}

void SessionGS2CL::SendMoveAckToClient(uint64_t role_guid, uint8_t ret, uint32_t idx, uint8_t type, uint16_t dst_x, uint16_t dst_y)
{
	ProtoClient3_MoveAck moveAck;
    moveAck.role_guid = role_guid;
	moveAck.ret = ret;
	moveAck.idx = idx;
	moveAck.type = type;
	moveAck.dst_x = dst_x;
	moveAck.dst_y = dst_y;

	SendPkg(&moveAck, sizeof(moveAck));
}

void SessionGS2CL::SendTurnNtfToClient(const uint64_t& guid, const uint8_t& dir)
{
	ProtoClient3_TurnNtf turnNtf;
	turnNtf.guid = guid;
	turnNtf.dir = dir;

	SendPkg(&turnNtf, sizeof(turnNtf));
}

void SessionGS2CL::SendSpellAckToClient(uint64_t role_guid, uint16_t id, int32_t errcode, const char* errmsg, uint16_t idx)
{
    LOG_TRACE("[SpellAck] id: %u, errcode: %d, idx: %u", id, errcode, idx);

	ProtoClient3_SpellAck spellAck;
    spellAck.role_guid = role_guid;
	spellAck.id = id;
	spellAck.ecode = errcode;
	strcpy_s(spellAck.detail, _countof(spellAck.detail), errmsg);
	spellAck.idx = idx;

	SendPkg(&spellAck, sizeof(spellAck));
}

void SessionGS2CL::SendLogoutReqToLS(uint32_t sessionid, uint32_t token, uint8_t info)
{
	ProtoGS_LogoutReq logoutReq;
	logoutReq.sessionid = sessionid;
	logoutReq.token = token;
    logoutReq.info = info;

	SendDataBySessionType(SESSION_TYPE_GS2LS, logoutReq);
}

void SessionGS2CL::SendUpdateOnlineStateToLS(uint64_t roleid, uint32_t token, uint8_t state)
{
    ProtoGS_UpdateOnlineState data;
    data.roleid = roleid;
    data.token = token;
    data.state = state;

    SendDataBySessionType(SESSION_TYPE_GS2LS, data);
}

void SessionGS2CL::SendReloginAckToClient(int32_t errcode, const char* errmsg)
{
	ProtoClient_ReloginAck reloginAck;
	reloginAck.errcode = errcode;
	if (errmsg) strcpy_s(reloginAck.errmsg, _countof(reloginAck.errmsg), errmsg);

	SendPkg(&reloginAck, sizeof(reloginAck));
}

void SessionGS2CL::OnLoginAck(ProtoGS_LoginAck* pLoginAck)
{
	if (pLoginAck->errcode != ERR_OK) {
        SendLoginAckToClient(pLoginAck->errcode, pLoginAck->errmsg, 0);
        return;
    }

    if (MaxClientReached() && !IsGMAccount(pLoginAck->userid)) {            // GM不限制登录
        SendLoginAckToClient(ERR_GS_OVERLOAD, EMSG_MAX_CLIENT_LIMIT, 0);
        SendLogoutReqToLS(GetID(), pLoginAck->token, 0);
        return;
    }

    SendLoginAckToClient(ERR_OK, pLoginAck->errmsg, pLoginAck->userid);

    auto oldContext = SessionContextMgr::GetInstance()->GetSessionContext(pLoginAck->userid);
    if (oldContext) {
        StopReserveContextTimer(oldContext);
        SessionContextMgr::GetInstance()->DelSessionContext(oldContext->nSessionID);
    }

    SetOnlineState(online_state_logged_in);
    m_spSessionContext->nPlayerGUID = pLoginAck->userid;
    m_spSessionContext->nToken = pLoginAck->token;
    m_spSessionContext->sRandKey = pLoginAck->randkey;
    LOG_NORMAL("Login success. Remote host: %s:%u, session id: %u, token: %u, userid: %llu",
        GetRemoteIp().c_str(), GetRemotePort(), GetID(), pLoginAck->token, pLoginAck->userid);

    SendRandKeyNtfToClient(pLoginAck->randkey);
}

void SessionGS2CL::OnReloginAck(ProtoGS_ReloginAck* pReloginAck)
{
    if (pReloginAck->errcode != ERR_OK) {
        SendReloginAckToClient(pReloginAck->errcode, pReloginAck->errmsg);
        return;
    }

    if (MaxClientReached()) {
        SendReloginAckToClient(ERR_GS_OVERLOAD, EMSG_MAX_CLIENT_LIMIT);
        SendLogoutReqToLS(GetID(), pReloginAck->token, 0);
        return;
    }

    auto oldContext = SessionContextMgr::GetInstance()->GetSessionContext(pReloginAck->player_guid);

    if (!oldContext) {  // 定时器到期删除或客户端选择了不同的gateserver relogin

        // do nothing
    }
    else if (oldContext->nSessionID != GetID()) {   // 只有session断开连接的时候才会设置定时器，之后session会被销毁
                                                    // 因此同一个session不可能设置定时器
		// 旧的会话置为未登录状态
		oldContext->nOnlineState = online_state_not_logged_in;

        StopReserveContextTimer(oldContext);
        SessionContextMgr::GetInstance()->DelSessionContext(oldContext->nSessionID);
    }

    m_spSessionContext->sUserName = pReloginAck->username;
    m_spSessionContext->nPlayerGUID = pReloginAck->player_guid;
    m_spSessionContext->nRoleGUID = pReloginAck->role_guid;
    m_spSessionContext->nToken = pReloginAck->token;
    m_spSessionContext->sRandKey = pReloginAck->randkey;

    SetOnlineState(online_state_logged_in);

    // 同步在线状态到LS CS MS
    SendUpdateOnlineStateToLS(pReloginAck->role_guid, pReloginAck->token, online_state_logged_in);

    // randkey、token跟以前一样，randkey不用同步给客户端

    // 同步cl2gs_sessid到map server 
    SendSyncSessionIDToMS(pReloginAck->role_guid, pReloginAck->token, GetID());

	SendUpdatePlayerStatus(pReloginAck->role_guid);

    LOG_NORMAL("Relogin success. Remote host: %s:%u, session id: %u, token: %u",
        GetRemoteIp().c_str(), GetRemotePort(), GetID(), pReloginAck->token);
}

void SessionGS2CL::SendSyncSessionIDToMS(uint64_t role_guid, uint32_t token, uint32_t cl2gs_sessid)
{
    ProtoGS_SyncSessionID data;
    data.role_guid = role_guid;
    data.token = token;
    data.cl2gs_sessid = cl2gs_sessid;

    SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::SendUpdatePlayerStatus(uint64_t guid)
{
	ProtoGS_AfterReloginUpdateStatus data;
	data.guid = guid;
	SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::OnLogoutNtf(ProtoLS_LogoutNtf* pLogoutNtf)
{
	if (strcmp(pLogoutNtf->username, m_spSessionContext->sUserName.c_str()) != 0) {
		LOG_ERROR("User name does not match. in session: %s, received: %s", m_spSessionContext->sUserName.c_str(), pLogoutNtf->username);
	}

	if (pLogoutNtf->playerid != GetPlayerGUID()) {
		LOG_ERROR("playerid does not match. in session: %" PRIu64 ", received: %" PRIu64, GetPlayerGUID(), pLogoutNtf->playerid);
	}

	SendKickUserNtfToClient();
}

void SessionGS2CL::OnGetRoleListAck(ProtoGS_GetRoleListAck* pGetRoleListAck)
{
	if (pGetRoleListAck->token != GetToken()) {
		SendGetRoleListAckToClient(ERR_NOUSERDATA, EMSG_INCONSIST_TOKEN);
		return;
	}

	m_spSessionContext->nLastSelectedRole = pGetRoleListAck->last_role;

	ProtoClient_GetRoleListAck getRoleListAck;
	getRoleListAck.errcode = pGetRoleListAck->errcode;
	strcpy_s(getRoleListAck.errmsg, _countof(getRoleListAck.errmsg), pGetRoleListAck->errmsg);
	getRoleListAck.rolenum = pGetRoleListAck->rolenum;
	getRoleListAck.last_role = pGetRoleListAck->last_role;
	memcpy_s(getRoleListAck.rolelist, sizeof(getRoleListAck.rolelist), pGetRoleListAck->rolelist, sizeof(pGetRoleListAck->rolelist));
	getRoleListAck.needCode = pGetRoleListAck->needCode;

	SendPkg(&getRoleListAck, sizeof(getRoleListAck));
}

void SessionGS2CL::OnCreateRoleAck(ProtoGS_CreateRoleAck* pCreateRoleAck)
{
	if (pCreateRoleAck->token != GetToken()) {
		LOG_ERROR("Token does not match");
		SendCreateRoleAckToClient(ERR_NOUSERDATA, EMSG_INCONSIST_TOKEN);
		return;
	}

	ProtoClient_CreateRoleAck createRoleAck;
	createRoleAck.errcode = pCreateRoleAck->errcode;
	strcpy_s(createRoleAck.errmsg, _countof(createRoleAck.errmsg), pCreateRoleAck->errmsg);
	createRoleAck.newrole = pCreateRoleAck->newrole;

	SendPkg(&createRoleAck, sizeof(createRoleAck));
}

void SessionGS2CL::OnDeleteRoleAck(ProtoGS_DeleteRoleAck* pDeleteRoleAck)
{
	if (pDeleteRoleAck->token != GetToken()) {
		LOG_ERROR("Token does not match");
		SendDeleteRoleAckToClient(pDeleteRoleAck->roleid, ERR_NOUSERDATA, EMSG_NO_USER_DATA);
		return;
	}

	SendDeleteRoleAckToClient(pDeleteRoleAck->roleid, pDeleteRoleAck->errcode, pDeleteRoleAck->errmsg);
}

void SessionGS2CL::OnRestoreRoleAck(ProtoGS_RestoreRoleAck* pRestoreRoleAck)
{
	if (pRestoreRoleAck->token != GetToken()) {
		LOG_ERROR("Token does not match");
		SendRestoreRoleAckToClient(pRestoreRoleAck->roleid, ERR_NOUSERDATA, EMSG_NO_USER_DATA, ROLE_BRIEF_INFO());
		return;
	}

	SendRestoreRoleAckToClient(pRestoreRoleAck->roleid, pRestoreRoleAck->errcode, pRestoreRoleAck->errmsg, pRestoreRoleAck->role);
}

void SessionGS2CL::OnMoveAck(ProtoGS_MoveAck* pMoveAck)     //发送角色移动的ACK消息
{
	SendMoveAckToClient(pMoveAck->role_guid, pMoveAck->ret, pMoveAck->idx, pMoveAck->type, pMoveAck->dst_x, pMoveAck->dst_y);
}

void SessionGS2CL::OnTurnNtf(ProtoGS_TurnNtf* pTurnNtf)
{
	if (pTurnNtf->token != GetToken() ||
		pTurnNtf->playerid != GetPlayerGUID()) {
		LOG_ERROR("[TurnNtf] token or playerid does not match");
		return;
	}

	SendTurnNtfToClient(pTurnNtf->guid, pTurnNtf->dir);
}

void SessionGS2CL::OnSpellAck(ProtoGS_SpellAck* pSpellAck)
{
	SendSpellAckToClient(pSpellAck->role_guid, pSpellAck->id, pSpellAck->ecode, pSpellAck->detail, pSpellAck->idx);
}

void SessionGS2CL::HandleClient3Msg_EnterGSReq(void* pData)
{
	ProtoClient3_EnterGSReq* req = (ProtoClient3_EnterGSReq*)pData;

	ProtoGS_EnterGSReq gsreq;
	gsreq.sessionid = GetID();
	gsreq.token = GetToken();
	gsreq.playerid = GetPlayerGUID();
	gsreq.MS2GSSessionID = SessionContextMgr::GetInstance()->GetMS2GSSessionID();
	gsreq.clienttype = req->clienttype;
	gsreq.entertype = req->entertype;
	gsreq.fangchenmi = req->fangchenmi;
	gsreq.roleBriefInfo = req->roleBriefInfo;
	m_spSessionContext->nRoleGUID = gsreq.roleBriefInfo.guid;

	LOG_NORMAL("EnterGSReq, remote host: %s:%u, session id: %u, token: %u, role id: %" PRIu64,
		GetRemoteIp().c_str(), GetRemotePort(), GetID(), GetToken(), GetRoleGUID());

	//send to center server
	SendDataBySessionType(SESSION_TYPE_GS2CS, gsreq);
}

void SessionGS2CL::HandleClient3Msg_ExitGSReq(void* pData)
{
	ProtoClient3_ExitGSReq* req = (ProtoClient3_ExitGSReq*)pData;
	if (nullptr == req) {
		return;
	}
	ProtoGS_ExitGSReq gsreq;
	gsreq.exittype = req->exittype;
	gsreq.sessionid = GetID();
	gsreq.nrole_guid = GetRoleGUID();
	//send to map server
	bool status = SendDataBySessionType(SESSION_TYPE_GS2MS, gsreq);
	if (false == status) {
		return;
	}
}

void SessionGS2CL::HandleClient3Msg_ReliveReq(void* pData)
{
	ProtoClient3_PlayerReliveReq* req = (ProtoClient3_PlayerReliveReq*)pData;
	if (nullptr == req) {
		return;
	}
	ProtoGS_PlayerReliveReq gsreq;
	gsreq.relive_type = req->relive_type;
	gsreq.sessionid = GetID();
	gsreq.token = GetToken();
	//send to map server
	bool status = SendDataBySessionType(SESSION_TYPE_GS2MS, gsreq);
	if (false == status) {
		return;
	}
}

void SessionGS2CL::OnKickRoleNtf(ProtoGS_KickRoleNtf* ntf)
{
	ProtoClient3_KickRoleNtf kickUserNtf;
	kickUserNtf.errcode = ntf->errcode;
	strcpy_s(kickUserNtf.errmsg, _countof(kickUserNtf.errmsg), ntf->errmsg);
	SendPkg(&kickUserNtf, sizeof(kickUserNtf));
    SetOnlineState(online_state_being_kicked);
}

void SessionGS2CL::OnGetTopListAck(ProtoGS_TopListAck* ack)
{
	ProtoClient2_TopListAck pack;
	pack.type = ack->type;
	pack.time = ack->time;
	pack.num = ack->num;
	for (uint8_t i = 0; i < ack->num; i++) {
		pack.info[i] = ack->info[i];
	}
	SendPkg(&pack, sizeof(ack));
}

void SessionGS2CL::HandleClient3Msg_NpcSelect(void *pData)
{
    auto pNpcSelect = (ProtoClient3_NpcSelect *)pData;

    ProtoGS_NpcSelect npcSelect;
    npcSelect.roleid = GetRoleGUID();
    npcSelect.token = GetToken();
    npcSelect.npc_guid = pNpcSelect->npc_guid;

    SendDataBySessionType(SESSION_TYPE_GS2MS, npcSelect);
}

void SessionGS2CL::HandleClient3Msg_NpcTalkReq(void *pData)
{
    const auto *msg = static_cast<ProtoClient3_NpcTalkReq *>(pData);

    ProtoGS_NpcTalkReq data;
    data.roleid = GetRoleGUID();
    data.token = GetToken();
    data.npc_guid = msg->npc_guid;
    strcpy_s(data.func, _countof(data.func), msg->func);

    SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient3Msg_TradeNpcBuy(void *pData)
{
    auto pTradeNpcBuy = (ProtoClient3_TradeNpcBuy *)pData;

    ProtoGS_TradeNpcBuy tradeNpcBuy;
    tradeNpcBuy.roleid = GetRoleGUID();
    tradeNpcBuy.token = GetToken();
    tradeNpcBuy.shop_id = pTradeNpcBuy->shop_id;
    tradeNpcBuy.item_index = pTradeNpcBuy->item_index;
    tradeNpcBuy.item_amount = pTradeNpcBuy->item_amount;
    tradeNpcBuy.is_bind = pTradeNpcBuy->is_bind;

    SendDataBySessionType(SESSION_TYPE_GS2MS, tradeNpcBuy);
}

void SessionGS2CL::HandleClient3Msg_AtkModeReq(void *pData)
{
    auto pAtkModeReq = (ProtoClient3_AtkModeReq *)pData;

    LOG_TRACE("atk_mode: %u", pAtkModeReq->atk_mode);

    ProtoGS_AtkModeReq atkModeReq;
    atkModeReq.roleid = GetRoleGUID();
    atkModeReq.token = GetToken();
    atkModeReq.atk_mode = pAtkModeReq->atk_mode;

    SendDataBySessionType(SESSION_TYPE_GS2MS, atkModeReq);
}

void SessionGS2CL::HandleClient3Msg_QuestQueryCanAccept(void *pData)
{
    auto pQuestQueryCanAccept = (ProtoClient3_QuestQueryCanAccept *)pData;

    ProtoGS_QuestQueryCanAccept questQueryCanAccept;
    questQueryCanAccept.roleid = GetRoleGUID();
    questQueryCanAccept.token = GetToken();

    SendDataBySessionType(SESSION_TYPE_GS2MS, questQueryCanAccept);
}

void SessionGS2CL::HandleClient3Msg_QuestAccept(void *pData)
{
    auto pQuestAccept = (ProtoClient3_QuestAccept *)pData;

    ProtoGS_QuestAccept questAccept;
    questAccept.roleid = GetRoleGUID();
    questAccept.token = GetToken();
    questAccept.quest_id = pQuestAccept->quest_id;

    SendDataBySessionType(SESSION_TYPE_GS2MS, questAccept);
}

void SessionGS2CL::HandleClient3Msg_QuestDrop(void *pData)
{
    const auto *pQuestDrop = static_cast<ProtoClient3_QuestDrop *>(pData);

    ProtoGS_QuestDrop questDrop;
    questDrop.roleid = GetRoleGUID();
    questDrop.token = GetToken();
    questDrop.quest_id = pQuestDrop->quest_id;

    SendDataBySessionType(SESSION_TYPE_GS2MS, questDrop);
}

void SessionGS2CL::HandleClient3Msg_QuestAccomplish(void *pData)
{
    const auto *pQuestAccomplish = static_cast<ProtoClient3_QuestAccomplish *>(pData);

    ProtoGS_QuestAccomplish questAccomplish;
    questAccomplish.roleid = GetRoleGUID();
    questAccomplish.token = GetToken();
    questAccomplish.quest_id = pQuestAccomplish->quest_id;
    questAccomplish.select_index = pQuestAccomplish->select_index;

    SendDataBySessionType(SESSION_TYPE_GS2MS, questAccomplish);
}

void SessionGS2CL::HandleClient3Msg_PlayerSwitchReq(void* pData)
{
	auto pPlayerSwitchReq = (ProtoClient3_PlayerSwitchReq*)pData;

	ProtoGS_PlayerSwitchReq Req;
	Req.id = pPlayerSwitchReq->id;
	Req.token = GetToken();
	Req.value = pPlayerSwitchReq->value;

	SendDataBySessionType(SESSION_TYPE_GS2MS, Req);
}

void SessionGS2CL::HandleClient3Msg_GetAroundTeamReq(void* pData)
{
	auto pReq = (ProtoClient3_GetAroundTeamReq*)pData;

	ProtoGS_GetAroundTeamReq Req;
	Req.token = GetToken();
	SendDataBySessionType(SESSION_TYPE_GS2MS, Req);
}

void SessionGS2CL::HandleClient3Msg_PlayerQuery(void *pData)
{
    const auto *msg = static_cast<ProtoClient3_PlayerQuery *>(pData);

    ProtoGS_PlayerQuery data;
    data.roleid = GetRoleGUID();
    data.token = GetToken();
    strcpy_s(data.player_name, _countof(data.player_name), msg->player_name);

    SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient3Msg_QuickBarSet(void* pData)
{
	auto pReq = (ProtoClient3_QuickBarSet*)pData;
	ProtoGS_QuickBarSet Req;
	Req.guid = pReq->guid;
	Req.id = pReq->id;
	Req.slot = pReq->slot;
	Req.type = pReq->type;
	Req.sessionid = m_spSessionContext->nSessionID;
	Req.role_id = GetRoleGUID();
	SendDataBySessionType(SESSION_TYPE_GS2MS, Req);
}

void SessionGS2CL::HandleClient3Msg_GoldTake(void* pData)
{
	auto pReq = (ProtoClient3_GoldTake *)pData;
	ProttoGS_GoldTake Req;
	Req.gold = pReq->gold;
	Req.sessionid = m_spSessionContext->nSessionID;
	Req.role_id = GetRoleGUID();
	SendDataBySessionType(SESSION_TYPE_GS2MS, Req);
}
void SessionGS2CL::HandleClient3Msg_GoldDeposit(void* pData)
{
	auto pReq = (ProtoClient3_GoldDeposit*)pData;
	ProtoGS_GoldDeposit Req;
	Req.gold = pReq->gold;
	Req.sessionid = m_spSessionContext->nSessionID;
	Req.role_id = GetRoleGUID();
	SendDataBySessionType(SESSION_TYPE_GS2MS, Req);
}

void SessionGS2CL::HandleClient3Msg_GMCommandReq(void* pData)
{
	auto pReq = (ProtoClient3_GMCommandReq*)pData;
    LOG_NORMAL("[GM] GMCommandReq cmd: %s, param: %s, sn: %d", pReq->cmd, pReq->param, pReq->sn);
	MSG_BUFFER_DATA(ProtoGS_GMCommandReq, req);
	//ProtoGS_GMCommandReq Req;
    req.sn = pReq->sn;
	strcpy_s(req.cmd, _countof(req.cmd), pReq->cmd);
	strcpy_s(req.param, _countof(req.param), pReq->param);
	req.sessionid = m_spSessionContext->nSessionID;
	req.role_id = GetRoleGUID();
	req.token = GetToken();
	SendDataBySessionType(SESSION_TYPE_GS2CS, req);
}
	
void SessionGS2CL::HandleClient3Msg_RoleCustVarReq(void* pData)
{
	auto pReq = (ProtoClient3_RoleCustVarReq*)pData;
	ProtoGS_RoleCustVarReq Req;
	Req.sessionid = m_spSessionContext->nSessionID;
	Req.role_guid = pReq->role_guid;
	SendDataBySessionType(SESSION_TYPE_GS2MS, Req);
}


void SessionGS2CL::HandleClient3Msg_RecordsMineReq(void* pData)
{
	auto pReq = (ProtoClient3_RecordsMineReq*)pData;
	ProtoGS_RecordsMineReq Req;
	Req.sessionid = m_spSessionContext->nSessionID;
	Req.role_id = pReq->role_id;
	Req.type = pReq->type;
	SendDataBySessionType(SESSION_TYPE_GS2MS, Req);
}

void SessionGS2CL::HandleClient3Msg_DelegateMineReq(void* pData)
{
	auto pReq = (ProtoClient3_DelegateMineReq*)pData;
	ProtoGS_DelegateMineReq Req;
	Req.sessionid = m_spSessionContext->nSessionID;
	Req.role_id = pReq->role_id;
	SendDataBySessionType(SESSION_TYPE_GS2MS, Req);
}

void SessionGS2CL::HandleClient3Msg_DelegateSellListReq(void* pData)
{
	auto pReq = (ProtoClient3_DelegateSellListReq*)pData;

	ProtoGS_DelegateListReq Req;
	Req.start = pReq->start;
	Req.count = pReq->count;
	Req.type = pReq->type;
	Req.subtype = pReq->subtype;
	memcpy_s(Req.item_name, sizeof(Req.item_name), pReq->item_name, sizeof(pReq->item_name));
	Req.is_reverse = pReq->is_reverse;
	Req.role_id = GetRoleGUID();
	Req.sessionid = m_spSessionContext->nSessionID;
	Req.delegatetype = delegate_type_sell;
	SendDataBySessionType(SESSION_TYPE_GS2MS, Req);
}

void SessionGS2CL::HandleClient3Msg_DelegateBuyListReq(void* pData)
{
	auto pReq = (ProtoClient3_DelegateBuyListReq*)pData;

	ProtoGS_DelegateListReq Req;
	Req.start = pReq->start;
	Req.count = pReq->count;
	Req.type = pReq->type;
	Req.subtype = pReq->subtype;
	memcpy_s(Req.item_name, sizeof(Req.item_name), pReq->item_name, sizeof(pReq->item_name));
	Req.is_reverse = pReq->is_reverse;
	Req.role_id = GetRoleGUID();
	Req.sessionid = m_spSessionContext->nSessionID;
	Req.delegatetype = delegate_type_buy;
	SendDataBySessionType(SESSION_TYPE_GS2MS, Req);
}

void SessionGS2CL::HandleClient3Msg_DelegateCancelReq(void* pData)
{
	auto pReq = (ProtoClient3_DelegateCancel*)pData;

	ProtoGS_DelegateCancelReq Req;
	Req.trade_id = pReq->trade_id;
	Req.role_id = GetRoleGUID();
	Req.sessionid = m_spSessionContext->nSessionID;
	SendDataBySessionType(SESSION_TYPE_GS2MS, Req);
}

void SessionGS2CL::HandleClient3Msg_DelegateSellCmd(void* pData)
{
	auto pReq = (ProtoClient3_DelegateSellCmd*)pData;

	ProtoGS_DelegateSellCmd Req;
	Req.item_guid = pReq->item_guid;
	Req.item_value = pReq->item_value;
	Req.item_unit = pReq->item_unit;
	Req.value_type = pReq->value_type;
	Req.role_id = GetRoleGUID();
	Req.sessionid = m_spSessionContext->nSessionID;
	SendDataBySessionType(SESSION_TYPE_GS2MS, Req);
}

void SessionGS2CL::HandleClient3Msg_DelegateBuyCmd(void* pData)
{
	auto pReq = (ProtoClient3_DelegateBuyCmd*)pData;

	ProtoGS_DelegateBuyCmd Req;
	Req.item_id = pReq->item_id;
	Req.item_count = pReq->item_count;
	Req.item_value = pReq->item_value;
	Req.item_unit = pReq->item_unit;
	Req.value_type = pReq->value_type;
	Req.role_id = GetRoleGUID();
	Req.sessionid = m_spSessionContext->nSessionID;
	SendDataBySessionType(SESSION_TYPE_GS2MS, Req);
}

void SessionGS2CL::HandleClient3Msg_MarketSellCmd(void* pData)
{
	auto pReq = (ProtoClient3_MarketSellCmd*)pData;

	ProtoGS_MarketSellCmd Req;
	Req.trade_id = pReq->trade_id;
	Req.item_guid = pReq->item_guid;
	Req.role_id = GetRoleGUID();
	Req.sessionid = m_spSessionContext->nSessionID;
	SendDataBySessionType(SESSION_TYPE_GS2MS, Req);
}

void SessionGS2CL::HandleClient3Msg_MarketBuyCmd(void* pData)
{
	auto pReq = (ProtoClient3_MarketBuyCmd*)pData;

	ProtoGS_MarketBuyCmd Req;
	Req.trade_id = pReq->trade_id;
	Req.count = pReq->count;
	Req.role_id = GetRoleGUID();
	Req.sessionid = m_spSessionContext->nSessionID;
	SendDataBySessionType(SESSION_TYPE_GS2MS, Req);
}

void SessionGS2CL::HandleClient3Msg_QueryEx(void* pData)
{
	auto pReq = (ProtoClient3_QueryEx*)pData;
	ProtoGS_QueryEx req;
	req.token = GetToken();
	req.self_role_id = GetRoleGUID();
	req.role_id = pReq->role_id;
	SendDataBySessionType(SESSION_TYPE_GS2MS, req);
}

void SessionGS2CL::HandleClient3Msg_JumpMapReq(void *pData)
{
	const auto *msg = static_cast<ProtoClient3_JumpMapReq *>(pData);

	ProtoGS_JumpMapReq data;
	data.roleid = GetRoleGUID();
	data.token = GetToken();
	data.dst_x = msg->dst_x;
	data.dst_y = msg->dst_y;
	data.type = msg->type;

	SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient3Msg_GetNpcPosReq(void* pData)
{
	const auto* msg = static_cast<ProtoClient3_GetNpcPosReq*>(pData);

	ProtoGS_GetNpcPosReq data;
	data.roleid = GetRoleGUID();
	strcpy_s(data.name, _countof(data.name), msg->name);
	SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient3Msg_StartDigReq(void *pData)
{
    const auto *msg = static_cast<ProtoClient3_StartDigReq *>(pData);

    ProtoGS_StartDigReq data;
    data.role_guid = GetRoleGUID();
    data.treasure_guid = msg->treasure_guid;

    SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient3Msg_RangePickup(void *pData)
{
    const auto *msg = static_cast<ProtoClient3_RangePickup *>(pData);

    ProtoGS_RangePickup data;
    data.role_guid = GetRoleGUID();
    ASSIGN_MEMBER(posnum);
    ASSIGN_ARRAY_MEMEBER(pos);

    SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient3Msg_SyncClientBaseSetting(void* pData)
{
	const auto* msg = static_cast<ProtoClient3_SyncClientBaseSetting*>(pData);

	ProtoGS_SyncClientBaseSetting data;
	data.role_guid = GetRoleGUID();
	ASSIGN_MEMBER(type);
	ASSIGN_MEMBER(value);

	SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient3Msg_VerifyBuyItemInfoReq(void *pData)
{
    const auto *msg = static_cast<ProtoClient3_VerifyBuyItemInfoReq *>(pData);

    ProtoGS_VerifyBuyItemInfoReq data;
    data.role_guid = GetRoleGUID();
    ASSIGN_MEMBER(item_id);
    ASSIGN_MEMBER(item_count);
    ASSIGN_MEMBER(item_price);

    SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}
void SessionGS2CL::HandleClient3Msg_ItemRefreshReq(void *pData)
{
    const auto *msg = static_cast<ProtoClient3_ItemRefreshReq *>(pData);
    LOG_TRACE("[ITEM] ItemRefreshReq");

    ProtoGS_ItemRefreshReq data;
    data.role_guid = GetRoleGUID();
    data.token = GetToken();

    SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}
void SessionGS2CL::HandleClient3Msg_ItemTip(void* pData)
{
	const auto* msg = static_cast<ProtoClient3_ItemTip*>(pData);
	ProtoGS_ItemTip data;
	data.guid = GetRoleGUID();
	data.owner_guid = msg->owner_guid;
	data.item_guid = msg->item_guid;
	SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient3Msg_TitleRemove(void* pData)
{
	const auto* msg = static_cast<ProtoClient3_TitleDel*>(pData);
	ProtoGS_TitleDel data;
	data.guid = GetRoleGUID();
	data.id = msg->id;
	SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient3Msg_TitleApply(void* pData)
{
	const auto* msg = static_cast<ProtoClient3_TitleWear*>(pData);
	ProtoGS_TitleWear data;
	data.guid = GetRoleGUID();
	data.id = msg->id;
	SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient3Msg_TitleUnApply(void* pData)
{
	const auto* msg = static_cast<ProtoClient3_TitleUnWear*>(pData);
	ProtoGS_TitleUnWear data;
	data.guid = GetRoleGUID();
	data.id = msg->id;
	SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient3Msg_SetAutoModeAck(void *pData)
{
    const auto *msg = static_cast<ProtoClient3_SetAutoModeAck *>(pData);

    ProtoGS_SetAutoModeAck data;
    ASSIGN_MEMBER(role_guid);
    ASSIGN_MEMBER(enable);

    SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient3Msg_TitleGetListReq(void* pData)
{
	ProtoGS_TitleGetListReq data;
	data.guid = GetRoleGUID();
	SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}

void SessionGS2CL::HandleClient3Msg_GoodsPostRecordAck(void* pData)
{
	const auto* msg = static_cast<ProtoClient3_GoodsPostRecordAck*>(pData);

	ProtoGS_GoodsPostRecordAck data;
	data.guid = GetRoleGUID();
	ASSIGN_STRING_MEMBER(order_no);
	SendDataBySessionType(SESSION_TYPE_GS2MS, data);
}
