#pragma once
#include "DataInfo.hpp"
#include "ProtoMS.h"
#include "ProtoCS.h"
#include "ProtoGS.h"

#include <map>

struct MALL_ITEM_DATA
{
	uint8_t			Page = 0;
	uint32_t        itemPurchasedNum = 0;
	MALL_ITEM_INFO	Item;
};


class GameMall
{
	DECL_SINGLETON(GameMall);
	// key为mall item id
	using MALL_ITEM_LIMIT_NON_MAP = std::unordered_map<uint32_t, MALL_ITEM_DATA>;
	using MALL_ITEM_LIMIT_ALL_MAP = std::unordered_map<uint32_t, MALL_ITEM_DATA>;
	using MALL_ITEM_LIMIT_SINGLE_DATA = std::unordered_map<uint32_t, MALL_ITEM_DATA>;
	using MALL_ITEM_LIMIT_SINGLE_MAP = std::map<uint64_t, MALL_ITEM_LIMIT_SINGLE_DATA>;

public:
	void Init();
	MALL_ITEM_LIMIT_NON_MAP& GetMallLimitNonMap() { return mMallItemLimitNonMap; };
	MALL_ITEM_LIMIT_ALL_MAP& GetMallLimitAllMap() { return  mMallItemLimitAllMap; };
	MALL_ITEM_LIMIT_SINGLE_MAP& GetMallLimitSinleMap() { return  mMallItemLimitSingleMap; };

	MALL_ITEM_DATA* GetMallItem(uint16_t itemIdx, uint64_t  playerguid);

	void GetMallInfoLimitFromCS(const ProtoMS_MallLimitInfoUpdate& data);
	void UpdateLimitNumWhenVipUp(uint64_t playerguid,uint16_t vip_level);
	void UpdateMallListWhenTimeRefresh(const ProtoCS_MallListUpdate& data);

	void GetMallSingleInfoFromCS(const ProtoCS_GetMallLimitInfoSingleAck& info);

	void DeleteMallLimitSingle(uint64_t playerguid);
	static int ValueTypeToPriceType(int valueType);
	static int PriceTypeToErrorCodeWhenCostNotEnough(int priceType);

	void SortAllMap();
	void SortSingleMap(const uint64_t playerguid);
protected:
	MALL_ITEM_LIMIT_NON_MAP mMallItemLimitNonMap;       // 不限购
	MALL_ITEM_LIMIT_ALL_MAP mMallItemLimitAllMap;       // 全局限购
	MALL_ITEM_LIMIT_SINGLE_MAP mMallItemLimitSingleMap; // 个人限购

};
