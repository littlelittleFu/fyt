#pragma once
#include "Session.h"
#include "ProtoLog.h"
#include "CNetManager.h"

class SessionGS2Log : public Session
{
public:
	SessionGS2Log();
	~SessionGS2Log();

	virtual void OnEstablish(SOCKET _Socket);
	virtual void OnLost();
	virtual void OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData);
	virtual void OnError(DWORD _ErrorCode);
	virtual void OnUpdate(UINT _Delta);
	virtual void DoHeartBeat();

	template<class T>
	static void SendDBLogData(uint16_t type, const T& lc)
	{
		SessionGS2Log* pSession = static_cast<SessionGS2Log*>(CNetManager::GetInstance()->GetSessionByType(SESSION_TYPE_GS2LOG));
		if (!pSession) {
			CLogger::GetInstance()->LogCritical("[%s:%d] pSession is NULL. nSessionType: %d", FUNC_LINE, SESSION_TYPE_GS2LOG);
			return;
		}
		static ProtoLog_LoggingReq req;
		req.Clear();
		req.Init(std::string(ConfigInfo::GetInstance()->m_sListenIp), ConfigInfo::GetInstance()->m_nListenPort, MODULE_TYPE_GS, ConfigInfo::GetInstance()->m_serverId, type, GetTimeStampMillisecond());
		req << lc;
		pSession->SendPkg(&req, sizeof(req));
	}

private:
	void HandleLogMsg(uint16_t protoid, void* pData);
    void HandleLogMsg_HeartBeatAck(void *pData);
};

#define SendDBLogData(type, data) SessionGS2Log::SendDBLogData<decltype(data)>(type, data);