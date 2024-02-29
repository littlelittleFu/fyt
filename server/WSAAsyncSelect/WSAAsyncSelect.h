#pragma once
#include <iostream>
#include<winsock2.h>
#include<vector>
#pragma comment(lib,"ws2_32")

//wsaasyncselect �Զ������׽���Ϊ������ģʽ  ��Ϣ����
// WSAEventSelect �¼�ģ��  �¼�����

CRITICAL_SECTION g_cs; // �ٽ��� ������ ֻ��windows�� ���û�̬ �ȽϿ�
ThreadObj* g_pThreadList;

ULONG g_totalConnects;
ULONG g_curConnects;

struct Socket_obj {
	SOCKET s;
	HANDLE event;
	sockaddr_in addr;
	Socket_obj* next;
};

class ThreadObj {
public:
	HANDLE events[100];
	int sockNums;
	Socket_obj* pSockHead;
	Socket_obj* pSockTail;
	CRITICAL_SECTION cs;
	ThreadObj* pNext;
};

Socket_obj* GetSocketObj(SOCKET s) {
	Socket_obj* pSock = (Socket_obj*)new (Socket_obj);
	pSock->s = s;
	pSock->event = ::WSACreateEvent();
}

void FreeSocketObj(Socket_obj* ps) {
	::CloseHandle(ps->event);
	closesocket(ps->s);
	delete ps;
}

ThreadObj* GetThreadObj()
{
	ThreadObj* pThread = (ThreadObj*) new ThreadObj();
	::InitializeCriticalSection(&pThread->cs);
	pThread->events[0] = WSACreateEvent();
	::EnterCriticalSection(&g_cs);
	pThread->pNext = g_pThreadList;
	g_pThreadList = pThread;
	::LeaveCriticalSection(&g_cs);

	return pThread;
}

void FreeThreadObj(ThreadObj* pThread) {
	::EnterCriticalSection(&g_cs);
	ThreadObj* p = g_pThreadList;
	if (p == pThread) {
		g_pThreadList = p->pNext;
	}
	else {
		while (p != nullptr && p->pNext != pThread) {
			p = p->pNext;
		}

		if (p != nullptr) {
			p->pNext = pThread->pNext;
		}
	}

	::LeaveCriticalSection(&g_cs);

	::CloseHandle(pThread->events[0]);
	::DeleteCriticalSection(&pThread->cs);
	delete pThread;
}

void RebuildArray(ThreadObj* pThread) {
	::EnterCriticalSection(&pThread->cs);
	Socket_obj* psock = pThread->pSockHead;
	int n = 1;
	while (psock != nullptr) {
		pThread->events[n++] = psock->event;
		psock = psock->next;
	}
	::LeaveCriticalSection(&pThread->cs);
}

bool InsertSSocketOnj(ThreadObj* pThread, Socket_obj* sock) {
	bool ret = false;
	::EnterCriticalSection(&pThread->cs);
	if (pThread->sockNums < 64 - 1) {
		if (pThread->pSockHead == nullptr) {
			pThread->pSockHead = pThread->pSockTail = sock;
		}
		else {
			pThread->pSockTail->next = sock;
			pThread->pSockTail = sock;
		}

		pThread->sockNums++;
		ret = true;
	}
	::LeaveCriticalSection(&pThread->cs);
	if (ret) {
	// ԭ�Ӳ�����������+1
		::InterlockedIncrement(&g_totalConnects);
		::InterlockedIncrement(&g_curConnects);
	}
	return ret;
}

DWORD WINAPI ServerThread(LPVOID lpParam) {
	ThreadObj* pthread = (ThreadObj*)lpParam;
	while (true) {
	// �ȴ������¼�
		int idx = ::WSAWaitForMultipleEvents
	}
}

int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(7890);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	bind(sock, (sockaddr*)&addr, sizeof(addr));

	listen(sock, 128);

	WSAEVENT events[100];
	SOCKET sockets[100];
	int totalEvent = 0;
	unsigned short port = 1111;

	// �����¼����� �����׽���
	WSAEVENT event = WSACreateEvent();
	::WSAEventSelect(sock, event, FD_ACCEPT | FD_CLOSE);

	events[totalEvent] = event;
	sockets[totalEvent] = sock;
	totalEvent++;

	//���������¼�
	while (true) {
		int index = ::WSAWaitForMultipleEvents(totalEvent, events, false, WSA_INFINITE, false);
		// ����ÿ���¼�������wait �Ա�ȷ��״̬

		index = index - WSA_WAIT_EVENT_0;
		for (int i = 0; i < index; ++i) {
		
		}
	}

	return 0;
}