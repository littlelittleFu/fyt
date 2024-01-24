#include"stdafx.h"
#include"CustomEquipSiteAndSub.h"

IMPL_SINGLETON(CustomEquipSiteAndSub)

bool CustomEquipSiteAndSub::FindSiteBySub(uint16_t sub, vecEQUIP_SITE_TABLE& vec)
{
	if (mTable.empty())return false;

	auto it = mTable.find(sub);
	if (it == mTable.end())return false;
	vec.assign(it->second.begin(), it->second.end());
	return true;
}

bool CustomEquipSiteAndSub::SetSubSite(uint16_t sub, vecEQUIP_SITE_TABLE table)
{
	if (!mTable.empty()) 
	{
		auto it = mTable.find(sub);
		if (it != mTable.end())return false;
	}
	mTable[sub] = std::move(table);
	return true;
}