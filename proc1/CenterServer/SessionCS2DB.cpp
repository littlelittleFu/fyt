#include "stdafx.h"
#include "SessionCS2DB.h"
#include "ILogHelper.h"
#include "CNetManager.h"

#include "SessionCS2MS.h"
#include "SessionFactory.h"
#include "UserMgr.h"
#include "GuildData.h"
#include "CustVarData.h"
#include "TopList.h"
#include "TradeData.h"
#include "GameMallMgr.h"
#include "WantedList.h"
#include "Title.h"
#include "SyncInfoToPlatformMgr.h"
#include "CustListMgr.h"

#include "ProtoGS.h"
#include "ProtoCS.h"
#include "ProtoMS.h"
#include "ProtoDB.h"
#include "SessionCS2MS.h"

SessionCS2DB::SessionCS2DB()
{

}

SessionCS2DB::~SessionCS2DB()
{

}

void SessionCS2DB::OnEstablish(SOCKET _Socket)
{
	LOG_NORMAL("Connection established. Remote host: %s:%u", GetRemoteIp().c_str(), GetRemotePort());
	Session::OnEstablish(_Socket);
}

void SessionCS2DB::OnLost()
{
	LOG_WARN("Lost connection with remote host: %s:%u", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionCS2DB::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    MsgCostStat::GetInstance()->BeginHandleMsg();

    OnHeartBeat();

	switch (moduleid) {

		case MODULE_TYPE_CS:
			HandleCenterServMsg(protoid, _pData);
			break;

		case MODULE_TYPE_GS:
			HandleGateServMsg(protoid, _pData);
			break;

		case MODULE_TYPE_MS:
			HandleMapServMsg(protoid, _pData);
			break;

        case MODULE_TYPE_DB:
            HandleDBServMsg(protoid, _pData);
            break;

		default:
			LOG_WARN("Unhandled moduleid: %u", moduleid);
			break;
	}

    MsgCostStat::GetInstance()->EndHandleMsg(moduleid, protoid);
}

void SessionCS2DB::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode: %u", _ErrorCode);
}

void SessionCS2DB::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionCS2DB::DoHeartBeat()
{
	ProtoCS_HeartBeatReq req;
	SendPkg(&req, sizeof(req));
}

void SessionCS2DB::HandleCenterServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_CS_HEART_BEAT_ACK, HandleCenterServMsg_HeartBeatAck)
        HANDLE_MSG(PROTO_CS_GET_ROLE_DATA_ACK, HandleCenterServMsg_GetRoleDataAck)
        HANDLE_MSG(PROTO_CS_GET_ITEM_ACK, HandleCenterServMsg_GetItemAck)
        HANDLE_MSG(PROTO_CS_GET_ROLE_INFO_ACK, HandleCenterServMsg_GetRoleInfoAck)
        HANDLE_MSG(PROTO_CS_ROLE_EXTRA_INFO_NTF, HandleCenterServMsg_RoleExtraInfoNtf)
        HANDLE_MSG(PROTO_CS_GET_GUILDS_ACK, HandleCenterServMsg_GetGuildsAck)
        HANDLE_MSG(PROTO_CS_GET_GUILD_MEMBERS_ACK, HandleCenterServMsg_GetGuildMembersAck)
        HANDLE_MSG(PROTO_CS_GET_GUILD_APPLICANTS_ACK, HandleCenterServMsg_GetGuildApplicantsAck)
        HANDLE_MSG(PROTO_CS_GET_TRADE_BUY_DELEGATE_ACK, HandleCenterServMsg_GetTradeBuyDelegateAck)
        HANDLE_MSG(PROTO_CS_GET_TRADE_SELL_DELEGATE_ACK, HandleCenterServMsg_GetTradeSellDelegateAck)
        HANDLE_MSG(PROTO_CS_GET_TRADE_RECORDS_ACK, HandleCenterServMsg_GetTradeRecordsAck)
        HANDLE_MSG(PROTO_CS_DELEGATE_CANCEL_ACK, HandleCenterServMsg_DelegateCancelAck)
        HANDLE_MSG(PROTO_CS_DELEGATE_BUY_ACK, HandleCenterServMsg_DelegateBuyAck)
        HANDLE_MSG(PROTO_CS_DELEGATE_SELL_ACK, HandleCenterServMsg_DelegateSellAck)
        HANDLE_MSG(PROTO_CS_GET_MAIL_ATTACHMENT_ACK, HandleCenterServMsg_GetMailAttachmentAck)
        HANDLE_MSG(PROTO_CS_GET_CONSTANT_CFG_ACK, HandleCenterServMsg_GetConstantCfgAck)
    END_MSG_HANDLER()
}

void SessionCS2DB::HandleCenterServMsg_HeartBeatAck(void* pData)
{
	// do nothing
}

void SessionCS2DB::HandleCenterServMsg_GetRoleDataAck(void* pData)
{
	auto ack = (ProtoCS_GetRoleDataAck*)pData;
	auto user = UserMgr::GetInstance()->FindUser(ack->token);
	if (nullptr != user) {
		user->OnGetRoleDataAck(ack->roleid);
	}
}

void SessionCS2DB::HandleCenterServMsg_GetItemAck(void* pData)
{
	ProtoCS_GetItemAck* getitemAck = (ProtoCS_GetItemAck*)pData;
	auto user = UserMgr::GetInstance()->FindUser(getitemAck->token);
	if (nullptr == user) {
		LOG_ERROR("user is NULL. roleid: %" PRIu64, getitemAck->role_id);
		return;
	}
	user->OnGetRoleItemAck(getitemAck->role_id, getitemAck->item_info, getitemAck->item_num);
}

void SessionCS2DB::HandleCenterServMsg_GetRoleInfoAck(void* pData)
{
	ProtoCS_GetRoleInfoAck* getRoleInfoAck = (ProtoCS_GetRoleInfoAck*)pData;

	auto user = UserMgr::GetInstance()->FindUser(getRoleInfoAck->token);
	if (nullptr == user) {
		LOG_ERROR("user is NULL. roleid: %" PRIu64, getRoleInfoAck->role_id);
		return;
	}

	user->HandleMapServMsg_SendRoleInfoAck(getRoleInfoAck);

}

void SessionCS2DB::HandleCenterServMsg_RoleExtraInfoNtf(void *pData)
{
    auto pRoleExtraInfoNtf = (ProtoCS_RoleExtraInfoNtf *)pData;

    auto pUser = UserMgr::GetInstance()->FindUser(pRoleExtraInfoNtf->token);
    if (!pUser) {
        LOG_ERROR("pUser is NULL. token: %u", pRoleExtraInfoNtf->token);
        return;
    }

    pUser->SetRoleExtraInfo(pRoleExtraInfoNtf->roleid, pRoleExtraInfoNtf->roleExtraInfo);
    pUser->SetRoleSettings(pRoleExtraInfoNtf->roleid, pRoleExtraInfoNtf->roleSettings);
}

void SessionCS2DB::HandleCenterServMsg_GetGuildsAck(void *pData)
{
    auto *msg = static_cast<Proto_General *>(pData);

    auto *guilds = static_cast<GUILD_MAP *>(msg->data);

    GuildData::GetInstance()->SetGuilds(*guilds);
    GuildData::GetInstance()->SetHasGuilds(true);

    ProtoCS_GetGuildsAck data;
    data.guilds = std::move(*guilds);

    SendDataBySessionType(SESSION_TYPE_CS2MS, data);

    delete guilds;
}

void SessionCS2DB::HandleCenterServMsg_GetGuildMembersAck(void *pData)
{
    auto *msg = static_cast<Proto_General *>(pData);

    auto *members = static_cast<GUILD_MEMBER_MAP *>(msg->data);

    GuildData::GetInstance()->SetMembers(*members);
    GuildData::GetInstance()->SetHasMembers(true);

    ProtoCS_GetGuildMembersAck data;
    data.members = std::move(*members);

    SendDataBySessionType(SESSION_TYPE_CS2MS, data);

    delete members;
}

void SessionCS2DB::HandleCenterServMsg_GetGuildApplicantsAck(void *pData)
{
    auto *msg = static_cast<Proto_General *>(pData);

    auto *applicants = static_cast<GUILD_APPLICANT_LIST *>(msg->data);

    GuildData::GetInstance()->SetApplicants(*applicants);
    GuildData::GetInstance()->SetHasApplicants(true);

    ProtoCS_GetGuildApplicantsAck data;
    data.applicants = std::move(*applicants);

    SendDataBySessionType(SESSION_TYPE_CS2MS, data);

    delete applicants;
}

void SessionCS2DB::HandleCenterServMsg_GetConstantCfgAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_GetConstantCfgAck*>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);
    // 相同key用ms的
    CONSTANT_CFG_MAP& constantCfgMap = ConfigInfo::GetInstance()->m_constantCfgMap;
    CONSTANT_CFG_MAP m;
    msg->custom >> m;
    for (auto& ele : constantCfgMap)
    {
        m[ele.first] = std::move(ele.second);
    }
    constantCfgMap = std::move(m);
    ConfigInfo::GetInstance()->m_beInited = true;
}

void SessionCS2DB::HandleCenterServMsg_GetTradeBuyDelegateAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_GetTradeBuyDelegateAck*>(pData);
    TradeData::GetInstance()->HandleGetTradeBuyDelegateAck(*msg);

    SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);
}

void SessionCS2DB::HandleCenterServMsg_GetTradeSellDelegateAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_GetTradeSellDelegateAck*>(pData);
    TradeData::GetInstance()->HandleGetTradeSellDelegateAck(*msg);

    SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);
}

void SessionCS2DB::HandleCenterServMsg_GetTradeRecordsAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_GetTradeRecordsAck*>(pData);
    TradeData::GetInstance()->HandleGetTradeRecordsAck(*msg);

    SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);
}

void SessionCS2DB::HandleCenterServMsg_DelegateCancelAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_DelegateCancelAck*>(pData);
    TradeData::GetInstance()->HandleDelegateCancelAck(*msg);
    SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);
}

void SessionCS2DB::HandleCenterServMsg_DelegateBuyAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_DelegateBuyAck*>(pData);
    TradeData::GetInstance()->HandleDelegateBuyAck(*msg);
    SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);
}

void SessionCS2DB::HandleCenterServMsg_DelegateSellAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_DelegateSellAck*>(pData);
    TradeData::GetInstance()->HandleDelegateSellAck(*msg);
    SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);
}

void SessionCS2DB::HandleCenterServMsg_GetMailAttachmentAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_GetMailAttachmentAck*>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);
    if (!msg->err_type)
    {
        auto user = (*UserMgr::GetInstance())[msg->item.base_info.role];
        if (nullptr == user)
        {
            LOG_ERROR("user is NULL. roleid: %" PRIu64, msg->item.base_info.role);
            return;
        }
        // site可能会重复,等ms来同步site
        memset(&msg->item.custom, 0, sizeof(msg->item.custom));
        user->OnGetRoleItemAck(msg->item.base_info.role, &msg->item, 1);
    }
}

void SessionCS2DB::HandleCenterServMsg_AuctionHouseAck(void* pData)
{
    auto* msg = static_cast<ProtoMS_SynAuctionItemInfo*>(pData);

    AuctionHouseMgr::GetInstance()->SyncAuctionItemInfoFromDB(*msg);

    SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);
}

void SessionCS2DB::HandleCenterServMsg_GetMallLimitInfoAck(void* pData)
{
    auto* msg = static_cast<ProtoMS_MallLimitInfoUpdate*>(pData);

    GameMallMgr::GetInstance()->GetMallLimitInfoAck(*msg);
    // 数据库没有数据时 初始化allmap
    if (msg->limit_type == mall_limit_type_all && !msg->num)
    {
        GameMallMgr::GetInstance()->InitMallAllMapToDB();
    }
    // 仅有全局的表在服务器初始化时同步给MS
    if (msg->limit_type == mall_limit_type_all && msg->num)
    {
        SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);
    }
}

void SessionCS2DB::HandleGateServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_GS_GET_ROLE_LIST_ACK, HandleGateServMsg_GetRoleListAck)
        HANDLE_MSG(PROTO_GS_CREATE_ROLE_ACK, HandleGateServMsg_CreateRoleAck)
        HANDLE_MSG(PROTO_GS_DELETE_ROLE_ACK, HandleGateServMsg_DeleteRoleAck)
        HANDLE_MSG(PROTO_GS_RESTORE_ROLE_ACK, HandleGateServMsg_RestoreRoleAck)
        HANDLE_MSG(PROTO_GS_ITEM_TIP_NTF, HandleGateServMsg_ItemTipNtf)

    END_MSG_HANDLER()
}

void SessionCS2DB::HandleGateServMsg_GetRoleListAck(void* pData)
{
	auto ack = (ProtoGS_GetRoleListAck*)pData;

	auto user = UserMgr::GetInstance()->FindUser(ack->playerid);
	if (nullptr == user) {
		LOG_ERROR("user is NULL. playerid: %" PRIu64, ack->playerid);
		return;
	}

	if (ERR_OK == ack->errcode && user->GetToken() == ack->token) {
		user->SetLastSelectRole(ack->last_role);
		//user->ClearRoleDataMap();
        //user->ClearDeleteRoleDataMap();
		for (int i = 0; i < ack->rolenum; ++i) {
			user->AddRoleDataInfo(ack->rolelist[i]);
		}
	}
    auto& map = ConfigInfo::GetInstance()->m_constantCfgMap;
    uint8_t res = 0;
    auto iter = map.find(CONSTANT_CREATE_ROLE_NEED_CODE);
    if (iter != map.end())
    {
        res = atoi(iter->second.value.c_str());
    }
    ack->needCode = res;
	SendDataBySessionID(user->GetCS2GSSessionID(), *ack);
}

void SessionCS2DB::HandleGateServMsg_CreateRoleAck(void* pData)
{
	auto ack = (ProtoGS_CreateRoleAck*)pData;
	auto user = UserMgr::GetInstance()->FindUser(ack->playerid);
	if (nullptr == user) {
		LOG_ERROR("user is NULL. playerid: %" PRIu64, ack->playerid);
		return;
	}

    if (ERR_OK != ack->errcode){
        LOG_ERROR("CreateRoleReq failed name %s, error %d!", ack->newrole.name, ack->errcode);
    }
    else{
        user->AddRoleDataInfo(ack->newrole);
        // 同步信息至后台
        PLATFORM_CREATE_ROLE_INFO info;
        if (CreateRoleInfoMgr::GeneratePlatformCreateRoleInfo(ack->newrole.guid, ack->playerid, user->GetChannel(), info)) {
            CreateRoleInfoMgr::SendToPlatform(info);
        }
    }
	SendDataBySessionID(user->GetCS2GSSessionID(), *ack);
}

void SessionCS2DB::HandleGateServMsg_DeleteRoleAck(void* pData)
{
	auto ack = (ProtoGS_DeleteRoleAck*)pData;
	auto user = UserMgr::GetInstance()->FindUser(ack->playerid);
	if (nullptr == user) {
		LOG_ERROR("user is NULL. playerid: %" PRIu64, ack->playerid);
		return;
	}

	SendDataBySessionID(user->GetCS2GSSessionID(), *ack);

    if (ack->errcode == 0) {
        user->RemoveRoleDataInfo(ack->roleid, ack->status);
        SendDataBySessionType(SESSION_TYPE_CS2MS, *ack);
    }
}

void SessionCS2DB::HandleGateServMsg_RestoreRoleAck(void* pData)
{
    auto ack = (ProtoGS_RestoreRoleAck*)pData;
    auto user = UserMgr::GetInstance()->FindUser(ack->playerid);
    if (nullptr == user) {
        LOG_ERROR("user is NULL. playerid: %" PRIu64, ack->playerid);
        return;
    }

    user->AddRoleDataInfo(ack->role);
    SendDataBySessionID(user->GetCS2GSSessionID(), *ack);
}

void SessionCS2DB::HandleGateServMsg_ItemTipNtf(void* pData)
{
    auto ack = (ProtoGS_ItemTipNtf*)pData;
    SendDataBySessionType(SESSION_TYPE_CS2MS, *ack);
}

void SessionCS2DB::HandleMapServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_MS_GET_SKILL_ACK, HandleMapServMsg_GetSkillAck)
        HANDLE_MSG(PROTO_MS_GET_BUFF_ACK, HandleMapServMsg_GetBuffAck)
        HANDLE_MSG(PROTO_MS_DELETE_MAIL_ACK, HandleMapServMsg_DelMailAck)
        HANDLE_MSG(PROTO_MS_AUCTION_ADD_ITEM_INFO, HandleCenterServMsg_AuctionHouseAck)
        HANDLE_MSG(PROTO_MS_MALL_LIMIT_INFO_UPDATE, HandleCenterServMsg_GetMallLimitInfoAck)
        HANDLE_MSG(PROTO_MS_GET_WANTED_LIST_ACK, HandleMapServMsg_GetWantedListAck)
        HANDLE_MSG(PROTO_MS_POST_BOUNTY_ACK, HandleMapServMsg_PostBountyAck)
        HANDLE_MSG(PROTO_MS_CHECK_ROLE_EXISTENCE_ACK, HandleMapServMsg_CheckRoleExistenceAck)
        HANDLE_MSG(PROTO_MS_UPDATE_SUPPORT_PLAYER, HandleMapServMsg_UpdateSupportPlayer)
    END_MSG_HANDLER()
}

void SessionCS2DB::HandleMapServMsg_GetSkillAck(void* pData)
{
	auto pGetSkillAck = (ProtoMS_GetSkillAck*)pData;

	LOG_TRACE("player: %" PRIu64 ", role: %" PRIu64 ", skillNum: %u",
		pGetSkillAck->playerid, pGetSkillAck->roleid, pGetSkillAck->skillNum);

	auto pUser = UserMgr::GetInstance()->FindUser(pGetSkillAck->playerid);
	if (!pUser) {
		LOG_ERROR("pUser is NULL");
		return;
	}

	pUser->SetSkillList(pGetSkillAck->roleid, pGetSkillAck->skillInfo, pGetSkillAck->skillNum);
}

void SessionCS2DB::HandleMapServMsg_GetBuffAck(void* pData)
{
	auto pGetBuffAck = (ProtoMS_GetBuffAck*)pData;

	LOG_TRACE("role: %" PRIu64 ", buffNum: %u", pGetBuffAck->roleid, pGetBuffAck->buffNum);

	auto user = UserMgr::GetInstance()->FindUser(pGetBuffAck->playerid);
	if (nullptr == user) {
		LOG_ERROR("can't find user. playerid:%" PRIu64, pGetBuffAck->playerid);
		return;
	}

	user->SetBuffList(pGetBuffAck->roleid, pGetBuffAck->buffs, pGetBuffAck->buffNum, pGetBuffAck->beFirstPack, true);
}

void SessionCS2DB::HandleMapServMsg_DelMailAck(void* pData)
{
    auto msg = (ProtoMS_DeleteMailAck*)pData;
    SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);
}

void SessionCS2DB::HandleMapServMsg_GetWantedListAck(void *pData)
{
    const auto *msg = static_cast<ProtoMS_GetWantedListAck *>(pData);

    if (!msg->pwanted_list) {
        LOG_ERROR("pwanted_list is NULL");
        return;
    }

    SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);

    auto &wanted_list = *msg->pwanted_list;

    WantedList::GetInstance()->SetRecvFromDB(true);
    WantedList::GetInstance()->SetWantedList(std::move(wanted_list));

    delete msg->pwanted_list;
}

void SessionCS2DB::HandleMapServMsg_PostBountyAck(void *pData)
{
    const auto *msg = static_cast<ProtoMS_PostBountyAck *>(pData);

    SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);

    if (msg->result != 0) return;

    WantedList::GetInstance()->AddToWantedList(msg);
}

void SessionCS2DB::HandleMapServMsg_CheckRoleExistenceAck(void *pData)
{
    const auto *msg = static_cast<ProtoMS_CheckRoleExistenceAck *>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);
}

void SessionCS2DB::HandleMapServMsg_UpdateSupportPlayer(void* pData)
{
    auto* msg = static_cast<ProtoMS_UpdateSupportPlayer*>(pData);
    std::list<uint64_t> l;
    for (auto i = 0; i < msg->num; ++i)
    {
        auto user = UserMgr::GetInstance()->FindUser(msg->guid[i]);
        if (user)
        {
            user->UpdateSupport(msg->type);
            const auto& roles = user->GetRoleDataMap();
            for (auto& role : roles) l.push_back(role.first);
        }
    }

    msg->num = 0;
    for (auto& id : l)
    {
        msg->guid[msg->num++] = id;
        if (msg->num >= _countof(msg->guid))
        {
            SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);
            msg->num = 0;
        }
    }
    if (msg->num) SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);;
}

void SessionCS2DB::HandleDBServMsg(uint16_t protoid, void *pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_DB_QUEST_INFO, HandleDBServMsg_QuestInfo)
        HANDLE_MSG(PROTO_DB_PLAYER_CUST_VAR, HandleDBServMsg_PlayerCustVar)
        HANDLE_MSG(PROTO_DB_PLAYER_ITEM_CUST_VAR, HandleDBServMsg_PlayerItemCustVar)
        HANDLE_MSG(PROTO_DB_GET_CUST_VAR_ACK, HandleDBServMsg_GetCustVarAck)
        HANDLE_MSG(PROTO_DB_QUICK_BAR_SET_NTF, HandleDBServMsg_QuickBarSetNtf)
        HANDLE_MSG(PROTO_DB_DGN_BIND_INFO_NTF, HandleDBServMsg_DgnBindInfoNtf)
        HANDLE_MSG(PROTO_DB_TOPLIST_ACK, HandleDBServMsg_GetTopListAck)
        HANDLE_MSG(PROTO_DB_ADD_MAIL_ACK, HandleDBServMsg_AddMailAck)
        HANDLE_MSG(PROTO_DB_GET_MAIL_INFO_ACK, HandleDBServMsg_GetMailInfoAck)   
        HANDLE_MSG(PROTO_DB_ITEM_DYN_ATTR_NTF, HandleDBServMsg_ItemDynAttrNtf)
        HANDLE_MSG(PROTO_DB_ROLE_DYN_ATTR_NTF, HandleDBServMsg_RoleDynAttrNtf)
        HANDLE_MSG(PROTO_DB_GET_PROHIBIT_CHAT_INFO_ACK, HandleDBServMsg_GetProhibitChatAck)
        HANDLE_MSG(PROTO_DB_GOODS_NOT_ISSUED_RECORDS_NTF, HandleDBServMsg_GoodsNotIssuedRecordsNtf)
        HANDLE_MSG(PROTO_DB_REBATE_MONEY_NOT_USED_RECORD_NTF, HandleDBServMsg_RebateMoneyNotUsedRecordNtf)
        HANDLE_MSG(PROTO_DB_PLAYER_SET_NAME_ACK, HandleDBServMsg_PlayerSetNameAck)
        HANDLE_MSG(PROTO_DB_GET_TITLE_INFO_ACK, HandleDBServMsg_GetTitleInfoAck)
        HANDLE_MSG(PROTO_DB_DEL_LOCK_ROlE_ACK, HandleDBServMsg_DelLockRoleAck)
        HANDLE_MSG(PROTO_DB_GET_CUST_LIST_INFO_ACK, HandleDBServMsg_GetCustListInfoAck)
        HANDLE_MSG(PROTO_DB_GOODS_NOT_POST_RECORDS_NTF, HandleDBServMsg_GoodsNotPostRecordsNtf)



	END_MSG_HANDLER()
}

void SessionCS2DB::HandleDBServMsg_QuestInfo(void *pData)
{
    auto *pQuestInfo = static_cast<ProtoDB_QuestInfo *>(pData);

    auto pUser = UserMgr::GetInstance()->FindUser(pQuestInfo->token);
    if (!pUser) {
        LOG_ERROR("pUser is NULL. token: %u", pQuestInfo->token);
        return;
    }

    pUser->SetQuestInfo(pQuestInfo->roleid, pQuestInfo->quest_info);
    pUser->SetQuestAchieves(pQuestInfo->roleid, pQuestInfo->achev_data, pQuestInfo->achev_data_num);
}

void SessionCS2DB::HandleDBServMsg_PlayerCustVar(void *pData)
{
    auto *msg = static_cast<ProtoDB_PlayerCustVar *>(pData);

    std::unique_ptr<CUST_VAR_MAP> vars(msg->vars);

    auto *user = UserMgr::GetInstance()->FindUser(msg->playerid);
    if (!user) {
        LOG_ERROR("user is NULL. playerid: %" PRIu64, msg->playerid);
        return;
    }

    if (user->GetToken() != msg->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    user->SetCustVars(msg->roleid, std::move(*vars));
}

void SessionCS2DB::HandleDBServMsg_PlayerItemCustVar(void *pData)
{
    auto *msg = static_cast<ProtoDB_PlayerItemCustVar *>(pData);

    std::unique_ptr<CUST_VAR_SP_LIST> vars(msg->vars);

    auto *user = UserMgr::GetInstance()->FindUser(msg->playerid);
    if (!user) {
        LOG_ERROR("user is NULL. playerid: %" PRIu64, msg->playerid);
        return;
    }

    if (user->GetToken() != msg->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    user->SetItemCustVars(msg->roleid, std::move(*vars));
}

void SessionCS2DB::HandleDBServMsg_GetCustVarAck(void *pData)
{
    auto *msg = static_cast<ProtoDB_GetCustVarAck *>(pData);

    std::unique_ptr<CUST_VAR_SP_LIST> vars(msg->vars);

    auto *inst = CustVarData::GetInstance();
    if (!inst) return;

    inst->SetCustVars(std::move(*vars));
    inst->SetHasData(true);

    ProtoDB_GetCustVarAck data;
    data.vars = &inst->GetCustVars();

    SendDataBySessionType(SESSION_TYPE_CS2MS, data);
}

void SessionCS2DB::HandleDBServMsg_QuickBarSetNtf(void* pData)
{
    auto* msg = static_cast<ProtoDB_QuickBarSetNtf*>(pData);
    auto* user = UserMgr::GetInstance()->FindUser(msg->userid);
    if (!user) {
        LOG_ERROR("user is NULL. playerid: %" PRIu64, msg->userid);
        return;
    }
    user->SetQuickBarSetNtf(msg);
}

void SessionCS2DB::HandleDBServMsg_DgnBindInfoNtf(void* pData)
{
    auto* msg = static_cast<ProtoDB_DgnBindInfoNtf*>(pData);
    auto* user = UserMgr::GetInstance()->FindUser(msg->userid);
    if (!user) {
        LOG_ERROR("user is NULL. playerid: %" PRIu64, msg->userid);
        return;
    }
    // CS
    user->SetDgnBindInfoNtf(msg);
}

void SessionCS2DB::HandleDBServMsg_GetTopListAck(void* pData)
{
    auto ack = (ProtoDB_GetTopListAck*)pData;
    auto topList = TopList::GetInstance();
    if (!topList) {
        LOG_ERROR("topList is NULL.");
        return;
    }
    topList->AddTopList(ack->type, ack->rolelist, ack->TopList,ack->TopListNum);
    topList->SetHas(true);
}

void SessionCS2DB::HandleDBServMsg_AddMailAck(void* pData)
{
    auto data = (ProtoDB_AddMailAck*)pData;
    if (data->err_type) return; 
    mail::GetInstance()->AddMail(data->num, data->infos);

    ProtoDB_AddMailAck info;
    auto& usermap = UserMgr::GetInstance()->GetUserMap();
    for (int i = 0; i < data->num; ++i)
    {
        uint64_t playerguid = data->infos[i].playerguid;
        auto it = find_if(usermap.begin(), usermap.end(), [playerguid](const pair<uint64_t, User*> &iter) {
            if (iter.second)
            {
                auto& roledatamap = iter.second->GetRoleDataMap();
                if (roledatamap.empty())return false;
                if (roledatamap.find(playerguid) != roledatamap.end())return true;
                return false;
            }
            return false;
            });
        if (it != usermap.end())
        {
            if (it->second && (it->second->GetOnlineState() == online_state_logged_in))
            {
                info.infos[info.num] = std::move(data->infos[i]);
                ++info.num;
            }
        }
    }
    SendDataBySessionType(SESSION_TYPE_CS2MS, info);
}

void SessionCS2DB::HandleDBServMsg_GetMailInfoAck(void* pData)
{
    auto data = (ProtoDB_GetMailInfoAck*)pData;
    mail::GetInstance()->AddMail(data->num, data->infos);
    SendDataBySessionType(SESSION_TYPE_CS2MS, *data);
}

void SessionCS2DB::HandleDBServMsg_ItemDynAttrNtf(void *pData)
{
    const auto *msg = static_cast<ProtoDB_ItemDynAttrNtf *>(pData);

    std::unique_ptr<ITEM_DYN_ATTRS_LIST> attrsList(msg->item_dyn_attrs_list);

    auto *user = UserMgr::GetInstance()->FindUser(msg->playerid);
    if (!user) {
        LOG_ERROR("user is NULL. playerid: %" PRIu64, msg->playerid);
        return;
    }

    if (user->GetToken() != msg->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    user->SetItemDynAttrsList(msg->roleid, std::move(*attrsList), true);
}

void SessionCS2DB::HandleDBServMsg_RoleDynAttrNtf(void* pData)
{
    const auto* msg = static_cast<ProtoDB_RoleDynAttrNtf*>(pData);

    std::unique_ptr<ROLE_DYN_ATTRS_LIST> attrsList(msg->role_dyn_attrs_list);

    auto* user = UserMgr::GetInstance()->FindUser(msg->playerid);
    if (!user) {
        LOG_ERROR("user is NULL. playerid: %" PRIu64, msg->playerid);
        return;
    }

    if (user->GetToken() != msg->token) {
        LOG_ERROR("Token does not match");
        return;
    }

    user->SetRoleDynAttrsList(msg->roleid, std::move(*attrsList));
}

void SessionCS2DB::HandleDBServMsg_GetProhibitChatAck(void* pData)
{
    const auto* msg = static_cast<ProtoDB_GetProhibitChatInfoAck*>(pData);
    SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);
}

void SessionCS2DB::HandleDBServMsg_GoodsNotIssuedRecordsNtf(void *pData)
{
    const auto *msg = static_cast<ProtoDB_GoodsNotIssuedRecordsNtf *>(pData);
    auto *user = UserMgr::GetInstance()->FindUser(msg->player_guid);
    if (!user) {
        LOG_ERROR("user is NULL. player_guid: %llu", msg->player_guid);
        return;
    }
    user->SetGoodsNotIssuedRecords(msg->role_guid, msg->records, msg->num);
}

void SessionCS2DB::HandleDBServMsg_RebateMoneyNotUsedRecordNtf(void* pData)
{
    const auto* msg = static_cast<ProtoDB_RebateMoneyNotUsedRecordNtf*>(pData);
    auto* user = UserMgr::GetInstance()->FindUser(msg->record.account_id);
    if (!user) {
        LOG_ERROR("user is NULL. player_guid: %llu", msg->record.account_id);
        return;
    }
    user->SetRebateMoneyNotUsedRecord(msg->record);
}

void SessionCS2DB::HandleDBServMsg_PlayerSetNameAck(void* pData)
{
    const auto* msg = static_cast<ProtoDB_PlayerSetNameAck*>(pData);
    if (msg->errcode == ERR_OK)
    {
        auto* user = UserMgr::GetInstance()->FindUser(msg->userid);
        if (user) {
            user->ChangePlayerNameInfo(msg->guid, msg->name, msg->orgName);
        }
    }

    SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);
}

void SessionCS2DB::HandleDBServMsg_GetTitleInfoAck(void* pData)
{
    const auto* msg = static_cast<ProtoDB_GetTitleInfoAck*>(pData);
    auto* user = UserMgr::GetInstance()->FindUser(msg->playerguid);
    if (!user) {
        LOG_ERROR("user is NULL. player_guid: %llu", msg->playerguid);
        return;
    }
    Title::GetInstance()->SyncPlayerTitleInfo(msg->guid, msg->num, msg->info);
}

void SessionCS2DB::HandleDBServMsg_DelLockRoleAck(void* pData)
{
    const auto* msg = static_cast<ProtoDB_DelLockRoleAck*>(pData);
    for (int i = 0; i < msg->num; ++i) {
        auto* user = UserMgr::GetInstance()->FindUser(msg->userID[i]);
        if (nullptr == user)continue;
        auto &roleDataMap = user->GetRoleDataMap();
        auto iter = roleDataMap.find(msg->guid[i]);
        if (iter == roleDataMap.end())continue;
        iter->second.GetBriefInfo().is_lock = 0;
    }

}

void SessionCS2DB::HandleDBServMsg_GetCustListInfoAck(void* pData)
{
    const auto* msg = static_cast<ProtoDB_GetCustListInfoAck*>(pData);
    CustListInfoMgr::GetInstance()->GetCustInfoFromDB(msg->num, msg->data);
    SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);
}

void SessionCS2DB::HandleDBServMsg_GoodsNotPostRecordsNtf(void* pData)
{
    const auto* msg = static_cast<ProtoDB_GoodsNotPostRecordsNtf*>(pData);
    auto* user = UserMgr::GetInstance()->FindUser(msg->player_guid);
    if (!user) {
        LOG_ERROR("user is NULL. player_guid: %llu", msg->player_guid);
        return;
    }
    user->SetGoodsNotPostRecords(msg->role_guid, msg->records, msg->num);
}
