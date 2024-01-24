#pragma once

#include "ProtoDef.h"


#define DEF_PROTO_HEADER_CLIENT2(protoid) uint16_t moduleid = MODULE_TYPE_CLIENT2; uint16_t protocolid = protoid
#define REDEF_PROTO_HEADER_CLIENT2(protoid) moduleid = MODULE_TYPE_CLIENT2; protocolid = protoid

enum
{
    PROTO_CLIENT2_PRIVATE_CHAT_NTF                  = 1,
    PROTO_CLIENT2_RELATION_CHAT_REQ                 = 2,
    PROTO_CLIENT2_RELATION_CHAT_ACK                 = 3,        // 回给请求方
    PROTO_CLIENT2_SYS_MSG_NTF                       = 4,
    PROTO_CLIENT2_TEAM_INVITE                       = 5,
    PROTO_CLIENT2_TEAM_INVITE_NTF                   = 6,
    PROTO_CLIENT2_TEAM_INVITE_RSP                   = 7,
    PROTO_CLIENT2_MISS_TEAM_NTF                     = 10,
    PROTO_CLIENT2_TEAM_LEADER_NTF                   = 11,
    PROTO_CLIENT2_TEAM_NTF                          = 12,
    PROTO_CLIENT2_FRIEND_ADD_REQ                    = 13,
    PROTO_CLIENT2_FAMILY_JOIN_REQ                   = 21,
    PROTO_CLIENT2_FAMILY_JOIN_ACK                   = 22,
    PROTO_CLIENT2_FAMILY_INVITE_REQ                 = 23,
    PROTO_CLIENT2_FAMILY_INVITE_VERIFY              = 24,
    PROTO_CLIENT2_FAMILY_INVITE_ACK                 = 25,
    PROTO_CLIENT2_GET_FAMILY_INFO_REQ               = 26,
    PROTO_CLIENT2_FAMILY_NOTICE_ACK                 = 27,
    PROTO_CLIENT2_FAMILY_MSG_ACK                    = 28,
    PROTO_CLIENT2_FAMILY_TITLES_ACK                 = 29,
    PROTO_CLIENT2_FAMILY_MEMBERS_ACK                = 30,
    PROTO_CLIENT2_FAMILY_ENEMY_ACK                  = 31,
    PROTO_CLIENT2_FAMILY_ALLY_ACK                   = 32,
    PROTO_CLIENT2_FAMILY_JOIN_LIST_ACK              = 33,
    PROTO_CLIENT2_FAMILY_TITLE_MODIFY_REQ           = 34,
    PROTO_CLIENT2_FAMILY_TITLE_AWARD_REQ            = 35,
    PROTO_CLIENT2_FAMILY_LEAVE_OR_LAST_MSG_REQ      = 36,
    PROTO_CLIENT2_FAMILY_EXPELL_REQ                 = 37,
    PROTO_CLIENT2_FAMILY_LEAVE_NTF                  = 38,
    PROTO_CLIENT2_FAMILY_DESTROY_REQ                = 39,
    PROTO_CLIENT2_FAMILY_ADD_ALLY_ENEMY_REQ         = 40,
    PROTO_CLIENT2_FAMILY_ADD_ALLY_VERIFY            = 41,
    PROTO_CLIENT2_FAMILY_ADD_ALLY_ACK               = 42,
    PROTO_CLIENT2_FAMILY_DEL_ALLY_ENEMY_REQ         = 43,
    PROTO_CLIENT2_FAMILY_NOTICE_EDIT_REQ            = 44,
    PROTO_CLIENT2_FAMILY_NAME_INPUT_REQ             = 45,
    PROTO_CLIENT2_FAMILY_NAME_INPUT_ACK             = 46,
    PROTO_CLIENT2_FAMILY_LIST_NTF_ACK               = 47,
    PROTO_CLIENT2_FAMILY_INFO_NTF                   = 48,
    PROTO_CLIENT2_FAMILY_BASE_INFO_ACK              = 49,
    PROTO_CLIENT2_TOPLIST_REQ                       = 50,
    PROTO_CLIENT2_TOPLIST_ACK                       = 51,   
	PROTO_CLIENT2_MAIL_LIST_REQ                     = 52,
    PROTO_CLIENT2_MAIL_LIST_ACK                     = 53,
    PROTO_CLIENT2_MAIL_OPEN_REQ                     = 54,
    PROTO_CLIENT2_MAIL_OPEN_ACK                     = 55,
    PROTO_CLIENT2_MAIL_ATTACHMENT_GET_REQ           = 56,
    PROTO_CLIENT2_MAIL_ATTACHMENT_GET_ACK           = 57,
    PROTO_CLIENT2_MAIL_DEL_REQ                      = 58,
    PROTO_CLIENT2_MAIL_DEL_ACK                      = 59,
    PROTO_CLIENT2_MAIL_SEND_REQ                     = 60,
    PROTO_CLIENT2_MAIL_SEND_ACK                     = 61,    
	PROTO_CLIENT2_SPEAKER_MSG_REQ                   = 62,
    PROTO_CLIENT2_SPEAKER_MSG_NTF                   = 63,
    PROTO_CLIENT2_NEW_MAIL_NTF                      = 64,
    PROTO_CLIENT2_TEAM_OPERATION                    = 65,
    PROTO_CLIENT2_TEAM_JOIN                         = 66,
    PROTO_CLIENT2_TEAM_JOIN_NTF                     = 67,
    PROTO_CLIENT2_TEAM_JOIN_RSP                     = 68,
    PROTO_CLIENT2_TEAM_LEAVE_REQ                    = 69,
    PROTO_CLIENT2_TEAM_KICK_REQ                     = 70,
    PROTO_CLIENT2_CANCEL_FAMILY_JOIN_REQ            = 71,
    PROTO_CLIENT2_CANCEL_FAMILY_JOIN_ACK            = 72,
    PROTO_CLIENT2_MAIL_OPEN_ACK2                    = 73,
    PROTO_CLIENT2_RELATION_CHAT_NTF                 = 77,       // 通知其他玩家
    PROTO_CLIENT2_SYS_MSG_NTF2                      = 80,       // 系统消息
    PROTO_CLIENT2_SCENE_DIALOG_NTF                  = 81,       // 场景对话框
    PROTO_CLINET2_SCROLL_TEXT_NTF                   = 83,       // 跑马灯
    PROTO_CLIENT2_CUST_MSG_NTF                      = 84,       // 后台自定义消息

    PROTO_CLIENT2_MAX
};

struct ProtoClient2_CustMsgNtf {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_CUST_MSG_NTF);
    char      message[65535];
    char      font_color[32];
    char      background_color[32];
    uint32_t  size                 = 0;
    uint8_t   comp                 = 0;
    uint16_t  display_type         = 0;  // 1 聊天框 2 跑马灯 3 公告 4（1&2） 5（1&3） 6（2&3） 7（1&2&3）
    uint8_t   scroll_times         = 0;
    ProtoClient2_CustMsgNtf() {
        memset(message, 0, sizeof(message));
        memset(font_color, 0, sizeof(font_color));
        memset(background_color, 0, sizeof(background_color));
    }
};

struct ProtoClient2_SysMsgNtf2 {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_SYS_MSG_NTF2);
    char      message[65535];
    char      font_color[32];
    char      background_color[32];
    uint32_t  size                 = 0;
    uint8_t   comp                 = 0;
    ProtoClient2_SysMsgNtf2() {
        memset(message, 0, sizeof(message));
        memset(font_color, 0, sizeof(font_color));
        memset(background_color, 0, sizeof(background_color));
    }
};

struct ProtoClient2_SceneDialogNtf {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_SCENE_DIALOG_NTF);
    char     message[65535];
    char     font_color[32];
    char     background_color[32];
    uint64_t objGuid            = 0;
    uint8_t  isAppearSrcName    = 0;
    uint32_t size               = 0;
    uint8_t  comp               = 0;
    ProtoClient2_SceneDialogNtf() {
        memset(message, 0, sizeof(message));
        memset(font_color, 0, sizeof(font_color));
        memset(background_color, 0, sizeof(background_color));
    }
};

struct ProtoClient2_ScrollText {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLINET2_SCROLL_TEXT_NTF);
    char     message[65535];
    char     font_color[32];
    char     background_color[32];
    uint8_t  scroll_times = 0;
    uint32_t size         = 0;
    uint8_t  comp         = 0;
    uint8_t  type         = 0;
    ProtoClient2_ScrollText() {
        memset(message, 0, sizeof(message));
        memset(font_color, 0, sizeof(font_color));
        memset(background_color, 0, sizeof(background_color));
    }
};

struct ProtoClient2_TopListAck {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_TOPLIST_ACK);
    unsigned char             type = 0; //排行榜类型，详见enum sort_type
    unsigned int              time = 0; //下次刷新时间
    unsigned char             num = 0; //上榜数量
    TOPLIST_INFO              info[100]; //排行榜内容
    ProtoClient2_TopListAck() {
        memset(info, 0, sizeof(info));
    }
};

struct ProtoClient2_TopListReq {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_TOPLIST_REQ);
    unsigned char             type; //排行榜类型，详见enum sort_type
    ProtoClient2_TopListReq(){}
};

struct ProtoClient2_TeamLeaderNtf{
  DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_TEAM_LEADER_NTF);
  uint64_t                  leader_guid; //新队长guid
  ProtoClient2_TeamLeaderNtf(){}
};

struct ProtoClient2_TeamJoin {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_TEAM_JOIN);
    char                      team_member[256] = {}; //申请加入队伍成员name
    ProtoClient2_TeamJoin() {}
};

struct ProtoClient2_TeamJoinNtf {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_TEAM_JOIN_NTF);
    char                      joiner[256] = {}; //申请加入者name
    ProtoClient2_TeamJoinNtf(){}
};

struct ProtoClient2_TeamJoinResponse {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_TEAM_JOIN_RSP);
    char                      joiner[256] = {}; //申请加入者name
    unsigned char             accepted; //是否同意
    ProtoClient2_TeamJoinResponse(){}
};

struct ProtoClient2_TeamKickEx {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_TEAM_KICK_REQ);
    char                      name[32] = {}; //被踢的name
    ProtoClient2_TeamKickEx() {}
};

struct ProtoClient2_TeamLeaveEx {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_TEAM_LEAVE_REQ);
    ProtoClient2_TeamLeaveEx() {}
};

struct ProtoClient2_TeamInvite {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_TEAM_INVITE);
    char                      invitee_name[256] = {}; //被邀请者name
    ProtoClient2_TeamInvite(){}
};

struct ProtoClient2_TeamInviteNtf {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_TEAM_INVITE_NTF);
    char                      inviter_name[256] = {}; //邀请者name
    unsigned char             exist; //是否有队伍
    unsigned short            num; //数量
    TEAM_INFO                 info[1] = {}; //队伍信息
    ProtoClient2_TeamInviteNtf() {}
};

struct ProtoClient2_TeamInviteRsp {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_TEAM_INVITE_RSP);
    char                      inviter_name[256] = {}; //邀请者name
    unsigned char             accepted; //是否同意
    ProtoClient2_TeamInviteRsp() {}
};

struct ProtoClient2_TeamLeaveNtf {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_MISS_TEAM_NTF);
    uint64_t                  player_guid; //player guid
    unsigned char             type; //1=被踢 2=主动离开
    ProtoClient2_TeamLeaveNtf() {}
};

struct ProtoClient2_TeamNtf {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_TEAM_NTF);
    TEAM_INFO                 info; //队伍信息
    ProtoClient2_TeamNtf()
    {
        memset(&info, 0, sizeof(info));
    }
};

struct ProtoClient2_Teamoperation {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_TEAM_OPERATION);
    unsigned char             operation = 0; //1 创建 2解散 3获取周围队伍 4转移队长
    char                      content[256]; //操作人
    ProtoClient2_Teamoperation() 
    {
        memset(content, 0, sizeof(content));
    }
};

struct ProtoClient2_PrivateChatNtf
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_PRIVATE_CHAT_NTF);

    uint8_t                     type                = 0;            // 6：私聊 5：点对点聊天
    CHAT_MSG                    chat_message;                       // 客户端发送时：角色名为目标角色的名字 客户端接收时：角色名为源角色的名字

    ProtoClient2_PrivateChatNtf()
    {
        memset(&chat_message, 0, sizeof(chat_message));
    }
};

struct ProtoClient2_RelationChatReq
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_RELATION_CHAT_REQ);

    uint8_t   type                = 0;            // 1：当前 2：队伍 3：公会 4：世界 5：小喇叭 9: 阵营 12：全服
    char      message[256];                       // 消息内容

    ProtoClient2_RelationChatReq()
    {
        memset(message, 0, sizeof(message));
    }
};

struct ProtoClient2_RelationChatAck
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_RELATION_CHAT_ACK);

    uint8_t   type                = 0;            // 1：当前 2：队伍 3：公会 4：世界 12：全服
    CHAT_MSG  chat_message;                       // 角色名为源角色的名字
    uint8_t   scroll_times = 0;
    char   font_color[32];
    char   background_color[32];

    ProtoClient2_RelationChatAck()
    {
        memset(&chat_message, 0, sizeof(chat_message));
        memset(&font_color, 0, sizeof(font_color));
        memset(&background_color, 0, sizeof(background_color));
    }
};

struct ProtoClient2_RelationChatNtf
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_RELATION_CHAT_NTF);

    uint8_t       type                = 0;            // 1：当前 2：队伍 3：公会 4：世界 12：全服
    CHAT_MSG      chat_message;                       // 角色名为源角色的名字
    uint8_t       scroll_times        = 0;
    char          font_color[32];
    char          background_color[32];
    uint32_t      size                = 0;            // 压缩后大小
    uint8_t       comp                = 0;            // 是否压缩 

    ProtoClient2_RelationChatNtf()
    {
        memset(&chat_message, 0, sizeof(chat_message));
        memset(&font_color, 0, sizeof(font_color));
        memset(&background_color, 0, sizeof(background_color));
    }
};

struct ProtoClient2_SysMsgNtf
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_SYS_MSG_NTF);

    uint8_t                     msg_type            = 0;            // 指定消息的类型，用来确定消息的显示区域
    uint8_t                     scroll_count        = 0;            // 消息的滚动次数 默认：1次
    char                        msg[256];                           // 具体的消息内容

    ProtoClient2_SysMsgNtf()
    {
        memset(msg, 0, sizeof(msg));
    }
};

struct ProtoClient2_SpeakerMsgReq
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_SPEAKER_MSG_REQ);

    char                        msg[256];                           // 消息内容

    ProtoClient2_SpeakerMsgReq()
    {
        memset(msg, 0, sizeof(msg));
    }
};

struct ProtoClient2_SpeakerMsgNtf
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_SPEAKER_MSG_NTF);

    char                        sender[256];                        // 发送者的名字
    char                        msg[256];                           // 消息内容

    ProtoClient2_SpeakerMsgNtf()
    {
        memset(sender, 0, sizeof(sender));
        memset(msg, 0, sizeof(msg));
    }
};

struct ProtoClient2_FamilyJoinReq
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_JOIN_REQ);

    uint64_t                    guid                = 0;            // 行会id
};

struct ProtoClient2_FamilyJoinAck
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_JOIN_ACK);

    uint64_t                    guid                = 0;            // 玩家的guid
    uint8_t                     is_allow            = 0;            // 是否允许入会：1、允许，0、不允许
};

struct ProtoClient2_FamilyInviteReq
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_INVITE_REQ);

    char                        name[32]            = {0};          // 被邀请者姓名
};

struct ProtoClient2_FamilyInviteVerify
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_INVITE_VERIFY);

    uint64_t                    guid                = 0;            // 行会ID
    char                        name[32]            = {0};          // 行会名称
};

struct ProtoClient2_FamilyInviteAck
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_INVITE_ACK);

    uint64_t                    guid                = 0;            // 行会ID
    uint8_t                     result              = 0;            // 是否同意。1、同意；0、不同意
};

struct ProtoClient2_GetFamilyInfoReq
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_GET_FAMILY_INFO_REQ);

    uint32_t                    reqType             = 0;            // 查询内容；1、行会公告；2、行会消息；4、行会封号；8、行会成员；16、敌对行会；32、联盟行会；64、入会申请列表；128、行会基本信息；256、可以加入的行会；512、在线成员；2048、所有行会成员；
    uint32_t                    start_index         = 0;            // 开始的index
    uint32_t                    req_count           = 0;            // 请求的数量
    uint32_t                    req_group           = 0;            // 分组信息
    char                        info[32]            = {0};          // 附加信息：如模糊查找的玩家名
};

struct ProtoClient2_FamilyNoticeAck
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_NOTICE_ACK);

    uint32_t                    notice_len          = 0;            // 公告长度
    char                        notice[1280]        = {0};          // 行会公告
};

struct ProtoClient2_FamilyMsgAck
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_MSG_ACK);

    uint32_t                    msg_len             = 0;            // 行会消息长度
    char                        sysmsgs[12800]      = {0};          // 行会消息，每个消息用'\n'隔开
};

struct ProtoClient2_FamilyTitlesAck
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_TITLES_ACK);

    uint32_t                    titles_len          = 0;            // 封号长度
    FAMILY_TITLE                titles[MAX_TITLE_NUM];              // 行会封号，最多MAX_TITLE_NUM个

    ProtoClient2_FamilyTitlesAck()
    {
        memset(titles, 0, sizeof(titles));
    }
};

struct ProtoClient2_FamilyMembersAck
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_MEMBERS_ACK);

    uint32_t                    total_num           = 0;            // 总共的成员数量
    uint32_t                    first_index         = 0;            // 当前第一个的index，从0开始算
    uint32_t                    members_num         = 0;            // 成员数量
    MEMBER_INFO                 members[100];                       // 行会成员

    ProtoClient2_FamilyMembersAck()
    {
        memset(members, 0, sizeof(members));
    }
};

struct ProtoClient2_FamilyEnemyAck
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_ENEMY_ACK);

    uint32_t                    total_num           = 0;            // 总共的成员数量
    uint32_t                    first_index         = 0;            // 当前第一个的index，从0开始算
    uint32_t                    enemy_num           = 0;            // 行会数量
    FAMILY_INFO                 enemy[MAX_ENEMY_NUM];               // 行会列表

    ProtoClient2_FamilyEnemyAck()
    {
        memset(enemy, 0, sizeof(enemy));
    }
};

struct ProtoClient2_FamilyAllyAck
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_ALLY_ACK);

    uint32_t                    total_num           = 0;            // 总共的成员数量
    uint32_t                    first_index         = 0;            // 当前第一个的index，从0开始算
    uint32_t                    ally_num            = 0;            // 行会数量
    FAMILY_INFO                 ally[MAX_ALLY_NUM];                 // 行会列表

    ProtoClient2_FamilyAllyAck()
    {
        memset(ally, 0, sizeof(ally));
    }
};

struct ProtoClient2_FamilyJoinListAck
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_JOIN_LIST_ACK);

    uint32_t                    total_num           = 0;            // 总共的成员数量
    uint32_t                    first_index         = 0;            // 当前第一个的index，从0开始算
    uint16_t                    num                 = 0;            // 数量
    APPLICANTS_INFO             info[50];                           // 申请者列表

    ProtoClient2_FamilyJoinListAck()
    {
        memset(info, 0, sizeof(info));
    }
};

struct ProtoClient2_FamilyTitleModifyReq
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_TITLE_MODIFY_REQ);

    uint8_t                     id                  = 0;            // 封号id(4-(MAX_TITLE_NUM - 1))，id不存在，即为新增
    char                        title[256]          = {0};          // 封号，封号不存在，即为删除
};

struct ProtoClient2_FamilyTitleAwardReq
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_TITLE_AWARD_REQ);

    uint64_t                    guid                = 0;            // 玩家ID
    uint8_t                     title_id            = 0;            // 封号id(0-(MAX_TITLE_NUM - 1))
};

struct ProtoClient2_FamilyLeaveOrLastMsgReq
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_LEAVE_OR_LAST_MSG_REQ);

    char                        byebye[256]         = {0};          // 临别赠言
};

struct ProtoClient2_FamilyExpellReq
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_EXPELL_REQ);

    uint64_t                    player_guid         = 0;            // 玩家ID
};

struct ProtoClient2_FamilyLeaveNtf
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_LEAVE_NTF);

    char                        kicker_name[32]     = {0};          // 开除者名字, 为空的话则是主动离开
    char                        family_name[32]     = {0};          // 行会名称
};

struct ProtoClient2_FamilyDestroyReq
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_DESTROY_REQ);
};

struct ProtoClient2_FamilyAddAllyEnemyReq
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_ADD_ALLY_ENEMY_REQ);

    uint8_t                     type                = 0;            // 类型：1、结盟；2、敌对
    char                        family_name[32]     = {0};          // 对方行会名称
};

struct ProtoClient2_FamilyAddAllyVerify
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_ADD_ALLY_VERIFY);

    char                        family_name[32]     = {0};          // 对方行会名称
};

struct ProtoClient2_FamilyAddAllyAck
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_ADD_ALLY_ACK);

    char                        family_name[32]     = {0};          // 对方行会名称
    uint8_t                     result              = 0;            // 1＝成功，0＝不同意
};

struct ProtoClient2_FamilyDeleteAllyEnemyReq
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_DEL_ALLY_ENEMY_REQ);

    uint64_t                    family_guid         = 0;            // 对方行会ID
};

struct ProtoClient2_FamilyNoticeEditReq
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_NOTICE_EDIT_REQ);

    uint32_t                    notice_len          = 0;            // 公告长度
    char                        notice[1280]        = {0};          // 行会公告
};

struct ProtoClient2_FamilyNameInputReq
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_NAME_INPUT_REQ);
};

struct ProtoClient2_FamilyNameInputAck
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_NAME_INPUT_ACK);

    char                        family_name[32]     = {0};          // 自己欲创建的行会名称
};

struct ProtoClient2_FamilyListNtfAck
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_LIST_NTF_ACK);

    uint32_t                    total_num           = 0;            // 总共的成员数量
    uint32_t                    first_index         = 0;            // 当前第一个的index，从0开始算
    uint32_t                    num                 = 0;            // 行会数量
    FAMILY_APPLY_INFO           familys[100];                       // 行会列表

    ProtoClient2_FamilyListNtfAck()
    {
        memset(familys, 0, sizeof(familys));
    }
};

struct ProtoClient2_FamilyInfoNtf
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_INFO_NTF);

    uint32_t                    type                = 0;            // 变更内容；1、行会公告；2、行会消息；4、行会封号；8、行会成员；16、敌对行会；32、联盟行会；64、入会申请列表；
};

struct ProtoClient2_MaillistReq 
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_MAIL_LIST_REQ);
    uint8_t                   type; //邮件类型：0、系统，1、玩家 2、所有类型
    uint64_t                  mail_id; //只接收该邮件后的邮件
    ProtoClient2_MaillistReq():type(0),mail_id() {}
};

struct ProtoClient2_MaillistAck 
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_MAIL_LIST_ACK);
    uint16_t                  cur_page;
    uint16_t                  page_num;
    int                       num; //当前返回的邮件数量
    MAIL_HEADER_INFO          mails[100]; //邮件列表
    ProtoClient2_MaillistAck() :num(0) {
        memset(mails, 0, sizeof(mails));
    }
};

struct ProtoClient2_MailOpenReq {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_MAIL_OPEN_REQ);
    uint64_t                  id; //邮件的ID
    ProtoClient2_MailOpenReq() :id(0) {}
};

struct ProtoClient2_MailOpenAck {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_MAIL_OPEN_ACK);
    uint64_t                  mail_id; //邮件ID
    MAIL_BODY_INFO            mail; //邮件
    ProtoClient2_MailOpenAck() :mail_id(0) {
        memset(&mail, 0, sizeof(mail));
    }
};

struct ProtoClient2_MailOpenAck2 {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_MAIL_OPEN_ACK2);
    uint64_t                  mail_id; //邮件ID
    MAIL_BODY_INFO2            mail; //邮件
    ProtoClient2_MailOpenAck2() :mail_id(0) {
        memset(&mail, 0, sizeof(mail));
    }
    void Clear()
    {
        memset(this, 0, sizeof(ProtoClient2_MailOpenAck2));
        REDEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_MAIL_OPEN_ACK2);
    }
};

struct ProtoClient2_MailAttachmentGetReq {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_MAIL_ATTACHMENT_GET_REQ);
    uint64_t                  mail_id; //邮件ID
    unsigned char             index; //附件序列：1是金币，2是元宝, 3-7为物品，8为积分
    ProtoClient2_MailAttachmentGetReq() :mail_id(0), index(0) {}
};

struct ProtoClient2_MailAttachmentGetAck {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_MAIL_ATTACHMENT_GET_ACK);
    uint64_t                  mail_id; //邮件ID
    unsigned char             index; //附件序列：1是金币，2是元宝, 3-7为物品，8为积分
    unsigned int              errcode; //错误码
    ProtoClient2_MailAttachmentGetAck() :mail_id(0), index(0), errcode(0) {}
};

struct ProtoClient2_MailDeleteReq {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_MAIL_DEL_REQ);
    uint64_t                  id; //邮件的ID
    ProtoClient2_MailDeleteReq() :id(0) {}
};

struct ProtoClient2_MailDeleteAck {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_MAIL_DEL_ACK);
    uint64_t                  id; //邮件的ID
    unsigned int              errcode; //错误码
    ProtoClient2_MailDeleteAck() :id(0), errcode(0) {}
};

struct ProtoClient2_MailSendReq {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_MAIL_SEND_REQ);
    char                      player_name[32]; //收件人姓名
    char                      text[256]; //邮件正文
    uint64_t                  item_guid[5]; //物品GUID列表
    int                       gold; //金币数量
    int                       yuanbao; //元宝数量
    ProtoClient2_MailSendReq() :gold(0), yuanbao(0) {
        memset(player_name, 0, sizeof(player_name));
        memset(text, 0, sizeof(text));
        memset(item_guid, 0, sizeof(item_guid));
    }
};

struct ProtoClient2_MailSendAck {
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_MAIL_SEND_ACK);
    unsigned int              errcode; //错误码
    ProtoClient2_MailSendAck() :errcode(0) {}
};

struct ProtoClient2_FamilyBaseInfoAck
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FAMILY_BASE_INFO_ACK);

    uint64_t                    family_guid         = 0;            // 行会id
    char                        name[32]            = {0};          // 行会名称
    uint32_t                    members_num         = 0;            // 行会人数
    uint64_t                    create_time         = 0;            // 创建时间
    uint8_t                     self_title_id       = 0;            // 查询者自己在行会中的封号ID
};

struct ProtoClient2_CancelFamilyJoinReq
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_CANCEL_FAMILY_JOIN_REQ);

    uint64_t                    guid                = 0;            // 行会id
};

struct ProtoClient2_CancelFamilyJoinAck
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_CANCEL_FAMILY_JOIN_ACK);

    uint64_t                    guid                = 0;            // 行会id
    uint32_t                    errcode             = 0;            // 错误码 0表示取消成功
};

struct ProtoClient2_NewMailNtf{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_NEW_MAIL_NTF);
    ProtoClient2_NewMailNtf() {}
};

struct ProtoClient2_FriendAddReq
{
    DEF_PROTO_HEADER_CLIENT2(PROTO_CLIENT2_FRIEND_ADD_REQ);

    char                        player_name[32]     = {0};          // 添加对象的名字
};


class ProtoClient2
{
public:
    ProtoClient2();
    ~ProtoClient2();

    static inline uint16_t GetModuleID(void) { return MODULE_TYPE_CLIENT2; }
    static inline uint16_t GetProtocolNum(void) { return PROTO_CLIENT2_MAX; }

    int BuildProtocol(void* pHost, char* pNet, int iNetSize);
    int HandleProtocol(void* pHost, char* pNet, int iNetSize);

private:
    EnCodeFunc m_EnCodeFuncArray[PROTO_CLIENT2_MAX];
    DeCodeFunc m_DeCodeFuncArray[PROTO_CLIENT2_MAX];
};
