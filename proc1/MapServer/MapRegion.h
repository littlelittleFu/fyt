#pragma once

#include <unordered_map>
#include "Role.h"
#include "SceneItem.h"

//地图区块的大小
const int AOI_LEN = 1;


class Monster;

class MapRegion
{
    using Func = std::function<void(Role *)>;

public:
	MapRegion();
	~MapRegion();
	void Init(Map* map, uint16_t row, uint16_t col, uint16_t regionWidth, uint16_t regionHeight);
	void RoleEnter(Role* role);
	void RoleLeave(Role* role);
	void RoleMove(Role* role);
    void RoleExit(Role *role);

    void NotifyRoleOnlyUpdateAppearNtf(Role* role);

    void SendRoleDirChangeNtf(Role* role, ProtoGS_TurnNtf& ntf);
    void SendRoleDieNtf(Role* role, ProtoMS_ObjDieNtf& ntf);
    void SendRoleItemAppearNtf(ProtoMS_ItemAppearNtf4& ntf);
    void SendRoleObjDisappearNtf(ProtoMS_ObjDisappearNtf& ntf);
    void SendRoleNameChangeNtf(Role* role ,ProtoGS_PlayerSetNameNtf& ntf);
    void SendRoleWearTitleNtf(Role* role, ProtoGS_TitleWearNtf& ntf);
    void SendRoleUnWearTitleNtf(Role* role, ProtoGS_TitleUnWearNtf& ntf);
    void SendEffectAppearNtf(ProtoMS_EffectAppearNtf& ntf);
    void SendEffectDisAppearNtf(ProtoMS_EffectDisAppearNtf& ntf);


    void ApplyFuncToAllPlayers(Func& f);
    void ApplyFuncToAllRoles(Func& f, uint16_t type = role_type_none);
    Role* GetRoleInPoint(uint16_t posX, uint16_t posY);
    void GetRoleInPoint(vector<Role*>&vec,uint16_t posX, uint16_t posY, uint32_t roleType, bool beAlive = false);
    int32_t GetRoleNum(uint32_t type, uint16_t posX = 0, uint16_t posY = 0, bool beAlive = false);
    int32_t HaveRoleNum(uint32_t type, uint16_t posX = 0, uint16_t posY = 0, bool beAlive = false);
    void GetNearstRoleByType(uint16_t posX, uint16_t posY, bool canGetStealth, uint8_t roleType, uint16_t& dis, Role*& role, Role* origRole = nullptr);
    void GetNearstRoleByCustType(uint16_t posX, uint16_t posY, uint8_t roleType, uint16_t& dis, Role*& role, Role* origRole = nullptr);
    void GetAllRoleByTypeByName(std::vector<Role*>& vec, uint8_t roleType, const char* name);
    void GetAllRoleByType(std::list<Role *> &roleList, uint8_t roleType);
    bool RemoveRole(Role* role);
    bool AddRole(Role* role);
    bool IsRoleExist(Role *role);
    std::map<uint64_t, Role*>& GetAllRoleTable() { return mRoles[role_type_none]; };

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
    void GetPetPickableItem(Monster *pet, uint16_t &dist, SceneItem *&item);
#pragma endregion

    //跳转点
    void AddJumpPointEffect(EffectPoint& data);
    void DelJumpPointEffect(EffectPoint& data);

    //陷阱
    void AddTrapPointEffect(TrapPointEffect& data, uint32_t lifetime);
    void DelTrapPointEffect(const TrapPointEffect& data);

protected:
    void RemoveItemFromMap(const SceneItem& item);
    void DestroyAllRoles();
    bool CheckType(int32_t type) { return role_type_none < type && type < role_type_cnt;}
protected:
    Map* mCurMap;
    std::map<uint64_t, Role*> mRoles[role_type_cnt];
    std::map<uint32_t, SceneItem> mSceneItems;
    std::map<uint32_t, std::map<uint32_t, TrapPointEffect>> mTrapEffectList;
    std::map<uint32_t, EffectPoint> mJumpPointEffectList;
	uint16_t mRow;
	uint16_t mCol;

    uint16_t mRegionWidth = 0;
    uint16_t mRegionHeight = 0;
};
