#include "stdafx.h"
#include "LuaScript.h"
#include <mutex>

#include "IFileHelper.h"

std::mutex g_MutexPrint; // 互斥量,用来互斥地输出信息
std::mutex g_MutexError; // 互斥量,用来互斥地输出整块错误信息

#define DEBUG_ERR_BUFF_LEN 1024
char LUA_DEBUG_ERR_BUFF[DEBUG_ERR_BUFF_LEN] = {0};

extern "C" {
#include "lualib.h"

// used for luaB_print
LuaScriptOutputFunc g_pPrintFunc = (LuaScriptOutputFunc)fputs;
}

int LuaPCallErrPrint(lua_State *L) {
    std::unique_lock<std::mutex> lk(g_MutexError);
    CLuaState _Temp(L);
    CLuaScript *_pLuaScriptObj = (CLuaScript *)_Temp.GetGlobalPointer("CLuaScriptPtr");
    string _CurFileName;
    string _CurFuncName;
    if (_pLuaScriptObj) {
        _CurFileName = _pLuaScriptObj->GetLuaFileName();
        _CurFuncName = _pLuaScriptObj->GetCurFuncName();
        string _Msg;
        if (!_CurFuncName.empty()) {
            _Msg += string("Function:(") + _CurFuncName + ")";
        }
        if (!_CurFileName.empty()) {
            if (!_Msg.empty()) {
                _Msg += ", ";
            }
            _Msg += string("File:") + _CurFileName;
        }
        if (!_Msg.empty()) {
            LOG_ERROR("[LuaErr] %s", _Msg.c_str());
        }
    }
    const char *msg = lua_tostring(L, -1);
    lua_pop(L, 1);
    LOG_ERROR("[LuaErr] ErrorCode:(%d), ErrorMsg,%s", 0xff, msg);
    lua_Debug ar;
    if (lua_getstack(L, 0, &ar)) /* no stack frame? */
    {
        lua_getinfo(L, "lnS", &ar);
        LOG_ERROR("[LuaErr] FunctionType(%s), Function(%s): short_src,%s", ar.what, ar.name, ar.short_src);

        for (int i = 1; i < 10; ++i) {
            if (lua_getstack(L, i, &ar)) /* no stack frame? */
            {
                lua_getinfo(L, "lnS", &ar);
                LOG_ERROR("[LuaErr] Stack %d: FunctionType(%s),Function(%s),Line(%d): %s",
                          i, ar.what, ar.name, ar.currentline, ar.short_src);
            } else
                break;
        }
    }
    LOG_ERROR("-----------------------------------------------------\r\n");
    return 0;
}

void LuaErrorLog(int err, const char *info, const char *msg) {
    std::unique_lock<std::mutex> lk(g_MutexError);
    LOG_ERROR("\r\n-----------------------------------------------------");
    if (info && strlen(info) > 0) {
        LOG_ERROR("%s", info);
    }
    LOG_ERROR("[LuaErr] ErrorCode:(%d),ErrorMsg,%s", err, msg);
    LOG_ERROR("-----------------------------------------------------\r\n");
}

static pcall_errfunc g_pLuaPCallErrFunc = LuaPCallErrPrint;
static LuaScriptErrorFunc g_pLuaErrorFunc = LuaErrorLog;

void LuaScriptSetPCallErrfunc(pcall_errfunc func) { g_pLuaPCallErrFunc = func; }

void LuaScriptSetErrorFunction(LuaScriptErrorFunc func) { g_pLuaErrorFunc = func; }

void LuaScriptSetOutputFunction(LuaScriptOutputFunc func) { g_pPrintFunc = func; }

CLuaObject NewTable(CLuaScript *pLuaScript) {
    if (nullptr != pLuaScript && nullptr != pLuaScript->GetCLuaState()) {
        return luabind::newtable(pLuaScript->GetCLuaState());
    } else {
        return CLuaObject();
    }
}

// CLuaValue
void CLuaValue::Release() {
    if (m_LuaValType == LUA_TSTRING) {
        if (m_pString) {
            free(m_pString);
            m_pString = 0;
        }
    } else if (m_LuaValType == LUA_TTABLE) {
        if (m_pTable) {
            delete m_pTable;
            m_pTable = 0;
        }
    }
}

int CLuaValue::GetInt() const {
    if (m_LuaValType == LUA_TNUMBER)
        return (int)(int64_t)m_LuaNumber;
    else {
        return 0;
    }
}

int64_t CLuaValue::GetInt64() const {
    if (m_LuaValType == LUA_TNUMBER)
        return (int64_t)(uint64_t)m_LuaNumber;
    else {
        return 0;
    }
}

bool CLuaValue::GetBool() const {
    if (m_LuaValType == LUA_TBOOLEAN)
        return m_LuaNumber != 0;
    else {
        return false;
    }
}

float CLuaValue::GetFloat() const {
    if (m_LuaValType == LUA_TNUMBER)
        return (float)m_LuaNumber;
    else {
        return 0;
    }
}

double CLuaValue::GetDouble() const {
    if (m_LuaValType == LUA_TNUMBER)
        return m_LuaNumber;
    else {
        return 0;
    }
}

const char *CLuaValue::GetString() const {
    if (m_LuaValType == LUA_TSTRING)
        return m_pString;
    else {
        return "";
    }
}

const wchar_t *CLuaValue::GetWString() const {
    if (m_LuaValType == LUA_TSTRING)
        return (const wchar_t *)m_pString;
    else {
        return L"";
    }
}

void *CLuaValue::GetPointer() const {
    if (m_LuaValType == LUA_TLIGHTUSERDATA)
        return m_Pointer;
    else
        return 0;
}

void CLuaValue::Set(const char *value) {
    Release();
    m_LuaValType = LUA_TSTRING;
#ifdef _WIN32
    m_pString = _strdup(value);
#else
    m_pString = strdup(value);
#endif
}

void CLuaValue::Set(const wchar_t *value) {
    Release();
    m_LuaValType = LUA_TSTRING;
    // m_pString = (char *)wcsdup((const wchar_t *)value);
    size_t len = wcslen(value) + 1;
    wchar_t *copy = (wchar_t *)malloc(len * sizeof(wchar_t));
    if (copy) {
        wmemcpy(copy, value, len);
    }

    m_pString = (char *)copy;
}

void CLuaValue::Set(const CLuaValue &value) {
    switch (value.m_LuaValType) {
    case LUA_TNUMBER:
        Set(value.GetDouble());
        break;
    case LUA_TBOOLEAN:
        Set(value.GetBool());
        break;
    case LUA_TSTRING:
        Set(value.GetString());
        break;
    case LUA_TTABLE:
        Set(value.GetTable());
        break;
    case LUA_TLIGHTUSERDATA:
        SetPointer(value.GetPointer());
        break;
    default:
        SetNil();
        break;
    }
    m_pCLuaState = value.m_pCLuaState;
}

void CLuaValue::Set(const CLuaTable &value) {
    Release();
    m_LuaValType = LUA_TTABLE;
    m_pTable = new CLuaTable;
    *m_pTable = value;
}

void CLuaValue::Set(const CLuaObject &value) {
    Release();

    if (luabind::type(value) == LUA_TTABLE) {
        m_LuaValType = LUA_TTABLE;
        m_pTable = new CLuaTable;

        string strKey = "";
        string strVal = "";
        int iKey = 0;
        double dVal = 0;

        luabind::iterator iter(value), end;
        for (; iter != end; iter++) {
            luabind::adl::object objKey = iter.key();
            luabind::adl::object objVal = *iter;

            //
            if (luabind::type(objKey) == LUA_TSTRING) {
                strKey = luabind::object_cast<string>(objKey);

                if (luabind::type(objVal) == LUA_TSTRING) {
                    strVal = luabind::object_cast<string>(objVal);
                    (*m_pTable)[strKey.c_str()] = strVal.c_str();
                } else if (luabind::type(objVal) == LUA_TNUMBER) {
                    dVal = luabind::object_cast<double>(objVal);
                    (*m_pTable)[strKey.c_str()] = dVal;
                }
            } else if (luabind::type(objKey) == LUA_TNUMBER) {
                iKey = luabind::object_cast<int>(objKey);

                if (luabind::type(objVal) == LUA_TSTRING) {
                    strVal = luabind::object_cast<string>(objVal);
                    (*m_pTable)[iKey] = strVal.c_str();
                } else if (luabind::type(objVal) == LUA_TNUMBER) {
                    dVal = luabind::object_cast<double>(objVal);
                    (*m_pTable)[iKey] = dVal;
                }
            }
        }
    }
}

static CLuaTable g_NullTable;
CLuaTable &CLuaValue::GetTable() const {
    if (m_LuaValType == LUA_TTABLE)
        return *m_pTable;
    else
        return g_NullTable;
}

bool CLuaValue::operator<(const CLuaValue &r) const {
    if (m_LuaValType == r.m_LuaValType) {
        switch (m_LuaValType) {
        case LUA_TNONE:
            return false;
        case LUA_TNIL:
            return false;
        case LUA_TBOOLEAN:
        case LUA_TNUMBER:
            return m_LuaNumber < r.m_LuaNumber;
        case LUA_TSTRING:
            return strcmp(m_pString, r.m_pString) < 0;
        case LUA_TTABLE:
            return false;
        case LUA_TLIGHTUSERDATA:
        case LUA_TFUNCTION:
        case LUA_TUSERDATA:
        case LUA_TTHREAD:
            return m_Pointer < r.m_Pointer;
        }
        return false;
    } else {
        return m_LuaValType < r.m_LuaValType;
    }
}

// CLuaState
CLuaState::CLuaState() {
    m_pLuaState = 0;
    m_pErrorFunc = g_pLuaErrorFunc;
}

CLuaState::~CLuaState() {}

void CLuaState::SetErrorFunction(LuaScriptErrorFunc func) { m_pErrorFunc = func; }

void CLuaState::SetGlobal(const char *name, int value) {
    Push(value);
    lua_setglobal(m_pLuaState, name);
}

void CLuaState::SetGlobal(const char *name, int64_t value) {
    Push(value);
    lua_setglobal(m_pLuaState, name);
}

void CLuaState::SetGlobal(const char *name, bool value) {
    Push(value);
    lua_setglobal(m_pLuaState, name);
}

void CLuaState::SetGlobal(const char *name, float value) {
    Push(value);
    lua_setglobal(m_pLuaState, name);
}

void CLuaState::SetGlobal(const char *name, double value) {
    Push(value);
    lua_setglobal(m_pLuaState, name);
}

void CLuaState::SetGlobal(const char *name, const char *value) {
    Push(value);
    lua_setglobal(m_pLuaState, name);
}

void CLuaState::SetGlobal(const char *name, const wchar_t *value) {
    Push(value);
    lua_setglobal(m_pLuaState, name);
}

void CLuaState::SetGlobal(const char *name, const CLuaTable &value) {
    Push(value);
    lua_setglobal(m_pLuaState, name);
}

void CLuaState::SetGlobalPointer(const char *name, void *value) {
    PushPointer(value);
    lua_setglobal(m_pLuaState, name);
}

void CLuaState::SetGlobalNil(const char *name) {
    PushNil();
    lua_setglobal(m_pLuaState, name);
}

bool CLuaState::GetGlobal(const char *name, int &value) {
    lua_getglobal(m_pLuaState, name);
    bool typeMatch = lua_type(m_pLuaState, -1) == LUA_TNUMBER;
    if (typeMatch)
        Pop(value);
    else
        Pop();
    return typeMatch;
}

bool CLuaState::GetGlobal(const char *name, int64_t &value) {
    lua_getglobal(m_pLuaState, name);
    bool typeMatch = lua_type(m_pLuaState, -1) == LUA_TNUMBER;
    if (typeMatch)
        Pop(value);
    else
        Pop();
    return typeMatch;
}

bool CLuaState::GetGlobal(const char *name, bool &value) {
    lua_getglobal(m_pLuaState, name);
    bool typeMatch = lua_type(m_pLuaState, -1) == LUA_TBOOLEAN;
    if (typeMatch)
        Pop(value);
    else
        Pop();
    return typeMatch;
}

bool CLuaState::GetGlobal(const char *name, float &value) {
    lua_getglobal(m_pLuaState, name);
    bool typeMatch = lua_type(m_pLuaState, -1) == LUA_TNUMBER;
    if (typeMatch)
        Pop(value);
    else
        Pop();
    return typeMatch;
}

bool CLuaState::GetGlobal(const char *name, double &value) {
    lua_getglobal(m_pLuaState, name);
    bool typeMatch = lua_type(m_pLuaState, -1) == LUA_TNUMBER;
    if (typeMatch)
        Pop(value);
    else
        Pop();
    return typeMatch;
}

bool CLuaState::GetGlobal(const char *name, string &value) {
    lua_getglobal(m_pLuaState, name);
    bool typeMatch = lua_type(m_pLuaState, -1) == LUA_TSTRING;
    if (typeMatch)
        Pop(value);
    else
        Pop();
    return typeMatch;
}

bool CLuaState::GetGlobal(const char *name, std::wstring &value) {
    lua_getglobal(m_pLuaState, name);
    bool typeMatch = lua_type(m_pLuaState, -1) == LUA_TSTRING;
    if (typeMatch)
        Pop(value);
    else
        Pop();
    return typeMatch;
}

bool CLuaState::GetGlobal(const char *name, CLuaTable &value) {
    lua_getglobal(m_pLuaState, name);
    bool typeMatch = lua_type(m_pLuaState, -1) == LUA_TTABLE;
    if (typeMatch)
        Pop(value);
    else
        Pop();
    return typeMatch;
}

bool CLuaState::GetGlobalPointer(const char *name, void *&value) {
    lua_getglobal(m_pLuaState, name);
    bool typeMatch = lua_type(m_pLuaState, -1) == LUA_TLIGHTUSERDATA;
    if (typeMatch)
        PopPointer(value);
    else
        Pop();
    return typeMatch;
}

bool CLuaState::IsGlobalNil(const char *name) {
    lua_getglobal(m_pLuaState, name);
    bool isNil = lua_isnil(m_pLuaState, -1);
    Pop();
    return isNil;
}

int CLuaState::GetGlobalInt(const char *name) {
    lua_getglobal(m_pLuaState, name);
    return PopInt();
}

int64_t CLuaState::GetGlobalInt64(const char *name) {
    lua_getglobal(m_pLuaState, name);
    return PopInt();
}

bool CLuaState::GetGlobalBool(const char *name) {
    lua_getglobal(m_pLuaState, name);
    return PopBool();
}

float CLuaState::GetGlobalFloat(const char *name) {
    lua_getglobal(m_pLuaState, name);
    return PopFloat();
}

double CLuaState::GetGlobalDouble(const char *name) {
    lua_getglobal(m_pLuaState, name);
    return PopDouble();
}

const char *CLuaState::GetGlobalString(const char *name) {
    lua_getglobal(m_pLuaState, name);
    return PopString();
}

const wchar_t *CLuaState::GetGlobalWString(const char *name) {
    lua_getglobal(m_pLuaState, name);
    return PopWString();
}

CLuaTable CLuaState::GetGlobalTable(const char *name) {
    lua_getglobal(m_pLuaState, name);
    return PopTable();
}

void *CLuaState::GetGlobalPointer(const char *name) {
    lua_getglobal(m_pLuaState, name);
    return PopPointer();
}

void CLuaState::PushNil() { lua_pushnil(m_pLuaState); }

void CLuaState::Push(int value) { lua_pushnumber(m_pLuaState, (unsigned int)value); }

void CLuaState::Push(int64_t value) { lua_pushnumber(m_pLuaState, (uint64_t)value); }

void CLuaState::Push(bool value) { lua_pushboolean(m_pLuaState, (int)value); }

void CLuaState::Push(float value) { lua_pushnumber(m_pLuaState, value); }

void CLuaState::Push(double value) { lua_pushnumber(m_pLuaState, value); }

void CLuaState::Push(const char *value) { lua_pushstring(m_pLuaState, value); }

void CLuaState::Push(const wchar_t *value) { lua_pushlstring(m_pLuaState, (const char *)value, wcslen(value) * 2); }

void CLuaState::Push(const string &value) { lua_pushlstring(m_pLuaState, value.c_str(), value.size()); }

void CLuaState::PushPointer(void *value) { lua_pushlightuserdata(m_pLuaState, value); }

void CLuaState::Push(const CLuaValue &value) {
    switch (value.GetType()) {
    case LUA_TNUMBER:
        Push(value.GetDouble());
        break;
    case LUA_TSTRING:
        Push(value.GetString());
        break;
    case LUA_TBOOLEAN:
        Push(value.GetBool());
        break;
    case LUA_TTABLE:
        Push(value.GetTable());
        break;
    case LUA_TLIGHTUSERDATA:
        PushPointer(value.GetPointer());
        break;
    default:
        PushNil();
        break;
    }
}

void CLuaState::Push(const CLuaTable &value) {
    lua_newtable(m_pLuaState);
    CLuaTable::const_iterator itr = value.begin();
    while (itr != value.end()) {
        Push(itr->first);
        Push(itr->second);
        lua_settable(m_pLuaState, -3);
        ++itr;
    }
}

void CLuaState::Pop() { lua_pop(m_pLuaState, 1); }

void CLuaState::Pop(int &value) {
    value = (int)(unsigned int)lua_tonumber(m_pLuaState, -1);
    lua_pop(m_pLuaState, 1);
}

void CLuaState::Pop(int64_t &value) {
    value = (int64_t)(uint64_t)lua_tonumber(m_pLuaState, -1);
    lua_pop(m_pLuaState, 1);
}

void CLuaState::Pop(bool &value) {
    value = lua_toboolean(m_pLuaState, -1) != 0;
    lua_pop(m_pLuaState, 1);
}

void CLuaState::Pop(float &value) {
    value = (float)lua_tonumber(m_pLuaState, -1);
    lua_pop(m_pLuaState, 1);
}

void CLuaState::Pop(double &value) {
    value = lua_tonumber(m_pLuaState, -1);
    lua_pop(m_pLuaState, 1);
}

void CLuaState::Pop(string &value) {
    const char *s = lua_tostring(m_pLuaState, -1);
    if (s)
        value = s;
    else
        value = "";
    lua_pop(m_pLuaState, 1);
}

void CLuaState::PopPointer(void *&value) {
    value = lua_touserdata(m_pLuaState, -1);
    lua_pop(m_pLuaState, 1);
}

void CLuaState::Pop(std::wstring &value) {
    const wchar_t *s = (const wchar_t *)lua_tostring(m_pLuaState, -1);
    if (s)
        value = (const wchar_t *)s;
    else
        value = L"";
    lua_pop(m_pLuaState, 1);
}

void CLuaState::Pop(CLuaValue &value, int eExpectType) {
    switch (lua_type(m_pLuaState, -1)) {
    case LUA_TNUMBER:
        value.Set(PopDouble());
        break;
    case LUA_TBOOLEAN:
        value.Set(PopBool());
        break;
    case LUA_TSTRING:
        value.Set(PopString());
        break;
    case LUA_TTABLE:
        value.Set(PopTable());
        break;
    case LUA_TUSERDATA:
    case LUA_TLIGHTUSERDATA:
        value.SetPointer(PopPointer());
        break;
    default:
        value.SetNil();
        Pop();
        break;
    }

    if (value.m_LuaValType != eExpectType) {
        char _ErrMsg[64] = {0};
        snprintf(_ErrMsg, sizeof(_ErrMsg) - 1, "函数返回类型不匹配！");
        if (nullptr != g_pLuaErrorFunc) {
            g_pLuaErrorFunc(0xff, "", _ErrMsg);
        }
    }
}

void CLuaState::Pop(CLuaTable &value) {
    if (lua_istable(m_pLuaState, -1)) {
        lua_pushnil(m_pLuaState);
        while (lua_next(m_pLuaState, -2) != 0) {
            switch (lua_type(m_pLuaState, -2)) {
            case LUA_TNUMBER:
                value[lua_tonumber(m_pLuaState, -2)] = PopValue();
                break;
            case LUA_TBOOLEAN:
                value[lua_toboolean(m_pLuaState, -2) != 0] = PopValue();
                break;
            case LUA_TSTRING:
                value[lua_tostring(m_pLuaState, -2)] = PopValue();
                break;
            case LUA_TUSERDATA:
            case LUA_TLIGHTUSERDATA: {
                CLuaValue v(this);
                v.SetPointer(lua_touserdata(m_pLuaState, -2));
                value[v] = PopValue();
            } break;
            default:
                // not supported
                assert(false);
                break;
            }
        }
    }
    lua_pop(m_pLuaState, 1);
}

const char *CLuaState::PopString() {
    const char *value = lua_tostring(m_pLuaState, -1);
    lua_pop(m_pLuaState, 1);
    if (value)
        return value;
    else
        return "";
}

const wchar_t *CLuaState::PopWString() {
    const wchar_t *value = (const wchar_t *)lua_tostring(m_pLuaState, -1);
    lua_pop(m_pLuaState, 1);
    if (value)
        return value;
    else
        return L"";
}

CLuaValue CLuaState::PopValue() {
    switch (lua_type(m_pLuaState, -1)) {
    case LUA_TNUMBER:
        return CLuaValue(PopDouble(), this);
    case LUA_TBOOLEAN:
        return CLuaValue(PopBool(), this);
    case LUA_TSTRING:
        return CLuaValue(PopString(), this);
    case LUA_TTABLE:
        return CLuaValue(PopTable(), this);
    case LUA_TUSERDATA:
    case LUA_TLIGHTUSERDATA: {
        CLuaValue v(this);
        v.SetPointer(PopPointer());
        return v;
    }
    default:
        return CLuaValue(this);
    }
}

CLuaTable CLuaState::PopTable() {
    CLuaTable table;
    Pop(table);
    return table;
}

int CLuaState::GetStackTop() { return lua_gettop(m_pLuaState); }

void CLuaState::NewTable() { lua_newtable(m_pLuaState); }

void CLuaState::SetTable(int idx) { lua_settable(m_pLuaState, idx); }

void CLuaState::GetTable(int idx) { lua_gettable(m_pLuaState, idx); }

void CLuaState::HandleError(int err) {
    if (err != 0) {
        const char *msg = lua_tostring(m_pLuaState, -1);
        Pop();
        if (m_pErrorFunc) {
            string info = GetCurFuncName();
            if (info.empty()) {
                info = GetLuaFileName();
            }
            m_pErrorFunc(err, info.c_str(), msg);
        }
        // throw CLuaException(this, err, msg);
    }
    SetLuaFileName("");
    SetCurFuncName("");
}

string CLuaState::toString(int eType) {
    switch (eType) {
    case LUA_TNONE:
        return "NONE";
    case LUA_TNIL:
        return "NIL";
    case LUA_TBOOLEAN:
        return "BOOLEAN";
    case LUA_TLIGHTUSERDATA:
        return "LIGHTUSERDATA";
    case LUA_TNUMBER:
        return "NUMBER";
    case LUA_TSTRING:
        return "STRING";
    case LUA_TTABLE:
        return "TABLE";
    default:
        return "OTHER";
    }
}

// CLuaThread
bool CLuaThread::IsDead() {
    lua_Debug ar;
    if (lua_getstack(m_pLuaState, 0, &ar) == 0 && lua_gettop(m_pLuaState) == 0)
        return true;
    else
        return false;
}

bool CLuaThread::Resume() {
    int err = lua_resume(m_pLuaState, 0);
    HandleError(err);
    return err == 0;
}

void CLuaThread::BeginResume() { m_iNumParams = 0; }

bool CLuaThread::EndResume() {
    int err = lua_resume(m_pLuaState, m_iNumParams);
    HandleError(err);
    return err == 0;
}

// CLuaScript
CLuaScript::CLuaScript() {
    m_errfunc = g_pLuaPCallErrFunc;
    m_pLuaState = 0;
    luabind::set_pcall_callback(m_errfunc);
    Reset();
}

CLuaScript::~CLuaScript() {
    if (m_pLuaState) {
        lua_close(m_pLuaState);
        m_pLuaState = 0;
    }
}

int lua_print(lua_State *L) {
    int nargs = lua_gettop(L);

    std::string t;
    for (int i = 1; i <= nargs; i++) {
        if (lua_istable(L, i))
            t += "table";
        else if (lua_isnone(L, i))
            t += "none";
        else if (lua_isnil(L, i))
            t += "nil";
        else if (lua_isboolean(L, i)) {
            if (lua_toboolean(L, i) != 0)
                t += "true";
            else
                t += "false";
        } else if (lua_isfunction(L, i))
            t += "function";
        else if (lua_islightuserdata(L, i))
            t += "lightuserdata";
        else if (lua_isthread(L, i))
            t += "thread";
        else {
            const char *str = lua_tostring(L, i);
            if (str)
                t += lua_tostring(L, i);
            else
                t += lua_typename(L, lua_type(L, i));
        }
        if (i != nargs)
            t += "\t";
    }
    LOG_NORMAL("[LUA-print] %s", t.c_str());

    return 0;
}

void CLuaScript::Reset() {
    if (m_pLuaState)
        lua_close(m_pLuaState);
    m_iNumParams = 0;

    m_pLuaState = lua_open();
    luaL_openlibs(m_pLuaState);
    lua_checkstack(m_pLuaState, 512);
    SetGlobalPointer("CLuaScriptPtr", (void *)this);

    // Register our version of the global "print" function
    const luaL_reg global_functions[] = {{"print", lua_print}, {nullptr, nullptr}};
    luaL_register(m_pLuaState, "_G", global_functions);
}

inline bool LuaPath_TrimRight(string &str, char chTrim) {
    if (str.size() && str[str.size() - 1] == chTrim) {
        str = str.substr(0, str.size() - 1);
    }
    return str.size() > 0;
}

#ifdef _WIN32
#define LUADIRSTR "\\?.lua"
#else
#define LUADIRSTR "/?.lua"
#endif

int CLuaScript::SetLuaPath(string strPath) // 设置Lua路径,不重复,不覆盖
{
    if (!m_pLuaState || !strPath.size()) {
        return -1;
    }

    if (!LuaPath_TrimRight(strPath, ';')) {
        return -1;
    }

    if (!LuaPath_TrimRight(strPath, '\\')) {
        return -1;
    }

    if (!LuaPath_TrimRight(strPath, '/')) {
        return -1;
    }

    strPath.append(LUADIRSTR);

    lua_State *L = m_pLuaState;
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "path");           // get field "path" from table at top of stack (-1)
    string cur_path = lua_tostring(L, -1); // grab path string from top of stack
    lua_pop(L, 1);                         // get rid of the string on the stack we just pushed on line 5

    if (!LuaPath_TrimRight(cur_path, ';')) {
        return -1;
    }
    cur_path.append(";"); // do your path magic here
    if (cur_path.find(strPath) != string::npos) {
        return 1;
    }
    cur_path.append(strPath);

    lua_pushstring(L, cur_path.c_str()); // push the new one
    lua_setfield(L, -2, "path");         // set the field "path" in table at -2 with
    // value at top of stack
    lua_pop(L, 1); // get rid of package table from top of stack

    m_searchPath.push_back(strPath); //save search path for ExecuteFile
    return 0;      // all done!
}

std::string CLuaScript::GetFullFileName(const char* fname)
{
    if (nullptr == fname) {
        return "";
    }

    if (IFileHelper::GetInstance()->IsAbsolutePath(fname)) {
        return fname;
    }

    std::string relativeName = fname;
    if (relativeName.rfind(".lua") != std::string::npos) {
        relativeName = relativeName.substr(0, relativeName.length() - 4);
    }

    for (int i = 0; i < m_searchPath.size(); i++) {
        std::string& sPath = m_searchPath[i];
        std::string::size_type pos = sPath.rfind('?');
        if (pos != std::string::npos) {
            std::string tempPath = m_searchPath[i];
            std::string fileName = tempPath.replace(pos, 1, relativeName);
            if (IFileHelper::GetInstance()->IsFileExist(fileName)) {
                return fileName;
            }
        }
    }
    return fname;
}

void CLuaScript::SetPCallErrfunc(pcall_errfunc _errfunc)
{
    m_errfunc = _errfunc; 
    luabind::set_pcall_callback(m_errfunc);
}

int CLuaScript::LuaDebugCall(lua_State *L, int nargs, int nresults) {
    int err = 0;
    int errfunc = 0;
    if (nullptr != m_errfunc) {
        int base = lua_gettop(L) - nargs;
        lua_pushcfunction(L, m_errfunc);
        lua_insert(L, base); // push pcall_callback under chunk and args
        errfunc = base;
    }

    err = lua_pcall(L, nargs, nresults, errfunc);
    if (nullptr == m_errfunc && err != 0) {
        HandleError(err);
    }

    if (nullptr != m_errfunc) {
        lua_remove(L, errfunc);
    }
    return err;
}

bool CLuaScript::ExecuteFile(const char *fname) {
    std::string fullFileName = GetFullFileName(fname);
    int _StackTop = lua_gettop(m_pLuaState);
    SetLuaFileName(fullFileName);
    int err = luaL_loadfile(m_pLuaState, fullFileName.c_str());
    HandleError(err);
    if (err == 0) {
        SetLuaFileName(fullFileName);
        err = LuaDebugCall(m_pLuaState, 0, LUA_MULTRET);
        HandleError(err);
    }
    lua_settop(m_pLuaState, _StackTop);
    return err == 0;
}

bool CLuaScript::ExecuteString(const string& str, const char *file) {
    const char *f = str.c_str();
    if (file) {
        f = file;
    }
    int _StackTop = lua_gettop(m_pLuaState);
    SetLuaFileName(f);
    int err = luaL_loadbuffer(m_pLuaState, str.c_str(), str.length(), str.c_str());
    HandleError(err);
    if (err == 0) {
        SetLuaFileName(f);
        err = LuaDebugCall(m_pLuaState, 0, LUA_MULTRET);
        HandleError(err);
    }
    lua_settop(m_pLuaState, _StackTop);
    return err == 0;
}

bool CLuaScript::ExecuteBuffer(const void *buf, int bufSize) {
    int _StackTop = lua_gettop(m_pLuaState);
    string _Temp((const char *)buf, bufSize);
    SetLuaFileName(_Temp);
    int err = luaL_loadbuffer(m_pLuaState, (const char *)buf, (size_t)bufSize, "");
    HandleError(err);
    if (err == 0) {
        SetLuaFileName(_Temp);
        err = LuaDebugCall(m_pLuaState, 0, LUA_MULTRET);
        HandleError(err);
    }
    lua_settop(m_pLuaState, _StackTop);
    return err == 0;
}

bool CLuaScript::IsFunction(const char *name) {
    lua_getglobal(m_pLuaState, name);
    bool isFunction = lua_isfunction(m_pLuaState, -1);
    Pop();
    return isFunction;
}

bool CLuaScript::Call(const char *name) {
    int _StackTop = lua_gettop(m_pLuaState);
    SetCurFuncName(name);
    lua_getglobal(m_pLuaState, name);
    int err = LuaDebugCall(m_pLuaState, 0, 0);
    m_iNumParams = 0;
    lua_settop(m_pLuaState, _StackTop);
    return err == 0;
}

int CLuaScript::BeginCall(const char *name) {
    int _StackTop = lua_gettop(m_pLuaState);
    SetCurFuncName(name);
    ExecuteString("BeginCallFunc = " + m_CurFuncName, nullptr);
    lua_getglobal(m_pLuaState, "BeginCallFunc");
    m_iNumParams = 0;
    return _StackTop;
}

bool CLuaScript::EndCall() {
    int err = LuaDebugCall(m_pLuaState, m_iNumParams, 0);
    return err == 0;
}

bool CLuaScript::EndCall(int &ret) {
    int err = LuaDebugCall(m_pLuaState, m_iNumParams, 1);
    if (err == 0) {
        CLuaValue oValue(this);
        Pop(oValue, LUA_TNUMBER);
        ret = oValue.GetInt();
    }
    return err == 0;
}

bool CLuaScript::EndCall(bool &ret) {
    int err = LuaDebugCall(m_pLuaState, m_iNumParams, 1);
    if (err == 0) {
        CLuaValue oValue(this);
        Pop(oValue, LUA_TBOOLEAN);
        ret = oValue.GetBool();
    }
    return err == 0;
}

bool CLuaScript::EndCall(float &ret) {
    int err = LuaDebugCall(m_pLuaState, m_iNumParams, 1);
    if (err == 0) {
        CLuaValue oValue(this);
        Pop(oValue, LUA_TNUMBER);
        ret = oValue.GetFloat();
    }
    return err == 0;
}

bool CLuaScript::EndCall(double &ret) {
    int err = LuaDebugCall(m_pLuaState, m_iNumParams, 1);
    if (err == 0) {
        CLuaValue oValue(this);
        Pop(oValue, LUA_TNUMBER);
        ret = oValue.GetDouble();
    }
    return err == 0;
}

bool CLuaScript::EndCall(string &ret) {
    int err = LuaDebugCall(m_pLuaState, m_iNumParams, 1);
    if (err == 0) {
        CLuaValue oValue(this);
        Pop(oValue, LUA_TSTRING);
        ret = oValue.GetString();
    }
    return err == 0;
}

bool CLuaScript::EndCall(std::wstring &ret) {
    int err = LuaDebugCall(m_pLuaState, m_iNumParams, 1);
    if (err == 0) {
        CLuaValue oValue(this);
        Pop(oValue, LUA_TSTRING);
        ret = oValue.GetWString();
    }
    return err == 0;
}

bool CLuaScript::EndCall(luabind::object &ret) {
    int err = LuaDebugCall(m_pLuaState, m_iNumParams, 1);
    if (err == 0) {
        ret = luabind::object(luabind::from_stack(m_pLuaState, -1));
    }
    return err == 0;
}

bool CLuaScript::EndCall(CLuaTable &ret) {
    int err = LuaDebugCall(m_pLuaState, m_iNumParams, 1);
    if (err == 0) {
        CLuaValue oValue(this);
        Pop(oValue, LUA_TTABLE);
        ret = oValue.GetTable();
    }
    return err == 0;
}

bool CLuaScript::EndCall(void *&ret) {
    int err = LuaDebugCall(m_pLuaState, m_iNumParams, 1);
    if (err == 0)
        PopPointer(ret);
    return err == 0;
}

void CLuaScript::RegisterCFunction(const char *name, lua_CFunction f) { lua_register(m_pLuaState, name, f); }

void CLuaScript::RegisterCLib(const char *name, const lua_CLib *lib) {
    luaL_openlib(m_pLuaState, name, (luaL_reg *)lib, 0);
}

CLuaThread *CLuaScript::CreateThread(const char *fnName) {
    lua_State *thread = lua_newthread(m_pLuaState);
    CLuaThread *t = new CLuaThread(thread);

    // create a (CLuaThread*, lua_State) mapping in registry to prevent gc
    lua_pushlightuserdata(m_pLuaState, t);
    lua_insert(m_pLuaState, -2);
    lua_settable(m_pLuaState, LUA_REGISTRYINDEX);

    lua_getglobal(thread, fnName);
    return t;
}

void CLuaScript::DeleteThread(CLuaThread *t) {
    if (t == 0)
        return;

    // clear (CLuaThread*, lua_State) mapping in registry to allow gc
    lua_pushlightuserdata(m_pLuaState, t);
    lua_pushnil(m_pLuaState);
    lua_settable(m_pLuaState, LUA_REGISTRYINDEX);

    delete t;
}
