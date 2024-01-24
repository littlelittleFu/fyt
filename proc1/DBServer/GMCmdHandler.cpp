#include "stdafx.h"
#include "GMCmdHandler.h"
#include "GameCfgMgr.h"

#define HANDLE_CMD(cmd) { #cmd, &GMCmdHandler::HandleCmd_##cmd }

void GMCmdHandler::HandleCmd(const char *cmd, const char *param)
{
    if (!cmd || !param) return;

    using handler_t = void (*)(const char *);

    static std::map<std::string, handler_t> handlers = {
        HANDLE_CMD(ReloadGameCfg)
    };

    auto it = handlers.find(cmd);
    if (it == handlers.end()) return;

    auto &handler = it->second;
    handler(param);
}

void GMCmdHandler::HandleCmd_ReloadGameCfg(const char *param)
{
    auto files = str_split(param, " ");
    std::vector<std::string> needLoad;

    if (files.empty()) {            // ¼ÓÔØÈ«²¿
        needLoad.push_back("illegal_characters");
    }
    else {
        for (auto &file : files) {
            if (file == "illegal_characters")
                needLoad.emplace_back(std::move(file));
        }
    }

    GameCfgMgr::GetInstance()->ReloadCfg(needLoad);
}
