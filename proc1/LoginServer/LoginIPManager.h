#pragma once

#include <map>
#include "DataInfo.hpp"
#include "ProtoDB.h"


class LoginIPManager
{
	DECL_SINGLETON(LoginIPManager)
public:
	LoginIPManager() {};
	~LoginIPManager() {};


public:
	bool GetWhiteIPList();
	bool GetWhiteAccountNameList();
	void InitLoginIpDataFromDB(uint16_t num,LOGIN_IP_DATA*data);
	void SyncLoginIpInfoFromDB(ProtoDB_SyncLoginTypeToLS* data);
	bool IsWhiteIp(uint32_t ip);
	bool IsBlackIp(uint32_t ip);
	bool IsWhiteName(const char* account);

private:
	static size_t CURLWriteCallback(void* data, size_t size, size_t nmemb, void* userp);

private:
	std::map<uint32_t, LOGIN_IP_DATA>mIPMap;
	std::vector<std::string> mWhiteAcountNameList;
};
