#include "stdafx.h"
#include "SessionCS2SS.h"
#include "ILogHelper.h"
#include "ProtoCS.h"
#include "CNetManager.h"
#include "SessionFactory.h"


SessionCS2SS::SessionCS2SS()
{

}

SessionCS2SS::~SessionCS2SS()
{

}

void SessionCS2SS::OnEstablish(SOCKET _Socket)
{
    LOG_NORMAL("Connection established. Remote host: %s:%u", GetRemoteIp().c_str(), GetRemotePort());
    Session::OnEstablish(_Socket);
    UploadConfigToServiceServer();
    RequestServerConfig();
}

void SessionCS2SS::OnLost()
{
    LOG_WARN("Lost connection with remote host: %s:%u", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionCS2SS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    OnHeartBeat();

    switch (moduleid) {
    case MODULE_TYPE_CS:
        HandleCenterServMsg(protoid, _pData);
        break;

    default:
        LOG_WARN("Unhandled moduleid: %u", moduleid);
        break;
    }
}

void SessionCS2SS::OnError(DWORD _ErrorCode)
{
    LOG_ERROR("_ErrorCode: %u", _ErrorCode);
}

void SessionCS2SS::OnUpdate(UINT _Delta)
{
    Session::OnUpdate(_Delta);
}

void SessionCS2SS::DoHeartBeat()
{
    ProtoCS_HeartBeatReq req;
    SendPkg(&req, sizeof(req));
}

void SessionCS2SS::HandleCenterServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_CS_HEART_BEAT_ACK, HandleCenterServMsg_HeartBeatAck)
        HANDLE_MSG(PROTO_CS_CONFIG_ACK, HandleCenterServMsg_ConfigAck)
    END_MSG_HANDLER()
}

void SessionCS2SS::HandleCenterServMsg_HeartBeatAck(void* pData)
{
    // do nothing
}

void SessionCS2SS::HandleCenterServMsg_ConfigAck(void* pData)
{
    ProtoCS_ConfigAck* pConfig = (ProtoCS_ConfigAck*)pData;

    ConfigInfo* pConfigInfo = ConfigInfo::GetInstance();
    pConfigInfo->m_sDBServerIP = Tools::ConvertIntToIP(pConfig->dbServIp);
    pConfigInfo->m_nDBServerPort = pConfig->dbServPort;

    pConfigInfo->m_sLogServerIP = Tools::ConvertIntToIP(pConfig->logServIp);
    pConfigInfo->m_nLogServerPort = pConfig->logServPort;

    LOG_NORMAL("DB server ip: %s, port: %d", pConfigInfo->m_sDBServerIP.c_str(), pConfigInfo->m_nDBServerPort);
    LOG_NORMAL("Log server ip: %s, port: %d", pConfigInfo->m_sLogServerIP.c_str(), pConfigInfo->m_nLogServerPort);
    if (!SessionExist(SESSION_TYPE_CS2DB)) {
        IssueConnectionRequest(pConfigInfo->m_sDBServerIP, pConfigInfo->m_nDBServerPort, SESSION_TYPE_CS2DB);
    }
    if (!SessionExist(SESSION_TYPE_CS2LOG)) {
        IssueConnectionRequest(pConfigInfo->m_sLogServerIP, pConfigInfo->m_nLogServerPort, SESSION_TYPE_CS2LOG);
    }
}

void SessionCS2SS::UploadConfigToServiceServer()
{
    ProtoCS_UploadConfigReq req;
    req.ip = inet_addr(ConfigInfo::GetInstance()->m_sLocalMachineIp.c_str());
    req.port = ConfigInfo::GetInstance()->m_nListenPort;
    SendPkg(&req, sizeof(req));
}

void SessionCS2SS::RequestServerConfig()
{
    if (HasGetConfigFromSS()) return;

    ProtoCS_ConfigReq req;
    SendPkg(&req, sizeof(req));
}

bool SessionCS2SS::HasGetConfigFromSS()
{
    return (ConfigInfo::GetInstance()->m_nDBServerPort != 0);
}
