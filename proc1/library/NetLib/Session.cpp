#include "pch.h"
#include "Session.h"
#include "CLogger.h"
#include "IProtoMgr.h"

#define HEART_BEAT_INTERVAL		9000
#define MAX_PKG_SIZE			1024 * 1024 * 4

Session::Session() : m_Type(0),m_Param(0)
{
	SetInvalid(false);
	m_Socket.SetSession(this);
	m_nHeartBeatTimeOut = 0;
	m_nHeartBeatPulse = 0;
    m_DestroyDelay = 0;
}

Session::~Session()
{

}

INT Session::GetType()
{
	return m_Type;
}

void Session::SetType(INT _Type)
{
	m_Type = _Type;
}

INT Session::GetParam()
{
	return m_Param;
}

void Session::SetParam(INT _Param)
{
	m_Param = _Param;
}

void Session::SetEncrypt(bool _Encrypt)
{
    m_Socket.SetEncrypt(_Encrypt);
}

UINT Session::GetID()
{
	return m_Socket.GetID();
}

void Session::OnEstablish(SOCKET _Socket)
{
	m_Socket.OnEstablish(_Socket);
}


void Session::OnLost()
{

}

void Session::HandleMessage(void* _pData, UINT _Len)
{
    if (!_pData || _Len == 0) {
        LOG_ERROR("Invalid param. _pData: %p, _Len: %u", _pData, _Len);
        return;
    }
	static char recv_buff[MAX_PKG_SIZE];
	char* pOut = recv_buff;
	int len = IProtoMgr::GetInstance()->DecodeMsg(_pData, pOut, _Len);
	if (len > 0) {
		uint16_t moduleid = *(uint16_t*)_pData;
		uint16_t protoid = *((uint16_t*)_pData + 1);
		OnMessage(moduleid, protoid, pOut);
	}
}

void Session::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{

}

void Session::OnError(DWORD _ErrorCode)
{
}

void Session::OnUpdate(UINT _Delta)
{
	m_Socket.OnUpdate(_Delta);

	
}

bool Session::SendPkg(void* _pData, UINT _Len, bool candrop)
{
	static char send_buff[MAX_PKG_SIZE];
	char* pOut = send_buff;
	int len = IProtoMgr::GetInstance()->EncodeMsg(_pData, pOut, MAX_PKG_SIZE);
	if (len <= 0) return false;
	m_Socket.DoSend(pOut, len, candrop);
    return true;
}

std::string Session::GetLocalIp()
{
	return m_Socket.GetLocalIp();
}

std::string Session::GetRemoteIp()
{
	return m_Socket.GetRemoteIp();
}

UINT Session::GetLocalPort()
{
	return m_Socket.GetLocalPort();
}

UINT Session::GetRemotePort()
{
	return m_Socket.GetRemotePort();
}

bool Session::IsInvalid()
{
	return m_Invalid;
}

void Session::SetInvalid(bool _Value)
{
	m_Invalid = _Value;
}

void Session::DoClose()
{
	m_Socket.DoClose();
}

void Session::SetIpInfo(std::string& _LocalIp, UINT _LocalPort, std::string& _RemoteIp, UINT _RemotePort)
{
	m_Socket.SetLocalIpPort(_LocalIp, _LocalPort);
	m_Socket.SetRemoteIpPort(_RemoteIp, _RemotePort);
}

void Session::OnHeartBeat()
{
	m_nHeartBeatTimeOut = 0;
    m_nHeartBeatPulse = 0;
}

void Session::DoHeartBeat()
{
	//此函数子类必须实现
}

void Session::LogDebugInfo(DEBUG_DATA& debugData)
{
	m_Socket.LogDebugInfo(debugData);
}

bool Session::CanBeDestroyed(UINT _Delta)
{
#ifdef _WIN32
    return IsInvalid();
#else
    if (!IsInvalid()) return false;
    m_DestroyDelay += _Delta;
    return (m_DestroyDelay > 10000);
#endif
}