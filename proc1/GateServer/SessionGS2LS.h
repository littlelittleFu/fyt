#pragma once
#include "Session.h"

class SessionGS2LS : public Session
{
public:
	SessionGS2LS();
	~SessionGS2LS();

	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual void DoHeartBeat();

private:
	void HandleGateServMsg(uint16_t protoid, void* pData);
	void HandleGateServMsg_SessionIDNtf(void* pData);
    void HandleGateServMsg_HeartBeatAck(void *pData);
	void HandleGateServMsg_LoginAck(void* pData);
	void HandleGateServMsg_KickRoleNtf(void* pData);
	void HandleGateServMsg_ReloginAck(void* pData);
	void HandleGateServMsg_KickOutPlayer(void* pData);

    void HandleLoginServMsg(uint16_t protoid, void* pData);
    void HandleLoginServMsg_LogoutNtf(void* pData);
    void HandleLoginServMsg_RemoveContext(void *pData);
};
