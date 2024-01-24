#include "stdafx.h"
#include "DataInfo.hpp"
#include "ProtoLog.h"
#include "ProtoDef.h"

int EncodeMALL_ITEM_INFO_BASE(void* pHost, CNetData* poNetData)
{
	MALL_ITEM_INFO_BASE* pstIn = (MALL_ITEM_INFO_BASE*)pHost;

	if (-1 == poNetData->AddQword(pstIn->playerguid))
		return -1;
	if (-1 == poNetData->AddDword(pstIn->item_idx))
		return -1;
	if (-1 == poNetData->AddDword(pstIn->num))
		return -1;
	return poNetData->GetDataLen();
}

int DecodeMALL_ITEM_INFO_BASE(void* pHost, CNetData* poNetData)
{
	MALL_ITEM_INFO_BASE* pstOut = (MALL_ITEM_INFO_BASE*)pHost;

	if (-1 == poNetData->DelQword(pstOut->playerguid))
		return -1;
	if (-1 == poNetData->DelDword(pstOut->item_idx))
		return -1;
	if (-1 == poNetData->DelDword(pstOut->num))
		return -1;

	return sizeof(*pstOut);
}

int EnCodeKEY_VALUE_PAIR(void* pHost, CNetData* poNetData)
{
	KEY_VALUE_PAIR* pstIn = (KEY_VALUE_PAIR*)pHost;

	if(-1 == poNetData->AddString(pstIn->key, sizeof(pstIn->key)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->value, sizeof(pstIn->value)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeKEY_VALUE_PAIR(void* pHost, CNetData* poNetData)
{
	KEY_VALUE_PAIR* pstOut = (KEY_VALUE_PAIR*)pHost;

	if(-1 == poNetData->DelString(pstOut->key, sizeof(pstOut->key)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->value, sizeof(pstOut->value)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePARAM_INFO(void* pHost, CNetData* poNetData)
{
	PARAM_INFO* pstIn = (PARAM_INFO*)pHost;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == poNetData->AddString(pstIn->value, sizeof(pstIn->value)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodePARAM_INFO(void* pHost, CNetData* poNetData)
{
	PARAM_INFO* pstOut = (PARAM_INFO*)pHost;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == poNetData->DelString(pstOut->value, sizeof(pstOut->value)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePARAM_INFO2(void* pHost, CNetData* poNetData)
{
	PARAM_INFO2* pstIn = (PARAM_INFO2*)pHost;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->size))
		return -1;

	{
		int iCount = (((1024) < ((int)pstIn->size)) ? (1024) : ((int)pstIn->size));
		if(-1 == poNetData->AddBlob((char*)pstIn->value, iCount*sizeof(char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodePARAM_INFO2(void* pHost, CNetData* poNetData)
{
	PARAM_INFO2* pstOut = (PARAM_INFO2*)pHost;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->size))
		return -1;

	{
		int iCount = (((1024) < ((int)pstOut->size)) ? (1024) : ((int)pstOut->size));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->value, iCount*sizeof(char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeIntData(void* pHost, CNetData* poNetData)
{
	IntData* pstIn = (IntData*)pHost;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->value))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeIntData(void* pHost, CNetData* poNetData)
{
	IntData* pstOut = (IntData*)pHost;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->value))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeStrData(void* pHost, CNetData* poNetData)
{
	StrData* pstIn = (StrData*)pHost;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->value, sizeof(pstIn->value)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeStrData(void* pHost, CNetData* poNetData)
{
	StrData* pstOut = (StrData*)pHost;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->value, sizeof(pstOut->value)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeBlobData(void* pHost, CNetData* poNetData)
{
	BlobData* pstIn = (BlobData*)pHost;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->size))
		return -1;

	{
		int iCount = (((262144) < ((int)pstIn->size)) ? (262144) : ((int)pstIn->size));
		if(-1 == poNetData->AddBlob((char*)pstIn->buf, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeBlobData(void* pHost, CNetData* poNetData)
{
	BlobData* pstOut = (BlobData*)pHost;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->size))
		return -1;

	{
		int iCount = (((262144) < ((int)pstOut->size)) ? (262144) : ((int)pstOut->size));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->buf, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}

int EnCodeITEM_CFG_VAR(void* pHost, CNetData* poNetData)
{
	ITEM_CFG_VAR* pstIn = static_cast<ITEM_CFG_VAR*>(pHost);

	if (-1 == poNetData->AddDword(pstIn->color))
		return -1;
	if (-1 == poNetData->AddQword(pstIn->icon))
		return -1;
	if (-1 == poNetData->AddDword(pstIn->quality))
		return -1;
	if (-1 == poNetData->AddDword(pstIn->subtype))
		return -1;
	return sizeof(*pstIn);
}

int DeCodeITEM_CFG_VAR(void* pHost, CNetData* poNetData)
{
	ITEM_CFG_VAR* pstOut = static_cast<ITEM_CFG_VAR*>(pHost);

	if (-1 == poNetData->DelDword(pstOut->color))
		return -1;
	if (-1 == poNetData->DelQword(pstOut->icon))
		return -1;
	if (-1 == poNetData->DelDword(pstOut->quality))
		return -1;
	if (-1 == poNetData->DelDword(pstOut->subtype))
		return -1;
	return sizeof(*pstOut);
}

int EnCodeROLE_DATA_INFO(void* pHost, CNetData* poNetData)
{
	ROLE_DATA_INFO* pstIn = (ROLE_DATA_INFO*)pHost;

	if(-1 == poNetData->AddInt(pstIn->intdatanum))
		return -1;

	for(int i = 0; i < 128; i++)
	{
		if(i >= (int)pstIn->intdatanum)
			break;
		if(-1 == EnCodeIntData(&pstIn->roleintdata[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddInt(pstIn->strdatanum))
		return -1;

	for(int i = 0; i < 64; i++)
	{
		if(i >= (int)pstIn->strdatanum)
			break;
		if(-1 == EnCodeStrData(&pstIn->rolestrdata[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddInt(pstIn->blobdatanum))
		return -1;

	for(int i = 0; i < 16; i++)
	{
		if(i >= (int)pstIn->blobdatanum)
			break;
		if(-1 == EnCodeBlobData(&pstIn->roleblobdata[i], poNetData))
			return -1;
	}

	if(-1 == EnCodeBlobData(&pstIn->gamedata, poNetData))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->billinyuanbao))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->billoutyuanbao))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->gameinyuanbao))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->gameoutyuanbao))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeROLE_DATA_INFO(void* pHost, CNetData* poNetData)
{
	ROLE_DATA_INFO* pstOut = (ROLE_DATA_INFO*)pHost;

	if(-1 == poNetData->DelInt(pstOut->intdatanum))
		return -1;

	for(int i = 0; i < 128; i++)
	{
		if(i >= (int)pstOut->intdatanum)
			break;
		if(-1 == DeCodeIntData(&pstOut->roleintdata[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelInt(pstOut->strdatanum))
		return -1;

	for(int i = 0; i < 64; i++)
	{
		if(i >= (int)pstOut->strdatanum)
			break;
		if(-1 == DeCodeStrData(&pstOut->rolestrdata[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelInt(pstOut->blobdatanum))
		return -1;

	for(int i = 0; i < 16; i++)
	{
		if(i >= (int)pstOut->blobdatanum)
			break;
		if(-1 == DeCodeBlobData(&pstOut->roleblobdata[i], poNetData))
			return -1;
	}

	if(-1 == DeCodeBlobData(&pstOut->gamedata, poNetData))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->billinyuanbao))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->billoutyuanbao))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->gameinyuanbao))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->gameoutyuanbao))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeCUSTOM_INFO(void* pHost, CNetData* poNetData)
{
	CUSTOM_INFO* pstIn = (CUSTOM_INFO*)pHost;

	if(-1 == poNetData->AddWord(pstIn->num))
		return -1;

	if (-1 == poNetData->AddWord(pstIn->idx))
		return -1;
	{
		int iCount = (((65536) < ((int)pstIn->num)) ? (65536) : ((int)pstIn->num));
		if(-1 == poNetData->AddBlob((char*)pstIn->buf, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeCUSTOM_INFO(void* pHost, CNetData* poNetData)
{
	CUSTOM_INFO* pstOut = (CUSTOM_INFO*)pHost;

	if(-1 == poNetData->DelWord(pstOut->num))
		return -1;

	if (-1 == poNetData->DelWord(pstOut->idx))
		return -1;
	{
		int iCount = (((65536) < ((int)pstOut->num)) ? (65536) : ((int)pstOut->num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->buf, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeITEM_DB_INFO(void* pHost, CNetData* poNetData)
{
	ITEM_DB_INFO* pstIn = (ITEM_DB_INFO*)pHost;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->role))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->site))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->amount))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->durability))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->max_durability))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->use_count))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->is_bound))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->life))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->ext_len))
		return -1;
	{
		int iCount = (((128) < ((int)pstIn->ext_len)) ? (128) : ((int)pstIn->ext_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->ext_data, iCount*sizeof(unsigned char)))
			return -1;
	}

	if (-1 == EnCodeITEM_CFG_VAR(&pstIn->item_cfg_var, poNetData))
		return -1;
	return poNetData->GetDataLen();
}
int DeCodeITEM_DB_INFO(void* pHost, CNetData* poNetData)
{
	ITEM_DB_INFO* pstOut = (ITEM_DB_INFO*)pHost;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->role))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->site))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->amount))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->durability))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->max_durability))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->use_count))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->is_bound))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->life))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->ext_len))
		return -1;

	{
		int iCount = (((128) < ((int)pstOut->ext_len)) ? (128) : ((int)pstOut->ext_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->ext_data, iCount*sizeof(unsigned char)))
			return -1;
	}

	if (-1 == DeCodeITEM_CFG_VAR(&pstOut->item_cfg_var, poNetData))
		return -1;
	return sizeof(*pstOut);
}

int EnCodeITEM_INFO(void* pHost, CNetData* poNetData)
{
	ITEM_INFO* pstIn = (ITEM_INFO*)pHost;

	if(-1 == EnCodeITEM_DB_INFO(&pstIn->base_info, poNetData))
		return -1;

	if(-1 == EnCodeCUSTOM_INFO(&pstIn->custom, poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeITEM_INFO(void* pHost, CNetData* poNetData)
{
	ITEM_INFO* pstOut = (ITEM_INFO*)pHost;

	if (-1 == DeCodeITEM_DB_INFO(&pstOut->base_info, poNetData))
		return -1;

	if(-1 == DeCodeCUSTOM_INFO(&pstOut->custom, poNetData))
		return -1;

	return sizeof(*pstOut);
}

int EnCodeLOGTRADE_DATA(void* pHost, CNetData* poNetData)
{
	LogTradeData* pstIn = (LogTradeData*)pHost;

	if (-1 == poNetData->AddQword(pstIn->tradeId))
		return -1;
	if (-1 == poNetData->AddWord(pstIn->tradeType))
		return -1;
	if (-1 == poNetData->AddWord(pstIn->valueType))
		return -1;
	if (-1 == poNetData->AddQword(pstIn->itemGuid))
		return -1;
	if (-1 == poNetData->AddDword(pstIn->itemId))
		return -1;
	if (-1 == poNetData->AddDword(pstIn->itemValue))
		return -1;
	if (-1 == poNetData->AddDword(pstIn->itemNum))
		return -1;
	if (-1 == poNetData->AddQword(pstIn->buyerGuid))
		return -1;
	if (-1 == poNetData->AddQword(pstIn->sellerGuid))
		return -1;
	if (-1 == poNetData->AddQword(pstIn->timestamp))
		return -1;
	if (-1 == poNetData->AddWord(pstIn->descLength))
		return -1;
	if (-1 == poNetData->AddBlob((char*)pstIn->desc, pstIn->descLength))
		return -1;
	//客户端用不到暂时不加
	//if (-1 == poNetData->AddQword(pstIn->orgItemGuid))
	//	return -1;
	//if (-1 == poNetData->AddQword(pstIn->tradeTimestamp))
	//	return -1;

	return poNetData->GetDataLen();
}
int DeCodeLOGTRADE_DATA(void* pHost, CNetData* poNetData)
{
	LogTradeData* pstOut = (LogTradeData*)pHost;

	if (-1 == poNetData->DelQword(pstOut->tradeId))
		return -1;
	if (-1 == poNetData->DelWord(pstOut->tradeType))
		return -1;
	if (-1 == poNetData->DelWord(pstOut->valueType))
		return -1;
	if (-1 == poNetData->DelQword(pstOut->itemGuid))
		return -1;
	if (-1 == poNetData->DelDword(pstOut->itemId))
		return -1;
	if (-1 == poNetData->DelDword(pstOut->itemValue))
		return -1;
	if (-1 == poNetData->DelDword(pstOut->itemNum))
		return -1;
	if (-1 == poNetData->DelQword(pstOut->buyerGuid))
		return -1;
	if (-1 == poNetData->DelQword(pstOut->sellerGuid))
		return -1;
	if (-1 == poNetData->DelQword(pstOut->timestamp))
		return -1;
	if (-1 == poNetData->DelWord(pstOut->descLength))
		return -1;
	if (-1 == poNetData->DelBlob((char*)pstOut->desc, pstOut->descLength))
		return -1;
	//客户端用不到暂时不加
	//if (-1 == poNetData->DelQword(pstOut->orgItemGuid))
	//	return -1;
	//if (-1 == poNetData->DelQword(pstOut->tradeTimestamp))
	//	return -1;

	return sizeof(*pstOut);
}

int EnCodeCHAT_MSG(void* pHost, CNetData* poNetData)
{
	CHAT_MSG* pstIn = (CHAT_MSG*)pHost;

	if(-1 == poNetData->AddString(pstIn->role_name, sizeof(pstIn->role_name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->message, sizeof(pstIn->message)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeCHAT_MSG(void* pHost, CNetData* poNetData)
{
	CHAT_MSG* pstOut = (CHAT_MSG*)pHost;

	if(-1 == poNetData->DelString(pstOut->role_name, sizeof(pstOut->role_name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->message, sizeof(pstOut->message)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSKILL_INFO(void* pHost, CNetData* poNetData)
{
	SKILL_INFO* pstIn = (SKILL_INFO*)pHost;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->active))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->proficiency))
		return -1;

	if(-1 == poNetData->AddString(pstIn->cfg, _countof(pstIn->cfg)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSKILL_INFO(void* pHost, CNetData* poNetData)
{
	SKILL_INFO* pstOut = (SKILL_INFO*)pHost;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->active))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->proficiency))
		return -1;

	if(-1 == poNetData->DelString(pstOut->cfg, _countof(pstOut->cfg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeBUFF_INFO(void* pHost, CNetData* poNetData)
{
	BUFF_INFO* pstIn = (BUFF_INFO*)pHost;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->stack))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->life))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->host))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeBUFF_INFO(void* pHost, CNetData* poNetData)
{
	BUFF_INFO* pstOut = (BUFF_INFO*)pHost;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->stack))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->life))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->host))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeBUFF_INFO_DB(void* pHost, CNetData* poNetData)
{
    BUFF_INFO_DB* pstIn = (BUFF_INFO_DB*)pHost;

    if(-1 == poNetData->AddQword(pstIn->index))
        return -1;

    if(-1 == poNetData->AddWord(pstIn->buffid))
        return -1;

    if(-1 == poNetData->AddDword(pstIn->timeleft))
        return -1;

    if(-1 == poNetData->AddQword(pstIn->timestamp))
        return -1;

    if(-1 == poNetData->AddQword(pstIn->actor_id))
        return -1;

    if(-1 == poNetData->AddString(pstIn->actor_name, _countof(pstIn->actor_name)))
        return -1;

    if(-1 == poNetData->AddByte(pstIn->actor_job))
        return -1;

    if(-1 == poNetData->AddDword(pstIn->actor_level))
        return -1;

    if(-1 == poNetData->AddWord(pstIn->actor_skill))
        return -1;

	if (-1 == poNetData->AddWord(pstIn->stack))
		return -1;

	if (-1 == poNetData->AddString(pstIn->attr, _countof(pstIn->attr)))
		return -1;

    return poNetData->GetDataLen();
}
int DeCodeBUFF_INFO_DB(void* pHost, CNetData* poNetData)
{
    BUFF_INFO_DB* pstOut = (BUFF_INFO_DB*)pHost;

    if(-1 == poNetData->DelQword(pstOut->index))
        return -1;

    if(-1 == poNetData->DelWord(pstOut->buffid))
        return -1;

    if(-1 == poNetData->DelDword(pstOut->timeleft))
        return -1;

    if(-1 == poNetData->DelQword(pstOut->timestamp))
        return -1;

    if(-1 == poNetData->DelQword(pstOut->actor_id))
        return -1;

    if(-1 == poNetData->DelString(pstOut->actor_name, _countof(pstOut->actor_name)))
        return -1;

    if(-1 == poNetData->DelByte(pstOut->actor_job))
        return -1;

    if(-1 == poNetData->DelDword(pstOut->actor_level))
        return -1;

    if(-1 == poNetData->DelWord(pstOut->actor_skill))
        return -1;

	if (-1 == poNetData->DelWord(pstOut->stack))
		return -1;

	if (-1 == poNetData->DelString(pstOut->attr, _countof(pstOut->attr)))
		return -1;

    return sizeof(*pstOut);
}
int EnCodeSHOP_ITEM_INFO(void* pHost, CNetData* poNetData)
{
	SHOP_ITEM_INFO* pstIn = (SHOP_ITEM_INFO*)pHost;

	if(-1 == poNetData->AddByte(pstIn->index))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->num))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->value))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSHOP_ITEM_INFO(void* pHost, CNetData* poNetData)
{
	SHOP_ITEM_INFO* pstOut = (SHOP_ITEM_INFO*)pHost;

	if(-1 == poNetData->DelByte(pstOut->index))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->num))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->value))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTEAM_MEMBER(void* pHost, CNetData* poNetData)
{
	TEAM_MEMBER* pstIn = (TEAM_MEMBER*)pHost;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->head))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->is_online))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->level))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->job))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->gender))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->map_code))
		return -1;

	if(-1 == poNetData->AddString(pstIn->map_name, sizeof(pstIn->map_name)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->y))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTEAM_MEMBER(void* pHost, CNetData* poNetData)
{
	TEAM_MEMBER* pstOut = (TEAM_MEMBER*)pHost;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->head))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->is_online))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->level))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->job))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->gender))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->map_code))
		return -1;

	if(-1 == poNetData->DelString(pstOut->map_name, sizeof(pstOut->map_name)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->y))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTEAM_INFO(void* pHost, CNetData* poNetData)
{
	TEAM_INFO* pstIn = (TEAM_INFO*)pHost;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->leader_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->leader_name, sizeof(pstIn->leader_name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->permission))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->member_num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstIn->member_num)
			break;
		if(-1 == EnCodeTEAM_MEMBER(&pstIn->members[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeTEAM_INFO(void* pHost, CNetData* poNetData)
{
	TEAM_INFO* pstOut = (TEAM_INFO*)pHost;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->leader_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->leader_name, sizeof(pstOut->leader_name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->permission))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->member_num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstOut->member_num)
			break;
		if(-1 == DeCodeTEAM_MEMBER(&pstOut->members[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeFRIEND_INFO(void* pHost, CNetData* poNetData)
{
	FRIEND_INFO* pstIn = (FRIEND_INFO*)pHost;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->is_online))
		return -1;

	if(-1 == poNetData->AddShort(pstIn->friendship))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeFRIEND_INFO(void* pHost, CNetData* poNetData)
{
	FRIEND_INFO* pstOut = (FRIEND_INFO*)pHost;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->is_online))
		return -1;

	if(-1 == poNetData->DelShort(pstOut->friendship))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeFRIEND_DETAIL(void* pHost, CNetData* poNetData)
{
	FRIEND_DETAIL* pstIn = (FRIEND_DETAIL*)pHost;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->family, sizeof(pstIn->family)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->title, sizeof(pstIn->title)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->position, sizeof(pstIn->position)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->head))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->job))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->gender))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->level))
		return -1;

	if(-1 == poNetData->AddShort(pstIn->friendship))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->is_in_team))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->members_num))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->is_online))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeFRIEND_DETAIL(void* pHost, CNetData* poNetData)
{
	FRIEND_DETAIL* pstOut = (FRIEND_DETAIL*)pHost;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->family, sizeof(pstOut->family)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->title, sizeof(pstOut->title)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->position, sizeof(pstOut->position)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->head))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->job))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->gender))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->level))
		return -1;

	if(-1 == poNetData->DelShort(pstOut->friendship))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->is_in_team))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->members_num))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->is_online))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeFRIEND_LIST(void* pHost, CNetData* poNetData)
{
	FRIEND_LIST* pstIn = (FRIEND_LIST*)pHost;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->friend_num))
		return -1;

	for(int i = 0; i < MAX_FRIEND_NUM; i++)
	{
		if(i >= (int)pstIn->friend_num)
			break;
		if(-1 == EnCodeFRIEND_INFO(&pstIn->friends[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeFRIEND_LIST(void* pHost, CNetData* poNetData)
{
	FRIEND_LIST* pstOut = (FRIEND_LIST*)pHost;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->friend_num))
		return -1;

	for(int i = 0; i < MAX_FRIEND_NUM; i++)
	{
		if(i >= (int)pstOut->friend_num)
			break;
		if(-1 == DeCodeFRIEND_INFO(&pstOut->friends[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeFRIEND_RELATION(void* pHost, CNetData* poNetData)
{
	FRIEND_RELATION* pstIn = (FRIEND_RELATION*)pHost;

	if(-1 == poNetData->AddQword(pstIn->role1_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->role1_name, sizeof(pstIn->role1_name)))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->role2_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->role2_name, sizeof(pstIn->role2_name)))
		return -1;

	if(-1 == poNetData->AddShort(pstIn->friendship))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeFRIEND_RELATION(void* pHost, CNetData* poNetData)
{
	FRIEND_RELATION* pstOut = (FRIEND_RELATION*)pHost;

	if(-1 == poNetData->DelQword(pstOut->role1_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->role1_name, sizeof(pstOut->role1_name)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->role2_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->role2_name, sizeof(pstOut->role2_name)))
		return -1;

	if(-1 == poNetData->DelShort(pstOut->friendship))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSERVANT_INFO(void* pHost, CNetData* poNetData)
{
	SERVANT_INFO* pstIn = (SERVANT_INFO*)pHost;

	if(-1 == poNetData->AddQword(pstIn->servant_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->monster_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->level))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->max_level))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->kill_count))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->hp))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->gen_tick))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->buff_data_len))
		return -1;

	{
		int iCount = (((1024) < ((int)pstIn->buff_data_len)) ? (1024) : ((int)pstIn->buff_data_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->buff_data, iCount*sizeof(char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeSERVANT_INFO(void* pHost, CNetData* poNetData)
{
	SERVANT_INFO* pstOut = (SERVANT_INFO*)pHost;

	if(-1 == poNetData->DelQword(pstOut->servant_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->monster_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->level))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->max_level))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->kill_count))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->hp))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->gen_tick))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->buff_data_len))
		return -1;

	{
		int iCount = (((1024) < ((int)pstOut->buff_data_len)) ? (1024) : ((int)pstOut->buff_data_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->buff_data, iCount*sizeof(char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeQUICK_BAR_INFO(void* pHost, CNetData* poNetData)
{
	QUICK_BAR_INFO* pstIn = static_cast<QUICK_BAR_INFO*>(pHost);

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->slot))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQUICK_BAR_INFO(void* pHost, CNetData* poNetData)
{
	QUICK_BAR_INFO* pstOut = static_cast<QUICK_BAR_INFO*>(pHost);

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->slot))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMAP_REGION_INFO(void* pHost, CNetData* poNetData)
{
	MAP_REGION_INFO* pstIn = (MAP_REGION_INFO*)pHost;

	if(-1 == poNetData->AddByte(pstIn->rg_type))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->min_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->max_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->min_y))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->max_y))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMAP_REGION_INFO(void* pHost, CNetData* poNetData)
{
	MAP_REGION_INFO* pstOut = (MAP_REGION_INFO*)pHost;

	if(-1 == poNetData->DelByte(pstOut->rg_type))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->min_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->max_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->min_y))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->max_y))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeFAMILY_TITLE(void* pHost, CNetData* poNetData)
{
	FAMILY_TITLE* pstIn = (FAMILY_TITLE*)pHost;

	if(-1 == poNetData->AddByte(pstIn->id))
		return -1;

	if(-1 == poNetData->AddString(pstIn->title, sizeof(pstIn->title)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeFAMILY_TITLE(void* pHost, CNetData* poNetData)
{
	FAMILY_TITLE* pstOut = (FAMILY_TITLE*)pHost;

	if(-1 == poNetData->DelByte(pstOut->id))
		return -1;

	if(-1 == poNetData->DelString(pstOut->title, sizeof(pstOut->title)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeFAMILY_DETAIL(void* pHost, CNetData* poNetData)
{
	FAMILY_DETAIL* pstIn = (FAMILY_DETAIL*)pHost;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->notice_len))
		return -1;

	{
		int iCount = (((1280) < ((int)pstIn->notice_len)) ? (1280) : ((int)pstIn->notice_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->notice, iCount*sizeof(char)))
			return -1;
	}
	if(-1 == poNetData->AddWord(pstIn->titles_num))
		return -1;

	for(int i = 0; i < MAX_TITLE_NUM; i++)
	{
		if(i >= (int)pstIn->titles_num)
			break;
		if(-1 == EnCodeFAMILY_TITLE(&pstIn->titles[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddWord(pstIn->msg_len))
		return -1;

	{
		int iCount = (((12800) < ((int)pstIn->msg_len)) ? (12800) : ((int)pstIn->msg_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->sysmsgs, iCount*sizeof(char)))
			return -1;
	}
	if(-1 == poNetData->AddWord(pstIn->ally_count))
		return -1;

	{
		int iCount = (((MAX_ALLY_NUM) < ((int)pstIn->ally_count)) ? (MAX_ALLY_NUM) : ((int)pstIn->ally_count));
		if(-1 == poNetData->AddBlob((char*)pstIn->allys, iCount*sizeof(uint64_t)))
			return -1;
	}
	if(-1 == poNetData->AddWord(pstIn->enemy_count))
		return -1;

	{
		int iCount = (((MAX_ENEMY_NUM) < ((int)pstIn->enemy_count)) ? (MAX_ENEMY_NUM) : ((int)pstIn->enemy_count));
		if(-1 == poNetData->AddBlob((char*)pstIn->enemys, iCount*sizeof(uint64_t)))
			return -1;
	}
	if(-1 == poNetData->AddDword(pstIn->create_time))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeFAMILY_DETAIL(void* pHost, CNetData* poNetData)
{
	FAMILY_DETAIL* pstOut = (FAMILY_DETAIL*)pHost;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->notice_len))
		return -1;

	{
		int iCount = (((1280) < ((int)pstOut->notice_len)) ? (1280) : ((int)pstOut->notice_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->notice, iCount*sizeof(char)))
			return -1;
	}
	if(-1 == poNetData->DelWord(pstOut->titles_num))
		return -1;

	for(int i = 0; i < MAX_TITLE_NUM; i++)
	{
		if(i >= (int)pstOut->titles_num)
			break;
		if(-1 == DeCodeFAMILY_TITLE(&pstOut->titles[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelWord(pstOut->msg_len))
		return -1;

	{
		int iCount = (((12800) < ((int)pstOut->msg_len)) ? (12800) : ((int)pstOut->msg_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->sysmsgs, iCount*sizeof(char)))
			return -1;
	}
	if(-1 == poNetData->DelWord(pstOut->ally_count))
		return -1;

	{
		int iCount = (((MAX_ALLY_NUM) < ((int)pstOut->ally_count)) ? (MAX_ALLY_NUM) : ((int)pstOut->ally_count));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->allys, iCount*sizeof(uint64_t)))
			return -1;
	}
	if(-1 == poNetData->DelWord(pstOut->enemy_count))
		return -1;

	{
		int iCount = (((MAX_ENEMY_NUM) < ((int)pstOut->enemy_count)) ? (MAX_ENEMY_NUM) : ((int)pstOut->enemy_count));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->enemys, iCount*sizeof(uint64_t)))
			return -1;
	}
	if(-1 == poNetData->DelDword(pstOut->create_time))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeFAMILY_INFO_GS(void* pHost, CNetData* poNetData)
{
	FAMILY_INFO_GS* pstIn = (FAMILY_INFO_GS*)pHost;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->titles_num))
		return -1;

	for(int i = 0; i < MAX_TITLE_NUM; i++)
	{
		if(i >= (int)pstIn->titles_num)
			break;
		if(-1 == EnCodeFAMILY_TITLE(&pstIn->titles[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddWord(pstIn->ally_count))
		return -1;

	{
		int iCount = (((MAX_ALLY_NUM) < ((int)pstIn->ally_count)) ? (MAX_ALLY_NUM) : ((int)pstIn->ally_count));
		if(-1 == poNetData->AddBlob((char*)pstIn->allys, iCount*sizeof(uint64_t)))
			return -1;
	}
	if(-1 == poNetData->AddWord(pstIn->enemy_count))
		return -1;

	{
		int iCount = (((MAX_ENEMY_NUM) < ((int)pstIn->enemy_count)) ? (MAX_ENEMY_NUM) : ((int)pstIn->enemy_count));
		if(-1 == poNetData->AddBlob((char*)pstIn->enemys, iCount*sizeof(uint64_t)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeFAMILY_INFO_GS(void* pHost, CNetData* poNetData)
{
	FAMILY_INFO_GS* pstOut = (FAMILY_INFO_GS*)pHost;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->titles_num))
		return -1;

	for(int i = 0; i < MAX_TITLE_NUM; i++)
	{
		if(i >= (int)pstOut->titles_num)
			break;
		if(-1 == DeCodeFAMILY_TITLE(&pstOut->titles[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelWord(pstOut->ally_count))
		return -1;

	{
		int iCount = (((MAX_ALLY_NUM) < ((int)pstOut->ally_count)) ? (MAX_ALLY_NUM) : ((int)pstOut->ally_count));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->allys, iCount*sizeof(uint64_t)))
			return -1;
	}
	if(-1 == poNetData->DelWord(pstOut->enemy_count))
		return -1;

	{
		int iCount = (((MAX_ENEMY_NUM) < ((int)pstOut->enemy_count)) ? (MAX_ENEMY_NUM) : ((int)pstOut->enemy_count));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->enemys, iCount*sizeof(uint64_t)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeFAMILY_INFO(void* pHost, CNetData* poNetData)
{
	FAMILY_INFO* pstIn = (FAMILY_INFO*)pHost;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeFAMILY_INFO(void* pHost, CNetData* poNetData)
{
	FAMILY_INFO* pstOut = (FAMILY_INFO*)pHost;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMEMBER_INFO(void* pHost, CNetData* poNetData)
{
	MEMBER_INFO* pstIn = (MEMBER_INFO*)pHost;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->player_name, sizeof(pstIn->player_name)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->level))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->job))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->family_guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->title_id))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->join_time))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->login_time))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->is_online))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->cur_ctrb))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->totle_ctrb))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->kills))
		return -1;

    if(-1 == poNetData->AddDword(pstIn->combat_capability))
        return -1;

    if(-1 == poNetData->AddDword(pstIn->reserved1))
        return -1;

    if(-1 == poNetData->AddDword(pstIn->reserved2))
        return -1;

	return poNetData->GetDataLen();
}
int DeCodeMEMBER_INFO(void* pHost, CNetData* poNetData)
{
	MEMBER_INFO* pstOut = (MEMBER_INFO*)pHost;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->player_name, sizeof(pstOut->player_name)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->level))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->job))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->family_guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->title_id))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->join_time))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->login_time))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->is_online))
		return -1;

    if(-1 == poNetData->DelDword(pstOut->cur_ctrb))
        return -1;

    if(-1 == poNetData->DelDword(pstOut->totle_ctrb))
        return -1;

    if(-1 == poNetData->DelDword(pstOut->kills))
        return -1;

    if(-1 == poNetData->DelDword(pstOut->combat_capability))
        return -1;

    if(-1 == poNetData->DelDword(pstOut->reserved1))
        return -1;

    if(-1 == poNetData->DelDword(pstOut->reserved2))
        return -1;

	return sizeof(*pstOut);
}
int EnCodeMEMBER_INFO_GS(void* pHost, CNetData* poNetData)
{
	MEMBER_INFO_GS* pstIn = (MEMBER_INFO_GS*)pHost;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->family_guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->title_id))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->cur_ctrb))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->totle_ctrb))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->join_time))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMEMBER_INFO_GS(void* pHost, CNetData* poNetData)
{
	MEMBER_INFO_GS* pstOut = (MEMBER_INFO_GS*)pHost;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->family_guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->title_id))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->cur_ctrb))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->totle_ctrb))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->join_time))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeAPPLICANTS_INFO(void* pHost, CNetData* poNetData)
{
	APPLICANTS_INFO* pstIn = (APPLICANTS_INFO*)pHost;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->player_name, sizeof(pstIn->player_name)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->level))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->job))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeAPPLICANTS_INFO(void* pHost, CNetData* poNetData)
{
	APPLICANTS_INFO* pstOut = (APPLICANTS_INFO*)pHost;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->player_name, sizeof(pstOut->player_name)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->level))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->job))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeROLE_FORBIDTALK_INFO(void* pHost, CNetData* poNetData)
{
	ROLE_FORBIDTALK_INFO* pstIn = (ROLE_FORBIDTALK_INFO*)pHost;

	if(-1 == poNetData->AddString(pstIn->role_name, sizeof(pstIn->role_name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->end_forbid_time, sizeof(pstIn->end_forbid_time)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->describe, sizeof(pstIn->describe)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeROLE_FORBIDTALK_INFO(void* pHost, CNetData* poNetData)
{
	ROLE_FORBIDTALK_INFO* pstOut = (ROLE_FORBIDTALK_INFO*)pHost;

	if(-1 == poNetData->DelString(pstOut->role_name, sizeof(pstOut->role_name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->end_forbid_time, sizeof(pstOut->end_forbid_time)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->describe, sizeof(pstOut->describe)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeFAMILY_APPLY_INFO(void* pHost, CNetData* poNetData)
{
	FAMILY_APPLY_INFO* pstIn = (FAMILY_APPLY_INFO*)pHost;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->leader_name, sizeof(pstIn->leader_name)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->members_num))
		return -1;

	if(-1 == poNetData->AddString(pstIn->hold_place, sizeof(pstIn->hold_place)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->is_applied))
		return -1;

    if(-1 == poNetData->AddString(pstIn->family_manifesto, sizeof(pstIn->family_manifesto)))
        return -1;

    if(-1 == poNetData->AddQword(pstIn->family_create_time))
        return -1;

    if(-1 == poNetData->AddDword(pstIn->family_level))
        return -1;

    if(-1 == poNetData->AddDword(pstIn->reserved1))
        return -1;

    if(-1 == poNetData->AddDword(pstIn->reserved2))
        return -1;

	return poNetData->GetDataLen();
}
int DeCodeFAMILY_APPLY_INFO(void* pHost, CNetData* poNetData)
{
	FAMILY_APPLY_INFO* pstOut = (FAMILY_APPLY_INFO*)pHost;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->leader_name, sizeof(pstOut->leader_name)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->members_num))
		return -1;

	if(-1 == poNetData->DelString(pstOut->hold_place, sizeof(pstOut->hold_place)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->is_applied))
		return -1;

    if(-1 == poNetData->DelString(pstOut->family_manifesto, sizeof(pstOut->family_manifesto)))
        return -1;

    if(-1 == poNetData->DelQword(pstOut->family_create_time))
        return -1;

    if(-1 == poNetData->DelDword(pstOut->family_level))
        return -1;

    if(-1 == poNetData->DelDword(pstOut->reserved1))
        return -1;

    if(-1 == poNetData->DelDword(pstOut->reserved2))
        return -1;

	return sizeof(*pstOut);
}
int EnCodeFAMILY_WAR_INFO(void* pHost, CNetData* poNetData)
{
	FAMILY_WAR_INFO* pstIn = (FAMILY_WAR_INFO*)pHost;

	//if (-1 == poNetData->AddQword(pstIn->guid))
	//	return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeFAMILY_WAR_INFO(void* pHost, CNetData* poNetData)
{
	FAMILY_WAR_INFO* pstOut = (FAMILY_WAR_INFO*)pHost;

	//if (-1 == poNetData->AddQword(pstOut->guid))
	//	return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeCASTLE_INFO(void* pHost, CNetData* poNetData)
{
	CASTLE_INFO* pstIn = (CASTLE_INFO*)pHost;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->is_start))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->start_time))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->duration))
		return -1;

	if(-1 == poNetData->AddString(pstIn->own_family, sizeof(pstIn->own_family)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->attack_families, sizeof(pstIn->attack_families)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->dst_map, sizeof(pstIn->dst_map)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->basilica_map, sizeof(pstIn->basilica_map)))
		return -1;

	if(-1 == EnCodeCUSTOM_INFO(&pstIn->custom, poNetData))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->state))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeCASTLE_INFO(void* pHost, CNetData* poNetData)
{
	CASTLE_INFO* pstOut = (CASTLE_INFO*)pHost;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->is_start))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->start_time))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->duration))
		return -1;

	if(-1 == poNetData->DelString(pstOut->own_family, sizeof(pstOut->own_family)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->attack_families, sizeof(pstOut->attack_families)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->dst_map, sizeof(pstOut->dst_map)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->basilica_map, sizeof(pstOut->basilica_map)))
		return -1;

	if(-1 == DeCodeCUSTOM_INFO(&pstOut->custom, poNetData))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->state))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeGUILD_INFO(void *pHost, CNetData *poNetData)
{
    const auto *pstIn = static_cast<GUILD_INFO *>(pHost);

    if (poNetData->AddQword(pstIn->id) == -1) return -1;

    if (poNetData->AddString(pstIn->name) == -1) return -1;

    if (poNetData->AddWord(pstIn->level) == -1) return -1;

    if (poNetData->AddString(pstIn->manifesto) == -1) return -1;

    if (poNetData->AddString(pstIn->notice) == -1) return -1;

    if (poNetData->AddQword(pstIn->ctime) == -1) return -1;

    if (poNetData->AddQword(pstIn->creator_id) == -1) return -1;

    if (poNetData->AddString(pstIn->creator_name) == -1) return -1;

    if (poNetData->AddQword(pstIn->chairman_id) == -1) return -1;

    if (poNetData->AddString(pstIn->chairman_name) == -1) return -1;

	if (poNetData->AddDword(pstIn->autojoin_level) == -1) return -1;

    uint16_t nAllyNum = static_cast<uint16_t>(pstIn->allies.size());
    if (poNetData->AddWord(nAllyNum) == -1) return -1;

    for (uint16_t i = 0; i < nAllyNum; ++i)
        if (poNetData->AddQword(pstIn->allies[i]) == -1) return -1;

    uint16_t nEnemyNum = static_cast<uint16_t>(pstIn->enemies.size());
    if (poNetData->AddWord(nEnemyNum) == -1) return -1;

    for (uint16_t i = 0; i < nEnemyNum; ++i)
        if (poNetData->AddQword(pstIn->enemies[i]) == -1) return -1;

    return poNetData->GetDataLen();
}
int DeCodeGUILD_INFO(void *pHost, CNetData *poNetData)
{
    auto nStartPos = poNetData->GetDataLen();

    auto *pstOut = static_cast<GUILD_INFO *>(pHost);

    char buf[1280];

    if (poNetData->DelQword(pstOut->id) == -1) return -1;

    if (poNetData->DelString(buf, _countof(buf)) == -1) return -1;
    pstOut->name = buf;

    if (poNetData->DelWord(pstOut->level) == -1) return -1;

    if (poNetData->DelString(buf, _countof(buf)) == -1) return -1;
    pstOut->manifesto = buf;

    if (poNetData->DelString(buf, _countof(buf)) == -1) return -1;
    pstOut->notice = buf;

    if (poNetData->DelQword(pstOut->ctime) == -1) return -1;

    if (poNetData->DelQword(pstOut->creator_id) == -1) return -1;

    if (poNetData->DelString(buf, _countof(buf)) == -1) return -1;
    pstOut->creator_name = buf;

    if (poNetData->DelQword(pstOut->chairman_id) == -1) return -1;

    if (poNetData->DelString(buf, _countof(buf)) == -1) return -1;
    pstOut->chairman_name = buf;

	if (poNetData->DelDword(pstOut->autojoin_level) == -1) return -1;

    uint16_t nAllyNum = 0;
    if (poNetData->DelWord(nAllyNum) == -1) return -1;

    pstOut->allies.resize(nAllyNum);
    for (uint16_t i = 0; i < nAllyNum; ++i)
        if (poNetData->DelQword(pstOut->allies[i]) == -1) return -1;

    uint16_t nEnemyNum = 0;
    if (poNetData->DelWord(nEnemyNum) == -1) return -1;

    pstOut->enemies.resize(nEnemyNum);
    for (uint16_t i = 0; i < nEnemyNum; ++i)
        if (poNetData->DelQword(pstOut->enemies[i]) == -1) return -1;

    return poNetData->GetDataLen() - nStartPos;
}
int EnCodeGUILD_MEMBER(void *pHost, CNetData *poNetData)
{
    const auto *pstIn = static_cast<GUILD_MEMBER *>(pHost);

    if (poNetData->AddQword(pstIn->player_id) == -1) return -1;

    if (poNetData->AddString(pstIn->player_name) == -1) return -1;

    if (poNetData->AddByte(pstIn->job) == -1) return -1;

    if (poNetData->AddDword(pstIn->level) == -1) return -1;

    if (poNetData->AddQword(pstIn->guild_id) == -1) return -1;

    if (poNetData->AddByte(pstIn->title) == -1) return -1;

    if (poNetData->AddByte(pstIn->new_title) == -1) return -1;

    if (poNetData->AddQword(pstIn->join_time) == -1) return -1;

    if (poNetData->AddQword(pstIn->login_time) == -1) return -1;

    if (poNetData->AddDword(pstIn->cur_contrib) == -1) return -1;

    if (poNetData->AddDword(pstIn->total_contrib) == -1) return -1;

    if (poNetData->AddDword(pstIn->kills) == -1) return -1;

    if (poNetData->AddDword(pstIn->combat_cap) == -1) return -1;

    if (poNetData->AddByte(pstIn->status) == -1) return -1;

    if (poNetData->AddString(pstIn->kicked_by) == -1) return -1;

    return poNetData->GetDataLen();
}
int DeCodeGUILD_MEMBER(void *pHost, CNetData *poNetData)
{
    auto nStartPos = poNetData->GetDataLen();

    auto *pstOut = static_cast<GUILD_MEMBER *>(pHost);

    char buf[32];

    if (poNetData->DelQword(pstOut->player_id) == -1) return -1;

    if (poNetData->DelString(buf, _countof(buf)) == -1) return -1;
    pstOut->player_name = buf;

    if (poNetData->DelByte(pstOut->job) == -1) return -1;

    if (poNetData->DelDword(pstOut->level) == -1) return -1;

    if (poNetData->DelQword(pstOut->guild_id) == -1) return -1;

    if (poNetData->DelByte(pstOut->title) == -1) return -1;

    if (poNetData->DelByte(pstOut->new_title) == -1) return -1;

    if (poNetData->DelQword(pstOut->join_time) == -1) return -1;

    if (poNetData->DelQword(pstOut->login_time) == -1) return -1;

    if (poNetData->DelDword(pstOut->cur_contrib) == -1) return -1;

    if (poNetData->DelDword(pstOut->total_contrib) == -1) return -1;

    if (poNetData->DelDword(pstOut->kills) == -1) return -1;

    if (poNetData->DelDword(pstOut->combat_cap) == -1) return -1;

    if (poNetData->DelByte(pstOut->status) == -1) return -1;

    if (poNetData->DelString(buf, _countof(buf)) == -1) return -1;
    pstOut->kicked_by = buf;

    return poNetData->GetDataLen() - nStartPos;
}
int EnCodeGUILD_APPLY_INFO(void *pHost, CNetData *poNetData)
{
    const auto *pstIn = static_cast<GUILD_APPLY_INFO *>(pHost);

    if (poNetData->AddQword(pstIn->player_id) == -1) return -1;

    if (poNetData->AddString(pstIn->player_name.c_str(), pstIn->player_name.length() + 1) == -1) return -1;

    if (poNetData->AddDword(pstIn->level) == -1) return -1;

    if (poNetData->AddByte(pstIn->job) == -1) return -1;

    if (poNetData->AddQword(pstIn->guild_id) == -1) return -1;

    if (poNetData->AddQword(pstIn->apply_time) == -1) return -1;

    if (poNetData->AddQword(pstIn->login_time) == -1) return -1;

    if (poNetData->AddByte(pstIn->status) == -1) return -1;

    if (poNetData->AddString(pstIn->handled_by.c_str(), pstIn->handled_by.length() + 1) == -1) return -1;

    return poNetData->GetDataLen();
}
int DeCodeGUILD_APPLY_INFO(void *pHost, CNetData *poNetData)
{
    auto nStartPos = poNetData->GetDataLen();

    auto *pstOut = static_cast<GUILD_APPLY_INFO *>(pHost);

    if (poNetData->DelQword(pstOut->player_id) == -1) return -1;

    char buf[32];
    if (poNetData->DelString(buf, _countof(buf)) == -1) return -1;
    pstOut->player_name = buf;

    if (poNetData->DelDword(pstOut->level) == -1) return -1;

    if (poNetData->DelByte(pstOut->job) == -1) return -1;

    if (poNetData->DelQword(pstOut->guild_id) == -1) return -1;

    if (poNetData->DelQword(pstOut->apply_time) == -1) return -1;

    if (poNetData->DelQword(pstOut->login_time) == -1) return -1;

    if (poNetData->DelByte(pstOut->status) == -1) return -1;

    if (poNetData->DelString(buf, _countof(buf)) == -1) return -1;
    pstOut->handled_by = buf;

    return poNetData->GetDataLen() - nStartPos;
}
int EnCodeMALL_ITEM_INFO(void* pHost, CNetData* poNetData)
{
	MALL_ITEM_INFO* pstIn = (MALL_ITEM_INFO*)pHost;

	if(-1 == poNetData->AddDword(pstIn->item_index))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->is_hot))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->num))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->value_type))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->price))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->discount))
		return -1;

	if (-1 == poNetData->AddWord(pstIn->limits_type))
		return -1;

	if (-1 == poNetData->AddWord(pstIn->limits_time))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMALL_ITEM_INFO(void* pHost, CNetData* poNetData)
{
	MALL_ITEM_INFO* pstOut = (MALL_ITEM_INFO*)pHost;

	if(-1 == poNetData->DelDword(pstOut->item_index))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->is_hot))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->num))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->value_type))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->price))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->discount))
		return -1;

	if (-1 == poNetData->DelWord(pstOut->limits_type))
		return -1;

	if (-1 == poNetData->DelWord(pstOut->limits_time))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMALL_ITEM_DETAIL(void* pHost, CNetData* poNetData)
{
	MALL_ITEM_DETAIL* pstIn = (MALL_ITEM_DETAIL*)pHost;

	if(-1 == poNetData->AddDword(pstIn->item_index))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->image_desc))
		return -1;

	if(-1 == poNetData->AddString(pstIn->text_desc, sizeof(pstIn->text_desc)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMALL_ITEM_DETAIL(void* pHost, CNetData* poNetData)
{
	MALL_ITEM_DETAIL* pstOut = (MALL_ITEM_DETAIL*)pHost;

	if(-1 == poNetData->DelDword(pstOut->item_index))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->image_desc))
		return -1;

	if(-1 == poNetData->DelString(pstOut->text_desc, sizeof(pstOut->text_desc)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTOPLIST_INFO(void* pHost, CNetData* poNetData)
{
	TOPLIST_INFO* pstIn = (TOPLIST_INFO*)pHost;

	if(-1 == poNetData->AddString(pstIn->player_name, sizeof(pstIn->player_name)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->level))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->job))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->gender))
		return -1;

	if(-1 == poNetData->AddString(pstIn->ext1, sizeof(pstIn->ext1)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->ext2, sizeof(pstIn->ext2)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->ext3, sizeof(pstIn->ext3)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTOPLIST_INFO(void* pHost, CNetData* poNetData)
{
	TOPLIST_INFO* pstOut = (TOPLIST_INFO*)pHost;

	if(-1 == poNetData->DelString(pstOut->player_name, sizeof(pstOut->player_name)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->level))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->job))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->gender))
		return -1;

	if(-1 == poNetData->DelString(pstOut->ext1, sizeof(pstOut->ext1)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->ext2, sizeof(pstOut->ext2)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->ext3, sizeof(pstOut->ext3)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQUEST_HUNTING_INFO(void* pHost, CNetData* poNetData)
{
	QUEST_HUNTING_INFO* pstIn = (QUEST_HUNTING_INFO*)pHost;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->count))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->required))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQUEST_HUNTING_INFO(void* pHost, CNetData* poNetData)
{
	QUEST_HUNTING_INFO* pstOut = (QUEST_HUNTING_INFO*)pHost;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->count))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->required))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQUEST_HUNTLEVEL_INFO(void* pHost, CNetData* poNetData)
{
	QUEST_HUNTLEVEL_INFO* pstIn = (QUEST_HUNTLEVEL_INFO*)pHost;

    if(-1 == poNetData->AddWord(pstIn->id))
        return -1;

	if(-1 == poNetData->AddWord(pstIn->min_num))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->max_num))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->count))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->required))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQUEST_HUNTLEVEL_INFO(void* pHost, CNetData* poNetData)
{
	QUEST_HUNTLEVEL_INFO* pstOut = (QUEST_HUNTLEVEL_INFO*)pHost;

    if(-1 == poNetData->DelWord(pstOut->id))
        return -1;

	if(-1 == poNetData->DelWord(pstOut->min_num))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->max_num))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->count))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->required))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQUEST_ITEM_INFO(void* pHost, CNetData* poNetData)
{
	QUEST_ITEM_INFO* pstIn = (QUEST_ITEM_INFO*)pHost;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->count))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->required))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQUEST_ITEM_INFO(void* pHost, CNetData* poNetData)
{
	QUEST_ITEM_INFO* pstOut = (QUEST_ITEM_INFO*)pHost;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->count))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->required))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQUEST_NPC_INFO(void* pHost, CNetData* poNetData)
{
	QUEST_NPC_INFO* pstIn = (QUEST_NPC_INFO*)pHost;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->count))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQUEST_NPC_INFO(void* pHost, CNetData* poNetData)
{
	QUEST_NPC_INFO* pstOut = (QUEST_NPC_INFO*)pHost;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->count))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMAIL_HEADER_INFO(void* pHost, CNetData* poNetData)
{
	MAIL_HEADER_INFO* pstIn = (MAIL_HEADER_INFO*)pHost;

	if(-1 == poNetData->AddQword(pstIn->mail_id))
		return -1;

	if (-1 == poNetData->AddString(pstIn->title,sizeof(pstIn->title)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->send_time))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->left_time))
		return -1;

	if(-1 == poNetData->AddString(pstIn->sender, sizeof(pstIn->sender)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->status))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMAIL_HEADER_INFO(void* pHost, CNetData* poNetData)
{
	MAIL_HEADER_INFO* pstOut = (MAIL_HEADER_INFO*)pHost;

	if(-1 == poNetData->DelQword(pstOut->mail_id))
		return -1;

	if (-1 == poNetData->DelString(pstOut->title,sizeof(pstOut->title)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->send_time))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->left_time))
		return -1;

	if(-1 == poNetData->DelString(pstOut->sender, sizeof(pstOut->sender)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->status))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMAIL_BODY_INFO(void* pHost, CNetData* poNetData)
{
	MAIL_BODY_INFO* pstIn = (MAIL_BODY_INFO*)pHost;

	if(-1 == poNetData->AddString(pstIn->text, sizeof(pstIn->text)))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->gold))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->yuanbao))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->count))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstIn->count)
			break;
		if(-1 == EnCodeITEM_INFO(&pstIn->items[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeMAIL_BODY_INFO(void* pHost, CNetData* poNetData)
{
	MAIL_BODY_INFO* pstOut = (MAIL_BODY_INFO*)pHost;

	if(-1 == poNetData->DelString(pstOut->text, sizeof(pstOut->text)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->gold))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->yuanbao))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->count))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstOut->count)
			break;
		if(-1 == DeCodeITEM_INFO(&pstOut->items[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeMAIL_BODY_INFO2(void* pHost, CNetData* poNetData)
{
	MAIL_BODY_INFO2* pstIn = (MAIL_BODY_INFO2*)pHost;

	if(-1 == poNetData->AddString(pstIn->text, sizeof(pstIn->text)))
		return -1;

	if(-1 == poNetData->AddInt64(pstIn->gold))
		return -1;

	if(-1 == poNetData->AddInt64(pstIn->yuanbao))
		return -1;

	if(-1 == poNetData->AddInt64(pstIn->integral))
		return -1;

	if (-1 == poNetData->AddInt64(pstIn->bind_gold))
		return -1;

	if (-1 == poNetData->AddInt64(pstIn->bind_yunabao))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->count))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstIn->count)
			break;
		if(-1 == EnCodeITEM_INFO(&pstIn->items[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeMAIL_BODY_INFO2(void* pHost, CNetData* poNetData)
{
	MAIL_BODY_INFO2* pstOut = (MAIL_BODY_INFO2*)pHost;

	if(-1 == poNetData->DelString(pstOut->text, sizeof(pstOut->text)))
		return -1;

	if(-1 == poNetData->DelInt64(pstOut->gold))
		return -1;

	if(-1 == poNetData->DelInt64(pstOut->yuanbao))
		return -1;

	if(-1 == poNetData->DelInt64(pstOut->integral))
		return -1;

	if (-1 == poNetData->DelInt64(pstOut->bind_gold))
		return -1;

	if (-1 == poNetData->DelInt64(pstOut->bind_yunabao))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->count))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstOut->count)
			break;
		if(-1 == DeCodeITEM_INFO(&pstOut->items[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeMAIL_INFO(void* pHost, CNetData* poNetData)
{
	MAIL_INFO* pstIn = (MAIL_INFO*)pHost;
	if (-1 == poNetData->AddQword(pstIn->playerguid))
		return -1;
	if (-1 == poNetData->AddQword(pstIn->mail_id))
		return -1;
	if (-1 == poNetData->AddString(pstIn->title, sizeof(pstIn->title)))
		return -1;
	if (-1 == poNetData->AddString(pstIn->text, sizeof(pstIn->text)))
		return -1;
	if (-1 == poNetData->AddDword(pstIn->status))
		return -1;
	if (-1 == poNetData->AddWord(pstIn->currency_type_num))
		return -1;
	for (uint16_t j = 0; j < pstIn->currency_type_num; ++j)
	{
		if (-1 == EncodeMAIL_CURRENCYINFO(&pstIn->mail_currency_info[j], poNetData))
			return -1;
	}
	if (-1 == poNetData->AddWord(pstIn->addition_item_num))
		return -1;
	for (uint16_t j = 0; j < pstIn->addition_item_num; ++j)
	{
		if (-1 == EnCodeMAIL_ADDITIONITEMINFO(&pstIn->mail_addition_item_info[j], poNetData))
			return -1;
	}
	if (-1 == poNetData->AddWord(pstIn->type))
		return -1;
	if (-1 == poNetData->AddString(pstIn->sendername,sizeof(pstIn->sendername)))
		return -1;
	if (-1 == poNetData->AddQword(pstIn->send_timesmap))
		return -1;
	return poNetData->GetDataLen();
}
int DeCodeMAIL_INFO(void* pHost, CNetData* poNetData)
{
	MAIL_INFO* pstOut = (MAIL_INFO*)pHost;
	if (-1 == poNetData->DelQword(pstOut->playerguid))
		return -1;
	if (-1 == poNetData->DelQword(pstOut->mail_id))
		return -1;
	if (-1 == poNetData->DelString(pstOut->title, sizeof(pstOut->title)))
		return -1;
	if (-1 == poNetData->DelString(pstOut->text, sizeof(pstOut->text)))
		return -1;
	if (-1 == poNetData->DelDword(pstOut->status))
		return -1;
	if (-1 == poNetData->DelWord(pstOut->currency_type_num))
		return -1;
	for (uint16_t j = 0; j < pstOut->currency_type_num; ++j)
	{
		if (-1 == DeCodeMAIL_CURRENCYINFO(&pstOut->mail_currency_info[j], poNetData))
			return -1;
	}
	if (-1 == poNetData->DelWord(pstOut->addition_item_num))
		return -1;
	for (uint16_t j = 0; j < pstOut->addition_item_num; ++j)
	{
		if (-1 == DeCodeMAIL_ADDITIONITEMINFO(&pstOut->mail_addition_item_info[j], poNetData))
			return -1;
	}
	if (-1 == poNetData->DelWord(pstOut->type))
		return -1;
	if (-1 == poNetData->DelString(pstOut->sendername,sizeof(pstOut->sendername)))
		return -1;
	if (-1 == poNetData->DelQword(pstOut->send_timesmap))
		return -1;
	return sizeof(*pstOut);
}
int EnCodeMAIL_ADDITIONITEMINFO(void* pHost, CNetData* poNetData)
{
	ADDITION_ITEM_INFO* pstIn = (ADDITION_ITEM_INFO*)pHost;
	if (-1 == poNetData->AddString(pstIn->item_name, sizeof(pstIn->item_name)))
		return -1;
	if (-1 == poNetData->AddWord(pstIn->item_id))
		return -1;
	if (-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;
	if (-1 == poNetData->AddWord(pstIn->count))
		return -1;
	if (-1 == poNetData->AddWord(pstIn->bind_status))
		return -1;
	return poNetData->GetDataLen();
}
int DeCodeMAIL_ADDITIONITEMINFO(void* pHost, CNetData* poNetData)
{
	ADDITION_ITEM_INFO* pstOut = (ADDITION_ITEM_INFO*)pHost;
	if (-1 == poNetData->DelString(pstOut->item_name, sizeof(pstOut->item_name)))
		return -1;
	if (-1 == poNetData->DelWord(pstOut->item_id))
		return -1;
	if (-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;
	if (-1 == poNetData->DelWord(pstOut->count))
		return -1;
	if (-1 == poNetData->DelWord(pstOut->bind_status))
		return -1;
	return sizeof(*pstOut);
}

int EncodeMAIL_CURRENCYINFO(void* pHost, CNetData* poNetData)
{
	CURRENCY_INFO* pstIn = (CURRENCY_INFO*)pHost;
	if (-1 == poNetData->AddWord(pstIn->type))
		return -1;
	if (-1 == poNetData->AddInt64(pstIn->num))
		return -1;
	return poNetData->GetDataLen();
}

int DeCodeMAIL_CURRENCYINFO(void* pHost, CNetData* poNetData)
{
	CURRENCY_INFO* pstOut = (CURRENCY_INFO*)pHost;
	if (-1 == poNetData->DelWord(pstOut->type))
		return -1;
	if (-1 == poNetData->DelInt64(pstOut->num))
		return -1;
	return sizeof(*pstOut);
}

int EnCodeMail_INFO_STATUS(void* pHost, CNetData* poNetData)
{
	Mail_Info_Status* pstIn = (Mail_Info_Status*)pHost;
	if (-1 == poNetData->AddQword(pstIn->mailid))
		return -1;
	if (-1 == poNetData->AddDword(pstIn->status))
		return -1;
	return poNetData->GetDataLen();
}

int DeCodeMail_INFO_STATUS(void* pHost, CNetData* poNetData)
{
	Mail_Info_Status* pstOut = (Mail_Info_Status*)pHost;
	if (-1 == poNetData->DelQword(pstOut->mailid))
		return -1;
	if (-1 == poNetData->DelDword(pstOut->status))
		return -1;
	return sizeof(*pstOut);
}

int EnCodeDELEGATE_SELL_ITEM(void* pHost, CNetData* poNetData)
{
	DELEGATE_SELL_ITEM* pstIn = (DELEGATE_SELL_ITEM*)pHost;

	if(-1 == poNetData->AddQword(pstIn->id))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->seller_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->seller, sizeof(pstIn->seller)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->item_value))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->item_unit))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->time))
		return -1;

	if(-1 == EnCodeITEM_INFO(&pstIn->item, poNetData))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->value_type))
		return -1;

	if (-1 == poNetData->AddDword(pstIn->td_time))
		return -1;

	if (-1 == poNetData->AddDword(pstIn->trade_time))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeDELEGATE_SELL_ITEM(void* pHost, CNetData* poNetData)
{
	DELEGATE_SELL_ITEM* pstOut = (DELEGATE_SELL_ITEM*)pHost;

	if(-1 == poNetData->DelQword(pstOut->id))
		return -1;

	if (-1 == poNetData->DelQword(pstOut->seller_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->seller, sizeof(pstOut->seller)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->item_value))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->item_unit))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->time))
		return -1;

	if(-1 == DeCodeITEM_INFO(&pstOut->item, poNetData))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->value_type))
		return -1;

	if (-1 == poNetData->DelDword(pstOut->td_time))
		return -1;

	if (-1 == poNetData->DelDword(pstOut->trade_time))
		return -1;

	return sizeof(*pstOut);
}
/*
int EnCodeDELEGATE_BUY_ITEM(void* pHost, CNetData* poNetData)
{
	DELEGATE_BUY_ITEM* pstIn = (DELEGATE_BUY_ITEM*)pHost;

	if(-1 == poNetData->AddQword(pstIn->id))
		return -1;

	if(-1 == poNetData->AddString(pstIn->buyer, sizeof(pstIn->buyer)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->time))
		return -1;

	if(-1 == poNetData->AddString(pstIn->item_name, sizeof(pstIn->item_name)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->item_num))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->item_value))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->item_unit))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->value_type))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeDELEGATE_BUY_ITEM(void* pHost, CNetData* poNetData)
{
	DELEGATE_BUY_ITEM* pstOut = (DELEGATE_BUY_ITEM*)pHost;

	if(-1 == poNetData->DelQword(pstOut->id))
		return -1;

	if(-1 == poNetData->DelString(pstOut->buyer, sizeof(pstOut->buyer)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->time))
		return -1;

	if(-1 == poNetData->DelString(pstOut->item_name, sizeof(pstOut->item_name)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->item_num))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->item_value))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->item_unit))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->value_type))
		return -1;

	return sizeof(*pstOut);
}
*/
/*
int EnCodeDELEGATE_INFO(void* pHost, CNetData* poNetData)
{
	DELEGATE_INFO* pstIn = (DELEGATE_INFO*)pHost;

	if (-1 == poNetData->AddQword(pstIn->id))
		return -1;

	if (-1 == poNetData->AddQword(pstIn->time))
		return -1;

	if (-1 == poNetData->AddQword(pstIn->role_id))
		return -1;

	if (-1 == poNetData->AddString(pstIn->role_name))
		return -1;

	if (-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if (-1 == poNetData->AddDword(pstIn->item_id))
		return -1;

	if (-1 == poNetData->AddString(pstIn->item_name))
		return -1;

	if (-1 == poNetData->AddDword(pstIn->item_num))
		return -1;

	if (-1 == poNetData->AddDword(pstIn->item_value))
		return -1;

	if (-1 == poNetData->AddDword(pstIn->item_unit))
		return -1;

	if (-1 == poNetData->AddByte(pstIn->value_type))
		return -1;

	if (-1 == poNetData->AddByte(pstIn->trade_type))
		return -1;

	return poNetData->GetDataLen();
}

int DeCodeDELEGATE_INFO(void* pHost, CNetData* poNetData)
{
	DELEGATE_INFO* pstOut = (DELEGATE_INFO*)pHost;

	if (-1 == poNetData->DelQword(pstOut->id))
		return -1;
	if (-1 == poNetData->DelQword(pstOut->time))
		return -1;
	if (-1 == poNetData->DelQword(pstOut->role_id))
		return -1;
	if (poNetData->DelString(pstOut->role_name, _countof(pstOut->role_name)) == -1)
		return -1;
	if (-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;
	if (-1 == poNetData->DelDword(pstOut->item_id))
		return -1;
	if (poNetData->DelString(pstOut->item_name, _countof(pstOut->item_name)) == -1)
		return -1;
	if (-1 == poNetData->DelDword(pstOut->item_num))
		return -1;
	if (-1 == poNetData->DelDword(pstOut->item_value))
		return -1;
	if (-1 == poNetData->DelDword(pstOut->item_unit))
		return -1;
	if (-1 == poNetData->DelByte(pstOut->value_type))
		return -1;
	if (-1 == poNetData->DelByte(pstOut->trade_type))
		return -1;

	return sizeof(*pstOut);
}
*/
int EnCodeCAMPAIGN_INFO(void* pHost, CNetData* poNetData)
{
	CAMPAIGN_INFO* pstIn = (CAMPAIGN_INFO*)pHost;

	if(-1 == poNetData->AddDword(pstIn->id))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == poNetData->AddString(pstIn->begin, sizeof(pstIn->begin)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->end, sizeof(pstIn->end)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->minlevel))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->maxlevel))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->count))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->max_count))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->status))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeCAMPAIGN_INFO(void* pHost, CNetData* poNetData)
{
	CAMPAIGN_INFO* pstOut = (CAMPAIGN_INFO*)pHost;

	if(-1 == poNetData->DelDword(pstOut->id))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == poNetData->DelString(pstOut->begin, sizeof(pstOut->begin)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->end, sizeof(pstOut->end)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->minlevel))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->maxlevel))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->count))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->max_count))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->status))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeFAMILY_ALLY_INFO(void* pHost, CNetData* poNetData)
{
	FAMILY_ALLY_INFO* pstIn = (FAMILY_ALLY_INFO*)pHost;

	if(-1 == poNetData->AddString(pstIn->family1, sizeof(pstIn->family1)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->family2, sizeof(pstIn->family2)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeFAMILY_ALLY_INFO(void* pHost, CNetData* poNetData)
{
	FAMILY_ALLY_INFO* pstOut = (FAMILY_ALLY_INFO*)pHost;

	if(-1 == poNetData->DelString(pstOut->family1, sizeof(pstOut->family1)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->family2, sizeof(pstOut->family2)))
		return -1;

	return sizeof(*pstOut);
}


int EnCodeTAOBAO_ITEM_INFO(void* pHost, CNetData* poNetData)
{
	TAOBAO_ITEM_INFO* pstIn = (TAOBAO_ITEM_INFO*)pHost;

	if(-1 == EnCodeITEM_INFO(&pstIn->item, poNetData))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->value))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTAOBAO_ITEM_INFO(void* pHost, CNetData* poNetData)
{
	TAOBAO_ITEM_INFO* pstOut = (TAOBAO_ITEM_INFO*)pHost;

	if(-1 == DeCodeITEM_INFO(&pstOut->item, poNetData))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->value))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMAP_INFO(void* pHost, CNetData* poNetData)
{
	MAP_INFO* pstIn = (MAP_INFO*)pHost;

	if(-1 == poNetData->AddWord(pstIn->width))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->height))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMAP_INFO(void* pHost, CNetData* poNetData)
{
	MAP_INFO* pstOut = (MAP_INFO*)pHost;

	if(-1 == poNetData->DelWord(pstOut->width))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->height))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTABLE_INFO(void* pHost, CNetData* poNetData)
{
	TABLE_INFO* pstIn = (TABLE_INFO*)pHost;

	if(-1 == poNetData->AddDword(pstIn->version))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->lines))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->size))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTABLE_INFO(void* pHost, CNetData* poNetData)
{
	TABLE_INFO* pstOut = (TABLE_INFO*)pHost;

	if(-1 == poNetData->DelDword(pstOut->version))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->lines))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->size))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTOPLIST_ITEM_INFO(void* pHost, CNetData* poNetData)
{
	TOPLIST_ITEM_INFO* pstIn = (TOPLIST_ITEM_INFO*)pHost;

	if(-1 == poNetData->AddByte(pstIn->size))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstIn->size)
			break;
		if(-1 == EnCodeITEM_INFO(&pstIn->item[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeTOPLIST_ITEM_INFO(void* pHost, CNetData* poNetData)
{
	TOPLIST_ITEM_INFO* pstOut = (TOPLIST_ITEM_INFO*)pHost;

	if(-1 == poNetData->DelByte(pstOut->size))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstOut->size)
			break;
		if(-1 == DeCodeITEM_INFO(&pstOut->item[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeDataInfoDoNotUse(void* pHost, CNetData* poNetData)
{
	DataInfoDoNotUse* pstIn = (DataInfoDoNotUse*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeDataInfoDoNotUse(void* pHost, CNetData* poNetData)
{
	DataInfoDoNotUse* pstOut = (DataInfoDoNotUse*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeVIP_ITEM(void* pHost, CNetData* poNetData)
{
	VIP_ITEM* pstIn = (VIP_ITEM*)pHost;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->enable))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->remain))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->price))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeVIP_ITEM(void* pHost, CNetData* poNetData)
{
	VIP_ITEM* pstOut = (VIP_ITEM*)pHost;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->enable))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->remain))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->price))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeVIP_LEVEL(void* pHost, CNetData* poNetData)
{
	VIP_LEVEL* pstIn = (VIP_LEVEL*)pHost;

	if(-1 == poNetData->AddWord(pstIn->level))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->price))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->times))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeVIP_LEVEL(void* pHost, CNetData* poNetData)
{
	VIP_LEVEL* pstOut = (VIP_LEVEL*)pHost;

	if(-1 == poNetData->DelWord(pstOut->level))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->price))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->times))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQUEST_STATE_ITEM(void* pHost, CNetData* poNetData)
{
	QUEST_STATE_ITEM* pstIn = (QUEST_STATE_ITEM*)pHost;

	if(-1 == poNetData->AddString(pstIn->title, sizeof(pstIn->title)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->template_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->state))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQUEST_STATE_ITEM(void* pHost, CNetData* poNetData)
{
	QUEST_STATE_ITEM* pstOut = (QUEST_STATE_ITEM*)pHost;

	if(-1 == poNetData->DelString(pstOut->title, sizeof(pstOut->title)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->template_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->state))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQUEST_STATE_INFO(void* pHost, CNetData* poNetData)
{
	QUEST_STATE_INFO* pstIn = (QUEST_STATE_INFO*)pHost;

	if(-1 == poNetData->AddWord(pstIn->num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstIn->num)
			break;
		if(-1 == EnCodeQUEST_STATE_ITEM(&pstIn->item[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeQUEST_STATE_INFO(void* pHost, CNetData* poNetData)
{
	QUEST_STATE_INFO* pstOut = (QUEST_STATE_INFO*)pHost;

	if(-1 == poNetData->DelWord(pstOut->num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstOut->num)
			break;
		if(-1 == DeCodeQUEST_STATE_ITEM(&pstOut->item[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeGLORY_STATE(void* pHost, CNetData* poNetData)
{
	GLORY_STATE* pstIn = (GLORY_STATE*)pHost;

	if(-1 == poNetData->AddWord(pstIn->template_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->state))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeGLORY_STATE(void* pHost, CNetData* poNetData)
{
	GLORY_STATE* pstOut = (GLORY_STATE*)pHost;

	if(-1 == poNetData->DelWord(pstOut->template_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->state))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeROLE_BRIEF_INFO(void* pHost, CNetData* poNetData)
{
	ROLE_BRIEF_INFO* pstIn = (ROLE_BRIEF_INFO*)pHost;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->head))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->level))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->status))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->job))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->hair))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->hair_color))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->gender))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->weapon))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->clothes))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->gssvrid))
		return -1;

	if (-1 == poNetData->AddDword(pstIn->vipLevel))
		return -1;

	if (-1 == poNetData->AddByte(pstIn->is_lock))
		return -1;

	if (-1 == poNetData->AddQword(pstIn->updateTime))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeROLE_BRIEF_INFO(void* pHost, CNetData* poNetData)
{
	ROLE_BRIEF_INFO* pstOut = (ROLE_BRIEF_INFO*)pHost;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->head))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->level))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->status))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->job))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->hair))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->hair_color))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->gender))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->weapon))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->clothes))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->gssvrid))
		return -1;

	if (-1 == poNetData->DelDword(pstOut->vipLevel))
		return -1;

	if (-1 == poNetData->DelByte(pstOut->is_lock))
		return -1;

	if (-1 == poNetData->DelQword(pstOut->updateTime))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeROLE_EXTRA_INFO(void *pHost, CNetData *poNetData)
{
    ROLE_EXTRA_INFO* pstIn = (ROLE_EXTRA_INFO*)pHost;

    if(-1 == poNetData->AddQword(pstIn->login_time))
        return -1;

    if(-1 == poNetData->AddDword(pstIn->hp))
        return -1;

    if(-1 == poNetData->AddDword(pstIn->mp))
        return -1;

    if(-1 == poNetData->AddQword(pstIn->exp))
        return -1;

    if(-1 == poNetData->AddWord(pstIn->mapid))
        return -1;

    if(-1 == poNetData->AddWord(pstIn->posx))
        return -1;

    if(-1 == poNetData->AddWord(pstIn->posy))
        return -1;

    if(-1 == poNetData->AddByte(pstIn->dir))
        return -1;

	if (-1 == poNetData->AddQword(pstIn->gold))
		return -1;

	if (-1 == poNetData->AddQword(pstIn->bindGold))
		return -1;

	if (-1 == poNetData->AddQword(pstIn->ingot))
		return -1;

	if (-1 == poNetData->AddQword(pstIn->bindIngot))
		return -1;

	if (-1 == poNetData->AddQword(pstIn->integral))
		return -1;

	if (-1 == poNetData->AddQword(pstIn->depositGold))
		return -1;

	if (-1 == poNetData->AddQword(pstIn->innerForceExp))
		return -1;

    if (-1 == poNetData->AddByte(pstIn->atkMode))
        return -1;

    if (-1 == poNetData->AddWord(pstIn->birthMap))
        return -1;

    if (-1 == poNetData->AddWord(pstIn->rebirthMap))
        return -1;

    if (-1 == poNetData->AddWord(pstIn->redNameMap))
        return -1;

	if (-1 == poNetData->AddWord(pstIn->rolePk))
		return -1;

	if (-1 == poNetData->AddDword(pstIn->modelID))
		return -1;

    return poNetData->GetDataLen();
}
int DeCodeROLE_EXTRA_INFO(void *pHost, CNetData *poNetData)
{
    ROLE_EXTRA_INFO* pstOut = (ROLE_EXTRA_INFO*)pHost;

    if(-1 == poNetData->DelQword(pstOut->login_time))
        return -1;

    if(-1 == poNetData->DelDword(pstOut->hp))
        return -1;

    if(-1 == poNetData->DelDword(pstOut->mp))
        return -1;

    if(-1 == poNetData->DelQword(pstOut->exp))
        return -1;

    if(-1 == poNetData->DelWord(pstOut->mapid))
        return -1;

    if(-1 == poNetData->DelWord(pstOut->posx))
        return -1;

    if(-1 == poNetData->DelWord(pstOut->posy))
        return -1;

    if(-1 == poNetData->DelByte(pstOut->dir))
        return -1;

	if (-1 == poNetData->DelQword(pstOut->gold))
		return -1;

	if (-1 == poNetData->DelQword(pstOut->bindGold))
		return -1;

	if (-1 == poNetData->DelQword(pstOut->ingot))
		return -1;

	if (-1 == poNetData->DelQword(pstOut->bindIngot))
		return -1;

	if (-1 == poNetData->DelQword(pstOut->integral))
		return -1;

	if (-1 == poNetData->DelQword(pstOut->depositGold))
		return -1;

	if (-1 == poNetData->DelQword(pstOut->innerForceExp))
		return -1;

    if (-1 == poNetData->DelByte(pstOut->atkMode))
        return -1;

    if (-1 == poNetData->DelWord(pstOut->birthMap))
        return -1;

    if (-1 == poNetData->DelWord(pstOut->rebirthMap))
        return -1;

    if (-1 == poNetData->DelWord(pstOut->redNameMap))
        return -1;

	if (-1 == poNetData->DelWord(pstOut->rolePk))
		return -1;

	if (-1 == poNetData->DelDword(pstOut->modelID))
		return -1;

    return sizeof(*pstOut);
}

int EnCodeQUEST_INFO(void* pHost, CNetData* poNetData)
{
    QUEST_INFO* pstIn = (QUEST_INFO*)pHost;

    if (-1 == poNetData->AddWord(pstIn->pre_quest))
        return -1;

    if (-1 == poNetData->AddWord(pstIn->cur_quest))
        return -1;

    if (-1 == poNetData->AddDword(pstIn->timeleft))
        return -1;

    if (-1 == poNetData->AddQword(pstIn->timestamp))
        return -1;

    return poNetData->GetDataLen();
}
int DeCodeQUEST_INFO(void* pHost, CNetData* poNetData)
{
    QUEST_INFO* pstOut = (QUEST_INFO*)pHost;

    if (-1 == poNetData->DelWord(pstOut->pre_quest))
        return -1;

    if (-1 == poNetData->DelWord(pstOut->cur_quest))
        return -1;

    if (-1 == poNetData->DelDword(pstOut->timeleft))
        return -1;

    if (-1 == poNetData->DelQword(pstOut->timestamp))
        return -1;

    return sizeof(*pstOut);
}
int EnCodeQUEST_ACHIEVE(void* pHost, CNetData* poNetData)
{
    QUEST_ACHIEVE* pstIn = (QUEST_ACHIEVE*)pHost;

    if (-1 == poNetData->AddWord(pstIn->quest))
        return -1;

    if (-1 == poNetData->AddByte(pstIn->achev_type))
        return -1;

    if (-1 == poNetData->AddWord(pstIn->achev_id))
        return -1;

    if (-1 == poNetData->AddInt(pstIn->achev_num))
        return -1;

    return poNetData->GetDataLen();
}
int DeCodeQUEST_ACHIEVE(void* pHost, CNetData* poNetData)
{
    QUEST_ACHIEVE* pstOut = (QUEST_ACHIEVE*)pHost;

    if (-1 == poNetData->DelWord(pstOut->quest))
        return -1;

    if (-1 == poNetData->DelByte(pstOut->achev_type))
        return -1;

    if (-1 == poNetData->DelWord(pstOut->achev_id))
        return -1;

    if (-1 == poNetData->DelInt(pstOut->achev_num))
        return -1;

    return sizeof(*pstOut);
}
int EnCodeDUMMY_BRIEF_INFO(void* pHost, CNetData* poNetData)
{
	DUMMY_BRIEF_INFO* pstIn = (DUMMY_BRIEF_INFO*)pHost;

	if(-1 == poNetData->AddQword(pstIn->master_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeDUMMY_BRIEF_INFO(void* pHost, CNetData* poNetData)
{
	DUMMY_BRIEF_INFO* pstOut = (DUMMY_BRIEF_INFO*)pHost;

	if(-1 == poNetData->DelQword(pstOut->master_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeCHECK_BUFF(void* pHost, CNetData* poNetData)
{
	CHECK_BUFF* pstIn = (CHECK_BUFF*)pHost;

	{
		int iCount = 32;
		if(-1 == poNetData->AddBlob((char*)pstIn->md5_data, iCount*sizeof(char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeCHECK_BUFF(void* pHost, CNetData* poNetData)
{
	CHECK_BUFF* pstOut = (CHECK_BUFF*)pHost;

	{
		int iCount = 32;
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->md5_data, iCount*sizeof(char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeEQUIP_INFO(void* pHost, CNetData* poNetData)
{
	EQUIP_INFO* pstIn = (EQUIP_INFO*)pHost;

	if(-1 == poNetData->AddWord(pstIn->site))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeEQUIP_INFO(void* pHost, CNetData* poNetData)
{
	EQUIP_INFO* pstOut = (EQUIP_INFO*)pHost;

	if(-1 == poNetData->DelWord(pstOut->site))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeDELEGATE_BUY_ITEM2(void* pHost, CNetData* poNetData)
{
	DELEGATE_BUY_ITEM2* pstIn = (DELEGATE_BUY_ITEM2*)pHost;

	if(-1 == poNetData->AddQword(pstIn->id))
		return -1;

	if (-1 == poNetData->AddQword(pstIn->buyer_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->buyer, sizeof(pstIn->buyer)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->time))
		return -1;

	if(-1 == poNetData->AddString(pstIn->item_name, sizeof(pstIn->item_name)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_template_id))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->item_num))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->item_value))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->item_unit))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->value_type))
		return -1;

	if (-1 == poNetData->AddDword(pstIn->td_time))
		return -1;

	if (-1 == poNetData->AddDword(pstIn->trade_time))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeDELEGATE_BUY_ITEM2(void* pHost, CNetData* poNetData)
{
	DELEGATE_BUY_ITEM2* pstOut = (DELEGATE_BUY_ITEM2*)pHost;

	if(-1 == poNetData->DelQword(pstOut->id))
		return -1;

	if (-1 == poNetData->DelQword(pstOut->buyer_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->buyer, sizeof(pstOut->buyer)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->time))
		return -1;

	if(-1 == poNetData->DelString(pstOut->item_name, sizeof(pstOut->item_name)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_template_id))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->item_num))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->item_value))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->item_unit))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->value_type))
		return -1;

	if (-1 == poNetData->DelDword(pstOut->td_time))
		return -1;

	if (-1 == poNetData->DelDword(pstOut->trade_time))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMOBA_ROOM_INFO(void* pHost, CNetData* poNetData)
{
	MOBA_ROOM_INFO* pstIn = (MOBA_ROOM_INFO*)pHost;

	if(-1 == poNetData->AddInt(pstIn->room_id))
		return -1;

	if(-1 == poNetData->AddString(pstIn->room_name, sizeof(pstIn->room_name)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->max_num))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->cur_num))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->state))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->lock))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->map_id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->room_mode))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMOBA_ROOM_INFO(void* pHost, CNetData* poNetData)
{
	MOBA_ROOM_INFO* pstOut = (MOBA_ROOM_INFO*)pHost;

	if(-1 == poNetData->DelInt(pstOut->room_id))
		return -1;

	if(-1 == poNetData->DelString(pstOut->room_name, sizeof(pstOut->room_name)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->max_num))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->cur_num))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->state))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->lock))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->map_id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->room_mode))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMOBA_ROOM_MEMBER_INFO(void* pHost, CNetData* poNetData)
{
	MOBA_ROOM_MEMBER_INFO* pstIn = (MOBA_ROOM_MEMBER_INFO*)pHost;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->camp))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->job))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->site))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->host))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->ready))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMOBA_ROOM_MEMBER_INFO(void* pHost, CNetData* poNetData)
{
	MOBA_ROOM_MEMBER_INFO* pstOut = (MOBA_ROOM_MEMBER_INFO*)pHost;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->camp))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->job))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->site))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->host))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->ready))
		return -1;

	return sizeof(*pstOut);
}

int EnCodeConstantCfg(void* pHost, CNetData* poNetData)
{
	auto beginPos = poNetData->GetDataLen();

	const auto* pstIn = static_cast<CONSTANT_CFG*>(pHost);

	if (poNetData->AddString(pstIn->name) == -1) return -1;

	if (poNetData->AddString(pstIn->value) == -1) return -1;

	return poNetData->GetDataLen() - beginPos;
}
int DeCodeConstantCfg(void* pHost, CNetData* poNetData)
{
	auto beginPos = poNetData->GetDataLen();

	auto* pstOut = static_cast<CONSTANT_CFG*>(pHost);

	char buf[4096] = { 0 };

	if (poNetData->DelString(buf, _countof(buf)) == -1) return -1;
	pstOut->name = buf;

	if (poNetData->DelString(buf, _countof(buf)) == -1) return -1;
	pstOut->value = buf;

	return poNetData->GetDataLen() - beginPos;
}

int EnCodeCUST_VAR(void *pHost, CNetData *poNetData)
{
    auto beginPos = poNetData->GetDataLen();

    const auto *pstIn = static_cast<CUST_VAR *>(pHost);

    if (poNetData->AddQword(pstIn->belong) == -1) return -1;

    if (poNetData->AddString(pstIn->name) == -1) return -1;

    if (poNetData->AddString(pstIn->value) == -1) return -1;

    if (poNetData->AddByte(pstIn->type) == -1) return -1;

    if (poNetData->AddQword(pstIn->expire) == -1) return -1;

	if (poNetData->AddByte(pstIn->mergeType) == -1) return -1;

    return poNetData->GetDataLen() - beginPos;
}
int DeCodeCUST_VAR(void *pHost, CNetData *poNetData)
{
    auto beginPos = poNetData->GetDataLen();

    auto *pstOut = static_cast<CUST_VAR *>(pHost);

    if (poNetData->DelQword(pstOut->belong) == -1) return -1;

    if (poNetData->DelString(pstOut->name) == -1) return -1;

    if (poNetData->DelString(pstOut->value) == -1) return -1;

    if (poNetData->DelByte(pstOut->type) == -1) return -1;

    if (poNetData->DelQword(pstOut->expire) == -1) return -1;

	if (poNetData->DelByte(pstOut->mergeType) == -1) return -1;

    return poNetData->GetDataLen() - beginPos;
}

int EnCodeCUST_VAR_SP_LIST(void *pHost, CNetData *poNetData)
{
    auto beginPos = poNetData->GetDataLen();

    auto *vars = static_cast<CUST_VAR_SP_LIST *>(pHost);

    uint16_t count = vars ? static_cast<uint16_t>(vars->size()) : 0;
    if (poNetData->AddWord(count) == -1) return -1;

    if (vars) {
        for (auto it = vars->begin(); it != vars->end(); ++it) {
            auto &var = *it;
            if (EnCodeCUST_VAR(var.get(), poNetData) == -1)
                return -1;
        }
    }

    return poNetData->GetDataLen() - beginPos;
}
int DeCodeCUST_VAR_SP_LIST(void *pHost, CNetData *poNetData)
{
    auto *vars = static_cast<CUST_VAR_SP_LIST *>(pHost);
    if (!vars) return -1;

    auto beginPos = poNetData->GetDataLen();

    uint16_t count;
    if (poNetData->DelWord(count) == -1) return -1;

    for (uint16_t i = 0; i < count; ++i) {

        auto var = std::make_shared<CUST_VAR>();

        if (DeCodeCUST_VAR(var.get(), poNetData) == -1) return -1;

        vars->emplace_back(std::move(var));
    }

    return poNetData->GetDataLen() - beginPos;
}

int EnCodeQUICK_BAR_LIST_INFO(void* pHost, CNetData* poNetData)
{
	QUICK_BAR_LIST_INFO* pstIn = static_cast<QUICK_BAR_LIST_INFO*>(pHost);

	if (-1 == poNetData->AddQword(pstIn->role_id))
		return -1;

	if (-1 == EnCodeQUICK_BAR_INFO(&pstIn->quick,poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQUICK_BAR_LIST_INFO(void* pHost, CNetData* poNetData)
{
	QUICK_BAR_LIST_INFO* pstOut = static_cast<QUICK_BAR_LIST_INFO*>(pHost);

	if (-1 == poNetData->DelQword(pstOut->role_id))
		return -1;

	if (-1 == DeCodeQUICK_BAR_INFO(&pstOut->quick, poNetData))
		return -1;

	return sizeof(*pstOut);
}

int EnCodeDYN_ATTR(void *pHost, CNetData *poNetData)
{
    auto beginPos = poNetData->GetDataLen();

    const auto *pstIn = static_cast<DYN_ATTR *>(pHost);

    if (poNetData->AddWord(pstIn->index) == -1) return -1;

    if (poNetData->AddWord(pstIn->attr) == -1) return -1;

    if (poNetData->AddInt(pstIn->value) == -1) return -1;

    return poNetData->GetDataLen() - beginPos;
}

int DeCodeDYN_ATTR(void *pHost, CNetData *poNetData)
{
    auto beginPos = poNetData->GetDataLen();

    auto *pstOut = static_cast<DYN_ATTR *>(pHost);

    if (poNetData->DelWord(pstOut->index) == -1) return -1;

    if (poNetData->DelWord(pstOut->attr) == -1) return -1;

    if (poNetData->DelInt(pstOut->value) == -1) return -1;

    return poNetData->GetDataLen() - beginPos;
}

int EnCodeITEM_DYN_ATTRS(void *pHost, CNetData *poNetData)
{
    auto beginPos = poNetData->GetDataLen();

    auto *pstIn = static_cast<ITEM_DYN_ATTRS *>(pHost);

    if (poNetData->AddQword(pstIn->guid) == -1) return -1;

    uint16_t count = static_cast<uint16_t>(pstIn->dyn_attrs.size());
    if (poNetData->AddWord(count) == -1) return -1;

    for (auto &dyn_attr : pstIn->dyn_attrs)
        if (EnCodeDYN_ATTR(&dyn_attr, poNetData) == -1)
            return -1;

    return poNetData->GetDataLen() - beginPos;
}

int DeCodeITEM_DYN_ATTRS(void *pHost, CNetData *poNetData)
{
    auto beginPos = poNetData->GetDataLen();

    auto *pstOut = static_cast<ITEM_DYN_ATTRS *>(pHost);

    if (poNetData->DelQword(pstOut->guid) == -1) return -1;

    uint16_t count;
    if (poNetData->DelWord(count) == -1) return -1;

    DYN_ATTR dyn_attr;
    for (uint16_t i = 0; i < count; ++i) {
        if (DeCodeDYN_ATTR(&dyn_attr, poNetData) == -1) return -1;
        pstOut->dyn_attrs.emplace_back(dyn_attr);
    }

    return poNetData->GetDataLen() - beginPos;
}

int EnCodeITEM_DYN_ATTRS_LIST(void *pHost, CNetData *poNetData)
{
    auto beginPos = poNetData->GetDataLen();

    auto *pstIn = static_cast<ITEM_DYN_ATTRS_LIST *>(pHost);

    uint16_t count = static_cast<uint16_t>(pstIn->size());
    if (poNetData->AddWord(count) == -1) return -1;

    for (auto &attrs : *pstIn)
        if (EnCodeITEM_DYN_ATTRS(&attrs, poNetData) == -1)
            return -1;

    return poNetData->GetDataLen() - beginPos;
}

int DeCodeITEM_DYN_ATTRS_LIST(void *pHost, CNetData *poNetData)
{
    auto beginPos = poNetData->GetDataLen();

    auto *pstOut = static_cast<ITEM_DYN_ATTRS_LIST *>(pHost);

    uint16_t count;
    if (poNetData->DelWord(count) == -1) return -1;

    for (uint16_t i = 0; i < count; ++i) {
        ITEM_DYN_ATTRS dyn_attrs;
        if (DeCodeITEM_DYN_ATTRS(&dyn_attrs, poNetData) == -1) return -1;
        pstOut->emplace_back(std::move(dyn_attrs));
    }

    return poNetData->GetDataLen() - beginPos;
}

int EnCodeAUCTION_HOUSE_ITEM_INFO(void* pHost, CNetData* poNetData)
{
	AUCTION_HOUSE_ITEM_INFO* pstIn = static_cast<AUCTION_HOUSE_ITEM_INFO*>(pHost);

	if (-1 == poNetData->AddString(pstIn->item_name, sizeof(pstIn->item_name)))
		return -1;
	if (-1 == poNetData->AddWord(pstIn->item_num))
		return -1;
	if (-1 == poNetData->AddInt(pstIn->item_price))
		return -1;
	if (-1 == poNetData->AddByte(pstIn->currency_type))
		return -1;
	if (-1 == poNetData->AddQword(pstIn->start_time))
		return -1;
	if (-1 == poNetData->AddQword(pstIn->keep_time))
		return -1;
	if (-1 == poNetData->AddByte(pstIn->status))
		return -1;
	if (-1 == poNetData->AddQword(pstIn->orderID))
		return -1;
	if (-1 == poNetData->AddQword(pstIn->ownerID))
		return -1;
	if (-1 == poNetData->AddString(pstIn->ownerName, sizeof(pstIn->ownerName)))
		return -1;
	return poNetData->GetDataLen();
}

int DeCodeAUCTION_HOUSE_ITEM_INFO(void* pHost, CNetData* poNetData)
{
	AUCTION_HOUSE_ITEM_INFO* pstOut = static_cast<AUCTION_HOUSE_ITEM_INFO*>(pHost);

	if (-1 == poNetData->DelString(pstOut->item_name,sizeof(pstOut->item_name)))
		return -1;
	if (-1 == poNetData->DelWord(pstOut->item_num))
		return -1;
	if (-1 == poNetData->DelInt(pstOut->item_price))
		return -1;
	if (-1 == poNetData->DelByte(pstOut->currency_type))
		return -1;
	if (-1 == poNetData->DelQword(pstOut->start_time))
		return -1;
	if (-1 == poNetData->DelQword(pstOut->keep_time))
		return -1;
	if (-1 == poNetData->DelByte(pstOut->status))
		return -1;
	if (-1 == poNetData->DelQword(pstOut->orderID))
		return -1;
	if (-1 == poNetData->DelQword(pstOut->ownerID))
		return -1;
	if (-1 == poNetData->DelString(pstOut->ownerName, sizeof(pstOut->ownerName)))
		return -1;
	return sizeof(*pstOut);
}

int EnCodeLOGIN_IP_DATA(void* pHost, CNetData* poNetData)
{
	LOGIN_IP_DATA* pstIn = static_cast<LOGIN_IP_DATA*>(pHost);

	if (-1 == poNetData->AddDword(pstIn->ip))
		return -1;
	if (-1 == poNetData->AddByte(pstIn->type))
		return -1;

	return sizeof(*pstIn);
}

int DeCodeLOGIN_IP_DATA(void* pHost, CNetData* poNetData)
{
	LOGIN_IP_DATA* pstOut = static_cast<LOGIN_IP_DATA*>(pHost);

	if (-1 == poNetData->DelDword(pstOut->ip))
		return -1;
	if (-1 == poNetData->DelByte(pstOut->type))
		return -1;

	return sizeof(*pstOut);
}

int EnCodePROHIBIT_CHAT_DATA(void* pHost, CNetData* poNetData)
{
	PROHIBIT_CHAT_DATA* pstIn = static_cast<PROHIBIT_CHAT_DATA*>(pHost);

	if (-1 == poNetData->AddQword(pstIn->playerguid))
		return -1;
	if (-1 == poNetData->AddQword(pstIn->time))
		return -1;

	return sizeof(*pstIn);
}

int DeCodePROHIBIT_CHAT_DATA(void* pHost, CNetData* poNetData)
{
	PROHIBIT_CHAT_DATA* pstOut = static_cast<PROHIBIT_CHAT_DATA*>(pHost);

	if (-1 == poNetData->DelQword(pstOut->playerguid))
		return -1;
	if (-1 == poNetData->DelQword(pstOut->time))
		return -1;

	return sizeof(*pstOut);
}

int EnCodeWANTED_BY(void *pHost, CNetData *poNetData)
{
    auto nStartPos = poNetData->GetDataLen();

    const auto *pWantedBy = static_cast<WANTED_BY *>(pHost);

    if (poNetData->AddDword(pWantedBy->index) == -1) return -1;

    if (poNetData->AddQword(pWantedBy->guid) == -1) return -1;

    if (poNetData->AddString(pWantedBy->name) == -1) return -1;

    if (poNetData->AddString(pWantedBy->desc) == -1) return -1;

    if (poNetData->AddDword(pWantedBy->bounty) == -1) return -1;

    if (poNetData->AddQword(pWantedBy->ptime) == -1) return -1;

    return poNetData->GetDataLen() - nStartPos;
}

int DeCodeWANTED_BY(void *pHost, CNetData *poNetData)
{
    auto nStartPos = poNetData->GetDataLen();

    auto *pWantedBy = static_cast<WANTED_BY *>(pHost);

    if (poNetData->DelDword(pWantedBy->index) == -1) return -1;

    if (poNetData->DelQword(pWantedBy->guid) == -1) return -1;

    if (poNetData->DelString(pWantedBy->name) == -1) return -1;

    if (poNetData->DelString(pWantedBy->desc) == -1) return -1;

    if (poNetData->DelDword(pWantedBy->bounty) == -1) return -1;

    if (poNetData->DelQword(pWantedBy->ptime) == -1) return -1;

    return poNetData->GetDataLen() - nStartPos;
}

int EnCodeWANTED(void *pHost, CNetData *poNetData)
{
    auto nStartPos = poNetData->GetDataLen();

    const auto *pWanted = static_cast<WANTED *>(pHost);

    if (poNetData->AddQword(pWanted->guid) == -1) return -1;

    if (poNetData->AddString(pWanted->name) == -1) return -1;

    auto count = static_cast<uint16_t>(pWanted->wanted_by_list.size());
    if (poNetData->AddWord(count) == -1) return -1;

    for (const auto &wanted_by : pWanted->wanted_by_list)
        if (EnCodeWANTED_BY(wanted_by.get(), poNetData) == -1)
            return -1;

    return poNetData->GetDataLen() - nStartPos;
}

int DeCodeWANTED(void *pHost, CNetData *poNetData)
{
    auto nStartPos = poNetData->GetDataLen();

    auto *pWanted = static_cast<WANTED *>(pHost);

    if (poNetData->DelQword(pWanted->guid) == -1) return -1;

    if (poNetData->DelString(pWanted->name) == -1) return -1;

    uint16_t count = 0;
    if (poNetData->DelWord(count) == -1) return -1;

    for (uint16_t i = 0; i < count; ++i) {

        auto spWantedBy = std::make_shared<WANTED_BY>();

        if (DeCodeWANTED_BY(spWantedBy.get(), poNetData) == -1)
            return -1;

        pWanted->wanted_by_list.emplace_back(std::move(spWantedBy));
    }

    return poNetData->GetDataLen() - nStartPos;
}

int EncodePoint(void *pHost, CNetData *poNetData)
{
	BEGIN_ENCODE(Point);
	ENCODE_SHORT(x);
	ENCODE_SHORT(y);
	END_ENCODE();
}

int DecodePoint(void *pHost, CNetData *poNetData)
{
	BEGIN_DECODE(Point);
	DECODE_SHORT(x);
	DECODE_SHORT(y);
	END_DECODE();
}

int EncodeAUTO_PICKUP(void *pHost, CNetData *poNetData)
{
	BEGIN_ENCODE(AUTO_PICKUP);
	ENCODE_BYTE(mode);
	ENCODE_BYTE(radius);
	ENCODE_BYTE(numpos);
	ENCODE_CHECK_UPBOUND(numpos, relpos);

	for (int i = 0; i < pstIn->numpos; ++i)
		if (EncodePoint(pstIn->relpos + i, poNetData) == -1)
			return -1;

    ENCODE_WORD(interval);
	END_ENCODE();
}

int DecodeAUTO_PICKUP(void *pHost, CNetData *poNetData)
{
	BEGIN_DECODE(AUTO_PICKUP);
	DECODE_BYTE(mode);
	DECODE_BYTE(radius);
	DECODE_BYTE(numpos);
	DECODE_CHECK_UPBOUND(numpos, relpos);

	for (int i = 0; i < pstOut->numpos; ++i)
		if (DecodePoint(pstOut->relpos + i, poNetData) == -1)
			return -1;

    DECODE_WORD(interval);
	END_DECODE();
}

int EncodeROLE_SETTINGS(void *pHost, CNetData *poNetData)
{
	BEGIN_ENCODE(ROLE_SETTINGS);

	if (EncodeAUTO_PICKUP(&pstIn->auto_pickup, poNetData) == -1)
		return -1;

	END_ENCODE();
}

int DecodeROLE_SETTINGS(void *pHost, CNetData *poNetData)
{
	BEGIN_DECODE(ROLE_SETTINGS);

	if (DecodeAUTO_PICKUP(&pstOut->auto_pickup, poNetData) == -1)
		return -1;

	END_DECODE();
}

int EncodeGOODS_ISSUE_RECORD(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE(GOODS_ISSUE_RECORD);
    ENCODE_STRING(order_no);
    ENCODE_QWORD(role_guid);
    ENCODE_BYTE(pay_type);
    ENCODE_DWORD(goods_id);
    ENCODE_DWORD(goods_num);
    ENCODE_DWORD(pay_amount);
    ENCODE_BYTE(issued);
	ENCODE_BYTE(isPost);

    END_ENCODE();
}

int DecodeGOODS_ISSUE_RECORD(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE(GOODS_ISSUE_RECORD);
    DECODE_STRING(order_no);
    DECODE_QWORD(role_guid);
    DECODE_BYTE(pay_type);
    DECODE_DWORD(goods_id);
    DECODE_DWORD(goods_num);
    DECODE_DWORD(pay_amount);
    DECODE_BYTE(issued);
	DECODE_BYTE(isPost);
    END_DECODE();
}

int EncodeREBATE_MONEY_RECORD(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE(REBATE_MONEY_RECORD);
	ENCODE_BYTE(be_load);
	ENCODE_INT64(inc_id);
	ENCODE_QWORD(account_id);
	ENCODE_STRING(account_name);
	ENCODE_INT64(rebate_money);
	ENCODE_BYTE(is_use);
	END_ENCODE();
}

int DecodeREBATE_MONEY_RECORD(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE(REBATE_MONEY_RECORD);
	DECODE_BYTE(be_load);
	DECODE_INT64(inc_id);
	DECODE_QWORD(account_id);
	DECODE_STRING(account_name);
	DECODE_INT64(rebate_money);
	DECODE_BYTE(is_use);
	END_DECODE();
}

int EncodeCUST_LIST_INFO(void* pHost, CNetData* poNetData) 
{
	BEGIN_ENCODE(CUST_LIST_INFO);
	ENCODE_QWORD(guid);
	ENCODE_INT(type);
	ENCODE_INT64(value);
	ENCODE_QWORD(stamp);
	ENCODE_STRING(desc);
	ENCODE_WORD(ranking);
	END_ENCODE();
}

int DecodeCUST_LIST_INFO(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE(CUST_LIST_INFO);
	DECODE_QWORD(guid);
	DECODE_INT(type);
	DECODE_INT64(value);
	DECODE_QWORD(stamp);
	DECODE_STRING(desc);
	DECODE_WORD(ranking);
	END_DECODE();
}

int EncodeEFFECT_POINT(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE(EffectPoint);
	ENCODE_WORD(x);
	ENCODE_WORD(y);
	ENCODE_DWORD(effect);
	END_ENCODE();
}

int DecodeEFFECT_POINT(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE(EffectPoint);
	DECODE_WORD(x);
	DECODE_WORD(y);
	DECODE_DWORD(effect);
	END_DECODE();
}

int EncodeMONITOR_CHAT_INFO(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE(MONITOR_CHAT_INFO);
	ENCODE_QWORD(user_id);
	ENCODE_STRING(user_name);
	ENCODE_QWORD(to_user_id);
	ENCODE_STRING(to_user_name);
	ENCODE_WORD(channel);
	ENCODE_STRING(guild);
	ENCODE_STRING(stamp);
	ENCODE_STRING(content);
	END_ENCODE();
}

int DecodeMONITOR_CHAT_INFO(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE(MONITOR_CHAT_INFO);
	DECODE_QWORD(user_id);
	DECODE_STRING(user_name);
	DECODE_QWORD(to_user_id);
	DECODE_STRING(to_user_name);
	DECODE_WORD(channel);
	DECODE_STRING(guild);
	DECODE_STRING(stamp);
	DECODE_STRING(content);
	END_DECODE();
}

int EncodeRELATION_CHAT_NTF(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE(RELATION_CHAT_NTF);
	ENCODE_DWORD(size);
	ENCODE_BYTE(type);
	if (EnCodeCHAT_MSG(&pstIn->chat_message, poNetData) == -1)return -1;
	ENCODE_BYTE(scroll_times);
	ENCODE_STRING(font_color);
	ENCODE_STRING(background_color);
	ENCODE_BYTE(comp);
	END_ENCODE();
}

int DecodeRELATION_CHAT_NTF(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE(RELATION_CHAT_NTF);
	DECODE_DWORD(size);
	DECODE_BYTE(type);
	if (DeCodeCHAT_MSG(&pstOut->chat_message, poNetData) == -1)return -1;
	DECODE_BYTE(scroll_times);
	DECODE_STRING(font_color);
	DECODE_STRING(background_color);
	DECODE_BYTE(comp);
	END_DECODE();
}

int EncodeSYSTEN_MESSAGE_NTF(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE(SYSTEN_MESSAGE_NTF);
	ENCODE_DWORD(size);
	if (-1 == poNetData->AddBlob(pstIn->message, pstIn->size))return -1;
	ENCODE_STRING(font_color);
	ENCODE_STRING(background_color);
	ENCODE_BYTE(comp);
	END_ENCODE();
}

int DecodeSYSTEN_MESSAGE_NTF(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE(SYSTEN_MESSAGE_NTF);
	DECODE_DWORD(size);
	if (-1 == poNetData->DelBlob(pstOut->message, pstOut->size))
		return -1;
	DECODE_STRING(font_color);
	DECODE_STRING(background_color);
	DECODE_BYTE(comp);
	END_DECODE();
}

int EncodeSCENCE_DIALOG_NTF(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE(SCENCE_DIALOG_NTF);
	ENCODE_DWORD(size);
	if (-1 == poNetData->AddBlob(pstIn->message, pstIn->size))return -1;
	ENCODE_STRING(font_color);
	ENCODE_STRING(background_color);
	ENCODE_QWORD(objGuid);
	ENCODE_BYTE(isAppearSrcName);
	ENCODE_BYTE(comp);
	END_ENCODE();
}

int DecodeSCENCE_DIALOG_NTF(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE(SCENCE_DIALOG_NTF);
	DECODE_DWORD(size);
	if (-1 == poNetData->DelBlob(pstOut->message, pstOut->size))
		return -1;
	DECODE_STRING(font_color);
	DECODE_STRING(background_color);
	DECODE_QWORD(objGuid);
	DECODE_BYTE(isAppearSrcName);
	DECODE_BYTE(comp);
	END_DECODE();
}

int EncodeSCROLL_TEXT(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE(SCROLL_TEXT);
	ENCODE_DWORD(size);
	ENCODE_BLOB(message, pstIn->size);
	ENCODE_STRING(font_color);
	ENCODE_STRING(background_color);
	ENCODE_BYTE(scroll_times);
	ENCODE_BYTE(comp);
	ENCODE_BYTE(type);
	END_ENCODE();
}

int DecodeSCROLL_TEXT(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE(SCROLL_TEXT);
	DECODE_DWORD(size);
	DECODE_BLOB(message, pstOut->size);
	DECODE_STRING(font_color);
	DECODE_STRING(background_color);
	DECODE_BYTE(scroll_times);
	DECODE_BYTE(comp);
	DECODE_BYTE(type);
	END_DECODE();
}

int EncodeCUST_MSG_NTF(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE(CUST_MSG_NTF);
	ENCODE_DWORD(size);
	ENCODE_BLOB(message, pstIn->size);
	ENCODE_STRING(font_color);
	ENCODE_STRING(background_color);
	ENCODE_BYTE(comp);
	ENCODE_WORD(display_type);
	ENCODE_BYTE(scroll_times);
	END_ENCODE();
}

int DecodeCUST_MSG_NTF(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE(CUST_MSG_NTF);
	DECODE_DWORD(size);
	DECODE_BLOB(message, pstOut->size);
	DECODE_STRING(font_color);
	DECODE_STRING(background_color);
	DECODE_BYTE(comp);
	DECODE_WORD(display_type);
	DECODE_BYTE(scroll_times);
	END_DECODE();
}

int EnCodeTITLE_INFO(void* pHost, CNetData* poNetData)
{
	BEGIN_ENCODE(TITLE_INFO);
	ENCODE_DWORD(Id);
	ENCODE_BYTE(isWear);
	ENCODE_QWORD(addTime);
	ENCODE_DWORD(lifeTime);
	ENCODE_DWORD(timeLimit);
	END_ENCODE();
}

int DeCodeTITLE_INFO(void* pHost, CNetData* poNetData)
{
	BEGIN_DECODE(TITLE_INFO);
	DECODE_DWORD(Id);
	DECODE_BYTE(isWear);
	DECODE_QWORD(addTime);
	DECODE_DWORD(lifeTime);
	DECODE_DWORD(timeLimit);
	END_DECODE();
}

CDataInfo::CDataInfo()
{
	m_EnCodeFuncArray[0] = &EnCodeDataInfoDoNotUse;
	m_DeCodeFuncArray[0] = &DeCodeDataInfoDoNotUse;

}

CDataInfo::~CDataInfo()
{
}

int CDataInfo::BuildProtocol(void* pHost, char *pNet, int iNetSize)
{
	CNetData m_oData;
	m_oData.Prepare(pNet, iNetSize);
	if (*(unsigned short*)pHost != 15)
	{
		return -1;
	}
	if (*(unsigned short*)((char*)pHost+sizeof(unsigned short)) >= sizeof(m_EnCodeFuncArray)/sizeof(EnCodeFuncDataInfo))
	{
		return -1;
	}
	return m_EnCodeFuncArray[*(unsigned short*)((char*)pHost+sizeof(unsigned short))](pHost, &m_oData);
}

bool CDataInfo::HandleProtocol(char *pNet, int iNetSize, void* pHost)
{
	CNetData m_oData;
	m_oData.Prepare(pNet, iNetSize);

	unsigned short moudleid = 0;
	unsigned short protocolid = 0;
	if (m_oData.DelWord(moudleid) < 0)
	{
		return false;
	}
	if (moudleid != 15)
	{
		return false;
	}
	if (m_oData.DelWord(protocolid) < 0)
	{
		return false;
	}
	if (protocolid >= sizeof(m_DeCodeFuncArray)/sizeof(DeCodeFuncDataInfo))
	{
		return false;
	}

	m_oData.Prepare(pNet, iNetSize);

	if (m_DeCodeFuncArray[protocolid](pHost, &m_oData) < 0)
	{
		return false;
	}

	switch(protocolid)
	{
	case 0:
		OnRecv_DataInfoDoNotUse(*(DataInfoDoNotUse*)pHost);
		break;
	default:
		return false;
	}

	return true;
}

void CUSTOM_INFO::operator<<(CONSTANT_CFG_MAP& constantCfgMap)
{
	CNetData c;
	c.Prepare(buf + num, sizeof(buf));

	c.AddWord((uint16_t)constantCfgMap.size());
	for (auto& var : constantCfgMap)
	{
		EnCodeConstantCfg(&var.second, &c);
	}
	num += c.m_iPos;
	idx = 0;
}
void CUSTOM_INFO::operator<<(CUST_VAR_MAP& mCustVars)
{
	CNetData c;
	c.Prepare(buf + num, sizeof(buf));

	c.AddWord((uint16_t)mCustVars.size());
	for (auto& var : mCustVars)
	{
		EnCodeCUST_VAR(&var.second, &c);
	}
	num += c.m_iPos;
	idx = 0;
}
void CUSTOM_INFO::operator<<(CUST_VAR_SP_MAP& mCustVars)
{
	CNetData c;
	c.Prepare(buf + num, sizeof(buf));

	c.AddWord((uint16_t)mCustVars.size());
	for (auto& var : mCustVars)
	{
		EnCodeCUST_VAR(var.second.get(), &c);
	}
	num += c.m_iPos;
	idx = 0;
}
void CUSTOM_INFO::operator<<(CUST_VAR_LIST& mCustVars)
{
	CNetData c;
	c.Prepare(buf + num, sizeof(buf));

	c.AddWord((uint16_t)mCustVars.size());
	for (auto& var : mCustVars)
	{
		EnCodeCUST_VAR(&var, &c);
	}
	num += c.m_iPos;
	idx = 0;
}
void CUSTOM_INFO::operator<<(CUST_VAR_SP_LIST& mCustVars)
{
	CNetData c;
	c.Prepare(buf + num, sizeof(buf));

	c.AddWord((uint16_t)mCustVars.size());
	for (auto& var : mCustVars)
	{
		EnCodeCUST_VAR(var.get(), &c);
	}
	num += c.m_iPos;
	idx = 0;
}
void CUSTOM_INFO::operator<<(DYN_ATTRS& mDynAttrs)
{
	CNetData c;
	c.Prepare(buf + num, sizeof(buf));

	c.AddWord((uint16_t)mDynAttrs.size());
	for (auto& var : mDynAttrs)
	{
		EnCodeDYN_ATTR(&var, &c);
	}
	num += c.m_iPos;
	idx = 0;
}
void CUSTOM_INFO::operator>>(CUST_VAR_LIST& mCustVars)
{
	if (idx >= num) return;

	CNetData c;
	c.Prepare(buf + idx, sizeof(buf));

	uint16_t len = 0;
	c.DelWord(len);
	for (int i = 0; i < len; ++i)
	{
		CUST_VAR var;
		DeCodeCUST_VAR(&var, &c);
		mCustVars.push_back(var);
	}
	idx += c.m_iPos;
}
void CUSTOM_INFO::operator>>(DYN_ATTRS& mDynAttrs)
{
	if (idx >= num) return;

	CNetData c;
	c.Prepare(buf + idx, sizeof(buf));

	uint16_t len = 0;
	c.DelWord(len);
	for (int32_t i = 0; i < len; ++i)
	{
		DYN_ATTR attr;
		DeCodeDYN_ATTR(&attr, &c);
		mDynAttrs.push_back(attr);
	}
	idx += c.m_iPos;
}
void CUSTOM_INFO::operator>>(CONSTANT_CFG_MAP& constantCfgMap)
{
	if (idx >= num) return;

	CNetData c;
	c.Prepare(buf + idx, sizeof(buf));

	uint16_t len = 0;
	c.DelWord(len);
	for (int i = 0; i < len; ++i)
	{
		CONSTANT_CFG var;
		DeCodeConstantCfg(&var, &c);
		constantCfgMap.emplace(var.name, std::move(var));
	}
	idx += c.m_iPos;
}

CUSTOM_INFO& CUSTOM_INFO::operator<<(uint16_t data)
{
	CNetData c;
	c.Prepare(buf + num, sizeof(buf));
	c.AddWord(data);
	num += c.m_iPos;
	idx = 0;

	return *this;
}
CUSTOM_INFO& CUSTOM_INFO::operator<<(const std::string& data)
{
	CNetData c;
	c.Prepare(buf + num, sizeof(buf));
	c.AddString(data);
	num += c.m_iPos;
	idx = 0;

	return *this;
}
CUSTOM_INFO& CUSTOM_INFO::operator>>(uint16_t& data)
{
	if (idx >= num) return *this;

	CNetData c;
	c.Prepare(buf + idx, sizeof(buf));

	c.DelWord(data);
	idx += c.m_iPos;

	return *this;
}
CUSTOM_INFO& CUSTOM_INFO::operator>>(std::string& data)
{
	if (idx >= num) return *this;

	CNetData c;
	c.Prepare(buf + idx, sizeof(buf));

	c.DelString(data);
	idx += c.m_iPos;

	return *this;
}