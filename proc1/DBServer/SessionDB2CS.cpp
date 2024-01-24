#include "stdafx.h"
#include "SessionDB2CS.h"
#include "ILogHelper.h"
#include "DBManager.h"
#include "DBServer.h"
#include "CNetManager.h"
#include "GMCmdHandler.h"

#include <memory>
#include <map>

#include "ProtoLS.h"
#include "ProtoGS.h"
#include "ProtoCS.h"
#include "ProtoMS.h"
#include "ProtoDB.h"


SessionDB2CS::SessionDB2CS()
{

}

SessionDB2CS::~SessionDB2CS()
{

}

void SessionDB2CS::OnEstablish(SOCKET _Socket)
{
	Session::OnEstablish(_Socket);
	LOG_NORMAL("OnEstablish. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
}

void SessionDB2CS::OnLost()
{
	LOG_NORMAL("OnLost. IP=%s Port=%d", GetRemoteIp().c_str(), GetRemotePort());
	//DoClose();
}

void SessionDB2CS::OnMessage(uint16_t moduleid, uint16_t protoid, void* _pData)
{
    MsgCostStat::GetInstance()->BeginHandleMsg();

    OnHeartBeat();

	switch (moduleid) {
		case MODULE_TYPE_CS:
			HandleCenterServMsg(protoid, _pData);
			break;

		case MODULE_TYPE_GS:
			HandleGateServMsg(protoid, _pData);
			break;

		case MODULE_TYPE_MS:
			HandleMapServMsg(protoid, _pData);
			break;

		default:
			LOG_WARN("Unhandled moduleid: %u", moduleid);
			break;
	}

    MsgCostStat::GetInstance()->EndHandleMsg(moduleid, protoid);
}

void SessionDB2CS::OnError(DWORD _ErrorCode)
{
	LOG_ERROR("_ErrorCode:%d", _ErrorCode);
}

void SessionDB2CS::OnUpdate(UINT _Delta)
{
	Session::OnUpdate(_Delta);
}

void SessionDB2CS::DoHeartBeat()
{

}

void SessionDB2CS::HandleCenterServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_CS_HEART_BEAT_REQ, HandleCenterServMsg_HeartBeatReq)
        HANDLE_MSG(PROTO_CS_GET_ROLE_DATA_REQ, HandleCenterServMsg_GetRoleDataReq)
        HANDLE_MSG(PROTO_CS_DELETE_ITEM_NTF, HandleCenterServMsg_DeleteItemReq)
        HANDLE_MSG(PROTO_CS_INSERT_ITEM_NTF, HandleCenterServMsg_InsertItemReq)
        HANDLE_MSG(PROTO_CS_UPDATE_ITEM_NTF, HandleCenterServMsg_UpdateItemReq)
        HANDLE_MSG(PROTO_CS_GET_ROLE_INFO_REQ, HandleCenterServMsg_GetRoleInfoReq)
        HANDLE_MSG(PROTO_CS_CLEAR_ROLE_INFO_NTF, HandleCenterServMsg_ClearRoleInfoReq)
        HANDLE_MSG(PROTO_CS_DELETE_ROLE_INFO_NTF, HandleCenterServMsg_DeleteRoleInfoReq)
        HANDLE_MSG(PROTO_CS_INSERT_ROLE_INFO_NTF, HandleCenterServMsg_InsertRoleInfoReq)
        HANDLE_MSG(PROTO_CS_UPDATE_ROLE_INFO_NTF, HandleCenterServMsg_UpdateRoleInfoReq)
        HANDLE_MSG(PROTO_CS_SYNC_SKILL_REQ, HandleCenterServMsg_SyncSkillReq)
        HANDLE_MSG(PROTO_CS_SYNC_BUFF_REQ, HandleCenterServMsg_SyncBuffReq)
        HANDLE_MSG(PROTO_CS_SYNC_QUEST_REQ, HandleCenterServMsg_SyncQuestReq)
        HANDLE_MSG(PROTO_CS_SYNC_PLAYER_CUST_VAR, HandleCenterServMsg_SyncPlayerCustVar)
        HANDLE_MSG(PROTO_CS_SYNC_ITEM_CUST_VAR, HandleCenterServMsg_SyncItemCustVar)
        HANDLE_MSG(PROTO_CS_QUICK_BAR_SET, HandleCenterServMsg_SyncQuickBarSet)
        HANDLE_MSG(PROTO_CS_DGN_BIND_INFO, HandleCenterServMsg_SyncDgnBindInfoSet)
        HANDLE_MSG(PROTO_CS_TOPLIST_REQ, HandleCenterServMsg_GetTopListReq)
        HANDLE_MSG(PROTO_CS_GET_MAIL_INFO, HandleCenterServMsg_GetMailInfo)   
        HANDLE_MSG(PROTO_CS_MARKET_SELL_ACK, HandleCenterServMsg_MarketSellAck);
        HANDLE_MSG(PROTO_CS_MARKET_BUY_ACK, HandleCenterServMsg_MarketBuyAck);
        HANDLE_MSG(PROTO_CS_ENTER_MS_NTF, HandleCenterServMsg_EnterMSNtf);
        HANDLE_MSG(PROTO_CS_SYNC_ROLE_INFO, HandleCenterServMsg_SyncRoleInfoFromCS);
        HANDLE_MSG(PROTO_CS_UPDATE_TABLES, HandleCenterServMsg_UpdateTables);
        HANDLE_MSG(PROTO_CS_GET_MAIL_ATTACHMENT_ACK, HandleCenterServMsg_GetMailAttachmentAck);
	END_MSG_HANDLER()
}

void SessionDB2CS::HandleCenterServMsg_DeleteItemReq(void* pData)
{
	ProtoCS_DeleteItemNtf* pDeleteItemReq = (ProtoCS_DeleteItemNtf*)pData;
	int result = CDBManager::GetInstance()->DeleteItemInfo(pDeleteItemReq->guid, pDeleteItemReq->role_id);
	if (result != 0) {
		LOG_WARN("delete item error!");
	}
}

void SessionDB2CS::HandleCenterServMsg_InsertItemReq(void* pData)
{
	ProtoCS_InsertItemNtf* pInsertItemReq = (ProtoCS_InsertItemNtf*)pData;
	int result = CDBManager::GetInstance()->InsertItemInfo(pInsertItemReq->role_id, pInsertItemReq->base_info);
	if (result != 0) {
		LOG_WARN("insert item error!");
	}
}

void SessionDB2CS::HandleCenterServMsg_UpdateItemReq(void* pData)
{
	ProtoCS_UpdateItemNtf* pUpdateItemReq = (ProtoCS_UpdateItemNtf*)pData;
	int result = CDBManager::GetInstance()->UpdateItemInfo(pUpdateItemReq->role_id, pUpdateItemReq->base_info);
	if (result != 0) {
		LOG_WARN("update item error!");
	}
}

void SessionDB2CS::HandleCenterServMsg_HeartBeatReq(void* pData)
{
	ProtoCS_HeartBeatAck ack;
	SendPkg(&ack, sizeof(ack));
}

void SessionDB2CS::HandleCenterServMsg_GetRoleDataReq(void* pData)
{
	SAFE_BEGIN;
	auto req = (ProtoCS_GetRoleDataReq*)pData;
    //===============================================================确认角色就是这个账号下的  转移角色后可能有问题
    int result = 0;
    result = CDBManager::GetInstance()->CheckRoleAccount(req->roleid,req->playerid);
    if (result != 0) {
        LOG_ERROR("CheckRoleAccount failed with error %d, playerid: %" PRIu64 ", roleid: %" PRIu64, result, req->playerid, req->roleid);
        return;
    }
    result = CDBManager::GetInstance()->UpdateLastSelectedRole(req->playerid, req->roleid);
    if (result != 0) {
        LOG_ERROR("UpdateLastSelectedRole failed with error %d, playerid: %" PRIu64 ", roleid: %" PRIu64, result, req->playerid, req->roleid);
    }
	//===============================================================角色额外信息
    ProtoCS_RoleExtraInfoNtf roleExtraInfoNtf;
    roleExtraInfoNtf.roleid = req->roleid;
    roleExtraInfoNtf.token = req->token;


    result = CDBManager::GetInstance()->GetRoleExtraInfo(req->roleid,
        roleExtraInfoNtf.roleExtraInfo, roleExtraInfoNtf.roleSettings);
    if (result != 0) {
        LOG_ERROR("GetRoleExtraInfo failed with error %d, roleid: %" PRIu64, result, req->roleid);
    }
    else {
        SendPkg(&roleExtraInfoNtf, sizeof(roleExtraInfoNtf));
    }


    //===============================================================角色动态属性
    ROLE_DYN_ATTRS_LIST roleDynAttrsList;
    result = CDBManager::GetInstance()->GetRoleDynAttrsList(req->roleid, roleDynAttrsList);
    if (result != 0) {
        LOG_WARN("GetRoleDynAttrsList failed with error %d, roleid: %" PRIu64, result, req->roleid);
    }
    else if (!roleDynAttrsList.empty()) {

        ProtoDB_RoleDynAttrNtf roleDynAttrNtf;
        roleDynAttrNtf.playerid = req->playerid;
        roleDynAttrNtf.roleid = req->roleid;
        roleDynAttrNtf.token = req->token;
        roleDynAttrNtf.role_dyn_attrs_list = &roleDynAttrsList;
        SendPkg(&roleDynAttrNtf, sizeof(roleDynAttrNtf));
    }

	//=============================================================获取角色物品
	std::list<ITEM_DB_INFO> vItemInfo;
	result = CDBManager::GetInstance()->GetItemInfo(req->roleid, vItemInfo);
	if (result != 0) {
		LOG_WARN("GetItemInfo failed. %" PRIu64,req->roleid);
	}
	else {
		auto& getItemAck = gProtoCS_GetItemAck;
		getItemAck.role_id = req->roleid;
		getItemAck.token = req->token;
		getItemAck.item_num = 0;
		int i = 0, idx = 0, maxCount = sizeof(getItemAck.item_info) / sizeof(ITEM_INFO);
		for (auto& itemInfo : vItemInfo) {
			getItemAck.item_info[idx].base_info = itemInfo;
			//memset(&getItemAck.item_info[idx].custom, 0, sizeof(getItemAck.item_info[idx].custom));
            ++idx, ++i;
			if (i == vItemInfo.size() || idx == maxCount) {
				getItemAck.item_num = idx;
				SendPkg(&getItemAck, sizeof(getItemAck));
				idx = 0;
			}
		}
	}

    //=============================================================获取角色物品动态属性
    ITEM_DYN_ATTRS_LIST itemDynAttrsList;
    result = CDBManager::GetInstance()->GetItemDynAttrsList(req->roleid, itemDynAttrsList);
    if (result != 0) {
        LOG_WARN("GetItemDynAttrsList failed with error %d, roleid: %" PRIu64, result, req->roleid);
    }
    else if (!itemDynAttrsList.empty()) {

        ProtoDB_ItemDynAttrNtf itemDynAttrNtf;
        itemDynAttrNtf.playerid = req->playerid;
        itemDynAttrNtf.roleid = req->roleid;
        itemDynAttrNtf.token = req->token;
        itemDynAttrNtf.item_dyn_attrs_list = &itemDynAttrsList;
        SendPkg(&itemDynAttrNtf, sizeof(itemDynAttrNtf));
    }

	//=============================================================获取角色技能
	ProtoMS_GetSkillAck getSkillAck;
	getSkillAck.playerid = req->playerid;
	getSkillAck.roleid = req->roleid;
	getSkillAck.skillNum = _countof(getSkillAck.skillInfo);
	result = CDBManager::GetInstance()->GetSkillInfo(req->roleid, getSkillAck.skillInfo, getSkillAck.skillNum);
	if (result != 0) {
		LOG_ERROR("GetSkillInfo failed with error %d", result);
	}
	else {
		SendPkg(&getSkillAck, sizeof(getSkillAck));
	}

	//=============================================================获取角色buff
    std::list<BUFF_INFO_DB> li;
	ProtoMS_GetBuffAck getBuffAck;
	getBuffAck.playerid = req->playerid;
	getBuffAck.roleid = req->roleid;
	getBuffAck.buffNum = 0;
    getBuffAck.beFirstPack = 1;
	result = CDBManager::GetInstance()->GetBuffInfo(req->roleid, li);
	if (result != 0) {
		LOG_ERROR("GetBuffInfo failed with error %d", result);
	}
	else {
        for (auto iter = li.begin(); iter != li.end(); ++iter)
        {
            getBuffAck.buffs[getBuffAck.buffNum++] = std::move(*iter);
            if (getBuffAck.buffNum == _countof(getBuffAck.buffs))
            {
                SendPkg(&getBuffAck, sizeof(getBuffAck));
                getBuffAck.buffNum = 0;
                getBuffAck.beFirstPack = 0;
            }
        }
        if (getBuffAck.buffNum) SendPkg(&getBuffAck, sizeof(getBuffAck));
	}

    //=============================================================获取任务信息
/*    ProtoDB_QuestInfo questInfo;
    questInfo.roleid = req->roleid;
    questInfo.token = req->token;

    result = CDBManager::GetInstance()->GetQuestInfo(req->roleid, questInfo.quest_info);
    if (result != DBERR_OK && result != DBERR_EMPTY) {
        LOG_ERROR("GetQuestInfo failed with error %d, roleid: %" PRIu64, result, req->roleid);
    }
    else {
        questInfo.achev_data_num = _countof(questInfo.achev_data);
        result = CDBManager::GetInstance()->GetQuestAchieve(req->roleid, questInfo.achev_data, questInfo.achev_data_num);

        if (result != DBERR_OK) {
            LOG_ERROR("GetQuestAchieve failed with error %d, roleid: %" PRIu64, result, req->roleid);
        }
        else {
            SendPkg(&questInfo, sizeof(questInfo));
        }
    }*/

    //=============================================================获取玩家自定义变量

    CUST_VAR_MAP playerVars;
    result = CDBManager::GetInstance()->GetPlayerCustVar(req->roleid, playerVars);

    if (result != DBERR_OK) {
        LOG_ERROR("GetPlayerCustVar failed with error %d, roleid: %" PRIu64, result, req->roleid);
    }
    else {
        ProtoDB_PlayerCustVar custVar;
        custVar.playerid = req->playerid;
        custVar.roleid = req->roleid;
        custVar.token = req->token;
        custVar.vars = &playerVars;

        SendPkg(&custVar, sizeof(custVar));
    }

    //=============================================================获取玩家物品自定义变量

    CUST_VAR_SP_LIST playerItemVars;
    result = CDBManager::GetInstance()->GetPlayerItemCustVar(req->roleid, playerItemVars);

    if (result != DBERR_OK) {
        LOG_ERROR("GetPlayerItemCustVar failed with error %d, roleid: %" PRIu64, result, req->roleid);
    }
    else {
        ProtoDB_PlayerItemCustVar custVar;
        custVar.playerid = req->playerid;
        custVar.roleid = req->roleid;
        custVar.token = req->token;
        custVar.vars = &playerItemVars;

        SendPkg(&custVar, sizeof(custVar));
    }

    //==============================================================获取副本绑定信息
    DGN_BIND_INFO_LIST vDgnBindInfo;
    ProtoDB_DgnBindInfoNtf getDgnBindInfo;
    result = CDBManager::GetInstance()->GetDgnBindInfo(req->roleid, vDgnBindInfo);
    if (result != 0) 
    {
        LOG_WARN("GetDgnBindInfo failed. %" PRIu64, req->roleid);
    }
    else
    {
        getDgnBindInfo.roleId = req->roleid;
        getDgnBindInfo.userid = req->playerid;
        getDgnBindInfo.num = 0;
        DGN_BIND_INFO_LIST::iterator it = vDgnBindInfo.begin();
        for (; it != vDgnBindInfo.end(); )
        {
            getDgnBindInfo.info[getDgnBindInfo.num++] = (*it++);
            if (getDgnBindInfo.num >= ProtoDB_DgnBindInfoNtf::DBI_MaxSize::Info_Size
                || it == vDgnBindInfo.end())
            {
                SendPkg(&getDgnBindInfo, sizeof(getDgnBindInfo));
                getDgnBindInfo.num = 0;
            }
        }
    }

    //==============================================================获取快捷栏信息
    std::list<QUICK_BAR_INFO> vQuickBarInfo;
    ProtoDB_QuickBarSetNtf getQuickBarInfo;
    result = CDBManager::GetInstance()->GetQuickBarSetInfo(req->roleid, vQuickBarInfo);
    if (result != 0) {
        LOG_WARN("GetQuickBarSet failed. %" PRIu64, req->roleid);
    }
    else {
        getQuickBarInfo.role_id = req->roleid;
        getQuickBarInfo.userid = req->playerid;
        getQuickBarInfo.num = vQuickBarInfo.size();
        int i = 0;
        for (list<QUICK_BAR_INFO>::iterator it = vQuickBarInfo.begin(); i < getQuickBarInfo.num; i++, it++) {
            getQuickBarInfo.info[i].guid = (*it).guid;
            getQuickBarInfo.info[i].id = (*it).id;
            getQuickBarInfo.info[i].slot = (*it).slot;
            getQuickBarInfo.info[i].type = (*it).type;
        }
    }
    SendPkg(&getQuickBarInfo, sizeof(getQuickBarInfo));

    //==============================================================获取未发放商品记录
    ProtoDB_GoodsNotIssuedRecordsNtf goodsNotIssuedRecords;
    goodsNotIssuedRecords.num = _countof(goodsNotIssuedRecords.records);
    result = CDBManager::GetInstance()->GetGoodsNotIssuedRecords(
        req->roleid, goodsNotIssuedRecords.records, goodsNotIssuedRecords.num);
    if (result != DBERR_OK) {
        LOG_WARN("GetGoodsNotIssuedRecords failed with error %d, roleid: %llu", result, req->roleid);
    }
    else if (goodsNotIssuedRecords.num > 0) {
        goodsNotIssuedRecords.player_guid = req->playerid;
        goodsNotIssuedRecords.role_guid = req->roleid;
        SendPkg(&goodsNotIssuedRecords, sizeof(goodsNotIssuedRecords));
    }

    //==============================================================获取未投递商品记录
    ProtoDB_GoodsNotPostRecordsNtf goodsNotPostRecords;
    goodsNotPostRecords.num = _countof(goodsNotPostRecords.records);
    result = CDBManager::GetInstance()->GetGoodsNotPostRecords(
        req->roleid, goodsNotPostRecords.records, goodsNotPostRecords.num);
    if (result != DBERR_OK) {
        LOG_WARN("GetGoodsNotPostRecords failed with error %d, roleid: %llu", result, req->roleid);
    }
    else if (goodsNotPostRecords.num > 0) {
        goodsNotPostRecords.player_guid = req->playerid;
        goodsNotPostRecords.role_guid = req->roleid;
        SendPkg(&goodsNotPostRecords, sizeof(goodsNotPostRecords));
    }

    //==============================================================删档返利记录
    /*
    ProtoDB_RebateMoneyNotUsedRecordNtf rebateMoneyNotUsedRecord;
    rebateMoneyNotUsedRecord.role_guid = req->roleid;
    rebateMoneyNotUsedRecord.record.be_load = 1;
    rebateMoneyNotUsedRecord.record.account_id = req->playerid;
    result = CDBManager::GetInstance()->GetRebateMoneyNotUsedRecord(rebateMoneyNotUsedRecord.record);
    if (result != DBERR_OK) {
        LOG_WARN("GetRebateMoneyNotUsedRecord failed with error %d, roleid: %llu  playerid: %llu", result, req->roleid, req->playerid);
    }
    else{
        SendPkg(&rebateMoneyNotUsedRecord, sizeof(rebateMoneyNotUsedRecord));
    }
    */
    //=============================================================获取角色称号
    ProtoDB_GetTitleInfoAck getTitleInfoAck;
    getTitleInfoAck.playerguid = req->playerid;
    getTitleInfoAck.guid = req->roleid;
    std::vector<TITLE_INFO>vec;
    result = CDBManager::GetInstance()->GetPlayerTitleInfo(req->roleid, vec);
    if (result != DBERR_OK) {
        LOG_WARN("get player title info failed with error %d, roleid: %llu", result, req->roleid);
    }
    if (vec.size() != 0) {
        for (int i = 0; i < vec.size(); ++i) {
            getTitleInfoAck.info[getTitleInfoAck.num] = std::move(vec[i]);
            ++getTitleInfoAck.num;
            if (getTitleInfoAck.num == 100) {
                SendPkg(&getTitleInfoAck, sizeof(getTitleInfoAck));
                memset(getTitleInfoAck.info, 0, sizeof(getTitleInfoAck.info));
                getTitleInfoAck.num = 0;
            }
        }
        if (getTitleInfoAck.num != 0 && getTitleInfoAck.num != 100) {
            SendPkg(&getTitleInfoAck, sizeof(getTitleInfoAck));
        }
    }

	//=============================================================GetRoleDataAck
	ProtoCS_GetRoleDataAck getRoleDataAck;
	getRoleDataAck.token = req->token;
	getRoleDataAck.playerid = req->playerid;
	getRoleDataAck.roleid = req->roleid;
	SendPkg(&getRoleDataAck, sizeof(getRoleDataAck));

    SAFE_END;
}

void SessionDB2CS::HandleGateServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_GS_GET_ROLE_LIST_REQ, HandleGateServMsg_GetRoleListReq)
        HANDLE_MSG(PROTO_GS_CREATE_ROLE_REQ, HandleGateServMsg_CreateRoleReq)
        HANDLE_MSG(PROTO_GS_DELETE_ROLE_REQ, HandleGateServMsg_DeleteRoleReq)
        HANDLE_MSG(PROTO_GS_RESTORE_ROLE_REQ, HandleGateServMsg_RestoreRoleReq)
        HANDLE_MSG(PROTO_GS_UPDATE_ONLINE_STATE, HandleGateServMsg_UpdateOnlineState)
    END_MSG_HANDLER()
}

void SessionDB2CS::HandleGateServMsg_GetRoleListReq(void* pData)
{
	ProtoGS_GetRoleListReq* pGetRoleListReq = (ProtoGS_GetRoleListReq*)pData;

	ProtoGS_GetRoleListAck getRoleListAck;
	getRoleListAck.sessionid = pGetRoleListReq->sessionid;
	getRoleListAck.token = pGetRoleListReq->token;
	getRoleListAck.playerid = pGetRoleListReq->playerid;

	uint64_t nLastSelectedRole = 0;
	std::vector<ROLE_BRIEF_INFO> vRoleBriefInfo;
	int result = CDBManager::GetInstance()->GetRoleBriefInfo(pGetRoleListReq->playerid, vRoleBriefInfo, nLastSelectedRole);

	if (result != 0) {
		getRoleListAck.errcode = ERR_DATABASEERR;
	}
	else {
		getRoleListAck.errcode = ERR_OK;
        getRoleListAck.rolenum = std::min<uint8_t>(vRoleBriefInfo.size(), _countof(getRoleListAck.rolelist));
        std::copy(vRoleBriefInfo.begin(),
            vRoleBriefInfo.begin() + getRoleListAck.rolenum, getRoleListAck.rolelist);
		getRoleListAck.last_role = nLastSelectedRole;
	}

	SendPkg(&getRoleListAck, sizeof(getRoleListAck));
}

void SessionDB2CS::HandleGateServMsg_CreateRoleReq(void* pData)
{
	auto pCreateRoleReq = (ProtoGS_CreateRoleReq*)pData;

    ProtoGS_CreateRoleAck createRoleAck;
    createRoleAck.playerid = pCreateRoleReq->playerid;
    createRoleAck.sessionid = pCreateRoleReq->sessionid;
    createRoleAck.token = pCreateRoleReq->token;

    int32_t r = CDBManager::GetInstance()->CheckIfCreateRoleCode(pCreateRoleReq->needCode, pCreateRoleReq->digCode);
    if (ERR_OK != r)
    {
        LOG_ERROR("CreateRoleReq failed with error %d", r);
        if (r == DBERR_NOTMATCH)
            createRoleAck.errcode = ERR_CREATE_ROLE_CODE_NOTMATTCH;
        else
            createRoleAck.errcode = ERR_DATABASEERR;

        SendPkg(&createRoleAck, sizeof(createRoleAck));
        return;
    }

    uint8_t beExist = 0;
    uint64_t guid = 0;
    int32_t result = CDBManager::GetInstance()->CheckIfRoleExistByName(pCreateRoleReq->createrole.name, beExist, guid, true);
    if (ERR_OK != result)
    {
        createRoleAck.errcode = ERR_DATABASEERR;
        LOG_ERROR("CreateRoleReq failed with error %d", result);
    }
    else if (!beExist)
    {
    pCreateRoleReq->createrole.guid = GenerateObjID(E_OBJ_PLAYER, ConfigInfo::GetInstance());
	pCreateRoleReq->createrole.level = 1;
	int result = CDBManager::GetInstance()->CreateRole(pCreateRoleReq->playerid, pCreateRoleReq->createrole);

	createRoleAck.newrole = pCreateRoleReq->createrole;
	createRoleAck.errcode = (result == 0) ? ERR_OK : ERR_DATABASEERR;

    if (ERR_OK == createRoleAck.errcode) CDBManager::GetInstance()->DeleteCreateRoleCode(pCreateRoleReq->needCode, pCreateRoleReq->digCode, pCreateRoleReq->createrole.guid);
    }
    else
    {
        createRoleAck.errcode = ERR_ROLENAMEEXIST;
        LOG_ERROR("CreateRoleReq failed name %s existed!", pCreateRoleReq->createrole.name);
    }
	SendPkg(&createRoleAck, sizeof(createRoleAck));
}

void SessionDB2CS::HandleGateServMsg_DeleteRoleReq(void* pData)
{
	auto pDeleteRoleReq = (ProtoGS_DeleteRoleReq*)pData;

	int result = CDBManager::GetInstance()->DeleteRole(pDeleteRoleReq->roleid, pDeleteRoleReq->status);

	ProtoGS_DeleteRoleAck deleteRoleAck;
	deleteRoleAck.sessionid = pDeleteRoleReq->sessionid;
	deleteRoleAck.token = pDeleteRoleReq->token;
	deleteRoleAck.playerid = pDeleteRoleReq->playerid;
	deleteRoleAck.roleid = pDeleteRoleReq->roleid;
	deleteRoleAck.errcode = (result == 0) ? ERR_OK : ERR_DATABASEERR;
    deleteRoleAck.status = pDeleteRoleReq->status;

	SendPkg(&deleteRoleAck, sizeof(deleteRoleAck));
}

void SessionDB2CS::HandleGateServMsg_RestoreRoleReq(void* pData)
{
    auto pRestoreRoleReq = (ProtoGS_RestoreRoleReq*)pData;

    int result = CDBManager::GetInstance()->RestoreRole(pRestoreRoleReq->roleid, pRestoreRoleReq->status);

    ProtoGS_RestoreRoleAck restoreRoleAck;
    restoreRoleAck.sessionid = pRestoreRoleReq->sessionid;
    restoreRoleAck.token = pRestoreRoleReq->token;
    restoreRoleAck.playerid = pRestoreRoleReq->playerid;
    restoreRoleAck.roleid = pRestoreRoleReq->roleid;
    restoreRoleAck.errcode = (result == 0) ? ERR_OK : ERR_DATABASEERR;
    if (DBERR_OK == result) CDBManager::GetInstance()->GetOneRoleBriefInfo(pRestoreRoleReq->roleid, restoreRoleAck.role);

    SendPkg(&restoreRoleAck, sizeof(restoreRoleAck));
}

void SessionDB2CS::HandleGateServMsg_UpdateOnlineState(void *pData)
{
    const auto *msg = static_cast<ProtoGS_UpdateOnlineState *>(pData);
    CDBManager::GetInstance()->UpdateOnlineState(msg->roleid, msg->state);
}

void SessionDB2CS::HandleMapServMsg(uint16_t protoid, void* pData)
{
    BEGIN_MSG_HANDLER()
        HANDLE_MSG(PROTO_MS_SYNC_ROLE_INFO_REQ, HandleMapServMsg_SyncRoleInfoReq)
        HANDLE_MSG(PROTO_MS_GET_GUILDS_REQ, HandleMapServMsg_GetGuildsReq)
        HANDLE_MSG(PROTO_MS_GET_GUILD_MEMBERS_REQ, HandleMapServMsg_GetGuildMembersReq)
        HANDLE_MSG(PROTO_MS_GET_GUILD_APPLICANTS_REQ, HandleMapServMsg_GetGuildApplicantsReq)
        HANDLE_MSG(PROTO_MS_GET_CUST_VAR_REQ, HandleMapServMsg_GetCustVarReq)
        HANDLE_MSG(PROTO_MS_SET_CUST_VAR, HandleMapServMsg_SetCustVar)
        HANDLE_MSG(PROTO_MS_SYNC_GUILD_APPLICANT, HandleMapServMsg_SyncGuildApplicant)
        HANDLE_MSG(PROTO_MS_SYNC_GUILD_MEMBER, HandleMapServMsg_SyncGuildMember)
        HANDLE_MSG(PROTO_MS_SYNC_GUILD_INFO, HandleMapServMsg_SyncGuildInfo)
        HANDLE_MSG(PROTO_MS_ADD_SYS_NEW_MAIL, HandleMapServMsg_AddSysNewMail)
        HANDLE_MSG(PROTO_MS_SYNC_MAIL_INFO_STATUS, HandleMapServMsg_SyncMailInfoStatus)
        HANDLE_MSG(PROTO_MS_MAIL_DEL_REQ, HandleMapServMsg_MailDelReq)
        HANDLE_MSG(PROTO_MS_SYNC_GUILD_RELATION, HandleMapServMsg_SyncGuildRelation)
        HANDLE_MSG(PROTO_MS_SYNC_ITEM_DYN_ATTRS, HandleMapServMsg_SyncItemDynAttrs)
        HANDLE_MSG(PROTO_MS_SYNC_ROLE_DYN_ATTRS, HandleMapServMsg_SyncRoleDynAttrs)
        HANDLE_MSG(PROTO_MS_GET_TRADE_DELEGATE_REQ, HandleMapServMsg_GetTradeDelegateReq)
        HANDLE_MSG(PROTO_MS_GET_TRADE_RECORDS_REQ, HandleMapServMsg_GetTradeRecordsReq)
        HANDLE_MSG(PROTO_MS_RECORDS_CANCEL_REQ, HandleMapServMsg_RecordsCancelReq)
        HANDLE_MSG(PROTO_MS_DELEGATE_CANCEL_REQ, HandleMapServMsg_DelegateCancelReq)
        HANDLE_MSG(PROTO_MS_DELEGATE_SELL_CMD, HandleMapServMsg_DelegateSellCmd)
        HANDLE_MSG(PROTO_MS_DELEGATE_BUY_CMD, HandleMapServMsg_DelegateBuyCmd)
        HANDLE_MSG(PROTO_MS_GET_MAIL_ATTACHMENT_REQ, HandleMapServMsg_GetMailAttachmentReq)
        HANDLE_MSG(PROTO_MS_AUCTION_HOUSE_REQ, HandleCenterServMsg_AuctionHouseReq)
        HANDLE_MSG(PROTO_MS_AUCTION_ADD_ITEM_INFO, HandleCenterServMsg_SynAuctionInfo)
        HANDLE_MSG(PROTO_MS_GET_CONSTANT_CFG_REQ, HandleCenterServMsg_GetConstantCfgReq)
        HANDLE_MSG(PROTO_MS_SET_SERVER_STATUS, HandleCenterServMsg_SetServerStatus)
        HANDLE_MSG(PROTO_MS_MALL_LIMIT_INFO_UPDATE, HandleCenterServMsg_UpdateMallLimitInfo)
        HANDLE_MSG(PROTO_MS_MALL_LIMIT_INFO_REQ, HandleCenterServMsg_GetMallLimitInfoReq)
        HANDLE_MSG(PROTO_MS_DELETE_MALL_REMAINED_DATA, HandleCenterServMsg_DeleteMallRemainedData)
        HANDLE_MSG(PROTO_MS_ADD_LOGIN_IP_TYPE, HandleCenterServMsg_AddLoginIpType)
        HANDLE_MSG(PROTO_MS_DEL_LOGIN_IP_TYPE, HandleCenterServMsg_DelLoginIpType)
        HANDLE_MSG(PROTO_MS_ADD_LOCK_PLAYER, HandleCenterServMsg_AddLockPlayer)
        HANDLE_MSG(PROTO_MS_UPDATE_SUPPORT_PLAYER, HandleCenterServMsg_UpdateSupportPlayer)
        HANDLE_MSG(PROTO_MS_ADD_LOCK_ROLE, HandleCenterServMsg_AddLockRole)
        HANDLE_MSG(PROTO_MS_DEL_LOCK_PLAYER, HandleCenterServMsg_DelLockPlayer)
        HANDLE_MSG(PROTO_MS_DEL_LOCK_ROLE, HandleCenterServMsg_DelLockRole)
        HANDLE_MSG(PROTO_MS_GET_PROHIBIT_CHAT_INFO_REQ, HandleCenterServMsg_GetProhibitChatInfo)
        HANDLE_MSG(PROTO_MS_DEL_PROHIBIT_INFO, HandleCenterServMsg_DelProhibitInfo)
        HANDLE_MSG(PROTO_MS_ADD_PROHIBIT_CHAT_INTO, HandleCenterServMsg_AddProhibitInfo)
        HANDLE_MSG(PROTO_MS_GET_WANTED_LIST_REQ, HandleMapServMsg_GetWantedListReq)
        HANDLE_MSG(PROTO_MS_POST_BOUNTY_REQ, HandleMapServMsg_PostBountyReq)
        HANDLE_MSG(PROTO_MS_CHECK_ROLE_EXISTENCE_REQ, HandleMapServMsg_CheckRoleExistenceReq)
        HANDLE_MSG(PROTO_MS_SAVE_GOODS_ISSUE_RECORD, HandleMapServMsg_SaveGoodsIssueRecord)
        HANDLE_MSG(PROTO_MS_GOODS_ISSUED_NTF, HandleMapServMsg_GoodsIssuedNtf)
        HANDLE_MSG(PROTO_MS_SYNC_GOODS_POST_RECORD, HandleMapServMsg_SyncGoodsPostRecord)
        HANDLE_MSG(PROTO_MS_REBATE_MONDY_USED_NTF, HandleMapServMsg_SetRebateMoneyUsedNtf)
        HANDLE_MSG(PROTO_MS_PLAYER_SET_NAME_REQ, HandleMapServMsg_PlayerSetNameReq)
        HANDLE_MSG(PROTO_MS_ITEM_TIP, HandleMapServMsg_ItemTip)
        HANDLE_MSG(PROTO_MS_ADD_TITLE, HandleMapServMsg_AddTitle)
        HANDLE_MSG(PROTO_MS_DEL_TITLE, HandleMapServMsg_DelTitle)
        HANDLE_MSG(PROTO_MS_TITLE_WEAR_TYPE, HandleMapServMsg_ChangeTitleWearType)
        HANDLE_MSG(PROTO_MS_SYNC_TITLE_INFO, HandleMapServMsg_SyncTitleInfo)
        HANDLE_MSG(PROTO_MS_ADD_PLAYER_PROHIBIT_CHAT, HandleMapServMsg_AddPlayerProhibitChat)
        HANDLE_MSG(PROTO_MS_DEL_PLAYER_PROHIBIT_CHAT, HandleMapServMsg_DelPlayerProhibitChat)
        HANDLE_MSG(PROTO_MS_RUNGMCMD, HandleMapServMsg_RumGMCmd)
        HANDLE_MSG(PROTO_MS_SYNC_CUST_LIST, HandleMapServMsg_SyncCustList)
        HANDLE_MSG(PROTO_MS_GET_CUST_LIST_REQ, HandleMapServMsg_GetCustListReq)
        HANDLE_MSG(PROTO_MS_SET_PLAYER_GENDER, HandleMapServMsg_SyncPlayerGender)



    END_MSG_HANDLER()
}

void SessionDB2CS::HandleMapServMsg_SyncRoleInfoReq(void *pData)
{
    auto pSyncRoleInfoReq = (ProtoMS_SyncRoleInfoReq *)pData;

    int result = CDBManager::GetInstance()->SyncRoleInfo(pSyncRoleInfoReq->roleBriefInfo,
        pSyncRoleInfoReq->roleExtraInfo, pSyncRoleInfoReq->roleSettings);
    if (result != 0) {
        LOG_ERROR("SyncRoleInfo failed with error %d", result);
    }
}

void SessionDB2CS::HandleCenterServMsg_GetConstantCfgReq(void* pData)
{
    auto* msg = static_cast<ProtoMS_GetConstantCfgReq*>(pData);

    CONSTANT_CFG_MAP constantCfgMap;
    auto result = CDBManager::GetInstance()->GetConstantCfg(constantCfgMap);
    if (result != 0) {
        LOG_ERROR("GetConstantCfg failed with error %d", result);
        return;
    }

    ProtoCS_GetConstantCfgAck cfgAck;
    cfgAck.custom << constantCfgMap;
    SendPkg(&cfgAck, sizeof(cfgAck));
}

void SessionDB2CS::HandleCenterServMsg_SetServerStatus(void* pData)
{
    auto* msg = static_cast<ProtoMS_SetServerStatus*>(pData);
    if (msg->status == server_status_close)
    {
        DBServer::GetInstance()->Quit();
    }
}

void SessionDB2CS::HandleMapServMsg_GetTradeDelegateReq(void* pData)
{
    auto* msg = static_cast<ProtoMS_GetTradeDelegateReq*>(pData);

    SP_BUY_DELEGATE_MAP buy;
    SP_SELL_DELEGATE_MAP sell;
    CDBManager::GetInstance()->GetTradeDelegate(buy, sell);

    ProtoCS_GetTradeBuyDelegateAck buyData;
    buyData.num = 0;
    buyData.packIdx = 0;
    if (buy.empty())
    {
        SendPkg(&buyData, sizeof(buyData));
    }
    else
    {
        SP_BUY_DELEGATE_MAP::iterator it = buy.begin();
        for (; it != buy.end(); )
        {
            buyData.delegateInfo[buyData.num++] = *(it->second);
            it++;
            if (buyData.num >= ProtoCS_GetTradeBuyDelegateAck::GTIA_MaxSize::Info_Size
                || it == buy.end())
            {
                buyData.packIdx++;
                // 最后一个包置0
                if (it == buy.end()) buyData.packIdx = 0;
                SendPkg(&buyData, sizeof(buyData));
                buyData.num = 0;
            }
        }
    }

    ProtoCS_GetTradeSellDelegateAck sellData;
    sellData.num = 0;
    sellData.packIdx = 0;
    if (sell.empty())
    {
        SendPkg(&sellData, sizeof(sellData));
    }
    else
    {
        SP_SELL_DELEGATE_MAP::iterator it = sell.begin();
        for (; it != sell.end(); )
        {
            sellData.delegateInfo[sellData.num++] = *(it->second);
            it++;
            if (sellData.num >= ProtoCS_GetTradeSellDelegateAck::GTIA_MaxSize::Info_Size
                || it == sell.end())
            {
                sellData.packIdx++;
                // 最后一个包置0
                if (it == sell.end()) sellData.packIdx = 0;
                SendPkg(&sellData, sizeof(sellData));
                sellData.num = 0;
            }
        }
    }
}

void SessionDB2CS::HandleMapServMsg_GetTradeRecordsReq(void* pData)
{
    auto* msg = static_cast<ProtoMS_GetTradeRecordsReq*>(pData);

    std::list<TRADE_RECORD> recordsList;
    CDBManager::GetInstance()->GetTradeRecords(msg->tradeRecordsExpireTime, recordsList);

    MSG_BUFFER_DATA(ProtoCS_GetTradeRecordsAck, data);

    data.num = 0;
    data.packIdx = 0;
    if (recordsList.empty())
    {
        SendPkg(&data, sizeof(data));
    }
    else
    {
        std::list<TRADE_RECORD>::iterator it = recordsList.begin();
        for (; it != recordsList.end();)
        {
            data.trade_record[data.num] = *it;
            data.num++;
            it++;
            if (data.num >= ProtoCS_GetTradeRecordsAck::GTRA_MaxSize::Info_Size
                || it == recordsList.end())
            {
                data.packIdx++;
                // 最后一个包置0
                if (it == recordsList.end()) data.packIdx = 0;
                SendPkg(&data, sizeof(data));
                data.num = 0;
            }
        }
    }
}

void SessionDB2CS::HandleMapServMsg_RecordsCancelReq(void* pData)
{
    auto* msg = (ProtoMS_RecordsCancelReq*)pData;
    CDBManager::GetInstance()->TradeRecordsCancel(msg->num, msg->trade_id);
}

void SessionDB2CS::HandleMapServMsg_DelegateCancelReq(void* pData)
{
    auto* msg = (ProtoMS_DelegateCancelReq*)pData;
    ProtoCS_DelegateCancelAck ack;
    ack.delegate_type = msg->delegate_type;
    ack.player_guid = msg->player_guid;
    ack.trade_id = msg->trade_id;
    ack.reason = msg->reason;
    ack.token = msg->token;
    int result = CDBManager::GetInstance()->TradeDelegateCancel(msg->trade_id, msg->delegate_type);
    ack.err_type = result;
    if (result != 0) 
    {
        LOG_ERROR("TradeDelegateCancel failed with error %d", result);
    }

    SendPkg(&ack, sizeof(ack));
}

void SessionDB2CS::HandleMapServMsg_DelegateSellCmd(void* pData)
{
    auto* msg = (ProtoMS_DelegateSellCmd*)pData;
    ProtoCS_DelegateSellAck ack;
    ack.token = msg->token;
    auto result = CDBManager::GetInstance()->TradeDelegateSell(*msg);
    ack.err_type = result;
    if (result != DBERR_OK) 
    {
        LOG_ERROR("TradeDelegateSell failed with error %d", result);
    }
    ack.sellItem = msg->sellItem;
    SendPkg(&ack, sizeof(ack)); 
}

void SessionDB2CS::HandleMapServMsg_DelegateBuyCmd(void* pData)
{
    auto* msg = (ProtoMS_DelegateBuyCmd*)pData;
    ProtoCS_DelegateBuyAck ack; 

    ack.token = msg->token;
    auto result = CDBManager::GetInstance()->TradeDelegateBuy(*msg);
    ack.err_type = result;
    if (result != DBERR_OK)
    {
        LOG_ERROR("TradeDelegateBuy failed with error %d", result);
    }
    ack.buyItem = msg->buyItem;
    SendPkg(&ack, sizeof(ack));
}

void SessionDB2CS::HandleCenterServMsg_MarketSellAck(void* pData)
{
    auto* msg = (ProtoCS_MarketSellAck*)pData;

    auto result = CDBManager::GetInstance()->TradeMarketSell(*msg);
    if (result != DBERR_OK)
    {
        LOG_ERROR("TradeMarketSell failed with error %d", result);
    }
}

void SessionDB2CS::HandleCenterServMsg_MarketBuyAck(void* pData)
{
    auto* msg = (ProtoCS_MarketBuyAck*)pData;

    auto result = CDBManager::GetInstance()->TradeMarketBuy(*msg);
    if (result != DBERR_OK)
    {
        LOG_ERROR("TradeMarketBuy failed with error %d", result);
    }
}

void SessionDB2CS::HandleCenterServMsg_UpdateMallLimitInfo(void* pData)
{
    auto* msg = (ProtoMS_MallLimitInfoUpdate*)pData;
    auto result = CDBManager::GetInstance()->UpdateMallInfo(*msg);
    if (result != DBERR_OK)
    {
        LOG_ERROR("MallInfoUpdate failed with error %d", result);
    }
}

void SessionDB2CS::HandleCenterServMsg_GetMallLimitInfoReq(void* pData)
{
    auto func = [this](std::vector<MALL_ITEM_INFO_BASE>& info, ProtoMS_MallLimitInfoUpdate& data) {
        int num = info.size();
        if(num == 0)SendPkg(&data, sizeof(data));
        while (num > 0)
        {
            if (num > 100)
            {
                data.num = 100;
            }
            else
            {
                data.num = num;
            }
            std::copy(info.begin(), info.begin() + data.num, data.data);
            info.erase(info.begin(), info.begin() + data.num);
            SendPkg(&data, sizeof(data));
            num -= 100;
        }
    };

    ProtoMS_MallLimitInfoUpdate data;
    std::vector<MALL_ITEM_INFO_BASE>info;
    auto result = CDBManager::GetInstance()->GetMallLimitInfo(mall_limit_type_all, info);
    data.limit_type = mall_limit_type_all;
    if (result != DBERR_OK)
    {
        LOG_ERROR("GetMallLimitAll failed with error %d", result);
    }
    func(info, data);
    
    info.clear();
    ProtoMS_MallLimitInfoUpdate _data;
    result = CDBManager::GetInstance()->GetMallLimitInfo(mall_limit_type_single, info);
    _data.limit_type = mall_limit_type_single;
    if (result != DBERR_OK)
    {
        LOG_ERROR("GetMallLimitSingle failed with error %d", result);
    }
    func(info, _data);
}

void SessionDB2CS::HandleCenterServMsg_DeleteMallRemainedData(void* pData)
{
    auto result = CDBManager::GetInstance()->DeleteMallRemainedData();
    if (result != DBERR_OK)
    {
        LOG_ERROR("delete mall data failed with error %d", result);
    }
}
void SessionDB2CS::HandleCenterServMsg_AddLoginIpType(void* pData)
{
    auto* msg = (ProtoMS_AddLoginIpType*)pData;
    auto result = CDBManager::GetInstance()->AddLoginIpType(msg->num,msg->ip,msg->ip_type);
    if (result != DBERR_OK)
    {
        LOG_ERROR("Add Login Ip failed with error %d", result);
        return;
    }
    ProtoDB_SyncLoginTypeToLS data;
    data.opt_type = ProtoDB_SyncLoginTypeToLS::add;
    data.num = msg->num;
    for (int i = 0; i < msg->num; ++i)
    {
        data.infos[i].ip = msg->ip[i];
        data.infos[i].type = msg->ip_type;
    }
    SendDataBySessionType(SESSION_TYPE_DB2LS, data);
}

void SessionDB2CS::HandleCenterServMsg_DelLoginIpType(void* pData)
{
    auto* msg = (ProtoMS_DelLoginIpType*)pData;
    auto result = CDBManager::GetInstance()->DelLoginIpType(msg->num,msg->ip,msg->ip_type);
    if (result != DBERR_OK)
    {
        LOG_ERROR("Add Login Ip failed with error %d", result);
        return;
    }
    ProtoDB_SyncLoginTypeToLS data;
    data.opt_type = ProtoDB_SyncLoginTypeToLS::del;
    data.num = msg->num;
    for (int i = 0; i < msg->num; ++i)
    {
        data.infos[i].ip = msg->ip[i];
        data.infos[i].type = msg->ip_type;
    }
    SendDataBySessionType(SESSION_TYPE_DB2LS, data);
}

void SessionDB2CS::HandleCenterServMsg_UpdateSupportPlayer(void* pData)
{
    auto* msg = (ProtoMS_UpdateSupportPlayer*)pData;
    auto result = CDBManager::GetInstance()->UpdateSupportPlayer(msg->num, msg->type, msg->name, msg->guid);
    if (result != DBERR_OK)
    {
        LOG_ERROR("update support player failed with error %d", result);
        return;
    }
    SendPkg(msg, sizeof(*msg));
}

void SessionDB2CS::HandleCenterServMsg_AddLockPlayer(void* pData)
{
    auto* msg = (ProtoMS_AddLockPlayer*)pData;
    auto result = CDBManager::GetInstance()->AddLockPlayer(msg->num,msg->name);
    if (result != DBERR_OK)
    {
        LOG_ERROR("Add lock player failed with error %d", result);
        return;
    }
}

void SessionDB2CS::HandleCenterServMsg_AddLockRole(void* pData)
{
    auto* msg = (ProtoMS_AddLockRole*)pData;
    auto result = CDBManager::GetInstance()->AddLockRole(msg->num,msg->guid);
    if (result != DBERR_OK)
    {
        LOG_ERROR("Add lock role failed with error %d", result);
        return;
    }
}

void SessionDB2CS::HandleCenterServMsg_DelLockPlayer(void* pData)
{
    auto* msg = (ProtoMS_DelLockPlayer*)pData;
    auto result = CDBManager::GetInstance()->DelLockPlayer(msg->num, msg->name);
    if (result != DBERR_OK)
    {
        LOG_ERROR("Del lock player failed with error %d", result);
        return;
    }
}

void SessionDB2CS::HandleCenterServMsg_DelLockRole(void* pData)
{
    auto* msg = (ProtoMS_DelLockRole*)pData;
    ProtoDB_DelLockRoleAck data;
    auto result = CDBManager::GetInstance()->DelLockRole(msg->num, msg->name, data);
    if (result != DBERR_OK)
    {
        LOG_ERROR("Del locked role failed with error %d", result);
        return;
    }
    SendPkg(&data, sizeof(data));
}

void SessionDB2CS::HandleCenterServMsg_GetProhibitChatInfo(void* pData)
{
    std::vector<PROHIBIT_CHAT_DATA>vec;
    auto result = CDBManager::GetInstance()->GetProhibitChatInfo(vec);
    if (result != DBERR_OK)
    {
        LOG_ERROR("get prohibit chat table failed with error %d", result);
        return;
    }
    if (vec.empty())return;
    uint64_t stamp = TimeHelper::GetInstance()->GetTimeStamp();
    auto iter = vec.begin();
    int delnum = 0;
    PROHIBIT_CHAT_DATA delinfo[100];
    // 删除过期的禁言
    while (iter != vec.end())
    {
        if (iter->time >= stamp)
        {
            delinfo[delnum] = *iter;
            ++delnum;
            if (delnum == 100)
            {
                CDBManager::GetInstance()->DelProhibitChatInfo(delnum,delinfo);
                memset(delinfo, 0, sizeof(delinfo));
            }
            iter = vec.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
    if (delnum > 0 && delnum < 100)
    {
        CDBManager::GetInstance()->DelProhibitChatInfo(delnum, delinfo);
    }

    // 返回还在禁言中的数据
    int num = vec.size();
    auto startIter = vec.begin();
    while (num > 0)
    {
        ProtoDB_GetProhibitChatInfoAck ack;
        if (num > 100)
        {
            ack.num = 100;
        }
        else
        {
            ack.num = num;
        }
        std::copy(startIter, startIter + ack.num, ack.infos);
        num -= 100;
        startIter += ack.num;
        SendDataBySessionType(SESSION_TYPE_DB2CS, ack);
    }
}

void SessionDB2CS::HandleCenterServMsg_DelProhibitInfo(void* pData)
{
    auto* msg = (ProtoMS_DelProhibitInfo*)pData;
    auto result = CDBManager::GetInstance()->DelProhibitChatInfo(msg->num,msg->infos);
    if (result != DBERR_OK)
    {
        LOG_ERROR("del prohibit infos failed with error %d", result);
    }
}

void SessionDB2CS::HandleCenterServMsg_AddProhibitInfo(void* pData)
{
    auto* msg = (ProtoMS_AddProhibitChatInfo*)pData;
    auto result = CDBManager::GetInstance()->AddProhibitChatInfo(msg->num, msg->infos);
    if (result != DBERR_OK)
    {
        LOG_ERROR("add prohibit infos failed with error %d", result);
    }
}

void SessionDB2CS::HandleCenterServMsg_AuctionHouseReq(void* pData)
{
    std::vector<AUCTION_HOUSE_ITEM_INFO>data;
    auto result = CDBManager::GetInstance()->GetAuctionHouseList(data);
    if (result != DBERR_OK)
    {
        LOG_ERROR("GetAuctionHouse failed with error %d", result);
    }
    int num = data.size();
    while (num > 0)
    {
        ProtoMS_SynAuctionItemInfo ack;
        if (num >= ProtoMS_SynAuctionItemInfo::max_num)
        {
            ack.num = ProtoMS_SynAuctionItemInfo::max_num;
        }
        else
        {
            ack.num = num;
        }
        std::copy(data.begin(), data.begin() + ack.num, ack.info);
        data.erase(data.begin(), data.begin() + ack.num);
        SendPkg(&ack, sizeof(ack));
        num -= ProtoMS_SynAuctionItemInfo::max_num;
    }
}

void SessionDB2CS::HandleCenterServMsg_EnterMSNtf(void* pData)
{
    ProtoCS_EnterMSNtf* ntf = (ProtoCS_EnterMSNtf*)pData;
    CDBManager::GetInstance()->UpdateLastSelectedRole(ntf->player_id, ntf->role_id);
    CDBManager::GetInstance()->UpdateRoleUpdateTime(ntf->role_id);
}

void SessionDB2CS::HandleCenterServMsg_SyncRoleInfoFromCS(void* pData)
{
    ProtoCS_SyncRoleInfo* ntf = (ProtoCS_SyncRoleInfo*)pData;
    auto result = CDBManager::GetInstance()->SyncRoleInfo(ntf);
    if (result != DBERR_OK)
    {
        LOG_ERROR("Sync Role Info From CS Failed! ,%d", result);
    }
}

void SessionDB2CS::HandleCenterServMsg_UpdateTables(void *pData)
{
    const auto *msg = static_cast<ProtoCS_UpdateTables *>(pData);
    CDBManager::GetInstance()->UpdateDBTables(msg->data, msg->len);
}

void SessionDB2CS::HandleCenterServMsg_GetMailAttachmentAck(void* pData)
{
    auto* msg = static_cast<ProtoCS_GetMailAttachmentAck*>(pData);
    CDBManager::GetInstance()->UpdateItemState(msg->item.base_info.guid, (uint32_t)item_state_unaccalimed);
}

void SessionDB2CS::HandleCenterServMsg_SynAuctionInfo(void* pData)
{
    auto* msg = (ProtoMS_SynAuctionItemInfo*)pData;
    auto result = CDBManager::GetInstance()->SyncAuctionItemInfo(*msg);
    if (result != DBERR_OK)
    {
        LOG_ERROR("TradeMarketBuy failed with error %d", result);
    }
}

void SessionDB2CS::HandleMapServMsg_GetMailAttachmentReq(void* pData)
{
    auto* msg = (ProtoMS_GetMailAttachmentReq*)pData;
    ProtoCS_GetMailAttachmentAck ack;
    ack.mail_guid = msg->mail_guid;
    ack.index = msg->index;

    auto result = CDBManager::GetInstance()->GetMailAttachment(*msg, ack);
    ack.err_type = result;
    if (result != DBERR_OK)
    {
        LOG_ERROR("GetMailAttachment failed with error %d, %llu, %llu", result, msg->role_guid, msg->item_guid);
    }
    SendPkg(&ack, sizeof(ack));
}

void SessionDB2CS::HandleMapServMsg_GetGuildsReq(void *pData)
{
    auto *msg = static_cast<ProtoMS_GetGuildsReq *>(pData);

    GUILD_MAP guilds;
    auto result = CDBManager::GetInstance()->GetGuilds(guilds);
    if (result != 0) {
        LOG_ERROR("GetGuilds failed with error %d", result);
        return;
    }

    ProtoCS_GetGuildsAck data;
    data.guilds = std::move(guilds);

    SendPkg(&data, sizeof(data));
}

void SessionDB2CS::HandleMapServMsg_GetGuildMembersReq(void *pData)
{
    auto *msg = static_cast<ProtoMS_GetGuildMembersReq *>(pData);

    GUILD_MEMBER_MAP members;
    auto result = CDBManager::GetInstance()->GetGuildMembers(members);
    if (result != 0) {
        LOG_ERROR("GetGuildMembers failed with error %d", result);
        return;
    }

    ProtoCS_GetGuildMembersAck data;
    data.members = std::move(members);

    SendPkg(&data, sizeof(data));
}

void SessionDB2CS::HandleMapServMsg_GetGuildApplicantsReq(void *pData)
{
    auto *msg = static_cast<ProtoMS_GetGuildApplicantsReq *>(pData);

    GUILD_APPLICANT_LIST applicants;
    auto result = CDBManager::GetInstance()->GetGuildApplicants(applicants);
    if (result != 0) {
        LOG_ERROR("GetGuildApplicants failed with error %d", result);
        return;
    }

    ProtoCS_GetGuildApplicantsAck data;
    data.applicants = std::move(applicants);

    SendPkg(&data, sizeof(data));
}

void SessionDB2CS::HandleMapServMsg_GetCustVarReq(void *pData)
{
    const auto *msg = static_cast<ProtoMS_GetCustVarReq *>(pData);

    CUST_VAR_SP_LIST vars;
    auto result = CDBManager::GetInstance()->GetCustVars(vars);
    if (result != DBERR_OK) {
        LOG_ERROR("GetCustVars failed with error %d", result);
        return;
    }

    ProtoDB_GetCustVarAck data;
    data.vars = &vars;

    SendPkg(&data, sizeof(data));
}

void SessionDB2CS::HandleMapServMsg_SetCustVar(void *pData)
{
    auto *msg = static_cast<ProtoMS_SetCustVar *>(pData);

    std::unique_ptr<CUST_VAR> var(msg->var);

    auto result = CDBManager::GetInstance()->SetCustVar(std::move(*var));
    if (result != DBERR_OK) {
        LOG_ERROR("SetCustVar failed with error %d", result);
    }
}

void SessionDB2CS::HandleMapServMsg_SyncGuildApplicant(void *pData)
{
    const auto *msg = static_cast<ProtoMS_SyncGuildApplicant *>(pData);

    SPGUILD_APPLICANT applicant(msg->applicant);

    auto result = CDBManager::GetInstance()->SyncGuildApplicant(applicant, msg->type);
    if (result != DBERR_OK) {
        LOG_ERROR("SyncGuildApplicant failed with error %d", result);
    }
}

void SessionDB2CS::HandleMapServMsg_SyncGuildMember(void *pData)
{
    const auto *msg = static_cast<ProtoMS_SyncGuildMember *>(pData);

    SPGUILD_MEMBER member(msg->member);

    auto result = CDBManager::GetInstance()->SyncGuildMember(member, msg->type);
    if (result != DBERR_OK) {
        LOG_ERROR("SyncGuildMember failed with error %d", result);
    }
}

void SessionDB2CS::HandleMapServMsg_SyncGuildInfo(void *pData)
{
    const auto *msg = static_cast<ProtoMS_SyncGuildInfo *>(pData);

    SPGUILD guild(msg->guild);

    auto result = CDBManager::GetInstance()->SyncGuildInfo(guild, msg->type);
    if (result != DBERR_OK) {
        LOG_ERROR("SyncGuildInfo failed with error %d", result);
    }
}

void SessionDB2CS::HandleMapServMsg_SyncGuildRelation(void *pData)
{
    const auto *msg = static_cast<ProtoMS_SyncGuildRelation *>(pData);

    auto result = CDBManager::GetInstance()->SyncGuildRelation(msg->type, msg->my_guild_guid,
        msg->peer_guild_guid, msg->relation);
    if (result != DBERR_OK) {
        LOG_ERROR("SyncGuildRelation failed with error %d", result);
    }
}

void SessionDB2CS::HandleMapServMsg_SyncItemDynAttrs(void *pData)
{
    const auto *msg = static_cast<ProtoMS_SyncItemDynAttrs *>(pData);

    std::unique_ptr<ITEM_DYN_ATTRS_LIST> attrsList(msg->attrs_list);

    auto result = CDBManager::GetInstance()->UpdateItemDynAttrs(*attrsList);
    if (result != DBERR_OK) {
        LOG_ERROR("UpdateItemDynAttrs failed with error %d", result);
    }
}

void SessionDB2CS::HandleMapServMsg_SyncRoleDynAttrs(void* pData)
{
    const auto* msg = static_cast<ProtoMS_SyncRoleDynAttrs*>(pData);

    std::unique_ptr<ROLE_DYN_ATTRS_LIST> attrsList(msg->attrs_list);

    auto result = CDBManager::GetInstance()->UpdateRoleDynAttrs(*attrsList);
    if (result != DBERR_OK) {
        LOG_ERROR("UpdateRoleDynAttrs failed with error %d", result);
    }
}

void SessionDB2CS::HandleCenterServMsg_GetTopListReq(void* pData)
{
    ProtoCS_TopListReq* req = (ProtoCS_TopListReq*)pData;
    // 栈空间不足，分多次发送
    //======================================================================================= 发送等级榜
    for (int i = 0; i <= 3; i++) {
        ProtoDB_GetTopListAck GetTopListAck;
        GetTopListAck.type = i;
        auto result = CDBManager::GetInstance()->GetTopList(GetTopListAck.rolelist,GetTopListAck.TopList, GetTopListAck.TopListNum, i);
        if (result != DBERR_OK) {
            LOG_ERROR("GetTopList failed with error %d", result);
            return;
        }
        SendPkg(&GetTopListAck, sizeof(GetTopListAck));
    }
}

void SessionDB2CS::HandleMapServMsg_AddSysNewMail(void* pData)
{
    auto msg = (ProtoMS_AddSysNewMail*)pData;
    ProtoDB_AddMailAck ack;
    std::vector<std::pair<uint64_t,uint64_t>>vec;
    auto result = CDBManager::GetInstance()->AddNewMail(*msg,vec);
    if (result != DBERR_OK) {
        LOG_ERROR("AddNewMail failed with error %d", result);
        ack.err_type = result;
        SendPkg(&ack, sizeof(ack));
        return;
    }
    if (vec.empty())
    {
        ack.err_type = ERR_MAIL_ADD_NONPLAYER;
        SendPkg(&ack, sizeof(ack));
        return;
    }

    for (int i = 0; i < vec.size(); ++i)
    {
        ack.infos[ack.num] = msg->infos;
        ack.infos[ack.num].playerguid = vec[i].first;
        ack.infos[ack.num].mail_id = vec[i].second;
        ++ack.num;
        if (ack.num == _countof(ack.infos))
        {
            SendPkg(&ack, sizeof(ack));
            ack.num = 0;
        }
    }
    if (ack.num > 0 && ack.num < _countof(ack.infos))
    {
        SendPkg(&ack, sizeof(ack));
    }
}

void SessionDB2CS::HandleMapServMsg_SyncMailInfoStatus(void* pData)
{
    auto msg = (ProtoMS_SyncMailInfoStatus*)pData;
    auto result = CDBManager::GetInstance()->SyncMailInfoStatus(msg->playerguid,msg->num,msg->info_status);
    if (result != DBERR_OK) {
        LOG_ERROR("SyncMailStatus failed with error %d", result);
        return;
    }
}

void SessionDB2CS::HandleMapServMsg_MailDelReq(void* pData)
{
    auto msg = (ProtoMS_DeleteMailReq*)pData;
    ProtoMS_DeleteMailAck ack;
    ack.mail_id = msg->id;
    ack.errcode = CDBManager::GetInstance()->DeleteMailByMailID(msg->id);
    ack.sessid = msg->sessid;
    SendPkg(&ack, sizeof(ack));
}

void SessionDB2CS::HandleMapServMsg_GetWantedListReq(void *pData)
{
    const auto *msg = static_cast<ProtoMS_GetWantedListReq *>(pData);

    WANTED_SP_LIST wantedList;
    auto result = CDBManager::GetInstance()->GetWantedList(wantedList);
    if (result != 0) {
        LOG_ERROR("GetWantedList failed with error %d", result);
        return;
    }

    ProtoMS_GetWantedListAck ack;
    ack.pwanted_list = &wantedList;
    SendPkg(&ack, sizeof(ack));
}

void SessionDB2CS::HandleMapServMsg_PostBountyReq(void *pData)
{
    const auto *msg = static_cast<ProtoMS_PostBountyReq *>(pData);

    uint32_t index = 0;
    uint64_t wanted_guid = 0;
    ProtoMS_PostBountyAck data;

    data.result = (uint8_t)CDBManager::GetInstance()->AddToWantedList(msg->wanted_by_guid, msg->wanted_name,
        msg->bounty, msg->desc, msg->ptime, wanted_guid, index);

    if (data.result != DBERR_OK) {
        LOG_ERROR("AddToWantedList failed with error %u", data.result);
    }

    data.index = index;
    data.wanted_by_guid = msg->wanted_by_guid;
    strcpy_s(data.wanted_by_name, _countof(data.wanted_by_name), msg->wanted_by_name);
    data.wanted_guid = wanted_guid;
    strcpy_s(data.wanted_name, _countof(data.wanted_name), msg->wanted_name);
    data.bounty = msg->bounty;
    strcpy_s(data.desc, _countof(data.desc), msg->desc);
    data.ptime = msg->ptime;

    SendPkg(&data, sizeof(data));
}

void SessionDB2CS::HandleMapServMsg_CheckRoleExistenceReq(void *pData)
{
    const auto *msg = static_cast<ProtoMS_CheckRoleExistenceReq *>(pData);

    ProtoMS_CheckRoleExistenceAck data;
    data.seq = msg->seq;
    data.by = msg->by;
    strcpy_s(data.name, _countof(data.name), msg->name);
    data.guid = msg->guid;

    int result = -1;

    if (msg->by == by_name)
        result = CDBManager::GetInstance()->CheckIfRoleExistByName(msg->name, data.exist, data.guid);
    else
        result = CDBManager::GetInstance()->CheckIfRoleExistByGUID(msg->guid, data.exist, data.name, _countof(data.name));

    if (result != ERR_OK) {
        LOG_ERROR("CheckIfRoleExist failed with error %d, by: %u", result, msg->by);
        return;
    }

    SendPkg(&data, sizeof(data));
}

void SessionDB2CS::HandleMapServMsg_SaveGoodsIssueRecord(void *pData)
{
    const auto *msg = static_cast<ProtoMS_SaveGoodsIssueRecord *>(pData);
    CDBManager::GetInstance()->SaveGoodsIssueRecord(msg->record);
}

void SessionDB2CS::HandleMapServMsg_GoodsIssuedNtf(void *pData)
{
    const auto *msg = static_cast<ProtoMS_GoodsIssuedNtf *>(pData);
    CDBManager::GetInstance()->SetGoodsIssuedFlag(msg->order_no, msg->num);
}

void SessionDB2CS::HandleMapServMsg_SyncGoodsPostRecord(void* pData)
{
    const auto* msg = static_cast<ProtoMS_SyncGoodsPostRecord*>(pData);
    CDBManager::GetInstance()->SyncGoodsPostRecord(msg->order_no, msg->num);
}

void SessionDB2CS::HandleMapServMsg_SetRebateMoneyUsedNtf(void* pData)
{
    auto* msg = static_cast<ProtoMS_RebateMoneyUsedNtf*>(pData);
    CDBManager::GetInstance()->SetRebateMoneyUsedFlag(msg->record);
}


void SessionDB2CS::HandleMapServMsg_PlayerSetNameReq(void* pData)
{
    const auto* msg = static_cast<ProtoMS_PlayerSetNameReq*>(pData);
    ProtoDB_PlayerSetNameAck data;
    uint64_t userid = 0;
    std::string orgName = "";
    data.guid = msg->guid;
    strcpy_s(data.name, _countof(data.name), msg->name);
    data.errcode = CDBManager::GetInstance()->PlayerSetName(msg->name, msg->guid , userid, orgName);
    data.userid = userid;
    strcpy_s(data.orgName, _countof(data.orgName), orgName);
    SendPkg(&data, sizeof(data));
}

void SessionDB2CS::HandleMapServMsg_ItemTip(void* pData)
{
    const auto* msg = static_cast<ProtoGS_ItemTip*>(pData);
    ProtoGS_ItemTipNtf data;
    data.guid = msg->guid;
    auto result = CDBManager::GetInstance()->GetItemTipInfo(msg->guid, msg->owner_guid, msg->item_guid,data.infos);
    if (result != ERR_OK) {
        LOG_WARN("get ItemTipInfo error!");
        return;
    }
    SendPkg(&data, sizeof(data));
}

void SessionDB2CS::HandleMapServMsg_AddTitle(void* pData)
{
    const auto* msg = static_cast<ProtoMS_AddTitle*>(pData);
    auto result = CDBManager::GetInstance()->AddTitle(msg->guid, msg->info);
    if (result != ERR_OK) {
        LOG_WARN("Add Title error!");
        return;
    }
}

void SessionDB2CS::HandleMapServMsg_DelTitle(void* pData)
{
    const auto* msg = static_cast<ProtoMS_DelTitle*>(pData);
    auto result = CDBManager::GetInstance()->DelTitle(msg->guid, msg->num, msg->id);
    if (result != ERR_OK) {
        LOG_WARN("Del Title error!");
        return;
    }
}

void SessionDB2CS::HandleMapServMsg_ChangeTitleWearType(void* pData)
{
    const auto* msg = static_cast<ProtoMS_TitleWearType*>(pData);
    auto result = CDBManager::GetInstance()->ChangeTitleWearType(msg->guid, msg->id, msg->wearType);
    if (result != ERR_OK) {
        LOG_WARN("Wear Title error!");
        return;
    }
}

void SessionDB2CS::HandleMapServMsg_SyncTitleInfo(void* pData)
{
    const auto* msg = static_cast<ProtoMS_SyncTitleInfo*>(pData);
    auto result = CDBManager::GetInstance()->SyncTitleInfo(msg->guid, msg->num, msg->info);
    if (result != ERR_OK) {
        LOG_WARN("Sync Title error!");
        return;
    }
}

void SessionDB2CS::HandleMapServMsg_AddPlayerProhibitChat(void* pData)
{
    const auto* msg = static_cast<ProtoMS_AddPlayerProhibitChat*>(pData);
    auto result = CDBManager::GetInstance()->AddPlayerProhibitChat(msg->userID, msg->stamp);
    if (result != ERR_OK) {
        LOG_WARN("Add player prohibit chat error!");
        return;
    }
}

void SessionDB2CS::HandleMapServMsg_DelPlayerProhibitChat(void* pData)
{
    const auto* msg = static_cast<ProtoMS_DelPlayerProhibitChat*>(pData);
    auto result = CDBManager::GetInstance()->DelPlayerProhibitChat(msg->userID);
    if (result != ERR_OK) {
        LOG_WARN("Del player prohibit chat err!");
        return;
    }
}

void SessionDB2CS::HandleMapServMsg_RumGMCmd(void *pData)
{
    const auto *msg = static_cast<ProtoMS_RunGMCmd *>(pData);
    GMCmdHandler::HandleCmd(msg->cmd, msg->param);
}

void SessionDB2CS::HandleMapServMsg_SyncCustList(void* pData)
{
    const auto* msg = static_cast<ProtoMS_SyncCustList*>(pData);
    auto result = CDBManager::GetInstance()->SyncCustListInfo(msg->optType, msg->num, msg->data);
    if (result != ERR_OK) {
        LOG_WARN("Sync Cust List Info Failed!");
        return;
    }
}

void SessionDB2CS::HandleMapServMsg_GetCustListReq(void* pData)
{
    std::vector<CUST_LIST_INFO> vec[CustType_Max];
    auto result = CDBManager::GetInstance()->GetCustListInfo(vec);
    if (result != ERR_OK) {
        LOG_WARN("Get Cust List Info Failed!");
        return;
    }

    for (int i = CustType_1; i < CustType_Max; ++i) {
        if (!vec[i].size())continue;
        auto data = std::make_shared<ProtoDB_GetCustListInfoAck>();
        for (auto& info : vec[i]) {
            data->data[data->num++] = info;
            if (data->num == 100)break;
        }
        SendDataBySessionType(SESSION_TYPE_DB2CS, *data);
    }
}

void SessionDB2CS::HandleMapServMsg_SyncPlayerGender(void* pData)
{
    const auto* msg = static_cast<ProtoMS_SetPlayerGender*>(pData);
    auto result = CDBManager::GetInstance()->SyncPlayerGender(msg->guid, msg->gender);
    if (result != ERR_OK) {
        LOG_WARN("Sync Player Gender Failed!");
        return;
    }
}

void SessionDB2CS::HandleCenterServMsg_GetRoleInfoReq(void* pData)
{
	ProtoCS_GetRoleInfoReq* pGetRoleInfoReq = (ProtoCS_GetRoleInfoReq*)pData;
	auto getRoleInfoAck = std::make_shared<ProtoCS_GetRoleInfoAck>();
	int result = CDBManager::GetInstance()->GetRoleInfo(pGetRoleInfoReq->role_id, (getRoleInfoAck->base_info),
        _countof(getRoleInfoAck->base_info));
	if (result != 0) {
		LOG_WARN("get RoleInfo error!");
	}

	getRoleInfoAck->role_id = pGetRoleInfoReq->role_id;
	getRoleInfoAck->token = pGetRoleInfoReq->token;
	SendPkg(getRoleInfoAck.get(), sizeof(*getRoleInfoAck));
}

void SessionDB2CS::HandleCenterServMsg_ClearRoleInfoReq(void* pData)
{
	ProtoCS_ClearRoleInfoNtf* pClearRoleInfoReq = (ProtoCS_ClearRoleInfoNtf*)pData;
	int result = CDBManager::GetInstance()->ClearRoleInfo(pClearRoleInfoReq->role_id);
	if (result != 0) {
		LOG_WARN("clear RoleInfo error!");
	}
}

void SessionDB2CS::HandleCenterServMsg_DeleteRoleInfoReq(void* pData)
{
	ProtoCS_DeleteRoleInfoNtf* pDeleteRoleInfoReq = (ProtoCS_DeleteRoleInfoNtf*)pData;
	int result = CDBManager::GetInstance()->DeleteRoleInfo(pDeleteRoleInfoReq->role_id, pDeleteRoleInfoReq->base_info);
	if (result != 0) {
		LOG_WARN("delete RoleInfo error!");
	}
}

void SessionDB2CS::HandleCenterServMsg_InsertRoleInfoReq(void* pData)
{
	ProtoCS_InsertRoleInfoNtf* pInsertRoleInfoReq = (ProtoCS_InsertRoleInfoNtf*)pData;
	int result = CDBManager::GetInstance()->InsertRoleInfo(pInsertRoleInfoReq->role_id, pInsertRoleInfoReq->base_info);
	if (result != 0) {
		LOG_WARN("insert RoleInfo error!");
	}
}

void SessionDB2CS::HandleCenterServMsg_UpdateRoleInfoReq(void* pData)
{
	ProtoCS_UpdateRoleInfoNtf* pUpdateRoleInfoReq = (ProtoCS_UpdateRoleInfoNtf*)pData;
	int result = CDBManager::GetInstance()->UpdateRoleInfo(pUpdateRoleInfoReq->role_id, pUpdateRoleInfoReq->base_info);
	if (result != 0) {
		LOG_WARN("update RoleInfo error!");
	}
}

void SessionDB2CS::HandleCenterServMsg_SyncSkillReq(void *pData)
{
    auto pSyncSkillReq = (ProtoCS_SyncSkillReq *)pData;

    LOG_TRACE("[SyncSkill] roleid: %" PRIu64 ", remove: %u, add: %u, update: %u", pSyncSkillReq->roleid,
        pSyncSkillReq->removeSkillNum, pSyncSkillReq->addSkillNum, pSyncSkillReq->updateSkillNum);

    int result = CDBManager::GetInstance()->SyncSkillInfo(pSyncSkillReq->roleid, pSyncSkillReq->removeSkillInfo,
        pSyncSkillReq->removeSkillNum, pSyncSkillReq->addSkillInfo, pSyncSkillReq->addSkillNum,
        pSyncSkillReq->updateSkillInfo, pSyncSkillReq->updateSkillNum);

    if (result != 0) {
        LOG_ERROR("SyncSkillInfo failed with error %d", result);
    }
}

void SessionDB2CS::HandleCenterServMsg_SyncBuffReq(void *pData)
{
    auto pSyncBuffReq = (ProtoCS_SyncBuffReq *)pData;

    LOG_TRACE("[SyncBuff] roleid: %" PRIu64 ", remove: %u, add: %u, update: %u", pSyncBuffReq->roleid,
        pSyncBuffReq->removeNum, pSyncBuffReq->addNum, pSyncBuffReq->updateNum);

    int result = CDBManager::GetInstance()->SyncBuffInfo(pSyncBuffReq->roleid, pSyncBuffReq->removeIndex,
        pSyncBuffReq->removeNum, pSyncBuffReq->addBuffInfo, pSyncBuffReq->addNum,
        pSyncBuffReq->updateBuffInfo, pSyncBuffReq->updateNum);

    if (result != 0) {
        LOG_ERROR("SyncBuffInfo failed with error %d", result);
    }
}

void SessionDB2CS::HandleCenterServMsg_SyncQuestReq(void *pData)
{
    auto *pSyncQuestReq = static_cast<ProtoCS_SyncQuestReq *>(pData);

    LOG_TRACE("[SyncQuest] roleid: %" PRIu64 ", remove: %u, add: %u, update: %u", pSyncQuestReq->roleid,
        pSyncQuestReq->remove_num, pSyncQuestReq->add_num, pSyncQuestReq->update_num);

    int result = CDBManager::GetInstance()->SyncQuestInfo(
        pSyncQuestReq->roleid, pSyncQuestReq->quest_info,
        pSyncQuestReq->remove_achev, pSyncQuestReq->remove_num,
        pSyncQuestReq->add_achev, pSyncQuestReq->add_num,
        pSyncQuestReq->update_achev, pSyncQuestReq->update_num);

    if (result != 0) {
        LOG_ERROR("SyncQuestInfo failed with error %d", result);
    }
}

void SessionDB2CS::HandleCenterServMsg_SyncPlayerCustVar(void *pData)
{
    auto *msg = static_cast<ProtoCS_SyncPlayerCustVar *>(pData);

    std::unique_ptr<CUST_VAR_LIST> add(msg->add);
    std::unique_ptr<CUST_VAR_LIST> remove(msg->remove);
    std::unique_ptr<CUST_VAR_LIST> update(msg->update);

    auto result = CDBManager::GetInstance()->SyncPlayerCustVar(std::move(*add),
        std::move(*remove), std::move(*update));

    if (result != DBERR_OK) {
        LOG_ERROR("SyncPlayerCustVar failed with error %d", result);
    }
}

void SessionDB2CS::HandleCenterServMsg_SyncItemCustVar(void *pData)
{
    auto *msg = static_cast<ProtoCS_SyncItemCustVar *>(pData);

    std::unique_ptr<CUST_VAR_SP_LIST> add(msg->add);
    std::unique_ptr<CUST_VAR_SP_LIST> remove(msg->remove);
    std::unique_ptr<CUST_VAR_SP_LIST> update(msg->update);

    auto result = CDBManager::GetInstance()->SyncItemCustVar(add.get(), remove.get(), update.get());

    if (result != DBERR_OK) {
        LOG_ERROR("SyncItemCustVar failed with error %d", result);
    }
}

void SessionDB2CS::HandleCenterServMsg_SyncQuickBarSet(void* pData)
{
    auto* msg = static_cast<ProtoCS_SyncQuickBarSet*>(pData);
	auto result = CDBManager::GetInstance()->SyncQuickBarSet(msg);
	if (result != DBERR_OK) {
		LOG_ERROR("SyncQuickBarSet failed with error %d", result);
	}
}

void SessionDB2CS::HandleCenterServMsg_SyncDgnBindInfoSet(void* pData)
{
    auto* msg = static_cast<ProtoCS_SyncDgnBindInfo*>(pData);
    auto result = CDBManager::GetInstance()->SyncDgnBindInfo(msg);
    if (result != DBERR_OK) {
        LOG_ERROR("SyncDgnBindInfo failed with error %d", result);
    }
}

void SessionDB2CS::HandleCenterServMsg_GetMailInfo(void* pData)
{
    auto data = (ProtoCS_GetMailInfo*)pData;
    std::list<MAIL_INFO>mail_list;

    auto result = CDBManager::GetInstance()->GetMailInfo(data->playerguid, mail_list);
    if (result != DBERR_OK) {
        LOG_ERROR("GetMailInfo failed with error %d", result);
    }

    ProtoDB_GetMailInfoAck ack;
    for (auto&i:mail_list) {
        if (i.status & mail_status_delete)continue;
        ack.infos[ack.num] = i;
        ++ack.num;
        if (ack.num == _countof(ack.infos))
        {
            SendPkg(&ack, sizeof(ack));
            ack.num = 0;
        }
    } 
    if (ack.num > 0 && ack.num < _countof(ack.infos))
    {
        SendPkg(&ack, sizeof(ack));
    }
}
