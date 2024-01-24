#include "stdafx.h"
#include "GameCfgMgr.h"
#include "IFileHelper.h"

template <typename T>
bool LoadCfg(const char *fileName)
{
    if (!fileName) return false;

    T::DestoryInstance();
    if (!T::CreateInstance()) {
        LOG_ERROR("CreateInstance failed. fileName: %s", fileName);
        return false;
    }

    auto filePath = GameCfgMgr::GetInstance()->GetGameCfgFolderPath() + fileName + ".csv";
    if (!T::Instance()->Load(filePath)) {
        LOG_ERROR("Load %s failed", filePath.c_str());
        return false;
    }

    return true;
}


IMPL_SINGLETON(GameCfgMgr);

GameCfgMgr::GameCfgMgr()
{
}

bool GameCfgMgr::LoadAllCfg()
{
    if (mGameCfgFolderPath.empty()) return false;

    bool result = true;

    if (!LoadCfgFromCSV()) result = false;

    return result;
}

bool GameCfgMgr::ReloadAllCfg()
{
    return LoadAllCfg();
}

bool GameCfgMgr::LoadCfgFromCSV()
{
    using namespace DATA;

    bool result = true;

    if (!LoadCfg<AthleticsRegionConfig>("athletics_region")) result = false;

    if (!LoadCfg<BornRegionConfig>("born_region")) result = false;

    if (!LoadCfg<BuffConfig>("buff")) result = false;

    if (!LoadCfg<BuffGroupConfig>("buff_group")) result = false;

    if (!LoadCfg<DropplusConfig>("dropplus")) result = false;

    if (!LoadCfg<GlobalConfig>("global")) result = false;

    if (!LoadCfg<GMCmdConfig>("gmcmd")) result = false;

    if (!LoadCfg<ItemConfig>("item")) result = false;

    if (!LoadCfg<JumpConfig>("jump")) result = false;

    if (!LoadCfg<MallConfig>("mall")) result = false;

    if (!LoadCfg<MapConfig>("map")) result = false;

    if (!LoadCfg<DropConfig>("mondrop")) result = false;

    if (!LoadCfg<MonsterConfig>("monster")) result = false;

    if (!LoadCfg<MonsterGenConfig>("monster_gen")) result = false;

    if (!LoadCfg<NpcConfig>("npc")) result = false;

    if (!LoadCfg<NpcGenConfig>("npc_gen")) result = false;

    if (!LoadCfg<RedNameRegionConfig>("red_name_region")) result = false;

    if (!LoadCfg<ReliveRegionConfig>("relive_region")) result = false;

    if (!LoadCfg<RoleConfig>("role")) result = false;

    if (!LoadCfg<RoleMGModConfig>("role_gm_mod")) result = false;

    if (!LoadCfg<SafeRegionConfig>("safe_region")) result = false;

    if (!LoadCfg<ShabakConfig>("shabak")) result = false;

    if (!LoadCfg<ShopConfig>("shop")) result = false;

    if (!LoadCfg<SkillConfig>("skill")) result = false;

    if (!LoadCfg<StallRegionConfig>("stall_region")) result = false;

    if (!LoadCfg<VipConfig>("vip")) result = false;

    if (!LoadCfg<GroupAttrConfig>("group_attr")) result = false;

    if (!LoadCfg<QuestTemplate>("quest")) result = false;

    //if (!LoadCfg<PlayerDropConfig>("playerdrop")) result = false;

    if (!LoadCfg<TitleConfig>("title")) result = false;

    if (!LoadCfg<SuitConfig>("suit")) result = false;

    if (!LoadCfg<IllegalCharactersConfig>("illegal_characters")) result = false;


    return result;
}

bool GameCfgMgr::ReloadSingleCfg(const std::string &name)
{
    using namespace DATA;

    if (name == "athletics_region") {
        return LoadCfg<AthleticsRegionConfig>("athletics_region");
    }
    else if (name == "born_region") {
        return LoadCfg<BornRegionConfig>("born_region");
    }
    else if (name == "buff") {
        return LoadCfg<BuffConfig>("buff");
    }
    else if (name == "buff_group") {
        return LoadCfg<BuffGroupConfig>("buff_group");
    }
    else if (name == "dropplus") {
        return LoadCfg<DropplusConfig>("dropplus");
    }
    else if (name == "global") {
        return LoadCfg<GlobalConfig>("global");
    }
    else if (name == "gmcmd") {
        return LoadCfg<GMCmdConfig>("gmcmd");
    }
    else if (name == "item") {
        return LoadCfg<ItemConfig>("item");
    }
    else if (name == "jump") {
        return LoadCfg<JumpConfig>("jump");
    }
    else if (name == "mall") {
        return LoadCfg<MallConfig>("mall");
    }
    else if (name == "map") {
        return LoadCfg<MapConfig>("map");
    }
    else if (name == "mondrop") {
        return LoadCfg<DropConfig>("mondrop");
    }
    else if (name == "monster") {
        return LoadCfg<MonsterConfig>("monster");
    }
    else if (name == "monster_gen") {
        return LoadCfg<MonsterGenConfig>("monster_gen");
    }
    else if (name == "npc") {
        return LoadCfg<NpcConfig>("npc");
    }
    else if (name == "npc_gen") {
        return LoadCfg<NpcGenConfig>("npc_gen");
    }
    else if (name == "quest") {
        return LoadCfg<QuestTemplate>("quest");
    }
    else if (name == "red_name_region") {
        return LoadCfg<RedNameRegionConfig>("red_name_region");
    }
    else if (name == "relive_region") {
        return LoadCfg<ReliveRegionConfig>("relive_region");
    }
    else if (name == "role") {
        return LoadCfg<RoleConfig>("role");
    }
    else if (name == "role_gm_mod") {
        return LoadCfg<RoleMGModConfig>("role_gm_mod");
    }
    else if (name == "safe_region") {
        return LoadCfg<SafeRegionConfig>("safe_region");
    }
    else if (name == "shabak") {
        return LoadCfg<ShabakConfig>("shabak");
    }
    else if (name == "shop") {
        return LoadCfg<ShopConfig>("shop");
    }
    else if (name == "skill") {
        return LoadCfg<SkillConfig>("skill");
    }
    else if (name == "stall_region") {
        return LoadCfg<StallRegionConfig>("stall_region");
    }
    else if (name == "vip") {
        return LoadCfg<VipConfig>("vip");
    }
    else if (name == "group_attr") {
        return LoadCfg<GroupAttrConfig>("group_attr");
    }

    else if (name == "playerdrop") {
        return LoadCfg<PlayerDropConfig>("playerdrop");
    }
    else if (name == "title") {
        return LoadCfg<TitleConfig>("title");
    }  
    else if (name == "illegal_characters") {
        return LoadCfg<IllegalCharactersConfig>("illegal_characters");
    }return false;
}

bool GameCfgMgr::ReloadCfg(const std::vector<std::string> &files)
{
    bool result = true;

    for (const auto &file : files)
        if (!ReloadSingleCfg(file))
            result = false;

    return result;
}