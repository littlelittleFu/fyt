#pragma once
#include "Session.h"
struct ROLE_BRIEF_INFO;
class SessionCS2GS : public Session
{
public:
	SessionCS2GS();
	~SessionCS2GS();

	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual void DoHeartBeat();

	std::string mScriptName;
protected:
	void SendGetRoleListAckToGS(const uint32_t& sessionid, const uint32_t& token, const uint64_t& playerid,
		const int32_t errcode, const char* errmsg);
	void SendCreateRoleAckToGS(const uint32_t& sessionid, const uint32_t& token, const uint64_t& playerid,
		const int32_t errcode, const char* errmsg);
	void SendDeleteRoleAckToGS(const uint32_t& sessionid, const uint32_t& token, const uint64_t& playerid,
		const uint64_t& roleid, const int32_t errcode, const char* errmsg);
	void SendRestoreRoleAckToGS(const uint32_t& sessionid, const uint32_t& token, const uint64_t& playerid,
		const uint64_t& roleid, const int32_t errcode, const char* errmsg);
	void HandleGateServerMsg(uint16_t protoid, void* pData);
    void HandleGateServerMsg_HeartBeatReq(void* pData);
	void HandleGateServerMsg_ClientEnterGSReq(void* pData);
	void HandleGateServerMsg_GetRoleListReq(void* pData);
	void HandleGateServerMsg_CreateRoleReq(void* pData);
	void HandleGateServerMsg_DeleteRoleReq(void* pData);
	void HandleGateServerMsg_RestoreRoleReq(void* pData);
	void HandleGateServerMsg_TopListReq(void* pData);
	void HandleGateServerMsg_GMCommandReq(void* pData);
};
