#include "stdafx.h"
#include "ProtoClient.h"
#include "ILogHelper.h"


static int EncodeLoginReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_LoginReq);
    ENCODE_STRING(username);
    ENCODE_DWORD(ip);
    ENCODE_DWORD(pwdlen);
    ENCODE_BLOB(password, pstIn->pwdlen);
    ENCODE_STRING(hwid);
    END_ENCODE();
}

static int DecodeLoginReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_LoginReq);
    DECODE_STRING(username);
    DECODE_DWORD(ip);
    DECODE_DWORD(pwdlen);
    DECODE_BLOB(password, pstOut->pwdlen);
    DECODE_STRING(hwid);
    END_DECODE();
}

static int EncodeLoginAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_LoginAck);
    ENCODE_QWORD(playerid);
    ENCODE_INT(errcode);
    ENCODE_STRING(errmsg);
    END_ENCODE();
}

static int DecodeLoginAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_LoginAck);
    DECODE_QWORD(playerid);
    DECODE_INT(errcode);
    DECODE_STRING(errmsg);
    END_DECODE();
}

static int EncodeThirdLoginReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_ThirdLoginReq);
    ENCODE_STRING(channel);
    ENCODE_DWORD(gameid);
    ENCODE_STRING(token);
    ENCODE_STRING(user_name);
    ENCODE_DWORD(login_ip);
    ENCODE_STRING(hwid);
    END_ENCODE();
}

static int DecodeThirdLoginReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_ThirdLoginReq);
    DECODE_STRING(channel);
    DECODE_DWORD(gameid);
    DECODE_STRING(token);
    DECODE_STRING(user_name);
    DECODE_DWORD(login_ip);
    DECODE_STRING(hwid);
    END_DECODE();
}

static int EncodeLogoutReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_LogoutReq);
    ENCODE_BYTE(info);
    END_ENCODE();
}

static int DecodeLogoutReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_LogoutReq);
    DECODE_BYTE(info);
    END_DECODE();
}

static int EncodeRandKeyNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_RandKeyNtf);
    ENCODE_DWORD(codelen);
    ENCODE_BLOB(code, pstIn->codelen);
    END_ENCODE();
}

static int DecodeRandKeyNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_RandKeyNtf);
    DECODE_DWORD(codelen);
    DECODE_BLOB(code, pstOut->codelen);
    END_DECODE();
}

static int EncodeReloginReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_ReloginReq);
    ENCODE_QWORD(player_guid);
    ENCODE_QWORD(role_guid);
    ENCODE_STRING(randkey);
    //ENCODE_STRING(hwid);
    END_ENCODE();
}

static int DecodeReloginReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_ReloginReq);
    DECODE_QWORD(player_guid);
    DECODE_QWORD(role_guid);
    DECODE_STRING(randkey);
    //DECODE_STRING(hwid);
    END_DECODE();
}

static int EncodeReloginAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_ReloginAck);
    ENCODE_INT(errcode);
    ENCODE_STRING(errmsg);
    END_ENCODE();
}

static int DecodeReloginAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_ReloginAck);
    DECODE_INT(errcode);
    DECODE_STRING(errmsg);
    END_DECODE();
}

static int EncodeConnReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_ConnReq);
    ENCODE_DWORD(version);
    ENCODE_DWORD(zone);
    END_ENCODE();
}

static int DecodeConnReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_ConnReq);
    DECODE_DWORD(version);
    DECODE_DWORD(zone);
    END_DECODE();
}

static int EncodeConnAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_ConnAck);
    ENCODE_DWORD(errcode);
    ENCODE_INT(overload);
    ENCODE_INT(delay);
    END_ENCODE();
}

static int DecodeConnAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_ConnAck);
    DECODE_DWORD(errcode);
    DECODE_INT(overload);
    DECODE_INT(delay);
    END_DECODE();
}

static int EncodeHeartBeatReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_HeartBeatReq);
    END_ENCODE();
}

static int DecodeHeartBeatReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_HeartBeatReq);
    END_DECODE();
}

static int EncodeHeartBeatAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_HeartBeatAck);
    END_ENCODE();
}

static int DecodeHeartBeatAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_HeartBeatAck);
    END_DECODE();
}

static int EncodeKickUserNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_KickUserNtf);
    ENCODE_INT(errcode);
    ENCODE_STRING(errmsg);
    END_ENCODE();
}

static int DecodeKickUserNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_KickUserNtf);
    DECODE_INT(errcode);
    DECODE_STRING(errmsg);
    END_DECODE();
}

static int EncodeCreateRoleReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_CreateRoleReq);
    if (-1 == EnCodeROLE_BRIEF_INFO(&pstIn->createrole, poNetData))
        return -1;
    END_ENCODE();
}

static int DecodeCreateRoleReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_CreateRoleReq);
    if (-1 == DeCodeROLE_BRIEF_INFO(&pstOut->createrole, poNetData))
        return -1;
    END_DECODE();
}

static int EncodeCreateRoleReqEx(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_CreateRoleReqEx);
    if (-1 == EnCodeROLE_BRIEF_INFO(&pstIn->createrole, poNetData))
        return -1;
    ENCODE_QWORD(digCode);
    END_ENCODE();
}

static int DecodeCreateRoleReqEx(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_CreateRoleReqEx);
    if (-1 == DeCodeROLE_BRIEF_INFO(&pstOut->createrole, poNetData))
        return -1;
    DECODE_QWORD(digCode);
    END_DECODE();
}

static int EncodeCreateRoleAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_CreateRoleAck);
    ENCODE_INT(errcode);
    ENCODE_STRING(errmsg);
    if (-1 == EnCodeROLE_BRIEF_INFO(&pstIn->newrole, poNetData))
        return -1;
    END_ENCODE();
}

static int DecodeCreateRoleAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_CreateRoleAck);
    DECODE_INT(errcode);
    DECODE_STRING(errmsg);
    if (-1 == DeCodeROLE_BRIEF_INFO(&pstOut->newrole, poNetData))
        return -1;
    END_ENCODE();
}

static int EncodeGetRoleListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_GetRoleListReq);
    END_ENCODE();
}

static int DecodeGetRoleListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_GetRoleListReq);
    END_DECODE();
}

static int EncodeGetRoleListAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_GetRoleListAck);
    ENCODE_INT(errcode);
    ENCODE_STRING(errmsg);
    ENCODE_BYTE(rolenum);
    ENCODE_QWORD(last_role);

    for (int i = 0; i < pstIn->rolenum; i++)
    {
        if (-1 == EnCodeROLE_BRIEF_INFO(&pstIn->rolelist[i], poNetData))
            return -1;
    }

    ENCODE_BYTE(needCode);
    END_ENCODE();
}

static int DecodeGetRoleListAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_GetRoleListAck);
    DECODE_INT(errcode);
    DECODE_STRING(errmsg);
    DECODE_BYTE(rolenum);
    DECODE_QWORD(last_role);

    for (int i = 0; i < pstOut->rolenum; i++)
    {
        if (-1 == DeCodeROLE_BRIEF_INFO(&pstOut->rolelist[i], poNetData))
            return -1;
    }

    DECODE_BYTE(needCode);
    END_DECODE();
}

static int DecodeEnterMapReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_EnterMapReq);
    DECODE_STRING(username);
    END_DECODE();
}

static int EncodeEnterMapReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_EnterMapReq);
    ENCODE_STRING(username);
    END_ENCODE();
}

static int DecodeEnterMapAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_EnterMapAck);
    DECODE_INT(Id);
    END_DECODE();
}

static int EncodeEnterMapAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_EnterMapAck);
    ENCODE_INT(Id);
    END_ENCODE();
}

static int EncodeDeleteRoleReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_DeleteRoleReq);
    ENCODE_QWORD(guid);
    END_ENCODE();
}

static int DecodeDeleteRoleReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_DeleteRoleReq);
    DECODE_QWORD(guid);
    END_DECODE();
}

static int EncodeRestoreRoleReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_RestoreRoleReq);
    ENCODE_QWORD(guid);
    END_ENCODE();
}

static int DecodeRestoreRoleReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_RestoreRoleReq);
    DECODE_QWORD(guid);
    END_DECODE();
}

static int EncodeDeleteRoleAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_DeleteRoleAck);
    ENCODE_QWORD(guid);
    ENCODE_INT(errcode);
    ENCODE_STRING(errmsg);
    END_ENCODE();
}

static int DecodeDeleteRoleAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_DeleteRoleAck);
    DECODE_QWORD(guid);
    DECODE_INT(errcode);
    DECODE_STRING(errmsg);
    END_DECODE();
}

static int EncodeRestoreRoleAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient_RestoreRoleAck);
    ENCODE_INT(errcode);
    ENCODE_STRING(errmsg);
    EnCodeROLE_BRIEF_INFO(&pstIn->role, poNetData);
    END_ENCODE();
}

static int DecodeRestoreRoleAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient_RestoreRoleAck);
    DECODE_INT(errcode);
    DECODE_STRING(errmsg);
    DeCodeROLE_BRIEF_INFO(&pstOut->role, poNetData);
    END_DECODE();
}

ProtoClient::ProtoClient()
{
    for (int i = 0; i < PROTO_CLIENT_MAX; ++i) {
        SET_ENCODER_DECODER(i, EncodeNotImpl, DecodeNotImpl);
    }

    SET_ENCODER_DECODER(PROTO_CLIENT_LOGIN_REQ, EncodeLoginReq, DecodeLoginReq);
    SET_ENCODER_DECODER(PROTO_CLIENT_LOGIN_ACK, EncodeLoginAck, DecodeLoginAck);
    SET_ENCODER_DECODER(PROTO_CLIENT_THIRD_LOGIN_REQ, EncodeThirdLoginReq, DecodeThirdLoginReq);
    SET_ENCODER_DECODER(PROTO_CLIENT_LOGOUT_REQ, EncodeLogoutReq, DecodeLogoutReq);
    SET_ENCODER_DECODER(PROTO_CLIENT_RANDKEY_NTF, EncodeRandKeyNtf, DecodeRandKeyNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT_RELOGIN_REQ, EncodeReloginReq, DecodeReloginReq);
    SET_ENCODER_DECODER(PROTO_CLIENT_RELOGIN_ACK, EncodeReloginAck, DecodeReloginAck);
    SET_ENCODER_DECODER(PROTO_CLIENT_HEART_BEAT_REQ, EncodeHeartBeatReq, DecodeHeartBeatReq);
    SET_ENCODER_DECODER(PROTO_CLIENT_HEART_BEAT_ACK, EncodeHeartBeatAck, DecodeHeartBeatAck);
    SET_ENCODER_DECODER(PROTO_CLIENT_CONN_REQ, EncodeConnReq, DecodeConnReq);
    SET_ENCODER_DECODER(PROTO_CLIENT_CONN_ACK, EncodeConnAck, DecodeConnAck);
    SET_ENCODER_DECODER(PROTO_CLIENT_KICK_USER_NTF, EncodeKickUserNtf, DecodeKickUserNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT_CREATE_ROLE_REQ, EncodeCreateRoleReq, DecodeCreateRoleReq);
    SET_ENCODER_DECODER(PROTO_CLIENT_CREATE_ROLE_REQ_EX, EncodeCreateRoleReqEx, DecodeCreateRoleReqEx);
    SET_ENCODER_DECODER(PROTO_CLIENT_CREATE_ROLE_ACK, EncodeCreateRoleAck, DecodeCreateRoleAck);
    SET_ENCODER_DECODER(PROTO_CLIENT_GET_ROLE_LIST_REQ, EncodeGetRoleListReq, DecodeGetRoleListReq);
    SET_ENCODER_DECODER(PROTO_CLIENT_GET_ROLE_LIST_ACK, EncodeGetRoleListAck, DecodeGetRoleListAck);
    SET_ENCODER_DECODER(PROTO_CLIENT_ENTER_MAP_REQ, EncodeEnterMapReq, DecodeEnterMapReq);
    SET_ENCODER_DECODER(PROTO_CLIENT_ENTER_MAP_ACK, EncodeEnterMapAck, DecodeEnterMapAck);
    SET_ENCODER_DECODER(PROTO_CLIENT_DEL_ROLE_REQ, EncodeDeleteRoleReq, DecodeDeleteRoleReq);
    SET_ENCODER_DECODER(PROTO_CLIENT_RECOVER_ROLE_REQ, EncodeRestoreRoleReq, DecodeRestoreRoleReq);
    SET_ENCODER_DECODER(PROTO_CLIENT_DEL_ROLE_ACK, EncodeDeleteRoleAck, DecodeDeleteRoleAck);
    SET_ENCODER_DECODER(PROTO_CLIENT_RECOVER_ROLE_ACK, EncodeRestoreRoleAck, DecodeRestoreRoleAck);
}

ProtoClient::~ProtoClient()
{

}

int ProtoClient::BuildProtocol(void* pHost, char* pNet, int iNetSize)
{
    unsigned short moduleid = *(unsigned short*)pHost;
    unsigned short protoid = *(unsigned short*)((char*)pHost + sizeof(unsigned short));
  /*  if (moduleid != GetModuleID()) {
        return -1;
    }*/
    if (protoid >= PROTO_CLIENT_MAX) {
        return -1;
    }

    CNetData m_oData;
    m_oData.Prepare(pNet, iNetSize);
    return m_EnCodeFuncArray[protoid](pHost, &m_oData);
}

int ProtoClient::HandleProtocol(void* pNet, char* pHost, int iNetSize)
{
    unsigned short moduleid = *(unsigned short*)pNet;
    unsigned short protoid = *(unsigned short*)((char*)pNet + sizeof(unsigned short));

#ifndef _HIDE_PROTO_LOG
    LOG_TRACE("moduleid: %d, protoid: %d", moduleid, protoid);
#endif // !_HIDE_PROTO_LOG


    if (moduleid != GetModuleID()) {
        return -1;
    }
    if (protoid >= PROTO_CLIENT_MAX) {
        return -1;
    }

    CNetData m_oData;
    m_oData.Prepare((char*)pNet, iNetSize);
    return m_DeCodeFuncArray[protoid](pHost, &m_oData);
}