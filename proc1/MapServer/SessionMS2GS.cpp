#include "stdafx.h"
#include "SessionMS2GS.h"
#include "ILogHelper.h"
#include "ProtoDef.h"
#include "ProtoMS.h"
#include "ProtoCS.h"
#include "ProtoGS.h"
#include "CNetManager.h"
#include "SessionFactory.h"
#include "MapRoleMgr.h"
#include "MapMgr.h"
#include "item_table.hpp"
#include "GameMall.h"
#include "TradeMgr.h"
#include "MailMgr.h"
#include "ProhibitChatMgr.h"
#include "MonitorMsg.h"
#include "TitleMgr.h"
#include "PlayerChatProhibitMgr.h"

SessionMS2GS::SessionMS2GS()
{
}

SessionMS2GS::~SessionMS2GS()
{
}

void SessionMS2GS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());

	ProtoGS_SessionIDNtf ntf;
	ntf.protocolid = PROTO_SESSION_MS2GS_NTF;
	ntf.sessionid = GetID();
	SendPkg(&ntf, sizeof(ntf));
}

void SessionMS2GS::OnLost()
{
	Session::OnLost();
	LOG_WARN("SessionMS2GS SESSION LOST!");
}

void SessionMS2GS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    MsgCostStat::GetInstance()->BeginHandleMsg();

    switch (moduleid) {
		case MODULE_TYPE_GS:
			HandleGateServMsg(protoid, _pData);
			break;

		default:
			LOG_WARN("Unhandled moduleid: %u", moduleid);
			break;
	}

    MsgCostStat::GetInstance()->EndHandleMsg(moduleid, protoid);
}

void SessionMS2GS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("SessionMS2GS ERROR %ld", _ErrorCode);
}

void SessionMS2GS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionMS2GS::DoHeartBeat()
{
}

void SessionMS2GS::HandleGateServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_GS_HEART_BEAT_REQ, HandleGateServMsg_HeartBeatReq)
        HANDLE_MSG(PROTO_GS_CREATE_PLAYER_REQ, HandleGateServMsg_CreatePlayerReq)
        HANDLE_MSG(PROTO_GS_RELIVE_REQ, HandleGateServMsg_ReliveReq)
        HANDLE_MSG(PROTO_GS_MOVE_REQ, HandleGateServMsg_MoveReq)
        HANDLE_MSG(PROTO_GS_TURN_REQ, HandleGateServMsg_TurnReq)
        HANDLE_MSG(PROTO_GS_SPELL_TARGET, HandleGateServMsg_SpellTarget)
        HANDLE_MSG(PROTO_GS_SPELL_GRID, HandleGateServMsg_SpellGrid)
        HANDLE_MSG(PROTO_GS_EXIT_GS_REQ, HandleGateServMsg_ExitReq)
        HANDLE_MSG(PROTO_GS_SKILL_SWITCH, HandleGateServMsg_SkillSwitch)
        HANDLE_MSG(PROTO_GS_ITEM_APPLY, HandleGateServMsg_ItemApply)
        HANDLE_MSG(PROTO_GS_ITEM_PICK_UP, HandleGateServMsg_ItemPickUp)
        HANDLE_MSG(PROTO_GS_ITEM_ARRANGE, HandleGateServMsg_ItemArrange)
        HANDLE_MSG(PROTO_GS_ITEM_DROP, HandleGateServMsg_ItemDrop)
        HANDLE_MSG(PROTO_GS_ITEM_MOVE, HandleGateServMsg_ItemMove)
        HANDLE_MSG(PROTO_GS_ITEM_SPLIT, HandleGateServMsg_ItemSplit)
        HANDLE_MSG(PROTO_GS_RUN_SERV_SCRIPT_REQ, HandleGateServMsg_RunServScriptReq)
        HANDLE_MSG(PROTO_GS_RELATION_CHAT_REQ, HandleGateServMsg_RelationChatReq)
        HANDLE_MSG(PROTO_GS_PRIVATE_CHAT_NTF, HandleGateServMsg_PrivateChatNtf)
        HANDLE_MSG(PROTO_GS_SPEAKER_MSG_REQ, HandleGateServMsg_SpeakerMsgReq)
        HANDLE_MSG(PROTO_GS_TRADE_MALL_BUY, HandleGateServMsg_TradeMallBuy)
        HANDLE_MSG(PROTO_GS_TRADE_MALL_LIST_REQ, HandleGateServMsg_TradeMallListReq)
        HANDLE_MSG(PROTO_GS_NPC_SELECT, HandleGateServMsg_NpcSelect)
        HANDLE_MSG(PROTO_GS_NPC_TALK_REQ, HandleGateServMsg_NpcTalkReq)
        HANDLE_MSG(PROTO_GS_TRADE_NPC_BUY, HandleGateServMsg_TradeNpcBuy)
        HANDLE_MSG(PROTO_GS_ATK_MODE_REQ, HandleGateServMsg_AtkModeReq)
        HANDLE_MSG(PROTO_GS_QUEST_QUERY_CAN_ACCEPT, HandleGateServMsg_QuestQueryCanAccept)
        HANDLE_MSG(PROTO_GS_QUEST_ACCEPT, HandleGateServMsg_QuestAccept)
        HANDLE_MSG(PROTO_GS_QUEST_DROP, HandleGateServMsg_QuestDrop)
        HANDLE_MSG(PROTO_GS_QUEST_ACCOMPLISH, HandleGateServMsg_QuestAccomplish)
        HANDLE_MSG(PROTO_GS_TEAM_OPERATION, HandleGateServMsg_TeamoperationReq)
        HANDLE_MSG(PROTO_GS_TEAM_LEAVE_REQ, HandleGateServMsg_TeamLeaveReq)
        HANDLE_MSG(PROTO_GS_TEAM_KICK_REQ, HandleGateServMsg_TeamKickReq)
        HANDLE_MSG(PROTO_GS_PLAYER_SWITCH_REQ, HandleGateServMsg_PlayerSwitchReq)
        HANDLE_MSG(PROTO_GS_TEAM_INVITE, HandleGateServMsg_TeamInvite)
        HANDLE_MSG(PROTO_GS_TEAM_INVITE_RSP, HandleGateServMsg_TeamInviteRsp)
        HANDLE_MSG(PROTO_GS_GET_ARROUND_TEAM_REQ, HandleGateServMsg_GetAroundTeamReq)
        HANDLE_MSG(PROTO_GS_TEAM_JOIN, HandleGateServMsg_TeamJoin)
        HANDLE_MSG(PROTO_GS_TEAM_JOIN_RSP, HandleGateServMsg_TeamJoinRsp)
        HANDLE_MSG(PROTO_GS_GET_FAMILY_INFO_REQ, HandleGateServMsg_GetFamilyInfoReq)
        HANDLE_MSG(PROTO_GS_PLAYER_QUERY, HandleGateServMsg_PlayerQuery)
        HANDLE_MSG(PROTO_GS_QUICK_BAR_SET, HandleGateServMsg_QuickBarSet)
        HANDLE_MSG(PROTO_GS_QUICK_GOLD_TAKE, HandleGateServMsg_GoldTake)
        HANDLE_MSG(PROTO_GS_QUICK_GOLD_DEPOSIT, HandleGateServMsg_GoldDeposit)
        HANDLE_MSG(PROTO_GS_FAMILY_JOIN_REQ, HandleGateServMsg_FamilyJoinReq)
        HANDLE_MSG(PROTO_GS_CANCEL_FAMILY_JOIN_REQ, HandleGateServMsg_CancelFamilyJoinReq)
        HANDLE_MSG(PROTO_GS_FAMILY_JOIN_ACK, HandleGateServMsg_FamilyJoinAck)
        HANDLE_MSG(PROTO_GS_FAMILY_TITLE_AWARD_REQ, HandleGateServMsg_FamilyTitleAwardReq)
        HANDLE_MSG(PROTO_GS_FAMILY_EXPELL_REQ, HandleGateServMsg_FamilyExpellReq)
        HANDLE_MSG(PROTO_GS_FAMILY_NOTICE_EDIT_REQ, HandleGateServMsg_FamilyNoticeEditReq)
        HANDLE_MSG(PROTO_GS_MAIL_LIST_REQ, HandleGateServMsg_MailListReq)
        HANDLE_MSG(PROTO_GS_MAIL_OPEN_REQ, HandleGateServMsg_MailOpenReq)
        HANDLE_MSG(PROTO_GS_MAIL_ATTACHMENT_GET_REQ, HandleGateServMsg_MailAttachmentGetReq)
        HANDLE_MSG(PROTO_GS_MAIL_DEL_REQ, HandleGateServMsg_MailDelReq)
        HANDLE_MSG(PROTO_GS_FRIEND_ADD_REQ, HandleGateServMsg_FriendAddReq)
        HANDLE_MSG(PROTO_GS_FAMILY_LEAVE_OR_LAST_MSG_REQ, HandleGateServMsg_FamilyLeaveOrLastMsgReq)
        HANDLE_MSG(PROTO_GS_FAMILY_DESTROY_REQ, HandleGateServMsg_FamilyDestroyReq)
        HANDLE_MSG(PROTO_GS_RECORDS_MINE_REQ, HandleGateServMsg_RecordsMineReq)
        HANDLE_MSG(PROTO_GS_DELEGATE_MINE_REQ, HandleGateServMsg_DelegateMineReq)
        HANDLE_MSG(PROTO_GS_DELEGATE_LIST_REQ, HandleGateServMsg_DelegateListReq)
        HANDLE_MSG(PROTO_GS_DELEGATE_CANCEL_REQ, HandleGateServMsg_DelegateCancelReq)
        HANDLE_MSG(PROTO_GS_DELEGATE_SELL_CMD, HandleGateServMsg_DelegateSellCmd)
        HANDLE_MSG(PROTO_GS_DELEGATE_BUY_CMD, HandleGateServMsg_DelegateBuyCmd)
        HANDLE_MSG(PROTO_GS_MARKET_SELL_CMD, HandleGateServMsg_MarketSellCmd)
        HANDLE_MSG(PROTO_GS_MARKET_BUY_CMD, HandleGateServMsg_MarketBuyCmd)
        HANDLE_MSG(PROTO_GS_QUERY_EX, HandleGateServMsg_PlayerQueryEx)
        HANDLE_MSG(PROTO_GS_SYNC_SESSION_ID, HandleGateServMsg_SyncSessionID)
        HANDLE_MSG(PROTO_GS_JUMP_MAP_REQ, HandleGateServMsg_JumpMapReq)
        HANDLE_MSG(PROTO_GS_GET_NPC_POS_REQ, HandleGateServMsg_GetNpcPosReq)
        HANDLE_MSG(PROTO_GS_START_DIG_REQ, HandleGateServMsg_StartDigReq)
        HANDLE_MSG(PROTO_GS_RANGE_PICKUP, HandleGateServMsg_RangePickup)
        HANDLE_MSG(PROTO_GS_SYNC_CLIENT_BASE_SETTING, HandleGateServMsg_SyncClientBaseSetting)
        HANDLE_MSG(PROTO_GS_VERIFY_BUY_ITEM_INFO_REQ, HandleGateServMsg_VerifyBuyItemInfoReq)
        HANDLE_MSG(PROTO_GS_ITEM_REFRESH_REQ, HandleGateServMsg_ItemRefreshReq)
        HANDLE_MSG(PROTO_GS_ITEM_TIP, HandleGateServMsg_ItemTip)
        HANDLE_MSG(PROTO_GS_TITLE_DEL, HandleGateServMsg_TitleDel)
        HANDLE_MSG(PROTO_GS_TITLE_WEAR, HandleGateServMsg_TitleWear)
        HANDLE_MSG(PROTO_GS_TITLE_UNWEAR, HandleGateServMsg_TitleUnWear)
        HANDLE_MSG(PROTO_GS_SET_AUTO_MODE_ACK, HandleGateServMsg_SetAutoModeAck)
        HANDLE_MSG(PROTO_GS_TITLE_GET_LIST_REQ, HandleGateServMsg_TitleGetListReq)
        HANDLE_MSG(PROTO_GS_AFTER_RELOGIN_UPDATE_STATUS, HandleGateServMsg_UpdatePlayerStatus)
        HANDLE_MSG(PROTO_GS_ROLE_CUST_VAR_REQ, HandleGateServMsg_RoleCustVarReq);
        HANDLE_MSG(PROTO_GS_GOODS_POST_RECORD_ACK, HandleGateServMsg_GoodsPostRecordAck);


    END_MSG_HANDLER()
}

void SessionMS2GS::HandleGateServMsg_ItemMove(void* pData)
{
	ProtoGS_ItemMove* move = (ProtoGS_ItemMove*)pData;
	auto player = MapRoleMgr::GetInstance()->FindPlayerByToken(move->token);
	if (!player) return;
	player->ItemMove(move->item_guid, move->dest_site);
}

void SessionMS2GS::HandleGateServMsg_ItemSplit(void* pData)
{
    ProtoGS_ItemSplit* split = (ProtoGS_ItemSplit*)pData;
    auto player = MapRoleMgr::GetInstance()->FindPlayerByToken(split->token);
    if (!player) return;
    player->ItemSplit(split->item_guid, split->item_amount, split->dest_site);
}

void SessionMS2GS::HandleGateServMsg_ItemApply(void* pData)
{
	ProtoGS_ItemApply* itemApply = (ProtoGS_ItemApply*)pData;
	auto player = MapRoleMgr::GetInstance()->FindPlayer(itemApply->role_guid);
	if (!player) return;
	player->UseItem(itemApply->item_guid,itemApply->num);
}

void SessionMS2GS::HandleGateServMsg_ItemPickUp(void* pData)
{
	ProtoGS_ItemPickUp* pickup = (ProtoGS_ItemPickUp*)pData;
	auto player = MapRoleMgr::GetInstance()->FindPlayerByToken(pickup->token);
	if (!player) return;
	player->PickUpItem();
}


void SessionMS2GS::HandleGateServMsg_ItemDrop(void* pData)
{
	ProtoGS_ItemDrop* drop = (ProtoGS_ItemDrop*)pData;
	auto player = MapRoleMgr::GetInstance()->FindPlayerByToken(drop->token);
	if (!player) return;
	player->DropItem(drop->item_guid);
}

void SessionMS2GS::HandleGateServMsg_ItemArrange(void* pData)
{
    ProtoGS_ItemArrange* arrange = (ProtoGS_ItemArrange*)pData;
    auto player = MapRoleMgr::GetInstance()->FindPlayerByToken(arrange->token);
    if (!player) return;
    player->ItemArrange(arrange->type);
}

void SessionMS2GS::HandleGateServMsg_HeartBeatReq(void* pData)
{
	ProtoGS_HeartBeatAck ack;
	SendPkg(&ack, sizeof(ack));
}

void SessionMS2GS::HandleGateServMsg_CreatePlayerReq(void* pData)
{
	auto req = (ProtoGS_CreatePlayerReq*)pData;

	auto player = MapRoleMgr::GetInstance()->FindPlayer(req->role_id);

	player->SetUserID(req->playerid);
	player->SetToken(req->token);
	player->SetClSessionID(req->clientSessionID);
	player->SetGsSessionID(GetID());
	player->SetRoleBriefInfo(req->roleBriefInfo);
}

void SessionMS2GS::HandleGateServMsg_ReliveReq(void* pData)
{
	ProtoGS_PlayerReliveReq* req = (ProtoGS_PlayerReliveReq*)pData;
	if (nullptr == req) {
		return;
	}
	
	auto player = MapRoleMgr::GetInstance()->FindPlayerByToken(req->token);
	if (!player) return;
	player->Relive(req->relive_type, req->sessionid);
}

void SessionMS2GS::HandleGateServMsg_ExitReq(void* pData)
{
	ProtoGS_ExitGSReq* req = (ProtoGS_ExitGSReq*)pData;
	auto player = MapRoleMgr::GetInstance()->FindPlayer(req->nrole_guid);
    if (player) player->OnExit(req->exittype);
}

void SessionMS2GS::HandleGateServMsg_SkillSwitch(void* pData)
{
	SAFE_BEGIN;

	auto pSkillSwitch = (ProtoGS_SkillSwitch*)pData;

	LOG_TRACE("[SkillSwitch] token: %u, session: %u, skill: %u, active: %u",
		pSkillSwitch->token, pSkillSwitch->clientSessionID, pSkillSwitch->id, pSkillSwitch->active);

	auto pSkillConfig = sSkillConfig.Get(pSkillSwitch->id);
	if (!pSkillSwitch) {
		LOG_ERROR("[SkillSwitch] pSkillConfig is NULL");
		return;
	}
    if (!pSkillConfig) {
        LOG_ERROR("[pSkillConfig] pSkillConfig is NULL");
        return;
    }
	if (pSkillConfig->SkillType != skill_type_switch) {
		LOG_ERROR("[SkillSwitch] Not a switch skill");
		return;
	}

	auto pPlayer = MapRoleMgr::GetInstance()->FindPlayerByToken(pSkillSwitch->token);
	if (!pPlayer) {
		LOG_ERROR("[SkillSwitch] pPlayer is NULL");
		return;
	}

	if (!pPlayer->GetRoleSkill()->SetSkillActive(pSkillSwitch->id, pSkillSwitch->active)) {
		LOG_ERROR("[SkillSwitch] SetSkillActive failed");
		return;
	}

	ProtoGS_SkillSwitchAck skillSwitchAck;
	skillSwitchAck.token = pSkillSwitch->token;
	skillSwitchAck.clientSessionID = pSkillSwitch->clientSessionID;
	skillSwitchAck.id = pSkillSwitch->id;
	skillSwitchAck.active = pSkillSwitch->active;
	SendPkg(&skillSwitchAck, sizeof(skillSwitchAck));

	SAFE_END;
}

void SessionMS2GS::HandleGateServMsg_MoveReq(void* pData)   //处理移动请求
{
	auto pMoveReq = (ProtoGS_MoveReq*)pData;

	ProtoGS_MoveAck moveAck;
    moveAck.clsessid = pMoveReq->clsessid;
	moveAck.role_guid = pMoveReq->role_guid;
	moveAck.type = pMoveReq->type;
	moveAck.idx = pMoveReq->idx;

	auto *role = MapRoleMgr::GetInstance()->FindRole(pMoveReq->role_guid);
	if (!role) {
		LOG_ERROR("FindRole failed. role_guid: %" PRIu64, pMoveReq->role_guid);
		moveAck.ret = move_result_fail;
	}
	else {
        auto endtime = role->GetMoveTimeEnd();
        if (endtime <= pMoveReq->movetime)
        {
            auto result = role->MoveTo(pMoveReq->dst_x, pMoveReq->dst_y, pMoveReq->type);
            moveAck.ret = (result == error_ok) ? move_result_success : move_result_fail;
            moveAck.dst_x = role->GetRolePosX();
            moveAck.dst_y = role->GetRolePosY();

            auto moveSpeed = role->GetRoleProp(role_move_speed);    // 移动1格需要的毫秒数
            auto moveType = pMoveReq->type;
            auto movemis = MapServer::GetInstance()->GetMoveMistake();
            if (result == error_ok)
            {
                moveSpeed *= 2;
                role->SetMoveTimeEnd(int(moveSpeed* movemis)+ pMoveReq->movetime);
            }
        }
        else
        {
            moveAck.dst_x = role->GetRolePosX();
            moveAck.dst_y = role->GetRolePosY();
            moveAck.ret = move_result_fail;
        }
	}
	SendPkg(&moveAck, sizeof(moveAck));
}

void SessionMS2GS::HandleGateServMsg_TurnReq(void* pData)
{
	auto pTurnReq = (ProtoGS_TurnReq*)pData;

	LOG_TRACE("[TurnReq] role_guid: %" PRIu64 ", dir: %u", pTurnReq->role_guid, pTurnReq->dir);

	auto *role = MapRoleMgr::GetInstance()->FindRole(pTurnReq->role_guid);
	if (!role) {
		LOG_ERROR("[TurnReq] FindRole failed. role_guid: %llu", pTurnReq->role_guid);
		return;
	}

	role->SetRoleDir(pTurnReq->dir);
}

void SessionMS2GS::HandleGateServMsg_SpellTarget(void* pData)
{
    const auto *msg = static_cast<ProtoGS_SpellTarget *>(pData);

    LOG_TRACE("[SpellTarget] role_guid: %" PRIu64 ", skill: %u, target: %" PRIu64,
        msg->role_guid, msg->id, msg->target);

    auto *role = MapRoleMgr::GetInstance()->FindRole(msg->role_guid);
    if (!role) {
        LOG_ERROR("[SpellTarget] FindRole failed. role_guid: %llu", msg->role_guid);
        return;
    }

    role->ApplySkillOnTarget(msg->id, msg->target, msg->idx);
}

void SessionMS2GS::HandleGateServMsg_SpellGrid(void* pData)
{
    SAFE_BEGIN;

    const auto *msg = static_cast<ProtoGS_SpellGrid *>(pData);

    LOG_TRACE("[SpellGrid] role_guid: %" PRIu64 ", skill: %u, x: %u, y: %u, idx: %u, target: %" PRIu64,
        msg->role_guid, msg->id, msg->target_x, msg->target_y, msg->idx, msg->ref_target);

    auto *role = MapRoleMgr::GetInstance()->FindRole(msg->role_guid);
    if (!role) {
        LOG_ERROR("[SpellGrid] FindRole failed. role_guid: %llu", msg->role_guid);
        return;
    }

    role->ApplySkillOnGrid(msg->id, msg->ref_target, msg->target_x, msg->target_y, msg->idx, msg->extra);

    SAFE_END;
}

void SessionMS2GS::HandleGateServMsg_RunServScriptReq(void *pData)
{
    auto pRunServScript = (ProtoGS_RunServScriptReq *)pData;

    LOG_TRACE("[RunServScript] session: %u, token: %u, player: %" PRIu64,
        pRunServScript->sessionid, pRunServScript->token, pRunServScript->playerid);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayerByToken(pRunServScript->token);
    if (!pPlayer) {
        LOG_ERROR("[RunServScript] pPlayer is NULL");
        return;
    }

    auto nRoleID = pPlayer->GetGUID();

    const uint64_t FORM_M = 1 << 31;
    const uint64_t FORM_KEY1 = 8090001239;
    const uint64_t FORM_KEY2 = 202187;

    auto GenKey = [&](uint64_t raw) { return (raw * FORM_KEY1 + FORM_KEY2) % FORM_M; };

    uint64_t nRandomKey = GenKey(nRoleID);

    auto RecData = [&](void *pData, uint32_t nDataLen) {
        uint8_t *p = (uint8_t *)pData;
        uint8_t *pKey = (uint8_t *)&nRandomKey;
        uint32_t nKeyLen = sizeof(nRandomKey);

        for (uint32_t i = 0; i < nDataLen; ++i)
            p[i] ^= pKey[i % nKeyLen];
    };

    RecData(&pRunServScript->form_count, sizeof(pRunServScript->form_count));

    nRandomKey = GenKey(pRunServScript->form_count + nRandomKey);
    RecData(pRunServScript->script_name, sizeof(pRunServScript->script_name));

    //auto CheckName = [](const char *pName) -> bool {

    //    size_t len = strlen(pName);
    //    if (len == 0) return false;

    //    for (size_t i = 0; i < len; ++i)
    //        if (!isalnum(pName[i]))
    //            return false;

    //    return true;
    //};

    // 字符串含中文，暂不检查

    //if (!CheckName(pRunServScript->script_name)) {
    //    LOG_ERROR("[RunServScript] script_name is invalid");
    //    return;
    //}

    nRandomKey = GenKey(nRandomKey);
    RecData(pRunServScript->function_name, sizeof(pRunServScript->function_name));

    //if (!CheckName(pRunServScript->function_name)) {
    //    LOG_ERROR("[RunServScript] function_name is invalid");
    //    return;
    //}

    for (uint16_t i = 0; i < pRunServScript->num; ++i) {

        auto &param = pRunServScript->info[i];

        nRandomKey = GenKey(nRandomKey);
        RecData(&param.type, sizeof(param.type));

        nRandomKey = GenKey(nRandomKey);
        RecData(param.value, param.size);
    }

    pPlayer->RunServScript(pRunServScript->script_name, pRunServScript->function_name,
        pRunServScript->info, pRunServScript->num);
}

void SessionMS2GS::HandleGateServMsg_RelationChatReq(void *pData)
{
    auto pRelationChatReq = (ProtoGS_RelationChatReq *)pData;

    LOG_TRACE("[CHAT] token: %u, type: %u, message: %s",
        pRelationChatReq->token, pRelationChatReq->type, pRelationChatReq->message);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayerByToken(pRelationChatReq->token);
    if (!pPlayer) {
        LOG_ERROR("[CHAT] pPlayer is NULL");
        return;
    }
    // 禁言中 
    if (ProhibitChatMgr::GetInstance()->IsProhibitChatStatus(pPlayer->GetGUID()))
    {
        auto& data = gMESSAGE_INFO;
        data.Clear();
        strcpy_s(data.message, _countof(data.message), "您的账号已被禁言");
        strcpy_s(data.font_color, _countof(data.font_color), "#0xffffff");
        strcpy_s(data.background_color, _countof(data.background_color), "#0xff0000");
        pPlayer->SendSysMsgNtf2(data);
        return;
    }

    // 禁言中 
    if (PlayerProhibitChatMgr::GetInstance()->IsProhibitChat(pPlayer->GetUserID()))
    {
        auto& data = gMESSAGE_INFO;
        data.Clear();
        strcpy_s(data.message, _countof(data.message), "您的账号已被禁言");
        strcpy_s(data.font_color, _countof(data.font_color), "#0xffffff");
        strcpy_s(data.background_color, _countof(data.background_color), "#0xff0000");
        pPlayer->SendSysMsgNtf2(data);
        return;
    }

    //auto &roleBriefInfo = pPlayer->GetRoleBriefInfo();

    //ProtoGS_RelationChatAck relationChatAck;
    //relationChatAck.sessionid = pPlayer->GetClSessionID();
    //relationChatAck.type = pRelationChatReq->type;
    //strcpy_s(relationChatAck.chat_message.message, _countof(relationChatAck.chat_message.message), pRelationChatReq->message);
    //sprintf_s(relationChatAck.chat_message.role_name, _countof(relationChatAck.chat_message.role_name), "%s:%u:%u:%u:%u",         // 名称:等级:VIP等级:性别:职业
    //    roleBriefInfo.name, roleBriefInfo.level, 0, roleBriefInfo.gender, roleBriefInfo.job);

    //SendPkg(&relationChatAck, sizeof(relationChatAck));         // 给请求方回ACK
    auto& data = gMESSAGE_INFO;
    data.Clear();
    data.type = pRelationChatReq->type;
    data.scroll_times = 1;
    strcpy_s(data.message, _countof(data.message), pRelationChatReq->message);
    pPlayer->SendRelationChatNtf(data);
    MonitorMsg::GetInstance()->SendMonitorChatMsg(pPlayer, nullptr, pRelationChatReq->type, pRelationChatReq->message);
}

void SessionMS2GS::HandleGateServMsg_PrivateChatNtf(void *pData)
{
    auto pPrivateChatNtf = (ProtoGS_PrivateChatNtf *)pData;

    LOG_TRACE("[CHAT] token: %u, type: %u, role_name: %s, message: %s", pPrivateChatNtf->token,
        pPrivateChatNtf->type, pPrivateChatNtf->chat_message.role_name, pPrivateChatNtf->chat_message.message);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayerByToken(pPrivateChatNtf->token);
    if (!pPlayer) {
        LOG_ERROR("[CHAT] pPlayer is NULL");
        return;
    }

    if (ProhibitChatMgr::GetInstance()->IsProhibitChatStatus(pPlayer->GetGUID()))
    {
        auto& data = gMESSAGE_INFO;
        data.Clear();
        strcpy_s(data.message, _countof(data.message), "您的账号已被禁言");
        strcpy_s(data.font_color, _countof(data.font_color), "#0xffffff");
        strcpy_s(data.background_color, _countof(data.background_color), "#0xff0000");
        pPlayer->SendSysMsgNtf2(data);
        return;
    }

    // 禁言中 
    if (PlayerProhibitChatMgr::GetInstance()->IsProhibitChat(pPlayer->GetUserID()))
    {
        auto& data = gMESSAGE_INFO;
        data.Clear();
        strcpy_s(data.message, _countof(data.message), "您的账号已被禁言");
        strcpy_s(data.font_color, _countof(data.font_color), "#0xffffff");
        strcpy_s(data.background_color, _countof(data.background_color), "#0xff0000");
        pPlayer->SendSysMsgNtf2(data);
        return;
    }

    auto pTargetPlayer = MapRoleMgr::GetInstance()->GetPlayerByName(pPrivateChatNtf->chat_message.role_name);
    if (!pTargetPlayer) {
        LOG_ERROR("[CHAT] pTargetPlayer is NULL");
        return;
    }

    ProtoGS_PrivateChatNtf privateChatNtf;
    privateChatNtf.token = pTargetPlayer->GetToken();
    privateChatNtf.sessionid = pTargetPlayer->GetClSessionID();
    privateChatNtf.type = pPrivateChatNtf->type;
    strcpy_s(privateChatNtf.chat_message.message, _countof(privateChatNtf.chat_message.message), pPrivateChatNtf->chat_message.message);
    strcpy_s(privateChatNtf.chat_message.role_name, _countof(privateChatNtf.chat_message.role_name), pPlayer->GetName().c_str());

    SendDataBySessionID(pTargetPlayer->GetGsSessionID(), privateChatNtf);
    MonitorMsg::GetInstance()->SendMonitorChatMsg(pPlayer, pTargetPlayer, 0, pPrivateChatNtf->chat_message.message);
}

void SessionMS2GS::HandleGateServMsg_SpeakerMsgReq(void *pData)
{
    auto pSpeakerMsgReq = (ProtoGS_SpeakerMsgReq *)pData;

    LOG_TRACE("[CHAT] token: %u, msg: %s", pSpeakerMsgReq->token, pSpeakerMsgReq->msg);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayerByToken(pSpeakerMsgReq->token);
    if (!pPlayer) {
        LOG_ERROR("[CHAT] pPlayer is NULL");
        return;
    }

    // 禁言中 
    if (ProhibitChatMgr::GetInstance()->IsProhibitChatStatus(pPlayer->GetGUID()))
    {
        auto& data = gMESSAGE_INFO;
        data.Clear();
        strcpy_s(data.message, _countof(data.message), "您的账号已被禁言");
        strcpy_s(data.font_color, _countof(data.font_color), "#0xffffff");
        strcpy_s(data.background_color, _countof(data.background_color), "#0xff0000");
        pPlayer->SendSysMsgNtf2(data);
        return;
    }

    // 禁言中 
    if (PlayerProhibitChatMgr::GetInstance()->IsProhibitChat(pPlayer->GetUserID()))
    {
        auto& data = gMESSAGE_INFO;
        data.Clear();
        strcpy_s(data.message, _countof(data.message), "您的账号已被禁言");
        strcpy_s(data.font_color, _countof(data.font_color), "#0xffffff");
        strcpy_s(data.background_color, _countof(data.background_color), "#0xff0000");
        pPlayer->SendSysMsgNtf2(data);
        return;
    }

    ProtoGS_SpeakerMsgNtf speakerMsgNtf;
    strcpy_s(speakerMsgNtf.sender, _countof(speakerMsgNtf.sender), pPlayer->GetName().c_str());
    strcpy_s(speakerMsgNtf.msg, _countof(speakerMsgNtf.msg), pSpeakerMsgReq->msg);

    auto applyFunc = [&](Role *pRole) {

        if (!pRole->IsPlayer()) return;

        auto player = static_cast<Player *>(pRole);
        speakerMsgNtf.sessionid = player->GetClSessionID();

        SendDataBySessionID(player->GetGsSessionID(), speakerMsgNtf);
    };

    MapMgr::GetInstance()->ApplyFuncToAllMap(applyFunc);
}

void SessionMS2GS::HandleGateServMsg_TradeMallBuy(void* pData)
{
    auto tradeItemBuy = (ProtoGS_TradeMallBuy*)pData;
    auto player = MapRoleMgr::GetInstance()->FindPlayerByToken(tradeItemBuy->token);
    if (nullptr == player) {
        LOG_WARN("failed to find player. token:%u", tradeItemBuy->token);
        return;
    }

    auto item = GameMall::GetInstance()->GetMallItem(tradeItemBuy->item_index,player->GetGUID());
    if (nullptr == item) {
        LOG_WARN("failed to find mall item. itemIdx:%u", tradeItemBuy->item_index);
        player->SendErrorAck(ERR_ITEM_NOT_EXIST);
        return;
    }

    if (item->Item.num != INFINITE_ITEM_NUM && tradeItemBuy->item_amount > item->Item.num) {
        LOG_WARN("failed to buy mall item. item not enough. buy_num:%u remain_num:%u", tradeItemBuy->item_amount, item->Item.num);
        player->SendErrorAck(ERR_TRADE_STALL_ITEM_NOT_ENOUGH);
        return;
    }

    auto priceType = GameMall::ValueTypeToPriceType(item->Item.value_type);

    //uint64_t price = min(item->Item.price, item->Item.discount);
    uint64_t price = item->Item.discount;
    uint64_t cost = price * tradeItemBuy->item_amount;

    std::map<uint16_t,uint16_t> tmpMap;
    tmpMap[role_ingot]              = 3001;
    tmpMap[role_bind_ingot]         = 3002;
    tmpMap[role_integral]           = 3003;
    tmpMap[role_gold]               = 3004;
    tmpMap[role_bind_gold]          = 3005;
    bool find = false;
    for (auto it = tmpMap.begin(); it != tmpMap.end(); ++it) {
        if (priceType == it->first) {
            auto prop = player->GetRoleAttr()->GetProp64(it->first);
            if (cost > prop) {
                player->SendErrorAck(GameMall::PriceTypeToErrorCodeWhenCostNotEnough(priceType));
                return;
            }

            auto itemCfg = sItemConfig.Get(item->Item.item_id);
            if (nullptr == itemCfg) {
                return;
            }

            //有无剩余格子
            int productNum = tradeItemBuy->item_amount;
            int siteNum = productNum / itemCfg->Stack + (productNum % itemCfg->Stack == 0 ? 0 : 1);
            if (siteNum > player->GetIdleBagCount())
            {
                player->SendErrorAck(ERR_BAG_SPACE_NOT_ENOUGH);
                return;
            }
            // 添加 
            int addnum = 0;
            while (productNum > 0)
            {
                if (productNum > itemCfg->Stack)
                {
                    addnum = itemCfg->Stack;
                }
                else
                {
                    addnum = productNum;
                }
                if (player->AddItem(item->Item.item_id, addnum, itemCfg->BindType, site_range_bag, log_params{ "商店购买" }) != ERR_OK)
                {
                    player->SendErrorAck(ERR_ITEM_ADD);
                    break;
                }
                productNum  = (productNum-addnum<=0?0: productNum - addnum);
            }

            player->GetRoleAttr()->SetProp64(it->first, prop - (tradeItemBuy->item_amount - productNum) * price, log_params{ "商店购买" });

            if (item->Item.num != INFINITE_ITEM_NUM)
            {
                item->Item.num -= (tradeItemBuy->item_amount - productNum);
                item->itemPurchasedNum += (tradeItemBuy->item_amount - productNum);
            }

            find = true;
            break;
        }
    }

    if (!find){
        player->SendErrorAck(ERR_NON_CURRENCY_TYPE);
        return;
    }

    auto& mallcfg = sMallConfig.GetIDMappings();
    if (mallcfg[item->Item.item_index] == nullptr)return;
    ProtoMS_MallLimitInfoUpdate data;
    data.limit_type = mallcfg[item->Item.item_index]->LimitsType;
    data.num = 1;
    data.data[0].playerguid = player->GetGUID();
    data.data[0].item_idx = item->Item.item_index;
    data.data[0].num = item->itemPurchasedNum;
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);

    ProtoGS_TradeMallListUpdate data2GS;
    data2GS.sessionid = player->GetClSessionID();
    data2GS.item_list[data2GS.item_count] = item->Item;
    ++data2GS.item_count;
    SendDataBySessionID(player->GetGsSessionID(), data2GS);
  
}

void SessionMS2GS::HandleGateServMsg_TradeMallListReq(void* pData)
{
    auto req = (ProtoGS_TradeMallListReq*)pData;

    auto player = MapRoleMgr::GetInstance()->FindPlayerByToken(req->token);
    if (nullptr == player) {
        LOG_WARN("failed to find player. token:%u", req->token);
        return;
    }

    ProtoGS_TradeMallListAck ack;
    ack.sessionid = req->sessionid;
    ack.page_id = req->page_id;
    ack.item_count = 0;
    int maxCount = _countof(ack.item_list);
    //不限购表
    auto& mallItemNonMap = GameMall::GetInstance()->GetMallLimitNonMap();
    for (auto& it : mallItemNonMap) {
        if (it.second.Page != req->page_id) continue;
        memcpy(&ack.item_list[ack.item_count], &it.second.Item, sizeof(MALL_ITEM_INFO));
        if (++ack.item_count >= maxCount)break;
    }
    //全局表查找
    auto& mallItemMap = GameMall::GetInstance()->GetMallLimitAllMap();
    for (auto& it : mallItemMap) {
        if (it.second.Page != req->page_id) continue;
        memcpy(&ack.item_list[ack.item_count], &it.second.Item, sizeof(MALL_ITEM_INFO));
        if (++ack.item_count >= maxCount)break;
    }

    //获取个人限购表
    auto& mallPlayerItemLimitMap = GameMall::GetInstance()->GetMallLimitSinleMap();
    auto playerLimitMapIter = mallPlayerItemLimitMap.find(player->GetGUID());
    if (playerLimitMapIter != mallPlayerItemLimitMap.end())
    {
        // 从物品限制map中找到 限制及折扣信息
        for(auto &iter:playerLimitMapIter->second)
        {
            if (iter.second.Page != req->page_id) continue;
            memcpy(&ack.item_list[ack.item_count], &iter.second.Item, sizeof(MALL_ITEM_INFO));
            if (++ack.item_count >= maxCount)break;
        }
    }


    SendPkg(&ack, sizeof(ack));
}

void SessionMS2GS::HandleGateServMsg_NpcSelect(void *pData)
{
    auto pNpcSelect = (ProtoGS_NpcSelect *)pData;

    LOG_TRACE("[NPC] roleid: %" PRIu64 ", token: %u, npc_guid: %" PRIu64, pNpcSelect->roleid, pNpcSelect->token, pNpcSelect->npc_guid);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayer(pNpcSelect->roleid);
    if (!pPlayer) {
        LOG_ERROR("pPlayer is NULL");
        return;
    }

    if (pPlayer->GetToken() != pNpcSelect->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    auto pNpc = MapRoleMgr::GetInstance()->FindNpc(pNpcSelect->npc_guid);
    if (!pNpc) {
        LOG_ERROR("pNpc is NULL");
        return;
    }

    std::string scriptName = pNpc->GetConfig() ? pNpc->GetConfig()->Script : "";
    if (scriptName.empty()) return;

    auto func = scriptName + ".main";

    LuaBindCallVoid(func, pNpc->GetGUIDAsString(), pPlayer->GetGUIDAsString());
}

void SessionMS2GS::HandleGateServMsg_NpcTalkReq(void *pData)
{
    auto *msg = static_cast<ProtoGS_NpcTalkReq *>(pData);

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->roleid);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    if (player->GetToken() != msg->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    auto *npc = MapRoleMgr::GetInstance()->FindNpc(msg->npc_guid);
    if (!npc) {
        LOG_ERROR("npc is NULL");
        return;
    }

    std::string func = msg->func;

    auto vec = str_split(trim(func), "#");
    if (vec.empty()) return;

    auto params = NewLuaObj();
    for (auto i = 1; i < vec.size(); ++i) params[i] = vec[i];

    LuaBindCallVoid(vec[0], npc->GetGUIDAsString(), player->GetGUIDAsString(), params);
}

void SessionMS2GS::HandleGateServMsg_TradeNpcBuy(void *pData)
{
    auto pTradeNpcBuy = (ProtoGS_TradeNpcBuy *)pData;

    LOG_TRACE("roleid: %" PRIu64 ", token: %u, shop_id: %u, item_index: %u, item_amount: %u, is_bind: %u",
        pTradeNpcBuy->roleid, pTradeNpcBuy->token, pTradeNpcBuy->shop_id, pTradeNpcBuy->item_index,
        pTradeNpcBuy->item_amount, pTradeNpcBuy->is_bind);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayer(pTradeNpcBuy->roleid);
    if (!pPlayer) {
        LOG_ERROR("pPlayer is NULL");
        return;
    }

    if (pPlayer->GetToken() != pTradeNpcBuy->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    pPlayer->BuyItem(pTradeNpcBuy->shop_id, pTradeNpcBuy->item_index, pTradeNpcBuy->item_amount, pTradeNpcBuy->is_bind);
}

void SessionMS2GS::HandleGateServMsg_AtkModeReq(void *pData)
{
    auto pAtkModeReq = (ProtoGS_AtkModeReq *)pData;

    LOG_TRACE("roleid: %" PRIu64 ", token: %u, atk_mode: %u", pAtkModeReq->roleid, pAtkModeReq->token, pAtkModeReq->atk_mode);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayer(pAtkModeReq->roleid);
    if (!pPlayer) {
        LOG_ERROR("pPlayer is NULL");
        return;
    }

    if (pPlayer->GetToken() != pAtkModeReq->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    pPlayer->SetRoleProp(role_atk_mode, pAtkModeReq->atk_mode);
}

void SessionMS2GS::HandleGateServMsg_QuestQueryCanAccept(void *pData)
{
    auto pQuestQueryCanAccept = (ProtoGS_QuestQueryCanAccept *)pData;

    LOG_TRACE("roleid: %" PRIu64 ", token: %u", pQuestQueryCanAccept->roleid, pQuestQueryCanAccept->token);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayer(pQuestQueryCanAccept->roleid);
    if (!pPlayer) {
        LOG_ERROR("pPlayer is NULL");
        return;
    }

    if (pPlayer->GetToken() != pQuestQueryCanAccept->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    pPlayer->GetQuestDataMgr().QuestQueryCanAccept();
}

void SessionMS2GS::HandleGateServMsg_QuestAccept(void *pData)
{
    auto pQuestAccept = (ProtoGS_QuestAccept *)pData;

    LOG_TRACE("roleid: %" PRIu64 ", token: %u", pQuestAccept->roleid, pQuestAccept->token);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayer(pQuestAccept->roleid);
    if (!pPlayer) {
        LOG_ERROR("pPlayer is NULL");
        return;
    }

    if (pPlayer->GetToken() != pQuestAccept->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    pPlayer->GetQuestDataMgr().AcceptQuest(pQuestAccept->quest_id);
}

void SessionMS2GS::HandleGateServMsg_QuestDrop(void *pData)
{
    const auto *pQuestDrop = static_cast<ProtoGS_QuestDrop *>(pData);

    LOG_TRACE("roleid: %" PRIu64 ", token: %u", pQuestDrop->roleid, pQuestDrop->token);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayer(pQuestDrop->roleid);
    if (!pPlayer) {
        LOG_ERROR("pPlayer is NULL");
        return;
    }

    if (pPlayer->GetToken() != pQuestDrop->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    pPlayer->GetQuestDataMgr().DropQuest(pQuestDrop->quest_id);
}

void SessionMS2GS::HandleGateServMsg_QuestAccomplish(void *pData)
{
    const auto *pQuestAccomplish = static_cast<ProtoGS_QuestAccomplish *>(pData);

    LOG_TRACE("roleid: %" PRIu64 ", token: %u", pQuestAccomplish->roleid, pQuestAccomplish->token);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayer(pQuestAccomplish->roleid);
    if (!pPlayer) {
        LOG_ERROR("pPlayer is NULL");
        return;
    }

    if (pPlayer->GetToken() != pQuestAccomplish->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    pPlayer->GetQuestDataMgr().AccomplishQuest(pQuestAccomplish->quest_id);
}

void SessionMS2GS::HandleGateServMsg_TeamoperationReq(void* pData)
{
    auto pTeamoperationReq = (ProtoGS_Teamoperation*)pData;

    LOG_NORMAL("Teamoperation token: %u, operation: %u", pTeamoperationReq->token, pTeamoperationReq->operation);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayerByToken(pTeamoperationReq->token);
    if (!pPlayer) {
        LOG_ERROR("pPlayer is NULL");
        return;
    }

    pPlayer->GetTeamDataMgr().HandleTeamOperation(pTeamoperationReq->operation, pTeamoperationReq->content);
}

void SessionMS2GS::HandleGateServMsg_TeamLeaveReq(void* pData)
{
    auto pReq = (ProtoGS_TeamLeaveEx*)pData;

    LOG_NORMAL("TeamLeaveReq token: %u", pReq->token);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayerByToken(pReq->token);
    if (!pPlayer) {
        LOG_ERROR("pPlayer is NULL");
        return;
    }

    pPlayer->GetTeamDataMgr().HandleTeamLeave();
}

void SessionMS2GS::HandleGateServMsg_TeamKickReq(void* pData)
{
    auto pReq = (ProtoGS_TeamKickEx*)pData;

    LOG_NORMAL("TeamKickReq token: %u", pReq->token);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayerByToken(pReq->token);
    if (!pPlayer) {
        LOG_ERROR("pPlayer is NULL");
        return;
    }

    pPlayer->GetTeamDataMgr().HandleTeamKick(pReq->name);
}

void SessionMS2GS::HandleGateServMsg_PlayerSwitchReq(void* pData)
{
    auto pReq = (ProtoGS_PlayerSwitchReq*)pData;

    LOG_NORMAL("PlayerSwitchReq token: %u, id: %u, value: %u", pReq->token, pReq->id, pReq->value);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayerByToken(pReq->token);
    if (!pPlayer) {
        LOG_ERROR("pPlayer is NULL");
        return;
    }

    pPlayer->HandlePlayerSwitch(pReq->id, pReq->value);
}

void SessionMS2GS::HandleGateServMsg_TeamInvite(void* pData)
{
    auto pReq = (ProtoGS_TeamInvite*)pData;

    LOG_NORMAL("TeamInvite token: %u, invitee_name: %s", pReq->token, pReq->invitee_name);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayerByToken(pReq->token);
    if (!pPlayer) {
        LOG_ERROR("pPlayer is NULL");
        return;
    }

    pPlayer->GetTeamDataMgr().HandleTeamInvite(pReq->invitee_name);
}

void SessionMS2GS::HandleGateServMsg_TeamInviteRsp(void* pData)
{
    auto pRsp = (ProtoGS_TeamInviteRsp*)pData;

    LOG_NORMAL("TeamInvite token: %u, accept: %u,inviter_name: %s", pRsp->token, pRsp->accepted, pRsp->inviter_name);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayerByToken(pRsp->token);
    if (!pPlayer) {
        LOG_ERROR("pPlayer is NULL");
        return;
    }
    pPlayer->GetTeamDataMgr().HandleTeamInviteRsp(pRsp->accepted, pRsp->inviter_name);
}

void SessionMS2GS::HandleGateServMsg_GetAroundTeamReq(void* pData)
{
    auto pReq = (ProtoGS_GetAroundTeamReq*)pData;

    //LOG_NORMAL("TeamInvite token: %u, accept: %u,inviter_name: %s", pRsp->token, pRsp->accepted, pRsp->inviter_name);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayerByToken(pReq->token);
    if (!pPlayer) {
        LOG_ERROR("pPlayer is NULL");
        return;
    }
    pPlayer->GetTeamDataMgr().HandleTeamArround();
}

void SessionMS2GS::HandleGateServMsg_TeamJoin(void* pData)
{
    auto pReq = (ProtoGS_TeamJoin*)pData;

    LOG_NORMAL("TeamJoin team_member: %s", pReq->team_member);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayerByToken(pReq->token);
    if (!pPlayer) {
        LOG_ERROR("pPlayer is NULL");
        return;
    }
    pPlayer->GetTeamDataMgr().HandleTeamJoin(pReq->team_member);
}

void SessionMS2GS::HandleGateServMsg_TeamJoinRsp(void* pData)
{
    auto pRsp = (ProtoGS_TeamJoinResponse*)pData;

    LOG_NORMAL("TeamJoinResponse accept: %u,joiner: %s", pRsp->accepted, pRsp->joiner);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayerByToken(pRsp->token);
    if (!pPlayer) {
        LOG_ERROR("pPlayer is NULL");
        return;
    }
    pPlayer->GetTeamDataMgr().HandleTeamJoinRsp(pRsp->accepted, pRsp->joiner);
    
}

void SessionMS2GS::HandleGateServMsg_GetFamilyInfoReq(void *pData)
{
    const auto *msg = static_cast<ProtoGS_GetFamilyInfoReq *>(pData);

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->roleid);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    if (player->GetToken() != msg->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    player->GetGuildDataMgr().OnGetFamilyInfo(msg->reqType, msg->start_index, msg->req_count, msg->req_group, msg->info);
}

void SessionMS2GS::HandleGateServMsg_PlayerQuery(void *pData)
{
    const auto *msg = static_cast<ProtoGS_PlayerQuery *>(pData);

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->roleid);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    if (player->GetToken() != msg->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    player->QueryPlayerInfo(msg->player_name);
}

void SessionMS2GS::HandleGateServMsg_QuickBarSet(void* pData)
{
    const auto* msg = static_cast<ProtoGS_QuickBarSet*>(pData);
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_id);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    if (player->GetGUID() != msg->role_id) {
        LOG_ERROR("Token does not match");
        return;
    }
    player->SetQuickBarSetVec(*msg);
}

void SessionMS2GS::HandleGateServMsg_GoldTake(void* pData)
{
    const auto* msg = (ProttoGS_GoldTake*)pData;
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_id);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    if (player->GetGUID() != msg->role_id) {
        LOG_ERROR("Token does not match");
        return;
    }
    if (!player->SetGoldChangeAttr(-(msg->gold), log_params{ "gold_take" })) {
        LOG_ERROR("Take Gold Failed");
    }
}

void SessionMS2GS::HandleGateServMsg_GoldDeposit(void* pData)
{
    const auto* msg = (ProtoGS_GoldDeposit*)pData;
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_id);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    if (player->GetGUID() != msg->role_id) {
        LOG_ERROR("Token does not match");
        return;
    }
    player->SetGoldChangeAttr(msg->gold, log_params{ "gold_deposit" });
}

void SessionMS2GS::HandleGateServMsg_FamilyJoinReq(void *pData)
{
    const auto *msg = static_cast<ProtoGS_FamilyJoinReq *>(pData);

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->roleid);

    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    if (player->GetToken() != msg->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    player->GetGuildDataMgr().OnJoinGuildReq(msg->guid);
}

void SessionMS2GS::HandleGateServMsg_CancelFamilyJoinReq(void *pData)
{
    const auto *msg = static_cast<ProtoGS_CancelFamilyJoinReq *>(pData);

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->roleid);

    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    if (player->GetToken() != msg->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    player->GetGuildDataMgr().OnCancelJoinGuildReq(msg->guid);
}

void SessionMS2GS::HandleGateServMsg_FamilyJoinAck(void *pData)
{
    const auto *msg = static_cast<ProtoGS_FamilyJoinAck *>(pData);

    auto *leader = MapRoleMgr::GetInstance()->FindPlayer(msg->leader_guid);
    if (!leader) {
        LOG_ERROR("leader is NULL");
        return;
    }

    leader->GetGuildDataMgr().OnFamilyJoinAck(msg->player_guid, msg->is_allow);
}

void SessionMS2GS::HandleGateServMsg_FamilyTitleAwardReq(void *pData)
{
    const auto *msg = static_cast<ProtoGS_FamilyTitleAwardReq *>(pData);

    auto *leader = MapRoleMgr::GetInstance()->FindPlayer(msg->leader_guid);
    if (!leader) {
        LOG_ERROR("leader is NULL");
        return;
    }

    leader->GetGuildDataMgr().OnChangeGuildMemberTitle(msg->player_guid, msg->title_id);
}

void SessionMS2GS::HandleGateServMsg_FamilyExpellReq(void *pData)
{
    const auto *msg = static_cast<ProtoGS_FamilyExpellReq *>(pData);

    auto *kicker = MapRoleMgr::GetInstance()->FindPlayer(msg->kicker_guid);
    if (!kicker) {
        LOG_ERROR("kicker is NULL");
        return;
    }

    kicker->GetGuildDataMgr().OnKickGuildMember(msg->player_guid);
}
void SessionMS2GS::HandleGateServMsg_FamilyNoticeEditReq(void *pData)
{
    const auto *msg = static_cast<ProtoGS_FamilyNoticeEditReq *>(pData);

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->roleid);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    if (player->GetToken() != msg->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    player->GetGuildDataMgr().OnEditGuildNotice(msg->notice);
}
void SessionMS2GS::HandleGateServMsg_MailListReq(void* pData)
{
    auto msg = (ProtoGS_MaillistReq*)pData;
    auto player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_id);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }
    
    MailMgr::GetMailList(this, player, msg->mail_id, msg->type);

}

void SessionMS2GS::HandleGateServMsg_MailOpenReq(void* pData)
{
    auto msg = (ProtoGS_MailOpenReq*)pData;
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_id);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }
    MailMgr::OpenMail(this, player, msg->id);
}

void SessionMS2GS::HandleGateServMsg_MailAttachmentGetReq(void* pData)
{
    auto msg = (ProtoGS_MailAttachmentGetReq*)pData;
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_id);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }
    MailMgr::AttachMentGet(this, player, msg->mail_id, msg->index);
}

void SessionMS2GS::HandleGateServMsg_MailDelReq(void* pData)
{
    auto msg = (ProtoGS_MailDeleteReq*)pData;
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_id);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    MailMgr::DeleteMail(this, player, msg->id);
}

void SessionMS2GS::HandleGateServMsg_FriendAddReq(void *pData)
{
    const auto *msg = static_cast<ProtoGS_FriendAddReq *>(pData);

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->roleid);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    if (player->GetToken() != msg->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    // TODO: player->AddFriend(msg->player_name);
}

void SessionMS2GS::HandleGateServMsg_FamilyLeaveOrLastMsgReq(void *pData)
{
    const auto *msg = static_cast<ProtoGS_FamilyLeaveOrLastMsgReq *>(pData);

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->roleid);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    if (player->GetToken() != msg->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    player->GetGuildDataMgr().OnLeaveGuild(msg->byebye);
}

void SessionMS2GS::HandleGateServMsg_FamilyDestroyReq(void *pData)
{
    const auto *msg = static_cast<ProtoGS_FamilyDestroyReq *>(pData);

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->roleid);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    if (player->GetToken() != msg->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    player->GetGuildDataMgr().OnDestroyGuild();
}

void SessionMS2GS::HandleGateServMsg_RecordsMineReq(void* pData)
{
    auto* msg = static_cast<ProtoGS_RecordsMineReq*>(pData);

    auto role = MapRoleMgr::GetInstance()->FindRole(msg->role_id);
    auto player = static_cast<Player*>(role);
    if (!player)
    {
        LOG_ERROR("[%s:%d] Player:%lld is NULL. ", FUNC_LINE, msg->role_id);
        return;
    }

    uint32_t checkRes = TradeMgr::GetInstance()->HandleRecordsMineReq(this, *msg, player);
    if (checkRes != ERR_OK)
    {
        player->SendErrorAck(checkRes);
    }
    return;
}


void SessionMS2GS::HandleGateServMsg_DelegateMineReq(void* pData)
{
    auto* msg = static_cast<ProtoGS_DelegateMineReq*>(pData);

    auto role = MapRoleMgr::GetInstance()->FindRole(msg->role_id);
    auto player = static_cast<Player*>(role);
    if (!player) 
    {
        LOG_ERROR("[%s:%d] Player:%lld is NULL. ", FUNC_LINE, msg->role_id);
        return;
    }

    uint32_t checkRes = TradeMgr::GetInstance()->HandleDelegateMineReq(this, *msg, player);
    if (checkRes != ERR_OK)
    {
        player->SendErrorAck(checkRes);
    }
    return;
}

void SessionMS2GS::HandleGateServMsg_DelegateListReq(void* pData)
{
    auto* msg = static_cast<ProtoGS_DelegateListReq*>(pData);

    auto player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_id);
    if (!player)
    {
        LOG_ERROR("[%s:%d] Player:%lld is NULL. ", FUNC_LINE, msg->role_id);
        return;
    }

    uint32_t checkRes = TradeMgr::GetInstance()->HandleDelegateListReq(this, *msg, player);
    if (checkRes != ERR_OK)
    {
        player->SendErrorAck(checkRes);
    }
    return;
}

void SessionMS2GS::HandleGateServMsg_DelegateCancelReq(void* pData)
{
    auto* msg = static_cast<ProtoGS_DelegateCancelReq*>(pData);
    auto player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_id);
    if (!player)
    {
        LOG_ERROR("[%s:%d] Player:%lld is NULL. ", FUNC_LINE, msg->role_id);
        return;
    }
    uint32_t checkRes = TradeMgr::GetInstance()->HandleDelegateCancelReq(this, *msg, player);
    if (checkRes != ERR_OK)
    {
        player->SendErrorAck(checkRes);
    }
    return;
}

void SessionMS2GS::HandleGateServMsg_DelegateSellCmd(void* pData)
{
    auto* msg = static_cast<ProtoGS_DelegateSellCmd*>(pData);
    auto player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_id);
    if (!player)
    {
        LOG_ERROR("[%s:%d] Player:%lld is NULL. ", FUNC_LINE, msg->role_id);
        return;
    }
    uint32_t checkRes = TradeMgr::GetInstance()->HandleDelegateSellCmd(this, *msg, player);
    if (checkRes != ERR_OK)
    {
        player->SendErrorAck(checkRes);
    }
    return;
}

void SessionMS2GS::HandleGateServMsg_DelegateBuyCmd(void* pData)
{
    auto* msg = static_cast<ProtoGS_DelegateBuyCmd*>(pData);
    auto player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_id);
    if (!player)
    {
        LOG_ERROR("[%s:%d] Player:%lld is NULL. ", FUNC_LINE, msg->role_id);
        return;
    }
    uint32_t checkRes = TradeMgr::GetInstance()->HandleDelegateBuyCmd(this, *msg, player);
    if (checkRes != ERR_OK)
    {
        player->SendErrorAck(checkRes);
    }
}

void SessionMS2GS::HandleGateServMsg_MarketSellCmd(void* pData)
{
    auto* msg = static_cast<ProtoGS_MarketSellCmd*>(pData);
    auto player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_id);
    if (!player)
    {
        LOG_ERROR("[%s:%d] Player:%lld is NULL. ", FUNC_LINE, msg->role_id);
        return;
    }

    uint32_t checkRes = TradeMgr::GetInstance()->HandleMarketSellCmd(this, *msg, player);
    if (checkRes != ERR_OK)
    {
        player->SendErrorAck(checkRes);
    }
}

void SessionMS2GS::HandleGateServMsg_MarketBuyCmd(void* pData)
{
    auto* msg = static_cast<ProtoGS_MarketBuyCmd*>(pData);
    auto player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_id);
    if (!player)
    {
        LOG_ERROR("[%s:%d] Player:%lld is NULL. ", FUNC_LINE, msg->role_id);
        return;
    }

    uint32_t checkRes = TradeMgr::GetInstance()->HandleMarketBuyCmd(this, *msg, player);
    if (checkRes != ERR_OK)
    {
        player->SendErrorAck(checkRes);
    }
}

void SessionMS2GS::HandleGateServMsg_PlayerQueryEx(void* pData)
{
    const auto* msg = static_cast<ProtoGS_QueryEx*>(pData);

    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->self_role_id);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    if (player->GetToken() != msg->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    player->QueryPlayerInfo(msg->role_id);
}

void SessionMS2GS::HandleGateServMsg_SyncSessionID(void *pData)
{
    const auto *msg = static_cast<ProtoGS_SyncSessionID *>(pData);

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_guid);

    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    if (player->GetToken() != msg->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    player->SetClSessionID(msg->cl2gs_sessid);
    player->SetGsSessionID(GetID());
}

void SessionMS2GS::HandleGateServMsg_JumpMapReq(void *pData)
{
    const auto *msg = static_cast<ProtoGS_JumpMapReq *>(pData);

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->roleid);

    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    if (player->GetToken() != msg->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    auto result = player->JumpMap(player->GetCurMapKeyName(), msg->dst_x, msg->dst_y, msg->type);

    ProtoGS_MoveAck ack;
    ack.clsessid = player->GetClSessionID();
    ack.role_guid = msg->roleid;
    ack.type = move_type_jump;
    ack.idx = 0;
    ack.ret = result ? move_result_success : move_result_fail;
    ack.dst_x = player->GetRolePosX();
    ack.dst_y = player->GetRolePosY();

    SendPkg(&ack, sizeof(ack));
}

void SessionMS2GS::HandleGateServMsg_GetNpcPosReq(void* pData)
{
    const auto* msg = static_cast<ProtoGS_GetNpcPosReq*>(pData);
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->roleid);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }
    ProtoGS_GetNpcPosAck ack;
    ack.result = player->GetNearstNpcPosByName(ack.posx, ack.posy, msg->name);
    ack.sessionid = player->GetClSessionID();
    SendPkg(&ack, sizeof(ack));

}

void SessionMS2GS::HandleGateServMsg_StartDigReq(void *pData)
{
    const auto *msg = static_cast<ProtoGS_StartDigReq *>(pData);

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_guid);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    player->GetDigMgr().HandleDigRequest(msg->treasure_guid);
}

void SessionMS2GS::HandleGateServMsg_RangePickup(void *pData)
{
    const auto *msg = static_cast<ProtoGS_RangePickup *>(pData);

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_guid);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    player->PickUpItem(msg->pos, msg->posnum);
}

void SessionMS2GS::HandleGateServMsg_SyncClientBaseSetting(void* pData)
{
    const auto* msg = static_cast<ProtoGS_SyncClientBaseSetting*>(pData);

    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_guid);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    player->SetClientBaseSetting(msg->type, msg->value);
}

void SessionMS2GS::HandleGateServMsg_VerifyBuyItemInfoReq(void* pData)
{
    const auto* msg = static_cast<ProtoGS_VerifyBuyItemInfoReq*>(pData);

    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_guid);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    player->VerifyBuyItemInfo(msg->item_id, msg->item_count, msg->item_price);
}

void SessionMS2GS::HandleGateServMsg_ItemRefreshReq(void *pData)    // 充值后刷新物品、元宝等
{
    const auto *msg = static_cast<ProtoGS_ItemRefreshReq *>(pData);

    LOG_TRACE("[ITEM] ItemRefreshReq");

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_guid);
    if (!player) {
        LOG_ERROR("[ITEM] player is NULL");
        return;
    }

    if (player->GetToken() != msg->token) {
        LOG_ERROR("[ITEM] Token does not match");
        return;
    }

    player->SendAllBagItemsToGS();
    player->SendRoleAttrExtNtf();
}
void SessionMS2GS::HandleGateServMsg_ItemTip(void* pData)
{
    const auto* msg = static_cast<ProtoGS_ItemTip*>(pData);
    auto* ownerPlayer = MapRoleMgr::GetInstance()->FindPlayer(msg->owner_guid);
    if (!ownerPlayer) {
        ProtoMS_ItemTip req;
        req.guid = msg->guid;
        req.item_guid = msg->item_guid;
        req.owner_guid = msg->owner_guid;
        SendDataBySessionType(SESSION_TYPE_MS2CS, req);
        return;
    }

    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->guid);
    if (!player) {
        LOG_ERROR("GetItemTip player's is NULL");
        return;
    }

    auto rolepack = ownerPlayer->GetRolePack();
    if(!rolepack){
        LOG_ERROR("GetItemTip ownerplayer's RolePack is NULL");
        return;
    }

    auto item = rolepack->FindItem(msg->item_guid);
    if (!item) {
        LOG_ERROR("GetItemTip ownerplayer's item is NULL");
        return;
    }

    MSG_BUFFER_DATA(ProtoGS_ItemTipNtf, data);
    item->GenerateItemInfo(data.infos);
    data.sessionid = player->GetClSessionID();
    SendPkg(&data, sizeof(data));
}

void SessionMS2GS::HandleGateServMsg_TitleDel(void* pData)
{
    const auto* msg = static_cast<ProtoGS_TitleDel*>(pData);
    ProtoGS_TitleDelAck ack;
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->guid);
    if (!player)
    {
        LOG_ERROR("del title player is NULL");
        return;
    }
    auto result = player->GetTitleData().DelTitle(msg->id);
    if (!result) {
        ack.id = msg->id;
        ack.err = ERR_TITLE_DEL_ERR;
        SendPkg(&ack, sizeof(ack));
    }
}

void SessionMS2GS::HandleGateServMsg_TitleWear(void* pData)
{
    const auto* msg = static_cast<ProtoGS_TitleWear*>(pData);
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->guid);
    if (!player)
    {
        LOG_ERROR("wear title player is NULL");
        return;
    }
    player->GetTitleData().WearTitle(msg->id);

}

void SessionMS2GS::HandleGateServMsg_TitleUnWear(void* pData)
{
    const auto* msg = static_cast<ProtoGS_TitleUnWear*>(pData);
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->guid);
    if (!player)
    {
        LOG_ERROR("unwear title player is NULL");
        return;
    }
    player->GetTitleData().UnWearTitle(msg->id);
}

void SessionMS2GS::HandleGateServMsg_SetAutoModeAck(void *pData)
{
    const auto *msg = static_cast<ProtoGS_SetAutoModeAck *>(pData);

    auto *role = MapRoleMgr::GetInstance()->FindRole(msg->role_guid);
    if (!role) {
        LOG_ERROR("FindRole failed. role_guid: %llu", msg->role_guid);
        return;
    }

    if (role->IsPlayerDoplganr()) {
        auto *doplganr = static_cast<PlayerDoplganr *>(role);
        doplganr->SetAutoMode(msg->enable);
    }
}

void SessionMS2GS::HandleGateServMsg_TitleGetListReq(void* pData)
{
    const auto* msg = static_cast<ProtoGS_TitleGetListReq*>(pData);
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->guid);
    if (!player) {
        LOG_ERROR("FindRole failed. guid: %llu", msg->guid);
        return;
    }
    player->GetTitleListReq();
}

void SessionMS2GS::HandleGateServMsg_UpdatePlayerStatus(void* pData)
{
    const auto* msg = static_cast<ProtoGS_AfterReloginUpdateStatus*>(pData);
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->guid);
    if (!player) {
        LOG_ERROR("relogin update status failed. guid: %llu", msg->guid);
        return;
    }

    if (player->GetRoleState()->GetState() == role_state_die) {
        AttackResult res;
        res.targetGUID = player->GetGUID();
        player->NotifyPlayer_RoleDie(player, res);
    }

    player->UpdateReloginInfo();
}

void SessionMS2GS::HandleGateServMsg_RoleCustVarReq(void* pData)
{
    const auto* msg = static_cast<ProtoGS_RoleCustVarReq*>(pData);
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_guid);
    if (!player) {
        LOG_ERROR("RoleCustVarReq failed. guid: %llu", msg->role_guid);
        return;
    }

    MSG_BUFFER_DATA(ProtoMS_RoleCustVarNtf, ntf);
    player->GenRoleCustVar(ntf);
    ntf.sessid = msg->sessionid;
    SendPkg(&ntf, sizeof(ntf));
}

void SessionMS2GS::HandleGateServMsg_GoodsPostRecordAck(void* pData)
{
    const auto* msg = static_cast<ProtoGS_GoodsPostRecordAck*>(pData);
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->guid);
    if (!player) {
        LOG_ERROR("GoodsPostRecordAck failed. guid: %llu", msg->guid);
        return;
    }
    player->HandleGoodsPostRecordAck(msg->order_no);
}