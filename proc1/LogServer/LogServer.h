#include <iostream>


class LogServer
{
	DECL_SINGLETON(LogServer)
public:
	LogServer();
	~LogServer();

	void Start();
	void Quit() { m_NeedQuit = true; }

protected:
	bool InitConfig();
	bool InitNetwork();
	void Run();
	bool NeedQuit();

	void StartConnCheckTimer();
	void StopConnCheckTimer();
	void OnConnCheckTimer();

	void SetLogLevel();
    void LogDebugInfo(uint32_t delta);

protected:
	bool m_NeedQuit = false;
	uint32_t m_ConnCheckTimerID = 0;
	std::thread m_cmd;
};
