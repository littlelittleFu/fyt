#include "pch.h"
#include "CMutex.h"

CMutex::CMutex()
{
}

CMutex::~CMutex()
{
}

void CMutex::Lock()
{
    m_Mutex.lock();
}

void CMutex::Unlock()
{
    m_Mutex.unlock();
}

CLockGuard::CLockGuard(CMutex& mutex) : m_Mutex(mutex)
{
    m_Mutex.Lock();
}

CLockGuard::~CLockGuard()
{
    m_Mutex.Unlock();
}
