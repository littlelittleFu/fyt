#pragma once

#include <string>
#include <memory>

#define DECL_SINGLETON(CLASS)\
protected:\
static CLASS* m_instance;\
public:\
static CLASS* GetInstance();

#define IMPL_SINGLETON(CLASS)\
CLASS* CLASS::m_instance = nullptr;\
CLASS* CLASS::GetInstance(){\
	if(m_instance == nullptr){\
		m_instance = new CLASS();\
	}\
	return m_instance;\
}

#define DECLARE_SINGLETON(cls) \
private: \
    static std::unique_ptr<cls> mInstance; \
public: \
    static bool CreateInstance() \
    { \
        if (!mInstance) mInstance = std::make_unique<cls>(); \
        return mInstance != nullptr; \
    } \
    static cls* Instance() { return mInstance.get(); } \
	static void DestoryInstance() { mInstance.release(); }

#define INSTANCE_SINGLETON(cls) std::unique_ptr<cls> cls::mInstance;

#define SAFE_RELEASE(x)         {if(nullptr != x){delete x;x = nullptr;}}
#define SAFE_RELEASE_ARRAY(x)   {if(nullptr != x){delete[] x;x = nullptr;}}

#define SAFE_FREE(x)			{if(nullptr != x){free(x);x = nullptr;}}

#if defined(_WIN64)
typedef signed __int64 ssize_t;
#else
#if defined(_WIN32)
typedef signed int ssize_t;
#endif
#endif

#ifndef _DEBUG
#define SAFE_BEGIN	try {
#define SAFE_END	} catch(...) {\
	LOG_ERROR("捕获到了异常");\
}
#define SAFE_BEGIN_EX	try {

#define SAFE_END_EX(ret)		}\
catch(const std::exception& e) {\
	LOG_ERROR("捕获到了异常: %s", e.what());\
    return ret;\
}\
catch(...) {\
	LOG_ERROR("捕获到了异常");\
    return ret;\
}
#else
#define SAFE_BEGIN
#define SAFE_END
#define SAFE_BEGIN_EX
#define SAFE_END_EX(ret)
#endif

static const std::string EMPTYSTR;
