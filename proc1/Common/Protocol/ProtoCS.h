#pragma once

#include "ProtoDef.h"
#include "ProtoLog.h"
#include <vector>

#define DEF_PROTO_HEADER_CS(protoid) uint16_t moduleid = MODULE_TYPE_CS; uint16_t protocolid = protoid
#define REDEF_PROTO_HEADER_CS(protoid) moduleid = MODULE_TYPE_CS; protocolid = protoid
enum
{
	PROTO_CS_HEART_BEAT_REQ,
	PROTO_CS_HEART_BEAT_ACK,
	PROTO_CS_UPLOAD_CONFIG_REQ,
	PROTO_CS_CONFIG_REQ,
	PROTO_CS_CONFIG_ACK,
	PROTO_CS_GET_ROLE_DATA_REQ,
	PROTO_CS_GET_ROLE_DATA_ACK,
	PROTO_CS_SEND_PLAYER_INFO,//SEND TO MS 
	PROTO_CS_SEND_MAP_LIST_NTF,//SEND TO MS 
	PROTO_CS_GET_ITEM_REQ,//SEND TO DB
	PROTO_CS_DELETE_ITEM_NTF,
	PROTO_CS_INSERT_ITEM_NTF,//SEND TO DB
	PROTO_CS_UPDATE_ITEM_NTF,//SEND TO DB
	PROTO_CS_GET_ITEM_ACK,//SEND TO DB

	PROTO_CS_GET_ROLE_INFO_REQ,//SEND TO DB
	PROTO_CS_CLEAR_ROLE_INFO_NTF,
	PROTO_CS_DELETE_ROLE_INFO_NTF,
	PROTO_CS_INSERT_ROLE_INFO_NTF,//SEND TO DB
	PROTO_CS_UPDATE_ROLE_INFO_NTF,//SEND TO DB
	PROTO_CS_GET_ROLE_INFO_ACK,//SEND TO DB

	PROTO_CS_SEND_ITEM_NTF,//SEND TO ms
	PROTO_CS_ENTER_MS_REQ,
	PROTO_CS_ENTER_MS_NTF,
    PROTO_CS_SYNC_SKILL_REQ,    // CS -> DB
    PROTO_CS_SYNC_BUFF_REQ,     // CS -> DB
    PROTO_CS_ROLE_EXTRA_INFO_NTF,
    PROTO_CS_SYNC_QUEST_REQ,    // CS -> DB
    PROTO_CS_GET_GUILDS_ACK,            // CS -> MS
    PROTO_CS_GET_GUILD_MEMBERS_ACK,     // CS -> MS
    PROTO_CS_GET_GUILD_APPLICANTS_ACK,  // CS -> MS
    PROTO_CS_SYNC_PLAYER_CUST_VAR,      // CS -> DB
    PROTO_CS_SYNC_ITEM_CUST_VAR,        // CS -> DB

	PROTO_CS_QUICK_BAR_SET,
	PROTO_CS_QUICK_BAR_SET_NTF,

	PROTO_CS_GLOBAL_NTF,

	PROTO_CS_DGN_BIND_INFO,
	PROTO_CS_DGN_BIND_INFO_NTF,

	PROTO_CS_GM_MOD_LEVEL,
	PROTO_CS_TOPLIST_REQ,
	PROTO_CS_GET_MAIL_INFO,

	PROTO_CS_GET_TRADE_BUY_DELEGATE_ACK,
	PROTO_CS_GET_TRADE_SELL_DELEGATE_ACK,
	PROTO_CS_DELEGATE_CANCEL_ACK,
	PROTO_CS_DELEGATE_SELL_ACK,
	PROTO_CS_DELEGATE_BUY_ACK,
	PROTO_CS_MARKET_SELL_ACK,
	PROTO_CS_MARKET_BUY_ACK,
	PROTO_CS_GET_MAIL_ATTACHMENT_ACK,
	PROTO_CS_AUCTION_GET_FINISHED_INFO_ACK,
	PROTO_CS_RUN_GM_CMD_ACK,
	PROTO_CS_GET_CONSTANT_CFG_ACK,
	PROTO_CS_GET_MALL_LIMIT_INFO_SINGLE_ACK,
	PROTO_CS_MALL_LIST_UPDATE,
	PROTO_CS_DEL_PROHIBIT_INFO,
	PROTO_CS_ADD_PROHIBIT_CHAT_INTO,

	PROTO_CS_ACTIVATION_CODE_ACK,
	PROTO_CS_GET_TRADE_RECORDS_ACK,
	PROTO_CS_RECORDS_CANCEL_ACK,
	PROTO_CS_SYNC_ROLE_INFO,
    PROTO_CS_UPDATE_TABLES,
	PROTO_CS_CUSTOM_HTTP_ACK,
	PROTO_CS_MAX
};

struct ProtoCS_SyncRoleInfo {
	DEF_PROTO_HEADER_CS(PROTO_CS_SYNC_ROLE_INFO);

	uint64_t guid = 0;
	int briefInfoNum = 0;
	int briefInfoKey[role_brief_info_flag::flag_brief_max] = { 0 };
	int briefInfoVal[role_brief_info_flag::flag_brief_max] = { 0 };

	int extraInfoNum = 0;
	int extraInfoKey[role_extra_info_flag::flag_extra_max] = { 0 };
	uint64_t extraInfoVal[role_extra_info_flag::flag_extra_max] = { 0 };

	uint8_t setFlag = 0;
	ROLE_SETTINGS roleset;

	ProtoCS_SyncRoleInfo() = default;
};

struct ProtoCS_ActivationCodeAck
{
	enum {
		err_ok  = 0,
		err_failed = 1,
	};
	DEF_PROTO_HEADER_CS(PROTO_CS_ACTIVATION_CODE_ACK);
	uint64_t guid = 0;
	uint16_t err  = 0;
	uint16_t type = 0;
	char  gift_name[100];
	char  gift_content[65535];
	char  err_desc[100];
	ProtoCS_ActivationCodeAck() {
		memset(err_desc, 0, _countof(err_desc));
		memset(gift_content, 0, _countof(gift_content));
		memset(gift_name, 0, _countof(gift_name));
	}
};

struct ProtoCS_AddProhibitChatInfo
{
	DEF_PROTO_HEADER_CS(PROTO_CS_ADD_PROHIBIT_CHAT_INTO);
	uint8_t num = 0;
	PROHIBIT_CHAT_DATA infos[100];
	ProtoCS_AddProhibitChatInfo()
	{
		memset(infos, 0, sizeof(infos));
	}
};

struct ProtocCS_DelProhibitInfo
{
	DEF_PROTO_HEADER_CS(PROTO_CS_DEL_PROHIBIT_INFO);
	uint8_t num = 0;
	PROHIBIT_CHAT_DATA infos[100];
	ProtocCS_DelProhibitInfo()
	{
		memset(infos, 0, sizeof(infos));
	}
};

struct ProtoCS_MallListUpdate
{
	DEF_PROTO_HEADER_CS(PROTO_CS_MALL_LIST_UPDATE);
	uint16_t num = 0;
	uint8_t  limit_type = 0;
	MALL_ITEM_INFO_BASE data[100];
	ProtoCS_MallListUpdate()
	{
		memset(data, 0, sizeof(data));
	}
};

struct ProtoCS_GetMallLimitInfoSingleAck
{
	DEF_PROTO_HEADER_CS(PROTO_CS_GET_MALL_LIMIT_INFO_SINGLE_ACK);
	uint64_t playerguid = 0;
	uint8_t isFirstPkg = 0;
	uint8_t isFinalPkg = 0;
	uint16_t num = 0;
	MALL_ITEM_INFO_BASE data[100];
	ProtoCS_GetMallLimitInfoSingleAck()
	{
		memset(data, 0, sizeof(data));
	}
};

struct ProtoCS_RunGmCmdAck
{
	DEF_PROTO_HEADER_CS(PROTO_CS_RUN_GM_CMD_ACK);

	uint8_t                     result              = 0;
    int32_t                     sn                  = 0;
    char                        cmd[256]            = {0};      //GM 指令
    char                        param[65535]          = {0};      //指令参数
	uint32_t                    token               = 0;
    char                        playername[32]      = {0};
	void Clear()
	{
		memset(this, 0, sizeof(ProtoCS_RunGmCmdAck));
		REDEF_PROTO_HEADER_CS(PROTO_CS_RUN_GM_CMD_ACK);
	}
};

struct ProtoCS_AuctionGetFinishedInfoAck
{
	DEF_PROTO_HEADER_CS(PROTO_CS_AUCTION_GET_FINISHED_INFO_ACK);
	uint16_t num             = 0;
	char     func[32];
	AUCTION_HOUSE_ITEM_INFO  info[100];
	ProtoCS_AuctionGetFinishedInfoAck() 
	{
		memset(func, 0, sizeof(func));
		memset(info, 0, sizeof(info));
	}
};

struct ProtoCS_TopListReq
{
	DEF_PROTO_HEADER_CS(PROTO_CS_TOPLIST_REQ);
};

struct ProtoCS_GetMailInfo
{
	DEF_PROTO_HEADER_CS(PROTO_CS_GET_MAIL_INFO);
	uint64_t playerguid = 0;
};

struct ProtoCS_ClearRoleInfoNtf
{
	DEF_PROTO_HEADER_CS(PROTO_CS_CLEAR_ROLE_INFO_NTF);
	uint64_t			 role_id = 0;
	uint32_t			 token = 0;
};

struct ProtoCS_DeleteRoleInfoNtf
{
	DEF_PROTO_HEADER_CS(PROTO_CS_DELETE_ROLE_INFO_NTF);
	uint64_t			 role_id = 0;
	uint32_t			 token = 0;
	char				 base_info[512];
};

struct ProtoCS_UpdateRoleInfoNtf
{
	DEF_PROTO_HEADER_CS(PROTO_CS_UPDATE_ROLE_INFO_NTF);
	uint64_t			 role_id = 0;
	uint32_t			 token = 0;
	char				 base_info[512];
};

struct ProtoCS_InsertRoleInfoNtf
{
	DEF_PROTO_HEADER_CS(PROTO_CS_INSERT_ROLE_INFO_NTF);
	uint64_t			 role_id = 0;
	uint32_t			 token = 0;
	char				 base_info[512];
};

struct ProtoCS_GetRoleInfoReq
{
	DEF_PROTO_HEADER_CS(PROTO_CS_GET_ROLE_INFO_REQ);
	uint64_t    role_id = 0;
	uint32_t    token = 0;
};

struct ProtoCS_GetRoleInfoAck
{
	DEF_PROTO_HEADER_CS(PROTO_CS_GET_ROLE_INFO_ACK);
	uint64_t                  role_id = 0;
	uint32_t                  token = 0;
	char                      base_info[512]; //信息
};

struct ProtoCS_DeleteItemNtf
{
	DEF_PROTO_HEADER_CS(PROTO_CS_DELETE_ITEM_NTF);
	uint64_t			 guid = 0;
	uint64_t			 role_id = 0;
	uint32_t			 token = 0;
};

struct ProtoCS_UpdateItemNtf
{
	DEF_PROTO_HEADER_CS(PROTO_CS_UPDATE_ITEM_NTF);
	uint64_t			 role_id = 0;
	uint32_t			 token = 0;
	ITEM_DB_INFO         base_info;
};

struct ProtoCS_InsertItemNtf
{
	DEF_PROTO_HEADER_CS(PROTO_CS_INSERT_ITEM_NTF);
	uint64_t			 role_id = 0;
	uint32_t			 token = 0;
	ITEM_DB_INFO         base_info;
};

struct ProtoCS_GetItemAck
{
	DEF_PROTO_HEADER_CS(PROTO_CS_GET_ITEM_ACK);
	uint64_t                  role_id = 0;
	uint32_t                  token = 0;
	unsigned short            item_num; //物品数量
	
	ITEM_INFO                 item_info[50]; //物品信息
};
static ProtoCS_GetItemAck gProtoCS_GetItemAck;

struct ProtoCS_SendItemNtf
{
	DEF_PROTO_HEADER_CS(PROTO_CS_SEND_ITEM_NTF);
	uint64_t role_id = 0;
	uint32_t    token = 0;
	unsigned short            item_num; //物品数量
	ITEM_INFO                 item_info[20]; //物品信息

};
static ProtoCS_SendItemNtf gProtoCS_SendItemNtf;

struct ProtoCS_HeartBeatReq
{
	DEF_PROTO_HEADER_CS(PROTO_CS_HEART_BEAT_REQ);
};

struct ProtoCS_HeartBeatAck
{
	DEF_PROTO_HEADER_CS(PROTO_CS_HEART_BEAT_ACK);
};

struct ProtoCS_UploadConfigReq
{
	DEF_PROTO_HEADER_CS(PROTO_CS_UPLOAD_CONFIG_REQ);

	uint32_t    ip = 0;
	uint32_t    port = 0;
};

struct ProtoCS_ConfigReq
{
	DEF_PROTO_HEADER_CS(PROTO_CS_CONFIG_REQ);
};

struct ProtoCS_ConfigAck
{
	DEF_PROTO_HEADER_CS(PROTO_CS_CONFIG_ACK);

	uint32_t    dbServIp = 0;
	uint32_t    dbServPort = 0;
	uint32_t    logServIp = 0;
	uint32_t    logServPort = 0;
};

struct ProtoCS_SendPlayerInfo
{
	DEF_PROTO_HEADER_CS(PROTO_CS_SEND_PLAYER_INFO);

	uint64_t    player_id = 0;
	uint64_t    role_id = 0;// player_roleid
	uint32_t    mtoken = 0;
	uint32_t    msessid = 0;
	//ROLE_BRIEF_INFO         roleBriefInfo;
	uint32_t  nGS2CSSessionID = 0;
	/* ProtoCS_SendPlayerInfo()
	 {
		 memset(&roleBriefInfo, 0, sizeof(roleBriefInfo));
	 }*/
};

struct ProtoCS_SendMAPLISTINFO
{
	DEF_PROTO_HEADER_CS(PROTO_CS_SEND_MAP_LIST_NTF);

	char        maplist[256];

	ProtoCS_SendMAPLISTINFO()
	{
		memset(maplist, 0, 256);
	}
};

struct ProtoCS_EnterMSReq
{
	DEF_PROTO_HEADER_CS(PROTO_CS_ENTER_MS_REQ);
	uint32_t                    sessionid = 0;
	uint32_t                    nMS2GSSessionID = 0;
	uint32_t                    token = 0;
	uint64_t                    playerid = 0;
	char                        entertype = -1;   //进入类型 0=上线 1=跳服
	char                        fangchenmi = -1;   //是否防沉迷用户 1：是 0：否
	char                        clienttype = -1;   //客户端类型 0=客户端 1=页游 2=手游
	ROLE_BRIEF_INFO             roleBriefInfo;
    ROLE_EXTRA_INFO             roleExtraInfo;
	ROLE_SETTINGS				roleSettings;
    QUEST_INFO                  questInfo;
    uint8_t                     questAchievesNum = 0;
    QUEST_ACHIEVE               questAchieves[50];
	int64_t                     isProhibitChat = 0; // 账号禁言 -1=永久 0=无封禁 int64封禁时间戳
	uint8_t                     isSupport = 0;
	char						playerName[32] = { 0 };
	ProtoCS_EnterMSReq()
	{
		memset(&roleBriefInfo, 0, sizeof(roleBriefInfo));
        memset(&roleExtraInfo, 0, sizeof(roleExtraInfo));
        memset(&questInfo, 0, sizeof(questInfo));
        memset(questAchieves, 0, sizeof(questAchieves));
	}
};

struct ProtoCS_EnterMSNtf
{
	DEF_PROTO_HEADER_CS(PROTO_CS_ENTER_MS_NTF);
	uint32_t                    token = 0;
	uint64_t					player_id = 0;
	uint64_t					role_id = 0;
};

struct ProtoCS_GetRoleDataReq
{
	DEF_PROTO_HEADER_CS(PROTO_CS_GET_ROLE_DATA_REQ);
	uint32_t                    token = 0;
	uint64_t                    playerid = 0;
	uint64_t                    roleid = 0;
};

struct ProtoCS_GetRoleDataAck
{
	DEF_PROTO_HEADER_CS(PROTO_CS_GET_ROLE_DATA_ACK);
	uint32_t                    token = 0;
	uint64_t                    playerid = 0;
	uint64_t                    roleid = 0;
};

struct ProtoCS_SyncSkillReq
{
    DEF_PROTO_HEADER_CS(PROTO_CS_SYNC_SKILL_REQ);

    uint64_t                    roleid          = 0;

    uint16_t                    removeSkillNum  = 0;
    SKILL_INFO                  removeSkillInfo[30];

    uint16_t                    addSkillNum     = 0;
    SKILL_INFO                  addSkillInfo[30];

    uint16_t                    updateSkillNum  = 0;
    SKILL_INFO                  updateSkillInfo[30];

    ProtoCS_SyncSkillReq()
    {
        memset(removeSkillInfo, 0, sizeof(removeSkillInfo));
        memset(addSkillInfo, 0, sizeof(addSkillInfo));
        memset(updateSkillInfo, 0, sizeof(updateSkillInfo));
    }
	void Clear()
	{
		memset(this, 0, sizeof(ProtoCS_SyncSkillReq));
		REDEF_PROTO_HEADER_CS(PROTO_CS_SYNC_SKILL_REQ);
	}
};

struct ProtoCS_SyncBuffReq
{
    DEF_PROTO_HEADER_CS(PROTO_CS_SYNC_BUFF_REQ);

    uint64_t                    roleid          = 0;

    uint16_t                    removeNum       = 0;
    uint64_t                    removeIndex[50];

    uint16_t                    addNum          = 0;
    BUFF_INFO_DB                addBuffInfo[50];

    uint16_t                    updateNum       = 0;
    BUFF_INFO_DB                updateBuffInfo[50];

    ProtoCS_SyncBuffReq()
    {
        memset(removeIndex, 0, sizeof(removeIndex));
        memset(addBuffInfo, 0, sizeof(addBuffInfo));
        memset(updateBuffInfo, 0, sizeof(updateBuffInfo));
    }
};

struct ProtoCS_RoleExtraInfoNtf
{
    DEF_PROTO_HEADER_CS(PROTO_CS_ROLE_EXTRA_INFO_NTF);

    uint64_t                    roleid          = 0;
    uint32_t                    token           = 0;

    ROLE_EXTRA_INFO             roleExtraInfo;
	ROLE_SETTINGS				roleSettings;

    ProtoCS_RoleExtraInfoNtf()
    {
        memset(&roleExtraInfo, 0, sizeof(roleExtraInfo));
    }
};

struct ProtoCS_SyncQuestReq
{
    DEF_PROTO_HEADER_CS(PROTO_CS_SYNC_QUEST_REQ);

    uint64_t                    roleid              = 0;

    QUEST_INFO                  quest_info;

    uint8_t                     remove_num          = 0;
    QUEST_ACHIEVE               remove_achev[50];

    uint8_t                     add_num             = 0;
    QUEST_ACHIEVE               add_achev[50];

    uint8_t                     update_num          = 0;
    QUEST_ACHIEVE               update_achev[50];

    ProtoCS_SyncQuestReq()
    {
        memset(&quest_info, 0, sizeof(quest_info));
        memset(remove_achev, 0, sizeof(remove_achev));
        memset(add_achev, 0, sizeof(add_achev));
        memset(update_achev, 0, sizeof(update_achev));
    }
};

struct ProtoCS_GetTradeBuyDelegateAck
{
	enum GTIA_MaxSize
	{
		Info_Size = 100
	};
	DEF_PROTO_HEADER_CS(PROTO_CS_GET_TRADE_BUY_DELEGATE_ACK);
	uint16_t		num = 0;
	uint16_t		packIdx = 0;
	DELEGATE_BUY_ITEM2	delegateInfo[Info_Size];
};

struct ProtoCS_GetTradeSellDelegateAck
{
	enum GTIA_MaxSize
	{
		Info_Size = 10
	};
	DEF_PROTO_HEADER_CS(PROTO_CS_GET_TRADE_SELL_DELEGATE_ACK);
	uint16_t		num = 0;
	uint16_t		packIdx = 0;
	DELEGATE_SELL_ITEM	delegateInfo[Info_Size];
};

struct ProtoCS_GetTradeRecordsAck
{
	enum GTRA_MaxSize
	{
		Info_Size = 10
	};
	DEF_PROTO_HEADER_CS(PROTO_CS_GET_TRADE_RECORDS_ACK);
	uint16_t		num = 0;
	uint16_t		packIdx = 0;
	TRADE_RECORD	trade_record[Info_Size];
	void Clear()
	{
		memset(this, 0, sizeof(ProtoCS_GetTradeRecordsAck));
		REDEF_PROTO_HEADER_CS(PROTO_CS_GET_TRADE_RECORDS_ACK);
	}
};

struct ProtoCS_RecordsCancelAck
{
	enum RCA_MaxSize
	{
		Info_Size = 100
	};
	DEF_PROTO_HEADER_CS(PROTO_CS_RECORDS_CANCEL_ACK);
	uint16_t            num = 0;
	uint64_t            trade_id[Info_Size] = { 0 };
};

struct ProtoCS_DelegateCancelAck
{
	DEF_PROTO_HEADER_CS(PROTO_CS_DELEGATE_CANCEL_ACK);
	uint16_t        err_type = 0;
	uint8_t			delegate_type = 0;
	uint64_t		player_guid = 0;
	uint64_t		trade_id = 0;
	uint8_t         reason = 0;
	uint32_t		token = 0;
};

struct ProtoCS_DelegateSellAck
{
	DEF_PROTO_HEADER_CS(PROTO_CS_DELEGATE_SELL_ACK);
	uint16_t        err_type = 0;
	uint32_t        token = 0;
	DELEGATE_SELL_ITEM	sellItem;
}; 

struct ProtoCS_DelegateBuyAck
{
	DEF_PROTO_HEADER_CS(PROTO_CS_DELEGATE_BUY_ACK);
	uint16_t        err_type = 0;
	uint32_t        token = 0;
	DELEGATE_BUY_ITEM2	buyItem;
};

struct ProtoCS_MarketSellAck
{
	DEF_PROTO_HEADER_CS(PROTO_CS_MARKET_SELL_ACK);
	uint64_t        trade_id = 0; //交易号
	uint64_t        seller_guid = 0;
	char			seller[32] = { 0 };
	uint32_t        count = 0;
	uint8_t         remove = 0;
	ITEM_INFO		item;
	uint32_t        token = 0;
};

struct ProtoCS_MarketBuyAck
{
	DEF_PROTO_HEADER_CS(PROTO_CS_MARKET_BUY_ACK);
	uint64_t        trade_id = 0; //交易号
	uint64_t        buyer_guid = 0;
	char			buyer[32] = { 0 };
	uint32_t        count = 0;
	uint8_t         remove = 0;
	ITEM_INFO		item;
	uint32_t        token = 0;
};

struct ProtoCS_GetMailAttachmentAck
{
	DEF_PROTO_HEADER_CS(PROTO_CS_GET_MAIL_ATTACHMENT_ACK);
	uint64_t            mail_guid;
	uint8_t             index;
	ITEM_INFO			item;
	uint16_t			err_type = 0;
};

struct ProtoCS_GetGuildsAck
{
    DEF_PROTO_HEADER_CS(PROTO_CS_GET_GUILDS_ACK);

    GUILD_MAP                   guilds;
};

struct ProtoCS_GetGuildMembersAck
{
    DEF_PROTO_HEADER_CS(PROTO_CS_GET_GUILD_MEMBERS_ACK);

    GUILD_MEMBER_MAP            members;
};

struct ProtoCS_GetGuildApplicantsAck
{
    DEF_PROTO_HEADER_CS(PROTO_CS_GET_GUILD_APPLICANTS_ACK);

    GUILD_APPLICANT_LIST        applicants;
};

struct ProtoCS_SyncPlayerCustVar
{
    DEF_PROTO_HEADER_CS(PROTO_CS_SYNC_PLAYER_CUST_VAR);

    uint64_t                    roleid              = 0;

    CUST_VAR_LIST              *add                 = nullptr;
    CUST_VAR_LIST              *remove              = nullptr;
    CUST_VAR_LIST              *update              = nullptr;
};

struct ProtoCS_SyncItemCustVar
{
    DEF_PROTO_HEADER_CS(PROTO_CS_SYNC_ITEM_CUST_VAR);

    CUST_VAR_SP_LIST           *add                 = nullptr;
    CUST_VAR_SP_LIST           *remove              = nullptr;
    CUST_VAR_SP_LIST           *update              = nullptr;
};

struct ProtoCS_SyncQuickBarSet
{
	DEF_PROTO_HEADER_CS(PROTO_CS_QUICK_BAR_SET);
	unsigned short		      num = 0;
	QUICK_BAR_LIST_INFO       info[30];
};

struct ProtoCS_QuickBarSetNtf
{
	DEF_PROTO_HEADER_CS(PROTO_CS_QUICK_BAR_SET_NTF);
	unsigned short			num;
	uint64_t	        	role_id = 0;
	uint32_t	        	token = 0;
	QUICK_BAR_INFO			info[30];
};
// cs to db
struct ProtoCS_SyncDgnBindInfo
{
	enum DBI_MaxSize
	{
		Info_Size = 50
	};
	DEF_PROTO_HEADER_CS(PROTO_CS_DGN_BIND_INFO);
	uint16_t						packIdx = 0;
	uint16_t						num = 0;
	uint64_t	        			roleId = 0;
	DGN_BIND_INFO					info[Info_Size];
};
// db to cs to ms
struct ProtoCS_DgnBindInfoNtf
{
	enum DBI_MaxSize
	{
		Info_Size = 50
	};
	DEF_PROTO_HEADER_CS(PROTO_CS_DGN_BIND_INFO_NTF);
	uint16_t						num;
	uint64_t	        			roleId = 0;
	uint32_t	        			token = 0;
	DGN_BIND_INFO					info[Info_Size];
};

struct ProtoCS_GlobalNtf 
{
	DEF_PROTO_HEADER_CS(PROTO_CS_GLOBAL_NTF);
	uint64_t	     role_id = 0;
	uint32_t	       token = 0;
	unsigned short int_count = 0;      //整形数据个数
	IntData        int_data[256];  //数据值
	unsigned short str_count = 0;      //字符型数据个数
	StrData        str_data[256];
	ProtoCS_GlobalNtf() = default;
};

struct ProtoCS_GMModLevel
{
	DEF_PROTO_HEADER_CS(PROTO_CS_GM_MOD_LEVEL);
	uint64_t			      role_id = 0;
	uint32_t                  GMModLevel = 0;
};

struct ProtoCS_GetConstantCfgAck
{
	DEF_PROTO_HEADER_CS(PROTO_CS_GET_CONSTANT_CFG_ACK);
	CUSTOM_INFO               custom;// size,key-value,...
};

struct ProtoCS_UpdateTables
{
    DEF_PROTO_HEADER_CS(PROTO_CS_UPDATE_TABLES);

    uint32_t                    len         = 0;
    uint8_t                    *data        = 0;
};

struct ProtoCS_CustomHttpAck
{
	DEF_PROTO_HEADER_CS(PROTO_CS_CUSTOM_HTTP_ACK);
	char     func[1024];
	char     data[10240];
};

class ProtoCS
{
public:
	ProtoCS();
	~ProtoCS();

	static inline uint16_t GetModuleID(void) { return MODULE_TYPE_CS; }
	static inline uint16_t GetProtocolNum(void) { return PROTO_CS_MAX; }

	int BuildProtocol(void* pHost, char* pNet, int iNetSize);
	int HandleProtocol(void* pHost, char* pNet, int iNetSize);

private:
	EnCodeFunc m_EnCodeFuncArray[PROTO_CS_MAX];
	DeCodeFunc m_DeCodeFuncArray[PROTO_CS_MAX];
};
