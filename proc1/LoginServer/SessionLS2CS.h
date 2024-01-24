#pragma once

#include "Session.h"


class SessionLS2CS : public Session
{
public:
	SessionLS2CS();
	~SessionLS2CS();

	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual void DoHeartBeat();

private:
    void HandleLoginServMsg(uint16_t protoid, void* pData);
	void HandleMapServMsg(uint16_t protoid, void* pData);
    void HandleLoginServMsg_HeartBeatAck(void* pData);
	void HandleLoginServMsg_SetServerStatus(void* pData);
};
