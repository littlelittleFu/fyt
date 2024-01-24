#include "stdafx.h"
#include "LogManager.h"

CLogManager* CLogManager::s_Instance = NULL;

CLogManager* CLogManager::GetInstance()
{
	if (s_Instance == NULL) {
		s_Instance = new CLogManager;
	}

	return s_Instance;
}

CLogManager::CLogManager()
{

}

CLogManager::~CLogManager()
{

}
bool CLogManager::InitGame()
{
	ConfigInfo* pConfig = ConfigInfo::GetInstance();
	LOG_NORMAL("connect mysql ! %s,%s", pConfig->m_sMySQLServAddr_GAME.c_str(), pConfig->m_sMySQLServUserName_GAME.c_str());
	if (!m_DBConnector_GAME.ConnDb(pConfig->m_sMySQLServAddr_GAME.c_str(), pConfig->m_sMySQLServUserName_GAME.c_str(),
		pConfig->m_sMySQLServPassword_GAME.c_str(), pConfig->m_sMySQLGameServDBName.c_str(), pConfig->m_nMySQLServPort_GAME)) {
		LOG_ERROR("connect mysql failed!");
		return false;
	}
// get version
	char buf[128] = { 0 };
	int32_t ret = 0;
	FMT2BUF(buf, "select* from {}.constant_cfg where name = '{}';", pConfig->m_sMySQLGameServDBName.c_str(), pConfig->m_sVersionKeyName.c_str());
	if (!ExecuteSQL(buf, ret,true))
	{
		LOG_ERROR("select version failed!");
		return false;
	}
	LOG_ERROR("select version suc!");
	int32_t num = m_DBConnector_GAME.GetQueryRowNum();
	if (num != 1)
	{
		LOG_ERROR("no version field exists!");
		return false;
	}
	m_DBConnector_GAME.GetQueryFieldData("value", m_msversion);
	std::replace(m_msversion.begin(), m_msversion.end(), '.', 'v');
	m_msversion = "_" + m_msversion;
	return true;
}

bool CLogManager::Init(uint8_t tmpIdx)
{
	ConfigInfo* pConfig = ConfigInfo::GetInstance();
	LOG_NORMAL("connect mysql ! %s,%s", pConfig->m_sMySQLServAddr.c_str(), pConfig->m_sMySQLServUserName.c_str());
	if (!m_DBConnector[tmpIdx].ConnDb(pConfig->m_sMySQLServAddr.c_str(), pConfig->m_sMySQLServUserName.c_str(),
		pConfig->m_sMySQLServPassword.c_str(), pConfig->m_sMySQLServDBName.c_str(), pConfig->m_nMySQLServPort)) {
		LOG_ERROR("connect mysql failed!");
		return false;
	}
	return true;
}

void CLogManager::SetSwitchLogDB(std::string ipPort)
{
	LOG_NORMAL("准备切换日志数据库!");
	std::vector<std::string> vec= str_split(ipPort, " ");
	if (vec.size() == 2)
	{
		m_switchIp = vec[0];
		m_switchPort = atoi(vec[1].c_str());
	}
	else
	{
		static std::string path = IFileHelper::GetInstance()->GetCurWorkPath() + "switchlogdb.ini";
		inifile::IniFile ini;
		if (ini.Load(path) != 0) return;
		ini.GetStringValueOrDefault("SwitchLogDB", "SwitchMySQLServAddr", &m_switchIp, "127.0.0.1");
		ini.GetIntValueOrDefault("SwitchLogDB", "SwitchMySQLServPort", &m_switchPort, 3306);
	}
	m_switch = true;
}

void CLogManager::CheckSwitchLogDB()
{
	if (m_switch)
	{
		m_switch = false;
		int32_t ret = 0;
		// 是当前连接
		if (m_DBConnector[m_idx].GetDbIP() == m_switchIp && m_DBConnector[m_idx].GetDbPort() == m_switchPort
			&& !m_DBConnector[m_idx].ExecQuery("select 1"))
		{
			LOG_NORMAL("切换日志数据库成功! Ip:%s Port:%d", m_switchIp.c_str(), m_switchPort);
			return;
		}
		// 已有的连接
		uint8_t tmpIdx = (m_idx + 1) % DB_CONNECT_COUNT;
		if (m_DBConnector[tmpIdx].GetDbIP() == m_switchIp && m_DBConnector[tmpIdx].GetDbPort() == m_switchPort
			&& !m_DBConnector[tmpIdx].ExecQuery("select 1"))
		{
			m_idx = tmpIdx;
			LOG_NORMAL("切换日志数据库成功! Ip:%s Port:%d", m_switchIp.c_str(), m_switchPort);
			return;
		}
		// 切换
		ConfigInfo* pConfig = ConfigInfo::GetInstance();
		if (!pConfig)
		{
			LOG_ERROR("获取数据库配置信息错误!");
			return;
		}
		std::string ip = pConfig->m_sMySQLServAddr;
		uint32_t port = pConfig->m_nMySQLServPort;
		pConfig->m_sMySQLServAddr = m_switchIp;
		pConfig->m_nMySQLServPort = m_switchPort;
		if (!Init(tmpIdx))
		{
			pConfig->m_sMySQLServAddr = ip;
			pConfig->m_nMySQLServPort = port;
			LOG_ERROR("切换日志数据库连时接失败! Ip:%s Port:%d", m_switchIp.c_str(), m_switchPort);
			return;
		}
		//m_DBConnector[m_idx].Clear();// 等下次切换再断
		m_idx = tmpIdx;
		LOG_NORMAL("切换日志数据库成功! Ip:%s Port:%d", m_switchIp.c_str(), m_switchPort);
	}
}

void CLogManager::Logging(const ProtoLog_LoggingReq& req)
{
    MsgCostStat::GetInstance()->BeginHandleMsg();

	switch (req.logType)
	{
	case log_type_currency_change: return HandleCurrentChange(req);
	case log_type_item_update: return HandleItemUpdate(req);
	case log_type_login_out: return HandleLoginOut(req);
	case log_type_entery_exit_map: return HandleEnteryExitMap(req);
	case log_type_drop_item: return HandleDropItem(req);
	case log_type_gm_cmd: return HandleGmCmd(req);
	case log_type_online_num: return HandleOnlineNumCmd(req);
	case log_type_trade_data: return HandleTradeDataCmd(req);
	case log_type_mail_info: return HandleMailInfoCmd(req);
	case log_type_death_record: return HandleDeathRecordCmd(req);
	case log_type_activity_data: return HandleActivityDataCmd(req);
	case log_type_reward_data: return HandleRewardDataCmd(req);
	case log_type_giftpack_data: return HandleGiftpackDataCmd(req);
	case log_type_recovery_data: return HandleRecoveryDataCmd(req);
	case log_type_db_exesql: return HandleDBSqlCmd(req);
	case log_type_item_dyn_attr: return HandleItemDynAttr(req);
	case log_type_item_cust_var: return HandleItemCustVar(req);
	default:break;
	}

    MsgCostStat::GetInstance()->EndHandleMsg(req.logType);
}
// 货币积分变化(张/天)
void CLogManager::HandleCurrentChange(const ProtoLog_LoggingReq& req)
{
	LogCurrencyChange* lc = nullptr;
	req >> lc;
	if (lc == nullptr) return;

	std::string insertSql = "";
	static char buf[10240] = { 0 };
	std::string curTime = ITimeHelper::GetInstance()->ConvertTimeToString(MS2S(req.timestamp), DTFMTA3);
	std::string tableName = std::string(CURRENCY_CHANGE_TEMPLATE_TABLE_NAME) + curTime.substr(0, 8) + m_msversion;

	FMT2BUF(buf,
		"insert into {} (server_ip, server_port, server_type, server_id, role_guid, change_type,"
		"before_value, change_value, after_value, reason_type, des, time)"
		"values ('{}', {}, {}, {}, {}, {},"
		"{}, {},  {},  {}, '{}', '{}');",//FROM_UNIXTIME({})
		ESCA2UTF8(tableName), ESCA2UTF8(req.serverIp), req.serverPort, req.serverType, req.serverId, lc->roleGuid, lc->type,
		lc->before, lc->change, lc->after, lc->reasonType, ESCA2UTF8(lc->desc), ESCA2UTF8(std::move(curTime)));
	insertSql += buf;memset(buf, 0, sizeof(buf));

	ExecuteLogSql(insertSql, tableName, std::string(CURRENCY_CHANGE_TEMPLATE_TABLE_NAME));
}
// 物品更新(张/天)
void CLogManager::HandleItemUpdate(const ProtoLog_LoggingReq& req)
{
	LogItemUpdate* lc = nullptr;
	req >> lc;
	if (lc == nullptr) return;

	std::string insertSql = "";
	static char buf[10240] = { 0 };
	std::string curTime = ITimeHelper::GetInstance()->ConvertTimeToString(MS2S(req.timestamp), DTFMTA3);
	std::string tableName = std::string(ITEM_UPDATE_TEMPLATE_TABLE_NAME) + curTime.substr(0, 8) + m_msversion;

	FMT2BUF(buf,
		"insert into {} (server_ip, server_port, server_type, server_id, role_guid, item_guid, item_name, item_id, item_site,"
		"prop_type, before_value, change_value, after_value, reason_type, des, time)"
		"values ('{}', {}, {}, {}, {}, {}, '{}', {}, {},"
		"{}, {}, {}, {}, {}, '{}', '{}');",//FROM_UNIXTIME({})
		ESCA2UTF8(tableName), ESCA2UTF8(req.serverIp), req.serverPort, req.serverType, req.serverId, lc->roleGuid, lc->itemGuid, ESCA2UTF8(lc->itemName), lc->itemId, lc->itemSite,
		lc->prop, lc->before, lc->change, lc->after, lc->reasonType, ESCA2UTF8(lc->desc), ESCA2UTF8(std::move(curTime)));
	insertSql += buf; memset(buf, 0, sizeof(buf));

	ExecuteLogSql(insertSql, tableName, std::string(ITEM_UPDATE_TEMPLATE_TABLE_NAME));
}
// 登录登出(张/月)
void CLogManager::HandleLoginOut(const ProtoLog_LoggingReq& req)
{
	LogLoginOut* lc = nullptr;
	req >> lc;
	if (lc == nullptr) return;

	std::string insertSql = "";
	static char buf[10240] = { 0 };
	std::string curTime = ITimeHelper::GetInstance()->ConvertTimeToString(MS2S(req.timestamp), DTFMTA3);
	std::string tableName = std::string(LOGIN_OUT_TEMPLATE_TABLE_NAME) + curTime.substr(0, 6) + m_msversion;

	FMT2BUF(buf,
		"insert into {} (server_ip, server_port, server_type, server_id, client_ip, client_hwid, player_id,"
		"type, des, time)"
		"values ('{}', {}, {}, {}, '{}', '{}', {},"
		"{}, '{}', '{}');",//FROM_UNIXTIME({})
		ESCA2UTF8(tableName), ESCA2UTF8(req.serverIp), req.serverPort, req.serverType, req.serverId, 
		ESCA2UTF8(lc->clientIp), ESCA2UTF8(lc->clientHwid), lc->playerId,
		lc->type, ESCA2UTF8(lc->desc), ESCA2UTF8(std::move(curTime)));
	insertSql += buf; memset(buf, 0, sizeof(buf));

	ExecuteLogSql(insertSql, tableName, std::string(LOGIN_OUT_TEMPLATE_TABLE_NAME));
}
// 进出地图(张/月)
void CLogManager::HandleEnteryExitMap(const ProtoLog_LoggingReq& req)
{
	LogEnteryExitMap* lc = nullptr;
	req >> lc;
	if (lc == nullptr) return;

	std::string insertSql = "";
	static char buf[10240] = { 0 };
	std::string curTime = ITimeHelper::GetInstance()->ConvertTimeToString(MS2S(req.timestamp), DTFMTA3);
	std::string tableName = std::string(ENTERY_EXIT_MAP_TEMPLATE_TABLE_NAME) + curTime.substr(0, 6) + m_msversion;

	FMT2BUF(buf,
		"insert into {} (server_ip, server_port, server_type, server_id, role_guid,"
		"from_mapid, from_maptype, to_mapid, to_maptype, duration, des, tickets_info, time)"
		"values ('{}', {}, {}, {}, {},"
		"{}, {}, {}, {}, {}, '{}', '{}', '{}');",//FROM_UNIXTIME({})
		ESCA2UTF8(tableName), ESCA2UTF8(req.serverIp), req.serverPort, req.serverType, req.serverId, lc->roleGuid,
		lc->fromMapId, lc->fromMapType, lc->toMapId, lc->toMapType, lc->duration, ESCA2UTF8(lc->desc), ESCA2UTF8(lc->ticks), ESCA2UTF8(std::move(curTime)));
	insertSql += buf; memset(buf, 0, sizeof(buf));

	ExecuteLogSql(insertSql, tableName, std::string(ENTERY_EXIT_MAP_TEMPLATE_TABLE_NAME));
}
// 物品掉落(张/月)
void CLogManager::HandleDropItem(const ProtoLog_LoggingReq& req)
{
	LogDropItem* lc = nullptr;
	req >> lc;
	if (lc == nullptr) return;

	std::string insertSql = "";
	static char buf[10240] = { 0 };
	std::string curTime = ITimeHelper::GetInstance()->ConvertTimeToString(MS2S(req.timestamp), DTFMTA3);
	std::string tableName = std::string(DROP_ITEM_TEMPLATE_TABLE_NAME) + curTime.substr(0, 8) + m_msversion;

	FMT2BUF(buf,
		"insert into {} (server_ip, server_port, server_type, server_id, map_id, map_type, role_guid,"
		"obj_guid, obj_maintype, obj_subtype, item_type, item_name, item_id, item_amount, des, time)"
		"values ('{}', {}, {}, {}, {}, {}, {},"
		"{}, {}, {}, {}, '{}', {}, {}, '{}', '{}');",//FROM_UNIXTIME({})
		ESCA2UTF8(tableName), ESCA2UTF8(req.serverIp), req.serverPort, req.serverType, req.serverId, lc->mapId, lc->mapType, lc->roleGuid,
		lc->objGuid, lc->objMainType, lc->objSubType, lc->itemType, ESCA2UTF8(lc->itemName), lc->itemId, lc->amount, ESCA2UTF8(lc->desc), ESCA2UTF8(std::move(curTime)));
	insertSql += buf; memset(buf, 0, sizeof(buf));

	ExecuteLogSql(insertSql, tableName, std::string(DROP_ITEM_TEMPLATE_TABLE_NAME));
}
// gm指令(张/月)
void CLogManager::HandleGmCmd(const ProtoLog_LoggingReq& req)
{
	LogGmCmd* lc = nullptr;
	req >> lc;
	if (lc == nullptr) return;

	std::string insertSql = "";
	static char buf[10240] = { 0 };
	std::string curTime = ITimeHelper::GetInstance()->ConvertTimeToString(MS2S(req.timestamp), DTFMTA3);
	std::string tableName = std::string(GM_CMD_TEMPLATE_TABLE_NAME) + curTime.substr(0, 6) + m_msversion;

	FMT2BUF(buf,
		"insert into {} (server_ip, server_port, server_type, server_id, role_guid,"
		"gm_level, gm_func, cmd_type, cmd_content, des, time)"
		"values ('{}', {}, {}, {}, {},"
		"{}, '{}', '{}', '{}', '{}', '{}');",//FROM_UNIXTIME({})
		ESCA2UTF8(tableName), ESCA2UTF8(req.serverIp), req.serverPort, req.serverType, req.serverId, lc->roleGuid,
		lc->gmLevel, lc->gmFunc, lc->gmCmdType, lc->gmCmd, ESCA2UTF8(lc->desc), ESCA2UTF8(std::move(curTime)));
	insertSql += buf; memset(buf, 0, sizeof(buf));

	ExecuteLogSql(insertSql, tableName, std::string(GM_CMD_TEMPLATE_TABLE_NAME));
	if (_stricmp(lc->gmCmdType, SWITCH_LOG_DB_CMD) == 0)
	{
		SetSwitchLogDB(std::string(lc->gmCmd));
	}
}
// 在线人数(张/月)
void CLogManager::HandleOnlineNumCmd(const ProtoLog_LoggingReq& req)
{
	LogOnlineNum* lc = nullptr;
	req >> lc;
	if (lc == nullptr) return;

	std::string insertSql = "";
	static char buf[10240] = { 0 };
	std::string curTime = ITimeHelper::GetInstance()->ConvertTimeToString(MS2S(req.timestamp), DTFMTA3);
	std::string tableName = std::string(ONLINE_NUM_TEMPLATE_TABLE_NAME) + curTime.substr(0, 6) + m_msversion;

	FMT2BUF(buf,
		"insert into {} (server_ip, server_port, server_type, server_id,"
		"num, des, time)"
		"values ('{}', {}, {}, {},"
		"{}, '{}', '{}');",//FROM_UNIXTIME({})
		ESCA2UTF8(tableName), ESCA2UTF8(req.serverIp), req.serverPort, req.serverType, req.serverId,
		lc->num, ESCA2UTF8(lc->desc), ESCA2UTF8(std::move(curTime)));
	insertSql += buf; memset(buf, 0, sizeof(buf));

	ExecuteLogSql(insertSql, tableName, std::string(ONLINE_NUM_TEMPLATE_TABLE_NAME));
}
// 寄售行交易记录(张/月)
void CLogManager::HandleTradeDataCmd(const ProtoLog_LoggingReq& req)
{
	ConfigInfo* pConfig = ConfigInfo::GetInstance();
	if (!pConfig)
	{
		LOG_ERROR("获取数据库配置信息错误!");
		return;
	}

	LogTradeData* lc = nullptr;
	req >> lc;
	if (lc == nullptr) return;

	int32_t ret = 0;
	static char buf[10240] = { 0 };
	std::string curTime = ITimeHelper::GetInstance()->ConvertTimeToString(lc->timestamp, DTFMTA3);
	std::string tTime = ITimeHelper::GetInstance()->ConvertTimeToString(lc->tradeTimestamp, DTFMTA3);
	//std::string tableName = std::string(TRADE_DATA_TEMPLATE_TABLE_NAME) + curTime.substr(0, 6);

	static std::string tb[2] =
	{
		pConfig->m_sMySQLGameServDBName + "." + TRADE_DATA_LOG_TEMPLATE_TABLE_NAME,		// game库使用一张表
		std::string(TRADE_DATA_TEMPLATE_TABLE_NAME) + curTime.substr(0, 6)				// log还是分表
	};
	for (int i = 0; i < 2; ++i)
	{
		std::string insertSql = "";
		FMT2BUF(buf,
			"insert into {} (server_ip, server_port, server_type, server_id, trade_id, trade_type, value_type,"
			"orig_item_guid, item_guid, item_name, item_id, item_value, item_num, buyer_guid, seller_guid, des, time, tTime)"
			"values ('{}', {}, {}, {}, {}, {}, {}, "
			"{}, {}, '{}', {}, {}, {}, {}, {}, '{}', '{}', '{}');",//FROM_UNIXTIME({})
			ESCA2UTF8(tb[i]), ESCA2UTF8(req.serverIp), req.serverPort, req.serverType, req.serverId, lc->tradeId, lc->tradeType, lc->valueType,
			lc->orgItemGuid, lc->itemGuid, ESCA2UTF8(lc->itemName), lc->itemId, lc->itemValue, lc->itemNum, lc->buyerGuid, lc->sellerGuid, ESCA2UTF8(lc->desc), ESCA2UTF8(curTime), ESCA2UTF8(tTime));
		insertSql += buf; memset(buf, 0, sizeof(buf));

		if (i==0)
		{
			ExecuteLogSql(insertSql, tb[i], std::string(TRADE_DATA_TEMPLATE_TABLE_NAME),true);
		}
		else
		{
			ExecuteLogSql(insertSql, tb[i], std::string(TRADE_DATA_TEMPLATE_TABLE_NAME));
		}
	}

	static std::vector<std::string> tab[2] =
	{
		{ 
			pConfig->m_sMySQLGameServDBName + "." + TRADE_ITEM_LOG_TEMPLATE_TABLE_NAME, 
			pConfig->m_sMySQLGameServDBName + "." + TRADE_ITEM_CUST_VAR_LOG_TEMPLATE_TABLE_NAME, 
			pConfig->m_sMySQLGameServDBName + "." + TRADE_ITEM_DYN_ATTR_LOG_TEMPLATE_TABLE_NAME
		},{
			TRADE_ITEM_TEMPLATE_TABLE_NAME,
			TRADE_ITEM_CUST_VAR_TEMPLATE_TABLE_NAME,
			TRADE_ITEM_DYN_ATTR_TEMPLATE_TABLE_NAME
		}
	};
	std::string sql = "";
	for (int i = 0;i < 2;++ i)
	{
		FMT2BUF(buf, "insert into {} select * from {}.item where guid = {};",
			ESCA2UTF8(tab[i][0]), pConfig->m_sMySQLGameServDBName.c_str(), lc->itemGuid);
		sql += buf; memset(buf, 0, sizeof(buf));

		FMT2BUF(buf, "insert into {} select * from {}.item_cust_var where belong = {};",
			ESCA2UTF8(tab[i][1]), pConfig->m_sMySQLGameServDBName.c_str(), lc->itemGuid);
		sql += buf; memset(buf, 0, sizeof(buf));

		FMT2BUF(buf, "insert into {} select * from {}.item_dyn_attr where item = {};",
			ESCA2UTF8(tab[i][2]), pConfig->m_sMySQLGameServDBName.c_str(), lc->itemGuid);
		sql += buf; memset(buf, 0, sizeof(buf));
		if (i==0)
		{
			ExecuteSQL(sql.c_str(), ret, true);
			sql = "";
		}
	}
	ExecuteSQL(sql.c_str(), ret);

	
}
// 邮件记录(张/月)
void CLogManager::HandleMailInfoCmd(const ProtoLog_LoggingReq& req)
{
	LogMailInfo* lc = nullptr;
	req >> lc;
	if (lc == nullptr) return;
	ConfigInfo* pConfig = ConfigInfo::GetInstance();
	if (!pConfig)
	{
		LOG_ERROR("获取数据库配置信息错误!");
		return;
	}

	std::string sql = "";
	static char buf[10240] = { 0 };
	// 得按照邮件发送的时间
	std::string curTime = ITimeHelper::GetInstance()->ConvertTimeToString(MS2S(req.timestamp), DTFMTA2);
	std::string sendTime = "";
	std::string tableName = "";
	for (int32_t i = 0; i < lc->mailNum;++ i)
	{
		sendTime = ITimeHelper::GetInstance()->ConvertTimeToString(GUID_TIME_PART(lc->mailStatus[i].mailid), DTFMTA3);
		tableName = std::string(MAIL_INFO_TEMPLATE_TABLE_NAME) + sendTime.substr(0, 6);
		// 删除
		if (LogMailInfo::LogMailUpdateFlag::LMUF_DELETE == lc->updateFlag)
		{
			FMT2BUF(buf, "update {} set update_flag = {} where mail_id = {};", ESCA2UTF8(tableName), lc->updateFlag, lc->mailStatus[i].mailid);
		}
		else if (LogMailInfo::LogMailUpdateFlag::LMUF_INSERT == lc->updateFlag)
		{
			FMT2BUF(buf,
				"select playerguid, mailID, title, text, currency_info, status, item_info, addition_item_num, send_time, type, sendername, cpy_guid "
				"from {}.mails_list_info where mailID = {};",
				pConfig->m_sMySQLGameServDBName.c_str(), lc->mailStatus[i].mailid);

			int32_t ret;
			if (!ExecuteSQL(buf, ret, true)) {
				LOG_ERROR("Insert Log Mail Failed! MailID:%llu sqlErr:%u", lc->mailStatus[i].mailid, ret); 
				continue;
			}

			int num = m_DBConnector_GAME.GetQueryRowNum();
			if (!num)continue;

			uint64_t playerGUID = 0, cpyGUID = 0;
			std::string title, text, currency_info, item_info, sendername;
			uint8_t addition_item_num = 0;
			uint32_t status = 0, send_time = 0, type = 0;

			try
			{
				m_DBConnector_GAME.GetQueryFieldData("playerguid", playerGUID);
				m_DBConnector_GAME.GetQueryFieldData("title", title);
				m_DBConnector_GAME.GetQueryFieldData("text", text);
				m_DBConnector_GAME.GetQueryFieldData("currency_info", currency_info);
				m_DBConnector_GAME.GetQueryFieldData("status", status);
				m_DBConnector_GAME.GetQueryFieldData("addition_item_num", addition_item_num);
				m_DBConnector_GAME.GetQueryFieldData("item_info", item_info);
			    m_DBConnector_GAME.GetQueryFieldData("send_time", send_time);
				m_DBConnector_GAME.GetQueryFieldData("type", type);
				m_DBConnector_GAME.GetQueryFieldData("sendername", sendername);
				//m_DBConnector_GAME.GetQueryFieldData("cpy_guid", cpyGUID);

			}
			catch (...) {
				LOG_ERROR("Exception occurred");
			}

			memset(buf, 0, _countof(buf));

			FMT2BUF(buf,
				"insert into {} (server_ip, server_port, server_type, server_id, "
				"role_guid, mail_id, title, text, currency_info, status, item_info, addition_item_num, send_time, type, sendername, "
				"des, time, update_flag) values('{}', {}, {}, {},"
				"{}, {}, '{}', '{}' ,'{}', {}, '{}', {}, {}, {}, '{}',"
			    "'{}', '{}', {});",
				ESCA2UTF8(tableName), ESCA2UTF8(req.serverIp), req.serverPort, req.serverType, req.serverId,
				playerGUID, lc->mailStatus[i].mailid, ESCA2UTF8(title), ESCA2UTF8(text), ESCA2UTF8(currency_info), status,
				ESCA2UTF8(item_info), addition_item_num, send_time, type, ESCA2UTF8(sendername),
				ESCA2UTF8(lc->desc), ESCA2UTF8(curTime), lc->updateFlag);
		}
		else if (LogMailInfo::LogMailUpdateFlag::LMUF_UPDATE == lc->updateFlag)
		{
			FMT2BUF(buf, "update {} set status = {}, update_flag = {} where mail_id = {};", ESCA2UTF8(tableName), lc->mailStatus[i].status, lc->updateFlag, lc->mailStatus[i].mailid);
		}
		sql += buf; memset(buf, 0, sizeof(buf));
	}
	TimerData timer;
	timer.interval = 3000;
	timer.loop = false;
	timer.callBack = [sql, tableName,this](const TimerData&) {
		ExecuteLogSql(sql, tableName, std::string(MAIL_INFO_TEMPLATE_TABLE_NAME));
	};
	ITimeHelper::GetInstance()->AddTimer(timer);
	
}
// 死亡记录(张/月)
void CLogManager::HandleDeathRecordCmd(const ProtoLog_LoggingReq& req)
{
	LogDeathRecord* lc = nullptr;
	req >> lc;
	if (lc == nullptr) return;

	std::string insertSql = "";
	static char buf[10240] = { 0 };
	std::string curTime = ITimeHelper::GetInstance()->ConvertTimeToString(MS2S(req.timestamp), DTFMTA3);
	std::string tableName = std::string(DEATH_RECORD_TEMPLATE_TABLE_NAME) + curTime.substr(0, 6) + m_msversion;

	FMT2BUF(buf,
		"insert into {} (server_ip, server_port, server_type, server_id, role_guid1,"
		"role_level1, map_id, map_type, role_guid2, role_level2, role_type, role_stype, des, time)"
		"values ('{}', {}, {}, {}, {},"
		"{}, {}, {}, {}, {}, {}, {}, '{}', '{}');",//FROM_UNIXTIME({})
		ESCA2UTF8(tableName), ESCA2UTF8(req.serverIp), req.serverPort, req.serverType, req.serverId, lc->roleGuid1,
		lc->roleLevel1, lc->mapId, lc->mapType, lc->roleGuid2, lc->roleLevel2, lc->roleType, lc->roleSType,  ESCA2UTF8(lc->desc), ESCA2UTF8(std::move(curTime)));
	insertSql += buf; memset(buf, 0, sizeof(buf));

	ExecuteLogSql(insertSql, tableName, std::string(DEATH_RECORD_TEMPLATE_TABLE_NAME));
}
// 活动(张/月)
void CLogManager::HandleActivityDataCmd(const ProtoLog_LoggingReq& req)
{
	LogActivityData* lc = nullptr;
	req >> lc;
	if (lc == nullptr) return;

	std::string insertSql = "";
	static char buf[10240] = { 0 };
	std::string curTime = ITimeHelper::GetInstance()->ConvertTimeToString(MS2S(req.timestamp), DTFMTA3);
	std::string tableName = std::string(ACTIVITY_DATA_TEMPLATE_TABLE_NAME) + curTime.substr(0, 6) + m_msversion;

	FMT2BUF(buf,
		"insert into {} (server_ip, server_port, server_type, server_id, activity_name,"
		"reward_name, activity_guid, role_guid, item_keyname, item_num, des, time)"
		"values ('{}', {}, {}, {}, '{}',"
		"'{}', {}, {}, '{}', {}, '{}', '{}');",//FROM_UNIXTIME({})
		ESCA2UTF8(tableName), ESCA2UTF8(req.serverIp), req.serverPort, req.serverType, req.serverId, ESCA2UTF8(lc->activityName),
		ESCA2UTF8(lc->rewardName), lc->activityGuid, lc->roleGuid, ESCA2UTF8(lc->itemKeyname), lc->itemNum, ESCA2UTF8(lc->desc), ESCA2UTF8(std::move(curTime)));
	insertSql += buf; memset(buf, 0, sizeof(buf));

	ExecuteLogSql(insertSql, tableName, std::string(ACTIVITY_DATA_TEMPLATE_TABLE_NAME));
}
// 奖励领取(张/月)
void CLogManager::HandleRewardDataCmd(const ProtoLog_LoggingReq& req)
{
	LogRewardData* lc = nullptr;
	req >> lc;
	if (lc == nullptr) return;

	std::string insertSql = "";
	static char buf[10240] = { 0 };
	std::string curTime = ITimeHelper::GetInstance()->ConvertTimeToString(MS2S(req.timestamp), DTFMTA3);
	std::string tableName = std::string(REWARD_DATA_TEMPLATE_TABLE_NAME) + curTime.substr(0, 6) + m_msversion;

	FMT2BUF(buf,
		"insert into {} (server_ip, server_port, server_type, server_id,"
		"reward_name, reward_guid, role_guid, item_keyname, item_num, des, time)"
		"values ('{}', {}, {}, {},"
		"'{}', {}, {}, '{}', {}, '{}', '{}');",//FROM_UNIXTIME({})
		ESCA2UTF8(tableName), ESCA2UTF8(req.serverIp), req.serverPort, req.serverType, req.serverId,
		ESCA2UTF8(lc->rewardName), lc->rewardGuid, lc->roleGuid, ESCA2UTF8(lc->itemKeyname), lc->itemNum, ESCA2UTF8(lc->desc), ESCA2UTF8(std::move(curTime)));
	insertSql += buf; memset(buf, 0, sizeof(buf));

	ExecuteLogSql(insertSql, tableName, std::string(REWARD_DATA_TEMPLATE_TABLE_NAME));
}
// 礼包(张/月)
void CLogManager::HandleGiftpackDataCmd(const ProtoLog_LoggingReq& req)
{
	LogGiftPackData* lc = nullptr;
	req >> lc;
	if (lc == nullptr) return;

	std::string insertSql = "";
	static char buf[10240] = { 0 };
	std::string curTime = ITimeHelper::GetInstance()->ConvertTimeToString(MS2S(req.timestamp), DTFMTA3);
	std::string tableName = std::string(GIFTPACK_DATA_TEMPLATE_TABLE_NAME) + curTime.substr(0, 6) + m_msversion;

	FMT2BUF(buf,
		"insert into {} (server_ip, server_port, server_type, server_id,"
		"gift_name, gift_guid, role_guid, item_keyname, item_num, des, time)"
		"values ('{}', {}, {}, {},"
		"'{}', {}, {}, '{}', {}, '{}', '{}');",//FROM_UNIXTIME({})
		ESCA2UTF8(tableName), ESCA2UTF8(req.serverIp), req.serverPort, req.serverType, req.serverId,
		ESCA2UTF8(lc->giftName), lc->giftGuid, lc->roleGuid, ESCA2UTF8(lc->itemKeyname), lc->itemNum, ESCA2UTF8(lc->desc), ESCA2UTF8(std::move(curTime)));
	insertSql += buf; memset(buf, 0, sizeof(buf));

	ExecuteLogSql(insertSql, tableName, std::string(GIFTPACK_DATA_TEMPLATE_TABLE_NAME));
}
// 回收(张/月)
void CLogManager::HandleRecoveryDataCmd(const ProtoLog_LoggingReq& req)
{
	LogRecoveryData* lc = nullptr;
	req >> lc;
	if (lc == nullptr) return;

	std::string insertSql = "";
	static char buf[10240] = { 0 };
	std::string curTime = ITimeHelper::GetInstance()->ConvertTimeToString(MS2S(req.timestamp), DTFMTA3);
	std::string tableName = std::string(RECOVERY_DATA_TEMPLATE_TABLE_NAME) + curTime.substr(0, 6) + m_msversion;

	FMT2BUF(buf,
		"insert into {} (server_ip, server_port, server_type, server_id,"
		"recovery_guid, role_guid, item_keyname, item_num, des, time)"
		"values ('{}', {}, {}, {},"
		"{}, {}, '{}', {}, '{}', '{}');",//FROM_UNIXTIME({})
		ESCA2UTF8(tableName), ESCA2UTF8(req.serverIp), req.serverPort, req.serverType, req.serverId,
		lc->recoveryGuid, lc->roleGuid, ESCA2UTF8(lc->itemKeyname), lc->itemNum, ESCA2UTF8(lc->desc), ESCA2UTF8(std::move(curTime)));
	insertSql += buf; memset(buf, 0, sizeof(buf));

	ExecuteLogSql(insertSql, tableName, std::string(RECOVERY_DATA_TEMPLATE_TABLE_NAME));
}
// db sql(张/月)
void CLogManager::HandleDBSqlCmd(const ProtoLog_LoggingReq& req)
{
	static string sqlStr("");
	LogDBSql* lc = nullptr;
	req >> lc;
	if (lc == nullptr) return;

	sqlStr += lc->dbSqlStr;
	if (!lc->beLastPack) return;

	std::string insertSql = "";
	static char buf[65536] = { 0 };
	std::string curTime = ITimeHelper::GetInstance()->ConvertTimeToString(MS2S(req.timestamp), DTFMTA3);
	std::string tableName = std::string(DB_SQL_TEMPLATE_TABLE_NAME) + curTime.substr(0, 6) + m_msversion;
	
	FMT2BUF(buf,
		"insert into {} (server_ip, server_port, server_type, server_id,"
		"sql_content, result, time)"
		"values ('{}', {}, {}, {},"
		"'{}', {}, '{}');",//FROM_UNIXTIME({})
		ESCA2UTF8(tableName), ESCA2UTF8(req.serverIp), req.serverPort, req.serverType, req.serverId,
		ESCA2UTF8(sqlStr.c_str()), lc->result, ESCA2UTF8(std::move(curTime)));
	insertSql += buf; memset(buf, 0, sizeof(buf));

	ExecuteLogSql(insertSql, tableName, std::string(DB_SQL_TEMPLATE_TABLE_NAME));

	sqlStr = "";
}
// ItemDynAttr(张/月)
void CLogManager::HandleItemDynAttr(const ProtoLog_LoggingReq& req)
{
	LogItemDynAttr* lc = nullptr;
	req >> lc;
	if (lc == nullptr) return;

	std::string insertSql = "";
	static char buf[10240] = { 0 };
	std::string curTime = ITimeHelper::GetInstance()->ConvertTimeToString(MS2S(req.timestamp), DTFMTA3);
	std::string tableName = std::string(ITEM_DYN_ATTR_UPDATE_TEMPLATE_TABLE_NAME) + curTime.substr(0, 6) + m_msversion;

	FMT2BUF(buf,
		"insert into {} (server_ip, server_port, server_type, server_id,"
		"item, idx, attr, value, time)"
		"values ('{}', {}, {}, {},"
		"{}, {}, {}, {}, '{}');",//FROM_UNIXTIME({})
		ESCA2UTF8(tableName), ESCA2UTF8(req.serverIp), req.serverPort, req.serverType, req.serverId,
		lc->guid, lc->index, lc->attr, lc->value, ESCA2UTF8(std::move(curTime)));
	insertSql += buf; memset(buf, 0, sizeof(buf));

	ExecuteLogSql(insertSql, tableName, std::string(ITEM_DYN_ATTR_UPDATE_TEMPLATE_TABLE_NAME));
}
// ItemCustVar(张/月)
void CLogManager::HandleItemCustVar(const ProtoLog_LoggingReq& req)
{
	LogItemCustVar* lc = nullptr;
	req >> lc;
	if (lc == nullptr) return;

	std::string insertSql = "";
	static char buf[10240] = { 0 };
	std::string curTime = ITimeHelper::GetInstance()->ConvertTimeToString(MS2S(req.timestamp), DTFMTA3);
	std::string tableName = std::string(ITEM_CUST_VAR_UPDATE_TEMPLATE_TABLE_NAME) + curTime.substr(0, 6) + m_msversion;

	FMT2BUF(buf,
		"insert into {} (server_ip, server_port, server_type, server_id,"
		"belong, name, value, type, expire, time)"
		"values ('{}', {}, {}, {},"
		"{}, '{}', '{}', {}, {}, '{}');",//FROM_UNIXTIME({})
		ESCA2UTF8(tableName), ESCA2UTF8(req.serverIp), req.serverPort, req.serverType, req.serverId,
		lc->belong, ESCA2UTF8(lc->name), ESCA2UTF8(lc->value), lc->type, lc->expire, ESCA2UTF8(std::move(curTime)));
	insertSql += buf; memset(buf, 0, sizeof(buf));

	ExecuteLogSql(insertSql, tableName, std::string(ITEM_CUST_VAR_UPDATE_TEMPLATE_TABLE_NAME));
}


void CLogManager::ExecuteLogSql(const std::string& insertSql, const std::string& createTableName, const std::string& templateTableName, bool isgame)
{
	int32_t ret = 0;
	if (!ExecuteSQL(insertSql.c_str(), ret, isgame) && ret == 1146)
	{
		std::string createSql = "";
		static char buf[10240] = { 0 };
		FMT2BUF(buf,
			"create table {} like {};", ESCA2UTF8(createTableName), ESCA2UTF8(templateTableName));
		createSql = buf;
		ExecuteSQL(createSql.c_str(), ret, isgame);
		ExecuteSQL(insertSql.c_str(), ret, isgame);
	}
}

bool CLogManager::ExecuteSQL(const char* sql, int32_t& ret, bool isgame)
{
	if (isgame)
	{
		int32_t res = m_DBConnector_GAME.ExecQuery(sql);
		if (res != 0) {
			ret = m_DBConnector_GAME.GetErrorCode();
			LOG_WARN("ExecQuery failed with errorcode:%d errormsg: %s\n", m_DBConnector_GAME.GetErrorCode(), m_DBConnector_GAME.GetErrorStr());
			return false;
		}
	}
	else
	{
		int32_t res = m_DBConnector[m_idx].ExecQuery(sql);
		if (res != 0) {
			ret = m_DBConnector[m_idx].GetErrorCode();
			LOG_WARN("ExecQuery failed with errorcode:%d errormsg: %s\n", m_DBConnector[m_idx].GetErrorCode(), m_DBConnector[m_idx].GetErrorStr());
			return false;
		}
	}
    
    return true;
}