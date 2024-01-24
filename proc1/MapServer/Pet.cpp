#include "stdafx.h"
#include "Pet.h"

Pet::Pet():mPetType(0)
{
}

Pet::~Pet()
{
	if (mPetAI_ptr != nullptr)
	{
		delete mPetAI_ptr;
		mPetAI_ptr = nullptr;
	}
}

void Pet::Init(uint64_t guid, DATA::Monster* pConfig)
{
	if (pConfig == nullptr)	return;

    mRoleAttr = new RoleAttr(this);
    mRoleState = new RoleState(this);
    mRoleMove = new RoleMove(this);
    mRoleSkill = new RoleSkill(this);
    mRoleBuff = new RoleBuff(this);

	Role::Init();
	SetGUID(guid);
	SetName(pConfig->Name);
	mMonsterTemplateID = pConfig->Id;
	SetScriptName(pConfig->Script);
	mPetAI_ptr = CreatePetAI(this, pConfig);
	SetType(role_type_pet);
	if (pConfig->ExistTime) {
		SetExistTime(pConfig->ExistTime);
	}
	InitRoleProp(pConfig);
	
}

PetAI* Pet::CreatePetAI(Pet* pet, DATA::Monster* pConfig)
{
	if (nullptr == pet || nullptr == pConfig) {
		return nullptr;
	}

	auto type = pConfig->MonsterAIType;//新建的类型
	PetAI* tmpPetAI = nullptr;
	switch (type)
	{
	case type6_normal_pet:
		tmpPetAI = new PetAI_Type6();
		break;
	case type7_taoist_pet:
		tmpPetAI = new PetAI_Type7();
		break;
	default:
		tmpPetAI = new PetAI_Type6();
		pet->SetWayFinding(false);
		break;
	}

	tmpPetAI->Init(pet, pConfig);
	return tmpPetAI;
}

void Pet::Update(int delta)
{
	Role::Update(delta);
	if (mPetAI_ptr)
	{
		mPetAI_ptr->Update(delta);
	}
}

bool Pet::TargetCanSelect(Role* tar)
{
	if (!tar || tar == this) return false;

	
	if (tar->IsNpc())return false;
	if (tar->IsPlayer()){

		if (tar->GetGUID() == mMasterGUID)
			return false;
	}

	if (tar->IsMonster()) {
		if (static_cast<Monster*>(tar)->IsTreasureMonster())return false;

		auto belong = GetMaster();
		if (!belong)return false;

		if (belong->GetRoleAttr()->GetRoleProp(role_camp) &&
			(belong->GetRoleAttr()->GetRoleProp(role_camp) == tar->GetRoleAttr()->GetRoleProp(role_camp)))return false;
	}

	if (tar->IsBiaoChe())return false;

	//暂无攻击模式对宠物产生影响的逻辑

	return true;
}

void Pet::OnRoleDie(uint64_t killerGUID)
{
	Role::OnRoleDie(killerGUID);
	RemoveExistTimeWhenDie();
}

bool Pet::JumpMap(Map* tarMap, uint16_t x, uint16_t y)
{
	if (!Monster::JumpMap(tarMap, x, y))return false;
	auto petAI = GetAIPet();
	if (!petAI) return false;
	petAI->ResetTarGuid();
	return true;
}

void Pet::ClearInvalidHateValue()
{
	for (auto iter = HatedVauleMap.begin(); iter != HatedVauleMap.end();)
	{
		auto role = MapRoleMgr::GetInstance()->FindRole(iter->first);
		if (!role)
		{
			iter = HatedVauleMap.erase(iter);
			continue;
		}
		if (role->GetRoleState()->GetState() == role_state_die || !GetAIPet()->IsInVieRange(role->GetGUID()))
		{
			iter = HatedVauleMap.erase(iter);
			continue;
		}
		++iter;
	}
}

void Pet::SetPetType(uint16_t monsterAIType)
{
	switch (monsterAIType)
	{
	case type6_normal_pet:
		mPetType = pet_type_normal;
		break;
	case type7_taoist_pet:
		mPetType = pet_type_taoist;
		break;
	default:
		break;
	}
}

void Pet::SetBackStatus()
{
	auto global = sGlobalConfig.GetData();
	if (!global)return;
	if (Tools::GenerateRandomInteger<int>(0, 10000) <= global->MonsterBackRate) {
		auto AI = GetAIPet();
		if (!AI)return;
		AI->SetBackStatus();
	}
}

bool Pet::IsInSameTeam(Role *role)
{
    auto *master = GetMaster();
    if (!master) return false;
    return master->IsInSameTeam(role);
}

bool Pet::IsInSameGuild(Role *role)
{
    auto *master = GetMaster();
    if (!master) return false;
    return master->IsInSameGuild(role);
}

bool Pet::IsInSameCamp(Role *role)
{
    auto *master = GetMaster();
    if (!master) return false;
    return master->IsInSameCamp(role);
}

bool Pet::IsGrayName()
{
    auto *master = GetMaster();
    if (!master) return false;
    return master->IsGrayName();
}

bool Pet::IsRedName()
{
    auto *master = GetMaster();
    if (!master) return false;
    return master->IsRedName();
}
