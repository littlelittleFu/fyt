#pragma once

#include "ProtoDef.h"

#define DEF_PROTO_HEADER_DB(protoid) uint16_t moduleid = MODULE_TYPE_DB; uint16_t protocolid = protoid

enum
{
    PROTO_DB_HEART_BEAT_REQ,
    PROTO_DB_HEART_BEAT_ACK,
    PROTO_DB_UPLOAD_CONFIG_REQ,
    PROTO_DB_QUEST_INFO,            // DB -> CS
    PROTO_DB_GET_CUST_VAR_ACK,      // DB -> CS
    PROTO_DB_PLAYER_CUST_VAR,       // DB -> CS
    PROTO_DB_PLAYER_ITEM_CUST_VAR,  // DB -> CS
    PROTO_DB_QUICK_BAR_SET_NTF,     // DB -> CS
    PROTO_DB_GLOBAL_NTF,
    PROTO_DB_DGN_BIND_INFO_NTF,     // DB -> CS
    PROTO_DB_TOPLIST_ACK,
    PROTO_DB_ADD_MAIL_ACK,
    PROTO_DB_GET_MAIL_INFO_ACK,    
    PROTO_DB_ITEM_DYN_ATTR_NTF,     // DB -> CS
    PROTO_DB_ROLE_DYN_ATTR_NTF,     // DB -> CS
    PROTO_DB_CONFIG_REQ,
    PROTO_DB_CONFIG_ACK,
    PROTO_DB_GET_LOGIN_IP_ACK,
    PROTO_DB_SYNC_LOGIN_TYPE_TO_LS,
    PROTO_DB_GET_PROHIBIT_CHAT_INFO_ACK,
    PROTO_DB_GOODS_NOT_ISSUED_RECORDS_NTF,
    PROTO_DB_PLAYER_SET_NAME_ACK,
    PROTO_DB_GET_TITLE_INFO_ACK,
    PROTO_DB_DEL_LOCK_ROlE_ACK,
    PROTO_DB_REBATE_MONEY_NOT_USED_RECORD_NTF,
    PROTO_DB_GET_CUST_LIST_INFO_ACK,
    PROTO_DB_GOODS_NOT_POST_RECORDS_NTF,
	PROTO_DB_MAX,   
};

struct ProtoDB_GetCustListInfoAck
{
    DEF_PROTO_HEADER_DB(PROTO_DB_GET_CUST_LIST_INFO_ACK);
    uint16_t       num = 0;
    CUST_LIST_INFO data[100];
    ProtoDB_GetCustListInfoAck()
    {
        memset(data, 0, sizeof(data));
    }
};

struct ProtoDB_DelLockRoleAck
{
    DEF_PROTO_HEADER_DB(PROTO_DB_DEL_LOCK_ROlE_ACK);
    uint16_t num = 0;
    uint64_t userID[100] = { 0 };
    uint64_t guid[100] = { 0 };
    ProtoDB_DelLockRoleAck() = default;
};

struct ProtoDB_GetTitleInfoAck
{
    DEF_PROTO_HEADER_DB(PROTO_DB_GET_TITLE_INFO_ACK);
    uint64_t playerguid = 0;
    uint64_t guid = 0;
    uint16_t num = 0;
    TITLE_INFO  info[100];
    ProtoDB_GetTitleInfoAck() = default;
};

struct ProtoDB_PlayerSetNameAck
{
    DEF_PROTO_HEADER_DB(PROTO_DB_PLAYER_SET_NAME_ACK);
    uint16_t errcode  = 0;
    uint64_t guid     = 0;
    uint64_t userid   = 0;
    char     orgName[32];
    char     name[32];
    ProtoDB_PlayerSetNameAck() {
        memset(orgName, 0, _countof(orgName));
        memset(name, 0, _countof(name));
    }
};

struct ProtoDB_GetProhibitChatInfoAck
{
    DEF_PROTO_HEADER_DB(PROTO_DB_GET_PROHIBIT_CHAT_INFO_ACK);
    uint8_t num = 0;
    PROHIBIT_CHAT_DATA   infos[100];
    ProtoDB_GetProhibitChatInfoAck() = default;
};

struct ProtoDB_SyncLoginTypeToLS
{
    enum opt_type
    {
        add = 1,
        del = 2,
    };
    DEF_PROTO_HEADER_DB(PROTO_DB_SYNC_LOGIN_TYPE_TO_LS);
    uint8_t num = 0;
    uint8_t opt_type = 0;
    LOGIN_IP_DATA   infos[100];
    ProtoDB_SyncLoginTypeToLS() = default;
};

struct ProtoDB_GetLoginIpAck
{
    DEF_PROTO_HEADER_DB(PROTO_DB_GET_LOGIN_IP_ACK);
    uint16_t        num = 0;
    LOGIN_IP_DATA   infos[100];
    ProtoDB_GetLoginIpAck()
    {
        memset(infos, 0, sizeof(infos));
    };
};

struct ProtoDB_GetMailInfoAck
{
    DEF_PROTO_HEADER_DB(PROTO_DB_GET_MAIL_INFO_ACK);
    uint16_t        num = 0;
    MAIL_INFO       infos[100];
    ProtoDB_GetMailInfoAck() = default;
};

struct ProtoDB_AddMailAck
{
    DEF_PROTO_HEADER_DB(PROTO_DB_ADD_MAIL_ACK);
    uint8_t         num = 0;
    uint16_t        err_type = 0;
    MAIL_INFO       infos[100];
    ProtoDB_AddMailAck() = default;
};

struct ProtoDB_GlobalNtf
{
    DEF_PROTO_HEADER_DB(PROTO_DB_GLOBAL_NTF);
    uint64_t       role_id = 0;
    uint64_t       userid = 0;
    unsigned short int_count = 0;      //整形数据个数
    IntData        int_data[256];  //数据值
    unsigned short str_count = 0;      //字符型数据个数
    StrData        str_data[256];
    ProtoDB_GlobalNtf() = default;
};

struct ProtoDB_QuickBarSetNtf
{
    DEF_PROTO_HEADER_DB(PROTO_DB_QUICK_BAR_SET_NTF);
    unsigned short            num = 0;
    uint64_t                  role_id = 0;
    uint64_t                  userid = 0;
    QUICK_BAR_INFO            info[30];
    ProtoDB_QuickBarSetNtf()
    {
        memset(info, 0, sizeof(info));
    }
};
// 回复给CS
struct ProtoDB_DgnBindInfoNtf
{
    enum DBI_MaxSize
    {
        Info_Size = 50
    };
    DEF_PROTO_HEADER_DB(PROTO_DB_DGN_BIND_INFO_NTF);
    uint16_t                    num = 0;
    uint64_t                    roleId = 0;
    uint64_t                    userid = 0;
    DGN_BIND_INFO               info[Info_Size];

};

struct ProtoDB_HeartBeatReq
{
    DEF_PROTO_HEADER_DB(PROTO_DB_HEART_BEAT_REQ);
};

struct ProtoDB_HeartBeatAck
{
    DEF_PROTO_HEADER_DB(PROTO_DB_HEART_BEAT_ACK);
};

struct ProtoDB_UploadConfigReq
{
    DEF_PROTO_HEADER_DB(PROTO_DB_UPLOAD_CONFIG_REQ);

    uint32_t                    ip                  = 0;
    uint32_t                    port                = 0;
};

struct ProtoDB_ConfigReq
{
    DEF_PROTO_HEADER_DB(PROTO_DB_CONFIG_REQ);
};

struct ProtoDB_ConfigAck
{
    DEF_PROTO_HEADER_DB(PROTO_DB_CONFIG_ACK);

    uint32_t    logServIp = 0;
    uint32_t    logServPort = 0;
};

struct ProtoDB_QuestInfo
{
    DEF_PROTO_HEADER_DB(PROTO_DB_QUEST_INFO);

    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;

    QUEST_INFO                  quest_info;

    uint8_t                     achev_data_num      = 0;
    QUEST_ACHIEVE               achev_data[50];

    ProtoDB_QuestInfo()
    {
        memset(&quest_info, 0, sizeof(quest_info));
        memset(achev_data, 0, sizeof(achev_data));
    }
};

struct ProtoDB_GetCustVarAck
{
    DEF_PROTO_HEADER_DB(PROTO_DB_GET_CUST_VAR_ACK);

    CUST_VAR_SP_LIST           *vars                = nullptr;
};

struct ProtoDB_PlayerCustVar
{
    DEF_PROTO_HEADER_DB(PROTO_DB_PLAYER_CUST_VAR);

    uint64_t                    playerid            = 0;
    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;

    CUST_VAR_MAP               *vars                = nullptr;
};

struct ProtoDB_PlayerItemCustVar
{
    DEF_PROTO_HEADER_DB(PROTO_DB_PLAYER_ITEM_CUST_VAR);

    uint64_t                    playerid            = 0;
    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;

    CUST_VAR_SP_LIST           *vars                = nullptr;
};

struct ProtoDB_GetTopListAck
{
    DEF_PROTO_HEADER_DB(PROTO_DB_TOPLIST_ACK);
    uint8_t                  type = 0;
    uint8_t                  TopListNum = 0;
    uint64_t                 rolelist[100];
    TOPLIST_INFO             TopList[100];
    ProtoDB_GetTopListAck()
    {
        memset(rolelist, 0, sizeof(rolelist));
        memset(TopList, 0, sizeof(TopList));
    }
};

struct ProtoDB_ItemDynAttrNtf
{
    DEF_PROTO_HEADER_DB(PROTO_DB_ITEM_DYN_ATTR_NTF);

    uint64_t                    playerid            = 0;
    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;

    ITEM_DYN_ATTRS_LIST        *item_dyn_attrs_list = nullptr;
};

struct ProtoDB_RoleDynAttrNtf
{
    DEF_PROTO_HEADER_DB(PROTO_DB_ROLE_DYN_ATTR_NTF);

    uint64_t                    playerid = 0;
    uint64_t                    roleid = 0;
    uint32_t                    token = 0;

    ROLE_DYN_ATTRS_LIST* role_dyn_attrs_list = nullptr;
};

struct ProtoDB_GoodsNotIssuedRecordsNtf
{
    DEF_PROTO_HEADER_DB(PROTO_DB_GOODS_NOT_ISSUED_RECORDS_NTF);

    uint64_t                    player_guid         = 0;
    uint64_t                    role_guid           = 0;
    uint8_t                     num                 = 0;
    GOODS_ISSUE_RECORD          records[MAX_GOODS_ISSUE_RECORD];
};

struct ProtoDB_GoodsNotPostRecordsNtf
{
    DEF_PROTO_HEADER_DB(PROTO_DB_GOODS_NOT_POST_RECORDS_NTF);

    uint64_t                    player_guid = 0;
    uint64_t                    role_guid = 0;
    uint8_t                     num = 0;
    GOODS_ISSUE_RECORD          records[MAX_GOODS_POST_RECORD];
};

struct ProtoDB_RebateMoneyNotUsedRecordNtf
{
    DEF_PROTO_HEADER_DB(PROTO_DB_REBATE_MONEY_NOT_USED_RECORD_NTF);

    uint64_t                    role_guid = 0;
    REBATE_MONEY_RECORD         record;
};

class ProtoDB
{
public:
    ProtoDB();
    ~ProtoDB();

    static inline uint16_t GetModuleID(void) { return MODULE_TYPE_DB; }
    static inline uint16_t GetProtocolNum(void) { return PROTO_DB_MAX; }

    int BuildProtocol(void* pHost, char* pNet, int iNetSize);
    int HandleProtocol(void* pHost, char* pNet, int iNetSize);

private:
    EnCodeFunc m_EnCodeFuncArray[PROTO_DB_MAX];
    DeCodeFunc m_DeCodeFuncArray[PROTO_DB_MAX];
};
