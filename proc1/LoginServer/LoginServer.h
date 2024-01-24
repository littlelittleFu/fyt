#pragma once


class LoginServer
{
	DECL_SINGLETON(LoginServer)
public:
	LoginServer();
	~LoginServer();

	void Start();
	void Quit() { m_NeedQuit = true; }

protected:
	bool InitConfig();
	bool InitNetwork();
	void Run();
	bool NeedQuit();
    void Term();

    void StartConnCheckTimer();
    void StopConnCheckTimer();
    void OnConnCheckTimer();

	void SetLogLevel();
protected:
	bool m_NeedQuit = false;
    uint32_t m_ConnCheckTimerID = 0;
};


