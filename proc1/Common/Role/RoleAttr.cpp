#include "stdafx.h"
#include "RoleAttr.h"
#include "Role.h"
#include "Map.h"
#include "LuaHost.h"

// 开区间
std::list<std::pair<int32_t, int32_t>> RoleAttr::AllPropList = {
	{(int32_t)role_1000_min, (int32_t)role_1000_max},     // 1000
	{(int32_t)role_2000_min, (int32_t)role_2000_max},     // 2000
	{(int32_t)role_10000_min, (int32_t)role_10000_max},   // 10000
	{(int32_t)role_7700_min, (int32_t)role_7700_max},     // 7700
	{(int32_t)role_7400_min, (int32_t)role_7400_max},     // 7400
	{(int32_t)role_7000_min, (int32_t)role_7000_max},     // 7000
	{(int32_t)role_6000_min, (int32_t)role_6000_max},     // 6000
	{(int32_t)role_9000_min, (int32_t)role_9000_max},     // 9000
	{(int32_t)role_9500_min, (int32_t)role_9500_max},     // 9500
};

int32_t & RoleAttr::AllPropVec::operator[](int32_t prop)
{
    for (uint16_t i = 0; i < Property.size(); ++i)
    {
        if (Property[i].CheckIn(prop))
        {
            return Property[i][prop];
        }
    }

    for (auto iter = AllPropList.begin(); iter != AllPropList.end(); ++iter)
    {
        if (prop <= iter->first || prop >= iter->second) continue;
        PropVec pv(iter->first, iter->second);
        Property.push_back(pv);
        return Property.back()[prop];
    }

    Null = 0;
    return Null;
}

RoleAttr::RoleAttr(Role* master) : RoleAction(master)
, PosX(0)
, PosY(0)
, Dir(4)
, MoveType(0)
, UpGradeExp(0)
{
	Property64.resize(role_attr_ext_max + 1, 0);
	mDynAttrs.clear();
	mTmpDynAttrs.clear();
	RecoveryIntervalTime = 3000;
	CurRecoveryInterval = 0;
	PropertyHistoryMap.clear();
}

RoleAttr::~RoleAttr()
{
}

void RoleAttr::SetRoleDir(uint8_t dir)
{
	if (nullptr == mMaster) {
		return;
	}

	if (dir >= dir_max || dir == Dir) {
		return;
	}

	Dir = dir;
	auto map = mMaster->GetCurMap();
	if (nullptr != map) {
		ProtoGS_TurnNtf ntf;
		ntf.guid = mMaster->GetGUID();        // 角色ID
		ntf.dir = dir;
		map->SendRoleDirChangeNtf(mMaster, ntf);
	}
}
void RoleAttr::SetDynAttr(uint16_t index, uint16_t attr, int32_t value)
{
	auto it = std::find_if(mDynAttrs.begin(), mDynAttrs.end(), [&](const auto& attr) { return attr.index == index; });
	if (it == mDynAttrs.end()) {
		value = AddRoleProp(attr, value);
		mDynAttrs.emplace_back(index, attr, value);
	}
	else {
		AddRoleProp(it->attr, -1 * it->value);
		it->attr = attr;
		it->value = AddRoleProp(it->attr, value);
	}
	mDynAttrsMody = true;
}

DYN_ATTR RoleAttr::GetDynAttr(uint16_t index)
{
	DYN_ATTR dynAttr;

	auto it = std::find_if(mDynAttrs.begin(), mDynAttrs.end(), [&](const auto& attr) { return attr.index == index; });
	if (it == mDynAttrs.end()) return dynAttr;

	dynAttr = *it;
	return dynAttr;
}

bool RoleAttr::Init()
{
	if (nullptr == mMaster) return true;

	// 动态属性
	for (auto& attr : mTmpDynAttrs)
	{
		SetDynAttr(attr.index, attr.attr, attr.value);
	}
	if (sGlobalConfig.GetData())
	{
		RecoveryIntervalTime = sGlobalConfig.GetData()->RecoveryPropertyTime;
	}

	return true;
}


void RoleAttr::CalculateRoleAttr_Base()
{
	auto master = GetMaster();
	if (!master) return;
	for (auto i = (int)role_9500_min; i < (int)role_9500_max; i++)
	{
		Property[i] = 0;
		//ReCalcProperty(i, 0, true);
		//SetRoleProp(i, 0);
	}
	for (auto i = (int)role_base_min_phy_def; i < (int)role_1000_max; i++)
	{
		Property[i] = 0;
	}
	for (auto i = (int)role_2000_min; i < (int)role_2000_max; i++)
	{
		Property[i] = 0;
	}

	for (auto i = (int)role_min_phy_def; i < (int)role_10000_max; i++)
	{
		Property[i] = 0;
	}
}


void RoleAttr::Update(int32_t delta)
{
	RecoveryProperty(delta);

    //static int32_t acc = 0;
    //acc += delta;
    //if (acc > 30) {
	    SendPropertyModyNtf();
    //    acc = 0;
    //}

    CheckNeedUpdate();
}

void RoleAttr::CopyFromOwner(RoleAction* ra)
{
	auto roleAttr = static_cast<RoleAttr*>(ra);
	if (!roleAttr) return;

	Property = roleAttr->Property;
	Property64 = roleAttr->Property64;

	SetRolePos(roleAttr->GetRolePosX(), roleAttr->GetRolePosY());
	SetRoleDir(roleAttr->GetRoleDir());
}

bool RoleAttr::NeedNotifyOther(int32_t prop)
{
    if (prop == role_hp || prop == role_mp) return true;

    static const int32_t props[] = {    // 必须有序
        role_level, role_job, role_atk_mode, role_pk, role_gender,
        role_vip_level, role_camp, role_has_collide, role_has_repelled,
        role_can_through, role_has_team, role_is_show_fashion, role_changed_modelid,
        role_can_through_monster, role_max_hp, role_max_mp, role_move_speed,
        role_attack_speed, role_casting_speed
    };

    return std::binary_search(std::begin(props), std::end(props), prop);
}

void RoleAttr::SendRoleAttrNtfToSelf()
{
    if (!mMaster || !mMaster->IsPlayer()) return;
    auto *player = static_cast<Player *>(mMaster);
    if (!player->IsOnline()) return;

    ProtoMS_RoleAttrNtf data;
    data.role_guid = player->GetGUID();
    data.attr_num = 0;
    data.clsessnum = 1;
    data.clsessids[0] = player->GetClSessionID();

    for (const auto &prop : PropertyMody) {
        data.attr_name[data.attr_num] = prop;
        data.attr_value[data.attr_num] = GetRoleProp(prop);
        if (++data.attr_num == _countof(data.attr_name)) {
            SendDataBySessionID(player->GetGsSessionID(), data);
            data.attr_num = 0;
        }
    }

    if (data.attr_num > 0) {
        SendDataBySessionID(player->GetGsSessionID(), data);
    }
}

void RoleAttr::SendRoleAttrNtfToOther()
{
    if (!mMaster) return;

    auto *map = mMaster->GetCurMap();
    if (!map) return;

    auto clsessidsMap = map->GetAroundPlayerCLSessionID(mMaster, false);
    if (clsessidsMap.empty()) return;

    ProtoMS_RoleAttrNtf data;
    data.role_guid = mMaster->GetGUID();
    data.attr_num = 0;

    for (const auto &prop : PropertyMody) {
        if (!NeedNotifyOther(prop)) continue;
        data.attr_name[data.attr_num] = prop;
        data.attr_value[data.attr_num] = GetRoleProp(prop);
        if (++data.attr_num == _countof(data.attr_name)) {
            SendDataBySessionID(clsessidsMap, data);
            data.attr_num = 0;
        }
    }

    bool candrop = std::all_of(data.attr_name, data.attr_name + data.attr_num, [](const auto &prop) {
        return (prop == role_hp || prop == role_mp);
    });

    if (data.attr_num > 0) {
        SendDataBySessionID(clsessidsMap, data, candrop);
    }
}

void RoleAttr::SendRoleAttrExtNtfToSelf()
{
    if (!mMaster || !mMaster->IsPlayer()) return;
    auto *player = static_cast<Player *>(mMaster);
    if (!player->IsOnline()) return;

    auto *map = player->GetCurMap();
    if (!map) return;

    ProtoMS_RoleAttrExtNtf data;
    data.player_guid = player->GetGUID();
    data.num = 0;
    data.sessid = player->GetClSessionID();

    for (const auto &prop : PropertyMody64) {
        data.attr_name[data.num] = prop;
        data.attr_value[data.num] = GetProp64(prop);
        if (++data.num == _countof(data.attr_name)) {
            SendDataBySessionID(player->GetGsSessionID(), data);
            data.num = 0;
        }
    }

    if (data.num > 0) {
        SendDataBySessionID(player->GetGsSessionID(), data);
    }
}

void RoleAttr::SendPropertyModyNtf()
{
	if (!mMaster) return;

	if (!PropertyMody.empty()) {
        SendRoleAttrNtfToSelf();
        SendRoleAttrNtfToOther();
		PropertyMody.clear();
	}

	if (!PropertyMody64.empty()) {
        SendRoleAttrExtNtfToSelf();
		PropertyMody64.clear();
	}

	if (mDynAttrsMody)
	{
		MSG_BUFFER_DATA(ProtoMS_RoleDynAttrsNtf, ntf);
		ntf.role_guid = mMaster->GetGUID();
		ntf.custom << mDynAttrs;
		// 单发
		mMaster->SendRoleDynAttrsNtf(ntf);
		// 广播
		//map->SendRoleDynAttrsNtf(mMaster, ntf);
		mDynAttrsMody = false;
	}
}

void RoleAttr::OnRecvRoleDynAttrsList(ROLE_DYN_ATTRS& attrsList)
{
	if (attrsList.dyn_attrs.empty()) return;

	mTmpDynAttrs = std::move(attrsList.dyn_attrs);
}

void RoleAttr::GetListProp(CLuaObject& list, uint16_t type, uint16_t min, uint16_t max)
{
	int ListIdx = 1;
	switch (type) {
	case lua_get_prop:
	{
		//for (auto &range : AllPropList) {
		//	for (int idx = range.first + 1; idx < range.second; ++idx) {

		//	}
		//}
		for (auto i = min; i <= max; ++i) {
			auto obj = NewLuaObj();
			obj[1] = i;
			obj[2] = Property[i];
			list[ListIdx++] = obj;
		}
		break;
	}
	case lua_get_prop_64:
	{
		for (int i = 0; i < role_attr_ext_max; ++i) {
			auto obj = NewLuaObj();
			obj[1] = i;
			obj[2] = std::to_string(Property64[i]);
			list[ListIdx++] = obj;
		}
		break;
	}
	case lua_get_prop_dyn: 
	{
		for (auto& i : mDynAttrs) {
			auto obj = NewLuaObj();
			obj[1] = i.index;
			obj[2] = i.attr;
			obj[3] = std::to_string(i.value);
			list[ListIdx++] = obj;
		}
		break;
	}
	default:
		break;
	}
}

void RoleAttr::PrintPropertyMap(int32_t prop)
{
	if (LuaHost::GetInstance()->GetRecordhistory())
	{
		int i = 1;
		for (auto itr : PropertyHistoryMap[prop])
		{
			auto info = itr.second;
			LOG_ERROR("[prop:%d num:%d,pre:%d,cur:%d,change:%d,来源type:%d,来源id:%d]", prop, i, info.predValue, info.curValue, info.changeValue, info.type, info.id);
			i++;
		}
	}
}

void RoleAttr::InsterPropertyHistoryMap(int32_t prop, int32_t before, int32_t after)
{
	if (LuaHost::GetInstance()->GetRecordhistory())
	{
		if (!mMaster) return;
		auto size = PropertyHistoryMap[prop].size();
		Propinfo info;
		info.curValue = after;
		info.predValue = before;
		info.changeValue = after - before;
		info.id = mMaster->temp_attr_id;
		info.type = mMaster->temp_attr_type;
		PropertyHistoryMap[prop][size] = info;
	}
}

static inline void CallBackUpdateAttr32(Role* master, int32_t prop, int32_t before, int32_t after)
{
	if (before != after && LuaHost::GetInstance()->IsCallBackUpdateAttr(prop, true) && master)
	{
		TRIGGER_EVENT(trigger_role_update_attr, master->GetGUIDAsString(), prop, 1, std::to_string(before), std::to_string(after));
	}
	master->GetRoleAttr()->InsterPropertyHistoryMap(prop, before, after);
}
std::pair<int32_t, int32_t> RoleAttr::ReCalcProperty(int32_t prop, int32_t value, bool beSet)
{
	auto master = GetMaster();
	int32_t& curValue = Property[prop];
	int32_t before = curValue;
	int32_t after = 0;
	// 更新
	beSet ? curValue = value : curValue += value;
	after = curValue;
    if (before != after) PropertyMody.insert(prop);
	//////////////////////////////////// ReCalcFunc ////////////////////////////////////
	// 计算类型
	enum ReCalcType{
		ReCalcType_0 = 0,	// 直接更新
		ReCalcType_1,		// A*B
		ReCalcType_2,		// 速度
		ReCalcType_3,		// 组合
	};
	// 0.直接修改属性值
	static ReCalcFunc ReCalcFunc0 = [](int32_t propType, int32_t propValue, bool beSet, Role* master, RoleAttr* roleAttr)->int32_t {
		return roleAttr->Property[propType];
	};
	// 1.固定两个属性相乘公式:A*B
	static ReCalcFunc ReCalcFunc1 = [](int32_t propType, int32_t propValue, bool beSet, Role* master, RoleAttr* roleAttr)->int32_t {
		// key:乘数属性1,value.first:乘数属性2,value.second:结果属性
		static const std::map<int32_t, std::pair<int32_t, int32_t>> kv1 =
		{
			{(int32_t)role_base_max_hp, {(int32_t)role_base_max_hp_pct,(int32_t)role_max_hp}},
			{(int32_t)role_base_max_mp, {(int32_t)role_base_max_mp_pct,(int32_t)role_max_mp}},
			{(int32_t)role_base_min_phy_def, {(int32_t)role_base_min_phy_def_pct,(int32_t)role_min_phy_def}},
			{(int32_t)role_base_max_phy_def, {(int32_t)role_base_max_phy_def_pct,(int32_t)role_max_phy_def}},
			{(int32_t)role_base_min_mag_def, {(int32_t)role_base_min_mag_def_pct,(int32_t)role_min_mag_def}},
			{(int32_t)role_base_max_mag_def, {(int32_t)role_base_max_mag_def_pct,(int32_t)role_max_mag_def}},
			{(int32_t)role_base_min_phy_atk, {(int32_t)role_base_min_phy_atk_pct,(int32_t)role_min_phy_atk}},
			{(int32_t)role_base_max_phy_atk, {(int32_t)role_base_max_phy_atk_pct,(int32_t)role_max_phy_atk}},
			{(int32_t)role_base_min_mag_atk, {(int32_t)role_base_min_mag_atk_pct,(int32_t)role_min_mag_atk}},
			{(int32_t)role_base_max_mag_atk, {(int32_t)role_base_max_mag_atk_pct,(int32_t)role_max_mag_atk}},
			{(int32_t)role_base_min_tao_atk, {(int32_t)role_base_min_tao_atk_pct,(int32_t)role_min_tao_atk}},
			{(int32_t)role_base_max_tao_atk, {(int32_t)role_base_max_tao_atk_pct,(int32_t)role_max_tao_atk}},
			{(int32_t)role_base_hp_rec, {(int32_t)role_base_hp_rec_pct,(int32_t)role_hp_rec}},
			{(int32_t)role_base_mp_rec, {(int32_t)role_base_mp_rec_pct,(int32_t)role_mp_rec}},
		};
		static const std::map<int32_t, std::pair<int32_t, int32_t>> kv2 =
		{
			{(int32_t)role_base_max_hp_pct, {(int32_t)role_base_max_hp,(int32_t)role_max_hp}},
			{(int32_t)role_base_max_mp_pct, {(int32_t)role_base_max_mp,(int32_t)role_max_mp}},
			{(int32_t)role_base_min_phy_def_pct, {(int32_t)role_base_min_phy_def,(int32_t)role_min_phy_def}},
			{(int32_t)role_base_max_phy_def_pct, {(int32_t)role_base_max_phy_def,(int32_t)role_max_phy_def}},
			{(int32_t)role_base_min_mag_def_pct, {(int32_t)role_base_min_mag_def,(int32_t)role_min_mag_def}},
			{(int32_t)role_base_max_mag_def_pct, {(int32_t)role_base_max_mag_def,(int32_t)role_max_mag_def}},
			{(int32_t)role_base_min_phy_atk_pct, {(int32_t)role_base_min_phy_atk,(int32_t)role_min_phy_atk}},
			{(int32_t)role_base_max_phy_atk_pct, {(int32_t)role_base_max_phy_atk,(int32_t)role_max_phy_atk}},
			{(int32_t)role_base_min_mag_atk_pct, {(int32_t)role_base_min_mag_atk,(int32_t)role_min_mag_atk}},
			{(int32_t)role_base_max_mag_atk_pct, {(int32_t)role_base_max_mag_atk,(int32_t)role_max_mag_atk}},
			{(int32_t)role_base_min_tao_atk_pct, {(int32_t)role_base_min_tao_atk,(int32_t)role_min_tao_atk}},
			{(int32_t)role_base_max_tao_atk_pct, {(int32_t)role_base_max_tao_atk,(int32_t)role_max_tao_atk}},
			{(int32_t)role_base_hp_rec_pct, {(int32_t)role_base_hp_rec,(int32_t)role_hp_rec}},
			{(int32_t)role_base_mp_rec_pct, {(int32_t)role_base_mp_rec,(int32_t)role_mp_rec}},
		};
		// 默认万分比
		auto precision = PRECISION;
		auto global = sGlobalConfig.GetData();
		if (global && global->Precision == precision_type_1)
		{
			precision = PERCENTAGE;
		}
		bool beFind = false;
		std::pair<int32_t, int32_t> change{ 0,0 };
		auto iter = kv1.find(propType);
		if (iter != kv1.end())
		{
			change.second = change.first = roleAttr->Property[iter->second.second];
			roleAttr->Property[iter->second.second] = std::floor((double)roleAttr->Property[iter->first] * ((double)roleAttr->Property[iter->second.first] * precision + 1));
			beFind = true;
		}
		else
		{
			iter = kv2.find(propType);
			if (iter != kv2.end())
			{
				change.second = change.first = roleAttr->Property[iter->second.second];
				roleAttr->Property[iter->second.second] = std::floor((double)roleAttr->Property[iter->second.first] * ((double)roleAttr->Property[iter->first] * precision + 1));
				beFind = true;
			}
		}
		if (!beFind)
		{
			LOG_ERROR("[%s:%d] 更新属性错误. propType:%d", __FUNCTION__, __LINE__, propType);
			return roleAttr->Property[propType];
		}
		change.second = roleAttr->Property[iter->second.second];
        if (change.first != change.second)
		    roleAttr->PropertyMody.insert(iter->second.second);
		if (iter->second.second == role_max_hp && roleAttr->Property[role_hp] > roleAttr->Property[iter->second.second])
		{
			std::pair<int32_t, int32_t> hp{ 0,0 };
			hp.second = hp.first = roleAttr->Property[role_hp];
			roleAttr->Property[role_hp] = roleAttr->Property[iter->second.second];
			roleAttr->PropertyMody.insert(role_hp);
			hp.second = roleAttr->Property[role_hp];
			CallBackUpdateAttr32(master, role_hp, hp.first, hp.second);
		}
		else if (iter->second.second == role_max_mp && roleAttr->Property[role_mp] > roleAttr->Property[iter->second.second])
		{
			std::pair<int32_t, int32_t> mp{ 0,0 };
			mp.second = mp.first = roleAttr->Property[role_mp];
			roleAttr->Property[role_mp] = roleAttr->Property[iter->second.second];
			roleAttr->PropertyMody.insert(role_mp);
			mp.second = roleAttr->Property[role_mp];
			CallBackUpdateAttr32(master, role_mp, mp.first, mp.second);
		}
		CallBackUpdateAttr32(master, iter->second.second, change.first, change.second);
		return roleAttr->Property[propType];
	};
	// 2.速度属性,配置的最终值是时间(毫秒),速度提升值是变小的
	static ReCalcFunc ReCalcFunc2 = [](int32_t propType, int32_t propValue, bool beSet, Role* master, RoleAttr* roleAttr)->int32_t {
		// key:计算属性1,value.first:计算属性比2,value.second:结果属性
		static const std::map<int32_t, std::pair<int32_t, int32_t>> kv1 =
		{
			{(int32_t)role_base_move_speed, {(int32_t)role_base_move_speed_pct,(int32_t)role_move_speed}},
			{(int32_t)role_base_attack_speed, {(int32_t)role_base_attack_speed_pct,(int32_t)role_attack_speed}},
			{(int32_t)role_base_casting_speed, {(int32_t)role_base_casting_speed_pct,(int32_t)role_casting_speed}},
		};
		// key:计算属性比1,value.first:计算属性2,value.second:结果属性
		static const std::map<int32_t, std::pair<int32_t, int32_t>> kv2 =
		{
			{(int32_t)role_base_move_speed_pct, {(int32_t)role_base_move_speed,(int32_t)role_move_speed}},
			{(int32_t)role_base_attack_speed_pct, {(int32_t)role_base_attack_speed,(int32_t)role_attack_speed}},
			{(int32_t)role_base_casting_speed_pct, {(int32_t)role_base_casting_speed,(int32_t)role_casting_speed}},
		};
		bool beFind = false;
		std::pair<int32_t, int32_t> change{ 0,0 };
		auto iter = kv1.find(propType);
		if (iter != kv1.end())
		{
			change.second = change.first = roleAttr->Property[iter->second.second];
			roleAttr->Property[iter->second.second] = std::ceil(((double)roleAttr->Property[iter->first]) / ((double)roleAttr->Property[iter->second.first] * PRECISION + 1));
			beFind = true;
		}
		else
		{
			iter = kv2.find(propType);
			if (iter != kv2.end())
			{
				change.second = change.first = roleAttr->Property[iter->second.second];
				roleAttr->Property[iter->second.second] = std::ceil(((double)roleAttr->Property[iter->second.first]) / ((double)roleAttr->Property[iter->first] * PRECISION + 1));
				beFind = true;
			}
		}
		if (!beFind)
		{
			LOG_ERROR("[%s:%d] 更新属性错误. propType:%d", __FUNCTION__, __LINE__, propType);
			return roleAttr->Property[propType];
		}
		change.second = roleAttr->Property[iter->second.second];
        if (change.first != change.second)
		    roleAttr->PropertyMody.insert(iter->second.second);
		CallBackUpdateAttr32(master, iter->second.second, change.first, change.second);
		return roleAttr->Property[propType];
	};
	// 3.组合属性,不止一种属性的更新
	static ReCalcFunc ReCalcFunc3 = [](int32_t propType, int32_t propValue, bool beSet, Role* master, RoleAttr* roleAttr)->int32_t {
		//所有属性特殊处理
		ReCalcFunc AllPropUpdateFunc = [](int32_t propType, int32_t propValue, bool beSet, Role* master, RoleAttr* roleAttr)->int32_t {
			static const std::list<std::pair<int32_t, int32_t>> AllUpdatePropList = {
				{(int32_t)role_1000_min, (int32_t)role_1000_max},     // 1000
				{(int32_t)role_2000_min, (int32_t)role_2000_max},     // 2000
			};
			auto iter = AllUpdatePropList.begin();
			for (; iter != AllUpdatePropList.end(); ++iter)
			{
				auto prop = iter->first + 1;
				for (; prop < iter->second; ++prop)
				{
					if (beSet)
						roleAttr->SetRoleProp(prop, 1 * propValue);
					else
						roleAttr->AddRoleProp(prop, 1 * propValue);
				}
			}
			return roleAttr->Property[propType];
		};
		// 所有属性
		if (6004 == propType) return AllPropUpdateFunc(propType, propValue, beSet, master, roleAttr);
	
		if (!::GetGroupAttrProp(propType, GROUP_ATTR_PROP_GROUPINFO)) return roleAttr->Property[propType];
		luabind::iterator iter(LuaRet), end;
		for (; iter != end; iter++)
		{
			luabind::adl::object objKey = iter.key();
			luabind::adl::object objVal = *iter;
			int32_t key = luabind::object_cast<int32_t>(objKey);
			int32_t val = luabind::object_cast<int32_t>(objVal);
			if (0 == val) continue;
			if (beSet)
				roleAttr->SetRoleProp(key, val * propValue);
			else
				roleAttr->AddRoleProp(key, val * propValue);
		}
		return roleAttr->Property[propType];
	};

	static ReCalcFunc ReCalcFuncArr[] = { ReCalcFunc0 ,ReCalcFunc1, ReCalcFunc2, ReCalcFunc3 };
	static const int32_t funcCnt = _countof(ReCalcFuncArr);
	//////////////////////////////////// ReCalcFunc ////////////////////////////////////
		// first:属性类型 second:ReCalcFuncArr的下标
	static const std::map<int32_t, int32_t> ReCalcFuncMap =
	{
		// 1000
		{(int32_t)role_base_max_hp, (int32_t)ReCalcType_1},
		{(int32_t)role_base_max_mp, (int32_t)ReCalcType_1},
		{(int32_t)role_base_min_phy_def, (int32_t)ReCalcType_1},
		{(int32_t)role_base_max_phy_def, (int32_t)ReCalcType_1},
		{(int32_t)role_base_min_mag_def, (int32_t)ReCalcType_1},
		{(int32_t)role_base_max_mag_def, (int32_t)ReCalcType_1},
		{(int32_t)role_base_min_phy_atk, (int32_t)ReCalcType_1},
		{(int32_t)role_base_max_phy_atk, (int32_t)ReCalcType_1},
		{(int32_t)role_base_min_mag_atk, (int32_t)ReCalcType_1},
		{(int32_t)role_base_max_mag_atk, (int32_t)ReCalcType_1},
		{(int32_t)role_base_min_tao_atk, (int32_t)ReCalcType_1},
		{(int32_t)role_base_max_tao_atk, (int32_t)ReCalcType_1},

		{(int32_t)role_base_hp_rec, (int32_t)ReCalcType_1},
		{(int32_t)role_base_mp_rec, (int32_t)ReCalcType_1},

		{(int32_t)role_base_move_speed, (int32_t)ReCalcType_2},
		{(int32_t)role_base_attack_speed, (int32_t)ReCalcType_2},
		{(int32_t)role_base_casting_speed, (int32_t)ReCalcType_2},

		// 2000
		{(int32_t)role_base_max_hp_pct, (int32_t)ReCalcType_1},
		{(int32_t)role_base_max_mp_pct, (int32_t)ReCalcType_1},
		{(int32_t)role_base_min_phy_def_pct, (int32_t)ReCalcType_1},
		{(int32_t)role_base_max_phy_def_pct, (int32_t)ReCalcType_1},
		{(int32_t)role_base_min_mag_def_pct, (int32_t)ReCalcType_1},
		{(int32_t)role_base_max_mag_def_pct, (int32_t)ReCalcType_1},
		{(int32_t)role_base_min_phy_atk_pct, (int32_t)ReCalcType_1},
		{(int32_t)role_base_max_phy_atk_pct, (int32_t)ReCalcType_1},
		{(int32_t)role_base_min_mag_atk_pct, (int32_t)ReCalcType_1},
		{(int32_t)role_base_max_mag_atk_pct, (int32_t)ReCalcType_1},
		{(int32_t)role_base_min_tao_atk_pct, (int32_t)ReCalcType_1},
		{(int32_t)role_base_max_tao_atk_pct, (int32_t)ReCalcType_1},
		{(int32_t)role_base_hp_rec_pct, (int32_t)ReCalcType_1},
		{(int32_t)role_base_mp_rec_pct, (int32_t)ReCalcType_1},

		{(int32_t)role_base_attack_speed_pct, (int32_t)ReCalcType_2},
		{(int32_t)role_base_casting_speed_pct, (int32_t)ReCalcType_2},
		{(int32_t)role_base_move_speed_pct, (int32_t)ReCalcType_2},

		// 3000
		// 4000
		// 5000

		// 6000
		{(int32_t)role_group_1, (int32_t)ReCalcType_3},
		{(int32_t)role_group_2, (int32_t)ReCalcType_3},
		{(int32_t)role_group_3, (int32_t)ReCalcType_3},
		{(int32_t)role_group_4, (int32_t)ReCalcType_3},
		{(int32_t)role_group_5, (int32_t)ReCalcType_3},
		{(int32_t)role_group_6, (int32_t)ReCalcType_3},
		{(int32_t)role_group_7, (int32_t)ReCalcType_3},
		{(int32_t)role_group_8, (int32_t)ReCalcType_3},
		{(int32_t)role_group_9, (int32_t)ReCalcType_3},
		{(int32_t)role_group_10, (int32_t)ReCalcType_3},
		{(int32_t)role_group_11, (int32_t)ReCalcType_3},
		{(int32_t)role_group_12, (int32_t)ReCalcType_3},
		{(int32_t)role_group_13, (int32_t)ReCalcType_3},
		{(int32_t)role_group_14, (int32_t)ReCalcType_3},
		{(int32_t)role_group_15, (int32_t)ReCalcType_3},
		{(int32_t)role_group_16, (int32_t)ReCalcType_3},
		{(int32_t)role_group_17, (int32_t)ReCalcType_3},
		{(int32_t)role_group_18, (int32_t)ReCalcType_3},
		{(int32_t)role_group_19, (int32_t)ReCalcType_3},
		{(int32_t)role_group_20, (int32_t)ReCalcType_3},

		// 7000
		// 8000
		// 9000
	};
	auto iter = ReCalcFuncMap.find(prop);
	if (iter != ReCalcFuncMap.end())
	{
		after = ReCalcFuncArr[iter->second](prop, value, beSet, master, this);
	}
	return { before,after };
}

void RoleAttr::UpdateOtherStatusByProp(int32_t prop, int32_t predValue, int32_t curValue)
{
	auto master = GetMaster();
	if (nullptr == master) return;
	if (master->GetRoleState()) master->GetRoleState()->UpdateOtherStatusByProp(prop, predValue, curValue);

	if (!master->IsPlayer()) return;
	auto player = static_cast<Player*>(master);
	if (!player) return;
	if (player->GetRoleVip()) player->GetRoleVip()->UpdateOtherStatusByProp(prop, predValue, curValue);
	// other
	switch (prop)
	{
		case role_level:
		{
			auto job = GetRoleProp(role_job);
			player->OnUpgrade(sRoleConfig.Get(predValue, job), sRoleConfig.Get(curValue, job));
			player->SendUpdateTopList();
		}
		break;
	}
}

void RoleAttr::UpdateOtherStatusByProp64(int32_t prop, int64_t predValue, int64_t curValue)
{
	auto master = GetMaster();
	if (nullptr == master) return;
	if (!master->IsPlayer()) return;
	auto player = static_cast<Player*>(master);
	if (!player) return;

	player->SendRoleAttrExtRefNtfToGS(prop, curValue - predValue);
}

int32_t RoleAttr::UpdateProp(int32_t prop, int32_t value, bool beSet)
{
	auto master = GetMaster();
	if (!master) return 0;
	if (!CheckProp32KeyRange(prop)) return 0;
	if (!CheckProp32ValueLimit(prop, value, beSet)) return 0;
	if (!CheckRoleState(prop)) return 0;

	//先注释了
	auto change = ReCalcProperty(prop, value, beSet);
	int32_t& predValue = change.first;
	int32_t& curValue = change.second;

	CallBackUpdateAttr32(master, prop, predValue, curValue);

	// 更新其他状态Property
	UpdateOtherStatusByProp(prop, predValue, curValue);

    if (prop == role_hp || prop == role_base_max_hp_pct || prop == role_base_max_hp)
        CheckNeedRecoverHP(predValue, curValue);
    else if (prop == role_mp || prop == role_base_max_mp_pct || prop == role_base_max_mp)
        CheckNeedRecoverMP(predValue, curValue);
    else if (prop == role_pk)
        CheckNeedUpdatePK(predValue, curValue);

    CheckNeedUpdate();

	return value;
}

int32_t RoleAttr::SetRoleProp(int32_t prop, int32_t value)
{
	return UpdateProp(prop, value, true);
}

int32_t RoleAttr::AddRoleProp(int32_t prop, int32_t value)
{
	return UpdateProp(prop, value, false);
}

int32_t RoleAttr::GetRoleProp(int32_t prop)
{
	if (!CheckProp32KeyRange(prop)) return 0;

	return Property[prop];
}

void RoleAttr::SetProp64(int32_t prop, int64_t value, const log_params& lp)
{
	if (!CheckProp64KeyRange(prop)) return;

	AddProp64(prop, value - GetProp64(prop), lp);
}

void RoleAttr::AddProp64(int32_t prop, int64_t value, const log_params& lp)
{
	auto master = GetMaster();
	if (!master) return;
	if (!(CheckProp64KeyRange(prop))) return;

	auto befVal = Property64[prop];
	Property64[prop] += value;
	auto aftVal = Property64[prop];
    if (befVal != aftVal) PropertyMody64.insert(prop);

	if (aftVal != befVal && LuaHost::GetInstance()->IsCallBackUpdateAttr(prop, false))
	{
		TRIGGER_EVENT(trigger_role_update_attr, master->GetGUIDAsString(), prop, 0, std::to_string(befVal), std::to_string(aftVal));
	}

	UpdateOtherStatusByProp64(prop, befVal, Property64[prop]);

    CheckNeedUpdate();

	if (LOG_PARAMS_INFO_INIT != lp.info)
	{
		SendDBLogData(log_type_currency_change, LogCurrencyChange(master->GetGUID(), prop, befVal, value, Property64[prop], 0, lp.info));
	}
}

int64_t RoleAttr::GetProp64(int32_t prop)
{
	if (!(CheckProp64KeyRange(prop))) return 0;

    return Property64[prop];
}

void RoleAttr::SetRolePos(uint16_t x, uint16_t y, bool raiseEvent,bool takeGrid)
{
    auto master = GetMaster();
	if (nullptr == master) {
		return;
	}
	if (master->IsInvalid()) {
		return;
	}
    master->ReleaseGrid();
	uint16_t old_x = PosX;
	uint16_t old_y = PosY;
	PosX = x;
	PosY = y;

	if (raiseEvent) {
		auto map = master->GetCurMap();
		bool movereturn = true;
		if (nullptr != map) {
			movereturn = map->RoleMove(master,old_x,old_y);
		}
		if (!movereturn)
		{
			PosX = old_x;
			PosY = old_y;
		}
	}

	if (takeGrid)
	{
		master->TakeGrid();
	}
}

void RoleAttr::RecoveryProperty(int32_t delta)
{	
	if (nullptr == mMaster) return;
	auto map = mMaster->GetCurMap();
	if (!map) return;

	// npc不需要回血
	if (mMaster->IsNpc()) return;
	// 默认3秒
	CurRecoveryInterval += delta;
	if (CurRecoveryInterval < RecoveryIntervalTime) return;

	CurRecoveryInterval -= RecoveryIntervalTime;

	//bool beSafeArea = map->IsSafeRegion(PosX, PosY);
	static const std::vector<std::pair<int32_t, int32_t>> recProp =
	{
		{(int32_t)role_hp, (int32_t)role_hp_rec},			/// 安全区hp回复值
		{(int32_t)role_mp, (int32_t)role_mp_rec},			/// 安全区mp回复值
		// 其他属性
	};
	std::vector<std::pair<int32_t, int32_t>>::const_iterator iter, end;
	iter = recProp.begin();
	end = recProp.end();
	std::map<int32_t, int32_t> propDiff =
	{
		{(int32_t)role_hp, (int32_t)0},
		{(int32_t)role_mp, (int32_t)0},
	};
	while (iter != end)
	{
		propDiff[iter->first] += AddRoleProp(iter->first, GetRoleProp(iter->second));
		iter++;
	}

	if (!mMaster->IsPlayer()) return;
	int32_t& hpDiff = propDiff[role_hp];
	int32_t& mpDiff = propDiff[role_mp];
	if (!hpDiff && !mpDiff) return;

	auto player = static_cast<Player*>(mMaster);
	if (!player) return;
	player->SendPlayerShowNtf(hpDiff, mpDiff);
}

bool RoleAttr::CheckProp32ValueLimit(int32_t curProp, int32_t &value, bool beSet)
{
	bool beNegative = false;		// 是否可以为负数
	// 计算上限的属性集合
	static std::map<int32_t, int32_t> kv =
	{
		{(int32_t)role_hp, (int32_t)role_max_hp},
		{(int32_t)role_mp, (int32_t)role_max_mp},
	};
	auto iter = kv.find(curProp);
	if (iter == kv.end()) return true;

	auto curValue = GetRoleProp(curProp);
	auto maxValue = GetRoleProp(iter->second);
	// 重置数据
	if (beSet)
	{
		if (value > 0)
		{
			(value > maxValue) ? value = maxValue : 1; 
		}
		else if(value < 0)
		{
			!beNegative ? value = 0 : 1;
		}
	}
	else
	{
		if (value > 0)
		{
			(curValue + value > maxValue) ? value = maxValue - curValue : 1;
		}
		else if (value < 0)
		{
			!beNegative ? value = -1 * std::min<int>(std::abs(curValue), std::abs(value)) : 1;
		}
		return value != 0;
	}
	return true;
}

bool RoleAttr::CheckRoleState(int32_t prop)
{
	auto master = GetMaster();
	if (nullptr == master) return false;

	static std::set<int32_t> attrMap{ role_hp, role_mp };
	// 死亡 并且 是hp\mp 不加
	if (!master->CheckAlive())
	{
		bool res = attrMap.find(prop) == attrMap.end();
		return res;
	}
	return true;
}

bool RoleAttr::CheckProp32KeyRange(int32_t prop)
{
	return (prop > role_attr_min && prop < role_attr_max);
}

bool RoleAttr::CheckProp64KeyRange(int32_t prop)
{
	return (prop >= role_attr_ext_min && prop <= role_attr_ext_max);
}

void RoleAttr::CheckNeedRecoverHP(int32_t preValue, int32_t curValue)
{
    if (GetRoleProp(role_hp_rec) == 0) {
        mNeedRecoverHP = false;
        return;
    }

    if (curValue == 0) {                    // 死亡不需要恢复
        mNeedRecoverHP = false;
    }
    else if (curValue < preValue) {         // 血量减少需要恢复
        mNeedRecoverHP = true;
    }
    else {
        auto maxhp = GetRoleProp(role_max_hp);
        if (curValue == maxhp)
            mNeedRecoverHP = false;
        else
            mNeedRecoverHP = true;
    }
}

void RoleAttr::CheckNeedRecoverMP(int32_t preValue, int32_t curValue)
{
    if (GetRoleProp(role_mp_rec) == 0) {
        mNeedRecoverMP = false;
        return;
    }

    if (curValue < preValue) {              // 蓝量减少需要恢复
        mNeedRecoverMP = true;
    }
    else {
        auto maxmp = GetRoleProp(role_max_mp);
        if (curValue == maxmp)
            mNeedRecoverMP = false;
        else
            mNeedRecoverMP = true;
    }
}

void RoleAttr::CheckNeedUpdatePK(int32_t preValue, int32_t curValue)
{
    auto *self = GetMaster();
    if (!self || !self->IsPlayer()) return;

    if (curValue == 0)
        self->ResetNeedUpdateFlag(player_pk_need_update_flag);
    else
        self->SetNeedUpdateFlag(player_pk_need_update_flag);
}

void RoleAttr::CheckNeedUpdate()
{
    if (mNeedRecoverHP || mNeedRecoverMP || PropModified())
        SetNeedUpdate(attr_need_update_flag);
    else
        ResetNeedUpdate(attr_need_update_flag);
}

bool RoleAttr::PropModified()
{
    return (!PropertyMody.empty() || !PropertyMody64.empty() || mDynAttrsMody);
}
