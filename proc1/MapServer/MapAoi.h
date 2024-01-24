#pragma once

#include <unordered_map>
#include "Role.h"
#include "MapRegion.h"

class Map;
class MapAoi
{
    using Func = std::function<void(Role *)>;

public:
	MapAoi();
	~MapAoi();

public:
	bool Init(Map* map, uint16_t mapWidth, uint16_t mapHeight, uint16_t regionWidth, uint16_t regionHeight);
	uint16_t GetRegionWidth() const { return mRegionWidth; }
	uint16_t GetRegionHeight() const { return mRegionHeight; }

	void RoleEnter(Role* role);
	void RoleLeave(Role* role);
	bool RoleMove(Role* role, uint16_t oldX, uint16_t oldY);
    void RoleExit(Role *role);

	void NotifyRoleOnlyUpdateAppearNtf(Role* role);

	void SendRoleDirChangeNtf(Role* role, ProtoGS_TurnNtf& ntf);
	void SendRoleDieNtf(Role* role, ProtoMS_ObjDieNtf& ntf);
	void SendRoleItemAppearNtf(ProtoMS_ItemAppearNtf4& ntf);
	void SendRoleObjDisappearNtf(uint16_t posX, uint16_t posY, ProtoMS_ObjDisappearNtf& ntf);
	void SendRoleNameChangeNtf(Role* role, ProtoGS_PlayerSetNameNtf& ntf);
	void SendRoleWearTitleNtf(Role* role, ProtoGS_TitleWearNtf& ntf);
	void SendRoleUnWearTitleNtf(Role* role, ProtoGS_TitleUnWearNtf& ntf);
	void SendEffectAppearNtf(uint16_t posX, uint16_t posY, ProtoMS_EffectAppearNtf& ntf);
	void SendEffectDisAppearNtf(uint16_t posX, uint16_t posY, ProtoMS_EffectDisAppearNtf& ntf);

	void ApplyFuncToAllRoles(Func& f, uint16_t type = role_type_none);
	void ApplyFuncToAllRolesInAroundRegions(uint16_t x, uint16_t y, Func& f);
	void ApplyFuncToAllPlayersInAroundRegions(uint16_t x, uint16_t y, Func& f);
	// ass
	bool IsHaveRoleInPoint(uint16_t posX, uint16_t posY);
    Role *GetRoleInPoint(uint16_t posX, uint16_t posY);
	void IsHaveRoleInPoint(uint32_t roleType, uint16_t posX, uint16_t posY, std::array<uint16_t, role_type_cnt>& arr, bool beAlive = true);
	bool IsHaveRoleInPoint(uint32_t roleType, uint16_t posX, uint16_t posY);
    bool IsRoleExist(Role *role);
	void DisappearMonsterCorpseInPoint(uint16_t posX, uint16_t posY);

	int32_t GetMonsterNum();
	int32_t GetPlayerNum();


	Role* GetNearstRoleByType(uint16_t posX, uint16_t posY, bool canGetStealth, uint8_t roleType = role_type_none, Role* origRole = nullptr);
	Role* GetNearstRoleByCustType(uint16_t posX, uint16_t posY, uint8_t roleType = cust_role_red_name, Role* origRole = nullptr);
	void GetAllRoleByTypeByName(std::vector<Role*>&vec, uint8_t roleType, const char* name);
	void GetSingleRegionRoleByType(std::list<Role*>& list, uint8_t roleType, uint32_t x, uint32_t y);
	bool RemoveRole(Role* role);
	bool AddRole(Role* role);
	int GetRoleRegionIndex(Role* role);
    std::list<Role *> GetAllRoleByType(uint8_t roleType);

#pragma region 场景物品
	SceneItem* AddSceneItem(uint16_t id, uint16_t x, uint16_t y, uint16_t amount = 1, uint16_t bind = 1,
        uint16_t drop = 1, uint64_t ownerGUID = 0, uint64_t teamGUID = 0);
	SceneItem* AddSceneItem(uint16_t x, uint16_t y, RoleItem* roleItem);
	bool DestroySceneItem(uint16_t x, uint16_t y);
	bool DestroySceneItem(uint64_t itemGUID, uint16_t x, uint16_t y);
	SceneItem* GetSceneItem(uint16_t x, uint16_t y);
	SceneItem* GetSceneItem(uint64_t itemGUID);
    void OnItemAppear(SceneItem *item);
    void OnItemDisappear(SceneItem *item);
	SceneItem* GetPetPickableItem(Monster *pet);
#pragma endregion

	//跳转点
	void AddJumpPointEffect(EffectPoint& data);
	void DelJumpPointEffect(EffectPoint& data);

	//陷阱
	void AddTrapPointEffect(TrapPointEffect& data, uint32_t lifetime);
protected:
	Map* mCurMap;
	uint16_t mRegionRows;
	uint16_t mRegionCols;
	MapRegion* mRegions;

    uint16_t mRegionWidth = 0;
    uint16_t mRegionHeight = 0;
};
