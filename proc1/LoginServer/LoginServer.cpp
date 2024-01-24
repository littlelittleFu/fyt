#include "stdafx.h"
#include "LoginServer.h"
#include "CNetManager.h"
#include "SessionFactoryLS.h"
#include "ProtoMgr.h"
#include "ThirdPartLoginMgr.h"
#include "LoginIPManager.h"
#include "MaintenanceMgr.h"

IMPL_SINGLETON(LoginServer)
LoginServer::LoginServer()
{
}

LoginServer::~LoginServer()
{
}



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

bool LoginServer::InitConfig()
{
	LOG_NORMAL("init config begin");
	//init config here
	LOG_NORMAL("init config end");
	return true;
}
bool LoginServer::InitNetwork()
{
	LOG_NORMAL("init network begin");
    ConfigInfo* pConfig = ConfigInfo::GetInstance();
	ISessionFactory::SetInstance(new SessionFactoryLS);
	IProtoMgr::SetInstance(new ProtoMgr);
	CNetManager::GetInstance()->Init(pConfig->m_nNetLibThreadNum);
	CNetManager::GetInstance()->SetLogFunction(LogText);
	CNetManager::GetInstance()->AddListener(pConfig->m_sListenIp, pConfig->m_nListenPort, SESSION_TYPE_LS2GS);
	CNetManager::GetInstance()->AddConnector(pConfig->m_sServiceServerIp, pConfig->m_nServiceServerPort, SESSION_TYPE_LS2SS);
	LOG_NORMAL("init network end");
	return true;
}

void LoginServer::Run()
{
	LOG_NORMAL("login server run");

#ifdef _WIN32
    if (WinService::GetInstance().IsRunAsService()) {
        WinService::GetInstance().SetCurrentState(SERVICE_RUNNING);
    }
#endif

    ITimeHelper::GetInstance()->CalcDeltaTime();    // ÖØÖÃÊ±¼ä´Á

    while (!NeedQuit()) {
		ITimeHelper::GetInstance()->CalcDeltaTime();
		int _Delta = ITimeHelper::GetInstance()->GetDeltaTime();
		ITimeHelper::GetInstance()->Update(_Delta);
        ThirdPartLoginMgr::GetInstance()->OnUpdate();
		CNetManager::GetInstance()->OnUpdate(_Delta);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

    Term();
}

bool LoginServer::NeedQuit()
{
	return m_NeedQuit;
}

void LoginServer::Term()
{
    ThirdPartLoginMgr::GetInstance()->Term();
    CNetManager::GetInstance()->UnInit();
}


void LoginServer::StartConnCheckTimer()
{
    TimerData timer;
    timer.interval = ConfigInfo::GetInstance()->m_nConnCheckTimerInterval;
    timer.loop = true;
    timer.callBack = [this](const TimerData &) { OnConnCheckTimer(); };

    m_ConnCheckTimerID = ITimeHelper::GetInstance()->AddTimer(timer);
}

void LoginServer::StopConnCheckTimer()
{
    ITimeHelper::GetInstance()->RemoveTimer(m_ConnCheckTimerID);
    m_ConnCheckTimerID = 0;
}

void LoginServer::OnConnCheckTimer()
{
    ConfigInfo* pConfigInfo = ConfigInfo::GetInstance();

    if (!SessionExist(SESSION_TYPE_LS2SS)) {
        IssueConnectionRequest(pConfigInfo->m_sServiceServerIp, pConfigInfo->m_nServiceServerPort, SESSION_TYPE_LS2SS);
    }

    bool bNeedSendConfigReq = false;

    if (!SessionExist(SESSION_TYPE_LS2DB)) {
        if (pConfigInfo->IsDBConfigValid())
            IssueConnectionRequest(pConfigInfo->m_sDBServerIP, pConfigInfo->m_nDBServerPort + 1, SESSION_TYPE_LS2DB);
        else
            bNeedSendConfigReq = true;
    }

    if (!SessionExist(SESSION_TYPE_LS2CS)) {
        if (pConfigInfo->IsCSConfigValid())
            IssueConnectionRequest(pConfigInfo->m_sCenterServerIP, pConfigInfo->m_nCenterServerPort + 1, SESSION_TYPE_LS2CS);
        else
            bNeedSendConfigReq = true;
    }

    if (!SessionExist(SESSION_TYPE_LS2LOG)){
        if (pConfigInfo->IsLogConfigValid())
            IssueConnectionRequest(pConfigInfo->m_sLogServerIP, pConfigInfo->m_nLogServerPort + 1, SESSION_TYPE_LS2LOG);
        else
            bNeedSendConfigReq = true;
    }

    if (bNeedSendConfigReq) {
        ProtoLS_ConfigReq configReq;
        SendDataBySessionType(SESSION_TYPE_LS2SS, configReq);
    }
}

void LoginServer::Start()
{
	LOG_NORMAL("login server start");
    if (!InitConfig()) {
        LOG_ERROR("init config failed");
        return;
    }

    if (ConfigInfo::GetInstance()->m_bInitStateMaintenance)
        MaintenanceMgr::GetInstance()->SetMaintence();

    if (!InitNetwork()) {
        LOG_ERROR("init network failed");
        return;
    }

    if (!ThirdPartLoginMgr::GetInstance()->Init()) {
        LOG_ERROR("Init login mgr failed");
        return;
    }

    //if (!LoginIPManager::GetInstance()->init())
    //{
    //    LOG_ERROR("Init login ip from http failed");
    //}

    StartConnCheckTimer();

    SetLogLevel();
	Run();

    StopConnCheckTimer();
}

void LoginServer::SetLogLevel()
{
    ConfigInfo* pConfig = ConfigInfo::GetInstance();
    int32_t logLevel = (nullptr == pConfig) ? 0 : pConfig->GetInstance()->m_bLogLevel;
    ILogHelper::GetInstance()->SetLogLevel(logLevel);
    CNetManager::GetInstance()->SetLogLevel(logLevel);
}