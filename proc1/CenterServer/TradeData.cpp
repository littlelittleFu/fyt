#include "stdafx.h"
#include "TradeData.h"

#include "SessionFactory.h"
#include "CNetManager.h"
#include "mail_table.h"
#include "UserMgr.h"
#include "CenterServer.h"

IMPL_SINGLETON(TradeData)

#define CHECK_EXPIRE_TIME	10	    // ÿ��10����һ��,��λ��

TradeData::TradeData()
{
    mBuyDelegate.clear();
    mSellDelegate.clear();
    mNameChange.clear();

    TimerData timer;
    timer.interval = S2MS(CHECK_EXPIRE_TIME);
    timer.loop = true;
    timer.callBack = [this](const TimerData&) {
        // ��⵽��
        CheckDelegateExpired();
        CheckRecordsExpired();
    };
    mCheckExpireTimerID = ITimeHelper::GetInstance()->AddTimer(timer);
}

TradeData::~TradeData() 
{

    if (mCheckExpireTimerID != 0)
    {
        ITimeHelper::GetInstance()->RemoveTimer(mCheckExpireTimerID);
        mCheckExpireTimerID = 0;
    }
}

void TradeData::SendTradeDelegateToMS()
{
    SendTradeBuyDelegateToMS();
    SendTradeSellDelegateToMS();
}

void TradeData::SendTradeRecordsToMS()
{
    ProtoCS_GetTradeRecordsAck data;
    data.num = 0;
    data.packIdx = 0;
    auto iter = mTradeRecord.begin();
    for (; iter != mTradeRecord.end();)
    {
        data.trade_record[data.num] = *iter->second;
        data.num++;
        iter++;
        if (data.num >= ProtoCS_GetTradeRecordsAck::GTRA_MaxSize::Info_Size
            || iter == mTradeRecord.end())
        {
            data.packIdx++;
            // ���һ������0
            if (iter == mTradeRecord.end()) data.packIdx = 0;
            SendDataBySessionType(SESSION_TYPE_CS2MS, data);
            data.num = 0;
        }
    }
}

void TradeData::HandleGetTradeRecordsAck(ProtoCS_GetTradeRecordsAck& msg)
{
    for (uint16_t i = 0; i < msg.num; i++)
    {
        mTradeRecord[msg.trade_record[i].logTradeData.tradeId] = std::make_shared<TRADE_RECORD>(msg.trade_record[i]);
    }
    // ���һ�����ݰ�
    if (0 == msg.packIdx)
    {
        SetHasRecords(true);
    }
}

void TradeData::HandleGetTradeBuyDelegateAck(ProtoCS_GetTradeBuyDelegateAck& msg)
{
    uint64_t curTime = 0;
    int64_t leftTime = 0;
    uint16_t idx = 0;
    GenerateCurTime(curTime);
	for (uint16_t i = 0; i < msg.num ; i++)
	{
        auto pConfig = sItemConfig.Get(msg.delegateInfo[i].item_template_id);
        if (!pConfig)
        {
            LOG_ERROR("[%s:%d] ��Ϣ�쳣1. itemId:%u", FUNC_LINE, msg.delegateInfo[i].item_template_id);
        }
        else
        {
            strcpy_s(msg.delegateInfo[i].item_name, pConfig->Name);
        }
        leftTime = int64_t(msg.delegateInfo[i].td_time) + msg.delegateInfo[i].trade_time - curTime;
        msg.delegateInfo[i].time = static_cast<uint32_t>(leftTime);
        mBuyDelegate[msg.delegateInfo[i].id] = std::make_shared<DELEGATE_BUY_ITEM2>(msg.delegateInfo[i]);
        // δ����
        if (leftTime > CHECK_EXPIRE_TIME)// CHECK_EXPIRE_TIME��ĺܴ�ʱ,������ms
        {
            if (idx != i)  std::swap(msg.delegateInfo[i], msg.delegateInfo[idx]);
            idx++;
        }
    }
    msg.num = idx;
    // ���һ�����ݰ�
    if (0 == msg.packIdx)
    {
        SetHasBuyDelegate(true);
    }
}

void TradeData::HandleGetTradeSellDelegateAck(ProtoCS_GetTradeSellDelegateAck& msg)
{
    uint64_t curTime = 0;
    int64_t leftTime = 0;
    uint16_t idx = 0;
    GenerateCurTime(curTime);
    for (uint16_t i = 0; i < msg.num; i++)
    {
        leftTime = int64_t(msg.delegateInfo[i].td_time) + msg.delegateInfo[i].trade_time - curTime;
        msg.delegateInfo[i].time = static_cast<uint32_t>(leftTime);
        mSellDelegate[msg.delegateInfo[i].id] = std::make_shared<DELEGATE_SELL_ITEM>(msg.delegateInfo[i]);
        // δ����
        if (leftTime > CHECK_EXPIRE_TIME)// CHECK_EXPIRE_TIME��ĺܴ�ʱ,������ms
        {
            if (idx != i)  std::swap(msg.delegateInfo[i], msg.delegateInfo[idx]);
            idx++;
        }
    }
    msg.num = idx;
    // ���һ�����ݰ�
    if (0 == msg.packIdx)
    {
        SetHasSellDelegate(true);
    }
}

void TradeData::HandleDelegateCancelAck(const ProtoCS_DelegateCancelAck& ack)
{
    if (ack.err_type) return;

    if (delegate_type_sell == ack.delegate_type)
    {
        HandleDelegateSellCancelAck(ack);
    }
    else if (delegate_type_buy == ack.delegate_type)
    {
        HandleDelegateBuyCancelAck(ack);
    }
}

void TradeData::GiveBackSellItem(uint64_t guid, const std::string& name, const ITEM_INFO& item, uint32_t token, const std::string& text)
{
    uint64_t itemGuid = GenerateObjID(E_OBJ_ITEM, ConfigInfo::GetInstance());
    // ͳһ���ﴦ�������item
    ProtoCS_MarketSellAck ack;
    ack.remove = 2;
    ack.item = item;
    ack.item.base_info.guid = itemGuid;
    SendDataBySessionType(SESSION_TYPE_CS2DB, ack);

    // ͨ���ʼ������ϼ�ʧ�ܵ���Ʒ
    MAIL_INFO mail;
    mail.status = mail_status_unread;//δ��
    strcpy_s(mail.title, sizeof(mail.title), "�������ʼ�");
    strcpy_s(mail.text, sizeof(mail.text), text.c_str());
    // ��һ����Ʒbitλ
    mail.addition_item_num = 1;
    mail.status += 0x00000001 << (mail.addition_item_num + 2);
    mail.mail_addition_item_info[0].item_id = item.base_info.id;
    strcpy_s(mail.mail_addition_item_info[0].item_name, sizeof(mail.mail_addition_item_info[0].item_name), item.base_info.name);
    mail.mail_addition_item_info[0].item_guid = itemGuid;
    mail.mail_addition_item_info[0].count = item.base_info.amount;
    mail.mail_addition_item_info[0].bind_status = item.base_info.is_bound;
    mail.type = eMail_Type_Trade; 
    GenerateCurTime(mail.send_timesmap);
    mail::GetInstance()->AddMailToDB(guid, name, mail, token);
}

void TradeData::HandleDelegateSellAck(const ProtoCS_DelegateSellAck& ack)
{
    if (ack.err_type) return GiveBackSellItem(ack.sellItem.seller_guid, std::string(ack.sellItem.seller), ack.sellItem.item, ack.token, "�ϼ��쳣,������Ʒ");

    mSellDelegate[ack.sellItem.id] = std::make_shared<DELEGATE_SELL_ITEM>(ack.sellItem);
}

void TradeData::HandleDelegateBuyAck(const ProtoCS_DelegateBuyAck& ack)
{
    if (ack.err_type) return;

    mBuyDelegate[ack.buyItem.id] = std::make_shared<DELEGATE_BUY_ITEM2>(ack.buyItem);
}

void TradeData::HandleMarketBuyCmd(ProtoMS_MarketBuyCmd& req)
{
    auto sellIt = mSellDelegate.find(req.trade_id);
    if (sellIt == mSellDelegate.end()) return;
    FlushTradeTaxRate();

    auto sellDelegateInfo = sellIt->second;

    uint32_t buyMaxCount = std::min<uint32_t>(sellDelegateInfo->item.base_info.amount, req.count);
    sellDelegateInfo->item.base_info.amount -= buyMaxCount;

    ProtoCS_MarketBuyAck ack;
    ack.trade_id = req.trade_id;
    ack.item = sellDelegateInfo->item;
    ack.buyer_guid = req.buyer_guid;
    strcpy_s(ack.buyer, sizeof(ack.buyer), req.buyer);
    ack.count = buyMaxCount;
    ack.token = req.token;

    uint64_t itemGuid = GenerateObjID(E_OBJ_ITEM, ConfigInfo::GetInstance());
    if (0 == sellDelegateInfo->item.base_info.amount)
    {
        ack.remove = 1;
        mSellDelegate.erase(sellIt);
    }
    // �򵽵���Ʒ��Ϣ
    ack.item.base_info.guid = itemGuid;
    ack.item.base_info.role = req.buyer_guid;
    ack.item.base_info.amount = buyMaxCount;
    TRADE_RECORD tr;
    tr.item = ack.item;
    SendDataBySessionType(SESSION_TYPE_CS2DB, ack);
    SendDataBySessionType(SESSION_TYPE_CS2MS, ack);

    // ��־
    tr.logTradeData = LogTradeData(req.trade_id, delegate_type_buy, sellDelegateInfo->value_type, sellDelegateInfo->item.base_info.guid, itemGuid, std::string(sellDelegateInfo->item.base_info.name),
        sellDelegateInfo->item.base_info.id, sellDelegateInfo->item_value, buyMaxCount, req.buyer_guid, sellDelegateInfo->seller_guid, MS2S(GetTimeStampMillisecond()), sellDelegateInfo->trade_time);
    SendDBLogData(log_type_trade_data, tr.logTradeData);
    // ��¼
    ProtoCS_GetTradeRecordsAck gtrAck;
    gtrAck.trade_record[gtrAck.num++] = tr;
    SendDataBySessionType(SESSION_TYPE_CS2MS, gtrAck);
    HandleGetTradeRecordsAck(gtrAck);

    // ������������ʼ�
    MAIL_INFO buyMail;
    buyMail.status = mail_status_unread;//δ��
    strcpy_s(buyMail.title, sizeof(buyMail.title), "�������ʼ�");
    strcpy_s(buyMail.text, sizeof(buyMail.text), "��������Ʒ");
    buyMail.addition_item_num = 1;
    buyMail.status += 0x00000001 << (buyMail.addition_item_num + 2);
    buyMail.mail_addition_item_info[0].item_id = sellDelegateInfo->item.base_info.id;
    strcpy_s(buyMail.mail_addition_item_info[0].item_name, sizeof(buyMail.mail_addition_item_info[0].item_name), sellDelegateInfo->item.base_info.name);
    buyMail.mail_addition_item_info[0].item_guid = itemGuid;
    buyMail.mail_addition_item_info[0].count = buyMaxCount;
    buyMail.mail_addition_item_info[0].bind_status = sellDelegateInfo->item.base_info.is_bound;
    buyMail.type = eMail_Type_Trade; 
    GenerateCurTime(buyMail.send_timesmap);
    mail::GetInstance()->AddMailToDB(req.buyer_guid, std::string(req.buyer), buyMail, ack.token);

    // ������������ʼ�
    MAIL_INFO sellMail;
    sellMail.status = mail_status_unread;//δ��
    strcpy_s(sellMail.title, sizeof(sellMail.title), "�������ʼ�");
    strcpy_s(sellMail.text, sizeof(sellMail.text), "�۳���Ʒ�������");
    sprintf(sellMail.text + strlen(sellMail.text), ",ͬʱ�۳�����%.1lf%%��˰��", (TradeTaxRate * 1.0) / 100);
    auto amount = std::floor((int64_t(buyMaxCount) * sellDelegateInfo->item_value) * ((10000 - TradeTaxRate) * PRECISION));
    mail::GetInstance()->FillCurrencyInfo(sellDelegateInfo->value_type, amount, sellMail);
    sellMail.type = eMail_Type_Trade; 
    GenerateCurTime(sellMail.send_timesmap);
    mail::GetInstance()->AddMailToDB(sellDelegateInfo->seller_guid, std::string(sellDelegateInfo->seller), sellMail, ack.token);

    SendToPlatform(PlatformTradeInfo(sellDelegateInfo->seller_guid, std::string(sellDelegateInfo->seller)));
}

void TradeData::HandleMarketSellCmd(ProtoMS_MarketSellCmd& req)
{
    auto buyIt = mBuyDelegate.find(req.trade_id);
    if (buyIt == mBuyDelegate.end())
    {
        req.item.base_info.amount = req.count;
        GiveBackSellItem(req.seller_guid, std::string(req.seller), req.item, req.token, "�����쳣,������Ʒ");
        return;
    }
    FlushTradeTaxRate();

    auto buyDelegateInfo = buyIt->second;

    uint32_t sellMaxCount = std::min<uint32_t>(buyDelegateInfo->item_num, req.count);
    buyDelegateInfo->item_num -= sellMaxCount;

    ProtoCS_MarketSellAck ack;
    ack.trade_id = req.trade_id;
    ack.item = req.item;
    ack.seller_guid = req.seller_guid;
    strcpy_s(ack.seller, sizeof(ack.seller), req.seller);
    ack.count = sellMaxCount;
    ack.token = req.token;

    uint64_t itemGuid = GenerateObjID(E_OBJ_ITEM, ConfigInfo::GetInstance());
    if (0 == buyDelegateInfo->item_num)
    {
        ack.remove = 1;
        mBuyDelegate.erase(buyIt);
    }
    // ��������Ʒ��Ϣ
    ack.item.base_info.guid = itemGuid;
    ack.item.base_info.role = buyDelegateInfo->buyer_guid;
    ack.item.base_info.amount = sellMaxCount;
    TRADE_RECORD tr;
    tr.item = ack.item;
    SendDataBySessionType(SESSION_TYPE_CS2DB, ack);
    ack.item = req.item;
    SendDataBySessionType(SESSION_TYPE_CS2MS, ack);

    // ��־
    tr.logTradeData = LogTradeData(req.trade_id, delegate_type_sell, buyDelegateInfo->value_type, req.item.base_info.guid, itemGuid, std::string(buyDelegateInfo->item_name),
        buyDelegateInfo->item_template_id, buyDelegateInfo->item_value, sellMaxCount, buyDelegateInfo->buyer_guid, req.seller_guid, MS2S(GetTimeStampMillisecond()), buyDelegateInfo->trade_time);
    SendDBLogData(log_type_trade_data, tr.logTradeData);
    // ��¼
    ProtoCS_GetTradeRecordsAck gtrAck;
    gtrAck.trade_record[gtrAck.num++] = tr;
    SendDataBySessionType(SESSION_TYPE_CS2MS, gtrAck);
    HandleGetTradeRecordsAck(gtrAck);

    // ����������ʼ�
    MAIL_INFO buyMail;
    buyMail.status = mail_status_unread;//δ��
    strcpy_s(buyMail.title, sizeof(buyMail.title), "�������ʼ�");
    strcpy_s(buyMail.text, sizeof(buyMail.text), "��������Ʒ");
    // ��һ����Ʒbitλ
    buyMail.addition_item_num = 1;
    buyMail.status += 0x00000001 << (buyMail.addition_item_num + 2);
    buyMail.mail_addition_item_info[0].item_id = buyDelegateInfo->item_template_id;
    strcpy_s(buyMail.mail_addition_item_info[0].item_name, sizeof(buyMail.mail_addition_item_info[0].item_name), buyDelegateInfo->item_name);
    buyMail.mail_addition_item_info[0].item_guid = itemGuid;
    buyMail.mail_addition_item_info[0].count = sellMaxCount;
    buyMail.mail_addition_item_info[0].bind_status = 1;
    buyMail.type = eMail_Type_Trade; 
    GenerateCurTime(buyMail.send_timesmap);
    mail::GetInstance()->AddMailToDB(buyDelegateInfo->buyer_guid, std::string(buyDelegateInfo->buyer), buyMail, ack.token);

    // ������������ʼ�
    MAIL_INFO sellMail;
    sellMail.status = mail_status_unread;//δ��
    strcpy_s(sellMail.title, sizeof(sellMail.title), "�������ʼ�");
    strcpy_s(sellMail.text, sizeof(sellMail.text), "�۳���Ʒ�������");
    sprintf(sellMail.text + strlen(sellMail.text), ",ͬʱ�۳�����%.1lf%%��˰��", (TradeTaxRate * 1.0) / 100);
    auto amount = std::floor((int64_t(sellMaxCount) * buyDelegateInfo->item_value) * ((10000 - TradeTaxRate) * PRECISION));
    mail::GetInstance()->FillCurrencyInfo(buyDelegateInfo->value_type, amount, sellMail);
    sellMail.type = eMail_Type_Trade; 
    GenerateCurTime(sellMail.send_timesmap);
    mail::GetInstance()->AddMailToDB(req.seller_guid, std::string(req.seller), sellMail, ack.token);

    if (req.count > sellMaxCount)
    {
        req.item.base_info.amount = req.count - sellMaxCount;
        GiveBackSellItem(req.seller_guid, std::string(req.seller), req.item, req.token, "��������,������Ʒ");
    }

    SendToPlatform(PlatformTradeInfo(req.seller_guid, std::string(req.seller)));
}

void TradeData::FlushTradeTaxRate()
{
    auto global = sGlobalConfig.GetData();
    if (global)
    {
        if (global->TradeTaxRate <= 10000)
        {
            TradeTaxRate = global->TradeTaxRate;
        }
    }
}

void TradeData::HandleDelegateSellCancelAck(const ProtoCS_DelegateCancelAck& ack)
{
	auto sellIt = mSellDelegate.find(ack.trade_id);
	if (sellIt == mSellDelegate.end())
	{
		LOG_ERROR("[%s:%d] tradeid:%" PRIu64 " not exist.", FUNC_LINE, ack.trade_id);
	}
	else
	{
        // ͨ���ʼ������ϼ�ʱ����Ʒ
        auto& sellDelegateInfo = sellIt->second;
        MAIL_INFO mail;
        mail.status = mail_status_unread;//δ��
        strcpy_s(mail.title, sizeof(mail.title), "�������ʼ�");
        if (delegate_cancel_manual == ack.reason)
            strcpy_s(mail.text, sizeof(mail.text), "����ȡ���ϼ�,������Ʒ");
        else if (delegate_cancel_expired == ack.reason)
            strcpy_s(mail.text, sizeof(mail.text), "��ʱȡ���ϼ�,������Ʒ");
        else if (delegate_cancel_delete_role == ack.reason)
            strcpy_s(mail.text, sizeof(mail.text), "ɾ����ɫȡ���ϼ�,������Ʒ");
        // ��һ����Ʒbitλ
        mail.addition_item_num = 1;
        mail.status += 0x00000001 << (mail.addition_item_num + 2);
        mail.mail_addition_item_info[0].item_id = sellDelegateInfo->item.base_info.id;
        strcpy_s(mail.mail_addition_item_info[0].item_name, sizeof(mail.mail_addition_item_info[0].item_name), sellDelegateInfo->item.base_info.name);
        mail.mail_addition_item_info[0].item_guid = sellDelegateInfo->item.base_info.guid;
        mail.mail_addition_item_info[0].count = sellDelegateInfo->item.base_info.amount;
        mail.mail_addition_item_info[0].bind_status = sellDelegateInfo->item.base_info.is_bound;
        mail.type = eMail_Type_Trade; 
        GenerateCurTime(mail.send_timesmap);
        mail::GetInstance()->AddMailToDB(sellDelegateInfo->seller_guid, std::string(sellDelegateInfo->seller), mail, ack.token);
        mSellDelegate.erase(sellIt);  
	}
}

void TradeData::HandleDelegateBuyCancelAck(const ProtoCS_DelegateCancelAck& ack)
{
	auto buyIt = mBuyDelegate.find(ack.trade_id);
	if (buyIt == mBuyDelegate.end())
	{
		LOG_ERROR("[%s:%d] tradeid:%" PRIu64 " not exist.", FUNC_LINE, ack.trade_id);
	}
	else
	{
        // ͨ���ʼ�������ʱ�۳��Ľ��/Ԫ��
        auto& buyDelegateInfo = buyIt->second;
        MAIL_INFO mail;
        mail.status = mail_status_unread;//δ��
        strcpy_s(mail.title, sizeof(mail.title), "�������ʼ�");
        if (delegate_cancel_manual == ack.reason)
            strcpy_s(mail.text, sizeof(mail.text), "����ȡ���չ�,������Ʒ");
        else if (delegate_cancel_expired == ack.reason)
            strcpy_s(mail.text, sizeof(mail.text), "��ʱȡ���չ�,������Ʒ");
        else if (delegate_cancel_delete_role == ack.reason)
            strcpy_s(mail.text, sizeof(mail.text), "ɾ����ɫȡ���ϼ�,������Ʒ");
        auto amount = buyDelegateInfo->item_value * buyDelegateInfo->item_num;
        mail::GetInstance()->FillCurrencyInfo(buyDelegateInfo->value_type, amount, mail);
        mail.addition_item_num = 0;
        mail.type = eMail_Type_Trade; 
        GenerateCurTime(mail.send_timesmap);
        mail::GetInstance()->AddMailToDB(buyDelegateInfo->buyer_guid, std::string(buyDelegateInfo->buyer), mail, ack.token);
        mBuyDelegate.erase(buyIt);
	}
}

void TradeData::SendTradeBuyDelegateToMS()
{
    ProtoCS_GetTradeBuyDelegateAck data;
    data.num = 0;
    data.packIdx = 0;
    auto iter = mBuyDelegate.begin();
    for (; iter != mBuyDelegate.end();)
    {
        data.delegateInfo[data.num] = *iter->second;
        data.num++;
        iter++;
        if (data.num >= ProtoCS_GetTradeBuyDelegateAck::GTIA_MaxSize::Info_Size
            || iter == mBuyDelegate.end())
        {
            data.packIdx++;
            // ���һ������0
            if (iter == mBuyDelegate.end()) data.packIdx = 0;
            SendDataBySessionType(SESSION_TYPE_CS2MS, data);
            data.num = 0;
        }
    }
}

void TradeData::SendTradeSellDelegateToMS()
{
    ProtoCS_GetTradeSellDelegateAck data;
    data.num = 0;
    data.packIdx = 0;
    auto iter = mSellDelegate.begin();
    for (; iter != mSellDelegate.end();)
    {
        data.delegateInfo[data.num] = *iter->second;
        data.num++;
        iter++;
        if (data.num >= ProtoCS_GetTradeSellDelegateAck::GTIA_MaxSize::Info_Size
            || iter == mSellDelegate.end())
        {
            data.packIdx++;
            // ���һ������0
            if (iter == mSellDelegate.end()) data.packIdx = 0;
            SendDataBySessionType(SESSION_TYPE_CS2MS, data);
            data.num = 0;
        }
    }
}

void TradeData::CheckRecordsExpired()
{
    std::set<uint64_t> allExpiredSet;
    std::set<uint64_t> allExpiredItemSet;
    uint64_t curTime = 0;
    GenerateCurTime(curTime);

    uint32_t tradeRecordsExpireTime = 2592000;
    auto global = sGlobalConfig.GetData();
    if (global && global->TradeRecordsExpireTime)
    {
        tradeRecordsExpireTime = global->TradeRecordsExpireTime;
    }
    if (!mTradeRecord.empty())
    {
        auto iter = mTradeRecord.begin();
        for (; iter != mTradeRecord.end();)
        {
            if (!iter->second) continue;

            if (curTime >= (uint64_t(iter->second->logTradeData.timestamp) + tradeRecordsExpireTime))
            {
                allExpiredSet.insert(iter->first);
                allExpiredItemSet.insert(iter->second->logTradeData.itemGuid);
                iter = mTradeRecord.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }

    if (!allExpiredSet.empty() || !allExpiredItemSet.empty()) SendRecordsExpired(allExpiredSet, allExpiredItemSet);
}

void TradeData::CheckDelegateExpired()
{
    std::set<uint64_t> buyExpiredSet, sellExpiredSet;
    uint64_t curTime = 0;
    GenerateCurTime(curTime);

    if (!mBuyDelegate.empty())
    {
        auto iter = mBuyDelegate.begin();
        for (; iter != mBuyDelegate.end(); ++iter)
        {
            if (!iter->second) continue;

            if (curTime >= (uint64_t(iter->second->trade_time) + iter->second->td_time))
            {
                buyExpiredSet.insert(iter->first);
            }
            auto it = mNameChange.find(iter->second->buyer_guid);
            if (it != mNameChange.end())
            {
                strcpy_s(iter->second->buyer, _countof(iter->second->buyer), it->second);
            }
        }
    }
    if (!mSellDelegate.empty())
    {
        auto iter = mSellDelegate.begin();
        for (; iter != mSellDelegate.end(); ++iter)
        {
            if (!iter->second) continue;

            if (curTime >= (uint64_t(iter->second->trade_time) + iter->second->td_time))
            {
                sellExpiredSet.insert(iter->first);
            }
            auto it = mNameChange.find(iter->second->seller_guid);
            if (it != mNameChange.end())
            {
                strcpy_s(iter->second->seller, _countof(iter->second->seller), it->second);
            }
        }
    }
    mNameChange.clear();
    if (!buyExpiredSet.empty()) SendDelegateExpired(delegate_type_buy, buyExpiredSet);
    if (!sellExpiredSet.empty()) SendDelegateExpired(delegate_type_sell, sellExpiredSet);
}

void TradeData::SendRecordsExpired(std::set<uint64_t>& expiredSet, std::set<uint64_t>& allExpiredItemSet)
{
    ProtoCS_RecordsCancelAck msg;

    {
    auto iter = expiredSet.begin();
    while (iter != expiredSet.end())
    {
        msg.trade_id[msg.num++] = *iter;
        ++iter;
        if (ProtoCS_RecordsCancelAck::RCA_MaxSize::Info_Size == msg.num)
        {
            SendDataBySessionType(SESSION_TYPE_CS2MS, msg);
            msg.num = 0;
        }
    }
    if (msg.num) SendDataBySessionType(SESSION_TYPE_CS2MS, msg);
    }

    ProtoMS_RecordsCancelReq req;

    {
    auto iter = allExpiredItemSet.begin();
    while (iter != allExpiredItemSet.end())
    {
        req.trade_id[req.num++] = *iter;
        ++iter;
        if (ProtoMS_RecordsCancelReq::RCQ_MaxSize::Info_Size == req.num)
        {
            SendDataBySessionType(SESSION_TYPE_CS2DB, req);
            req.num = 0;
        }
    }
    if (req.num) SendDataBySessionType(SESSION_TYPE_CS2DB, req);
    }
}

void TradeData::SendDelegateExpired(uint8_t delegatetype, std::set<uint64_t>& expiredSet, uint8_t reason)
{
    ProtoMS_DelegateCancelReq msg;
    msg.reason = reason;
    if (delegate_type_sell == delegatetype)
    {
        msg.delegate_type = delegate_type_sell;
        auto iter = expiredSet.begin();
        while (iter != expiredSet.end())
        {
            auto it = mSellDelegate.find(*iter);
            if (it != mSellDelegate.end() && it->second)
            {
                msg.player_guid = it->second->seller_guid;
                msg.trade_id = it->first;
                auto user = (*UserMgr::GetInstance())[it->second->seller_guid];// �ʼ������ÿ�ζ���db,���Լ�����Ҳ�����csû�����ʼ�,���ߺ�������ȡ
                if (user) msg.token = user->GetToken();
                SendDataBySessionType(SESSION_TYPE_CS2DB, msg);
            }
            ++iter;
        }
    }
    else if (delegate_type_buy == delegatetype)
    {
        msg.delegate_type = delegate_type_buy;
        auto iter = expiredSet.begin();
        while (iter != expiredSet.end())
        {
            auto it = mBuyDelegate.find(*iter);
            if (it != mBuyDelegate.end() && it->second)
            {
                msg.player_guid = it->second->buyer_guid;
                msg.trade_id = it->first;
                auto user = (*UserMgr::GetInstance())[it->second->buyer_guid];
                if (user) msg.token = user->GetToken();
                SendDataBySessionType(SESSION_TYPE_CS2DB, msg);
            }
            ++iter;
        }
    }
}

void TradeData::ChangeNameInfo(uint64_t guid, const std::string& name)
{
    mNameChange[guid] = name;
}

void TradeData::HandleAllDelegateCancel(uint64_t roleGuid)
{
    std::set<uint64_t> buyExpiredSet, sellExpiredSet;

    if (!mBuyDelegate.empty())
    {
        auto iter = mBuyDelegate.begin();
        for (; iter != mBuyDelegate.end(); ++iter)
        {
            if (!iter->second) continue;
            if (iter->second->buyer_guid != roleGuid) continue;
           
            buyExpiredSet.insert(iter->first);
        }
    }
    if (!mSellDelegate.empty())
    {
        auto iter = mSellDelegate.begin();
        for (; iter != mSellDelegate.end(); ++iter)
        {
            if (!iter->second) continue;
            if (iter->second->seller_guid != roleGuid) continue;

            sellExpiredSet.insert(iter->first);
        }
    }

    if (!buyExpiredSet.empty()) SendDelegateExpired(delegate_type_buy, buyExpiredSet, delegate_cancel_delete_role);
    if (!sellExpiredSet.empty()) SendDelegateExpired(delegate_type_sell, sellExpiredSet, delegate_cancel_delete_role);
}

size_t TradeData::CURLWriteCallback(void* data, size_t size, size_t nmemb, void* userp)
{
    auto len = size * nmemb;

    auto* resp = static_cast<std::vector<char> *>(userp);

    auto oldSize = resp->size();
    auto newSize = oldSize + len + 1;

    resp->resize(newSize);

    memcpy(resp->data() + oldSize, data, len);

    return len;

}
void TradeData::SendToPlatform(const PlatformTradeInfo& tradeInfo)
{
    auto* cfg = ConfigInfo::GetInstance();
    if (!cfg) return;

    auto url = cfg->m_sPlatformDomain + TRADE_CODE_PATH;

    auto spTradeInfo = std::make_shared<PlatformTradeInfo>(tradeInfo);

    ctpl::task_t task = [=](int) {
        const int HTTP_MSG_LENGTH = 10240;
        char data[HTTP_MSG_LENGTH] = { 0 };

        if (!ComposeHttpRequest(*spTradeInfo, data, _countof(data)))
            return;

        auto* curl = curl_easy_init();
        if (!curl) {
            LOG_ERROR("curl_easy_init failed");
            return;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CURLWriteCallback);
        //std::vector<char> resp;
        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        //if (!resp.empty())
        //{
        //    const char* raw = resp.data();
        //    Json::Value root;
        //    Json::Reader reader;
        //    if (!reader.parse(raw, raw + strlen(raw), root)) {
        //        LOG_ERROR("parse failed, raw: %s", raw);
        //        return;
        //    }
        //    auto code = root["code"].asInt();
        //    auto msg = utf8_to_gbk(root["msg"].asString().c_str());
        //    auto data = root["data"].asBool();
        //}
    };

    auto& threadPool = CenterServer::GetInstance()->GetThreadPool();
    threadPool.push(std::move(task));
}

bool TradeData::ComposeHttpRequest(const PlatformTradeInfo& tradeInfo, char* buf, int bufsz)
{
    ConfigInfo* cfg = ConfigInfo::GetInstance();
    if (!cfg) return false;

    auto gameID = cfg->GetCurAgentId();
    auto regionID = cfg->GetCurAreaId();
    auto serverID = regionID * 1000 + cfg->GetCurAreaServerId();

    sprintf_s(buf, bufsz, "game_id=%u&region_id=%u&server_id=%u&role_id=%s&role_name=%s",
        gameID, regionID, serverID, to_string(tradeInfo.user_id).c_str(), gbk_to_utf8(tradeInfo.user_name).c_str());

    return true;
}