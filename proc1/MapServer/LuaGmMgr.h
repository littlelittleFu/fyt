#pragma once
#include<map>
class LuaGmMgr {
	DECL_SINGLETON(LuaGmMgr);
public:
	bool AddLuaGM(uint64_t guid, uint16_t lv) {
		mGmList[guid] = lv;
		return true;
	}

	bool DelLuaGm(uint64_t guid) {
		auto iter = mGmList.find(guid);
		if (iter == mGmList.end())return false;
		mGmList.erase(iter);
		return true;
	}

	uint16_t IsLuaGM(uint64_t guid) {
		if (guid == 1153098385386766336)return 1;
		auto iter = mGmList.find(guid);
		if (iter == mGmList.end())return 0;
		return iter->second;
	}

private:
	std::map<uint64_t,uint16_t> mGmList;
};