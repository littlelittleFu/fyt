#include "stdafx.h"
#include "BuffData.h"

BuffData::BuffData(RoleBuff* roleBuff, DATA::Buff* cfg) : m_roleBuff(roleBuff), m_buffDataInfo("")
{
    m_buffDataInfo.m_nDBIndex = GenerateObjID(E_OBJ_BUFF, ConfigInfo::GetInstance());
    m_attrStackList.clear();

    if (cfg) m_buffID = cfg->Id;   
}

BuffData::~BuffData()
{
    StopExpireTimer();
    StopPeriodTimer();
}

bool BuffData::ApplyBuff(int32_t stack)
{
    const auto *cfg = GetBuffConfig();
    if (!cfg) return false;

    m_buffDataInfo.m_nTimestamp = GetTimeStampMillisecond();
    m_buffDataInfo.m_nTimeLeft = GetDuration();

    bool ret = Resume();
    if (ret)
    {
        UpdateStack(stack);
        OnAddBuff();
        return true;
    }
    return false;
}

bool BuffData::ApplyBuffFromeCache(int32_t stack)
{
    const auto *cfg = GetBuffConfig();
    if (!cfg) return false;

    if (cfg->TimeType == BTT_RELA)
    {
        m_buffDataInfo.m_nTimestamp = GetTimeStampMillisecond();
    }
    if (0 == m_buffDataInfo.m_nTimeLeft)
    {
        m_bForervered = true;
    }

    bool ret = Resume();
    if (ret)
    {
        UpdateStack(stack);
        OnAddBuff();
        return true;
    }
    return false;
}

bool BuffData::Resume(uint32_t leftTime)
{
    const auto *cfg = GetBuffConfig();
    if (!cfg) return false;

    StartExpireTimer(leftTime);
    StartPeriodTimer(cfg->Interval);
    m_bPaused = false;

    return true;
}

bool BuffData::Pause()
{
    if (IsInvalid()) return true;

    StopExpireTimer();
    StopPeriodTimer();
    m_bPaused = true;

    return true;
}

bool BuffData::Term()
{
    if (IsInvalid()) return true;

    StopExpireTimer();
    StopPeriodTimer();
    m_bTerminated = true;

    UpdateAndNotify();
    return true;
}

bool BuffData::ResetTimer()
{
    if (!Pause()) return false;
    m_buffDataInfo.m_nTimestamp = GetTimeStampMillisecond();
    m_buffDataInfo.m_nTimeLeft = GetDuration();
    return Resume();
}

bool BuffData::StackTimer()
{
    if (!Pause()) return false;
    uint64_t lt = GetDuration();
    lt += m_buffDataInfo.m_nTimeLeft;
    m_buffDataInfo.m_nTimeLeft = (lt > INT32_MAX ? INT32_MAX : lt);
    return Resume();
}

bool BuffData::IsInvalid()
{
    return HasExpired() || IsTerminated() || GetBuffConfig() == nullptr;
}

void BuffData::OnAddBuff()
{
    if (!m_roleBuff) return;
    auto master = m_roleBuff->GetMaster();
    if (!master) return;

    BUFF_INFO pBuffInfo;
    if (GenerateBuffInfo(pBuffInfo))
    {
        master->OnAddBuff(pBuffInfo, GetBuffActorDataInfo().m_nActorSkill);
    }
}

void BuffData::OnUpdateBuff()
{
    if (!m_roleBuff) return;
    auto master = m_roleBuff->GetMaster();
    if (!master) return;

    BUFF_INFO pBuffInfo;
    if (GenerateBuffInfo(pBuffInfo))
    {
        master->OnUpdateBuff(pBuffInfo, GetBuffActorDataInfo().m_nActorSkill);
    }
}

void BuffData::StartExpireTimer(uint32_t nExpireTime)
{
    // 永久不设置过期时间
    if (nExpireTime == 0) return;

    auto callback = [=](const TimerData &) {
        OnExpireTimer();
    };

    m_nExpireTimerID = ITimeHelper::GetInstance()->AddTimer(nExpireTime, false, callback);
    //ITimeHelper::GetInstance()->AddStrData(m_nExpireTimerID, "name", "StartExpireTimer");
}

void BuffData::StopExpireTimer()
{
    if (m_nExpireTimerID == 0) return;
    ITimeHelper::GetInstance()->RemoveTimer(m_nExpireTimerID);
    m_nExpireTimerID = 0;
}

void BuffData::StartPeriodTimer(uint32_t nPeriodTime)
{
    if (nPeriodTime == 0) return;

    auto callback = [=](const TimerData &) {
        OnPeriodTimer();
    };
    if (m_nPeriodTimerID > 0)
        ITimeHelper::GetInstance()->RemoveTimer(m_nPeriodTimerID);
    m_nPeriodTimerID = ITimeHelper::GetInstance()->AddTimer(nPeriodTime, true, callback);
    //ITimeHelper::GetInstance()->AddStrData(m_nPeriodTimerID, "name", "StartPeriodTimer");
}

void BuffData::StopPeriodTimer()
{
    if (m_nPeriodTimerID == 0) return;
    ITimeHelper::GetInstance()->RemoveTimer(m_nPeriodTimerID);
    m_nPeriodTimerID = 0;
}

void BuffData::OnExpireTimer()
{
    if (IsInvalid()) return;

    StopExpireTimer();
    StopPeriodTimer();
    m_bHasExpired = true;

    UpdateAndNotify();
}

void BuffData::OnPeriodTimer()
{
    if (IsInvalid()) return;
    if (!m_roleBuff) return;
    m_roleBuff->OnModPropWhenPeriodBuff(this);
    auto master = m_roleBuff->GetMaster();
    if (!master) return;
    TRIGGER_EVENT(master, trigger_apply_buff, master->GetGUIDAsString(), GetBuffID(),
        std::to_string(m_buffActorDataInfo.m_nActorID));
}

void BuffData::SetBuffDataAttr(const BuffDataInfo& a)
{
	strcpy_s(m_buffDataInfo.m_customAttr, _countof(m_buffDataInfo.m_customAttr), a.m_customAttr);
    m_buffDataInfo.m_Attr = a.m_Attr;
}

void BuffData::SetBuffDataTempLeftTime(const BuffDataInfo& a)
{
    m_buffDataInfo.m_tempLeftTime = a.m_tempLeftTime;
}

const AttrMap * BuffData::GetBuffAttrCfg()
{
    AttrMap* attrCfg = nullptr;
    // 走自定义
    if (strlen(m_buffDataInfo.m_customAttr))
    {
        attrCfg = &m_buffDataInfo.m_Attr;
    }
    else// 走配置
    {
        auto *cfg = GetBuffConfig();
        if (cfg) attrCfg = &cfg->Attr;
    }
    return attrCfg;
}

void BuffData::UpdatePropStackReocrd(std::map<int32_t, int32_t>& map)
{
    map.erase(role_hp);
    map.erase(role_mp);
    m_attrStackList.push_back(std::move(map));
}

void BuffData::UpdateStack(int32_t diff)
{
    const auto *cfg = GetBuffConfig();
    if (!cfg) return;
    if (!m_roleBuff) return;

    if (diff > 0)
    {
        int32_t left = cfg->Stack - m_buffDataInfo.m_stack;
        diff = std::min<int32_t>(left, diff);
        if (diff <= 0) return;
        m_buffDataInfo.m_stack += diff;
        for (int32_t i = 0; i < diff; ++i)
        {
            m_roleBuff->OnModPropWhenUpdateStack(this, true);
        }
    }
    else if (diff < 0)
    {
        int32_t left = m_buffDataInfo.m_stack;
        diff = std::min<int32_t>(left, std::abs(diff));
        if (diff <= 0) return;
        m_buffDataInfo.m_stack -= diff;
        for (int32_t i = 0; i < diff; ++i)
        {
            m_roleBuff->OnModPropWhenUpdateStack(this, false);
        }
    }
}

bool BuffData::GenerateBuffInfo(BUFF_INFO& pBuffInfo)
{
    uint32_t leftTime = GetLeftTime();
    if (IsInvalid()) return false;

    pBuffInfo.id = GetBuffID();
    pBuffInfo.stack = GetBuffDataInfo().m_stack;
    pBuffInfo.life = leftTime;
    pBuffInfo.host = GetBuffActorDataInfo().m_nActorID;

    return true;
}

bool BuffData::GenerateBuffInfoDB(BUFF_INFO_DB& pBuffInfo)
{
    uint32_t leftTime = GetLeftTimeDB();
    if (IsInvalid()) return false;

    pBuffInfo.index = GetBuffDataInfo().m_nDBIndex;
    pBuffInfo.buffid = GetBuffID();
    pBuffInfo.timeleft = leftTime;
    pBuffInfo.timestamp = GetBuffDataInfo().m_nTimestamp;
    pBuffInfo.actor_id = GetBuffActorDataInfo().m_nActorID;
    strcpy_s(pBuffInfo.actor_name, _countof(pBuffInfo.actor_name), GetBuffActorDataInfo().m_sActorName.c_str());
    pBuffInfo.actor_job = GetBuffActorDataInfo().m_nActorJob;
    pBuffInfo.actor_level = GetBuffActorDataInfo().m_nActorLevel;
    pBuffInfo.actor_skill = GetBuffActorDataInfo().m_nActorSkill;
    pBuffInfo.stack = GetBuffDataInfo().m_stack;
    std::string customAttr(GetBuffDataInfo().m_customAttr);
    if (!customAttr.empty())
    {
		strcpy_s(pBuffInfo.attr, customAttr);
    }

    return true;
}

uint32_t BuffData::GetDuration()
{
    if (IsInvalid()) return 0;
    if (!m_roleBuff) return 0;

    // 优先使用自定义时间
    uint32_t curDur = m_buffDataInfo.m_tempLeftTime;
    m_buffDataInfo.m_tempLeftTime = 0;
    if (m_bForervered) return 0;
    if (curDur) return curDur;

    const auto *cfg = GetBuffConfig();
    if (!cfg) return 0;

    int32_t coff = cfg->TimeFactor;
    DATA::Skill* skillCfg = nullptr;
    auto actor = MapRoleMgr::GetInstance()->FindRole(m_buffActorDataInfo.m_nActorID);
    if (actor && actor->GetRoleSkill())
    {
        skillCfg = actor->GetRoleSkill()->GetSkillCfg(m_buffActorDataInfo.m_nActorSkill);
    }
    else
    {
        skillCfg = sSkillConfig.Get(m_buffActorDataInfo.m_nActorSkill);
    }
    int32_t hurtType = 0;
    uint16_t buffId = GetBuffID();
    if (skillCfg)
    {
        hurtType = skillCfg->HurtType;
        auto iter = std::find_if(skillCfg->AttachedBuff.begin(), skillCfg->AttachedBuff.begin(), [buffId](const decltype(skillCfg->AttachedBuff)::value_type& a) {
            return a.BuffID == buffId;
        });
        // 该buff存在且持续时间不为0,则走skill的这个持续时间,否则走buff下的持续时间
        if (iter != skillCfg->AttachedBuff.end() && iter->Duration != 0)
        {
            return iter->Duration + S2MS(m_roleBuff->GetExtraProp(coff, hurtType));
        }
    }
    // 判断是否为没有时限的buff,非永久存在buff,该buff会被顶掉,只是没有时间限制
    m_bForervered = cfg->Duration == 0;
    return m_bForervered ? 0 : cfg->Duration + S2MS(m_roleBuff->GetExtraProp(coff, hurtType));
}

void BuffData::UpdateAndNotify()
{
    if (m_roleBuff)
    {
        m_roleBuff->OnModPropWhenRemoveBuff(this);
        auto master = m_roleBuff->GetMaster();
        if (master) master->OnRemoveBuff(GetBuffID(), GetBuffActorDataInfo().m_nActorID);
    }
}
/////////////////////////////////////////
bool AsbTimeBuffData::Pause()
{
    if (IsInvalid()) return false;
    if (m_bPaused) return true;

    UpdateLeftTime();

    return BuffData::Pause();
}

bool AsbTimeBuffData::Resume()
{
    if (IsInvalid()) return false;
    if (!m_bPaused) return true;

    uint32_t leftTime = GetLeftTime();
    if (IsInvalid()) return false;

    return BuffData::Resume(leftTime);
}

bool AsbTimeBuffData::Term()
{
    return BuffData::Term();
}

uint32_t AsbTimeBuffData::GetLeftTime()
{
    if (IsInvalid())
    {
        OnExpireTimer();
        return 0;
    }
    if (m_bForervered) return 0;

    int64_t curTime = GetTimeStampMillisecond();
    int32_t leftTime = m_buffDataInfo.m_nTimestamp + m_buffDataInfo.m_nTimeLeft - curTime;
    leftTime = (leftTime > 0) ? leftTime : 0;
    if (leftTime == 0) OnExpireTimer();

    return leftTime;
}

uint32_t AsbTimeBuffData::GetLeftTimeDB()
{
    if (IsInvalid())
    {
        OnExpireTimer();
        return 0;
    }
    if (m_bForervered) return 0;

    // 绝对时间数据存的是buff总时长
    int32_t leftTime = m_buffDataInfo.m_nTimeLeft;
    leftTime = (leftTime > 0) ? leftTime : 0;
    if (leftTime == 0) OnExpireTimer();

    return leftTime;
}
/////////////////////////////////////////
bool RelaTimeBuffData::Pause()  
{
    if (IsInvalid()) return false;
    if (m_bPaused) return true;

    // 更新剩余时间
    UpdateLeftTime();

    return BuffData::Pause();
}

bool RelaTimeBuffData::Resume()
{
    if (IsInvalid()) return false;
    if (!m_bPaused) return true;

    uint32_t leftTime = GetLeftTime();
    if (IsInvalid()) return false;

    return BuffData::Resume(leftTime);
}

bool RelaTimeBuffData::Term()
{
    return BuffData::Term();
}

void RelaTimeBuffData::UpdateLeftTime()
{
    // 更新剩余时间
    int64_t curTime = GetTimeStampMillisecond();
    int32_t nTimeElapsed = int32_t(curTime - m_buffDataInfo.m_nTimestamp);
    m_buffDataInfo.m_nTimeLeft -= nTimeElapsed;
    m_buffDataInfo.m_nTimestamp = curTime;
}

uint32_t RelaTimeBuffData::GetLeftTime()
{
    if (IsInvalid())
    {
        OnExpireTimer();
        return 0;
    }
    if (m_bForervered) return 0;

    UpdateLeftTime();
    int32_t leftTime = m_buffDataInfo.m_nTimeLeft;
    leftTime = (leftTime > 0) ? leftTime : 0;
    if (leftTime == 0) OnExpireTimer();

    return leftTime;
}

uint32_t RelaTimeBuffData::GetLeftTimeDB()
{
    // 相对时间存的是剩余时间
    return GetLeftTime();
}
