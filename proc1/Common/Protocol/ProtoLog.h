#pragma once
#include "ProtoDef.h"
#include "Types.h"

#define DEF_PROTO_HEADER_LOG(protoid) uint16_t moduleid = MODULE_TYPE_LOG; uint16_t protocolid = protoid
#define REDEF_PROTO_HEADER_LOG(protoid) moduleid = MODULE_TYPE_LOG; protocolid = protoid

enum
{
	PROTO_LOG_HEART_BEAT_REQ,
	PROTO_LOG_HEART_BEAT_ACK,
	PROTO_LOG_UPLOAD_CONFIG_REQ,
	PROTO_LOG_LOGGING_REQ,
	PROTO_LOG_MAX
};


struct ProtoLog_HeartBeatReq
{
	DEF_PROTO_HEADER_LOG(PROTO_LOG_HEART_BEAT_REQ);
};

struct ProtoLog_HeartBeatAck
{
	DEF_PROTO_HEADER_LOG(PROTO_LOG_HEART_BEAT_ACK);
};

struct ProtoLog_UploadConfigReq
{
	DEF_PROTO_HEADER_LOG(PROTO_LOG_UPLOAD_CONFIG_REQ);

	uint32_t                    ip = 0;
	uint32_t                    port = 0;
};


// logContent
// 积分货币变化
struct LogCurrencyChange
{
	LogCurrencyChange(uint64_t role, uint16_t ty, int64_t bef,
		int64_t ch, int64_t aft, uint16_t rea = 0, const string& des = EMPTYSTR)
	{
		roleGuid = role;
		type = ty;
		before = bef;
		change = ch;
		after = aft;
		reasonType = rea;
		strncpy_s(desc, des.c_str(), sizeof(desc) - 1);
		descLength = strlen(desc);
	}
	uint64_t	roleGuid = 0;
	uint16_t	type = 0;			// 类型role_attr_ext
	int64_t		before = 0;			// 变化前
	int64_t		change = 0;			// 变化量
	int64_t		after = 0;			// 变化后
	uint16_t	reasonType = 0;		// 变化原因,log_item_change_reason,暂时不要了
	uint16_t	descLength = 0;		// 描述数据长度
	char		desc[64] = { 0 };	// 描述数据
};
// 物品更新
struct LogItemUpdate
{
	LogItemUpdate(uint64_t role, uint64_t iGuid, uint32_t iId, uint32_t iSite,
		uint32_t pro, int32_t bef, int32_t cha, int32_t aft, const string& in, uint16_t rea = 0, const string& des = EMPTYSTR)
	{
		roleGuid = role;
		itemGuid = iGuid;
		itemId = iId;
		itemSite = iSite;
		prop = pro;
		before = bef;
		change = cha;
		after = aft;
		reasonType = rea;
		strncpy_s(desc, des.c_str(), sizeof(desc) - 1);
		descLength = strlen(desc);
		strncpy_s(itemName, in.c_str(), sizeof(itemName) - 1);
	}
	uint64_t	roleGuid = 0;
	uint64_t	itemGuid = 0;		// 装备guid
	char		itemName[64] = { 0 };// 物品名,非keyname
	uint32_t	itemId = 0;			// 模板id
	uint32_t	itemSite = 0;		// site
	uint32_t	prop = 0;			// 属性item_attr
	int32_t		before = 0;			// 变化前
	int32_t		change = 0;			// 变化量
	int32_t		after = 0;			// 变化后
	uint16_t	reasonType = 0;		// 变化原因,log_item_change_reason,暂时不要了
	uint16_t	descLength = 0;		// 描述数据长度
	char		desc[64] = { 0 };	// 描述数据
};
// 登录登出
struct LogLoginOut
{
	LogLoginOut(const string& ip, const string& hwid, uint64_t pid, uint16_t typ, const string& des = EMPTYSTR)
	{
		strncpy_s(clientIp, ip.c_str(), sizeof(clientIp) - 1);
		strncpy_s(clientHwid, hwid.c_str(), sizeof(clientHwid) - 1);
		hwidLen = strlen(clientHwid);
		playerId = pid;
		type = typ;
		strncpy_s(desc, des.c_str(), sizeof(desc) - 1);
		descLength = strlen(desc);
	}
	char		clientIp[16] = { 0 };
	uint16_t	hwidLen = 0;
	char		clientHwid[256] = { 0 };
	uint64_t	playerId = 0;		// 账号id
	uint16_t	type = 0;			// 类型log_loginout_type
	uint16_t	descLength = 0;		// 描述数据长度
	char		desc[64] = { 0 };	// 描述数据
};
// 进出地图
struct LogEnteryExitMap
{
	LogEnteryExitMap(uint64_t rGuid, uint32_t fId, uint16_t fType, uint32_t tId, uint16_t tType, const string& des = EMPTYSTR, const std::string& tInfo = "", uint64_t du = 0)
	{
		roleGuid = rGuid;
		fromMapId = fId;
		fromMapType = fType;
		toMapId = tId;
		toMapType = tType;
		duration = du;
		strncpy_s(ticks, tInfo.c_str(), sizeof(ticks) - 1);
		ticksLength = strlen(ticks);
		strncpy_s(desc, des.c_str(), sizeof(desc) - 1);
		descLength = strlen(desc);
	}
	uint64_t	roleGuid = 0;
	uint32_t	fromMapId = 0;			// 原地图id(选角界面为0)
	uint16_t	fromMapType = 0;		// 原地图类型(选角界面为0)
	uint32_t	toMapId = 0;			// 后地图id(选角界面为0)
	uint16_t	toMapType = 0;			// 后地图类型(选角界面为0)
	uint16_t	ticksLength = 0;		// 描述门票信息长度
	char		ticks[64] = {0};		// 门票信息
	uint64_t	duration = 0;			// 在线时长(登出记录)
	uint16_t	descLength = 0;		// 描述数据长度
	char		desc[64] = { 0 };	// 描述数据
};
// 物品掉落
struct LogDropItem
{
	LogDropItem(uint32_t mId, uint16_t mType, uint64_t rGuid, uint64_t oGuid, uint16_t oMType, uint32_t oSType, uint16_t iType, uint32_t iId, uint32_t amo, const string& in, const string& des = EMPTYSTR)
	{
		mapId = mId;
		mapType = mType;
		roleGuid = rGuid;
		objGuid = oGuid;
		objMainType = oMType;
		objSubType = oSType;
		itemType = iType;
		itemId = iId;
		amount = amo;
		strncpy_s(desc, des.c_str(), sizeof(desc) - 1);
		descLength = strlen(desc);
		strncpy_s(itemName, in.c_str(), sizeof(itemName) - 1);
	}
	uint32_t	mapId = 0;			// 地图id
	uint16_t	mapType = 0;		// 地图类型
	uint64_t	roleGuid = 0;
	uint64_t	objGuid = 0;		// 对象guid
	uint16_t	objMainType = 0;	// 对象的主类型
	uint32_t	objSubType = 0;		// 对象的子类型
	uint16_t	itemType = 0;		// 物品、货币(log_drop_item_type)
	uint32_t	itemId = 0;			// 模板id(货币用role_attr_ext)
	uint32_t	amount = 0;			// 掉落数量
	char		itemName[64] = { 0 };// 物品名,非keyname
	uint16_t	descLength = 0;		// 描述数据长度
	char		desc[64] = { 0 };	// 描述数据
};
// gm指令
struct LogGmCmd
{
	LogGmCmd(uint64_t rGuid, int32_t level, const string& func, const string& cmdType, const string& cmd, const string& des = EMPTYSTR)
	{
		roleGuid = rGuid;
		gmLevel = level;
		strncpy_s(gmFunc, func.c_str(), sizeof(gmFunc) - 1);
		gmFuncLength = strlen(gmFunc);
		strncpy_s(gmCmdType, cmdType.c_str(), sizeof(gmCmdType) - 1);
		gmCmdTypeLength = strlen(gmCmdType);
		strncpy_s(gmCmd, cmd.c_str(), sizeof(gmCmd) - 1);
		gmCmdLength = strlen(gmCmd);
		strncpy_s(desc, des.c_str(), sizeof(desc) - 1);
		descLength = strlen(desc);
	}
	uint64_t	roleGuid = 0;
	int32_t		gmLevel = 0;
	uint16_t	gmFuncLength = 0;	// gm函数数据长度
	char		gmFunc[64] = { 0 };	// gm函数数据
	uint16_t	gmCmdTypeLength = 0;	// gm指令类型数据长度
	char		gmCmdType[32] = { 0 };	// gm指令类型数据,可以替换成整型,提升查找速度
	uint16_t	gmCmdLength = 0;	// gm指令数据长度
	char		gmCmd[1024] = { 0 };	// gm指令数据
	uint16_t	descLength = 0;		// 描述数据长度
	char		desc[64] = { 0 };	// 描述数据
};
// 在线人数(cs)
struct LogOnlineNum
{
	LogOnlineNum(uint32_t n, const string& des = EMPTYSTR)
	{
		num = n;
		strncpy_s(desc, des.c_str(), sizeof(desc) - 1);
		descLength = strlen(desc);
	}
	uint32_t	num = 0;			// 人数
	uint16_t	descLength = 0;		// 描述数据长度
	char		desc[64] = { 0 };	// 描述数据
};
// 寄售行交易记录
struct LogTradeData
{
	LogTradeData() {}
	LogTradeData(uint64_t tId, uint16_t tType, uint16_t vType, uint64_t	oGuid, uint64_t	iGuid, const string& in, uint32_t	iId,
		uint32_t iValue, uint32_t iNum, uint64_t bGuid, uint64_t sGuid, uint64_t time, uint64_t tTime, const string& des = EMPTYSTR)
	{
		tradeId = tId;
		tradeType = tType;
		valueType = vType;
		itemGuid = iGuid;
		itemId = iId;
		itemValue = iValue;
		itemNum = iNum;
		buyerGuid = bGuid;
		sellerGuid = sGuid;
		timestamp = time;
		strncpy_s(desc, des.c_str(), sizeof(desc) - 1);
		descLength = strlen(desc);
		strncpy_s(itemName, in.c_str(), sizeof(itemName) - 1);
		orgItemGuid = oGuid;
		tradeTimestamp = tTime;
	}
	uint64_t	tradeId = 0;		// 交易id
	uint16_t	tradeType = 0;		// 委托类型:卖0,买1
	uint16_t	valueType = 0;		// 价格类型:金币0,元宝1
	uint64_t	itemGuid= 0;		// 物品guid
	uint32_t	itemId = 0;			// 物品模板id
	char		itemName[64] = { 0 };// 物品名,非keyname
	uint32_t	itemValue = 0;		// 物品单价
	uint32_t	itemNum = 0;		// 物品数量
	uint64_t	buyerGuid = 0;		// 买家角色guid
	uint64_t	sellerGuid = 0;		// 卖家guid
	uint64_t	timestamp = 0;		// 时间戳,交易时间
	uint16_t	descLength = 0;		// 描述数据长度
	char		desc[64] = { 0 };	// 描述数据
	uint64_t	orgItemGuid = 0;	// 原物品guid
	uint64_t	tradeTimestamp = 0;	// 时间戳,上架时间
};
// 邮件记录
struct LogMailInfo
{
	enum LogMailUpdateFlag
	{
		LMUF_INSERT,
		LMUF_UPDATE,
		LMUF_DELETE,
	};
	// LMUF_INSERT 和 LMUF_DELETE
	LogMailInfo(const std::vector<uint64_t>& mails, LogMailUpdateFlag flag, const string& des = EMPTYSTR)
	{
		assert(mails.size() <= sizeof(mailStatus) / sizeof(mailStatus[0]));
		for (int32_t i = 0; i < mails.size(); ++i)
		{
			mailStatus[i].mailid = mails[i];
		}
		mailNum = mails.size();
		updateFlag = flag;
		strncpy_s(desc, des.c_str(), sizeof(desc) - 1);
		descLength = strlen(desc);
	}
	// LMUF_UPDATE
	LogMailInfo(const Mail_Info_Status* info, uint16_t num, const string& des = EMPTYSTR)
	{
		assert(num <= sizeof(mailStatus) / sizeof(mailStatus[0]));
		for (int32_t i = 0; i < num; ++i) 
		{
			mailStatus[i] = info[i];
		}
		mailNum = num;
		updateFlag = LMUF_UPDATE;
		strncpy_s(desc, des.c_str(), sizeof(desc) - 1);
		descLength = strlen(desc);
	}
	uint16_t	mailNum = 0;
	Mail_Info_Status	mailStatus[1000];		// 邮件状态集合
	uint8_t		updateFlag = LMUF_INSERT;		// 更新标识
	uint16_t	descLength = 0;		// 描述数据长度
	char		desc[64] = { 0 };	// 描述数据
};
// 死亡记录
struct LogDeathRecord
{
	LogDeathRecord(uint64_t u1, uint32_t l1, uint32_t mId, uint16_t mType, uint64_t u2, uint32_t l2, uint16_t type, uint32_t stype, const string& des = EMPTYSTR)
	{
		roleGuid1 = u1;
		roleLevel1 = l1;
		mapId = mId;
		mapType = mType;
		roleGuid2 = u2;
		roleLevel2 = l2;
		roleType = type;
		roleSType = stype;
		strncpy_s(desc, des.c_str(), sizeof(desc) - 1);
		descLength = strlen(desc);
	}
	uint64_t	roleGuid1 = 0;		// 受害者角色guid
	uint32_t	roleLevel1 = 0;		// 受害者角色等级
	uint32_t	mapId = 0;			// 地图id
	uint16_t	mapType = 0;		// 地图类型
	uint64_t	roleGuid2 = 0;		// 凶手角色guid
	uint32_t	roleLevel2 = 0;		// 凶手角色等级
	uint16_t	roleType = 0;		// 凶手类型
	uint32_t	roleSType = 0;		// 凶手子类型
	uint16_t	descLength = 0;		// 描述数据长度
	char		desc[64] = { 0 };	// 描述数据
};
// 活动
struct LogActivityData
{
	LogActivityData(const string& an, const string& rn, uint64_t au, uint64_t ru, const string& ikn, uint32_t num, const string& des = EMPTYSTR)
	{
		strncpy_s(activityName, an.c_str(), sizeof(activityName) - 1);
		strncpy_s(rewardName, rn.c_str(), sizeof(rewardName) - 1);
		activityGuid = au;
		roleGuid = ru;
		strncpy_s(itemKeyname, ikn.c_str(), sizeof(itemKeyname) - 1);
		itemNum = num;
		strncpy_s(desc, des.c_str(), sizeof(desc) - 1);
		descLength = strlen(desc);
	}
	char		activityName[64] = { 0 };	// 活动名称
	char		rewardName[64] = { 0 };		// 奖励名称
	uint64_t	activityGuid = 0;			// 活动单号id
	uint64_t	roleGuid = 0;				// 角色guid
	char		itemKeyname[64] = { 0 };	// 物品keyname
	uint32_t	itemNum = { 0 };			// 物品数量
	uint16_t	descLength = 0;				// 描述数据长度
	char		desc[64] = { 0 };			// 描述数据
};
// 奖励领取
struct LogRewardData
{
	LogRewardData(const string& rn, uint64_t reu, uint64_t ru, const string& ikn, uint32_t num, const string& des = EMPTYSTR)
	{
		strncpy_s(rewardName, rn.c_str(), sizeof(rewardName) - 1);
		rewardGuid = reu;
		roleGuid = ru;
		strncpy_s(itemKeyname, ikn.c_str(), sizeof(itemKeyname) - 1);
		itemNum = num;
		strncpy_s(desc, des.c_str(), sizeof(desc) - 1);
		descLength = strlen(desc);
	}
	char		rewardName[64] = { 0 };		// 奖励名称
	uint64_t	rewardGuid = 0;				// 奖励单号id
	uint64_t	roleGuid = 0;				// 角色guid
	char		itemKeyname[64] = { 0 };	// 物品keyname
	uint32_t	itemNum = { 0 };			// 物品数量
	uint16_t	descLength = 0;				// 描述数据长度
	char		desc[64] = { 0 };			// 描述数据
};
// 礼包
struct LogGiftPackData
{
	LogGiftPackData(const string& gn, uint64_t gu, uint64_t ru, const string& ikn, uint32_t num, const string& des = EMPTYSTR)
	{
		strncpy_s(giftName, gn.c_str(), sizeof(giftName) - 1);
		giftGuid = gu;
		roleGuid = ru;
		strncpy_s(itemKeyname, ikn.c_str(), sizeof(itemKeyname) - 1);
		itemNum = num;
		strncpy_s(desc, des.c_str(), sizeof(desc) - 1);
		descLength = strlen(desc);
	}
	char		giftName[64] = { 0 };		// 礼包名称
	uint64_t	giftGuid = 0;				// 礼包单号id
	uint64_t	roleGuid = 0;				// 角色guid
	char		itemKeyname[64] = { 0 };	// 物品keyname
	uint32_t	itemNum = { 0 };			// 物品数量
	uint16_t	descLength = 0;				// 描述数据长度
	char		desc[64] = { 0 };			// 描述数据
};
// 回收
struct LogRecoveryData
{
	LogRecoveryData(uint64_t reu, uint64_t ru, const string& ikn, uint32_t num, const string& des = EMPTYSTR)
	{
		recoveryGuid = reu;
		roleGuid = ru;
		strncpy_s(itemKeyname, ikn.c_str(), sizeof(itemKeyname) - 1);
		itemNum = num;
		strncpy_s(desc, des.c_str(), sizeof(desc) - 1);
		descLength = strlen(desc);
	}
	uint64_t	recoveryGuid = 0;			// 回收单号id
	uint64_t	roleGuid = 0;				// 角色guid
	char		itemKeyname[64] = { 0 };	// 物品keyname
	uint32_t	itemNum = { 0 };			// 物品数量
	uint16_t	descLength = 0;				// 描述数据长度
	char		desc[64] = { 0 };			// 描述数据
};
// db sql
struct LogDBSql
{
	LogDBSql() {}
	uint8_t	beLastPack = 1;
	uint8_t result = 0;
	char dbSqlStr[65530] = { 0 };
};
// 物品动态属性
struct LogItemDynAttr
{
	LogItemDynAttr(uint64_t gid, uint16_t idx, uint16_t att, int32_t val)
	{
		guid = gid;
		index = idx;
		attr = att;
		value = val;
	}
	uint64_t guid = 0;
	uint16_t index = 0;
	uint16_t attr = 0;
	int32_t value = 0;
};
// 物品自定义属性
struct LogItemCustVar
{
	LogItemCustVar(uint64_t gid, const std::string& n, const std::string& v, uint8_t t, uint64_t exp)
	{
		belong = gid;
		strncpy_s(name, n.c_str(), sizeof(name) - 1);
		strncpy_s(value, v.c_str(), sizeof(value) - 1);
		type = t;
		expire = exp;
	}
	uint64_t belong = 0;
	char name[64] = { 0 };
	char value[65440] = { 0 };
	uint8_t type = 0;
	uint64_t expire = 0;
};

struct ProtoLog_LoggingReq
{
	DEF_PROTO_HEADER_LOG(PROTO_LOG_LOGGING_REQ);
	ProtoLog_LoggingReq() {}
	void Clear()
	{
		memset(this, 0, sizeof(ProtoLog_LoggingReq));
		REDEF_PROTO_HEADER_LOG(PROTO_LOG_LOGGING_REQ);
	}
	void Init(const std::string& ip, uint16_t port, uint16_t sType, uint32_t id, uint16_t type, uint64_t time)
	{
		memcpy(serverIp, ip.c_str(), ip.size());
		serverPort = port;
		serverType = sType;
		serverId = id;
		logType = type;
		timestamp = time;
	}
	template<class T>
	void operator<<(const T& lc)
	{
		logLength = sizeof(lc);
		memcpy(logContent, &lc, logLength);
	}
	template<class T>
	void operator>>(T& lc) const
	{
		memcpy(&lc, logContent, logLength);
	}
	template<class T>
	void operator>>(T*& lc) const
	{
		lc = (T*)logContent;
	}
	char serverIp[16] = { 0 };
	uint16_t serverPort = 0;
	uint16_t serverType = 0;		// 服务器类型
	uint32_t serverId = 0;			// 服务器id(预留)
	uint16_t logType = 0;			// 日志类型log_type
	uint64_t timestamp = 0;			// 时间戳
	uint16_t logLength = 0;			// 日志数据长度
	char logContent[65536] = { 0 };	// 日志数据长度
};


struct TRADE_RECORD
{
	LogTradeData	logTradeData;
	ITEM_INFO		item;
};
using SP_TRADE_RECORD = std::shared_ptr<TRADE_RECORD>;
using SP_TRADE_RECORD_MAP = std::map<uint64_t, SP_TRADE_RECORD>;

class ProtoLog
{
public:
	ProtoLog();
	~ProtoLog();

	static inline uint16_t GetModuleID(void) { return MODULE_TYPE_LOG; }
	static inline uint16_t GetProtocolNum(void) { return PROTO_LOG_MAX; }

	int BuildProtocol(void* pHost, char* pNet, int iNetSize);
	int HandleProtocol(void* pHost, char* pNet, int iNetSize);

private:
	EnCodeFunc m_EnCodeFuncArray[PROTO_LOG_MAX];
	DeCodeFunc m_DeCodeFuncArray[PROTO_LOG_MAX];
};
