
#pragma once
#include "DBConnector.h"

#include <iostream>
#include <list>

#include"ProtoCS.h"
#include"ProtoMS.h"
#include"ProtoDB.h"
#include "fb_structs_generated.h"

enum DBErrCode {
    DBERR_OK,
    DBERR_EXESQL,
    DBERR_PARAM,
    DBERR_ROWNUM,
    DBERR_EMPTY,
    DBERR_NOTMATCH,
    DBERR_EXCEPT,
    DBERR_BUFSZ
};

class CDBManager
{
    enum DBElemType {
        elem_type_string    = 1,
        elem_type_uint8     = 2,
        elem_type_uint16    = 3,
        elem_type_uint32    = 4,
        elem_type_uint64    = 5
    };

public:
	CDBManager();
	~CDBManager();

	static CDBManager* GetInstance();
	bool Init();

	int CheckAccount(const char* pUserName, const char* pPassword, uint64_t& playerid,uint8_t isThirdLogin, int64_t& isProhibitChat, uint8_t& isSupport);
    int InsertPlayer(uint64_t playerid, const char *username);
    int GetLoginIpInfo(std::vector<LOGIN_IP_DATA>&vec);
	int GetRoleBriefInfo(const uint64_t& nPlayerID, std::vector<ROLE_BRIEF_INFO>& vRoleBriefInfo, uint64_t& nLastSelectedRole);
    int GetOneRoleBriefInfo(const uint64_t& nRoleID, ROLE_BRIEF_INFO& roleBriefInfo);
	int UpdateLastSelectedRole(const uint64_t &nPlayerID, const uint64_t& nRoleID);
	int CreateRole(const uint64_t& nPlayerID, const ROLE_BRIEF_INFO& roleBriefInfo);
	int DeleteRole(const uint64_t& nRoleID, int32_t& status);
    int RestoreRole(const uint64_t& nRoleID, int32_t& status);
    int CheckIfCreateRoleCode(uint8_t needCode, uint64_t digCode);
    int DeleteCreateRoleCode(uint8_t needCode, uint64_t digCode, uint64_t role);
    int CheckIfRoleExistByName(const char *name, uint8_t &exist, uint64_t &guid, bool includingDeleted = false);
    int CheckIfRoleExistByGUID(uint64_t guid, uint8_t &exist, char *name, uint32_t bufsize);
	int GetSkillInfo(const uint64_t& nRoleID, SKILL_INFO* pSkillInfo, uint16_t& num);
    int SyncSkillInfo(const uint64_t &nRoleID, const SKILL_INFO *pRemoveSkillInfo, uint16_t nRemoveSkillNum,
        const SKILL_INFO *pAddSkillInfo, uint16_t nAddSkillNum, const SKILL_INFO *pUpdateSkillInfo, uint16_t nUpdateSkillNum);
	int GetBuffInfo(const uint64_t& nRoleID, std::list<BUFF_INFO_DB>&);
    int SyncBuffInfo(const uint64_t &nRoleID, const uint64_t *pRemoveIndex, uint16_t nRemoveNum,
        const BUFF_INFO_DB *pAddBuffInfo, uint16_t nAddNum, const BUFF_INFO_DB *pUpdateBuffInfo, uint16_t nUpdateNum);

	int ClearRoleInfo(const uint64_t& nRoleID);
	int DeleteRoleInfo(const uint64_t& nRoleID, const std::string& info);
	int UpdateRoleInfo(const uint64_t& nRoleID, const std::string& info);
	int InsertRoleInfo(const uint64_t& nRoleID, const std::string& info);
	int GetRoleInfo(const uint64_t& nRoleID,char *info, uint32_t buffSize);
	int GetRoleInfo(const uint64_t& nRoleID, char* info, uint32_t buffSize, uint64_t& rows);

	int GetItemInfo(const uint64_t& nguid, std::list<ITEM_DB_INFO>& vitemInfo, uint8_t state = item_state_owner, std::string tableName = "item");
    int GetItemInfoByItemGuid(uint64_t nguid, uint64_t itemGuid, ITEM_DB_INFO& vitemInfo, uint8_t state = item_state_owner, std::string tableName = "item");
	int DeleteItemInfo(const uint64_t& roleguid, const uint64_t& guid);
	int InsertItemInfo(const uint64_t& nguid, const ITEM_DB_INFO& Info, uint8_t state = item_state_owner);
    int InsertItemExtraData(const ITEM_INFO& Info);
	int UpdateItemInfo(const uint64_t& nguid, const ITEM_DB_INFO& Info);


    int GetItemDynAttrsList(const uint64_t &roleid, ITEM_DYN_ATTRS_LIST &attrsList, uint8_t state = item_state_owner, std::string tableName = "item_dyn_attr", std::string tName = "item");
    int GetItemDynAttrs(const uint64_t itemGUID, DYN_ATTRS &attrs, uint8_t state = item_state_owner,
                        const char *attrTable = "item_dyn_attr", const char *itemTable = "item");
    int UpdateItemDynAttrs(const ITEM_DYN_ATTRS_LIST &attrsList);

    int CheckRoleAccount(const uint64_t& nRoleID, const uint64_t& playerid);
    int GetRoleExtraInfo(const uint64_t &nRoleID, ROLE_EXTRA_INFO &roleExtraInfo, ROLE_SETTINGS &roleSettings);
    int SyncRoleInfo(const ROLE_BRIEF_INFO &brief, const ROLE_EXTRA_INFO &extra, const ROLE_SETTINGS &settings);
    int SyncRoleInfo(const ProtoCS_SyncRoleInfo* info);
    int GetRoleDynAttrsList(const uint64_t& roleid, ROLE_DYN_ATTRS_LIST& attrsList);
    int UpdateRoleDynAttrs(const ROLE_DYN_ATTRS_LIST& attrsList);
    int UpdateOnlineState(const uint64_t &roleGUID, const uint8_t &state);

    int GetQuestInfo(const uint64_t &nRoleID, QUEST_INFO &questInfo);
    int GetQuestAchieve(const uint64_t &nRoleID, QUEST_ACHIEVE *pQuestAchieve, uint8_t &num);
    int SyncQuestInfo(const uint64_t &nRoleID, const QUEST_INFO &questInfo,
        const QUEST_ACHIEVE *pRemoveAchevs, uint8_t nRemoveNum, const QUEST_ACHIEVE *pAddAchevs, uint8_t nAddNum,
        const QUEST_ACHIEVE *pUpdateAchevs, uint8_t nUpdateNum);

    void GetTradeRecords(uint32_t tradeRecordsExpireTime, std::list<TRADE_RECORD>& list);
    void GetTradeDelegate(SP_BUY_DELEGATE_MAP& buy, SP_SELL_DELEGATE_MAP& sell);
    int TradeRecordsCancel(uint16_t num, uint64_t* trade_id);
    int TradeDelegateCancel(uint64_t tradeid, uint8_t delegatetype);
    int TradeDelegateBuy(const ProtoMS_DelegateBuyCmd& cmd);
    int TradeDelegateSell(const ProtoMS_DelegateSellCmd& cmd);
    int TradeMarketBuy(const ProtoCS_MarketBuyAck& cmd);
    int TradeMarketSell(const ProtoCS_MarketSellAck & cmd);
    int GetGuilds(GUILD_MAP &guilds);
    int GetGuildMembers(GUILD_MEMBER_MAP &members);
    int GetGuildApplicants(GUILD_APPLICANT_LIST &applicants);
    int SyncGuildApplicant(const SPGUILD_APPLICANT &applyInfo, uint8_t type);
    int SyncGuildMember(const SPGUILD_MEMBER &member, uint8_t type);
    int SyncGuildInfo(const SPGUILD &guild, uint8_t type);
    int SyncGuildRelation(uint8_t type, uint64_t myGUID, uint64_t peerGUID, uint8_t relation);
    int SyncAuctionItemInfo(const ProtoMS_SynAuctionItemInfo& info);
    int UpdateMallInfo(const ProtoMS_MallLimitInfoUpdate& info);

    int GetCustVars(CUST_VAR_SP_LIST &vars);
    int SetCustVar(CUST_VAR var);

    int GetPlayerCustVar(const uint64_t &roleid, CUST_VAR_MAP &vars);
    int SyncPlayerCustVar(CUST_VAR_LIST add, CUST_VAR_LIST remove, CUST_VAR_LIST update);

    int GetPlayerItemCustVar(const uint64_t &roleid, CUST_VAR_SP_LIST &vars, uint8_t state = item_state_owner, std::string tableName = "item_cust_var", std::string tName = "item");
    int GetItemCustVars(uint64_t itemGUID, CUST_VAR_SP_LIST &vars, uint8_t state = item_state_owner,
                        const char *varTable = "item_cust_var", const char *itemTable = "item");
    int SyncItemCustVar(CUST_VAR_SP_LIST *add, CUST_VAR_SP_LIST *remove, CUST_VAR_SP_LIST *update);

    int SyncQuickBarSet(void* pData);
    int GetQuickBarSetInfo(const uint64_t& nRoleID, QUICK_BAR_INFO_LIST &vars);

    int SyncDgnBindInfo(void* pData);
    int GetDgnBindInfo(const uint64_t& nRoleID, DGN_BIND_INFO_LIST& vars);
    int GetTopList(uint64_t* rolelist, TOPLIST_INFO* topList,uint8_t &topListNum, uint8_t type); 
    int AddNewMail(const ProtoMS_AddSysNewMail &data, std::vector<std::pair<uint64_t,uint64_t>>&info);
    int DeleteMailByMailID(const uint64_t& MailID);
    int SyncMailInfoStatus(uint64_t playerguid,uint16_t num,const Mail_Info_Status* info);
    int GetMailInfo(uint64_t playerguid, std::list<MAIL_INFO>& maillist);
    int GetMailAttachment(const ProtoMS_GetMailAttachmentReq& req, ProtoCS_GetMailAttachmentAck& ack);
    int GetAuctionHouseList(std::vector<AUCTION_HOUSE_ITEM_INFO>& req);
    void UpdateAuctionHouseInfo(std::vector<AUCTION_HOUSE_ITEM_INFO>& req);

    int GetMallLimitInfo(uint8_t limit_type,vector<MALL_ITEM_INFO_BASE>& data);
    int DeleteMallRemainedData();
    int AddLoginIpType(uint8_t num,uint32_t* ip, uint8_t ip_type);
    int DelLoginIpType(uint8_t num,uint32_t* ip, uint8_t ip_type);
    int UpdateSupportPlayer(uint8_t& num, uint8_t type, char name[100][32], uint64_t guid[100]);
    int AddLockPlayer(uint8_t num, char name[100][32]);
    int AddLockRole(uint8_t num, uint64_t guid[100]);
    int DelLockPlayer(uint8_t num, char name[100][32]);
    int DelLockRole(uint8_t num, char name[100][32], ProtoDB_DelLockRoleAck& data);
    int GetProhibitChatInfo(std::vector<PROHIBIT_CHAT_DATA>&vec);
    int DelProhibitChatInfo(uint8_t num, const PROHIBIT_CHAT_DATA* data);
    int AddProhibitChatInfo(uint8_t num, const PROHIBIT_CHAT_DATA* data);
    string JsonStyleEncode(const MAIL_INFO& data);
    string JsonStyleEncode(const MAIL_INFO& data,int);
    string JsonStyleEncode(const ITEM_CFG_VAR& data);
    void JsonStyleDecode(const string& info, MAIL_INFO& data);
    void JsonStyleDecode(const string& info, MAIL_INFO& data,int);
    void JsonStyleDecode(const string& info, ITEM_CFG_VAR& data);
    int GetConstantCfg(CONSTANT_CFG_MAP& constantCfgMap);

    int GetWantedList(WANTED_SP_LIST &wantedList);
    int AddToWantedList(uint64_t nWantedByGUID, const char *pWantedName, uint32_t nBounty, const char *pDesc,
        uint64_t nTime, uint64_t &nWantedGUID, uint32_t &nIndex);

    int SaveGoodsIssueRecord(const GOODS_ISSUE_RECORD &record);
    int GetGoodsNotIssuedRecords(uint64_t roleGUID, GOODS_ISSUE_RECORD *records, uint8_t &num);
    int GetGoodsNotPostRecords(uint64_t roleGUID, GOODS_ISSUE_RECORD* records, uint8_t& num);

    int SetGoodsIssuedFlag(const char orderNoList[MAX_GOODS_ISSUE_RECORD][ORDER_NO_BUFLEN], uint8_t num);
    int SyncGoodsPostRecord(const char orderNoList[MAX_GOODS_POST_RECORD][ORDER_NO_BUFLEN], uint8_t num);
    int GetRebateMoneyNotUsedRecord(REBATE_MONEY_RECORD& record);
    int SetRebateMoneyUsedFlag(REBATE_MONEY_RECORD& record);
    int PlayerSetName(const std::string& name, uint64_t guid, uint64_t& userid,std::string& orgName);
    int UpdateRoleUpdateTime(uint64_t guid);

    void UpdateNameInfoToTable(const std::string& tableName, const std::string& guidFeild, const std::string nameFeild,
        uint64_t guid, const std::string& changeName);
    int GetItemTipInfo(uint64_t orgGuid, uint64_t ownerGuid, uint64_t itemGuid, ITEM_INFO& info);
    int AddTitle(uint64_t guid, const TITLE_INFO& info);
    int DelTitle(uint64_t guid,uint16_t num, const uint32_t* id);
    int ChangeTitleWearType(uint64_t guid, uint32_t id, uint16_t wearType);
    int SyncTitleInfo(uint64_t guid, int num, const TITLE_INFO* info);
    int GetPlayerTitleInfo(uint64_t guid, std::vector<TITLE_INFO>& vec);
    int UpdateDBTables(const uint8_t *data, uint32_t len);
    int AddPlayerProhibitChat(uint64_t userID, int64_t stamp);
    int DelPlayerProhibitChat(uint64_t userID);
    int SyncCustListInfo(uint8_t optType, uint8_t num, const CUST_LIST_INFO* data);
    int SyncPlayerGender(uint64_t guid, uint8_t gender);
    int GetCustListInfo(std::vector<CUST_LIST_INFO>*vec);

    int UpdateItemState(uint64_t itemGuid, uint32_t state);

public:
    static void MailUpdateDay();

private:
	bool ExecuteSQL(const char* sql);
	bool ExecuteSQL(const char* sql,uint64_t &rows);

    int SyncCustVar(const char *table, CUST_VAR_LIST &add, CUST_VAR_LIST &remove, CUST_VAR_LIST &update);
    int SyncCustVar(const char *table, CUST_VAR_SP_LIST *add, CUST_VAR_SP_LIST *remove, CUST_VAR_SP_LIST *update);

    int SyncQuickBar(const char* table, void* pData);
   
    void GetItemExtraData(uint64_t role_guid, uint64_t item_guid, ITEM_INFO & item, uint8_t state = item_state_owner);
    void GetTradeItemExtraData(uint64_t role_guid, uint64_t item_guid, ITEM_INFO& item);

    int UpdateRole(const flatbuffers::Vector<uint8_t> *key,
                   const flatbuffers::Vector<flatbuffers::Offset<DBElem>> *elems);

    int UpdateAppendElem(char *&buf, int &bufsz, const char *elemName, DBElemType elemType,
                         const uint8_t *data, bool &first);

private:
	static CDBManager* s_Instance;
	DBConnector    m_DBConnector;
};
