#pragma once




class GuildData
{
    DECL_SINGLETON(GuildData);

public:
    void SetHasGuilds(bool flag) { mHasGuilds = flag; }
    bool HasGuilds() const { return mHasGuilds; }

    void SetHasMembers(bool flag) { mHasMembers = flag; }
    bool HasMembers() { return mHasMembers; }

    void SetHasApplicants(bool flag) { mHasApplicants = flag; }
    bool HasApplicants() { return mHasApplicants; }

    void SetGuilds(GUILD_MAP guilds) { mGuilds = std::move(guilds); }
    GUILD_MAP & GetGuilds() { return mGuilds; }

    void SetMembers(GUILD_MEMBER_MAP members) { mMembers = std::move(members); }
    GUILD_MEMBER_MAP & GetMembers() { return mMembers; }

    void SetApplicants(GUILD_APPLICANT_LIST applicants) { mApplicants = std::move(applicants); }
    GUILD_APPLICANT_LIST & GetApplicants() { return mApplicants; }

    void SyncGuildApplicant(const SPGUILD_APPLICANT &applyInfo, uint8_t type);
    void SyncGuildMember(const SPGUILD_MEMBER &member, uint8_t type);
    void SyncGuildInfo(const SPGUILD &guild, uint8_t type);
    void SyncGuildRelation(uint8_t type, uint64_t myGUID, uint64_t peerGUID, uint8_t relation);

    void ChangeNameInfo(uint64_t guid, const std::string& name);

private:
    GuildData() {}
    ~GuildData() {}

    SPGUILD GetGuild(uint64_t guid);

    bool IsGuildExist(uint64_t guid);

    bool IsExistInList(const GUILD_ID_LIST &idList, uint64_t id);

    bool HasRelation(uint64_t guid1, uint64_t guid2);

    void RemoveGuildRelation(uint64_t guid);
    void RemoveAlly(uint64_t myGUID, uint64_t peerGUID);
    void RemoveEnemy(uint64_t myGUID, uint64_t peerGUID);

private:
    bool mHasGuilds     = false;
    bool mHasMembers    = false;
    bool mHasApplicants = false;

    GUILD_MAP               mGuilds;
    GUILD_MEMBER_MAP        mMembers;
    GUILD_APPLICANT_LIST    mApplicants;
};
