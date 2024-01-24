#include "stdafx.h"
#include "SessionCS2Log.h"
#include "ILogHelper.h"
#include "ProtoLog.h"
#include "ProtoCS.h"
#include "UserMgr.h"

SessionCS2Log::SessionCS2Log()
{

}

SessionCS2Log::~SessionCS2Log()
{

}

void SessionCS2Log::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
	UserMgr::GetInstance();
}

void SessionCS2Log::OnLost()
{
	LOG_NORMAL("OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
	//DoClose();
}

void SessionCS2Log::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
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

void SessionCS2Log::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionCS2Log::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}
// client发起心跳包
void SessionCS2Log::DoHeartBeat()
{
	ProtoLog_HeartBeatReq req;
	SendPkg(&req, sizeof(req));
}

void SessionCS2Log::HandleLogMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_LOG_HEART_BEAT_ACK, HandleLogMsg_HeartBeatAck)
    END_MSG_HANDLER()
}

void SessionCS2Log::HandleLogMsg_HeartBeatAck(void* pData)
{
}
