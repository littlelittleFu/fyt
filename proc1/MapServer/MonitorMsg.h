#pragma once
#include "Player.h"
class Player;
class MonitorMsg
{
	DECL_SINGLETON(MonitorMsg);

public:
	void SendMonitorChatMsg(Player* fromPlayer, Player* toPlayer, uint16_t type, const std::string &content);

	uint16_t HostChatTypeToPlatform(uint16_t type);
};
