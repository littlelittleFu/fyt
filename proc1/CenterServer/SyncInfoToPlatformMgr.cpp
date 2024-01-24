#include "stdafx.h"
#include "SyncInfoToPlatformMgr.h"
#include "ConfigInfo.h"
#include "MD5.h"
#include "CenterServer.h"

void CreateRoleInfoMgr::SendToPlatform(const PLATFORM_CREATE_ROLE_INFO& info)
{
    auto* cfg = ConfigInfo::GetInstance();
    if (!cfg) return;

    auto url = cfg->m_sPlatformDomain + REPORT_ROLE_PATH;
    auto spCreateRoleInfo = std::make_shared<PLATFORM_CREATE_ROLE_INFO>(info);

    auto task = [=](int) {
        const int HTTP_MSG_LENGTH = 10240;
        char data[HTTP_MSG_LENGTH] = { 0 };

        if (!ComposeHttpRequest(*spCreateRoleInfo, data, _countof(data))) {
            return;
        }

        auto* curl = curl_easy_init();
        if (!curl) {
            LOG_ERROR("curl_easy_init failed");
            return;
        }

        // 有返回值 但是返回值不用处理
        //std::vector<char> resp;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CURLWriteCallback);
        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    };

    auto& theadPool = CenterServer::GetInstance()->GetThreadPool();
    theadPool.push(task);
}

bool CreateRoleInfoMgr::ComposeHttpRequest(const PLATFORM_CREATE_ROLE_INFO& info, char* buf, int bufsz)
{
    ConfigInfo* cfg = ConfigInfo::GetInstance();
    if (!cfg) return false;

    sprintf_s(buf, bufsz, "channel=%s&game_id=%s&region_id=%s&role_id=%s&server_id=%s&user_id=%s&key=%s",
        info.channel.c_str(), info.game_id.c_str(), info.region_id.c_str(), info.role_id.c_str(),
        info.server_id.c_str(), info.user_id.c_str(), cfg->m_sServerKey.c_str());

    auto sign = MD5::GetMD5(buf);
    char* p = strstr(buf, "key=");

    sprintf_s(p, bufsz - (p - buf), "sign=%s", sign.c_str());
    return true;
}

bool CreateRoleInfoMgr::GeneratePlatformCreateRoleInfo(uint64_t roleID, uint64_t userID, const std::string& channel, PLATFORM_CREATE_ROLE_INFO& info)
{
    ConfigInfo* cfg = ConfigInfo::GetInstance();
    if (!cfg) return false;

    info.game_id = std::to_string(cfg->GetCurAgentId());
    info.region_id = std::to_string(cfg->GetCurAreaId());
    info.server_id = std::to_string(cfg->GetCurAreaId()*1000 + cfg->GetCurAreaServerId());
    info.channel = channel;
    info.role_id = std::to_string(roleID);
    info.user_id = std::to_string(userID);

    return true;
}