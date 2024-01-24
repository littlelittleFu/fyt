#pragma once

#define EMSG_SERV_INTCONN_ERROR             u8"服务器内部连接异常"

// 2 - DB, 3 - CS, 4 - GS, 5 - MS, 6 - LS

#define EMSG_GS2LS_CONN_ERROR               EMSG_SERV_INTCONN_ERROR "(406)"
#define EMSG_GS2CS_CONN_ERROR               EMSG_SERV_INTCONN_ERROR "(403)"
#define EMSG_GS2MS_CONN_ERROR               EMSG_SERV_INTCONN_ERROR "(405)"

#define EMSG_LS2DB_CONN_ERROR               EMSG_SERV_INTCONN_ERROR "(602)"
#define EMSG_LS2CS_CONN_ERROR               EMSG_SERV_INTCONN_ERROR "(603)"
#define EMSG_LS2GS_CONN_ERROR               EMSG_SERV_INTCONN_ERROR "(604)"

#define EMSG_CS2DB_CONN_ERROR               EMSG_SERV_INTCONN_ERROR "(302)"
#define EMSG_CS2MS_CONN_ERROR               EMSG_SERV_INTCONN_ERROR "(305)"
#define EMSG_CS2LS_CONN_ERROR               EMSG_SERV_INTCONN_ERROR "(306)"

#define EMSG_MS2GS_CONN_ERROR               EMSG_SERV_INTCONN_ERROR "(504)"
#define EMSG_MS2CS_CONN_ERROR               EMSG_SERV_INTCONN_ERROR "(503)"
#define EMSG_MS2DB_CONN_ERROR               EMSG_SERV_INTCONN_ERROR "(502)"

#define EMSG_REPEAT_LOGIN                   u8"重复登录"
#define EMSG_NOT_LOGGED_IN                  u8"未登录"
#define EMSG_ALREADY_LOGGED_IN              u8"已登录"
#define EMSG_LOGGED_IN_ELSEWHERE            u8"已在其他地方登录"
#define EMSG_NO_USER_DATA                   u8"没有用户数据"
#define EMSG_INCONSIST_UID                  u8"用户ID不一致"
#define EMSG_NO_USERNAME                    u8"用户名不存在"
#define EMSG_WRONG_PASSWORD                 u8"密码不正确"
#define EMSG_UNKNOWN_ERROR                  u8"未知错误"
#define EMSG_INCONSIST_TOKEN                u8"用户数据不一致"
#define EMSG_VERIFY_TOKEN                   u8"验证失败"
#define EMSG_MAX_CLIENT_LIMIT               u8"该服过于火爆，请选择其他区服"
#define EMSG_INCONSIST_RANDKEY              u8"用户数据不一致"
#define EMSG_MAINTENANCE                    u8"维护中"
#define EMSG_PROHIBIT                       u8"已封禁"
#define EMSG_CLOSE                          u8"已关服"
