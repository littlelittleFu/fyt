#pragma once
#include "Session.h"

class SessionLog2DB : public Session
{
public:
	SessionLog2DB();
	~SessionLog2DB();

	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual void DoHeartBeat();

private:
	void HandleLogMsg(uint16_t protoid, void* pData);
	void HandleLogMsg_LoggingReq(void* pData);
	void HandleLogMsg_HeartBeatReq(void* pData);
};
