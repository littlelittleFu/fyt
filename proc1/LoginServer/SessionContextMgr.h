#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>


class ISession;

struct SessionContext
{
    uint32_t                nGateServSessionID      = 0;
    uint32_t                nClientSessionID        = 0;

    uint32_t                nToken                  = 0;
    std::string             sRandKey;

    std::string             sUserName;
    std::string             sPassword;
    uint32_t                nIP                     = 0;
    std::string             sHardwareID;
    uint64_t                nPlayerGUID             = 0;

    uint8_t                 nOnlineState            = 0;

    // 三方登录数据
    std::string             sChannel;
    uint32_t                nGameID                 = 0;
    std::string             sPlatformToken;
};

typedef std::shared_ptr<SessionContext> SPSessionContext;
typedef std::map<uint64_t, SPSessionContext> SessionContextMap;

class SessionContextMgr
{
    DECL_SINGLETON(SessionContextMgr)

public:
    void AddSessionContext(SPSessionContext& spSessionContext);

    void DelSessionContext(uint64_t& nKey);
    void DelSessionContext(const char* pUserName);
    void DelSessionContext(SPSessionContext sessionContext);
    void GetSessionInfoByIP(std::vector<SPSessionContext>&vec,uint32_t ip);

    SPSessionContext GetSessionContext(uint64_t &nKey);
    SPSessionContext GetSessionContext(uint32_t &nToken);
    SPSessionContext GetSessionContext(const char *pUserName);
    SPSessionContext GetSessionContextByPlayerGUID(uint64_t nPlayerGUID);

    void DelAllContextOfGateServSessionID(uint32_t nGateServSessionID);

private:
    SessionContextMgr();
    ~SessionContextMgr();

private:
    SessionContextMap m_SessionContextMap;
};
