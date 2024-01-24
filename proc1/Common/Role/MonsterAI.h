#pragma once
#include "monster_table.hpp"
#include "Role.h"
#include "AStarPathFinder.h"
#include "MonsterAI_Trigger.h"

#define DECREASE_HATE_TIME 1000       //���ֵ��ʱ����
#define FLASH_TAR_PLAYER 1000         //ˢ��Ŀ�����ʱ����
#define MAX_FOLLOW_JUMP_RANGE 3       //���������ת���뾶

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
	monster_ai_mAvoidTrap        = 1, //�������
	monster_ai_mKeepMaxAttackDis = 2, //������󹥻�����
	monster_ai_mAttackWithMaster = 3, //�������˹���
	monster_ai_IsFollowMaster    = 4, //��������
	monster_ai_max,
};

enum
{
	ai_state_none,				//��ͨ�����AI״̬
	ai_state_idle,  			//�ٻ��Ӣ��AI״̬������
	ai_state_attack,			//�ٻ��Ӣ��AI״̬������
	ai_state_attack_idle,       //�ٻ��Ӣ��AI״̬��ս������
	ai_state_patrol,            //�ٻ��Ӣ��AI״̬��Ѳ��
	ai_state_pursure,           //�ٻ��Ӣ��AI״̬��׷�� 
	ai_state_escape,            //�ٻ��Ӣ��AI״̬������
	ai_state_follow,			//�ٻ��Ӣ��AI״̬������
	ai_state_pickitem,          //�ٻ��Ӣ��AI״̬������
	ai_state_reserve_1,         //�ٻ��Ӣ��AI״̬��Ԥ��1
	ai_state_reserve_2,         //�ٻ��Ӣ��AI״̬��Ԥ��2
};

enum ai_schedule{
	// �ۼ�ʱ��
	ai_schedule_MovTime             = 0,                // ����ʱ��
	ai_schedule_MovStepTime         = 1,                // �������ʱ��
	ai_schedule_MovReadyTime        = 2,                // �ƶ�׼��ʱ��
	ai_schedule_AttackReadyTime     = 3,                // ����׼��ʱ��
	ai_schedule_AttackTime          = 4,                // ����ʱ��
	ai_schedule_MoveDelayTime       = 5,                // �ƶ��ȴ�ʱ��
	ai_schedule_BackTime            = 6,                // ����ʱ��
	ai_schedule_Type2StayTime       = 7,                // �����������ص�ԭ��ȴ�ʱ��
	ai_schedule_DecreaseHateTime    = 8,                // ���ֵ�ݼ�ʱ��

	// �ۼӲ���
	ai_schedule_MoveStep            = 9,                // �������

	// ���ۼ� ��״̬
	ai_schedule_idle                = 10,               // ����״̬
	ai_schedule_patrol              = 11,               // Ѳ��״̬
	ai_schedule_move                = 12,               // �ƶ�״̬  
	ai_schedule_pursure             = 13,               // ׷��״̬
	ai_schedule_attack              = 14,               // ����״̬
	ai_schedule_escape              = 15,               // ����״̬
	ai_schedule_back                = 16,               // �ܻ�״̬
	ai_schedule_follow              = 17,               // ����״̬
	ai_schedule_max,
};

#define     AI_SCHEDULE_DELTAMAX    ai_schedule_DecreaseHateTime
#define     AI_SCHEDULE_STEPMIN     ai_schedule_MoveStep
#define     AI_SCHEDULE_STEPMAX     ai_schedule_MoveStep


enum {
	ai_schedule_state_ready  = 1, // ״̬׼��
	ai_schedule_state_start,      // ״̬��ʼ
	ai_schedule_state_ing,        // ״̬��
	ai_schedule_state_end,        // ״̬���

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
	void RegisterBehaviour(const CLuaObject& info);                                     // ͨ�ù����ע����Ϊ
	void RegisterAttribute(const CLuaObject& info);                                     // ͨ�ù����ע������
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
	bool IsInVieRange(uint64_t tarGuid);                    //�Ƿ�����Ұ��Χ��
	bool IsInTraRange(uint64_t tarGuid);                    //�Ƿ���׷�ٷ�Χ��
	bool IsInTraRange(uint16_t dis) { return dis <= mTraRange; };   //�Ƿ����׷�پ���
	bool IsInMoveRange(uint16_t x, uint16_t y);             //�Ƿ��ڻ��Χ��
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
	bool GetAssassinatePos(uint16_t x, uint16_t y, std::pair<uint16_t, uint16_t>& pos);   //Ѱ�Ҵ�ɱλ
	bool KeepMaxAttackDis();                                // ������󹥻�����

protected:
	Role* GetNearestRoleByType(uint8_t roleType);           //��ȡ����Ľ�ɫ
	Role* Monster_GetTarRoleInRange();                      //��ȡ��Ұ�������Ŀ��
	Role* Monster_GetFlushTarRole(int delta);               //��ȡˢ�º��Ŀ��
	uint16_t GetSkillNumber();                              //����Ȩ�ػ�ȡ����
	uint16_t GetMaxDisSkill();                              //��ȡʩ��������Զ�ļ���
	bool GetMaxDisPoint();                                  //��ȡ����������ĵ�

	///condition
	bool IsRoleEnterVieRange();                             //�Ƿ���Ŀ�������Ұ
	bool IsHateValueRoleInTraRange();                       //�Ƿ��г��ֵ�Ľ�ɫ����׷����Χ
	bool IsEnterAttackState();                              //�Ƿ���빥��״̬


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

	// ״̬�����
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

	// ״̬�߼�
	virtual uint16_t ChangeIdleState(int delta);                      //����idle״̬
	virtual void OnIdleProc(int delta);                               //ִ��idle״̬��Ϊ
	virtual void ExitIdleState(uint16_t newStateType);                //�˳�idle״̬

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
    uint32_t mAISchedule[ai_schedule_max]       = {0};      // ��ǰ����ʱ��
    uint32_t mAIScheduleTime[ai_schedule_max]   = {0};      // �̶�����ʱ��
    uint16_t mAIScheduleState[ai_schedule_max]  = {0};      // ��ǰ����״̬ 



protected:
	Monster*		            mSelf                       = nullptr;
	uint16_t		            mAIState                    = ai_state_idle;

	uint16_t		            mVieRange                   = 0;                    /// ��Ұ
	uint16_t		            mMovRange                   = 0;					/// ���Χ
	uint16_t		            mTraRange                   = 0;                    /// ׷�پ���
	uint16_t                    mAttackRange                = 0;                    /// ������Χ
	uint16_t                    mCurSkillID                 = 0;                    /// ��ǰ����id
	std::vector<std::pair<int, int>> mCurSkillGroup;                                /// ��ǰ������
	bool                        mTriggerSpecialSkill        = false;                /// �Ƿ��Ѿ������ض�����
	bool                        mTriggerEscape              = false;                /// ��������
	bool                        mKeepMaxAttackDising        = false;                /// �Ƿ񱣳����������ƶ�
	bool                        mIsPursueAttacking          = false;                /// �Ƿ���׷��
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
	MonsterTraggerBehaviourMap  mBehaviorMap;                                       /// ������Ϊ��
	MonsterAttributeMap         mAttributeMap;                                      /// ע�����Ա�
	
};
