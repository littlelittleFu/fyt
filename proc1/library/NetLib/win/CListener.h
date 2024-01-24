#pragma once
#include "Type.h"
#include "CSocket.h"
#include <winsock2.h>
#include <MSWSock.h>

class CListener
{
public:
	CListener();
	~CListener();

	UINT GetID() { return m_ID; }
	UINT GetListenPort() { return m_ListenPort; }

	bool Start(std::string& _Ip, UINT _Port);
	void Stop();
	bool PostAcceptEx(PER_IO_DATA* _IoData);
	void OnAccept(PER_IO_DATA* _IoData);
	bool HandleIocpError(DWORD _Error);

	void SetType(INT _Type);
    void SetParam(INT _Param);
    void SetEncrypt(bool _Encrypt);

private:
	bool InitAcceptEx();
	void GetSocketAddress(PER_IO_DATA* _IoData, std::string& _LocalIp, UINT& _LocalPort, std::string& _RemoteIp, UINT& _RemotePort);
protected:
	UINT m_ID;
	bool m_IsStarted;
	SOCKET m_ListenSocket;
	UINT m_ListenPort;

	PER_HANDLE_DATA m_HandleData;
	PER_IO_DATA* m_IoDataArray;

	static LPFN_ACCEPTEX               m_lpfnAcceptEx;
	static LPFN_GETACCEPTEXSOCKADDRS   m_lpfnGetAcceptExSockAddrs;

	INT m_Type;
    INT m_Param;
    bool m_Encrypt;
};