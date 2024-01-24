#pragma once
#include<map>
#include "DataInfo.hpp"
typedef std::map<uint64_t, PROHIBIT_CHAT_DATA> ProhibitChatMap;


class ProhibitChatMgr
{
	DECL_SINGLETON(ProhibitChatMgr)
public:
	ProhibitChatMgr() {};
	~ProhibitChatMgr() {};

	void GetProhibitInfoAck(uint8_t num, const PROHIBIT_CHAT_DATA* data);
	bool IsProhibitChatStatus(uint64_t playerguid);
	void DelProhibitData(uint8_t num, const PROHIBIT_CHAT_DATA* data);
	void AddProhibitData(uint8_t num, const PROHIBIT_CHAT_DATA* data);

private:
	ProhibitChatMap mProhibitChatMap;
};