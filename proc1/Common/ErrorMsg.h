#pragma once

#define EMSG_SERV_INTCONN_ERROR             u8"�������ڲ������쳣"

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

#define EMSG_REPEAT_LOGIN                   u8"�ظ���¼"
#define EMSG_NOT_LOGGED_IN                  u8"δ��¼"
#define EMSG_ALREADY_LOGGED_IN              u8"�ѵ�¼"
#define EMSG_LOGGED_IN_ELSEWHERE            u8"���������ط���¼"
#define EMSG_NO_USER_DATA                   u8"û���û�����"
#define EMSG_INCONSIST_UID                  u8"�û�ID��һ��"
#define EMSG_NO_USERNAME                    u8"�û���������"
#define EMSG_WRONG_PASSWORD                 u8"���벻��ȷ"
#define EMSG_UNKNOWN_ERROR                  u8"δ֪����"
#define EMSG_INCONSIST_TOKEN                u8"�û����ݲ�һ��"
#define EMSG_VERIFY_TOKEN                   u8"��֤ʧ��"
#define EMSG_MAX_CLIENT_LIMIT               u8"�÷����ڻ𱬣���ѡ����������"
#define EMSG_INCONSIST_RANDKEY              u8"�û����ݲ�һ��"
#define EMSG_MAINTENANCE                    u8"ά����"
#define EMSG_PROHIBIT                       u8"�ѷ��"
#define EMSG_CLOSE                          u8"�ѹط�"
