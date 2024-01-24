#include "stdafx.h"
#include "WantedList.h"

IMPL_SINGLETON(WantedList)

void WantedList::SetWantedList(WANTED_SP_LIST wantedList)
{
    mWantedList = std::move(wantedList);
    SortList();
}

void WantedList::SortList()
{
    auto f = [this](const WANTED_SP &left, const WANTED_SP &right) {

        auto nLeftBounty = GetTotalBounty(left);
        auto nRightBounty = GetTotalBounty(right);

        if (nLeftBounty > nRightBounty) return true;    // 按赏金降序
        if (nLeftBounty < nRightBounty) return false;

        // 赏金相等按首次悬赏时间升序
        if (left->wanted_by_list.empty()) return false;
        if (right->wanted_by_list.empty()) return true;

        return left->wanted_by_list.front()->ptime <= right->wanted_by_list.front()->ptime;
    };

    mWantedList.sort(f);
}

uint32_t WantedList::GetTotalBounty(const WANTED_SP &wanted) const
{
    uint32_t total = 0;

    for (const auto &wanted_by : wanted->wanted_by_list)
        total += wanted_by->bounty;

    return total;
}

void WantedList::AddToWantedList(const ProtoMS_PostBountyAck *ack)
{
    if (!ack) return;

    auto spWantedBy = std::make_shared<WANTED_BY>();
    spWantedBy->index = ack->index;
    spWantedBy->guid = ack->wanted_by_guid;
    spWantedBy->name = ack->wanted_by_name;
    spWantedBy->desc = ack->desc;
    spWantedBy->bounty = ack->bounty;
    spWantedBy->ptime = ack->ptime;

    for (auto &spWanted : mWantedList) {
        if (spWanted->guid == ack->wanted_guid) {
            spWanted->wanted_by_list.emplace_back(std::move(spWantedBy));
            SortList();
            return;
        }
    }

    auto spWanted = std::make_shared<WANTED>();
    spWanted->guid = ack->wanted_guid;
    spWanted->name = ack->wanted_name;
    spWanted->wanted_by_list.emplace_back(std::move(spWantedBy));

    mWantedList.emplace_back(std::move(spWanted));
    SortList();
}