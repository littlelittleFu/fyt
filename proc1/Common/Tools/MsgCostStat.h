#pragma once

class MsgCostStat
{
    DECL_SINGLETON(MsgCostStat);

private:
    struct MsgCostData
    {
        int     time        = 0;
        int     num         = 0;
    };

public:
    void StartStat();
    void StopStat();

    void BeginHandleMsg();
    void EndHandleMsg(uint16_t moduleid, uint16_t protoid);
    void EndHandleMsg(int msgid);

    std::string CollMsgCostInfo();

private:
    bool        mStat       = false;
    uint64_t    mStartTime  = 0;

    std::map<int, MsgCostData> mMsgCostMap;
};
