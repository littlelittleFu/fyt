#pragma once
#include<unordered_map>

class PlayerProhibitChatMgr {
	DECL_SINGLETON(PlayerProhibitChatMgr);
public:
	void UpdatePlayerProhibitChatMgr(uint64_t userID, int64_t stamp);
	void AddPlayerProhibitChatMgr(uint64_t userID, int64_t stamp);
	void DelPlayerProhibitChatMgr(uint64_t userID);
	bool IsProhibitChat(uint64_t userID);

private:
	std::unordered_map<uint64_t, int64_t> mList;
};

