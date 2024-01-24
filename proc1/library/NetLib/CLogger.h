#pragma once
#include "Type.h"
#include <functional>

class ILogger
{
public:
	virtual void LogText(const char* _Text, int _Type) = 0;
};

class CLogger : public ILogger
{
private:
	CLogger();
	~CLogger();
	bool Init();
	void UnInit();

public:
	void SetLogger(ILogger* _Logger);

	void LogCritical(const char* _Format, ...);
	void LogWarning(const char* _Format, ...);
	void LogTrace(const char* _Format, ...);
	void LogNormal(const char* _Format, ...);

	void SetLogFunction(std::function<void(const char*,int)>& _Func);
protected:
	virtual void LogText(const char* _Text, int _Type);
	DECLARE_INSTANCE(CLogger)

private:
	ILogger* m_Logger;

	std::function<void(const char*,int)> m_LogFunc;

	enum {
        log_trace = 1,
		log_normal,
		log_warn,
		log_error,
	};
};
