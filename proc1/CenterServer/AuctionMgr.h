#pragma once
#include "ProtoMS.h"
#include "ProtoCS.h"

class  AuctionHouseMgr
{
	DECL_SINGLETON(AuctionHouseMgr)
public:
	AuctionHouseMgr() {};
	~AuctionHouseMgr() {};
	void SynAuctionItemInfo(ProtoMS_SynAuctionItemInfo& info);
	void SyncAuctionItemInfoFromDB(ProtoMS_SynAuctionItemInfo& info);
	void GetFinishedItemInfo(ProtoCS_AuctionGetFinishedInfoAck& data, uint32_t time);

	void ChangeNameInfo(uint64_t guid, const std::string& name);

private:
	AUCTION_HOUSE_ITEM_INFO_LIST mAuctionHouseItemList;
};
