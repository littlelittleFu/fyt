#pragma once
#include "Session.h"
#include "mail_table.h"
#include "AuctionMgr.h"
#include "CenterServer.h"
struct ITEM_INFO; 
class SessionCS2MS : public Session
{
public:
	SessionCS2MS();
	~SessionCS2MS();

	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual void DoHeartBeat();

protected:
	void HandleMapServMsg(uint16_t protoid, void* pData);
	void HandleMapServMsg_HeartBeatReq(void* pData);
	void HandleMapServMsg_GetInfoReq(void* pData);
	void HandleMapServMsg_EnterMSAck(void* pData);
	void HandleMapServMsg_EnterMSNtf(void* pData);
	void HandleMapServMsg_ItemAck(void* pData);
	void HandleMapServMsg_SyncBuffReq(void* pData);
	void HandleMapServMsg_SyncSkillReq(void* pData);
	void HandleMapServMsg_SendSyncItemNtf(void* pData);
	void HandleMapServMsg_SendDelItemNtf(void* pData);
	void HandleMapServMsg_GetRoleInfoReq(void* pData);
	void HandleMapServMsg_ClearRoleInfoReq(void* pData);
	void HandleMapServMsg_DeleteRoleInfoReq(void* pData);
	void HandleMapServMsg_InsertRoleInfoReq(void* pData);
	void HandleMapServMsg_UpdateRoleInfoReq(void* pData);
	void HandleMapServMsg_SyncRoleInfoReq(void* pData);
	void HandleMapServMsg_SyncQuestReq(void* pData);
	void HandleMapServMsg_GetConstantCfgReq(void* pData);
	void HandleMapServMsg_UpdateConstantCfgReq(void* pData);
	void HandleMapServMsg_SetServerStatus(void* pData);
	void HandleMapServMsg_UpdateMallLimitInfo(void* pData);
	void HandleMapServMsg_GetMallLimitInfoReq(void* pData);	
	void HandleMapServMsg_DeleteMallRemainedData(void* pData);
	void HandleMapServMsg_AddLoginIpType(void* pData);
	void HandleMapServMsg_DelLoginIpType(void* pData);
	void HandleMapServMsg_UpdateSupportPlayer(void* pData);
	void HandleMapServMsg_AddLockPlayer(void* pData);
	void HandleMapServMsg_AddLockRole(void* pData);
	void HandleMapServMsg_DelRole(void* pData);
	void HandleMapServMsg_SyncCustList(void* pData);
	void HandleMapServMsg_GetCustListReq(void* pData);
	void HandleMapServMsg_DelLockPlayer(void* pData);
	void HandleMapServMsg_DelLockRole(void* pData);
	void HandleMapServMsg_GetProhibitChatInfoReq(void* pData);
	void HandleMapServMsg_DelProhibitInfo(void* pData);
	void HandleMapServMsg_AddProhibitChatInfo(void* pData);
    void HandleMapServMsg_GetTradeDelegateReq(void* pData);
	void HandleMapServMsg_GetTradeRecordsReq(void* pData);
	void HandleMapServMsg_DelegateCancelReq(void* pData);
	void HandleMapServMsg_DelegateSellCmd(void* pData);
	void HandleMapServMsg_DelegateBuyCmd(void* pData);
	void HandleMapServMsg_MarketSellCmd(void* pData);
	void HandleMapServMsg_MarketBuyCmd(void* pData);
	void HandleMapServMsg_GetMailAttachmentReq(void* pData);

	void HandleMapServMsg_GetGuildsReq(void* pData);
	void HandleMapServMsg_GetGuildMembersReq(void* pData);
	void HandleMapServMsg_GetGuildApplicantsReq(void* pData);
	void HandleMapServMsg_SyncPlayerCustVar(void* pData);
	void HandleMapServMsg_SyncPlayerItemCustVar(void* pData);
	void HandleMapServMsg_GetCustVarReq(void* pData);
	void HandleMapServMsg_SetCustVar(void* pData);
	void HandleMapServMsg_QuickBarSet(void* pData);
	void HandleMapServMsg_DgnBindInfo(void* pData);
	void HandleMapServMsg_GetTopListAck(void* pData);
	void HandleMapServMsg_SyncGuildApplicant(void* pData);
	void HandleMapServMsg_SyncGuildMember(void* pData);
	void HandleMapServMsg_SyncGuildInfo(void* pData);
	void HandleMapServMsg_AddSysNewMail(void* pData);
	void HandleMapServMsg_SyncMailInfo(void* pData);
	void HandleMapServMsg_SyncMailInfoStatus(void* pData);
	void HandleMapServMsg_DelMailReq(void* pData);
    void HandleMapServMsg_SyncGuildRelation(void *pData);
    void HandleMapServMsg_SyncItemDynAttrs(void *pData);
	void HandleMapServMsg_SyncRoleDynAttrs(void* pData);
	void HandleMapServMsg_SynAuctionInfo(void* pData);
	void HandleMapServMsg_GetAuctionFinishedInfoReq(void* pData);
	void HandleMapServMsg_GetAuctionHouseReq(void* pData);
    void HandleMapServMsg_GetWantedListReq(void *pData);
    void HandleMapServMsg_PostBountyReq(void *pData);
    void HandleMapServMsg_CheckRoleExistenceReq(void *pData);
    void HandleMapServMsg_SaveGoodsIssueRecord(void *pData);
    void HandleMapServMsg_GoodsIssuedNtf(void *pData);
	void HandleMapServMsg_GoodsPostRecord(void* pData);
	void HandleMapServMsg_SetPlayerGender(void* pData);

	void HandleMapServMsg_RebateMoneyUsedNtf(void* pData);
	void HandleMapServMsg_PlayerSetNameReq(void* pData);
	void HandleMapServMsg_ItemTip(void* pData);
	void HandleMapServMsg_MonitorChatMsg(void* pData);
	void HandleMapServMsg_AddTitle(void* pData);
	void HandleMapServMsg_DelTitle(void* pData);
	void HandleMapServMsg_ChangeTitleWearType(void* pData);
	void HandleMapServMsg_SyncTitleInfo(void* pData);
	void HandleMapServMsg_AddActivationCodeTask(void* pData);
	void HandleMapServMsg_AddPlayerProhibitChat(void* pData);
	void HandleMapServMsg_DelPlayerProhibitChat(void* pData);
    void HandleMapServMsg_RunGMCmd(void *pData);

    void HandleGateServMsg(uint16_t protoid, void *pData);
    void HandleGateServMsg_UpdateOnlineState(void *pData);

	void HandleCenterServMsg(uint16_t protoid, void* pData);
	void HandleCenterServMsg_GetMailAttachmentAck(void* pData);

	void HandleMapServMsg_RunLuaHttp(void* pData);



	bool ComposeHttpRequest(char* buf, int bufsz, const char* custom);
	static size_t CURLWriteCallback(void* data, size_t size, size_t nmemb, void* userp);
	void ParseResult(std::vector<char>& resp, const char* callBackFunc);
};
