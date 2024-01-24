#include "stdafx.h"
#include "PetAI_Type6.h"

PetAI_Type6::PetAI_Type6():PetAI()
{

}

PetAI_Type6::~PetAI_Type6()
{

}


bool PetAI_Type6::HaveOtherBehaviourBeforeActivityStatus(int delta)
{
	return JumpToMasterWhenOutOfRange();
}