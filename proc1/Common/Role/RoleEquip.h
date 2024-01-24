#pragma once
#include "RoleAction.h"

class Role;
class RoleEquip : public RoleAction
{
public:
	RoleEquip(Role* master = nullptr);
	~RoleEquip();

public:
	bool Init() override;
	void Update(int32_t delta) override;

};
