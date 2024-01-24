#pragma once
#include <stdint.h>
#include <map>

#define FUNC_LINE __FUNCTION__,__LINE__

// 释放指针宏
#define RELEASE(x)         {if(NULL != x){delete x;x = NULL;}}
//释放指针数组宏
#define RELEASE_ARRAY(x)   {if(NULL != x){delete[] x;x = NULL;}}
// 释放句柄宏
#define RELEASE_HANDLE(x)  {if(NULL != x && INVALID_HANDLE_VALUE != x){ CloseHandle(x);x = NULL;}}
// 释放Socket宏
#ifdef _WIN32
#define RELEASE_SOCKET(x)  {if(INVALID_SOCKET != x) { closesocket(x);x = INVALID_SOCKET;}}
#else
#define RELEASE_SOCKET(x)  {if(INVALID_SOCKET != x) { close(x);x = INVALID_SOCKET;}}
#endif
// 传递给Worker线程的退出信号
#define EXIT_CODE            NULL

#define MSG_BUFFER_DATA(type, msg) char* p##msg = nullptr;\
uint32_t msgSize = sizeof(type);\
CBufPoolManager::GetInstance()->GetBuffer(p##msg, msgSize, true);\
type& msg = *((type*)p##msg);\
msg.Clear();

#ifdef __linux__
typedef int32_t INT;
typedef uint32_t UINT;
typedef uint32_t DWORD;
#define SOCKET int
#define INVALID_SOCKET -1
#endif

//客户端最大连接数
#define MAX_CONNECTION	10000

#define SOCK_ERROR_OVERFLOW			10000		//缓冲区溢出

#define SESSION_TYPE_INVALID		-1

#define DECLARE_INSTANCE(cls)			\
public:									\
	static cls* GetInstance()			\
	{									\
		if(NULL == m_Instance){			\
			m_Instance = new cls;		\
		}								\
		return m_Instance;				\
	}									\
private:								\
	static cls* m_Instance;	

#define IMPLEMENT_INSTANCE(cls)		\
cls* cls::m_Instance = NULL;

struct DEBUG_DATA
{
    struct cache_value
    {
        uint64_t msgNum = 0;
        uint64_t msgMem = 0;
    };
	uint32_t sendCache = 0;
	uint64_t sendMem = 0;
	uint32_t sendPeak = 0;
	uint32_t recvCache = 0;
	uint64_t recvMem = 0;
	uint32_t recvPeak = 0;

	uint32_t buffIdleCache = 0;
	uint64_t buffIdleMem = 0;
	uint32_t buffIdlePeak = 0;
	uint32_t buffBusyCache = 0;
	uint64_t buffBusyMem = 0;
	uint32_t buffBusyPeak = 0;

    std::map<uint32_t, cache_value> sendMsgMap;    // id -> <num, Bytes>
    std::map<uint32_t, cache_value> recvMsgMap;

    std::string GenSendMsgInfo()
    {
        return GenMsgInfo(sendMsgMap);
    }

    std::string GenRecvMsgInfo()
    {
        return GenMsgInfo(recvMsgMap);
    }

    std::string GenMsgInfo(const std::map<uint32_t, cache_value> &msgMap)
    {
        char buf[128] = { 0 };
        std::string info;

        for (const auto &it : msgMap) {
            if (!it.second.msgNum) continue;
            sprintf_s(buf, _countof(buf), "msg: %lu, num: %llu, mem: %llu, avg: %llu",
                it.first, it.second.msgNum, it.second.msgMem, (uint64_t)it.second.msgMem / it.second.msgNum);
            if (!info.empty()) info += "\n";
            info += buf;
        }

        return info;
    }
};
