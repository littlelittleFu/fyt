#pragma once
#include "Session.h"
#include "SessionContextMgr.h"

class SessionGS2MS : public Session
{
public:
	SessionGS2MS();
	~SessionGS2MS();
    //std::map<int, int> msgmap;

	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual void DoHeartBeat();

	void HandleMapServMsg_TeamNtf(void* pData);
	void HandleMapServMsg_TeamLeaveNtf(void* pData);
	void HandleMapServMsg_TeamInviteNtf(void* pData);
	void HandleMapServMsg_TeamJoinNtf(void* pData);
	void HandleMapServMsg_TeamLeaderNtf(void* pData);
	void HandleMapServMsg_GetAroundTeamAck(void* pData);
	void HandleMapServerMsg(uint16_t protoid, void* pData);
    void HandleMapServerMsg_SpellNtf(void* pData);
    void HandleMapServerMsg_ErrorAck(void *pData);
    void HandleMapServerMsg_GMErrorAck(void *pData);
    void HandleMapServerMsg_AttrShowNtfEx2(void *pData);
    void HandleMapServerMsg_ObjDieNtf(void *pData);
    void HandleMapServerMsg_RoleAttrNtf(void *pData);
	void HandleMapServerMsg_RoleAttrExtNtf(void* pData);
    void HandleMapServMsg_RoleDynAttrNtf(void* pData);
    void HandleMapServMsg_RoleCustVarNtf(void* pData);
    void HandleMapServMsg_PlayerAppearNtf(void *pData);
	void HandleMapServMsg_MonsterAppearNtf(void* pData);
    void HandleMapServMsg_SkillAddAck(void* pData);
    void HandleMapServMsg_BuffAddAck(void *pData);
    void HandleMapServMsg_BuffDestroyAck(void *pData);
	void HandleMapServMsg_ItemAppearNtf4(void* pData);
    void HandleMapServMsg_RunClientScript(void *pData);
	void HandleMapServMsg_EnterMSAck(void* pData);
	void HandleMapServMsg_EnterMSNtf(void* pData);
    void HandleMapServMsg_SysMsgNtf(void *pData);
    void HandleMapServMsg_NpcAppearNtf(void *pData);
    void HandleMapServMsg_TradeNpcShopNtf(void *pData);
    void HandleMapServMsg_QuestNpcTalkAck(void *pData);
    void HandleMapServMsg_QuestTimeoutNtf(void *pData);
    void HandleMapServMsg_QuestUpdateNtf(void *pData);
    void HandleMapServMsg_QuestDropNtf(void *pData);
    void HandleMapServMsg_QuestStateNtf(void *pData);
    void HandleMapServMsg_QuestNpcStateNtf(void *pData);
    void HandleMapServMsg_RoleAttrExtRefNtf(void *pData);
    void HandleMapServMsg_LevelUpNtf(void *pData);
    void HandleMapServMsg_RoleAppNtf(void *pData);
    void HandleMapServMsg_FamilyNoticeAck(void *pData);
    void HandleMapServMsg_FamilyMembersAck(void *pData);
    void HandleMapServMsg_FamilyEnemyAck(void *pData);
    void HandleMapServMsg_FamilyAllyAck(void *pData);
    void HandleMapServMsg_FamilyJoinListAck(void *pData);
    void HandleMapServMsg_FamilyBaseInfoAck(void *pData);
    void HandleMapServMsg_FamilyListNtfAck(void *pData);
    void HandleMapServMsg_PlayerQueryNtf(void *pData);
    void HandleMapServMsg_MsgNtf(void* pData);
    void HandleMapServMsg_PopDlgMsgNtf(void *pData);
    void HandleMapServMsg_PlayerFamilyChangeNtf(void *pData);
    void HandleMapServMsg_CancelFamilyJoinAck(void *pData);
    void HandleMapServMsg_FamilyLeaveNtf(void *pData);
    void HandleMapServMsg_FamilyInfoNtf(void *pData);
    void HandleMapServMsg_MissNtf(void *pData);
    void HandleMapServMsg_RecordsMineAck(void* pData);
    void HandleMapServMsg_DelegateMineAck(void* pData);
    void HandleMapServMsg_DelegateSellListAck(void* pData);
    void HandleMapServMsg_DelegateBuyListAck(void* pData);
    void HandleMapServMsg_DeleteSkillAck(void* pData);
    void HandleMapServMsg_SkillStatusNtf(void *pData);
    void HandleMapServMsg_SkillPropPermanetChangedNtf(void *pData);
    void HandleMapServMsg_SkillProficiencyNtf(void *pData);
    void HandleMapServMsg_RoleInfoChangeNtf(void* pData);
    void HandleMapServMsg_ItemPickupNtf(void *pData);
    void HandleMapServMsg_AutoPickupSettingsNtf(void *pData);
    void HandleMapServMsg_StartDigAck(void *pData);
    void HandleMapServMsg_StopDigNtf(void *pData);
    void HandleMapServMsg_RoleAppearNtf(void *pData);
    void HandleMapServMsg_VerifyBuyItemInfoAck(void *pData);
    void HandleMapServMsg_MonsterBackNtf(void* pData);
    void HandleMapServMsg_SetAutoModeReq(void *pData);
    void HandleMapServMsg_SceneItemUpdateNtf(void *pData);

    void HandleGateServMsg(uint16_t protoid, void* pData);
	void HandleGateServMsg_SessionIDNtf(void* pData);
    void HandleGateServMsg_HeartBeatAck(void *pData);
    void HandleGateServMsg_MoveAck(void *pData);
    void HandleGateServMsg_TurnNtf(void *pData);
    void HandleGateServMsg_SpellAck(void *pData);
    void HandleGateServMsg_SkillSwitchAck(void *pData);
    void HandleGateServMsg_RunServScriptAck(void *pData);
    void HandleGateServMsg_RelationChatAck(void *pData);
    void HandleGateServMsg_RelationChatNtf(void *pData);
    void HandleGateServMsg_PrivateChatNtf(void *pData);
    void HandleGateServMsg_SpeakerMsgNtf(void *pData);
	void HandleGateServMsg_TradeMallListAck(void* pData);
    void HandleGateServMsg_QuestQueryCanAcceptNtf(void *pData);
    void HandleGateServMsg_QuestAddNtf(void *pData);

	void HandleMSPlayerMoveNtfMsg(void* pData);
	void HandleMSObjDisAppearNtfMsg(void* pData);

	void HandleMSItemUpdateMsg(void* pData);
	void HandleMSItemAckMsg(void* pData);
	void HandleMSItemDestroyMsg(void* pData);
	void HandleGateServMsg_ExitGSMsg(void* pData);
	void HandleMSItemAttrNtfMsg(void* pData);

    void HandleMapServMsg_QuickBarSetNtf(void* pData);
    void HandleMapServMsg_GlobalNtf(void* pData);
    void HandleMapServMsg_NewMailNtf(void* pData);
    void HandleMapServMsg_GetMailListAck(void* pData);
    void HandleMapServMsg_DeleteMailAck(void* pData);
    void HandleMapServMsg_OpenMailAck(void* pData);
    void HandleMapServMsg_MailAttachmentGetAck(void* pData);
    void HandleMapServMsg_ShabakOwnerNtf(void *pData);
    void HandleMapServMsg_ShabakLossNtf(void *pData);
    void HandleMapServMsg_ShabakEngageNtf(void *pData);
    void HandleMapServMsg_ShabakEndNtf(void *pData);
    void HandleMapServMsg_MoveNtfEx(void *pData);
    void HandleMapServMsg_TurnNtf(void *pData);
    void HandleMapServMsg_SendGoodsPostRecordToClient(void* pData);
    void HandleMapServMsg_EffectAppearNtf(void* pData);
    void HandleMapServMsg_EffectDisAppearNtf(void* pData);



    void HandleMapServMsg_SysMsgNtf2(void* pData);
    void HandleMapServMsg_SceneDialogNtf(void* pData);
    void HandleMapServMsg_ScrollText(void* pData);
    void HandleMapServMsg_TradeListUpdate(void* pData);
    void HandleMapServMsg_KickOutRole(void* pData);
    void HandleMapServMsg_GetNpcPosAck(void* pData);
    void HandleMapServMsg_RunningFamilyWarNtf(void* pData);
    void HandleMapServMsg_SetServerStatus(void* pData);
    void HandleMapServMsg_MonsterPursureStatusChangedNtf(void* pData);
    void HandleMapServMsg_PlayerSetNameNtf(void* pData);
    void HandleMapServMsg_ItemTipNtf(void* pData);
    void HandleMapServMsg_CustMsgNtf(void* pData);
    void HandleMapServMsg_TitleAddAck(void* pData);
    void HandleMapServMsg_TitleDelAck(void* pData);
    void HandleMapServMsg_TitleList(void* pData);
    void HandleMapServMsg_TitleWearNtf(void* pData);
    void HandleMapServMsg_TitleUnWearNtf(void* pData);
};
