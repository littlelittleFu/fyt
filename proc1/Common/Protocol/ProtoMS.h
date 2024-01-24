#pragma once

#include "ProtoDef.h"
#include "ProtoLog.h"

#define DEF_PROTO_HEADER_MS(protoid) uint16_t moduleid = MODULE_TYPE_MS; uint16_t protocolid = protoid
#define REDEF_PROTO_HEADER_MS(protoid) moduleid = MODULE_TYPE_MS; protocolid = protoid

enum
{
    PROTO_MS_HEART_BEAT_REQ,
    PROTO_MS_HEART_BEAT_ACK,
    PROTO_MS_ENTER_MS_ACK,
    PROTO_MS_UPLOAD_CONFIG_REQ,
    PROTO_MS_CONFIG_REQ,
    PROTO_MS_CONFIG_ACK,

    PROTO_MS_GET_INFO_REQ,
    PROTO_MS_GET_INFO_ACK,

    PROTO_MS_MOVE_NTF,
    PROTO_MS_PLAYER_APPEAR_NTF,
    PROTO_MS_NPC_TALK_REQ,
    PROTO_MS_NPC_TALK_ACK,
    PROTO_MS_ENTER_MS_NTF,
    PROTO_MS_ATTR_SHOW_NTF2_EX2,
    PROTO_MS_SPELL_NTF,
    PROTO_MS_ERROR_ACK,
    PROTO_MS_MONSTER_APPEAR_NTF6,
    PROTO_MS_OBJDIE_NTF,
    PROTO_MS_SKILL_ADD_ACK,
	PROTO_MS_DISAPPEAR_NTF,           // ms ->gs-> client
    PROTO_MS_ITEM_ACK,           // ms ->gs-> client
    PROTO_MS_ROLE_ATTR_NTF,           // ms ->gs-> client
    PROTO_MS_ROLE_ATTR_EXT_NTF,           // ms ->gs-> client
    PROTO_MS_ITEM_DESTROY_ACK,//5
    PROTO_MS_ITEM_UPDATE_NTF,//39
    PROTO_MS_GET_SKILL_ACK,
    PROTO_MS_GET_BUFF_ACK,
    PROTO_MS_SYNC_BUFF_REQ,                 // MS -> CS
    PROTO_MS_BUFF_ADD_ACK,
    PROTO_MS_BUFF_DESTROY_ACK,
    PROTO_MS_GET_ITEM_ACK,
    PROTO_MS_ITEM_PICK_UP,
    PROTO_MS_ITEM_APPEAR_NTF4,
    PROTO_MS_ITEM_ATTR_NTF,
    PROTO_MS_RUN_CLIENT_SCRIPT,     // MS -> GS -> CLIENT
    PROTO_MS_SEND_SYNC_ITEM_NTF,     // MS -> CS 
    PROTO_MS_SEND_DEL_ITEM_NTF,
    PROTO_MS_GET_ROLE_INFO_REQ,//SEND TO DB
    PROTO_MS_CLEAR_ROLE_INFO_NTF,
    PROTO_MS_DELETE_ROLE_INFO_NTF,
    PROTO_MS_INSERT_ROLE_INFO_NTF,//SEND TO DB
    PROTO_MS_UPDATE_ROLE_INFO_NTF,//SEND TO DB
    PROTO_MS_GET_ROLE_INFO_ACK,//SEND TO DB
    PROTO_MS_SYS_MSG_NTF,           // MS -> GS -> CLIENT
    PROTO_MS_SYNC_SKILL_REQ,                // MS -> CS
    PROTO_MS_SYNC_ROLE_INFO_REQ,            // MS -> CS
    PROTO_MS_SYNC_ROLE_DYN_ATTRS,        // MS -> CS
    PROTO_MS_NPC_APPEAR_NTF,                // MS -> GS
    PROTO_MS_TRADE_NPC_SHOP_NTF,            // MS -> GS
    PROTO_MS_SYNC_QUEST_REQ,                // MS -> CS
    PROTO_MS_QUEST_NPC_TALK_ACK,            // MS -> GS
    PROTO_MS_QUEST_TIMEOUT_NTF,             // MS -> GS
    PROTO_MS_QUEST_UPDATE_NTF,              // MS -> GS
    PROTO_MS_QUEST_DROP_NTF,                // MS -> GS
    PROTO_MS_QUEST_STATE_NTF,               // MS -> GS
    PROTO_MS_QUEST_NPC_STATE_NTF,           // MS -> GS
    PROTO_MS_TEAM_NTF,
    PROTO_MS_MISS_TEAM_NTF,
    PROTO_MS_TEAM_INVITE_NTF,
    PROTO_MS_GET_ARROUND_TEAM_ACK,
    PROTO_MS_TEAM_JOIN_NTF,
    PROTO_MS_TEAM_LEADER_NTF,
    PROTO_MS_ROLE_ATTR_EXT_REF_NTF,         // MS -> GS
    PROTO_MS_LEVEL_UP_NTF,                  // MS -> GS
    PROTO_MS_ROLE_APP_NTF,                  // MS -> GS

    PROTO_MS_GET_GUILDS_REQ,                // MS -> CS
    PROTO_MS_GET_GUILD_MEMBERS_REQ,         // MS -> CS
    PROTO_MS_GET_GUILD_APPLICANTS_REQ,      // MS -> CS
    PROTO_MS_FAMILY_NOTICE_ACK,             // MS -> GS
    PROTO_MS_FAMILY_MEMBERS_ACK,            // MS -> GS
    PROTO_MS_FAMILY_ENEMY_ACK,              // MS -> GS
    PROTO_MS_FAMILY_ALLY_ACK,               // MS -> GS
    PROTO_MS_FAMILY_JOIN_LIST_ACK,          // MS -> GS
    PROTO_MS_FAMILY_BASE_INFO_ACK,          // MS -> GS
    PROTO_MS_FAMILY_LIST_NTF_ACK,           // MS -> GS
    PROTO_MS_SYNC_PLAYER_CUST_VAR,          // MS -> CS
    PROTO_MS_PLAYER_FAMILY_CHANGE_NTF,      // MS -> GS
    PROTO_MS_SYNC_GUILD_APPLICANT,          // MS -> CS
    PROTO_MS_CANCEL_FAMILY_JOIN_ACK,        // MS -> GS
    PROTO_MS_SYNC_GUILD_MEMBER,             // MS -> CS
    PROTO_MS_FAMILY_LEAVE_NTF,              // MS -> GS
    PROTO_MS_FAMILY_INFO_NTF,               // MS -> GS
    PROTO_MS_SYNC_GUILD_INFO,               // MS -> CS
    PROTO_MS_SYNC_GUILD_RELATION,           // MS -> CS

    PROTO_MS_SET_CUST_VAR,                  // MS -> CS
    PROTO_MS_SYNC_PLAYER_ITEM_CUST_VAR,     // MS -> CS
    PROTO_MS_GET_CUST_VAR_REQ,              // MS -> CS
    PROTO_MS_PLAYER_QUERY_NTF,              // MS -> GS

    PROTO_MS_QUICK_BAR_SET,                 //ms->CS
    PROTO_MS_QUICK_BAR_SET_NTF,             //MS->GS
    PROTO_MS_GLOBAL_NTF,                    //ms->gs

    PROTO_MS_DGN_BIND_INFO,             //ms->CS

    PROTO_MS_UPDATE_TOPLIST_ACK,

    PROTO_MS_POP_DLG_MSG_NTF,               // MS->GS

    PROTO_MS_MSG_NTF,    
    PROTO_MS_ADD_SYS_NEW_MAIL,
    PROTO_MS_NEW_MAIL_NTF,
    PROTO_MS_SYNC_MAIL_INFO_STATUS,
    PROTO_MS_GET_MAIL_LIST_ACK,
    PROTO_MS_OPEN_MAIL_ACK,
    PROTO_MS_MAIL_DEL_REQ,
    PROTO_MS_DELETE_MAIL_ACK,
    PROTO_MS_MAIL_ATTACHMENT_GET_ACK,
    PROTO_MS_MISS_NTF,
    PROTO_MS_SYNC_ITEM_DYN_ATTRS,

    PROTO_MS_GET_TRADE_DELEGATE_REQ,      // MS -> CS
    PROTO_MS_DELEGATE_MINE_ACK,
    PROTO_MS_DELEGATE_SELL_LIST_ACK,
    PROTO_MS_DELEGATE_BUY_LIST_ACK,
    PROTO_MS_DELEGATE_CANCEL_REQ,   // MS -> CS
    PROTO_MS_DELEGATE_SELL_CMD,     // MS -> CS
    PROTO_MS_DELEGATE_BUY_CMD,      // MS -> CS
    PROTO_MS_MARKET_SELL_CMD,       // MS -> CS     
    PROTO_MS_MARKET_BUY_CMD,        // MS -> CS    

    PROTO_MS_GET_MAIL_ATTACHMENT_REQ,
    PROTO_MS_DELETE_SKILL_ACK,
    PROTO_MS_SKILL_STATUS_NTF,

    PROTO_MS_ROLE_DYN_ATTR_NTF,
    PROTO_MS_ROLE_CUST_VAR_NTF,

    PROTO_MS_AUCTION_ADD_ITEM_INFO,
    PROTO_MS_AUCTION_PPRICE_UPDATE,
    PROTO_MS_AUCTION_STATUS_UPDATE,
    PROTO_MS_AUCTION_GET_FINISH_INFO_REQ,
    PROTO_MS_AUCTION_HOUSE_REQ,
    PROTO_MS_SHABAK_OWNER_NTF,              // MS -> GS
    PROTO_MS_SHABAK_LOSS_NTF,               // MS -> GS
    PROTO_MS_SHABAK_ENGAGE_NTF,             // MS -> GS
    PROTO_MS_SHABAK_END_NTF,                // MS -> GS

    PROTO_MS_FAMILY_WAR_NTF,
    PROTO_MS_GET_CONSTANT_CFG_REQ,          // MS -> CS
    PROTO_MS_SET_SERVER_STATUS, 
    PROTO_MS_MALL_LIMIT_INFO_UPDATE,
    PROTO_MS_MALL_LIMIT_INFO_REQ,

    PROTO_MS_DELETE_MALL_REMAINED_DATA, 
    PROTO_MS_ADD_LOGIN_IP_TYPE,
    PROTO_MS_DEL_LOGIN_IP_TYPE,
    PROTO_MS_ADD_LOCK_PLAYER,
    PROTO_MS_DEL_LOCK_PLAYER,
    PROTO_MS_ADD_LOCK_ROLE,
    PROTO_MS_DEL_LOCK_ROLE,
    PROTO_MS_GET_PROHIBIT_CHAT_INFO_REQ,
    PROTO_MS_DEL_PROHIBIT_INFO,
    PROTO_MS_ADD_PROHIBIT_CHAT_INTO,
    PROTO_MS_SKILL_CD_CHANGED_NTF,
    PROTO_MS_SKILL_PROP_PERMANENT_CHANGED_NTF,
    PROTO_MS_GET_WANTED_LIST_REQ,
    PROTO_MS_GET_WANTED_LIST_ACK,
    PROTO_MS_POST_BOUNTY_REQ,
    PROTO_MS_POST_BOUNTY_ACK,
    PROTO_MS_CHECK_ROLE_EXISTENCE_REQ,
    PROTO_MS_CHECK_ROLE_EXISTENCE_ACK,
    PROTO_MS_ROLE_INFO_CHANGE_NTF,
    PROTO_MS_SKILL_PROFICIENCY_NTF,
    PROTO_MS_ITEM_PICKUP_NTF,
    PROTO_MS_AUTO_PICKUP_SETTINGS_NTF,
    PROTO_MS_MONSTER_PURSURE_ATTACKING_NTF,
    PROTO_MS_START_DIG_ACK,
    PROTO_MS_STOP_DIG_NTF,
    PROTO_MS_ROLE_APPEAR_NTF,
    PROTO_MS_SAVE_GOODS_ISSUE_RECORD,
    PROTO_MS_VERIFY_BUY_ITEM_INFO_ACK,
    PROTO_MS_GOODS_ISSUED_NTF,
    PROTO_MS_PLAYER_SET_NAME_REQ,
    PROTO_MS_ITEM_TIP,
    PROTO_MS_MONITOR_CHAT_MSG,
    PROTO_MS_ADD_TITLE,
    PROTO_MS_DEL_TITLE,
    PROTO_MS_TITLE_WEAR_TYPE,
    PROTO_MS_SYNC_TITLE_INFO,

    PROTO_MS_MONSTER_BACK_NTF,
    PROTO_MS_SET_AUTO_MODE_REQ,
    PROTO_MS_PLAYER_ACTIVATION_CODE,
    PROTO_MS_GET_TRADE_RECORDS_REQ,      // MS -> CS
    PROTO_MS_RECORDS_MINE_ACK,
    PROTO_MS_RECORDS_CANCEL_REQ,
    PROTO_MS_GM_ERROR_ACK,
    PROTO_MS_SCENE_ITEM_UPDATE_NTF,
    PROTO_MS_MOVE_NTF_EX,
    PROTO_MS_TURN_NTF,
    PROTO_MS_ADD_PLAYER_PROHIBIT_CHAT,
    PROTO_MS_DEL_PLAYER_PROHIBIT_CHAT,
    PROTO_MS_RUNGMCMD,
    PROTO_MS_REBATE_MONDY_USED_NTF,
    PROTO_MS_CUSTOM_HTTP,

    PROTO_MS_UPDATE_SUPPORT_PLAYER,
    PROTO_MS_DEL_ROLE_ACK,
    PROTO_MS_SYNC_CUST_LIST,
    PROTO_MS_GET_CUST_LIST_REQ,
    PROTO_MS_SEND_GOODS_POST_RECORD_TO_CLIENT,
    PROTO_MS_SYNC_GOODS_POST_RECORD,

    PROTO_MS_UPDATE_CONSTANT_CFG_REQ,
    PROTO_MS_SET_PLAYER_GENDER,
    PROTO_MS_EFFECT_APPEAR_NTF,
    PROTO_MS_EFFECT_DISAPPEAR_NTF,
    PROTO_MS_MAX
};

struct ProtoMS_EffectAppearNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_EFFECT_APPEAR_NTF);
    uint16_t num = 0;
    EffectPoint info[100];
    uint16_t type      = 0;
    uint32_t sessionid = 0;
    void Clear() {
        memset(this, 0, sizeof(ProtoMS_EffectAppearNtf));
        REDEF_PROTO_HEADER_MS(PROTO_MS_EFFECT_APPEAR_NTF);
    }
};

struct ProtoMS_EffectDisAppearNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_EFFECT_DISAPPEAR_NTF);
    uint16_t num = 0;
    EffectPoint info[100];
    uint16_t type      = 0;
    uint32_t sessionid = 0;
    void Clear() {
        memset(this, 0, sizeof(ProtoMS_EffectDisAppearNtf));
        REDEF_PROTO_HEADER_MS(PROTO_MS_EFFECT_DISAPPEAR_NTF);
    }
};

struct ProtoMS_SetPlayerGender
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SET_PLAYER_GENDER);
    uint64_t userID  = 0;
    uint64_t guid    = 0;
    uint8_t  gender  = 0;
};

struct ProtoMS_SendGoodsPostRecordToClient
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SEND_GOODS_POST_RECORD_TO_CLIENT);
    uint32_t sessionID = 0;
    GOODS_ISSUE_RECORD record;
};

struct ProtoMS_GetCustListReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_GET_CUST_LIST_REQ);
};

struct ProtoMS_SyncCustList
{
    enum OptType {
        optType_add = 0,
        optType_update = 1
    };
    DEF_PROTO_HEADER_MS(PROTO_MS_SYNC_CUST_LIST);
    uint8_t  optType = 0;
    int      type    = 0;
    uint16_t num     = 0;
    CUST_LIST_INFO data[100];
    ProtoMS_SyncCustList(uint8_t _optType):optType(_optType) {
        memset(data, 0, sizeof(data));
    }
    ProtoMS_SyncCustList(){
        memset(data, 0, sizeof(data));
    }
    void Clear() {
        memset(this, 0, sizeof(ProtoMS_SyncCustList));
        REDEF_PROTO_HEADER_MS(PROTO_MS_SYNC_CUST_LIST);
    }
};

struct ProtoMS_AddPlayerProhibitChat
{
    DEF_PROTO_HEADER_MS(PROTO_MS_ADD_PLAYER_PROHIBIT_CHAT);
    uint64_t userID = 0;
    int64_t stamp = 0;
    ProtoMS_AddPlayerProhibitChat() = default;
};

struct ProtoMS_DelPlayerProhibitChat
{
    DEF_PROTO_HEADER_MS(PROTO_MS_DEL_PLAYER_PROHIBIT_CHAT);
    uint64_t userID = 0;
    ProtoMS_DelPlayerProhibitChat() = default;
};

struct ProtoMS_PlayerActivationCode
{
    DEF_PROTO_HEADER_MS(PROTO_MS_PLAYER_ACTIVATION_CODE);
    RedemptionCodeInfo info;
    ProtoMS_PlayerActivationCode() = default;
};


struct ProtoMS_MonsterBackNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_MONSTER_BACK_NTF);
    uint64_t guid = 0;
    uint16_t status = 0;                   // 0 受击状态结束 1 受击状态开始
    uint32_t sessionid = 0;
    ProtoMS_MonsterBackNtf() = default;
};
struct ProtoMS_AddTitle
{
    DEF_PROTO_HEADER_MS(PROTO_MS_ADD_TITLE);
    uint64_t   guid = 0;
    TITLE_INFO info;
    ProtoMS_AddTitle() = default;
};

struct ProtoMS_DelTitle
{
    DEF_PROTO_HEADER_MS(PROTO_MS_DEL_TITLE);
    uint64_t guid = 0;
    uint16_t num = 0;
    uint32_t id[100] = {0};
    ProtoMS_DelTitle() = default;
};

struct ProtoMS_TitleWearType
{
    DEF_PROTO_HEADER_MS(PROTO_MS_TITLE_WEAR_TYPE);
    uint64_t guid = 0;
    uint32_t id = 0;
    uint16_t wearType = 0;
    ProtoMS_TitleWearType() = default;
};

struct ProtoMS_SyncTitleInfo
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SYNC_TITLE_INFO);
    uint64_t   guid = 0;
    uint16_t   num = 0;
    TITLE_INFO info[100];
    ProtoMS_SyncTitleInfo() {
        memset(info, 0, sizeof(info));
    };
};

struct ProtoMS_PlayerSetNameReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_PLAYER_SET_NAME_REQ);
    uint64_t guid = 0;
    char     name[32];
    ProtoMS_PlayerSetNameReq()
    {
        memset(name, 0, _countof(name));
    }
};

struct ProtoMS_MonsterPursureAttackingNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_MONSTER_PURSURE_ATTACKING_NTF);
    uint64_t guid = 0;
    uint16_t status = 0;                   // 0 追击状态结束 1 追击状态开始
    uint32_t sessionid = 0;
    ProtoMS_MonsterPursureAttackingNtf() = default;
};

struct ProtoMS_DeleteMallRemainedData
{
    DEF_PROTO_HEADER_MS(PROTO_MS_DELETE_MALL_REMAINED_DATA);
    ProtoMS_DeleteMallRemainedData() = default;
};
struct ProtoMS_AddProhibitChatInfo
{
    DEF_PROTO_HEADER_MS(PROTO_MS_ADD_PROHIBIT_CHAT_INTO);
    uint8_t num = 0;
    PROHIBIT_CHAT_DATA infos[100];
    ProtoMS_AddProhibitChatInfo()
    {
        memset(infos, 0, sizeof(infos));
    }
};

struct ProtoMS_DelProhibitInfo
{
    DEF_PROTO_HEADER_MS(PROTO_MS_DEL_PROHIBIT_INFO);
    uint8_t num = 0;
    PROHIBIT_CHAT_DATA infos[100];
    ProtoMS_DelProhibitInfo()
    {
        memset(infos, 0, sizeof(infos));
    }
};

struct ProtoMS_GetProhibitChatInfoReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_GET_PROHIBIT_CHAT_INFO_REQ);
    ProtoMS_GetProhibitChatInfoReq() = default;
};

struct ProtoMS_AddLockRole
{
    DEF_PROTO_HEADER_MS(PROTO_MS_ADD_LOCK_ROLE);
    uint8_t num = 0;
    uint64_t guid[100] = {0};
};

struct ProtoMS_DelLockRole
{
    DEF_PROTO_HEADER_MS(PROTO_MS_DEL_LOCK_ROLE);
    uint8_t num = 0;
    char name[100][32];
    ProtoMS_DelLockRole()
    {
        memset(name, 0, sizeof(name));
    };
};

struct ProtoMS_DelLockPlayer
{
    DEF_PROTO_HEADER_MS(PROTO_MS_DEL_LOCK_PLAYER);
    uint8_t num = 0;
    char name[100][32];
    ProtoMS_DelLockPlayer()
    {
        memset(name, 0, sizeof(name));
    };
};

struct ProtoMS_AddLockPlayer
{
    DEF_PROTO_HEADER_MS(PROTO_MS_ADD_LOCK_PLAYER);
    uint8_t num = 0;
    char name[100][32];
    ProtoMS_AddLockPlayer()
    {
        memset(name, 0, sizeof(name));
    };
};

struct ProtoMS_UpdateSupportPlayer
{
    DEF_PROTO_HEADER_MS(PROTO_MS_UPDATE_SUPPORT_PLAYER);
    uint8_t num = 0;
    uint8_t type = 0;
    char name[100][32];
    uint64_t guid[100] = { 0 };
    ProtoMS_UpdateSupportPlayer()
    {
        memset(name, 0, sizeof(name));
        memset(guid, 0, sizeof(guid));
    };
};

struct ProtoMS_Del_Role_By_GM
{
    DEF_PROTO_HEADER_MS(PROTO_MS_DEL_ROLE_ACK);
    uint64_t pid;
    uint64_t guid;
};



struct ProtoMS_AddLoginIpType
{
    DEF_PROTO_HEADER_MS(PROTO_MS_ADD_LOGIN_IP_TYPE);
    uint8_t num = 0;
    uint8_t ip_type = 0;
    uint32_t ip[100];
    ProtoMS_AddLoginIpType()
    {
        memset(ip, 0, _countof(ip));
    }
};

struct ProtoMS_DelLoginIpType
{
    DEF_PROTO_HEADER_MS(PROTO_MS_DEL_LOGIN_IP_TYPE);
    uint8_t num = 0;
    uint8_t ip_type = 0;
    uint32_t ip[100];
    ProtoMS_DelLoginIpType()
    {
        memset(ip, 0, _countof(ip));
    }
};
struct ProtoMS_MallLimitInfoReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_MALL_LIMIT_INFO_REQ);
    ProtoMS_MallLimitInfoReq() = default;
};

struct ProtoMS_SetServerStatus
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SET_SERVER_STATUS);
    uint8_t status = 0;
    ProtoMS_SetServerStatus() = default;
};
struct ProtoMS_MallLimitInfoUpdate
{
    enum opt_type
    {
        opt_type_add = 1,
        opt_type_update = 2,
    };

    DEF_PROTO_HEADER_MS(PROTO_MS_MALL_LIMIT_INFO_UPDATE);
    uint16_t num = 0;
    uint8_t  limit_type = 0;
    uint8_t opt_type = 0;
    MALL_ITEM_INFO_BASE data[100];
    ProtoMS_MallLimitInfoUpdate()
    {
        memset(data, 0, sizeof(data));
    }
};
struct ProtoMS_GetAuctionHouseReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_AUCTION_HOUSE_REQ);
    ProtoMS_GetAuctionHouseReq() = default;
};

struct ProtoMS_AuctionGetFinishedInfoReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_AUCTION_GET_FINISH_INFO_REQ);
    uint32_t time = 0;
    char     func[32];
    ProtoMS_AuctionGetFinishedInfoReq()
    {
        memset(func, 0, sizeof(func));
    };
};

struct ProtoMS_SynAuctionItemInfo
{
    enum maxnum
    {
        max_num = 100,
    };
    enum opt_type {
        null   = 0,
        updata = 1,
        add    = 2,
    };
    DEF_PROTO_HEADER_MS(PROTO_MS_AUCTION_ADD_ITEM_INFO);
    uint16_t                type = 0;
    uint16_t                num = 0;
    AUCTION_HOUSE_ITEM_INFO info[100];
    ProtoMS_SynAuctionItemInfo() = default;
};

struct ProtoMS_UpdateTopListAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_UPDATE_TOPLIST_ACK);

    uint64_t            role = 0;
    TOPLIST_INFO        nowRole;
    ProtoMS_UpdateTopListAck() {
        memset(&nowRole, 0, sizeof(nowRole));
    }
};

struct ProtoMS_DeleteMailReq {
    DEF_PROTO_HEADER_MS(PROTO_MS_MAIL_DEL_REQ);
    uint64_t                  id = 0; //邮件的ID
    uint64_t                  playerguid = 0;
    uint32_t                  sessid = 0;
    ProtoMS_DeleteMailReq() = default;
};

struct ProtoMS_DeleteMailAck{
    DEF_PROTO_HEADER_MS(PROTO_MS_DELETE_MAIL_ACK);
    uint64_t                  mail_id; //邮件ID
    unsigned int              errcode;
    uint32_t       sessid;
    ProtoMS_DeleteMailAck() = default;
};

struct ProtoMS_OpenMailAck{
    DEF_PROTO_HEADER_MS(PROTO_MS_OPEN_MAIL_ACK);
    uint64_t                  mail_id; //邮件ID
    MAIL_BODY_INFO2            mail; //邮件
    uint32_t       sessid;
    void Clear()
    {
        memset(this, 0, sizeof(ProtoMS_OpenMailAck));
        REDEF_PROTO_HEADER_MS(PROTO_MS_OPEN_MAIL_ACK);
    }
    ProtoMS_OpenMailAck() = default;
};
static ProtoMS_OpenMailAck gProtoMS_OpenMailAck;

struct ProtoMS_GetMailListAck{
    DEF_PROTO_HEADER_MS(PROTO_MS_GET_MAIL_LIST_ACK);
    MAIL_HEADER_INFO          mails[100]; //邮件列表
    int                       num = 0; //当前返回的邮件数量
    uint16_t                  cur_page = 0;
    uint16_t                  page_num = 0;
    uint32_t                  sessid;
    ProtoMS_GetMailListAck() = default;
};

//struct ProtoMS_SyncMailInfo{
//    DEF_PROTO_HEADER_MS(PROTO_MS_SYNC_MAIL_INFO);
//    char           rolename[32];
//    uint16_t       num;
//    MAIL_INFO      infos[100];
//    ProtoMS_SyncMailInfo() = default;
//};

struct ProtoMS_SyncMailInfoStatus {
    DEF_PROTO_HEADER_MS(PROTO_MS_SYNC_MAIL_INFO_STATUS);
    uint64_t playerguid = 0;
    uint16_t         num = 0;
    Mail_Info_Status info_status[100];
    ProtoMS_SyncMailInfoStatus() = default;
};

struct ProtoMS_NewMailNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_NEW_MAIL_NTF);
    uint32_t         sessid;
    ProtoMS_NewMailNtf() = default;
};

struct ProtoMS_AddSysNewMail{
    DEF_PROTO_HEADER_MS(PROTO_MS_ADD_SYS_NEW_MAIL);
    enum add_type {
        add_type_non      = 0,
        add_type_by_name  = 1,    //通过名字加
        add_type_by_guid  = 2,    //通过guid加
    };
    char           rolename[32];
    uint64_t       guid[1000] = {0};
    uint32_t       num = 0;
    MAIL_INFO      infos;
    uint16_t       addType = 0;
    ProtoMS_AddSysNewMail() = default;
    void Clear() {
        memset(this, 0, sizeof(ProtoMS_AddSysNewMail));
        REDEF_PROTO_HEADER_MS(PROTO_MS_ADD_SYS_NEW_MAIL);
    };
};
static ProtoMS_AddSysNewMail gProtoMS_AddSysNewMail;

struct ProtoMS_MailAttachmentGetAck{
    DEF_PROTO_HEADER_MS(PROTO_MS_MAIL_ATTACHMENT_GET_ACK);
    uint64_t                  mail_id; //邮件ID
    unsigned char             index; //附件序列：1是金币，2是元宝, 3-7为物品，8为积分
    unsigned int              errcode; //错误码
    uint32_t       sessid;
    ProtoMS_MailAttachmentGetAck() = default;
};

struct ProtoMS_GetMailAttachmentReq 
{
    DEF_PROTO_HEADER_MS(PROTO_MS_GET_MAIL_ATTACHMENT_REQ);
    uint64_t            role_guid;
    uint64_t            mail_guid;
    uint64_t            item_guid;
    uint8_t             index;
    ProtoMS_GetMailAttachmentReq() = default;
};

struct ProtoMS_RecordsMineAck
{
    enum RMA_MaxSize
    {
        Info_Size = 10
    };
    DEF_PROTO_HEADER_MS(PROTO_MS_RECORDS_MINE_ACK);
    uint64_t                    role_id = 0;
    uint16_t                    type = 0;
    uint32_t                    count = 0;
    TRADE_RECORD                trade_record[Info_Size];
    uint8_t                     last_pack = 0;
    uint32_t                    sessid = 0;
    void Clear()
    {
        memset(this, 0, sizeof(ProtoMS_RecordsMineAck));
        REDEF_PROTO_HEADER_MS(PROTO_MS_RECORDS_MINE_ACK);
    }
    ProtoMS_RecordsMineAck() = default;
};

struct ProtoMS_DelegateMineAck
{
    enum DMA_MaxSize
    {
        Info_Size = 5
    };
    DEF_PROTO_HEADER_MS(PROTO_MS_DELEGATE_MINE_ACK);
    uint64_t                    role_id = 0;
    uint32_t                    count_buy = 0;  //买入数量
    uint32_t                    count_sell = 0; //卖出数量
    DELEGATE_BUY_ITEM2          buy_items[Info_Size];
    DELEGATE_SELL_ITEM          sell_items[Info_Size];
    uint8_t                     last_pack = 0;
    uint32_t                    sessid = 0;
    void Clear()
    {
        memset(this, 0, sizeof(ProtoMS_DelegateMineAck));
        REDEF_PROTO_HEADER_MS(PROTO_MS_DELEGATE_MINE_ACK);
    }
    ProtoMS_DelegateMineAck() = default;
};

struct ProtoMS_DelegateSellListAck
{
    enum DSLA_MaxSize
    {
        Info_Size = 20
    };
    DEF_PROTO_HEADER_MS(PROTO_MS_DELEGATE_SELL_LIST_ACK);
    uint16_t                type = 0;       //分类
    uint16_t                subtype = 0;    //子分类
    uint32_t                total = 0;      //总数(意义变更为总包cnt)
    uint32_t                start = 0;      //起始序列号(意义变更为当前包idx)
    uint32_t                count = 0;      //申请数量
    DELEGATE_SELL_ITEM      items[Info_Size];      //物品列表
    uint32_t                sessid = 0;
    void Clear()
    {
        memset(this, 0, sizeof(ProtoMS_DelegateSellListAck));
        REDEF_PROTO_HEADER_MS(PROTO_MS_DELEGATE_SELL_LIST_ACK);
    }
    ProtoMS_DelegateSellListAck() = default;
};

struct ProtoMS_DelegateBuyListAck
{
    enum DBLA_MaxSize
    {
        Info_Size = 20
    };
    DEF_PROTO_HEADER_MS(PROTO_MS_DELEGATE_BUY_LIST_ACK);
    uint16_t                type = 0;       //分类
    uint16_t                subtype = 0;    //子分类
    uint32_t                total = 0;      //总数
    uint32_t                start = 0;      //起始序列号
    uint32_t                count = 0;      //申请数量
    DELEGATE_BUY_ITEM2      items[Info_Size];      //物品列表
    uint32_t                sessid = 0;
    ProtoMS_DelegateBuyListAck() = default;
};

struct ProtoMS_DgnBindInfo 
{
    enum DBI_MaxSize
    {
        Info_Size = 50
    };
    DEF_PROTO_HEADER_MS(PROTO_MS_DGN_BIND_INFO);

    DGN_BIND_INFO       info[Info_Size];
    uint16_t            packIdx;
    uint16_t            num;
    uint64_t	        roleId = 0;
    uint64_t            userid = 0;
    ProtoMS_DgnBindInfo() = default;
};


struct ProtoMS_GlobalNtf{
    DEF_PROTO_HEADER_MS(PROTO_MS_GLOBAL_NTF);
    uint32_t       sessid;
    unsigned short int_count = 0;      //整形数据个数
    IntData        int_data[256];  //数据值
    unsigned short str_count = 0;      //字符型数据个数
    StrData        str_data[256];
    ProtoMS_GlobalNtf() = default;
};

struct ProtoMS_QuickBarSet {
    DEF_PROTO_HEADER_MS(PROTO_MS_QUICK_BAR_SET);

    QUICK_BAR_INFO            info[30];
    unsigned short            num;
    uint64_t			      role_id = 0;
    uint64_t                  userid =0;
    ProtoMS_QuickBarSet() = default;
};

struct ProtoMS_QuickBarSetNtf {
    DEF_PROTO_HEADER_MS(PROTO_MS_QUICK_BAR_SET_NTF);

    unsigned short            num;//快捷栏数量
    QUICK_BAR_INFO            info[30];//快捷栏信息
    uint32_t                  sessid;
    ProtoMS_QuickBarSetNtf() = default;
};

struct ProtoMS_TeamLeaderNtf {
    DEF_PROTO_HEADER_MS(PROTO_MS_TEAM_LEADER_NTF);

    uint64_t                  leader_guid; //新队长guid
    uint32_t                  session_id;
    ProtoMS_TeamLeaderNtf() {}
};

struct ProtoMS_TeamJoinNtf {
    DEF_PROTO_HEADER_MS(PROTO_MS_TEAM_JOIN_NTF);

    char                      joiner[256] = {}; //申请加入者name
    uint32_t                  session_id;
    ProtoMS_TeamJoinNtf() {}
};

struct ProtoMS_GetAroundTeamAck {
    DEF_PROTO_HEADER_MS(PROTO_MS_GET_ARROUND_TEAM_ACK);

    unsigned char             list_size; //列表大小
    TEAM_MEMBER               list_data[20]; //列表内容
    uint32_t                  session_id;
    ProtoMS_GetAroundTeamAck() = default;
};

struct ProtoMS_TeamInviteNtf {
    DEF_PROTO_HEADER_MS(PROTO_MS_TEAM_INVITE_NTF);

    char                      inviter_name[256] = {}; //邀请者name
    unsigned char             exist; //是否有队伍
    unsigned short            num; //数量
    TEAM_INFO                 info[1] = {}; //队伍信息
    uint32_t                  session_id;
    ProtoMS_TeamInviteNtf() {}
};

struct ProtoMS_TeamLeaveNtf {
    DEF_PROTO_HEADER_MS(PROTO_MS_MISS_TEAM_NTF);

    uint64_t                  player_guid; //player guid
    unsigned char             type; //1=被踢 2=主动离开
    uint32_t                  session_id;
    ProtoMS_TeamLeaveNtf() {}
};

struct ProtoMS_TeamNtf {
    DEF_PROTO_HEADER_MS(PROTO_MS_TEAM_NTF);

    TEAM_INFO                 info; //队伍信息
    uint32_t                  session_id;
    uint32_t                  gatesession_id;
    ProtoMS_TeamNtf()
    {
        memset(&info, 0, sizeof(info));
    }
};

struct ProtoMS_ClearRoleInfoNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_CLEAR_ROLE_INFO_NTF);

    uint64_t			      role_id = 0;
    uint32_t			      token = 0;
};

struct ProtoMS_DeleteRoleInfoNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_DELETE_ROLE_INFO_NTF);

    uint64_t			 role_id = 0;
    uint32_t			 token = 0;
    char				 base_info[512];
};

struct ProtoMS_UpdateRoleInfoNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_UPDATE_ROLE_INFO_NTF);

    uint64_t			 role_id = 0;
    uint32_t			 token = 0;
    char				 base_info[512];
};

struct ProtoMS_InsertRoleInfoNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_INSERT_ROLE_INFO_NTF);

    uint64_t			 role_id = 0;
    uint32_t			 token = 0;
    char				 base_info[512];
};

struct ProtoMS_GetRoleInfoReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_GET_ROLE_INFO_REQ);

    uint64_t    role_id = 0;
    uint32_t    token = 0;
};

struct ProtoMS_GetRoleInfoAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_GET_ROLE_INFO_ACK);

    uint64_t                  role_id = 0;
    uint32_t                  token = 0;
    char                      base_info[512]; //信息
};

struct ProtoMS_SendDelItemNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SEND_DEL_ITEM_NTF);

    uint64_t                  user_guid         = 0;
    uint64_t                  role_guid         = 0;
    uint64_t                  item_guid         = 0;
    uint8_t                   tradeDel          = 0;
};

struct ProtoMS_SendSyncItemNtf {
    DEF_PROTO_HEADER_MS(PROTO_MS_SEND_SYNC_ITEM_NTF);

    uint32_t                  token = 0;
    uint64_t                  role_guid =0; //role guid
    uint64_t                  Guid = 0;
    char                      Name[32] = {};
    unsigned short            Tempid = 0;//id
    uint64_t                  Roleid = 0;
    unsigned short            Site = 0;
    unsigned short            Amount = 0;
    int                       Durability = 0;
    int                       Max_durability = 0;
    unsigned short            Use_count = 0;
    unsigned char             IsBind = 0;
    unsigned int              Life = 0;
    ITEM_CFG_VAR              ItemCfgVar;           //自定义配置表字段
    ProtoMS_SendSyncItemNtf() = default;
};
static ProtoMS_SendSyncItemNtf gProtoMS_SendSyncItemNtf;

struct ProtoMS_ItemAttrNtf {
    DEF_PROTO_HEADER_MS(PROTO_MS_ITEM_ATTR_NTF);

    uint64_t                  item_guid; //物品GUID
    unsigned int              attr_name; //物品属性名称
    int                       attr_value; //物品属性值
    uint32_t sessid;
    ProtoMS_ItemAttrNtf() = default;
};
static ProtoMS_ItemAttrNtf gProtoMS_ItemAttrNtf;

struct ProtoMS_ItemPickUp {
    DEF_PROTO_HEADER_MS(PROTO_MS_ITEM_PICK_UP);
};

struct ProtoMS_ItemAppearNtf4
{
    DEF_PROTO_HEADER_MS(PROTO_MS_ITEM_APPEAR_NTF4);

    uint64_t                    item_guid           = 0;            // item guid
    uint16_t                    template_id         = 0;            // 模板id
    int32_t                     dst_x               = 0;            // 目标点x
    int32_t                     dst_y               = 0;            // 目标点y
    uint16_t                    skill_id            = 0;            // 技能id
    char                        item_name[64]       = {0};          // 物品名称
    int16_t                     seed                = 0;            // 校验种子
    uint8_t                     is_drop             = 0;            // 是否是掉落出现
    uint64_t                    owner_guid          = 0;            // 拥有者guid
    uint64_t                    team_guid           = 0;            // 拥有者队伍guid
    uint32_t                    clsessid            = 0;
};
static ProtoMS_ItemAppearNtf4 gProtoMS_ItemAppearNtf4;

struct ProtoMS_ItemDestroyAck {
    DEF_PROTO_HEADER_MS(PROTO_MS_ITEM_DESTROY_ACK);

    uint64_t                  item_guid; //物品GUID
    uint32_t  sessid;
    ProtoMS_ItemDestroyAck() = default;
};


struct ProtoMS_ItemUpdateNtf {
    DEF_PROTO_HEADER_MS(PROTO_MS_ITEM_UPDATE_NTF);

    ITEM_INFO                 info;
    uint32_t  sessid;
    ProtoMS_ItemUpdateNtf() = default;
};
static ProtoMS_ItemUpdateNtf gProtoMS_ItemUpdateNtf;

struct ProtoMS_RoleAttrNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_ROLE_ATTR_NTF);

    uint64_t                    role_guid           = 0;
    uint16_t                    attr_num            = 0;        // 数量
    uint16_t                    attr_name[100]      = {0};      // 属性名称
    int                         attr_value[100]     = {0};      // 属性值
    uint16_t                    clsessnum           = 0;
    uint32_t                    clsessids[300]      = {0};
};

struct ProtoMS_ItemAddAck {
    DEF_PROTO_HEADER_MS(PROTO_MS_ITEM_ACK);

    char                      isPackItem;
    ITEM_INFO                 info;
    uint32_t                  sessid;
    uint32_t                  nGS2CSSessionID;
    ProtoMS_ItemAddAck() = default;
};
static ProtoMS_ItemAddAck gProtoMS_ItemAddAck;

struct ProtoMS_ObjDisappearNtf {
    DEF_PROTO_HEADER_MS(PROTO_MS_DISAPPEAR_NTF);

    uint64_t                  obj_guid; //obj guid
    uint32_t                  sessid;
    ProtoMS_ObjDisappearNtf() = default;
};
static ProtoMS_ObjDisappearNtf gProtoMS_ObjDisappearNtf;

struct ProtoMS_MonsterAppearNtf6
{
    DEF_PROTO_HEADER_MS(PROTO_MS_MONSTER_APPEAR_NTF6);

    uint64_t                  monster_guid; //monster guid
    char                      monster_name[50];
    unsigned short            template_id; //模板id
    int                       dst_x; //目标点x
    int                       dst_y; //目标点y
    unsigned char             dir; //方向
    unsigned int              cur_hp; //当前血量
    unsigned int              max_hp; //最大血量
    unsigned char             status; //怪物状态 0=活着 1=死亡 2=被挖过
    unsigned char             servant_lv; //随从等级
    unsigned short            move_speed; //移动速度
    unsigned short            buff_num; //Buff数量
    BUFF_INFO                 buffs[50]; //Buff信息
    char                      master_name[32]; //主人的名字
    unsigned char             appear_type; //出现类型 0=进入视野 1=出生 2=跳跃
    short                     seed; //校验种子
    unsigned short            attack_speed; //攻击速度
    CUSTOM_INFO               custom; //自定义数据
    unsigned int              inner_force; //当前内功
    unsigned int              max_inner_force; //最大内功
    unsigned int              modelid;
    unsigned short            reserve_num; //保留字段数量
    unsigned int              reserve_values[10]; //保留字段
    char                      name_color[10]; // 名字颜色
    uint32_t                  sessid;
    uint32_t                  nGS2CSSessionID;
    ProtoMS_MonsterAppearNtf6() = default;
};
static ProtoMS_MonsterAppearNtf6 gProtoMS_MonsterAppearNtf6;

struct ProtoMS_HeartBeatReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_HEART_BEAT_REQ);
};

struct ProtoMS_HeartBeatAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_HEART_BEAT_ACK);
};

struct ProtoMS_MoveNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_MOVE_NTF);

    uint64_t           guid;  // player/monster/npc's guid
    unsigned char   type;       //移动类型 0=走 1=跑 2=跳
    unsigned short dst_x;     //目标点x
    unsigned short dst_y;     //目标点y
    uint32_t                 sessionid;    //CLI <--->GS

    ProtoMS_MoveNtf() : guid(0), type(0), dst_x(0), dst_y(0)
    {
    }
};
static ProtoMS_MoveNtf gProtoMS_MoveNtf;

struct ProtoMS_MoveNtfEx
{
    DEF_PROTO_HEADER_MS(PROTO_MS_MOVE_NTF_EX);

    uint64_t                guid                = 0;            // player/monster/npc's guid
    uint8_t                 type                = 0;            // 移动类型 0=走 1=跑 2=跳
    uint16_t                dst_x               = 0;            // 目标点x
    uint16_t                dst_y               = 0;            // 目标点y
    uint16_t                clsessnum           = 0;
    uint32_t                clsessids[300]      = {0};          // CLI <--->GS
};

struct ProtoMS_TurnNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_TURN_NTF);

    uint64_t                guid                = 0;
    uint8_t                 dir                 = 0;
    uint16_t                clsessnum           = 0;
    uint32_t                clsessids[300]      = {0};
};

struct ProtoMS_EnterMSAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_ENTER_MS_ACK);

    uint32_t                nClientSessionID    = 0;
    uint32_t                nCS2GSSessionID     = 0;

    uint8_t                 entertype           = 0xFF;   //进入类型 0=上线 1=跳服
    uint64_t                playerid            = 0;
    uint64_t                roleguid            = 0;    //角色guid
    uint32_t                gsobjid             = 0;    //客户端在GS上的objid
    int32_t                 errcode             = -1;   //错误码
    char                    errmsg[256];                //错误描述
    ROLE_BRIEF_INFO             roleBriefInfo;
    ProtoMS_EnterMSAck()
    {
        memset(errmsg, 0, sizeof(errmsg));
        memset(&roleBriefInfo, 0, sizeof(roleBriefInfo));
    }
};

struct ProtoMS_EnterMSNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_ENTER_MS_NTF);

    uint32_t                nClientSessionID    = 0;
    uint32_t                nCS2GSSessionID = 0;

    uint64_t                mapcode             = 0;    //地图流水号
    char                    logic[256];                 //地图逻辑格文件
    uint16_t                view_x              = 0;    //地图视野范围X
    uint16_t                view_y              = 0;    //地图视野范围Y
    uint16_t                width               = 0;    //宽
    uint16_t                height              = 0;    //高
    uint32_t                token;

    ProtoMS_EnterMSNtf()
    {
        memset(logic, 0, sizeof(logic));
    }
};

struct ProtoMS_UploadConfigReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_UPLOAD_CONFIG_REQ);

    uint32_t    ip;
    uint32_t    port;

    ProtoMS_UploadConfigReq() : ip(0), port(0)
    {}
};

struct ProtoMS_ConfigReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_CONFIG_REQ);
};

struct ProtoMS_ConfigAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_CONFIG_ACK);

    uint32_t    dbServIp;
    uint32_t    dbServPort;
    uint32_t    centerServIp;
    uint32_t    centerServPort;
    uint32_t    logServIp;
    uint32_t    logServPort;

    ProtoMS_ConfigAck() : dbServIp(0), dbServPort(0), centerServIp(0), centerServPort(0), logServIp(0), logServPort(0)
    {}
};

struct ProtoMS_RoleAttrExtNtf {
    DEF_PROTO_HEADER_MS(PROTO_MS_ROLE_ATTR_EXT_NTF);

    uint64_t                  player_guid; //player guid
    unsigned short            num; //数量
    unsigned short            attr_name[20]; //属性名称
    int64_t                   attr_value[20]; //属性值
    uint32_t sessid;
    ProtoMS_RoleAttrExtNtf() = default;
};

struct ProtoMS_RoleCustVarNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_ROLE_CUST_VAR_NTF);

    uint64_t                    role_guid = 0;
    CUSTOM_INFO                 custom;
    uint32_t                    sessid = 0;
    uint8_t                     type = 0;        //0=全部 1=部分
    void Clear()
    {
        memset(this, 0, sizeof(ProtoMS_RoleCustVarNtf));
        REDEF_PROTO_HEADER_MS(PROTO_MS_ROLE_CUST_VAR_NTF);
    }
};

struct ProtoMS_RoleDynAttrsNtf 
{
    DEF_PROTO_HEADER_MS(PROTO_MS_ROLE_DYN_ATTR_NTF);

    uint64_t                  role_guid = 0;
    CUSTOM_INFO                 custom;
    uint32_t                  sessid = 0;
    void Clear()
    {
        memset(this, 0, sizeof(ProtoMS_RoleDynAttrsNtf));
        REDEF_PROTO_HEADER_MS(PROTO_MS_ROLE_DYN_ATTR_NTF);
    }
};

struct ProtoMS_RoleInfoChangeNtf {
    DEF_PROTO_HEADER_MS(PROTO_MS_ROLE_INFO_CHANGE_NTF);

    uint64_t                    role_guid = 0;
    uint16_t                    num = 0;
    CUSTOM_INFO                 custom;
    uint32_t                    sessid = 0;
    void Clear()
    {
        memset(this, 0, sizeof(ProtoMS_RoleInfoChangeNtf));
        REDEF_PROTO_HEADER_MS(PROTO_MS_ROLE_INFO_CHANGE_NTF);
    }
    ProtoMS_RoleInfoChangeNtf() = default;
};
static ProtoMS_RoleInfoChangeNtf gProtoMS_RoleInfoChangeNtf;

struct ProtoMS_PlayerAppearNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_PLAYER_APPEAR_NTF);

    uint64_t                    player_guid         = 0;            // player guid
    char                        name[128]           = {0};          // 名称
    uint8_t                     gender              = 0;            // 性别
    uint8_t                     job                 = 0;            // 职业
    uint8_t                     status              = 0;            // 人物状态 0=活着 1=死亡
    uint16_t                    head                = 0;            // 头像
    uint32_t                    level               = 0;            // 等级
    uint16_t                    dst_x               = 0;            // 目标点x
    uint16_t                    dst_y               = 0;            // 目标点y
    uint8_t                     dir                 = 0;            // 方向
    uint16_t                    hair                = 0;            // 头发
    uint16_t                    hair_color          = 0;            // 头发颜色
    uint16_t                    body                = 0;            // 身体
    uint16_t                    weapon              = 0;            // 武器
    uint16_t                    wings               = 0;            // 翅膀
    uint16_t                    mount               = 0;            // 坐骑
    uint16_t                    weapon_effect       = 0;            // 武器特效
    uint16_t                    body_effect         = 0;            // 身体特效
    uint16_t                    mount_effect        = 0;            // 坐骑特效
    uint32_t                    hp                  = 0;            // 当前血量
    uint32_t                    max_hp              = 0;            // 最大血量
    uint32_t                    mp                  = 0;            // 当前mp
    uint32_t                    max_mp              = 0;            // 最大mp
    int                         pk                  = 0;            // pk
    uint16_t                    move_speed          = 0;            // 移动速度
    uint16_t                    attack_speed        = 0;            // 攻击速度
    uint16_t                    casting_speed       = 0;            // 施法速度
    uint16_t                    show_fashion        = 0;            // 显示时装
    uint32_t                    model_id            = 0;            // 显示更改后的外观
    uint16_t                    title               = 0;            // 称号
    uint8_t                     has_team            = 0;            // 是否有队伍
    uint8_t                     stall               = 0;            // 0: 未摆摊 1: 摆摊准备 2: 摆摊中
    char                        stall_name[32]      = {0};          // 摆摊名称
    uint16_t                    buff_num            = 0;            // Buff数量
    BUFF_INFO                   buffs[50];                          // Buff信息
    char                        family_name[32]     = {0};          // 行会名称
    char                        castle_name[256]    = {0};          // 城堡名称，可以多个用与符号分隔
    char                        family_title[32]    = {0};          // 行会称号
    char                        alias[64]           = {0};          // 别名
    CUSTOM_INFO                 custom;                             // 自定义数据
    uint8_t                     appear_type         = 0;            // 出现类型 0=进入视野 1=出生 2=跳跃
    uint16_t                    amulet              = 0;            // 法宝
    uint16_t                    equip_num           = 0;            // 扩展装备数量
    EQUIP_INFO                  equips[10];                         // 扩展装备信息
    uint32_t                    inner_force         = 0;            // 当前内功
    uint32_t                    max_inner_force     = 0;            // 最大内功
    uint16_t                    reserve_num         = 0;            // 保留字段数量
    uint32_t                    reserve_values[10]  = {0};          // 保留字段
    uint64_t                    master_guid         = 0;            // 主人guid
    uint16_t                    title_num           = 0;            // 称号数量
    uint32_t                    title_id[10]        = {0};          // 称号id
    uint32_t                    sessid              = 0;

    ProtoMS_PlayerAppearNtf()
    {
        memset(buffs, 0, sizeof(buffs));
        memset(&custom, 0, sizeof(custom));
        memset(equips, 0, sizeof(equips));
    }

    void Reset() { memset((uint8_t *)this + 4, 0, sizeof(*this) - 4); }
};

static ProtoMS_PlayerAppearNtf gProtoMS_PlayerAppearNtf;

struct ProtoMS_NpcTalkReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_NPC_TALK_REQ);
};

struct ProtoMS_NpcTalkAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_NPC_TALK_ACK);

    char        content[256] = {0};
};

struct ProtoMS_AttrShowNtfEx2
{
    DEF_PROTO_HEADER_MS(PROTO_MS_ATTR_SHOW_NTF2_EX2);

    uint64_t                  actor             = 0; //actor, 可能是player/monster/npc's guid
    unsigned short            skill_id          = 0; //skill id
    uint64_t                  target            = 0; //target, 可能是player/monster/npc's guid
    unsigned char             type              = 0; //0=普通 1=爆击
    int                       actor_hp_ref      = 0; //actor hp显示值
    int                       target_hp_ref     = 0; //目标hp显示值
    int                       target_hp         = 0; //目标hp绝对值
    int                       target_mp         = 0; //目标mp绝对值
    int                       actor_mp_ref      = 0; //actor mp显示值
    int                       target_mp_ref     = 0; //目标mp显示值
    unsigned char             reserve_size      = 0; //保留字段数量
    unsigned int              reserve[10]       = {0}; //保留字段
    uint16_t                  clsessnum         = 0;
    uint32_t                  clsessids[300]    = {0};
};

struct ProtoMS_SpellNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SPELL_NTF);

    uint64_t        actor               = 0;            // 施放者, 可能是player/monster/npc's guid
    uint16_t        id                  = 0;            // 技能id
    uint16_t        target_x            = 0;            // 目标逻辑格的X坐标
    uint16_t        target_y            = 0;            // 目标逻辑格的Y坐标
    uint16_t        num                 = 0;            // 有效目标数量
    uint64_t        targets[50]         = {0};          // 目标集, 可能是player/monster/npc's guid
    uint8_t         extra               = 0;            // 普攻时用来表示是否使用刺杀特效

    uint16_t        clsessnum           = 0;
    uint32_t        clsessids[300]      = {0};
};

struct ProtoMS_ErrorAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_ERROR_ACK);

    uint32_t        clientSessionID     = 0;

    int32_t         ecode               = -1;       // 错误码
    uint64_t        guid                = 0;        // role id
};

struct ProtoMS_GMErrorAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_GM_ERROR_ACK);

    uint32_t        clsessid            = 0;

    int32_t         sn                  = 0;
    int32_t         ecode               = -1;       // 错误码
    uint64_t        guid                = 0;        // role id
};

struct ProtoMS_ObjDieNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_OBJDIE_NTF);

    uint32_t        clientSessionID     = 0;

    uint64_t        die_guid            = 0;    //死亡的对象的guid 可能是player/monster/npc
    uint64_t        kill_guid           = 0;    //杀手的对象的guid 可能是player/monster/npc
    char            kill_name[32];              //杀手的名称

    ProtoMS_ObjDieNtf()
    {
        memset(kill_name, 0, sizeof(kill_name));
    }
};

struct ProtoMS_SkillAddAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SKILL_ADD_ACK);

    uint32_t        nClientSessionID    = 0;
    uint64_t        role_guid           = 0;

    uint16_t        num                 = 0;    // 技能数量
    SKILL_INFO      info[100];                  // 技能信息
    uint8_t         add = 0;            // 是否新增技能
    void Clear()
    {
        memset(this, 0, sizeof(ProtoMS_SkillAddAck));
        REDEF_PROTO_HEADER_MS(PROTO_MS_SKILL_ADD_ACK);
    }
    ProtoMS_SkillAddAck()
    {
        memset(info, 0, sizeof(info));
    }

};

struct ProtoMS_DeleteSkillAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_DELETE_SKILL_ACK);
    uint32_t                    nClientSessionID = 0;
    uint16_t                    skillid = 0;

    ProtoMS_DeleteSkillAck() {}
};

struct ProtoMS_GetSkillAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_GET_SKILL_ACK);

    uint64_t                    playerid    = 0;
    uint64_t                    roleid      = 0;
    uint16_t                    skillNum    = 0;
    SKILL_INFO                  skillInfo[100];

    ProtoMS_GetSkillAck()
    {
        memset(skillInfo, 0, sizeof(skillInfo));
    }
};

struct ProtoMS_SyncSkillReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SYNC_SKILL_REQ);

    uint64_t                    playerid    = 0;
    uint64_t                    roleid      = 0;
    uint16_t                    skillNum    = 0;
    SKILL_INFO                  skillInfo[100];
    void Clear()
    {
        memset(this, 0, sizeof(ProtoMS_SyncSkillReq));
        REDEF_PROTO_HEADER_MS(PROTO_MS_SYNC_SKILL_REQ);
    }
    ProtoMS_SyncSkillReq()
    {
        memset(skillInfo, 0, sizeof(skillInfo));
    }
};

struct ProtoMS_GetBuffAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_GET_BUFF_ACK);
    uint64_t                    playerid    = 0;
    uint64_t                    roleid      = 0;

    uint8_t                     beFirstPack = 0;
    uint16_t                    buffNum     = 0;
    BUFF_INFO_DB                buffs[50];

    ProtoMS_GetBuffAck()
    {
        memset(buffs, 0, sizeof(buffs));
    }
};

struct ProtoMS_SyncBuffReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SYNC_BUFF_REQ);

    uint64_t                    playerid    = 0;
    uint64_t                    roleid      = 0;
    uint8_t                     roleType    = 0;

    uint8_t                     beFirstPack = 0;
    uint16_t                    buffNum     = 0;
    BUFF_INFO_DB                buffs[50];
    void Clear()
    {
        memset(this, 0, sizeof(ProtoMS_SyncBuffReq));
        REDEF_PROTO_HEADER_MS(PROTO_MS_SYNC_BUFF_REQ);
    }
    ProtoMS_SyncBuffReq()
    {
        memset(buffs, 0, sizeof(buffs));
    }
};

struct ProtoMS_BuffAddAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_BUFF_ADD_ACK);

    uint32_t            nClientSessionID    = 0;

    uint64_t            role_guid           = 0;        // 可能是player/monster/npc's guid
    uint16_t            num                 = 0;        // Buff数量
    BUFF_INFO           info[50];                       // Buff信息
    uint16_t            clsessnum = 0;
    uint32_t            clsessids[300] = { 0 };

    ProtoMS_BuffAddAck()
    {
        memset(info, 0, sizeof(info));
    }
};

struct ProtoMS_BuffDestroyAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_BUFF_DESTROY_ACK);

    uint32_t            nClientSessionID    = 0;

    uint64_t            role_guid           = 0;        // 可能是player/monster/npc's guid
    uint16_t            id                  = 0;        // Buff id
    uint16_t            clsessnum = 0;
    uint32_t            clsessids[300] = { 0 };
};

struct ProtoMS_RunClientScript
{
    DEF_PROTO_HEADER_MS(PROTO_MS_RUN_CLIENT_SCRIPT);

    uint32_t                    clientSessionID     = 0;

    char                        form_name[256];                     //表单名称
    uint16_t                    size                = 0;            //表单内容字节数
    char                        form_content[65535];                 //表单内容
    uint8_t                     comp                = 0;            //是否要对表单内容进行压缩 0 = 不压缩 1 = 压缩
    uint8_t                     all                 = 0;
    uint16_t            clsessnum = 0;
    uint32_t            clsessids[300] = { 0 };
    void Clear()
    {
        memset(this, 0, sizeof(ProtoMS_RunClientScript));
        REDEF_PROTO_HEADER_MS(PROTO_MS_RUN_CLIENT_SCRIPT);
    }
    ProtoMS_RunClientScript()
    {
        memset(form_name, 0, sizeof(form_name));
        memset(form_content, 0, sizeof(form_content));
    }
};

struct ProtoMS_SysMsgNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SYS_MSG_NTF);

    uint32_t                    clientSessionID     = 0;

    uint8_t                     msg_type            = 0;            // 指定消息的类型，用来确定消息的显示区域
    uint8_t                     scroll_count        = 0;            // 消息的滚动次数 默认：1次
    char                        msg[256];                           // 具体的消息内容

    ProtoMS_SysMsgNtf()
    {
        memset(msg, 0, sizeof(msg));
    }
};

struct ProtoMS_SyncRoleInfoReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SYNC_ROLE_INFO_REQ);

    uint64_t                    userid              = 0;
    uint64_t                    roleid              = 0;

    ROLE_BRIEF_INFO             roleBriefInfo;
    ROLE_EXTRA_INFO             roleExtraInfo;
    ROLE_SETTINGS               roleSettings;

    ProtoMS_SyncRoleInfoReq()
    {
        memset(&roleBriefInfo, 0, sizeof(roleBriefInfo));
        memset(&roleExtraInfo, 0, sizeof(roleExtraInfo));
    }
};

struct ProtoMS_NpcAppearNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_NPC_APPEAR_NTF);

    uint32_t                    clientSessionID     = 0;

    uint64_t                    npc_guid            = 0;
    uint16_t                    template_id         = 0;            // 模板id
    uint16_t                    dst_x               = 0;            // 目标点x
    uint16_t                    dst_y               = 0;            // 目标点y
    uint8_t                     dir                 = 0;            // 方向
    char                        name[256];                          // 名字
    uint32_t                    modelid             = 0;            // 模型id

    ProtoMS_NpcAppearNtf()
    {
        memset(name, 0, sizeof(name));
    }
};

struct ProtoMS_TradeNpcShopNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_TRADE_NPC_SHOP_NTF);

    uint32_t                    clientSessionID     = 0;

    uint16_t                    shop_id             = 0;            // shop_index
    uint8_t                     item_count          = 0;            // 商品数量
    SHOP_ITEM_INFO              item_list[250];                     // 商品信息列表

    ProtoMS_TradeNpcShopNtf()
    {
        memset(item_list, 0, sizeof(item_list));
    }
};

struct ProtoMS_QuestNpcTalkAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_QUEST_NPC_TALK_ACK);

    uint32_t                    clientSessionID     = 0;

    uint16_t                    width               = 0;            // NPC对话框面板的宽度
    uint16_t                    height              = 0;            // NPC对话框面板的高度
    uint64_t                    npc_guid            = 0;            // npc的GUID
    uint16_t                    talk_len            = 0;            // NPC面板内容长度
    char                        talk[7500]          = {0};          // NPC面板显示的内容
    uint16_t                    quest_state_num     = 0;            // 任务状态数据数量
    QUEST_STATE_INFO            quest_states[2];                    // 任务状态数据
    uint8_t                     comp                = 0;            // 是否要对表单内容进行压缩 0 = 不压缩 1 = 压缩
    void Clear()
    {
        memset(this, 0, sizeof(ProtoMS_QuestNpcTalkAck));
        REDEF_PROTO_HEADER_MS(PROTO_MS_QUEST_NPC_TALK_ACK);
    }
    ProtoMS_QuestNpcTalkAck()
    {
        memset(quest_states, 0, sizeof(quest_states));
    }
};

struct ProtoMS_QuestTimeoutNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_QUEST_TIMEOUT_NTF);

    uint32_t                    client_sessionid    = 0;

    uint16_t                    quest_id            = 0;
};

struct ProtoMS_SyncQuestReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SYNC_QUEST_REQ);

    uint64_t                    playerid            = 0;
    uint64_t                    roleid              = 0;

    QUEST_INFO                  quest_info;
    uint8_t                     quest_achev_num     = 0;
    QUEST_ACHIEVE               quest_achevs[50];

    ProtoMS_SyncQuestReq()
    {
        memset(&quest_info, 0, sizeof(quest_info));
        memset(quest_achevs, 0, sizeof(quest_achevs));
    }
};

struct ProtoMS_QuestUpdateNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_QUEST_UPDATE_NTF);

    uint32_t                    client_sessionid    = 0;

    uint16_t                    quest_id            = 0;            // 任务模板id
    int32_t                     data_type           = 0;            // 数据类型, 参考quest_track_state
    int32_t                     id                  = 0;
    int32_t                     value               = 0;
};

struct ProtoMS_QuestDropNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_QUEST_DROP_NTF);

    uint32_t                    sessionid           = 0;

    uint16_t                    quest_id            = 0;
};

struct ProtoMS_QuestStateNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_QUEST_STATE_NTF);

    uint32_t                    sessionid           = 0;

    uint16_t                    quest_id            = 0;
    uint8_t                     state               = 0;            // 0：空闲，1：准备接任务，2：做任务，3：就绪，4：完成
};

struct ProtoMS_QuestNpcStateNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_QUEST_NPC_STATE_NTF);

    uint32_t                    sessionid           = 0;

    uint16_t                    npc_id              = 0;
    uint8_t                     state               = 0;            // 0：null，1：任务可交，2：任务可接，3：任务已接不可交
};

struct ProtoMS_RoleAttrExtRefNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_ROLE_ATTR_EXT_REF_NTF);

    uint32_t                    sessionid           = 0;

    uint16_t                    attr_name           = 0;            // 属性名称
    int64_t                     attr_value          = 0;            // 属性改变相对值
};

struct ProtoMS_LevelUpNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_LEVEL_UP_NTF);

    uint32_t                    sessionid           = 0;

    uint64_t                    player_guid         = 0;
    uint32_t                    level               = 0;
};

struct ProtoMS_RoleAppNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_ROLE_APP_NTF);

    uint32_t                    sessionid           = 0;

    uint64_t                    player_guid         = 0;            // player guid
    uint16_t                    hair                = 0;            // 头发
    uint16_t                    hair_color          = 0;            // 头发颜色
    uint16_t                    body                = 0;            // 身体
    uint16_t                    weapon              = 0;            // 武器
    uint16_t                    wings               = 0;            // 翅膀
    uint16_t                    mount               = 0;            // 坐骑
    uint16_t                    weapon_effect       = 0;            // 武器特效
    uint16_t                    body_effect         = 0;            // 身体特效
    uint16_t                    mount_effect        = 0;            // 坐骑特效
    uint16_t                    amulet              = 0;            // 法宝
    uint16_t                    equip_num           = 0;            // 扩展装备数量
    EQUIP_INFO                  equips[10];                         // 扩展装备信息
    uint8_t                     is_first            = 0;

    void Reset() { memset((uint8_t *)this + 4, 0, sizeof(*this) - 4); }
};

static ProtoMS_RoleAppNtf gProtoMS_RoleAppNtf;

struct ProtoMS_GetConstantCfgReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_GET_CONSTANT_CFG_REQ);
};

struct ProtoMS_GetTradeDelegateReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_GET_TRADE_DELEGATE_REQ);
};

struct ProtoMS_GetTradeRecordsReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_GET_TRADE_RECORDS_REQ);

    uint32_t            tradeRecordsExpireTime = 0;
};

struct ProtoMS_RecordsCancelReq
{
    enum RCQ_MaxSize
    {
        Info_Size = 100
    };
    DEF_PROTO_HEADER_MS(PROTO_MS_RECORDS_CANCEL_REQ);

    uint16_t            num = 0;
    uint64_t            trade_id[Info_Size] = { 0 };
    ProtoMS_RecordsCancelReq() = default;
};

struct ProtoMS_DelegateCancelReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_DELEGATE_CANCEL_REQ);

    uint8_t             delegate_type = 0;
    uint64_t            player_guid = 0;
    uint64_t            trade_id = 0;
    uint8_t             reason = 0;        //0:主动取消 1:委托到期取消
    uint32_t            token = 0;
    ProtoMS_DelegateCancelReq() = default;
};

struct ProtoMS_DelegateSellCmd
{
    DEF_PROTO_HEADER_MS(PROTO_MS_DELEGATE_SELL_CMD);
    DELEGATE_SELL_ITEM      sellItem;
    uint32_t                token = 0;
    void Clear()
    {
        memset(this, 0, sizeof(ProtoMS_DelegateSellCmd));
        REDEF_PROTO_HEADER_MS(PROTO_MS_DELEGATE_SELL_CMD);
    }
    ProtoMS_DelegateSellCmd() = default;
};

struct ProtoMS_DelegateBuyCmd
{
    DEF_PROTO_HEADER_MS(PROTO_MS_DELEGATE_BUY_CMD);
    DELEGATE_BUY_ITEM2      buyItem;
    uint32_t                token = 0;
    ProtoMS_DelegateBuyCmd() = default;

};

struct ProtoMS_MarketSellCmd
{
    DEF_PROTO_HEADER_MS(PROTO_MS_MARKET_SELL_CMD);
    uint64_t        trade_id = 0; //交易号
    uint64_t        seller_guid = 0;
    char            seller[32] = { 0 };
    uint32_t        count = 0;
    ITEM_INFO       item;
    uint32_t        token = 0;
    void Clear()
    {
        memset(this, 0, sizeof(ProtoMS_MarketSellCmd));
        REDEF_PROTO_HEADER_MS(PROTO_MS_MARKET_SELL_CMD);
    }
};

struct ProtoMS_MarketBuyCmd
{
    DEF_PROTO_HEADER_MS(PROTO_MS_MARKET_BUY_CMD);
    uint64_t        trade_id = 0; //交易号
    uint64_t        buyer_guid = 0;
    char            buyer[32] = { 0 };
    uint32_t        count = 0;
    uint32_t        token = 0;
};


struct ProtoMS_GetGuildsReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_GET_GUILDS_REQ);
};

struct ProtoMS_GetGuildMembersReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_GET_GUILD_MEMBERS_REQ);
};

struct ProtoMS_GetGuildApplicantsReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_GET_GUILD_APPLICANTS_REQ);
};

struct ProtoMS_FamilyNoticeAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_FAMILY_NOTICE_ACK);

    uint32_t                    sessionid           = 0;

    uint32_t                    notice_len          = 0;            // 公告长度
    char                        notice[1280]        = {0};          // 行会公告
};

struct ProtoMS_FamilyMembersAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_FAMILY_MEMBERS_ACK);

    uint32_t                    sessionid           = 0;

    uint32_t                    total_num           = 0;            // 总共的成员数量
    uint32_t                    first_index         = 0;            // 当前第一个的index，从0开始算
    uint32_t                    members_num         = 0;            // 成员数量
    MEMBER_INFO                 members[100];                       // 行会成员

    ProtoMS_FamilyMembersAck()
    {
        memset(members, 0, sizeof(members));
    }
};

struct ProtoMS_FamilyEnemyAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_FAMILY_ENEMY_ACK);

    uint32_t                    sessionid           = 0;

    uint32_t                    total_num           = 0;            // 总共的成员数量
    uint32_t                    first_index         = 0;            // 当前第一个的index，从0开始算
    uint32_t                    enemy_num           = 0;            // 行会数量
    FAMILY_INFO                 enemy[MAX_ENEMY_NUM];               // 行会列表

    ProtoMS_FamilyEnemyAck()
    {
        memset(enemy, 0, sizeof(enemy));
    }
};

struct ProtoMS_FamilyAllyAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_FAMILY_ALLY_ACK);

    uint32_t                    sessionid           = 0;

    uint32_t                    total_num           = 0;            // 总共的成员数量
    uint32_t                    first_index         = 0;            // 当前第一个的index，从0开始算
    uint32_t                    ally_num            = 0;            // 行会数量
    FAMILY_INFO                 ally[MAX_ALLY_NUM];                 // 行会列表

    ProtoMS_FamilyAllyAck()
    {
        memset(ally, 0, sizeof(ally));
    }
};

struct ProtoMS_FamilyJoinListAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_FAMILY_JOIN_LIST_ACK);

    uint32_t                    sessionid           = 0;

    uint32_t                    total_num           = 0;            // 总共的成员数量
    uint32_t                    first_index         = 0;            // 当前第一个的index，从0开始算
    uint16_t                    num                 = 0;            // 数量
    APPLICANTS_INFO             info[50];                           // 申请者列表

    ProtoMS_FamilyJoinListAck()
    {
        memset(info, 0, sizeof(info));
    }
};

struct ProtoMS_FamilyBaseInfoAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_FAMILY_BASE_INFO_ACK);

    uint32_t                    sessionid           = 0;

    uint64_t                    family_guid         = 0;            // 行会id
    char                        name[32]            = {0};          // 行会名称
    uint32_t                    members_num         = 0;            // 行会人数
    uint64_t                    create_time         = 0;            // 创建时间
    uint8_t                     self_title_id       = 0;            // 查询者自己在行会中的封号ID
};

struct ProtoMS_FamilyListNtfAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_FAMILY_LIST_NTF_ACK);

    uint32_t                    sessionid           = 0;

    uint32_t                    total_num           = 0;            // 总共的成员数量
    uint32_t                    first_index         = 0;            // 当前第一个的index，从0开始算
    uint32_t                    num                 = 0;            // 行会数量
    FAMILY_APPLY_INFO           familys[100];                       // 行会列表

    ProtoMS_FamilyListNtfAck()
    {
        memset(familys, 0, sizeof(familys));
    }
};

struct ProtoMS_PopDlgMsgNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_POP_DLG_MSG_NTF);

    uint32_t                    sessionid           = 0;

    char                        msg[256]            = {0};          // 消息内容
};

struct ProtoMS_SyncPlayerCustVar
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SYNC_PLAYER_CUST_VAR);

    uint64_t                    playerid            = 0;
    uint64_t                    roleid              = 0;

    CUST_VAR_MAP               *vars                = nullptr;
};

struct ProtoMS_SetCustVar
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SET_CUST_VAR);

    CUST_VAR                   *var                 = nullptr;
};

struct ProtoMS_SyncPlayerItemCustVar
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SYNC_PLAYER_ITEM_CUST_VAR);

    uint64_t                    playerid            = 0;
    uint64_t                    roleid              = 0;

    CUST_VAR_SP_LIST           *vars                = nullptr;
};

struct ProtoMS_GetCustVarReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_GET_CUST_VAR_REQ);
};

struct ProtoMS_PlayerQueryNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_PLAYER_QUERY_NTF);
    enum {
        max_item_info_num = 45,
    };
    uint32_t                    sessionid           = 0;

    uint64_t                    player_guid         = 0;
    char                        name[128]           = {0};          //玩家名称
    uint8_t                     gender              = 0;            //性别
    uint8_t                     job                 = 0;            //职业
    uint32_t                    level               = 0;            //等级
    char                        family_name[32]     = {0};          //行会名称
    char                        family_title[32]    = {0};          //行会称号
    char                        alias[64]           = {0};          //别名
    uint16_t                    item_num            = 0;            //物品数量
    ITEM_INFO                   item_info[max_item_info_num];       //物品信息
    unsigned char               isFinalPack         = 0;            //是否是最后一个包
    ProtoMS_PlayerQueryNtf()
    {
        memset(item_info, 0, sizeof(item_info));
    }

    void Reset()
    {
        sessionid       = 0;
        player_guid     = 0;
        memset(name, 0, sizeof(name));
        gender          = 0;
        job             = 0;
        level           = 0;
        memset(family_name, 0, sizeof(family_name));
        memset(family_title, 0, sizeof(family_title));
        memset(alias, 0, sizeof(alias));
        item_num        = 0;
        memset(item_info, 0, sizeof(item_info));
        isFinalPack     = 0;
    }
};

struct ProtoMS_MsgNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_MSG_NTF);

    uint32_t                    sessionid = 0;

    uint8_t                     foreground = 0;            // 消息前景颜色ID
    uint8_t                     background = 0;            // 消息背景颜色ID
    uint8_t                     count      = 0;            // 消息滚动次数
    uint8_t                     site       = 0;            // 消息位置  0:top  1:center  2:bottom
    char                        msg[256]   ={0};           // 消息内容
};

struct ProtoMS_PlayerFamilyChangeNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_PLAYER_FAMILY_CHANGE_NTF);

    uint32_t                    sessionid           = 0;

    uint64_t                    player_guid         = 0;
    char                        family_name[32]     = {0};          //行会名称
    char                        castle_name[256]    = {0};          //城堡名称，可以多个用与符号分隔
    uint8_t                     title               = 0;
};

struct ProtoMS_SyncGuildApplicant
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SYNC_GUILD_APPLICANT);

    uint8_t                     type                = 0;            // 1增，2删，3改
    GUILD_APPLY_INFO           *applicant           = nullptr;
};

struct ProtoMS_CancelFamilyJoinAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_CANCEL_FAMILY_JOIN_ACK);

    uint32_t                    sessionid           = 0;

    uint64_t                    guid                = 0;            // 行会id
    uint32_t                    errcode             = 0;            // 错误码 0表示取消成功
};

struct ProtoMS_SyncGuildMember
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SYNC_GUILD_MEMBER);

    uint8_t                     type                = 0;
    GUILD_MEMBER               *member              = nullptr;
};

struct ProtoMS_FamilyLeaveNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_FAMILY_LEAVE_NTF);

    uint32_t                    sessionid           = 0;

    char                        kicker_name[32]     = {0};          // 开除者名字, 为空的话则是主动离开
    char                        family_name[32]     = {0};          // 行会名称
};

struct ProtoMS_FamilyInfoNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_FAMILY_INFO_NTF);

    uint32_t                    sessionid           = 0;

    uint32_t                    type                = 0;            // 变更内容；1、行会公告；2、行会消息；4、行会封号；8、行会成员；16、敌对行会；32、联盟行会；64、入会申请列表；
};

struct ProtoMS_SyncGuildInfo
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SYNC_GUILD_INFO);

    uint8_t                     type                = 0;
    GUILD_INFO                 *guild               = nullptr;
};

struct ProtoMS_SyncGuildRelation
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SYNC_GUILD_RELATION);

    uint8_t                     type                = 0;
    uint64_t                    my_guild_guid       = 0;
    uint64_t                    peer_guild_guid     = 0;
    uint8_t                     relation            = 0;
};

struct ProtoMS_MissNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_MISS_NTF);

    uint64_t                    actor               = 0;            //actor, 可能是player/monster/npc's guid
    uint64_t                    target              = 0;            //target, 可能是player/monster/npc's guid
    uint16_t                    skill_id            = 0;            //技能id
    uint8_t                     type                = 0;            //1=闪避 2=免疫
    uint16_t                    clsessnum           = 0;
    uint32_t                    clsessids[300]      = {0};
};

struct ProtoMS_SyncItemDynAttrs
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SYNC_ITEM_DYN_ATTRS);

    uint64_t                    playerid            = 0;
    uint64_t                    roleid              = 0;

    ITEM_DYN_ATTRS_LIST        *attrs_list          = nullptr;
};


struct ProtoMS_SyncRoleDynAttrs
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SYNC_ROLE_DYN_ATTRS);

    uint64_t                    playerid = 0;
    uint64_t                    roleid = 0;
    ROLE_DYN_ATTRS_LIST         * attrs_list = nullptr;
};


struct ProtoMS_SkillStatusNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SKILL_STATUS_NTF);

    uint32_t                    sessionid           = 0;

    uint16_t                    id                  = 0;            // 技能id
    uint8_t                     active              = 0;            // 0=不激活 1=激活
};

struct ProtoMS_ShabakOwnerNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SHABAK_OWNER_NTF);

    uint32_t                    sessionid           = 0;

    uint64_t                    role_guid           = 0;            // 沙巴克索引地图名
};

struct ProtoMS_ShabakLossNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SHABAK_LOSS_NTF);

    uint32_t                    sessionid           = 0;

    uint64_t                    role_guid           = 0;            // 沙巴克索引地图名
};

struct ProtoMS_ShabakEngageNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SHABAK_ENGAGE_NTF);

    uint32_t                    sessionid               = 0;

    char                        own_family[32]          = {0};          // 所属行会
    char                        attack_families[4096]   = {0};          // 攻方行会
};

struct ProtoMS_ShabakEndNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SHABAK_END_NTF);

    uint32_t                    sessionid           = 0;
};

struct ProtoMS_RunningFamilyWarNtf {
    enum MaxSize {
        MAX_SIZE = 100,
    };
    DEF_PROTO_HEADER_MS(PROTO_MS_FAMILY_WAR_NTF);
    uint32_t                  sessionid = 0;
    uint8_t                   idx = 1;
    uint8_t                   total = 1;
    uint16_t                   num;                      // 进行中的行会战数量
    FAMILY_WAR_INFO           families[MAX_SIZE];       // 进行中的行会战信息
};

struct ProtoMS_SkillCDChangedNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SKILL_CD_CHANGED_NTF);

    uint32_t                    clsessid            = 0;

    uint16_t                    skill_id            = 0;            // 技能ID
    uint32_t                    new_cd              = 0;            // 技能冷却时间
};

struct ProtoMS_SkillPropPermanentChangedNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SKILL_PROP_PERMANENT_CHANGED_NTF);

    uint32_t                    clsessid            = 0;

    uint64_t                    player_guid         = 0;
    uint16_t                    num = 0;
    SKILL_INFO                  info[100];
    void Clear()
    {
        memset(this, 0, sizeof(ProtoMS_SkillPropPermanentChangedNtf));
        REDEF_PROTO_HEADER_MS(PROTO_MS_SKILL_PROP_PERMANENT_CHANGED_NTF);
    }
};

struct ProtoMS_GetWantedListReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_GET_WANTED_LIST_REQ);
};

struct ProtoMS_GetWantedListAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_GET_WANTED_LIST_ACK);

    WANTED_SP_LIST             *pwanted_list        = nullptr;
};

struct ProtoMS_PostBountyReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_POST_BOUNTY_REQ);

    uint64_t                    wanted_by_guid      = 0;
    char                        wanted_by_name[50]  = {0};
    char                        wanted_name[50]     = {0};
    uint32_t                    bounty              = 0;
    char                        desc[50]            = {0};
    uint64_t                    ptime               = 0;
};

struct ProtoMS_PostBountyAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_POST_BOUNTY_ACK);

    uint8_t                     result              = 0;            // 0成功，其他失败
    uint32_t                    index               = 0;
    uint64_t                    wanted_by_guid      = 0;
    char                        wanted_by_name[50]  = {0};
    uint64_t                    wanted_guid         = 0;
    char                        wanted_name[50]     = {0};
    uint32_t                    bounty              = 0;
    char                        desc[50]            = {0};
    uint64_t                    ptime               = 0;
};

struct ProtoMS_CheckRoleExistenceReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_CHECK_ROLE_EXISTENCE_REQ);

    uint32_t                    seq                 = 0;            // 序列号，用来区分不同查询
    uint8_t                     by                  = 0;            // 0名字, 1 guid
    char                        name[50]            = {0};
    uint64_t                    guid                = 0;
};

struct ProtoMS_CheckRoleExistenceAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_CHECK_ROLE_EXISTENCE_ACK);

    uint32_t                    seq                 = 0;            // 序列号，用来区分不同查询
    uint8_t                     by                  = 0;            // 0名字, 1 guid
    char                        name[50]            = {0};
    uint64_t                    guid                = 0;
    uint8_t                     exist               = 0;
};

struct ProtoMS_SkillProficiencyNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SKILL_PROFICIENCY_NTF);

    uint32_t                    clsessid            = 0;

    uint16_t                    id                  = 0;            // 技能id
    uint32_t                    proficiency         = 0;            // 技能熟练度
};

struct ProtoMS_ItemPickupNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_ITEM_PICKUP_NTF);

    uint32_t                    clsessid            = 0;

    uint64_t                    item_guid           = 0;            // 物品id
    uint64_t                    role_guid           = 0;            // 被谁捡起
};

struct ProtoMS_AutoPickupSettingsNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_AUTO_PICKUP_SETTINGS_NTF);

    uint32_t                    clsessid            = 0;

    AUTO_PICKUP                 auto_pickup;
};

struct ProtoMS_StartDigAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_START_DIG_ACK);

    uint32_t                    clsessid            = 0;
    uint64_t                    treasure_guid       = 0;            // 宝物GUID
    uint8_t                     code                = 0;            // 0－正常；1－宝物不存在；2－超出挖宝范围
    uint32_t                    dig_time            = 0;            // 采集时间
};

struct ProtoMS_StopDigNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_STOP_DIG_NTF);

    uint32_t                    clsessid            = 0;
    uint64_t                    treasure_guid       = 0;            // 宝物GUID
    uint8_t                     reason              = 0;            // 0－倒计时结束；1－角色移动；2－角色死亡；3－被其他人挖走
};

struct ProtoMS_RoleAppearNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_ROLE_APPEAR_NTF);

    uint32_t                    clsessid            = 0;
    uint64_t                    role_guid           = 0;            // 角色GUID
    uint8_t                     appear_type         = 0;            // 0=进入视野 1=出生 2=跳跃 3=挖宝
};

struct ProtoMS_SaveGoodsIssueRecord
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SAVE_GOODS_ISSUE_RECORD);

    uint64_t                    player_guid         = 0;
    uint64_t                    role_guid           = 0;
    GOODS_ISSUE_RECORD          record;
};

struct ProtoMS_VerifyBuyItemInfoAck
{
    DEF_PROTO_HEADER_MS(PROTO_MS_VERIFY_BUY_ITEM_INFO_ACK);

    uint32_t                    clsessid            = 0;
    uint32_t                    item_id             = 0;            // 购买的商品ID
    uint8_t                     status              = 0;            // 商品能否购买
};

struct ProtoMS_GoodsIssuedNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_GOODS_ISSUED_NTF);

    uint64_t                    player_guid         = 0;
    uint64_t                    role_guid           = 0;
    uint8_t                     num                 = 0;
    char                        order_no[MAX_GOODS_ISSUE_RECORD][ORDER_NO_BUFLEN] = {0};
};

struct ProtoMS_SyncGoodsPostRecord
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SYNC_GOODS_POST_RECORD);

    uint64_t                    player_guid = 0;
    uint64_t                    role_guid = 0;
    uint8_t                     num = 0;
    char                        order_no[MAX_GOODS_POST_RECORD][ORDER_NO_BUFLEN] = { 0 };
};

struct ProtoMS_RebateMoneyUsedNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_REBATE_MONDY_USED_NTF);

    uint64_t                    role_guid = 0;
    REBATE_MONEY_RECORD         record;
};

struct ProtoMS_ItemTip
{
    DEF_PROTO_HEADER_MS(PROTO_MS_ITEM_TIP);
    uint64_t                    guid = 0;
    uint64_t                    owner_guid = 0;
    uint64_t                    item_guid = 0;
};

struct ProtoMS_MonitorChatMsg
{
    DEF_PROTO_HEADER_MS(PROTO_MS_MONITOR_CHAT_MSG);
    MONITOR_CHAT_INFO info;
    void Clear(){
        memset(this, 0, sizeof(ProtoMS_MonitorChatMsg));
        REDEF_PROTO_HEADER_MS(PROTO_MS_MONITOR_CHAT_MSG);
    }
};
static ProtoMS_MonitorChatMsg gProtoMS_MonitorChatMsg;

struct ProtoMS_SetAutoModeReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SET_AUTO_MODE_REQ);

    uint32_t                    clsessid            = 0;
    uint64_t                    role_guid           = 0;
    uint8_t                     enable              = 0;
};

struct ProtoMS_SceneItemUpdateNtf
{
    DEF_PROTO_HEADER_MS(PROTO_MS_SCENE_ITEM_UPDATE_NTF);

    uint32_t                    clsessid            = 0;
    uint64_t                    item_guid           = 0;
};

struct ProtoMS_RunGMCmd
{
    DEF_PROTO_HEADER_MS(PROTO_MS_RUNGMCMD);

    char                        cmd[256]            = {0};      //GM 指令
    char                        param[1024]         = {0};      //指令参数
};


struct ProtoMS_CustomHttp
{
    DEF_PROTO_HEADER_MS(PROTO_MS_CUSTOM_HTTP);

    char                        cmd[256] = { 0 };      //自定义参数
    char                        param[1024] = { 0 };   //自定义参数
    char                        callBackFunc[1024] = { 0 };   //自定义参数
};

struct ProtoMS_UpdateConstantCfgReq
{
    DEF_PROTO_HEADER_MS(PROTO_MS_UPDATE_CONSTANT_CFG_REQ);
    CUSTOM_INFO               custom;// size,key-value,...
};

class ProtoMS
{
public:
    ProtoMS();
    ~ProtoMS();

    static inline uint16_t GetModuleID(void) { return MODULE_TYPE_MS; }
    static inline uint16_t GetProtocolNum(void) { return PROTO_MS_MAX; }

    int BuildProtocol(void* pHost, char* pNet, int iNetSize);
    int HandleProtocol(void* pHost, char* pNet, int iNetSize);

private:
    EnCodeFunc m_EnCodeFuncArray[PROTO_MS_MAX];
    DeCodeFunc m_DeCodeFuncArray[PROTO_MS_MAX];
};
