#pragma once

#include <vector>
#include <list>

#include"DataInfo.hpp"
#include "ProtoMS.h"
#include "ProtoCS.h"
#include "ProtoGS.h"


class TopList
{
	DECL_SINGLETON(TopList)
public:
	TopList();
	~TopList();
	void AddTopList(uint8_t type, uint64_t* rolelist, TOPLIST_INFO* topList,uint8_t topListNum);
	void AddTmpTopList(const ROLE_BRIEF_INFO& roleBriefInfo);
	void TopListRange();
	void LevelRange(uint8_t type);
	void Update(ProtoMS_UpdateTopListAck *ack);
	void SendTopList(ProtoGS_TopListReq* req);
	void SetHas(bool tmp) { has = tmp; };
	bool GetHas() { return has; };

	void ChangeNameInfo(uint64_t guid, const std::string& name, const std::string& orgName);

public:
	bool has = false;
	uint32_t mFlashTimerID;
	std::map<uint64_t, TOPLIST_INFO*> mTopList;
	std::vector<TOPLIST_INFO*> mTopListRange[sort_type_max];
};