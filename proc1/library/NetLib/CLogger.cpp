#include "pch.h"
#include "CLogger.h"

IMPLEMENT_INSTANCE(CLogger)

CLogger::CLogger() : m_LogFunc(NULL)
{
	Init();
}

CLogger::~CLogger()
{
	UnInit();
}

bool CLogger::Init()
{
	SetLogger(this);
	return true;
}

void CLogger::UnInit()
{

}

void CLogger::SetLogger(ILogger* _Logger)
{
	m_Logger = _Logger;
}

void CLogger::LogCritical(const char* _Format, ...)
{
	if (NULL != m_Logger) {
		char _Msg[512] = { 0 };
		va_list args;
		va_start(args, _Format);
		int32_t _Len = sprintf(_Msg, "%s ", "[CRIT]");
		_vsnprintf(_Msg + _Len, sizeof(_Msg) - _Len - 1, _Format, args);
		va_end(args);
		m_Logger->LogText(_Msg, log_error);
	}
}

void CLogger::LogWarning(const char* _Format, ...)
{
	if (NULL != m_Logger) {
		char _Msg[512] = { 0 };
		va_list args;
		va_start(args, _Format);
		int32_t _Len = sprintf(_Msg, "%s ", "[WARN]");
		_vsnprintf(_Msg + _Len, sizeof(_Msg) - _Len - 1, _Format, args);
		va_end(args);
		m_Logger->LogText(_Msg, log_warn);
	}
}

void CLogger::LogTrace(const char* _Format, ...)
{
	if (NULL != m_Logger) {
		char _Msg[512] = { 0 };
		va_list args;
		va_start(args, _Format);
		int32_t _Len = sprintf(_Msg, "%s ", "[INFO]");
		_vsnprintf(_Msg + _Len, sizeof(_Msg) - _Len - 1, _Format, args);
		va_end(args);
		m_Logger->LogText(_Msg, log_trace);
	}
}

void CLogger::LogNormal(const char* _Format, ...)
{
	if (NULL != m_Logger) {
		char _Msg[512] = { 0 };
		va_list args;
		va_start(args, _Format);
		_vsnprintf(_Msg, sizeof(_Msg), _Format, args);
		va_end(args);
		m_Logger->LogText(_Msg, log_normal);
	}
}

void CLogger::LogText(const char* _Text,int _Type)
{
	if (m_LogFunc) {
		m_LogFunc(_Text, _Type);
	}
	else {
		printf("%s\n", _Text);
	}
}

void CLogger::SetLogFunction(std::function<void(const char*,int)>& _Func)
{
	m_LogFunc = _Func;
}