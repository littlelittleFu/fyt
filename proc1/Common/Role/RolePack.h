#pragma once
#include "RoleAction.h"
#include "RoleItem.h"
#include "item_table.hpp"
#include "ProtoCS.h"
#include "SuitCounter.h"


struct ItemParam
{
    uint16_t        nItemID = 0;
    int32_t         nNum    = 0;
    bind_type       nBind   = bind_nullptr;

    ItemParam(uint16_t _nItemID, int32_t _nNum, bind_type _nBind)
        : nItemID(_nItemID), nNum(_nNum), nBind(_nBind) {}
};

struct UpdateParam
{
    bool beWear = false;
    uint64_t targetGuid = 0;
    uint32_t num = 0;
    uint16_t site = 0;
    std::string reason = "";
};

using ItemParams = std::vector<ItemParam>;

class SceneItem;

class RolePack : public RoleAction
{
public:
    RolePack(Role* master = nullptr);
    ~RolePack();

public:
    bool Init() override;
    void Update(int32_t delta) override;
    void CopyFromOwner(RoleAction* ra) override;
public:
    uint16_t GetEquipSiteByType(int32_t type);
    uint16_t GetItemSite(const uint64_t itemGUID);
    uint16_t GetItemSiteInEquip(const uint64_t itemGUID);
    uint16_t GetItemSiteInBag(const uint64_t itemGUID);
    uint16_t GetItemSiteInWareHouse(const uint64_t itemGUID);
    uint16_t GetItemSiteInAdvWareHouse(const uint64_t itemGUID);
    uint16_t GetIdleBagSite();
    uint16_t GetIdleBagCount();
    uint16_t GetTotalBagCount();
    bool IsCanUseEquipSiteByType(uint32_t type,uint32_t site);
    bool IsItemExist(const uint64_t itemGUID);
    bool IsItemExistInEquip(const uint64_t itemGUID);
    bool IsItemExistInBag(const uint64_t itemGUID);
    bool IsItemExistInWareHouse(const uint64_t itemGUID);
    bool IsItemExistInAdvWareHouse(const uint64_t itemGUID);
    uint16_t AddItemToBag(uint16_t tempID, const log_params& lp);
    uint16_t AddItemToBag(RoleItem& item, const log_params& lp);
    uint16_t AddItemToBag(RoleItem* item, const log_params& lp);
    bool AddItem(const ITEM_INFO& item, const log_params& lp);
    bool AddItem(const ITEM_INFO* item, const log_params& lp);
    int AddItem(uint16_t nTemplateID, uint16_t nNum, bind_type nBind, site_range nSiteRange, const log_params& lp);
    int AddItemByKeyName(const std::string &sKeyName, uint16_t nNum, uint8_t bBind, uint8_t nJob, uint16_t nSite, site_range nSiteRange, const log_params& lp);
    uint64_t AddSingleItem(uint16_t nTemplateID, uint16_t nNum, bind_type nBind, const log_params& lp);
    int AddItems(const CLuaObject &luaObj, site_range nSiteRange, const log_params& lp);
    int RemoveItem(uint16_t nTemplateID, uint16_t nNum, uint8_t bindRequire, site_range nSiteRange, const log_params& lp);
    int RemoveItem(const uint64_t itemGuid, uint16_t nNum, const log_params& lp);
    void RemoveItem(uint16_t site, const log_params& lp);
    int RemoveAllItem(rolepack_opt_type type);
    int CanAddItems(const ItemParams &items, site_range nSiteRange = site_range_bag);
    int CanRemoveItems(const ItemParams &items, site_range nSiteRange = site_range_bag);
    int AddItems(const ItemParams &items, site_range nSiteRange, const log_params& lp);
    int RemoveItems(const ItemParams &items, site_range nSiteRange, const log_params& lp);
    RoleItem* FindItem(const uint64_t itemGUID);
    RoleItem* FindItemInEquip(const uint64_t itemGUID);
    RoleItem* FindItemInBag(const uint64_t itemGUID);
    RoleItem* FindItemInWareHouse(const uint64_t itemGUID);
    RoleItem* FindItemInAdvWareHouse(const uint64_t itemGUID);
    uint32_t GetItemNum(uint16_t nItemTemplateID, uint8_t bindRequire = bind_require_any, site_range siteRange = site_range_bag);
    void ClearAllItems();
    const std::vector<RoleItem*>& GetItemList(void) { return mItemList; };
    RoleItem * GetItem(uint16_t nSite);
    std::vector<RoleItem *> GetAllEquipments();
    void OnRecvItemFromCS(ProtoCS_SendItemNtf& ntf);
    int UseItem(uint64_t itemGUID, uint32_t num);
    int MoveItem(const uint64_t fromItemGUID, uint16_t toSite);
    int SplitItem(uint64_t guid, uint16_t amount, uint16_t site);
    int DropItem(uint64_t itemGUID);
    void Arrange(uint16_t start, uint16_t end);
    int ItemArrange(unsigned char type);
    int PickUpItem();
    int PickUpItem(SceneItem *item);
    int AutoPickupItem(const Point *pos, uint8_t num);

    void GetSiteRange(site_range nSiteRange, int &nSiteBegin, int &nSiteEnd);
    bool IsInSiteRange(uint16_t nSite, site_range nSiteRange);

    uint16_t GetItemID(uint16_t site);

    bool OnUpdateUseItem(uint16_t id, UpdateParam& up);
    uint64_t GetItemGuidBySite(uint32_t site);

    bool SetAmount(const std::string &guid, uint32_t num, const log_params& lp);
    void SetDynAttr(uint16_t site, uint16_t index, uint16_t attr, int32_t value);
    void OnRecvItemCustVarList(CUST_VAR_SP_LIST& var)
    {
        mCustVarList.insert(mCustVarList.end(), var.begin(), var.end());
    }
    void OnRecvItemDynAttrsList(ITEM_DYN_ATTRS_LIST& var)
    {
        mDybAttrsList.insert(mDybAttrsList.end(), var.begin(), var.end());
    }

    bool SetItemCfg(uint64_t guid, const CLuaObject& tab);
    bool CheckWearEquipSite(uint16_t site);
    void SetAutoStack(bool b);

    void CalcDropItems(uint64_t killerGUID);
    void DropItemByDropProcess(uint16_t type, uint64_t killerGUID = 0);

    void GetItemList(CLuaObject& list,uint16_t min, uint16_t max);
protected:
    // item¸üÐÂ
    bool OnUpdateEquipItem(uint16_t id, const UpdateParam& up);
    bool OnUpdateConsumabItem(uint16_t id, UpdateParam& up);
    bool OnUpdateFinitebItem(uint16_t id, UpdateParam& up);
    bool OnUpdateScriptItem(uint16_t id, const UpdateParam& up);

    int OnTriggerScript(uint16_t id, const UpdateParam& up);
    void OnUpdateItemProp(uint16_t id, const UpdateParam& up);
    void OnUpdateEquipProp(uint16_t id, const UpdateParam& up);
    void OnUpdateRoleProp(uint16_t id, const UpdateParam& up);
    void OnUpdateRolePropBySuit(uint16_t id, const UpdateParam &up);
    void OnTriggerEffect(uint16_t id, const UpdateParam& up);

    int DoUseEquip(int16_t site);
    int DoUseItem(int16_t site, uint32_t num);
public:
    void NtfMasterAddItem(uint16_t site, bool isPackItem = true);
    void NtfMasterUpdateItem(uint16_t site);
    void NotifyAroundPlayers_PickupItem(SceneItem *item);

protected:
    void OnAddItem(uint16_t nSite, const log_params& lp);
    void OnRemoveItem(uint16_t nSite, const log_params& lp);
    void OnUpdateItem(uint16_t nSite, int32_t nNum, int32_t bef, const log_params& lp);
    void OnSwapItem(uint16_t nSite1, uint16_t nSite2, const log_params& lp);
    void OnUseEquip(uint16_t site, uint16_t toSite);
    void OnUnloadEquip(uint16_t site, uint16_t toSite);

    void UpdateEquipBySite(uint16_t site);

    int32_t CheckSite(DATA::Item*, uint16_t);
protected:
    void InitItemCustVarList(uint64_t guid);
    void InitItemDynAttrsList(uint64_t guid);
    void InitEquipUpdateProp();
    RoleItem* GenerateRoleItemByItemCfg(DATA::Item* itemCfg, int16_t site);
    RoleItem* GenerateRoleItemByRoleItem(RoleItem* item, int16_t site);

private:
    int AutoPickupItem(uint16_t x, uint16_t y);
    int AutoPickupItem(SceneItem *item);

private:
    std::vector<RoleItem*> mItemList;

    CUST_VAR_SP_LIST mCustVarList;
    ITEM_DYN_ATTRS_LIST mDybAttrsList;

    time_t                  mLastAutoPickTime   = 0;
    bool                    mBeAutoStack = false;

    SuitCounter             mSuitCounter;
};
