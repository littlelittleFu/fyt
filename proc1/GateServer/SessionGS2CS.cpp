#include "stdafx.h"
#include "SessionGS2CS.h"
#include "SessionGS2CL.h"
#include "ILogHelper.h"
#include "ProtoGS.h"
#include "ProtoMS.h"
#include "ProtoClient.h"
#include "ProtoClient3.h"
#include "CNetManager.h"
#include "SessionFactory.h"
#include "SessionContextMgr.h"



SessionGS2CS::SessionGS2CS()
{

}

SessionGS2CS::~SessionGS2CS()
{

}

void SessionGS2CS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionGS2CS::OnLost()
{
	LOG_NORMAL("OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
	//DoClose();
}

void SessionGS2CS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    MsgCostStat::GetInstance()->BeginHandleMsg();

    OnHeartBeat();

	switch (moduleid) {
		case MODULE_TYPE_GS:
			HandleCSRspMsg(protoid, _pData);
			break;

		case MODULE_TYPE_MS:
			HandleMapServMsg(protoid, _pData);
			break;

		default:
			LOG_WARN("Unhandled moduleid: %u", moduleid);
			break;
	}

    MsgCostStat::GetInstance()->EndHandleMsg(moduleid, protoid);
}

void SessionGS2CS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionGS2CS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionGS2CS::DoHeartBeat()
{
	ProtoGS_HeartBeatReq req;
	SendPkg(&req, sizeof(req));
}

void SessionGS2CS::HandleCSRspMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
		HANDLE_MSG(PROTO_GS_HEART_BEAT_ACK, HandleCSRspMsg_HeartBeatAck)
        HANDLE_MSG(PROTO_SESSION_CS2GS_NTF, HandleCSRspMsg_SessionIDNtf)
        HANDLE_MSG(PROTO_GS_GET_ROLE_LIST_ACK, HandleCSRspMsg_GetRoleListAck)
        HANDLE_MSG(PROTO_GS_CREATE_ROLE_ACK, HandleCSRspMsg_CreateRoleAck)
        HANDLE_MSG(PROTO_GS_DELETE_ROLE_ACK, HandleCSRspMsg_DeleteRoleAck)
		HANDLE_MSG(PROTO_GS_RESTORE_ROLE_ACK, HandleCSRspMsg_RestoreRoleAck)
        HANDLE_MSG(PROTO_GS_TOPLIST_ACK, HandleCSRspMsg_TopListAck)
		HANDLE_MSG(PROTO_GS_KICK_OUT_BY_LOCK, HandleCSRspMsg_KickOutPlayer)
    END_MSG_HANDLER()
}

void SessionGS2CS::HandleCSRspMsg_HeartBeatAck(void *pData)
{
	// do nothing
}

void SessionGS2CS::HandleCSRspMsg_TopListAck(void* pData)
{
	ProtoGS_TopListAck* ack = (ProtoGS_TopListAck*)pData;

	ISession* pSession = CNetManager::GetInstance()->GetSessionByID(ack->sessionid);
	SessionGS2CL* pSessionGS = dynamic_cast<SessionGS2CL*>(pSession);
	if (!pSessionGS) {
		return;
	}

	pSessionGS->OnGetTopListAck(ack);
}

void SessionGS2CS::HandleCSRspMsg_KickOutPlayer(void* pData)
{
	ProtoGS_KickOutByLock* ack = (ProtoGS_KickOutByLock*)pData;

	ProtoClient3_ExitGSAck pAck;

	pAck.exittype = ack->info;
	//pAck.errcode = ack->errcode;
	//strcpy_s(pAck.errmsg, _countof(EMSG_PROHIBIT), EMSG_PROHIBIT);

	ISession* pGateServ = CNetManager::GetInstance()->GetSessionByID(ack->sessionid);
	if (pGateServ) {
		pGateServ->SendPkg(&pAck, sizeof(pAck));
	}

	SendDataBySessionType(SESSION_TYPE_GS2LS, *ack);
}

void SessionGS2CS::HandleCSRspMsg_SessionIDNtf(void* pData)
{
	auto ntf = (ProtoGS_SessionIDNtf*)pData;
	SessionContextMgr::GetInstance()->SetCS2GSSessionID(ntf->sessionid);
}

void SessionGS2CS::HandleCSRspMsg_GetRoleListAck(void* pData)
{
	auto pGetRoleListAck = (ProtoGS_GetRoleListAck*)pData;
	ISession* pSession = CNetManager::GetInstance()->GetSessionByID(pGetRoleListAck->sessionid);
	SessionGS2CL* pSessionGS = dynamic_cast<SessionGS2CL*>(pSession);
	if (!pSessionGS) {
		return;
	}

	pSessionGS->OnGetRoleListAck(pGetRoleListAck);
}

void SessionGS2CS::HandleCSRspMsg_CreateRoleAck(void* pData)
{
	auto pCreateRoleAck = (ProtoGS_CreateRoleAck*)pData;

	ISession* pSession = CNetManager::GetInstance()->GetSessionByID(pCreateRoleAck->sessionid);
	SessionGS2CL* pSessionGS = dynamic_cast<SessionGS2CL*>(pSession);

	if (!pSessionGS) {
		LOG_ERROR("pSessionGS is NULL. sessionid: %u", pCreateRoleAck->sessionid);
		return;
	}

	pSessionGS->OnCreateRoleAck(pCreateRoleAck);
}

void SessionGS2CS::HandleCSRspMsg_DeleteRoleAck(void* pData)
{
	auto pDeleteRoleAck = (ProtoGS_DeleteRoleAck*)pData;

	ISession* pSession = CNetManager::GetInstance()->GetSessionByID(pDeleteRoleAck->sessionid);
	SessionGS2CL* pSessionGS = dynamic_cast<SessionGS2CL*>(pSession);

	if (!pSessionGS) {
		LOG_ERROR("pSessionGS is NULL. sessionid: %u", pDeleteRoleAck->sessionid);
		return;
	}

	pSessionGS->OnDeleteRoleAck(pDeleteRoleAck);
}

void SessionGS2CS::HandleCSRspMsg_RestoreRoleAck(void* pData)
{
	auto pRestoreRoleAck = (ProtoGS_RestoreRoleAck*)pData;

	ISession* pSession = CNetManager::GetInstance()->GetSessionByID(pRestoreRoleAck->sessionid);
	SessionGS2CL* pSessionGS = dynamic_cast<SessionGS2CL*>(pSession);

	if (!pSessionGS) {
		LOG_ERROR("pSessionGS is NULL. sessionid: %u", pRestoreRoleAck->sessionid);
		return;
	}

	pSessionGS->OnRestoreRoleAck(pRestoreRoleAck);
}

void SessionGS2CS::HandleMapServMsg(uint16_t protoid, void* pData)
{
	
}
