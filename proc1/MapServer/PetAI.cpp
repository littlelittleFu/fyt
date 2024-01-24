#include"stdafx.h"
#include"PetAI.h"

PetAI::PetAI():MonsterAI()
{
	mActivityStatus = pet_activity_status_non;
	mIsCanPickItem = false;
	mFollowMasterAttack = false;
}

PetAI::~PetAI()
{

}

bool PetAI::Init(Pet* pet, DATA::Monster* cfg)
{
	if (nullptr == pet || nullptr == cfg) {
		return false;
	}
	auto type = cfg->MonsterAIType;//新建的类型
	mSelf = pet;

	mVieRange = cfg->VieRange;
	mMovRange = cfg->MovRange;
	mTraRange = cfg->TraRange;
	mBornPosX = 0;
	mBornPosY = 0;
	mTarGUID = 0;
	mTarItem = 0;
	mAttackRange = 0;
    mTarPlayerTime = 0;
	mAIState = ai_state_idle;
	mKeepMaxAttackDising = false;
	mIsPursueAttacking = false;
	mActivityStatus = pet_activity_status_non;
	if (!cfg->SkillCastingRate.empty())
	{
		mCurSkillGroup = cfg->SkillCastingRate[0];
	}
	if (type == all_type_stay_put) mSelf->SetWayFinding(false);

	for (int i = 0; i < ai_schedule_max; ++i) {
		mAISchedule[i] = 0;
		mAIScheduleState[i] = ai_schedule_state_ready;
	}
	mAIScheduleTime[ai_schedule_MovTime] = cfg->MovTime;
	mAIScheduleTime[ai_schedule_MovStepTime] = cfg->StepWait;
	mAIScheduleTime[ai_schedule_MovReadyTime] = cfg->MoveReady;
	mAIScheduleTime[ai_schedule_AttackReadyTime] = cfg->AttackReady;
	mAIScheduleTime[ai_schedule_AttackTime] = cfg->AttackSpeed;
	mAIScheduleTime[ai_schedule_MoveDelayTime] = cfg->MoveSpeed;
	mAIScheduleTime[ai_schedule_BackTime] = cfg->Back;
	mAIScheduleTime[ai_schedule_Type2StayTime] = 1000;
	mAIScheduleTime[ai_schedule_DecreaseHateTime] = DECREASE_HATE_TIME;
	mAIScheduleTime[ai_schedule_MoveStep] = cfg->Step;

    return true;
}

void PetAI::Update(int delta)
{
	auto belong = mSelf->GetMaster();
	if (!belong)
	{
		//销毁
        mSelf->LeaveMap();
		MapRoleMgr::GetInstance()->RemovePet(mSelf->GetGUID());
		return;
	}

	// always update schedule
	AlwaysUpdateSchedule(delta);

	// always run func
	AlwaysRunFunc();

	if (!IsCanEnterState())return;

	HaveOtherBehaviourBeforeActivityStatus(delta);

	ActionByActivityStatus(delta);
}

void PetAI::Stay()
{
	return;
}

void PetAI::JumpToMaster(Map* tarMap)
{
	if (!mSelf)return;
	auto belong = mSelf->GetMaster();
	std::vector<std::pair<uint16_t, uint16_t>> canTakePoint;
	Map* map = nullptr;
	tarMap == nullptr ? map = mSelf->GetCurMap() : map = tarMap;
	auto posx = belong->GetRolePosX();
	auto posy = belong->GetRolePosY();
	auto dir = belong->GetRoleDir();

	for (int range = 1; range <= MAX_FOLLOW_JUMP_RANGE; ++range)
	{
		map->GetAllBlankPointInRange(posx, posy, range, range, canTakePoint);

		int negativeDir = (dir + 4) % dir_max;
		for (auto iter = canTakePoint.begin(); iter != canTakePoint.end();)
		{
			auto curdir = Utility::CalcRelativeDir(iter->first, iter->second, posx, posy);
			if (curdir == negativeDir || curdir == (negativeDir + 1) % dir_max || curdir == (negativeDir + dir_max - 1) % dir_max)
			{
				iter = canTakePoint.erase(iter);
				continue;
			}
			++iter;
		}

		if (!canTakePoint.empty()) break;
	}

	if (!canTakePoint.empty()){
		mSelf->SetRoleDir(dir);
		posx = canTakePoint[0].first;
		posy = canTakePoint[0].second;
	}

	if (tarMap)
		mSelf->JumpMap(tarMap, posx, posy);
	else
		mSelf->JumpMap(posx, posy);

	mTarGUID = 0;

	TRIGGER_EVENT(mSelf, trigger_pet_jump_to_master, mSelf->GetGUIDAsString(), mSelf->GetMasterGUIDAsString());
	return;
}

bool PetAI::JumpToMasterWhenOutOfRange()
{
	if (!mSelf)return false;

	auto belong = mSelf->GetMaster();
	if (!belong)return false;

	auto dis = mSelf->DistanceFromRole(belong);
	if (dis > FOLLOW_RANGE)
	{
		auto rolemove = mSelf->GetRoleMove();
		if (rolemove)
		{
			rolemove->StopMove();
		}
		JumpToMaster();
		return true;
	}
	return false;
}

Role* PetAI::Pet_GetNearestTarget()
{
	if (!mTarGUID)
	{
		auto role = GetNearestRoleByType(role_type_monster);
		if (!role)return nullptr;

		auto dis = mSelf->DistanceFromRole(role);
		if (dis <= mVieRange && dis <= mTraRange)
		{
			mTarGUID = role->GetGUID();
			return role;
		}
		return nullptr;
	}

	auto role = MapRoleMgr::GetInstance()->FindRole(mTarGUID);
	if (!role)
	{
		mTarGUID = 0;
		return nullptr;
	}

	auto roleStatus = role->GetRoleState();
	if (!roleStatus || !roleStatus->CheckAlive())
	{
		mTarGUID = 0;
		return nullptr;
	}

	if (!mSelf->IsInSameMap(role))
	{
		mTarGUID = 0;
		return nullptr;
	}

	auto dis = mSelf->DistanceFromRole(role);
	if (dis <= mVieRange && dis <= mTraRange)
	{
		mTarGUID = role->GetGUID();
		return role;
	}
	return nullptr;
}

bool PetAI::Pet_IsMonsterEnterVieRange()
{
	if (!mSelf)return false;
	auto role = GetNearestRoleByType(role_type_monster);
	if (!role)return false;

	auto dis = mSelf->DistanceFromRole(role);

	if (dis > mVieRange || dis > mTraRange)
	{
		return false;
	}
	return true;
}

void PetAI::SetActivityStatus(uint16_t status)
{
	mActivityStatus = status;
	ResetTarGuid();
	SetAIState(ai_state_idle);

	if (!mSelf)return;
	auto master = mSelf->GetMaster();
	if (!master)return;
	auto toMap = master->GetCurMap();
	if (!toMap)return;
	if (mSelf->GetCurMap() != toMap) {
		JumpToMaster(toMap);
	}
}

bool PetAI::IsCanPickItem()
{
	if (!mIsCanPickItem)return false;

	if (!mSelf) return false;

	auto* player = mSelf->GetMaster();
	if (!player) return false;

	if (player->GetIdleBagCount() == 0) return false;

	auto* map = mSelf->GetCurMap();
	if (!map) return false;

	auto* item = map->GetPetPickableItem(mSelf);

	if (!item) return false;

	if (item->GetCategory() != item_cat_scene) return false;
	return true;
}

void PetAI::SetAIState(uint16_t state)
{
	if (nullptr == mSelf) return;
	if (state == mAIState) return;

	mAIState = state;
	switch (state) {
	case ai_state_idle:
		mTarGUID = 0;
	case ai_state_pursure:
		EnterPursureState();
		break;
	default:
		break;
	}
}

void PetAI::ActionByActivityStatus(int delta)
{
	switch (mActivityStatus)
	{
	case pet_activity_status_follow:
	{
		FollowStatusLogic(delta);
		break;
	}
	case pet_activity_status_active:
	{
		ActiveStatusLogic(delta);
		break;
	}
	case pet_activity_status_defend:
	{
		DefendStatusLogic(delta);
		break;
	}
	case pet_activity_status_stay:
	{
		StayStatusLogic(delta);
		break;
	}
	default:
		break;
	}
}

void PetAI::FollowStatusLogic(int delta)
{
	switch (mAIState) {
	case ai_state_idle:
		OnStateIdleProcInFollowLogic(delta);
		break;
	case ai_state_escape:
		OnStateEscapeProcInFollowLogic(delta);
		break;
	case ai_state_follow:
		OnStateFollowProcInFollowLogic(delta);
		break;
	case ai_state_pickitem:
		OnStatePickItemProcInFollowLogic(delta);
		break;
	default:
		break;
	}
}

void PetAI::ActiveStatusLogic(int delta)
{
	switch (mAIState) {
	case ai_state_idle:
		OnStateIdleProcInActiveLogic(delta);
		break;
	case ai_state_escape:
		OnStateEscapeProcInActiveLogic(delta);
		break;
	case ai_state_follow:
		OnStateFollowProcInActiveLogic(delta);
		break;
	case ai_state_pickitem:
		OnStatePickItemProcInActiveLogic(delta);
		break;
	case ai_state_pursure:
		OnStatePursureProcInActiveLogic(delta);
		break;
	case ai_state_attack:
		OnStateAttackProcInActiveLogic(delta);
		break;
	case ai_state_attack_idle:
		OnStateAttackIdleProcInActiveLogic(delta);
		break;
	default:
		break;
	}
}

void PetAI::DefendStatusLogic(int delta)
{
	switch (mAIState) {
	case ai_state_idle:
		OnStateIdleProcInDefendLogic(delta);
		break;
	case ai_state_escape:
		OnStateEscapeProcInDefendLogic(delta);
		break;
	case ai_state_follow:
		OnStateFollowProcInDefendLogic(delta);
		break;
	case ai_state_pickitem:
		OnStatePickItemProcInDefendLogic(delta);
		break;
	case ai_state_pursure:
		OnStatePursureProcInDefendLogic(delta);
		break;
	case ai_state_attack:
		OnStateAttackProcInDefendLogic(delta);
		break;
	default:
		break;
	}
}

void PetAI::StayStatusLogic(int delta)
{
	Stay();
}

void PetAI::OnStateIdleProcInFollowLogic(int delta)
{
	auto newState = ChangeIdleStateInFollowLogic(delta);
	if (newState) {
		ExitIdleState(newState);
		return;
	}
	OnIdleProc(delta);
}

void PetAI::OnStateEscapeProcInFollowLogic(int delta)
{

}

void PetAI::OnStateFollowProcInFollowLogic(int delta)
{
	auto newState = ChangeFollowStateInFollowLogic(delta);
	if (newState) {
		ExitFollowState(newState);
		return;
	}
	OnFollowProc(delta);
}

void PetAI::OnStatePickItemProcInFollowLogic(int delta)
{
	auto newState = ChangePickItemStateInFollowLogic(delta);
	if (newState) {
		ExitPickItemState(newState);
		return;
	}
	OnPickItemProc(delta);
}

void PetAI::OnStateIdleProcInActiveLogic(int delta)
{
	auto newState = ChangeIdleStateInActiveLogic(delta);
	if (newState) {
		ExitIdleState(newState);
		return;
	}
	OnIdleProc(delta);
}

void PetAI::OnStateEscapeProcInActiveLogic(int delta)
{

}

void PetAI::OnStateFollowProcInActiveLogic(int delta)
{
	auto newState = ChangeFollowStateInActiveLogic(delta);
	if (newState) {
		ExitFollowState(newState);
		return;
	}
	OnFollowProc(delta);
}

void PetAI::OnStatePickItemProcInActiveLogic(int delta)
{
	auto newState = ChangePickItemStateInActiveLogic(delta);
	if (newState) {
		ExitPickItemState(newState);
		return;
	}
	OnPickItemProc(delta);
}

void PetAI::OnStateAttackProcInActiveLogic(int delta)
{
	auto newState = ChangeAttackStateInActiveLogic(delta);
	if (newState) {
		ExitAttackState(newState);
		return;
	}
	OnAttackProc(delta);
}

void PetAI::OnStateAttackIdleProcInActiveLogic(int delta)
{
	auto newState = ChangeAttackIdleStateInActiveLogic(delta);
	if (newState) {
		ExitAttackIdleState(newState);
		return;
	}
	OnAttackIdleProc(delta);
}

void PetAI::OnStatePursureProcInActiveLogic(int delta)
{
	auto newState = ChangePursureStateInActiveLogic(delta);
	if (newState) {
		ExitPursureState(newState);
		return;
	}
	OnPursureProc(delta);
}

void PetAI::OnStateIdleProcInDefendLogic(int delta)
{
	auto newState = ChangeIdleStateInDefendLogic(delta);
	if (newState) {
		ExitIdleState(newState);
		return;
	}
	OnIdleProc(delta);
}

void PetAI::OnStateEscapeProcInDefendLogic(int delta)
{

}

void PetAI::OnStateFollowProcInDefendLogic(int delta)
{
	auto newState = ChangeFollowStateInDefendLogic(delta);
	if (newState) {
		ExitFollowState(newState);
		return;
	}
	OnFollowProc(delta);
}

void PetAI::OnStatePickItemProcInDefendLogic(int delta)
{
	auto newState = ChangePickItemStateInDefendLogic(delta);
	if (newState) {
		ExitPickItemState(newState);
		return;
	}
	OnPickItemProc(delta);
}

void PetAI::OnStatePursureProcInDefendLogic(int delta)
{
	auto newState = ChangePursureStateInDefendLogic(delta);
	if (newState) {
		ExitPursureState(newState);
		return;
	}
	OnPursureProc(delta);
}

void PetAI::OnStateAttackProcInDefendLogic(int delta)
{
	auto newState = ChangeAttackStateInDefendLogic(delta);
	if (newState) {
		ExitAttackState(newState);
		return;
	}
	OnAttackProc(delta);
}


uint16_t PetAI::ChangeIdleStateInFollowLogic(int delta)
{
	if (IsCanPickItem())return ai_state_pickitem;
	if (mSelf->DistanceFromRole(mSelf->GetMaster()) > FOLLOW_DIS)return ai_state_follow;
	return ai_state_none;
}
void PetAI::OnIdleProc(int delta)
{

}
void PetAI::ExitIdleState(uint16_t newStateType)
{
	SetAIState(newStateType);
}

uint16_t PetAI::ChangeFollowStateInFollowLogic(int delta)
{
	if (IsCanPickItem())return ai_state_pickitem;
	if (mSelf->DistanceFromRole(mSelf->GetMaster()) <= FOLLOW_DIS)return ai_state_idle;
	return ai_state_none;
}

void PetAI::OnFollowProc(int delta)
{
	UpdateAISchedule(delta, ai_schedule_MovStepTime);
	if (IsAIStateScheduleIng(ai_schedule_MovStepTime)) return;

	// 开始跟随
	if (IsAIStateScheduleReady(ai_schedule_follow)) {
		StartAISchedule(ai_schedule_follow);
	}

	// 到达步长 间隔 进入步长间隔等待
	if (IsAIStateScheduleEnd(ai_schedule_MoveStep) && IsAIStateScheduleEnd(ai_schedule_MoveDelayTime)) {
		StartAISchedule(ai_schedule_MovStepTime);
		StartAISchedule(ai_schedule_MoveStep);
		return;
	}

	// 成功 步长+1
	if (ActiveFollow(delta)) {
		if (IsAIStateScheduleReady(ai_schedule_MoveStep)) {
			StartAISchedule(ai_schedule_MoveStep);
		}
		UpdateAIScheduleByStep(1, ai_schedule_MoveStep);
	}
}

void PetAI::ExitFollowState(uint16_t newStateType)
{
	int table[4] = { ai_schedule_MovReadyTime, ai_schedule_follow ,
		ai_schedule_MoveStep ,ai_schedule_MovStepTime };
	ResetAISchedule(table, 4);
	SetAIState(newStateType);
}

uint16_t PetAI::ChangePickItemStateInFollowLogic(int delta)
{
	if (!IsCanPickItem())return ai_state_idle;
	return ai_state_none;
}

void PetAI::OnPickItemProc(int delta)
{
	UpdateAISchedule(delta, ai_schedule_MovStepTime);
	if (IsAIStateScheduleIng(ai_schedule_MovStepTime)) return;

	// 到达步长 间隔 进入步长间隔等待
	if (IsAIStateScheduleEnd(ai_schedule_MoveStep) && IsAIStateScheduleEnd(ai_schedule_MoveDelayTime)) {
		StartAISchedule(ai_schedule_MovStepTime);
		StartAISchedule(ai_schedule_MoveStep);
		return;
	}

	auto map = mSelf->GetCurMap();
	if (!map)return;
	auto* item = map->GetPetPickableItem(mSelf);
	if (!item) return ;
	if (item->GetCategory() != item_cat_scene) return ;
	if (mSelf->DistanceFromPos(item->GetPosX(), item->GetPosY()) == 0)
	{
		auto player = mSelf->GetMaster();
		if (nullptr == player)return;
		auto* sceneItem = static_cast<SceneItem*>(item);
		auto* rolePack = player->GetRolePack();
		if (!rolePack) return ;
		rolePack->PickUpItem(sceneItem);
		return;
	}
	// 成功 步长+1
	if (BehaviourMove(delta, item->GetPosX(), item->GetPosY())) {
		if (IsAIStateScheduleReady(ai_schedule_MoveStep)) {
			StartAISchedule(ai_schedule_MoveStep);
		}
		UpdateAIScheduleByStep(1, ai_schedule_MoveStep);
	}
}

void PetAI::ExitPickItemState(uint16_t newStateType)
{
	int table[4] = { ai_schedule_MovReadyTime, ai_schedule_follow ,
		ai_schedule_MoveStep ,ai_schedule_MovStepTime };
	ResetAISchedule(table, 4);
	SetAIState(newStateType);
}

uint16_t PetAI::ChangeIdleStateInActiveLogic(int delta)
{
	if (Pet_IsMonsterEnterVieRange())return ai_state_attack;
	if (IsCanPickItem())return ai_state_pickitem;
	if (mSelf->DistanceFromRole(mSelf->GetMaster()) > FOLLOW_DIS)return ai_state_follow;
	return ai_state_none;
}

uint16_t PetAI::ChangeFollowStateInActiveLogic(int delta)
{
	if (Pet_IsMonsterEnterVieRange())return ai_state_attack;
	if (IsCanPickItem())return ai_state_pickitem;
	if (mSelf->DistanceFromRole(mSelf->GetMaster()) <= FOLLOW_DIS)return ai_state_idle;
	return ai_state_none;
}

uint16_t PetAI::ChangePickItemStateInActiveLogic(int delta)
{
	if (Pet_IsMonsterEnterVieRange())return ai_state_attack;
	if (!IsCanPickItem())return ai_state_idle;
	return ai_state_none;
}

uint16_t PetAI::ChangePursureStateInActiveLogic(int delta)
{
	if (CanHitTarget())return ai_state_attack;       // 进入攻击
	if (LossTarget()) return ai_state_attack_idle;   // 进入攻击待机
	return ai_state_none;
}

uint16_t PetAI::ChangeAttackStateInActiveLogic(int delta)
{
	if (!mTarGUID) return ai_state_attack_idle;   // 进入攻击待机
	if (mIsPursueAttacking)return ai_state_pursure;
	return ai_state_none;
}

uint16_t PetAI::ChangeAttackIdleStateInActiveLogic(int delta)
{
	if (!Pet_IsMonsterEnterVieRange())return ai_state_idle;
	if (mTarGUID) return ai_state_attack; //进入攻击
	return ai_state_none;
}

void PetAI::OnAttackIdleProc(int delta)
{
	auto role = Pet_GetNearestTarget();
	if (!role || !role->CheckAlive())return;
}

uint16_t PetAI::ChangeIdleStateInDefendLogic(int delta)
{
	if (mTarGUID)return ai_state_attack;
	if (IsCanPickItem())return ai_state_pickitem;
	if (mSelf->DistanceFromRole(mSelf->GetMaster()) > FOLLOW_DIS)return ai_state_follow;
	return ai_state_none;
}

uint16_t PetAI::ChangeFollowStateInDefendLogic(int delta)
{
	if (mTarGUID)return ai_state_attack;
	if (IsCanPickItem())return ai_state_pickitem;
	if (mSelf->DistanceFromRole(mSelf->GetMaster()) <= FOLLOW_DIS)return ai_state_idle;
	return ai_state_none;
}

uint16_t PetAI::ChangePickItemStateInDefendLogic(int delta)
{
	if (mTarGUID)return ai_state_attack;
	if (!IsCanPickItem())return ai_state_idle;
	return ai_state_none;
}

uint16_t PetAI::ChangePursureStateInDefendLogic(int delta)
{
	if (CanHitTarget())return ai_state_attack;       // 进入攻击
	if (LossTarget()) return ai_state_idle;   
	return ai_state_none;
}

uint16_t PetAI::ChangeAttackStateInDefendLogic(int delta)
{
	if (!mTarGUID) return ai_state_attack_idle;   // 进入攻击待机
	if (mIsPursueAttacking)return ai_state_pursure;
	return ai_state_none;
}

bool PetAI::ActiveFollow(int delta)
{
	if (nullptr == mSelf)return false;
	auto player = mSelf->GetMaster();
	if (nullptr == player)return false;

	if (BehaviourMove(delta, player->GetRolePosX(), player->GetRolePosY()))return true;
	return false;
}