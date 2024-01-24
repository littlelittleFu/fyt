#include "stdafx.h"
#include "GameMall.h"
#include "mall_table.hpp"
#include "item_table.hpp"
#include "CNetManager.h"


IMPL_SINGLETON(GameMall)

void GameMall::Init()
{
	MALL_ITEM_DATA item;
	auto& mallDatas = sMallConfig.GetData();
	for (auto& data : mallDatas) {
		if (data == nullptr)continue;
		if (data->NotSell) continue;
		if (data->LimitsType == mall_limit_type_all)
		{
			auto itemCfg = sItemConfig.GetByKeyName(data->KeyName);
			if (nullptr == itemCfg) continue;

			item.Page = data->Page;
			item.Item.item_index = data->ID;
			item.Item.item_id = itemCfg->Id;
			item.Item.is_hot = data->Hot;
			item.Item.num = data->Number[0];
			item.Item.value_type = data->CostType;
			item.Item.price = data->Price;
			item.Item.discount = data->Discount[0];
			item.Item.limits_type = data->LimitsType;
			item.Item.limits_time = data->LimitsTime;
			mMallItemLimitAllMap[item.Item.item_index] = item;
		}
		else if (data->LimitsType == mall_limit_type_non)
		{
			auto itemCfg = sItemConfig.GetByKeyName(data->KeyName);
			if (nullptr == itemCfg) continue;

			item.Page = data->Page;
			item.Item.item_index = data->ID;
			item.Item.item_id = itemCfg->Id;
			item.Item.is_hot = data->Hot;
			item.Item.num = 0xffff;
			item.Item.value_type = data->CostType;
			item.Item.price = data->Price;
			item.Item.discount = data->Discount[0];
			mMallItemLimitNonMap[item.Item.item_index] = item;
		}
	}
}

MALL_ITEM_DATA* GameMall::GetMallItem(uint16_t itemIdx,uint64_t  playerguid)
{
	auto _it = mMallItemLimitNonMap.find(itemIdx);
	if (_it != mMallItemLimitNonMap.end()) {
		return &_it->second;
	}
	auto it = mMallItemLimitAllMap.find(itemIdx);
	if (it != mMallItemLimitAllMap.end()) {
		return &it->second;
	}
	auto iter = mMallItemLimitSingleMap.find(playerguid);
	if (iter != mMallItemLimitSingleMap.end())
	{
		auto _iter = iter->second.find(itemIdx);
			if (_iter != iter->second.end()) {
				return &_iter->second;
			}
	}

	return nullptr;
}

void GameMall::GetMallInfoLimitFromCS(const ProtoMS_MallLimitInfoUpdate& data)
{
	if (data.limit_type == mall_limit_type_all)
	{
		for (int i = 0; i < data.num; ++i)
		{
			if (mMallItemLimitAllMap.find(data.data[i].item_idx) == mMallItemLimitAllMap.end())continue;
			mMallItemLimitAllMap[data.data[i].item_idx].itemPurchasedNum = data.data[i].num;
			mMallItemLimitAllMap[data.data[i].item_idx].Item.num -= data.data[i].num;
		}
		SortAllMap();
	}
	else if (data.limit_type == mall_limit_type_single)
	{
		for (int i = 0; i < data.num; ++i)
		{
			auto player = MapRoleMgr::GetInstance()->FindPlayer(data.data[i].playerguid);
			if (player == nullptr)return;

			if (mMallItemLimitSingleMap.find(data.data[i].playerguid) == mMallItemLimitSingleMap.end())continue;
			if (mMallItemLimitSingleMap[data.data[i].playerguid].find(data.data[i].item_idx) 
				== mMallItemLimitSingleMap[data.data[i].playerguid].end())continue;
			mMallItemLimitSingleMap[data.data[i].playerguid][data.data[i].item_idx].itemPurchasedNum = data.data[i].num;
			mMallItemLimitSingleMap[data.data[i].playerguid][data.data[i].item_idx].Item.num -= data.data[i].num;
		}
	}
}

void GameMall::UpdateLimitNumWhenVipUp(uint64_t playerguid, uint16_t vip_level)
{
	auto player = MapRoleMgr::GetInstance()->FindPlayer(playerguid);
	if (!player)return;
	auto playerMallSingleLimitIter = mMallItemLimitSingleMap.find(playerguid);
	if (playerMallSingleLimitIter == mMallItemLimitSingleMap.end())return;

	ProtoGS_TradeMallListUpdate data2GS;
	data2GS.sessionid = player->GetClSessionID();

	ProtoMS_MallLimitInfoUpdate data2CS;
	data2CS.limit_type = mall_limit_type_single;

	auto mallCfgMap = sMallConfig.GetData();
	for (auto& data : mallCfgMap) {
		if (data == nullptr)continue;
		if (data->NotSell && data->NotSell > vip_level) continue;
		if (data->LimitsType == mall_limit_type_all || data->LimitsType == mall_limit_type_non)continue;
		auto itemCfg = sItemConfig.GetByKeyName(data->KeyName);
		if (nullptr == itemCfg) continue;

		// 找到最大的限购vip等级
		int maxVipLevel = 0;
		if (data->Number.find(vip_level) != data->Number.end())
		{
			maxVipLevel = vip_level;
		}
		else
		{
			for (auto& vipiter : data->Number)
			{
				if (vipiter.first < vip_level && vipiter.first>maxVipLevel)
				{
					maxVipLevel = vipiter.first;
				}
			}
		}
		// 找到最大的discount vip等级
		int maxDiscountLevel = 0;
		if (data->Discount.find(vip_level) != data->Discount.end())
		{
			maxDiscountLevel = vip_level;
		}
		else
		{
			for (auto& vipDiscountIter : data->Discount)
			{
				if (vipDiscountIter.first < vip_level && vipDiscountIter.first>maxDiscountLevel)
				{
					maxDiscountLevel = vipDiscountIter.first;
				}
			}
		}

		auto itemIter = playerMallSingleLimitIter->second.find(data->ID);
		if (itemIter != playerMallSingleLimitIter->second.end())
		{
			if (data->Number.find(maxVipLevel) != data->Number.end())
			{
				int finalnum = data->Number[maxVipLevel] - itemIter->second.itemPurchasedNum;
				itemIter->second.Item.num = finalnum > 0 ? finalnum : 0;
			}
			else
			{
				itemIter->second.Item.num = 0;
			}

			if (data->Discount.find(maxDiscountLevel) != data->Discount.end())
			{
				itemIter->second.Item.discount = data->Discount[maxDiscountLevel];
			}
			else
			{
				itemIter->second.Item.discount = itemIter->second.Item.price;
			}
			data2GS.item_list[data2GS.item_count] = itemIter->second.Item;
			++data2GS.item_count;
		}
		else
		{
			// 上架与vip挂钩 vip提升后会新增上架物品
			MALL_ITEM_DATA item;
			auto itemCfg = sItemConfig.GetByKeyName(data->KeyName);
			if (nullptr == itemCfg) continue;
			item.Page = data->Page;
			item.Item.item_index = data->ID;
			item.Item.item_id = itemCfg->Id;
			item.Item.is_hot = data->Hot;
			if (data->Number.find(vip_level) != data->Number.end())
			{
				item.Item.num = data->Number[maxVipLevel];
			}
			else
			{
				item.Item.num = 0;
			}
			item.Item.value_type = data->CostType;
			item.Item.price = data->Price;
			if (data->Discount.find(vip_level) != data->Discount.end())
			{
				item.Item.discount = data->Discount[maxDiscountLevel];
			}
			else
			{
				item.Item.discount = data->Price;
			}
			item.Item.limits_type = data->LimitsType;
			item.Item.limits_time = data->LimitsTime;

			mMallItemLimitSingleMap[playerguid][item.Item.item_index] = item;
			data2CS.data[data2CS.num].item_idx = item.Item.item_index;
			data2CS.data[data2CS.num].playerguid = playerguid;
			data2CS.data[data2CS.num].num = 0;
			++data2CS.num;
			if (data2CS.num == 100)
			{
				SendDataBySessionType(SESSION_TYPE_MS2CS, data2CS);
				data2CS.num = 0;
			}
			data2GS.item_list[data2GS.item_count] = item.Item;
			++data2GS.item_count;
		}
	}
	if (data2CS.num > 0 && data2CS.num < 100)
	{
		SendDataBySessionType(SESSION_TYPE_MS2CS, data2CS);
	}
	SendDataBySessionID(player->GetGsSessionID(), data2GS);
}

void GameMall::UpdateMallListWhenTimeRefresh(const ProtoCS_MallListUpdate& data)
{
	ProtoGS_TradeMallListUpdate ack;
	switch (data.limit_type)
	{
	case mall_limit_type_all:
	{
		for (int i = 0; i < data.num; ++i)
		{
			if (mMallItemLimitAllMap.find(data.data[i].item_idx) == mMallItemLimitAllMap.end())continue;
			mMallItemLimitAllMap[data.data[i].item_idx].Item.num += mMallItemLimitAllMap[data.data[i].item_idx].itemPurchasedNum;
			mMallItemLimitAllMap[data.data[i].item_idx].itemPurchasedNum = 0;

			ack.item_list[ack.item_count] = mMallItemLimitAllMap[data.data[i].item_idx].Item;
			++ack.item_count;
		}
		break;
	}
	case mall_limit_type_single:
	{
		for (int i = 0; i < data.num; ++i)
		{
			if (mMallItemLimitSingleMap.find(data.data[i].playerguid) == mMallItemLimitSingleMap.end())continue;
			if (mMallItemLimitSingleMap[data.data[i].playerguid].find(data.data[i].item_idx) == mMallItemLimitSingleMap[data.data[i].playerguid].end())continue;
			mMallItemLimitSingleMap[data.data[i].playerguid][data.data[i].item_idx].Item.num +=
				mMallItemLimitSingleMap[data.data[i].playerguid][data.data[i].item_idx].itemPurchasedNum;
			mMallItemLimitSingleMap[data.data[i].playerguid][data.data[i].item_idx].itemPurchasedNum = 0;

			ack.item_list[ack.item_count] = mMallItemLimitSingleMap[data.data[i].playerguid][data.data[i].item_idx].Item;
			++ack.item_count;
		}
		break;
	}
	default:
		break;
	}

	auto& playermap =  MapRoleMgr::GetInstance()->GetPlayerMap();
	for (auto& i : playermap)
	{
		if (!i.second)continue;
		ack.sessionid = i.second->GetClSessionID();
		SendDataBySessionID(i.second->GetGsSessionID(), ack);
	}

}

void GameMall::GetMallSingleInfoFromCS(const ProtoCS_GetMallLimitInfoSingleAck& info)
{
	auto player = MapRoleMgr::GetInstance()->FindPlayer(info.playerguid);
	if (!player)return;

	if (info.isFirstPkg)
	{
		auto playerLevel = player->GetRoleBriefInfo().vipLevel;
		// 玩家登录第一次接收csmall数据 拉取个人限购的表格
		MALL_ITEM_DATA item;
		auto& mallDatas = sMallConfig.GetData();

		for (auto& data : mallDatas)
		{
			if (data == nullptr)continue;
			// 找到最大的限购vip等级
			int maxVipLevel = 0;
			if (data->Number.find(playerLevel) != data->Number.end())
			{
				maxVipLevel = playerLevel;
			}
			else
			{
				for (auto& vipiter : data->Number)
				{
					if (vipiter.first < playerLevel && vipiter.first>maxVipLevel)
					{
						maxVipLevel = vipiter.first;
					}
				}
			}
			// 找到最大的discount vip等级
			int maxDiscountLevel = 0;
			if (data->Discount.find(playerLevel) != data->Discount.end())
			{
				maxDiscountLevel = playerLevel;
			}
			else
			{
				for (auto& vipDiscountIter : data->Discount)
				{
					if (vipDiscountIter.first < playerLevel && vipDiscountIter.first>maxDiscountLevel)
					{
						maxDiscountLevel = vipDiscountIter.first;
					}
				}
			}

			if (data->NotSell && data->NotSell > playerLevel) continue;
			if (data->LimitsType == mall_limit_type_all || data->LimitsType == mall_limit_type_non)continue;
			auto itemCfg = sItemConfig.GetByKeyName(data->KeyName);
			if (nullptr == itemCfg) continue;
			item.Page = data->Page;
			item.Item.item_index = data->ID;
			item.Item.item_id = itemCfg->Id;
			item.Item.is_hot = data->Hot;
			if (data->Number.find(maxVipLevel) != data->Number.end())
			{
				item.Item.num = data->Number[maxVipLevel];
			}
			else
			{
				item.Item.num = 0;
			}
			item.Item.value_type = data->CostType;
			item.Item.price = data->Price;
			if (data->Discount.find(maxDiscountLevel) != data->Discount.end())
			{
				item.Item.discount = data->Discount[maxDiscountLevel];
			}
			else
			{
				item.Item.discount = data->Price;
			}
			item.Item.limits_type = data->LimitsType;
			item.Item.limits_time = data->LimitsTime;

			mMallItemLimitSingleMap[info.playerguid][item.Item.item_index] = item;
		}
	}

	for (int i = 0; i < info.num; ++i)
	{
		if (mMallItemLimitSingleMap.find(info.playerguid) == mMallItemLimitSingleMap.end())continue;
		if (mMallItemLimitSingleMap[info.playerguid].find(info.data[i].item_idx) ==
			mMallItemLimitSingleMap[info.playerguid].end())continue;
		mMallItemLimitSingleMap[info.playerguid][info.data[i].item_idx].itemPurchasedNum = info.data[i].num;
		mMallItemLimitSingleMap[info.playerguid][info.data[i].item_idx].Item.num -= info.data[i].num;
	}


	if (info.isFinalPkg)
	{
		// 个人限购的排序
		SortSingleMap(info.playerguid);
		// 尾包已经拉取所有CS数据 将该名玩家的mallSingleMap数据全部同步到CS
		ProtoMS_MallLimitInfoUpdate ack;
		ack.limit_type = mall_limit_type_single;
		if (mMallItemLimitSingleMap.find(info.playerguid) == mMallItemLimitSingleMap.end())return;
		for (auto& i : mMallItemLimitSingleMap[info.playerguid])
		{
			ack.data[ack.num].playerguid = info.playerguid;
			ack.data[ack.num].item_idx = i.first;
			ack.data[ack.num].num = i.second.itemPurchasedNum;
			++ack.num;
			if (ack.num >= 100)
			{
				SendDataBySessionType(SESSION_TYPE_MS2CS, ack);
				ack.num = 0;
			}
		}
		if (ack.num > 0 && ack.num < 100)
		{
			SendDataBySessionType(SESSION_TYPE_MS2CS, ack);
		}
	}
}

void GameMall::DeleteMallLimitSingle(uint64_t playerguid)
{
	auto iter = mMallItemLimitSingleMap.find(playerguid);
	if (iter != mMallItemLimitSingleMap.end())
	{
		mMallItemLimitSingleMap.erase(iter);
	}
}

int GameMall::ValueTypeToPriceType(int valueType)
{
	switch (valueType)
	{
		case 0: return role_ingot;
		case 1: return role_bind_ingot;
		case 2: return role_integral;
		case 3: return role_gold;
		case 4: return role_bind_gold;
		default: break;
	}
	return role_ingot;
}

int GameMall:: PriceTypeToErrorCodeWhenCostNotEnough(int priceType)
{
	switch (priceType)
	{
	case role_ingot: return ERR_INGOT_NOT_ENOUGH;
	case role_bind_ingot: return ERR_BIND_INGOT_NOT_ENOUGH;
	case role_integral: return ERR_INTEGRAL_NOT_ENOUGH;
	case role_gold: return ERR_GOLD_NOT_ENOUGH;
	case role_bind_gold: return ERR_BIND_GOLD_NOT_ENOUGH;
	default: break;
	}
	return ERR_INGOT_NOT_ENOUGH;
}

void GameMall::SortAllMap()
{
	std::vector<MALL_ITEM_DATA>vec;
	for (auto& i : mMallItemLimitAllMap)
	{
		vec.push_back(i.second);
	}
	auto& mallcfg = sMallConfig.GetIDMappings();
	sort(vec.begin(), vec.end(), [&mallcfg](const MALL_ITEM_DATA&a, const MALL_ITEM_DATA&b) {
		if (mallcfg.find(a.Item.item_index) == mallcfg.end() || mallcfg.find(a.Item.item_index)->second == nullptr) return true;
		if (mallcfg.find(b.Item.item_index) == mallcfg.end() || mallcfg.find(b.Item.item_index)->second == nullptr) return true;

		if (mallcfg[a.Item.item_index]->Chart < mallcfg[b.Item.item_index]->Chart)
		{
			return true;
		}
		else if (mallcfg[a.Item.item_index]->Chart == mallcfg[b.Item.item_index]->Chart)
		{
			if (a.Item.item_index < b.Item.item_index)
				return true;
		}
		return false;
	});
	mMallItemLimitAllMap.clear();
	for (auto& i : vec)
	{
		mMallItemLimitAllMap.emplace(make_pair(i.Item.item_index, i));
	}
}

void GameMall::SortSingleMap(const uint64_t playerguid)
{
	if (mMallItemLimitSingleMap.find(playerguid) == mMallItemLimitSingleMap.end())return;
	std::vector<MALL_ITEM_DATA>vec;
	for (auto& i : mMallItemLimitSingleMap[playerguid])
	{
		vec.push_back(i.second);
	}
	auto& mallcfg = sMallConfig.GetIDMappings();
	sort(vec.begin(), vec.end(), [&mallcfg](const MALL_ITEM_DATA& a, const MALL_ITEM_DATA& b) {
		if (mallcfg.find(a.Item.item_index) == mallcfg.end() || mallcfg.find(a.Item.item_index)->second == nullptr) return true;
		if (mallcfg.find(b.Item.item_index) == mallcfg.end() || mallcfg.find(b.Item.item_index)->second == nullptr) return true;
		if (mallcfg[a.Item.item_index]->Chart < mallcfg[b.Item.item_index]->Chart)
		{
			return true;
		}
		else if (mallcfg[a.Item.item_index]->Chart == mallcfg[b.Item.item_index]->Chart)
		{
			if (a.Item.item_index < b.Item.item_index)
				return true;
		}
		return false;
		});
	mMallItemLimitSingleMap[playerguid].clear();
	for (auto& i : vec)
	{
		mMallItemLimitSingleMap[playerguid].emplace(make_pair(i.Item.item_index, i));
	}
}
