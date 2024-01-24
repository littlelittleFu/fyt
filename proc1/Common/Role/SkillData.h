#pragma once
#include "skill_table.hpp"


class RoleSkill;

class SkillData
{
public:
    SkillData() = default;
    virtual ~SkillData();
	void Init(RoleSkill *roleSkill, uint16_t id, bool active, uint32_t proficiency, DATA::Skill*, std::map<uint16_t, string>&);
	void Update(int delta);
	
	uint16_t GetID() const { return mID; }
	bool IsActive() const { return mActive; }
	void SetActive(uint8_t active) { mActive = active; }

	bool InCD() const { return mInCD; };
	void StartCD();
    uint32_t GetCD() const { return mCDTime; }
	void ClearCD();

    void SetProficiency(uint32_t proficiency) { mProficiency = proficiency; }
    uint32_t GetProficiency() const { return mProficiency; }

    void SetFireTime(uint32_t nFireTime) { mFireTime = nFireTime; }
    uint32_t GetFireTime() const { return mFireTime; }
    void StartFireTimeCountDown();
    void StopFireTimeCountDown();
    bool FireTimeExpired() const;
    bool IsInFireTime() const;

    const std::map<uint16_t, string>& GetSkillCfgModifyMap() const { return mSkillCfgModifyMap; }
    DATA::Skill* GetSkillCfg();
    bool ModifyCfg(DATA::Skill*, const std::pair<uint16_t, string>&);
private:
    void CountDownFireTime(int nDeltaTime);
    bool CheckAndCreateSkillTable(DATA::Skill*);
private:
    RoleSkill  *mRoleSkill          = nullptr;
    uint16_t    mID                 = 0;
    uint8_t     mActive             = 0;
    uint32_t    mProficiency        = 0;
    uint32_t    mCDTime             = 0;
    uint32_t    mCDCur              = 0;

    bool        mInCD               = false;

    uint32_t    mFireTime           = 0;
    uint32_t    mCurFireTime        = 0;
    bool        mCountDownFireTime  = false;

    DATA::Skill* mSkillTable = nullptr;
    std::map<uint16_t, string>    mSkillCfgModifyMap;
};
