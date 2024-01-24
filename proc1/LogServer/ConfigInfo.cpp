#include "stdafx.h"
#include "ConfigInfo.h"
#include "IFileHelper.h"
#include "ILogHelper.h"
IMPL_SINGLETON(ConfigInfo)

ConfigInfo::ConfigInfo()
{
    Init();
}

ConfigInfo::~ConfigInfo()
{

}

void ConfigInfo::Init()
{
    std::string sConfigFilePath = IFileHelper::GetInstance()->GetConfigFilePath();
    LOG_NORMAL("CONFIG PATH %s",sConfigFilePath.c_str());
    const char* pAppName = "LogServer";

    inifile::IniFile ini;
    if (ini.Load(sConfigFilePath) != 0) return;

    ini.GetIntValue(pAppName, "ConnCheckTimerInterval", (int *)&m_nConnCheckTimerInterval);
    ini.GetIntValue(pAppName, "NetLibThreadNum", (int *)&m_nNetLibThreadNum);
    ini.GetStringValue(pAppName, "ListenIP", &m_sListenIp);
    ini.GetIntValue(pAppName, "ListenPort", (int *)&m_nListenPort);
    ini.GetStringValue(pAppName, "ServiceServerIP", &m_sServiceServerIp);
    ini.GetIntValue(pAppName, "ServiceServerPort", (int *)&m_nServiceServerPort);
    ini.GetStringValue(pAppName, "LocalMachineIP", &m_sLocalMachineIp);
    ini.GetStringValue(pAppName, "MySQLServAddr", &m_sMySQLServAddr);
    ini.GetIntValue(pAppName, "MySQLServPort", (int *)&m_nMySQLServPort);
    ini.GetStringValue(pAppName, "MySQLServUserName", &m_sMySQLServUserName);
    ini.GetStringValue(pAppName, "MySQLServPassword", &m_sMySQLServPassword);
    ini.GetStringValue(pAppName, "MySQLServDBName", &m_sMySQLServDBName);
    ini.GetIntValue(pAppName, "LogLevel", (int *)&m_bLogLevel);
    ini.GetIntValue(pAppName, "ServerId", (int*)&m_serverId);

    const char* pAreaServerInfo = "AreaServerInfo";
    ini.GetIntValue(pAreaServerInfo, "AgentId", (int*)&m_agentId);
    ini.GetIntValue(pAreaServerInfo, "AreaId", (int*)&m_areaId);
    ini.GetIntValue(pAreaServerInfo, "AreaServerId", (int*)&m_areaServerId);
    ini.GetStringValue(pAreaServerInfo, "Version", &m_sVersionKeyName);

    const char* pDBServerInfo = "DBServer";
    ini.GetStringValue(pDBServerInfo, "MySQLServAddr", &m_sMySQLServAddr_GAME);
    ini.GetIntValue(pDBServerInfo, "MySQLServPort", (int*)&m_nMySQLServPort_GAME);
    ini.GetStringValue(pDBServerInfo, "MySQLServUserName", &m_sMySQLServUserName_GAME);
    ini.GetStringValue(pDBServerInfo, "MySQLServPassword", &m_sMySQLServPassword_GAME);

    const char* pDefault = "Default";
    ini.GetStringValue(pDefault, "PlatformDomain", &m_sPlatformDomain);

    if (m_agentId || m_areaId || m_areaServerId) {
        m_sMySQLServDBName += "_" + to_string(m_agentId) + "_" + to_string(m_areaId) + "_" + to_string(m_areaServerId);
        m_sMySQLGameServDBName += "_" + to_string(m_agentId) + "_" + to_string(m_areaId) + "_" + to_string(m_areaServerId);
    }
}
