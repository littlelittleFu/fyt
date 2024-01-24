#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>


class ISession;

struct SessionContext
{
    uint32_t                nSessionID              = 0;
    uint32_t                nToken                  = 0;
    std::string             sRandKey;

    std::string             sUserName;
    uint32_t                nIP                     = 0;
    std::string             sHardwareID;
    uint64_t                nPlayerGUID             = 0;
    uint64_t                nRoleGUID               = 0;
    uint8_t                 nOnlineState            = 0;

    uint64_t                nLastSelectedRole       = 0;
    uint32_t                nReserveContextTimerID  = 0;
};

typedef std::shared_ptr<SessionContext> SPSessionContext;
typedef std::map<uint32_t, SPSessionContext> SessionID2ContextMap;

class SessionContextMgr
{
    DECL_SINGLETON(SessionContextMgr)

public:
    void AddSessionContext(SPSessionContext& spUserContext);

    SPSessionContext GetSessionContext(uint32_t nSessionID);
    SPSessionContext GetSessionContext(uint64_t nPlayerGUID);
    SPSessionContext GetSessionContext(const char *pRandKey);

    void DelSessionContext(uint32_t nSessionID);

    void SetLS2GSSessionID(uint32_t nID) { mLS2GSSessionID = nID; }
    void SetCS2GSSessionID(uint32_t nID) { mCS2GSSessionID = nID; }
    void SetMS2GSSessionID(uint32_t nID) { mMS2GSSessionID = nID; }
    uint32_t GetLS2GSSessionID() { return mLS2GSSessionID; }
    uint32_t GetCS2GSSessionID() { return mCS2GSSessionID; }
    uint32_t GetMS2GSSessionID() { return mMS2GSSessionID; }

    SessionID2ContextMap& GetSessionID2ContextMap() { return m_SessionID2ContextMap; };
    uint32_t GetOnlineNum();
    uint32_t GetTotalNum() { return m_SessionID2ContextMap.size(); }

private:
    SessionContextMgr();
    ~SessionContextMgr();

private:
    SessionID2ContextMap m_SessionID2ContextMap;

    uint32_t mLS2GSSessionID = 0;
    uint32_t mCS2GSSessionID = 0;
    uint32_t mMS2GSSessionID = 0;
};
