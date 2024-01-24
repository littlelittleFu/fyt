#pragma once
#include"Monster.h"
#include"MonsterAI.h"

class MonsterTrigger
{
	DECL_SINGLETON(MonsterTrigger);
	using MonsterAIFuncMap = std::map<monster_behaviour_trigger, std::function<bool(Monster*, std::string)>>;
public:
	MonsterTrigger();
	~MonsterTrigger() {};
	void update(Monster*master);
private:
	MonsterAIFuncMap mMonsterAIFuncMap;

};

bool FindTarget(Monster* master, std::string params);
bool TargetHP(Monster* master, std::string params);
bool SelfHP(Monster* master, std::string params);
bool OnDie(Monster* master, std::string params);
//bool StartAttackTime(Monster* master, std::string params);
bool CurDistance(Monster* master, std::string params);
bool TargetObj(Monster* master, std::string params);
bool HarmedBySpecialSkill(Monster* master, std::string params);