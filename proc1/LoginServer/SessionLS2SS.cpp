#include "stdafx.h"
#include "SessionLS2SS.h"
#include "ILogHelper.h"
#include "ProtoLS.h"
#include "CNetManager.h"
#include "SessionFactory.h"


SessionLS2SS::SessionLS2SS()
{
	
}

SessionLS2SS::~SessionLS2SS()
{

}

void SessionLS2SS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);

    UploadConfigToServiceServer();
    RequestServerConfig();
}

void SessionLS2SS::OnLost()
{
	Session::OnLost();
	LOG_WARN("SessionSS2LS SESSION LOST!");
}

void SessionLS2SS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    OnHeartBeat();

    if (moduleid != MODULE_TYPE_LS) return;

    switch (protoid)
    {
    case PROTO_LS_CONFIG_ACK:
        HandleConfigAck(_pData);
        break;

    default:
        break;
    }
}

void SessionLS2SS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("SessionSS2LS ERROR %ld", _ErrorCode);
}

void SessionLS2SS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionLS2SS::DoHeartBeat()
{
    ProtoLS_HeartBeatReq req;
    SendPkg(&req, sizeof(req));
}

void SessionLS2SS::UploadConfigToServiceServer()
{
    ProtoLS_UploadConfigReq req;
    req.ip = inet_addr(ConfigInfo::GetInstance()->m_sLocalMachineIp.c_str());
    req.port = ConfigInfo::GetInstance()->m_nListenPort;

    SendPkg(&req, sizeof(req));
}

void SessionLS2SS::RequestServerConfig()
{
    if (HasGetConfigFromSS()) return;

    ProtoLS_ConfigReq req;
    SendPkg(&req, sizeof(req));
}

bool SessionLS2SS::HasGetConfigFromSS()
{
    return (ConfigInfo::GetInstance()->m_nDBServerPort != 0);
}

void SessionLS2SS::HandleConfigAck(void* pData)
{
    ProtoLS_ConfigAck* pConfig = (ProtoLS_ConfigAck*)pData;

    ConfigInfo *pConfigInfo = ConfigInfo::GetInstance();
    pConfigInfo->m_sDBServerIP = Tools::ConvertIntToIP(pConfig->dbServIp);
    pConfigInfo->m_nDBServerPort = pConfig->dbServPort;

    pConfigInfo->m_sCenterServerIP = Tools::ConvertIntToIP(pConfig->centerServIp);
    pConfigInfo->m_nCenterServerPort = pConfig->centerServPort;

    pConfigInfo->m_sLogServerIP = Tools::ConvertIntToIP(pConfig->logServIp);
    pConfigInfo->m_nLogServerPort = pConfig->logServPort;

    LOG_NORMAL("DB server ip: %s, port: %d", pConfigInfo->m_sDBServerIP.c_str(), pConfigInfo->m_nDBServerPort);
    LOG_NORMAL("Center server ip: %s, port: %d", pConfigInfo->m_sCenterServerIP.c_str(), pConfigInfo->m_nCenterServerPort);
    LOG_NORMAL("Log server ip: %s, port: %d", pConfigInfo->m_sLogServerIP.c_str(), pConfigInfo->m_nLogServerPort);

    if (!SessionExist(SESSION_TYPE_LS2DB))
    {
        IssueConnectionRequest(pConfigInfo->m_sDBServerIP, pConfigInfo->m_nDBServerPort +1, SESSION_TYPE_LS2DB);
    }

    if (!SessionExist(SESSION_TYPE_LS2CS))
    {
        IssueConnectionRequest(pConfigInfo->m_sCenterServerIP, pConfigInfo->m_nCenterServerPort +1, SESSION_TYPE_LS2CS);
    }

    if (!SessionExist(SESSION_TYPE_LS2LOG))
    {
        IssueConnectionRequest(pConfigInfo->m_sLogServerIP, pConfigInfo->m_nLogServerPort + 1, SESSION_TYPE_LS2LOG);
    }
}
