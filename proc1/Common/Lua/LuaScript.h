#ifndef __LUA_SCRIPT__
#define __LUA_SCRIPT__

#include "luabind/lua_include.hpp"
#include "luabind/luabind.hpp"
#include "luabind/object.hpp"
#include <string>
#include <cstdint>
#include <string>
#include <map>
#include <stack>
#include <vector>


using std::string;

struct lua_CLib {
    const char *name;
    lua_CFunction func;
};

class CLuaValue;
class CLuaScript;

typedef luabind::object CLuaObject;
CLuaObject NewTable(CLuaScript *pLuaScript);
typedef std::map<CLuaValue, CLuaValue> CLuaTable;

//
int LuaPCallErrPrint(lua_State *L);
// void LuaErrorPrint(const char *format,...);

// used for lua_pcall errfunc
typedef int (*pcall_errfunc)(lua_State *L);
void LuaScriptSetPCallErrfunc(pcall_errfunc func);

// global error handler
typedef void (*LuaScriptErrorFunc)(int err, const char *info, const char *msg);
void LuaScriptSetErrorFunction(LuaScriptErrorFunc func);

// global lua print handler
typedef void (*LuaScriptOutputFunc)(const char *msg, void *out);
void LuaScriptSetOutputFunction(LuaScriptOutputFunc func);

class CLuaType {
public:
    template <class T> static int GetType() {
        T *_pNotused = nullptr;
        return GetType_<T>(_pNotused);
    }

protected:
    template <class T> static int GetType_(T *_pNotused) { return LUA_TNIL; }
};

template <>
inline int CLuaType::GetType_<char>(char* /*_pNotused*/) {
    return LUA_TNUMBER;
}
template <>
inline int CLuaType::GetType_<unsigned char>(unsigned char* /*_pNotused*/) {
    return LUA_TNUMBER;
}
template <>
inline int CLuaType::GetType_<signed char>(signed char* /*_pNotused*/) {
    return LUA_TNUMBER;
}
template <>
inline int CLuaType::GetType_<int>(int* /*_pNotused*/) {
    return LUA_TNUMBER;
}
template <>
inline int CLuaType::GetType_<unsigned int>(unsigned int* /*_pNotused*/) {
    return LUA_TNUMBER;
}
// template <> inline int CLuaType::GetType_<long>(long */*_pNotused*/) { return LUA_TNUMBER; }
// template <> inline int CLuaType::GetType_<unsigned long>(unsigned long */*_pNotused*/) { return
// LUA_TNUMBER; }

template <>
inline int CLuaType::GetType_<int64_t>(int64_t* /*_pNotused*/) {
    return LUA_TNUMBER;
}
template <>
inline int CLuaType::GetType_<uint64_t>(uint64_t* /*_pNotused*/) {
    return LUA_TNUMBER;
}

// template <> inline int CLuaType::GetType_<int64_t>(int64_t */*_pNotused*/) { return LUA_TNUMBER; }
// template <> inline int CLuaType::GetType_<uint64_t>(uint64_t */*_pNotused*/) { return
// LUA_TNUMBER; }
template <>
inline int CLuaType::GetType_<bool>(bool* /*_pNotused*/) {
    return LUA_TBOOLEAN;
}
template <>
inline int CLuaType::GetType_<float>(float* /*_pNotused*/) {
    return LUA_TNUMBER;
}
template <>
inline int CLuaType::GetType_<double>(double* /*_pNotused*/) {
    return LUA_TNUMBER;
}
template <>
inline int CLuaType::GetType_<const char*>(const char** /*_pNotused*/) {
    return LUA_TSTRING;
}
template <>
inline int CLuaType::GetType_<const wchar_t*>(const wchar_t** /*_pNotused*/) {
    return LUA_TSTRING;
}
template <>
inline int CLuaType::GetType_<string>(string* /*_pNotused*/) {
    return LUA_TSTRING;
}
template <>
inline int CLuaType::GetType_<const string>(const string* /*_pNotused*/) {
    return LUA_TSTRING;
}
template <>
inline int CLuaType::GetType_<CLuaObject>(CLuaObject* /*_pNotused*/) {
    return LUA_TTABLE;
}
template <>
inline int CLuaType::GetType_<void*>(void** /*_pNotused*/) {
    return LUA_TNUMBER;
}

class CLuaState;

class CLuaValue {
public:
    friend class CLuaState;

    CLuaValue();
    ~CLuaValue();

    CLuaValue(const CLuaValue &value);

    CLuaValue(CLuaState *pState);
    CLuaValue(int value, CLuaState *pState = nullptr);
    //CLuaValue(int64_t value, CLuaState *pState = nullptr);

	//CLuaValue(unsigned int value, CLuaState *pState = nullptr);
	CLuaValue(int64_t value, CLuaState *pState = nullptr);

    CLuaValue(bool value, CLuaState *pState = nullptr);
    CLuaValue(float value, CLuaState *pState = nullptr);
    CLuaValue(double value, CLuaState *pState = nullptr);
    CLuaValue(const char *value, CLuaState *pState = nullptr);
    CLuaValue(const wchar_t *value, CLuaState *pState = nullptr);
    CLuaValue(const CLuaTable &value, CLuaState *pState = nullptr);
    CLuaValue(const CLuaObject &value, CLuaState *pState = nullptr);

    int GetInt() const;
    int64_t GetInt64() const;

    bool GetBool() const;
    float GetFloat() const;
    double GetDouble() const;
    const char *GetString() const;
    const wchar_t *GetWString() const;
    CLuaTable &GetTable() const;
    void *GetPointer() const;

    int GetType() const;

    bool operator<(const CLuaValue &r) const;

    CLuaValue &operator[](const CLuaValue &r) const { return GetTable()[r]; }

    CLuaValue &operator=(const CLuaValue &r);

private:
    void SetNil();
    void Set(int value);
    void Set(int64_t value);
    void Set(bool value);
    void Set(float value);
    void Set(double value);
    void Set(const char *value);
    void Set(const wchar_t *value);
    void Set(const CLuaValue &value);
    void Set(const CLuaTable &value);
    void Set(const CLuaObject &value);
    void SetPointer(void *value);

    void Release();

    int m_LuaValType;
    union {
        double m_LuaNumber;
        char *m_pString;
        CLuaTable *m_pTable;
        void *m_Pointer;
    };

    CLuaState *m_pCLuaState;
};

class CLuaState {
public:
    CLuaState();
    CLuaState(lua_State *ls);
    virtual ~CLuaState();

    // set error handler, global handler is used if not set
    void SetErrorFunction(LuaScriptErrorFunc func);

    // set global variable, add new one if not exist
    void SetGlobal(const char *name, int value);
    void SetGlobal(const char *name, int64_t value);
    void SetGlobal(const char *name, bool value);
    void SetGlobal(const char *name, float value);
    void SetGlobal(const char *name, double value);
    void SetGlobal(const char *name, const char *value);
    void SetGlobal(const char *name, const wchar_t *value);
    void SetGlobal(const char *name, const CLuaTable &value);
    void SetGlobalPointer(const char *name, void *value);
    void SetGlobalNil(const char *name);

    // get global variable with type checking
    bool GetGlobal(const char *name, int &value);
    bool GetGlobal(const char *name, int64_t &value);
    bool GetGlobal(const char *name, bool &value);
    bool GetGlobal(const char *name, float &value);
    bool GetGlobal(const char *name, double &value);
    bool GetGlobal(const char *name, string &value);
    bool GetGlobal(const char *name, std::wstring &value);
    bool GetGlobal(const char *name, CLuaTable &value);
    bool GetGlobalPointer(const char *name, void *&value);
    bool IsGlobalNil(const char *name);

    // get global variable, cast type automatically
    int GetGlobalInt(const char *name);
    int64_t GetGlobalInt64(const char *name);
    bool GetGlobalBool(const char *name);
    float GetGlobalFloat(const char *name);
    double GetGlobalDouble(const char *name);
    const char *GetGlobalString(const char *name);
    const wchar_t *GetGlobalWString(const char *name);
    CLuaTable GetGlobalTable(const char *name);
    void *GetGlobalPointer(const char *name);

    // stack operations
    void PushNil();
    void Push(int value);
    void Push(int64_t value);
    void Push(bool value);
    void Push(float value);
    void Push(double value);
    void Push(const char *value);
    void Push(const wchar_t *value);
    void Push(const CLuaValue &value);
    void Push(const CLuaTable &value);
    void PushPointer(void *value);
    void Push(const string &value);

    void Pop();
    void Pop(int &value);
    void Pop(int64_t &value);
    void Pop(bool &value);
    void Pop(float &value);
    void Pop(double &value);
    void Pop(string &value);
    void Pop(std::wstring &value);
    void Pop(CLuaValue &value, int eExpectType);
    void Pop(CLuaTable &value);
    void PopPointer(void *&value);

    int PopInt();
    int64_t PopInt64();
    bool PopBool();
    float PopFloat();
    double PopDouble();
    const char *PopString();
    const wchar_t *PopWString();
    void *PopPointer();
    CLuaValue PopValue();
    CLuaTable PopTable();

    // low level table functions
    void NewTable();
    void SetTable(int idx = LUA_GLOBALSINDEX);
    void GetTable(int idx = LUA_GLOBALSINDEX);

    // get internal state
    lua_State *GetCLuaState();
    int GetStackTop();

    void SetLuaFileName(const string &strFileName) { m_LuaFileName = strFileName; }
    string GetLuaFileName() { return m_LuaFileName; }

    void SetCurFuncName(const string &strFuncName) { m_CurFuncName = strFuncName; }
    string GetCurFuncName() { return m_CurFuncName; }

    string toString(int eType);

protected:
    void HandleError(int err);
    lua_State *m_pLuaState;
    LuaScriptErrorFunc m_pErrorFunc;
    string m_CurFuncName;
    string m_LuaFileName;
};

class CLuaParamHelper : public CLuaState {
public:
    CLuaParamHelper();
    CLuaParamHelper(lua_State *ls);

    bool IsBool(lua_State *L, int idx);
    bool IsInt(lua_State *L, int idx);
    bool IsInt64(lua_State *L, int idx);
    bool IsFloat(lua_State *L, int idx);
    bool IsDouble(lua_State *L, int idx);
    bool IsString(lua_State *L, int idx);
    bool IsLightUserData(lua_State *L, int idx);
    bool IsTable(lua_State *L, int idx);

    void Param(int value);
    void Param(int64_t value);
    void Param(bool value);
    void Param(float value);
    void Param(double value);
    void Param(const char *value);
    void Param(const wchar_t *value);
    void Param(const CLuaValue &value);
    void Param(const CLuaTable &value);
    void ParamPointer(void *value);
    void Param(const string &value);

protected:
    int m_iNumParams;
};

class CLuaThread : public CLuaParamHelper {
public:
    CLuaThread(lua_State *ls);

    bool IsDead();
    bool Resume();

    void BeginResume(); // after BeginResume(), use Param() to set parameters
    bool EndResume();
};

class CLuaScript : public CLuaParamHelper {
private:
    pcall_errfunc m_errfunc;
    std::vector<string> m_searchPath;

public:
    CLuaScript();
    virtual ~CLuaScript();

    void Reset();
    int SetLuaPath(string strPath); // 设置Lua路径,不重复,不覆盖
    std::string GetFullFileName(const char* fname);

    void SetPCallErrfunc(pcall_errfunc _errfunc);
    int LuaDebugCall(lua_State *L, int nargs, int nresults);

    bool ExecuteFile(const char *fname);
    bool ExecuteString(const string& str, const char *file);
    bool ExecuteBuffer(const void *buf, int bufSize);

    bool IsFunction(const char *name);

    bool Call(const char *name); // call script function, without parameter and
    // return value

    int BeginCall(const char *name); // after BeginCall, use Param() to set
    // parameters, EndCall() to get return value
    bool EndCall();
    bool EndCall(int &ret);
    bool EndCall(int64_t &ret);
    bool EndCall(bool &ret);
    bool EndCall(float &ret);
    bool EndCall(double &ret);
    bool EndCall(string &ret);
    bool EndCall(std::wstring &ret);
    bool EndCall(CLuaTable &ret);
    bool EndCall(luabind::object &ret);
    bool EndCall(void *&ret);

    void RegisterCFunction(const char *name, lua_CFunction f);
    void RegisterCLib(const char *name, const lua_CLib *lib);

    CLuaThread *CreateThread(const char *fnName);
    void DeleteThread(CLuaThread *t);

    // TCall is a template method to execute a LUA function.
    // Besides the first argument(function name), another 15 arguments can be
    // assigned at most.
    // and a result type must be provided.
    // Usage:
    //  CLuaScript L;
    //  ...
    //  int iResult = L.TCall<int>("func01", 1, 2, 3, 4);
    template <class R> R TCallResult(int _StackTop) {
        R ret;
        EndCall(ret);
        lua_settop(m_pLuaState, _StackTop);
        return ret;
    }

    template <class R> R TCall(const char *name) {
        int _StackTop = BeginCall(name);
        return TCallResult<R>(_StackTop);
    }

    template <class R, class P1> R TCall(const char *name, const P1 &p1) {
        int _StackTop = BeginCall(name);
        Param(p1);
        return TCallResult<R>(_StackTop);
    }

    template <class R, class P1, class P2> R TCall(const char *name, const P1 &p1, const P2 &p2) {
        int _StackTop = BeginCall(name);
        Param(p1);
        Param(p2);
        return TCallResult<R>(_StackTop);
    }

    template <class R, class P1, class P2, class P3>
    R TCall(const char *name, const P1 &p1, const P2 &p2, const P3 &p3) {
        int _StackTop = BeginCall(name);
        Param(p1);
        Param(p2);
        Param(p3);
        return TCallResult<R>(_StackTop);
    }

    template <class R, class P1, class P2, class P3, class P4>
    R TCall(const char *name, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4) {
        int _StackTop = BeginCall(name);
        Param(p1);
        Param(p2);
        Param(p3);
        Param(p4);
        return TCallResult<R>(_StackTop);
    }

    template <class R, class P1, class P2, class P3, class P4, class P5>
    R TCall(const char *name, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5) {
        int _StackTop = BeginCall(name);
        Param(p1);
        Param(p2);
        Param(p3);
        Param(p4);
        Param(p5);
        return TCallResult<R>(_StackTop);
    }

    template <class R, class P1, class P2, class P3, class P4, class P5, class P6>
    R TCall(const char *name, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6) {
        int _StackTop = BeginCall(name);
        Param(p1);
        Param(p2);
        Param(p3);
        Param(p4);
        Param(p5);
        Param(p6);
        return TCallResult<R>(_StackTop);
    }

    template <class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
    R TCall(const char *name, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6,
            const P7 &p7) {
        int _StackTop = BeginCall(name);
        Param(p1);
        Param(p2);
        Param(p3);
        Param(p4);
        Param(p5);
        Param(p6);
        Param(p7);
        return TCallResult<R>(_StackTop);
    }

    template <class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
    R TCall(const char *name, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6,
            const P7 &p7, const P8 &p8) {
        int _StackTop = BeginCall(name);
        Param(p1);
        Param(p2);
        Param(p3);
        Param(p4);
        Param(p5);
        Param(p6);
        Param(p7);
        Param(p8);
        return TCallResult<R>(_StackTop);
    }

    template <class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
    R TCall(const char *name, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6,
            const P7 &p7, const P8 &p8, const P9 &p9) {
        int _StackTop = BeginCall(name);
        Param(p1);
        Param(p2);
        Param(p3);
        Param(p4);
        Param(p5);
        Param(p6);
        Param(p7);
        Param(p8);
        Param(p9);
        return TCallResult<R>(_StackTop);
    }

    template <class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9,
              class P10>
    R TCall(const char *name, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6,
            const P7 &p7, const P8 &p8, const P9 &p9, const P10 &p10) {
        int _StackTop = BeginCall(name);
        Param(p1);
        Param(p2);
        Param(p3);
        Param(p4);
        Param(p5);
        Param(p6);
        Param(p7);
        Param(p8);
        Param(p9);
        Param(p10);
        return TCallResult<R>(_StackTop);
    }

    template <class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9,
              class P10, class P11>
    R TCall(const char *name, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6,
            const P7 &p7, const P8 &p8, const P9 &p9, const P10 &p10, const P11 &p11) {
        int _StackTop = BeginCall(name);
        Param(p1);
        Param(p2);
        Param(p3);
        Param(p4);
        Param(p5);
        Param(p6);
        Param(p7);
        Param(p8);
        Param(p9);
        Param(p10);
        Param(p11);
        return TCallResult<R>(_StackTop);
    }

    template <class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9,
              class P10, class P11, class P12>
    R TCall(const char *name, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6,
            const P7 &p7, const P8 &p8, const P9 &p9, const P10 &p10, const P11 &p11, const P12 &p12) {
        int _StackTop = BeginCall(name);
        Param(p1);
        Param(p2);
        Param(p3);
        Param(p4);
        Param(p5);
        Param(p6);
        Param(p7);
        Param(p8);
        Param(p9);
        Param(p10);
        Param(p11);
        Param(p12);
        return TCallResult<R>(_StackTop);
    }

    template <class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9,
              class P10, class P11, class P12, class P13>
    R TCall(const char *name, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6,
            const P7 &p7, const P8 &p8, const P9 &p9, const P10 &p10, const P11 &p11, const P12 &p12, const P13 &p13) {
        int _StackTop = BeginCall(name);
        Param(p1);
        Param(p2);
        Param(p3);
        Param(p4);
        Param(p5);
        Param(p6);
        Param(p7);
        Param(p8);
        Param(p9);
        Param(p10);
        Param(p11);
        Param(p12);
        Param(p13);
        return TCallResult<R>(_StackTop);
    }

    template <class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9,
              class P10, class P11, class P12, class P13, class P14>
    R TCall(const char *name, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6,
            const P7 &p7, const P8 &p8, const P9 &p9, const P10 &p10, const P11 &p11, const P12 &p12, const P13 &p13,
            const P14 &p14) {
        int _StackTop = BeginCall(name);
        Param(p1);
        Param(p2);
        Param(p3);
        Param(p4);
        Param(p5);
        Param(p6);
        Param(p7);
        Param(p8);
        Param(p9);
        Param(p10);
        Param(p11);
        Param(p12);
        Param(p13);
        Param(p14);
        return TCallResult<R>(_StackTop);
    }

    template <class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9,
              class P10, class P11, class P12, class P13, class P14, class P15>
    R TCall(const char *name, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6,
            const P7 &p7, const P8 &p8, const P9 &p9, const P10 &p10, const P11 &p11, const P12 &p12, const P13 &p13,
            const P14 &p14, const P15 &p15) {
        int _StackTop = BeginCall(name);
        Param(p1);
        Param(p2);
        Param(p3);
        Param(p4);
        Param(p5);
        Param(p6);
        Param(p7);
        Param(p8);
        Param(p9);
        Param(p10);
        Param(p11);
        Param(p12);
        Param(p13);
        Param(p14);
        Param(p15);
        return TCallResult<R>(_StackTop);
    }
};

template <> inline void CLuaScript::TCallResult<void>(int _StackTop) {
    EndCall();
    lua_settop(m_pLuaState, _StackTop);
}

//////////////////////////////////////////////////////////////////////////

inline CLuaValue::CLuaValue() {
    m_LuaValType = LUA_TNIL;
    m_LuaNumber = 0;
    m_pCLuaState = nullptr;
}

inline CLuaValue::~CLuaValue() { Release(); }

inline CLuaValue::CLuaValue(CLuaState *pState) {
    m_LuaValType = LUA_TNIL;
    m_LuaNumber = 0;
    m_pCLuaState = pState;
}

inline CLuaValue::CLuaValue(int value, CLuaState *pState /* = nullptr*/) {
    m_LuaValType = LUA_TNIL;
    Set(value);

    m_pCLuaState = pState;
}

inline CLuaValue::CLuaValue(int64_t value, CLuaState *pState /* = nullptr*/) {
    m_LuaValType = LUA_TNIL;
    Set(value);

    m_pCLuaState = pState;
}

inline CLuaValue::CLuaValue(bool value, CLuaState *pState /* = nullptr*/) {
    m_LuaValType = LUA_TNIL;
    Set(value);

    m_pCLuaState = pState;
}

inline CLuaValue::CLuaValue(float value, CLuaState *pState /* = nullptr*/) {
    m_LuaValType = LUA_TNIL;
    Set(value);

    m_pCLuaState = pState;
}

inline CLuaValue::CLuaValue(double value, CLuaState *pState /* = nullptr*/) {
    m_LuaValType = LUA_TNIL;
    Set(value);

    m_pCLuaState = pState;
}

inline CLuaValue::CLuaValue(const char *value, CLuaState *pState /* = nullptr*/) {
    m_LuaValType = LUA_TNIL;
    Set(value);

    m_pCLuaState = pState;
}

inline CLuaValue::CLuaValue(const wchar_t *value, CLuaState *pState /* = nullptr*/) {
    m_LuaValType = LUA_TNIL;
    Set(value);

    m_pCLuaState = pState;
}

inline CLuaValue::CLuaValue(const CLuaValue &value) {
    m_LuaValType = LUA_TNIL;
    Set(value);

    m_pCLuaState = value.m_pCLuaState;
}

inline CLuaValue::CLuaValue(const CLuaTable &value, CLuaState *pState /* = nullptr*/) {
    m_LuaValType = LUA_TNIL;
    Set(value);

    m_pCLuaState = pState;
}

inline CLuaValue::CLuaValue(const CLuaObject &value, CLuaState *pState /* = nullptr*/) {
    m_LuaValType = LUA_TNIL;
    Set(value);

    m_pCLuaState = pState;
}

inline void CLuaValue::SetNil() {
    Release();
    m_LuaValType = LUA_TNIL;
    m_LuaNumber = 0;
}

inline void CLuaValue::Set(int value) {
    Release();
    m_LuaValType = LUA_TNUMBER;
    m_LuaNumber = (unsigned int)value;
}

inline void CLuaValue::Set(int64_t value) {
    Release();
    m_LuaValType = LUA_TNUMBER;
    m_LuaNumber = (uint64_t)value;
}

inline void CLuaValue::Set(bool value) {
    Release();
    m_LuaValType = LUA_TBOOLEAN;
    if (value)
        m_LuaNumber = 1;
    else
        m_LuaNumber = 0;
}

inline void CLuaValue::Set(float value) {
    Release();
    m_LuaValType = LUA_TNUMBER;
    m_LuaNumber = value;
}

inline void CLuaValue::Set(double value) {
    Release();
    m_LuaValType = LUA_TNUMBER;
    m_LuaNumber = value;
}

inline void CLuaValue::SetPointer(void *value) {
    Release();
    m_LuaValType = LUA_TLIGHTUSERDATA;
    m_Pointer = value;
}

inline int CLuaValue::GetType() const { return m_LuaValType; }

inline CLuaValue &CLuaValue::operator=(const CLuaValue &r) {
    Set(r);
    return *this;
}

// CLuaState
inline CLuaState::CLuaState(lua_State *ls) {
    m_pLuaState = ls;
    m_pErrorFunc = 0;//@zhuhangmin 20170112
}

inline int CLuaState::PopInt() {
    int value;
    Pop(value);
    return value;
}

inline int64_t CLuaState::PopInt64() {
    int64_t value;
    Pop(value);
    return value;
}

inline bool CLuaState::PopBool() {
    bool value;
    Pop(value);
    return value;
}

inline float CLuaState::PopFloat() {
    float value;
    Pop(value);
    return value;
}

inline double CLuaState::PopDouble() {
    double value;
    Pop(value);
    return value;
}

inline void *CLuaState::PopPointer() {
    void *value;
    PopPointer(value);
    return value;
}

inline lua_State *CLuaState::GetCLuaState() { return m_pLuaState; }

// CLuaParamHelper
inline CLuaParamHelper::CLuaParamHelper() { m_iNumParams = 0; }

inline CLuaParamHelper::CLuaParamHelper(lua_State *ls) : CLuaState(ls) { m_iNumParams = 0; }

inline bool CLuaParamHelper::IsBool(lua_State *L, int idx) { return lua_type(L, idx) == LUA_TBOOLEAN; }

inline bool CLuaParamHelper::IsInt(lua_State *L, int idx) { return lua_type(L, idx) == LUA_TNUMBER; }

inline bool CLuaParamHelper::IsInt64(lua_State *L, int idx) { return lua_type(L, idx) == LUA_TNUMBER; }

inline bool CLuaParamHelper::IsFloat(lua_State *L, int idx) { return lua_type(L, idx) == LUA_TNUMBER; }

inline bool CLuaParamHelper::IsDouble(lua_State *L, int idx) { return lua_type(L, idx) == LUA_TNUMBER; }

inline bool CLuaParamHelper::IsString(lua_State *L, int idx) { return lua_type(L, idx) == LUA_TSTRING; }

inline bool CLuaParamHelper::IsLightUserData(lua_State *L, int idx) { return lua_type(L, idx) == LUA_TLIGHTUSERDATA; }

inline bool CLuaParamHelper::IsTable(lua_State *L, int idx) { return lua_type(L, idx) == LUA_TTABLE; }

inline void CLuaParamHelper::Param(int value) {
    Push(value);
    m_iNumParams++;
}

inline void CLuaParamHelper::Param(bool value) {
    Push(value);
    m_iNumParams++;
}

inline void CLuaParamHelper::Param(float value) {
    Push(value);
    m_iNumParams++;
}

inline void CLuaParamHelper::Param(double value) {
    Push(value);
    m_iNumParams++;
}

inline void CLuaParamHelper::Param(const char *value) {
    Push(value);
    m_iNumParams++;
}

inline void CLuaParamHelper::Param(const wchar_t *value) {
    Push(value);
    m_iNumParams++;
}

inline void CLuaParamHelper::Param(const CLuaValue &value) {
    Push(value);
    m_iNumParams++;
}

inline void CLuaParamHelper::Param(const CLuaTable &value) {
    Push(value);
    m_iNumParams++;
}

inline void CLuaParamHelper::ParamPointer(void *value) {
    PushPointer(value);
    m_iNumParams++;
}

inline void CLuaParamHelper::Param(const string &value) {
    Push(value);
    m_iNumParams++;
}

// CLuaThread
inline CLuaThread::CLuaThread(lua_State *ls) : CLuaParamHelper(ls) {}
#endif
