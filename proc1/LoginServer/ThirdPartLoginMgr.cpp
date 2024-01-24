#include "stdafx.h"
#include "ThirdPartLoginMgr.h"
#include "MD5.h"
#include "json.h"
#include "SessionManager.h"
#include "SessionLS2GS.h"

IMPL_SINGLETON(ThirdPartLoginMgr)

ThirdPartLoginMgr::ThirdPartLoginMgr()
{
}

ThirdPartLoginMgr::~ThirdPartLoginMgr()
{
}

bool ThirdPartLoginMgr::Init()
{
    m_exit = false;

    auto *cfg = ConfigInfo::GetInstance();

    for (int i = 0; i < cfg->m_nCheckTokenThreadNum; ++i) {
        m_threads.emplace_back(&ThirdPartLoginMgr::ThreadProc, this);
    }

    return true;
}

void ThirdPartLoginMgr::Term()
{
    m_exit = true;

    m_cv.notify_all();

    for (auto &t : m_threads) t.join();

    m_threads.clear();
    m_ctxToBeChecked.clear();
    m_ctxChecked.clear();
}

void ThirdPartLoginMgr::CheckToken(SPSessionContext context)
{
    std::unique_lock<std::mutex> lk(m_mutex);

    m_ctxToBeChecked.emplace_back(std::move(context));

    m_cv.notify_all();
}

void ThirdPartLoginMgr::GetCheckedContext(std::list<SPSessionContext> &contexts)
{
    std::unique_lock<std::mutex> lk(m_mutex);

    contexts = std::move(m_ctxChecked);

    m_ctxChecked.clear();
    m_needHandleData = false;
}

void ThirdPartLoginMgr::ThreadProc()
{
    auto *curl = InitCurl();
    if (!curl) return;

    std::unique_lock<std::mutex> lk(m_mutex);

    while (!m_exit) {

        m_cv.wait(lk);

        if (m_exit) break;

        do {

            if (m_ctxToBeChecked.empty()) break;

            auto context = std::move(m_ctxToBeChecked.front());
            m_ctxToBeChecked.pop_front();

            lk.unlock();

            DoCheckToken(context, curl);

            lk.lock();

            m_ctxChecked.emplace_back(std::move(context));
            m_needHandleData = true;

        } while (!m_exit);
    }

    curl_easy_cleanup(curl);
}

CURL * ThirdPartLoginMgr::InitCurl()
{
    CURL *curl = curl_easy_init();
    if (!curl) {
        LOG_ERROR("curl_easy_init failed");
        return nullptr;
    }

    auto *cfg = ConfigInfo::GetInstance();
    auto url = cfg->m_sPlatformDomain + CHECK_TOKEN_PATH;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CURLWriteCallback);

    return curl;
}

size_t ThirdPartLoginMgr::CURLWriteCallback(void *data, size_t size, size_t nmemb, void *userp)
{
    auto len = size * nmemb;

    auto *resp = static_cast<std::vector<char> *>(userp);

    auto oldSize = resp->size();
    auto newSize = oldSize + len + 1;

    resp->resize(newSize);

    memcpy(resp->data() + oldSize, data, len);

    return len;
}

void ThirdPartLoginMgr::DoCheckToken(SPSessionContext &context, CURL *curl)
{
    std::vector<char> resp;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);

    auto data = FormPostData(context);
    Tools::Purge(context->sPlatformToken);    // 不再使用，回收内存
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

    curl_easy_perform(curl);

    if (resp.empty()) return;

    ParseResult(context, resp.data());
}

std::string ThirdPartLoginMgr::FormPostData(SPSessionContext &context)
{
    auto *cfg = ConfigInfo::GetInstance();

    auto *token = curl_easy_escape(nullptr, context->sPlatformToken.c_str(), 0);
    if (!token) {
        LOG_ERROR("curl_easy_escape failed");
        return "";
    }

    char buf[1024];

    sprintf_s(buf, _countof(buf),
        "channel=%s&game_id=%u&server_id=%u&token=%s&key=%s",
        context->sChannel.c_str(), context->nGameID, cfg->GetCurServerId(),
        token, cfg->m_sServerKey.c_str());

    curl_free(token);

    auto sign = MD5::GetMD5(buf);

    char *p = strstr(buf, "key=");
    sprintf_s(p, _countof(buf) - (p - buf), "sign=%s", sign.c_str());

    return buf;
}

void ThirdPartLoginMgr::ParseResult(SPSessionContext &context, const char *raw)
{
    SAFE_BEGIN;

    if (!raw) return;
    LOG_TRACE("check token response: %s", raw);

    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(raw, raw + strlen(raw), root)) {
        LOG_ERROR("parse failed, raw: %s", raw);
        return;
    }

    if (!root.isMember("code")) {
        LOG_ERROR("No code member, raw: %s", raw);
        return;
    }

    auto code = root["code"].asInt();
    if (code != 0) {
        LOG_ERROR("Verify token failed. raw: %s", raw);
        return;
    }

    if (!root.isMember("data")) {
        LOG_ERROR("No data member, raw: %s", raw);
        return;
    }

    const auto &data = root["data"];

    if (!data.isMember("userId")) {
        LOG_ERROR("No userId member, raw: %s", raw);
        return;
    }

    context->nPlayerGUID = std::stoull(data["userId"].asString());
    if (context->nPlayerGUID == 0) {
        LOG_ERROR("Wrong userId, raw: %s", raw);
        return;
    }

    SAFE_END;
}

void ThirdPartLoginMgr::OnUpdate()
{
    if (!m_needHandleData) return;

    std::list<SPSessionContext> context;
    GetCheckedContext(context);

    for (auto &it : context) {

        auto *session = SessionManager::GetInstance()->GetSessionByID(it->nGateServSessionID);
        if (!session) {
            LOG_ERROR("session is NULL. id: %u", it->nGateServSessionID);
            continue;
        }

        auto *gssess = static_cast<SessionLS2GS *>(session);
        gssess->HandleThirdPartLoginResult(std::move(it));
    }
}
