#pragma once

#include "tsqueue.h"

class CenterServer
{
    DECL_SINGLETON(CenterServer)

public:
    void Start();
    void Quit() { m_NeedQuit = true; }

    ctpl::thread_pool & GetThreadPool() { return m_ThreadPool; }

    callable_tsqueue & GetCallableQueue() { return m_CallableQueue; }

protected:
    CenterServer();
    ~CenterServer();

    bool InitConfig();
    bool InitTable();
    bool InitNetwork();
    bool InitLuaEngine();
    void Run();
    void CallFuncInQueue();
    bool NeedQuit();
    void Term();

    void StartConnCheckTimer();
    void StopConnCheckTimer();
    void OnConnCheckTimer();

    void SetLogLevel();
    void LogDebugInfo(uint32_t delta);

protected:
    bool                m_NeedQuit          = false;
    uint32_t            m_ConnCheckTimerID  = 0;
    ctpl::thread_pool   m_ThreadPool;
    callable_tsqueue    m_CallableQueue;
};
