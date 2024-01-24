#pragma once

class GMCmdHandler
{
public:
    static void HandleCmd(const char *cmd, const char *param);

private:
    GMCmdHandler() = delete;

    static bool IsNeedSendToDB(const char *cmd, const char *param);
    static void SendRunGMCmdToDB(const char *cmd, const char *param);

    static void HandleCmd_ReloadGameCfg(const char *param);
};