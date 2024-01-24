#pragma once
#include"iostream"
#include<vector>
#include<map>

using CustInfoList = std::map<uint16_t, CUST_DATA_SP>;

class CustListInfoMgr {
	DECL_SINGLETON(CustListInfoMgr);
public:
	void GetCustInfoFromDB(uint16_t num, const CUST_LIST_INFO *info);
	void SyncCustInfoFromMS(int type, uint16_t num, CUST_LIST_INFO* info);

private:
	CustInfoList mCustList[CustType_Max];
};