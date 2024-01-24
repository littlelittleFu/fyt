#include "stdafx.h"
#include "MapMgr.h"
#include "SessionFactory.h"
#include "CNetManager.h"
#include "PlayerChatProhibitMgr.h"

IMPL_SINGLETON(MapMgr)

bool MapMgr::Init()
{
	mScriptName = "MapMgr";
	return true;
}


void MapMgr::ApplyFuncToAllMap(Func f)
{
	for (auto& it : mMapList) {
		if (it.second) it.second->ApplyFuncToAllRoles(f);
	}
	for (auto& it : mDgnMapList) {
		if (it.second) it.second->ApplyFuncToAllRoles(f);
	}
}

Map* MapMgr::CreateMap(const std::string& mapName)
{
	SAFE_BEGIN_EX;
	auto mapTable = sMapConfig.GetByKeyName(mapName);
	if (nullptr == mapTable) {
		LOG_ERROR("failed to find map config. mapName:%s", mapName.c_str());
		return nullptr;
	}

	auto map = FindMap(mapName);
	if (nullptr != map) {
		return map;
	}

	map = new Map();
	if (!map->Init(mapTable)) {
		LOG_ERROR("init map failed. mapName:%s", mapName.c_str());
		delete map;
		return nullptr;
	}

	mMapList.insert(std::pair<std::string, Map*>(mapName, map));
	LOG_NORMAL("create map success. mapName:%s", mapName.c_str());

    map->TriggerEvent(trigger_map_create, map->GetGUIDAsString(), map->GetName());

	return map;
	SAFE_END_EX(nullptr);
}

void MapMgr::DestroyMap(const std::string& mapName)
{
	auto map = FindMap(mapName);
	if (nullptr != map) {
		mMapList.erase(mapName);
		SAFE_RELEASE(map);
	}
}

Map* MapMgr::FindMap(const std::string& mapName)
{
	auto iter = mMapList.find(mapName);
	if (iter != mMapList.end()) {
		return iter->second;
	}
	return nullptr;
}

Map* MapMgr::FindMapByID(uint16_t mapID)
{
    auto cfg = sMapConfig.Get(mapID);
    if (!cfg) return nullptr;
    return FindMap(cfg->KeyName);
}

Map* MapMgr::FindMapByGUID(uint64_t mapGUID)
{
	for (auto& iter : mMapList) {
		if (iter.second->GetGUID() == mapGUID) return iter.second;
	}
	for (auto& iter : mDgnMapList) {
		if (iter.second->GetGUID() == mapGUID) return iter.second;
	}
	return nullptr;
}

void MapMgr::Update(int delta)
{
	for (MapList::iterator iter = mMapList.begin(); iter != mMapList.end(); ++iter) {
		if (nullptr != iter->second) {
			iter->second->Update(delta);
		}
	}
	std::set<uint64_t> destorySet;
	for (DgnMapList::iterator iter = mDgnMapList.begin(); iter != mDgnMapList.end(); ++iter)
	{
		if (nullptr == iter->second || iter->second->GetDestroyFlag())
		{
			destorySet.insert(iter->first);
		}
		if (nullptr != iter->second)
		{
			iter->second->Update(delta);
		}
	}
	for (auto iter = destorySet.begin(); iter != destorySet.end(); ++iter)
	{
		DestroyMulDgnMap(*iter);
	}
}

void MapMgr::OnRecv_EnterMSReq(ProtoCS_EnterMSReq& req)
{
	const DATA::Map *mapcfg = nullptr;

	const auto &mapid = req.roleExtraInfo.mapid;
	if (mapid) mapcfg = sMapConfig.Get(mapid);

	Map *map = nullptr;
	if (mapcfg) map = MapMgr::GetInstance()->FindMap(mapcfg->KeyName);

	if (!map) {
		uint16_t initMapID = 0;
		LuaBindCallRet(initMapID, LUA_SCRIPT_FUNC(this, "GetInitMapID"));

		if (initMapID == 0) {
			LOG_ERROR("initMapID is 0");
			return;
		}

		mapcfg = sMapConfig.Get(initMapID);
		if (!mapcfg) {
			LOG_ERROR("mapcfg is NULL. initMapID: %u", initMapID);
			return;
		}

		map = MapMgr::GetInstance()->FindMap(mapcfg->KeyName);
		if (!map) {
			LOG_ERROR("map is NULL. initMapID: %u", initMapID);
			return;
		}
	}
	
	auto player = MapRoleMgr::GetInstance()->AddPlayer(req.roleBriefInfo.guid);
	if(player == nullptr){
		LOG_ERROR("add player failed. playGUID:%" PRIu64, req.roleBriefInfo.guid);
		return;
	}

	if (req.isProhibitChat != 0) {
		PlayerProhibitChatMgr::GetInstance()->UpdatePlayerProhibitChatMgr(req.playerid, req.isProhibitChat);
	}

	ProtoMS_EnterMSAck ack;
	ack.nClientSessionID = req.sessionid;
	ack.entertype = req.entertype;
	ack.playerid = req.playerid;
	ack.roleguid = req.roleBriefInfo.guid;
	ack.gsobjid = 0;
	ack.errcode = 0;
	ack.roleBriefInfo = req.roleBriefInfo;
	strcpy(ack.errmsg, "notify player enter ack!");
	SendDataBySessionID(req.nMS2GSSessionID, ack);

    auto &posx = req.roleExtraInfo.posx;
    auto &posy = req.roleExtraInfo.posy;
    auto &birthMap = req.roleExtraInfo.birthMap;
    auto &dir = req.roleExtraInfo.dir;

    if (posx == 0 || posy == 0) {
        birthMap = mapcfg->Id;
        dir = dir_down;
        const auto *rows = sBornRegionConfig.GetRows(mapcfg->KeyName);
        if (rows) {
            for (const auto &cfg : *rows) {
                const auto &region = cfg->m_Region;
                if (map->GetRandBlankPointInRange(region.left, region.top, region.width, region.height, posx, posy))
                    break;
            }
        }
    }

    if (posx == 0 || posy == 0) {
        map->GetRandBlankPointInRange(0, 0, map->GetWidth(), map->GetHeight(), posx, posy);
    }

	player->SetUserName(std::string(req.playerName).c_str());
	player->SetUserID(req.playerid);
	player->SetToken(req.token);
	player->SetClSessionID(req.sessionid);
	player->SetGsSessionID(req.nMS2GSSessionID);
    player->SetName(req.roleBriefInfo.name);
	player->SetRoleBriefInfo(req.roleBriefInfo);
    player->SetRoleExtraInfo(req.roleExtraInfo);
	player->SetRoleSettings(req.roleSettings);
    //player->GetQuestDataMgr().SetQuestInfo(req.questInfo);
    //player->GetQuestDataMgr().SetQuestAchieves(req.questAchieves, req.questAchievesNum);

	player->SetSupport(req.isSupport);
    player->OnEnterMap(map);
    player->SetRolePos(req.roleExtraInfo.posx, req.roleExtraInfo.posy);
    player->SetRoleDir(req.roleExtraInfo.dir);
}

void MapMgr::OnRecv_EnterMSNtf(ProtoCS_EnterMSNtf& ntf)
{
	auto player = MapRoleMgr::GetInstance()->FindPlayerByToken(ntf.token);
	if (nullptr == player) {
		LOG_ERROR("cant find player. token:%u", ntf.token);
		return;
	}

	auto map = player->GetCurMap();
	if (nullptr == map || nullptr == map->GetMapConfig()) {
		LOG_ERROR("map is null");
		return;
	}

	auto mapCfg = map->GetMapConfig();
	if (nullptr == mapCfg) {
		LOG_ERROR("map cfg is null");
		return;
	}

	ProtoMS_EnterMSNtf enterMsNtf;
	enterMsNtf.nClientSessionID = player->GetClSessionID();
	enterMsNtf.height = map->GetWidth();
	enterMsNtf.width = map->GetHeight();
	enterMsNtf.view_x = std::max<uint16_t>(mapCfg->LightXr, 8);
	enterMsNtf.view_y = std::max<uint16_t>(mapCfg->LightYr, 8);
	enterMsNtf.token = player->GetToken();
	memcpy_s(enterMsNtf.logic, sizeof(enterMsNtf.logic), mapCfg->KeyName, sizeof(mapCfg->KeyName));
	enterMsNtf.mapcode = mapCfg->Id;
	SendDataBySessionID(player->GetGsSessionID(), enterMsNtf);

	player->OnLogin();
	//如果玩家已经没有属性   不保存到cs   并且让玩家下线
	if (nullptr == player->GetRoleAttr()) {
		ProtoGS_KickOutByLock ack;
		ack.info = E_EXIT_EXITGS;
		ack.sessionid = player->GetClSessionID();
		ack.token = player->GetToken();
		SendDataBySessionID(player->GetGsSessionID(), ack);
		return;
	}
}



std::string MapMgr::CreateMulDgnMap(const std::string& sDgnMapName, const std::string& sPlayerGuid, bool delayInit, uint32_t exitTime, CLuaObject call_back)
{
	LOG_NORMAL("C++: 开始创建多人副本");
	SAFE_BEGIN_EX;
	if (sDgnMapName.empty())
	{
		LOG_ERROR("[%s:%d] 副本name为空", FUNC_LINE);
		return "";
	}
	if (sPlayerGuid.empty())
	{
		LOG_ERROR("[%s:%d] 玩家id为空", FUNC_LINE);
		return "";
	}

	uint64_t playerGuid = std::stoull(sPlayerGuid);
	std::string sDgnMapGuid = GetMulDgnGuidByPlayerGuid(sDgnMapName, sPlayerGuid);
	if (!sDgnMapGuid.empty())
	{
		LOG_NORMAL("[%s:%d] 玩家当前已绑定副本. playGuid:%lld  dgnMapGuid:%s", FUNC_LINE, playerGuid, sDgnMapGuid.c_str());
		return sDgnMapGuid;
	}

	auto pMapConfig = sMapConfig.Get(sDgnMapName);
	if (nullptr == pMapConfig)
	{
		LOG_ERROR("[%s:%d]  配置文件不存在. playGuid:%lld  dgnMapName: %s", FUNC_LINE, playerGuid, sDgnMapName.c_str());
		return "";
	}

	auto dgnMap = new DgnMap();
	if (nullptr == dgnMap)
	{
		LOG_ERROR("[%s:%d] 创建副本失败1. playGuid:%lld  dgnMapName:%s", FUNC_LINE, playerGuid, sDgnMapName.c_str());
		return "";
	}
	else if (!dgnMap->Init(pMapConfig))
	{
		LOG_ERROR("[%s:%d] 创建副本失败2. playGuid:%lld  dgnMapName:%s", FUNC_LINE, playerGuid, sDgnMapName.c_str());
		delete dgnMap;
		return "";
	}

	// 先写死测试
	//dgnMap->SetGUID(123456);
	dgnMap->Prepare(playerGuid, exitTime, call_back, delayInit);
	uint64_t dgnGuid = dgnMap->GetGUID();
	mDgnMapList.insert(std::pair<uint64_t, DgnMap*>(dgnGuid, dgnMap));
	LOG_NORMAL("[%s:%d] 创建多人副本成功. playerGuid:%lld  dgnMapGuid:%lld  dgnMapName:%s  exitTime:%d  delayInit:%d", FUNC_LINE, playerGuid, dgnGuid, sDgnMapName.c_str(), exitTime, delayInit);
	LOG_NORMAL("C++: 创建多人副本成功");
	return dgnMap->GetGUIDAsString();
	SAFE_END_EX("");
}

uint32_t MapMgr::DestroyMulDgnMap(const std::string& sDgnMapGuid)
{
	if (sDgnMapGuid.empty())
	{
		LOG_ERROR("[%s:%d] 副本id为空", FUNC_LINE);
		return 101;
	}

	uint64_t dgnGuid = std::stoull(sDgnMapGuid);
	auto iter = mDgnMapList.find(dgnGuid);
	if (iter != mDgnMapList.end()) 
	{
		if (nullptr != iter->second)
		{
			if (!iter->second->IsEmpty()){
				bool destroy = false;
				TRIGGER_EVENT_RET<bool>(destroy, trigger_whether_destroy_dgn_when_have_players, dgnGuid);
				if (!destroy) {
					LOG_NORMAL("[%s:%d] 副本存在玩家，不可销毁. dgnMapGuid:%lld", FUNC_LINE, dgnGuid);
					return Destroy_have_player;
				}
			}

			iter->second->SetDestroyFlag(true);
		}
		LOG_NORMAL("[%s:%d] 预销毁副本. dgnMapGuid:%lld", FUNC_LINE, dgnGuid);
		return 0;
	}
	LOG_NORMAL("[%s:%d] 副本不存在. dgnMapGuid:%lld", FUNC_LINE, dgnGuid);
	return 0;
}

uint32_t MapMgr::BindMulDgnGuidWithPlayerGuid(const std::string& sDgnMapGuid, const std::string& sPlayerGuid)
{
	if (sDgnMapGuid.empty())
	{
		LOG_ERROR("[%s:%d] 副本id为空", FUNC_LINE);
		return 101;
	}
	if (sPlayerGuid.empty())
	{
		LOG_ERROR("[%s:%d] 玩家id为空", FUNC_LINE);
		return 102;
	}

	uint64_t dgnGuid = std::stoull(sDgnMapGuid);
	uint64_t playerGuid = std::stoull(sPlayerGuid);
	auto player = MapRoleMgr::GetInstance()->FindPlayer(playerGuid);
	if (nullptr == player)
	{
		LOG_ERROR("[%s:%d] 获取玩家实例失败. playGuid:%lld  dgnMapGuid:%lld", FUNC_LINE, playerGuid, dgnGuid);
		return 103;
	}
	//if (player->IsInDgnMap())
	//{
	//	LOG_ERROR("[%s:%d] 玩家正在副本中无法绑定. playGuid:%lld  dgnMapGuid:%lld curDgnMapGuid:%lld", FUNC_LINE, playerGuid, dgnGuid, player->GetCurMultDgnMapID());
	//	return 104;
	//}
	//看需求要不要判断玩家已经绑定就return
	//std::string sDgnMapName = player->GetMultDgnMapName(dgnGuid);
	//if (!sDgnMapName.empty())
	//{
	//	LOG_ERROR("[%s:%d] 玩家已绑定关联副本. playGuid:%lld  dgnMapGuid:%lld dgnMapName:%s", FUNC_LINE, playerGuid, dgnGuid, sDgnMapName.c_str());
	//	return 105;
	//}
	auto iter = mDgnMapList.find(dgnGuid);
	if (iter != mDgnMapList.end() && nullptr != iter->second)
	{
		std::string sDgnMapName = iter->second->GetName();
		LOG_NORMAL("[%s:%d] 玩家绑定关联副本. playGuid:%lld  dgnMapGuid:%lld dgnMapName:%s", FUNC_LINE, playerGuid, dgnGuid, sDgnMapName.c_str());
		// 玩家关联副本
		player->SetMultDgnMapID(sDgnMapName, dgnGuid);
		// 副本关联玩家
		iter->second->AddBindPlayerGuid(playerGuid);
		return 0;
	}
	LOG_ERROR("[%s:%d] 目标副本不存在. playGuid:%lld  dgnMapGuid:%lld", FUNC_LINE, playerGuid, dgnGuid);
	return 106;
}

uint32_t MapMgr::UnBindMulDgnGuidWithPlayerGuid(const std::string& sDgnMapName, const std::string& sPlayerGuid)
{
	if (sDgnMapName.empty())
	{
		LOG_ERROR("[%s:%d] 副本name为空", FUNC_LINE);
		return 101;
	}
	if (sPlayerGuid.empty())
	{
		LOG_ERROR("[%s:%d] 玩家id为空", FUNC_LINE);
		return 102;
	}

	uint64_t playerGuid = std::stoull(sPlayerGuid);
	auto player = MapRoleMgr::GetInstance()->FindPlayer(playerGuid);
	if (player == nullptr)
	{
		LOG_ERROR("[%s:%d] 获取玩家实例失败. playGuid:%lld  dgnMapName:%s", FUNC_LINE, playerGuid, sDgnMapName.c_str());
		return 103;
	}
	//if (player->IsInDgnMap())
	//{
	//	LOG_ERROR("[%s:%d] 玩家正在副本中无法解绑. playGuid:%lld  dgnMapName:%s", FUNC_LINE, playerGuid, sDgnMapName.c_str());
	//	return 104;
	//}
	uint64_t dgnGuid = player->GetMultDgnMapID(sDgnMapName);
	//if (0 == dgnGuid)
	//{
	//	LOG_ERROR("[%s:%d] 玩家实例未绑定关联副本. playGuid:%lld  dgnMapName:%s", FUNC_LINE, playerGuid, sDgnMapName.c_str());
	//	return 105;
	//}
	auto iter = mDgnMapList.find(dgnGuid);
	if (iter != mDgnMapList.end() && nullptr != iter->second)
	{
		LOG_NORMAL("[%s:%d] 玩家解绑关联副本. playGuid:%lld  dgnMapGuid:%lld dgnMapName:%s", FUNC_LINE, playerGuid, dgnGuid, sDgnMapName.c_str());
		// 玩家解绑副本
		player->SetMultDgnMapID(sDgnMapName, 0);
		// 副本解绑玩家
		iter->second->RemoveBindPlayerGuid(playerGuid);
		return 0;
	}
	LOG_ERROR("[%s:%d] 目标副本不存在,玩家解绑关联副本. playGuid:%lld  dgnMapGuid:%lld dgnMapName:%s", FUNC_LINE, playerGuid, dgnGuid, sDgnMapName.c_str());
	player->SetMultDgnMapID(sDgnMapName, 0);
	return 0;
}

uint32_t MapMgr::EnteryMulDgnMap(const std::string& sDgnMapName, const std::string& sPlayerGuid, uint16_t posX, uint16_t posY, const log_params& lp)
{
	LOG_NORMAL("C++: 开始进入多人副本");
	if (sDgnMapName.empty())
	{
		LOG_ERROR("[%s:%d] 副本name为空", FUNC_LINE);
		return 101;
	}
	if (sPlayerGuid.empty())
	{
		LOG_ERROR("[%s:%d] 玩家id为空", FUNC_LINE);
		return 102;
	}

	uint64_t playerGuid = std::stoull(sPlayerGuid);
	auto player = MapRoleMgr::GetInstance()->FindPlayer(playerGuid);
	if (nullptr == player)
	{
		LOG_ERROR("[%s:%d]  获取玩家实例失败. playGuid:%lld  dgnMapName:%s", FUNC_LINE, playerGuid, sDgnMapName.c_str());
		return 103;
	}
	uint64_t dgnGuid = player->GetMultDgnMapID(sDgnMapName);
	if (0 == dgnGuid)
	{
		LOG_ERROR("[%s:%d] 玩家未关联当前副本. playGuid:%lld  dgnMapName:%s", FUNC_LINE, playerGuid, sDgnMapName.c_str());
		return 104;
	}
	auto dgnMap = FindMulDgnMapByDgnGuid(dgnGuid);
	if (nullptr == dgnMap)
	{
		LOG_ERROR("[%s:%d] 获取副本实例失败. playGuid:%lld  dgnMapGuid:%lld  dgnMapName:%s", FUNC_LINE, playerGuid, dgnGuid, sDgnMapName.c_str());
		return 105;
	}
	return player->EnteryMulDgnMap(dgnMap, posX, posY, lp);
}

uint32_t MapMgr::ExitMulDgnMap(const std::string& sDgnMapGuid, const std::string& sPlayerGuid)
{
	LOG_NORMAL("C++: 开始退出多人副本");
	if (sDgnMapGuid.empty())
	{
		LOG_ERROR("[%s:%d] 副本id为空", FUNC_LINE);
		return 104;
	}
	if (sPlayerGuid.empty())
	{
		LOG_ERROR("[%s:%d] 玩家id为空", FUNC_LINE);
		return 101;
	}

	uint64_t dgnGuid = std::stoull(sDgnMapGuid);
	uint64_t playerGuid = std::stoull(sPlayerGuid);
	auto player = MapRoleMgr::GetInstance()->FindPlayer(playerGuid);
	if (nullptr == player)
	{
		LOG_ERROR("[%s:%d] 获取玩家实例失败. playGuid:%lld", FUNC_LINE, playerGuid);
		return 102;
	}
	uint64_t curDgnGuid = player->GetCurMultDgnMapID();
	if (dgnGuid != curDgnGuid)
	{
		LOG_ERROR("[%s:%d] 玩家所在副本Guid不匹配. playGuid:%lld dgnMapGuid:%lld  curDgnMapGuid:%lld", FUNC_LINE, playerGuid, dgnGuid, curDgnGuid);
		return 105;
	}
	auto dgnMap = FindMulDgnMapByDgnGuid(dgnGuid);
	if (nullptr == dgnMap)
	{
		LOG_ERROR("[%s:%d] 获取副本实例失败. playGuid:%lld  dgnMapGuid:%lld ", FUNC_LINE, playerGuid, dgnGuid);
		return 103;
	}
	return player->ExitMulDgnMap(dgnMap);
}

std::string	MapMgr::GetMulDgnGuidByPlayerGuid(const std::string& sDgnMapName, const std::string& sPlayerGuid)
{
	if (sDgnMapName.empty())
	{
		LOG_ERROR("[%s:%d] 副本name为空", FUNC_LINE);
		return "";
	}
	if (sPlayerGuid.empty())
	{
		LOG_ERROR("[%s:%d] 玩家id为空", FUNC_LINE);
		return "";
	}

	uint64_t playerGuid = std::stoull(sPlayerGuid);
	auto player = MapRoleMgr::GetInstance()->FindPlayer(playerGuid);
	if (player == nullptr)
	{
		LOG_ERROR("[%s:%d] 获取玩家实例失败. playGuid:%s dgnMapName:%s", FUNC_LINE, sPlayerGuid.c_str(), sDgnMapName.c_str());
		return "";
	}
	uint64_t dgnGuid = player->GetMultDgnMapID(sDgnMapName);
	return (0 == dgnGuid) ? "" : to_string(dgnGuid);
}

DgnMap* MapMgr::FindMulDgnMapByDgnGuid(uint64_t dgnGuid)
{
	auto iter = mDgnMapList.find(dgnGuid);
	if (iter != mDgnMapList.end())
	{
		return iter->second;
	}
	return nullptr;
}

uint32_t MapMgr::DestroyMulDgnMap(uint64_t dgnGuid)
{
	auto iter = mDgnMapList.find(dgnGuid);
	if (iter != mDgnMapList.end())
	{
		if (nullptr != iter->second)
		{
			iter->second->Clear();
			SAFE_RELEASE(iter->second);
		}
		mDgnMapList.erase(iter);
		LOG_NORMAL("[%s:%d] 销毁副本. dgnMapGuid:%lld", FUNC_LINE, dgnGuid);
		return 0;
	}
	LOG_NORMAL("[%s:%d] 副本不存在. dgnMapGuid:%lld", FUNC_LINE, dgnGuid);
	return 0;
}
