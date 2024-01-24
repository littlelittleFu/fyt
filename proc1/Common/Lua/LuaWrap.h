#ifndef __LUAWRAP__
#define __LUAWRAP__

#include "luabind/luabind.hpp"
#include "luabind/lua_include.hpp"
#include "luabind/object.hpp"

//////////////////////////////////////////////////////////////////////////
#define LUABIND_REGISTER_CLASS_BEGIN(luaScript, ClassName)                                                             \
    \
{                                                                                                               \
        lua_State *L = luaScript->GetCLuaState();                                                                       \
        if (!luabind::detail::class_registry::get_registry(L)) \
{                                                    \
            luabind::open(L);                                                                                          \
        \
}                                                                                                           \
        luabind::class_<ClassName> x(#ClassName);                                                                      \
        if (!luaScript->GetGlobalPointer(#ClassName)) \
{                                                              \
            x.def(luabind::constructor<>());                                                                           \
        \
}

#define LUABIND_REGISTER_CLASS_BEGIN_EX(luaScript, ClassName, BaseClassName)                                            \
    \
{                                                                                                               \
        lua_State *L = luaScript->GetCLuaState();                                                                       \
        if (!luabind::detail::class_registry::get_registry(L)) \
{                                                    \
            luabind::open(L);                                                                                          \
        \
}                                                                                                           \
        luabind::class_<ClassName, BaseClassName> x(#ClassName);                                                       \
        if (!luaScript->GetGlobalPointer(#ClassName)) \
{                                                              \
            x.def(luabind::constructor<>());                                                                           \
        \
}

#define LUABIND_REGISTER_CLASS_FUNC(ClassName, FuncName) x.def(#FuncName, &ClassName::FuncName);

#define LUABIND_REGISTER_CLASS_END(luaScript)                                                                          \
    luabind::module(L)[x];                                                                                             \
    \
}

#define LUABIND_GET_CLASS_OBJECT(luaScript, ClassName) (ClassName *) luaScript->GetGlobalPointer(#ClassName);

#define LUABIND_REGISTER_FUNCTION(luaScript, FuncName)                                                                 \
    \
{                                                                                                               \
        lua_State *L = luaScript->GetCLuaState();                                                                       \
        if (!luabind::detail::class_registry::get_registry(L)) \
{                                                    \
            luabind::open(L);                                                                                          \
        \
}                                                                                                           \
        if (!luaScript->GetGlobalPointer(#FuncName)) \
{                                                               \
            luabind::module(L)[luabind::def(#FuncName, &FuncName)];                                                    \
        \
}                                                                                                           \
    \
}

#define LUABIND_REGISTER_FUNCTION_EX(luaScript, ClassName, FuncName)                                                   \
    \
{                                                                                                               \
        lua_State *L = luaScript->GetCLuaState();                                                                       \
        if (!luabind::detail::class_registry::get_registry(L)) \
{                                                    \
            luabind::open(L);                                                                                          \
        \
}                                                                                                           \
        if (!luaScript->GetGlobalPointer(#FuncName)) \
{                                                               \
            luabind::module(L)[luabind::def(#FuncName, &ClassName::FuncName)];                                         \
        \
}                                                                                                           \
    \
}

#define LUABIND_REGISTER_MODULE_BEGIN(luaScript, ModuleName)                                                           \
    \
{                                                                                                               \
        lua_State *L = luaScript->GetCLuaState();                                                                       \
        if (!luabind::detail::class_registry::get_registry(L)) \
{                                                    \
            luabind::open(L);                                                                                          \
        \
}                                                                                                           \
        luabind::module(L, ModuleName) \
	[

#define LUABIND_REGISTER_MODULE_FUNC(ClassName, FuncName) luabind::def(#FuncName, &ClassName::FuncName)

#define LUABIND_REGISTER_MODULE_END()                                                                                  \
        ];                                                                                                             \
    \
}

#endif