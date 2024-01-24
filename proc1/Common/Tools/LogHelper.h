#pragma once

#include <string>
#include <thread>
#include <list>
#include <mutex>
#include <fstream>
#include "ILogHelper.h"

#include <atomic>
struct LogCacheData
{
	LogCacheData(int32_t level, const std::string& content)
	{
		logLevel = level;
		logContent = content;
	}
	int32_t			logLevel = 0;
	std::string		logContent = "";
};
class LogHelper : public ILogHelper
{
public:
	void Init(const std::string& folder = "");
	void UnInit();
	void LogPrint(int level, const char* format, ...);
	void SetLogLevel(int32_t logLevel) { mlogLevel = logLevel; };

	void ResetTimer();
	void GenerateLogFileName();
protected:
	std::string GetLevelStr(int level);
	void UpdateConsoleColor(int type);
	void PushLog(int32_t logLevel,const std::string& content);
	void Log();
	void LogPrint(const LogCacheData& log);
private:
	std::string mLogPath;
	int32_t mlogLevel = log_level_trace;
	std::mutex	mLogMutex;
	std::thread	mThread;
	std::string mId;
	std::ofstream o;
	uint32_t mTimerID;
	std::atomic<bool>	mRun{false};
	std::atomic<bool>	mOfs{false};
	std::list<LogCacheData>	mLogCacheList;// 消费>生产
};

