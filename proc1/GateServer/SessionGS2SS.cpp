#include "stdafx.h"
#include "SessionGS2SS.h"
#include "ILogHelper.h"
#include "ProtoGS.h"
#include "SessionFactory.h"
#include "CNetManager.h"


SessionGS2SS::SessionGS2SS()
{

}

SessionGS2SS::~SessionGS2SS()
{

}

void SessionGS2SS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());

    RequestServerConfig();
}

void SessionGS2SS::OnLost()
{
	LOG_NORMAL("OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
	//DoClose();
}

void SessionGS2SS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    OnHeartBeat();

    //if (moduleid != MODULE_TYPE_GS) return;

    switch (protoid)
    {
    case PROTO_GS_CONFIG_ACK:
        HandleConfigAck(_pData);
        break;

    default:
        break;
    }
}

void SessionGS2SS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionGS2SS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionGS2SS::DoHeartBeat()
{
    ProtoGS_HeartBeatReq req;
    SendPkg(&req, sizeof(req));
}

void SessionGS2SS::RequestServerConfig()
{
    if (HasGetConfigFromSS()) return;

    ProtoGS_ConfigReq req;
    SendPkg(&req, sizeof(req));
}

bool SessionGS2SS::HasGetConfigFromSS()
{
    return (ConfigInfo::GetInstance()->m_nLoginServerPort != 0);
}

void SessionGS2SS::HandleConfigAck(void* pData)
{
    ProtoGS_ConfigAck *pConfig = (ProtoGS_ConfigAck *)pData;

    ConfigInfo* pConfigInfo = ConfigInfo::GetInstance();
    pConfigInfo->m_sLoginServerIP = Tools::ConvertIntToIP(pConfig->loginServIp);
    pConfigInfo->m_nLoginServerPort = pConfig->loginServPort;

    pConfigInfo->m_sMapServerIP = Tools::ConvertIntToIP(pConfig->mapServIp);
    pConfigInfo->m_nMapServerPort = pConfig->mapServPort;

    pConfigInfo->m_sCenterServerIP = Tools::ConvertIntToIP(pConfig->centerServIp);
    pConfigInfo->m_nCenterServerPort = pConfig->centerServPort;

    pConfigInfo->m_sLogServerIP = Tools::ConvertIntToIP(pConfig->logServIp);
    pConfigInfo->m_nLogServerPort = pConfig->logServPort;

    LOG_NORMAL("Login server ip: %s, port: %d", pConfigInfo->m_sLoginServerIP.c_str(), pConfigInfo->m_nLoginServerPort);
    LOG_NORMAL("Map server ip: %s, port: %d", pConfigInfo->m_sMapServerIP.c_str(), pConfigInfo->m_nMapServerPort);
    LOG_NORMAL("Center server ip: %s, port: %d", pConfigInfo->m_sCenterServerIP.c_str(), pConfigInfo->m_nCenterServerPort);
    LOG_NORMAL("Log server ip: %s, port: %d", pConfigInfo->m_sLogServerIP.c_str(), pConfigInfo->m_nLogServerPort);

    if (!SessionExist(SESSION_TYPE_GS2LS))
    {
        IssueConnectionRequest(pConfigInfo->m_sLoginServerIP, pConfigInfo->m_nLoginServerPort, SESSION_TYPE_GS2LS);
    }

    if (!SessionExist(SESSION_TYPE_GS2MS))
    {
        IssueConnectionRequest(pConfigInfo->m_sMapServerIP, pConfigInfo->m_nMapServerPort, SESSION_TYPE_GS2MS);
    }

    if (!SessionExist(SESSION_TYPE_GS2CS))
    {
        IssueConnectionRequest(pConfigInfo->m_sCenterServerIP, pConfigInfo->m_nCenterServerPort, SESSION_TYPE_GS2CS);
    }

    if (!SessionExist(SESSION_TYPE_GS2LOG))
    {
        IssueConnectionRequest(pConfigInfo->m_sLogServerIP, pConfigInfo->m_nLogServerPort + 3, SESSION_TYPE_GS2LOG);
    }
}
