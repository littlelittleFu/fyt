#include "stdafx.h"
#include "DBServer.h"
#include "SessionFactoryDB.h"
#include "CNetManager.h"
#include "DBManager.h"
#include "ProtoMgr.h"
#include "MiniDumper.h"
#include "GameCfgMgr.h"
#include <iostream>

IMPL_SINGLETON(DBServer)

CMiniDumper* g_CMiniDumper = NULL;

void LogText(const char* content, int level)
{
    switch (level) {
    case log_level_error:
        ILogHelper::GetInstance()->LogPrint(log_level_error, content);
        break;
    case log_level_warn:
        ILogHelper::GetInstance()->LogPrint(log_level_warn, content);
        break;
    default:
        ILogHelper::GetInstance()->LogPrint(log_level_normal, content);
        break;
    }
}

DBServer::DBServer()
{
	g_CMiniDumper = new CMiniDumper(TRUE);
}

DBServer::~DBServer() {
	if (g_CMiniDumper) {
		delete g_CMiniDumper;
	}
}

void DBServer::Start()
{
	LOG_NORMAL("db server start");

	if (!InitConfig()) {
		LOG_ERROR("init config failed");
		return;
	}

	if (!InitTable()) {
		LOG_ERROR("init table failed");
		return;
	}

	if (!InitNetwork()) {
		LOG_ERROR("init network failed");
		return;
	}

	if (!CDBManager::GetInstance()->Init()) {
		LOG_ERROR("init db failed");
		return;
	}

	if (!InitDBManagerTimer()) {
		LOG_ERROR("init db manager timer failed");
		return;
	}

    StartConnCheckTimer();

	SetLogLevel();

	Run();

    StopConnCheckTimer();
}

bool DBServer::InitConfig()
{
	LOG_NORMAL("init config begin");
	LOG_NORMAL("init config end");
	return true;
}

bool DBServer::InitTable()
{
	LOG_NORMAL("init table begin");
	const auto& cfgFolder = ConfigInfo::GetInstance()->m_sGameCfgFolderPath;
	GameCfgMgr::GetInstance()->SetGameCfgFolderPath(cfgFolder);

	GameCfgMgr::GetInstance()->ReloadSingleCfg("illegal_characters");

	GameCfgMgr::GetInstance()->ReloadSingleCfg("global");

	LOG_NORMAL("init table end");
	return true;

}

bool DBServer::InitNetwork()
{
	LOG_NORMAL("init network begin");
    ConfigInfo* pConfig = ConfigInfo::GetInstance();

	ISessionFactory::SetInstance(new SessionFactoryDB);
	IProtoMgr::SetInstance(new ProtoMgr);
	CNetManager::GetInstance()->Init(pConfig->m_nNetLibThreadNum);
	CNetManager::GetInstance()->SetLogFunction(LogText);
	CNetManager::GetInstance()->AddListener(pConfig->m_sListenIp, pConfig->m_nListenPort, SESSION_TYPE_DB2CS);
	CNetManager::GetInstance()->AddListener(pConfig->m_sListenIp, pConfig->m_nListenPort+1, SESSION_TYPE_DB2LS);
	CNetManager::GetInstance()->AddConnector(pConfig->m_sServiceServerIp, pConfig->m_nServiceServerPort, SESSION_TYPE_DB2SS);
	LOG_NORMAL("init network end");
	return true;
}

bool DBServer::InitDBManagerTimer()
{
	TimerData timer;
	timer.interval = 86400*1000;
	timer.loop = true;
	timer.callBack = [this](const TimerData&) { UpdateMailDeleteDay(); };
	ITimeHelper::GetInstance()->AddTimer(timer);
	return true;
}

void DBServer::Run()
{
	LOG_NORMAL("db server run");

#ifdef _WIN32
    if (WinService::GetInstance().IsRunAsService()) {
        WinService::GetInstance().SetCurrentState(SERVICE_RUNNING);
    }
#endif

    ITimeHelper::GetInstance()->CalcDeltaTime();    // ÖØÖÃÊ±¼ä´Á

	while (!NeedQuit()) {
		ITimeHelper::GetInstance()->CalcDeltaTime();
		int _Delta = ITimeHelper::GetInstance()->GetDeltaTime();
        LogDebugInfo(_Delta);
		ITimeHelper::GetInstance()->Update(_Delta);
		CNetManager::GetInstance()->OnUpdate(_Delta);
		//IScheduledHelper::GetInstance()->Update(_Delta);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

    Term();
}

bool DBServer::NeedQuit()
{
	return m_NeedQuit;
}

void DBServer::Term()
{
    CNetManager::GetInstance()->UnInit();
}

void DBServer::StartConnCheckTimer()
{
	TimerData timer;
    timer.interval = ConfigInfo::GetInstance()->m_nConnCheckTimerInterval;
    timer.loop = true;
    timer.callBack = [this](const TimerData &) { OnConnCheckTimer(); };

    m_ConnCheckTimerID = ITimeHelper::GetInstance()->AddTimer(timer);
}

void DBServer::StopConnCheckTimer()
{
    ITimeHelper::GetInstance()->RemoveTimer(m_ConnCheckTimerID);
}

void DBServer::OnConnCheckTimer()
{
    ConfigInfo* pConfig = ConfigInfo::GetInstance();

    if (!SessionExist(SESSION_TYPE_DB2SS)) {
        IssueConnectionRequest(pConfig->m_sServiceServerIp, pConfig->m_nServiceServerPort, SESSION_TYPE_DB2SS);
    }

	bool bNeedSendConfigReq = false;

	if (!SessionExist(SESSION_TYPE_DB2LOG)) {
		if (pConfig->IsLogConfigValid())
			IssueConnectionRequest(pConfig->m_sLogServerIP, pConfig->m_nLogServerPort + 4, SESSION_TYPE_DB2LOG);
		else
			bNeedSendConfigReq = true;
	}

	if (bNeedSendConfigReq) {
		ProtoDB_ConfigReq configReq;
		SendDataBySessionType(SESSION_TYPE_DB2SS, configReq);
	}
}

void DBServer::SetLogLevel()
{
	ConfigInfo* pConfig = ConfigInfo::GetInstance();
	int32_t logLevel = (nullptr == pConfig) ? 0 : pConfig->GetInstance()->m_bLogLevel;
	ILogHelper::GetInstance()->SetLogLevel(logLevel);
	CNetManager::GetInstance()->SetLogLevel(logLevel);
}

void DBServer::LogDebugInfo(uint32_t delta)
{
    static int maxDeltaTime = 0;
    if (delta > maxDeltaTime) maxDeltaTime = delta;

    if (delta > 1000)
        MsgCostStat::GetInstance()->StartStat();
    else
        MsgCostStat::GetInstance()->StopStat();

    static int curTime = 0;
    curTime += delta;
    if (curTime < 10000) return;
    curTime = 0;

    auto info = MsgCostStat::GetInstance()->CollMsgCostInfo();
    if (!info.empty()) {
        LOG_NORMAL(
            "\n########################################################################\n"
            "delta: %d, max_delta: %d\n"
            "%s\n"
            "########################################################################",
            delta, maxDeltaTime, info.c_str());
    }
}

void DBServer::UpdateMailDeleteDay()
{
	CDBManager::MailUpdateDay();
}
