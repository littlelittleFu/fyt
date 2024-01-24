#pragma once

#include <string>
#include "IConfigInfo.h"

class ConfigInfo : public IConfigInfo
{
    DECL_SINGLETON(ConfigInfo)

private:
    ConfigInfo();
    ~ConfigInfo();

    void Init();

    virtual uint32_t GetCurAgentId() { return m_agentId; }
    virtual uint32_t GetCurAreaId() { return m_areaId; }
    virtual uint32_t GetCurAreaServerId() { return m_areaServerId; }
    virtual uint32_t GetCurServerId() { return m_serverId; }
public:
    uint32_t m_nConnCheckTimerInterval  = 10000;
    uint32_t m_nNetLibThreadNum         = 2;

    std::string m_sListenIp             = "0.0.0.0";
    uint32_t m_nListenPort              = 13990;

    std::string m_sServiceServerIp      = "127.0.0.1";
    uint32_t m_nServiceServerPort       = 19995;

    std::string m_sLocalMachineIp       = "127.0.0.1";

    std::string m_sMySQLServAddr        = "127.0.0.1";
    uint32_t m_nMySQLServPort           = 3306;
    std::string m_sMySQLServUserName    = "root";
    std::string m_sMySQLServPassword    = "123456";

    std::string m_sMySQLServAddr_GAME = "127.0.0.1";
    uint32_t m_nMySQLServPort_GAME = 3306;
    std::string m_sMySQLServUserName_GAME = "root";
    std::string m_sMySQLServPassword_GAME = "123456";

    std::string m_sMySQLServDBName      = "log";
    std::string m_sMySQLGameServDBName  = "game";
    std::string m_sVersionKeyName       = "Version";

    int32_t m_bLogLevel                 = log_level_normal;
    std::string m_sPlatformDomain       = "http://csuser.guanying.xin";


    uint32_t    m_agentId               = 0;    // 代理ID
    uint32_t    m_areaId                = 0;    // 区ID
    uint32_t    m_areaServerId          = 0;    // 区服ID
    uint32_t    m_serverId              = 6;    // 服务器ID
};
