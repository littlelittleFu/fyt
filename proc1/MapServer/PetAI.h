#pragma once
#include<vector>
#include"Pet.h"
#include"MonsterAI.h"
#include"ItemMap.h"
#define FOLLOW_DIS 1

class Pet;
class PetAI :public MonsterAI
{
public:
	PetAI();
	~PetAI();
	bool Init(Pet* pet, DATA::Monster* cfg);
	virtual void Update(int delta)override;

	void Stay();                                            // 原地不动
	void JumpToMaster(Map* tarMap = nullptr);                                    // 跳转至主人身边
	bool JumpToMasterWhenOutOfRange();                      // 超出跟随范围跳转至主人身边
	Role* Pet_GetNearestTarget();                           // 宠物获取攻击目标
	bool Pet_IsMonsterEnterVieRange();                      // 是否有怪物在宠物视野范围

	virtual void SetAIState(uint16_t state);

	void ActionByActivityStatus(int delta);
	virtual void FollowStatusLogic(int delta);
	virtual void ActiveStatusLogic(int delta);
	virtual void DefendStatusLogic(int delta);
	virtual void StayStatusLogic(int delta);

	// 跟随逻辑下的状态改变
	virtual void OnStateIdleProcInFollowLogic(int delta);
	virtual void OnStateEscapeProcInFollowLogic(int delta);
	virtual void OnStateFollowProcInFollowLogic(int delta);
	virtual void OnStatePickItemProcInFollowLogic(int delta);

	// 主动逻辑下的状态
	virtual void OnStateIdleProcInActiveLogic(int delta);
	virtual void OnStateEscapeProcInActiveLogic(int delta);
	virtual void OnStateFollowProcInActiveLogic(int delta);
	virtual void OnStatePickItemProcInActiveLogic(int delta);
	virtual void OnStateAttackProcInActiveLogic(int delta);
	virtual void OnStateAttackIdleProcInActiveLogic(int delta);
	virtual void OnStatePursureProcInActiveLogic(int delta);

	// 守护逻辑下的状态
	virtual void OnStateIdleProcInDefendLogic(int delta);
	virtual void OnStateEscapeProcInDefendLogic(int delta);
	virtual void OnStateFollowProcInDefendLogic(int delta);
	virtual void OnStatePickItemProcInDefendLogic(int delta);
	virtual void OnStatePursureProcInDefendLogic(int delta);
	virtual void OnStateAttackProcInDefendLogic(int delta);

	// 休息逻辑下的状态
	//

	uint16_t ChangeIdleStateInFollowLogic(int delta);
	void OnIdleProc(int delta)override;
	void ExitIdleState(uint16_t newStateType)override;

	uint16_t ChangeFollowStateInFollowLogic(int delta) ;
	void OnFollowProc(int delta) override;
	void ExitFollowState(uint16_t newStateType) override;

	uint16_t ChangePickItemStateInFollowLogic(int delta);
	void OnPickItemProc(int delta) override;
	void ExitPickItemState(uint16_t newStateType) override;

	virtual uint16_t ChangeIdleStateInActiveLogic(int delta);
	virtual uint16_t ChangeFollowStateInActiveLogic(int delta);
	virtual	uint16_t ChangePickItemStateInActiveLogic(int delta);
	virtual uint16_t ChangePursureStateInActiveLogic(int delta);
	virtual uint16_t ChangeAttackStateInActiveLogic(int delta);
	virtual uint16_t ChangeAttackIdleStateInActiveLogic(int delta);
	void OnAttackIdleProc(int delta)override;

	uint16_t ChangeIdleStateInDefendLogic(int delta);
	uint16_t ChangeFollowStateInDefendLogic(int delta);
	uint16_t ChangePickItemStateInDefendLogic(int delta);
	uint16_t ChangePursureStateInDefendLogic(int delta);
	uint16_t ChangeAttackStateInDefendLogic(int delta);

	bool ActiveFollow(int delta) override;


	virtual bool HaveOtherBehaviourBeforeActivityStatus(int delta) { return false; };

	uint16_t GetActivityStatus() { return mActivityStatus; }
	void SetActivityStatus(uint16_t status);

	bool IsCanPickItem();
	void SetCanPickItem() { mIsCanPickItem = true; }
	void ResetCanPickItem() { mIsCanPickItem = false; }

	bool IsFollowMasterAttack() { return mFollowMasterAttack; };
	void SetFollowMasterAttack() { mFollowMasterAttack = true; }
	void ResetFollowMasterAttack() { mFollowMasterAttack = false; }

private:
	uint16_t mActivityStatus;              ///宠物状态
	bool     mIsCanPickItem;               ///是否能捡物
	bool     mFollowMasterAttack;          ///是否跟随主人攻击
};