#include "stdafx.h"
#include "LuaEngine.h"



IMPL_SINGLETON(CLuaEngine)

CLuaEngine::CLuaEngine() : m_pLuaScript(nullptr)
{

}

CLuaEngine::~CLuaEngine()
{
	SAFE_RELEASE(m_pLuaScript);
}

void CLuaEngine::Init()
{
	SAFE_RELEASE(m_pLuaScript);
	m_pLuaScript = new CLuaScript;
}

void CLuaEngine::AddSearchPath(const std::string& path)
{
	std::string searchPath = path;
	if (nullptr != m_pLuaScript) {
		m_pLuaScript->SetLuaPath(searchPath);
	}
}

bool CLuaEngine::RunLuaString(const string& luaString, const string& fileName)
{
	if (nullptr != m_pLuaScript) {
		return m_pLuaScript->ExecuteString(luaString, fileName.empty() ? nullptr : fileName.c_str());
	}
	return false;
}

bool CLuaEngine::RunLuaFile(const string& luaFile)
{
	if (nullptr != m_pLuaScript) {
		return m_pLuaScript->ExecuteFile(luaFile.c_str());
	}
	return false;
}

bool CLuaEngine::RunLuaBuffer(const void* buf, int bufSize)
{
	if ((nullptr != m_pLuaScript) && (nullptr != buf) && (bufSize > 0)) {
		return m_pLuaScript->ExecuteBuffer(buf, bufSize);
	}
	return false;
}

CLuaScript* CLuaEngine::GetLuaScript()
{
	return m_pLuaScript;
}

lua_State* CLuaEngine::GetLuaState()
{
	if (nullptr != m_pLuaScript) {
		return m_pLuaScript->GetCLuaState();
	}
	return nullptr;
}

bool CLuaEngine::IsLuaFuncExist(const std::string& luaFunc)
{
    auto ary = str_split(luaFunc, ".");

    auto obj = luabind::globals(GetLuaState());

    for (auto it = ary.begin(); it != ary.end(); ++it) {

        const auto &s = *it;
        obj = obj[s];

        if (it == ary.end() - 1) {
            return (luabind::type(obj) == LUA_TFUNCTION);
        }

        if (luabind::type(obj) != LUA_TTABLE) return false;
    }
	return false;
}

bool CLuaEngine::LoadLuaScripts(std::list<std::string> scripts)
{
    char buf[256];
    bool result = true;

    for (auto &script : scripts) {

        auto pos = script.find_last_of("/\\");
        if (pos != std::string::npos) script = script.erase(0, pos + 1);

        pos = script.find_last_of('.');
        if (pos != std::string::npos) script = script.erase(pos);

        sprintf_s(buf, _countof(buf), R"(package.loaded["%s"] = nil; require "%s")", script.c_str(), script.c_str());

        if (!RunLuaBuffer(buf, strlen(buf))) result = false;
    }

    return result;
}

bool CLuaEngine::LoadLuaScripts(std::vector<std::string> scripts)
{
    std::list<std::string> l;
    std::move(scripts.begin(), scripts.end(), std::back_inserter(l));
    return LoadLuaScripts(std::move(l));
}
