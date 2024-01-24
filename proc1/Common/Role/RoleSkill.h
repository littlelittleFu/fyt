#pragma once
#include "RoleAction.h"
#include "SkillData.h"
#include <map>
#include "../Common/DB/skill_table.hpp"

#include <vector>

struct AttackResult {
    uint64_t    actorGUID   = 0;            // 攻击者
    std::string actorName   = "";           // 攻击者名
    uint64_t    targetGUID  = 0;            // 被攻击者
    uint16_t    skillId     = 0;            // 技能

    int32_t     decreaseHP  = 0;            // target扣hp
    int32_t     remainHP    = 0;            // target剩余hp
    int32_t     decreaseMP  = 0;            // target扣mp
    int32_t     remainMP    = 0;            // target剩余mp
    int32_t     type        = 0;            // 伤害类型
};

using AttackResults = std::list<AttackResult>;

using PositionList = std::list<std::pair<uint16_t, uint16_t>>;

class Player;

class RoleSkill : public RoleAction
{
public:
	RoleSkill(Role* master = nullptr);
	~RoleSkill();

public:
	bool Init() override;
	void Update(int32_t delta) override;

public:
	int AddSkill(uint16_t id, bool active, uint32_t proficiency, string cfg = "");
	void RemoveSkill(uint16_t id);
    bool IsSkillExist(uint16_t id);
    bool IsSkillExistByChainID(uint32_t skillChainID);
    std::list<SkillData> &GetSkillList() { return mSkillList; }
    uint16_t GetSkillList(SKILL_INFO *pSkillInfo, uint16_t num);
    std::vector<uint16_t> GetSkillIDsByChainID(uint32_t skillChainID);
    bool SetSkillActive(uint16_t nSkillID, uint8_t active);

    void ApplySkillOnTarget(uint16_t skillID, uint64_t targetGUID, uint16_t clientSN);
    void ApplySkillOnGrid(uint16_t skillID, uint64_t targetGUID, uint16_t x, uint16_t y, uint16_t clientSN, uint8_t extraInfo = 0);

    bool CanApplySkillOnTarget(uint16_t skillID, Role *target);

    static void CalculateHarmData(AttackResult& res, uint32_t round = 1);

    void CaculateHatedValue(uint16_t skillID,uint64_t tarGuid);

    bool IsInCD(uint16_t nSkillID);

    void SetSkillProp(uint16_t skillID, uint16_t propType, const std::string& cfg);
    bool GetSkillProp(uint16_t skillID, uint16_t propType);

    bool AddProficiencyValue(uint16_t skillID, uint32_t value);

    bool SetSkillLevel(uint16_t skillID);
private:
    void ApplySkill(uint16_t skillID, uint64_t targetGUID, uint16_t x, uint16_t y, uint16_t clientSN, uint8_t extraInfo);
    void ApplyBuffOnTarget(uint16_t skillID, uint64_t targetGUID);
    void RemoveBuffFromTarget(uint16_t, uint64_t targetGUID);

    uint16_t BeforeApplySkill(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID);
    void AfterApplySkill(uint16_t skillID , const AttackResults& res);

    void DoApplySkill(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN, uint8_t extraInfo);
    uint16_t DoApplySkill_Trap(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN);
    uint16_t DoApplySkill_Status(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN);
    uint16_t DoApplySkill_Normal(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN, uint8_t extraInfo = 0);
    uint16_t DoApplySkill_Collide(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN);
    uint16_t DoApplySkill_Repel(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN);
    uint16_t DoApplySkill_Fly(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN);
    uint16_t DoApplySkill_Stab(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN);
    uint16_t DoApplySkill_Summon(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN);
    uint16_t DoApplySkill_Doplganr(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN);
    uint16_t DoApplySkill_Direct(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, uint16_t clientSN);

    void OnSkillApplyResult(AttackResults &atkResults);
    void OnSkillApplyResult(AttackResult &atkResult);

    bool CanApplySkillOnTarget_SelfIsPlayer(uint16_t skillID, Role *target);
    bool CanApplySkillOnTarget_SelfIsServant(uint16_t skillID, Role *target);
    bool CanApplySkillOnTarget_SelfIsMonster(uint16_t skillID, Role *target);

public:
    DATA::Skill * GetSkillCfg(uint16_t nSkillID);
    SkillData* GetSkillData(uint16_t nSkillID);

    void AddGrayBuff(uint64_t tarGuid);

private:
    uint16_t ConditionCheck(uint16_t skillID, bool checkCD, bool checkMP);
    uint16_t CheckRoleState(uint16_t skillID);
    uint16_t CheckSkill(const uint16_t nSkillID, bool checkCD);
    uint16_t CheckHPMP(uint16_t nSkillID);
    uint16_t CheckDistance(uint16_t skillID, uint16_t x, uint16_t y);

    uint16_t GetSkillCastTargets(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, AttackResults &atkResults);
    uint16_t GetSkillCastTargets_Friend(uint16_t skillID, uint16_t x, uint16_t y, uint64_t targetGUID, AttackResults &atkResults);

    uint16_t GetSkillCastPositionList(uint16_t skillID, uint16_t x, uint16_t y, PositionList &posList);
    uint16_t GetSkillCastPositionList_Point(uint16_t skillID, uint16_t x, uint16_t y, PositionList &posList);
    uint16_t GetSkillCastPositionList_Line(uint16_t skillID, uint16_t x, uint16_t y, PositionList &posList);
    uint16_t GetSkillCastPositionList_Rect(uint16_t skillID, uint16_t x, uint16_t y, PositionList &posList);
    uint16_t GetSkillCastPositionList_Cust(uint16_t skillID, uint16_t x, uint16_t y, PositionList &posList);

    uint32_t GetTrapSkillExpireTime(uint16_t skillID);

    uint16_t RotateSeq(uint16_t seq, uint8_t by);

    uint16_t GetApplySkillDelayTime(uint16_t skillID, uint16_t x, uint16_t y);
    void StartCD(uint16_t nSkillID);


    void StartFireTimeCountDown(uint16_t nSkillID);
    void StopFireTimeCountDown(uint16_t nSkillID);

    int32_t GetSkillCostAttValue(uint16_t skillID, uint16_t att);

    void SendSpellAck(int32_t ecode, uint16_t skillID, uint16_t clientSN);

    void DecreaseActorHPMP(uint16_t skillID);
    void AddProficiency(uint16_t skillID);


    void StartCastSkillPubCD(uint32_t cdTime);
    bool IsCastSkillInPubCD();
    void UpdateCastSkillPubCD(int32_t delta);

    void AddHateValue(uint32_t skillID,uint64_t tarGuid);

    void AddPetTarget(uint64_t tarGuid);
    void AddFightInfoWhenAttack(uint32_t skillID, uint64_t tarGuid);
    void AddFightInfoWhenBeAttacked(uint32_t skillID, uint64_t ownerGuid, uint64_t actorGuid);
    void AddBackStatus(uint64_t targetGuid);


    void ClearTimeridmap();
    void UpdateTimeridmap();
public:
    static std::map<uint16_t, string> DecodeSkillCfg(std::string cfg);
    static std::string EncodeSkillCfg(const std::map<uint16_t, string>& skillCfg);

protected:
	std::list<SkillData>    mSkillList;
    std::map<unsigned int, int>  mTimeridmap;
    bool mNeedTimerUpdate = false;
    uint32_t                mCastSkillPubCDTime     = 0;        // 施法类技能公共CD
    uint32_t                mCastSkillPubCDCur      = 0;
};
