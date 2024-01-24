#include "stdafx.h"
#include "IFileHelper.h"

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
    const char* pAppName = "LoginServer";

    inifile::IniFile ini;
    if (ini.Load(sConfigFilePath) != 0) return;

    ini.GetIntValue(pAppName, "ConnCheckTimerInterval", (int *)&m_nConnCheckTimerInterval);
    ini.GetIntValue(pAppName, "NetLibThreadNum", (int *)&m_nNetLibThreadNum);
    ini.GetStringValue(pAppName, "ListenIP", &m_sListenIp);
    ini.GetIntValue(pAppName, "ListenPort", (int *)&m_nListenPort);
    ini.GetStringValue(pAppName, "ServiceServerIP", &m_sServiceServerIp);
    ini.GetIntValue(pAppName, "ServiceServerPort", (int *)&m_nServiceServerPort);
    ini.GetStringValue(pAppName, "LocalMachineIP", &m_sLocalMachineIp);
    ini.GetIntValue(pAppName, "LogLevel", (int *)&m_bLogLevel);
    ini.GetIntValue(pAppName, "InitStateMaintenance", (int *)&m_bInitStateMaintenance);
    ini.GetIntValue(pAppName, "CheckTokenThreadNum", (int *)&m_nCheckTokenThreadNum);
    ini.GetIntValue(pAppName, "ServerId", (int*)&m_serverId);

    const char* pAreaServerInfo = "AreaServerInfo";
    ini.GetIntValue(pAreaServerInfo, "AgentId", (int*)&m_agentId);
    ini.GetIntValue(pAreaServerInfo, "AreaId", (int*)&m_areaId);
    ini.GetIntValue(pAreaServerInfo, "AreaServerId", (int*)&m_areaServerId);

    const char* pDefault = "Default";
    ini.GetStringValue(pDefault, "PlatformDomain", &m_sPlatformDomain);
    ini.GetStringValue(pDefault, "ServerKey", &m_sServerKey);
}

bool ConfigInfo::IsDBConfigValid()
{
    return !m_sDBServerIP.empty() && m_nDBServerPort != 0;
}

bool ConfigInfo::IsCSConfigValid()
{
    return !m_sCenterServerIP.empty() && m_nCenterServerPort != 0;
}

bool ConfigInfo::IsLogConfigValid()
{
    return !m_sLogServerIP.empty() && m_nLogServerPort != 0;
}
