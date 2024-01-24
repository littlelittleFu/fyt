#pragma once
#include"MailMgr.h"
#include "ProtoMS.h"
#include <Lua/LuaScript.h>

class  AuctionHouse
{
	DECL_SINGLETON(AuctionHouse)
public:
	AuctionHouse() {};
	~AuctionHouse() {};

	void AddAuctionItemInfo(const CLuaObject& info);
	bool OfferPrice(const std::string& guid, const std::string& orderID, int price);

	void StartAcution(uint64_t orderID);
	void EndAuction(AUCTION_HOUSE_ITEM_INFO info);

	void SendItemInfoToCS(ProtoMS_SynAuctionItemInfo& info, uint16_t opt_type);
	void SendAuctionItemToOwner(AUCTION_HOUSE_ITEM_INFO& info);

	void GetAuctionHouseFromCS(ProtoMS_SynAuctionItemInfo& info);

	void AddInfoToArr(ProtoMS_SynAuctionItemInfo& info, AUCTION_HOUSE_ITEM_INFO& from);
	void AddInfoToTable(CLuaObject& to, AUCTION_HOUSE_ITEM_INFO& from);

	void ChangeNameInfo(uint64_t guid, const std::string& name);

private:
	AUCTION_HOUSE_ITEM_INFO_LIST mAuctionHouseItemList;
};