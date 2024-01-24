#include "stdafx.h"
#include "LoginIPManager.h"
#include "ThirdPartLoginMgr.h"
#include "json.h"
#include "Utility.h"

IMPL_SINGLETON(LoginIPManager)

size_t LoginIPManager::CURLWriteCallback(void* data, size_t size, size_t nmemb, void* userp)
{
    auto len = size * nmemb;

    auto* resp = static_cast<std::vector<char> *>(userp);

    auto oldSize = resp->size();
    auto newSize = oldSize + len + 1;

    resp->resize(newSize);

    memcpy(resp->data() + oldSize, data, len);

    return len;
}

bool LoginIPManager::GetWhiteIPList()
{
    CURL* curl = curl_easy_init();
    if (!curl) {
        LOG_ERROR("curl_easy_init failed");
        return false;
    }

    auto* cfg = ConfigInfo::GetInstance();
    std::string params = "?AgentId=" + to_string(cfg->m_agentId) + "&AreaId=" + to_string(cfg->m_areaId) + "&AreaServerId=" + to_string(cfg->m_areaServerId);
    auto url = cfg->m_sPlatformDomain + CHECK_WHITE_IP_PATH + params;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CURLWriteCallback);

    std::vector<char> resp;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (resp.empty()) return false;

    // ½âÎö
    Json::Value root;
    Json::Reader reader;

    const auto* json = resp.data();
    reader.parse(json, json + strlen(json), root);
    if (root.isNull())
    {
        LOG_ERROR("parse failed, data: %s", resp.data());
        return false;
    }

    for (auto it = mIPMap.begin(); it != mIPMap.end();) {
        if (it->second.type == login_ip_type_white) {
            it = mIPMap.erase(it);
            continue;
        }
        ++it;
    }

    for (auto& it : root)
    {
        auto ip = Utility::IpStr2UInt(it.asString());
        if (ip)
        {
            LOGIN_IP_DATA data;
            data.ip = ip;
            data.type = login_ip_type_white;
            mIPMap[ip] = data;
        }
    }

    return true;
}

bool LoginIPManager::GetWhiteAccountNameList()
{
    CURL* curl = curl_easy_init();
    if (!curl) {
        LOG_ERROR("curl_easy_init failed");
        return false;
    }

    auto* cfg = ConfigInfo::GetInstance();
    std::string params = "?AgentId=" + to_string(cfg->m_agentId) + "&AreaId=" + to_string(cfg->m_areaId) + "&AreaServerId=" + to_string(cfg->m_areaServerId);
    auto url = cfg->m_sPlatformDomain + GET_WHITE_ACCOUNT_NAME + params;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CURLWriteCallback);

    std::vector<char> resp;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (resp.empty()) return false;

    // ½âÎö
    Json::Value root;
    Json::Reader reader;

    const auto* json = resp.data();
    reader.parse(json, json + strlen(json), root);
    if (root.isNull())
    {
        LOG_ERROR("parse failed, data: %s", resp.data());
        return false;
    }

    mWhiteAcountNameList.clear();

    for (auto& it : root)
    {
        auto whiteName = it.asString();
        if (CSV_HELPER::CsvUtils::StrIsUTF8(whiteName)) {
            whiteName = utf8_to_gbk(whiteName);
        }
        
        mWhiteAcountNameList.push_back(whiteName);
    }

    return true;
}

void LoginIPManager::InitLoginIpDataFromDB(uint16_t num, LOGIN_IP_DATA* data)
{
	for (int i = 0; i < num; ++i)
	{
		mIPMap[data[i].ip] = data[i];
	}
}

void LoginIPManager::SyncLoginIpInfoFromDB(ProtoDB_SyncLoginTypeToLS* data)
{
    for (int i = 0; i < data->num; ++i)
    {
        if (data->opt_type == ProtoDB_SyncLoginTypeToLS::add)
        {
            mIPMap[data->infos[i].ip] = data->infos[i];
        }
        else if (data->opt_type == ProtoDB_SyncLoginTypeToLS::del)
        {
            auto it = mIPMap.find(data->infos[i].ip);
            if (it != mIPMap.end())
            {
                mIPMap.erase(it);
            }
        }
    }
}

bool LoginIPManager::IsWhiteIp(uint32_t ip)
{
    if (mIPMap.find(ip) != mIPMap.end())
    {
        if (mIPMap[ip].type == login_ip_type_white)
            return true;
    }
    return false;
}

bool LoginIPManager::IsBlackIp(uint32_t ip)
{

    if (mIPMap.find(ip) != mIPMap.end())
    {
        if (mIPMap[ip].type == login_ip_type_black)
            return true;
    }
    return false;
}

bool LoginIPManager::IsWhiteName(const char* account)
{
    for (auto& i : mWhiteAcountNameList) {
        if (strcmp(i.c_str(), account) == 0)return true;
    }
    return false;
}