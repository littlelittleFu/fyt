#include "stdafx.h"
#include "GMCmdHandler.h"
#include "ProtoMS.h"

#define HANDLE_CMD(cmd) { #cmd, &GMCmdHandler::HandleCmd_##cmd }

void GMCmdHandler::HandleCmd(const char *cmd, const char *param)
{
    if (!cmd || !param) return;

    if (IsNeedSendToDB(cmd, param)) {
        SendRunGMCmdToDB(cmd, param);
    }

    using handler_t = void (*)(const char *);

    static std::map<std::string, handler_t> handlers = {
        HANDLE_CMD(ReloadGameCfg)
    };

    auto it = handlers.find(cmd);
    if (it == handlers.end()) return;

    auto &handler = it->second;
    handler(param);
}

bool GMCmdHandler::IsNeedSendToDB(const char *cmd, const char *param)
{
    if (!cmd || !param) return false;

    if (strcmp(cmd, "ReloadGameCfg") == 0) {
        return true;
    }

    return false;
}

void GMCmdHandler::SendRunGMCmdToDB(const char *cmd, const char *param)
{
    ProtoMS_RunGMCmd data;
    strcpy_s(data.cmd, cmd);
    strcpy_s(data.param, param);
    SendDataBySessionType(SESSION_TYPE_CS2DB, data);
}

void GMCmdHandler::HandleCmd_ReloadGameCfg(const char *param)
{
    auto files = str_split(param, " ");
    bool result = true;

    if (files.empty()) {            // ¼ÓÔØÈ«²¿
        result = GameCfgMgr::GetInstance()->ReloadAllCfg();
    }
    else {
        result = GameCfgMgr::GetInstance()->ReloadCfg(files);
    }
}
