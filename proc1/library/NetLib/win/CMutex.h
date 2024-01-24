#pragma once
#include <windows.h>
class CMutex
{
public:
	CMutex();
	~CMutex();

	void Lock();
	void Unlock();

private:
	CRITICAL_SECTION m_MutexID;
};

class CLockGuard
{
public:
    CLockGuard(CMutex &mutex);
    ~CLockGuard();

private:
    CMutex &m_Mutex;
};
