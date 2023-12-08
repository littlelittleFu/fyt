#pragma once
#include<iostream>
#include<string>
#define LOG_NORMAL(format, ...) Log::GetInstance()->PrintMessage(log_level_normal,"NORMAL",__FUNCTION__,__LINE__,format,##__VA_ARGS__)
#define LOG_WARNING(format, ...) Log::GetInstance()->PrintMessage(log_level_warning,"WARNING",__FUNCTION__,__LINE__,format,##__VA_ARGS__)
#define LOG_ERROR(format, ...) Log::GetInstance()->PrintMessage(log_level_err,"ERROR",__FUNCTION__,__LINE__,format,##__VA_ARGS__)

enum log_level {
	log_level_normal,
	log_level_warning,
	log_level_err,
};
class Log {
public:
	Log():mLogLv(log_level::log_level_normal) {
		memset(buf, 0, sizeof(buf));
	}

	static Log* GetInstance();

	void PrintMessage(log_level lv, const char* desc, const char * func, int line, const char* format, ...) {
		if (lv < log_level_normal) return;

		memset(buf, 0, sizeof(buf));

		va_list args;
		__crt_va_start(args, format);
		vsprintf_s(buf, _countof(buf), format, args);
		__crt_va_end(args);

		std::cout << "LOG [" << desc << "] [" << func << ":" << __LINE__ << "] Desc:"  << buf << std::endl;
	}

private:
	char buf[1024] = {0};
	log_level mLogLv;
	static Log* m_instance;
};

Log* Log::m_instance = new Log;
Log* Log::GetInstance() { return m_instance; }