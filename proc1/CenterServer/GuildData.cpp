#include "stdafx.h"
#include "GuildData.h"


IMPL_SINGLETON(GuildData)

void GuildData::SyncGuildApplicant(const SPGUILD_APPLICANT &applyInfo, uint8_t type)
{
    for (auto it = mApplicants.begin(); it != mApplicants.end(); ++it) {

        auto applicant = *it;

        if (applicant->player_id != applyInfo->player_id) continue;
        if (applicant->guild_id != applyInfo->guild_id) continue;

        mApplicants.erase(it);
        break;
    }

    if (type != db_op_type_del) {    // ·ÇÉ¾³ı²Ù×÷
        mApplicants.emplace_back(applyInfo);
    }
}

void GuildData::SyncGuildMember(const SPGUILD_MEMBER &member, uint8_t type)
{
    switch (type) {

    case db_op_type_add:
        mMembers.emplace(member->player_id, member);
        break;

    case db_op_type_del:
        mMembers.erase(member->player_id);
        break;

    case db_op_type_update:
        mMembers[member->player_id] = member;
        break;

    default:
        break;
    }
}

void GuildData::SyncGuildInfo(const SPGUILD &guild, uint8_t type)
{
    switch (type) {

    case db_op_type_add:
        mGuilds.emplace(guild->id, guild);
        break;

    case db_op_type_del:
        RemoveGuildRelation(guild->id);
        mGuilds.erase(guild->id);
        break;

    case db_op_type_update:
        mGuilds[guild->id] = guild;
        break;

    default:
        break;
    }
}

void GuildData::RemoveGuildRelation(uint64_t guid)
{
    auto guild = GetGuild(guid);
    if (!guild) return;

    for (const auto &id : guild->allies) {
        RemoveAlly(id, guid);
    }

    for (const auto &id : guild->enemies) {
        RemoveEnemy(id, guid);
    }

    guild->allies.clear();
    guild->enemies.clear();
}

void GuildData::RemoveAlly(uint64_t myGUID, uint64_t peerGUID)
{
    auto guild = GetGuild(myGUID);
    if (!guild) return;

    auto &allies = guild->allies;

    auto it = std::find(allies.begin(), allies.end(), peerGUID);
    if (it != allies.end()) allies.erase(it);
}

void GuildData::RemoveEnemy(uint64_t myGUID, uint64_t peerGUID)
{
    auto guild = GetGuild(myGUID);
    if (!guild) return;

    auto &enemies = guild->enemies;

    auto it = std::find(enemies.begin(), enemies.end(), peerGUID);
    if (it != enemies.end()) enemies.erase(it);
}

void GuildData::SyncGuildRelation(uint8_t type, uint64_t myGUID, uint64_t peerGUID, uint8_t relation)
{
    auto myGuild = GetGuild(myGUID);
    if (!myGuild) return;

    auto peerGuild = GetGuild(peerGUID);
    if (!peerGuild) return;

    switch (type) {

    case db_op_type_add:
    {
        if (relation == guild_relation_ally) {
            if (HasRelation(myGUID, peerGUID)) return;
            myGuild->allies.push_back(peerGUID);
            peerGuild->allies.push_back(myGUID);
        }
        else if (relation == guild_relation_enemy) {
            if (HasRelation(myGUID, peerGUID)) return;
            myGuild->enemies.push_back(peerGUID);
            peerGuild->enemies.push_back(myGUID);
        }

        break;
    }

    case db_op_type_del:
    {
        if (relation == guild_relation_ally) {
            auto it = std::find(myGuild->allies.begin(), myGuild->allies.end(), peerGUID);
            if (it != myGuild->allies.end()) myGuild->allies.erase(it);

            it = std::find(peerGuild->allies.begin(), peerGuild->allies.end(), myGUID);
            if (it != peerGuild->allies.end()) peerGuild->allies.erase(it);
        }
        else if (relation == guild_relation_enemy) {
            auto it = std::find(myGuild->enemies.begin(), myGuild->enemies.end(), peerGUID);
            if (it != myGuild->enemies.end()) myGuild->enemies.erase(it);

            it = std::find(peerGuild->enemies.begin(), peerGuild->enemies.end(), myGUID);
            if (it != peerGuild->enemies.end()) peerGuild->enemies.erase(it);
        }
    }

    default:
        break;
    }
}

void GuildData::ChangeNameInfo(uint64_t guid, const std::string& name)
{
    for (auto i : mGuilds){
        if (!i.second)continue;
        if (i.second.get()->chairman_id == guid){
            i.second.get()->chairman_name = name;
        }
        if (i.second.get()->creator_id == guid){
            i.second.get()->creator_name = name;
        }
    }
    
    auto memberIter = mMembers.find(guid);
    if (memberIter != mMembers.end()) {
        if (memberIter->second) {
            memberIter->second.get()->player_name = name;
        }
    }

    for (auto i : mApplicants){
        if (!i)continue;
        if (i.get()->player_id == guid){
            i.get()->player_name = name;
            break;
        }
    }
    
}

SPGUILD GuildData::GetGuild(uint64_t guid)
{
    auto it = mGuilds.find(guid);
    return it == mGuilds.end() ? nullptr : it->second;
}

bool GuildData::IsGuildExist(uint64_t guid)
{
    return mGuilds.find(guid) != mGuilds.end();
}

bool GuildData::IsExistInList(const GUILD_ID_LIST &idList, uint64_t id)
{
    return std::find(idList.begin(), idList.end(), id) != idList.end();
}

bool GuildData::HasRelation(uint64_t guid1, uint64_t guid2)
{
    auto guild1 = GetGuild(guid1);
    if (!guild1) return false;

    auto guild2 = GetGuild(guid2);
    if (!guild2) return false;

    if (IsExistInList(guild1->allies, guid2)) return true;
    if (IsExistInList(guild1->enemies, guid2)) return true;
    if (IsExistInList(guild2->allies, guid1)) return true;
    if (IsExistInList(guild2->enemies, guid1)) return true;
    return false;
}
