#include"CIocp.h"

CIocp* CIocp::instance = nullptr;

bool CIocp::init()
{
	WSADATA _WsaData;
	int _Result = WSAStartup(MAKEWORD(2, 2), &_WsaData);

	if (NO_ERROR != _Result)
	{
		std::cout << "WSAStartUp Failed!" << std::endl;
		return false;
	}

	// 创建关闭事件
	m_hShutdownEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	// 创建完成端口
	m_CompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	// 根据cpu数量获取工作线程数量
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
			std::cout << "创建工作线程失败!" << std::endl;
			return false;
		}
	}

	return true;
}


bool CIocp::AssociateWithIocp(SOCKET _Socket, PRE_HANDLE_DATA* _HandleData)
{
	if (NULL != CreateIoCompletionPort((HANDLE)_Socket, m_CompletionPort, (ULONG_PTR)_HandleData, 0)) {
		return false;
	}
	return true;
}

unsigned CIocp::WorkerThread(LPVOID _Param)
{
	CIocp* _iocp = (CIocp*)_Param;
	if (_iocp)
	{
		_iocp->Run();
	}
	return 0;
}

void CIocp::Run()
{
	PRE_HANDLE_DATA* _PRE_HANDLE_DATA;
	PRE_IO_DATA* _PRE_IO_DATA;
	bool _Ret;
	DWORD _ByteTrans;
	DWORD _LastError;
	CListener* _Listener = NULL;
	CSocket* _Socket = NULL;

	//关闭事件是否触发
	while (WAIT_OBJECT_0 == WaitForSingleObject(m_hShutdownEvent, 0))
	{
		// 完成端口的队列
		_Ret = GetQueuedCompletionStatus(
			m_CompletionPort,
			&_ByteTrans,
			(PULONG_PTR)&_PRE_HANDLE_DATA,
			(LPOVERLAPPED*)&_PRE_IO_DATA,
			INFINITE);

		// 消息+1


		// 收到消息
		if (NULL == _PRE_HANDLE_DATA) {
			std::cout << "完成端口退出！" << std::endl;
			return;
		}

		if (!_Ret) {
			if (NULL == _PRE_IO_DATA) {
				std::cout<<"单IO数据为空"<<std::endl;
				continue;
			}
			std::cout << "IOCP处理异常!" << std::endl;
			continue;
		}

		if (HANDLE_TYPE_LISTEN == _PRE_HANDLE_DATA->_Type) {
			_Listener = (CListener*)_PRE_HANDLE_DATA->_Pointer;
			if (_Listener) {
				_Listener->OnAccept(_PRE_IO_DATA);
			}
		}
		else if (HANDLE_TYPE_SOCKET == _PRE_HANDLE_DATA->_Type)
		{
			_Socket = (CSocket*)_PRE_HANDLE_DATA->_Pointer;
			if (_Socket)
			{
				if ((0 == _ByteTrans) && ((IO_TYPE_RECV == _PRE_IO_DATA->opt_type) || IO_TYPE_SEND == _PRE_IO_DATA->opt_type)) {
					continue;
				}
				else
				{
					// 数据处理
					if (IO_TYPE_RECV == _PRE_HANDLE_DATA->_Type)
					{
						_Socket->OnRecv(_ByteTrans);
					}
					else if(IO_TYPE_SEND == _PRE_HANDLE_DATA->_Type)
					{
						_Socket->OnSend(_ByteTrans);
					}
				}
			}
		}
	}
}