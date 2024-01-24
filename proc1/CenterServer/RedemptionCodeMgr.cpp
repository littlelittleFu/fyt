#include "stdafx.h"
#include "RedemptionCodeMgr.h"
#include "CenterServer.h"
#include "ProtoCS.h"

void RedemptionCodeMgr::SendToPlatform(const RedemptionCodeInfo& info)
{
    ctpl::task_t task = [=](int) {

        auto ack = std::make_shared<ProtoCS_ActivationCodeAck>();   // 大结构体在堆上分配
        ack->guid = info.guid;
        ack->err = ProtoCS_ActivationCodeAck::err_failed;
        ack->type = info.type;
        strcpy_s(ack->err_desc, "领取失败");

        do {
            ConfigInfo *cfg = ConfigInfo::GetInstance();
            if (!cfg) break;

            string url;
            switch (info.type) {
            case redemption_code_type_npc:
            case redemption_code_type_cdkey:
                url = cfg->m_sPlatformDomain + REDEMPTION_CODE_PATH;
                break;

            case redemption_code_type_game:
                url = cfg->m_sPlatformDomain + GIFT_CODE_PATH;
                break;

            default:
                break;
            }
            if (url.empty()) break;

            const int BUFSZ = 512;
            char data[BUFSZ] = {0};

            if (!ComposeHttpRequest(info, data, _countof(data)))
                break;

            LOG_TRACE("gift exchange request url: %s, data: %s", url.c_str(), data);

            auto curl = curl_easy_init();
            if (!curl) {
                LOG_ERROR("curl_easy_init failed");
                break;
            }

            std::vector<char> resp;
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CURLWriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

            curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (resp.empty()) break;
            ParseResult(*ack , resp.data(), info.type);

        } while (0);

        callable_t func = [=] {
            SendDataBySessionType(SESSION_TYPE_CS2MS, *ack);
        };
        auto &queue = CenterServer::GetInstance()->GetCallableQueue();
        queue.push(std::move(func));
    };

    auto& threadPool = CenterServer::GetInstance()->GetThreadPool();
    threadPool.push(std::move(task));
}

bool RedemptionCodeMgr::ComposeHttpRequest(const RedemptionCodeInfo& info, char* buf, int bufsz)
{
    ConfigInfo* cfg = ConfigInfo::GetInstance();
    if (!cfg) return false;

    auto gameID = cfg->GetCurAgentId();
    auto regionID = cfg->GetCurAreaId();
    auto serverID = regionID * 1000 + cfg->GetCurAreaServerId();

    switch (info.type)
    {
    case redemption_code_type_npc:
    case redemption_code_type_cdkey:
    {
        sprintf_s(buf, bufsz, "code=%s&game_id=%u&region_id=%u&role_id=%llu&server_id=%u&type=%u&user_id=%llu&key=%s",
            info.code, gameID, regionID, info.guid, serverID, info.type, info.userid, cfg->m_sServerKey.c_str());

        auto sign = MD5::GetMD5(buf);
        char* p = strstr(buf, "key=");

        sprintf_s(p, bufsz - (p - buf), "sign=%s", sign.c_str());
        return true;
    }
    case redemption_code_type_game:
    {
        sprintf_s(buf, bufsz, "gift_code=%s&game_id=%u&server_id=%u&chrname=%s&guid=%llu&account=%llu",
            info.code, gameID, serverID, gbk_to_utf8(info.name).c_str(), info.guid, info.userid);
        return true;
    }
    default:
        break;
    }



    return false;
}

bool RedemptionCodeMgr::ParseResult(ProtoCS_ActivationCodeAck& ack, const char* raw, uint16_t type)
{
    SAFE_BEGIN_EX;
    if (!raw) return false;

    LOG_TRACE("gift exchange respond: %s", raw);

    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(raw, raw + strlen(raw), root)) {
        LOG_ERROR("parse failed, raw: %s", raw);
        return false;
    }

    switch (type)
    {
    case redemption_code_type_npc:
    case redemption_code_type_cdkey:
    {
        if (!root.isMember("code")) {
            LOG_ERROR("No code member, raw: %s", raw);
            return false;
        }

        if (!root.isMember("msg")) {
            LOG_ERROR("No msg member, raw: %s", raw);
            return false;
        }

        auto code = root["code"].asUInt();
        auto _msg = root["msg"].asCString();
        ack.err = code;
        strcpy_s(ack.err_desc, _countof(ack.err_desc), utf8_to_gbk(_msg));
        return true;
    }
    case redemption_code_type_game:
    {
        if (!root.isMember("ret")) {
            LOG_ERROR("No ret member, raw: %s", raw);
            return false;
        }

        if (!root.isMember("msg")) {
            LOG_ERROR("No msg member, raw: %s", raw);
            return false;
        }

        if (root.isMember("gift_name")) {
            auto gift_name = root["gift_name"].asCString();
            strcpy_s(ack.gift_name, _countof(ack.gift_name), utf8_to_gbk(gift_name));
        }

        if (root.isMember("gift_content")) {
            auto gift_content = root["gift_content"].asCString();
            strcpy_s(ack.gift_content, _countof(ack.gift_content), utf8_to_gbk(gift_content));
        }
        auto ret = root["ret"].asUInt();
        auto _msg = root["msg"].asCString();

        ack.err = ret;
        strcpy_s(ack.err_desc, _countof(ack.err_desc), utf8_to_gbk(_msg));
        return true;
    }
    default:
        break;
    }

    return false;
    SAFE_END_EX(false);
}

size_t RedemptionCodeMgr::CURLWriteCallback(void* data, size_t size, size_t nmemb, void* userp)
{
    auto len = size * nmemb;

    auto* resp = static_cast<std::vector<char> *>(userp);

    auto oldSize = resp->size();
    auto newSize = oldSize + len + 1;

    resp->resize(newSize);

    memcpy(resp->data() + oldSize, data, len);

    return len;
}