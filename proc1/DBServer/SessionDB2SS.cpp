#include "stdafx.h"
#include "SessionDB2SS.h"
#include "ILogHelper.h"
#include "DBManager.h"
#include "ProtoDB.h"
#include "CNetManager.h"
#include "SessionFactory.h"

SessionDB2SS::SessionDB2SS()
{

}

SessionDB2SS::~SessionDB2SS()
{

}

void SessionDB2SS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());

	UploadConfigToServiceServer();
    RequestServerConfig();
}

void SessionDB2SS::OnLost()
{
	LOG_NORMAL("OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionDB2SS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    OnHeartBeat();

    switch (moduleid) {
    case MODULE_TYPE_DB:
        HandleDBMsg(protoid, _pData);
        break;

    default:
        LOG_WARN("Unhandled moduleid: %u", moduleid);
        break;
    }
}

void SessionDB2SS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionDB2SS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionDB2SS::DoHeartBeat()
{
    ProtoDB_HeartBeatReq req;
    SendPkg(&req, sizeof(req));
}

void SessionDB2SS::UploadConfigToServiceServer()
{
	ProtoDB_UploadConfigReq req;
	req.ip = inet_addr(ConfigInfo::GetInstance()->m_sLocalMachineIp.c_str());
	req.port = ConfigInfo::GetInstance()->m_nListenPort;

	SendPkg(&req, sizeof(req));
}

void SessionDB2SS::RequestServerConfig()
{
    if (HasGetConfigFromSS()) return;

    ProtoDB_ConfigReq req;
    SendPkg(&req, sizeof(req));
}

bool SessionDB2SS::HasGetConfigFromSS()
{
    return (ConfigInfo::GetInstance()->m_nLogServerPort != 0);
}

void SessionDB2SS::HandleDBMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_DB_HEART_BEAT_ACK, HandleDBMsg_HeartBeatAck)
        HANDLE_MSG(PROTO_DB_CONFIG_ACK, HandleDBMsg_ConfigAck)
    END_MSG_HANDLER()
}

void SessionDB2SS::HandleDBMsg_HeartBeatAck(void* pData)
{
    // do nothing
}

void SessionDB2SS::HandleDBMsg_ConfigAck(void* pData)
{
    ProtoDB_ConfigAck* pConfig = (ProtoDB_ConfigAck*)pData;

    ConfigInfo* pConfigInfo = ConfigInfo::GetInstance();

    pConfigInfo->m_sLogServerIP = Tools::ConvertIntToIP(pConfig->logServIp);
    pConfigInfo->m_nLogServerPort = pConfig->logServPort;

    LOG_NORMAL("Log server ip: %s, port: %d", pConfigInfo->m_sLogServerIP.c_str(), pConfigInfo->m_nLogServerPort);

    if (!SessionExist(SESSION_TYPE_DB2LOG))
    {
        IssueConnectionRequest(pConfigInfo->m_sLogServerIP, pConfigInfo->m_nLogServerPort + 4, SESSION_TYPE_DB2LOG);
    }
}