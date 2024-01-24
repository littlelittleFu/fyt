#include "stdafx.h"
#include "MonitorChatMsgMgr.h"
#include "ConfigInfo.h"
#include "CenterServer.h"

void MonitorChatMsgMgr::SendToPlatform(const MONITOR_CHAT_INFO &chatInfo)
{
    auto *cfg = ConfigInfo::GetInstance();
    if (!cfg) return;

    auto url = cfg->m_sPlatformDomain + MONITOR_CHAT_PATH;

    auto spChatInfo = std::make_shared<MONITOR_CHAT_INFO>(chatInfo);    // 结构体太大，在堆上分配

    ctpl::task_t task = [=] (int) {
        const int HTTP_MSG_LENGTH = 10240;
        char data[HTTP_MSG_LENGTH] = { 0 };

        if (!ComposeHttpRequest(*spChatInfo, data, _countof(data)))
            return;

        auto *curl = curl_easy_init();
        if (!curl) {
            LOG_ERROR("curl_easy_init failed");
            return;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    };

    auto &threadPool = CenterServer::GetInstance()->GetThreadPool();
    threadPool.push(std::move(task));
}

bool MonitorChatMsgMgr::ComposeHttpRequest(const MONITOR_CHAT_INFO &chatInfo, char *buf, int bufsz)
{
    ConfigInfo *cfg = ConfigInfo::GetInstance();
    if (!cfg) return false;

    auto gameID = cfg->GetCurAgentId();
    auto regionID = cfg->GetCurAreaId();
    auto serverID = regionID * 1000 + cfg->GetCurAreaServerId();

    sprintf_s(buf, bufsz, "game_id=%u&region_id=%u&server_id=%u&user_id=%s&"
        "user_name=%s&to_user_id=%s&to_user_name=%s&channel=%u&guild=%s&content=%s&time=%s",
        gameID, regionID, serverID, to_string(chatInfo.user_id).c_str(), gbk_to_utf8(chatInfo.user_name).c_str()
        , to_string(chatInfo.to_user_id).c_str(), gbk_to_utf8(chatInfo.to_user_name).c_str(), chatInfo.channel
        , gbk_to_utf8(chatInfo.guild).c_str(), gbk_to_utf8(chatInfo.content).c_str(), chatInfo.stamp);

    return true;
}