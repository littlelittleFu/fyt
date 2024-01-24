#pragma once

enum EObjType {
    E_OBJ_NULL = 0,
    E_OBJ_DUMMY = 1,
    E_OBJ_PLAYER = 2,                   // 为了生成的role uuid的高位是1
    E_OBJ_MONSTER,
    E_OBJ_NPC,
    E_OBJ_ITEM,
    E_OBJ_MAP,
    E_OBJ_TEAM,
    E_OBJ_GUILD,
    E_OBJ_EVENT,
    E_OBJ_SCENEMAGIC,
    E_OBJ_SYSTEM,
    E_OBJ_BUFF,
    E_OBJ_MAIL,
    E_OBJ_MARKET,
    E_OBJ_AUCTION,
    E_OBJ_PET,
    E_OBJ_ELITE_MONSTER,                // 暂时不用
    E_OBJ_STALL_DUMMY,
    E_OBJ_PLAYER_DOPLGANR,             // 玩家分身
    E_OBJ_TYPE_NUM
};
// 日志的单独拎出来,给EObjType省点bit位
enum ELogObjType {
    E_LOG_OBJ_NULL = 0,
    E_LOG_OBJ_ACTIVITY = 16,             // 活动日志
    E_LOG_OBJ_REWARD = 17,               // 奖励领取
    E_LOG_OBJ_GIFTPACK = 18,             // 礼包购买
    E_LOG_OBJ_RECOVERY = 19,             // 回收
};

/* new version */
#define GUID_BEGIN_TIME  1672531200 // 2023-01-01 08:00:00
#define GUID_TYPE_PART(guid)    (EObjType)((uint64_t(guid)  >> 59)  & uint64_t(0x000000000000001F))
#define GUID_TIME_PART(guid)    GetTimePart(guid)

#define IS_PLAYER_GUID(guid) ((GUID_TYPE_PART(guid) == E_OBJ_PLAYER) && guid)
#define IS_DUMMY_GUID(guid) ((GUID_TYPE_PART(guid) == E_OBJ_DUMMY) && guid)
#define IS_NPC_GUID(guid) (GUID_TYPE_PART(guid) == E_OBJ_NPC)
#define IS_ELITE_MONSTER_GUID(guid) (GUID_TYPE_PART(guid) == E_OBJ_ELITE_MONSTER)
#define IS_MONSTER_GUID(guid) (GUID_TYPE_PART(guid) == E_OBJ_MONSTER || GUID_TYPE_PART(guid) == E_OBJ_ELITE_MONSTER)
#define IS_ITEM_GUID(guid) (GUID_TYPE_PART(guid) == E_OBJ_ITEM)
#define IS_MAP_GUID(guid) (GUID_TYPE_PART(guid) == E_OBJ_MAP)
#define IS_GUILD_GUID(guid) (GUID_TYPE_PART(guid) == E_OBJ_GUILD)
#define IS_TEAM_GUID(guid) (GUID_TYPE_PART(guid) == E_OBJ_TEAM)
#define IS_CLIENT_PLAYER_GUID(guid) (IS_PLAYER_GUID(guid) || IS_DUMMY_GUID(guid))
#define IS_PET_GUID(guid) (GUID_TYPE_PART(guid) == E_OBJ_PET)
#define IS_STALL_DUMMY_GUID(guid) (GUID_TYPE_PART(guid) == E_OBJ_STALL_DUMMY)
#define IS_PLAYER_DOPLGANR_GUID(guid) (GUID_TYPE_PART(guid) == E_OBJ_PLAYER_DOPLGANR)
#define IS_ROLE_GUID(guid) (IS_PLAYER_GUID(guid) || IS_MONSTER_GUID(guid) || IS_NPC_GUID(guid) || \
                            IS_STALL_DUMMY_GUID(guid) || IS_PLAYER_DOPLGANR_GUID(guid) || IS_PET_GUID(guid))

class IConfigInfo;
uint64_t GenerateObjID(EObjType nObjType, IConfigInfo*);
uint64_t GetTimePart(uint64_t guid);