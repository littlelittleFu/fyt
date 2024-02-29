#pragma once
#include"CSocket.h"
#include"Clistener.h"
#define WORKER_THREADS_PER_PROCESSOR 2
class CIocp
{
private:
	CIocp(){};
	~CIocp() {};
public:
	bool init();
	bool AssociateWithIocp(SOCKET _Socket, PRE_HANDLE_DATA* _HandleData);
	void Run();


private:
	// 工作线程
	static unsigned WINAPI WorkerThread(LPVOID _Param);

private:
	HANDLE m_CompletionPort;
	HANDLE m_hShutdownEvent;
	HANDLE* m_WorkerArray;
	INT	m_WorkerCount;

private:
	static CIocp* instance;
public:
	static CIocp* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new CIocp;
			return instance;
		}
		return instance;
	}
};