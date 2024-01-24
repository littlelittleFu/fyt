#pragma once

struct RoleInfo
{
    uint64_t        guid = 0;
    std::string     name;
    bool            exist = false;

    RoleInfo() = default;

    RoleInfo(uint64_t guid_, const std::string &name_, bool exist_)
        : guid(guid_), name(name_), exist(exist_)
    {}
};

using RoleInfoSP = std::shared_ptr<RoleInfo>;
using NameToRoleInfoSPMap = std::map<std::string, RoleInfoSP>;
using GUIDToRoleInfoSPMap = std::map<uint64_t, RoleInfoSP>;

class RoleInfoCache
{
    DECL_SINGLETON(RoleInfoCache);

public:
    void AddRoleInfo(RoleInfoSP spRoleInfo);
    RoleInfoSP GetRoleInfo(uint64_t guid);
    RoleInfoSP GetRoleInfo(const std::string &name);

    void OnRoleLogin(uint64_t guid, const std::string &name);
    void OnDeleteRole(uint64_t guid);

private:
    RoleInfoCache() = default;

private:
    NameToRoleInfoSPMap mNameToRoleInfoSPMap;
    GUIDToRoleInfoSPMap mGUIDToRoleInfoSPMap;
};

struct RoleInfoPendingQuery
{
    uint32_t        seq         = 0;
    uint32_t        timer       = 0;
    CLuaObject      callback;

    RoleInfoPendingQuery(uint32_t seq_, const CLuaObject &cb)
        : seq(seq_), callback(cb)
    {}
};

using RoleInfoPendingQuerySP = shared_ptr<RoleInfoPendingQuery>;
using SeqToRoleInfoPendingQuerySPMap = std::map<uint32_t, RoleInfoPendingQuerySP>;

class RoleInfoPendingQueryMgr
{
    DECL_SINGLETON(RoleInfoPendingQueryMgr);

public:
    bool CacheQuery(RoleInfoPendingQuerySP query);
    void RemoveQuery(uint32_t seq);
    RoleInfoPendingQuerySP GetQuery(uint32_t seq);

private:
    SeqToRoleInfoPendingQuerySPMap mPendingQueries;
};