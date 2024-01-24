#include "stdafx.h"
#include "User.h"
#include "ILogHelper.h"
#include "CNetManager.h"
#include "SessionFactory.h"
#include "UserMgr.h"
#include "ProtoMS.h"
#include "ProtoCS.h"
#include "ProtoDB.h"
#include "ProtoGS.h"
#include "GameMallMgr.h"
#include "fb_structs_generated.h"
#include "CenterServer.h"

User::User()
{
	Init(0);
}

User::User(uint64_t id)
{
	Init(id);
}

User::~User()
{

}

void User::Init(uint64_t id)
{
	mID = id;
	mToken = 0;                  //
	mGS2LSSessionID = 0;      // 网
	mGS2CLSessionID = 0;
	mCS2GSSessionID = 0;
	mMS2GSSessionID = 0;

	mEnterType = -1;
	mFangChenMi = -1;
	mClientType = -1;

	mUserName = "";
	mIP = 0;
	mHardware = "";
	mOnlineState = 0;
	mLastSelectRole = 0;
	mChannel = "";
}

void  User::AddRoleDataInfo(ROLE_BRIEF_INFO& info)
{
	if (info.status == role_status_new || info.status == role_status_normal)
	{
		auto iter = mRoleDataMap.find(info.guid);
		if (iter == mRoleDataMap.end())
		{
			mRoleDataMap[info.guid].SetBriefInfo(info);
		}
		mDeleteRoleDataMap.erase(info.guid);
	}
	else if (info.status == role_status_deleted || info.status == role_status_new_deleted)
	{
		auto iter = mDeleteRoleDataMap.find(info.guid);
		if (iter == mDeleteRoleDataMap.end())
		{
			mDeleteRoleDataMap[info.guid].SetBriefInfo(info);
		}
		mRoleDataMap.erase(info.guid);
	}
}

void  User::RemoveRoleDataInfo(uint64_t role_id, int32_t status)
{
	auto iter = mRoleDataMap.find(role_id);
	if (iter != mRoleDataMap.end())
	{
		auto& info = iter->second.GetBriefInfo();
		info.status = status;
		mDeleteRoleDataMap[role_id].SetBriefInfo(info);
		mRoleDataMap.erase(iter);
	}
	if(status == role_status_permanent_deleted)
		mDeleteRoleDataMap.erase(role_id);
}

const ROLE_BRIEF_INFO& User::GetRoleBirefInfo(uint64_t role_id)
{
	auto iter = mRoleDataMap.find(role_id);
	if (iter != mRoleDataMap.end()) return iter->second.GetBriefInfo();
	iter = mDeleteRoleDataMap.find(role_id);
	if (iter != mDeleteRoleDataMap.end()) return iter->second.GetBriefInfo();

	static ROLE_BRIEF_INFO info;
	memset(&info, 0, sizeof(info));
	return info;
}

std::list<std::unique_ptr<ITEM_INFO>>& User::GetRoleAllItem(uint64_t id)
{
	return mRoleDataMap[id].GetItemList();
};

void User::AddRoleItem(uint64_t id, std::unique_ptr<ITEM_INFO>& item)
{
	auto it = mRoleDataMap.find(id);
	if (it != mRoleDataMap.end()) {
		it->second.AddItem(item);
	}
}

void User::DelRoleItem(const uint64_t roleID, const uint64_t itemID) 
{
	auto it = mRoleDataMap.find(roleID);
	if (it != mRoleDataMap.end()) {
		it->second.DelItem(itemID);
	}
}

ITEM_INFO* User::GetRoleSingleItem(const uint64_t roleID, const uint64_t itemID)
{
	auto it = mRoleDataMap.find(roleID);
	if (it != mRoleDataMap.end()) {
		return it->second.GetItem(itemID);
	}
	return nullptr;
}

bool User::CompareItem(const ITEM_INFO* localitem, const ITEM_INFO* recvitem)
{
	if (localitem->base_info.guid != recvitem->base_info.guid)
		return false;
	if (!strcmp(localitem->base_info.name, recvitem->base_info.name))
		return false;
	if (localitem->base_info.id != recvitem->base_info.id)
		return false;
	if (localitem->base_info.role != recvitem->base_info.role)
		return false;
	if (localitem->base_info.site != recvitem->base_info.site)
		return false;
	if (localitem->base_info.amount != recvitem->base_info.amount)
		return false;
	if (localitem->base_info.durability != recvitem->base_info.durability)
		return false;
	if (localitem->base_info.max_durability != recvitem->base_info.max_durability)
		return false;
	if (localitem->base_info.use_count != recvitem->base_info.use_count)
		return false;
	if (localitem->base_info.is_bound != recvitem->base_info.is_bound)
		return false;
	if (localitem->base_info.life != recvitem->base_info.life)
		return false;
	if (localitem->base_info.item_cfg_var.color != recvitem->base_info.item_cfg_var.color)
		return false;
	if (localitem->base_info.item_cfg_var.icon != recvitem->base_info.item_cfg_var.icon)
		return false;
	if (localitem->base_info.item_cfg_var.quality != recvitem->base_info.item_cfg_var.quality)
		return false;
	if (localitem->base_info.item_cfg_var.subtype != recvitem->base_info.item_cfg_var.subtype)
		return false;
	return true;
}

bool User::CompareItem(const ITEM_INFO* localitem, const ProtoMS_SendSyncItemNtf* recvitem)
{
	if (localitem->base_info.guid != recvitem->Guid)
		return false;
	if (strcmp(localitem->base_info.name, recvitem->Name))
		return false;
	if (localitem->base_info.id != recvitem->Tempid)
		return false;
	if (localitem->base_info.role != recvitem->Roleid)
		return false;
	if (localitem->base_info.site != recvitem->Site)
		return false;
	if (localitem->base_info.amount != recvitem->Amount)
		return false;
	if (localitem->base_info.durability != recvitem->Durability)
		return false;
	if (localitem->base_info.max_durability != recvitem->Max_durability)
		return false;
	if (localitem->base_info.use_count != recvitem->Use_count)
		return false;
	if (localitem->base_info.is_bound != recvitem->IsBind)
		return false;
	if (localitem->base_info.life != recvitem->Life)
		return false;
	if (localitem->base_info.item_cfg_var.color != recvitem->ItemCfgVar.color)
		return false;
	if (localitem->base_info.item_cfg_var.icon != recvitem->ItemCfgVar.icon)
		return false;
	if (localitem->base_info.item_cfg_var.quality != recvitem->ItemCfgVar.quality)
		return false;
	if (localitem->base_info.item_cfg_var.subtype != recvitem->ItemCfgVar.subtype)
		return false;
	return true;
}

void User::SetSkillList(const uint64_t& nRoleID, const SKILL_INFO* pSkillInfo, uint16_t nNum)
{
    auto it = mRoleDataMap.find(nRoleID);
	if (it == mRoleDataMap.end()) return;
    it->second.SetSkillList(pSkillInfo, nNum);
}

uint16_t User::GetSkillList(const uint64_t& nRoleID, SKILL_INFO* pSkillInfo, uint16_t nNum)
{
    if (!pSkillInfo || nNum == 0) return 0;

    auto itor = mRoleDataMap.find(nRoleID);
    if (itor == mRoleDataMap.end()) return 0;

    const auto& skillList = itor->second.GetSkillList();

    uint16_t n = 0;
    for (auto &it : skillList) {
        pSkillInfo[n] = it;
        if (++n == nNum) break;
    }

    return n;
}

void User::SyncSkillList(const uint64_t &nRoleID, const SKILL_INFO *pSkillInfo, uint16_t nNum)
{
    if (!pSkillInfo) return;

    auto itor = mRoleDataMap.find(nRoleID);
    if (itor == mRoleDataMap.end()) return;

    const auto &skillList = itor->second.GetSkillList();

    using SkillMap = std::map<uint16_t, const SKILL_INFO *>;

    SkillMap newSkillList, oldSkillList;

    for (uint16_t i = 0; i < nNum; ++i)
        newSkillList[pSkillInfo[i].id] = pSkillInfo + i;

    for (auto &it : skillList)
        oldSkillList[it.id] = &it;

	MSG_BUFFER_DATA(ProtoCS_SyncSkillReq, syncSkillReq);
    auto &nRemoveSkillNum = syncSkillReq.removeSkillNum;
    auto &nAddSkillNum = syncSkillReq.addSkillNum;
    auto &nUpdateSkillNum = syncSkillReq.updateSkillNum;
    nRemoveSkillNum = 0;
    nAddSkillNum = 0;
    nUpdateSkillNum = 0;

    for (auto &oldItor : oldSkillList) {

        auto nOldSkillID = oldItor.first;

        auto newItor = newSkillList.find(nOldSkillID);

        if (newItor == newSkillList.end()) {
            if (nRemoveSkillNum < _countof(syncSkillReq.removeSkillInfo))
                syncSkillReq.removeSkillInfo[nRemoveSkillNum++] = *oldItor.second;
        }
        else if (oldItor.second->active != newItor->second->active 
				 || oldItor.second->proficiency != newItor->second->proficiency
                 || strcmp(oldItor.second->cfg, newItor->second->cfg)) {
            if (nUpdateSkillNum < _countof(syncSkillReq.updateSkillInfo))
                syncSkillReq.updateSkillInfo[nUpdateSkillNum++] = *newItor->second;
        }

        if (newItor != newSkillList.end()) newSkillList.erase(newItor);
    }

    for (auto &newItor : newSkillList) {

        if (nAddSkillNum < _countof(syncSkillReq.addSkillInfo))
            syncSkillReq.addSkillInfo[nAddSkillNum++] = *newItor.second;
    }

    if (nRemoveSkillNum == 0 && nAddSkillNum == 0 && nUpdateSkillNum == 0) return;

    syncSkillReq.roleid = nRoleID;
    SendDataBySessionType(SESSION_TYPE_CS2DB, syncSkillReq);

    SetSkillList(nRoleID, pSkillInfo, nNum);
}

std::unique_ptr<ITEM_INFO> User::AppendUserItemInfo(void* pdata)
{
	auto pntf = (ProtoMS_SendSyncItemNtf*)pdata;
	auto info = std::make_unique<ITEM_INFO>();
	info->base_info.guid = pntf->Guid;
	memcpy(info->base_info.name, pntf->Name, _countof(pntf->Name));
	info->base_info.id = pntf->Tempid;
	info->base_info.role = pntf->Roleid;
	info->base_info.site = pntf->Site;
	info->base_info.amount = pntf->Amount;
	info->base_info.durability = pntf->Durability;
	info->base_info.max_durability = pntf->Max_durability;
	info->base_info.use_count = pntf->Use_count;
	info->base_info.is_bound = pntf->IsBind;
	info->base_info.life = pntf->Life;
	//info->custom.num = 0;
	info->base_info.item_cfg_var = pntf->ItemCfgVar;
	//memset(info->custom.buf, 0, _countof(info->custom.buf));
	return info;
}

void User::SyncUserItemInfo(ITEM_INFO* info, void* pdata)
{
	auto pntf = (ProtoMS_SendSyncItemNtf*)pdata;
	info->base_info.guid = pntf->Guid;
	memcpy(info->base_info.name, pntf->Name, _countof(pntf->Name));
	info->base_info.id = pntf->Tempid;
	info->base_info.role = pntf->Roleid;
	info->base_info.site = pntf->Site;
	info->base_info.amount = pntf->Amount;
	info->base_info.durability = pntf->Durability;
	info->base_info.max_durability = pntf->Max_durability;
	info->base_info.use_count = pntf->Use_count;
	info->base_info.is_bound = pntf->IsBind;
	info->base_info.life = pntf->Life;
	info->base_info.item_cfg_var = pntf->ItemCfgVar;
}

std::string& User::GetInfo(const uint64_t& nRoleID)
{
	return mRoleDataMap[nRoleID].GetInfo();
}

void User::SetInfo(uint64_t id, const std::string& str)
{
	mRoleDataMap[id].SetInfo(str);
}

void User::SendInsertItemNtf(void* pData)
{
	auto pntf = (ProtoMS_SendSyncItemNtf*)pData;
	ProtoCS_InsertItemNtf insert;
	insert.base_info.guid = pntf->Guid;
	memcpy(insert.base_info.name, pntf->Name, _countof(pntf->Name));
	insert.base_info.id = pntf->Tempid;
	insert.base_info.role = pntf->Roleid;
	insert.base_info.site = pntf->Site;
	insert.base_info.amount = pntf->Amount;
	insert.base_info.durability = pntf->Durability;
	insert.base_info.max_durability = pntf->Max_durability;
	insert.base_info.use_count = pntf->Use_count;
	insert.base_info.is_bound = pntf->IsBind;
	insert.base_info.life = pntf->Life;
	insert.base_info.item_cfg_var = pntf->ItemCfgVar;
	SendDataBySessionType(SESSION_TYPE_CS2DB, insert);
}

void User::SendUpdateItemNtf(void* pData)
{
	auto pntf = (ProtoMS_SendSyncItemNtf*)pData;
	ProtoCS_UpdateItemNtf update;
	update.base_info.guid = pntf->Guid;
	memcpy(update.base_info.name, pntf->Name, _countof(pntf->Name));
	update.base_info.id = pntf->Tempid;
	update.base_info.role = pntf->Roleid;
	update.base_info.site = pntf->Site;
	update.base_info.amount = pntf->Amount;
	update.base_info.durability = pntf->Durability;
	update.base_info.max_durability = pntf->Max_durability;
	update.base_info.use_count = pntf->Use_count;
	update.base_info.is_bound = pntf->IsBind;
	update.base_info.life = pntf->Life;
	update.base_info.item_cfg_var = pntf->ItemCfgVar;
	SendDataBySessionType(SESSION_TYPE_CS2DB, update);
}

void User::SendDelItemNtf(uint64_t roleGUID, uint64_t itemGUID)
{
    ProtoCS_DeleteItemNtf data;
    data.guid = itemGUID;
    data.role_id = roleGUID;
    SendDataBySessionType(SESSION_TYPE_CS2DB, data);
}

void User::DeleteItem(uint64_t roleGUID, uint64_t itemGUID, uint8_t tradeDel)
{
    auto &items = GetRoleAllItem(roleGUID);
    auto it = std::find_if(items.begin(), items.end(), [&](const auto &item) {
        return item->base_info.guid == itemGUID;
	});
    if (it == items.end()) return;
    items.erase(it);

	DeleteItemCustVars(roleGUID, itemGUID);
	DeleteItemAttrsList(roleGUID, itemGUID);

    SendDelItemNtf(roleGUID, itemGUID);
}

void User::HandleMapServMsg_SendSyncItemNtf(void* pData)
{
	auto pntf = (ProtoMS_SendSyncItemNtf*)pData;
	auto it = mRoleDataMap.find(pntf->role_guid);
	if (it == mRoleDataMap.end()) {
		LOG_ERROR("find role data failed. roleGUID:%" PRIu64, pntf->role_guid);
		return;
	}
	// 不存在该物品则插入
	auto item = it->second.GetItem(pntf->Guid);
	if (nullptr == item) {
		auto append = AppendUserItemInfo(pntf);
		AddRoleItem(pntf->Roleid, append);
		SendInsertItemNtf(pntf);
	}
	// 存在如果数据不一样则是更新
	else if(!CompareItem(item, pntf)) {
		SyncUserItemInfo(item, pntf);
		SendUpdateItemNtf(pntf);
	}
}

bool User::CompareQuickBar(const QUICK_BAR_INFO* localitem, const QUICK_BAR_INFO* recvitem)
{
	if (localitem->guid != recvitem->guid)
		return false;
	if (localitem->id != recvitem->id)
		return false;
	if (localitem->slot != recvitem->slot)
		return false;
	if (localitem->type != recvitem->type)
		return false;
	return true;
}


void User::HandleMapServMsg_SyncQuickBarSet(void* pData)
{
	auto pntf = (ProtoMS_QuickBarSet*)pData;
	auto it = mRoleDataMap.find(pntf->role_id);
	if (it == mRoleDataMap.end()) 
	{
		LOG_ERROR("find role data failed. roleGUID:%" PRIu64, pntf->role_id);
		return;
	}
	//ProtoCS_SyncQuickBarSet req;
	//req.num=pntf->num;
	for (int i = 0; i < pntf->num; ++i){
		//req.info[i].role_id = pntf->role_id;
		//req.info[i].quick.guid = pntf->info[i].guid;
		//req.info[i].quick.id = pntf->info[i].id;
		//req.info[i].quick.slot = pntf->info[i].slot;
		//req.info[i].quick.type = pntf->info[i].type;
		auto item = it->second.GetQuickBarSet((pntf->info)[i].slot);
		if (nullptr == item) {
			AddQuickBar(pntf->role_id, pntf->info[i]);
			it->second.UpdateQuickBarSetFlag(pntf->info[i].slot);
		}
		else {
			if (!CompareQuickBar(item, &((pntf->info)[i]))) {
				UpdateQuickBar(item, &((pntf->info)[i]));
				it->second.UpdateQuickBarSetFlag(pntf->info[i].slot);
			}
		}
	}
	//SendDataBySessionType(SESSION_TYPE_CS2DB, req);

}

 void User::AddQuickBar(uint64_t id,QUICK_BAR_INFO& item)
 {
	 auto it = mRoleDataMap.find(id);
	 if (it != mRoleDataMap.end()) {
		 it->second.AddBar(item);
	 }
 }

 void User::UpdateQuickBar(QUICK_BAR_INFO* info, void* pdata)
 {
	 auto pntf = (QUICK_BAR_INFO*)pdata;
	 info->guid = pntf->guid;
	 info->id = pntf->id;
	 info->slot = pntf->slot;
	 info->type = pntf->type;
 }

 void User::SetQuickBarSetNtf(void* pData)
 {
	 auto pntf=(ProtoDB_QuickBarSetNtf*)pData;
	 auto it = mRoleDataMap.find(pntf->role_id);
	 if (it != mRoleDataMap.end()) {
		 it->second.syncQuickBarSetNtf(pntf->info, pntf->num);
	 }
 }

 void User::ChangePlayerNameInfo(uint64_t guid, const std::string& name, const std::string& orgName)
 {
	 auto it = mRoleDataMap.find(guid);
	 if (it == mRoleDataMap.end()) return;
	 auto &brefInfo = it->second.GetBriefInfo();
	 strcpy_s(brefInfo.name, _countof(brefInfo.name), name);

	 // 同步名字信息
	 AuctionHouseMgr::GetInstance()->ChangeNameInfo(guid, name);
	 GuildData::GetInstance()->ChangeNameInfo(guid, name);
	 TopList::GetInstance()->ChangeNameInfo(guid, name, orgName);
	 TradeData::GetInstance()->ChangeNameInfo(guid, name);
	 WantedList::GetInstance()->ChangeNameInfo(guid, name);
 }

 void User::HandleMapServMsg_SyncDgnBindInfo(void* pData)
 {
	 auto pntf = (ProtoMS_DgnBindInfo*)pData;
	 auto it = mRoleDataMap.find(pntf->roleId);
	 if (it == mRoleDataMap.end()) 
	 {

		 LOG_ERROR("find role data failed. roleGUID:%" PRIu64, pntf->roleId);
		 return;
	 }
	 for (uint16_t i = 0; i < pntf->num; ++i)
	 {
		 it->second.AddTmpDgnBindInfo(pntf->info[i]);
	 }
	 if (0 != pntf->packIdx)
	 {
		 return;
	 }

	 it->second.SwapDgnBindInfoList();

	 auto& dgnInfoList = it->second.GetDgnBindInfoList();
	 ProtoCS_SyncDgnBindInfo req;
	 req.packIdx = 0;
	 req.num = 0;
	 req.roleId = pntf->roleId;
	 if (dgnInfoList.empty())
	 {
		 SendDataBySessionType(SESSION_TYPE_CS2DB, req);
		 return;
	 }
	 bool first = true;
	 for (auto iter = dgnInfoList.begin(); iter != dgnInfoList.end();)
	 {
		 req.info[req.num++] = *iter++;
		 if (req.num >= ProtoCS_SyncDgnBindInfo::DBI_MaxSize::Info_Size
			 || iter == dgnInfoList.end())
		 {
			 if (!first)// 第一条消息置0
			 {
				 req.packIdx++;
			 }
			 first = false;
			 SendDataBySessionType(SESSION_TYPE_CS2DB, req);
			 req.num = 0;
		 }
	 }
 }

 void User::SetDgnBindInfoNtf(void* pData)
 {
	 auto pntf = (ProtoDB_DgnBindInfoNtf*)pData;
	 auto it = mRoleDataMap.find(pntf->roleId);
	 if (it != mRoleDataMap.end()) 
	 {
		 it->second.syncDgnBindInfoNtf(pntf->info, pntf->num);
	 }
 }

void User::HandleMapServMsg_GetRoleInfoReq(void* pdata)
{
	auto req = (ProtoMS_GetRoleInfoReq*)pdata;
	auto& info = GetInfo(req->role_id);
	if (!info.empty()) {
		ProtoMS_GetRoleInfoAck ack;
		ack.role_id = req->role_id;
		memcpy(ack.base_info, info.c_str(), sizeof(ack.base_info));
		SendDataBySessionType(SESSION_TYPE_CS2MS, ack);
		return;
	}
	ProtoCS_GetRoleInfoReq ntf;
	ntf.role_id = req->role_id;
	ntf.token = req->token;
	SendDataBySessionType(SESSION_TYPE_CS2DB, ntf);
}

void User::HandleMapServMsg_ClearRoleInfoNtf(void* pData)
{
	auto req = (ProtoMS_ClearRoleInfoNtf*)pData;
	auto& info = GetInfo(req->role_id);
	info.erase();

	ProtoCS_ClearRoleInfoNtf ntf;
	ntf.role_id = req->role_id;
	SendDataBySessionType(SESSION_TYPE_CS2DB, ntf);
}

void User::HandleMapServMsg_DelRoleInfoNtf(void* pData)
{
	auto req = (ProtoMS_DeleteRoleInfoNtf*)pData;
	auto& info = GetInfo(req->role_id);
	auto it = info.find(req->base_info);
	if (it  != std::string::npos)
	{
		info.erase(it, strlen(req->base_info));
	}
	

	ProtoCS_DeleteRoleInfoNtf ntf;
	ntf.role_id = req->role_id;
	memcpy(ntf.base_info, req->base_info, sizeof(ntf.base_info));
	SendDataBySessionType(SESSION_TYPE_CS2DB, ntf);
}

void User::HandleMapServMsg_UpdateRoleInfoNtf(void* pData)
{
	auto req = (ProtoMS_UpdateRoleInfoNtf*)pData;
	auto& info = GetInfo(req->role_id);
	if (info.empty()) {
		SetInfo(req->role_id, req->base_info);
	}
	if (info == req->base_info) {
		return;
	}
	
	ProtoCS_UpdateRoleInfoNtf ntf;
	ntf.role_id = req->role_id;
	memcpy(ntf.base_info, req->base_info, sizeof(ntf.base_info));
	SendDataBySessionType(SESSION_TYPE_CS2DB, ntf);
}

void User::HandleMapServMsg_InsertRoleInfoNtf(void* pData)
{
	auto req = (ProtoMS_InsertRoleInfoNtf*)pData;
	SetInfo(req->role_id, req->base_info);
	ProtoCS_InsertRoleInfoNtf ntf;
	ntf.role_id = req->role_id;
	memcpy(ntf.base_info, req->base_info, sizeof(ntf.base_info));
	SendDataBySessionType(SESSION_TYPE_CS2DB, ntf);
}

void User::HandleMapServMsg_SendRoleInfoAck(void* pData)
{
	auto getRoleInfoAck = (ProtoCS_GetRoleInfoAck*)pData;
	SetInfo(getRoleInfoAck->role_id, getRoleInfoAck->base_info);

	ProtoMS_GetRoleInfoAck ack;
	ack.role_id = getRoleInfoAck->role_id;
	memcpy(ack.base_info, getRoleInfoAck->base_info, sizeof(ack.base_info));
	SendDataBySessionType(SESSION_TYPE_CS2MS, ack);

}

void User::OnGetRoleDataAck(const uint64_t& roleID)
{
	auto it = mRoleDataMap.find(roleID);
	if (it == mRoleDataMap.end()) {
		return;
	}

	it->second.SetInitialized(true);

	OnEnterMapReq(roleID);
}

void User::OnEnterMapReq(const uint64_t& roleID)
{
	auto it = mRoleDataMap.find(roleID);
	if (it == mRoleDataMap.end()) return;
    auto &roleData = it->second;

	//==================================================发送进入地图信息
	ProtoCS_EnterMSReq msreq;
	strcpy_s(msreq.playerName, GetUserName());
	msreq.clienttype = GetClientType();
	msreq.entertype = GetEnterType();
	msreq.fangchenmi = GetFangChenMi();
	msreq.playerid = GetID();
	msreq.sessionid = GetGS2CLSessionID();
	msreq.token = GetToken();
	msreq.nMS2GSSessionID = GetMS2GSSessionID();
	msreq.roleBriefInfo = roleData.GetBriefInfo();
    msreq.roleExtraInfo = roleData.GetRoleExtraInfo();
	msreq.roleSettings = roleData.GetRoleSettings();
    msreq.questInfo = roleData.GetQuestInfo();
    msreq.questAchievesNum = _countof(msreq.questAchieves);
    roleData.GetQuestAchieves(msreq.questAchieves, msreq.questAchievesNum);
	msreq.isProhibitChat = GetIsProhibitChat();
	msreq.isSupport = GetIsSupport();
	SendDataBySessionType(SESSION_TYPE_CS2MS, msreq);


	//==================================================发送玩家物品自定义变量信息
	ProtoDB_PlayerItemCustVar itemCustVar;
	itemCustVar.playerid = GetID();
	itemCustVar.roleid = roleID;
	itemCustVar.token = GetToken();
	itemCustVar.vars = GetItemCustVars(roleID);
	SendDataBySessionType(SESSION_TYPE_CS2MS, itemCustVar);

	//==================================================发送物品动态属性信息
	auto* itemDynAttrsList = GetItemDynAttrsList(roleID);
	if (itemDynAttrsList && !itemDynAttrsList->empty()) {

		ProtoDB_ItemDynAttrNtf itemDynAttrNtf;
		itemDynAttrNtf.playerid = GetID();
		itemDynAttrNtf.roleid = roleID;
		itemDynAttrNtf.token = GetToken();
		itemDynAttrNtf.item_dyn_attrs_list = itemDynAttrsList;

		SendDataBySessionType(SESSION_TYPE_CS2MS, itemDynAttrNtf);
	}
	//==================================================发送角色动态属性信息
	auto* roleDynAttrsList = GetRoleDynAttrsList(roleID);
	if (roleDynAttrsList && !roleDynAttrsList->empty()) {

		ProtoDB_RoleDynAttrNtf roleDynAttrNtf;
		roleDynAttrNtf.playerid = GetID();
		roleDynAttrNtf.roleid = roleID;
		roleDynAttrNtf.token = GetToken();
		roleDynAttrNtf.role_dyn_attrs_list = roleDynAttrsList;

		SendDataBySessionType(SESSION_TYPE_CS2MS, roleDynAttrNtf);
	}
	//==================================================发送物品信息
	auto& itemList = roleData.GetItemList();
	auto& ntf = gProtoCS_SendItemNtf;
	ntf.role_id = roleID;
	ntf.token = GetToken();
	ntf.item_num = 0;
	int num = 0, maxNum = sizeof(ntf.item_info) / sizeof(ITEM_INFO);
	for (auto it = itemList.begin(); it != itemList.end(); ++it) {
		memcpy(&ntf.item_info[ntf.item_num], it->get(), sizeof(ITEM_INFO));
		++num;
		++ntf.item_num;
		if (num == itemList.size() || ntf.item_num == maxNum ) {
			SendDataBySessionType(SESSION_TYPE_CS2MS, ntf);
			ntf.item_num = 0;
		}
	}

	//==================================================发送技能信息
	ProtoMS_GetSkillAck getSkillAck;
	getSkillAck.playerid = GetID();
	getSkillAck.roleid = roleID;
	getSkillAck.skillNum = GetSkillList(roleID, getSkillAck.skillInfo, _countof(getSkillAck.skillInfo));
	SendDataBySessionType(SESSION_TYPE_CS2MS, getSkillAck);

    //==================================================发送玩家自定义变量信息
    ProtoDB_PlayerCustVar custVar;
    custVar.playerid = GetID();
    custVar.roleid = roleID;
    custVar.token = GetToken();
    custVar.vars = GetCustVars(roleID);
    SendDataBySessionType(SESSION_TYPE_CS2MS, custVar);

	//==================================================发送快捷栏自定义信息
	ProtoCS_QuickBarSetNtf barSetNtf;
	barSetNtf.role_id = roleID;
	barSetNtf.token = GetToken();
	barSetNtf.num = roleData.GetQuickBarSetNtfNum();
	roleData.GetQuickBarSetNtfInfo(barSetNtf.info, barSetNtf.num);
	SendDataBySessionType(SESSION_TYPE_CS2MS, barSetNtf);

	//==================================================发送buff信息
	ProtoMS_GetBuffAck getBuffAck;
	getBuffAck.playerid = GetID();
	getBuffAck.roleid = roleID;
	getBuffAck.buffNum = 0;
	getBuffAck.beFirstPack = 1;
	const std::vector<BUFF_INFO_DB>& li = roleData.GetBuffList();
	for (auto iter = li.begin(); iter != li.end();)
	{
		getBuffAck.buffs[getBuffAck.buffNum++] = *iter; ++iter;
		if (getBuffAck.buffNum >= _countof(getBuffAck.buffs) || iter == li.end())
		{
			SendDataBySessionType(SESSION_TYPE_CS2MS, getBuffAck);
			getBuffAck.buffNum = 0;
			getBuffAck.beFirstPack = 0;
		}
	}

	//==================================================发送副本绑定信息
	auto& dgnInfoList = roleData.GetDgnBindInfoList();
	ProtoCS_DgnBindInfoNtf getDgnBindAck;
	getDgnBindAck.roleId = roleID;
	getDgnBindAck.token = GetToken();
	getDgnBindAck.num = 0;
	for (auto iter = dgnInfoList.begin(); iter != dgnInfoList.end();)
	{
		getDgnBindAck.info[getDgnBindAck.num++] = *iter++;
		if (getDgnBindAck.num >= ProtoCS_DgnBindInfoNtf::DBI_MaxSize::Info_Size
			|| iter == dgnInfoList.end())
		{
			SendDataBySessionType(SESSION_TYPE_CS2MS, getDgnBindAck);
			getDgnBindAck.num = 0;
		}
	}
	
	//=================================================发送GM权限
	auto &role_gm_mod = sROLE_GM_MOD_Config.GetNameMappings();
	auto ptr = role_gm_mod.find(roleData.GetBriefInfo().name);
	if (ptr != role_gm_mod.end()) {
		if (std::string(ptr->second->Role_account) == mUserName) {
			ProtoCS_GMModLevel ack;
			ack.role_id = roleID;
			ack.GMModLevel = ptr->second->MOD;
			SendDataBySessionType(SESSION_TYPE_CS2MS, ack);
		}
	}

	//=================================================玩家商城信息
	auto& mallSingleMap = GameMallMgr::GetInstance()->GetMallItemLimitSingleMap();
	// 玩家登录时同步CS中该名玩家的mallsingle数据到MS
	if (mallSingleMap.empty() || mallSingleMap.find(roleID) == mallSingleMap.end())
	{
		ProtoCS_GetMallLimitInfoSingleAck mallInfoAck;
		mallInfoAck.playerguid = roleID;
		mallInfoAck.isFirstPkg = 1;
		mallInfoAck.isFinalPkg = 1;
		SendDataBySessionType(SESSION_TYPE_CS2MS, mallInfoAck);
	}
	else
	{
		bool isFirstPkg = true;
		auto mallSingleIter = mallSingleMap.find(roleID);
		auto singleMallInfoIter = mallSingleIter->second.begin();
		int singleMapNum = mallSingleIter->second.size();
		while (singleMapNum > 0)
		{
			ProtoCS_GetMallLimitInfoSingleAck mallInfoAck;
			mallInfoAck.playerguid = roleID;
			// 首包
			if (isFirstPkg)
			{
				mallInfoAck.isFirstPkg = 1;
				isFirstPkg = false;
			}

			if (singleMapNum > 100)
			{
				mallInfoAck.num = 100;
			}
			else
			{
				mallInfoAck.num = singleMapNum;
				mallInfoAck.isFinalPkg = 1;
			}
			for (int curPkgnum = 0; curPkgnum < mallInfoAck.num; ++curPkgnum)
			{
				mallInfoAck.data[curPkgnum] = singleMallInfoIter->second;
				++singleMallInfoIter;
			}
			singleMapNum -= 100;
			SendDataBySessionType(SESSION_TYPE_CS2MS, mallInfoAck);
		}
	
	}

    //==================================================未发放商品记录
    ProtoDB_GoodsNotIssuedRecordsNtf goodsNotIssuedRecords;
    goodsNotIssuedRecords.num = roleData.GetGoodsNotIssuedRecords(
        goodsNotIssuedRecords.records, _countof(goodsNotIssuedRecords.records));
    if (goodsNotIssuedRecords.num > 0) {
        goodsNotIssuedRecords.role_guid = roleID;
        SendDataBySessionType(SESSION_TYPE_CS2MS, goodsNotIssuedRecords);
    }

	//==================================================未投递商品记录
	ProtoDB_GoodsNotPostRecordsNtf goodsNotPostRecords;
	goodsNotPostRecords.num = roleData.GetGoodsNotPostRecords(
		goodsNotPostRecords.records, _countof(goodsNotPostRecords.records));
	if (goodsNotPostRecords.num > 0) {
		goodsNotPostRecords.role_guid = roleID;
		SendDataBySessionType(SESSION_TYPE_CS2MS, goodsNotPostRecords);
	}

	//==============================================================删档返利记录
	ProtoDB_RebateMoneyNotUsedRecordNtf rebateMoneyNotUsedRecord;
	rebateMoneyNotUsedRecord.role_guid = roleID;
	rebateMoneyNotUsedRecord.record = mRebateMoneyRecord;
	SendDataBySessionType(SESSION_TYPE_CS2MS, rebateMoneyNotUsedRecord);

	//==================================================发送称号
	Title::GetInstance()->SendPlayerInfoToMS(roleID);

	//==================================================最后发送进入地图通知
	ProtoCS_EnterMSNtf enterMsNtf;
	enterMsNtf.token = GetToken();
	enterMsNtf.player_id = GetID();
	enterMsNtf.role_id = roleID;
	SendDataBySessionType(SESSION_TYPE_CS2MS, enterMsNtf);
	SendDataBySessionType(SESSION_TYPE_CS2DB, enterMsNtf);
	//=================================================发送邮件列表
	ProtoCS_GetMailInfo ack;
	ack.playerguid = roleID;
	SendDataBySessionType(SESSION_TYPE_CS2DB, ack);
}

void User::SetBuffList(const uint64_t& roleID, BUFF_INFO_DB* buff, uint16_t num, bool firstPack, bool sync)
{
	auto it = mRoleDataMap.find(roleID);
	if (it != mRoleDataMap.end()) {
		it->second.SetBuffList(buff, num, firstPack, sync);
	}
}

void User::OnGetRoleItemAck(const uint64_t& roleID, ITEM_INFO* items, int num)
{
	auto it = mRoleDataMap.find(roleID);
	if (it == mRoleDataMap.end()) {
		return;
	}

	if (nullptr == items) {
		return;
	}

	auto& roleData = it->second;
	for (int i = 0; i < num; ++i) {
		auto item = std::make_unique<ITEM_INFO>();
		memcpy(item.get(), &items[i], sizeof(ITEM_INFO));
		roleData.AddItem(item);
	}
}

void User::SetRoleExtraInfo(const uint64_t &nRoleID, const ROLE_EXTRA_INFO &roleExtraInfo)
{
    auto it = mRoleDataMap.find(nRoleID);
    if (it == mRoleDataMap.end()) return;
    it->second.SetRoleExtraInfo(roleExtraInfo);
}

void User::SyncRoleInfo(const uint64_t &nRoleID, const ROLE_BRIEF_INFO &newBriefInfo,
	const ROLE_EXTRA_INFO &newExtraInfo, const ROLE_SETTINGS &newSettings)
{
    auto it = mRoleDataMap.find(nRoleID);
    if (it == mRoleDataMap.end()) return;

	it->second.UpdateBriefInfo(newBriefInfo);
    //it->second.SetBriefInfo(roleBriefInfo);
	it->second.UpDataExtraInfo(newExtraInfo);
    //it->second.SetRoleExtraInfo(roleExtraInfo);
	it->second.UpdataRoleSettingsInfo(newSettings);
	//it->second.SetRoleSettings(roleSettings);
/*
    auto &roleData = it->second;
    const auto &oldBriefInfo = roleData.GetBriefInfo();
    const auto &oldExtraInfo = roleData.GetRoleExtraInfo();
    const auto &oldSettings = roleData.GetRoleSettings();

    flatbuffers::FlatBufferBuilder builder;
    auto key = builder.CreateVector((unsigned char *)&nRoleID, sizeof(nRoleID));

    std::vector<flatbuffers::Offset<UpdateTable>> tableOffsetAry;
    std::vector<flatbuffers::Offset<DBElem>> elemOffsetAry;

#define CHECK_DIFF_1(member, eid) \
    if (oldBriefInfo.member != newBriefInfo.member) { \
        auto data = builder.CreateVector((unsigned char *)&oldBriefInfo.member, sizeof(oldBriefInfo.member)); \
        auto elemOffset = CreateDBElem(builder, eid, data); \
        elemOffsetAry.emplace_back(elemOffset); \
    }

    CHECK_DIFF_1(head, role_eid_head);
    CHECK_DIFF_1(level, role_eid_level);
    CHECK_DIFF_1(status, role_eid_status);
    CHECK_DIFF_1(job, role_eid_job);
    CHECK_DIFF_1(hair, role_eid_hair);
    CHECK_DIFF_1(hair_color, role_eid_hair_color);
    CHECK_DIFF_1(gender, role_eid_gender);
    CHECK_DIFF_1(weapon, role_eid_weapon);
    CHECK_DIFF_1(clothes, role_eid_clothes);
    CHECK_DIFF_1(vipLevel, role_eid_vip_level);
    CHECK_DIFF_1(is_lock, role_eid_is_lock);

#define CHECK_DIFF_2(member, eid) \
    if (oldExtraInfo.member != newExtraInfo.member) { \
        auto data = builder.CreateVector((unsigned char *)&oldExtraInfo.member, sizeof(oldExtraInfo.member)); \
        auto elemOffset = CreateDBElem(builder, eid, data); \
        elemOffsetAry.emplace_back(elemOffset); \
    }

    CHECK_DIFF_2(login_time, role_eid_login_time);
    CHECK_DIFF_2(hp, role_eid_hp);
    CHECK_DIFF_2(mp, role_eid_mp);
    CHECK_DIFF_2(exp, role_eid_exp);
    CHECK_DIFF_2(gold, role_eid_gold);
    CHECK_DIFF_2(bindGold, role_eid_bind_gold);
    CHECK_DIFF_2(ingot, role_eid_ingot);
    CHECK_DIFF_2(bindIngot, role_eid_bind_ingot);
    CHECK_DIFF_2(integral, role_eid_integral);
    CHECK_DIFF_2(depositGold, role_eid_deposit_gold);
    CHECK_DIFF_2(innerForceExp, role_eid_inner_force_exp);
    CHECK_DIFF_2(atkMode, role_eid_atk_mode);
    CHECK_DIFF_2(rolePk, role_eid_role_pk);
    CHECK_DIFF_2(modelID, role_eid_model_id);

    if (!elemOffsetAry.empty()) {
        auto elems = builder.CreateVector(elemOffsetAry);
        auto tableOffset = CreateUpdateTable(builder, table_role, key, elems);
        tableOffsetAry.emplace_back(tableOffset);
    }

    ////////////////////////////////////////////////////////////////////////////////
    // role_location

    elemOffsetAry.clear();

    CHECK_DIFF_2(mapid, role_location_map);
    CHECK_DIFF_2(posx, role_location_posx);
    CHECK_DIFF_2(posy, role_location_posy);
    CHECK_DIFF_2(dir, role_location_dir);
    CHECK_DIFF_2(birthMap, role_location_birth_map);
    CHECK_DIFF_2(rebirthMap, role_location_rebirth_map);
    CHECK_DIFF_2(redNameMap, role_location_redname_map);

    if (!elemOffsetAry.empty()) {
        auto elems = builder.CreateVector(elemOffsetAry);
        auto tableOffset = CreateUpdateTable(builder, table_role_location, key, elems);
        tableOffsetAry.emplace_back(tableOffset);
    }

    ////////////////////////////////////////////////////////////////////////////////
    // role_settings

    elemOffsetAry.clear();

    if (memcmp(&oldSettings.auto_pickup, &newSettings.auto_pickup, sizeof(AUTO_PICKUP)) != 0) {

        const auto &autoPickup = newSettings.auto_pickup;

        flatbuffers::FlatBufferBuilder builder2;
        auto relposOffset = builder2.CreateVectorOfStructs((Position *)autoPickup.relpos, autoPickup.numpos);
        auto offset = CreateAutoPickItem(builder2, autoPickup.mode, autoPickup.radius, relposOffset, autoPickup.interval);

        builder2.Finish(offset);
        auto *buf = builder2.GetBufferPointer();
        auto size = builder2.GetSize();

        auto data = builder.CreateVector(buf, size);
        auto elemOffset = CreateDBElem(builder, role_settings_auto_pickup, data);
        elemOffsetAry.emplace_back(elemOffset);
    }

    if (!elemOffsetAry.empty()) {
        auto elems = builder.CreateVector(elemOffsetAry);
        auto tableOffset = CreateUpdateTable(builder, table_role_settings, key, elems);
        tableOffsetAry.emplace_back(tableOffset);
    }

    ////////////////////////////////////////////////////////////////////////////////

    if (!tableOffsetAry.empty()) {
        auto tables = builder.CreateVector(tableOffsetAry);
        auto offset = CreateUpdateTables(builder, tables);

        builder.Finish(offset);
        auto *buf = builder.GetBufferPointer();
        auto size = builder.GetSize();

        ProtoCS_UpdateTables data;
        data.len = size;
        data.data = buf;

        SendDataBySessionType(SESSION_TYPE_CS2DB, data);
    }

    roleData.SetBriefInfo(newBriefInfo);
    roleData.SetRoleExtraInfo(newExtraInfo);
    roleData.SetRoleSettings(newSettings);
*/
}

void User::SetRoleSettings(const uint64_t &nRoleID, const ROLE_SETTINGS &roleSettings)
{
	auto it = mRoleDataMap.find(nRoleID);
	if (it == mRoleDataMap.end()) return;
	it->second.SetRoleSettings(roleSettings);
}

void User::SetQuestInfo(const uint64_t &nRoleID, const QUEST_INFO &questInfo)
{
    auto it = mRoleDataMap.find(nRoleID);
    if (it == mRoleDataMap.end()) return;

    it->second.SetQuestInfo(questInfo);
}

void User::SetQuestAchieves(const uint64_t &nRoleID, const QUEST_ACHIEVE *pQuestAchieve, uint16_t num)
{
    auto it = mRoleDataMap.find(nRoleID);
    if (it == mRoleDataMap.end()) return;

    it->second.SetQuestAchieves(pQuestAchieve, num);
}

void User::SyncQuestInfo(const uint64_t &nRoleID, const QUEST_INFO &questInfo, const QUEST_ACHIEVE *pQuestAchieve, uint8_t num)
{
    if (!pQuestAchieve) return;

    auto itRoleData = mRoleDataMap.find(nRoleID);
    if (itRoleData == mRoleDataMap.end()) return;

    auto &roleData = itRoleData->second;

    ProtoCS_SyncQuestReq syncQuestReq;

    syncQuestReq.quest_info = questInfo;
    roleData.SetQuestInfo(questInfo);

    auto &nRemoveNum = syncQuestReq.remove_num;
    auto &nAddNum = syncQuestReq.add_num;
    auto &nUpdateNum = syncQuestReq.update_num;

    std::list<const QUEST_ACHIEVE *> newAchevs;
    for (uint8_t i = 0; i < num; ++i) newAchevs.push_back(pQuestAchieve + i);

    const auto &oldAchevs = roleData.GetQuestAchieves();

    for (auto &oldAchev : oldAchevs) {

        auto itNewAchev = std::find_if(newAchevs.begin(), newAchevs.end(), [&](auto *pNewAchev) {
            return (pNewAchev->quest == oldAchev.quest) &&
                   (pNewAchev->achev_type == oldAchev.achev_type) &&
                   (pNewAchev->achev_id == oldAchev.achev_id);
        });

        if (itNewAchev == newAchevs.end()) {     // 未找到
            syncQuestReq.remove_achev[nRemoveNum++] = oldAchev;
        }
        else if ((*itNewAchev)->achev_num != oldAchev.achev_num) {
            syncQuestReq.update_achev[nUpdateNum++] = **itNewAchev;
            newAchevs.erase(itNewAchev);
        }
    }

    for (auto &pNewAchev : newAchevs) {
        syncQuestReq.add_achev[nAddNum++] = *pNewAchev;
    }

    syncQuestReq.roleid = nRoleID;
    SendDataBySessionType(SESSION_TYPE_CS2DB, syncQuestReq);

    roleData.SetQuestAchieves(pQuestAchieve, num);
}

void User::SetCustVars(const uint64_t &roleid, CUST_VAR_MAP vars)
{
    auto it = mRoleDataMap.find(roleid);
    if (it == mRoleDataMap.end()) return;

    it->second.SetCustVars(std::move(vars));
}

CUST_VAR_MAP * User::GetCustVars(const uint64_t &roleid)
{
    auto it = mRoleDataMap.find(roleid);
    if (it == mRoleDataMap.end()) return nullptr;

    return &it->second.GetCustVars();
}

void User::SyncCustVars(const uint64_t &roleid, CUST_VAR_MAP vars)
{
    auto it = mRoleDataMap.find(roleid);
    if (it == mRoleDataMap.end()) return;

    auto &roleData = it->second;

    auto &oldVars = roleData.GetCustVars();
    auto &newVars = vars;

    CUST_VAR_LIST add, remove, update;

    for (auto &itNew : newVars) {

        auto &name = itNew.first;
        auto &newVar = itNew.second;
		if (newVar.type == cust_var_type_temp)
		{
			continue;
		}
		auto itOld = oldVars.find(name);
        if (itOld == oldVars.end()) {
            add.push_back(newVar);
            continue;
        }

        auto &oldVar = itOld->second;

        if (oldVar.value != newVar.value || oldVar.type != newVar.type ||
            oldVar.expire != newVar.expire) {
            update.push_back(newVar);
        }

        oldVars.erase(itOld);
    }

    for (auto &it : oldVars) {

        auto &oldVar = it.second;
        oldVar.value.clear();       // 减少数据发送量
        remove.push_back(std::move(oldVar));
    }

    if (!add.empty() || !remove.empty() || !update.empty()) {

        ProtoCS_SyncPlayerCustVar data;

        data.roleid = roleid;
        data.add = &add;
        data.remove = &remove;
        data.update = &update;

        SendDataBySessionType(SESSION_TYPE_CS2DB, data);
    }

    roleData.SetCustVars(std::move(vars));
}

void User::SetItemCustVars(const uint64_t &roleid, CUST_VAR_SP_LIST vars)
{
    auto it = mRoleDataMap.find(roleid);
    if (it == mRoleDataMap.end()) return;

    it->second.SetItemCustVars(std::move(vars));
}

CUST_VAR_SP_LIST * User::GetItemCustVars(const uint64_t &roleid)
{
    auto it = mRoleDataMap.find(roleid);
    if (it == mRoleDataMap.end()) return nullptr;

    return &it->second.GetItemCustVars();
}

void User::DeleteItemCustVars(uint64_t roleGUID, uint64_t itemGUID)
{
	auto* list = GetItemCustVars(roleGUID);
	if (list)
	{
		for (auto iter = list->begin(); iter != list->end();)
		{
			if ((*iter)->belong == itemGUID)
			{
				iter = list->erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}

void User::SyncItemCustVars(const uint64_t &roleid, CUST_VAR_SP_LIST vars)
{
    auto it = mRoleDataMap.find(roleid);
    if (it == mRoleDataMap.end()) return;

    auto &roleData = it->second;

    auto &oldVars = roleData.GetItemCustVars();
    auto &newVars = vars;

    CUST_VAR_SP_LIST add, remove, update;

    for (auto &newVar : newVars) {

        auto it = std::find_if(oldVars.begin(), oldVars.end(), [&](const auto &oldVar) {
            return (oldVar->belong == newVar->belong) && (oldVar->name == newVar->name);
        });

        if (it == oldVars.end()) {
            add.emplace_back(newVar);
            continue;
        }

        auto &oldVar = *it;
        if (oldVar->value != newVar->value || oldVar->type != newVar->type || oldVar->expire != newVar->expire) {
            update.emplace_back(newVar);
        }

        oldVars.erase(it);
    }

    remove = std::move(oldVars);
    for (auto &var : remove) var->value.clear();

    if (!add.empty() || !remove.empty() || !update.empty()) {

        ProtoCS_SyncItemCustVar data;

        data.add = &add;
        data.remove = &remove;
        data.update = &update;

        SendDataBySessionType(SESSION_TYPE_CS2DB, data);
    }

    roleData.SetItemCustVars(std::move(vars));
}

void User::SetItemDynAttrsList(const uint64_t &roleid, ITEM_DYN_ATTRS_LIST attrsList, bool sync)
{
    auto it = mRoleDataMap.find(roleid);
    if (it == mRoleDataMap.end()) return;
    it->second.SetItemDynAttrsList(std::move(attrsList), sync);
}

ITEM_DYN_ATTRS_LIST * User::GetItemDynAttrsList(const uint64_t &roleid)
{
    auto it = mRoleDataMap.find(roleid);
    if (it == mRoleDataMap.end()) return nullptr;
    return &it->second.GetItemDynAttrsList();
}

void User::DeleteItemAttrsList(uint64_t roleGUID, uint64_t itemGUID)
{
	auto* list = GetItemDynAttrsList(roleGUID);
	if (list)
	{
		auto iter = std::find_if(list->begin(), list->end(), 
			[=](const ITEM_DYN_ATTRS& a) {return a.guid == itemGUID; }
		);
		if (iter != list->end()) list->erase(iter);
	}
}

void User::SetRoleDynAttrsList(const uint64_t& roleid, ITEM_DYN_ATTRS_LIST attrsList)
{
	auto it = mRoleDataMap.find(roleid);
	if (it == mRoleDataMap.end()) return;
	it->second.SetRoleDynAttrsList(std::move(attrsList));
}

ROLE_DYN_ATTRS_LIST* User::GetRoleDynAttrsList(const uint64_t& roleid)
{
	auto it = mRoleDataMap.find(roleid);
	if (it == mRoleDataMap.end()) return nullptr;
	return &it->second.GetRoleDynAttrsList();
}

void User::IsHavingGmMod(const std::string& gmCmd, std::string& playername ,uint8_t& result)
{
	auto& role_gm_modCfg = sROLE_GM_MOD_Config.GetNameMappings();
	auto iterRoleGmCfg = role_gm_modCfg.find(mUserName);
	if (iterRoleGmCfg == role_gm_modCfg.end())
	{
		result = ERR_EXEGMCMDFAIL;
		return;
	}
	playername = std::string(iterRoleGmCfg->second->Role_name);

	auto& gm_cmd_mod = sGM_CMD_Config.GetNameMappings();
	auto iterGmCmdMod = gm_cmd_mod.find(gmCmd);
	if (iterGmCmdMod == gm_cmd_mod.end())
	{
		if (iterRoleGmCfg->second->MOD == 5)
		{
			result = ERR_OK;
			return;
		}
		result = ERR_NOGMCMD;
		return;
	}

	if (iterRoleGmCfg->second->MOD < iterGmCmdMod->second->mod_level)
	{
		result = ERR_GMCMDNORIGHT;
		return;
	}
	result = ERR_OK;
}

void User::SetRebateMoneyNotUsedRecord(const REBATE_MONEY_RECORD& record)
{
	if (mRebateMoneyRecord.be_load) return;

	mRebateMoneyRecord = record;
}

void User::SetGoodsNotIssuedRecords(const uint64_t &roleGUID, const GOODS_ISSUE_RECORD *records, uint8_t num)
{
    auto it = mRoleDataMap.find(roleGUID);
    if (it == mRoleDataMap.end()) return;
    it->second.SetGoodsNotIssuedRecords(records, num);
}

void User::SetGoodsNotPostRecords(const uint64_t& roleGUID, const GOODS_ISSUE_RECORD* records, uint8_t num)
{
	auto it = mRoleDataMap.find(roleGUID);
	if (it == mRoleDataMap.end()) return;
	it->second.SetGoodsNotPostRecords(records, num);
}

void User::AddGoodsNotIssuedRecord(const uint64_t &roleGUID, const GOODS_ISSUE_RECORD &record)
{
    auto it = mRoleDataMap.find(roleGUID);
    if (it == mRoleDataMap.end()) return;
    it->second.AddGoodsNotIssuedRecord(record);
}

void User::AddGoodsNotPostRecord(const uint64_t& roleGUID, const GOODS_ISSUE_RECORD& record)
{
	auto it = mRoleDataMap.find(roleGUID);
	if (it == mRoleDataMap.end()) return;
	it->second.AddGoodsNotPostRecord(record);
}

void User::RemoveGoodsNotIssuedRecords(const uint64_t &roleGUID,
    const char orderNoList[MAX_GOODS_ISSUE_RECORD][ORDER_NO_BUFLEN], uint8_t num)
{
    auto it = mRoleDataMap.find(roleGUID);
    if (it == mRoleDataMap.end()) return;
    it->second.RemoveGoodsNotIssuedRecords(orderNoList, num);
}

void User::SyncGoodsPostRecords(const uint64_t& roleGUID,
	const char orderNoList[MAX_GOODS_POST_RECORD][ORDER_NO_BUFLEN], uint8_t num)
{
	auto it = mRoleDataMap.find(roleGUID);
	if (it == mRoleDataMap.end()) return;
	it->second.UpdateGoodsNotPostRecords(orderNoList, num);
}

void User::SetRebateMoneyUsedRecord(ProtoMS_RebateMoneyUsedNtf& msg)
{
	if (mRebateMoneyRecord.is_use) return;

	mRebateMoneyRecord.is_use = 1;
	msg.record = mRebateMoneyRecord;
	//SendDataBySessionType(SESSION_TYPE_CS2DB, msg);
	SendUpdateRebateReqToPlatform(User::PlatformRebateReq(GetID(), GetUserName()));
}

void User::SyncPlayerGender(uint8_t gender, uint64_t guid)
{
	auto it = mRoleDataMap.find(guid);
	if (it == mRoleDataMap.end()) return;
	it->second.SyncPlayerGender(gender);
}

void User::UpdateOnlineStateToDB(uint8_t type)
{
	ProtoGS_UpdateOnlineState data;
	data.state = type;
	data.token = GetToken();
	auto& roleDataMap = GetRoleDataMap();
	for (auto& i : roleDataMap) {
		data.roleid = i.second.GetBriefInfo().guid;
		SendDataBySessionType(SESSION_TYPE_CS2DB, data);
	}
}

void User::StartSyncRoleInfoTimer()
{
	if (0 != mSyncUserTimerId) StopSyncRoleInfoTimer();
	uint32_t intervalTime = SEND_SYNC_USER_DATA_INTERVAL_TIME;
	auto globalCfg = sGlobalConfig.GetData();
	if (globalCfg) intervalTime = globalCfg->SyncUserDataIntervalTime;

	auto UserID = GetID();

	mSyncUserTimerId = ITimeHelper::GetInstance()->AddTimer(intervalTime, true, [=](const TimerData&) {
		auto* user = UserMgr::GetInstance()->FindUser(UserID);
		if (!user) return;
		SyncUserData();
	});
}

void User::StopSyncRoleInfoTimer()
{
	SyncUserData();
	if (mSyncUserTimerId == 0)return;
	ITimeHelper::GetInstance()->RemoveTimer(mSyncUserTimerId);
	mSyncUserTimerId = 0;
}

void User::SyncUserData()
{
	for (auto& i : mRoleDataMap) {
		i.second.SyncRoleInfoToDB(GetID());
        i.second.SyncBuffList();
		i.second.SyncItemDynAttrsList(GetID());
		i.second.SyncRoleTitleToDB();
		i.second.SyncQuickBarSetToDB();
	}
	
}

void User::UpdateQuickBarSetFlag(uint8_t slot, uint64_t guid)
{
	auto role = mRoleDataMap.find(guid);
	if (role == mRoleDataMap.end())return;
	role->second.UpdateQuickBarSetFlag(slot);
}

size_t User::CURLWriteCallback(void* data, size_t size, size_t nmemb, void* userp)
{
	auto len = size * nmemb;

	auto* resp = static_cast<std::vector<char> *>(userp);

	auto oldSize = resp->size();
	auto newSize = oldSize + len + 1;

	resp->resize(newSize);

	memcpy(resp->data() + oldSize, data, len);

	return len;

}

void User::SendGetRebateReqToPlatform(const PlatformRebateReq& rebateReq)
{
	if (mRebateMoneyRecord.be_load) return;

	auto* cfg = ConfigInfo::GetInstance();
	if (!cfg) return;

	auto url = cfg->m_sPlatformDomain + GET_REBATE_CODE_PATH;

	auto spRebateReq = std::make_shared<PlatformRebateReq>(rebateReq);

	ctpl::task_t task = [=](int) {
		const int HTTP_MSG_LENGTH = 10240;
		char data[HTTP_MSG_LENGTH] = { 0 };

		if (!ComposeHttpRequest(*spRebateReq, data, _countof(data)))
			return;

		auto* curl = curl_easy_init();
		if (!curl) {
			LOG_ERROR("curl_easy_init failed");
			return;
		}

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CURLWriteCallback);
		std::vector<char> resp;
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		ParseResult(spRebateReq, resp);
	};

	auto& threadPool = CenterServer::GetInstance()->GetThreadPool();
	threadPool.push(std::move(task));
}

void User::SendUpdateRebateReqToPlatform(const PlatformRebateReq& rebateReq)
{
	auto* cfg = ConfigInfo::GetInstance();
	if (!cfg) return;

	auto url = cfg->m_sPlatformDomain + UPDATE_REBATE_CODE_PATH;

	auto spRebateReq = std::make_shared<PlatformRebateReq>(rebateReq);

	ctpl::task_t task = [=](int) {
		const int HTTP_MSG_LENGTH = 10240;
		char data[HTTP_MSG_LENGTH] = { 0 };

		if (!ComposeHttpRequest(*spRebateReq, data, _countof(data)))
			return;

		auto* curl = curl_easy_init();
		if (!curl) {
			LOG_ERROR("curl_easy_init failed");
			return;
		}

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		};

	auto& threadPool = CenterServer::GetInstance()->GetThreadPool();
	threadPool.push(std::move(task));
}

bool User::ComposeHttpRequest(const PlatformRebateReq& rebateReq, char* buf, int bufsz)
{
	ConfigInfo* cfg = ConfigInfo::GetInstance();
	if (!cfg) return false;

	auto gameID = cfg->GetCurAgentId();
	auto regionID = cfg->GetCurAreaId();
	auto serverID = regionID * 1000 + cfg->GetCurAreaServerId();

	sprintf_s(buf, bufsz, "game_id=%u&region_id=%u&server_id=%u&account_id=%s",
		gameID, regionID, serverID, gbk_to_utf8(rebateReq.account_name).c_str());

	return true;
}

void User::ParseResult(std::shared_ptr<PlatformRebateReq> ptr, std::vector<char>& resp)
{
	if (resp.empty()) return;

	const char* raw = resp.data();
	Json::Value root;
	Json::Reader reader;
	if (!reader.parse(raw, raw + strlen(raw), root)) {
		LOG_ERROR("parse failed, raw: %s", raw);
		return;
	}

	if (!root.isMember("code")) {
		LOG_ERROR("No code member, raw: %s", raw);
		return;
	}

	REBATE_MONEY_RECORD record;
	record.account_id = ptr->account_id;
	strncpy_s(record.account_name, ptr->account_name, sizeof(record.account_name) - 1);
	auto code = root["code"].asInt();

	if (!code)
	{
		record.be_load = 1;
		if (root.isMember("data"))
		{
			record.inc_id = 1;
			const auto& data = root["data"];
			if (data.isMember("rebate_money"))
			{
				record.rebate_money = std::stoull(data["rebate_money"].asCString());
			}
			if (data.isMember("is_use"))
			{
				record.is_use = data["is_use"].asBool();
			}
		}
	}

	callable_t func = [=] {
		auto user = UserMgr::GetInstance()->FindUser(record.account_id);
		if (!user) return;

		user->SetRebateMoneyNotUsedRecord(record);
	};
	auto& queue = CenterServer::GetInstance()->GetCallableQueue();
	queue.push(func);
}