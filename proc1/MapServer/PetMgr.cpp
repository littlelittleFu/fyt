#include "stdafx.h"
#include "PetMgr.h"
#define MAX_PET_GEN_RANGE 10
#define MAX_PET_GEN_RANGE_BY_RULE 3

Pet* PetMgr::PetMonster(DATA::Monster* monsterCfg)
{
	if (nullptr == m_player) {
		LOG_WARN("belong not exist");
		return nullptr;
	}

	auto map = m_player->GetCurMap();
	if (nullptr == map) {
		LOG_WARN("map not exist");
		return nullptr;
	}

	int x0 = m_player->GetRolePosX();
	int y0 = m_player->GetRolePosY();

	std::vector<std::pair<uint16_t, uint16_t>> canTakePoint;
	auto playerDir = m_player->GetRoleDir();
	for (int range = 1; range <= MAX_PET_GEN_RANGE; ++range)
	{
		map->GetAllBlankPointInRange(x0, y0, range, range, canTakePoint);

		// 玩家周围3圈以内 宠物只生成在反方向
		if (range <= MAX_PET_GEN_RANGE_BY_RULE)
		{
			int negativeDir = (playerDir + 4) % dir_max;
			for (auto iter = canTakePoint.begin(); iter != canTakePoint.end();)
			{
				auto curdir = Utility::CalcRelativeDir(iter->first, iter->second, x0, y0);
				if (curdir == negativeDir || curdir == (negativeDir + 1) % dir_max || curdir == (negativeDir + dir_max - 1) % dir_max)
				{
					iter = canTakePoint.erase(iter);
					continue;
				}
				++iter;
			}
		}

		if (!canTakePoint.empty()) break;
	}
	if (canTakePoint.empty()) return nullptr;

	//uint16_t left = (uint16_t)std::max<int>(x0 - 3, 0);
	//uint16_t top = (uint16_t)std::max<int>(y0 - 3, 0);
	//uint16_t right = (uint16_t)std::min<int>(x0 + 3, map->GetWidth() - 1);
	//uint16_t bottom = (uint16_t)std::min<int>(y0 + 3, map->GetHeight() - 1);

	//uint16_t x1, y1;
	//if (!map->GetRandBlankPointInRange(left, top, right - left + 1, bottom - top + 1, x1, y1)) {
	//	return nullptr;
	//}

	auto pet = MapRoleMgr::GetInstance()->CreatePet(monsterCfg->Id);
	if (nullptr == pet) {
		return nullptr;
	}

	pet->OnEnterMap(map);
	pet->SetRolePos(canTakePoint[0].first,canTakePoint[0].second);
	//pet->SetBornPos(x1, y1);
	pet->SetRoleDir(Tools::GenerateRandomInteger<uint16_t>(dir_up, dir_max - 1));
	pet->SetMasterGUID(m_player->GetGUID());
	pet->SetMasterName(m_player->GetRoleBriefInfo().name);
	pet->SetWayFinding(true);
	pet->SetPetType(monsterCfg->MonsterAIType);
	map->RoleEnter(pet);

	mPetList.push_back(pet->GetGUID());
	CheckPetMonsterNeedUpdate();

	return pet;
}
Pet* PetMgr::PetMonsterByID(uint16_t monsterID)
{
	auto cfg = sMonsterConfig.Get(monsterID);
	if (nullptr == cfg) {
		LOG_WARN("monster cfg not exist");
		return nullptr;
	}

	if (cfg->MonsterAIType != type6_normal_pet && cfg->MonsterAIType != type7_taoist_pet)
	{
		LOG_WARN("monsterAI cfg not is pet");
		return nullptr;
	}
	auto pet = PetMonster(cfg);
	if (pet == nullptr)
	{
		LOG_WARN("petmonster gen by id failed,monsterid: %d",monsterID);
		return nullptr;
	}
	return pet;

}
Pet* PetMgr::PetMonsterByName(const std::string& monsterName)
{
	auto cfg = sMonsterConfig.GetByKeyName(monsterName);
	if (nullptr == cfg) {
		LOG_WARN("monster cfg not exist");
		return nullptr;
	}

	if (cfg->MonsterAIType != type6_normal_pet && cfg->MonsterAIType != type7_taoist_pet)
	{
		LOG_WARN("monsterAI cfg not is pet");
		return nullptr;
	}
	auto pet = PetMonster(cfg);
	if (pet == nullptr)
	{
		LOG_WARN("petmonster gen by name failed,monsterName:%s", monsterName.c_str());
		return nullptr;
	}
	return pet;
}

Pet* PetMgr::PetMonsterByIDByLuaTable(uint16_t monsterID, const CLuaObject& luaObj)
{
	auto pet = PetMonsterByID(monsterID);
	if (!pet)return nullptr;
	UpdatePetPropByLUaTable(pet, luaObj);
	return pet;
}

Pet* PetMgr::PetMonsterByNameByLuaTable(const std::string& monsterName, const CLuaObject& luaObj)
{
	auto pet = PetMonsterByName(monsterName);
	if (!pet)return nullptr;
	UpdatePetPropByLUaTable(pet, luaObj);
	return pet;
}

void PetMgr::DestroyPet()
{
	for (auto& i : mPetList)
	{
		auto pet = MapRoleMgr::GetInstance()->FindPet(i);
		if (nullptr != pet) {
			auto map = m_player->GetCurMap();
			if (nullptr != map) {
				map->GetMapAoi().RemoveRole(pet);
			}

			MapRoleMgr::GetInstance()->RemovePet(i);
		}
	}
	mPetList.clear();
}

void PetMgr::DestroyPet(uint64_t petGUID)
{
	auto it = std::find(mPetList.begin(), mPetList.end(), petGUID);
	if (it == mPetList.end()) return;

	mPetList.erase(it);
	CheckPetMonsterNeedUpdate();

	auto pet = MapRoleMgr::GetInstance()->FindPet(petGUID);
	if (nullptr != pet) {
		auto map = m_player->GetCurMap();
		if (nullptr != map) {
			map->GetMapAoi().RemoveRole(pet);
		}

		MapRoleMgr::GetInstance()->RemovePet(petGUID);
	}
}

void PetMgr::DestroyPet(const std::string& sPetGUID)
{
	if (sPetGUID.empty()) return;
	uint64_t petGUID = std::stoull(sPetGUID);
	DestroyPet(petGUID);
}

void PetMgr::UpdatePetPropByLUaTable(Pet* pet, const CLuaObject& luaObj)
{
	if (!pet)return;

	if (luabind::type(luaObj) != LUA_TTABLE)
	{
		LOG_ERROR("retDeopData is not table!");
		return;
	}

	for (luabind::iterator it(luaObj), end; it != end; ++it)
	{
		if (luabind::type((*it)[1]) != LUA_TNUMBER)
		{
			LOG_ERROR("key is not number!");
			return;
		}
		auto key = luabind::object_cast<std::int32_t>((*it)[1]);
		if (luabind::type((*it)[2]) != LUA_TNUMBER)
		{
			LOG_ERROR("value is not number!");
			return;
		}
		auto value = luabind::object_cast<std::int32_t>((*it)[2]);
		if (key == role_base_max_hp)
		{
			pet->SetRoleProp(key, value);
			pet->SetRoleProp(role_hp, value);
		}
		else if (key == role_base_max_mp)
		{
			pet->SetRoleProp(key, value);
			pet->SetRoleProp(role_mp, value);

		}
		else
		{
			pet->SetRoleProp(key, value);
		}
	}
}

void PetMgr::SetPetActivityStatus(const std::string& guid, uint16_t status)
{
	auto pet = MapRoleMgr::GetInstance()->FindPet(std::stoull(guid));
	if (!pet)
	{
		LOG_ERROR("set pet activity status failed! guid:%s",guid.c_str());
		return;
	}
	auto petAI = pet->GetAIPet();
	if (!petAI)return;

	petAI->SetActivityStatus(status);
}

void PetMgr::SetPetPickItemStatus(const std::string& guid, bool canPickitem)
{
	auto pet = MapRoleMgr::GetInstance()->FindPet(std::stoull(guid));
	if (!pet)
	{
		LOG_ERROR("set pet activity status failed! guid:%s", guid.c_str());
		return;
	}
	auto petAI = pet->GetAIPet();
	if (!petAI)return;

	canPickitem == true ? petAI->SetCanPickItem() : petAI->ResetCanPickItem();
}

void PetMgr::UpdatePetList()
{
	if (mPetList.empty()) return;
	for (auto it = mPetList.begin(); it != mPetList.end();) {
		auto pet = MapRoleMgr::GetInstance()->FindPet(*it);
		if (nullptr == pet || !pet->CheckAlive()) {
			it = mPetList.erase(it);
			continue;
		}
		++it;
	}

	CheckPetMonsterNeedUpdate();
}

void PetMgr::PetEnterMap()
{
	Map* map = m_player->GetCurMap();
	if (!map) return;

	for (const auto& guid : mPetList) {

		auto* pet = MapRoleMgr::GetInstance()->FindPet(guid);
		if (!pet) continue;

		auto AI = pet->GetAIPet();
		if (!AI)continue;
		if (AI->GetActivityStatus() == pet_activity_status_stay)continue;

		map->RoleEnter(pet);
		auto petAI = pet->GetAIPet();
		if (!petAI)continue;
		petAI->JumpToMaster();
	}
}

void PetMgr::PetLeaveMap(uint64_t petGUID)
{
	Map* map = m_player->GetCurMap();
	if (!map) return;

	for (const auto& guid : mPetList) {

		auto* Pet = MapRoleMgr::GetInstance()->FindPet(guid);
		if (!Pet) continue;

		auto AI = Pet->GetAIPet();
		if (!AI)continue;
		if (AI->GetActivityStatus() == pet_activity_status_stay)continue;

		auto rolemove = Pet->GetRoleMove();
		if (rolemove)
		{
			rolemove->StopMove();
		}

		if (petGUID == 0)
		{
			map->RoleLeave(Pet);
		}
		else if (guid == petGUID)
		{
			map->RoleLeave(Pet);
			return;
		}
	}
}

void PetMgr::CheckPetMonsterNeedUpdate()
{
	if (!m_player) return;

	auto num = mPetList.size();

	if (num == 0)
		m_player->ResetNeedUpdateFlag(pet_monster_need_udpate_flag);
	else
		m_player->SetNeedUpdateFlag(pet_monster_need_udpate_flag);
}

void PetMgr::PetTeleportToMaster()
{
    for (const auto &guid : mPetList) {

        auto *pet = MapRoleMgr::GetInstance()->FindPet(guid);
        if (!pet) continue;

        auto *ai = pet->GetAIPet();
        if (!ai) continue;

        ai->JumpToMaster();
    }
}

void PetMgr::ChangeMasterNameInfo(const std::string& name, ProtoGS_PlayerSetNameNtf& ntf)
{
	for (auto i : mPetList) {
		auto pet = MapRoleMgr::GetInstance()->FindPet(i);
		if (!pet)continue;
		pet->SetMasterName(name);

		auto map = pet->GetCurMap();
		if (!map)continue;
		map->SendMasterChangeNameNtf(pet, ntf);
	}
}