#include "stdafx.h"
#include "GateServer.h"
#include "SessionFactoryGS.h"
#include "CNetManager.h"
#include "CSocket.h"
#include "ProtoMgr.h"
#include "MiniDumper.h"
#include "SessionContextMgr.h"

IMPL_SINGLETON(GateServer)
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

GateServer::GateServer() {
    g_CMiniDumper = new CMiniDumper(TRUE);
}

GateServer::~GateServer() {
    if (g_CMiniDumper) {
        delete g_CMiniDumper;
    }
}

void GateServer::Start()
{
	LOG_NORMAL("gate server start");
    if (!InitConfig()) {
        LOG_ERROR("init config failed");
        return;
    }

    if (!InitNetwork()) {
        LOG_ERROR("init network failed");
        return;
    }
    StartConnCheckTimer();

    SetLogLevel();
	Run();

    StopConnCheckTimer();
}

bool GateServer::InitConfig()
{
	LOG_NORMAL("init config begin");
	LOG_NORMAL("init config end");
	return true;
}

bool GateServer::InitNetwork()
{
	LOG_NORMAL("init network begin");
    ConfigInfo* pConfig = ConfigInfo::GetInstance();

	ISessionFactory::SetInstance(new SessionFactoryGS);
	IProtoMgr::SetInstance(new ProtoMgr);
	CNetManager::GetInstance()->Init(pConfig->m_nNetLibThreadNum);
	CNetManager::GetInstance()->SetLogFunction(LogText);
    CNetManager::GetInstance()->AddListener(pConfig->m_sListenIp, pConfig->m_nListenPort, SESSION_TYPE_GS2CL, CLIENT_PROTO_DEF, true);
    CNetManager::GetInstance()->AddListener(pConfig->m_sListenIp, pConfig->m_nListenPortWS, SESSION_TYPE_GS2CL, CLIENT_PROTO_WS, true);
    CNetManager::GetInstance()->AddConnector(pConfig->m_sServiceServerIp, pConfig->m_nServiceServerPort, SESSION_TYPE_GS2SS);
	LOG_NORMAL("init network end");
	return true;
}

void GateServer::Run()
{
	LOG_NORMAL("gate server run");

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
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

    Term();
}

bool GateServer::NeedQuit()
{
	return m_NeedQuit;
}

void GateServer::Term()
{
    CNetManager::GetInstance()->UnInit();
}

void GateServer::StartConnCheckTimer()
{
    TimerData timer;
    timer.interval = ConfigInfo::GetInstance()->m_nConnCheckTimerInterval;
    timer.loop = true;
    timer.callBack = [this](const TimerData &) { OnConnCheckTimer(); };

    m_ConnCheckTimerID = ITimeHelper::GetInstance()->AddTimer(timer);
}

void GateServer::StopConnCheckTimer()
{
    ITimeHelper::GetInstance()->RemoveTimer(m_ConnCheckTimerID);
    m_ConnCheckTimerID = 0;
}

void GateServer::OnConnCheckTimer()
{
    ConfigInfo* pConfigInfo = ConfigInfo::GetInstance();

    if (!SessionExist(SESSION_TYPE_GS2SS)) {
        IssueConnectionRequest(pConfigInfo->m_sServiceServerIp, pConfigInfo->m_nServiceServerPort, SESSION_TYPE_GS2SS);
    }

    bool bNeedSendConfigReq = false;

    if (!SessionExist(SESSION_TYPE_GS2LS)) {
        if (pConfigInfo->IsLSConfigValid())
            IssueConnectionRequest(pConfigInfo->m_sLoginServerIP, pConfigInfo->m_nLoginServerPort, SESSION_TYPE_GS2LS);
        else
            bNeedSendConfigReq = true;
    }

    if (!SessionExist(SESSION_TYPE_GS2MS)) {
        if (pConfigInfo->IsMSConfigValid())
            IssueConnectionRequest(pConfigInfo->m_sMapServerIP, pConfigInfo->m_nMapServerPort, SESSION_TYPE_GS2MS);
        else
            bNeedSendConfigReq = true;
    }

    if (!SessionExist(SESSION_TYPE_GS2CS)) {
        if (pConfigInfo->IsCSConfigValid())
            IssueConnectionRequest(pConfigInfo->m_sCenterServerIP, pConfigInfo->m_nCenterServerPort, SESSION_TYPE_GS2CS);
        else
            bNeedSendConfigReq = true;
    }

    if (!SessionExist(SESSION_TYPE_GS2LOG)) {
        if (pConfigInfo->IsLogConfigValid())
            IssueConnectionRequest(pConfigInfo->m_sLogServerIP, pConfigInfo->m_nLogServerPort + 3, SESSION_TYPE_GS2LOG);
        else
            bNeedSendConfigReq = true;
    }

    if (bNeedSendConfigReq) {
        ProtoGS_ConfigReq configReq;
        SendDataBySessionType(SESSION_TYPE_GS2SS, configReq);
    }
}

void GateServer::SetLogLevel()
{
    ConfigInfo* pConfig = ConfigInfo::GetInstance();
    int32_t logLevel = (nullptr == pConfig) ? 0 : pConfig->GetInstance()->m_bLogLevel;
    ILogHelper::GetInstance()->SetLogLevel(logLevel);
    CNetManager::GetInstance()->SetLogLevel(logLevel);
}

void GateServer::LogDebugInfo(uint32_t delta)
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

    DEBUG_DATA debugData;
    CNetManager::GetInstance()->LogDebugInfo(debugData);
    LOG_NORMAL(
        "\n########################################################################\n"
        "delta:%d, max_delta:%d\n"
        "player:%d/%d\n"
        "send_cache:%d send_mem:%" PRIu64 " send_peak:%d\n"
        "recv_cache:%d recv_mem:%" PRIu64 " recv_peak:%d\n"
        "idle_cache:%d idle_mem:%" PRIu64 " idle_peak:%d\n"
        "busy_cache:%d busy_mem:%" PRIu64 " busy_peak:%d\n"
        "########################################################################",
        delta, maxDeltaTime,
        SessionContextMgr::GetInstance()->GetOnlineNum(),
        SessionContextMgr::GetInstance()->GetTotalNum(),
        debugData.sendCache, debugData.sendMem, debugData.sendPeak,
        debugData.recvCache, debugData.recvMem, debugData.recvPeak,
        debugData.buffIdleCache, debugData.buffIdleMem, debugData.buffIdlePeak,
        debugData.buffBusyCache, debugData.buffBusyMem, debugData.buffBusyPeak);


    auto sendInfo = debugData.GenSendMsgInfo();
    auto recvInfo = debugData.GenRecvMsgInfo();

    if (!sendInfo.empty() || !recvInfo.empty())
    {
        LOG_NORMAL(
            "\n----------------------------------------------------------------------"
            "\nSend cache msg info:\n%s"
            "\nRecv cache msg info:\n%s"
            "\n----------------------------------------------------------------------",
            sendInfo.c_str(),
            recvInfo.c_str());
    }

    auto info = MsgCostStat::GetInstance()->CollMsgCostInfo();
    if (!info.empty()) {
        LOG_NORMAL(
            "\n########################################################################\n"
            "%s\n"
            "########################################################################",
            info.c_str());
    }
}
