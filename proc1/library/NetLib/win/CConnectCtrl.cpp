#include "pch.h"
#include "CConnectCtrl.h"
#include <process.h>
#include "CLogger.h"
#include "SessionManager.h"

CConnectCtrl::CConnectCtrl()
{
	Init();
}

CConnectCtrl::~CConnectCtrl()
{
	UnInit();
}

void CConnectCtrl::Init()
{
	m_Terminate = false;

	for (int _Idx = 0; _Idx < MAX_CONNECTION; _Idx++) {
		m_Sockets[_Idx] = INVALID_SOCKET;
		m_Events[_Idx] = WSA_INVALID_EVENT;
		m_ConnectData[_Idx]._Type = 0;
		m_ConnectData[_Idx]._Ip = "";
		m_ConnectData[_Idx]._Port = 0;
		m_ConnectData[_Idx]._Param = 0;
	}
	m_ConnectCount = 0;

	UINT dwThreadID = 0;
	m_hThread = (HANDLE)_beginthreadex(NULL,					// Security
		0,						// Stack size - use default
		WorkerThread,     		// Thread fn entry point
		(void*)this,			// Param for thread
		0,						// Init flag
		&dwThreadID);			// Thread address
}

void CConnectCtrl::UnInit()
{
	m_Terminate = true;
	WaitForSingleObject(m_hThread,INFINITE);

	for (int _Idx = 0; _Idx < MAX_CONNECTION; _Idx++) {
		RELEASE_SOCKET(m_Sockets[_Idx]);
		RELEASE_HANDLE(m_Events[_Idx]);
	}
}

unsigned CConnectCtrl::WorkerThread(void* _Param)
{
	CConnectCtrl* _pCConnectCtrl = (CConnectCtrl*)_Param;
	if (_pCConnectCtrl) {
		_pCConnectCtrl->Run();
	}

	return 0;
}

void CConnectCtrl::Run()
{
	while (!m_Terminate) {
		RunConnect();
		ListenEvent();
		Sleep(1);
	}
}

void CConnectCtrl::RunConnect()
{
	m_Mutex.Lock();
	while (m_ConnectCache.size() > 0) {
		ConnectData _Data = m_ConnectCache.front();
		m_ConnectCache.pop_front();
		m_Mutex.Unlock();
		SOCKET hSock = socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
		if (INVALID_SOCKET == hSock) {
			CLogger::GetInstance()->LogCritical("[%s:%d] Socket failed. _Error = %d", FUNC_LINE, WSAGetLastError());
			m_Mutex.Lock();
			continue;
		}
		const char szOpt = 1;
		if (0 != ::setsockopt(hSock, IPPROTO_TCP, TCP_NODELAY, (char *)&szOpt, sizeof(char))) {
			CLogger::GetInstance()->LogWarning("[%s:%d] setsockopt failed. _Error = %d", FUNC_LINE, WSAGetLastError());
		}

		//允许端口复用
		INT _ReUse = 1;
		if (0 != setsockopt(hSock, SOL_SOCKET, SO_REUSEADDR, (char*)&_ReUse, sizeof(_ReUse))) {
			CLogger::GetInstance()->LogWarning("[%s:%d] setsockopt failed. _Error = %d", FUNC_LINE, WSAGetLastError());
		}

		WSAEVENT hEvent = WSACreateEvent();
		if (WSA_INVALID_EVENT == hEvent) {
			CLogger::GetInstance()->LogCritical("[%s:%d] WSACreateEvent failed. _Error = %d", FUNC_LINE, WSAGetLastError());
			closesocket(hSock);
			m_Mutex.Lock();
			continue;
		}
		if (SOCKET_ERROR == WSAEventSelect(hSock, hEvent, FD_CONNECT)) {
			CLogger::GetInstance()->LogCritical("[%s:%d] WSAEventSelect failed. _Error = %d", FUNC_LINE, WSAGetLastError());
			closesocket(hSock);
			WSACloseEvent(hEvent);
			m_Mutex.Lock();
			continue;
		}
		sockaddr_in stAddr = { 0 };
		stAddr.sin_family = AF_INET;
		stAddr.sin_addr.s_addr = inet_addr(_Data._Ip.c_str());
		stAddr.sin_port = htons(_Data._Port);
		if (SOCKET_ERROR == connect(hSock, (sockaddr*)&stAddr, sizeof(stAddr))) {
			if (WSAEWOULDBLOCK != WSAGetLastError()) {
				CLogger::GetInstance()->LogCritical("[%s:%d] connect failed. _Error = %d", FUNC_LINE, WSAGetLastError());
				closesocket(hSock);
				WSACloseEvent(hEvent);
				m_Mutex.Lock();
				continue;
			}
		}
		m_Sockets[m_ConnectCount] = hSock;
		m_Events[m_ConnectCount] = hEvent;
		m_ConnectData[m_ConnectCount]._Type = _Data._Type;
		m_ConnectData[m_ConnectCount]._Ip = _Data._Ip;
		m_ConnectData[m_ConnectCount]._Port = _Data._Port;
		m_ConnectData[m_ConnectCount]._Param = _Data._Param;
        m_ConnectData[m_ConnectCount]._Encrypt = _Data._Encrypt;
		m_ConnectCount++;
		m_Mutex.Lock();
	}
	m_Mutex.Unlock();
}

void CConnectCtrl::ListenEvent()
{
	if (m_ConnectCount > 0) {
		int _Start = 0;
		int _Count = 0;
		int _Index = 0;
		WSAEVENT* _Events;
		WSANETWORKEVENTS _NetworkEvents;
		
		do 
		{
			_Events = &m_Events[_Start];
			if (_Start + WSA_MAXIMUM_WAIT_EVENTS > m_ConnectCount) {
				_Count = m_ConnectCount - _Start;
			}
			else {
				_Count = WSA_MAXIMUM_WAIT_EVENTS;
			}
			_Index = WSAWaitForMultipleEvents(_Count, _Events, false, 0, false);
			if ((WSA_WAIT_FAILED == _Index) || WSA_WAIT_TIMEOUT == _Index) {
				_Start += _Count;
			}
			else {
				_Index -= WSA_WAIT_EVENT_0;
				_Index += _Start;
				//_Start++;
				_Start += _Count;

				if (SOCKET_ERROR == WSAEnumNetworkEvents(m_Sockets[_Index], m_Events[_Index], &_NetworkEvents)) {
					if (WSAEWOULDBLOCK != WSAGetLastError()) {
						CLogger::GetInstance()->LogCritical("[%s:%d] WSAEnumNetworkEvents failed. _Error = %d", FUNC_LINE, WSAGetLastError());
						RELEASE_SOCKET(m_Sockets[_Index]);
						RELEASE_HANDLE(m_Events[_Index]);
						m_ConnectData[_Index]._Type = 0;
						m_ConnectData[_Index]._Ip = "";
						m_ConnectData[_Index]._Port = 0;
						m_ConnectData[_Index]._Param = 0;
                        m_ConnectData[_Index]._Encrypt = false;
						continue;
					}
				}

				if (_NetworkEvents.lNetworkEvents & FD_CONNECT) {
					if (_NetworkEvents.iErrorCode[FD_CONNECT_BIT] != 0) {
						CLogger::GetInstance()->LogCritical("[%s:%d] iErrorCode = %d. _Error = %d Type = %d", FUNC_LINE, _NetworkEvents.iErrorCode[FD_CONNECT_BIT], WSAGetLastError(), m_ConnectData[_Index]._Type);
						RELEASE_SOCKET(m_Sockets[_Index]);
						RELEASE_HANDLE(m_Events[_Index]);
						m_ConnectData[_Index]._Type = 0;
						m_ConnectData[_Index]._Ip = "";
						m_ConnectData[_Index]._Port = 0;
						m_ConnectData[_Index]._Param = 0;
                        m_ConnectData[_Index]._Encrypt = false;
						continue;
					}

					//连接成功
                    UPSessionInfo upSessionInfo = std::make_unique<SessionInfo>();
                    upSessionInfo->nType = m_ConnectData[_Index]._Type;
                    upSessionInfo->nParam = m_ConnectData[_Index]._Param;
                    upSessionInfo->bEncrypt = m_ConnectData[_Index]._Encrypt;
                    upSessionInfo->bAddFront = true;
                    upSessionInfo->sLocalIP = "";
                    upSessionInfo->nLocalPort = 0;
                    upSessionInfo->sRomoteIP = m_ConnectData[_Index]._Ip;
                    upSessionInfo->nRomotePort = m_ConnectData[_Index]._Port;
                    upSessionInfo->sock = m_Sockets[_Index];

                    SessionManager::GetInstance()->CacheSessionInfo(std::move(upSessionInfo));

                    WSACloseEvent(m_Events[_Index]);
                    m_Sockets[_Index] = INVALID_SOCKET;
                    m_Events[_Index] = WSA_INVALID_EVENT;
                    m_ConnectData[_Index]._Type = 0;
                    m_ConnectData[_Index]._Ip = "";
                    m_ConnectData[_Index]._Port = 0;
                    m_ConnectData[_Index]._Param = 0;
                    m_ConnectData[_Index]._Encrypt = false;
				}
			}
		} while (_Start < m_ConnectCount);
		CompressEvent();
	}
}

void CConnectCtrl::CompressEvent()
{
	UINT _Index = 0;
	for (uint32_t _Idx = 0; _Idx < m_ConnectCount; _Idx++) {
		if (m_Sockets[_Idx] != INVALID_SOCKET) {
			if (_Idx != _Index) {
				m_Sockets[_Index] = m_Sockets[_Idx];
				m_Events[_Index] = m_Events[_Idx];
				m_ConnectData[_Index]._Type = m_ConnectData[_Idx]._Type;
				m_ConnectData[_Index]._Ip = m_ConnectData[_Idx]._Ip;
				m_ConnectData[_Index]._Port = m_ConnectData[_Idx]._Port;
				m_ConnectData[_Index]._Param = m_ConnectData[_Idx]._Param;
                m_ConnectData[_Index]._Encrypt = m_ConnectData[_Idx]._Encrypt;
			}
			++_Index;
		}
	}

	m_ConnectCount = _Index;
}

void CConnectCtrl::AddConnector(std::string& _Ip, UINT _Port, INT _Type, INT _Param, bool _Encrypt)
{
	ConnectData _Data;
	_Data._Ip = _Ip;
	_Data._Port = _Port;
	_Data._Type = _Type;
	_Data._Param = _Param;
    _Data._Encrypt = _Encrypt;
	m_Mutex.Lock();
	m_ConnectCache.push_back(_Data);
	m_Mutex.Unlock();
}