#include"stdafx.h"
#include"PKValueMgr.h"
#include "CastleWarMgr.h"

void PKValueMgr::AddPKValue(uint64_t killerguid, Player *victim)
{
	auto role = MapRoleMgr::GetInstance()->FindRole(killerguid);
	if (!role)return;

	Player* finalPlayer = nullptr;

	if (role->IsPlayer()) {
		finalPlayer = static_cast<Player*>(role);
	}
	else if (role->IsPet()) {
		auto pet = static_cast<Pet*>(role);
		if (pet) {
			finalPlayer = pet->GetMaster();
		}
	}
	else if (role->IsPlayerDoplganr()) {
		auto doplganr = static_cast<PlayerDoplganr*>(role);
		if (doplganr) {
			finalPlayer = doplganr->GetMaster();
		}
	}

	if (!finalPlayer)return;

	auto map = finalPlayer->GetCurMap();
	if (!map)return;
	if (!map->GetMapConfig()->KillPk)return;
    if (IsShabakNoPK(finalPlayer, victim)) return;

	auto curPK = finalPlayer->GetRoleProp(role_pk);
	auto finalPK = curPK + sGlobalConfig.GetData()->IncreasePKValueWithKillWhite;
	// pk值设定上限
	finalPK = finalPK > MAX_ROLE_PK ? MAX_ROLE_PK : finalPK;
	if (curPK != MAX_ROLE_PK) {
		finalPlayer->SetRoleProp(role_pk, finalPK);
	}
	if (finalPK > sGlobalConfig.GetData()->PKValueOfYellowName)
	{
		finalPlayer->RemoveBuff(sGlobalConfig.GetData()->GrayBuffID);
	}
}

bool PKValueMgr::IsShabakNoPK(Player *killer, Player *victim)
{
    if (!killer || !victim) return false;

    const auto &killerGuild = killer->GetGuildName();
    const auto &victimGuild = victim->GetGuildName();

    auto *castleWarMgr = CastleWarMgr::GetInstance();
    if (!castleWarMgr) return false;

    if (!castleWarMgr->IsInWar()) return false;
    if (!castleWarMgr->IsInShabak(killer)) return false;
    if (!castleWarMgr->IsInShabak(victim)) return false;
    if (!castleWarMgr->IsEngagedGuild(killerGuild)) return false;
    if (!castleWarMgr->IsEngagedGuild(victimGuild)) return false;

    return true;
}

bool PKValueMgr::IsWhiteName(uint64_t guid)
{
	auto player = MapRoleMgr::GetInstance()->FindPlayer(guid); 
	if (!player)return true;
	if (player->GetRoleProp(role_is_gray) >= 1)
		return false;
	if (player->GetRoleProp(role_pk) > sGlobalConfig.GetData()->PKValueOfYellowName)
		return false;
	return true;
}

bool PKValueMgr::IsYellowName(uint64_t guid)
{
	auto player = MapRoleMgr::GetInstance()->FindPlayer(guid);
	if (!player)return true;
	if (player->GetRoleProp(role_pk) > sGlobalConfig.GetData()->PKValueOfYellowName && 
		player->GetRoleProp(role_pk) <= sGlobalConfig.GetData()->PKValueOfRedName)
		return true;
	return false;
}


//bool PKValueMgr::IsYellowName(uint64_t guid)
//{
//	auto player = MapRoleMgr::GetInstance()->FindPlayer(guid);
//	if (!player)return true;
//	auto pk = player->GetRoleProp(role_pk);
//	if (pk > sGlobalConfig.GetData()->PKValueOfYellowName)
//	{
//		return true;
//	}
//	return false;
//}

void PKValueMgr::UpdatePKValue(int delta)
{
    if (!mPlayer) return;

    auto pk = mPlayer->GetRoleProp(role_pk);
    if (pk == 0) {
        mCurRedNameTime = 0;
        return;
    }

    mCurRedNameTime += delta;

    auto interval = S2MS(sGlobalConfig.GetData()->DcreasePKValueInterval);
    if (mCurRedNameTime < interval) return;

    mCurRedNameTime -= interval;
    mPlayer->SetRoleProp(role_pk, --pk);

    if (pk == 0) {
        mCurRedNameTime = 0;
    }
}
