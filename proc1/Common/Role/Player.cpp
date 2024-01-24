#include "stdafx.h"
#include "Player.h"
#include "RoleMove.h"
#include "MapAoi.h"
#include "ProtoClient3.h"
#include "ProtoClient2.h"
#include "Session.h"
#include "CNetManager.h"
#include "SessionFactory.h"
#include "ProtoGS.h"
#include "MapMgr.h"
#include "ShopMgr.h"
#include "Monster.h"
#include "CustVarMgr.h"
#include "TradeMgr.h"
#include "CastleWarMgr.h"
#include "RoleInfoCache.h"
#include "GMCmdHandler.h"
#include "LuaHost.h"
#include "LuaGmMgr.h"



Player::Player(uint32_t type) : Role(type), mPetMgr(this),mSummonMonsterMgr(this)
, mGuildDataMgr(this), mTeamDataMgr(this), mQuestDataMgr(this), mPKValueMgr(this)
, mDigMgr(this),mTitleDataMgr(this)
{
	mSyncTimerId = 0;
	mToken = 0;
	mGsSessionID = 0;
	mClSessionID = 0;
	mExitType = 0;
	SetScriptName("Player");
    mBuyDelegateInfo.clear();
    mSellDelegateInfo.clear();
	mTradeBuyRecords.clear();
	mTradeSellRecords.clear();
}

Player::~Player()
{
    StopSyncDataTimer();
}

void Player::Update(int32_t delta)
{
	mFightInfo.Update(delta);
	mPKValueMgr.UpdatePKValue(delta);
    Role::Update(delta);
    mSummonMonsterMgr.UpdateSummonList();
	mPetMgr.UpdatePetList();
	mTitleDataMgr.Update(delta);
	SendRoleCustVar();

	if (mCalculateAttribute)
	{
		if (mNeedCalculateAttribute)
		{
			CalculateRoleAttr();
			mNeedCalculateAttribute = false;
		}
		SetCalculateAttribute(false);
	}

}

void Player::Init()
{
    mRoleAttr = new RoleAttr(this);
    mRoleState = new RoleState(this);
    mRoleMove = new RoleMove(this);
    mRoleSkill = new RoleSkill(this);
    mRoleBuff = new RoleBuff(this);
    mRolePack = new RolePack(this);
    //mRoleTask = new RoleTask(this);
    mRoleTeam = new RoleTeam(this);
    mRoleVip = new RoleVip(this);
}

//重新计算属性
void Player::CalculateRoleAttr()
{
	if (nullptr == this->GetRoleAttr()) {
		return;
	}
	this->GetRoleAttr()->SendPropertyModyNtf();
	auto hp = GetRoleProp(role_hp);
	auto mp = GetRoleProp(role_mp);
	this->GetRoleAttr()->CalculateRoleAttr_Base();
	TRIGGER_EVENT(this, trigger_pre_recalculate, GetGUIDAsString());
	
	this->GetRoleAttr()->ClearPropertyHistoryMap();
	auto roleCfg = sRoleConfig.Get(mRoleBriefInfo.level, mRoleBriefInfo.job);
	if (roleCfg)
		InitRoleProp(roleCfg); 
	//计算buff
	std::list<BUFF_INFO_DB> list;
	auto roleBuff = GetRoleBuff();
	if (roleBuff)
	{
		roleBuff->GetAllBuffInfo(list,false);
		BUFF_INFO_DB                buffs[50];
		int buffNum = 0;
		if (!list.empty())
		{
			auto iter = list.begin();
			for (; iter != list.end();)
			{
				buffs[buffNum] = *iter;
				buffs[buffNum].actor_id = GetGUID();
				strcpy_s(buffs[buffNum].actor_name, _countof(buffs[buffNum].actor_name), GetName().c_str());
				buffNum++; iter++;
				if (buffNum == _countof(buffs) || iter == list.end())
				{
					OnGetBuffAck(buffs, buffNum);
					buffNum = 0;
				}
			}
		}
		roleBuff->Init();
	}
	auto rolePack = GetRolePack();
	rolePack->Init();
	mTitleDataMgr.Init();
	//lua脚本 重新计算属性
	TRIGGER_EVENT(this, trigger_recalculate, GetGUIDAsString());
	SetRoleProp(role_hp, hp);
	SetRoleProp(role_mp, mp);
}

void Player::InitRoleAttr(DATA::Role* roleCfg)
{
	if (nullptr == roleCfg) {
		return;
	}

	InitRoleProp(roleCfg);

    SetUpGradeExp(roleCfg->UpgradeExp);
    SetRoleProp(role_luck_curse, roleCfg->LC);
	SetRoleProp(role_curse, 0);
	SetRoleProp(role_level, mRoleBriefInfo.level);
	SetRoleProp(role_job, mRoleBriefInfo.job);
    SetRoleProp(role_vip_level, mRoleBriefInfo.vipLevel);
	//mRoleExtraInfo.hp == 0 ? SetRoleProp(role_hp, roleCfg->HP) : SetRoleProp(role_hp, mRoleExtraInfo.hp);
	//mRoleExtraInfo.mp == 0 ? SetRoleProp(role_mp, roleCfg->MP) : SetRoleProp(role_mp, mRoleExtraInfo.mp);
	SetRoleProp(role_gender, mRoleBriefInfo.gender);
	SetRoleProp(role_atk_mode, mRoleExtraInfo.atkMode);
	SetRoleProp(role_team_switch, 1);
    SetRoleProp(role_has_collide, 0);
	SetRoleProp(role_pk, mRoleExtraInfo.rolePk);
	SetRoleProp(role_changed_modelid, mRoleExtraInfo.modelID);

	log_params lp{ LOG_PARAMS_INFO_INIT };
	SetRoleProp64(role_exp, mRoleExtraInfo.exp, lp);
	SetRoleProp64(role_ingot, mRoleExtraInfo.ingot, lp);
	SetRoleProp64(role_bind_ingot, mRoleExtraInfo.bindIngot, lp);
	SetRoleProp64(role_integral, mRoleExtraInfo.integral, lp);
	SetRoleProp64(role_gold, mRoleExtraInfo.gold, lp);
	SetRoleProp64(role_bind_gold, mRoleExtraInfo.bindGold, lp);
	SetRoleProp64(role_gold_deposit, mRoleExtraInfo.depositGold, lp);
	SetRoleProp64(role_inner_force_exp, mRoleExtraInfo.innerForceExp, lp);

    SetBagSize();
	SetWarehouseSize();
	SetAdvWarehouseSize();

	SetClientBaseSetting();
	SetCustVarAssociatedData();
}

void Player::SetWarehouseSize()
{
	SetRoleProp(role_warehouse_size , MAX_WAREHOUSE_SIZE);
}

void Player::SetAdvWarehouseSize()
{
	SetRoleProp(role_warehouse_adv_size, 0);
}

void Player::SetBagSize()
{
    auto num = GetItemNumByKeyName("背包扩充40", bind_require_any, site_range_bag);   // TODO: 需要考虑是否使用，修改range

    for (auto i = 0; i < std::min<int>(num, 4) + 1; ++i)
        SetRoleProp(role_bag_size_0 + i, 40);
}

uint16_t Player::GetWarehouseSize()
{
	return GetRoleProp(role_warehouse_size);
}
uint16_t Player::GetAdvWarehouseSize()
{
	return GetRoleProp(role_warehouse_adv_size);
}

uint16_t Player::GetWarehouseFreeSize()
{
	const auto &warehouselist = GetRolePack()->GetItemList();
	uint16_t count = 0;
    int32_t end = std::min<int32_t>(site_warehouse + GetRoleProp(role_warehouse_size), site_warehouse_adv);
	for (int32_t i = site_warehouse; i < end; ++i)
	{
		if (warehouselist.at(i) == nullptr){
			++count;
		}
	}
	return count;
}
uint16_t Player::GetAdvWarehouseFreeSize()
{
	const auto &advwarehouselist = GetRolePack()->GetItemList();
	uint16_t count = 0;
	int32_t end = std::min<int>(site_warehouse_adv + GetRoleProp(role_warehouse_adv_size), site_bag_end);
	for (int32_t i = site_warehouse_adv; i < end; ++i)
	{
		if (advwarehouselist.at(i) == nullptr) {
			++count;
		}
	}
	return count;
}

uint16_t Player::GetWarehouseFirstFreeSite()
{
	const auto &warehouselist = GetRolePack()->GetItemList();
	for (uint16_t i = site_warehouse; i < site_warehouse + GetWarehouseSize(); ++i)
	{
		if (warehouselist.at(i) == nullptr) return i;
	}
	return 0;
}

uint16_t Player::GetAdvWarehouseFirstFreeSite()
{
	const auto &advwarehouselist = GetRolePack()->GetItemList();
	for (uint16_t i = site_warehouse_adv; i < site_warehouse_adv + GetAdvWarehouseSize(); ++i)
	{
		if (advwarehouselist.at(i) == nullptr) return i;
	}
	return 0;
}

uint32_t Player::GetGmModLevel()
{
	return GetRoleProp(role_gm_level);
}

CLuaObject Player::GetVipExtePermissions()
{
	auto luaObj = NewLuaObj();
	
	auto roleVip = GetRoleVip();
	if (!roleVip) return luaObj;

	const auto& eps = roleVip->GetExtePermissions();
	if (!eps.empty())
	{
		auto iter = eps.begin();
		for (int32_t i = 1; iter != eps.end(); ++iter,++ i)
		{
			luaObj[i] = *iter;
		}
	}

	return luaObj;
}

bool Player::HasVipExtePermissions(int32_t permissions)
{
	if (!GetRoleVip()) return false;

	return GetRoleVip()->HasExtePermissions(permissions);
}

void Player::SetNameToCS(const std::string& name, uint64_t guid)
{
	ProtoMS_PlayerSetNameReq data;
	data.guid = guid;
	strcpy_s(data.name, _countof(data.name), name);
	SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

bool Player::AddTitleByName(const std::string& titleName)
{
	return mTitleDataMgr.AddTitle(titleName);
}

bool Player::DelTitleByName(const std::string& titleName)
{
	return mTitleDataMgr.DelTitle(titleName);

}

bool Player::IsHasTitle(const std::string& titleName)
{
	return mTitleDataMgr.IsHasTitle(titleName);

}

void Player::GetListProp(CLuaObject& list, uint16_t type, uint16_t min, uint16_t max)
{
	if (mRoleAttr) {
		mRoleAttr->GetListProp(list, type, min, max);
	}
}

void Player::GetListItem(CLuaObject& list, uint16_t min, uint16_t max)
{
	if (mRolePack) {
		mRolePack->GetItemList(list, min, max);
	}
}

void Player::GenRoleCustVar(ProtoMS_RoleCustVarNtf& ntf)
{
	ntf.role_guid = GetGUID();
	ntf.custom << mCustVars;
	ntf.type = 0;
}

void Player::GenRoleTempCustVar(ProtoMS_RoleCustVarNtf& ntf)
{
	ntf.role_guid = GetGUID();
	ntf.custom << mTempCustVars;
	ntf.type = 1;
}



void Player::SendRoleCustVar()
{
	if (mCustVarMody)
	{
		MSG_BUFFER_DATA(ProtoMS_RoleCustVarNtf, ntf);
		GenRoleCustVar(ntf);
		// 单发
		SendRoleCustVarNtf(ntf);
		// 广播
		//map->SendRoleCustVarNtf(this, ntf);
		mCustVarMody = false;
		mTempCustVarMody = false;
		mTempCustVars.clear();
        CheckCustVarNeedUpdate();
	}
	if (mTempCustVarMody)
	{
		MSG_BUFFER_DATA(ProtoMS_RoleCustVarNtf, ntf);
		GenRoleTempCustVar(ntf);
		// 单发
		SendRoleCustVarNtf(ntf);
		mTempCustVarMody = false;
		mTempCustVars.clear();
		CheckCustVarNeedUpdate();
	}
}

void Player::StartSyncDataTimer()
{
	if (0 != mSyncTimerId) StopSyncDataTimer();
	uint32_t intervalTime = SEND_SYNC_DATA_INTERVAL_TIME;
	auto globalCfg = sGlobalConfig.GetData();
	if (globalCfg) intervalTime = globalCfg->SyncDataIntervalTime;

    auto guid = GetGUID();

    mSyncTimerId = ITimeHelper::GetInstance()->AddTimer(intervalTime, true, [=](const TimerData &){
        auto *player = MapRoleMgr::GetInstance()->FindPlayer(guid);
        if (!player) return;
        player->SyncPlayerData();
    });
}

void Player::StopSyncDataTimer()
{
	if (mSyncTimerId == 0) return;

	ITimeHelper::GetInstance()->RemoveTimer(mSyncTimerId);
	mSyncTimerId = 0;
}

/* 公共接口*/
void Player::SendErrorAck(int32_t type, const char* errMsg)
{
	ProtoMS_ErrorAck errorAck;
	errorAck.clientSessionID = GetClSessionID();
	errorAck.guid = GetGUID();
	errorAck.ecode = type;
	SendDataBySessionID(GetGsSessionID(), errorAck);
}

void Player::SendGMErrorAck(int32_t sn, int32_t ecode)
{
    ProtoMS_GMErrorAck data;
    data.clsessid = GetClSessionID();
    data.sn = sn;
    data.ecode = ecode;
    data.guid = GetGUID();
    SendDataBySessionID(GetGsSessionID(), data);
}

void Player::SendPopDlgMsgNtf(const std::string &msg)
{
    SAFE_BEGIN;

    ProtoMS_PopDlgMsgNtf data;
    data.sessionid = GetClSessionID();
    strcpy_s(data.msg, _countof(data.msg), msg.c_str());

    SendDataBySessionID(GetGsSessionID(), data);

    SAFE_END;
}
void Player::SendSysMsgNtf2(MESSAGE_INFO& info,bool toall)
{
	MSG_BUFFER_DATA(ProtoGS_SysMsgNtf2, data);
	GenerateSysMsgInfo(info, data.info);
	data.sessid = this->GetClSessionID();
	if (toall)
	{
		data.all = 1;
		SendDataBySessionType(SESSION_TYPE_MS2GS, data, true);
	}
	else
	{
		SendDataBySessionID(GetGsSessionID(), data);

	}
	

	
}

void Player::SendSceneDialogNtf(MESSAGE_INFO& info)
{
	MSG_BUFFER_DATA(ProtoGS_SceneDialogNtf, data);
	auto role = MapRoleMgr::GetInstance()->FindRole(info.srcGuid);
	if (!role)return;
	GenerateSenceDialogInfo(info, data.info);
	data.sessid = this->GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), data);
}

void Player::SendScrollText(MESSAGE_INFO& info, bool toall)
{
	MSG_BUFFER_DATA(ProtoGS_ScrollText, data);
	GenerateScrollTextInfo(info, data.info);
	data.sessid = this->GetClSessionID();
	if (toall)
	{
		data.all = 1;
		SendDataBySessionType(SESSION_TYPE_MS2GS, data, true);
	}
	else
	{
		SendDataBySessionID(GetGsSessionID(), data);
	}
}

void Player::SendCustMsgNtf(MESSAGE_INFO& info)
{
	MSG_BUFFER_DATA(ProtoGS_CustMsgNtf, data);
	GenerateCustMsgInfo(info, data.info);
	data.sessionid = this->GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), data);
}

void Player::SendMonsterPursureStatus(Monster* monster)
{
	if (!monster)return;
    if (!IsOnline()) return;
	ProtoMS_MonsterPursureAttackingNtf info;
	monster->IsPursureStatus() == true ? info.status = 1 : info.status = 0;
	info.guid = monster->GetGUID();
	info.sessionid = GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), info);
}

void Player::SendMonsterAppearNtf(Monster* monster)
{
	if (!monster)return;
	auto& pdata = gProtoMS_MonsterAppearNtf6;
	monster->MakeMonsterAppearNtfData(pdata);
	pdata.sessid = GetClSessionID();
	pdata.nGS2CSSessionID = GetGsSessionID();
	SendDataBySessionID(GetGsSessionID(), pdata);
}

void Player::GenerateSysMsgInfo(MESSAGE_INFO& info, SYSTEN_MESSAGE_NTF& data)
{
	if (info.comp) {
		memcpy(data.message, info.message, info.size);
	}
	else {
		strcpy_s(data.message, _countof(data.message), info.message);
		info.size = _countof(info.message);
	}
	data.size = info.size;
	data.comp = info.comp;
	strcpy_s(data.font_color, _countof(data.font_color), info.font_color);
	strcpy_s(data.background_color, _countof(data.background_color), info.background_color);
}

void Player::GenerateSenceDialogInfo(MESSAGE_INFO& info, SCENCE_DIALOG_NTF& data)
{
	if (info.comp) {
		memcpy(data.message, info.message, info.size);
	}
	else {
		strcpy_s(data.message, _countof(data.message), info.message);
		info.size = _countof(info.message);
	}
	strcpy_s(data.font_color, _countof(data.font_color), info.font_color);
	strcpy_s(data.background_color, _countof(data.background_color), info.background_color);
	if (info.srcGuid)return;
	data.objGuid = info.srcGuid;
	data.isAppearSrcName = info.isAppearSrcName;
	data.size = info.size;
	data.comp = info.comp;
}

void Player::GenerateScrollTextInfo(MESSAGE_INFO& info, SCROLL_TEXT& data)
{
	if (info.comp) {
		memcpy(data.message, info.message, info.size);
	}
	else {
		strcpy_s(data.message, _countof(data.message), info.message);
		info.size = _countof(info.message);
	}
	strcpy_s(data.font_color, _countof(data.font_color), info.font_color);
	strcpy_s(data.background_color, _countof(data.background_color), info.background_color);
	data.size = info.size;
	data.comp = info.comp;
	data.type = info.marqueeType;
	data.scroll_times = info.scroll_times;
}

void Player::GenerateCustMsgInfo(MESSAGE_INFO& info, CUST_MSG_NTF& data)
{
	if (info.comp) {
		memcpy(data.message, info.message, info.size);
	}
	else {
		strcpy_s(data.message, _countof(data.message), info.message);
		info.size = _countof(info.message);
	}
	strcpy_s(data.font_color, _countof(data.font_color), info.font_color);
	strcpy_s(data.background_color, _countof(data.background_color), info.background_color);
	data.size = info.size;
	data.comp = info.comp;
	data.scroll_times = info.scroll_times;
	data.display_type = info.display_type;
}

void Player::SendItemAttrNtf(uint64_t guid, uint32_t attr, int val)
{
	ProtoMS_ItemAttrNtf ntf;
	ntf.item_guid = guid;
	ntf.attr_name = attr;
	ntf.attr_value = val;
	ntf.sessid = GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), ntf);
}

void Player::SendAddItem(ProtoMS_ItemAddAck& ack)
{
	ack.sessid = GetClSessionID();
	ack.nGS2CSSessionID = GetGsSessionID();
	SendDataBySessionID(GetGsSessionID(), ack);
    LOG_TRACE("[ITEM] ItemAddAck, id: %u, site: %u", ack.info.base_info.id, ack.info.base_info.site);
}

void Player::SendAllBagItemsToGS()
{
    auto *rolePack = GetRolePack();
    if (!rolePack) return;

    for (uint16_t i = site_bag_0; i < site_warehouse; ++i)
        rolePack->NtfMasterAddItem(i, false);
}

void Player::SendItemUpdateNtf(ProtoMS_ItemUpdateNtf& ntf)
{
	ntf.sessid = GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), ntf);
}

void Player::SendPlayerReliveNtf(std::string mapName, int type, int hp, int mp, uint16_t x, uint16_t y)
{
	GetRoleState()->SetState(role_state_idle);
	if(GetRoleProp(role_hp) > 0)return;
	SetRoleProp(role_hp, hp);
	SetRoleProp(role_mp, mp);
	auto roleAttr = GetRoleAttr();
	if (!roleAttr) return;
	roleAttr->SetMoveType(type);

	DATA::Map* fromMapCfg = nullptr;
	DATA::Map* toMapCfg = nullptr;
	if (GetCurMap()) fromMapCfg = GetCurMap()->GetMapConfig();
	Map* tarMap = MapMgr::GetInstance()->FindMap(mapName);
	if (tarMap != nullptr && tarMap != GetCurMap())
	{
		tarMap->FindJumpablePos(x, y);
		if (!LeaveCurMap(false)) return;
		EnterMap(tarMap, x, y);
		if (GetCurMap()) toMapCfg = GetCurMap()->GetMapConfig();
		if (fromMapCfg && toMapCfg && fromMapCfg != toMapCfg)
		{
			SendDBLogData(log_type_entery_exit_map, LogEnteryExitMap(GetGUID(), fromMapCfg->Id, fromMapCfg->MapType, toMapCfg->Id, toMapCfg->MapType, "回城复活"));
		}
	}
	else
	{
		auto* map = GetCurMap();
		if (!map) return;
		map->FindJumpablePos(x, y);
		//SetRolePosNoEvent(x, y);
		SetRolePos(x, y);
	}

	if (roleAttr->GetMoveType() == move_type_jump) {
		roleAttr->SetMoveType(move_type_walk);
	}

	LOG_TRACE("####SendPlayerReliveNtf");
}

void Player::SendSyncItemNtf(uint64_t guid, uint16_t amount, int dura, uint16_t id, int site,
	const std::string& name, int max_dura, uint16_t use_cnt, uint8_t boud, uint32_t life)
{
	ProtoMS_SendSyncItemNtf ntf;
	ntf.Guid = guid;
	ntf.Amount = amount;
	ntf.Durability = dura;
	ntf.IsBind = boud;
	ntf.Life = life;
	ntf.Max_durability = max_dura;
	memcpy(ntf.Name, name.c_str(), _countof(ntf.Name));
	ntf.Tempid = id;
	ntf.Site = site;
	ntf.Use_count = use_cnt;
	ntf.role_guid = GetGUID();
	ntf.token = GetToken();
	ntf.Roleid = GetGUID();
	SendDataBySessionType(SESSION_TYPE_MS2CS, ntf);
}

void Player::SendSyncItemNtf(const RoleItem& item)
{
	ProtoMS_SendSyncItemNtf ntf;
	ntf.Guid = item.GetGUID();
	ntf.Amount = item.GetAmount();
	ntf.Durability = item.GetDurability();
	ntf.IsBind = item.GetIsBind();
	ntf.Life = item.GetLife();
	ntf.Max_durability = item.GetMaxDurability();
    strcpy_s(ntf.Name, _countof(ntf.Name), item.GetName().c_str());
	ntf.Tempid = item.GetTemplateID();
	ntf.Site = item.GetSite();
	ntf.Use_count = item.GetUse_count();
	ntf.role_guid = GetGUID();
	ntf.token = GetToken();
	ntf.Roleid = GetGUID();
	ntf.ItemCfgVar.subtype = item.GetSubType();
	ntf.ItemCfgVar.color = item.GetColor();
	ntf.ItemCfgVar.icon = item.GetIcon();
	ntf.ItemCfgVar.quality = item.GetQuality();
	SendDataBySessionType(SESSION_TYPE_MS2CS, ntf);
}

void Player::SendDelItemNtf(const RoleItem& item, uint8_t tradeDel)
{
    ProtoMS_SendDelItemNtf data;
    data.user_guid = GetUserID();
    data.role_guid = GetGUID();
    data.item_guid = item.GetGUID();
	data.tradeDel = tradeDel;
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void Player::SendPlayerShowNtf(int hp, int mp)
{
    if (!IsOnline()) return;

	ProtoMS_AttrShowNtfEx2 AttrShowNtfEx2;
	AttrShowNtfEx2.actor = GetGUID();
	AttrShowNtfEx2.skill_id = 1;
	AttrShowNtfEx2.type = 0;
	AttrShowNtfEx2.actor_hp_ref = hp;
	AttrShowNtfEx2.actor_mp_ref = mp;

	AttrShowNtfEx2.target = 0;
	AttrShowNtfEx2.target_hp_ref = 0;
	AttrShowNtfEx2.target_mp_ref = 0;
	AttrShowNtfEx2.target_hp = 0;
	AttrShowNtfEx2.target_mp = 0;
	AttrShowNtfEx2.reserve_size = 0;
	memset(AttrShowNtfEx2.reserve, 0, sizeof(AttrShowNtfEx2.reserve));
	AttrShowNtfEx2.clsessnum = 1;
    AttrShowNtfEx2.clsessids[0] = GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), AttrShowNtfEx2, true);
}

void Player::SendMapEnterNtf(DATA::Map* cfg)
{
	if (IsInvalid()) return;
	ProtoMS_EnterMSNtf ntf;
	ntf.nClientSessionID = GetClSessionID();
	ntf.nCS2GSSessionID = GetGsSessionID();
	ntf.mapcode = cfg->Id;
	memcpy(ntf.logic, cfg->KeyName, sizeof(cfg->KeyName));
	auto curmap = GetCurMap();
	ntf.height = curmap == nullptr ? 0 : curmap->GetHeight();
	ntf.width = curmap == nullptr ? 0 : curmap->GetWidth();

	ntf.view_x = cfg->LightXr;
	ntf.view_y = cfg->LightYr;
	ntf.token = GetToken();
	SendDataBySessionID(GetGsSessionID(), ntf);
}

bool Player::ItemMove(uint64_t guid, uint16_t site)
{
	int ret = ERR_OK;
	ret = (!site) ? GetRolePack()->DropItem(guid) : GetRolePack()->MoveItem(guid, site);

	if (ERR_OK != ret) {
		SendErrorAck(ret);
		return false;
	}
	return true;
}

bool Player::ItemSplit(uint64_t guid, uint16_t amount, uint16_t site)
{
	int ret = ERR_OK;
	ret = GetRolePack()->SplitItem(guid, amount, site);

	if (ERR_OK != ret) {
		SendErrorAck(ret);
		return false;
	}
	return true;
}

void Player::OnRecvIDgnBindInfoFromCS(const ProtoCS_DgnBindInfoNtf& ntf)
{
	for (uint16_t i = 0; i < ntf.num; ++i)
	{
		MapMgr::GetInstance()->BindMulDgnGuidWithPlayerGuid(std::to_string(ntf.info[i].dgnId), GetGUIDAsString());
	}
}

void Player::OnRecvItemFromCS(ProtoCS_SendItemNtf& ntf)
{
	auto* pack = GetRolePack();
	if (!pack) return;

	pack->OnRecvItemFromCS(ntf);
}

void Player::OnRecvTitleFromDB(uint16_t num, TITLE_INFO* info)
{
	mTitleDataMgr.GetTitleInfoFromDB(num, info);
}

void Player::UseItem(uint64_t guid, uint32_t num)
{
	auto ret = GetRolePack()->UseItem(guid, num);
	if (ret != ERR_OK) {
		SendErrorAck(ret);
	}
}

void Player::DropItem(uint64_t guid)
{
	auto ret = GetRolePack()->DropItem(guid);
	if (ERR_OK != ret) {
		SendErrorAck(ret);
	}
}

void Player::ItemArrange(unsigned char type)
{
	auto ret = GetRolePack()->ItemArrange(type);
	if (ERR_OK != ret) {
		SendErrorAck(ret);
	}
}

void Player::PickUpItem(void)
{
	auto ret = GetRolePack()->PickUpItem();
	if (ret != ERR_OK) {
		SendErrorAck(ret);
	}
}

void Player::PickUpItem(const Point *pos, uint8_t num)
{
    auto ret = GetRolePack()->AutoPickupItem(pos, num);
    if (ret != ERR_OK) {
        SendErrorAck(ret);
    }
}

bool Player::AddPlayerItem(uint16_t tempid, const log_params& lp)
{
	return GetRolePack()->AddItemToBag(tempid, lp) != INVALID_ITEM_SITE;
}

bool Player::CheckUpgrade(int64_t& exp, int64_t diffExp, int32_t nLevel, uint64_t nUpgradeExp, const log_params& lp)
{
	bool beUpgrade = true;
	CLuaObject upgradeRet = NewLuaObj();
	TRIGGER_EVENT_RET<CLuaObject>(upgradeRet, trigger_pre_level_up, GetGUIDAsString(), nLevel, std::to_string(diffExp));
	if (luabind::type(upgradeRet) == LUA_TTABLE && luabind::type(upgradeRet["BeUpgrade"]) == LUA_TBOOLEAN && luabind::type(upgradeRet["AddExp"]) == LUA_TSTRING)
	{
		beUpgrade = luabind::object_cast<bool>(upgradeRet["BeUpgrade"]);
		diffExp = std::stoull(luabind::object_cast<std::string>(upgradeRet["AddExp"]));
	}
	exp = diffExp + GetRoleProp64(role_exp);
	exp = (exp <= 0) ? 0 : exp;
	if (!beUpgrade)
	{
		SetRoleProp64(role_exp, exp, lp);
		return false;
	}
	if (exp < nUpgradeExp) {
		SetRoleProp64(role_exp, exp, lp);
		return false;
	}
	return true;
}

void Player::AddRoleExp(int64_t exp, const log_params& lp)
{
    if (exp == 0) return;

    auto nLevel = GetRoleProp(role_level);
    auto nJob = GetRoleProp(role_job);

	auto pCurRoleCfg = sRoleConfig.Get(nLevel, nJob);
    if (!pCurRoleCfg) {
        LOG_ERROR("pCurRoleCfg is NULL. nLevel: %d, nJob: %d", nLevel, nJob);
        return;
    }

    const auto &nTempUpgradeExp = pCurRoleCfg->UpgradeExp;
	auto nExp_pct = GetRoleProp(role_exp_consume_pct);
	auto nUpgradeExp = nTempUpgradeExp;
	if (nExp_pct > 0)
	{
		nUpgradeExp = nUpgradeExp * (1 + nExp_pct / 10000.0);
	}

	if (exp < 0)
	{	// 降经验,最多当前等级的经验值为0
		exp += GetRoleProp64(role_exp);
		exp = (exp <= 0) ? 0 : exp;
	}
	else
	{
		exp = RecalcExp(exp);
		exp += GetRoleProp64(role_exp);
	}

	int64_t diffExp = exp - GetRoleProp64(role_exp);

    if (exp < nUpgradeExp) {
        SetRoleProp64(role_exp, exp, lp);
        return;
    }

    // 升级

    nLevel += 1;
    auto pNextRoleCfg = sRoleConfig.Get(nLevel, nJob);
    if (!pNextRoleCfg) {        // 已是最高等级
        SetRoleProp64(role_exp, nUpgradeExp, lp);
        return;
    }

    if (mUpgradeTimerID != 0) {     // 正在升级
        SetRoleProp64(role_exp, exp, lp);
        return;
    }
	
	if (!CheckUpgrade(exp, diffExp, nLevel - 1, nUpgradeExp, lp)) return;
	SetRoleProp64(role_exp, exp, lp);
    exp -= nUpgradeExp;
    SetRoleProp64(role_exp, exp, lp);
    SetRoleProp(role_level, nLevel);

    if (exp < pNextRoleCfg->UpgradeExp) return;

    // 连续升级

    auto roleID = GetGUID();

    TimerData timer;
    timer.interval = 1000;
    timer.loop = true;
    timer.callBack = [roleID, lp, this](const TimerData &data) {

        auto *player = MapRoleMgr::GetInstance()->FindPlayer(roleID);
        if (!player) {      // 玩家已退出
            ITimeHelper::GetInstance()->RemoveTimer(data.id);
            return;
        }

        auto level = GetRoleProp(role_level);
        auto job = GetRoleProp(role_job);
        auto exp = GetRoleProp64(role_exp);

		auto curCfg = sRoleConfig.Get(level, job);
        if (!curCfg) {
            LOG_ERROR("curCfg is NULL. level: %d, job: %d", level, job);
            RemoveUpgradeTimer();
            return;
        }

        const auto & nTempUpgradeExp = curCfg->UpgradeExp;
		auto upgradeExp = nTempUpgradeExp;
		auto nExp_pct = GetRoleProp(role_exp_consume_pct);
		if (nExp_pct > 0)
		{
			upgradeExp = upgradeExp * (1 + nExp_pct / 10000.0);
		}

        if (exp < upgradeExp) {
            RemoveUpgradeTimer();
            return;
        }

        level += 1;
		auto nectCfg = sRoleConfig.Get(level, job);
        if (!nectCfg) {
            SetRoleProp64(role_exp, upgradeExp, lp);
            RemoveUpgradeTimer();
            return;
        }

		if (!CheckUpgrade(exp, 0, level - 1, upgradeExp, lp))
		{
			RemoveUpgradeTimer();
			return;
		}

        exp -= upgradeExp;
        SetRoleProp64(role_exp, exp, lp);
        SetRoleProp(role_level, level);

        if (exp < nectCfg->UpgradeExp) RemoveUpgradeTimer();
    };

    mUpgradeTimerID = ITimeHelper::GetInstance()->AddTimer(timer);
}

void Player::RemoveUpgradeTimer()
{
    if (mUpgradeTimerID == 0) return;
    ITimeHelper::GetInstance()->RemoveTimer(mUpgradeTimerID);
    mUpgradeTimerID = 0;
}

uint64_t Player::RecalcExp(uint64_t exp)
{
	double coff = 1.0;

	if (BuffExist(EXPBUFF_DOUBLE)) coff += 1;    // 双倍经验
	if (BuffExist(EXPBUFF_DUP)) coff += 1;      // 副本经验增加100%

	return uint64_t(exp * coff + 0.5);
}

void Player::AddPlayerExperience(int64_t exp, const log_params& lp)
{
	if (!sRoleConfig.Has(GetRoleProp(role_level), GetRoleProp(role_job))) {
		return;
	}
	AddRoleExp(exp, lp);
}

void Player::AddPlayerGold(uint64_t goldid, const log_params& lp)
{
	AddRoleProp64(role_gold, goldid, lp);
}

void Player::OnEnterMap(Map *map)
{
    Role::OnEnterMap(map);
    SaveRebirthMap(map);
    SaveRedNameMap(map);
}

void Player::CalcDropItems(uint64_t killerGUID)
{
	auto map = GetCurMap();
	if (nullptr == map) {
		return;
	}

	auto rolepack = GetRolePack();
	if (!rolepack)return;
	rolepack->CalcDropItems(killerGUID);
}

void Player::SaveRebirthMap(Map *map)
{
    if (!map) return;

    const auto &mapName = map->GetName();
    const auto *regionCfg = sReliveRegionConfig.Get(mapName);
    if (!regionCfg) return;

    auto mapWidth = map->GetWidth();
    auto mapHeight = map->GetHeight();

    if (regionCfg->m_Region.left >= mapWidth) return;
    if (regionCfg->m_Region.top >= mapHeight) return;

    mRoleExtraInfo.rebirthMap = map->GetTemplateID();
}

void Player::SaveRedNameMap(Map *map)
{
    if (!map) return;

    const auto &mapName = map->GetName();
    const auto *regionCfg = sRedNameRegionConfig.Get(mapName);
    if (!regionCfg) return;

    auto mapWidth = map->GetWidth();
    auto mapHeight = map->GetHeight();

    if (regionCfg->m_Region.left >= mapWidth) return;
    if (regionCfg->m_Region.top >= mapHeight) return;

    mRoleExtraInfo.redNameMap = map->GetTemplateID();
}

void Player::OnRoleEnter(Role* role)
{
	if (!role) return;
	if (role->GetGUID() == GetGUID()) return;

	if (role->IsPlayer() || role->IsStallDummy()) {
		SendPlayerAppearNtf(role);
		role->SendRoleAppNtf(this);
		SendPlayerSkillPropChangeNtf(role);
	}
	else if (role->IsMonster()) {
		auto monster = static_cast<Monster*>(role);
		if (!monster)return;
		SendMonsterAppearNtf(monster);
		SendMonsterPursureStatus(monster);
	}
	else if (role->IsNpc()) {
		ProtoMS_NpcAppearNtf pdata;
		static_cast<Npc*>(role)->MakeNpcAppearNtfData(pdata);
		pdata.clientSessionID = GetClSessionID();
		SendDataBySessionID(GetGsSessionID(), pdata);
	}
	else if (role->IsPet())
	{
		auto pet = static_cast<Pet*>(role);
		if (!pet)return;
		SendMonsterAppearNtf(pet);
	}
    else if (role->IsPlayerDoplganr()) {
        role->SendAppearNtf(this);
        role->SendRoleAppNtf(this);
    }

	NotifyOnePlayer_AddBuff(this, role);
}

void Player::OnRoleLeave(Role* role)
{
	if (!role) return;
    if (role->GetGUID() == GetGUID()) {
        ReleaseGrid();
        return;
    }

	SendObjDisappearNtfToGS(role->GetGUID());
}

void Player::OnRoleMove(Role* role)      // 发送角色移动的NTF消息
{
	if (!role) return;
	auto& moventf = gProtoMS_MoveNtf;
	uint16_t x, y;
	auto roleAttr = role->GetRoleAttr();
	roleAttr->GetRolePos(x, y);

	moventf.guid = role->GetGUID();
	moventf.type = roleAttr->GetMoveType();
	moventf.dst_x = x;
	moventf.dst_y = y;
	moventf.sessionid = this->GetClSessionID();
	SendDataBySessionID(this->GetGsSessionID(), moventf);
}

void Player::OnRoleExit(Role* role)
{
	if (!role) return;
	Role::OnRoleExit(role);

	if (role->GetGUID() != GetGUID()) {
		SendObjDisappearNtfToGS(role->GetGUID());
		return;
	}
}

void Player::OnRoleUpdateHPMP(int32_t nHP, int32_t nMP)
{
    UpdateHPMP(nHP, nMP, 0, true);
}

void Player::OnRoleDie(uint64_t killerGUID)
{
    auto *map = GetCurMap();
    if (!map) return;
    Role::OnRoleDie(killerGUID);
	//if (PKValueMgr::IsWhiteName(GetGUID()))
	if (!IsRedName() && !IsGrayName()) {
		PKValueMgr::AddPKValue(killerGUID, this);
	}

	auto role = MapRoleMgr::GetInstance()->FindRole(killerGUID);
	if (role && !role->IsMonster()) {
		DropItemByDropProcess(player_drop_type_die, killerGUID);
	}

	auto globalcfg = sGlobalConfig.GetData();
	if (globalcfg) {
		if (globalcfg->PlayerCanDrop) {
			CalcDropItems(killerGUID);
		}
	}

    mSummonMonsterMgr.SummonMonsterLeaveMap();
    mSummonMonsterMgr.DestroySummonMonster();
	mPetMgr.PetLeaveMap();
	mPetMgr.DestroyPet();

    if (mDoplganrMgr) {
        mDoplganrMgr->DoplganrLeaveMap();
        mDoplganrMgr->DestroyDoplganr();
    }

    map->RemoveMonitorRegionForTrapSkill(GetGUID());

	auto mcfg = map->GetMapConfig();
	if (!mcfg) return;

	uint64_t kGuid = killerGUID;
	uint16_t t = GUID_TYPE_PART(killerGUID);
	uint32_t st = 0;
	uint32_t lv = 0;
	auto skiller = MapRoleMgr::GetInstance()->FindRole(killerGUID);
	if (skiller)
	{
		if (!skiller->IsPlayer())
		{
			Player* belongPlayer = nullptr;
			if (skiller->IsPet()) {
				auto pet = static_cast<Pet*>(skiller);
				if (pet && pet->GetConfig())
				{
					st = pet->GetConfig()->Id;
					lv = pet->GetRoleProp(role_level);
					belongPlayer = pet->GetMaster();
				}
			}
			else if (skiller->IsPlayerDoplganr()) {
				auto* doplganr = static_cast<PlayerDoplganr*>(skiller);
				if (doplganr)
				{
					st = doplganr->GetRoleProp(role_job);
					lv = doplganr->GetRoleProp(role_level);
					belongPlayer = doplganr->GetMaster();
				}
			}
			else if (skiller->IsMonster()) {
				auto* monster = static_cast<Monster*>(skiller);
				if (monster && monster->GetConfig())
				{
					st = monster->GetConfig()->Id;
					lv = monster->GetRoleProp(role_level);
					belongPlayer = monster->GetMaster();
				}
			}
			if (belongPlayer)
			{
				kGuid = belongPlayer->GetGUID();
				st = belongPlayer->GetRoleProp(role_job);
				lv = belongPlayer->GetRoleProp(role_level);
				t = GUID_TYPE_PART(kGuid);
			}
		}
		else
		{
			st = skiller->GetRoleProp(role_job);
			lv = skiller->GetRoleProp(role_level);
		}
	}
	SendDBLogData(log_type_death_record, LogDeathRecord(GetGUID(), mRoleBriefInfo.level, mcfg->Id, mcfg->MapType, kGuid, lv, t, st));
}

void Player::TeleportToPos(uint16_t x, uint16_t y)
{
    auto *map = GetCurMap();
    if (!map) return;

    map->RoleLeave(this);
    SetRolePosNoEvent(x, y);
    map->RoleEnter(this);
    SendPlayerAppearNtf(this);

    mSummonMonsterMgr.SummonMonsterTeleportToMaster();
}

void Player::SetCustVarAssociatedData()
{
	static const std::string typeArr[] = { std::string(CUST_VAR_ALIAS_KEY) };
	for (auto& type : typeArr)
	{
		std::string value = GetCustVar(type);
		if (value.empty()) continue;

		SetCustVarAssociatedData(type, value);
	}
}

void Player::SetCustVarAssociatedData(const std::string& type, const std::string& value)
{
	if (type == CUST_VAR_ALIAS_KEY)
	{
		Object::SetAlias(value);
	}
}

void Player::SetClientBaseSetting()
{
	static const uint16_t typeArr[] = { scbs_auto_stack, scbse_stall_bind_trade };
	for (auto type : typeArr)
	{
		std::string name = SYNC_CLIENT_BASE_SETTING_PREFIX + to_string(type);
		std::string value = GetCustVar(name);
		if (value.empty()) continue;

		int32_t val = atoi(value.c_str());
		SetClientBaseSetting(type, val);
	}
}

void Player::SetClientBaseSetting(uint16_t type, int32_t val)
{
	std::string name = SYNC_CLIENT_BASE_SETTING_PREFIX + to_string(type);
	std::string value = to_string(val);
	SetCustVar(name, value, cust_var_type_normal);
	switch (type)
	{
		case scbs_auto_stack:
		{
			auto rolePack = GetRolePack(); if (!rolePack) return;
			rolePack->SetAutoStack(val != 0);
			break;
		}
		case scbse_stall_bind_trade:
		{
			mStallBindTrade = (val != 0);
			break;
		}
	}
}

bool Player::HandleGoodsIssue(GOODS_ISSUE_RECORD &record)
{
    if (!IsOnline()) {
        LOG_NORMAL("[GM] player is not online");
        return SendSaveGoodsIssueRecordToCS(record);
    }

    bool issued = false;
    TRIGGER_EVENT_RET(issued, this, trigger_issue_goods, GetGUIDAsString(), record.goods_id, record.goods_num);
    record.issued = issued;

	// 订单发至客户端上传
	LOG_ERROR("GM Goods Post order:%s,time:%s", record.order_no, ITimeHelper::GetInstance()->GetCurTimeStrMS().c_str());
	SendGoodsPostRecordToClient(record);
	mGoodsNotPostRecords.push_back(record);

    auto sent = SendSaveGoodsIssueRecordToCS(record);
    LOG_NORMAL("[GM] goods_id: %u, issued: %d, sent: %d", record.goods_id, issued, sent);
    return issued || sent;
}

void Player::VerifyBuyItemInfo(uint32_t itemID, uint8_t count, uint32_t price)
{
    bool canBuy = true;
    TRIGGER_EVENT_RET(canBuy, this, trigger_can_buy_goods, GetGUIDAsString(), itemID, count, price);

    ProtoMS_VerifyBuyItemInfoAck data;
    data.clsessid = GetClSessionID();
    data.item_id = itemID;
    data.status = canBuy;

    SendDataBySessionID(GetGsSessionID(), data);
}

void Player::SendSyncItemInfoReqToCS()
{
	auto* rolepack = this->GetRolePack();
	if (nullptr == rolepack) return;

	const auto &itemlist = rolepack->GetItemList();
	for (const auto &item : itemlist)
	{
		if (!item) continue;
		SendSyncItemNtf(*item);
	}
}

void Player::SendSyncItemDynAttrsToCS()
{
    auto *rolePack = GetRolePack();
    if (!rolePack) return;

    ITEM_DYN_ATTRS_LIST attrsList;

    for (auto i = 0; i < site_end; ++i) {

        auto *item = rolePack->GetItem(i);
        if (!item) continue;

        auto &dynAttrs = item->GetDynAttrs();
        if (dynAttrs.empty()) continue;

        attrsList.emplace_back(item->GetGUID(), dynAttrs);
    }

    ProtoMS_SyncItemDynAttrs data;
    data.playerid = GetUserID();
    data.roleid = GetGUID();
    data.attrs_list = &attrsList;

    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void Player::SendSyncPlayerQuickBarSetToCS()
{
	ProtoMS_QuickBarSet bar;
	bar.userid = this->GetUserID();
	bar.role_id = this->GetGUID();
	bar.num = BarVector.size();
	for (int i = 0; i < bar.num; ++i)
	{
		bar.info[i].guid = BarVector[i].guid;
		bar.info[i].id = BarVector[i].id;
		bar.info[i].slot = BarVector[i].slot;
		bar.info[i].type = BarVector[i].type;
	}
	SendDataBySessionType(SESSION_TYPE_MS2CS, bar);
}

void Player::SendSyncPlayerDgnBindInfoToCS()
{
	ProtoMS_DgnBindInfo dgnBind;
	dgnBind.userid = this->GetUserID();
	dgnBind.roleId = this->GetGUID();
	dgnBind.num = 0;
	dgnBind.packIdx = 0;
	if (mMultDgnMapID.empty())
	{
		SendDataBySessionType(SESSION_TYPE_MS2CS, dgnBind);
		return;
	}
	auto iter = mMultDgnMapID.begin();
	for (; iter != mMultDgnMapID.end(); )
	{
		dgnBind.info[dgnBind.num].roleId = dgnBind.roleId;
		memcpy_s(dgnBind.info[dgnBind.num].dgnKeyName, sizeof(dgnBind.info[dgnBind.num].dgnKeyName), iter->first.c_str(), sizeof(iter->first.c_str()));
		dgnBind.info[dgnBind.num].dgnId = iter->second;
		dgnBind.info[dgnBind.num].optType = DGN_BIND_INFO::DBI_OPTTYPE::Update;
		dgnBind.num++;
		iter++;
		if (dgnBind.num >= ProtoMS_DgnBindInfo::DBI_MaxSize::Info_Size || iter == mMultDgnMapID.end())
		{
			dgnBind.packIdx++;
			if (iter == mMultDgnMapID.end())// 最后一条消息置0
			{
				dgnBind.packIdx = 0;
			}
			SendDataBySessionType(SESSION_TYPE_MS2CS, dgnBind);
			dgnBind.num = 0;
		}
	}
}

void Player::SendSyncPlayerMailInfoToCS()
{
	ProtoMS_SyncMailInfoStatus data;
	data.playerguid = GetGUID();
	int num = MailVector.size();
	for (int i = 0; i < num; ++i) {
		data.info_status[data.num].mailid = MailVector[i].mail_id;
		data.info_status[data.num].status = MailVector[i].status;
		++data.num;
		if (data.num == 100)
		{
			SendDataBySessionType(SESSION_TYPE_MS2CS, data);
			data.num = 0;
			memset(data.info_status, 0, _countof(data.info_status));
		}
	}
	if (data.num && data.num != 100)
	{
		SendDataBySessionType(SESSION_TYPE_MS2CS, data);
	}
}

void Player::SendSyncPlayerTitleInfoToCS()
{
	auto &titleList = mTitleDataMgr.GetTitleList();
	if (titleList.empty())return;

	ProtoMS_SyncTitleInfo data;
	data.guid = GetGUID();
	int num = titleList.size();
	for (auto iter = titleList.begin(); iter != titleList.end();) {
		data.info[data.num] = *iter->second.get();
		++data.num;
		++iter;
		if (data.num == 100)
		{
			SendDataBySessionType(SESSION_TYPE_MS2CS, data);
			data.num = 0;
			memset(data.info, 0, _countof(data.info));
		}
	}
	if (data.num && data.num != 100)
	{
		SendDataBySessionType(SESSION_TYPE_MS2CS, data);
	}
}

void Player::MakePlayerAppearNtfData(ProtoMS_PlayerAppearNtf& ntf)
{
	auto& roleinfo = GetRoleBriefInfo();
	ntf.Reset();
	ntf.player_guid = GetGUID();
	strcpy_s(ntf.name, _countof(ntf.name), roleinfo.name);
	ntf.gender = roleinfo.gender;
	ntf.job = roleinfo.job;
	ntf.status = CheckAlive()?0:1;
	ntf.head = roleinfo.head;
	ntf.level = GetRoleProp(role_level);
	ntf.hair = roleinfo.hair;
	ntf.hair_color = roleinfo.hair_color;
	ntf.weapon = roleinfo.weapon;
	ntf.body = roleinfo.clothes;

	ntf.hp = GetRoleProp(role_hp);
	ntf.max_hp = GetRoleProp(role_max_hp);
	ntf.mp = GetRoleProp(role_mp);
	ntf.max_mp = GetRoleProp(role_max_mp);
	ntf.move_speed = GetRoleProp(role_move_speed);
	ntf.attack_speed = GetRoleProp(role_attack_speed);
	ntf.casting_speed = GetRoleProp(role_casting_speed);
	ntf.show_fashion = GetRoleProp(role_is_show_fashion);
	ntf.model_id = GetRoleProp(role_changed_modelid);

	ntf.dst_x = GetRolePosX();
	ntf.dst_y = GetRolePosY();
	ntf.dir = GetRoleDir();
	ntf.wings = 0;
	ntf.mount = 0;
	ntf.weapon_effect = 0;
	ntf.body_effect = 0;
	ntf.mount_effect = 0;
	ntf.pk = GetRoleProp(role_pk);
	ntf.title = 0;
	ntf.has_team = 0;
	ntf.stall = GetRoleProp(role_stall);
	std::string stallName = GetCustVar(CUST_VAR_STALL_NAME_KEY);
	(ntf.stall == stall_state_ok && stallName.empty()) ? stallName = "摆摊" : stallName;
	strncpy_s(ntf.stall_name, stallName.c_str(), _countof(ntf.stall_name) - 1);
	ntf.buff_num = 0;
	memset((void*)&ntf.buffs, 0, sizeof(ntf.buffs));
	memset((void*)&ntf.castle_name, 0, sizeof(ntf.castle_name));
	memset((void*)&ntf.alias, 0, sizeof(ntf.alias));
	strcpy_s(ntf.alias, _countof(ntf.alias), GetAlias().c_str());
	memset((void*)&ntf.custom, 0, sizeof(ntf.custom));
    memset((void*)&ntf.family_name, 0, sizeof(ntf.family_name));
    memset((void*)&ntf.family_title, 0, sizeof(ntf.family_title));
	ntf.appear_type = GetRoleAppearType();
	ntf.amulet = 0;
	ntf.equip_num = 0;
	memset(ntf.equips, 0, sizeof(ntf.equips));
	ntf.inner_force = 0;
	ntf.max_inner_force = 0;
	ntf.reserve_num = 0;
	memset(ntf.reserve_values, 0, sizeof(ntf.reserve_values));

    const auto &guildName = GetGuildName();
    if (!guildName.empty()) {

        auto guildMember = GetGuildDataMgr().GetGuildMember();
        if (guildMember && guildMember->status != guild_member_status_removed) {

            strcpy_s(ntf.family_name, _countof(ntf.family_name), guildName.c_str());
            strcpy_s(ntf.family_title, _countof(ntf.family_title), GuildMgr::GetInstance()->GetMemberTitle(guildMember->title));
        }

        auto *shabak = CastleWarMgr::GetInstance();
        if (shabak && shabak->IsWinnerGuild(guildName)) {

            auto *sbkcfg = shabak->GetCfg();
            if (sbkcfg) {
                strcpy_s(ntf.castle_name, _countof(ntf.castle_name), sbkcfg->MainCityMap.c_str());
            }
        }
    }

	auto &titleList = mTitleDataMgr.GetTitleList();
	for (auto& i : titleList) {
		if (i.second->isWear) {
			ntf.title_id[ntf.title_num++] = i.first;
		}
	}

}

void Player::OnGetSkillAck(const SKILL_INFO* pSkillInfo, uint16_t num)
{
    const auto *globalCfg = sGlobalConfig.GetData();
    if (!globalCfg) return;

	mRoleSkill->AddSkill(globalCfg->CommonAttackSkillID, true, 0);       // 普攻另外加，不存数据库

	for (uint16_t i = 0; i < num; ++i) {
		if (pSkillInfo[i].id == globalCfg->CommonAttackSkillID) continue;

		mRoleSkill->AddSkill(pSkillInfo[i].id, pSkillInfo[i].active, pSkillInfo[i].proficiency, pSkillInfo[i].cfg);
	}

	SendSkillAddAckToGS();
}

int Player::AddSkill(uint16_t skillID, bool active)
{
    auto *roleSkill = GetRoleSkill();
    if (!roleSkill) return ERR_UNKNOW;

    auto result = roleSkill->AddSkill(skillID, active, 0);
    if (result != ERR_OK) return result;

    SendSkillAddAckToGS(skillID);
    return ERR_OK;
}

void Player::RemoveSkill(uint16_t skillID)
{
	auto* roleSkill = GetRoleSkill();
	if (!roleSkill) return ;

	roleSkill->RemoveSkill(skillID);

	SendSkillDeleteAckToGS(skillID);
	return ;
}

void Player::RemoveSkillByChainID(uint32_t skillChainID)
{
    auto *roleSkill = GetRoleSkill();
    if (!roleSkill) return;
    auto skillIDs = roleSkill->GetSkillIDsByChainID(skillChainID);
    for (const auto &skillID : skillIDs) {
        roleSkill->RemoveSkill(skillID);
        SendSkillDeleteAckToGS(skillID);
    }
}

void Player::AlterSkill(uint16_t oldSkillID, uint16_t newSkillID)
{
	RemoveSkill(oldSkillID);
	AddSkill(newSkillID, true);
}

bool Player::SkillIsExist(uint16_t skillID)
{
	auto* roleSkill = GetRoleSkill();
	if (!roleSkill) return false;
	return 	roleSkill->IsSkillExist(skillID);
}

std::vector<uint16_t> Player::GetSkillIDList()
{
    std::vector<uint16_t> skillIDList;

    auto *roleSkill = GetRoleSkill();
    if (!roleSkill) return skillIDList;

    const auto &skillDataList = roleSkill->GetSkillList();
    skillIDList.reserve(skillDataList.size());

    for (const auto &skillData : skillDataList) {
        skillIDList.push_back(skillData.GetID());
    }

    return skillIDList;
}

bool Player::AddSkillProficiencyValue(uint32_t skillID, uint32_t value)
{
	auto roleSkill = GetRoleSkill();
	if (nullptr == roleSkill)return false;
	return roleSkill->AddProficiencyValue(skillID, value);
}

bool Player::SetSkillLevel(uint32_t skillID)
{
	auto roleSkill = GetRoleSkill();
	if (nullptr == roleSkill)return false;
	return roleSkill->SetSkillLevel(skillID);
}

void Player::UpdateReloginInfo()
{
	if (!mCurMap) {
		LOG_ERROR("send player relogin info failed!cur map is null!");
		OnLogout();
		return;
	}
	if (!mRoleAttr) {
		LOG_ERROR("send player relogin info failed!mRoleAttr is null!");
		OnLogout();
		return;
	}

	mRoleAttr->SetMoveType(move_type_jump);
	SetRolePos(GetRolePosX(), GetRolePosY());

	SendMapEnterNtf(mCurMap->GetMapConfig());
	SendPlayerAppearNtf(this);
	SendRoleAppNtf(this);

	HandleGoodsNotIssuedRecords();
	HandleGoodsNotPostIssuedRecords();

	mCurMap->GetMapAoi().RoleEnter(this);
	if (mRoleAttr->GetMoveType() == move_type_jump) mRoleAttr->SetMoveType(move_type_walk);

	NotifyAroundPlayers_AddBuff();
	//增加断线重连后 custvar 整包下发   
	mCustVarMody = true;

}

void Player::NotifyPlayer_StartMove(uint16_t nDstX, uint16_t nDstY)
{
	ProtoGS_MoveAck moveAck;
    moveAck.clsessid = GetClSessionID();
	moveAck.role_guid = GetGUID();
	moveAck.type = 0;
	moveAck.dst_x = nDstX;
	moveAck.dst_y = nDstY;
	moveAck.idx = 0;
	moveAck.ret = move_result_success;

	SendDataBySessionID(GetGsSessionID(), moveAck);
}

void Player::SendSkillAddAckToGS(uint16_t skillID)
{
	SAFE_BEGIN;
	if (!mRoleSkill) return;

	MSG_BUFFER_DATA(ProtoMS_SkillAddAck, skillAddAck);
    skillAddAck.role_guid = GetGUID();
	if (0 == skillID)
	{
		const auto& skillList = mRoleSkill->GetSkillList();

		if (skillList.empty()) return;

		skillAddAck.nClientSessionID = mClSessionID;

		const auto *globalCfg = sGlobalConfig.GetData();
		if (!globalCfg) return;

		uint16_t n = 0;
		for (const auto& it : skillList) {
			uint16_t nSkillID = it.GetID();
			if (nSkillID == globalCfg->CommonAttackSkillID) continue;       // 普攻客户端不用显示

			skillAddAck.info[n].id = nSkillID;
			skillAddAck.info[n].active = it.IsActive();
			skillAddAck.info[n].proficiency = 0;
			string cfg = RoleSkill::EncodeSkillCfg(it.GetSkillCfgModifyMap());
			if (!cfg.empty()) strcpy_s(skillAddAck.info[n].cfg, cfg);

			if (++n == _countof(skillAddAck.info)) break;
		}
		skillAddAck.num = n;
		skillAddAck.add = 1;
	}
	else
	{
		auto skillData = mRoleSkill->GetSkillData(skillID);
		if (!skillData) return;

		skillAddAck.nClientSessionID = GetClSessionID();
		skillAddAck.num = 1;

		auto& info = skillAddAck.info[0];
		info.id = skillID;
		info.active = skillData->IsActive();
		info.proficiency = 0;
		string cfg = RoleSkill::EncodeSkillCfg(skillData->GetSkillCfgModifyMap());
		if (!cfg.empty()) strcpy_s(info.cfg, cfg);
		skillAddAck.add = 0;
	}

	SendDataBySessionID(mGsSessionID, skillAddAck);

	SAFE_END;
}

void Player::SendSkillDeleteAckToGS(uint16_t skillID)
{
	auto* cfg = sSkillConfig.Get(skillID);
	if (!cfg) return;

	ProtoMS_DeleteSkillAck data;
	data.skillid = skillID;
	data.nClientSessionID = GetClSessionID();

	SendDataBySessionID(GetGsSessionID(), data);
}

void Player::SendSkillStatusNtfToGS(uint16_t skillID, bool active)
{
    if (!IsOnline()) return;

    ProtoMS_SkillStatusNtf data;
    data.sessionid = GetClSessionID();
    data.id = skillID;
    data.active = active;

    SendDataBySessionID(GetGsSessionID(), data);
}

void Player::SendSkillPropChangedNtfToGS(uint16_t skillID, const std::string& cfg)
{
	MSG_BUFFER_DATA(ProtoMS_SkillPropPermanentChangedNtf, data);
	data.player_guid = GetGUID();
	data.num = 1;
    data.info[0].id = skillID;
	strcpy_s(data.info[0].cfg, cfg);

	auto func = [&](Player* player) {
		if (!player) return;

		data.clsessid = player->GetClSessionID();
		SendDataBySessionID(player->GetGsSessionID(), data);
	};
	ApplyFuncToAroundPlayers(func);
}

void Player::SendSkillProficiencyNtfToGS(uint16_t skillID, uint32_t proficiency)
{
	ProtoMS_SkillProficiencyNtf data;
	data.clsessid = GetClSessionID();
	data.id = skillID;
	data.proficiency = proficiency;

	SendDataBySessionID(GetGsSessionID(), data);
}

void Player::SendPlayerSkillPropChangeNtf(Role* pRole)
{
	if (!pRole->IsPlayer() && !pRole->IsStallDummy()) return;
	if (!pRole->GetRoleSkill()) return;
	const auto& skillList = pRole->GetRoleSkill()->GetSkillList();
	if (skillList.empty()) return;

	auto globalCfg = sGlobalConfig.GetData();
	MSG_BUFFER_DATA(ProtoMS_SkillPropPermanentChangedNtf, data);
	data.player_guid = pRole->GetGUID();
	data.clsessid = GetClSessionID();
	data.num = 0;
	for (const auto& it : skillList) 
	{
		uint16_t nSkillID = it.GetID();
		if (globalCfg && nSkillID == globalCfg->CommonAttackSkillID) continue;

		data.info[data.num].id = nSkillID;
		string cfg = RoleSkill::EncodeSkillCfg(it.GetSkillCfgModifyMap());
		if (cfg.empty()) continue;

		strcpy_s(data.info[data.num].cfg, cfg);

		if (++data.num == _countof(data.info)) break;
	}
	SendDataBySessionID(GetGsSessionID(), data);
}

void Player::SendObjDisappearNtfToGS(const uint64_t& nObjID)
{
    if (!IsOnline()) return;
	ProtoMS_ObjDisappearNtf ntf;
	ntf.obj_guid = nObjID;
	ntf.sessid = GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), ntf);
}

void Player::SendPlayerAppearNtf(Role* pRole)
{
	if (!pRole->IsPlayer() && !pRole->IsStallDummy()) return;
	if (LuaGmMgr::GetInstance()->IsLuaGM(pRole->GetGUID())&&!LuaGmMgr::GetInstance()->IsLuaGM(GetGUID()))
	{
		return;
	}
	auto pPlayer = static_cast<Player*>(pRole);

	auto& pdata = gProtoMS_PlayerAppearNtf;
	pPlayer->MakePlayerAppearNtfData(pdata);
	pdata.sessid = GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), pdata);
}

void Player::RunServScript(const char* pScriptName, const char* pFuncName, const PARAM_INFO2* pParams, uint16_t nParamNum)
{
	SAFE_BEGIN;

	std::string sFunc = std::string(pScriptName) + "." + pFuncName;
    if (!LuaHost::GetInstance()->IsRunServScriptAllowedFunc(sFunc)) {
        LOG_WARN("Try to run %s, which is not allowed", sFunc.c_str());
        return;
    }

	auto params = NewLuaObj();
	auto ret = NewLuaObj();

	for (uint16_t i = 0; i < nParamNum; ++i) {

		switch (pParams[i].type) {      // 数据类型 1=INT8 2=UINT8 3=INT16 4=UINT16 5=INT32 6=UINT32 7=INT64 8=UINT64 9=字符串

		case 1:
			params[i + 1] = *(int8_t*)pParams[i].value;
			break;

		case 2:
			params[i + 1] = *(uint8_t*)pParams[i].value;
			break;

		case 3:
			params[i + 1] = *(int16_t*)pParams[i].value;
			break;

		case 4:
			params[i + 1] = *(uint16_t*)pParams[i].value;
			break;

		case 5:
			params[i + 1] = *(int32_t*)pParams[i].value;
			break;

		case 6:
			params[i + 1] = *(uint32_t*)pParams[i].value;
			break;

		case 7:
			params[i + 1] = *(int64_t*)pParams[i].value;
			break;

		case 8:
			params[i + 1] = *(uint64_t*)pParams[i].value;
			break;

		case 9:
			params[i + 1] = pParams[i].value;
			break;

		default:
			LOG_ERROR("Invalid param type: %u", pParams[i].type);
			return;
		}
	}

	LuaBindCallVoid(sFunc, GetGUIDAsString(), params, ret);

	if (luabind::type(ret["result"]) == LUA_TSTRING) {

		auto res = luabind::object_cast<std::string>(ret["result"]);

		ProtoGS_RunServScriptAck runServScriptAck;
		runServScriptAck.sessionid = mClSessionID;
		runServScriptAck.token = mToken;
		runServScriptAck.playerid = mUserID;
		strcpy_s(runServScriptAck.script_name, _countof(runServScriptAck.script_name), pScriptName);
		strcpy_s(runServScriptAck.result, _countof(runServScriptAck.result), res.c_str());

		SendDataBySessionID(mGsSessionID, runServScriptAck);
	}

	SAFE_END;
}

void Player::RunClientScript(const char *pScriptName, const char *pContent, bool bCompress)
{
    if (!pScriptName || !pContent) return;
    if (!IsOnline()) return;

	MSG_BUFFER_DATA(ProtoMS_RunClientScript, req);
	req.clientSessionID = mClSessionID;
	strcpy_s(req.form_name, pScriptName);
	req.comp = bCompress;

	if (bCompress) {
		uLongf nDstLen = sizeof(req.form_content);
		auto result = compress((Bytef*)req.form_content, &nDstLen, (const Bytef*)pContent, strlen(pContent));
		if (result != Z_OK) {
			LOG_ERROR("compress failed with error %d", result);
			return;
		}
		req.size = nDstLen;
	}
	else {
		strcpy_s(req.form_content, pContent);
		req.size = (uint16_t)strlen(pContent);
	}

	SendDataBySessionID(mGsSessionID, req);
}


void Player::RunClientScript_Around(const char* pScriptName, const char* pContent, bool bCompress)
{
	if (!pScriptName || !pContent) return;
	if (!IsOnline()) return;
	auto map = GetCurMap();
	if (!map) return;
	MSG_BUFFER_DATA(ProtoMS_RunClientScript, req);
	//req.clientSessionID = mClSessionID;
	strcpy_s(req.form_name, pScriptName);
	req.comp = bCompress;

	if (bCompress) {
		uLongf nDstLen = sizeof(req.form_content);
		auto result = compress((Bytef*)req.form_content, &nDstLen, (const Bytef*)pContent, strlen(pContent));
		if (result != Z_OK) {
			LOG_ERROR("compress failed with error %d", result);
			return;
		}
		req.size = nDstLen;
	}
	else {
		strcpy_s(req.form_content, pContent);
		req.size = (uint16_t)strlen(pContent);
	}
	auto clsessidsMap = map->GetAroundPlayerCLSessionID(this);
	SendDataBySessionID(clsessidsMap, req);
}


void Player::SendDestroyItem(uint64_t itemGUID)
{
    if (!IsOnline()) return;
	ProtoMS_ItemDestroyAck pattrntf;
	pattrntf.item_guid = itemGUID;
	pattrntf.sessid = GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), pattrntf);
}

void Player::SendRoleAttrExtNtf()
{
    ProtoMS_RoleAttrExtNtf data;
    data.player_guid = GetGUID();
    data.sessid = GetClSessionID();

    auto &n = data.num;
    n = 0;

    for (int prop = role_attr_ext_min; prop <= role_attr_ext_max; ++prop) {
        auto value = GetRoleProp64(prop);
        data.attr_name[n] = prop;
        data.attr_value[n] = value;

        if (++n == _countof(data.attr_name)) {
            SendDataBySessionID(GetGsSessionID(), data);
            n = 0;
        }
    }

    if (n) SendDataBySessionID(GetGsSessionID(), data);
}

void Player::SendRoleDynAttrsNtf(ProtoMS_RoleDynAttrsNtf& ntf)
{
	ntf.sessid = GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), ntf);
}

void Player::SendRoleCustVarNtf(ProtoMS_RoleCustVarNtf& ntf)
{
	ntf.sessid = GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), ntf);
}

void Player::SendRoleDirChangeNtf(Role* role, ProtoGS_TurnNtf& ntf)
{
	if (nullptr == role) {
		return;
	}

	ntf.sessionid = GetClSessionID();
	ntf.token = GetToken();
	ntf.playerid = GetUserID();
	SendDataBySessionID(GetGsSessionID(), ntf);
}

void Player::SendRoleDieNtf(Role* role, ProtoMS_ObjDieNtf& ntf)
{
	if (nullptr == role) {
		return;
	}

	ntf.clientSessionID = GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), ntf);
}

void Player::SendRoleObjDisappearNtf(ProtoMS_ObjDisappearNtf& ntf) {
    if (!IsOnline()) return;
	ntf.sessid = GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), ntf);
}

void Player::SendObjDisappearNtfToGSBySingle(const uint64_t& nObjID) {
    if (!IsOnline()) return;
	ProtoMS_ObjDisappearNtf ntf;
	ntf.obj_guid = nObjID;
	ntf.sessid = GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), ntf);
}

void Player::SendRoleItemAppearNtf(ProtoMS_ItemAppearNtf4& ntf)
{
	ntf.clsessid = GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), ntf);
}

void Player::SendRoleNameChangeNtf(ProtoGS_PlayerSetNameNtf& ntf)
{
	ntf.sessionid = GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), ntf);
}

void Player::SendRoleWearTitleNtf(ProtoGS_TitleWearNtf& ntf)
{
	ntf.sessionid = GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), ntf);
}

void Player::SendRoleUnWearTitleNtf(ProtoGS_TitleUnWearNtf& ntf)
{
	ntf.sessionid = GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), ntf);
}

void Player::OnlyUpdateAppearNtf(Role* role)
{
	if (!role) return;
	// 自己也更新
	//if (role->GetGUID() == GetGUID()) return;

	if (role->IsPlayer() || role->IsStallDummy()) {
		SendPlayerAppearNtf(role);
		role->SendRoleAppNtf(this);
	}
	else if (role->IsMonster()) {
		auto monster = static_cast<Monster*>(role);
		if (!monster)return;
		SendMonsterAppearNtf(monster);
	}
	else if (role->IsNpc()) {
		ProtoMS_NpcAppearNtf pdata;
		static_cast<Npc*>(role)->MakeNpcAppearNtfData(pdata);
		pdata.clientSessionID = GetClSessionID();
		SendDataBySessionID(GetGsSessionID(), pdata);
	}
	else if (role->IsPet())
	{
		auto pet = static_cast<Pet*>(role);
		if (!pet)return;
		SendMonsterAppearNtf(pet);
	}
	else if (role->IsPlayerDoplganr()) {
		role->SendAppearNtf(this);
		role->SendRoleAppNtf(this);
	}
}

void Player::SendEffectAppearNtf(ProtoMS_EffectAppearNtf& ntf)
{
	ntf.sessionid = GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), ntf);
}

void Player::SendEffectDisAppearNtf(ProtoMS_EffectDisAppearNtf& ntf)
{
	ntf.sessionid = GetClSessionID();
	SendDataBySessionID(GetGsSessionID(), ntf);
}

void Player::HandlePlayerSwitch(uint8_t id, uint8_t val)
{
	if (id == 0) SetRoleProp(role_friend_switch, val);
	if (id == 1) SetRoleProp(role_team_switch, val);
	if (id >= 2) LOG_ERROR("player_switch_type_max!");
}

void Player::Relive(uint8_t type, uint32_t sessid)
{
    switch (type) {
    case 1:     // 原地复活
        break;

    case 2:     // 回城复活
        RebirthBackToTown();
        break;

    case 3:     // 副本入口复活
        break;

    default:
        break;
    }
}

void Player::RebirthBackToTown()
{
	DATA::Map* fromMapCfg = nullptr;
	DATA::Map* toMapCfg = nullptr;
	if (GetCurMap()) fromMapCfg = GetCurMap()->GetMapConfig();
    if (!LeaveCurMap(true)) return;

    const auto &rebirthMap = mRoleExtraInfo.rebirthMap ? mRoleExtraInfo.rebirthMap : mRoleExtraInfo.birthMap;

    const auto *mapCfg = sMapConfig.Get(rebirthMap);
    if (!mapCfg) return;

    const DATA::RegionCommon *region = nullptr;

    const auto *regionCfg = sReliveRegionConfig.Get(mapCfg->KeyName);
    if (regionCfg) {
        region = &regionCfg->m_Region;
    }
    else {
        const auto *regionCfg = sBornRegionConfig.Get(mapCfg->KeyName);
        if (regionCfg) region = &regionCfg->m_Region;
    }
    if (!region) return;

    auto *map = MapMgr::GetInstance()->FindMap(mapCfg->KeyName);
    if (!map) return;

    uint16_t x, y;

    if (!map->GetRandBlankPointInRange(region->left, region->top,
        std::max<uint16_t>(region->width, 1), std::max<uint16_t>(region->height, 1), x, y)) {

        if (!map->GetRandBlankPointInRange(0, 0, map->GetWidth(), map->GetHeight(), x, y))
            return;
    }

    const auto *roleCfg = sRoleConfig.Get(GetRoleProp(role_level), GetRoleProp(role_job));
    if (!roleCfg) return;

    mRoleExtraInfo.hp = roleCfg->HP;
    mRoleExtraInfo.mp = roleCfg->MP;

    EnterMap(map, x, y);
	if (GetCurMap()) toMapCfg = GetCurMap()->GetMapConfig();

    GetRoleState()->SetState(role_state_idle);

	if (fromMapCfg && toMapCfg && fromMapCfg != toMapCfg)
	{
		SendDBLogData(log_type_entery_exit_map, LogEnteryExitMap(GetGUID(), fromMapCfg->Id, fromMapCfg->MapType, toMapCfg->Id, toMapCfg->MapType, "回城复活"));
	}
}

bool Player::LeaveCurMap(bool destroySummonMonster)
{
    auto *curMap = GetCurMap();
    if (!curMap) return false;

    curMap->RoleLeave(this);

	DropItemByDropProcess(player_drop_type_leave_map);

    curMap->RemoveMonitorRegionForTrapSkill(GetGUID());

	MarkLeaveMap(curMap);
    mSummonMonsterMgr.SummonMonsterLeaveMap();
    mSummonMonsterMgr.DestroySummonMonster(destroySummonMonster);
	mPetMgr.PetLeaveMap();

    if (mDoplganrMgr) {
        mDoplganrMgr->DoplganrLeaveMap();
    }

    Role::OnLeaveCurMap();

    return true;
}

bool Player::EnterMap(Map *map, uint16_t x, uint16_t y)
{
    if (!map) return false;

    OnEnterMap(map);
    SetRolePosNoEvent(x, y);

    SendMapEnterNtf(map->GetMapConfig());
    SendPlayerAppearNtf(this);

    SendRoleAppNtf(this);
	SendPlayerSkillPropChangeNtf(this);
    map->RoleEnter(this);

	MarkEntryMap(map);
    mSummonMonsterMgr.SummonMonsterEnterMap();
	mPetMgr.PetEnterMap();

    if (mDoplganrMgr) {
        mDoplganrMgr->DoplganrEnterMap(map);
    }

	UpdateRoleInfo();
    return true;
}

void Player::MarkEntryMap(Map* map)
{
	if (map && map->GetMapConfig() && EMT_DGN == map->GetMapConfig()->MapType)
	{
		mCurMulDgnMapID = map->GetGUID();
		mInDgnMap = true;
		map->AddPlayerGuid(GetGUID());
	}
}

void Player::MarkLeaveMap(Map* map)
{
	if (map && map->GetMapConfig() && EMT_DGN == map->GetMapConfig()->MapType)
	{
		mCurMulDgnMapID = 0;
		mInDgnMap = false;
		map->RemovePlayerGuid(GetGUID());
	}
}

void Player::SetOnlineState(uint8_t state)
{
    auto oldOnlineState = mOnlineState;
    auto newOnlineState = state;
    if (oldOnlineState == newOnlineState) return;

    mOnlineState = newOnlineState;
    mGuildDataMgr.SetGuildMemberOnline(newOnlineState == online_state_logged_in);

    if (oldOnlineState == online_state_logged_in &&
        newOnlineState == online_state_disconnected) {              // 断线
        ApplyEventHandlers_RoleOffline();
    }
    else if (oldOnlineState == online_state_disconnected &&
             newOnlineState == online_state_logged_in) {            // 重新上线
        ApplyEventHandlers_RoleOnline();
    }
}

void Player::SendUpdateOnlineStateToCS(uint32_t state)
{
    ProtoGS_UpdateOnlineState data;
    data.roleid = GetGUID();
    data.token = GetToken();
    data.state = static_cast<uint8_t>(state);
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void Player::OnLogin()
{
    auto map = GetCurMap();
    if (!map) return;

	auto mapCfg = map->GetMapConfig();
	if (!mapCfg) return;
	auto roleCfg = sRoleConfig.Get(mRoleBriefInfo.level, mRoleBriefInfo.job);
	if (!roleCfg) return;

	uint32_t hp = mRoleExtraInfo.hp, mp = mRoleExtraInfo.mp;
	SetLoginTime(time(nullptr));
	SetOnlineState(online_state_logged_in);
    InitRoleAttr(roleCfg);
    Role::Init();
	mRoleExtraInfo.hp = !hp ? SetRoleProp(role_hp, roleCfg->HP) : SetRoleProp(role_hp, hp);
	mRoleExtraInfo.mp = !mp ? SetRoleProp(role_mp, roleCfg->MP) : SetRoleProp(role_mp, mp);

    
    SendUpdateOnlineStateToCS(online_state_logged_in);
    RoleInfoCache::GetInstance()->OnRoleLogin(GetGUID(), GetName());
    HandleGoodsNotIssuedRecords();
	HandleGoodsNotPostIssuedRecords();

	// 初始化其他功能模块数据
    mGuildDataMgr.InitGuildData();
	//mQuestDataMgr.ResumeQuest();

	TradeMgr::GetInstance()->GetPlayerDelegateList(GetGUID(), mBuyDelegateInfo);
	TradeMgr::GetInstance()->GetPlayerDelegateList(GetGUID(), mSellDelegateInfo);
	TradeMgr::GetInstance()->GetPlayerBuyRecordsList(GetGUID(), mTradeBuyRecords);
	TradeMgr::GetInstance()->GetPlayerSellRecordsList(GetGUID(), mTradeSellRecords);
	BindStallDummy();

	SendPlayerAppearNtf(this);
	SendRoleAppNtf(this);
    map->RoleEnter(this);

	SendDBLogData(log_type_entery_exit_map, LogEnteryExitMap(GetGUID(), 0, 0, mapCfg->Id, mapCfg->MapType, "登录"));

	if (mRoleBriefInfo.status == role_status_new) {
		mRoleBriefInfo.status = role_status_normal;
		TRIGGER_EVENT(this, trigger_first_in_game, GetGUIDAsString());
	}
	TRIGGER_EVENT(this, trigger_login, GetGUIDAsString());
	mTitleDataMgr.Init();
	StartSyncDataTimer();
    SendAutoPickupSettingsNtfToGS();

	mLoginOutTimestamp.first = ITimeHelper::GetInstance()->GetTimeStamp();
}

void Player::OnLogout()
{
	mLoginOutTimestamp.second = ITimeHelper::GetInstance()->GetTimeStamp();
	// 最先调用,脚本中有设置相关角色数据
	TRIGGER_EVENT(this, trigger_logout, GetGUIDAsString());

	DropItemByDropProcess(player_drop_type_logout);

	StopSyncDataTimer();
	GetRoleBuff()->PauseBuff();
	GameMall::GetInstance()->DeleteMallLimitSingle(this->GetGUID());

	auto map = GetCurMap();
	DATA::Map* mapCfg = nullptr;
	if (map)
	{
		map->RoleExit(this);
		map->RemoveMonitorRegionForTrapSkill(GetGUID());
		mapCfg = map->GetMapConfig();
	}
	mSummonMonsterMgr.SummonMonsterLeaveMap();
    mSummonMonsterMgr.DestroySummonMonster();
	mPetMgr.PetLeaveMap();
	mPetMgr.DestroyPet();
    mGuildDataMgr.UpdateGuildInfoOnLogout();
	mTeamDataMgr.HandleTeamLeave();
    if (mDoplganrMgr) {
        mDoplganrMgr->DoplganrLeaveMap();
        mDoplganrMgr->DestroyDoplganr();
    }

	UnBindStallDummy();
	SyncPlayerData();

	MapRoleMgr::GetInstance()->RemovePlayer(GetGUID());
	ReleaseGrid();

    if (IsOnline()) {
	    ProtoGS_ExitGSAck ack;
	    ack.exittype = GetExitType();
	    ack.sessionid = GetClSessionID();
	    SendDataBySessionID(GetGsSessionID(), ack);
    }

	if (mapCfg) SendDBLogData(log_type_entery_exit_map, LogEnteryExitMap(GetGUID(), mapCfg->Id, mapCfg->MapType, 0, 0, "登出", "", (mLoginOutTimestamp.second - mLoginOutTimestamp.first) / 1000));

    SetOnlineState(online_state_not_logged_in);
    SendUpdateOnlineStateToCS(online_state_not_logged_in);
}

void Player::SyncPlayerData()
{
	//如果玩家已经没有属性   不保存到cs   并且让玩家下线
	if (nullptr == this->GetRoleAttr()) {
		ProtoGS_KickOutByLock ack;
		ack.info = E_EXIT_EXITGS;
		ack.sessionid = GetClSessionID();
		ack.token = GetToken();
		SendDataBySessionID(GetGsSessionID(), ack);
		return;
	}
    UpdateRoleInfo();
    SendSyncRoleInfoReqToCS();
	SendSyncRoleDynAttrReqToCS();
    SendSyncItemInfoReqToCS();
    SendSyncItemDynAttrsToCS();
    SendSyncBuffReqToCS();
    SendSyncSkillReqToCS();
    SendSyncPlayerCustVarToCS();
    SendSyncPlayerItemCustVarToCS();
	SendSyncPlayerQuickBarSetToCS();
	//SendSyncPlayerDgnBindInfoToCS();
	SendSyncPlayerMailInfoToCS();
	SendSyncPlayerTitleInfoToCS();
	//mQuestDataMgr.SaveQuest();
}

void Player::ResetSyncPlayerTimer()
{
	if (0 != mSyncTimerId)
	{
		TimerData* timer = ITimeHelper::GetInstance()->GetTimer(mSyncTimerId);
		if (timer) timer->tick64 = GetTimeStampMillisecond() + timer->interval;
	}
}

void Player::OnExit(uint8_t nExitType)
{
	SetExitType(nExitType);

	OnLogout();
}

void Player::OnUpgrade(DATA::Role* preCfg, DATA::Role* curCfg)
{
	if (!preCfg || !curCfg) return;
	UpgradeUpdateRoleProp(preCfg, curCfg);

	TRIGGER_EVENT(this, trigger_level_up, GetGUIDAsString(), curCfg->Level);
    SendLevelUpNtfToAroundPlayers();
}

void Player::GetRoleInfoReq(void)
{
	ProtoMS_GetRoleInfoReq req;
	req.role_id = GetGUID();
	req.token = GetToken();
	SendDataBySessionType(SESSION_TYPE_MS2CS, req);
}

void Player::ClearRoleInfo(void)
{
	ProtoMS_ClearRoleInfoNtf ntf;
	ntf.role_id = GetGUID();
	ntf.token = GetToken();
	SendDataBySessionType(SESSION_TYPE_MS2CS, ntf);
}

void Player::DelRoleInfo(const std::string& info)
{
	ProtoMS_DeleteRoleInfoNtf ntf;
	ntf.role_id = GetGUID();
	ntf.token = GetToken();
	memcpy(ntf.base_info, info.c_str(), sizeof(ntf.base_info));
	SendDataBySessionType(SESSION_TYPE_MS2CS, ntf);
}

void Player::InsertRoleInfo(const std::string& info)
{
	ProtoMS_InsertRoleInfoNtf ntf;
	ntf.role_id = GetGUID();
	ntf.token = GetToken();
	memcpy(ntf.base_info, info.c_str(), sizeof(ntf.base_info));
	SendDataBySessionType(SESSION_TYPE_MS2CS, ntf);
}

void Player::UpdateRoleInfo(const std::string& info)
{
	ProtoMS_UpdateRoleInfoNtf ntf;
	ntf.role_id = GetGUID();
	ntf.token = GetToken();
	memcpy(ntf.base_info, info.c_str(), sizeof(ntf.base_info));
	SendDataBySessionType(SESSION_TYPE_MS2CS, ntf);
}

int32_t Player::GetAttackMode()
{
    auto *shabak = CastleWarMgr::GetInstance();
    if (shabak && shabak->IsInWar()) {

        const auto &guild = GetGuildName();
        if (shabak->IsEngagedGuild(guild) && shabak->IsInShabak(this)) {

            return atk_mode_guild;
        }
    }

    return Role::GetAttackMode();
}

bool Player::CheckCross()
{
    auto *mgr = CastleWarMgr::GetInstance();
    if (mgr) {
        const auto &guild = GetGuildName();
        if (mgr->IsWinnerGuild(guild)) {
            auto x = GetRolePosX();
            auto y = GetRolePosY();
            if (mgr->IsPalaceFrontDoorMonsterSpot(x, y))
                return true;
        }
    }

	return false;
}

bool Player::CheckTakeGrid(uint16_t x, uint16_t y)
{
    auto *mgr = CastleWarMgr::GetInstance();
    if (mgr) {
        const auto &guild = GetGuildName();
        if (mgr->IsWinnerGuild(guild) && mgr->IsPalaceFrontDoorMonsterSpot(x, y)) {
            return true;        // 皇宫归属行会成员可穿过正门怪物
        }
    }

    auto* map = GetCurMap();
    if (!map) return false;

    return !map->GetMapGrid().IsForbid_PlayerMoveAck(x, y, this);
}

void Player::CheckJump(void)
{
	auto map = GetCurMap();
	if (map) map->Jump(this);
}

void Player::NotifyJump(const char* mapname, uint16_t pox, uint16_t poy, uint16_t type)
{
    JumpMap(mapname, pox, poy, type);
}

void Player::SendSyncBuffReqToCS()
{
    auto roleBuff = GetRoleBuff();
    if (!roleBuff) return;

    std::list<BUFF_INFO_DB> list;
    roleBuff->GetAllBuffInfo(list);

	MSG_BUFFER_DATA(ProtoMS_SyncBuffReq, syncBuffReq);
	syncBuffReq.playerid = GetUserID();
	syncBuffReq.roleid = GetGUID();
	syncBuffReq.roleType = GetType();
	syncBuffReq.buffNum = 0;
	syncBuffReq.beFirstPack = 1;
	if (!list.empty())
	{
		auto iter = list.begin();
		for (; iter != list.end();)
		{
			syncBuffReq.buffs[syncBuffReq.buffNum] = *iter;
			syncBuffReq.buffNum++; iter++;
			if (syncBuffReq.buffNum == _countof(syncBuffReq.buffs) || iter == list.end())
			{
				SendDataBySessionType(SESSION_TYPE_MS2CS, syncBuffReq);
				syncBuffReq.buffNum = 0;
				syncBuffReq.beFirstPack = 0;
			}
		}
	}
	else
	{
		SendDataBySessionType(SESSION_TYPE_MS2CS, syncBuffReq);
	}
}

void Player::SendSyncSkillReqToCS()
{
	MSG_BUFFER_DATA(ProtoMS_SyncSkillReq, syncSkillReq);
	syncSkillReq.playerid = GetUserID();
	syncSkillReq.roleid = GetGUID();
	syncSkillReq.skillNum = GetRoleSkill()->GetSkillList(syncSkillReq.skillInfo, _countof(syncSkillReq.skillInfo));

	SendDataBySessionType(SESSION_TYPE_MS2CS, syncSkillReq);
}

void Player::UpdateRoleInfo()
{
	
	mRoleBriefInfo.level = GetRoleProp(role_level);
	mRoleBriefInfo.vipLevel = GetRoleProp(role_vip_level);

	mRoleExtraInfo.hp = GetRoleProp(role_hp);
	mRoleExtraInfo.mp = GetRoleProp(role_mp);
	mRoleExtraInfo.exp = GetRoleProp64(role_exp);
	mRoleExtraInfo.atkMode = GetRoleProp(role_atk_mode);
	mRoleExtraInfo.rolePk = GetRoleProp(role_pk);
	mRoleExtraInfo.modelID = GetRoleProp(role_changed_modelid);


	if (!mInDgnMap) {
		SaveCurLocation();
	}

	mRoleExtraInfo.gold = GetRoleProp64(role_gold);
	mRoleExtraInfo.bindGold = GetRoleProp64(role_bind_gold);
	mRoleExtraInfo.ingot = GetRoleProp64(role_ingot);
	mRoleExtraInfo.bindIngot = GetRoleProp64(role_bind_ingot);
	mRoleExtraInfo.integral = GetRoleProp64(role_integral);
	mRoleExtraInfo.depositGold = GetRoleProp64(role_gold_deposit);
	mRoleExtraInfo.innerForceExp = GetRoleProp64(role_inner_force_exp);
}

void Player::SendSyncRoleInfoReqToCS()
{
	ProtoMS_SyncRoleInfoReq syncRoleInfoReq;
	syncRoleInfoReq.userid = GetUserID();
	syncRoleInfoReq.roleid = GetGUID();
	syncRoleInfoReq.roleBriefInfo = mRoleBriefInfo;
	syncRoleInfoReq.roleExtraInfo = mRoleExtraInfo;
	syncRoleInfoReq.roleSettings = mRoleSettings;

	SendDataBySessionType(SESSION_TYPE_MS2CS, syncRoleInfoReq);
}

void Player::SendChangePlayerNameNtf(const std::string& name)
{

}

void Player::SendSyncRoleDynAttrReqToCS()
{
	auto* roleAttr = GetRoleAttr();
	if (!roleAttr) return;

	auto& dynAttrs = roleAttr->GetDynAttrs();
	if (dynAttrs.empty()) return;


	ROLE_DYN_ATTRS_LIST attrsList;
	attrsList.emplace_back(GetGUID(), dynAttrs);

	ProtoMS_SyncRoleDynAttrs data;
	data.playerid = GetUserID();
	data.roleid = GetGUID();
	data.attrs_list = &attrsList;

	SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

uint64_t Player::GetMapCode()
{
	auto map = GetCurMap();
	if (map)
	{
		auto mapconfig = sMapConfig.GetByKeyName(map->GetName());
		return mapconfig->Id;
	}
	else
	{
		return 0;
	}

}

void Player::EnterShop(uint16_t nShopID)
{
	if (!ShopMgr::GetInstance()->InitShop(nShopID)) {
		LOG_ERROR("InitShop failed. nShopID: %u", nShopID);
		return;
	}

	auto pShopItems = ShopMgr::GetInstance()->GetShopItems(nShopID);
	if (!pShopItems) {
		LOG_ERROR("pShopItems is NULL. nShopID: %u", nShopID);
		return;
	}

	ProtoMS_TradeNpcShopNtf tradeNpcShopNtf;
	tradeNpcShopNtf.clientSessionID = GetClSessionID();
	tradeNpcShopNtf.shop_id = nShopID;

	auto& i = tradeNpcShopNtf.item_count;
	i = 0;

	for (auto it : *pShopItems) {

		tradeNpcShopNtf.item_list[i] = it.second;

		if (++i >= _countof(tradeNpcShopNtf.item_list)) break;
	}

	SendDataBySessionID(GetGsSessionID(), tradeNpcShopNtf);
}

void Player::BuyItem(uint16_t nShopID, uint16_t nItemIndex, uint16_t nAmount, bool bUseBind)
{
	auto pShopItem = ShopMgr::GetInstance()->GetShopItem(nShopID, (uint8_t)nItemIndex);
	if (!pShopItem) {
		LOG_ERROR("pShopItem is NULL. nShopID: %u, nItemIndex: %u", nShopID, nItemIndex);
		SendErrorAck(ERR_ITEM_NOT_EXIST);
		return;
	}

	if (pShopItem->num < nAmount) {
		SendErrorAck(ERR_ITEM_NOT_ENOUGH);
		return;
	}

	if (GetRolePack()->GetIdleBagCount() < nAmount) {
		SendErrorAck(ERR_BAG_SPACE_NOT_ENOUGH);
		return;
	}

	auto nCost = nAmount * pShopItem->value;
	auto nPayMethod = bUseBind ? role_bind_gold : role_gold;
	auto nDeposit = GetRoleProp64(nPayMethod);

	if (nDeposit < nCost) {
		SendErrorAck(bUseBind ? ERR_DEPOSIT_NOT_ENOUGH_BIND_GOLD : ERR_DEPOSIT_NOT_ENOUGH_GOLD);
		return;
	}

	auto nItemAdded = 0;
	log_params lp{ "商店购买" };
	for (; nItemAdded < nAmount; ++nItemAdded) {
		if (!AddPlayerItem(pShopItem->id, lp)) {
			break;
		}
	}

	if (nItemAdded < nAmount) {
		SendErrorAck(ERR_ITEM_ADD);
	}

	if (pShopItem->num != INFINITE_ITEM_NUM) pShopItem->num -= nItemAdded;

	SetRoleProp64(nPayMethod, nDeposit - int64_t(nItemAdded) * pShopItem->value, lp);
}

int Player::EnterDgnMap(const std::string& sMapKeyName, const log_params& lp)
{
	SAFE_BEGIN_EX;

	int32_t res = 0;
	auto pCurMap = GetCurMap();
	if (!pCurMap) {
		LOG_ERROR("pCurMap is NULL");
		return ++res;
	}

	auto pMapConfig = sMapConfig.Get(sMapKeyName);
	if (!pMapConfig) {
		LOG_ERROR("pMapConfig is NULL. sMapKeyName: %s", sMapKeyName.c_str());
		return ++res;
	}

	mDgnMap = std::make_unique<Map>();
	if (!mDgnMap->Init(pMapConfig)) {
		return ++res;
	}

	SaveCurLocation();
    uint16_t posX = mDgnMap->GetWidth() / 2;
    uint16_t posY = mDgnMap->GetHeight() / 2;
    if (!mDgnMap->FindJumpablePos(posX, posY)) return ++res;

	DATA::Map* fromMapCfg = nullptr;
	DATA::Map* toMapCfg = nullptr;
	if (GetCurMap()) fromMapCfg = GetCurMap()->GetMapConfig();
    if (!LeaveCurMap(false)) return ++res;

    if (!EnterMap(mDgnMap.get(), posX, posY)) return ++res;
	if (GetCurMap()) toMapCfg = GetCurMap()->GetMapConfig();

	if (fromMapCfg && toMapCfg && fromMapCfg != toMapCfg)
	{
		SendDBLogData(log_type_entery_exit_map, LogEnteryExitMap(GetGUID(), fromMapCfg->Id, fromMapCfg->MapType, toMapCfg->Id, toMapCfg->MapType, std::string("进入单人副本 ") + std::string(toMapCfg->Name), lp.info));
	}

	return res;
	SAFE_END_EX(10);
}

int Player::EnteryMulDgnMap(Map* mulDgnMap, uint16_t posX, uint16_t posY, const log_params& lp)
{

	SAFE_BEGIN_EX;
	int32_t res = 0;
	auto pCurMap = GetCurMap();
	if (!pCurMap) {
		LOG_ERROR("pCurMap is NULL");
		return ++res;
	}

    if (!mulDgnMap) {
        LOG_ERROR("mulDgnMap is NULL");
        return ++res;
    }

	SaveCurLocation();

	if (!mulDgnMap->FindJumpablePos(posX, posY)) return ++res;

	DATA::Map* fromMapCfg = nullptr;
	DATA::Map* toMapCfg = nullptr;
	if (GetCurMap()) fromMapCfg = GetCurMap()->GetMapConfig();
	if (!LeaveCurMap(false)) return ++res;

	if (!EnterMap(mulDgnMap, posX, posY)) return ++res;
	if (GetCurMap()) toMapCfg = GetCurMap()->GetMapConfig();

	if (fromMapCfg && toMapCfg && fromMapCfg != toMapCfg)
	{
		SendDBLogData(log_type_entery_exit_map, LogEnteryExitMap(GetGUID(), fromMapCfg->Id, fromMapCfg->MapType, toMapCfg->Id, toMapCfg->MapType, std::string("进入多人副本 ") + std::string(toMapCfg->Name), lp.info));
	}
	return res;
	SAFE_END_EX(10);
}

void Player::SaveCurLocation()
{
	mRoleExtraInfo.mapid = GetCurMap()->GetTemplateID();
	mRoleExtraInfo.posx = GetRolePosX();
	mRoleExtraInfo.posy = GetRolePosY();
	mRoleExtraInfo.dir = GetRoleDir();
}

int Player::ExitDgnMap()
{
	SAFE_BEGIN_EX;

	//if (!mInDgnMap) return 1;

	if (!mDgnMap) {
		LOG_ERROR("mDgnMap is NULL");
		return 2;
	}

	auto pPrevMap = MapMgr::GetInstance()->FindMapByID(mRoleExtraInfo.mapid);
	if (!pPrevMap) {
		LOG_ERROR("pPrevMap is NULL. mapid: %u", mRoleExtraInfo.mapid);
		return 3;
	}

    if (mDgnMap->GetGUID() != GetCurMap()->GetGUID())
    {
        return 0;
    }

	DATA::Map* fromMapCfg = nullptr;
	DATA::Map* toMapCfg = nullptr;
	if (GetCurMap()) fromMapCfg = GetCurMap()->GetMapConfig();
    if (!LeaveCurMap(false)) return 4;

    if (!EnterMap(pPrevMap, mRoleExtraInfo.posx, mRoleExtraInfo.posy)) return 5;
	if (GetCurMap()) toMapCfg = GetCurMap()->GetMapConfig();

	if (fromMapCfg && toMapCfg && fromMapCfg != toMapCfg)
	{
		SendDBLogData(log_type_entery_exit_map, LogEnteryExitMap(GetGUID(), fromMapCfg->Id, fromMapCfg->MapType, toMapCfg->Id, toMapCfg->MapType, std::string("进入地图 ") + std::string(toMapCfg->Name)));
	}

	mDgnMap = nullptr;
	return 0;
	SAFE_END_EX(0);
}

int Player::ExitMulDgnMap(Map* mulDgnMap)
{

	SAFE_BEGIN_EX;

	//if (!mInDgnMap) return 1;

	if (!mulDgnMap) {
		LOG_ERROR("mulDgnMap is NULL");
		return 2;
	}

	auto pPrevMap = MapMgr::GetInstance()->FindMapByID(mRoleExtraInfo.mapid);
	if (!pPrevMap) {
		LOG_ERROR("pPrevMap is NULL. mapid: %u", mRoleExtraInfo.mapid);
		return 3;
	}

	// 在副本里可能没通过EnteryMulDgnMap退出,导致玩家退出到其他图,但是mulDgnMap的playerGuidSet没删除玩家
	if (mulDgnMap->GetGUID() != GetCurMap()->GetGUID())
	{
		return 0;
	}

	DATA::Map* fromMapCfg = nullptr;
	DATA::Map* toMapCfg = nullptr;
	if (GetCurMap()) fromMapCfg = GetCurMap()->GetMapConfig();
	if (!LeaveCurMap(false)) return 4;

	if (!EnterMap(pPrevMap, mRoleExtraInfo.posx, mRoleExtraInfo.posy)) return 5;
	if (GetCurMap()) toMapCfg = GetCurMap()->GetMapConfig();

	if (fromMapCfg && toMapCfg && fromMapCfg != toMapCfg)
	{
		SendDBLogData(log_type_entery_exit_map, LogEnteryExitMap(GetGUID(), fromMapCfg->Id, fromMapCfg->MapType, toMapCfg->Id, toMapCfg->MapType, std::string("进入地图 ") + std::string(toMapCfg->Name)));
	}
	return 0;
	SAFE_END_EX(0);
}

uint16_t Player::GetIdleBagCount()
{
	return GetRolePack()->GetIdleBagCount();
}

uint16_t Player::GetBagFirstFreeSite()
{
	return GetRolePack()->GetIdleBagSite();
}

int Player::AddItem(uint16_t nTemplateID, uint16_t nNum, uint8_t nBindRequire, uint8_t nSiteRange, const log_params& lp)
{
	return GetRolePack()->AddItem(nTemplateID, nNum, static_cast<bind_type>(nBindRequire),
        static_cast<site_range>(nSiteRange), lp);
}

uint32_t Player::GetItemNum(uint16_t templateID, uint8_t bindRequire, uint8_t nSiteRange)
{
    auto rolePack = GetRolePack();
    if (!rolePack) return ERR_MAIL_NO_PLAYER;

	return rolePack->GetItemNum(templateID, bindRequire, static_cast<site_range>(nSiteRange));
}

uint32_t Player::GetItemNumByKeyName(const std::string &keyName, uint8_t bindRequire, uint8_t nSiteRange)
{
    const auto *itemCfg = sItemConfig.Get(keyName);
    if (!itemCfg) return 0;

    return GetItemNum(itemCfg->Id, bindRequire, nSiteRange);
}

int Player::AddItemByKeyName(const std::string& sKeyName, uint16_t nNum, uint8_t bBind, uint8_t nJob, const log_params& lp)
{
	return GetRolePack()->AddItemByKeyName(sKeyName, nNum, bBind, nJob, site_nullptr, site_range_bag, lp);
}

int Player::AddItemByKeyNameToSite(const std::string& sKeyName, uint16_t nNum, uint8_t bBind, uint8_t nJob, uint16_t nSite, const log_params& lp)
{
	return GetRolePack()->AddItemByKeyName(sKeyName, nNum, bBind, nJob, nSite, site_range_bag, lp);
}

uint64_t Player::AddSingleItem(uint16_t nTemplateID, uint16_t nNum, uint8_t nBindRequire, const log_params& lp)
{
	return GetRolePack()->AddSingleItem(nTemplateID, nNum, (bind_type)nBindRequire, lp);
}

int Player::AddItems(const CLuaObject& luaObj, const log_params& lp)
{
	return GetRolePack()->AddItems(luaObj, site_range_bag, lp);
}

const std::string & Player::GetGuildName()
{
	return  GetGuildDataMgr().GetGuildName();
}

int Player::RemoveItem(uint16_t nTemplateID, uint16_t nNum, uint8_t bindRequire, uint8_t nSiteRange, const log_params& lp)
{
    auto rolePack = GetRolePack();
    if (!rolePack) return ERR_ITEM_DESTROY;
	return rolePack->RemoveItem(nTemplateID, nNum, bindRequire, (site_range)nSiteRange, lp);
}

int Player::RemoveItem(uint64_t itemGuid, uint16_t nNum, const log_params& lp)
{
    auto rolePack = GetRolePack();
    if (!rolePack) return ERR_ITEM_DESTROY;
    return rolePack->RemoveItem(itemGuid, nNum, lp);
}

int Player::RemoveItem(const std::string& itemKeyName, uint16_t nNum, uint8_t bindRequire, uint8_t nSiteRange, const log_params& lp)
{
    auto pItemCfg = sItemConfig.Get(itemKeyName);
    if (!pItemCfg) return ERR_ITEM_DESTROY;

    return RemoveItem(pItemCfg->Id, nNum, bindRequire, (site_range)nSiteRange, lp);
}


void Player::SendSyncQuestReqToCS()
{
    auto *pRoleTask = GetRoleTask();
    if (!pRoleTask) return;

    ProtoMS_SyncQuestReq syncQuestReq;

    syncQuestReq.playerid = GetUserID();
    syncQuestReq.roleid = GetGUID();
    syncQuestReq.quest_info = pRoleTask->GetQuestInfo();
    syncQuestReq.quest_achev_num = _countof(syncQuestReq.quest_achevs);
    pRoleTask->GetQuestAchieves(syncQuestReq.quest_achevs, syncQuestReq.quest_achev_num);

    SendDataBySessionType(SESSION_TYPE_MS2CS, syncQuestReq);
}

void Player::SendRoleAttrExtRefNtfToGS(uint16_t nAttrID, int64_t nDelta)
{
    ProtoMS_RoleAttrExtRefNtf roleAttrExtRefNtf;
    roleAttrExtRefNtf.sessionid = GetClSessionID();
    roleAttrExtRefNtf.attr_name = nAttrID;
    roleAttrExtRefNtf.attr_value = nDelta;

    SendDataBySessionID(GetGsSessionID(), roleAttrExtRefNtf);
}

void Player::OnAddItem(uint16_t nSite)
{
    auto *pRolePack = GetRolePack();
    if (!pRolePack) return;

    if (pRolePack->IsInSiteRange(nSite, site_range_bag)) {

        const auto *pItem = pRolePack->GetItem(nSite);
        if (!pItem) return;

		mQuestDataMgr.AddToQuestAchieve(quest_achev_collect_item, pItem->GetTemplateID(), pItem->GetAmount());
    }
}

void Player::OnRemoveItem(uint16_t nSite)
{
    auto *pRolePack = GetRolePack();
    if (!pRolePack) return;

    if (pRolePack->IsInSiteRange(nSite, site_range_bag)) {

        const auto *pItem = pRolePack->GetItem(nSite);
        if (!pItem) return;

		mQuestDataMgr.AddToQuestAchieve(quest_achev_collect_item, pItem->GetTemplateID(), -pItem->GetAmount());
    }
}

void Player::OnUpdateItem(uint16_t nSite, int nNum)
{
    auto *pRolePack = GetRolePack();
    if (!pRolePack) return;

    if (pRolePack->IsInSiteRange(nSite, site_range_bag)) {

        const auto *pItem = pRolePack->GetItem(nSite);
        if (!pItem) return;

		mQuestDataMgr.AddToQuestAchieve(quest_achev_collect_item, pItem->GetTemplateID(), nNum);
    }
}

void Player::OnSwapItem(uint16_t nSite1, uint16_t nSite2)
{
    auto *pRolePack = GetRolePack();
    if (!pRolePack) return;

    const auto *pItem1 = pRolePack->GetItem(nSite1);
    const auto *pItem2 = pRolePack->GetItem(nSite2);

    if (pRolePack->IsInSiteRange(nSite1, site_range_bag)) {

        if (pItem2) {
			mQuestDataMgr.AddToQuestAchieve(quest_achev_collect_item, pItem2->GetTemplateID(), -pItem2->GetAmount());
        }

        if (pItem1) {
			mQuestDataMgr.AddToQuestAchieve(quest_achev_collect_item, pItem1->GetTemplateID(), pItem1->GetAmount());
        }
    }

    if (pRolePack->IsInSiteRange(nSite2, site_range_bag)) {

        if (pItem1) {
			mQuestDataMgr.AddToQuestAchieve(quest_achev_collect_item, pItem1->GetTemplateID(), -pItem1->GetAmount());
        }

        if (pItem2) {
			mQuestDataMgr.AddToQuestAchieve(quest_achev_collect_item, pItem2->GetTemplateID(), pItem2->GetAmount());
        }
    }
}

void Player::OnItemAppear(SceneItem *item)
{
}

void Player::OnItemDisappear(SceneItem *item)
{
}

void Player::OnUseEquip(uint16_t site)
{
	mNeedCalculateAttribute = true;
    NotifyAroundPlayers_RefreshEquip();
}

void Player::OnUnloadEquip(uint16_t site)
{
	mNeedCalculateAttribute = true;
    NotifyAroundPlayers_RefreshEquip();
}

void Player::NotifyAroundPlayers_RefreshEquip()
{
    auto *map = GetCurMap();
    if (!map) return;

    auto x = GetRolePosX();
    auto y = GetRolePosY();

    map->ApplyFuncToAllRolesInAroundRegions(x, y, [this](Role *role){ SendRoleAppNtf(role); });
}

void Player::SendRoleAppNtf(Role *toRole)
{
    if (!toRole || (!toRole->IsPlayer() && !toRole->IsStallDummy())) return;

    auto *player = static_cast<Player *>(toRole);
	if (!player) return;

    auto *pack = GetRolePack();
    if (!pack) return;

    auto &msg = gProtoMS_RoleAppNtf;
    msg.Reset();
    msg.sessionid = player->GetClSessionID();
    msg.player_guid = GetGUID();
    msg.hair = mRoleBriefInfo.hair;
    msg.hair_color = mRoleBriefInfo.hair_color;
    msg.body = pack->GetItemID(site_armor);
    msg.weapon = pack->GetItemID(site_weapon);
    msg.wings = pack->GetItemID(site_wings);
    msg.mount = pack->GetItemID(site_mount);
    msg.amulet = pack->GetItemID(site_amulet);
    msg.is_first = 1;

	std::pair<item_site, item_site> ext[] = {
		{site_weapon, site_equip_end},
		{site_glasses, site_equip_reserved_end},
		{site_equip_custom_0, site_equip_custom_end},
		{site_fashion_helmet, site_fashion_end},
	};

    auto &i = msg.equip_num;

    bool needSend = true;
	for (const auto& siteRang : ext) {
	    for (uint16_t site = siteRang.first; site < siteRang.second; ++site ) {

            auto id = pack->GetItemID(site);
            if (id == 0) continue;

            auto &equip = msg.equips[i];
            equip.site = site;
            equip.id = id;

            needSend = true;

            if (++i == _countof(msg.equips))
            {
                SendDataBySessionID(player->GetGsSessionID(), msg);
                i = 0;
                needSend = false;
                msg.is_first = 0;
            }
        }
	}
    if (needSend) SendDataBySessionID(player->GetGsSessionID(), msg);

    mRoleBriefInfo.weapon = msg.weapon;
    mRoleBriefInfo.clothes = msg.body;
}

bool Player::JumpMapByTarMap(Map* tarMap, uint16_t x, uint16_t y, uint16_t type)
{
	if (!tarMap)return false;
	if (!tarMap->FindJumpablePos(x, y)) return false;

	// 跳转地图停止移动状态
	auto rolemove = GetRoleMove();
	if (rolemove)
	{
		rolemove->StopMove(false);
	}

	std::string fromMapGuid = "", toMapGuid = "";
	if (tarMap == GetCurMap()) {

		DropItemByDropProcess(player_drop_type_jump_map);
		fromMapGuid = toMapGuid = GetCurMap()->GetGUIDAsString();
		auto roleAttr = GetRoleAttr();
		if (roleAttr) roleAttr->SetMoveType(move_type_jump);
		SetRolePos(x, y);
		auto rolemove = GetRoleMove();
		if (roleAttr->GetMoveType() == move_type_jump) roleAttr->SetMoveType(move_type_walk);

		TRIGGER_EVENT(trigger_post_enter_jump, GetGUIDAsString(), fromMapGuid, toMapGuid, x, y, type);
		return true;
	}

	DATA::Map* fromMapCfg = nullptr;
	DATA::Map* toMapCfg = nullptr;
	if (GetCurMap())
	{
		fromMapCfg = GetCurMap()->GetMapConfig();
		fromMapGuid = GetCurMap()->GetGUIDAsString();
	}
	if (!LeaveCurMap(false)) return false;

	bool ret = EnterMap(tarMap, x, y);
	if (GetCurMap())
	{
		toMapCfg = GetCurMap()->GetMapConfig();
		toMapGuid = GetCurMap()->GetGUIDAsString();
	}

	if (fromMapCfg && toMapCfg && fromMapCfg != toMapCfg)
	{
		SendDBLogData(log_type_entery_exit_map, LogEnteryExitMap(GetGUID(), fromMapCfg->Id, fromMapCfg->MapType, toMapCfg->Id, toMapCfg->MapType, std::string("进入地图 ") + std::string(toMapCfg->Name)));
	}
	TRIGGER_EVENT(trigger_post_enter_jump, GetGUIDAsString(), fromMapGuid, toMapGuid, x, y, type);
	return ret;
}

bool Player::JumpMap(const std::string& mapName, uint16_t posX, uint16_t posY, uint16_t type)
{
	auto state = GetRoleState();
	if (!state || !state->CheckAlive())
	{
		LOG_ERROR("Cur Player State Is Die Can't Jump Map:%s", mapName.c_str());
		return false;
	}
    auto mapCfg = sMapConfig.Get(mapName);
    if (nullptr == mapCfg) {
        LOG_ERROR("map config not exist. mapName:%s", mapName.c_str());
        return false;
    }

    Map* tarMap = MapMgr::GetInstance()->FindMap(mapName);
    if (nullptr == tarMap) {
        LOG_ERROR("tar map instance not exist. mapName:%s", mapName.c_str());
        return false;
    }

	return JumpMapByTarMap(tarMap, posX, posY, type);
}

bool Player::JumpMap(Map* tarMap, uint16_t x, uint16_t y)
{
	return JumpMapByTarMap(tarMap, x, y, (uint16_t)jump_map_type::default_type_null);
}

void Player::SendLevelUpNtfToAroundPlayers()
{
    ProtoMS_LevelUpNtf ntf;
    ntf.player_guid = GetGUID();
    ntf.level = GetRoleProp(role_level);

    auto f = [&](Player *player){
        ntf.sessionid = player->GetClSessionID();
        SendDataBySessionID(player->GetGsSessionID(), ntf);
        player->RunClientScript("脚本表单", "PlayerHeaderInfo.LevelUp_Msg_Close()", false);
    };

    ApplyFuncToAroundPlayers(f);
}

void Player::TalkToNpc(Role *npc, std::string dialog)
{
    if (!npc || !npc->IsNpc()) return;
    if (trim(dialog).empty()) return;

	MSG_BUFFER_DATA(ProtoMS_QuestNpcTalkAck, ack);
    ack.clientSessionID = GetClSessionID();
    ack.npc_guid = npc->GetGUID();
    ack.talk_len = dialog.length();
    strcpy_s(ack.talk, _countof(ack.talk), dialog.c_str());

    SendDataBySessionID(GetGsSessionID(), ack);
}

void Player::SendRelationChatNtf(const MESSAGE_INFO& info)
{
	MSG_BUFFER_DATA(ProtoGS_RelationChatNtf, data);
	if (info.comp){
		memcpy(data.info.chat_message.message, info.message, _countof(info.message));
	}
	else{
		strcpy_s(data.info.chat_message.message, _countof(data.info.chat_message.message), info.message);
		data.info.size = _countof(data.info.chat_message.message);
	}
	data.info.type = info.type;
	data.info.comp = info.comp;
    sprintf_s(data.info.chat_message.role_name, _countof(data.info.chat_message.role_name), "%s:%u:%u:%u:%u",         // 名称:等级:VIP等级:性别:职业
        mRoleBriefInfo.name, mRoleBriefInfo.level, mRoleBriefInfo.vipLevel, mRoleBriefInfo.gender, mRoleBriefInfo.job);
	strcpy_s(data.info.font_color, _countof(data.info.font_color), info.font_color);
	strcpy_s(data.info.background_color, _countof(data.info.background_color), info.background_color);
	data.info.scroll_times = info.scroll_times;


    auto applyFunc = [&](Role *pRole) {

        if (!pRole->IsPlayer()) return;
        //if (pRole == this) return;

        auto pOtherPlayer = static_cast<Player *>(pRole);
        data.sessionid = pOtherPlayer->GetClSessionID();

        SendDataBySessionID(pOtherPlayer->GetGsSessionID(), data);       // 给其他人回NTF
    };

    auto x = GetRolePosX();
    auto y = GetRolePosY();
    auto pMap = GetCurMap();
	if (!pMap)return;

    switch (info.type) {      // 1：当前 2：队伍 3：公会 4：世界 9: 阵营 12：全服

    case relation_chat_ntf_type_current:
        pMap->ApplyFuncToAllPlayersInAroundRegions(x, y, applyFunc);
        break;

    case relation_chat_ntf_type_team:
	{
		auto teamguid = mTeamDataMgr.GetTeamGuid();
		if (teamguid.empty())return;
		auto team_info = TeamMgr::GetInstance()->FindTeam(std::stoull(teamguid));
		if (!team_info)return;
		for (auto& i : team_info->mMemberList)
		{
			auto role = MapRoleMgr::GetInstance()->FindRole(i.guid);
			if (!role || !role->IsPlayer())continue;
			applyFunc(role);
		}
		break;
	}
    case relation_chat_ntf_type_guild:
    {
		auto mGuild = GetGuildDataMgr().GetGuild();
        if (!mGuild) break;
        auto *members = GuildMgr::GetInstance()->GetMemberList(mGuild->id);
        if (!members) break;

        for (auto &member : *members) {
            auto *player = MapRoleMgr::GetInstance()->FindPlayer(member->player_id);
            if (!player) continue;
            data.sessionid = player->GetClSessionID();
            SendDataBySessionID(player->GetGsSessionID(), data);
        }
    }
        break;

    case relation_chat_ntf_type_world:
		pMap->ApplyFuncToAllRoles(applyFunc);

        break;
	case relation_chat_ntf_type_trumpt:
		MapMgr::GetInstance()->ApplyFuncToAllMap(applyFunc);
		break;
    case relation_chat_ntf_type_camp:
        break;

    case relation_chat_ntf_type_whole:
		MapMgr::GetInstance()->ApplyFuncToAllMap(applyFunc);
        break;
    }
}

bool Player::SetAutoPickItemRadius(uint8_t radius)
{
	const auto &maxDis = sGlobalConfig.GetData()->AutoPickupMaxDistance;
	if (radius > maxDis) return false;

	auto &roleSettings = GetRoleSettings();
	auto &autoPickupSettings = roleSettings.auto_pickup;

	if (radius == 0)
		autoPickupSettings.mode = static_cast<uint8_t>(auto_pick_item_mode_undef);
	else
		autoPickupSettings.mode = static_cast<uint8_t>(auto_pick_item_mode_around);

	autoPickupSettings.radius = radius;
	autoPickupSettings.numpos = 0;
    SendAutoPickupSettingsNtfToGS();
	return true;
}

bool Player::SetAutoPickItemRelativePositions(std::vector<Point> relpos)
{
	if (relpos.size() > AUTO_PICKUP_MAXPOS) return false;

	const auto &maxDis = sGlobalConfig.GetData()->AutoPickupMaxDistance;
	for (const auto &pos : relpos) {
		if (abs(pos.x) > maxDis) return false;
		if (abs(pos.y) > maxDis) return false;
	}

	auto &roleSettings = GetRoleSettings();
	auto &autoPickupSettings = roleSettings.auto_pickup;
	autoPickupSettings.numpos = static_cast<uint8_t>(relpos.size());

	if (autoPickupSettings.numpos == 0)
		autoPickupSettings.mode = static_cast<uint8_t>(auto_pick_item_mode_undef);
	else
		autoPickupSettings.mode = static_cast<uint8_t>(auto_pick_item_mode_designated);

	for (uint8_t i = 0; i < autoPickupSettings.numpos; ++i) {
		autoPickupSettings.relpos[i].x = relpos[i].x;
		autoPickupSettings.relpos[i].y = relpos[i].y;
	}

    SendAutoPickupSettingsNtfToGS();
	return true;
}

bool Player::SetAutoPickItemInterval(uint16_t interval)
{
    if (interval < AUTO_PICKUP_MININTVL || interval > AUTO_PICKUP_MAXINTVL)
        return false;

    auto &roleSettings = GetRoleSettings();
    auto &autoPickupSettings = roleSettings.auto_pickup;

    autoPickupSettings.interval = interval;
    SendAutoPickupSettingsNtfToGS();
    return true;
}

void Player::SetCustVars(CUST_VAR_MAP vars)
{
    mCustVars = std::move(vars);
    mCustVarMody = true;
	CustVarMgr::GetInstance()->CheckExpired_CS(mCustVars);
    CheckCustVarNeedUpdate();
}

void Player::SetCustVar(std::string name, std::string value, const uint8_t &type)
{
    CustVarMgr::GetInstance()->SetValue(mCustVars, GetGUID(), name, value, type);
	CustVarMgr::GetInstance()->SetValue(mTempCustVars, GetGUID(), name, value, type);
	if (std::string(CUST_VAR_STALL_NAME_KEY) == name && mStallDummy)
	{
		mStallDummy->ChangeStallName(value, type);
	}
	mTempCustVarMody = true;
    CheckCustVarNeedUpdate();

	TRIGGER_EVENT(this, trigger_post_set_customer_var, GetGUIDAsString(), name, value, type);
}

const std::string & Player::GetCustVar(const std::string &name)
{
    return CustVarMgr::GetInstance()->GetValue(mCustVars, name);
}

void Player::SendSyncPlayerCustVarToCS()
{
	CustVarMgr::GetInstance()->CheckExpired(mCustVars);

    ProtoMS_SyncPlayerCustVar data;

    data.playerid = GetUserID();
    data.roleid = GetGUID();
    data.vars = &mCustVars;

    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void Player::SetItemCustVars(CUST_VAR_SP_LIST vars)
{
    auto *pack = GetRolePack();
    if (!pack) return;

	pack->OnRecvItemCustVarList(vars);
}

void Player::SetItemDynAttrsList(ITEM_DYN_ATTRS_LIST attrsList)
{
    auto *rolePack = GetRolePack();
    if (!rolePack) return;

	rolePack->OnRecvItemDynAttrsList(attrsList);
}

void Player::SetRoleDynAttrsList(ROLE_DYN_ATTRS_LIST attrsList)
{
	auto* roleAttr = GetRoleAttr();
	if (!roleAttr) return;

	auto guid = GetGUID();
	auto iter = std::find_if(attrsList.begin(), attrsList.end(), [guid](ROLE_DYN_ATTRS& attrs) {
		return attrs.guid == guid;
	});
	if (iter == attrsList.end()) return;
	roleAttr->OnRecvRoleDynAttrsList(*iter);
}

void Player::SendSyncPlayerItemCustVarToCS()
{
    auto *pack = GetRolePack();
    if (!pack) return;

    CUST_VAR_SP_LIST vars;

    auto curTime = time(nullptr);

    for (uint16_t i = 0; i < site_end; ++i) {

        auto *item = pack->GetItem(i);
        if (!item) continue;

        auto &itemVars = item->GetCustVars();
		CustVarMgr::GetInstance()->CheckExpiredAndCollect(itemVars, vars);
    }

    ProtoMS_SyncPlayerItemCustVar data;
    data.playerid = GetUserID();
    data.roleid = GetGUID();
    data.vars = &vars;

    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

bool Player::SendSaveGoodsIssueRecordToCS(const GOODS_ISSUE_RECORD &record, bool sendByGM)
{
    ProtoMS_SaveGoodsIssueRecord data;
    data.player_guid = sendByGM ? 0 : GetUserID();
    data.role_guid = sendByGM ? 0 : GetGUID();
    data.record = record;
    if (!SendDataBySessionType(SESSION_TYPE_MS2CS, data)) {
        LOG_ERROR("SendSaveGoodsIssueRecordToCS failed. "
            "order_no: %s, role_guid: %llu, pay_type: %u, goods_id: %u, goods_num: %u, pay_amount: %u, issued: %u, isPost: %u",
            record.order_no, record.role_guid, record.pay_type, record.goods_id, record.goods_num, record.pay_amount,
            record.issued, record.isPost);
        return false;
    }
    return true;
}

void Player::SendGoodsPostRecordToClient(GOODS_ISSUE_RECORD& record)
{
	ProtoMS_SendGoodsPostRecordToClient data;
	data.record = record;
	data.sessionID = this->GetClSessionID();
	SendDataBySessionID(this->GetGsSessionID(), data);
}

void Player::SendGoodsIssuedNtfToCS(const std::vector<std::string> &orderNoList)
{
    if (orderNoList.empty()) return;
    ProtoMS_GoodsIssuedNtf data;
    data.player_guid = GetUserID();
    data.role_guid = GetGUID();
    data.num = std::min<uint8_t>(_countof(data.order_no), orderNoList.size());
    for (uint8_t i = 0; i < data.num; ++i) {
        strcpy_s(data.order_no[i], orderNoList[i].c_str());
    }
    SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void Player::SendGoodsIssuedPostToCS(const std::vector<std::string>& PostList)
{
	if (PostList.empty()) return;
	ProtoMS_SyncGoodsPostRecord data;
	data.player_guid = GetUserID();
	data.role_guid = GetGUID();
	data.num = std::min<uint8_t>(_countof(data.order_no), PostList.size());
	for (uint8_t i = 0; i < data.num; ++i) {
		strcpy_s(data.order_no[i], PostList[i].c_str());
	}
	SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void Player::SendActivationCodeToCS(uint16_t type, const std::string& code)
{
	ProtoMS_PlayerActivationCode data;
	data.info.userid = GetUserID();
	data.info.type = type;
	data.info.guid = GetGUID();
	strcpy_s(data.info.code, _countof(data.info.code), code.c_str());
	strcpy_s(data.info.name, _countof(data.info.name), GetName().c_str());
	SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void Player::SendRebateMoneyUsedNtfToCS()
{
	ProtoMS_RebateMoneyUsedNtf data;
	data.role_guid = GetGUID();
	data.record = mRebateMoneyRecord;

	SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

void Player::SendAutoPickupSettingsNtfToGS()
{
    ProtoMS_AutoPickupSettingsNtf data;
    data.clsessid = GetClSessionID();
    data.auto_pickup = GetRoleSettings().auto_pickup;
    SendDataBySessionID(GetGsSessionID(), data);
}

void Player::QueryPlayerInfo(const std::string &name)
{
    auto *player = MapRoleMgr::GetInstance()->GetPlayerByName(name);
    QueryPlayerInfo(player);
}

void Player::QueryPlayerInfo(const uint64_t &guid)
{
    auto *role = MapRoleMgr::GetInstance()->FindRole(guid);
    if (!role) return;
    if (role->IsPlayer())
        QueryPlayerInfo(static_cast<Player *>(role));
    else if (role->IsPlayerDoplganr())
        QueryPlayerDoplganrInfo(static_cast<PlayerDoplganr *>(role));
}

void Player::QueryPlayerInfo(Player *player)
{
    if (!player) return;

    static auto data = std::make_unique<ProtoMS_PlayerQueryNtf>();     // 结构体太大只能new，否则栈溢出
    data->Reset();
    data->sessionid = GetClSessionID();
    data->player_guid = player->GetGUID();
    strcpy_s(data->name, _countof(data->name), player->GetName().c_str());
    data->gender = static_cast<uint8_t>(player->GetRoleProp(role_gender));
    data->job = static_cast<uint8_t>(player->GetRoleProp(role_job));
    data->level = player->GetRoleProp(role_level);
    strcpy_s(data->family_name, _countof(data->family_name), player->GetGuildName().c_str());
    strcpy_s(data->family_title, _countof(data->family_title), GuildMgr::GetInstance()->GetMemberTitle(player->GetGuildDataMgr().GetGuildMemberTitle()));

    auto items = player->GetAllEquipments();

    int i = 0;
    auto n = items.size();

    auto &itemNum = data->item_num;
    auto &finalPack = data->isFinalPack;
    bool send = false;

    while (true) {

        if (i == n) finalPack = true;

        if (finalPack || itemNum == ProtoMS_PlayerQueryNtf::max_item_info_num)
            send = true;

        if (send && !finalPack) {
            auto t = i;
            while (t < n && !items[t++]);
            if (t == n) finalPack = true;
        }

        if (send) {
            SendDataBySessionID(GetGsSessionID(), *data);
            memset(data->item_info, 0, sizeof(data->item_info));
            itemNum = 0;
            send = false;
        }

        if (finalPack) break;

        auto &item = items[i++];
        if (!item) continue;

        item->GenerateItemInfo(data->item_info[itemNum++]);
    }
}

void Player::QueryPlayerDoplganrInfo(PlayerDoplganr *doplganr)
{
    if (!doplganr) return;

    static auto data = std::make_unique<ProtoMS_PlayerQueryNtf>();     // 结构体太大只能new，否则栈溢出
    data->Reset();
    data->sessionid = GetClSessionID();
    data->player_guid = doplganr->GetGUID();
    strcpy_s(data->name, doplganr->GetName());
    data->gender = static_cast<uint8_t>(doplganr->GetRoleProp(role_gender));
    data->job = static_cast<uint8_t>(doplganr->GetRoleProp(role_job));
    data->level = doplganr->GetRoleProp(role_level);

    auto items = doplganr->GetAllEquipments();

    int i = 0;
    auto n = items.size();

    auto &itemNum = data->item_num;
    auto &finalPack = data->isFinalPack;
    bool send = false;

    while (true) {

        if (i == n) finalPack = true;

        if (finalPack || itemNum == ProtoMS_PlayerQueryNtf::max_item_info_num)
            send = true;

        if (send && !finalPack) {
            auto t = i;
            while (t < n && !items[t++]);
            if (t == n) finalPack = true;
        }

        if (send) {
            SendDataBySessionID(GetGsSessionID(), *data);
            memset(data->item_info, 0, sizeof(data->item_info));
            itemNum = 0;
            send = false;
        }

        if (finalPack) break;

        auto &item = items[i++];
        if (!item) continue;

        item->GenerateItemInfo(data->item_info[itemNum++]);
    }
}

void Player::SetQuickBarSetVec(const ProtoGS_QuickBarSet &msg)
{
	QUICK_BAR_INFO val;
	val.guid = msg.guid;
	val.id = msg.id;
	val.slot = msg.slot;
	val.type = msg.type;

	for (auto pos = BarVector.begin(); pos != BarVector.end(); pos++)
	{
		if (pos->slot == val.slot)
		{
			pos->guid = val.guid;
			pos->id = val.id;
			pos->type = val.type;
			pos->slot = val.slot;
			return;
		}
	}
	BarVector.push_back(val);
}

bool Player::SetGoldChangeAttr(int64_t gold, const log_params& lp)
{
	if ((mRoleExtraInfo.gold -= gold) < 0) return false;
	if ((mRoleExtraInfo.depositGold += gold) < 0)return false;
	SetRoleProp64(role_gold,mRoleExtraInfo.gold, lp);
	SetRoleProp64(role_gold_deposit, mRoleExtraInfo.depositGold, lp);
	return true;
};

void Player::RunGMCommand(void* pData)
{
	auto msg = (ProtoCS_RunGmCmdAck*)pData;
	if (msg->result != ERR_OK && msg->result != ERR_EXEGMCMDFAIL)	{
		if (msg->result == ERR_EXEGMCMDFAIL)return;
		SendGMErrorAck(msg->sn, msg->result);
		return;
	}

	// 角色名不对 或者用户名不对
	if (strcmp(GetName().c_str(), msg->playername))
	{
		LOG_WARN("[GM] player isn't GM");
		return;
	}

	string param = msg->param;
	if (CSV_HELPER::CsvUtils::StrIsUTF8(param)) {
		param = utf8_to_gbk(msg->param);
	}

    GMCmdHandler::HandleCmd(this, msg->cmd, param.c_str(), msg->sn);
}

void Player::SetMultDgnMapID(const std::string& mapName, uint64_t multDgnMapID)
{
	if (mapName.empty()) return;

	if (0 != multDgnMapID)
	{
		mMultDgnMapID[mapName] = multDgnMapID;
	}
	else
	{
		mMultDgnMapID.erase(mapName);
	}
}

uint64_t Player::GetMultDgnMapID(const std::string& mapName)
{
	if (mapName.empty()) return 0;
	auto iter = mMultDgnMapID.find(mapName);
	return iter != mMultDgnMapID.end() ? iter->second : 0;
}

const std::string & Player::GetMultDgnMapName(uint64_t multDgnMapID)
{
	auto iter = std::find_if(mMultDgnMapID.begin(), mMultDgnMapID.end(),
		[&](const std::pair<std::string, uint64_t>& iter)
		{
			return iter.second == multDgnMapID;
		});
	return iter != mMultDgnMapID.end() ? iter->first : EMPTYSTR;
}

bool Player::IsGM()
{
    return (GetName() == "杜清远");
}

bool Player::SetGender(uint8_t Gender)
{
	if (Gender == mRoleBriefInfo.gender)return false;
	mRoleBriefInfo.gender = Gender;

	auto map = GetCurMap();
	if (!map)return false;
	map->NotifyRoleAppearNtfChange(this);

	ProtoMS_SetPlayerGender data;
	data.userID = GetUserID();
	data.guid = GetGUID();
	data.gender = Gender;
	SendDataBySessionType(SESSION_TYPE_MS2CS, data);
	return true;
}

void Player::SendSpellAck(uint64_t role_guid, int32_t ecode, uint16_t skillID, uint16_t clientSN)
{
    ProtoGS_SpellAck data;
    data.sessionid = GetClSessionID();
    data.role_guid = role_guid;
    data.id = skillID;
    data.ecode = ecode;
    data.idx = clientSN;

    SendDataBySessionID(GetGsSessionID(), data);

    LOG_TRACE("[SpellAck] role_guid: %llu, ecode: %d, skillID: %u, clientSN: %u",
        role_guid, ecode, skillID, clientSN);
}

bool Player::IsInSameTeam(Role *role)
{
    if (!role) return false;

    if (role->IsPlayer()) {
        auto *myTeam = this->GetRoleTeam();
        auto *roleTeam = role->GetRoleTeam();
        if (!myTeam || !roleTeam) return false;
        return (myTeam->GetTeamGUID() != 0 &&
                myTeam->GetTeamGUID() == roleTeam->GetTeamGUID());
    }

    return role->IsInSameTeam(this);
}

bool Player::IsInSameGuild(Role *role)
{
    if (!role) return false;

    if (role->IsPlayer()) {
        auto myGuildID = this->GetGuildDataMgr().GetGuildID();
        auto roleGuildID = static_cast<Player *>(role)->GetGuildDataMgr().GetGuildID();
        return (myGuildID != 0 && myGuildID == roleGuildID);
    }

    return role->IsInSameGuild(this);
}

bool Player::IsInSameCamp(Role *role)
{
    if (!role) return false;

    if (role->IsPlayer()) {
        auto myCamp = GetRoleProp(role_camp);
        auto peerCamp = role->GetRoleProp(role_camp);
        return (myCamp != 0 && myCamp == peerCamp);
    }

    return role->IsInSameCamp(this);
}

bool Player::IsGrayName()
{
    return (GetRoleProp(role_is_gray) != 0);
}

bool Player::IsRedName()
{
    return (GetRoleProp(role_pk) > sGlobalConfig.GetData()->PKValueOfRedName);
}

bool Player::IsMyPet(Role *role)
{
    if (!role) return false;
    if (!role->IsPet()) return false;
    auto *pet = static_cast<Pet *>(role);
    return (pet->GetMasterGUID() == GetGUID());
}

bool Player::IsMyDoplganr(Role *role)
{
    if (!role) return false;
    if (!role->IsPlayerDoplganr()) return false;
    auto *doplganr = static_cast<PlayerDoplganr *>(role);
    return (doplganr->GetMasterGUID() == GetGUID());
}

bool Player::IsMyBiaoChe(Role *role)
{
    if (!role || !role->IsBiaoChe()) return false;
    auto *monster = static_cast<Monster *>(role);
    return (monster->GetMasterGUID() == GetGUID());
}

uint16_t Player::GetNearstNpcPosByName(uint16_t& x, uint16_t& y, const char* name)
{
	auto* map = GetCurMap();
	if (!map) return 0;
	auto role = map->GetNearestRoleByName(GetRolePosX(),GetRolePosY(), role_type_npc, name);
	if (!role)return 0;
	x = role->GetRolePosX();
	y = role->GetRolePosY();
	return 1;
}

void Player::CopyFromOwner()
{
	if (!mStallDummy) return;

	mStallDummy->mUserID = mUserID;
	mStallDummy->mRoleBriefInfo = mRoleBriefInfo;
	mStallDummy->mRoleBriefInfo.guid = mStallDummy->GetGUID();
	mStallDummy->mRoleExtraInfo = mRoleExtraInfo;
	mStallDummy->mCustVars = mCustVars;
	mStallDummy->SetName(mRoleBriefInfo.name);
}

void Player::GetTitleListReq()
{
	auto& titleList = GetTitleData();
	titleList.SendTitleListInfoToGS();
}

void Player::DropItemByDropProcess(uint16_t type, uint64_t killerGuid)
{
	auto* rolePack = GetRolePack();
	if (!rolePack)return;
	rolePack->DropItemByDropProcess(type, killerGuid);
}

void Player::ApplyFuncToAroundPlayers(std::function<void(Player*)> func, bool online)
{
    if (!func) return;

    auto *map = GetCurMap();
    if (!map) return;

    auto f = [&](Role *role) {
        if (!role || !role->IsPlayer()) return;
        auto *player = static_cast<Player *>(role);
        if (online && !player->IsOnline()) return;
        func(player);
    };

    auto x = GetRolePosX();
    auto y = GetRolePosY();

    map->ApplyFuncToAllPlayersInAroundRegions(x, y, f);
}

void Player::CheckCustVarNeedUpdate()
{
    if (mCustVarMody || mTempCustVarMody)
        SetNeedUpdateFlag(custvar_need_update_flag);
    else
        ResetNeedUpdateFlag(custvar_need_update_flag);
}

void Player::SendRoleAppearNtfToAroundPlayers(uint8_t appearType)
{
    ProtoMS_RoleAppearNtf data;
    data.role_guid = GetGUID();
    data.appear_type = appearType;

    auto f = [&](Player *player) {
        if (player == this) return;
        data.clsessid = player->GetClSessionID();
        SendDataBySessionID(player->GetGsSessionID(), data);
    };

    ApplyFuncToAroundPlayers(f);
}

uint8_t Player::GetRoleAppearType()
{
    if (GetDigMgr().IsDigging()) return role_appear_digging;
    return role_appear_normal;
}

void Player::BindStallDummy()
{
	mStallDummy = MapRoleMgr::GetInstance()->FindStallDummy(GetGUID(), 0);
	if (mStallDummy)
	{
		mStallDummy->mOwner = this;
		auto roleAttr = GetRoleAttr();
		if (roleAttr) roleAttr->SetRoleProp(role_stall, stall_state_ok);
	}
}

void Player::UnBindStallDummy()
{
	if (mStallDummy) mStallDummy->mOwner = nullptr;
}

void Player::TriggerCheckStall()
{
	// 未绑定
	if (!mStallBindTrade) return;
	if (mStallDummy) return;
	// 是否首次
	// 1.没有寄售物品
	if (!mSellDelegateInfo.empty()) return;
	// 2.没有摊位状态
	auto roleAttr = GetRoleAttr();
	if (!roleAttr) return;
	auto value = roleAttr->GetRoleProp(role_stall);
	if (value == stall_state_ok) return;
	// 是否在摆摊区域内
	auto map = GetCurMap();
	if (!map) return;
	uint16_t x = GetRolePosX();
	uint16_t y = GetRolePosY();
	if (!map->IsTypeRegion(x, y, region_stall)) return;
	// 当前位置只有当前玩家一人
	if (!map->GetMapGrid().IsOnlyDPForbid(x, y)) return;
	std::array<uint16_t, role_type_cnt> num{ 0 };
	map->GetMapAoi().IsHaveRoleInPoint(role_type_none, x, y, num);
	// 有其他玩家
	if (num.at(role_type_player) > 1) return;

	// 脚本其他处理
	bool canStall = true;
	TRIGGER_EVENT_RET<bool>(canStall, trigger_pre_stall, GetGUIDAsString());
	if (!canStall) return;

	// 设置摆摊
	mStallDummy = MapRoleMgr::GetInstance()->CreateStallDummy(this);
	if (!mStallDummy) return;

	mStallDummy->Role::OnEnterMap(map);
	roleAttr->SetRoleProp(role_stall, stall_state_ok);
	mStallDummy->CopyFromOwner();
	map->RoleEnter(mStallDummy);
}

SP_BUY_DELEGATE_LIST& Player::GetBuyDelegateInfo()
{
	if (IsStallDummy())
	{
		auto sdPlayer = static_cast<StallDummy*>(this);
		if (sdPlayer)
		{
			if (sdPlayer->mOwner) return sdPlayer->mOwner->GetBuyDelegateInfo();
			TradeMgr::GetInstance()->GetPlayerDelegateList(sdPlayer->mOwnerGuid, mBuyDelegateInfo);
		}
	}
	return mBuyDelegateInfo;
}
SP_SELL_DELEGATE_LIST& Player::GetSellDelegateInfo()
{
	if (IsStallDummy())
	{
		auto sdPlayer = static_cast<StallDummy*>(this);
		if (sdPlayer)
		{
			if (sdPlayer->mOwner) return sdPlayer->mOwner->GetSellDelegateInfo();
			TradeMgr::GetInstance()->GetPlayerDelegateList(sdPlayer->mOwnerGuid, mSellDelegateInfo);
		}
	}
	return mSellDelegateInfo;
}
SP_TRADE_RECORD_MAP& Player::GetTradeBuyRecords()
{
	if (IsStallDummy())
	{
		auto sdPlayer = static_cast<StallDummy*>(this);
		if (sdPlayer)
		{
			if (sdPlayer->mOwner) return sdPlayer->mOwner->GetTradeBuyRecords();
			TradeMgr::GetInstance()->GetPlayerBuyRecordsList(sdPlayer->mOwnerGuid, mTradeBuyRecords);
		}
	}
	return mTradeBuyRecords;
}
SP_TRADE_RECORD_MAP& Player::GetTradeSellRecords()
{
	if (IsStallDummy())
	{
		auto sdPlayer = static_cast<StallDummy*>(this);
		if (sdPlayer)
		{
			if (sdPlayer->mOwner) return sdPlayer->mOwner->GetTradeBuyRecords();
			TradeMgr::GetInstance()->GetPlayerSellRecordsList(sdPlayer->mOwnerGuid, mTradeSellRecords);
		}
	}
	return mTradeSellRecords;
}

CLuaObject Player::GetRebateMoneyInfo()
{
	auto luaObj = NewLuaObj();

	luaObj["RoleGuid"] = GetGUIDAsString();
	luaObj["BeExist"] = mRebateMoneyRecord.inc_id != 0;
	luaObj["BeUsed"] = mRebateMoneyRecord.is_use != 0;
	luaObj["Money"] = std::to_string(mRebateMoneyRecord.rebate_money);

	return luaObj;
}

void Player::GetRebateMoney()
{
	if (!mRebateMoneyRecord.inc_id) return;
	if (mRebateMoneyRecord.is_use) return;
	
	bool used = false;
	TRIGGER_EVENT_RET(used, this, trigger_rebate_money, GetGUIDAsString(), std::to_string(mRebateMoneyRecord.rebate_money));
	if (used)
	{
		mRebateMoneyRecord.is_use = 1;
		SendRebateMoneyUsedNtfToCS();
	}
	LOG_NORMAL("RebateMoney, playerGUID: %llu, inc_id: %llu, rebate_money: %llu, used: %d",
		GetGUID(), mRebateMoneyRecord.inc_id, mRebateMoneyRecord.rebate_money, mRebateMoneyRecord.is_use);
}
/////////////////////////////////////////////////////////////////////////////////////////////
StallDummy::StallDummy(Player* owner) : Player(role_type_stall_dummy), mOwner(owner)
{
	if (mOwner) mOwnerGuid = mOwner->GetGUID();

	SetScriptName("StallDummy");
}

void StallDummy::Init()
{
	// 只需要摆摊那一刻的外观,属性值先不考虑,节省内存暂时先RoleAttr和RolePack,
	mRoleAttr = new RoleAttr(this);
	mRolePack = new RolePack(this);
	Role::Init();
}

void StallDummy::Update(int32_t delta)
{
	Role::Update(delta);
}

void StallDummy::CopyFromOwner()
{
	if (!mOwner) return;

	mOwner->CopyFromOwner();
	if (mRolePack) mRolePack->CopyFromOwner(mOwner->mRolePack);
	if (mRoleAttr) mRoleAttr->CopyFromOwner(mOwner->mRoleAttr);
}

void StallDummy::TriggerCheckUnStall()
{
	if (CheckUnStall(GetSellDelegateInfo()) && mOwner)
	{
		mOwner->mStallDummy = nullptr;
		auto roleAttr = mOwner->GetRoleAttr();
		if (roleAttr) roleAttr->SetRoleProp(role_stall, stall_state_nullptr);
	}
}

bool StallDummy::CheckUnStall(const SP_SELL_DELEGATE_LIST& mSellDelegateInfo)
{
	if (mSellDelegateInfo.empty())
	{
		auto map = GetCurMap();
		if (map) map->RoleLeave(this);
		MapRoleMgr::GetInstance()->RemoveStallDummy(GetGUID());
		return true;
	}
	return false;
}

void Player::SetRebateMoneyNotUsedRecord(const REBATE_MONEY_RECORD& record)
{
	if (mRebateMoneyRecord.be_load) return;

	mRebateMoneyRecord = record;
}

void Player::SetGoodsNotIssuedRecords(const GOODS_ISSUE_RECORD *records, uint8_t num)
{
    if (!records) return;
    mGoodsNotIssuedRecords.clear();
    for (uint8_t i = 0; i < num; ++i) {
        mGoodsNotIssuedRecords.push_back(records[i]);
    }
}

void Player::SetGoodsNotPostRecords(const GOODS_ISSUE_RECORD* records, uint8_t num)
{
	if (!records) return;
	mGoodsNotPostRecords.clear();
	for (uint8_t i = 0; i < num; ++i) {
		mGoodsNotPostRecords.push_back(records[i]);
	}
}

void Player::SetNameInfo(const std::string& name)
{
	auto& briefInfo = GetRoleBriefInfo();
	ProtoGS_PlayerSetNameNtf ntf;
	ntf.guid = GetGUID();
	strcpy_s(ntf.name, _countof(ntf.name), name);
	strcpy_s(ntf.orgName, _countof(ntf.orgName), briefInfo.name);

	SetName(name);
	strcpy_s(briefInfo.name, _countof(briefInfo.name), name);

	mPetMgr.ChangeMasterNameInfo(name, ntf);
	mSummonMonsterMgr.ChangeMasterNameInfo(name, ntf);
	mGuildDataMgr.ChangeNameInfo(GetGUID(), name);
	AuctionHouse::GetInstance()->ChangeNameInfo(GetGUID(), name);
	TeamMgr::GetInstance()->ChangeMemberNameInfo(GetGUID(), name);
	for (auto i : mBuyDelegateInfo) {
		if (!i.get())continue;
		if (i.get()->buyer_guid == GetGUID()) {
			strcpy_s(i.get()->buyer, _countof(i.get()->buyer), name);
		}
	}
	for (auto i : mSellDelegateInfo) {
		if (!i.get())continue;
		if (i.get()->seller_guid == GetGUID()) {
			strcpy_s(i.get()->seller, _countof(i.get()->seller), name);
		}
	}

	// 广播
	auto map = GetCurMap();
	if (!map)return;
	map->SendPlayerChangeNameNtf(this, ntf);
}

void Player::HandleGoodsNotIssuedRecords()
{
    auto playerGUID = GetGUID();

    if (mGoodsNotIssuedRecords.empty()) return;

    LOG_NORMAL("IssueGoods, playerGUID: %llu, mGoodsNotIssuedRecords size: %u",
        playerGUID, mGoodsNotIssuedRecords.size());

    auto callback = [&, playerGUID](const TimerData &) {

        auto *player = MapRoleMgr::GetInstance()->FindPlayer(playerGUID);
        if (player != this || !IsOnline()) {
            LOG_NORMAL("IssueGoods, player is not online. playerGUID: %llu", playerGUID);
            return;
        }

        std::vector<std::string> orderNoList;

        for (auto &record : mGoodsNotIssuedRecords) {
            bool issued = false;
            TRIGGER_EVENT_RET(issued, this, trigger_issue_goods, GetGUIDAsString(), record.goods_id, record.goods_num);
            if (issued) orderNoList.push_back(record.order_no);
            LOG_NORMAL("IssueGoods, playerGUID: %llu, order_no: %s, goods_id: %u, goods_num: %u, issued: %d",
                playerGUID, record.order_no, record.goods_id, record.goods_num, issued);
        }
        SendGoodsIssuedNtfToCS(orderNoList);
        mGoodsNotIssuedRecords.clear();
    };

    auto delayTime = GetCurLoginNotifyDelayTime();
    ITimeHelper::GetInstance()->AddTimer(delayTime, false, callback);
    SetNextLoginNotifyDelayTime(delayTime + 2000);
}

void Player::HandleGoodsNotPostIssuedRecords()
{
	auto playerGUID = GetGUID();

	if (mGoodsNotPostRecords.empty()) return;

	auto* player = MapRoleMgr::GetInstance()->FindPlayer(playerGUID);
	if (player != this || !IsOnline()) {
		LOG_NORMAL("IssueGoodsPost, player is not online. playerGUID: %llu", playerGUID);
		return;
	}

	uint32_t delaytime = 0;
	uint16_t incrementTime = 1000;
	uint32_t clsession = GetClSessionID();
	uint32_t gssession = GetGsSessionID();

	for (auto& record : mGoodsNotPostRecords) {

		if (delaytime) {
			TimerData timer;
			timer.interval = delaytime;
			timer.loop = false;
			timer.callBack = [this, record, clsession, gssession](const TimerData&) {
				LOG_ERROR("Relogin Or Login Goods Post order:%s,time:%s", record.order_no, ITimeHelper::GetInstance()->GetCurTimeStrMS().c_str());
				ProtoMS_SendGoodsPostRecordToClient data;
				data.record = record;
				data.sessionID = clsession;
				SendDataBySessionID(gssession, data);
			};
			ITimeHelper::GetInstance()->AddTimer(timer);
		}
		else
		{
			LOG_ERROR("Relogin Or Login Goods Post order:%s,time:%s", record.order_no, ITimeHelper::GetInstance()->GetCurTimeStrMS().c_str());
			SendGoodsPostRecordToClient(record);
		}
		delaytime += incrementTime;
	}

}

void Player::HandleGoodsPostRecordAck(const char* order_no)
{
	if (mGoodsNotPostRecords.empty())return;
	for (auto record = mGoodsNotPostRecords.begin(); record != mGoodsNotPostRecords.end(); ++record) {
		if (strcmp(record->order_no, order_no) == 0) {
			std::vector<std::string>vec;
			vec.push_back(order_no);
			SendGoodsIssuedPostToCS(vec);
			mGoodsNotPostRecords.erase(record);
			break;
		}
	}
}

void StallDummy::ChangeStallName(std::string value,uint8_t type)
{
	SetCustVar(CUST_VAR_STALL_NAME_KEY, value, type);
	NotifyAroundPlayers_RoleInfoChange((uint16_t)RoleInfoChangeKey::rick_stall_name, value);
}
