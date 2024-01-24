#pragma once
#include"Pet.h"
#include"PetAI.h"
#include"logic_def.hpp"
#define ATTACK_RANGE 6
#define FOLLOW_RANGE 10

class PetAI_Type6 :public PetAI
{
public:
	PetAI_Type6();
	~PetAI_Type6();

	bool HaveOtherBehaviourBeforeActivityStatus(int delta)override;

private:

};