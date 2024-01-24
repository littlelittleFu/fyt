#pragma once
#include "Session.h"
#include "Player.h"
#include "ProtoMS.h"
#include "ITimeHelper.h"

class SessionMS2CS : public Session
{
public:
	SessionMS2CS();
	~SessionMS2CS();

	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual void DoHeartBeat();

private:
    void HandleGateServMsg(uint16_t protoid, void* pData);
    void HandleGateServMsg_LogoutReq(void* pData);
    void HandleGateServMsg_UpdateOnlineState(void *pData);
    void HandleGateServMsg_DeleteRoleAck(void *pData);
    void HandleGateServMsg_ItemTipNtf(void* pData);

	void HandleCSMessage(uint16_t protoid, void* _pData);
	void HandleCSEnterMSReq(void* _pData);
	void HandleCSEnterMSNtf(void* pData);
	void HandleCSSendItemNtf(void* _pData);
    void HandleCenterServMsg_GetGuildsAck(void *pData);
    void HandleCenterServMsg_GetGuildMembersAck(void *pData);
    void HandleCenterServMsg_GetGuildApplicantsAck(void *pData);
    void HandleCenterServMsg_QuickBarSetNtf(void* pData);
    void HandleCenterServMsg_DgnBindInfoNtf(void* pData);
    void HandleCenterServMsg_GlobalNtf(void* pData);
    void HandleCenterServMsg_SyncGMModLevel(void* pData);
    void HandleCenterServMsg_GetConstantCfgAck(void* pData);
    void HandleCenterServMsg_GetMallLimitInfoSingleFromCS(void* pData);
    void HandleCenterServMsg_UpdateMallList(void* pData);
    void HandleCenterServMsg_ActivationCodeAck(void* pData);
    void HandleCenterServMsg_GetTradeBuyDelegateAck(void* pData);
    void HandleCenterServMsg_GetTradeSellDelegateAck(void* pData);
    void HandleCenterServMsg_GetTradeRecordsAck(void* pData);
    void HandleCenterServMsg_RecordsCancelAck(void* pData);
    void HandleCenterServMsg_DelegateCancelAck(void* pData);
    void HandleCenterServMsg_DelegateBuyAck(void* pData);
    void HandleCenterServMsg_DelegateSellAck(void* pData);
    void HandleCenterServMsg_MarketSellAck(void* pData);
    void HandleCenterServMsg_MarketBuyAck(void* pData);
    void HandleCenterServMsg_GetMailAttachmentAck(void* pData);
    void HandleCenterServMsg_GetAuctionGetFinishedInfoReq(void* pData);
    void HandleCenterServMsg_HandleRunGMCmdAck(void* pData);

    void HandleMapServMsg(uint16_t protoid, void *pData);
    void HandleMapServMsg_HeartBeatAck(void *pData);
    void HandleMapServMsg_GetSkillAck(void *pData);
    void HandleMapServMsg_GetBuffAck(void *pData);
	void HandleMapServMsg_GetRoleInfoAck(void* pData);
    void HandleMapServMsg_DelMailAck(void* pData);
    void HandleMapServMsg_GetAuctionHouseAck(void* pData);
    void HandleMapServMsg_GetMallLimitInfoAck(void* pData);
    void HandleMapServMsg_GetWantedListAck(void *pData);
    void HandleMapServMsg_PostBountyAck(void *pData);
    void HandleMapServMsg_CheckRoleExistenceAck(void *pData);
    void HandleCenterServMsg_UpdateSupportPlayer(void* pData);

    void HandleDBServMsg(uint16_t protoid, void *pData);
    void HandleDBServMsg_PlayerCustVar(void *pData);
    void HandleDBServMsg_PlayerItemCustVar(void *pData);
    void HandleDBServMsg_GetCustVarAck(void *pData);
    void HandleDBServMsg_AddMailAck(void *pData);
    void HandleDBServMsg_GetMailInfoAck(void* pData);
    void HandleDBServMsg_ItemDynAttrNtf(void *pData);
    void HandleDBServMsg_RoleDynAttrNtf(void* pData);
    void HandleDBServMsg_GetProhibitInfoAck(void* pData);
    void HandleDBServMsg_GoodsNotIssuedRecordsNtf(void *pData);
    void HandleDBServMsg_RebateMoneyNotUsedRecordNtf(void *pData);
    void HandleDBServMsg_PlayerSetNameAck(void* pData);
    void HandleDBServMsg_PlayerGetTitleInfo(void* pData);
    void HandleDBServMsg_GetCustListInfoAck(void* pData);
    void HandleMapServMsg_CustomHttpAck(void* pData);
    void HandleDBServMsg_GoodsNotPostRecordsNtf(void* pData);


public:
    void SendGlobalNtfToClient(uint32_t token = 0);
private:
    void SendGetCustVarReqToCS();
    void SendGetGuildsReqToCS();
    void SendGetGuildMembersReqToCS();
    void SendGetGuildApplicantsReqToCS();
    void SendGetTradeDelegateReqToCS();
    void SendGetAuctionHouseReqRoCS();
    void SendGetConstantCfgReqToCS();
    void SendGetMallLimitInfoReqToCS();
    void SendGetProhibitChatInfoReqToCS();
    void SendGetWantedListReqToCS();
    void SendGetCustListReqToCS();

    void OnCustVarReady();
    void OnGuildsReady();
    void OnDataReady();

private:
    bool mCustVarReady  = false;
    bool mGuildsRead    = false;
};
