#include "stdafx.h"
#include "ProtoLS.h"


static int EncodeHeartBeatReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoLS_HeartBeatReq);
    END_ENCODE();
}

static int DecodeHeartBeatReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoLS_HeartBeatReq);
    END_DECODE();
}

static int EncodeHeartBeatAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoLS_HeartBeatAck);
    END_ENCODE();
}

static int DecodeHeartBeatAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoLS_HeartBeatAck);
    END_DECODE();
}

static int EncodeUploadConfigReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoLS_UploadConfigReq);
    ENCODE_DWORD(ip);
    ENCODE_DWORD(port);
    END_ENCODE();
}

static int DecodeUploadConfigReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoLS_UploadConfigReq);
    DECODE_DWORD(ip);
    DECODE_DWORD(port);
    END_DECODE();
}

static int EncodeConfigReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoLS_ConfigReq);
    END_ENCODE();
}

static int DecodeConfigReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoLS_ConfigReq);
    END_DECODE();
}

static int EncodeConfigAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoLS_ConfigAck);
    ENCODE_DWORD(dbServIp);
    ENCODE_DWORD(dbServPort);
    ENCODE_DWORD(centerServIp);
    ENCODE_DWORD(centerServPort);
    ENCODE_DWORD(logServIp);
    ENCODE_DWORD(logServPort);
    END_ENCODE();
}

static int DecodeConfigAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoLS_ConfigAck);
    DECODE_DWORD(dbServIp);
    DECODE_DWORD(dbServPort);
    DECODE_DWORD(centerServIp);
    DECODE_DWORD(centerServPort);
    DECODE_DWORD(logServIp);
    DECODE_DWORD(logServPort);
    END_DECODE();
}

static int EncodeLoginReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoLS_LoginReq);
    ENCODE_DWORD(gssessid);
    ENCODE_DWORD(clsessid);
    ENCODE_BYTE(isthirdlogin);
    ENCODE_STRING(username);
    ENCODE_STRING(password);
    ENCODE_DWORD(ip);
    ENCODE_STRING(hwid);
    END_ENCODE();
}

static int DecodeLoginReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoLS_LoginReq);
    DECODE_DWORD(gssessid);
    DECODE_DWORD(clsessid);
    DECODE_BYTE(isthirdlogin);
    DECODE_STRING(username);
    DECODE_STRING(password);
    DECODE_DWORD(ip);
    DECODE_STRING(hwid);
    END_DECODE();
}

static int EncodeLoginAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoLS_LoginAck);
    ENCODE_DWORD(gssessid);
    ENCODE_DWORD(clsessid);
    ENCODE_STRING(username);
    ENCODE_QWORD(userid);
    ENCODE_WORD(result);
    ENCODE_STRING(info);
    ENCODE_DWORD(ip);
    ENCODE_STRING(hwid);
    ENCODE_INT64(isProhibitChat);
    ENCODE_BYTE(isSupport);
    END_ENCODE();
}

static int DecodeLoginAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoLS_LoginAck);
    DECODE_DWORD(gssessid);
    DECODE_DWORD(clsessid);
    DECODE_STRING(username);
    DECODE_QWORD(userid);
    DECODE_WORD(result);
    DECODE_STRING(info);
    DECODE_DWORD(ip);
    DECODE_STRING(hwid);
    DECODE_INT64(isProhibitChat);
    DECODE_BYTE(isSupport);
    END_DECODE();
}

static int EncodeSaveLoginReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoLS_SaveLoginReq);
    ENCODE_QWORD(player_guid);
    ENCODE_STRING(username);
    ENCODE_DWORD(token);
    ENCODE_STRING(randkey);
    ENCODE_DWORD(ip);
    ENCODE_STRING(hwid);
    ENCODE_STRING(channel);
    ENCODE_BYTE(isSaveProhibit);
    ENCODE_INT64(isProhibitChat);
    ENCODE_BYTE(isSaveSupport);
    ENCODE_BYTE(isSupport);
    END_ENCODE();
}

static int DecodeSaveLoginReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoLS_SaveLoginReq);
    DECODE_QWORD(player_guid);
    DECODE_STRING(username);
    DECODE_DWORD(token);
    DECODE_STRING(randkey);
    DECODE_DWORD(ip);
    DECODE_STRING(hwid);
    DECODE_STRING(channel);
    DECODE_BYTE(isSaveProhibit);
    DECODE_INT64(isProhibitChat);
    DECODE_BYTE(isSaveSupport);
    DECODE_BYTE(isSupport);
    END_DECODE();
}

static int EncodeLogoutNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoLS_LogoutNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_STRING(username);
    ENCODE_QWORD(playerid);
    END_ENCODE();
}

static int DecodeLogoutNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoLS_LogoutNtf);
    DECODE_DWORD(sessionid);
    DECODE_STRING(username);
    DECODE_QWORD(playerid);
    END_DECODE();
}

static int EncodeInsertPlayer(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoLS_InsertPlayer);
    ENCODE_QWORD(playerid);
    ENCODE_STRING(username);
    END_ENCODE();
}

static int DecodeInsertPlayer(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoLS_InsertPlayer);
    DECODE_QWORD(playerid);
    DECODE_STRING(username);
    END_DECODE();
}

static int EncodeRemoveContext(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoLS_RemoveContext);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodeRemoveContext(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoLS_RemoveContext);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodeGetLoginIpReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoLS_GetLoginIpReq);
    END_ENCODE();
}

static int DecodeGetLoginIpReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoLS_GetLoginIpReq);
    END_DECODE();
}

ProtoLS::ProtoLS()
{
    SET_ENCODER_DECODER(PROTO_LS_HEART_BEAT_REQ, EncodeHeartBeatReq, DecodeHeartBeatReq);
    SET_ENCODER_DECODER(PROTO_LS_HEART_BEAT_ACK, EncodeHeartBeatAck, DecodeHeartBeatAck);
    SET_ENCODER_DECODER(PROTO_LS_UPLOAD_CONFIG_REQ, EncodeUploadConfigReq, DecodeUploadConfigReq);
    SET_ENCODER_DECODER(PROTO_LS_CONFIG_REQ, EncodeConfigReq, DecodeConfigReq);
    SET_ENCODER_DECODER(PROTO_LS_CONFIG_ACK, EncodeConfigAck, DecodeConfigAck);
    SET_ENCODER_DECODER(PROTO_LS_LOGIN_REQ, EncodeLoginReq, DecodeLoginReq);
    SET_ENCODER_DECODER(PROTO_LS_LOGIN_ACK, EncodeLoginAck, DecodeLoginAck);
    SET_ENCODER_DECODER(PROTO_LS_SAVE_LOGIN_REQ, EncodeSaveLoginReq, DecodeSaveLoginReq);
    SET_ENCODER_DECODER(PROTO_LS_LOGOUT_NTF, EncodeLogoutNtf, DecodeLogoutNtf);
    SET_ENCODER_DECODER(PROTO_LS_INSERT_PLAYER, EncodeInsertPlayer, DecodeInsertPlayer);
    SET_ENCODER_DECODER(PROTO_LS_REMOVE_CONTEXT, EncodeRemoveContext, DecodeRemoveContext);
    SET_ENCODER_DECODER(PROTO_LS_GET_LOGIN_IP_REQ, EncodeGetLoginIpReq, DecodeGetLoginIpReq);

}

ProtoLS::~ProtoLS()
{

}

int ProtoLS::BuildProtocol(void* pHost, char* pNet, int iNetSize)
{
    unsigned short moduleid = *(unsigned short*)pHost;
    unsigned short protoid = *(unsigned short*)((char*)pHost + sizeof(unsigned short));
    if (moduleid != GetModuleID()) {
        return -1;
    }
    if (protoid >= PROTO_LS_MAX) {
        return -1;
    }

    CNetData m_oData;
    m_oData.Prepare(pNet, iNetSize);
    return m_EnCodeFuncArray[protoid](pHost, &m_oData);
}

int ProtoLS::HandleProtocol(void* pNet, char* pHost, int iNetSize)
{
    unsigned short moduleid = *(unsigned short*)pNet;
    unsigned short protoid = *(unsigned short*)((char*)pNet + sizeof(unsigned short));
    if (moduleid != GetModuleID()) {
        return -1;
    }
    if (protoid >= PROTO_LS_MAX) {
        return -1;
    }

    CNetData m_oData;
    m_oData.Prepare((char*)pNet, iNetSize);
    return m_DeCodeFuncArray[protoid](pHost, &m_oData);
}