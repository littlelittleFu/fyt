#include "stdafx.h"
#include "LuaAPI.h"
#include "LuaWrap.h"

void CLuaAPI::RegisterLuaAPI(CLuaScript* luaScript)
{
	LUABIND_REGISTER_CLASS_BEGIN(luaScript, CLuaAPI);

	LUABIND_REGISTER_CLASS_FUNC(CLuaAPI, Multiply);
	LUABIND_REGISTER_CLASS_FUNC(CLuaAPI, GetText);
	LUABIND_REGISTER_CLASS_FUNC(CLuaAPI, SetText);

	LUABIND_REGISTER_CLASS_END(luaScript);
}

int CLuaAPI::Multiply(int a, int b)
{
	return a * b;
}

std::string CLuaAPI::GetText()
{
	return m_Text;
}

void CLuaAPI::SetText(const std::string& str)
{
	m_Text = str;
}