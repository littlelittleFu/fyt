#include "stdafx.h"
#include "ProtoMS.h"
#include <DataInfo.hpp>

static int EncodeEffectAppearNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_EffectAppearNtf);
	ENCODE_WORD(num);
	for (int i = 0; i < pstIn->num; ++i) {
		if (EncodeEFFECT_POINT(&pstIn->info, poNetData) == -1) return -1;
	}
	ENCODE_WORD(type);
	ENCODE_DWORD(sessionid);
	END_ENCODE();
}

static int DecodeEffectAppearNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_EffectAppearNtf);
	DECODE_WORD(num);
	for (int i = 0; i < pstOut->num; ++i) {
		if (DecodeEFFECT_POINT(&pstOut->info, poNetData) == -1) return -1;
	}
	DECODE_WORD(type);
	DECODE_DWORD(sessionid);
	END_DECODE();
}

static int EncodeEffectDisAppearNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_EffectDisAppearNtf);
	ENCODE_WORD(num);
	for (int i = 0; i < pstIn->num; ++i) {
		if (EncodeEFFECT_POINT(&pstIn->info, poNetData) == -1) return -1;
	}
	ENCODE_WORD(type);
	ENCODE_DWORD(sessionid);
	END_ENCODE();
}

static int DecodeEffectDisAppearNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_EffectDisAppearNtf);
	DECODE_WORD(num);
	for (int i = 0; i < pstOut->num; ++i) {
		if (DecodeEFFECT_POINT(&pstOut->info, poNetData) == -1) return -1;
	}
	DECODE_WORD(type);
	DECODE_DWORD(sessionid);
	END_DECODE();
}

static int EncodeSetPlayerGender(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_SetPlayerGender);
	ENCODE_QWORD(userID);
	ENCODE_QWORD(guid);
	ENCODE_BYTE(gender);
	END_ENCODE();
}

static int DecodeSetPlayerGender(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_SetPlayerGender);
	DECODE_QWORD(userID);
	DECODE_QWORD(guid);
	DECODE_BYTE(gender);
	END_DECODE();
}

static int EncodeSendGoodsPostRecordToClient(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_SendGoodsPostRecordToClient);
	ENCODE_DWORD(sessionID);
	if (EncodeGOODS_ISSUE_RECORD(&pstIn->record, poNetData) == -1) return -1;
	END_ENCODE();
}

static int DecodeSendGoodsPostRecordToClient(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_SendGoodsPostRecordToClient);
	DECODE_DWORD(sessionID);
	if (DecodeGOODS_ISSUE_RECORD(&pstOut->record, poNetData) == -1) return -1;
	END_DECODE();
}

static int EncodeGetCustListReq(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_GetCustListReq);
	END_ENCODE();
}

static int DecodeGetCustListReq(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_GetCustListReq);
	END_DECODE();
}

static int EncodeSyncCustList(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_SyncCustList);
	ENCODE_BYTE(optType);
	ENCODE_INT(type);
	ENCODE_WORD(num);
	for (int i = 0; i < pstIn->num; ++i) {
		if (-1 == EncodeCUST_LIST_INFO(&pstIn->data[i], poNetData))return -1;
	}
	END_ENCODE();
}

static int DecodeSyncCustList(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_SyncCustList);
	DECODE_BYTE(optType);
	DECODE_INT(type);
	DECODE_WORD(num);
	for (int i = 0; i < pstOut->num; ++i) {
		if (-1 == DecodeCUST_LIST_INFO(&pstOut->data[i], poNetData))return -1;
	}
	END_DECODE();
}


static int EncodeAddPlayerProhibitChat(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_AddPlayerProhibitChat);
	ENCODE_QWORD(userID);
	ENCODE_INT64(stamp);
	END_ENCODE();
}

static int DecodeAddPlayerProhibitChat(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_AddPlayerProhibitChat);
	DECODE_QWORD(userID);
	DECODE_INT64(stamp);
	END_DECODE();
}

static int EncodeDelPlayerProhibitChat(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_DelPlayerProhibitChat);
	ENCODE_QWORD(userID);
	END_ENCODE();
}

static int DecodeDelPlayerProhibitChat(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_DelPlayerProhibitChat);
	DECODE_QWORD(userID);
	END_DECODE();
}

static int EncodePlayerActivationCode(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_PlayerActivationCode);
	ENCODE_QWORD(info.userid);
	ENCODE_QWORD(info.guid);
	ENCODE_BYTE(info.type);
	ENCODE_STRING(info.code);
	ENCODE_STRING(info.name);
	END_ENCODE();
}

static int DecodePlayerActivationCode(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_PlayerActivationCode);
	DECODE_QWORD(info.userid);
	DECODE_QWORD(info.guid);
	DECODE_BYTE(info.type);
	DECODE_STRING(info.code);
	DECODE_STRING(info.name);
	END_DECODE();
}

static int EncodeMonsterBackNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_MonsterBackNtf);
	ENCODE_QWORD(guid);
	ENCODE_WORD(status);
	ENCODE_DWORD(sessionid);
	END_ENCODE();
}

static int DecodeMonsterBackNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_MonsterBackNtf);
	DECODE_QWORD(guid);
	DECODE_WORD(status);
	DECODE_DWORD(sessionid);
	END_DECODE();
}

static int EncodeAddTitle(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_AddTitle);
	ENCODE_QWORD(guid);
	if (-1 == EnCodeTITLE_INFO(&pstIn->info, poNetData))return -1;
	END_ENCODE();
}

static int DecodeAddTitle(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_AddTitle);
	DECODE_QWORD(guid);
	if (-1 == DeCodeTITLE_INFO(&pstOut->info, poNetData))return -1;
	END_DECODE();
}

static int EncodeDelTitle(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_DelTitle);
	ENCODE_QWORD(guid);
	ENCODE_WORD(num);
	ENCODE_BLOB(id, pstIn->num * sizeof(uint32_t));
	END_ENCODE();
}

static int DecodeDelTitle(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_DelTitle);
	DECODE_QWORD(guid);
	DECODE_WORD(num);
	DECODE_BLOB(id, pstOut->num * sizeof(uint32_t));
	END_DECODE();
}

static int EncodeTitleWearType(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_TitleWearType);
	ENCODE_QWORD(guid);
	ENCODE_DWORD(id);
	ENCODE_WORD(wearType);
	END_ENCODE();
}

static int DecodeTitleWearType(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_TitleWearType);
	DECODE_QWORD(guid);
	DECODE_DWORD(id);
	DECODE_WORD(wearType);
	END_DECODE();
}

static int EncodeSyncTitleInfo(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_SyncTitleInfo);
	ENCODE_QWORD(guid);
	ENCODE_WORD(num);
	for (int i = 0; i < pstIn->num; ++i) {
		if (-1 == EnCodeTITLE_INFO(&pstIn->info[i], poNetData))return -1;
	}
	END_ENCODE();
}

static int DecodeSyncTitleInfo(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_SyncTitleInfo);
	DECODE_QWORD(guid);
	DECODE_WORD(num);
	for (int i = 0; i < pstOut->num; ++i) {
		if (-1 == DeCodeTITLE_INFO(&pstOut->info[i], poNetData))return -1;
	}
	END_DECODE();
}
static int EncodePlayerSetNameReq(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_PlayerSetNameReq);
	ENCODE_QWORD(guid);
	ENCODE_STRING(name);
	END_ENCODE();
}

static int DecodePlayerSetNameReq(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_PlayerSetNameReq);
	DECODE_QWORD(guid);
	DECODE_STRING(name);
	END_DECODE();
}

static int EncodeMonsterPursureAttackingNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_MonsterPursureAttackingNtf);
	ENCODE_QWORD(guid);
	ENCODE_WORD(status);
	ENCODE_DWORD(sessionid);
	END_ENCODE();
}

static int DecodeMonsterPursureAttackingNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_MonsterPursureAttackingNtf);
	DECODE_QWORD(guid);
	DECODE_WORD(status);
	DECODE_DWORD(sessionid);
	END_DECODE();
}

static int EncodeDeleteMallRemainedData(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_DeleteMallRemainedData);
	END_ENCODE();
}

static int DecodeDeleteMallRemainedData(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_DeleteMallRemainedData);
	END_DECODE();
}
static int EncodeAddProhibitChatInfo(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_AddProhibitChatInfo);
	ENCODE_BYTE(num);
	for (int i = 0; i < pstIn->num; ++i)
	{
		if (-1 == EnCodePROHIBIT_CHAT_DATA(&pstIn->infos[i], poNetData)) return -1;
	}
	END_ENCODE();
}

static int DecodeAddProhibitChatInfo(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_AddProhibitChatInfo);
	DECODE_BYTE(num);
	for (int i = 0; i < pstOut->num; ++i)
	{
		if (-1 == DeCodePROHIBIT_CHAT_DATA(&pstOut->infos[i], poNetData)) return -1;
	}
	END_DECODE();
}

static int EncodeDelProhibitInfo(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_DelProhibitInfo);
	ENCODE_BYTE(num);
	for (int i = 0; i < pstIn->num; ++i)
	{
		if (-1 == EnCodePROHIBIT_CHAT_DATA(&pstIn->infos[i], poNetData)) return -1;
	}
	END_ENCODE();
}

static int DecodeDelProhibitInfo(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_DelProhibitInfo);
	DECODE_BYTE(num);
	for (int i = 0; i < pstOut->num; ++i)
	{
		if (-1 == DeCodePROHIBIT_CHAT_DATA(&pstOut->infos[i], poNetData)) return -1;
	}
	END_DECODE();
}

static int EncodeGetProhibitChatInfoReq(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_GetProhibitChatInfoReq);
	END_ENCODE();
}

static int DecodeGetProhibitChatInfoReq(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_GetProhibitChatInfoReq);
	END_DECODE();
}

static int EncodeAddLockRole(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_AddLockRole);
	ENCODE_BYTE(num);
	for (int i = 0; i < pstIn->num; ++i) {
		ENCODE_QWORD(guid[i]);
	}
	END_ENCODE();
}

static int DecodeAddLockRole(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_AddLockRole);
	DECODE_BYTE(num);
	for (int i = 0; i < pstOut->num; ++i) {
		DECODE_QWORD(guid[i]);
	}

	END_DECODE();
}

static int EncodeDelLockRole(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_DelLockRole);
	ENCODE_BYTE(num);
	for (int i = 0; i < pstIn->num; ++i)
	{
		if (-1 == poNetData->AddString(pstIn->name[i]))return -1;
	}
	END_ENCODE();
}

static int DecodeDelLockRole(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_DelLockRole);
	DECODE_BYTE(num);
	for (int i = 0; i < pstOut->num; ++i)
	{
		if (-1 == poNetData->DelString(pstOut->name[i], sizeof(pstOut->name[i])))return -1;
	}
	END_DECODE();
}

static int EncodeAddLockPlayer(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_AddLockPlayer);
	ENCODE_BYTE(num);
	for (int i = 0; i < pstIn->num; ++i)
	{
		if (-1 == poNetData->AddString(pstIn->name[i]))return -1;
	}
	END_ENCODE();
}

static int DecodeAddLockPlayer(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_AddLockPlayer);
	DECODE_BYTE(num);
	for (int i = 0; i < pstOut->num; ++i)
	{
		if (-1 == poNetData->DelString(pstOut->name[i], sizeof(pstOut->name[i])))return -1;
	}
	END_DECODE();
}

static int EncodeUpdateSupportPlayer(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_UpdateSupportPlayer);
	ENCODE_BYTE(num);
	ENCODE_BYTE(type);
	for (int i = 0; i < pstIn->num; ++i)
	{
		if (-1 == poNetData->AddString(pstIn->name[i]))return -1;
		if (-1 == poNetData->AddQword(pstIn->guid[i]))return -1;
	}
	END_ENCODE();
}

static int DecodeUpdateSupportPlayer(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_UpdateSupportPlayer);
	DECODE_BYTE(num);
	DECODE_BYTE(type);
	for (int i = 0; i < pstOut->num; ++i)
	{
		if (-1 == poNetData->DelString(pstOut->name[i], sizeof(pstOut->name[i])))return -1;
		if (-1 == poNetData->DelQword(pstOut->guid[i]))return -1;
	}
	END_DECODE();
}

static int EncodeDelLockPlayer(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_DelLockPlayer);
	ENCODE_BYTE(num);
	for (int i = 0; i < pstIn->num; ++i)
	{
		if (-1 == poNetData->AddString(pstIn->name[i]))return -1;
	}
	END_ENCODE();
}

static int DecodeDelLockPlayer(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_DelLockPlayer);
	DECODE_BYTE(num);
	for (int i = 0; i < pstOut->num; ++i)
	{
		if (-1 == poNetData->DelString(pstOut->name[i], sizeof(pstOut->name[i])))return -1;
	}
	END_DECODE();
}

static int EncodeSetLoginIpType(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_AddLoginIpType);
	ENCODE_BYTE(num);
	ENCODE_BYTE(ip_type);
	ENCODE_INTARRAY(ip, pstIn->num);
	END_ENCODE();
}

static int DecodeSetLoginIpType(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_AddLoginIpType);
	DECODE_BYTE(num);
	DECODE_BYTE(ip_type);
	DECODE_INTARRAY(ip, pstOut->num);
	END_DECODE();
}

static int EncodeDelLoginIpType(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_DelLoginIpType);
	ENCODE_BYTE(num);
	ENCODE_BYTE(ip_type);
	ENCODE_INTARRAY(ip, pstIn->num);
	END_ENCODE();
}

static int DecodeDelLoginIpType(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_DelLoginIpType);
	DECODE_BYTE(num);
	DECODE_BYTE(ip_type);
	DECODE_INTARRAY(ip, pstOut->num);
	END_DECODE();
}
static int EncodeSetServerStatus(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_SetServerStatus);
	ENCODE_BYTE(status);
	END_ENCODE();
}

static int DecodeSetServerStatus(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_SetServerStatus);
	DECODE_BYTE(status);
	END_DECODE();
}
static int EncodeMallLimitInfoReq(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_MallLimitInfoReq);
	END_ENCODE();
}

static int DecodeMallLimitInfoReq(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_MallLimitInfoReq);
	END_DECODE();
}

static int EncodeMallLimitInfoUpdate(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_MallLimitInfoUpdate);
	ENCODE_WORD(num);
	ENCODE_BYTE(limit_type);
	ENCODE_BYTE(opt_type);
	for (int i = 0; i < pstIn->num; ++i)
	{
		if (-1 == EncodeMALL_ITEM_INFO_BASE(&pstIn->data[i], poNetData)) return -1;
	}
	END_ENCODE();
}

static int DecodeMallLimitInfoUpdate(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_MallLimitInfoUpdate);
	DECODE_WORD(num);
	DECODE_BYTE(limit_type);
	DECODE_BYTE(opt_type);
	for (int i = 0; i < pstOut->num; ++i)
	{
		if (-1 == DecodeMALL_ITEM_INFO_BASE(&pstOut->data[i], poNetData)) return -1;
	}
	END_DECODE();
}
static int EncodeGetConstantCfgReq(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_GetConstantCfgReq);
	END_ENCODE();
}

static int DecodeGetConstantCfgReq(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_GetConstantCfgReq);
	END_DECODE();
}

static int EncodeGetAuctionHosueReq(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_GetAuctionHouseReq);
	END_ENCODE();
}

static int DecodeGetAuctionHosueReq(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_GetAuctionHouseReq);
	END_DECODE();
}

static int EncodeAuctionGetFinishedInfoReq(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_AuctionGetFinishedInfoReq);
	ENCODE_DWORD(time);
	ENCODE_STRING(func);
	END_ENCODE();
}

static int DecodeAuctionGetFinishedInfoReq(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_AuctionGetFinishedInfoReq);
	DECODE_DWORD(time);
	DECODE_STRING(func);
	END_DECODE();
}

static int EncodeAddAuctionItemInfo(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_SynAuctionItemInfo);
	ENCODE_WORD(type);
	ENCODE_WORD(num);
	for (int i = 0; i < pstIn->num; ++i)
	{
		if (-1 == EnCodeAUCTION_HOUSE_ITEM_INFO(&pstIn->info[i], poNetData)) return -1;
	}
	END_ENCODE();
}

static int DecodeAddAuctionItemInfo(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_SynAuctionItemInfo);
	DECODE_WORD(type);
	DECODE_WORD(num);
	for (int i = 0; i < pstOut->num; ++i)
	{
		if (-1 == DeCodeAUCTION_HOUSE_ITEM_INFO(&pstOut->info[i], poNetData)) return -1;
	}
	END_DECODE();
}

static int EncodeMarketSellCmd(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_MarketSellCmd);
	ENCODE_QWORD(trade_id);
	ENCODE_QWORD(seller_guid);
	ENCODE_STRING(seller);
	ENCODE_DWORD(count);
	if (-1 == EnCodeITEM_INFO(&pstIn->item, poNetData)) return -1;
	ENCODE_DWORD(token);
	END_ENCODE();
}

static int DecodeMarketSellCmd(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_MarketSellCmd);
	DECODE_QWORD(trade_id);
	DECODE_QWORD(seller_guid);
	DECODE_STRING(seller);
	DECODE_DWORD(count);
	if (-1 == DeCodeITEM_INFO(&pstOut->item, poNetData)) return -1;
	DECODE_DWORD(token);
	END_DECODE();
}

static int EncodeMarketBuyCmd(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_MarketBuyCmd);
	ENCODE_QWORD(trade_id);
	ENCODE_QWORD(buyer_guid);
	ENCODE_STRING(buyer);
	ENCODE_DWORD(count);
	ENCODE_DWORD(token);
	END_ENCODE();
}

static int DecodeMarketBuyCmd(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_MarketBuyCmd);
	DECODE_QWORD(trade_id);
	DECODE_QWORD(buyer_guid);
	DECODE_STRING(buyer);
	DECODE_DWORD(count);
	DECODE_DWORD(token);
	END_DECODE();
}

static int EncodeDelegateSellCmd(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_DelegateSellCmd);
	if (-1 == EnCodeDELEGATE_SELL_ITEM(&pstIn->sellItem, poNetData))return -1;
	ENCODE_DWORD(token);
	END_ENCODE();
}

static int DecodeDelegateSellCmd(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_DelegateSellCmd);
	if (-1 == DeCodeDELEGATE_SELL_ITEM(&pstOut->sellItem, poNetData))return -1;
	DECODE_DWORD(token);
	END_DECODE();
}

static int EncodeDelegateBuyCmd(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_DelegateBuyCmd);
	if (-1 == EnCodeDELEGATE_BUY_ITEM2(&pstIn->buyItem, poNetData))return -1;
	ENCODE_DWORD(token);
	END_ENCODE();
}

static int DecodeDelegateBuyCmd(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_DelegateBuyCmd);
	if (-1 == DeCodeDELEGATE_BUY_ITEM2(&pstOut->buyItem, poNetData))return -1;
	DECODE_DWORD(token);
	END_DECODE();
}

static int EncodeGetTradeDelegateReq(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_GetTradeDelegateReq);
	END_ENCODE();
}

static int DecodeGetTradeDelegateReq(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_GetTradeDelegateReq);
	END_DECODE();
}

static int EncodeGetTradeRecordsReq(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_GetTradeRecordsReq);
    ENCODE_DWORD(tradeRecordsExpireTime);
	END_ENCODE();
}

static int DecodeGetTradeRecordsReq(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_GetTradeRecordsReq);
    DECODE_DWORD(tradeRecordsExpireTime);
	END_DECODE();
}

static int EncodeRecordsCancelReq(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_RecordsCancelReq);
	ENCODE_WORD(num);
	for (uint16_t i = 0; i < pstIn->num; ++i)
	{
		ENCODE_QWORD(trade_id[i]);
	}
	END_ENCODE();
}

static int DecodeRecordsCancelReq(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_RecordsCancelReq);
	DECODE_WORD(num);
	for (uint16_t i = 0; i < pstOut->num; ++i)
	{
		DECODE_QWORD(trade_id[i]);
	}
	END_DECODE();
}

static int EncodeDelegateCancelReq(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_DelegateCancelReq);
	ENCODE_BYTE(delegate_type);
	ENCODE_QWORD(player_guid);
	ENCODE_QWORD(trade_id);
	ENCODE_BYTE(reason);
	ENCODE_DWORD(token);
	END_ENCODE();
}

static int DecodeDelegateCancelReq(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_DelegateCancelReq);
	DECODE_BYTE(delegate_type);
	DECODE_QWORD(player_guid);
	DECODE_QWORD(trade_id);
	DECODE_BYTE(reason);
	DECODE_DWORD(token);
	END_DECODE();
}

static int EncodeDelegateSellListAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_DelegateSellListAck);
	ENCODE_WORD(type);
	ENCODE_WORD(subtype);
	ENCODE_DWORD(total);
	ENCODE_DWORD(start);
	ENCODE_DWORD(count);
	for (uint16_t i = 0; i < pstIn->count; ++i)
	{
		if (-1 == EnCodeDELEGATE_SELL_ITEM(&pstIn->items[i], poNetData))return -1;
	}
	ENCODE_DWORD(sessid);
	END_ENCODE();
}

static int DecodeDelegateSellListAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_DelegateSellListAck);
	DECODE_WORD(type);
	DECODE_WORD(subtype);
	DECODE_DWORD(total);
	DECODE_DWORD(start);
	DECODE_DWORD(count);
	for (uint16_t i = 0; i < pstOut->count; ++i)
	{
		if (-1 == DeCodeDELEGATE_SELL_ITEM(&pstOut->items[i], poNetData))return -1;
	}
	DECODE_DWORD(sessid);
	END_DECODE();
}

static int EncodeDelegateBuyListAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_DelegateBuyListAck);
	ENCODE_WORD(type);
	ENCODE_WORD(subtype);
	ENCODE_DWORD(total);
	ENCODE_DWORD(start);
	ENCODE_DWORD(count);
	for (uint16_t i = 0; i < pstIn->count; ++i)
	{
		if (-1 == EnCodeDELEGATE_BUY_ITEM2(&pstIn->items[i], poNetData))return -1;
	}
	ENCODE_DWORD(sessid);
	END_ENCODE();
}

static int DecodeDelegateBuyListAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_DelegateBuyListAck);
	DECODE_WORD(type);
	DECODE_WORD(subtype);
	DECODE_DWORD(total);
	DECODE_DWORD(start);
	DECODE_DWORD(count);
	for (uint16_t i = 0; i < pstOut->count; ++i)
	{
		if (-1 == DeCodeDELEGATE_BUY_ITEM2(&pstOut->items[i], poNetData))return -1;
	}
	DECODE_DWORD(sessid);
	END_DECODE();
}

static int EncodeGetMailAttachmentReq(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_GetMailAttachmentReq);
	ENCODE_QWORD(role_guid);
	ENCODE_QWORD(mail_guid);
	ENCODE_QWORD(item_guid);
	ENCODE_BYTE(index);
	END_ENCODE();
}

static int DecodeGetMailAttachmentReq(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_GetMailAttachmentReq);
	DECODE_QWORD(role_guid);
	DECODE_QWORD(mail_guid);
	DECODE_QWORD(item_guid);
	DECODE_BYTE(index);
	END_DECODE();
}

static int EncodeRecordsMineAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_RecordsMineAck);
	ENCODE_QWORD(role_id);
	ENCODE_WORD(type);
	ENCODE_DWORD(count);
	for (uint16_t i = 0; i < pstIn->count; ++i)
	{
		if (EnCodeLOGTRADE_DATA(&pstIn->trade_record[i].logTradeData, poNetData) == -1)
			return -1;
		if (EnCodeITEM_INFO(&pstIn->trade_record[i].item, poNetData) == -1)
			return -1;
	}
	ENCODE_BYTE(last_pack);
	ENCODE_DWORD(sessid);
	END_ENCODE();
}

static int DecodeRecordsMineAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_RecordsMineAck);
	DECODE_QWORD(role_id);
	DECODE_WORD(type);
	DECODE_DWORD(count);
	for (uint16_t i = 0; i < pstOut->count; ++i)
	{
		if (DeCodeLOGTRADE_DATA(&pstOut->trade_record[i].logTradeData, poNetData) == -1)
			return -1;
		if (DeCodeITEM_INFO(&pstOut->trade_record[i].item, poNetData) == -1)
			return -1;
	}
	DECODE_BYTE(last_pack);
	DECODE_DWORD(sessid);
	END_DECODE();
}

static int EncodeDelegateMineAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_DelegateMineAck);
	ENCODE_QWORD(role_id);
	ENCODE_DWORD(count_buy);
	ENCODE_DWORD(count_sell);
	for (uint16_t i = 0; i < pstIn->count_buy; ++i)
	{
		if (-1 == EnCodeDELEGATE_BUY_ITEM2(&pstIn->buy_items[i], poNetData))return -1;
	}
	for (uint16_t i = 0; i < pstIn->count_sell; ++i)
	{
		if (-1 == EnCodeDELEGATE_SELL_ITEM(&pstIn->sell_items[i], poNetData))return -1;
	}
	ENCODE_BYTE(last_pack);
	ENCODE_DWORD(sessid);
	END_ENCODE();
}

static int DecodeDelegateMineAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_DelegateMineAck);
	DECODE_QWORD(role_id);
	DECODE_DWORD(count_buy);
	DECODE_DWORD(count_sell);
	for (uint16_t i = 0; i < pstOut->count_buy; ++i)
	{
		if (-1 == DeCodeDELEGATE_BUY_ITEM2(&pstOut->buy_items[i], poNetData))return -1;
	}
	for (uint16_t i = 0; i < pstOut->count_sell; ++i)
	{
		if (-1 == DeCodeDELEGATE_SELL_ITEM(&pstOut->sell_items[i], poNetData))return -1;
	}
	DECODE_BYTE(last_pack);
	DECODE_DWORD(sessid);
	END_DECODE();
}

static int EnCodeMailDelReq(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_DeleteMailReq);
	ENCODE_QWORD(id);
	ENCODE_QWORD(playerguid);
	ENCODE_DWORD(sessid);
	END_ENCODE();
}

static int DeCodeMailDelReq(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_DeleteMailReq);
	DECODE_QWORD(id);
	DECODE_QWORD(playerguid);
	DECODE_DWORD(sessid);
	END_DECODE();
}

static int EnCodeMailAttachmentGetAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_MailAttachmentGetAck);
	ENCODE_QWORD(mail_id);
	ENCODE_BYTE(index);
	ENCODE_DWORD(errcode);
	ENCODE_DWORD(sessid);
	END_ENCODE();
}

static int DeCodeMailAttachmentGetAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_MailAttachmentGetAck);
	DECODE_QWORD(mail_id);
	DECODE_BYTE(index);
	DECODE_DWORD(errcode);
	DECODE_DWORD(sessid);
	END_DECODE();
}

static int EnCodeMailOpenAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_OpenMailAck);
	ENCODE_QWORD(mail_id);
	if (-1 == EnCodeMAIL_BODY_INFO2(&pstIn->mail, poNetData))return -1;
	ENCODE_DWORD(sessid);
	END_ENCODE();
}

static int DeCodeMailOpenAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_OpenMailAck);
	DECODE_QWORD(mail_id);
	if (-1 == DeCodeMAIL_BODY_INFO2(&pstOut->mail, poNetData))return -1;
	DECODE_DWORD(sessid);
	END_DECODE();
}

static int EnCodeDeleteMailAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_DeleteMailAck);
	ENCODE_QWORD(mail_id);
	ENCODE_DWORD(errcode);
	ENCODE_DWORD(sessid);
	END_ENCODE();
}

static int DeCodeDeleteMailAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_DeleteMailAck);
	DECODE_QWORD(mail_id);
	DECODE_DWORD(errcode);
	DECODE_DWORD(sessid);
	END_DECODE();
}

static int EnCodeGetMailListAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_GetMailListAck);
	ENCODE_INT(num);
	ENCODE_WORD(cur_page);
	ENCODE_WORD(page_num);
	for (uint16_t i = 0; i < pstIn->num; ++i){
		if (-1 == EnCodeMAIL_HEADER_INFO(&pstIn->mails[i], poNetData))return -1;
	}
	ENCODE_DWORD(sessid);
	END_ENCODE();
}

static int DeCodeGetMailListAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_GetMailListAck);
	DECODE_INT(num);
	DECODE_WORD(cur_page);
	DECODE_WORD(page_num);
	for (uint16_t i = 0; i < pstOut->num; ++i){
		if (-1 == DeCodeMAIL_HEADER_INFO(&pstOut->mails[i], poNetData))return -1;
	}
	DECODE_DWORD(sessid);
	END_DECODE();
}

static int EnCodeSyncMailInfoStatus(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_SyncMailInfoStatus);
	ENCODE_QWORD(playerguid);
	ENCODE_WORD(num);
	for (uint16_t i = 0; i < pstIn->num; ++i) {
		if (-1 == EnCodeMail_INFO_STATUS(&pstIn->info_status[i], poNetData))return -1;
	}
	END_ENCODE();
}

static int DeCodeSyncMailInfoStatus(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_SyncMailInfoStatus);
	DECODE_QWORD(playerguid);
	DECODE_WORD(num);
	for (uint16_t i = 0; i < pstOut->num; ++i) {
		if (-1 == DeCodeMail_INFO_STATUS(&pstOut->info_status[i], poNetData))return -1;
	}
	END_DECODE();
}

static int EnCodeNewMailNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_NewMailNtf);
	ENCODE_DWORD(sessid);
	END_ENCODE();
}

static int DeCodeNewMailNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_NewMailNtf);
	DECODE_DWORD(sessid);
	END_DECODE();
}
static int EnCodeAddSysNewMail(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_AddSysNewMail);
	ENCODE_STRING(rolename);
	ENCODE_DWORD(num);
	for (int i = 0; i < pstIn->num; ++i) {
		ENCODE_QWORD(guid[i]);
	}
	if (-1 == EnCodeMAIL_INFO(&pstIn->infos, poNetData))return -1;
	ENCODE_WORD(addType);
	END_ENCODE();
}

static int DeCodeAddSysNewMail(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_AddSysNewMail);
	DECODE_STRING(rolename);
	DECODE_DWORD(num);
	for (int i = 0; i < pstOut->num; ++i) {
		DECODE_QWORD(guid[i]);
	}
	if (-1 == DeCodeMAIL_INFO(&pstOut->infos, poNetData))return -1;
	DECODE_WORD(addType);
	END_DECODE();
}

static int EnCodeDgnBindInfoSet(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_DgnBindInfo);
	ENCODE_WORD(packIdx);
	ENCODE_WORD(num);
	ENCODE_QWORD(roleId);
	ENCODE_QWORD(userid);

	for (uint16_t i = 0; i < pstIn->num; ++i)
	{
		if (-1 == poNetData->AddQword(pstIn->info[i].roleId))
			return -1;

		if (-1 == poNetData->AddString(pstIn->info[i].dgnKeyName))
			return -1;

		if (-1 == poNetData->AddQword(pstIn->info[i].dgnId))
			return -1;

		if (-1 == poNetData->AddWord(pstIn->info[i].optType))
			return -1;
	}

	END_ENCODE();
}

static int DeCodeDgnBindInfoSet(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_DgnBindInfo);
	DECODE_WORD(packIdx);
	DECODE_WORD(num);
	DECODE_QWORD(roleId);
	DECODE_QWORD(userid);

	for (uint16_t i = 0; i < pstOut->num; ++i)
	{
		if (-1 == poNetData->DelQword(pstOut->info[i].roleId))
			return -1;

		if (-1 == poNetData->DelString(pstOut->info[i].dgnKeyName, sizeof(pstOut->info[i].dgnKeyName)))
			return -1;

		if (-1 == poNetData->DelQword(pstOut->info[i].dgnId))
			return -1;

		if (-1 == poNetData->DelWord(pstOut->info[i].optType))
			return -1;
	}
	END_DECODE();
}

static int EnCodeQuickBarSet(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_QuickBarSet);
    ENCODE_WORD(num);
    ENCODE_QWORD(role_id);
    ENCODE_QWORD(userid);

    for (uint16_t i = 0; i < pstIn->num; ++i)
        if (EnCodeQUICK_BAR_INFO(pstIn->info + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DeCodeQuickBarSet(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_QuickBarSet);
    DECODE_WORD(num);
    DECODE_QWORD(role_id);
    DECODE_QWORD(userid);

    for (uint16_t i = 0; i < pstOut->num; ++i)
        if (DeCodeQUICK_BAR_INFO(pstOut->info + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EnCodeQuickBarSetNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_QuickBarSetNtf);
    ENCODE_WORD(num);
    ENCODE_DWORD(sessid);

    for (uint16_t i = 0; i < pstIn->num; ++i)
        if (EnCodeQUICK_BAR_INFO(pstIn->info + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DeCodeQuickBarSetNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_QuickBarSetNtf);
    DECODE_WORD(num);
    DECODE_DWORD(sessid);

    for (uint16_t i = 0; i < pstOut->num; ++i)
        if (DeCodeQUICK_BAR_INFO(pstOut->info + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EnCodeGlobalNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_GlobalNtf);
	ENCODE_DWORD(sessid);
	ENCODE_WORD(int_count);
	for (int i = 0; i < pstIn->int_count; ++i)
	{
		ENCODE_STRING(int_data[i].name);
		ENCODE_BYTE(int_data[i].type);
		ENCODE_QWORD(int_data[i].value);
	}
	ENCODE_WORD(str_count);
	for (int i = 0; i < pstIn->str_count; ++i)
	{
		ENCODE_STRING(str_data[i].name);
		ENCODE_STRING(str_data[i].value);
	}
	END_ENCODE();
}

static int DeCodeGlobalNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_GlobalNtf);
	DECODE_DWORD(sessid);
	DECODE_WORD(int_count);
	for (int i = 0; i < pstOut->int_count; ++i)
	{
		DECODE_STRING(int_data[i].name);
		DECODE_BYTE(int_data[i].type);
		DECODE_QWORD(int_data[i].value);
	}
	DECODE_WORD(str_count);
	for (int i = 0; i < pstOut->str_count; ++i)
	{
		DECODE_STRING(str_data[i].name);
		DECODE_STRING(str_data[i].value);
	}
	END_DECODE();
}

static  int EncodeClearRoleInfoNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_UpdateRoleInfoNtf);
	ENCODE_QWORD(role_id);
	ENCODE_DWORD(token);
	END_ENCODE();
}

static  int DecodeClearRoleInfoNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_UpdateRoleInfoNtf);
	DECODE_QWORD(role_id);
	DECODE_DWORD(token);
	END_DECODE();
}

static  int EncodeDeleteRoleInfoNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_DeleteRoleInfoNtf);
	ENCODE_QWORD(role_id);
	ENCODE_DWORD(token);
	ENCODE_STRING(base_info);
	END_ENCODE();
}

static  int DecodeDeleteRoleInfoNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_DeleteRoleInfoNtf);
	DECODE_QWORD(role_id);
	DECODE_DWORD(token);
	DECODE_STRING(base_info);
	END_DECODE();
}

static  int EncodeUpdateRoleInfoNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_UpdateRoleInfoNtf);
	ENCODE_QWORD(role_id);
	ENCODE_DWORD(token);
	ENCODE_STRING(base_info);
	END_ENCODE();
}

static  int DecodeUpdateRoleInfoNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_UpdateRoleInfoNtf);
	DECODE_QWORD(role_id);
	DECODE_DWORD(token);
	DECODE_STRING(base_info);
	END_DECODE();
}

static  int EncodeInsertRoleInfoNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_InsertRoleInfoNtf);
	ENCODE_QWORD(role_id);
	ENCODE_DWORD(token);
	ENCODE_STRING(base_info);
	END_ENCODE();
}

static  int DecodeInsertRoleInfoNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_InsertRoleInfoNtf);
	DECODE_QWORD(role_id);
	DECODE_DWORD(token);
	DECODE_STRING(base_info);
	END_DECODE();
}

static int EncodeGetRoleInfoReq(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_GetRoleInfoReq);
	ENCODE_QWORD(role_id);
	ENCODE_DWORD(token);
	END_ENCODE();
}

static int DecodeGetRoleInfoReq(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_GetRoleInfoReq);
	DECODE_QWORD(role_id);
	DECODE_DWORD(token);
	END_DECODE();
}

static int EncodeGetRoleInfoAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_GetRoleInfoAck);
	ENCODE_QWORD(role_id);
	ENCODE_DWORD(token);
	ENCODE_STRING(base_info);
	END_ENCODE();
}

static int DecodeGetRoleInfoAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_GetRoleInfoAck);
	DECODE_QWORD(role_id);
	DECODE_DWORD(token);
	DECODE_STRING(base_info);
	END_DECODE();
}

static int EncodeSendDelItemNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SendDelItemNtf);
    ENCODE_QWORD(user_guid);
    ENCODE_QWORD(role_guid);
    ENCODE_QWORD(item_guid);
	ENCODE_BYTE(tradeDel);
    END_ENCODE();
}

static int DecodeSendDelItemNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SendDelItemNtf);
    DECODE_QWORD(user_guid);
    DECODE_QWORD(role_guid);
    DECODE_QWORD(item_guid);
	DECODE_BYTE(tradeDel);
    END_DECODE();
}

static int EncodeSendSyncItemNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_SendSyncItemNtf);
	ENCODE_QWORD(role_guid);
	ENCODE_DWORD(token);
	ENCODE_QWORD(Guid);
	ENCODE_STRING(Name);
	ENCODE_WORD(Tempid);
	ENCODE_QWORD(Roleid);
	ENCODE_WORD(Site);
	ENCODE_WORD(Amount);
	ENCODE_INT(Durability);
	ENCODE_INT(Max_durability);
	ENCODE_WORD(Use_count);
	ENCODE_BYTE(IsBind);
	ENCODE_DWORD(Life);
	if (-1 == EnCodeITEM_CFG_VAR(&pstIn->ItemCfgVar, poNetData))return -1;
	END_ENCODE();
}
static int DecodeSendSyncItemNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_SendSyncItemNtf);
	DECODE_QWORD(role_guid);
	DECODE_DWORD(token);
	DECODE_QWORD(Guid);
	DECODE_STRING(Name);
	DECODE_WORD(Tempid);
	DECODE_QWORD(Roleid);
	DECODE_WORD(Site);
	DECODE_WORD(Amount);
	DECODE_INT(Durability);
	DECODE_INT(Max_durability);
	DECODE_WORD(Use_count);
	DECODE_BYTE(IsBind);
	DECODE_DWORD(Life);
	if (-1 == DeCodeITEM_CFG_VAR(&pstOut->ItemCfgVar, poNetData))return -1;
	END_DECODE();
}

static int EncodeItemAttrNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_ItemAttrNtf);
	ENCODE_QWORD(item_guid);
	ENCODE_DWORD(attr_name);
	ENCODE_INT(attr_value);
	ENCODE_DWORD(sessid);
	END_ENCODE();
}
static int DecodeItemAttrNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_ItemAttrNtf);
	DECODE_QWORD(item_guid);
	DECODE_DWORD(attr_name);
	DECODE_INT(attr_value);
	DECODE_DWORD(sessid);
	END_DECODE();
}

static int EncodeItemPickUp(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_ItemPickUp);
	END_ENCODE();
}
static int DecodeItemPickUp(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_ItemPickUp);
	END_DECODE();
}

static int EncodeItemAppearNtf4(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_ItemAppearNtf4);
	ENCODE_QWORD(item_guid);
	ENCODE_WORD(template_id);
	ENCODE_INT(dst_x);
	ENCODE_INT(dst_y);
	ENCODE_WORD(skill_id);
	ENCODE_STRING(item_name);
	ENCODE_SHORT(seed);
	ENCODE_BYTE(is_drop);
    ENCODE_QWORD(owner_guid);
    ENCODE_QWORD(team_guid);
	ENCODE_DWORD(clsessid);
	END_ENCODE();
}
static int DecodeItemAppearNtf4(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_ItemAppearNtf4);
	DECODE_QWORD(item_guid);
	DECODE_WORD(template_id);
	DECODE_INT(dst_x);
	DECODE_INT(dst_y);
	DECODE_WORD(skill_id);
	DECODE_STRING(item_name);
	DECODE_SHORT(seed);
	DECODE_BYTE(is_drop);
    DECODE_QWORD(owner_guid);
    DECODE_QWORD(team_guid);
    DECODE_DWORD(clsessid);
	END_DECODE();
}
static int EncodeItemDestroyAck(void* pHost, CNetData* poNetData)
{

	BEGIN_ENCODE_EX(ProtoMS_ItemDestroyAck);
	ENCODE_QWORD(item_guid);
	ENCODE_DWORD(sessid);
	END_ENCODE();

}
static int DecodeItemDestroyAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_ItemDestroyAck);
	DECODE_QWORD(item_guid);
	DECODE_DWORD(sessid);
	END_DECODE();
}

static int EncodeItemUpdateNtf(void* pHost, CNetData* poNetData)
{

	BEGIN_ENCODE_EX(ProtoMS_ItemUpdateNtf);
	if (-1 == EnCodeITEM_INFO(&pstIn->info, poNetData))return -1;
	ENCODE_DWORD(sessid);
	END_ENCODE();

}
static int DecodeItemUpdateNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_ItemUpdateNtf);
	if (-1 == DeCodeITEM_INFO(&pstOut->info, poNetData))return -1;
	DECODE_DWORD(sessid);
	END_DECODE();
}

static int EnCodeRoleAttrExtNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_RoleAttrExtNtf);
    ENCODE_QWORD(player_guid);
    ENCODE_WORD(num);
    ENCODE_BLOB(attr_name, pstIn->num * sizeof(uint16_t));
    ENCODE_BLOB(attr_value, pstIn->num * sizeof(int64_t));
    ENCODE_DWORD(sessid);
    END_ENCODE();
}

static int DeCodeRoleAttrExtNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_RoleAttrExtNtf);
    DECODE_QWORD(player_guid);
    DECODE_WORD(num);
    DECODE_BLOB(attr_name, pstOut->num * sizeof(uint16_t));
    DECODE_BLOB(attr_value, pstOut->num * sizeof(int64_t));
    DECODE_DWORD(sessid);
    END_DECODE();
}

static int EnCodeRoleDynAttrsNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_RoleDynAttrsNtf);
	ENCODE_QWORD(role_guid);
	if (EnCodeCUSTOM_INFO(&pstIn->custom, poNetData) == -1)
		return -1;
	ENCODE_DWORD(sessid);
	END_ENCODE();
}

static int DeCodeRoleDynAttrsNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_RoleDynAttrsNtf);
	DECODE_QWORD(role_guid);
	if (-1 == DeCodeCUSTOM_INFO(&pstOut->custom, poNetData))
		return -1;
	DECODE_DWORD(sessid);
	END_DECODE();
}

static int EnCodeRoleInfoChangeNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_RoleInfoChangeNtf);
	ENCODE_QWORD(role_guid);
	ENCODE_WORD(num);
	if (EnCodeCUSTOM_INFO(&pstIn->custom, poNetData) == -1)
		return -1;
	ENCODE_DWORD(sessid);
	END_ENCODE();
}

static int DeCodeRoleInfoChangeNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_RoleInfoChangeNtf);
	DECODE_QWORD(role_guid);
	DECODE_WORD(num);
	if (-1 == DeCodeCUSTOM_INFO(&pstOut->custom, poNetData))
		return -1;
	DECODE_DWORD(sessid);
	END_DECODE();
}

static int EnCodeRoleCustVarNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_RoleCustVarNtf);
	ENCODE_QWORD(role_guid);
	if(EnCodeCUSTOM_INFO(&pstIn->custom, poNetData) == -1)
		return -1;
	ENCODE_DWORD(sessid);
	ENCODE_BYTE(type);
	END_ENCODE();
}

static int DeCodeRoleCustVarNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_RoleCustVarNtf);
	DECODE_QWORD(role_guid);
	if (-1 == DeCodeCUSTOM_INFO(&pstOut->custom, poNetData))
		return -1;
	DECODE_DWORD(sessid);
	DECODE_BYTE(type);
	END_DECODE();
}

static int EnCodeRoleAttrNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_RoleAttrNtf);
    ENCODE_QWORD(role_guid);
    ENCODE_WORD(attr_num);
    ENCODE_BLOB(attr_name, pstIn->attr_num * sizeof(uint16_t));
    ENCODE_BLOB(attr_value, pstIn->attr_num * sizeof(int));
    ENCODE_WORD(clsessnum);
    ENCODE_BLOB(clsessids, pstIn->clsessnum * sizeof(uint32_t));
    END_ENCODE();
}

static int DeCodeRoleAttrNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_RoleAttrNtf);
    DECODE_QWORD(role_guid);
    DECODE_WORD(attr_num);
    DECODE_BLOB(attr_name, pstOut->attr_num * sizeof(uint16_t));
    DECODE_BLOB(attr_value, pstOut->attr_num * sizeof(int));
    DECODE_WORD(clsessnum);
    DECODE_BLOB(clsessids, pstOut->clsessnum * sizeof(uint32_t));
    END_DECODE();
}

static int EncodeItemAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_ItemAddAck);
	ENCODE_CHAR(isPackItem);
	if (-1 == EnCodeITEM_INFO(&pstIn->info, poNetData))return -1;
	ENCODE_DWORD(sessid);
	ENCODE_DWORD(nGS2CSSessionID);
	END_ENCODE();
}

static int DecodeItemAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_ItemAddAck);
	DECODE_CHAR(isPackItem);
	if (-1 == DeCodeITEM_INFO(&pstOut->info, poNetData))return -1;
	DECODE_DWORD(sessid);
	DECODE_DWORD(nGS2CSSessionID);
	END_DECODE();
}

static int EncodeObjdisAppearNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_ObjDisappearNtf);
	ENCODE_QWORD(obj_guid);
	ENCODE_DWORD(sessid);
	END_ENCODE();
}

static int DecodeObjdisAppearNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_ObjDisappearNtf);
	DECODE_QWORD(obj_guid);
	DECODE_DWORD(sessid);
	END_DECODE();
}

static int EncodeMonsterAppearNtf6(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_MonsterAppearNtf6);
	ENCODE_QWORD(monster_guid);
	ENCODE_STRING(monster_name);
	ENCODE_WORD(template_id);
	ENCODE_INT(dst_x);
	ENCODE_INT(dst_y);
	ENCODE_BYTE(dir);
	ENCODE_DWORD(cur_hp);
	ENCODE_DWORD(max_hp);
	ENCODE_BYTE(status);
	ENCODE_BYTE(servant_lv);
	ENCODE_WORD(move_speed);
	ENCODE_WORD(buff_num);
	ENCODEBUFF_INFO(buffs, buff_num, 50);
	ENCODE_STRING(master_name);
	ENCODE_BYTE(appear_type);
	ENCODE_SHORT(seed);
	ENCODE_WORD(attack_speed);
	ENCODECUSTOM_INFO(custom);
	ENCODE_DWORD(inner_force);
	ENCODE_DWORD(max_inner_force);
	ENCODE_WORD(reserve_num);
	ENCODE_INTARRAY(reserve_values, pstIn->reserve_num);
	ENCODE_STRING(name_color);
	ENCODE_DWORD(sessid);
	ENCODE_DWORD(nGS2CSSessionID);
	ENCODE_DWORD(modelid);
	END_ENCODE();
}

static int DecodeMonsterAppearNtf6(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_MonsterAppearNtf6);
	DECODE_QWORD(monster_guid);
	DECODE_STRING(monster_name);
	DECODE_WORD(template_id);
	DECODE_INT(dst_x);
	DECODE_INT(dst_y);
	DECODE_BYTE(dir);
	DECODE_DWORD(cur_hp);
	DECODE_DWORD(max_hp);
	DECODE_BYTE(status);
	DECODE_BYTE(servant_lv);
	DECODE_WORD(move_speed);
	DECODE_WORD(buff_num);
	DECODEBUFF_INFO(buffs, buff_num, 50);
	DECODE_STRING(master_name);
	DECODE_BYTE(appear_type);
	DECODE_SHORT(seed);
	DECODE_WORD(attack_speed);
	DECODECUSTOM_INFO(custom);
	DECODE_DWORD(inner_force);
	DECODE_DWORD(max_inner_force);
	DECODE_WORD(reserve_num);
	DECODE_INTARRAY(reserve_values, pstOut->reserve_num);
	DECODE_STRING(name_color);
	DECODE_DWORD(sessid);
	DECODE_DWORD(nGS2CSSessionID);
	DECODE_DWORD(modelid);
	END_DECODE();
}

static int EncodeHeartBeatReq(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_HeartBeatReq);
	END_ENCODE();
}

static int DecodeHeartBeatReq(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_HeartBeatReq);
	END_DECODE();
}

static int EncodeHeartBeatAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_HeartBeatAck);
	END_ENCODE();
}

static int DecodeHeartBeatAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_HeartBeatAck);
	END_DECODE();
}

static int EnCodeUploadConfigReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_UploadConfigReq);
    ENCODE_DWORD(ip);
    ENCODE_DWORD(port);
    END_ENCODE();
}

static int DeCodeUploadConfigReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_UploadConfigReq);
    DECODE_DWORD(ip);
    DECODE_DWORD(port);
    END_DECODE();
}

static int EnCodeConfigReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_ConfigReq);
    END_ENCODE();
}

static int DeCodeConfigReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_ConfigReq);
    END_DECODE();
}

static int EnCodeConfigAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_ConfigAck);
    ENCODE_DWORD(dbServIp);
    ENCODE_DWORD(dbServPort);
    ENCODE_DWORD(centerServIp);
    ENCODE_DWORD(centerServPort);
    ENCODE_DWORD(logServIp);
    ENCODE_DWORD(logServPort);
    END_ENCODE();
}

static int DeCodeConfigAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_ConfigAck);
    DECODE_DWORD(dbServIp);
    DECODE_DWORD(dbServPort);
    DECODE_DWORD(centerServIp);
    DECODE_DWORD(centerServPort);
    DECODE_DWORD(logServIp);
    DECODE_DWORD(logServPort);
    END_DECODE();
}

static int EncodePlayerAppearNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_PlayerAppearNtf);
    ENCODE_QWORD(player_guid);
    ENCODE_STRING(name);
    ENCODE_BYTE(gender);
    ENCODE_BYTE(job);
    ENCODE_BYTE(status);
    ENCODE_WORD(head);
    ENCODE_DWORD(level);
    ENCODE_WORD(dst_x);
    ENCODE_WORD(dst_y);
    ENCODE_BYTE(dir);
    ENCODE_WORD(hair);
    ENCODE_WORD(hair_color);
    ENCODE_WORD(body);
    ENCODE_WORD(weapon);
    ENCODE_WORD(wings);
    ENCODE_WORD(mount);
    ENCODE_WORD(weapon_effect);
    ENCODE_WORD(body_effect);
    ENCODE_WORD(mount_effect);
    ENCODE_DWORD(hp);
    ENCODE_DWORD(max_hp);
    ENCODE_DWORD(mp);
    ENCODE_DWORD(max_mp);
    ENCODE_INT(pk);
    ENCODE_WORD(move_speed);
    ENCODE_WORD(attack_speed);
	ENCODE_WORD(casting_speed);
	ENCODE_WORD(show_fashion);
	ENCODE_DWORD(model_id);
    ENCODE_WORD(title);
    ENCODE_BYTE(has_team);
    ENCODE_BYTE(stall);
    ENCODE_STRING(stall_name);
    ENCODE_WORD(buff_num);

    for (uint16_t i = 0; i < pstIn->buff_num; ++i)
        if (EnCodeBUFF_INFO(pstIn->buffs + i, poNetData) == -1)
            return -1;

    ENCODE_STRING(family_name);
    ENCODE_STRING(castle_name);
    ENCODE_STRING(family_title);
    ENCODE_STRING(alias);

    if (EnCodeCUSTOM_INFO(&pstIn->custom, poNetData) == -1)
        return -1;

    ENCODE_BYTE(appear_type);
    ENCODE_WORD(amulet);
    ENCODE_WORD(equip_num);

    for (uint16_t i = 0; i < pstIn->equip_num; ++i)
        if (EnCodeEQUIP_INFO(pstIn->equips + i, poNetData) == -1)
            return -1;

    ENCODE_DWORD(inner_force);
    ENCODE_DWORD(max_inner_force);
    ENCODE_WORD(reserve_num);

    for (uint16_t i = 0; i < pstIn->reserve_num; ++i)
        ENCODE_DWORD(reserve_values[i]);

    ENCODE_QWORD(master_guid);
	ENCODE_WORD(title_num);
	for (int i = 0; i < pstIn->title_num; ++i) {
		ENCODE_DWORD(title_id[i]);
	}
    ENCODE_DWORD(sessid);
    END_ENCODE();
}

static int DecodePlayerAppearNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_PlayerAppearNtf);
    DECODE_QWORD(player_guid);
    DECODE_STRING(name);
    DECODE_BYTE(gender);
    DECODE_BYTE(job);
    DECODE_BYTE(status);
    DECODE_WORD(head);
    DECODE_DWORD(level);
    DECODE_WORD(dst_x);
    DECODE_WORD(dst_y);
    DECODE_BYTE(dir);
    DECODE_WORD(hair);
    DECODE_WORD(hair_color);
    DECODE_WORD(body);
    DECODE_WORD(weapon);
    DECODE_WORD(wings);
    DECODE_WORD(mount);
    DECODE_WORD(weapon_effect);
    DECODE_WORD(body_effect);
    DECODE_WORD(mount_effect);
    DECODE_DWORD(hp);
    DECODE_DWORD(max_hp);
    DECODE_DWORD(mp);
    DECODE_DWORD(max_mp);
    DECODE_INT(pk);
    DECODE_WORD(move_speed);
    DECODE_WORD(attack_speed);
	DECODE_WORD(casting_speed);
	DECODE_WORD(show_fashion);
	DECODE_DWORD(model_id);
    DECODE_WORD(title);
    DECODE_BYTE(has_team);
    DECODE_BYTE(stall);
    DECODE_STRING(stall_name);
    DECODE_WORD(buff_num);

    for (uint16_t i = 0; i < pstOut->buff_num; ++i)
        if (DeCodeBUFF_INFO(pstOut->buffs + i, poNetData) == -1)
            return -1;

    DECODE_STRING(family_name);
    DECODE_STRING(castle_name);
    DECODE_STRING(family_title);
    DECODE_STRING(alias);

    if (DeCodeCUSTOM_INFO(&pstOut->custom, poNetData) == -1)
        return -1;

    DECODE_BYTE(appear_type);
    DECODE_WORD(amulet);
    DECODE_WORD(equip_num);

    for (uint16_t i = 0; i < pstOut->equip_num; ++i)
        if (DeCodeEQUIP_INFO(pstOut->equips + i, poNetData) == -1)
            return -1;

    DECODE_DWORD(inner_force);
    DECODE_DWORD(max_inner_force);
    DECODE_WORD(reserve_num);

    for (uint16_t i = 0; i < pstOut->reserve_num; ++i)
        DECODE_DWORD(reserve_values[i]);

    DECODE_QWORD(master_guid);
	DECODE_WORD(title_num);
	for (int i = 0; i < pstOut->title_num; ++i) {
		DECODE_DWORD(title_id[i]);
	}
    DECODE_DWORD(sessid);
    END_DECODE();
}

static int EnCodeNpcTalkReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_NpcTalkReq);
    END_ENCODE();
}

static int DeCodeNpcTalkReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_NpcTalkReq);
    END_DECODE();
}

static int EnCodeNpcTalkAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_NpcTalkAck);
    ENCODE_STRING(content);
    END_ENCODE();
}

static int DeCodeNpcTalkAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_NpcTalkAck);
    DECODE_STRING(content);
    END_DECODE();
}

static int EncodeEnterMSAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_EnterMSAck);
	ENCODE_DWORD(nClientSessionID);
	ENCODE_DWORD(nCS2GSSessionID);
	ENCODE_BYTE(entertype);
	ENCODE_QWORD(playerid);
	ENCODE_QWORD(roleguid);
	ENCODE_DWORD(gsobjid);
	ENCODE_INT(errcode);
	ENCODE_STRING(errmsg);
	if (-1 == EnCodeROLE_BRIEF_INFO(&pstIn->roleBriefInfo, poNetData))
		return -1;
	END_ENCODE();
}

static int DecodeEnterMSAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_EnterMSAck);
	DECODE_DWORD(nClientSessionID);
	DECODE_DWORD(nCS2GSSessionID);
	DECODE_BYTE(entertype);
	DECODE_QWORD(playerid);
	DECODE_QWORD(roleguid);
	DECODE_DWORD(gsobjid);
	DECODE_INT(errcode);
	DECODE_STRING(errmsg);
	if (-1 == DeCodeROLE_BRIEF_INFO(&pstOut->roleBriefInfo, poNetData))
		return -1;
	END_DECODE();
}

int EncodeEnterMSNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_EnterMSNtf);
	ENCODE_DWORD(nClientSessionID);
	ENCODE_DWORD(nCS2GSSessionID);
	ENCODE_QWORD(mapcode);
	ENCODE_STRING(logic);
	ENCODE_WORD(view_x);
	ENCODE_WORD(view_y);
	ENCODE_WORD(width);
	ENCODE_WORD(height);
	ENCODE_DWORD(token);
	END_ENCODE();
}

int DecodeEnterMSNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_EnterMSNtf);
	DECODE_DWORD(nClientSessionID);
	DECODE_DWORD(nCS2GSSessionID);
	DECODE_QWORD(mapcode);
	DECODE_STRING(logic);
	DECODE_WORD(view_x);
	DECODE_WORD(view_y);
	DECODE_WORD(width);
	DECODE_WORD(height);
	DECODE_DWORD(token);
	END_DECODE();
}

int EnCodeAttrShowNTF2EX2(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_AttrShowNtfEx2);
	ENCODE_QWORD(actor);
	ENCODE_WORD(skill_id);
	ENCODE_QWORD(target);
	ENCODE_BYTE(type);
	ENCODE_INT(actor_hp_ref);
	ENCODE_INT(target_hp_ref);
	ENCODE_INT(target_hp);
	ENCODE_INT(target_mp);
	ENCODE_INT(actor_mp_ref);
	ENCODE_INT(target_mp_ref);
	ENCODE_BYTE(reserve_size);
	ENCODE_BLOB(reserve, pstIn->reserve_size * sizeof(uint32_t));
    ENCODE_WORD(clsessnum);
    ENCODE_BLOB(clsessids, pstIn->clsessnum * sizeof(uint32_t));
    END_ENCODE();
}

int DeCodeAttrShowNTF2EX2(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_AttrShowNtfEx2);
	DECODE_QWORD(actor);
	DECODE_WORD(skill_id);
	DECODE_QWORD(target);
	DECODE_BYTE(type);
	DECODE_INT(actor_hp_ref);
	DECODE_INT(target_hp_ref);
	DECODE_INT(target_hp);
	DECODE_INT(target_mp);
	DECODE_INT(actor_mp_ref);
	DECODE_INT(target_mp_ref);
	DECODE_BYTE(reserve_size);
	DECODE_BLOB(reserve, pstOut->reserve_size * sizeof(uint32_t));
    DECODE_WORD(clsessnum);
    DECODE_BLOB(clsessids, pstOut->clsessnum * sizeof(uint32_t));
    END_DECODE();
}


static int EncodeMoveNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_MoveNtf);
	ENCODE_QWORD(guid);
	ENCODE_BYTE(type);
	ENCODE_WORD(dst_x);
	ENCODE_WORD(dst_y);
	ENCODE_DWORD(sessionid);
	END_ENCODE();
}

static int DecodeMoveNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_MoveNtf);
	DECODE_QWORD(guid);
	DECODE_BYTE(type);
	DECODE_WORD(dst_x);
	DECODE_WORD(dst_y);
	DECODE_DWORD(sessionid);
	END_DECODE();
}

static int EncodeMoveNtfEx(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_MoveNtfEx);
    ENCODE_QWORD(guid);
    ENCODE_BYTE(type);
    ENCODE_WORD(dst_x);
    ENCODE_WORD(dst_y);
    ENCODE_WORD(clsessnum);
    ENCODE_INTARRAY(clsessids, pstIn->clsessnum);
    END_ENCODE();
}

static int DecodeMoveNtfEx(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_MoveNtfEx);
    DECODE_QWORD(guid);
    DECODE_BYTE(type);
    DECODE_WORD(dst_x);
    DECODE_WORD(dst_y);
    DECODE_WORD(clsessnum);
    DECODE_INTARRAY(clsessids, pstOut->clsessnum);
    END_DECODE();
}

static int EncodeTurnNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_TurnNtf);
    ENCODE_QWORD(guid);
    ENCODE_BYTE(dir);
    ENCODE_WORD(clsessnum);
    ENCODE_INTARRAY(clsessids, pstIn->clsessnum);
    END_ENCODE();
}

static int DecodeTurnNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_TurnNtf);
    DECODE_QWORD(guid);
    DECODE_BYTE(dir);
    DECODE_WORD(clsessnum);
    DECODE_INTARRAY(clsessids, pstOut->clsessnum);
    END_DECODE();
}

static int EncodeSpellNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_SpellNtf);
	ENCODE_QWORD(actor);
	ENCODE_WORD(id);
	ENCODE_WORD(target_x);
	ENCODE_WORD(target_y);
	ENCODE_WORD(num);
    ENCODE_BLOB(targets, pstIn->num * sizeof(uint64_t));
    ENCODE_BYTE(extra);
    ENCODE_WORD(clsessnum);
    ENCODE_BLOB(clsessids, pstIn->clsessnum * sizeof(uint32_t));
	END_ENCODE();
}

static int DecodeSpellNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_SpellNtf);
	DECODE_QWORD(actor);
	DECODE_WORD(id);
	DECODE_WORD(target_x);
	DECODE_WORD(target_y);
	DECODE_WORD(num);
    DECODE_BLOB(targets, pstOut->num * sizeof(uint64_t));
    DECODE_BYTE(extra);
    DECODE_WORD(clsessnum);
    DECODE_BLOB(clsessids, pstOut->clsessnum * sizeof(uint32_t));
	END_DECODE();
}

static int EncodeErrorAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_ErrorAck);
	ENCODE_DWORD(clientSessionID);
	ENCODE_INT(ecode);
	ENCODE_QWORD(guid);
	END_ENCODE();
}

static int DecodeErrorAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_ErrorAck);
	DECODE_DWORD(clientSessionID);
	DECODE_INT(ecode);
	DECODE_QWORD(guid);
	END_DECODE();
}

static int EncodeGMErrorAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_GMErrorAck);
    ENCODE_DWORD(clsessid);
    ENCODE_INT(sn);
    ENCODE_INT(ecode);
    ENCODE_QWORD(guid);
    END_ENCODE();
}

static int DecodeGMErrorAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_GMErrorAck);
    DECODE_DWORD(clsessid);
    DECODE_INT(sn);
    DECODE_INT(ecode);
    DECODE_QWORD(guid);
    END_DECODE();
}

static int EncodeObjDieNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_ObjDieNtf);
	ENCODE_DWORD(clientSessionID);
	ENCODE_QWORD(die_guid);
	ENCODE_QWORD(kill_guid);
	ENCODE_STRING(kill_name);
	END_ENCODE();
}

static int DecodeObjDieNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_ObjDieNtf);
	DECODE_DWORD(clientSessionID);
	DECODE_QWORD(die_guid);
	DECODE_QWORD(kill_guid);
	DECODE_STRING(kill_name);
	END_DECODE();
}

static int EncodeSkillAddAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_SkillAddAck);
	ENCODE_DWORD(nClientSessionID);
    ENCODE_QWORD(role_guid);
	ENCODE_WORD(num);
	for (int i = 0; i < pstIn->num; ++i)
		if (EnCodeSKILL_INFO(pstIn->info + i, poNetData) == -1)
			return -1;
	ENCODE_BYTE(add);
	END_ENCODE();
}

static int DecodeSkillAddAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_SkillAddAck);
	DECODE_DWORD(nClientSessionID);
    DECODE_QWORD(role_guid);
	DECODE_WORD(num);
	for (int i = 0; i < pstOut->num; ++i)
		if (DeCodeSKILL_INFO(pstOut->info + i, poNetData) == -1)
			return -1;
	DECODE_BYTE(add);
	END_DECODE();
}

static int EncodeSkillDeleteAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_DeleteSkillAck);
	ENCODE_DWORD(nClientSessionID);
	ENCODE_WORD(skillid);
	END_ENCODE();
}

static int DecodeSkillDeleteAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_DeleteSkillAck);
	DECODE_DWORD(nClientSessionID);
	DECODE_WORD(skillid);
	END_DECODE();
}

static int EncodeGetSkillAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_GetSkillAck);
	ENCODE_QWORD(playerid);
	ENCODE_QWORD(roleid);
	ENCODE_WORD(skillNum);
    for (int i = 0; i < pstIn->skillNum; ++i)
        if (EnCodeSKILL_INFO(pstIn->skillInfo + i, poNetData) == -1)
            return -1;
	END_ENCODE();
}

static int DecodeGetSkillAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_GetSkillAck);
	DECODE_QWORD(playerid);
	DECODE_QWORD(roleid);
	DECODE_WORD(skillNum);
    for (int i = 0; i < pstOut->skillNum; ++i)
        if (DeCodeSKILL_INFO(pstOut->skillInfo + i, poNetData) == -1)
            return -1;
    END_DECODE();
}

static int EncodeSyncSkillReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SyncSkillReq);
    ENCODE_QWORD(playerid);
    ENCODE_QWORD(roleid);
    ENCODE_WORD(skillNum);
    for (int i = 0; i < pstIn->skillNum; ++i)
        if (EnCodeSKILL_INFO(pstIn->skillInfo + i, poNetData) == -1)
            return -1;
    END_ENCODE();
}

static int DecodeSyncSkillReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SyncSkillReq);
    DECODE_QWORD(playerid);
    DECODE_QWORD(roleid);
    DECODE_WORD(skillNum);
    for (int i = 0; i < pstOut->skillNum; ++i)
        if (DeCodeSKILL_INFO(pstOut->skillInfo + i, poNetData) == -1)
            return -1;
    END_DECODE();
}

static int EncodeGetBuffAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_GetBuffAck);
	ENCODE_QWORD(playerid);
	ENCODE_QWORD(roleid);
	ENCODE_BYTE(beFirstPack);
	ENCODE_WORD(buffNum);

	for (uint16_t i = 0; i < pstIn->buffNum; ++i)
		if (EnCodeBUFF_INFO_DB(pstIn->buffs + i, poNetData) == -1)
			return -1;

	END_ENCODE();
}

static int DecodeGetBuffAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_GetBuffAck);
	DECODE_QWORD(playerid);
	DECODE_QWORD(roleid);
	DECODE_BYTE(beFirstPack);
	DECODE_WORD(buffNum);

	for (uint16_t i = 0; i < pstOut->buffNum; ++i)
		if (DeCodeBUFF_INFO_DB(pstOut->buffs + i, poNetData) == -1)
			return -1;

	END_DECODE();
}

static int EncodeSyncBuffReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SyncBuffReq);
    ENCODE_QWORD(playerid);
    ENCODE_QWORD(roleid);
    ENCODE_BYTE(roleType);
	ENCODE_BYTE(beFirstPack);
    ENCODE_WORD(buffNum);

    for (uint16_t i = 0; i < pstIn->buffNum; ++i)
        if (EnCodeBUFF_INFO_DB(pstIn->buffs + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeSyncBuffReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SyncBuffReq);
    DECODE_QWORD(playerid);
    DECODE_QWORD(roleid);
    DECODE_BYTE(roleType);
	DECODE_BYTE(beFirstPack);
    DECODE_WORD(buffNum);

    for (uint16_t i = 0; i < pstOut->buffNum; ++i)
        if (DeCodeBUFF_INFO_DB(pstOut->buffs + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodeBuffAddAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_BuffAddAck);
	ENCODE_DWORD(nClientSessionID);
	ENCODE_QWORD(role_guid);
	ENCODE_WORD(num);

	for (uint16_t i = 0; i < pstIn->num; ++i)
		if (EnCodeBUFF_INFO(pstIn->info + i, poNetData) == -1)
			return -1;
	ENCODE_WORD(clsessnum);
	ENCODE_BLOB(clsessids, pstIn->clsessnum * sizeof(uint32_t));
	END_ENCODE();
}

static int DecodeBuffAddAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_BuffAddAck);
	DECODE_DWORD(nClientSessionID);
	DECODE_QWORD(role_guid);
	DECODE_WORD(num);

	for (uint16_t i = 0; i < pstOut->num; ++i)
		if (DeCodeBUFF_INFO(pstOut->info + i, poNetData) == -1)
			return -1;
	DECODE_WORD(clsessnum);
	DECODE_BLOB(clsessids, pstOut->clsessnum * sizeof(uint32_t));
	END_DECODE();
}

static int EncodeBuffDestroyAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_BuffDestroyAck);
	ENCODE_DWORD(nClientSessionID);
	ENCODE_QWORD(role_guid);
	ENCODE_WORD(id);
	ENCODE_WORD(clsessnum);
	ENCODE_BLOB(clsessids, pstIn->clsessnum * sizeof(uint32_t));
	END_ENCODE();
}

static int DecodeBuffDestroyAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_BuffDestroyAck);
	DECODE_DWORD(nClientSessionID);
	DECODE_QWORD(role_guid);
	DECODE_WORD(id);
	DECODE_WORD(clsessnum);
	DECODE_BLOB(clsessids, pstOut->clsessnum * sizeof(uint32_t));
	END_DECODE();
}

static int EncodeRunClientScript(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_RunClientScript);
	ENCODE_DWORD(clientSessionID);
	ENCODE_STRING(form_name);
	ENCODE_WORD(size);
	ENCODE_BLOB(form_content, pstIn->size);
	ENCODE_BYTE(comp);
	ENCODE_BYTE(all);
	ENCODE_WORD(clsessnum);
	ENCODE_BLOB(clsessids, pstIn->clsessnum * sizeof(uint32_t));
	END_ENCODE();
}

static int DecodeRunClientScript(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_RunClientScript);
	DECODE_DWORD(clientSessionID);
	DECODE_STRING(form_name);
	DECODE_WORD(size);
	DECODE_BLOB(form_content, pstOut->size);
	DECODE_BYTE(comp);
	DECODE_BYTE(all);
	DECODE_WORD(clsessnum);
	DECODE_BLOB(clsessids, pstOut->clsessnum * sizeof(uint32_t));
	END_DECODE();
}

static int EncodeSysMsgNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SysMsgNtf);
    ENCODE_DWORD(clientSessionID);
    ENCODE_BYTE(msg_type);
    ENCODE_BYTE(scroll_count);
    ENCODE_STRING(msg);
    END_ENCODE();
}

static int DecodeSysMsgNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SysMsgNtf);
    DECODE_DWORD(clientSessionID);
    DECODE_BYTE(msg_type);
    DECODE_BYTE(scroll_count);
    DECODE_STRING(msg);
    END_DECODE();
}

static int EncodeSyncRoleInfoReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SyncRoleInfoReq);
    ENCODE_QWORD(userid);
    ENCODE_QWORD(roleid);
    if (EnCodeROLE_BRIEF_INFO(&pstIn->roleBriefInfo, poNetData) == -1) return -1;
    if (EnCodeROLE_EXTRA_INFO(&pstIn->roleExtraInfo, poNetData) == -1) return -1;
	if (EncodeROLE_SETTINGS(&pstIn->roleSettings, poNetData) == -1) return -1;
    END_ENCODE();
}

static int DecodeSyncRoleInfoReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SyncRoleInfoReq);
    DECODE_QWORD(userid);
    DECODE_QWORD(roleid);
    if (DeCodeROLE_BRIEF_INFO(&pstOut->roleBriefInfo, poNetData) == -1) return -1;
    if (DeCodeROLE_EXTRA_INFO(&pstOut->roleExtraInfo, poNetData) == -1) return -1;
	if (DecodeROLE_SETTINGS(&pstOut->roleSettings, poNetData) == -1) return -1;
    END_DECODE();
}

static int EncodeNpcAppearNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_NpcAppearNtf);
    ENCODE_DWORD(clientSessionID);
    ENCODE_QWORD(npc_guid);
    ENCODE_WORD(template_id);
    ENCODE_WORD(dst_x);
    ENCODE_WORD(dst_y);
    ENCODE_BYTE(dir);
    ENCODE_STRING(name);
	ENCODE_DWORD(modelid);
    END_ENCODE();
}

static int DecodeNpcAppearNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_NpcAppearNtf);
    DECODE_DWORD(clientSessionID);
    DECODE_QWORD(npc_guid);
    DECODE_WORD(template_id);
    DECODE_WORD(dst_x);
    DECODE_WORD(dst_y);
    DECODE_BYTE(dir);
    DECODE_STRING(name);
	DECODE_DWORD(modelid);
    END_DECODE();
}

static int EncodeTradeNpcShopNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_TradeNpcShopNtf);
    ENCODE_DWORD(clientSessionID);
    ENCODE_WORD(shop_id);
    ENCODE_BYTE(item_count);
    for (uint8_t i = 0; i < pstIn->item_count; ++i)
        if (EnCodeSHOP_ITEM_INFO(pstIn->item_list + i, poNetData) == -1)
            return -1;
    END_ENCODE();
}

static int DecodeTradeNpcShopNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_TradeNpcShopNtf);
    DECODE_DWORD(clientSessionID);
    DECODE_WORD(shop_id);
    DECODE_BYTE(item_count);
    for (uint8_t i = 0; i < pstOut->item_count; ++i)
        if (DeCodeSHOP_ITEM_INFO(pstOut->item_list + i, poNetData) == -1)
            return -1;
    END_ENCODE();
}

static int EncodeQuestNpcTalkAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_QuestNpcTalkAck);
    ENCODE_DWORD(clientSessionID);
    ENCODE_WORD(width);
    ENCODE_WORD(height);
    ENCODE_QWORD(npc_guid);
    ENCODE_WORD(talk_len);
    ENCODE_BLOB(talk, pstIn->talk_len);
    ENCODE_WORD(quest_state_num);
    for (uint16_t i = 0; i < pstIn->quest_state_num; ++i)
        if (EnCodeQUEST_STATE_INFO(pstIn->quest_states + i, poNetData) == -1)
            return -1;

    ENCODE_BYTE(comp);
    END_ENCODE();
}

static int DecodeQuestNpcTalkAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_QuestNpcTalkAck);
    DECODE_DWORD(clientSessionID);
    DECODE_WORD(width);
    DECODE_WORD(height);
    DECODE_QWORD(npc_guid);
    DECODE_WORD(talk_len);
    DECODE_BLOB(talk, pstOut->talk_len);

    DECODE_WORD(quest_state_num);
    for (uint16_t i = 0; i < pstOut->quest_state_num; ++i)
        if (DeCodeQUEST_STATE_INFO(pstOut->quest_states + i, poNetData) == -1)
            return -1;

    DECODE_BYTE(comp);
    END_DECODE();
}


static int EncodeQuestTimeoutNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_QuestTimeoutNtf);
    ENCODE_DWORD(client_sessionid);
    ENCODE_WORD(quest_id);
    END_ENCODE();
}

static int DecodeQuestTimeoutNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_QuestTimeoutNtf);
    DECODE_DWORD(client_sessionid);
    DECODE_WORD(quest_id);
    END_DECODE();
}

static int EncodeTeamNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_TeamNtf);
	EnCodeTEAM_INFO(&pstIn->info, poNetData);
	ENCODE_DWORD(session_id);
	ENCODE_DWORD(gatesession_id);
	END_ENCODE();
}

static int DecodeTeamNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_TeamNtf);
	DeCodeTEAM_INFO(&pstOut->info, poNetData);
	DECODE_DWORD(session_id);
	DECODE_DWORD(gatesession_id);
	END_DECODE();
}

static int EncodeMissTeamNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_TeamLeaveNtf);
	ENCODE_QWORD(player_guid);
	ENCODE_BYTE(type);
	ENCODE_DWORD(session_id);
	END_ENCODE();
}

static int DecodeMissTeamNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_TeamLeaveNtf);
	DECODE_QWORD(player_guid);
	DECODE_BYTE(type);
	DECODE_DWORD(session_id);
	END_DECODE();
}

static int EncodeTeamInviteNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_TeamInviteNtf);
	ENCODE_STRING(inviter_name);
	ENCODE_BYTE(exist);
	ENCODE_WORD(num);
	EnCodeTEAM_INFO(&pstIn->info[0], poNetData);
	ENCODE_DWORD(session_id);
	END_ENCODE();
}

static int DecodeTeamInviteNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_TeamInviteNtf);
	DECODE_STRING(inviter_name);
	DECODE_BYTE(exist);
	DECODE_WORD(num);
	DeCodeTEAM_INFO(&pstOut->info[0], poNetData);
	DECODE_DWORD(session_id);
	END_DECODE();
}

static int EnCodeGetAroundTeamAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_GetAroundTeamAck);
	ENCODE_BYTE(list_size);
	for (int i = 0; i < 20; i++)
	{
		if (i >= (int)pstIn->list_size)
			break;
		if (-1 == EnCodeTEAM_MEMBER(&pstIn->list_data[i], poNetData))
			return -1;
	}
	ENCODE_DWORD(session_id);
	END_ENCODE();
}

static int DeCodeGetAroundTeamAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_GetAroundTeamAck);
	DECODE_BYTE(list_size);
	for (int i = 0; i < 20; i++)
	{
		if (i >= (int)pstOut->list_size)
			break;
		if (-1 == DeCodeTEAM_MEMBER(&pstOut->list_data[i], poNetData))
			return -1;
	}
	DECODE_DWORD(session_id);
	END_DECODE();
}

static int EncodeTeamTeamJoinNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_TeamJoinNtf);
	ENCODE_STRING(joiner);
	ENCODE_DWORD(session_id);
	END_ENCODE();
}

static int DecodeTeamTeamJoinNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_TeamJoinNtf);
	DECODE_STRING(joiner);
	DECODE_DWORD(session_id);
	END_DECODE();
}

static int EncodeTeamLeaderNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_TeamLeaderNtf);
	ENCODE_QWORD(leader_guid);
	ENCODE_DWORD(session_id);
	END_ENCODE();
}

static int DecodeTeamLeaderNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_TeamLeaderNtf);
	DECODE_QWORD(leader_guid);
	DECODE_DWORD(session_id);
	END_DECODE();
}

static int EncodeSyncQuestReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SyncQuestReq);
    ENCODE_QWORD(playerid);
    ENCODE_QWORD(roleid);
    if (EnCodeQUEST_INFO(&pstIn->quest_info, poNetData) == -1)
        return -1;

    ENCODE_BYTE(quest_achev_num);
    for (uint8_t i = 0; i < pstIn->quest_achev_num; ++i)
        if (EnCodeQUEST_ACHIEVE(pstIn->quest_achevs + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeSyncQuestReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SyncQuestReq);
    DECODE_QWORD(playerid);
    DECODE_QWORD(roleid);
    if (DeCodeQUEST_INFO(&pstOut->quest_info, poNetData) == -1)
        return -1;

    DECODE_BYTE(quest_achev_num);
    for (uint8_t i = 0; i < pstOut->quest_achev_num; ++i)
        if (DeCodeQUEST_ACHIEVE(pstOut->quest_achevs + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodeQuestUpdateNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_QuestUpdateNtf);
    ENCODE_DWORD(client_sessionid);
    ENCODE_WORD(quest_id);
    ENCODE_INT(data_type);
    ENCODE_INT(id);
    ENCODE_INT(value);
    END_ENCODE();
}

static int DecodeQuestUpdateNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_QuestUpdateNtf);
    DECODE_DWORD(client_sessionid);
    DECODE_WORD(quest_id);
    DECODE_INT(data_type);
    DECODE_INT(id);
    DECODE_INT(value);
    END_DECODE();
}

static int EncodeQuestDropNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_QuestDropNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_WORD(quest_id);
    END_ENCODE();
}

static int DecodeQuestDropNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_QuestDropNtf);
    DECODE_DWORD(sessionid);
    DECODE_WORD(quest_id);
    END_DECODE();
}

static int EncodeQuestStateNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_QuestStateNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_WORD(quest_id);
    ENCODE_BYTE(state);
    END_ENCODE();
}

static int DecodeQuestStateNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_QuestStateNtf);
    DECODE_DWORD(sessionid);
    DECODE_WORD(quest_id);
    DECODE_BYTE(state);
    END_DECODE();
}

static int EncodeQuestNpcStateNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_QuestNpcStateNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_WORD(npc_id);
    ENCODE_BYTE(state);
    END_ENCODE();
}

static int DecodeQuestNpcStateNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_QuestNpcStateNtf);
    DECODE_DWORD(sessionid);
    DECODE_WORD(npc_id);
    DECODE_BYTE(state);
    END_DECODE();
}

static int EncodeRoleAttrExtRefNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_RoleAttrExtRefNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_WORD(attr_name);
    ENCODE_INT64(attr_value);
    END_ENCODE();
}

static int DecodeRoleAttrExtRefNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_RoleAttrExtRefNtf);
    DECODE_DWORD(sessionid);
    DECODE_WORD(attr_name);
    DECODE_INT64(attr_value);
    END_DECODE();
}

static int EncodeLevelUpNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_LevelUpNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_QWORD(player_guid);
    ENCODE_DWORD(level);
    END_ENCODE();
}

static int DecodeLevelUpNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_LevelUpNtf);
    DECODE_DWORD(sessionid);
    DECODE_QWORD(player_guid);
    DECODE_DWORD(level);
    END_DECODE();
}

static int EncodeRoleAppNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_RoleAppNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_QWORD(player_guid);
    ENCODE_WORD(hair);
    ENCODE_WORD(hair_color);
    ENCODE_WORD(body);
    ENCODE_WORD(weapon);
    ENCODE_WORD(wings);
    ENCODE_WORD(mount);
    ENCODE_WORD(weapon_effect);
    ENCODE_WORD(body_effect);
    ENCODE_WORD(mount_effect);
    ENCODE_WORD(amulet);
    ENCODE_WORD(equip_num);

    for (uint16_t i = 0; i < pstIn->equip_num; ++i)
        if (EnCodeEQUIP_INFO(pstIn->equips + i, poNetData) == -1)
            return -1;

    ENCODE_BYTE(is_first);
    END_ENCODE();
}

static int DecodeRoleAppNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_RoleAppNtf);
    DECODE_DWORD(sessionid);
    DECODE_QWORD(player_guid);
    DECODE_WORD(hair);
    DECODE_WORD(hair_color);
    DECODE_WORD(body);
    DECODE_WORD(weapon);
    DECODE_WORD(wings);
    DECODE_WORD(mount);
    DECODE_WORD(weapon_effect);
    DECODE_WORD(body_effect);
    DECODE_WORD(mount_effect);
    DECODE_WORD(amulet);
    DECODE_WORD(equip_num);

    for (uint16_t i = 0; i < pstOut->equip_num; ++i)
        if (DeCodeEQUIP_INFO(pstOut->equips + i, poNetData) == -1)
            return -1;

    DECODE_BYTE(is_first);
    END_DECODE();
}

static int EncodeGetGuildsReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_GetGuildsReq);
    END_ENCODE();
}

static int DecodeGetGuildsReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_GetGuildsReq);
    END_DECODE();
}

static int EncodeGetGuildMembersReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_GetGuildMembersReq);
    END_ENCODE();
}

static int DecodeGetGuildMembersReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_GetGuildMembersReq);
    END_DECODE();
}

static int EncodeGetGuildApplicantsReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_GetGuildApplicantsReq);
    END_ENCODE();
}

static int DecodeGetGuildApplicantsReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_GetGuildApplicantsReq);
    END_DECODE();
}

static int EncodeFamilyNoticeAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_FamilyNoticeAck);
    ENCODE_DWORD(sessionid);
    ENCODE_DWORD(notice_len);
    ENCODE_STRING(notice);
    END_ENCODE();
}

static int DecodeFamilyNoticeAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_FamilyNoticeAck);
    DECODE_DWORD(sessionid);
    DECODE_DWORD(notice_len);
    DECODE_STRING(notice);
    END_DECODE();
}

static int EncodeFamilyMembersAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_FamilyMembersAck);
    ENCODE_DWORD(sessionid);
    ENCODE_DWORD(total_num);
    ENCODE_DWORD(first_index);
    ENCODE_DWORD(members_num);

    for (uint32_t i = 0; i < pstIn->members_num; ++i)
        if (EnCodeMEMBER_INFO(pstIn->members + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeFamilyMembersAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_FamilyMembersAck);
    DECODE_DWORD(sessionid);
    DECODE_DWORD(total_num);
    DECODE_DWORD(first_index);
    DECODE_DWORD(members_num);

    for (uint32_t i = 0; i < pstOut->members_num; ++i)
        if (DeCodeMEMBER_INFO(pstOut->members + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodeFamilyEnemyAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_FamilyEnemyAck);
    ENCODE_DWORD(sessionid);
    ENCODE_DWORD(total_num);
    ENCODE_DWORD(first_index);
    ENCODE_DWORD(enemy_num);

    for (uint32_t i = 0; i < pstIn->enemy_num; ++i)
        if (EnCodeFAMILY_INFO(pstIn->enemy + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeFamilyEnemyAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_FamilyEnemyAck);
    DECODE_DWORD(sessionid);
    DECODE_DWORD(total_num);
    DECODE_DWORD(first_index);
    DECODE_DWORD(enemy_num);

    for (uint32_t i = 0; i < pstOut->enemy_num; ++i)
        if (DeCodeFAMILY_INFO(pstOut->enemy + i, poNetData) == -1)
            return -1;

    END_DECODE();
}
static int EncodeFamilyAllyAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_FamilyAllyAck);
    ENCODE_DWORD(sessionid);
    ENCODE_DWORD(total_num);
    ENCODE_DWORD(first_index);
    ENCODE_DWORD(ally_num);

    for (uint32_t i = 0; i < pstIn->ally_num; ++i)
        if (EnCodeFAMILY_INFO(pstIn->ally + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeFamilyAllyAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_FamilyAllyAck);
    DECODE_DWORD(sessionid);
    DECODE_DWORD(total_num);
    DECODE_DWORD(first_index);
    DECODE_DWORD(ally_num);

    for (uint32_t i = 0; i < pstOut->ally_num; ++i)
        if (DeCodeFAMILY_INFO(pstOut->ally + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodeFamilyJoinListAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_FamilyJoinListAck);
    ENCODE_DWORD(sessionid);
    ENCODE_DWORD(total_num);
    ENCODE_DWORD(first_index);
    ENCODE_WORD(num);

    for (uint16_t i = 0; i < pstIn->num; ++i)
        if (EnCodeAPPLICANTS_INFO(pstIn->info + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeFamilyJoinListAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_FamilyJoinListAck);
    DECODE_DWORD(sessionid);
    DECODE_DWORD(total_num);
    DECODE_DWORD(first_index);
    DECODE_WORD(num);

    for (uint16_t i = 0; i < pstOut->num; ++i)
        if (DeCodeAPPLICANTS_INFO(pstOut->info + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodeFamilyBaseInfoAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_FamilyBaseInfoAck);
    ENCODE_DWORD(sessionid);
    ENCODE_QWORD(family_guid);
    ENCODE_STRING(name);
    ENCODE_DWORD(members_num);
    ENCODE_QWORD(create_time);
    ENCODE_BYTE(self_title_id);
    END_ENCODE();
}

static int DecodeFamilyBaseInfoAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_FamilyBaseInfoAck);
    DECODE_DWORD(sessionid);
    DECODE_QWORD(family_guid);
    DECODE_STRING(name);
    DECODE_DWORD(members_num);
    DECODE_QWORD(create_time);
    DECODE_BYTE(self_title_id);
    END_DECODE();
}

static int EncodeFamilyListNtfAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_FamilyListNtfAck);
    ENCODE_DWORD(sessionid);
    ENCODE_DWORD(total_num);
    ENCODE_DWORD(first_index);
    ENCODE_DWORD(num);

    for (uint32_t i = 0; i < pstIn->num; ++i)
        if (EnCodeFAMILY_APPLY_INFO(pstIn->familys + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeFamilyListNtfAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_FamilyListNtfAck);
    DECODE_DWORD(sessionid);
    DECODE_DWORD(total_num);
    DECODE_DWORD(first_index);
    DECODE_DWORD(num);

    for (uint32_t i = 0; i < pstOut->num; ++i)
        if (DeCodeFAMILY_APPLY_INFO(pstOut->familys + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodePopDlgMsgNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_PopDlgMsgNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_STRING(msg);
    END_ENCODE();
}

static int DecodePopDlgMsgNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_PopDlgMsgNtf);
    DECODE_DWORD(sessionid);
    DECODE_STRING(msg);
    END_DECODE();
}

static int EncodeSyncPlayerCustVar(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SyncPlayerCustVar);
    ENCODE_QWORD(playerid);
    ENCODE_QWORD(roleid);

    if (!pstIn->vars) return -1;

    auto count = static_cast<uint16_t>(pstIn->vars->size());
    if (poNetData->AddWord(count) == -1) return -1;

    for (auto &it : *pstIn->vars)
        if (EnCodeCUST_VAR(&it.second, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeSyncPlayerCustVar(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SyncPlayerCustVar);
    DECODE_QWORD(playerid);
    DECODE_QWORD(roleid);

    uint16_t count = 0;
    if (poNetData->DelWord(count) == -1) return -1;

    auto vars = std::make_unique<CUST_VAR_MAP>();

    CUST_VAR var;

    for (uint16_t i = 0; i < count; ++i) {

        if (DeCodeCUST_VAR(&var, poNetData) == -1) return -1;

        (*vars)[var.name] = std::move(var);
    }

    pstOut->vars = vars.release();

    END_DECODE();
}

static int EncodeSetCustVar(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SetCustVar);

    if (!pstIn->var) return -1;

    if (EnCodeCUST_VAR(pstIn->var, poNetData) == -1) return -1;

    END_ENCODE();
}

static int DecodeSetCustVar(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SetCustVar);

    auto var = std::make_unique<CUST_VAR>();

    if (DeCodeCUST_VAR(var.get(), poNetData) == -1) return -1;

    pstOut->var = var.release();

    END_DECODE();
}

static int EncodeSyncPlayerItemCustVar(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SyncPlayerItemCustVar);
    ENCODE_QWORD(playerid);
    ENCODE_QWORD(roleid);

    if (EnCodeCUST_VAR_SP_LIST(pstIn->vars, poNetData) == -1) return -1;

    END_ENCODE();
}

static int DecodeSyncPlayerItemCustVar(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SyncPlayerItemCustVar);
    DECODE_QWORD(playerid);
    DECODE_QWORD(roleid);

    auto vars = std::make_unique<CUST_VAR_SP_LIST>();
    if (DeCodeCUST_VAR_SP_LIST(vars.get(), poNetData) == -1) return -1;
    pstOut->vars = vars.release();

    END_DECODE();
}

static int EncodeGetCustVarReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_GetCustVarReq);
    END_ENCODE();
}

static int DecodeGetCustVarReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_GetCustVarReq);
    END_DECODE();
}

static int EncodePlayerQueryNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_PlayerQueryNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_QWORD(player_guid);
    ENCODE_STRING(name);
    ENCODE_BYTE(gender);
    ENCODE_BYTE(job);
    ENCODE_DWORD(level);
    ENCODE_STRING(family_name);
    ENCODE_STRING(family_title);
    ENCODE_STRING(alias);
	ENCODE_BYTE(isFinalPack);
    ENCODE_WORD(item_num);

    for (uint16_t i = 0; i < pstIn->item_num; ++i)
        if (EnCodeITEM_INFO(pstIn->item_info + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodePlayerQueryNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_PlayerQueryNtf);
    DECODE_DWORD(sessionid);
    DECODE_QWORD(player_guid);
    DECODE_STRING(name);
    DECODE_BYTE(gender);
    DECODE_BYTE(job);
    DECODE_DWORD(level);
    DECODE_STRING(family_name);
    DECODE_STRING(family_title);
    DECODE_STRING(alias);
	DECODE_BYTE(isFinalPack);
    DECODE_WORD(item_num);

    for (uint16_t i = 0; i < pstOut->item_num; ++i)
        if (DeCodeITEM_INFO(pstOut->item_info + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodeUpdateTopListAck(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_UpdateTopListAck);
	ENCODE_QWORD(role);
	if (EnCodeTOPLIST_INFO(&pstIn->nowRole, poNetData) == -1)
		return -1;

	END_ENCODE();
}

static int DecodeUpdateTopListAck(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_UpdateTopListAck);
	DECODE_QWORD(role);
	if (DeCodeTOPLIST_INFO(&pstOut->nowRole, poNetData) == -1)
		return -1;

	END_DECODE();
}

static int EncodeMsgNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_MsgNtf);
	ENCODE_DWORD(sessionid);
	ENCODE_BYTE(foreground);
	ENCODE_BYTE(background);
	ENCODE_BYTE(count);
	ENCODE_BYTE(site);
	ENCODE_STRING(msg);
	END_ENCODE();
}

static int DecodeMsgNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_MsgNtf);
	DECODE_DWORD(sessionid);
	DECODE_BYTE(foreground);
	DECODE_BYTE(background);
	DECODE_BYTE(count);
	DECODE_BYTE(site);
	DECODE_STRING(msg);
	END_DECODE();
}

static int EncodePlayerFamilyChangeNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_PlayerFamilyChangeNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_QWORD(player_guid);
    ENCODE_STRING(family_name);
    ENCODE_STRING(castle_name);
    ENCODE_BYTE(title);
    END_ENCODE();
}

static int DecodePlayerFamilyChangeNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_PlayerFamilyChangeNtf);
    DECODE_DWORD(sessionid);
    DECODE_QWORD(player_guid);
    DECODE_STRING(family_name);
    DECODE_STRING(castle_name);
    DECODE_BYTE(title);
    END_DECODE();
}

static int EncodeSyncGuildApplicant(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SyncGuildApplicant);
    ENCODE_BYTE(type);

    if (!pstIn->applicant) return -1;

    if (EnCodeGUILD_APPLY_INFO(pstIn->applicant, poNetData) == -1)
        return -1;

    END_ENCODE();
}

static int DecodeSyncGuildApplicant(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SyncGuildApplicant);
    DECODE_BYTE(type);

    auto applicant = std::make_unique<GUILD_APPLY_INFO>();

    if (DeCodeGUILD_APPLY_INFO(applicant.get(), poNetData) == -1)
        return -1;

    pstOut->applicant = applicant.release();

    END_DECODE();
}

static int EncodeCancelFamilyJoinAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_CancelFamilyJoinAck);
    ENCODE_DWORD(sessionid);
    ENCODE_QWORD(guid);
    ENCODE_DWORD(errcode);
    END_ENCODE();
}

static int DecodeCancelFamilyJoinAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_CancelFamilyJoinAck);
    DECODE_DWORD(sessionid);
    DECODE_QWORD(guid);
    DECODE_DWORD(errcode);
    END_DECODE();
}

static int EncodeSyncGuildMember(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SyncGuildMember);
    ENCODE_BYTE(type);

    if (!pstIn->member) return -1;

    if (EnCodeGUILD_MEMBER(pstIn->member, poNetData) == -1)
        return -1;

    END_ENCODE();
}

static int DecodeSyncGuildMember(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SyncGuildMember);
    DECODE_BYTE(type);

    auto member = std::make_unique<GUILD_MEMBER>();

    if (DeCodeGUILD_MEMBER(member.get(), poNetData) == -1)
        return -1;

    pstOut->member = member.release();

    END_DECODE();
}

static int EncodeFamilyLeaveNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_FamilyLeaveNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_STRING(kicker_name);
    ENCODE_STRING(family_name);
    END_ENCODE();
}

static int DecodeFamilyLeaveNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_FamilyLeaveNtf);
    DECODE_DWORD(sessionid);
    DECODE_STRING(kicker_name);
    DECODE_STRING(family_name);
    END_DECODE();
}

static int EncodeFamilyInfoNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_FamilyInfoNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_DWORD(type);
    END_ENCODE();
}

static int DecodeFamilyInfoNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_FamilyInfoNtf);
    DECODE_DWORD(sessionid);
    DECODE_DWORD(type);
    END_DECODE();
}

static int EncodeSyncGuildInfo(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SyncGuildInfo);
    ENCODE_BYTE(type);

    if (!pstIn->guild) return -1;

    if (EnCodeGUILD_INFO(pstIn->guild, poNetData) == -1)
        return -1;

    END_ENCODE();
}

static int DecodeSyncGuildInfo(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SyncGuildInfo);
    DECODE_BYTE(type);

    auto guild = std::make_unique<GUILD_INFO>();

    if (DeCodeGUILD_INFO(guild.get(), poNetData) == -1)
        return -1;

    pstOut->guild = guild.release();

    END_DECODE();
}

static int EncodeSyncGuildRelation(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SyncGuildRelation);
    ENCODE_BYTE(type);
    ENCODE_QWORD(my_guild_guid);
    ENCODE_QWORD(peer_guild_guid);
    ENCODE_BYTE(relation);
    END_ENCODE();
}

static int DecodeSyncGuildRelation(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SyncGuildRelation);
    DECODE_BYTE(type);
    DECODE_QWORD(my_guild_guid);
    DECODE_QWORD(peer_guild_guid);
    DECODE_BYTE(relation);
    END_DECODE();
}

static int EncodeMissNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_MissNtf);
    ENCODE_QWORD(actor);
    ENCODE_QWORD(target);
    ENCODE_WORD(skill_id);
    ENCODE_BYTE(type);
    ENCODE_WORD(clsessnum);
    ENCODE_BLOB(clsessids, pstIn->clsessnum * sizeof(uint32_t));
    END_ENCODE();
}

static int DecodeMissNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_MissNtf);
    DECODE_QWORD(actor);
    DECODE_QWORD(target);
    DECODE_WORD(skill_id);
    DECODE_BYTE(type);
    DECODE_WORD(clsessnum);
    DECODE_BLOB(clsessids, pstOut->clsessnum * sizeof(uint32_t));
    END_DECODE();
}

static int EncodeSyncItemDynAttrs(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SyncItemDynAttrs);
    ENCODE_QWORD(playerid);
    ENCODE_QWORD(roleid);

    if (EnCodeITEM_DYN_ATTRS_LIST(pstIn->attrs_list, poNetData) == -1) return -1;

    END_ENCODE();
}

static int DecodeSyncItemDynAttrs(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SyncItemDynAttrs);
    DECODE_QWORD(playerid);
    DECODE_QWORD(roleid);

    auto attrsList = std::make_unique<ITEM_DYN_ATTRS_LIST>();

    if (DeCodeITEM_DYN_ATTRS_LIST(attrsList.get(), poNetData) == -1) return -1;

    pstOut->attrs_list = attrsList.release();

    END_DECODE();
}

static int EncodeSyncRoleDynAttrs(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_SyncRoleDynAttrs);
	ENCODE_QWORD(playerid);
	ENCODE_QWORD(roleid);

	if (EnCodeITEM_DYN_ATTRS_LIST(pstIn->attrs_list, poNetData) == -1) return -1;

	END_ENCODE();
}

static int DecodeSyncRoleDynAttrs(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_SyncRoleDynAttrs);
	DECODE_QWORD(playerid);
	DECODE_QWORD(roleid);

	auto attrsList = std::make_unique<ROLE_DYN_ATTRS_LIST>();

	if (DeCodeITEM_DYN_ATTRS_LIST(attrsList.get(), poNetData) == -1) return -1;

	pstOut->attrs_list = attrsList.release();

	END_DECODE();
}

static int EncodeSkillStatusNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SkillStatusNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_WORD(id);
    ENCODE_BYTE(active);
    END_ENCODE();
}

static int DecodeSkillStatusNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SkillStatusNtf);
    DECODE_DWORD(sessionid);
    DECODE_WORD(id);
    DECODE_BYTE(active);
    END_DECODE();
}

static int EncodeShabakOwnerNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_ShabakOwnerNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_QWORD(role_guid);
    END_ENCODE();
}

static int DecodeShabakOwnerNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_ShabakOwnerNtf);
    DECODE_DWORD(sessionid);
    DECODE_QWORD(role_guid);
    END_DECODE();
}

static int EncodeShabakLossNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_ShabakLossNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_QWORD(role_guid);
    END_ENCODE();
}

static int DecodeShabakLossNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_ShabakLossNtf);
    DECODE_DWORD(sessionid);
    DECODE_QWORD(role_guid);
    END_DECODE();
}

static int EncodeShabakEngageNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_ShabakEngageNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_STRING(own_family);
    ENCODE_STRING(attack_families);
    END_ENCODE();
}

static int DecodeShabakEngageNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_ShabakEngageNtf);
    DECODE_DWORD(sessionid);
    DECODE_STRING(own_family);
    DECODE_STRING(attack_families);
    END_DECODE();
}

static int EncodeShabakEndNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_ShabakEndNtf);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodeShabakEndNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_ShabakEndNtf);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodeRunningFamilyWarNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_RunningFamilyWarNtf);
	ENCODE_DWORD(sessionid);
	ENCODE_WORD(num);
	for (uint16_t i = 0; i < pstIn->num; ++i)
	{
		if (EnCodeFAMILY_WAR_INFO(&pstIn->families[i], poNetData) == -1)
			return -1;
	}
	ENCODE_BYTE(idx);
	ENCODE_BYTE(total);
	END_ENCODE();
}

static int DecodeRunningFamilyWarNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_RunningFamilyWarNtf);
	DECODE_DWORD(sessionid);
	DECODE_WORD(num);
	for (uint16_t i = 0; i < pstOut->num; ++i)
	{
		if (DeCodeFAMILY_WAR_INFO(&pstOut->families[i], poNetData) == -1)
			return -1;
	}
	DECODE_BYTE(idx);
	DECODE_BYTE(total);
	END_DECODE();
}

static int EncodeSkillCDChangedNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SkillCDChangedNtf);
    ENCODE_DWORD(clsessid);
    ENCODE_WORD(skill_id);
    ENCODE_DWORD(new_cd);
    END_ENCODE();
}

static int DecodeSkillCDChangedNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SkillCDChangedNtf);
    DECODE_DWORD(clsessid);
    DECODE_WORD(skill_id);
    DECODE_DWORD(new_cd);
    END_DECODE();
}

static int EncodeSkillPropPermanentChangedNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SkillPropPermanentChangedNtf);
    ENCODE_DWORD(clsessid);
	ENCODE_QWORD(player_guid);
	ENCODE_WORD(num);
	for (int i = 0; i < pstIn->num; ++i)
		if (EnCodeSKILL_INFO(pstIn->info + i, poNetData) == -1)
			return -1;
    END_ENCODE();
}

static int DecodeSkillPropPermanentChangedNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SkillPropPermanentChangedNtf);
    DECODE_DWORD(clsessid);
	DECODE_QWORD(player_guid);
	DECODE_WORD(num);
	for (int i = 0; i < pstOut->num; ++i)
		if (DeCodeSKILL_INFO(pstOut->info + i, poNetData) == -1)
			return -1;
    END_DECODE();
}

static int EncodeGetWantedListReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_GetWantedListReq);
    END_ENCODE();
}

static int DecodeGetWantedListReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_GetWantedListReq);
    END_DECODE();
}

static int EncodeGetWantedListAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_GetWantedListAck);

    if (!pstIn->pwanted_list) return -1;

    const auto &wanted_list = *pstIn->pwanted_list;

    auto count = static_cast<uint16_t>(wanted_list.size());
    if (poNetData->AddWord(count) == -1) return -1;

    for (const auto &wanted : wanted_list)
        if (EnCodeWANTED(wanted.get(), poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeGetWantedListAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_GetWantedListAck);

    uint16_t count = 0;
    if (poNetData->DelWord(count) == -1) return -1;

    auto upWantedList = std::make_unique<WANTED_SP_LIST>();

    for (uint16_t i = 0; i < count; ++i) {

        auto spWanted = std::make_shared<WANTED>();

        if (DeCodeWANTED(spWanted.get(), poNetData) == -1)
            return -1;

        upWantedList->emplace_back(std::move(spWanted));
    }

    pstOut->pwanted_list = upWantedList.release();

    END_DECODE();
}

static int EncodePostBountyReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_PostBountyReq);
    ENCODE_QWORD(wanted_by_guid);
    ENCODE_STRING(wanted_by_name);
    ENCODE_STRING(wanted_name);
    ENCODE_DWORD(bounty);
    ENCODE_STRING(desc);
    ENCODE_QWORD(ptime);
    END_ENCODE();
}

static int DecodePostBountyReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_PostBountyReq);
    DECODE_QWORD(wanted_by_guid);
    DECODE_STRING(wanted_by_name);
    DECODE_STRING(wanted_name);
    DECODE_DWORD(bounty);
    DECODE_STRING(desc);
    DECODE_QWORD(ptime);
    END_DECODE();
}

static int EncodePostBountyAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_PostBountyAck);
    ENCODE_BYTE(result);
    ENCODE_DWORD(index);
    ENCODE_QWORD(wanted_by_guid);
    ENCODE_STRING(wanted_by_name);
    ENCODE_QWORD(wanted_guid);
    ENCODE_STRING(wanted_name);
    ENCODE_DWORD(bounty);
    ENCODE_STRING(desc);
    ENCODE_QWORD(ptime);
    END_ENCODE();
}

static int DecodePostBountyAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_PostBountyAck);
    DECODE_BYTE(result);
    DECODE_DWORD(index);
    DECODE_QWORD(wanted_by_guid);
    DECODE_STRING(wanted_by_name);
    DECODE_QWORD(wanted_guid);
    DECODE_STRING(wanted_name);
    DECODE_DWORD(bounty);
    DECODE_STRING(desc);
    DECODE_QWORD(ptime);
    END_DECODE();
}

static int EncodeCheckRoleExistenceReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_CheckRoleExistenceReq);
	ENCODE_DWORD(seq);
    ENCODE_BYTE(by);
    ENCODE_STRING(name);
    ENCODE_QWORD(guid);
    END_ENCODE();
}

static int DecodeCheckRoleExistenceReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_CheckRoleExistenceReq);
	DECODE_DWORD(seq);
    DECODE_BYTE(by);
    DECODE_STRING(name);
    DECODE_QWORD(guid);
    END_DECODE();
}

static int EncodeCheckRoleExistenceAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_CheckRoleExistenceAck);
	ENCODE_DWORD(seq);
    ENCODE_BYTE(by);
    ENCODE_STRING(name);
    ENCODE_QWORD(guid);
    ENCODE_BYTE(exist);
    END_ENCODE();
}

static int DecodeCheckRoleExistenceAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_CheckRoleExistenceAck);
	DECODE_DWORD(seq);
    DECODE_BYTE(by);
    DECODE_STRING(name);
    DECODE_QWORD(guid);
    DECODE_BYTE(exist);
    END_DECODE();
}

static int EncodeSkillProficiencyNtf(void *pHost, CNetData *poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_SkillProficiencyNtf);
	ENCODE_DWORD(clsessid);
	ENCODE_WORD(id);
	ENCODE_DWORD(proficiency);
	END_ENCODE();
}

static int DecodeSkillProficiencyNtf(void *pHost, CNetData *poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_SkillProficiencyNtf);
	DECODE_DWORD(clsessid);
	DECODE_WORD(id);
	DECODE_DWORD(proficiency);
	END_DECODE();
}

static int EncodeItemPickupNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_ItemPickupNtf);
    ENCODE_DWORD(clsessid);
    ENCODE_QWORD(item_guid);
    ENCODE_QWORD(role_guid);
    END_ENCODE();
}

static int DecodeItemPickupNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_ItemPickupNtf);
    DECODE_DWORD(clsessid);
    DECODE_QWORD(item_guid);
    DECODE_QWORD(role_guid);
    END_DECODE();
}

static int EncodeAutoPickupSettingsNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_AutoPickupSettingsNtf);
    ENCODE_DWORD(clsessid);

    if (EncodeAUTO_PICKUP(&pstIn->auto_pickup, poNetData) == -1)
        return -1;

    END_ENCODE();
}

static int DecodeAutoPickupSettingsNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_AutoPickupSettingsNtf);
    DECODE_DWORD(clsessid);

    if (DecodeAUTO_PICKUP(&pstOut->auto_pickup, poNetData) == -1)
        return -1;

    END_DECODE();
}

static int EncodeStartDigAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_StartDigAck);
    ENCODE_DWORD(clsessid);
    ENCODE_QWORD(treasure_guid);
    ENCODE_BYTE(code);
    ENCODE_DWORD(dig_time);
    END_ENCODE();
}

static int DecodeStartDigAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_StartDigAck);
    DECODE_DWORD(clsessid);
    DECODE_QWORD(treasure_guid);
    DECODE_BYTE(code);
    DECODE_DWORD(dig_time);
    END_DECODE();
}

static int EncodeStopDigNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_StopDigNtf);
    ENCODE_DWORD(clsessid);
    ENCODE_QWORD(treasure_guid);
    ENCODE_BYTE(reason);
    END_ENCODE();
}

static int DecodeStopDigNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_StopDigNtf);
    DECODE_DWORD(clsessid);
    DECODE_QWORD(treasure_guid);
    DECODE_BYTE(reason);
    END_DECODE();
}

static int EncodeRoleAppearNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_RoleAppearNtf);
    ENCODE_DWORD(clsessid);
    ENCODE_QWORD(role_guid);
    ENCODE_BYTE(appear_type);
    END_ENCODE();
}

static int DecodeRoleAppearNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_RoleAppearNtf);
    DECODE_DWORD(clsessid);
    DECODE_QWORD(role_guid);
    DECODE_BYTE(appear_type);
    END_DECODE();
}

static int EncodeSaveIssueRecord(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SaveGoodsIssueRecord);
    ENCODE_QWORD(player_guid);
    ENCODE_QWORD(role_guid);
    if (EncodeGOODS_ISSUE_RECORD(&pstIn->record, poNetData) == -1) return -1;
    END_ENCODE();
}

static int DecodeSaveIssueRecord(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SaveGoodsIssueRecord);
    DECODE_QWORD(player_guid);
    DECODE_QWORD(role_guid);
    if (DecodeGOODS_ISSUE_RECORD(&pstOut->record, poNetData) == -1) return -1;
    END_DECODE();
}

static int EncodeVerifyBuyItemInfoAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_VerifyBuyItemInfoAck);
    ENCODE_DWORD(clsessid);
    ENCODE_DWORD(item_id);
    ENCODE_BYTE(status);
    END_ENCODE();
}

static int DecodeVerifyBuyItemInfoAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_VerifyBuyItemInfoAck);
    DECODE_DWORD(clsessid);
    DECODE_DWORD(item_id);
    DECODE_BYTE(status);
    END_DECODE();
}

static int EncodeGoodsIssuedNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_GoodsIssuedNtf);
    ENCODE_QWORD(player_guid);
    ENCODE_QWORD(role_guid);
    ENCODE_BYTE(num);
    ENCODE_CHECK_UPBOUND(num, order_no);
    for (uint8_t i = 0; i < pstIn->num; ++i)
        ENCODE_STRING(order_no[i]);
    END_ENCODE();
}

static int DecodeGoodsIssuedNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_GoodsIssuedNtf);
    DECODE_QWORD(player_guid);
    DECODE_QWORD(role_guid);
    DECODE_BYTE(num);
    DECODE_CHECK_UPBOUND(num, order_no);
    for (uint8_t i = 0; i < pstOut->num; ++i)
        DECODE_STRING(order_no[i]);
    END_DECODE();
}

static int EncodeSyncGoodsPostRecord(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_SyncGoodsPostRecord);
	ENCODE_QWORD(player_guid);
	ENCODE_QWORD(role_guid);
	ENCODE_BYTE(num);
	ENCODE_CHECK_UPBOUND(num, order_no);
	for (uint8_t i = 0; i < pstIn->num; ++i)
		ENCODE_STRING(order_no[i]);
	END_ENCODE();
}

static int DecodeSyncGoodsPostRecord(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_SyncGoodsPostRecord);
	DECODE_QWORD(player_guid);
	DECODE_QWORD(role_guid);
	DECODE_BYTE(num);
	DECODE_CHECK_UPBOUND(num, order_no);
	for (uint8_t i = 0; i < pstOut->num; ++i)
		DECODE_STRING(order_no[i]);
	END_DECODE();
}

static int EncodeRebateMoneyUsedNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_RebateMoneyUsedNtf);
	ENCODE_QWORD(role_guid);
	if (EncodeREBATE_MONEY_RECORD(&pstIn->record, poNetData) == -1)
		return -1;
	END_ENCODE();
}

static int DecodeRebateMoneyUsedNtf(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_RebateMoneyUsedNtf);
	DECODE_QWORD(role_guid);
	if (DecodeREBATE_MONEY_RECORD(&pstOut->record, poNetData) == -1)
		return -1;
	END_DECODE();
}

static int EncodeItemTip(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_ItemTip);
	ENCODE_QWORD(guid);
	ENCODE_QWORD(owner_guid);
	ENCODE_QWORD(item_guid);
	END_ENCODE();
}

static int DecodeItemTip(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_ItemTip);
	DECODE_QWORD(guid);
	DECODE_QWORD(owner_guid);
	DECODE_QWORD(item_guid);
	END_DECODE();
}

static int EncodeMonitorChatMsg(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_MonitorChatMsg);
	if (EncodeMONITOR_CHAT_INFO(&pstIn->info, poNetData) == -1) return -1;
	END_ENCODE();
}

static int DecodeMonitorChatMsg(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_MonitorChatMsg);
	if (DecodeMONITOR_CHAT_INFO(&pstOut->info, poNetData) == -1) return -1;
	END_DECODE();
}

static int EncodeSetAutoModeReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SetAutoModeReq);
    ENCODE_DWORD(clsessid);
    ENCODE_QWORD(role_guid);
    ENCODE_BYTE(enable);
    END_ENCODE();
}

static int DecodeSetAutoModeReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SetAutoModeReq);
    DECODE_DWORD(clsessid);
    DECODE_QWORD(role_guid);
    DECODE_BYTE(enable);
    END_DECODE();
}

static int EncodeSceneItemUpdateNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_SceneItemUpdateNtf);
    ENCODE_DWORD(clsessid);
    ENCODE_QWORD(item_guid);
    END_ENCODE();
}

static int DecodeSceneItemUpdateNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_SceneItemUpdateNtf);
    DECODE_DWORD(clsessid);
    DECODE_QWORD(item_guid);
    END_DECODE();
}

static int EncodeRunGMCmd(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoMS_RunGMCmd);
    ENCODE_STRING(cmd);
    ENCODE_STRING(param);
    END_ENCODE();
}

static int DecodeRunGMCmd(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoMS_RunGMCmd);
    DECODE_STRING(cmd);
    DECODE_STRING(param);
    END_DECODE();
}

static int EncodeRunCustomHttp(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_CustomHttp);
	ENCODE_STRING(cmd);
	ENCODE_STRING(param);
	ENCODE_STRING(callBackFunc);
	END_ENCODE();
}

static int DecodeRunCustomHttp(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_CustomHttp);
	DECODE_STRING(cmd);
	DECODE_STRING(param);
	DECODE_STRING(callBackFunc);
	END_DECODE();
}

static int EncodeDelRole(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_Del_Role_By_GM);
	ENCODE_QWORD(pid);
	ENCODE_QWORD(guid);
	END_ENCODE();
}

static int DecodeDelRole(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_Del_Role_By_GM);
	DECODE_QWORD(pid);
	DECODE_QWORD(guid);
	END_DECODE();
}

static int EncodeUpdateConstantCfgReq(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE_EX(ProtoMS_UpdateConstantCfgReq);

	if (-1 == EnCodeCUSTOM_INFO(&pstIn->custom, poNetData))
		return -1;

	END_ENCODE();
}

static int DecodeUpdateConstantCfgReq(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE_EX(ProtoMS_UpdateConstantCfgReq);

	if (-1 == DeCodeCUSTOM_INFO(&pstOut->custom, poNetData))
		return -1;

	END_DECODE();
}


ProtoMS::ProtoMS()
{
	SET_ENCODER_DECODER(PROTO_MS_TEAM_LEADER_NTF, EncodeTeamLeaderNtf, DecodeTeamLeaderNtf);
	SET_ENCODER_DECODER(PROTO_MS_TEAM_JOIN_NTF, EncodeTeamTeamJoinNtf, DecodeTeamTeamJoinNtf);
	SET_ENCODER_DECODER(PROTO_MS_GET_ARROUND_TEAM_ACK, EnCodeGetAroundTeamAck, DeCodeGetAroundTeamAck);
	SET_ENCODER_DECODER(PROTO_MS_TEAM_INVITE_NTF, EncodeTeamInviteNtf, DecodeTeamInviteNtf);
	SET_ENCODER_DECODER(PROTO_MS_MISS_TEAM_NTF, EncodeMissTeamNtf, DecodeMissTeamNtf);
	SET_ENCODER_DECODER(PROTO_MS_CLEAR_ROLE_INFO_NTF, EncodeClearRoleInfoNtf, DecodeClearRoleInfoNtf);
	SET_ENCODER_DECODER(PROTO_MS_DELETE_ROLE_INFO_NTF, EncodeDeleteRoleInfoNtf, DecodeDeleteRoleInfoNtf);
	SET_ENCODER_DECODER(PROTO_MS_UPDATE_ROLE_INFO_NTF, EncodeUpdateRoleInfoNtf, DecodeUpdateRoleInfoNtf);
	SET_ENCODER_DECODER(PROTO_MS_INSERT_ROLE_INFO_NTF, EncodeInsertRoleInfoNtf, DecodeInsertRoleInfoNtf);
	SET_ENCODER_DECODER(PROTO_MS_GET_ROLE_INFO_REQ, EncodeGetRoleInfoReq, DecodeGetRoleInfoReq);
	SET_ENCODER_DECODER(PROTO_MS_GET_ROLE_INFO_ACK, EncodeGetRoleInfoAck, DecodeGetRoleInfoAck);
	SET_ENCODER_DECODER(PROTO_MS_SEND_DEL_ITEM_NTF, EncodeSendDelItemNtf, DecodeSendDelItemNtf);
	SET_ENCODER_DECODER(PROTO_MS_SEND_SYNC_ITEM_NTF, EncodeSendSyncItemNtf, DecodeSendSyncItemNtf);
	SET_ENCODER_DECODER(PROTO_MS_ITEM_ATTR_NTF, EncodeItemAttrNtf, DecodeItemAttrNtf);
	SET_ENCODER_DECODER(PROTO_MS_ITEM_PICK_UP, EncodeItemPickUp, DecodeItemPickUp);
	SET_ENCODER_DECODER(PROTO_MS_ITEM_APPEAR_NTF4, EncodeItemAppearNtf4, DecodeItemAppearNtf4);
	SET_ENCODER_DECODER(PROTO_MS_ITEM_DESTROY_ACK, EncodeItemDestroyAck, DecodeItemDestroyAck);
	SET_ENCODER_DECODER(PROTO_MS_ITEM_UPDATE_NTF, EncodeItemUpdateNtf, DecodeItemUpdateNtf);
	SET_ENCODER_DECODER(PROTO_MS_ITEM_ACK, EncodeItemAck, DecodeItemAck);
	SET_ENCODER_DECODER(PROTO_MS_DISAPPEAR_NTF, EncodeObjdisAppearNtf, DecodeObjdisAppearNtf);
	SET_ENCODER_DECODER(PROTO_MS_MONSTER_APPEAR_NTF6, EncodeMonsterAppearNtf6, DecodeMonsterAppearNtf6);
	SET_ENCODER_DECODER(PROTO_MS_HEART_BEAT_REQ, EncodeHeartBeatReq, DecodeHeartBeatReq);
	SET_ENCODER_DECODER(PROTO_MS_HEART_BEAT_ACK, EncodeHeartBeatAck, DecodeHeartBeatAck);
	SET_ENCODER_DECODER(PROTO_MS_MOVE_NTF, EncodeMoveNtf, DecodeMoveNtf);
    SET_ENCODER_DECODER(PROTO_MS_MOVE_NTF_EX, EncodeMoveNtfEx, DecodeMoveNtfEx);
    SET_ENCODER_DECODER(PROTO_MS_TURN_NTF, EncodeTurnNtf, DecodeTurnNtf);
    SET_ENCODER_DECODER(PROTO_MS_SPELL_NTF, EncodeSpellNtf, DecodeSpellNtf);
	SET_ENCODER_DECODER(PROTO_MS_ERROR_ACK, EncodeErrorAck, DecodeErrorAck);
    SET_ENCODER_DECODER(PROTO_MS_GM_ERROR_ACK, EncodeGMErrorAck, DecodeGMErrorAck);
    SET_ENCODER_DECODER(PROTO_MS_OBJDIE_NTF, EncodeObjDieNtf, DecodeObjDieNtf);
	SET_ENCODER_DECODER(PROTO_MS_SKILL_ADD_ACK, EncodeSkillAddAck, DecodeSkillAddAck);
	SET_ENCODER_DECODER(PROTO_MS_DELETE_SKILL_ACK, EncodeSkillDeleteAck, DecodeSkillDeleteAck);
    SET_ENCODER_DECODER(PROTO_MS_UPLOAD_CONFIG_REQ, EnCodeUploadConfigReq, DeCodeUploadConfigReq);
    SET_ENCODER_DECODER(PROTO_MS_CONFIG_REQ, EnCodeConfigReq, DeCodeConfigReq);
    SET_ENCODER_DECODER(PROTO_MS_CONFIG_ACK, EnCodeConfigAck, DeCodeConfigAck);
    SET_ENCODER_DECODER(PROTO_MS_ATTR_SHOW_NTF2_EX2, EnCodeAttrShowNTF2EX2, DeCodeAttrShowNTF2EX2);
    SET_ENCODER_DECODER(PROTO_MS_PLAYER_APPEAR_NTF, EncodePlayerAppearNtf, DecodePlayerAppearNtf);
    SET_ENCODER_DECODER(PROTO_MS_NPC_TALK_REQ, EnCodeNpcTalkReq, DeCodeNpcTalkReq);
    SET_ENCODER_DECODER(PROTO_MS_NPC_TALK_ACK, EnCodeNpcTalkAck, DeCodeNpcTalkAck);
    SET_ENCODER_DECODER(PROTO_MS_ROLE_ATTR_NTF, EnCodeRoleAttrNtf, DeCodeRoleAttrNtf);
    SET_ENCODER_DECODER(PROTO_MS_ROLE_ATTR_EXT_NTF, EnCodeRoleAttrExtNtf, DeCodeRoleAttrExtNtf);
	SET_ENCODER_DECODER(PROTO_MS_ENTER_MS_ACK, EncodeEnterMSAck, DecodeEnterMSAck);
	SET_ENCODER_DECODER(PROTO_MS_ENTER_MS_NTF, EncodeEnterMSNtf, DecodeEnterMSNtf);
	SET_ENCODER_DECODER(PROTO_MS_GET_SKILL_ACK, EncodeGetSkillAck, DecodeGetSkillAck);
    SET_ENCODER_DECODER(PROTO_MS_SYNC_SKILL_REQ, EncodeSyncSkillReq, DecodeSyncSkillReq);
    SET_ENCODER_DECODER(PROTO_MS_GET_BUFF_ACK, EncodeGetBuffAck, DecodeGetBuffAck);
    SET_ENCODER_DECODER(PROTO_MS_SYNC_BUFF_REQ, EncodeSyncBuffReq, DecodeSyncBuffReq);
    SET_ENCODER_DECODER(PROTO_MS_BUFF_ADD_ACK, EncodeBuffAddAck, DecodeBuffAddAck);
	SET_ENCODER_DECODER(PROTO_MS_BUFF_DESTROY_ACK, EncodeBuffDestroyAck, DecodeBuffDestroyAck);
	SET_ENCODER_DECODER(PROTO_MS_RUN_CLIENT_SCRIPT, EncodeRunClientScript, DecodeRunClientScript);
    SET_ENCODER_DECODER(PROTO_MS_SYS_MSG_NTF, EncodeSysMsgNtf, DecodeSysMsgNtf);
    SET_ENCODER_DECODER(PROTO_MS_SYNC_ROLE_INFO_REQ, EncodeSyncRoleInfoReq, DecodeSyncRoleInfoReq);
    SET_ENCODER_DECODER(PROTO_MS_NPC_APPEAR_NTF, EncodeNpcAppearNtf, DecodeNpcAppearNtf);
    SET_ENCODER_DECODER(PROTO_MS_TRADE_NPC_SHOP_NTF, EncodeTradeNpcShopNtf, DecodeTradeNpcShopNtf);
    SET_ENCODER_DECODER(PROTO_MS_QUEST_NPC_TALK_ACK, EncodeQuestNpcTalkAck, DecodeQuestNpcTalkAck);
    SET_ENCODER_DECODER(PROTO_MS_QUEST_TIMEOUT_NTF, EncodeQuestTimeoutNtf, DecodeQuestTimeoutNtf);
    SET_ENCODER_DECODER(PROTO_MS_TEAM_NTF, EncodeTeamNtf, DecodeTeamNtf);
    SET_ENCODER_DECODER(PROTO_MS_SYNC_QUEST_REQ, EncodeSyncQuestReq, DecodeSyncQuestReq);
    SET_ENCODER_DECODER(PROTO_MS_QUEST_UPDATE_NTF, EncodeQuestUpdateNtf, DecodeQuestUpdateNtf);
    SET_ENCODER_DECODER(PROTO_MS_QUEST_DROP_NTF, EncodeQuestDropNtf, DecodeQuestDropNtf);
    SET_ENCODER_DECODER(PROTO_MS_QUEST_STATE_NTF, EncodeQuestStateNtf, DecodeQuestStateNtf);
    SET_ENCODER_DECODER(PROTO_MS_QUEST_NPC_STATE_NTF, EncodeQuestNpcStateNtf, DecodeQuestNpcStateNtf);
    SET_ENCODER_DECODER(PROTO_MS_ROLE_ATTR_EXT_REF_NTF, EncodeRoleAttrExtRefNtf, DecodeRoleAttrExtRefNtf);
    SET_ENCODER_DECODER(PROTO_MS_LEVEL_UP_NTF, EncodeLevelUpNtf, DecodeLevelUpNtf);
    SET_ENCODER_DECODER(PROTO_MS_ROLE_APP_NTF, EncodeRoleAppNtf, DecodeRoleAppNtf);
    SET_ENCODER_DECODER(PROTO_MS_GET_GUILDS_REQ, EncodeGetGuildsReq, DecodeGetGuildsReq);
    SET_ENCODER_DECODER(PROTO_MS_GET_GUILD_MEMBERS_REQ, EncodeGetGuildMembersReq, DecodeGetGuildMembersReq);
    SET_ENCODER_DECODER(PROTO_MS_GET_GUILD_APPLICANTS_REQ, EncodeGetGuildApplicantsReq, DecodeGetGuildApplicantsReq);
    SET_ENCODER_DECODER(PROTO_MS_FAMILY_NOTICE_ACK, EncodeFamilyNoticeAck, DecodeFamilyNoticeAck);
    SET_ENCODER_DECODER(PROTO_MS_FAMILY_MEMBERS_ACK, EncodeFamilyMembersAck, DecodeFamilyMembersAck);
    SET_ENCODER_DECODER(PROTO_MS_FAMILY_ENEMY_ACK, EncodeFamilyEnemyAck, DecodeFamilyEnemyAck);
    SET_ENCODER_DECODER(PROTO_MS_FAMILY_ALLY_ACK, EncodeFamilyAllyAck, DecodeFamilyAllyAck);
    SET_ENCODER_DECODER(PROTO_MS_FAMILY_JOIN_LIST_ACK, EncodeFamilyJoinListAck, DecodeFamilyJoinListAck);
    SET_ENCODER_DECODER(PROTO_MS_FAMILY_BASE_INFO_ACK, EncodeFamilyBaseInfoAck, DecodeFamilyBaseInfoAck);
    SET_ENCODER_DECODER(PROTO_MS_FAMILY_LIST_NTF_ACK, EncodeFamilyListNtfAck, DecodeFamilyListNtfAck);
    SET_ENCODER_DECODER(PROTO_MS_POP_DLG_MSG_NTF, EncodePopDlgMsgNtf, DecodePopDlgMsgNtf);
    SET_ENCODER_DECODER(PROTO_MS_SYNC_PLAYER_CUST_VAR, EncodeSyncPlayerCustVar, DecodeSyncPlayerCustVar);
    SET_ENCODER_DECODER(PROTO_MS_SET_CUST_VAR, EncodeSetCustVar, DecodeSetCustVar);
    SET_ENCODER_DECODER(PROTO_MS_SYNC_PLAYER_ITEM_CUST_VAR, EncodeSyncPlayerItemCustVar, DecodeSyncPlayerItemCustVar);
    SET_ENCODER_DECODER(PROTO_MS_GET_CUST_VAR_REQ, EncodeGetCustVarReq, DecodeGetCustVarReq);
    SET_ENCODER_DECODER(PROTO_MS_PLAYER_QUERY_NTF, EncodePlayerQueryNtf, DecodePlayerQueryNtf);
	SET_ENCODER_DECODER(PROTO_MS_QUICK_BAR_SET, EnCodeQuickBarSet, DeCodeQuickBarSet);
	SET_ENCODER_DECODER(PROTO_MS_QUICK_BAR_SET_NTF, EnCodeQuickBarSetNtf, DeCodeQuickBarSetNtf);
	SET_ENCODER_DECODER(PROTO_MS_GLOBAL_NTF, EnCodeGlobalNtf, DeCodeGlobalNtf);
	SET_ENCODER_DECODER(PROTO_MS_DGN_BIND_INFO, EnCodeDgnBindInfoSet, DeCodeDgnBindInfoSet);
	SET_ENCODER_DECODER(PROTO_MS_UPDATE_TOPLIST_ACK, EncodeUpdateTopListAck, DecodeUpdateTopListAck);
	SET_ENCODER_DECODER(PROTO_MS_MSG_NTF, EncodeMsgNtf, DecodeMsgNtf);
    SET_ENCODER_DECODER(PROTO_MS_PLAYER_FAMILY_CHANGE_NTF, EncodePlayerFamilyChangeNtf, DecodePlayerFamilyChangeNtf);
    SET_ENCODER_DECODER(PROTO_MS_SYNC_GUILD_APPLICANT, EncodeSyncGuildApplicant, DecodeSyncGuildApplicant);
    SET_ENCODER_DECODER(PROTO_MS_CANCEL_FAMILY_JOIN_ACK, EncodeCancelFamilyJoinAck, DecodeCancelFamilyJoinAck);
    SET_ENCODER_DECODER(PROTO_MS_SYNC_GUILD_MEMBER, EncodeSyncGuildMember, DecodeSyncGuildMember);
    SET_ENCODER_DECODER(PROTO_MS_FAMILY_LEAVE_NTF, EncodeFamilyLeaveNtf, DecodeFamilyLeaveNtf);
    SET_ENCODER_DECODER(PROTO_MS_FAMILY_INFO_NTF, EncodeFamilyInfoNtf, DecodeFamilyInfoNtf);   
	SET_ENCODER_DECODER(PROTO_MS_SYNC_GUILD_MEMBER, EncodeSyncGuildMember, DecodeSyncGuildMember);	
	SET_ENCODER_DECODER(PROTO_MS_ADD_SYS_NEW_MAIL, EnCodeAddSysNewMail, DeCodeAddSysNewMail);
	SET_ENCODER_DECODER(PROTO_MS_NEW_MAIL_NTF, EnCodeNewMailNtf, DeCodeNewMailNtf);
	SET_ENCODER_DECODER(PROTO_MS_SYNC_MAIL_INFO_STATUS, EnCodeSyncMailInfoStatus, DeCodeSyncMailInfoStatus);
	SET_ENCODER_DECODER(PROTO_MS_GET_MAIL_LIST_ACK, EnCodeGetMailListAck, DeCodeGetMailListAck);
	SET_ENCODER_DECODER(PROTO_MS_MAIL_DEL_REQ, EnCodeMailDelReq, DeCodeMailDelReq);
	SET_ENCODER_DECODER(PROTO_MS_DELETE_MAIL_ACK, EnCodeDeleteMailAck, DeCodeDeleteMailAck);
	SET_ENCODER_DECODER(PROTO_MS_OPEN_MAIL_ACK, EnCodeMailOpenAck, DeCodeMailOpenAck);
	SET_ENCODER_DECODER(PROTO_MS_MAIL_ATTACHMENT_GET_ACK, EnCodeMailAttachmentGetAck, DeCodeMailAttachmentGetAck);
    SET_ENCODER_DECODER(PROTO_MS_SYNC_GUILD_INFO, EncodeSyncGuildInfo, DecodeSyncGuildInfo);
    SET_ENCODER_DECODER(PROTO_MS_SYNC_GUILD_RELATION, EncodeSyncGuildRelation, DecodeSyncGuildRelation);
    SET_ENCODER_DECODER(PROTO_MS_MISS_NTF, EncodeMissNtf, DecodeMissNtf);
    SET_ENCODER_DECODER(PROTO_MS_SYNC_ITEM_DYN_ATTRS, EncodeSyncItemDynAttrs, DecodeSyncItemDynAttrs);
	SET_ENCODER_DECODER(PROTO_MS_SYNC_ROLE_DYN_ATTRS, EncodeSyncRoleDynAttrs, DecodeSyncRoleDynAttrs);
	SET_ENCODER_DECODER(PROTO_MS_GET_TRADE_DELEGATE_REQ, EncodeGetTradeDelegateReq, DecodeGetTradeDelegateReq);
	SET_ENCODER_DECODER(PROTO_MS_GET_TRADE_RECORDS_REQ, EncodeGetTradeRecordsReq, DecodeGetTradeRecordsReq);
	SET_ENCODER_DECODER(PROTO_MS_RECORDS_MINE_ACK, EncodeRecordsMineAck, DecodeRecordsMineAck);
	SET_ENCODER_DECODER(PROTO_MS_DELEGATE_MINE_ACK, EncodeDelegateMineAck, DecodeDelegateMineAck);
	SET_ENCODER_DECODER(PROTO_MS_DELEGATE_SELL_LIST_ACK, EncodeDelegateSellListAck, DecodeDelegateSellListAck);
	SET_ENCODER_DECODER(PROTO_MS_DELEGATE_BUY_LIST_ACK, EncodeDelegateBuyListAck, DecodeDelegateBuyListAck);
	SET_ENCODER_DECODER(PROTO_MS_RECORDS_CANCEL_REQ, EncodeRecordsCancelReq, DecodeRecordsCancelReq);
	SET_ENCODER_DECODER(PROTO_MS_DELEGATE_CANCEL_REQ, EncodeDelegateCancelReq, DecodeDelegateCancelReq);
	SET_ENCODER_DECODER(PROTO_MS_DELEGATE_SELL_CMD, EncodeDelegateSellCmd, DecodeDelegateSellCmd);
	SET_ENCODER_DECODER(PROTO_MS_DELEGATE_BUY_CMD, EncodeDelegateBuyCmd, DecodeDelegateBuyCmd);
	SET_ENCODER_DECODER(PROTO_MS_MARKET_SELL_CMD, EncodeMarketSellCmd, DecodeMarketSellCmd);
	SET_ENCODER_DECODER(PROTO_MS_MARKET_BUY_CMD, EncodeMarketBuyCmd, DecodeMarketBuyCmd);
	SET_ENCODER_DECODER(PROTO_MS_GET_MAIL_ATTACHMENT_REQ, EncodeGetMailAttachmentReq, DecodeGetMailAttachmentReq);
    SET_ENCODER_DECODER(PROTO_MS_SKILL_STATUS_NTF, EncodeSkillStatusNtf, DecodeSkillStatusNtf);
	SET_ENCODER_DECODER(PROTO_MS_ROLE_DYN_ATTR_NTF, EnCodeRoleDynAttrsNtf, DeCodeRoleDynAttrsNtf);
	SET_ENCODER_DECODER(PROTO_MS_ROLE_CUST_VAR_NTF, EnCodeRoleCustVarNtf, DeCodeRoleCustVarNtf);
	SET_ENCODER_DECODER(PROTO_MS_AUCTION_ADD_ITEM_INFO, EncodeAddAuctionItemInfo, DecodeAddAuctionItemInfo);
	SET_ENCODER_DECODER(PROTO_MS_AUCTION_GET_FINISH_INFO_REQ, EncodeAuctionGetFinishedInfoReq, DecodeAuctionGetFinishedInfoReq);
	SET_ENCODER_DECODER(PROTO_MS_AUCTION_HOUSE_REQ, EncodeGetAuctionHosueReq, DecodeGetAuctionHosueReq);
    SET_ENCODER_DECODER(PROTO_MS_SHABAK_OWNER_NTF, EncodeShabakOwnerNtf, DecodeShabakOwnerNtf);
    SET_ENCODER_DECODER(PROTO_MS_SHABAK_LOSS_NTF, EncodeShabakLossNtf, DecodeShabakLossNtf);
    SET_ENCODER_DECODER(PROTO_MS_SHABAK_ENGAGE_NTF, EncodeShabakEngageNtf, DecodeShabakEngageNtf);
    SET_ENCODER_DECODER(PROTO_MS_SHABAK_END_NTF, EncodeShabakEndNtf, DecodeShabakEndNtf);
	SET_ENCODER_DECODER(PROTO_MS_FAMILY_WAR_NTF, EncodeRunningFamilyWarNtf, DecodeRunningFamilyWarNtf);
	SET_ENCODER_DECODER(PROTO_MS_GET_CONSTANT_CFG_REQ, EncodeGetConstantCfgReq, DecodeGetConstantCfgReq);
	SET_ENCODER_DECODER(PROTO_MS_SET_SERVER_STATUS, EncodeSetServerStatus, DecodeSetServerStatus);
	SET_ENCODER_DECODER(PROTO_MS_MALL_LIMIT_INFO_UPDATE, EncodeMallLimitInfoUpdate, DecodeMallLimitInfoUpdate);
	SET_ENCODER_DECODER(PROTO_MS_MALL_LIMIT_INFO_REQ, EncodeMallLimitInfoReq, DecodeMallLimitInfoReq);
	SET_ENCODER_DECODER(PROTO_MS_MONSTER_PURSURE_ATTACKING_NTF, EncodeMonsterPursureAttackingNtf, DecodeMonsterPursureAttackingNtf);
	SET_ENCODER_DECODER(PROTO_MS_DELETE_MALL_REMAINED_DATA, EncodeDeleteMallRemainedData, DecodeDeleteMallRemainedData);
	SET_ENCODER_DECODER(PROTO_MS_ADD_LOGIN_IP_TYPE, EncodeSetLoginIpType, DecodeSetLoginIpType); 
	SET_ENCODER_DECODER(PROTO_MS_DEL_LOGIN_IP_TYPE, EncodeDelLoginIpType, DecodeDelLoginIpType);
	SET_ENCODER_DECODER(PROTO_MS_UPDATE_SUPPORT_PLAYER, EncodeUpdateSupportPlayer, DecodeUpdateSupportPlayer);
	SET_ENCODER_DECODER(PROTO_MS_ADD_LOCK_PLAYER, EncodeAddLockPlayer, DecodeAddLockPlayer);
	SET_ENCODER_DECODER(PROTO_MS_DEL_LOCK_PLAYER, EncodeDelLockPlayer, DecodeDelLockPlayer);
	SET_ENCODER_DECODER(PROTO_MS_ADD_LOCK_ROLE, EncodeAddLockRole, DecodeAddLockRole);
	SET_ENCODER_DECODER(PROTO_MS_DEL_LOCK_ROLE, EncodeDelLockRole, DecodeDelLockRole);
	SET_ENCODER_DECODER(PROTO_MS_GET_PROHIBIT_CHAT_INFO_REQ, EncodeGetProhibitChatInfoReq, DecodeGetProhibitChatInfoReq);
	SET_ENCODER_DECODER(PROTO_MS_DEL_PROHIBIT_INFO, EncodeDelProhibitInfo, DecodeDelProhibitInfo);
	SET_ENCODER_DECODER(PROTO_MS_ADD_PROHIBIT_CHAT_INTO, EncodeAddProhibitChatInfo, DecodeAddProhibitChatInfo);
    SET_ENCODER_DECODER(PROTO_MS_SKILL_CD_CHANGED_NTF, EncodeSkillCDChangedNtf, DecodeSkillCDChangedNtf);
    SET_ENCODER_DECODER(PROTO_MS_SKILL_PROP_PERMANENT_CHANGED_NTF, EncodeSkillPropPermanentChangedNtf, DecodeSkillPropPermanentChangedNtf);
    SET_ENCODER_DECODER(PROTO_MS_GET_WANTED_LIST_REQ, EncodeGetWantedListReq, DecodeGetWantedListReq);
    SET_ENCODER_DECODER(PROTO_MS_GET_WANTED_LIST_ACK, EncodeGetWantedListAck, DecodeGetWantedListAck);
    SET_ENCODER_DECODER(PROTO_MS_POST_BOUNTY_REQ, EncodePostBountyReq, DecodePostBountyReq);
    SET_ENCODER_DECODER(PROTO_MS_POST_BOUNTY_ACK, EncodePostBountyAck, DecodePostBountyAck);
    SET_ENCODER_DECODER(PROTO_MS_CHECK_ROLE_EXISTENCE_REQ, EncodeCheckRoleExistenceReq, DecodeCheckRoleExistenceReq);
    SET_ENCODER_DECODER(PROTO_MS_CHECK_ROLE_EXISTENCE_ACK, EncodeCheckRoleExistenceAck, DecodeCheckRoleExistenceAck);
	SET_ENCODER_DECODER(PROTO_MS_ROLE_INFO_CHANGE_NTF, EnCodeRoleInfoChangeNtf, DeCodeRoleInfoChangeNtf);
	SET_ENCODER_DECODER(PROTO_MS_SKILL_PROFICIENCY_NTF, EncodeSkillProficiencyNtf, DecodeSkillProficiencyNtf);
    SET_ENCODER_DECODER(PROTO_MS_ITEM_PICKUP_NTF, EncodeItemPickupNtf, DecodeItemPickupNtf);
    SET_ENCODER_DECODER(PROTO_MS_AUTO_PICKUP_SETTINGS_NTF, EncodeAutoPickupSettingsNtf, DecodeAutoPickupSettingsNtf);
    SET_ENCODER_DECODER(PROTO_MS_START_DIG_ACK, EncodeStartDigAck, DecodeStartDigAck);
    SET_ENCODER_DECODER(PROTO_MS_STOP_DIG_NTF, EncodeStopDigNtf, DecodeStopDigNtf);
    SET_ENCODER_DECODER(PROTO_MS_ROLE_APPEAR_NTF, EncodeRoleAppearNtf, DecodeRoleAppearNtf);
    SET_ENCODER_DECODER(PROTO_MS_SAVE_GOODS_ISSUE_RECORD, EncodeSaveIssueRecord, DecodeSaveIssueRecord);
    SET_ENCODER_DECODER(PROTO_MS_VERIFY_BUY_ITEM_INFO_ACK, EncodeVerifyBuyItemInfoAck, DecodeVerifyBuyItemInfoAck);
    SET_ENCODER_DECODER(PROTO_MS_GOODS_ISSUED_NTF, EncodeGoodsIssuedNtf, DecodeGoodsIssuedNtf);
	SET_ENCODER_DECODER(PROTO_MS_REBATE_MONDY_USED_NTF, EncodeRebateMoneyUsedNtf, DecodeRebateMoneyUsedNtf);
	SET_ENCODER_DECODER(PROTO_MS_PLAYER_SET_NAME_REQ, EncodePlayerSetNameReq, DecodePlayerSetNameReq);
	SET_ENCODER_DECODER(PROTO_MS_ITEM_TIP, EncodeItemTip, DecodeItemTip);
	SET_ENCODER_DECODER(PROTO_MS_MONITOR_CHAT_MSG, EncodeMonitorChatMsg, DecodeMonitorChatMsg);
	SET_ENCODER_DECODER(PROTO_MS_ADD_TITLE, EncodeAddTitle, DecodeAddTitle);
	SET_ENCODER_DECODER(PROTO_MS_DEL_TITLE, EncodeDelTitle, DecodeDelTitle);
	SET_ENCODER_DECODER(PROTO_MS_TITLE_WEAR_TYPE, EncodeTitleWearType, DecodeTitleWearType);
	SET_ENCODER_DECODER(PROTO_MS_SYNC_TITLE_INFO, EncodeSyncTitleInfo, DecodeSyncTitleInfo);
	SET_ENCODER_DECODER(PROTO_MS_MONSTER_BACK_NTF, EncodeMonsterBackNtf, DecodeMonsterBackNtf);
    SET_ENCODER_DECODER(PROTO_MS_SET_AUTO_MODE_REQ, EncodeSetAutoModeReq, DecodeSetAutoModeReq);
	SET_ENCODER_DECODER(PROTO_MS_PLAYER_ACTIVATION_CODE, EncodePlayerActivationCode, DecodePlayerActivationCode);
    SET_ENCODER_DECODER(PROTO_MS_SCENE_ITEM_UPDATE_NTF, EncodeSceneItemUpdateNtf, DecodeSceneItemUpdateNtf);
	SET_ENCODER_DECODER(PROTO_MS_ADD_PLAYER_PROHIBIT_CHAT, EncodeAddPlayerProhibitChat, DecodeAddPlayerProhibitChat);
	SET_ENCODER_DECODER(PROTO_MS_DEL_PLAYER_PROHIBIT_CHAT, EncodeDelPlayerProhibitChat, DecodeDelPlayerProhibitChat);
    SET_ENCODER_DECODER(PROTO_MS_RUNGMCMD, EncodeRunGMCmd, DecodeRunGMCmd);
	SET_ENCODER_DECODER(PROTO_MS_CUSTOM_HTTP, EncodeRunCustomHttp, DecodeRunCustomHttp);
	SET_ENCODER_DECODER(PROTO_MS_DEL_ROLE_ACK, EncodeDelRole, DecodeDelRole);
	SET_ENCODER_DECODER(PROTO_MS_SYNC_CUST_LIST, EncodeSyncCustList, DecodeSyncCustList);
	SET_ENCODER_DECODER(PROTO_MS_GET_CUST_LIST_REQ, EncodeGetCustListReq, DecodeGetCustListReq);
	SET_ENCODER_DECODER(PROTO_MS_SEND_GOODS_POST_RECORD_TO_CLIENT, EncodeSendGoodsPostRecordToClient, DecodeSendGoodsPostRecordToClient);
	SET_ENCODER_DECODER(PROTO_MS_SYNC_GOODS_POST_RECORD, EncodeSyncGoodsPostRecord, DecodeSyncGoodsPostRecord);
	SET_ENCODER_DECODER(PROTO_MS_UPDATE_CONSTANT_CFG_REQ, EncodeUpdateConstantCfgReq, DecodeUpdateConstantCfgReq);
	SET_ENCODER_DECODER(PROTO_MS_SET_PLAYER_GENDER, EncodeSetPlayerGender, DecodeSetPlayerGender);
	SET_ENCODER_DECODER(PROTO_MS_EFFECT_APPEAR_NTF, EncodeEffectAppearNtf, DecodeEffectAppearNtf);
	SET_ENCODER_DECODER(PROTO_MS_EFFECT_DISAPPEAR_NTF, EncodeEffectDisAppearNtf, DecodeEffectDisAppearNtf);
}

ProtoMS::~ProtoMS()
{

}

int ProtoMS::BuildProtocol(void* pHost, char* pNet, int iNetSize)
{
	unsigned short moduleid = *(unsigned short*)pHost;
	unsigned short protoid = *(unsigned short*)((char*)pHost + sizeof(unsigned short));
	if (moduleid != GetModuleID()) {
		return -1;
	}
	if (protoid >= PROTO_MS_MAX) {
		return -1;
	}

	CNetData m_oData;
	m_oData.Prepare(pNet, iNetSize);
	return m_EnCodeFuncArray[protoid](pHost, &m_oData);
}

int ProtoMS::HandleProtocol(void* pNet, char* pHost, int iNetSize)
{
	unsigned short moduleid = *(unsigned short*)pNet;
	unsigned short protoid = *(unsigned short*)((char*)pNet + sizeof(unsigned short));
	if (moduleid != GetModuleID()) {
		return -1;
	}
	if (protoid >= PROTO_MS_MAX) {
		return -1;
	}

	CNetData m_oData;
	m_oData.Prepare((char*)pNet, iNetSize);
	return m_DeCodeFuncArray[protoid](pHost, &m_oData);
}
