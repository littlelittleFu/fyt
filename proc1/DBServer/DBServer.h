#pragma once
//#include "ScheduledHelper.h"

class DBServer
{
	DECL_SINGLETON(DBServer)
public:
	DBServer();
	~DBServer();

	void Start();
	void Quit() { m_NeedQuit = true; }

protected:
	bool InitConfig();
	bool InitTable();
	bool InitNetwork();
	bool InitDBManagerTimer();
	void Run();
	bool NeedQuit();
    void Term();

    void StartConnCheckTimer();
    void StopConnCheckTimer();
    void OnConnCheckTimer();

	void SetLogLevel();
    void LogDebugInfo(uint32_t delta);

	void UpdateMailDeleteDay();

protected:
    bool m_NeedQuit = false;
    uint32_t m_ConnCheckTimerID = 0;
};
