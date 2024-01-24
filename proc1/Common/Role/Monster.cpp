#include "stdafx.h"
#include "Monster.h"
#include "RoleMove.h"
#include "Map.h"
#include "MapMgr.h"
#include "TeamMgr.h"
#include "BossInfo.h"

Monster::Monster() : Role(role_type_monster)
{
}

Monster::~Monster()
{
	if (mMonsterAI_ptr != nullptr)
	{
		delete mMonsterAI_ptr;
		mMonsterAI_ptr = nullptr;
	}
}

void Monster::Init(uint64_t guid, DATA::Monster* pConfig)
{
	if (nullptr == pConfig) {
		return;
	}

    if (pConfig->Type == monster_type_treasure) {
        mRoleAttr = new RoleAttr(this);
        mRoleState = new RoleState(this);
    }
    else {
        mRoleAttr = new RoleAttr(this);
        mRoleState = new RoleState(this);
        mRoleMove = new RoleMove(this);
        mRoleSkill = new RoleSkill(this);
        mRoleBuff = new RoleBuff(this);
    }

	Role::Init();
	SetGUID(guid);
    SetName(pConfig->Name);
	mMonsterTemplateID = pConfig->Id;
	SetScriptName(pConfig->Script);

    if (NeedMonsterAI(pConfig)) {
	    mMonsterAI_ptr = CreateMonsterAI(this,pConfig);//传入要生成的AI类型
    }

    if (mRoleState) mRoleState->SetState(role_state_battle_idle);

	if (pConfig->ExistTime) {
		SetExistTime(pConfig->ExistTime);
	}

	InitRoleProp(pConfig);
}

void Monster::Update(int delta)
{
	Role::Update(delta);
	if (mMonsterAI_ptr)
	{
		mMonsterAI_ptr->Update(delta);
	}
	mFightInfo.Update(delta);
	UpdateExclusiveRole(delta);
	UpdateAliveStateByOwner();          // 属于玩家的怪物始终更新ai，因此没必要单独设标志位

    // 暂时用不到
    //CheckAINeedUpdate(delta);
}

void Monster::OnRoleEnter(Role *role)
{
    CheckAINeedUpdate(role, true);
}

void Monster::OnRoleLeave(Role *role)
{
    CheckAINeedUpdate(role, false);
	if (GetGUID() != role->GetGUID())
	{
		DeleteMaxHateValue(role->GetGUID());
	}
}

void Monster::OnRoleExit(Role *role)
{
    Role::OnRoleExit(role);
    CheckAINeedUpdate(role, false);
	if (GetGUID() != role->GetGUID())
	{
		DeleteMaxHateValue(role->GetGUID());
	}
}

void Monster::CheckAINeedUpdate(Role *role, bool enter)
{
    if (!role || (!role->IsPlayer() && !role->IsPlayerDoplganr())) return;

    if (GetMasterGUID() != 0) return;   // 属于玩家的怪物总是更新ai

    auto *monsterAI = GetAIMonster();
    if (!monsterAI) return;

    if (enter) {                        // 有玩家进入
        mAroundPlayers.emplace(role->GetGUID());
        if (mAroundPlayers.size() == 1) {
            SetNeedUpdateFlag(ai_need_update_flag);
        }
    }
    else {                              // 有玩家离开
        mAroundPlayers.erase(role->GetGUID());
        if (mAroundPlayers.size() == 0) {
            ResetNeedUpdateFlag(ai_need_update_flag);
        }
    }
}

void Monster::CheckAINeedUpdate(int delta)
{
    const uint32_t CHECK_INTERVAL = 10000;
    const uint32_t MAX_DISTANCE = 30;

    mCheckAINeedUpdateTimeCounter += delta;
    if (mCheckAINeedUpdateTimeCounter < CHECK_INTERVAL) return;
    mCheckAINeedUpdateTimeCounter = 0;

    for (auto it = mAroundPlayers.begin(); it != mAroundPlayers.end(); ) {

        const auto &playerGUID = *it;

        auto *player = MapRoleMgr::GetInstance()->FindPlayer(playerGUID);
        if (!player) {
            it = mAroundPlayers.erase(it);
            continue;
        }

        if (DistanceFromRole(player) > MAX_DISTANCE) {
            it = mAroundPlayers.erase(it);
            continue;
        }

        ++it;
    }

    if (mAroundPlayers.empty())
        ResetNeedUpdateFlag(ai_need_update_flag);
    else
        SetNeedUpdateFlag(ai_need_update_flag);
}

bool Monster::TargetCanSelect(Role* tar)
{
	if (!tar || tar == this) return false;

    if (tar->IsNpc() || tar->IsStallDummy()) return false;
	if (tar->IsPlayer())
	{
		if (GetRoleAttr()->GetRoleProp(role_camp) &&
			(GetRoleAttr()->GetRoleProp(role_camp) == tar->GetRoleAttr()->GetRoleProp(role_camp)))return false;
		return true;
	}
	else if (tar->IsPet()) {
		auto pet = static_cast<Pet*>(tar);
		if (!pet)return false;
		auto belong = pet->GetMaster();
		if (!belong)return false;
		if (GetRoleAttr()->GetRoleProp(role_camp) &&
			(GetRoleAttr()->GetRoleProp(role_camp) == belong->GetRoleAttr()->GetRoleProp(role_camp)))return false;
		return true;
	}
	else if(tar->IsPlayerDoplganr())
	{
		auto doplganr = static_cast<PlayerDoplganr*>(tar);
		if (!doplganr)return false;
		auto belong = doplganr->GetMaster();
		if (!belong)return false;
		if (GetRoleAttr()->GetRoleProp(role_camp) &&
			(GetRoleAttr()->GetRoleProp(role_camp) == belong->GetRoleAttr()->GetRoleProp(role_camp)))return false;
		return true;
	}

	return false;
}

bool Monster::CheckTakeGrid(uint16_t x, uint16_t y)
{
    auto* map = GetCurMap();
    if (!map) return false;

    std::array<uint16_t, role_type_cnt> roleNumAry{ 0 };
    map->GetMapAoi().IsHaveRoleInPoint(role_type_none, x, y, roleNumAry);

    if (CheckCross()) {     // 可以穿怪
        for (int i = role_type_player; i < role_type_cnt; ++i) {
            if (i == role_type_monster) continue;
            if (roleNumAry.at(i) > 0) return false;
        }
    }
    else {
        for (const auto &roleNum : roleNumAry)
            if (roleNum > 0) return false;
    }

	auto gridIsForbid = map->GetMapGrid().IsForbid(x, y);
    return !gridIsForbid;
}

void Monster::SetScriptName(const std::string& scriptName)
{
	if (!scriptName.empty() && scriptName != "0") {
		Role::SetScriptName(scriptName);
	}
	else {
		Role::SetScriptName("Monster");
	}
}

Player * Monster::GetMaster()
{
	return MapRoleMgr::GetInstance()->FindPlayer(mMasterGUID);
}

void Monster::SetMonsterNameColor(std::string nameColor)
{
	mMonsterNameColor = nameColor;
	auto map = GetCurMap();
	if (nullptr == map)return;
	map->NotifyRoleAppearNtfChange(this);
}

void Monster::MakeMonsterAppearNtfData(ProtoMS_MonsterAppearNtf6& ntf)
{
    auto *cfg = GetConfig();
    if (!cfg) return;

	ntf.monster_guid = GetGUID();
	strcpy_s(ntf.monster_name, _countof(ntf.monster_name), GetName().c_str());
	ntf.template_id = mMonsterTemplateID;
	ntf.dst_x = GetRolePosX();
	ntf.dst_y = GetRolePosY();
	ntf.dir = GetRoleDir();
	ntf.cur_hp = GetRoleProp(role_hp);
	ntf.max_hp = GetRoleProp(role_max_hp);
	ntf.status = ntf.cur_hp ? 0 : 1;
	ntf.servant_lv = 1;
	ntf.move_speed = GetRoleProp(role_move_speed);
	ntf.buff_num = 0;
	memset(ntf.buffs, 0, sizeof(ntf.buffs));
	strcpy_s(ntf.master_name, _countof(ntf.master_name), m_sMasterName.c_str());
	ntf.appear_type = 0;
	ntf.seed = 0;
	ntf.attack_speed = GetRoleProp(role_attack_speed);
	ntf.custom.num = 0;
	memset(ntf.custom.buf, 0, sizeof(ntf.custom.buf));
	ntf.inner_force = 0;
	ntf.max_inner_force = 0;
	ntf.reserve_num = 0;
	memset(ntf.reserve_values, 0, sizeof(ntf.reserve_values));
	ntf.modelid = GetRoleProp(role_changed_modelid);
	strcpy_s(ntf.name_color, _countof(ntf.name_color), GetMonsterNameColor().c_str());
}

void Monster::OnRoleBeAttacked(uint64_t attackerGUID)
{
    auto *attacker = MapRoleMgr::GetInstance()->FindRole(attackerGUID);
    if (!attacker) return;

    Role *effectAttacker = nullptr;

    if (attacker->IsPlayer()) {
        effectAttacker = attacker;
    }
    if (attacker->IsPet()) {
        auto *pet = static_cast<Pet *>(attacker);
        effectAttacker = pet->GetMaster();
    }
    else if (attacker->IsPlayerDoplganr()) {
        auto *doplganr = static_cast<PlayerDoplganr *>(attacker);
        effectAttacker = doplganr->GetMaster();
    }

    if (!effectAttacker) return;
    auto effectAttackerGUID = effectAttacker->GetGUID();

    if (mExclusiveRole != 0) {
        if (mExclusiveRole == effectAttackerGUID) {
            mExpireTime = 0;        // 重新计时怪物死亡掉落归属
        }
        return;
    }

    auto *roleTeam = effectAttacker->GetRoleTeam();
	mExclusiveRoleTeam = roleTeam ? roleTeam->GetTeamGUID() : 0;
	mExclusiveRole = effectAttackerGUID;
	mExpireTime = 0;

    SetNeedUpdateFlag(monster_excl_need_update_flag);
}

void Monster::OnRoleDie(uint64_t killerGUID)
{
	UpdateBossInfoWhenDie();
	Role::OnRoleDie(killerGUID);
	CalcDropItems(killerGUID);
    AddPlayerExp();
    //AddToQuestAchieve();
    HandleReborn();
	RemoveExistTimeWhenDie();
}

void Monster::CalcDropItems(uint64_t killerGUID)
{
    //if (IsSummonMonster()) return;    // 召唤怪无掉落

	auto map = GetCurMap();
	if (nullptr == map) {
		return;
	}

	auto mcfg = map->GetMapConfig();
    auto *cfg = GetConfig();

	if (!cfg) {
		return;
	}
	//掉落表
	auto& mondropConfig = sDropConfig.GetMappings();
	auto mondropConfigIter = mondropConfig.find(cfg->Drop);
	if (mondropConfig.end() == mondropConfigIter)return;

	//组掉落表
	auto& dropplusConfig = sDropplusConfig.GetMappings();

	//人物爆率
	auto role = MapRoleMgr::GetInstance()->FindRole(mExclusiveRole);
	if (!role) {
		role = MapRoleMgr::GetInstance()->FindRole(killerGUID);
	};
	if (nullptr == role)return;
	Player* belongPlayer = nullptr;
	if (role->IsPet()){
		// 宠物击杀按主人爆率掉落
		auto pet = static_cast<Pet*>(role);
		belongPlayer = pet->GetMaster();
	}
	else if (role->IsPlayer()){
		belongPlayer = static_cast<Player*>(role);
	}
    else if (role->IsPlayerDoplganr()){
        auto *doplganr = static_cast<PlayerDoplganr *>(role);
        belongPlayer = doplganr->GetMaster();
    }
	else{
		return;
	}
	if (!belongPlayer)return;
	
	auto roleAddRate = belongPlayer->GetRoleProp(role_monster_drop_pct);  //该处返回值为整数 爆率只能倍增
	auto roleBaseRate = sGlobalConfig.GetData()->RoleBaseDropRate;

	CLuaObject dropData = NewLuaObj();
	CLuaObject luaRet = NewLuaObj();
	int idx = 1;
	for (auto& i : *(mondropConfigIter->second)) {
		CLuaObject table = NewLuaObj();
		int index = 1;
		// 物品权重
		CLuaObject itemTable = NewLuaObj();
		// 组权重
		CLuaObject groupTable = NewLuaObj();
		if (!i->item.empty()) {
			for (auto& x : i->item) {
				CLuaObject itemWeight = NewLuaObj();
				itemWeight[1] = x.first;
				itemWeight[2] = x.second;
				itemTable[index] = itemWeight;
				++index;
			}
			table[6] = drop_type_item;
		}
		else{
			for (auto& y : i->group) {
				auto groupWeightInfo = dropplusConfig.find(to_string(y.first));
				if (groupWeightInfo == dropplusConfig.end())continue;
				CLuaObject allGroupWeight = NewLuaObj();
				CLuaObject groupWeight = NewLuaObj();
				int groupItemIdx = 1;
				for (auto z : *groupWeightInfo->second) {
					CLuaObject groupItemWeight = NewLuaObj();
					groupItemWeight[1] = z->item;
					groupItemWeight[2] = z->weight;
					groupWeight[groupItemIdx] = groupItemWeight;
					++groupItemIdx;
				}
				allGroupWeight[1] = groupWeight;
				allGroupWeight[2] = y.second;
				groupTable[index] = allGroupWeight;
				++index;
			}
			table[6] = drop_type_group;
		}

		table[1] = itemTable;
		table[2] = groupTable;
		table[3] = i->rate;       // 掉落表爆率
		table[4] = i->min;
		table[5] = i->max;
		table[7] = roleAddRate;   // 人物爆率
		table[8] = roleBaseRate;  // 全局表爆率
		table[9] = i->dropgroupid;
	
		dropData[idx] = table;
		++idx;
	}

	LuaRet = dropData;

	CLuaObject retDropData = NewLuaObj();
	TRIGGER_EVENT_RET<CLuaObject>(retDropData, trigger_pre_drop_weight, belongPlayer->GetGUIDAsString(), this->GetGUIDAsString());

	CLuaObject firstRetTableData = NewLuaObj();
	firstRetTableData = dropData;
	if (CLuaLib::GetInstance()->IsHaveEvent(trigger_pre_drop_weight))
	{
		if (luabind::type(retDropData) != LUA_TTABLE) {
			LOG_ERROR("retDropRateWeightInfoTable is not table!");
			return;
		}

		firstRetTableData = retDropData;
	}

	////////////////////////////////////////

	CLuaObject finalDropInfo = NewLuaObj();
	int finalIdx = 1;

	for (luabind::iterator iter(firstRetTableData), end; iter != end; ++iter){
		int _rate = luabind::object_cast<int>((*iter)[3]);
		int _min = luabind::object_cast<int>((*iter)[4]);
		int _max = luabind::object_cast<int>((*iter)[5]);
		int _type = luabind::object_cast<int>((*iter)[6]);
		int _roleRate = luabind::object_cast<int>((*iter)[7]);
		int _globalRate = luabind::object_cast<int>((*iter)[8]);

		//获取每种物品的数量
		if (_min > _max){
			LOG_ERROR("the drop item num is invailed!");
			return;
		}

		// 是否掉落         计算公式：dropRate * roleRate * globalRate
		if (Tools::GenerateRandomInteger<uint16_t>(1, 10000) > (double)(_rate * PRECISION * _roleRate * PRECISION * _globalRate))continue;

		auto num = Tools::GenerateRandomInteger<uint16_t>(_min, _max);

		if (_type == drop_type_item) {
			if (luabind::type((*iter)[1]) != LUA_TTABLE)continue;
			auto sum = 0;
			// 计算总权重
			for (luabind::iterator itemIter((*iter)[1]), itemEnd; itemIter != itemEnd; ++itemIter){
				if (luabind::type((*itemIter)[1]) != LUA_TNUMBER)continue;
				if (luabind::type((*itemIter)[2]) != LUA_TNUMBER)continue;
				int _item = luabind::object_cast<int>((*itemIter)[1]);
				int _weight = luabind::object_cast<int>((*itemIter)[2]);
				sum += _weight;
			}
			auto randomWeight = Tools::GenerateRandomInteger<uint16_t>(1, sum);
			auto result = 0;
			for (luabind::iterator itemIter((*iter)[1]), itemEnd; itemIter != itemEnd; ++itemIter){
				int _item = luabind::object_cast<int>((*itemIter)[1]);
				int _weight = luabind::object_cast<int>((*itemIter)[2]);
				result += _weight;
				// 当前物品高于权重计算值 掉落该物品
				if (result >= randomWeight){
					auto itemData = sItemConfig.GetByID(_item);
					if (itemData == nullptr)break;
					CLuaObject table = NewLuaObj();
					table[1] = _item;
					table[2] = num;
					finalDropInfo[finalIdx] = table;
					break;
				}
			}
		}
		else {
			auto sum = 0;
			if (luabind::type((*iter)[2]) != LUA_TTABLE)continue;

			// 获取掉落组
			for (luabind::iterator groupIter((*iter)[2]), groupEnd; groupIter != groupEnd; ++groupIter){
				if (luabind::type((*groupIter)[1]) != LUA_TTABLE)continue;
				if (luabind::type((*groupIter)[2]) != LUA_TNUMBER)continue;
				int _weight = luabind::object_cast<int>((*groupIter)[2]);
				sum += _weight;
			}
			auto randomGroupWeight = Tools::GenerateRandomInteger<uint16_t>(1, sum);
			auto result = 0;
			for (luabind::iterator groupIter((*iter)[2]), groupEnd; groupIter != groupEnd; ++groupIter){
				if (luabind::type((*groupIter)[1]) != LUA_TTABLE)continue;
				if (luabind::type((*groupIter)[2]) != LUA_TNUMBER)continue;
				int _weight = luabind::object_cast<int>((*groupIter)[2]);
				result += _weight;

				if (result >= randomGroupWeight){
					// 掉落组中取掉落物品
					CLuaObject itemGroupTable = (*groupIter)[1];

					sum = 0;
					for (luabind::iterator itemIter(itemGroupTable), itemEnd; itemIter != itemEnd; ++itemIter) {
						if (luabind::type((*itemIter)[1]) != LUA_TNUMBER)continue;
						if (luabind::type((*itemIter)[2]) != LUA_TNUMBER)continue;
						int _itemWeight = luabind::object_cast<int>((*itemIter)[2]);
						sum += _itemWeight;
					}
					auto randomItemWeight = Tools::GenerateRandomInteger<uint16_t>(1, sum);
					result = 0;
					for (luabind::iterator itemIter(itemGroupTable), itemEnd; itemIter != itemEnd; ++itemIter) {
						if (luabind::type((*itemIter)[1]) != LUA_TNUMBER)continue;
						if (luabind::type((*itemIter)[2]) != LUA_TNUMBER)continue;
						int _item = luabind::object_cast<int>((*itemIter)[1]);
						int _itemWeight = luabind::object_cast<int>((*itemIter)[2]);
						result += _itemWeight;

						if (result >= randomItemWeight) {
							auto itemData = sItemConfig.GetByID(_item);
							if (itemData == nullptr)break;
							CLuaObject table = NewLuaObj();
							table[1] = _item;
							table[2] = num;
							finalDropInfo[finalIdx] = table;
							break;
						}
					}
					break;
				}
			}
		}
		++finalIdx;
	}

	LuaRet = finalDropInfo;
	CLuaObject retfinalDropInfo = NewLuaObj();
	TRIGGER_EVENT_RET<CLuaObject>(retfinalDropInfo, trigger_pre_drop_rate, belongPlayer->GetGUIDAsString(), this->GetGUIDAsString());

	CLuaObject secondRetTableData = NewLuaObj();
	secondRetTableData = finalDropInfo;
	if (CLuaLib::GetInstance()->IsHaveEvent(trigger_pre_drop_rate)) {
		if (luabind::type(retfinalDropInfo) != LUA_TTABLE) {
			LOG_ERROR("retDeopData is not table!");
			return;
		}
		secondRetTableData = retfinalDropInfo;
	}


	//获取脚本返回的最终掉落数据
	std::vector<DATA::DropData>finalDropData;


	for (luabind::iterator it(secondRetTableData), end; it != end; ++it){
		if (luabind::type((*it)[1]) != LUA_TNUMBER)continue;
		if (luabind::type((*it)[2]) != LUA_TNUMBER)continue;
		DATA::DropData tmpdata;
		tmpdata.itemid = luabind::object_cast<std::int32_t>((*it)[1]);
		tmpdata.num = luabind::object_cast<std::int32_t>((*it)[2]);
		finalDropData.push_back(tmpdata);
	}

	if (finalDropData.empty())return;

	//是否随机
	if (sGlobalConfig.GetData()->DropIsRandom)
	{
		static std::random_device rd;
		std::shuffle(finalDropData.begin(), finalDropData.end(), rd);
	}

	uint16_t posX, posY;
	//掉落
	CLuaObject item_table = NewLuaObj();
	int item_table_idx = 1;

	for (auto& i : finalDropData)
	{
		auto itemconfig = sItemConfig.GetByID(i.itemid);
		if (!itemconfig) continue;
		if (itemconfig->Stack <= 0) continue;
		if (itemconfig->Stack == 1)
		{
			for (int j = 0; j < i.num; ++j)
			{
				if (map->GetBlankSceneItemPos(GetRolePosX(), GetRolePosY(), posX, posY)) {
					auto sceneItem = map->AddSceneItem(posX, posY, i.itemid, 1, 0, 0, mExclusiveRole, mExclusiveRoleTeam);
					if (nullptr != sceneItem) {

						uint16_t oMType = GUID_TYPE_PART(GetGUID());
						if (mcfg) SendDBLogData(log_type_drop_item, LogDropItem(mcfg->Id, mcfg->MapType, belongPlayer->GetGUID(), GetGUID(), oMType, cfg->Id, log_drop_item_type_item, i.itemid, 1, sceneItem->GetName()));

						item_table[item_table_idx] = sceneItem->GetGUIDAsString();
						++item_table_idx;

					}
				}
			}
		}
		else
		{
			auto addnum = i.num;
			while (addnum > 0)
			{
				SceneItem* sceneItem = nullptr;
				if (!map->GetBlankSceneItemPos(GetRolePosX(), GetRolePosY(), posX, posY))
				{
					return;
				}
				int amount = 0;
				if (addnum <= itemconfig->Stack)
				{
					amount = addnum;
					sceneItem = map->AddSceneItem(posX, posY, i.itemid, addnum, 0, 0, mExclusiveRole, mExclusiveRoleTeam);
				}
				else
				{
					amount = itemconfig->Stack;
					sceneItem = map->AddSceneItem(posX, posY, i.itemid, itemconfig->Stack, 0, 0,
                        mExclusiveRole, mExclusiveRoleTeam);
				}
				if (nullptr != sceneItem) {

					uint16_t oMType = GUID_TYPE_PART(GetGUID());
					if (mcfg) SendDBLogData(log_type_drop_item, LogDropItem(mcfg->Id, mcfg->MapType, belongPlayer->GetGUID(), GetGUID(), oMType, cfg->Id, log_drop_item_type_item, i.itemid, amount, sceneItem->GetName()));

					item_table[item_table_idx] = sceneItem->GetGUIDAsString();
					++item_table_idx;
				}
				addnum -= itemconfig->Stack;
			}
		}

	}

	TRIGGER_EVENT(this, trigger_post_item_drop, belongPlayer->GetGUIDAsString(), this->GetGUIDAsString(), item_table);
}

bool Monster::IsTreasureMonster()
{
    auto *cfg = sMonsterConfig.Get(mMonsterTemplateID);
    if (!cfg) return false;
    return cfg->Type == monster_type_treasure;
}

bool Monster::IsBiaoChe() 
{
	auto* cfg = sMonsterConfig.Get(mMonsterTemplateID);
	if (!cfg) return false;
	return cfg->Type == monster_type_biaoche;
}

bool Monster::IsInSameTeam(Role *role)
{
    auto *master = GetMaster();
    if (!master) return false;
    return master->IsInSameTeam(role);
}

bool Monster::IsInSameGuild(Role *role)
{
    auto *master = GetMaster();
    if (!master) return false;
    return master->IsInSameGuild(role);
}

bool Monster::IsInSameCamp(Role *role)
{
    auto *master = GetMaster();
    if (!master) return false;
    return master->IsInSameCamp(role);
}

void Monster::AddPlayerExp()
{
    auto *cfg = GetConfig();
    if (!cfg) return;
    if (cfg->Exp == 0) return;

	//if (IsSummonMonster())return;

    auto players = GetBenefitPlayers();
    if (players.empty()) return;

    int64_t exp = cfg->Exp / players.size();
    if (exp == 0) exp = 1;

	log_params lp{ "怪物奖励" };
    for (auto &player : players) {
		// 怪物经验倍率
		auto magnification = player->GetRoleProp(role_exp_monster) + 10000;

		// 最大十倍
		magnification > 100000 ? magnification = 100000 : 0;

		magnification >= 0 ? exp = exp * magnification / 10000 : exp = 0;

        player->AddPlayerExperience(exp, lp);
    }
}

void Monster::AddToQuestAchieve()
{
    auto *cfg = GetConfig();
    if (!cfg) return;
    const auto &id = cfg->Id;

    auto players = GetBenefitPlayers();

    for (auto &player : players) {
        player->GetQuestDataMgr().AddToQuestAchieve(quest_achev_kill_monster, id, 1);
    }
}

std::vector<Player *> Monster::GetBenefitPlayers()
{
    std::vector<Player *> players;

    const auto *team = TeamMgr::GetInstance()->FindTeam(mExclusiveRoleTeam);
    if (team) {
        const auto &range = sGlobalConfig.GetData()->TeamBenefitRange;

        for (const auto &member : team->mMemberList) {

            auto *player = MapRoleMgr::GetInstance()->FindPlayer(member.guid);
            if (!player) continue;

            auto dist = DistanceFromRole(player);
            if (dist > range) continue;

            players.push_back(player);
        }
    }
    else {
        auto *owner = MapRoleMgr::GetInstance()->FindPlayer(mExclusiveRole);
        if (owner) players.push_back(owner);
    }

    return players;
}

void Monster::UpdateExclusiveRole(int delta)
{
	if (mExclusiveRole == 0) return;

	mExpireTime += delta;
	if (mExpireTime >= 6000) {	//暂时写死6秒，后面改为使用全局表中配置
		mExclusiveRole = 0;
		mExclusiveRoleTeam = 0;
		mExpireTime = 0;

        ResetNeedUpdateFlag(monster_excl_need_update_flag);
	}
}

void Monster::UpdateAliveStateByOwner()
{
	if (0 == mMasterGUID) {
		return;
	}

	bool ret = true;

	auto owner = MapRoleMgr::GetInstance()->FindRole(mMasterGUID);
	if (nullptr == owner) {
		if (!mNeedEnterMasterLogoutEvent)return;
		TRIGGER_EVENT_RET<bool>(ret, trigger_remove_summon_monster_when_logout, GetMasterGUIDAsString(), GetGUIDAsString());
		mNeedEnterMasterLogoutEvent = false;
		if (!ret)return;
		RemoveMonster(false);
		MapRoleMgr::GetInstance()->RemoveMonster(GetGUID());
		return;
	}
	else {
		mNeedEnterMasterLogoutEvent = true;
	}
	
	if (!IsInSameMap(owner)) {
		if (!mNeedEnterMasterInDifferentMapEvent)return;
		TRIGGER_EVENT_RET<bool>(ret, trigger_remove_summon_monster_when_different_map, GetMasterGUIDAsString(), GetGUIDAsString());
		mNeedEnterMasterInDifferentMapEvent = false;
		if (!ret)return;
		RemoveMonster(false);
		MapRoleMgr::GetInstance()->RemoveMonster(GetGUID());
	}
	else {
		mNeedEnterMasterInDifferentMapEvent = true;
	}
}

void Monster::SetRebornRegion(uint16_t left, uint16_t top, uint16_t width, uint16_t height)
{
    mRebornRegionLeft = left;
    mRebornRegionTop = top;
    mRebornRegionWidth = width;
    mRebornRegionHeight = height;
}

void Monster::HandleReborn()
{
    if (mRebornTime == 0) return;

    auto *map = GetCurMap();
    if (!map) return;

    auto mapID = map->GetTemplateID();
    auto monsterTemplateID = mMonsterTemplateID;
    auto left = mRebornRegionLeft;
    auto top = mRebornRegionTop;
    auto with = mRebornRegionWidth;
    auto height = mRebornRegionHeight;
    auto dir = mRebornDir;
    auto wayFinding = m_WayFinding;
    auto camp = mCamp;
    auto reborn = mRebornTime;
	auto curGUID = GetGUID();

    TimerData timer;
    timer.interval = mRebornTime;
    timer.loop = false;
    timer.callBack = [=](const TimerData&) {

        auto *map = MapMgr::GetInstance()->FindMapByID(mapID);

        auto *cfg = sMonsterConfig.Get(monsterTemplateID);

        if (!map || !cfg) return;

        auto *monster = map->GenMonster(cfg, left, top, with, height, dir, curGUID);
        if (!monster) return;
        monster->SetCamp(camp);
        monster->SetRebornTime(reborn);
        monster->SetRebornRegion(left, top, with, height);
        monster->SetRebornDir(dir);
    };

    auto TimerID = ITimeHelper::GetInstance()->AddTimer(timer,true);
	//ITimeHelper::GetInstance()->AddStrData(TimerID, "name", "HandleReborn");
}

void Monster::SetMasterGUID(uint64_t guid)
{
    mMasterGUID = guid;

    if (guid)
        SetNeedUpdateFlag(ai_need_update_flag);
    else
        ResetNeedUpdateFlag(ai_need_update_flag);
}

void Monster::TeleportToMaster()
{
    if (!IsSummonMonster() || !mMonsterAI_ptr) return;

	//mMonsterAI_ptr->JumpToOwner();
}

bool Monster::JumpMap(uint16_t x, uint16_t y)
{
	auto tarMap = GetCurMap();
	if (!tarMap) return false;
	if (!tarMap->FindJumpablePos(x, y)) return false;

	auto rolemove = GetRoleMove();
	if (rolemove)
	{
		rolemove->StopMove(false);
	}

	auto roleAttr = GetRoleAttr();
	if (roleAttr) roleAttr->SetMoveType(move_type_jump);
	SetRolePos(x, y);
	tarMap->GetMapAoi().RoleEnter(this);
	if (roleAttr->GetMoveType() == move_type_jump) roleAttr->SetMoveType(move_type_walk);
	return true;
}

bool Monster::JumpMap(Map* tarMap, uint16_t x, uint16_t y)
{
	return Role::JumpMap(tarMap, x, y);
}

bool Monster::IsEmptyHateValueMap()
{
	return this->HatedVauleMap.empty();
}

bool Monster::IsTarInHateValueMap(uint64_t tarGuid)
{
	if (HatedVauleMap.empty())return false;
	auto it = HatedVauleMap.find(tarGuid);
	if (it != HatedVauleMap.end())return true;
	return false;
}

Role* Monster::GetMaxHatedValueRole()
{
	Hated_Value tmpdata;
	uint64_t tmpGuid = 0;
	std::map<uint64_t, Hated_Value>::iterator iter;
	for (auto& i : HatedVauleMap)
	{
		if (!mMonsterAI_ptr->IsInTraRange(i.first)) continue;
		if (i.second.hated_value > tmpdata.hated_value)
		{
			tmpGuid = i.first;
			tmpdata = i.second;
		}
		else if (i.second.hated_value == tmpdata.hated_value)
		{
			if (i.second.timer < tmpdata.timer)
			{
				tmpGuid = i.first;
				tmpdata = i.second;
			}
		}
	}
	if (tmpGuid)
	{
		auto role = MapRoleMgr::GetInstance()->FindRole(tmpGuid);
		if (!role)
		{
			DeleteMaxHateValue(tmpGuid);
		}
		if (role->GetRoleState()->GetState() == role_state_die) {
			DeleteMaxHateValue(tmpGuid);
			return nullptr;
		}
		return role;
	}
	return nullptr;
}

Player* Monster::GetMaxHatedValueRedNameRole()
{
	Hated_Value tmpdata;
	uint64_t tmpGuid = 0;
	Hated_Value tmpRedData;
	uint64_t TmpRedGUID = 0;
	std::map<uint64_t, Hated_Value>::iterator iter;
	for (auto& i : HatedVauleMap)
	{
		if (!mMonsterAI_ptr->IsInTraRange(i.first)) continue;
		auto tarPlayer = MapRoleMgr::GetInstance()->FindPlayer(i.first);
		if (!tarPlayer)continue;
		if (tarPlayer->IsRedName())
		{
			if (i.second.hated_value > tmpRedData.hated_value)
			{
				TmpRedGUID = i.first;
				tmpRedData = i.second;
			}
			else if (i.second.hated_value == tmpRedData.hated_value)
			{
				if (i.second.timer < tmpRedData.timer)
				{
					TmpRedGUID = i.first;
					tmpRedData = i.second;
				}
			}
		}
		else
		{
			if (i.second.hated_value > tmpdata.hated_value)
			{
				tmpGuid = i.first;
				tmpdata = i.second;
			}
			else if (i.second.hated_value == tmpdata.hated_value)
			{
				if (i.second.timer < tmpdata.timer)
				{
					tmpGuid = i.first;
					tmpdata = i.second;
				}
			}
		}

	}
	auto finalGuid = TmpRedGUID ? TmpRedGUID : tmpGuid;
	auto tarPlayer = MapRoleMgr::GetInstance()->FindPlayer(finalGuid);
	return tarPlayer;
}

void Monster::UpdateBossInfoWhenDie()
{
	auto cfg = sMonsterConfig.GetByID(GetTemplateID());
	if (!cfg)return;
	if (cfg->Type != monster_type_boss)return;

	auto map = GetCurMap();
	if (!map)return;

	auto stamp = GetTimeStampMillisecond2();
	auto reliveTime = (mRebornTime == 0) ? mRebornTime : mRebornTime + stamp;

	BossInfoMgr::GetInstance()->UpdateBossInfoWhenDie(BossInfo(cfg->Id, GetGUID(), map->GetTemplateID(), reliveTime, map->GetName(), 0));
	
}

void Monster::UpdateBossInfoWhenGen(DATA::Monster* cfg, uint64_t lastGUID)
{
	if (cfg->Type != monster_type_boss)return;
	// 增加boss信息
	auto map = GetCurMap();
	if (!map)return;
	BossInfoMgr::GetInstance()->UpdateBossInfoWhenGen(BossInfo(cfg->Id, GetGUID(), map->GetTemplateID(), 0, map->GetName(), lastGUID));
}

bool Monster::NeedMonsterAI(DATA::Monster *pConfig)
{
    if (!pConfig) return false;
    if (pConfig->Type == monster_type_treasure) return false;
    return true;
}

MonsterAI* Monster::CreateMonsterAI(Monster* monster,DATA::Monster* pConfig)
{
	if (nullptr == monster || nullptr == pConfig) {
		return nullptr;
	}

	auto type = pConfig->MonsterAIType;//新建的类型
	MonsterAI* tmpMonsterAI = nullptr;
	switch (type)
	{
	case all_type_stay_put:
		tmpMonsterAI = new MonsterAI_Type1();
		break;
	case type1_active_pursuit:
		tmpMonsterAI = new MonsterAI_Type1();
		break;
	case type1_non_active_pursuit:
		tmpMonsterAI = new MonsterAI_Type1();
		break;
	case type2_dadaowei:
		tmpMonsterAI = new MonsterAI_Type2();
		break;
	case type3_shouchengweibing:
		tmpMonsterAI = new MonsterAI_Type3();
		break;
	case type4_biaoche_active:
		tmpMonsterAI = new MonsterAI_Type4();
		break;
	case type4_biaoche_non_active:
		tmpMonsterAI = new MonsterAI_Type4();
		break;
	case type5_biaoche_non_master:
		tmpMonsterAI = new MonsterAI_Type5();
		break;
	default:
		tmpMonsterAI = new MonsterAI_Type1();
		monster->SetWayFinding(false);
		break;
	}

	tmpMonsterAI->Init(monster, pConfig);


	return tmpMonsterAI;
}

void Monster::AddHatedValue(uint64_t guid, uint32_t hatevalue)
{
	Hated_Value tmpdata;
	auto curtime = time(nullptr);
	tmpdata.hated_value = hatevalue;
	auto iter = HatedVauleMap.find(guid);
	if (iter != HatedVauleMap.end())
	{
		if ((iter->second.hated_value += hatevalue) >= MAX_HATED_VALUE)
		{
			iter->second.hated_value = MAX_HATED_VALUE;
			iter->second.timer = time(nullptr);
		}
		return;
	}
	if (hatevalue >= MAX_HATED_VALUE)
	{
		tmpdata.timer = time(nullptr);
	}
	HatedVauleMap.insert(std::make_pair(guid, tmpdata));
}

void Monster::DeleteMaxHateValue(uint64_t guid)
{
	auto iter = HatedVauleMap.find(guid);
	if (iter == HatedVauleMap.end())return;
	HatedVauleMap.erase(iter);
}

void Monster::DecreaseHateValue()
{
	for (auto iter = HatedVauleMap.begin();iter!=HatedVauleMap.end();)
	{
		if (iter->second.hated_value* DECREASE_PERCENTAGE < 0.1)
		{
			iter = HatedVauleMap.erase(iter);
			continue;
		}
		iter->second.hated_value *= DECREASE_PERCENTAGE;
		++iter;
	}
}

void Monster::ClearInvalidHateValue()
{
	for (auto iter = HatedVauleMap.begin(); iter != HatedVauleMap.end();)
	{
		auto role = MapRoleMgr::GetInstance()->FindRole(iter->first);
		if (!role)
		{
			iter = HatedVauleMap.erase(iter);
			continue;
		}
		if (role->GetRoleState()->GetState() == role_state_die || !GetAIMonster()->IsInTraRange(role->GetGUID()))
		{
			iter = HatedVauleMap.erase(iter);
			continue;
		}
		++iter;
	}
}

CLuaObject Monster::GetHateValueMapToLua()
{
	auto luaObj = NewLuaObj();
	int index = 1;

    for(auto &i:HatedVauleMap)
	{
		CLuaObject table = NewLuaObj();
		table[1] = i.first;
		table[2] = i.second.hated_value;
		table[3] = i.second.timer;
		luaObj[index] = table;
		index++;
	}
	return luaObj;
}

void Monster::RemoveMonster(bool appearBody)
{
	auto pMap = GetCurMap();
	if (!pMap) return;

	auto x = GetRolePosX();
	auto y = GetRolePosY();
	auto statu = GetRoleState();
	auto attr = GetRoleAttr();
	if (statu){
		statu->SetState(role_state_die);
	}
	if (attr){
		attr->SetRoleProp(role_hp, 0);
	}
	AttackResult res;
	res.remainHP = 0;
	res.targetGUID = GetGUID();
	auto f = [&](Role* pRole) {
	    NotifyPlayer_RoleDie(pRole, res);
	};

	pMap->ApplyFuncToAllPlayersInAroundRegions(x, y, f);
	if (appearBody)
	{
		MapRoleMgr::GetInstance()->DelaySendRoleDisappearNtfToAroundPlayers(GetGUID());
	}
	else
	{
		auto pMap = GetCurMap();
		if (!pMap) return;
		pMap->RoleLeave(this);
		MapRoleMgr::GetInstance()->RemoveRole(this);
	}
	RemoveBuffWhenDie();
	RemoveExistTimeWhenDie();
	Role::OnRoleDie(GetGUID());
}

void Monster::SetExistTime(uint32_t time)
{
	TimerData timer;
	timer.interval = time;
	timer.loop = false;
	timer.callBack = [this](const TimerData&) {
		if (CheckAlive()) {
			TRIGGER_EVENT(this, trigger_monster_arrived_exist_time, GetGUIDAsString());
			RemoveMonster();
		}
	};
	ITimeHelper::GetInstance()->AddTimer(timer,true);
	//ITimeHelper::GetInstance()->AddStrData(timer.id, "name", "SetExistTime");
	mMonsterExistTimerID = timer.id;
}

void Monster::RemoveExistTimeWhenDie()
{
	if (mMonsterExistTimerID) {
		ITimeHelper::GetInstance()->RemoveTimer(mMonsterExistTimerID);
		mMonsterExistTimerID = 0;
	}
}

void Monster::SetBackStatus()
{
	auto global = sGlobalConfig.GetData();
	if (!global)return;
	if (Tools::GenerateRandomInteger<int>(0, 10000) <= global->MonsterBackRate) {
		auto AI = GetAIMonster();
		if (!AI)return;
		AI->SetBackStatus();
	}
}
