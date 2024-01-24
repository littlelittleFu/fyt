#include "stdafx.h"
#include "SessionDB2Log.h"
#include "ILogHelper.h"
#include "ProtoLog.h"
#include "ProtoDB.h"

SessionDB2Log::SessionDB2Log()
{

}

SessionDB2Log::~SessionDB2Log()
{

}

void SessionDB2Log::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionDB2Log::OnLost()
{
	LOG_NORMAL("OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
	//DoClose();
}

void SessionDB2Log::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
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

void SessionDB2Log::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionDB2Log::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}
// client发起心跳包
void SessionDB2Log::DoHeartBeat()
{
	ProtoLog_HeartBeatReq req;
	SendPkg(&req, sizeof(req));
}

void SessionDB2Log::HandleLogMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_LOG_HEART_BEAT_ACK, HandleLogMsg_HeartBeatAck)
    END_MSG_HANDLER()
}

void SessionDB2Log::HandleLogMsg_HeartBeatAck(void* pData)
{
}
