#include "stdafx.h"
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
    AssignDefaultValue();

    std::string sConfigFilePath = IFileHelper::GetInstance()->GetConfigFilePath();
    LOG_NORMAL("CONFIG PATH %s",sConfigFilePath.c_str());
    const char* pAppName = "DBServer";

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
    ini.GetStringValue(pAppName, "MySQLGlobalServDBName", &m_sMySQLGlobalServDBName);
    ini.GetStringValue(pAppName, "MySQLLogServDBName", &m_sMySQLLogServDBName);
    ini.GetIntValue(pAppName, "LogLevel", (int *)&m_bLogLevel);
    ini.GetIntValue(pAppName, "ServerId", (int*)&m_serverId);
    ini.GetStringValue(pAppName, "GameCfgFolderPath", &m_sGameCfgFolderPath);

    Tools::AppendPathSeperator(m_sGameCfgFolderPath);

    const char* pAreaServerInfo = "AreaServerInfo";
    ini.GetIntValue(pAreaServerInfo, "AgentId", (int*)&m_agentId);
    ini.GetIntValue(pAreaServerInfo, "AreaId", (int*)&m_areaId);
    ini.GetIntValue(pAreaServerInfo, "AreaServerId", (int*)&m_areaServerId);

    const char* pDefault = "Default";
    ini.GetStringValue(pDefault, "PlatformDomain", &m_sPlatformDomain);

    if (m_agentId || m_areaId || m_areaServerId) {
        m_sAgentAreaServerIdStr = to_string(m_agentId) + "_" + to_string(m_areaId) + "_" + to_string(m_areaServerId);
        m_sMySQLServDBName += "_" + to_string(m_agentId) + "_" + to_string(m_areaId) + "_" + to_string(m_areaServerId);
        m_sMySQLLogServDBName += "_" + to_string(m_agentId) + "_" + to_string(m_areaId) + "_" + to_string(m_areaServerId);
        m_sMySQLGlobalServDBName += "_" + to_string(m_agentId);
    }
}

void ConfigInfo::AssignDefaultValue()
{
    auto curWorkPath = IFileHelper::GetInstance()->GetCurWorkPath();
#ifdef _WIN32
    m_sGameCfgFolderPath = curWorkPath + "res\\db\\";
#else
    m_sGameCfgFolderPath = curWorkPath + "res/db/";
#endif
}

bool ConfigInfo::IsLogConfigValid()
{
    return !m_sLogServerIP.empty() && m_nLogServerPort != 0;
}