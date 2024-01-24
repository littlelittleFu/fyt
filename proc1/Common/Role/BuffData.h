#pragma once

#include "buff_table.hpp"
#include "ITimeHelper.h"

using AttrMap = std::map<int32_t, std::vector<int32_t>>;
struct BuffDataInfo
{
    BuffDataInfo(std::string attrStr)
    {
        m_Attr.clear();
		strcpy_s(m_customAttr, attrStr);
        SPLIT_STRING_KEY_MULTIPLE_VALUE(attrStr, "|", ";", 3, m_Attr);
    }
    uint16_t m_stack = 0;               // 堆叠次数
    uint64_t m_nDBIndex = 0;            // 改为guid由ms生成,因为db中的idx没有返回ms和cs不知道其值
    int64_t m_nTimestamp = 0;          // 添加该buff的起始时间戳(ms)
    int32_t m_nTimeLeft = 0;            // 剩余时间(ms)
    char m_customAttr[256] = { 0 };      // 自定义属性
    AttrMap m_Attr;                     /// 属性
    // 临时属性
    uint32_t  m_tempLeftTime = 0;            // 添加剩余时间
};
struct BuffActorDataInfo
{
    uint64_t m_nActorID = 0;
    std::string m_sActorName = "";
    uint8_t m_nActorJob = 0;
    uint32_t m_nActorLevel = 0;
    uint16_t m_nActorSkill = 0;
};
class RoleBuff;
class BuffData
{
public:
    BuffData(RoleBuff* roleBuff, DATA::Buff* cfg);
    virtual ~BuffData();
    bool ApplyBuff(int32_t stack = 1);
    bool ApplyBuffFromeCache(int32_t stack = 1);
    bool Resume(uint32_t leftTime);
    
    virtual bool Pause();
    virtual bool Resume() = 0;
    virtual bool Term();
    virtual void UpdateLeftTime() = 0;
    virtual uint32_t GetLeftTime() = 0;
    virtual uint32_t GetLeftTimeDB() = 0;

    bool ResetTimer();
    bool StackTimer();

    const BuffActorDataInfo& GetBuffActorDataInfo() { return m_buffActorDataInfo; }
    const BuffDataInfo& GetBuffDataInfo() { return m_buffDataInfo; }
    void SetBuffActorDataInfo(const BuffActorDataInfo& a) { m_buffActorDataInfo = a; }
    void SetBuffDataInfo(const BuffDataInfo& a) { m_buffDataInfo = a;}
    void SetBuffDataAttr(const BuffDataInfo& a);
    void SetBuffDataTempLeftTime(const BuffDataInfo& a);
    uint16_t GetBuffID() { return m_buffID; }
    DATA::Buff *GetBuffConfig() { return sBuffConfig.Get(m_buffID); }
    std::list<std::map<int32_t, int32_t>>& GetAttrStackList() { return m_attrStackList; }
    const AttrMap * GetBuffAttrCfg();

    void UpdatePropStackReocrd(std::map<int32_t, int32_t>& attrMap);
    void UpdateStack(int32_t diff);

    bool IsPaused() { return m_bPaused; }
    bool HasExpired() { return m_bHasExpired; }
    bool IsTerminated() { return m_bTerminated; }
    bool IsInvalid();

    bool GenerateBuffInfo(BUFF_INFO& pBuffInfo);
    bool GenerateBuffInfoDB(BUFF_INFO_DB& pBuffInfo);

    void OnAddBuff();
    void OnUpdateBuff();
protected:
    void StartExpireTimer(uint32_t nExpireTime);
    void StopExpireTimer();
    void OnExpireTimer();

    void StartPeriodTimer(uint32_t nPeriodTime);
    void StopPeriodTimer();
    void OnPeriodTimer();

    uint32_t GetDuration();
    void UpdateAndNotify();
protected:
    RoleBuff* m_roleBuff = nullptr;
    uint16_t m_buffID = 0;
    BuffDataInfo m_buffDataInfo;
    BuffActorDataInfo m_buffActorDataInfo;

    bool m_bForervered = false;
    bool m_bHasExpired = false;
    bool m_bPaused = true ;
    bool m_bTerminated = false;

    // 定时器
    uint32_t m_nPeriodTimerID = 0;      // 周期定期器
    uint32_t m_nExpireTimerID = 0;      // 到期定时器

    std::list<std::map<int32_t, int32_t>>  m_attrStackList;
};
using UPBuffData = std::shared_ptr<BuffData>;
using UPBuffDataAry = std::list<UPBuffData>;
using UPBuffDataAryMap = std::map<uint16_t, UPBuffDataAry>; // key:组id

// 绝对时间buff
class AsbTimeBuffData : public BuffData
{
public:
    AsbTimeBuffData(RoleBuff* roleBuff, DATA::Buff* cfg) : BuffData(roleBuff, cfg){}
    virtual bool Pause();
    virtual bool Resume();
    virtual bool Term();
    virtual void UpdateLeftTime() {}
    virtual uint32_t GetLeftTime();
    virtual uint32_t GetLeftTimeDB();
};
// 相对时间buff
class RelaTimeBuffData : public BuffData
{
public:
    RelaTimeBuffData(RoleBuff* roleBuff, DATA::Buff* cfg) : BuffData(roleBuff, cfg) {}
    virtual bool Pause();
    virtual bool Resume();
    virtual bool Term();
    virtual void UpdateLeftTime();
    virtual uint32_t GetLeftTime();
    virtual uint32_t GetLeftTimeDB();
};