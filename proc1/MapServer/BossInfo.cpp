#include"stdafx.h"
#include"BossInfo.h"

IMPL_SINGLETON(BossInfoMgr)

void BossInfoMgr::UpdateBossInfoWhenDie(const BossInfo& info) 
{
	auto iter = mBossList.find(info.mapID);
	if (iter == mBossList.end())return;
	auto bossList = iter->second.find(info.tempID);
	if (bossList == iter->second.end())return;

	auto boss = find_if(bossList->second.begin(), bossList->second.end(), [=](const BossInfo& data) {
		if (data.guid == info.guid)return true;
		return false;
		});

	if (boss == bossList->second.end())return;

	if (info.reliveTime == 0) {
		bossList->second.erase(boss);
	}
	else {
		boss->reliveTime = info.reliveTime;
	}
}

void BossInfoMgr::UpdateBossInfoWhenGen(const BossInfo& info)
{
	// 增加重生前guid 判定是否删除已复活的boss
	if (info.lastGUID) {
		auto iter = mBossList.find(info.mapID);
		if (iter != mBossList.end()) {
			auto bossListIt = iter->second.find(info.tempID);
			if (bossListIt != iter->second.end()) {
				bossListIt->second.erase(std::remove_if(bossListIt->second.begin(), bossListIt->second.end(),
					[&](const BossInfo& bossInfo) {
						if (bossInfo.guid == info.lastGUID)return true;
						return false;
					})
					, bossListIt->second.end());
			}
		}
	}
	mBossList[info.mapID][info.tempID].push_back(info);
}

void BossInfoMgr::GetBossInfoByMapID(uint16_t mapid, std::vector<BossInfo>& list)
{
	auto it = mBossList.find(mapid);
	if (it == mBossList.end())return;
	for (auto& bossList : it->second) {
		for (auto& boss : bossList.second) {
			list.push_back(boss);
		}
	}
}