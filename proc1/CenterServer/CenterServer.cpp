#include "stdafx.h"
#include "CenterServer.h"
#include "SessionFactoryCS.h"
#include "CNetManager.h"
#include "ProtoMgr.h"
#include "MiniDumper.h"
#include "mail_table.h"
#include "GameMallMgr.h"
#include "ScheduledHelper.h"


IMPL_SINGLETON(CenterServer)
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

CenterServer::CenterServer() : m_ThreadPool(4) {
	g_CMiniDumper = new CMiniDumper(true);
}

CenterServer::~CenterServer() {
	if (g_CMiniDumper) {
		delete g_CMiniDumper;
	}
}

void CenterServer::Start()
{
	LOG_NORMAL("center server start");
	if (!InitConfig()) {
		LOG_ERROR("init config failed");
		return;
	}

	if (!InitNetwork()) {
		LOG_ERROR("init network failed");
		return;
	}

	if (!InitTable()) {
		LOG_ERROR("init table failed");
		return;
	}

	if (!InitLuaEngine()) {
		LOG_ERROR("init lua engine failed");
		return;
	}
	CLuaEngineMgr()->RunLuaFile("Main");

    StartConnCheckTimer();

	SetLogLevel();
	Run();

    StopConnCheckTimer();
}

bool CenterServer::InitConfig()
{
	LOG_NORMAL("init config begin");
	LOG_NORMAL("init config end");
	return true;
}

bool CenterServer::InitTable()
{
	LOG_NORMAL("init table begin");
	const auto &cfgFolder = ConfigInfo::GetInstance()->m_sGameCfgFolderPath;
	GameCfgMgr::GetInstance()->SetGameCfgFolderPath(cfgFolder);
	GameCfgMgr::GetInstance()->LoadAllCfg();
	GameMallMgr::GetInstance()->Init();
	LOG_NORMAL("init table end");
	return true;
}

bool CenterServer::InitNetwork()
{
	LOG_NORMAL("init network begin");
    ConfigInfo* pConfig = ConfigInfo::GetInstance();

	ISessionFactory::SetInstance(new SessionFactoryCS);
	IProtoMgr::SetInstance(new ProtoMgr);
	CNetManager::GetInstance()->Init(pConfig->m_nNetLibThreadNum);
	CNetManager::GetInstance()->SetLogFunction(LogText);
    CNetManager::GetInstance()->AddListener(pConfig->m_sListenIp, pConfig->m_nListenPort, SESSION_TYPE_CS2GS);
	CNetManager::GetInstance()->AddListener(pConfig->m_sListenIp, pConfig->m_nListenPort+1, SESSION_TYPE_CS2LS);
	CNetManager::GetInstance()->AddListener(pConfig->m_sListenIp, pConfig->m_nListenPort+2, SESSION_TYPE_CS2MS);
    CNetManager::GetInstance()->AddConnector(pConfig->m_sServiceServerIp, pConfig->m_nServiceServerPort, SESSION_TYPE_CS2SS);
	LOG_NORMAL("init network end");
	return true;
}

bool CenterServer::InitLuaEngine()
{
	LOG_NORMAL("init lua engine begin");
	const auto &scriptFolder = ConfigInfo::GetInstance()->m_sScriptFolderPath;
	CLuaEngineMgr()->Init();
	CLuaEngineMgr()->AddSearchPath(scriptFolder);
	CLuaEngineMgr()->RunLuaFile("LoadAllFiles");
	LOG_NORMAL("init lua engine end");

	return true;
}
void CenterServer::Run()
{
	LOG_NORMAL("center server run");

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
		IScheduledHelper::GetInstance()->Update(_Delta);
        CallFuncInQueue();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

    Term();
}

void CenterServer::CallFuncInQueue()
{
    auto &queue = GetCallableQueue();
    auto list = queue.popall();
    for (auto &func : list) func();
}

bool CenterServer::NeedQuit()
{
	return m_NeedQuit;
}

void CenterServer::Term()
{
    m_ThreadPool.stop();
    CNetManager::GetInstance()->UnInit();
}

void CenterServer::StartConnCheckTimer()
{
	TimerData timer;
    timer.interval = ConfigInfo::GetInstance()->m_nConnCheckTimerInterval;
    timer.loop = true;
    timer.callBack = [this](const TimerData &) { OnConnCheckTimer(); };

    m_ConnCheckTimerID = ITimeHelper::GetInstance()->AddTimer(timer);
}

void CenterServer::StopConnCheckTimer()
{
    ITimeHelper::GetInstance()->RemoveTimer(m_ConnCheckTimerID);
}

void CenterServer::OnConnCheckTimer()
{
    ConfigInfo* pConfigInfo = ConfigInfo::GetInstance();

    if (!SessionExist(SESSION_TYPE_CS2SS)) {
        IssueConnectionRequest(pConfigInfo->m_sServiceServerIp, pConfigInfo->m_nServiceServerPort, SESSION_TYPE_CS2SS);
    }

    bool bNeedSendConfigReq = false;

    if (!SessionExist(SESSION_TYPE_CS2DB)) {
        if (pConfigInfo->IsDBConfigValid())
            IssueConnectionRequest(pConfigInfo->m_sDBServerIP, pConfigInfo->m_nDBServerPort, SESSION_TYPE_CS2DB);
        else
            bNeedSendConfigReq = true;
    }

	if (!SessionExist(SESSION_TYPE_CS2LOG)) {
		if (pConfigInfo->IsLogConfigValid())
			IssueConnectionRequest(pConfigInfo->m_sLogServerIP, pConfigInfo->m_nLogServerPort, SESSION_TYPE_CS2LOG);
		else
			bNeedSendConfigReq = true;
	}

    if (bNeedSendConfigReq) {
        ProtoCS_ConfigReq configReq;
        SendDataBySessionType(SESSION_TYPE_CS2SS, configReq);
    }
}

void CenterServer::SetLogLevel()
{
	ConfigInfo* pConfig = ConfigInfo::GetInstance();
	int32_t logLevel = (nullptr == pConfig) ? 0 : pConfig->GetInstance()->m_bLogLevel;
	ILogHelper::GetInstance()->SetLogLevel(logLevel);
	CNetManager::GetInstance()->SetLogLevel(logLevel);
}

void CenterServer::LogDebugInfo(uint32_t delta)
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
