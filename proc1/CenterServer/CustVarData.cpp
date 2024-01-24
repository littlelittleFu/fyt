#include "stdafx.h"
#include "CustVarData.h"

IMPL_SINGLETON(CustVarData);

void CustVarData::SetCustVar(CUST_VAR_SP var)
{
    for (auto it = mCustVars.begin(); it != mCustVars.end(); ++it) {

        auto &old = *it;

        if (old->belong == var->belong && old->name == var->name) {

            if (var->value.empty())
                mCustVars.erase(it);
            else
                old = std::move(var);

            return;
        }
    }

    mCustVars.emplace_back(std::move(var));
}
