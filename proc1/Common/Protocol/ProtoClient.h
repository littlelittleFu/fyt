#pragma once

#include "ProtoDef.h"


#define DEF_PROTO_HEADER_CLIENT(protoid) uint16_t moduleid = MODULE_TYPE_CLIENT; uint16_t protocolid = protoid

enum
{
    PROTO_CLIENT_LOGIN_REQ              = 0,        // CLIENT -> GS
    PROTO_CLIENT_LOGIN_ACK              = 1,        // GS -> CLIENT
    PROTO_CLIENT_LOGOUT_REQ             = 2,        // CLIENT -> GS
    PROTO_CLIENT_CREATE_ROLE_REQ        = 3,        // CLIENT -> GS
    PROTO_CLIENT_CREATE_ROLE_ACK        = 4,        // GS -> CLIENT
    PROTO_CLIENT_DEL_ROLE_REQ           = 5,        // CLIENT -> GS
    PROTO_CLIENT_DEL_ROLE_ACK           = 6,        // GS -> CLIENT
    PROTO_CLIENT_RECOVER_ROLE_REQ       = 7,        // CLIENT -> GS
    PROTO_CLIENT_RECOVER_ROLE_ACK       = 8,        // GS -> CLIENT
    PROTO_CLIENT_GET_ROLE_LIST_REQ      = 9,        // CLIENT -> GS
    PROTO_CLIENT_GET_ROLE_LIST_ACK      = 10,       // GS -> CLIENT
    PROTO_CLIENT_KICK_USER_NTF          = 11,       // GS -> CLIENT
    PROTO_CLIENT_RANDKEY_NTF            = 12,       // GS -> CLIENT，建立连接时分配随机密钥
    PROTO_CLIENT_RELOGIN_REQ            = 13,       // CLIENT -> GS
    PROTO_CLIENT_RELOGIN_ACK            = 14,       // GS -> CLIENT
    PROTO_CLIENT_THIRD_LOGIN_REQ        = 15,       // CLIENT -> GS
    PROTO_CLIENT_HEART_BEAT_REQ         = 19,       // CLIENT -> GS
    PROTO_CLIENT_HEART_BEAT_ACK         = 20,       // GS -> CLIENT
    PROTO_CLIENT_CONN_REQ               = 25,       // CLIENT -> GS
    PROTO_CLIENT_CONN_ACK               = 26,       // GS -> CLIENT


    PROTO_CLIENT_ENTER_MAP_REQ,         // CLIENT->GS->CS
    PROTO_CLIENT_ENTER_MAP_ACK,         // GS->CLIENT

    PROTO_CLIENT_CREATE_ROLE_REQ_EX,
    PROTO_CLIENT_MAX
};

struct ProtoClient_LoginReq
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_LOGIN_REQ);

    char        username[256];                                          // 账号名
    uint32_t    ip                      = 0;                            // 登陆ip地址
    uint32_t    pwdlen                  = 0;                            // 密码密文长度
    uint8_t     password[128];                                          // 密码密文
    char        hwid[256];                                              // 硬件码

    ProtoClient_LoginReq() {
        memset(username, 0, sizeof(username));
        memset(password, 0, sizeof(password));
        memset(hwid, 0, sizeof(hwid));
    }
};

struct ProtoClient_LoginAck
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_LOGIN_ACK);

    uint64_t    playerid                = 0;
    int32_t     errcode                 = -1;                           // 错误码
    char        errmsg[256];                                            // 错误描述

    ProtoClient_LoginAck() {
        memset(errmsg, 0, sizeof(errmsg));
    }
};

struct ProtoClient_ThirdLoginReq
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_THIRD_LOGIN_REQ);

    char                        channel[16]             = {0};              // 渠道信息
    uint32_t                    gameid                  = 0;                // 游戏id
    char                        token[256]              = {0};              // 验证token

    char                        user_name[256]          = {0};              // 用户名
    uint32_t                    login_ip                = 0;                // 登录ip
    char                        hwid[256]               = {0};              // 硬件码
};

struct ProtoClient_LogoutReq
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_LOGOUT_REQ);

    uint8_t     info                    = 0;                            // 登出类型 1=打退, 2=小退
};

struct ProtoClient_CreateRoleReq
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_CREATE_ROLE_REQ);

    ROLE_BRIEF_INFO     createrole;                                     // 新建角色的基础信息

    ProtoClient_CreateRoleReq() {
        memset(&createrole, 0, sizeof(createrole));
    }
};

struct ProtoClient_CreateRoleReqEx
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_CREATE_ROLE_REQ_EX);

    ROLE_BRIEF_INFO     createrole;                                     // 新建角色的基础信息
    uint64_t            digCode = 0;                                    // 数字校验码
    ProtoClient_CreateRoleReqEx()
    {
        memset(&createrole, 0, sizeof(createrole));
    }
};

struct ProtoClient_CreateRoleAck
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_CREATE_ROLE_ACK);

    int32_t             errcode         = -1;                           // 错误码
    char                errmsg[256];                                    // 错误描述
    ROLE_BRIEF_INFO     newrole;                                        // 角色简要信息列表

    ProtoClient_CreateRoleAck()
    {
        memset(errmsg, 0, sizeof(errmsg));
        memset(&newrole, 0, sizeof(newrole));
    }
};

struct ProtoClient_GetRoleListReq
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_GET_ROLE_LIST_REQ);
};

struct ProtoClient_GetRoleListAck
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_GET_ROLE_LIST_ACK);

    int32_t             errcode         = -1;               // 错误码
    char                errmsg[256];                        // 错误描述
    uint8_t             rolenum         = 0;                // 角色列表中的角色数量
    uint64_t            last_role       = 0;                // 上次选择角色
    ROLE_BRIEF_INFO     rolelist[10];                       // 角色简要信息列表
    uint8_t             needCode        = 0;                // 创建角色是否需要校验码,0不需要,1需要
    ProtoClient_GetRoleListAck()
    {
        memset(errmsg, 0, sizeof(errmsg));
        memset(rolelist, 0, sizeof(rolelist));
    }
};

struct ProtoClient_RandKeyNtf
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_RANDKEY_NTF);

    uint32_t    codelen     = 0;        // 随机密钥长度
    uint8_t     code[128];              // 随机密钥

    ProtoClient_RandKeyNtf()
    {
        memset(code, 0, sizeof(code));
    }
};

struct ProtoClient_ReloginReq
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_RELOGIN_REQ);

    uint64_t            player_guid     = 0;        // 账号id
    uint64_t            role_guid       = 0;        // 角色id
    char                randkey[128]    = {0};      // 会话密钥
    char                hwid[256] = { 0 };
};

struct ProtoClient_ReloginAck
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_RELOGIN_ACK);

    int32_t     errcode     = -1;       // 错误码
    char        errmsg[256];            // 错误描述

    ProtoClient_ReloginAck()
    {
        memset(errmsg, 0, sizeof(errmsg));
    }
};

struct ProtoClient_HeartBeatReq
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_HEART_BEAT_REQ);
};

struct ProtoClient_HeartBeatAck
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_HEART_BEAT_ACK);
};

struct ProtoClient_KickUserNtf
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_KICK_USER_NTF);

    int32_t     errcode     = -1;
    char        errmsg[256];

    ProtoClient_KickUserNtf()
    {
        memset(errmsg, 0, sizeof(errmsg));
    }
};

struct ProtoClient_ConnReq
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_CONN_REQ);

    uint32_t    version     = 0;        // 客户端的版本
    uint32_t    zone        = 0;
};

struct ProtoClient_ConnAck
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_CONN_ACK);

    uint32_t    errcode     = 0;        // 0表示成功，参考hand_err
    int32_t     overload    = 0;        // 当前网关的负载
    int32_t     delay       = 0;        // 当前网关的设置延迟
};


struct ProtoClient_EnterMapReq
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_ENTER_MAP_REQ);
    char        username[256];
};


struct ProtoClient_EnterMapAck
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_ENTER_MAP_ACK);

    int32_t     Id      = 0;         // 地图索引
};

struct ProtoClient_DeleteRoleReq
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_DEL_ROLE_REQ);

    uint64_t        guid        = 0;
};

struct ProtoClient_RestoreRoleReq
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_RECOVER_ROLE_REQ);

    uint64_t        guid = 0;
};

struct ProtoClient_DeleteRoleAck
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_DEL_ROLE_ACK);

    uint64_t        guid        = 0;
    int             errcode     = -1;       // 错误码
    char            errmsg[256];            // 错误描述

    ProtoClient_DeleteRoleAck()
    {
        memset(errmsg, 0, sizeof(errmsg));
    }
};
struct  ProtoClient_RestoreRoleAck
{
    DEF_PROTO_HEADER_CLIENT(PROTO_CLIENT_RECOVER_ROLE_ACK);

    int             errcode = -1;
    char            errmsg[256];
    ROLE_BRIEF_INFO           role;

    ProtoClient_RestoreRoleAck()
    {
        memset(errmsg, 0, sizeof(errmsg));
    }
};

class ProtoClient
{
public:
    ProtoClient();
    ~ProtoClient();

    static inline uint16_t GetModuleID(void) { return MODULE_TYPE_CLIENT; }
    static inline uint16_t GetProtocolNum(void) { return PROTO_CLIENT_MAX; }

    int BuildProtocol(void* pHost, char* pNet, int iNetSize);
    int HandleProtocol(void* pHost, char* pNet, int iNetSize);

private:
    EnCodeFunc m_EnCodeFuncArray[PROTO_CLIENT_MAX];
    DeCodeFunc m_DeCodeFuncArray[PROTO_CLIENT_MAX];
};
