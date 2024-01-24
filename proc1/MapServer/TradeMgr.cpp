#include "stdafx.h"
#include "TradeMgr.h"
#include "SessionFactory.h"
#include "CNetManager.h"
#include "Session.h"

IMPL_SINGLETON(TradeMgr)

#define TRADE_RECORDS_MAXCNT 200

TradeMgr::TradeMgr()
{
	mBuyDelegate.clear();
	mSellDelegate.clear();
	mItemTypeDelegate.clear();
	mTradeItemTypeKeyPtrList.clear();
	mTradeRecord.clear();

	mTradeDelegateTime = TRADE_DELEGATE_TIME;
	auto global = sGlobalConfig.GetData();
	if (global && global->TradeDelegateTime)
	{
		mTradeDelegateTime = int64_t(global->TradeDelegateTime) * 3600;
	}
}

TradeMgr::~TradeMgr()
{
}

void TradeMgr::HandleGetTradeBuyDelegateAck(const ProtoCS_GetTradeBuyDelegateAck& msg)
{
	for (uint16_t i = 0; i < msg.num; i++)
	{
		SetDelegate(msg.delegateInfo[i]);
	}
	return;
	// Test
	ProtoGS_DelegateListReq req;
	req.start = 0; 
	req.count = 10;
	req.type = 1;
	req.subtype = 1;
	req.is_reverse = 0; //是否倒序
	req.delegatetype = 1;// 委托类型
	req.sessionid = 0;
	HandleDelegateListReq(nullptr, req, nullptr);
	strcpy_s(req.item_name, sizeof(req.item_name), "鹤嘴锄");
	HandleDelegateListReq(nullptr, req, nullptr);
	strcpy_s(req.item_name, sizeof(req.item_name), "鹤嘴锄1");
	HandleDelegateListReq(nullptr, req, nullptr);
}

void TradeMgr::HandleGetTradeSellDelegateAck(const ProtoCS_GetTradeSellDelegateAck& msg)
{
	for (uint16_t i = 0; i < msg.num; i++)
	{
		SetDelegate(msg.delegateInfo[i]);
	}
	return;
	// Test
	ProtoGS_DelegateListReq req;
	req.start = 0;
	req.count = 10;
	req.type = 1;
	req.subtype = 1;
	req.is_reverse = 0; //是否倒序
	req.delegatetype = 0;// 委托类型
	req.sessionid = 0;
	HandleDelegateListReq(nullptr, req, nullptr);
	strcpy_s(req.item_name, sizeof(req.item_name), "乌木剑");
	HandleDelegateListReq(nullptr, req, nullptr);
	strcpy_s(req.item_name, sizeof(req.item_name), "乌木剑1");
	HandleDelegateListReq(nullptr, req, nullptr);
}

void TradeMgr::HandleGetTradeRecordsAck(const ProtoCS_GetTradeRecordsAck& msg)
{
	for (uint16_t i = 0; i < msg.num; i++)
	{
		HandleAddRecords(msg.trade_record[i]);
	}
}

void TradeMgr::GetPlayerDelegateList(uint64_t roleid, SP_BUY_DELEGATE_LIST& list)
{
	list.clear();
	for (auto& it : mBuyDelegate) 
	{
		if (it.second.delegateInfo->buyer_guid != roleid) 
			continue;

		list.push_back(it.second.delegateInfo);
	}
}

void TradeMgr::GetPlayerDelegateList(uint64_t roleid, SP_SELL_DELEGATE_LIST& list)
{
	list.clear();
	for (auto& it : mSellDelegate)
	{
		if (it.second.delegateInfo->seller_guid != roleid)
			continue;

		list.push_back(it.second.delegateInfo);
	}
}

void TradeMgr::GetPlayerBuyRecordsList(uint64_t roleid, SP_TRADE_RECORD_MAP& map)
{
	map.clear();
	uint32_t tradeRecordsMaxCnt = TRADE_RECORDS_MAXCNT;
	auto global = sGlobalConfig.GetData();
	if (global && global->TradeRecordsMaxCnt)
	{
		tradeRecordsMaxCnt = global->TradeRecordsMaxCnt;
	}
	for (auto& it : mTradeRecord)
	{
		if (map.size() >= tradeRecordsMaxCnt) break;
		if (it.second->logTradeData.buyerGuid != roleid) continue;
		
		map.insert(it);
	}
}

void TradeMgr::GetPlayerSellRecordsList(uint64_t roleid, SP_TRADE_RECORD_MAP& map)
{
	map.clear();
	uint32_t tradeRecordsMaxCnt = TRADE_RECORDS_MAXCNT;
	auto global = sGlobalConfig.GetData();
	if (global && global->TradeRecordsMaxCnt)
	{
		tradeRecordsMaxCnt = global->TradeRecordsMaxCnt;
	}
	for (auto& it : mTradeRecord)
	{
		if (map.size() >= tradeRecordsMaxCnt) break;
		if (it.second->logTradeData.sellerGuid != roleid) continue;

		map.insert(it);
	}
}

//////////////////////////request////////////////////////////
uint32_t TradeMgr::HandleRecordsMineReq(Session* session, const ProtoGS_RecordsMineReq& req, Player* player)
{
	if (!session) return ERR_MARKET_NOT_EXIST;
	if (!player) return ERR_MARKET_NOT_EXIST;

	MSG_BUFFER_DATA(ProtoMS_RecordsMineAck, ack);
	ack.role_id = player->GetGUID();
	ack.sessid = req.sessionid;
	ack.type = (ProtoGS_RecordsMineReq::RMR_TYPE::sell == req.type ? req.type : ProtoGS_RecordsMineReq::RMR_TYPE::buy);
	auto& records = (ProtoGS_RecordsMineReq::RMR_TYPE::sell == ack.type ? player->GetTradeSellRecords() : player->GetTradeBuyRecords());
	for (auto& record : records)
	{
		ack.trade_record[ack.count++] = *record.second;
		if (ProtoMS_RecordsMineAck::RMA_MaxSize::Info_Size == ack.count)
		{
			session->SendPkg(&ack, sizeof(ack));
			ack.count = 0;
		}
	}
	ack.last_pack = 1;
	session->SendPkg(&ack, sizeof(ack));
	return ERR_OK;
}

uint32_t TradeMgr::HandleDelegateMineReq(Session* session, const ProtoGS_DelegateMineReq& req, Player* player)
{
	if (!session) return ERR_MARKET_NOT_EXIST;
	if (!player) return ERR_MARKET_NOT_EXIST;

	// 检测是自己的还是假人的
	auto& mBuyDelegateInfo = player->GetBuyDelegateInfo();
	auto& mSellDelegateInfo = player->GetSellDelegateInfo();

	uint64_t curTime = 0;
	int64_t leftTime = 0;
	GenerateCurTime(curTime);

	MSG_BUFFER_DATA(ProtoMS_DelegateMineAck, ack);
	ack.role_id = player->GetGUID();
	ack.sessid = req.sessionid;

	if (mBuyDelegateInfo.empty() && mSellDelegateInfo.empty())
	{
		ack.last_pack = 1;
		session->SendPkg(&ack, sizeof(ack));
		return ERR_OK;
	}
	auto buyIt = mBuyDelegateInfo.begin();
	auto sellIt = mSellDelegateInfo.begin();
	bool buyBreak = false;
	bool sellBreak = false;
	while (!buyBreak || !sellBreak)
	{
		if (!buyBreak && buyIt != mBuyDelegateInfo.end())
		{
			if (*buyIt)
			{
				leftTime = int64_t((*buyIt)->td_time) + (*buyIt)->trade_time - curTime;
				leftTime = std::max<int64_t>(leftTime, 0);
				(*buyIt)->time = static_cast<uint32_t>(leftTime);
				ack.buy_items[ack.count_buy] = *(*buyIt);
				ack.count_buy++;
			}
			++buyIt;
		}
		else
		{
			buyBreak = true;
		}
		if (!sellBreak && sellIt != mSellDelegateInfo.end())
		{
			if (*sellIt)
			{
				leftTime = int64_t((*sellIt)->td_time) + (*sellIt)->trade_time - curTime;
				leftTime = std::max<int64_t>(leftTime, 0);
				(*sellIt)->time = static_cast<uint32_t>(leftTime);
				ack.sell_items[ack.count_sell] = *(*sellIt);
				ack.count_sell++;
			}
			++sellIt;
		}
		else
		{
			sellBreak = true;
		}
		if (ack.count_buy >= ProtoMS_DelegateMineAck::DMA_MaxSize::Info_Size
			|| ack.count_sell >= ProtoMS_DelegateMineAck::DMA_MaxSize::Info_Size)
		{
			session->SendPkg(&ack, sizeof(ack));
			ack.count_buy = 0;
			ack.count_sell = 0;
		}
	};
	ack.last_pack = 1;
	session->SendPkg(&ack, sizeof(ack));
	return ERR_OK;
}

uint32_t TradeMgr::HandleDelegateListReq(Session* session, ProtoGS_DelegateListReq& req, Player* player)
{
	if (delegate_type_sell == req.delegatetype)
	{
		return HandDelegateSellListReqEx(session, req);
	}
	else if (delegate_type_buy == req.delegatetype)
	{
		return HandDelegateBuyListReqEx(session, req);
	}
	return ERR_OK;

	// uint8_t                 is_reverse = 0;			//是否倒序
	if (delegate_type_sell == req.delegatetype)
	{
		return HandDelegateSellListReq(session, req);
	}
	else if (delegate_type_buy == req.delegatetype)
	{
		return HandDelegateBuyListReq(session, req);
	}
	return ERR_OK;
}

uint32_t TradeMgr::HandleDelegateCancelReq(Session* session, const ProtoGS_DelegateCancelReq& req, Player* player)
{
	if (!session) return ERR_MARKET_NOT_EXIST;
	if (!player) return ERR_MARKET_NOT_EXIST;

	auto& mBuyDelegateInfo = player->GetBuyDelegateInfo();
	auto& mSellDelegateInfo = player->GetSellDelegateInfo();

	ProtoMS_DelegateCancelReq msg;
	msg.player_guid = player->GetGUID();;
	msg.trade_id = req.trade_id;
	msg.reason = delegate_cancel_manual;
	msg.token = player->GetToken();
	// buy
	auto buyIt = std::find_if(mBuyDelegateInfo.begin(), mBuyDelegateInfo.end(), [&req](const SP_BUY_DELEGATE& a) {
		return req.trade_id == a->id;
	});
	if (buyIt != mBuyDelegateInfo.end())
	{
		msg.delegate_type = delegate_type_buy;
		SendDataBySessionType(SESSION_TYPE_MS2CS, msg);
		return ERR_OK;
	}
	// sell
	auto sellIt = std::find_if(mSellDelegateInfo.begin(), mSellDelegateInfo.end(), [&req](const SP_SELL_DELEGATE& a) {
		return req.trade_id == a->id;
	});
	if (sellIt != mSellDelegateInfo.end())
	{
		msg.delegate_type = delegate_type_sell;
		SendDataBySessionType(SESSION_TYPE_MS2CS, msg);
		return ERR_OK;
	}
	return ERR_MARKET_NOT_EXIST;
}

uint32_t TradeMgr::HandleDelegateSellCmd(Session* session, const ProtoGS_DelegateSellCmd& req, Player* player)
{	
	if (!player) return ERR_MARKET_CANT_SELL;
	auto roleAttr = player->GetRoleAttr();
	if (!roleAttr) return ERR_MARKET_CANT_SELL;
	auto rolePack = player->GetRolePack();
	if (!rolePack) return ERR_MARKET_CANT_SELL;
	// 物品判断
	auto item = rolePack->FindItem(req.item_guid);
	if (!item) return ERR_MARKET_CANT_SELL;
	// 配置
	auto pConfig = sItemConfig.Get(item->GetTemplateID());
	if (!pConfig) return ERR_MARKET_CANT_SELL;

	// 脚本自行判断上架条件,返回物品上架时间,货币类型,value_type不同版本可能不同,所以货币扣除交给脚本自己处理
	CLuaObject tradeData = NewLuaObj();
	TRIGGER_EVENT_RET<CLuaObject>(tradeData, trigger_pre_trade_delegate_sell, std::to_string(req.role_id), item->GetTemplateID(), std::to_string(req.item_guid), req.value_type, req.item_value);
	if (luabind::type(tradeData["Ret"]) != LUA_TBOOLEAN) return ERR_MARKET_CANT_SELL;
	bool ret = luabind::object_cast<bool>(tradeData["Ret"]);
	if (!ret) return ERR_OK;
	if (luabind::type(tradeData["Type"]) != LUA_TNUMBER || luabind::type(tradeData["TDTime"]) != LUA_TNUMBER) return ERR_MARKET_CANT_SELL;

	uint8_t valueType = luabind::object_cast<uint8_t>(tradeData["Type"]); // 货币类型
	uint32_t tdTime = luabind::object_cast<uint32_t>(tradeData["TDTime"]);// 时间(秒)
	if (valueType >= stall_price_max) valueType = stall_price_gold;
	if (!tdTime) tdTime = mTradeDelegateTime;

	// 同步数据
	player->SyncPlayerData();
	player->ResetSyncPlayerTimer();

	std::string cfgName = pConfig->Name;
	std::string playerName = player->GetName();

	// 等cs返回再加到缓存
	MSG_BUFFER_DATA(ProtoMS_DelegateSellCmd, data);
	data.token = player->GetToken();
	data.sellItem.id = GenerateObjID(E_OBJ_MARKET, ConfigInfo::GetInstance());
	data.sellItem.seller_guid = player->GetGUID();
	strcpy_s(data.sellItem.seller, playerName);
	data.sellItem.item_value = req.item_value;
	data.sellItem.item_unit = req.item_unit;
	GenerateCurTime(data.sellItem.trade_time);
	data.sellItem.value_type = valueType;
	item->GenerateItemInfo(data.sellItem.item);
	data.sellItem.td_time = tdTime;

	SendDataBySessionType(SESSION_TYPE_MS2CS, data);

	rolePack->RemoveItem(data.sellItem.item.base_info.guid, 0, log_params{ "寄售行上架",0, 1 });
	return ERR_OK;
}

uint32_t TradeMgr::HandleDelegateBuyCmd(Session* session, const ProtoGS_DelegateBuyCmd& req, Player* player)
{	
	if (!player) return ERR_MARKET_CANT_PURCHASE;
	auto roleAttr = player->GetRoleAttr();
	if (!roleAttr) return ERR_MARKET_CANT_PURCHASE;
	// 可收购配置
	auto pConfig = sItemConfig.Get(req.item_id);
	if (!pConfig) return ERR_MARKET_CANT_PURCHASE;

	// 脚本自行判断上架条件,返回物品上架时间,货币类型,value_type不同版本可能不同
	CLuaObject tradeData = NewLuaObj();
	TRIGGER_EVENT_RET<CLuaObject>(tradeData, trigger_pre_trade_delegate_buy, std::to_string(req.role_id), req.item_id, req.value_type, req.item_value, req.item_count);
	if (luabind::type(tradeData["Ret"]) != LUA_TBOOLEAN) return ERR_MARKET_CANT_SELL;
	bool ret = luabind::object_cast<bool>(tradeData["Ret"]);
	if (!ret) return ERR_OK;
	if (luabind::type(tradeData["Type"]) != LUA_TNUMBER || luabind::type(tradeData["TDTime"]) != LUA_TNUMBER) return ERR_MARKET_CANT_SELL;

	uint8_t valueType = luabind::object_cast<uint8_t>(tradeData["Type"]); // 货币类型
	uint32_t tdTime = luabind::object_cast<uint32_t>(tradeData["TDTime"]);// 时间(秒)
	if (valueType >= stall_price_max) valueType = stall_price_gold;
	if (!tdTime || tdTime) tdTime = mTradeDelegateTime;

	std::string cfgName = pConfig->Name;
	std::string playerName = player->GetName();

	// 等cs返回再加到缓存
	ProtoMS_DelegateBuyCmd data;
	data.token = player->GetToken();
	data.buyItem.id = GenerateObjID(E_OBJ_MARKET, ConfigInfo::GetInstance());
	data.buyItem.buyer_guid = player->GetGUID();
	strcpy_s(data.buyItem.buyer, playerName);
	GenerateCurTime(data.buyItem.trade_time);
	strcpy_s(data.buyItem.item_name, cfgName);
	data.buyItem.item_template_id = req.item_id;
	data.buyItem.item_num = req.item_count;
	data.buyItem.item_value = req.item_value;
	data.buyItem.item_unit = req.item_unit;
	data.buyItem.value_type = valueType;
	data.buyItem.td_time = tdTime;

	SendDataBySessionType(SESSION_TYPE_MS2CS, data);
	return ERR_OK;
}

uint32_t TradeMgr::HandleMarketSellCmd(Session* session, const ProtoGS_MarketSellCmd& req, Player* player)
{
	if (!player) return ERR_MARKET_NOT_EXIST;
	auto rolePack = player->GetRolePack();
	if (!rolePack) return ERR_MARKET_NOT_EXIST;

	auto buyIt = mBuyDelegate.find(req.trade_id);
	if (buyIt == mBuyDelegate.end()) return ERR_MARKET_NOT_EXIST;

	const auto& buyDelegateInfo = buyIt->second.delegateInfo;
	// 不能向自己卖
	if (buyDelegateInfo->buyer_guid == player->GetGUID()) return ERR_MARKET_CANT_SELL;
	// 物品判断
	auto item = rolePack->FindItem(req.item_guid);
	if (!item) return ERR_MARKET_CANT_SELL;
	if (item->GetTemplateID() != buyDelegateInfo->item_template_id) return ERR_MARKET_CANT_SELL;
	// 数量判断
	 uint32_t sellMaxCount = std::min<uint32_t>(item->GetAmount(), buyDelegateInfo->item_num);
	if (0 == sellMaxCount) return ERR_MARKET_CANT_SELL;

	CLuaObject tradeData = NewLuaObj();
	TRIGGER_EVENT_RET<CLuaObject>(tradeData, trigger_pre_trade_market_sell, std::to_string(req.role_id), item->GetTemplateID(), std::to_string(req.item_guid));
	if (luabind::type(tradeData["Ret"]) != LUA_TBOOLEAN) return ERR_MARKET_CANT_SELL;
	bool ret = luabind::object_cast<bool>(tradeData["Ret"]);
	if (!ret) return ERR_OK;

	// 同步数据
	player->SyncPlayerData();
	player->ResetSyncPlayerTimer();

	std::string playerName = player->GetName();
	MSG_BUFFER_DATA(ProtoMS_MarketSellCmd, data);
	data.token = player->GetToken();
	data.trade_id = req.trade_id;
	data.seller_guid = player->GetGUID();
	strcpy_s(data.seller, playerName);
	data.count = sellMaxCount;
	item->GenerateItemInfo(data.item);
	strcpy_s(data.item.base_info.name, buyDelegateInfo->item_name);
	SendDataBySessionType(SESSION_TYPE_MS2CS, data);

	rolePack->RemoveItem(data.item.base_info.guid, data.count, log_params{ "寄售行出售" });
	return ERR_OK;
}

uint32_t TradeMgr::HandleMarketBuyCmd(Session* session, const ProtoGS_MarketBuyCmd& req, Player* player)
{
	if (!player) return ERR_MARKET_NOT_EXIST;
	auto roleAttr = player->GetRoleAttr();
	if (!roleAttr) return ERR_MARKET_NOT_EXIST;

	auto sellIt = mSellDelegate.find(req.trade_id);
	if (sellIt == mSellDelegate.end()) return ERR_MARKET_NOT_EXIST;

	const auto& sellDelegateInfo = sellIt->second.delegateInfo;
	// 不能买自己的
	if (sellDelegateInfo->seller_guid == player->GetGUID()) return ERR_MARKET_CANT_PURCHASE;
	// 数量判断
	uint32_t buyMaxCount = std::min<uint32_t>(req.count, sellDelegateInfo->item.base_info.amount); 
	if (0 == buyMaxCount) return ERR_MARKET_CANT_PURCHASE;

	CLuaObject tradeData = NewLuaObj();
	TRIGGER_EVENT_RET<CLuaObject>(tradeData, trigger_pre_trade_market_buy, std::to_string(req.role_id), sellDelegateInfo->item.base_info.id, sellDelegateInfo->value_type, sellDelegateInfo->item_value, buyMaxCount);
	if (luabind::type(tradeData["Ret"]) != LUA_TBOOLEAN) return ERR_MARKET_CANT_PURCHASE;
	bool ret = luabind::object_cast<bool>(tradeData["Ret"]);
	if (!ret) return ERR_OK;

	std::string playerName = player->GetName();
	ProtoMS_MarketBuyCmd data;
	data.token = player->GetToken();
	data.trade_id = req.trade_id;
	data.buyer_guid = player->GetGUID();
	strcpy_s(data.buyer, playerName);
	data.count = buyMaxCount;
	SendDataBySessionType(SESSION_TYPE_MS2CS, data);
	return ERR_OK;
}

//////////////////////////request ack////////////////////////////

void TradeMgr::HandleRecordsCancelAck(const ProtoCS_RecordsCancelAck& ack)
{
	for (uint16_t i = 0; i < ack.num; i++)
	{
		HandleDeleteRecords(ack.trade_id[i]);
	}
}

void TradeMgr::HandleDelegateCancelAck(const ProtoCS_DelegateCancelAck& ack, Player* player)
{
	if (ack.err_type) return;
	if (delegate_type_buy == ack.delegate_type)
	{
		HandleDeleteBuyDelegate(ack.trade_id, player);
	}
	else
	{
		HandleDeleteSellDelegate(ack.trade_id, player);
	}
}

void TradeMgr::HandleDelegateSellAck(const ProtoCS_DelegateSellAck& ack, Player* player)
{
	if (ack.err_type) return;
	auto sellDelegate = SetDelegate(ack.sellItem);
	if (!sellDelegate) return;

	if (!player) return;
	auto rolePack = player->GetRolePack();
	if (!rolePack) return;
	auto roleAttr = player->GetRoleAttr();
	if (!roleAttr) return;

	player->TriggerCheckStall();
	auto& list = player->GetSellDelegateInfo();
	list.push_back(sellDelegate);

	TRIGGER_EVENT(trigger_post_trade_delegate_sell, std::to_string(sellDelegate->seller_guid), sellDelegate->item.base_info.id, std::to_string(sellDelegate->item.base_info.guid));
}

void TradeMgr::HandleDelegateBuyAck(const ProtoCS_DelegateBuyAck& ack, Player* player)
{
	if (ack.err_type) return;
	auto buyDelegate = SetDelegate(ack.buyItem);
	if (!buyDelegate) return;

	if (!player) return;
	auto roleAttr = player->GetRoleAttr();
	if (!roleAttr) return;

	auto& list = player->GetBuyDelegateInfo();

	log_params lp{ "寄售行求购" };
	list.push_back(buyDelegate);
	TRIGGER_EVENT(trigger_post_trade_delegate_buy, std::to_string(buyDelegate->buyer_guid), buyDelegate->item_template_id, buyDelegate->value_type, buyDelegate->item_value, buyDelegate->item_num);
}

void TradeMgr::HandleMarketSellAck(const ProtoCS_MarketSellAck& ack, Player* player)
{
	if (!player) return;
	auto rolePack = player->GetRolePack();
	if (!rolePack) return;

	auto buyIt = mBuyDelegate.find(ack.trade_id);
	if (buyIt == mBuyDelegate.end()) return;

	auto& buyDelegateInfo = buyIt->second.delegateInfo;
	// 删除物品
	buyDelegateInfo->item_num -= ack.count;
	TRIGGER_EVENT(trigger_post_trade_market_sell, std::to_string(ack.seller_guid), std::to_string(buyDelegateInfo->buyer_guid), ack.item.base_info.id, std::to_string(ack.item.base_info.guid), ack.count);
	if (ack.remove)
	{
		auto buyPlayer = MapRoleMgr::GetInstance()->FindPlayer(buyDelegateInfo->buyer_guid);
		HandleDeleteBuyDelegate(ack.trade_id, buyPlayer);
	}
}

void TradeMgr::HandleMarketBuyAck(const ProtoCS_MarketBuyAck& ack, Player* player)
{
	if (!player) return;
	auto roleAttr = player->GetRoleAttr();
	if (!roleAttr) return;

	auto sellIt = mSellDelegate.find(ack.trade_id);
	if (sellIt == mSellDelegate.end()) return;

	auto& sellDelegateInfo = sellIt->second.delegateInfo;
	sellDelegateInfo->item.base_info.amount -= ack.count;
	TRIGGER_EVENT(trigger_post_trade_market_buy, std::to_string(ack.buyer_guid), std::to_string(sellDelegateInfo->seller_guid), ack.item.base_info.id, std::to_string(ack.item.base_info.guid), sellDelegateInfo->value_type, sellDelegateInfo->item_value, ack.count);
	if (ack.remove)
	{
		auto sellPlayer = MapRoleMgr::GetInstance()->FindPlayer(sellDelegateInfo->seller_guid);
		HandleDeleteSellDelegate(ack.trade_id, sellPlayer);
	}
}
///////////////////////////////////////////

SP_BUY_DELEGATE TradeMgr::SetDelegate(const DELEGATE_BUY_ITEM2& tradeInfo)
{
	if (mBuyDelegate.find(tradeInfo.id) != mBuyDelegate.end()) return SP_BUY_DELEGATE();
	TradeItemTypeKeyPtr typeKey;
	std::string keyName = "", cfgName = "", name = "";

	if (!GenerateItemTypeInfo(tradeInfo.item_template_id, typeKey, keyName, cfgName)) return SP_BUY_DELEGATE();
	name = cfgName;
	// all
	TradeItemTypeKeyPtr allKey;
	if (!GetTradeItemTypeKeyPtr(0, 0, allKey)) return SP_BUY_DELEGATE();
	// type的所有
	TradeItemTypeKeyPtr typeAllKey;
	if (!GetTradeItemTypeKeyPtr(typeKey->type, 0, typeAllKey)) return SP_BUY_DELEGATE();

	DelegateInfoValue<SP_BUY_DELEGATE> v1;
	TradeItemNameKey nameKey{ name, keyName, cfgName };
	v1.typeKey = typeKey;
	v1.nameKey = nameKey;
	auto delegateInfo = std::make_shared<DELEGATE_BUY_ITEM2>(tradeInfo);
	v1.delegateInfo = delegateInfo;
	mBuyDelegate.insert(std::make_pair(tradeInfo.id, v1));

	TradeItemNameValue<SP_BUY_DELEGATE> nameValue;
	nameValue.nameKey = nameKey;
	nameValue.delegateInfo = delegateInfo;
	TradeItemTypeValue& v2 = GetTradeItemTypeValue(typeKey);
	v2.buy.insert(std::make_pair(tradeInfo.id, delegateInfo));
	auto& value2 = v2.buyKeyNameMap[keyName];
	value2.push_back(delegateInfo);
	v2.buyNameList.push_back(nameValue);

	TradeItemTypeValue& v3 = GetTradeItemTypeValue(allKey);
	v3.buy.insert(std::make_pair(tradeInfo.id, delegateInfo));
	auto& value3 = v3.buyKeyNameMap[keyName];
	value3.push_back(delegateInfo);
	v3.buyNameList.push_back(nameValue);

	TradeItemTypeValue& v4 = GetTradeItemTypeValue(typeAllKey);
	v4.buy.insert(std::make_pair(tradeInfo.id, delegateInfo));
	auto& value4 = v4.buyKeyNameMap[keyName];
	value4.push_back(delegateInfo);
	v4.buyNameList.push_back(nameValue);

	return delegateInfo;
}

SP_SELL_DELEGATE TradeMgr::SetDelegate(const DELEGATE_SELL_ITEM& tradeInfo)
{
	if (mSellDelegate.find(tradeInfo.id) != mSellDelegate.end()) return SP_SELL_DELEGATE();
	TradeItemTypeKeyPtr typeKey;
	std::string keyName = "", cfgName = "", name = "";

	if (!GenerateItemTypeInfo(tradeInfo.item.base_info.id, typeKey, keyName, cfgName)) return SP_SELL_DELEGATE();
	name = tradeInfo.item.base_info.name;
	// all
	TradeItemTypeKeyPtr allKey;
	if (!GetTradeItemTypeKeyPtr(0, 0, allKey)) return SP_SELL_DELEGATE();
	// type的所有
	TradeItemTypeKeyPtr typeAllKey;
	if (!GetTradeItemTypeKeyPtr(typeKey->type, 0, typeAllKey)) return SP_SELL_DELEGATE();

	DelegateInfoValue<SP_SELL_DELEGATE> v1;
	TradeItemNameKey nameKey{ name, keyName, cfgName };
	v1.typeKey = typeKey;
	v1.nameKey = nameKey;
	auto delegateInfo = std::make_shared<DELEGATE_SELL_ITEM>(tradeInfo);
	v1.delegateInfo = delegateInfo;
	mSellDelegate.insert(std::make_pair(tradeInfo.id, v1));

	TradeItemNameValue<SP_SELL_DELEGATE> nameValue;
	nameValue.nameKey = nameKey;
	nameValue.delegateInfo = delegateInfo;
	TradeItemTypeValue& v2 = GetTradeItemTypeValue(typeKey);
	v2.sell.insert(std::make_pair(tradeInfo.id, delegateInfo));
	auto& value2 = v2.sellKeyNameMap[keyName];
	value2.push_back(delegateInfo);
	v2.sellNameList.push_back(nameValue);

	TradeItemTypeValue& v3 = GetTradeItemTypeValue(allKey);
	v3.sell.insert(std::make_pair(tradeInfo.id, delegateInfo));
	auto& value3 = v3.sellKeyNameMap[keyName];
	value3.push_back(delegateInfo);
	v3.sellNameList.push_back(nameValue);

	TradeItemTypeValue& v4 = GetTradeItemTypeValue(typeAllKey);
	v4.sell.insert(std::make_pair(tradeInfo.id, delegateInfo));
	auto& value4 = v4.sellKeyNameMap[keyName];
	value4.push_back(delegateInfo);
	v4.sellNameList.push_back(nameValue);

	return delegateInfo;
}

template<uint16_t Info_Size, class Iter, class AckType>
void GenerateAckEx(Iter& it, Iter& end, bool befilter, std::string& subStr, AckType& ack, std::vector<AckType>& ackVec, uint64_t curTime)
{
	uint64_t leftTime = 0;

	for (; it != end; ++it)
	{
		if (befilter)
		{
			if (it->nameKey.name.size() < subStr.size()) continue;// 优化

			auto pos = it->nameKey.name.find(subStr);
			if (pos == std::string::npos) continue;
		}

		leftTime = int64_t(it->delegateInfo->td_time) + it->delegateInfo->trade_time - curTime;
		leftTime = std::max<int64_t>(leftTime, 0);
		it->delegateInfo->time = static_cast<uint32_t>(leftTime);
		ack.items[ack.count] = *(it->delegateInfo);
		ack.count++;

		if (ack.count >= Info_Size)
		{
			ack.start++;
			ackVec.push_back(ack);
			ack.count = 0;
		}
	}
	if (ack.count)
	{
		ack.start++;
		ackVec.push_back(ack);
		ack.count = 0;
	}
}
uint32_t TradeMgr::HandDelegateSellListReqEx(Session* session, ProtoGS_DelegateListReq& req)
{
	static TradeItemTypeKey tk(0, 0);
	CheckTypeKey(req.type, req.subtype, tk);
	TradeItemTypeKeyPtr typeKey;
	if (!GetTradeItemTypeKeyPtr(tk.type, tk.subType, typeKey))
	{
		return ERR_MARKET_NOT_EXIST;
	}
	std::vector<ProtoMS_DelegateSellListAck> ackVec;
	ackVec.clear();
	MSG_BUFFER_DATA(ProtoMS_DelegateSellListAck, ack);
	const TradeItemTypeValue& v = GetTradeItemTypeValue(typeKey);
	uint32_t total = static_cast<uint32_t>(v.sellNameList.size());
	ack.type = req.type;
	ack.subtype = req.subtype;
	//ack.start = req.start;
	ack.sessid = req.sessionid;
	// 没有数据
	if (0 != total)
	{
		uint64_t curTime = 0;
		GenerateCurTime(curTime);

		bool befilter = (0 != strlen(req.item_name));

		std::string subStr(req.item_name);
		if (!req.is_reverse)
		{
			auto it = v.sellNameList.begin();
			auto end = v.sellNameList.end();
			GenerateAckEx<ProtoMS_DelegateSellListAck::DSLA_MaxSize::Info_Size>(it, end, befilter, subStr, ack, ackVec, curTime);
		}
		else
		{
			auto it = v.sellNameList.rbegin();
			auto end = v.sellNameList.rend();
			GenerateAckEx<ProtoMS_DelegateSellListAck::DSLA_MaxSize::Info_Size>(it, end, befilter, subStr, ack, ackVec, curTime);
		}
	}
	if (ackVec.empty())
	{
		session->SendPkg(&ack, sizeof(ack));
	}
	else
	{
		auto iter = ackVec.begin();
		for (; iter != ackVec.end(); ++iter)
		{
			iter->total = ackVec.size();
			session->SendPkg(&(*iter), sizeof(*iter));
		}
	}
	return ERR_OK;
}

uint32_t TradeMgr::HandDelegateBuyListReqEx(Session* session, ProtoGS_DelegateListReq& req)
{
	static TradeItemTypeKey tk(0, 0);
	CheckTypeKey(req.type, req.subtype, tk);
	TradeItemTypeKeyPtr typeKey;
	if (!GetTradeItemTypeKeyPtr(tk.type, tk.subType, typeKey))
	{
		return ERR_MARKET_NOT_EXIST;
	}
	std::vector<ProtoMS_DelegateBuyListAck> ackVec;
	ackVec.clear();
	ProtoMS_DelegateBuyListAck ack;
	const TradeItemTypeValue& v = GetTradeItemTypeValue(typeKey);
	uint32_t total = static_cast<uint32_t>(v.buyNameList.size());
	ack.type = req.type;
	ack.subtype = req.subtype;
	//ack.start = req.start;
	ack.sessid = req.sessionid;
	// 没有数据
	if (0 != total)
	{
		uint64_t curTime = 0;
		GenerateCurTime(curTime);

		bool befilter = (0 != strlen(req.item_name));

		std::string subStr(req.item_name);
		if (!req.is_reverse)
		{
			auto it = v.buyNameList.begin();
			auto end = v.buyNameList.end();
			GenerateAckEx<ProtoMS_DelegateBuyListAck::DBLA_MaxSize::Info_Size>(it, end, befilter, subStr, ack, ackVec, curTime);
		}
		else
		{
			auto it = v.buyNameList.rbegin();
			auto end = v.buyNameList.rend();
			GenerateAckEx<ProtoMS_DelegateBuyListAck::DBLA_MaxSize::Info_Size>(it, end, befilter, subStr, ack, ackVec, curTime);
		}
	}
	if (ackVec.empty())
	{
		session->SendPkg(&ack, sizeof(ack));
	}
	else
	{
		auto iter = ackVec.begin();
		for (; iter != ackVec.end(); ++iter)
		{
			iter->total = ackVec.size();
			session->SendPkg(&(*iter), sizeof(*iter));
		}
	}
	return ERR_OK;
}

template<uint16_t Info_Size, class Iter, class AckType>
void GenerateAck1(Iter& it, Iter& end, AckType& ack, uint64_t curTime)
{
	uint64_t leftTime = 0;
	while (it != end && ack.count < Info_Size)
	{
		leftTime = int64_t((*it)->td_time) + (*it)->trade_time - curTime;
		leftTime = std::max<int64_t>(leftTime, 0);
		(*it)->time = static_cast<uint32_t>(leftTime);
		ack.items[ack.count] = *(*it);
		ack.count++;
		it++;
	}
}
template<uint16_t Info_Size, class Iter, class AckType>
void GenerateAck2(Iter& it, Iter& end, AckType& ack, uint64_t curTime)
{
	uint64_t leftTime = 0;
	while (it != end && ack.count < Info_Size)
	{
		leftTime = int64_t(it->second->td_time) + it->second->trade_time - curTime;
		leftTime = std::max<int64_t>(leftTime, 0);
		it->second->time = static_cast<uint32_t>(leftTime);
		ack.items[ack.count] = *(it->second);
		ack.count++;
		it++;
	}
}
uint32_t TradeMgr::HandDelegateSellListReq(Session* session, ProtoGS_DelegateListReq& req)
{
	static TradeItemTypeKey tk(0, 0);
	CheckTypeKey(req.type, req.subtype, tk);
	TradeItemTypeKeyPtr typeKey;
	if (!GetTradeItemTypeKeyPtr(tk.type, tk.subType, typeKey))
	{
		return ERR_MARKET_NOT_EXIST;
	}

	MSG_BUFFER_DATA(ProtoMS_DelegateSellListAck, ack);
	const TradeItemTypeValue& v = GetTradeItemTypeValue(typeKey);
	uint32_t total = static_cast<uint32_t>(v.sell.size());
	ack.type = req.type;
	ack.subtype = req.subtype;
	ack.start = req.start;
	ack.sessid = req.sessionid;
	// 没有数据
	if (0 != total)
	{
		uint64_t curTime = 0;
		GenerateCurTime(curTime);

		// 过滤
		if (0 != strlen(req.item_name))
		{
			auto iter = v.sellKeyNameMap.find(std::string(req.item_name));
			if (iter != v.sellKeyNameMap.end())
			{
				const auto& list = iter->second;
				ack.total = static_cast<uint32_t>(list.size());
				// 不超出列表长度
				if (0 != ack.total && req.start < ack.total)
				{
					// 截取区间
					if (!req.is_reverse)
					{
						auto it = std::next(list.begin(), req.start);
						auto end = (req.start + req.count <= ack.total) ? std::next(it, req.count) : list.end();
						GenerateAck1<ProtoMS_DelegateSellListAck::DSLA_MaxSize::Info_Size>(it, end, ack, curTime);
					}
					else
					{
						auto it = std::next(list.rbegin(), req.start);
						auto end = (req.start + req.count <= ack.total) ? std::next(it, req.count) : list.rend();
						GenerateAck1<ProtoMS_DelegateSellListAck::DSLA_MaxSize::Info_Size>(it, end, ack, curTime);
					}
				}
			}
		}
		else// 不过滤
		{
			ack.total = total;
			const auto& map = v.sell;
			// 不超出表长度
			if (0 != ack.total && req.start < ack.total)
			{
				// 截取区间
				if (!req.is_reverse)
				{
					auto it = std::next(map.begin(), req.start);
					auto end = (req.start + req.count <= ack.total) ? std::next(it, req.count) : map.end();
					GenerateAck2<ProtoMS_DelegateSellListAck::DSLA_MaxSize::Info_Size>(it, end, ack, curTime);
				}
				else
				{
					auto it = std::next(map.rbegin(), req.start);
					auto end = (req.start + req.count <= ack.total) ? std::next(it, req.count) : map.rend();
					GenerateAck2<ProtoMS_DelegateSellListAck::DSLA_MaxSize::Info_Size>(it, end, ack, curTime);
				}
			}
		}
	}
	session->SendPkg(&ack, sizeof(ack));
	return ERR_OK;
}

uint32_t TradeMgr::HandDelegateBuyListReq(Session* session, ProtoGS_DelegateListReq& req)
{
	static TradeItemTypeKey tk(0, 0);
	CheckTypeKey(req.type, req.subtype, tk);
	TradeItemTypeKeyPtr typeKey;
	if (!GetTradeItemTypeKeyPtr(tk.type, tk.subType, typeKey))
	{
		return ERR_MARKET_NOT_EXIST;
	}
	ProtoMS_DelegateBuyListAck ack;
	const TradeItemTypeValue& v = GetTradeItemTypeValue(typeKey);
	uint32_t total = static_cast<uint32_t>(v.buy.size());
	ack.type = req.type;
	ack.subtype = req.subtype;
	ack.start = req.start;
	ack.sessid = req.sessionid;
	// 没有数据
	if (0 != total)
	{
		uint64_t curTime = 0;
		GenerateCurTime(curTime);

		// 过滤
		if (0 != strlen(req.item_name))
		{
			auto iter = v.buyKeyNameMap.find(std::string(req.item_name));
			if (iter != v.buyKeyNameMap.end())
			{
				const auto& list = iter->second;
				ack.total = static_cast<uint32_t>(list.size());
				// 不超出列表长度
				if (0 != ack.total && req.start < ack.total)
				{
					// 截取区间
					if (!req.is_reverse)
					{
						auto it = std::next(list.begin(), req.start);
						auto end = (req.start + req.count <= ack.total) ? std::next(it, req.count) : list.end();
						GenerateAck1<ProtoMS_DelegateBuyListAck::DBLA_MaxSize::Info_Size>(it, end, ack, curTime);
					}
					else
					{
						auto it = std::next(list.rbegin(), req.start);
						auto end = (req.start + req.count <= ack.total) ? std::next(it, req.count) : list.rend();
						GenerateAck1<ProtoMS_DelegateBuyListAck::DBLA_MaxSize::Info_Size>(it, end, ack, curTime);
					}
				}
			}
		}
		else// 不过滤
		{
			ack.total = total;
			const auto& map = v.buy;
			// 不超出表长度
			if (0 != ack.total && req.start < ack.total)
			{
				// 截取区间
				if (!req.is_reverse)
				{
					auto it = std::next(map.begin(), req.start);
					auto end = (req.start + req.count <= ack.total) ? std::next(it, req.count) : map.end();
					GenerateAck2<ProtoMS_DelegateBuyListAck::DBLA_MaxSize::Info_Size>(it, end, ack, curTime);
				}
				else
				{
					auto it = std::next(map.rbegin(), req.start);
					auto end = (req.start + req.count <= ack.total) ? std::next(it, req.count) : map.rend();
					GenerateAck2<ProtoMS_DelegateBuyListAck::DBLA_MaxSize::Info_Size>(it, end, ack, curTime);
				}
			}
		}
	}
	session->SendPkg(&ack, sizeof(ack));
	return ERR_OK;
}

void DeleteSellDelegate(uint64_t tradeid, Player* player)
{
	if (!player) return;

	auto& mSellDelegateInfo = player->GetSellDelegateInfo();
	auto sellIt = std::find_if(mSellDelegateInfo.begin(), mSellDelegateInfo.end(), [&tradeid](const SP_SELL_DELEGATE& a) {
		return tradeid == a->id;
		});
	if (sellIt != mSellDelegateInfo.end())
	{
		mSellDelegateInfo.erase(sellIt);
	}
}
void TradeMgr::HandleDeleteSellDelegate(uint64_t tradeid, Player* player)
{
	StallDummy* stallDummy = nullptr;
	if (player)
	{
		DeleteSellDelegate(tradeid, player);
		stallDummy = player->GetStallDummy();
	}

	auto sellIt = mSellDelegate.find(tradeid);
	if (sellIt == mSellDelegate.end())
	{
		LOG_ERROR("[%s:%d] tradeid:%" PRIu64 " not exist.", FUNC_LINE, tradeid);
	}
	else
	{
		// typeKey
		const auto& typeKey = sellIt->second.typeKey;
		const auto& delegateInfo = sellIt->second.delegateInfo;
		const auto& nameKey = sellIt->second.nameKey;
		std::string itemKeyName(nameKey.keyName);
		if (!stallDummy) stallDummy = MapRoleMgr::GetInstance()->FindStallDummy(delegateInfo->seller_guid, 0);
		// 及时清除缓存
		DeleteSellDelegate(tradeid, stallDummy);
		// all
		TradeItemTypeKeyPtr allKey;
		GetTradeItemTypeKeyPtr(0, 0, allKey);
		// type的所有
		TradeItemTypeKeyPtr typeAllKey;
		GetTradeItemTypeKeyPtr(typeKey->type, 0, typeAllKey);
		std::list<TradeItemTypeKeyPtr> l;
		l.push_back(typeKey);
		l.push_back(allKey);
		l.push_back(typeAllKey);
		auto it = l.begin();
		for (; it != l.end(); ++it)
		{
			auto itemTypeIt = mItemTypeDelegate.find(*it);
			if (itemTypeIt == mItemTypeDelegate.end())
			{
				LOG_ERROR("[%s:%d] type:%u, subType:%u not exist.", FUNC_LINE, (*it)->type, (*it)->subType);
			}
			else
			{
				auto& typeValue = itemTypeIt->second;
				auto sellKeyNameIt = typeValue.sellKeyNameMap.find(itemKeyName);
				if (sellKeyNameIt == typeValue.sellKeyNameMap.end())
				{
					LOG_ERROR("[%s:%d] itemKeyName:%s not exist.", FUNC_LINE, itemKeyName.c_str());
				}
				else
				{
					auto& itemList = sellKeyNameIt->second;
					auto itemListIt = std::find_if(itemList.begin(), itemList.end(), [=](const SP_SELL_DELEGATE& a) {
						return a->id == tradeid;
					});
					if (itemListIt == itemList.end())
					{
						LOG_ERROR("[%s:%d] itemKeyName:%s, tradeid:%" PRIu64 " not exist.", FUNC_LINE, itemKeyName.c_str(), tradeid);
					}
					else
					{
						itemList.erase(itemListIt);
					}
				}

				auto itemListIt = std::find_if(typeValue.sellNameList.begin(), typeValue.sellNameList.end(), [=](const TradeItemNameValue<SP_SELL_DELEGATE>& a) {
					return a.delegateInfo->id == tradeid;
					});
				if (itemListIt == typeValue.sellNameList.end())
				{
					LOG_ERROR("[%s:%d] itemKeyName:%s, tradeid:%" PRIu64 " not exist.", FUNC_LINE, itemKeyName.c_str(), tradeid);
				}
				else
				{
					typeValue.sellNameList.erase(itemListIt);
				}

				typeValue.sell.erase(tradeid);
			}
		}
		mSellDelegate.erase(sellIt);
	}
	if (stallDummy) stallDummy->TriggerCheckUnStall();
}

void DeleteBuyDelegate(uint64_t tradeid, Player* player)
{
	if (!player) return;

	auto& mBuyDelegateInfo = player->GetBuyDelegateInfo();
	auto buyIt = std::find_if(mBuyDelegateInfo.begin(), mBuyDelegateInfo.end(), [&tradeid](const SP_BUY_DELEGATE& a) {
		return tradeid == a->id;
		});
	if (buyIt != mBuyDelegateInfo.end())
	{
		mBuyDelegateInfo.erase(buyIt);
	}
}
void TradeMgr::HandleDeleteBuyDelegate(uint64_t tradeid, Player* player)
{
	if (player)
	{
		DeleteBuyDelegate(tradeid, player);
	}

	auto buyIt = mBuyDelegate.find(tradeid);
	if (buyIt == mBuyDelegate.end())
	{
		LOG_ERROR("[%s:%d] tradeid:%" PRIu64 " not exist.", FUNC_LINE, tradeid);
	}
	else
	{
		// typeKey
		const auto& typeKey = buyIt->second.typeKey;
		const auto& delegateInfo = buyIt->second.delegateInfo;
		const auto& nameKey = buyIt->second.nameKey;
		std::string itemKeyName(nameKey.keyName);
		// all
		TradeItemTypeKeyPtr allKey;
		GetTradeItemTypeKeyPtr(0, 0, allKey);
		// type的所有
		TradeItemTypeKeyPtr typeAllKey;
		GetTradeItemTypeKeyPtr(typeKey->type, 0, typeAllKey);
		std::list<TradeItemTypeKeyPtr> l;
		l.push_back(typeKey);
		l.push_back(allKey);
		l.push_back(typeAllKey);
		auto it = l.begin();
		for (; it != l.end(); ++it)
		{
			auto itemTypeIt = mItemTypeDelegate.find(*it);
			if (itemTypeIt == mItemTypeDelegate.end())
			{
				LOG_ERROR("[%s:%d] type:%u, subType:%u not exist.", FUNC_LINE, (*it)->type, (*it)->subType);
			}
			else
			{
				auto& typeValue = itemTypeIt->second;
				auto buyKeyNameIt = typeValue.buyKeyNameMap.find(itemKeyName);
				if (buyKeyNameIt == typeValue.buyKeyNameMap.end())
				{
					LOG_ERROR("[%s:%d] itemKeyName:%s not exist.", FUNC_LINE, itemKeyName.c_str());
				}
				else
				{
					auto& itemList = buyKeyNameIt->second;
					auto itemListIt = std::find_if(itemList.begin(), itemList.end(), [=](const SP_BUY_DELEGATE& a) {
						return a->id == tradeid;
					});
					if (itemListIt == itemList.end())
					{
						LOG_ERROR("[%s:%d] itemKeyName:%s, tradeid:%" PRIu64 " not exist.", FUNC_LINE, itemKeyName.c_str(), tradeid);
					}
					else
					{
						itemList.erase(itemListIt);
					}
				}
				
				auto itemListIt = std::find_if(typeValue.buyNameList.begin(), typeValue.buyNameList.end(), [=](const TradeItemNameValue<SP_BUY_DELEGATE>& a) {
					return a.delegateInfo->id == tradeid;
				});
				if (itemListIt == typeValue.buyNameList.end())
				{
					LOG_ERROR("[%s:%d] itemKeyName:%s, tradeid:%" PRIu64 " not exist.", FUNC_LINE, itemKeyName.c_str(), tradeid);
				}
				else
				{
					typeValue.buyNameList.erase(itemListIt);
				}

				typeValue.buy.erase(tradeid);
			}
		}
		mBuyDelegate.erase(buyIt);
	}
}

void TradeMgr::HandleAddRecords(const TRADE_RECORD& trade_record)
{
	auto tr = std::make_shared<TRADE_RECORD>(trade_record);
	mTradeRecord[trade_record.logTradeData.tradeId] = tr;

	auto buyPlayer = MapRoleMgr::GetInstance()->FindPlayer(trade_record.logTradeData.buyerGuid);
	auto sellPlayer = MapRoleMgr::GetInstance()->FindPlayer(trade_record.logTradeData.sellerGuid);
	// 不会加到摆摊假人上,因为请求时会重新拉取
	if (buyPlayer)
	{
		auto& buyRecords = buyPlayer->GetTradeBuyRecords();
		buyRecords[trade_record.logTradeData.tradeId] = tr;
	}
	if (sellPlayer)
	{
		auto& sellRecords = sellPlayer->GetTradeSellRecords();
		sellRecords[trade_record.logTradeData.tradeId] = tr;
	}
}

void DeleteBuyRecords(uint64_t tradeid, Player* player)
{
	if (!player) return;

	auto& mBuyRecords = player->GetTradeBuyRecords();
	auto buyIt = mBuyRecords.find(tradeid);
	if (buyIt == mBuyRecords.end()) return;

	mBuyRecords.erase(buyIt);
}
void DeleteSellRecords(uint64_t tradeid, Player* player)
{
	if (!player) return;

	auto& mSellRecords = player->GetTradeSellRecords();
	auto sellIt = mSellRecords.find(tradeid);
	if (sellIt == mSellRecords.end()) return;

	mSellRecords.erase(sellIt);
}
void TradeMgr::HandleDeleteRecords(uint64_t tradeId)
{
	auto iter = mTradeRecord.find(tradeId);
	if (iter == mTradeRecord.end() || !iter->second) return;

	auto buyPlayer = MapRoleMgr::GetInstance()->FindPlayer(iter->second->logTradeData.buyerGuid);
	auto sellPlayer = MapRoleMgr::GetInstance()->FindPlayer(iter->second->logTradeData.sellerGuid);
	StallDummy* buyStallDummy = nullptr, *sellStallDummy = nullptr;
	if (buyPlayer)
	{
		DeleteBuyRecords(tradeId, buyPlayer);
		buyStallDummy = buyPlayer->GetStallDummy();
	}
	if (sellPlayer)
	{
		DeleteSellRecords(tradeId, sellPlayer);
		sellStallDummy = sellPlayer->GetStallDummy();
	}
	if (!buyStallDummy) buyStallDummy = MapRoleMgr::GetInstance()->FindStallDummy(iter->second->logTradeData.buyerGuid, 0);
	if (!sellStallDummy) sellStallDummy = MapRoleMgr::GetInstance()->FindStallDummy(iter->second->logTradeData.sellerGuid, 0);
	// 及时清除缓存
	DeleteBuyRecords(tradeId, buyStallDummy);
	DeleteSellRecords(tradeId, sellStallDummy);

	mTradeRecord.erase(iter);
}
///////////////////other///////////////////////

bool TradeMgr::GenerateItemTypeInfo(uint16_t itemId, TradeItemTypeKeyPtr& typeKey, std::string& keyName, std::string& cfgName)
{
	if (!::GetItemProp(itemId, ITEM_PROP_TYPE))
	{
		LOG_ERROR("[%s:%d] 信息异常1. itemId:%u", FUNC_LINE, itemId);
		return false;
	}
	uint32_t type = luabind::object_cast<int32_t>(LuaRet);
	if (!::GetItemProp(itemId, ITEM_PROP_SUBTYPE))
	{
		LOG_ERROR("[%s:%d] 信息异常2. itemId:%u", FUNC_LINE, itemId);
		return false;
	}
	uint32_t subType = luabind::object_cast<int32_t>(LuaRet);
	if (!::GetItemProp(itemId, ITEM_PROP_KEYNAME))
	{
		LOG_ERROR("[%s:%d] 信息异常3. itemId:%u", FUNC_LINE, itemId);
		return false;
	}
	keyName = luabind::object_cast<std::string>(LuaRet);
	if (!::GetItemProp(itemId, ITEM_PROP_NAME))
	{
		LOG_ERROR("[%s:%d] 信息异常4. itemId:%u", FUNC_LINE, itemId);
		return false;
	}
	cfgName = luabind::object_cast<std::string>(LuaRet);

	return GetTradeItemTypeKeyPtr(type, subType, typeKey);
}

bool TradeMgr::GetTradeItemTypeKeyPtr(uint32_t type, uint32_t subType, TradeItemTypeKeyPtr& typeKey)
{
	// 检测type 和subtype  return false;
	auto it = std::find_if(mTradeItemTypeKeyPtrList.begin(), mTradeItemTypeKeyPtrList.end(), [=](const TradeItemTypeKeyPtr& key) {
		return key->type == type && key->subType == subType;
	});
	if (it != mTradeItemTypeKeyPtrList.end())
	{
		typeKey = *it;
	}
	else
	{
		typeKey = std::make_shared<TradeItemTypeKey>(type, subType);
		mTradeItemTypeKeyPtrList.push_back(typeKey);
	}
	return true;
	/*
	auto it = mTradeItemTypeKeyPtrList.begin();
	for (; it != mTradeItemTypeKeyPtrList.end(); ++it)
	{
		if ((*it)->type == type && (*it)->subType == subType)
		{
			typeKey = *it;
			return true;
		}
	}
	if (!typeKey)
	{
		typeKey = std::make_shared<TradeItemTypeKey>(type, subType);
		mTradeItemTypeKeyPtrList.push_back(typeKey);
	}
	return true;
	*/
}

TradeItemTypeValue& TradeMgr::GetTradeItemTypeValue(const TradeItemTypeKeyPtr& typeKey)
{
	auto iter = mItemTypeDelegate.find(typeKey);
	if (iter == mItemTypeDelegate.end())
	{
		mItemTypeDelegate.insert(std::make_pair(typeKey, TradeItemTypeValue()));
		return mItemTypeDelegate[typeKey];
	}
	return iter->second;
}

void TradeMgr::CheckTypeKey(uint32_t type, uint32_t subType, TradeItemTypeKey& tk)
{
	if (TYPE_KEY_ALL == type)
	{
		tk.type = TYPE_KEY_ALL;
		tk.subType = SUB_TYPE_KEY_ALL;
	}
	else if (SUB_TYPE_KEY_ALL == subType)
	{
		tk.type = type;
		tk.subType = SUB_TYPE_KEY_ALL;
	}
	else
	{
		tk.type = type;
		tk.subType = subType;
	}
}
