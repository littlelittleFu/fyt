#include "stdafx.h"
#include "MapRegion.h"
#include "item_table.hpp"
#include "Map.h"
#include "ItemMap.h"
#include "Monster.h"

#pragma region MACRO DEFINES
#define SEND_AROUND_ROLE_MSG(func,role,msg)\
for (auto& it : mRoles[role_type_none]) {\
if(it.second == nullptr)continue;\
it.second->func(role, msg);\
}

#define SEND_AROUND_MSG(func,msg)\
for (auto& it : mRoles[role_type_player]) {\
if(it.second == nullptr)continue;\
it.second->func(msg);\
}
#pragma endregion

MapRegion::MapRegion() : mRow(0), mCol(0)
{
    mCurMap = nullptr;
}

MapRegion::~MapRegion()
{
    DestroyAllRoles();
}

void MapRegion::Init(Map* map, uint16_t row, uint16_t col, uint16_t regionWidth, uint16_t regionHeight)
{
    mCurMap = map;
	mRow = row;
	mCol = col;

    mRegionWidth = regionWidth;
    mRegionHeight = regionHeight;
}

void MapRegion::RoleEnter(Role* role)
{
	if (nullptr == role) {
		return;
	}
    auto type = role->GetType();
    if (!CheckType(type)) return;

	uint16_t row = role->GetRolePosY() / mRegionHeight;
	uint16_t col = role->GetRolePosX() / mRegionWidth;
	if (row == mRow && col == mCol) {
		mRoles[type][role->GetGUID()] = role;
        mRoles[role_type_none][role->GetGUID()] = role;
	}

	for (auto& it : mRoles[role_type_none]) {
        if (it.second == nullptr) continue;
		it.second->OnRoleEnter(role);
	}

    for (auto& it : mRoles[role_type_none]) {
        if (it.second == nullptr) continue;
		if (it.second->GetGUID() != role->GetGUID()) {
			role->OnRoleEnter(it.second);
		}
	}

    auto& ntf = gProtoMS_ItemAppearNtf4;
    for (auto& it : mSceneItems) {
        ntf.item_guid = it.second.GetGUID();
        ntf.template_id = it.second.GetTemplateID();
        ntf.dst_x = it.second.GetPosX();
        ntf.dst_y = it.second.GetPosY();
        strcpy_s(ntf.item_name, _countof(ntf.item_name), it.second.GetName().c_str());
        ntf.skill_id = it.second.GetSkillID();
        ntf.seed = 0;
        ntf.is_drop = it.second.GetIsDrop();
        ntf.owner_guid = it.second.GetOwnerGUID();
        ntf.team_guid = it.second.GetOwnerTeamGUID();
        role->SendRoleItemAppearNtf(ntf);
        role->OnItemAppear(&it.second);
    }

    MSG_BUFFER_DATA(ProtoMS_EffectAppearNtf, data);
    if (!mJumpPointEffectList.empty()) {
        for (auto& it : mJumpPointEffectList) {
            data.info[data.num++] = it.second;
        }
        data.type = effect_point_type_jump;
        role->SendEffectAppearNtf(data);
    }

    data.Clear();
    if (!mTrapEffectList.empty()) {
        for (auto& point : mTrapEffectList) {
            for (auto& trap : point.second) {
                data.info[data.num++] = trap.second.data;
                if (data.num == 100) {
                    role->SendEffectAppearNtf(data);
                    data.Clear();
                }
            }
        }
        if (data.num) {
            role->SendEffectAppearNtf(data);
        }
    }

}

void MapRegion::RoleLeave(Role* role)
{
	if (nullptr == role) {
		return;
	}
    auto type = role->GetType();
    if (!CheckType(type)) return;

	for (auto& it : mRoles[role_type_none]) {
		it.second->OnRoleLeave(role);
        role->OnRoleLeave(it.second);
	}

    mRoles[type].erase(role->GetGUID());
    mRoles[role_type_none].erase(role->GetGUID());
    auto& ntf = gProtoMS_ObjDisappearNtf;
    for (auto& it : mSceneItems) {
        ntf.obj_guid = it.second.GetGUID();
        role->SendRoleObjDisappearNtf(ntf);
        role->OnItemDisappear(&it.second);
    }

    MSG_BUFFER_DATA(ProtoMS_EffectDisAppearNtf, data);
    if (!mJumpPointEffectList.empty()) {
        for (auto& it : mJumpPointEffectList) {
            data.info[data.num++] = it.second;
        }
        data.type = effect_point_type_jump;
        role->SendEffectDisAppearNtf(data);
    }

    data.Clear();
    if (!mTrapEffectList.empty()) {
        for (auto& point : mTrapEffectList) {
            for (auto& trap : point.second) {
                data.info[data.num++] = trap.second.data;
                if (data.num == 100) {
                    role->SendEffectDisAppearNtf(data);
                    data.Clear();
                }
            }
        }
        if (data.num) {
            role->SendEffectDisAppearNtf(data);
        }
    }

}

void MapRegion::RoleMove(Role* role)
{
    if (!role) return;

    auto &players = mRoles[role_type_player];
    if (players.empty()) return;

    std::map<uint32_t, std::vector<uint32_t>> clsessidsMap;

    for (auto &it : players) {
        auto *player = static_cast<Player *>(it.second);
        if (!player || !player->IsOnline()) continue;
        auto gssessid = player->GetGsSessionID();
        if (gssessid == 0) continue;
        clsessidsMap[gssessid].push_back(player->GetClSessionID());
    }

    ProtoMS_MoveNtfEx data;
    data.guid  = role->GetGUID();
    data.type  = role->GetRoleAttr()->GetMoveType();
    data.dst_x = role->GetRolePosX();
    data.dst_y = role->GetRolePosY();

    SendDataBySessionID(clsessidsMap, data);
}

void MapRegion::RoleExit(Role* role)
{
    if (nullptr == role) {
        return;
    }
    auto type = role->GetType();
    if (!CheckType(type)) return;

    for (auto& it : mRoles[role_type_none]) {
        it.second->OnRoleExit(role);
    }

    mRoles[type].erase(role->GetGUID());
    mRoles[role_type_none].erase(role->GetGUID());
}

void MapRegion::NotifyRoleOnlyUpdateAppearNtf(Role* role)
{
    if (nullptr == role) {
        return;
    }
    auto type = role->GetType();
    if (!CheckType(type)) return;

    uint16_t row = role->GetRolePosY() / mRegionHeight;
    uint16_t col = role->GetRolePosX() / mRegionWidth;

    for (auto& it : mRoles[role_type_player]) {
        if (it.second == nullptr) continue;
        it.second->OnlyUpdateAppearNtf(role);
    }
}

bool MapRegion::RemoveRole(Role* role)
{
    if (!role) return false;
    auto type = role->GetType();
    if (!CheckType(type)) return false;

    mRoles[type].erase(role->GetGUID());
    return mRoles[role_type_none].erase(role->GetGUID()) == 1;
}

void MapRegion::DestroyAllRoles()
{
    for (auto &it : mRoles[role_type_none]) {
        it.second->OnLeaveCurMap();
        MapRoleMgr::GetInstance()->RemoveRole(it.second);
    }
    mRoles[role_type_none].clear();
    for (uint16_t type = role_type_none + 1; type < role_type_cnt; ++type)
    {
        mRoles[type].clear();
    }
}

bool MapRegion::AddRole(Role* role)
{
    if (!role) return false;

    uint16_t row = role->GetRolePosY() / mRegionHeight;
    uint16_t col = role->GetRolePosX() / mRegionWidth;
    if (row != mRow || col != mCol) return false;

    auto type = role->GetType();
    if (!CheckType(type)) return false;

    mRoles[type][role->GetGUID()] = role;
    mRoles[role_type_none][role->GetGUID()] = role;
    return true;
}

bool MapRegion::IsRoleExist(Role *role)
{
    if (!role) return false;
    auto guid = role->GetGUID();
    return mRoles[role_type_none].find(guid) != mRoles[role_type_none].end();
}

int32_t MapRegion::HaveRoleNum(uint32_t type, uint16_t posX, uint16_t posY, bool beAlive)
{
    if (type >= role_type_cnt) return 0;

    if (!posX && !posY)
    {
        if (!beAlive) return mRoles[type].size();
        int32_t cnt = 0;
        for (auto& e : mRoles[type])
        {
            if (e.second && e.second->CheckAlive()) cnt++;
        }
        return cnt;
    }

    int32_t cnt = 0;
    for (auto& it : mRoles[type]) {
        auto role = it.second;
        if (role == nullptr)continue;
        if (beAlive && !role->CheckAlive()) continue;
        if ((role->GetRolePosX() == posX && role->GetRolePosY() == posY))
            return  1;
    }
    return cnt;
}

int32_t MapRegion::GetRoleNum(uint32_t type, uint16_t posX, uint16_t posY, bool beAlive)
{
    if (type >= role_type_cnt) return 0;

    if (!posX && !posY)
    {
        if (!beAlive) return mRoles[type].size();
        int32_t cnt = 0;
        for (auto& e : mRoles[type])
        {
            if (e.second && e.second->CheckAlive()) cnt++;
        }
        return cnt;
    }

    int32_t cnt = 0;
    for (auto& it : mRoles[type]) {
        auto role = it.second;
        if (role == nullptr)continue;
        if (beAlive && !role->CheckAlive()) continue;
        if ((role->GetRolePosX() == posX && role->GetRolePosY() == posY))
            cnt += 1;
    }
    return cnt;
}

Role *MapRegion::GetRoleInPoint(uint16_t posX, uint16_t posY)
{
    for (auto &it : mRoles[role_type_none]) {
        auto role = it.second;
        if (role != nullptr && role->CheckAlive() && role->GetRolePosX() == posX && role->GetRolePosY() == posY) {
            return role;
        }
    }

    return nullptr;
}

void MapRegion::GetRoleInPoint(vector<Role*>&vec, uint16_t posX, uint16_t posY, uint32_t roleType, bool beAlive)
{
    if (!CheckType(roleType)) return;
    for (auto& it : mRoles[roleType]) {
        auto role = it.second;
        if (role == nullptr)continue;
        if (beAlive && !role->CheckAlive()) continue;
        if ((role->GetRolePosX() == posX && role->GetRolePosY() == posY))
            vec.push_back(role);
    }
}

void MapRegion::ApplyFuncToAllRoles(Func &f, uint16_t type)
{
    for (auto &it : mRoles[type]) {
        f(it.second);
    }
}

void MapRegion::ApplyFuncToAllPlayers(Func& f)
{
    for (auto& it : mRoles[role_type_player]) {
        f(it.second);
    }
}


void MapRegion::GetNearstRoleByType(uint16_t posX, uint16_t posY, bool canGetStealth, uint8_t roleType, uint16_t& dis, Role*& role, Role* origRole)
{
    if (!CheckType(roleType)) return;

    for (auto& it : mRoles[roleType]) {
        auto r = it.second;
        if (nullptr == r)continue;
        if (r == origRole) continue;
        if (!r->CheckAlive()) continue;
        if (!canGetStealth) {
            if (r->GetRoleProp(role_is_stealth) >= 1) continue;     // 隐身
        }
        if (nullptr != origRole && !origRole->TargetCanSelect(r)) continue;

        auto d = r->DistanceFromPos(posX, posY);
        if (d < dis) {
            role = r;
            dis = d;
            if (dis <= 1) {
                return;
            }
        }
    }
}

void MapRegion::GetNearstRoleByCustType(uint16_t posX, uint16_t posY, uint8_t roleCustType, uint16_t& dis, Role*& role, Role* origRole)
{
    switch (roleCustType)
    {
    case cust_role_red_name:
        for (auto& it : mRoles[role_type_player]) {
            auto r = it.second;
            //if (roleType != role_type_none && r->GetType() != roleType) {
            //    continue;
            //}
            if (nullptr == r)continue;
            if (r == origRole) continue;

            if (!r->CheckAlive()) continue;
            if (r->GetRoleProp(role_is_stealth) >= 1) continue;     // 隐身
            if (nullptr != origRole && !origRole->TargetCanSelect(r)) continue;

            if (!r->IsPlayer()) continue;
            auto tarrole = static_cast<Player*>(r);
            if (!tarrole->IsRedName())continue;
            auto d = tarrole->DistanceFromPos(posX, posY);
            if (d < dis) {
                role = tarrole;
                dis = d;
                if (dis <= 1) {
                    return;
                }
            }
        }
        break;
    default:
        break;
    }
}

void MapRegion::GetAllRoleByTypeByName(std::vector<Role*>& vec, uint8_t roleType, const char* name)
{
    if (!CheckType(roleType)) return;

    for (auto& i : mRoles[roleType])
    {
        if (i.second != nullptr && (strcmp(name, i.second->GetName().c_str()) == 0))
            vec.push_back(i.second);
    }
}

void MapRegion::GetAllRoleByType(std::list<Role *> &roleList, uint8_t roleType)
{
    if (!CheckType(roleType)) return;

    for (auto &it : mRoles[roleType])
        if (it.second != nullptr)
            roleList.push_back(it.second);
}

void MapRegion::SendRoleDirChangeNtf(Role* role, ProtoGS_TurnNtf& ntf)
{
    auto &players = mRoles[role_type_player];
    if (players.empty()) return;

    std::map<uint32_t, std::vector<uint32_t>> clsessidsMap;

    for (auto &it : players) {
        auto *player = static_cast<Player *>(it.second);
        if (!player || !player->IsOnline()) continue;
        clsessidsMap[player->GetGsSessionID()].push_back(player->GetClSessionID());
    }

    ProtoMS_TurnNtf data;
    data.guid = role->GetGUID();
    data.dir = role->GetRoleDir();

    SendDataBySessionID(clsessidsMap, data);
}

void MapRegion::SendRoleDieNtf(Role* role, ProtoMS_ObjDieNtf& ntf)
{
    SEND_AROUND_ROLE_MSG(SendRoleDieNtf, role, ntf);
}

void MapRegion::SendRoleItemAppearNtf(ProtoMS_ItemAppearNtf4& ntf)
{
    SEND_AROUND_MSG(SendRoleItemAppearNtf, ntf);
}

void MapRegion::SendRoleObjDisappearNtf(ProtoMS_ObjDisappearNtf& ntf)
{
    SEND_AROUND_MSG(SendRoleObjDisappearNtf, ntf);
}

void MapRegion::SendRoleNameChangeNtf(Role* role, ProtoGS_PlayerSetNameNtf& ntf)
{
    SEND_AROUND_MSG(SendRoleNameChangeNtf, ntf);
}

void MapRegion::SendRoleWearTitleNtf(Role* role, ProtoGS_TitleWearNtf& ntf)
{
    SEND_AROUND_MSG(SendRoleWearTitleNtf, ntf);
}

void MapRegion::SendRoleUnWearTitleNtf(Role* role, ProtoGS_TitleUnWearNtf& ntf)
{
    SEND_AROUND_MSG(SendRoleUnWearTitleNtf, ntf);
}

void MapRegion::SendEffectAppearNtf(ProtoMS_EffectAppearNtf& ntf)
{
    SEND_AROUND_MSG(SendEffectAppearNtf, ntf);
}

void MapRegion::SendEffectDisAppearNtf(ProtoMS_EffectDisAppearNtf& ntf)
{
    SEND_AROUND_MSG(SendEffectDisAppearNtf, ntf);
}


#pragma region 场景物品
SceneItem* MapRegion::AddSceneItem(uint16_t id, uint16_t x, uint16_t y, uint16_t amount, uint16_t bind,
    uint16_t drop, uint64_t ownerGUID, uint64_t teamGUID)
{
    if (nullptr == mCurMap) return nullptr;

    auto itemCfg = sItemConfig.Get(id);
    if (nullptr == itemCfg) {
        return nullptr;
    }

    uint32_t key = x << 16 | y;
    if (mSceneItems.find(key) != mSceneItems.end()) {
        return nullptr;
    }

    SceneItem &sceneItem = mSceneItems[key];
    sceneItem.SetGUID(GenerateObjID(E_OBJ_ITEM, ConfigInfo::GetInstance()));
    sceneItem.SetTemplateID(id);
    sceneItem.SetAmount(amount);
    sceneItem.SetIsBind(bind);
    sceneItem.SetPosX(x);
    sceneItem.SetPosY(y);
    sceneItem.SetName(itemCfg->Name);
    sceneItem.SetIsDrop(drop);
    sceneItem.SetExistingMapName(mCurMap->GetName());
    sceneItem.SetUse_count(itemCfg->UseCount);
    sceneItem.SetOwnerGUID(ownerGUID);
    sceneItem.SetOwnerTeamGUID(teamGUID);

    auto& ntf = gProtoMS_ItemAppearNtf4;
    ntf.dst_x = x;
    ntf.dst_y = y;
    ntf.is_drop = drop;
    ntf.item_guid = sceneItem.GetGUID();
    ntf.template_id = sceneItem.GetTemplateID();
    strcpy_s(ntf.item_name, _countof(ntf.item_name), sceneItem.GetName().c_str());
    ntf.skill_id = 0;
    ntf.seed = 0;
    ntf.owner_guid = sceneItem.GetOwnerGUID();
    ntf.team_guid = sceneItem.GetOwnerTeamGUID();
    mCurMap->SendRoleItemAppearNtf(ntf);
    mCurMap->OnItemAppear(&sceneItem);

    ItemMap::GetInstance()->AddItem(&sceneItem);

    TRIGGER_EVENT(mCurMap, trigger_item_appear, mCurMap->GetGUIDAsString(),
        sceneItem.GetGUIDAsString(), sceneItem.GetTemplateID(), sceneItem.GetName(), x, y);

    return &mSceneItems[key];
}

SceneItem* MapRegion::AddSceneItem(uint16_t x, uint16_t y, RoleItem* roleItem)
{
    if (nullptr == mCurMap) return nullptr;

    uint32_t key = x << 16 | y;
    if (mSceneItems.find(key) != mSceneItems.end()) {
        return nullptr;
    }

    mSceneItems.emplace(std::make_pair(key, SceneItem(roleItem)));
    auto& sceneItem = mSceneItems[key];
    sceneItem.SetPosX(x);
    sceneItem.SetPosY(y);
    sceneItem.SetIsDrop(0);
    sceneItem.SetExistingMapName(mCurMap->GetName());

    auto& ntf = gProtoMS_ItemAppearNtf4;
    ntf.dst_x = x;
    ntf.dst_y = y;
    ntf.is_drop = sceneItem.GetIsDrop();
    ntf.item_guid = sceneItem.GetGUID();
    ntf.template_id = sceneItem.GetTemplateID();
    strcpy_s(ntf.item_name, _countof(ntf.item_name), sceneItem.GetName().c_str());
    ntf.skill_id = 0;
    ntf.seed = 0;
    ntf.owner_guid = sceneItem.GetOwnerGUID();
    ntf.team_guid = sceneItem.GetOwnerTeamGUID();
    mCurMap->SendRoleItemAppearNtf(ntf);
    mCurMap->OnItemAppear(&sceneItem);

    ItemMap::GetInstance()->AddItem(&sceneItem);

    TRIGGER_EVENT(mCurMap, trigger_item_appear, mCurMap->GetGUIDAsString(),
        sceneItem.GetGUIDAsString(), sceneItem.GetTemplateID(), sceneItem.GetName(), x, y);

    return &mSceneItems[key];
}

bool MapRegion::DestroySceneItem(uint16_t x, uint16_t y)
{
    if (nullptr == mCurMap) return false;

    uint32_t key = x << 16 | y;
    if (mSceneItems.find(key) != mSceneItems.end()) {
        auto& sceneItem = mSceneItems[key];
        auto guid = sceneItem.GetGUID();

        auto& ntf = gProtoMS_ObjDisappearNtf;
        ntf.obj_guid = guid;
        mCurMap->SendRoleObjDisappearNtf(x, y, ntf);
        mCurMap->OnItemDisappear(&sceneItem);

        TRIGGER_EVENT(mCurMap, trigger_item_disappear, mCurMap->GetGUIDAsString(), std::to_string(guid),
            sceneItem.GetTemplateID(), sceneItem.GetName(), sceneItem.GetPosX(), sceneItem.GetPosY());

        RemoveItemFromMap(sceneItem);

        mSceneItems.erase(key);
        return true;
    }

    return  false;
}

bool MapRegion::DestroySceneItem(uint64_t itemGUID, uint16_t x, uint16_t y)
{
    if (nullptr == mCurMap) return false;

    for (auto it = mSceneItems.begin(); it != mSceneItems.end(); ++it) {
        if (it->second.GetGUID() == itemGUID) {
            auto& sceneItem = it->second;

            auto& ntf = gProtoMS_ObjDisappearNtf;
            ntf.obj_guid = itemGUID;
            mCurMap->SendRoleObjDisappearNtf(sceneItem.GetPosX(), sceneItem.GetPosY(), ntf);
            mCurMap->OnItemDisappear(&sceneItem);

            TRIGGER_EVENT(mCurMap, trigger_item_disappear, mCurMap->GetGUIDAsString(), sceneItem.GetGUIDAsString(),
                sceneItem.GetTemplateID(), sceneItem.GetName(), sceneItem.GetPosX(), sceneItem.GetPosY());

            RemoveItemFromMap(sceneItem);

            mSceneItems.erase(it);
            return true;
        }
    }

    return false;
}

void MapRegion::RemoveItemFromMap(const SceneItem &item)
{
    auto *itemMap = ItemMap::GetInstance();
    if (!itemMap) return;

    auto id = item.GetGUID();

    auto *cur = itemMap->GetItem(id);
    if (cur != &item) return;           // 被玩家捡起

    itemMap->RemoveItem(id);
}

SceneItem* MapRegion::GetSceneItem(uint16_t x, uint16_t y)
{
    uint32_t key = x << 16 | y;
    if (mSceneItems.find(key) != mSceneItems.end()) {
        return &mSceneItems[key];
    }
    return nullptr;
}

SceneItem* MapRegion::GetSceneItem(uint64_t itemGUID)
{
    for (auto it = mSceneItems.begin(); it != mSceneItems.end(); ++it) {
        if (it->second.GetGUID() == itemGUID) {
            return &it->second;
        }
    }

    return nullptr;
}

void MapRegion::OnItemAppear(SceneItem *item)
{
    if (!item) return;

    for (auto &it : mRoles[role_type_player]) {
        if (!it.second) continue;
        it.second->OnItemAppear(item);
    }
}

void MapRegion::OnItemDisappear(SceneItem *item)
{
    if (!item) return;

    for (auto &it : mRoles[role_type_player]) {
        if (!it.second) continue;
        it.second->OnItemDisappear(item);
    }
}

void MapRegion::GetPetPickableItem(Monster *pet, uint16_t &dist, SceneItem *&item)
{
    if (!pet) return;

    auto *cfg = pet->GetConfig();
    if (!cfg) return;

    auto viewRange = cfg->VieRange;

    auto x0 = pet->GetRolePosX();
    auto y0 = pet->GetRolePosY();

    for (auto &it : mSceneItems) {

        auto &sceneItem = it.second;

        auto x1 = sceneItem.GetPosX();
        auto y1 = sceneItem.GetPosY();

        auto dist0 = Utility::CalcLongerDistance(x0, y0, x1, y1);
        if (dist0 > viewRange) continue;

        if (dist0 >= dist) continue;

        if (!sceneItem.IsCanPickup(pet)) continue;

        item = &sceneItem;
        dist = dist0;
    }
}

#pragma endregion


void MapRegion::AddJumpPointEffect(EffectPoint& data)
{
    auto key = data.x << 16 | data.y;
    mJumpPointEffectList[key] = data;
}

void MapRegion::DelJumpPointEffect(EffectPoint& data)
{
    auto key = data.x << 16 | data.y;
    auto iter = mJumpPointEffectList.find(key);
    if (iter != mJumpPointEffectList.end()) {
        mJumpPointEffectList.erase(iter);
    }
}

void MapRegion::AddTrapPointEffect(TrapPointEffect& data, uint32_t lifetime)
{
    if (!mCurMap)return;
    TimerData timer;
    timer.interval = lifetime;
    timer.loop = false;
    timer.callBack = [=](const TimerData&) {
        DelTrapPointEffect(data);
    };

    auto key = data.data.x << 16 | data.data.y;
    auto pointIter = mTrapEffectList.find(key);
    if (pointIter != mTrapEffectList.end()) {
        auto skillIter = pointIter->second.find(data.SkillID);
        if (skillIter != pointIter->second.end()) {
            ITimeHelper::GetInstance()->RemoveTimer(skillIter->second.timerID);
            mCurMap->DelTrapTimer(skillIter->second.timerID);
            skillIter->second.timerID = ITimeHelper::GetInstance()->AddTimer(timer);
            mCurMap->AddTrapTimer(skillIter->second.timerID);
            return;
        }
    }

    data.timerID = ITimeHelper::GetInstance()->AddTimer(timer);
    mCurMap->AddTrapTimer(data.timerID);
    mTrapEffectList[key][data.SkillID] = data;
    ProtoMS_EffectAppearNtf info;
    info.info[info.num++] = data.data;
    info.type = effect_point_type_trap;
    mCurMap->GetMapAoi().SendEffectAppearNtf(data.data.x, data.data.y, info);
}

void MapRegion::DelTrapPointEffect(const TrapPointEffect& data)
{
    if (!mCurMap)return;
    auto key = data.data.x << 16 | data.data.y;
    auto pointIter = mTrapEffectList.find(key);
    if (pointIter != mTrapEffectList.end()) {
        auto skillIter = pointIter->second.find(data.SkillID);
        if (skillIter != pointIter->second.end()) {
            ProtoMS_EffectDisAppearNtf info;
            info.info[info.num++] = data.data;
            info.type = effect_point_type_trap;
            mCurMap->DelTrapTimer(skillIter->second.timerID);
            mCurMap->GetMapAoi().SendEffectDisAppearNtf(data.data.x, data.data.y, info);
            pointIter->second.erase(skillIter);
        }
        if (pointIter->second.empty()) {
            mTrapEffectList.erase(pointIter);
        }
    }
}