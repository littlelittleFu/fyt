#include "stdafx.h"
#include "SessionLOG2SS.h"
#include "LogManager.h"
#include "ProtoLog.h"

SessionLog2SS::SessionLog2SS()
{

}

SessionLog2SS::~SessionLog2SS()
{

}

void SessionLog2SS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());

	UploadConfigToServiceServer();
}

void SessionLog2SS::OnLost()
{
	LOG_NORMAL("OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionLog2SS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
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

void SessionLog2SS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionLog2SS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionLog2SS::DoHeartBeat()
{
    ProtoLog_HeartBeatReq req;
    SendPkg(&req, sizeof(req));
}

void SessionLog2SS::UploadConfigToServiceServer()
{
	ProtoLog_UploadConfigReq req;
	req.ip = inet_addr(ConfigInfo::GetInstance()->m_sLocalMachineIp.c_str());
	req.port = ConfigInfo::GetInstance()->m_nListenPort;

	SendPkg(&req, sizeof(req));
}

void SessionLog2SS::HandleLogMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_LOG_HEART_BEAT_ACK, HandleLogMsg_HeartBeatAck)
        HANDLE_MSG(PROTO_LOG_LOGGING_REQ, HandleLogMsg_LoggingReq)
    END_MSG_HANDLER()
}


void SessionLog2SS::HandleLogMsg_HeartBeatAck(void* pData)
{

}

void SessionLog2SS::HandleLogMsg_LoggingReq(void* pData)
{
	auto req = static_cast<ProtoLog_LoggingReq*>(pData);
	std::string ip = GetRemoteIp();
	strcpy_s(req->serverIp, ip);
	req->serverPort = GetRemotePort();
	req->serverType = MODULE_TYPE_SS;
	CLogManager::GetInstance()->Logging(*req);
}