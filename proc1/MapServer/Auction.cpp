#include "stdafx.h"
#include "Auction.h"

IMPL_SINGLETON(AuctionHouse)

void AuctionHouse::AddAuctionItemInfo(const CLuaObject& info)
{
	ProtoMS_SynAuctionItemInfo data;
	int num = 0;
	for (luabind::iterator it(info), end; it != end; ++it,++num)
	{
		AUCTION_HOUSE_ITEM_INFO curInfo;
		if (luabind::type((*it)[1]) != LUA_TSTRING) return;
		auto item_name = luabind::object_cast<std::string>((*it)[1]);
		strcpy_s(curInfo.item_name, _countof(curInfo.item_name), item_name.c_str());
		if (luabind::type((*it)[2]) != LUA_TNUMBER) return;
		auto item_num = luabind::object_cast<uint16_t>((*it)[2]);
		curInfo.item_num = item_num;
		if (luabind::type((*it)[3]) != LUA_TNUMBER) return;
		auto item_price = luabind::object_cast<int>((*it)[3]);
		curInfo.item_price = item_price;
		if (luabind::type((*it)[4]) != LUA_TNUMBER) return;
		auto currency_type = luabind::object_cast<uint8_t>((*it)[4]);
		curInfo.currency_type = currency_type;
		if (luabind::type((*it)[5]) != LUA_TSTRING) return;
		auto start_time = luabind::object_cast<std::string>((*it)[5]);
		curInfo.start_time = ITimeHelper::GetInstance()->ConvertStringToTime(start_time, DTFMTB1);
		auto keep_time = luabind::object_cast<uint64_t>((*it)[6]);
		curInfo.keep_time = keep_time;
		auto orderid = GenerateObjID(E_OBJ_AUCTION, ConfigInfo::GetInstance());
		curInfo.orderID = orderid;

		//添加拍卖开始结束的定时器
		int64_t stamp = ITimeHelper::GetInstance()->ConvertStringToTime(start_time, DTFMTB1);
		int64_t curstamp = time(nullptr);
		int64_t timegap = curstamp - stamp;
		if (timegap < 0) {
			//等待拍卖开始
			curInfo.status = AUCTION_HOUSE_ITEM_INFO::auction_status_type_wait;
			TimerData timer;
			timer.loop = false;
			timer.interval = S2MS(stamp - curstamp);
			timer.callBack = [curInfo, this](const TimerData&) {
				//拍卖开始
				StartAcution(curInfo.orderID);
				TimerData _timer;
				_timer.loop = false;
				_timer.interval = S2MS(curInfo.keep_time);
				_timer.callBack = [curInfo, this](const TimerData&) {
					//拍卖结束
					EndAuction(curInfo);
				};
				ITimeHelper::GetInstance()->AddTimer(_timer);
			};
			ITimeHelper::GetInstance()->AddTimer(timer);

		}
		else if (timegap >= 0 && timegap <= keep_time) {
			curInfo.status = AUCTION_HOUSE_ITEM_INFO::auction_status_type_ing;
			TimerData timer;
			timer.loop = false;
			timer.interval = S2MS(stamp + keep_time - curstamp);
			timer.callBack = [curInfo, this](const TimerData&) {
				EndAuction(curInfo);
			};
			ITimeHelper::GetInstance()->AddTimer(timer);
		}
		else {
			curInfo.status = AUCTION_HOUSE_ITEM_INFO::auction_status_type_passin;
			data.info[num] = curInfo;
			continue;
		}
		mAuctionHouseItemList[orderid] = curInfo;
		data.info[num] = curInfo;
	}
	data.num = num;
	CLuaObject luaRet = NewLuaObj();
	for (int i = 0; i < data.num; ++i)
	{
		CLuaObject curInfo = NewLuaObj();
		AddInfoToTable(curInfo, data.info[i]);
		luaRet[i + 1] = curInfo;
	}
	LuaRet = luaRet;
	TRIGGER_EVENT(trigger_auction_add);
	SendItemInfoToCS(data, ProtoMS_SynAuctionItemInfo::add);
}

bool AuctionHouse::OfferPrice(const std::string& guid, const std::string& orderID, int price)
{
	std::string last_name;
	uint64_t last_guid = 0;
	int last_price = 0;
	auto* player = MapRoleMgr::GetInstance()->FindPlayer(std::stoull(guid));
	if (!player)return false;

	auto iter = mAuctionHouseItemList.find(std::stoull(orderID));
	if (iter == mAuctionHouseItemList.end())return false;

	if (price > iter->second.item_price)
	{
		last_guid = iter->second.ownerID;
		last_name = iter->second.ownerName;
		last_price = iter->second.item_price;
		iter->second.item_price = price;
		iter->second.ownerID = std::stoull(guid);
		strcpy_s(iter->second.ownerName, _countof(iter->second.ownerName), player->GetName().c_str());
		ProtoMS_SynAuctionItemInfo data;
		data.num = 1;
		AddInfoToArr(data, iter->second);
		SendItemInfoToCS(data, ProtoMS_SynAuctionItemInfo::updata);
		LuaBindCallVoid("OfferPriceSuccess.main", std::to_string(iter->second.orderID), last_price, price, std::to_string(last_guid), last_name);
		TRIGGER_EVENT(trigger_auction_price_update);
		return true;
	}
	return false;
}

void AuctionHouse::StartAcution(uint64_t orderID)
{
	auto iter = mAuctionHouseItemList.find(orderID);
	if (iter != mAuctionHouseItemList.end())
	{
		iter->second.status = AUCTION_HOUSE_ITEM_INFO::auction_status_type_ing;
		CLuaObject luaRet = NewLuaObj();
		AddInfoToTable(luaRet, iter->second);
		TRIGGER_EVENT(trigger_auction_start);
		ProtoMS_SynAuctionItemInfo data;
		data.num = 1;
		AddInfoToArr(data, iter->second);
		SendItemInfoToCS(data, ProtoMS_SynAuctionItemInfo::updata);
	}

}

void AuctionHouse::EndAuction(AUCTION_HOUSE_ITEM_INFO info)
{
	auto iter = mAuctionHouseItemList.find(info.orderID);
	if (iter != mAuctionHouseItemList.end())
	{
		if (iter->second.ownerID)
		{
			iter->second.status = AUCTION_HOUSE_ITEM_INFO::auction_status_type_end;
			//发给拥有者
			SendAuctionItemToOwner(iter->second);
		}
		else
		{
			iter->second.status = AUCTION_HOUSE_ITEM_INFO::auction_status_type_passin;
		}
		ProtoMS_SynAuctionItemInfo data;
		data.num = 1;
		AddInfoToArr(data, iter->second);
		SendItemInfoToCS(data, ProtoMS_SynAuctionItemInfo::updata);

		CLuaObject luaRet = NewLuaObj();
		AddInfoToTable(luaRet, info);
		TRIGGER_EVENT(trigger_auction_end);
		mAuctionHouseItemList.erase(iter);
	}
}

void AuctionHouse::SendItemInfoToCS(ProtoMS_SynAuctionItemInfo& info, uint16_t opt_type)
{
	info.type = opt_type;
	SendDataBySessionType(SESSION_TYPE_MS2CS, info);
}

void AuctionHouse::SendAuctionItemToOwner(AUCTION_HOUSE_ITEM_INFO& info)
{
	MSG_BUFFER_DATA(ProtoMS_AddSysNewMail, data);
	if (info.ownerID == 0)return;
	data.guid[0] = info.ownerID;
	data.num = 1;
	data.addType = ProtoMS_AddSysNewMail::add_type_by_guid;
	data.infos.type = eMail_Type_Auction;
	strcpy_s(data.infos.title, sizeof(data.infos.title), "拍卖行");
	strcpy_s(data.infos.text, sizeof(data.infos.text), "请查收拍卖所得物品");
	MailMgr::AddMailSys2Player(data);

}

void AuctionHouse::GetAuctionHouseFromCS(ProtoMS_SynAuctionItemInfo& info)
{
	for (int i = 0; i < info.num; ++i)
	{
		if (!info.info[i].orderID)continue;
		if (info.info[i].status == AUCTION_HOUSE_ITEM_INFO::auction_status_type_wait)
		{
			int64_t curstamp = GetTimeStampMillisecond();
			int64_t timegap = S2MS(info.info[i].start_time) - curstamp;

			TimerData timer;
			timer.loop = false;
			timer.interval = timegap;
			AUCTION_HOUSE_ITEM_INFO data = info.info[i];
			timer.callBack = [data, this](const TimerData&) {
				StartAcution(data.orderID);
				TimerData _timer;
				_timer.loop = false;
				_timer.interval = S2MS(data.keep_time);
				_timer.callBack = [data, this](const TimerData&) {
					EndAuction(data);
				};
				ITimeHelper::GetInstance()->AddTimer(_timer);
			};
			ITimeHelper::GetInstance()->AddTimer(timer);
		}
		else
		{
			int64_t curstamp = GetTimeStampMillisecond();

			TimerData timer;
			timer.loop = false;
			timer.interval = S2MS(info.info[i].start_time + info.info[i].keep_time) - curstamp;
			AUCTION_HOUSE_ITEM_INFO data = info.info[i];
			timer.callBack = [data, this](const TimerData&) {
				EndAuction(data);
			};
			ITimeHelper::GetInstance()->AddTimer(timer);
		}
		mAuctionHouseItemList[info.info[i].orderID] = info.info[i];
	}
}

void AuctionHouse::AddInfoToArr(ProtoMS_SynAuctionItemInfo& info, AUCTION_HOUSE_ITEM_INFO& from)
{
	strcpy_s(info.info[0].item_name, _countof(info.info[0].item_name), from.item_name);
	info.info[0].item_num = from.item_num;
	info.info[0].item_price = from.item_price;
	info.info[0].currency_type = from.currency_type;
	info.info[0].keep_time = from.keep_time;
	info.info[0].orderID = from.orderID;
	info.info[0].ownerID = from.ownerID;
	strcpy_s(info.info[0].ownerName, _countof(info.info[0].ownerName), from.ownerName);
	info.info[0].start_time = from.start_time;
	info.info[0].status = from.status;
}

void AuctionHouse::AddInfoToTable(CLuaObject& to, AUCTION_HOUSE_ITEM_INFO& from)
{
	to[1] = from.item_name;
	to[2] = from.item_num;
	to[3] = from.item_price;
	to[4] = from.currency_type;
	to[5] = from.start_time;
	to[6] = from.keep_time;
	to[7] = std::to_string(from.orderID);
	to[8] = std::to_string(from.ownerID);
	to[9] = from.ownerName;
}

void AuctionHouse::ChangeNameInfo(uint64_t guid, const std::string& name)
{
	for (auto& i : mAuctionHouseItemList) {
		if (i.second.ownerID == guid) {
			strcpy_s(i.second.ownerName, _countof(i.second.ownerName), name);
		}
	}
}