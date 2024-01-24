#pragma once

#include "Session.h"

class SessionLS2SS : public Session
{
public:
	SessionLS2SS();
	~SessionLS2SS();

	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual void DoHeartBeat();

private:
    void UploadConfigToServiceServer();
    void RequestServerConfig();
    bool HasGetConfigFromSS();

    void HandleConfigAck(void *pData);
};
