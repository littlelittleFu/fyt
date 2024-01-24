#pragma once
#include "RoleAction.h"

class RoleTeam : public RoleAction
{
public:
	RoleTeam(Role* master = nullptr);
	~RoleTeam();

	bool Init() override;
	void Update(int32_t delta) override;

	void Clear();
	void SetTeamGUID(uint64_t guid);
	uint64_t GetTeamGUID();

protected:
	uint64_t mTeamGUID = 0;

};
