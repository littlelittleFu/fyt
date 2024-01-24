#pragma once

#include"Monster.h"
#include"PetAI.h"
#include"PetAI_Type6.h"
#include"PetAI_Type7.h"

class Pet :public Monster
{
public:
	Pet();
	virtual ~Pet();

	void Init(uint64_t guid, DATA::Monster* pConfig);
	PetAI* CreatePetAI(Pet* pet, DATA::Monster* pConfig);
	PetAI* GetAIPet() { return mPetAI_ptr; };
	virtual void Update(int delta) override;
	virtual bool TargetCanSelect(Role* tar) override;
	virtual void OnRoleDie(uint64_t killerGUID) override;
	virtual bool JumpMap(Map* tarMap, uint16_t x, uint16_t y)override;
	virtual void ClearInvalidHateValue()override;
    bool IsInSameTeam(Role *role) override;
    bool IsInSameGuild(Role *role) override;
    bool IsInSameCamp(Role *role) override;
    bool IsGrayName() override;
    bool IsRedName() override;

	void SetPetType(uint16_t monsterAIType);
	uint16_t GetPetType() { return mPetType; }
	void SetBackStatus();

protected:
	uint16_t mPetType;
	PetAI* mPetAI_ptr = nullptr;
};