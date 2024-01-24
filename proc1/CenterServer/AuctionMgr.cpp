#include "stdafx.h"
#include "AuctionMgr.h"

IMPL_SINGLETON(AuctionHouseMgr)

void AuctionHouseMgr::SynAuctionItemInfo(ProtoMS_SynAuctionItemInfo& info)
{
	for (int i = 0; i < info.num; ++i)
	{
		mAuctionHouseItemList[info.info[i].orderID] = info.info[i];
	}
}

void AuctionHouseMgr::SyncAuctionItemInfoFromDB(ProtoMS_SynAuctionItemInfo& info)
{
	for (int i = 0; i < info.num; ++i)
	{
		mAuctionHouseItemList[info.info[i].orderID] = info.info[i];
		if (info.info[i].status == AUCTION_HOUSE_ITEM_INFO::auction_status_type_end
			|| info.info[i].status == AUCTION_HOUSE_ITEM_INFO::auction_status_type_passin)
		{
			info.info[i].orderID = 0;
		}
	}
}

void AuctionHouseMgr::GetFinishedItemInfo(ProtoCS_AuctionGetFinishedInfoAck& data,uint32_t time0)
{
	auto curtime = time(nullptr);
	for (auto& i : mAuctionHouseItemList)
	{
		if (i.second.status == AUCTION_HOUSE_ITEM_INFO::auction_status_type_end 
			|| i.second.status == AUCTION_HOUSE_ITEM_INFO::auction_status_type_passin)
		{
			
			if ((curtime - time0 < i.second.start_time))
			{
				data.info[data.num] = i.second;
				++data.num;
			}
		}
	}
}

void AuctionHouseMgr::ChangeNameInfo(uint64_t guid, const std::string& name)
{
	auto iter = find_if(mAuctionHouseItemList.begin(), mAuctionHouseItemList.end(), [=](const std::pair<uint64_t,AUCTION_HOUSE_ITEM_INFO>& info) {
		if (info.second.ownerID == guid)return true;
		return false;
		});
	if (iter != mAuctionHouseItemList.end()) {
		strcpy_s(iter->second.ownerName, _countof(iter->second.ownerName), name);
	}
}

