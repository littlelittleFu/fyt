#pragma once

class WantedList
{
    DECL_SINGLETON(WantedList);

public:
    void SetWantedList(WANTED_SP_LIST wantedList);
    WANTED_SP_LIST & GetWantedList() { return mWantedList; }

    void AddToWantedList(const ProtoMS_PostBountyAck *ack);

private:
    WantedList() {}

    void SortList();

    uint32_t GetTotalBounty(const WANTED_SP &wanted) const;

private:
    WANTED_SP_LIST  mWantedList;
};