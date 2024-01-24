#pragma once

using vecEQUIP_SITE_TABLE = vector<uint16_t>;
using mapEQUIP_SITE_TABLE = map<uint16_t, vecEQUIP_SITE_TABLE>;

class CustomEquipSiteAndSub
{
	DECL_SINGLETON(CustomEquipSiteAndSub)
private:
	CustomEquipSiteAndSub() {};
	~CustomEquipSiteAndSub() {};
public:
	bool FindSiteBySub(uint16_t sub, vecEQUIP_SITE_TABLE& vec);
	bool SetSubSite(uint16_t sub,vecEQUIP_SITE_TABLE table);


private:
	mapEQUIP_SITE_TABLE mTable;
};
