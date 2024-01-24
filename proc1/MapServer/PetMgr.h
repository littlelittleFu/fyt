#pragma once
#include "Monster.h"
#include "Role.h"
#include "Pet.h"
#include <list>
class PetMgr
{
public:
	PetMgr(Player* player): m_player(player) {};
	~PetMgr() {};

	Pet* PetMonster(DATA::Monster* monsterCfg);
	Pet* PetMonsterByID(uint16_t monsterID);
	Pet* PetMonsterByName(const std::string& monsterName);

	Pet* PetMonsterByIDByLuaTable(uint16_t monsterID, const CLuaObject& luaObj);
	Pet* PetMonsterByNameByLuaTable(const std::string& monsterName, const CLuaObject& luaObj);

	void DestroyPet();
	void DestroyPet(uint64_t petGUID);
	void DestroyPet(const std::string& sPetGUID);

	void UpdatePetPropByLUaTable(Pet* pet,const CLuaObject& luaObj);
	void SetPetActivityStatus(const std::string& guid, uint16_t status);
	void SetPetPickItemStatus(const std::string& guid, bool canPickitem);

	std::list<uint64_t>& GetPetList() { return mPetList; }
    uint32_t GetPetNum() { return mPetList.size(); }

	void UpdatePetList();
	void PetEnterMap();
	void PetLeaveMap(uint64_t petGUID = 0);
    void PetTeleportToMaster();
	void ChangeMasterNameInfo(const std::string& name, ProtoGS_PlayerSetNameNtf& ntf);

private:
	void CheckPetMonsterNeedUpdate();
private:
	Player* m_player;
	std::list<uint64_t> mPetList;
};