#include "stdafx.h"
#include "SessionContextMgr.h"

IMPL_SINGLETON(SessionContextMgr)

SessionContextMgr::SessionContextMgr()
{

}

SessionContextMgr::~SessionContextMgr()
{

}

void SessionContextMgr::AddSessionContext(SPSessionContext& spUserContext)
{
    m_SessionID2ContextMap[spUserContext->nSessionID] = spUserContext;
}

SPSessionContext SessionContextMgr::GetSessionContext(uint32_t nSessionID)
{
    auto it = m_SessionID2ContextMap.find(nSessionID);
    return (it != m_SessionID2ContextMap.end()) ? it->second : nullptr;
}

SPSessionContext SessionContextMgr::GetSessionContext(uint64_t nPlayerGUID)
{
    for (auto &it : m_SessionID2ContextMap)
        if (it.second->nPlayerGUID == nPlayerGUID)
            return it.second;

    return nullptr;
}

SPSessionContext SessionContextMgr::GetSessionContext(const char* pRandKey)
{
    if (!pRandKey) return nullptr;

    for (auto& it : m_SessionID2ContextMap)
        if (strcmp(it.second->sRandKey.c_str(), pRandKey) == 0)
            return it.second;

    return nullptr;
}

void SessionContextMgr::DelSessionContext(uint32_t nSessionID)
{
    m_SessionID2ContextMap.erase(nSessionID);
}

uint32_t SessionContextMgr::GetOnlineNum()
{
    uint32_t num = 0;

    for (const auto &it : m_SessionID2ContextMap) {
        const auto &context = it.second;
        if (context->nOnlineState == online_state_logged_in)
            num += 1;
    }

    return num;
}
