#pragma once
#include "Type.h"
#ifdef _WIN32
#include <WinSock2.h>
#endif
#include <string>

class ISession
{
public:
	ISession() {};
	virtual ~ISession() {};
	virtual INT GetType() = 0;
	virtual void SetType(INT _Type) = 0;
	virtual INT GetParam() = 0;
	virtual void SetParam(INT _Param) = 0;
    virtual void SetEncrypt(bool _Encrypt) = 0;
	virtual UINT GetID() = 0;
	virtual void OnEstablish(SOCKET _Socket) = 0;
	virtual void OnLost() = 0;
	virtual void HandleMessage(void* _pData, UINT _Len) = 0;
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData) = 0;
	virtual void OnError(DWORD _ErrorCode) = 0;
	virtual void OnUpdate(UINT _Delta) = 0;
	virtual bool SendPkg(void* _pData, UINT _Len, bool candrop = false) = 0;
	virtual bool IsInvalid() = 0;
	virtual void SetInvalid(bool _Value) = 0;
	virtual void DoClose() = 0;
	virtual void SetIpInfo(std::string& _LocalIp,UINT _LocalPort, std::string& _RemoteIp,UINT _RemotePort) = 0;
	virtual void LogDebugInfo(DEBUG_DATA& debugData) = 0;
    virtual bool CanBeDestroyed(UINT _Delta) = 0;
};
typedef std::map<UINT, ISession*> ISessionMap;
typedef std::vector<std::map<UINT, ISession*>> ISessionMapVec;