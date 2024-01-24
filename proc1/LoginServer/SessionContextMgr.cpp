#include "stdafx.h"
#include "SessionContextMgr.h"



IMPL_SINGLETON(SessionContextMgr)

SessionContextMgr::SessionContextMgr()
{

}

SessionContextMgr::~SessionContextMgr()
{

}

void SessionContextMgr::AddSessionContext(SPSessionContext& spSessionContext)
{
    uint64_t nKey = Tools::MakeQWORD(spSessionContext->nGateServSessionID, spSessionContext->nClientSessionID);
    m_SessionContextMap[nKey] = spSessionContext;
}

SPSessionContext SessionContextMgr::GetSessionContext(uint64_t& nKey)
{
    const auto &it = m_SessionContextMap.find(nKey);
    return (it != m_SessionContextMap.end()) ? it->second : nullptr;
}

SPSessionContext SessionContextMgr::GetSessionContext(uint32_t& nToken)
{
    for (auto it = m_SessionContextMap.begin(); it != m_SessionContextMap.end();++it) {
        if (it->second->nToken == nToken) {
            return it->second;
        }
    }
    return nullptr;
}

SPSessionContext SessionContextMgr::GetSessionContextByPlayerGUID(uint64_t nPlayerGUID)
{
    for (const auto &it : m_SessionContextMap)
        if (it.second->nPlayerGUID == nPlayerGUID)
            return it.second;

    return nullptr;
}

void SessionContextMgr::DelSessionContext(uint64_t& nKey)
{
    m_SessionContextMap.erase(nKey);
}

void SessionContextMgr::DelSessionContext(const char* pUserName)
{
    if (nullptr != pUserName) {
        for (auto it = m_SessionContextMap.begin(); it != m_SessionContextMap.end(); ++it) {
            if (strcmp(it->second->sUserName.c_str(), pUserName) == 0) {
                m_SessionContextMap.erase(it);
                break;
            }
        }
    }
}

void SessionContextMgr::DelSessionContext(SPSessionContext sessionContext)
{
    if (nullptr != sessionContext) {
        uint64_t nKey = Tools::MakeQWORD(sessionContext->nGateServSessionID, sessionContext->nClientSessionID);
        DelSessionContext(nKey);
    }
}

void SessionContextMgr::GetSessionInfoByIP(std::vector<SPSessionContext>& vec, uint32_t ip)
{
    for(auto & i:m_SessionContextMap)
    {
        if (i.second != nullptr && i.second->nIP == ip)
        {
            vec.push_back(i.second);
        }
    }
}

SPSessionContext SessionContextMgr::GetSessionContext(const char *pUserName)
{
    if (!pUserName) return nullptr;

    for (const auto &it : m_SessionContextMap)
        if (strcmp(it.second->sUserName.c_str(), pUserName) == 0)
            return it.second;

    return nullptr;
}

void SessionContextMgr::DelAllContextOfGateServSessionID(uint32_t nGateServSessionID)
{
    for (auto it = m_SessionContextMap.begin(); it != m_SessionContextMap.end();) {
        if (it->second->nGateServSessionID == nGateServSessionID) {
            it = m_SessionContextMap.erase(it);
        }
        else {
            it++;
        }
    }
}
