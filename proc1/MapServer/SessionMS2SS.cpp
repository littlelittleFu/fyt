#include "stdafx.h"
#include "SessionMS2SS.h"
#include "ILogHelper.h"
#include "ProtoMS.h"
#include "CNetManager.h"
#include "SessionFactory.h"


SessionMS2SS::SessionMS2SS()
{
	
}

SessionMS2SS::~SessionMS2SS()
{

}

void SessionMS2SS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);

    UploadConfigToServiceServer();
    RequestServerConfig();
}

void SessionMS2SS::OnLost()
{
	Session::OnLost();
	LOG_WARN("SessionSS2MS SESSION LOST!");
}

void SessionMS2SS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    OnHeartBeat();

    if (moduleid != MODULE_TYPE_MS) return;

    switch (protoid)
    {
    case PROTO_MS_CONFIG_ACK:
        HandleConfigAck(_pData);
        break;

    default:
        break;
    }
}

void SessionMS2SS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("SessionSS2MS ERROR %ld", _ErrorCode);
}

void SessionMS2SS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionMS2SS::DoHeartBeat()
{
    ProtoMS_HeartBeatReq req;
    SendPkg(&req, sizeof(req));
}

void SessionMS2SS::UploadConfigToServiceServer()
{
    ProtoMS_UploadConfigReq req;
    req.ip = inet_addr(ConfigInfo::GetInstance()->m_sLocalMachineIp.c_str());
    req.port = ConfigInfo::GetInstance()->m_nListenPort;

    SendPkg(&req, sizeof(req));
}

void SessionMS2SS::RequestServerConfig()
{
    if (HasGetConfigFromSS()) return;

    ProtoMS_ConfigReq req;
    SendPkg(&req, sizeof(req));
}

bool SessionMS2SS::HasGetConfigFromSS()
{
    return (ConfigInfo::GetInstance()->m_nDBServerPort != 0);
}

void SessionMS2SS::HandleConfigAck(void* pData)
{
    ProtoMS_ConfigAck* pConfig = (ProtoMS_ConfigAck*)pData;

    ConfigInfo* pConfigInfo = ConfigInfo::GetInstance();
    pConfigInfo->m_sDBServerIP = Tools::ConvertIntToIP(pConfig->dbServIp);
    pConfigInfo->m_nDBServerPort = pConfig->dbServPort;

    pConfigInfo->m_sCenterServerIP = Tools::ConvertIntToIP(pConfig->centerServIp);
    pConfigInfo->m_nCenterServerPort = pConfig->centerServPort;

    pConfigInfo->m_sLogServerIP = Tools::ConvertIntToIP(pConfig->logServIp);
    pConfigInfo->m_nLogServerPort = pConfig->logServPort;

    LOG_NORMAL("DB server ip: %s, port: %d", pConfigInfo->m_sDBServerIP.c_str(), pConfigInfo->m_nDBServerPort);
    LOG_NORMAL("Center server ip: %s, port: %d", pConfigInfo->m_sCenterServerIP.c_str(), pConfigInfo->m_nCenterServerPort);
    LOG_NORMAL("Log server ip: %s, port: %d", pConfigInfo->m_sLogServerIP.c_str(), pConfigInfo->m_nLogServerPort);

    if (!SessionExist(SESSION_TYPE_MS2DB))
    {
        //IssueConnectionRequest(pConfigInfo->m_sDBServerIP, pConfigInfo->m_nDBServerPort, SESSION_TYPE_MS2DB);
    }

    if (!SessionExist(SESSION_TYPE_MS2CS))
    {
        IssueConnectionRequest(pConfigInfo->m_sCenterServerIP, pConfigInfo->m_nCenterServerPort +2, SESSION_TYPE_MS2CS);
    }

    if (!SessionExist(SESSION_TYPE_MS2LOG))
    {
        IssueConnectionRequest(pConfigInfo->m_sLogServerIP, pConfigInfo->m_nLogServerPort + 2, SESSION_TYPE_MS2LOG);
    }
}
