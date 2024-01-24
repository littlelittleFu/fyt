#include "stdafx.h"
#include "WantedList.h"

IMPL_SINGLETON(WantedList)

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
            return;
        }
    }

    auto spWanted = std::make_shared<WANTED>();
    spWanted->guid = ack->wanted_guid;
    spWanted->name = ack->wanted_name;
    spWanted->wanted_by_list.emplace_back(std::move(spWantedBy));

    mWantedList.emplace_back(std::move(spWanted));
}

void WantedList::ChangeNameInfo(uint64_t guid, const std::string& name)
{
    for (auto i : mWantedList) {
        if (!i.get()) continue;
        if (i.get()->guid == guid) {
            i.get()->name = name;

        }

        for (auto iter : i.get()->wanted_by_list) {
            if (!iter) continue;
            if (iter->guid == guid) {
                iter->name = name;
            }
        }
    }
}