#pragma once

#ifdef __linux__
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#else
#include <winsock2.h>
#include <windows.h>
#endif


#ifdef __linux__

#define _atoi64(str) strtoll(str, nullptr, 10)

#define _stricmp strcasecmp

#define _strnicmp strncasecmp

#define sprintf_s snprintf

#define sscanf_s sscanf

#define _countof(a) (sizeof(a) / sizeof(a[0]))

#define _vsnprintf vsnprintf

#define vsprintf_s vsnprintf

#define strtok_s strtok_r

#define TRUE true
#define FALSE false

inline void * memcpy_s(void *dst, size_t dstsz, const void *src, size_t count)
{
    if (!dst || !src) return dst;
    const size_t num = dstsz < count ? dstsz : count;
    return memcpy(dst, src, num);
}

#endif
