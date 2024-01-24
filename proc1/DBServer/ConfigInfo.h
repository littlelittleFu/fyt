#pragma once

#include <string>
#include "IConfigInfo.h"

class ConfigInfo : public IConfigInfo
{
    DECL_SINGLETON(ConfigInfo)
public:
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
    void AssignDefaultValue();

public:
    uint32_t m_nConnCheckTimerInterval  = 10000;
    uint32_t m_nNetLibThreadNum         = 2;

    std::string m_sListenIp             = "0.0.0.0";
    uint32_t m_nListenPort              = 15990;

    std::string m_sServiceServerIp      = "127.0.0.1";
    uint32_t m_nServiceServerPort       = 19993;

    std::string m_sLocalMachineIp       = "127.0.0.1";

    std::string m_sMySQLServAddr        = "127.0.0.1";
    uint32_t m_nMySQLServPort           = 3306;
    std::string m_sMySQLServUserName    = "root";
    std::string m_sMySQLServPassword    = "123456";
    std::string m_sMySQLServDBName      = "game";
    std::string m_sMySQLGlobalServDBName= "global";
    std::string m_sMySQLLogServDBName   = "log";
    std::string m_sAgentAreaServerIdStr = "";

    std::string m_sLogServerIP;
    uint32_t m_nLogServerPort           = 0;

    int32_t m_bLogLevel                 = log_level_normal;
    std::string m_sGameCfgFolderPath;
    std::string m_sPlatformDomain       = "http://csuser.guanying.xin";

    uint32_t    m_agentId               = 0;    // 代理ID
    uint32_t    m_areaId                = 0;    // 区ID
    uint32_t    m_areaServerId          = 0;    // 区服ID
    uint32_t    m_serverId              = 5;    // 服务器ID
};
