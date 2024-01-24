#include "stdafx.h"
#include "MapGrid.h"
#include "ILogHelper.h"
#include "IFileHelper.h"
#include "fcaseopen.h"

const std::string PLAINTEXT_PREFIX("guanying");
#define MAPGRID_DATA (mData.get() + mOffset)

MapGrid::MapGrid()
{
}

MapGrid::~MapGrid()
{
}

bool MapGrid::Init(const char *name)
{
    if (!name) return false;

	std::string path = ConfigInfo::GetInstance()->m_sMapGridFolderPath + name + ".grid";

#ifdef __linux__
    path = gbk_to_utf8(path);
#endif

	auto *file = fcaseopen(path.c_str(), "rb");
	if (!file) {
		LOG_ERROR("fcaseopen failed. path: %s", path.c_str());
		return false;
	}

    auto deleter = [](FILE *file) { if (file) fclose(file); };
    std::unique_ptr<FILE, decltype(deleter)> autoclose(file, deleter);

    fseek(file, 0, SEEK_END);
	auto fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

    if (fileSize < MINFILESZ) {
        LOG_ERROR("Invalid file size. path: %s", path.c_str());
        return false;
    }


    unique_ptr<uint8_t[]> cypher = std::make_unique<uint8_t[]>(fileSize);
    unique_ptr<uint8_t[]> plain;
    if (fread(cypher.get(), 1, fileSize, file) != fileSize) {
        LOG_ERROR("fread failed. path: %s", path.c_str());
        return false;
    }

    std::string prefix((char*)cypher.get(), PLAINTEXT_PREFIX.size());
    bool res = false;
    if (PLAINTEXT_PREFIX != prefix)
    {
        res = LoadCypher(fileSize, cypher, plain);
    }
    else
    {
        res = LoadPlain(fileSize, cypher, plain);
        mOffset = PLAINTEXT_PREFIX.size();
    }
    if (!res) return false;

    auto* p = reinterpret_cast<uint32_t *>(plain.get() + mOffset);
    const auto width = *p;
    const auto height = *(p + 1);

    if (fileSize < MINFILESZ + width * height * 4 + mOffset) {
        LOG_ERROR("Invalid file size. path: %s", path.c_str());
        return false;
    }

    mData = std::move(plain);
    return true;
}

bool MapGrid::LoadCypher(uint32_t fileSize, unique_ptr<uint8_t[]>& cypher, unique_ptr<uint8_t[]>& plain)
{
    plain = std::make_unique<uint8_t[]>(fileSize);
    const uint8_t key[32] = {
        0x48, 0x3F, 0x7C, 0x9F, 0x15, 0x74, 0x61, 0x4A, 0xDE, 0x86, 0x73, 0x30, 0xB7, 0xCC, 0xD8, 0xFE,
        0xE6, 0xCE, 0xA2, 0x9C, 0x54, 0x55, 0x00, 0x22, 0x94, 0x8E, 0xA0, 0x8A, 0x89, 0x58, 0x61, 0xCD
    };
    AES aes;
    aes.SetParam("cfb", 128, key, _countof(key), nullptr, 0);
    auto result = aes.Decrypt(cypher.get(), fileSize, plain.get());
    if (result < 0) {
        LOG_ERROR("Decrypt failed with error %d", result);
        return false;
    }
    return true;
}

bool MapGrid::LoadPlain(uint32_t fileSize, unique_ptr<uint8_t[]>& cypher, unique_ptr<uint8_t[]>& plain)
{
    plain.reset(cypher.release());
    return true;
}

uint32_t MapGrid::GetWidth()
{
    if (!mData) return 0;
    auto *p = reinterpret_cast<uint32_t *>(MAPGRID_DATA);
    return *p;
}

uint32_t MapGrid::GetHeight()
{
    if (!mData) return 0;
    auto *p = reinterpret_cast<uint32_t *>(MAPGRID_DATA);
    return *(p + 1);
}

uint32_t MapGrid::GetGridWidth()
{
    if (!mData) return 0;
    auto *p = reinterpret_cast<uint32_t *>(MAPGRID_DATA);
    return *(p + 2);
}

uint32_t MapGrid::GetGridHeight()
{
    if (!mData) return 0;
    auto *p = reinterpret_cast<uint32_t *>(MAPGRID_DATA);
    return *(p + 3);
}

bool MapGrid::IsForbid_PlayerMoveAck(int x, int y, Role* role)
{
    if (!role) return true;
    auto map = role->GetCurMap();
	if (!map) return true;

    if (IsForbid(x, y)) {
        if (IsOnlyForbid(x, y)) return !role->CheckCross();

        // 检测穿人穿怪
        auto canThrough = false;
        auto canThroughMonste = false;
        auto canThroughNPC = false;
        auto canThroughStallDummy = false;
        auto cfg = map->GetMapConfig();
        if (cfg)
        {
            canThrough = cfg->CrossHuman > 0;
            canThroughMonste = cfg->CrossMonster > 0;
        }
        if (map->IsTypeRegion(x, y, region_safe))
        {
            canThrough = sGlobalConfig.GetData()->SafeRegionCanThroughHuman > 0 ? true : canThrough;
            canThroughMonste = sGlobalConfig.GetData()->SafeRegionCanThroughMonster > 0 ? true : canThroughMonste;
        }
        else
        {
            canThrough = role->GetRoleProp(role_can_through) > 0 ? true : canThrough;
            canThroughMonste = role->GetRoleProp(role_can_through_monster) > 0 ? true : canThroughMonste;
        }
        // 不能穿人
        if (!canThrough && IsDPForbid(x, y)) return true;
        // 不能穿怪
        if (!canThroughMonste && IsDMForbid(x, y)) return true;
        // 不能NPC
        if (!canThroughNPC && IsNPCForbid(x, y)) return true;
        // 不能摆摊
        if (!canThroughStallDummy && IsSDForbid(x, y)) return true;
    }

	return false;
}

void MapGrid::SetFlag(int x, int y, uint32_t flag, bool set)
{
    auto *p = GetGridData(x, y);
    if (!p) return;
    set ? (*p |= flag) : (*p &= ~flag);
}

bool MapGrid::IsFlagSet(int x, int y, uint32_t flag)
{
    auto *p = GetGridData(x, y);
    if (!p) return true;
    return (*p & flag);
}

uint32_t * MapGrid::GetGridData(int x, int y)
{
    if (!mData) return nullptr;

    auto width = GetWidth();
    auto height = GetHeight();
    if (x < 0 || x >= width) return nullptr;
    if (y < 0 || y >= height) return nullptr;

    auto *p = reinterpret_cast<uint32_t *>(MAPGRID_DATA);
    return (p + 4 + y * width + x);
}