#pragma once
#include"CSocket.h"
#include"CIocp.h"
#include"sessionMgr.h"
#include <MSWSock.h>


#define LISTEN_PORT 8888
#define POST_ACCEPTEX_COUNT 128
class CListener
{
public:
	CListener() {};
	~CListener() {}

	void AddListener();
	bool InitAccepeEx();
	void OnAccept(PRE_IO_DATA* _IoData);
	bool PostAcceptEx(PRE_IO_DATA* _IoData);

	void SetType(INT type) { m_Type = type; };


private:
	SOCKET m_ListenSocket;
	PRE_HANDLE_DATA m_HandleData;
	PRE_IO_DATA* m_IoDataArray;

	INT m_Type;

	static LPFN_ACCEPTEX               m_lpfnAcceptEx;
	static LPFN_GETACCEPTEXSOCKADDRS   m_lpfnGetAcceptExSockAddrs;
};