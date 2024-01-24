#include "pch.h"
#include "CIocpCtrl.h"
#include "CLogger.h"
#include <process.h>
#include "CListener.h"
#include "Config.h"

#define WORKER_THREADS_PER_PROCESSOR 2

IMPLEMENT_INSTANCE(CIocpCtrl);

CIocpCtrl::CIocpCtrl()
{
	m_hShutdownEvent = NULL;
	m_hCompletionPort = NULL;
	m_WorkerArray = NULL;
	m_WorkerCount = 0;
}

CIocpCtrl::~CIocpCtrl()
{
	UnInit();
}

bool CIocpCtrl::Init(uint32_t nThreadNum)
{
	WSADATA _WsaData;
	int _Result = WSAStartup(MAKEWORD(2, 2), &_WsaData);
	if (NO_ERROR != _Result) {
		CLogger::GetInstance()->LogCritical("[%s:%d]WSAStartup failed Error=%d", FUNC_LINE,_Result);
		return false;
	}

	m_hShutdownEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (NULL == m_hCompletionPort) {
		CLogger::GetInstance()->LogCritical("[%s:%d]CreateIoCompletionPort failed Error=%d", FUNC_LINE, WSAGetLastError());
		return false;
	}

	SYSTEM_INFO _Info;
	GetSystemInfo(&_Info);
	m_WorkerCount = _Info.dwNumberOfProcessors * WORKER_THREADS_PER_PROCESSOR;
	m_WorkerArray = new HANDLE[m_WorkerCount];
	for (int _Idx = 0; _Idx < m_WorkerCount; _Idx++) {
		m_WorkerArray[_Idx] = INVALID_HANDLE_VALUE;
	}

	UINT _ThreadID = 0;
	for (int _Idx = 0; _Idx < m_WorkerCount; _Idx++) {
		m_WorkerArray[_Idx] = (HANDLE)_beginthreadex(NULL, 0, WorkerThread, (void*)this, 0, &_ThreadID);
		if (NULL == m_WorkerArray[_Idx]) {
			m_WorkerCount = _Idx;
			UnInit();
			CLogger::GetInstance()->LogCritical("[%s:%d]create worker thread failed", FUNC_LINE);
			return false;
		}
	}

	return true;
}

void CIocpCtrl::UnInit()
{
	if (m_WorkerCount > 0) {
		if (NULL != m_hShutdownEvent) {
			SetEvent(m_hShutdownEvent);
		}

		if (NULL != m_hCompletionPort) {
			for (int _Idx = 0; _Idx < m_WorkerCount; _Idx++) {
				PostQueuedCompletionStatus(m_hCompletionPort, 0, NULL, NULL);
			}
			WaitForMultipleObjects(m_WorkerCount, m_WorkerArray, true, INFINITE);
		}

		RELEASE_HANDLE(m_hShutdownEvent);

		for (int _Idx = 0; _Idx < m_WorkerCount; _Idx++) {
			RELEASE_HANDLE(m_WorkerArray[_Idx]);
		}

		RELEASE(m_WorkerArray);
		RELEASE_HANDLE(m_hCompletionPort);
		m_WorkerCount = 0;
	}
}

unsigned CIocpCtrl::WorkerThread(LPVOID _Param)
{
	CIocpCtrl* _Ctrl = (CIocpCtrl*)_Param;
	if (_Ctrl) {
		_Ctrl->Run();
	}

	return 0;
}

void CIocpCtrl::Run()
{
	PER_HANDLE_DATA* _PER_HANDLE_DATA;
	PER_IO_DATA* _PER_IO_DATA;
	bool _Ret;
	DWORD _ByteTrans;
	DWORD _LastError;
	CListener* _Listener = NULL;
	CSocket* _Socket = NULL;

	//关闭事件没有发出信号
	while (WAIT_OBJECT_0 != WaitForSingleObject(m_hShutdownEvent, 0)) {
		_Ret = GetQueuedCompletionStatus(
			m_hCompletionPort, 
			&_ByteTrans, 
			(PULONG_PTR)&_PER_HANDLE_DATA, 
			(LPOVERLAPPED*)&_PER_IO_DATA, 
			INFINITE);

		g_MsgAll += 1;

		// 如果收到的是退出标志，则直接退出
		if (EXIT_CODE == _PER_HANDLE_DATA) {
			CLogger::GetInstance()->LogNormal("[%s:%d]完成端口退出",FUNC_LINE);
			return;
		}

		if (!_Ret) {
			if (NULL == _PER_IO_DATA) {
				CLogger::GetInstance()->LogNormal("[%s:%d]单IO数据为空",FUNC_LINE);
				continue;
			}

			_LastError = WSAGetLastError();
			if (!HandleError(_PER_HANDLE_DATA, _LastError)) {
				CLogger::GetInstance()->LogCritical("[%s:%d]IOCP未处理的异常.Error=%d", FUNC_LINE, _LastError);
			}
			continue;
		}

		if (HANDLE_TYPE_LISTEN == _PER_HANDLE_DATA->_Type) {
			_Listener = (CListener*)_PER_HANDLE_DATA->_Pointer;
			if (_Listener) {
				_Listener->OnAccept(_PER_IO_DATA);
			}
		}
		else if (HANDLE_TYPE_SOCKET == _PER_HANDLE_DATA->_Type) {
			_Socket = (CSocket*)_PER_HANDLE_DATA->_Pointer;
			if (_Socket) {
				if ((0 == _ByteTrans) && ((IO_TYPE_RECV == _PER_IO_DATA->_Type) || IO_TYPE_SEND == _PER_IO_DATA->_Type)) {
					_Socket->OnLost();
					continue;
				}
				else {
					if (IO_TYPE_RECV == _PER_IO_DATA->_Type) {
						_Socket->OnRecv(_ByteTrans);
					}
					else if (IO_TYPE_SEND == _PER_IO_DATA->_Type) {
						_Socket->OnSend(_ByteTrans);
					}
				}
			}
		}
	}
}

bool CIocpCtrl::HandleError(PER_HANDLE_DATA* _HandleData, DWORD _Error)
{
	bool _Ret = false;
	if (!_Ret && _HandleData) {
		if (HANDLE_TYPE_LISTEN == _HandleData->_Type) {
			CListener* _Listener = (CListener*)_HandleData->_Pointer;
			if (_Listener) {
				_Ret = _Listener->HandleIocpError(_Error);
			}
		}
		else if (HANDLE_TYPE_SOCKET == _HandleData->_Type) {
			CSocket* _Socket = (CSocket*)_HandleData->_Pointer;
			if (_Socket) {
				_Ret = _Socket->HandleIocpError(_Error);
			}
		}
	}

	return _Ret;
}

bool CIocpCtrl::AssociateWithIocp(SOCKET _Socket, PER_HANDLE_DATA* _HandleData) 
{
	bool _Ret = false;
	if (NULL != m_hCompletionPort) {
		if (NULL != CreateIoCompletionPort((HANDLE)_Socket, m_hCompletionPort, (ULONG_PTR)_HandleData, 0)) {
			_Ret = true;
		}
		else {
			CLogger::GetInstance()->LogCritical("[%s:%d] AssociateWithIocp failed Error=%d", FUNC_LINE, WSAGetLastError());			
		}
	}

	return _Ret;
}