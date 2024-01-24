#include "pch.h"
#include "SessionManager.h"
#include <algorithm>

IMPLEMENT_INSTANCE(SessionManager);

SessionManager::SessionManager()
{

	m_SessionList.resize(SESSION_TYPE_COUNT);
}

SessionManager::~SessionManager()
{

}

ISession* SessionManager::CreateSession(INT _Type, INT _Param, bool _AddFront)
{
	ISession* _pSession = NULL;
	if (CheckTypeInvalid(_Type)) return _pSession;

	ISessionFactory* _pFactory = ISessionFactory::GetInstance();
	if (_pFactory) {
		_pSession = _pFactory->CreateSession(_Type, _Param);
		if (_pSession) {
			m_SessionList[_Type].emplace(_pSession->GetID(), _pSession);
		}
	}
	return _pSession;
}

void SessionManager::RemoveSession(ISession* _pSession)
{
	auto *sessionFactory = ISessionFactory::GetInstance();
	if (!sessionFactory) return;

	uint16_t type = _pSession->GetType();
	uint32_t id = _pSession->GetID();
	if (CheckTypeInvalid(type)) return;

	auto _Iter = m_SessionList[type].find(id);
	if (_Iter == m_SessionList[type].end()) return;

	sessionFactory->RemoveSession(_pSession);
	m_SessionList[type].erase(_Iter);
}

void SessionManager::RemoveAllSession()
{
    auto *sessionFactory = ISessionFactory::GetInstance();
    if (!sessionFactory) return;

	for (uint16_t i = 0; i < SESSION_TYPE_COUNT; ++i)
	{
		for (auto& session : m_SessionList[i])
			sessionFactory->RemoveSession(session.second);

		m_SessionList[i].clear();
	}
}

ISession* SessionManager::GetSessionByType(INT _Type) 
{
	ISession* _pSession = NULL;
	if (CheckTypeInvalid(_Type)) return _pSession;
	if (m_SessionList[_Type].empty()) return _pSession;

	return m_SessionList[_Type].begin()->second;
}

ISession* SessionManager::GetSessionByID(UINT _ID)
{
	static std::vector<uint16_t> priority =
	{
		(uint16_t)SESSION_TYPE_MS2GS,
		(uint16_t)SESSION_TYPE_GS2CL,
	};
	bool bit[SESSION_TYPE_COUNT] = { 0 };
	for (auto _Iter = priority.begin(); _Iter != priority.end(); ++_Iter)
	{
		if (CheckTypeInvalid(*_Iter)) continue;

		bit[*_Iter] = true;
		auto iter = m_SessionList[*_Iter].find(_ID);
		if (iter != m_SessionList[*_Iter].end())
		{
			return iter->second;
		}
	}
	for (uint16_t i = 0; i < SESSION_TYPE_COUNT; ++i)
	{
		if (bit[i]) continue;

		auto iter = m_SessionList[i].find(_ID);
		if (iter != m_SessionList[i].end())
		{
			return iter->second;
		}
	}
	return NULL;
}

const ISessionMap* SessionManager::GetAllSessionByType(INT type)
{
	if (CheckTypeInvalid(type)) return nullptr;
	return &m_SessionList[type];
}

int SessionManager::GetSessionNum(int type)
{
	if (CheckTypeInvalid(type)) return 0;

	return m_SessionList[type].size();
}

void SessionManager::CacheSessionInfo(UPSessionInfo upSessionInfo)
{
    CLockGuard lockGuard(m_Mutex);
    m_SessionInfoList.push_back(std::move(upSessionInfo));
}

void SessionManager::CacheSessionInfo(int32_t sessionType, int32_t sessionParam,
        bool encrypt, bool addFront, const std::string &localIP, uint32_t localPort,
        const std::string &remoteIP, uint32_t remotePort, SOCKET sock)
{
    UPSessionInfo upSessionInfo = std::make_unique<SessionInfo>();
    upSessionInfo->nType = sessionType;
    upSessionInfo->nParam = sessionParam;
    upSessionInfo->bEncrypt = encrypt;
    upSessionInfo->bAddFront = addFront;
    upSessionInfo->sLocalIP = localIP;
    upSessionInfo->nLocalPort = localPort;
    upSessionInfo->sRomoteIP = remoteIP;
    upSessionInfo->nRomotePort = remotePort;
    upSessionInfo->sock = sock;

    CacheSessionInfo(std::move(upSessionInfo));
}

void SessionManager::OnUpdate(UINT _Delta)
{
	ISessionFactory* _pFactory = ISessionFactory::GetInstance();
	if (_pFactory) {

        m_Mutex.Lock();
        for (auto &it : m_SessionInfoList)
        {
            ISession* pSession = CreateSession(it->nType, it->nParam, it->bAddFront);
            if (!pSession) continue;

            pSession->SetIpInfo(it->sLocalIP, it->nLocalPort, it->sRomoteIP, it->nRomotePort);
            pSession->SetEncrypt(it->bEncrypt);
            pSession->OnEstablish(it->sock);
        }
        m_SessionInfoList.clear();
        m_Mutex.Unlock();

		for (uint16_t i = 0; i < SESSION_TYPE_COUNT; ++i)
		{
			for (auto _Iter = m_SessionList[i].begin(); _Iter != m_SessionList[i].end();) {
				ISession* _pSession = _Iter->second;

				if (CanRemoveSession(_pSession, _Delta)) {
					_Iter = m_SessionList[i].erase(_Iter);
					_pFactory->RemoveSession(_pSession);
				}
				else {
					_pSession->OnUpdate(_Delta);
					++_Iter;
				}
			}
		}
	}
}

bool SessionManager::CanRemoveSession(ISession* _pSession, UINT _Delta)
{
    if (!_pSession) return true;
    return _pSession->CanBeDestroyed(_Delta);
}

void SessionManager::LogDebugInfo(DEBUG_DATA& debugData)
{
	for (uint16_t i = 0; i < SESSION_TYPE_COUNT; ++i)
	{
		for (auto& it : m_SessionList[i])
		{
			if (it.second) it.second->LogDebugInfo(debugData);
		}
	}
}