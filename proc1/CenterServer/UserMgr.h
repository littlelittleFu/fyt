#pragma once

#include "User.h"
#include <unordered_map>

class UserMgr
{
	DECL_SINGLETON(UserMgr);
public:
	User* AddUser(uint64_t userID);//PLAYER id
	void RemoveUser(uint64_t userID);
	User* FindUser(uint64_t userID);
	User* FindUser(uint32_t token);
	User* FindUser(const std::string & name);
    User *FindUserByRoleGUID(uint64_t roleGUID);
	User* operator[](uint64_t roleGuid);
	void SetAllUserOnlineStatus(uint8_t status);
	std::unordered_map<uint64_t, User*>&  GetUserMap() { return mUserMap; };
private:
	UserMgr();
	virtual ~UserMgr();
	void UpdateLogOnlineNum();
protected:
	std::unordered_map<uint64_t, User*> mUserMap;
	uint32_t  mUpdateOnlineNumTimerId = 0;
};
