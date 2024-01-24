#pragma once

class GMCmdHandler
{
public:
    static void HandleCmd(const char *cmd, const char *param);

private:
    GMCmdHandler() = delete;

    static void HandleCmd_ReloadGameCfg(const char *param);
};