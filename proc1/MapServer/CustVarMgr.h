#pragma once




class CustVarMgr
{
    DECL_SINGLETON(CustVarMgr);

public:
    bool SetVar(const std::string &belong, std::string name, std::string value, const uint8_t &type, const uint8_t& mergeType = 0);
    const std::string & GetVar(const std::string &belong, const std::string &name);

    void SetValue(CUST_VAR_MAP &vars, const uint64_t &belong, std::string name, std::string value, const uint8_t &type);
    const std::string & GetValue(CUST_VAR_MAP &vars, const std::string &name);

    void SetValue(CUST_VAR_SP_MAP &vars, const uint64_t &belong, std::string name, std::string value, const uint8_t &type, bool& beDelete);
    void SetValue(CUST_VAR_SP_MAP& vars, CUST_VAR& cv);
    const std::string & GetValue(CUST_VAR_SP_MAP &vars, const std::string &name, bool& beDelete);
    const CUST_VAR_SP& GetCustVarSP(CUST_VAR_SP_MAP& vars, const std::string& name, bool& beDelete);

    void SetGlobalVars(CUST_VAR_SP_LIST vars);

    void CheckExpired(CUST_VAR_MAP& CustVars);
    void CheckExpired_CS(CUST_VAR_MAP& CustVars);
    void CheckExpiredAndCollect(CUST_VAR_SP_MAP& CustVars, CUST_VAR_SP_LIST& var);

    bool DelTempVar(const uint64_t& belong);
private:
    CustVarMgr() {}
    ~CustVarMgr() {}

    bool SetGlobalVar(const uint64_t &belong, std::string name, std::string value, const uint8_t &type, const uint8_t& mergeType = 0);
    const std::string & GetGlobalVar(const uint64_t &belong, const std::string &name);

    bool SetTempVar(const uint64_t &belong, std::string name, std::string value, const uint8_t &type, const uint8_t& mergeType = 0);
    const std::string & GetTempVar(const uint64_t &belong, const std::string &name);

    bool SetPlayerVar(const uint64_t &belong, std::string name, std::string value, const uint8_t &type);
    const std::string & GetPlayerVar(const uint64_t &belong, const std::string &name);

    bool SetItemVar(const uint64_t &belong, std::string name, std::string value, const uint8_t &type);
    const std::string & GetItemVar(const uint64_t &belong, const std::string &name);

    bool DoSetVar(GUID_TO_CUST_VAR_MAP &varMap, const uint64_t &belong, std::string name,
        std::string value, const uint8_t &type, bool syncToDB, const uint8_t& mergeType);
    const std::string & DoGetVar(GUID_TO_CUST_VAR_MAP &varMap, const uint64_t &belong, const std::string &name, bool syncToDB);

    void SendSetCustVarToCS(CUST_VAR &var);

private:
    GUID_TO_CUST_VAR_MAP mGlobalVars;
    GUID_TO_CUST_VAR_MAP mTempVars;
};
