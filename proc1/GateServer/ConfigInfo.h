#pragma once

#include <string>
#include "IConfigInfo.h"

class ConfigInfo : public IConfigInfo
{
    DECL_SINGLETON(ConfigInfo)

public:
    bool IsLSConfigValid();
    bool IsMSConfigValid();
    bool IsCSConfigValid();
    bool IsLogConfigValid();
    // 实现
    virtual uint32_t GetCurAgentId() { return m_agentId; }
    virtual uint32_t GetCurAreaId() { return m_areaId; }
    virtual uint32_t GetCurAreaServerId() { return m_areaServerId; }
    virtual uint32_t GetCurServerId() { return m_serverId; }
private:
    ConfigInfo();
    ~ConfigInfo();

    void Init();

public:
    uint32_t m_nConnCheckTimerInterval  = 10000;
    uint32_t m_nNetLibThreadNum         = 2;

    std::string m_sListenIp             = "0.0.0.0";
    uint32_t m_nListenPort              = 16990;
    uint32_t m_nListenPortWS            = 16880;

    std::string m_sServiceServerIp      = "127.0.0.1";
    uint32_t m_nServiceServerPort       = 19992;

    std::string m_sLoginServerIP;
    uint32_t m_nLoginServerPort         = 0;

    std::string m_sMapServerIP;
    uint32_t m_nMapServerPort           = 0;

    std::string m_sLogServerIP;
    uint32_t m_nLogServerPort           = 0;

    std::string m_sCenterServerIP;
    uint32_t m_nCenterServerPort        = 0;

    int32_t m_bLogLevel                 = log_level_normal;

    uint32_t m_nMaxClientNum            = 0;
    std::string m_sPlatformDomain       = "http://csuser.guanying.xin";


    uint32_t    m_agentId               = 0;    // 代理ID
    uint32_t    m_areaId                = 0;    // 区ID
    uint32_t    m_areaServerId          = 0;    // 区服ID
    uint32_t    m_serverId              = 3;    // 服务器ID
    uint32_t m_nSessCtxRsvTime          = 30;       // 秒
};
