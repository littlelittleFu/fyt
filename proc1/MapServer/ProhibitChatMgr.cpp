#include "stdafx.h"
#include "ProhibitChatMgr.h"

IMPL_SINGLETON(ProhibitChatMgr)

void ProhibitChatMgr::GetProhibitInfoAck(uint8_t num, const PROHIBIT_CHAT_DATA* data)
{
	for (int i = 0; i < num; ++i)
	{
		mProhibitChatMap[data[i].playerguid] = data[i];
	}
}

bool ProhibitChatMgr::IsProhibitChatStatus(uint64_t playerguid)
{
	auto iter = mProhibitChatMap.find(playerguid);
	if (iter != mProhibitChatMap.end())
	{
		auto stamp = (uint64_t)MS2S(TimeHelper::GetInstance()->GetTimeStamp());
		if (stamp > iter->second.time)
		{
			// 删掉数据库中数据
			PROHIBIT_CHAT_DATA data (iter->second);
			DelProhibitData(1, &data);
			return false;
		}
		return true;
	}
	return false;
}

void ProhibitChatMgr::DelProhibitData(uint8_t num, const PROHIBIT_CHAT_DATA* data)
{
	ProtoMS_DelProhibitInfo info;
	for (int i = 0; i < num; ++i)
	{
		auto iter = mProhibitChatMap.find(data[i].playerguid);
		if (iter != mProhibitChatMap.end())
		{
			info.infos[info.num] = data[i];
			++info.num;
			mProhibitChatMap.erase(iter);
		}
	}
	SendDataBySessionType(SESSION_TYPE_MS2CS, info);
}

void ProhibitChatMgr::AddProhibitData(uint8_t num, const PROHIBIT_CHAT_DATA* data)
{
	for (int i = 0; i < num; ++i)
	{
		mProhibitChatMap[data[i].playerguid] = data[i];
	}
	ProtoMS_AddProhibitChatInfo info;
	info.num = num;
	std::move(data, data + num, info.infos);
	SendDataBySessionType(SESSION_TYPE_MS2CS, info);
}