#include "stdafx.h"
#include "SessionLOG2MS.h"
#include "LogManager.h"
#include "ProtoMS.h"
#include "ProtoLog.h"
#include "LogServer.h"

SessionLog2MS::SessionLog2MS()
{

}

SessionLog2MS::~SessionLog2MS()
{

}

void SessionLog2MS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());

	//UploadConfigToServiceServer();
}

void SessionLog2MS::OnLost()
{
	LOG_NORMAL("OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionLog2MS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    OnHeartBeat();

    switch (moduleid) {
    case MODULE_TYPE_LOG:
        HandleLogMsg(protoid, _pData);
        break;
    case MODULE_TYPE_MS:
        HandleMapMsg(protoid, _pData);
        break;
    default:
        LOG_WARN("Unhandled moduleid: %u", moduleid);
        break;
    }
}

void SessionLog2MS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionLog2MS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionLog2MS::DoHeartBeat()
{
}

void SessionLog2MS::HandleLogMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_LOG_HEART_BEAT_REQ, HandleLogMsg_HeartBeatReq)
        HANDLE_MSG(PROTO_LOG_LOGGING_REQ, HandleLogMsg_LoggingReq)
    END_MSG_HANDLER()
}

void SessionLog2MS::HandleLogMsg_HeartBeatReq(void* pData)
{
    ProtoLog_HeartBeatAck ack;
    SendPkg(&ack, sizeof(ack));
}

void SessionLog2MS::HandleLogMsg_LoggingReq(void* pData)
{
    auto req = static_cast<ProtoLog_LoggingReq*>(pData);
    std::string ip = GetRemoteIp();
    strcpy_s(req->serverIp, ip);
    req->serverPort = GetRemotePort();
    req->serverType = MODULE_TYPE_MS;
    CLogManager::GetInstance()->Logging(*req);
}

void SessionLog2MS::HandleMapMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_MS_SET_SERVER_STATUS, HandleMapMsg_SetServerStatus)
        END_MSG_HANDLER()
}

void SessionLog2MS::HandleMapMsg_SetServerStatus(void* pData)
{
    auto req = static_cast<ProtoMS_SetServerStatus*>(pData);
    if (req->status == server_status_close)
    {
        LogServer::GetInstance()->Quit();
    }
}
