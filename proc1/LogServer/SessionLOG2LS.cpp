#include "stdafx.h"
#include "SessionLOG2LS.h"
#include "LogManager.h"
#include "ProtoLS.h"
#include "ProtoLog.h"


SessionLog2LS::SessionLog2LS()
{

}

SessionLog2LS::~SessionLog2LS()
{

}

void SessionLog2LS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionLog2LS::OnLost()
{
	LOG_NORMAL("OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
	//DoClose();
}

void SessionLog2LS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    OnHeartBeat();

    switch (moduleid)
    {
    case MODULE_TYPE_LOG:
        HandleLogMsg(protoid, _pData);
        break;

    default:
        break;
    }
}

void SessionLog2LS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionLog2LS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionLog2LS::DoHeartBeat()
{
	
}

void SessionLog2LS::HandleLogMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_LOG_HEART_BEAT_REQ, HandleLogMsg_HeartBeatReq)
        HANDLE_MSG(PROTO_LOG_LOGGING_REQ, HandleLogMsg_LoggingReq)
    END_MSG_HANDLER()
}

void SessionLog2LS::HandleLogMsg_HeartBeatReq(void* pData)
{
    ProtoLog_HeartBeatAck ack;
    SendPkg(&ack, sizeof(ack));
}

void SessionLog2LS::HandleLogMsg_LoggingReq(void* pData)
{
    auto req = static_cast<ProtoLog_LoggingReq*>(pData);
    std::string ip = GetRemoteIp();
    strcpy_s(req->serverIp, ip);
    req->serverPort = GetRemotePort();
    req->serverType = MODULE_TYPE_LS;
    CLogManager::GetInstance()->Logging(*req);
}