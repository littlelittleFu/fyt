#include "stdafx.h"
#include "SessionDB2LS.h"
#include "ILogHelper.h"
#include "DBManager.h"
#include "ProtoLS.h"
#include "ProtoGS.h"



SessionDB2LS::SessionDB2LS()
{

}

SessionDB2LS::~SessionDB2LS()
{

}

void SessionDB2LS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionDB2LS::OnLost()
{
	LOG_NORMAL("OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
	//DoClose();
}

void SessionDB2LS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    MsgCostStat::GetInstance()->BeginHandleMsg();

    OnHeartBeat();

    switch (moduleid)
    {
    case MODULE_TYPE_LS:
        HandleLoginServMsg(protoid, _pData);
        break;

    default:
        break;
    }

    MsgCostStat::GetInstance()->EndHandleMsg(moduleid, protoid);
}

void SessionDB2LS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionDB2LS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionDB2LS::DoHeartBeat()
{
	
}

void SessionDB2LS::HandleLoginServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_LS_HEART_BEAT_REQ, HandleLoginServMsg_HeartBeatReq)
        HANDLE_MSG(PROTO_LS_LOGIN_REQ, HandleLoginServMsg_LoginReq)
        HANDLE_MSG(PROTO_LS_INSERT_PLAYER, HandleLoginServMsg_InsertPlayer)
        HANDLE_MSG(PROTO_LS_GET_LOGIN_IP_REQ, HandleLoginServMsg_GetLoginIpReq)

    END_MSG_HANDLER()
}

void SessionDB2LS::HandleLoginServMsg_HeartBeatReq(void* pData)
{
    ProtoLS_HeartBeatAck ack;
    SendPkg(&ack, sizeof(ack));
}

void SessionDB2LS::HandleLoginServMsg_LoginReq(void* pData)
{
    ProtoLS_LoginReq* pLoginReq = (ProtoLS_LoginReq*)pData;

    uint64_t playerid = 0;
    int64_t isProhibitChat = 0;
    uint8_t isSupport = 0;
    int result = CDBManager::GetInstance()->CheckAccount(pLoginReq->username, pLoginReq->password, playerid,pLoginReq->isthirdlogin, isProhibitChat, isSupport);

    ProtoLS_LoginAck loginAck;
    loginAck.gssessid = pLoginReq->gssessid;
    loginAck.clsessid = pLoginReq->clsessid;
    sprintf_s(loginAck.username, _countof(loginAck.username), pLoginReq->username);
    loginAck.userid = playerid;
    loginAck.isProhibitChat = isProhibitChat;
    loginAck.isSupport = isSupport;
    loginAck.ip = pLoginReq->ip;
    strcpy_s(loginAck.hwid, _countof(loginAck.hwid), pLoginReq->hwid);
    switch (result)
    {
        case DBERR_OK:
            loginAck.result = ERR_OK;
            break;

        case DBERR_EMPTY:
            loginAck.result = ERR_LOGIN_WRONG_USER;
            strcpy_s(loginAck.info, _countof(loginAck.info), "用户名不存在");
            break;

        case DBERR_NOTMATCH:
            loginAck.result = ERR_LOGIN_WRONG_PASSWORD;
            strcpy_s(loginAck.info, _countof(loginAck.info), "密码不正确");
            break;
        case ERR_FORBIDLOGIN_ACCOUNT:
            loginAck.result = ERR_FORBIDLOGIN_ACCOUNT;
            strcpy_s(loginAck.info, _countof(loginAck.info), "账号已封禁");
            break;

        default:
            loginAck.result = ERR_UNKNOW;
            strcpy_s(loginAck.info, _countof(loginAck.info), "未知错误");
            break;
    }

    SendPkg(&loginAck, sizeof(loginAck));
}

void SessionDB2LS::HandleLoginServMsg_InsertPlayer(void *pData)
{
    const auto *msg = static_cast<ProtoLS_InsertPlayer *>(pData);

    int result = CDBManager::GetInstance()->InsertPlayer(msg->playerid, msg->username);

    if (result != DBERR_OK) {
        LOG_ERROR("InsertPlayer failed with error %d", result);
    }
}

void SessionDB2LS::HandleLoginServMsg_GetLoginIpReq(void* pData)
{
    std::vector<LOGIN_IP_DATA>vec;
    int result = CDBManager::GetInstance()->GetLoginIpInfo(vec);

    if (result != DBERR_OK) {
        LOG_ERROR("Get Login Ip Table failed with error %d", result);
    }

    int num = vec.size();
    auto startIter = vec.begin();
    while (num > 0)
    {
        ProtoDB_GetLoginIpAck data;
        if (num > 100)
        {
            data.num = 100;
        }
        else
        {
            data.num = num;
        }
        std::copy(startIter, startIter + data.num, data.infos);
        SendPkg(&data, sizeof(data));
        startIter += data.num;
        num -= 100;
    }
}
