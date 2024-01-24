#include "stdafx.h"
#include "UserMgr.h"

#define UpdateLogOnlineNumIntervalTime 60000

IMPL_SINGLETON(UserMgr)

UserMgr::UserMgr()
{
	 TimerData timer;
	 auto global = sGlobalConfig.GetData();
	 timer.interval = UpdateLogOnlineNumIntervalTime;
	 timer.loop = true;
	 timer.callBack = [this](const TimerData &) { UpdateLogOnlineNum(); };
	 mUpdateOnlineNumTimerId = ITimeHelper::GetInstance()->AddTimer(timer);
}

UserMgr::~UserMgr()
{
	ITimeHelper::GetInstance()->RemoveTimer(mUpdateOnlineNumTimerId);
	mUpdateOnlineNumTimerId = 0;
}

User* UserMgr::AddUser(uint64_t userID)
{
	auto user = FindUser(userID);
	if (nullptr != user){
		return user;
	}


	user = new User();
	user->SetID(userID);

	mUserMap[userID] = user;
	return user;
}

void  UserMgr::RemoveUser(uint64_t userID)
{
	auto user = FindUser(userID);
	if (nullptr != user) {
		mUserMap.erase(userID);
		SAFE_RELEASE(user);	
	}
}

User* UserMgr::FindUser(uint64_t userID)
{
	if (mUserMap.count(userID) > 0) {
		return mUserMap[userID];
	}
	return nullptr;
}

User* UserMgr::FindUser(uint32_t token)
{
	for (auto& iter : mUserMap) {
		if (iter.second->GetToken() == token) {
			return iter.second;
		}
	}
	return nullptr;
}


User* UserMgr::FindUser(const std::string& name)
{
	for (auto& iter : mUserMap) {
		if (iter.second->GetUserName() == name) {
			return iter.second;
		}
	}
	return nullptr;
}

User *UserMgr::FindUserByRoleGUID(uint64_t roleGUID)
{
    for (auto &it : mUserMap) {
        auto &user = it.second;
        if (!user) continue;
        const auto &roleData = user->GetRoleDataMap();
		const auto& roleDelData = user->GetDeleteRoleDataMap();
        if (roleData.find(roleGUID) == roleData.end())
			if (roleDelData.find(roleGUID) == roleDelData.end())
				continue;
        return user;
    }
    return nullptr;
}

User* UserMgr::operator[](uint64_t roleGuid)
{
    return FindUserByRoleGUID(roleGuid);
}

void UserMgr::SetAllUserOnlineStatus(uint8_t status)
{
	for (auto& iter : mUserMap)
	{
		if (iter.second != nullptr)
		{
			iter.second->SetOnlineState(status);
		}
	}
}

void UserMgr::UpdateLogOnlineNum()
{
	uint32_t num = 0;
	for (auto& iter : mUserMap)
	{
		if (!iter.second) continue;
		if (iter.second->GetOnlineState() != online_state_logged_in) continue;
		num ++;
	}

	SendDBLogData(log_type_online_num, LogOnlineNum(num));
}
