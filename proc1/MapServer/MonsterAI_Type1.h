#pragma once
#include"MonsterAI.h"
#include"Monster.h"
#include"logic_def.hpp"


class MonsterAI_Type1 :public MonsterAI
{
public:
	MonsterAI_Type1();
	~MonsterAI_Type1();
	static bool GetRandomState();
	bool ActivePursure(int delta) override;
	class RandomState
	{
	public:
		RandomState();
		~RandomState();
		void GenerateRandomState();
		bool GetRandomState();
	protected:
		std::bitset<64> bt;
		uint16_t mIdx;
	};

protected:
	static RandomState mAss;
};