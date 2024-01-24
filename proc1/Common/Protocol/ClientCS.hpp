#pragma once

#include "netdata.h"

//===============包含的其他协议文件===============
#include "DataInfo.hpp"
//===============宏定义开始===============
enum CSProtocolID {
    ENTER_CS_NTF                    = 0,
    PRIVATE_CHAT_NTF                = 1,
    RELATION_CHAT_REQ               = 2,
    RELATION_CHAT_ACK               = 3,
    CS_SYS_MSG_NTF                  = 4,
    TEAM_INVITE                     = 5,
    TEAM_INVITE_NTF                 = 6,
    TEAM_INVITE_REQ                 = 7,
    TEAM_KICK                       = 8,
    TEAM_LEAVE                      = 9,
    TEAM_LEAVE_NTF                  = 10,
    TEAM_LEADER_NTF                 = 11,
    TEAM_NTF                        = 12,
    FRIEND_ADD_REQ                  = 13,
    FRIEND_ADD_REQ_VERIFY           = 14,
    FRIEND_ADD_REQ_ACK              = 15,
    FRIEND_LIST                     = 16,
    FRIEND_DEL_REQ                  = 17,
    FRIEND_LIST_CHG                 = 18,
    FRIEND_DETAIL_REQ               = 19,
    FRIEND_DETAIL_ACK               = 20,
    FAMILY_JOIN_REQ                 = 21,
    FAMILY_JOIN_ACK                 = 22,
    FAMILY_INVITE_REQ               = 23,
    FAMILY_INVITE_VERIFY            = 24,
    FAMILY_INVITE_ACK               = 25,
    GET_FAMILY_INFO_REQ             = 26,
    FAMILY_NOTICE_ACK               = 27,
    FAMILY_MSG_ACK                  = 28,
    FAMILY_TITLES_ACK               = 29,
    FAMILY_MEMBERS_ACK              = 30,
    FAMILY_ENEMY_ACK                = 31,
    FAMILY_ALLY_ACK                 = 32,
    FAMILY_JOIN_LIST_ACK            = 33,
    FAMILY_TITLE_MODIFY_REQ         = 34,
    FAMILY_TITLE_AWARD_REQ          = 35,
    FAMILY_LEAVE_OR_LAST_MSG_REQ    = 36,
    FAMILY_EXPELL_REQ               = 37,
    FAMILY_LEAVE_NTF                = 38,
    FAMILY_DESTROY_REQ              = 39,
    FAMILY_ADD_ALLY_ENEMY_REQ       = 40,
    FAMILY_ADD_ALLY_VERIFY          = 41,
    FAMILY_ADD_ALLY_ACK             = 42,
    FAMILY_DEL_ALLY_ENEMY_REQ       = 43,
    FAMILY_NOTICE_EDIT_REQ          = 44,
    FAMILY_NAME_INPUT_REQ           = 45,
    FAMILY_NAME_INPUT_ACK           = 46,
    FAMILY_LIST_NTF_ACK             = 47,
    FAMILY_INFO_NTF                 = 48,
    FAMILY_BASE_INFO_ACK            = 49,
    TOPLIST_REQ                     = 50,
    TOPLIST_ACK                     = 51,
    MAIL_LIST_REQ                   = 52,
    MAIL_LIST_ACK                   = 53,
    MAIL_OPEN_REQ                   = 54,
    MAIL_OPEN_ACK                   = 55,
    MAIL_ATTACHMENT_GET_REQ         = 56,
    MAIL_ATTACHMENT_GET_ACK         = 57,
    MAIL_DEL_REQ                    = 58,
    MAIL_DEL_ACK                    = 59,
    MAIL_SEND_REQ                   = 60,
    MAIL_SEND_ACK                   = 61,
    SPEAKER_MSG_REQ                 = 62,
    SPEAKER_MSG_NTF                 = 63,
    NEW_MAIL_NTF                    = 64,
    TEAM_OPERATION                  = 65,
    TEAM_JOIN                       = 66,
    TEAM_JOIN_NTF                   = 67,
    TEAM_JOIN_REQ                   = 68,
    TEAM_LEAVE_EX                   = 69,
    TEAM_KICK_EX                    = 70,
    CANCEL_FAMILY_JOIN_REQ          = 71,
    CANCEL_FAMILY_JOIN_ACK          = 72,
    MAIL_OPEN_ACK2                  = 73,
    TEAM_CANCEL_JOIN_NTF            = 74,
    VOICE2_TEXT_AUTH_REQ            = 75,
    VOICE2_TEXT_AUTH_ACK            = 76,
    CS_PROTOCOL_ID_MAX
};
//===============宏定义结束===============

//===============数据定义开始===============
#pragma warning( push )
#pragma warning( disable : 4512)
struct EnterCSNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned int              objid; //玩家在Center Server上的objid
	EnterCSNtf():moudleid(MOUDLE_ID_CS),protocolid(ENTER_CS_NTF){}
};

struct PrivateChatNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             type; //6：私聊 5：点对点聊天
	CHAT_MSG                  chat_message; //客户端发送时：角色名为目标角色的名字 客户端接收时：角色名为源角色的名字
	PrivateChatNtf():moudleid{MOUDLE_ID_CS},protocolid(PRIVATE_CHAT_NTF){}
};

struct RelationChatReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             type; //1：当前 2：队伍 3：公会 4：世界 5：小喇叭 12：全服
	char                      message[256]; //消息内容
	RelationChatReq():moudleid{MOUDLE_ID_CS},protocolid(RELATION_CHAT_REQ){}
};

struct RelationChatAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             type; //1：当前 2：队伍 3：公会 4：世界 12：全服
	CHAT_MSG                  chat_message; //角色名为源角色的名字
	RelationChatAck():moudleid{MOUDLE_ID_CS},protocolid(RELATION_CHAT_ACK){}
};

struct CSSysMsgNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             msg_type; //指定消息的类型，用来确定消息的显示区域
	unsigned char             scroll_count; //消息的滚动次数 默认：1次
	char                      msg[256]; //具体的消息内容
	CSSysMsgNtf():moudleid{MOUDLE_ID_CS},protocolid(CS_SYS_MSG_NTF){}
};

struct TeamInvite{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      invitee_name[256]; //被邀请者name
	TeamInvite():moudleid{MOUDLE_ID_CS},protocolid(TEAM_INVITE){}
};

struct TeamInviteNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      inviter_name[256]; //邀请者name
	unsigned char             exist; //是否有队伍
	unsigned short            num; //数量
	TEAM_INFO                 info[1]; //队伍信息
	TeamInviteNtf():moudleid{MOUDLE_ID_CS},protocolid(TEAM_INVITE_NTF){}
};

struct TeamInviteResponse{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      inviter_name[256]; //邀请者name
	unsigned char             accepted; //是否同意
	TeamInviteResponse():moudleid{MOUDLE_ID_CS},protocolid(TEAM_INVITE_REQ){}
};

struct TeamKick{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      name[32]; //被踢的name
	TeamKick():moudleid{MOUDLE_ID_CS},protocolid(TEAM_KICK){}
};

struct TeamLeave{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	TeamLeave():moudleid{MOUDLE_ID_CS},protocolid(TEAM_LEAVE){}
};

struct TeamLeaveNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  player_guid; //player guid
	unsigned char             type; //0=解散 1=被踢 2=主动离开
	TeamLeaveNtf():moudleid{MOUDLE_ID_CS},protocolid(TEAM_LEAVE_NTF){}
};

struct TeamLeaderNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  leader_guid; //新队长guid
	TeamLeaderNtf():moudleid{MOUDLE_ID_CS},protocolid(TEAM_LEADER_NTF){}
};

struct TeamNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	TEAM_INFO                 info; //队伍信息
	TeamNtf():moudleid{MOUDLE_ID_CS},protocolid(TEAM_NTF){}
};

struct FriendAddReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      player_name[32]; //添加对象的名字
	FriendAddReq():moudleid{MOUDLE_ID_CS},protocolid(FRIEND_ADD_REQ){}
};

struct FriendAddReqVerify{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      applicant_name[32]; //申请人的name
	FriendAddReqVerify():moudleid{MOUDLE_ID_CS},protocolid(FRIEND_ADD_REQ_VERIFY){}
};

struct FriendAddReqAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      player_name[32]; //被添加对象的名字
	unsigned char             result; //0＝成功，1＝不同意，2＝不允许加为好友,3=对方不在线，4＝对方人数已满，5＝自己人数已满,6=玩家设置了拒绝加好友,7=对方已经是自己的好友
	FriendAddReqAck():moudleid{MOUDLE_ID_CS},protocolid(FRIEND_ADD_REQ_ACK){}
};

struct FriendList{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	FRIEND_LIST_INFO               friend_list; //好友列表信息
	FriendList():moudleid{MOUDLE_ID_CS},protocolid(FRIEND_LIST){}
};

struct FriendDelReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      applicant_name[32]; //欲删除的好友姓名
	unsigned char             move_blacklist; //是否移动到黑名单，0、不移动， 1、移动到黑名单
	FriendDelReq():moudleid{MOUDLE_ID_CS},protocolid(FRIEND_DEL_REQ){}
};

struct FriendListChg{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             action; //操作：1、添加， 2、删除, 3、状态更新
	FRIEND_INFO               friend_info; //目标对象的信息
	FriendListChg():moudleid{MOUDLE_ID_CS},protocolid(FRIEND_LIST_CHG){}
};

struct FriendDetailReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      player_name[32]; //查询对象的名字
	FriendDetailReq():moudleid{MOUDLE_ID_CS},protocolid(FRIEND_DETAIL_REQ){}
};

struct FriendDetailAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	FRIEND_DETAIL             friend_detail; //查询对象的名字
	FriendDetailAck():moudleid{MOUDLE_ID_CS},protocolid(FRIEND_DETAIL_ACK){}
};

struct FamilyJoinReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  guid; //行会id
	FamilyJoinReq():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_JOIN_REQ){}
};

struct FamilyJoinAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  guid; //玩家的guid
	unsigned char             is_allow; //是否允许入会：1、允许，0、不允许
	FamilyJoinAck():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_JOIN_ACK){}
};

struct FamilyInviteReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      name[32]; //被邀请者姓名
	FamilyInviteReq():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_INVITE_REQ){}
};

struct FamilyInviteVerify{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  guid; //行会ID
	char                      name[32]; //行会名称
	FamilyInviteVerify():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_INVITE_VERIFY){}
};

struct FamilyInviteAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  guid; //行会ID
	unsigned char             result; //是否同意。1、同意；0、不同意
	FamilyInviteAck():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_INVITE_ACK){}
};

struct GetFamilyInfoReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned int              reqType; //查询内容；1、行会公告；2、行会消息；4、行会封号；8、行会成员；16、敌对行会；32、联盟行会；64、入会申请列表；128、行会基本信息；256、可以加入的行会；512、在线成员；2048、所有行会成员；
	unsigned int              start_index; //开始的index
	unsigned int              req_count; //请求的数量
	unsigned int              req_group; //分组信息
	char                      info[32]; //附加信息：如模糊查找的玩家名
	GetFamilyInfoReq():moudleid{MOUDLE_ID_CS},protocolid(GET_FAMILY_INFO_REQ){}
};

struct FamilyNoticeAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       notice_len; //公告长度
	char                      notice[1280]; //行会公告
	FamilyNoticeAck():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_NOTICE_ACK){}
};

struct FamilyMsgAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       msg_len; //行会消息长度
	char                      sysmsgs[12800]; //行会消息，每个消息用'\n'隔开
	FamilyMsgAck():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_MSG_ACK){}
};

struct FamilyTitlesAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       titles_len; //封号长度
	FAMILY_TITLE              titles[MAX_TITLE_NUM]; //行会封号，最多MAX_TITLE_NUM个
	FamilyTitlesAck():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_TITLES_ACK){}
};

struct FamilyMembersAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       total_num; //总共的成员数量
	int                       first_index; //当前第一个的index，从0开始算
	int                       members_num; //成员数量
	MEMBER_INFO               members[100]; //行会成员
	FamilyMembersAck():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_MEMBERS_ACK){}
};

struct FamilyEnemyAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       total_num; //总共的成员数量
	int                       first_index; //当前第一个的index，从0开始算
	int                       enemy_num; //行会数量
	FAMILY_INFO               enemy[MAX_ENEMY_NUM]; //行会列表
	FamilyEnemyAck():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_ENEMY_ACK){}
};

struct FamilyAllyAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       total_num; //总共的成员数量
	int                       first_index; //当前第一个的index，从0开始算
	int                       ally_num; //行会数量
	FAMILY_INFO               ally[MAX_ALLY_NUM]; //行会列表
	FamilyAllyAck():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_ALLY_ACK){}
};

struct FamilyJoinListAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       total_num; //总共的成员数量
	int                       first_index; //当前第一个的index，从0开始算
	unsigned short            num; //数量
	APPLICANTS_INFO           info[50]; //申请者列表
	FamilyJoinListAck():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_JOIN_LIST_ACK){}
};

struct FamilyTitleModifyReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             id; //封号id(4-(MAX_TITLE_NUM - 1))，id不存在，即为新增
	char                      title[256]; //封号，封号不存在，即为删除
	FamilyTitleModifyReq():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_TITLE_MODIFY_REQ){}
};

struct FamilyTitleAwardReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  guid; //玩家ID
	unsigned char             title_id; //封号id(0-(MAX_TITLE_NUM - 1))
	FamilyTitleAwardReq():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_TITLE_AWARD_REQ){}
};

struct FamilyLeaveOrLastMsgReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      byebye[256]; //临别赠言
	FamilyLeaveOrLastMsgReq():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_LEAVE_OR_LAST_MSG_REQ){}
};

struct FamilyExpellReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  player_guid; //玩家ID
	FamilyExpellReq():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_EXPELL_REQ){}
};

struct FamilyLeaveNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      kicker_name[32]; //开除者名字, 为空的话则是主动离开
	char                      family_name[32]; //行会名称
	FamilyLeaveNtf():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_LEAVE_NTF){}
};

struct FamilyDestroyReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	FamilyDestroyReq():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_DESTROY_REQ){}
};

struct FamilyAddAllyEnemyReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             type; //类型：1、结盟；2、敌对
	char                      family_name[32]; //对方行会名称
	FamilyAddAllyEnemyReq():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_ADD_ALLY_ENEMY_REQ){}
};

struct FamilyAddAllyVerify{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      family_name[32]; //对方行会名称
	FamilyAddAllyVerify():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_ADD_ALLY_VERIFY){}
};

struct FamilyAddAllyAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      family_name[32]; //对方行会名称
	unsigned char             result; //1＝成功，0＝不同意
	FamilyAddAllyAck():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_ADD_ALLY_ACK){}
};

struct FamilyDeleteAllyEnemyReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  family_guid; //对方行会ID
	FamilyDeleteAllyEnemyReq():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_DEL_ALLY_ENEMY_REQ){}
};

struct FamilyNoticeEditReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       notice_len; //公告长度
	char                      notice[1280]; //行会公告
	FamilyNoticeEditReq():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_NOTICE_EDIT_REQ){}
};

struct FamilyNameInputReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	FamilyNameInputReq():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_NAME_INPUT_REQ){}
};

struct FamilyNameInputAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      family_name[32]; //自己欲创建的行会名称
	FamilyNameInputAck():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_NAME_INPUT_ACK){}
};

struct FamilyListNtfAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       total_num; //总共的成员数量
	int                       first_index; //当前第一个的index，从0开始算
	int                       num; //行会数量
	FAMILY_APPLY_INFO         familys[100]; //行会列表
	FamilyListNtfAck():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_LIST_NTF_ACK){}
};

struct FamilyInfoNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned int              type; //变更内容；1、行会公告；2、行会消息；4、行会封号；8、行会成员；16、敌对行会；32、联盟行会；64、入会申请列表；
	FamilyInfoNtf():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_INFO_NTF){}
};

struct FamilyBaseInfoAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  family_guid; //行会id
	char                      name[32]; //行会名称
	unsigned int              members_num; //行会人数
	unsigned int              create_time; //创建时间
	unsigned char             self_title_id; //查询者自己在行会中的封号ID
	FamilyBaseInfoAck():moudleid{MOUDLE_ID_CS},protocolid(FAMILY_BASE_INFO_ACK){}
};

struct ToplistReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             type; //排行榜类型，详见enum sort_type
	ToplistReq():moudleid{MOUDLE_ID_CS},protocolid(TOPLIST_REQ){}
};

struct ToplistAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             type; //排行榜类型，详见enum sort_type
	unsigned int              time; //下次刷新时间
	unsigned char             num; //上榜数量
	TOPLIST_INFO              info[100]; //排行榜内容
	ToplistAck():moudleid{MOUDLE_ID_CS},protocolid(TOPLIST_ACK){}
};

struct MaillistReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             type; //邮件类型：0、系统，1、玩家
	uint64_t                  mail_id; //只接收该邮件后的邮件
	MaillistReq():moudleid{MOUDLE_ID_CS},protocolid(MAIL_LIST_REQ){}
};

struct MaillistAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	int                       num; //当前返回的邮件数量
	MAIL_HEADER_INFO          mails[100]; //邮件列表
	MaillistAck():moudleid{MOUDLE_ID_CS},protocolid(MAIL_LIST_ACK){}
};

struct MailOpenReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  id; //邮件的ID
	MailOpenReq():moudleid{MOUDLE_ID_CS},protocolid(MAIL_OPEN_REQ){}
};

struct MailOpenAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  mail_id; //邮件ID
	MAIL_BODY_INFO            mail; //邮件
	MailOpenAck():moudleid{MOUDLE_ID_CS},protocolid(MAIL_OPEN_ACK){}
};

struct MailAttachmentGetReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  mail_id; //邮件ID
	unsigned char             index; //附件序列：1是金币，2是元宝, 3-7为物品，8为积分
	MailAttachmentGetReq():moudleid{MOUDLE_ID_CS},protocolid(MAIL_ATTACHMENT_GET_REQ){}
};

struct MailAttachmentGetAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  mail_id; //邮件ID
	unsigned char             index; //附件序列：1是金币，2是元宝, 3-7为物品，8为积分
	unsigned int              errcode; //错误码
	MailAttachmentGetAck():moudleid{MOUDLE_ID_CS},protocolid(MAIL_ATTACHMENT_GET_ACK){}
};

struct MailDeleteReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  id; //邮件的ID
	MailDeleteReq():moudleid{MOUDLE_ID_CS},protocolid(MAIL_DEL_REQ){}
};

struct MailDeleteAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  id; //邮件的ID
	unsigned int              errcode; //错误码
	MailDeleteAck():moudleid{MOUDLE_ID_CS},protocolid(MAIL_DEL_ACK){}
};

struct MailSendReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      player_name[32]; //收件人姓名
	char                      text[256]; //邮件正文
	uint64_t                  item_guid[5]; //物品GUID列表
	int                       gold; //金币数量
	int                       yuanbao; //元宝数量
	MailSendReq():moudleid{MOUDLE_ID_CS},protocolid(MAIL_SEND_REQ){}
};

struct MailSendAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned int              errcode; //错误码
	MailSendAck():moudleid{MOUDLE_ID_CS},protocolid(MAIL_SEND_ACK){}
};

struct SpeakerMsgReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      msg[256]; //消息内容
	SpeakerMsgReq():moudleid{MOUDLE_ID_CS},protocolid(SPEAKER_MSG_REQ){}
};

struct SpeakerMsgNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      sender[256]; //发送者的名字
	char                      msg[256]; //消息内容
	SpeakerMsgNtf():moudleid{MOUDLE_ID_CS},protocolid(SPEAKER_MSG_NTF){}
};

struct NewMailNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	NewMailNtf():moudleid{MOUDLE_ID_CS},protocolid(NEW_MAIL_NTF){}
};

struct Teamoperation{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	unsigned char             operation; //1 创建 2解散 3获取周围队伍 4转移队长
	char                      content[256]; //操作人
	Teamoperation():moudleid{MOUDLE_ID_CS},protocolid(TEAM_OPERATION){}
};

struct TeamJoin{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      team_member[256]; //申请加入队伍成员name
	TeamJoin():moudleid{MOUDLE_ID_CS},protocolid(TEAM_JOIN){}
};

struct TeamJoinNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      joiner[256]; //申请加入者name
	TeamJoinNtf():moudleid{MOUDLE_ID_CS},protocolid(TEAM_JOIN_NTF){}
};

struct TeamJoinResponse{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      joiner[256]; //申请加入者name
	unsigned char             accepted; //是否同意
	TeamJoinResponse():moudleid{MOUDLE_ID_CS},protocolid(TEAM_JOIN_REQ){}
};

struct TeamLeaveEx{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	TeamLeaveEx():moudleid{MOUDLE_ID_CS},protocolid(TEAM_LEAVE_EX){}
};

struct TeamKickEx{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      name[32]; //被踢的name
	TeamKickEx():moudleid{MOUDLE_ID_CS},protocolid(TEAM_KICK_EX){}
};

struct CancelFamilyJoinReq{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  guid; //行会id
	CancelFamilyJoinReq():moudleid{MOUDLE_ID_CS},protocolid(CANCEL_FAMILY_JOIN_REQ){}
};

struct CancelFamilyJoinAck{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  guid; //行会id
	unsigned int              errcode; //错误码 0表示取消成功
	CancelFamilyJoinAck():moudleid{MOUDLE_ID_CS},protocolid(CANCEL_FAMILY_JOIN_ACK){}
};

struct MailOpenAck2{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	uint64_t                  mail_id; //邮件ID
	MAIL_BODY_INFO2           mail; //邮件
	MailOpenAck2():moudleid{MOUDLE_ID_CS},protocolid(MAIL_OPEN_ACK2){}
};

struct TeamCancelJoinNtf{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	char                      joiner[256]; //申请加入者name
	TeamCancelJoinNtf():moudleid{MOUDLE_ID_CS},protocolid(TEAM_CANCEL_JOIN_NTF){}
};

struct Voice2TextAuthReq {
    const unsigned short      moudleid;
    const unsigned short      protocolid;
    Voice2TextAuthReq() :moudleid{MOUDLE_ID_CS}, protocolid(VOICE2_TEXT_AUTH_REQ) {}
};

struct Voice2TextAuthAck {
    const unsigned short      moudleid;
    const unsigned short      protocolid;
    char                      token[4096];  //获取鉴权的token
    Voice2TextAuthAck():moudleid{MOUDLE_ID_CS}, protocolid(VOICE2_TEXT_AUTH_ACK) {}
};

#pragma warning( pop ) 
//===============数据定义结束===============
//===============打包解包函数定义开始===============
int EnCodeEnterCSNtf(void* pHost, CNetData* poNetData);
int DeCodeEnterCSNtf(void* pHost, CNetData* poNetData);
int EnCodePrivateChatNtf(void* pHost, CNetData* poNetData);
int DeCodePrivateChatNtf(void* pHost, CNetData* poNetData);
int EnCodeRelationChatReq(void* pHost, CNetData* poNetData);
int DeCodeRelationChatReq(void* pHost, CNetData* poNetData);
int EnCodeRelationChatAck(void* pHost, CNetData* poNetData);
int DeCodeRelationChatAck(void* pHost, CNetData* poNetData);
int EnCodeCSSysMsgNtf(void* pHost, CNetData* poNetData);
int DeCodeCSSysMsgNtf(void* pHost, CNetData* poNetData);
int EnCodeTeamInvite(void* pHost, CNetData* poNetData);
int DeCodeTeamInvite(void* pHost, CNetData* poNetData);
int EnCodeTeamInviteNtf(void* pHost, CNetData* poNetData);
int DeCodeTeamInviteNtf(void* pHost, CNetData* poNetData);
int EnCodeTeamInviteResponse(void* pHost, CNetData* poNetData);
int DeCodeTeamInviteResponse(void* pHost, CNetData* poNetData);
int EnCodeTeamKick(void* pHost, CNetData* poNetData);
int DeCodeTeamKick(void* pHost, CNetData* poNetData);
int EnCodeTeamLeave(void* pHost, CNetData* poNetData);
int DeCodeTeamLeave(void* pHost, CNetData* poNetData);
int EnCodeTeamLeaveNtf(void* pHost, CNetData* poNetData);
int DeCodeTeamLeaveNtf(void* pHost, CNetData* poNetData);
int EnCodeTeamLeaderNtf(void* pHost, CNetData* poNetData);
int DeCodeTeamLeaderNtf(void* pHost, CNetData* poNetData);
int EnCodeTeamNtf(void* pHost, CNetData* poNetData);
int DeCodeTeamNtf(void* pHost, CNetData* poNetData);
int EnCodeFriendAddReq(void* pHost, CNetData* poNetData);
int DeCodeFriendAddReq(void* pHost, CNetData* poNetData);
int EnCodeFriendAddReqVerify(void* pHost, CNetData* poNetData);
int DeCodeFriendAddReqVerify(void* pHost, CNetData* poNetData);
int EnCodeFriendAddReqAck(void* pHost, CNetData* poNetData);
int DeCodeFriendAddReqAck(void* pHost, CNetData* poNetData);
int EnCodeFriendList(void* pHost, CNetData* poNetData);
int DeCodeFriendList(void* pHost, CNetData* poNetData);
int EnCodeFriendDelReq(void* pHost, CNetData* poNetData);
int DeCodeFriendDelReq(void* pHost, CNetData* poNetData);
int EnCodeFriendListChg(void* pHost, CNetData* poNetData);
int DeCodeFriendListChg(void* pHost, CNetData* poNetData);
int EnCodeFriendDetailReq(void* pHost, CNetData* poNetData);
int DeCodeFriendDetailReq(void* pHost, CNetData* poNetData);
int EnCodeFriendDetailAck(void* pHost, CNetData* poNetData);
int DeCodeFriendDetailAck(void* pHost, CNetData* poNetData);
int EnCodeFamilyJoinReq(void* pHost, CNetData* poNetData);
int DeCodeFamilyJoinReq(void* pHost, CNetData* poNetData);
int EnCodeFamilyJoinAck(void* pHost, CNetData* poNetData);
int DeCodeFamilyJoinAck(void* pHost, CNetData* poNetData);
int EnCodeFamilyInviteReq(void* pHost, CNetData* poNetData);
int DeCodeFamilyInviteReq(void* pHost, CNetData* poNetData);
int EnCodeFamilyInviteVerify(void* pHost, CNetData* poNetData);
int DeCodeFamilyInviteVerify(void* pHost, CNetData* poNetData);
int EnCodeFamilyInviteAck(void* pHost, CNetData* poNetData);
int DeCodeFamilyInviteAck(void* pHost, CNetData* poNetData);
int EnCodeGetFamilyInfoReq(void* pHost, CNetData* poNetData);
int DeCodeGetFamilyInfoReq(void* pHost, CNetData* poNetData);
int EnCodeFamilyNoticeAck(void* pHost, CNetData* poNetData);
int DeCodeFamilyNoticeAck(void* pHost, CNetData* poNetData);
int EnCodeFamilyMsgAck(void* pHost, CNetData* poNetData);
int DeCodeFamilyMsgAck(void* pHost, CNetData* poNetData);
int EnCodeFamilyTitlesAck(void* pHost, CNetData* poNetData);
int DeCodeFamilyTitlesAck(void* pHost, CNetData* poNetData);
int EnCodeFamilyMembersAck(void* pHost, CNetData* poNetData);
int DeCodeFamilyMembersAck(void* pHost, CNetData* poNetData);
int EnCodeFamilyEnemyAck(void* pHost, CNetData* poNetData);
int DeCodeFamilyEnemyAck(void* pHost, CNetData* poNetData);
int EnCodeFamilyAllyAck(void* pHost, CNetData* poNetData);
int DeCodeFamilyAllyAck(void* pHost, CNetData* poNetData);
int EnCodeFamilyJoinListAck(void* pHost, CNetData* poNetData);
int DeCodeFamilyJoinListAck(void* pHost, CNetData* poNetData);
int EnCodeFamilyTitleModifyReq(void* pHost, CNetData* poNetData);
int DeCodeFamilyTitleModifyReq(void* pHost, CNetData* poNetData);
int EnCodeFamilyTitleAwardReq(void* pHost, CNetData* poNetData);
int DeCodeFamilyTitleAwardReq(void* pHost, CNetData* poNetData);
int EnCodeFamilyLeaveOrLastMsgReq(void* pHost, CNetData* poNetData);
int DeCodeFamilyLeaveOrLastMsgReq(void* pHost, CNetData* poNetData);
int EnCodeFamilyExpellReq(void* pHost, CNetData* poNetData);
int DeCodeFamilyExpellReq(void* pHost, CNetData* poNetData);
int EnCodeFamilyLeaveNtf(void* pHost, CNetData* poNetData);
int DeCodeFamilyLeaveNtf(void* pHost, CNetData* poNetData);
int EnCodeFamilyDestroyReq(void* pHost, CNetData* poNetData);
int DeCodeFamilyDestroyReq(void* pHost, CNetData* poNetData);
int EnCodeFamilyAddAllyEnemyReq(void* pHost, CNetData* poNetData);
int DeCodeFamilyAddAllyEnemyReq(void* pHost, CNetData* poNetData);
int EnCodeFamilyAddAllyVerify(void* pHost, CNetData* poNetData);
int DeCodeFamilyAddAllyVerify(void* pHost, CNetData* poNetData);
int EnCodeFamilyAddAllyAck(void* pHost, CNetData* poNetData);
int DeCodeFamilyAddAllyAck(void* pHost, CNetData* poNetData);
int EnCodeFamilyDeleteAllyEnemyReq(void* pHost, CNetData* poNetData);
int DeCodeFamilyDeleteAllyEnemyReq(void* pHost, CNetData* poNetData);
int EnCodeFamilyNoticeEditReq(void* pHost, CNetData* poNetData);
int DeCodeFamilyNoticeEditReq(void* pHost, CNetData* poNetData);
int EnCodeFamilyNameInputReq(void* pHost, CNetData* poNetData);
int DeCodeFamilyNameInputReq(void* pHost, CNetData* poNetData);
int EnCodeFamilyNameInputAck(void* pHost, CNetData* poNetData);
int DeCodeFamilyNameInputAck(void* pHost, CNetData* poNetData);
int EnCodeFamilyListNtfAck(void* pHost, CNetData* poNetData);
int DeCodeFamilyListNtfAck(void* pHost, CNetData* poNetData);
int EnCodeFamilyInfoNtf(void* pHost, CNetData* poNetData);
int DeCodeFamilyInfoNtf(void* pHost, CNetData* poNetData);
int EnCodeFamilyBaseInfoAck(void* pHost, CNetData* poNetData);
int DeCodeFamilyBaseInfoAck(void* pHost, CNetData* poNetData);
int EnCodeToplistReq(void* pHost, CNetData* poNetData);
int DeCodeToplistReq(void* pHost, CNetData* poNetData);
int EnCodeToplistAck(void* pHost, CNetData* poNetData);
int DeCodeToplistAck(void* pHost, CNetData* poNetData);
int EnCodeMaillistReq(void* pHost, CNetData* poNetData);
int DeCodeMaillistReq(void* pHost, CNetData* poNetData);
int EnCodeMaillistAck(void* pHost, CNetData* poNetData);
int DeCodeMaillistAck(void* pHost, CNetData* poNetData);
int EnCodeMailOpenReq(void* pHost, CNetData* poNetData);
int DeCodeMailOpenReq(void* pHost, CNetData* poNetData);
int EnCodeMailOpenAck(void* pHost, CNetData* poNetData);
int DeCodeMailOpenAck(void* pHost, CNetData* poNetData);
int EnCodeMailAttachmentGetReq(void* pHost, CNetData* poNetData);
int DeCodeMailAttachmentGetReq(void* pHost, CNetData* poNetData);
int EnCodeMailAttachmentGetAck(void* pHost, CNetData* poNetData);
int DeCodeMailAttachmentGetAck(void* pHost, CNetData* poNetData);
int EnCodeMailDeleteReq(void* pHost, CNetData* poNetData);
int DeCodeMailDeleteReq(void* pHost, CNetData* poNetData);
int EnCodeMailDeleteAck(void* pHost, CNetData* poNetData);
int DeCodeMailDeleteAck(void* pHost, CNetData* poNetData);
int EnCodeMailSendReq(void* pHost, CNetData* poNetData);
int DeCodeMailSendReq(void* pHost, CNetData* poNetData);
int EnCodeMailSendAck(void* pHost, CNetData* poNetData);
int DeCodeMailSendAck(void* pHost, CNetData* poNetData);
int EnCodeSpeakerMsgReq(void* pHost, CNetData* poNetData);
int DeCodeSpeakerMsgReq(void* pHost, CNetData* poNetData);
int EnCodeSpeakerMsgNtf(void* pHost, CNetData* poNetData);
int DeCodeSpeakerMsgNtf(void* pHost, CNetData* poNetData);
int EnCodeNewMailNtf(void* pHost, CNetData* poNetData);
int DeCodeNewMailNtf(void* pHost, CNetData* poNetData);
int EnCodeTeamoperation(void* pHost, CNetData* poNetData);
int DeCodeTeamoperation(void* pHost, CNetData* poNetData);
int EnCodeTeamJoin(void* pHost, CNetData* poNetData);
int DeCodeTeamJoin(void* pHost, CNetData* poNetData);
int EnCodeTeamJoinNtf(void* pHost, CNetData* poNetData);
int DeCodeTeamJoinNtf(void* pHost, CNetData* poNetData);
int EnCodeTeamJoinResponse(void* pHost, CNetData* poNetData);
int DeCodeTeamJoinResponse(void* pHost, CNetData* poNetData);
int EnCodeTeamLeaveEx(void* pHost, CNetData* poNetData);
int DeCodeTeamLeaveEx(void* pHost, CNetData* poNetData);
int EnCodeTeamKickEx(void* pHost, CNetData* poNetData);
int DeCodeTeamKickEx(void* pHost, CNetData* poNetData);
int EnCodeCancelFamilyJoinReq(void* pHost, CNetData* poNetData);
int DeCodeCancelFamilyJoinReq(void* pHost, CNetData* poNetData);
int EnCodeCancelFamilyJoinAck(void* pHost, CNetData* poNetData);
int DeCodeCancelFamilyJoinAck(void* pHost, CNetData* poNetData);
int EnCodeMailOpenAck2(void* pHost, CNetData* poNetData);
int DeCodeMailOpenAck2(void* pHost, CNetData* poNetData);
int EnCodeTeamCancelJoinNtf(void* pHost, CNetData* poNetData);
int DeCodeTeamCancelJoinNtf(void* pHost, CNetData* poNetData);
int EnCodeVoice2TextAuthReq(void* pHost, CNetData* poNetData);
int DeCodeVoice2TextAuthReq(void* pHost, CNetData* poNetData);
int EnCodeVoice2TextAuthAck(void* pHost, CNetData* poNetData);
int DeCodeVoice2TextAuthAck(void* pHost, CNetData* poNetData);
//===============打包解包函数定义结束===============
typedef int (*EnCodeFuncClientCS)(void *pHost, CNetData* poNetData);
typedef int (*DeCodeFuncClientCS)(void *pHost, CNetData* poNetData);

class CClientCS
{
public:
	CClientCS();
	~CClientCS();
	int BuildProtocol(void* pHost, char *pNet, int iNetSize);

	bool HandleProtocol(char *pNet, int iNetSize, void* pHost);

	static inline unsigned short GetModuleID(void){ return MOUDLE_ID_CS; }

	static inline unsigned short GetProtocolNum(void){ return CS_PROTOCOL_ID_MAX; }

//===============以下协议回调函数需要使用者来实现===============
	virtual void OnRecv_EnterCSNtf(EnterCSNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_PrivateChatNtf(PrivateChatNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RelationChatReq(RelationChatReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_RelationChatAck(RelationChatAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CSSysMsgNtf(CSSysMsgNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TeamInvite(TeamInvite& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TeamInviteNtf(TeamInviteNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TeamInviteResponse(TeamInviteResponse& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TeamKick(TeamKick& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TeamLeave(TeamLeave& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TeamLeaveNtf(TeamLeaveNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TeamLeaderNtf(TeamLeaderNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TeamNtf(TeamNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FriendAddReq(FriendAddReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FriendAddReqVerify(FriendAddReqVerify& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FriendAddReqAck(FriendAddReqAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FriendList(FriendList& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FriendDelReq(FriendDelReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FriendListChg(FriendListChg& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FriendDetailReq(FriendDetailReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FriendDetailAck(FriendDetailAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyJoinReq(FamilyJoinReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyJoinAck(FamilyJoinAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyInviteReq(FamilyInviteReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyInviteVerify(FamilyInviteVerify& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyInviteAck(FamilyInviteAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_GetFamilyInfoReq(GetFamilyInfoReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyNoticeAck(FamilyNoticeAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyMsgAck(FamilyMsgAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyTitlesAck(FamilyTitlesAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyMembersAck(FamilyMembersAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyEnemyAck(FamilyEnemyAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyAllyAck(FamilyAllyAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyJoinListAck(FamilyJoinListAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyTitleModifyReq(FamilyTitleModifyReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyTitleAwardReq(FamilyTitleAwardReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyLeaveOrLastMsgReq(FamilyLeaveOrLastMsgReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyExpellReq(FamilyExpellReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyLeaveNtf(FamilyLeaveNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyDestroyReq(FamilyDestroyReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyAddAllyEnemyReq(FamilyAddAllyEnemyReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyAddAllyVerify(FamilyAddAllyVerify& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyAddAllyAck(FamilyAddAllyAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyDeleteAllyEnemyReq(FamilyDeleteAllyEnemyReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyNoticeEditReq(FamilyNoticeEditReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyNameInputReq(FamilyNameInputReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyNameInputAck(FamilyNameInputAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyListNtfAck(FamilyListNtfAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyInfoNtf(FamilyInfoNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_FamilyBaseInfoAck(FamilyBaseInfoAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ToplistReq(ToplistReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_ToplistAck(ToplistAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MaillistReq(MaillistReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MaillistAck(MaillistAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MailOpenReq(MailOpenReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MailOpenAck(MailOpenAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MailAttachmentGetReq(MailAttachmentGetReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MailAttachmentGetAck(MailAttachmentGetAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MailDeleteReq(MailDeleteReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MailDeleteAck(MailDeleteAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MailSendReq(MailSendReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MailSendAck(MailSendAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SpeakerMsgReq(SpeakerMsgReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_SpeakerMsgNtf(SpeakerMsgNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_NewMailNtf(NewMailNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_Teamoperation(Teamoperation& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TeamJoin(TeamJoin& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TeamJoinNtf(TeamJoinNtf& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TeamJoinResponse(TeamJoinResponse& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TeamLeaveEx(TeamLeaveEx& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TeamKickEx(TeamKickEx& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CancelFamilyJoinReq(CancelFamilyJoinReq& rstProtocol){ rstProtocol; };
	virtual void OnRecv_CancelFamilyJoinAck(CancelFamilyJoinAck& rstProtocol){ rstProtocol; };
	virtual void OnRecv_MailOpenAck2(MailOpenAck2& rstProtocol){ rstProtocol; };
	virtual void OnRecv_TeamCancelJoinNtf(TeamCancelJoinNtf& rstProtocol){ rstProtocol; };
    virtual void OnRecv_Voice2TextAuthReq(Voice2TextAuthReq& rstProtocol) { rstProtocol; };
    virtual void OnRecv_Voice2TextAuthAck(Voice2TextAuthAck& rstProtocol) { rstProtocol; };
private:
	EnCodeFuncClientCS m_EnCodeFuncArray[CS_PROTOCOL_ID_MAX];
	DeCodeFuncClientCS m_DeCodeFuncArray[CS_PROTOCOL_ID_MAX];
};
