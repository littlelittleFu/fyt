#pragma once
#include "Role.h"
#include "ProtoMS.h"
#include "SceneItem.h"
#include "GuildMgr.h"
#include "map_table.hpp"
#include "SummonMonster.h"
#include "TeamMgr.h"
#include "QuestMgr.h"
#include "PKValueMgr.h"
#include "MapServer.h"
#include "GameMall.h"
#include "PetMgr.h"
#include "FightInfoMgr.h"
#include "DigMgr.h"
#include "Auction.h"
#include "TitleMgr.h"
#include "PlayerDoplganr.h"

enum EXPBUFF {
    EXPBUFF_DOUBLE = 15000,     // 双倍经验buff
    EXPBUFF_DUP = 382,          // 副本双倍经验buff
};

struct TeamData;
class Monster;
class Session;
class StallDummy;
class PlayerDoplganr;

class Player : public Role
{
    friend StallDummy;
public:
	Player(uint32_t type = role_type_player);
	~Player();
    
	virtual void Update(int32_t delta) override;

    int32_t GetAttackMode() override;
    bool CheckCross() override;
    bool CheckTakeGrid(uint16_t x, uint16_t y) override;
    void CheckJump(void)override;
    void NotifyJump(const char*, uint16_t pox, uint16_t poy, uint16_t type) override;
    void OnRoleEnter(Role* role) override;
    void OnRoleLeave(Role* role) override;
    void OnRoleMove(Role* role) override;
    void OnRoleExit(Role* role) override;
    void OnRoleUpdateHPMP(int32_t nHP, int32_t nMP) override;
    void OnRoleDie(uint64_t killerGUID) override;
    void OnEnterMap(Map* map) override;
    void CalcDropItems(uint64_t killerGUID);
    void GetRoleInfoReq(void);
    void ClearRoleInfo(void);
    void DelRoleInfo(const std::string& info);
    void InsertRoleInfo(const std::string& info);
    void UpdateRoleInfo(const std::string& info);
    void SendRoleDirChangeNtf(Role* role, ProtoGS_TurnNtf& ntf) override;
    void SendRoleDieNtf(Role* role, ProtoMS_ObjDieNtf& ntf) override;
    void SendRoleObjDisappearNtf(ProtoMS_ObjDisappearNtf& ntf) override;
    void SendRoleItemAppearNtf(ProtoMS_ItemAppearNtf4& ntf) override;
    void SendRoleNameChangeNtf(ProtoGS_PlayerSetNameNtf& ntf) override;
    void SendRoleWearTitleNtf(ProtoGS_TitleWearNtf& ntf) override;
    void SendRoleUnWearTitleNtf(ProtoGS_TitleUnWearNtf& ntf) override;
    void OnlyUpdateAppearNtf(Role* role)override;
    void SendEffectAppearNtf(ProtoMS_EffectAppearNtf& ntf)override;
    void SendEffectDisAppearNtf(ProtoMS_EffectDisAppearNtf& ntf)override;

    void SendRoleAttrExtNtf();
    void SendRoleDynAttrsNtf(ProtoMS_RoleDynAttrsNtf& ntf);
    void SendRoleCustVarNtf(ProtoMS_RoleCustVarNtf& ntf);

	void AddRoleExp(int64_t exp, const log_params& lp);
	bool AddPlayerItem(uint16_t tempid, const log_params& lp);
	void AddPlayerExperience(int64_t tempid, const log_params& lp);
	void AddPlayerGold(uint64_t tempid, const log_params& lp);


	void NotifyPlayer_StartMove(uint16_t nDstX, uint16_t nDstY);

	void OnLogin();
    void OnLogout();
    void OnExit(uint8_t nExitType);
    void OnUpgrade(DATA::Role* preCfg, DATA::Role* curCfg);

    void ApplyFuncToAroundPlayers(std::function<void(Player*)> func, bool online = true);

public:
	void SetToken(uint32_t token) { mToken = token; }
	uint32_t GetToken() { return mToken; }

    void SetOnlineState(uint8_t state);
    uint8_t GetOnlineState() { return mOnlineState; }
    bool IsOnline() const { return mOnlineState == online_state_logged_in; }
    void SendUpdateOnlineStateToCS(uint32_t state);

	void SetClSessionID(uint32_t clSessionID) { mClSessionID = clSessionID; }
	void SetGsSessionID(uint32_t gsSessionID) { mGsSessionID = gsSessionID; }
	uint32_t GetGsSessionID() const { return mGsSessionID; }
	uint32_t GetClSessionID() const { return mClSessionID; }

    void SetUserName(const std::string& userName) { mUserName = userName; }
    std::string GetUserName() { return mUserName; }
    void SetSupport(uint8_t isSupport) { mIsSupport  = isSupport;}
    bool IsSupport() { return mIsSupport != 0; }
	void SetUserID(uint64_t userid) { mUserID = userid; };
	uint64_t GetUserID() { return mUserID; };

    void SetMultDgnMapID(const std::string& mapName, uint64_t multDgnMapID);
    uint64_t GetMultDgnMapID(const std::string& mapName);
    const std::string & GetMultDgnMapName(uint64_t multDgnMapID);
    uint64_t GetCurMultDgnMapID() {return mCurMulDgnMapID;}

	void SetRoleBriefInfo(const ROLE_BRIEF_INFO& info) { mRoleBriefInfo = info; };
	ROLE_BRIEF_INFO& GetRoleBriefInfo() { return mRoleBriefInfo; };
    bool IsGM();

    bool SetGender(uint8_t Gender);

    void SetRoleExtraInfo(const ROLE_EXTRA_INFO &info) { mRoleExtraInfo = info; }
    ROLE_EXTRA_INFO & GetRoleExtraInfo() { return mRoleExtraInfo; }

    void SetRoleSettings(const ROLE_SETTINGS &settings) { mRoleSettings = settings; }
    ROLE_SETTINGS & GetRoleSettings() { return mRoleSettings; }

    bool SetAutoPickItemRadius(uint8_t radius);
    bool SetAutoPickItemRelativePositions(std::vector<Point> relpos);
    bool SetAutoPickItemInterval(uint16_t interval);

	void SetExitType(uint8_t type) { mExitType = type; };
    uint8_t GetExitType() { return mExitType; };

    void SetLoginTime(uint64_t loginTime) { mRoleExtraInfo.login_time = loginTime; }
    uint64_t GetLoginTime() { return mRoleExtraInfo.login_time; }

    void SetCustVars(CUST_VAR_MAP vars);
    const CUST_VAR_MAP & GetCustVars() { return mCustVars; }

    void SetCustVar(std::string name, std::string value, const uint8_t &type);
    const std::string & GetCustVar(const std::string &name);

    void SetItemCustVars(CUST_VAR_SP_LIST vars);

    void SetItemDynAttrsList(ITEM_DYN_ATTRS_LIST attrsList);
    void SetRoleDynAttrsList(ROLE_DYN_ATTRS_LIST attrsList);

    void SetRebateMoneyNotUsedRecord(const REBATE_MONEY_RECORD& record);
    void SetGoodsNotIssuedRecords(const GOODS_ISSUE_RECORD *records, uint8_t num);
    void SetGoodsNotPostRecords(const GOODS_ISSUE_RECORD* records, uint8_t num);

    void SetNameInfo(const std::string& name);

    uint32_t GetCurLoginNotifyDelayTime() { return mLoginNotifyDelayTime; }
    void SetNextLoginNotifyDelayTime(uint32_t delayTime) { mLoginNotifyDelayTime = delayTime; }

	uint64_t GetMapCode();

    uint16_t GetIdleBagCount();
    uint16_t GetBagFirstFreeSite();
    int AddItem(uint16_t nTemplateID, uint16_t nNum, uint8_t nBindRequire, uint8_t nSiteRange, const log_params& lp);
    int AddItemByKeyName(const std::string &sKeyName, uint16_t nNum, uint8_t bBind, uint8_t nJob, const log_params& lp);
    int AddItemByKeyNameToSite(const std::string& sKeyName, uint16_t nNum, uint8_t bBind, uint8_t nJob, uint16_t nSite, const log_params& lp);
    uint64_t AddSingleItem(uint16_t nTemplateID, uint16_t nNum, uint8_t nBindRequire, const log_params& lp);
    int RemoveItem(uint16_t nTemplateID, uint16_t nNum, uint8_t bindRequire, uint8_t nSiteRange, const log_params& lp);
    int RemoveItem(uint64_t itemGuid, uint16_t nNum, const log_params& lp);
    int RemoveItem(const std::string& itemKeyName, uint16_t nNum, uint8_t bindRequire, uint8_t nSiteRange, const log_params& lp);
    uint32_t GetItemNum(uint16_t templateID, uint8_t bindRequire, uint8_t nSiteRange);
    uint32_t GetItemNumByKeyName(const std::string &keyName, uint8_t bindRequire, uint8_t nSiteRange);
    int AddItems(const CLuaObject &luaObj, const log_params& lp);
    const std::string & GetGuildName();
    void TalkToNpc(Role *npc, std::string dialog);

    int AddSkill(uint16_t skillID, bool active);
    void RemoveSkill(uint16_t skillID);
    void RemoveSkillByChainID(uint32_t skillChainID);
    void AlterSkill(uint16_t oldSkillID, uint16_t newSkillID);  // 技能升级或降级
    bool SkillIsExist(uint16_t skillID);
    std::vector<uint16_t> GetSkillIDList();
    bool AddSkillProficiencyValue(uint32_t skillID, uint32_t value);

    bool SetSkillLevel(uint32_t skillID);
    void UpdateReloginInfo();

public:
	void Init();
    void InitRoleAttr(DATA::Role* roleCfg);
    void CalculateRoleAttr();

	void MakePlayerAppearNtfData(ProtoMS_PlayerAppearNtf& ntf);
	void SendErrorAck(int32_t type, const char* errMsg = nullptr);
    void SendGMErrorAck(int32_t sn, int32_t ecode);
    void SendPopDlgMsgNtf(const std::string &msg);

    void SendSysMsgNtf2(MESSAGE_INFO& info,bool toall = false);
    void SendSceneDialogNtf(MESSAGE_INFO& info);
    void SendScrollText(MESSAGE_INFO& info,bool toall = false);
    void SendCustMsgNtf(MESSAGE_INFO& info);
    void SendMonsterPursureStatus(Monster* monster);
    void SendMonsterAppearNtf(Monster* monster);

    static void GenerateSysMsgInfo(MESSAGE_INFO& info, SYSTEN_MESSAGE_NTF& data);
    static void GenerateSenceDialogInfo(MESSAGE_INFO& info, SCENCE_DIALOG_NTF& data);
    static void GenerateScrollTextInfo(MESSAGE_INFO& info, SCROLL_TEXT& data);
    static void GenerateCustMsgInfo(MESSAGE_INFO& info, CUST_MSG_NTF& data);


    void OnGetSkillAck(const SKILL_INFO *pSkillInfo, uint16_t num);

    void OnRecvIDgnBindInfoFromCS(const ProtoCS_DgnBindInfoNtf& ntf);

	void OnRecvItemFromCS(ProtoCS_SendItemNtf& ntf);
    void OnRecvTitleFromDB(uint16_t num, TITLE_INFO* info);
	void UseItem(uint64_t guid, uint32_t num);
	void DropItem( uint64_t guid);
    void ItemArrange(unsigned char type);
	void PickUpItem();
    void PickUpItem(const Point *pos, uint8_t num);
	bool ItemMove(uint64_t, uint16_t);
    bool ItemSplit(uint64_t, uint16_t, uint16_t);
	void SendDestroyItem(uint64_t itemGUID);
	void SendAddItem(ProtoMS_ItemAddAck& ack);
    void SendAllBagItemsToGS();
    void OnUseEquip(uint16_t site);
    void OnUnloadEquip(uint16_t site);
	void HandlePlayerSwitch(uint8_t id, uint8_t val);

    void QueryPlayerInfo(const std::string &name);
    void QueryPlayerInfo(const uint64_t &guid);
    void QueryPlayerInfo(Player *player);
    void QueryPlayerDoplganrInfo(PlayerDoplganr *doplganr);

    void TeleportToPos(uint16_t x, uint16_t y);

    void SetCustVarAssociatedData();
    void SetCustVarAssociatedData(const std::string& type, const std::string& value);
    void SetClientBaseSetting();
    void SetClientBaseSetting(uint16_t type, int32_t value);
    bool HandleGoodsIssue(GOODS_ISSUE_RECORD &record);
    void HandleGoodsPostRecordAck(const char* order_no);
    void VerifyBuyItemInfo(uint32_t itemID, uint8_t count, uint32_t price);

	void  Relive(uint8_t type, uint32_t sessid);

	void RunServScript(const char* pScriptName, const char* pFuncName, const PARAM_INFO2* pParams, uint16_t nParamNum);
	void RunClientScript(const char *pScriptName, const char *pContent, bool bCompress);
    void RunClientScript_Around(const char* pScriptName, const char* pContent, bool bCompress);

    void EnterShop(uint16_t nShopID);
    void BuyItem(uint16_t nShopID, uint16_t nItemIndex, uint16_t nAmount, bool bUseBind);

    int EnterDgnMap(const std::string &sMapKeyName, const log_params& lp);        // 进入副本地图
    int EnteryMulDgnMap(Map* mulDgnMap, uint16_t posX, uint16_t posY, const log_params& lp);
    int ExitDgnMap();                                       // 退出副本地图
    int ExitMulDgnMap(Map* mulDgnMap);
    bool IsInDgnMap() { return mInDgnMap; }

    bool IsInSameTeam(Role *role) override;
    bool IsInSameGuild(Role *role) override;
    bool IsInSameCamp(Role *role) override;
    bool IsGrayName() override;
    bool IsRedName() override;
    bool IsMyPet(Role *role) override;
    bool IsMyDoplganr(Role *role) override;
    bool IsMyBiaoChe(Role *role) override;

    uint16_t GetNearstNpcPosByName(uint16_t& x, uint16_t& y,const char * name);
    void CopyFromOwner();

    void GetTitleListReq();

    void DropItemByDropProcess(uint16_t type, uint64_t killerGuid = 0);

    ////////////////////////////////////////////////////////////////////////////////
    // SKILL

    void SendSpellAck(uint64_t role_guid, int32_t ecode, uint16_t skillID, uint16_t clientSN);

    void OnAddItem(uint16_t nSite);
    void OnRemoveItem(uint16_t nSite);
    void OnUpdateItem(uint16_t nSite, int nNum);
    void OnSwapItem(uint16_t nSite1, uint16_t nSite2);
    void OnItemAppear(SceneItem *item) override;
    void OnItemDisappear(SceneItem *item) override;

    void SendRoleAttrExtRefNtfToGS(uint16_t nAttrID, int64_t nDelta);

public:

    void TriggerCheckStall();
    void SendPlayerSkillPropChangeNtf(Role* pRole);
    void SendRelationChatNtf(const MESSAGE_INFO& info);
	void SendPlayerAppearNtf(Role* pRole);
    void SendRoleAppNtf(Role *toRole) override;
	void SendPlayerReliveNtf(std::string mapName, int type, int hp, int mp, uint16_t x, uint16_t y);
	void SendPlayerShowNtf(int hp, int mp);
	void SendMapEnterNtf(DATA::Map* cfg);
    void SetQuickBarSetVec(const ProtoGS_QuickBarSet &msg);
    bool SetGoldChangeAttr(int64_t gold, const log_params& lp);
    void RunGMCommand(void* pData);
    void UpdateRoleInfo();
    void SendChangePlayerNameNtf(const std::string& name);

	//to CS
	void SendSyncItemNtf(uint64_t guid, uint16_t amount, int dura, uint16_t id, int site,
		const std::string& name, int max_dura, uint16_t use_cnt, uint8_t boud, uint32_t life);
	void SendSyncItemNtf(const RoleItem & item);//update, insert
	void SendDelItemNtf(const RoleItem & item, uint8_t beTrade = 0);//del
	void SendSyncBuffReqToCS();
    void SendSyncSkillReqToCS();
    void SendSyncRoleInfoReqToCS();
    void SendSyncRoleDynAttrReqToCS();
    void SendSyncItemInfoReqToCS();
    void SendSyncItemDynAttrsToCS();
    void SendSyncPlayerQuickBarSetToCS();
    void SendSyncPlayerDgnBindInfoToCS();
    void SendSyncPlayerMailInfoToCS();
    void SendSyncPlayerTitleInfoToCS();
    void SendSyncQuestReqToCS();
    void SendSyncPlayerCustVarToCS();
    void SendSyncPlayerItemCustVarToCS();
    bool SendSaveGoodsIssueRecordToCS(const GOODS_ISSUE_RECORD &record, bool sendByGM = false);
    void SendGoodsPostRecordToClient(GOODS_ISSUE_RECORD& record);
    void SendGoodsIssuedNtfToCS(const std::vector<std::string> &orderNoList);
    void SendGoodsIssuedPostToCS(const std::vector<std::string>& PostList);
    void SendActivationCodeToCS(uint16_t type, const std::string& code);
    void SendRebateMoneyUsedNtfToCS();
	/*to GS */
    void SendSkillAddAckToGS(uint16_t skillID = 0);
    void SendSkillDeleteAckToGS(uint16_t skillID);
    void SendSkillStatusNtfToGS(uint16_t skillID, bool active);
    void SendSkillPropChangedNtfToGS(uint16_t skillID, const std::string& cfg);
    void SendSkillProficiencyNtfToGS(uint16_t skillID, uint32_t proficiency);

    void SendObjDisappearNtfToGS(const uint64_t &nObjID);
    void SendObjDisappearNtfToGSBySingle(const uint64_t &nObjID);

	void SendItemUpdateNtf(ProtoMS_ItemUpdateNtf& ntf);
	void SendItemAttrNtf(uint64_t guid,uint32_t attr,int val);
    void SendLevelUpNtfToAroundPlayers();
    void SendAutoPickupSettingsNtfToGS();
    void SendRoleAppearNtfToAroundPlayers(uint8_t appearType);

    bool JumpMapByTarMap(Map* tarMap, uint16_t x,uint16_t y,uint16_t type);
	bool JumpMap(const std::string& mapName, uint16_t posX, uint16_t posY, uint16_t type);
    bool JumpMap(Map* tarMap, uint16_t x, uint16_t y)override;


    uint16_t GetWarehouseSize();
    uint16_t GetAdvWarehouseSize();
    uint16_t GetWarehouseFreeSize();
    uint16_t GetAdvWarehouseFreeSize();
    uint16_t GetWarehouseFirstFreeSite();
    uint16_t GetAdvWarehouseFirstFreeSite();
    uint32_t GetGmModLevel();

    CLuaObject  GetVipExtePermissions();
    bool        HasVipExtePermissions(int32_t permissions);

    static void SetNameToCS(const std::string &name, uint64_t guid);

    bool AddTitleByName(const std::string& titleName);
    bool DelTitleByName(const std::string& titleName);
    bool IsHasTitle(const std::string& titleName);

    void GetListProp(CLuaObject& list,uint16_t type, uint16_t min , uint16_t max);
    void GetListItem(CLuaObject& list, uint16_t min, uint16_t max);

    void GenRoleCustVar(ProtoMS_RoleCustVarNtf& ntf);
    void GenRoleTempCustVar(ProtoMS_RoleCustVarNtf& ntf);

    CLuaObject GetRebateMoneyInfo();
    void GetRebateMoney();

protected:
    void SendRoleCustVar();
    void StartSyncDataTimer();
    void StopSyncDataTimer();

    bool CheckUpgrade(int64_t& exp, int64_t diffExp, int32_t nLevel, uint64_t nUpgradeExp, const log_params& lp);
public:
    void SyncPlayerData();

    void ResetSyncPlayerTimer();
protected:
    void SaveCurLocation();

    uint64_t RecalcExp(uint64_t exp);

    void RemoveUpgradeTimer();

    void SaveRebirthMap(Map *map);
    void SaveRedNameMap(Map *map);

    void RebirthBackToTown();     // 回城复活
    bool LeaveCurMap(bool destroySummonMonster);
    bool EnterMap(Map *map, uint16_t x, uint16_t y);

    void SetBagSize();
    void SetWarehouseSize();
    void SetAdvWarehouseSize();

    void NotifyAroundPlayers_RefreshEquip();

    void MarkEntryMap(Map* map);
    void MarkLeaveMap(Map* map);

    void CheckCustVarNeedUpdate();

    uint8_t  GetRoleAppearType();

    void BindStallDummy();
    void UnBindStallDummy();
    void HandleGoodsNotIssuedRecords();
    void HandleGoodsNotPostIssuedRecords();


////////////////////////////////////////////////////////////////////////////////

    // 没有用到
    //void SendRoleAttrNtfToGS(uint16_t nAttrName, int32_t nAttrValue);
    //void SendRoleAttrNtf(const std::vector<uint16_t>& attr);
public:
    SP_BUY_DELEGATE_LIST& GetBuyDelegateInfo();
    SP_SELL_DELEGATE_LIST& GetSellDelegateInfo();
    SP_TRADE_RECORD_MAP& GetTradeBuyRecords();
    SP_TRADE_RECORD_MAP& GetTradeSellRecords();
    vector<MAIL_INFO>& GetMailInfo() { return MailVector; }
    SummonMonsterMgr& GetSummonMonsterMgr() { return mSummonMonsterMgr; }
    PetMgr& GetPetMgr() { return mPetMgr; }
    GuildDataMgr& GetGuildDataMgr() { return mGuildDataMgr; }
    TeamDataMgr& GetTeamDataMgr() { return mTeamDataMgr; }
    QuestDataMgr& GetQuestDataMgr() { return mQuestDataMgr; }
    DigMgr & GetDigMgr() { return mDigMgr; }
    StallDummy * GetStallDummy() { return mStallDummy;; }
    TitleDataMgr& GetTitleData() { return mTitleDataMgr; }
    PlayerDoplganrMgrPtr & GetDoplganrMgr() { return mDoplganrMgr; }
    bool NeedCalculate() { return mNeedCalculateAttribute; }
protected:
    std::string                     mUserName               = "";
	uint32_t                        mToken                  = 0;
	uint32_t                        mGsSessionID            = 0;
	uint32_t                        mClSessionID            = 0;
	uint64_t                        mUserID                 = 0;
    uint8_t                         mExitType               = 0;
    uint32_t                        mSyncTimerId            = 0;
    uint8_t                         mOnlineState            = 0;
    std::pair<uint64_t, uint64_t>   mLoginOutTimestamp      = { 0,0 };

	ROLE_BRIEF_INFO                 mRoleBriefInfo;
    ROLE_EXTRA_INFO                 mRoleExtraInfo;
    ROLE_SETTINGS                   mRoleSettings;

    std::unique_ptr<Map>            mDgnMap;
    uint64_t                        mCurMulDgnMapID         = 0;        // 当前进入的副本mapGuid
    std::unordered_map<std::string, uint64_t> mMultDgnMapID;            // 每个副本mapKeyName对应一个副本mapGuid
    bool                            mInDgnMap               = false;

    uint32_t                        mUpgradeTimerID         = 0;
    uint32_t                        mLoginNotifyDelayTime   = 4000;     // 登录后各通知延迟时间

    CUST_VAR_MAP                    mCustVars;
    CUST_VAR_MAP                    mTempCustVars;
    bool                            mCustVarMody            = false;
    bool                            mTempCustVarMody        = false;

    vector<QUICK_BAR_INFO>          BarVector;
    vector<MAIL_INFO>               MailVector;
    std::list<GOODS_ISSUE_RECORD>   mGoodsNotIssuedRecords;
    std::list<GOODS_ISSUE_RECORD>   mGoodsNotPostRecords;

    REBATE_MONEY_RECORD             mRebateMoneyRecord;

    PetMgr                          mPetMgr;
    SummonMonsterMgr                mSummonMonsterMgr;
    GuildDataMgr                    mGuildDataMgr;
    TeamDataMgr                     mTeamDataMgr;
    QuestDataMgr                    mQuestDataMgr;
    PKValueMgr                      mPKValueMgr;
    DigMgr                          mDigMgr;
    TitleDataMgr                    mTitleDataMgr;
    PlayerDoplganrMgrPtr            mDoplganrMgr;
    bool                            mNeedCalculateAttribute = false;

    uint8_t                         mIsSupport = 0;
protected:
    // 摆摊假人,状态为角色摆摊那一刻的状态
    StallDummy*                     mStallDummy = nullptr;
    bool                            mStallBindTrade = false;
    SP_BUY_DELEGATE_LIST            mBuyDelegateInfo;
    SP_SELL_DELEGATE_LIST           mSellDelegateInfo;
    SP_TRADE_RECORD_MAP             mTradeBuyRecords;
    SP_TRADE_RECORD_MAP             mTradeSellRecords;
};

class StallDummy : public Player
{
    friend Player;
public:
    StallDummy(Player* owner);
    void Init();
    virtual void Update(int32_t delta) override;
    void OnRoleEnter(Role* role) override {}
    void OnRoleLeave(Role* role) override {}
    void OnRoleMove(Role* role) override {}
    void OnRoleExit(Role* role) override {}

    void CopyFromOwner();
    void TriggerCheckUnStall();
    void ChangeStallName(std::string name,uint8_t type);
private:
    bool CheckUnStall(const SP_SELL_DELEGATE_LIST& mSellDelegateInfo);
private:
    uint64_t mOwnerGuid = 0;
    Player* mOwner = nullptr;

};