#include "stdafx.h"
#include "LogHelper.h"
#include "ITimeHelper.h"
#include "IFileHelper.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#include <stdio.h>
#include <stdarg.h>
#include <iostream>

#include <sstream>

void LogHelper::Init(const std::string& folder)
{
	std::string cur_path = IFileHelper::GetInstance()->GetCurWorkPath();
	cur_path += "Log/";
	if (!folder.empty()) {
		cur_path += folder;
		cur_path += "/";
	}

	if (!IFileHelper::GetInstance()->IsDirExist(cur_path)) {
		IFileHelper::GetInstance()->CreateDir(cur_path);
	}

	mLogPath = cur_path;
	mRun = true;
	mOfs = true;
	mLogCacheList.clear();
    mTimerID = 0;

	ResetTimer();
	GenerateLogFileName();

	mThread = std::move(std::thread([&]() 
	{
		while (mRun)
		{
			if (mLogCacheList.empty())
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));
				continue;
			}
			Log();
		}
		Log();
	}));
	std::stringstream ss;
	ss << mThread.get_id();
	ss >> mId;
	//mThread.detach();
}

void LogHelper::UnInit()
{
	mRun = false;
	mThread.join();
	if (o.is_open())
	{
		o.close();
	}
}

std::string LogHelper::GetLevelStr(int level)
{
	std::string ret;
	switch (level) {
    case log_level_trace:
        ret = "[TRACE]";
        break;
	case log_level_error:
		ret = "[ERROR]";
		break;
	case log_level_warn:
		ret = "[WARN]";
		break;
	default:
		ret = "[NORMAL]";
		break;
	}
	return ret;
}

void LogHelper::UpdateConsoleColor(int type)
{
    static int nPreType = -1;
    if (type == nPreType) return;

#ifdef _WIN32
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (handle) {
		if (log_level_error == type) {
			SetConsoleTextAttribute(handle, FOREGROUND_RED);
		}
		else if (log_level_warn == type) {
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN);
		}
		else {
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
	}
#else
    if (log_level_error == type) {
        std::cout << "\033[31m";
    }
    else if (log_level_warn == type) {
        std::cout << "\033[33m";
    }
    else {
        std::cout << "\033[0m";
    }
#endif

    nPreType = type;
}

void LogHelper::LogPrint(int level, const char* format, ...)
{
	if (mLogPath.empty()) {
		return;
	}

	if (level < mlogLevel ) {
		return;
	}

	char buffer[128 * 1024];

	va_list args;
	va_start(args, format);
	vsprintf_s(buffer, _countof(buffer), format, args);
	va_end(args);

	std::string _strContent = ITimeHelper::GetInstance()->GetCurTimeStrMS();
	std::thread::id tid = std::this_thread::get_id();
	std::string tidStr = std::to_string(*(uint32_t*)&tid);
	_strContent += " [" + tidStr + "] ";
	_strContent += GetLevelStr(level);
	_strContent += " ";
	_strContent += buffer;

	PushLog(level, _strContent);
}

void LogHelper::ResetTimer()
{
	mOfs = true;
	if (0 == mTimerID)
	{
		TimerData timer;
		timer.interval = S2MS(ITimeHelper::GetInstance()->GetTimeSecOfDayEnd());
		timer.loop = true;
		timer.callBack = std::bind(&LogHelper::ResetTimer, this);
		mTimerID = ITimeHelper::GetInstance()->AddTimer(timer);
	}
	else
	{
		TimerData* timer = ITimeHelper::GetInstance()->GetTimer(mTimerID);
		if (timer)
		{
			timer->interval = S2MS(ITimeHelper::GetInstance()->GetTimeSecOfDayEnd());
		}
	}
}

void LogHelper::GenerateLogFileName()
{
	if (!mOfs) return;

	mOfs = false;
	std::string fileName = mLogPath + ITimeHelper::GetInstance()->GetDayString() + ".log";
	if (o.is_open())
	{
		o.close();
	}
	o.open(fileName, std::ios::app);
}

void LogHelper::PushLog(int32_t logLevel, const std::string& content)
{
	std::lock_guard<std::mutex> lg(mLogMutex);
	mLogCacheList.emplace_back(logLevel, content);
}

void LogHelper::Log()
{
	static decltype(mLogCacheList) tmpList;
	{
		std::lock_guard<std::mutex> lg(mLogMutex);
		tmpList = std::move(mLogCacheList);
		mLogCacheList.clear();
	}
	if (tmpList.empty()) return;
	auto iter = tmpList.begin();
	for (; iter != tmpList.end(); ++iter)
	{
		LogPrint(*iter);
	}
}

void LogHelper::LogPrint(const LogCacheData& log)
{
	UpdateConsoleColor(log.logLevel);
	std::cout << log.logContent << std::endl;
	UpdateConsoleColor(log_level_normal);
	// GenerateLogFileName放到当前线程中执行,避免io代码频繁加锁
	GenerateLogFileName();

	o << log.logContent << std::endl;
}