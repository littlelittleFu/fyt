#pragma once
#include "Session.h"

class SessionDB2CS : public Session
{
public:
	SessionDB2CS();
	~SessionDB2CS();

	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual void DoHeartBeat();

private:
    void HandleCenterServMsg(uint16_t protoid, void* pData);
    void HandleCenterServMsg_HeartBeatReq(void *pData);
	void HandleCenterServMsg_GetRoleDataReq(void* pData);
	void HandleCenterServMsg_DeleteItemReq(void* pData);
	void HandleCenterServMsg_InsertItemReq(void* pData);
	void HandleCenterServMsg_UpdateItemReq(void* pData);

    void HandleGateServMsg(uint16_t protoid, void *pData);
    void HandleGateServMsg_GetRoleListReq(void *pData);
    void HandleGateServMsg_CreateRoleReq(void* pData);
    void HandleGateServMsg_DeleteRoleReq(void *pData);
    void HandleGateServMsg_RestoreRoleReq(void* pData);
    void HandleGateServMsg_UpdateOnlineState(void *pData);

    void HandleMapServMsg(uint16_t protoid, void* pData);
    void HandleMapServMsg_SyncRoleInfoReq(void *pData);
    void HandleMapServMsg_SyncRoleDynAttrs(void *pData);
    void HandleCenterServMsg_GetConstantCfgReq(void* pData);
    void HandleCenterServMsg_SetServerStatus(void* pData);
    void HandleCenterServMsg_UpdateMallLimitInfo(void* pData);

    void HandleCenterServMsg_GetMallLimitInfoReq(void* pData);  
    void HandleCenterServMsg_DeleteMallRemainedData(void* pData);
    void HandleCenterServMsg_AddLoginIpType(void* pData);
    void HandleCenterServMsg_DelLoginIpType(void* pData);
    void HandleCenterServMsg_UpdateSupportPlayer(void* pData);
    void HandleCenterServMsg_AddLockPlayer(void* pData);
    void HandleCenterServMsg_AddLockRole(void* pData);
    void HandleCenterServMsg_DelLockPlayer(void* pData);
    void HandleCenterServMsg_DelLockRole(void* pData);
    void HandleCenterServMsg_GetProhibitChatInfo(void* pData);
    void HandleCenterServMsg_DelProhibitInfo(void* pData);
    void HandleCenterServMsg_AddProhibitInfo(void* pData);
    void HandleMapServMsg_GetTradeDelegateReq(void* pData);
    void HandleMapServMsg_GetTradeRecordsReq(void* pData);
    void HandleMapServMsg_RecordsCancelReq(void* pData);
    void HandleMapServMsg_DelegateCancelReq(void* pData);
    void HandleMapServMsg_DelegateSellCmd(void* pData);
    void HandleMapServMsg_DelegateBuyCmd(void* pData);
    void HandleMapServMsg_GetMailAttachmentReq(void* pData);

    void HandleMapServMsg_GetGuildsReq(void *pData);
    void HandleMapServMsg_GetGuildMembersReq(void *pData);
    void HandleMapServMsg_GetGuildApplicantsReq(void *pData);
    void HandleMapServMsg_GetCustVarReq(void *pData);
    void HandleMapServMsg_SetCustVar(void *pData);
    void HandleMapServMsg_SyncGuildApplicant(void *pData);
    void HandleMapServMsg_SyncGuildMember(void *pData);
    void HandleMapServMsg_SyncGuildInfo(void *pData);
    void HandleMapServMsg_AddSysNewMail(void* pData);
    void HandleMapServMsg_SyncMailInfo(void* pData);
    void HandleMapServMsg_SyncMailInfoStatus(void* pData);
    void HandleMapServMsg_MailDelReq(void* pData);
    void HandleMapServMsg_SyncGuildRelation(void *pData);
    void HandleMapServMsg_SyncItemDynAttrs(void *pData);
    void HandleMapServMsg_GetWantedListReq(void *pData);
    void HandleMapServMsg_PostBountyReq(void *pData);
    void HandleMapServMsg_CheckRoleExistenceReq(void *pData);
    void HandleMapServMsg_SaveGoodsIssueRecord(void *pData);
    void HandleMapServMsg_GoodsIssuedNtf(void *pData);
    void HandleMapServMsg_SyncGoodsPostRecord(void* pData);
    void HandleMapServMsg_SetRebateMoneyUsedNtf(void* pData);
    void HandleMapServMsg_PlayerSetNameReq(void* pData);
    void HandleMapServMsg_ItemTip(void* pData);
    void HandleMapServMsg_AddTitle(void* pData);
    void HandleMapServMsg_DelTitle(void* pData);
    void HandleMapServMsg_ChangeTitleWearType(void* pData);
    void HandleMapServMsg_SyncTitleInfo(void* pData);
    void HandleMapServMsg_AddPlayerProhibitChat(void* pData);
    void HandleMapServMsg_DelPlayerProhibitChat(void* pData);
    void HandleMapServMsg_RumGMCmd(void *pData);
    void HandleMapServMsg_SyncCustList(void* pData);
    void HandleMapServMsg_GetCustListReq(void* pData);
    void HandleMapServMsg_SyncPlayerGender(void* pData);

    void HandleCenterServMsg_GetTopListReq(void* pData);
	void HandleCenterServMsg_GetRoleInfoReq(void* pData);
	void HandleCenterServMsg_DeleteRoleInfoReq(void* pData);
	void HandleCenterServMsg_ClearRoleInfoReq(void* pData);
	void HandleCenterServMsg_InsertRoleInfoReq(void* pData);
	void HandleCenterServMsg_UpdateRoleInfoReq(void* pData);
    void HandleCenterServMsg_SyncSkillReq(void *pData);
    void HandleCenterServMsg_SyncBuffReq(void *pData);
    void HandleCenterServMsg_SyncQuestReq(void *pData);
    void HandleCenterServMsg_SyncPlayerCustVar(void *pData);
    void HandleCenterServMsg_SyncItemCustVar(void *pData);
    void HandleCenterServMsg_SyncQuickBarSet(void* pData);
    void HandleCenterServMsg_SyncDgnBindInfoSet(void* pData);
    void HandleCenterServMsg_GetMailInfo(void* pData);
    void HandleCenterServMsg_MarketSellAck(void* pData);
    void HandleCenterServMsg_MarketBuyAck(void* pData);
    void HandleCenterServMsg_SynAuctionInfo(void* pData);
    void HandleCenterServMsg_AuctionHouseReq(void* pData);
    void HandleCenterServMsg_EnterMSNtf(void* pData);
    void HandleCenterServMsg_SyncRoleInfoFromCS(void* pData);
    void HandleCenterServMsg_UpdateTables(void *pData);
    void HandleCenterServMsg_GetMailAttachmentAck(void* pData);
};
