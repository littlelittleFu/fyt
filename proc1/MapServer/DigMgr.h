#pragma once

class Player;

class DigMgr
{
public:
    DigMgr(Player *player);

    void        HandleDigRequest(uint64_t treasureGUID);
    bool        IsDigging() { return mDigTimerID != 0; }
    void        OnTakenAway();

private:
    int         StartDig(uint64_t treasureGUID, uint32_t &digTime);
    void        StopDig(int reason);

    void        StartDigTimer(uint32_t countdown);
    void        StopDigTimer();

    void        SetTreasureGUID(uint64_t guid) { mTreasureGUID = guid; }
    uint64_t    GetTreasureGUID() { return mTreasureGUID; }

    void        SendStartDigAckToGS(uint64_t treasureGUID, int code, uint32_t digTime);
    void        SendStopDigNtfToGS(uint64_t treasureGUID, int reason);

    void        OnDigTimeup();
    void        OnRoleMove();
    void        OnRoleDie();

    void        AddEventHandler();
    void        RemoveEventHandler();

    void        AddDigRecord(uint64_t treasureGUID);
    void        RemoveDigRecord(uint64_t treasureGUID);

private:
    Player     *mPlayer             = nullptr;
    uint32_t    mDigTimerID         = 0;        // ÍÚ±¦¶¨Ê±Æ÷
    uint64_t    mTreasureGUID       = 0;
    uint32_t    mRoleMoveHandlerID  = 0;
    uint32_t    mRoleDieHandlerID   = 0;
};

class TreasureDiggerRecorder
{
    using Diggers = std::set<uint64_t>;
    using Recorder = std::map<uint64_t, Diggers>;

public:
    static TreasureDiggerRecorder & Instance() { return mInstance; }

    void AddRecord(uint64_t treasureGUID, uint64_t roleGUID);
    void RemoveRecord(uint64_t treasureGUID, uint64_t roleGUID);
    Diggers GetDiggers(uint64_t treasureGUID);

private:
    TreasureDiggerRecorder() {}

private:
    static TreasureDiggerRecorder   mInstance;
    Recorder                        mRecorder;
};
