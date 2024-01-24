#include "stdafx.h"
#include "ErrorReporter.h"
#include <thread>
#include <curl.h>

void ErrorReporter::Report(bool useThread)
{
    CURL *curl = curl_easy_init();
    if (!curl) return;

    auto data = ComposePostData();
    curl_easy_setopt(curl, CURLOPT_URL, mURL.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

    if (useThread) {
        std::thread t ([curl] {
            curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        });
        t.detach();
    }
    else {
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
}

std::string ErrorReporter::ComposePostData()
{
    char buf[64];

    sprintf_s(buf, _countof(buf), "game_id=%u&server_id=%u&type=%u&msg=",
              mGameID, mServerID, mType);

    auto *msg = curl_easy_escape(nullptr, mMsg.c_str(), 0);
    auto data = std::string(buf) + msg;
    curl_free(msg);

    return data;
}
