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

	// �����ر��¼�
	m_hShutdownEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	// ������ɶ˿�
	m_CompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	// ����cpu������ȡ�����߳�����
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
			std::cout << "���������߳�ʧ��!" << std::endl;
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

	//�ر��¼��Ƿ񴥷�
	while (WAIT_OBJECT_0 == WaitForSingleObject(m_hShutdownEvent, 0))
	{
		// ��ɶ˿ڵĶ���
		_Ret = GetQueuedCompletionStatus(
			m_CompletionPort,
			&_ByteTrans,
			(PULONG_PTR)&_PRE_HANDLE_DATA,
			(LPOVERLAPPED*)&_PRE_IO_DATA,
			INFINITE);

		// ��Ϣ+1


		// �յ���Ϣ
		if (NULL == _PRE_HANDLE_DATA) {
			std::cout << "��ɶ˿��˳���" << std::endl;
			return;
		}

		if (!_Ret) {
			if (NULL == _PRE_IO_DATA) {
				std::cout<<"��IO����Ϊ��"<<std::endl;
				continue;
			}
			std::cout << "IOCP�����쳣!" << std::endl;
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
					// ���ݴ���
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