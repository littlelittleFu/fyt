#pragma once
#include"MonsterAI.h"
#include"Monster.h"
#include"logic_def.hpp"

#define FINAL_RANGE_4  1
//ïÚ³µ¹Ö
class MonsterAI_Type4 :public MonsterAI
{
public:
	MonsterAI_Type4();
	~MonsterAI_Type4();
	bool TarIsInRange();
	void InitParams(const std::string& guid, uint32_t X, uint32_t Y, uint32_t range, uint16_t finalRange);
	bool IsFinshed();

	uint16_t ChangeIdleState(int delta) override;
	void OnIdleProc(int delta) override;
	void ExitIdleState(uint16_t newStateType) override;

	uint16_t ChangeFollowState(int delta) override;
	void OnFollowProc(int delta) override;
	void ExitFollowState(uint16_t newStateType) override;

	bool ActiveFollow(int delta) override;


protected:
	uint16_t mRange;        //¸úËæ·¶Î§
	uint16_t mFinalRange;   //ÖÕµã±ê·¶Î§
	bool mFinished;
};
