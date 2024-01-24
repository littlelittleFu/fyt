#include "stdafx.h"
#include "MsgCostStat.h"
#include "ITimeHelper.h"

IMPL_SINGLETON(MsgCostStat);

void MsgCostStat::StartStat()
{
    mStat = true;
}

void MsgCostStat::StopStat()
{
    if (!mStat) return;
    mMsgCostMap.clear();
    mStat = false;
}

void MsgCostStat::BeginHandleMsg()
{
    if (!mStat) return;
    mStartTime = ITimeHelper::GetInstance()->GetTimeStamp();
}

void MsgCostStat::EndHandleMsg(uint16_t moduleid, uint16_t protoid)
{
    EndHandleMsg(moduleid * 10000 + protoid);
}

void MsgCostStat::EndHandleMsg(int msgid)
{
    if (!mStat) return;

    auto endTime = ITimeHelper::GetInstance()->GetTimeStamp();
    auto costTime = static_cast<int>(endTime - mStartTime);

    auto &costData = mMsgCostMap[msgid];
    costData.time += costTime;
    costData.num += 1;
}

std::string MsgCostStat::CollMsgCostInfo()
{
    if (mMsgCostMap.empty()) return "";

    char buf[100];
    std::string info;

    for (const auto &it : mMsgCostMap) {
        sprintf_s(buf, _countof(buf), "msg: %d, cost: %d, num: %d, ave: %d",
                  it.first, it.second.time, it.second.num, it.second.time / it.second.num);
        if (!info.empty()) info += "\n";
        info += buf;
    }

    mMsgCostMap.clear();
    return info;
}
