#include "stdafx.h"
#include "SessionMS2CS.h"
#include "ILogHelper.h"
#include "CNetManager.h"
#include "SessionFactory.h"
#include "MapRoleMgr.h"
#include "MapMgr.h"
#include <vector>
#include "map_table.hpp"

#include "MailMgr.h"
#include "TradeMgr.h"
#include "GuildMgr.h"
#include "CustVarMgr.h"
#include "CastleWarMgr.h"
#include "Auction.h"
#include "GameMall.h"
#include "ProhibitChatMgr.h"
#include "WantedList.h"
#include "RoleInfoCache.h"
#include "CustList.h"

#include "ProtoMS.h"
#include "ProtoCS.h"
#include "ProtoGS.h"
#include "ProtoDB.h"

SessionMS2CS::SessionMS2CS()
{

}

SessionMS2CS::~SessionMS2CS()
{

}

void SessionMS2CS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("SessionCS2MS MS OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());	

    SendGetCustVarReqToCS();

    SendGetGuildsReqToCS();
    SendGetGuildMembersReqToCS();
    SendGetGuildApplicantsReqToCS();
    SendGetTradeDelegateReqToCS();
    SendGetAuctionHouseReqRoCS();
    SendGetConstantCfgReqToCS();
    SendGetMallLimitInfoReqToCS();
    SendGetProhibitChatInfoReqToCS();
    //SendGetWantedListReqToCS();
    SendGetCustListReqToCS();
}

void SessionMS2CS::SendGetCustVarReqToCS()
{
    ProtoMS_GetCustVarReq data;
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void SessionMS2CS::SendGetGuildsReqToCS()
{
    ProtoMS_GetGuildsReq data;
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void SessionMS2CS::SendGetGuildMembersReqToCS()
{
    ProtoMS_GetGuildMembersReq data;
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void SessionMS2CS::SendGetGuildApplicantsReqToCS()
{
    ProtoMS_GetGuildApplicantsReq data;
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void SessionMS2CS::SendGetTradeDelegateReqToCS()
{
    ProtoMS_GetTradeDelegateReq data;
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);

    ProtoMS_GetTradeRecordsReq data1;
    data1.tradeRecordsExpireTime = 2592000;

    auto global = sGlobalConfig.GetData();
    if (global && global->TradeRecordsExpireTime)
        data1.tradeRecordsExpireTime = global->TradeRecordsExpireTime;

    SendDataBySessionType(SESSION_TYPE_MS2CS, data1);
}

void SessionMS2CS::SendGetAuctionHouseReqRoCS()
{
    ProtoMS_GetAuctionHouseReq data;
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void SessionMS2CS::SendGetConstantCfgReqToCS()
{
    ProtoMS_GetConstantCfgReq data;
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void SessionMS2CS::SendGetMallLimitInfoReqToCS()
{
    ProtoMS_MallLimitInfoReq data;
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void SessionMS2CS::SendGetProhibitChatInfoReqToCS()
{
    ProtoMS_GetProhibitChatInfoReq data;
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void SessionMS2CS::SendGetWantedListReqToCS()
{
    ProtoMS_GetWantedListReq data;
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void SessionMS2CS::SendGetCustListReqToCS()
{
    ProtoMS_GetCustListReq data;
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void SessionMS2CS::OnLost()
{
	Session::OnLost();
	LOG_NORMAL("OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionMS2CS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    MsgCostStat::GetInstance()->BeginHandleMsg();

    OnHeartBeat();

    switch (moduleid) {
        case MODULE_TYPE_GS:
            HandleGateServMsg(protoid, _pData);
            break;

		case MODULE_TYPE_CS://cs->ms
			HandleCSMessage(protoid, _pData);
			break;

        case MODULE_TYPE_MS:
            HandleMapServMsg(protoid, _pData);
            break;

        case MODULE_TYPE_DB:
            HandleDBServMsg(protoid, _pData);
            break;
	
		default:
			LOG_WARN("Unhandled moduleid: %d", moduleid);
			break;
	}

    MsgCostStat::GetInstance()->EndHandleMsg(moduleid, protoid);
}

void SessionMS2CS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionMS2CS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionMS2CS::DoHeartBeat()
{
    ProtoMS_HeartBeatReq req;
    SendPkg(&req, sizeof(req));
}

void SessionMS2CS::HandleCSMessage(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_CS_ENTER_MS_REQ, HandleCSEnterMSReq)
        HANDLE_MSG(PROTO_CS_ENTER_MS_NTF, HandleCSEnterMSNtf)
        HANDLE_MSG(PROTO_CS_SEND_ITEM_NTF, HandleCSSendItemNtf)
        HANDLE_MSG(PROTO_CS_GET_GUILDS_ACK, HandleCenterServMsg_GetGuildsAck)
        HANDLE_MSG(PROTO_CS_GET_GUILD_MEMBERS_ACK, HandleCenterServMsg_GetGuildMembersAck)
        HANDLE_MSG(PROTO_CS_GET_GUILD_APPLICANTS_ACK, HandleCenterServMsg_GetGuildApplicantsAck)
        HANDLE_MSG(PROTO_CS_QUICK_BAR_SET_NTF, HandleCenterServMsg_QuickBarSetNtf)
        HANDLE_MSG(PROTO_CS_GLOBAL_NTF, HandleCenterServMsg_GlobalNtf);
    HANDLE_MSG(PROTO_CS_DGN_BIND_INFO_NTF, HandleCenterServMsg_DgnBindInfoNtf)
        HANDLE_MSG(PROTO_CS_GM_MOD_LEVEL, HandleCenterServMsg_SyncGMModLevel)
        HANDLE_MSG(PROTO_CS_GET_TRADE_BUY_DELEGATE_ACK, HandleCenterServMsg_GetTradeBuyDelegateAck)
        HANDLE_MSG(PROTO_CS_GET_TRADE_SELL_DELEGATE_ACK, HandleCenterServMsg_GetTradeSellDelegateAck)
        HANDLE_MSG(PROTO_CS_GET_TRADE_RECORDS_ACK, HandleCenterServMsg_GetTradeRecordsAck)
        HANDLE_MSG(PROTO_CS_RECORDS_CANCEL_ACK, HandleCenterServMsg_RecordsCancelAck)
        HANDLE_MSG(PROTO_CS_DELEGATE_CANCEL_ACK, HandleCenterServMsg_DelegateCancelAck)
        HANDLE_MSG(PROTO_CS_DELEGATE_BUY_ACK, HandleCenterServMsg_DelegateBuyAck)
        HANDLE_MSG(PROTO_CS_DELEGATE_SELL_ACK, HandleCenterServMsg_DelegateSellAck)
        HANDLE_MSG(PROTO_CS_MARKET_SELL_ACK, HandleCenterServMsg_MarketSellAck)
        HANDLE_MSG(PROTO_CS_MARKET_BUY_ACK, HandleCenterServMsg_MarketBuyAck)
        HANDLE_MSG(PROTO_CS_GET_MAIL_ATTACHMENT_ACK, HandleCenterServMsg_GetMailAttachmentAck)
        HANDLE_MSG(PROTO_CS_AUCTION_GET_FINISHED_INFO_ACK, HandleCenterServMsg_GetAuctionGetFinishedInfoReq)
        HANDLE_MSG(PROTO_CS_RUN_GM_CMD_ACK, HandleCenterServMsg_HandleRunGMCmdAck)
        HANDLE_MSG(PROTO_CS_GET_CONSTANT_CFG_ACK, HandleCenterServMsg_GetConstantCfgAck)
        HANDLE_MSG(PROTO_CS_GET_MALL_LIMIT_INFO_SINGLE_ACK, HandleCenterServMsg_GetMallLimitInfoSingleFromCS);
        HANDLE_MSG(PROTO_CS_MALL_LIST_UPDATE, HandleCenterServMsg_UpdateMallList);
        HANDLE_MSG(PROTO_CS_ACTIVATION_CODE_ACK, HandleCenterServMsg_ActivationCodeAck);
        HANDLE_MSG(PROTO_CS_CUSTOM_HTTP_ACK, HandleMapServMsg_CustomHttpAck)

    END_MSG_HANDLER()
}

void SessionMS2CS::HandleGateServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_GS_LOGOUT_REQ, HandleGateServMsg_LogoutReq)
        HANDLE_MSG(PROTO_GS_UPDATE_ONLINE_STATE, HandleGateServMsg_UpdateOnlineState)
        HANDLE_MSG(PROTO_GS_DELETE_ROLE_ACK, HandleGateServMsg_DeleteRoleAck)
        HANDLE_MSG(PROTO_GS_ITEM_TIP_NTF, HandleGateServMsg_ItemTipNtf)

    END_MSG_HANDLER()
}

void SessionMS2CS::HandleGateServMsg_LogoutReq(void* pData)
{
    auto pLogoutReq = (ProtoGS_LogoutReq*)pData;
    auto player = MapRoleMgr::GetInstance()->FindPlayerByToken(pLogoutReq->token);
    if (nullptr != player)
    {
        player->SetExitType(pLogoutReq->info);
        player->OnLogout();
    }
}

void SessionMS2CS::HandleGateServMsg_UpdateOnlineState(void *pData)
{
    const auto *msg = static_cast<ProtoGS_UpdateOnlineState *>(pData);

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->roleid);
    if (!player) return;
    player->SetOnlineState(msg->state);
}

void SessionMS2CS::HandleGateServMsg_DeleteRoleAck(void *pData)
{
    const auto *msg = static_cast<ProtoGS_DeleteRoleAck *>(pData);

    RoleInfoCache::GetInstance()->OnDeleteRole(msg->roleid);
}

void SessionMS2CS::HandleGateServMsg_ItemTipNtf(void* pData)
{
    auto* msg = static_cast<ProtoGS_ItemTipNtf*>(pData);
    auto player = MapRoleMgr::GetInstance()->FindPlayer(msg->guid);
    if (!player) {
        LOG_NORMAL("Get Item Tip Ntf player not online!");
    }
    msg->sessionid = player->GetClSessionID();
    SendDataBySessionID(player->GetGsSessionID() ,*msg);
}

void SessionMS2CS::HandleCSEnterMSReq(void* pData)
{
	ProtoCS_EnterMSReq* req = (ProtoCS_EnterMSReq*)pData;
    MapMgr::GetInstance()->OnRecv_EnterMSReq(*req);
}

void SessionMS2CS::HandleCSEnterMSNtf(void* pData)
{
    ProtoCS_EnterMSNtf* ntf = (ProtoCS_EnterMSNtf*)pData;
    SendGlobalNtfToClient(ntf->token);
    MapMgr::GetInstance()->OnRecv_EnterMSNtf(*ntf);
}

void SessionMS2CS::HandleCSSendItemNtf(void* _pData)
{
    auto ntf = (ProtoCS_SendItemNtf*)_pData;
    auto player = MapRoleMgr::GetInstance()->FindPlayerByToken(ntf->token);
    if (nullptr == player) {
        LOG_ERROR("can't find player");
        return;
    }
    player->OnRecvItemFromCS(*ntf);
}

void SessionMS2CS::HandleCenterServMsg_GetGuildsAck(void *pData)
{
    auto *msg = static_cast<Proto_General *>(pData);

    auto *guilds = static_cast<GUILD_MAP *>(msg->data);

    GuildMgr::GetInstance()->SetGuilds(std::move(*guilds));

    delete guilds;

    OnGuildsReady();
}

void SessionMS2CS::HandleCenterServMsg_GetGuildMembersAck(void *pData)
{
    auto *msg = static_cast<Proto_General *>(pData);

    auto *members = static_cast<GUILD_MEMBER_MAP *>(msg->data);

    GuildMgr::GetInstance()->SetMembers(std::move(*members));

    delete members;
}

void SessionMS2CS::HandleCenterServMsg_GetGuildApplicantsAck(void *pData)
{
    auto *msg = static_cast<Proto_General *>(pData);

    auto *applicants = static_cast<GUILD_APPLICANT_LIST *>(msg->data);

    GuildMgr::GetInstance()->SetApplicants(std::move(*applicants));

    delete applicants;
}

void SessionMS2CS::HandleCenterServMsg_GetConstantCfgAck(void* pData)
{
    // 相同key用ms的
    auto* msg = static_cast<ProtoCS_GetConstantCfgAck*>(pData);
    CONSTANT_CFG_MAP &constantCfgMap = ConfigInfo::GetInstance()->m_constantCfgMap;
    CONSTANT_CFG_MAP m;
    msg->custom >> m;
    for (auto& ele : constantCfgMap)
    {
        m[ele.first] = std::move(ele.second);
    }
    constantCfgMap = std::move(m);
    ConfigInfo::GetInstance()->m_beInited = true;
}

void SessionMS2CS::HandleCenterServMsg_GetMallLimitInfoSingleFromCS(void* pData)
{
    auto* msg = static_cast<ProtoCS_GetMallLimitInfoSingleAck*>(pData);
    GameMall::GetInstance()->GetMallSingleInfoFromCS(*msg);
}

void SessionMS2CS::HandleCenterServMsg_UpdateMallList(void* pData)
{
    auto* msg = static_cast<ProtoCS_MallListUpdate*>(pData);
    GameMall::GetInstance()->UpdateMallListWhenTimeRefresh(*msg);
}

void SessionMS2CS::HandleCenterServMsg_ActivationCodeAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_ActivationCodeAck*>(pData);

    LOG_TRACE("ActivationCodeAck, guid: %llu, err: %u, type: %u, gift_name: %s, gift_content: %s, err_desc: %s",
        msg->guid, msg->err, msg->type, msg->gift_name, msg->gift_content, msg->err_desc);

    auto player = MapRoleMgr::GetInstance()->FindPlayer(msg->guid);
    if (!player) {
        LOG_NORMAL("ActivationCode player not online!");
        return;
    }

    switch (msg->type) {
    case redemption_code_type_npc:
    case redemption_code_type_cdkey:
        TRIGGER_EVENT(trigger_player_redeem_code, player->GetGUIDAsString(), msg->err, msg->err_desc);
        break;
    case redemption_code_type_game:
        TRIGGER_EVENT(trigger_player_redeem_code2, player->GetGUIDAsString(), msg->err, msg->err_desc, msg->gift_name, msg->gift_content);
        break;
    default:
        LOG_NORMAL("Invalid ActivationCode Type!");
        break;
    }
}

void SessionMS2CS::HandleCenterServMsg_GetTradeBuyDelegateAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_GetTradeBuyDelegateAck*>(pData);
    TradeMgr::GetInstance()->HandleGetTradeBuyDelegateAck(*msg);
}

void SessionMS2CS::HandleCenterServMsg_GetTradeSellDelegateAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_GetTradeSellDelegateAck*>(pData);
    TradeMgr::GetInstance()->HandleGetTradeSellDelegateAck(*msg);
}

void SessionMS2CS::HandleCenterServMsg_GetTradeRecordsAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_GetTradeRecordsAck*>(pData);
    TradeMgr::GetInstance()->HandleGetTradeRecordsAck(*msg);
}

void SessionMS2CS::HandleCenterServMsg_DelegateCancelAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_DelegateCancelAck*>(pData);
    auto player = MapRoleMgr::GetInstance()->FindPlayer(msg->player_guid);
    TradeMgr::GetInstance()->HandleDelegateCancelAck(*msg, player);
}

void SessionMS2CS::HandleCenterServMsg_RecordsCancelAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_RecordsCancelAck*>(pData);
    TradeMgr::GetInstance()->HandleRecordsCancelAck(*msg);
}

void SessionMS2CS::HandleCenterServMsg_DelegateBuyAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_DelegateBuyAck*>(pData);
    auto player = MapRoleMgr::GetInstance()->FindPlayer(msg->buyItem.buyer_guid);
    TradeMgr::GetInstance()->HandleDelegateBuyAck(*msg, player);
}

void SessionMS2CS::HandleCenterServMsg_DelegateSellAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_DelegateSellAck*>(pData);
    auto player = MapRoleMgr::GetInstance()->FindPlayer(msg->sellItem.seller_guid);
    TradeMgr::GetInstance()->HandleDelegateSellAck(*msg, player);
}

void SessionMS2CS::HandleCenterServMsg_MarketSellAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_MarketSellAck*>(pData);
    auto player = MapRoleMgr::GetInstance()->FindPlayer(msg->seller_guid);
    TradeMgr::GetInstance()->HandleMarketSellAck(*msg, player);
}

void SessionMS2CS::HandleCenterServMsg_MarketBuyAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_MarketBuyAck*>(pData);
    auto player = MapRoleMgr::GetInstance()->FindPlayer(msg->buyer_guid);
    TradeMgr::GetInstance()->HandleMarketBuyAck(*msg, player);
}

void SessionMS2CS::HandleCenterServMsg_GetMailAttachmentAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_GetMailAttachmentAck*>(pData);
    if (!msg->err_type)
    {
        auto pPlayer = MapRoleMgr::GetInstance()->FindPlayer(msg->item.base_info.role);
        MailMgr::GetMailAttachmentAck(this, pPlayer, *msg);
    }
}

void SessionMS2CS::HandleCenterServMsg_GetAuctionGetFinishedInfoReq(void* pData)
{
    auto* msg = static_cast<ProtoCS_AuctionGetFinishedInfoAck*>(pData);
    CLuaObject luaRet = NewLuaObj();
    for (int i = 0; i < msg->num; ++i)
    {
        CLuaObject info = NewLuaObj();
        info[1] = std::to_string(msg->info[i].orderID);
        info[2] = (std::string)msg->info[i].item_name;
        info[3] = msg->info[i].item_num;
        info[4] = msg->info[i].item_price;
        info[5] = msg->info[i].currency_type;
        info[6] = std::to_string(msg->info[i].ownerID);
        info[7] = (std::string)msg->info[i].ownerName;
        info[8] = ITimeHelper::GetInstance()->ConvertTimeToString(msg->info[i].start_time, DTFMTA1);
        auto stamp = msg->info[i].start_time + msg->info[i].keep_time;
        info[9] = ITimeHelper::GetInstance()->ConvertTimeToString(stamp, DTFMTA1);
        info[10] = msg->info[i].status;
        luaRet[i + 1] = info;
    }
    LuaRet = luaRet;
    LuaBindCallVoid(std::string(msg->func));
}

void SessionMS2CS::HandleCenterServMsg_HandleRunGMCmdAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_RunGmCmdAck*>(pData);
    LOG_NORMAL("[GM] RunGmCmdAck result: %d, sn: %d, cmd: %s, param: %s",
        msg->result, msg->sn, msg->cmd, msg->param);

    auto player = MapRoleMgr::GetInstance()->FindPlayerByToken(msg->token);
    if (nullptr == player) {
        LOG_ERROR("[GM] can't find player");
        return;
    }

    player->RunGMCommand(pData);

}

void SessionMS2CS::HandleCenterServMsg_QuickBarSetNtf(void* pData)
{
    auto *msg = static_cast<ProtoCS_QuickBarSetNtf*>(pData);
    ProtoMS_QuickBarSetNtf ack;
    ack.num = msg->num;
    std::copy(msg->info, msg->info + msg->num, ack.info);
    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayerByToken(msg->token);
    if (nullptr == pPlayer)
    {
        LOG_ERROR("[%s:%d] can't find player", FUNC_LINE);
        return;
    }
    ack.sessid = pPlayer->GetClSessionID();
    SendDataBySessionID(pPlayer->GetGsSessionID(), ack);
    
}

void SessionMS2CS::HandleCenterServMsg_GlobalNtf(void* pData)
{
    auto msg = (ProtoCS_GlobalNtf*)(pData);
    ProtoMS_GlobalNtf ack;
    ack.int_count = msg->int_count;
    std::copy(msg->int_data, msg->int_data + msg->int_count, ack.int_data);
    ack.str_count = msg->str_count;
    std::copy(msg->str_data, msg->str_data + msg->str_count, ack.str_data);
    if (!msg->token && !msg->role_id)
    {
        const auto& playerMap = MapRoleMgr::GetInstance()->GetPlayerMap();
        auto it = playerMap.begin();
        for (; it != playerMap.end(); ++it)
        {
            if (!it->second) continue;
            ack.sessid = it->second->GetClSessionID();
            SendDataBySessionID(it->second->GetGsSessionID(), ack);
        }
    }
    else
    {
        auto pPlayer = MapRoleMgr::GetInstance()->FindPlayerByToken(msg->token);
        if (nullptr == pPlayer)
        {
            LOG_ERROR("[%s:%d] can't find player", FUNC_LINE);
            return;
        }
        ack.sessid = pPlayer->GetClSessionID();
        SendDataBySessionID(pPlayer->GetGsSessionID(), ack);
    }
}

void SessionMS2CS::HandleCenterServMsg_DgnBindInfoNtf(void* pData)
{
    auto* ntf = static_cast<ProtoCS_DgnBindInfoNtf*>(pData);

    auto player = MapRoleMgr::GetInstance()->FindPlayerByToken(ntf->token);
    if (nullptr == player) 
    {
        LOG_ERROR("[%s:%d] can't find player", FUNC_LINE);
        return;
    }
    player->OnRecvIDgnBindInfoFromCS(*ntf);
}

void SessionMS2CS::HandleCenterServMsg_SyncGMModLevel(void* pData)
{
    auto* ntf = (ProtoCS_GMModLevel*)pData;
    auto player = MapRoleMgr::GetInstance()->FindPlayer(ntf->role_id);
    if (nullptr == player) {
        LOG_ERROR("[%s:%d] can't find player", FUNC_LINE);
        return;
    }
    player->SetRoleProp(role_gm_level, ntf->GMModLevel);
}

void SessionMS2CS::HandleMapServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_MS_HEART_BEAT_ACK, HandleMapServMsg_HeartBeatAck)
        HANDLE_MSG(PROTO_MS_GET_SKILL_ACK, HandleMapServMsg_GetSkillAck)
        HANDLE_MSG(PROTO_MS_GET_BUFF_ACK, HandleMapServMsg_GetBuffAck)
        HANDLE_MSG(PROTO_MS_GET_ROLE_INFO_ACK, HandleMapServMsg_GetRoleInfoAck)
        HANDLE_MSG(PROTO_MS_DELETE_MAIL_ACK, HandleMapServMsg_DelMailAck)
        HANDLE_MSG(PROTO_MS_AUCTION_ADD_ITEM_INFO, HandleMapServMsg_GetAuctionHouseAck)
        HANDLE_MSG(PROTO_MS_MALL_LIMIT_INFO_UPDATE, HandleMapServMsg_GetMallLimitInfoAck)
        HANDLE_MSG(PROTO_MS_GET_WANTED_LIST_ACK, HandleMapServMsg_GetWantedListAck)
        HANDLE_MSG(PROTO_MS_POST_BOUNTY_ACK, HandleMapServMsg_PostBountyAck)
        HANDLE_MSG(PROTO_MS_CHECK_ROLE_EXISTENCE_ACK, HandleMapServMsg_CheckRoleExistenceAck)
        HANDLE_MSG(PROTO_MS_UPDATE_SUPPORT_PLAYER, HandleCenterServMsg_UpdateSupportPlayer);
    END_MSG_HANDLER()
}

void SessionMS2CS::HandleMapServMsg_HeartBeatAck(void* pData)
{
    // do nothing
}

void SessionMS2CS::HandleMapServMsg_GetSkillAck(void* pData)
{
    auto pGetSkillAck = (ProtoMS_GetSkillAck*)pData;

    LOG_TRACE("player: %" PRIu64 ", role: %" PRIu64 ", skillNum: %u",
        pGetSkillAck->playerid, pGetSkillAck->roleid, pGetSkillAck->skillNum);

    auto pPlayer = MapRoleMgr::GetInstance()->FindPlayer(pGetSkillAck->roleid);
    if (!pPlayer) {
        LOG_ERROR("pPlayer is NULL");
        return;
    }

    pPlayer->OnGetSkillAck(pGetSkillAck->skillInfo, pGetSkillAck->skillNum);
}

void SessionMS2CS::HandleMapServMsg_GetBuffAck(void* pData)
{
    auto pGetBuffAck = (ProtoMS_GetBuffAck*)pData;

    LOG_TRACE("role: %" PRIu64 ", buffNum: %u", pGetBuffAck->roleid, pGetBuffAck->buffNum);

    auto pRole = MapRoleMgr::GetInstance()->FindRole(pGetBuffAck->roleid);
    if (!pRole) {
        LOG_ERROR("pRole is NULL");
        return;
    }

    pRole->OnGetBuffAck(pGetBuffAck->buffs, pGetBuffAck->buffNum);
}

void SessionMS2CS::HandleMapServMsg_GetRoleInfoAck(void* pData)
{
    auto pGetRoleInfoAck = (ProtoMS_GetRoleInfoAck*)pData;

    auto pRole = MapRoleMgr::GetInstance()->FindRole(pGetRoleInfoAck->role_id);
    if (!pRole) {
        LOG_ERROR("pRole is NULL");
        return;
    }

    pRole->SetRoleInfo(pGetRoleInfoAck->base_info);
}

void SessionMS2CS::HandleMapServMsg_DelMailAck(void* pData)
{
    auto msg = (ProtoMS_DeleteMailAck*)pData;
    SendDataBySessionType(SESSION_TYPE_MS2GS, *msg, true);
}

void SessionMS2CS::HandleMapServMsg_GetAuctionHouseAck(void* pData)
{
    auto msg = (ProtoMS_SynAuctionItemInfo*)pData;
    AuctionHouse::GetInstance()->GetAuctionHouseFromCS(*msg);
}

void SessionMS2CS::HandleMapServMsg_GetMallLimitInfoAck(void* pData)
{
    auto msg = (ProtoMS_MallLimitInfoUpdate*)pData;
    GameMall::GetInstance()->GetMallInfoLimitFromCS(*msg);

}

void SessionMS2CS::HandleMapServMsg_GetWantedListAck(void *pData)
{
    const auto *msg = static_cast<ProtoMS_GetWantedListAck *>(pData);

    auto &wanted_list = *msg->pwanted_list;

    WantedList::GetInstance()->SetWantedList(std::move(wanted_list));

    delete msg->pwanted_list;
}

void SessionMS2CS::HandleMapServMsg_PostBountyAck(void *pData)
{
    const auto *msg = static_cast<ProtoMS_PostBountyAck *>(pData);

    if (msg->result == 0) {
        WantedList::GetInstance()->AddToWantedList(msg);
    }

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->wanted_by_guid);

    TRIGGER_EVENT(player, trigger_post_bounty_result, msg->result == 0 ? true : false,
        std::to_string(msg->wanted_by_guid), msg->wanted_by_name, std::to_string(msg->wanted_guid),
        msg->wanted_name, msg->bounty, msg->desc, std::to_string(msg->ptime));
}

void SessionMS2CS::HandleMapServMsg_CheckRoleExistenceAck(void *pData)
{
    const auto *msg = static_cast<ProtoMS_CheckRoleExistenceAck *>(pData);

    auto spRoleInfo = std::make_shared<RoleInfo>(msg->guid, msg->name, msg->exist);
    RoleInfoCache::GetInstance()->AddRoleInfo(std::move(spRoleInfo));

    auto query = RoleInfoPendingQueryMgr::GetInstance()->GetQuery(msg->seq);
    if (!query) return;

    LuaBindCallExVoid(query->callback, msg->name, std::to_string(msg->guid), !!msg->exist);     // !!תΪboolֵ
    RoleInfoPendingQueryMgr::GetInstance()->RemoveQuery(msg->seq);
}

void SessionMS2CS::HandleCenterServMsg_UpdateSupportPlayer(void* pData)
{
    auto* msg = static_cast<ProtoMS_UpdateSupportPlayer*>(pData);
    for (auto i = 0; i < msg->num; ++i)
    {
        uint16_t guid = 0;
        auto player = MapRoleMgr::GetInstance()->FindPlayer(msg->guid[i]);
        if (player) player->SetSupport(msg->type);
    }
}

void SessionMS2CS::SendGlobalNtfToClient(uint32_t token)
{
    auto GlobalCfg = sGlobalConfig.GetData();
    ProtoCS_GlobalNtf g_ack;
    g_ack.role_id = 0;
    g_ack.token = token;
    g_ack.int_count = 8;
    strcpy_s(g_ack.int_data[0].name, _countof(g_ack.int_data[0].name), "RemoteOpenWarehouse");
    g_ack.int_data[0].value = GlobalCfg->RemoteOpenWarehouse;
    strcpy_s(g_ack.int_data[1].name, _countof(g_ack.int_data[1].name), "SafeRegionCanThroughHuman");
    g_ack.int_data[1].value = GlobalCfg->SafeRegionCanThroughHuman;
    strcpy_s(g_ack.int_data[2].name, _countof(g_ack.int_data[2].name), "StallRegionCanThroughHuman");
    g_ack.int_data[2].value = GlobalCfg->StallRegionCanThroughHuman;
    strcpy_s(g_ack.int_data[3].name, _countof(g_ack.int_data[3].name), "SafeRegionCanThroughMonster");
    g_ack.int_data[3].value = GlobalCfg->SafeRegionCanThroughMonster;
    strcpy_s(g_ack.int_data[4].name, _countof(g_ack.int_data[4].name), "StallRegionCanThroughMonster");
    g_ack.int_data[4].value = GlobalCfg->StallRegionCanThroughMonster;
    strcpy_s(g_ack.int_data[5].name, _countof(g_ack.int_data[5].name), "MonsterBackRate");
    g_ack.int_data[5].value = GlobalCfg->MonsterBackRate;
    strcpy_s(g_ack.int_data[6].name, _countof(g_ack.int_data[6].name), "PKValueOfYellowName");
    g_ack.int_data[6].value = GlobalCfg->PKValueOfYellowName;    
    strcpy_s(g_ack.int_data[7].name, _countof(g_ack.int_data[7].name), "PKValueOfRedName");
    g_ack.int_data[7].value = GlobalCfg->PKValueOfRedName;

    HandleCenterServMsg_GlobalNtf(&g_ack);
}

void SessionMS2CS::HandleDBServMsg(uint16_t protoid, void *pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_DB_PLAYER_CUST_VAR, HandleDBServMsg_PlayerCustVar)
        HANDLE_MSG(PROTO_DB_PLAYER_ITEM_CUST_VAR, HandleDBServMsg_PlayerItemCustVar)
        HANDLE_MSG(PROTO_DB_GET_CUST_VAR_ACK, HandleDBServMsg_GetCustVarAck)
        HANDLE_MSG(PROTO_DB_ADD_MAIL_ACK, HandleDBServMsg_AddMailAck)
        HANDLE_MSG(PROTO_DB_GET_MAIL_INFO_ACK, HandleDBServMsg_GetMailInfoAck)
        HANDLE_MSG(PROTO_DB_ITEM_DYN_ATTR_NTF, HandleDBServMsg_ItemDynAttrNtf)
        HANDLE_MSG(PROTO_DB_ROLE_DYN_ATTR_NTF, HandleDBServMsg_RoleDynAttrNtf)
        HANDLE_MSG(PROTO_DB_GET_PROHIBIT_CHAT_INFO_ACK, HandleDBServMsg_GetProhibitInfoAck)
        HANDLE_MSG(PROTO_DB_GOODS_NOT_ISSUED_RECORDS_NTF, HandleDBServMsg_GoodsNotIssuedRecordsNtf)
        HANDLE_MSG(PROTO_DB_REBATE_MONEY_NOT_USED_RECORD_NTF, HandleDBServMsg_RebateMoneyNotUsedRecordNtf)
        HANDLE_MSG(PROTO_DB_PLAYER_SET_NAME_ACK, HandleDBServMsg_PlayerSetNameAck)
        HANDLE_MSG(PROTO_DB_GET_TITLE_INFO_ACK, HandleDBServMsg_PlayerGetTitleInfo)
        HANDLE_MSG(PROTO_DB_GET_CUST_LIST_INFO_ACK, HandleDBServMsg_GetCustListInfoAck)
        HANDLE_MSG(PROTO_DB_GOODS_NOT_POST_RECORDS_NTF, HandleDBServMsg_GoodsNotPostRecordsNtf)



    END_MSG_HANDLER()
}

void SessionMS2CS::HandleDBServMsg_PlayerCustVar(void *pData)
{
    auto *msg = static_cast<ProtoDB_PlayerCustVar *>(pData);

    std::unique_ptr<CUST_VAR_MAP> vars(msg->vars);

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->roleid);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    if (player->GetToken() != msg->token) {
        LOG_ERROR("token does not match");
        return;
    }

    player->SetCustVars(std::move(*vars));
}

void SessionMS2CS::HandleDBServMsg_PlayerItemCustVar(void *pData)
{
    auto *msg = static_cast<ProtoDB_PlayerItemCustVar *>(pData);

    std::unique_ptr<CUST_VAR_SP_LIST> vars(msg->vars);

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->roleid);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    if (player->GetToken() != msg->token) {
        LOG_ERROR("token does not match");
        return;
    }

    player->SetItemCustVars(std::move(*vars));
}

void SessionMS2CS::HandleDBServMsg_GetCustVarAck(void *pData)
{
    auto *msg = static_cast<ProtoDB_GetCustVarAck *>(pData);

    std::unique_ptr<CUST_VAR_SP_LIST> vars(msg->vars);

    CustVarMgr::GetInstance()->SetGlobalVars(std::move(*vars));

    OnCustVarReady();
}

void SessionMS2CS::HandleDBServMsg_AddMailAck(void* pData)
{
    auto data = (ProtoDB_AddMailAck*)pData;
    for (int i = 0; i < data->num; ++i)
    {
        auto player = MapRoleMgr::GetInstance()->FindPlayer(data->infos[i].playerguid);
        if (player)
        {
            MailMgr::AddMailInfo(this, player, data->infos[i]);
        }
    }
}

void SessionMS2CS::HandleDBServMsg_GetMailInfoAck(void* pData)
{
    auto data =(ProtoDB_GetMailInfoAck*)pData;
    for (int i = 0; i < data->num; ++i) {
        auto player = MapRoleMgr::GetInstance()->FindPlayer(data->infos[i].playerguid);
        MailMgr::AddMailInfo(this, player, data->infos[i]);
    }
}

void SessionMS2CS::HandleDBServMsg_ItemDynAttrNtf(void *pData)
{
    const auto *msg = static_cast<ProtoDB_ItemDynAttrNtf *>(pData);

    std::unique_ptr<ITEM_DYN_ATTRS_LIST> attrsList(msg->item_dyn_attrs_list);

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->roleid);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    if (player->GetToken() != msg->token) {
        LOG_ERROR("token does not match");
        return;
    }

    player->SetItemDynAttrsList(std::move(*attrsList));
}

void SessionMS2CS::HandleDBServMsg_RoleDynAttrNtf(void* pData)
{
    const auto* msg = static_cast<ProtoDB_RoleDynAttrNtf*>(pData);

    std::unique_ptr<ROLE_DYN_ATTRS_LIST> attrsList(msg->role_dyn_attrs_list);

    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->roleid);
    if (!player) {
        LOG_ERROR("player is NULL");
        return;
    }

    if (player->GetToken() != msg->token) {
        LOG_ERROR("token does not match");
        return;
    }

    player->SetRoleDynAttrsList(std::move(*attrsList));
}

void SessionMS2CS::HandleDBServMsg_GetProhibitInfoAck(void* pData)
{
    const auto* msg = static_cast<ProtoDB_GetProhibitChatInfoAck*>(pData);
    ProhibitChatMgr::GetInstance()->GetProhibitInfoAck(msg->num, msg->infos);
}

void SessionMS2CS::HandleDBServMsg_GoodsNotIssuedRecordsNtf(void *pData)
{
    const auto *msg = static_cast<ProtoDB_GoodsNotIssuedRecordsNtf *>(pData);
    auto *player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_guid);
    if (!player) {
        LOG_ERROR("player is NULL, role_guid: %llu", msg->role_guid);
        return;
    }
    player->SetGoodsNotIssuedRecords(msg->records, msg->num);
}

void SessionMS2CS::HandleDBServMsg_RebateMoneyNotUsedRecordNtf(void* pData)
{
    const auto* msg = static_cast<ProtoDB_RebateMoneyNotUsedRecordNtf*>(pData);
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_guid);
    if (!player) {
        LOG_ERROR("player is NULL, role_guid: %llu", msg->role_guid);
        return;
    }
    player->SetRebateMoneyNotUsedRecord(msg->record);
}

void SessionMS2CS::HandleDBServMsg_PlayerSetNameAck(void* pData)
{
    const auto* msg = static_cast<ProtoDB_PlayerSetNameAck*>(pData);
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->guid);
    if (!player)return;

    TRIGGER_EVENT(player, trigger_player_set_name, player->GetGUIDAsString(),msg->errcode, msg->orgName);

    if (msg->errcode != ERR_OK) {
        //player->SendErrorAck(msg->errcode);
        return;
    };
    player->SetNameInfo(msg->name);
}

void SessionMS2CS::HandleDBServMsg_PlayerGetTitleInfo(void* pData)
{
    auto* msg = static_cast<ProtoDB_GetTitleInfoAck*>(pData);
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->guid);
    if (!player)return;

    player->OnRecvTitleFromDB(msg->num, msg->info);
}

void SessionMS2CS::HandleDBServMsg_GetCustListInfoAck(void* pData)
{
    auto* msg = static_cast<ProtoDB_GetCustListInfoAck*>(pData);
    CustListMgr::GetInstance()->GetInfoFromDB(msg->num, msg->data);
}

void SessionMS2CS::HandleMapServMsg_CustomHttpAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_CustomHttpAck*>(pData);
    LuaBindCallVoid(msg->func, msg->data);
}

void SessionMS2CS::HandleDBServMsg_GoodsNotPostRecordsNtf(void* pData)
{
    const auto* msg = static_cast<ProtoDB_GoodsNotPostRecordsNtf*>(pData);
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(msg->role_guid);
    if (!player) {
        LOG_ERROR("player is NULL, role_guid: %llu", msg->role_guid);
        return;
    }
    player->SetGoodsNotPostRecords(msg->records, msg->num);
}

void SessionMS2CS::OnCustVarReady()
{
    mCustVarReady = true;
    OnDataReady();
}

void SessionMS2CS::OnGuildsReady()
{
    mGuildsRead = true;
    OnDataReady();
}

void SessionMS2CS::OnDataReady()
{
    if (mGuildsRead && mCustVarReady) {
        CastleWarMgr::GetInstance()->RecoverCastleWar();
    }
}
