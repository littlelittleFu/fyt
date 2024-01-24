#include "stdafx.h"
#include "SkillData.h"

SkillData::~SkillData()
{
    if (mSkillTable)
    {
        SAFE_RELEASE(mSkillTable);
    }
    mSkillCfgModifyMap.clear();
}

void SkillData::Init(RoleSkill *roleSkill, uint16_t id, bool active, uint32_t proficiency, DATA::Skill* skillTable, std::map<uint16_t, string>& skillCfg)
{
    if (!skillTable) return;
    /*
    // 配置文件会中途重载,代码里不能有指向配置的缓存指针
    else
    {
        mSkillTable = skillTable;
    }
    */
    if (mSkillTable) skillTable = mSkillTable;
    mRoleSkill = roleSkill;
    mID = id;
    mActive = active;
    mProficiency = proficiency;
    mCDTime = skillTable->CD;

    if (!skillCfg.empty())
    {
        for (const auto& cfg : skillCfg)
        {
            ModifyCfg(skillTable, cfg);
        }
    }
}

void SkillData::Update(int delta)
{
    CountDownFireTime(delta);

	if (!mInCD) {
		return;
	}

	if (mCDTime == 0) {
		return;
	}

	mCDCur += delta;
	if (mCDCur >= mCDTime) {
		mInCD = false;
		mCDCur = 0;
	}
}

void SkillData::StartCD()
{
    if (mCDTime == 0) return;
    mInCD = true;
    mCDCur = 0;
    if (mRoleSkill) mRoleSkill->SetNeedUpdate(skill_need_update_flag);
}

void SkillData::ClearCD()
{
	mInCD = false;
	mCDCur = 0;
}

void SkillData::StartFireTimeCountDown()
{
    mCurFireTime = 0;
    mCountDownFireTime = true;
    if (mRoleSkill) mRoleSkill->SetNeedUpdate(skill_need_update_flag);
}

void SkillData::StopFireTimeCountDown()
{
    mCurFireTime = 0;
    mCountDownFireTime = false;
}

bool SkillData::FireTimeExpired() const
{
    return mFireTime && mCurFireTime >= mFireTime;
}

bool SkillData::IsInFireTime() const
{
    return mCountDownFireTime;
}

DATA::Skill* SkillData::GetSkillCfg()
{
    return mSkillTable ? mSkillTable : sSkillConfig.Get(mID);
}

void SkillData::CountDownFireTime(int nDeltaTime)
{
    if (!mCountDownFireTime) return;

    mCurFireTime += nDeltaTime;
    if (mCurFireTime < mFireTime) return;

    mCountDownFireTime = false;
}

bool SkillData::ModifyCfg(DATA::Skill* skillTable, const std::pair<uint16_t, string>& cfg)
{
    if (!skillTable) return false;
    if (!::CanModifySkillProp(cfg.first)) return false;
    if (!CheckAndCreateSkillTable(skillTable)) return false;
    mSkillCfgModifyMap[cfg.first] = cfg.second.c_str();
    switch (cfg.first)
    {
    case SKILL_PROP_CD: 
        mSkillTable->CD = atoi(cfg.second.c_str());
        mCDTime = mSkillTable->CD;
        break;
    case SKILL_PROP_MAGICID:
        mSkillTable->MagicID = atoi(cfg.second.c_str());
        break;
    case SKILL_PROP_RANGETYPE:
        mSkillTable->RangeType = atoi(cfg.second.c_str());
        break;
    case SKILL_PROP_RANGEPARAM:
        mSkillTable->RangeParam = atoi(cfg.second.c_str());
        break;
    case SKILL_PROP_CUSTOMSHAPE:
        sSkillConfig.FillData_CustomShape(mSkillTable, cfg.second);
        break;
    case SKILL_PROP_CASTDISTANCE:
        mSkillTable->CastDistance = atoi(cfg.second.c_str());
        break;
    case SKILL_PROP_LEVELCOMPARE:
        mSkillTable->LevelCompare = atoi(cfg.second.c_str());
        break;
    case SKILL_PROP_ATTACHEDBUFF:
        sSkillConfig.FillData_AttachedBuff(mSkillTable, cfg.second);
        break;
    case SKILL_PROP_SUMMONPARAMS:
        sSkillConfig.FillData_SummonParams(mSkillTable, cfg.second);
        break;
    }
    return true;
}

bool SkillData::CheckAndCreateSkillTable(DATA::Skill* skillTable)
{
    if (!mSkillTable)
    {
        mSkillTable = new DATA::Skill();
        *mSkillTable = *skillTable;
    }
    return mSkillTable != nullptr;
}