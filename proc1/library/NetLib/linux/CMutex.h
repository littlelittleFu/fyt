#pragma once

#include <mutex>

class CMutex
{
public:
    CMutex();
    ~CMutex();

    void Lock();
    void Unlock();

private:
    std::mutex m_Mutex;
};

class CLockGuard
{
public:
    CLockGuard(CMutex &mutex);
    ~CLockGuard();

private:
    CMutex &m_Mutex;
};
