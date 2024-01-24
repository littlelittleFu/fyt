#pragma once

#include <string>

enum
{
    log_level_trace = 1,
	log_level_normal,
	log_level_warn,
	log_level_error,
};

class ILogHelper
{
public:
	static void SetInstance(ILogHelper* inst) { m_instance = inst; };
	static ILogHelper* GetInstance() { return m_instance; };

	virtual void Init(const std::string& folder = "") = 0;
	virtual void UnInit() = 0;
	virtual void LogPrint(int level, const char* format, ...) = 0;
	virtual void SetLogLevel(int32_t logLevel) = 0;

private:
	static ILogHelper* m_instance;
};

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#ifdef _WIN32
#define DECFORMAT(format) "[" __FUNCTION__ ":" STR(__LINE__) "] " format
#else
#define DECFORMAT(format) "[" __FILE__ ":" STR(__LINE__) "] " format
#endif

#define LOG_INIT(folder) ILogHelper::GetInstance()->Init(folder);
#define LOG_UNINIT() ILogHelper::GetInstance()->UnInit();

#define LOG_TRACE(format, ...) ILogHelper::GetInstance()->LogPrint(log_level_trace, DECFORMAT(format), ##__VA_ARGS__);
#define LOG_NORMAL(format,...) ILogHelper::GetInstance()->LogPrint(log_level_normal,DECFORMAT(format), ##__VA_ARGS__);
#define LOG_WARN(format,...) ILogHelper::GetInstance()->LogPrint(log_level_warn, DECFORMAT(format), ##__VA_ARGS__);
#define LOG_ERROR(format,...) ILogHelper::GetInstance()->LogPrint(log_level_error, DECFORMAT(format), ##__VA_ARGS__);