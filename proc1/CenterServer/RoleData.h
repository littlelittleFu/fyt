#pragma once
#include <list>

#include <memory>
#include <vector>
#include"ProtoCS.h"
#include"ProtoMS.h"
#include"Title.h"

class RoleData
{
public:
	RoleData();
	~RoleData();
	
	void SetInitialized(bool val) { mInitialized = val; }
	bool IsInitialized() { return mInitialized; };

	void SetBriefInfo(const ROLE_BRIEF_INFO& briefInfo) { mBriefInfo = briefInfo; }
	ROLE_BRIEF_INFO& GetBriefInfo() { return mBriefInfo; }

	void AddItem( std::unique_ptr<ITEM_INFO>& item);
	void DelItem(const uint64_t itemGUID);
	void ClearItem();
	ITEM_INFO* GetItem(const uint64_t itemGUID);
	std::list<std::unique_ptr<ITEM_INFO>>& GetItemList() { return mItemList; }

	QUICK_BAR_INFO* GetQuickBarSet(const unsigned char mslot);
	void AddBar(QUICK_BAR_INFO& item);
	unsigned short GetQuickBarSetNtfNum() { return (unsigned short)mQuickBarSetInfo.size(); };
	void GetQuickBarSetNtfInfo(QUICK_BAR_INFO* info,unsigned short num);
	void syncQuickBarSetNtf(QUICK_BAR_INFO* info, unsigned short num);


	void AddTmpDgnBindInfo(DGN_BIND_INFO& info);
	void SwapDgnBindInfoList();
	const DGN_BIND_INFO_LIST& GetDgnBindInfoList() { return mDgnBindInfo; }
	void syncDgnBindInfoNtf(DGN_BIND_INFO* info, uint16_t num);

    void SetSkillList(const SKILL_INFO *pSkillInfo, uint16_t num);
	std::list<SKILL_INFO>& GetSkillList() { return mSkillList; };

	std::string& GetInfo(void) { return info; };
	void SetInfo(const std::string& str) { info = str; };

	std::vector<BUFF_INFO_DB>& GetBuffList() { return mBuffList; }
	uint16_t GetValidBuffInfo(BUFF_INFO_DB* pBuffInfo, uint16_t num);
	void SetBuffList(const BUFF_INFO_DB* pBuffInfo, const uint16_t& nBuffNum, bool firstPack, bool sync = false);
    void SyncBuffList();

    void SetRoleExtraInfo(const ROLE_EXTRA_INFO &roleExtraInfo) { mRoleExtraInfo = roleExtraInfo; }
    ROLE_EXTRA_INFO & GetRoleExtraInfo() { return mRoleExtraInfo; }

	void SetRoleSettings(const ROLE_SETTINGS &roleSettings) { mRoleSettings = roleSettings; }
	ROLE_SETTINGS & GetRoleSettings() { return mRoleSettings; }

    void SetQuestInfo(const QUEST_INFO &questInfo) { mQuestInfo = questInfo; }
    QUEST_INFO & GetQuestInfo() { return mQuestInfo; }

    void SetQuestAchieves(const QUEST_ACHIEVE *pQuestAchieve, uint16_t num);
    std::list<QUEST_ACHIEVE> & GetQuestAchieves() { return mQuestAchieves; }
    void GetQuestAchieves(QUEST_ACHIEVE *pQuestAchieve, uint8_t &num);

    void SetCustVars(CUST_VAR_MAP vars) { mCustVars = std::move(vars); }
    CUST_VAR_MAP & GetCustVars() { return mCustVars; }

    void SetItemCustVars(CUST_VAR_SP_LIST vars) { mItemCustVars = std::move(vars); }
    CUST_VAR_SP_LIST & GetItemCustVars() { return mItemCustVars; }

	void SetItemDynAttrsList(ITEM_DYN_ATTRS_LIST attrsList, bool sync);
	ITEM_DYN_ATTRS_LIST & GetItemDynAttrsList() { return mItemDynAttrsList; }
	ITEM_DYN_ATTRS_LIST & GetSynItemDynAttrsList() { return mSyncItemDynAttrsList; }

	void SetRoleDynAttrsList(ROLE_DYN_ATTRS_LIST attrsList) { mRoleDynAttrsList = std::move(attrsList); }
	ROLE_DYN_ATTRS_LIST& GetRoleDynAttrsList() { return mRoleDynAttrsList; }

    void SetGoodsNotIssuedRecords(const GOODS_ISSUE_RECORD *records, uint8_t num);
	void SetGoodsNotPostRecords(const GOODS_ISSUE_RECORD* records, uint8_t num);
    void AddGoodsNotIssuedRecord(const GOODS_ISSUE_RECORD &record);
	void AddGoodsNotPostRecord(const GOODS_ISSUE_RECORD& record);

    uint8_t GetGoodsNotIssuedRecords(GOODS_ISSUE_RECORD *records, uint8_t size);
	uint8_t GetGoodsNotPostRecords(GOODS_ISSUE_RECORD* records, uint8_t size);

    void RemoveGoodsNotIssuedRecords(const char orderNoList[MAX_GOODS_ISSUE_RECORD][ORDER_NO_BUFLEN], uint8_t num);
	void UpdateGoodsNotPostRecords(const char orderNoList[MAX_GOODS_POST_RECORD][ORDER_NO_BUFLEN], uint8_t num);

	void SyncPlayerGender(uint8_t gender);

	void UpdateBriefInfo(const ROLE_BRIEF_INFO& briefInfo);
	void UpDataExtraInfo(const ROLE_EXTRA_INFO& extraInfo);
	void UpdataRoleSettingsInfo(const ROLE_SETTINGS& settingInfo);
	void UpdateQuickBarSetFlag(const unsigned char mslot);
	void SyncRoleInfoToDB(uint64_t userid);
	void SyncItemDynAttrsList(uint64_t userid);
	void SyncRoleTitleToDB();
	void SyncQuickBarSetToDB();

	void GenerateBriefInfo(ProtoCS_SyncRoleInfo& info);
	void GenerateExtraInfo(ProtoCS_SyncRoleInfo& info);

private:
    void CollectDiffItemDynAttrs(const DYN_ATTRS &newAttrs, DYN_ATTRS &oldAttrs, DYN_ATTRS &diffAttrs);

protected:
	bool mInitialized = false;
	ROLE_BRIEF_INFO mBriefInfo;
    ROLE_EXTRA_INFO mRoleExtraInfo;
	ROLE_SETTINGS   mRoleSettings;
	std::list<std::unique_ptr<ITEM_INFO>> mItemList;
	std::list<SKILL_INFO> mSkillList;
	std::string  info;
	std::vector<BUFF_INFO_DB> mBuffList;
    std::vector<BUFF_INFO_DB> mOldBuffList;
    std::list<GOODS_ISSUE_RECORD> mGoodsNotIssuedRecords;
	std::list<GOODS_ISSUE_RECORD> mGoodsNotPostRecords;

    QUEST_INFO mQuestInfo;
    std::list<QUEST_ACHIEVE> mQuestAchieves;

    CUST_VAR_MAP            mCustVars;
    CUST_VAR_SP_LIST        mItemCustVars;

	QUICK_BAR_INFO_LIST     mQuickBarSetInfo;

	DGN_BIND_INFO_LIST      mDgnBindInfo;
	DGN_BIND_INFO_LIST      mTmpDgnBindInfo;

    ITEM_DYN_ATTRS_LIST     mItemDynAttrsList, mSyncItemDynAttrsList;
	ROLE_DYN_ATTRS_LIST     mRoleDynAttrsList;

	bool mRoleSettingFlag = false;
	uint8_t mRoleBriefInfoFlagArray[role_brief_info_flag::flag_brief_max]{ 0 };
	uint8_t mRoleExtraInfoFlagArray[role_extra_info_flag::flag_extra_max]{ 0 };

	std::vector<unsigned char>mQuickBarSetFlag;
};
