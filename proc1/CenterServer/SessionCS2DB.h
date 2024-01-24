#pragma once

#include "Session.h"

class SessionCS2DB : public Session
{
public:
	SessionCS2DB();
	~SessionCS2DB();

	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual void DoHeartBeat();

private:
    void HandleCenterServMsg(uint16_t protoid, void* pData);
    void HandleCenterServMsg_HeartBeatAck(void *pData);
	void HandleCenterServMsg_GetRoleDataAck(void* pData);
	void HandleCenterServMsg_GetItemAck(void* pData);
	void HandleCenterServMsg_GetRoleInfoAck(void* pData);
    void HandleCenterServMsg_RoleExtraInfoNtf(void *pData);
    void HandleCenterServMsg_GetGuildsAck(void *pData);
    void HandleCenterServMsg_GetGuildMembersAck(void *pData);
    void HandleCenterServMsg_GetGuildApplicantsAck(void *pData);
    void HandleCenterServMsg_GetConstantCfgAck(void* pData);
    void HandleCenterServMsg_GetTradeBuyDelegateAck(void* pData);
    void HandleCenterServMsg_GetTradeSellDelegateAck(void* pData);
    void HandleCenterServMsg_GetTradeRecordsAck(void* pData);
    void HandleCenterServMsg_DelegateCancelAck(void* pData);
    void HandleCenterServMsg_DelegateBuyAck(void* pData);
    void HandleCenterServMsg_DelegateSellAck(void* pData);
    void HandleCenterServMsg_GetMailAttachmentAck(void* pData);
    void HandleCenterServMsg_AuctionHouseAck(void* pData);
    void HandleCenterServMsg_GetMallLimitInfoAck(void* pData);

    void HandleGateServMsg(uint16_t protoid, void *pData);
    void HandleGateServMsg_GetRoleListAck(void *pData);
    void HandleGateServMsg_CreateRoleAck(void* pData);
    void HandleGateServMsg_DeleteRoleAck(void *pData);
    void HandleGateServMsg_RestoreRoleAck(void* pData);
    void HandleGateServMsg_ItemTipNtf(void* pData);

    void HandleMapServMsg(uint16_t protoid, void *pData);
    void HandleMapServMsg_GetSkillAck(void *pData);
    void HandleMapServMsg_GetBuffAck(void *pData);
    void HandleMapServMsg_DelMailAck(void* pData);
    void HandleMapServMsg_GetWantedListAck(void *pData);
    void HandleMapServMsg_PostBountyAck(void *pData);
    void HandleMapServMsg_CheckRoleExistenceAck(void *pData);
    void HandleMapServMsg_UpdateSupportPlayer(void* pData);

    void HandleDBServMsg(uint16_t protoid, void *pData);
    void HandleDBServMsg_QuestInfo(void *pData);
    void HandleDBServMsg_PlayerCustVar(void *pData);
    void HandleDBServMsg_PlayerItemCustVar(void *pData);
    void HandleDBServMsg_GetCustVarAck(void *pData);
    void HandleDBServMsg_QuickBarSetNtf(void* pData);
    void HandleDBServMsg_DgnBindInfoNtf(void* pData);
    void HandleDBServMsg_GetTopListAck(void* pData);
    void HandleDBServMsg_AddMailAck(void* pData);
    void HandleDBServMsg_GetMailInfoAck(void* pData);
    void HandleDBServMsg_ItemDynAttrNtf(void *pData);
    void HandleDBServMsg_RoleDynAttrNtf(void* pData);
    void HandleDBServMsg_GetProhibitChatAck(void* pData);
    void HandleDBServMsg_GoodsNotIssuedRecordsNtf(void *pData);
    void HandleDBServMsg_RebateMoneyNotUsedRecordNtf(void* pData);
    void HandleDBServMsg_PlayerSetNameAck(void* pData);
    void HandleDBServMsg_GetTitleInfoAck(void* pData);
    void HandleDBServMsg_DelLockRoleAck(void* pData);
    void HandleDBServMsg_GetCustListInfoAck(void* pData);
    void HandleDBServMsg_GoodsNotPostRecordsNtf(void* pData);
};