#pragma once


class GateServer
{
    DECL_SINGLETON(GateServer)

public:
    void Start();
    void Quit() { m_NeedQuit = true; }

protected:
    GateServer();
    ~GateServer();

    bool InitConfig();
    bool InitNetwork();
    void Run();
    bool NeedQuit();
    void Term();

    void StartConnCheckTimer();
    void StopConnCheckTimer();
    void OnConnCheckTimer();

    void SetLogLevel();
    void LogDebugInfo(uint32_t delta);

public:
    void SetCloseServerState() { m_CloseServerState = true; };
    bool IsCloseServerState() { return m_CloseServerState; }

protected:
    bool m_NeedQuit = false;
    uint32_t m_ConnCheckTimerID = 0;
    bool m_CloseServerState = false;
};
