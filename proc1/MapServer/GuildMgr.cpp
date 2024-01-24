#include "stdafx.h"
#include "GuildMgr.h"

#include <algorithm>

#include "ProtoMS.h"
#include "SessionFactory.h"
#include "CNetManager.h"
#include "CastleWarMgr.h"


IMPL_SINGLETON(GuildMgr)

void GuildMgr::SetGuilds(GUILD_MAP guilds)
{
    mGuilds = std::move(guilds);
    SetHasGuilds(true);
    AssembleData();
}

void GuildMgr::SetMembers(GUILD_MEMBER_MAP members)
{
    mMembers = std::move(members);
    SetHasMembers(true);
    AssembleData();
}

void GuildMgr::SetApplicants(GUILD_APPLICANT_LIST applicants)
{
    mApplicants = std::move(applicants);
    SetHasApplicants(true);
    AssembleData();
}

void GuildMgr::AssembleData()
{
    if (!HasGuilds() || !HasMembers() || !HasApplicants()) return;

    mGuildData.clear();

    for (auto &it : mGuilds) {

        const auto &guildID = it.first;

        auto &data = mGuildData[guildID];

        AssembleMembers(guildID, data.members);
        AssembleApplicants(guildID, data.applicants);
    }
    CheckAutoJoinGuild();
}

void GuildMgr::AssembleMembers(const uint64_t &guildID, GUILD_MEMBER_LIST &members)
{
    for (auto &it : mMembers) {

        auto &member = it.second;

        if (member->guild_id != guildID) continue;

        members.push_back(member);
    }
}

void GuildMgr::AssembleApplicants(const uint64_t &guildID, GUILD_APPLICANT_LIST &applicants)
{
    for (auto &applicant : mApplicants) {

        if (applicant->guild_id != guildID) continue;

        applicants.push_back(applicant);
    }
}

SPGUILD GuildMgr::GetGuild(uint64_t guildID)
{
    auto it = mGuilds.find(guildID);
    return (it == mGuilds.end()) ? nullptr : it->second;
}

SPGUILD_MEMBER GuildMgr::GetMember(uint64_t roleid)
{
    auto it = mMembers.find(roleid);
    return (it == mMembers.end()) ? nullptr : it->second;
}

GUILD_APPLICANT_LIST GuildMgr::GetPlayerApplicants(uint64_t roleid)
{
    GUILD_APPLICANT_LIST applicants;

    for (auto &it : mApplicants) {

        if (it->player_id != roleid) continue;

        applicants.push_back(it);
    }

    return applicants;
}

void GuildMgr::AddApplicant(const SPGUILD_APPLICANT &applicant)
{
    mApplicants.emplace_back(applicant);

    auto guildGUID = applicant->guild_id;
    auto it = mGuildData.find(guildGUID);
    if (it == mGuildData.end()) return;
    it->second.applicants.emplace_back(applicant);
}

void GuildMgr::RemoveApplicant(uint64_t playerGUID, uint64_t guildGUID)
{
    RemoveApplicant(mApplicants, playerGUID, guildGUID);

    auto it = mGuildData.find(guildGUID);
    if (it == mGuildData.end()) return;
    RemoveApplicant(it->second.applicants, playerGUID, guildGUID);
}

void GuildMgr::RemoveApplicant(GUILD_APPLICANT_LIST &applies, uint64_t playerGUID, uint64_t guildGUID)
{
    for (auto it = applies.begin(); it != applies.end(); ++it) {

        auto &apply = *it;

        if (apply->player_id != playerGUID) continue;
        if (apply->guild_id != guildGUID) continue;

        applies.erase(it);
        break;
    }
}

SPGUILD_APPLICANT GuildMgr::UpdateApplicant(uint64_t playerGUID, uint64_t guildGUID, uint8_t status)
{
    auto it = mGuildData.find(guildGUID);
    if (it == mGuildData.end()) return nullptr;

    auto &applies = it->second.applicants;

    for (auto it = applies.begin(); it != applies.end(); ++it) {

        auto &apply = *it;

        if (apply->player_id != playerGUID) continue;

        apply->status = status;
        return apply;
    }

    return nullptr;
}

SPGUILD_APPLICANT GuildMgr::GetApplicant(uint64_t guildGUID, uint64_t playerGUID)
{
    auto it = mGuildData.find(guildGUID);
    if (it == mGuildData.end()) return nullptr;

    for (auto &apply : it->second.applicants)
        if (apply->player_id == playerGUID)
            return apply;

    return nullptr;
}

const char * GuildMgr::GetMemberTitle(uint8_t title)
{
    switch (title) {

    case guild_member_title_member:
        return "成员";

    case guild_member_title_chairman:
        return "会长";

    case guild_member_title_vice_chairman:
        return "副会长";

    case guild_member_title_elite:
        return "精英";

    default:
        return "";
    }
}

bool GuildMgr::GetGuildName(uint64_t guildID, char *buf, uint32_t bufSize)
{
    auto it = mGuilds.find(guildID);
    if (it == mGuilds.end()) return false;

    strcpy_s(buf, bufSize, it->second->name.c_str());
    return true;
}

const std::string & GuildMgr::GetGuildName(uint64_t guildGUID)
{
    auto it = mGuilds.find(guildGUID);
    if (it == mGuilds.end())
    {
        return EMPTYSTR;
    }
    else
    {
        return it->second->name;
    }
}

uint64_t GuildMgr::GetGuildIDByName(const std::string &name)
{
    for (const auto &it : mGuilds)
        if (it.second->name == name)
            return it.first;

    return 0;
}

bool GuildMgr::GetChairmanName(uint64_t guildID, char *buf, uint32_t bufSize)
{
    auto it = mGuilds.find(guildID);
    if (it == mGuilds.end()) return false;

    strcpy_s(buf, bufSize, it->second->chairman_name.c_str());
    return true;
}

GUILD_MEMBER_LIST * GuildMgr::GetMemberList(uint64_t guildID)
{
    auto it = mGuildData.find(guildID);
    return (it == mGuildData.end()) ? nullptr : &it->second.members;
}

std::vector<uint64_t> GuildMgr::GetMemberGuidList(uint64_t guildID)
{
    std::vector<uint64_t> v;
    auto pList = GetMemberList(guildID);
    if (!pList) return v;

    for (auto iter = pList->begin(); iter != pList->end(); ++iter)
    {
        if (!(*iter)) continue;
        v.push_back((*iter)->player_id);
    }
    return v;
}

GUILD_ID_SET* GuildMgr::GetWarSet(uint64_t guildGUID)
{
    auto it = mGuildData.find(guildGUID);
    return (it == mGuildData.end()) ? nullptr : &it->second.war;
}

GUILD_ID_LIST * GuildMgr::GetAllyList(uint64_t guildID)
{
    auto it = mGuilds.find(guildID);
    return (it == mGuilds.end()) ? nullptr : &it->second->allies;
}

GUILD_ID_LIST * GuildMgr::GetEnemyList(uint64_t guildID)
{
    auto it = mGuilds.find(guildID);
    return (it == mGuilds.end()) ? nullptr : &it->second->enemies;
}

GUILD_APPLICANT_LIST * GuildMgr::GetApplicantList(uint64_t guildID)
{
    auto it = mGuildData.find(guildID);
    return (it == mGuildData.end()) ? nullptr : &it->second.applicants;
}

bool GuildMgr::CanViewApplicants(int title)
{
    return (title == guild_member_title_chairman ||
            title == guild_member_title_vice_chairman);
}

uint32_t GuildMgr::GetMemberNum(uint64_t guildID)
{
    auto it = mGuildData.find(guildID);
    if (it == mGuildData.end()) return 0;

    auto &members = it->second.members;

    auto num = std::count_if(members.begin(), members.end(), [](const auto &member) {
        return (member->status != guild_member_status_removed);
    });

    return static_cast<uint32_t>(num);
}

bool GuildMgr::IsReachMaxMemberLimit(uint64_t guildID)
{
    auto guild = GetGuild(guildID);
    if (!guild) return true;

    const auto &MaxMemLimit = sGlobalConfig.GetData()->GuildMaxMemberLimit;
    if (MaxMemLimit.empty()) return false;

    const auto &guildLevel = guild->level;
    auto i = std::min<size_t>(MaxMemLimit.size() - 1, guildLevel - 1);

    auto memNum = GetMemberNum(guildID);
    return (memNum >= MaxMemLimit[i]);
}

bool GuildMgr::GuildExist(const std::string &name, bool ignoreCase)
{
    if (ignoreCase) {
        for (const auto &it : mGuilds)
            if (_stricmp(it.second->name.c_str(), name.c_str()) == 0)
                return true;
    }
    else {
        for (const auto &it : mGuilds)
            if (it.second->name == name) return true;
    }

    return false;
}

void GuildMgr::AddMember(const SPGUILD_MEMBER &member)
{
    auto guildGUID = member->guild_id;
    auto it = mGuildData.find(guildGUID);
    if (it == mGuildData.end()) return;
    it->second.members.emplace_back(member);
    mMembers[member->player_id] = member;

    OnJoinGuild(guildGUID, member->player_id);
}

bool GuildMgr::IsPlayerInGuild(uint64_t playerGUID)
{
    return mMembers.find(playerGUID) != mMembers.end();
}

void GuildMgr::RemoveMember(uint64_t guildGUID, uint64_t memberGUID)
{
    mMembers.erase(memberGUID);

    auto it = mGuildData.find(guildGUID);
    if (it == mGuildData.end()) return;

    auto &members = it->second.members;
    for (auto it = members.begin(); it != members.end(); ++it) {
        if ((*it)->player_id == memberGUID) {
            members.erase(it);
            break;
        }
    }

    OnLeaveGuild(guildGUID, memberGUID);
}

void GuildMgr::AddGuild(const SPGUILD &guild)
{
    mGuilds[guild->id] = guild;

    mGuildData[guild->id];
}

void GuildMgr::RemoveGuild(uint64_t guildGUID)
{
    mGuilds.erase(guildGUID);

    for (auto it = mApplicants.begin(); it != mApplicants.end(); ) {

        auto &apply = *it;

        if (apply->guild_id == guildGUID) {
            it = mApplicants.erase(it);
        }
        else {
            ++it;
        }
    }

    mGuildData.erase(guildGUID);
}

void GuildMgr::RemoveGuildRelation(uint64_t guildGUID)
{
    auto guild = GetGuild(guildGUID);
    if (!guild) return;

    for (const auto &id : guild->allies) {
        RemoveAlly(id, guildGUID);
    }

    for (const auto &id : guild->enemies) {
        RemoveEnemy(id, guildGUID);
    }

    guild->allies.clear();
    guild->enemies.clear();
}

void GuildMgr::RemoveAlly(uint64_t myGUID, uint64_t peerGUID)
{
    auto guild = GetGuild(myGUID);
    if (!guild) return;

    auto &allies = guild->allies;

    auto it = std::find(allies.begin(), allies.end(), peerGUID);
    if (it != allies.end()) allies.erase(it);
}

void GuildMgr::RemoveEnemy(uint64_t myGUID, uint64_t peerGUID)
{
    auto guild = GetGuild(myGUID);
    if (!guild) return;

    auto &enemies = guild->enemies;

    auto it = std::find(enemies.begin(), enemies.end(), peerGUID);
    if (it != enemies.end()) enemies.erase(it);
}

SPGUILD GuildMgr::GetGuildByName(const std::string &guildName)
{
    for (auto &guild : mGuilds)
        if (guild.second->name == guildName)
            return guild.second;

    return nullptr;
}

bool GuildMgr::IsExistInList(const GUILD_ID_LIST &idList, uint64_t id)
{
    return std::find(idList.begin(), idList.end(), id) != idList.end();
}

void GuildMgr::SyncGuildRelation(uint8_t opType, uint64_t myGuildGUID, uint64_t peerGuildGUID, uint8_t relation)
{
    ProtoMS_SyncGuildRelation data;
    data.type = opType;
    data.my_guild_guid = myGuildGUID;
    data.peer_guild_guid = peerGuildGUID;
    data.relation = relation;

    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

int GuildMgr::AddAlly(const std::string &myGuildName, const std::string &allyGuildName)
{
    auto myGuild = GetGuildByName(myGuildName);
    if (!myGuild) return ERR_FAMILY_NOT_EXSIT;

    auto allyGuild = GetGuildByName(allyGuildName);
    if (!allyGuild) return ERR_FAMILY_NOT_EXSIT;

    if (myGuild->id == allyGuild->id) return ERR_FAMILY_SELF;

    if (IsExistInList(myGuild->allies, allyGuild->id))
        return ERR_FAMILY_HAS_ALLY;

    if (IsExistInList(myGuild->enemies, allyGuild->id))
        return ERR_FAMILY_ALLY_WITH_ENEMY;

    if (IsExistInList(allyGuild->allies, myGuild->id))
        return ERR_FAMILY_HAS_ALLY;

    if (IsExistInList(allyGuild->enemies, myGuild->id))
        return ERR_FAMILY_ALLY_WITH_ENEMY;

    myGuild->allies.push_back(allyGuild->id);
    allyGuild->allies.push_back(myGuild->id);

    SyncGuildRelation(db_op_type_add, myGuild->id, allyGuild->id, guild_relation_ally);
    return ERR_OK;
}

int GuildMgr::DelAlly(const std::string &myGuildName, const std::string &allyGuildName)
{
    auto myGuild = GetGuildByName(myGuildName);
    if (!myGuild) return ERR_FAMILY_NOT_EXSIT;

    auto allyGuild = GetGuildByName(allyGuildName);
    if (!allyGuild) return ERR_FAMILY_NOT_EXSIT;

    auto it = std::find(myGuild->allies.begin(), myGuild->allies.end(), allyGuild->id);
    if (it != myGuild->allies.end()) myGuild->allies.erase(it);

    it = std::find(allyGuild->allies.begin(), allyGuild->allies.end(), myGuild->id);
    if (it != allyGuild->allies.end()) allyGuild->allies.erase(it);

    SyncGuildRelation(db_op_type_del, myGuild->id, allyGuild->id, guild_relation_ally);
    return ERR_OK;
}

bool GuildMgr::IsAlly(const std::string &myGuildName, const std::string &allyGuildName)
{
    auto myGuild = GetGuildByName(myGuildName);
    if (!myGuild) return false;

    auto allyGuild = GetGuildByName(allyGuildName);
    if (!allyGuild) return false;

    return std::find(myGuild->allies.begin(), myGuild->allies.end(), allyGuild->id) != myGuild->allies.end();
}

int GuildMgr::AddEnemy(const std::string &myGuildName, const std::string &enemyGuildName)
{
    auto myGuild = GetGuildByName(myGuildName);
    if (!myGuild) return ERR_FAMILY_NOT_EXSIT;

    auto enemyGuild = GetGuildByName(enemyGuildName);
    if (!enemyGuild) return ERR_FAMILY_NOT_EXSIT;

    if (myGuild->id == enemyGuild->id) return ERR_FAMILY_SELF;
    
    if (IsExistInList(myGuild->allies, enemyGuild->id))
        return ERR_FAMILY_ENEMY_WITH_ALLY;

    if (IsExistInList(myGuild->enemies, enemyGuild->id))
        return ERR_FAMILY_HAS_ENEMY;

    if (IsExistInList(enemyGuild->allies, myGuild->id))
        return ERR_FAMILY_ENEMY_WITH_ALLY;

    if (IsExistInList(enemyGuild->enemies, myGuild->id))
        return ERR_FAMILY_HAS_ENEMY;

    myGuild->enemies.push_back(enemyGuild->id);
    enemyGuild->enemies.push_back(myGuild->id);

    SyncGuildRelation(db_op_type_add, myGuild->id, enemyGuild->id, guild_relation_enemy);
    return ERR_OK;
}

int GuildMgr::DelEnemy(const std::string &myGuildName, const std::string &enemyGuildName)
{
    auto myGuild = GetGuildByName(myGuildName);
    if (!myGuild) return ERR_FAMILY_NOT_EXSIT;

    auto enemyGuild = GetGuildByName(enemyGuildName);
    if (!enemyGuild) return ERR_FAMILY_NOT_EXSIT;

    auto it = std::find(myGuild->enemies.begin(), myGuild->enemies.end(), enemyGuild->id);
    if (it != myGuild->enemies.end()) myGuild->enemies.erase(it);

    it = std::find(enemyGuild->enemies.begin(), enemyGuild->enemies.end(), myGuild->id);
    if (it != enemyGuild->enemies.end()) enemyGuild->enemies.erase(it);

    SyncGuildRelation(db_op_type_del, myGuild->id, enemyGuild->id, guild_relation_enemy);
    return ERR_OK;
}

bool GuildMgr::IsEnemy(const std::string &myGuildName, const std::string &enemyGuildName)
{
    auto myGuild = GetGuildByName(myGuildName);
    if (!myGuild) return false;

    auto enemyGuild = GetGuildByName(enemyGuildName);
    if (!enemyGuild) return false;

    return std::find(myGuild->enemies.begin(), myGuild->enemies.end(), enemyGuild->id) != myGuild->enemies.end();
}

void GuildMgr::OnJoinGuild(uint64_t guildGUID, uint64_t playerGUID)
{
    auto *player = MapRoleMgr::GetInstance()->FindPlayer(playerGUID);
    if (!player) return;

    NotifyRunningGuildWear(guildGUID, playerGUID);

    auto *shabak = CastleWarMgr::GetInstance();
    if (!shabak) return;

    const auto &guildName = GetGuildName(guildGUID);
    if (shabak->IsWinnerGuild(guildName)) {
        shabak->NotifyAroundPlayers_ShabakOwnerNtf(player);
    }

    if (shabak->IsInWar() && shabak->IsInShabak(player)) {
        shabak->SendShabakEngageNtfToGS(player);
    }
}

void GuildMgr::OnLeaveGuild(uint64_t guildGUID, uint64_t playerGUID)
{
    auto *player = MapRoleMgr::GetInstance()->FindPlayer(playerGUID);
    if (!player) return;

    auto *shabak = CastleWarMgr::GetInstance();
    if (!shabak) return;

    const auto &guildName = GetGuildName(guildGUID);
    if (shabak->IsWinnerGuild(guildName)) {
        shabak->NotifyAroundPlayers_ShabakLossNtf(player);
    }

    if (shabak->IsInWar() && shabak->IsInShabak(player)) {
        shabak->SendShabakEngageNtfToGS(player);
    }
}

int32_t GuildMgr::JoinGuild(uint64_t playerGuid, uint64_t guildGuid, SPGUILD_APPLICANT app)
{
    if (IsPlayerInGuild(playerGuid)) return ERR_FAMILY_IN_FAMILY;
    auto guild = GetGuild(guildGuid);
    if (!guild) return ERR_FAMILY_NOT_EXSIT;

    auto player = MapRoleMgr::GetInstance()->FindPlayer(playerGuid);
    if (!player && !app) app = GetApplicant(guildGuid, playerGuid);
    if (!player && !app) return ERR_FAMILY_OFFLINE;

    auto member = std::make_shared<GUILD_MEMBER>();
    member->player_id = playerGuid;
    member->player_name = app ? app->player_name : player->GetName();
    member->job = app ? app->job : player->GetRoleProp(role_job);
    member->level = app ? app->level : player->GetRoleProp(role_level);
    member->guild_id = guildGuid;
    member->title = member->new_title = guild_member_title_member;
    member->join_time = time(nullptr);
    member->login_time = app ? app->login_time : player->GetLoginTime();
    member->online = true;
    AddMember(member);

    SyncGuildMemberToCS(member, db_op_type_add);
    TRIGGER_EVENT(player, trigger_family_member_ntf, guildGuid, guild->name, member->player_id,
        family_member_ntf_add_member, member->player_name, guild->creator_id);


    if (player)
    {
    player->GetGuildDataMgr().SetGuild(guild);
    player->GetGuildDataMgr().SetGuildMember(member);
    player->GetGuildDataMgr().SendPlayerFamilyChangeNtfToGS(guild->name);
    // 如果在该工会有申请则删除申请记录
    auto apply = player->GetGuildDataMgr().GetApplicant(guildGuid);
    GuildMgr::SyncApplicantToCS(apply, db_op_type_del);
    player->GetGuildDataMgr().RemoveApplicant(guildGuid);

    auto timeStr = ITimeHelper::GetInstance()->GetCurTimeStr();
    auto msg = timeStr + "加入了行会。";
    auto& data = gMESSAGE_INFO;
    data.Clear();
    data.type = relation_chat_ntf_type_guild;
    data.scroll_times = 1;
    strcpy_s(data.message, _countof(data.message), msg.c_str());
    player->SendRelationChatNtf(data);

    }
    else
    {
        GuildMgr::SyncApplicantToCS(app, db_op_type_del);
    }
    RemoveApplicant(playerGuid, guildGuid);
    return ERR_OK;
}

int32_t GuildMgr::SetGuildLevel(uint64_t guildGuid, uint16_t level)
{
    auto guild = GetGuild(guildGuid);
    if (!guild) return ERR_FAMILY_NOT_EXSIT;

    guild->level = level;
    SyncGuildInfoToCS(guild, db_op_type_update);
    return ERR_OK;
}

int32_t GuildMgr::SetGuildAutoJoinLevel(uint64_t guildGuid, uint32_t level)
{
    auto guild = GetGuild(guildGuid);
    if (!guild) return ERR_FAMILY_NOT_EXSIT;

    guild->autojoin_level = level;
    SyncGuildInfoToCS(guild, db_op_type_update);

    CheckAutoJoinGuild();

    return ERR_OK;
}

int32_t GuildMgr::EditGuildNotice(uint64_t guildGuid, const std::string& notice)
{
    auto guild = GetGuild(guildGuid);
    if (!guild) return ERR_FAMILY_NOT_EXSIT;

    guild->notice = notice;

    GuildMgr::SyncGuildInfoToCS(guild, db_op_type_update);

    return ERR_OK;
}

int32_t GuildMgr::ChangeGuildMemberTitle(uint64_t memberGUID, uint8_t title)
{
    auto member1 = GetMember(memberGUID);
    if (!member1 || member1->status == guild_member_status_removed) return ERR_FAMILY_NO_FAMILY;

    auto guildGuid = member1->guild_id;
    auto guild = GetGuild(guildGuid);
    if (!guild) return ERR_FAMILY_NOT_EXSIT;

    // 不能将会长置为其他title(可以直接设置其他成员为会长,会长自动变为副会长)
    if (title != guild_member_title_chairman && memberGUID == guild->chairman_id) return ERR_FAMILY_CAN_NOT_TITLE;
    // 没有变
    if (member1->new_title == title) return ERR_OK;

    // 替换会长
    if (title == guild_member_title_chairman)
    {
        // 获取原会长
        uint64_t oldChairman = guild->chairman_id;
        auto member2 = GetMember(oldChairman);
        // 其他成员成为新将会长,则将老会长置为副会长
        if (oldChairman != memberGUID && member2)
        {
            member2->new_title = guild_member_title_vice_chairman;
            auto* player2 = MapRoleMgr::GetInstance()->FindPlayer(oldChairman);
            if (player2)
            {
                TRIGGER_EVENT(player2, trigger_family_member_ntf, std::to_string(guildGuid), guild->name,
                    std::to_string(member2->player_id), family_member_ntf_change_title, member2->player_name, memberGUID);
                member2->title = guild_member_title_vice_chairman;

                player2->GetGuildDataMgr().SendFamilyInfoNtfToGS(eFamilyInfoReq_Title);
                SyncGuildMemberToCS(member2, db_op_type_update);
                player2->GetGuildDataMgr().SendPlayerFamilyChangeNtfToGS(guild->name);
            }
        }
        // 会长信息更新
        guild->chairman_id = member1->player_id;
        guild->chairman_name = member1->player_name;
        SyncGuildInfoToCS(guild, db_op_type_update);
    }

    member1->new_title = title;
    auto* player1 = MapRoleMgr::GetInstance()->FindPlayer(memberGUID);
    if (player1)
    {
        TRIGGER_EVENT(player1, trigger_family_member_ntf, std::to_string(guildGuid), guild->name,
            std::to_string(member1->player_id), family_member_ntf_change_title, member1->player_name, memberGUID);
        member1->title = title;

        player1->GetGuildDataMgr().SendFamilyInfoNtfToGS(eFamilyInfoReq_Title);
        SyncGuildMemberToCS(member1, db_op_type_update);
        player1->GetGuildDataMgr().SendPlayerFamilyChangeNtfToGS(guild->name);
    }
    return ERR_OK;
}

int32_t GuildMgr::KickGuildMember(uint64_t memberGUID)
{
    if (GuildMgr::CheckInCastleWar())
    {
        LOG_ERROR("沙巴克期间不允许踢人");
        return ERR_FAMILY_CAN_NOT_KICK;
    }

    auto member = GetMember(memberGUID);
    if (!member || member->status == guild_member_status_removed) return ERR_FAMILY_NO_FAMILY;

    auto guildGuid = member->guild_id;
    auto guild = GetGuild(guildGuid);
    if (!guild) return ERR_FAMILY_NOT_EXSIT;
    
    // 不能T会长
    if (memberGUID == guild->chairman_id)
    {
        LOG_ERROR("不允许踢会长");
        return ERR_FAMILY_CAN_NOT_KICK;
    }

    // 置为被T状态
    member->status = guild_member_status_removed;
    member->kicked_by = guild->chairman_name;
    // 被T玩家
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(memberGUID);
    if (player) 
    {
        player->GetGuildDataMgr().BeingKickedFromGuild();
    }
    else {
        SyncGuildMemberToCS(member, db_op_type_update);
    }
    return ERR_OK;
}

int32_t GuildMgr::DestroyGuild(uint64_t guildGuid)
{
    auto guild = GetGuild(guildGuid);
    if (!guild) return ERR_FAMILY_NOT_EXSIT;

    if (GuildMgr::CheckInCastleWar())
    {
        LOG_ERROR("沙巴克期间不允许解散行会");
        return ERR_FAMILY_CAN_NOT_DESTORY;
    }

    auto vec = GetMemberGuidList(guildGuid);
    for (auto iter = vec.begin(); iter != vec.end(); ++iter)
    {
        KickGuildMember(*iter);
        auto player = MapRoleMgr::GetInstance()->FindPlayer(*iter);
        if (player) player->SendPopDlgMsgNtf("您所在的行会已解散");
    }
    auto player = MapRoleMgr::GetInstance()->FindPlayer(guild->chairman_id);
    auto member = GetMember(guild->chairman_id);

    member->status = guild_member_status_removed;
    member->kicked_by = guild->chairman_name;
    if (player)
    {
        player->GetGuildDataMgr().BeingKickedFromGuild();
        player->SendPopDlgMsgNtf("您所在的行会已解散");
    }
    else {
        SyncGuildMemberToCS(member, db_op_type_update);
    }
    SyncGuildInfoToCS(guild, db_op_type_del);
    RemoveGuildRelation(guildGuid);
    RemoveGuild(guildGuid);

    return ERR_OK;
}

void GuildMgr::GuildWar(uint64_t guildGuid, uint64_t enemyGuildGuid, uint32_t durTime)
{
    auto guild1 = GetGuild(guildGuid);
    auto guild2 = GetGuild(enemyGuildGuid);
    if (!guild1 || !guild2 || !durTime) return;
    if (!IsEnemy(guild1->name, guild2->name)) return;
    auto warSet1 = GetWarSet(guildGuid);
    auto warSet2 = GetWarSet(enemyGuildGuid);
    if (!warSet1 || !warSet2) return;
    // 检测是否正在行会战
    if (warSet1->find(enemyGuildGuid) != warSet1->end() ||
        warSet2->find(guildGuid) != warSet2->end()) return;
    // 添加
    warSet1->insert(enemyGuildGuid);
    warSet2->insert(guildGuid);

    NotifyRunningGuildWear(guildGuid);
    NotifyRunningGuildWear(enemyGuildGuid);

    TimerData td;
    td.interval = durTime;
    td.loop = false;
    td.callBack = [&, guildGuid, enemyGuildGuid](const TimerData& td) {
        // 删除
        auto ws1 = GetWarSet(guildGuid);
        auto ws2 = GetWarSet(enemyGuildGuid);
        if (ws1) ws1->erase(enemyGuildGuid);
        if (ws2) ws2->erase(guildGuid);

        NotifyRunningGuildWear(guildGuid);
        NotifyRunningGuildWear(enemyGuildGuid);
        // 行会战结束
        TRIGGER_EVENT(trigger_guild_war_end, std::to_string(guildGuid), std::to_string(enemyGuildGuid));
    };

    ITimeHelper::GetInstance()->AddTimer(td);
    // 行会战开始
    TRIGGER_EVENT(trigger_guild_war_start, std::to_string(guildGuid), std::to_string(enemyGuildGuid));
}

void GuildMgr::NotifyRunningGuildFunc(Player* player, void* data)
{
    if (!player) return;
    if (!data) return;
    std::vector<ProtoMS_RunningFamilyWarNtf>& ntf = *static_cast<std::vector<ProtoMS_RunningFamilyWarNtf>*>(data);
    if (ntf.empty()) return;

    for (auto& ack : ntf)
    {
        ack.sessionid = player->GetClSessionID();
        ack.total = (uint8_t)ntf.size();
        SendDataBySessionID(player->GetGsSessionID(), ack);
    }
}

void GuildMgr::GenerateRunningGuildWearNtf(uint64_t guildGuid, std::vector<ProtoMS_RunningFamilyWarNtf>& ntfVec)
{
    ntfVec.clear();
    ProtoMS_RunningFamilyWarNtf ntf;
    ntf.num = 0;
    ntf.idx = 1;
    ntf.total = 1;
    auto warSet = GetWarSet(guildGuid);
    if (!warSet || warSet->empty())
    {
        ntfVec.push_back(ntf);
        return;
    }

    for (auto iter = warSet->begin(); iter != warSet->end();)
    {
        auto guild = GetGuild(*iter);
        if (!guild) continue;
        //FAMILY_WAR_INFO
        ntf.families[ntf.num].guid = guild->id;
        strcpy_s(ntf.families[ntf.num].name, guild->name);
        ntf.num++;
        iter++;
        if (ntf.num >= ProtoMS_RunningFamilyWarNtf::MaxSize::MAX_SIZE || iter == warSet->end())
        {
            ntfVec.push_back(ntf);
            ntf.num = 0;
            ntf.idx ++;
        }
    }
}

void GuildMgr::NotifyRunningGuildWear(uint64_t guildGuid, uint64_t playerGuid)
{
    std::vector<ProtoMS_RunningFamilyWarNtf> ntfVec;
    GenerateRunningGuildWearNtf(guildGuid, ntfVec);
    ApplyFuncToMember(guildGuid, playerGuid, NotifyRunningGuildFunc, (void*)&ntfVec);
}

void GuildMgr::ApplyFuncToMember(uint64_t guildGuid, uint64_t playerGuid, Func func, void* data)
{
    auto ml1 = GetMemberList(guildGuid);
    if (!ml1) return;

    for (auto iter = ml1->begin(); iter != ml1->end(); ++iter)
    {
        if (!(*iter) || (*iter)->status == guild_member_status_removed) continue;
        if (!playerGuid)//向所有成员发送
        {
            func(MapRoleMgr::GetInstance()->FindPlayer((*iter)->player_id), data);
        }
        else if ((*iter)->player_id == playerGuid)// 向指定成员发送
        {
            func(MapRoleMgr::GetInstance()->FindPlayer(playerGuid), data);
            return;
        }
    }
}

void GuildMgr::CheckAutoJoinGuild()
{
    auto apps = mApplicants;
    for (auto& app : apps)
    {
        CheckAutoJoinGuild(app);
    }
    apps.clear();
}

void GuildMgr::CheckAutoJoinGuild(SPGUILD_APPLICANT app)
{
    if (!app) return;

    auto guild = GetGuild(app->guild_id);
    if (!guild) return;

    if (!guild->autojoin_level || guild->autojoin_level > app->level) return;

    JoinGuild(app->player_id, app->guild_id, app);
}

bool GuildMgr::CheckInCastleWar()
{
    auto* shabak = CastleWarMgr::GetInstance();
    if (shabak && shabak->IsInWar()) return true;

    return false;
}
////////////////////////////////////////////////////////////////////////////////
//
// GuildDataMgr
//

GuildDataMgr::GuildDataMgr(Player* player) :m_player(player)
{
}

GuildDataMgr::~GuildDataMgr()
{

}

void GuildDataMgr::InitGuildData()
{
    auto* mgr = GuildMgr::GetInstance();
    if (!mgr) return;

    auto roleid = m_player->GetGUID();

    mGuildApplicants = mgr->GetPlayerApplicants(roleid);

    auto delayTime = m_player->GetCurLoginNotifyDelayTime();

    if (NeedNtfGuildApplyResult()) {
        DelayNtfGuildApplyResult(delayTime);
        delayTime += 2000;
    }

    mGuildMember = mgr->GetMember(roleid);
    if (!mGuildMember) return;

    mGuild = mgr->GetGuild(mGuildMember->guild_id);
    // 工会可能已解散
    if (!mGuild)
    {
        DelayNtfDestoryGuild(delayTime);
        delayTime += 2000;
        return;
    }

    if (mGuildMember->status != guild_member_status_removed) {
        SetGuildMemberOnline(true);
        SetGuildMemberLoginTime(m_player->GetLoginTime());

        if (GuildTitleChanged()) {
            DelayNtfGuildTitleChanged(delayTime);
            delayTime += 2000;
        }
        mgr->NotifyRunningGuildWear(mGuildMember->guild_id, roleid);
    }
    else {
        DelayNtfRemovedFromGuild(delayTime);
        delayTime += 2000;
    }

    m_player->SetNextLoginNotifyDelayTime(delayTime);
}

bool GuildDataMgr::IsGuildApplied(uint64_t guildID)
{
    for (auto& apply : mGuildApplicants) {
        if (apply->guild_id == guildID &&
            (apply->status == guild_apply_status_applied ||
                apply->status == guild_apply_status_passed))
            return true;
    }

    return false;
}

void GuildDataMgr::SetCurContrib(uint32_t contrib)
{
    if (!mGuildMember) return;

    if (contrib > mGuildMember->cur_contrib) {
        auto increase = contrib - mGuildMember->cur_contrib;
        auto total = GetTotalContrib();
        SetTotalContrib(total + increase);
    }

    mGuildMember->cur_contrib = contrib;
    GuildMgr::SyncGuildMemberToCS(mGuildMember, db_op_type_update);
}

void GuildDataMgr::SetTotalContrib(uint32_t contrib)
{
    if (!mGuildMember) return;
    mGuildMember->total_contrib = contrib;
    GuildMgr::SyncGuildMemberToCS(mGuildMember, db_op_type_update);
}

SPGUILD_APPLICANT GuildDataMgr::GetApplicant(uint64_t guildGUID)
{
    for (auto& applicant : mGuildApplicants)
        if (applicant->guild_id == guildGUID)
            return applicant;

    return nullptr;
}

SPGUILD_APPLICANT GuildDataMgr::AddApplicant(uint64_t guildGUID)
{
    auto applicant = std::make_shared<GUILD_APPLY_INFO>();
    applicant->player_id = m_player->GetGUID();
    applicant->player_name = m_player->GetName();
    applicant->level = m_player->GetRoleProp(role_level);
    applicant->job = m_player->GetRoleProp(role_job);
    applicant->guild_id = guildGUID;
    applicant->apply_time = time(nullptr);
    applicant->login_time = m_player->GetLoginTime();
    applicant->status = guild_apply_status_applied;

    mGuildApplicants.emplace_back(applicant);
    GuildMgr::GetInstance()->AddApplicant(applicant);

    return applicant;
}

void GuildDataMgr::ChangeNameInfo(uint64_t guid, const std::string& name)
{
    if (mGuild) {
        if (mGuild.get()->chairman_id == guid) {
            mGuild.get()->chairman_name = name;
        }
        if (mGuild.get()->creator_id == guid) {
            mGuild.get()->creator_name = name;
        }
    }

    if (mGuildMember) {
        mGuildMember.get()->player_name = name;
    }

    for (auto i : mGuildApplicants) {
        if (i) {
            if (i.get()->player_id == guid) {
                i.get()->player_name = name;
                break;
            }
        }
    }
    
}

////////////////////////////////////////////
int32_t GuildDataMgr::CreateGuild(const std::string& guildName)
{
    if (guildName.empty()) return ERR_UNKNOW;
    if (HasGuild()) return ERR_FAMILY_IN_FAMILY;

    auto* mgr = GuildMgr::GetInstance();
    if (!mgr) return ERR_UNKNOW;

    if (mgr->GuildExist(guildName, true))
        return ERR_FAMILY_NAME_EXSIT;

    auto creatorName = m_player->GetName();

    mGuild = std::make_shared<GUILD_INFO>();
    mGuild->id = GenerateObjID(E_OBJ_GUILD, ConfigInfo::GetInstance());
    mGuild->name = guildName;
    mGuild->level = 1;
    mGuild->ctime = time(nullptr);
    mGuild->creator_id = m_player->GetGUID();
    mGuild->creator_name = creatorName;
    mGuild->chairman_id = mGuild->creator_id;
    mGuild->chairman_name = mGuild->creator_name;
    mgr->AddGuild(mGuild);

    GuildMgr::SyncGuildInfoToCS(mGuild, db_op_type_add);

    auto guildGUID = std::to_string(mGuild->id);
    auto creatorGUID = m_player->GetGUIDAsString();
    TRIGGER_EVENT(m_player, trigger_family_ntf, guildGUID, guildName, 1, creatorGUID);

    mGuildMember = std::make_shared<GUILD_MEMBER>();
    mGuildMember->player_id = mGuild->creator_id;
    mGuildMember->player_name = mGuild->creator_name;
    mGuildMember->job = m_player->GetRoleProp(role_job);
    mGuildMember->level = m_player->GetRoleProp(role_level);
    mGuildMember->guild_id = mGuild->id;
    mGuildMember->title = mGuildMember->new_title = guild_member_title_chairman;
    mGuildMember->join_time = mGuild->ctime;
    mGuildMember->login_time = m_player->GetLoginTime();
    mGuildMember->online = true;
    mgr->AddMember(mGuildMember);

    GuildMgr::SyncGuildMemberToCS(mGuildMember, db_op_type_add);

    TRIGGER_EVENT(m_player, trigger_family_member_ntf, guildGUID, guildName, creatorGUID,
        family_member_ntf_add_member, creatorName, creatorGUID);

    return ERR_OK;
}

void GuildDataMgr::OnLeaveGuild(const char* byebye)
{
    if (!HasGuild()) return;
    if (GuildMgr::CheckInCastleWar())
    {
        LOG_ERROR("沙巴克期间不允许退出行会");
        m_player->SendPopDlgMsgNtf("沙巴克期间不允许退出行会");
        return;
    }

    auto title = GetGuildMemberTitle();
    if (title == guild_member_title_chairman) {
        m_player->SendPopDlgMsgNtf("会长不可以离开帮会");
        return;
    }

    auto timeStr = ITimeHelper::GetInstance()->GetCurTimeStr();
    auto msg = timeStr + "离开了行会。";
    auto& data = gMESSAGE_INFO;
    data.Clear();
    data.type = relation_chat_ntf_type_guild;
    data.scroll_times = 1;
    strcpy_s(data.message, _countof(data.message), msg.c_str());
    m_player->SendRelationChatNtf(data);

    LeaveGuild("");
}

void GuildDataMgr::OnDestroyGuild()
{
    auto* guildMgr = GuildMgr::GetInstance();
    if (!guildMgr) return;

    if (GuildMgr::CheckInCastleWar())
    {
        LOG_ERROR("沙巴克期间不允许解散行会");
        m_player->SendPopDlgMsgNtf("沙巴克期间不允许解散行会");
        return;
    }
    auto guildGUID = GetGuildID();

    auto memberNum = guildMgr->GetMemberNum(guildGUID);
    if (memberNum == 0) return;

    if (memberNum > 1) {
        m_player->SendPopDlgMsgNtf("帮会里还有其他成员");
        return;
    }

    SendPlayerFamilyChangeNtfToGS("");

    GuildMgr::SyncGuildInfoToCS(mGuild, db_op_type_del);
    GuildMgr::SyncGuildMemberToCS(mGuildMember, db_op_type_del);
    guildMgr->RemoveMember(guildGUID, m_player->GetGUID());
    guildMgr->RemoveGuildRelation(guildGUID);
    guildMgr->RemoveGuild(guildGUID);

    mGuild = nullptr;
    mGuildMember = nullptr;
}

void GuildDataMgr::OnChangeGuildMemberTitle(uint64_t memberGUID, uint8_t title)
{
    auto myGUID = m_player->GetGUID();

    if (myGUID == memberGUID) {
        m_player->SendPopDlgMsgNtf("不能给自己指定职位");
        return;
    }

    if (!mGuildMember) return;
    auto myTitle = mGuildMember->title;

    if (myTitle != guild_member_title_chairman &&
        myTitle != guild_member_title_vice_chairman) {
        m_player->SendPopDlgMsgNtf("对不起，您没有权限");
        return;
    }

    if (myTitle == guild_member_title_vice_chairman &&      // 副会长只能指定成员和精英
        (title == guild_member_title_chairman || title == guild_member_title_vice_chairman)) {
        m_player->SendPopDlgMsgNtf("对不起，您没有权限");
        return;
    }

    auto guildGUID = GetGuildID();
    auto sGuildGUID = std::to_string(guildGUID);
    const auto &guildName = GetGuildName();
    auto sMemberGUID = std::to_string(memberGUID);
    auto sMyGUID = m_player->GetGUIDAsString();
    auto myName = m_player->GetName();

    auto* guildMgr = GuildMgr::GetInstance();
    if (!guildMgr) return;

    auto member = guildMgr->GetMember(memberGUID);
    if (!member || member->guild_id != guildGUID) {
        m_player->SendPopDlgMsgNtf("该玩家已退出帮会");
        return;
    }

    auto& memberName = member->player_name;
    auto oldTitle = member->new_title;      // new_title也是之前的，所以称为oldTitle

    auto* player = MapRoleMgr::GetInstance()->FindPlayer(memberGUID);

    if (myTitle == guild_member_title_chairman && title == guild_member_title_chairman) {   // 转让会长

        if (oldTitle != guild_member_title_vice_chairman) {
            m_player->SendPopDlgMsgNtf("只能转让给副会长");
            return;
        }

        if (!player) {
            m_player->SendPopDlgMsgNtf("转让会长需要对方在线");
            return;
        }

        mGuildMember->new_title = guild_member_title_vice_chairman;

        TRIGGER_EVENT(m_player, trigger_family_member_ntf, sGuildGUID, guildName,
            sMyGUID, family_member_ntf_change_title, myName, sMyGUID);

        mGuildMember->title = guild_member_title_vice_chairman;     // 事件触发之后同步

        SendFamilyInfoNtfToGS(eFamilyInfoReq_Title);
        GuildMgr::SyncGuildMemberToCS(mGuildMember, db_op_type_update);
        SendPlayerFamilyChangeNtfToGS(guildName);

        mGuild->chairman_id = player->GetGUID();
        mGuild->chairman_name = player->GetName();
        GuildMgr::SyncGuildInfoToCS(mGuild, db_op_type_update);
    }

    if (oldTitle == title) return;

    member->new_title = title;

    if (player) {

        TRIGGER_EVENT(player, trigger_family_member_ntf, sGuildGUID, guildName,
            sMemberGUID, family_member_ntf_change_title, memberName, sMyGUID);

        member->title = title;      // 事件触发之后同步

        player->GetGuildDataMgr().SendFamilyInfoNtfToGS(eFamilyInfoReq_Title);
        player->GetGuildDataMgr().SendPlayerFamilyChangeNtfToGS(guildName);
    }

    GuildMgr::SyncGuildMemberToCS(member, db_op_type_update);
}

void GuildDataMgr::OnGetFamilyInfo(uint32_t nReqType, uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo)
{
    const auto* globalCfg = sGlobalConfig.GetData();
    if (!globalCfg) return;

    if (nReqType & eFamilyInfoReq_Notice) {
        GetFamilyInfo_Notice(nStartIndex, nReqCount, nReqGroup, pInfo);
    }

    if (nReqType & eFamilyInfoReq_Member) {
        GetFamilyInfo_Member(nStartIndex, nReqCount, nReqGroup, pInfo);
    }

    if (nReqType & eFamilyInfoReq_Enemy) {
        GetFamilyInfo_Enemy(nStartIndex, nReqCount, nReqGroup, pInfo);
    }

    if (nReqType & eFamilyInfoReq_Ally) {
        GetFamilyInfo_Ally(nStartIndex, nReqCount, nReqGroup, pInfo);
    }

    if (nReqType & eFamilyInfoReq_Apply) {
        GetFamilyInfo_Apply(nStartIndex, nReqCount, nReqGroup, pInfo);
    }

    if (nReqType & eFamilyInfoReq_BasicInfo) {
        GetFamilyInfo_BasicInfo(nStartIndex, nReqCount, nReqGroup, pInfo);
    }

    if (nReqType & eFamilyInfoReq_FamilyList) {
        GetFamilyInfo_FamilyList(nStartIndex, nReqCount, nReqGroup, pInfo);
    }

    if (nReqType & eFamilyInfoReq_MemberOL) {
        GetFamilyInfo_MemberOnline(nStartIndex, nReqCount, nReqGroup, pInfo);
    }
}

void GuildDataMgr::OnJoinGuildReq(uint64_t guildGUID)
{
    if (mGuild)
    {
        m_player->SendPopDlgMsgNtf("您已经加入了行会#COLORCOLOR_ORANGE#" + GetGuildName() + "#COLORCOLOR_WHITE#");
        return;
    }
    if (mGuildMember)
    {
        m_player->SendPopDlgMsgNtf("稍后再操作一遍!");
        return;
    }
    TRIGGER_EVENT(m_player, trigger_pre_join_family, m_player->GetGUIDAsString(), std::to_string(guildGUID));

    auto applicant = GetApplicant(guildGUID);

    uint8_t syncType = 0;

    if (applicant) {

        auto& status = applicant->status;

        if (status == guild_apply_status_applied ||
            status == guild_apply_status_passed) return;

        status = guild_apply_status_applied;
        applicant->apply_time = time(nullptr);
        syncType = db_op_type_update;
    }
    else {

        if (GuildMgr::GetInstance()->IsReachMaxMemberLimit(guildGUID)) {
            m_player->SendPopDlgMsgNtf("该行会已达最大人数限制");
            return;
        }

        applicant = AddApplicant(guildGUID);
        syncType = db_op_type_add;
    }

    GuildMgr::SyncApplicantToCS(applicant, syncType);

    // 处理请求
    GuildMgr::GetInstance()->CheckAutoJoinGuild(applicant);
}

void GuildDataMgr::OnCancelJoinGuildReq(uint64_t guildGUID)
{
    for (auto it = mGuildApplicants.begin(); it != mGuildApplicants.end(); ++it) {

        auto& apply = *it;

        if (apply->guild_id == guildGUID) {

            apply->player_name.clear();     // 减少传输
            GuildMgr::SyncApplicantToCS(apply, db_op_type_del);

            mGuildApplicants.erase(it);
            SendCancelFamilyJoinAckToGS(guildGUID, ERR_OK);
            break;
        }
    }

    GuildMgr::GetInstance()->RemoveApplicant(m_player->GetGUID(), guildGUID);
}

void GuildDataMgr::OnFamilyJoinAck(uint64_t applicantGUID, bool approved)
{
    auto* guildMgr = GuildMgr::GetInstance();
    if (!guildMgr) return;

    auto guildGUID = GetGuildID();
    auto sGuildGUID = std::to_string(guildGUID);
    const auto &guildName = GetGuildName();
    auto sApplicantGUID = std::to_string(applicantGUID);
    auto handledBy = m_player->GetName();

    auto apply = guildMgr->GetApplicant(guildGUID, applicantGUID);
    if (!apply) return;

    if (!apply->handled_by.empty()) {     // 已处理

        char msg[100];

        sprintf_s(msg, _countof(msg), "该申请已被#COLORCOLOR_BLUE#「%s」#COLORCOLOR_ORANGE#%s",
            apply->handled_by.c_str(), apply->status == guild_apply_status_passed ? "批准" : "拒绝");

        m_player->SendPopDlgMsgNtf(msg);
        return;
    }

    if (approved) {

        if (guildMgr->IsPlayerInGuild(applicantGUID)) {
            m_player->SendPopDlgMsgNtf("该申请者已加入其他帮会");
            return;
        }
        else if (guildMgr->IsReachMaxMemberLimit(guildGUID)) {
            m_player->SendPopDlgMsgNtf("当前行会已达最大人数限制");
            return;
        }
    }

    apply->handled_by = handledBy;

    auto* applicant = MapRoleMgr::GetInstance()->FindPlayer(applicantGUID);

    if (applicant) {    // 在线

        TRIGGER_EVENT(applicant, trigger_family_apply_ntf, sApplicantGUID, sGuildGUID,
            guildName, handledBy, approved);
    }

    if (approved) {

        auto member = std::make_shared<GUILD_MEMBER>();
        member->player_id = apply->player_id;
        member->player_name = apply->player_name;
        member->job = apply->job;
        member->level = applicant ? applicant->GetRoleProp(role_level) : apply->level;
        member->guild_id = apply->guild_id;
        member->title = member->new_title = guild_member_title_member;
        member->join_time = time(nullptr);
        member->login_time = applicant ? applicant->GetLoginTime() : apply->login_time;
        member->online = applicant && (applicant->GetOnlineState() == online_state_logged_in) ? true : false;
        guildMgr->AddMember(member);

        GuildMgr::SyncGuildMemberToCS(member, db_op_type_add);

        TRIGGER_EVENT(applicant, trigger_family_member_ntf, sGuildGUID, guildName,
            sApplicantGUID, family_member_ntf_add_member, apply->player_name, m_player->GetGUIDAsString());

        if (applicant) {
            applicant->GetGuildDataMgr().SetGuild(GetGuild());
            applicant->GetGuildDataMgr().SetGuildMember(member);
            applicant->GetGuildDataMgr().SendPlayerFamilyChangeNtfToGS(guildName);

            auto timeStr = ITimeHelper::GetInstance()->GetCurTimeStr();
            auto msg = timeStr + "加入了行会。";
            auto& data = gMESSAGE_INFO;
            data.Clear();
            data.type = relation_chat_ntf_type_guild;
            data.scroll_times = 1;
            strcpy_s(data.message, _countof(data.message), msg.c_str());
            m_player->SendRelationChatNtf(data);
        }
    }

    apply->status = approved ? guild_apply_status_passed : guild_apply_status_failed;

    if (applicant) {
        GuildMgr::SyncApplicantToCS(apply, db_op_type_del);
        applicant->GetGuildDataMgr().RemoveApplicant(guildGUID);
        guildMgr->RemoveApplicant(applicantGUID, guildGUID);
    }
    else {
        GuildMgr::SyncApplicantToCS(apply, db_op_type_update);
    }
}

void GuildDataMgr::OnKickGuildMember(uint64_t memberGUID)
{
    auto myGUID = m_player->GetGUID();

    if (GuildMgr::CheckInCastleWar())
    {
        LOG_ERROR("沙巴克期间不允许踢人");
        m_player->SendPopDlgMsgNtf("沙巴克期间不允许踢人");
        return;
    }
    if (myGUID == memberGUID) {
        m_player->SendPopDlgMsgNtf("不能踢自己");
        return;
    }

    if (!mGuildMember) return;
    auto myTitle = mGuildMember->title;

    if (myTitle != guild_member_title_chairman &&
        myTitle != guild_member_title_vice_chairman) {
        m_player->SendPopDlgMsgNtf("对不起，您没有权限");
        return;
    }

    auto guildGUID = GetGuildID();
    auto myName = m_player->GetName();

    auto* guildMgr = GuildMgr::GetInstance();
    if (!guildMgr) return;

    auto member = guildMgr->GetMember(memberGUID);
    if (!member || member->guild_id != guildGUID) {
        m_player->SendPopDlgMsgNtf("该玩家已退出帮会");
        return;
    }

    member->status = guild_member_status_removed;
    member->kicked_by = myName;

    auto& memberName = member->player_name;

    auto* player = MapRoleMgr::GetInstance()->FindPlayer(memberGUID);

    if (player) {
        player->GetGuildDataMgr().BeingKickedFromGuild();
    }
    else {
        GuildMgr::SyncGuildMemberToCS(member, db_op_type_update);
    }
}

void GuildDataMgr::OnEditGuildNotice(const char* notice)
{
    if (!notice || !mGuild) return;
    mGuild->notice = notice;

    GuildMgr::SyncGuildInfoToCS(mGuild, db_op_type_update);
}

////////////////////////////////////////////
void GuildDataMgr::BeingKickedFromGuild()
{
    LeaveGuild(mGuildMember->kicked_by);
}

void GuildDataMgr::LeaveGuild(const std::string& kickedBy)
{
    auto* guildMgr = GuildMgr::GetInstance();
    if (!guildMgr) return;

    auto guildGUID = GetGuildID();
    auto sGuildGUID = std::to_string(guildGUID);
    const auto &guildName = GetGuildName();
    auto memberGUID = m_player->GetGUID();
    auto sMemberGUID = m_player->GetGUIDAsString();
    auto memberName = m_player->GetName();

    TRIGGER_EVENT(m_player, trigger_family_member_ntf, sGuildGUID, guildName,
        sMemberGUID, family_member_ntf_del_member, memberName, "");

    SendPlayerFamilyChangeNtfToGS("");

    SendFamilyLeaveNtf(guildName, kickedBy);
    GuildMgr::SyncGuildMemberToCS(mGuildMember, db_op_type_del);

    mGuildMember = nullptr;
    mGuild = nullptr;

    guildMgr->RemoveMember(guildGUID, memberGUID);
}

void GuildDataMgr::RemoveApplicant(uint64_t guildGUID)
{
    for (auto it = mGuildApplicants.begin(); it != mGuildApplicants.end(); ++it) {
        auto& apply = *it;
        if (apply->guild_id == guildGUID) {
            mGuildApplicants.erase(it);
            break;
        }
    }
}

void GuildDataMgr::UpdateGuildInfoOnLogout()
{
    SetGuildMemberOnline(false);

    for (auto& apply : mGuildApplicants) {
        apply->level = m_player->GetRoleProp(role_level);
        apply->login_time = m_player->GetLoginTime();
    }
}

bool GuildDataMgr::GuildTitleChanged()
{
    if (!mGuildMember) return false;
    return mGuildMember->title != mGuildMember->new_title;
}

bool GuildDataMgr::NeedNtfGuildApplyResult()
{
    for (auto& apply : mGuildApplicants)
        if (apply->status == guild_apply_status_passed ||
            apply->status == guild_apply_status_failed)
            return true;

    return false;
}

void GuildDataMgr::DelayNtfGuildApplyResult(int32_t delayTime)
{
    auto playerGUID = m_player->GetGUID();

    TimerData param;
    param.interval = delayTime;
    param.loop = false;
    param.callBack = [&, playerGUID](const TimerData&) {

        auto* self = MapRoleMgr::GetInstance()->FindPlayer(playerGUID);
        if (self != m_player) return;

        auto* guildMgr = GuildMgr::GetInstance();
        if (!guildMgr) return;

        auto sPlayerGUID = m_player->GetGUIDAsString();

        for (auto it = mGuildApplicants.begin(); it != mGuildApplicants.end(); ) {

            auto& apply = *it;

            if (apply->status != guild_apply_status_passed &&
                apply->status != guild_apply_status_failed) {
                ++it;
                continue;
            }

            auto guildGUID = apply->guild_id;
            auto sGuildGUID = std::to_string(guildGUID);
            const auto &guildName = guildMgr->GetGuildName(guildGUID);

            TRIGGER_EVENT(m_player, trigger_family_apply_ntf, sPlayerGUID, sGuildGUID,
                guildName, apply->handled_by, (apply->status == guild_apply_status_passed));

            GuildMgr::SyncApplicantToCS(apply, db_op_type_del);
            guildMgr->RemoveApplicant(playerGUID, guildGUID);

            it = mGuildApplicants.erase(it);
        }
    };

    ITimeHelper::GetInstance()->AddTimer(param);
}

void GuildDataMgr::DelayNtfGuildTitleChanged(int32_t delayTime)
{
    auto myGUID = m_player->GetGUID();

    TimerData param;
    param.interval = delayTime;
    param.loop = false;
    param.callBack = [&, myGUID](const TimerData&) {
        auto* self = MapRoleMgr::GetInstance()->FindPlayer(myGUID);
        if (self != m_player) return;
        if (!mGuild) return;

        auto guildGUID = mGuild->id;
        auto sGuildGUID = std::to_string(guildGUID);
        auto& guildName = mGuild->name;

        auto sMyGUID = m_player->GetGUIDAsString();
        auto myName = m_player->GetName();

        TRIGGER_EVENT(m_player, trigger_family_member_ntf, sGuildGUID, guildName,
            sMyGUID, family_member_ntf_change_title, myName, "");

        if (!mGuildMember) return;
        if (mGuildMember->title == mGuildMember->new_title) return;
        GuildMgr::SyncGuildTitle(mGuildMember);
        SendFamilyInfoNtfToGS(eFamilyInfoReq_Title);
        SendPlayerFamilyChangeNtfToGS(guildName);
    };

    ITimeHelper::GetInstance()->AddTimer(param);
}

void GuildDataMgr::DelayNtfRemovedFromGuild(int32_t delayTime)
{
    auto myGUID = m_player->GetGUID();

    TimerData param;
    param.interval = delayTime;
    param.loop = false;
    param.callBack = [&, myGUID](const TimerData&) {

        auto* self = MapRoleMgr::GetInstance()->FindPlayer(myGUID);
        if (self != m_player) return;

        BeingKickedFromGuild();
    };

    ITimeHelper::GetInstance()->AddTimer(param);
}

void GuildDataMgr::DelayNtfDestoryGuild(int32_t delayTime)
{
    auto myGUID = m_player->GetGUID();

    TimerData param;
    param.interval = delayTime;
    param.loop = false;
    param.callBack = [&, myGUID](const TimerData&) {

        auto* self = MapRoleMgr::GetInstance()->FindPlayer(myGUID);
        if (self != m_player) return;
        BeingKickedFromGuild();
        m_player->SendPopDlgMsgNtf("您所在的行会已解散");
        };

    ITimeHelper::GetInstance()->AddTimer(param);
}

void GuildDataMgr::SendFamilyInfoNtfToGS(uint32_t type)
{
    ProtoMS_FamilyInfoNtf data;

    data.sessionid = m_player->GetClSessionID();
    data.type = type;

    SendDataBySessionID(m_player->GetGsSessionID(), data);
}

void GuildDataMgr::SendFamilyMembersAck(uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo, bool onlineOnly)
{
    auto* mgr = GuildMgr::GetInstance();
    if (!mgr) return;

    auto guildID = GetGuildID();
    if (guildID == 0) return;

    auto* members = mgr->GetMemberList(guildID);
    if (!members) return;

    ProtoMS_FamilyMembersAck data;

    data.sessionid = m_player->GetClSessionID();
    data.first_index = nStartIndex;

    auto& total = data.total_num;
    auto& n = data.members_num;

    for (auto it = members->begin(); it != members->end(); ++it) {

        auto& member = *it;

        if (member->status == guild_member_status_removed) continue;

        if (onlineOnly && !member->online) continue;

        if (total++ >= nStartIndex && n < nReqCount && n < _countof(data.members)) {

            auto& dst = data.members[n++];

            dst.player_guid = member->player_id;
            strcpy_s(dst.player_name, _countof(dst.player_name), member->player_name.c_str());
            dst.level = member->level;
            dst.job = member->job;
            dst.family_guid = member->guild_id;
            dst.title_id = member->new_title;
            dst.join_time = member->join_time;
            dst.login_time = member->login_time;
            dst.is_online = member->online;
            dst.cur_ctrb = member->cur_contrib;
            dst.totle_ctrb = member->total_contrib;
            dst.kills = member->kills;
            dst.combat_capability = member->combat_cap;
        }
    }

    SendDataBySessionID(m_player->GetGsSessionID(), data);
}

void GuildDataMgr::SendFamilyLeaveNtf(const std::string& guildName, const std::string& kickerName)
{
    ProtoMS_FamilyLeaveNtf data;
    data.sessionid = m_player->GetClSessionID();
    strcpy_s(data.kicker_name, _countof(data.kicker_name), kickerName.c_str());
    strcpy_s(data.family_name, _countof(data.family_name), guildName.c_str());

    SendDataBySessionID(m_player->GetGsSessionID(), data);
}

void GuildDataMgr::SendPlayerFamilyChangeNtfToGS(const std::string & guildName)
{
    ProtoMS_PlayerFamilyChangeNtf data;

    auto title = GetGuildMemberTitle();

    data.player_guid = m_player->GetGUID();
    strcpy_s(data.family_name, _countof(data.family_name), guildName.c_str());
    data.title = static_cast<uint8_t>(title);

    auto f = [&](Player *player) {
        data.sessionid = player->GetClSessionID();
        SendDataBySessionID(player->GetGsSessionID(), data);
    };

    m_player->ApplyFuncToAroundPlayers(f);
}

void GuildDataMgr::SendCancelFamilyJoinAckToGS(uint64_t guildGUID, uint32_t errcode)
{
    ProtoMS_CancelFamilyJoinAck data;
    data.sessionid = m_player->GetClSessionID();
    data.guid = guildGUID;
    data.errcode = errcode;

    SendDataBySessionID(m_player->GetGsSessionID(), data);
}


void GuildMgr::SyncGuildTitle(SPGUILD_MEMBER& mGuildMember)
{
    if (!mGuildMember) return;

    mGuildMember->title = mGuildMember->new_title;
    SyncGuildMemberToCS(mGuildMember, db_op_type_update);
}

void GuildMgr::SyncGuildMemberToCS(SPGUILD_MEMBER& member, uint8_t type)
{
    if (!member) return;

    ProtoMS_SyncGuildMember data;
    data.type = type;
    data.member = member.get();

    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void GuildMgr::SyncApplicantToCS(SPGUILD_APPLICANT& applicant, uint8_t type)
{
    if (!applicant) return;

    ProtoMS_SyncGuildApplicant data;
    data.type = type;
    data.applicant = applicant.get();

    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void GuildMgr::SyncGuildInfoToCS(SPGUILD& mGuild, uint8_t type)
{
    if (!mGuild) return;

    ProtoMS_SyncGuildInfo data;
    data.type = type;
    data.guild = mGuild.get();

    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}






void GuildDataMgr::GetFamilyInfo_Notice(uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo)
{
    if (!HasGuild()) return;

    ProtoMS_FamilyNoticeAck data;
    data.sessionid = m_player->GetClSessionID();
    data.notice_len = mGuild->notice.length() + 1;
    sprintf_s(data.notice, _countof(data.notice), mGuild->notice.c_str());

    SendDataBySessionID(m_player->GetGsSessionID(), data);
}

void GuildDataMgr::GetFamilyInfo_Member(uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo)
{
    SendFamilyMembersAck(nStartIndex, nReqCount, nReqGroup, pInfo, false);
}

void GuildDataMgr::GetFamilyInfo_Enemy(uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo)
{
    auto guildID = GetGuildID();
    if (guildID == 0) return;

    auto* enemies = GuildMgr::GetInstance()->GetEnemyList(guildID);
    if (!enemies) return;

    ProtoMS_FamilyEnemyAck data;

    data.sessionid = m_player->GetClSessionID();
    data.total_num = enemies->size();
    data.first_index = nStartIndex;

    if (nStartIndex < enemies->size()) {
        auto& n = data.enemy_num;

        for (auto it = std::next(enemies->begin(), nStartIndex); it != enemies->end(); ++it) {
            auto& enemy = data.enemy[n++];

            enemy.guid = *it;
            GuildMgr::GetInstance()->GetGuildName(enemy.guid, enemy.name, _countof(enemy.name));

            if (n == nReqCount || n == _countof(data.enemy)) break;
        }
    }

    SendDataBySessionID(m_player->GetGsSessionID(), data);
}

void GuildDataMgr::GetFamilyInfo_Ally(uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo)
{
    auto guildID = GetGuildID();
    if (guildID == 0) return;

    auto* allies = GuildMgr::GetInstance()->GetAllyList(guildID);
    if (!allies) return;

    ProtoMS_FamilyAllyAck data;

    data.sessionid = m_player->GetClSessionID();
    data.total_num = allies->size();
    data.first_index = nStartIndex;

    if (nStartIndex < allies->size()) {
        auto& n = data.ally_num;

        for (auto it = std::next(allies->begin(), nStartIndex); it != allies->end(); ++it) {
            auto& ally = data.ally[n++];

            ally.guid = *it;
            GuildMgr::GetInstance()->GetGuildName(ally.guid, ally.name, _countof(ally.name));

            if (n == nReqCount || n == _countof(data.ally)) break;
        }
    }

    SendDataBySessionID(m_player->GetGsSessionID(), data);
}

void GuildDataMgr::GetFamilyInfo_Apply(uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo)
{
    auto* mgr = GuildMgr::GetInstance();
    if (!mgr) return;

    auto guildID = GetGuildID();
    if (guildID == 0) return;

    auto title = GetGuildMemberTitle();
    if (!mgr->CanViewApplicants(title)) return;

    auto* applicants = mgr->GetApplicantList(guildID);
    if (!applicants) return;

    ProtoMS_FamilyJoinListAck data;

    data.sessionid = m_player->GetClSessionID();
    data.first_index = nStartIndex;

    auto& total = data.total_num;
    auto& n = data.num;

    for (auto it = applicants->begin(); it != applicants->end(); ++it) {

        auto& applicant = *it;

        if (applicant->status != guild_apply_status_applied) continue;

        if (total++ >= nStartIndex && n < nReqCount && n < _countof(data.info)) {

            auto* player = MapRoleMgr::GetInstance()->FindPlayer(applicant->player_id);

            auto& info = data.info[n++];
            info.player_guid = applicant->player_id;
            strcpy_s(info.player_name, _countof(info.player_name), applicant->player_name.c_str());
            info.level = player ? player->GetRoleProp(role_level) : applicant->level;   // 在线玩家用实时值
            info.job = applicant->job;
        }
    }

    SendDataBySessionID(m_player->GetGsSessionID(), data);
}

void GuildDataMgr::GetFamilyInfo_BasicInfo(uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo)
{
    auto guildID = GetGuildID();
    if (guildID == 0) return;

    ProtoMS_FamilyBaseInfoAck data;
    data.sessionid = m_player->GetClSessionID();
    data.family_guid = guildID;
    strcpy_s(data.name, _countof(data.name), GetGuildName().c_str());
    data.members_num = GuildMgr::GetInstance()->GetMemberNum(guildID);
    data.create_time = GetGuildCreationTime();
    data.self_title_id = GetGuildMemberTitle();

    SendDataBySessionID(m_player->GetGsSessionID(), data);
}

void GuildDataMgr::GetFamilyInfo_FamilyList(uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo)
{
    auto* mgr = GuildMgr::GetInstance();
    if (!mgr) return;

    auto& guilds = mgr->GetGuilds();

    ProtoMS_FamilyListNtfAck data;
    data.sessionid = m_player->GetClSessionID();
    data.total_num = guilds.size();
    data.first_index = nStartIndex;

    if (nStartIndex < guilds.size()) {
        auto& n = data.num;

        for (auto it = std::next(guilds.begin(), nStartIndex); it != guilds.end(); ++it) {

            auto& guild = it->second;

            auto& dst = data.familys[n++];
            dst.guid = guild->id;
            strcpy_s(dst.name, _countof(dst.name), guild->name.c_str());
            strcpy_s(dst.leader_name, _countof(dst.leader_name), guild->chairman_name.c_str());
            dst.members_num = mgr->GetMemberNum(guild->id);
            dst.is_applied = IsGuildApplied(guild->id);
            strcpy_s(dst.family_manifesto, _countof(dst.family_manifesto), guild->manifesto.c_str());
            dst.family_create_time = guild->ctime;
            dst.family_level = guild->level;

            if (n == nReqCount || n == _countof(data.familys)) break;
        }
    }

    SendDataBySessionID(m_player->GetGsSessionID(), data);
}

void GuildDataMgr::GetFamilyInfo_MemberOnline(uint32_t nStartIndex, uint32_t nReqCount, uint32_t nReqGroup, const char* pInfo)
{
    SendFamilyMembersAck(nStartIndex, nReqCount, nReqGroup, pInfo, true);
}
