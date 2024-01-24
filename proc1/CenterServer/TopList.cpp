#include "stdafx.h"
#include "TopList.h"
#include "ITimeHelper.h"
#include "CNetManager.h"
#include "SessionFactory.h"

IMPL_SINGLETON(TopList)

TopList::TopList()
{
	TimerData timer;
	auto global = sGlobalConfig.GetData();
	timer.interval = global->TopListFlashTime;
	timer.loop = true;
	timer.callBack = [this](const TimerData&) {
		/*//定时器通知CS同步数据
		SendGetTopListReq();*/
		// 定时器负责排序
		TopListRange();
		//LOG_ERROR("mTopListNum = %d", mTopListNum);
	};
	mFlashTimerID = ITimeHelper::GetInstance()->AddTimer(timer);
}

TopList::~TopList() {
	if (mFlashTimerID != 0) {
		ITimeHelper::GetInstance()->RemoveTimer(mFlashTimerID);
		mFlashTimerID = 0;
	}
	std::map<uint64_t, TOPLIST_INFO*>::iterator iter = mTopList.begin();
	for (; iter != mTopList.end(); ++iter)
	{
		if (iter->second)
		{
			SAFE_RELEASE(iter->second);
		}
	}
	mTopList.clear();
	for (int32_t i = 0; i < sort_type_max; ++i)
	{
		mTopListRange[i].clear();
	}
}

void TopList::AddTopList(uint8_t type, uint64_t*rolelist, TOPLIST_INFO* topList, uint8_t topListNum)
{
	TOPLIST_INFO* info = nullptr;
	for (uint8_t i = 0; i < topListNum; i++) {
		auto iter = mTopList.find(rolelist[i]);
		if (iter != mTopList.end())
		{
			continue;
		}
		info = new TOPLIST_INFO();
		*info = *(topList + i);
		mTopList[rolelist[i]] = info;
	}
	TopListRange();
}

void TopList::AddTmpTopList(const ROLE_BRIEF_INFO& roleBriefInfo)
{
	auto iter = mTopList.find(roleBriefInfo.guid);
	if (iter != mTopList.end()&& iter->second)
	{
		strcpy_s(iter->second->player_name, _countof(iter->second->player_name), roleBriefInfo.name);
		iter->second->level = roleBriefInfo.level;
		iter->second->job = roleBriefInfo.job;
		iter->second->gender = roleBriefInfo.gender;
	}
	else
	{
		TOPLIST_INFO* tmp = new TOPLIST_INFO();
		strcpy_s(tmp->player_name, _countof(tmp->player_name), roleBriefInfo.name);
		tmp->level = roleBriefInfo.level;
		tmp->job = roleBriefInfo.job;
		tmp->gender = roleBriefInfo.gender;
		mTopList[roleBriefInfo.guid] = tmp;
	}
}

void TopList::TopListRange()
{
	for (uint8_t i = 0; i < sort_type_beauty; i++)
		LevelRange(i);
}

void TopList::LevelRange(uint8_t type)
{
	std::list<TOPLIST_INFO*> tmp;
	for (auto i : mTopList) {
		tmp.emplace_back(i.second);
	}
	uint32_t minSize = std::min<uint32_t>((uint32_t)tmp.size(), 100);
	mTopListRange[type].resize(minSize);
	if (type == 0) {
		tmp.sort([](const TOPLIST_INFO* a, const TOPLIST_INFO* b) {
			return a->level > b->level;
		});
	}
	else {
		tmp.sort([&type](const TOPLIST_INFO* a, const TOPLIST_INFO* b) {
			if (a->job != b->job) {
				if (a->job == type)return true;
				if (b->job == type)return false;
			}
			return a->level > b->level;
		});
	}
	uint32_t i = 0;
	for (auto x : tmp) {
		mTopListRange[type][i++] = x;
		if (i >= mTopListRange[type].size()) break;
	}
}

void TopList::Update(ProtoMS_UpdateTopListAck *ack)
{
	if (nullptr == ack) return;
	auto iter = mTopList.find(ack->role);
	if (iter != mTopList.end() && iter->second)
	{
		*iter->second = ack->nowRole;
	}
	else
	{
		TOPLIST_INFO* tmp = new TOPLIST_INFO();
		*tmp = ack->nowRole;
		mTopList[ack->role] = tmp;
	}
}

void TopList::SendTopList(ProtoGS_TopListReq* req)
{
	if (!req) return;
	ProtoGS_TopListAck topListAck;
	topListAck.type = req->type;
	auto tmp = ITimeHelper::GetInstance()->GetTimer(mFlashTimerID);
	topListAck.time = tmp->interval - tmp->tick;
	topListAck.num = mTopListRange[req->type].size();
	topListAck.sessionid = req->sessionid;
	for (uint8_t i = 0; i < mTopListRange[req->type].size(); i++) {
		topListAck.info[i] = *(mTopListRange[req->type][i]);
	}
	SendDataBySessionType(SESSION_TYPE_CS2GS, topListAck);
}

void TopList::ChangeNameInfo(uint64_t guid, const std::string& name, const std::string& orgName)
{
	auto it = mTopList.find(guid);
	if (it != mTopList.end()) {
		if (it->second) {
			strcpy_s(it->second->player_name, _countof(it->second->player_name), name);
		}
	}

	for (int i = sort_type_level; i < sort_type_max; ++i){
		for (auto iter = mTopListRange[i].begin(); iter != mTopListRange[i].end(); ++iter){
			if (!(*iter))continue;
			if (strcmp((*iter)->player_name, orgName.c_str()) == 0) {
				strcpy_s((*iter)->player_name, _countof((*iter)->player_name), name);
				break;
			}
		}
			
	}
}