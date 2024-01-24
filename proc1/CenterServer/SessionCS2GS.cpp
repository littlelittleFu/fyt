#include "stdafx.h"
#include "SessionCS2GS.h"
#include "ILogHelper.h"
#include "ProtoMS.h"
#include "ProtoClient.h"
#include "CNetManager.h"
#include <string>
#include "ProtoCS.h"
#include "AssignMapServer.h"
#include "ProtoGS.h"

#include <SessionFactory.h>

#include "UserMgr.h"
#include "TopList.h"

SessionCS2GS::SessionCS2GS()
{

}

SessionCS2GS::~SessionCS2GS()
{

}

void SessionCS2GS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
	LOG_NORMAL("OnEstablish.================ GetID=%d ", GetID());

	ProtoGS_SessionIDNtf ntf;
	ntf.protocolid = PROTO_SESSION_CS2GS_NTF;
	ntf.sessionid = GetID();
	SendPkg(&ntf, sizeof(ntf));
}

void SessionCS2GS::OnLost()
{
	LOG_NORMAL("OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
	//DoClose();
}

void SessionCS2GS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    MsgCostStat::GetInstance()->BeginHandleMsg();

    OnHeartBeat();

	switch (moduleid) {
		case MODULE_TYPE_GS:
			HandleGateServerMsg(protoid, _pData);
			break;
		default:
			LOG_WARN("Default SessionCS::OnMessage server moduleid: %d", moduleid);
			break;
	}

    MsgCostStat::GetInstance()->EndHandleMsg(moduleid, protoid);
}

void SessionCS2GS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionCS2GS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionCS2GS::DoHeartBeat()
{

}

void SessionCS2GS::HandleGateServerMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_GS_HEART_BEAT_REQ, HandleGateServerMsg_HeartBeatReq)
        HANDLE_MSG(PROTO_GS_ENTER_GS_REQ, HandleGateServerMsg_ClientEnterGSReq)
        HANDLE_MSG(PROTO_GS_GET_ROLE_LIST_REQ, HandleGateServerMsg_GetRoleListReq)
        HANDLE_MSG(PROTO_GS_CREATE_ROLE_REQ, HandleGateServerMsg_CreateRoleReq)
        HANDLE_MSG(PROTO_GS_DELETE_ROLE_REQ, HandleGateServerMsg_DeleteRoleReq)
		HANDLE_MSG(PROTO_GS_RESTORE_ROLE_REQ, HandleGateServerMsg_RestoreRoleReq)
        HANDLE_MSG(PROTO_GS_TOPLIST_REQ, HandleGateServerMsg_TopListReq)
		HANDLE_MSG(PROTO_GS_GM_COMMAND_REQ, HandleGateServerMsg_GMCommandReq)
    END_MSG_HANDLER()
}

void SessionCS2GS::HandleGateServerMsg_TopListReq(void* pData)
{
	auto* req = (ProtoGS_TopListReq*)pData;
	TopList::GetInstance()->SendTopList(req);
}

void SessionCS2GS::HandleGateServerMsg_HeartBeatReq(void* pData)
{
	ProtoGS_HeartBeatAck ack;
	SendPkg(&ack, sizeof(ack));
}

void SessionCS2GS::HandleGateServerMsg_ClientEnterGSReq(void* pData)
{
	ProtoGS_EnterGSReq* req = (ProtoGS_EnterGSReq*)pData;
	auto user = UserMgr::GetInstance()->FindUser(req->token);
	if (nullptr == user) {
		LOG_ERROR("user is NULL. playerid: %" PRIu64, req->playerid);
		return;
	}

	auto& roleDataMap = user->GetRoleDataMap();
	auto iter = roleDataMap.find(req->roleBriefInfo.guid);
	if (iter == roleDataMap.end()) {
		LOG_ERROR("can't find role data. playerid: %" PRIu64 " roleid: %" PRIu64, req->playerid, req->roleBriefInfo.guid);
		return;
	}
	user->SetGS2CLSessionID(req->sessionid);
	user->SetMS2GSSessionID(req->MS2GSSessionID);
	user->SetEnterType(req->entertype);
	user->SetClientType(req->clienttype);
	user->SetFangChenMi(req->fangchenmi);
    user->SetLastSelectRole(req->roleBriefInfo.guid);

	if (iter->second.IsInitialized()) {
		user->OnEnterMapReq(req->roleBriefInfo.guid);
		return;
	}

	ProtoCS_GetRoleDataReq roleDataReq;
	roleDataReq.token = req->token;
	roleDataReq.playerid = req->playerid;
	roleDataReq.roleid = req->roleBriefInfo.guid;
	SendDataBySessionType(SESSION_TYPE_CS2DB, roleDataReq);
}

void SessionCS2GS::HandleGateServerMsg_GetRoleListReq(void* pData)
{
	ProtoGS_GetRoleListReq* pGetRoleListReq = (ProtoGS_GetRoleListReq*)pData;//ProtoCS_GetRoleListReq

	auto user = UserMgr::GetInstance()->FindUser(pGetRoleListReq->playerid);
	if (!user || user->GetToken() != pGetRoleListReq->token) {
		SendGetRoleListAckToGS(pGetRoleListReq->sessionid, pGetRoleListReq->token, pGetRoleListReq->playerid,
			ERR_NOUSERDATA, EMSG_NO_USER_DATA);
		return;
	}

	if (online_state_not_logged_in == user->GetOnlineState()) {
		SendGetRoleListAckToGS(pGetRoleListReq->sessionid, pGetRoleListReq->token, pGetRoleListReq->playerid,
			ERR_NOUSERDATA, EMSG_NOT_LOGGED_IN);
		return;
	}

	user->SetCS2GSSessionID(GetID());
	user->SetGS2CLSessionID(pGetRoleListReq->sessionid);
	if (!SendDataBySessionType(SESSION_TYPE_CS2DB, *pGetRoleListReq)) {
		SendGetRoleListAckToGS(pGetRoleListReq->sessionid, pGetRoleListReq->token, pGetRoleListReq->playerid,
			ERR_SYSTEM, EMSG_CS2DB_CONN_ERROR);
	}


}

void SessionCS2GS::HandleGateServerMsg_CreateRoleReq(void* pData)
{
	ProtoGS_CreateRoleReq* req = (ProtoGS_CreateRoleReq*)pData;

	auto user = UserMgr::GetInstance()->FindUser(req->playerid);
	if (!user) {
		LOG_ERROR("user is NULL. playerid: %" PRIu64, req->playerid);
		SendCreateRoleAckToGS(req->sessionid, req->token, req->playerid, ERR_NOUSERDATA, EMSG_NO_USER_DATA);
		return;
	}

	if (online_state_not_logged_in == user->GetOnlineState()) {
		LOG_ERROR("User not logged in. playerid: %" PRIu64, req->playerid);
		SendCreateRoleAckToGS(req->sessionid, req->token, req->playerid, ERR_NOUSERDATA, EMSG_NOT_LOGGED_IN);
		return;
	}

	// 获取是否需要校验
	auto& map = ConfigInfo::GetInstance()->m_constantCfgMap;
	uint8_t needCode = 0;
	auto iter = map.find(CONSTANT_CREATE_ROLE_NEED_CODE);
	if (iter != map.end()) needCode = atoi(iter->second.value.c_str());
	req->needCode = needCode;

	if (!SendDataBySessionType(SESSION_TYPE_CS2DB, *req)) {
		SendCreateRoleAckToGS(req->sessionid, req->token, req->playerid, ERR_SYSTEM, EMSG_CS2DB_CONN_ERROR);
	}
}

void SessionCS2GS::HandleGateServerMsg_DeleteRoleReq(void* pData)
{
	auto req = (ProtoGS_DeleteRoleReq*)pData;

	auto user = UserMgr::GetInstance()->FindUser(req->playerid);
	//K auto spSessionContext = SessionContextMgr::GetInstance()->GetSessionContext(pGetRoleListReq->token);

	if (!user) {
		LOG_ERROR("user is NULL. playerid: %" PRIu64, req->playerid);
		SendDeleteRoleAckToGS(req->sessionid, req->token, req->playerid, req->roleid, ERR_NOUSERDATA, EMSG_NO_USER_DATA);
		return;
	}

	auto& info = user->GetRoleBirefInfo(req->roleid);
	if (!info.guid) {
		LOG_ERROR("role is NULL. role: %" PRIu64, req->roleid);
		SendDeleteRoleAckToGS(req->sessionid, req->token, req->playerid, req->roleid, ERR_NOUSERDATA, EMSG_NO_USER_DATA);
		return;
	}
	if (online_state_not_logged_in == user->GetOnlineState()) {
		LOG_ERROR("User not logged in. playerid: %" PRIu64, req->playerid);
		SendDeleteRoleAckToGS(req->sessionid, req->token, req->playerid, req->roleid,
			ERR_NOUSERDATA, EMSG_NOT_LOGGED_IN);
		return;
	}

	user->SyncUserData();
	TradeData::GetInstance()->HandleAllDelegateCancel(req->roleid);

	if (info.status == role_status_new)
		req->status = role_status_new_deleted;
	else if (info.status == role_status_normal)
		req->status = role_status_deleted;
	else if (info.status == role_status_new_deleted || info.status == role_status_deleted)
		req->status = role_status_permanent_deleted;

	if (!SendDataBySessionType(SESSION_TYPE_CS2DB, *req)) {
		SendDeleteRoleAckToGS(req->sessionid, req->token, req->playerid, req->roleid, ERR_SYSTEM, EMSG_CS2DB_CONN_ERROR);
	}
}

void SessionCS2GS::HandleGateServerMsg_RestoreRoleReq(void* pData)
{
	auto req = (ProtoGS_RestoreRoleReq*)pData;

	auto user = UserMgr::GetInstance()->FindUser(req->playerid);
	//K auto spSessionContext = SessionContextMgr::GetInstance()->GetSessionContext(pGetRoleListReq->token);

	if (!user) {
		LOG_ERROR("user is NULL. playerid: %" PRIu64, req->playerid);
		SendRestoreRoleAckToGS(req->sessionid, req->token, req->playerid, req->roleid, ERR_NOUSERDATA, EMSG_NO_USER_DATA);
		return;
	}

	auto& info = user->GetRoleBirefInfo(req->roleid);
	if (!info.guid) {
		LOG_ERROR("role is NULL. role: %" PRIu64, req->roleid);
		SendRestoreRoleAckToGS(req->sessionid, req->token, req->playerid, req->roleid, ERR_NOUSERDATA, EMSG_NO_USER_DATA);
		return;
	}
	if (online_state_not_logged_in == user->GetOnlineState()) {
		LOG_ERROR("User not logged in. playerid: %" PRIu64, req->playerid);
		SendRestoreRoleAckToGS(req->sessionid, req->token, req->playerid, req->roleid,
			ERR_NOUSERDATA, EMSG_NOT_LOGGED_IN);
		return;
	}

	if (info.status == role_status_deleted)
		req->status = role_status_normal;
	else if (info.status == role_status_new_deleted)
		req->status = role_status_new;
	else if (info.status == role_status_permanent_deleted)
		req->status = role_status_permanent_deleted;

	if (!SendDataBySessionType(SESSION_TYPE_CS2DB, *req)) {
		SendRestoreRoleAckToGS(req->sessionid, req->token, req->playerid, req->roleid, ERR_SYSTEM, EMSG_CS2DB_CONN_ERROR);
	}
}

void SessionCS2GS::SendGetRoleListAckToGS(const uint32_t& sessionid, const uint32_t& token,
	const uint64_t& playerid, const int32_t errcode, const char* errmsg)
{
	auto& getRoleListAck = gProtoGS_GetRoleListAck;
	getRoleListAck.sessionid = sessionid;
	getRoleListAck.token = token;
	getRoleListAck.playerid = playerid;
	getRoleListAck.errcode = errcode;
	strcpy_s(getRoleListAck.errmsg, _countof(getRoleListAck.errmsg), errmsg);
	SendPkg(&getRoleListAck, sizeof(getRoleListAck));
}

void SessionCS2GS::SendCreateRoleAckToGS(const uint32_t& sessionid, const uint32_t& token,
	const uint64_t& playerid, const int32_t errcode, const char* errmsg)
{
	ProtoGS_CreateRoleAck createRoleAck;
	createRoleAck.sessionid = sessionid;
	createRoleAck.token = token;
	createRoleAck.playerid = playerid;
	createRoleAck.errcode = errcode;
	strcpy_s(createRoleAck.errmsg, _countof(createRoleAck.errmsg), errmsg);
	SendPkg(&createRoleAck, sizeof(createRoleAck));
}

void SessionCS2GS::SendDeleteRoleAckToGS(const uint32_t& sessionid, const uint32_t& token,
	const uint64_t& playerid, const uint64_t& roleid, const int32_t errcode, const char* errmsg)
{
	ProtoGS_DeleteRoleAck deleteRoleAck;
	deleteRoleAck.sessionid = sessionid;
	deleteRoleAck.token = token;
	deleteRoleAck.playerid = playerid;
	deleteRoleAck.roleid = roleid;
	deleteRoleAck.errcode = errcode;
	strcpy_s(deleteRoleAck.errmsg, _countof(deleteRoleAck.errmsg), errmsg);
	SendPkg(&deleteRoleAck, sizeof(deleteRoleAck));
}

void SessionCS2GS::SendRestoreRoleAckToGS(const uint32_t& sessionid, const uint32_t& token, const uint64_t& playerid, const uint64_t& roleid, const int32_t errcode, const char* errmsg)
{
	ProtoGS_RestoreRoleAck restoreRoleAck;
	restoreRoleAck.sessionid = sessionid;
	restoreRoleAck.token = token;
	restoreRoleAck.playerid = playerid;
	restoreRoleAck.roleid = roleid;
	restoreRoleAck.errcode = errcode;
	strcpy_s(restoreRoleAck.errmsg, _countof(restoreRoleAck.errmsg), errmsg);
	SendPkg(&restoreRoleAck, sizeof(restoreRoleAck));
}

void SessionCS2GS::HandleGateServerMsg_GMCommandReq(void* pData)
{
	auto req = (ProtoGS_GMCommandReq*)pData;
    LOG_NORMAL("[GM] GMCommandReq sn: %d, cmd: %s, param: %s", req->sn, req->cmd, req->param);

	auto user = UserMgr::GetInstance()->FindUser(req->token);
	if (nullptr == user) {
		LOG_ERROR("[GM] user is NULL. playerid: %" PRIu64, req->role_id);

		ProtoGS_KickOutByLock kick;
		kick.info = E_EXIT_EXITGS;
		kick.sessionid = req->sessionid;
		kick.token = req->token;
		SendPkg(&kick, sizeof(kick));
		return;
	}
	string name;
	MSG_BUFFER_DATA(ProtoCS_RunGmCmdAck, data);
	user->IsHavingGmMod(std::string(req->cmd),name,data.result);
    data.sn = req->sn;
	strcpy_s(data.cmd, _countof(data.cmd), req->cmd);
	strcpy_s(data.param, _countof(data.param), req->param);
	strcpy_s(data.playername, _countof(data.playername), name.c_str());
	data.token = req->token;
	SendDataBySessionType(SESSION_TYPE_CS2MS, data);
    LOG_NORMAL("[GM] RunGmCmdAck result: %d", data.result);
}