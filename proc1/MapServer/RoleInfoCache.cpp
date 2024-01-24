#include "stdafx.h"
#include "RoleInfoCache.h"

IMPL_SINGLETON(RoleInfoCache);

void RoleInfoCache::AddRoleInfo(RoleInfoSP spRoleInfo)
{
    if (spRoleInfo->guid) {
        mGUIDToRoleInfoSPMap[spRoleInfo->guid] = spRoleInfo;
    }

    if (!spRoleInfo->name.empty()) {
        mNameToRoleInfoSPMap[spRoleInfo->name] = spRoleInfo;
    }
}

RoleInfoSP RoleInfoCache::GetRoleInfo(uint64_t guid)
{
    auto it = mGUIDToRoleInfoSPMap.find(guid);
    if (it == mGUIDToRoleInfoSPMap.end()) return nullptr;
    return it->second;
}

RoleInfoSP RoleInfoCache::GetRoleInfo(const std::string &name)
{
    auto it = mNameToRoleInfoSPMap.find(name);
    if (it == mNameToRoleInfoSPMap.end()) return nullptr;
    return it->second;
}

void RoleInfoCache::OnRoleLogin(uint64_t guid, const std::string &name)
{
    if (guid == 0 || name.empty()) return;

    auto it = mGUIDToRoleInfoSPMap.find(guid);
    if (it != mGUIDToRoleInfoSPMap.end()) return;

    auto spRoleInfo = std::make_shared<RoleInfo>(guid, name, true);
    mGUIDToRoleInfoSPMap.emplace(guid, spRoleInfo);
    mNameToRoleInfoSPMap[name] = std::move(spRoleInfo);
}

void RoleInfoCache::OnDeleteRole(uint64_t guid)
{
    if (guid == 0) return;

    auto it = mGUIDToRoleInfoSPMap.find(guid);

    if (it != mGUIDToRoleInfoSPMap.end()) {

        auto &spRoleInfo = it->second;
        if (spRoleInfo) {
            spRoleInfo->exist = false;
            return;
        }
    }

    auto spRoleInfo = std::make_shared<RoleInfo>(guid, EMPTYSTR, false);
    mGUIDToRoleInfoSPMap[guid] = std::move(spRoleInfo);
}

////////////////////////////////////////////////////////////////////////////////
//
// RoleInfoPendingQueryMgr
//

IMPL_SINGLETON(RoleInfoPendingQueryMgr);

bool RoleInfoPendingQueryMgr::CacheQuery(RoleInfoPendingQuerySP query)
{
    auto seq = query->seq;

    auto it = mPendingQueries.find(seq);
    if (it != mPendingQueries.end()) return false;

    auto TimerCallback = [=] (const TimerData &) {
        RoleInfoPendingQueryMgr::GetInstance()->RemoveQuery(seq);
    };

    const uint32_t INTVL = 10000;
    query->timer = ITimeHelper::GetInstance()->AddTimer(INTVL, false, TimerCallback);

    mPendingQueries.emplace(seq, std::move(query));
    return true;
}

void RoleInfoPendingQueryMgr::RemoveQuery(uint32_t seq)
{
    auto it = mPendingQueries.find(seq);
    if (it == mPendingQueries.end()) return;

    ITimeHelper::GetInstance()->RemoveTimer(it->second->timer);
    mPendingQueries.erase(it);
}

RoleInfoPendingQuerySP RoleInfoPendingQueryMgr::GetQuery(uint32_t seq)
{
    auto it = mPendingQueries.find(seq);
    return (it == mPendingQueries.end()) ? nullptr : it->second;
}
