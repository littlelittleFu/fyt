#pragma once
#include <WinSock2.h>
#include <list>
#include "CMutex.h"
#include "Type.h"
#include <string>

struct ConnectData
{
	std::string _Ip;
	UINT _Port;
	INT _Type;
	INT _Param;
    bool _Encrypt;
};

class CConnectCtrl
{
public:
	CConnectCtrl();
	~CConnectCtrl();

public:
	void AddConnector(std::string& _Ip, UINT _Port, INT _Type, INT _Param = 0, bool _Encrypt = false);
private:
	void Init();
	void UnInit();
	static unsigned WINAPI WorkerThread(void* _Param);
	void Run();
	void RunConnect();
	void ListenEvent();
	void CompressEvent();
private:
	bool m_Terminate;
	HANDLE m_hThread;
	SOCKET m_Sockets[MAX_CONNECTION];
	WSAEVENT m_Events[MAX_CONNECTION];
	ConnectData m_ConnectData[MAX_CONNECTION];
	UINT m_ConnectCount;
	std::list<ConnectData> m_ConnectCache;
	CMutex m_Mutex;
};
