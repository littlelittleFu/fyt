#pragma once

#include <string.h>
#include "RoleItem.h"
#include "Role.h"

class SceneItem : public RoleItem
{
public:
	SceneItem();
	SceneItem(const RoleItem& item);
	SceneItem(const RoleItem* item);
	SceneItem(const SceneItem& item);
	SceneItem(const SceneItem* item);
	 ~SceneItem();

	 void SetPosY(unsigned short  mount) { mPosy = mount; }
	 unsigned short  GetPosY() const { return mPosy; }


	void SetPosX(unsigned short  mount) { mPosx = mount; }
	unsigned short  GetPosX() const { return mPosx; }

	void SetSkillID(unsigned int   mount) { mSkillID = mount; }
	unsigned int    GetSkillID() const { return mSkillID; }

	//物品是否能被某个角色拾取
	bool IsCanPickup(Role* role);
	int IsCanPickupWithErr(Role* role);

	void SetIsDrop(uint16_t drop) { mIsDrop = drop; }
	uint16_t GetIsDrop() const { return mIsDrop; }

    void SetDropBy(uint64_t dropBy) { mDropBy = dropBy; }
    uint64_t GetDropBy() { return mDropBy; }

	void SetOwnerGUID(uint64_t guid) { mOwnerGUID = guid; }
	uint64_t GetOwnerGUID() { return mOwnerGUID; }
	void SetOwnerTeamGUID(uint64_t guid) { mOwnerTeamGUID = guid; }
	uint64_t GetOwnerTeamGUID() { return mOwnerTeamGUID; }

	void SetExistingMapName(const std::string& mapName) { mExistingMapName = mapName; }
	std::string GetExistingMapName() { return mExistingMapName; }

    uint64_t GetCreationTime() { return mCreationTime; }

protected:
	void InitWithSceneItem(const SceneItem* item);
	void InitTimer();

protected:
	unsigned short			  mPosx = 0;
	unsigned short            mPosy = 0;
	unsigned int              mSkillID = 0; 
	uint16_t				  mIsDrop = 1;
    uint64_t                  mDropBy = 0;
	uint64_t				  mOwnerGUID = 0;
	uint64_t				  mOwnerTeamGUID = 0;
	uint32_t				  mDisAppearTimerID = 0;
	uint32_t				  mResetOwnerTimerID = 0;
	std::string				  mExistingMapName;
    uint64_t                  mCreationTime = 0;
};


