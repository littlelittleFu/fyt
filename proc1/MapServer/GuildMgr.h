#pragma once

#include <memory>
#include <map>
#include <unordered_map>
#include <list>



class Player;

class GuildMgr
{
    DECL_SINGLETON(GuildMgr);
    typedef std::function<void(Player*, void* data)> Func;
public:
    void SetGuilds(GUILD_MAP guilds);
    GUILD_MAP & GetGuilds() { return mGuilds; }

    void SetMembers(GUILD_MEMBER_MAP members);
    GUILD_MEMBER_MAP & GetMembers() { return mMembers; }

    void SetApplicants(GUILD_APPLICANT_LIST applicants);
    GUILD_APPLICANT_LIST & GetApplicants() { return mApplicants; }

    SPGUILD GetGuild(uint64_t guildID);
    SPGUILD_MEMBER GetMember(uint64_t roleid);
    GUILD_APPLICANT_LIST GetPlayerApplicants(uint64_t roleid);

    const char * GetMemberTitle(uint8_t title);
    bool GetGuildName(uint64_t guildID, char *buf, uint32_t bufSize);
    const std::string & GetGuildName(uint64_t guildGUID);
    uint64_t GetGuildIDByName(const std::string &name);
    bool GetChairmanName(uint64_t guildID, char *buf, uint32_t bufSize);
    uint32_t GetMemberNum(uint64_t guildID);
    bool IsReachMaxMemberLimit(uint64_t guildID);

    GUILD_MEMBER_LIST * GetMemberList(uint64_t guildID);
    std::vector<uint64_t> GetMemberGuidList(uint64_t guildID);
    std::vector<uint64_t> * GetAllyList(uint64_t guildID);
    std::vector<uint64_t> * GetEnemyList(uint64_t guildID);
    GUILD_APPLICANT_LIST * GetApplicantList(uint64_t guildID);
    GUILD_ID_SET* GetWarSet(uint64_t guildGUID);

    bool CanViewApplicants(int title);

    bool GuildExist(const std::string &name, bool ignoreCase);

    void AddGuild(const SPGUILD &guild);
    void RemoveGuild(uint64_t guildGUID);
    void RemoveGuildRelation(uint64_t guildGUID);

    void AddMember(const SPGUILD_MEMBER &member);
    void RemoveMember(uint64_t guildGUID, uint64_t memberGUID);

    void AddApplicant(const SPGUILD_APPLICANT &applicant);
    void RemoveApplicant(uint64_t playerGUID, uint64_t guildGUID);
    SPGUILD_APPLICANT UpdateApplicant(uint64_t playerGUID, uint64_t guildGUID, uint8_t status);
    SPGUILD_APPLICANT GetApplicant(uint64_t guildGUID, uint64_t playerGUID);

    bool IsPlayerInGuild(uint64_t playerGUID);

    int AddAlly(const std::string &myGuildName, const std::string &allyGuildName);
    int DelAlly(const std::string &myGuildName, const std::string &allyGuildName);
    bool IsAlly(const std::string &myGuildName, const std::string &allyGuildName);

    int AddEnemy(const std::string &myGuildName, const std::string &enemyGuildName);
    int DelEnemy(const std::string &myGuildName, const std::string &enemyGuildName);
    bool IsEnemy(const std::string &myGuildName, const std::string &enemyGuildName);

    int32_t JoinGuild(uint64_t playerGuid, uint64_t guildGuid, SPGUILD_APPLICANT app);
    int32_t SetGuildLevel(uint64_t guildGuid, uint16_t level);
    int32_t SetGuildAutoJoinLevel(uint64_t guildGuid, uint32_t level);
    int32_t EditGuildNotice(uint64_t guildGuid, const std::string& notice);
    int32_t ChangeGuildMemberTitle(uint64_t memberGUID, uint8_t title);
    int32_t KickGuildMember(uint64_t memberGUID);
    int32_t DestroyGuild(uint64_t guildGuid);
    void GuildWar(uint64_t guildGuid, uint64_t enemyGuildGuid, uint32_t durTime);
private:
    GuildMgr() {}
    ~GuildMgr() {}

    void SetHasGuilds(bool flag) { mHasGuilds = flag; }
    bool HasGuilds() const { return mHasGuilds; }

    void SetHasMembers(bool flag) { mHasMembers = flag; }
    bool HasMembers() { return mHasMembers; }

    void SetHasApplicants(bool flag) { mHasApplicants = flag; }
    bool HasApplicants() { return mHasApplicants; }

    void AssembleData();
    void AssembleMembers(const uint64_t &guildID, GUILD_MEMBER_LIST &members);
    void AssembleApplicants(const uint64_t &guildID, GUILD_APPLICANT_LIST &applicants);

    void RemoveApplicant(GUILD_APPLICANT_LIST &applies, uint64_t playerGUID, uint64_t guildGUID);

    SPGUILD GetGuildByName(const std::string &guildName);

    void RemoveAlly(uint64_t myGUID, uint64_t peerGUID);
    void RemoveEnemy(uint64_t myGUID, uint64_t peerGUID);

    bool IsExistInList(const GUILD_ID_LIST &idList, uint64_t id);

    void SyncGuildRelation(uint8_t opType, uint64_t myGuildGUID, uint64_t peerGuildGUID, uint8_t relation);

    void OnJoinGuild(uint64_t guildGUID, uint64_t playerGUID);
    void OnLeaveGuild(uint64_t guildGUID, uint64_t playerGUID);

    void ApplyFuncToMember(uint64_t guildGuid, uint64_t playerGuid, Func, void* data);

    void GenerateRunningGuildWearNtf(uint64_t guildGuid, std::vector<ProtoMS_RunningFamilyWarNtf>&);
    static void NotifyRunningGuildFunc(Player* player, void* data);
public:
    void CheckAutoJoinGuild();
    void CheckAutoJoinGuild(SPGUILD_APPLICANT app);
    void NotifyRunningGuildWear(uint64_t guildGuid, uint64_t playerGuid = 0);
    // sync
public:
    static bool CheckInCastleWar();
    static void SyncGuildTitle(SPGUILD_MEMBER& mGuildMember);
    static void SyncGuildMemberToCS(SPGUILD_MEMBER& member, uint8_t type);
    static void SyncApplicantToCS(SPGUILD_APPLICANT& applicant, uint8_t type);
    static void SyncGuildInfoToCS(SPGUILD& mGuild, uint8_t type);
private:
    bool mHasGuilds     = false;
    bool mHasMembers    = false;
    bool mHasApplicants = false;

    GUILD_MAP               mGuilds;            // 所有工会信息数据
    GUILD_MEMBER_MAP        mMembers;           // 所有玩家信息(在工会的数据信息)
    GUILD_APPLICANT_LIST    mApplicants;        // 所有玩家工会的申请信息

    GUILD_DATA_MAP          mGuildData;         // key:工会id ,value:该工会的成员和申请
};

class GuildDataMgr
{
    friend Player;
    friend GuildMgr;
public:
    GuildDataMgr(Player* player);
    virtual ~GuildDataMgr();

    void InitGuildData();
    // Get
    uint64_t GetGuildID() { return mGuild ? mGuild->id : 0; }
    const std::string& GetGuildName()  { if (mGuild)  return mGuild->name; else  return EMPTYSTR;  }
    uint64_t GetGuildCreationTime() { return mGuild ? mGuild->ctime : 0; }
    bool HasGuild() { return (mGuild != nullptr); }
    int32_t GetGuildMemberTitle() { return GetGuildMemberNewTitle(); }
    int32_t GetGuildMemberOldTitle() { return mGuildMember ? mGuildMember->title : guild_member_title_not_member; }
    int32_t GetGuildMemberNewTitle() { return mGuildMember ? mGuildMember->new_title : guild_member_title_not_member; }
    bool IsGuildApplied(uint64_t guildID);
    uint32_t GetCurContrib() { return mGuildMember ? mGuildMember->cur_contrib : 0; }
    void SetCurContrib(uint32_t contrib);
    uint32_t GetTotalContrib() { return mGuildMember ? mGuildMember->total_contrib : 0; }
    void SetTotalContrib(uint32_t contrib);
    SPGUILD GetGuild() { return mGuild; }
    void SetGuild(const SPGUILD& guild) { mGuild = guild; }
    SPGUILD_MEMBER GetGuildMember() { return mGuildMember; }
    void SetGuildMember(const SPGUILD_MEMBER& member) { mGuildMember = member; }
    SPGUILD_APPLICANT GetApplicant(uint64_t guildGUID);
    SPGUILD_APPLICANT AddApplicant(uint64_t guildGUID);
    void SetGuildMemberOnline(bool online) { if (mGuildMember) mGuildMember->online = online; }
    void SetGuildMemberLoginTime(uint64_t loginTime) { if (mGuildMember) mGuildMember->login_time = loginTime; }

    void ChangeNameInfo(uint64_t guid, const std::string& name);

    //
    int32_t CreateGuild(const std::string& guildName);
    // handle
    void OnLeaveGuild(const char* byebye);
    void OnDestroyGuild();
    void OnChangeGuildMemberTitle(uint64_t memberGUID, uint8_t title);
    void OnGetFamilyInfo(uint32_t nReqType, uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo);
    void OnJoinGuildReq(uint64_t guildGUID);
    void OnCancelJoinGuildReq(uint64_t guildGUID);
    void OnFamilyJoinAck(uint64_t applicantGUID, bool approved);
    void OnKickGuildMember(uint64_t memberGUID);
    void OnEditGuildNotice(const char* notice);
protected:
    void BeingKickedFromGuild();
    void LeaveGuild(const std::string& kickedBy);
    void RemoveApplicant(uint64_t guildGUID);
    void UpdateGuildInfoOnLogout();
    bool GuildTitleChanged();
    bool NeedNtfGuildApplyResult();
    void DelayNtfGuildApplyResult(int32_t delayTime);
    void DelayNtfGuildTitleChanged(int32_t delayTime);
    void DelayNtfRemovedFromGuild(int32_t delayTime);
    void DelayNtfDestoryGuild(int32_t delayTime);

    // send
    void SendFamilyInfoNtfToGS(uint32_t type);
    void SendFamilyMembersAck(uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo, bool onlineOnly);
    void SendFamilyLeaveNtf(const std::string& guildName, const std::string& kickerName);
public:
    void SendPlayerFamilyChangeNtfToGS(const std::string& guildName);
protected:
    void SendCancelFamilyJoinAckToGS(uint64_t guildGUID, uint32_t errcode);

private:
    void GetFamilyInfo_Notice(uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo);
    void GetFamilyInfo_Member(uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo);
    void GetFamilyInfo_Enemy(uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo);
    void GetFamilyInfo_Ally(uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo);
    void GetFamilyInfo_Apply(uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo);
    void GetFamilyInfo_BasicInfo(uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo);
    void GetFamilyInfo_FamilyList(uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo);
    void GetFamilyInfo_MemberOnline(uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo);
protected:
    Player* m_player;

    SPGUILD                 mGuild;                 // 玩家所在工会信息
    SPGUILD_MEMBER          mGuildMember;           // 玩家信息(在工会的数据信息)
    GUILD_APPLICANT_LIST    mGuildApplicants;       // 玩家工会的申请信息
};