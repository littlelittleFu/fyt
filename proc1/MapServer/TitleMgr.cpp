#include "stdafx.h"
#include "TitleMgr.h"

TitleDataMgr::TitleDataMgr(Player* player):mMaster(player)
{
	assert(mMaster != nullptr);
}

TitleDataMgr::~TitleDataMgr()
{

}

void TitleDataMgr::Init()
{
	if (mTitleList.empty())return;
	for (auto& i : mTitleList) {
		auto titleCfg = sTitleConfig.GetByID(i.first);
		if (nullptr == titleCfg) continue;
		if (titleCfg->type == titile_subtype_no_wear ||
			(titleCfg->type == title_subtype_wear && i.second->isWear == title_wear)) {
			UpdateTitleProp(titleCfg->Id, titleCfg, title_prop_increase);
		}
		if (i.second->isWear == title_wear) {
			SendWearNtf(i.first);
		}
	}
}

void TitleDataMgr::Update(int delta)
{
	if (mTitleList.empty()) {
		mMaster->ResetNeedUpdateFlag(title_need_update_flag);
		return;
	}
	for (auto iter = mTitleList.begin(); iter != mTitleList.end();) {
		//limit为0 永久生成
		if (iter->second->timeLimit == 0) {
			++iter;
			continue;
		}

		iter->second->lifeTime += delta;

		if (IsExpired(iter->second)) {
			auto tmpIter = iter;
			++iter;
			DelTitle(tmpIter->second->Id);
			continue;
		}
		++iter;
	}
}

bool TitleDataMgr::AddTitle(DATA::Title* title)
{
	auto spTitleInfo = make_shared<TITLE_INFO>();
	spTitleInfo->Id = title->Id;
	spTitleInfo->isWear = false;
	spTitleInfo->addTime = ITimeHelper::GetInstance()->GetTimeStamp();
	spTitleInfo->lifeTime = 0;
	spTitleInfo->timeLimit = title->TimeLimit;
	mTitleList[title->Id] = spTitleInfo;
	SendAddTitleToClient(spTitleInfo);
	SendAddTitleToCS(spTitleInfo);
	mMaster->SetNeedUpdateFlag(title_need_update_flag);
	return true;
}

bool TitleDataMgr::AddTitle(uint32_t id)
{
	auto titleCfg = sTitleConfig.GetByID(id);
	if (titleCfg == nullptr)return false;

	if (!IsCanAdd(id)) return false;

	AddTitle(titleCfg);
	if (titleCfg->type == titile_subtype_no_wear) {
		UpdateTitleProp(id, titleCfg, title_prop_increase);
	}
	return true;
}

bool TitleDataMgr::AddTitle(const std::string& name)
{
	auto titleCfg = sTitleConfig.GetByKeyName(name);
	if (titleCfg == nullptr)return false;

	return AddTitle(titleCfg->Id);
}

bool TitleDataMgr::DelTitle(uint32_t id)
{
	auto titleCfg = sTitleConfig.GetByID(id);
	if (titleCfg == nullptr)return false;

	auto iter = mTitleList.find(id);
	if (iter == mTitleList.end())return false;

	if (iter->second->isWear == title_wear) {
		UnWearTitle(iter->second->Id);
	}

	if ((titleCfg->type == titile_subtype_no_wear)) {
		UpdateTitleProp(id, titleCfg, title_prop_decrease);
	}
	mTitleList.erase(iter);

	SendDelTitleToClient(id);
	SendDelTitleToCS(1, &id);
	return true;
}

bool TitleDataMgr::DelTitle(const std::string& name)
{
	auto titleCfg = sTitleConfig.GetByKeyName(name);
	if (titleCfg == nullptr)return false;

	return DelTitle(titleCfg->Id);
}

bool TitleDataMgr::WearTitle(uint32_t id)
{
	auto titleCfg = sTitleConfig.GetByID(id);
	if (nullptr == titleCfg)return false;

	auto iter = mTitleList.find(id);
	if (iter == mTitleList.end())return false;

	if (iter->second->isWear != title_unwear)return false;

	// 替换已经穿戴的称号
	auto needReplaceTitle = find_if(mTitleList.begin(), mTitleList.end(), [=](const std::pair<uint32_t, SP_TITLE_INFO> &spInfo) {
		auto curTitleCfg = sTitleConfig.GetByID(spInfo.second->Id);
		if (nullptr == curTitleCfg)return false;
		if (spInfo.second->isWear == title_wear && curTitleCfg->Priority == titleCfg->Priority)return true;
		return false;
		});

	if (needReplaceTitle != mTitleList.end()) {
		UnWearTitle(needReplaceTitle->second->Id);
	}

	// 穿戴新的称号
	iter->second->isWear = title_wear;

	if (titleCfg->type == title_subtype_wear) {
		UpdateTitleProp(id, titleCfg, title_prop_increase);
		TriggerEffect(id, titleCfg);
	}
	SendWearNtf(id);
	SendWearTypeTitleToCS(id, title_wear);
	return true;
}

bool TitleDataMgr::WearTitle(const std::string& name)
{
	auto titleCfg = sTitleConfig.GetByKeyName(name);
	if (titleCfg == nullptr)return false;

	return WearTitle(titleCfg->Id);
}

void TitleDataMgr::UnWearTitle(uint32_t id)
{
	auto titleCfg = sTitleConfig.GetByID(id);
	if (titleCfg == nullptr)return ;

	auto iter = mTitleList.find(id);
	if (iter == mTitleList.end())return;

	if (iter->second->isWear != title_wear)return;
	iter->second->isWear = title_unwear;

	// 穿戴逻辑
	if (titleCfg->type == title_subtype_wear) {
		UpdateTitleProp(id, titleCfg, title_prop_decrease);
		UnTriggerEffect(id, titleCfg);
	}

	SendUnWearNtf(id);
	SendWearTypeTitleToCS(id, title_unwear);
	return;
}

void TitleDataMgr::UnWearTitle(const std::string& name)
{
	auto titleCfg = sTitleConfig.GetByKeyName(name);
	if (titleCfg == nullptr)return;
	// 穿戴逻辑
	UnWearTitle(titleCfg->Id);
}

bool TitleDataMgr::IsExpired(SP_TITLE_INFO info)
{
	return IsExpired(info.get());
}

bool TitleDataMgr::IsExpired(TITLE_INFO* info)
{
	auto titleCfg = sTitleConfig.GetByID(info->Id);
	if (nullptr == titleCfg)return true;
	switch (titleCfg->UseAbsTime) {
	case time_type_relation:
	{
		if (info->lifeTime <= info->timeLimit) {
			return false;
		}
		break;
	}
	case time_type_abs: 
	{
		auto stamp = ITimeHelper::GetInstance()->GetTimeStamp();
		if ((info->addTime + info->timeLimit) >= stamp) {
			return false;
		}
		break;
	}
	default:
		break;
	}
	return true;
}

bool TitleDataMgr::IsHasTitle(uint32_t id)
{
	return mTitleList.find(id) != mTitleList.end();
}

bool TitleDataMgr::IsHasTitle(const std::string& name)
{
	auto titleCfg = sTitleConfig.GetByKeyName(name);
	if (titleCfg == nullptr)return false;
	return IsHasTitle(titleCfg->Id);
}

bool TitleDataMgr::IsCanAdd(uint32_t id)
{
	if (mTitleList.find(id) != mTitleList.end())return false;
	return true;
};

void TitleDataMgr::UpdateTitleProp(uint32_t id, DATA::Title* cfg, uint8_t updateType)
{
	if (nullptr == mMaster)return;
	if (nullptr == cfg)return;

	mMaster->temp_attr_type = 2;
	mMaster->temp_attr_id = id;

	static const std::pair<uint32_t, uint32_t> propList[] = {
		// 最大HP\MP
	{role_base_max_hp,                  TITLE_PROP_HP},
	{role_base_max_mp,                  TITLE_PROP_MP},
	// 物防
	{role_base_max_phy_def,             TITLE_PROP_MAXPHYDEF},
	{role_base_min_phy_def,             TITLE_PROP_MINPHYDEF},
	// 魔防
	{role_base_max_mag_def,             TITLE_PROP_MAXMAGDEF},
	{role_base_min_mag_def,             TITLE_PROP_MINMAGDEF},
	// 物攻
	{role_base_max_phy_atk,             TITLE_PROP_MAXPHYATK},
	{role_base_min_phy_atk,             TITLE_PROP_MINPHYATK},
	// 魔攻
	{role_base_max_mag_atk,             TITLE_PROP_MAXMAGATK},
	{role_base_min_mag_atk,             TITLE_PROP_MINMAGATK},
	// 道术攻击
	{role_base_max_tao_atk,             TITLE_PROP_MAXTAOATK},
	{role_base_min_tao_atk,             TITLE_PROP_MINTAOATK},
	// 命中、闪避
	{role_hit,                          TITLE_PROP_HIT},
	{role_miss,                         TITLE_PROP_MISS},
	};

	static const int32_t propCount = _countof(propList);
	for (int i = 0; i < propCount; ++i) {
		if (::GetTitleProp(id, propList[i].second)) {
			int32_t updateValue = luabind::object_cast<int32_t>(LuaRet);
			if (0 != updateValue) {
				updateValue *= updateType ? 1 : -1;
				mMaster->AddRoleProp(propList[i].first, updateValue);
			}
		}
	}

	// 特殊属性字段
	if (::GetTitleProp(id, TITLE_PROP_SPECIALATTR))
	{
		luabind::iterator iter(LuaRet), end;
		for (; iter != end; iter++)
		{
			luabind::adl::object objKey = iter.key();
			luabind::adl::object objVal = *iter;
			int32_t key = luabind::object_cast<int32_t>(objKey);
			int32_t val = luabind::object_cast<int32_t>(objVal);
			if (0 != val)
			{
				val *= updateType ? 1 : -1;
				mMaster->AddRoleProp(key, val);
			}
		}
	}
	mMaster->temp_attr_type = 0;
	mMaster->temp_attr_id = 0;
}

void TitleDataMgr::TriggerEffect(uint32_t id, DATA::Title* cfg)
{
	if (nullptr == mMaster)return;
	if (nullptr == cfg)return;
	// 触发的技能
	if (cfg->SkillId) {
		auto skillCfg = sSkillConfig.Get(cfg->SkillId);
		if (nullptr != skillCfg) {
			auto roleSkill = mMaster->GetRoleSkill();
			if (nullptr != roleSkill) {
				roleSkill->ApplySkillOnTarget(cfg->SkillId, mMaster->GetGUID(), 0);
			}
		}
	}

	// 称号绑定的buff(不是称号触发的buff)
	if (cfg->BuffID) {
		auto buffCfg = sBuffConfig.Get(cfg->BuffID);
		if (nullptr != buffCfg) {
			mMaster->AddBuffByRole(cfg->BuffID, mMaster, 0);
		}
	}

}

void TitleDataMgr::UnTriggerEffect(uint32_t id, DATA::Title* cfg)
{
	if (nullptr == mMaster)return;
	if (nullptr == cfg)return;

	if (cfg->BuffID) {
		auto buffCfg = sBuffConfig.Get(cfg->BuffID);
		if (nullptr != buffCfg) {
			mMaster->RemoveBuff(cfg->BuffID);
		}
	}
}

void TitleDataMgr::SendAddTitleToClient(SP_TITLE_INFO info)
{
	ProtoGS_TitleAddAck data;
	data.info = *info.get();
	data.sessionid = mMaster->GetClSessionID();
	SendDataBySessionID(mMaster->GetGsSessionID(), data);
}

void TitleDataMgr::SendAddTitleToCS(SP_TITLE_INFO info)
{
	ProtoMS_AddTitle data;
	data.guid = mMaster->GetGUID();
	data.info = *info.get();
	SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void TitleDataMgr::SendDelTitleToClient(uint32_t id)
{
	ProtoGS_TitleDelAck data;
	data.err = ERR_OK;
	data.id = id;
	data.sessionid = mMaster->GetClSessionID();
	SendDataBySessionID(mMaster->GetGsSessionID(), data);

}

void TitleDataMgr::SendDelTitleToCS(uint16_t num, uint32_t* id)
{
	ProtoMS_DelTitle data;
	for (int i = 0; i < num; ++i) {
		data.id[i] = id[i];
	}
	data.num = num;
	data.guid = mMaster->GetGUID();
	SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void TitleDataMgr::SendWearTypeTitleToCS(uint32_t id, uint16_t isWear)
{
	ProtoMS_TitleWearType data;
	data.guid = mMaster->GetGUID();
	data.id = id;
	data.wearType = isWear;
	SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void TitleDataMgr::SendWearNtf(uint32_t id)
{
	if (nullptr == mMaster)return;

	auto map = mMaster->GetCurMap();
	if (nullptr == map)return;

	ProtoGS_TitleWearNtf data;
	data.guid = mMaster->GetGUID();
	data.id = id;
	map->SendPlayerWearTitleNtf(mMaster, data);
}

void TitleDataMgr::SendUnWearNtf(uint32_t id)
{
	if (nullptr == mMaster)return;

	auto map = mMaster->GetCurMap();
	if (nullptr == map)return;

	ProtoGS_TitleUnWearNtf data;
	data.guid = mMaster->GetGUID();
	data.id = id;
	map->SendPlayerUnWearTitleNtf(mMaster, data);
}

void TitleDataMgr::GetTitleInfoFromDB(uint16_t num, TITLE_INFO* data)
{
	ProtoMS_DelTitle csData;
	csData.guid = mMaster->GetGUID();
	ProtoGS_TitleList gsData;
	gsData.guid = mMaster->GetGUID();
	gsData.sessionid = mMaster->GetClSessionID();
	for (int i = 0; i < num; ++i)
	{
		if (IsExpired(&data[i])) {
			csData.id[csData.num] = data[i].Id;
			++csData.num;
			continue;
		}

		gsData.info[gsData.num] = data[i];
		++gsData.num;
		mTitleList[data[i].Id] = make_shared<TITLE_INFO>(std::move(data[i]));
	}
	if (gsData.num != 0) {
		mMaster->SetNeedUpdateFlag(title_need_update_flag);
		SendDataBySessionID(mMaster->GetGsSessionID(), gsData);
	}
	if (csData.num != 0) {
		SendDataBySessionType(SESSION_TYPE_MS2CS, csData);
	}
}

void TitleDataMgr::SendTitleListInfoToGS()
{
	if (nullptr == mMaster)return;
	if (mTitleList.empty())return;
	ProtoGS_TitleList data;
	data.sessionid = mMaster->GetClSessionID();
	for (auto i : mTitleList) {
		data.info[data.num] = *i.second.get();
		++data.num;
	}
	SendDataBySessionID(mMaster->GetGsSessionID(), data);
}