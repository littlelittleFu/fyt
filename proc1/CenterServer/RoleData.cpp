#include "stdafx.h"
#include "RoleData.h"
#include <experimental/list>
#include <iterator>
#include <algorithm>

RoleData::RoleData()
{
	memset(&mBriefInfo, 0, sizeof(mBriefInfo));
    memset(&mRoleExtraInfo, 0, sizeof(mRoleExtraInfo));
    memset(&mQuestInfo, 0, sizeof(mQuestInfo));
}

RoleData::~RoleData()
{
	mItemList.clear();
	mSkillList.clear();
	mDgnBindInfo.clear();
}

void RoleData::AddItem( std::unique_ptr<ITEM_INFO>& item)
{
	mItemList.push_back(std::move(item));
}

void RoleData::DelItem(const uint64_t itemGUID)
{
	for (auto it = mItemList.begin(); it != mItemList.end(); ) {
		if ((* it)->base_info.guid == itemGUID) {
			it = mItemList.erase(it);
			break;
		}
		else {
			++it;
		}
	}
}

void RoleData::ClearItem()
{
	mItemList.clear();
}

ITEM_INFO* RoleData::GetItem(const uint64_t itemGUID)
{
	auto it = std::find_if(mItemList.begin(), mItemList.end(), [itemGUID](std::unique_ptr<ITEM_INFO>& mlist) {
		return mlist->base_info.guid == itemGUID;
		});
	return it == mItemList.end() ? nullptr : ((*it).get());
}

QUICK_BAR_INFO* RoleData::GetQuickBarSet(const unsigned char mslot)
{
	auto it = std::find_if(mQuickBarSetInfo.begin(), mQuickBarSetInfo.end(), [mslot](QUICK_BAR_INFO& mlist) {
		return mlist.slot == mslot;
		});
	if (it == mQuickBarSetInfo.end())
	{
		return nullptr;
	}
	return &(*it);
}

void RoleData::AddBar(QUICK_BAR_INFO& item)
{
	mQuickBarSetInfo.push_back(item);
}

void RoleData::GetQuickBarSetNtfInfo(QUICK_BAR_INFO* info, unsigned short num)
{
	unsigned short n = 0;
	for (auto& it : mQuickBarSetInfo) {
		info[n] = it;
		if (++n == num) break;
	}
}

void RoleData::syncQuickBarSetNtf(QUICK_BAR_INFO* info, unsigned short num)
{
	mQuickBarSetInfo.clear();
	for (int i=0;i<num;++i)
	{
		mQuickBarSetInfo.push_back(info[i]);
	}
}

void RoleData::AddTmpDgnBindInfo(DGN_BIND_INFO& info)
{
	mTmpDgnBindInfo.push_back(info);
}

void RoleData::SwapDgnBindInfoList()
{
	std::swap(mTmpDgnBindInfo, mDgnBindInfo);
	mTmpDgnBindInfo.clear();
}

void RoleData::syncDgnBindInfoNtf(DGN_BIND_INFO* info, uint16_t num)
{
	for (int i = 0; i < num; ++i)
	{
		mDgnBindInfo.push_back(info[i]);
	}
}

uint16_t RoleData::GetValidBuffInfo(BUFF_INFO_DB* pBuffInfo, uint16_t num)
{
	if (!pBuffInfo) return 0;

	int n = 0;
	for (auto& buff : mBuffList) {
		pBuffInfo[n++] = buff;
		if (n >= num) break;
	}
	return n;
}

void RoleData::SetBuffList(const BUFF_INFO_DB* pBuffInfo, const uint16_t& nBuffNum, bool firstPack, bool sync)
{
	if (nullptr == pBuffInfo) {
		return;
	}

	if (firstPack) mBuffList.clear();

	for (int32_t i = 0; i < nBuffNum; ++i)
	{
		mBuffList.push_back(pBuffInfo[i]);
	}

    if (sync) mOldBuffList = mBuffList;
}

void RoleData::SyncBuffList()
{
    using BuffMap = std::map<uint64_t, const BUFF_INFO_DB *>;

    BuffMap newBuffList, oldBuffList;

    for (auto &it : mBuffList)
        newBuffList[it.index] = &it;
    for (auto &it : mOldBuffList)
        oldBuffList[it.index] = &it;

    ProtoCS_SyncBuffReq syncBuffReq;
    auto &nRemoveNum = syncBuffReq.removeNum;
    auto &nAddNum = syncBuffReq.addNum;
    auto &nUpdateNum = syncBuffReq.updateNum;
    nRemoveNum = 0;
    nAddNum = 0;
    nUpdateNum = 0;
	syncBuffReq.roleid = mBriefInfo.guid;
    for (auto &oldItor : oldBuffList) {

        auto nOldBuffIdx = oldItor.first;

        auto newItor = newBuffList.find(nOldBuffIdx);

        if (newItor == newBuffList.end()) {
            if (nRemoveNum < _countof(syncBuffReq.removeIndex))
                syncBuffReq.removeIndex[nRemoveNum++] = oldItor.second->index;
        }
        else {
            if (memcmp(oldItor.second, newItor->second, sizeof(BUFF_INFO_DB)) != 0) {
                if (nUpdateNum < _countof(syncBuffReq.updateBuffInfo))
                    syncBuffReq.updateBuffInfo[nUpdateNum++] = *newItor->second;
            }
            newBuffList.erase(newItor);
        }

		if (nRemoveNum >= _countof(syncBuffReq.removeIndex) || nUpdateNum >= _countof(syncBuffReq.updateBuffInfo))
		{
			SendDataBySessionType(SESSION_TYPE_CS2DB, syncBuffReq);
			nRemoveNum = 0;
			nUpdateNum = 0;
		}
    }

    for (auto &newItor : newBuffList) {
		if (nAddNum < _countof(syncBuffReq.addBuffInfo))
			syncBuffReq.addBuffInfo[nAddNum++] = *newItor.second;

		if (nAddNum >= _countof(syncBuffReq.addBuffInfo))
		{
			SendDataBySessionType(SESSION_TYPE_CS2DB, syncBuffReq);
			nRemoveNum = 0;
			nUpdateNum = 0;
			nAddNum = 0;
		}
    }

    if (nRemoveNum != 0 || nAddNum != 0 || nUpdateNum != 0) SendDataBySessionType(SESSION_TYPE_CS2DB, syncBuffReq);

    mOldBuffList = mBuffList;
}

void RoleData::SetSkillList(const SKILL_INFO *pSkillInfo, uint16_t num)
{
    if (!pSkillInfo) return;

    mSkillList.clear();
	mSkillList.assign(pSkillInfo, pSkillInfo + num);
}

void RoleData::SetQuestAchieves(const QUEST_ACHIEVE *pQuestAchieve, uint16_t num)
{
    if (!pQuestAchieve) return;

    mQuestAchieves.clear();
	mQuestAchieves.assign(pQuestAchieve, pQuestAchieve + num);
}

void RoleData::GetQuestAchieves(QUEST_ACHIEVE *pQuestAchieve, uint8_t &num)
{
    if (!pQuestAchieve) return;

    num = std::min<uint8_t>(num, static_cast<uint8_t>(mQuestAchieves.size()));
    auto it = mQuestAchieves.begin();

    for (uint8_t i = 0; i < num; ++i) {
        pQuestAchieve[i] = *it++;
    }
}
static void CheckSyncItemDynAttrs(ITEM_DYN_ATTRS& attrs, ITEM_DYN_ATTRS_LIST& syncAttrsList)
{
	if (attrs.dyn_attrs.empty()) return;
	if (syncAttrsList.empty())
	{
		syncAttrsList.push_back(attrs);
		return;
	}

	auto iter = syncAttrsList.begin();
	for (; iter != syncAttrsList.end(); ++iter)
	{
		if (attrs.guid == iter->guid) break;
	}

	if (iter == syncAttrsList.end())
	{
		// 没有该guid
		syncAttrsList.push_back(attrs);
	}
	else
	{
		for (auto& attr : attrs.dyn_attrs)
		{
			auto it = iter->dyn_attrs.begin();
			for (; it != iter->dyn_attrs.end(); ++it)
			{
				if (attr.index != it->index)
					continue;

				// 改变
				if (memcmp(&attr, &(*it), sizeof(DYN_ATTR)) != 0) *it = attr;
				
				break;
			}
			// 不存在
			if (it == iter->dyn_attrs.end())  iter->dyn_attrs.push_back(attr);
		}
	}
}
void RoleData::SetItemDynAttrsList(ITEM_DYN_ATTRS_LIST attrsList, bool sync)
{
	mItemDynAttrsList = std::move(attrsList);
    if (sync) mSyncItemDynAttrsList = mItemDynAttrsList;
}

void RoleData::SetGoodsNotIssuedRecords(const GOODS_ISSUE_RECORD *records, uint8_t num)
{
    if (!records) return;
    mGoodsNotIssuedRecords.clear();
    for (uint8_t i = 0; i < num; ++i) {
        mGoodsNotIssuedRecords.push_back(records[i]);
    }
}

void RoleData::SetGoodsNotPostRecords(const GOODS_ISSUE_RECORD* records, uint8_t num)
{
	if (!records) return;
	mGoodsNotPostRecords.clear();
	for (uint8_t i = 0; i < num; ++i) {
		mGoodsNotPostRecords.push_back(records[i]);
	}
}

void RoleData::AddGoodsNotIssuedRecord(const GOODS_ISSUE_RECORD &record)
{
    for (const auto &stored : mGoodsNotIssuedRecords)
        if (strcmp(stored.order_no, record.order_no) == 0)
            return;
    mGoodsNotIssuedRecords.push_back(record);
}

void RoleData::AddGoodsNotPostRecord(const GOODS_ISSUE_RECORD& record)
{
	for (const auto& stored : mGoodsNotPostRecords)
		if (strcmp(stored.order_no, record.order_no) == 0)
			return;
	mGoodsNotPostRecords.push_back(record);
}

uint8_t RoleData::GetGoodsNotIssuedRecords(GOODS_ISSUE_RECORD *records, uint8_t size)
{
    uint8_t num = std::min<uint8_t>(size, static_cast<uint8_t>(mGoodsNotIssuedRecords.size()));
    auto it = mGoodsNotIssuedRecords.begin();
    for (uint8_t i = 0; i < num; ++i, ++it) {
        records[i] = *it;
    }
    return num;
}

uint8_t RoleData::GetGoodsNotPostRecords(GOODS_ISSUE_RECORD* records, uint8_t size)
{
	uint8_t num = std::min<uint8_t>(size, static_cast<uint8_t>(mGoodsNotPostRecords.size()));
	auto it = mGoodsNotPostRecords.begin();
	for (uint8_t i = 0; i < num; ++i, ++it) {
		records[i] = *it;
	}
	return num;
}

void RoleData::RemoveGoodsNotIssuedRecords(const char orderNoList[MAX_GOODS_ISSUE_RECORD][ORDER_NO_BUFLEN], uint8_t num)
{
    for (uint8_t i = 0; i < num; ++i) {
        for (auto it = mGoodsNotIssuedRecords.begin(); it != mGoodsNotIssuedRecords.end(); ++it) {
            if (strcmp(it->order_no, orderNoList[i]) == 0) {
				mGoodsNotIssuedRecords.erase(it);
                break;
            }
        }
    }
}

void RoleData::UpdateGoodsNotPostRecords(const char orderNoList[MAX_GOODS_POST_RECORD][ORDER_NO_BUFLEN], uint8_t num)
{
	for (uint8_t i = 0; i < num; ++i) {
		for (auto it = mGoodsNotPostRecords.begin(); it != mGoodsNotPostRecords.end(); ++it) {
			if (strcmp(it->order_no, orderNoList[i]) == 0) {
				mGoodsNotPostRecords.erase(it);
				break;
			}
		}
	}
}

void RoleData::SyncPlayerGender(uint8_t gender)
{
	mBriefInfo.gender = gender;
}

void RoleData::UpdateBriefInfo(const ROLE_BRIEF_INFO& briefInfo)
{
#define COM_BRIEF(member) if (briefInfo.member != mBriefInfo.member) mRoleBriefInfoFlagArray[role_brief_info_flag::flag_brief_##member] = 1;

	COM_BRIEF(head);
	COM_BRIEF(level);
	COM_BRIEF(status);
	COM_BRIEF(job);
	COM_BRIEF(hair);
	COM_BRIEF(hair_color);
	COM_BRIEF(gender);
	COM_BRIEF(weapon);
	COM_BRIEF(clothes);
	COM_BRIEF(gssvrid);
	COM_BRIEF(vipLevel);
	COM_BRIEF(is_lock);

	mBriefInfo = briefInfo;
}

void RoleData::UpDataExtraInfo(const ROLE_EXTRA_INFO& extraInfo)
{
#define COM_EXTRA(member) if (mRoleExtraInfo.member != extraInfo.member) mRoleExtraInfoFlagArray[role_extra_info_flag::flag_extra_##member] = 1;
	COM_EXTRA(login_time);
	COM_EXTRA(hp);
	COM_EXTRA(mp);
	COM_EXTRA(exp);
	COM_EXTRA(mapid);
	COM_EXTRA(posx);
	COM_EXTRA(posy);
	COM_EXTRA(dir);
	COM_EXTRA(gold);
	COM_EXTRA(bindGold);
	COM_EXTRA(ingot);
	COM_EXTRA(bindIngot);
	COM_EXTRA(integral);
	COM_EXTRA(depositGold);
	COM_EXTRA(innerForceExp);
	COM_EXTRA(atkMode);
	COM_EXTRA(birthMap);
	COM_EXTRA(redNameMap);
	COM_EXTRA(rolePk);
	COM_EXTRA(modelID);

	mRoleExtraInfo = extraInfo;
}

void RoleData::UpdataRoleSettingsInfo(const ROLE_SETTINGS& settingInfo)
{
	if (!mRoleSettings.Comp(settingInfo)){
		mRoleSettings = settingInfo;
		mRoleSettingFlag = true;
	}
}

void RoleData::SyncRoleInfoToDB(uint64_t userid)
{
	ProtoCS_SyncRoleInfo info;
	info.guid = mBriefInfo.guid;
	GenerateBriefInfo(info);
	GenerateExtraInfo(info);

	if (mRoleSettingFlag) {
		info.setFlag = 1;
		info.roleset = mRoleSettings;
		mRoleSettingFlag = false;
	}

	if (info.briefInfoNum || info.extraInfoNum || info.setFlag) {
		SendDataBySessionType(SESSION_TYPE_CS2DB, info);
	}
}

void RoleData::SyncItemDynAttrsList(uint64_t userid)
{
    // 目前ms没有删除属性操作,暂时不考虑删除判断

    ITEM_DYN_ATTRS_LIST itemDiffAttrs;

    for (const auto &newItemAttrs : mItemDynAttrsList) {

        bool found = false;

        for (auto it = mSyncItemDynAttrsList.begin(); it != mSyncItemDynAttrsList.end(); ++it) {

            auto &oldItemAttrs = *it;

            if (newItemAttrs.guid != oldItemAttrs.guid) continue;

            found = true;

            const auto &newAttrs = newItemAttrs.dyn_attrs;
            auto &oldAttrs = oldItemAttrs.dyn_attrs;

            DYN_ATTRS diffAttrs;
            CollectDiffItemDynAttrs(newAttrs, oldAttrs, diffAttrs);

            if (!diffAttrs.empty()) {
                itemDiffAttrs.emplace_back(newItemAttrs.guid, std::move(diffAttrs));
            }

            mSyncItemDynAttrsList.erase(it);
            break;
        }

        if (!found) itemDiffAttrs.push_back(newItemAttrs);
    }

    if (!itemDiffAttrs.empty()) {
	    ProtoMS_SyncItemDynAttrs data;
        data.playerid = userid;
        data.roleid = mBriefInfo.guid;
        data.attrs_list = &itemDiffAttrs;
	    SendDataBySessionType(SESSION_TYPE_CS2DB, data);
    }

	mSyncItemDynAttrsList = mItemDynAttrsList;
}

void RoleData::CollectDiffItemDynAttrs(const DYN_ATTRS &newAttrs, DYN_ATTRS &oldAttrs,
                                       DYN_ATTRS &diffAttrs)
{
    for (const auto &newAttr : newAttrs) {

        bool found = false;

        for (auto it = oldAttrs.begin(); it != oldAttrs.end(); ++it) {

            auto &oldAttr = *it;

            if (oldAttr.index != newAttr.index) continue;

            found = true;

            if (oldAttr != newAttr) diffAttrs.push_back(newAttr);

            oldAttrs.erase(it);
            break;
        }

        if (!found) diffAttrs.push_back(newAttr);
    }
}

void RoleData::SyncRoleTitleToDB()
{
	ProtoMS_SyncTitleInfo data;
	data.guid = mBriefInfo.guid;
	Title::GetInstance()->GenerateSyncInfoToDB(data.guid, data.num, data.info);
	if (data.num) {
		SendDataBySessionType(SESSION_TYPE_CS2DB, data);
	}
}

void RoleData::SyncQuickBarSetToDB()
{
	if (mQuickBarSetFlag.empty())return;
	ProtoCS_SyncQuickBarSet req;
	for (auto i:mQuickBarSetFlag) {
		auto item = GetQuickBarSet(i);
		if (nullptr == item) continue;
		req.info[req.num].role_id = mBriefInfo.guid;
		req.info[req.num].quick = *item;
		++req.num; 
	}
	mQuickBarSetFlag.clear();
	SendDataBySessionType(SESSION_TYPE_CS2DB, req);
}

void RoleData::UpdateQuickBarSetFlag(const unsigned char mslot)
{
	auto iter = find(mQuickBarSetFlag.begin(), mQuickBarSetFlag.end(), mslot);
	if (iter != mQuickBarSetFlag.end())return;
	mQuickBarSetFlag.push_back(mslot);
}

void RoleData::GenerateBriefInfo(ProtoCS_SyncRoleInfo& info)
{
#define my_macro(member)\
	if (mRoleBriefInfoFlagArray[role_brief_info_flag::flag_brief_##member]) {\
		info.briefInfoKey[info.briefInfoNum] = role_brief_info_flag::flag_brief_##member;\
		info.briefInfoVal[info.briefInfoNum] = mBriefInfo.member;\
		info.briefInfoNum++;\
		mRoleBriefInfoFlagArray[role_brief_info_flag::flag_brief_##member] = 0;\
	}

	my_macro(head);
	my_macro(level);
	my_macro(status);
	my_macro(job);
	my_macro(hair);
	my_macro(hair_color);
	my_macro(gender);
	my_macro(weapon);
	my_macro(clothes);
	my_macro(gssvrid);
	my_macro(vipLevel);
	my_macro(is_lock);
}

void RoleData::GenerateExtraInfo(ProtoCS_SyncRoleInfo& info)
{
#define my_macro(member)\
	if (mRoleExtraInfoFlagArray[role_extra_info_flag::flag_extra_##member]) {\
		info.extraInfoKey[info.extraInfoNum] = role_extra_info_flag::flag_extra_##member;\
		info.extraInfoVal[info.extraInfoNum] = mRoleExtraInfo.member;\
		info.extraInfoNum++;\
		mRoleExtraInfoFlagArray[role_extra_info_flag::flag_extra_##member] = 0;\
	}

	my_macro(login_time);
	my_macro(hp);
	my_macro(mp);
	my_macro(exp);
	my_macro(mapid);
	my_macro(posx);
	my_macro(posy);
	my_macro(dir);
	my_macro(gold);
	my_macro(bindGold);
	my_macro(ingot);
	my_macro(bindIngot);
	my_macro(integral);
	my_macro(depositGold);
	my_macro(innerForceExp);
	my_macro(atkMode);
	my_macro(birthMap);
	my_macro(rebirthMap);
	my_macro(redNameMap);
	my_macro(rolePk);
	my_macro(modelID);
}
