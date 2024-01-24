#pragma once
#include "Object.h"
#include "Player.h"
#include "Monster.h"
#include "Npc.h"
#include <map>
#include <unordered_map>
#include "MapGrid.h"
#include "MapAoi.h"
#include "MapAoi.h"
#include "MapRoleMgr.h"
#include "map_table.hpp"
#include "item_table.hpp"
#include "jump_table.h"
#include "SceneItem.h"
#include "regioncommon.h"

typedef std::pair<uint64_t, Player*> PlayerPair;
typedef std::pair<uint64_t, Monster*> MonsterPair;
typedef std::pair<uint64_t, Npc*> NpcPair;


struct TrapSkillRoleInfo
{
    uint64_t roleGUID   = 0;
    uint32_t stillTime  = 0;        // 静止不动时间
    uint16_t x          = 0;
    uint16_t y          = 0;
	uint32_t nround		= 1;
    TrapSkillRoleInfo(uint64_t roleGUID_, uint16_t x_, uint16_t y_) : roleGUID(roleGUID_), x(x_), y(y_) {}
};

using TrapSkillRoleInfoList = std::list<TrapSkillRoleInfo>;

struct TrapSkillMonitorRegionInfo
{
    uint16_t    skillID         = 0;
    uint64_t    actorGUID       = 0;

    uint32_t    elapsedTime     = 0;
    uint32_t    expireTime      = 0;
	
    bool        valid           = true;

    PositionList            posList;
    TrapSkillRoleInfoList   roleInfoList;
};

using TrapSkillMonitorRegionInfoList = std::list<TrapSkillMonitorRegionInfo>;
using TrapSkillMonitorRegionInfoPtrList = std::vector<TrapSkillMonitorRegionInfo *>;

using DynJumpPointList = std::map<uint32_t,DATA::Jump>;


class Map : public Object, public EventTrigger
{
public:
	Map();
	virtual ~Map();

	bool Init(DATA::Map* mapConfig);

	void Update(int delta) override;

    uint16_t GetTemplateID() { return mTemplateID; }

	MapGrid& GetMapGrid() { return mMapGrid; }

	DATA::Map* GetMapConfig() { return sMapConfig.Get(mTemplateID); }
	MapAoi& GetMapAoi() { return mMapAoi; }

    uint32_t GetWidth() { return mMapGrid.GetWidth(); }
    uint32_t GetHeight() { return mMapGrid.GetHeight(); }

    const std::string & GetScriptName() { return mScriptName; }
	void DisAppearMonster(Monster* monster, Role* player);
	void AppearMonster(Monster* monster, Role* player);

    void RoleEnter(Role* role);
    void RoleLeave(Role* role , bool isReleasedGrid = true);
	bool RoleMove(Role* role, uint16_t oldX, uint16_t oldY);
	void RoleExit(Role* role);
	void Jump(Role* role);

    void SetRegionSize(uint16_t regionWidth, uint16_t regionHeight);
	bool GetRandBlankPointInRange(uint16_t left, uint16_t top, uint16_t width, uint16_t height, uint16_t& posX, uint16_t& posY, bool mustBlank = true, bool excludeJP = false);
	void GetAllBlankPointInRange(uint16_t x, uint16_t y, uint16_t rangeX, uint16_t rangeY, std::vector<std::pair<uint16_t, uint16_t>>&vec);
	void GenMapMonster();
    void GenMapNPC();
	std::string GenMapNPCByKeyName(const std::string& keyName, uint16_t x, uint16_t y,  uint8_t dir);
	void DelMapNPCByGuid(uint64_t guid);

    void GenMapMonsterByName(const std::string& Name, uint16_t left, uint16_t top,
		uint16_t width, uint16_t height, uint16_t num, uint8_t dir, bool isCastle = false);
    void GenMapMonsterByID(uint16_t id, uint16_t left, uint16_t top,
		uint16_t width, uint16_t height, uint16_t num, uint8_t dir);
	Monster* GenMonster(DATA::Monster* monster_cfg, uint16_t left, uint16_t top,
		uint16_t width, uint16_t height, uint8_t dir, uint64_t lastGUID = 0, bool isCastle = false);
    int GetMonsterNum();
    Role* GetRoleInPoint(uint16_t posX, uint16_t posY);
	std::vector<Role *> GetRolesInSameCircle(uint16_t x0, uint16_t y0, uint8_t radius, uint8_t roleType);
    std::vector<SceneItem *> GetSceneItemsInSameCircle(uint16_t x0, uint16_t y0, uint8_t radius);
    bool IsGridAvail(uint16_t x, uint16_t y);
	void DisappearMonsterCorpseInPoint(uint16_t posX, uint16_t posY);

	bool IsSafeRegion(uint16_t  posx, uint16_t posy);
    bool IsRoleExist(Role *role) { return mMapAoi.IsRoleExist(role); }

	void AddJumpPoint(const std::string& from_guid, const std::string& to_guid, uint16_t from_x, uint16_t from_y, uint16_t to_x, uint16_t to_y, uint32_t enterEffect, uint32_t leaveEffect);
	void AddJumpPoint(uint16_t x, uint16_t y, uint32_t effect);
	void DelJumpPoint(const std::string& guid, uint16_t x, uint16_t y);
	void DelJumpPoint(uint16_t x, uint16_t y);
	std::list<Role *> GetAllRoleByType(uint8_t roleType);
	void SendBlankGridTableToLua(uint16_t x, uint16_t y, uint16_t rangeX, uint16_t rangeY, uint16_t type);

	bool IsTypeRegion(uint16_t  posx, uint16_t posy,int type);
	void GetTypeRegion(int type, std::vector<DATA::RegionCommon>& vec);

	int SelelctSite(int x, int y, int& desti, int& destj, int step);
	Role* GetNearstRoleByType(uint16_t posX, uint16_t posY, bool canGetStealth, uint8_t roleType = role_type_none, Role* origRole = nullptr);
	Role* GetNeatstRoleByCustType(uint16_t posX, uint16_t posY, uint8_t roleType = cust_role_red_name, Role* origRole = nullptr);
	Role* GetNearestRoleByName(uint16_t posX, uint16_t posY, uint8_t roleType, const char* name, Role* origRole = nullptr);
	void GetAllRoleByTypeByName(std::vector<Role*> &vec, uint8_t roleType, const char* name);

	void SendRoleDirChangeNtf(Role* role, ProtoGS_TurnNtf& ntf);
	void SendRoleDieNtf(Role* role, ProtoMS_ObjDieNtf& ntf);

	void NotifyRoleAppearNtfChange(Role* role);

    uint32_t AddLuaTimer(unsigned int interval, bool loop, const std::string& call_back);
    uint32_t AddLuaTimerEx(unsigned int interval, bool loop, CLuaObject call_back);
	void RemoveLuaTimer(unsigned int id);

	void AddTrapTimer(uint32_t timer) { mMapTimerId.insert(timer); }
	void DelTrapTimer(uint32_t timer) { mMapTimerId.erase(timer); }
	void RemoveAllTrapTimer();

	void InitJumpPointForbit(DATA::Map* mapConfig);

#pragma region 场景物品相关
	bool GetBlankSceneItemPos(uint16_t srcX, uint16_t srcY, uint16_t& dstX, uint16_t& dstY);
    const std::string & GenSceneItem(uint16_t x, uint16_t y, uint16_t id, uint16_t amount, uint16_t bind ,const std::string& ownerGuid = "");
    const std::string & GenSceneItemByName(uint16_t x, uint16_t y, const std::string &name, uint16_t amount, uint16_t bind ,const std::string& ownerGuid = "");
	SceneItem* AddSceneItem( uint16_t x, uint16_t y, uint16_t id, uint16_t amount = 1, uint16_t bind = 1,
        uint16_t drop = 1, uint64_t ownerGUID = 0, uint64_t teamGUID = 0);
	SceneItem* AddSceneItem(uint16_t x, uint16_t y, RoleItem* roleItem);
	bool DestroySceneItem(uint16_t x, uint16_t y);
	bool DestroySceneItem(uint64_t itemGUID, uint16_t x, uint16_t y);
	SceneItem* GetSceneItem(uint16_t x, uint16_t y);
	SceneItem* GetSceneItem(uint64_t itemGUID);
	//std::unordered_map<uint32_t, SceneItem>& GetSceneItems() { return mSceneItems; }
	bool OnRoleDropItem(Role* role, RoleItem* item);
	void SendRoleItemAppearNtf(ProtoMS_ItemAppearNtf4& ntf);
	void SendRoleObjDisappearNtf(uint16_t posX, uint16_t posY, ProtoMS_ObjDisappearNtf& ntf);
	void SendPlayerChangeNameNtf(Role* role, ProtoGS_PlayerSetNameNtf& ntf);
	void SendMasterChangeNameNtf(Role* role, ProtoGS_PlayerSetNameNtf& ntf);
	void SendPlayerWearTitleNtf(Role* role, ProtoGS_TitleWearNtf& ntf);
	void SendPlayerUnWearTitleNtf(Role* role, ProtoGS_TitleUnWearNtf& ntf);
    void OnItemAppear(SceneItem *item);
    void OnItemDisappear(SceneItem *item);
	SceneItem* GetPetPickableItem(Monster *pet);
	bool SupportAutoPickItem();
#pragma endregion

    void SendSysMsg(uint8_t nMsgType, const std::string &sMsg);
	void SendSysMsgNtf2AllRole(MESSAGE_INFO& info);
	void SendSysMsgNtf2AllRoleInAroundRegion(MESSAGE_INFO& info);
	void SendSceneDialogNtfAllRole(MESSAGE_INFO& info);
	void SendSceneDialogNtfAllRoleInAroundRegion(MESSAGE_INFO& info);
	void SendScrollTextAllRole(MESSAGE_INFO& info);
	void SendScrollTextAllRoleInAroundRegion(MESSAGE_INFO& info);
	void RunClientScript(const char* pScriptName, const char* pContent, bool bCompress);
	bool FindJumpablePos(uint16_t& posX, uint16_t& posY);

	void SetDestroyFlag(bool beDestroy) { mBeDestroy = beDestroy; }
	bool GetDestroyFlag() { return  mBeDestroy;}

	virtual void AddPlayerGuid(uint64_t playerGuid) {};
	virtual void RemovePlayerGuid(uint64_t playerGuid)  {};

    void OnEndMove(Role *role);

	bool CheckCross(uint32_t roleType);

    std::pair<uint16_t, uint16_t> GetMForbidPoint(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);      // 获取两点之间的第一个魔法阻挡点

    std::map<uint32_t, std::vector<uint32_t>> GetAroundPlayerCLSessionID(Role *role, bool includingSelf = true);
	std::map<uint32_t, std::vector<uint32_t>> GetAllPlayerCLSessionID();

    ////////////////////////////////////////////////////////////////////////////////
    // Callback support
public:
    using       Func    = std::function<void(Role*)>;
    using       FuncMap = std::map<uint32_t, Func>;

    void        ApplyFuncToAllRoles(Func f, uint16_t type = role_type_none);
    void        ApplyFuncToAllRolesInAroundRegions(uint16_t x, uint16_t y, Func f);
	void        ApplyFuncToAllPlayersInAroundRegions(uint16_t x, uint16_t y, Func f);
	

    uint32_t    AddOnRoleEnterFunc(Func func);
    uint32_t    AddOnRoleLeaveFunc(Func func);

    void        RemoveOnRoleEnterFunc(uint32_t funcID);
    void        RemoveOnRoleLeaveFunc(uint32_t funcID);

private:
    uint32_t    AddFuncToMap(FuncMap &funcMap, Func func);
    void        RemoveFuncFromMap(FuncMap &funcMap, uint32_t funcID);
    void        ApplyFuncInMap(FuncMap &funcMap, Role *role);

    void        ApplyOnRoleEnterFunc(Role *role);
    void        ApplyOnRoleLeaveFunc(Role *role);

private:
    FuncMap     mOnRoleEnterFunc;
    FuncMap     mOnRoleLeaveFunc;
    ////////////////////////////////////////////////////////////////////////////////

	void OnDestroy();
public:
	void AddPosToTrap(uint16_t x, uint16_t y)
	{
		uint32_t key = x << 16 | y;
		mTrapList.insert(key);
	}
	void RemovePosInTrap(uint16_t x, uint16_t y)
	{
		uint32_t key = x << 16 | y;
		mTrapList.erase(key);
	}
	bool IsTrapPoint(uint16_t x, uint16_t y)
	{
		uint32_t key = x << 16 | y;
		if (mTrapList.find(key) != mTrapList.end()) return true;
		return false;
	}

    ////////////////////////////////////////////////////////////////////////////////
    // 陷阱类技能
public:
    bool AddMonitorRegionForTrapSkill(uint16_t skillID, uint32_t expireTime, uint64_t actorGUID, PositionList posList);
    void RemoveMonitorRegionForTrapSkill(uint64_t actorGUID);
	void AddTrapEffect(uint16_t skillID, uint16_t x, uint16_t y, uint32_t effect, uint32_t lifetime);

private:
    void EraseTrapSkillOverlappedRegion(uint16_t skillID, PositionList &newPosList);
    void FillTrapSkillRoleInfoList(TrapSkillMonitorRegionInfo &regionInfo);
    void TrapSkillInitHurt(TrapSkillMonitorRegionInfo &regionInfo);
    void TrapSkillHurtRole(uint16_t skillID, uint64_t actorGUID, uint64_t roleGUID,uint32_t round = 1);
    void UpdateTrapSkillRegionState(int delta);
    void UpdateTrapSkillRegionRoleInfo(Role *role);

    TrapSkillMonitorRegionInfoPtrList FindTrapSkillMonitorRegion(uint64_t roleGUID);
    TrapSkillMonitorRegionInfoPtrList FindTrapSkillMonitorRegion(uint16_t x, uint16_t y);

    void AddTrapSkillRoleInfo(TrapSkillRoleInfoList &roleInfoList, uint64_t roleGUID, uint16_t x, uint16_t y);
    void UpdateTrapSkillRoleInfo(TrapSkillRoleInfoList &roleInfoList, uint64_t roleGUID, uint16_t x, uint16_t y);
    void EraseTrapSkillRoleInfo(TrapSkillRoleInfoList &roleInfoList, uint64_t roleGUID);
    TrapSkillRoleInfo * GetTrapSkillRoleInfo(TrapSkillRoleInfoList &roleInfoList, uint64_t roleGUID);

private:
    TrapSkillMonitorRegionInfoList mTrapSkillMonitorRegionInfoList;
    ////////////////////////////////////////////////////////////////////////////////

protected:
	MapGrid mMapGrid;
	MapAoi mMapAoi;
	std::string mScriptName;
	std::set<uint32_t> mTimerId;
	std::set<uint32_t> mMapTimerId;
    uint16_t mTemplateID = 0;
	uint16_t mRegionWidth = 10;
	uint16_t mRegionHeight = 10;
	bool	mBeDestroy = false;
	std::map<uint32_t, bool> CheckCrossMap;
	
	DynJumpPointList mDynJumpPointList;

	std::multiset<uint32_t> mTrapList;
};

class DgnMap : public Map
{
public:
	DgnMap() { ResetDgnData();}
	virtual ~DgnMap() {}
	void ResetDgnData();
	void Prepare(uint64_t oGuid, uint32_t dTime, CLuaObject call_back, bool delay = true);
	void Clear();
	void AddBindPlayerGuid(uint64_t playerGuid);
	void RemoveBindPlayerGuid(uint64_t playerGuid);
	// overwrite
	void AddPlayerGuid(uint64_t playerGuid);
	void RemovePlayerGuid(uint64_t playerGuid);

	bool IsEmpty();
protected:
	uint64_t			ownerGuid;			// 创建副本的玩家,或者说副本的房主
	std::set<uint64_t>	bindGuidSet;		// 绑定此副本的玩家
	std::set<uint64_t>	playerGuidSet;		// 在副本里的玩家
	uint32_t	mDestoryTime;				// 副本销毁时间
	uint32_t	mDestoryTimerId;			// 副本销毁定时器
	bool		mDelayInit;					// 是否延迟初始化
};

