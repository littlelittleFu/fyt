#include "stdafx.h"
#include "MapServer.h"
#include "SessionFactoryMS.h"
#include "CNetManager.h"
#include "MapMgr.h"
#include "Map.h"
#include "ProtoMgr.h"
#include "Player.h"
#include "MapRoleMgr.h"
#include "MiniDumper.h"
#include "GameMall.h"
#include "LuaHost.h"


IMPL_SINGLETON(MapServer)
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

MapServer::MapServer() {
	g_CMiniDumper = new CMiniDumper(TRUE); 
}

MapServer::~MapServer() {
	if (g_CMiniDumper) {
		delete g_CMiniDumper;
	}
}

void MapServer::Start()
{
	LOG_NORMAL("map server start");
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

	if (!RegisterLuaModule()) {
		LOG_ERROR("register lua module failed");
		return;
	}

	if (!LoadLuaScripts()) {
		LOG_ERROR("load lua scripts failed");
        // 继续
	}

    if (!InitAStarPathFinder()) {
        LOG_ERROR("InitAStarPathFinder failed");
        return;
    }

	if (!MapMgr::GetInstance()->Init()) {
		LOG_ERROR("init map manager failed");
		return;
	}

	SetLogLevel();

    ADD_TRIGGER(0, trigger_system_start, "on_system_start");

	TRIGGER_EVENT(trigger_system_start);

	CreateAllMap();

    StartConnCheckTimer();

    Run();

    StopConnCheckTimer();
}

bool MapServer::InitConfig()
{
	LOG_NORMAL("init config begin");
	//init config here
	LOG_NORMAL("init config end");
	return true;
}

bool MapServer::InitNetwork()
{
	LOG_NORMAL("init network begin");
    ConfigInfo* pConfig = ConfigInfo::GetInstance();
	ISessionFactory::SetInstance(new SessionFactoryMS);
	IProtoMgr::SetInstance(new ProtoMgr);
	CNetManager::GetInstance()->Init(pConfig->m_nNetLibThreadNum);
	CNetManager::GetInstance()->SetLogFunction(LogText);
	CNetManager::GetInstance()->AddListener(pConfig->m_sListenIp, pConfig->m_nListenPort, SESSION_TYPE_MS2GS);
	CNetManager::GetInstance()->AddConnector(pConfig->m_sServiceServerIp, pConfig->m_nServiceServerPort, SESSION_TYPE_MS2SS);
	LOG_NORMAL("init network end");
	return true;
}

bool MapServer::InitTable()
{
	LOG_NORMAL("init table begin");
	const auto &cfgFolder = ConfigInfo::GetInstance()->m_sGameCfgFolderPath;
	GameCfgMgr::GetInstance()->SetGameCfgFolderPath(cfgFolder);
    GameCfgMgr::GetInstance()->LoadAllCfg();
	GameMall::GetInstance()->Init();
	LOG_NORMAL("init table end");
	return true;
}

bool MapServer::InitLuaEngine()
{
	LOG_NORMAL("init lua engine begin");
	CLuaEngineMgr()->Init();

	const auto &basePath = ConfigInfo::GetInstance()->m_sScriptFolderPath;

    auto allPath = IFileHelper::GetInstance()->GetAllFoldersInDir(basePath.c_str(), true);
    allPath.emplace(allPath.begin(), basePath);

    for (const auto &path : allPath)
        CLuaEngineMgr()->AddSearchPath(path);

	LOG_NORMAL("init lua engine end");
	return true;
}

bool MapServer::RegisterLuaModule()
{
    auto *luaScript = CLuaEngineMgr()->GetLuaScript();
    if (!luaScript) return false;

    auto *luaHost = LuaHost::GetInstance();
    if (!luaHost) return false;

    luaHost->RegisterLuaAPI(luaScript);
    LuaGlobalVar["LuaHost"] = luaHost;
	
	return true;
}

bool MapServer::LoadLuaScripts()
{
    SAFE_BEGIN;

	const auto &basePath = ConfigInfo::GetInstance()->m_sScriptFolderPath;

    auto scripts = IFileHelper::GetInstance()->GetAllFilesInDirRecursive(basePath, "*.lua");

    // 将main.lua放到最前面
    for (auto it = scripts.begin(); it != scripts.end(); ++it) {
        auto &script = *it;
        if (script.find("main.lua") == std::string::npos) continue;
        auto temp = std::move(script);
        scripts.erase(it);
        scripts.emplace_front(std::move(temp));
        break;
    }

    return CLuaEngine::GetInstance()->LoadLuaScripts(std::move(scripts));

    SAFE_END_EX(false);
}


void MapServer::RunClientScript(const char* pScriptName, const char* pContent, bool bCompress)
{
    if (!pScriptName || !pContent) return;

    MSG_BUFFER_DATA(ProtoMS_RunClientScript, req);
    req.all = 1;
    strcpy_s(req.form_name, pScriptName);
    req.comp = bCompress;

    if (bCompress) {
        uLongf nDstLen = sizeof(req.form_content);
        auto result = compress((Bytef*)req.form_content, &nDstLen, (const Bytef*)pContent, strlen(pContent));
        if (result != Z_OK) {
            LOG_ERROR("compress failed with error %d", result);
            return;
        }
        req.size = nDstLen;
    }
    else {
        strcpy_s(req.form_content, pContent);
        req.size = (uint16_t)strlen(pContent);
    }
    SendDataBySessionType(SESSION_TYPE_MS2GS, req,true);
}


bool MapServer::InitAStarPathFinder()
{
    const auto *globalCfg = sGlobalConfig.GetData();
    if (!globalCfg) return false;

    auto *pathFinder = CAStarPathFinder::GetInstance();
    if (!pathFinder) return false;

    return pathFinder->Init(globalCfg->MaxMapWidth, globalCfg->MaxMapHeight, GRID_SIZE);
}

void MapServer::Run()
{
	LOG_NORMAL("map server run");

#ifdef _WIN32
    if (WinService::GetInstance().IsRunAsService()) {
        WinService::GetInstance().SetCurrentState(SERVICE_RUNNING);
    }
#endif

    ITimeHelper::GetInstance()->CalcDeltaTime();    // 重置时间戳

    while (!NeedQuit()) {

        ITimeHelper::GetInstance()->CalcDeltaTime();
        m_Update_Delta += ITimeHelper::GetInstance()->GetDeltaTime();
        if (m_Update_Delta > 15)
        {
            int64_t costttt = 50;
            int64_t costtLog = 0;
            int64_t costtTime = 0;
            int64_t costtScheduled = 0;
            int64_t costtNet = 0;
            int64_t costtMap = 0;
            int64_t costtMapRole = 0;
            int64_t costtGloble = 0;
            auto _Delta = m_Update_Delta;
            int64_t beginstampall = GetTimeStampMillisecond();
            int64_t beginstamp = beginstampall;
            LogDebugInfo(_Delta);
            int64_t endstamp = GetTimeStampMillisecond();
            costtLog = endstamp - beginstamp;


            beginstamp = endstamp;
            ITimeHelper::GetInstance()->Update(_Delta);
            endstamp = GetTimeStampMillisecond();
            costtTime = endstamp - beginstamp;


            beginstamp = endstamp;
            IScheduledHelper::GetInstance()->Update(_Delta);
            endstamp = GetTimeStampMillisecond();
            costtScheduled = endstamp - beginstamp;
            

            beginstamp = endstamp;
            CNetManager::GetInstance()->OnUpdate(_Delta);
            endstamp = GetTimeStampMillisecond();
            costtNet = endstamp - beginstamp;
            

            beginstamp = endstamp;
            MapMgr::GetInstance()->Update(_Delta);
            endstamp = GetTimeStampMillisecond();
            costtMap = endstamp - beginstamp;
            

            beginstamp = endstamp;
            MapRoleMgr::GetInstance()->Update(_Delta);
            endstamp = GetTimeStampMillisecond();
            costtMapRole = endstamp - beginstamp;


            beginstamp = endstamp;
            Globle::GetInstance()->Update(_Delta);
            endstamp = GetTimeStampMillisecond();
            costtGloble = endstamp - beginstamp;
            beginstampall = endstamp - beginstampall;
            if (beginstampall > costttt)
            {
                LOG_ERROR(
                    "\n########################################################################\n"
                    "costtLog:%d "
                    "costtTime:%d "
                    "costtScheduled:%d "
                    "costtNet:%d "
                    "costtMap:%d "
                    "costtMapRole:%d "
                    "costtGloble:%d "
                    "all:%d\n"
                    "########################################################################",
                    costtLog, costtTime, costtScheduled, costtNet, costtMap, costtMapRole, costtGloble, beginstampall);
            }

            m_Update_Delta = 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    Term();
}

bool MapServer::NeedQuit()
{
	return m_NeedQuit;
}

void MapServer::Term()
{
    CNetManager::GetInstance()->UnInit();
}

void MapServer::StartConnCheckTimer()
{
	TimerData timer;
    timer.interval = ConfigInfo::GetInstance()->m_nConnCheckTimerInterval;
    timer.loop = true;
    timer.callBack = [this](const TimerData &) { OnConnCheckTimer(); };

    m_ConnCheckTimerID = ITimeHelper::GetInstance()->AddTimer(timer);
}

void MapServer::StopConnCheckTimer()
{
    ITimeHelper::GetInstance()->RemoveTimer(m_ConnCheckTimerID);
    m_ConnCheckTimerID = 0;
}

void MapServer::OnConnCheckTimer()
{
    ConfigInfo* pConfigInfo = ConfigInfo::GetInstance();

    if (!SessionExist(SESSION_TYPE_MS2SS)) {
        IssueConnectionRequest(pConfigInfo->m_sServiceServerIp, pConfigInfo->m_nServiceServerPort, SESSION_TYPE_MS2SS);
    }

    bool bNeedSendConfigReq = false;

    /*if (!SessionExist(SESSION_TYPE_MS2DB)) {
        if (pConfigInfo->IsDBConfigValid())
            IssueConnectionRequest(pConfigInfo->m_sDBServerIP, pConfigInfo->m_nDBServerPort, SESSION_TYPE_MS2DB);
        else
            bNeedSendConfigReq = true;
    }*/

    if (!SessionExist(SESSION_TYPE_MS2CS)) {
        if (pConfigInfo->IsCSConfigValid())
            IssueConnectionRequest(pConfigInfo->m_sCenterServerIP, pConfigInfo->m_nCenterServerPort + 2, SESSION_TYPE_MS2CS);
        else
            bNeedSendConfigReq = true;
    }

	if (!SessionExist(SESSION_TYPE_MS2LOG)) {
		if (pConfigInfo->IsLogConfigValid())
			IssueConnectionRequest(pConfigInfo->m_sLogServerIP, pConfigInfo->m_nLogServerPort + 2, SESSION_TYPE_MS2LOG);
		else
			bNeedSendConfigReq = true;
	}

    if (bNeedSendConfigReq) {
        ProtoMS_ConfigReq configReq;
        SendDataBySessionType(SESSION_TYPE_MS2SS, configReq);
    }
}

void MapServer::SetLogLevel()
{
	ConfigInfo * pConfig = ConfigInfo::GetInstance();
	int32_t logLevel = (nullptr == pConfig) ? 0 : pConfig->GetInstance()->m_bLogLevel;
	ILogHelper::GetInstance()->SetLogLevel(logLevel);
	CNetManager::GetInstance()->SetLogLevel(logLevel);
}

void MapServer::LogDebugInfo(uint32_t deltaTime)
{
    static int maxDeltaTime = 0;
    if (deltaTime > maxDeltaTime) maxDeltaTime = deltaTime;

    if (deltaTime > 1000)
        MsgCostStat::GetInstance()->StartStat();
    else
        MsgCostStat::GetInstance()->StopStat();

	static int curTime = 0;
	curTime += deltaTime;
	if (curTime < 60000) return;
	curTime = 0;

	DEBUG_DATA debugData;
	CNetManager::GetInstance()->LogDebugInfo(debugData);
    LOG_WARN(
		"\n########################################################################\n"
		"delta:%d, max_delta:%d\n"
		"player:%d/%d\n"
		"stall_dummy:%d\n"
		"monster:%d\n"
		"npc:%d\n"
        "pet:%d\n"
        "ITimeHelper:%d\n"
		"send_cache:%d send_mem:%" PRIu64 " send_peak:%d\n"
		"recv_cache:%d recv_mem:%" PRIu64 " recv_peak:%d\n"
		"idle_cache:%d idle_mem:%" PRIu64 " idle_peak:%d\n"
		"busy_cache:%d busy_mem:%" PRIu64 " busy_peak:%d\n"
		"########################################################################",
        deltaTime, maxDeltaTime,
        MapRoleMgr::GetInstance()->GetOnlinePlayerCount(),
		MapRoleMgr::GetInstance()->GetPlayerCount(),
		MapRoleMgr::GetInstance()->GetStallDummyCount(),
		MapRoleMgr::GetInstance()->GetMonsterCount(),
		MapRoleMgr::GetInstance()->GetNpcCount(),
        MapRoleMgr::GetInstance()->GetPetCount(),
        ITimeHelper::GetInstance()->GetLoopTimeNum(),
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

void MapServer::CreateAllMap()
{
	auto* mapMgr = MapMgr::GetInstance();
	if (!mapMgr) return;	
	auto &mapConfig = sMapConfig.GetNameMappings();
	for (auto& i : mapConfig)
	{
		if (i.second->MapType == EMapType::EMT_DGN)
			continue;
		mapMgr->CreateMap(i.first);
	}
}
void MapServer::SetMoveMistake(uint32_t MoveMistake) {
    m_MoveMistake = MoveMistake / 10000.0;
    if (m_MoveMistake > 0.98f)
    {
        m_MoveMistake = 0.98f;
    }
    if(m_MoveMistake < 0.85f)
        m_MoveMistake = 0.85f;
}