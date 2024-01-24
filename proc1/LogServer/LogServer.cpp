#include "stdafx.h"
#include "LogServer.h"
#include "SessionFactoryLog.h"
#include "CNetManager.h"
#include "LogManager.h"
#include "ProtoMgr.h"
#include "MiniDumper.h"

IMPL_SINGLETON(LogServer)

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

void CmdFunThread()
{
	while (1)
	{
		char cmdBuff[128] = { 0 };
		fgets(cmdBuff, sizeof(cmdBuff), stdin);
		// SwitchLogDB
		if (_stricmp(cmdBuff, (std::string(SWITCH_LOG_DB_CMD) + "\n").c_str()) == 0)
		{
			CLogManager::GetInstance()->SetSwitchLogDB("");
		}
		else
		{
			LOG_NORMAL("不支持的命令!");
		}
	}
}
LogServer::LogServer()
{
	g_CMiniDumper = new CMiniDumper(TRUE);
	//m_cmd = std::thread(CmdFunThread);
	//m_cmd.detach();
}

LogServer::~LogServer() {
	if (g_CMiniDumper) {
		delete g_CMiniDumper;
	}
}

void LogServer::Start()
{
	LOG_NORMAL("log server start");

	if (!InitConfig()) {
		LOG_ERROR("init config failed");
		return;
	}

	if (!InitNetwork()) {
		LOG_ERROR("init network failed");
		return;
	}

	if (!CLogManager::GetInstance()->Init()) {
		LOG_ERROR("init db failed");
		return;
	}
	if (!CLogManager::GetInstance()->InitGame()) {
		LOG_ERROR("init gamedb failed");
		return;
	}
	StartConnCheckTimer();

	SetLogLevel();

	Run();

	StopConnCheckTimer();
}

bool LogServer::InitConfig()
{
	LOG_NORMAL("init config begin");
	LOG_NORMAL("init config end");
	return true;
}

bool LogServer::InitNetwork()
{
	LOG_NORMAL("init network begin");
	ConfigInfo* pConfig = ConfigInfo::GetInstance();

	ISessionFactory::SetInstance(new SessionFactoryLog);
	IProtoMgr::SetInstance(new ProtoMgr);
	CNetManager::GetInstance()->Init(pConfig->m_nNetLibThreadNum);
	CNetManager::GetInstance()->SetLogFunction(LogText);
	CNetManager::GetInstance()->AddListener(pConfig->m_sListenIp, pConfig->m_nListenPort, SESSION_TYPE_LOG2CS);
	CNetManager::GetInstance()->AddListener(pConfig->m_sListenIp, pConfig->m_nListenPort + 1, SESSION_TYPE_LOG2LS);
	CNetManager::GetInstance()->AddListener(pConfig->m_sListenIp, pConfig->m_nListenPort + 2, SESSION_TYPE_LOG2MS);
	CNetManager::GetInstance()->AddListener(pConfig->m_sListenIp, pConfig->m_nListenPort + 3, SESSION_TYPE_LOG2GS);
	CNetManager::GetInstance()->AddListener(pConfig->m_sListenIp, pConfig->m_nListenPort + 4, SESSION_TYPE_LOG2DB);

	CNetManager::GetInstance()->AddConnector(pConfig->m_sServiceServerIp, pConfig->m_nServiceServerPort, SESSION_TYPE_LOG2SS);
	LOG_NORMAL("init network end");
	
	return true;
}

void LogServer::Run()
{
	LOG_NORMAL("log server run");

    ITimeHelper::GetInstance()->CalcDeltaTime();    // 重置时间戳

	while (!NeedQuit()) {
		ITimeHelper::GetInstance()->CalcDeltaTime();
		int _Delta = ITimeHelper::GetInstance()->GetDeltaTime();
        LogDebugInfo(_Delta);
		ITimeHelper::GetInstance()->Update(_Delta);
		CNetManager::GetInstance()->OnUpdate(_Delta);
		CLogManager::GetInstance()->CheckSwitchLogDB();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

bool LogServer::NeedQuit()
{
	return m_NeedQuit;
}

void LogServer::StartConnCheckTimer()
{
	TimerData timer;
	timer.interval = ConfigInfo::GetInstance()->m_nConnCheckTimerInterval;
	timer.loop = true;
	timer.callBack = [this](const TimerData &) { OnConnCheckTimer(); };

	m_ConnCheckTimerID = ITimeHelper::GetInstance()->AddTimer(timer);
}

void LogServer::StopConnCheckTimer()
{
	ITimeHelper::GetInstance()->RemoveTimer(m_ConnCheckTimerID);
}

void LogServer::OnConnCheckTimer()
{
	ConfigInfo* pConfig = ConfigInfo::GetInstance();

	if (!SessionExist(SESSION_TYPE_LOG2SS)) {
		IssueConnectionRequest(pConfig->m_sServiceServerIp, pConfig->m_nServiceServerPort, SESSION_TYPE_LOG2SS);
	}
}

void LogServer::SetLogLevel()
{
	ConfigInfo* pConfig = ConfigInfo::GetInstance();
	int32_t logLevel = (nullptr == pConfig) ? 0 : pConfig->GetInstance()->m_bLogLevel;
	ILogHelper::GetInstance()->SetLogLevel(logLevel);
	CNetManager::GetInstance()->SetLogLevel(logLevel);
}

void LogServer::LogDebugInfo(uint32_t delta)
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
