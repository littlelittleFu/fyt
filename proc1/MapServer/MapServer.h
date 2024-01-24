#pragma once
#include <string>

struct TimerData;

class MapServer
{
	DECL_SINGLETON(MapServer)
public:
	MapServer();
	~MapServer();

	void Start();
	void Quit() { m_NeedQuit = true; }
    bool LoadLuaScripts();
	float GetMoveMistake() { return m_MoveMistake; }
	void SetMoveMistake(uint32_t MoveMistake);
	//
	void RunClientScript(const char* pScriptName, const char* pContent, bool bCompress);

protected:
	bool InitConfig();
	bool InitNetwork();
	bool InitTable();
	bool InitLuaEngine();
	bool RegisterLuaModule();
    bool InitAStarPathFinder();
	void Run();
	bool NeedQuit();
    void Term();

    void StartConnCheckTimer();
    void StopConnCheckTimer();
    void OnConnCheckTimer();

	void SetLogLevel();
	void LogDebugInfo(uint32_t delta);
	void CreateAllMap();

protected:
	bool                m_NeedQuit          = false;
    uint32_t            m_ConnCheckTimerID  = 0;
	float				m_MoveMistake = 0.9f;
	uint32_t			m_Update_Delta		= 0;
};
