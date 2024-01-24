/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once
#include <string>
#include <map>
#include <vector>


namespace DATA
{
struct StallRegion
{
	RegionCommon m_Region;
};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma warning( push )
#pragma warning( disable : 4996 )
#endif

class StallRegionConfig : public RegionBase<StallRegion>
{
    DECLARE_SINGLETON(StallRegionConfig);
};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma warning( pop )
#endif

#define sStallRegionConfig (*DATA::StallRegionConfig::Instance())
}

