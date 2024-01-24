#include "stdafx.h"
#include "SessionLog2GS.h"
#include "LogManager.h"
#include "ProtoGS.h"
#include "ProtoLog.h"

SessionLog2GS::SessionLog2GS()
{

}

SessionLog2GS::~SessionLog2GS()
{

}

void SessionLog2GS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());

	//UploadConfigToServiceServer();
}

void SessionLog2GS::OnLost()
{
	LOG_NORMAL("OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionLog2GS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    OnHeartBeat();

    switch (moduleid) {
    case MODULE_TYPE_LOG:
        HandleLogMsg(protoid, _pData);
        break;

    default:
        LOG_WARN("Unhandled moduleid: %u", moduleid);
        break;
    }
}

void SessionLog2GS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionLog2GS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionLog2GS::DoHeartBeat()
{
}

void SessionLog2GS::HandleLogMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_LOG_HEART_BEAT_REQ, HandleLogMsg_HeartBeatReq)
        HANDLE_MSG(PROTO_LOG_LOGGING_REQ, HandleLogMsg_LoggingReq)
    END_MSG_HANDLER()
}

void SessionLog2GS::HandleLogMsg_HeartBeatReq(void* pData)
{
    ProtoLog_HeartBeatAck ack;
    SendPkg(&ack, sizeof(ack));
}

void SessionLog2GS::HandleLogMsg_LoggingReq(void* pData)
{
    auto req = static_cast<ProtoLog_LoggingReq*>(pData);
    std::string ip = GetRemoteIp();
    strcpy_s(req->serverIp, ip);
    req->serverPort = GetRemotePort();
    req->serverType = MODULE_TYPE_GS;
    CLogManager::GetInstance()->Logging(*req);
}