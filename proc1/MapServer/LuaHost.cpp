#include "stdafx.h"
#include "LuaHost.h"

#include "MapMgr.h"
#include "Map.h"
#include "Role.h"
#include "MapRoleMgr.h"
#include "TeamMgr.h"

#include "CustVarMgr.h"
#include "ItemMap.h"
#include "MailMgr.h"
#include "CustomEquipSiteAndSub.h"
#include "CastleWarMgr.h"
#include "Auction.h"
#include "WantedList.h"
#include "RoleInfoCache.h"
#include "ProhibitChatMgr.h"
#include "LuaGmMgr.h"
#include "BossInfo.h"
#include "PlayerChatProhibitMgr.h"
#include "CustList.h"


#define BEGIN_EXPORT()  LUABIND_REGISTER_CLASS_BEGIN(luaScript, LuaHost)
#define END_EXPORT()    LUABIND_REGISTER_CLASS_END(luaScript)
#define EXPORT(func)    LUABIND_REGISTER_CLASS_FUNC(LuaHost, func)

IMPL_SINGLETON(LuaHost);


inline static log_params ParseLogParams(const CLuaObject& logInfo)
{
    log_params lp;
    SAFE_BEGIN_EX
    if (luabind::type(logInfo) != LUA_TTABLE) return lp;

    if (luabind::type(logInfo[1]) != LUA_TSTRING) return lp;
    lp.info = luabind::object_cast<std::string>(logInfo[1]);

    return lp;
    SAFE_END_EX(lp)
}

inline static log_params ParseEDLogParams(const CLuaObject& logInfo)
{
    log_params lp;
    SAFE_BEGIN_EX
    if (luabind::type(logInfo) != LUA_TTABLE) return lp;

    Json::Value info(Json::arrayValue);
    for (luabind::iterator it(logInfo), end; it != end; ++it)
    {
        auto luaPos = *it;
        if (luabind::type(luaPos) != LUA_TTABLE) continue;

        if (luabind::type(luaPos[1]) != LUA_TSTRING) continue;  // 票
        if (luabind::type(luaPos[2]) != LUA_TNUMBER) continue;  // 数量

        Json::Value value(Json::arrayValue);
        value.append(Json::Value(luabind::object_cast<std::string>(luaPos[1])));
        value.append(Json::Value(luabind::object_cast<uint16_t>(luaPos[2])));
        info.append(value);
    }
    lp.info = std::move(info.toFastString());
    return lp;
    SAFE_END_EX(lp)
}

inline static  std::vector<log_item_params> ParseItemLogParams(const CLuaObject& itemInfo, const CLuaObject& goldInfo)
{
    std::vector<log_item_params> lips;
    SAFE_BEGIN_EX
    if (luabind::type(itemInfo) == LUA_TTABLE)
    {
        for (luabind::iterator it(itemInfo), end; it != end; ++it)
        {
            auto luaPos = *it;
            if (luabind::type(luaPos) != LUA_TTABLE) continue;

            if (luabind::type(luaPos[1]) != LUA_TSTRING) continue;
            if (luabind::type(luaPos[2]) != LUA_TNUMBER) continue;

            log_item_params lip;
            lip.itemKeyname = luabind::object_cast<std::string>(luaPos[1]);
            lip.itemNum = luabind::object_cast<uint16_t>(luaPos[2]);
            lips.push_back(lip);
        }
    }
    if (luabind::type(goldInfo) == LUA_TTABLE)
    {
        for (luabind::iterator it(goldInfo), end; it != end; ++it)
        {
            auto luaPos = *it;
            if (luabind::type(luaPos) != LUA_TTABLE) continue;

            if (luabind::type(luaPos[1]) != LUA_TSTRING) continue;
            if (luabind::type(luaPos[2]) != LUA_TNUMBER) continue;

            log_item_params lip;
            lip.itemKeyname = luabind::object_cast<std::string>(luaPos[1]);
            lip.itemNum = luabind::object_cast<uint16_t>(luaPos[2]);
            lips.push_back(lip);
        }
    }
    return lips;
    SAFE_END_EX(lips)
}

void LuaHost::RegisterLuaAPI(CLuaScript *luaScript)
{
    if (!luaScript) return;

    BEGIN_EXPORT();

    // Global export functions
    EXPORT(GetGlobalProp);
    EXPORT(GetRoleCfgValue);
    EXPORT(GetBuffProp);
    EXPORT(GetBuffGroupProp);
    EXPORT(GetSkillProp);
    EXPORT(GetMonsterProp);
    EXPORT(GetNpcProp);
    EXPORT(GetMapProp);
    EXPORT(GetItemProp);
    EXPORT(GetItemPropByKeyName);
    EXPORT(GetGroupAttrProp);
    EXPORT(GetQuestProp);
    EXPORT(SetCustVar);
    EXPORT(SetCustVarEx);
    EXPORT(GetCustVar);
    EXPORT(ReloadScript);
    EXPORT(RegisterCustomSiteAndSub);
    EXPORT(GetConstantCfg);
    EXPORT(SetCreateRoleNeedCode);
    EXPORT(GBK2UTF8);
    EXPORT(UTF82GBK);
    EXPORT(DeleteMallRemainedData);
    EXPORT(CheckIfRoleExistByName);
    EXPORT(CheckIfRoleExistByGUID);

    EXPORT(AddScheduled);
    EXPORT(AddLuaTimer);
    EXPORT(AddLuaTimerEx);
    EXPORT(RemoveLuaTimer);
    EXPORT(AddNumData);
    EXPORT(GetNumData);
    EXPORT(RemoveNumData);
    EXPORT(AddStrData);
    EXPORT(GetStrData);
    EXPORT(RemoveStrData);
    EXPORT(AddMailByName);
    EXPORT(AddMailByGuid);

    EXPORT(GetAllOnlinePlayerGuid);
    EXPORT(RunLuaScriptEveryOnlinePlayer);
    EXPORT(SimpleArithmetic);
    EXPORT(SetFormAllowFunc);
    EXPORT(SetCallBackUpdateAttr32);
    EXPORT(SetCallBackUpdateAttr64);

    EXPORT(SendChatMsg);
    EXPORT(SendChatMsgTime);

    EXPORT(GetCustListInfoByType);

    EXPORT(Auction_AddItemInfo);
    EXPORT(Auction_OfferPrice);
    EXPORT(Auction_GetFinishedItemTable);

    
    EXPORT(AddTrigger);
    EXPORT(RemoveTrigger);

    // MapMgr export functions
    EXPORT(MapMgr_CreateMap);
    EXPORT(MapMgr_DestroyMap);
    EXPORT(MapMgr_FindMap);
    EXPORT(MapMgr_CreateMulDgnMap);
    EXPORT(MapMgr_DestroyMulDgnMap);
    EXPORT(MapMgr_BindMulDgnGuidWithPlayerGuid);
    EXPORT(MapMgr_UnBindMulDgnGuidWithPlayerGuid);
    EXPORT(MapMgr_EnteryMulDgnMap);
    EXPORT(MapMgr_ExitMulDgnMap);
    EXPORT(MapMgr_GetMulDgnGuidByPlayerGuid);

    // Map export functions
    EXPORT(Map_GetID);
    EXPORT(Map_IsThisMapGridType);
    EXPORT(Map_RoleEnter);
    EXPORT(Map_RoleLeave);
    EXPORT(Map_GenSceneItem);
    EXPORT(Map_GenSceneItemByName);
    EXPORT(Map_GetMapName);
    EXPORT(Map_SetRegionSize);
    EXPORT(Map_GetRoleInPoint);
    EXPORT(Map_IsSafeRegion);
    EXPORT(Map_IsGridAvail);
    EXPORT(Map_GenMapMonster);
    EXPORT(Map_GenMapMonsterByName);
    EXPORT(Map_GenMapMonsterByID);
    EXPORT(Map_GetMonsterNum);
    EXPORT(Map_GenMapNPCByKeyName);
    EXPORT(Map_DelMapNPCByGuid);
    EXPORT(Map_SendSysMsg);
    EXPORT(Map_AddJumpPoint);
    EXPORT(Map_DelJumpPoint);
    EXPORT(Map_GetAllRoleByType);
    EXPORT(Map_GetAllEmptyGrid);
    EXPORT(Map_GetAllCanDropItemGrid);
    EXPORT(Map_DisappearMonsterCorpseInPoint);
    EXPORT(Map_GetBossInfo);

    // RoleMgr export functions
    EXPORT(RoleMgr_GetPlayerGUID);
    EXPORT(RoleMgr_IsRoleExist);

    // Role export functions
    EXPORT(Role_GetType);
    EXPORT(Role_GetName);
    EXPORT(Role_SetName);
    EXPORT(Role_SetAlias);
    EXPORT(Role_GetCurMapGUID);
    EXPORT(Role_GetProp);
    EXPORT(Role_SetProp);
    EXPORT(Role_AddProp);
    EXPORT(Role_GetProp64);
    EXPORT(Role_ModProp64);
    EXPORT(Role_ModProp64ByStr);
    EXPORT(Role_CheckProp64Amount);
    EXPORT(Role_GetPosX);
    EXPORT(Role_GetPosY);
    EXPORT(Role_SetPos);
    EXPORT(Role_GetDir);
    EXPORT(Role_SetDir);
    EXPORT(Role_AddBuff);
    EXPORT(Role_AddBuffByRole);
    EXPORT(Role_RemoveBuff);
    EXPORT(Role_RemoveBuffWithActorID);
    EXPORT(Role_BuffExist);
    EXPORT(Role_BuffExistByGroupID);
    EXPORT(Role_BuffExistByKeyName);
    EXPORT(Role_GetBuffStack);
    EXPORT(Role_GetBuffLeftTime);
    EXPORT(Role_GetBuffList);
    EXPORT(Role_UpdateBuffStack);
    EXPORT(Role_AttackedByRole);
    EXPORT(Role_AttackedByRole2);
    EXPORT(Role_IsAlive);
    EXPORT(Role_GetBuffActorGuid);
    EXPORT(Role_GetBuffActorName);
    EXPORT(Role_GetBuffActorJob);
    EXPORT(Role_GetBuffActorLevel);
    EXPORT(Role_GetBuffActorSkill);
    EXPORT(Role_IncreaseHP);
    EXPORT(Role_DecreaseHP);
    EXPORT(Role_ChangeAppearance);
    EXPORT(Role_SetSkillProp);
    EXPORT(Role_GetSkillProp);
    EXPORT(Role_JumpMapByGuid);
    EXPORT(Role_RandJumpMapByGuid);
    EXPORT(Role_ApplySkill);
    EXPORT(Role_GetMasterGUIDAsString);
    EXPORT(Role_SetRideHorseModelid);
    EXPORT(Role_SetRideHorseSwitch);
    EXPORT(Role_GetRideHorseModelid);
    EXPORT(Role_GetRideHorseSwitch);

    // Player export functions
    EXPORT(Player_IsSupport);
    EXPORT(Player_SendItemDestroyAck);
    EXPORT(Player_SendPlayerReliveNtf);
    EXPORT(Player_SendPlayerShowNtf);
    EXPORT(Player_SendRoleAttrExtRefNtf);
    EXPORT(Player_AddPlayerItem);
    EXPORT(Player_AddPlayerExperience);
    EXPORT(Player_AddPlayerGold);
    EXPORT(Player_RunClientScript);
    EXPORT(Player_NotifyPlayer_StartMove);
    EXPORT(Player_RunClientScript_plus);
    EXPORT(Player_SendErrorAck);
    EXPORT(Player_SendPopDlgMsgNtf);
    EXPORT(Player_SendPlayerFamilyChangeNtf);
    EXPORT(Player_Jump);
    EXPORT(Player_JumpMap);
    EXPORT(Player_JumpWithType);
    EXPORT(Player_JumpMapWithType);
    EXPORT(Player_SummonMonsterByID);
    EXPORT(Player_SummonMonsterByName);
    EXPORT(Player_DestroySummonMonster);
    EXPORT(Player_GetSummonMonster);
    EXPORT(Player_PetMonsterByID);
    EXPORT(Player_PetMonsterByName);
    EXPORT(Player_PetMonsterIDByAttrTable);
    EXPORT(Player_PetMonsterNameByAttrTable);
    EXPORT(Player_DestroyPetMonster);
    EXPORT(Player_GetPetList);
    EXPORT(Player_SetPetActivityStatus);
    EXPORT(Player_DestroyAllPetMonster);
    EXPORT(Player_SetPetPickItemStatus);
    EXPORT(Player_EnterShop);
    EXPORT(Player_EnterDgnMap);
    EXPORT(Player_ExitDgnMap);
    EXPORT(Player_IsInDgnMap);
    EXPORT(Player_GetIdleBagCount);
    EXPORT(Player_GetBagFirstFreeSite);
    EXPORT(Player_ItemMove);
    EXPORT(Player_AddItem);
    EXPORT(Player_AddItemByKeyName);
    EXPORT(Player_AddItemByKeyNameToSite);
    EXPORT(Player_AddItems);
    EXPORT(Player_RemoveItem);
    EXPORT(Player_RemoveItemByGuid);
    EXPORT(Player_RemoveItemByGuid2);
    EXPORT(Player_RemoveAllItem);
    EXPORT(Player_GetItemNum);
    EXPORT(Player_GetItemNumByKeyName);
    EXPORT(Player_GetItemAmount);
    EXPORT(Player_SetItemAmount);
    EXPORT(Player_GetTeamMemNum);
    EXPORT(Player_GetTeamInfo);
    EXPORT(Player_StartQuestDialog);
    EXPORT(Player_IsDoingQuest);
    EXPORT(Player_GetQuestState);
    EXPORT(Player_GetAcceptableQuests);
    EXPORT(Player_GetCurQuestID);
    EXPORT(Player_GetPreQuestID);
    EXPORT(Player_TalkToNpc);
    EXPORT(Player_CreateGuild);
    EXPORT(Player_AddSkill);
    EXPORT(Player_DeleteSkill);
    EXPORT(Player_SkillIsExist);
    EXPORT(Player_GetSkillIDList);
    EXPORT(Player_GetSkillIDByChainID);
    EXPORT(Player_GetWarehouseFreeSize);
    EXPORT(Player_GetAdvWarehouseFreeSize);
    EXPORT(Player_GetWarehouseFirstFreeSite);
    EXPORT(Player_GetAdvWarehouseFirstFreeSite);
    EXPORT(Player_GetVipExtePermissions);
    EXPORT(Player_HasVipExtePermissions);
    EXPORT(Player_SendMsgNtf);
    EXPORT(Player_GetGuildGUID);
    EXPORT(Player_GetGuildMemberTitle);
    EXPORT(Player_GetGuildMemberOldTitle);
    EXPORT(Player_GetGuildMemberNewTitle);
    EXPORT(Player_GetCurContrib);
    EXPORT(Player_SetCurContrib);
    EXPORT(Player_GetTotalContrib);
    EXPORT(Player_GetRolePackInfo);
    EXPORT(Player_GetItemBySite);
    EXPORT(Player_GetItemBindType);
    EXPORT(Player_SetItemBindType);
    EXPORT(Player_GetItemSiteByGuid);
    EXPORT(Player_GetGuildName);
    EXPORT(Player_GetTeamGuid);
    EXPORT(Player_AddSingleItem);
    EXPORT(Player_RemoveItemByKeyName);
    EXPORT(Player_SetAutoPickItemRadius);
    EXPORT(Player_SetAutoPickItemRelativePositions);
    EXPORT(Player_SetAutoPickItemInterval);
    EXPORT(Player_SetItemCfg);
    EXPORT(Player_SetName);
    EXPORT(Player_AddTitle);
    EXPORT(Player_DelTitle);
    EXPORT(Player_HasTitle);
    EXPORT(Player_TitleIDToName);
    EXPORT(Player_TitleNameToID);
    EXPORT(Player_RedemptionActivationCode);
    EXPORT(Player_AddProficiencyValue);
    EXPORT(Player_SetSkillLevel);
    EXPORT(Role_InsertInfo);
    EXPORT(Player_IsProhibitChat);
    EXPORT(Player_GetListProp);
    EXPORT(Player_ItemGuidList);
    EXPORT(Player_IsLuaGM);
    EXPORT(Player_AddCustListInfo);
    EXPORT(Player_SetGender);
    EXPORT(Role_UpdateInfo);
    EXPORT(Role_ClearInfo);
    EXPORT(Role_DelInfo);
    EXPORT(Role_GetInfoReq);
    EXPORT(Role_GetInfoAck);
    EXPORT(Role_SetDynAttr);
    EXPORT(Role_GetDynAttr);
    // NPC export functions
    EXPORT(Npc_NpcTalkAck);
    EXPORT(Npc_GetTemplateID);
    EXPORT(NPC_GetKeyName);


    // Monster export functions
    EXPORT(Monster_BeSuckedAway);
    EXPORT(Monster_SetMasterName);
    EXPORT(Monster_GetTemplateID);
    EXPORT(Monster_GetTemplateIDByName);
    EXPORT(Monster_GetMasterGUIDAsString);
    EXPORT(Monster_GetBelongPlayerIDAsString);
    EXPORT(Monster_SetSummonMonsterType);
    EXPORT(Monster_GetHateValueMap);
    EXPORT(Monster_GetCurAttackTar);
    EXPORT(Monster_InitBiaoChe);
    EXPORT(Monster_RegisterBehavior);
    EXPORT(Monster_RegisterAttribute);
    EXPORT(Monster_RemoveMonsterBehavior);
    EXPORT(Monster_RemoveMonster);
    EXPORT(Monster_SetNameColor);
    EXPORT(Monster_SwapSkillGroup);
    EXPORT(Monster_UseSpecialSkill);
    EXPORT(Monster_Escape);
    EXPORT(Monster_AddSkill);
    EXPORT(Monster_RemoveSkill);
    EXPORT(Monster_GetCurSkillGroup);
    EXPORT(Monster_DropItem);
    EXPORT(Monster_UpdateBiaocheAI);
    EXPORT(Monster_SetPetFollowMasterAttackState);

    // Guild export functions
    EXPORT(Guild_GetGUIDByName);
    EXPORT(Guild_GetLeaderName);
    EXPORT(Guild_AddAlly);
    EXPORT(Guild_DelAlly);
    EXPORT(Guild_IsAlly);
    EXPORT(Guild_AddEnemy);
    EXPORT(Guild_DelEnemy);
    EXPORT(Guild_IsEnemy);
    EXPORT(Guild_GetGuildNameList);
    EXPORT(Guild_GetGuildMember);
    EXPORT(Guild_JoinGuild);
    EXPORT(Guild_SetGuildLevel);
    EXPORT(Guild_GuildWar);
    EXPORT(Guild_SetGuildAutoJoinLevel);
    EXPORT(Guild_EditGuildNotice);
    EXPORT(Guild_ChangeGuildMemberTitle);
    EXPORT(Guild_KickGuildMember);
    EXPORT(Guild_DestroyGuild);

    // Item export functions
    EXPORT(Item_UpdateDurability);
    EXPORT(Item_Geturability);
    EXPORT(Item_SetDynAttr);
    EXPORT(Item_GetDynAttr);
    EXPORT(Item_GetTempId);
    EXPORT(Item_ItemInfoEncodeToJson);
    EXPORT(Item_DecodeJsonToAddItem);
    EXPORT(Item_SetSubType);
    EXPORT(Item_SetName);
    EXPORT(Item_IsBind);

    // shabak export functions
    EXPORT(StartCastleWar);
    EXPORT(StopCastleWar);
    EXPORT(GetCastleAttackFamily);
    EXPORT(GetCastleOwnFamily);
    EXPORT(SetCastleOwnFamily);
    EXPORT(QueryCastleStart);
    EXPORT(IsCastleWarStart);
    EXPORT(GenCastleMonster);

    // wanted list export functions
    EXPORT(GetWantedList);
    EXPORT(PostBounty);

    EXPORT(GetRebateMoneyInfo);
    EXPORT(GetRebateMoney);

    EXPORT(Log_ActivityData);
    EXPORT(Log_RewardData);
    EXPORT(Log_GiftPackData);
    EXPORT(Log_RecoveryData);

    EXPORT(SetMaxImageCount);
    EXPORT(Role_GetProp_Info);
    EXPORT(Role_GetRegionRoleByType);
    EXPORT(PostHttpCurl);
    EXPORT(SetMoveMistake);
    EXPORT(LuaSerialize);
    EXPORT(Getmicrosecond);
    EXPORT(BigNumberCalculation);
    END_EXPORT();
}

////////////////////////////////////////////////////////////////////////////////
//
// Global export functions
//
void LuaHost::PostHttpCurl(const std::string& cmd, const std::string& custom, const std::string& callBackFunc)
{
    ProtoMS_CustomHttp data;
    strcpy_s(data.cmd, _countof(data.cmd), cmd.c_str());
    strcpy_s(data.param, _countof(data.param), custom.c_str());
    strcpy_s(data.callBackFunc, _countof(data.callBackFunc), callBackFunc.c_str());
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

bool LuaHost::GetGlobalProp(uint16_t propType)
{
    return ::GetGlobalProp(propType);
}

bool LuaHost::GetRoleCfgValue(uint32_t level, uint8_t job, uint16_t propType)
{
    return ::GetRoleProp(level, job, propType);
}

bool LuaHost::GetBuffProp(uint16_t buffID, uint16_t propType)
{
    return ::GetBuffProp(buffID, propType);
}

bool LuaHost::GetBuffGroupProp(uint16_t g1, uint16_t g2, uint16_t propType)
{
    return ::GetBuffGroupProp(g1, g2, propType);
}

bool LuaHost::GetSkillProp(uint16_t skillID, uint16_t propType)
{
    return ::GetSkillProp(skillID, propType);
}

bool LuaHost::GetMonsterProp(uint16_t monsterID, uint16_t propType)
{
    return ::GetMonsterProp(monsterID, propType);
}

bool LuaHost::GetNpcProp(uint16_t npcID, uint16_t propType)
{
    return ::GetNpcProp(npcID, propType);
}

bool LuaHost::GetMapProp(uint16_t mapID, uint16_t propType)
{
    return ::GetMapProp(mapID, propType);
}

bool LuaHost::GetItemProp(uint16_t itemID, uint16_t propType)
{
    return ::GetItemProp(itemID, propType);
}

bool LuaHost::GetItemPropByKeyName(const std::string& itemKeyName, uint16_t propType)
{
    return ::GetItemProp(itemKeyName, propType);
}

bool LuaHost::GetGroupAttrProp(uint16_t groupID, uint16_t propType)
{
    return ::GetGroupAttrProp(groupID, propType);
}

bool LuaHost::GetQuestProp(uint16_t questID, uint16_t propType)
{
    return ::GetQuestProp(questID, propType);
}

bool LuaHost::SetCustVar(const std::string &belong, std::string name, std::string value, uint8_t type)
{
    return CustVarMgr::GetInstance()->SetVar(belong, std::move(name), std::move(value), type);
}
bool LuaHost::SetCustVarEx(std::string name, std::string value, uint8_t type, uint8_t mergeType)
{
    return CustVarMgr::GetInstance()->SetVar("0", std::move(name), std::move(value), type, mergeType);
}
std::string LuaHost::GetCustVar(const std::string &belong, const std::string &name)
{
    return CustVarMgr::GetInstance()->GetVar(belong, name);
}

void LuaHost::ReloadScript(uint32_t scriptType)
{
    SAFE_BEGIN;

    auto *fileHelper = IFileHelper::GetInstance();
    if (!fileHelper) return;

    const char *subFolder = nullptr;

    switch (scriptType) {

    case script_type_player:        // 玩家相关脚本
        subFolder = "player";
        break;

    case script_type_hero:          // 英雄相关脚本
        break;

    case script_type_monster:       // 怪物相关脚本
        subFolder = "monster";
        break;

    case script_type_npc:           // NPC相关脚本
        subFolder = "npc";
        break;

    case script_type_item:          // 物品相关脚本
        subFolder = "item";
        break;

    case script_type_map:           // 地图相关脚本
        subFolder = "map";
        break;

    case script_type_team:          // 组队相关脚本
        break;

    case script_type_guild:         // 行会相关脚本
        break;

    case script_type_event:         // 事件相关脚本
        break;

    case script_type_scene_magic:   // 场景魔法相关脚本
        break;

    case script_type_system:        // 系统相关脚本
        break;

    case script_type_mail:          // 邮件相关脚本
        break;

    case script_type_consignment:   // 寄售行相关脚本
        break;

    case script_type_achievement:   // 成就相关脚本
        break;

    case script_type_form:          // 表单相关脚本
        subFolder = "form";
        break;

    case script_type_console:       // 控制台相关脚本
        subFolder = "console";
        break;

    case script_type_activity:      // 活动相关脚本
        break;

    case script_type_quest:         // 任务相关脚本
        break;

    case script_type_vip:           // VIP相关脚本
        break;

    case script_type_skill:         // 技能相关脚本
        subFolder = "skill";
        break;

    case script_type_buff:          // BUFF相关脚本
        break;

    case script_type_all:
        break;

    default:
        break;
    }

    auto t0 = std::chrono::high_resolution_clock::now();

    if (subFolder) {
        const auto &basePath = ConfigInfo::GetInstance()->m_sScriptFolderPath;
        auto scripts = fileHelper->GetAllFilesInDirRecursive(basePath + subFolder, "*.lua");
        CLuaEngine::GetInstance()->LoadLuaScripts(std::move(scripts));
    }
    else {          // 加载所有脚本
        MapServer::GetInstance()->LoadLuaScripts();
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);

    LOG_NORMAL("Reloading %s scripts takes time: %dms",
               subFolder ? subFolder : "all", dt.count());

    SAFE_END;
}

bool LuaHost::RegisterCustomSiteAndSub(const CLuaObject& luaObj)
{
    SAFE_BEGIN_EX
    for (luabind::iterator it(luaObj), end; it != end; ++it)
    {
        auto obj = *it;

        const auto& key = obj[1];
        if (luabind::type(key) != LUA_TNUMBER) return false;
        auto Fkey = luabind::object_cast<uint16_t>(key);
        const auto& value = obj[2];
        vector<uint16_t> vValue;
        for (luabind::iterator iter(value), end; iter != end; ++iter)
        {
            auto inobj = *iter;
            if (luabind::type(inobj) != LUA_TNUMBER) return false;
            auto Fvalue = luabind::object_cast<uint16_t>(inobj);
            vValue.emplace_back(Fvalue);
        }
        CustomEquipSiteAndSub::GetInstance()->SetSubSite(Fkey, vValue);
    }
    return true;
    SAFE_END_EX(false)
}

std::string LuaHost::GetConstantCfg(const std::string& key)
{
    SAFE_BEGIN_EX

    if (!ConfigInfo::GetInstance()->m_beInited) return "";
    auto& cfgMap = ConfigInfo::GetInstance()->m_constantCfgMap;
    auto iter = cfgMap.find(key);
    if (iter == cfgMap.end()) return "";
    return iter->second.value;

    SAFE_END_EX("")
}

void LuaHost::SetConstantCfg(const std::string& key, const std::string& value)
{
    SAFE_BEGIN_EX

    auto& cfgMap = ConfigInfo::GetInstance()->m_constantCfgMap;
    CONSTANT_CFG cfg;
    cfg.name = key;
    cfg.value = value;
    cfgMap[key] = cfg;

    CONSTANT_CFG_MAP m;
    m[key] = cfg;
    // 只发送变化的
    ProtoMS_UpdateConstantCfgReq data;
    data.custom << m;
    bool res = SendDataBySessionType(SESSION_TYPE_MS2CS, data);
    if (!res)
    {
        TimerData timer;
        timer.interval = 3000;
        timer.loop = true;
        timer.callBack = [=](const TimerData& t) {
            const_cast<TimerData*>(&t)->invalid = SendDataBySessionType(SESSION_TYPE_MS2CS, data);
        };
        TimeHelper::GetInstance()->AddTimer(timer);
    }
    SAFE_END;
}

void LuaHost::SetCreateRoleNeedCode(uint8_t beSet)
{
    SetConstantCfg(CONSTANT_CREATE_ROLE_NEED_CODE, std::to_string(beSet));
}

std::string LuaHost::GBK2UTF8(const std::string &str)
{
    SAFE_BEGIN_EX

    return gbk_to_utf8(str);

    SAFE_END_EX("")
}

std::string LuaHost::UTF82GBK(const std::string &str)
{
    SAFE_BEGIN_EX;

    return utf8_to_gbk(str);

    SAFE_END_EX("");
}

void LuaHost::DeleteMallRemainedData()
{
    SAFE_BEGIN
    ProtoMS_DeleteMallRemainedData data;
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
    SAFE_END
}

void LuaHost::CheckIfRoleExistByName(const std::string &name, const CLuaObject &callback)
{
    auto spRoleInfo = RoleInfoCache::GetInstance()->GetRoleInfo(name);
    if (spRoleInfo) {
        LuaBindCallExVoid(callback, spRoleInfo->name, std::to_string(spRoleInfo->guid), spRoleInfo->exist);
        return;
    }

    auto seq = Tools::GenerateUINT32();
    SendCheckRoleExistenceReqToCS(seq, static_cast<uint8_t>(by_name), name, 0);

    auto query = std::make_shared<RoleInfoPendingQuery>(seq, callback);
    RoleInfoPendingQueryMgr::GetInstance()->CacheQuery(std::move(query));
}

void LuaHost::CheckIfRoleExistByGUID(const std::string &guid, const CLuaObject &callback)
{
    auto nGUID = std::stoull(guid);

    auto spRoleInfo = RoleInfoCache::GetInstance()->GetRoleInfo(nGUID);
    if (spRoleInfo) {
        LuaBindCallExVoid(callback, spRoleInfo->name, guid, spRoleInfo->exist);
        return;
    }

    auto seq = Tools::GenerateUINT32();
    SendCheckRoleExistenceReqToCS(seq, static_cast<uint8_t>(by_guid), EMPTYSTR, nGUID);

    auto query = std::make_shared<RoleInfoPendingQuery>(seq, callback);
    RoleInfoPendingQueryMgr::GetInstance()->CacheQuery(std::move(query));
}

void LuaHost::SendCheckRoleExistenceReqToCS(uint32_t seq, uint8_t by, const std::string &name, uint64_t guid)
{
    ProtoMS_CheckRoleExistenceReq data;

    data.seq = seq;
    data.by = by;
    strcpy_s(data.name, _countof(data.name), name.c_str());
    data.guid = guid;

    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

////////////////////////////////////////////////////////////////////////////////

uint32_t LuaHost::AddScheduled(/*uint32_t id, */const std::string& name, uint16_t type, const CLuaObject& scheduled, const std::string& callBack, const std::string& params)
{
    SAFE_BEGIN_EX;

    std::vector<std::string> vec;
    for (luabind::iterator it(scheduled), end; it != end; ++it)
    {
        auto obj = *it;
        if (luabind::type(obj) != LUA_TSTRING) return 0;

        auto value = luabind::object_cast<std::string>(obj);
        vec.push_back(std::move(value));
    }
    if (vec.empty() || callBack.empty()) return 0;

    ScheduledPtr ptr = IScheduledHelper::GetInstance()->AddScheduled(type, name, vec, params, callBack);
    if (ptr) return ptr->GetId();

    return 0;
    SAFE_END_EX(0);
}

uint32_t LuaHost::AddLuaTimer(const std::string& Guid, uint32_t interval, bool loop, const std::string &callBack)
{
    SAFE_BEGIN_EX;

    if ("" == Guid || callBack.empty()) return 0;
    auto guid = stoull(Guid);
    if (IS_ROLE_GUID(guid)) {
        auto* role = GetRole(Guid);
        if (!role) return 0;

        return role->AddLuaTimer(interval, loop, callBack);
    }
    else if (IS_MAP_GUID(guid)) {
        auto* map = GetMap(Guid);
        if (!map) return 0;

        return map->AddLuaTimer(interval, loop, callBack);
    }
    else {

        auto id = ITimeHelper::GetInstance()->AddTimer(interval, loop, [=](const TimerData &timer) {
            if (!callBack.empty()) {
                LuaBindCallVoid(callBack, timer.id);
            }
        });

        return id;
    }
    
    SAFE_END_EX(0);
}

uint32_t LuaHost::AddLuaTimerEx(const std::string& Guid, uint32_t interval, bool loop, CLuaObject callBack)
{
    SAFE_BEGIN_EX;

    if ("" == Guid) return 0;
    auto guid = stoull(Guid);
    if (IS_ROLE_GUID(guid)) {
        auto* role = GetRole(Guid);
        if (!role) return 0;

        return role->AddLuaTimerEx(interval, loop, callBack);
    }
    else if (IS_MAP_GUID(guid)) {
        auto* map = GetMap(Guid);
        if (!map) return 0;

        return map->AddLuaTimerEx(interval, loop, callBack);
    }
    else {

        auto id = ITimeHelper::GetInstance()->AddTimer(interval, loop, [=](const TimerData &timer) {
            if (callBack.is_valid()) {
                LuaBindCallExVoid(callBack, timer.id);
            }
        });

        return id;
    }
    
    SAFE_END_EX(0);
}

void LuaHost::RemoveLuaTimer(const std::string& Guid, uint32_t timerID)
{
    SAFE_BEGIN;

    if ("" == Guid) return;
    auto guid = stoull(Guid);
    if (IS_ROLE_GUID(guid)) {
        auto* role = GetRole(Guid);
        if (!role) return;

        role->RemoveLuaTimer(timerID);
    }
    else if (IS_MAP_GUID(guid)) {
        auto* map = GetMap(Guid);
        if (!map) return;

        map->RemoveLuaTimer(timerID);
    }
    else {

        ITimeHelper::GetInstance()->RemoveTimer(timerID);
    }

    SAFE_END;
}

void LuaHost::AddNumData(uint32_t timerID, const std::string& key, uint32_t val)
{
    auto *timer = ITimeHelper::GetInstance();
    if (!timer) return;

    timer->AddNumData(timerID, key, val);
}

uint32_t LuaHost::GetNumData(uint32_t timerID, const std::string& key)
{
    auto *timer = ITimeHelper::GetInstance();
    if (!timer) return 0;

    return timer->GetNumData(timerID, key);
}

void LuaHost::RemoveNumData(uint32_t timerID, const std::string& key)
{
    auto *timer = ITimeHelper::GetInstance();
    if (!timer) return;

    timer->RemoveNumData(timerID, key);
}

void LuaHost::AddStrData(uint32_t timerID, const std::string& key, const std::string& val)
{
    auto *timer = ITimeHelper::GetInstance();
    if (!timer) return;

    timer->AddStrData(timerID, key, val);
}

std::string LuaHost::GetStrData(uint32_t timerID, const std::string& key)
{
    auto *timer = ITimeHelper::GetInstance();
    if (!timer) return "";

    return timer->GetStrData(timerID, key);
}

void LuaHost::RemoveStrData(uint32_t timerID, const std::string& key)
{
    auto *timer = ITimeHelper::GetInstance();
    if (!timer) return;

    timer->RemoveStrData(timerID, key);
}

int LuaHost::AddMailByName(const std::string& Rolename, const std::string& title, const std::string& text, const CLuaObject& additions, const CLuaObject& currency, uint8_t type)
{
    SAFE_BEGIN_EX;
    MSG_BUFFER_DATA(ProtoMS_AddSysNewMail, data);
    int err = MailMgr::ParseParamsByLua(Rolename, 0, ProtoMS_AddSysNewMail::add_type_by_name, title, text, additions, currency, type, data);
    if (err != ERR_OK){
        return err;
    }
    return MailMgr::AddMailSys2Player(data);
    SAFE_END_EX(0);
}

int LuaHost::AddMailByGuid(const std::string& Guid, const std::string& title, const std::string& text, const CLuaObject& additions, const CLuaObject& currency, uint8_t type)
{
    SAFE_BEGIN_EX;
    MSG_BUFFER_DATA(ProtoMS_AddSysNewMail, data);
    int err = MailMgr::ParseParamsByLua("", std::stoull(Guid), ProtoMS_AddSysNewMail::add_type_by_guid, title, text, additions, currency, type, data);
    if (err != ERR_OK) {
        return err;
    }
    return MailMgr::AddMailSys2Player(data);
    SAFE_END_EX(0);
}

CLuaObject LuaHost::GetAllOnlinePlayerGuid()
{
    SAFE_BEGIN_EX;
    return MapRoleMgr::GetInstance()->GetAllOnlinePlayerGuid();
    SAFE_END_EX(NewLuaObj());
}

void LuaHost::RunLuaScriptEveryOnlinePlayer(const std::string& scriptName, const std::string& params)
{
    SAFE_BEGIN;
    if (scriptName.empty()) return;
    auto &playermap = MapRoleMgr::GetInstance()->GetPlayerMap();
    for (auto& i : playermap)
    {
        LuaBindCallVoid(scriptName, std::to_string(i.first) , params);
    }
    SAFE_END;
}

std::string LuaHost::SimpleArithmetic(const std::string& lhs, const std::string& rhs, int type)
{
    SAFE_BEGIN_EX
    int64_t result = 0;
    switch (type)
    {
    case simple_Arithmetic_add:
        result = std::stoll(lhs) + std::stoll(rhs);
        break;
    case simple_Arithmetic_subtract:
        result = std::stoll(lhs) - std::stoll(rhs);
        break;
    case simple_Arithmetic_multiply:
        result = std::stoll(lhs) * std::stoll(rhs);
        break;
    case simple_Arithmetic_divide:
        result = std::stoll(lhs) / std::stoll(rhs);
        break;
    default:
        return "";
    }
    return std::to_string(result);
    SAFE_END_EX("")
}

void LuaHost::SetFormAllowFunc(const CLuaObject &allowFuncs)
{
    SAFE_BEGIN;
    for (luabind::iterator it(allowFuncs), end; it != end; ++it) {
        auto luaObjFuncName = *it;
        if (luabind::type(luaObjFuncName) != LUA_TSTRING) continue;
        auto funcName = luabind::object_cast<std::string>(luaObjFuncName);
        mRunServScriptAllowedFuncs.insert(std::move(funcName));
    }
    SAFE_END;
}

bool LuaHost::IsRunServScriptAllowedFunc(const std::string &func)
{
    return mRunServScriptAllowedFuncs.find(func) != mRunServScriptAllowedFuncs.end();
}

void LuaHost::SetCallBackUpdateAttr32(const CLuaObject& allowFuncs)
{
    SAFE_BEGIN;
    for (luabind::iterator it(allowFuncs), end; it != end; ++it) {
        auto luaObjAttrType32 = *it;
        if (luabind::type(luaObjAttrType32) != LUA_TNUMBER) continue;
        auto attrType32 = luabind::object_cast<int32_t>(luaObjAttrType32);
        if (attrType32 <= role_attr_min || attrType32 >= role_attr_max) continue;

        mCallBackUpdateAttrs32.insert(attrType32);
    }
    SAFE_END;
}

void LuaHost::SetCallBackUpdateAttr64(const CLuaObject& allowFuncs)
{
    SAFE_BEGIN;
    for (luabind::iterator it(allowFuncs), end; it != end; ++it) {
        auto luaObjAttrType64 = *it;
        if (luabind::type(luaObjAttrType64) != LUA_TNUMBER) continue;
        auto attrType64 = luabind::object_cast<int32_t>(luaObjAttrType64);
        if (attrType64 < role_attr_ext_min || attrType64 > role_attr_ext_max) continue;

        mCallBackUpdateAttrs64.insert(attrType64);
    }
    SAFE_END;
}

bool LuaHost::IsCallBackUpdateAttr(int32_t attrType, bool beAttr32)
{
    return beAttr32 ? mCallBackUpdateAttrs32.find(attrType) != mCallBackUpdateAttrs32.end() :
        mCallBackUpdateAttrs64.find(attrType) != mCallBackUpdateAttrs64.end();
}

void LuaHost::SendChatMsg(const CLuaObject& params)
{
    SAFE_BEGIN;
    auto &info = gMESSAGE_INFO;
    info.Clear();
    const auto &_msgType = params[1];
    if (luabind::type(_msgType) != LUA_TNUMBER) return;
    info.type = luabind::object_cast<int32_t>(_msgType);

    const auto& _context= params[2];
    if (luabind::type(_context) != LUA_TSTRING) return;
    auto msg = luabind::object_cast<std::string>(_context);

    const auto& _font_color = params[3];
    if (luabind::type(_font_color) != LUA_TSTRING) return;
    strcpy_s(info.font_color, _countof(info.font_color), luabind::object_cast<std::string>(_font_color));

    const auto& _background_color = params[4];
    if (luabind::type(_background_color) != LUA_TSTRING) return;
    strcpy_s(info.background_color, _countof(info.background_color), luabind::object_cast<std::string>(_background_color));

    const auto& _srcGuid = params[5];
    if (luabind::type(_srcGuid) != LUA_TSTRING) return;
    auto srcGuid = luabind::object_cast<std::string>(_srcGuid);
    if (strcmp(srcGuid.c_str(), "") != 0) {
        info.srcGuid = std::stoull(srcGuid);
    }
    
    const auto& _dstGuid = params[6];
    if (luabind::type(_dstGuid) != LUA_TSTRING) return;
    auto dstGuid = luabind::object_cast<std::string>(_dstGuid);
    if (strcmp(dstGuid.c_str(), "") != 0) {
        info.dstGuid = std::stoull(dstGuid);
    }

    const auto& _isAppearSrcName = params[7];
    if (luabind::type(_isAppearSrcName) != LUA_TNUMBER) return;
    info.isAppearSrcName = luabind::object_cast<uint8_t>(_isAppearSrcName);

    const auto& _posx = params[8];
    if (luabind::type(_posx) != LUA_TNUMBER) return;
    info.posx = luabind::object_cast<uint16_t>(_posx);

    const auto& _posy = params[9];
    if (luabind::type(_posy) != LUA_TNUMBER) return;
    info.posy = luabind::object_cast<uint16_t>(_posy);

    const auto& _scroll_times = params[10];
    if (luabind::type(_scroll_times) != LUA_TNUMBER) return;
    info.scroll_times = luabind::object_cast<uint16_t>(_scroll_times);

    const auto& _comp = params[11];
    if (luabind::type(_comp) != LUA_TNUMBER) return;
    info.comp = luabind::object_cast<uint16_t>(_comp);

    const auto& marqueeType = params["type"];
    if(luabind::type(marqueeType) == LUA_TNUMBER){
        info.marqueeType = luabind::object_cast<uint16_t>(marqueeType);
    }


    // 脚本需要时添加 display_type 暂不添加
    uLongf nDstLen = _countof(info.message);
    if (info.comp){
        auto result = compress((Bytef*)info.message, &nDstLen, (const Bytef*)msg.c_str(), msg.size());
        if (result != Z_OK) {
            LOG_ERROR("SendRelationChatNtf failed ,compress failed with error, %d", result);
            return;
        }
        info.size = nDstLen;
    }
    else {
        strcpy_s(info.message, nDstLen, msg.c_str());
        info.size = nDstLen;
    }

    switch (info.type)
    {
    case lua_chat_msg_dialog_current:
    case lua_chat_msg_dialog_team:
    case lua_chat_msg_dialog_guild:
    case lua_chat_msg_dialog_world:
    case lua_chat_msg_dialog_trumpt:
    case lua_chat_msg_dialog_camp:
    case lua_chat_msg_dialog_whole:
    {
        auto player = MapRoleMgr::GetInstance()->FindPlayer(info.dstGuid);
        if (player){
            player->SendRelationChatNtf(info);
        }
        break;
    }
    case lua_chat_msg_dialog_sys_all:
    {
        auto &playermap = MapRoleMgr::GetInstance()->GetPlayerMap();
        for (auto& i : playermap){
            if (i.second){
                i.second->SendSysMsgNtf2(info,true);
                break;
            }
        }
        break;
    }
    case lua_chat_msg_dialog_sys_map:
    {
        auto map = MapMgr::GetInstance()->FindMapByGUID(info.dstGuid);
        if (map){
            map->SendSysMsgNtf2AllRole(info);
        }
        break;
    }
    case lua_chat_msg_dialog_sys_region:
    {
        auto map = MapMgr::GetInstance()->FindMapByGUID(info.dstGuid);
        if (map){
            map->SendSysMsgNtf2AllRoleInAroundRegion(info);
        }
        break;
    }
    case lua_chat_msg_dialog_sys_single:
    {
        auto player = MapRoleMgr::GetInstance()->FindPlayer(info.dstGuid);
        if (player){
            player->SendSysMsgNtf2(info);
        }
        break;
    }
    case lua_chat_msg_scene_appear_all:
    {
        auto &playermap = MapRoleMgr::GetInstance()->GetPlayerMap();
        for (auto& i : playermap){
            if (i.second){
                i.second->SendSceneDialogNtf(info);
            }
        }
        break;
    }
    case lua_chat_msg_scene_appear_map:
    {
        auto map = MapMgr::GetInstance()->FindMapByGUID(info.dstGuid);
        if (map){
            map->SendSceneDialogNtfAllRole(info);
        }
        break;
    }
    case lua_chat_msg_scene_appear_region:
    {
        auto map = MapMgr::GetInstance()->FindMapByGUID(info.dstGuid);
        if (map){
            map->SendSceneDialogNtfAllRoleInAroundRegion(info);
        }
        break;
    }
    case lua_chat_msg_scene_appear_single:
    {
        auto player = MapRoleMgr::GetInstance()->FindPlayer(info.dstGuid);
        if (player){
            player->SendSceneDialogNtf(info);
        }
        break;
    }
    case lua_chat_msg_scroll_text_all:
    {
        auto &playermap = MapRoleMgr::GetInstance()->GetPlayerMap();
        for (auto& i : playermap){
            if (i.second){
                i.second->SendScrollText(info,true);
                break;
            }
        }
        break;
    }
    case lua_chat_msg_scroll_text_map:
    {
        auto map = MapMgr::GetInstance()->FindMapByGUID(info.dstGuid);
        if (map){
            map->SendScrollTextAllRole(info);
        }
        break;
    }
    case lua_chat_msg_scroll_text_region:
    {
        auto map = MapMgr::GetInstance()->FindMapByGUID(info.dstGuid);
        if (map){
            map->SendScrollTextAllRoleInAroundRegion(info);
        }
        break;
    }
    case lua_chat_msg_scroll_text_single:
    {
        auto player = MapRoleMgr::GetInstance()->FindPlayer(info.dstGuid);
        if (player){
            player->SendScrollText(info);
        }
        break;
    }
    default:
        break;
    }

    SAFE_END
}

CLuaObject LuaHost::GetCustListInfoByType(int type)
{
    SAFE_BEGIN_EX
    auto table = NewLuaObj();
    CustListMgr::GetInstance()->GetCustListByType(type, table);
    return table;
    SAFE_END_EX(NewLuaObj());
}

void LuaHost::Auction_AddItemInfo(const CLuaObject& info)
{
    SAFE_BEGIN
    AuctionHouse::GetInstance()->AddAuctionItemInfo(info);
    SAFE_END
}

bool LuaHost::Auction_OfferPrice(const std::string& guid, const std::string& orderID, int price)
{
    SAFE_BEGIN_EX
    return AuctionHouse::GetInstance()->OfferPrice(guid, orderID, price);
    SAFE_END_EX(false)
}

void LuaHost::Auction_GetFinishedItemTable(const std::string& func,uint32_t few_time_ago)
{
    SAFE_BEGIN
    ProtoMS_AuctionGetFinishedInfoReq data;
    strcpy_s(data.func, _countof(data.func), func.c_str());
    data.time = few_time_ago;
    SendDataBySessionType(SESSION_TYPE_MS2CS,data);
    SAFE_END
}

////////////////////////////////////////////////////////////////////////////////

void LuaHost::AddTrigger(const std::string& objGUID, uint32_t eventID, const::std::string& callBack)
{
    auto *lualib = CLuaLib::GetInstance();
    if (!lualib) return;

    lualib->AddTrigger(objGUID, eventID, callBack);
}

void LuaHost::RemoveTrigger(const std::string& objGUID, uint32_t eventID, const::std::string& callBack)
{
    auto *lualib = CLuaLib::GetInstance();
    if (!lualib) return;

    lualib->RemoveTrigger(objGUID, eventID, callBack);
}

////////////////////////////////////////////////////////////////////////////////
//
// MapMgr export functions
//

std::string LuaHost::MapMgr_CreateMap(const std::string &keyName)
{
    auto *mapMgr = MapMgr::GetInstance();
    if (!mapMgr) return "";

    auto *map = mapMgr->CreateMap(keyName);
    if (!map) return "";

    return map->GetGUIDAsString();
}

void LuaHost::MapMgr_DestroyMap(const std::string& mapName)
{
    auto* mapMgr = MapMgr::GetInstance();
    if (!mapMgr) return;

    mapMgr->DestroyMap(mapName);
}
std::string LuaHost::MapMgr_FindMap(const std::string& mapName)
{
    auto* mapMgr = MapMgr::GetInstance();
    if (!mapMgr) return "";

    auto* map = mapMgr->FindMap(mapName);
    if (!map) return "";

    return map->GetGUIDAsString();
}

std::string LuaHost::MapMgr_CreateMulDgnMap(const std::string& sDgnMapName, const std::string& sPlayerGuid, bool delayInit, uint32_t exitTime, CLuaObject call_back)
{
    auto* mapMgr = MapMgr::GetInstance();
    if (!mapMgr) return "";
    
    return mapMgr->CreateMulDgnMap(sDgnMapName, sPlayerGuid, delayInit, exitTime, call_back);
}

uint32_t LuaHost::MapMgr_DestroyMulDgnMap(const std::string& sDgnMapGuid)
{
    auto* mapMgr = MapMgr::GetInstance();
    if (!mapMgr) return 1000;

    return mapMgr->DestroyMulDgnMap(sDgnMapGuid);
}

uint32_t LuaHost::MapMgr_BindMulDgnGuidWithPlayerGuid(const std::string& sDgnMapGuid, const std::string& sPlayerGuid)
{
    auto* mapMgr = MapMgr::GetInstance();
    if (!mapMgr) return 1000;

    return mapMgr->BindMulDgnGuidWithPlayerGuid(sDgnMapGuid, sPlayerGuid);
}

uint32_t LuaHost::MapMgr_UnBindMulDgnGuidWithPlayerGuid(const std::string& sDgnMapName, const std::string& sPlayerGuid)
{
    auto* mapMgr = MapMgr::GetInstance();
    if (!mapMgr) return 1000;

    return mapMgr->UnBindMulDgnGuidWithPlayerGuid(sDgnMapName, sPlayerGuid);
}

uint32_t LuaHost::MapMgr_EnteryMulDgnMap(const std::string& sDgnMapName, const std::string& sPlayerGuid, uint16_t posX, uint16_t posY, const CLuaObject& edlogInfo)
{
    auto* mapMgr = MapMgr::GetInstance();
    if (!mapMgr) return 1000;

    return mapMgr->EnteryMulDgnMap(sDgnMapName, sPlayerGuid, posX, posY, ParseEDLogParams(edlogInfo));
}

uint32_t LuaHost::MapMgr_ExitMulDgnMap(const std::string& sDgnMapGuid, const std::string& sPlayerGuid)
{
    auto* mapMgr = MapMgr::GetInstance();
    if (!mapMgr) return 1000;

    return mapMgr->ExitMulDgnMap(sDgnMapGuid, sPlayerGuid);
}

std::string LuaHost::MapMgr_GetMulDgnGuidByPlayerGuid(const std::string& sDgnMapName, const std::string& sPlayerGuid)
{
    auto* mapMgr = MapMgr::GetInstance();
    if (!mapMgr) return "";

    return mapMgr->GetMulDgnGuidByPlayerGuid(sDgnMapName, sPlayerGuid);
}

////////////////////////////////////////////////////////////////////////////////
//
// Map export functions
//

int LuaHost::Map_GetID(const std::string & mapGuid)
{
    auto* map = GetMap(mapGuid);
    if (!map) return -1;

    return map->GetTemplateID();
}

bool LuaHost::Map_IsThisMapGridType(const std::string& mapGuid, uint16_t posX, uint16_t posY, int type)
{
    SAFE_BEGIN_EX
    auto* map = GetMap(mapGuid);
    if (!map) return false;
    return map->IsTypeRegion(posX, posY, type);
    SAFE_END_EX(false)
}

void LuaHost::Map_AddJumpPoint(const std::string& from_guid, const std::string& to_guid, uint16_t from_x, uint16_t from_y, uint16_t to_x, uint16_t to_y, uint32_t enterEffect, uint32_t leaveEffect)
{
    SAFE_BEGIN
    auto* map = GetMap(from_guid);
    if (!map) return ;
    map->AddJumpPoint(from_guid, to_guid, from_x, from_y, to_x, to_y, enterEffect, leaveEffect);
    SAFE_END
}

void LuaHost::Map_DelJumpPoint(const std::string& guid, uint16_t x, uint16_t y)
{
    SAFE_BEGIN
    auto* map = GetMap(guid);
    if (!map) return ;
    map->DelJumpPoint(guid, x, y);
    SAFE_END
}

CLuaObject LuaHost::Map_GetAllRoleByType(const std::string &mapGUID, uint8_t roleType)
{
    auto roles = NewLuaObj();

    SAFE_BEGIN_EX;
    auto *map = GetMap(mapGUID);
    if (!map) return roles;

    auto roleList = map->GetAllRoleByType(roleType);

    int i = 0;
    for (auto &role : roleList) {
        if (!role) continue;
        roles[++i] = role->GetGUIDAsString();
    }

    return roles;
    SAFE_END_EX(roles);
}

void LuaHost::Map_GetAllEmptyGrid(const std::string& mapguid, uint16_t x, uint16_t y, uint16_t rangeX, uint16_t rangeY)
{
    SAFE_BEGIN
    auto* map = GetMap(mapguid);
    if (!map) return;
    map->SendBlankGridTableToLua(x,y,rangeX,rangeY, blank_grid_normal);
    SAFE_END
}

void LuaHost::Map_GetAllCanDropItemGrid(const std::string& mapguid, uint16_t x, uint16_t y, uint16_t rangeX, uint16_t rangeY)
{
    SAFE_BEGIN
        auto* map = GetMap(mapguid);
    if (!map) return;
    map->SendBlankGridTableToLua(x, y, rangeX, rangeY, blank_grid_drop);
    SAFE_END
}

void LuaHost::Map_DisappearMonsterCorpseInPoint(const std::string& mapguid, uint16_t x, uint16_t y)
{
    SAFE_BEGIN
    auto* map = GetMap(mapguid);
    if (!map) return;
    map->DisappearMonsterCorpseInPoint(x, y);
    SAFE_END
}

bool LuaHost::Map_GetBossInfo(const std::string& MapKey)
{
    SAFE_BEGIN_EX
    auto mapCfg = sMapConfig.GetByKeyName(MapKey);
    if (!mapCfg)return false;
    std::vector<BossInfo> vec;
    BossInfoMgr::GetInstance()->GetBossInfoByMapID(mapCfg->Id, vec);
    auto list = NewLuaObj();
    int idx = 1;
    for (auto& i : vec) {
        auto table = NewLuaObj();
        auto cfg = sMonsterConfig.GetByID(i.tempID);
        if (!cfg)continue;
        table[1] = i.mapName;
        table[2] = cfg->KeyName;
        table[3] = to_string(i.reliveTime);
        list[idx++] = table;
    }
    LuaRet = list;
    return true;
    SAFE_END_EX(false)
}

////////////////////////////////////////////////////////////////////////////////
//
// Player export functions
//
inline Player* LuaHost::GetPlayerByGuid(const std::string& guid)
{
    SAFE_BEGIN_EX
    if (guid.empty()) return nullptr;

    auto* mapRoleMgr = MapRoleMgr::GetInstance();
    if (!mapRoleMgr) return nullptr;

    auto id = std::stoull(guid);
    return mapRoleMgr->FindPlayer(id);
    SAFE_END_EX(nullptr)
}

bool LuaHost::Player_IsSupport(const std::string& guid)
{
    SAFE_BEGIN_EX
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return false;

    return player->IsSupport();
    SAFE_END_EX(false)
}

// ok
void LuaHost::Player_SendItemDestroyAck(const std::string& guid)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;

    player->SendDestroyItem(std::stoull(guid));
}

// ok
void LuaHost::Player_SendPlayerReliveNtf(const std::string& guid, const std::string& MapName, int hp, int mp, int x, int y)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;
    player->SendPlayerReliveNtf(MapName,2, hp, mp, x, y);
}

// ok
void LuaHost::Player_SendPlayerShowNtf(const std::string& guid, int hp, int mp)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;

    player->SendPlayerShowNtf(hp, mp);
}

void LuaHost::Player_SendRoleAttrExtRefNtf(const std::string &guid, uint16_t attr, int delta)
{
    auto *player = GetPlayerByGuid(guid);
    if (!player) return;

    player->SendRoleAttrExtRefNtfToGS(attr, delta);
}

// ok
bool LuaHost::Player_AddPlayerItem(const std::string& guid, uint16_t tempid, const CLuaObject& logInfo)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return false;

    return player->AddPlayerItem(tempid, ParseLogParams(logInfo));
}
// ok
void LuaHost::Player_AddPlayerExperience(const std::string& guid, int64_t exp, const CLuaObject& logInfo)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;

    player->AddPlayerExperience(exp, ParseLogParams(logInfo));
}
// ok
void LuaHost::Player_AddPlayerGold(const std::string& guid, uint64_t goldid, const CLuaObject& logInfo)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;

    player->AddPlayerGold(goldid, ParseLogParams(logInfo));
}
// ok
void LuaHost::Player_RunClientScript(const std::string& guid, const std::string& sScriptName, const std::string& sContent, bool bCompress)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;

    player->RunClientScript(sScriptName.c_str(), sContent.c_str(), bCompress);
}

void LuaHost::Player_RunClientScript_plus(const std::string& guid, const std::string& sScriptName, const std::string& sContent, bool bCompress, uint16_t type)
{
    switch (type)
    {
    case 0:
        {
            auto* player = GetPlayerByGuid(guid);
            if (nullptr == player) return;

            player->RunClientScript_Around(sScriptName.c_str(), sContent.c_str(), bCompress);
        }
        break;
    case 1:
        {
            auto* map = GetMap(guid);
            if (!map) return;

            map->RunClientScript(sScriptName.c_str(), sContent.c_str(), bCompress);
        }
        break;
    case 2:
        {
            MapServer::GetInstance()->RunClientScript(sScriptName.c_str(), sContent.c_str(), bCompress);
        }
        break;

    default:
        break;
    }
    
}
std::string LuaHost::_LuaSerialize(const CLuaObject& luaObj, std::string& str)
{
    if (luabind::type(luaObj) == LUA_TNUMBER)
    {
        auto  num = luabind::object_cast<int>(luaObj);
        str += to_string(num);
    }
    else if (luabind::type(luaObj) == LUA_TBOOLEAN)
    {
        auto  num = luabind::object_cast<bool>(luaObj);
        str += to_string(num);

    }
    else if(luabind::type(luaObj) == LUA_TSTRING)
    {
        auto strKey = luabind::object_cast<string>(luaObj);
        str += "\""+strKey + "\"";
    }
    else if (luabind::type(luaObj) == LUA_TTABLE)
    {
        str += "{\n";

        auto m_LuaValType = LUA_TTABLE;
        auto m_pTable = new CLuaTable;

        string strKey = "";
        string strVal = "";
        int iKey = 0;
        double dVal = 0;

        luabind::iterator iter(luaObj), end;
        for (; iter != end; iter++) {
            luabind::adl::object objKey = iter.key();
            luabind::adl::object objVal = *iter;
            if (objKey && objVal)
            {
                str += "[";
                _LuaSerialize(objKey, str);
                str += "]=";
                _LuaSerialize(objVal, str);
                str += ",\n";
            }
        }
        //getmetatable   static_class_gettable
        /*auto metatable = luabind::getmetatable(luaObj);
        if (metatable && luabind::type(metatable) == LUA_TTABLE)
        {
            luabind::iterator iter(metatable), end;
            for (; iter != end; iter++) {
                luabind::adl::object objKey = iter.key();
            luabind::adl::object objVal = *iter;
            if (objKey && objVal)
            {
                str += "[";
                _LuaSerialize(objKey, str);
                str += "]=";
                _LuaSerialize(objVal, str);
                str += ",\n";
            }
         }*/
        str += "}";
    }
    else if (luabind::type(luaObj) == LUA_TNIL)
    {
        return str;
    }
    return str;
}

std::string LuaHost::LuaSerialize(const CLuaObject& luaObj)
{
    std::string str;
    _LuaSerialize(luaObj,str);
    return str;
}


bool LuaHost::IsWin32()
{
#ifdef _WIN32
    return true;
#else
    return false;
#endif
}

// ok
void LuaHost::Player_NotifyPlayer_StartMove(const std::string& guid, uint16_t nDstX, uint16_t nDstY)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;

    player->NotifyPlayer_StartMove(nDstX, nDstY);
}
// ok
void LuaHost::Player_SendErrorAck(const std::string& guid, int32_t type, const char* errMsg)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;

    player->SendErrorAck(type, errMsg);
}
// ok

void LuaHost::Player_SendPopDlgMsgNtf(const std::string &guid, const std::string &msg)
{
    auto *player = GetPlayerByGuid(guid);
    if (!player) return;

    player->SendPopDlgMsgNtf(msg);
}

void LuaHost::Player_SendPlayerFamilyChangeNtf(const std::string &guid, const std::string &msg)
{
    auto *player = GetPlayerByGuid(guid);
    if (!player) return;

    player->GetGuildDataMgr().SendPlayerFamilyChangeNtfToGS(msg);
}

// ok
void LuaHost::Player_Jump(const std::string& guid, const std::string& mapName)
{
    Player_JumpWithType(guid, mapName, (uint16_t)jump_map_type::default_type_null);
}

// ok
bool LuaHost::Player_JumpMap(const std::string& guid, const std::string& mapName, uint16_t posX, uint16_t posY)
{
    return Player_JumpMapWithType(guid, mapName, posX, posY, (uint16_t)jump_map_type::default_type_null);
}

// ok
void LuaHost::Player_JumpWithType(const std::string& guid, const std::string& mapName, uint16_t type)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;

    Map* tarMap = MapMgr::GetInstance()->FindMap(mapName);
    if (nullptr == tarMap) {
        LOG_ERROR("tar map instance not exist. mapName:%s", mapName.c_str());
        return;
    }

    auto width = tarMap->GetWidth();
    auto height = tarMap->GetHeight();

    uint16_t x, y;
    if (!tarMap->GetRandBlankPointInRange(0, 0, width, height, x, y)) {
        LOG_ERROR("GetRandBlankPointInRange failed. mapName: %s", mapName.c_str());
        return;
    }

    if (!player->JumpMap(mapName, x, y, type)) {
        LOG_ERROR("JumpMap failed");
    }
}

// ok
bool LuaHost::Player_JumpMapWithType(const std::string& guid, const std::string& mapName, uint16_t posX, uint16_t posY, uint16_t type)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return false;

    if (!mapName.empty()) return player->JumpMap(mapName, posX, posY, type);

    auto *map = player->GetCurMap();
    if (!map) return false;
    return player->JumpMap(map->GetName(), posX, posY, type);
}
// ok
std::string LuaHost::Player_SummonMonsterByID(const std::string& guid, uint16_t monsterID)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return "";

    auto* monster = player->GetSummonMonsterMgr().SummonMonsterByID(monsterID);
    if (nullptr == monster) return "";

    return monster->GetGUIDAsString();
}

// ok
std::string LuaHost::Player_SummonMonsterByName(const std::string& guid, const std::string& monsterName)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return "";

    auto* monster = player->GetSummonMonsterMgr().SummonMonsterByName(monsterName);
    if (nullptr == monster) return "";

    return monster->GetGUIDAsString();
}
// ok
void LuaHost::Player_DestroySummonMonster(const std::string& guid, const std::string& sMonsterGUID)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;

    uint64_t monsterGuid = std::stoull(sMonsterGUID);
    player->GetSummonMonsterMgr().SummonMonsterLeaveMap(monsterGuid);
    if (monsterGuid == 0)
        player->GetSummonMonsterMgr().DestroySummonMonster();
    else
        player->GetSummonMonsterMgr().DestroySummonMonster(monsterGuid);
}

std::string LuaHost::Player_PetMonsterByID(const std::string& guid, uint16_t monsterid)
{
    SAFE_BEGIN_EX
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return "";

    auto* pet = player->GetPetMgr().PetMonsterByID(monsterid);
    if (nullptr == pet) return "";

    return pet->GetGUIDAsString();
    SAFE_END_EX("");
}

std::string LuaHost::Player_PetMonsterByName(const std::string& guid, const std::string& monsterName)
{
    SAFE_BEGIN_EX
        auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return "";

    auto* pet = player->GetPetMgr().PetMonsterByName(monsterName);
    if (nullptr == pet) return "";

    return pet->GetGUIDAsString();
    SAFE_END_EX("");
}

std::string LuaHost::Player_PetMonsterIDByAttrTable(const std::string& guid, uint16_t nTemplateID, const CLuaObject& luaObj)
{
    SAFE_BEGIN_EX
        auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return "";
    auto* pet = player->GetPetMgr().PetMonsterByIDByLuaTable(nTemplateID,luaObj);
    if (nullptr == pet) return "";

    return pet->GetGUIDAsString();
    SAFE_END_EX("");
}

std::string LuaHost::Player_PetMonsterNameByAttrTable(const std::string& guid, const std::string& name, const CLuaObject& luaObj)
{
    SAFE_BEGIN_EX
        auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return "";
    auto* pet = player->GetPetMgr().PetMonsterByNameByLuaTable(name, luaObj);
    if (nullptr == pet) return "";

    return pet->GetGUIDAsString();
    SAFE_END_EX("");
}

CLuaObject LuaHost::Player_GetPetList(const std::string& guid)
{
    SAFE_BEGIN_EX
    CLuaObject obj = NewLuaObj();
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return obj;

    auto list = player->GetPetMgr().GetPetList();
    int idx = 1;
    for (auto& i : list)
    {
        obj[idx] = std::to_string(i);
        ++idx;
    }
    return obj;
    SAFE_END_EX(NewLuaObj());
}

void LuaHost::Player_DestroyPetMonster(const std::string& guid, const std::string& petguid)
{
    SAFE_BEGIN
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;
    player->GetPetMgr().PetLeaveMap(std::stoull(petguid));
    player->GetPetMgr().DestroyPet(petguid);
    SAFE_END
}

void LuaHost::Player_DestroyAllPetMonster(const std::string& guid)
{
    SAFE_BEGIN
        auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;
    player->GetPetMgr().PetLeaveMap();
    player->GetPetMgr().DestroyPet();
    SAFE_END
}

void LuaHost::Player_SetPetActivityStatus(const std::string& guid, const std::string& petguid, uint16_t status)
{
    SAFE_BEGIN
        auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;
    player->GetPetMgr().SetPetActivityStatus(petguid, status);
    SAFE_END
}

void LuaHost::Player_SetPetPickItemStatus(const std::string& guid, const std::string& petguid, bool canPick)
{
    SAFE_BEGIN
        auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;
    player->GetPetMgr().SetPetPickItemStatus(petguid, canPick);
    SAFE_END
}

// ok
std::string LuaHost::Player_GetSummonMonster(const std::string& guid, uint16_t nTemplateID)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return "";

    auto* monster = player->GetSummonMonsterMgr().GetSummonMonster(nTemplateID);
    if (nullptr == monster) return "";

    return monster->GetMasterGUIDAsString();
}
// ok
void LuaHost::Player_EnterShop(const std::string& guid, uint16_t nShopID)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;

    player->EnterShop(nShopID);
}
// ok1
int LuaHost::Player_EnterDgnMap(const std::string& guid, const std::string& sMapKeyName, const CLuaObject& edlogInfo)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return 1;

    return player->EnterDgnMap(sMapKeyName, ParseEDLogParams(edlogInfo));
}
// ok1
int LuaHost::Player_ExitDgnMap(const std::string& guid)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return 2;

    return player->ExitDgnMap();
}
// ok
bool LuaHost::Player_IsInDgnMap(const std::string& guid)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return false;

    return player->IsInDgnMap();
}
// ok
uint16_t LuaHost::Player_GetIdleBagCount(const std::string& guid)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return 0;

    return player->GetIdleBagCount();
}

uint16_t LuaHost::Player_GetBagFirstFreeSite(const std::string& guid)
{
    SAFE_BEGIN_EX
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return 0;

    return player->GetBagFirstFreeSite();
    SAFE_END_EX(0)
}
//ok
bool  LuaHost::Player_ItemMove(const std::string& guid, const std::string& itemguid, uint16_t site)
{
    SAFE_BEGIN_EX;
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return false;
    auto itemGuid = std::stoull(itemguid);
    return player->ItemMove(itemGuid,site);
    SAFE_END_EX(false);
}
// ok
int LuaHost::Player_AddItem(const std::string& guid, uint16_t nTemplateID, uint16_t nNum, uint8_t nBindRequire, uint8_t nSiteRange, const CLuaObject& logInfo)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return ERR_ITEM_NO_DATA_ROW;

    return player->AddItem(nTemplateID, nNum, nBindRequire, nSiteRange, ParseLogParams(logInfo));
}

std::string LuaHost::Player_AddSingleItem(const std::string& guid, uint16_t tempid, uint8_t nBindRequire, const CLuaObject& logInfo)
{
    SAFE_BEGIN_EX
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return "";

    auto itemguid = player->AddSingleItem(tempid, 1, nBindRequire , ParseLogParams(logInfo));
    if (!itemguid)return "";
    else return to_string(itemguid);
    SAFE_END_EX("")
}

// ok
int LuaHost::Player_AddItemByKeyName(const std::string& guid, const std::string& sKeyName, uint16_t nNum, uint8_t bBind, uint8_t nJob, const CLuaObject& logInfo)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return ERR_ITEM_NO_DATA_ROW;

    return player->AddItemByKeyName(sKeyName, nNum, bBind, nJob, ParseLogParams(logInfo));
}

// ok
int LuaHost::Player_AddItemByKeyNameToSite(const std::string& guid, const std::string& sKeyName, uint16_t nNum, uint8_t bBind, uint8_t nJob, uint16_t nSite, const CLuaObject& logInfo)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return ERR_ITEM_NO_DATA_ROW;

    return player->AddItemByKeyNameToSite(sKeyName, nNum, bBind, nJob, nSite, ParseLogParams(logInfo));
}

// ok
int LuaHost::Player_AddItems(const std::string& guid, const CLuaObject& luaObj, const CLuaObject& logInfo)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return ERR_ITEM_ADD;

    return player->AddItems(luaObj, ParseLogParams(logInfo));
}
// ok
int LuaHost::Player_RemoveItem(const std::string& guid, uint16_t nTemplateID, uint16_t nNum, uint8_t bindRequire, uint8_t nSiteRange, const CLuaObject& logInfo)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return ERR_ITEM_DESTROY;

    return player->RemoveItem(nTemplateID, nNum, bindRequire, nSiteRange, ParseLogParams(logInfo));
}
// ok
int LuaHost::Player_RemoveItemByGuid(const std::string& guid, const std::string& itemGuid, const CLuaObject& logInfo)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return ERR_ITEM_DESTROY;
    auto itemguid = std::stoull(itemGuid);
    auto rolePack = player->GetRolePack();
    if (!rolePack) return ERR_ITEM_DESTROY;
    auto* item = rolePack->FindItem(itemguid);
    if (!item) return ERR_ITEM_NOT_EXIST;
    auto itemAmount = item->GetAmount();

    return player->RemoveItem(itemguid, itemAmount, ParseLogParams(logInfo));
}

int LuaHost::Player_RemoveItemByGuid2(const std::string &playerGUID, const std::string &itemGUID,
                                      uint16_t num, const CLuaObject &logInfo)
{
    auto *player = GetPlayerByGuid(playerGUID);
    if (!player) return ERR_ITEM_DESTROY;
    auto itemguid = stoull_s(itemGUID);
    return player->RemoveItem(itemguid, num, ParseLogParams(logInfo));
}

int LuaHost::Player_RemoveItemByKeyName(const std::string& guid, const std::string& keyName, uint16_t nNum, uint8_t bindRequire, uint8_t nSiteRange, const CLuaObject& logInfo)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return ERR_ITEM_DESTROY;

    return player->RemoveItem(keyName, nNum, bindRequire, nSiteRange, ParseLogParams(logInfo));
}

int LuaHost::Player_RemoveAllItem(const std::string& guid, rolepack_opt_type type)
{
    SAFE_BEGIN_EX
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return ERR_ITEM_DESTROY;
    return player->GetRolePack()->RemoveAllItem(type);
    SAFE_END_EX(ERR_ITEM_DESTROY)
}
// ok
uint32_t LuaHost::Player_GetItemNum(const std::string& guid, uint16_t templateID, uint8_t bindRequire, uint8_t nSiteRange)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return 0;

    return player->GetItemNum(templateID, bindRequire, nSiteRange);
}
// ok
uint32_t LuaHost::Player_GetItemNumByKeyName(const std::string& guid, const std::string& keyName, uint8_t bindRequire, uint8_t nSiteRange)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return 0;

    return player->GetItemNumByKeyName(keyName, bindRequire, nSiteRange);
}

uint16_t LuaHost::Player_GetItemAmount(const std::string& guid, const std::string& itemguid)
{
    SAFE_BEGIN_EX
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return 0;

    auto item = player->GetRolePack()->FindItem(std::stoull(itemguid));
    if (item == nullptr)return 0;
    return item->GetAmount();
    SAFE_END_EX(0)
}

bool LuaHost::Player_SetItemAmount(const std::string& guid,const std::string& itemguid ,uint32_t num, const CLuaObject& logInfo)
{
    SAFE_BEGIN_EX
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return false;
    auto rolePack = player->GetRolePack();
    if (rolePack == nullptr)return false;

    return rolePack->SetAmount(itemguid, num, ParseLogParams(logInfo));
    SAFE_END_EX(false)
}

// ok
uint16_t LuaHost::Player_GetTeamMemNum(const std::string& guid)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return 0;

    return player->GetTeamDataMgr().GetTeamMemNum();
}
// ok
CLuaObject LuaHost::Player_GetTeamInfo(const std::string& guid)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return NewLuaObj();

    return player->GetTeamDataMgr().GetTeamInfo();
}

std::string LuaHost::Player_GetTeamGuid(const std::string& guid)
{
    SAFE_BEGIN_EX
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return "";

    return player->GetTeamDataMgr().GetTeamGuid();
    SAFE_END_EX("")
}
// ok
void LuaHost::Player_StartQuestDialog(const std::string& guid, const std::string& npcGuid, uint16_t nQuestID, uint8_t nState)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;

    auto* npc = GetNpcByGuid(npcGuid);
    if (nullptr == npc) return;

    player->GetQuestDataMgr().StartQuestDialog(npc, nQuestID, nState);
}
// ok
bool LuaHost::Player_IsDoingQuest(const std::string& guid)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return false;

    return player->GetQuestDataMgr().IsDoingQuest();
}
// ok
int LuaHost::Player_GetQuestState(const std::string& guid)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return quest_state_idle;

    return player->GetQuestDataMgr().GetQuestState();
}
// ok
CLuaObject LuaHost::Player_GetAcceptableQuests(const std::string& guid)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return NewLuaObj();

    return player->GetQuestDataMgr().GetAcceptableQuests();
}
// ok
uint16_t LuaHost::Player_GetCurQuestID(const std::string& guid)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return 0;

    return player->GetQuestDataMgr().GetCurQuestID();
}
// ok
uint16_t LuaHost::Player_GetPreQuestID(const std::string& guid)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return 0;

    return player->GetQuestDataMgr().GetPreQuestID();
}
// ok
void LuaHost::Player_TalkToNpc(const std::string& guid, const std::string& npcGuid, const std::string& dialog)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;

    auto* npc = GetNpcByGuid(npcGuid);
    if (nullptr == npc) return;

    player->TalkToNpc(npc, dialog);
}
// ok
int LuaHost::Player_CreateGuild(const std::string& guid, const std::string& guildName)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return ERR_UNKNOW;

    return player->GetGuildDataMgr().CreateGuild(guildName);
}
// ok
int LuaHost::Player_AddSkill(const std::string& guid, uint16_t skillID, bool active)
{
    auto *player = GetPlayerByGuid(guid);
    if (!player) return ERR_UNKNOW;
    return player->AddSkill(skillID, active);
}

void LuaHost::Player_DeleteSkill(const std::string& guid, uint16_t skillID, bool delAllInSameChain)
{
    SAFE_BEGIN
    auto *player = GetPlayerByGuid(guid);
    if (!player) return;

    if (!delAllInSameChain) {
        player->RemoveSkill(skillID);
        return;
    }

    auto *skillCfg = sSkillConfig.Get(skillID);
    if (!skillCfg) return;

    if (skillCfg->SkillChainID == 0) {
        player->RemoveSkill(skillID);
        return;
    }

    player->RemoveSkillByChainID(skillCfg->SkillChainID);
    SAFE_END
}

bool LuaHost::Player_SkillIsExist(const std::string& guid, uint16_t skillID, bool searchSkillChain)
{
    SAFE_BEGIN_EX
    auto *player = GetPlayerByGuid(guid);
    if (!player) return false;

    if (!searchSkillChain)
        return player->SkillIsExist(skillID);

    auto *skillCfg = sSkillConfig.Get(skillID);
    if (!skillCfg) return false;

    if (skillCfg->SkillChainID == 0)
        return player->SkillIsExist(skillID);

    auto *roleSkill = player->GetRoleSkill();
    if (!roleSkill) return false;

    return roleSkill->IsSkillExistByChainID(skillCfg->SkillChainID);
    SAFE_END_EX(false)
}

CLuaObject LuaHost::Player_GetSkillIDList(const std::string &guid)
{
    CLuaObject obj = NewLuaObj();

    auto *player = GetPlayerByGuid(guid);
    if (!player) return obj;

    auto skillIDList = player->GetSkillIDList();

    int i = 0;
    for (const auto &skillID : skillIDList) {
        obj[++i] = skillID;
    }

    return obj;
}

uint16_t LuaHost::Player_GetSkillIDByChainID(const std::string &guid, uint32_t chainID)
{
    auto *player = GetPlayerByGuid(guid);
    if (!player) return 0;

    auto *roleSkill = player->GetRoleSkill();
    if (!roleSkill) return 0;

    auto skillIDs = roleSkill->GetSkillIDsByChainID(chainID);
    return skillIDs.empty() ? 0 : skillIDs[0];
}

uint16_t LuaHost::Player_GetWarehouseFreeSize(const std::string& guid)
{
    auto* player = GetPlayerByGuid(guid);
    if (!player) return 0;

    return player->GetWarehouseFreeSize();
}

uint16_t LuaHost::Player_GetAdvWarehouseFreeSize(const std::string& guid)
{
    auto* player = GetPlayerByGuid(guid);
    if (!player) return 0;

    return player->GetAdvWarehouseFreeSize();
}

uint16_t LuaHost::Player_GetWarehouseFirstFreeSite(const std::string& guid)
{
    auto* player = GetPlayerByGuid(guid);
    if (!player) return 0;
    return player->GetWarehouseFirstFreeSite();
}
uint16_t LuaHost::Player_GetAdvWarehouseFirstFreeSite(const std::string& guid)
{
    auto* player = GetPlayerByGuid(guid);
    if (!player) return 0;
    return player->GetAdvWarehouseFirstFreeSite();
}

uint16_t LuaHost::Player_GetGmModLevel(const std::string& guid)
{
    SAFE_BEGIN_EX;
    auto* player = GetPlayerByGuid(guid);
    if (!player) return 0;
    return player->GetGmModLevel();
    SAFE_END_EX(0);
}

CLuaObject LuaHost::Player_GetVipExtePermissions(const std::string& guid)
{
    SAFE_BEGIN_EX
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return NewLuaObj();

    return player->GetVipExtePermissions();
    SAFE_END_EX(NewLuaObj())
}

bool LuaHost::Player_HasVipExtePermissions(const std::string& guid, int32_t permissions)
{
    SAFE_BEGIN_EX
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return false;

    return player->HasVipExtePermissions(permissions);
    SAFE_END_EX(false)
}

void LuaHost::Player_SendMsgNtf(const uint8_t type, const uint8_t site, const uint8_t foreground, const uint8_t background,
                                const std::string& msg, const std::string& guid, const uint8_t count)
{
    ProtoMS_MsgNtf ntf;
    ntf.background = background;
    ntf.foreground = foreground;
    ntf.count = count;
    strcpy_s(ntf.msg,_countof(ntf.msg), msg.c_str());
    ntf.site = site;
    auto funcntf= [&](Role* pRole) {

        if (!pRole || !pRole->IsPlayer()) return;

        auto pOtherPlayer = static_cast<Player*>(pRole);
        ntf.sessionid = pOtherPlayer->GetClSessionID();

        SendDataBySessionID(pOtherPlayer->GetGsSessionID(), ntf);       // 回NTF
    };
    switch (type) {
    case msg_type_own:
    {
        auto player = GetPlayerByGuid(guid);
        funcntf(player);
        break; 
    }
    case msg_type_all:
    {
        auto &playermap = MapRoleMgr::GetInstance()->GetPlayerMap();
        for (auto &tmp : playermap)
            funcntf(tmp.second);
        break;
    }
    case msg_type_guild:
    {
        if (guid.empty()) break;
        auto guildmember = GuildMgr::GetInstance()->GetMemberList(stoull(guid));
        if (nullptr == guildmember) break;

        for (auto &tmp : *guildmember)
            funcntf(GetPlayerByGuid(std::to_string(tmp->player_id)));
        break;
    }
    case msg_type_team:
    {
        if (guid.empty()) break;
        auto teammember = TeamMgr::GetInstance()->FindTeam(stoull(guid));
        if (nullptr == teammember)break;

        for (auto &tmp : teammember->mMemberList)
            funcntf(GetPlayerByGuid(std::to_string(tmp.guid)));
        break;
    }
    case msg_type_present:
    default: break;
    }
}

std::string LuaHost::Player_GetGuildGUID(const std::string &playerGUID)
{
    auto *player = GetPlayerByGuid(playerGUID);
    if (!player) return "";

    auto guildGUID = player->GetGuildDataMgr().GetGuildID();
    return std::to_string(guildGUID);
}

int LuaHost::Player_GetGuildMemberTitle(const std::string &guid)
{
    return Player_GetGuildMemberNewTitle(guid);
}

int LuaHost::Player_GetGuildMemberOldTitle(const std::string &guid)
{
    auto *player = GetPlayerByGuid(guid);
    if (!player) return guild_member_title_not_member;
    return player->GetGuildDataMgr().GetGuildMemberOldTitle();
}

int LuaHost::Player_GetGuildMemberNewTitle(const std::string &guid)
{
    auto *player = GetPlayerByGuid(guid);
    if (!player) return guild_member_title_not_member;
    return player->GetGuildDataMgr().GetGuildMemberNewTitle();
}

uint32_t LuaHost::Player_GetCurContrib(const std::string &playerGUID)
{
    auto *player = GetPlayerByGuid(playerGUID);
    if (!player) return 0;
    return player->GetGuildDataMgr().GetCurContrib();
}

std::string LuaHost::Player_GetGuildName(const std::string& guid)
{
    SAFE_BEGIN_EX
    auto* player = GetPlayerByGuid(guid);
    if (!player) return "";
    return player->GetGuildName();
    SAFE_END_EX("")
}

void LuaHost::Player_SetCurContrib(const std::string &playerGUID, uint32_t contrib)
{
    auto *player = GetPlayerByGuid(playerGUID);
    if (!player) return;
    player->GetGuildDataMgr().SetCurContrib(contrib);
}

uint32_t LuaHost::Player_GetTotalContrib(const std::string &playerGUID)
{
    auto *player = GetPlayerByGuid(playerGUID);
    if (!player) return 0;
    return player->GetGuildDataMgr().GetTotalContrib();
}

void LuaHost::Player_GetRolePackInfo(const std::string& guid, const int type)
{
    SAFE_BEGIN
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;

    auto playerPack = player->GetRolePack();
    if (playerPack == nullptr) return;

    const auto &itemlist = playerPack->GetItemList();

    CLuaObject luaRet = NewLuaObj();
    int index = 1;
    switch (type)
    {
    case 1:  //背包
        for (int i = site_bag_0; i < site_warehouse; ++i)
        {
            if (itemlist.at(i) != nullptr)
            {
                luaRet[index] = std::to_string(playerPack->GetItemGuidBySite(i));
                ++index;
            }
        }
        break;
    case 2:  // 仓库
        for (int i = site_warehouse; i < site_warehouse_adv; ++i)
        {
            if (itemlist.at(i) != nullptr)
            {
                luaRet[index] = std::to_string(playerPack->GetItemGuidBySite(i));
                ++index;
            }
        }
        break;
    case 3:  //高级仓库
        for (int i = site_warehouse_adv; i < site_bag_end; ++i)
        {
            if (itemlist.at(i) != nullptr)
            {
                luaRet[index] = std::to_string( playerPack->GetItemGuidBySite(i));
                ++index;
            }
        }
        break;
    default:
        break;
    }
    LuaRet = luaRet;
    SAFE_END
}

std::string LuaHost::Player_GetItemBySite(const std::string& guid, const int site)
{
    SAFE_BEGIN_EX
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return "";

    auto playerPack = player->GetRolePack();
    if (playerPack == nullptr) return "";

    auto itemguid = playerPack->GetItemGuidBySite(site);
    return itemguid == 0 ? "" : to_string(itemguid);
    SAFE_END_EX("")
}

int LuaHost::Player_GetItemBindType(const std::string& guid, const std::string& itemguid)
{
    SAFE_BEGIN_EX
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return -1;

    auto item = player->GetRolePack()->FindItem(std::stoull(itemguid));
    if (item == nullptr)return -1;

    return item->GetIsBind();
    SAFE_END_EX(false)
}

void LuaHost::Player_SetItemBindType(const std::string& guid, const std::string& itemguid, int type)
{
    SAFE_BEGIN
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;

    auto item = player->GetRolePack()->FindItem(std::stoull(itemguid));
    if (item == nullptr)return;

    item->SetIsBind(type);
    SAFE_END
}
int LuaHost::Player_GetItemSiteByGuid(const std::string& guid, const std::string& itemGuid)
{
	SAFE_BEGIN_EX
		auto* player = GetPlayerByGuid(guid);
	if (nullptr == player)
		return -1;
	auto item = player->GetRolePack()->FindItem(std::stoull(itemGuid));
	if (item == nullptr)
		return -1;
	auto rolePack = player->GetRolePack();
	if (!rolePack) return ERR_UNKNOW;
	auto itemguid = std::stoull(itemGuid);
	int nsite = (int)rolePack->GetItemSite(itemguid);

	return nsite;
	SAFE_END_EX(false)
}

bool LuaHost::Player_SetAutoPickItemRadius(const std::string &guid, uint8_t radius)
{
    SAFE_BEGIN_EX;
    auto *player = GetPlayerByGuid(guid);
    if (!player) return false;
    return player->SetAutoPickItemRadius(radius);
    SAFE_END_EX(false);
}

bool LuaHost::Player_SetAutoPickItemRelativePositions(const std::string &guid, const CLuaObject &relpos)
{
    SAFE_BEGIN_EX;

    auto *player = GetPlayerByGuid(guid);
    if (!player) return false;

    std::vector<Point> points;

    // relpos: { {1, 1}, {-1, -1}, {1, 0}, ... }
    for (luabind::iterator it(relpos), end; it != end; ++it)
    {
        auto luaPos = *it;
        if (luabind::type(luaPos) != LUA_TTABLE) return false;

        const auto &luax = luaPos[1];
        if (luabind::type(luax) != LUA_TNUMBER) return false;

        const auto &luay = luaPos[2];
        if (luabind::type(luay) != LUA_TNUMBER) return false;

        auto x = luabind::object_cast<int16_t>(luax);
        auto y = luabind::object_cast<int16_t>(luay);

        points.emplace_back(x, y);
    }

    return player->SetAutoPickItemRelativePositions(std::move(points));
    SAFE_END_EX(false);
}

bool LuaHost::Player_SetAutoPickItemInterval(const std::string &guid, uint16_t interval)
{
    SAFE_BEGIN_EX;

    auto *player = GetPlayerByGuid(guid);
    if (!player) return false;

    return player->SetAutoPickItemInterval(interval);
    SAFE_END_EX(false);
}

bool LuaHost::Player_SetItemCfg(const std::string& guid, const std::string& itemguid, const CLuaObject& tab)
{
    SAFE_BEGIN_EX

    auto* player = GetPlayerByGuid(guid);
    if (!player) return false;

    return player->GetRolePack()->SetItemCfg(std::stoull(itemguid), tab);
    SAFE_END_EX(false)
}

bool LuaHost::Player_SetName(const std::string& guid, const std::string& name)
{
    SAFE_BEGIN_EX
    if (name.size() > MAX_ROLE_NAME_LENGTH) return false;
    Player::SetNameToCS(name, std::stoull(guid));
    return true;
    SAFE_END_EX(false)
}

bool LuaHost::Player_AddTitle(const std::string& guid, const std::string& titleName)
{
    SAFE_BEGIN_EX
    auto* player = GetPlayerByGuid(guid);
    if (!player) return false;
    return player->AddTitleByName(titleName);
    SAFE_END_EX(false)

}

bool LuaHost::Player_DelTitle(const std::string& guid, const std::string& titleName)
{
    SAFE_BEGIN_EX
    auto* player = GetPlayerByGuid(guid);
    if (!player) return false;
    return player->DelTitleByName(titleName);
    SAFE_END_EX(false)
}

bool LuaHost::Player_HasTitle(const std::string& guid, const std::string& titleName)
{
    SAFE_BEGIN_EX
    auto* player = GetPlayerByGuid(guid);
    if (!player) return false;
    return player->IsHasTitle(titleName);
    SAFE_END_EX(false)
}

std::string LuaHost::Player_TitleIDToName(uint32_t titleID)
{
    SAFE_BEGIN_EX
    auto titleCfg = sTitleConfig.GetByID(titleID);
    if (nullptr == titleCfg)return "";
    return titleCfg->KeyName;
    SAFE_END_EX("")
}

uint32_t LuaHost::Player_TitleNameToID(const std::string& name)
{
    SAFE_BEGIN_EX
    auto titleCfg = sTitleConfig.GetByKeyName(name);
    if (nullptr == titleCfg)return 0;
    return titleCfg->Id;
    SAFE_END_EX(0)
}

void LuaHost::Player_RedemptionActivationCode(const std::string& guid, uint16_t type, const std::string& code)
{
    SAFE_BEGIN
    auto* player = GetPlayerByGuid(guid);
    if (!player) return;

    player->SendActivationCodeToCS(type, code);
    return ;
    SAFE_END
}

bool LuaHost::Player_AddProficiencyValue(const std::string& guid, uint32_t skillID, uint32_t value)
{
    SAFE_BEGIN_EX
    auto* player = GetPlayerByGuid(guid);
    if (!player) return false;

    return player->AddSkillProficiencyValue(skillID, value);
    SAFE_END_EX(false)
}

bool LuaHost::Player_SetSkillLevel(const std::string& guid, uint32_t skillID)
{
    SAFE_BEGIN_EX
        auto* player = GetPlayerByGuid(guid);
    if (!player) return false;

    return player->SetSkillLevel(skillID);
    SAFE_END_EX(false)
}

bool LuaHost::Player_IsProhibitChat(const std::string& guid)
{
    SAFE_BEGIN_EX
    auto ret = ProhibitChatMgr::GetInstance()->IsProhibitChatStatus(std::stoull(guid));
    if (ret)return true;
    auto* player = GetPlayerByGuid(guid);
    if (!player) return false;
    ret = PlayerProhibitChatMgr::GetInstance()->IsProhibitChat(player->GetUserID());
    if (ret)return true;
    return false;
    SAFE_END_EX(false)
}

CLuaObject LuaHost::Player_GetListProp(const std::string& guid, uint16_t type, uint16_t min, uint16_t max)
{
    SAFE_BEGIN_EX
    auto obj = NewLuaObj();
    auto* player = GetPlayerByGuid(guid);
    if (!player) return obj;

    if ((type == lua_get_prop) && min > max)return obj;

    player->GetListProp(obj, type, min, max);
    return obj;
    SAFE_END_EX(CLuaObject())

}

CLuaObject LuaHost::Player_ItemGuidList(const std::string& guid, uint16_t min, uint16_t max)
{
    SAFE_BEGIN_EX
    auto obj = NewLuaObj();

    auto* player = GetPlayerByGuid(guid);
    if (!player) return obj;

    if (min > max)return obj;

    player->GetListItem(obj, min, max);
    return obj;
    SAFE_END_EX(CLuaObject())
}

uint16_t LuaHost::Player_IsLuaGM(const std::string& guid)
{
    SAFE_BEGIN_EX
    if (guid.empty()) return 0;
    uint64_t id = 0;
    try {
        id = std::stoull(guid);
    }
    catch (...) {
        return 0;
    }
    return LuaGmMgr::GetInstance()->IsLuaGM(id);
    SAFE_END_EX(0)
}

bool LuaHost::Player_AddCustListInfo(const std::string& guid, int type, const std::string& value, const std::string& desc)
{
    SAFE_BEGIN_EX
    uint64_t playerGUID = 0;
    int64_t  listValue = 0;
    try {
        playerGUID = std::stoull(guid);
        listValue = _atoi64(value.c_str());
        if (desc.size() > 1000) {
            LOG_ERROR("Parsing Cust Info failed! The desc is out of length!");
            return false;
        }
    }
    catch (...) {
        LOG_ERROR("Parsing Cust Info failed! guid:%s,value:%s", guid, value);
        return false;
    }

    CustListMgr::GetInstance()->InsertDataByType(playerGUID, type, listValue, desc.c_str());
    return true;
    SAFE_END_EX(false)
}

bool LuaHost::Player_SetGender(const std::string& guid, int gender)
{
    SAFE_BEGIN_EX
    auto* player = GetPlayerByGuid(guid);
    if (!player) return false;

    return player->SetGender(gender);
    SAFE_END_EX(false);
}

void LuaHost::Role_InsertInfo(const std::string& guid, const std::string& info)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;

    player->InsertRoleInfo(info);
    return;
}

void LuaHost::Role_UpdateInfo(const std::string& guid, const std::string& info)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;

    player->UpdateRoleInfo(info);
    return;
}

void LuaHost::Role_ClearInfo(const std::string& guid)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;

    player->ClearRoleInfo();
    return;
}

void LuaHost::Role_DelInfo(const std::string& guid, const std::string& info)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;

    player->DelRoleInfo(info);
    return;
}

void LuaHost::Role_GetInfoReq(const std::string& guid)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return;

    player->GetRoleInfoReq();
    return;
}

const std::string LuaHost::Role_GetInfoAck(const std::string& guid)
{
    auto* player = GetPlayerByGuid(guid);
    if (nullptr == player) return"";

    return player->GetRoleInfoAck();
}

void LuaHost::Role_SetDynAttr(const std::string& guid, uint16_t index, uint16_t attr, int32_t value)
{
    auto* role = GetRole(guid);
    if (nullptr == role) return;

    auto roleAttr = role->GetRoleAttr();
    if (!roleAttr) return;

    roleAttr->SetDynAttr(index, attr, value);
}

CLuaObject LuaHost::Role_GetDynAttr(const std::string& guid, uint16_t index)
{
    auto obj = NewLuaObj();

    auto* role = GetRole(guid);
    if (nullptr == role) return obj;

    auto roleAttr = role->GetRoleAttr();
    if (!roleAttr) return obj;

    auto dynAttr = roleAttr->GetDynAttr(index);

    obj["index"] = index;
    obj["attr"] = dynAttr.attr;
    obj["value"] = dynAttr.value;

    return obj;
}

////////////////////////////////////////////////////////////////////////////////
//
// Npc export functions
//
inline Npc* LuaHost::GetNpcByGuid(const std::string& guid)
{
    SAFE_BEGIN_EX
    if (guid.empty()) return nullptr;

    auto* mapRoleMgr = MapRoleMgr::GetInstance();
    if (!mapRoleMgr) return nullptr;

    auto id = std::stoull(guid);
    return mapRoleMgr->FindNpc(id);
    SAFE_END_EX(nullptr)
}
// ok
uint16_t LuaHost::Npc_NpcTalkAck(const std::string& guid, const std::string& ack)
{
    auto* npc = GetNpcByGuid(guid);
    if (nullptr == npc) return 0;

    return npc->NpcTalkAck(ack);
}
// ok
int LuaHost::Npc_GetTemplateID(const std::string& guid)
{
    auto* npc = GetNpcByGuid(guid);
    if (nullptr == npc) return -1;

    return npc->GetTemplateID();
}

std::string LuaHost::NPC_GetKeyName(const string& guid)
{
    SAFE_BEGIN_EX
    auto* npc = GetNpcByGuid(guid);
    if (nullptr == npc) return "";

    return npc->GetKeyName();
    SAFE_END_EX("")
}

////////////////////////////////////////////////////////////////////////////////
//
// Monster export functions
//
inline Monster* LuaHost::GetMonsterByGuid(const std::string& guid)
{
    SAFE_BEGIN_EX
    if (guid.empty()) return nullptr;

    auto* mapRoleMgr = MapRoleMgr::GetInstance();
    if (!mapRoleMgr) return nullptr;

    auto id = std::stoull(guid);
    if (IS_MONSTER_GUID(id))
    {
        return mapRoleMgr->FindMonster(id);
    }
    else if (IS_PET_GUID(id))
    {
        return mapRoleMgr->FindPet(id);
    }
    return nullptr;
    SAFE_END_EX(nullptr)
}

void LuaHost::Monster_BeSuckedAway(const std::string& guid, uint16_t x, uint16_t y)
{
    SAFE_BEGIN
    Role* master = GetMonsterByGuid(guid);
    if (nullptr == master)return;
    auto roleAttr = master->GetRoleAttr();
    if (!roleAttr) return;
    auto* map = master->GetCurMap();
    if (!map) return;
    if (!map->FindJumpablePos(x, y)) return;

    auto rolemove = master->GetRoleMove();
    if (rolemove) rolemove->StopMove(false);
    roleAttr->SetMoveType(move_type_sucked);
    uint8_t dir = Utility::CalcRelativeDir(master->GetRolePosX(), master->GetRolePosY(), x, y);
    master->SetRoleDir(dir);
    master->SetRolePos(x, y);
    master->RemoveBuffWhenMove();
    roleAttr->SetMoveType(move_type_walk);
    return;
    SAFE_END
}

void LuaHost::Monster_SetMasterName(const std::string& guid, const std::string& sMasterName)
{
    SAFE_BEGIN
    auto* master = GetMonsterByGuid(guid);
    if (nullptr == master)return;
    master->SetMasterName(sMasterName);
    return;
    SAFE_END
}

int LuaHost::Monster_GetTemplateID(const std::string& guid)
{
    SAFE_BEGIN_EX
    auto* master = GetMonsterByGuid(guid);
    if (nullptr == master)return -1;
    return master->GetTemplateID();
    SAFE_END_EX(-1)
}

int LuaHost::Monster_GetTemplateIDByName(const std::string KeyName)
{
    SAFE_BEGIN_EX
    auto cfg = sMonsterConfig.GetByKeyName(KeyName);
    return cfg == nullptr ? 0 : cfg->Id;
    SAFE_END_EX(0)
}

std::string LuaHost::Monster_GetMasterGUIDAsString(const std::string& guid)
{
    SAFE_BEGIN_EX
    auto* master = GetMonsterByGuid(guid);
    if (nullptr == master)return "";
    return master->GetMasterGUIDAsString();
    SAFE_END_EX("")
}

std::string LuaHost::Monster_GetBelongPlayerIDAsString(const std::string& guid)
{
    SAFE_BEGIN_EX
    auto* master = GetMonsterByGuid(guid);
    if (nullptr == master)return "";
    return master->GetBelongPlayerIDAsString();
    SAFE_END_EX("")
}

void LuaHost::Monster_SetSummonMonsterType(const std::string &guid, uint8_t type)
{
    auto *monster = GetMonsterByGuid(guid);
    if (!monster) return;

    monster->SetSummonMonsterType(type);
}

CLuaObject LuaHost::Monster_GetHateValueMap(const std::string& guid)
{
    SAFE_BEGIN_EX
    auto* master = GetMonsterByGuid(guid);
    if (nullptr == master)return NewLuaObj();
    return master->GetHateValueMapToLua();
    SAFE_END_EX(NewLuaObj())
}

const std::string LuaHost::Monster_GetCurAttackTar(const std::string& guid)
{
    SAFE_BEGIN_EX
    auto* master = GetMonsterByGuid(guid);
    if (nullptr == master)return "";
    auto pMonsterAI = master->GetAIMonster();
    if (pMonsterAI)
    {
        return std::to_string(pMonsterAI->GetTarGuid());
    }
    return "";
    SAFE_END_EX("")
}

void LuaHost::Monster_InitBiaoChe(const std::string& guid, const std::string& targuid, uint16_t x, uint16_t y, uint16_t range, 
    uint16_t finalRange, uint8_t posRange, const CLuaObject& posTable, const std::string& func)
{
    SAFE_BEGIN
    auto* monster = GetMonsterByGuid(guid);
    if (!monster) return;

    auto AI = monster->GetAIMonster();
    if (!AI) return;
    auto cfg = monster->GetConfig();
    if (!cfg) return;
    
    if ((cfg->MonsterAIType == type4_biaoche_active) || (cfg->MonsterAIType == type4_biaoche_non_active))
    {
        auto monsterAI = static_cast<MonsterAI_Type4*>(AI);

        monsterAI->InitParams(targuid, x, y, range, finalRange);
        return;
    }
    else if (cfg->MonsterAIType == type5_biaoche_non_master)
    {
        auto monsterAI = static_cast<MonsterAI_Type5*>(AI);

        monsterAI->InitParams(targuid, x, y, finalRange, func, posRange, posTable);
        return;
    }

    SAFE_END
}

void LuaHost::Monster_RegisterBehavior(const std::string& guid, const CLuaObject& info)
{
    SAFE_BEGIN
    auto* monster = GetMonsterByGuid(guid);
    if (!monster) return;
    auto monsterAI = monster->GetAIMonster();
    if (!monsterAI)return;
    monsterAI->RegisterBehaviour(info);
    SAFE_END
}

void LuaHost::Monster_RegisterAttribute(const std::string& guid, const CLuaObject& info)
{
    SAFE_BEGIN
    auto* monster = GetMonsterByGuid(guid);
    if (!monster) return;
    auto monsterAI = monster->GetAIMonster();
    if (!monsterAI)return;
    monsterAI->RegisterAttribute(info);
    SAFE_END
}

void LuaHost::Monster_RemoveMonsterBehavior(const std::string& guid, uint16_t behaviorID)
{
    SAFE_BEGIN
        auto* monster = GetMonsterByGuid(guid);
    if (!monster) return;
    auto monsterAI = monster->GetAIMonster();
    if (!monsterAI)return;

    monsterAI->RemoveBehaviour(behaviorID);
        SAFE_END
}

void LuaHost::Monster_RemoveMonster(const std::string & guid, bool appearBody)
{
    SAFE_BEGIN
    auto* monster = GetMonsterByGuid(guid);
    if (!monster) return;
    monster->RemoveMonster(appearBody);
    SAFE_END
}

void LuaHost::Monster_SetNameColor(const std::string& guid, const std::string& nameColor)
{
    SAFE_BEGIN
    auto* monster = GetMonsterByGuid(guid);
    if (!monster) return;
    monster->SetMonsterNameColor(nameColor);
    SAFE_END
}

void LuaHost::Monster_SwapSkillGroup(const std::string& guid, uint16_t skillGroup)
{
    SAFE_BEGIN
    auto* master = GetMonsterByGuid(guid);
    if (nullptr == master)return;
    if (master->IsPet())
    {
        auto petai = master->GetAIPet();
        if (!petai)return;
        petai->SwapSkillGroup(skillGroup);
        return;
    }
    auto monsterAI = master->GetAIMonster();
    if (!monsterAI)return;
    monsterAI->SwapSkillGroup(skillGroup);
    SAFE_END
}

void LuaHost::Monster_UseSpecialSkill(const std::string& guid, uint32_t Skillid)
{
    SAFE_BEGIN
    auto* master = GetMonsterByGuid(guid);
    if (!master) return;
    if (master->IsPet())
    {
        auto petai = master->GetAIPet();
        if (!petai)return;
        petai->UseSpecialSkill(Skillid);
        return;
    }
    auto monsterAI = master->GetAIMonster();
    if (!monsterAI)return;
    monsterAI->UseSpecialSkill(Skillid);
    SAFE_END
}

void LuaHost::Monster_Escape(const std::string& guid,int dis)
{
    SAFE_BEGIN
    auto* monster = GetMonsterByGuid(guid);
    if (!monster) return;
    auto monsterAI = monster->GetAIMonster();
    if (!monsterAI)return;
    monsterAI->Escape(dis);
    SAFE_END
}

void LuaHost::Monster_AddSkill(const std::string& guid, const CLuaObject& skillinfo)
{
    SAFE_BEGIN
    auto* master = GetMonsterByGuid(guid);
    if (nullptr == master)return;

    const auto& _skillid = skillinfo[1];
    if (luabind::type(_skillid) != LUA_TNUMBER) return;
    auto  skillid = luabind::object_cast<uint32_t>(_skillid);

    const auto& _weight = skillinfo[2];
    if (luabind::type(_weight) != LUA_TNUMBER) return;
    auto  weight = luabind::object_cast<uint32_t>(_weight);

    if (master->IsPet())
    {
        auto petai = master->GetAIPet();
        if (!petai)return;
        petai->AddSkill(skillid, weight);
        return;
    }
    auto monsterAI = master->GetAIMonster();
    if (!monsterAI)return;
    monsterAI->AddSkill(skillid, weight);
    SAFE_END
}

void LuaHost::Monster_RemoveSkill(const std::string& guid, uint32_t SkillID)
{
    SAFE_BEGIN
    auto* master = GetMonsterByGuid(guid);
    if (nullptr == master)return;
    if (master->IsPet())
    {
        auto petai = master->GetAIPet();
        if (!petai)return;
        petai->RemoveSkill(SkillID);
        return;
    }
    auto monsterAI = master->GetAIMonster();
    if (!monsterAI)return;
    monsterAI->RemoveSkill(SkillID);
    SAFE_END
}
void LuaHost::Monster_GetCurSkillGroup(const std::string& guid)
{
    SAFE_BEGIN
    auto* master = GetMonsterByGuid(guid);
    if (nullptr == master)
    {
        LuaRet = NewLuaObj();
        return;
    }

    std::vector<std::pair<int, int>> skillGroup;
    if (master->IsPet())
    {
        auto petai = master->GetAIPet();
        if (!petai)
        {
            LuaRet = NewLuaObj();
            return;
        }
        skillGroup = petai->GetCurSkillGroup();
    }
    else
    {
        auto monsterAI = master->GetAIMonster();
        if (!monsterAI)
        {
            LuaRet = NewLuaObj();
            return;
        }
        skillGroup = monsterAI->GetCurSkillGroup();
    }

    auto info = NewLuaObj();
    int index = 1;
    for (auto& i : skillGroup)
    {
        auto singleinfo = NewLuaObj();
        singleinfo[1] = i.first;
        singleinfo[2] = i.second;
        info[index] = singleinfo;
        ++index;
    }
    LuaRet = info;
    SAFE_END
}

void LuaHost::Monster_DropItem(const std::string& guid, const std::string& killerGuid)
{
    SAFE_BEGIN
    auto* monster = GetMonsterByGuid(guid);
    if (!monster) return;
    monster->CalcDropItems(std::stoull(killerGuid));
    SAFE_END
}

bool LuaHost::Monster_UpdateBiaocheAI(const std::string& guid)
{
    SAFE_BEGIN_EX
    auto* monster = GetMonsterByGuid(guid);
    if (!monster) return false;
    if (!monster->IsBiaoChe())return false;
    auto AI = monster->GetAIMonster();
    if (!AI)return false;
    AI->UpdateBiaocheAIState();
    return true;
    SAFE_END_EX(false)
}

bool LuaHost::Monster_SetPetFollowMasterAttackState(const std::string& guid, uint8_t state)
{
    SAFE_BEGIN_EX
    auto* pet = GetMonsterByGuid(guid);
    if (!pet) return false;
    auto AI = pet->GetAIPet();
    if (!AI)return false;
    if (state) AI->SetFollowMasterAttack();
    else AI->ResetFollowMasterAttack();
    return true;
    SAFE_END_EX(false)
}

void LuaHost::Map_RoleEnter(const std::string& mapGuid,const std::string& roleGuid)
{
    auto* map = GetMap(mapGuid);
    if (!map) return;

    auto* role = GetRole(roleGuid);
    if (!role) return;

    map->RoleEnter(role);
}
void LuaHost::Map_RoleLeave(const std::string& mapGuid,const std::string& roleGuid)
{
    auto* map = GetMap(mapGuid);
    if (!map) return;

    auto* role = GetRole(roleGuid);
    if (!role) return;

    map->RoleLeave(role);
}
std::string LuaHost::Map_GenSceneItem(const std::string & mapGuid, const std::string& ownerGuid, uint16_t x, uint16_t y, uint16_t id, uint16_t amount, uint16_t bind)
{
    auto* map = GetMap(mapGuid);
    if (!map) return "";
    
    return map->GenSceneItem(x, y, id, amount, bind, ownerGuid);
}
std::string LuaHost::Map_GenSceneItemByName(const std::string& mapGuid, const std::string& ownerGuid, uint16_t x, uint16_t y, const std::string& name, uint16_t amount, uint16_t bind)
{
    auto* map = GetMap(mapGuid);
    if (!map) return "";

    return map->GenSceneItemByName(x, y, name, amount, bind, ownerGuid);
}
std::string LuaHost::Map_GetMapName(const std::string& mapGuid)
{
    auto* map = GetMap(mapGuid);
    if (!map) return "";

    return map->GetName();
}
void LuaHost::Map_SetRegionSize(const std::string& mapGuid, uint16_t regionWidth, uint16_t regionHeight)
{
    auto* map = GetMap(mapGuid);
    if (!map) return;

    map->SetRegionSize(regionWidth, regionHeight);
}
std::string LuaHost::Map_GetRoleInPoint(const std::string& mapGuid, uint16_t posX, uint16_t posY)       //?Role*
{
    auto* map = GetMap(mapGuid);
    if (!map) return "";

    auto *role = map->GetMapAoi().GetRoleInPoint(posX, posY);
    if (!role) return "";

    return role->GetGUIDAsString();
}
bool LuaHost::Map_IsSafeRegion(const std::string& mapGuid, uint16_t  posx, uint16_t posy)
{
    auto* map = GetMap(mapGuid);
    if (!map) return false;

    return map->IsSafeRegion(posx, posy);
}
bool LuaHost::Map_IsGridAvail(const std::string& mapGuid, uint16_t x, uint16_t y)
{
    auto* map = GetMap(mapGuid);
    if (!map) return false;

    return map->IsGridAvail(x, y);
}
void LuaHost::Map_GenMapMonster(const std::string& mapGuid)
{
    auto* map = GetMap(mapGuid);
    if (!map) return;

    map->GenMapMonster();
}
void LuaHost::Map_GenMapMonsterByName(const std::string& mapGuid, const std::string& Name, uint16_t left, uint16_t top,
    uint16_t width, uint16_t height, uint16_t num, uint8_t dir)
{
    auto* map = GetMap(mapGuid);
    if (!map) return;

    map->GenMapMonsterByName(Name, left, top, width, height, num, dir);
}
void LuaHost::Map_GenMapMonsterByID(const std::string& mapGuid, uint16_t id, uint16_t left, uint16_t top,
    uint16_t width, uint16_t height, uint16_t num, uint8_t dir)
{
    auto* map = GetMap(mapGuid);
    if (!map) return;

    map->GenMapMonsterByID(id, left, top, width, height, num, dir);
}

std::string LuaHost::Map_GenMapNPCByKeyName(const std::string& mapGuid, const std::string& npcKeyName, uint16_t x, uint16_t y, uint8_t dir)
{
    auto* map = GetMap(mapGuid);
    if (!map) return "";

    return map->GenMapNPCByKeyName(npcKeyName, x, y, dir);
}

void LuaHost::Map_DelMapNPCByGuid(const std::string& npcGuid)
{
    auto role = GetNpcByGuid(npcGuid);
    if (!role) return;

    auto map = role->GetCurMap();
    if (!map) return;

    map->DelMapNPCByGuid(role->GetGUID());
}

int LuaHost::Map_GetMonsterNum(const std::string& mapGuid)
{
    auto* map = GetMap(mapGuid);
    if (!map) return 0;

    return map->GetMapAoi().GetMonsterNum();
}

void LuaHost::Map_SendSysMsg(const std::string& mapGuid, uint8_t nMsgType, const std::string& sMsg)
{
    auto* map = GetMap(mapGuid);
    if (!map) return;

    map->SendSysMsg(nMsgType, sMsg);
}
/*
MapAoi& LuaHost::Map_GetMapAoi(std::string mapGuid)
{
    auto* map = GetMap(mapGuid);
    if (!map) return;

    return map->GetMapAoi();
}
*/

////////////////////////////////////////////////////////////////////////////////
//
// RoleMgr export functions
//

std::string LuaHost::RoleMgr_GetPlayerGUID(const std::string &name)
{
    auto *roleMgr = MapRoleMgr::GetInstance();
    if (!roleMgr) return "";

    auto *player = roleMgr->GetPlayerByName(name);
    if (!player) return "";

    return player->GetGUIDAsString();
}

bool LuaHost::RoleMgr_IsRoleExist(const std::string &guid)
{
    auto *role = GetRole(guid);
    return (role != nullptr);
}

////////////////////////////////////////////////////////////////////////////////
//
// Role export functions
//

uint32_t LuaHost::Role_GetType(const std::string &guid)
{
    auto *role = GetRole(guid);
    if (!role) return role_type_none;

    return role->GetType();;
}

std::string LuaHost::Role_GetName(const std::string &guid)
{
    auto *role = GetRole(guid);
    if (!role) return "";

    return role->GetName();

}

void LuaHost::Role_SetName(const std::string& guid, const string& name)
{
    if (name.size() > MAX_ROLE_NAME_LENGTH) return;
    auto* role = GetRole(guid);
    if (!role) return;
    // 暂时不支持玩家改名
    if (role->GetType() == role_type_player) return;

    role->ChangeName(name);
}

void LuaHost::Role_SetAlias(const std::string& guid, const string& name)
{
    if (name.size() > MAX_ROLE_NAME_LENGTH) return;
    auto* role = GetRole(guid);
    if (!role) return;

    role->ChangeAlias(name);
}

std::string LuaHost::Role_GetCurMapGUID(const std::string &guid)
{
    auto *role = GetRole(guid);
    if (!role) return "";

    auto *map = role->GetCurMap();
    if (!map) return "";

    return map->GetGUIDAsString();
}

int32_t LuaHost::Role_GetProp(const std::string &guid, int prop)
{
    auto *role = GetRole(guid);
    if (!role) return 0;

    return role->GetRoleProp(prop);
}

int32_t LuaHost::Role_GetProp_Info(const std::string& guid, int prop)
{
    auto* role = GetRole(guid);
    if (!role) return 0;
    if (prop == 0)
    {
        SetRecordhistory(false);
    }
    if (prop == 1)
    {
        SetRecordhistory(true);
    }
    if (role->GetRoleAttr())
    {
        role->GetRoleAttr()->PrintPropertyMap(prop);
    }
    return 1;
}

CLuaObject LuaHost::Role_GetRegionRoleByType(const std::string& guid, uint8_t type)
{
    SAFE_BEGIN_EX
    auto table = NewLuaObj();
    auto* role = GetRole(guid);
    if (!role) return table;

    auto map = role->GetCurMap();
    if (!map)return table;

    std::list<Role*> list;
    map->GetMapAoi().GetSingleRegionRoleByType(list, type, role->GetRolePosX(), role->GetRolePosY());
    int idx = 1;
    for (auto i : list) {
        if (!i)continue;
        table[idx++] = i->GetGUIDAsString();
    }
    return table;
    SAFE_END_EX(NewLuaObj());
}

void LuaHost::Role_AddProp(const std::string& guid, int32_t prop, int32_t value)
{
    auto* role = GetRole(guid);
    if (!role) return;

    role->AddRoleProp(prop, value);
}

void LuaHost::Role_SetProp(const std::string &guid, int prop, int32_t value)
{
    auto *role = GetRole(guid);
    if (!role) return;

    role->SetRoleProp(prop, value);
}

std::string LuaHost::Role_GetProp64(const std::string &guid, int prop)
{
    auto *role = GetRole(guid);
    if (!role) return "";

    auto value = role->GetRoleProp64(prop);
    return std::to_string(value);
}

void LuaHost::Role_ModProp64(const std::string &guid, int prop, double delta, const CLuaObject& logInfo)
{
    auto *role = GetRole(guid);
    if (!role) return;

    int64_t value = delta;

    if (IS_PLAYER_GUID(std::stoll(guid)) && prop == role_exp) {
        auto *player = GetPlayerByGuid(guid);
        player->AddRoleExp(value, ParseLogParams(logInfo));
    }
    else {
        role->AddRoleProp64(prop, value, ParseLogParams(logInfo));
    }
    auto* player = GetPlayerByGuid(guid);
    if(player) player->UpdateRoleInfo();
}

void LuaHost::Role_ModProp64ByStr(const std::string& guid, int prop, std::string delta, const CLuaObject& logInfo)
{
    SAFE_BEGIN
    auto* role = GetRole(guid);
    if (!role) return;
    if (delta.empty())return;

    int64_t value = std::stoll(delta);
    if (IS_PLAYER_GUID(std::stoll(guid)) && prop == role_exp) {
        auto* player = GetPlayerByGuid(guid);
        player->AddRoleExp(value, ParseLogParams(logInfo));
    }
    else {
        role->AddRoleProp64(prop, value, ParseLogParams(logInfo));
    }
    auto* player = GetPlayerByGuid(guid);
    if (player) player->UpdateRoleInfo();
    SAFE_END
}

bool LuaHost::Role_CheckProp64Amount(const std::string &guid, int prop, const std::string &needNum)
{
    auto *role = GetRole(guid);
    if (!role) return false;

    return role->CheckProp64Amount(prop, needNum);
}

uint16_t LuaHost::Role_GetPosX(const std::string &guid)
{
    auto *role = GetRole(guid);
    if (!role) return UINT16_MAX;

    return role->GetRolePosX();
}

uint16_t LuaHost::Role_GetPosY(const std::string &guid)
{
    auto *role = GetRole(guid);
    if (!role) return UINT16_MAX;

    return role->GetRolePosY();
}

void LuaHost::Role_SetPos(const std::string &guid, uint16_t x, uint16_t y)
{
    auto *role = GetRole(guid);
    if (!role) return;

    role->SetRolePos(x, y);
}

uint8_t LuaHost::Role_GetDir(const std::string &guid)
{
    auto *role = GetRole(guid);
    if (!role) return dir_max;

    return role->GetRoleDir();
}

void LuaHost::Role_SetDir(const std::string &guid, uint8_t dir)
{
    auto *role = GetRole(guid);
    if (!role) return;

    role->SetRoleDir(dir);
}

bool LuaHost::Role_AddBuff(const std::string &guid, uint16_t buffID, uint16_t skillID)
{
    auto *role = GetRole(guid);
    if (!role) return false;

    return role->AddBuffByRole(buffID, role, skillID);
}

bool LuaHost::Role_AddBuffByRole(const std::string &guid, uint16_t buffID, const std::string &actorGUID, uint16_t skillID, const std::string& attrStr, uint32_t time)
{
    auto *role = GetRole(guid);
    if (!role) return false;

    auto *actor = GetRole(actorGUID);
    if (!actor) return false;

    return role->AddBuffByRole(buffID, actor, skillID, attrStr, time);
}

bool LuaHost::Role_RemoveBuff(const std::string &guid, uint16_t buffID)
{
    auto *role = GetRole(guid);
    if (!role) return false;

    return role->RemoveBuff(buffID);
}

bool LuaHost::Role_RemoveBuffWithActorID(const std::string &guid, uint16_t buffID, const std::string &actorID)
{
    auto *role = GetRole(guid);
    if (!role) return false;

    return role->RemoveBuffWithActorID(buffID, actorID);
}

bool LuaHost::Role_BuffExist(const std::string &guid, uint16_t buffID)
{
    auto *role = GetRole(guid);
    if (!role) return false;

    return role->BuffExist(buffID);
}

bool LuaHost::Role_BuffExistByGroupID(const std::string& guid, uint16_t buffGroupID)
{
    auto* role = GetRole(guid);
    if (!role) return false;

    return role->BuffExistByGroupID(buffGroupID);
}

bool LuaHost::Role_BuffExistByKeyName(const std::string& guid, const std::string& keyName)
{
    if (keyName.empty()) return false;
    auto* role = GetRole(guid);
    if (!role) return false;
    auto cfg = sBuffConfig.GetByKeyName(keyName);
    if (!cfg) return false;

    return role->BuffExist(cfg->Id);
}

uint16_t LuaHost::Role_GetBuffStack(const std::string& guid, uint16_t buffID)
{
    auto* role = GetRole(guid);
    if (!role) return false;

    return role->GetBuffStack(buffID);
}

std::string LuaHost::Role_GetBuffLeftTime(const std::string& guid, uint16_t buffID)
{
    auto* role = GetRole(guid);
    if (!role) return "-1";

    return std::to_string(role->GetBuffLeftTime(buffID));
}

CLuaObject LuaHost::Role_GetBuffList(const std::string &guid)
{
    auto luaObjBuffList = NewLuaObj();

    auto *role = GetRole(guid);
    if (!role) return luaObjBuffList;

    int i = 0;
    auto buffIDList = role->GetValidBuffIDList();
    for (const auto &buffID : buffIDList)
        luaObjBuffList[++i] = buffID;

    return luaObjBuffList;
}

void LuaHost::Role_UpdateBuffStack(const std::string& guid, uint16_t buffID, int16_t diff)
{
    auto* role = GetRole(guid);
    if (!role) return;

    return role->UpdateBuffStack(buffID,  diff);
}

void LuaHost::Role_AttackedByRole(const std::string &guid, const std::string &actorGUID, uint16_t skillID, uint32_t lossHP, uint8_t harmType)
{
    auto *actor = GetRole(actorGUID);
    Role_AttackedByRole2(guid, actorGUID, actor ? actor->GetName() : "", skillID, lossHP, harmType);
}

void LuaHost::Role_AttackedByRole2(const std::string &guid, const std::string &actorGUID, const std::string &actorName,
    uint16_t skillID, uint32_t lossHP, uint8_t harmType)
{
    auto *role = GetRole(guid);
    if (!role) return;

    AttackResult res;
    res.actorGUID = std::stoull(actorGUID);
    res.actorName = actorName;
    res.targetGUID = role->GetGUID();
    res.skillId = skillID;
    res.decreaseHP = lossHP;
    res.type = harmType;
    role->AttackedByRole(res);
}

bool LuaHost::Role_IsAlive(const std::string &guid)
{
    auto *role = GetRole(guid);
    if (!role) return false;

    return role->CheckAlive();
}

std::string LuaHost::Role_GetBuffActorGuid(const std::string &guid, uint16_t buffID)
{
    auto *role = GetRole(guid);
    if (!role) return "";

    return role->GetBuffActorGuid(buffID);
}

std::string LuaHost::Role_GetBuffActorName(const std::string &guid, const std::string &actorGuid, uint16_t buffID)
{
    auto *role = GetRole(guid);
    if (!role) return "";

    return role->GetBuffActorName(actorGuid, buffID);
}

uint8_t LuaHost::Role_GetBuffActorJob(const std::string &guid, const std::string &actorGuid, uint16_t buffID)
{
    auto *role = GetRole(guid);
    if (!role) return 0;

    return role->GetBuffActorJob(actorGuid, buffID);
}

uint32_t LuaHost::Role_GetBuffActorLevel(const std::string &guid, const std::string &actorGuid, uint16_t buffID)
{
    auto *role = GetRole(guid);
    if (!role) return 0;

    return role->GetBuffActorLevel(actorGuid, buffID);
}

uint16_t LuaHost::Role_GetBuffActorSkill(const std::string &guid, const std::string &actorGuid, uint16_t buffID)
{
    auto *role = GetRole(guid);
    if (!role) return 0;

    return role->GetBuffActorSkill(actorGuid, buffID);
}

void LuaHost::Role_IncreaseHP(const std::string &guid, int32_t amount, uint8_t type, bool notify)
{
    auto *role = GetRole(guid);
    if (!role) return;

    role->UpdateHPMP(amount, 0, type, notify);
}

void LuaHost::Role_DecreaseHP(const std::string &guid, int32_t amount, uint8_t type, bool notify)
{
    auto *role = GetRole(guid);
    if (!role) return;

    role->UpdateHPMP(-amount, 0, type, notify);
}

void LuaHost::Role_SetSkillProp(const std::string& guid, uint16_t skillID, uint16_t propType, const std::string& cfg)
{
    auto* role = GetRole(guid);
    if (!role) return;
    
    role->SetSkillProp(skillID, propType, cfg);
}

bool LuaHost::Role_GetSkillProp(const std::string& guid, uint16_t skillID, uint16_t propType)
{
    auto* role = GetRole(guid);
    if (!role) return false;

    return role->GetSkillProp(skillID, propType);
}

bool LuaHost::Role_JumpMapByGuid(const std::string& guid, const std::string& mapGuid, uint16_t x, uint16_t y)
{
    auto* role = GetRole(guid);
    if (!role) return false;
    auto map = MapMgr::GetInstance()->FindMapByGUID(std::stoull(mapGuid));
    if (!map)return false;
    return role->JumpMap(map, x, y);
}

bool LuaHost::Role_RandJumpMapByGuid(const std::string& guid, const std::string& mapGuid)
{
    auto* role = GetRole(guid);
    if (!role) return false;
    auto map = MapMgr::GetInstance()->FindMapByGUID(std::stoull(mapGuid));
    if (!map)return false;
    return role->RandJumpMap(std::stoull(mapGuid));
}

bool LuaHost::Role_ApplySkill(const std::string &guid, uint16_t skillID, uint16_t x, uint16_t y,
                              const std::string &targetGUID)
{
    auto *role = GetRole(guid);
    if (!role) return false;
    auto *roleSkill = role->GetRoleSkill();
    if (!roleSkill) return false;
    auto target = stoull_s(targetGUID);
    roleSkill->ApplySkillOnGrid(skillID, target, x, y, 0);
    return true;
}

std::string LuaHost::Role_GetMasterGUIDAsString(const std::string &guid)
{
    auto *role = GetRole(guid);
    if (!role) return EMPTYSTR;
    if (role->IsPlayerDoplganr()) {
        auto *doplganr = static_cast<PlayerDoplganr *>(role);
        return std::to_string(doplganr->GetMasterGUID());
    }
    else if (role->IsMonster() || role->IsPet()) {
        auto *monster = static_cast<Monster *>(role);
        return monster->GetMasterGUIDAsString();
    }
    return EMPTYSTR;
}

void LuaHost::Role_SetRideHorseModelid(const std::string& guid, int32_t value)
{
    return Role_SetProp(guid, role_horse_modelid, value);
}

void LuaHost::Role_SetRideHorseSwitch(const std::string& guid, bool value)
{
    return Role_SetProp(guid, role_ride_switch, value ? 1 : 0);
}

int32_t LuaHost::Role_GetRideHorseModelid(const std::string& guid)
{
    return Role_GetProp(guid, role_horse_modelid);
}

bool LuaHost::Role_GetRideHorseSwitch(const std::string& guid)
{
    return Role_GetProp(guid, role_ride_switch) >= 1;
}

void LuaHost::Role_ChangeAppearance(const std::string& guid, uint16_t modelID)
{
    auto* role = GetRole(guid);
    if (!role) return;

    role->SetRoleProp(role_changed_modelid, modelID);
    if (role->IsNpc())
    {
        auto npc = static_cast<Npc*>(role);
        auto map = npc->GetCurMap();
        if (!map)return;
        map->GetMapAoi().RoleEnter(npc);
    }

}


////////////////////////////////////////////////////////////////////////////////
//
// Helper functions
//

Role * LuaHost::GetRole(const std::string &guid)
{
    SAFE_BEGIN_EX
    if (guid.empty()) return nullptr;

    auto *roleMgr = MapRoleMgr::GetInstance();
    if (!roleMgr) return nullptr;

    auto id = std::stoull(guid);
    return roleMgr->FindRole(id);
    SAFE_END_EX(nullptr);
}

Map* LuaHost::GetMap(const std::string& guid)
{
    SAFE_BEGIN_EX
    if (guid.empty()) return nullptr;

    auto* mapMgr = MapMgr::GetInstance();
    if (!mapMgr) return nullptr;

    auto id = std::stoull(guid);
    auto* map = mapMgr->FindMapByGUID(id);
    return map;
    SAFE_END_EX(nullptr);
}

std::string LuaHost::Guild_GetGUIDByName(const std::string &guildName)
{
    auto *guildMgr = GuildMgr::GetInstance();
    if (!guildMgr) return EMPTYSTR;
    auto guildGUID = guildMgr->GetGuildIDByName(guildName);
    return std::to_string(guildGUID);
}

std::string LuaHost::Guild_GetLeaderName(const std::string &guildGUID)
{
    if (guildGUID.empty()) return "";

    auto *guildMgr = GuildMgr::GetInstance();
    if (!guildMgr) return "";

    char buff[32] = {0};
    guildMgr->GetChairmanName(std::stoull(guildGUID), buff, _countof(buff));

    return buff;
}

int LuaHost::Guild_AddAlly(const std::string &myGuildName, const std::string &allyGuildName)
{
    return GuildMgr::GetInstance()->AddAlly(myGuildName, allyGuildName);
}

int LuaHost::Guild_DelAlly(const std::string &myGuildName, const std::string &allyGuildName)
{
    return GuildMgr::GetInstance()->DelAlly(myGuildName, allyGuildName);
}

bool LuaHost::Guild_IsAlly(const std::string &myGuildName, const std::string &allyGuildName)
{
    return GuildMgr::GetInstance()->IsAlly(myGuildName, allyGuildName);
}

int LuaHost::Guild_AddEnemy(const std::string &myGuildName, const std::string &enemyGuildName)
{
    return GuildMgr::GetInstance()->AddEnemy(myGuildName, enemyGuildName);
}

int LuaHost::Guild_DelEnemy(const std::string &myGuildName, const std::string &enemyGuildName)
{
    return GuildMgr::GetInstance()->DelEnemy(myGuildName, enemyGuildName);
}

bool LuaHost::Guild_IsEnemy(const std::string &myGuildName, const std::string &enemyGuildName)
{
    return GuildMgr::GetInstance()->IsEnemy(myGuildName, enemyGuildName);
}

CLuaObject LuaHost::Guild_GetGuildNameList()
{
    auto obj = NewLuaObj();
    int i = 0;

    const auto &guilds = GuildMgr::GetInstance()->GetGuilds();
    for (const auto &it : guilds) {

        obj[++i] = it.second->name;
    }

    return obj;
}

CLuaObject LuaHost::Guild_GetGuildMember(const std::string& GuildGUID)
{
    SAFE_BEGIN_EX
    auto table = NewLuaObj();
    auto pMemberList = GuildMgr::GetInstance()->GetMemberList(std::stoull(GuildGUID));
    if (!pMemberList)return table;
    int idx = 1;
    for (auto iter = pMemberList->begin(); iter != pMemberList->end(); ++iter)
    {
        if (iter->get()->status != guild_member_status_removed)
        {
            table[idx] = std::to_string(iter->get()->player_id);
            ++idx;
        }
    }
    return table;
    SAFE_END_EX(NewLuaObj())
}

int32_t LuaHost::Guild_JoinGuild(const std::string& playerGuid, const std::string& guildGuid)
{
    SAFE_BEGIN_EX
    return GuildMgr::GetInstance()->JoinGuild(std::stoull(playerGuid), std::stoull(guildGuid), SPGUILD_APPLICANT());
    SAFE_END_EX(0);
}

int32_t LuaHost::Guild_SetGuildLevel(const std::string& guildGuid, uint16_t level)
{
    SAFE_BEGIN_EX
    return GuildMgr::GetInstance()->SetGuildLevel(std::stoull(guildGuid), level);
    SAFE_END_EX(0);
}

void LuaHost::Guild_GuildWar(const std::string& guildGuid, const std::string& enemyGuildGuid, uint32_t durTime)
{
    SAFE_BEGIN_EX
    GuildMgr::GetInstance()->GuildWar(std::stoull(guildGuid), std::stoull(enemyGuildGuid), durTime);
    SAFE_END_EX();
}

int32_t LuaHost::Guild_SetGuildAutoJoinLevel(const std::string& guildGuid, uint32_t level)
{
    SAFE_BEGIN_EX
    return GuildMgr::GetInstance()->SetGuildAutoJoinLevel(std::stoull(guildGuid), level);
    SAFE_END_EX(0);
}

int32_t LuaHost::Guild_EditGuildNotice(const std::string& guildGuid, const std::string& notice)
{
    SAFE_BEGIN_EX
    return GuildMgr::GetInstance()->EditGuildNotice(std::stoull(guildGuid), notice);
    SAFE_END_EX(0);
}

int32_t LuaHost::Guild_ChangeGuildMemberTitle(const std::string& memberGUID, uint8_t title)
{
    SAFE_BEGIN_EX
    return GuildMgr::GetInstance()->ChangeGuildMemberTitle(std::stoull(memberGUID), title);
    SAFE_END_EX(0);
}

int32_t LuaHost::Guild_KickGuildMember(const std::string& memberGUID)
{
    SAFE_BEGIN_EX
    return GuildMgr::GetInstance()->KickGuildMember(std::stoull(memberGUID));
    SAFE_END_EX(0);
}

int32_t LuaHost::Guild_DestroyGuild(const std::string& guildGuid)
{
    SAFE_BEGIN_EX
    return GuildMgr::GetInstance()->DestroyGuild(std::stoull(guildGuid));
    SAFE_END_EX(0);
}

void LuaHost::Item_UpdateDurability(const std::string& guid, int32_t value)
{
    SAFE_BEGIN_EX
    if (guid.empty()) return;

    auto* item = ItemMap::GetInstance()->GetItem(std::stoull(guid));
    if (!item) return;
    auto roleItem = static_cast<RoleItem*>(item);
    if (!roleItem) return;

    roleItem->UpdateDurability(value);
    if (item->GetCategory() == item_cat_player)
    {
        auto roleGuid = roleItem->GetRoleid();
        auto role = GetRole(to_string(roleGuid));
        if (!role) return;
        auto rolePack = role->GetRolePack();
        if (!rolePack) return;
        rolePack->NtfMasterUpdateItem(roleItem->GetSite());
    }
    SAFE_END_EX()
}

int32_t LuaHost::Item_Geturability(const std::string& guid)
{
    SAFE_BEGIN_EX
    if (guid.empty()) return 0;

    auto* item = ItemMap::GetInstance()->GetItem(std::stoull(guid));
    if (!item) return 0;
    auto roleItem = static_cast<RoleItem*>(item);
    if (!roleItem) return 0;

    return roleItem->GetDurability();
    SAFE_END_EX(0);
}

void LuaHost::Item_SetDynAttr(const std::string &guid, uint16_t index, uint16_t attr, int32_t value)
{
    SAFE_BEGIN_EX
    if (guid.empty()) return;

    auto *item = ItemMap::GetInstance()->GetItem(std::stoull(guid));
    if (!item) return;
    if (item->GetCategory() == item_cat_player)
    {
        auto roleItem = static_cast<RoleItem*>(item);
        if (!roleItem) return;
        auto roleGuid = roleItem->GetRoleid();
        auto role = GetRole(to_string(roleGuid));
        if (!role) return;
        auto rolePack = role->GetRolePack();
        if (!rolePack) return;
        rolePack->SetDynAttr(roleItem->GetSite(), index, attr, value);
    }
    else
    {
        item->SetDynAttr(index, attr, value);
    }
    SAFE_END_EX()
}

CLuaObject LuaHost::Item_GetDynAttr(const std::string &guid, uint16_t index)
{
    SAFE_BEGIN_EX
    auto obj = NewLuaObj();

    if (guid.empty()) return obj;

    auto *item = ItemMap::GetInstance()->GetItem(std::stoull(guid));
    if (!item) return obj;

    auto dynAttr = item->GetDynAttr(index);

    obj["index"] = index;
    obj["attr"] = dynAttr.attr;
    obj["value"] = dynAttr.value;

    return obj;
    SAFE_END_EX(NewLuaObj())
}

int LuaHost::Item_GetTempId(const std::string& guid)
{
    SAFE_BEGIN_EX
    if (guid.empty()) return -1;

    auto* item = ItemMap::GetInstance()->GetItem(std::stoull(guid));
    if (!item) return -1;

    return item->GetTemplateID();
    SAFE_END_EX(-1)
}

std::string LuaHost::Item_ItemInfoEncodeToJson(const std::string& guid)
{
    SAFE_BEGIN_EX
    if (guid.empty()) return "";

    auto* item = ItemMap::GetInstance()->GetItem(std::stoull(guid));
    if (!item) return "";
    Json::Value jsondata(Json::objectValue);

    jsondata["guid"] = item->GetGUIDAsString();
    jsondata["tempid"] = item->GetTemplateID();
    jsondata["name"] = item->GetName();
    auto* roleitem = dynamic_cast<RoleItem*>(item);
    if (!roleitem) return "";
    if (roleitem->GetSite() != 0)
    {
        jsondata["site"] = roleitem->GetSite();
    }
    if (roleitem->GetAmount() != 0)
    {
        jsondata["amount"] = roleitem->GetAmount();
    }
    if (roleitem->GetDurability() != 0)
    {
        jsondata["durability"] = roleitem->GetDurability();
    }
    if (roleitem->GetMaxDurability() != 0)
    {
        jsondata["durability_max"] = roleitem->GetMaxDurability();
    }
    if (roleitem->GetUse_count() != 0)
    {
        jsondata["use_count"] = roleitem->GetUse_count();
    }
    jsondata["bind"] = roleitem->GetIsBind();
    if (roleitem->GetLife() != 0)
    {
        jsondata["life"] = roleitem->GetLife();
    }
    auto &DynAttrList = item->GetDynAttrs();
    if (!DynAttrList.empty())
    {
        int index = 0;
        Json::Value dynAttr(Json::arrayValue);
        for (auto& i : DynAttrList)
        {
            Json::Value singleDynAttr(Json::objectValue);
            singleDynAttr["index"] = i.index;
            singleDynAttr["attr"] = i.attr;
            singleDynAttr["value"] = i.value;
            dynAttr[index] = singleDynAttr;
            ++index;
        }
        jsondata["dynattr"] = dynAttr;
    }
    auto &CustMap = item->GetCustVars();
    if (!CustMap.empty())
    {
        int index = 0;
        Json::Value custVar(Json::arrayValue);
        for (auto& i : CustMap)
        {
            Json::Value singleCustVar(Json::objectValue);
            singleCustVar["index"] = i.second->name;
            singleCustVar["attr"] = i.second->value;
            singleCustVar["value"] = i.second->type;
            singleCustVar["expire"] = to_string(i.second->expire);
            custVar[index] = singleCustVar;
            ++index;
        }
        jsondata["cust_var"] = custVar;
    }
    return jsondata.toFastString();
    SAFE_END_EX("")
}

std::string LuaHost::Item_DecodeJsonToAddItem(const std::string& info, const std::string& belong)
{
    SAFE_BEGIN_EX
    Json::Value jsondata(Json::objectValue);
    Json::Reader reader;
    reader.parse(info, jsondata);
    auto player = static_cast<Player*>(MapRoleMgr::GetInstance()->GetRole(belong));
    if (player == nullptr)return "";
    auto site = player->GetRolePack()->GetIdleBagSite();
    auto result = player->AddSingleItem(jsondata["tempid"].asUInt(), jsondata["amount"].asUInt(), jsondata["bind"].asUInt(), log_params{ "反序列化" });
    if (!result)return "";
    auto item = player->GetRolePack()->GetItem(site);
    if (item == nullptr)return "";
    if (jsondata["durability"].asInt())
    {
        item->SetDurability(jsondata["durability"].asInt());
    }
    if (jsondata["durability_max"].asInt())
    {
        item->SetMaxDurability(jsondata["durability_max"].asInt());
    }
    if (jsondata["use_count"].asInt())
    {
        item->SetUse_count(jsondata["use_count"].asUInt());
    }
    item->SetIsBind(jsondata["bind"].asUInt());
    if (jsondata["life"].asUInt())
    {
        item->SetLife(jsondata["life"].asUInt());
    }
    Json::Value dynAttr(Json::arrayValue);
    dynAttr = jsondata["dynattr"];
    if (!dynAttr.isNull())
    {
        DYN_ATTRS mylist;
        for (int i = 0; i < dynAttr.size(); ++i)
        {
            DYN_ATTR value;
            value.index = dynAttr[i]["index"].asUInt();
            value.attr  = dynAttr[i]["attr"].asUInt();
            value.value = dynAttr[i]["value"].asInt();
            mylist.emplace_back(value);
        }
        item->SetDynAttrs(mylist);
    }
    Json::Value custVar(Json::arrayValue);
    custVar = jsondata["cust_var"];
    if (!custVar.isNull())
    {
        CUST_VAR_SP_MAP mymap;
        for (int i = 0; i < custVar.size(); ++i)
        {
            CUST_VAR_SP value;
            value->belong = std::stoull(belong);
            value->name = custVar[i]["name"].asString();
            value->value = custVar[i]["value"].asString();
            value->type = custVar[i]["type"].asUInt();
            value->expire = custVar[i]["expire"].asUInt();
            mymap.insert(std::pair<std::string, CUST_VAR_SP>(value->name, value));
        }
        item->SetCustVars(mymap);
    }
    return item->GetGUIDAsString();
    SAFE_END_EX("")
}

bool LuaHost::Item_SetSubType(const std::string& guid, const std::string & belong,uint16_t subtype)
{
    SAFE_BEGIN_EX
    auto* player = GetPlayerByGuid(belong);
    if (nullptr == player) return false;

    auto* rolepack = player->GetRolePack();
    if (!rolepack) return false;

    auto obj = NewLuaObj();
    obj["SubType"] = subtype;
    return rolepack->SetItemCfg(std::stoull(guid), obj);

    /*
    auto* item = player->GetRolePack()->FindItem(std::stoull(guid));
    if (!item) return false;

    item->SetSubType(subtype);
    return true;
    */
    SAFE_END_EX(false)
}

bool LuaHost::Item_SetName(const std::string& playerguid, const std::string& guid ,const std::string& Name)
{
    SAFE_BEGIN_EX
    if (Name .size() > MAX_ROLE_NAME_LENGTH) return false;
    auto *player = GetPlayerByGuid(playerguid);
    if (!player) return false;

    auto *rolepack = player->GetRolePack();
    if (!rolepack) return false;

    auto obj = NewLuaObj();
    obj["Name"] = Name;
    return rolepack->SetItemCfg(std::stoull(guid), obj);
    /*
    auto *item = rolepack->FindItem(std::stoull(guid));
    if (!item) return false;

    item->SetName(Name);
    auto site = item->GetSite();
    rolepack->NtfMasterUpdateItem(site);

    return true;
    */
    SAFE_END_EX(false)
}

bool LuaHost::Item_IsBind(const std::string &itemGUID)
{
    SAFE_BEGIN_EX;
    auto *inst = ItemMap::GetInstance();
    if (!inst) return false;

    auto guid = stoull_s(itemGUID);
    auto *item = inst->GetItem(guid);
    if (!item) return false;

    auto *roleItem = dynamic_cast<RoleItem *>(item);
    if (!roleItem) return false;

    return roleItem->GetIsBind();
    SAFE_END_EX(false);
}

void LuaHost::Log_ActivityData(const string& an, const string& rn, const string& roleguid, const CLuaObject& itemInfo, const CLuaObject& goldInfo)
{
    SAFE_BEGIN_EX
    auto guid = std::stoull(roleguid);
    std::vector<log_item_params> lips = ParseItemLogParams(itemInfo, goldInfo);
    uint64_t logGuid = GenerateObjID(static_cast<EObjType>(E_LOG_OBJ_ACTIVITY), ConfigInfo::GetInstance());
    if (lips.size())
    {
        for (auto iter = lips.begin(); iter != lips.end(); ++iter)
        {
            SendDBLogData(log_type_activity_data, LogActivityData(an, rn, logGuid, guid, iter->itemKeyname, iter->itemNum));
        }
    }
    else
    {
        SendDBLogData(log_type_activity_data, LogActivityData(an, rn, logGuid, guid, "", 0));
    }
    SAFE_END_EX()
}

void LuaHost::Log_RewardData(const string& rn, const string& roleguid, const CLuaObject& itemInfo, const CLuaObject& goldInfo)
{
    SAFE_BEGIN_EX
    auto guid = std::stoull(roleguid);
    std::vector<log_item_params> lips = ParseItemLogParams(itemInfo, goldInfo);
    uint64_t logGuid = GenerateObjID(static_cast<EObjType>(E_LOG_OBJ_REWARD), ConfigInfo::GetInstance());
    if (lips.size())
    {
        for (auto iter = lips.begin(); iter != lips.end(); ++iter)
        {
            SendDBLogData(log_type_reward_data, LogRewardData(rn, logGuid, guid, iter->itemKeyname, iter->itemNum));
        }
    }
    else
    {
        SendDBLogData(log_type_reward_data, LogRewardData(rn, logGuid, guid, "", 0));
    }
    SAFE_END_EX()
}

void LuaHost::Log_GiftPackData(const string& gn, const string& roleguid, const CLuaObject& itemInfo, const CLuaObject& goldInfo)
{
    SAFE_BEGIN_EX
    auto guid = std::stoull(roleguid);
    std::vector<log_item_params> lips = ParseItemLogParams(itemInfo, goldInfo);
    uint64_t logGuid = GenerateObjID(static_cast<EObjType>(E_LOG_OBJ_GIFTPACK), ConfigInfo::GetInstance());
    if (lips.size())
    {
        for (auto iter = lips.begin(); iter != lips.end(); ++iter)
        {
            SendDBLogData(log_type_giftpack_data, LogGiftPackData(gn, logGuid, guid, iter->itemKeyname, iter->itemNum));
        }
    }
    else
    {
        SendDBLogData(log_type_giftpack_data, LogGiftPackData(gn, logGuid, guid, "", 0));
    }
    SAFE_END_EX()
}

void LuaHost::Log_RecoveryData(const string& roleguid, const CLuaObject& itemInfo, const CLuaObject& goldInfo)
{
    SAFE_BEGIN_EX
    auto guid = std::stoull(roleguid);
    std::vector<log_item_params> lips = ParseItemLogParams(itemInfo, goldInfo);
    uint64_t logGuid = GenerateObjID(static_cast<EObjType>(E_LOG_OBJ_RECOVERY), ConfigInfo::GetInstance());
    if (lips.size())
    {
        for (auto iter = lips.begin(); iter != lips.end(); ++iter)
        {
            SendDBLogData(log_type_recovery_data, LogRecoveryData(logGuid, guid, iter->itemKeyname, iter->itemNum));
        }
    }
    else
    {
        SendDBLogData(log_type_recovery_data, LogRecoveryData(logGuid, guid, "", 0));
    }
    SAFE_END_EX()
}

bool LuaHost::StartCastleWar(const CLuaObject &guildNames, const std::string &startTime, uint32_t duration)
{
    SAFE_BEGIN_EX;

    std::vector<std::string> guilds;

    for (luabind::iterator it(guildNames), end; it != end; ++it) {

        auto obj = *it;
        if (luabind::type(obj) != LUA_TSTRING) return false;

        auto guild = luabind::object_cast<std::string>(obj);
        guilds.emplace_back(std::move(guild));
    }

    auto nStartTime = ITimeHelper::GetInstance()->ConvertStringToTime(startTime);

    return CastleWarMgr::GetInstance()->StartCastleWar(std::move(guilds), nStartTime, duration);

    SAFE_END_EX(false);
}

bool LuaHost::StopCastleWar()
{
    return CastleWarMgr::GetInstance()->StopCastleWar();
}

CLuaObject LuaHost::GetCastleAttackFamily()
{
    auto obj = NewLuaObj();

    const auto &guilds = CastleWarMgr::GetInstance()->QueryEngagedGuilds();
    for (auto i = 0; i < guilds.size(); ++i) {
        obj[i+1] = guilds[i];
    }

    return obj;
}

std::string LuaHost::GetCastleOwnFamily()
{
    return CastleWarMgr::GetInstance()->GetWinner();
}

void LuaHost::SetCastleOwnFamily(std::string guildName)
{
    CastleWarMgr::GetInstance()->SetWinner(std::move(guildName));
}

std::string LuaHost::QueryCastleStart()
{
    auto startTime = CastleWarMgr::GetInstance()->QueryStartTime();
    if (startTime == 0) return "";
    return ITimeHelper::GetInstance()->ConvertTimeToString(startTime);
}

bool LuaHost::IsCastleWarStart()
{
    return CastleWarMgr::GetInstance()->IsInWar();
}


void LuaHost::SetMaxImageCount(uint32_t num)
{
    MapRoleMgr::GetInstance()->SetMaxImageCount(num);
}

void LuaHost::GenCastleMonster(uint32_t type)
{
    CastleWarMgr::GetInstance()->GenCastleMonster(type);
}

CLuaObject LuaHost::GetWantedList()
{
    SAFE_BEGIN_EX;

    auto luaWantedList = NewLuaObj();

    const auto &wantedList = WantedList::GetInstance()->GetWantedList();

    int n = 0;
    for (const auto &spWanted : wantedList) {

        auto luaWanted = NewLuaObj();

        uint32_t bounty = 0;
        uint64_t ptime = 0;
        auto desc = NewLuaObj();

        int i = 0;
        for (const auto &spWantedBy : spWanted->wanted_by_list) {
            bounty += spWantedBy->bounty;
            if (i < 3) desc[++i] = spWantedBy->desc;
            if (ptime == 0) ptime = spWantedBy->ptime;
        }

        luaWanted["guid"] = std::to_string(spWanted->guid);
        luaWanted["name"] = spWanted->name;
        luaWanted["online"] = MapRoleMgr::GetInstance()->IsPlayerOnline(spWanted->guid);
        luaWanted["bounty"] = bounty;
        luaWanted["desc"] = desc;
        luaWanted["time"] = std::to_string(ptime);

        luaWantedList[++n] = luaWanted;
    }

    return luaWantedList;

    SAFE_END_EX(NewLuaObj());
}

void LuaHost::PostBounty(const std::string &wantedByGUID, const std::string &wantedName, uint32_t bounty, const std::string &desc)
{
    ProtoMS_PostBountyReq data;

    data.wanted_by_guid = std::stoull(wantedByGUID);

    auto *player = MapRoleMgr::GetInstance()->FindPlayer(data.wanted_by_guid);
    if (player) {
        strcpy_s(data.wanted_by_name, _countof(data.wanted_by_name), player->GetName().c_str());
    }

    strcpy_s(data.wanted_name, _countof(data.wanted_name), wantedName.c_str());
    data.bounty = bounty;
    strcpy_s(data.desc, _countof(data.desc), desc.c_str());
    data.ptime = time(nullptr);

    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

CLuaObject LuaHost::GetRebateMoneyInfo(const std::string& roleGuid)
{
    SAFE_BEGIN_EX;
    auto guid = std::stoull(roleGuid);
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(guid);
    if (!player) return NewLuaObj();

    return player->GetRebateMoneyInfo();
    SAFE_END_EX(NewLuaObj());
}

void LuaHost::GetRebateMoney(const std::string& roleGuid)
{
    SAFE_BEGIN_EX;
    auto guid = std::stoull(roleGuid);
    auto* player = MapRoleMgr::GetInstance()->FindPlayer(guid);
    if (!player) return;

    player->GetRebateMoney();
    SAFE_END_EX();
}
void LuaHost::SetMoveMistake(uint32_t num)
{
    MapServer::GetInstance()->SetMoveMistake(num);
}

std::string LuaHost::Getmicrosecond()
{
    return std::to_string(GetTimeStampMillisecond3()); ;
}

std::string LuaHost::BigNumberCalculation(const std::string& numstr1, const std::string& numstr2, int type)
{
    auto num1 = std::stoull(numstr1);
    auto num2 = std::stoull(numstr2);
    if (type == 1)
    {
        return std::to_string(num1 + num2);
    }
    else if(type == 2)
    {
        return std::to_string(num1 - num2);
    }
    else if (type == 3)
    {
        return std::to_string(num1 * num2);
    }
    else
    {
        return std::to_string(num1 / num2);
    }
   
}