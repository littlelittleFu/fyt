#include "stdafx.h"
#include "RoleBuff.h"
#include "Role.h"
#include "role_table.hpp"

RoleBuff::RoleBuff(Role* master) : RoleAction(master)
{
    m_BuffDataAry.clear();
    m_buffInfoDBList.clear();
}

RoleBuff::~RoleBuff()
{
}

bool RoleBuff::Init()
{
    m_BuffDataAry.clear();
    if (!m_buffInfoDBList.empty())
    {
        for (auto& data : m_buffInfoDBList)
        {
            AddBuffFromCache(data);
        }
        m_buffInfoDBList.clear();
    }
	return true;
}

void RoleBuff::Update(int32_t delta)
{
    curTime += delta;
    if (curTime < 1000) return;
    curTime = 0;
    if (!m_BuffDataAry.empty())
    {
        for (auto iter = m_BuffDataAry.begin(); iter != m_BuffDataAry.end(); ++iter) 
        {
            auto& list = iter->second;
            if (list.empty()) continue;

            auto it = list.begin();
            for (; it != list.end();)
            {
                auto &upBuffData = *it;
                // 无效的
                if (upBuffData->IsInvalid()) 
                {
                    it = list.erase(it);
                    continue;
                }
                ++it;
            }
        }

        ResetNeedUpdate(buff_need_update_flag);
    }
}
// to player
uint16_t RoleBuff::GetInUseBuffInfo(std::list<BUFF_INFO>& list)
{
    auto iter = m_BuffDataAry.begin();
    for (;iter != m_BuffDataAry.end(); ++iter)
    {
        auto& buffDataAry = iter->second;
        auto it = buffDataAry.begin();
        for (; it != buffDataAry.end(); ++it)
        {
            if ((*it)->IsInvalid() || (*it)->IsPaused()) continue;
            BUFF_INFO pBuffInfo;
            if (!(*it)->GenerateBuffInfo(pBuffInfo)) continue;

            list.push_back(pBuffInfo);
        }
    }
    return (uint16_t)list.size();
}
// to db
uint16_t RoleBuff::GetAllBuffInfo(std::list<BUFF_INFO_DB>& list, bool beSave)
{
    auto iter = m_BuffDataAry.begin();
    for (;iter != m_BuffDataAry.end(); ++iter)
    {
        auto& buffDataAry = iter->second;
        auto it = buffDataAry.begin();
        for (; it != buffDataAry.end(); ++it) 
        {
            if ((*it)->IsInvalid()) continue;
            auto cfg = (*it)->GetBuffConfig();
            if (beSave)
                if (!cfg || cfg->OfflineSave == BOST_NOTSAVE) continue;
            BUFF_INFO_DB pBuffInfo;
            if (!(*it)->GenerateBuffInfoDB(pBuffInfo))continue;

            list.push_back(pBuffInfo);
        }
    }
    return (uint16_t)list.size();
}

bool RoleBuff::AddBuffFromCache(const BUFF_INFO_DB *pBuffInfo)
{
    m_buffInfoDBList.push_back(*pBuffInfo);
    return true;
}

std::vector<uint16_t> RoleBuff::GetValidBuffIDList()
{
    std::vector<uint16_t> buffIDList;
    for (const auto &iter : m_BuffDataAry) {
        const auto &buffDataAry = iter.second;
        for (const auto &buffData : buffDataAry) {
            if (buffData->IsInvalid()) continue;
            buffIDList.push_back(buffData->GetBuffID());
        }
    }
    return buffIDList;
}

bool RoleBuff::AddBuffFromCache(const BUFF_INFO_DB& pBuffInfo)
{
    auto pBuffData = FindBuff(pBuffInfo.buffid);
    if (pBuffData) return true;

    pBuffData = CreateBuffData(pBuffInfo.buffid);
    if (!pBuffData) return false;
    auto cfg = pBuffData->GetBuffConfig();
    if (!cfg) return false;

    auto* master = GetMaster();
    if (!master) return false;
    master->temp_attr_type = 1;
    master->temp_attr_id = pBuffInfo.buffid;

    BuffActorDataInfo actorInfo;
    actorInfo.m_nActorID = pBuffInfo.actor_id;
    actorInfo.m_sActorName = pBuffInfo.actor_name;
    actorInfo.m_nActorJob = pBuffInfo.actor_job;
    actorInfo.m_nActorLevel = pBuffInfo.actor_level;
    actorInfo.m_nActorSkill = pBuffInfo.actor_skill;
    pBuffData->SetBuffActorDataInfo(actorInfo);
    BuffDataInfo buffInfo(std::string(pBuffInfo.attr));
    buffInfo.m_nDBIndex = pBuffInfo.index;
    buffInfo.m_nTimestamp = pBuffInfo.timestamp;
    buffInfo.m_nTimeLeft = pBuffInfo.timeleft;
    buffInfo.m_tempLeftTime = pBuffInfo.timeleft;
    pBuffData->SetBuffDataInfo(buffInfo);

    if (pBuffData->ApplyBuffFromeCache(pBuffInfo.stack))
    {
        auto& list = m_BuffDataAry[cfg->GroupId];
        list.push_back(pBuffData);
        AddInvisibleEffectByAttr(pBuffData, GetMaster());
        return true;
    }
    master->temp_attr_type = 0;
    master->temp_attr_id = 0;
    return false;
}

bool RoleBuff::AddBuffByRole(uint16_t nBuffID, Role *pActor, uint16_t nSkillID, const std::string& attrStr, uint32_t time)
{
    if (!pActor) return false;

    BuffActorDataInfo actorInfo;
    actorInfo.m_nActorID = pActor->GetGUID();
    actorInfo.m_sActorName = pActor->GetName();
    actorInfo.m_nActorJob = (uint8_t)pActor->GetRoleProp(role_job);
    actorInfo.m_nActorLevel = pActor->GetRoleProp(role_level);
    actorInfo.m_nActorSkill = nSkillID;
    BuffDataInfo buffInfo(attrStr);
    buffInfo.m_tempLeftTime = time;
    UPBuffData pBuffData;
    if ((pBuffData = DoAddBuffByRole(nBuffID, buffInfo, actorInfo)) != nullptr)
    {
        AddInvisibleEffectByAttr(pBuffData, pActor);
        return true;
    }
    return false;
}

UPBuffData RoleBuff::DoAddBuffByRole(uint16_t nBuffID, const BuffDataInfo& buffInfo, const BuffActorDataInfo& actorInfo)
{
    UPBuffData pBuffData;
    auto master = GetMaster();
    if (!master) return pBuffData;
    if (!Check(nBuffID, actorInfo)) return pBuffData;

    DATA::Buff* config = sBuffConfig.Get(nBuffID);
    if (!config) return pBuffData;
    if (BGRI_4 == config->GroupRelation && (pBuffData = FindBuffByGroupID(config->GroupId)))
    {
        if (!buffInfo.m_tempLeftTime) const_cast<BuffDataInfo*>(&buffInfo)->m_tempLeftTime = config->Duration;
        UpdateInlineBuffData(pBuffData, buffInfo, actorInfo, true);
        return pBuffData;
    }

    pBuffData = FindBuff(nBuffID);
    if (pBuffData) 
    {
        UpdateInlineBuffData(pBuffData, buffInfo, actorInfo, true);
    }
    else 
    {
        pBuffData = AddNewBuffData(nBuffID, buffInfo, actorInfo);
    }
    return pBuffData;
}

UPBuffData RoleBuff::FindBuff(uint16_t nBuffID, uint64_t nActorID)
{
    auto iter = m_BuffDataAry.begin();
    for (; iter != m_BuffDataAry.end(); ++iter)
    {
        for (auto& it : iter->second)
            if (!it->IsInvalid() && it->GetBuffID() == nBuffID && it->GetBuffActorDataInfo().m_nActorID == nActorID)
                return it;
    }
    return nullptr;
}

UPBuffData RoleBuff::FindBuff(uint16_t nBuffID)
{
    auto iter = m_BuffDataAry.begin();
    for (; iter != m_BuffDataAry.end(); ++iter)
    {
        for (auto& it : iter->second)
            if (!it->IsInvalid() && it->GetBuffID() == nBuffID)
                return it;
    }
    return nullptr;
}

UPBuffData RoleBuff::FindBuffByGroupID(uint16_t buffGroupID)
{
    auto iter = m_BuffDataAry.find(buffGroupID);
    if (iter != m_BuffDataAry.end())
    {
        const UPBuffDataAry& ar = iter->second;
        for (auto it = ar.begin(); it != ar.end(); ++it)
        {
            if ((*it) && !(*it)->IsInvalid()) return *it;
        }
    }
    
    return nullptr;
}

bool RoleBuff::BuffExistByGroupID(uint16_t buffGroupID)
{
    auto buffData = FindBuffByGroupID(buffGroupID);
    if (buffData) return true;

    return false;
}

bool RoleBuff::BuffExist(uint16_t nBuffID)
{
    return FindBuff(nBuffID) != nullptr;
}

bool RoleBuff::BuffExist(uint16_t nBuffID, uint64_t nActorID)
{
    return FindBuff(nBuffID, nActorID) != nullptr;
}

bool RoleBuff::RemoveBuff(uint16_t nBuffID)
{
    auto buffData = FindBuff(nBuffID);
    if (buffData) buffData->Term();

    return true;
}

bool RoleBuff::RemoveBuff(uint16_t nBuffID, uint64_t nActorID)
{
    auto buffData = FindBuff(nBuffID, nActorID);
    if (buffData) buffData->Term();

    return true;
}

void RoleBuff::PauseBuff()
{
    auto iter = m_BuffDataAry.begin();
    for (; iter != m_BuffDataAry.end(); ++iter)
    {
        for (auto& it : iter->second)
            it->Pause();
    }
}

void RoleBuff::PauseBuff(uint16_t nBuffID)
{
    auto buffData = FindBuff(nBuffID);
    if (buffData) buffData->Pause();
}

void RoleBuff::ResumeBuff()
{
    auto iter = m_BuffDataAry.begin();
    for (; iter != m_BuffDataAry.end(); ++iter)
    {
        for (auto& it : iter->second)
            it->Resume();
    }
}

void RoleBuff::ResumeBuff(uint16_t nBuffID)
{
    auto buffData = FindBuff(nBuffID);
    if (buffData) buffData->Resume();
}
// =-1buff不存在,=0永久,>0剩余时间(buff时间不会超过int32_t上限)
int64_t RoleBuff::GetBuffLeftTime(uint16_t buffID)
{
    auto buffData = FindBuff(buffID);
    BUFF_INFO pBuffInfo;
    if (buffData && buffData->GenerateBuffInfo(pBuffInfo))
    {
        return pBuffInfo.life;
    }
    return -1;
}

uint16_t RoleBuff::GetBuffStack(uint16_t buffID)
{
    auto buffData = FindBuff(buffID);
    if (buffData) return buffData->GetBuffDataInfo().m_stack;

    return 0;
}

void RoleBuff::UpdateBuffStack(uint16_t buffID, int16_t diff)
{
    auto buffData = FindBuff(buffID);
    if (!buffData) return;

    auto cfg = buffData->GetBuffConfig();
    if (!cfg) return;

    auto gri = cfg->GroupRelation;
    if (gri != BGRI_3) return;
    /*
    BGRI_0:// 无视新增BUFF
    BGRI_1:// 按先后顺序进行替换
    BGRI_2:// 按等级替换
    BGRI_3:// 刷新时间并增加层数
    BGRI_4:// 时间叠加
    */
    buffData->UpdateStack(diff);
    buffData->ResetTimer();
    buffData->OnUpdateBuff();

}

void RoleBuff::OnRoleDead()
{
    auto iter = m_BuffDataAry.begin();
    for (; iter != m_BuffDataAry.end(); ++iter)
    {
        for (auto& buffData : iter->second)
        {
            auto* cfg = buffData->GetBuffConfig();
            if (!cfg || cfg->DieDelete == BRDDT_NOTDELETE) continue;

            buffData->Term();
        }
    }
}

void RoleBuff::OnRoleMove()
{
    auto iter = m_BuffDataAry.begin();
    for (; iter != m_BuffDataAry.end(); ++iter)
    {
        for (auto& buffData : iter->second)
        {
            auto* cfg = buffData->GetBuffConfig();
            if (!cfg || cfg->MoveDelete == BUFF_MOVE_NODELETE) continue;

            buffData->Term();
        }
    }
}

std::string RoleBuff::GetBuffActorGuid(uint16_t buffID)
{
    auto buffData = FindBuff(buffID);
    if (!buffData) return EMPTYSTR;

    return std::to_string(buffData->GetBuffActorDataInfo().m_nActorID);
}

const std::string & RoleBuff::GetBuffActorName(const std::string &actorGuid, uint16_t buffID)
{
    if (actorGuid.empty()) return EMPTYSTR;
    auto guid = std::stoull(actorGuid);

    auto buffData = FindBuff(buffID, guid);
    if (!buffData) return EMPTYSTR;

    return buffData->GetBuffActorDataInfo().m_sActorName;
}

uint8_t RoleBuff::GetBuffActorJob(const std::string &actorGuid, uint16_t buffID)
{
    if (actorGuid.empty()) return 0;
    auto guid = std::stoull(actorGuid);

    auto buffData = FindBuff(buffID, guid);
    if (!buffData) return 0;

    return buffData->GetBuffActorDataInfo().m_nActorJob;
}

uint32_t RoleBuff::GetBuffActorLevel(const std::string &actorGuid, uint16_t buffID)
{
    if (actorGuid.empty()) return 0;
    auto guid = std::stoull(actorGuid);

    auto buffData = FindBuff(buffID, guid);
    if (!buffData) return 0;

    return buffData->GetBuffActorDataInfo().m_nActorLevel;
}

uint16_t RoleBuff::GetBuffActorSkill(const std::string &actorGuid, uint16_t buffID)
{
    if (actorGuid.empty()) return 0;
    auto guid = std::stoull(actorGuid);

    auto buffData = FindBuff(buffID, guid);
    if (!buffData) return 0;

    return buffData->GetBuffActorDataInfo().m_nActorSkill;
}

void RoleBuff::OnModPropWhenUpdateStack(BuffData* upBuffData, bool beAdd)
{
    ModRoleProp(upBuffData, false, beAdd, 1);
}

void RoleBuff::OnModPropWhenRemoveBuff(BuffData* upBuffData)
{
    ModRoleProp(upBuffData, false, false, upBuffData->GetBuffDataInfo().m_stack);
}

void RoleBuff::OnModPropWhenPeriodBuff(BuffData* upBuffData)
{
    // 只更新hp、mp
    ModRoleProp(upBuffData, true, true);
}

void RoleBuff::ModRoleProp(BuffData* upBuffData, bool bePeriod, bool beAdd, uint16_t stackDiff)
{
    auto* self = GetMaster();
    if (!self) return;
    if (!upBuffData) return;

    if (beAdd)
    {
        const AttrMap* attrCfg = upBuffData->GetBuffAttrCfg();
        if (!attrCfg) return;

        int32_t hurtType = 0;
        auto* skillCfg = sSkillConfig.Get(upBuffData->GetBuffActorDataInfo().m_nActorSkill);
        if (skillCfg) hurtType = skillCfg->HurtType;

        std::map<int32_t, int32_t> attrMap;
        auto iter = (*attrCfg).begin();
        for (; iter != (*attrCfg).end(); ++iter)
        {
            // 周期只更新hp、mp
            if (bePeriod && role_hp != iter->first && role_mp != iter->first) continue;
           
            auto att = iter->first;
            auto val = iter->second.front();
            if (att == 0 || val == 0) continue;

            // 根据伤害类型更新
            auto coff = iter->second.back();
            val += GetExtraProp(coff, hurtType);
            // 更新非hp、mp
            if (att != role_hp && att != role_mp)
            {
                val = self->AddRoleProp(att, val);
            }
            attrMap[att] += val;
        }
        // hp、mp单独更新
        ModHM(upBuffData, attrMap[role_hp], attrMap[role_mp]);
        if (!bePeriod) upBuffData->UpdatePropStackReocrd(attrMap);
    }
    else
    {
        auto& attrStackList = upBuffData->GetAttrStackList();
        for (uint16_t i = 0; i < stackDiff; ++i)
        {
            if (attrStackList.empty()) break;
            // 扣除一层
            auto& attrMap = attrStackList.back();
            auto iter = attrMap.begin();
            for (; iter != attrMap.end(); ++iter)
            {
                auto att = iter->first;
                auto val = -1 * iter->second;
                if (att == 0 || val == 0) continue;

                self->AddRoleProp(att, val);
            }
            attrStackList.pop_back();
        }
    }
}

bool RoleBuff::Check(uint16_t nBuffID, const BuffActorDataInfo& actorInfo)
{
    auto master = GetMaster();
    if (!master) return false;

    bool ret = true;
    TRIGGER_EVENT_RET<bool>(ret, trigger_check_add_buff, nBuffID, master->GetGUIDAsString(), to_string(actorInfo.m_nActorID));
    return ret;
}

void RoleBuff::ModHM(BuffData* upBuffData, int32_t deltaHP, int32_t deltaMP)
{
    if (!upBuffData) return;
    if (deltaHP == 0 && deltaMP == 0) return;

    auto* self = GetMaster();
    if (!self) return;

    if (deltaHP < 0)
    {
        AttackResult res;
        res.actorGUID = upBuffData->GetBuffActorDataInfo().m_nActorID;
        res.actorName = upBuffData->GetBuffActorDataInfo().m_sActorName;
        res.targetGUID = self->GetGUID();
        res.skillId = upBuffData->GetBuffActorDataInfo().m_nActorSkill;
        res.decreaseHP = -deltaHP;
        res.decreaseMP = -deltaMP;

        self->AttackedByRole(res);
    }
    else
    {
        self->UpdateHPMP(deltaHP, deltaMP, 0, true);
    }
}

int32_t RoleBuff::GetExtraProp(int32_t coff, int32_t hurtType)
{
    if (coff == 0) return 0;

    auto* pMaster = GetMaster();
    if (!pMaster) return 0;

    int32_t min = 0;
    int32_t max = 0;
    switch (hurtType)
    {
    case skill_hurt_type_phy:
        min = pMaster->GetRoleProp(role_min_phy_atk);
        max = pMaster->GetRoleProp(role_max_phy_atk);
        break;
    case skill_hurt_type_mag:
        min = pMaster->GetRoleProp(role_min_mag_atk);
        max = pMaster->GetRoleProp(role_max_mag_atk);
        break;
    case skill_hurt_type_tao:
        min = pMaster->GetRoleProp(role_min_tao_atk);
        max = pMaster->GetRoleProp(role_max_tao_atk);
        break;
    }

    auto val = Tools::GenerateRandomInteger<int32_t>(min, max);
    return int32_t(val * (double(coff) * PRECISION));
}
// beSelf:是否组内的同一个buff
void RoleBuff::UpdateInlineBuffData(UPBuffData& buffData, const BuffDataInfo& buffInfo, const BuffActorDataInfo& actorInfo, bool beSelf)
{
    auto cfg = buffData->GetBuffConfig();
    if (!cfg) return;

    buffData->SetBuffActorDataInfo(actorInfo);
    buffData->SetBuffDataTempLeftTime(buffInfo);

    auto gri = cfg->GroupRelation;
    auto gid = cfg->GroupId;

    switch (gri)
    {
        case BGRI_0:// 无视新增BUFF
            IgnoreBuffData(buffData, beSelf);
            break;
        case BGRI_1:// 按先后顺序进行替换
            SwapBuffDataByTimestamp(buffData, beSelf);
            break;
        case BGRI_2:// 按等级替换
            SwapBuffDataByLevel(buffData, beSelf);
            break;
        case BGRI_3:// 刷新时间并增加层数
            FlushBuffData_DurationAndStack(buffData, beSelf);
            break;
        case BGRI_4:// 时间叠加
            FlushBuffData_Duration(buffData, beSelf);
            break;
        default: return;
    }
}

UPBuffData RoleBuff::AddNewBuffData(uint16_t nBuffID, const BuffDataInfo& buffInfo, const BuffActorDataInfo& actorInfo)
{
    auto pBuffData = CreateBuffData(nBuffID);
    if (!pBuffData) return nullptr;
    auto cfg = pBuffData->GetBuffConfig();
    if (!cfg) return nullptr;

    // 新buff才允许自定义属性
    pBuffData->SetBuffDataAttr(buffInfo);

    auto gid = cfg->GroupId;
    // 判断该buff处理方式,先判断组间,在判断组内关系
    struct RelationNode
    {
        uint16_t gid = 0;
        uint16_t ggr = BGRO_0;
    };
    RelationNode node;
    std::vector<RelationNode> relationVec;  // 当前buff与其他各组的关系
    auto arrIter = m_BuffDataAry.begin();
    for (; arrIter != m_BuffDataAry.end(); ++arrIter)
    {
        if (arrIter->first != gid && !arrIter->second.empty())// 非当前buff组
        {
            node.gid = arrIter->first;
            auto bfc = sBuffGroupConfig.GetByGroupIdKey(DATA::GroupIdKey(arrIter->first, gid));
            if (bfc) node.ggr = bfc->GroupRelation;
            relationVec.push_back(node);
        }
    }
    // 按照关系优先级排序
    if (!relationVec.empty())
    {
        std::sort(relationVec.begin(), relationVec.end(), [](const RelationNode& a, const RelationNode& b){
            return a.ggr > b.ggr;
        });
        auto relaIter = relationVec.begin();
        for (; relaIter != relationVec.end(); ++relaIter)
        {
            switch (relaIter->ggr)
            {
            case BGRO_0:         // 共存
                UpdateInlineBuffData(pBuffData, buffInfo, actorInfo, false);
                break;
            case BGRO_1:         // 替换(新留下)
                RemoveBuffGroup(relaIter->gid);
                UpdateInlineBuffData(pBuffData, buffInfo, actorInfo, false);
                break;
            case BGRO_2:         // 抵消(两组都消失)
                RemoveBuffGroup(relaIter->gid);
                RemoveBuffGroup(gid);
                pBuffData = nullptr;
                break;
            case BGRO_3:         // 忽略(新无法加入)
                pBuffData = nullptr;
                break;
            }
            // 只会与其中一组做操作,按照优先级来
            break;
        }
    }
    else// 加入当前组
    {
        UpdateInlineBuffData(pBuffData, buffInfo, actorInfo, false);
    }
    return pBuffData;
}

void RoleBuff::IgnoreBuffData(UPBuffData& buffData, bool beSelf)
{
    if (beSelf)
    {
        // 不处理
        return;
    }
    // 新增
    auto cfg = buffData->GetBuffConfig();
    if (!cfg)
    {
        buffData = nullptr;
        return;
    }

    auto gid = cfg->GroupId;
    auto& list = m_BuffDataAry[gid];
    // 当前组如果是空的需要加进来
    if (IsAllInvalid(gid))
    {
        if (buffData->ApplyBuff(1))
        {
            list.push_back(buffData);
            return;
        }
    }
    buffData = nullptr;
    // 忽略,不处理
}

void RoleBuff::SwapBuffDataByTimestamp(UPBuffData& buffData, bool beSelf)
{
    if (beSelf)
    {
        buffData->ResetTimer();
        buffData->OnUpdateBuff();
        return;
    }
    // 新增
    auto cfg = buffData->GetBuffConfig();
    if (!cfg)
    {
        buffData = nullptr;
        return;
    }

    auto gid = cfg->GroupId;
    auto& list = m_BuffDataAry[gid];

    if (!buffData->ApplyBuff(1))
    {
        buffData = nullptr;
        return;
    }
    if (!IsAllInvalid(gid))
    {
        auto iter = list.begin();
        for (; iter != list.end(); ++iter)
        {
            if (!(*iter)->IsInvalid())
            {
                (*iter)->Term();
                list.push_back(buffData);
                return;
            }
        }
    }
    list.push_back(buffData);
}

void RoleBuff::SwapBuffDataByLevel(UPBuffData& buffData, bool beSelf)
{
    if (beSelf)
    {
        buffData->ResetTimer();
        buffData->OnUpdateBuff();
        return;
    }
    // 新增
    auto cfg = buffData->GetBuffConfig();
    if (!cfg)
    {
        buffData = nullptr;
        return;
    }

    auto gid = cfg->GroupId;
    auto& list = m_BuffDataAry[gid];
    auto level = cfg->Level;

    if (!IsAllInvalid(gid))
    {
        UPBuffData tmp;
        // 找比当前buff等级低的
        auto iter = list.begin();
        for (; iter != list.end(); ++iter)
        {
            if (!(*iter)->IsInvalid() && level > (*iter)->GetBuffConfig()->Level)
            {
                level = (*iter)->GetBuffConfig()->Level;
                tmp = *iter;
            }
        }
        if (tmp)
        {
            if (!buffData->ApplyBuff(1))
            {
                buffData = nullptr;
                return;
            }
            tmp->Term();
            list.push_back(buffData);
        }
        else
        {
            buffData = nullptr;
        }
        return;
    }

    if (!buffData->ApplyBuff(1))
    {
        buffData = nullptr;
        return;
    }
    list.push_back(buffData);
}

void RoleBuff::FlushBuffData_DurationAndStack(UPBuffData& buffData, bool beSelf)
{
    if (beSelf)
    {
        buffData->UpdateStack(1);
        buffData->ResetTimer();
        buffData->OnUpdateBuff();
        return;
    }
    // 新加的buff
    auto cfg = buffData->GetBuffConfig();
    if (!cfg)
    {
        buffData = nullptr;
        return;
    }

    auto gid = cfg->GroupId;
    auto& list = m_BuffDataAry[gid];

    if (!buffData->ApplyBuff(1))
    {
        buffData = nullptr;
        return;
    }
    list.push_back(buffData);
}

void RoleBuff::FlushBuffData_Duration(UPBuffData& buffData, bool beSelf)
{
    if (beSelf)
    {
        buffData->StackTimer();
        buffData->OnUpdateBuff();
        return;
    }

    // 新加的buff
    auto cfg = buffData->GetBuffConfig();
    if (!cfg)
    {
        buffData = nullptr;
        return;
    }

    auto gid = cfg->GroupId;
    auto& list = m_BuffDataAry[gid];

    if (!buffData->ApplyBuff(1))
    {
        buffData = nullptr;
        return;
    }
    list.push_back(buffData);
}

void RoleBuff::RemoveBuffGroup(uint16_t groupId)
{
    auto& list = m_BuffDataAry[groupId];
    if (!list.empty())
    {
        auto iter = list.begin();
        for (; iter != list.end(); ++iter)
        {
            (*iter)->Term();
        }
    }
}

void RoleBuff::AddInvisibleEffectByAttr(UPBuffData& pBuffData, Role* actor)
{
    if (!actor) return;
    if (!pBuffData) return;
    const AttrMap* attrCfg = pBuffData->GetBuffAttrCfg();
    if (!attrCfg || attrCfg->empty()) return;

    auto iter = attrCfg->find(role_is_stealth);
    // 属性key是隐身 属性值是1则添加效果
    if (iter == attrCfg->end() || iter->second.empty() || !iter->second[0]) return;
    actor->AddInvisibleEffect();
}

UPBuffData RoleBuff::CreateBuffData(uint16_t buffid)
{
    UPBuffData upBuffData;
    DATA::Buff* config = sBuffConfig.Get(buffid);
    if (!config) return nullptr;

    if (config->TimeType == BTT_ASB)
    {
        upBuffData = std::make_shared<AsbTimeBuffData>(this, config);
    }
    else
    {
        upBuffData = std::make_shared<RelaTimeBuffData>(this, config);
    }
    return upBuffData;
}

bool RoleBuff::IsAllInvalid(uint32_t groupId)
{
    for (auto iter = m_BuffDataAry[groupId].begin(); iter != m_BuffDataAry[groupId].end(); ++iter)
    {
        if (!(*iter)->IsInvalid()) return false;
    }
    return true;
}