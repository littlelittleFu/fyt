#include "stdafx.h"
#include "CLuaLib.h"
#include "LuaEngine.h"
#include "LuaWrap.h"
#include "MapMgr.h"
#include "MapRoleMgr.h"

IMPL_SINGLETON(CLuaLib)

void CLuaLib::AddTrigger(uint64_t objGUID, uint32_t eventID, const::std::string& callBack)
{
    SAFE_BEGIN;

    if (objGUID == 0) {
        Globle::GetInstance()->AddTrigger(eventID, callBack);
        return;
    }

    if (IS_MAP_GUID(objGUID)) {
        auto map = MapMgr::GetInstance()->FindMapByGUID(objGUID);
        if (nullptr != map)
        {
            map->AddTrigger(eventID, callBack);
        }
        return;
    }

    if (IS_ROLE_GUID(objGUID)) {
        auto role = MapRoleMgr::GetInstance()->FindRole(objGUID);
        if (nullptr != role)
        {
            role->AddTrigger(eventID, callBack);
        }
        return;
    }

    SAFE_END;
}

void CLuaLib::AddTrigger(const std::string& objGUID, uint32_t eventID, const::std::string& callBack)
{
	SAFE_BEGIN;

    auto guid = objGUID.empty() ? 0 : std::stoull(objGUID);
    AddTrigger(guid, eventID, callBack);

	SAFE_END;
}

void CLuaLib::RemoveTrigger(uint64_t objGUID, uint32_t eventID, const::std::string& callBack)
{
    SAFE_BEGIN;

    if (objGUID == 0) {
        Globle::GetInstance()->RemoveTrigger(eventID, callBack);
        return;
    }

    if (IS_MAP_GUID(objGUID)) {
        auto map = MapMgr::GetInstance()->FindMapByGUID(objGUID);
        if (nullptr != map) map->RemoveTrigger(eventID, callBack);
        return;
    }

    if (IS_ROLE_GUID(objGUID)) {
        auto role = MapRoleMgr::GetInstance()->FindRole(objGUID);
        if (nullptr != role) role->RemoveTrigger(eventID, callBack);
        return;
    }

    SAFE_END;
}

void CLuaLib::RemoveTrigger(const std::string& objGUID, uint32_t eventID, const::std::string& callBack)
{
	SAFE_BEGIN;

    auto guid = objGUID.empty() ? 0 : std::stoull(objGUID);
    RemoveTrigger(guid, eventID, callBack);

	SAFE_END;
}

bool CLuaLib::IsHaveEvent(uint32_t eventID)
{
    auto result = Globle::GetInstance()->IsHaveEvent(eventID);
    return result;
}
