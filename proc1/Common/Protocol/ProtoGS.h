#pragma once
#include "ProtoDef.h"

#define DEF_PROTO_HEADER_GS(protoid) uint16_t moduleid = MODULE_TYPE_GS; uint16_t protocolid = protoid
#define REDEF_PROTO_HEADER_GS(protoid) moduleid = MODULE_TYPE_GS; protocolid = protoid
enum
{
    PROTO_SESSION_LS2GS_NTF,
    PROTO_SESSION_CS2GS_NTF,
    PROTO_SESSION_MS2GS_NTF,
    PROTO_GS_HEART_BEAT_REQ,
    PROTO_GS_HEART_BEAT_ACK,
    PROTO_GS_CONFIG_REQ,    // GS -> SS
    PROTO_GS_CONFIG_ACK,    // SS -> GS
    PROTO_GS_LOGIN_REQ,     // GS -> LS
    PROTO_GS_LOGIN_ACK,     // LS -> GS
    PROTO_GS_LOGOUT_REQ,    // GS -> LS
    PROTO_GS_RELOGIN_REQ,   // GS -> LS
    PROTO_GS_RELOGIN_ACK,   // GS -> CL
    PROTO_GS_ENTER_MAP_REQ, // GS -> CS
    PROTO_GS_ENTER_MAP_ACK, // CS -> GS
    PROTO_GS_GET_ROLE_LIST_REQ,     // GS -> CS
    PROTO_GS_GET_ROLE_LIST_ACK,     // CS -> GS
    PROTO_GS_ENTER_GS_REQ, // GS -> CS
    PROTO_GS_ENTER_GS_NTF, // CS -> GS
    PROTO_GS_CREATE_ROLE_REQ,   // GS -> CS
    PROTO_GS_CREATE_ROLE_ACK,   // CS -> GS
    PROTO_GS_DELETE_ROLE_REQ,   // GS -> CS
    PROTO_GS_DELETE_ROLE_ACK,   // CS -> GS
    PROTO_GS_MOVE_REQ,          // GS -> MS
    PROTO_GS_MOVE_ACK,          // MS -> GS
    PROTO_GS_TURN_REQ,          // GS -> MS
    PROTO_GS_TURN_NTF,          // MS -> GS
    PROTO_GS_SPELL_TARGET,      // GS -> MS
    PROTO_GS_SPELL_GRID,        // GS -> MS
    PROTO_GS_SPELL_ACK,         // MS -> GS
    PROTO_GS_EXIT_GS_REQ,         // GS -> MS
    PROTO_GS_EXIT_GS_ACK,         // MS -> GS
    PROTO_GS_SKILL_SWITCH,      // GS -> MS
    PROTO_GS_SKILL_SWITCH_ACK,  // MS -> GS
    PROTO_GS_ITEM_APPLY,  // MS -> GS
    PROTO_GS_ITEM_ARRANGE,  // GS -> MS
    PROTO_GS_ITEM_DROP,  // MS -> GS
    PROTO_GS_CREATE_PLAYER_REQ,  // GS -> MS
    PROTO_GS_KICK_ROLE_NTF,
    PROTO_GS_SAVE_KEY_NTF,
    PROTO_GS_ITEM_PICK_UP,
    PROTO_GS_ITEM_MOVE,
    PROTO_GS_RUN_SERV_SCRIPT_REQ,
    PROTO_GS_RUN_SERV_SCRIPT_ACK,
    PROTO_GS_RELIVE_REQ,
    PROTO_GS_RELIVE_ACK,
    PROTO_GS_RELATION_CHAT_REQ,
    PROTO_GS_RELATION_CHAT_ACK,
    PROTO_GS_RELATION_CHAT_NTF,
    PROTO_GS_PRIVATE_CHAT_NTF,
    PROTO_GS_SPEAKER_MSG_REQ,
    PROTO_GS_SPEAKER_MSG_NTF,
    PROTO_GS_TRADE_MALL_BUY,
    PROTO_GS_TRADE_MALL_LIST_REQ,
    PROTO_GS_TRADE_MALL_LIST_ACK,
    PROTO_GS_NPC_SELECT,                    // GS -> MS
    PROTO_GS_NPC_TALK_REQ,                  // GS -> MS
    PROTO_GS_TRADE_NPC_BUY,                 // GS -> MS
    PROTO_GS_ATK_MODE_REQ,                  // GS -> MS
    PROTO_GS_QUEST_QUERY_CAN_ACCEPT,        // GS -> MS
    PROTO_GS_QUEST_QUERY_CAN_ACCEPT_NTF,    // MS -> GS
    PROTO_GS_QUEST_ACCEPT,                  // GS -> MS
    PROTO_GS_QUEST_ADD_NTF,                 // MS -> GS
    PROTO_GS_QUEST_DROP,                    // GS -> MS
    PROTO_GS_QUEST_ACCOMPLISH,              // GS -> MS
    PROTO_GS_TEAM_OPERATION,
    PROTO_GS_TEAM_LEAVE_REQ,
    PROTO_GS_PLAYER_SWITCH_REQ,
    PROTO_GS_TEAM_INVITE,
    PROTO_GS_TEAM_INVITE_RSP,
    PROTO_GS_TEAM_KICK_REQ,
    PROTO_GS_GET_ARROUND_TEAM_REQ,
    PROTO_GS_TEAM_JOIN,
    PROTO_GS_TEAM_JOIN_RSP,
    PROTO_GS_GET_FAMILY_INFO_REQ,
    PROTO_GS_PLAYER_QUERY,
    PROTO_GS_QUICK_BAR_SET,  
    PROTO_GS_QUICK_GOLD_TAKE,
    PROTO_GS_QUICK_GOLD_DEPOSIT,
    PROTO_GS_GM_COMMAND_REQ,
	PROTO_GS_TOPLIST_REQ,
    PROTO_GS_TOPLIST_ACK,

    PROTO_GS_FAMILY_JOIN_REQ,
    PROTO_GS_CANCEL_FAMILY_JOIN_REQ,
    PROTO_GS_FAMILY_JOIN_ACK,

    PROTO_GS_FAMILY_EXPELL_REQ,
    PROTO_GS_FAMILY_NOTICE_EDIT_REQ,
    PROTO_GS_FAMILY_TITLE_AWARD_REQ,	
    PROTO_GS_MAIL_LIST_REQ,
    PROTO_GS_MAIL_OPEN_REQ,
    PROTO_GS_MAIL_ATTACHMENT_GET_REQ,
    PROTO_GS_MAIL_DEL_REQ,     
    PROTO_GS_FRIEND_ADD_REQ,
    PROTO_GS_FAMILY_LEAVE_OR_LAST_MSG_REQ,
    PROTO_GS_FAMILY_DESTROY_REQ,

    PROTO_GS_DELEGATE_MINE_REQ,
    PROTO_GS_DELEGATE_LIST_REQ,
    PROTO_GS_DELEGATE_CANCEL_REQ,
    PROTO_GS_DELEGATE_SELL_CMD,
    PROTO_GS_DELEGATE_BUY_CMD,
    PROTO_GS_MARKET_BUY_CMD,
    PROTO_GS_MARKET_SELL_CMD,
    PROTO_GS_QUERY_EX,
    PROTO_GS_THIRD_LOGIN_REQ,

    PROTO_GS_SYS_MSG_NTF2,
    PROTO_GS_SCENE_DIALOG_NTF,
    PROTO_GS_SCROLL_TEXT_NTF,
    PROTO_GS_UPDATE_ONLINE_STATE,
    PROTO_GS_SYNC_SESSION_ID,
    PROTO_GS_TRADE_LIST_UPDATE,
    PROTO_GS_SET_MAINTENANCE_STATUE,
    PROTO_GS_KICK_OUT_BY_LOCK,
    PROTO_GS_JUMP_MAP_REQ,
    PROTO_GS_GET_NPC_POS_REQ,
    PROTO_GS_GET_NPC_POS_ACK,
    PROTO_GS_START_DIG_REQ,
    PROTO_GS_RANGE_PICKUP,
    PROTO_GS_SYNC_CLIENT_BASE_SETTING,
    PROTO_GS_VERIFY_BUY_ITEM_INFO_REQ,
    PROTO_GS_PLAYER_SET_NAME_NTF,
    PROTO_GS_ITEM_REFRESH_REQ,
    PROTO_GS_ITEM_TIP,
    PROTO_GS_ITEM_TIP_NTF,  
    PROTO_GS_CUST_MSG_NTF,
    PROTO_GS_ITEM_SPLIT,

    PROTO_GS_TITLE_ADD_ACK,
    PROTO_GS_TITLE_DEL,
    PROTO_GS_TITLE_DEL_ACK,
    PROTO_GS_TITLE_WEAR,
    PROTO_GS_TITLE_WEAR_NTF,
    PROTO_GS_TITLE_UNWEAR,
    PROTO_GS_TITLE_UNWEAR_NTF,
    PROTO_GS_TITLE_LIST,    
    
    PROTO_GS_SET_AUTO_MODE_ACK,
    PROTO_GS_RECORDS_MINE_REQ,
    PROTO_GS_TITLE_GET_LIST_REQ,
    PROTO_GS_AFTER_RELOGIN_UPDATE_STATUS,

    PROTO_GS_ROLE_CUST_VAR_REQ,

    PROTO_GS_RESTORE_ROLE_REQ,   // GS -> CS
    PROTO_GS_RESTORE_ROLE_ACK,   // CS -> GS
    PROTO_GS_GOODS_POST_RECORD_ACK,
    PROTO_GS_MAX
};

struct ProtoGS_GoodsPostRecordAck {
    DEF_PROTO_HEADER_GS(PROTO_GS_GOODS_POST_RECORD_ACK);
    uint64_t guid = 0;
    char     order_no[ORDER_NO_BUFLEN] = { 0 };           // 订单号
    ProtoGS_GoodsPostRecordAck() = default;
};

struct ProtoGS_AfterReloginUpdateStatus {
    DEF_PROTO_HEADER_GS(PROTO_GS_AFTER_RELOGIN_UPDATE_STATUS);
    uint64_t guid = 0;
    ProtoGS_AfterReloginUpdateStatus() = default;
};

struct ProtoGS_TitleGetListReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_TITLE_GET_LIST_REQ);
    uint64_t guid = 0;
    ProtoGS_TitleGetListReq() = default;
};

struct ProtoGS_TitleAddAck
{
    DEF_PROTO_HEADER_GS(PROTO_GS_TITLE_ADD_ACK);
    TITLE_INFO info;
    uint32_t    sessionid = 0;
    ProtoGS_TitleAddAck() = default;
};

struct ProtoGS_TitleDel
{
    DEF_PROTO_HEADER_GS(PROTO_GS_TITLE_DEL);
    uint64_t    guid = 0;
    uint32_t    id = 0;
    ProtoGS_TitleDel() = default;
};

struct ProtoGS_TitleDelAck
{
    DEF_PROTO_HEADER_GS(PROTO_GS_TITLE_DEL_ACK);
    uint32_t    id = 0;
    unsigned char err = 0;
    uint32_t    sessionid = 0;
    ProtoGS_TitleDelAck() = default;
};

struct ProtoGS_TitleWear
{
    DEF_PROTO_HEADER_GS(PROTO_GS_TITLE_WEAR);
    uint64_t    guid = 0;
    uint32_t    id = 0;
    ProtoGS_TitleWear() = default;
};

struct ProtoGS_TitleWearNtf
{
    DEF_PROTO_HEADER_GS(PROTO_GS_TITLE_WEAR_NTF);
    uint64_t    guid = 0;
    uint32_t    id = 0;
    uint32_t sessionid = 0;
    ProtoGS_TitleWearNtf() = default;
};

struct ProtoGS_TitleUnWear
{
    DEF_PROTO_HEADER_GS(PROTO_GS_TITLE_UNWEAR);
    uint64_t    guid = 0;
    uint32_t    id = 0;
    ProtoGS_TitleUnWear() = default;
};

struct ProtoGS_TitleUnWearNtf
{
    DEF_PROTO_HEADER_GS(PROTO_GS_TITLE_UNWEAR_NTF);
    uint64_t    guid = 0;
    uint32_t    id = 0;
    uint32_t sessionid = 0;
    ProtoGS_TitleUnWearNtf() = default;
};

struct ProtoGS_TitleList
{
    DEF_PROTO_HEADER_GS(PROTO_GS_TITLE_LIST);
    uint64_t    guid = 0;
    uint16_t    num = 0;
    TITLE_INFO  info[100];
    uint32_t    sessionid = 0;
    ProtoGS_TitleList() = default;
};

struct ProtoGS_PlayerSetNameNtf 
{
    DEF_PROTO_HEADER_GS(PROTO_GS_PLAYER_SET_NAME_NTF);
    uint64_t    guid = 0;
    char        name[32];
    char        orgName[32];
    uint32_t    sessionid = 0;
    ProtoGS_PlayerSetNameNtf()
    {
        memset(name, 0, _countof(name));
    }
};

struct ProtoGS_KickOutByLock
{
    DEF_PROTO_HEADER_GS(PROTO_GS_KICK_OUT_BY_LOCK);
    uint32_t    sessionid = 0;
    uint32_t    token     = 0;
    uint8_t     info      = 0 ;           //登出类型
    uint8_t     type      = 0;            //是否踢掉所有人
    ProtoGS_KickOutByLock() = default;
};

struct ProtoGS_SetMaintenanceStatus
{
    DEF_PROTO_HEADER_GS(PROTO_GS_SET_MAINTENANCE_STATUE);
    uint8_t status = 0;
    ProtoGS_SetMaintenanceStatus() = default;
};

struct ProtoGS_TradeMallListUpdate
{
    DEF_PROTO_HEADER_GS(PROTO_GS_TRADE_LIST_UPDATE);
    uint32_t                    sessionid = 0;
    unsigned char               item_count = 0; //商品数量
    MALL_ITEM_INFO              item_list[250]; //商品信息列表
    ProtoGS_TradeMallListUpdate()
    {
        memset(item_list, 0, sizeof(item_list));
    }
};

struct ProtoGS_SysMsgNtf2 {
    DEF_PROTO_HEADER_GS(PROTO_GS_SYS_MSG_NTF2);
    SYSTEN_MESSAGE_NTF info;
    uint32_t  sessid = 0;
    uint8_t   all = 0;
    void Clear()
    {
        memset(this, 0, sizeof(ProtoGS_SysMsgNtf2));
        REDEF_PROTO_HEADER_GS(PROTO_GS_SYS_MSG_NTF2);
    }
};

struct ProtoGS_SceneDialogNtf {
    DEF_PROTO_HEADER_GS(PROTO_GS_SCENE_DIALOG_NTF);
    SCENCE_DIALOG_NTF info;
    uint32_t   sessid          = 0;
    void Clear()
    {
        memset(this, 0, sizeof(ProtoGS_SceneDialogNtf));
        REDEF_PROTO_HEADER_GS(PROTO_GS_SCENE_DIALOG_NTF);
    }
};

struct ProtoGS_ScrollText {
    DEF_PROTO_HEADER_GS(PROTO_GS_SCROLL_TEXT_NTF);
    SCROLL_TEXT info;
    uint32_t sessid = 0;
    uint8_t  all = 0;
    void Clear()
    {
        memset(this, 0, sizeof(ProtoGS_ScrollText));
        REDEF_PROTO_HEADER_GS(PROTO_GS_SCROLL_TEXT_NTF);
    }
};

struct ProtoGS_QueryEx
{
    DEF_PROTO_HEADER_GS(PROTO_GS_QUERY_EX);
    uint64_t                  self_role_id;
    uint64_t                  role_id;
    uint32_t                  token;
    ProtoGS_QueryEx() = default;
};

struct ProtoGS_MaillistReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_MAIL_LIST_REQ);
    uint8_t                   type; //邮件类型：0、系统，1、玩家 2、所有类型
    uint64_t                  mail_id; //只接收该邮件后的邮件
    uint64_t                  role_id;
    ProtoGS_MaillistReq() = default;
};

struct ProtoGS_MailOpenReq {
    DEF_PROTO_HEADER_GS(PROTO_GS_MAIL_OPEN_REQ);
    uint64_t                  id; //邮件的ID
    uint64_t                  role_id;
    ProtoGS_MailOpenReq() = default;
};

struct ProtoGS_MailAttachmentGetReq {
    DEF_PROTO_HEADER_GS(PROTO_GS_MAIL_ATTACHMENT_GET_REQ);
    uint64_t                  mail_id; //邮件ID
    unsigned char             index; //附件序列：1是金币，2是元宝, 3-7为物品，8为积分
    uint64_t                  role_id;
    ProtoGS_MailAttachmentGetReq() = default;
};

struct ProtoGS_MailDeleteReq {
    DEF_PROTO_HEADER_GS(PROTO_GS_MAIL_DEL_REQ);
    uint64_t                  id; //邮件的ID
    uint64_t                  role_id;
    ProtoGS_MailDeleteReq() = default;
};

struct ProtoGS_DelegateMineReq {
    DEF_PROTO_HEADER_GS(PROTO_GS_DELEGATE_MINE_REQ);
    uint64_t            role_id = 0;
    uint32_t            sessionid = 0;
    ProtoGS_DelegateMineReq() = default;
};

struct ProtoGS_RecordsMineReq {
    enum RMR_TYPE 
    {
        sell = 0,
        buy = 1,
    };
    DEF_PROTO_HEADER_GS(PROTO_GS_RECORDS_MINE_REQ);
    uint64_t            role_id = 0;
    uint16_t            type = 0;
    uint32_t            sessionid = 0;
    ProtoGS_RecordsMineReq() = default;
};

struct ProtoGS_DelegateListReq {
    DEF_PROTO_HEADER_GS(PROTO_GS_DELEGATE_LIST_REQ);
    uint32_t                start = 0;  //起始序列号
    uint32_t                count = 0;  //申请数量
    uint16_t                type = 0;   //分类
    uint16_t                subtype = 0; //子分类
    char                    item_name[32] = { 0 }; //物品名称过滤
    uint8_t                 is_reverse = 0; //是否倒序
    uint8_t                 delegatetype = 0;// 委托类型
    uint64_t                role_id = 0;
    uint32_t                sessionid = 0;
    ProtoGS_DelegateListReq() = default;
};

struct ProtoGS_DelegateCancelReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_DELEGATE_CANCEL_REQ);
    uint64_t        trade_id = 0; //交易号
    uint64_t        role_id = 0;
    uint32_t        sessionid = 0;
};

struct ProtoGS_DelegateSellCmd
{
    DEF_PROTO_HEADER_GS(PROTO_GS_DELEGATE_SELL_CMD);
    uint64_t                item_guid = 0;  //物品GUID
    uint32_t                item_value = 0; //物品单价
    uint32_t                item_unit = 1;  //物品单位数量
    uint8_t                 value_type = 0; //价格类型：0、金币；1、元宝
    uint64_t                role_id = 0;
    uint32_t                sessionid = 0;
};

struct ProtoGS_DelegateBuyCmd
{
    DEF_PROTO_HEADER_GS(PROTO_GS_DELEGATE_BUY_CMD);
    uint16_t                item_id = 0;    //物品模版ID
    uint32_t                item_count = 0; //物品数量
    uint32_t                item_value = 0; //物品单价
    uint32_t                item_unit = 1;  //物品单位数量
    uint8_t                 value_type = 0; //价格类型：0、金币；1、元宝
    uint64_t                role_id = 0;
    uint32_t                sessionid = 0;

};

struct ProtoGS_MarketSellCmd
{
    DEF_PROTO_HEADER_GS(PROTO_GS_MARKET_SELL_CMD);
    uint64_t        trade_id = 0; //交易号
    uint64_t        item_guid = 0;
    uint64_t        role_id = 0;
    uint32_t        sessionid = 0;
};

struct ProtoGS_MarketBuyCmd
{
    DEF_PROTO_HEADER_GS(PROTO_GS_MARKET_BUY_CMD);
    uint64_t        trade_id = 0; //交易号
    uint32_t        count = 0;
    uint64_t        role_id = 0;
    uint32_t        sessionid = 0;
};

struct ProtoGS_GMCommandReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_GM_COMMAND_REQ);

    int32_t                     sn              = 0;        //序列号
    char                        cmd[256]        = {0};      //GM 指令
    char                        param[65535]      = {0};      //指令参数
    uint64_t                    role_id         = 0;
    uint32_t                    sessionid       = 0;
    uint32_t                    token           = 0;
    void Clear()
    {
        memset(this, 0, sizeof(ProtoGS_GMCommandReq));
        REDEF_PROTO_HEADER_GS(PROTO_GS_GM_COMMAND_REQ);
    }
};

struct ProttoGS_GoldTake {
    DEF_PROTO_HEADER_GS(PROTO_GS_QUICK_GOLD_TAKE);
    int64_t                   gold; //gold
    uint64_t            role_id;
    uint32_t    sessionid = 0;
    ProttoGS_GoldTake() = default;
};


struct ProtoGS_GoldDeposit {
    DEF_PROTO_HEADER_GS(PROTO_GS_QUICK_GOLD_DEPOSIT);
    int64_t                   gold; //gold
    uint64_t            role_id;
    uint32_t    sessionid = 0;
    ProtoGS_GoldDeposit() = default;
};

struct ProtoGS_QuickBarSet {
    DEF_PROTO_HEADER_GS(PROTO_GS_QUICK_BAR_SET);

    unsigned char             type; //0=null 1=item 2=skill
    unsigned char             slot; //槽位
    unsigned short            id; //模板id
    uint64_t                  guid; //物品guid
    uint64_t            role_id;
    uint32_t    sessionid = 0;
    ProtoGS_QuickBarSet() {}
};

struct ProtoGS_TeamJoin {
    DEF_PROTO_HEADER_GS(PROTO_GS_TEAM_JOIN);

    char                      team_member[256] = {}; //申请加入队伍成员name
    uint32_t            token = 0;
    ProtoGS_TeamJoin() {}
};

struct ProtoGS_TeamJoinResponse {
    DEF_PROTO_HEADER_GS(PROTO_GS_TEAM_JOIN_RSP);

    char                      joiner[256] = {}; //申请加入者name
    unsigned char             accepted; //是否同意
    uint32_t            token = 0;
    ProtoGS_TeamJoinResponse() {}
};

struct ProtoGS_GetAroundTeamReq {
    DEF_PROTO_HEADER_GS(PROTO_GS_GET_ARROUND_TEAM_REQ);

    uint32_t            token = 0;
    ProtoGS_GetAroundTeamReq() = default;
};

struct ProtoGS_TeamKickEx {
    DEF_PROTO_HEADER_GS(PROTO_GS_TEAM_KICK_REQ);

    char                name[32] = {}; //被踢的name
    uint32_t            token = 0;
    ProtoGS_TeamKickEx() {}
};

struct ProtoGS_TeamLeaveEx {
    DEF_PROTO_HEADER_GS(PROTO_GS_TEAM_LEAVE_REQ);

    uint32_t            token = 0;
    ProtoGS_TeamLeaveEx() {}
};

struct ProtoGS_TeamInviteRsp {
    DEF_PROTO_HEADER_GS(PROTO_GS_TEAM_INVITE_RSP);

    char                      inviter_name[256] = {}; //邀请者name
    unsigned char             accepted; //是否同意
    uint32_t            token;
    ProtoGS_TeamInviteRsp() {}
};

struct ProtoGS_TeamInvite {
    DEF_PROTO_HEADER_GS(PROTO_GS_TEAM_INVITE);

    char                      invitee_name[256] = {}; //被邀请者name
    uint32_t            token;
    ProtoGS_TeamInvite() {}
};

struct ProtoGS_PlayerSwitchReq {
    DEF_PROTO_HEADER_GS(PROTO_GS_PLAYER_SWITCH_REQ);

    unsigned char             id; //id(player_switch_type)
    unsigned char             value; //开关值
    uint32_t            token;
    ProtoGS_PlayerSwitchReq() = default;
};

struct ProtoGS_SessionIDNtf {
    DEF_PROTO_HEADER_GS(PROTO_SESSION_LS2GS_NTF);

    uint32_t            sessionid = 0;
};

struct ProtoGS_PlayerReliveReq {
    DEF_PROTO_HEADER_GS(PROTO_GS_RELIVE_REQ);

    unsigned char             relive_type; //复活类型 1=原地复活 2=回城复活 3=副本入口复活
    uint32_t sessionid;
    uint32_t token;
    ProtoGS_PlayerReliveReq() = default;
};

struct ProtoGS_PlayerReliveAck {
    DEF_PROTO_HEADER_GS(PROTO_GS_RELIVE_ACK);

    unsigned char             relive_type; //复活类型 1=原地复活 2=回城复活 3=副本入口复活
    int                       error_code; //错误码 0=表示成功
    uint32_t sessionid;
    ProtoGS_PlayerReliveAck() = default;
};

struct ProtoGS_ReloginAck {

    DEF_PROTO_HEADER_GS(PROTO_GS_RELOGIN_ACK);

    int32_t                 errcode         = -1;               // 错误码
    char                    errmsg[256]     = {0};              // 错误描述

    uint64_t                player_guid     = 0;
    uint64_t                role_guid       = 0;

    char                    username[256]   = {0};
    char                    password[128]   = {0};

    uint32_t                token           = 0;
    char                    randkey[128]    = {0};              // 随机密钥

    uint32_t                cl2gs_sessid    = 0;
};

struct ProtoGS_ItemApply {
    DEF_PROTO_HEADER_GS(PROTO_GS_ITEM_APPLY);

    uint64_t                    item_guid   = 0;                //物品GUID
    uint32_t                    num         = 0;                //物品数量
    uint32_t                    sessid      = 0;
    uint32_t                    token       = 0;
    uint64_t                    role_guid   = 0;
};

struct ProtoGS_ItemPickUp{
    DEF_PROTO_HEADER_GS(PROTO_GS_ITEM_PICK_UP);

    uint32_t  sessid;
    uint32_t  token;
    ProtoGS_ItemPickUp() = default;
};

struct ProtoGS_ItemDrop {
    DEF_PROTO_HEADER_GS(PROTO_GS_ITEM_DROP);

    uint64_t            item_guid; //物品GUID
    uint32_t  sessid;
    uint32_t  token;
    ProtoGS_ItemDrop() = default;
};

struct ProtoGS_ItemArrange {
    DEF_PROTO_HEADER_GS(PROTO_GS_ITEM_ARRANGE);

    unsigned char             type; //0=背包 1=仓库 2=高级仓库
    uint32_t  sessid;
    uint32_t  token;
    ProtoGS_ItemArrange() = default;
};

struct ProtoGS_HeartBeatReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_HEART_BEAT_REQ);
};

struct ProtoGS_HeartBeatAck
{
    DEF_PROTO_HEADER_GS(PROTO_GS_HEART_BEAT_ACK);
};

struct ProtoGS_ExitGSReq        // GS -> SS
{
    DEF_PROTO_HEADER_GS(PROTO_GS_EXIT_GS_REQ);

    unsigned char             exittype{ 2 }; //退出类型 1=大退 2=小退
    uint32_t    sessionid{0};      //跟客户端的session id
    uint64_t    nrole_guid{0};      //跟客户端的session id
};

struct ProtoGS_ExitGSAck        // GS -> SS
{
    DEF_PROTO_HEADER_GS(PROTO_GS_EXIT_GS_ACK);

    unsigned char             exittype{ 2 }; //退出类型 1=大退 2=小退
    int                       errcode{ 0 }; //错误码
    char                      errmsg[256]; //错误描述   
    uint32_t    sessionid{ 0 };      //跟客户端的session id
    uint64_t    nrole_guid{0};
    ProtoGS_ExitGSAck()
    {
        memset(errmsg, 0, 256);
    }
};

struct ProtoGS_ConfigReq        // GS -> SS
{
    DEF_PROTO_HEADER_GS(PROTO_GS_CONFIG_REQ);
};

struct ProtoGS_ConfigAck        // SS -> GS
{
    DEF_PROTO_HEADER_GS(PROTO_GS_CONFIG_ACK);

    uint32_t    loginServIp;
    uint32_t    loginServPort;

    uint32_t    mapServIp;
    uint32_t    mapServPort;

    uint32_t    centerServIp;
    uint32_t    centerServPort;

    uint32_t    logServIp;
    uint32_t    logServPort;

    ProtoGS_ConfigAck() : loginServIp(0), loginServPort(0), mapServIp(0), mapServPort(0)
        , centerServIp(0), centerServPort(0), logServIp(0), logServPort(0)
    {}
};

struct ProtoGS_LoginReq         // GS -> LS
{
    DEF_PROTO_HEADER_GS(PROTO_GS_LOGIN_REQ);

    uint32_t                    clsessid            = 0;            // 跟客户端的session id
    char                        username[256]       = {0};          // 账号名
    char                        password[128]       = {0};          // 密码密文
    uint32_t                    ip                  = 0;            // 登陆ip地址
    char                        hwid[256]           = {0};          // 硬件码
};

struct ProtoGS_LoginAck         // LS -> GS
{
    DEF_PROTO_HEADER_GS(PROTO_GS_LOGIN_ACK);

    uint32_t                    clsessid            = 0;
    int32_t                     errcode             = 0;            // 错误码
    char                        errmsg[256]         = {0};          // 错误描述

    char                        username[256]       = {0};
    uint64_t                    userid              = 0;

    uint32_t                    token               = 0;
    char                        randkey[128]        = {0};          // 随机密钥
};

struct ProtoGS_ThirdLoginReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_THIRD_LOGIN_REQ);

    uint32_t                    sessionid           = 0;            // 跟客户端的session id

    char                        channel[16]         = {0};          // 渠道信息
    uint32_t                    gameid              = 0;            // 游戏id
    char                        token[256]          = {0};          // 验证token

    char                        user_name[256]      = {0};          // 用户名
    uint32_t                    login_ip            = 0;            // 登录ip
    char                        hwid[256]           = {0};          // 硬件码
};

struct ProtoGS_LogoutReq         // GS -> LS
{
    DEF_PROTO_HEADER_GS(PROTO_GS_LOGOUT_REQ);

    uint32_t                    sessionid           = 0;
    uint32_t                    token               = 0;
    uint8_t                     info                = 0;           //登出类型
};

struct ProtoGS_ReloginReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_RELOGIN_REQ);

    uint64_t                    player_guid         = 0;            // 账号id
    uint64_t                    role_guid           = 0;            // 角色id
    char                        randkey[128]        = {0};          // 会话密钥
    uint32_t                    cl2gs_sessid        = 0;
    uint32_t                    ip                  = 0;     
    char                        hwid[256]           = { 0 };
};

struct ProtoGS_EnterMapReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_ENTER_MAP_REQ);
    uint32_t    sessionid;    //CLI <--->GS
    char        username[256];
    ProtoGS_EnterMapReq() : sessionid(0)
    {
        memset(username, 0, _countof(username));
    }

};

struct ProtoGS_EnterMapAck      // CS -> GS
{
    DEF_PROTO_HEADER_GS(PROTO_GS_ENTER_MAP_ACK);
    uint32_t    sessionid;
    char        username[256];
    uint16_t    id;//map id
    ProtoGS_EnterMapAck() : sessionid(0), id(0)
    {
        memset(username, 0, _countof(username));
    }
};

struct ProtoGS_GetRoleListReq       // GS -> CS
{
    DEF_PROTO_HEADER_GS(PROTO_GS_GET_ROLE_LIST_REQ);

    uint32_t    sessionid;
    uint32_t    token;
    uint64_t    playerid;

    ProtoGS_GetRoleListReq() : sessionid(0), token(0), playerid(0)
    {}
};

struct ProtoGS_GetRoleListAck       // CS -> GS
{
    DEF_PROTO_HEADER_GS(PROTO_GS_GET_ROLE_LIST_ACK);

    uint32_t                    sessionid;
    uint32_t                    token;
    uint64_t                    playerid;

    int32_t                     errcode;                //错误码
    char                        errmsg[256];            //错误描述
    uint8_t                     rolenum;                //角色列表中的角色数量
    uint64_t                    last_role;              //上次选择角色
    ROLE_BRIEF_INFO             rolelist[10];           //角色简要信息列表
    uint8_t                     needCode = 0;           //创建角色是否需要校验码,0不需要,1需要

    ProtoGS_GetRoleListAck() : sessionid(0), token(0), playerid(0), errcode(-1), rolenum(0), last_role(0), needCode(0)
    {
        memset(errmsg, 0, sizeof(errmsg));
        memset(rolelist, 0, sizeof(rolelist));
    }
};
static ProtoGS_GetRoleListAck gProtoGS_GetRoleListAck;

struct ProtoGS_EnterGSReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_ENTER_GS_REQ);

    uint32_t                    sessionid       = 0;
    uint32_t                    token           = 0;
    uint64_t                    playerid        = 0;

    uint32_t                    MS2GSSessionID = 0;

    char                        entertype       = -1;   //进入类型 0=上线 1=跳服
    char                        fangchenmi      = -1;   //是否防沉迷用户 1：是 0：否
    char                        clienttype      = -1;   //客户端类型 0=客户端 1=页游 2=手游

    ROLE_BRIEF_INFO             roleBriefInfo;

    ProtoGS_EnterGSReq()
    {
        memset(&roleBriefInfo, 0, sizeof(roleBriefInfo));
    }
};

struct ProtoGS_EnterGSNTF
{
    DEF_PROTO_HEADER_GS(PROTO_GS_ENTER_GS_NTF);
    uint64_t                  mapcode; //地图流水号
    char                      logic[256]; //地图逻辑格文件
    unsigned short            view_x; //地图视野范围X
    unsigned short            view_y; //地图视野范围Y
    unsigned short            width; //宽
    unsigned short            height; //高
    uint32_t    sessionid;    //CLI <--->GS
    uint32_t    token;
    ProtoGS_EnterGSNTF() : sessionid(0) {}

};

struct ProtoGS_CreateRoleReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_CREATE_ROLE_REQ);

    uint32_t                    sessionid;
    uint32_t                    token;
    uint64_t                    playerid;

    ROLE_BRIEF_INFO             createrole;     //新建角色的基础信息

    uint8_t                     needCode = 0;           //是否需要校验码,0不需要,1数字校验码
    uint64_t                    digCode = 0;            //数字校验码
    ProtoGS_CreateRoleReq() : sessionid(0), token(0), playerid(0), needCode(0), digCode(0)
    {
        memset(&createrole, 0, sizeof(createrole));
    }
};

struct ProtoGS_CreateRoleAck
{
    DEF_PROTO_HEADER_GS(PROTO_GS_CREATE_ROLE_ACK);

    uint32_t                    sessionid;
    uint32_t                    token;
    uint64_t                    playerid;

    int32_t                     errcode;        //错误码
    char                        errmsg[256];    //错误描述
    ROLE_BRIEF_INFO             newrole;        //角色简要信息列表

    ProtoGS_CreateRoleAck() : sessionid(0), token(0), playerid(0), errcode(-1)
    {
        memset(errmsg, 0, sizeof(errmsg));
        memset(&newrole, 0, sizeof(newrole));
    }
};

struct ProtoGS_DeleteRoleReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_DELETE_ROLE_REQ);

    uint32_t                    sessionid;
    uint32_t                    token;
    uint64_t                    playerid;
    uint64_t                    roleid;
    int32_t                     status;
    ProtoGS_DeleteRoleReq() : sessionid(0), token(0), playerid(0), roleid(0), status(2)
    {}
};
struct ProtoGS_RestoreRoleReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_RESTORE_ROLE_REQ);

    uint32_t                    sessionid;
    uint32_t                    token;
    uint64_t                    playerid;
    uint64_t                    roleid;
    int32_t                     status;
    ProtoGS_RestoreRoleReq() : sessionid(0), token(0), playerid(0), roleid(0), status(1)
    {}
};

struct ProtoGS_DeleteRoleAck
{
    DEF_PROTO_HEADER_GS(PROTO_GS_DELETE_ROLE_ACK);

    uint32_t                    sessionid;
    uint32_t                    token;
    uint64_t                    playerid;
    uint64_t                    roleid;
    int                         errcode;        //错误码
    char                        errmsg[256];    //错误描述
    int32_t                     status;

    ProtoGS_DeleteRoleAck() : sessionid(0), token(0), playerid(0), roleid(0), errcode(-1), status(-1)
    {
        memset(errmsg, 0, sizeof(errmsg));
    }
};

struct ProtoGS_RestoreRoleAck
{
    DEF_PROTO_HEADER_GS(PROTO_GS_RESTORE_ROLE_ACK);

    uint32_t                    sessionid;
    uint32_t                    token;
    uint64_t                    playerid;
    uint64_t                    roleid;
    int                         errcode;        //错误码
    char                        errmsg[256];    //错误描述
    ROLE_BRIEF_INFO             role;           //角色简要信息

    ProtoGS_RestoreRoleAck() : sessionid(0), token(0), playerid(0), roleid(0), errcode(-1)
    {
        memset(errmsg, 0, sizeof(errmsg));
    }
};

struct ProtoGS_MoveReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_MOVE_REQ);

    uint32_t                    clsessid        = 0;
    uint64_t                    role_guid       = 0;        //移动角色的guid，玩家或分身
    uint8_t                     type            = 0;        //移动类型 0=走 1=跑
    uint16_t                    dst_x           = 0;        //目标点x
    uint16_t                    dst_y           = 0;        //目标点y
    uint32_t                    idx             = 0;        //客户端序列号
    uint64_t                    movetime        = 0;
};

struct ProtoGS_MoveAck
{
    DEF_PROTO_HEADER_GS(PROTO_GS_MOVE_ACK);

    uint32_t                    clsessid        = 0;
    uint64_t                    role_guid       = 0;
    uint8_t                     ret             = 1;        //0=成功, 1=表示失败
    uint8_t                     type            = 0;        //移动类型 0=走 1=跑
    uint16_t                    dst_x           = 0;        //移动前的点x
    uint16_t                    dst_y           = 0;        //移动前的点y
    uint32_t                    idx             = 0;        //客户端序列号
};

struct ProtoGS_TurnReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_TURN_REQ);

    uint64_t                    role_guid       = 0;
    uint8_t                     dir             = 0;        //角色现在的方向
};

struct ProtoGS_TurnNtf
{
    DEF_PROTO_HEADER_GS(PROTO_GS_TURN_NTF);

    uint32_t                    sessionid;
    uint32_t                    token;
    uint64_t                    playerid;

    uint64_t                    guid;
    uint8_t                     dir;        //角色现在的方向

    ProtoGS_TurnNtf() : sessionid(0), token(0), playerid(0), guid(0), dir(0)
    {}
};

struct ProtoGS_SpellTarget
{
    DEF_PROTO_HEADER_GS(PROTO_GS_SPELL_TARGET);

    uint64_t                    role_guid       = 0;
    uint16_t                    id              = 0;            //技能id
    uint64_t                    target          = 0;            //目标, 可能是player/monster/npc's guid
    uint16_t                    idx             = 0;            //时间戳，单位ms
};

struct ProtoGS_SpellGrid
{
    DEF_PROTO_HEADER_GS(PROTO_GS_SPELL_GRID);

    uint64_t                    role_guid       = 0;
    uint16_t                    id              = 0;            // 技能id
    uint16_t                    target_x        = 0;            // 目标逻辑格的X坐标
    uint16_t                    target_y        = 0;            // 目标逻辑格的X坐标
    uint16_t                    idx             = 0;            // 时间戳，单位ms
    uint64_t                    ref_target      = 0;            // 参照目标guid
    uint8_t                     extra           = 0;            // 普攻时用来表示是否使用刺杀特效
};

struct ProtoGS_SpellAck
{
    DEF_PROTO_HEADER_GS(PROTO_GS_SPELL_ACK);

    uint32_t                    sessionid       = 0;
    uint64_t                    role_guid       = 0;

    uint16_t                    id              = 0;            //技能id
    int32_t                     ecode           = -1;           //错误码
    char                        detail[256]     = {0};          //错误描述
    uint16_t                    idx             = 0;            //~
};

struct ProtoGS_SkillSwitch
{
    DEF_PROTO_HEADER_GS(PROTO_GS_SKILL_SWITCH);

    uint32_t                    token           = 0;
    uint32_t                    clientSessionID = 0;

    uint16_t                    id              = 0;
    uint8_t                     active          = 0;
};

struct ProtoGS_SkillSwitchAck
{
    DEF_PROTO_HEADER_GS(PROTO_GS_SKILL_SWITCH_ACK);

    uint32_t                    token           = 0;
    uint32_t                    clientSessionID = 0;

    uint16_t                    id              = 0;
    uint8_t                     active          = 0;
};

struct ProtoGS_CreatePlayerReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_CREATE_PLAYER_REQ);

    uint32_t                    token           = 0;
    uint32_t                    clientSessionID = 0;
    uint64_t                    playerid        = 0;
    uint64_t                    role_id         = 0;
    uint16_t                    mapid = 0;
    ROLE_BRIEF_INFO             roleBriefInfo;

    ProtoGS_CreatePlayerReq()
    {
        memset(&roleBriefInfo, 0, sizeof(roleBriefInfo));
    }
};


struct ProtoGS_KickRoleNtf {
    DEF_PROTO_HEADER_GS(PROTO_GS_KICK_ROLE_NTF);

    uint32_t                  sessionid;
    uint64_t                  roleguid; //被踢除角色的GUID
    int                       errcode; //错误码
    char                      errmsg[256]; //错误描述
    ProtoGS_KickRoleNtf() = default;
};


struct ProtoGS_SaveKeyNtf
{
    DEF_PROTO_HEADER_GS(PROTO_GS_SAVE_KEY_NTF);

    char        key[128];
    uint32_t    token;
};

struct ProtoGS_ItemMove {
    DEF_PROTO_HEADER_GS(PROTO_GS_ITEM_MOVE);

    uint64_t                  item_guid; //物品GUID
    unsigned short            dest_site; //物品的目标位置
    uint32_t    token;
    ProtoGS_ItemMove() = default;
};

struct ProtoGS_ItemSplit {
    DEF_PROTO_HEADER_GS(PROTO_GS_ITEM_SPLIT);

    uint64_t                item_guid; //物品GUID
    uint16_t                item_amount;    //物品数量
    uint16_t                dest_site;      //物品的目标位置
    uint32_t                token;
    ProtoGS_ItemSplit() = default;
};


struct ProtoGS_RunServScriptReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_RUN_SERV_SCRIPT_REQ);

    uint32_t                    sessionid           = 0;
    uint32_t                    token               = 0;
    uint64_t                    playerid            = 0;

    uint32_t                    form_count          = 0;            //表单计数
    char                        script_name[256];                   //脚本名称
    char                        function_name[256];                 //函数名称
    uint16_t                    num                 = 0;            //参数个数
    PARAM_INFO2                 info[100];                          //参数信息

    ProtoGS_RunServScriptReq()
    {
        memset(script_name, 0, sizeof(script_name));
        memset(function_name, 0, sizeof(function_name));
        memset(info, 0, sizeof(info));
    }
};

struct ProtoGS_RunServScriptAck
{
    DEF_PROTO_HEADER_GS(PROTO_GS_RUN_SERV_SCRIPT_ACK);

    uint32_t                    sessionid           = 0;
    uint32_t                    token               = 0;
    uint64_t                    playerid            = 0;

    char                        script_name[256];                   //脚本名称
    char                        result[256];                        //反馈

    ProtoGS_RunServScriptAck()
    {
        memset(script_name, 0, sizeof(script_name));
        memset(result, 0, sizeof(result));
    }
};

struct ProtoGS_RelationChatReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_RELATION_CHAT_REQ);

    uint32_t                    token               = 0;

    uint8_t                     type                = 0;            // 1：当前 2：队伍 3：公会 4：世界 5：小喇叭 9: 阵营 12：全服
    char                        message[256];                       // 消息内容

    ProtoGS_RelationChatReq()
    {
        memset(message, 0, sizeof(message));
    }
};

struct ProtoGS_RelationChatAck
{
    DEF_PROTO_HEADER_GS(PROTO_GS_RELATION_CHAT_ACK);

    uint32_t                    sessionid           = 0;

    uint8_t                     type                = 0;            // 1：当前 2：队伍 3：公会 4：世界 5：小喇叭 9: 阵营 12：全服
    uint8_t   scroll_times = 0;
    char   font_color[32];
    char   background_color[32];
    CHAT_MSG                    chat_message;                       // 角色名为源角色的名字

    ProtoGS_RelationChatAck()
    {
        memset(&chat_message, 0, sizeof(chat_message));
        memset(&font_color, 0, sizeof(font_color));
        memset(&background_color, 0, sizeof(background_color));
    }
};

struct ProtoGS_RelationChatNtf
{
    DEF_PROTO_HEADER_GS(PROTO_GS_RELATION_CHAT_NTF);
    RELATION_CHAT_NTF info;
    uint32_t    sessionid           = 0;
    void Clear()
    {
        memset(this, 0, sizeof(ProtoGS_RelationChatNtf));
        REDEF_PROTO_HEADER_GS(PROTO_GS_RELATION_CHAT_NTF);
    }
};

struct ProtoGS_PrivateChatNtf
{
    DEF_PROTO_HEADER_GS(PROTO_GS_PRIVATE_CHAT_NTF);

    uint32_t                    sessionid           = 0;
    uint32_t                    token               = 0;

    uint8_t                     type                = 0;            // 6：私聊 5：点对点聊天
    CHAT_MSG                    chat_message;                       // 客户端发送时：角色名为目标角色的名字 客户端接收时：角色名为源角色的名字

    ProtoGS_PrivateChatNtf()
    {
        memset(&chat_message, 0, sizeof(chat_message));
    }
};

struct ProtoGS_SpeakerMsgReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_SPEAKER_MSG_REQ);

    uint32_t                    token               = 0;

    char                        msg[256];                           // 消息内容

    ProtoGS_SpeakerMsgReq()
    {
        memset(msg, 0, sizeof(msg));
    }
};

struct ProtoGS_SpeakerMsgNtf
{
    DEF_PROTO_HEADER_GS(PROTO_GS_SPEAKER_MSG_NTF);

    uint32_t                    sessionid           = 0;

    char                        sender[256];                        // 发送者的名字
    char                        msg[256];                           // 消息内容

    ProtoGS_SpeakerMsgNtf()
    {
        memset(sender, 0, sizeof(sender));
        memset(msg, 0, sizeof(msg));
    }
};

struct ProtoGS_TradeMallListReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_TRADE_MALL_LIST_REQ);
    uint32_t                    sessionid = 0;
    uint32_t                    token;
    unsigned char               page_id = 0; //商品的分页
    ProtoGS_TradeMallListReq() = default;
};

struct ProtoGS_TradeMallListAck 
{
    DEF_PROTO_HEADER_GS(PROTO_GS_TRADE_MALL_LIST_ACK);
    uint32_t                    sessionid = 0;
    unsigned char               page_id = 0; //商品的分页
    unsigned char               item_count = 0; //商品数量
    MALL_ITEM_INFO              item_list[250]; //商品信息列表
    ProtoGS_TradeMallListAck()
    {
        memset(item_list, 0, sizeof(item_list));
    }
};

struct ProtoGS_TradeMallBuy {
    DEF_PROTO_HEADER_GS(PROTO_GS_TRADE_MALL_BUY);
    uint32_t                    sessionid = 0;
    uint32_t                    token = 0;
    unsigned int                item_index = 0; //item_index
    unsigned short              item_amount = 0; //物品数量
    ProtoGS_TradeMallBuy() = default;
};

struct ProtoGS_NpcSelect
{
    DEF_PROTO_HEADER_GS(PROTO_GS_NPC_SELECT);

    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;

    uint64_t                    npc_guid            = 0;
};

struct ProtoGS_NpcTalkReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_NPC_TALK_REQ);

    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;

    uint64_t                    npc_guid            = 0;
    char                        func[256]           = {0};
};

struct ProtoGS_TradeNpcBuy
{
    DEF_PROTO_HEADER_GS(PROTO_GS_TRADE_NPC_BUY);

    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;

    uint16_t                    shop_id             = 0;            // shop_index
    uint16_t                    item_index          = 0;            // item_index
    uint16_t                    item_amount         = 0;            // 物品数量
    uint8_t                     is_bind             = 0;            // 是否使用绑定金币, 1、使用；0、不使用
};

struct ProtoGS_AtkModeReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_ATK_MODE_REQ);

    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;

    uint8_t                     atk_mode            = 0;
};

struct ProtoGS_QuestQueryCanAccept
{
    DEF_PROTO_HEADER_GS(PROTO_GS_QUEST_QUERY_CAN_ACCEPT);

    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;
};

struct ProtoGS_QuestQueryCanAcceptNtf
{
    DEF_PROTO_HEADER_GS(PROTO_GS_QUEST_QUERY_CAN_ACCEPT_NTF);

    uint32_t                    sessionid           = 0;

    uint16_t                    num                 = 0;
    uint16_t                    quests[500]         = {0};
};

struct ProtoGS_QuestAccept
{
    DEF_PROTO_HEADER_GS(PROTO_GS_QUEST_ACCEPT);

    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;

    uint16_t                    quest_id            = 0;            // 任务模板id
};

struct ProtoGS_QuestAddNtf
{
    DEF_PROTO_HEADER_GS(PROTO_GS_QUEST_ADD_NTF);

    uint32_t                    sessionid           = 0;

    uint16_t                    quest_id            = 0;            // 任务模板id
    char                        quest_name[256]     = {0};          // 任务的名称
    uint8_t                     quest_type          = 0;            // 任务的类型, 显示用
    uint16_t                    group_huntings_len  = 0;            // 组打怪计数
    QUEST_HUNTING_INFO          group_huntings[20];                 // 组打怪数据
    uint16_t                    huntings_len        = 0;            // 打怪计数
    QUEST_HUNTING_INFO          huntings[20];                       // 打怪数据
    uint16_t                    huntlevels_len      = 0;            // 打等级怪计数
    QUEST_HUNTLEVEL_INFO        huntlevels[20];                     // 打等级怪数据
    uint16_t                    group_items_len     = 0;            // 组物品收集
    QUEST_ITEM_INFO             group_items[20];                    // 组收集数据
    uint16_t                    collect_items_len   = 0;            // 物品收集
    QUEST_ITEM_INFO             collect_items[20];                  // 收集数据
    uint16_t                    apply_items_len     = 0;            // 物品使用
    QUEST_ITEM_INFO             apply_items[20];                    // 收集使用
    uint16_t                    npcs_len            = 0;            // Npc
    QUEST_NPC_INFO              npcs[20];                           // npc访问
    uint8_t                     track_enabled       = 0;            // 是否开启追踪
    uint32_t                    life                = 0;            // 剩余时间
    char                        progressing[256]    = {0};          // 任务进行时追踪文本
    char                        accomplishing[256]  = {0};          // 任务完成时追踪文本

    ProtoGS_QuestAddNtf()
    {
        memset(group_huntings, 0, sizeof(group_huntings));
        memset(huntings, 0, sizeof(huntings));
        memset(huntlevels, 0, sizeof(huntlevels));
        memset(group_items, 0, sizeof(group_items));
        memset(collect_items, 0, sizeof(collect_items));
        memset(apply_items, 0, sizeof(apply_items));
        memset(npcs, 0, sizeof(npcs));
    }
};

struct ProtoGS_QuestDrop
{
    DEF_PROTO_HEADER_GS(PROTO_GS_QUEST_DROP);

    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;

    uint16_t                    quest_id            = 0;
};

struct ProtoGS_QuestAccomplish
{
    DEF_PROTO_HEADER_GS(PROTO_GS_QUEST_ACCOMPLISH);

    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;

    uint16_t                    quest_id            = 0;
    uint16_t                    select_index        = 0;            // 玩家选择项索引
};

struct ProtoGS_Teamoperation {
    DEF_PROTO_HEADER_GS(PROTO_GS_TEAM_OPERATION);
    uint32_t                    token = 0;
    unsigned char             operation = 0; //1 创建 2解散 3获取周围队伍 4转移队长
    char                      content[256]; //操作人
    ProtoGS_Teamoperation()
    {
        memset(content, 0, sizeof(content));
    }
};

struct ProtoGS_GetFamilyInfoReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_GET_FAMILY_INFO_REQ);

    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;

    uint32_t                    reqType             = 0;            // 查询内容；1、行会公告；2、行会消息；4、行会封号；8、行会成员；16、敌对行会；32、联盟行会；64、入会申请列表；128、行会基本信息；256、可以加入的行会；512、在线成员；2048、所有行会成员；
    uint32_t                    start_index         = 0;            // 开始的index
    uint32_t                    req_count           = 0;            // 请求的数量
    uint32_t                    req_group           = 0;            // 分组信息
    char                        info[32]            = {0};          // 附加信息：如模糊查找的玩家名
};

struct ProtoGS_PlayerQuery
{
    DEF_PROTO_HEADER_GS(PROTO_GS_PLAYER_QUERY);

    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;

    char                        player_name[128]    = {0};          // 玩家名称
};

struct ProtoGS_TopListReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_TOPLIST_REQ);

    unsigned char             type = 0; //排行榜类型，详见enum sort_type
    uint32_t                  sessionid = 0;
};

struct ProtoGS_TopListAck
{
    DEF_PROTO_HEADER_GS(PROTO_GS_TOPLIST_ACK);

    unsigned char             type = 0; //排行榜类型，详见enum sort_type
    unsigned int              time = 0; //下次刷新时间
    unsigned char             num = 0; //上榜数量
    uint32_t                  sessionid = 0;    // session
    TOPLIST_INFO              info[100]; //排行榜内容
    ProtoGS_TopListAck() {
        memset(info, 0, sizeof(info));
    }
};

struct ProtoGS_FamilyJoinReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_FAMILY_JOIN_REQ);

    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;

    uint64_t                    guid                = 0;            // 行会id
};

struct ProtoGS_CancelFamilyJoinReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_CANCEL_FAMILY_JOIN_REQ);

    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;

    uint64_t                    guid                = 0;            // 行会id
};

struct ProtoGS_FamilyJoinAck
{
    DEF_PROTO_HEADER_GS(PROTO_GS_FAMILY_JOIN_ACK);

    uint64_t                    leader_guid         = 0;            // 会长GUID
    uint64_t                    player_guid         = 0;            // 玩家的guid
    uint8_t                     is_allow            = 0;            // 是否允许入会：1、允许，0、不允许
};

struct ProtoGS_FamilyTitleAwardReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_FAMILY_TITLE_AWARD_REQ);

    uint64_t                    leader_guid         = 0;
    uint64_t                    player_guid         = 0;            // 玩家ID
    uint8_t                     title_id            = 0;            // 封号id(0-(MAX_TITLE_NUM - 1))
};

struct ProtoGS_FamilyExpellReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_FAMILY_EXPELL_REQ);

    uint64_t                    kicker_guid         = 0;
    uint64_t                    player_guid         = 0;            // 玩家ID
};

struct ProtoGS_FamilyNoticeEditReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_FAMILY_NOTICE_EDIT_REQ);

    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;

    uint32_t                    notice_len          = 0;            // 公告长度
    char                        notice[1280]        = {0};          // 行会公告
};

struct ProtoGS_FriendAddReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_FRIEND_ADD_REQ);

    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;

    char                        player_name[32]     = {0};          // 添加对象的名字
};

struct ProtoGS_FamilyLeaveOrLastMsgReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_FAMILY_LEAVE_OR_LAST_MSG_REQ);

    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;

    char                        byebye[256]         = {0};          // 临别赠言
};

struct ProtoGS_FamilyDestroyReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_FAMILY_DESTROY_REQ);

    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;
};

struct ProtoGS_UpdateOnlineState
{
    DEF_PROTO_HEADER_GS(PROTO_GS_UPDATE_ONLINE_STATE);

    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;
    uint8_t                     state               = 0;
};

struct ProtoGS_SyncSessionID
{
    DEF_PROTO_HEADER_GS(PROTO_GS_SYNC_SESSION_ID);

    uint64_t                    role_guid           = 0;
    uint32_t                    token               = 0;
    uint32_t                    cl2gs_sessid        = 0;
};

struct ProtoGS_JumpMapReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_JUMP_MAP_REQ);

    uint64_t                    roleid              = 0;
    uint32_t                    token               = 0;

    uint16_t                    dst_x               = 0;            // 目标点x
    uint16_t                    dst_y               = 0;            // 目标点y
    uint8_t                     type                = 0;            // 见 jump_map_type
};

struct ProtoGS_GetNpcPosReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_GET_NPC_POS_REQ);
    uint64_t  roleid    = 0;
    char      name[256] = {0};

};

struct ProtoGS_GetNpcPosAck
{
    DEF_PROTO_HEADER_GS(PROTO_GS_GET_NPC_POS_ACK);
    uint16_t  posx      = 0;
    uint16_t  posy      = 0;
    uint8_t   result    = 0;
    uint32_t  sessionid = 0;
};

struct ProtoGS_StartDigReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_START_DIG_REQ);

    uint64_t                    role_guid           = 0;            // 角色GUID
    uint64_t                    treasure_guid       = 0;            // 宝物GUID
};

struct ProtoGS_RangePickup
{
    DEF_PROTO_HEADER_GS(PROTO_GS_RANGE_PICKUP);

    uint64_t                    role_guid           = 0;
    uint8_t                     posnum              = 0;
    Point                       pos[AUTO_PICKUP_MAXPOS];
};

struct ProtoGS_SyncClientBaseSetting
{
    DEF_PROTO_HEADER_GS(PROTO_GS_SYNC_CLIENT_BASE_SETTING);

    uint64_t                    role_guid = 0;
    uint16_t                    type = 0;
    int32_t                     value = 0;
};

struct ProtoGS_VerifyBuyItemInfoReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_VERIFY_BUY_ITEM_INFO_REQ);

    uint64_t                    role_guid           = 0;
    uint32_t                    item_id             = 0;            // 购买的商品ID
    uint8_t                     item_count          = 0;            // 购买的商品数量
    uint32_t                    item_price          = 0;            // 购买的商品单价（分）
};

struct ProtoGS_ItemRefreshReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_ITEM_REFRESH_REQ);

    uint64_t                    role_guid           = 0;
    uint32_t                    token               = 0;
};
struct ProtoGS_ItemTip
{
    DEF_PROTO_HEADER_GS(PROTO_GS_ITEM_TIP);
    uint64_t                    guid = 0;
    uint64_t                    owner_guid = 0;
    uint64_t                    item_guid  = 0;
};

struct ProtoGS_ItemTipNtf
{
    DEF_PROTO_HEADER_GS(PROTO_GS_ITEM_TIP_NTF);
    uint64_t guid;
    uint32_t sessionid;
    ITEM_INFO infos;
    void Clear() {
        memset(this, 0, sizeof(ProtoGS_ItemTipNtf));
        REDEF_PROTO_HEADER_GS(PROTO_GS_ITEM_TIP_NTF);
    }
};
static ProtoGS_ItemTipNtf gProtoGS_ItemTipNtf;

struct ProtoGS_CustMsgNtf
{
    DEF_PROTO_HEADER_GS(PROTO_GS_CUST_MSG_NTF);
    CUST_MSG_NTF info;
    uint32_t sessionid = 0;
    void Clear() {
        memset(this, 0, sizeof(ProtoGS_CustMsgNtf));
        REDEF_PROTO_HEADER_GS(PROTO_GS_CUST_MSG_NTF);
    }
};

struct ProtoGS_SetAutoModeAck
{
    DEF_PROTO_HEADER_GS(PROTO_GS_SET_AUTO_MODE_ACK);

    uint64_t                    role_guid           = 0;
    uint8_t                     enable              = 0;
};

struct ProtoGS_RoleCustVarReq
{
    DEF_PROTO_HEADER_GS(PROTO_GS_ROLE_CUST_VAR_REQ);

    uint64_t                    role_guid = 0;
    uint32_t                    sessionid = 0;
};

class ProtoGS
{
public:
    ProtoGS();
    ~ProtoGS();

    static inline uint16_t GetModuleID(void) { return MODULE_TYPE_GS; }
    static inline uint16_t GetProtocolNum(void) { return PROTO_GS_MAX; }

    int BuildProtocol(void* pHost, char* pNet, int iNetSize);
    int HandleProtocol(void* pHost, char* pNet, int iNetSize);

private:
    EnCodeFunc m_EnCodeFuncArray[PROTO_GS_MAX];
    DeCodeFunc m_DeCodeFuncArray[PROTO_GS_MAX];
};
