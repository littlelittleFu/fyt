#pragma once

#include <string>
#include "Map.h"
#include "AStarPathFinder.h"
#define TILE_PROP_TEXBIT 4 // 地质类型占位数
#define TILE_PROP_TEX_MASK (((unsigned int)-1) >> TILE_PROP_TEXBIT)
#define MAKETEXPROP(x) ((x) << (32 - TILE_PROP_TEXBIT))
#define GETTEXPROP(x) ((x) >> (32 - TILE_PROP_TEXBIT))
#define TEXTYPE_MIN 0
#define TEXTYPE_MAX ((1 << (TILE_PROP_TEXBIT + 1)) - 1)

#define MAPSND_MIN 0
#define MAPSND_MAX ((unsigned char)-1)

class CAStarPathFinder;
enum GridType
{
    GRID_TYPE_FORBID = (1 << 0) /*0x00000001*/,                         // 物理阻挡
    GRID_TYPE_MFORBID = (1 << 1) /*0x00000002*/,                        // 魔法阻挡
    GRID_TYPE_PENETRABLE = (1 << 3) /*0x00000008*/,                     // 可穿透
    GRID_TYPE_JUMPPOINT = (1 << 4) /*0x00000010*/,                      // 跳转
    GRID_TYPE_RELIVEZONE = (1 << 5) /*0x00000020*/,                     // 复活区
    GRID_TYPE_BAITANZONE = (1 << 6) /*0x00000040*/,                     // 摆摊区
    GRID_TYPE_SAFEZONE = (1 << 8) /*0x00000080*/,                       // 安全区
    GRID_TYPE_FISHPRO = (1 << 11) /*0x00000004*/,                       // 是否是钓鱼点
    GRID_TYPE_DICKPRO = (1 << 10) /*0x00000008*/,                       // 是否是挖矿点
    GRID_TYPE_WOODPRO = (1 << 12) /*0x00000010*/,                       // 是否是伐木点
    GRID_TYPE_DRUGPRO = (1 << 13) /*0x00000020*/,                       // 是否是采药点
    GRID_TYPE_GUIDEPOINT = (1 << 14) /*0x00000040*/,                    // 是否是导航点
    GRID_TYPE_NPCPOINT = (1 << 20) /*0x00000040*/,                      // 是否是NPC点
    GRID_TYPE_GHOST = (1 << 21),	//是否隐身
    GRID_TYPE_ROUTINE = (1 << 22),	//特殊路径点
    GRID_TYPE_DYNAMIC_MONSTER = (1 << 23),	// 是否是动态怪物点
    GRID_TYPE_DYNAMIC_PLAYER = (1 << 24),	// 是否是动态玩家点
    GRID_TYPE_STALL_DUMMY = (1 << 25),	    // 摆摊模型点
    GRID_TYPE_TEXPRO = (((unsigned int)-1) << (32 - TILE_PROP_TEXBIT)), // 是否指定地表材质(一一对应音效)种类
};

class MapGrid
{
    enum {
        MINFILESZ = 16
    };

public:
	MapGrid();
	~MapGrid();

    bool Init(const char *name);

    uint32_t GetWidth();
    uint32_t GetHeight();
    uint32_t GetGridWidth();
    uint32_t GetGridHeight();

    void SetSDForbid(int x, int y) { SetFlag(x, y, GRID_TYPE_STALL_DUMMY, true); }
    void RemoveSDForbid(int x, int y) { SetFlag(x, y, GRID_TYPE_STALL_DUMMY, false); }
    bool IsSDForbid(int x, int y) { return IsFlagSet(x, y, GRID_TYPE_STALL_DUMMY); }

    void SetNPCForbid(int x, int y) { SetFlag(x, y, GRID_TYPE_NPCPOINT, true); }
    void RemoveNPCForbid(int x, int y) { SetFlag(x, y, GRID_TYPE_NPCPOINT, false); }
    bool IsNPCForbid(int x, int y) { return IsFlagSet(x, y, GRID_TYPE_NPCPOINT); }

    void SetDMForbid(int x, int y) { SetFlag(x, y, GRID_TYPE_DYNAMIC_MONSTER, true); }
    void RemoveDMForbid(int x, int y) { SetFlag(x, y, GRID_TYPE_DYNAMIC_MONSTER, false); }
    bool IsDMForbid(int x, int y) { return IsFlagSet(x, y, GRID_TYPE_DYNAMIC_MONSTER); }

    void SetDPForbid(int x, int y) { SetFlag(x, y, GRID_TYPE_DYNAMIC_PLAYER, true); }
    void RemoveDPForbid(int x, int y) { SetFlag(x, y, GRID_TYPE_DYNAMIC_PLAYER, false); }
    bool IsDPForbid(int x, int y) { return IsFlagSet(x, y, GRID_TYPE_DYNAMIC_PLAYER); }
    bool IsOnlyDPForbid(int x, int y) { return IsFlagSet(x, y, GRID_TYPE_DYNAMIC_PLAYER) && !IsFlagSet(x, y, GRID_TYPE_DYNAMIC_MONSTER)
        && !IsFlagSet(x, y, GRID_TYPE_STALL_DUMMY) && !IsFlagSet(x, y, GRID_TYPE_NPCPOINT); }

    void SetForbid(int x, int y) { SetFlag(x, y, GRID_TYPE_FORBID, true); }
    void RemoveForbid(int x, int y) { SetFlag(x, y, GRID_TYPE_FORBID, false); }
    bool IsForbid(int x, int y) { return IsFlagSet(x, y, GRID_TYPE_FORBID) || IsFlagSet(x, y, GRID_TYPE_DYNAMIC_MONSTER) || IsFlagSet(x, y, GRID_TYPE_DYNAMIC_PLAYER)
        || IsFlagSet(x, y, GRID_TYPE_STALL_DUMMY) || IsFlagSet(x, y, GRID_TYPE_NPCPOINT); }
    bool IsOnlyForbid(int x, int y) { return IsFlagSet(x, y, GRID_TYPE_FORBID); }

    void SetMForbid(int x, int y) { SetFlag(x, y, GRID_TYPE_MFORBID, true); }
    void RemoveMForbid(int x, int y) { SetFlag(x, y, GRID_TYPE_MFORBID, false); }
    bool IsMForbid(int x, int y) { return IsFlagSet(x, y, GRID_TYPE_MFORBID); }

    void SetJPForbid(int x, int y) { SetFlag(x, y, GRID_TYPE_JUMPPOINT, true); }
    void RemoveJPForbid(int x, int y) { SetFlag(x, y, GRID_TYPE_JUMPPOINT, false); }
    bool IsJPForbid(int x, int y) { return IsFlagSet(x, y, GRID_TYPE_JUMPPOINT); }

    bool IsForbid_PlayerMoveAck(int x, int y , Role* role);

private:
    void SetFlag(int x, int y, uint32_t flag, bool set);
    bool IsFlagSet(int x, int y, uint32_t flag);
    uint32_t * GetGridData(int x, int y);

    bool LoadCypher(uint32_t fileSize, unique_ptr<uint8_t[]>& cypher, unique_ptr<uint8_t[]>& plain);
    bool LoadPlain(uint32_t fileSize, unique_ptr<uint8_t[]>& cypher, unique_ptr<uint8_t[]>& plain);
private:
    std::unique_ptr<uint8_t[]> mData;
    uint8_t mOffset = 0;
};
