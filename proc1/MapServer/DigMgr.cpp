#include "stdafx.h"
#include "DigMgr.h"

DigMgr::DigMgr(Player *player) : mPlayer(player)
{
}

void DigMgr::HandleDigRequest(uint64_t treasureGUID)
{
    uint32_t digTime = 0;
    auto result = StartDig(treasureGUID, digTime);
    SendStartDigAckToGS(treasureGUID, result, digTime);
    if (result != start_dig_ok) return;
    mPlayer->SendRoleAppearNtfToAroundPlayers(role_appear_digging);
    AddEventHandler();
    AddDigRecord(treasureGUID);
    SetTreasureGUID(treasureGUID);
}

int DigMgr::StartDig(uint64_t treasureGUID, uint32_t &digTime)
{
    SAFE_BEGIN_EX;

    auto *treasure = MapRoleMgr::GetInstance()->FindMonster(treasureGUID);
    if (!treasure) return start_dig_no_target;

    auto *cfg = treasure->GetConfig();
    if (!cfg) return start_dig_no_target;

    if (mPlayer->DistanceFromRole(treasure) > cfg->VieRange)        // VieRange为可以挖宝距离
        return start_dig_out_of_range;

    if (IsDigging()) return start_dig_digging;

    auto ret = NewLuaObj();
    TRIGGER_EVENT_RET(ret, mPlayer, trigger_start_dig, mPlayer->GetGUIDAsString(),
        std::to_string(treasureGUID), cfg->MovTime);                // MovTime为读条倒计时

    if (luabind::type(ret) != LUA_TTABLE) {
        LOG_ERROR("trigger_start_dig invalid return type");
        return start_dig_other_reason;
    }

    auto canStart = luabind::object_cast<bool>(ret[1]);
    if (!canStart) return start_dig_other_reason;

    digTime = luabind::object_cast<uint32_t>(ret[2]);
    StartDigTimer(digTime);

    return start_dig_ok;

    SAFE_END_EX(start_dig_other_reason);
}

void DigMgr::StopDig(int reason)
{
    if (!IsDigging()) return;

    StopDigTimer();
    auto treasureGUID = GetTreasureGUID();
    SendStopDigNtfToGS(treasureGUID, reason);
    mPlayer->SendRoleAppearNtfToAroundPlayers(role_appear_normal);
    RemoveEventHandler();
    RemoveDigRecord(treasureGUID);
    SetTreasureGUID(0);
}

void DigMgr::StartDigTimer(uint32_t countdown)
{
    auto playerGUID = mPlayer->GetGUID();

    auto callback = [=](const TimerData &) {
        auto *player = MapRoleMgr::GetInstance()->FindPlayer(playerGUID);
        if (!player) return;
        OnDigTimeup();
    };

    mDigTimerID = ITimeHelper::GetInstance()->AddTimer(countdown, false, callback);
}

void DigMgr::StopDigTimer()
{
    if (mDigTimerID == 0) return;
    ITimeHelper::GetInstance()->RemoveTimer(mDigTimerID);
    mDigTimerID = 0;
}

void DigMgr::SendStartDigAckToGS(uint64_t treasureGUID, int code, uint32_t digTime)
{
    ProtoMS_StartDigAck data;
    data.clsessid = mPlayer->GetClSessionID();
    data.treasure_guid = treasureGUID;
    data.code = static_cast<uint8_t>(code);
    data.dig_time = digTime;

    SendDataBySessionID(mPlayer->GetGsSessionID(), data);
}

void DigMgr::SendStopDigNtfToGS(uint64_t treasureGUID, int reason)
{
    ProtoMS_StopDigNtf data;

    data.clsessid = mPlayer->GetClSessionID();
    data.treasure_guid = treasureGUID;
    data.reason = static_cast<uint8_t>(reason);

    SendDataBySessionID(mPlayer->GetGsSessionID(), data);
}

void DigMgr::OnDigTimeup()
{
    auto treasureGUID = GetTreasureGUID();  // StopDig会将treasureGUID置0，因此提前获取
    StopDig(stop_dig_timeup);

    auto diggers = TreasureDiggerRecorder::Instance().GetDiggers(treasureGUID);

    // diggers中已不包含自己
    for (auto &playerGUID : diggers) {
        auto *player = MapRoleMgr::GetInstance()->FindPlayer(playerGUID);
        if (!player) continue;
        player->GetDigMgr().OnTakenAway();
    }

    TRIGGER_EVENT(mPlayer, trigger_dig_timesup, mPlayer->GetGUIDAsString(), std::to_string(treasureGUID));
}

void DigMgr::OnRoleMove()
{
    StopDig(stop_dig_role_move);
}

void DigMgr::OnRoleDie()
{
    StopDig(stop_dig_role_die);
}

void DigMgr::OnTakenAway()
{
    StopDig(stop_dig_taken_away);
}

void DigMgr::AddEventHandler()
{
    if (mRoleMoveHandlerID == 0)
        mRoleMoveHandlerID = mPlayer->AddEventHandler_StartMove([=]{ OnRoleMove(); });

    if (mRoleDieHandlerID == 0)
        mRoleDieHandlerID = mPlayer->AddEventHandler_RoleDie([=]{ OnRoleDie(); });
}

void DigMgr::RemoveEventHandler()
{
    mPlayer->RemoveEventHandler_RoleDie(mRoleMoveHandlerID);
    mRoleMoveHandlerID = 0;

    mPlayer->RemoveEventHandler_RoleDie(mRoleDieHandlerID);
    mRoleDieHandlerID = 0;
}

void DigMgr::AddDigRecord(uint64_t treasureGUID)
{
    TreasureDiggerRecorder::Instance().AddRecord(treasureGUID, mPlayer->GetGUID());
}

void DigMgr::RemoveDigRecord(uint64_t treasureGUID)
{
    TreasureDiggerRecorder::Instance().RemoveRecord(treasureGUID, mPlayer->GetGUID());
}

////////////////////////////////////////////////////////////////////////////////
//
// TreasureDiggerRecorder
//

TreasureDiggerRecorder TreasureDiggerRecorder::mInstance;

void TreasureDiggerRecorder::AddRecord(uint64_t treasureGUID, uint64_t roleGUID)
{
    auto &diggers = mRecorder[treasureGUID];
    diggers.insert(roleGUID);
}

void TreasureDiggerRecorder::RemoveRecord(uint64_t treasureGUID, uint64_t roleGUID)
{
    auto it = mRecorder.find(treasureGUID);
    if (it == mRecorder.end()) return;
    auto &diggers = it->second;
    diggers.erase(roleGUID);
    if (diggers.empty()) mRecorder.erase(it);
}

TreasureDiggerRecorder::Diggers TreasureDiggerRecorder::GetDiggers(uint64_t treasureGUID)
{
    auto it = mRecorder.find(treasureGUID);
    if (it == mRecorder.end()) return Diggers();
    return it->second;
}