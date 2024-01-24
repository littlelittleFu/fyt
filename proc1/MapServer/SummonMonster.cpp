#include "stdafx.h"
#include "SummonMonster.h"

SummonMonsterMgr::SummonMonsterMgr(Player* player) : m_player(player)
{
}

SummonMonsterMgr::~SummonMonsterMgr()
{
}

Monster* SummonMonsterMgr::SummonMonster(DATA::Monster* monsterCfg)
{
	if (nullptr == monsterCfg) {
		LOG_WARN("monsterCfg is null");
		return nullptr;
	}

	auto map = m_player->GetCurMap();
	if (nullptr == map) {
		LOG_WARN("map not exist");
		return nullptr;
	}

	int x0 = m_player->GetRolePosX();
	int y0 = m_player->GetRolePosY();

    uint16_t left = (uint16_t)std::max<int>(x0 - 3, 0);
    uint16_t top = (uint16_t)std::max<int>(y0 - 3, 0);
    uint16_t right = (uint16_t)std::min<int>(x0 + 3, map->GetWidth() - 1);
    uint16_t bottom = (uint16_t)std::min<int>(y0 + 3, map->GetHeight() - 1);

	uint16_t x1, y1;
	if (!map->GetRandBlankPointInRange(left, top, right - left + 1, bottom - top + 1, x1, y1)) {
		return nullptr;
	}

	auto monster = MapRoleMgr::GetInstance()->CreateMonster(monsterCfg->Id);
	if (nullptr == monster) {
		return nullptr;
	}

	monster->SetRolePos(x1, y1);
	monster->SetBornPos(x1, y1);
	monster->SetRoleDir(Tools::GenerateRandomInteger<uint16_t>(dir_up, dir_max - 1));
	monster->SetMasterGUID(m_player->GetGUID());
	monster->SetMasterName(m_player->GetRoleBriefInfo().name);
	monster->SetWayFinding(true);

	map->RoleEnter(monster);

	mSummonList.push_back(monster->GetGUID());
    CheckSummonMonsterNeedUpdate();

	return monster;
}

Monster* SummonMonsterMgr::SummonMonsterByID(uint16_t monsterID)
{
	auto monster = SummonMonster(sMonsterConfig.Get(monsterID));
	if (nullptr == monster) {
		LOG_WARN("SummonMonsterByID failed. monsterID:%d", monsterID);
	}
	return monster;
}

Monster* SummonMonsterMgr::SummonMonsterByName(const std::string& monsterName)
{
	auto monster = SummonMonster(sMonsterConfig.GetByKeyName(monsterName));
	if (nullptr == monster) {
		LOG_WARN("SummonMonsterByName failed. monsterName:%s", monsterName);
	}
	return monster;
}

void SummonMonsterMgr::DestroySummonMonster(uint64_t monsterGUID)
{
	auto it = std::find(mSummonList.begin(), mSummonList.end(), monsterGUID);
	if (it == mSummonList.end()) return;

	mSummonList.erase(it);
    CheckSummonMonsterNeedUpdate();

	auto monster = MapRoleMgr::GetInstance()->FindMonster(monsterGUID);
	if (nullptr != monster) {
		auto map = m_player->GetCurMap();
		if (nullptr != map) {
			map->GetMapAoi().RemoveRole(monster);
		}

		MapRoleMgr::GetInstance()->RemoveMonster(monsterGUID);
	}
}

void SummonMonsterMgr::DestroySummonMonster(const std::string& sMonsterGUID)
{
	if (sMonsterGUID.empty()) return;
	uint64_t monsterGUID = std::stoull(sMonsterGUID);
	DestroySummonMonster(monsterGUID);
}

Monster* SummonMonsterMgr::GetSummonMonster(uint16_t nTemplateID)
{
	for (auto nMonsterGUID : mSummonList) {

		auto pMonster = MapRoleMgr::GetInstance()->FindMonster(nMonsterGUID);
		if (!pMonster) continue;

		if (pMonster->GetTemplateID() == nTemplateID) return pMonster;
	}

	return nullptr;
}

void SummonMonsterMgr::UpdateSummonList()
{
	if (mSummonList.empty()) return;
	for (auto it = mSummonList.begin(); it != mSummonList.end();) {
		auto monster = MapRoleMgr::GetInstance()->FindMonster(*it);
		if (nullptr == monster || !monster->CheckAlive()) {
			it = mSummonList.erase(it);
			continue;
		}
		++it;
	}

    CheckSummonMonsterNeedUpdate();
}

void SummonMonsterMgr::SummonMonsterEnterMap()
{
	Map* map = m_player->GetCurMap();
	if (!map) return;

	for (const auto& guid : mSummonList) {

		auto* monster = MapRoleMgr::GetInstance()->FindMonster(guid);
		if (!monster) continue;

		map->RoleEnter(monster);
	}
}

void SummonMonsterMgr::SummonMonsterLeaveMap(uint64_t monsterGUID)
{
	Map* map = m_player->GetCurMap();
	if (!map) return;

	for (const auto& guid : mSummonList) {

		auto* monster = MapRoleMgr::GetInstance()->FindMonster(guid);
		if (!monster) continue;

		if (monsterGUID == 0)
		{
			map->RoleLeave(monster);
		}
		else if (guid == monsterGUID)
		{
			map->RoleLeave(monster);
			return;
		}
	}
}

void SummonMonsterMgr::DestroySummonMonster(bool destroySummonMonster)
{
	if (!destroySummonMonster) return;

	std::list<uint64_t> summonList = mSummonList;
	for (const auto& guid : summonList) {
		DestroySummonMonster(guid);
	}
}

void SummonMonsterMgr::SummonMonsterTeleportToMaster()
{
	for (const auto& guid : mSummonList) {

		auto* monster = MapRoleMgr::GetInstance()->FindMonster(guid);
		if (!monster) continue;

		monster->TeleportToMaster();
	}
}

void SummonMonsterMgr::ChangeMasterNameInfo(const std::string& name, ProtoGS_PlayerSetNameNtf& ntf)
{
	for (auto i : mSummonList) {
		auto summonMonster = MapRoleMgr::GetInstance()->FindMonster(i);
		if (!summonMonster)continue;
		summonMonster->SetMasterName(name);

		auto map = summonMonster->GetCurMap();
		if (!map)continue;
		map->SendMasterChangeNameNtf(summonMonster, ntf);
	}
}

void SummonMonsterMgr::CheckSummonMonsterNeedUpdate()
{
    if (!m_player) return;

    auto num = mSummonList.size();

    if (num == 0)
        m_player->ResetNeedUpdateFlag(summon_monster_need_udpate_flag);
    else
        m_player->SetNeedUpdateFlag(summon_monster_need_udpate_flag);
}
