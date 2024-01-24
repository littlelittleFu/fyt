#pragma once

#include "SessionContextMgr.h"

class ThirdPartLoginMgr
{
    DECL_SINGLETON(ThirdPartLoginMgr);

public:
    bool Init();

    void Term();

    void CheckToken(SPSessionContext context);

    void OnUpdate();

private:
    ThirdPartLoginMgr();
    ~ThirdPartLoginMgr();

    void ThreadProc();
    CURL * InitCurl();

    static size_t CURLWriteCallback(void *data, size_t size, size_t nmemb, void *userp);

    void DoCheckToken(SPSessionContext &context, CURL *curl);

    std::string FormPostData(SPSessionContext &context);

    void ParseResult(SPSessionContext &context, const char *raw);

    void GetCheckedContext(std::list<SPSessionContext> &contexts);

private:
    std::vector<std::thread> m_threads;
    std::mutex m_mutex;
    std::condition_variable m_cv;

    std::list<SPSessionContext> m_ctxToBeChecked;
    std::list<SPSessionContext> m_ctxChecked;

    std::atomic<bool> m_exit{false};
    std::atomic<bool> m_needHandleData{false};
};
