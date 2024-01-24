#pragma once
#include "CSocket.h"
class Session : public ISession
{
public:
	Session();
	virtual ~Session();

	virtual INT GetType();
	virtual void SetType(INT _Type);
	virtual INT GetParam();
	virtual void SetParam(INT _Param);
    virtual void SetEncrypt(bool _Encrypt);
	virtual UINT GetID();
	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void HandleMessage(void* _pData, UINT _Len);
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual bool SendPkg(void* _pData, UINT _Len, bool candrop = false);
	virtual bool IsInvalid();
	virtual void SetInvalid(bool _Value);
	virtual void DoClose();
	virtual void SetIpInfo(std::string& _LocalIp, UINT _LocalPort, std::string& _RemoteIp, UINT _RemotePort);
	virtual void DoHeartBeat();
	virtual void LogDebugInfo(DEBUG_DATA& debugData);
    virtual bool CanBeDestroyed(UINT _Delta);

public:
	std::string GetLocalIp();
	std::string GetRemoteIp();
	UINT GetLocalPort();
	UINT GetRemotePort();

	void OnHeartBeat();

public:
	INT m_Type;
	INT m_Param;
	CSocket m_Socket;
	bool m_Invalid;
	UINT m_nHeartBeatTimeOut;
	UINT m_nHeartBeatPulse;
    UINT m_DestroyDelay;
};

#define BEGIN_MSG_HANDLER() switch (protoid) {
#define HANDLE_MSG(id, handler) case id: handler(pData); break;
#define END_MSG_HANDLER() default: LOG_WARN("Unhandled protoid: %d", protoid); break; }
