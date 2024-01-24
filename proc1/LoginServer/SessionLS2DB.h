#pragma once
#include "Session.h"

class SessionLS2DB : public Session
{
public:
	SessionLS2DB();
	~SessionLS2DB();

	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual void DoHeartBeat();


	void GetLoginIpToDBReq();
private:
    void HandleLoginServMsg(uint16_t protoid, void* pData);
	void HandleLoginServMsg_HeartBeatAck(void *pData);
    void HandleLoginServMsg_LoginAck(void* pData);

	void HandleDBServMsg(uint16_t protoid, void* pData);
	void HandleDBServMsg_LoginIpAck(void* pData);
	void HandleDBServMsg_SyncLoginTypeInfo(void* pData);
};
