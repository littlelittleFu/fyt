#include "stdafx.h"
#include "ObjID.h"
#include "Object.h"
#include <chrono>
#include <atomic>

uint64_t GenerateObjID(EObjType nObjType, IConfigInfo* pConfig)
{
    static const uint16_t arrSize = E_OBJ_TYPE_NUM;
    uint16_t type = nObjType;
    if (nObjType <= E_OBJ_NULL || nObjType >= E_OBJ_TYPE_NUM) return 0;
    assert(pConfig != nullptr);
    if (!pConfig) return 0;

    uint64_t nObjID = 0;
    uint32_t areaID = pConfig->GetCurAreaId();
    uint32_t areaServerID = pConfig->GetCurAreaServerId();
    uint32_t serverID = pConfig->GetCurServerId();
    nObjID =  uint64_t((uint64_t)nObjType       & uint64_t(0x000000000000001F)) << 59;

    static std::atomic<uint64_t> inc[arrSize];
    uint64_t prev = inc[type].fetch_add(1);

    using std::chrono::duration_cast;
    using std::chrono::seconds;
    using std::chrono::system_clock;
    uint64_t timestamp = (uint64_t)duration_cast<seconds>(system_clock::now().time_since_epoch()).count() - uint64_t(GUID_BEGIN_TIME);

    if (nObjType == E_OBJ_PLAYER || nObjType == E_OBJ_MAIL
        || nObjType == E_OBJ_GUILD || nObjType == E_OBJ_BUFF
        || nObjType == E_OBJ_AUCTION || nObjType == E_OBJ_MARKET)
    {
        nObjID |= uint64_t((uint64_t)areaID         & uint64_t(0x000000000000007F)) << 52;
        nObjID |= uint64_t((uint64_t)areaServerID   & uint64_t(0x00000000000003FF)) << 42;
        nObjID |= uint64_t((uint64_t)timestamp      & uint64_t(0x000000000FFFFFFF)) << 14;
        nObjID |= uint64_t((uint64_t)prev           & uint64_t(0x0000000000003FFF));
    }
    else if (nObjType == E_OBJ_ITEM)
    {
        nObjID |= uint64_t((uint64_t)areaID         & uint64_t(0x000000000000007F)) << 52;
        nObjID |= uint64_t((uint64_t)areaServerID   & uint64_t(0x00000000000003FF)) << 42;
        nObjID |= uint64_t((uint64_t)serverID       & uint64_t(0x0000000000000001)) << 41;
        nObjID |= uint64_t((uint64_t)timestamp      & uint64_t(0x000000000FFFFFFF)) << 13;
        nObjID |= uint64_t((uint64_t)prev           & uint64_t(0x0000000000001FFF));
    }
    else
    {
        nObjID |= uint64_t((uint64_t)timestamp      & uint64_t(0x000000000FFFFFFF)) << 31;
        nObjID |= uint64_t((uint64_t)prev           & uint64_t(0x000000007FFFFFFF));
    }

    return nObjID;
}
uint64_t GetTimePart(uint64_t guid)
{
    uint16_t nObjType = GUID_TYPE_PART(guid);
    uint64_t timestamp = 0;
    uint16_t rsbit = 0;
    if (nObjType == E_OBJ_PLAYER || nObjType == E_OBJ_MAIL
        || nObjType == E_OBJ_GUILD || nObjType == E_OBJ_BUFF
        || nObjType == E_OBJ_AUCTION || nObjType == E_OBJ_MARKET)
    {
        rsbit = 14;
    }
    else if (nObjType == E_OBJ_ITEM)
    {
        rsbit = 13;
    }
    else
    {
        rsbit = 31;
    }
    timestamp = (uint64_t)(((uint64_t(guid) >> rsbit) & uint64_t(0x000000000FFFFFFF)) + uint64_t(GUID_BEGIN_TIME));
    
    return timestamp;
}
