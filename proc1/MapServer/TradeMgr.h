#pragma once
#include "Types.h"
#include "DataInfo.hpp"
#include "ProtoCS.h"

#define TYPE_KEY_ALL		0
#define SUB_TYPE_KEY_ALL	0

class Session;
class Player;
struct TradeItemTypeKey
{
	uint32_t type = 0;
	uint32_t subType = 0;
	TradeItemTypeKey(uint32_t t, uint32_t st) : type(t), subType(st) {}
	bool operator<(const TradeItemTypeKey& tk) const
	{
		if (type < tk.type)
			return true;
		if (type == tk.type)
		{
			if (subType < tk.subType)
				return true;
		}
		return false;
	}
	bool operator==(const TradeItemTypeKey& tk) const
	{
		return (type == tk.type && subType == tk.subType);
	}
};
typedef std::shared_ptr<TradeItemTypeKey> TradeItemTypeKeyPtr;

struct TradeItemNameKey
{
	std::string cfgName = "";
	std::string keyName = "";
	std::string name = "";
	TradeItemNameKey() {}
	TradeItemNameKey(std::string& n, std::string& kn, std::string& cn) : name(n), keyName(kn), cfgName(cn) {}
	//bool operator<(const TradeItemNameKey& tk) const
	//{
	//	if (cfgName < tk.cfgName)
	//		return true;
	//	if (cfgName == tk.cfgName)
	//	{
	//		if (name < tk.name)
	//			return true;
	//	}
	//	return false;
	//}
	//bool operator==(const TradeItemNameKey& tk) const
	//{
	//	return (cfgName == tk.cfgName && name == tk.name);
	//}
};
template<typename T>
struct TradeItemNameValue
{
	TradeItemNameKey	nameKey;
	T					delegateInfo;	// 信息SP_BUY_DELEGATE,SP_SELL_DELEGATE
};

typedef std::unordered_map<std::string, SP_BUY_DELEGATE_LIST> SP_BUY_DELEGATE_ITEM_KEYNAME_MAP;
typedef std::unordered_map<std::string, SP_SELL_DELEGATE_LIST> SP_SELL_DELEGATE_ITEM_KEYNAME_MAP;
typedef std::list<TradeItemNameValue<SP_BUY_DELEGATE>>	BUY_DELEGATE_NAMEINFO_LIST;
typedef std::list<TradeItemNameValue<SP_SELL_DELEGATE>>	SELL_DELEGATE_NAMEINFO_LIST;
struct TradeItemTypeValue
{
	TradeItemTypeValue() 
	{
		buy.clear();
		buyKeyNameMap.clear();
		buyNameList.clear();
		sell.clear();
		sellKeyNameMap.clear();
		sellNameList.clear();
	}
	SP_BUY_DELEGATE_MAP					buy;
	SP_BUY_DELEGATE_ITEM_KEYNAME_MAP	buyKeyNameMap;
	BUY_DELEGATE_NAMEINFO_LIST			buyNameList;
	SP_SELL_DELEGATE_MAP				sell;
	SP_SELL_DELEGATE_ITEM_KEYNAME_MAP	sellKeyNameMap;
	SELL_DELEGATE_NAMEINFO_LIST			sellNameList;
};
// 类型区域->交易信息
typedef std::map<TradeItemTypeKeyPtr, TradeItemTypeValue> ITEM_TYPE_DELEGATE_INFO_MAP;

template<typename T>
struct DelegateInfoValue
{
	TradeItemTypeKeyPtr	typeKey;		// 类型区域
	TradeItemNameKey	nameKey;		// name信息
	T					delegateInfo;	// 信息SP_BUY_DELEGATE,SP_SELL_DELEGATE
};
// 交易id->交易信息
typedef std::unordered_map<uint64_t, DelegateInfoValue<SP_BUY_DELEGATE>>	BUY_DELEGATE_INFO_MAP;
typedef std::unordered_map<uint64_t, DelegateInfoValue<SP_SELL_DELEGATE>>	SELL_DELEGATE_INFO_MAP;

// 检测放到cs里做
#define checktime 5000;

template<class T>
struct TradeIter
{
public:
	T it;
	T end;
};

class TradeMgr
{
	DECL_SINGLETON(TradeMgr)
public:
	// 服务器启动获取交易行委托数据
	void HandleGetTradeBuyDelegateAck(const ProtoCS_GetTradeBuyDelegateAck& msg);
	void HandleGetTradeSellDelegateAck(const ProtoCS_GetTradeSellDelegateAck& msg);
	void HandleGetTradeRecordsAck(const ProtoCS_GetTradeRecordsAck& msg);
	// 获取玩家的委托信息
	void GetPlayerDelegateList(uint64_t roleid, SP_BUY_DELEGATE_LIST& list);
	void GetPlayerDelegateList(uint64_t roleid, SP_SELL_DELEGATE_LIST& list);
	void GetPlayerBuyRecordsList(uint64_t roleid, SP_TRADE_RECORD_MAP& map);
	void GetPlayerSellRecordsList(uint64_t roleid, SP_TRADE_RECORD_MAP& map);
	//void DelegateCheck();
	//void DelegateCancel(uint64_t did);
	// request
	uint32_t HandleRecordsMineReq(Session* session, const ProtoGS_RecordsMineReq& req, Player* player);
	uint32_t HandleDelegateMineReq(Session* session, const ProtoGS_DelegateMineReq& req, Player* player);
	uint32_t HandleDelegateListReq(Session* session, ProtoGS_DelegateListReq& req, Player* player);
	uint32_t HandleDelegateCancelReq(Session* session, const ProtoGS_DelegateCancelReq& req, Player* player);
	uint32_t HandleDelegateSellCmd(Session* session, const ProtoGS_DelegateSellCmd& req, Player* player);
	uint32_t HandleDelegateBuyCmd(Session* session, const ProtoGS_DelegateBuyCmd& req, Player* player);
	uint32_t HandleMarketSellCmd(Session* session, const ProtoGS_MarketSellCmd& req, Player* player);
	uint32_t HandleMarketBuyCmd(Session* session, const ProtoGS_MarketBuyCmd& req, Player* player);
	// ack
	void HandleRecordsCancelAck(const ProtoCS_RecordsCancelAck& ack);
	void HandleDelegateCancelAck(const ProtoCS_DelegateCancelAck& ack, Player* player);
	void HandleDelegateSellAck(const ProtoCS_DelegateSellAck& ack, Player* player);
	void HandleDelegateBuyAck(const ProtoCS_DelegateBuyAck& ack, Player* player);
	void HandleMarketSellAck(const ProtoCS_MarketSellAck& ack, Player* player);
	void HandleMarketBuyAck(const ProtoCS_MarketBuyAck& ack, Player* player);
private:
	// 添加委托数据
	SP_BUY_DELEGATE SetDelegate(const DELEGATE_BUY_ITEM2& tradeInfo);
	SP_SELL_DELEGATE SetDelegate(const DELEGATE_SELL_ITEM& tradeInfo);
	/*using*/
	uint32_t HandDelegateSellListReqEx(Session* session, ProtoGS_DelegateListReq& req);
	uint32_t HandDelegateBuyListReqEx(Session* session, ProtoGS_DelegateListReq& req);
	/*呵呵*/
	uint32_t HandDelegateSellListReq(Session* session, ProtoGS_DelegateListReq& req);
	uint32_t HandDelegateBuyListReq(Session* session, ProtoGS_DelegateListReq& req);
	// 处理取消委托
	void HandleDeleteSellDelegate(uint64_t tradeid, Player* player);
	void HandleDeleteBuyDelegate(uint64_t tradeid, Player* player);
	void HandleAddRecords(const TRADE_RECORD& tr);
	void HandleDeleteRecords(uint64_t tradeId);
private:
	bool GenerateItemTypeInfo(uint16_t itemId, TradeItemTypeKeyPtr& typeKey, std::string& keyName, std::string& cfgName);
	bool GetTradeItemTypeKeyPtr(uint32_t type, uint32_t subType, TradeItemTypeKeyPtr& typeKey);
	TradeItemTypeValue& GetTradeItemTypeValue(const TradeItemTypeKeyPtr& typeKey);
	void CheckTypeKey(uint32_t type, uint32_t subType, TradeItemTypeKey& tk);
	template<typename T>
	void GenerateCurTime(T& curTime);
private:
	TradeMgr();
	~TradeMgr();

	// 总表
	BUY_DELEGATE_INFO_MAP			mBuyDelegate;
	SELL_DELEGATE_INFO_MAP			mSellDelegate;

	// 划分
	ITEM_TYPE_DELEGATE_INFO_MAP		mItemTypeDelegate;

	std::list<TradeItemTypeKeyPtr>	mTradeItemTypeKeyPtrList;

	int64_t mTradeDelegateTime = 0;		// 委托时间

	SP_TRADE_RECORD_MAP				mTradeRecord;
};

template<typename T>
void TradeMgr::GenerateCurTime(T& curTime)
{
	curTime = static_cast<T>(time(nullptr));
}