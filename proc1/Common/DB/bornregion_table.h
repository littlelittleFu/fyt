/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once
#include <string>
#include <map>
#include <vector>

namespace DATA
{
struct BornRegion
{
	RegionCommon m_Region;
};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma warning( push )
#pragma warning( disable : 4996 )
#endif

class BornRegionConfig : public RegionBase<BornRegion>
{
    DECLARE_SINGLETON(BornRegionConfig);
};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma warning( pop )
#endif
#define sBornRegionConfig (*DATA::BornRegionConfig::Instance())
}

