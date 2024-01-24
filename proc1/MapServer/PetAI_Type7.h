#pragma once
#include "Pet.h"
#include "PetAI.h"
#define FOLLOW_RANGE 10
#define HATETIME 10000

class PetAI_Type7 :public PetAI
{
public:
	PetAI_Type7();
	~PetAI_Type7() {};

	void DefendStatusLogic(int delta)override;
	bool IsHateTime(int delta);

	uint16_t ChangeIdleStateInActiveLogic(int delta) override;
	void OnIdleProc(int delta)override;
	uint16_t ChangeFollowStateInActiveLogic(int delta) override;
	uint16_t ChangePickItemStateInActiveLogic(int delta) override;
	uint16_t ChangePursureStateInActiveLogic(int delta) override;
	uint16_t ChangeAttackStateInActiveLogic(int delta) override;
	uint16_t ChangeAttackIdleStateInActiveLogic(int delta) override;


private:
	uint32_t mHateTime;

};
