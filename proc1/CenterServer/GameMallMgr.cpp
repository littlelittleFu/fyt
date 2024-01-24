#include"stdafx.h"
#include"GameMallMgr.h"
#include"CNetManager.h"
#include"UserMgr.h"
#include"User.h"
IMPL_SINGLETON(GameMallMgr)

void GameMallMgr::Init()
{
	MALL_ITEM_INFO_BASE item;
	auto& mallDatas = sMallConfig.GetData();
	for (auto& data : mallDatas) {
		if (data == nullptr)continue;
		if (data->NotSell) continue;
		if (data->LimitsType != mall_limit_type_all)continue;
		auto itemCfg = sItemConfig.GetByKeyName(data->KeyName);
		if (nullptr == itemCfg) continue;
		
		item.item_idx = data->ID;
		item.num = 0;
		mMallMgrItemLimitAllMap[item.item_idx] = item;
	}

	auto global = sGlobalConfig.GetData();
	if (global && global->MallDayUpdateTime)
	{
		IScheduledHelper::GetInstance()->AddScheduled(ESTT_DAY, "商城日更表", std::vector<std::string>{std::string(global->MallDayUpdateTime)}, "", GameMallUpDateDay);
	}
	if (global && global->MallWeekUpdateTime)
	{
		IScheduledHelper::GetInstance()->AddScheduled(ESTT_WEEK, "商城周更表", std::vector<std::string>{std::string(global->MallWeekUpdateTime)}, "", GameMallUpDateWeek);
	}
	if (global && global->MallMonthUpdateTime)
	{
		IScheduledHelper::GetInstance()->AddScheduled(ESTT_MONTH, "商城月更表", std::vector<std::string>{std::string(global->MallMonthUpdateTime)}, "", GameMallUpDateMonth);
	}
}

void GameMallMgr::InitMallAllMapToDB()
{
	auto& allmap = GetMallMgrItemLimitAllMap();
	ProtoMS_MallLimitInfoUpdate data;
	data.limit_type = mall_limit_type_all;
	data.opt_type = ProtoMS_MallLimitInfoUpdate::opt_type_add;
	for (auto& i : allmap)
	{
		data.data[data.num].num = i.second.num;
		data.data[data.num].item_idx = i.first;
		++data.num;
		if (data.num >= 100)
		{
			SendDataBySessionType(SESSION_TYPE_CS2DB, data);
			data.num = 0;
		}
	}
	if (data.num > 0 && data.num < 100)
	{
		SendDataBySessionType(SESSION_TYPE_CS2DB, data);
	}
}

void GameMallMgr::UpdateMallInfoToDB(ProtoMS_MallLimitInfoUpdate& data)
{

	ProtoMS_MallLimitInfoUpdate addAck;
	ProtoMS_MallLimitInfoUpdate updateAck;
	//MALL_ITEM_INFO_BASE 
	if (data.limit_type == mall_limit_type_all)
	{
		addAck.limit_type = mall_limit_type_all;
		addAck.opt_type = ProtoMS_MallLimitInfoUpdate::opt_type_add;

		updateAck.limit_type = mall_limit_type_all;
		updateAck.opt_type = ProtoMS_MallLimitInfoUpdate::opt_type_update;

		for (int i = 0; i < data.num; ++i)
		{
			auto mallAllMapIter = mMallMgrItemLimitAllMap.find(data.data[i].item_idx);
			if (mallAllMapIter == mMallMgrItemLimitAllMap.end())
			{
				// addType
				addAck.data[addAck.num] = data.data[i];
				++addAck.num;
			}
			else {
				if (mallAllMapIter->second.num != data.data[i].num)
				{
					// updateType
					updateAck.data[updateAck.num] = data.data[i];
					++updateAck.num;
				}
			}	
			mMallMgrItemLimitAllMap[data.data[i].item_idx] = data.data[i];
		}
	}
	else if (data.limit_type == mall_limit_type_single)
	{
		addAck.limit_type = mall_limit_type_single;
		addAck.opt_type = ProtoMS_MallLimitInfoUpdate::opt_type_add;

		updateAck.limit_type = mall_limit_type_single;
		updateAck.opt_type = ProtoMS_MallLimitInfoUpdate::opt_type_update;

		for (int i = 0; i < data.num; ++i)
		{
			auto mallSingleMapIter = mMallMgrItemLimitSingleMap.find(data.data[i].playerguid);
			if (mallSingleMapIter == mMallMgrItemLimitSingleMap.end())
			{
				// addType
				addAck.data[addAck.num] = data.data[i];
				++addAck.num;
			}
			else {
				// addType
				auto mallSingleInfoIter = mallSingleMapIter->second.find(data.data[i].item_idx);
				if (mallSingleInfoIter == mallSingleMapIter->second.end())
				{

					addAck.data[addAck.num] = data.data[i];
					++addAck.num;
				}
				else
				{
					if (mallSingleInfoIter->second.num != data.data[i].num)
					{
						// updateType
						updateAck.data[updateAck.num] = data.data[i];
						++updateAck.num;
					}
				}
			}
			mMallMgrItemLimitSingleMap[data.data[i].playerguid][data.data[i].item_idx] = data.data[i];
		}
	}
	if (addAck.num)
	{
		SendDataBySessionType(SESSION_TYPE_CS2DB, addAck);
	}
	if (updateAck.num)
	{
		SendDataBySessionType(SESSION_TYPE_CS2DB, updateAck);
	}
}

void GameMallMgr::GetMallLimitInfoAck(ProtoMS_MallLimitInfoUpdate& data)
{
	if (data.limit_type == mall_limit_type_all)
	{
		for (int i = 0; i < data.num; ++i)
		{
			if (mMallMgrItemLimitAllMap.find(data.data[i].item_idx) == mMallMgrItemLimitAllMap.end())continue;
			mMallMgrItemLimitAllMap[data.data[i].item_idx] = data.data[i];
		}
	}
	else if (data.limit_type == mall_limit_type_single)
	{
		for (int i = 0; i < data.num; ++i)
		{
			mMallMgrItemLimitSingleMap[data.data[i].playerguid][data.data[i].item_idx] = data.data[i];
		}
	}
}

void GameMallMgr::GameMallUpDateDay(Scheduled* scheduled)
{
	GameMallUpdateFunc(mall_cfg_limits_time_type_day);
}
void GameMallMgr::GameMallUpDateWeek(Scheduled* scheduled)
{
	GameMallUpdateFunc(mall_cfg_limits_time_type_week);
}
void GameMallMgr::GameMallUpDateMonth(Scheduled* scheduled)
{
	GameMallUpdateFunc(mall_cfg_limits_time_type_month);
}

void GameMallMgr::GameMallUpdateFunc(uint8_t type)
{
	ProtoMS_MallLimitInfoUpdate allData;
	allData.opt_type = ProtoMS_MallLimitInfoUpdate::opt_type_update;
	allData.limit_type = mall_limit_type_all;
	ProtoCS_MallListUpdate allData2MS;
	allData2MS.limit_type = mall_limit_type_all;

	ProtoMS_MallLimitInfoUpdate singleData;
	singleData.opt_type = ProtoMS_MallLimitInfoUpdate::opt_type_update;
	singleData.limit_type = mall_limit_type_single;
	ProtoCS_MallListUpdate singleData2MS;
	singleData2MS.limit_type = mall_limit_type_single;

	// 全局
	auto& allMap = GameMallMgr::GetInstance()->GetMallMgrItemLimitAllMap();
	auto& mallItemCfg = sMallConfig.GetIDMappings();
	for (auto& data : allMap)
	{
		if (mallItemCfg[data.first] && mallItemCfg[data.first]->LimitsTime == type)
		{
			if (!data.second.num)continue;
			data.second.num = 0;
			allData.data[allData.num] = data.second;
			++allData.num;
			allData2MS.data[allData2MS.num] = data.second;
			++allData2MS.num;
			if (allData.num >= 100)
			{
				SendDataBySessionType(SESSION_TYPE_CS2DB, allData);
				SendDataBySessionType(SESSION_TYPE_CS2MS, allData2MS);

				allData.num = 0;
				allData2MS.num = 0;
			}
		}
	}
	if(allData.num<100 && allData.num >0)
	{
		SendDataBySessionType(SESSION_TYPE_CS2DB, allData);
		SendDataBySessionType(SESSION_TYPE_CS2MS, allData2MS);

	}
	// 个人
	auto& singleMap = GameMallMgr::GetInstance()->GetMallItemLimitSingleMap();
	for (auto& singleDataMap : singleMap)
	{
		for (auto& data : singleDataMap.second)
		{
			if (mallItemCfg[data.first] && mallItemCfg[data.first]->LimitsTime == type)
			{
				if (!data.second.num)continue;
				data.second.num = 0;
			    singleData.data[singleData.num] = data.second;
				++singleData.num;
				singleData2MS.data[singleData2MS.num] = data.second;
				++singleData2MS.num;
				if (singleData.num >= 100)
				{
					SendDataBySessionType(SESSION_TYPE_CS2DB, singleData);
					SendDataBySessionType(SESSION_TYPE_CS2MS, singleData2MS);

					singleData.num = 0;
					singleData2MS.num = 0;
				}
			}
		}
	}
	if (singleData.num < 100 && singleData.num >0)
	{
		SendDataBySessionType(SESSION_TYPE_CS2DB, singleData);
		SendDataBySessionType(SESSION_TYPE_CS2MS, singleData2MS);
	}
}
