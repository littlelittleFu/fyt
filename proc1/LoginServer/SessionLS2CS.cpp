#include "stdafx.h"
#include "SessionLS2CS.h"
#include "SessionLS2GS.h"
#include "ILogHelper.h"
#include "ProtoLS.h"
#include "CNetManager.h"
#include "SessionFactory.h"
#include "ProtoGS.h"
#include "ProtoMS.h"
#include "LoginServer.h"




SessionLS2CS::SessionLS2CS()
{

}

SessionLS2CS::~SessionLS2CS()
{

}

void SessionLS2CS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionLS2CS::OnLost()
{
	LOG_NORMAL("OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
	//DoClose();
}

void SessionLS2CS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
	OnHeartBeat();

	switch (moduleid)
	{
		case MODULE_TYPE_LS:
			HandleLoginServMsg(protoid, _pData);
			break;
		case MODULE_TYPE_MS:
			HandleMapServMsg(protoid, _pData);
			break;
		default:
			LOG_WARN("Unhandled moduleid: %d", moduleid);
			break;
	}
}

void SessionLS2CS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionLS2CS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionLS2CS::DoHeartBeat()
{
	ProtoLS_HeartBeatReq req;
	SendPkg(&req, sizeof(req));
}

void SessionLS2CS::HandleLoginServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_LS_HEART_BEAT_ACK, HandleLoginServMsg_HeartBeatAck)
    END_MSG_HANDLER()
}

void SessionLS2CS::HandleMapServMsg(uint16_t protoid, void* pData)
{
	BEGIN_MSG_HANDLER()
		HANDLE_MSG(PROTO_MS_SET_SERVER_STATUS, HandleLoginServMsg_SetServerStatus)
		END_MSG_HANDLER()
}

void SessionLS2CS::HandleLoginServMsg_HeartBeatAck(void* pData)
{
	// do nothing
}

void SessionLS2CS::HandleLoginServMsg_SetServerStatus(void* pData)
{
	auto msg = (ProtoMS_SetServerStatus*)pData;
	if (msg->status == server_status_close)
	{
		LoginServer::GetInstance()->Quit();
	}
}

