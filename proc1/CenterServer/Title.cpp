#include "stdafx.h"
#include "Title.h"
#include "ProtoDB.h"

IMPL_SINGLETON(Title);

void Title::AddTitle(uint64_t guid, const TITLE_INFO& info)
{
	mTitleList[guid].push_back(make_shared<TITLE_INFO>(std::move(info)));

}

void Title::DelTitle(uint64_t guid,uint16_t num,const uint32_t* id)
{
	auto iter = mTitleList.find(guid);
	if (iter == mTitleList.end())return;
	for (int i = 0; i < num; ++i) {
		auto it = find_if(iter->second.begin(), iter->second.end(), [=](const SP_TITLE_INFO spInfo) {
			if (spInfo->Id == id[i])return true;
			return false;
			});

		if (it == iter->second.end()) {
			++id;
			continue;
		}
		iter->second.erase(it);
		++id;
	}
}

void Title::ChangeWearType(uint64_t guid, uint32_t id, uint16_t wearType)
{
	auto iter = mTitleList.find(guid);
	if (iter == mTitleList.end())return;
	auto it = find_if(iter->second.begin(), iter->second.end(), [=](const SP_TITLE_INFO spInfo) {
		if (spInfo->Id == id)return true;
		return false;
		});
	if (it == iter->second.end())return;
	it->get()->isWear = wearType;
}

void Title::SyncPlayerTitleInfo(uint64_t guid, uint16_t num, const TITLE_INFO* info)
{
	auto iter = mTitleList.find(guid);
	if (iter == mTitleList.end()) {
		std::vector<SP_TITLE_INFO> vec;
		for (int i = 0; i < num; ++i) {
			vec.push_back(std::move(make_shared<TITLE_INFO>(info[i])));
		}
		mTitleList[guid] = std::move(vec);
	}
	else{
		for (int i = 0; i < num; ++i) {
			auto titleCfg = sTitleConfig.GetByID(info[i].Id);
			if (nullptr == titleCfg) {
				continue;
			}
			auto it = find_if(iter->second.begin(), iter->second.end(), [=](const SP_TITLE_INFO data) {
				if (data->Id == info[i].Id)return true;
				return false;
				});
			if (it != iter->second.end()) {
				it->get()->lifeTime = info[i].lifeTime;
				it->get()->isWear = info[i].isWear;
			}
			else {
				iter->second.push_back(std::move(make_shared<TITLE_INFO>(*info)));
			}
		}
	}
}

void Title::UpdateTiltleInfo(uint64_t guid, uint16_t num, const TITLE_INFO* info)
{
	auto iter = mTitleList.find(guid);
	if (iter == mTitleList.end())return;
	for (int i = 0; i < num; ++i) {
		auto title = find_if(iter->second.begin(), iter->second.end(), [=](const SP_TITLE_INFO data) {
			if (data->Id == info[i].Id)return true;
			return false;
			});
		if (title == iter->second.end())continue;
		if (info[i].timeLimit == 0)continue;
		auto flag = find(mTitleFlag[guid].begin(), mTitleFlag[guid].end(), info[i].Id);
		if (flag == mTitleFlag[guid].end()) {
			mTitleFlag[guid].push_back(info[i].Id);
		}
	}
}

void Title::SendPlayerInfoToMS(uint64_t guid)
{
	auto iter = mTitleList.find(guid);
	if (iter == mTitleList.end())return;
	if (iter->second.empty())return;
	ProtoDB_GetTitleInfoAck data;
	data.guid = guid;
	for (int i = 0; i < iter->second.size(); ++i) {
		data.info[data.num] = *iter->second[i].get();
		++data.num;
		if (data.num == 100) {
			SendDataBySessionType(SESSION_TYPE_CS2MS, data);
			memset(data.info, 0, sizeof(data.info));
			data.num = 0;
		}
	}
	if (data.num != 0 && data.num != 100) {
		SendDataBySessionType(SESSION_TYPE_CS2MS, data);

	}
}

void Title::GenerateSyncInfoToDB(uint64_t guid, uint16_t& num, TITLE_INFO* info)
{
	auto iter = mTitleFlag.find(guid);
	if (iter == mTitleFlag.end())return;
	if (iter->second.empty())return;

	for (auto i : iter->second) {
		auto roleTitleList = mTitleList.find(guid);
		if (roleTitleList == mTitleList.end())return;
		auto title = find_if(roleTitleList->second.begin(), roleTitleList->second.end(), [=](const SP_TITLE_INFO data) {
			if (data->Id == i)return true;
			return false;
			});
		if (title == roleTitleList->second.end())continue;

		info[num] = *title->get();
		++num;
	}
	mTitleFlag.erase(iter);
}