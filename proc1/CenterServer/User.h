#pragma once
#include "ProtoMS.h"
#include "RoleData.h"
#include "AuctionMgr.h"
#include "GuildData.h"
#include "TopList.h"
#include "TradeData.h"
#include "WantedList.h"
#include "Title.h"

class User
{

public:
	struct PlatformRebateReq
	{
		PlatformRebateReq(uint64_t id, const std::string& account)
		{
			account_id = id;
			strncpy_s(account_name, account.c_str(), sizeof(account_name) - 1);
		}
		uint64_t		account_id = 0;
		char			account_name[256] = { 0 };
	};
public:
	
	User();
	User(uint64_t id);
	~User();
	void Init(uint64_t id);

	void SetID(uint64_t id) { mID = id; };
	uint64_t GetID(void) { return mID; };

	void SetToken(uint32_t token) { mToken = token; };
	uint32_t GetToken(void) { return mToken; };


	void SetGS2LSSessionID(uint32_t sessionID) { mGS2LSSessionID = sessionID; };
	uint64_t GetGS2LSSessionID(void) { return mGS2LSSessionID; };


	void SetGS2CLSessionID(uint32_t sessionID) { mGS2CLSessionID = sessionID; };
	uint64_t GetGS2CLSessionID(void) { return  mGS2CLSessionID; };


	void SetCS2GSSessionID(uint32_t sessionID) { mCS2GSSessionID = sessionID; };
	uint64_t GetCS2GSSessionID(void) { return mCS2GSSessionID; };

	void SetMS2GSSessionID(uint32_t sessionID) { mMS2GSSessionID = sessionID; };
	uint64_t GetMS2GSSessionID(void) { return mMS2GSSessionID; };

	void SetUserName(const std::string& userName) { mUserName = userName; }
	const std::string & GetUserName() const { return mUserName; };

	void SetOnlineState(uint8_t state) { mOnlineState = state; };
	uint8_t GetOnlineState() { return mOnlineState; };

	void SetIP(uint32_t ip) { mIP = ip; }
	uint32_t GetIP() { return mIP; }

	void SetProhibitChat(int64_t isProhibitChat) { mIsProhibitChat = isProhibitChat; }
	int64_t GetIsProhibitChat() { return mIsProhibitChat; }

	void SetLastSelectRole(uint64_t roleGUID) { mLastSelectRole = roleGUID; }
	uint64_t GetLastSelectRole() { return mLastSelectRole; }

	void AddRoleDataInfo(ROLE_BRIEF_INFO& info);
	void RemoveRoleDataInfo(uint64_t role_id, int32_t status);
	
	const ROLE_BRIEF_INFO& GetRoleBirefInfo(uint64_t role_id);
	std::map<uint64_t, RoleData>& GetRoleDataMap() { return mRoleDataMap; }
	std::map<uint64_t, RoleData>& GetDeleteRoleDataMap() { return mDeleteRoleDataMap; }
	void ClearRoleDataMap() { mRoleDataMap.clear(); }
	void ClearDeleteRoleDataMap() { mDeleteRoleDataMap.clear(); }
	void AddRoleItem(uint64_t id,std::unique_ptr<ITEM_INFO>& item);
	void DelRoleItem(const uint64_t roleID, const uint64_t itemID);
	ITEM_INFO* GetRoleSingleItem(const uint64_t roleID, const uint64_t itemID);
	std::list<std::unique_ptr<ITEM_INFO>>& GetRoleAllItem(uint64_t id);

	bool CompareItem(const ITEM_INFO * localitem, const ITEM_INFO * recvitem);
	bool CompareItem(const ITEM_INFO * localitem, const ProtoMS_SendSyncItemNtf* recvitem);

    void SetSkillList(const uint64_t& nRoleID, const SKILL_INFO* pSkillInfo, uint16_t nNum);
	uint16_t GetSkillList(const uint64_t& nRoleID, SKILL_INFO* pSkillInfo, uint16_t nNum);
    void SyncSkillList(const uint64_t &nRoleID, const SKILL_INFO *pSkillInfo, uint16_t nNum);

	std::unique_ptr<ITEM_INFO> AppendUserItemInfo(void* pdata);
	void SyncUserItemInfo(ITEM_INFO*,void *pdata);

    std::string& GetInfo(const uint64_t& nRoleID);
	void SetInfo(uint64_t id, const std::string& str);

	void SetRandKey(const std::string& key) { mRandKey = key; }
	std::string GetRandKey() { return mRandKey; }

	void SetChannel(const std::string& channel) { mChannel = channel; }
	std::string GetChannel() { return mChannel; }

	void SetHardware(const std::string& key) { mHardware = key; }
	std::string GetHardware() { return mHardware; }

	void SetEnterType(char val) { mEnterType = val; }
	char GetEnterType() { return mEnterType; }
	void SetFangChenMi(char val) { mFangChenMi = val; }
	char GetFangChenMi() { return mFangChenMi; }
	void SetClientType(char val) { mClientType = val; }
	char GetClientType() { return mClientType; }

	void OnGetRoleDataAck(const uint64_t& roleID);
	void OnEnterMapReq(const uint64_t& roleID);

	void SetBuffList(const uint64_t& roleID, BUFF_INFO_DB* buff, uint16_t num, bool firstPack, bool sync = false);

    void SetRoleExtraInfo(const uint64_t &nRoleID, const ROLE_EXTRA_INFO &roleExtraInfo);
    void SyncRoleInfo(const uint64_t &nRoleID, const ROLE_BRIEF_INFO &newBriefInfo,
		const ROLE_EXTRA_INFO &newExtraInfo, const ROLE_SETTINGS &newSettings);

	void SetRoleSettings(const uint64_t &nRoleID, const ROLE_SETTINGS &roleSettings);

    void SetQuestInfo(const uint64_t &nRoleID, const QUEST_INFO &questInfo);
    void SetQuestAchieves(const uint64_t &nRoleID, const QUEST_ACHIEVE *pQuestAchieve, uint16_t num);
    void SyncQuestInfo(const uint64_t &nRoleID, const QUEST_INFO &questInfo, const QUEST_ACHIEVE *pQuestAchieve, uint8_t num);

    void SetCustVars(const uint64_t &roleid, CUST_VAR_MAP vars);
    CUST_VAR_MAP * GetCustVars(const uint64_t &roleid);
    void SyncCustVars(const uint64_t &roleid, CUST_VAR_MAP vars);

    void SetItemCustVars(const uint64_t &roleid, CUST_VAR_SP_LIST vars);
    CUST_VAR_SP_LIST * GetItemCustVars(const uint64_t &roleid);
    void SyncItemCustVars(const uint64_t &roleid, CUST_VAR_SP_LIST vars);
	void DeleteItemCustVars(uint64_t roleGUID, uint64_t itemGUID);

    void SetItemDynAttrsList(const uint64_t &roleid, ITEM_DYN_ATTRS_LIST attrsList, bool sync);
    ITEM_DYN_ATTRS_LIST * GetItemDynAttrsList(const uint64_t &roleid);
	void DeleteItemAttrsList(uint64_t roleGUID, uint64_t itemGUID);

	void SetRoleDynAttrsList(const uint64_t& roleid, ROLE_DYN_ATTRS_LIST attrsList);
	ROLE_DYN_ATTRS_LIST* GetRoleDynAttrsList(const uint64_t& roleid);

	void IsHavingGmMod(const std::string& gmCmd, std::string& playername, uint8_t& result);

	void SetRebateMoneyNotUsedRecord(const REBATE_MONEY_RECORD& record);
    void SetGoodsNotIssuedRecords(const uint64_t &roleGUID, const GOODS_ISSUE_RECORD *records, uint8_t num);
	void SetGoodsNotPostRecords(const uint64_t& roleGUID, const GOODS_ISSUE_RECORD* records, uint8_t num);

    void AddGoodsNotIssuedRecord(const uint64_t &roleGUID, const GOODS_ISSUE_RECORD &record);
	void AddGoodsNotPostRecord(const uint64_t& roleGUID, const GOODS_ISSUE_RECORD& record);

    void RemoveGoodsNotIssuedRecords(const uint64_t &roleGUID,
    const char orderNoList[MAX_GOODS_ISSUE_RECORD][ORDER_NO_BUFLEN], uint8_t num);
	void SyncGoodsPostRecords(const uint64_t& roleGUID,
		const char orderNoList[MAX_GOODS_POST_RECORD][ORDER_NO_BUFLEN], uint8_t num);
	void SetRebateMoneyUsedRecord(ProtoMS_RebateMoneyUsedNtf& msg);

	void SyncPlayerGender(uint8_t gender, uint64_t guid);

	void UpdateOnlineStateToDB(uint8_t type);
	void StartSyncRoleInfoTimer();
	void StopSyncRoleInfoTimer();
	void SyncUserData();
	void UpdateQuickBarSetFlag(uint8_t slot,uint64_t guid);

	static size_t CURLWriteCallback(void* data, size_t size, size_t nmemb, void* userp);
	void SendGetRebateReqToPlatform(const PlatformRebateReq& rebateInfo);
	void SendUpdateRebateReqToPlatform(const PlatformRebateReq& rebateReq);
	bool ComposeHttpRequest(const PlatformRebateReq& rebateInfo, char* buf, int bufsz);
	void ParseResult(std::shared_ptr<PlatformRebateReq> ptr,  std::vector<char>& resp);
	void UpdateSupport(uint8_t val) { mSupportStatus = val; }
	uint8_t GetIsSupport() { return mSupportStatus; }
protected:
	uint64_t			    mID;
	uint32_t                mToken;                  // 登录后分配的
	uint32_t                mGS2LSSessionID;      // 网关与登录服务器的session id
	uint32_t                mGS2CLSessionID;
	uint32_t                mCS2GSSessionID;
	uint32_t                mMS2GSSessionID;

	uint32_t                mSyncUserTimerId = 0;

	char					mEnterType;
	char					mFangChenMi;
	char					mClientType;

	int64_t                 mIsProhibitChat = 0;

	uint8_t					mSupportStatus = 0;
	std::string             mUserName;
	uint32_t                mIP;
	std::string             mHardware;
	uint8_t                 mOnlineState;
	std::string				mRandKey;
	uint64_t				mLastSelectRole;
	std::string             mChannel;
	std::map<uint64_t, RoleData> mRoleDataMap;
	REBATE_MONEY_RECORD		mRebateMoneyRecord;

	std::map<uint64_t, RoleData> mDeleteRoleDataMap;
public:
	void OnGetRoleItemAck(const uint64_t& roleID, ITEM_INFO* items, int num);
	
	void HandleMapServMsg_SendSyncItemNtf(void* pData);
	void DeleteItem(uint64_t roleGUID, uint64_t itemGUID, uint8_t tradeDel);

	void HandleMapServMsg_SyncQuickBarSet(void* pData);
	void AddQuickBar(uint64_t id, QUICK_BAR_INFO& item);
	void UpdateQuickBar(QUICK_BAR_INFO* info, void* pdata);
	bool CompareQuickBar(const QUICK_BAR_INFO* localitem, const QUICK_BAR_INFO* recvitem);
	void SetQuickBarSetNtf(void* pData);
	void ChangePlayerNameInfo(uint64_t guid, const std::string& name, const std::string& orgName);

	void HandleMapServMsg_SyncDgnBindInfo(void* pData);
	void SetDgnBindInfoNtf(void* pData);

	void HandleMapServMsg_GetRoleInfoReq(void* pdata);
	void HandleMapServMsg_DelRoleInfoNtf(void* pData);
	void HandleMapServMsg_ClearRoleInfoNtf(void* pData);
	void HandleMapServMsg_UpdateRoleInfoNtf(void* pData);
	void HandleMapServMsg_InsertRoleInfoNtf(void* pData);
	void HandleMapServMsg_SendRoleInfoAck(void* pData);

	void SendInsertItemNtf(void* pData);
	void SendUpdateItemNtf(void* pData);
	void SendDelItemNtf(uint64_t roleGUID, uint64_t itemGUID);
};
