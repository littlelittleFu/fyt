#include<stdafx.h>
#include<CustList.h>

#define CYCLE_SORT_TIME 300000
#define MAX_CUST_LIST_DATA_NUM  200
#define MAX_CUST_LIST_DATA_NUM_CAN_GET 100

IMPL_SINGLETON(CustListMgr)


void CustListMgr::Init()
{
	TimerData timer;
	timer.interval = CYCLE_SORT_TIME;
	timer.loop = true;
	timer.callBack = [this](const TimerData&) {
		Sort();
		SyncDataToDB();
	};

	ITimeHelper::GetInstance()->AddTimer(timer);
}

void CustListMgr::Sort()
{
	for (int i = CustType_1; i < CustType_Max; ++i) {
		if (!mflag[i])continue;
		mCustVec[i].clear();
		mCustVec[i].assign(mUnSortCustList[i].begin(), mUnSortCustList[i].end());
		sort(mCustVec[i].begin(), mCustVec[i].end(), [](const std::pair<uint64_t, CUST_DATA_SP>& l, const std::pair<uint64_t, CUST_DATA_SP>& r) {
			if (l.second->value == r.second->value)
				return l.second->stamp < r.second->stamp;
			else 
				return l.second->value < r.second->value;
			});

		if (mCustVec[i].size() > MAX_CUST_LIST_DATA_NUM) {
			mCustVec[i].erase(mCustVec[i].begin() + MAX_CUST_LIST_DATA_NUM, mCustVec->end());
		}

		mUnSortCustList[i].clear();
		for (auto& idx : mCustVec[i]) {
			mUnSortCustList[i].emplace(idx);
		}
	}
}

void CustListMgr::InsertDataByType(uint64_t guid, int type, int64_t value, const char * desc)
{
	CUST_DATA_SP sp = std::make_shared<CUST_LIST_INFO>(guid, type, value, (uint64_t)MS2S(ITimeHelper::GetInstance()->GetTimeStamp()), desc);
	mUnSortCustList[type][guid] = sp;
	mflag[type] = 1;
}

void CustListMgr::GetInfoFromDB(uint16_t num, const CUST_LIST_INFO* info)
{
	for (int i = 0; i < num; ++i) {
		mCustVec[info[i].type].push_back(std::make_pair(info[i].guid, std::make_shared<CUST_LIST_INFO>(info[i])));
		mUnSortCustList[info[i].type][info[i].guid] = std::make_shared<CUST_LIST_INFO>(info[i]);
	}
}

void CustListMgr::SyncDataToDB()
{
	for (int i = CustType_1; i < CustType_Max; ++i) {
		if (!mflag[i])continue;
		mflag[i] = 0;
		MSG_BUFFER_DATA(ProtoMS_SyncCustList, data);
		data.type = i;
		for (auto& info : mCustVec[i]) {
			data.data[data.num].guid = info.second->guid;
			data.data[data.num].type = info.second->type;
			data.data[data.num].value = info.second->value;
			data.data[data.num].stamp = info.second->stamp;
			strcpy_s(data.data[data.num].desc, _countof(data.data[data.num].desc), info.second->desc);
			data.data[data.num++].ranking = i * 1000 + data.num + 1;
			if (data.num == MAX_CUST_LIST_DATA_NUM_CAN_GET)break;
		}
		SendDataBySessionType(SESSION_TYPE_MS2CS, data);
	}
}

void CustListMgr::GetCustListByType(int type, CLuaObject& table)
{
	if (mCustVec[type].empty())return;
	int idx = 1;

	for (auto& i : mCustVec[type]) {
		auto data = NewLuaObj();
		data[1] = std::to_string(i.second->guid);
		data[2] = std::to_string(i.second->value);
		data[3] = i.second->desc;
		data[4] = idx;
		table[idx++] = data;
		if (idx > MAX_CUST_LIST_DATA_NUM_CAN_GET)break;
	}
	return;
}
