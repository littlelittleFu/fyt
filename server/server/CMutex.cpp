#include "CMutex.h"

CMutex::CMutex()
{
	InitializeCriticalSection(&m_MutexID);
}

CMutex::~CMutex()
{
	DeleteCriticalSection(&m_MutexID);
}

void CMutex::Lock()
{
	EnterCriticalSection(&m_MutexID);
}

void CMutex::Unlock()
{
	LeaveCriticalSection(&m_MutexID);
}

CLockGuard::CLockGuard(CMutex& mutex) : m_Mutex(mutex)
{
	m_Mutex.Lock();
}

CLockGuard::~CLockGuard()
{
	m_Mutex.Unlock();
}