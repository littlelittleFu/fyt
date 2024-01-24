#include "stdafx.h"
#include "SessionLS2GS.h"
#include "ILogHelper.h"
#include "ProtoClient.h"
#include "SessionContextMgr.h"
#include "CNetManager.h"
#include "SessionFactory.h"
#include "ProtoGS.h"
#include "ProtoLS.h"
#include "ThirdPartLoginMgr.h"
#include "LoginIPManager.h"
#include "MaintenanceMgr.h"

SessionLS2GS::SessionLS2GS()
{

}

SessionLS2GS::~SessionLS2GS()
{

}

void SessionLS2GS::OnEstablish(SOCKET _Socket)
{
    LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
	Session::OnEstablish(_Socket);

    ProtoGS_SessionIDNtf ntf;
    ntf.protocolid = PROTO_SESSION_LS2GS_NTF;
    ntf.sessionid = GetID();
    SendPkg(&ntf, sizeof(ntf));
}

void SessionLS2GS::OnLost()
{
    LOG_WARN("SessionLS2GS SESSION LOST!");
	Session::OnLost();
    SessionContextMgr::GetInstance()->DelAllContextOfGateServSessionID(GetID());    // 删除所连网关的所有context
}

void SessionLS2GS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    OnHeartBeat();

    switch (moduleid)
    {
        case MODULE_TYPE_GS:
            HandleGateServMsg(protoid, _pData);
            break;

        default:
            LOG_WARN("Unhandled moduleid: %d", moduleid);
            break;
    }
}

void SessionLS2GS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("SessionLS2GS ERROR %ld", _ErrorCode);
}

void SessionLS2GS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionLS2GS::DoHeartBeat()
{
}

void SessionLS2GS::HandleGateServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_GS_HEART_BEAT_REQ, HandleGateServMsg_HeartBeatReq)
        HANDLE_MSG(PROTO_GS_LOGIN_REQ, HandleGateServMsg_LoginReq)
        HANDLE_MSG(PROTO_GS_THIRD_LOGIN_REQ, HandleGateServMsg_ThirdLoginReq)
        HANDLE_MSG(PROTO_GS_LOGOUT_REQ, HandleGateServMsg_LogoutReq)
        HANDLE_MSG(PROTO_GS_RELOGIN_REQ, HandleGateServMsg_ReloginReq)
        HANDLE_MSG(PROTO_GS_SAVE_KEY_NTF, HandleGateServMsg_SaveKeyNtf)
        HANDLE_MSG(PROTO_GS_UPDATE_ONLINE_STATE, HandleGateServMsg_UpdateOnlineState)
        HANDLE_MSG(PROTO_GS_SET_MAINTENANCE_STATUE, HandleGateServMsg_SetMaintenanceStatus)
        HANDLE_MSG(PROTO_GS_KICK_OUT_BY_LOCK, HandleGateServMsg_KickOutByLock)

    END_MSG_HANDLER()
}

void SessionLS2GS::HandleGateServMsg_SaveKeyNtf(void* pData)
{
    ProtoGS_SaveKeyNtf*ntf = (ProtoGS_SaveKeyNtf*) pData;
    auto context = SessionContextMgr::GetInstance()->GetSessionContext(ntf->token);
    if (nullptr == context) {
        return;
    }
    
    context->sRandKey = ntf->key;
}

void SessionLS2GS::HandleGateServMsg_HeartBeatReq(void* pData)
{
    ProtoGS_HeartBeatAck ack;
    SendPkg(&ack, sizeof(ack));
}

void SessionLS2GS::HandleGateServMsg_LoginReq(void* pData)
{
    auto *pLoginReq = (ProtoGS_LoginReq *)pData;

    // 封ip判定
    if (LoginIPManager::GetInstance()->IsBlackIp(pLoginReq->ip))
    {
        SendLoginAckToGS(pLoginReq->clsessid, ERR_FORBIDLOGIN_IP, EMSG_VERIFY_TOKEN);
        return;
    }
    // 维护时只有白名ip可以登录
    if (MaintenanceMgr::GetInstance()->IsMaintenceIng()) {
        // 重新拉取白名单
        LoginIPManager::GetInstance()->GetWhiteIPList();
        LoginIPManager::GetInstance()->GetWhiteAccountNameList();

        bool isWhiteIP = false;
        bool isWhiteName = false;

        isWhiteIP = LoginIPManager::GetInstance()->IsWhiteIp(pLoginReq->ip);

        if (!isWhiteIP) {
            isWhiteName = LoginIPManager::GetInstance()->IsWhiteName(pLoginReq->username);
        }

        if (!isWhiteIP && !isWhiteName) {
            SendLoginAckToGS(pLoginReq->clsessid, ERR_SERVER_STATUS_MAINTENANCE, EMSG_MAINTENANCE);
            return;
        }
    }

    auto oldContext = SessionContextMgr::GetInstance()->GetSessionContext(pLoginReq->username);

    if (!oldContext || oldContext->nToken == 0) {       // 没有登录过

        if (!SendLoginReqToDB(pLoginReq)) {
            SendLoginAckToGS(pLoginReq->clsessid, ERR_SYSTEM, EMSG_LS2DB_CONN_ERROR);
            return;
        }

        if (oldContext) SessionContextMgr::GetInstance()->DelSessionContext(pLoginReq->username);

        // 缓存信息
        auto newContext = std::make_shared<SessionContext>();
        newContext->nGateServSessionID = GetID();
        newContext->nClientSessionID = pLoginReq->clsessid;
        newContext->sUserName = pLoginReq->username;
        newContext->sPassword = pLoginReq->password;
        newContext->nIP = pLoginReq->ip;
        newContext->sHardwareID = pLoginReq->hwid;

        SessionContextMgr::GetInstance()->AddSessionContext(newContext);
        return;
    }

    // 登录过，用缓存的密码
    if (oldContext->sPassword != pLoginReq->password) {   // 密码不正确

        SendLoginAckToGS(pLoginReq->clsessid, ERR_LOGIN_WRONG_PASSWORD, EMSG_WRONG_PASSWORD);
        return;
    }

    if (oldContext->nOnlineState == online_state_logged_in) {               // 在线

        if (oldContext->nGateServSessionID == GetID() &&
            oldContext->nClientSessionID == pLoginReq->clsessid) {         // 是自己，重复登录

            SendLoginAckToGS(pLoginReq->clsessid, ERR_REPEATLOGIN, EMSG_REPEAT_LOGIN);
            return;
        }

        // 不是自己,踢人
        SendKickRoleNtf(oldContext->nGateServSessionID, oldContext->nClientSessionID, oldContext->nPlayerGUID, ERR_REPEATLOGIN, EMSG_REPEAT_LOGIN);
        SendLogoutReqToCS(oldContext->nClientSessionID, oldContext->nToken);
    }
    else if (oldContext->nOnlineState == online_state_disconnected) {       // 连接中断没走relogin，直接login

        SendLogoutReqToCS(oldContext->nClientSessionID, oldContext->nToken);

        if (oldContext->nGateServSessionID != GetID()) {                    // 不是同一个gateserver
            SendRemoveContextToGS(oldContext->nGateServSessionID, oldContext->nClientSessionID);
        }
    }
    else {                                                                  // 未登录

        // do nothing
    }

    SessionContextMgr::GetInstance()->DelSessionContext(pLoginReq->username);

    // 复用oldContext
    oldContext->nGateServSessionID = GetID();
    oldContext->nClientSessionID = pLoginReq->clsessid;
    oldContext->nToken = Tools::GenerateUINT32();
    oldContext->sRandKey = Tools::GenerateGuidString();
    oldContext->nIP = pLoginReq->ip;
    oldContext->sHardwareID = pLoginReq->hwid;
    oldContext->nOnlineState = online_state_logged_in;

    SessionContextMgr::GetInstance()->AddSessionContext(oldContext);

    SendSaveLoginReqToCS(oldContext);

    SendLoginAckToGS(pLoginReq->clsessid, ERR_OK, nullptr, pLoginReq->username, oldContext->nPlayerGUID,
        oldContext->nToken, oldContext->sRandKey.c_str());
}

void SessionLS2GS::HandleGateServMsg_ThirdLoginReq(void *pData)
{
    const auto *msg = static_cast<ProtoGS_ThirdLoginReq *>(pData);

    // 封ip判定
    if (LoginIPManager::GetInstance()->IsBlackIp(msg->login_ip))
    {
        SendLoginAckToGS(msg->sessionid, ERR_FORBIDLOGIN_IP, EMSG_VERIFY_TOKEN);
        return;
    }
    // 维护时只有白名ip可以登录
    if (MaintenanceMgr::GetInstance()->IsMaintenceIng()) {
        // 重新拉取白名单
        LoginIPManager::GetInstance()->GetWhiteIPList();
        LoginIPManager::GetInstance()->GetWhiteAccountNameList();

        bool isWhiteIP = false;
        bool isWhiteName = false;

        isWhiteIP = LoginIPManager::GetInstance()->IsWhiteIp(msg->login_ip);

        if (!isWhiteIP) {
            isWhiteName = LoginIPManager::GetInstance()->IsWhiteName(msg->user_name);
        }

        if (!isWhiteIP && !isWhiteName) {
            SendLoginAckToGS(msg->sessionid, ERR_SERVER_STATUS_MAINTENANCE, EMSG_MAINTENANCE);
            return;
        }
    }

    auto context = SessionContextMgr::GetInstance()->GetSessionContext(msg->user_name);

    if (context) {

        if (context->nOnlineState == online_state_logged_in) {          // 已登录

            if (context->nGateServSessionID == GetID() &&
                context->nClientSessionID == msg->sessionid) {          // 是自己，重复登录

                SendLoginAckToGS(msg->sessionid, ERR_REPEATLOGIN, EMSG_REPEAT_LOGIN);
                return;
            }
        }
    }

    auto newContext = std::make_shared<SessionContext>();
    newContext->nGateServSessionID = GetID();
    newContext->nClientSessionID = msg->sessionid;
    newContext->sUserName = msg->user_name;
    newContext->nIP = msg->login_ip;
    newContext->sHardwareID = msg->hwid;
    newContext->sPlatformToken = msg->token;
    newContext->sChannel = msg->channel;
    newContext->nGameID = msg->gameid;

    ThirdPartLoginMgr::GetInstance()->CheckToken(std::move(newContext));
}

bool SessionLS2GS::SendLoginReqToDB(ProtoGS_LoginReq* req, uint8_t isThirdLogin)
{
    ProtoLS_LoginReq loginReq;
    loginReq.gssessid = GetID();
    loginReq.clsessid = req->clsessid;
    loginReq.isthirdlogin = isThirdLogin;
    loginReq.ip = req->ip;
    strcpy_s(loginReq.hwid, _countof(loginReq.hwid), req->hwid);
    strcpy_s(loginReq.username, _countof(loginReq.username), req->username);
    strcpy_s(loginReq.password, _countof(loginReq.password), req->password);

    return SendDataBySessionType(SESSION_TYPE_LS2DB, loginReq);
}

void SessionLS2GS::HandleGateServMsg_LogoutReq(void* pData)
{
    ProtoGS_LogoutReq* pLogoutReq = (ProtoGS_LogoutReq*)pData;

    uint64_t nKey = Tools::MakeQWORD(GetID(), pLogoutReq->sessionid);
    auto sessionContext = SessionContextMgr::GetInstance()->GetSessionContext(nKey);
    if (nullptr != sessionContext) {
        sessionContext->nOnlineState = online_state_not_logged_in;
        sessionContext->nClientSessionID = 0;
        sessionContext->nGateServSessionID = 0;

        SendLogoutReqToCS(pLogoutReq);
    }
}

void SessionLS2GS::HandleGateServMsg_ReloginReq(void* pData)
{
    const auto *msg = static_cast<ProtoGS_ReloginReq *>(pData);

    auto context = SessionContextMgr::GetInstance()->GetSessionContextByPlayerGUID(msg->player_guid);

    if (!context) {
        SendReloginAckToGS(msg->cl2gs_sessid, ERR_NOUSERDATA, EMSG_NO_USER_DATA);
        return;
    }

    if (context->sRandKey != msg->randkey) {
        SendReloginAckToGS(msg->cl2gs_sessid, ERR_NOUSERDATA, EMSG_INCONSIST_RANDKEY);
        return;
    }

    // 已经断开连接了 地图服务器数据已清空 需要重新登录
    if (context->nGateServSessionID == 0 && context->nClientSessionID == 0 && context->nOnlineState == online_state_not_logged_in) {
        SendReloginAckToGS(msg->cl2gs_sessid, ERR_NOUSERDATA, EMSG_NO_USER_DATA);
        return;
    }

    context->nOnlineState = online_state_logged_in;

    if (context->nGateServSessionID != GetID()) {   // 不是同一个gateserver
        SendRemoveContextToGS(context->nGateServSessionID, context->nClientSessionID);
    }

    if (context->nGateServSessionID != GetID() || context->nClientSessionID != msg->cl2gs_sessid) {
        SessionContextMgr::GetInstance()->DelSessionContext(context);
        context->nGateServSessionID = GetID();
        context->nClientSessionID = msg->cl2gs_sessid;
        context->nIP = msg->ip;
        context->sHardwareID = msg->hwid;
        SessionContextMgr::GetInstance()->AddSessionContext(context);
    }

    SendSaveLoginReqToCS(context);
    SendReloginAckToGS(msg->cl2gs_sessid, ERR_OK, nullptr, context->sUserName.c_str(), nullptr,
        context->nPlayerGUID, msg->role_guid, context->nToken, context->sRandKey.c_str());
}

void SessionLS2GS::HandleGateServMsg_UpdateOnlineState(void *pData)
{
    auto *msg = static_cast<ProtoGS_UpdateOnlineState *>(pData);

    auto context = SessionContextMgr::GetInstance()->GetSessionContext(msg->token);
    if (!context) return;
    context->nOnlineState = msg->state;

    SendDataBySessionType(SESSION_TYPE_LS2CS, *msg);
}

void SessionLS2GS::HandleGateServMsg_SetMaintenanceStatus(void* pData)
{
    auto* msg = static_cast<ProtoGS_SetMaintenanceStatus*>(pData);
    if(msg->status == server_status_maintenance)
    {
        MaintenanceMgr::GetInstance()->SetMaintence();
    }
    else if (msg->status == server_status_reset_maintenance)
    {
        MaintenanceMgr::GetInstance()->ReSetMaintence();
    }
}

void SessionLS2GS::HandleGateServMsg_KickOutByLock(void* pData)
{
    ProtoGS_KickOutByLock* pLogoutReq = (ProtoGS_KickOutByLock*)pData;

    uint64_t nKey = Tools::MakeQWORD(GetID(), pLogoutReq->sessionid);
    auto sessionContext = SessionContextMgr::GetInstance()->GetSessionContext(nKey);
    if (nullptr != sessionContext) {
        ProtoGS_LogoutReq data;
        data.info = pLogoutReq->info;
        data.sessionid = pLogoutReq->sessionid;
        data.token = pLogoutReq->token;
        SendLogoutReqToCS(&data);
        SessionContextMgr::GetInstance()->DelSessionContext(sessionContext);
    }
}

void SessionLS2GS::HandleDBServMsg_LoginAck(ProtoLS_LoginAck* pLoginAck)
{
    uint64_t nKey = Tools::MakeQWORD(GetID(), pLoginAck->clsessid);
    auto context = SessionContextMgr::GetInstance()->GetSessionContext(nKey);
    if (!context) {
        LOG_WARN("context is NULL");
        SendLoginAckToGS(pLoginAck->clsessid, ERR_UNKNOW, EMSG_UNKNOWN_ERROR);
        return;
    }

    if (pLoginAck->result != ERR_OK) {
        SessionContextMgr::GetInstance()->DelSessionContext(nKey);
        SendLoginAckToGS(pLoginAck->clsessid, pLoginAck->result, pLoginAck->info);
        return;
    }

    context->nToken = Tools::GenerateUINT32();
    context->sRandKey = Tools::GenerateGuidString();
    context->nPlayerGUID = pLoginAck->userid;
    context->nOnlineState = online_state_logged_in;
    context->nIP = pLoginAck->ip;
    context->sHardwareID = pLoginAck->hwid;

    SendSaveLoginReqToCS(context, 1, pLoginAck->isProhibitChat, 1, pLoginAck->isSupport);

    SendLoginAckToGS(pLoginAck->clsessid, pLoginAck->result, pLoginAck->info, pLoginAck->username,
        pLoginAck->userid, context->nToken, context->sRandKey.c_str());
}

bool SessionLS2GS::SendSaveLoginReqToCS(SPSessionContext& spSessionContext, uint8_t saveProhibitChat, int64_t isProhibitChat, uint8_t saveSupport, uint8_t isSupport)
{
    ProtoLS_SaveLoginReq saveLoginReq;
    saveLoginReq.token = spSessionContext->nToken;
    saveLoginReq.player_guid = spSessionContext->nPlayerGUID;
    strcpy_s(saveLoginReq.username, _countof(saveLoginReq.username), spSessionContext->sUserName.c_str());
    strcpy_s(saveLoginReq.randkey, _countof(saveLoginReq.randkey), spSessionContext->sRandKey.c_str());
    saveLoginReq.ip = spSessionContext->nIP;
    strcpy_s(saveLoginReq.hwid, spSessionContext->sHardwareID);
    strcpy_s(saveLoginReq.channel, _countof(saveLoginReq.channel), spSessionContext->sChannel.c_str());
    saveLoginReq.isSaveProhibit = saveProhibitChat;
    saveLoginReq.isProhibitChat = isProhibitChat;
    saveLoginReq.isSaveSupport = saveSupport;
    saveLoginReq.isSupport = isSupport;
    return SendDataBySessionType(SESSION_TYPE_LS2CS, saveLoginReq);
}

bool SessionLS2GS::SendLogoutNtfToGS(SPSessionContext& spContext)
{
    ProtoLS_LogoutNtf logoutNtf;
    logoutNtf.sessionid = spContext->nClientSessionID;
    strcpy_s(logoutNtf.username, _countof(logoutNtf.username), spContext->sUserName.c_str());
    logoutNtf.playerid = spContext->nPlayerGUID;

    // 发给网关通知用户下线
    bool ret = SendDataBySessionID(spContext->nGateServSessionID, logoutNtf);
    return ret;
}

bool SessionLS2GS::SendLogoutReqToCS(ProtoGS_LogoutReq* pLogoutReq)
{
    return SendDataBySessionType(SESSION_TYPE_LS2CS, *pLogoutReq);
}

void SessionLS2GS::SendLoginAckToGS(uint32_t clsessid, int32_t errcode, const char *errmsg, const char *username,
    uint64_t userid, uint32_t token, const char *randkey)
{
    ProtoGS_LoginAck data;

    data.clsessid = clsessid;
    data.errcode = errcode;
    if (errmsg) strcpy_s(data.errmsg, _countof(data.errmsg), errmsg);

    if (username) strcpy_s(data.username, _countof(data.username), username);
    data.userid = userid;

    data.token = token;
    if (randkey) strcpy_s(data.randkey, _countof(data.randkey), randkey);

    SendPkg(&data, sizeof(data));
}

void SessionLS2GS::SendKickRoleNtf(uint32_t gssess, uint32_t clsess, uint64_t roleguid, int32_t errorcode, const char* errmsg)
{
    ProtoGS_KickRoleNtf ntf;
    ntf.sessionid = clsess;
    ntf.roleguid = roleguid;
    ntf.errcode = errorcode;
    memcpy(ntf.errmsg, errmsg, strlen(errmsg) + 1);
    SendDataBySessionID(gssess, ntf);
}

void SessionLS2GS::HandleThirdPartLoginResult(SPSessionContext newContext)
{
    if (newContext->nPlayerGUID == 0) {
        SendLoginAckToGS(newContext->nClientSessionID, ERR_LOGIN_WRONG_USER, EMSG_VERIFY_TOKEN);
        return;
    }

    auto oldContext = SessionContextMgr::GetInstance()->GetSessionContextByPlayerGUID(newContext->nPlayerGUID);

    if (oldContext) {

        if (oldContext->nOnlineState == online_state_logged_in) {               // 已登录，踢人

            SendKickRoleNtf(oldContext->nGateServSessionID, oldContext->nClientSessionID, oldContext->nPlayerGUID, ERR_REPEATLOGIN, EMSG_REPEAT_LOGIN);
            SendLogoutReqToCS(oldContext->nClientSessionID, oldContext->nToken);
        }
        else if (oldContext->nOnlineState == online_state_disconnected) {       // 连接中断没走relogin，直接login

            SendLogoutReqToCS(oldContext->nClientSessionID, oldContext->nToken);

            if (oldContext->nGateServSessionID != GetID()) {                    // 不是同一个gateserver
                SendRemoveContextToGS(oldContext->nGateServSessionID, oldContext->nClientSessionID);
            }
        }

        SessionContextMgr::GetInstance()->DelSessionContext(newContext->sUserName.c_str());
    }

    SendInsertPlayerToDB(newContext->nPlayerGUID, newContext->sUserName.c_str());

    ProtoGS_LoginReq pLoginReq;
    pLoginReq.clsessid = newContext.get()->nClientSessionID;
    strcpy_s(pLoginReq.username, _countof(pLoginReq.username), newContext->sUserName.c_str());
    strcpy_s(pLoginReq.password, _countof(pLoginReq.password), newContext->sPassword.c_str());
    pLoginReq.ip = newContext->nIP;
    strcpy_s(pLoginReq.hwid, _countof(pLoginReq.hwid), newContext->sHardwareID.c_str());
    SendLoginReqToDB(&pLoginReq,true);
    ///  走一遍数据库 回来才能发ack

    SessionContextMgr::GetInstance()->AddSessionContext(newContext);
}

void SessionLS2GS::SendInsertPlayerToDB(uint64_t playerid, const char *username)
{
    ProtoLS_InsertPlayer data;
    data.playerid = playerid;
    strcpy_s(data.username, _countof(data.username), username);

    SendDataBySessionType(SESSION_TYPE_LS2DB, data);
}

void SessionLS2GS::SendLogoutReqToCS(uint32_t session, uint32_t token, uint8_t info)
{
    ProtoGS_LogoutReq data;

    data.sessionid = session;
    data.token = token;
    data.info = info;

    //SendDataBySessionType(SESSION_TYPE_LS2CS, data);
    SendLogoutReqToCS(&data);
}

void SessionLS2GS::SendRemoveContextToGS(uint32_t nGSSessionID, uint32_t nClientSessionID)
{
    ProtoLS_RemoveContext data;
    data.sessionid = nClientSessionID;

    SendDataBySessionID(nGSSessionID, data);
}

void SessionLS2GS::SendReloginAckToGS(uint32_t nClientSessionID, int32_t nErrCode, const char *pErrMsg, const char *pUserName,
    const char *pPassword, uint64_t nPlayerGUID, uint64_t nRoleGUID, uint32_t nToken, const char *pRandKey)
{
    ProtoGS_ReloginAck data;

    data.errcode = nErrCode;
    if (pErrMsg) strcpy_s(data.errmsg, _countof(data.errmsg), pErrMsg);

    data.player_guid = nPlayerGUID;
    data.role_guid = nRoleGUID;

    if (pUserName) strcpy_s(data.username, _countof(data.username), pUserName);
    if (pPassword) strcpy_s(data.password, _countof(data.password), pPassword);

    data.token = nToken;
    if (pRandKey) strcpy_s(data.randkey, _countof(data.randkey), pRandKey);

    data.cl2gs_sessid = nClientSessionID;

    SendPkg(&data, sizeof(data));
}
