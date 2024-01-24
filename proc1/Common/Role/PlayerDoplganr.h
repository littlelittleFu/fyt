#pragma once

#include "Role.h"

class Player;
class Map;

class PlayerDoplganr : public Role
{
    using RoleGUIDSet = std::set<uint64_t>;

    enum state {
        state_ai_mode,
        state_request_enable_auto_mode,
        state_request_disable_auto_mode,
        state_auto_mode,
    };

    enum ai_state {
        ai_state_idle,
        ai_state_follow,
        ai_state_attack,
        ai_state_attack_idle,       //召唤物、英雄AI状态：战斗待机
        ai_state_escape,
        ai_state_pursure, 
    };

    static uint8_t  const ATTACK_DIST       = 10;
    static uint8_t  const START_FOLLOW_DIST = 3;
    static uint8_t  const ATTACK_FOLLOW_DIST = 10;
    static uint8_t  const JUMP_DIST         = 20;
    static uint16_t const WAIT_RESP_TIME    = 3000;
    static uint64_t const WalkDelayTime     = 600;
    static uint64_t const RunDelayTime      = 300;
    static uint64_t const TARGET_RESP_TIME = 3000;

public:
                    PlayerDoplganr();
    virtual        ~PlayerDoplganr();

    // Object virtual functions override
    void            Update(int32_t deltaTimeMS) override;

    // Role virtual functions override
    void            SendAppearNtf(Role *toRole) override;
    void            SendRoleAppNtf(Role *toRole) override;
    bool            CheckTakeGrid(uint16_t x, uint16_t y) override;
    void            OnRoleEnter(Role *role) override;
    void            OnRoleLeave(Role *role) override;
    void            OnRoleExit(Role *role) override;
    void            OnRoleMove(Role *role) override;
    void            OnRoleDie(uint64_t killedBy) override;
    bool            IsInSameTeam(Role *role) override;
    bool            IsInSameGuild(Role *role) override;
    bool            IsInSameCamp(Role *role) override;
    bool            IsGrayName() override;
    bool            IsRedName() override;
    bool            GetWalkablePos(uint16_t& dir, uint16_t tarRoleposX, uint16_t tarRoleposY, uint16_t& tarX, uint16_t& tarY, uint16_t todir);
    void            Init();
    void            CloneMaster();

    void            SetMasterGUID(uint64_t masterGUID);
    uint64_t        GetMasterGUID() { return mMasterGUID; }
    Player         *GetMaster();

    void            SetAutoMode(bool enable) { mAutoMode = enable; }
    void            CopyPropFromMaster();
    void            CopyEquipFromMaster();
    void            CopySkillFromMaster();
    void            CopyBuffFromMaster();

    Role*           GetNearestRoleByType(uint8_t roleType,Role* role);

    std::map<uint64_t, Hated_Value>& GetHateValueMap() { return HatedVauleMap; }
    CLuaObject GetHateValueMapToLua();

    bool IsEmptyHateValueMap();
    bool IsTarInHateValueMap(uint64_t tarGuid);
    void AddHatedValue(uint64_t guid, uint32_t hatevalue);
    void DeleteMaxHateValue(uint64_t guid);
    void DecreaseHateValue();

    bool IsInVieRange(uint64_t tarGuid);                    //是否在视野范围内
    bool IsInTraRange(uint64_t tarGuid);                    //是否在追踪范围内

    Role* GetMaxHatedValueRole();
    Player* GetMaxHatedValueRedNameRole();

    void  JumpToMaster();

private:
 

    uint16_t        GetEquipID(uint32_t site);

    void            SendSkillAddAck();
    void            SendSetAutoModeReq(bool enable);

    bool            ExistAttackTarget();
    bool            IsAutoMode() { return mAutoMode; }

    void            SetState(state state) { mState = state; }
    state           GetState() { return mState; }

    void            SetAIState(ai_state state) { mAIState = state; }
    ai_state        GetAIState() { return mAIState; }

    void            HandleAIState_idle(int32_t deltaTimeMS);
    void            HandleAIState_follow(int32_t deltaTimeMS);
    void            HandleAIState_Attack(int32_t deltaTimeMS);
    void            HandleAIState_Pursure(int32_t deltaTimeMS);
    void            HandleAIState_attack_idle(int32_t deltaTimeMS);
    

    uint8_t         FollowMaster();
    uint8_t         moveto(uint16_t x, uint16_t y);
    
    bool            CanHitTarget(int mCurSkillID);
    void            SetTarGuid(uint64_t targuid) { mTarGUID = targuid; }
    uint64_t        GetTarGuid() { return mTarGUID; };
    void            ResetTarGuid() { mTarGUID = 0; }

    void            SetCurAttackDir();
    void            ApplySkill(int mCurSkillID);

    //move to


    void            ResetTimeElapsed() { mUpdateTime = GetTimeStampMillisecond2(); }
    void            AddTimeElapsed(uint64_t delta) { mUpdateTime = GetTimeStampMillisecond2() + delta; }
    uint64_t        TimeElapsed() { return mUpdateTime; }

    void            GenStopFollowDist();
    void            GenStopAttackFollowDist();
    uint16_t        StopFollowDist() { return mStopFollowDist; }

private:
    uint64_t        mMasterGUID         = 0;
    bool            mAutoMode           = false;
    int64_t         mEndLifeTime        = 0;

    char            family_name[32] = { 0 };          // 行会名称
    char            castle_name[256] = { 0 };          // 城堡名称，可以多个用与符号分隔

    RoleGUIDSet     mAttackableRoles;
    state           mState              = state_ai_mode;
    ai_state        mAIState            = ai_state_idle;
    uint32_t        mTimeElapsed        = 0;
    uint16_t        mStopFollowDist     = 0;                // 跟随主人距离多远之内停止
    uint64_t        mUpdateTime         = 0;
    uint64_t		mTarGUID            = 0;
    int32_t         mGeneralSkill       = 0;
    uint64_t        mChangeTargTime     = 0;

    uint16_t		            mVieRange                   = 0;                    /// ??
	uint16_t		            mMovRange                   = 0;					/// ????
	uint16_t		            mTraRange                   = 0;                    /// ????
    uint16_t                    mMovPosX = 0;
    uint16_t                    mMovPosY = 0;
    uint16_t                    mMovDir = 0;
    std::string                 mStateKey;
    std::map<uint64_t, Hated_Value> HatedVauleMap;
};

class PlayerDoplganrMgr
{
public:
                    PlayerDoplganrMgr(Player *player);
                   ~PlayerDoplganrMgr();

    uint32_t        GetDoplganrNum() { return mDoplganrs.size(); }
    std::vector<PlayerDoplganr*>& GetDoplganrList() { return mDoplganrs; }
    void            AddDoplganr(PlayerDoplganr* doplganr) { mDoplganrs.push_back(doplganr); }
    void            RemoveDoplganr(PlayerDoplganr *doplganr);

    void            DoplganrEnterMap(Map *map);
    void            DoplganrLeaveMap();
    void            DestroyDoplganr();

private:
    std::vector<PlayerDoplganr *>   mDoplganrs;
    Player         *mPlayer     = nullptr;
};

using PlayerDoplganrMgrPtr = std::unique_ptr<PlayerDoplganrMgr>;