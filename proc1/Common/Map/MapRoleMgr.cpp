#include "stdafx.h"
#include "MapRoleMgr.h"
#include "role_table.hpp"
#include "MapMgr.h"
#include "../../MapServer/MapAoi.h"
#include "SessionFactory.h"
#include "CNetManager.h"
#include "PlayerDoplganr.h"

#define _CRTDBG_MAP_ALLOC 
IMPL_SINGLETON(MapRoleMgr)
MapRoleMgr::MapRoleMgr()
{
	mScriptName = "LuaRoleMgr";
}

MapRoleMgr::~MapRoleMgr()
{

}

StallDummy* MapRoleMgr::CreateStallDummy(Player* player)
{
	if (!player) return nullptr;
	SAFE_BEGIN_EX;

	uint64_t nSDPlayerID = GenerateObjID(E_OBJ_STALL_DUMMY, ConfigInfo::GetInstance());
	auto sdPlayer = new StallDummy(player);
	sdPlayer->Init();
	sdPlayer->SetGUID(nSDPlayerID);
	mStallDummyMap.emplace(PlayerStallDummyKey{ player->GetGUID(), nSDPlayerID }, sdPlayer);
	return sdPlayer;
	SAFE_END_EX(nullptr);
}

Player* MapRoleMgr::AddPlayer(uint64_t id)
{
	SAFE_BEGIN_EX;
	auto player = FindPlayer(id);
	auto it = mPlayerandDoplganrMap.find(id);
	if (it != mPlayerandDoplganrMap.end()) {              
		RemovePlayerDoplganr(it->second);
		mPlayerandDoplganrMap.erase(it);                  
	}

	if (nullptr != player) {
		LOG_ERROR("add player failed IS ADD ");
		player->OnExit(1);
		return nullptr;
	}
	player = new Player();
    player->Init();
	player->SetGUID(id);
	mPlayerMap.emplace(id, player);
	return player;
	SAFE_END_EX(nullptr);
}

Npc* MapRoleMgr::CreateNpc(uint16_t nTemplateID)
{
    SAFE_BEGIN_EX;

    auto pNpcConfig = sNpcConfig.Get(nTemplateID);
    if (!pNpcConfig) return nullptr;

    uint64_t nNpcID = GenerateObjID(E_OBJ_NPC, ConfigInfo::GetInstance());

    auto pNpc = new Npc();
    pNpc->Init(nNpcID, pNpcConfig);

    mNpcMap.emplace(nNpcID, pNpc);
    return pNpc;

    SAFE_END_EX(nullptr);
}

Monster* MapRoleMgr::CreateMonster(uint16_t nTemplateID)
{
	SAFE_BEGIN_EX;

    auto pMonsterConfig = sMonsterConfig.Get(nTemplateID);
    if (!pMonsterConfig) return nullptr;

    auto pMonster = new Monster();
    uint64_t nMonsterID = GenerateObjID(E_OBJ_MONSTER, ConfigInfo::GetInstance());
	pMonster->Init(nMonsterID, pMonsterConfig);

    mMonsterMap.emplace(nMonsterID, pMonster);
    return pMonster;

	SAFE_END_EX(nullptr);
}

Pet* MapRoleMgr::CreatePet(uint16_t nTemplateID)
{
	SAFE_BEGIN_EX
	auto pMonsterConfig = sMonsterConfig.Get(nTemplateID);
	if (!pMonsterConfig) return nullptr;

	auto pPet = new Pet();
	uint64_t nPetID = GenerateObjID(E_OBJ_PET, ConfigInfo::GetInstance());
	pPet->Init(nPetID, pMonsterConfig);
	mPetMap.emplace(nPetID, pPet);
	return pPet;

	SAFE_END_EX(nullptr);
}

PlayerDoplganr *MapRoleMgr::CreatePlayerDoplganr(uint64_t masterGUID)
{
    SAFE_BEGIN_EX;
    uint64_t guid = GenerateObjID(E_OBJ_PLAYER_DOPLGANR, ConfigInfo::GetInstance());
    auto *doplganr = new PlayerDoplganr();
    doplganr->SetGUID(guid);
	doplganr->SetMasterGUID(masterGUID);
    mPlayerDoplganrMap.emplace(guid, doplganr);
    return doplganr;
    SAFE_END_EX(nullptr);
}

Player* MapRoleMgr::FindPlayer(uint64_t id)
{
	if (!mPlayerMap.empty()) {
		auto it = mPlayerMap.find(id);
		if (it != mPlayerMap.end()) {
			return it->second;
		}
	}
	return nullptr;
}

StallDummy* MapRoleMgr::FindStallDummy(uint64_t ownerGuid, uint64_t stallDummyGuid)
{
	if (!mStallDummyMap.empty()) {
		auto it = std::find_if(mStallDummyMap.begin(), mStallDummyMap.end(), [=](auto& pair) {
			return ownerGuid == pair.first.ownerGuid || stallDummyGuid == pair.first.stallDummyGuid;
			});
		if (it != mStallDummyMap.end()) {
			return it->second;
		}
	}
	return nullptr;
}

Player* MapRoleMgr::FindPlayerByToken(uint32_t token)
{
	for (auto& it : mPlayerMap) {
		if (it.second->GetToken() == token) {
			return it.second;
		}
	}
	return nullptr;
}

bool MapRoleMgr::IsPlayerOnline(uint64_t guid)
{
    auto *player = FindPlayer(guid);
    if (!player) return false;
    return player->IsOnline();
}

CLuaObject MapRoleMgr::GetAllOnlinePlayerGuid()
{
	auto playerlist = NewLuaObj();
	int i = 1;
	for (auto it = mPlayerMap.begin(); it != mPlayerMap.end(); ++it)
	{
		playerlist[i] = to_string(it->first);
		++i;
	}
	return playerlist;
}

Player* MapRoleMgr::GetPlayerByUserName(const std::string& name)
{
	for (auto& it : mPlayerMap) {
		if (it.second->GetUserName() == name) {
			return it.second;
		}
	}
	return nullptr;
}

Player* MapRoleMgr::GetPlayerByName(const std::string &name)
{
    for (auto& it : mPlayerMap) {
        if (it.second->GetName() == name) {
            return it.second;
        }
    }
    return nullptr;
}

Npc* MapRoleMgr::FindNpc(uint64_t id)
{
	if (!mNpcMap.empty()) {
		auto it = mNpcMap.find(id);
		if (it != mNpcMap.end()) {
			return it->second;
		}
	}
	return nullptr;
}

Monster* MapRoleMgr::FindMonster(uint64_t id)
{
	if (!mMonsterMap.empty()) {
		auto it = mMonsterMap.find(id);
		if (it != mMonsterMap.end()) {
			return it->second;
		}
	}
	return nullptr;
}

Pet* MapRoleMgr::FindPet(uint64_t id)
{
	if (!mPetMap.empty())
	{
		auto it = mPetMap.find(id);
		if (it != mPetMap.end()){
			return it->second;
		}
	}
	return nullptr;
}

PlayerDoplganr *MapRoleMgr::FindPlayerDoplganr(uint64_t guid)
{
    auto it = mPlayerDoplganrMap.find(guid);
    return it == mPlayerDoplganrMap.end() ? nullptr : it->second;
}

Role* MapRoleMgr::GetRole(const std::string& guid)
{
	SAFE_BEGIN_EX;
    if (guid.empty()) return nullptr;
	uint64_t id = std::stoull(guid);
	return FindRole(id);
	SAFE_END_EX(nullptr);
}

Role* MapRoleMgr::FindRole_Fast(uint64_t id)
{
	if (mTemp_role1 && mTemp_role1->GetGUID() == id)
		return mTemp_role1;
	if (mTemp_role2 && mTemp_role2->GetGUID() == id)
		return mTemp_role2;
	return nullptr;
}

void MapRoleMgr::SetRole_Fast(Role* role)
{
	if (!role)
	{
		return;
	}
	if (role->IsInvalid())
	{
		return;
	}
	if (!mTemp_role1)
	{
		mTemp_role1 = role;
		lastTemp_role = 1;
	}
	else if (!mTemp_role2)
	{
		mTemp_role2 = role;
		lastTemp_role = 2;
	}
	else if (lastTemp_role == 1)
	{
		mTemp_role2 = role;
		lastTemp_role = 2;
	}
	else if (lastTemp_role == 2)
	{
		mTemp_role1 = role;
		lastTemp_role = 1;
	}
}

void MapRoleMgr::RemoveRole_Fast(uint64_t id)
{
	if (mTemp_role1 && mTemp_role1->GetGUID() == id)
		mTemp_role1 = nullptr;
	if (mTemp_role2 && mTemp_role2->GetGUID() == id)
		mTemp_role2 = nullptr;
}

Role* MapRoleMgr::FindRole(uint64_t id)
{
	
    Role* role = FindRole_Fast(id);
	if (role)
		return role;

	if (IS_PLAYER_GUID(id))
		role = FindPlayer(id);
	else if (IS_NPC_GUID(id))
		role = FindNpc(id);
	else if (IS_MONSTER_GUID(id))
		role = FindMonster(id);
	else if (IS_PET_GUID(id))
		role = FindPet(id);
	else if (IS_STALL_DUMMY_GUID(id))
		role = FindStallDummy(0, id);
    else if (IS_PLAYER_DOPLGANR_GUID(id))
        role = FindPlayerDoplganr(id);
	SetRole_Fast(role);
	return role;
}

void MapRoleMgr::RemoveStallDummy(uint64_t id)
{
	auto sdPlayer = FindStallDummy(0, id);
	if (!sdPlayer) return;
	sdPlayer->SetInvalid();
	TRIGGER_EVENT(sdPlayer, trigger_role_destroyed, std::to_string(id));
}

void MapRoleMgr::RemovePlayer(uint64_t id)
{
	auto player = FindPlayer(id);
	if (!player) return;
	player->SetInvalid();
	TRIGGER_EVENT(player, trigger_role_destroyed, std::to_string(id));
}

void MapRoleMgr::RemoveNpc(uint64_t id)
{
	auto npc = FindNpc(id);
	if (!npc) return;
	npc->SetInvalid();
	TRIGGER_EVENT(npc, trigger_role_destroyed, std::to_string(id));
}

void MapRoleMgr::RemoveMonster(uint64_t id)
{
	auto monster = FindMonster(id);
	if (!monster) return;
	monster->SetInvalid();
	TRIGGER_EVENT(monster, trigger_role_destroyed, std::to_string(id));
}

void MapRoleMgr::RemovePet(uint64_t id)
{
	auto pet = FindPet(id);
	if (!pet) return;
	pet->SetInvalid();
	TRIGGER_EVENT(pet, trigger_role_destroyed, std::to_string(id));
}

void MapRoleMgr::RemovePlayerDoplganr(uint64_t guid)
{
    auto *role = FindPlayerDoplganr(guid);
    if (!role) return;
    role->SetInvalid();
    TRIGGER_EVENT(role, trigger_role_destroyed, role->GetGUIDAsString());
}

void MapRoleMgr::RemoveRole(Role* pRole)
{
    if (!pRole) return;

    uint32_t nRoleType = pRole->GetType();
    uint64_t nRoleID = pRole->GetGUID();

    switch (nRoleType) {

    case role_type_player:
        RemovePlayer(nRoleID);
        break;

    case role_type_monster:
        RemoveMonster(nRoleID);
        break;

    case role_type_npc:
        RemoveNpc(nRoleID);
        break;

	case role_type_pet:
		RemovePet(nRoleID);
		break;

	case role_type_stall_dummy:
		RemoveStallDummy(nRoleID);
		break;

    case role_type_player_doplganr:
        RemovePlayerDoplganr(nRoleID);
        break;

    default:
        break;
    }
}

void MapRoleMgr::OnDestroy(Map* map)
{
	DestroyStallDummy(map);
	DestroyPlayer(map);
	DestroyNpc(map);
	DestroyMonster(map);
	DestroyPet(map);
    DestroyPlayerDoplganr(map);
}
void MapRoleMgr::DestroyPlayer(Map* map)
{
	if (!map) return;
	for (auto it = mPlayerMap.begin(); it != mPlayerMap.end(); ++it) {
		if (!it->second) continue;
		if (it->second->GetCurMap() != map) continue;

		it->second->SetInvalid();
		TRIGGER_EVENT(it->second, trigger_role_destroyed, it->second->GetGUIDAsString());
	}
}

void MapRoleMgr::DestroyStallDummy(Map* map)
{
	if (!map) return;
	for (auto it = mStallDummyMap.begin(); it != mStallDummyMap.end(); ++it) {
		if (!it->second) continue;
		if (it->second->GetCurMap() != map) continue;

		it->second->SetInvalid();
		TRIGGER_EVENT(it->second, trigger_role_destroyed, it->second->GetGUIDAsString());
	}
}

void MapRoleMgr::DestroyNpc(Map* map)
{
	if (!map) return;
	for (auto it = mNpcMap.begin(); it != mNpcMap.end(); ++it) {
		if (!it->second) continue;
		if (it->second->GetCurMap() != map) continue;

		it->second->SetInvalid();
		TRIGGER_EVENT(it->second, trigger_role_destroyed, it->second->GetGUIDAsString());
	}
}

void MapRoleMgr::DestroyMonster(Map* map)
{
	if (!map) return;
	for (auto it = mMonsterMap.begin(); it != mMonsterMap.end(); ++it) {
		if (!it->second) continue;
		if (it->second->GetCurMap() != map) continue;

		it->second->SetInvalid();
		TRIGGER_EVENT(it->second, trigger_role_destroyed, it->second->GetGUIDAsString());
	}
}

void MapRoleMgr::DestroyPlayerDoplganr(Map *map)
{
    if (!map) return;
    for (const auto &it : mPlayerDoplganrMap) {
        const auto &role = it.second;
        if (!role || role->GetCurMap() != map) continue;
        role->SetInvalid();
        TRIGGER_EVENT(role, trigger_role_destroyed, role->GetGUIDAsString());
    }
}

void MapRoleMgr::DestroyPet(Map* map)
{
	if (!map)return;
	for (auto it = mPetMap.begin(); it != mPetMap.end(); ++it) {
		if (!it->second)continue;
		if (it->second->GetCurMap() != map)continue;

		it->second->SetInvalid();
		TRIGGER_EVENT(it->second, trigger_role_destroyed, it->second->GetGUIDAsString());
	}
}



void MapRoleMgr::Update(int delta) 
{
	int64_t beginstamp = GetTimeStampMillisecond();
    for (const auto &roleGUID : mRolesToBeRemovedFromNeedUpdateList) {
		mNeedPlayerUpdateRoles.erase(roleGUID);
    }
	for (const auto& roleGUID : mRolesToBeRemovedFromNeedUpdateList) {
		mNeedPetUpdateRoles.erase(roleGUID);
	}
	for (const auto& roleGUID : mRolesToBeRemovedFromNeedUpdateList) {
		mNeedMonUpdateRoles.erase(roleGUID);
	}
	for (const auto& roleGUID : mRolesToBeRemovedFromNeedUpdateList) {
		mNeedOUpdateRoles.erase(roleGUID);
	}
    mRolesToBeRemovedFromNeedUpdateList.clear();
	int64_t endstamp = GetTimeStampMillisecond();
	if (endstamp - beginstamp > 15)
	{
		LOG_ERROR("mRolesToBeRemovedFromNeedUpdateList : %u", endstamp - beginstamp);
	}
	beginstamp = endstamp;

    for (const auto &it : mRolesToBeAddedToNeedUpdateList) {
		switch (it.second->GetType())
		{
		case role_type_player:
			mNeedPlayerUpdateRoles.emplace(it.first, it.second);
			break;
		case role_type_monster:
			mNeedMonUpdateRoles.emplace(it.first, it.second);
			break;
		case role_type_pet:
			mNeedPetUpdateRoles.emplace(it.first, it.second);
			break;
		default:
			mNeedOUpdateRoles.emplace(it.first, it.second);
			break;
		}
    }
    mRolesToBeAddedToNeedUpdateList.clear();

	endstamp = GetTimeStampMillisecond();
	if (endstamp - beginstamp > 15)
	{
		LOG_ERROR("mRolesToBeAddedToNeedUpdateList : %u", endstamp - beginstamp);
	}
	beginstamp = endstamp;

    for (auto it = mNeedPlayerUpdateRoles.begin(); it != mNeedPlayerUpdateRoles.end(); ) {
        auto &role = it->second;
        if (role->IsInvalid()) {
            role->LeaveMap();
			if (role->IsPlayer())
				mPlayerMap.erase(it->first);
			else if (role->IsMonster())
				mMonsterMap.erase(it->first);
			else if (role->IsNpc())
				mNpcMap.erase(it->first);
			else if (role->IsPet())
				mPetMap.erase(it->first);
            else if (role->IsPlayerDoplganr())
                mPlayerDoplganrMap.erase(it->first);
			else if (role->IsStallDummy())
			{
				auto iter = std::find_if(mStallDummyMap.begin(), mStallDummyMap.end(), [=](auto& pair) {
					return it->first == pair.first.stallDummyGuid;
					});
				if (iter != mStallDummyMap.end()) mStallDummyMap.erase(iter);
			}

            SAFE_RELEASE(role);
            it = mNeedPlayerUpdateRoles.erase(it);
            continue;
        }
        role->Update(delta);
        ++it;
    }
	endstamp = GetTimeStampMillisecond();
	if (endstamp - beginstamp > 15)
	{
		LOG_ERROR("mNeedPlayerUpdateRoles : %u", endstamp - beginstamp);
	}
	beginstamp = endstamp;
	for (auto it = mNeedPetUpdateRoles.begin(); it != mNeedPetUpdateRoles.end(); ) {
		auto& role = it->second;
		if (role->IsInvalid()) {
			role->LeaveMap();
			if (role->IsPlayer())
				mPlayerMap.erase(it->first);
			else if (role->IsMonster())
				mMonsterMap.erase(it->first);
			else if (role->IsNpc())
				mNpcMap.erase(it->first);
			else if (role->IsPet())
				mPetMap.erase(it->first);
			else if (role->IsPlayerDoplganr())
				mPlayerDoplganrMap.erase(it->first);
			else if (role->IsStallDummy())
			{
				auto iter = std::find_if(mStallDummyMap.begin(), mStallDummyMap.end(), [=](auto& pair) {
					return it->first == pair.first.stallDummyGuid;
					});
				if (iter != mStallDummyMap.end()) mStallDummyMap.erase(iter);
			}
			SAFE_RELEASE(role);
			it = mNeedPetUpdateRoles.erase(it);
			continue;
		}
		role->Update(delta);
		++it;
	}
	endstamp = GetTimeStampMillisecond();
	if (endstamp - beginstamp > 15)
	{
		LOG_ERROR("mNeedPetUpdateRoles : %u", endstamp - beginstamp);
	}
	beginstamp = endstamp;
	for (auto it = mNeedMonUpdateRoles.begin(); it != mNeedMonUpdateRoles.end(); ) {
		auto& role = it->second;
		if (role->IsInvalid()) {
			role->LeaveMap();
			if (role->IsPlayer())
				mPlayerMap.erase(it->first);
			else if (role->IsMonster())
				mMonsterMap.erase(it->first);
			else if (role->IsNpc())
				mNpcMap.erase(it->first);
			else if (role->IsPet())
				mPetMap.erase(it->first);
			else if (role->IsPlayerDoplganr())
				mPlayerDoplganrMap.erase(it->first);
			else if (role->IsStallDummy())
			{
				auto iter = std::find_if(mStallDummyMap.begin(), mStallDummyMap.end(), [=](auto& pair) {
					return it->first == pair.first.stallDummyGuid;
					});
				if (iter != mStallDummyMap.end()) mStallDummyMap.erase(iter);
			}
			SAFE_RELEASE(role);
			it = mNeedMonUpdateRoles.erase(it);
			continue;
		}
		role->Update(delta);
		++it;
	}
	endstamp = GetTimeStampMillisecond();
	if (endstamp - beginstamp > 15)
	{
		LOG_ERROR("mNeedMonUpdateRoles : %u", endstamp - beginstamp);
	}
	beginstamp = endstamp;

	for (auto it = mNeedOUpdateRoles.begin(); it != mNeedOUpdateRoles.end(); ) {
		auto& role = it->second;
		if (role->IsInvalid()) {
			role->LeaveMap();
			if (role->IsPlayer())
				mPlayerMap.erase(it->first);
			else if (role->IsMonster())
				mMonsterMap.erase(it->first);
			else if (role->IsNpc())
				mNpcMap.erase(it->first);
			else if (role->IsPet())
				mPetMap.erase(it->first);
			else if (role->IsPlayerDoplganr())
				mPlayerDoplganrMap.erase(it->first);
			else if (role->IsStallDummy())
			{
				auto iter = std::find_if(mStallDummyMap.begin(), mStallDummyMap.end(), [=](auto& pair) {
					return it->first == pair.first.stallDummyGuid;
					});
				if (iter != mStallDummyMap.end()) mStallDummyMap.erase(iter);
			}
			SAFE_RELEASE(role);
			it = mNeedOUpdateRoles.erase(it);
			continue;
		}
		role->Update(delta);
		++it;
	}
	endstamp = GetTimeStampMillisecond();
	if (endstamp - beginstamp > 15)
	{
		LOG_ERROR("mNeedOUpdateRoles : %u", endstamp - beginstamp);
	}
	beginstamp = endstamp;

	UpdateImageMap(delta);
}




void MapRoleMgr::DelaySendRoleDisappearNtfToAroundPlayers(uint64_t nObjID)
{
	SAFE_BEGIN;

	auto pTarget = FindRole(nObjID);
    if (!pTarget) return;

    if (!pTarget->IsMonster() && !pTarget->IsPet() && !pTarget->IsPlayerDoplganr())
        return;

	auto global = sGlobalConfig.GetData();
	if (!global) return;

	if (global->CorpseTime == 0) {
		auto pMap = pTarget->GetCurMap();
		if (!pMap) return;
		pMap->RoleLeave(pTarget);
		RemoveRole(pTarget);
		return;
	}

	bool IsDisappear = true;
	TRIGGER_EVENT_RET<bool>(IsDisappear, trigger_monster_disappear_pre_die, std::to_string(pTarget->GetGUID()));
	if (IsDisappear)
	{
		TimerData timer;
		timer.interval = global->CorpseTime;
		timer.loop = false;
		timer.callBack = [=](const TimerData&) {

			auto pRole = FindRole(nObjID);
			if (!pRole) return;

			auto pMap = pRole->GetCurMap();
			if (!pMap) return;

			pMap->RoleLeave(pRole);
			RemoveRole(pRole);
		};

		auto TimerID = ITimeHelper::GetInstance()->AddTimer(timer,true);
		//ITimeHelper::GetInstance()->AddStrData(TimerID, "name", "IsDisappear");
	}

	SAFE_END;
}

void MapRoleMgr::AddToNeedUpdateList(Role *role)
{
    if (!role) return;

    auto guid = role->GetGUID();
    // auto it = mRolesToBeRemovedFromNeedUpdateList.find(guid);
    // if (it != mRolesToBeRemovedFromNeedUpdateList.end()) {          // 同一次循环中先删后加
        // mRolesToBeRemovedFromNeedUpdateList.erase(it);              // 操作抵消
        // return;
    // }

    mRolesToBeAddedToNeedUpdateList.emplace(guid, role);
}

void MapRoleMgr::RemoveFromNeedUpdateList(Role *role)
{
    if (!role) return;

    auto guid = role->GetGUID();
    // auto it = mRolesToBeAddedToNeedUpdateList.find(guid);
    // if (it != mRolesToBeAddedToNeedUpdateList.end()) {              // 同一次循环中先加后删
        // mRolesToBeAddedToNeedUpdateList.erase(it);                  // 操作抵消
        // return;
    // }

    mRolesToBeRemovedFromNeedUpdateList.emplace(guid);
}

uint16_t MapRoleMgr::GetOnlinePlayerCount() const
{
    uint16_t num = 0;
    for (const auto &it : mPlayerMap) {
        const auto *player = it.second;
        if (!player || !player->IsOnline()) continue;
        num += 1;
    }
    return num;
}

uint64_t MapRoleMgr::GetDoplganridByPlayer(uint64_t ownerGuid)
{
	auto it = mPlayerandDoplganrMap.find(ownerGuid);
	if (it != mPlayerandDoplganrMap.end()) {             
		return it->second;
	}
	return 0;
}
void MapRoleMgr::CreateImageByPlayer(uint64_t ownerGuid)
{
	if (MapRoleMgr::GetInstance()->GetDoplganridByPlayer(ownerGuid) > 0)
	{
		return;
	}
	Map* tarMap = MapMgr::GetInstance()->FindMap("mzc");
	if (nullptr == tarMap) {
		return;
	}
	auto* doplganr = MapRoleMgr::GetInstance()->CreatePlayerDoplganr(ownerGuid);
	if (!doplganr) return;
	auto pTarget = FindRole(ownerGuid);
	if (!pTarget) return;
	doplganr->SetName(pTarget->GetName());
	doplganr->SetMasterGUID(ownerGuid);
	doplganr->CloneMaster();
	doplganr->SetMasterGUID(0);
	doplganr->OnEnterMap(tarMap);
	doplganr->SetRolePos(344 - Tools::GenerateRandomInteger<uint16_t>(1, 14), 378 - Tools::GenerateRandomInteger<uint16_t>(1, 18));
	MapRoleMgr::GetInstance()->AddPlayerandDoplganrMap(ownerGuid, doplganr->GetGUID());
	TRIGGER_EVENT(trigger_doplganr_appear, std::to_string(doplganr->GetGUID()));
}

void MapRoleMgr::UpdateImageMap(int delta)
{
	if (GetDoplganrCount() > mMaxImageCount)
	{
		auto it = mPlayerandDoplganrMap.begin();
		if (it != mPlayerandDoplganrMap.end()) {
			RemovePlayerDoplganr(it->second);
			mPlayerandDoplganrMap.erase(it);
		}
	}
}
