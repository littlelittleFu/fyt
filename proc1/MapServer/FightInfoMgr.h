#pragma once
#include<vector>
#include<map>
#define INFOREMAINEDTIME 120000 //ms
struct Info
{
	uint64_t guid;
	uint32_t skillID;
	uint32_t remainedtime;
	Info(uint64_t Guid,uint64_t skillid):guid(Guid),skillID(skillid), remainedtime(0) {};

};
using AttackTargetInfoList = std::vector<Info>;
using BeAttackedInfoList = std::vector<Info>;


class FightInfo
{
public:
	FightInfo(Role * role ):mMaster(role){};
	~FightInfo() {};
	void Update(int32_t delta);
	void AddAttackTargetInfo(uint64_t guid, uint32_t skillID);
	void AddBeAttackedInfo(uint64_t guid, uint32_t skillID);
	void GetLatestAttackTarget(std::vector<Info>&vec);
	void GetLatestBeAttackedOwner(std::vector<Info>& vec);
	AttackTargetInfoList& GetAttackTargetInfoList() { return mAttackTargetInfoList; };
	BeAttackedInfoList& GetBeAttackedTargetInfoList() { return mBeAttackedInfoList; };

private:
	Role* mMaster;
	AttackTargetInfoList mAttackTargetInfoList;
	BeAttackedInfoList   mBeAttackedInfoList;
	uint32_t curTime = 0;
};