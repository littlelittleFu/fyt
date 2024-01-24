#pragma once
#include "Session.h"



class SessionGS2CS : public Session
{
public:
	SessionGS2CS();
	~SessionGS2CS();

	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual void DoHeartBeat();

	void HandleCSRspMsg(uint16_t protoid, void* _pData);
	void HandleCSRspMsg_HeartBeatAck(void *pData);
	void HandleCSRspMsg_SessionIDNtf(void* pData);
    void HandleCSRspMsg_GetRoleListAck(void *pData);
    void HandleCSRspMsg_CreateRoleAck(void* pData);
    void HandleCSRspMsg_DeleteRoleAck(void* pData);
	void HandleCSRspMsg_RestoreRoleAck(void* pData);
	void HandleCSRspMsg_TopListAck(void* pData);
	void HandleCSRspMsg_KickOutPlayer(void* pData);

    void HandleMapServMsg(uint16_t protoid, void *pData);
};
