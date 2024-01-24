#pragma once

#include "Role.h"
#include "Player.h"
#include "Npc.h"
#include "Monster.h"
#include "Pet.h"
#include <map>
#include <unordered_map>
#include <string>
#include "ProtoMS.h"

class PlayerDoplganr;

struct PlayerStallDummyKey
{
	uint64_t ownerGuid = 0;
	uint64_t stallDummyGuid = 0;
	PlayerStallDummyKey(uint64_t o, uint64_t s) : ownerGuid(o), stallDummyGuid(s) {}
	bool operator<(const PlayerStallDummyKey& key) const
	{
		if (ownerGuid < key.ownerGuid)
			return true;
		if (ownerGuid == key.ownerGuid)
		{
			if (stallDummyGuid < key.stallDummyGuid)
				return true;
		}
		return false;
	}
};
typedef std::map<PlayerStallDummyKey, StallDummy*> StallDummyMap;
typedef std::unordered_map<uint64_t, Player*> PlayerMap;
typedef std::unordered_map<uint64_t, Monster*> MonsterMap;
typedef std::unordered_map<uint64_t, Npc*> NpcMap;
typedef std::unordered_map<uint64_t, Pet*> PetMap;
typedef std::map<uint64_t, PlayerDoplganr *> PlayerDoplganrMap;


class MapRoleMgr
{
	DECL_SINGLETON(MapRoleMgr);

public:
	MapRoleMgr();//最好不要通过构造函数访问对象
	~MapRoleMgr();

public:

	StallDummy* CreateStallDummy(Player* player);
	Player* AddPlayer(uint64_t id);
    Npc* CreateNpc(uint16_t nTemplateID);
    Monster* CreateMonster(uint16_t nTemplateID);
	Pet* CreatePet(uint16_t nTemplateID);
    PlayerDoplganr * CreatePlayerDoplganr(uint64_t masterGUID);

	void RemoveStallDummy(uint64_t id);
	void RemovePlayer(uint64_t id);
	void RemoveNpc(uint64_t id);
	void RemoveMonster(uint64_t id);
	void RemovePet(uint64_t id);
    void RemovePlayerDoplganr(uint64_t guid);
    void RemoveRole(Role *pRole);

	void OnDestroy(Map* map);
	void DestroyPlayer(Map* map);
	void DestroyStallDummy(Map* map);
	void DestroyNpc(Map* map);
	void DestroyPet(Map* map);
	void DestroyMonster(Map* map);
    void DestroyPlayerDoplganr(Map *map);

	Player* GetPlayerByUserName(const std::string& name);
    Player* GetPlayerByName(const std::string &name);
	Player* FindPlayer(uint64_t id);
	Player* FindPlayerByToken(uint32_t token);
    bool    IsPlayerOnline(uint64_t guid);

	CLuaObject GetAllOnlinePlayerGuid();

	StallDummy* FindStallDummy(uint64_t ownerGuid, uint64_t stallDummyGuid);
	Npc* FindNpc(uint64_t id);
	Monster* FindMonster(uint64_t id);
	Pet* FindPet(uint64_t id);
    PlayerDoplganr * FindPlayerDoplganr(uint64_t guid);
    Role* FindRole(uint64_t id);
	Role* FindRole_Fast(uint64_t id);
	void SetRole_Fast(Role* role);
	void RemoveRole_Fast(uint64_t id);
    Role* GetRole(const std::string& guid);

	void DelaySendRoleDisappearNtfToAroundPlayers(uint64_t nObjID);
	void AddPlayerandDoplganrMap(uint64_t ownerGuid, uint64_t DoplganrGuid) {
		mPlayerandDoplganrMap.emplace(ownerGuid, DoplganrGuid); 
	}
	uint64_t GetDoplganridByPlayer(uint64_t ownerGuid);
	void CreateImageByPlayer(uint64_t ownerGuid);
	void UpdateImageMap(int delta);

	//因为map中需要对这些角色进行修改，所以这里不用const reference
	MonsterMap& GetMonsterMap(void) { return mMonsterMap; }
	NpcMap& GetNpcMap(void) { return mNpcMap; }
	PlayerMap& GetPlayerMap(void) { return mPlayerMap; }
	StallDummyMap& GetStallDummyMap(void) { return mStallDummyMap; }
	PetMap& GetPetMap(void) { return mPetMap; }
    PlayerDoplganrMap & GetPlayerDoplganrMap() { return mPlayerDoplganrMap; }

	uint16_t GetStallDummyCount() const { return mStallDummyMap.size(); }
	uint16_t GetPlayerCount() const { return mPlayerMap.size(); }
    uint16_t GetOnlinePlayerCount() const;
	uint16_t GetMonsterCount() const { return mMonsterMap.size(); }
	uint16_t GetNpcCount() const { return mNpcMap.size(); }
	uint16_t GetPetCount() const { return mPetMap.size(); }
    uint16_t GetPlayerDoplganrCount() const { return mPlayerDoplganrMap.size(); }
	uint16_t GetDoplganrCount() const { return mPlayerandDoplganrMap.size(); }

	void Update(int delta);
    const std::string & GetScriptName() { return mScriptName; }

    void AddToNeedUpdateList(Role *role);
    void RemoveFromNeedUpdateList(Role *role);

	void SetMaxImageCount(uint32_t num) {mMaxImageCount = num;}
private:
	StallDummyMap mStallDummyMap;
	PlayerMap mPlayerMap;
	MonsterMap mMonsterMap;
	NpcMap mNpcMap;
	PetMap mPetMap;
    PlayerDoplganrMap mPlayerDoplganrMap;
	std::string mScriptName;
	Role* mTemp_role1 = nullptr;
	Role* mTemp_role2 = nullptr;
	int lastTemp_role = 0;



	std::unordered_map<uint64_t, Role*> mNeedPlayerUpdateRoles;
	std::unordered_map<uint64_t, Role*> mNeedPetUpdateRoles;
	std::unordered_map<uint64_t, Role*> mNeedMonUpdateRoles;
	std::unordered_map<uint64_t, Role*> mNeedOUpdateRoles;


    std::unordered_map<uint64_t, Role *> mRolesToBeAddedToNeedUpdateList;
    std::unordered_set<uint64_t> mRolesToBeRemovedFromNeedUpdateList;
	std::unordered_map<uint64_t, uint64_t> mPlayerandDoplganrMap;
	int mMaxImageCount = 100;
};
