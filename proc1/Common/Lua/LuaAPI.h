#pragma once
#include <string>
#include "LuaScript.h"

class CLuaAPI
{
public:
	void RegisterLuaAPI(CLuaScript* luaScript);

	int Multiply(int a, int b);
	std::string GetText();
	void SetText(const std::string& str);

private:
	std::string m_Text;
};
