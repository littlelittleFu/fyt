#pragma once
// 内置类型和string
#define SETCASE(val, prop) case val: LuaRet = pConfig->prop; break
// 集合类型
#define SETCASE_SET(val, prop) case val:	            \
{                                       	            \
    CLuaObject luaRet = NewLuaObj();	                \
    int32_t i = 1;	                                    \
    auto iter = pConfig->prop.begin();	                \
    for (; iter != pConfig->prop.end(); ++iter)	        \
    {                                                   \
        luaRet[i++] = *iter;	                        \
    }                                           	    \
    LuaRet = luaRet;                                    \
}	                                                    \
break;

#define SETCASE_VECTOR(val, prop)   SETCASE_SET(val, prop)

// 字典类型,k,v(内置、string类型)
#define SETCASE_MAP(val, prop) case val:	            \
{                                       	            \
    CLuaObject luaRet = NewLuaObj();        	        \
    auto iter = pConfig->prop.begin();                  \
    for (; iter != pConfig->prop.end(); ++iter)         \
    {                                   	            \
        luaRet[iter->first] = iter->second; 	        \
    }                                                   \
    LuaRet = luaRet;    	                            \
}                                                       \
break;

// 字典类型,k,v(pair类型)
#define SETCASE_MAP_PAIR(val, prop) case val:	        \
{                                       	            \
    CLuaObject luaRet = NewLuaObj();        	        \
    auto iter = pConfig->prop.begin();                  \
    for (; iter != pConfig->prop.end(); ++iter)         \
    {                                   	            \
        CLuaObject luaTable = NewLuaObj();              \
        luaTable[1] = iter->second.first;               \
        luaTable[2] = iter->second.second;              \
        luaRet[iter->first] = luaTable; 	            \
    }                                                   \
    LuaRet = luaRet;    	                            \
}                                                       \
break;

// 字典类型,k,v(vector类型)
#define SETCASE_MAP_VECTOR(val, prop) case val:	        \
{                                       	            \
    CLuaObject luaRet = NewLuaObj();        	        \
    auto iter = pConfig->prop.begin();                  \
    for (; iter != pConfig->prop.end(); ++iter)         \
    {                                   	            \
        int32_t i = 1;                                  \
        CLuaObject luaTable = NewLuaObj();              \
        auto it = iter->second.begin();                 \
        for (;it != iter->second.end();++ it)           \
            luaTable[i++] = *it;                        \
        luaRet[iter->first] = luaTable; 	            \
    }                                                   \
    LuaRet = luaRet;    	                            \
}                                                       \
break;