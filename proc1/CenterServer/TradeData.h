// ms
#pragma once
#include "Types.h"
#include "DataInfo.hpp"
#include "ProtoCS.h"
#include "ProtoMS.h"

class TradeData
{
	struct PlatformTradeInfo
	{
		PlatformTradeInfo(uint64_t uid, const std::string& name)
		{
			user_id = uid;
			strncpy_s(user_name, name.c_str(), sizeof(user_name) - 1);
		}
		uint64_t		user_id = 0;
		char			user_name[32] = { 0 };
	};

	DECL_SINGLETON(TradeData)
public:
	void SetHasBuyDelegate(bool flag) { mHasBuyDelegate = flag; }
	bool HasBuyDelegate() { return mHasBuyDelegate; }

	void SetHasSellDelegate(bool flag) { mHasSellDelegate = flag; }
	bool HasSellDelegate() { return mHasSellDelegate; }

	void SetHasRecords(bool flag) { mHasRecords = flag; }
	bool HasRecords() { return mHasRecords; }

	void SendTradeDelegateToMS();
	void SendTradeRecordsToMS();

	void HandleGetTradeRecordsAck(ProtoCS_GetTradeRecordsAck& ack);
	void HandleGetTradeBuyDelegateAck(ProtoCS_GetTradeBuyDelegateAck& ack);
	void HandleGetTradeSellDelegateAck(ProtoCS_GetTradeSellDelegateAck& ack);
	void HandleDelegateCancelAck(const ProtoCS_DelegateCancelAck& ack);
	void HandleDelegateSellAck(const ProtoCS_DelegateSellAck& ack);
	void HandleDelegateBuyAck(const ProtoCS_DelegateBuyAck& ack);

	void HandleMarketSellCmd(ProtoMS_MarketSellCmd& req);
	void HandleMarketBuyCmd(ProtoMS_MarketBuyCmd& req);

	void ChangeNameInfo(uint64_t guid, const std::string& name);

	void HandleAllDelegateCancel(uint64_t roleGuid);
	template<typename T>
	void GenerateCurTime(T& curTime);
	static size_t CURLWriteCallback(void* data, size_t size, size_t nmemb, void* userp);
private:
	TradeData();
	~TradeData();

	void FlushTradeTaxRate();
	void HandleDelegateSellCancelAck(const ProtoCS_DelegateCancelAck& ack);
	void HandleDelegateBuyCancelAck(const ProtoCS_DelegateCancelAck& ack);

	void SendTradeBuyDelegateToMS();
	void SendTradeSellDelegateToMS();

	void CheckRecordsExpired();
	void CheckDelegateExpired();
	void SendRecordsExpired(std::set<uint64_t>& expiredSet, std::set<uint64_t>& allExpiredItemSet);
	void SendDelegateExpired(uint8_t delegatetype, std::set<uint64_t>& expiredSet, uint8_t reason = delegate_cancel_expired);

	void GiveBackSellItem(uint64_t guid, const std::string& name, const ITEM_INFO& item, uint32_t token, const std::string& text);
	void SendToPlatform(const PlatformTradeInfo& tradeInfo);
	bool ComposeHttpRequest(const PlatformTradeInfo& tradeInfo, char* buf, int bufsz);
private:

	bool mHasBuyDelegate = false;
	bool mHasSellDelegate = false;

	SP_BUY_DELEGATE_MAP		mBuyDelegate;
	SP_SELL_DELEGATE_MAP	mSellDelegate;

	uint32_t mCheckExpireTimerID = 0;	// 先简单实现一个定时器检测到期(效率差,到时候优化)
	uint32_t TradeTaxRate = 500;		// 万分比
	std::unordered_map<uint64_t, std::string> mNameChange;

	bool mHasRecords = false;
	SP_TRADE_RECORD_MAP		mTradeRecord;
};

template<typename T>
inline void TradeData::GenerateCurTime(T& curTime)
{
	curTime = static_cast<T>(time(nullptr));
}