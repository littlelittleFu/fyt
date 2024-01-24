#pragma once
#include "monster_table.hpp"
#include "Role.h"
#include "AStarPathFinder.h"
#include "MonsterAI_Trigger.h"

#define DECREASE_HATE_TIME 1000       //仇恨值的时间间隔
#define FLASH_TAR_PLAYER 1000         //刷新目标玩家时间间隔
#define MAX_FOLLOW_JUMP_RANGE 3       //宠物跟随跳转最大半径

struct RegisterInfo
{
	std::string params;
	std::string callback;
	RegisterInfo()
	{
		params.clear();
		callback.clear();
	}
};

enum MonsterAI_Attribute
{
	monster_ai_mAvoidTrap        = 1, //躲避陷阱
	monster_ai_mKeepMaxAttackDis = 2, //保持最大攻击距离
	monster_ai_mAttackWithMaster = 3, //跟随主人攻击
	monster_ai_IsFollowMaster    = 4, //跟随主人
	monster_ai_max,
};

enum
{
	ai_state_none,				//普通怪物的AI状态
	ai_state_idle,  			//召唤物、英雄AI状态：待机
	ai_state_attack,			//召唤物、英雄AI状态：攻击
	ai_state_attack_idle,       //召唤物、英雄AI状态：战斗待机
	ai_state_patrol,            //召唤物、英雄AI状态：巡逻
	ai_state_pursure,           //召唤物、英雄AI状态：追击 
	ai_state_escape,            //召唤物、英雄AI状态：逃跑
	ai_state_follow,			//召唤物、英雄AI状态：跟随
	ai_state_pickitem,          //召唤物、英雄AI状态：捡物
	ai_state_reserve_1,         //召唤物、英雄AI状态：预留1
	ai_state_reserve_2,         //召唤物、英雄AI状态：预留2
};

enum ai_schedule{
	// 累加时间
	ai_schedule_MovTime             = 0,                // 活动间隔时间
	ai_schedule_MovStepTime         = 1,                // 步长间隔时间
	ai_schedule_MovReadyTime        = 2,                // 移动准备时间
	ai_schedule_AttackReadyTime     = 3,                // 攻击准备时间
	ai_schedule_AttackTime          = 4,                // 攻击时间
	ai_schedule_MoveDelayTime       = 5,                // 移动等待时间
	ai_schedule_BackTime            = 6,                // 后仰时间
	ai_schedule_Type2StayTime       = 7,                // 大刀守卫攻击回到原点等待时间
	ai_schedule_DecreaseHateTime    = 8,                // 仇恨值递减时间

	// 累加步数
	ai_schedule_MoveStep            = 9,                // 步长间隔

	// 不累加 仅状态
	ai_schedule_idle                = 10,               // 待机状态
	ai_schedule_patrol              = 11,               // 巡逻状态
	ai_schedule_move                = 12,               // 移动状态  
	ai_schedule_pursure             = 13,               // 追击状态
	ai_schedule_attack              = 14,               // 攻击状态
	ai_schedule_escape              = 15,               // 逃跑状态
	ai_schedule_back                = 16,               // 受击状态
	ai_schedule_follow              = 17,               // 跟随状态
	ai_schedule_max,
};

#define     AI_SCHEDULE_DELTAMAX    ai_schedule_DecreaseHateTime
#define     AI_SCHEDULE_STEPMIN     ai_schedule_MoveStep
#define     AI_SCHEDULE_STEPMAX     ai_schedule_MoveStep


enum {
	ai_schedule_state_ready  = 1, // 状态准备
	ai_schedule_state_start,      // 状态开始
	ai_schedule_state_ing,        // 状态中
	ai_schedule_state_end,        // 状态完成

};

enum {
	broadcast_pusure_exit   = 0,   
	broadcast_pursure_enter = 1,   
};

enum {
	broadcast_back_exit = 0,
	broadcast_back_enter = 1,
};

class Monster;
class MonsterAI
{
	using MonsterTraggerBehaviourMap = std::map<monster_behaviour_trigger, RegisterInfo>;
	using MonsterAttributeMap = std::map<MonsterAI_Attribute, bool>;

public:
	MonsterAI();
	virtual ~MonsterAI();

	bool Init(Monster* monster, DATA::Monster* cfg);
	void SetBornPos(uint16_t posX, uint16_t posY) { mBornPosX = posX; mBornPosY = posY; }
	void SetTmpStayPos(uint16_t posX, uint16_t posY) { mTmpStayPosX = posX; mTmpStayPosY = posY; }
	void RegisterBehaviour(const CLuaObject& info);                                     // 通用怪物可注册行为
	void RegisterAttribute(const CLuaObject& info);                                     // 通用怪物可注册属性
	void RemoveBehaviour(uint16_t behaviourID);
	MonsterTraggerBehaviourMap& GetAIBehaviourMap() { return mBehaviorMap; };

    const std::string & GetScriptName();


	bool CheckSelfState();
	void ApplySkill();

	void SetTarGuid(uint64_t targuid) { mTarGUID = targuid; }
	uint64_t GetTarGuid() { return mTarGUID; };
	void ResetTarGuid() { mTarGUID = 0; }


	void SetBackStatus();
	void SetIsPursueAttackingStatus(bool ref);
	bool IsPursureAttackingStatus() { return mIsPursueAttacking; }

	void NotifyAroundPlayers_PursureStatusChanged(Role* role, ProtoMS_MonsterPursureAttackingNtf& info);
	void NotifyAroundPlayers_BackStatusChanged(Role* role, ProtoMS_MonsterBackNtf& info);


protected:
	bool GetWalkablePos(uint16_t& dir, uint16_t tarRoleposX,uint16_t tarRoleposY, uint16_t& tarX, uint16_t& tarY);
	void GetAroundTarget(uint16_t tarRoleposX, uint16_t tarRoleposY, std::vector<std::pair<uint16_t, uint16_t>>& canTakePos);
	void GetSelfAroundTarget(uint16_t tarRoleposX, uint16_t tarRoleposY, std::vector < std::pair<uint16_t, uint16_t>>& canTakePos);
	bool FindPathByDir(uint16_t curX, uint16_t curY, uint16_t& dir, uint16_t& tarX, uint16_t& tarY);
	bool FindPathByDis(uint16_t posX, uint16_t posY, uint16_t IndirectTarPosX, uint16_t IndirectTarPosY, uint16_t& dir, uint16_t& tarX, uint16_t& tarY);
	bool FindPathByAStar(uint16_t posX, uint16_t posY, uint16_t IndirectTarPosX, uint16_t IndirectTarPosY, uint16_t& dir, uint16_t& tarX, uint16_t& tarY, uint16_t max_path = MAX_PTH, uint16_t Max_Depth = MAX_DEPTH);
	bool TryMoveToTarget(uint16_t tarX, uint16_t tarY);
    bool CanHitTarget();
	bool LossTarget();

public:
	bool IsInVieRange(uint64_t tarGuid);                    //是否在视野范围内
	bool IsInTraRange(uint64_t tarGuid);                    //是否在追踪范围内
	bool IsInTraRange(uint16_t dis) { return dis <= mTraRange; };   //是否进入追踪距离
	bool IsInMoveRange(uint16_t x, uint16_t y);             //是否在活动范围内
	bool IsTrapPoint(uint16_t posx, uint16_t posy);
    bool IsAIAttrSet(MonsterAI_Attribute attr);
	void SetCurAttackDir();
	void AddSkill(uint32_t skillID, uint32_t Weight);
	void RemoveSkill(uint32_t skillID);
	std::vector<std::pair<int, int>>& GetCurSkillGroup() { return mCurSkillGroup; };
	void UpdateBiaocheAIState();

	//trigger condition
	bool FindTarget( std::string params);
	bool TargetHP(std::string params);
	bool SelfHP(std::string params);
	bool OnDie(std::string params);
	bool CurDistance(std::string params);
	bool TargetObj(std::string params);
	bool HarmedBySpecialSkill(std::string params);

	//trigger action
	void SwapSkillGroup(uint16_t id);
	void UseSpecialSkill(uint32_t skillid) { mCurSkillID = skillid; mTriggerSpecialSkill = true; }
	void Escape(uint16_t dis);

	//add action
	bool GetAssassinatePos(uint16_t x, uint16_t y, std::pair<uint16_t, uint16_t>& pos);   //寻找刺杀位
	bool KeepMaxAttackDis();                                // 保持最大攻击距离

protected:
	Role* GetNearestRoleByType(uint8_t roleType);           //获取最近的角色
	Role* Monster_GetTarRoleInRange();                      //获取视野内最近的目标
	Role* Monster_GetFlushTarRole(int delta);               //获取刷新后的目标
	uint16_t GetSkillNumber();                              //根据权重获取技能
	uint16_t GetMaxDisSkill();                              //获取施法距离最远的技能
	bool GetMaxDisPoint();                                  //获取反方向最近的点

	///condition
	bool IsRoleEnterVieRange();                             //是否有目标进入视野
	bool IsHateValueRoleInTraRange();                       //是否有仇恨值的角色进入追击范围
	bool IsEnterAttackState();                              //是否进入攻击状态


public:
	uint16_t GetAIState() { return mAIState; }
	virtual void Update(int delta);


	bool IsAttacking() { return mAIScheduleState[ai_schedule_AttackTime] == ai_schedule_state_ing; };
	bool IsMoving() { return mAIScheduleState[ai_schedule_MoveDelayTime] == ai_schedule_state_ing; };
	bool IsBacking() { return mAIScheduleState[ai_schedule_BackTime] == ai_schedule_state_ing; };
	virtual void SetAIState(uint16_t state);
	void AlwaysUpdateSchedule(int delta);
	void AlwaysRunFunc();
	bool IsCanEnterState();

	void UpdateAISchedule(int delta, int* table, int num);
	void UpdateAISchedule(int delta, uint16_t idx);
	void UpdateAIScheduleByStep(int step, int* table, int num);
	void UpdateAIScheduleByStep(int step, uint16_t idx);
	void ResetAISchedule(int* table, int num);
	void ResetAISchedule(uint16_t idx) { mAISchedule[idx] = 0; mAIScheduleState[idx] = ai_schedule_state_ready; };
	void StartAISchedule(int* table, int num);
	void StartAISchedule(uint16_t idx) { mAIScheduleState[idx] = ai_schedule_state_start;};
	bool IsAIStateScheduleReady(int* table, int num);
	bool IsAIStateScheduleReady(uint16_t idx) { return mAIScheduleState[idx] == ai_schedule_state_ready; };
	bool IsAIStateScheduleStart(uint16_t idx) {return mAIScheduleState[idx] == ai_schedule_state_start;}
	bool IsAIStateScheduleIng(uint16_t idx) { return mAIScheduleState[idx] == ai_schedule_state_ing; };
	bool IsAIStateScheduleEnd(uint16_t idx) { return mAIScheduleState[idx] == ai_schedule_state_end; };
	void ChangeAIStateScheduleState(uint16_t idx, uint16_t state) { mAIScheduleState[idx] = state; };

	// 状态总入口
	void OnStateIdleProc(int delta); 
	void OnStatePatrolProc(int delta);
	void OnStatePursureProc(int delta);
	void OnStateAttackIdleProc(int delta);
	void OnStateAttackProc(int delta);
	void OnStateEscapeProc(int delta);
	virtual void OnStateFollowProc(int delta);
	virtual void OnStatePickItemProc(int delta);
	virtual void OnStateReserve1(int delta) {};
	virtual void OnStateReserve2(int delta) {};

	// 状态逻辑
	virtual uint16_t ChangeIdleState(int delta);                      //更新idle状态
	virtual void OnIdleProc(int delta);                               //执行idle状态行为
	virtual void ExitIdleState(uint16_t newStateType);                //退出idle状态

	virtual uint16_t ChangePatrolState(int delta);
	virtual void OnPatrolProc(int delta);
	virtual void ExitPatrolState(uint16_t newStateType);

	virtual uint16_t ChangePursureState(int delta);
	virtual void OnPursureProc(int delta);
	virtual void ExitPursureState(uint16_t newStateType);
	virtual void EnterPursureState();

	virtual uint16_t ChangeAttackIdleState(int delta);
	virtual void OnAttackIdleProc(int delta);
	virtual void ExitAttackIdleState(uint16_t newStateType);

	virtual uint16_t ChangeAttackState(int delta);
	virtual void OnAttackProc(int delta);
	virtual void ExitAttackState(uint16_t newStateType);

	uint16_t ChangeEscapeState(int delta);
	void OnEscapeProc(int delta);
	void ExitEscapeState(uint16_t newStateType);

	virtual uint16_t ChangeFollowState(int delta) { return ai_state_none; };
	virtual void OnFollowProc(int delta) {};
	virtual void ExitFollowState(uint16_t newStateType) {};

	virtual uint16_t ChangePickItemState(int delta) { return ai_state_none; };
	virtual void OnPickItemProc(int delta) {};
	virtual void ExitPickItemState(uint16_t newStateType) {};

	// active
	virtual bool ActiveAttack(int delta);
	virtual bool ActivePatrol(int delta);
	virtual bool ActivePursure(int delta);
	virtual bool ActiveEscape(int delta);
	virtual bool ActiveFollow(int delta);

	// behaviour
	bool BehaviourMove(int delta, uint16_t x, uint16_t y);
	virtual bool BehaviourAttack(int delta);

	void SendPursureStateToCl(uint16_t state);
	void SendBackStateToCl(uint16_t state);

	void UpdateBackState(int delta);
	void UpdateHatedValue(int delta);

protected:
    uint32_t mAISchedule[ai_schedule_max]       = {0};      // 当前任务时间
    uint32_t mAIScheduleTime[ai_schedule_max]   = {0};      // 固定任务时间
    uint16_t mAIScheduleState[ai_schedule_max]  = {0};      // 当前任务状态 



protected:
	Monster*		            mSelf                       = nullptr;
	uint16_t		            mAIState                    = ai_state_idle;

	uint16_t		            mVieRange                   = 0;                    /// 视野
	uint16_t		            mMovRange                   = 0;					/// 活动范围
	uint16_t		            mTraRange                   = 0;                    /// 追踪距离
	uint16_t                    mAttackRange                = 0;                    /// 攻击范围
	uint16_t                    mCurSkillID                 = 0;                    /// 当前技能id
	std::vector<std::pair<int, int>> mCurSkillGroup;                                /// 当前技能组
	bool                        mTriggerSpecialSkill        = false;                /// 是否已经触发特定技能
	bool                        mTriggerEscape              = false;                /// 触发逃跑
	bool                        mKeepMaxAttackDising        = false;                /// 是否保持向最大距离移动
	bool                        mIsPursueAttacking          = false;                /// 是否在追击
	uint16_t                    mTarX                       = 0;
	uint16_t                    mTarY                       = 0;
	uint16_t                    mEscapeX                    = 0;
	uint16_t                    mEscapeY                    = 0;
	uint16_t		            mBornPosX                   = 0;
	uint16_t		            mBornPosY                   = 0;
	uint16_t                    mTmpStayPosX                = 0;
	uint16_t                    mTmpStayPosY                = 0;
	uint64_t		            mTarGUID                    = 0;
    uint64_t                    mTarItem                    = 0;   
	uint32_t                    mTarPlayerTime              = 0;

	pursue_attack_type          mAttackPAursuitType;
	MonsterTraggerBehaviourMap  mBehaviorMap;                                       /// 特殊行为表
	MonsterAttributeMap         mAttributeMap;                                      /// 注册属性表
	
};
