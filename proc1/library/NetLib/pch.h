#pragma once

#include <stdint.h>
#include <stdlib.h>

#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <memory>
#include <thread>
#include <cstring>
#include <atomic>

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

#include <PortToLinux.h>
#include <AES.h>

#include "Types.h"
#include "CLogger.h"

#include "ISessionFactory.h"

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define DECFORMAT(format) "[" __FILE__ ":" STR(__LINE__) "] " format

#define LOG_ERROR(format, ...) CLogger::GetInstance()->LogCritical(DECFORMAT(format), ##__VA_ARGS__)
#define LOG_WARN(format, ...) CLogger::GetInstance()->LogWarning(DECFORMAT(format), ##__VA_ARGS__)
#define LOG_TRACE(format, ...) CLogger::GetInstance()->LogTrace(DECFORMAT(format), ##__VA_ARGS__)
#define LOG_NORMAL(format, ...) CLogger::GetInstance()->LogNormal(DECFORMAT(format), ##__VA_ARGS__)
