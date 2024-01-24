#pragma once

#include "RoleAction.h"
#include "vip_table.hpp"
#include "GameMall.h"

#define RoleVipLevelAmount	20
enum Role_VipLevel
{
	role_vip_level_none = 0,											//无效等级
	role_vip_level_1 = 1,											//等级1
	role_vip_level_min = role_vip_level_1,							//最低等级
	role_vip_level_max = role_vip_level_none + RoleVipLevelAmount,	//最大等级
};

enum Role_VipExtePermissions
{
	role_vip_exteperm_none = 0,						// 无效特权
	role_vip_exteperm_1,							// 特权1
	role_vip_exteperm_2,							// 特权2
	role_vip_exteperm_3,							// 特权3
	role_vip_exteperm_4,							// 特权4
	role_vip_exteperm_5,							// 特权5
	role_vip_exteperm_6,							// 特权6
	role_vip_exteperm_7,							// 特权7
	role_vip_exteperm_8,							// 特权8
	role_vip_exteperm_9,							// 特权9
	role_vip_exteperm_10,							// 特权10
};
class RoleVip : public RoleAction
{
public:
	RoleVip(Role* master = nullptr);
	~RoleVip();

public:
	bool Init() override;
	void Update(int32_t delta) override;

	void UpdateOtherStatusByProp(int32_t prop, int32_t predValue, int32_t curValue);
	static bool CheckVipInfo(int32_t vipLevel, Role* master);
	bool HasExtePermissions(int32_t ep);
	std::set<int32_t>	GetExtePermissions();
protected:
    DATA::Vip * GetCurVipConfig();
	void HandleUpdateVip(int32_t vipLevel);
	void UpdateVipPrivilege(DATA::Vip* vipConfig);
	void OnUpdateMallLimitData();
	void OnUpdateBasicProp(DATA::Vip* vipConfig);
	void OnUpdateSpecialProp(DATA::Vip* vipConfig);
	void OnUpdateAddSkill(DATA::Vip* vipConfig);
	void OnUpdateExtePermissions(DATA::Vip* vipConfig);
	void OnUpdateBuff(DATA::Vip* vipConfig);
	void OnTriggerScript(DATA::Vip* vipConfig);
private:
	int32_t mCurVipLevel = 0;	// 当前vipLevel
};
