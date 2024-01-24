#pragma once

#include <list>
#include "RoleAction.h"
#include "BuffData.h"


class RoleBuff : public RoleAction
{
    friend BuffData;
public:
    RoleBuff(Role* master = nullptr);
    ~RoleBuff();

    virtual bool Init() override;
    virtual void Update(int32_t delta) override;

    uint16_t GetInUseBuffInfo(std::list<BUFF_INFO>& list);
    uint16_t GetAllBuffInfo(std::list<BUFF_INFO_DB>& list,bool beSave = true);
    bool AddBuffFromCache(const BUFF_INFO_DB *pBuffInfo);
    std::vector<uint16_t> GetValidBuffIDList();

private:
    bool AddBuffFromCache(const BUFF_INFO_DB& pBuffInfo);
public:
    bool AddBuffByRole(uint16_t nBuffID, Role *pActor, uint16_t nSkillID, const std::string& attrStr, uint32_t time);


    UPBuffData FindBuff(uint16_t nBuffID, uint64_t nActorID);
    UPBuffData FindBuff(uint16_t nBuffID);
    UPBuffData FindBuffByGroupID(uint16_t buffGroupID);
    bool BuffExistByGroupID(uint16_t buffGroupID);
    bool BuffExist(uint16_t nBuffID);
    bool BuffExist(uint16_t nBuffID, uint64_t nActorID);
    bool RemoveBuff(uint16_t nBuffID);
    bool RemoveBuff(uint16_t nBuffID, uint64_t nActorID);

    void PauseBuff();
    void PauseBuff(uint16_t nBuffID);
    void ResumeBuff();
    void ResumeBuff(uint16_t nBuffID);

    int64_t GetBuffLeftTime(uint16_t buffID);
    uint16_t GetBuffStack(uint16_t buffID);
    void UpdateBuffStack(uint16_t buffID, int16_t diff);
    std::string GetBuffActorGuid(uint16_t buffID);
    const std::string & GetBuffActorName(const std::string& actorGuid, uint16_t buffID);

    uint8_t     GetBuffActorJob(const std::string& actorGuid, uint16_t buffID);
    uint32_t    GetBuffActorLevel(const std::string& actorGuid, uint16_t buffID);
    uint16_t    GetBuffActorSkill(const std::string& actorGuid, uint16_t buffID);

    void OnRoleDead();
    void OnRoleMove();
private:
    UPBuffData DoAddBuffByRole(uint16_t nBuffID, const BuffDataInfo& buffInfo, const BuffActorDataInfo& actorInfo);

    void OnModPropWhenUpdateStack(BuffData* upBuffData, bool beAdd);
    void OnModPropWhenRemoveBuff(BuffData* upBuffData);
    void OnModPropWhenPeriodBuff(BuffData* upBuffData);
    // 更新hp,mp
    void ModHM(BuffData* upBuffData, int32_t deltaHP, int32_t deltaMP);
    // 属性额外增量
    int32_t GetExtraProp(int32_t coff, int32_t attrType);
    // reverse=true减属性,否则加属性
    void ModRoleProp(BuffData* upBuffData, bool bePeriod, bool beAdd, uint16_t stackDiff = 0);
    bool Check(uint16_t nBuffID, const BuffActorDataInfo& actorInfo);
    //////////////////////
private:
    void UpdateInlineBuffData(UPBuffData& buffData, const BuffDataInfo& buffInfo, const BuffActorDataInfo& actorInfo, bool beSelf);
    UPBuffData AddNewBuffData(uint16_t nBuffID, const BuffDataInfo& buffInfo, const BuffActorDataInfo& actorInfo);

    void IgnoreBuffData(UPBuffData& buffData, bool beSelf);
    void SwapBuffDataByTimestamp(UPBuffData& buffData,  bool beSelf);
    void SwapBuffDataByLevel(UPBuffData& buffData, bool beSelf);
    void FlushBuffData_DurationAndStack(UPBuffData& buffData, bool beSelf);
    void FlushBuffData_Duration(UPBuffData& buffData, bool beSelf);
    void RemoveBuffGroup(uint16_t groupId);

    // 隐身效果
    void AddInvisibleEffectByAttr(UPBuffData& buffData, Role*actor);

    UPBuffData CreateBuffData(uint16_t buffid);
    bool IsAllInvalid(uint32_t groupId);
private:
    UPBuffDataAryMap m_BuffDataAry;
    std::list<BUFF_INFO_DB> m_buffInfoDBList;
    uint32_t curTime = 0;
};
