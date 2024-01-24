#include "stdafx.h"
#include "Map.h"
#include "ILogHelper.h"

#include "ProtoClient3.h"
#include "ISession.h"
#include "CNetManager.h"
#include <Session.h>
#include "SessionFactory.h"

#include "monster_gen_table.h"

#include "RoleMove.h"
#include "saferegion_table.h"
#include "ItemMap.h"
#include "BossInfo.h"

Map::Map()
{
	mScriptName = "MapBase";
	auto guid = GenerateObjID(E_OBJ_MAP, ConfigInfo::GetInstance());
    SetGUID(guid);
}

Map::~Map()
{
	std::set<uint32_t> tmpTimerId = mTimerId;
	for (auto it = tmpTimerId.begin(); it != tmpTimerId.end();) {
		RemoveLuaTimer(*it);
	}
	RemoveAllTrapTimer();
	OnDestroy();
}


bool Map::Init(DATA::Map* mapConfig)
{
	SAFE_BEGIN_EX;
	if (!mapConfig) return false;

    mTemplateID = mapConfig->Id;
    SetName(mapConfig->KeyName);

	if (!mMapGrid.Init(mapConfig->Logic)) {
		LOG_ERROR("Map::Init failed. can not init map grid data");
		return false;
	}

	SetRegionSize(10, 10);

	mMapAoi.Init(this, mMapGrid.GetWidth(), mMapGrid.GetHeight(), mRegionWidth, mRegionHeight);

	InitJumpPointForbit(mapConfig);

	GenMapMonster();
	GenMapNPC();

    std::string script(mapConfig->Script);
	if (!script.empty() && script != "0") {
        AddTrigger(trigger_map_create, script + ".on_map_create");
        AddTrigger(trigger_map_destroy, script + ".on_map_destroy");
	}

	return true;
	SAFE_END_EX(false);
}

void Map::OnDestroy()
{
    const auto *cfg = GetMapConfig();

	if (cfg) {
		std::string script(cfg->Script);
		if (!script.empty() && script != "0") {
			TriggerEvent(trigger_map_destroy, GetGUIDAsString(), cfg->KeyName);
		}
	}
	MapRoleMgr::GetInstance()->OnDestroy(this);
}

void Map::Update(int delta)
{
	UpdateEventMap();
    UpdateTrapSkillRegionState(delta);
}

void Map::DisAppearMonster(Monster* monster, Role* player)
{
}
void Map::AppearMonster(Monster* monster, Role* player)
{
}

void Map::RoleEnter(Role* role)
{
	if (nullptr == role) {
		return;
	}

	role->OnEnterMap(this);
	mMapAoi.RoleEnter(role);

	if (nullptr != role) {
		if (IS_PLAYER_GUID(role->GetGUID()) || IS_DUMMY_GUID(role->GetGUID()) ||
            IS_STALL_DUMMY_GUID(role->GetGUID()) || IS_PLAYER_DOPLGANR_GUID(role->GetGUID())) {
			TRIGGER_EVENT(role, trigger_enter_map, role->GetGUIDAsString());
			if (role->IsInSafeRegion() && IS_PLAYER_GUID(role->GetGUID()))
			{
				role->SetCalculateAttribute(true);
			}

		}
		else if (IS_MONSTER_GUID(role->GetGUID())) {
			auto monster = static_cast<Monster*>(role);
			TRIGGER_EVENT(monster, trigger_monster_appear, monster->GetGUIDAsString(), monster->GetConfig()->Id,
				monster->GetConfig()->KeyName, monster->GetRolePosX(), monster->GetRolePosY());
		}
		else if (IS_NPC_GUID(role->GetGUID())) {
			auto npc = static_cast<Npc*>(role);
			TRIGGER_EVENT(npc, trigger_npc_appear, npc->GetGUIDAsString(), npc->GetConfig()->Id,
				npc->GetConfig()->KeyName, npc->GetRolePosX(), npc->GetRolePosY());
		}
		else if (IS_PET_GUID(role->GetGUID()))
		{
			auto pet = static_cast<Pet*>(role);
			TRIGGER_EVENT(pet, trigger_pet_appear, pet->GetGUIDAsString(), pet->GetConfig()->Id,
				pet->GetConfig()->KeyName, pet->GetRolePosX(), pet->GetRolePosY());
		}
	}

    ApplyOnRoleEnterFunc(role);
}

void Map::RoleLeave(Role* role, bool isReleasedGrid)
{
	if (!role) return;

	if (!IsRoleExist(role))
	{
		return;
	}
		

	if (IS_PLAYER_GUID(role->GetGUID()) || IS_DUMMY_GUID(role->GetGUID()) || IS_STALL_DUMMY_GUID(role->GetGUID())) {
		TRIGGER_EVENT(role, trigger_leave_map, role->GetGUIDAsString());
	}
	else if (IS_MONSTER_GUID(role->GetGUID())) {
		auto monster = static_cast<Monster*>(role);
		TRIGGER_EVENT(monster, trigger_monster_disappear, monster->GetGUIDAsString(), monster->GetConfig()->Id,
			monster->GetConfig()->KeyName, monster->GetRolePosX(), monster->GetRolePosY());
	}
	else if (IS_NPC_GUID(role->GetGUID())) {
		auto npc = static_cast<Npc*>(role);
		TRIGGER_EVENT(npc, trigger_npc_disappear, npc->GetGUIDAsString(), npc->GetConfig()->Id,
			npc->GetConfig()->KeyName, npc->GetRolePosX(), npc->GetRolePosY());
	}
	else if (IS_PET_GUID(role->GetGUID())) {
		auto pet = static_cast<Pet*>(role);

		TRIGGER_EVENT(pet, trigger_pet_disappear, pet->GetGUIDAsString(), pet->GetConfig()->Id,
			pet->GetConfig()->KeyName, pet->GetRolePosX(), pet->GetRolePosY());
	}

	mMapAoi.RoleLeave(role);
	if (isReleasedGrid) role->ReleaseGrid();

    ApplyOnRoleLeaveFunc(role);
}

bool Map::RoleMove(Role* role, uint16_t oldX, uint16_t oldY)
{
	if (nullptr == role) {
		return true;
	}
	return mMapAoi.RoleMove(role, oldX, oldY);
}

void Map::RoleExit(Role* role)
{
	if (nullptr == role) {
		return;
	}
	mMapAoi.RoleExit(role);

	if (nullptr != role) {
		if (IS_PLAYER_GUID(role->GetGUID()) || IS_DUMMY_GUID(role->GetGUID())) {
			TRIGGER_EVENT(role, trigger_leave_map, role->GetGUIDAsString());
		}
	}
}

void Map::Jump(Role* role)
{
	auto& row = sJumpConfig.GetData();
	auto pox = role->GetRolePosX();
	auto poy = role->GetRolePosY();
	if (!GetMapGrid().IsJPForbid(pox, poy)) return;
	for (size_t i = 0; i < row.size(); i++) {
		if (0 == strcmp(row[i]->from_map, this->GetName().c_str())) {
			auto left = row[i]->from_left;
			auto top = row[i]->from_top;
			auto width = row[i]->from_width;
			auto height = row[i]->from_height;

			if (pox <= left + width && pox >= left && poy <= top + height && poy >= top) {
				auto* sitem = GetSceneItem(pox, poy);

				auto toMap = MapMgr::GetInstance()->FindMap(row[i]->to_map);
				if (!toMap)return;
				bool canjump = true;
				TRIGGER_EVENT_RET<bool>(canjump, trigger_pre_enter_jump, role->GetGUIDAsString(), this->GetGUIDAsString(), toMap->GetGUIDAsString());

				if (canjump)
				{
					if (sitem)
					{
						auto player = static_cast<Player*>(role);
						player->SendObjDisappearNtfToGSBySingle(sitem->GetGUID());
					}
					role->NotifyJump(row[i]->to_map, row[i]->to_left, row[i]->to_top, (uint16_t)jump_map_type::sys_jump_map_point);
				}
				return;
			}
		}
	}
	auto key = pox << 16 | poy;
	auto iter = mDynJumpPointList.find(key);
	if (iter != mDynJumpPointList.end())
	{
		auto* sitem = GetSceneItem(pox, poy);

		auto toMap = MapMgr::GetInstance()->FindMap(iter->second.to_map);
		if (!toMap)return;
		bool canjump = true;
		TRIGGER_EVENT_RET<bool>(canjump,trigger_pre_enter_jump, role->GetGUIDAsString(), this->GetGUIDAsString(), toMap->GetGUIDAsString());

		if (canjump)
		{
			if (sitem)
			{
				auto player = static_cast<Player*>(role);
				player->SendObjDisappearNtfToGSBySingle(sitem->GetGUID());
			}
			role->NotifyJump(iter->second.to_map, iter->second.to_left, iter->second.to_top, (uint16_t)jump_map_type::dyn_jump_map_point);
		}
		return;
	}
}

void Map::SetRegionSize(uint16_t regionWidth, uint16_t regionHeight)
{
	mRegionWidth = regionWidth;
	mRegionHeight = regionHeight;
}

bool Map::GetRandBlankPointInRange(uint16_t left, uint16_t top, uint16_t width, uint16_t height, uint16_t& posX, uint16_t& posY, bool mustBlank, bool excludeJP)
{
    if (width == 0) width = 1;
    if (height == 0) height = 1;

    auto nMapWidth = GetWidth();
    auto nMapHeight = GetHeight();

    if (width > nMapWidth) width = nMapWidth;
    if (height > nMapHeight) height = nMapHeight;

	int count = 0;
	int count_max = int(width) * height * 2;
	while (true) {
		posX = Tools::GenerateRandomInteger<uint16_t>(left, left + width - 1);
		posY = Tools::GenerateRandomInteger<uint16_t>(top, top + height - 1);

		if (!mMapGrid.IsForbid(posX, posY) && !mMapAoi.IsHaveRoleInPoint(posX, posY)) {
			if (excludeJP && mMapGrid.IsJPForbid(posX, posY)) {
				count += 1;
				if (count >= count_max) {
					break;
				}
				continue;
			}
			return true;
		}

		count += 1;
		if (count >= count_max) {
			break;
		}
	}

    if (!mustBlank) {
        posX = Tools::GenerateRandomInteger<uint16_t>(left, left + width - 1);
        posY = Tools::GenerateRandomInteger<uint16_t>(top, top + height - 1);
		if (excludeJP && mMapGrid.IsJPForbid(posX, posY)) {
			return false;
		}
        return true;
    }

	return false;
}
 
void Map::GetAllBlankPointInRange(uint16_t x, uint16_t y, uint16_t rangeX, uint16_t rangeY, std::vector<std::pair<uint16_t, uint16_t>>& vec)
{
	auto ltx = x - rangeX;
	auto lty = y + rangeY;
	for (auto i = ltx; i <= ltx + 2 * rangeX; ++i)
	{
		for (auto j = lty; j >= lty - 2 * rangeY; --j)
		{
			if (i >= mMapGrid.GetWidth() || j >= mMapGrid.GetHeight() || j < 0 || i < 0)continue;
			if (!mMapGrid.IsForbid(i, j))
			{
				vec.emplace_back(std::make_pair(i, j));
			}
		}
	}
}

Monster* Map::GenMonster(DATA::Monster* monster_cfg, uint16_t left, uint16_t top,
	uint16_t width, uint16_t height, uint8_t dir, uint64_t lastGUID, bool isCastle)
{
	if (!monster_cfg) return nullptr;
	uint16_t posX, posY;

	if (isCastle) {
		if (!GetRandBlankPointInRange(left, top, width, height, posX, posY, false)) {
			LOG_ERROR("Cur Monster Can't Born ID:%d", monster_cfg->Id);
			return nullptr;
		}
	}
	else {
		if (!GetRandBlankPointInRange(left, top, width, height, posX, posY, false, true)) {
			LOG_ERROR("Cur Monster Can't Born ID:%d", monster_cfg->Id);
			return nullptr;
		}
	}

	auto monster = MapRoleMgr::GetInstance()->CreateMonster(monster_cfg->Id);
	if (nullptr == monster) {
		return nullptr;
	}

	monster->SetRolePosNoTakeGrid(posX, posY);
	monster->SetBornPos(posX, posY);
	monster->SetTmpStayPos(posX, posY);
	monster->SetRoleDir(dir);
	RoleEnter(monster);
	monster->TakeGrid();

	monster->UpdateBossInfoWhenGen(monster_cfg, lastGUID);
	return monster;
}

void Map::GenMapMonsterByName(const std::string& Name, uint16_t left, uint16_t top,
	uint16_t width, uint16_t height, uint16_t num, uint8_t dir, bool isCastle)
{
	auto monster_cfg = sMonsterConfig.GetByKeyName(Name);
	if (nullptr == monster_cfg) {
		LOG_WARN("nullptr == monster_cfg");
		return;
	}

	CLuaObject luaRet = NewLuaObj();
	for (int i = 0,j = 0; i < num; ++i) {
		auto monster = GenMonster(monster_cfg, left, top, width, height, dir, 0, isCastle);
		if (monster == nullptr) {
			continue;
		}
		luaRet[++j] = monster->GetGUIDAsString();
	}
	LuaRet = luaRet;
}

void Map::GenMapMonsterByID(uint16_t id, uint16_t left, uint16_t top,
	uint16_t width, uint16_t height, uint16_t num, uint8_t dir)
{
	auto monster_cfg = sMonsterConfig.Get(id);
	if (nullptr == monster_cfg) {
		LOG_WARN("nullptr == monster_cfg");
		return;
	}

	CLuaObject luaRet = NewLuaObj();
	for (int i = 0, j = 0; i < num; ++i) {
		auto monster = GenMonster(monster_cfg, left, top, width, height, dir);
		if (monster == nullptr) {
			continue;
		}
		luaRet[++j] = monster->GetGUIDAsString();
	}
	LuaRet = luaRet;
}

void Map::GenMapMonster()
{
    const auto *cfg = GetMapConfig();
    if (!cfg) return;

	auto& monster_gen_datas = sMonsterGenConfig.GetData();
	for (auto& gen_data : monster_gen_datas) {
		if (strcmp(gen_data->map_name, cfg->KeyName) != 0) {
			continue;
		}

		auto monster_cfg = sMonsterConfig.GetByKeyName(gen_data->KeyName);
		if (nullptr == monster_cfg) {
			continue;
		}

		for (int i = 0; i < gen_data->number; ++i) {
			auto monster = GenMonster(monster_cfg, gen_data->left, gen_data->top, gen_data->width, gen_data->height, gen_data->direction);
			if (nullptr == monster) {
				continue;
			}

			monster->SetCamp(gen_data->camp);
            monster->SetRebornTime(gen_data->reborn);
            monster->SetRebornRegion(gen_data->left, gen_data->top, gen_data->width, gen_data->height);
            monster->SetRebornDir(gen_data->direction);

			RoleEnter(monster);
		}
	}
}

int Map::GetMonsterNum()
{
    return mMapAoi.GetMonsterNum();
}

void Map::GenMapNPC()
{
    const auto *cfg = GetMapConfig();
    if (!cfg) return;

	auto& npcGenData = sNpcGenConfig.GetData();

	for (auto pData : npcGenData) {

		if (strcmp(pData->map_name, cfg->KeyName) != 0) continue;

		GenMapNPCByKeyName(pData->KeyName, pData->x, pData->y, pData->direction);
	}
}

std::string Map::GenMapNPCByKeyName(const std::string& keyName, uint16_t x, uint16_t y, uint8_t direction)
{
	auto pNpcConfig = sNpcConfig.GetByKeyName(keyName);
	if (!pNpcConfig) return "";

	auto pNPC = MapRoleMgr::GetInstance()->CreateNpc(pNpcConfig->Id);
	if (!pNPC) return "";

	pNPC->OnEnterMap(this);
	pNPC->SetRolePos(x, y);
	pNPC->SetRoleDir(direction);
	RoleEnter(pNPC);
	return pNPC->GetGUIDAsString();
}

void Map::DelMapNPCByGuid(uint64_t guid)
{
	auto* npc = MapRoleMgr::GetInstance()->FindNpc(guid);
	if (!npc) return;

	RoleLeave(npc);
	MapRoleMgr::GetInstance()->RemoveNpc(guid);
}

Role* Map::GetRoleInPoint(uint16_t posX, uint16_t posY)
{
	return mMapAoi.GetRoleInPoint(posX, posY);
}

std::vector<Role *> Map::GetRolesInSameCircle(uint16_t x0, uint16_t y0, uint8_t radius, uint8_t roleType)
{
	int w = static_cast<int>(GetWidth());
	int h = static_cast<int>(GetHeight());

	int x, y, l, r, t, b;
	std::vector<Role *> roles;

	auto GetRole = [&]
	{
		auto *role = GetRoleInPoint(static_cast<uint16_t>(x), static_cast<uint16_t>(y));
		if (!role) return;
		if (roleType != role_type_none && role->GetType() != roleType) return;
		roles.push_back(role);
	};

	if (radius == 0)
	{
		x = x0;
		y = y0;
		GetRole();
		return roles;
	}

	y = y0 - radius;
	if (y >= 0)
	{
		l = std::max<int>(x0 - radius, 0);
		r = std::min<int>(x0 + radius - 1, w - 1);
		for (x = l; x <= r; ++x) GetRole();
	}

	x = x0 + radius;
	if (x < w)
	{
		t = std::max<int>(y0 - radius, 0);
		b = std::min<int>(y0 + radius - 1, h - 1);
		for (y = t; y <= b; ++y) GetRole();
	}

	y = y0 + radius;
	if (y < h)
	{
		r = std::min<int>(x0 + radius, w - 1);
		l = std::max<int>(x0 - radius + 1, 0);
		for (x = r; x >= l; --x) GetRole();
	}

	x = x0 - radius;
	if (x >= 0)
	{
		b = std::min<int>(y0 + radius, h - 1);
		t = std::max<int>(y0 - radius + 1, 0);
		for (y = b; y >= t; --y) GetRole();
	}

	return roles;
}

std::vector<SceneItem *> Map::GetSceneItemsInSameCircle(uint16_t x0, uint16_t y0, uint8_t radius)
{
    std::vector<SceneItem *> items;

    int w = static_cast<int>(GetWidth());
    int h = static_cast<int>(GetHeight());
    int x, y, l, r, t, b;

    auto GetItem = [&]
    {
        auto *item = GetSceneItem(static_cast<uint16_t>(x), static_cast<uint16_t>(y));
        if (!item) return;
        items.push_back(item);
    };

    if (radius == 0)
    {
        x = x0;
        y = y0;
        GetItem();
        return items;
    }

    y = y0 - radius;
    if (y >= 0)
    {
        l = std::max<int>(x0 - radius, 0);
        r = std::min<int>(x0 + radius - 1, w - 1);
        for (x = l; x <= r; ++x) GetItem();
    }

    x = x0 + radius;
    if (x < w)
    {
        t = std::max<int>(y0 - radius, 0);
        b = std::min<int>(y0 + radius - 1, h - 1);
        for (y = t; y <= b; ++y) GetItem();
    }

    y = y0 + radius;
    if (y < h)
    {
        r = std::min<int>(x0 + radius, w - 1);
        l = std::max<int>(x0 - radius + 1, 0);
        for (x = r; x >= l; --x) GetItem();
    }

    x = x0 - radius;
    if (x >= 0)
    {
        b = std::min<int>(y0 + radius, h - 1);
        t = std::max<int>(y0 - radius + 1, 0);
        for (y = b; y >= t; --y) GetItem();
    }

    return items;
}

bool Map::IsGridAvail(uint16_t x, uint16_t y)
{
	if (mMapGrid.IsForbid(x, y) || mMapGrid.IsMForbid(x, y)) return false;

	if (GetRoleInPoint(x, y)) return false;

	return true;
}

void Map::DisappearMonsterCorpseInPoint(uint16_t posX, uint16_t posY)
{
	mMapAoi.DisappearMonsterCorpseInPoint(posX, posY);
}

void Map::ApplyFuncToAllRoles(Func f, uint16_t type)
{
	mMapAoi.ApplyFuncToAllRoles(f, type);
}

void Map::ApplyFuncToAllRolesInAroundRegions(uint16_t x, uint16_t y, Func f)
{
	mMapAoi.ApplyFuncToAllRolesInAroundRegions(x, y, f);
}

void Map::ApplyFuncToAllPlayersInAroundRegions(uint16_t x, uint16_t y, Func f)
{
	mMapAoi.ApplyFuncToAllPlayersInAroundRegions(x, y, f);
}

bool Map::IsSafeRegion(uint16_t  posx, uint16_t posy)
{
	std::vector<DATA::RegionCommon>vec;
	GetTypeRegion(region_safe, vec);
	if (vec.empty())return false;
	for (auto& i : vec)
	{
		//标准矩形
		if (i.width && i.height)
		{
			if ((posx >= i.left && posy >= i.top) && posx <= (i.left + i.width) && posy <= (i.top + i.height)) return true;
		}
		else//旋转矩形
		{

			auto IsInRhombus = [=](uint16_t posx, uint16_t posy, uint16_t left, uint16_t top, uint16_t left2, uint16_t top2) {
				int _Size = abs(top2 - top);  //_Size为菱形宽高
				//首先将坐标系移动到菱形中心，则测试点会相应移动
				int X = posx - left;
				int Y = posy - (min(top,top2) + _Size / 2);
				if (abs(X) + abs(Y) <= _Size / 2)
					return true;
				return false;
			};

			return IsInRhombus(posx, posy, i.left, i.top, i.left2, i.top2);
		}
	}
	return false;
}

void Map::AddJumpPoint(const std::string& from_guid, const std::string& to_guid, uint16_t from_x, uint16_t from_y, uint16_t to_x, uint16_t to_y, uint32_t enterEffect, uint32_t leaveEffect)
{
	auto from_map = MapMgr::GetInstance()->FindMapByGUID(std::stoull(from_guid));
	auto to_map = MapMgr::GetInstance()->FindMapByGUID(std::stoull(to_guid));
	if (!from_map || !to_map)
	{
		LOG_ERROR("Can't find Map Guid");
		return;
	}
	auto key = from_x << 16 | from_y;
	DATA::Jump value;
	value.from_left = from_x;
	value.from_top = from_y;
	value.to_left = to_x;
	value.to_top = to_y;
	strcpy_s(value.to_map, _countof(value.to_map), to_map->GetMapConfig()->KeyName);
	mDynJumpPointList[key] = value;

	from_map->AddJumpPoint(from_x, from_y, enterEffect);
	to_map->AddJumpPoint(to_x, to_y, leaveEffect);
}

void Map::AddJumpPoint(uint16_t x, uint16_t y, uint32_t effect)
{
	ProtoMS_EffectAppearNtf data;
	EffectPoint info;
	info.x = x;
	info.y = y;
	info.effect = effect;
	data.info[data.num++] = info;
	data.type = effect_point_type_jump;
	mMapGrid.SetJPForbid(x, y);
	mMapAoi.AddJumpPointEffect(info);
	mMapAoi.SendEffectAppearNtf(x, y, data);
}

void Map::DelJumpPoint(const std::string& guid, uint16_t x, uint16_t y)
{
	auto key = x << 16 | y;
	auto iter = mDynJumpPointList.find(key);
	if (iter != mDynJumpPointList.end())
	{
		auto to_map = MapMgr::GetInstance()->FindMap(iter->second.to_map);
		if (to_map) {
			to_map->DelJumpPoint(iter->second.to_left, iter->second.to_top);
		}

		auto from_map = MapMgr::GetInstance()->FindMapByGUID(std::stoull(guid));
		if (from_map) {
			from_map->DelJumpPoint(iter->second.from_left, iter->second.from_top);
		}

		mDynJumpPointList.erase(iter);
	}

}

void Map::DelJumpPoint(uint16_t x, uint16_t y)
{
	ProtoMS_EffectDisAppearNtf data;
	EffectPoint info;
	info.x = x;
	info.y = y;
	data.info[data.num++] = info;
	data.type = effect_point_type_jump;
	mMapGrid.RemoveJPForbid(x, y);
	mMapAoi.DelJumpPointEffect(info);
	mMapAoi.SendEffectDisAppearNtf(x, y, data);
}

std::list<Role *> Map::GetAllRoleByType(uint8_t roleType)
{
	return mMapAoi.GetAllRoleByType(roleType);
}

void Map::SendBlankGridTableToLua(uint16_t x, uint16_t y, uint16_t rangeX, uint16_t rangeY, uint16_t type)
{
	std::vector<std::pair<uint16_t, uint16_t>> blankSpaceTable;
	GetAllBlankPointInRange(x, y, rangeX, rangeY, blankSpaceTable);
	switch (type)
	{
	case blank_grid_normal:
		{
		for (auto iter = blankSpaceTable.begin(); iter != blankSpaceTable.end();)
		{
			if (IsTypeRegion(iter->first, iter->second, region_safe) || IsTypeRegion(iter->first, iter->second, region_stall))
			{
				iter = blankSpaceTable.erase(iter);
				continue;
			}
			++iter;
		}
			break;
		}
	case blank_grid_drop:
		{
		for (auto iter = blankSpaceTable.begin(); iter != blankSpaceTable.end();)
		{
			if (IsTypeRegion(iter->first, iter->second, region_safe) || IsTypeRegion(iter->first, iter->second, region_stall)
				|| mMapAoi.GetSceneItem(iter->first, iter->second))
			{
				iter = blankSpaceTable.erase(iter);
				continue;
			}
			++iter;
		}
			break;
		}
	default:
		break;
	}


	std::sort(blankSpaceTable.begin(), blankSpaceTable.end(), 
		[&x,&y](std::pair<uint16_t, uint16_t>& first, std::pair<uint16_t, uint16_t>& second) {
			auto disf = Utility::CalcLongerDistance(first.first, first.second, x, y);
			auto disb = Utility::CalcLongerDistance(second.first, second.second, x, y);
			if (disb > disf)return true;
			return false;
		});
	CLuaObject luaRet = NewLuaObj();
	for (auto i = 1; i <= blankSpaceTable.size(); ++i)
	{
		CLuaObject point = NewLuaObj();
		point[1] = blankSpaceTable[i - 1].first;
		point[2] = blankSpaceTable[i - 1].second;
		luaRet[i] = point;
	}
	LuaRet = luaRet;
}

bool Map::IsTypeRegion(uint16_t  posx, uint16_t posy, int type)
{
	std::vector<DATA::RegionCommon>vec;
	GetTypeRegion(type,vec);
	if (vec.empty())return false;
	for (auto& i : vec)
	{
		//标准矩形
		if (i.width && i.height)
		{
			if ((posx >= i.left && posy >= i.top) && posx <= (i.left + i.width) && posy <= (i.top + i.height)) return true;
		}
		else//旋转矩形
		{
			auto IsInRhombus = [=](uint16_t posx, uint16_t posy, uint16_t left, uint16_t top, uint16_t left2, uint16_t top2) {
				int _Size = abs(top2 - top);  //_Size为菱形宽高
				//首先将坐标系移动到菱形中心，则测试点会相应移动
				int X = posx - left;
				int Y = posy - (min(top, top2) + _Size / 2);
				if (abs(X) + abs(Y) <= _Size / 2)
					return true;
				return false;
			};

			return IsInRhombus(posx, posy, i.left, i.top, i.left2, i.top2);
		}
	}
	return false;
}
void Map::GetTypeRegion(int type, std::vector<DATA::RegionCommon>& vec)
{
	DATA::RegionCommon region;
	switch (type)
	{
	case region_safe:
	{
		auto &saferegion = sSafeRegionConfig.GetNameMaping();
		if (saferegion.empty()) return;
		for (auto& i : saferegion)
		{
			if (i.second->m_Region.KeyName != GetName())continue;
			vec.push_back(i.second->m_Region);
		}
		break;
	}
	case region_stall:
	{
		auto& stallregion = sStallRegionConfig.GetNameMaping();
		if (stallregion.empty()) return;
		for (auto& i : stallregion)
		{
			if (i.second->m_Region.KeyName != GetName())continue;
			vec.push_back(i.second->m_Region);
		}
		break;
	}
	case region_athletics:
	{
		//没表
		//auto* athleticsregion = sAthleticsRegionConfig.Get(mMapName);
		//if (nullptr == athleticsregion) return;
		//region = athleticsregion->m_Region;
		//break;
		return;
	}
	case region_relive:
	{
		auto& reliveregion = sReliveRegionConfig.GetNameMaping();
		if (reliveregion.empty()) return;
		for (auto& i : reliveregion)
		{
			if (i.second->m_Region.KeyName != GetName())continue;
			vec.push_back(i.second->m_Region);
		}
		break;
	}
	case region_red_name:
	{
		auto& rednameregion = sRedNameRegionConfig.GetNameMaping();
		if (rednameregion.empty()) return;
		for (auto& i : rednameregion)
		{
			if (i.second->m_Region.KeyName != GetName())continue;
			vec.push_back(i.second->m_Region);
		}
		break;
	}
	case region_born:
	{
		auto& bornregion = sBornRegionConfig.GetNameMaping();
		if (bornregion.empty()) return;
		for (auto& i : bornregion)
		{
			if (i.second->m_Region.KeyName != GetName())continue;
			vec.push_back(i.second->m_Region);
		}
		break;
	}
	case region_jump:
		return;
	case region_mine:
		return;
	case region_through:
		return;
	default:
		return;
	}
}

Role* Map::GetNearstRoleByType(uint16_t posX, uint16_t posY, bool canGetStealth, uint8_t roleType, Role* origRole)
{
	return mMapAoi.GetNearstRoleByType(posX, posY, canGetStealth, roleType, origRole);
}

Role* Map::GetNeatstRoleByCustType(uint16_t posX, uint16_t posY, uint8_t roleType, Role* origRole)
{
	return mMapAoi.GetNearstRoleByCustType(posX, posY, roleType, origRole);
}

Role* Map::GetNearestRoleByName(uint16_t posX, uint16_t posY, uint8_t roleType, const char* name, Role* origRole)
{
	std::vector<Role*>vec;
	GetAllRoleByTypeByName(vec, roleType, name);
	if (vec.empty())return nullptr;
	Role* role = vec[0];
	auto dis = role->DistanceFromPos(posX, posY);
	for (int i = 1; i < vec.size(); ++i)
	{
		auto curdis = vec[i]->DistanceFromPos(posX, posY);
		if (curdis < dis)
		{
			role = vec[i];
			dis = curdis;
		}
	}
	return role;
}

void Map::GetAllRoleByTypeByName(std::vector<Role*> &vec, uint8_t roleType, const char* name)
{
	mMapAoi.GetAllRoleByTypeByName(vec, roleType, name);
}

void Map::SendRoleDirChangeNtf(Role* role, ProtoGS_TurnNtf& ntf)
{
	mMapAoi.SendRoleDirChangeNtf(role, ntf);
}

void Map::SendRoleDieNtf(Role* role, ProtoMS_ObjDieNtf& ntf)
{
	mMapAoi.SendRoleDieNtf(role, ntf);
}

void Map::NotifyRoleAppearNtfChange(Role* role) 
{
	mMapAoi.NotifyRoleOnlyUpdateAppearNtf(role);
}

#pragma region 场景物品相关
bool Map::GetBlankSceneItemPos(uint16_t srcX, uint16_t srcY, uint16_t& dstX, uint16_t& dstY)
{
	uint16_t lenX = 1;
	uint16_t lenY = 1;
	uint16_t maxLenX = mMapAoi.GetRegionWidth() * AOI_LEN;
	uint16_t maxLenY = mMapAoi.GetRegionHeight() * AOI_LEN;
	while (true) {
		for (uint16_t j = srcY - lenY; j <= srcY + lenY; ++j) {
			for (uint16_t i = srcX - lenX; i <= srcX + lenX; ++i) {
				if (i > (srcX - lenX) && i < (srcX + lenX) && j >(srcY - lenY) && j < (srcY + lenY)) {
					continue;
				}

				if (mMapGrid.IsForbid(i, j)) {
					continue;
				}

				if (mMapGrid.IsJPForbid(i, j)) {
					continue;
				}

				if (mMapAoi.IsHaveRoleInPoint(i, j)) {
					continue;
				}

				if (nullptr != mMapAoi.GetSceneItem(i, j)) {
					continue;
				}

				dstX = i;
				dstY = j;
				return true;
			}
		}

		++lenX;
		++lenY;
		lenX = std::min<uint16_t>(lenX, maxLenX);
		lenY = std::min<uint16_t>(lenY, maxLenY);

		if (lenX >= maxLenX && lenY >= maxLenY) {
			break;
		}
	}

	return false;
}

const std::string & Map::GenSceneItem(uint16_t x, uint16_t y, uint16_t id, uint16_t amount, uint16_t bind, const std::string& ownerGuid)
{
	auto sceneItem = AddSceneItem(x, y, id, amount, bind);
	if (nullptr != sceneItem) {
		if (ownerGuid == "0")
		{
			// 1 标记为归属于系统
			sceneItem->SetOwnerGUID(1);// 需要等SceneItemSurvivalTime
		}
		else if (ownerGuid == "1")
		{
			sceneItem->SetOwnerGUID(0);	// 归属于系统但不需要等
		}
		else
		{
			sceneItem->SetOwnerGUID(std::stoull(ownerGuid));
		}
		return sceneItem->GetGUIDAsString();
	}
	return EMPTYSTR;
}

const std::string & Map::GenSceneItemByName(uint16_t x, uint16_t y, const std::string &name, uint16_t amount, uint16_t bind, const std::string& ownerGuid)
{
    auto *cfg = sItemConfig.Get(name);
    if (!cfg) return EMPTYSTR;

    return GenSceneItem(x, y, cfg->Id, amount, bind ,ownerGuid);
}

SceneItem* Map::AddSceneItem(uint16_t x, uint16_t y, uint16_t id, uint16_t amount, uint16_t bind,
    uint16_t drop, uint64_t ownerGUID, uint64_t teamGUID)
{
	if (mMapGrid.IsForbid(x, y)) {
		return nullptr;
	}
	auto sceneItem = mMapAoi.AddSceneItem(id, x, y, amount, bind, drop, ownerGUID, teamGUID);
	return sceneItem;
}

SceneItem* Map::AddSceneItem(uint16_t x, uint16_t y, RoleItem* roleItem)
{
	if (mMapGrid.IsForbid(x, y)) {
		return nullptr;
	}

	auto sceneItem = mMapAoi.AddSceneItem(x, y, roleItem);
	return sceneItem;
}

bool Map::DestroySceneItem(uint16_t x, uint16_t y)
{
	return mMapAoi.DestroySceneItem(x, y);
}

bool Map::DestroySceneItem(uint64_t itemGUID, uint16_t x, uint16_t y)
{
	return mMapAoi.DestroySceneItem(itemGUID,x,y);
}

SceneItem* Map::GetSceneItem(uint16_t x, uint16_t y)
{
	return mMapAoi.GetSceneItem(x, y);
}

SceneItem* Map::GetSceneItem(uint64_t itemGUID)
{
	return mMapAoi.GetSceneItem(itemGUID);
}

bool Map::OnRoleDropItem(Role* role, RoleItem* item)
{
	if (nullptr == role || nullptr == item) {
		return false;
	}

	uint16_t posX, posY;
	if (!GetBlankSceneItemPos(role->GetRolePosX(), role->GetRolePosY(), posX, posY)) {
		return false;
	}

	auto sceneItem = AddSceneItem(posX, posY, item);
	if (nullptr == sceneItem) {
		return false;
	}

    sceneItem->SetDropBy(role->GetGUID());

	return true;
}

void Map::OnItemAppear(SceneItem *item)
{
    mMapAoi.OnItemAppear(item);
}

void Map::OnItemDisappear(SceneItem *item)
{
    mMapAoi.OnItemDisappear(item);
}

void Map::SendRoleItemAppearNtf(ProtoMS_ItemAppearNtf4& ntf)
{
	mMapAoi.SendRoleItemAppearNtf(ntf);
}

SceneItem* Map::GetPetPickableItem(Monster *pet)
{
    return mMapAoi.GetPetPickableItem(pet);
}

bool Map::SupportAutoPickItem()
{
	auto *cfg = GetMapConfig();
	if (!cfg) return false;
	return cfg->AutoPickItem;
}

#pragma endregion

void Map::SendRoleObjDisappearNtf(uint16_t posX, uint16_t posY, ProtoMS_ObjDisappearNtf& ntf)
{
	mMapAoi.SendRoleObjDisappearNtf(posX, posY, ntf);
}

void Map::SendPlayerChangeNameNtf(Role* role, ProtoGS_PlayerSetNameNtf& ntf)
{
	mMapAoi.SendRoleNameChangeNtf(role, ntf);
}

void Map::SendMasterChangeNameNtf(Role* role, ProtoGS_PlayerSetNameNtf& ntf)
{
	mMapAoi.SendRoleNameChangeNtf(role, ntf);
}

void Map::SendPlayerWearTitleNtf(Role* role, ProtoGS_TitleWearNtf& ntf)
{
	mMapAoi.SendRoleWearTitleNtf(role, ntf);
}

void Map::SendPlayerUnWearTitleNtf(Role* role, ProtoGS_TitleUnWearNtf& ntf)
{
	mMapAoi.SendRoleUnWearTitleNtf(role, ntf);
}

uint32_t Map::AddLuaTimer(unsigned int interval, bool loop, const std::string& call_back)
{
    auto id = ITimeHelper::GetInstance()->AddTimer(interval, loop, [=](const TimerData &timer) {
        if (!call_back.empty()) {
            LuaBindCallVoid(call_back, timer.id);
        }
		if (!loop)
		{
			mTimerId.erase(timer.id);
		}
    });

	mTimerId.insert(id);
	return id;
}

uint32_t Map::AddLuaTimerEx(unsigned int interval, bool loop, CLuaObject call_back)
{
    auto id = ITimeHelper::GetInstance()->AddTimer(interval, loop, [=](const TimerData &timer) {
        if (call_back.is_valid()) {
            LuaBindCallExVoid(call_back, timer.id);
        }
		if (!loop)
		{
			mTimerId.erase(timer.id);
		}
    });

	mTimerId.insert(id);
	return id;
}

void Map::RemoveLuaTimer(uint32_t id)
{
	ITimeHelper::GetInstance()->RemoveTimer(id);
	mTimerId.erase(id);
}

void Map::RemoveAllTrapTimer()
{
	for (auto i : mMapTimerId) {
		ITimeHelper::GetInstance()->RemoveTimer(i);
	}
}

void Map::InitJumpPointForbit(DATA::Map* mapConfig)
{
	if (nullptr == mapConfig)return;
	auto &jumpData = sJumpConfig.GetData();
	for (auto i : jumpData) {
		if (nullptr == i)continue;

		if (strcmp(i->from_map, mapConfig->KeyName) == 0) {
			for (int x = i->from_left; x <= (i->from_left + i->from_width); ++x) {
				for (int y = i->from_top; y <= (i->from_top + i->from_height); ++y) {
					GetMapGrid().SetJPForbid(x, y);
				}
			}
		}

		if (strcmp(i->to_map, mapConfig->KeyName) == 0) {
			for (int x = i->to_left; x <= (i->to_left + i->to_width); ++x) {
				for (int y = i->to_top; y <= (i->to_top + i->to_height); ++y) {
					GetMapGrid().SetJPForbid(x, y);
				}
			}
		}
	}
}

void Map::SendSysMsg(uint8_t nMsgType, const std::string& sMsg)
{
	ProtoMS_SysMsgNtf sysMsgNtf;
	sysMsgNtf.msg_type = nMsgType;
	strcpy_s(sysMsgNtf.msg, _countof(sysMsgNtf.msg), sMsg.c_str());

	auto applyFunc = [&](Role* pRole) {
		if (!pRole->IsPlayer()) return;

		auto pPlayer = static_cast<Player*>(pRole);

		sysMsgNtf.clientSessionID = pPlayer->GetClSessionID();

		SendDataBySessionID(pPlayer->GetGsSessionID(), sysMsgNtf);
	};

	ApplyFuncToAllRoles(applyFunc);
}

void Map::SendSysMsgNtf2AllRole(MESSAGE_INFO& info)
{
	MSG_BUFFER_DATA(ProtoGS_SysMsgNtf2, data);
	Player::GenerateSysMsgInfo(info, data.info);
	auto applyFunc = [&](Role* pRole) {
		if (!pRole->IsPlayer()) return;
		auto pPlayer = static_cast<Player*>(pRole);
		data.sessid = pPlayer->GetClSessionID();
		SendDataBySessionID(pPlayer->GetGsSessionID(), data);
	};
	ApplyFuncToAllRoles(applyFunc);
}

void Map::SendSysMsgNtf2AllRoleInAroundRegion(MESSAGE_INFO& info)
{
	MSG_BUFFER_DATA(ProtoGS_SysMsgNtf2, data);
	Player::GenerateSysMsgInfo(info, data.info);
	auto applyFunc = [&](Role* pRole) {
		if (!pRole->IsPlayer()) return;
		auto pPlayer = static_cast<Player*>(pRole);
		data.sessid = pPlayer->GetClSessionID();
		SendDataBySessionID(pPlayer->GetGsSessionID(), data);
	};

	ApplyFuncToAllPlayersInAroundRegions(info.posx,info.posy,applyFunc);
}

void Map::SendSceneDialogNtfAllRole(MESSAGE_INFO& info)
{
	MSG_BUFFER_DATA(ProtoGS_SceneDialogNtf, data);
	Player::GenerateSenceDialogInfo(info, data.info);
	auto applyFunc = [&](Role* pRole) {
		if (!pRole->IsPlayer()) return;

		auto pPlayer = static_cast<Player*>(pRole);

		data.sessid = pPlayer->GetClSessionID();

		SendDataBySessionID(pPlayer->GetGsSessionID(), data);
	};
	ApplyFuncToAllRoles(applyFunc);
}

void Map::SendSceneDialogNtfAllRoleInAroundRegion(MESSAGE_INFO& info)
{
	MSG_BUFFER_DATA(ProtoGS_SceneDialogNtf, data);
	Player::GenerateSenceDialogInfo(info, data.info);
	auto applyFunc = [&](Role* pRole) {
		if (!pRole->IsPlayer()) return;

		auto pPlayer = static_cast<Player*>(pRole);

		data.sessid = pPlayer->GetClSessionID();

		SendDataBySessionID(pPlayer->GetGsSessionID(), data);
	};
	ApplyFuncToAllPlayersInAroundRegions(info.posx, info.posy, applyFunc);
}

void Map::SendScrollTextAllRole(MESSAGE_INFO& info)
{
	MSG_BUFFER_DATA(ProtoGS_ScrollText, data);
	Player::GenerateScrollTextInfo(info, data.info);
	auto applyFunc = [&](Role* pRole) {
		if (!pRole->IsPlayer()) return;

		auto pPlayer = static_cast<Player*>(pRole);

		data.sessid = pPlayer->GetClSessionID();

		SendDataBySessionID(pPlayer->GetGsSessionID(), data);
	};
	ApplyFuncToAllRoles(applyFunc);
}

void Map::SendScrollTextAllRoleInAroundRegion(MESSAGE_INFO& info)
{
	MSG_BUFFER_DATA(ProtoGS_ScrollText, data);
	Player::GenerateScrollTextInfo(info, data.info);
	auto applyFunc = [&](Role* pRole) {
		if (!pRole->IsPlayer()) return;

		auto pPlayer = static_cast<Player*>(pRole);

		data.sessid = pPlayer->GetClSessionID();

		SendDataBySessionID(pPlayer->GetGsSessionID(), data);
	};
	ApplyFuncToAllPlayersInAroundRegions(info.posx, info.posy, applyFunc);

}

//计算跳转点坐标
//优先传入的坐标。不满足时以传入的坐标为中心一圈一圈的向外找。找不到时仍然使用传入坐标
bool Map::FindJumpablePos(uint16_t& posX, uint16_t& posY)
{
	if ((posX || posY) && !mMapGrid.IsForbid(posX, posY)) return true;

	const uint16_t MAX_LEN = 10;

	uint16_t lenX = 1;
	uint16_t lenY = 1;
	while (true) {
		std::vector<std::pair<uint16_t, uint16_t>> posVec;
		for (uint16_t j = posY - lenY; j <= posY + lenY; ++j) {
			for (uint16_t i = posX - lenX; i <= posX + lenX; ++i) {
				if (i > (posX - lenX) && i < (posX + lenX) && j >(posY - lenY) && j < (posY + lenY)) continue;
				if (mMapGrid.IsForbid(i, j)) continue;
				posVec.emplace_back(i, j);
			}
		}

		if (!posVec.empty())
		{
			auto& pos = posVec[Tools::GenerateRandomInteger<uint16_t>(0, posVec.size() - 1)];
			posX = pos.first;
			posY = pos.second;
			return true;
		}
		++lenX;
		++lenY;
		lenX = std::min<uint16_t>(lenX, MAX_LEN);
		lenY = std::min<uint16_t>(lenY, MAX_LEN);

		if (lenX >= MAX_LEN && lenY >= MAX_LEN) break;
	}
    return false;
}

bool Map::AddMonitorRegionForTrapSkill(uint16_t skillID, uint32_t expireTime, uint64_t actorGUID, PositionList posList)
{
    auto *cfg = sSkillConfig.Get(skillID);
    if (!cfg) return false;

    if (expireTime == 0) return false;

    auto *actor = MapRoleMgr::GetInstance()->FindRole(actorGUID);
    if (!actor) return false;

    EraseTrapSkillOverlappedRegion(skillID, posList);

    if (posList.empty()) return true;

    TrapSkillMonitorRegionInfo info;
    info.skillID = skillID;
    info.actorGUID = actorGUID;
    info.expireTime = expireTime;
    info.posList = std::move(posList);

    FillTrapSkillRoleInfoList(info);
    TrapSkillInitHurt(info);

    mTrapSkillMonitorRegionInfoList.emplace_back(std::move(info));

    return true;
}

void Map::RemoveMonitorRegionForTrapSkill(uint64_t actorGUID)
{
    for (auto &regionInfo : mTrapSkillMonitorRegionInfoList) {

        if (regionInfo.actorGUID == actorGUID) {

            for (auto i : regionInfo.posList)
                RemovePosInTrap(i.first, i.second);

            regionInfo.valid = false;
        }
    }
}

void Map::AddTrapEffect(uint16_t skillID, uint16_t x, uint16_t y, uint32_t effect, uint32_t lifetime)
{
	TrapPointEffect data;
	data.SkillID = skillID;
	data.data.x = x;
	data.data.y = y;
	data.data.effect = effect;
	mMapAoi.AddTrapPointEffect(data, lifetime);
}

void Map::EraseTrapSkillOverlappedRegion(uint16_t skillID, PositionList &newPosList)
{
    auto *cfg = sSkillConfig.Get(skillID);
    if (!cfg) return;

    if (cfg->SpecialEffectType != skill_special_trap_trigger) return;

    for (const auto &regionInfo : mTrapSkillMonitorRegionInfoList) {

        if (!regionInfo.valid) continue;
        if (regionInfo.skillID != skillID) continue;

        for (const auto &pos : regionInfo.posList) {

            auto it = std::find(newPosList.begin(), newPosList.end(), pos);

            if (it != newPosList.end()) newPosList.erase(it);

            if (newPosList.empty()) return;
        }
    }
}

void Map::FillTrapSkillRoleInfoList(TrapSkillMonitorRegionInfo &regionInfo)
{
	auto actor = MapRoleMgr::GetInstance()->FindRole(regionInfo.actorGUID);
    for (const auto &pos : regionInfo.posList) {

        const auto &x = pos.first;
        const auto &y = pos.second;

        auto *role = GetRoleInPoint(x, y);
        if (!role) continue;
		if (role->IsMonster() && static_cast<Monster*>(role)->IsTreasureMonster())continue;
		/*if (actor && actor->GetRoleAttr()->GetRoleProp(role_camp) &&
			actor->GetRoleAttr()->GetRoleProp(role_camp) == role->GetRoleAttr()->GetRoleProp(role_camp))continue;*/
        auto roleGUID = role->GetGUID();
        if (roleGUID == regionInfo.actorGUID) continue;

		AddPosToTrap(x, y);
        regionInfo.roleInfoList.emplace_back(roleGUID, x, y);
    }
}

void Map::TrapSkillInitHurt(TrapSkillMonitorRegionInfo &regionInfo)
{
    auto *cfg = sSkillConfig.Get(regionInfo.skillID);
    if (!cfg) return;

    if (cfg->SpecialEffectType != skill_special_trap_rt) return;

    for (const auto &roleInfo : regionInfo.roleInfoList) {

        TrapSkillHurtRole(regionInfo.skillID, regionInfo.actorGUID, roleInfo.roleGUID);
    }
}

void Map::TrapSkillHurtRole(uint16_t skillID, uint64_t actorGUID, uint64_t roleGUID, uint32_t round)
{
    auto *role = MapRoleMgr::GetInstance()->FindRole(roleGUID);
    if (!role) return;

    auto *actor = MapRoleMgr::GetInstance()->FindRole(actorGUID);
    if (!actor) return;

    auto *roleSkill = actor->GetRoleSkill();
    if (!roleSkill) return;

    if (!roleSkill->CanApplySkillOnTarget(skillID, role)) return;

	AttackResult res;
	res.actorGUID = actor->GetGUID();
	res.actorName = actor->GetName();
	res.targetGUID = roleGUID;
	res.skillId = skillID;
	RoleSkill::CalculateHarmData(res, round);
	if (res.type > 0 && res.decreaseHP > 0)
	{
		auto roledskill = actor->GetRoleSkill();
		if (roledskill) {
			roledskill->AddGrayBuff(res.targetGUID);
		}
	}
    role->AttackedByRole(res);
}

void Map::UpdateTrapSkillRegionState(int delta)
{
    if (mTrapSkillMonitorRegionInfoList.empty()) return;

    for (auto regionInfo = mTrapSkillMonitorRegionInfoList.begin(); regionInfo != mTrapSkillMonitorRegionInfoList.end(); ) {

        if (!regionInfo->valid) {
			for (auto i : regionInfo->posList)
				RemovePosInTrap(i.first, i.second);
            regionInfo = mTrapSkillMonitorRegionInfoList.erase(regionInfo);
            continue;
        }

        const auto *cfg = sSkillConfig.Get(regionInfo->skillID);
        if (!cfg) {
            ++regionInfo;
            continue;
        }

        uint16_t interval = 0;
        if (cfg->SpecialEffectType == skill_special_trap_trigger) {
            interval = cfg->SpecialEffectParam[0];
        }
        else if (cfg->SpecialEffectType == skill_special_trap_rt) {
            interval = cfg->SpecialEffectParam[1];
        }
        else {
            ++regionInfo;
            continue;
        }

        for (auto &roleInfo : regionInfo->roleInfoList) {

            roleInfo.stillTime += delta;

            if (roleInfo.stillTime >= interval) {
				roleInfo.nround++;
                TrapSkillHurtRole(regionInfo->skillID, regionInfo->actorGUID, roleInfo.roleGUID, roleInfo.nround);

                roleInfo.stillTime = 0;
            }
        }

        regionInfo->elapsedTime += delta;

        if (regionInfo->elapsedTime >= regionInfo->expireTime) {
			for (auto i : regionInfo->posList)
				RemovePosInTrap(i.first, i.second);
            regionInfo = mTrapSkillMonitorRegionInfoList.erase(regionInfo);
            continue;
        }

        ++regionInfo;
    }
}

void Map::OnEndMove(Role *role)
{
    UpdateTrapSkillRegionRoleInfo(role);
}

void Map::UpdateTrapSkillRegionRoleInfo(Role *role)
{
    if (!role) return;

    auto roleGUID = role->GetGUID();
    auto x = role->GetRolePosX();
    auto y = role->GetRolePosY();

    auto fromRegions = FindTrapSkillMonitorRegion(roleGUID);

    auto toRegions = FindTrapSkillMonitorRegion(x, y);

    for (auto itFrom = fromRegions.begin(); itFrom != fromRegions.end(); ) {

        auto *fromRegion = *itFrom;

        auto itTo = std::find(toRegions.begin(), toRegions.end(), fromRegion);

        if (itTo == toRegions.end()) {
            ++itFrom;
            continue;
        }

        // 同一区域移动

        itFrom = fromRegions.erase(itFrom);
        toRegions.erase(itTo);

        auto *roleInfo = GetTrapSkillRoleInfo(fromRegion->roleInfoList, roleGUID);
        if (!roleInfo) continue;

        if (roleInfo->x == x && roleInfo->y == y) continue;

        auto *cfg = sSkillConfig.Get(fromRegion->skillID);
        if (!cfg) continue;

        if (cfg->SpecialEffectType == skill_special_trap_trigger) {

            TrapSkillHurtRole(fromRegion->skillID, fromRegion->actorGUID, roleGUID);
            roleInfo->stillTime = 0;
        }

        roleInfo->x = x;
        roleInfo->y = y;
    }

    for (auto &fromRegion : fromRegions) {      // 离开区域
        EraseTrapSkillRoleInfo(fromRegion->roleInfoList, roleGUID);
    }

    for (auto &toRegion : toRegions) {          // 进入区域

        if (roleGUID == toRegion->actorGUID) continue;

        TrapSkillHurtRole(toRegion->skillID, toRegion->actorGUID, roleGUID);
        AddTrapSkillRoleInfo(toRegion->roleInfoList, roleGUID, x, y);
    }
}

TrapSkillMonitorRegionInfoPtrList Map::FindTrapSkillMonitorRegion(uint64_t roleGUID)
{
    TrapSkillMonitorRegionInfoPtrList plist;

    for (auto &regionInfo : mTrapSkillMonitorRegionInfoList) {

        if (!regionInfo.valid) continue;

        for (auto &roleInfo : regionInfo.roleInfoList) {

            if (roleInfo.roleGUID == roleGUID)
                plist.emplace_back(&regionInfo);
        }
    }

    return plist;
}

TrapSkillMonitorRegionInfoPtrList Map::FindTrapSkillMonitorRegion(uint16_t x, uint16_t y)
{
    TrapSkillMonitorRegionInfoPtrList plist;

    for (auto &regionInfo : mTrapSkillMonitorRegionInfoList) {

        if (!regionInfo.valid) continue;

        for (auto &pos : regionInfo.posList) {

            if (pos.first == x && pos.second == y)
                plist.emplace_back(&regionInfo);
        }
    }

    return plist;
}

void Map::AddTrapSkillRoleInfo(TrapSkillRoleInfoList &roleInfoList, uint64_t roleGUID, uint16_t x, uint16_t y)
{
    roleInfoList.emplace_back(roleGUID, x, y);
}

void Map::UpdateTrapSkillRoleInfo(TrapSkillRoleInfoList &roleInfoList, uint64_t roleGUID, uint16_t x, uint16_t y)
{
    auto it = std::find_if(roleInfoList.begin(), roleInfoList.end(), [&](const auto &roleInfo){
        return (roleInfo.roleGUID == roleGUID);
    });

    if (it == roleInfoList.end()) return;

    it->x = x;
    it->y = y;
    it->stillTime = 0;
}

void Map::EraseTrapSkillRoleInfo(TrapSkillRoleInfoList &roleInfoList, uint64_t roleGUID)
{
    auto it = std::find_if(roleInfoList.begin(), roleInfoList.end(), [&](const auto &roleInfo){
        return (roleInfo.roleGUID == roleGUID);
    });

    if (it == roleInfoList.end()) return;

    roleInfoList.erase(it);
}

TrapSkillRoleInfo * Map::GetTrapSkillRoleInfo(TrapSkillRoleInfoList &roleInfoList, uint64_t roleGUID)
{
    for (auto &roleInfo : roleInfoList) {
        if (roleInfo.roleGUID == roleGUID) return &roleInfo;
    }

    return nullptr;
}

bool Map::CheckCross(uint32_t roleType)
{
	auto it = CheckCrossMap.find(roleType);
	if (it != CheckCrossMap.end()) return it->second;

    const auto *cfg = GetMapConfig();
	if (!cfg) {
		CheckCrossMap[roleType] = false;
		return false;
	}
		

	if (cfg->CrossHuman == 1 && (roleType == role_type_player || roleType == role_type_player_doplganr)) {
		CheckCrossMap[roleType] = true;
		return true;
	}
	if (cfg->CrossMonster == 1 && (roleType == role_type_monster || roleType == role_type_pet)) {
		CheckCrossMap[roleType] = false;
		return false;
	}
	CheckCrossMap[roleType] = false;
	return false;
}

std::pair<uint16_t, uint16_t> Map::GetMForbidPoint(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    auto &mapGrid = GetMapGrid();

    if (x0 == x1) {

        if (y0 < y1) {

            for (uint16_t y = y0 + 1; y < y1; ++y)
                if (mapGrid.IsMForbid(x0, y))
                    return {x0, y};
        }
        else {

            for (uint16_t y = y0 - 1; y > y1; --y)
                if (mapGrid.IsMForbid(x0, y))
                    return {x0, y};
        }
    }
    else {

        double tan0 = double(y1 - y0) / (x1 - x0);

        if (abs(tan0) < 1) {

            if (x0 < x1) {

                for (uint16_t x = x0 + 1; x < x1; ++x) {

                    uint16_t y = uint16_t(y0 + (x - x0) * tan0 + 0.5);

                    if (mapGrid.IsMForbid(x, y)) return {x, y};
                }
            }
            else {

                for (uint16_t x = x0 - 1; x > x1; --x) {

                    uint16_t y = uint16_t(y0 + (x - x0) * tan0 + 0.5);

                    if (mapGrid.IsMForbid(x, y)) return {x, y};
                }
            }
        }
        else {

            if (y0 < y1) {

                for (uint16_t y = y0 + 1; y < y1; ++y) {

                    uint16_t x = uint16_t(x0 + (y - y0) / tan0 + 0.5);

                    if (mapGrid.IsMForbid(x, y)) return {x, y};
                }
            }
            else {

                for (uint16_t y = y0 - 1; y > y1; --y) {

                    uint16_t x = uint16_t(x0 + (y - y0) / tan0 + 0.5);

                    if (mapGrid.IsMForbid(x, y)) return {x, y};
                }
            }
        }
    }

    return {0, 0};
}

std::map<uint32_t, std::vector<uint32_t>> Map::GetAroundPlayerCLSessionID(Role *role, bool includingSelf)
{
    std::map<uint32_t, std::vector<uint32_t>> clsessidsMap;
    if (!role) return clsessidsMap;

    auto f = [&](Role *role2) {
        if (!role2 || !role2->IsPlayer()) return;
        if (!includingSelf && role2 == role) return;
        auto *player = static_cast<Player *>(role2);
        if (!player->IsOnline()) return;
        clsessidsMap[player->GetGsSessionID()].push_back(player->GetClSessionID());
    };

    auto x = role->GetRolePosX();
    auto y = role->GetRolePosY();
	ApplyFuncToAllPlayersInAroundRegions(x, y, f);
    return clsessidsMap;
}

std::map<uint32_t, std::vector<uint32_t>> Map::GetAllPlayerCLSessionID()
{
	std::map<uint32_t, std::vector<uint32_t>> clsessidsMap;
	auto f = [&](Role* role2) {
		if (!role2 || !role2->IsPlayer()) return;
		auto* player = static_cast<Player*>(role2);
		if (!player->IsOnline()) return;
		clsessidsMap[player->GetGsSessionID()].push_back(player->GetClSessionID());
	};

	ApplyFuncToAllRoles(f, role_type_player);
	return clsessidsMap;
}


uint32_t Map::AddFuncToMap(FuncMap &funcMap, Func func)
{
    auto funcID = Tools::GenerateUINT32();
    funcMap.emplace(funcID, std::move(func));
    return funcID;
}

void Map::RemoveFuncFromMap(FuncMap &funcMap, uint32_t funcID)
{
    auto it = funcMap.find(funcID);
    if (it == funcMap.end()) return;
    it->second = nullptr;   // 不能直接删除，假如在回调中调用会导致迭代器失效
}

void Map::ApplyFuncInMap(FuncMap &funcMap, Role *role)
{
    SAFE_BEGIN;

    for (auto it = funcMap.begin(); it != funcMap.end(); ) {
        if (it->second) {
            it->second(role);
            ++it;
        }
        else {
            it = funcMap.erase(it);
        }
    }

    SAFE_END;
}

uint32_t Map::AddOnRoleEnterFunc(Func func)
{
    return AddFuncToMap(mOnRoleEnterFunc, std::move(func));
}

uint32_t Map::AddOnRoleLeaveFunc(Func func)
{
    return AddFuncToMap(mOnRoleLeaveFunc, std::move(func));
}

void Map::RemoveOnRoleEnterFunc(uint32_t funcID)
{
    RemoveFuncFromMap(mOnRoleEnterFunc, funcID);
}

void Map::RemoveOnRoleLeaveFunc(uint32_t funcID)
{
    RemoveFuncFromMap(mOnRoleLeaveFunc, funcID);
}

void Map::ApplyOnRoleEnterFunc(Role *role)
{
    ApplyFuncInMap(mOnRoleEnterFunc, role);
}

void Map::ApplyOnRoleLeaveFunc(Role *role)
{
    ApplyFuncInMap(mOnRoleLeaveFunc, role);
}


void Map::RunClientScript(const char* pScriptName, const char* pContent, bool bCompress)
{
	if (!pScriptName || !pContent) return;

	MSG_BUFFER_DATA(ProtoMS_RunClientScript, req);
	//req.clientSessionID = mClSessionID;
	strcpy_s(req.form_name, pScriptName);
	req.comp = bCompress;

	if (bCompress) {
		uLongf nDstLen = sizeof(req.form_content);
		auto result = compress((Bytef*)req.form_content, &nDstLen, (const Bytef*)pContent, strlen(pContent));
		if (result != Z_OK) {
			LOG_ERROR("compress failed with error %d", result);
			return;
		}
		req.size = nDstLen;
	}
	else {
		strcpy_s(req.form_content, pContent);
		req.size = (uint16_t)strlen(pContent);
	}
	auto clsessidsMap = GetAllPlayerCLSessionID();
	SendDataBySessionID(clsessidsMap, req);
}


void DgnMap::ResetDgnData()
{
	ownerGuid = 0;
	mDestoryTime = 0;
	mDestoryTimerId = 0;
	mDelayInit = false;
	playerGuidSet.clear();
	bindGuidSet.clear();
}

void DgnMap::Prepare(uint64_t oGuid, uint32_t dTime, CLuaObject call_back, bool delay)
{
	ownerGuid = oGuid;
	mDestoryTime = dTime;
	mDestoryTimerId = AddLuaTimerEx(dTime, false, call_back);
	(ITimeHelper::GetInstance())->AddStrData(mDestoryTimerId, "DestroyDgnMapGuid", GetGUIDAsString());
	mDelayInit = delay;
}

void DgnMap::Clear()
{
	// 移除定时器
	RemoveLuaTimer(mDestoryTimerId);
	// 踢出所有玩家
	// 这里之所以copy是应为UnBindMulDgnGuidWithPlayerGuid中会调用RemovePlayerGuid,导致迭代器失效
	std::set<uint64_t> copyBind = bindGuidSet;
	std::set<uint64_t> copyPlayer = playerGuidSet;
	auto iter = copyPlayer.begin();
	for (; iter != copyPlayer.end(); ++iter)
	{
		std::string playerGuid = to_string(*iter);
		// 退出副本
		MapMgr::GetInstance()->ExitMulDgnMap(GetGUIDAsString(), playerGuid);
	}
	iter = copyBind.begin();
	for (; iter != copyBind.end(); ++iter)
	{
		std::string playerGuid = to_string(*iter);
		// 解绑dgnGuid
		MapMgr::GetInstance()->UnBindMulDgnGuidWithPlayerGuid(GetName(), playerGuid);
	}
	ResetDgnData();
}

void DgnMap::AddBindPlayerGuid(uint64_t playerGuid)
{
	bindGuidSet.insert(playerGuid);
}

void DgnMap::RemoveBindPlayerGuid(uint64_t playerGuid)
{
	bindGuidSet.erase(playerGuid);
	if (playerGuid == ownerGuid)
	{
		ownerGuid = 0;
		//重新选择房主
		//ownerGuid = bindGuidSet.empty() ? 0 : *bindGuidSet.begin();
	}
}

void DgnMap::AddPlayerGuid(uint64_t playerGuid)
{
	playerGuidSet.insert(playerGuid);
}

void DgnMap::RemovePlayerGuid(uint64_t playerGuid)
{
	playerGuidSet.erase(playerGuid);
}

bool DgnMap::IsEmpty()
{
	auto guid = GetGUID();

	auto owner = MapRoleMgr::GetInstance()->FindPlayer(ownerGuid);
	if (owner) {
		if (owner->GetCurMultDgnMapID() == guid)return false;
	}

	for (auto i : playerGuidSet) {
		auto player = MapRoleMgr::GetInstance()->FindPlayer(i);
		if (!player)continue;
		if (player->GetCurMultDgnMapID() == guid)return false;
	}
	return true;
}
