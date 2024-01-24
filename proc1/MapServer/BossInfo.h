#pragma once
#include<unordered_map>
#include<string>
#include<vector>
#include"DataInfo.hpp"

#define ONE_THOUSAND_MS

typedef std::unordered_map<uint16_t, std::unordered_map<uint32_t,std::vector<BossInfo>>> BossList;

class BossInfoMgr {
	DECL_SINGLETON(BossInfoMgr);
public:
	void UpdateBossInfoWhenGen(const BossInfo& info);
	void UpdateBossInfoWhenDie(const BossInfo& info);
	void GetBossInfoByMapID(uint16_t mapid, std::vector<BossInfo>& list);
private:
	BossList mBossList;
};