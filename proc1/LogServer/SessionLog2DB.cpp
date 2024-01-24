#include "stdafx.h"
#include "SessionLog2DB.h"
#include "LogManager.h"
#include "ProtoDB.h"
#include "ProtoLog.h"

SessionLog2DB::SessionLog2DB()
{

}

SessionLog2DB::~SessionLog2DB()
{

}

void SessionLog2DB::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());

	//UploadConfigToServiceServer();
}

void SessionLog2DB::OnLost()
{
	LOG_NORMAL("OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionLog2DB::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
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

void SessionLog2DB::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionLog2DB::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionLog2DB::DoHeartBeat()
{
}

void SessionLog2DB::HandleLogMsg(uint16_t protoid, void* pData)
{
	BEGIN_MSG_HANDLER()
		HANDLE_MSG(PROTO_LOG_HEART_BEAT_REQ, HandleLogMsg_HeartBeatReq)
		HANDLE_MSG(PROTO_LOG_LOGGING_REQ, HandleLogMsg_LoggingReq)
	END_MSG_HANDLER()
}

void SessionLog2DB::HandleLogMsg_HeartBeatReq(void* pData)
{
	ProtoLog_HeartBeatAck ack;
	SendPkg(&ack, sizeof(ack));
}

void SessionLog2DB::HandleLogMsg_LoggingReq(void* pData)
{
	auto req = static_cast<ProtoLog_LoggingReq*>(pData);
	std::string ip = GetRemoteIp();
	strcpy_s(req->serverIp, ip);
	req->serverPort = GetRemotePort();
	req->serverType = MODULE_TYPE_DB;
	CLogManager::GetInstance()->Logging(*req);
}