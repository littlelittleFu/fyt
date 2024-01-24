#include "stdafx.h"
#include "CustVarMgr.h"

#include "MapRoleMgr.h"
#include "CNetManager.h"
#include "SessionFactory.h"
#include "ItemMap.h"

IMPL_SINGLETON(CustVarMgr);

bool CustVarMgr::SetVar(const std::string &belong, std::string name, std::string value, const uint8_t &type, const uint8_t& mergeType)
{
    auto guid = std::stoull(belong);

    if (guid == 0) {        // 全局变量
        return SetGlobalVar(guid, std::move(name), std::move(value), type, mergeType);
    }

    switch (GUID_TYPE_PART(guid)) {

    case E_OBJ_PLAYER:
        return SetPlayerVar(guid, std::move(name), std::move(value), type);

    case E_OBJ_MONSTER:
    case E_OBJ_NPC:
    case E_OBJ_MAP:
    case E_OBJ_PET:
    case E_OBJ_PLAYER_DOPLGANR:
        return SetTempVar(guid, std::move(name), std::move(value), type);

    case E_OBJ_ITEM:
        return SetItemVar(guid, std::move(name), std::move(value), type);

    case E_OBJ_GUILD:
        return SetGlobalVar(guid, std::move(name), std::move(value), type, mergeType);

    default:
        return false;
    }
}

bool CustVarMgr::SetGlobalVar(const uint64_t &belong, std::string name, std::string value, const uint8_t &type, const uint8_t& mergeType)
{
    return DoSetVar(mGlobalVars, belong, std::move(name), std::move(value), type, true, mergeType);
}

bool CustVarMgr::SetTempVar(const uint64_t &belong, std::string name, std::string value, const uint8_t &type, const uint8_t& mergeType)
{
    return DoSetVar(mTempVars, belong, std::move(name), std::move(value), type, false, mergeType);
}

bool CustVarMgr::DelTempVar(const uint64_t& belong)
{
    auto itMap = mTempVars.find(belong);
    if (itMap == mTempVars.end()) return true;
    mTempVars.erase(itMap);
    return true;
}

bool CustVarMgr::SetPlayerVar(const uint64_t &belong, std::string name, std::string value, const uint8_t &type)
{
    auto *player = MapRoleMgr::GetInstance()->FindPlayer(belong);
    if (!player) return false;

    player->SetCustVar(std::move(name), std::move(value), type);
    return true;
}

bool CustVarMgr::SetItemVar(const uint64_t &belong, std::string name, std::string value, const uint8_t &type)
{
    auto *item = ItemMap::GetInstance()->GetItem(belong);
    if (!item) return false;

    bool beDelete = false;
    item->SetCustVar(name, value, type, beDelete);
    if (item->GetCategory() == item_cat_player)
    {
        auto* roleMgr = MapRoleMgr::GetInstance();
        if (!roleMgr) return true;
        auto roleItem = static_cast<RoleItem*>(item);
        if (!roleItem) return true;
        auto roleGuid = roleItem->GetRoleid();
        auto role = roleMgr->FindRole(roleGuid);
        if (!role) return true;
        auto rolePack = role->GetRolePack();
        if (!rolePack) return true;
        rolePack->NtfMasterUpdateItem(roleItem->GetSite());
        // 每次更新都要记录
        auto info = item->GetCustVarSP(name, beDelete);
        if (info)
        {
            SendDBLogData(log_type_item_cust_var, LogItemCustVar(item->GetGUID(), info->name, info->value, info->type, info->expire));
        }
        else if (beDelete)
        {
            SendDBLogData(log_type_item_cust_var, LogItemCustVar(item->GetGUID(), name, "", 0, 0));
        }
    }
    return true;
}

bool CustVarMgr::DoSetVar(GUID_TO_CUST_VAR_MAP &varMap, const uint64_t &belong, std::string name,
    std::string value, const uint8_t &type, bool syncToDB, const uint8_t& mergeType)
{
    if (value.empty()) {

        auto itMap = varMap.find(belong);
        if (itMap == varMap.end()) return true;

        auto &vars = itMap->second;

        auto itVar = vars.find(name);
        if (itVar == vars.end()) return true;

        if (syncToDB) {
            auto &var = itVar->second;
            var->value.clear();
            SendSetCustVarToCS(*var);
        }

        vars.erase(itVar);
        return true;
    }


    auto &vars = varMap[belong];

    auto it = vars.find(name);
    if (it == vars.end()) {
        auto var = std::make_shared<CUST_VAR>();
        it = vars.emplace(name, std::move(var)).first;
    }

    auto &var = it->second;
    var->belong = belong;
    var->name = std::move(name);
    var->value = std::move(value);
    var->type = type;
    var->mergeType = mergeType;

    if (type == cust_var_type_daily) {
        var->expire = ITimeHelper::GetInstance()->GetEndOfDay();
    }

    if (syncToDB) SendSetCustVarToCS(*var);
    return true;
}

const std::string & CustVarMgr::GetVar(const std::string &belong, const std::string &name)
{
    auto guid = std::stoull(belong);

    if (guid == 0) {
        return GetGlobalVar(guid, name);
    }

    switch (GUID_TYPE_PART(guid)) {

    case E_OBJ_PLAYER:
        return GetPlayerVar(guid, name);

    case E_OBJ_MONSTER:
    case E_OBJ_NPC:
    case E_OBJ_MAP:
    case E_OBJ_PET:
    case E_OBJ_PLAYER_DOPLGANR:
        return GetTempVar(guid, name);

    case E_OBJ_ITEM:
        return GetItemVar(guid, name);

    case E_OBJ_GUILD:
        return GetGlobalVar(guid, name);

    default:
        return EMPTYSTR;
    }
}

const std::string & CustVarMgr::GetGlobalVar(const uint64_t &belong, const std::string &name)
{
    return DoGetVar(mGlobalVars, belong, name, true);
}

const std::string & CustVarMgr::GetTempVar(const uint64_t &belong, const std::string &name)
{
    return DoGetVar(mTempVars, belong, name, false);
}

const std::string & CustVarMgr::GetPlayerVar(const uint64_t &belong, const std::string &name)
{
    auto *player = MapRoleMgr::GetInstance()->FindPlayer(belong);
    return player ? player->GetCustVar(name) : EMPTYSTR;
}

const std::string & CustVarMgr::GetItemVar(const uint64_t &belong, const std::string &name)
{
    auto *item = ItemMap::GetInstance()->GetItem(belong);
    if (!item) return EMPTYSTR;

    bool beDelete = false;
    const auto& var = item->GetCustVar(name, beDelete);
    if (beDelete)
    {
        SendDBLogData(log_type_item_cust_var, LogItemCustVar(item->GetGUID(), name, "", 0, 0));
    }
    return var;
}

const std::string & CustVarMgr::DoGetVar(GUID_TO_CUST_VAR_MAP &varMap, const uint64_t &belong, const std::string &name, bool syncToDB)
{
    auto itMap = varMap.find(belong);
    if (itMap == varMap.end()) return EMPTYSTR;

    auto &vars = itMap->second;

    auto itVar = vars.find(name);
    if (itVar == vars.end()) return EMPTYSTR;

    auto &var = itVar->second;

    switch (var->type) {

    case cust_var_type_normal:
    case cust_var_type_temp:
        return var->value;

    case cust_var_type_daily:
        if (time(nullptr) <= var->expire)
            return var->value;

        if (syncToDB) {
            var->value.clear();
            SendSetCustVarToCS(*var);
        }

        vars.erase(itVar);
        return EMPTYSTR;

    default:
        return EMPTYSTR;
    }
}

void CustVarMgr::SendSetCustVarToCS(CUST_VAR &var)
{
    if (var.type != cust_var_type_temp)
    {
        ProtoMS_SetCustVar data;
        data.var = &var;

        SendDataBySessionType(SESSION_TYPE_MS2CS, data);
    }
}

void CustVarMgr::SetValue(CUST_VAR_MAP &vars, const uint64_t &belong, std::string name, std::string value, const uint8_t &type)
{
    if (value.empty()) {
        vars.erase(name);
        return;
    }

    auto &var = vars[name];
    var.belong = belong;
    var.name = std::move(name);
    var.value = std::move(value);
    var.type = type;

    if (type == cust_var_type_daily) {
        var.expire = ITimeHelper::GetInstance()->GetEndOfDay();
    }
}

const std::string & CustVarMgr::GetValue(CUST_VAR_MAP &vars, const std::string &name)
{
    auto it = vars.find(name);
    if (it == vars.end()) return EMPTYSTR;

    auto &var = it->second;

    switch (var.type) {

    case cust_var_type_normal:
    case cust_var_type_temp:
        return var.value;

    case cust_var_type_daily:
        if (time(nullptr) <= var.expire)
            return var.value;

        vars.erase(it);
        return EMPTYSTR;

    default:
        return EMPTYSTR;
    }
}

void CustVarMgr::SetValue(CUST_VAR_SP_MAP &vars, const uint64_t &belong, std::string name, std::string value, const uint8_t &type, bool& beDelete)
{
    if (value.empty()) {
        if (vars.find(name) != vars.end()) beDelete = true;
        vars.erase(name);
        return;
    }

    auto var = std::make_shared<CUST_VAR>();
    var->belong = belong;
    var->name = std::move(name);
    var->value = std::move(value);
    var->type = type;

    if (type == cust_var_type_daily) {
        var->expire = ITimeHelper::GetInstance()->GetEndOfDay();
    }

    vars[var->name] = std::move(var);
}

void CustVarMgr::SetValue(CUST_VAR_SP_MAP& vars, CUST_VAR& cv)
{
    if (cv.name.empty()) {
        vars.erase(cv.name);
        return;
    }

    auto var = std::make_shared<CUST_VAR>();
    *var = cv;
    vars[var->name] = std::move(var);
}

const std::string & CustVarMgr::GetValue(CUST_VAR_SP_MAP &vars, const std::string &name, bool& beDelete)
{
    auto it = vars.find(name);
    if (it == vars.end()) return EMPTYSTR;
    if (!it->second)
    {
        beDelete = true;
        vars.erase(it);
        return EMPTYSTR;
    }

    auto &var = it->second;

    switch (var->type) {

    case cust_var_type_normal:
    case cust_var_type_temp:
        return var->value;

    case cust_var_type_daily:
        if (time(nullptr) <= var->expire)
            return var->value;

        beDelete = true;
        vars.erase(it);
        return EMPTYSTR;

    default:
        return EMPTYSTR;
    }
}

const CUST_VAR_SP& CustVarMgr::GetCustVarSP(CUST_VAR_SP_MAP& vars, const std::string& name, bool& beDelete)
{
    static CUST_VAR_SP sp;
    auto it = vars.find(name);
    if (it == vars.end()) return sp;
    if (!it->second)
    {
        beDelete = true;
        vars.erase(it);
        return sp;
    }

    auto& var = it->second;

    switch (var->type) {

    case cust_var_type_normal:
    case cust_var_type_temp:
        return var;

    case cust_var_type_daily:
        if (time(nullptr) <= var->expire)
            return var;

        beDelete = true;
        vars.erase(it);
    }
    return sp;
}

void CustVarMgr::SetGlobalVars(CUST_VAR_SP_LIST vars)
{
    auto curTime = time(nullptr);

    for (auto &var : vars) {
        if (!var) continue;

        if (var->expire > 0 && curTime > var->expire)
            SendSetCustVarToCS(*var);
        else
            mGlobalVars[var->belong][var->name] = std::move(var);
    }
}

void CustVarMgr::CheckExpired(CUST_VAR_MAP& CustVars)
{
    auto curTime = time(nullptr);

    for (auto it = CustVars.begin(); it != CustVars.end(); ) {

        auto& var = it->second;

        if (var.expire > 0 && curTime > var.expire)
            it = CustVars.erase(it);
        else
            ++it;
    }
}

void CustVarMgr::CheckExpired_CS(CUST_VAR_MAP& CustVars)
{
    auto curTime = time(nullptr);

    for (auto it = CustVars.begin(); it != CustVars.end(); ) {

        auto& var = it->second;

        if (var.expire > 0 && curTime > var.expire)
            it = CustVars.erase(it);
        else if (var.type == cust_var_type_temp)
            it = CustVars.erase(it);
        else
            ++it;
    }
}

void CustVarMgr::CheckExpiredAndCollect(CUST_VAR_SP_MAP& CustVars, CUST_VAR_SP_LIST& vars)
{
    auto curTime = time(nullptr);

    for (auto it = CustVars.begin(); it != CustVars.end(); ) {
        auto& var = it->second;
        if (!var)
        {
            ++it;
            continue;
        }

        if (var->expire > 0 && curTime > var->expire)
        {
            SendDBLogData(log_type_item_cust_var, LogItemCustVar(var->belong, var->name, "", 0, 0));
            it = CustVars.erase(it);
        }
        else
        {
            vars.emplace_back(var);
            ++it;
        }
    }
}