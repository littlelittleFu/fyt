#include "stdafx.h"
#include "SessionLS2DB.h"
#include "SessionLS2GS.h"
#include "ILogHelper.h"
#include "ProtoLS.h"
#include "ProtoGS.h"
#include "ProtoDB.h"
#include "SessionContextMgr.h"
#include "CNetManager.h"
#include "SessionFactory.h"
#include "LoginIPManager.h"


SessionLS2DB::SessionLS2DB()
{

}

SessionLS2DB::~SessionLS2DB()
{

}

void SessionLS2DB::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
    GetLoginIpToDBReq();
}

void SessionLS2DB::OnLost()
{
	Session::OnLost();
	LOG_WARN("SessionDB2LS SESSION LOST!");
}

void SessionLS2DB::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    OnHeartBeat();

    switch (moduleid)
    {
        case MODULE_TYPE_LS:
            HandleLoginServMsg(protoid, _pData);
            break;
        case MODULE_TYPE_DB:
            HandleDBServMsg(protoid, _pData);
            break;

        default:
            break;
    }
}

void SessionLS2DB::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("SessionDB2LS ERROR %ld", _ErrorCode);
}

void SessionLS2DB::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionLS2DB::DoHeartBeat()
{
    ProtoLS_HeartBeatReq req;
    SendPkg(&req, sizeof(req));
}

void SessionLS2DB::GetLoginIpToDBReq()
{
    ProtoLS_GetLoginIpReq req;
    SendDataBySessionType(SESSION_TYPE_LS2DB, req);
}

void SessionLS2DB::HandleLoginServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_LS_HEART_BEAT_ACK, HandleLoginServMsg_HeartBeatAck)
        HANDLE_MSG(PROTO_LS_LOGIN_ACK, HandleLoginServMsg_LoginAck)
    END_MSG_HANDLER()
}

void SessionLS2DB::HandleLoginServMsg_HeartBeatAck(void *pData)
{
    // do nothing
}

void SessionLS2DB::HandleLoginServMsg_LoginAck(void* pData)
{
    ProtoLS_LoginAck* pLoginAck = (ProtoLS_LoginAck*)pData;
    SessionLS2GS* pSessionLS = (SessionLS2GS*)CNetManager::GetInstance()->GetSessionByID(pLoginAck->gssessid);
    if (!pSessionLS) {
        return;
    }

    pSessionLS->HandleDBServMsg_LoginAck(pLoginAck);
}

void SessionLS2DB::HandleDBServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_DB_GET_LOGIN_IP_ACK, HandleDBServMsg_LoginIpAck)
        HANDLE_MSG(PROTO_DB_SYNC_LOGIN_TYPE_TO_LS, HandleDBServMsg_SyncLoginTypeInfo)
    END_MSG_HANDLER()
}

void SessionLS2DB::HandleDBServMsg_LoginIpAck(void* pData)
{
    ProtoDB_GetLoginIpAck* ack = (ProtoDB_GetLoginIpAck*)pData;
    LoginIPManager::GetInstance()->InitLoginIpDataFromDB(ack->num, ack->infos);
}

void SessionLS2DB::HandleDBServMsg_SyncLoginTypeInfo(void* pData)
{
    ProtoDB_SyncLoginTypeToLS* ack = (ProtoDB_SyncLoginTypeToLS*)pData;
    LoginIPManager::GetInstance()->SyncLoginIpInfoFromDB(ack);
    for (int i = 0; i < ack->num; ++i)
    {
        if ((ack->opt_type == ProtoDB_SyncLoginTypeToLS::add) && (ack->infos[i].type == login_ip_type_black))
        {
            std::vector<SPSessionContext>vec;
            SessionContextMgr::GetInstance()->GetSessionInfoByIP(vec, ack->infos[i].ip);
            if (!vec.empty())
            {
                for (auto it = vec.begin(); it != vec.end(); ++it)
                {
                    if (nullptr == *it)continue;
                    ProtoGS_LogoutReq pLogoutReq;
                    pLogoutReq.sessionid = it->get()->nClientSessionID;
                    pLogoutReq.token = it->get()->nToken;
                    pLogoutReq.info = E_EXIT_EXITGS;

                    it->get()->nOnlineState = online_state_not_logged_in;
                    it->get()->nClientSessionID = 0;
                    it->get()->nGateServSessionID = 0;
                    SendDataBySessionType(SESSION_TYPE_LS2CS, pLogoutReq);
                }
            }
        }
    }
}
