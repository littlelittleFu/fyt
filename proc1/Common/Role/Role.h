#pragma once

#include "Object.h"
#include "RoleType.h"
#include "RoleAttr.h"
#include "RoleState.h"
#include "RoleMove.h"
#include "RoleSkill.h"
#include "RoleBuff.h"
#include "RolePack.h"
#include "RoleAvatar.h"
#include "RoleRelation.h"
#include "RoleTask.h"
#include "RoleTeam.h"
#include "RoleVip.h"
#include "IObserver.h"
#include "ProtoMS.h"
#include "ProtoGS.h"
#include "monster_table.hpp"
#include "role_table.hpp"
#include "npc_table.hpp"
#include "FightInfoMgr.h"


enum
{
    attr_need_update_flag,
    skill_need_update_flag,
    buff_need_update_flag,
    quest_need_update_flag,
    move_need_update_flag,
    event_map_need_update_flag,
    ai_need_update_flag,
    monster_excl_need_update_flag,              // 怪物归属
    player_pk_need_update_flag,
    summon_monster_need_udpate_flag,
    custvar_need_update_flag,
    invalid_role_need_update_flag,              // 需要删除
	pet_monster_need_udpate_flag,
	fight_info_need_update_flag,
	title_need_update_flag,
    need_update_flag_num

};

enum class RoleInfoChangeKey
{
	rick_name = 0,			// 如物品名,角色名
	rick_stall_name = 1,	// 摆摊名
	rick_alias = 2,	// 别名
	rick_num
};

class Map;
class SceneItem;
class Role : public Object, public IObserver, public EventTrigger
{
public:
	Role(uint32_t type);
	virtual ~Role();

	// Object
	virtual void Update(int32_t delta) override;
	// IObserver
	void Notify(ISubject* sub) override;

    // EventTrigger virtual functions override
    void OnRemoveTrigger() override;

	// virtual
	virtual void StartMove(uint16_t x, uint16_t y);
	virtual void EndMove(bool success);

	virtual bool TargetCanSelect(Role* tar) { return true; }
	// role action
	virtual void AddInvisibleEffect();
	virtual void CheckJump(void) {};
	virtual void NotifyJump(const char*, uint16_t pox, uint16_t poy, uint16_t type) {};
	virtual bool JumpMap(Map*tarMap, uint16_t x, uint16_t y);
	bool RandJumpMap(uint64_t mapGuid);

	virtual void OnRoleEnter(Role* role) {};
	virtual void OnRoleLeave(Role* role) {};
	virtual void OnRoleMove(Role* role) {};
	virtual void OnRoleExit(Role* role);
	virtual void OnRoleUpdateHPMP(int32_t nHP, int32_t nMP) {};
	virtual void OnRoleBeAttacked(uint64_t killerGUID) {};
	virtual void OnRoleDie(uint64_t killerGUID);
	virtual void OnlyUpdateAppearNtf(Role* role) {};
	// buff
	virtual void OnAddBuff(const BUFF_INFO& pBuffInfo, uint16_t nActorSkill);
	virtual void OnUpdateBuff(const BUFF_INFO& pBuffInfo, uint16_t nActorSkill);
	virtual void OnRemoveBuff(uint16_t nBuffID, uint64_t nActorID);
	// map
	virtual void OnEnterMap(Map* map) { mCurMap = map; }
	virtual void OnLeaveCurMap() { mCurMap = nullptr; }
	//Item
	virtual bool IsCanUseItem(uint64_t itemGUID) { return true; }
	virtual void OnItemAppear(SceneItem* item) {}
	virtual void OnItemDisappear(SceneItem* item) {}
	// msg
	virtual void SendRoleCustVarNtf(ProtoMS_RoleCustVarNtf& ntf) {};
	virtual void SendRoleDynAttrsNtf(ProtoMS_RoleDynAttrsNtf& ntf) {};
	virtual void SendRoleDirChangeNtf(Role* role, ProtoGS_TurnNtf& ntf) {};
	virtual void SendRoleDieNtf(Role* role, ProtoMS_ObjDieNtf& ntf) {};
	virtual void SendRoleObjDisappearNtf(ProtoMS_ObjDisappearNtf& ntf) {};
	virtual void SendRoleItemAppearNtf(ProtoMS_ItemAppearNtf4& ntf) {};
	virtual void SendRoleNameChangeNtf(ProtoGS_PlayerSetNameNtf& ntf) {};
	virtual void SendRoleWearTitleNtf(ProtoGS_TitleWearNtf& ntf) {};
	virtual void SendRoleUnWearTitleNtf(ProtoGS_TitleUnWearNtf& ntf) {};
    virtual void SendAppearNtf(Role *toRole) {}
    virtual void SendRoleAppNtf(Role *toRole) {}
	virtual void SendEffectAppearNtf(ProtoMS_EffectAppearNtf& ntf) {};
	virtual void SendEffectDisAppearNtf(ProtoMS_EffectDisAppearNtf& ntf) {};

    void ApplySkillOnTarget(uint16_t skillID, uint64_t targetGUID, uint16_t clientSN);
    void ApplySkillOnGrid(uint16_t skillID, uint64_t targetGUID, uint16_t x, uint16_t y,
        uint16_t clientSN, uint8_t extraInfo = 0);

///////////////////////////////////////////
	void Init();

    uint32_t GetType() { return mType; }
    void SetType(uint32_t type) { mType = type; }
    bool IsPlayer() { return mType == role_type_player; }
	bool IsStallDummy() { return mType == role_type_stall_dummy; }
    bool IsMonster() { return mType == role_type_monster; }
    bool IsNpc() { return mType == role_type_npc; }
	bool IsPet() { return mType == role_type_pet; }
    bool IsPlayerDoplganr() { return mType == role_type_player_doplganr; }
    virtual bool IsBiaoChe() { return false; }
    virtual bool IsInSameTeam(Role *role) { return false; }
    virtual bool IsInSameGuild(Role *role) { return false; }
    virtual bool IsInSameCamp(Role *role) { return false; }
    virtual bool IsGrayName() { return false; }
    virtual bool IsRedName() { return false; }
    bool IsGrayOrRedName() { return IsGrayName() || IsRedName(); }
    virtual bool IsMyPet(Role *role) { return false; }
    virtual bool IsMyDoplganr(Role *role) { return false; }
    virtual bool IsMyBiaoChe(Role *role) { return false; }
    bool IsMySummon(Role *role) { return IsMyPet(role) || IsMyDoplganr(role); }
    bool IsMyServant(Role *role) { return IsMyPet(role) || IsMyDoplganr(role) || IsMyBiaoChe(role); }

	void ChangeName(std::string name);
	void ChangeAlias(std::string name);
	void SetInvalid();
	inline bool IsInvalid() { return mInvalid; }

	void SetCamp(uint8_t camp) { mCamp = camp; }
	uint8_t GetCamp() { return mCamp; }

	Map* GetCurMap() { return mCurMap; };
    const std::string & GetCurMapKeyName();
    bool IsInSameMap(Role *role);
    bool IsInSameLine(Role *role);
    void LeaveMap();

	void SetRoleInfo(const std::string& pInfo) { info = pInfo; }
	const std::string& GetRoleInfoAck() { return GetInfo(); }
	std::string& GetInfo(void) { return info; };

    const std::string & GetScriptName() { return mScriptName; };
	virtual void SetScriptName(const std::string& scriptName) { mScriptName = scriptName; }

	void SetSkillProp(uint16_t skillID, uint16_t propType, const std::string& cfg);
	bool GetSkillProp(uint16_t skillID, uint16_t propType);

	// 属性
	int32_t SetRoleProp(int32_t prop, int32_t value);
	void SetRoleProp64(int32_t prop, int64_t value, const log_params& lp);
    int32_t GetRoleProp(int32_t prop);
	int64_t GetRoleProp64(int32_t prop);
	int32_t AddRoleProp(int32_t prop, int32_t value);
	void AddRoleProp64(int32_t prop, int64_t value, const log_params& lp);
    bool CheckProp64Amount(int32_t prop, const std::string &needNum);
	void SetUpGradeExp(uint64_t exp);
	uint64_t GetUpGradeExp(void);
    void SetRolePos(uint16_t x, uint16_t y);
	void SetRolePosNoEvent(uint16_t x, uint16_t y);
	void SetRolePosNoTakeGrid(uint16_t x, uint16_t y);
    uint16_t GetRolePosX();
    uint16_t GetRolePosY();
    void SetRoleDir(uint8_t dir);
    uint8_t GetRoleDir();
    bool IsInSafeRegion();
    // check
	bool CheckAlive();
	virtual bool CheckCross();
    virtual bool CheckTakeGrid(uint16_t x, uint16_t y) { return false; }
    virtual int32_t GetAttackMode() { return GetRoleProp(role_atk_mode); }
	// timer
	uint32_t AddLuaTimer(uint32_t interval, bool loop, const std::string& call_back);
	uint32_t AddLuaTimerEx(uint32_t interval, bool loop, CLuaObject call_back);
	void RemoveLuaTimer(uint32_t id);
	// buff
	bool AddBuffByRole(uint16_t nBuffID, Role* pActor, uint16_t nSkillID, std::string attrStr = "", uint32_t time = 0);
	bool RemoveBuff(uint16_t nBuffID);
	bool RemoveBuffWithActorID(uint16_t nBuffID, std::string sActorID);
	void RemoveBuffWhenDie();
	void RemoveBuffWhenMove();
	bool BuffExist(uint16_t nBuffID);
	bool BuffExistByGroupID(uint16_t buffGroupID);
    std::vector<uint16_t> GetValidBuffIDList();

	int64_t GetBuffLeftTime(uint16_t buffID);
	uint16_t GetBuffStack(uint16_t buffID);
	void UpdateBuffStack(uint16_t buffID, int16_t diff);
	std::string GetBuffActorGuid(uint16_t buffID);
    const std::string & GetBuffActorName(const std::string& actorGuid, uint16_t buffID);

	uint8_t     GetBuffActorJob(const std::string& actorGuid, uint16_t buffID);
	uint32_t    GetBuffActorLevel(const std::string& actorGuid, uint16_t buffID);
	uint16_t    GetBuffActorSkill(const std::string& actorGuid, uint16_t buffID);
	// ass
	void TakeGrid();
	void ReleaseGrid();
	uint16_t DistanceFromRole(Role* role);
    uint16_t DistanceFromPos(uint16_t x, uint16_t y);
	Point PosRelativeToCurRole(uint16_t x, uint16_t y);
	void UpdateHPMP(int32_t hpAmount, int32_t mpAmount, uint8_t type, bool notify);
    uint16_t MoveTo(uint16_t x,uint16_t y, uint8_t type = 0);
	// 当前角色被攻击
	void AttackedByRole(AttackResult& res);

	void NotifyAroundPlayers_SpellNtf(const AttackResults &atkResults, uint16_t skillID, uint16_t x, uint16_t y, uint8_t extraInfo = 0);
	void NotifyAroundPlayers_SpellNtf(uint64_t targetGUID, uint16_t skillID, uint16_t x, uint16_t y, uint8_t extraInfo = 0);

    std::vector<RoleItem *> GetAllEquipments();
	void SetCalculateAttribute(bool CalculateAttribute) { mCalculateAttribute = CalculateAttribute; }

////////////////////////////////////////////////////////////////////////////////
// Event Callback

public:
    using       EventHandler    = std::function<void()>;
    using       EventHandlerMap = std::map<uint32_t, EventHandler>;

    uint32_t    AddEventHandler_RoleExit(EventHandler handler);
    void        RemoveEventHandler_RoleExit(uint32_t handlerID);

    uint32_t    AddEventHandler_RoleDie(EventHandler handler);
    void        RemoveEventHandler_RoleDie(uint32_t handlerID);

    uint32_t    AddEventHandler_StartMove(EventHandler handler);
    void        RemoveEventHandler_StartMove(uint32_t handlerID);

    uint32_t    AddEventHandler_RoleOnline(EventHandler handler);
    void        RemoveEventHandler_RoleOnline(uint32_t handlerID);

    uint32_t    AddEventHandler_RoleOffline(EventHandler handler);
    void        RemoveEventHandler_RoleOffline(uint32_t handlerID);

protected:
    uint32_t    AddEventHandlerToMap(EventHandlerMap &handlerMap, EventHandler handler);
    void        RemoveEventHandlerFromMap(EventHandlerMap &handlerMap, uint32_t handlerID);
    void        ApplyEventHandlersInMap(EventHandlerMap &handlerMap);

    void        ApplyEventHandlers_RoleExit();
    void        ApplyEventHandlers_RoleDie();
    void        ApplyEventHandlers_StartMove();
    void        ApplyEventHandlers_RoleOnline();
    void        ApplyEventHandlers_RoleOffline();

private:
    EventHandlerMap     mHandlersRoleExit;
    EventHandlerMap     mHandlersRoleDie;
    EventHandlerMap     mHandlersStartMove;
    EventHandlerMap     mHandlersRoleOnline;
    EventHandlerMap     mHandlersRoleOffline;

////////////////////////////////////////////////////////////////////////////////

public:
    void        SetNeedUpdateFlag(std::size_t pos);
    void        ResetNeedUpdateFlag(std::size_t pos);

private:
    std::bitset<need_update_flag_num> mNeedUpdateFlags;

////////////////////////////////////////////////////////////////////////////////

protected:
	void NotifyAroundPlayers_AddBuff();
	void NotifyAroundPlayers_AddBuff(const std::list<BUFF_INFO>& list);
	void NotifyOnePlayer_AddBuff(Role* pRoleToNotify, const uint64_t& nRoleIDSrc, const std::list<BUFF_INFO>& list);
	void NotifyOnePlayer_AddBuff(Role* pRoleToNotify, Role* pRoleBuffSrc);
	void NotifyAroundPlayers_RemoveBuff(uint16_t nBuffID);
	/////////////////////////////////////////////
public:
	void NotifyAroundPlayers_Attacked(AttackResult& res);
	void NotifyPlayer_RoleDie(Role* pRoleToNotify, const AttackResult& res);
	void NotifyAroundPlayers_UpdateHPMP(int32_t hpAmount, int32_t hptotal, int32_t mpAmount, int32_t mpTotal, uint8_t type);
	void NotifyAroundPlayers_RoleInfoChange(uint16_t type, const string& value);

public:
	RoleAction*		GetAction(int actionType);
	RoleAttr*		GetRoleAttr()		{ return mRoleAttr; };
	RoleState*		GetRoleState()		{ return mRoleState; };
	RoleSkill*		GetRoleSkill()		{ return mRoleSkill; };
	RoleMove*		GetRoleMove()		{ return mRoleMove; };
	RoleBuff*		GetRoleBuff()		{ return mRoleBuff; };
	RolePack*		GetRolePack()		{ return mRolePack; };
	RoleAvatar*		GetRoleAvatar()		{ return mRoleAvatar; };
	RoleRelation*	GetRoleRelation()	{ return mRoleRelation; };
	RoleTask*		GetRoleTask()		{ return mRoleTask; };
	RoleTeam*		GetRoleTeam()		{ return mRoleTeam; };
	RoleVip*		GetRoleVip()		{ return mRoleVip; };


	FightInfo& GetFightInfo() { return mFightInfo; };
	void OnGetBuffAck(const BUFF_INFO_DB* pBuffInfo, uint16_t num);
	void SendUpdateTopList();

	void UpgradeUpdateRoleProp(DATA::Role* preCfg, DATA::Role* curCfg);
	void InitRoleProp(DATA::Role* cfg);
	void InitRoleProp(DATA::Npc* cfg);
	void InitRoleProp(DATA::Monster* cfg);

	int64_t GetMoveTimeEnd() { return m_MoveEnd;}
	void SetMoveTimeEnd(int64_t n_time) { m_MoveEnd = n_time;}

	uint32_t temp_attr_type = 0;   // 1 buff  2 title  3 item .....
	uint32_t temp_attr_id = 0;

protected:
	uint32_t mType;
	bool mInvalid;

    RoleAction      *mRoleAction[role_action_max] = {nullptr};
	RoleAttr        *mRoleAttr      = nullptr;
	RoleState       *mRoleState     = nullptr;
	RoleSkill       *mRoleSkill     = nullptr;
	RoleMove        *mRoleMove      = nullptr;
	RoleBuff        *mRoleBuff      = nullptr;
	RolePack        *mRolePack      = nullptr;
	RoleAvatar      *mRoleAvatar    = nullptr;
	RoleRelation    *mRoleRelation  = nullptr;
	RoleTask        *mRoleTask      = nullptr;
	RoleTeam        *mRoleTeam      = nullptr;
	RoleVip         *mRoleVip       = nullptr;

	Map             *mCurMap        = nullptr;
	std::string mScriptName;
	uint8_t mCamp;
	int64_t			m_MoveEnd = 0;

	std::string info = {};
	std::set<uint32_t> mTimerId;
	FightInfo          mFightInfo;
	bool               mCalculateAttribute = false;			//进入安全区才重新计算属性
};

struct DoHandlerNotify
{
	uint16_t start;
	uint16_t end;
	std::function<void(uint16_t type)> func;
};

void HandlerNotifyAttr(uint16_t);
void HandlerNotifyState( uint16_t);
void HandlerNotifyMove(uint16_t);
void HandlerNotifySkill( uint16_t);
void HandlerNotifyBuff( uint16_t);
void HandlerNotifyPack( uint16_t);
void HandlerNotifyAvatar( uint16_t);
void HandlerNotifyRelation( uint16_t);
void HandlerNotifyTask( uint16_t);
void HandlerNotifyEquip(uint16_t);
void HandlerNotifyTeam(uint16_t);
void HandlerNotifyVip(uint16_t);