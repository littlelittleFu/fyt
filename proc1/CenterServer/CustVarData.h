#pragma once




class CustVarData
{
    DECL_SINGLETON(CustVarData);

public:
    void SetHasData(bool flag) { mHasData = flag; }
    bool HasData() { return mHasData; }

    void SetCustVars(CUST_VAR_SP_LIST vars) { mCustVars = std::move(vars); }
    CUST_VAR_SP_LIST & GetCustVars() { return mCustVars; }

    void SetCustVar(CUST_VAR_SP var);

private:
    CustVarData() {}
    ~CustVarData() {}

private:
    bool                mHasData = false;
    CUST_VAR_SP_LIST    mCustVars;
};
