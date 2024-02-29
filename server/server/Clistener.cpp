#include"Clistener.h"

LPFN_ACCEPTEX CListener::m_lpfnAcceptEx = NULL;
LPFN_GETACCEPTEXSOCKADDRS CListener::m_lpfnGetAcceptExSockAddrs = NULL;

void CListener::AddListener()
{
	m_ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_ListenSocket == INVALID_SOCKET)
	{
		std::cout << "Create Listen Socket Failed!" << std::endl;
		return;
	}
	// ����˿ڸ���
	INT _ReUse = 1;
	setsockopt(m_ListenSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&_ReUse, sizeof(_ReUse));

	// ��IP���˿�
	sockaddr_in _addr = { 0 };
	_addr.sin_family = AF_INET;
	_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	_addr.sin_port = LISTEN_PORT;

	// �����׽���
	if (-1 == listen(m_ListenSocket, POST_ACCEPTEX_COUNT))
	{
		std::cout << "Socket Liten Failed!" << std::endl;
		return;
	}

	// �������׽��ְ󶨵�IO��ɶ˿���
	CIocp::GetInstance()->AssociateWithIocp(m_ListenSocket,&m_HandleData);

	// ��ʼ�����պ���
	InitAccepeEx();

}

bool CListener::InitAccepeEx()
{
	DWORD dwBytes = 0;
	GUID GuidAcceptEx = WSAID_ACCEPTEX;
	GUID GuidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS;
	// ��ȡAcceptEx����ָ��
	if (NULL == m_lpfnAcceptEx)
	{
		if (SOCKET_ERROR == WSAIoctl(
			m_ListenSocket,
			SIO_GET_EXTENSION_FUNCTION_POINTER,
			&GuidAcceptEx,
			sizeof(GuidAcceptEx),
			&m_lpfnAcceptEx,
			sizeof(m_lpfnAcceptEx),
			&dwBytes,
			NULL,
			NULL)) {
			std::cout << "δ�ܻ�ȡacceptEx����ָ��" << std::endl;
			return false;
		}
	}

	// ��ȡguidGetAcceptExSockAddrs����ָ��
	if (NULL == m_lpfnGetAcceptExSockAddrs) {
		if (SOCKET_ERROR == WSAIoctl(
			m_ListenSocket,
			SIO_GET_EXTENSION_FUNCTION_POINTER,
			&GuidGetAcceptExSockAddrs,
			sizeof(GuidGetAcceptExSockAddrs),
			&m_lpfnGetAcceptExSockAddrs,
			sizeof(m_lpfnGetAcceptExSockAddrs),
			&dwBytes,
			NULL,
			NULL)) {
			std::cout<<"[%s:%d] δ�ܻ�ȡGuidGetAcceptExSockAddrs����ָ�롣Error:%d"<<std::endl;
			return false;
		}
	}

	// ��������io��������
	m_IoDataArray = new PRE_IO_DATA[POST_ACCEPTEX_COUNT];

	// Ƕ������
	for (int idx = 0; idx < POST_ACCEPTEX_COUNT; ++idx)
	{
		m_IoDataArray[idx].wsabuf = (LPWSABUF)(new char[sizeof(WSABUF) + 4]);
		m_IoDataArray[idx].wsabuf->buf = m_IoDataArray[idx].buffer;
		m_IoDataArray[idx].wsabuf->len = 128;

		if (false == PostAcceptEx(&m_IoDataArray[idx])) {
			std::cout << "PostAcceptEx Failed!" << std::endl;
			return false;
		}
	}
	return true;
}

void CListener::OnAccept(PRE_IO_DATA* _IoData)
{
	if (NULL == _IoData) {
		return;
	}

	SOCKET _Socket = _IoData->socket;

	std::string _LocalIp, _RemoteIp;
	UINT _LocalPort, _RemotePort;
	if (NULL != _IoData) {
		sockaddr_in* _LocalAddr = NULL;
		sockaddr_in* _RemoteAddr = NULL;
		int _LocalLen = sizeof(SOCKADDR_IN);
		int _RemoteLen = sizeof(SOCKADDR_IN);

		if (NULL != m_lpfnGetAcceptExSockAddrs) {
			m_lpfnGetAcceptExSockAddrs(_IoData->wsabuf->buf, 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16,
				(LPSOCKADDR*)&_LocalAddr, &_LocalLen, (LPSOCKADDR*)&_RemoteAddr, &_RemoteLen);

			_LocalIp = inet_ntoa(_LocalAddr->sin_addr);
			_LocalPort = ntohs(_LocalAddr->sin_port);
			_RemoteIp = inet_ntoa(_RemoteAddr->sin_addr);
			_RemotePort = ntohs(_RemoteAddr->sin_port);
		}
	}

	PostAcceptEx(_IoData);

	//////////////////////////////////////////////////////////////////////////
	//����session��Ϣ�������߳��д���

	UPSessionInfo upSessionInfo = std::make_unique<SessionInfo>();
	upSessionInfo->nType = m_Type;
	upSessionInfo->nParam = 0;
	upSessionInfo->bAddFront = false;
	upSessionInfo->sLocalIP = _LocalIp;
	upSessionInfo->nLocalPort = _LocalPort;
	upSessionInfo->sRomoteIP = _RemoteIp;
	upSessionInfo->nRomotePort = _RemotePort;
	upSessionInfo->sock = _Socket;

	SessionManager::GetInstance()->CacheSessionInfo(std::move(upSessionInfo));

}

bool CListener::PostAcceptEx(PRE_IO_DATA* _IoData)
{
	SOCKET _Socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == _Socket) {
		std::cout << "wsasocket failed!" << std::endl;
		return false;
	}

	//����˿ڸ���
	INT _ReUse = 1;
	if (0 != setsockopt(_Socket, SOL_SOCKET, SO_REUSEADDR, (char*)&_ReUse, sizeof(_ReUse))) {
		std::cout << "�˿ڸ���ʧ��!" << std::endl;
	}

	// ��ֵiodata
	memset(&_IoData->overlapped, 0, sizeof(_IoData->overlapped));
	_IoData->socket = _Socket;
	_IoData->opt_type = IO_TYPE_ACCEPT;

	DWORD dwBytes = 0;
	// Ͷ��AcceptEx
	if (false == m_lpfnAcceptEx(m_ListenSocket,
		_Socket,
		_IoData->buffer,
		0,
		sizeof(SOCKADDR_IN) + 16,
		sizeof(SOCKADDR_IN) + 16,
		&dwBytes,
		&_IoData->overlapped)) {
		if (WSA_IO_PENDING != WSAGetLastError()) {
			std::cout << "Ͷ��ʧ�ܣ�" << std::endl;
			closesocket(_Socket);
			return false;
		}
	}

	return true;
}