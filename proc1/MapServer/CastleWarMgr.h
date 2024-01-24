#pragma once

#include "shabak_table.hpp"


class CastleWarMgr
{
    DECL_SINGLETON(CastleWarMgr);

    struct PlayerData
    {
        uint32_t nOnDieFuncID   = 0;
        uint32_t nOnExitFuncID  = 0;
        uint32_t nOnlineFuncID  = 0;
        uint32_t nOfflineFuncID = 0;
        bool     bOnline        = false;
    };

    using PlayerDataMap = std::unordered_map<uint64_t, PlayerData>;
    using GuildPlayerMap = std::map<std::string, PlayerDataMap>;
    using GuildList = std::vector<std::string>;

public:
    bool RecoverCastleWar();    // 从数据库恢复
    bool StartCastleWar(GuildList guilds, uint64_t startTime, uint32_t duration);
    bool StopCastleWar();

    const GuildList & QueryEngagedGuilds();         // 攻沙结束或未注册返回空
    const std::string & GetWinner() const { return mWinner; }
    void SetWinner(std::string winner) { OnWinnerChange(std::move(winner)); }
    uint64_t QueryStartTime();                      // 攻沙结束或未注册返回0
    void GenCastleMonster(uint32_t type);

    bool IsWarInSchedule() { return mStartTimerID != 0; }
    bool IsInWar() { return mEndTimerID != 0; }
    bool IsWarEnd() { return mEndTime > 0; }

    bool IsWinnerGuild(const std::string &guild);
    bool IsEngagedGuild(const std::string &guild);
    bool IsPalaceFrontDoorMonsterSpot(uint16_t x, uint16_t y);
    bool IsInShabak(Role *role);                    // 是否在沙巴克或皇宫中

    DATA::Shabak * GetCfg();

private:
    std::string GetCastleWarInfoFromDB();
    void SaveCastleWarInfoToDB();

    bool ParseCastleWarInfo(const std::string &info);
    std::string AssembleCastleWarInfo();

    bool CheckGuilds(const GuildList &guilds);

    bool SetStartTimer();
    bool SetEndTimer();

    void ResetStartTimer();
    void ResetEndTimer();

    void OnWarStart();
    void OnWarEnd();
    void OnWarStop();

    void InitPalacePlayerData();
    void CleanPalacePlayerData();

    void GenMainCityFrontDoorMonster(const std::string &mapName, const std::string &monsterName, uint16_t x, uint16_t y,
        const std::vector<int32_t> &seqs);
    void GenMonster(const std::string &mapName, const std::string &monsterName, uint16_t x, uint16_t y);

    bool AddOnEnterMainCityFunc();
    void RemoveOnEnterMainCityFunc();
    void OnEnterMainCity(Role *role);

    bool AddOnEnterPalaceFunc();
    void RemoveOnEnterPalaceFunc();
    void OnEnterPalace(Role *role);

    bool AddOnLeavePalaceFunc();
    void RemoveOnLeavePalaceFunc();
    void OnLeavePalace(Role *role);

    void SetStateChangeFunc(Role *role, PlayerData &playerData);
    void ResetStateChangeFunc(Role *role, PlayerData &playerData);

    void OnRoleDie(Role *role);
    void OnRoleExit(Role *role);
    void OnRoleOnline(Role *role);
    void OnRoleOffline(Role *role);

    bool NoOnlinePlayerInPalace(const PlayerDataMap &players);
    bool AnyOnlinePlayerInPalace(const PlayerDataMap &players);
    bool JustOneOnlinePlayerInPalace(const PlayerDataMap &players);

    void RecalcWinner();
    void OnWinnerChange(std::string newWinner);

    void NotifyWinnerMembers(const std::string &winnerGuild);
    void NotifyLossMembers(const std::string &lossGuild);
    void NotifyAllPlayersWarStart();
    void NotifyAllPlayersWarEnd();

    const std::string & GetRoleGuildName(Role *role);

    Map * GetMainCityMap();
    Map * GetPalaceMap();

public:
    void NotifyAroundPlayers_ShabakLossNtf(Player* player);
    void NotifyAroundPlayers_ShabakOwnerNtf(Player* player);
    void SendShabakEngageNtfToGS(Player* player);
    void SendShabakEndNtfToGS(Player* player);

private:
    uint64_t                    mStartTime              = 0;        // 计划开始时间
    uint32_t                    mDuration               = 0;        // 计划持续时间
    uint64_t                    mEndTime                = 0;        // 实际结束时间

    GuildList                   mGuilds;                            // 参与攻沙的工会名列表
    std::string                 mWinner;

    uint32_t                    mStartTimerID           = 0;        // 攻沙开始定时器
    uint32_t                    mEndTimerID             = 0;        // 攻沙结束定时器

    GuildPlayerMap              mPalacePlayerData;                  // 皇宫内各工会人数统计

    uint32_t                    mOnEnterPalaceFuncID    = 0;
    uint32_t                    mOnLeavePalaceFuncID    = 0;
    uint32_t                    mOnEnterMainCityFuncID  = 0;
};
