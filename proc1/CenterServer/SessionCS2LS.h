#pragma once
#include "Session.h"
class SessionCS2LS : public Session
{
public:
	SessionCS2LS();
	~SessionCS2LS();

	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual void DoHeartBeat();

	void HandleLoginServMsg(uint16_t protoid, void* pData);
    void HandleLoginServMsg_HeartBeatReq(void *pData);
	void HandleLoginServMsg_SaveLoginReq(void* pData);
    void HandleGateServMsg(uint16_t protoid, void* pData);
	void HandleGateServMsg_LogoutReq(void* pData);
    void HandleGateServMsg_UpdateOnlineState(void *pData);

	std::string mScriptName;
protected:

	
	
};
