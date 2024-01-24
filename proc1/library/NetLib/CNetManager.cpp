#include "pch.h"
#include "CNetManager.h"
#include "CListener.h"
#include "SessionManager.h"
#include "CBufManager.h"
#include "CLogger.h"
#include "Config.h"

#ifdef _WIN32
#include "CIocpCtrl.h"
#define CNetCtrl CIocpCtrl
#else
#include "CEpollCtrl.h"
#define CNetCtrl CEpollCtrl
#endif


IMPLEMENT_INSTANCE(CNetManager)

CNetManager::CNetManager()
{

}

CNetManager::~CNetManager()
{
	
}

void CNetManager::Init(uint32_t nThreadNum)
{
	CNetCtrl::GetInstance()->Init(nThreadNum);
}

void CNetManager::UnInit()
{
	CNetCtrl::GetInstance()->UnInit();

	for (auto _Iter = m_Listeners.begin(); _Iter != m_Listeners.end(); _Iter++) {
		if ((*_Iter)) {
			(*_Iter)->Stop();
			delete (*_Iter);
		}
	}

	m_Listeners.clear();

    SessionManager::GetInstance()->RemoveAllSession();
}

bool CNetManager::AddListener(std::string _Ip, UINT _Port, INT _Type, INT _Param, bool _Encrypt)
{
	bool _Ret = false;
	CListener* _pListener = new CListener;
	if (_pListener) {
		m_Listeners.push_back(_pListener);
		_pListener->SetType(_Type);
        _pListener->SetParam(_Param);
        _pListener->SetEncrypt(_Encrypt);
		_Ret = _pListener->Start(_Ip, _Port);
	}

	return _Ret;
}

bool CNetManager::AddConnector(std::string _Ip, UINT _Port, INT _Type,INT _Param, bool _Encrypt)
{
	m_ConnectCtrl.AddConnector(_Ip, _Port, _Type, _Param, _Encrypt);
	return true;
}

void CNetManager::RemoveSession(ISession* _pSession)
{
	SessionManager::GetInstance()->RemoveSession(_pSession);
}

ISession* CNetManager::GetSessionByType(INT _Type)
{
	return SessionManager::GetInstance()->GetSessionByType(_Type);
}

ISession* CNetManager::GetSessionByID(UINT _ID)
{
	return SessionManager::GetInstance()->GetSessionByID(_ID);
}

const ISessionMap* CNetManager::GetAllSessionByType(INT type)
{
    return SessionManager::GetInstance()->GetAllSessionByType(type);
}

void CNetManager::OnUpdate(UINT _Delta)
{
	CBufManager::GetInstance()->OnUpdate(_Delta);
	SessionManager::GetInstance()->OnUpdate(_Delta);
}

void CNetManager::SetLogFunction(std::function<void(const char*,int)> _Func)
{
	CLogger::GetInstance()->SetLogFunction(_Func);
}

void CNetManager::SetLogLevel(int32_t logLevel)
{
	g_LogLevel = logLevel;
}

void CNetManager::LogDebugInfo(DEBUG_DATA& debugData)
{
	SessionManager::GetInstance()->LogDebugInfo(debugData);
	CBufManager::GetInstance()->LogDebugInfo(debugData);
}