#include "stdafx.h"
#include "SessionCS2LS.h"
#include "ILogHelper.h"
#include "CNetManager.h"
#include "SessionFactory.h"
#include "ProtoLS.h"
#include "ProtoGS.h"
#include "UserMgr.h" 

SessionCS2LS::SessionCS2LS()
{

}

SessionCS2LS::~SessionCS2LS()
{

}

void SessionCS2LS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionCS2LS::OnLost()
{
	LOG_NORMAL("OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
	//DoClose();
}

void SessionCS2LS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    MsgCostStat::GetInstance()->BeginHandleMsg();

    OnHeartBeat();

    switch (moduleid) {
        case MODULE_TYPE_LS:
            HandleLoginServMsg(protoid, _pData);
            break;

        case MODULE_TYPE_GS:
            HandleGateServMsg(protoid, _pData);
            break;

        default:
            LOG_WARN("Unhandled moduleid: %u", moduleid);
            break;
    }

    MsgCostStat::GetInstance()->EndHandleMsg(moduleid, protoid);
}

void SessionCS2LS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionCS2LS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionCS2LS::DoHeartBeat()
{
	
}

void SessionCS2LS::HandleLoginServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_LS_HEART_BEAT_REQ, HandleLoginServMsg_HeartBeatReq)
        HANDLE_MSG(PROTO_LS_SAVE_LOGIN_REQ, HandleLoginServMsg_SaveLoginReq)
    END_MSG_HANDLER()
}


void SessionCS2LS::HandleLoginServMsg_HeartBeatReq(void* pData)
{
    ProtoLS_HeartBeatAck ack;
    SendPkg(&ack, sizeof(ack));
}

void SessionCS2LS::HandleLoginServMsg_SaveLoginReq(void* pData)
{
    auto req = (ProtoLS_SaveLoginReq*)pData;
    auto user = UserMgr::GetInstance()->AddUser(req->player_guid);
    user->SetUserName(req->username);
    user->SetToken(req->token);
    user->SetRandKey(req->randkey);
    user->SetOnlineState(online_state_logged_in);
    user->SetIP(req->ip);
    user->SetHardware(req->hwid);
    user->SetChannel(req->channel);
    if (req->isSaveProhibit) {
        user->SetProhibitChat(req->isProhibitChat);
    }
    if (req->isSaveSupport) {
        user->UpdateSupport(req->isSupport);
    }
    user->StartSyncRoleInfoTimer();

    user->SendGetRebateReqToPlatform(User::PlatformRebateReq(user->GetID(), user->GetUserName()));
    SendDBLogData(log_type_login_out, LogLoginOut(Utility::UInt2IpStr(req->ip), std::string(req->hwid), user->GetID(), log_loginout_login));
}

void SessionCS2LS::HandleGateServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_GS_LOGOUT_REQ, HandleGateServMsg_LogoutReq)
        HANDLE_MSG(PROTO_GS_UPDATE_ONLINE_STATE, HandleGateServMsg_UpdateOnlineState)
    END_MSG_HANDLER()
}

void SessionCS2LS::HandleGateServMsg_LogoutReq(void* pData)
{
    auto req = (ProtoGS_LogoutReq*)pData;
    auto user = UserMgr::GetInstance()->FindUser(req->token);
    if (nullptr == user) {
        return;
    }
     
    user->SetOnlineState(online_state_not_logged_in);
    user->UpdateOnlineStateToDB(online_state_not_logged_in);
    user->StopSyncRoleInfoTimer();
   
    SendDataBySessionType(SESSION_TYPE_CS2MS, *req);

    SendDBLogData(log_type_login_out, LogLoginOut(Utility::UInt2IpStr(user->GetIP()), user->GetHardware(), user->GetID(), log_loginout_logout));
}

void SessionCS2LS::HandleGateServMsg_UpdateOnlineState(void *pData)
{
    const auto *msg = static_cast<ProtoGS_UpdateOnlineState *>(pData);

    auto *user = UserMgr::GetInstance()->FindUser(msg->token);
    if (!user) return;
    user->SetOnlineState(msg->state);

    SendDataBySessionType(SESSION_TYPE_CS2MS, *msg);
    SendDataBySessionType(SESSION_TYPE_CS2DB, *msg);
}
