#include"stdafx.h"
#include"MonsterAI_Trigger.h"

IMPL_SINGLETON(MonsterTrigger);

MonsterTrigger::MonsterTrigger()
{
	mMonsterAIFuncMap[monster_ai_discover_target]              = FindTarget;
	mMonsterAIFuncMap[monster_ai_target_hp]                    = TargetHP;
	mMonsterAIFuncMap[monster_ai_self_hp]                      = SelfHP;
	mMonsterAIFuncMap[monster_ai_die_trigger]                  = OnDie;
	//mMonsterAIFuncMap[monster_ai_start_fight_time]             = StartAttackTime;
	mMonsterAIFuncMap[monster_ai_target_and_self_instance]     = CurDistance;
	mMonsterAIFuncMap[monster_ai_target_job]                   = TargetObj;
	mMonsterAIFuncMap[monster_ai_self_harmed_by_special_skill] = HarmedBySpecialSkill;
}

void MonsterTrigger::update(Monster* master)
{
	if (!master || !master->GetAIMonster())return;
	auto& mmap = master->GetAIMonster()->GetAIBehaviourMap();
	if (mmap.empty())return;
	for (auto& i : mmap)
	{
		auto iter = mMonsterAIFuncMap.find(i.first);
		if (iter == mMonsterAIFuncMap.end())continue;
		auto result = iter->second(master,i.second.params);
		if (result)
		{
			LuaBindCallVoid(i.second.callback, to_string(master->GetGUID()), to_string(master->GetAIMonster()->GetTarGuid()));
		}
	}
}

bool FindTarget(Monster* master, std::string params)
{
	if (!master)return false;
    return master->GetAIMonster()->FindTarget(params);
}
bool TargetHP(Monster* master, std::string params)
{
	if (!master)return false;
	return master->GetAIMonster()->TargetHP(params);
}
bool SelfHP(Monster* master, std::string params)
{
	if (!master)return false;
	return master->GetAIMonster()->SelfHP(params);
}
bool OnDie(Monster* master, std::string params)
{
	if (!master)return false;
	return master->GetAIMonster()->OnDie(params);
}
//bool StartAttackTime(Monster* master, std::string params)
//{
//	if (!master)return false;
//	return master->GetAIMonster()->StartAttackTime(params);
//}
bool CurDistance(Monster* master, std::string params)
{
	if (!master)return false;
	return master->GetAIMonster()->CurDistance(params);
}
bool TargetObj(Monster* master, std::string params)
{
	if (!master)return false;
	return master->GetAIMonster()->TargetObj(params);
}
bool HarmedBySpecialSkill(Monster* master, std::string params)
{
	return false;//暂时从这触发
	if (!master)return false;
	return master->GetAIMonster()->HarmedBySpecialSkill(params);
}