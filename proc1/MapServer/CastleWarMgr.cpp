#include "stdafx.h"
#include "CastleWarMgr.h"
#include "CustVarMgr.h"
#include "GuildMgr.h"



#define CASTLEWAR_VARBELONG     "0"
#define CASTLEWAR_VARNAME       "ServerInternal.CastleWar"


IMPL_SINGLETON(CastleWarMgr);


bool CastleWarMgr::RecoverCastleWar()
{
    std::string info = GetCastleWarInfoFromDB();        // 从全局自定义变量获取
    if (info.empty()) return true;

    if (!ParseCastleWarInfo(info)) return false;

    if (IsWarEnd()) return true;    // 已结束

    if (mStartTime == 0 || mDuration == 0) return false;

    uint64_t endTime = mStartTime + mDuration;          // 计划结束时间
    uint64_t curTime = time(nullptr);

    if (endTime <= curTime) {       // 超时结束
        mEndTime = curTime;
        // 是否需要通知客户端？
        SaveCastleWarInfoToDB();
        return true;
    }

    if (!CheckGuilds(mGuilds)) {    // 工会不存在
        mEndTime = curTime;         // 结束攻沙
        // 是否需要通知客户端？
        SaveCastleWarInfoToDB();
        return false;
    }

    if (mStartTime > curTime) {
        SetStartTimer();
    }
    else {
        OnWarStart();
    }

    return true;
}

std::string CastleWarMgr::GetCastleWarInfoFromDB()
{
    return CustVarMgr::GetInstance()->GetVar(CASTLEWAR_VARBELONG, CASTLEWAR_VARNAME);
}

void CastleWarMgr::SaveCastleWarInfoToDB()
{
    std::string info = AssembleCastleWarInfo();
    CustVarMgr::GetInstance()->SetVar(CASTLEWAR_VARBELONG, CASTLEWAR_VARNAME, std::move(info), cust_var_type_normal, cvmt_delete);
}

bool CastleWarMgr::ParseCastleWarInfo(const std::string &info)
{
    if (info.empty()) return false;

    Json::Value root;
    Json::Reader reader;

    if (!reader.parse(info, root)) {
        LOG_ERROR("parse failed, castle war info: %s", info.c_str());
        return false;
    }

    // startTime
    if (!root.isMember("startTime")) {
        LOG_ERROR("No member startTime");
        return false;
    }
    auto &startTime = root["startTime"];
    if (!startTime.isString()) {
        LOG_ERROR("startTime is not string");
        return false;
    }
    auto nStartTime = std::stoull(startTime.asString());

    // duration
    if (!root.isMember("duration")) {
        LOG_ERROR("No member duration");
        return false;
    }
    auto &duration = root["duration"];
    if (!duration.isInt()) {
        LOG_ERROR("duration is not int");
        return false;
    }
    auto nDuration = duration.asUInt();

    // endTime
    if (!root.isMember("endTime")) {
        LOG_ERROR("No member endTime");
        return false;
    }
    auto &endTime = root["endTime"];
    if (!endTime.isString()) {
        LOG_ERROR("endTime is not string");
        return false;
    }
    auto nEndTime = std::stoull(endTime.asString());

    // guilds
    if (!root.isMember("guilds")) {
        LOG_ERROR("No member guilds");
        return false;
    }
    auto &guilds = root["guilds"];
    if (!guilds.isArray()) {
        LOG_ERROR("guilds is not array");
        return false;
    }
    GuildList guildList;
    for (auto i = 0; i < guilds.size(); ++i) {
        auto &guild = guilds[i];
        if (!guild.isString()) {
            LOG_ERROR("guild is not string");
            return false;
        }
        guildList.emplace_back(guild.asString());
    }

    // winner
    if (!root.isMember("winner")) {
        LOG_ERROR("No member winner");
        return false;
    }
    auto &winner = root["winner"];
    if (!winner.isString()) {
        LOG_ERROR("winner is not string");
        return false;
    }
    auto sWinner = winner.asString();

    mStartTime = nStartTime;
    mDuration = nDuration;
    mEndTime = nEndTime;
    mGuilds = std::move(guildList);
    mWinner = std::move(sWinner);

    return true;
}

std::string CastleWarMgr::AssembleCastleWarInfo()
{
    Json::Value root;
    root["startTime"] = std::to_string(mStartTime);
    root["duration"] = mDuration;
    root["endTime"] = std::to_string(mEndTime);

    for (auto i = 0; i < mGuilds.size(); ++i) {
        root["guilds"][i] = mGuilds[i];
    }

    root["winner"] = mWinner;

    return root.toFastString();
}

bool CastleWarMgr::CheckGuilds(const GuildList &guilds)
{
    if (guilds.empty()) return false;

    for (const auto &guild : guilds) {
        if (!GuildMgr::GetInstance()->GuildExist(guild, true)) {
            LOG_ERROR("guild %s not exist", guild.c_str());
            return false;
        }
    }

    return true;
}

bool CastleWarMgr::SetStartTimer()
{
    if (mStartTimerID != 0) return true;        // 已开始
    if (mStartTime == 0) return false;

    auto curTime = time(nullptr);
    if (mStartTime <= curTime) return false;    // 已开始

    uint32_t interval = (uint32_t)S2MS(mStartTime - curTime);

    auto callback = [&](const TimerData &){
        mStartTimerID = 0;  // 一次性定时器会自动停止，因此只需重置为0即可
        OnWarStart();
    };

    mStartTimerID = ITimeHelper::GetInstance()->AddTimer(interval, false, callback);
    return (mStartTimerID != 0);
}

bool CastleWarMgr::SetEndTimer()
{
    if (mEndTimerID != 0) return true;
    if (mStartTime == 0 || mDuration == 0) return false;

    auto endTime = mStartTime + mDuration;
    auto curTime = time(nullptr);

    if (mStartTime > curTime) return false;     // 未开始
    if (endTime <= curTime) return false;       // 已结束

    uint32_t interval = (uint32_t)S2MS(endTime - curTime);

    auto callback = [&](const TimerData &){
        mEndTimerID = 0;
        OnWarEnd();
    };

    mEndTimerID = ITimeHelper::GetInstance()->AddTimer(interval, false, callback);
    return (mEndTimerID != 0);
}

void CastleWarMgr::ResetStartTimer()
{
    if (mStartTimerID == 0) return;
    ITimeHelper::GetInstance()->RemoveTimer(mStartTimerID);
    mStartTimerID = 0;
}

void CastleWarMgr::ResetEndTimer()
{
    if (mEndTimerID == 0) return;
    ITimeHelper::GetInstance()->RemoveTimer(mEndTimerID);
    mEndTimerID = 0;
}

void CastleWarMgr::OnWarStart()
{
    SetEndTimer();      // 必须首先设置结束定时器，这样IsInWar会返回true

    AddOnEnterPalaceFunc();
    AddOnLeavePalaceFunc();
    AddOnEnterMainCityFunc();
    InitPalacePlayerData();
    NotifyAllPlayersWarStart();

    // 通知客户端攻沙开始
    TRIGGER_EVENT(trigger_castle_war_start);
}

void CastleWarMgr::OnWarEnd()
{
    OnWarStop();

    // 通知客户端攻沙结束
    TRIGGER_EVENT(trigger_castle_war_end);
}

void CastleWarMgr::OnWarStop()
{
    RemoveOnEnterPalaceFunc();
    RemoveOnLeavePalaceFunc();
    RemoveOnEnterMainCityFunc();
    CleanPalacePlayerData();
    NotifyAllPlayersWarEnd();

    mEndTime = time(nullptr);
    SaveCastleWarInfoToDB();
}

void CastleWarMgr::InitPalacePlayerData()
{
    mPalacePlayerData.clear();

    auto *map = GetPalaceMap();
    if (!map) return;

    auto func = [&](Role *role){
        const auto &guild = GetRoleGuildName(role);
        if (!IsEngagedGuild(guild)) return;

        auto guid = role->GetGUID();
        auto &playerData = mPalacePlayerData[guild][guid];
        SetStateChangeFunc(role, playerData);
        playerData.bOnline = true;
    };

    map->ApplyFuncToAllRoles(func);

    RecalcWinner();
}

void CastleWarMgr::CleanPalacePlayerData()
{
    for (auto &it : mPalacePlayerData) {

        auto &players = it.second;

        for (auto &it2 : players) {

            auto &guid = it2.first;
            auto *player = MapRoleMgr::GetInstance()->FindPlayer(guid);
            if (!player) continue;

            ResetStateChangeFunc(player, it2.second);
        }
    }

    mPalacePlayerData.clear();
}

bool CastleWarMgr::AddOnEnterPalaceFunc()
{
    auto *map = GetPalaceMap();
    if (!map) return false;

    mOnEnterPalaceFuncID = map->AddOnRoleEnterFunc([=](Role *role){ OnEnterPalace(role); });
    return true;
}

bool CastleWarMgr::AddOnLeavePalaceFunc()
{
    auto *map = GetPalaceMap();
    if (!map) return false;

    mOnLeavePalaceFuncID = map->AddOnRoleLeaveFunc([=](Role *role){ OnLeavePalace(role); });
    return true;
}

bool CastleWarMgr::AddOnEnterMainCityFunc()
{
    auto *map = GetMainCityMap();
    if (!map) return false;

    mOnEnterMainCityFuncID = map->AddOnRoleEnterFunc([=](Role *role){ OnEnterMainCity(role); });
    return true;
}

void CastleWarMgr::RemoveOnEnterPalaceFunc()
{
    if (mOnEnterPalaceFuncID == 0) return;

    auto *map = GetPalaceMap();
    if (!map) return;

    map->RemoveOnRoleEnterFunc(mOnEnterPalaceFuncID);
    mOnEnterPalaceFuncID = 0;
}

void CastleWarMgr::RemoveOnLeavePalaceFunc()
{
    if (mOnLeavePalaceFuncID == 0) return;

    auto *map = GetPalaceMap();
    if (!map) return;

    map->RemoveOnRoleLeaveFunc(mOnLeavePalaceFuncID);
    mOnLeavePalaceFuncID = 0;
}

void CastleWarMgr::RemoveOnEnterMainCityFunc()
{
    if (mOnEnterMainCityFuncID == 0) return;

    auto *map = GetMainCityMap();
    if (map) return;

    map->RemoveOnRoleEnterFunc(mOnEnterMainCityFuncID);
    mOnEnterMainCityFuncID = 0;
}

bool CastleWarMgr::StartCastleWar(GuildList guilds, uint64_t startTime, uint32_t duration)
{
    if (IsWarInSchedule() || IsInWar()) return false;

    if (!CheckGuilds(guilds)) return false;

    auto curTime = time(nullptr);
    if (startTime < curTime) return false;

    mGuilds = std::move(guilds);
    mStartTime = startTime;
    mDuration = duration;
    mEndTime = 0;

    SetStartTimer();
    SaveCastleWarInfoToDB();

    return true;
}

bool CastleWarMgr::StopCastleWar()
{
    if (!IsWarInSchedule() && !IsInWar()) return true;

    ResetStartTimer();
    ResetEndTimer();

    OnWarStop();

    return true;
}

const CastleWarMgr::GuildList & CastleWarMgr::QueryEngagedGuilds()
{
    if (!IsWarInSchedule() && !IsInWar()) return GuildList{};
    return mGuilds;
}

uint64_t CastleWarMgr::QueryStartTime()
{
    if (!IsWarInSchedule() && !IsInWar()) return 0;
    return mStartTime;
}

void CastleWarMgr::GenCastleMonster(uint32_t type)
{
    auto *cfg = GetCfg();
    if (!cfg) return;

    switch (type) {

    case main_city_front_door_monster:
        GenMainCityFrontDoorMonster(cfg->MainCityMap, cfg->MainCityFrontDoorMonster.KeyName,
            cfg->MainCityFrontDoorMonster.x, cfg->MainCityFrontDoorMonster.y, cfg->MainCityFrontDoorMonsterTakePos);
        break;

    case palace_front_door_monster:
        GenMonster(cfg->MainCityMap, cfg->PalaceFrontDoorMonster.KeyName, cfg->PalaceFrontDoorMonster.x, cfg->PalaceFrontDoorMonster.y);
        break;

    case palace_side_door_monster:
        for (const auto &monster : cfg->PalaceSideDoorMonsters) {
            GenMonster(cfg->MainCityMap, monster.KeyName, monster.x, monster.y);
        }
        break;

    default:
        break;
    }
}

void CastleWarMgr::GenMainCityFrontDoorMonster(const std::string &mapName, const std::string &monsterName,
    uint16_t x, uint16_t y, const std::vector<int32_t> &seqs)
{
    auto *map = MapMgr::GetInstance()->FindMap(mapName);
    if (!map) return;

    auto *role = map->GetRoleInPoint(x, y);
    if (role && role->IsMonster()) {
        auto *monster = static_cast<Monster *>(role);
        const auto *cfg = monster->GetConfig();
        if (cfg && cfg->KeyName == monsterName) return;
    }

    auto *cfg = sMonsterConfig.Get(monsterName);
    if (!cfg) return;

    auto *monster = map->GenMonster(cfg, x, y, 1, 1, dir_down, 0, true);
    if (!monster) return;

    // 占用逻辑格
    auto &mapGrid = map->GetMapGrid();
    mapGrid.SetForbid(x, y);

    int16_t dx, dy;
    for (const auto &seq : seqs) {
        if (seq == 0) continue;
        Tools::GetRelativePos(uint16_t(seq), dx, dy);
        mapGrid.SetForbid(x + dx, y + dy);
    }

    // 退出时取消逻辑格占用
    auto ReleaseGridOnDie = [=] {
        Map *map = MapMgr::GetInstance()->FindMap(mapName);
        if (!map) return;

        auto &mapGrid = map->GetMapGrid();
        mapGrid.RemoveForbid(x, y);

        int16_t dx, dy;
        for (const auto &seq : seqs) {
            if (seq == 0) continue;
            Tools::GetRelativePos(uint16_t(seq), dx, dy);
            mapGrid.RemoveForbid(x + dx, y + dy);
        }
    };

    monster->AddEventHandler_RoleDie(ReleaseGridOnDie);
}

void CastleWarMgr::GenMonster(const std::string &mapName, const std::string &monsterName, uint16_t x, uint16_t y)
{
    auto *map = MapMgr::GetInstance()->FindMap(mapName);
    if (!map) return;

    auto *role = map->GetRoleInPoint(x, y);
    if (role && role->IsMonster()) {
        auto *monster = static_cast<Monster *>(role);
        auto *cfg = monster->GetConfig();
        if (cfg && cfg->KeyName == monsterName) return;
    }

    map->GenMapMonsterByName(monsterName, x, y, 1, 1, 1, dir_down, true);
}

bool CastleWarMgr::IsWinnerGuild(const std::string &guild)
{
    if (guild.empty()) return false;
    return (guild == mWinner);
}

bool CastleWarMgr::IsEngagedGuild(const std::string &guild)
{
    if (guild.empty()) return false;
    return std::find(mGuilds.begin(), mGuilds.end(), guild) != mGuilds.end();
}

bool CastleWarMgr::IsPalaceFrontDoorMonsterSpot(uint16_t x, uint16_t y)
{
    auto *cfg = GetCfg();
    if (!cfg) return false;
    return (x || y) && (cfg->PalaceFrontDoorMonster.x == x) && (cfg->PalaceFrontDoorMonster.y == y);
}

bool CastleWarMgr::IsInShabak(Role *role)
{
    if (!role) return false;
    const auto &roleMap = role->GetCurMapKeyName();
    if (roleMap.empty()) return false;

    const auto *sbkcfg = GetCfg();
    if (!sbkcfg) return false;

    if (roleMap == sbkcfg->MainCityMap || roleMap == sbkcfg->PalaceMap)
        return true;

    for (const auto &map : sbkcfg->RelMaps)
        if (roleMap == map) return true;

    return false;
}

void CastleWarMgr::OnEnterPalace(Role *role)
{
    if (!IsInWar()) return;

    const auto &guild = GetRoleGuildName(role);
    if (!IsEngagedGuild(guild)) return;

    auto guid = role->GetGUID();
    auto &players = mPalacePlayerData[guild];

    if (players.find(guid) != players.end()) {
        LOG_WARN("player %" PRIu64 " already exists in palace", guid);
        ResetStateChangeFunc(role, players[guid]);
    }

    SetStateChangeFunc(role, players[guid]);
    players[guid].bOnline = true;

    if (JustOneOnlinePlayerInPalace(players)) {
        RecalcWinner();
    }
}

void CastleWarMgr::OnLeavePalace(Role *role)
{
    if (!IsInWar()) return;

    const auto &guild = GetRoleGuildName(role);
    auto it = mPalacePlayerData.find(guild);
    if (it == mPalacePlayerData.end()) return;

    auto &players = it->second;
    auto guid = role->GetGUID();
    auto it2 = players.find(guid);
    if (it2 == players.end()) return;

    auto &playerData = it2->second;
    ResetStateChangeFunc(role, playerData);

    players.erase(it2);
    if (NoOnlinePlayerInPalace(players)) {
        RecalcWinner();
    }
}

void CastleWarMgr::SetStateChangeFunc(Role *role, PlayerData &playerData)
{
    playerData.nOnDieFuncID = role->AddEventHandler_RoleDie([=]{ OnRoleDie(role); });
    playerData.nOnExitFuncID = role->AddEventHandler_RoleExit([=]{ OnRoleExit(role); });
    playerData.nOnlineFuncID = role->AddEventHandler_RoleOnline([=]{ OnRoleOnline(role); });
    playerData.nOfflineFuncID = role->AddEventHandler_RoleOffline([=]{ OnRoleOffline(role); });
}

void CastleWarMgr::ResetStateChangeFunc(Role *role, PlayerData &playerData)
{
    role->RemoveEventHandler_RoleDie(playerData.nOnDieFuncID);
    role->RemoveEventHandler_RoleExit(playerData.nOnExitFuncID);
    role->RemoveEventHandler_RoleOnline(playerData.nOnlineFuncID);
    role->RemoveEventHandler_RoleOffline(playerData.nOfflineFuncID);
}

void CastleWarMgr::OnEnterMainCity(Role *role)
{
    if (!IsInWar()) return;
    if (!role || !role->IsPlayer()) return;
    auto *player = static_cast<Player *>(role);
    SendShabakEngageNtfToGS(player);
}

void CastleWarMgr::OnRoleDie(Role *role)
{
    OnLeavePalace(role);
}

void CastleWarMgr::OnRoleExit(Role *role)
{
    OnLeavePalace(role);
}

void CastleWarMgr::OnRoleOnline(Role *role)
{
    if (!role) return;

    const auto &guild = GetRoleGuildName(role);

    auto it = mPalacePlayerData.find(guild);
    if (it == mPalacePlayerData.end()) return;

    auto &players = it->second;
    auto guid = role->GetGUID();

    auto it2 = players.find(guid);
    if (it2 == players.end()) return;

    auto &playerData = it2->second;
    playerData.bOnline = true;

    if (JustOneOnlinePlayerInPalace(players)) {
        RecalcWinner();
    }
}

void CastleWarMgr::OnRoleOffline(Role *role)
{
    if (!role) return;

    const auto &guild = GetRoleGuildName(role);

    auto it = mPalacePlayerData.find(guild);
    if (it == mPalacePlayerData.end()) return;

    auto &players = it->second;
    auto guid = role->GetGUID();

    auto it2 = players.find(guid);
    if (it2 == players.end()) return;

    auto &playerData = it2->second;
    playerData.bOnline = false;

    if (NoOnlinePlayerInPalace(players)) {
        RecalcWinner();
    }
}

const std::string & CastleWarMgr::GetRoleGuildName(Role *role)
{
    if (!role || !role->IsPlayer()) return EMPTYSTR;
    auto *player = static_cast<Player *>(role);
    return player->GetGuildName();
}

bool CastleWarMgr::NoOnlinePlayerInPalace(const PlayerDataMap &players)
{
    return std::none_of(players.begin(), players.end(), [](const auto &it) {
        return it.second.bOnline;
    });
}

bool CastleWarMgr::AnyOnlinePlayerInPalace(const PlayerDataMap &players)
{
    return std::any_of(players.begin(), players.end(), [](const auto &it) {
        return it.second.bOnline;
    });
}

bool CastleWarMgr::JustOneOnlinePlayerInPalace(const PlayerDataMap &players)
{
    uint32_t num = 0;
    for (const auto &it : players) {
        const auto &playerData = it.second;
        if (playerData.bOnline) {
            num += 1;
            if (num > 1) return false;
        }
    }
    return (num == 1);
}

void CastleWarMgr::RecalcWinner()
{
    std::string newWinner;

    for (const auto &it : mPalacePlayerData) {
        if (AnyOnlinePlayerInPalace(it.second)) {
            if (newWinner.empty()) {
                newWinner = it.first;
            }
            else {                      // 至少有两个行会同时在皇宫中
                newWinner.clear();
                break;
            }
        }
    }

    if (!newWinner.empty() && newWinner != mWinner) {
        OnWinnerChange(std::move(newWinner));
    }
}

void CastleWarMgr::OnWinnerChange(std::string newWinner)
{
    std::string oldWinner = std::move(mWinner);
    mWinner = std::move(newWinner);

    NotifyLossMembers(oldWinner);
    NotifyWinnerMembers(mWinner);

    TRIGGER_EVENT(trigger_castle_owner_changed, oldWinner, mWinner);
}

void CastleWarMgr::NotifyWinnerMembers(const std::string &winnerGuild)
{
    if (winnerGuild.empty()) return;

    auto *guildMgr = GuildMgr::GetInstance();
    if (!guildMgr) return;

    auto guildID = guildMgr->GetGuildIDByName(winnerGuild);
    if (guildID == 0) return;

    const auto *memberList = guildMgr->GetMemberList(guildID);
    if (!memberList) return;

    for (const auto &member : *memberList) {
        if (!member->online) continue;
        auto *player = MapRoleMgr::GetInstance()->FindPlayer(member->player_id);
        NotifyAroundPlayers_ShabakOwnerNtf(player);
    }
}

void CastleWarMgr::NotifyLossMembers(const std::string &lossGuild)
{
    if (lossGuild.empty()) return;

    auto *guildMgr = GuildMgr::GetInstance();
    if (!guildMgr) return;

    auto guildID = guildMgr->GetGuildIDByName(lossGuild);
    if (guildID == 0) return;

    const auto *memberList = guildMgr->GetMemberList(guildID);
    if (!memberList) return;

    for (const auto &member : *memberList) {
        if (!member->online) continue;
        auto *player = MapRoleMgr::GetInstance()->FindPlayer(member->player_id);
        NotifyAroundPlayers_ShabakLossNtf(player);
    }
}

void CastleWarMgr::NotifyAllPlayersWarStart()
{
    if (!IsWarInSchedule() && !IsInWar()) return;
    auto f = [&](Role *role){
        if (!role || !role->IsPlayer()) return;
        auto *player = static_cast<Player *>(role);
        SendShabakEngageNtfToGS(player);
    };

    auto *map = GetMainCityMap();
    if (map) map->ApplyFuncToAllRoles(f);

    map = GetPalaceMap();
    if (map) map->ApplyFuncToAllRoles(f);
}

void CastleWarMgr::NotifyAllPlayersWarEnd()
{
    auto f = [&](Role *role){
        if (!role || !role->IsPlayer()) return;
        auto *player = static_cast<Player *>(role);
        SendShabakEndNtfToGS(player);
    };

    auto *map = GetMainCityMap();
    if (map) map->ApplyFuncToAllRoles(f);

    map = GetPalaceMap();
    if (map) map->ApplyFuncToAllRoles(f);
}

DATA::Shabak * CastleWarMgr::GetCfg()
{
    if (sShabakConfig.GetSize() < 1) return nullptr;
    return sShabakConfig.At(0);
}

Map * CastleWarMgr::GetMainCityMap()
{
    auto *cfg = GetCfg();
    if (!cfg) return nullptr;
    return MapMgr::GetInstance()->FindMap(cfg->MainCityMap);
}

Map * CastleWarMgr::GetPalaceMap()
{
    auto *cfg = GetCfg();
    if (!cfg) return nullptr;
    return MapMgr::GetInstance()->FindMap(cfg->PalaceMap);
}

void CastleWarMgr::NotifyAroundPlayers_ShabakLossNtf(Player* player)
{
    if (!player) return;

    ProtoMS_ShabakLossNtf data;
    data.role_guid = player->GetGUID();

    auto f = [&](Player* player) {
        data.sessionid = player->GetClSessionID();
        SendDataBySessionID(player->GetGsSessionID(), data);
    };

    player->ApplyFuncToAroundPlayers(f);
}

void CastleWarMgr::NotifyAroundPlayers_ShabakOwnerNtf(Player* player)
{
    if (!player) return;

    ProtoMS_ShabakOwnerNtf data;
    data.role_guid = player->GetGUID();

    auto f = [&](Player* player) {
        data.sessionid = player->GetClSessionID();
        SendDataBySessionID(player->GetGsSessionID(), data);
    };

    player->ApplyFuncToAroundPlayers(f);
}

void CastleWarMgr::SendShabakEngageNtfToGS(Player* player)
{
    if (!player) return;
    if (!IsWarInSchedule() && !IsInWar())  return;
    const auto& winner = GetWinner();
    const auto& guilds = QueryEngagedGuilds();

    std::string attackers;
    for (const auto& guild : guilds) {
        if (guild == winner) continue;
        if (!attackers.empty()) attackers.append("|");
        attackers.append(guild);
    }

    ProtoMS_ShabakEngageNtf data;
    data.sessionid = player->GetClSessionID();
    strcpy_s(data.own_family, _countof(data.own_family), winner.c_str());
    strcpy_s(data.attack_families, _countof(data.attack_families), attackers.c_str());

    SendDataBySessionID(player->GetGsSessionID(), data);
}

void CastleWarMgr::SendShabakEndNtfToGS(Player* player)
{
    if (!player) return;

    ProtoMS_ShabakEndNtf data;
    data.sessionid = player->GetClSessionID();
    SendDataBySessionID(player->GetGsSessionID(), data);
}