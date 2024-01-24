#pragma once

#include "ProtoDef.h"

#define DEF_PROTO_HEADER_LS(protoid) uint16_t moduleid = MODULE_TYPE_LS; uint16_t protocolid = protoid

enum
{
    PROTO_LS_HEART_BEAT_REQ,        // LS -> SS, DB, CS
    PROTO_LS_HEART_BEAT_ACK,        // SS, DB, CS -> LS
    PROTO_LS_UPLOAD_CONFIG_REQ,     // LS -> SS
    PROTO_LS_CONFIG_REQ,            // LS -> SS
    PROTO_LS_CONFIG_ACK,            // SS -> LS
    PROTO_LS_LOGIN_REQ,             // LS -> DB
    PROTO_LS_LOGIN_ACK,             // DB -> LS
    PROTO_LS_SAVE_LOGIN_REQ,        // LS -> CS
    PROTO_LS_LOGOUT_NTF,            // LS -> GS，用户已在其他地方登录，强制下线
    PROTO_LS_INSERT_PLAYER,         // LS -> DB，通过平台登录，在数据库插入一条记录
    PROTO_LS_REMOVE_CONTEXT,        // LS -> GS，通知GS移除老的SESSION CONTEXT
    PROTO_LS_GET_LOGIN_IP_REQ,
    PROTO_LS_MAX
};

struct ProtoLS_HeartBeatReq
{
    DEF_PROTO_HEADER_LS(PROTO_LS_HEART_BEAT_REQ);
};

struct ProtoLS_HeartBeatAck
{
    DEF_PROTO_HEADER_LS(PROTO_LS_HEART_BEAT_ACK);
};

struct ProtoLS_UploadConfigReq      // LS -> SS
{
    DEF_PROTO_HEADER_LS(PROTO_LS_UPLOAD_CONFIG_REQ);

    uint32_t    ip;
    uint32_t    port;

    ProtoLS_UploadConfigReq() : ip(0), port(0)
    {}
};

struct ProtoLS_ConfigReq            // LS -> SS
{
    DEF_PROTO_HEADER_LS(PROTO_LS_CONFIG_REQ);
};

struct ProtoLS_ConfigAck            // SS -> LS
{
    DEF_PROTO_HEADER_LS(PROTO_LS_CONFIG_ACK);

    uint32_t    dbServIp;
    uint32_t    dbServPort;
    uint32_t    centerServIp;
    uint32_t    centerServPort;
    uint32_t    logServIp;
    uint32_t    logServPort;

    ProtoLS_ConfigAck() : dbServIp(0), dbServPort(0), centerServIp(0), centerServPort(0), logServIp(0), logServPort(0)
    {}
};

struct ProtoLS_LoginReq             // LS -> DB
{
    DEF_PROTO_HEADER_LS(PROTO_LS_LOGIN_REQ);

    uint32_t                gssessid            = 0;
    uint32_t                clsessid            = 0;
    uint8_t                 isthirdlogin        = 0;

    uint32_t                ip                  = 0;
    char                    hwid[256]           = { 0 };
    char                    username[256]       = {0};
    char                    password[128]       = {0};
};

struct ProtoLS_LoginAck             // DB -> LS
{
    DEF_PROTO_HEADER_LS(PROTO_LS_LOGIN_ACK);

    uint32_t                gssessid            = 0;
    uint32_t                clsessid            = 0;

    char                    username[256]       = {0};
    uint64_t                userid              = 0;

    uint32_t                ip                  = 0;
    char                    hwid[256]           = { 0 };
    uint16_t                result              = 0;         // 0 - 成功，其他失败
    char                    info[256]           = {0};

    int64_t                 isProhibitChat      = 0;
    uint8_t                 isSupport           = 0;
};

struct ProtoLS_SaveLoginReq         // LS -> CS
{
    DEF_PROTO_HEADER_LS(PROTO_LS_SAVE_LOGIN_REQ);

    uint64_t                player_guid         = 0;
    char                    username[256]       = {0};          // 账号名

    uint32_t                token               = 0;
    char                    randkey[128]        = {0};          // 随机密钥

    uint32_t                ip                  = 0;            // 登录ip地址
    char                    hwid[256]           = {0};          // 硬件码

    char                    channel[256]        = {0};          // 渠道

    uint8_t                 isSaveProhibit      = 0;
    int64_t                 isProhibitChat      = 0;            // 账号禁言
    uint8_t                 isSaveSupport = 0;
    uint8_t                 isSupport = 0;
};

struct ProtoLS_LogoutNtf            // LS -> GS
{
    DEF_PROTO_HEADER_LS(PROTO_LS_LOGOUT_NTF);

    uint32_t    sessionid;

    char        username[256];
    uint64_t    playerid;

    ProtoLS_LogoutNtf() : sessionid(0), playerid(0)
    {
        memset(username, 0, sizeof(username));
    }
};

struct ProtoLS_InsertPlayer
{
    DEF_PROTO_HEADER_LS(PROTO_LS_INSERT_PLAYER);

    uint64_t    playerid        = 0;
    char        username[256]   = {0};
};

struct ProtoLS_RemoveContext
{
    DEF_PROTO_HEADER_LS(PROTO_LS_REMOVE_CONTEXT);

    uint32_t    sessionid       = 0;
};

struct ProtoLS_GetLoginIpReq
{
    DEF_PROTO_HEADER_LS(PROTO_LS_GET_LOGIN_IP_REQ);
};


class ProtoLS
{
public:
    ProtoLS();
    ~ProtoLS();

    static inline uint16_t GetModuleID(void) { return MODULE_TYPE_LS; }
    static inline uint16_t GetProtocolNum(void) { return PROTO_LS_MAX; }

    int BuildProtocol(void* pHost, char* pNet, int iNetSize);
    int HandleProtocol(void* pHost, char* pNet, int iNetSize);

private:
    EnCodeFunc m_EnCodeFuncArray[PROTO_LS_MAX];
    DeCodeFunc m_DeCodeFuncArray[PROTO_LS_MAX];
};
