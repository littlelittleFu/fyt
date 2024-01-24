#pragma once
#include<map>
#include "Role.h"
#include "ProtoMS.h"
#include "MonsterAI.h"
#include "MonsterAI_Type1.h"
#include "MonsterAI_Type2.h"
#include "MonsterAI_Type3.h"
#include "MonsterAI_Type4.h"
#include "MonsterAI_Type5.h"
#include "FightInfoMgr.h"

#define MAX_HATED_VALUE 100           //最大仇恨值
#define DECREASE_PERCENTAGE 0.7       //除仇恨值刷新比例
class Player;
class PetAI;

class Monster : public Role
{
public:
	Monster();
	virtual ~Monster();

public:

    void Init(uint64_t guid, DATA::Monster* pConfig);
    virtual void Update(int delta) override;
    virtual bool TargetCanSelect(Role* tar) override;
    bool CheckTakeGrid(uint16_t x, uint16_t y) override;
	void SetScriptName(const std::string& scriptName) override;

    void OnRoleEnter(Role *role) override;
    void OnRoleLeave(Role *role) override;
    void OnRoleExit(Role *role) override;

    Player* GetMaster();
    MonsterAI* GetAIMonster() { return mMonsterAI_ptr; };
    virtual PetAI* GetAIPet() { return nullptr; };
    DATA::Monster* GetConfig() { return sMonsterConfig.Get(mMonsterTemplateID); }
    uint16_t GetTemplateID() { return mMonsterTemplateID; }

    void SetMasterName(std::string sMasterName) { m_sMasterName = sMasterName; }
    const std::string& GetMasterName() { return m_sMasterName; }

    void SetMonsterNameColor(std::string nameColor);
    const std::string& GetMonsterNameColor() { return mMonsterNameColor; }

    void SetMasterGUID(uint64_t guid);
    uint64_t GetMasterGUID() { return mMasterGUID; }
    std::string GetMasterGUIDAsString() { return std::to_string(mMasterGUID); }

    uint64_t GetBelongPlayerID() { return mExclusiveRole; }
    std::string GetBelongPlayerIDAsString() { return std::to_string(mExclusiveRole); }

    void MakeMonsterAppearNtfData(ProtoMS_MonsterAppearNtf6& ntf);

    void SetBornPos(uint16_t posX, uint16_t posY) { if (mMonsterAI_ptr) mMonsterAI_ptr->SetBornPos(posX, posY); }
    void SetTmpStayPos(uint16_t posX, uint16_t posY) { if (mMonsterAI_ptr) mMonsterAI_ptr->SetTmpStayPos(posX, posY); }
    void SetRebornTime(uint32_t rebornTime) { mRebornTime = rebornTime; }
    void SetRebornRegion(uint16_t left, uint16_t top, uint16_t width, uint16_t height);
    void SetRebornDir(uint8_t dir) { mRebornDir = dir; }
    void SetWayFinding(bool wayFinding) { m_WayFinding = wayFinding; }
    bool IsWayFinding() { return m_WayFinding; }
    bool IsPursureStatus() { return mMonsterAI_ptr ? mMonsterAI_ptr->IsPursureAttackingStatus() : false; }
    void RemoveMonster(bool appearBody = true);
    void SetExistTime(uint32_t time);
    void RemoveExistTimeWhenDie();
    void SetBackStatus();

    virtual void OnRoleBeAttacked(uint64_t attackerGUID) override;
    virtual void OnRoleDie(uint64_t killerGUID) override;

public:
    bool JumpMap(uint16_t x, uint16_t y);
    virtual bool JumpMap(Map * tarMap, uint16_t x, uint16_t y)override;
    void CalcDropItems(uint64_t killerGUID);
    bool IsTreasureMonster();
    bool IsBiaoChe() override;
    bool IsInSameTeam(Role *role) override;
    bool IsInSameGuild(Role *role) override;
    bool IsInSameCamp(Role *role) override;

protected:
    void AddPlayerExp();
    void AddToQuestAchieve();
    void UpdateExclusiveRole(int delta);
    void UpdateAliveStateByOwner();
    void HandleReborn();

    //new AI  and hated sys
public:
    std::map<uint64_t, Hated_Value>& GetHateValueMap() { return HatedVauleMap; }
    CLuaObject GetHateValueMapToLua();

    bool IsEmptyHateValueMap();
    bool IsTarInHateValueMap(uint64_t tarGuid);
    void AddHatedValue(uint64_t guid, uint32_t hatevalue);
    void DeleteMaxHateValue(uint64_t guid);
    void DecreaseHateValue();
    virtual void ClearInvalidHateValue();

    Role* GetMaxHatedValueRole();
    Player* GetMaxHatedValueRedNameRole();

    void UpdateBossInfoWhenDie();
    void UpdateBossInfoWhenGen(DATA::Monster*cfg, uint64_t lastGUID = 0);

protected:
    bool NeedMonsterAI(DATA::Monster *pConfig);
    MonsterAI* CreateMonsterAI(Monster* monster, DATA::Monster* pConfig);
    std::vector<Player*> GetBenefitPlayers();

    void CheckAINeedUpdate(Role *role, bool enter);
    void CheckAINeedUpdate(int delta);

protected:

    bool m_WayFinding               = true;
    uint64_t mMasterGUID            = 0;
    uint16_t mMonsterTemplateID     = 0;
    std::string m_sMasterName       = "";
    uint32_t mMonsterExistTimerID   = 0;
    std::string mMonsterNameColor;

    std::map<uint64_t, Hated_Value> HatedVauleMap;


private:
    MonsterAI* mMonsterAI_ptr = nullptr;

    //专属角色，被专属角色杀死后掉落的物品只有专属角色和其队友可以拾取
    uint64_t mExclusiveRole = 0;
    uint64_t mExclusiveRoleTeam = 0;
    int mExpireTime = 0;

    uint32_t mRebornTime            = 0;
    uint16_t mRebornRegionLeft      = 0;
    uint16_t mRebornRegionTop       = 0;
    uint16_t mRebornRegionWidth     = 0;
    uint16_t mRebornRegionHeight    = 0;
    uint8_t  mRebornDir             = 0;

    std::set<uint64_t> mAroundPlayers;      // 普通怪物周围的玩家，有主人的怪物为空
    uint32_t mCheckAINeedUpdateTimeCounter = 0;
    bool mNeedEnterMasterInDifferentMapEvent = true;
    bool mNeedEnterMasterLogoutEvent = true;


    /// old var and func start
private:
    uint8_t  mSummonMonsterType = 0;

public:
    bool IsSummonMonster() { return (mSummonMonsterType != 0); }
    void SetSummonMonsterType(uint8_t type) { mSummonMonsterType = type; };
    uint8_t GetSummonMonsterType() { return mSummonMonsterType; }
    void SetAIState(uint16_t state) { mMonsterAI_ptr->SetAIState(state); }
    uint16_t GetAIState() { return mMonsterAI_ptr->GetAIState(); }
    void TeleportToMaster();
};
