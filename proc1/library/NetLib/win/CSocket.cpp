#include "pch.h"
#include "CSocket.h"
#include "CBufManager.h"
#include "Config.h"
#include "CLogger.h"
#include "CIocpCtrl.h"

#include <websocketpp/processors/hybi00.hpp>
#include <websocketpp/processors/hybi07.hpp>
#include <websocketpp/processors/hybi08.hpp>
#include <websocketpp/processors/hybi13.hpp>

/*
	注：当设置项目的字节对齐为1时,WSARecv和WSASend有可能返回错误10014
	原因：WSABUFF结构体的字节对齐方式默认不是1，如果stPerIoData结构图中_WsaBuf字段类型是WSABUFF时，会引起10014
	解决方法：stPerIoData结构图中_WsaBuf字段类型改为LPWSABUFF，并且在CSocket初始化时给_WsaBuf多分配4字节空间
*/

/*
	如果网络已经连接，则：
	1.如果对方调用closesocket，我方的PostRecv将会返回，传输的字节数为0
	2.如果对方直接关闭退出，我方会收到ERROR_NETNAME_DELETED
	3.如果我方调用closesocket，则会收到ERROR_CONNECTION_ABORTED或者ERROR_OPERATION_ABORTED
*/

CSocket::rng_type CSocket::m_rng;

CSocket::CSocket()
{
	static UINT _ID = 0;
	_ID++;
	if (_ID > 4200000000) {
		_ID = 0;
	}
	m_ID = _ID;

	m_HandleData._Type = HANDLE_TYPE_SOCKET;
	m_HandleData._Pointer = this;
	m_IoDataSend._Type = IO_TYPE_SEND;
	m_IoDataSend._WsaBuf = (LPWSABUF)(new char[sizeof(WSABUF) + 4]);
	m_IoDataRecv._Type = IO_TYPE_RECV;
	m_IoDataRecv._WsaBuf = (LPWSABUF)(new char[sizeof(WSABUF) + 4]);
    m_DataType = DATA_TYPE_DEF;
	m_Socket = INVALID_SOCKET;
	m_IsConnect = false;
	m_SendBuf = NULL;
	m_RecvBuf = NULL;
	m_SendSize = 0;
	m_RecvSize = 0;
	m_SendPos = 0;
	m_RecvPos = 0;

	m_LocalIP = "";
	m_LocalPort = 0;
	m_RemoteIP = "";
	m_RemotePort = 0;

	m_pSession = NULL;
    m_Encrypt = false;
	m_NeedClose = false;
    m_bNeedNotifySessionOnLost = false;
	m_SendingData = false;
	m_dwPostRecv = 0;

	Init();
}

CSocket::~CSocket()
{
	UnInit();
}

void CSocket::Init()
{
	m_SendSize = g_SendBufSize;
	m_SendPos = 0;
	CBufManager::GetInstance()->GetSendOrRecvBuffer(m_SendBuf, m_SendSize, true);

	m_RecvSize = g_RecvBufSize;
	m_RecvPos = 0;
	CBufManager::GetInstance()->GetSendOrRecvBuffer(m_RecvBuf, m_RecvSize, false);

    unsigned char aes_key[32] = {
        0x4E, 0xD9, 0x83, 0x4F, 0x20, 0x59, 0x9E, 0x47, 0x6C, 0xFF, 0x0C, 0x74, 0x59, 0x29, 0x4E, 0x0B,
        0x00, 0x5B, 0x7E, 0xA2, 0x33, 0x58, 0xC4, 0x4E, 0x2C, 0x6C, 0xFD, 0x4E, 0x07, 0x38, 0x59, 0x7B };

    unsigned char aes_iv[32] = {
        0x21, 0x80, 0xA0, 0xCF, 0xB1, 0xA4, 0x40, 0x99, 0x2C, 0x50, 0x0F, 0x8E, 0xD1, 0x4F, 0xEE, 0xD7,
        0xC1, 0x7D, 0x22, 0x30, 0x7C, 0x36, 0x6A, 0xF7, 0xD0, 0x0D, 0xB7, 0x05, 0xAE, 0xE0, 0x97, 0x4D };

    m_aes.SetParam("cfb", 128, aes_key, _countof(aes_key), nullptr, 0);
}

void CSocket::UnInit()
{
	if (NULL != m_SendBuf) {
		CBufManager::GetInstance()->ReleaseSendOrRecvBuffer(m_SendBuf, m_SendSize, true);
		m_SendBuf = NULL;
	}

	if (NULL != m_RecvBuf) {
		CBufManager::GetInstance()->ReleaseSendOrRecvBuffer(m_RecvBuf, m_RecvSize, false);
		m_RecvBuf = NULL;
	}

	if (INVALID_SOCKET != m_Socket) {
		shutdown(m_Socket,SD_BOTH);
		closesocket(m_Socket);
		m_Socket = INVALID_SOCKET;
	}

	if (NULL != m_IoDataSend._WsaBuf) {
		delete m_IoDataSend._WsaBuf;
		m_IoDataSend._WsaBuf = NULL;
	}

	if (NULL != m_IoDataRecv._WsaBuf) {
		delete m_IoDataSend._WsaBuf;
		m_IoDataSend._WsaBuf = NULL;
	}
}

bool CSocket::AssociateWithIocp()
{
	bool _Ret = false;
	if (INVALID_SOCKET!= m_Socket) {
		_Ret = CIocpCtrl::GetInstance()->AssociateWithIocp(m_Socket, &m_HandleData);
	}
	return _Ret;
}

void CSocket::OnUpdate(int _Delta)
{
    if (m_bNeedNotifySessionOnLost)
    {
        if (m_pSession)
        {
            m_pSession->OnLost();
            m_pSession->SetInvalid(true);
        }

        m_bNeedNotifySessionOnLost = false;
    }

	if (!m_IsConnect) {
		return;
	}

	if (g_LogLevel) {
		if (m_SendPeak < m_SendCache.size()) m_SendPeak = m_SendCache.size();
		if (m_RecvPeak < m_RecvCache.size()) m_RecvPeak = m_RecvCache.size();
	}

	if (!m_SendingData) {
		if (NULL != m_SendBuf) {
            CLockGuard guard(m_SendMutex);

			while (m_SendCache.size() > 0) {
				DATA_CACHE& _Data = m_SendCache.front();
				if (m_SendPos + _Data._Len < m_SendSize) {
					memcpy(m_SendBuf + m_SendPos, _Data._Data, _Data._Len);
					m_SendPos += _Data._Len;
					CBufManager::GetInstance()->ReleaseBuffer(_Data._Data, _Data._MaxLen);
					m_SendCache.pop_front();
				}
				else {
					break;
				}
			}

			if (0 < m_SendPos) {
				PostSend();
			}
        }
	}

	if (0 < m_RecvCache.size()) {
		while (m_RecvCache.size() > 0) {
			m_RecvMutex.Lock();
			DATA_CACHE _Data = m_RecvCache.front();
			m_RecvCache.pop_front();
			m_RecvMutex.Unlock();
			//通知上层处理消息
			if (m_pSession) {
				m_pSession->HandleMessage(_Data._Data, _Data._Len);
			}
			CBufManager::GetInstance()->ReleaseBuffer(_Data._Data, _Data._MaxLen);
		}
	}
}

void CSocket::OnEstablish(SOCKET _Socket)
{
	m_IsConnect = true;
	m_Socket = _Socket;
	if (!AssociateWithIocp()) {
		CLogger::GetInstance()->LogCritical("[%s:%d] OnEstablish failed", FUNC_LINE);
		UnInit();
		return;
	}

    if (m_pSession && m_pSession->GetParam() == CLIENT_PROTO_WS) {
        SetDataType(DATA_TYPE_HTTP);
    }

	PostRecv();
}

void CSocket::OnLost()
{
	m_IsConnect = false;
    m_bNeedNotifySessionOnLost = true;
}

void CSocket::DoClose()
{
	m_IsConnect = false;
    m_bNeedNotifySessionOnLost = true;
	if (INVALID_SOCKET != m_Socket) {
		shutdown(m_Socket, SD_BOTH);
		closesocket(m_Socket);
		m_Socket = INVALID_SOCKET;
	}
}

void CSocket::DoSend(const void* _Data, UINT _Len, bool candrop)
{
    if (nullptr == _Data || _Len == 0) {
        return;
    }

    if (nullptr == m_SendBuf) {
        return;
    }

    if (!m_IsConnect) {
        return;
    }

    switch (m_DataType) {

    case DATA_TYPE_DEF:
        DoSend_Default(_Data, _Len);
        break;

    case DATA_TYPE_WS:
        DoSend_WebSocket(_Data, _Len);
        break;

    default:
        LOG_ERROR("Unhandled data type: %d", m_DataType);
        break;
    }
}

void CSocket::DoSend_Default(const void *_Data, UINT _Len)
{
    if (GetDataType() != DATA_TYPE_DEF) return;

    unsigned int _TotalLen = _Len + sizeof(unsigned int);
    if (_TotalLen > m_SendSize) {
        CLogger::GetInstance()->LogWarning("[%s:%d] data size bigger than buffer size %d", FUNC_LINE, _TotalLen);
        return;
    }

    DATA_CACHE &_Cache = m_SendDataCache;
    _Cache._Data = nullptr;
    _Cache._MaxLen = _TotalLen;
    _Cache._Len = _TotalLen;
    CBufManager::GetInstance()->GetBuffer(_Cache._Data, _Cache._MaxLen, true);
    if (nullptr != _Cache._Data) {
        memcpy(_Cache._Data, (char *)&_TotalLen, sizeof(unsigned int));
        if (m_Encrypt) {
            auto rc = m_aes.Encrypt((uint8_t *)_Data, _Len, (uint8_t *)_Cache._Data + sizeof(unsigned int));
            if (rc > 0) {
                m_SendCache.push_back(_Cache);
            }
            else {
                CLogger::GetInstance()->LogCritical("[%s:%d] Encrypt failed with error %d", FUNC_LINE, rc);
                CBufManager::GetInstance()->ReleaseBuffer(_Cache._Data, _Cache._MaxLen);
            }
        }
        else {
            memcpy(_Cache._Data + 4, _Data, _Len);
            m_SendCache.push_back(_Cache);
        }
    }
    else {
        CLogger::GetInstance()->LogWarning("[%s:%d] fetch send buff failed. _TotalLen=%d", FUNC_LINE, _TotalLen);
    }
}

void CSocket::DoSend_WebSocket(const void *_Data, UINT _Len)
{
    if (GetDataType() != DATA_TYPE_WS) return;

    if (!m_processor) {
        LOG_ERROR("m_processor is nullptr");
        return;
    }

    if (!m_msg_manager) {
        LOG_ERROR("m_msg_manager is nullptr");
        return;
    }

    auto in = m_msg_manager->get_message();
    in->set_opcode(websocketpp::frame::opcode::BINARY);

    auto totalLen = _Len + sizeof(uint32_t);
    auto &in_payload = in->get_raw_payload();
    in_payload.resize(totalLen);

    auto *raw = const_cast<char *>(in_payload.data());
    memcpy(raw, &totalLen, sizeof(uint32_t));

    auto rc = m_aes.Encrypt(reinterpret_cast<const uint8_t *>(_Data), _Len,
        reinterpret_cast<uint8_t *>(raw) + sizeof(uint32_t));
    if (rc <= 0) {
        LOG_ERROR("Encrypt failed");
        return;
    }

    auto out = m_msg_manager->get_message();
    auto ec = m_processor->prepare_data_frame(in, out);
    if (ec) {
        LOG_ERROR("prepare_data_frame failed with error %d", ec.value());
        return;
    }

    auto data = out->get_header();
    data += out->get_payload();
    SendDirectly(data.data(), data.size());
}

void CSocket::SendDirectly(const void *_Data, UINT _Len)
{
    if (!_Data || _Len == 0 || !m_SendBuf || !m_IsConnect) return;

    if (_Len > m_SendSize) {
        CLogger::GetInstance()->LogWarning("[%s:%d] data size bigger than buffer size %d", FUNC_LINE, _Len);
        return;
    }

    DATA_CACHE &_Cache = m_SendDataCache;
    _Cache._Data = nullptr;
    _Cache._MaxLen = _Len;
    _Cache._Len = _Len;
    CBufManager::GetInstance()->GetBuffer(_Cache._Data, _Cache._MaxLen, true);
    if (nullptr != _Cache._Data) {
        memcpy(_Cache._Data, _Data, _Len);
        m_SendCache.push_back(_Cache);
    }
    else {
        CLogger::GetInstance()->LogWarning("[%s:%d] fetch send buff failed. _TotalLen=%d", FUNC_LINE, _Len);
    }
}

bool CSocket::PostSend()
{
	if (!m_IsConnect) {
		return false;
	}

	if (nullptr == m_SendBuf || m_SendPos == 0) {
		return false;
	}

	if (m_SendingData) {
		return false;
	}

	g_SendMsgAll += 1;

	m_SendingData = true;
	m_IoDataSend._WsaBuf->buf = m_SendBuf;
	m_IoDataSend._WsaBuf->len = m_SendPos;
	ZeroMemory(&m_IoDataSend._OverLapped, sizeof(m_IoDataSend._OverLapped));
	DWORD _ByteSend = 0;
	if (0 != WSASend(m_Socket, m_IoDataSend._WsaBuf, 1, &_ByteSend, 0, &m_IoDataSend._OverLapped, nullptr)) {
		DWORD _Error = WSAGetLastError();
		if (WSA_IO_PENDING != _Error) {
			CLogger::GetInstance()->LogWarning("[%s:%d] PostSend failed Error:%d, Type=%d", FUNC_LINE, _Error, m_pSession ? m_pSession->GetType() : -1);
			OnSend(m_SendPos);
			return false;
		}
	}

	return true;
}

void CSocket::OnSend(UINT _Len)
{
	if (m_IsConnect) {
		if (nullptr != m_SendBuf) {
			m_SendMutex.Lock();
			if (_Len >= m_SendPos) {
				m_SendPos = 0;
			}
			else {
				m_SendPos -= _Len;
				memmove(m_SendBuf, m_SendBuf + _Len, m_SendPos);
				m_IoDataSend._WsaBuf->buf = m_SendBuf;
				m_IoDataSend._WsaBuf->len = m_SendPos;
			}
			m_SendMutex.Unlock();
			m_SendingData = false;
		}
	}
}

void CSocket::OnRecv(UINT _Len)
{
	g_RecvMsgAll += 1;
	if (!m_IsConnect) return;
    if (!m_RecvBuf) return;

	m_RecvPos += _Len;

	//接收缓冲区已满，但还没有装下一个完整包
	if (m_RecvPos > m_RecvSize) {
		CLogger::GetInstance()->LogCritical("[%s:%d] recv buff overflow", FUNC_LINE);
		if (m_pSession) {
			m_pSession->OnError(SOCK_ERROR_OVERFLOW);
		}
		return;
	}

    ParsePacks();
    PostRecv();
}

void CSocket::ParsePacks()
{
    switch (m_DataType) {

    case DATA_TYPE_DEF:
        ParsePacks_Default();
        break;

    case DATA_TYPE_HTTP:
        ParsePacks_HTTP();
        break;

    case DATA_TYPE_WS:
        ParsePacks_WebSocket();
        break;

    default:
        LOG_ERROR("Unhandled data type: %d", m_DataType);
        break;
    }
}

void CSocket::ParsePacks_Default()
{
    if (GetDataType() != DATA_TYPE_DEF) return;

    while (true) {
        //还未收完消息头
        if (m_RecvPos < sizeof(UINT)) {
            break;
        }
        UINT _MsgLen = *(UINT *)m_RecvBuf;

        if (_MsgLen < sizeof(UINT)) {
            m_RecvPos = 0;
            break;
        }

        //还未收完消息体
        if (m_RecvPos < _MsgLen) {
            break;
        }

        DATA_CACHE &_Cache = m_RecvDataCache;
        _Cache._Data = nullptr;
        _Cache._MaxLen = _MsgLen - sizeof(UINT);
        _Cache._Len = _MsgLen - sizeof(UINT);
        CBufManager::GetInstance()->GetBuffer(_Cache._Data, _Cache._MaxLen, true);
        if (nullptr != _Cache._Data) {
            if (m_Encrypt) {
                auto rc = m_aes.Decrypt((uint8_t *)m_RecvBuf + sizeof(UINT), _Cache._Len, (uint8_t *)_Cache._Data);
                if (rc > 0) {
                    m_RecvMutex.Lock();
                    m_RecvCache.push_back(_Cache);
                    m_RecvMutex.Unlock();
                }
                else {
                    CLogger::GetInstance()->LogCritical("[%s:%d] Decrypt failed with error %d", FUNC_LINE, rc);
                    CBufManager::GetInstance()->ReleaseBuffer(_Cache._Data, _Cache._MaxLen);
                }
            }
            else {
                memcpy(_Cache._Data, (uint8_t *)m_RecvBuf + sizeof(UINT), _Cache._Len);
                m_RecvMutex.Lock();
                m_RecvCache.push_back(_Cache);
                m_RecvMutex.Unlock();
            }
        }
        else {
            CLogger::GetInstance()->LogWarning("[%s:%d] fetch recv buff failed. _Len=%d", FUNC_LINE, _Cache._Len);
        }

        m_RecvPos -= _MsgLen;

        if (m_RecvPos < 0) {
            m_RecvPos = 0;
        }
        if (m_RecvPos > 0) {
            memmove(m_RecvBuf, m_RecvBuf + _MsgLen, m_RecvPos);
        }
    }
}

void CSocket::ParsePacks_HTTP()
{
    if (GetDataType() != DATA_TYPE_HTTP) return;

    namespace wspp = websocketpp;
    wspp::http::parser::request req;
    size_t processed = 0;

    try {
        processed = req.consume(m_RecvBuf, m_RecvPos);
    }
    catch (wspp::http::exception &e) {
        LOG_ERROR("parse exception: %s", e.what());
        m_RecvPos = 0;
        return;
    }

    if (!req.ready()) {
        if (m_RecvPos > 1024) m_RecvPos = 0;
        return;
    }

    if (wspp::processor::is_websocket_handshake(req)) {

        auto version = wspp::processor::get_websocket_version(req);
        InitWSProcessor(version);

        if (m_processor) {
            auto ec = m_processor->validate_handshake(req);

            if (ec) {
                LOG_WARN("validate_handshake failed with error %d", ec.value());
            }
            else {
                wspp::http::parser::response rsp;
                ec = m_processor->process_handshake(req, "", rsp);
                if (ec) {
                    LOG_WARN("process_handshake failed with error %d", ec.value());
                }
                else {
                    rsp.set_version("HTTP/1.1");
                    rsp.set_status(wspp::http::status_code::switching_protocols);
                    rsp.append_header("Sec-WebSocket-Protocol", "binary");
                    auto ans = rsp.raw();
                    SendDirectly(ans.c_str(), ans.length());
                    SetDataType(DATA_TYPE_WS);
                }
            }
        }
        else {
            LOG_ERROR("InitWSProcessor failed, version: %d", version);
        }
    }

    m_RecvPos -= processed;
    if (m_RecvPos < 0) m_RecvPos = 0;
    if (m_RecvPos > 0) {
        memmove(m_RecvBuf, m_RecvBuf + processed, m_RecvPos);
        ParsePacks();
    }
}

void CSocket::ParsePacks_WebSocket()
{
    if (GetDataType() != DATA_TYPE_WS) return;

    if (!m_processor) {
        LOG_ERROR("m_processor is nullptr");
        m_RecvPos = 0;
        return;
    }

    size_t processed = 0;

    while (processed < m_RecvPos) {

        websocketpp::lib::error_code ec;
        auto p = m_processor->consume(reinterpret_cast<uint8_t *>(m_RecvBuf) + processed, m_RecvPos - processed, ec);
        if (ec) {
            LOG_ERROR("consume failed with error code %d", ec.value());
            m_processor->reset_headers();
            if (p == 0) {
                m_RecvPos = 0;
                break;
            }
            else {
                processed += p;
                continue;
            }
        }

        processed += p;
        if (!m_processor->ready()) break;

        auto msg = m_processor->get_message();
        if (!msg) {
            LOG_ERROR("msg is nullptr");
        }
        else if (is_control(msg->get_opcode())) {
            // TODO: handle close opcode
            LOG_WARN("Unhandled opcode: %d", msg->get_opcode());
        }
        else {      // 数据
            const auto &payload = msg->get_payload();
            auto _MsgLen = payload.length();

            DATA_CACHE &_Cache = m_RecvDataCache;
            _Cache._Data = nullptr;
            _Cache._MaxLen = _MsgLen - sizeof(UINT);
            _Cache._Len = _MsgLen - sizeof(UINT);
            CBufManager::GetInstance()->GetBuffer(_Cache._Data, _Cache._MaxLen, true);
            if (nullptr != _Cache._Data) {
                auto rc = m_aes.Decrypt((uint8_t *)payload.data() + sizeof(UINT), _Cache._Len, (uint8_t *)_Cache._Data);
                if (rc > 0) {
                    m_RecvMutex.Lock();
                    m_RecvCache.push_back(_Cache);
                    m_RecvMutex.Unlock();
                }
                else {
                    LOG_ERROR("Decrypt failed with error %d", rc);
                    CBufManager::GetInstance()->ReleaseBuffer(_Cache._Data, _Cache._MaxLen);
                }
            }
            else {
                LOG_WARN("fetch recv buff failed. _Len=%d", _Cache._Len);
            }
        }
    }

    m_RecvPos -= processed;
    if (m_RecvPos < 0) m_RecvPos = 0;
    if (m_RecvPos > 0) memmove(m_RecvBuf, m_RecvBuf + processed, m_RecvPos);
}

void CSocket::InitWSProcessor(int version)
{
    using namespace websocketpp;

    if (m_processor) return;
    if (!m_msg_manager) m_msg_manager = lib::make_shared<msg_manager>();

    switch (version) {
    case 0:
        m_processor = lib::make_shared<processor::hybi00<ws_config>>(false, true, m_msg_manager);
        break;
    case 7:
        m_processor = lib::make_shared<processor::hybi07<ws_config>>(false, true, m_msg_manager, lib::ref(m_rng));
        break;
    case 8:
        m_processor = lib::make_shared<processor::hybi08<ws_config>>(false, true, m_msg_manager, lib::ref(m_rng));
        break;
    case 13:
        m_processor = lib::make_shared<processor::hybi13<ws_config>>(false, true, m_msg_manager, lib::ref(m_rng));
        break;
    default:
        break;
    }
}

bool CSocket::PostRecv()
{
	bool _Ret = false;
	if (m_IsConnect) {
		if ((nullptr != m_RecvBuf) && (m_RecvPos < m_RecvSize)) {
			_Ret = true;
			ZeroMemory(&m_IoDataRecv._OverLapped, sizeof(m_IoDataRecv._OverLapped));
			m_IoDataRecv._WsaBuf->buf = m_RecvBuf + m_RecvPos;
			m_IoDataRecv._WsaBuf->len = m_RecvSize - m_RecvPos;

			DWORD _Len = 0, _Flag = 0;
			if (0 != WSARecv(m_Socket, m_IoDataRecv._WsaBuf, 1, &_Len, &_Flag, &m_IoDataRecv._OverLapped, nullptr)) {
				DWORD _Error = WSAGetLastError();
				if (WSA_IO_PENDING != _Error) {
					_Ret = false;
					CLogger::GetInstance()->LogWarning("[%s:%d] PostRecv failed Error:%d Type=%d", FUNC_LINE, _Error,m_pSession? m_pSession->GetType() : -1);
				}
			}
		}
	}
	return _Ret;
}

bool CSocket::HandleIocpError(DWORD _Error)
{
	bool _Ret = false;
	if (WAIT_TIMEOUT == _Error) {
		if (!IsSocketAlive()) {
			CLogger::GetInstance()->LogWarning("[%s:%d] 检测到客户端超时退出", FUNC_LINE);
			OnError(_Error);
		}
		_Ret = true;
	}
	else if (ERROR_NETNAME_DELETED == _Error) {
		//对方应用程序在没有事先通知我关闭网络的情况下，退出
		CLogger::GetInstance()->LogWarning("[%s:%d] 检测到客户端关闭退出", FUNC_LINE);
		//OnLost();
		_Ret = true;
	}
	else if ((ERROR_CONNECTION_ABORTED == _Error) || (ERROR_OPERATION_ABORTED == _Error)) {
		//ERROR_CONNECTION_ABORTED ： 由本地系统终止网络连接。说白了就是主动关闭了连接
		//ERROR_OPERATION_ABORTED ： 由于线程退出或应用程序请求，已放弃 I/O 操作。说白了就是我自己主动关闭了网络
		OnLost();
		_Ret = true;
	}
	else if (WSA_IO_PENDING == _Error) {
		_Ret = true;
	}

	return _Ret;
}

bool CSocket::IsSocketAlive()
{
	bool _Ret = false;
	if (INVALID_SOCKET != m_Socket) {
		if (-1 != send(m_Socket, "", 0, 0)) {
			_Ret = true;
		}
	}
	return _Ret;
}

void CSocket::SetLocalIpPort(std::string& _LocalIP, UINT _LocalPort)
{
	m_LocalIP = _LocalIP; 
	m_LocalPort = _LocalPort;
}

void CSocket::SetRemoteIpPort(std::string& _RemoteIP, UINT _RemotePort)
{
	m_RemoteIP = _RemoteIP; 
	m_RemotePort = _RemotePort;
}

void CSocket::SetSession(ISession* _pSession)
{
	m_pSession = _pSession;
}
/*
void CSocket::ParseIpAndPort()
{
	if (INVALID_SOCKET != m_Socket) {
		sockaddr_in RemoteAddr;
		sockaddr_in LocalAddr;
		int32_t nRemoteAddrLen = sizeof(sockaddr_in);
		int32_t nLocalAddrLen = sizeof(sockaddr_in);

		if (0 == getpeername(m_Socket, (struct sockaddr*)&RemoteAddr, &nRemoteAddrLen)) {
			m_RemoteIP = inet_ntoa(RemoteAddr.sin_addr);
			m_RemotePort = ntohs(RemoteAddr.sin_port);
		}

		if (0 == getsockname(m_Socket, (struct sockaddr*)&LocalAddr, &nLocalAddrLen)) {
			m_LocalIP = inet_ntoa(LocalAddr.sin_addr);
			m_LocalPort = ntohs(LocalAddr.sin_port);
		}
	}
}
*/
void CSocket::OnError(DWORD _ErrorCode)
{
	if (m_pSession) {
		m_pSession->OnError(_ErrorCode);
	}
	DoClose();
}

void CSocket::IncPostRecv()
{
	InterlockedIncrement((LONG*)&m_dwPostRecv);
}

void CSocket::DecPostRecv()
{
	InterlockedDecrement((LONG*)&m_dwPostRecv);
}

uint32_t CSocket::GetPostRecv()
{
	return InterlockedExchange((LONG*)&m_dwPostRecv, m_dwPostRecv);
}

void CSocket::LogDebugInfo(DEBUG_DATA& debugData)
{
	debugData.sendCache += m_SendCache.size();
	for (auto &data : m_SendCache) {
		debugData.sendMem += data._Len;
	}
	
	m_RecvMutex.Lock();
	debugData.recvCache += m_RecvCache.size();
	for (auto &data : m_RecvCache) {
		debugData.recvMem += data._Len;
	}
	m_RecvMutex.Unlock();

	if (debugData.sendPeak < m_SendPeak) debugData.sendPeak = m_SendPeak;
	if (debugData.recvPeak < m_RecvPeak) debugData.recvPeak = m_RecvPeak;
}

