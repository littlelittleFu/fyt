#pragma once
#include"MonsterAI.h"
#include"Monster.h"
#include"logic_def.hpp"

#define FINAL_RANGE_5  0
//ïÚ³µ¹Ö
class MonsterAI_Type5 :public MonsterAI
{
public:
	MonsterAI_Type5();
	~MonsterAI_Type5();
	void InitParams(const std::string& guid, uint32_t X, uint32_t Y, uint16_t finalRange, const std::string&func, uint8_t posRange,const CLuaObject posTable);
	bool IsFinshed();

	uint16_t ChangeIdleState(int delta) override;
	void OnIdleProc(int delta) override;
	void ExitIdleState(uint16_t newStateType) override;

	uint16_t ChangeFollowState(int delta) override;
	void OnFollowProc(int delta) override;
	void ExitFollowState(uint16_t newStateType) override;

	bool ActiveFollow(int delta) override;

protected:
	uint16_t mFinalRange;   //ÖÕµã±ê·¶Î§
	std::string mFunc;
	bool mFinished;
	uint8_t mPosRange;
	std::vector<std::pair<uint32_t, uint32_t>> mPos;
};