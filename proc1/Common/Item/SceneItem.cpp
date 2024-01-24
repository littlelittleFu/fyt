#include "stdafx.h"
#include "SceneItem.h"
#include "ITimeHelper.h"
#include "MapMgr.h"
#include "ItemMap.h"

SceneItem::SceneItem()
{
    mCreationTime = GetTimeStampMillisecond2();
	InitTimer();
    SetCategory(item_cat_scene);
}

SceneItem::~SceneItem()
{
	if (mDisAppearTimerID != 0) {
		ITimeHelper::GetInstance()->RemoveTimer(mDisAppearTimerID);
		mDisAppearTimerID = 0;
	}

	if (mResetOwnerTimerID != 0) {
		ITimeHelper::GetInstance()->RemoveTimer(mResetOwnerTimerID);
		mResetOwnerTimerID = 0;
	}
}

SceneItem::SceneItem(const RoleItem& item) : RoleItem(item)
{
	mPosx = 0;
	mPosy = 0;
	mSkillID = 0;
	mIsDrop = 0;
    mCreationTime = GetTimeStampMillisecond2();
	InitTimer();
    SetCategory(item_cat_scene);
}

SceneItem::SceneItem(const RoleItem* item) : RoleItem(item)
{
	mPosx = 0;
	mPosy = 0;
	mSkillID = 0;
	mIsDrop = 0;
    mCreationTime = GetTimeStampMillisecond2();
	InitTimer();
    SetCategory(item_cat_scene);
}

SceneItem::SceneItem(const SceneItem& item) : RoleItem(item)
{
    mCreationTime = GetTimeStampMillisecond2();
	InitWithSceneItem(&item);
    SetCategory(item_cat_scene);
}

SceneItem::SceneItem(const SceneItem* item) : RoleItem(item)
{
    mCreationTime = GetTimeStampMillisecond2();
	InitWithSceneItem(item);
    SetCategory(item_cat_scene);
}

void SceneItem::InitWithSceneItem(const SceneItem* item)
{
	if (nullptr == item) {
		return;
	}

	mPosx = item->GetPosX();
	mPosy = item->GetPosY();
	mSkillID = item->GetSkillID();
	mIsDrop = item->GetIsDrop();
	InitTimer();
}

bool SceneItem::IsCanPickup(Role* role)
{
	if (nullptr == role) {
		return false;
	}

    if (role->IsPlayer()) {
        //只有队友或者自己可以拾取
        if (mOwnerTeamGUID > 0 && role->GetRoleTeam()->GetTeamGUID() != mOwnerTeamGUID) {
            return false;
        }

        if (mOwnerTeamGUID == 0 && mOwnerGUID > 0 && mOwnerGUID != role->GetGUID()) {
            return false;
        }

        return true;
    }
    else if (role->IsMonster() || role->IsPet()) {

        auto *monster = static_cast<Monster *>(role);
        auto masterGUID = monster->GetMasterGUID();

        if (GetDropBy() == masterGUID) return false;    // 被丢弃不捡

        auto *player = MapRoleMgr::GetInstance()->FindPlayer(masterGUID);
        if (!player) return false;

        if (mOwnerTeamGUID > 0 && player->GetRoleTeam()->GetTeamGUID() != mOwnerTeamGUID) {
            return false;
        }

        if (mOwnerTeamGUID == 0 && mOwnerGUID > 0 && mOwnerGUID != masterGUID) {
            return false;
        }

        return true;
    }
    else {
        return false;
    }
}

int SceneItem::IsCanPickupWithErr(Role* role)
{
    if (nullptr == role) {
        return ERR_ITEM_PICKUP;
    }

    if (role->IsPlayer()) {
        //只有队友或者自己可以拾取
        if (mOwnerTeamGUID > 0 && role->GetRoleTeam()->GetTeamGUID() != mOwnerTeamGUID) {
            return ERR_ITEM_PICKUP_TEAM;
        }

        if (mOwnerTeamGUID == 0 && mOwnerGUID > 0 && mOwnerGUID != role->GetGUID()) {
            return ERR_ITEM_PICKUP_OWNER;
        }

        return ERR_OK;
    }
    else if (role->IsMonster() || role->IsPet()) {

        auto* monster = static_cast<Monster*>(role);
        auto masterGUID = monster->GetMasterGUID();

        if (GetDropBy() == masterGUID) return ERR_ITEM_PICK_UP_DROPED;    // 被丢弃不捡

        auto* player = MapRoleMgr::GetInstance()->FindPlayer(masterGUID);
        if (!player) return ERR_ITEM_PICKUP;

        if (mOwnerTeamGUID > 0 && player->GetRoleTeam()->GetTeamGUID() != mOwnerTeamGUID) {
            return ERR_ITEM_PICKUP_TEAM;
        }

        if (mOwnerTeamGUID == 0 && mOwnerGUID > 0 && mOwnerGUID != masterGUID) {
            return ERR_ITEM_PICKUP_OWNER;
        }

        return ERR_OK;
    }
    else {
        return ERR_ITEM_PICKUP;
    }
}

void SceneItem::InitTimer()
{
	///////////////////////////////////////////////////////////////////////////////////
	//配置物品的专属时间
	TimerData timer;
	auto global = sGlobalConfig.GetData();
	timer.interval = global->SceneItemSurvivalTime;
	timer.loop = false;
	timer.callBack = [this](const TimerData&) {
		mResetOwnerTimerID = 0;

        if (mOwnerGUID == 0 && mOwnerTeamGUID == 0) return;

		mOwnerGUID = 0;
		mOwnerTeamGUID = 0;

        auto *map = MapMgr::GetInstance()->FindMap(mExistingMapName);
        if (!map) return;

        ProtoMS_SceneItemUpdateNtf data;
        data.item_guid = GetGUID();

        auto f = [&] (Role *role) {
            if (!role || !role->IsPlayer()) return;
            const auto *player = static_cast<Player *>(role);
            data.clsessid = player->GetClSessionID();
            SendDataBySessionID(player->GetGsSessionID(), data);
        };

        auto x = GetPosX();
        auto y = GetPosY();

        map->ApplyFuncToAllPlayersInAroundRegions(x, y, f);
	};
	mResetOwnerTimerID = ITimeHelper::GetInstance()->AddTimer(timer,true);
    //ITimeHelper::GetInstance()->AddStrData(mResetOwnerTimerID, "name", "ResetOwner");

	///////////////////////////////////////////////////////////////////////////////////
	//配置物品的消失时间
	timer.interval = global->SceneItemDeadTime;
	timer.loop = false;
	timer.callBack = [this](const TimerData&) {
		mDisAppearTimerID = 0;
		if (mResetOwnerTimerID > 0) {
			ITimeHelper::GetInstance()->RemoveTimer(mResetOwnerTimerID);
			mResetOwnerTimerID = 0;
		}
		auto map = MapMgr::GetInstance()->FindMap(mExistingMapName);
		if (nullptr != map) {
			map->DestroySceneItem(GetGUID(), GetPosX(), GetPosY());
		}
	};
	mDisAppearTimerID = ITimeHelper::GetInstance()->AddTimer(timer,true);
    //ITimeHelper::GetInstance()->AddStrData(mDisAppearTimerID, "name", "DisAppear");
}
