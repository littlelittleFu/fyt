#include "stdafx.h"
#include "MapAoi.h"
#include "MapRegion.h"
#include <algorithm>
#include "Map.h"
#include"Monster.h"

#pragma region MACRO DEFINES
#define CALL_REGION_FUC_BY_POS_RET(func, x, y)\
{\
uint16_t row = y / mRegionHeight;\
uint16_t col = x / mRegionWidth;\
if (row >= 0 && row < mRegionRows && col >= 0 && col < mRegionCols) {\
	return mRegions[row * mRegionCols + col].func(x, y);\
}\
}

#define CALL_ALL_REGION_FUC_BY_GUID_RET(func, guid)\
{\
for (int i = 0; i < mRegionRows; ++i) {\
	for (int j = 0; j < mRegionCols; ++j) {\
		auto res = mRegions[i * mRegionCols + j].func(guid);\
		if (res) {\
		return res;\
		}\
	}\
}\
}

#define CALL_ALL_REGION_FUC_BY_GUID_RET2(func, guid, x, y)\
{\
uint16_t row = y / mRegionHeight; \
uint16_t col = x / mRegionWidth; \
if (row >= 0 && row < mRegionRows && col >= 0 && col < mRegionCols) {\
		return mRegions[row * mRegionCols + col].func(guid,x,y); \
}\
}

#define CALL_AROUND_REGION_FUC_BY_ITEM1(func, item)\
{\
if (nullptr == item) {\
return;\
}\
uint16_t row = item->GetPosY() / mRegionHeight;\
uint16_t col = item->GetPosX() / mRegionWidth;\
for (int i = row - AOI_LEN; i <= row + AOI_LEN; ++i) {\
	for (int j = col - AOI_LEN; j <= col + AOI_LEN; ++j) {\
		if (i >= 0 && i < mRegionRows && j >= 0 && j < mRegionCols) {\
			mRegions[i * mRegionCols + j].func(item);\
		}\
	}\
}\
}

#define CALL_AROUND_REGION_FUC_BY_ROLE1(func, role)\
{\
if (nullptr == role) {\
return;\
}\
uint16_t row = role->GetRolePosY() / mRegionHeight;\
uint16_t col = role->GetRolePosX() / mRegionWidth;\
for (int i = row - AOI_LEN; i <= row + AOI_LEN; ++i) {\
	for (int j = col - AOI_LEN; j <= col + AOI_LEN; ++j) {\
		if (i >= 0 && i < mRegionRows && j >= 0 && j < mRegionCols) {\
			mRegions[i * mRegionCols + j].func(role);\
		}\
	}\
}\
}

#define CALL_AROUND_REGION_FUC_BY_ROLE2(func, role, param1)\
{\
if (nullptr == role) {\
return;\
}\
uint16_t row = role->GetRolePosY() / mRegionHeight;\
uint16_t col = role->GetRolePosX() / mRegionWidth;\
for (int i = row - AOI_LEN; i <= row + AOI_LEN; ++i) {\
	for (int j = col - AOI_LEN; j <= col + AOI_LEN; ++j) {\
		if (i >= 0 && i < mRegionRows && j >= 0 && j < mRegionCols) {\
			mRegions[i * mRegionCols + j].func(role, param1);\
		}\
	}\
}\
}

#define SEND_AROUND_REGION_MSG_BY_ROLE(func,role,msg)\
{\
if (nullptr == role) {\
return;\
}\
uint16_t row = role->GetRolePosY() / mRegionHeight;\
uint16_t col = role->GetRolePosX() / mRegionWidth;\
for (int i = row - AOI_LEN; i <= row + AOI_LEN; ++i) {\
	for (int j = col - AOI_LEN; j <= col + AOI_LEN; ++j) {\
		if (i >= 0 && i < mRegionRows && j >= 0 && j < mRegionCols) {\
			mRegions[i * mRegionCols + j].func(role, msg);\
		}\
	}\
}\
}

#define SEND_AROUND_REGION_MSG_BY_POS(func,posX,posY,msg)\
{\
uint16_t row = (posY) / mRegionHeight;\
uint16_t col = (posX) / mRegionWidth;\
for (int i = row - AOI_LEN; i <= row + AOI_LEN; ++i) {\
	for (int j = col - AOI_LEN; j <= col + AOI_LEN; ++j) {\
		if (i >= 0 && i < mRegionRows && j >= 0 && j < mRegionCols) {\
			mRegions[i * mRegionCols + j].func(msg);\
		}\
	}\
}\
}
#pragma endregion

MapAoi::MapAoi() : mRegionRows(0), mRegionCols(0), mRegions(nullptr)
{
	mCurMap = nullptr;
}

MapAoi::~MapAoi()
{
	SAFE_RELEASE_ARRAY(mRegions);
}

bool MapAoi::Init(Map* map, uint16_t mapWidth, uint16_t mapHeight, uint16_t regionWidth, uint16_t regionHeight)
{
	SAFE_BEGIN;
	mCurMap = map;
    mRegionWidth = regionWidth;
    mRegionHeight = regionHeight;

	mRegionRows = mapHeight / mRegionHeight + 1;
	mRegionCols = mapWidth / mRegionWidth + 1;
	mRegions = new MapRegion[mRegionRows * mRegionCols];
	for (auto i = 0; i < mRegionRows; ++i) {
		for (auto j = 0; j < mRegionCols; ++j) {
			mRegions[i * mRegionCols + j].Init(map, i,j, mRegionWidth, mRegionHeight);
		}
	}
	SAFE_END;
	return true;
}

void MapAoi::RoleEnter(Role* role)
{
	CALL_AROUND_REGION_FUC_BY_ROLE1(RoleEnter, role);
}

void MapAoi::RoleLeave(Role* role)
{
	CALL_AROUND_REGION_FUC_BY_ROLE1(RoleLeave, role);
}

bool MapAoi::RoleMove(Role* role, uint16_t oldX, uint16_t oldY)
{
	SAFE_BEGIN;
	if (nullptr == role) {
		return true;
	}

	uint16_t oldRow = oldY / mRegionHeight;
	uint16_t oldCol = oldX / mRegionWidth;
	uint16_t newRow = role->GetRolePosY() / mRegionHeight;
	uint16_t newCol = role->GetRolePosX() / mRegionWidth;
	if (oldRow >= mRegionRows) return true;
	if (oldCol >= mRegionCols) return true;
	if (newRow >= mRegionRows) return false;
	if (newCol >= mRegionCols) return false;

	//计算老集合
	std::set<uint32_t> set_old;
	for (int i = oldRow - AOI_LEN; i <= oldRow + AOI_LEN; ++i) {
		for (int j = oldCol - AOI_LEN; j <= oldCol + AOI_LEN; ++j) {
			if (i >= 0 && i < mRegionRows && j >= 0 && j < mRegionCols) {
				set_old.insert(i * mRegionCols + j);
			}
		}
	}

	//计算新集合
	std::set<uint32_t> set_new;
	for (int i = newRow - AOI_LEN; i <= newRow + AOI_LEN; ++i) {
		for (int j = newCol - AOI_LEN; j <= newCol + AOI_LEN; ++j) {
			if (i >= 0 && i < mRegionRows && j >= 0 && j < mRegionCols) {
				set_new.insert(i * mRegionCols + j);
			}
		}
	}

	//计算新老集合的差集，通知角色离开
	std::set<uint32_t> set_diff_old;
	std::set_difference(set_old.begin(), set_old.end(), set_new.begin(), set_new.end(), std::inserter(set_diff_old, set_diff_old.begin()));
	for (auto id : set_diff_old) {
		mRegions[id].RoleLeave(role);
	}

	//计算新老集合的差集，通知角色进入
	std::set<uint32_t> set_diff_new;
	std::set_difference(set_new.begin(), set_new.end(), set_old.begin(), set_old.end(), std::inserter(set_diff_new, set_diff_new.begin()));
	for (auto id : set_diff_new) {
		mRegions[id].RoleEnter(role);
	}

	//最后通知角色移动
	for (auto id : set_new) {
		mRegions[id].RoleMove(role);
	}

    if (oldRow != newRow || oldCol != newCol) {
        mRegions[oldRow * mRegionCols + oldCol].RemoveRole(role);
        mRegions[newRow * mRegionCols + newCol].AddRole(role);
    }

	SAFE_END;
	return true;
}

void MapAoi::RoleExit(Role* role)
{
	CALL_AROUND_REGION_FUC_BY_ROLE1(RoleExit, role);
}

void MapAoi::NotifyRoleOnlyUpdateAppearNtf(Role* role)
{
	CALL_AROUND_REGION_FUC_BY_ROLE1(NotifyRoleOnlyUpdateAppearNtf, role);
}

bool MapAoi::RemoveRole(Role* role)
{
    int regionIndex = GetRoleRegionIndex(role);
    if (regionIndex < 0) return false;
    return mRegions[regionIndex].RemoveRole(role);
}

bool MapAoi::AddRole(Role* role)
{
	int regionIndex = GetRoleRegionIndex(role);
	if (regionIndex < 0) return false;
	return mRegions[regionIndex].AddRole(role);
}

int MapAoi::GetRoleRegionIndex(Role* role)
{
    if (!role) return -1;

    int row = role->GetRolePosY() / mRegionHeight;
    if (row >= mRegionRows) return -1;

    int col = role->GetRolePosX() / mRegionWidth;
    if (col >= mRegionCols) return -1;

    return row * mRegionCols + col;
}

std::list<Role *> MapAoi::GetAllRoleByType(uint8_t roleType)
{
    std::list<Role *> roleList;

    for (auto i = 0, n = mRegionRows * mRegionCols; i < n; ++i)
        mRegions[i].GetAllRoleByType(roleList, roleType);

    return roleList;
}

bool MapAoi::IsHaveRoleInPoint(uint16_t posX, uint16_t posY)
{
	return GetRoleInPoint(posX, posY) != nullptr;
}

Role* MapAoi::GetRoleInPoint(uint16_t posX, uint16_t posY)
{
	uint16_t row = posY / mRegionHeight;
	uint16_t col = posX / mRegionWidth;

	if (row < 0 || row >= mRegionRows) {
		return nullptr;
	}

	if (col < 0 || col >= mRegionCols) {
		return nullptr;
	}

	return mRegions[row * mRegionCols + col].GetRoleInPoint(posX, posY);
}

void MapAoi::IsHaveRoleInPoint(uint32_t roleType, uint16_t posX, uint16_t posY, std::array<uint16_t, role_type_cnt>& arr, bool beAlive)
{
	uint16_t row = posY / mRegionHeight;
	uint16_t col = posX / mRegionWidth;

	if (row < 0 || row >= mRegionRows) {
		return;
	}

	if (col < 0 || col >= mRegionCols) {
		return;
	}

	std::pair<uint32_t, uint32_t> p{ role_type_none + 1 , role_type_cnt - 1};
	if (role_type_none != roleType)
	{
		p = { roleType ,roleType };
	}
	for (auto t = p.first; t <= p.second; ++t)
	{
		arr.at(t) = mRegions[row * mRegionCols + col].HaveRoleNum(t, posX, posY, beAlive);
	}
}

bool MapAoi::IsHaveRoleInPoint(uint32_t roleType, uint16_t posX, uint16_t posY)
{
	uint16_t row = posY / mRegionHeight;
	uint16_t col = posX / mRegionWidth;

	if (row < 0 || row >= mRegionRows) {
		return false;
	}

	if (col < 0 || col >= mRegionCols) {
		return false;
	}
	vector<Role*>vec;
	mRegions[row * mRegionCols + col].GetRoleInPoint(vec, posX, posY, roleType);
	for (auto& pMonster : vec)
	{
		if (!pMonster)continue;
		auto state = pMonster->GetRoleState();
		if (!state)continue;
		if (state->CheckAlive())return true;
	}
	return false;
}

bool MapAoi::IsRoleExist(Role *role)
{
    auto i = GetRoleRegionIndex(role);
    if (i < 0) return false;
    return mRegions[i].IsRoleExist(role);
}

void MapAoi::DisappearMonsterCorpseInPoint(uint16_t posX, uint16_t posY)
{
	uint16_t row = posY / mRegionHeight;
	uint16_t col = posX / mRegionWidth;

	if (row < 0 || row >= mRegionRows) {
		return;
	}

	if (col < 0 || col >= mRegionCols) {
		return;
	}
	vector<Role*>vec;
	mRegions[row * mRegionCols + col].GetRoleInPoint(vec, posX, posY, role_type_monster);

	for (auto& pMonster : vec)
	{
		if (!pMonster)continue;
		auto state = pMonster->GetRoleState();
		if (!state)continue;
		if (!state->CheckAlive())
		{
			mCurMap->RoleLeave(pMonster);
			RemoveRole(pMonster);
		}
	}
}

void MapAoi::ApplyFuncToAllRoles(Func &f, uint16_t type)
{
    if (!f) return;

    for (auto i = 0; i < mRegionRows; ++i) {
        for (auto j = 0; j < mRegionCols; ++j) {
            mRegions[i * mRegionCols + j].ApplyFuncToAllRoles(f,type);
        }
    }
}

void MapAoi::ApplyFuncToAllPlayersInAroundRegions(uint16_t x, uint16_t y, Func& f)
{
	if (!f) return;

	uint16_t row = y / mRegionHeight;
	uint16_t col = x / mRegionWidth;

	for (int i = row - AOI_LEN; i <= row + AOI_LEN; ++i) {
		for (int j = col - AOI_LEN; j <= col + AOI_LEN; ++j) {
			if (i >= 0 && i < mRegionRows && j >= 0 && j < mRegionCols) {
				mRegions[i * mRegionCols + j].ApplyFuncToAllRoles(f);
			}
		}
	}
}

void MapAoi::ApplyFuncToAllRolesInAroundRegions(uint16_t x, uint16_t y, Func &f)
{
    if (!f) return;

    uint16_t row = y / mRegionHeight;
    uint16_t col = x / mRegionWidth;

    for (int i = row - AOI_LEN; i <= row + AOI_LEN; ++i) {
        for (int j = col - AOI_LEN; j <= col + AOI_LEN; ++j) {
            if (i >= 0 && i < mRegionRows && j >= 0 && j < mRegionCols) {
                mRegions[i * mRegionCols + j].ApplyFuncToAllRoles(f);
            }
        }
    }
}

Role* MapAoi::GetNearstRoleByType(uint16_t posX, uint16_t posY, bool canGetStealth, uint8_t roleType, Role* origRole)
{
	Role* role = nullptr;
	uint16_t x = posX;
	uint16_t y = posY;
	uint16_t dis = 10000;

	uint16_t row = posY / mRegionHeight;
	uint16_t col = posX / mRegionWidth;
	for (int i = row - AOI_LEN; i <= row + AOI_LEN; ++i) {
		for (int j = col - AOI_LEN; j <= col + AOI_LEN; ++j) {
			if (i >= 0 && i < mRegionRows && j >= 0 && j < mRegionCols) {
				mRegions[i * mRegionCols + j].GetNearstRoleByType(posX, posY, canGetStealth, roleType, dis, role, origRole);
				if (dis <= 1) {
					return role;
				}
			}
		}
	}

	return role;
}

Role* MapAoi::GetNearstRoleByCustType(uint16_t posX, uint16_t posY, uint8_t roleType, Role* origRole)
{
	Role* role = nullptr;
	uint16_t x = posX;
	uint16_t y = posY;
	uint16_t dis = 10000;

	uint16_t row = posY / mRegionHeight;
	uint16_t col = posX / mRegionWidth;
	for (int i = row - AOI_LEN; i <= row + AOI_LEN; ++i) {
		for (int j = col - AOI_LEN; j <= col + AOI_LEN; ++j) {
			if (i >= 0 && i < mRegionRows && j >= 0 && j < mRegionCols) {
				mRegions[i * mRegionCols + j].GetNearstRoleByCustType(posX, posY, roleType, dis, role, origRole);
				if (dis <= 1) {
					return role;
				}
			}
		}
	}

	return role;
}

void MapAoi::GetAllRoleByTypeByName(std::vector<Role*>& vec, uint8_t roleType, const char* name)
{
	for (int i = 0; i < mRegionRows; ++i) {
		for (int j = 0; j < mRegionCols; ++j) {
				mRegions[i * mRegionCols + j].GetAllRoleByTypeByName(vec, roleType, name); 
		}
	}
}

void MapAoi::GetSingleRegionRoleByType(std::list<Role*>& list, uint8_t roleType, uint32_t x, uint32_t y)
{
	uint16_t row = y / mRegionHeight;
	uint16_t col = x / mRegionWidth;
	for (int i = row - AOI_LEN; i <= row + AOI_LEN; ++i) {
		for (int j = col - AOI_LEN; j <= col + AOI_LEN; ++j) {
			if (i >= 0 && i < mRegionRows && j >= 0 && j < mRegionCols) {
				mRegions[i * mRegionCols + j].GetAllRoleByType(list, roleType);
			}
		}
	}
}

int32_t MapAoi::GetMonsterNum()
{
	int32_t nMonsterNum = 0;

	for (auto i = 0; i < mRegionRows * mRegionCols; ++i) {
		nMonsterNum += mRegions[i].GetRoleNum(role_type_monster);
	}

    return nMonsterNum;
}

int32_t MapAoi::GetPlayerNum()
{
	int32_t nPlayerNum = 0;

	for (auto i = 0; i < mRegionRows * mRegionCols; ++i) {
		nPlayerNum += mRegions[i].GetRoleNum(role_type_player);
	}

	return nPlayerNum;
}

void MapAoi::SendRoleDirChangeNtf(Role* role, ProtoGS_TurnNtf& ntf)
{
	SEND_AROUND_REGION_MSG_BY_ROLE(SendRoleDirChangeNtf, role, ntf);
}

void MapAoi::SendRoleDieNtf(Role* role, ProtoMS_ObjDieNtf& ntf)
{
	SEND_AROUND_REGION_MSG_BY_ROLE(SendRoleDieNtf, role, ntf);

}

void MapAoi::SendRoleItemAppearNtf(ProtoMS_ItemAppearNtf4& ntf)
{
	SEND_AROUND_REGION_MSG_BY_POS(SendRoleItemAppearNtf, ntf.dst_x, ntf.dst_y, ntf);
}

void MapAoi::SendRoleObjDisappearNtf(uint16_t posX, uint16_t posY, ProtoMS_ObjDisappearNtf& ntf)
{
	SEND_AROUND_REGION_MSG_BY_POS(SendRoleObjDisappearNtf, posX, posY, ntf);
}

void MapAoi::SendRoleNameChangeNtf(Role* role, ProtoGS_PlayerSetNameNtf& ntf)
{
	SEND_AROUND_REGION_MSG_BY_ROLE(SendRoleNameChangeNtf, role, ntf);
}

void MapAoi::SendRoleWearTitleNtf(Role* role, ProtoGS_TitleWearNtf& ntf)
{
	SEND_AROUND_REGION_MSG_BY_ROLE(SendRoleWearTitleNtf, role, ntf);
}

void MapAoi::SendRoleUnWearTitleNtf(Role* role, ProtoGS_TitleUnWearNtf& ntf)
{
	SEND_AROUND_REGION_MSG_BY_ROLE(SendRoleUnWearTitleNtf, role, ntf);
}

void MapAoi::SendEffectAppearNtf(uint16_t posX, uint16_t posY, ProtoMS_EffectAppearNtf& ntf)
{
	SEND_AROUND_REGION_MSG_BY_POS(SendEffectAppearNtf, posX, posY, ntf);
}

void MapAoi::SendEffectDisAppearNtf(uint16_t posX, uint16_t posY, ProtoMS_EffectDisAppearNtf& ntf)
{
	SEND_AROUND_REGION_MSG_BY_POS(SendEffectDisAppearNtf, posX, posY, ntf);
}

#pragma region MyRegion
SceneItem* MapAoi::AddSceneItem(uint16_t id, uint16_t x, uint16_t y, uint16_t amount, uint16_t bind,
    uint16_t drop, uint64_t ownerGUID, uint64_t teamGUID)
{
	if (IsHaveRoleInPoint(x, y)) {
		return nullptr;
	}

	uint16_t row = y / mRegionHeight;
	uint16_t col = x / mRegionWidth;
	if (row >= 0 && row < mRegionRows && col >= 0 && col < mRegionCols) {
	
		return mRegions[row * mRegionCols + col].AddSceneItem(id, x, y, amount, bind, drop, ownerGUID, teamGUID);
	}

	return nullptr;
}

SceneItem* MapAoi::AddSceneItem(uint16_t x, uint16_t y, RoleItem* roleItem)
{
	if (IsHaveRoleInPoint(x, y)) {
		return nullptr;
	}

	uint16_t row = y / mRegionHeight;
	uint16_t col = x / mRegionWidth;
	if (row >= 0 && row < mRegionRows && col >= 0 && col < mRegionCols) {
		return mRegions[row * mRegionCols + col].AddSceneItem(x, y, roleItem);
	}

	return nullptr;
}

bool MapAoi::DestroySceneItem(uint16_t x, uint16_t y)
{
	CALL_REGION_FUC_BY_POS_RET(DestroySceneItem, x, y);
	return false;
}

bool MapAoi::DestroySceneItem(uint64_t itemGUID,uint16_t x, uint16_t y)
{
	CALL_ALL_REGION_FUC_BY_GUID_RET2(DestroySceneItem, itemGUID, x, y);
	return false;
}

SceneItem* MapAoi::GetSceneItem(uint16_t x, uint16_t y)
{
	CALL_REGION_FUC_BY_POS_RET(GetSceneItem, x, y);
	return nullptr;
}

SceneItem* MapAoi::GetSceneItem(uint64_t itemGUID)
{
	CALL_ALL_REGION_FUC_BY_GUID_RET(GetSceneItem, itemGUID)
	return nullptr;
}

void MapAoi::OnItemAppear(SceneItem *item)
{
	CALL_AROUND_REGION_FUC_BY_ITEM1(OnItemAppear, item);
}

void MapAoi::OnItemDisappear(SceneItem *item)
{
	CALL_AROUND_REGION_FUC_BY_ITEM1(OnItemDisappear, item);
}

SceneItem* MapAoi::GetPetPickableItem(Monster *pet)
{
    if (!pet) return 0;

    auto x = pet->GetRolePosX();
    auto y = pet->GetRolePosY();

    auto row = y / mRegionHeight;
    auto col = x / mRegionWidth;

    uint16_t dist = UINT16_MAX;
    SceneItem *item = nullptr;

    for (auto i = row - AOI_LEN; i <= row + AOI_LEN; ++i) {
        for (auto j = col - AOI_LEN; j <= col + AOI_LEN; ++j) {
            if (i >= 0 && i < mRegionRows && j >= 0 && j < mRegionCols) {
                mRegions[i * mRegionCols + j].GetPetPickableItem(pet, dist, item);
                if (dist == 0 && item) return item;
            }
        }
    }

    return item;
}

#pragma endregion

void MapAoi::AddJumpPointEffect(EffectPoint& data)
{
	if (!mCurMap)return;
	auto row = data.y / mRegionHeight;
	auto col = data.x / mRegionWidth;
	if ((row >= mRegionRows || row < 0) || (col >= mRegionCols || col < 0)) {
		LOG_ERROR("Add JumpPoint Failed! mapname :%s x:%d y:%d", mCurMap->GetName().c_str(), data.x, data.y);
	}

	mRegions[row * mRegionCols + col].AddJumpPointEffect(data);
}

void MapAoi::DelJumpPointEffect(EffectPoint& data)
{
	if (!mCurMap)return;
	auto row = data.y / mRegionHeight;
	auto col = data.x / mRegionWidth;
	if ((row >= mRegionRows || row < 0) || (col >= mRegionCols || col < 0)) {
		LOG_ERROR("Del JumpPoint Failed! mapname :%s x:%d y:%d", mCurMap->GetName().c_str(), data.x, data.y);
	}
	mRegions[row * mRegionCols + col].DelJumpPointEffect(data);
}

void MapAoi::AddTrapPointEffect(TrapPointEffect& data, uint32_t lifetime)
{
	if (!mCurMap)return;
	auto row = data.data.y / mRegionHeight;
	auto col = data.data.x / mRegionWidth;
	if ((row >= mRegionRows || row < 0) || (col >= mRegionCols || col < 0)) {
		LOG_ERROR("Add Trap Failed! mapname :%s x:%d y:%d", mCurMap->GetName().c_str(), data.data.x, data.data.y);
	}
	mRegions[row * mRegionCols + col].AddTrapPointEffect(data, lifetime);
}