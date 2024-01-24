#pragma once

#include "netdata.h"
#include <vector>
#include <set>
#include <memory>
#include <list>
#include <map>
#include <unordered_map>

//===============包含的其他协议文件===============
//===============宏定义开始===============
#define MAX_FRIEND_NUM                 50 //最大好友数量
#define MAX_ALLY_NUM                   20 //行会最大联盟数
#define MAX_ENEMY_NUM                  20 //行会最大敌对数
#define MAX_TITLE_NUM                  20 //行会最大封号数
#define MAX_CUSTITLE_NUM               16 //行会自定义封号数
#define MAX_MAIL_REMAIN_DATE           2592000//邮件保留时间
#define	MAX_ADDITION_NUM               5  //附件种类数量
#define MAX_MAIL_CURRENCY_TYPE_NUM     5  //邮件货币种类
#define MAX_AUCTION_HOUSE_REMAIN_DATE           2592000//拍卖行数据保留时间

//===============宏定义结束===============

//===============数据定义开始===============
#pragma warning( push )
#pragma warning( disable : 4512)
struct KEY_VALUE_PAIR{
	char                      key[32]; //key
	char                      value[256]; //value
};

struct PARAM_INFO{
	unsigned char             type; //数据类型 1=INT8 2=UINT8 3=INT16 4=UINT16 5=INT32 6=UINT32 7=INT64 8=UINT64 9=字符串
	char                      value[1024]; //数据值
};

struct PARAM_INFO2{
	unsigned char             type; //数据类型 1=INT8 2=UINT8 3=INT16 4=UINT16 5=INT32 6=UINT32 7=INT64 8=UINT64 9=字符串
	int                       size; //二进制数据大小
	char                      value[1024]; //数据值
};

struct IntData{
	char                      name[32]; //数据名
	unsigned char             type; //数据类型 1=INT8 2=UINT8 3=INT16 4=UINT16 5=INT32 6=UINT32 7=INT64 8=UINT64
	uint64_t                  value; //数据值
};

struct StrData{
	char                      name[32]; //数据名
	char                      value[256]; //数据值
};

struct BlobData{
	char                      name[32]; //数据名
	int                       size; //二进制数据大小
	unsigned char             buf[262144]; //二进制数据
};

struct ITEM_CFG_VAR
{
	uint32_t                  color = 0;
	uint64_t                  icon = 0;
	uint32_t                  quality = 0;
	uint32_t                  subtype = 0;
	ITEM_CFG_VAR() = default;
};

struct ROLE_DATA_INFO{
	int                       intdatanum; //角色整形数据个数
	IntData                   roleintdata[128]; //角色整形数据
	int                       strdatanum; //字符串数据个数
	StrData                   rolestrdata[64]; //角色字符串数据
	int                       blobdatanum; //角色二进制数据个数
	BlobData                  roleblobdata[16]; //角色二进制数据
	BlobData                  gamedata; //临时保存的玩家二进制数据
	int                       billinyuanbao; //累计充值元宝
	int                       billoutyuanbao; //累计消费元宝
	int                       gameinyuanbao; //累计奖励元宝（绑定）
	int                       gameoutyuanbao; //累计消费的绑定元宝
};

struct ITEM_DB_INFO
{
	uint64_t                  guid              = 0; //guid
	unsigned short            id                = 0; //模板Id
    char                      name[32]          = {0}; //名称
	uint64_t                  role              = 0; //拥有者GUID
	unsigned short            site              = 0; //当前所在的位置
	unsigned short            amount            = 0; //当前的堆叠数量
	int                       durability        = 0; //装备耐久
	int                       max_durability    = 0; //装备耐久
	unsigned short            use_count         = 0; //当前的使用次数
	unsigned char             is_bound          = 0; //是否已绑定
	unsigned int              life              = 0; //绝对时间起始或存活时间
	unsigned char             ext_len           = 0; //扩展数据长度
    unsigned char             ext_data[128]     = {0}; //扩展数据
	ITEM_CFG_VAR              item_cfg_var;           //自定义配置表字段
};
struct CUST_VAR 
{
	uint64_t                    belong = 0;    // 所属ID
	std::string                 name = "";
	std::string                 value = "";
	uint8_t                     type = 0;    // 类型
	uint64_t                    expire = 0;    // 失效时间
	uint8_t						mergeType = 0;
};

struct DYN_ATTR {
	uint16_t                    index = 0;
	uint16_t                    attr = 0;
	int32_t                     value = 0;

	DYN_ATTR() = default;
	DYN_ATTR(uint16_t i, uint16_t a, int32_t v) : index(i), attr(a), value(v) {}

    bool operator == (const DYN_ATTR &other) {
        return index == other.index &&
               attr == other.attr &&
               value == other.value;
    }

    bool operator != (const DYN_ATTR &other) {
        return !operator == (other);
    }
};

using DYN_ATTRS = std::list<DYN_ATTR>;

struct ITEM_DYN_ATTRS {
	uint64_t                    guid = 0;
	DYN_ATTRS                   dyn_attrs;

	ITEM_DYN_ATTRS() = default;
	ITEM_DYN_ATTRS(uint64_t guid, const DYN_ATTRS& attrs) : guid(guid), dyn_attrs(attrs) {}
    ITEM_DYN_ATTRS(uint64_t guid, DYN_ATTRS &&attrs) : guid(guid), dyn_attrs(std::move(attrs)) {}
};

using CUST_VAR_MAP = std::map<std::string, CUST_VAR>;
using CUST_VAR_LIST = std::list<CUST_VAR>;

using CUST_VAR_SP = std::shared_ptr<CUST_VAR>;
using CUST_VAR_SP_MAP = std::map<std::string, CUST_VAR_SP>;
using CUST_VAR_SP_LIST = std::list<CUST_VAR_SP>;
using GUID_TO_CUST_VAR_MAP = std::unordered_map<uint64_t, CUST_VAR_SP_MAP>;
using ITEM_DYN_ATTRS_LIST = std::list<ITEM_DYN_ATTRS>;
using ROLE_DYN_ATTRS = ITEM_DYN_ATTRS;
using ROLE_DYN_ATTRS_LIST = ITEM_DYN_ATTRS_LIST;

struct CONSTANT_CFG
{
	std::string name = "";
	std::string value = "";
};
using CONSTANT_CFG_MAP = std::unordered_map<std::string, CONSTANT_CFG>;

struct CUSTOM_INFO {
	CUSTOM_INFO& operator<<(uint16_t);
	CUSTOM_INFO& operator<<(const std::string&);
	void operator<<(CONSTANT_CFG_MAP& constantCfgMap);
	void operator<<(CUST_VAR_MAP& mCustVars);
	void operator<<(CUST_VAR_SP_MAP& mCustVars);
	void operator<<(CUST_VAR_LIST& mCustVars);
	void operator<<(CUST_VAR_SP_LIST& mCustVars);
	void operator<<(DYN_ATTRS& mDynAttrs);
	void operator>>(CUST_VAR_LIST& mCustVars);
	void operator>>(DYN_ATTRS& mDynAttrs);
	void operator>>(CONSTANT_CFG_MAP& constantCfgMap);
	CUSTOM_INFO& operator>>(uint16_t&);
	CUSTOM_INFO& operator>>(std::string&);
	unsigned short            num = 0; //缓存长度
	unsigned short			  idx = 0;
	char					  buf[65536] = { 0 }; //缓存
};

struct ITEM_INFO
{
	ITEM_DB_INFO               base_info;
	CUSTOM_INFO               custom;
};

struct CHAT_MSG{
	char                      role_name[256]; //角色名字
	char                      message[65535]; //消息内容
};

struct SKILL_INFO{
	uint16_t				  id = 0; //模板Id
	uint8_t					  active = 1; //是否已开启(开关技能有效)
	uint32_t                  proficiency = 0; //熟练度
	char					  cfg[512] = { 0 };
};

struct BUFF_INFO{
	unsigned short            id    = 0; //模板Id
	unsigned short            stack = 0; //堆叠数量
	unsigned int              life  = 0; //存活时间
	uint64_t                  host  = 0; //宿主
};

struct BUFF_INFO_DB {
    uint64_t                  index = 0;
    unsigned short            buffid = 0;
    unsigned int              timeleft = 0;
    uint64_t                  timestamp = 0;
    uint64_t                  actor_id = 0;
	char                      actor_name[32] = { 0 };
    unsigned char             actor_job = 0;
    unsigned int              actor_level = 0;
    unsigned short            actor_skill = 0;
	uint16_t				  stack = 1;
	char                      attr[256] = { 0 };
};

struct SHOP_ITEM_INFO{
	unsigned char             index; //物品在店铺中的格子位置
	unsigned short            id; //物品的模板id
	unsigned short            num; //物品剩于数量 0xffff=物品数量无限制
	unsigned int              value; //物品的价格
};

struct TEAM_MEMBER{
	uint64_t                  guid; //guid
	char                      name[32]; //角色名字
	unsigned short            head; //头像
	unsigned char             is_online; //是否在线
	unsigned int              level; //等级
	unsigned char             job; //职业
	unsigned char             gender; //性别
	uint64_t                  map_code; //地图guid
	char                      map_name[32]; //地图名字
	unsigned short            x; //x
	unsigned short            y; //y
};

struct TEAM_INFO{
	uint64_t                  guid; //队伍 guid
	uint64_t                  leader_guid; //队长 guid
	char                      leader_name[32]; //队长 name
	unsigned char             permission; //1=开启队友招人权限 0=关闭
	int                       member_num; //队员数量
	TEAM_MEMBER               members[100]; //队员信息
};

struct FRIEND_INFO{
	uint64_t                  guid; //好友 guid
	char                      name[32]; //好友名字
	unsigned char             is_online; //是否在线
	short                     friendship; //亲密度
};

struct FRIEND_DETAIL{
	uint64_t                  guid; //好友 guid
	char                      name[32]; //好友名字
	char                      family[32]; //好友工会
	char                      title[32]; //好友封号
	char                      position[32]; //所在地图
	unsigned short            head; //头像
	unsigned char             job; //职业
	unsigned char             gender; //性别
	unsigned int              level; //等级
	short                     friendship; //亲密度
	unsigned char             is_in_team; //是否组队
	unsigned char             members_num; //队伍人数
	unsigned char             is_online; //是否在线
};

struct FRIEND_LIST{
	uint64_t                  guid; //玩家的guid
	int                       friend_num; //好友数量
	FRIEND_INFO               friends[MAX_FRIEND_NUM]; //好友信息
};

struct FRIEND_RELATION{
	uint64_t                  role1_guid; //角色1id
	char                      role1_name[256]; //角色1姓名
	uint64_t                  role2_guid; //角色2id
	char                      role2_name[256]; //角色2姓名
	short                     friendship; //亲密度：0、没有双向好友关系；-1、黑名单
	unsigned char             type; //类型：0、双向好友；1、角色1好友；2、角色2好友
};

struct SERVANT_INFO{
	uint64_t                  servant_guid; //随从的guid
	unsigned short            monster_id; //怪物模板id
	unsigned char             level; //随从等级
	unsigned char             max_level; //最大随从等级
	unsigned short            kill_count; //随从杀怪数
	int                       hp; //血量
	unsigned int              gen_tick; //生成时刻
	unsigned char             type; //随从类型 法师召唤=1 道士召唤=2
	int                       buff_data_len; //buff数据长度
	char                      buff_data[1024]; //buff数据
};

struct QUICK_BAR_INFO{
	unsigned char             type; //0=null 1=item 2=skill
	unsigned char             slot; //槽位
	unsigned short            id; //模板id
	uint64_t                  guid; //物品guid
};

struct QUICK_BAR_LIST_INFO {
	uint64_t                  role_id;
	QUICK_BAR_INFO            quick;
};

struct DGN_BIND_INFO
{
	enum DBI_OPTTYPE
	{
		None = 0,
		Insert = 1,
		Update = 2,
		Delete = 3
	};
	enum DBI_KEYNAME_LEN
	{
		MAX_LEN = 64
	};
	DGN_BIND_INFO()
	{
		roleId = 0;
		memset(dgnKeyName, 0, sizeof(dgnKeyName));
		dgnId = 0;
		optType = DBI_OPTTYPE::Update;
	}
	void operator=(const DGN_BIND_INFO& a)
	{
		roleId = a.roleId;
		memcpy_s(dgnKeyName,sizeof(dgnKeyName),a.dgnKeyName, sizeof(a.dgnKeyName));
		dgnId = a.dgnId;
		optType = a.optType;
	}
	uint64_t                    roleId;
	char						dgnKeyName[MAX_LEN];
	uint64_t					dgnId;
	uint16_t					optType;		//1 新增 2 更新
};

struct MAP_REGION_INFO{
	unsigned char             rg_type; //区域类型 0=安全区 1=摆摊区 2=竞技区 3=复活区
	unsigned short            min_x; //最小x坐标
	unsigned short            max_x; //最大x坐标
	unsigned short            min_y; //最小y坐标
	unsigned short            max_y; //最大y坐标
};

struct FAMILY_TITLE{
	unsigned char             id; //封号ID
	char                      title[32]; //封号名称
};

struct FAMILY_DETAIL{
	uint64_t                  guid; //行会id
	char                      name[32]; //行会名称
	unsigned short            notice_len; //公告长度
	char                      notice[1280]; //行会公告
	unsigned short            titles_num; //封号个数
	FAMILY_TITLE              titles[MAX_TITLE_NUM]; //行会自定义封号，最多MAX_TITLE_NUM个
	unsigned short            msg_len; //行会消息长度
	char                      sysmsgs[12800]; //行会消息，每个消息用'\n'隔开
	unsigned short            ally_count; //行会数量
	uint64_t                  allys[MAX_ALLY_NUM]; //结盟行会
	unsigned short            enemy_count; //行会数量
	uint64_t                  enemys[MAX_ENEMY_NUM]; //敌对行会
	unsigned int              create_time; //创建时间
};

struct FAMILY_INFO_GS{
	uint64_t                  guid; //行会id
	char                      name[32]; //行会名称
	unsigned short            titles_num; //封号个数
	FAMILY_TITLE              titles[MAX_TITLE_NUM]; //行会自定义封号，最多MAX_TITLE_NUM个
	unsigned short            ally_count; //行会数量
	uint64_t                  allys[MAX_ALLY_NUM]; //结盟行会
	unsigned short            enemy_count; //行会数量
	uint64_t                  enemys[MAX_ENEMY_NUM]; //敌对行会
};

struct FAMILY_INFO{
	uint64_t                  guid; //行会id
	char                      name[32]; //行会名称
};

struct MEMBER_INFO{
	uint64_t                  player_guid; //玩家guid
	char                      player_name[32]; //玩家姓名
	unsigned int              level; //等级
	unsigned char             job; //职业
	uint64_t                  family_guid; //行会ID
	unsigned char             title_id; //封号ID, 0、行会成员；1、会长；2、副会长；3、精英、4以上为自定义
	uint64_t                  join_time; //入会时间
	uint64_t                  login_time; //最后一次上线时间
	unsigned char             is_online; //是否在线
    unsigned int              cur_ctrb; //当前贡献度
    unsigned int              totle_ctrb; //累计贡献度
    unsigned int              kills; //杀敌人数
    unsigned int              combat_capability;//战斗力
    unsigned int              reserved1;//预留位1
    unsigned int              reserved2;//预留位2
};

struct MEMBER_INFO_GS{
	uint64_t                  player_guid; //玩家guid
	uint64_t                  family_guid; //行会ID
	unsigned char             title_id; //封号ID, 0、行会成员；1、会长；2、副会长；3、精英、4以上为自定义
	unsigned int              cur_ctrb; //当前贡献度
	unsigned int              totle_ctrb; //累计贡献度
	unsigned int              join_time; //入会时间
};

struct APPLICANTS_INFO{
	uint64_t                  player_guid; //玩家guid
	char                      player_name[32]; //玩家姓名
	unsigned int              level; //等级
	unsigned char             job; //职业
};

struct ROLE_FORBIDTALK_INFO{
	char                      role_name[32]; //被禁言玩家的名字
	char                      end_forbid_time[256]; //禁言到期时间
	char                      describe[256]; //被禁原因
	unsigned char             type; //类型, 1 文字禁言 2 语音禁言 3 文字和语音禁言
};

struct FAMILY_APPLY_INFO{
	uint64_t                  guid; //行会id
	char                      name[32]; //行会名称
	char                      leader_name[32]; //会长名
	unsigned int              members_num; //行会人数
	char                      hold_place[32]; //占有城堡地点
	unsigned char             is_applied; //是否申请过
    char                      family_manifesto[100];//--行会宣言
    uint64_t                  family_create_time;//帮会创建时间
    unsigned int              family_level; //行会等级
    unsigned int              reserved1;//预留位1
    unsigned int              reserved2;//预留位2
};

struct FAMILY_WAR_INFO{
	uint64_t				  guid = 0;	//guid
	char                      name[32]; //行会名称
};

struct CASTLE_INFO{
	char                      name[32]; //城堡名称
	unsigned char             is_start; //攻城战是否开始
	unsigned int              start_time; //攻城战开始时间
	unsigned int              duration; //攻城战持续时间
	char                      own_family[32]; //所属行会
	char                      attack_families[4096]; //攻方行会
	char                      dst_map[32]; //所属地图
	char                      basilica_map[32]; //皇宫地图
	CUSTOM_INFO               custom; //自定义数据
	unsigned char             state; //system use only
};

using GUILD_ID_LIST = std::vector<uint64_t>;
using GUILD_ID_SET = std::set<uint64_t>;

struct GUILD_INFO {
    uint64_t                    id              = 0;        // 行会ID
    std::string                 name;                       // 行会名
    uint16_t                    level           = 0;        // 行会等级
    std::string                 manifesto;                  // 宣言
    std::string                 notice;                     // 公告
    uint64_t                    ctime           = 0;        // 创建时间
    uint64_t                    creator_id      = 0;        // 创建者ID
    std::string                 creator_name;               // 创建者昵称
    uint64_t                    chairman_id     = 0;        // 会长ID
    std::string                 chairman_name;              // 会长昵称
	uint32_t                    autojoin_level = 0;			// 角色达到等级申请自动加入
    GUILD_ID_LIST               allies;                     // 结盟行会
    GUILD_ID_LIST               enemies;                    // 敌对行会
};

using SPGUILD = std::shared_ptr<GUILD_INFO>;
using GUILD_MAP = std::map<uint64_t, SPGUILD>;

struct GUILD_MEMBER {
    uint64_t                    player_id       = 0;        // 玩家ID
    std::string                 player_name;                // 玩家昵称
    uint8_t                     job             = 0;        // 职业
    uint32_t                    level           = 0;        // 等级
    uint64_t                    guild_id        = 0;        // 行会ID
    uint8_t                     title           = 0;        // 封号ID, 0、行会成员；1、会长；2、副会长；3、精英、4以上为自定义
    uint8_t                     new_title       = 0;        // 新封号
    uint64_t                    join_time       = 0;        // 入会时间
    uint64_t                    login_time      = 0;        // 最后一次上线时间
    uint32_t                    cur_contrib     = 0;        // 当前贡献度
    uint32_t                    total_contrib   = 0;        // 累计贡献度
    uint32_t                    kills           = 0;        // 杀敌人数
    uint32_t                    combat_cap      = 0;        // 战斗力
    uint8_t                     status          = 0;        // 状态, 0 - 正常, 1 - 被踢
    std::string                 kicked_by;                  // 踢人者名
    bool                        online          = false;    // 是否在线
};

using SPGUILD_MEMBER = std::shared_ptr<GUILD_MEMBER>;
using GUILD_MEMBER_LIST = std::list<SPGUILD_MEMBER>;
using GUILD_MEMBER_MAP = std::unordered_map<uint64_t, SPGUILD_MEMBER>;

struct GUILD_APPLY_INFO {
    uint64_t                    player_id   = 0;    // 玩家ID
    std::string                 player_name;        // 玩家姓名
    uint32_t                    level       = 0;    // 等级
    uint8_t                     job         = 0;    // 职业
    uint64_t                    guild_id    = 0;    // 申请行会ID
    uint64_t                    apply_time  = 0;    // 申请时间
    uint64_t                    login_time  = 0;    // 上次登录时间
    uint8_t                     status      = 0;    // 申请状态
    std::string                 handled_by;         // 受理人
};

using SPGUILD_APPLICANT = std::shared_ptr<GUILD_APPLY_INFO>;
using GUILD_APPLICANT_LIST = std::list<SPGUILD_APPLICANT>;

struct GUILD_DATA
{
    GUILD_MEMBER_LIST           members;
    GUILD_APPLICANT_LIST        applicants;
	GUILD_ID_SET				war;
};

using GUILD_DATA_MAP = std::map<uint64_t, GUILD_DATA>;

struct MALL_ITEM_INFO{
	unsigned int              item_index = 0; //商品ID
	unsigned short            item_id = 0; //物品的模板id
	unsigned char             is_hot = 0; //是否热销
	unsigned short            num = 0; //物品剩于数量 0xffff=物品数量无限制
	unsigned char             value_type = 0; //价格类型：0:元宝，1:绑元，2:积分，3:金币，4:绑金
	unsigned int              price = 0; //原价
	unsigned int              discount = 0; //折扣价
	unsigned short            limits_type = 0;//限购类型
	unsigned short            limits_time = 0;//限购时间
};

struct MALL_ITEM_DETAIL{
	unsigned int              item_index = 0; //商品ID
	unsigned short            item_id = 0; //物品的模板id
	unsigned short            image_desc = 0; //商品图片描述
	char                      text_desc[256]; //商品文字描述
	MALL_ITEM_DETAIL() 
	{
		memset(text_desc, 0, _countof(text_desc));
	}
};

struct MALL_ITEM_INFO_BASE
{
	uint64_t playerguid = 0;
	uint32_t item_idx = 0;
	uint32_t num = 0;
};

struct TOPLIST_INFO{
	char                      player_name[32]; //玩家姓名
	unsigned int              level; //等级
	unsigned char             job; //职业
	unsigned char             gender; //性别
	char                      ext1[32]; //扩展1
	char                      ext2[32]; //扩展2
	char                      ext3[32]; //扩展3
};

struct QUEST_HUNTING_INFO{
	unsigned short            id; //怪物模板ID
	unsigned short            count; //杀怪计数变量
	unsigned short            required; //杀怪需求总量
};

struct QUEST_HUNTLEVEL_INFO{
    unsigned short            id; //怪物模板ID
	unsigned short            min_num; //怪物有效最小等级
	unsigned short            max_num; //杀怪有效最大等级
	unsigned short            count; //杀怪计数变量
	unsigned short            required; //杀怪需求总量
};

struct QUEST_ITEM_INFO{
	unsigned short            id; //物品模板ID
	unsigned short            count; //物品计数变量
	unsigned short            required; //物品需求总量
};

struct QUEST_NPC_INFO{
	unsigned short            id; //Npc模板ID
	unsigned short            count; //Npc计数变量
};

struct MAIL_HEADER_INFO{
	uint64_t                  mail_id; //邮件ID
	char                      title[64];
	unsigned int              send_time; //发件时间
	unsigned int              left_time; //剩余时间
	char                      sender[32]; //发件人
	unsigned int              status; //邮件状态
	unsigned char             type; //邮件类型 1、玩家邮件；0、系统邮件
};

struct MAIL_BODY_INFO{
	char                      text[400]; //邮件正文
	int                       gold; //金币数量
	int                       yuanbao; //元宝数量
	unsigned char             count; //物品数量
	ITEM_INFO                 items[5]; //物品ID列表
};

struct MAIL_BODY_INFO2{
	char                      text[400]; //邮件正文
	int64_t                   gold; //金币数量
	int64_t                   yuanbao; //元宝数量
	int64_t                   integral; //积分数量
	int64_t                   bind_gold;
	int64_t                   bind_yunabao;
	unsigned char             count; //物品数量
	ITEM_INFO                 items[5]; //物品ID列表
	MAIL_BODY_INFO2() :gold(0), yuanbao(0), integral(0) , count(0), bind_gold(0), bind_yunabao(0) {
		memset(text, 0, sizeof(text));
		memset(items, 0, sizeof(items));
	}
};

struct ADDITION_ITEM_INFO
{
	char         item_name[32];
	uint16_t     item_id = 0;
	uint64_t     item_guid;
	uint16_t     count;
	uint16_t     bind_status;
	ADDITION_ITEM_INFO() :item_id(0), item_guid(0),count(0), bind_status(0) {
		memset(item_name, 0, sizeof(item_name));
	}
};

struct CURRENCY_INFO
{
	uint16_t type;
	int64_t  num;
	CURRENCY_INFO() :type(0), num(0) {};
};

struct MAIL_INFO
{
	uint64_t                  playerguid = 0;
	uint64_t                  mail_id;
	char                      title[64];
	char                      text[400];
	unsigned int              status;          //读取与领取状态
	CURRENCY_INFO             mail_currency_info[MAX_MAIL_CURRENCY_TYPE_NUM];
	uint16_t                  currency_type_num;
	ADDITION_ITEM_INFO        mail_addition_item_info[MAX_ADDITION_NUM];
	uint16_t                  addition_item_num ;
	uint16_t                  type;            //0 系统 1 寄售行 2 GM 
	char                      sendername[32];
	uint64_t                  send_timesmap;
	MAIL_INFO() :playerguid(0), mail_id(0), status(0), currency_type_num(0), addition_item_num(0), type(0), send_timesmap(0) {
		memset(title, 0, sizeof(title));
		memset(text, 0, sizeof(text));
		memset(sendername, 0, sizeof(sendername));
	};

	int64_t GetCurrencyNum(uint16_t type)
	{
		for (auto i = 0; i < _countof(mail_currency_info); ++i)
		{
			if (type == mail_currency_info[i].type)
			{
				return mail_currency_info[i].num;
			}
		}
		return 0;
	};
};

struct Mail_Info_Status {
	uint64_t mailid;
	uint32_t status;
	Mail_Info_Status() :mailid(0), status(0) {}
};

struct DELEGATE_SELL_ITEM{
	uint64_t                  id                = 0;    //ID,交易id
	uint64_t          		  seller_guid       = 0;	//出售者guid
    char                      seller[32]        = {0};  //出售者
	unsigned int              item_value        = 0;    //物品单价
	unsigned int              item_unit         = 0;    //物品单位数量
	unsigned int              time              = 0;    //下架剩余时间
	ITEM_INFO                 item;                     //物品详细信息
	unsigned char             value_type        = 0;    //价格类型：0、金币；1、元宝；2、积分 
	unsigned int              td_time			= 0;	//委托时长
	unsigned int              trade_time		= 0;	//委托开始时间

};
/*
struct DELEGATE_BUY_ITEM{
	uint64_t                  id; //ID
	char                      buyer[32]; //收购者
	unsigned int              time; //下架剩余时间
	char                      item_name[32]; //物品名称
	unsigned int              item_num; //求购数量
	unsigned int              item_value; //物品单价
	unsigned int              item_unit; //物品单位数量
	unsigned char             value_type; //价格类型：0、金币；1、元宝；2、积分
};
*/
/*
struct DELEGATE_INFO
{
	DELEGATE_INFO()
	{
		memset(this, 0, sizeof(DELEGATE_INFO));
		item_unit = 1;
	}
	uint64_t          			id;				//ID
	uint64_t          			time;			//委托时间
	uint64_t          			role_id;		//roleid
	char						role_name[32];	//角色名
	uint64_t          			item_guid;		//物品guid
	unsigned int				item_id;		//物品id
	char						item_name[32];	//物品名
	unsigned int				item_num;		//剩余数量
	unsigned int				item_value;		//物品单价
	unsigned int				item_unit;		//物品单位数量
	unsigned char				value_type;		//价格类型：0、金币；1、元宝
	unsigned char				trade_type;		//委托类型：0、出售；1、收购
};
*/
struct CAMPAIGN_INFO{
	unsigned int              id; //活动id
	char                      name[256]; //活动名称
	unsigned char             type; //活动类型 4：每周执行 5：每天执行
	char                      begin[256]; //开始时间
	char                      end[256]; //结束时间
	unsigned int              minlevel; //最小等级
	unsigned int              maxlevel; //最大等级
	unsigned char             count; //活动次数
	unsigned char             max_count; //最大活动次数
	unsigned char             status; //活动状态 1：未开始 2：进行中 3：已结束
};

struct FAMILY_ALLY_INFO{
	char                      family1[32]; //行会1
	char                      family2[32]; //行会2
};

//struct TITLE_INFO{
//	unsigned short            id; //模板Id
//	unsigned int              life; //存活时间
//};

struct TAOBAO_ITEM_INFO{
	ITEM_INFO                 item; //物品信息
	unsigned int              value; //物品的价格
};

struct MAP_INFO{
	unsigned short            width; //width
	unsigned short            height; //height
	char                      name[32]; //name
};

struct TABLE_INFO{
	unsigned int              version; //版本号
	int                       lines; //表行数
	int                       size; //数据长度
	char                      name[32]; //name
};

struct TOPLIST_ITEM_INFO{
	unsigned char             size; //数据长度
	ITEM_INFO                 item[100]; //物品数据
};

struct DataInfoDoNotUse{
	const unsigned short      moudleid;
	const unsigned short      protocolid;
	DataInfoDoNotUse():moudleid(15),protocolid(0){}
};

struct VIP_ITEM{
	unsigned short            id; //道具ID
	unsigned char             enable; //0未激活 1VIP已激活 2单个购买
	unsigned int              remain; //如果单个购买，显示剩余时间
	unsigned int              price; //购买价格
};

struct VIP_LEVEL{
	unsigned short            level; //VIP等级
	unsigned int              price; //购买价格
	unsigned int              times; //VIP持续时间
};

struct QUEST_STATE_ITEM{
	char                      title[256]; //标题
	unsigned short            template_id; //任务模板id
	unsigned char             state; //状态，1：任务可交，2：任务可接，3：任务已接不可交
};

struct QUEST_STATE_INFO{
	unsigned short            num; //数量
	QUEST_STATE_ITEM          item[100]; //任务状态项
};

struct GLORY_STATE{
	unsigned short            template_id; //成就模板id
	unsigned char             state; //状态，1：未完成，2：已完成，3：奖励已领取
};

struct ROLE_BRIEF_INFO{
	uint64_t                  guid; //角色GUID
	char                      name[32]; //角色名
	unsigned short            head; //头像
	unsigned int              level; //等级
	unsigned char             status; //角色状态 0=从未进过游戏,1=正常,2=角色已删除3=角色永久删除4=角色没有进过游戏就已删除
	unsigned char             job; //职业
	unsigned char             hair; //头发
	unsigned char             hair_color; //头发颜色
	unsigned char             gender; //性别
	unsigned short            weapon; //武器
	unsigned short            clothes; //衣服
	unsigned int              gssvrid; //角色所在gs的server id
	unsigned int              vipLevel; //vip等级
	unsigned char             is_lock;  // 是否被封禁
	uint64_t				  updateTime = 0;
	ROLE_BRIEF_INFO() 
	{
		memset(this, 0, sizeof(ROLE_BRIEF_INFO));
	}
};

struct Point {
	int16_t						x			= 0;
	int16_t						y			= 0;

	Point() = default;
	Point(int16_t x_, int16_t y_) : x(x_), y(y_) {}
	bool operator== (const Point &rhs) const { return (x == rhs.x) && (y == rhs.y); }
};

struct AUTO_PICKUP {
	uint8_t						mode		= 0;	// 1 - 周围，2 - 指定点
	uint8_t					    radius		= 0;
	uint8_t						numpos		= 0;
	Point						relpos[AUTO_PICKUP_MAXPOS];
    uint16_t                    interval    = 0;    // 捡物间隔ms
};

struct ROLE_SETTINGS {
	AUTO_PICKUP					auto_pickup;

	bool Comp(const ROLE_SETTINGS& data) {
		if (auto_pickup.mode != data.auto_pickup.mode)return false;
		if (auto_pickup.radius != data.auto_pickup.radius)return false;
		if (auto_pickup.numpos != data.auto_pickup.numpos)return false;
		for (int i = 0; i < auto_pickup.numpos; ++i) {
			if (auto_pickup.relpos[i].x != data.auto_pickup.relpos->x || auto_pickup.relpos[i].y != data.auto_pickup.relpos->y)return false;
		}
		if (auto_pickup.interval != data.auto_pickup.interval)return false;
		return true;
	}
};

struct ROLE_EXTRA_INFO{
    uint64_t                  login_time;
    uint32_t                  hp;
    uint32_t                  mp;
    uint64_t                  exp;
    uint16_t                  mapid;
    uint16_t                  posx;
    uint16_t                  posy;
    uint8_t                   dir;
	uint64_t				  gold;						//金币
	uint64_t				  bindGold;					//绑定金币
	uint64_t				  ingot;					//元宝
	uint64_t				  bindIngot;				//绑定元宝
	uint64_t				  integral;					//积分
	uint64_t				  depositGold;				//仓库金币
	uint64_t				  innerForceExp;			//内功经验
    uint8_t                   atkMode;                  //攻击模式
    uint16_t                  birthMap;                 //出生地图ID
    uint16_t                  rebirthMap;               //重生地图ID
    uint16_t                  redNameMap;               //红名重生地图ID
	uint16_t                  rolePk;				    //人物PK值
	uint32_t                  modelID;                  //模型id
};

struct QUEST_INFO {
    uint16_t                  pre_quest;                // 前一个任务ID
    uint16_t                  cur_quest;                // 当前任务ID
    uint32_t                  timeleft;                 // 任务剩余时间s
    uint64_t                  timestamp;                // 上次中断时间戳s
};

struct QUEST_ACHIEVE {
    uint16_t                  quest;                    // 任务ID
    uint8_t                   achev_type;               // 完成类型：1与NPC对话|2击杀怪物|3收集道具|4角色等级判定|5角色装备收集判断|6脚本编号|7移动到指定地图指定坐标
    uint16_t                  achev_id;
    int32_t                   achev_num;
};

struct DUMMY_BRIEF_INFO{
	uint64_t                  master_guid; //角色GUID
};

struct CHECK_BUFF{
	char                      md5_data[32]; //md5
};

struct EQUIP_INFO{
	uint16_t                    site            = 0;    //位置
	uint16_t                    id              = 0;    //模板Id
};

struct DELEGATE_BUY_ITEM2{
	uint64_t                  id                = 0; //ID
	uint64_t          		  buyer_guid        = 0;	//收购者guid
    char                      buyer[32]         = {0}; //收购者
	unsigned int              time              = 0; //下架剩余时间
    char                      item_name[32]     = {0}; //物品名称
	unsigned short            item_template_id  = 0; //物品模板ID
	unsigned int              item_num          = 0; //求购数量
	unsigned int              item_value        = 0; //物品单价
	unsigned int              item_unit         = 0; //物品单位数量
	unsigned char             value_type        = 0; //价格类型：0、金币；1、元宝；2、积分
	unsigned int              td_time			= 0; //委托时长
	unsigned int              trade_time		= 0; //委托开始时间
};

struct MOBA_ROOM_INFO{
	int                       room_id; //room id
	char                      room_name[32]; //房间名字
	unsigned short            max_num; //每边的最大人数
	unsigned short            cur_num; //当前人数
	unsigned char             state; //房间状态 1=准备 2=游戏中 3=游戏结束
	unsigned char             lock; //1=有密码 0=无密码
	unsigned short            map_id; //地图id
	unsigned short            room_mode; //房间模式
};

struct MOBA_ROOM_MEMBER_INFO{
	char                      name[32]; //玩家昵称
	uint64_t                  guid; //玩家guid
	unsigned char             camp; //玩家阵营 1=red 2=blue
	unsigned char             job; //角色职业
	unsigned char             site; //玩家位置 0=第一个位置
	unsigned char             host; //是否是房主
	unsigned char             ready; //是否准备完成
};

struct CUST_LIST_INFO
{
	uint64_t guid = 0;
	int      type = 0;
	int64_t  value = 0;
	uint64_t stamp = 0;
	char     desc[1000] = { 0 };
	uint16_t ranking = 0;
	CUST_LIST_INFO() {};
	CUST_LIST_INFO(uint64_t _guid, int _type, int64_t _value, uint64_t _stamp, const char* _desc) :guid(_guid), type(_type), value(_value), stamp(_stamp) {
		memcpy_s(desc, sizeof(desc), _desc, sizeof(_desc));
	};
};

using CUST_DATA_SP = std::shared_ptr<CUST_LIST_INFO>;

struct MONITOR_CHAT_INFO {
	uint64_t      user_id;
	char          user_name[32];
	uint64_t      to_user_id;
	char          to_user_name[32];
	uint16_t      channel;
	char          guild[32];
	char          stamp[100];
	char          content[65535];
};

using MONITOR_CHAT_INFO_SP = std::shared_ptr<MONITOR_CHAT_INFO>;
using MONITOR_CHAT_INFO_SP_LIST = std::list<MONITOR_CHAT_INFO_SP>;

struct PLATFORM_CREATE_ROLE_INFO
{
	std::string game_id = "";
	std::string region_id = "";
	std::string server_id = "";
	std::string role_id = "";
	std::string channel = "";
	std::string user_id = "";
};

using SP_BUY_DELEGATE = std::shared_ptr<DELEGATE_BUY_ITEM2>;
using SP_BUY_DELEGATE_MAP = std::map<uint64_t, SP_BUY_DELEGATE>;
using SP_BUY_DELEGATE_LIST = std::list<SP_BUY_DELEGATE>;
using SP_SELL_DELEGATE = std::shared_ptr<DELEGATE_SELL_ITEM>;
using SP_SELL_DELEGATE_MAP = std::map<uint64_t, SP_SELL_DELEGATE>;
using SP_SELL_DELEGATE_LIST = std::list<SP_SELL_DELEGATE>;
//using SPDELEGATE = std::shared_ptr<DELEGATE_INFO>;
//using DELEGATE_MAP = std::map<uint64_t, SPDELEGATE>;

using DGN_BIND_INFO_LIST = std::list<DGN_BIND_INFO>;

using QUICK_BAR_INFO_LIST = std::list<QUICK_BAR_INFO>;

struct Hated_Value
{
	float hated_value = 0;
	uint64_t timer = 0;
};

struct AUCTION_HOUSE_ITEM_INFO
{
	enum auction_house_item_status
	{
		auction_status_type_wait   = 0,
		auction_status_type_ing    = 1,
		auction_status_type_end    = 2,
		auction_status_type_passin = 3,
	};
	char           item_name[32];
	uint16_t       item_num;
	int            item_price;
	uint8_t        currency_type;
	uint64_t       start_time;
	uint64_t       keep_time;
	uint8_t        status;
	uint64_t       orderID;
	uint64_t       ownerID;
	char           ownerName[32];
	AUCTION_HOUSE_ITEM_INFO():item_num(0), item_price(0), start_time(0), keep_time(0),status(0),orderID(0), ownerID(0)
	{
		memset(item_name, 0, sizeof(item_name));
		memset(ownerName, 0, sizeof(ownerName));
	}
};

struct LOGIN_IP_DATA
{
	uint32_t ip    = 0;
	uint8_t  type  = 0;
	LOGIN_IP_DATA() = default;
};

struct PROHIBIT_CHAT_DATA
{
	uint64_t playerguid = 0;
	uint64_t time = 0;
	PROHIBIT_CHAT_DATA() = default;
};

using AUCTION_HOUSE_ITEM_INFO_LIST = std::map<uint64_t, AUCTION_HOUSE_ITEM_INFO>;


struct WANTED_BY                                                // 悬赏发起者信息
{
    uint32_t                    index           = 0;            // 数据库中的序号
    uint64_t                    guid            = 0;            // 悬赏发起者GUID
    std::string                 name;                           // 悬赏发起者名字
    std::string                 desc;                           // 描述
    uint32_t                    bounty          = 0;            // 悬赏金额
    uint64_t                    ptime           = 0;            // 发起悬赏时间
};

using WANTED_BY_SP = std::shared_ptr<WANTED_BY>;
using WANTED_BY_SP_LIST = std::list<WANTED_BY_SP>;

struct WANTED                                                   // 被悬赏者信息
{
    uint64_t                    guid            = 0;            // 被悬赏者GUID
    std::string                 name;                           // 被悬赏者名字
    WANTED_BY_SP_LIST           wanted_by_list;                 // 悬赏发起者列表
};

using WANTED_SP = std::shared_ptr<WANTED>;
using WANTED_SP_LIST = std::list<WANTED_SP>;

struct GOODS_ISSUE_RECORD                                       // 玩家充值购买商品发放记录
{
    char                        order_no[ORDER_NO_BUFLEN] = {0};           // 订单号
    uint64_t                    role_guid       = 0;            // 角色GUID
    uint8_t                     pay_type        = 0;            // 充值类型
    uint32_t                    goods_id        = 0;            // 充值表档位ID
    uint32_t                    goods_num       = 0;            // 商品数量
    uint32_t                    pay_amount      = 0;            // 充值金额
    uint8_t                     issued          = 0;            // 是否已发货
	uint8_t                     isPost          = 0;            // 是否已上报
};

struct REBATE_MONEY_RECORD                                       // 玩家删档返利发放记录
{
	uint8_t						be_load = 0;
	int64_t						inc_id = 0;						// 加快set flag时查询效率
	uint64_t					account_id = 0;					// id
	char						account_name[256] = { 0 };		// 账号
	int64_t						rebate_money = 0;				// 返利金额
	uint8_t                     is_use = 0;						// 是否已发放
};

struct MESSAGE_INFO
{
	char       message[65535];
	char       font_color[32];
	char       background_color[32];
	int32_t    type                   = 0;
	uint32_t   size                   = 0;
	uint8_t    comp                   = 0;
	uint16_t   display_type           = 0;
	uint8_t    scroll_times           = 0;
	uint64_t   srcGuid                = 0;
	uint64_t   dstGuid                = 0;
	uint8_t    isAppearSrcName        = 0;
	uint16_t   posx                   = 0;
	uint16_t   posy                   = 0;
	uint16_t   marqueeType            = 0;
	MESSAGE_INFO() {
		memset(message, 0, _countof(message));
		memset(font_color, 0, _countof(font_color));
		memset(background_color, 0, _countof(background_color));
	}
	void Clear() {
		memset(this, 0, sizeof(MESSAGE_INFO));
	}
};
static MESSAGE_INFO gMESSAGE_INFO;

struct RELATION_CHAT_NTF
{
	uint8_t     type                 = 0;    // 1：当前 2：队伍 3：公会 4：世界 5：小喇叭 9: 阵营 12：全服
	CHAT_MSG    chat_message;                // 角色名为源角色的名字
	uint8_t     scroll_times         = 0;
	char        font_color[32];
	char        background_color[32];
	uint32_t    size                 = 0;    // 压缩后包大小
	uint8_t     comp                 = 0;    // 是否压缩
};

struct SYSTEN_MESSAGE_NTF
{
	char      message[65535];
	char      font_color[32];
	char      background_color[32];
	uint32_t  size                         = 0;
	uint8_t   comp                         = 0;

	SYSTEN_MESSAGE_NTF() {
		memset(message, 0, _countof(message));
		memset(font_color, 0, _countof(font_color));
		memset(background_color, 0, _countof(background_color));
	}
};

struct SCENCE_DIALOG_NTF
{
	char       message[65535];
	char       font_color[32];
	char       background_color[32];
	uint64_t   objGuid                      = 0;
	uint8_t    isAppearSrcName              = 0;
	uint32_t   size                         = 0;
	uint8_t    comp                         = 0;

	SCENCE_DIALOG_NTF() {
		memset(message, 0, _countof(message));
		memset(font_color, 0, _countof(font_color));
		memset(background_color, 0, _countof(background_color));
	}
};

struct SCROLL_TEXT
{
	char      message[65535];
	char      font_color[32];
	char      background_color[32];
	uint8_t   scroll_times               = 0;
	uint32_t  size                       = 0;
	uint8_t   comp                       = 0;
	uint8_t   type                       = 0;

	SCROLL_TEXT() {
		memset(message, 0, _countof(message));
		memset(font_color, 0, _countof(font_color));
		memset(background_color, 0, _countof(background_color));
	}
};

struct CUST_MSG_NTF
{
	char      message[65535];
	char      font_color[32];
	char      background_color[32];
	uint32_t  size         = 0;
	uint8_t   comp         = 0;
	uint16_t  display_type = 0;  // 1 聊天框 2 跑马灯 3 公告 4（1&2） 5（1&3） 6（2&3） 7（1&2&3）
	uint8_t   scroll_times = 0;
	CUST_MSG_NTF() {
		memset(message, 0, _countof(message));
		memset(font_color, 0, _countof(font_color));
		memset(background_color, 0, _countof(background_color));
	}
};

struct TITLE_INFO {
	uint32_t         Id        = 0;         // id
	uint8_t          isWear    = 0;         // 是否穿戴
	uint64_t         addTime   = 0;         // 添加时间
	uint32_t         lifeTime  = 0;         // 存在时间
	uint32_t         timeLimit = 0;         // 存在时限
};

using SP_TITLE_INFO = std::shared_ptr<TITLE_INFO>;

struct RedemptionCodeInfo
{
	uint64_t userid = 0;
	uint64_t guid = 0;
	uint8_t  type = 0;
	char     code[50];
	char     name[50];
	RedemptionCodeInfo() {
		memset(code, 0, _countof(code));
		memset(name, 0, _countof(code));
	}
};

struct BossInfo {
	uint32_t tempID = 0;
	uint64_t guid = 0;
	uint32_t mapID = 0;
	std::string mapName;
	uint64_t reliveTime = 0;
	uint64_t lastGUID = 0;
	BossInfo(uint32_t _temp,uint64_t _guid,uint32_t _mapID,uint64_t _reliveTime,std::string _mapName, uint64_t _lastGUID):
		tempID(_temp),guid(_guid),mapID(_mapID),reliveTime(_reliveTime),mapName(_mapName),lastGUID(_lastGUID)
	{
	}
};

struct EffectPoint {
	uint16_t x       = 0;
	uint16_t y       = 0;
	uint32_t effect  = 0;
};

struct TrapPointEffect {
	uint32_t SkillID = 0;
	uint32_t timerID = 0;
	EffectPoint data;
};

#pragma warning( pop ) 
//===============数据定义结束===============
//===============打包解包函数定义开始===============
int EnCodeKEY_VALUE_PAIR(void* pHost, CNetData* poNetData);
int DeCodeKEY_VALUE_PAIR(void* pHost, CNetData* poNetData);
int EnCodePARAM_INFO(void* pHost, CNetData* poNetData);
int DeCodePARAM_INFO(void* pHost, CNetData* poNetData);
int EnCodePARAM_INFO2(void* pHost, CNetData* poNetData);
int DeCodePARAM_INFO2(void* pHost, CNetData* poNetData);
int EnCodeIntData(void* pHost, CNetData* poNetData);
int DeCodeIntData(void* pHost, CNetData* poNetData);
int EnCodeStrData(void* pHost, CNetData* poNetData);
int DeCodeStrData(void* pHost, CNetData* poNetData);
int EnCodeBlobData(void* pHost, CNetData* poNetData);
int DeCodeBlobData(void* pHost, CNetData* poNetData);
int EnCodeITEM_CFG_VAR(void* pHost, CNetData* poNetData);
int DeCodeITEM_CFG_VAR(void* pHost, CNetData* poNetData);
int EnCodeROLE_DATA_INFO(void* pHost, CNetData* poNetData);
int DeCodeROLE_DATA_INFO(void* pHost, CNetData* poNetData);
int EnCodeCUSTOM_INFO(void* pHost, CNetData* poNetData);
int DeCodeCUSTOM_INFO(void* pHost, CNetData* poNetData);
int EnCodeITEM_DB_INFO(void* pHost, CNetData* poNetData);
int DeCodeITEM_DB_INFO(void* pHost, CNetData* poNetData);
int EnCodeITEM_INFO(void* pHost, CNetData* poNetData);
int DeCodeITEM_INFO(void* pHost, CNetData* poNetData);
int EnCodeLOGTRADE_DATA(void* pHost, CNetData* poNetData);
int DeCodeLOGTRADE_DATA(void* pHost, CNetData* poNetData);
int EnCodeCHAT_MSG(void* pHost, CNetData* poNetData);
int DeCodeCHAT_MSG(void* pHost, CNetData* poNetData);
int EnCodeSKILL_INFO(void* pHost, CNetData* poNetData);
int DeCodeSKILL_INFO(void* pHost, CNetData* poNetData);
int EnCodeBUFF_INFO(void* pHost, CNetData* poNetData);
int DeCodeBUFF_INFO(void* pHost, CNetData* poNetData);
int EnCodeBUFF_INFO_DB(void* pHost, CNetData* poNetData);
int DeCodeBUFF_INFO_DB(void* pHost, CNetData* poNetData);
int EnCodeSHOP_ITEM_INFO(void* pHost, CNetData* poNetData);
int DeCodeSHOP_ITEM_INFO(void* pHost, CNetData* poNetData);
int EnCodeTEAM_MEMBER(void* pHost, CNetData* poNetData);
int DeCodeTEAM_MEMBER(void* pHost, CNetData* poNetData);
int EnCodeTEAM_INFO(void* pHost, CNetData* poNetData);
int DeCodeTEAM_INFO(void* pHost, CNetData* poNetData);
int EnCodeFRIEND_INFO(void* pHost, CNetData* poNetData);
int DeCodeFRIEND_INFO(void* pHost, CNetData* poNetData);
int EnCodeFRIEND_DETAIL(void* pHost, CNetData* poNetData);
int DeCodeFRIEND_DETAIL(void* pHost, CNetData* poNetData);
int EnCodeFRIEND_LIST(void* pHost, CNetData* poNetData);
int DeCodeFRIEND_LIST(void* pHost, CNetData* poNetData);
int EnCodeFRIEND_RELATION(void* pHost, CNetData* poNetData);
int DeCodeFRIEND_RELATION(void* pHost, CNetData* poNetData);
int EnCodeSERVANT_INFO(void* pHost, CNetData* poNetData);
int DeCodeSERVANT_INFO(void* pHost, CNetData* poNetData);
int EnCodeMAP_REGION_INFO(void* pHost, CNetData* poNetData);
int DeCodeMAP_REGION_INFO(void* pHost, CNetData* poNetData);
int EnCodeFAMILY_TITLE(void* pHost, CNetData* poNetData);
int DeCodeFAMILY_TITLE(void* pHost, CNetData* poNetData);
int EnCodeFAMILY_DETAIL(void* pHost, CNetData* poNetData);
int DeCodeFAMILY_DETAIL(void* pHost, CNetData* poNetData);
int EnCodeFAMILY_INFO_GS(void* pHost, CNetData* poNetData);
int DeCodeFAMILY_INFO_GS(void* pHost, CNetData* poNetData);
int EnCodeFAMILY_INFO(void* pHost, CNetData* poNetData);
int DeCodeFAMILY_INFO(void* pHost, CNetData* poNetData);
int EnCodeMEMBER_INFO(void* pHost, CNetData* poNetData);
int DeCodeMEMBER_INFO(void* pHost, CNetData* poNetData);
int EnCodeMEMBER_INFO_GS(void* pHost, CNetData* poNetData);
int DeCodeMEMBER_INFO_GS(void* pHost, CNetData* poNetData);
int EnCodeAPPLICANTS_INFO(void* pHost, CNetData* poNetData);
int DeCodeAPPLICANTS_INFO(void* pHost, CNetData* poNetData);
int EnCodeROLE_FORBIDTALK_INFO(void* pHost, CNetData* poNetData);
int DeCodeROLE_FORBIDTALK_INFO(void* pHost, CNetData* poNetData);
int EnCodeFAMILY_APPLY_INFO(void* pHost, CNetData* poNetData);
int DeCodeFAMILY_APPLY_INFO(void* pHost, CNetData* poNetData);
int EnCodeFAMILY_WAR_INFO(void* pHost, CNetData* poNetData);
int DeCodeFAMILY_WAR_INFO(void* pHost, CNetData* poNetData);
int EnCodeCASTLE_INFO(void* pHost, CNetData* poNetData);
int DeCodeCASTLE_INFO(void* pHost, CNetData* poNetData);
int EnCodeGUILD_INFO(void *pHost, CNetData *poNetData);
int DeCodeGUILD_INFO(void *pHost, CNetData *poNetData);
int EnCodeGUILD_MEMBER(void *pHost, CNetData *poNetData);
int DeCodeGUILD_MEMBER(void *pHost, CNetData *poNetData);
int EnCodeGUILD_APPLY_INFO(void *pHost, CNetData *poNetData);
int DeCodeGUILD_APPLY_INFO(void *pHost, CNetData *poNetData);
int EnCodeMALL_ITEM_INFO(void* pHost, CNetData* poNetData);
int DeCodeMALL_ITEM_INFO(void* pHost, CNetData* poNetData);
int EnCodeMALL_ITEM_DETAIL(void* pHost, CNetData* poNetData);
int DeCodeMALL_ITEM_DETAIL(void* pHost, CNetData* poNetData);
int EncodeMALL_ITEM_INFO_BASE(void* pHost, CNetData* poNetData);
int DecodeMALL_ITEM_INFO_BASE(void* pHost, CNetData* poNetData);
int EnCodeTOPLIST_INFO(void* pHost, CNetData* poNetData);
int DeCodeTOPLIST_INFO(void* pHost, CNetData* poNetData);
int EnCodeQUEST_HUNTING_INFO(void* pHost, CNetData* poNetData);
int DeCodeQUEST_HUNTING_INFO(void* pHost, CNetData* poNetData);
int EnCodeQUEST_HUNTLEVEL_INFO(void* pHost, CNetData* poNetData);
int DeCodeQUEST_HUNTLEVEL_INFO(void* pHost, CNetData* poNetData);
int EnCodeQUEST_ITEM_INFO(void* pHost, CNetData* poNetData);
int DeCodeQUEST_ITEM_INFO(void* pHost, CNetData* poNetData);
int EnCodeQUEST_NPC_INFO(void* pHost, CNetData* poNetData);
int DeCodeQUEST_NPC_INFO(void* pHost, CNetData* poNetData);
int EnCodeMAIL_HEADER_INFO(void* pHost, CNetData* poNetData);
int DeCodeMAIL_HEADER_INFO(void* pHost, CNetData* poNetData);
int EnCodeMAIL_BODY_INFO(void* pHost, CNetData* poNetData);
int DeCodeMAIL_BODY_INFO(void* pHost, CNetData* poNetData);
int EnCodeMAIL_BODY_INFO2(void* pHost, CNetData* poNetData);
int DeCodeMAIL_BODY_INFO2(void* pHost, CNetData* poNetData);
int EnCodeMAIL_INFO(void* pHost, CNetData* poNetData);
int DeCodeMAIL_INFO(void* pHost, CNetData* poNetData);
int EnCodeMAIL_ADDITIONITEMINFO(void* pHost, CNetData* poNetData);
int DeCodeMAIL_ADDITIONITEMINFO(void* pHost, CNetData* poNetData);
int EncodeMAIL_CURRENCYINFO(void* pHost, CNetData* poNetData);
int DeCodeMAIL_CURRENCYINFO(void* pHost, CNetData* poNetData);
int EnCodeMail_INFO_STATUS(void* pHost, CNetData* poNetData);
int DeCodeMail_INFO_STATUS(void* pHost, CNetData* poNetData);
int EnCodeDELEGATE_SELL_ITEM(void* pHost, CNetData* poNetData);
int DeCodeDELEGATE_SELL_ITEM(void* pHost, CNetData* poNetData);
//int EnCodeDELEGATE_BUY_ITEM(void* pHost, CNetData* poNetData);
//int DeCodeDELEGATE_BUY_ITEM(void* pHost, CNetData* poNetData);
//int EnCodeDELEGATE_INFO(void* pHost, CNetData* poNetData);
//int DeCodeDELEGATE_INFO(void* pHost, CNetData* poNetData);
int EnCodeCAMPAIGN_INFO(void* pHost, CNetData* poNetData);
int DeCodeCAMPAIGN_INFO(void* pHost, CNetData* poNetData);
int EnCodeFAMILY_ALLY_INFO(void* pHost, CNetData* poNetData);
int DeCodeFAMILY_ALLY_INFO(void* pHost, CNetData* poNetData);
int EnCodeTITLE_INFO(void* pHost, CNetData* poNetData);
int DeCodeTITLE_INFO(void* pHost, CNetData* poNetData);
int EnCodeTAOBAO_ITEM_INFO(void* pHost, CNetData* poNetData);
int DeCodeTAOBAO_ITEM_INFO(void* pHost, CNetData* poNetData);
int EnCodeMAP_INFO(void* pHost, CNetData* poNetData);
int DeCodeMAP_INFO(void* pHost, CNetData* poNetData);
int EnCodeTABLE_INFO(void* pHost, CNetData* poNetData);
int DeCodeTABLE_INFO(void* pHost, CNetData* poNetData);
int EnCodeTOPLIST_ITEM_INFO(void* pHost, CNetData* poNetData);
int DeCodeTOPLIST_ITEM_INFO(void* pHost, CNetData* poNetData);
int EnCodeDataInfoDoNotUse(void* pHost, CNetData* poNetData);
int DeCodeDataInfoDoNotUse(void* pHost, CNetData* poNetData);
int EnCodeVIP_ITEM(void* pHost, CNetData* poNetData);
int DeCodeVIP_ITEM(void* pHost, CNetData* poNetData);
int EnCodeVIP_LEVEL(void* pHost, CNetData* poNetData);
int DeCodeVIP_LEVEL(void* pHost, CNetData* poNetData);
int EnCodeQUEST_STATE_ITEM(void* pHost, CNetData* poNetData);
int DeCodeQUEST_STATE_ITEM(void* pHost, CNetData* poNetData);
int EnCodeQUEST_STATE_INFO(void* pHost, CNetData* poNetData);
int DeCodeQUEST_STATE_INFO(void* pHost, CNetData* poNetData);
int EnCodeGLORY_STATE(void* pHost, CNetData* poNetData);
int DeCodeGLORY_STATE(void* pHost, CNetData* poNetData);
int EnCodeROLE_BRIEF_INFO(void* pHost, CNetData* poNetData);
int DeCodeROLE_BRIEF_INFO(void* pHost, CNetData* poNetData);
int EnCodeROLE_EXTRA_INFO(void* pHost, CNetData* poNetData);
int DeCodeROLE_EXTRA_INFO(void* pHost, CNetData* poNetData);
int EnCodeQUEST_INFO(void* pHost, CNetData* poNetData);
int DeCodeQUEST_INFO(void* pHost, CNetData* poNetData);
int EnCodeQUEST_ACHIEVE(void* pHost, CNetData* poNetData);
int DeCodeQUEST_ACHIEVE(void* pHost, CNetData* poNetData);
int EnCodeDUMMY_BRIEF_INFO(void* pHost, CNetData* poNetData);
int DeCodeDUMMY_BRIEF_INFO(void* pHost, CNetData* poNetData);
int EnCodeCHECK_BUFF(void* pHost, CNetData* poNetData);
int DeCodeCHECK_BUFF(void* pHost, CNetData* poNetData);
int EnCodeEQUIP_INFO(void* pHost, CNetData* poNetData);
int DeCodeEQUIP_INFO(void* pHost, CNetData* poNetData);
int EnCodeDELEGATE_BUY_ITEM2(void* pHost, CNetData* poNetData);
int DeCodeDELEGATE_BUY_ITEM2(void* pHost, CNetData* poNetData);
int EnCodeMOBA_ROOM_INFO(void* pHost, CNetData* poNetData);
int DeCodeMOBA_ROOM_INFO(void* pHost, CNetData* poNetData);
int EnCodeMOBA_ROOM_MEMBER_INFO(void* pHost, CNetData* poNetData);
int DeCodeMOBA_ROOM_MEMBER_INFO(void* pHost, CNetData* poNetData);
int EnCodeCUST_VAR(void *pHost, CNetData *poNetData);
int DeCodeCUST_VAR(void *pHost, CNetData *poNetData);
int EnCodeCUST_VAR_SP_LIST(void *pHost, CNetData *poNetData);
int DeCodeCUST_VAR_SP_LIST(void *pHost, CNetData *poNetData);

int EnCodeQUICK_BAR_INFO(void* pHost, CNetData* poNetData);
int DeCodeQUICK_BAR_INFO(void* pHost, CNetData* poNetData);

int EnCodeQUICK_BAR_LIST_INFO(void* pHost, CNetData* poNetData);
int DeCodeQUICK_BAR_LIST_INFO(void* pHost, CNetData* poNetData);
int EnCodeDYN_ATTR(void *pHost, CNetData *poNetData);
int DeCodeDYN_ATTR(void *pHost, CNetData *poNetData);
int EnCodeITEM_DYN_ATTRS(void *pHost, CNetData *poNetData);
int DeCodeITEM_DYN_ATTRS(void *pHost, CNetData *poNetData);
int EnCodeITEM_DYN_ATTRS_LIST(void *pHost, CNetData *poNetData);
int DeCodeITEM_DYN_ATTRS_LIST(void *pHost, CNetData *poNetData);
int EnCodeAUCTION_HOUSE_ITEM_INFO(void* pHost, CNetData* poNetData);
int DeCodeAUCTION_HOUSE_ITEM_INFO(void* pHost, CNetData* poNetData);
int EnCodeLOGIN_IP_DATA(void* pHost, CNetData* poNetData);
int DeCodeLOGIN_IP_DATA(void* pHost, CNetData* poNetData);
int EnCodePROHIBIT_CHAT_DATA(void* pHost, CNetData* poNetData);
int DeCodePROHIBIT_CHAT_DATA(void* pHost, CNetData* poNetData);
int EnCodeWANTED_BY(void *pHost, CNetData *poNetData);
int DeCodeWANTED_BY(void *pHost, CNetData *poNetData);
int EnCodeWANTED(void *pHost, CNetData *poNetData);
int DeCodeWANTED(void *pHost, CNetData *poNetData);
int EncodePoint(void *pHost, CNetData *poNetData);
int DecodePoint(void *pHost, CNetData *poNetData);
int EncodeAUTO_PICKUP(void *pHost, CNetData *poNetData);
int DecodeAUTO_PICKUP(void *pHost, CNetData *poNetData);
int EncodeROLE_SETTINGS(void *pHost, CNetData *poNetData);
int DecodeROLE_SETTINGS(void *pHost, CNetData *poNetData);
int EncodeGOODS_ISSUE_RECORD(void *pHost, CNetData *poNetData);
int DecodeGOODS_ISSUE_RECORD(void *pHost, CNetData *poNetData);
int EncodeREBATE_MONEY_RECORD(void* pHost, CNetData* poNetData);
int DecodeREBATE_MONEY_RECORD(void* pHost, CNetData* poNetData);
int EncodeMONITOR_CHAT_INFO(void* pHost, CNetData* poNetData);
int DecodeMONITOR_CHAT_INFO(void* pHost, CNetData* poNetData);
int EncodeSYSTEN_MESSAGE_NTF(void* pHost, CNetData* poNetData);
int DecodeSYSTEN_MESSAGE_NTF(void* pHost, CNetData* poNetData);
int EncodeSCENCE_DIALOG_NTF(void* pHost, CNetData* poNetData);
int DecodeSCENCE_DIALOG_NTF(void* pHost, CNetData* poNetData);
int EncodeSCROLL_TEXT(void* pHost, CNetData* poNetData);
int DecodeSCROLL_TEXT(void* pHost, CNetData* poNetData);
int EncodeRELATION_CHAT_NTF(void* pHost, CNetData* poNetData);
int DecodeRELATION_CHAT_NTF(void* pHost, CNetData* poNetData);
int EncodeCUST_MSG_NTF(void* pHost, CNetData* poNetData);
int DecodeCUST_MSG_NTF(void* pHost, CNetData* poNetData);
int EncodeCUST_LIST_INFO(void* pHost, CNetData* poNetData);
int DecodeCUST_LIST_INFO(void* pHost, CNetData* poNetData);
int EncodeEFFECT_POINT(void* pHost, CNetData* poNetData);
int DecodeEFFECT_POINT(void* pHost, CNetData* poNetData);


//===============打包解包函数定义结束===============
typedef int (*EnCodeFuncDataInfo)(void *pHost, CNetData* poNetData);
typedef int (*DeCodeFuncDataInfo)(void *pHost, CNetData* poNetData);

class CDataInfo
{
public:
	CDataInfo();
	~CDataInfo();
	int BuildProtocol(void* pHost, char *pNet, int iNetSize);

	bool HandleProtocol(char *pNet, int iNetSize, void* pHost);

	static inline unsigned short GetModuleID(void){ return 15; }

	static inline unsigned short GetProtocolNum(void){ return 1; }

	static const unsigned short module_id = 15;

	static const unsigned short protocol_num = 1;

//===============以下协议回调函数需要使用者来实现===============
	virtual void OnRecv_DataInfoDoNotUse(DataInfoDoNotUse& rstProtocol){ rstProtocol; };
private:
	EnCodeFuncDataInfo m_EnCodeFuncArray[1];
	EnCodeFuncDataInfo m_DeCodeFuncArray[1];
};
