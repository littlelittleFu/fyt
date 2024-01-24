#pragma once
#include "Session.h"

class SessionDB2SS : public Session
{
public:
	SessionDB2SS();
	~SessionDB2SS();

	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual void DoHeartBeat();

private:
    void HandleDBMsg(uint16_t protoid, void* pData);
    void HandleDBMsg_HeartBeatAck(void* pData);
	void HandleDBMsg_ConfigAck(void* pData);

private:
	void UploadConfigToServiceServer();
	void RequestServerConfig();
	bool HasGetConfigFromSS();
};
