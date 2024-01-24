#include "stdafx.h"
#include "RoleVip.h"
#include "Player.h"

RoleVip::RoleVip(Role* master) : RoleAction(master)
{
}

RoleVip::~RoleVip()
{

}

bool RoleVip::Init()
{
    auto *self = GetMaster();
    if (self && self->IsPlayer()) {
        mCurVipLevel = self->GetRoleProp(role_vip_level);
    }

    return true;
}

DATA::Vip * RoleVip::GetCurVipConfig()
{
    return sVipConfig.Get(mCurVipLevel);
}

void RoleVip::Update(int32_t delta)
{
	
}
// 更新vip相关属性
void RoleVip::UpdateOtherStatusByProp(int32_t prop, int32_t predValue, int32_t curValue)
{
	switch (prop)
	{
		case role_vip_level: HandleUpdateVip(curValue);  break;
	}
}

void RoleVip::HandleUpdateVip(int32_t vipLevel)
{
	if (!RoleVip::CheckVipInfo(vipLevel, GetMaster())) return;
	if (mCurVipLevel == vipLevel) return;

	auto mVipConfig = sVipConfig.GetByID(vipLevel);
	UpdateVipPrivilege(mVipConfig);
    mCurVipLevel = vipLevel;
}

void RoleVip::OnUpdateMallLimitData()
{
	if (!mMaster)return;
	auto viplevel = mMaster->GetRoleProp(role_vip_level);
	GameMall::GetInstance()->UpdateLimitNumWhenVipUp(mMaster->GetGUID(),viplevel);
}

void RoleVip::UpdateVipPrivilege(DATA::Vip* vipConfig)
{
	OnUpdateMallLimitData();
	OnUpdateBasicProp(vipConfig);
	OnUpdateSpecialProp(vipConfig);
	OnUpdateAddSkill(vipConfig);
	OnUpdateExtePermissions(vipConfig);
	OnUpdateBuff(vipConfig);
	OnTriggerScript(vipConfig);
}

void RoleVip::OnUpdateBasicProp(DATA::Vip* vipConfig)
{
	if (nullptr == vipConfig) return;
	auto master = GetMaster();
	if (nullptr == master) return;
	auto roleAttr = master->GetRoleAttr();
	if (nullptr == roleAttr) return;
	// 配置是最终值
    auto *curVipConfig = GetCurVipConfig();
	if (curVipConfig && !curVipConfig->basicProp.empty())
	{
		auto iter = curVipConfig->basicProp.begin();
		for (; iter != curVipConfig->basicProp.end(); ++iter)
		{
			roleAttr->AddRoleProp(iter->first, -1 * iter->second);
		}
	}
	if (vipConfig && !vipConfig->basicProp.empty())
	{
		auto iter = vipConfig->basicProp.begin();
		for (; iter != vipConfig->basicProp.end(); ++iter)
		{
			roleAttr->AddRoleProp(iter->first, iter->second);
		}
	}
}

void RoleVip::OnUpdateSpecialProp(DATA::Vip* vipConfig)
{
	if (nullptr == vipConfig) return;
	auto master = GetMaster();
	if (nullptr == master) return;
	auto roleAttr = master->GetRoleAttr();
	if (nullptr == roleAttr) return;
	// 配置是最终值
    auto *curVipConfig = GetCurVipConfig();
	if (curVipConfig && !curVipConfig->specialProp.empty())
	{
		auto iter = curVipConfig->specialProp.begin();
		for (; iter != curVipConfig->specialProp.end(); ++iter)
		{
			roleAttr->AddRoleProp(iter->first, -1 * iter->second);
		}
	}
	if (vipConfig && !vipConfig->specialProp.empty())
	{
		auto iter = vipConfig->specialProp.begin();
		for (; iter != vipConfig->specialProp.end(); ++iter)
		{
			roleAttr->AddRoleProp(iter->first, iter->second);
		}
	}
}

void RoleVip::OnUpdateAddSkill(DATA::Vip* vipConfig)
{
	if (nullptr == vipConfig) return;
	auto master = GetMaster();
	if (!master || !master->IsPlayer()) return;

	Player* player = static_cast<Player*>(master);

	if (!vipConfig->addSkill.empty())
	{
		auto iter = vipConfig->addSkill.begin();
		for (; iter != vipConfig->addSkill.end(); ++iter)
		{
			player->AddSkill(*iter, true);
		}
	}
}

void RoleVip::OnUpdateExtePermissions(DATA::Vip* vipConfig)
{
	if (nullptr == vipConfig) return;
	auto master = GetMaster();
	if (nullptr == master) return;
}

void RoleVip::OnUpdateBuff(DATA::Vip* vipConfig)
{
	if (nullptr == vipConfig) return;
	auto master = GetMaster();
	if (nullptr == master) return;
	// 配置是最终值
    auto *curVipConfig = GetCurVipConfig();
	if (curVipConfig && !curVipConfig->buffId.empty())
	{
		auto iter = curVipConfig->buffId.begin();
		for (; iter != curVipConfig->buffId.end(); ++iter)
		{
			master->RemoveBuff(*iter);
		}
	}
	if (vipConfig && !vipConfig->buffId.empty())
	{
		auto iter = vipConfig->buffId.begin();
		for (; iter != vipConfig->buffId.end(); ++iter)
		{
			master->AddBuffByRole(*iter, master, 0);
		}
	}
}

void RoleVip::OnTriggerScript(DATA::Vip* vipConfig)
{
	if (nullptr == vipConfig) return;
	auto master = GetMaster();
	if (nullptr == master) return;

	std::string scriptName(vipConfig->script);
	if (scriptName.empty() || scriptName == "0") return;

	scriptName += ".main";
	LuaBindCallVoid(scriptName, master->GetGUIDAsString(), vipConfig->vipLevel);
}

bool RoleVip::CheckVipInfo(int32_t vipLevel, Role* master)
{
	if (!master || !master->IsPlayer()) return false;
	if (vipLevel < role_vip_level_min || vipLevel > role_vip_level_max) return false;

	auto vipConfig = sVipConfig.GetByID(vipLevel);
	if (nullptr == vipConfig) return false;

	return true;
}

bool RoleVip::HasExtePermissions(int32_t ep)
{
    auto *curVipConfig = GetCurVipConfig();
	if (nullptr == curVipConfig)  return false;
	if (curVipConfig->extePermissions.empty()) return false;
	return std::find(curVipConfig->extePermissions.begin(), 
        curVipConfig->extePermissions.end(), ep) != curVipConfig->extePermissions.end();
}

std::set<int32_t> RoleVip::GetExtePermissions()
{
    auto *curVipConfig = GetCurVipConfig();
	if (nullptr == curVipConfig)  return std::set<int32_t>();
	return curVipConfig->extePermissions;
}