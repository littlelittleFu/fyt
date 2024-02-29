#include"sessionMgr.h"

SessionMgr* SessionMgr::instance = nullptr;

void SessionMgr::CacheSessionInfo(UPSessionInfo upSessionInfo)
{
    CLockGuard lockGuard(m_Mutex);
    m_SessionInfoList.push_back(std::move(upSessionInfo));
}

void SessionMgr::CacheSessionInfo(int32_t sessionType, int32_t sessionParam, bool addFront,
    const std::string& localIP, uint32_t localPort, const std::string& remoteIP,
    uint32_t remotePort, SOCKET sock)
{
    UPSessionInfo upSessionInfo = std::make_unique<SessionInfo>();
    upSessionInfo->nType = sessionType;
    upSessionInfo->nParam = sessionParam;
    upSessionInfo->bAddFront = addFront;
    upSessionInfo->sLocalIP = localIP;
    upSessionInfo->nLocalPort = localPort;
    upSessionInfo->sRomoteIP = remoteIP;
    upSessionInfo->nRomotePort = remotePort;
    upSessionInfo->sock = sock;

    CacheSessionInfo(std::move(upSessionInfo));
}