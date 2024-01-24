/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once
#include <string>
#include <map>
#include <vector>

namespace DATA
{
struct SafeRegion
{
	RegionCommon m_Region;
};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma warning( push )
#pragma warning( disable : 4996 )
#endif

class SafeRegionConfig : public RegionBase<SafeRegion>
{
    DECLARE_SINGLETON(SafeRegionConfig);
};


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma warning( pop )
#endif
#define sSafeRegionConfig (*DATA::SafeRegionConfig::Instance())
}

