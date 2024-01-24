
#pragma once
#include "DBConnector.h"
#include "ProtoLog.h"

#include <locale>
#include <codecvt>
#include <iostream>
#include <list>

//#include"ProtoCS.h"
//#include"ProtoMS.h"
//#include"ProtoDB.h"
#define SWITCH_LOG_DB_CMD   "SwitchLogDB"
#define DB_CONNECT_COUNT    2
enum DBErrCode {
    DBERR_OK,
    DBERR_EXESQL,
    DBERR_PARAM,
    DBERR_ROWNUM,
    DBERR_EMPTY,
    DBERR_NOTMATCH,
    DBERR_EXCEPT
};

class CLogManager
{
public:
    CLogManager();
	~CLogManager();

	static CLogManager* GetInstance();
	bool Init(uint8_t tmpIdx = 0);
    bool InitGame();
    void Logging(const ProtoLog_LoggingReq& req);
    void SetSwitchLogDB(std::string ipPort);
    void CheckSwitchLogDB();
protected:
    void HandleCurrentChange(const ProtoLog_LoggingReq& req);
    void HandleItemUpdate(const ProtoLog_LoggingReq& req);
    void HandleLoginOut(const ProtoLog_LoggingReq& req);
    void HandleEnteryExitMap(const ProtoLog_LoggingReq& req);
    void HandleDropItem(const ProtoLog_LoggingReq& req);
    void HandleGmCmd(const ProtoLog_LoggingReq& req);
    void HandleOnlineNumCmd(const ProtoLog_LoggingReq& req);
    void HandleTradeDataCmd(const ProtoLog_LoggingReq& req);
    void HandleMailInfoCmd(const ProtoLog_LoggingReq& req);
    void HandleDeathRecordCmd(const ProtoLog_LoggingReq& req);
    void HandleActivityDataCmd(const ProtoLog_LoggingReq& req);
    void HandleRewardDataCmd(const ProtoLog_LoggingReq& req);
    void HandleGiftpackDataCmd(const ProtoLog_LoggingReq& req);
    void HandleRecoveryDataCmd(const ProtoLog_LoggingReq& req);
    void HandleDBSqlCmd(const ProtoLog_LoggingReq& req);
    void HandleItemDynAttr(const ProtoLog_LoggingReq& req);
    void HandleItemCustVar(const ProtoLog_LoggingReq& req);

    void ExecuteLogSql(const std::string& insertSql, const std::string& createTableName, const std::string& templateTableName, bool isgame = false);

    bool ExecuteSQL(const char* sql, int32_t& ret,bool isgame = false);
private:
	static CLogManager* s_Instance;
	DBConnector    m_DBConnector[DB_CONNECT_COUNT];
    DBConnector    m_DBConnector_GAME;
    uint8_t m_idx = 0;
    std::atomic<bool> m_switch{false};
    std::string m_switchIp = "";
    int32_t m_switchPort = 0;

    std::string m_msversion = "";
};
