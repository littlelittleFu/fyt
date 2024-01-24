#pragma once

#include "ProtoDef.h"

#define DEF_PROTO_HEADER_CLIENT7(protoid) uint16_t moduleid = MODULE_TYPE_CLIENT7; uint16_t protocolid = protoid

enum
{
    PROTO_CLIENT7_ERROR_ACK             = 0,
    PROTO_CLIENT7_POP_DLG_MSG_NTF       = 12,
    PROTO_CLIENT7_MSG_NTF               = 28,
    PROTO_CLIENT7_GM_ERROR_ACK          = 29,
    PROTO_CLIENT7_MAX
};

struct ProtoClient7_ErrorAck
{
    DEF_PROTO_HEADER_CLIENT7(PROTO_CLIENT7_ERROR_ACK);

    int32_t                     ecode               = -1;           // ������
    uint64_t                    guid                = 0;            // role id
};

struct ProtoClient7_MsgNtf
{
    DEF_PROTO_HEADER_CLIENT7(PROTO_CLIENT7_MSG_NTF);

    uint8_t                     foreground = 0;            // ��Ϣǰ����ɫID
    uint8_t                     background = 0;            // ��Ϣ������ɫID
    uint8_t                     count      = 0;            // ��Ϣ��������
    uint8_t                     type       = 0;            // ��Ϣλ��   0:top  1:center  2:bottom
    char                        msg[256]   ={0};           // ��Ϣ����
};

struct ProtoClient7_PopDlgMsgNtf
{
    DEF_PROTO_HEADER_CLIENT7(PROTO_CLIENT7_POP_DLG_MSG_NTF);

    char                        msg[256]            = {0};          // ��Ϣ����
};

struct ProtoClient7_GMErrorAck
{
    DEF_PROTO_HEADER_CLIENT7(PROTO_CLIENT7_GM_ERROR_ACK);

    int32_t                     sn                  = 0;            // ���к�
    int32_t                     ecode               = -1;           // ������
    uint64_t                    guid                = 0;            // role id
};

class ProtoClient7
{
public:
    ProtoClient7();
    ~ProtoClient7();

    static uint16_t GetModuleID() { return MODULE_TYPE_CLIENT7; }
    static uint16_t GetProtocolNum() { return PROTO_CLIENT7_MAX; }

    int BuildProtocol(void* pHost, char* pNet, int iNetSize);
    int HandleProtocol(void* pHost, char* pNet, int iNetSize);

private:
    EnCodeFunc m_EnCodeFuncArray[PROTO_CLIENT7_MAX];
    DeCodeFunc m_DeCodeFuncArray[PROTO_CLIENT7_MAX];
};
