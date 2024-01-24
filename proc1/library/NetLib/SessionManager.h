#pragma once
#include "Type.h"
#include "ISession.h"
#include <functional>
#include <map>
#include <list>
#include <memory>
#include "CMutex.h"

struct SessionInfo
{
    int32_t         nType           = 0;
    int32_t         nParam          = 0;
    bool            bAddFront       = false;
    bool            bEncrypt        = true;

    std::string     sLocalIP;
    uint32_t        nLocalPort      = 0;
    std::string     sRomoteIP;
    uint32_t        nRomotePort     = 0;

    SOCKET          sock            = INVALID_SOCKET;
};

typedef std::unique_ptr<SessionInfo> UPSessionInfo;
typedef std::list<UPSessionInfo> SessionInfoList;

class SessionManager
{
public:
	SessionManager();
	~SessionManager();

	ISession* CreateSession(INT _Type, INT _Param = 0, bool _AddFront = false);
	void RemoveSession(ISession* _pSession);
    void RemoveAllSession();
    bool CanRemoveSession(ISession* _pSession, UINT _Delta);
	ISession* GetSessionByType(INT _Type);
	ISession* GetSessionByID(UINT _ID);
    const ISessionMap* GetAllSessionByType(INT type);
    int GetSessionNum(int type);
    void CacheSessionInfo(UPSessionInfo upSessionInfo);
    void CacheSessionInfo(int32_t sessionType, int32_t sessionParam, bool encrypt,
        bool addFront, const std::string &localIP, uint32_t localPort,
        const std::string &remoteIP, uint32_t remotePort, SOCKET sock);

	void OnUpdate(UINT _Delta);

    void LogDebugInfo(DEBUG_DATA& debugData);

	DECLARE_INSTANCE(SessionManager);
private:
    bool CheckTypeInvalid(uint16_t type) { return type >= SESSION_TYPE_COUNT; }
private:
	std::map<INT, std::function<ISession*()>> m_SessionFunc;
    ISessionMapVec m_SessionList;
    SessionInfoList m_SessionInfoList;
    CMutex m_Mutex;
};
