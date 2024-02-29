#pragma once
#include<list>
#include<string>
#include"CSocket.h"
#include"CMutex.h"

struct SessionInfo
{
	int32_t         nType;
	int32_t         nParam;
	bool            bAddFront;

	std::string     sLocalIP;
	uint32_t        nLocalPort;
	std::string     sRomoteIP;
	uint32_t        nRomotePort;

	SOCKET          sock;

	SessionInfo() : nType(0), nParam(0), bAddFront(false), nLocalPort(0), nRomotePort(0), sock(INVALID_SOCKET)
	{}
};

typedef std::unique_ptr<SessionInfo> UPSessionInfo;
typedef std::list<UPSessionInfo> SessionInfoList;


class SessionMgr
{
private:
	SessionMgr() {};
	~SessionMgr() {};

public:
	void CacheSessionInfo(UPSessionInfo upSessionInfo);
	void CacheSessionInfo(int32_t sessionType, int32_t sessionParam, bool addFront,
		const std::string& localIP, uint32_t localPort, const std::string& remoteIP,
		uint32_t remotePort, SOCKET sock);



private:
	SessionInfoList m_SessionInfoList;
	CMutex m_Mutex;


private:
	static SessionMgr* instance;
public:
	static SessionMgr* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new SessionMgr;
			return instance;
		}
		return instance;
	}
};