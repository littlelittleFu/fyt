#pragma once

#include "LuaScript.h"
#include "ILogHelper.h"

template <class T, class TObj> inline bool IsLuaObjMatch(TObj _Obj) {
	if (luabind::type(_Obj) == LUA_TNIL) {
		return false;
	}
	if (CLuaType::GetType<T>() != LUA_TTABLE) {
		if (luabind::type(_Obj) != CLuaType::GetType<T>()) {
			return false;
		}
	}
	return true;
}

class CLuaEngine
{
protected:
	CLuaEngine();
	~CLuaEngine();

	DECL_SINGLETON(CLuaEngine)

public:
	void Init();
	void AddSearchPath(const std::string& path);

	bool RunLuaString(const string& luaString, const string& fileName);
	bool RunLuaFile(const string& luaFile);
	bool RunLuaBuffer(const void* buf, int bufSize);

	bool IsLuaFuncExist(const std::string& luaFunc);
    bool LoadLuaScripts(std::list<std::string> scripts);
    bool LoadLuaScripts(std::vector<std::string> scripts);

	CLuaScript* GetLuaScript();
	lua_State* GetLuaState();

private:
	CLuaScript* m_pLuaScript;
};

#define CLuaEngineMgr() CLuaEngine::GetInstance()
#define LuaCall CLuaEngine::GetInstance()->GetLuaScript()->TCall
#define LuaGlobalVar (luabind::globals(CLuaEngine::GetInstance()->GetLuaState()))
#define NewLuaObj() NewTable(CLuaEngine::GetInstance()->GetLuaScript())
#define LuaObj CLuaObject
#define LuaObjParam(x) CLuaValue(x, CLuaEngine::GetInstance()->GetLuaScript())
#define LuaRet (LuaGlobalVar["LuaRet"])//c++ ->lua
#define LuaArg (LuaGlobalVar["LuaArg"]) //lua->c++

//lua_State
#define LUA_SAFE_BEGIN() try {

#define LUA_SAFE_END(ret) \
} catch(...) { \
    LOG_ERROR("Luabind exception"); \
    return ret; \
}

template <typename... Args>
bool LuaBindCallVoid(const std::string &func, const Args&... params)
{
    if (func.empty()) return false;

    try {
        auto newFunc = func;
        auto pos = newFunc.find('.');
        if (pos != std::string::npos) {     // 加上 _G["."]
            newFunc.insert(pos, "\"]");
            newFunc.insert(0, "_G[\"");
        }

#ifdef __linux__
        newFunc = gbk_to_utf8(newFunc);
#endif

        if (CLuaEngineMgr()->RunLuaString("LuaCallFunc = " + newFunc, "") &&
            CLuaEngineMgr()->IsLuaFuncExist("LuaCallFunc")) {
            luabind::call_function<void>(CLuaEngineMgr()->GetLuaState(), "LuaCallFunc", params...);
        }
        else {
            LOG_ERROR("LuaBindCallVoid error. function %s not exist", newFunc.c_str());
            return false;
        }

        return true;
    } catch (std::exception &e) {
        LOG_ERROR("Lua function: %s, exception: %s", func.c_str(), e.what());
        return false;
    }
}

template <typename T, typename... Args>
bool LuaBindCallRet(T &ret, const std::string &func, const Args&... params)
{
    if (func.empty()) return false;

    try {
        auto newFunc = func;
        auto pos = newFunc.find('.');
        if (pos != std::string::npos) {     // 加上 _G["."]
            newFunc.insert(pos, "\"]");
            newFunc.insert(0, "_G[\"");
        }

#ifdef __linux__
        newFunc = gbk_to_utf8(newFunc);
#endif

        if (CLuaEngineMgr()->RunLuaString("LuaCallFunc = " + newFunc, "") &&
            CLuaEngineMgr()->IsLuaFuncExist("LuaCallFunc")) {
            ret = luabind::call_function<T>(CLuaEngineMgr()->GetLuaState(), "LuaCallFunc", params...);
        }
        else {
            LOG_ERROR("LuaBindCallRet error. function %s not exist", newFunc.c_str());
            return false;
        }

        return true;
    } catch (std::exception &e) {
        LOG_ERROR("Lua function: %s, exception: %s", func.c_str(), e.what());
        return false;
    }
}

template <typename... Args>
bool LuaBindCallExVoid(const CLuaObject &func, const Args&... params)
{
    try {
        if (luabind::type(func) != LUA_TFUNCTION) {
            LOG_ERROR("Not LUA_TFUNCTION");
            return false;
        }

        luabind::call_function<void>(func, params...);
        return true;
    } catch (std::exception &e) {
        LOG_ERROR("Exception: %s", e.what());
        return false;
    }
}

template <typename T, typename... Args>
bool LuaBindCallExRet(T &ret, const CLuaObject &func, const Args&... params)
{
    try {
        if (luabind::type(func) != LUA_TFUNCTION) {
            LOG_ERROR("Not LUA_TFUNCTION");
            return false;
        }

        ret = luabind::call_function<T>(func, params...);
        return true;
    } catch (std::exception &e) {
        LOG_ERROR("Exception: %s", e.what());
        return false;
    }
}

#define LUA_SCRIPT_FUNC(obj, func) (obj->GetScriptName() + std::string(".") + std::string(func)).c_str()

