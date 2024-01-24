#include "stdafx.h"
#include "SessionGS2LS.h"
#include "SessionGS2CL.h"
#include "ILogHelper.h"
#include "ProtoGS.h"
#include "ProtoLS.h"
#include "CNetManager.h"
#include "ProtoClient.h"

SessionGS2LS::SessionGS2LS()
{

}

SessionGS2LS::~SessionGS2LS()
{

}

void SessionGS2LS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionGS2LS::OnLost()
{
	LOG_NORMAL("OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
	//DoClose();
}

void SessionGS2LS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    MsgCostStat::GetInstance()->BeginHandleMsg();

    OnHeartBeat();

    switch (moduleid)
    {
        case MODULE_TYPE_GS:
            HandleGateServMsg(protoid, _pData);
            break;

        case MODULE_TYPE_LS:
            HandleLoginServMsg(protoid, _pData);
            break;
        default:
            LOG_WARN("Unhandled moduleid: %d", moduleid);
            break;
    }

    MsgCostStat::GetInstance()->EndHandleMsg(moduleid, protoid);
}

void SessionGS2LS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionGS2LS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionGS2LS::DoHeartBeat()
{
    ProtoGS_HeartBeatReq req;
    SendPkg(&req, sizeof(req));
}

void SessionGS2LS::HandleGateServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_SESSION_LS2GS_NTF, HandleGateServMsg_SessionIDNtf)
        HANDLE_MSG(PROTO_GS_HEART_BEAT_ACK, HandleGateServMsg_HeartBeatAck)
        HANDLE_MSG(PROTO_GS_LOGIN_ACK, HandleGateServMsg_LoginAck)
        HANDLE_MSG(PROTO_GS_KICK_ROLE_NTF, HandleGateServMsg_KickRoleNtf)
        HANDLE_MSG(PROTO_GS_RELOGIN_ACK, HandleGateServMsg_ReloginAck)
    END_MSG_HANDLER()
}

void SessionGS2LS::HandleGateServMsg_SessionIDNtf(void* pData)
{
    auto ntf = (ProtoGS_SessionIDNtf*)pData;
    SessionContextMgr::GetInstance()->SetLS2GSSessionID(ntf->sessionid);
}

void SessionGS2LS::HandleGateServMsg_HeartBeatAck(void* pData)
{
    // do nothing
}

void SessionGS2LS::HandleLoginServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_LS_LOGOUT_NTF, HandleLoginServMsg_LogoutNtf)
        HANDLE_MSG(PROTO_LS_REMOVE_CONTEXT, HandleLoginServMsg_RemoveContext)
    END_MSG_HANDLER()
}

void SessionGS2LS::HandleGateServMsg_LoginAck(void* pData)
{
    ProtoGS_LoginAck* pLoginAck = (ProtoGS_LoginAck*)pData;
    ISession* pSession = CNetManager::GetInstance()->GetSessionByID(pLoginAck->clsessid);
    SessionGS2CL* pSessionGS = dynamic_cast<SessionGS2CL*>(pSession);
    if (!pSessionGS) {
        LOG_ERROR("pSessionGS is NULL. sessionid: %d, username: %s", pLoginAck->clsessid, pLoginAck->username);
        return;
    }

    pSessionGS->OnLoginAck(pLoginAck);
}

void SessionGS2LS::HandleGateServMsg_ReloginAck(void* pData)
{
    ProtoGS_ReloginAck* ack = static_cast<ProtoGS_ReloginAck*>(pData);
    ISession* pSession = CNetManager::GetInstance()->GetSessionByID(ack->cl2gs_sessid);
    SessionGS2CL* pSessionGS = dynamic_cast<SessionGS2CL*>(pSession);
    if (!pSessionGS) {
        LOG_ERROR("pSessionGS is NULL. sessionid: %d, username: %s", ack->cl2gs_sessid, ack->username);
        return;
    }

    pSessionGS->OnReloginAck(ack);
}

void SessionGS2LS::HandleLoginServMsg_LogoutNtf(void* pData)
{
    ProtoLS_LogoutNtf* pLogoutNtf = (ProtoLS_LogoutNtf*)pData;

    ISession* pSession = CNetManager::GetInstance()->GetSessionByID(pLogoutNtf->sessionid);
    SessionGS2CL* pSessionGS = dynamic_cast<SessionGS2CL*>(pSession);
    if (!pSessionGS)
    {
        LOG_ERROR("pSessionGS is NULL. sessionid: %d, username: %s", pLogoutNtf->sessionid, pLogoutNtf->username);
        return;
    }

    pSessionGS->OnLogoutNtf(pLogoutNtf);
}

void SessionGS2LS::HandleGateServMsg_KickRoleNtf(void* pData)
{
    ProtoGS_KickRoleNtf* ntf = (ProtoGS_KickRoleNtf*)pData;
    
    ISession* pSession = CNetManager::GetInstance()->GetSessionByID(ntf->sessionid);
    SessionGS2CL* pSessionGS = dynamic_cast<SessionGS2CL*>(pSession);
    if (!pSessionGS){
        LOG_ERROR("pSessionGS is NULL. sessionid: %d", ntf->sessionid);
        return;
    }

    pSessionGS->OnKickRoleNtf(ntf);
}

void SessionGS2LS::HandleLoginServMsg_RemoveContext(void *pData)
{
    const auto *msg = static_cast<ProtoLS_RemoveContext *>(pData);

    auto context = SessionContextMgr::GetInstance()->GetSessionContext(msg->sessionid);
    if (!context) return;

    if (context->nReserveContextTimerID) {
        ITimeHelper::GetInstance()->RemoveTimer(context->nReserveContextTimerID);
        context->nReserveContextTimerID = 0;
    }

    // 重连后新gate会删除旧gate中的session 超时后会走OnLost 导致玩家掉线
    context->nOnlineState = online_state_not_logged_in;

           
    SessionContextMgr::GetInstance()->DelSessionContext(msg->sessionid);
}
