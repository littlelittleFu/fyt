#include "stdafx.h"
#include "CustListMgr.h"
#include "ProtoMS.h"

IMPL_SINGLETON(CustListInfoMgr)

void CustListInfoMgr::GetCustInfoFromDB(uint16_t num, const CUST_LIST_INFO* info)
{
	for (int i = 0; i < num; ++i) {
		mCustList[info[i].type][info[i].ranking] = std::make_shared<CUST_LIST_INFO>(info[i]);
	}
}

void CustListInfoMgr::SyncCustInfoFromMS(int type, uint16_t num, CUST_LIST_INFO* info)
{
	auto addData = make_shared<ProtoMS_SyncCustList>(ProtoMS_SyncCustList::OptType::optType_add);
	auto updateData = make_shared<ProtoMS_SyncCustList>(ProtoMS_SyncCustList::OptType::optType_update);

	for (int i = 0; i < num; ++i) {
		auto iter = mCustList[type].find(info[i].ranking);
		if (iter == mCustList[type].end()) {
			mCustList[type][info[i].ranking] = std::make_shared<CUST_LIST_INFO>(info[i]);
			addData->data[addData->num++] = info[i];
		}
		else {
			if (iter->second->guid == info[i].guid && iter->second->value == info[i].value)continue;
			mCustList[type][info[i].ranking] = std::make_shared<CUST_LIST_INFO>(info[i]);
			updateData->data[updateData->num++] = info[i];
		}
	}
	if (addData->num) {
		SendDataBySessionType(SESSION_TYPE_CS2DB, *addData);
	}
	if (updateData->num) {
		SendDataBySessionType(SESSION_TYPE_CS2DB, *updateData);
	}
}