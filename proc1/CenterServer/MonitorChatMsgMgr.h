#pragma once


class MonitorChatMsgMgr
{
public:
    MonitorChatMsgMgr() = delete;
    ~MonitorChatMsgMgr() = delete;

    static void SendToPlatform(const MONITOR_CHAT_INFO &chatInfo);
	static bool ComposeHttpRequest(const MONITOR_CHAT_INFO &chatInfo, char *buf, int bufsz);
};