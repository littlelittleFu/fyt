#pragma once

#include "ProtoMS.h"

class WantedList
{
    DECL_SINGLETON(WantedList);

public:
    void SetRecvFromDB(bool recvd) { mRecvFromDB = recvd; }
    bool HasRecvFromDB() { return mRecvFromDB; }

    void SetWantedList(WANTED_SP_LIST wantedList) { mWantedList = std::move(wantedList); }
    WANTED_SP_LIST & GetWantedList() { return mWantedList; }

    void AddToWantedList(const ProtoMS_PostBountyAck *ack);

    void ChangeNameInfo(uint64_t guid, const std::string& name);

protected:
    WantedList() {}

private:
    WANTED_SP_LIST  mWantedList;

    bool            mRecvFromDB = false;
};