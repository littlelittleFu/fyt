#include "stdafx.h"
#include "SessionLOG2CS.h"
#include "LogManager.h"
#include "ProtoCS.h"
#include "ProtoLog.h"

SessionLog2CS::SessionLog2CS()
{

}

SessionLog2CS::~SessionLog2CS()
{

}

void SessionLog2CS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionLog2CS::OnLost()
{
	LOG_NORMAL("OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
	//DoClose();
}

void SessionLog2CS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    MsgCostStat::GetInstance()->BeginHandleMsg();

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

void SessionLog2CS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionLog2CS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}
// server不主动向client发心跳包
void SessionLog2CS::DoHeartBeat()
{

}

void SessionLog2CS::HandleLogMsg(uint16_t protoid, void* pData)
{
	BEGIN_MSG_HANDLER()
		HANDLE_MSG(PROTO_LOG_HEART_BEAT_REQ, HandleLogMsg_HeartBeatReq)
		HANDLE_MSG(PROTO_LOG_LOGGING_REQ, HandleLogMsg_LoggingReq)
	END_MSG_HANDLER()
}

void SessionLog2CS::HandleLogMsg_HeartBeatReq(void* pData)
{
	ProtoLog_HeartBeatAck ack;
	SendPkg(&ack, sizeof(ack));
}

void SessionLog2CS::HandleLogMsg_LoggingReq(void* pData)
{
	auto req = static_cast<ProtoLog_LoggingReq*>(pData);
	std::string ip = GetRemoteIp();
	strcpy_s(req->serverIp, ip);
	req->serverPort = GetRemotePort();
	req->serverType = MODULE_TYPE_CS;
	CLogManager::GetInstance()->Logging(*req);
}