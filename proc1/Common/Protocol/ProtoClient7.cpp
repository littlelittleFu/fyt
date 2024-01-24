#include "stdafx.h"
#include "ProtoClient7.h"
#include "ILogHelper.h"

static int EncodeErrorAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient7_ErrorAck);
    ENCODE_INT(ecode);
    ENCODE_QWORD(guid);
    END_ENCODE();
}

static int DecodeErrorAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient7_ErrorAck);
    DECODE_INT(ecode);
    DECODE_QWORD(guid);
    END_DECODE();
}

static int EncodeMsgNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient7_MsgNtf);
    ENCODE_BYTE(foreground);
    ENCODE_BYTE(background);
    ENCODE_BYTE(count);
    ENCODE_BYTE(type);
    ENCODE_STRING(msg);
    END_ENCODE();
}

static int DecodeMsgNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient7_MsgNtf);
    DECODE_BYTE(foreground);
    DECODE_BYTE(background);
    DECODE_BYTE(count);
    DECODE_BYTE(type);
    DECODE_STRING(msg);
    END_DECODE();
}

static int EncodePopDlgMsgNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient7_PopDlgMsgNtf);
    ENCODE_STRING(msg);
    END_ENCODE();
}

static int DecodePopDlgMsgNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient7_PopDlgMsgNtf);
    DECODE_STRING(msg);
    END_DECODE();
}

static int EncodeGMErrorAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient7_GMErrorAck);
    ENCODE_INT(sn);
    ENCODE_INT(ecode);
    ENCODE_QWORD(guid);
    END_ENCODE();
}

static int DecodeGMErrorAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient7_GMErrorAck);
    DECODE_INT(sn);
    DECODE_INT(ecode);
    DECODE_QWORD(guid);
    END_DECODE();
}

ProtoClient7::ProtoClient7()
{
    for (auto i = 0; i < PROTO_CLIENT7_MAX; ++i) {
        SET_ENCODER_DECODER(i, EncodeNotImpl, DecodeNotImpl);
    }

    SET_ENCODER_DECODER(PROTO_CLIENT7_ERROR_ACK, EncodeErrorAck, DecodeErrorAck);
    SET_ENCODER_DECODER(PROTO_CLIENT7_MSG_NTF, EncodeMsgNtf, DecodeMsgNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT7_POP_DLG_MSG_NTF, EncodePopDlgMsgNtf, DecodePopDlgMsgNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT7_GM_ERROR_ACK, EncodeGMErrorAck, DecodeGMErrorAck);
}

ProtoClient7::~ProtoClient7()
{

}

int ProtoClient7::BuildProtocol(void* pHost, char* pNet, int iNetSize)
{
    uint16_t moduleid = *(uint16_t*)pHost;
    uint16_t protoid = *((uint16_t*)pHost + 1);

    if (moduleid != GetModuleID()) return -1;
    if (protoid >= PROTO_CLIENT7_MAX) return -1;

    CNetData netData;
    netData.Prepare(pNet, iNetSize);
    return m_EnCodeFuncArray[protoid](pHost, &netData);
}

int ProtoClient7::HandleProtocol(void* pHost, char* pNet, int iNetSize)
{
    uint16_t moduleid = *(uint16_t*)pNet;
    uint16_t protoid = *((uint16_t*)pNet + 1);

#ifndef _HIDE_PROTO_LOG
    LOG_TRACE("moduleid: %d, protoid: %d", moduleid, protoid);
#endif // !_HIDE_PROTO_LOG


    if (moduleid != GetModuleID()) return -1;
    if (protoid >= PROTO_CLIENT7_MAX) return -1;

    CNetData netData;
    netData.Prepare((char*)pNet, iNetSize);
    return m_DeCodeFuncArray[protoid](pHost, &netData);
}
