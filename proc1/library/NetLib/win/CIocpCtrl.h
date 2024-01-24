#pragma once
#include "Type.h"
#include "CSocket.h"

class CIocpCtrl
{
private:
	CIocpCtrl();
	~CIocpCtrl();

public:
	bool Init(uint32_t nThreadNum);
	void UnInit();
	bool AssociateWithIocp(SOCKET _Socket, PER_HANDLE_DATA* _HandleData);

	DECLARE_INSTANCE(CIocpCtrl);

private:
	static unsigned WINAPI WorkerThread(LPVOID _Param);
	void Run();
	bool HandleError(PER_HANDLE_DATA* _HandleData, DWORD _Error);
private:
	HANDLE m_hShutdownEvent;
	HANDLE m_hCompletionPort;
	HANDLE*	m_WorkerArray;
	INT	m_WorkerCount;
};