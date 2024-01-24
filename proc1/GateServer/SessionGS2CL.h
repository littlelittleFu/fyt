#pragma once
#include "Session.h"
#include "SessionContextMgr.h"
#include "ProtoGS.h"
#include "ProtoLS.h"


class SessionGS2CL : public Session
{
public:
	SessionGS2CL();
	~SessionGS2CL();

	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual void DoHeartBeat();

    void OnLoginAck(ProtoGS_LoginAck *pLoginAck);       // SessionLS -> SessionGS2CL
    void OnReloginAck(ProtoGS_ReloginAck* pLoginAck);       // SessionLS -> SessionGS2CL
    void OnLogoutNtf(ProtoLS_LogoutNtf* pLogoutNtf);    // SessionLS -> SessionGS2CL
    void OnGetRoleListAck(ProtoGS_GetRoleListAck *pGetRoleListAck);     // SessionCS -> SessionGS2CL
    void OnCreateRoleAck(ProtoGS_CreateRoleAck *pCreateRoleAck);        // SessionCS -> SessionGS2CL
    void OnDeleteRoleAck(ProtoGS_DeleteRoleAck* pDeleteRoleAck);        // SessionCS -> SessionGS2CL
    void OnRestoreRoleAck(ProtoGS_RestoreRoleAck* pRestoreRoleAck);
    void OnMoveAck(ProtoGS_MoveAck *pMoveAck);
    void OnTurnNtf(ProtoGS_TurnNtf *pTurnNtf);
    void OnSpellAck(ProtoGS_SpellAck *pSpellAck);
    void OnKickRoleNtf(ProtoGS_KickRoleNtf* ntf);
    void OnGetTopListAck(ProtoGS_TopListAck* ack);

private:
    void HandleClientMsg(uint16_t protoid, void* pData);
    void HandleClientMsg_ConnReq(void *pData);
    void HandleClientMsg_HeartBeatReq(void* pData);
    void HandleClientMsg_LoginReq(void* pData);
    void HandleClientMsg_ThirdLoginReq(void *pData);
    void HandleClientMsg_LogoutReq(void *pData);
    void HandleClientMsg_GetRoleListReq(void *pData);
    void HandleClientMsg_CreateRoleReq(void *pData);
    void HandleClientMsg_CreateRoleReqEx(void* pData);
    void HandleClientMsg_DeleteRoleReq(void *pData);
    void HandleClientMsg_RestoreRoleReq(void* pData);
    void HandleClientMsg_ReloginReq(void *pData);

    void HandleClient2Msg(uint16_t protoid, void *pData);
    void HandleClient2Msg_PrivateChatNtf(void *pData);
    void HandleClient2Msg_RelationChatReq(void *pData);
    void HandleClient2Msg_SpeakerMsgReq(void *pData);
    void HandleClient2Msg_Teamoperation(void *pData);
    void HandleClient2Msg_TeamInvite(void *pData);
    void HandleClient2Msg_TeamInviteRsp(void *pData);
    void HandleClient2Msg_TeamLeaveReq(void *pData);
    void HandleClient2Msg_TeamKickReq(void *pData);
    void HandleClient2Msg_TeamJoin(void* pData);
    void HandleClient2Msg_TeamJoinRsp(void* pData);
    void HandleClient2Msg_GetFamilyInfoReq(void *pData);
    void HandleClient2Msg_TopListReq(void* pData);
    void HandleClient2Msg_FamilyJoinReq(void *pData);
    void HandleClient2Msg_FamilyJoinAck(void *pData);
    void HandleClient2Msg_CancelFamilyJoinReq(void *pData);
    void HandleClient2Msg_FamilyTitleAwardReq(void *pData);
    void HandleClient2Msg_FamilyExpellReq(void *pData);
    void HandleClient2Msg_FamilyNoticeEditReq(void *pData);
    void HandleClient2Msg_MailListReq(void* pData);
    void HandleClient2Msg_MailOpenReq(void* pData);
    void HandleClient2Msg_MailAttachmentGetReq(void* pData);
    void HandleClient2Msg_MailDelReq(void* pData);  
    void HandleClient2Msg_FriendAddReq(void *pData);
    void HandleClient2Msg_FamilyLeaveOrLastMsgReq(void *pData);
    void HandleClient2Msg_FamilyDestroyReq(void *pData);

    void HandleClient3Msg(uint16_t protoid, void* pData);
    void HandleClient3Msg_ReliveReq(void* pData);
    void HandleClient3Msg_EnterGSReq(void* pData);
    void HandleClient3Msg_ExitGSReq(void* pData);
    void HandleClient3Msg_MoveReq(void* pData);
    void HandleClient3Msg_TurnReq(void* pData);
    void HandleClient3Msg_SpellTarget(void* pData);
    void HandleClient3Msg_SpellGrid(void* pData);
    void HandleClient3Msg_SkillSwitch(void *pData);
    void HandleClient3Msg_ItemApply(void* pData);
    void HandleClient3Msg_ItemPickUp(void* pData);
    void HandleClient3Msg_ItemDrop(void* pData);
    void HandleClient3Msg_ItemArrange(void* pData);
    void HandleClient3Msg_ItemMove(void* pData);
    void HandleClient3Msg_ItemSplit(void* pData);
    void HandleClient3Msg_RunServScriptReq(void *pData);
    void HandleClient3Msg_TradeMallBuy(void* pData);
    void HandleClient3Msg_TradeMallListReq(void* pData);
    void HandleClient3Msg_NpcSelect(void *pData);
    void HandleClient3Msg_NpcTalkReq(void *pData);
    void HandleClient3Msg_TradeNpcBuy(void *pData);
    void HandleClient3Msg_AtkModeReq(void *pData);
    void HandleClient3Msg_QuestQueryCanAccept(void *pData);
    void HandleClient3Msg_QuestAccept(void *pData);
    void HandleClient3Msg_QuestDrop(void *pData);
    void HandleClient3Msg_QuestAccomplish(void *pData);
    void HandleClient3Msg_PlayerSwitchReq(void *pData);
    void HandleClient3Msg_GetAroundTeamReq(void* pData);
    void HandleClient3Msg_PlayerQuery(void *pData);
    void HandleClient3Msg_QuickBarSet(void* pData);
    void HandleClient3Msg_GoldTake(void* pData);
    void HandleClient3Msg_GoldDeposit(void* pData);
    void HandleClient3Msg_GMCommandReq(void* pData);
    void HandleClient3Msg_RoleCustVarReq(void* pData);
    void HandleClient3Msg_RecordsMineReq(void* pData);
    void HandleClient3Msg_DelegateMineReq(void* pData);
    void HandleClient3Msg_DelegateSellListReq(void* pData);
    void HandleClient3Msg_DelegateBuyListReq(void* pData);
    void HandleClient3Msg_DelegateCancelReq(void* pData);
    void HandleClient3Msg_DelegateSellCmd(void* pData);
    void HandleClient3Msg_DelegateBuyCmd(void* pData);
    void HandleClient3Msg_MarketSellCmd(void* pData);
    void HandleClient3Msg_MarketBuyCmd(void* pData);
    void HandleClient3Msg_QueryEx(void* pData);
    void HandleClient3Msg_JumpMapReq(void *pData);
    void HandleClient3Msg_GetNpcPosReq(void* pData);
    void HandleClient3Msg_StartDigReq(void *pData);
    void HandleClient3Msg_RangePickup(void *pData);
    void HandleClient3Msg_SyncClientBaseSetting(void* pData);
    void HandleClient3Msg_VerifyBuyItemInfoReq(void *pData);
    void HandleClient3Msg_ItemRefreshReq(void *pData);
    void HandleClient3Msg_ItemTip(void* pData);
    void HandleClient3Msg_TitleRemove(void* pData);
    void HandleClient3Msg_TitleApply(void* pData);
    void HandleClient3Msg_TitleUnApply(void* pData);
    void HandleClient3Msg_SetAutoModeAck(void *pData);
    void HandleClient3Msg_TitleGetListReq(void* pData);
    void HandleClient3Msg_GoodsPostRecordAck(void* pData);


    void SendRandKeyNtfToClient(const char *randkey);
    void SendLoginAckToClient(int32_t errcode, const char* errmsg, uint64_t playerid);
    void SendKickUserNtfToClient();
    void SendGetRoleListAckToClient(int32_t errcode, const char *errmsg);
    void SendCreateRoleAckToClient(int32_t errcode, const char *errmsg);
    void SendDeleteRoleAckToClient(const uint64_t &roleid, int32_t errcode, const char *errmsg);
    void SendRestoreRoleAckToClient(const uint64_t& roleid, int32_t errcode, const char* errmsg, const ROLE_BRIEF_INFO& role);
    void SendMoveAckToClient(uint64_t role_guid, uint8_t ret, uint32_t idx, uint8_t type = 0, uint16_t dst_x = 0, uint16_t dst_y = 0);
    void SendTurnNtfToClient(const uint64_t &guid, const uint8_t &dir);
    void SendSpellAckToClient(uint64_t role_guid, uint16_t id, int32_t errcode, const char* errmsg, uint16_t idx);
    void SendReloginAckToClient(int32_t errcode, const char *errmsg);
    static void SendLogoutReqToLS(uint32_t sessionid, uint32_t token, uint8_t info);
    static void SendUpdateOnlineStateToLS(uint64_t roleid, uint32_t token, uint8_t state);
    static void SendSyncSessionIDToMS(uint64_t role_guid, uint32_t token, uint32_t cl2gs_sessid);
    static void SendUpdatePlayerStatus(uint64_t guid);

    uint64_t GetPlayerGUID() { return m_spSessionContext ? m_spSessionContext->nPlayerGUID : 0; }
    uint64_t GetRoleGUID() { return m_spSessionContext ? m_spSessionContext->nRoleGUID : 0; }
    uint32_t GetToken() { return m_spSessionContext ? m_spSessionContext->nToken : 0; }
    bool IsLoggedIn() { return m_spSessionContext ? (m_spSessionContext->nOnlineState == online_state_logged_in) : false; }
    void SetOnlineState(online_state state) { if (m_spSessionContext) m_spSessionContext->nOnlineState = state; }

    void StartReserveContextTimer();
    void StopReserveContextTimer(SPSessionContext &context);

    bool MaxClientReached();
    bool IsGMAccount(uint64_t userid);

private:
    SPSessionContext m_spSessionContext;
};
