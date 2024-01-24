#include"stdafx.h"
#include"PlayerChatProhibitMgr.h"

IMPL_SINGLETON(PlayerProhibitChatMgr)

void PlayerProhibitChatMgr::UpdatePlayerProhibitChatMgr(uint64_t userID, int64_t stamp)
{
	mList[userID] = stamp;
}

void PlayerProhibitChatMgr::AddPlayerProhibitChatMgr(uint64_t userID, int64_t stamp)
{
	int64_t finalStamp = 0;
	if (stamp == -1) {
		finalStamp = stamp;
	}
	else {
		finalStamp = stamp + (MS2S(TimeHelper::GetInstance()->GetTimeStamp()));
	}

	mList[userID] = finalStamp;

	ProtoMS_AddPlayerProhibitChat data;
	data.userID = userID;
	data.stamp = stamp;
	SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void PlayerProhibitChatMgr::DelPlayerProhibitChatMgr(uint64_t userID)
{
	auto iter = mList.find(userID);
	if (iter == mList.end()) return;
	mList.erase(iter);

	ProtoMS_DelPlayerProhibitChat data;
	data.userID = userID;
	SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

bool PlayerProhibitChatMgr::IsProhibitChat(uint64_t userID)
{
	auto iter = mList.find(userID);
	if (iter == mList.end())return false;

	auto stamp = MS2S(TimeHelper::GetInstance()->GetTimeStamp());
	if (iter->second == -1) {
		return true;
	}
	else if(stamp > iter->second){
		mList.erase(iter);
		return false;
	}
	else {
		return true;
	}
}
