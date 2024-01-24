#include "stdafx.h"
#include "GMCmdHandler.h"
#include "ProhibitChatMgr.h"
#include "CustVarMgr.h"
#include "LuaGmMgr.h"
#include "PlayerChatProhibitMgr.h"
#include "MailMgr.h"

#define HANDLE_CMD(cmd) { #cmd, &GMCmdHandler::HandleCmd_##cmd }

void GMCmdHandler::HandleCmd(Player *admin, const char *cmd, const char *param, int32_t sn)
{
    if (!admin || !cmd || !param) return;

    if (IsNeedSendToCS(cmd, param)) {
        SendRunGMCmdToCS(cmd, param);
    }

    using handler_t = int32_t (*)(Player *, const char *);

    static std::map<std::string, handler_t> handlers = {
        HANDLE_CMD(closeS),
        HANDLE_CMD(maintenanceS),
        HANDLE_CMD(ResetmaintenanceS),
        HANDLE_CMD(AddWhiteIP),
        HANDLE_CMD(DelWhiteIP),
        HANDLE_CMD(AddBlackIP),
        HANDLE_CMD(DelBlackIP),
        HANDLE_CMD(support_player),
        HANDLE_CMD(un_support_player),
        HANDLE_CMD(lock_player),
        HANDLE_CMD(unlock_player),
        HANDLE_CMD(lock_role),
        HANDLE_CMD(unlock_role),
        HANDLE_CMD(prohibit_chat),
        HANDLE_CMD(unprohibit_chat),
        HANDLE_CMD(ReloadScript),
        HANDLE_CMD(ReloadGameCfg),
        HANDLE_CMD(IssueGoods),
        HANDLE_CMD(mail),
        HANDLE_CMD(add64),
        HANDLE_CMD(sendmsg),
        HANDLE_CMD(AddItem),
        HANDLE_CMD(RemoveItem),
        HANDLE_CMD(SetPlayerProp),
        HANDLE_CMD(SetPlayerCustVar),
        HANDLE_CMD(AddBuff),
        HANDLE_CMD(AddLuaGM),
        HANDLE_CMD(DelLuaGM),
        HANDLE_CMD(AddPlayerProhibitChat),
        HANDLE_CMD(DelPlayerProhibitChat),
        HANDLE_CMD(RunScript),
        HANDLE_CMD(DeleteMail),
        HANDLE_CMD(DeleteRole),
        HANDLE_CMD(KickOut)

    };

    auto it = handlers.find(cmd);
    if (it == handlers.end()) {
        LOG_WARN("Unrecognized gm cmd: %s", cmd);
        admin->SendGMErrorAck(sn, ERR_NOGMCMD);
        return;
    }

    auto &handler = it->second;
    auto ecode = handler(admin, param);
    admin->SendGMErrorAck(sn, ecode);

    RecordOperation(admin, cmd, param);
}

void GMCmdHandler::RecordOperation(Player *admin, const char *cmd, const char *param)
{
    auto playerGUID = admin->GetGUID();
    auto gmLevel = admin->GetRoleProp(role_gm_level);

    SendDBLogData(log_type_gm_cmd, LogGmCmd(playerGUID, gmLevel, cmd, cmd, param));
}

bool GMCmdHandler::IsNeedSendToCS(const char *cmd, const char *param)
{
    if (!cmd || !param) return false;

    if (strcmp(cmd, "ReloadGameCfg") == 0) {
        return true;
    }

    return false;
}

void GMCmdHandler::SendRunGMCmdToCS(const char *cmd, const char *param)
{
    ProtoMS_RunGMCmd data;
    strcpy_s(data.cmd, cmd);
    strcpy_s(data.param, param);
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

int32_t GMCmdHandler::HandleCmd_closeS(Player *admin, const char *param)
{
    // 先GS提出在线玩家
    ProtoMS_SetServerStatus data;
    data.status = server_status_close;
    SendDataBySessionType(SESSION_TYPE_MS2GS, data, true);

    // 延时关闭服务器
    TimerData timer;
    timer.interval = CLOSE_SERVER_DELAY_TIME;
    timer.loop = false;
    timer.callBack = [](const TimerData &) {
        ProtoMS_SetServerStatus data;
        data.status = server_status_close;
        SendDataBySessionType(SESSION_TYPE_MS2CS, data);
        SendDataBySessionType(SESSION_TYPE_MS2SS, data);
        SendDataBySessionType(SESSION_TYPE_MS2LOG, data);

        TimerData _timer;
        _timer.interval = CLOSE_CUR_SERVER_DELAY_TIME;
        _timer.loop = false;
        _timer.callBack = [](const TimerData &) {
            MapServer::GetInstance()->Quit();
        };
        TimeHelper::GetInstance()->AddTimer(_timer);
    };
    TimeHelper::GetInstance()->AddTimer(timer);

    return ERR_OK;
}

int32_t GMCmdHandler::HandleCmd_maintenanceS(Player *admin, const char *param)
{
    // 玩家下线
    ProtoMS_SetServerStatus data;
    data.status = server_status_maintenance;
    // GS不再接收登录请求
    SendDataBySessionType(SESSION_TYPE_MS2GS, data, true);

    return ERR_OK;
}

int32_t GMCmdHandler::HandleCmd_ResetmaintenanceS(Player *admin, const char *param)
{
    ProtoMS_SetServerStatus data;
    data.status = server_status_reset_maintenance;
    SendDataBySessionType(SESSION_TYPE_MS2GS, data, true);

    return ERR_OK;
}

int32_t GMCmdHandler::HandleCmd_AddWhiteIP(Player *admin, const char *param)
{
    auto ips = str_split(param, " ");

    ProtoMS_AddLoginIpType data;
    data.ip_type = login_ip_type_white;
    for (const auto &ip : ips) {
        data.ip[data.num++] = Utility::IpStr2UInt(ip);
    }
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);

    return ERR_OK;
}

int32_t GMCmdHandler::HandleCmd_DelWhiteIP(Player *admin, const char *param)
{
    auto ips = str_split(param, " ");

    ProtoMS_DelLoginIpType data;
    data.ip_type = login_ip_type_white;
    for (const auto &ip : ips) {
        data.ip[data.num++] = Utility::IpStr2UInt(ip);
    }
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);

    return ERR_OK;
}

int32_t GMCmdHandler::HandleCmd_AddBlackIP(Player *admin, const char *param)
{
    auto ips = str_split(param, " ");

    ProtoMS_AddLoginIpType data;
    data.ip_type = login_ip_type_black;
    for (const auto &ip : ips) {
        data.ip[data.num++] = Utility::IpStr2UInt(ip);
    }
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);

    return ERR_OK;
}

int32_t GMCmdHandler::HandleCmd_DelBlackIP(Player *admin, const char *param)
{
    auto ips = str_split(param, " ");

    ProtoMS_DelLoginIpType data;
    data.ip_type = login_ip_type_black;
    for (const auto &ip : ips) {
        data.ip[data.num++] = Utility::IpStr2UInt(ip);
    }
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);

    return ERR_OK;
}

int32_t GMCmdHandler::HandleCmd_support_player(Player* admin, const char* param)
{
    auto names = str_split(param, " ");

    ProtoMS_UpdateSupportPlayer data;
    data.type = 1;
    for (const auto &name : names) {
        auto player = MapRoleMgr::GetInstance()->GetPlayerByUserName(name);
        if (player) player->SetSupport(data.type);
        strcpy_s(data.name[data.num], sizeof(data.name[data.num]), name.c_str());
        ++data.num;
        if (data.num >= 100)
        {
            SendDataBySessionType(SESSION_TYPE_MS2CS, data);
            data.num = 0;
        }
    }
    if (data.num) SendDataBySessionType(SESSION_TYPE_MS2CS, data);
    return ERR_OK;
}

int32_t GMCmdHandler::HandleCmd_un_support_player(Player* admin, const char* param)
{
    auto names = str_split(param, " ");

    ProtoMS_UpdateSupportPlayer data;
    data.type = 0;
    for (const auto &name : names) {
        auto player = MapRoleMgr::GetInstance()->GetPlayerByUserName(name);
        if (player) player->SetSupport(data.type);
        strcpy_s(data.name[data.num], sizeof(data.name[data.num]), name.c_str());
        ++data.num;
        if (data.num >= 100)
        {
            SendDataBySessionType(SESSION_TYPE_MS2CS, data);
            data.num = 0;
        }
    }
    if (data.num) SendDataBySessionType(SESSION_TYPE_MS2CS, data);
    return ERR_OK;
}

int32_t GMCmdHandler::HandleCmd_lock_player(Player *admin, const char *param)
{
    auto names = str_split(param, " ");

    ProtoMS_AddLockPlayer data;
    for (const auto &name : names) {
        strcpy_s(data.name[data.num], sizeof(data.name[data.num]), name.c_str());
        ++data.num;
    }
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
    return ERR_OK;
}

int32_t GMCmdHandler::HandleCmd_unlock_player(Player *admin, const char *param)
{
    auto names = str_split(param, " ");

    ProtoMS_DelLockPlayer data;
    for (const auto &name : names) {
        strcpy_s(data.name[data.num], sizeof(data.name[data.num]), name.c_str());
        ++data.num;
    }
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
    return ERR_OK;
}

int32_t GMCmdHandler::HandleCmd_DeleteRole(Player* admin, const char* param)
{
    ProtoMS_Del_Role_By_GM data;
    auto names = str_split(param, " ");
    if (names.size() == 2)
    {
        uint64_t _pid = 0;
        try {
            _pid = std::stoull(names[0]);
        }
        catch (...) {
            LOG_ERROR("DeleteRole err!");
        }
        data.pid = _pid;

        uint64_t _guid = 0;
        try {
            _guid = std::stoull(names[1]);
        }
        catch (...) {
            LOG_ERROR("DeleteRole err!");
        }
        data.guid = _guid;
       
    }
    else
    {
        LOG_ERROR("DeleteRole err!");
		return ERR_EXEGMCMDFAIL;
    }
   
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
    return ERR_OK;
}



int32_t GMCmdHandler::HandleCmd_lock_role(Player *admin, const char *param)
{
    const uint32_t SEND_WARNING_TIMES = 3;
    auto guids = str_split(param, " ");

    ProtoMS_AddLockRole data;
    for (const auto & guid : guids) {
        uint64_t _guid = 0;
        try {
            _guid = std::stoull(guid);
        }
        catch (...) {
            LOG_ERROR("lock_role guid err! %s", guid.c_str());
            continue;
        }
        auto* player = MapRoleMgr::GetInstance()->FindPlayer (_guid);
        if (player)
        {
            auto& info = gMESSAGE_INFO;
            info.Clear();
            strcpy_s(info.message, _countof(info.message), "您的角色因违规，被封禁处理，详情请联系客服");
            strcpy_s(info.font_color, _countof(info.font_color), "#0xffffff");
            strcpy_s(info.background_color, _countof(info.background_color), "#0xff0000");
            for (int i = 0; i < SEND_WARNING_TIMES; ++i) {
                player->SendSysMsgNtf2(info);
            }
            auto& roleinfo = player->GetRoleBriefInfo();
            roleinfo.is_lock = 1;
        }
        data.guid[data.num] = _guid;
        ++data.num;
    }
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);

    TimerData timer;
    timer.interval = KICK_PLAYER_DELAY_TIME;
    timer.loop = false;
    timer.callBack = [data](const TimerData &) {
        ProtoGS_KickOutByLock ack;
        ack.info = E_EXIT_EXITGS;
        for (int i = 0; i < data.num; ++i)
        {
            auto player = MapRoleMgr::GetInstance()->FindPlayer(data.guid[i]);
            if (player)
            {
                ack.sessionid = player->GetClSessionID();
                ack.token = player->GetToken();
                SendDataBySessionID(player->GetGsSessionID(), ack);
            }
        }
    };
    TimeHelper::GetInstance()->AddTimer(timer);
    return ERR_OK;
}

int32_t GMCmdHandler::HandleCmd_unlock_role(Player *admin, const char *param)
{
    auto names = str_split(param, " ");

    ProtoMS_DelLockRole data;
    for (const auto &name : names) {
        strcpy_s(data.name[data.num], sizeof(data.name[data.num]), name.c_str());
        ++data.num;
    }
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
    return ERR_OK;

}

int32_t GMCmdHandler::HandleCmd_prohibit_chat(Player *admin, const char *param)
{
    auto infos = str_split(param, " ");

    PROHIBIT_CHAT_DATA data[100];
    int num = 0;
    auto stamp = (uint64_t)MS2S(GetTimeStampMillisecond());
    for (auto &it : infos) {
        auto kv = str_split(std::move(it), ":");
        if (kv.size() == 1)
        {
            data[num].playerguid = std::stoull(kv.front());
            data[num].time = stamp + ONE_MONTH_STAMP;
            ++num;
        }
        else if (kv.size() == 2)
        {
            data[num].playerguid = std::stoull(kv.front());
            data[num].time = stamp + std::stoull(kv.back());
            ++num;
        }
    }
    ProhibitChatMgr::GetInstance()->AddProhibitData(num, data);
    return ERR_OK;

}

int32_t GMCmdHandler::HandleCmd_unprohibit_chat(Player *admin, const char *param)
{
    auto infos = str_split(param, " ");

    PROHIBIT_CHAT_DATA data[100];
    int num = 0;
    for (const auto &it : infos) {
        data[num++].playerguid = std::stoull(it);
    }
    ProhibitChatMgr::GetInstance()->DelProhibitData(num, data);
    return ERR_OK;

}

int32_t GMCmdHandler::HandleCmd_ReloadScript(Player *admin, const char *param)
{
    auto files = str_split(param, " ");
    auto num = files.size();
    bool result = true;

    auto t0 = std::chrono::high_resolution_clock::now();

    if (num == 0) {            // 加载全部
        result = MapServer::GetInstance()->LoadLuaScripts();
    }
    else {
#ifdef __linux__
        for (auto &file : files) file = gbk_to_utf8(file);
#endif
        result = CLuaEngine::GetInstance()->LoadLuaScripts(std::move(files));
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);

    LOG_NORMAL("[GM] Reloading %s scripts takes time: %dms",
               num ? std::to_string(num).c_str() : "all", dt.count());

    return result ? ERR_OK : ERR_EXEGMCMDFAIL;
}

int32_t GMCmdHandler::HandleCmd_ReloadGameCfg(Player *admin, const char *param)
{
    auto files = str_split(param, " ");
    bool result = true;

    if (files.empty()) {            // 加载全部
        result = GameCfgMgr::GetInstance()->ReloadAllCfg();
    }
    else {
        result = GameCfgMgr::GetInstance()->ReloadCfg(files);
    }

    if (sGlobalConfig.GetReloaded())
    {
        SessionMS2CS *session = (SessionMS2CS *)CNetManager::GetInstance()->GetSessionByType(SESSION_TYPE_MS2CS);
        if (session) session->SendGlobalNtfToClient();
        sGlobalConfig.ResetReload();
    }

    return result ? ERR_OK : ERR_EXEGMCMDFAIL;
}

int32_t GMCmdHandler::HandleCmd_IssueGoods(Player *admin, const char *param)
{
    bool handled = false;

    SAFE_BEGIN;

    do {
        Json::Value root;
        Json::Reader reader;
        if (!reader.parse(param, param + strlen(param), root)) {
            LOG_ERROR("[GM] parse PayInfo failed. param: %s", param);
            break;
        }

        GOODS_ISSUE_RECORD record;

        if (!root.isMember("order")) {
            LOG_ERROR("[GM] No order member. param: %s", param);
            break;
        }
        auto *order = root["order"].asCString();
        strcpy_s(record.order_no, order ? order : "");

        if (!root.isMember("role")) {
            LOG_ERROR("[GM] No role member. param: %s", param);
            break;
        }
        auto sRoleGUID = root["role"].asString();
        record.role_guid = std::stoull(sRoleGUID);

        if (!root.isMember("type")) {
            LOG_ERROR("[GM] No type member. param: %s", param);
            break;
        }
        record.pay_type = static_cast<uint8_t>(root["type"].asUInt());

        if (!root.isMember("goods")) {
            LOG_ERROR("[GM] No goods member. param: %s", param);
            break;
        }
        record.goods_id = root["goods"].asUInt();

        if (!root.isMember("count")) {
            LOG_ERROR("[GM] No count member. param: %s", param);
            break;
        }
        record.goods_num = root["count"].asUInt();

        if (!root.isMember("amount")) {
            LOG_ERROR("[GM] No amount member. param: %s", param);
            break;
        }
        record.pay_amount = root["amount"].asUInt();

        auto *player = MapRoleMgr::GetInstance()->FindPlayer(record.role_guid);
        if (player) {
            handled = player->HandleGoodsIssue(record);
        }
        else {
            LOG_NORMAL("[GM] player is not online");
            handled = admin->SendSaveGoodsIssueRecordToCS(record, true);
        }
    } while (0);

    LOG_NORMAL("[GM] handled: %d", handled);

    SAFE_END;

    return handled ? ERR_OK : ERR_EXEGMCMDFAIL;
}

int32_t GMCmdHandler::HandleCmd_mail(Player *admin, const char* param)
{
    int32_t ret = ERR_OK;
    MSG_BUFFER_DATA(ProtoMS_AddSysNewMail, data);

    SAFE_BEGIN

    auto err = MailMgr::ParseParamsByGM(param, data);
    if (err != ERR_OK){
        return err;
    }
    ret = MailMgr::AddMailSys2Player(data);

    SAFE_END;

    return (ret == ERR_OK) ? ERR_OK : ERR_MAIL_ADD_FAILED;
};

int32_t GMCmdHandler::HandleCmd_add64(Player *admin, const char* param)
{
    SAFE_BEGIN
    auto info = str_split(param, " ");
    if (info.size() != 4){
        return ERR_EXEGMCMDFAIL;
    }

    auto player = MapRoleMgr::GetInstance()->GetPlayerByName(info[0]);
    if (!player){
        return ERR_EXEGMCMDFAIL;
    }

    int prop = 0;
    int64_t value = 0;
    std::string desc;
    try
    {
        prop = std::stoi(info[1]);
        value = std::stoll(info[2]);
        desc = info[3];
    }
    catch (...) {
        return ERR_EXEGMCMDFAIL;
    };

    auto curValue = player->GetRoleProp64(prop);
    if (curValue + value < 0) return ERR_EXEGMCMDFAIL;

    if (prop == role_exp) {
        player->AddRoleExp(value, log_params{ "GM改变经验属性" });
    }
    else {
        player->AddRoleProp64(prop, value, log_params{ desc });
    }
    player->UpdateRoleInfo();
    SAFE_END

    return ERR_OK;
}

int32_t GMCmdHandler::HandleCmd_sendmsg(Player *admin, const char* param)
{
    SAFE_BEGIN
    auto& data = gMESSAGE_INFO;
    data.Clear();
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(param, root)) {
        LOG_ERROR("parse sendmsg failed. param: %s", param);
        return ERR_EXEGMCMDFAIL;
    }
    
    // 不用type区分  改用display_type区分
    if (!root["type"].isNull() && root["type"].isIntegral()) {
        //LOG_ERROR("parse sendmsg failed. param: %s", param);
        //mPlayer->SendGMErrorAck(sn, ERR_EXEGMCMDFAIL);
        //data.type = root["type"].asUInt();
    }

    if (root["display_type"].isNull() || !root["display_type"].isIntegral()) {
        LOG_ERROR("parse sendmsg failed. param: %s", param);
        return ERR_EXEGMCMDFAIL;
    }
    data.display_type = root["display_type"].asUInt();

    if (root["text"].isNull() || !root["text"].isString()) {
        LOG_ERROR("parse sendmsg failed. param: %s", param);
        return ERR_EXEGMCMDFAIL;
    }
    auto text = root["text"].asCString();

    if (!root["font_color"].isNull() && root["font_color"].isString()) {
        strcpy_s(data.font_color, _countof(data.font_color), root["font_color"].asCString());
    }

    if (!root["back_color"].isNull() && root["back_color"].isString()) {
        strcpy_s(data.background_color, _countof(data.background_color), root["back_color"].asCString());
    }

    if (!root["comp"].isNull() && root["comp"].isIntegral()) {
        data.comp = root["comp"].asUInt();
    }

    if (!root["scroll_times"].isNull() && root["scroll_times"].isIntegral()) {
        data.scroll_times = root["scroll_times"].asUInt();
    }

    uLongf nDstLen = _countof(data.message);
    if (data.comp) {
        auto result = compress((Bytef*)data.message, &nDstLen, (const Bytef*)text, strlen(text));
        if (result != Z_OK) {
            LOG_ERROR("SendRelationChatNtf failed ,compress failed with error, %d", result);
            return ERR_EXEGMCMDFAIL;
        }
        data.size = nDstLen;
    }
    else {
        strcpy_s(data.message, _countof(data.message), text);
    }

    auto& playermap = MapRoleMgr::GetInstance()->GetPlayerMap();
    for (auto& i : playermap){
        if (i.second){
            i.second->SendCustMsgNtf(data);
        }
    }

    //LOG_ERROR("parse sendmsg failed. param: %s", param);
    //mPlayer->SendGMErrorAck(sn, ERR_EXEGMCMDFAIL);
    //return;
    SAFE_END

    return ERR_OK;
}

int32_t GMCmdHandler::HandleCmd_AddItem(Player *admin, const char *param)
{
    auto params = str_split(param, " ");
    if (params.size() != 4) return ERR_EXEGMCMDFAIL;

    const auto &playerName = params[0];
    auto *player = MapRoleMgr::GetInstance()->GetPlayerByName(playerName);
    if (!player) return ERR_EXEGMCMDFAIL;

    const auto &itemKeyName = params[1];
    auto num = static_cast<uint16_t>(atoi(params[2].c_str()));
    auto bindType = static_cast<uint8_t>(atoi(params[3].c_str()));

    auto result = player->AddItemByKeyName(itemKeyName, num, bindType, 0, {"GM添加物品"});
    return result;
}

int32_t GMCmdHandler::HandleCmd_RemoveItem(Player *admin, const char *param)
{
    auto params = str_split(param, " ");
    if (params.size() != 4) return ERR_EXEGMCMDFAIL;

    const auto &playerName = params[0];
    auto *player = MapRoleMgr::GetInstance()->GetPlayerByName(playerName);
    if (!player) return ERR_EXEGMCMDFAIL;

    const auto &itemKeyName = params[1];
    auto num = static_cast<uint16_t>(atoi(params[2].c_str()));
    auto bindType = static_cast<uint8_t>(atoi(params[3].c_str()));

    auto result = player->RemoveItem(itemKeyName, num, bindType, site_range_bag, {"GM删除物品"});
    return result;
}

int32_t GMCmdHandler::HandleCmd_SetPlayerProp(Player *admin, const char *param)
{
    auto params = str_split(param, " ");
    if (params.size() != 3) return ERR_EXEGMCMDFAIL;

    const auto &playerName = params[0];
    auto *player = MapRoleMgr::GetInstance()->GetPlayerByName(playerName);
    if (!player) return ERR_EXEGMCMDFAIL;

    auto prop = atoi(params[1].c_str());
    auto value = atoi(params[2].c_str());

    player->SetRoleProp(prop, value);
    return ERR_OK;
}

int32_t GMCmdHandler::HandleCmd_SetPlayerCustVar(Player* admin, const char* param)
{
    auto params = str_split(param, " ");
    if (params.size() != 4) return ERR_EXEGMCMDFAIL;

    const auto& playerName = params[0];
    auto* player = MapRoleMgr::GetInstance()->GetPlayerByName(playerName);
    if (!player) return ERR_EXEGMCMDFAIL;

    const auto& name = params[1];
    const auto& value = params[2];
    auto type = atoi(params[3].c_str());

    bool canSet = false;
    TRIGGER_EVENT_RET(canSet, player, trigger_pre_set_customer_var, player->GetGUIDAsString(), name, value, type);
    if (!canSet) return ERR_EXEGMCMDFAIL;

    CustVarMgr::GetInstance()->SetVar(player->GetGUIDAsString(), name, value, type);
    return ERR_OK;
}

int32_t GMCmdHandler::HandleCmd_AddBuff(Player* admin, const char* param)
{
    auto params = str_split(param, " ");
    if (params.size() != 5) return ERR_EXEGMCMDFAIL;

    const auto& playerName = params[0];
    auto* player = MapRoleMgr::GetInstance()->GetPlayerByName(playerName);
    if (!player) return ERR_EXEGMCMDFAIL;


    auto buffID = atoi(params[1].c_str());
    auto skillID = atoi(params[2].c_str());
    const auto& attr = params[3];
    auto time = atoi(params[4].c_str());

    auto ret = player->AddBuffByRole(buffID, player, skillID, attr, time);

    return ret ? ERR_OK : ERR_EXEGMCMDFAIL;
}

int32_t GMCmdHandler::HandleCmd_AddLuaGM(Player* admin, const char* param)
{
    auto params = str_split(param, " ");
    if (params.size() != 2) return ERR_EXEGMCMDFAIL;

    uint64_t playerGUID = 0;
    try {
        playerGUID = std::stoull(params[0].c_str());
    }
    catch (...) {
        return ERR_EXEGMCMDFAIL;
    }

    auto lv = atoi(params[1].c_str());

    auto ret = LuaGmMgr::GetInstance()->AddLuaGM(playerGUID, lv);
    return ret ? ERR_OK : ERR_EXEGMCMDFAIL;
}

int32_t GMCmdHandler::HandleCmd_DelLuaGM(Player* admin, const char* param)
{
    uint64_t playerGUID = 0;
    try {
        playerGUID = std::stoull(param);
    }
    catch (...) {
        return ERR_EXEGMCMDFAIL;
    }

    auto ret = LuaGmMgr::GetInstance()->DelLuaGm(playerGUID);
    return ret ? ERR_OK : ERR_EXEGMCMDFAIL;
}

int32_t GMCmdHandler::HandleCmd_RunScript(Player* admin, const char* param)
{
    //执行  lua脚本

    auto params = str_split(param, "#");
    bool ret = false;
    if (params.size() == 2)
    {
        TRIGGER_EVENT_RET<bool>(ret, trigger_gm_cmd, params[0].c_str(), params[1].c_str());
    }
    return ret ? ERR_OK : ERR_EXEGMCMDFAIL;
}

int32_t GMCmdHandler::HandleCmd_DeleteMail(Player* admin, const char* param)
{
    auto params = str_split(param, " ");
    bool ret = false;
    if (params.size() != 2)return ERR_EXEGMCMDFAIL;

    ProtoMS_DeleteMailReq data;

    try {
        data.playerguid = std::stoull(params[0]);
        data.id = std::stoull(params[1]);
    }
    catch (...) {
        return ERR_EXEGMCMDFAIL;
    }

    auto player = MapRoleMgr::GetInstance()->FindPlayer(data.playerguid);
    if (player) {
        auto& MailVector = player->GetMailInfo();
        auto it = find_if(MailVector.begin(), MailVector.end(), [&data](MAIL_INFO& a) {return data.id == a.mail_id; });
        if (it != MailVector.end()) {
            it->status |= mail_status_delete;
        }
        data.sessid = player->GetGsSessionID();
    }
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);

    return ERR_OK;
}

int32_t GMCmdHandler::HandleCmd_KickOut(Player* admin, const char* param)
{
    uint64_t guid = 0;
    try {
        guid = std::stoull(param);
    }
    catch (...) {
        return ERR_EXEGMCMDFAIL;
    }

    ProtoGS_KickOutByLock data;

    if (guid == 0) {
        auto &playerMap = MapRoleMgr::GetInstance()->GetPlayerMap();
        for (auto& i : playerMap) {
            if (i.second && !i.second->IsGM()) {
                data.sessionid = i.second->GetClSessionID();
                data.token = i.second->GetToken();
                data.info = E_EXIT_EXITGS;
                SendDataBySessionID(i.second->GetGsSessionID(), data);
            }
        }

    }
    else {
        auto player = MapRoleMgr::GetInstance()->FindPlayer(guid);
        if (!player) {
            LOG_ERROR("Kick Out Player Failed! Not online playerguid:%", PRIu64, guid);
            return ERR_EXEGMCMDFAIL;
        }
        if (player->IsGM())return ERR_EXEGMCMDFAIL;
        data.sessionid = player->GetClSessionID();
        data.token = player->GetToken();
        data.info = E_EXIT_EXITGS;
        SendDataBySessionID(player->GetGsSessionID(), data);
    }
    return ERR_OK;
}


int32_t GMCmdHandler::HandleCmd_AddPlayerProhibitChat(Player* admin, const char* param)
{
    auto params = str_split(param, " ");
    if (params.size() != 2) return ERR_EXEGMCMDFAIL;

    uint64_t userID = 0;
    int64_t stamp = 0;
    try {
         userID = std::stoull(params[0]);
    }
    catch (...) {
        return ERR_EXEGMCMDFAIL;
    }

    try {
         stamp = _atoi64(params[1].c_str());
    }
    catch (...) {
        return ERR_EXEGMCMDFAIL;
    }

    PlayerProhibitChatMgr::GetInstance()->AddPlayerProhibitChatMgr(userID, stamp);
    return ERR_OK;
}

int32_t GMCmdHandler::HandleCmd_DelPlayerProhibitChat(Player* admin, const char* param)
{
    uint64_t userID = 0;
    try {
        userID = std::stoull(param);
    }
    catch (...) {
        return ERR_EXEGMCMDFAIL;
    }
    PlayerProhibitChatMgr::GetInstance()->DelPlayerProhibitChatMgr(userID);
    return ERR_OK;
}