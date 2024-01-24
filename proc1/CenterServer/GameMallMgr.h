#pragma once
#include<map>
#include"DataInfo.hpp"
#include"ProtoMS.h"
#include "ProtoCS.h"
#include "ScheduledHelper.h"
enum mall_cfg_limits_time_type
{
	mall_cfg_limits_time_type_day = 1,
	mall_cfg_limits_time_type_week = 2,
	mall_cfg_limits_time_type_month = 3,
	mall_cfg_limits_time_type_forever = 4,
};


class GameMallMgr
{
	DECL_SINGLETON(GameMallMgr);
	// key为mall item id
	using MALL_MGR_ITEM_LIMIT_ALL_MAP = std::map<uint32_t, MALL_ITEM_INFO_BASE>;
	using MALL_MGR_ITEM_LIMIT_SINGLE_DATA = std::map<uint32_t, MALL_ITEM_INFO_BASE>;
	using MALL_MGR_ITEM_LIMIT_SINGLE_MAP = std::map<uint64_t, MALL_MGR_ITEM_LIMIT_SINGLE_DATA>;

public:
	void Init();
	void InitMallAllMapToDB();
	void UpdateMallInfoToDB(ProtoMS_MallLimitInfoUpdate& data);
	void GetMallLimitInfoAck(ProtoMS_MallLimitInfoUpdate& data);
	MALL_MGR_ITEM_LIMIT_ALL_MAP& GetMallMgrItemLimitAllMap() { return mMallMgrItemLimitAllMap; }
	MALL_MGR_ITEM_LIMIT_SINGLE_MAP& GetMallItemLimitSingleMap() { return mMallMgrItemLimitSingleMap; }

	static void GameMallUpDateDay(Scheduled* scheduled);
	static void GameMallUpDateWeek(Scheduled* scheduled);
	static void GameMallUpDateMonth(Scheduled* scheduled);
	static void GameMallUpdateFunc(uint8_t type);
protected:

	MALL_MGR_ITEM_LIMIT_ALL_MAP mMallMgrItemLimitAllMap; // 全局限购
	MALL_MGR_ITEM_LIMIT_SINGLE_MAP mMallMgrItemLimitSingleMap; // 个人限购

};