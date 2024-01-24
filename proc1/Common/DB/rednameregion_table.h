/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once
#include <string>
#include <map>
#include <vector>

namespace DATA
{
struct RedNameRegion
{
	RegionCommon m_Region;
};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma warning( push )
#pragma warning( disable : 4996 )
#endif

class RedNameRegionConfig : public RegionBase<RedNameRegion>
{
    DECLARE_SINGLETON(RedNameRegionConfig);
};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma warning( pop )
#endif
#define sRedNameRegionConfig (*DATA::RedNameRegionConfig::Instance())
}

