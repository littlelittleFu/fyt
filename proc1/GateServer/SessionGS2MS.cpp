#include "stdafx.h"
#include "SessionGS2MS.h"
#include "SessionGS2CL.h"
#include "ILogHelper.h"
#include "ProtoMS.h"
#include "ProtoClient.h"
#include "ProtoClient2.h"
#include "ProtoClient7.h"
#include "CNetManager.h"
#include "ProtoGS.h"
#include "ProtoClient3.h"
#include "SessionGS2CL.h"
#include <SessionFactory.h>
#include "SessionContextMgr.h"
#include <cassert>
#include "GateServer.h"


SessionGS2MS::SessionGS2MS()
{

}

SessionGS2MS::~SessionGS2MS()
{

}

void SessionGS2MS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionGS2MS::OnLost()
{
	LOG_NORMAL("SessionMS2GS OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
	//DoClose();
}

void SessionGS2MS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    MsgCostStat::GetInstance()->BeginHandleMsg();

    OnHeartBeat();
	//msgmap[moduleid * 1000 + protoid] ++;
	switch (moduleid) {
		case MODULE_TYPE_MS:
			HandleMapServerMsg(protoid, _pData);
			break;

		case MODULE_TYPE_GS:
			HandleGateServMsg(protoid, _pData);
			break;

		default:
			LOG_WARN("Unhandled moduleid: %d", moduleid);
			break;
	}

    MsgCostStat::GetInstance()->EndHandleMsg(moduleid, protoid);
}

void SessionGS2MS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionGS2MS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
	//看10秒内发送的消息数量
	/*static int maxDeltaTime = 0;
	maxDeltaTime += _Delta;
	if (maxDeltaTime > 10000)
	{
		for (auto itr : msgmap)
		{
			LOG_ERROR("msgmap:%d,%d", itr.first,itr.second);
		}
		msgmap.clear();
		maxDeltaTime = 0;
	}*/
}

void SessionGS2MS::DoHeartBeat()
{
	ProtoGS_HeartBeatReq req;
	SendPkg(&req, sizeof(req));
}

void SessionGS2MS::HandleMapServMsg_TeamNtf(void* pData)
{
	LOG_NORMAL("SessionMS2GS::HandleMapServMsg_TeamNtf protoid: ");
	ProtoMS_TeamNtf* pTeamNtf = (ProtoMS_TeamNtf*)pData;
	ProtoClient2_TeamNtf ntf;
	ntf.info = pTeamNtf->info;
	ISession* pGateServ = CNetManager::GetInstance()->GetSessionByID(pTeamNtf->session_id);
	if (!pGateServ) {
		LOG_ERROR("pGateServ is null");
		return;
	}
	pGateServ->SendPkg(&ntf, sizeof(ntf));
}

void SessionGS2MS::HandleMapServMsg_TeamLeaveNtf(void* pData)
{
	LOG_NORMAL("SessionMS2GS::HandleMapServMsg_TeamLeaveNtf protoid: ");
	ProtoMS_TeamLeaveNtf* pTeamNtf = (ProtoMS_TeamLeaveNtf*)pData;
	ProtoClient2_TeamLeaveNtf ntf;
	ntf.player_guid = pTeamNtf->player_guid;
	ntf.type = pTeamNtf->type;
	ISession* pGateServ = CNetManager::GetInstance()->GetSessionByID(pTeamNtf->session_id);
	if (!pGateServ) {
		LOG_ERROR("pGateServ is null");
		return;
	}
	pGateServ->SendPkg(&ntf, sizeof(ntf));
}

void SessionGS2MS::HandleMapServMsg_TeamInviteNtf(void* pData)
{
	LOG_NORMAL("SessionMS2GS::HandleMapServMsg_TeamInviteNtf protoid: ");
	ProtoMS_TeamInviteNtf* pTeamNtf = (ProtoMS_TeamInviteNtf*)pData;
	ProtoClient2_TeamInviteNtf ntf;
	ntf.exist = pTeamNtf->exist;
	ntf.num = pTeamNtf->num;
	ntf.info[0] = pTeamNtf->info[0];
	memcpy(ntf.inviter_name, pTeamNtf->inviter_name,strlen(pTeamNtf->inviter_name)+1);
	ISession* pGateServ = CNetManager::GetInstance()->GetSessionByID(pTeamNtf->session_id);
	if (!pGateServ) {
		LOG_ERROR("pGateServ is null");
		return;
	}
	pGateServ->SendPkg(&ntf, sizeof(ntf));
}

void SessionGS2MS::HandleMapServMsg_TeamJoinNtf(void* pData)
{
	LOG_NORMAL("SessionMS2GS::HandleMapServMsg_TeamJoinNtf protoid: ");
	ProtoMS_TeamJoinNtf* pTeamNtf = (ProtoMS_TeamJoinNtf*)pData;
	ProtoClient2_TeamJoinNtf ntf;
	memcpy(ntf.joiner, pTeamNtf->joiner, strlen(pTeamNtf->joiner) + 1);
	ISession* pGateServ = CNetManager::GetInstance()->GetSessionByID(pTeamNtf->session_id);
	if (!pGateServ) {
		LOG_ERROR("pGateServ is null");
		return;
	}
	pGateServ->SendPkg(&ntf, sizeof(ntf));
}

void SessionGS2MS::HandleMapServMsg_TeamLeaderNtf(void* pData)
{
	LOG_NORMAL("SessionMS2GS::HandleMapServMsg_TeamLeaderNtf protoid: ");
	ProtoMS_TeamLeaderNtf* pTeamNtf = (ProtoMS_TeamLeaderNtf*)pData;
	ProtoClient2_TeamLeaderNtf ntf;
	ntf.leader_guid = pTeamNtf->leader_guid;
	ISession* pGateServ = CNetManager::GetInstance()->GetSessionByID(pTeamNtf->session_id);
	if (!pGateServ) {
		LOG_ERROR("pGateServ is null");
		return;
	}
	pGateServ->SendPkg(&ntf, sizeof(ntf));
}

void SessionGS2MS::HandleMapServMsg_GetAroundTeamAck(void* pData)
{
	LOG_NORMAL("SessionMS2GS::HandleMapServMsg_GetAroundTeamAck protoid: ");
	ProtoMS_GetAroundTeamAck* pTeamNtf = (ProtoMS_GetAroundTeamAck*)pData;
	ProtoClient3_GetAroundTeamAck ack;

	ack.list_size = pTeamNtf->list_size;
	for (size_t i = 0; i < ack.list_size; ++i)
	{
		//memcpy(ack.list_data, pTeamNtf->inviter_name, strlen(pTeamNtf->inviter_name) + 1);
		ack.list_data[i] = pTeamNtf->list_data[i];
	}

	ISession* pGateServ = CNetManager::GetInstance()->GetSessionByID(pTeamNtf->session_id);
	if (!pGateServ) {
		LOG_ERROR("pGateServ is null");
		return;
	}
	pGateServ->SendPkg(&ack, sizeof(ack));
}

void SessionGS2MS::HandleMapServerMsg(uint16_t protoid, void* pData)
{
	BEGIN_MSG_HANDLER()
		HANDLE_MSG(PROTO_MS_GET_ARROUND_TEAM_ACK, HandleMapServMsg_GetAroundTeamAck)
		HANDLE_MSG(PROTO_MS_TEAM_NTF, HandleMapServMsg_TeamNtf)
		HANDLE_MSG(PROTO_MS_MISS_TEAM_NTF, HandleMapServMsg_TeamLeaveNtf)
		HANDLE_MSG(PROTO_MS_TEAM_INVITE_NTF, HandleMapServMsg_TeamInviteNtf)
		HANDLE_MSG(PROTO_MS_TEAM_JOIN_NTF, HandleMapServMsg_TeamJoinNtf)
		HANDLE_MSG(PROTO_MS_TEAM_LEADER_NTF, HandleMapServMsg_TeamLeaderNtf)
		HANDLE_MSG(PROTO_MS_ENTER_MS_ACK, HandleMapServMsg_EnterMSAck)
		HANDLE_MSG(PROTO_MS_ENTER_MS_NTF, HandleMapServMsg_EnterMSNtf)
		HANDLE_MSG(PROTO_MS_MOVE_NTF, HandleMSPlayerMoveNtfMsg)
		HANDLE_MSG(PROTO_MS_SPELL_NTF, HandleMapServerMsg_SpellNtf)
		HANDLE_MSG(PROTO_MS_ERROR_ACK, HandleMapServerMsg_ErrorAck)
        HANDLE_MSG(PROTO_MS_GM_ERROR_ACK, HandleMapServerMsg_GMErrorAck)
		HANDLE_MSG(PROTO_MS_ATTR_SHOW_NTF2_EX2, HandleMapServerMsg_AttrShowNtfEx2)
		HANDLE_MSG(PROTO_MS_OBJDIE_NTF, HandleMapServerMsg_ObjDieNtf)
		HANDLE_MSG(PROTO_MS_DISAPPEAR_NTF, HandleMSObjDisAppearNtfMsg)
		HANDLE_MSG(PROTO_MS_PLAYER_APPEAR_NTF, HandleMapServMsg_PlayerAppearNtf)
		HANDLE_MSG(PROTO_MS_MONSTER_APPEAR_NTF6, HandleMapServMsg_MonsterAppearNtf)
		HANDLE_MSG(PROTO_MS_ITEM_DESTROY_ACK, HandleMSItemDestroyMsg)
		HANDLE_MSG(PROTO_MS_SKILL_ADD_ACK, HandleMapServMsg_SkillAddAck)
		HANDLE_MSG(PROTO_MS_BUFF_ADD_ACK, HandleMapServMsg_BuffAddAck)
		HANDLE_MSG(PROTO_MS_BUFF_DESTROY_ACK, HandleMapServMsg_BuffDestroyAck)
		HANDLE_MSG(PROTO_MS_ROLE_ATTR_NTF, HandleMapServerMsg_RoleAttrNtf)
		HANDLE_MSG(PROTO_MS_ROLE_ATTR_EXT_NTF, HandleMapServerMsg_RoleAttrExtNtf)
		HANDLE_MSG(PROTO_MS_ITEM_UPDATE_NTF, HandleMSItemUpdateMsg)
		HANDLE_MSG(PROTO_MS_ITEM_ACK, HandleMSItemAckMsg)
		HANDLE_MSG(PROTO_MS_ITEM_ATTR_NTF, HandleMSItemAttrNtfMsg)
		HANDLE_MSG(PROTO_MS_ITEM_APPEAR_NTF4, HandleMapServMsg_ItemAppearNtf4)
		HANDLE_MSG(PROTO_MS_RUN_CLIENT_SCRIPT, HandleMapServMsg_RunClientScript)
		HANDLE_MSG(PROTO_MS_SYS_MSG_NTF, HandleMapServMsg_SysMsgNtf)
		HANDLE_MSG(PROTO_MS_NPC_APPEAR_NTF, HandleMapServMsg_NpcAppearNtf)
		HANDLE_MSG(PROTO_MS_TRADE_NPC_SHOP_NTF, HandleMapServMsg_TradeNpcShopNtf)
		HANDLE_MSG(PROTO_MS_QUEST_NPC_TALK_ACK, HandleMapServMsg_QuestNpcTalkAck)
		HANDLE_MSG(PROTO_MS_QUEST_TIMEOUT_NTF, HandleMapServMsg_QuestTimeoutNtf)
		HANDLE_MSG(PROTO_MS_QUEST_UPDATE_NTF, HandleMapServMsg_QuestUpdateNtf)
		HANDLE_MSG(PROTO_MS_QUEST_DROP_NTF, HandleMapServMsg_QuestDropNtf)
		HANDLE_MSG(PROTO_MS_QUEST_STATE_NTF, HandleMapServMsg_QuestStateNtf)
		HANDLE_MSG(PROTO_MS_QUEST_NPC_STATE_NTF, HandleMapServMsg_QuestNpcStateNtf)
		HANDLE_MSG(PROTO_MS_ROLE_ATTR_EXT_REF_NTF, HandleMapServMsg_RoleAttrExtRefNtf)
		HANDLE_MSG(PROTO_MS_LEVEL_UP_NTF, HandleMapServMsg_LevelUpNtf)
		HANDLE_MSG(PROTO_MS_ROLE_APP_NTF, HandleMapServMsg_RoleAppNtf)
		HANDLE_MSG(PROTO_MS_FAMILY_NOTICE_ACK, HandleMapServMsg_FamilyNoticeAck)
		HANDLE_MSG(PROTO_MS_FAMILY_MEMBERS_ACK, HandleMapServMsg_FamilyMembersAck)
		HANDLE_MSG(PROTO_MS_FAMILY_ENEMY_ACK, HandleMapServMsg_FamilyEnemyAck)
		HANDLE_MSG(PROTO_MS_FAMILY_ALLY_ACK, HandleMapServMsg_FamilyAllyAck)
		HANDLE_MSG(PROTO_MS_FAMILY_JOIN_LIST_ACK, HandleMapServMsg_FamilyJoinListAck)
		HANDLE_MSG(PROTO_MS_FAMILY_BASE_INFO_ACK, HandleMapServMsg_FamilyBaseInfoAck)
		HANDLE_MSG(PROTO_MS_FAMILY_LIST_NTF_ACK, HandleMapServMsg_FamilyListNtfAck)
		HANDLE_MSG(PROTO_MS_PLAYER_QUERY_NTF, HandleMapServMsg_PlayerQueryNtf)
		HANDLE_MSG(PROTO_MS_QUICK_BAR_SET_NTF, HandleMapServMsg_QuickBarSetNtf)
		HANDLE_MSG(PROTO_MS_GLOBAL_NTF, HandleMapServMsg_GlobalNtf)
		HANDLE_MSG(PROTO_MS_MSG_NTF, HandleMapServMsg_MsgNtf)
        HANDLE_MSG(PROTO_MS_POP_DLG_MSG_NTF, HandleMapServMsg_PopDlgMsgNtf)
        HANDLE_MSG(PROTO_MS_PLAYER_FAMILY_CHANGE_NTF, HandleMapServMsg_PlayerFamilyChangeNtf)
        HANDLE_MSG(PROTO_MS_CANCEL_FAMILY_JOIN_ACK, HandleMapServMsg_CancelFamilyJoinAck)
        HANDLE_MSG(PROTO_MS_FAMILY_LEAVE_NTF, HandleMapServMsg_FamilyLeaveNtf)
        HANDLE_MSG(PROTO_MS_FAMILY_INFO_NTF, HandleMapServMsg_FamilyInfoNtf)
		HANDLE_MSG(PROTO_MS_NEW_MAIL_NTF, HandleMapServMsg_NewMailNtf)
		HANDLE_MSG(PROTO_MS_GET_MAIL_LIST_ACK, HandleMapServMsg_GetMailListAck)
		HANDLE_MSG(PROTO_MS_DELETE_MAIL_ACK, HandleMapServMsg_DeleteMailAck)
		HANDLE_MSG(PROTO_MS_OPEN_MAIL_ACK, HandleMapServMsg_OpenMailAck)
		HANDLE_MSG(PROTO_MS_MAIL_ATTACHMENT_GET_ACK, HandleMapServMsg_MailAttachmentGetAck)
        HANDLE_MSG(PROTO_MS_MISS_NTF, HandleMapServMsg_MissNtf)
		HANDLE_MSG(PROTO_MS_RECORDS_MINE_ACK, HandleMapServMsg_RecordsMineAck)
		HANDLE_MSG(PROTO_MS_DELEGATE_MINE_ACK, HandleMapServMsg_DelegateMineAck)
		HANDLE_MSG(PROTO_MS_DELEGATE_SELL_LIST_ACK, HandleMapServMsg_DelegateSellListAck)
		HANDLE_MSG(PROTO_MS_DELEGATE_BUY_LIST_ACK, HandleMapServMsg_DelegateBuyListAck)
		HANDLE_MSG(PROTO_MS_DELETE_SKILL_ACK, HandleMapServMsg_DeleteSkillAck)
        HANDLE_MSG(PROTO_MS_SKILL_STATUS_NTF, HandleMapServMsg_SkillStatusNtf)
        HANDLE_MSG(PROTO_MS_SKILL_PROP_PERMANENT_CHANGED_NTF, HandleMapServMsg_SkillPropPermanetChangedNtf)
		HANDLE_MSG(PROTO_MS_SKILL_PROFICIENCY_NTF, HandleMapServMsg_SkillProficiencyNtf)
		HANDLE_MSG(PROTO_MS_ROLE_DYN_ATTR_NTF, HandleMapServMsg_RoleDynAttrNtf)
		HANDLE_MSG(PROTO_MS_ROLE_CUST_VAR_NTF, HandleMapServMsg_RoleCustVarNtf)
        HANDLE_MSG(PROTO_MS_SHABAK_OWNER_NTF, HandleMapServMsg_ShabakOwnerNtf)
        HANDLE_MSG(PROTO_MS_SHABAK_LOSS_NTF, HandleMapServMsg_ShabakLossNtf)
        HANDLE_MSG(PROTO_MS_SHABAK_ENGAGE_NTF, HandleMapServMsg_ShabakEngageNtf)
        HANDLE_MSG(PROTO_MS_SHABAK_END_NTF, HandleMapServMsg_ShabakEndNtf)
		HANDLE_MSG(PROTO_MS_FAMILY_WAR_NTF, HandleMapServMsg_RunningFamilyWarNtf)
		HANDLE_MSG(PROTO_MS_SET_SERVER_STATUS, HandleMapServMsg_SetServerStatus)
		HANDLE_MSG(PROTO_MS_ROLE_INFO_CHANGE_NTF, HandleMapServMsg_RoleInfoChangeNtf)
        HANDLE_MSG(PROTO_MS_ITEM_PICKUP_NTF, HandleMapServMsg_ItemPickupNtf)
        HANDLE_MSG(PROTO_MS_AUTO_PICKUP_SETTINGS_NTF, HandleMapServMsg_AutoPickupSettingsNtf)
		HANDLE_MSG(PROTO_MS_MONSTER_PURSURE_ATTACKING_NTF, HandleMapServMsg_MonsterPursureStatusChangedNtf)
        HANDLE_MSG(PROTO_MS_START_DIG_ACK, HandleMapServMsg_StartDigAck)
        HANDLE_MSG(PROTO_MS_STOP_DIG_NTF, HandleMapServMsg_StopDigNtf)
        HANDLE_MSG(PROTO_MS_ROLE_APPEAR_NTF, HandleMapServMsg_RoleAppearNtf)
        HANDLE_MSG(PROTO_MS_VERIFY_BUY_ITEM_INFO_ACK, HandleMapServMsg_VerifyBuyItemInfoAck)
		HANDLE_MSG(PROTO_MS_MONSTER_BACK_NTF, HandleMapServMsg_MonsterBackNtf)
        HANDLE_MSG(PROTO_MS_SET_AUTO_MODE_REQ, HandleMapServMsg_SetAutoModeReq)
        HANDLE_MSG(PROTO_MS_SCENE_ITEM_UPDATE_NTF, HandleMapServMsg_SceneItemUpdateNtf)
        HANDLE_MSG(PROTO_MS_MOVE_NTF_EX, HandleMapServMsg_MoveNtfEx)
        HANDLE_MSG(PROTO_MS_TURN_NTF, HandleMapServMsg_TurnNtf)
		HANDLE_MSG(PROTO_MS_SEND_GOODS_POST_RECORD_TO_CLIENT, HandleMapServMsg_SendGoodsPostRecordToClient)
		HANDLE_MSG(PROTO_MS_EFFECT_APPEAR_NTF, HandleMapServMsg_EffectAppearNtf)
		HANDLE_MSG(PROTO_MS_EFFECT_DISAPPEAR_NTF, HandleMapServMsg_EffectDisAppearNtf)


	END_MSG_HANDLER()
}

void SessionGS2MS::HandleMSItemAttrNtfMsg(void* pData)
{
	ProtoMS_ItemAttrNtf* pItemAck = (ProtoMS_ItemAttrNtf*)pData;
	ProtoClient3_ItemAttrNtf pAck;

	pAck.item_guid = pItemAck->item_guid;
	pAck.attr_name = pItemAck->attr_name;
	pAck.attr_value = pItemAck->attr_value;

	ISession* pGateServ = CNetManager::GetInstance()->GetSessionByID(pItemAck->sessid);
	if (!pGateServ) {
		LOG_ERROR("pGateServ is null");
		return;
	}
	pGateServ->SendPkg(&pAck, sizeof(pAck));
}

void SessionGS2MS::HandleMapServMsg_ItemAppearNtf4(void* pData)
{
	const auto *msg = static_cast<ProtoMS_ItemAppearNtf4 *>(pData);

	ProtoClient3_ItemAppearNtf4 data;
    ASSIGN_MEMBER(item_guid);
    ASSIGN_MEMBER(template_id);
    ASSIGN_MEMBER(dst_x);
    ASSIGN_MEMBER(dst_y);
    ASSIGN_MEMBER(skill_id);
    ASSIGN_STRING_MEMBER(item_name);
    ASSIGN_MEMBER(seed);
    ASSIGN_MEMBER(is_drop);
    ASSIGN_MEMBER(owner_guid);
    ASSIGN_MEMBER(team_guid);

    SendDataBySessionID(msg->clsessid, data);
}

void SessionGS2MS::HandleMapServMsg_RunClientScript(void *pData)
{
    auto p = (ProtoMS_RunClientScript *)pData;

    ProtoClient3_RunClientScript req;
    strcpy_s(req.form_name, _countof(req.form_name), p->form_name);
    req.size = p->size;
    memcpy_s(req.form_content, sizeof(req.form_content), p->form_content, p->size);     // 必须用内存拷贝，有可能是压缩数据
    req.comp = p->comp;

	if (p->all == 1)
	{
		//SendDataBySessionID(pBuffAddAck->nClientSessionID, buffAddAck);
		SendDataBySessionType(SESSION_TYPE_GS2CL, req, true);
	}
	else
	{
		if (p->clientSessionID)
		{
			SendDataBySessionID(p->clientSessionID, req);
		}
		for (auto i = 0; i < p->clsessnum; ++i) {
			SendDataBySessionID(p->clsessids[i], req);
		}
	}
	
}

void SessionGS2MS::HandleMSItemUpdateMsg(void* pData)
{
	ProtoMS_ItemUpdateNtf* pItemAck = (ProtoMS_ItemUpdateNtf*)pData;
	ProtoClient3_ItemUpdateNtf pAck;

	pAck.info = pItemAck->info;
	ISession* pGateServ = CNetManager::GetInstance()->GetSessionByID(pItemAck->sessid);
	if (!pGateServ) {
		LOG_ERROR("pGateServ is null");
		return;
	}
	pGateServ->SendPkg(&pAck, sizeof(pAck));
}

void SessionGS2MS::HandleMSItemAckMsg(void* pData)
{
	ProtoMS_ItemAddAck* pItemAck = (ProtoMS_ItemAddAck*)pData;
	ProtoClient3_ItemAddAck pAck;

	pAck.info = pItemAck->info;
	pAck.isPackItem = pItemAck->isPackItem;
	ISession* pGateServ = CNetManager::GetInstance()->GetSessionByID(pItemAck->sessid);
	if (!pGateServ) {
		LOG_ERROR("[ITEM] pGateServ is null");
		return;
	}
	pGateServ->SendPkg(&pAck, sizeof(pAck));

    LOG_TRACE("[ITEM] ItemAddAck, id: %u, site: %u",
        pItemAck->info.base_info.id, pItemAck->info.base_info.site);
}

void SessionGS2MS::HandleMapServMsg_MonsterAppearNtf(void* pData)
{
	ProtoMS_MonsterAppearNtf6* msg = (ProtoMS_MonsterAppearNtf6*)pData;
	if (nullptr == msg) {
		LOG_WARN("Unhandled notify!");
		return;
	}

	ISession* pGateServ = CNetManager::GetInstance()->GetSessionByID(msg->sessid);
	if (!pGateServ) {
		LOG_ERROR("pGateServ is null");
		return;
	}
	ProtoClient3_MonsterAppearNtf6 data;
	/*  gsntf.moduleid = 3;*/
	ASSIGN_MEMBER(monster_guid);
	ASSIGN_STRING_MEMBER(monster_name);
	ASSIGN_MEMBER(template_id);
	ASSIGN_MEMBER(dst_x);
	ASSIGN_MEMBER(dst_y);
	ASSIGN_MEMBER(dir);
	ASSIGN_MEMBER(cur_hp);
	ASSIGN_MEMBER(max_hp);
	ASSIGN_MEMBER(status);
	ASSIGN_MEMBER(servant_lv);
	ASSIGN_MEMBER(move_speed);
	ASSIGN_MEMBER(buff_num);
	for (size_t i = 0; i < msg->buff_num; i++) {
		ASSIGN_MEMBER(buffs[i]);
	}
	ASSIGN_STRING_MEMBER(master_name);
	ASSIGN_MEMBER(appear_type);
	ASSIGN_MEMBER(seed);
	ASSIGN_MEMBER(attack_speed);
	ASSIGN_MEMBER(custom.num);
	ASSIGN_MEMBER(custom.idx);
	ASSIGN_STRING_MEMBER(custom.buf);
	ASSIGN_MEMBER(inner_force);
	ASSIGN_MEMBER(max_inner_force);
	ASSIGN_MEMBER(modelid);
	ASSIGN_MEMBER(reserve_num);
	for (size_t i = 0; i < msg->reserve_num; i++) {
		ASSIGN_MEMBER(reserve_values[i]);
	}
	ASSIGN_STRING_MEMBER(name_color);
	pGateServ->SendPkg(&data, sizeof(data));
}

void SessionGS2MS::HandleMapServMsg_SkillAddAck(void* pData)
{
	auto pSkillAddAck = (ProtoMS_SkillAddAck*)pData;

	ProtoClient3_SkillAddAck skillAddAck;
    skillAddAck.role_guid = pSkillAddAck->role_guid;
	skillAddAck.num = pSkillAddAck->num;
	for (uint16_t i = 0; i < pSkillAddAck->num; ++i)
		skillAddAck.info[i] = pSkillAddAck->info[i];

	SendDataBySessionID(pSkillAddAck->nClientSessionID, skillAddAck);
}

void SessionGS2MS::HandleMapServMsg_BuffAddAck(void* pData)
{
	auto pBuffAddAck = (ProtoMS_BuffAddAck*)pData;

	ProtoClient3_BuffAddAck buffAddAck;
	buffAddAck.role_guid = pBuffAddAck->role_guid;
	buffAddAck.num = pBuffAddAck->num;
	std::copy(pBuffAddAck->info, pBuffAddAck->info + pBuffAddAck->num, buffAddAck.info);
	if (pBuffAddAck->nClientSessionID)
	{
		SendDataBySessionID(pBuffAddAck->nClientSessionID, buffAddAck);
	}
	for (auto i = 0; i < pBuffAddAck->clsessnum; ++i) {
		SendDataBySessionID(pBuffAddAck->clsessids[i], buffAddAck);
	}
}

void SessionGS2MS::HandleMapServMsg_BuffDestroyAck(void* pData)
{
	auto pBuffDestroyAck = (ProtoMS_BuffDestroyAck*)pData;

	ProtoClient3_BuffDestroyAck buffDestroyAck;
	buffDestroyAck.role_guid = pBuffDestroyAck->role_guid;
	buffDestroyAck.id = pBuffDestroyAck->id;
	if (pBuffDestroyAck->nClientSessionID)
	{
		SendDataBySessionID(pBuffDestroyAck->nClientSessionID, buffDestroyAck);
	}
	for (auto i = 0; i < pBuffDestroyAck->clsessnum; ++i) {
		SendDataBySessionID(pBuffDestroyAck->clsessids[i], buffDestroyAck);
	}
}

void SessionGS2MS::HandleMapServMsg_PlayerAppearNtf(void* pData)
{
    const auto *msg = static_cast<ProtoMS_PlayerAppearNtf *>(pData);

    ProtoClient3_PlayerAppearNtf3 data;

    ASSIGN_MEMBER(player_guid);
    ASSIGN_STRING_MEMBER(name);
    ASSIGN_MEMBER(gender);
    ASSIGN_MEMBER(job);
    ASSIGN_MEMBER(status);
    ASSIGN_MEMBER(head);
    ASSIGN_MEMBER(level);
    ASSIGN_MEMBER(dst_x);
    ASSIGN_MEMBER(dst_y);
    ASSIGN_MEMBER(dir);
    ASSIGN_MEMBER(hair);
    ASSIGN_MEMBER(hair_color);
    ASSIGN_MEMBER(body);
    ASSIGN_MEMBER(weapon);
    ASSIGN_MEMBER(wings);
    ASSIGN_MEMBER(mount);
    ASSIGN_MEMBER(weapon_effect);
    ASSIGN_MEMBER(body_effect);
    ASSIGN_MEMBER(mount_effect);
    ASSIGN_MEMBER(hp);
    ASSIGN_MEMBER(max_hp);
    ASSIGN_MEMBER(mp);
    ASSIGN_MEMBER(max_mp);
    ASSIGN_MEMBER(pk);
    ASSIGN_MEMBER(move_speed);
    ASSIGN_MEMBER(attack_speed);
	ASSIGN_MEMBER(casting_speed);
	ASSIGN_MEMBER(show_fashion);
	ASSIGN_MEMBER(model_id);
    ASSIGN_MEMBER(title);
    ASSIGN_MEMBER(has_team);
    ASSIGN_MEMBER(stall);
    ASSIGN_STRING_MEMBER(stall_name);
    ASSIGN_MEMBER(buff_num);
    ASSIGN_ARRAY_MEMEBER(buffs);
    ASSIGN_STRING_MEMBER(family_name);
    ASSIGN_STRING_MEMBER(castle_name);
    ASSIGN_STRING_MEMBER(family_title);
    ASSIGN_STRING_MEMBER(alias);
    ASSIGN_STRUCT_MEMBER(custom);
    ASSIGN_MEMBER(appear_type);
    ASSIGN_MEMBER(amulet);
    ASSIGN_MEMBER(equip_num);
    ASSIGN_ARRAY_MEMEBER(equips);
    ASSIGN_MEMBER(inner_force);
    ASSIGN_MEMBER(max_inner_force);
    ASSIGN_MEMBER(reserve_num);
    ASSIGN_ARRAY_MEMEBER(reserve_values);
	ASSIGN_MEMBER(title_num);
	ASSIGN_ARRAY_MEMEBER(title_id);
    ASSIGN_MEMBER(master_guid);

    SendDataBySessionID(msg->sessid, data);
}

void SessionGS2MS::HandleMapServMsg_SysMsgNtf(void *pData)
{
    auto pSysMsgNtf = (ProtoMS_SysMsgNtf *)pData;

    ProtoClient2_SysMsgNtf sysMsgNtf;
    sysMsgNtf.msg_type = pSysMsgNtf->msg_type;
    sysMsgNtf.scroll_count = pSysMsgNtf->scroll_count;
    strcpy_s(sysMsgNtf.msg, _countof(sysMsgNtf.msg), pSysMsgNtf->msg);

    SendDataBySessionID(pSysMsgNtf->clientSessionID, sysMsgNtf);
}

void SessionGS2MS::HandleMSItemDestroyMsg(void* pData)
{
	LOG_NORMAL("SessionMS2GS::HandleMSItemDestroyMsg protoid:5 ");
	ProtoMS_ItemDestroyAck* pItemAck = (ProtoMS_ItemDestroyAck*)pData;
	ProtoClient3_ItemDestroyAck pAck;

	pAck.item_guid = pItemAck->item_guid;
	ISession* pGateServ = CNetManager::GetInstance()->GetSessionByID(pItemAck->sessid);
	if (!pGateServ) {
		LOG_ERROR("pGateServ is null");
		return;
	}
	pGateServ->SendPkg(&pAck, sizeof(pAck));
}


void SessionGS2MS::HandleGateServMsg_ExitGSMsg(void* pData)
{

	ProtoGS_ExitGSAck* pExitAck = (ProtoGS_ExitGSAck*)pData;
	ProtoClient3_ExitGSAck pAck;

	pAck.exittype = pExitAck->exittype;
	pAck.errcode = pExitAck->errcode;
	memcpy(pAck.errmsg, pExitAck->errmsg, sizeof(pExitAck->errmsg));

	ISession* pGateServ = CNetManager::GetInstance()->GetSessionByID(pExitAck->sessionid);
	if (!pGateServ) {
		LOG_ERROR("##### HandleGateServMsg_ExitGSMsg pGateServ is null");
		return;
	}

	pGateServ->SendPkg(&pAck, sizeof(pAck));
}

void SessionGS2MS::HandleMapServerMsg_SpellNtf(void* pData)
{
	ProtoMS_SpellNtf* pSpellNtf = (ProtoMS_SpellNtf*)pData;

	ProtoClient3_SpellNtf spellNtf;
	spellNtf.actor = pSpellNtf->actor;
	spellNtf.id = pSpellNtf->id;
	spellNtf.target_x = pSpellNtf->target_x;
	spellNtf.target_y = pSpellNtf->target_y;
    spellNtf.extra = pSpellNtf->extra;
	spellNtf.num = pSpellNtf->num;
	for (uint16_t i = 0; i < pSpellNtf->num; ++i)
		spellNtf.targets[i] = pSpellNtf->targets[i];

    for (auto i = 0; i < pSpellNtf->clsessnum; ++i) {
	    SendDataBySessionID(pSpellNtf->clsessids[i], spellNtf, true);
    }
}

void SessionGS2MS::HandleMapServerMsg_ErrorAck(void* pData)
{
	auto pErrorAck = (ProtoMS_ErrorAck*)pData;
	//LOG_ERROR("########################## HandleMapServerMsg_ErrorAck#################################");
	ProtoClient7_ErrorAck errorAck;
	errorAck.guid = pErrorAck->guid;
	errorAck.ecode = pErrorAck->ecode;

	SendDataBySessionID(pErrorAck->clientSessionID, errorAck);

	LOG_TRACE("Send ErrorAck to client. session: %u, guid: %" PRIu64 ", ecode: %d",
		pErrorAck->clientSessionID, pErrorAck->guid, pErrorAck->ecode);
}

void SessionGS2MS::HandleMapServerMsg_GMErrorAck(void *pData)
{
    auto pErrorAck = (ProtoMS_GMErrorAck *)pData;
    //LOG_ERROR("########################## HandleMapServerMsg_ErrorAck#################################");
    ProtoClient7_GMErrorAck errorAck;
    errorAck.sn = pErrorAck->sn;
    errorAck.guid = pErrorAck->guid;
    errorAck.ecode = pErrorAck->ecode;

    SendDataBySessionID(pErrorAck->clsessid, errorAck);

    LOG_NORMAL("[GM] Send GMErrorAck to client. session: %u, guid: %" PRIu64 ", ecode: %d, sn: %d",
        pErrorAck->clsessid, pErrorAck->guid, pErrorAck->ecode, pErrorAck->sn);
}

void SessionGS2MS::HandleMapServerMsg_AttrShowNtfEx2(void* pData)
{
	auto pAttrShowNtf = (ProtoMS_AttrShowNtfEx2*)pData;

	ProtoClient3_AttrShowNtfEx2 attrShowNtf;
	attrShowNtf.actor = pAttrShowNtf->actor;
	attrShowNtf.target = pAttrShowNtf->target;
	attrShowNtf.skill_id = pAttrShowNtf->skill_id;
	attrShowNtf.type = pAttrShowNtf->type;
	attrShowNtf.actor_hp_ref = pAttrShowNtf->actor_hp_ref;
	attrShowNtf.actor_mp_ref = pAttrShowNtf->actor_mp_ref;
	attrShowNtf.target_hp_ref = pAttrShowNtf->target_hp_ref;
	attrShowNtf.target_hp = pAttrShowNtf->target_hp;
	attrShowNtf.target_mp_ref = pAttrShowNtf->target_mp_ref;
	attrShowNtf.target_mp = pAttrShowNtf->target_mp;
	attrShowNtf.reserve_size = pAttrShowNtf->reserve_size;
	for (int i = 0; i < pAttrShowNtf->reserve_size; ++i)
		attrShowNtf.reserve[i] = pAttrShowNtf->reserve[i];

    for (auto i = 0; i < pAttrShowNtf->clsessnum; ++i) {
	    SendDataBySessionID(pAttrShowNtf->clsessids[i], attrShowNtf, true);
    }
}

void SessionGS2MS::HandleMapServerMsg_ObjDieNtf(void* pData)
{
	auto pObjDieNtf = (ProtoMS_ObjDieNtf*)pData;

	ProtoClient3_ObjDieNtf objDieNtf;
	objDieNtf.die_guid = pObjDieNtf->die_guid;
	objDieNtf.kill_guid = pObjDieNtf->kill_guid;
	strcpy_s(objDieNtf.kill_name, _countof(objDieNtf.kill_name), pObjDieNtf->kill_name);

	SendDataBySessionID(pObjDieNtf->clientSessionID, objDieNtf);
}

void SessionGS2MS::HandleMapServerMsg_RoleAttrNtf(void* pData)
{
	auto pRoleAttrNtf = (ProtoMS_RoleAttrNtf*)pData;
	ProtoClient3_RoleAttrNtf roleAttrNtf;
	roleAttrNtf.role_guid = pRoleAttrNtf->role_guid;
	roleAttrNtf.num = pRoleAttrNtf->attr_num;
	for (uint16_t i = 0; i < pRoleAttrNtf->attr_num; ++i) {
		roleAttrNtf.attr_name[i] = pRoleAttrNtf->attr_name[i];
		roleAttrNtf.attr_value[i] = pRoleAttrNtf->attr_value[i];
	}

    bool candrop = std::all_of(pRoleAttrNtf->attr_name,
                               pRoleAttrNtf->attr_name + pRoleAttrNtf->attr_num,
                               [](const auto &prop) {
                                    return (prop == role_hp || prop == role_mp);
                               });

    for (auto i = 0; i < pRoleAttrNtf->clsessnum; ++i) {
	    SendDataBySessionID(pRoleAttrNtf->clsessids[i], roleAttrNtf, candrop);
    }
}

void SessionGS2MS::HandleMapServerMsg_RoleAttrExtNtf(void* pData)
{
	auto pRoleAttrNtf = (ProtoMS_RoleAttrExtNtf*)pData;
	ProtoClient3_RoleAttrExtNtf roleAttrNtf;
	roleAttrNtf.player_guid = pRoleAttrNtf->player_guid;
	roleAttrNtf.num = pRoleAttrNtf->num;
	for (uint16_t i = 0; i < pRoleAttrNtf->num; ++i) {
		roleAttrNtf.attr_name[i] = pRoleAttrNtf->attr_name[i];
		roleAttrNtf.attr_value[i] = pRoleAttrNtf->attr_value[i];
	}

	SendDataBySessionID(pRoleAttrNtf->sessid, roleAttrNtf);
}

void SessionGS2MS::HandleMapServMsg_RoleDynAttrNtf(void* pData)
{
	auto pRoleAttrNtf = (ProtoMS_RoleDynAttrsNtf*)pData;
	ProtoClient3_RoleDynAttrNtf roleDynAttrNtf;
	roleDynAttrNtf.role_guid = pRoleAttrNtf->role_guid;
	roleDynAttrNtf.custom = pRoleAttrNtf->custom;

	SendDataBySessionID(pRoleAttrNtf->sessid, roleDynAttrNtf);
}

void SessionGS2MS::HandleMapServMsg_RoleInfoChangeNtf(void* pData)
{
	auto changeNtf = (ProtoMS_RoleInfoChangeNtf*)pData;
	ProtoClient3_RoleInfoChangeNtf ntf;
	ntf.role_guid = changeNtf->role_guid;
	ntf.num = changeNtf->num;
	ntf.custom = changeNtf->custom;

	SendDataBySessionID(changeNtf->sessid, ntf);
}

void SessionGS2MS::HandleMapServMsg_RoleCustVarNtf(void* pData)
{
	auto pRoleCustVarNtf = (ProtoMS_RoleCustVarNtf*)pData;
	ProtoClient3_RoleCustVarNtf roleCustVarNtf;
	roleCustVarNtf.role_guid = pRoleCustVarNtf->role_guid;
	roleCustVarNtf.custom = pRoleCustVarNtf->custom;
	roleCustVarNtf.type = pRoleCustVarNtf->type;
	SendDataBySessionID(pRoleCustVarNtf->sessid, roleCustVarNtf);
}

void SessionGS2MS::HandleMapServMsg_ItemPickupNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_ItemPickupNtf *>(pData);

    ProtoClient3_ItemPickupNtf data;
    ASSIGN_MEMBER(role_guid);
    ASSIGN_MEMBER(item_guid);

    SendDataBySessionID(msg->clsessid, data);
}

void SessionGS2MS::HandleMapServMsg_AutoPickupSettingsNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_AutoPickupSettingsNtf *>(pData);

    ProtoClient3_AutoPickupSettingsNtf data;
    ASSIGN_STRUCT_MEMBER(auto_pickup);

    SendDataBySessionID(msg->clsessid, data);
}

void SessionGS2MS::HandleMapServMsg_StartDigAck(void *pData)
{
    const auto *msg = static_cast<ProtoMS_StartDigAck *>(pData);

    ProtoClient3_StartDigAck data;
    ASSIGN_MEMBER(treasure_guid);
    ASSIGN_MEMBER(code);
    ASSIGN_MEMBER(dig_time);

    SendDataBySessionID(msg->clsessid, data);
}

void SessionGS2MS::HandleMapServMsg_StopDigNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_StopDigNtf *>(pData);

    ProtoClient3_StopDigNtf data;
    ASSIGN_MEMBER(treasure_guid);
    ASSIGN_MEMBER(reason);

    SendDataBySessionID(msg->clsessid, data);
}

void SessionGS2MS::HandleMapServMsg_RoleAppearNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_RoleAppearNtf *>(pData);

    ProtoClient3_RoleAppearNtf data;
    ASSIGN_MEMBER(role_guid);
    ASSIGN_MEMBER(appear_type);

    SendDataBySessionID(msg->clsessid, data);
}

void SessionGS2MS::HandleMapServMsg_VerifyBuyItemInfoAck(void *pData)
{
    const auto *msg = static_cast<ProtoMS_VerifyBuyItemInfoAck *>(pData);

    ProtoClient3_VerifyBuyItemInfoAck data;
    ASSIGN_MEMBER(item_id);
    ASSIGN_MEMBER(status);

    SendDataBySessionID(msg->clsessid, data);
}

void SessionGS2MS::HandleMapServMsg_MonsterBackNtf(void* pData)
{
	const auto* msg = static_cast<ProtoMS_MonsterBackNtf*>(pData);
	ProtoClient3_MonsterBackNtf data;
	data.guid = msg->guid;
	data.status = msg->status;
	SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_SetAutoModeReq(void *pData)
{
    const auto *msg = static_cast<ProtoMS_SetAutoModeReq *>(pData);

    ProtoClient3_SetAutoModeReq data;
    ASSIGN_MEMBER(role_guid);
    ASSIGN_MEMBER(enable);

    SendDataBySessionID(msg->clsessid, data);
}

void SessionGS2MS::HandleMapServMsg_SceneItemUpdateNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_SceneItemUpdateNtf *>(pData);

    ProtoClient3_SceneItemUpdateNtf data;
    ASSIGN_MEMBER(item_guid);

    SendDataBySessionID(msg->clsessid, data);
}

void SessionGS2MS::HandleMapServMsg_MoveNtfEx(void *pData)
{
    const auto *msg = static_cast<ProtoMS_MoveNtfEx *>(pData);

    ProtoClient3_MoveNtf data;
    ASSIGN_MEMBER(guid);
    ASSIGN_MEMBER(type);
    ASSIGN_MEMBER(dst_x);
    ASSIGN_MEMBER(dst_y);

    for (auto i = 0; i < msg->clsessnum; ++i)
        SendDataBySessionID(msg->clsessids[i], data);
}

void SessionGS2MS::HandleMapServMsg_TurnNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_TurnNtf *>(pData);

    ProtoClient3_TurnNtf data;
    ASSIGN_MEMBER(guid);
    ASSIGN_MEMBER(dir);

    for (auto i = 0; i < msg->clsessnum; ++i)
        SendDataBySessionID(msg->clsessids[i], data);
}

void SessionGS2MS::HandleMapServMsg_SendGoodsPostRecordToClient(void* pData)
{
	const auto* msg = static_cast<ProtoMS_SendGoodsPostRecordToClient*>(pData);
	ProtoClient3_SendGoodsPostRecordToClient data;
	ASSIGN_MEMBER(record);
	SendDataBySessionID(msg->sessionID, data);
}

void SessionGS2MS::HandleMapServMsg_EffectAppearNtf(void* pData)
{
	const auto* msg = static_cast<ProtoMS_EffectAppearNtf*>(pData);
	ProtoClient3_EffectAppearNtf data;
	ASSIGN_MEMBER(num);
	ASSIGN_ARRAY_MEMEBER(info);
	ASSIGN_MEMBER(type);
	SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_EffectDisAppearNtf(void* pData)
{
	const auto* msg = static_cast<ProtoMS_EffectDisAppearNtf*>(pData);
	ProtoClient3_EffectDisAppearNtf data;
	ASSIGN_MEMBER(num);
	ASSIGN_ARRAY_MEMEBER(info);
	ASSIGN_MEMBER(type);
	SendDataBySessionID(msg->sessionid, data);
}

// 这里加动态属性
void SessionGS2MS::HandleGateServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_SESSION_MS2GS_NTF, HandleGateServMsg_SessionIDNtf)
        HANDLE_MSG(PROTO_GS_HEART_BEAT_ACK, HandleGateServMsg_HeartBeatAck)
        HANDLE_MSG(PROTO_GS_MOVE_ACK, HandleGateServMsg_MoveAck)
        HANDLE_MSG(PROTO_GS_TURN_NTF, HandleGateServMsg_TurnNtf)
        HANDLE_MSG(PROTO_GS_SPELL_ACK, HandleGateServMsg_SpellAck)
        HANDLE_MSG(PROTO_GS_EXIT_GS_ACK, HandleGateServMsg_ExitGSMsg)
        HANDLE_MSG(PROTO_GS_SKILL_SWITCH_ACK, HandleGateServMsg_SkillSwitchAck)
        HANDLE_MSG(PROTO_GS_RUN_SERV_SCRIPT_ACK, HandleGateServMsg_RunServScriptAck)
        HANDLE_MSG(PROTO_GS_RELATION_CHAT_ACK, HandleGateServMsg_RelationChatAck)
        HANDLE_MSG(PROTO_GS_RELATION_CHAT_NTF, HandleGateServMsg_RelationChatNtf)
        HANDLE_MSG(PROTO_GS_PRIVATE_CHAT_NTF, HandleGateServMsg_PrivateChatNtf)
        HANDLE_MSG(PROTO_GS_SPEAKER_MSG_NTF, HandleGateServMsg_SpeakerMsgNtf)
        HANDLE_MSG(PROTO_GS_TRADE_MALL_LIST_ACK, HandleGateServMsg_TradeMallListAck)
        HANDLE_MSG(PROTO_GS_QUEST_QUERY_CAN_ACCEPT_NTF, HandleGateServMsg_QuestQueryCanAcceptNtf)
        HANDLE_MSG(PROTO_GS_QUEST_ADD_NTF, HandleGateServMsg_QuestAddNtf)
		HANDLE_MSG(PROTO_GS_SYS_MSG_NTF2, HandleMapServMsg_SysMsgNtf2)
		HANDLE_MSG(PROTO_GS_SCENE_DIALOG_NTF, HandleMapServMsg_SceneDialogNtf)
		HANDLE_MSG(PROTO_GS_SCROLL_TEXT_NTF, HandleMapServMsg_ScrollText)
		HANDLE_MSG(PROTO_GS_TRADE_LIST_UPDATE, HandleMapServMsg_TradeListUpdate)
		HANDLE_MSG(PROTO_GS_KICK_OUT_BY_LOCK, HandleMapServMsg_KickOutRole)
		HANDLE_MSG(PROTO_GS_GET_NPC_POS_ACK, HandleMapServMsg_GetNpcPosAck)
		HANDLE_MSG(PROTO_GS_PLAYER_SET_NAME_NTF, HandleMapServMsg_PlayerSetNameNtf)
		HANDLE_MSG(PROTO_GS_ITEM_TIP_NTF, HandleMapServMsg_ItemTipNtf)
		HANDLE_MSG(PROTO_GS_CUST_MSG_NTF, HandleMapServMsg_CustMsgNtf)
		HANDLE_MSG(PROTO_GS_TITLE_ADD_ACK, HandleMapServMsg_TitleAddAck)
		HANDLE_MSG(PROTO_GS_TITLE_DEL_ACK, HandleMapServMsg_TitleDelAck)
		HANDLE_MSG(PROTO_GS_TITLE_LIST, HandleMapServMsg_TitleList)
		HANDLE_MSG(PROTO_GS_TITLE_WEAR_NTF, HandleMapServMsg_TitleWearNtf)
		HANDLE_MSG(PROTO_GS_TITLE_UNWEAR_NTF, HandleMapServMsg_TitleUnWearNtf)
    END_MSG_HANDLER()
}

void SessionGS2MS::HandleGateServMsg_SessionIDNtf(void* pData)
{
	auto ntf = (ProtoGS_SessionIDNtf*)pData;
	SessionContextMgr::GetInstance()->SetMS2GSSessionID(ntf->sessionid);
}

void SessionGS2MS::HandleGateServMsg_HeartBeatAck(void* pData)
{
	// do nothing
}

void SessionGS2MS::HandleGateServMsg_MoveAck(void* pData)
{
	auto pMoveAck = (ProtoGS_MoveAck*)pData;

	ISession* pSession = CNetManager::GetInstance()->GetSessionByID(pMoveAck->clsessid);
	SessionGS2CL* pSessionGS2CL = dynamic_cast<SessionGS2CL*>(pSession);
	if (!pSessionGS2CL) {
		LOG_ERROR("pSessionGS2CL is NULL");
		return;
	}

	pSessionGS2CL->OnMoveAck(pMoveAck);
}

void SessionGS2MS::HandleGateServMsg_TurnNtf(void* pData)
{
	auto pTurnNtf = (ProtoGS_TurnNtf*)pData;

	LOG_TRACE("[TurnNtf] session: %u, token: %u, player: %" PRIu64 ", role: %" PRIu64 ", dir: %u",
		pTurnNtf->sessionid, pTurnNtf->token, pTurnNtf->playerid, pTurnNtf->guid, pTurnNtf->dir);

	ISession* pSession = CNetManager::GetInstance()->GetSessionByID(pTurnNtf->sessionid);
	SessionGS2CL* pSessionGS2CL = dynamic_cast<SessionGS2CL*>(pSession);
	if (!pSessionGS2CL) {
		LOG_ERROR("[TurnNtf] pSessionGS2CL is NULL");
		return;
	}

	pSessionGS2CL->OnTurnNtf(pTurnNtf);
}

void SessionGS2MS::HandleGateServMsg_SpellAck(void* pData)
{
	auto pSpellAck = (ProtoGS_SpellAck*)pData;

	ISession* pSession = CNetManager::GetInstance()->GetSessionByID(pSpellAck->sessionid);
	SessionGS2CL* pSessionGS2CL = dynamic_cast<SessionGS2CL*>(pSession);
	if (!pSessionGS2CL) {
		LOG_ERROR("pSessionGS2CL is NULL. role_guid: %" PRIu64, pSpellAck->role_guid);
		return;
	}

	pSessionGS2CL->OnSpellAck(pSpellAck);
}

void SessionGS2MS::HandleGateServMsg_SkillSwitchAck(void* pData)
{
	auto pSkillSwitchAck = (ProtoGS_SkillSwitchAck*)pData;

    LOG_TRACE("[SkillSwitchAck] skill: %u, active: %u", pSkillSwitchAck->id, pSkillSwitchAck->active);

	ProtoClient3_SkillSwitchAck skillSwitchAck;
	skillSwitchAck.id = pSkillSwitchAck->id;
	skillSwitchAck.active = pSkillSwitchAck->active;

	SendDataBySessionID(pSkillSwitchAck->clientSessionID, skillSwitchAck);
}

void SessionGS2MS::HandleGateServMsg_RunServScriptAck(void *pData)
{
    auto pRunServScriptAck = (ProtoGS_RunServScriptAck *)pData;

    ProtoClient3_RunServScriptAck runServScriptAck;
    strcpy_s(runServScriptAck.script_name, _countof(runServScriptAck.script_name), pRunServScriptAck->script_name);
    strcpy_s(runServScriptAck.result, _countof(runServScriptAck.result), pRunServScriptAck->result);

    SendDataBySessionID(pRunServScriptAck->sessionid, runServScriptAck);
}

void SessionGS2MS::HandleGateServMsg_RelationChatAck(void *pData)
{
    auto pRelationChatAck = (ProtoGS_RelationChatAck *)pData;

    ProtoClient2_RelationChatAck relationChatAck;
    relationChatAck.type = pRelationChatAck->type;
	strcpy_s(relationChatAck.font_color, _countof(relationChatAck.font_color), pRelationChatAck->font_color);
	strcpy_s(relationChatAck.background_color, _countof(relationChatAck.background_color), pRelationChatAck->background_color);
	relationChatAck.scroll_times = pRelationChatAck->scroll_times;
    relationChatAck.chat_message = pRelationChatAck->chat_message;

    SendDataBySessionID(pRelationChatAck->sessionid, relationChatAck);
}

void SessionGS2MS::HandleGateServMsg_RelationChatNtf(void *pData)
{
    auto pRelationChatNtf = (ProtoGS_RelationChatNtf *)pData;

    ProtoClient2_RelationChatNtf relationChatNtf;
	pRelationChatNtf->moduleid = relationChatNtf.moduleid;
	pRelationChatNtf->protocolid = relationChatNtf.protocolid;
	memcpy(&relationChatNtf, pRelationChatNtf, sizeof(ProtoClient2_RelationChatNtf));
    SendDataBySessionID(pRelationChatNtf->sessionid, relationChatNtf);
}

void SessionGS2MS::HandleGateServMsg_PrivateChatNtf(void *pData)
{
    auto pPrivateChatNtf = (ProtoGS_PrivateChatNtf *)pData;

    ProtoClient2_PrivateChatNtf privateChatNtf;
    privateChatNtf.type = pPrivateChatNtf->type;
    privateChatNtf.chat_message = pPrivateChatNtf->chat_message;

    SendDataBySessionID(pPrivateChatNtf->sessionid, privateChatNtf);
}

void SessionGS2MS::HandleGateServMsg_SpeakerMsgNtf(void *pData)
{
    auto pSpeakerMsgNtf = (ProtoGS_SpeakerMsgNtf *)pData;

    ProtoClient2_SpeakerMsgNtf speakerMsgNtf;
    strcpy_s(speakerMsgNtf.sender, _countof(speakerMsgNtf.sender), pSpeakerMsgNtf->sender);
    strcpy_s(speakerMsgNtf.msg, _countof(speakerMsgNtf.msg), pSpeakerMsgNtf->msg);

    SendDataBySessionID(pSpeakerMsgNtf->sessionid, speakerMsgNtf);
}

void SessionGS2MS::HandleGateServMsg_TradeMallListAck(void* pData)
{
	auto pAck = (ProtoGS_TradeMallListAck*)pData;
	ProtoClient3_TradeMallListAck ack;
	ack.page_id = pAck->page_id;
	ack.item_count = pAck->item_count;
	memcpy(ack.item_list, pAck->item_list, sizeof(MALL_ITEM_INFO) * pAck->item_count);
	SendDataBySessionID(pAck->sessionid, ack);
}

void SessionGS2MS::HandleGateServMsg_QuestQueryCanAcceptNtf(void *pData)
{
    auto pQuestQueryCanAcceptNtf = (ProtoGS_QuestQueryCanAcceptNtf *)pData;

    ProtoClient3_QuestQueryCanAcceptNtf questQueryCanAcceptNtf;
    questQueryCanAcceptNtf.num = pQuestQueryCanAcceptNtf->num;
    CopyArray(questQueryCanAcceptNtf.quests, pQuestQueryCanAcceptNtf->quests);

    SendDataBySessionID(pQuestQueryCanAcceptNtf->sessionid, questQueryCanAcceptNtf);
}

void SessionGS2MS::HandleGateServMsg_QuestAddNtf(void *pData)
{
    auto pQuestAddNtf = (ProtoGS_QuestAddNtf *)pData;

    ProtoClient3_QuestAddNtf questAddNtf;
    questAddNtf.quest_id = pQuestAddNtf->quest_id;
    CopyArray(questAddNtf.quest_name, pQuestAddNtf->quest_name);
    questAddNtf.quest_type = pQuestAddNtf->quest_type;
    questAddNtf.group_huntings_len = pQuestAddNtf->group_huntings_len;
    CopyArray(questAddNtf.group_huntings, pQuestAddNtf->group_huntings);
    questAddNtf.huntings_len = pQuestAddNtf->huntings_len;
    CopyArray(questAddNtf.huntings, pQuestAddNtf->huntings);
    questAddNtf.huntlevels_len = pQuestAddNtf->huntlevels_len;
    CopyArray(questAddNtf.huntlevels, pQuestAddNtf->huntlevels);
    questAddNtf.group_items_len = pQuestAddNtf->group_items_len;
    CopyArray(questAddNtf.group_items, pQuestAddNtf->group_items);
    questAddNtf.collect_items_len = pQuestAddNtf->collect_items_len;
    CopyArray(questAddNtf.collect_items, pQuestAddNtf->collect_items);
    questAddNtf.apply_items_len = pQuestAddNtf->apply_items_len;
    CopyArray(questAddNtf.apply_items, pQuestAddNtf->apply_items);
    questAddNtf.npcs_len = pQuestAddNtf->npcs_len;
    CopyArray(questAddNtf.npcs, pQuestAddNtf->npcs);
    questAddNtf.track_enabled = pQuestAddNtf->track_enabled;
    questAddNtf.life = pQuestAddNtf->life;
    CopyArray(questAddNtf.progressing, pQuestAddNtf->progressing);
    CopyArray(questAddNtf.accomplishing, pQuestAddNtf->accomplishing);

    SendDataBySessionID(pQuestAddNtf->sessionid, questAddNtf);
}

void SessionGS2MS::HandleMSPlayerMoveNtfMsg(void* pData)
{
	ProtoMS_MoveNtf* ntf = (ProtoMS_MoveNtf*)pData;
	if (nullptr == ntf) {
		LOG_WARN("Unhandled notify!");
		return;
	}

	ISession* pGateServ = CNetManager::GetInstance()->GetSessionByID(ntf->sessionid);
	if (!pGateServ) {
		LOG_ERROR("pGateServ is null");
		return;
	}
	ProtoClient3_MoveNtf moventf;
	moventf.dst_x = ntf->dst_x;
	moventf.dst_y = ntf->dst_y;
	moventf.type = ntf->type;
	moventf.guid = ntf->guid;
	pGateServ->SendPkg(&moventf, sizeof(moventf));

}

void SessionGS2MS::HandleMSObjDisAppearNtfMsg(void* pData)
{
	ProtoMS_ObjDisappearNtf* ntf = (ProtoMS_ObjDisappearNtf*)pData;
	if (nullptr == ntf) {
		LOG_WARN("Unhandled notify!");
		return;
	}

    LOG_TRACE("notify cleint  sesssin id %d!", ntf->sessid);
	ISession* pGateServ = CNetManager::GetInstance()->GetSessionByID(ntf->sessid);
	if (!pGateServ) {
		LOG_ERROR("pGateServ is null");
		return;
	}
	ProtoClient3_ObjDisappearNtf gsntf;
	gsntf.obj_guid = ntf->obj_guid;
	pGateServ->SendPkg(&gsntf, sizeof(gsntf));
}

void SessionGS2MS::HandleMapServMsg_EnterMSAck(void* pData)
{
	auto pEnterMSAck = (ProtoMS_EnterMSAck*)pData;

	ProtoClient3_EnterMSAck enterMSAck;
	enterMSAck.entertype = pEnterMSAck->entertype;
	enterMSAck.roleguid = pEnterMSAck->roleguid;
	enterMSAck.gsobjid = pEnterMSAck->gsobjid;
	enterMSAck.errcode = pEnterMSAck->errcode;
	strcpy_s(enterMSAck.errmsg, _countof(enterMSAck.errmsg), pEnterMSAck->errmsg);

	SendDataBySessionID(pEnterMSAck->nClientSessionID, enterMSAck);
}

void SessionGS2MS::HandleMapServMsg_EnterMSNtf(void* pData)
{
	auto pEnterMSNtf = (ProtoMS_EnterMSNtf*)pData;

	ProtoClient3_EnterGSNTF enterGSNtf;
	enterGSNtf.mapcode = pEnterMSNtf->mapcode;
	strcpy_s(enterGSNtf.logic, _countof(enterGSNtf.logic), pEnterMSNtf->logic);
	enterGSNtf.view_x = pEnterMSNtf->view_x;
	enterGSNtf.view_y = pEnterMSNtf->view_y;
	enterGSNtf.width = pEnterMSNtf->width;
	enterGSNtf.height = pEnterMSNtf->height;

	SendDataBySessionID(pEnterMSNtf->nClientSessionID, enterGSNtf);
}

void SessionGS2MS::HandleMapServMsg_NpcAppearNtf(void *pData)
{
    auto pNpcAppearNtf = (ProtoMS_NpcAppearNtf *)pData;

    ProtoClient3_NpcAppearNtf npcAppearNtf;
    npcAppearNtf.npc_guid = pNpcAppearNtf->npc_guid;
    npcAppearNtf.template_id = pNpcAppearNtf->template_id;
    npcAppearNtf.dst_x = pNpcAppearNtf->dst_x;
    npcAppearNtf.dst_y = pNpcAppearNtf->dst_y;
    npcAppearNtf.dir = pNpcAppearNtf->dir;
	npcAppearNtf.modelid = pNpcAppearNtf->modelid;
    strcpy_s(npcAppearNtf.name, _countof(npcAppearNtf.name), pNpcAppearNtf->name);

    SendDataBySessionID(pNpcAppearNtf->clientSessionID, npcAppearNtf);
}

void SessionGS2MS::HandleMapServMsg_TradeNpcShopNtf(void *pData)
{
    auto pTradeNpcShopNtf = (ProtoMS_TradeNpcShopNtf *)pData;

    ProtoClient3_TradeNpcShopNtf tradeNpcShopNtf;
    tradeNpcShopNtf.shop_id = pTradeNpcShopNtf->shop_id;
    tradeNpcShopNtf.item_count = pTradeNpcShopNtf->item_count;
    CopyArray(tradeNpcShopNtf.item_list, pTradeNpcShopNtf->item_list);

    SendDataBySessionID(pTradeNpcShopNtf->clientSessionID, tradeNpcShopNtf);
}

void SessionGS2MS::HandleMapServMsg_QuestNpcTalkAck(void *pData)
{
    auto pQuestNpcTalkAck = (ProtoMS_QuestNpcTalkAck *)pData;

    ProtoClient3_QuestNpcTalkAck questNpcTalkAck;
    questNpcTalkAck.width = pQuestNpcTalkAck->width;
    questNpcTalkAck.height = pQuestNpcTalkAck->height;
    questNpcTalkAck.npc_guid = pQuestNpcTalkAck->npc_guid;
    questNpcTalkAck.talk_len = pQuestNpcTalkAck->talk_len;
    CopyArray(questNpcTalkAck.talk, pQuestNpcTalkAck->talk);
    questNpcTalkAck.quest_state_num = pQuestNpcTalkAck->quest_state_num;
    CopyArray(questNpcTalkAck.quest_states, pQuestNpcTalkAck->quest_states);
    questNpcTalkAck.comp = pQuestNpcTalkAck->comp;

    SendDataBySessionID(pQuestNpcTalkAck->clientSessionID, questNpcTalkAck);
}

void SessionGS2MS::HandleMapServMsg_QuestTimeoutNtf(void *pData)
{
    auto *pQuestTimeoutNtf = static_cast<ProtoMS_QuestTimeoutNtf *>(pData);

    ProtoClient3_QuestTimeoutNtf questTimeoutNtf;
    questTimeoutNtf.quest_id = pQuestTimeoutNtf->quest_id;

    SendDataBySessionID(pQuestTimeoutNtf->client_sessionid, questTimeoutNtf);
}

void SessionGS2MS::HandleMapServMsg_QuestUpdateNtf(void *pData)
{
    const auto *pQuestUpdateNtf = static_cast<ProtoMS_QuestUpdateNtf *>(pData);

    ProtoClient3_QuestUpdateNtf questUpdateNtf;
    questUpdateNtf.quest_id = pQuestUpdateNtf->quest_id;
    questUpdateNtf.data_type = pQuestUpdateNtf->data_type;
    questUpdateNtf.id = pQuestUpdateNtf->id;
    questUpdateNtf.value = pQuestUpdateNtf->value;

    SendDataBySessionID(pQuestUpdateNtf->client_sessionid, questUpdateNtf);
}

void SessionGS2MS::HandleMapServMsg_QuestDropNtf(void *pData)
{
    const auto *pQuestDropNtf = static_cast<ProtoMS_QuestDropNtf *>(pData);

    ProtoClient3_QuestDropNtf questDropNtf;
    questDropNtf.quest_id = pQuestDropNtf->quest_id;

    SendDataBySessionID(pQuestDropNtf->sessionid, questDropNtf);
}

void SessionGS2MS::HandleMapServMsg_QuestStateNtf(void *pData)
{
    const auto *pQuestStateNtf = static_cast<ProtoMS_QuestStateNtf *>(pData);

    ProtoClient3_QuestStateNtf questStateNtf;
    questStateNtf.quest_id = pQuestStateNtf->quest_id;
    questStateNtf.state = pQuestStateNtf->state;

    SendDataBySessionID(pQuestStateNtf->sessionid, questStateNtf);
}

void SessionGS2MS::HandleMapServMsg_QuestNpcStateNtf(void *pData)
{
    const auto *pQuestNpcStateNtf = static_cast<ProtoMS_QuestNpcStateNtf *>(pData);

    ProtoClient3_QuestNpcStateNtf questNpcStateNtf;
    questNpcStateNtf.npc_id = pQuestNpcStateNtf->npc_id;
    questNpcStateNtf.state = pQuestNpcStateNtf->state;

    SendDataBySessionID(pQuestNpcStateNtf->sessionid, questNpcStateNtf);
}

void SessionGS2MS::HandleMapServMsg_RoleAttrExtRefNtf(void *pData)
{
    const auto *pRoleAttrExtRefNtf = static_cast<ProtoMS_RoleAttrExtRefNtf *>(pData);

    ProtoClient3_RoleAttrExtRefNtf roleAttrExtRefNtf;
    roleAttrExtRefNtf.attr_name = pRoleAttrExtRefNtf->attr_name;
    roleAttrExtRefNtf.attr_value = pRoleAttrExtRefNtf->attr_value;

    SendDataBySessionID(pRoleAttrExtRefNtf->sessionid, roleAttrExtRefNtf);
}

void SessionGS2MS::HandleMapServMsg_LevelUpNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_LevelUpNtf *>(pData);

    ProtoClient3_LevelUpNtf ntf;
    ntf.player_guid = msg->player_guid;
    ntf.level = msg->level;

    SendDataBySessionID(msg->sessionid, ntf);
}

void SessionGS2MS::HandleMapServMsg_RoleAppNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_RoleAppNtf *>(pData);

    ProtoClient3_RoleAppNtf2 ntf;
    ntf.player_guid = msg->player_guid;
    ntf.hair = msg->hair;
    ntf.hair_color = msg->hair_color;
    ntf.body = msg->body;
    ntf.weapon = msg->weapon;
    ntf.wings = msg->wings;
    ntf.mount = msg->mount;
    ntf.weapon_effect = msg->weapon_effect;
    ntf.body_effect = msg->body_effect;
    ntf.mount_effect = msg->mount_effect;
    ntf.amulet = msg->amulet;
    ntf.equip_num = msg->equip_num;
    std::copy_n(msg->equips, msg->equip_num, ntf.equips);
    ntf.is_first = msg->is_first;

    SendDataBySessionID(msg->sessionid, ntf);
}

void SessionGS2MS::HandleMapServMsg_FamilyNoticeAck(void *pData)
{
    const auto *msg = static_cast<ProtoMS_FamilyNoticeAck *>(pData);

    ProtoClient2_FamilyNoticeAck data;
    data.notice_len = msg->notice_len;
    strcpy_s(data.notice, _countof(data.notice), msg->notice);

    SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_FamilyMembersAck(void *pData)
{
    const auto *msg = static_cast<ProtoMS_FamilyMembersAck *>(pData);

    ProtoClient2_FamilyMembersAck data;
    data.total_num = msg->total_num;
    data.first_index = msg->first_index;
    data.members_num = msg->members_num;
    std::copy(msg->members, msg->members + msg->members_num, data.members);

    SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_FamilyEnemyAck(void *pData)
{
    const auto *msg = static_cast<ProtoMS_FamilyEnemyAck *>(pData);

    ProtoClient2_FamilyEnemyAck data;
    data.total_num = msg->total_num;
    data.first_index = msg->first_index;
    data.enemy_num = msg->enemy_num;
    std::copy(msg->enemy, msg->enemy + msg->enemy_num, data.enemy);

    SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_FamilyAllyAck(void *pData)
{
    const auto *msg = static_cast<ProtoMS_FamilyAllyAck *>(pData);

    ProtoClient2_FamilyAllyAck data;
    data.total_num = msg->total_num;
    data.first_index = msg->first_index;
    data.ally_num = msg->ally_num;
    std::copy(msg->ally, msg->ally + msg->ally_num, data.ally);

    SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_FamilyJoinListAck(void *pData)
{
    const auto *msg = static_cast<ProtoMS_FamilyJoinListAck *>(pData);

    ProtoClient2_FamilyJoinListAck data;
    data.total_num = msg->total_num;
    data.first_index = msg->first_index;
    data.num = msg->num;
    std::copy(msg->info, msg->info + msg->num, data.info);

    SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_FamilyBaseInfoAck(void *pData)
{
    const auto *msg = static_cast<ProtoMS_FamilyBaseInfoAck *>(pData);

    ProtoClient2_FamilyBaseInfoAck data;
    data.family_guid = msg->family_guid;
    strcpy_s(data.name, _countof(data.name), msg->name);
    data.members_num = msg->members_num;
    data.create_time = msg->create_time;
    data.self_title_id = msg->self_title_id;

    SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_FamilyListNtfAck(void *pData)
{
    const auto *msg = static_cast<ProtoMS_FamilyListNtfAck *>(pData);

    ProtoClient2_FamilyListNtfAck data;
    data.total_num = msg->total_num;
    data.first_index = msg->first_index;
    data.num = msg->num;
    std::copy(msg->familys, msg->familys + msg->num, data.familys);

    SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_PopDlgMsgNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_PopDlgMsgNtf *>(pData);

    ProtoClient7_PopDlgMsgNtf data;
    strcpy_s(data.msg, _countof(data.msg), msg->msg);

    SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_PlayerFamilyChangeNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_PlayerFamilyChangeNtf *>(pData);

    ProtoClient3_PlayerFamilyChangeNtf data;
    data.player_guid = msg->player_guid;
    strcpy_s(data.family_name, _countof(data.family_name), msg->family_name);
    strcpy_s(data.castle_name, _countof(data.castle_name), msg->castle_name);
    data.title = msg->title;

    SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_CancelFamilyJoinAck(void *pData)
{
    const auto *msg = static_cast<ProtoMS_CancelFamilyJoinAck *>(pData);

    ProtoClient2_CancelFamilyJoinAck data;
    data.guid = msg->guid;
    data.errcode = msg->errcode;

    SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_FamilyLeaveNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_FamilyLeaveNtf *>(pData);

    ProtoClient2_FamilyLeaveNtf data;
    strcpy_s(data.kicker_name, _countof(data.kicker_name), msg->kicker_name);
    strcpy_s(data.family_name, _countof(data.family_name), msg->family_name);

    SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_FamilyInfoNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_FamilyInfoNtf *>(pData);

    ProtoClient2_FamilyInfoNtf data;
    data.type = msg->type;

    SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_PlayerQueryNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_PlayerQueryNtf *>(pData);

    auto data = std::make_unique<ProtoClient3_PlayerQueryNtf>();    // 结构体太大只能new，否则栈溢出
    data->player_guid = msg->player_guid;
    strcpy_s(data->name, _countof(data->name), msg->name);
    data->gender = msg->gender;
    data->job = msg->job;
    data->level = msg->level;
    strcpy_s(data->family_name, _countof(data->family_name), msg->family_name);
    strcpy_s(data->family_title, _countof(data->family_title), msg->family_title);
    strcpy_s(data->alias, _countof(data->alias), msg->alias);
    data->item_num = msg->item_num;
	data->isFinalPack = msg->isFinalPack;
    std::copy(msg->item_info, msg->item_info + msg->item_num, data->item_info);

    SendDataBySessionID(msg->sessionid, *data);
}

void SessionGS2MS::HandleMapServMsg_QuickBarSetNtf(void* pData)
{
	const auto *msg = static_cast<ProtoMS_QuickBarSetNtf*>(pData);
	ProtoClient3_QuickBarSetNtf data;
	data.num = msg->num;
	std::copy(msg->info, msg->info + msg->num, data.info);
	SendDataBySessionID(msg->sessid, data);
}

void SessionGS2MS::HandleMapServMsg_GlobalNtf(void* pData)
{
	auto* msg = (ProtoMS_GlobalNtf*)(pData);
	ProtoClient3_GlobalNtf ack;
	ack.int_count = msg->int_count;
	std::copy(msg->int_data, msg->int_data + msg->int_count, ack.int_data);
	ack.str_count = msg->str_count;
	std::copy(msg->str_data, msg->str_data + msg->str_count, ack.str_data);
	SendDataBySessionID(msg->sessid, ack);
}

void SessionGS2MS::HandleMapServMsg_MsgNtf(void* pData)
{
	auto pMsgNtf = (ProtoMS_MsgNtf*)pData;

	ProtoClient7_MsgNtf MsgNtf;
	MsgNtf.background = pMsgNtf->background;
	MsgNtf.count = pMsgNtf->count;
	MsgNtf.foreground = pMsgNtf->foreground;
	MsgNtf.type = pMsgNtf->site;
	strcpy_s(MsgNtf.msg, _countof(MsgNtf.msg), pMsgNtf->msg);

	SendDataBySessionID(pMsgNtf->sessionid, MsgNtf);
}

void SessionGS2MS::HandleMapServMsg_NewMailNtf(void* pData)
{
	auto msg = (ProtoMS_NewMailNtf*)pData;
	ProtoClient2_NewMailNtf ack;
	SendDataBySessionID(msg->sessid, ack);
}

void SessionGS2MS::HandleMapServMsg_GetMailListAck(void* pData)
{
	auto msg = (ProtoMS_GetMailListAck*)pData;
	ProtoClient2_MaillistAck ack;
	ack.cur_page = msg->cur_page;
	ack.page_num = msg->page_num;
	ack.num = msg->num;
	for (int i = 0; i < msg->num; ++i) {
		ack.mails[i] = msg->mails[i];
	}
	SendDataBySessionID(msg->sessid, ack);
}

void SessionGS2MS::HandleMapServMsg_DeleteMailAck(void* pData)
{
	auto msg = (ProtoMS_DeleteMailAck*)pData;
	ProtoClient2_MailDeleteAck ack;
	ack.id = msg->mail_id;
	ack.errcode = msg->errcode;
	SendDataBySessionID(msg->sessid, ack);
}

void SessionGS2MS::HandleMapServMsg_OpenMailAck(void* pData)
{
	auto msg = (ProtoMS_OpenMailAck*)pData;
	MSG_BUFFER_DATA(ProtoClient2_MailOpenAck2, ack);
	ack.mail_id = msg->mail_id;
	ack.mail = msg->mail;
	SendDataBySessionID(msg->sessid, ack);
}

void SessionGS2MS::HandleMapServMsg_MailAttachmentGetAck(void* pData)
{
	auto msg = (ProtoMS_MailAttachmentGetAck*)pData;
	ProtoClient2_MailAttachmentGetAck ack;
	ack.mail_id = msg->mail_id;
	ack.index = msg->index;
	ack.errcode = msg->errcode;
	SendDataBySessionID(msg->sessid, ack);
}

void SessionGS2MS::HandleMapServMsg_MissNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_MissNtf *>(pData);

    ProtoClient3_MissNtf data;
    data.actor = msg->actor;
    data.target = msg->target;
    data.skill_id = msg->skill_id;
    data.type = msg->type;

    for (auto i = 0; i < msg->clsessnum; ++i) {
        SendDataBySessionID(msg->clsessids[i], data, true);
    }
}

void SessionGS2MS::HandleMapServMsg_RecordsMineAck(void* pData)
{
	auto* msg = static_cast<ProtoMS_RecordsMineAck*>(pData);
	// 保证字节对齐
	ProtoClient3_RecordsMineAck data;
	msg->moduleid = data.moduleid;
	msg->protocolid = data.protocolid;
	memcpy_s(&data, sizeof(data), msg, sizeof(ProtoClient3_RecordsMineAck));

	SendDataBySessionID(msg->sessid, data);
}

void SessionGS2MS::HandleMapServMsg_DelegateMineAck(void* pData)
{
	auto* msg = static_cast<ProtoMS_DelegateMineAck*>(pData);
	// 保证字节对齐
	ProtoClient3_DelegateMineAck2 data;
	msg->moduleid = data.moduleid;
	msg->protocolid = data.protocolid;
	memcpy_s(&data, sizeof(data), msg, sizeof(ProtoClient3_DelegateMineAck2));

	SendDataBySessionID(msg->sessid, data);
}

void SessionGS2MS::HandleMapServMsg_DelegateSellListAck(void* pData)
{
	auto* msg = static_cast<ProtoMS_DelegateSellListAck*>(pData);
	// 保证字节对齐
	ProtoClient3_DelegateSellListAck data;
	msg->moduleid = data.moduleid;
	msg->protocolid = data.protocolid;
	memcpy_s(&data, sizeof(data), msg, sizeof(ProtoClient3_DelegateSellListAck));

	SendDataBySessionID(msg->sessid, data);
}

void SessionGS2MS::HandleMapServMsg_DelegateBuyListAck(void* pData)
{
	auto* msg = static_cast<ProtoMS_DelegateBuyListAck*>(pData);
	// 保证字节对齐
	ProtoClient3_DelegateBuyListAck2 data;
	msg->moduleid = data.moduleid;
	msg->protocolid = data.protocolid;
	memcpy_s(&data, sizeof(data), msg, sizeof(ProtoClient3_DelegateBuyListAck2));

	SendDataBySessionID(msg->sessid, data);
}

void SessionGS2MS::HandleMapServMsg_DeleteSkillAck(void* pData)
{
	auto* msg = static_cast<ProtoMS_DeleteSkillAck*>(pData);
	// 保证字节对齐
	ProtoClient3_SkillDeleteAck data;
	data.id = msg->skillid;
	SendDataBySessionID(msg->nClientSessionID, data);
}

void SessionGS2MS::HandleMapServMsg_SkillStatusNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_SkillStatusNtf *>(pData);

    ProtoClient3_SkillStatusNtf data;
    ASSIGN_MEMBER(id);
    ASSIGN_MEMBER(active);

    SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_SkillPropPermanetChangedNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_SkillPropPermanentChangedNtf *>(pData);

	MSG_BUFFER_DATA(ProtoClient3_SkillPropPermanentChangedNtf, data);
	ASSIGN_MEMBER(player_guid);
	data.num = msg->num;
	for (uint16_t i = 0; i < msg->num; ++i)
		data.info[i] = msg->info[i];

    SendDataBySessionID(msg->clsessid, data);
}

void SessionGS2MS::HandleMapServMsg_SkillProficiencyNtf(void *pData)
{
	const auto *msg = static_cast<ProtoMS_SkillProficiencyNtf *>(pData);

	ProtoClient3_SkillProficiencyNtf data;
	ASSIGN_MEMBER(id);
	ASSIGN_MEMBER(proficiency);

	SendDataBySessionID(msg->clsessid, data);
}

void SessionGS2MS::HandleMapServMsg_ShabakOwnerNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_ShabakOwnerNtf *>(pData);

    ProtoClient3_ShabakOwnerNtf data;
    ASSIGN_MEMBER(role_guid);

    SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_ShabakLossNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_ShabakLossNtf *>(pData);

    ProtoClient3_ShabakLossNtf data;
    ASSIGN_MEMBER(role_guid);

    SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_ShabakEngageNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_ShabakEngageNtf *>(pData);

    ProtoClient3_ShabakEngageNtf data;
    ASSIGN_STRING_MEMBER(own_family);
    ASSIGN_STRING_MEMBER(attack_families);

    SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_ShabakEndNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_ShabakEndNtf *>(pData);

    ProtoClient3_ShabakEndNtf data;

    SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_SysMsgNtf2(void* pData)
{
	auto* msg = static_cast<ProtoGS_SysMsgNtf2*>(pData);
	ProtoClient2_SysMsgNtf2 data;
	msg->moduleid = data.moduleid;
	msg->protocolid = data.protocolid;
	memcpy(&data, msg, sizeof(ProtoClient2_SysMsgNtf2));
	if (msg->all == 1)
	{
		SendDataBySessionType(SESSION_TYPE_GS2CL, data, true);
	}
	else
	{
		SendDataBySessionID(msg->sessid, data);
	}
}

void SessionGS2MS::HandleMapServMsg_SceneDialogNtf(void* pData)
{
	auto* msg = static_cast<ProtoGS_SceneDialogNtf*>(pData);
	ProtoClient2_SceneDialogNtf data;
	msg->moduleid = data.moduleid;
	msg->protocolid = data.protocolid;
	memcpy(&data, msg, sizeof(ProtoClient2_SceneDialogNtf));
	SendDataBySessionID(msg->sessid, data);
}

void SessionGS2MS::HandleMapServMsg_ScrollText(void* pData)
{
	auto* msg = static_cast<ProtoGS_ScrollText*>(pData);
	ProtoClient2_ScrollText data;
	msg->moduleid = data.moduleid;
	msg->protocolid = data.protocolid;
	memcpy(&data, msg, sizeof(ProtoClient2_ScrollText));
	if (msg->all == 1)
	{
		SendDataBySessionType(SESSION_TYPE_GS2CL, data, true);
	}
	else
	{
		SendDataBySessionID(msg->sessid, data);
	}

	
}

void SessionGS2MS::HandleMapServMsg_TradeListUpdate(void* pData)
{
	const auto* msg = static_cast<ProtoGS_TradeMallListUpdate*>(pData);
	ProtoClient3_TradeMallListUpdate data;
	data.item_count = msg->item_count;
	memcpy_s(data.item_list, sizeof(data.item_list), msg->item_list, sizeof(msg->item_list));
	SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_KickOutRole(void* pData)
{
	const auto* msg = static_cast<ProtoGS_KickOutByLock*>(pData);

	//if (msg->type) {
	//	ProtoGS_LogoutReq logout;
	//	logout.info = msg->info;
	//	auto& map = SessionContextMgr::GetInstance()->GetSessionID2ContextMap();
	//	for (auto& i : map)
	//	{
	//		if (i.second == nullptr)continue;
	//		logout.sessionid = i.second->nSessionID;
	//		logout.token = i.second->nToken;
	//		SendDataBySessionType(SESSION_TYPE_GS2LS, logout);
	//	}
	//}
	//else {
	SendDataBySessionType(SESSION_TYPE_GS2LS, *msg);
	//}
}

void SessionGS2MS::HandleMapServMsg_GetNpcPosAck(void* pData)
{
	const auto* msg = static_cast<ProtoGS_GetNpcPosAck*>(pData);
	ProtoClient3_GetNpcPosAck data;
	data.posx = msg->posx;
	data.posy = msg->posy;
	data.result = msg->result;
	SendDataBySessionID(msg->sessionid,data);
}

void SessionGS2MS::HandleMapServMsg_RunningFamilyWarNtf(void* pData)
{
	const auto* msg = static_cast<ProtoMS_RunningFamilyWarNtf*>(pData);

	ProtoClient3_RunningFamilyWarNtf data;
	data.idx = msg->idx;
	data.total = msg->total;
	data.num = msg->num;
	memcpy_s(data.families, sizeof(data.families), msg->families, sizeof(msg->families));
	SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_SetServerStatus(void* pData)
{
	auto AllRoleLogoutFunc = []() {
		ProtoGS_LogoutReq logout;
		logout.info = 1;
		auto& map = SessionContextMgr::GetInstance()->GetSessionID2ContextMap();
		for (auto& i : map)
		{
			if (i.second == nullptr)continue;
			logout.sessionid = i.second->nSessionID;
			logout.token = i.second->nToken;
			SendDataBySessionType(SESSION_TYPE_GS2LS, logout);

			ProtoClient3_ExitGSAck pAck;
			pAck.exittype = E_EXIT_EXITGS;
			ISession* pGateServ = CNetManager::GetInstance()->GetSessionByID(i.second->nSessionID);
			if (pGateServ) {
				pGateServ->SendPkg(&pAck, sizeof(pAck));
			}
		}

	};
	const auto* msg = static_cast<ProtoMS_SetServerStatus*>(pData);
	if (msg->status == server_status_maintenance)
	{
		AllRoleLogoutFunc();
		ProtoGS_SetMaintenanceStatus data;
		data.status = msg->status;
		SendDataBySessionType(SESSION_TYPE_GS2LS, data);
	}
	else if(msg->status == server_status_reset_maintenance)
	{
		ProtoGS_SetMaintenanceStatus data;
		data.status = msg->status;
		SendDataBySessionType(SESSION_TYPE_GS2LS, data);
	}
	else if(msg->status == server_status_close)
	{
		// 关服后禁止玩家登录
		GateServer::GetInstance()->SetCloseServerState();

		AllRoleLogoutFunc();
		TimerData timer;
		timer.interval = CLOSE_SERVER_DELAY_TIME;
		timer.loop = false;
		timer.callBack = [this](const TimerData&) {
			GateServer::GetInstance()->Quit();
		};
		TimeHelper::GetInstance()->AddTimer(timer);
	}
}

void SessionGS2MS::HandleMapServMsg_MonsterPursureStatusChangedNtf(void* pData)
{
	const auto* msg = static_cast<ProtoMS_MonsterPursureAttackingNtf*>(pData);

	ProtoClient3_MonsterPursureAttackingNtf data;
	data.guid = msg->guid;
	data.status = msg->status;
	SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_PlayerSetNameNtf(void* pData)
{
	const auto* msg = static_cast<ProtoGS_PlayerSetNameNtf*>(pData);
	ProtoClient3_PlayerSetNameNtf data;
	data.guid = msg->guid;
	strcpy_s(data.name, _countof(data.name), msg->name);
	strcpy_s(data.orgName, _countof(data.orgName), msg->orgName);
	SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_ItemTipNtf(void* pData)
{
	const auto* msg = static_cast<ProtoGS_ItemTipNtf*>(pData);
	ProtoClient3_ItemTipNtf data;
	data.info = msg->infos;
	SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_CustMsgNtf(void* pData)
{
	auto* msg = static_cast<ProtoGS_CustMsgNtf*>(pData);
	ProtoClient2_CustMsgNtf data;
	msg->moduleid = data.moduleid;
	msg->protocolid = data.protocolid;
	memcpy(&data, msg, sizeof(ProtoClient2_CustMsgNtf));
	SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_TitleAddAck(void* pData)
{
	auto* msg = static_cast<ProtoGS_TitleAddAck*>(pData);
	ProtoClient3_TitleAddAck data;
	data.info = msg->info;
	SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_TitleDelAck(void* pData)
{
	auto* msg = static_cast<ProtoGS_TitleDelAck*>(pData);
	ProtoClient3_TitleDelAck data;
	ASSIGN_MEMBER(id);
	ASSIGN_MEMBER(err);
	SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_TitleList(void* pData)
{
	auto* msg = static_cast<ProtoGS_TitleList*>(pData);
	ProtoClient3_TitleList data;
	ASSIGN_MEMBER(num);
	ASSIGN_ARRAY_MEMEBER(info);
	SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_TitleWearNtf(void* pData)
{
	auto* msg = static_cast<ProtoGS_TitleWearNtf*>(pData);
	ProtoClient3_TitleWearNtf data;
	ASSIGN_MEMBER(id);
	ASSIGN_MEMBER(guid);
	SendDataBySessionID(msg->sessionid, data);
}

void SessionGS2MS::HandleMapServMsg_TitleUnWearNtf(void* pData)
{
	auto* msg = static_cast<ProtoGS_TitleUnWearNtf*>(pData);
	ProtoClient3_TitleUnWearNtf data;
	ASSIGN_MEMBER(id);
	ASSIGN_MEMBER(guid);
	SendDataBySessionID(msg->sessionid, data);
}
