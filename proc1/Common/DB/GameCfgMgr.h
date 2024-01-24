#ifndef CXX_DBMANAGER_H
#define CXX_DBMANAGER_H


#include "TableBase.h"
#include "RegionBase.h"
#include "regioncommon.h"


#include "world_icon_table.hpp"
#include "vipshop_table.hpp"
#include "vip_table.hpp"
#include "title_table.hpp"
#include "through_region.h"
#include "suit_table.hpp"
#include "stallregion_table.h"
#include "shop_table.hpp"
#include "saferegion_table.h"
#include "role_table.hpp"
#include "role_gm_mod.hpp"
#include "reliveregion_table.h"
#include "rednameregion_table.h"
#include "quest_template_parser.hpp"
#include "prompt_table.hpp"
#include "npc_table.hpp"
#include "npc_quest_binding_table.hpp"
#include "npc_gen_table.h"
#include "monster_table.hpp"
#include "monster_gen_table.h"
#include "mons_info_table.h"
#include "mapicon_table.hpp"
#include "map_table.hpp"
#include "mall_table.hpp"
#include "loading_up.h"
#include "jump_table.h"
#include "JoinHitTable.h"
#include "item_table.hpp"
#include "skill_table.hpp"
#include "item_refine_table.hpp"
#include "inner_force_table.hpp"
#include "icon_table.hpp"
#include "hero_table.hpp"
#include "hair_table.hpp"
#include "GMcmd.hpp"
#include "global.hpp"
#include "fashion_table.hpp"
#include "drop_table.hpp"
#include "DropPlus.h"
#include "castle_table.hpp"
#include "buff_table.hpp"
#include "bornregion_table.h"
#include "Avatar_table.hpp"
#include "att_table.hpp"
#include "athleticsregion_table.h"
#include "achievement_table.hpp"
#include "group_attr.hpp"
#include "buff_group_table.hpp"
#include "drop_table.hpp"
#include "DropPlus.h"
#include "shabak_table.hpp"
#include "quest_template_parser.hpp"
#include "playerdrop_table.hpp"
#include "illegal_characters_table.hpp"

class GameCfgMgr
{
    DECL_SINGLETON(GameCfgMgr);

protected:
    GameCfgMgr();

public:
    bool LoadAllCfg();
    bool ReloadAllCfg();
    bool ReloadSingleCfg(const std::string &name);
    bool ReloadCfg(const std::vector<std::string> &files);

    const std::string & GetGameCfgFolderPath() const { return mGameCfgFolderPath; }
    void SetGameCfgFolderPath(const std::string &path) { mGameCfgFolderPath = path; }

private:
    bool LoadCfgFromCSV();

private:
    std::string mGameCfgFolderPath;
};

#endif