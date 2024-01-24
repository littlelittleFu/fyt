#pragma once
#include<iostream>
#include<map>
#include<vector>

using CustList = std::vector<std::pair<uint64_t, CUST_DATA_SP>>;
using TempCustList = std::map<int, std::map<uint64_t, CUST_DATA_SP>>;

class CustListMgr {
	DECL_SINGLETON(CustListMgr);

public:
	CustListMgr() { Init(); };
	~CustListMgr(){};

	void Init();
	void Sort();
	void InsertDataByType(uint64_t guid,int type,int64_t value,const char* desc);

	void GetInfoFromDB(uint16_t num, const CUST_LIST_INFO* info);
	void SyncDataToDB();

	void GetCustListByType(int type, CLuaObject& table);
private:
	int mflag[CustType_Max];
	CustList mCustVec[CustType_Max];
	TempCustList mUnSortCustList;
};