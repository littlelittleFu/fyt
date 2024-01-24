#pragma once
#include "Session.h"

class SessionDB2LS : public Session
{
public:
	SessionDB2LS();
	~SessionDB2LS();

	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual void DoHeartBeat();

private:
    void HandleLoginServMsg(uint16_t protoid, void* pData);
    void HandleLoginServMsg_HeartBeatReq(void *pData);
    void HandleLoginServMsg_LoginReq(void *pData);
    void HandleLoginServMsg_InsertPlayer(void *pData);
	void HandleLoginServMsg_GetLoginIpReq(void* pData);

};
