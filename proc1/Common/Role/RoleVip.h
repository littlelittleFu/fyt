#pragma once

#include "RoleAction.h"
#include "vip_table.hpp"
#include "GameMall.h"

#define RoleVipLevelAmount	20
enum Role_VipLevel
{
	role_vip_level_none = 0,											//��Ч�ȼ�
	role_vip_level_1 = 1,											//�ȼ�1
	role_vip_level_min = role_vip_level_1,							//��͵ȼ�
	role_vip_level_max = role_vip_level_none + RoleVipLevelAmount,	//���ȼ�
};

enum Role_VipExtePermissions
{
	role_vip_exteperm_none = 0,						// ��Ч��Ȩ
	role_vip_exteperm_1,							// ��Ȩ1
	role_vip_exteperm_2,							// ��Ȩ2
	role_vip_exteperm_3,							// ��Ȩ3
	role_vip_exteperm_4,							// ��Ȩ4
	role_vip_exteperm_5,							// ��Ȩ5
	role_vip_exteperm_6,							// ��Ȩ6
	role_vip_exteperm_7,							// ��Ȩ7
	role_vip_exteperm_8,							// ��Ȩ8
	role_vip_exteperm_9,							// ��Ȩ9
	role_vip_exteperm_10,							// ��Ȩ10
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
	int32_t mCurVipLevel = 0;	// ��ǰvipLevel
};
