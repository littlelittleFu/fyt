#include "pch.h"
#include "CListener.h"
#include "CLogger.h"
#include "SessionManager.h"
#include "CIocpCtrl.h"

#pragma comment(lib,"ws2_32.lib")

#define POST_ACCEPTEX_COUNT     128

LPFN_ACCEPTEX CListener::m_lpfnAcceptEx = NULL;
LPFN_GETACCEPTEXSOCKADDRS CListener::m_lpfnGetAcceptExSockAddrs = NULL;
CListener::CListener()
{
	static UINT _ID = 0;
	_ID++;
	if (_ID > 4200000000) {
		_ID = 0;
	}
	m_ID = _ID;
	m_IsStarted = false;
	m_ListenSocket = INVALID_SOCKET;
	m_ListenPort = 0;
	m_HandleData._Type = HANDLE_TYPE_LISTEN;
	m_HandleData._Pointer = this;
	m_IoDataArray = NULL;

	m_Type = SESSION_TYPE_INVALID;
    m_Param = 0;
    m_Encrypt = true;
}

CListener::~CListener()
{
	RELEASE_SOCKET(m_ListenSocket);

	for (int _Idx = 0; _Idx < POST_ACCEPTEX_COUNT; _Idx++) {
		if (NULL != m_IoDataArray[_Idx]._WsaBuf) {
			delete m_IoDataArray[_Idx]._WsaBuf;
		}
	}
	RELEASE_ARRAY(m_IoDataArray);
}

bool CListener::InitAcceptEx()
{
	DWORD dwBytes = 0;
	GUID GuidAcceptEx = WSAID_ACCEPTEX;
	GUID GuidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS;
	if (NULL == m_lpfnAcceptEx) {
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
			CLogger::GetInstance()->LogCritical("[%s:%d] 未能获取AcceptEx函数指针。Error:%d",FUNC_LINE, WSAGetLastError());
			return false;
		}
	}

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
			CLogger::GetInstance()->LogCritical("[%s:%d] 未能获取GuidGetAcceptExSockAddrs函数指针。Error:%d", FUNC_LINE, WSAGetLastError());
			return false;
		}
	}

	m_IoDataArray = new PER_IO_DATA[POST_ACCEPTEX_COUNT];
	if (NULL == m_IoDataArray) {
		CLogger::GetInstance()->LogCritical("[%s:%d] create m_IoDataArray failed.", FUNC_LINE);
		return false;
	}

	for (int _Idx = 0; _Idx < POST_ACCEPTEX_COUNT; _Idx++) {
		m_IoDataArray[_Idx]._WsaBuf = (LPWSABUF)(new char[sizeof(WSABUF) + 4]);
		m_IoDataArray[_Idx]._WsaBuf->buf = m_IoDataArray[_Idx]._Buf;
		m_IoDataArray[_Idx]._WsaBuf->len = 128;

		if (false == PostAcceptEx(&m_IoDataArray[_Idx])) {
			CLogger::GetInstance()->LogCritical("[%s:%d] PostAcceptEx failed.", FUNC_LINE);
			return false;
		}
	}

	return true;
}

void CListener::GetSocketAddress(PER_IO_DATA* _IoData,std::string& _LocalIp,UINT& _LocalPort,std::string& _RemoteIp,UINT& _RemotePort)
{
	if (NULL != _IoData) {
		sockaddr_in* _LocalAddr = NULL;
		sockaddr_in* _RemoteAddr = NULL;
		int _LocalLen = sizeof(SOCKADDR_IN);
		int _RemoteLen = sizeof(SOCKADDR_IN);

		if (NULL != m_lpfnGetAcceptExSockAddrs) {
			m_lpfnGetAcceptExSockAddrs(_IoData->_WsaBuf->buf, 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16,
				(LPSOCKADDR*)&_LocalAddr, &_LocalLen, (LPSOCKADDR*)&_RemoteAddr, &_RemoteLen);

			_LocalIp = inet_ntoa(_LocalAddr->sin_addr);
			_LocalPort = ntohs(_LocalAddr->sin_port);
			_RemoteIp = inet_ntoa(_RemoteAddr->sin_addr);
			_RemotePort = ntohs(_RemoteAddr->sin_port);
		}
	}
}

bool CListener::Start(std::string& _Ip,UINT _Port)
{
	m_ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == m_ListenSocket) {
		CLogger::GetInstance()->LogCritical("[%s:%d]create listen socket failed. Error=%d", FUNC_LINE, WSAGetLastError());
		return false;
	}

	//允许端口复用
	INT _ReUse = 1;
	setsockopt(m_ListenSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&_ReUse, sizeof(_ReUse));

	//绑定IP及端口
	sockaddr_in _Addr = { 0 };
	_Addr.sin_family = AF_INET;
	if (_Ip.empty()) {
		_Addr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else {
		_Addr.sin_addr.s_addr = inet_addr(_Ip.c_str());
	}
	_Addr.sin_port = htons(_Port);
	if (-1 == bind(m_ListenSocket, (sockaddr*)&_Addr, sizeof(_Addr))) {
		CLogger::GetInstance()->LogCritical("[%s:%d]socket bind failed. Error=%d", FUNC_LINE, WSAGetLastError());
		return false;
	}

	//监听该套接字
	if (-1 == listen(m_ListenSocket, POST_ACCEPTEX_COUNT)) {
		CLogger::GetInstance()->LogCritical("[%s:%d]socket listen failed. Error=%d", FUNC_LINE, WSAGetLastError());
		return false;
	}

	//将该套接字绑定到IO完成端口上
	if (!CIocpCtrl::GetInstance()->AssociateWithIocp(m_ListenSocket, &m_HandleData)) {
		CLogger::GetInstance()->LogCritical("[%s:%d]socket AssociateWithIocp failed. Error=%d", FUNC_LINE, WSAGetLastError());
		return false;
	}

	if (!InitAcceptEx()) {
		return false;
	}

	m_IsStarted = true;

	CLogger::GetInstance()->LogNormal("[%s:%d] start listen. IP=%s Port=%d Type=%d", FUNC_LINE, _Ip.c_str(), _Port, m_Type);

	return true;
}

void CListener::Stop()
{
	m_IsStarted = false;
}

bool CListener::PostAcceptEx(PER_IO_DATA* _IoData)
{
	SOCKET _Socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == _Socket) {
		CLogger::GetInstance()->LogCritical("[%s:%d] WSASocket failed.Error=%d", FUNC_LINE, WSAGetLastError());
		return false;
	}

	//允许端口复用
	INT _ReUse = 1;
	if (0 != setsockopt(_Socket, SOL_SOCKET, SO_REUSEADDR, (char*)&_ReUse, sizeof(_ReUse))) {
		CLogger::GetInstance()->LogWarning("[%s:%d] setsockopt failed. _Error = %d", FUNC_LINE, WSAGetLastError());
	}

	memset(&_IoData->_OverLapped, 0, sizeof(_IoData->_OverLapped));
	_IoData->_Socket = _Socket;
	_IoData->_Type = IO_TYPE_ACCEPT;

	DWORD dwBytes = 0;
	// 投递AcceptEx
	if (false == m_lpfnAcceptEx(m_ListenSocket, 
		_Socket, 
		_IoData->_Buf,
		0,
		sizeof(SOCKADDR_IN) + 16,
		sizeof(SOCKADDR_IN) + 16, 
		&dwBytes,
		&_IoData->_OverLapped)) {
		if (WSA_IO_PENDING != WSAGetLastError()) {
			CLogger::GetInstance()->LogCritical("[%s:%d]投递 AcceptEx 请求失败，Error:%d", FUNC_LINE, WSAGetLastError());
			closesocket(_Socket);
			return false;
		}
	}

	return true;
}

void CListener::OnAccept(PER_IO_DATA* _IoData)
{
	if (NULL == _IoData) {
		return;
	}

	SOCKET _Socket = _IoData->_Socket;
	if (!m_IsStarted) {
		closesocket(_Socket);
		return;
	}

	std::string _LocalIp, _RemoteIp;
	UINT _LocalPort, _RemotePort;
	GetSocketAddress(_IoData, _LocalIp, _LocalPort, _RemoteIp, _RemotePort);
	PostAcceptEx(_IoData);

	//////////////////////////////////////////////////////////////////////////
	//保存session信息，在主线程中创建

    UPSessionInfo upSessionInfo = std::make_unique<SessionInfo>();
    upSessionInfo->nType = m_Type;
    upSessionInfo->nParam = m_Param;
    upSessionInfo->bEncrypt = m_Encrypt;
    upSessionInfo->bAddFront = false;
    upSessionInfo->sLocalIP = _LocalIp;
    upSessionInfo->nLocalPort = _LocalPort;
    upSessionInfo->sRomoteIP = _RemoteIp;
    upSessionInfo->nRomotePort = _RemotePort;
    upSessionInfo->sock = _Socket;

    SessionManager::GetInstance()->CacheSessionInfo(std::move(upSessionInfo));
}

bool CListener::HandleIocpError(DWORD _Error)
{
	bool _Ret = false;
	if (WSA_IO_PENDING == _Error) {
	_Ret = true;
	}
	return _Ret;
}

void CListener::SetType(INT _Type)
{
	m_Type = _Type;
}

void CListener::SetParam(INT _Param)
{
    m_Param = _Param;
}

void CListener::SetEncrypt(bool _Encrypt)
{
    m_Encrypt = _Encrypt;
}