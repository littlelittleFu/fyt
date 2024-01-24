#pragma once
#include "Types.h"

class Session;
class Player;
class Monster;
class SummonMonsterMgr
{
    friend Player;
public:
    SummonMonsterMgr(Player* player);
    virtual ~SummonMonsterMgr();

    std::list<uint64_t>& GetSummonList() { return mSummonList; };
    
    Monster* SummonMonster(DATA::Monster* monsterCfg);
    Monster* SummonMonsterByID(uint16_t monsterID);
    Monster* SummonMonsterByName(const std::string& monsterName);
    void DestroySummonMonster(uint64_t monsterGUID);
    void DestroySummonMonster(const std::string& sMonsterGUID);
    Monster* GetSummonMonster(uint16_t nTemplateID);

    void UpdateSummonList();
    void SummonMonsterEnterMap();
    void SummonMonsterLeaveMap(uint64_t monsterGUID = 0);
    void DestroySummonMonster(bool destroySummonMonster = true);
    void SummonMonsterTeleportToMaster();
    void ChangeMasterNameInfo(const std::string& name, ProtoGS_PlayerSetNameNtf& ntf);

private:
    void CheckSummonMonsterNeedUpdate();

protected:
    Player* m_player;
    std::list<uint64_t> mSummonList;
};
