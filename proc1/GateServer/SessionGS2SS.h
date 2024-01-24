#pragma once
#include "Session.h"

class ProtoGS;

class SessionGS2SS : public Session
{
public:
	SessionGS2SS();
	~SessionGS2SS();

	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual void DoHeartBeat();

private:
    void RequestServerConfig();
    bool HasGetConfigFromSS();

    void HandleConfigAck(void *pData);
};
