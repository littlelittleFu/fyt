#include "stdafx.h"
#include "SessionGS2Log.h"
#include "ILogHelper.h"
#include "ProtoLog.h"
#include "ProtoGS.h"

SessionGS2Log::SessionGS2Log()
{

}

SessionGS2Log::~SessionGS2Log()
{

}

void SessionGS2Log::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionGS2Log::OnLost()
{
	LOG_NORMAL("OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
	//DoClose();
}

void SessionGS2Log::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
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

void SessionGS2Log::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionGS2Log::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}
// client发起心跳包
void SessionGS2Log::DoHeartBeat()
{
	ProtoLog_HeartBeatReq req;
	SendPkg(&req, sizeof(req));
}

void SessionGS2Log::HandleLogMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_LOG_HEART_BEAT_ACK, HandleLogMsg_HeartBeatAck)
    END_MSG_HANDLER()
}

void SessionGS2Log::HandleLogMsg_HeartBeatAck(void* pData)
{
}
