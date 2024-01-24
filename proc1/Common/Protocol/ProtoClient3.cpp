#include "stdafx.h"
#include "ProtoClient3.h"
#include "ILogHelper.h"

static int EncodeEffectAppearNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_EffectAppearNtf);
    ENCODE_WORD(num);
    for (int i = 0; i < pstIn->num; ++i) {
        if (EncodeEFFECT_POINT(&pstIn->info, poNetData) == -1) return -1;
    }
    ENCODE_WORD(type);
    END_ENCODE();
}

static int DecodeEffectAppearNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_EffectAppearNtf);
    DECODE_WORD(num);
    for (int i = 0; i < pstOut->num; ++i) {
        if (DecodeEFFECT_POINT(&pstOut->info, poNetData) == -1) return -1;
    }
    DECODE_WORD(type);
    END_DECODE();
}

static int EncodeEffectDisAppearNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_EffectDisAppearNtf);
    ENCODE_WORD(num);
    for (int i = 0; i < pstIn->num; ++i) {
        if (EncodeEFFECT_POINT(&pstIn->info, poNetData) == -1) return -1;
    }
    ENCODE_WORD(type);
    END_ENCODE();
}

static int DecodeEffectDisAppearNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_EffectDisAppearNtf);
    DECODE_WORD(num);
    for (int i = 0; i < pstOut->num; ++i) {
        if (DecodeEFFECT_POINT(&pstOut->info, poNetData) == -1) return -1;
    }
    DECODE_WORD(type);
    END_DECODE();
}

static int EncodeGoodsPostRecordAck (void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_GoodsPostRecordAck);
    ENCODE_STRING(order_no);
    END_ENCODE();
}

static int DecodeGoodsPostRecordAck (void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_GoodsPostRecordAck);
    DECODE_STRING(order_no);
    END_ENCODE();
}

static int EncodeSendGoodsPostRecordToClient(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_SendGoodsPostRecordToClient);
    if (EncodeGOODS_ISSUE_RECORD(&pstIn->record, poNetData) == -1) return -1;
    END_ENCODE();
}

static int DecodeSendGoodsPostRecordToClient(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_SendGoodsPostRecordToClient);
    if (DecodeGOODS_ISSUE_RECORD(&pstOut->record, poNetData) == -1) return -1;
    END_ENCODE();
}

static int EncodeTitleGetListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_TitleGetListReq);
    END_ENCODE();
}

static int DecodeTitleGetListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_TitleGetListReq);
    END_ENCODE();
}

static int EncodeMonsterBackNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_MonsterBackNtf);
    ENCODE_QWORD(guid);
    ENCODE_WORD(status);
    END_ENCODE();
}

static int DecodeMonsterBackNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_MonsterBackNtf);
    DECODE_QWORD(guid);
    DECODE_WORD(status);
    END_ENCODE();
}

static int EncodeItemTip(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ItemTip);
    ENCODE_QWORD(owner_guid);
    ENCODE_QWORD(item_guid);
    END_ENCODE();
}

static int DecodeItemTip(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ItemTip);
    DECODE_QWORD(owner_guid);
    DECODE_QWORD(item_guid);
    END_ENCODE();
}

static int EncodeItemTipNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ItemTipNtf);
    if (-1 == EnCodeITEM_INFO(&pstIn->info, poNetData))
        return -1;
    END_ENCODE();
}

static int DecodeItemTipNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ItemTipNtf);
    if (-1 == DeCodeITEM_INFO(&pstOut->info, poNetData))
        return -1;
    END_ENCODE();
}

static int EncodeGetNpcPosReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_GetNpcPosReq);
    ENCODE_STRING(name);
    END_ENCODE();
}

static int DecodeGetNpcPosReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_GetNpcPosReq);
    DECODE_STRING(name);
    END_ENCODE();
}

static int EncodeGetNpcPosAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_GetNpcPosAck);
    ENCODE_WORD(posx);
    ENCODE_WORD(posy);
    ENCODE_BYTE(result);
    END_ENCODE();
}

static int DecodeGetNpcPosAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_GetNpcPosAck);
    DECODE_WORD(posx);
    DECODE_WORD(posy);
    DECODE_BYTE(result);
    END_ENCODE();
}

static int EncodeTradeMallListUpdate(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_TradeMallListUpdate);
    ENCODE_BYTE(item_count);

    int maxCount = std::min<int>((int)pstIn->item_count, (int)_countof(pstIn->item_list));
    for (int i = 0; i < pstIn->item_count; ++i) {
        if (-1 == EnCodeMALL_ITEM_INFO(&pstIn->item_list[i], poNetData))
            return -1;
    }

    END_ENCODE();
}

static int DecodeTradeMallListUpdate(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_TradeMallListUpdate);
    DECODE_BYTE(item_count);

    int maxCount = std::min<int>((int)pstOut->item_count, (int)_countof(pstOut->item_list));
    for (int i = 0; i < pstOut->item_count; ++i) {
        if (-1 == DeCodeMALL_ITEM_INFO(&pstOut->item_list[i], poNetData))
            return -1;
    }

    END_ENCODE();
}

static int EnCodeGMCommandReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_GMCommandReq);
    ENCODE_INT(sn);
    ENCODE_STRING(cmd);
    ENCODE_STRING(param);
    END_ENCODE();
}

static int DeCodeGMCommandReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_GMCommandReq);
    DECODE_INT(sn);
    DECODE_STRING(cmd);
    DECODE_STRING(param);
    END_DECODE();
}

static int EnCodeGoldTake(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_GoldTake);
    ENCODE_INT64(gold);
    END_ENCODE();
}

static int DeCodeGoldTake(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_GoldTake);
    DECODE_INT64(gold);
    END_DECODE();
}

static int EnCodeGoldDeposit(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_GoldDeposit);
    ENCODE_INT64(gold);
    END_ENCODE();
}

static int DeCodeGoldDeposit(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_GoldDeposit);
    DECODE_INT64(gold);
    END_DECODE();
}

static int EnCodeGlobalNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_GlobalNtf);
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
    BEGIN_DECODE_EX(ProtoClient3_GlobalNtf);
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

static int EnCodeQuickBarSet(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_QuickBarSet);
    ENCODE_BYTE(type);
    ENCODE_BYTE(slot);
    ENCODE_WORD(id);
    ENCODE_QWORD(guid);
    END_ENCODE();
}

static int DeCodeQuickBarSet(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_QuickBarSet);
    DECODE_BYTE(type);
    DECODE_BYTE(slot);
    DECODE_WORD(id);
    DECODE_QWORD(guid);
    END_DECODE();
}

static int EnCodeQuickBarSetNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_QuickBarSetNtf);
    ENCODE_WORD(num);

    for (uint16_t i = 0; i < pstIn->num; ++i)
        if (EnCodeQUICK_BAR_INFO(pstIn->info + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DeCodeQuickBarSetNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_QuickBarSetNtf);
    DECODE_WORD(num);

    for (uint16_t i = 0; i < pstOut->num; ++i)
        if (DeCodeQUICK_BAR_INFO(pstOut->info + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EnCodePlayerReliveReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_PlayerReliveReq);
    ENCODE_BYTE(relive_type);
    END_ENCODE();
}

static int DeCodePlayerReliveReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_PlayerReliveReq);
    DECODE_BYTE(relive_type);
    END_DECODE();
}

static int EnCodePlayerReliveAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_PlayerReliveAck);
    ENCODE_BYTE(relive_type);
    ENCODE_INT(error_code);
    END_ENCODE();
}

static int DeCodePlayerReliveAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_PlayerReliveAck);
    DECODE_BYTE(relive_type);
    DECODE_INT(error_code);
    END_DECODE();
}

static int EncodeItemPickUp(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ItemPickUp);
    END_ENCODE();
}
static int DecodeItemPickUp(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ItemPickUp);
    END_DECODE();
}

static int EncodeItemAppearNtf4(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ItemAppearNtf4);
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
    END_ENCODE();
}
static int DecodeItemAppearNtf4(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ItemAppearNtf4);
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
    END_DECODE();
}

static int EncodeItemDestroyAck(void* pHost, CNetData* poNetData)
{

    BEGIN_ENCODE_EX(ProtoClient3_ItemDestroyAck);
    ENCODE_QWORD(item_guid);
    END_ENCODE();

}
static int DecodeItemDestroyAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ItemDestroyAck);
    DECODE_QWORD(item_guid);
    END_DECODE();
}

static int EncodeItemUpdateNtf(void* pHost, CNetData* poNetData)
{

    BEGIN_ENCODE_EX(ProtoClient3_ItemUpdateNtf);
    if (-1 == EnCodeITEM_INFO(&pstIn->info, poNetData))return -1;
    END_ENCODE();

}
static int DecodeItemUpdateNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ItemUpdateNtf);
    if (-1 == DeCodeITEM_INFO(&pstOut->info, poNetData))return -1;
    END_DECODE();
}


static int EncodeItemApply(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ItemApply);
    ENCODE_QWORD(item_guid);
    ENCODE_DWORD(num);
    END_ENCODE();

}

static int DecodeItemApply(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ItemApply);
    DECODE_QWORD(item_guid);
    DECODE_DWORD(num);
    END_DECODE();
}


static int EncodeItemDrop(void* pHost, CNetData* poNetData)
{

    BEGIN_ENCODE_EX(ProtoClient3_ItemDrop);
    ENCODE_QWORD(item_guid);
    END_ENCODE();

}
static int DecodeItemDrop(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ItemDrop);
    DECODE_QWORD(item_guid);
    END_DECODE();
}

static int EnCodeRoleDynAttrNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_RoleDynAttrNtf);
    ENCODE_QWORD(role_guid);
    if (EnCodeCUSTOM_INFO(&pstIn->custom, poNetData) == -1)
        return -1;

    END_ENCODE();
}

static int DeCodeRoleDynAttrNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_RoleDynAttrNtf);
    DECODE_QWORD(role_guid);
    if (-1 == DeCodeCUSTOM_INFO(&pstOut->custom, poNetData))
        return -1;

    END_DECODE();
}

static int EnCodeRoleInfoChangeNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_RoleInfoChangeNtf);
    ENCODE_QWORD(role_guid);
    ENCODE_WORD(num);
    if (EnCodeCUSTOM_INFO(&pstIn->custom, poNetData) == -1)
        return -1;

    END_ENCODE();
}

static int DeCodeRoleInfoChangeNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_RoleInfoChangeNtf);
    DECODE_QWORD(role_guid);
    DECODE_WORD(num);
    if (-1 == DeCodeCUSTOM_INFO(&pstOut->custom, poNetData))
        return -1;

    END_DECODE();
}

static int EnCodeRoleCustVarReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_RoleCustVarReq);
    ENCODE_QWORD(role_guid);
    END_ENCODE();
}

static int DeCodeRoleCustVarReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_RoleCustVarReq);
    DECODE_QWORD(role_guid);
    END_DECODE();
}

static int EnCodeRoleCustVarNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_RoleCustVarNtf);
    ENCODE_QWORD(role_guid);
    if (EnCodeCUSTOM_INFO(&pstIn->custom, poNetData) == -1)
        return -1;
    ENCODE_BYTE(type);

    END_ENCODE();
}

static int DeCodeRoleCustVarNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_RoleCustVarNtf);
    DECODE_QWORD(role_guid);
    if (-1 == DeCodeCUSTOM_INFO(&pstOut->custom, poNetData))
        return -1;
    DECODE_BYTE(type);

    END_DECODE();
}

static int EnCodeRoleAttrExtNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_RoleAttrExtNtf);
    ENCODE_QWORD(player_guid);
    ENCODE_WORD(num);
    ENCODE_BLOB(attr_name, pstIn->num * sizeof(uint16_t));
    ENCODE_BLOB(attr_value, pstIn->num * sizeof(int64_t));
    END_ENCODE();
}

static int DeCodeRoleAttrExtNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_RoleAttrExtNtf);
    DECODE_QWORD(player_guid);
    DECODE_WORD(num);
    DECODE_BLOB(attr_name, pstOut->num * sizeof(uint16_t));
    DECODE_BLOB(attr_value, pstOut->num * sizeof(int64_t));
    END_DECODE();
}

static int EnCodeRoleAttrNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_RoleAttrNtf);
    ENCODE_QWORD(role_guid);
    ENCODE_WORD(num);
    ENCODE_BLOB(attr_name, pstIn->num * sizeof(uint16_t));
    ENCODE_BLOB(attr_value, pstIn->num * sizeof(int));
    END_ENCODE();
}

static int DeCodeRoleAttrNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_RoleAttrNtf);
    DECODE_QWORD(role_guid);
    DECODE_WORD(num);
    DECODE_BLOB(attr_name, pstOut->num * sizeof(uint16_t));
    DECODE_BLOB(attr_value, pstOut->num * sizeof(int));
    END_DECODE();
}

static int EncodeItemMove(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ItemMove);
    ENCODE_QWORD(item_guid);
    ENCODE_WORD(dest_site);
    END_ENCODE();
}

static int DecodeItemMove(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ItemMove);
    DECODE_QWORD(item_guid);
    DECODE_WORD(dest_site);
    END_DECODE();
}

static int EncodeItemSplit(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ItemSplit);
    ENCODE_QWORD(item_guid);
    ENCODE_WORD(item_amount);
    ENCODE_WORD(dest_site);
    END_ENCODE();
}

static int DecodeItemSplit(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ItemSplit);
    DECODE_QWORD(item_guid);
    DECODE_WORD(item_amount);
    DECODE_WORD(dest_site);
    END_DECODE();
}

static int EncodeItemArrange(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ItemArrange);
    ENCODE_BYTE(type);
    END_ENCODE();
}

static int DecodeItemArrange(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ItemArrange);
    DECODE_BYTE(type);
    END_DECODE();
}

static int EncodeItemAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ItemAddAck);
    ENCODE_CHAR(isPackItem);
    if (-1 == EnCodeITEM_INFO(&pstIn->info, poNetData))return -1;
    END_ENCODE();
}

static int DecodeItemAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ItemAddAck);
    DECODE_CHAR(isPackItem);
    if (-1 == DeCodeITEM_INFO(&pstOut->info, poNetData))return -1;
    END_DECODE();
}

static int EncodeObjdisAppearNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ObjDisappearNtf);
    ENCODE_QWORD(obj_guid);
    END_ENCODE();
}

static int DecodeObjdisAppearNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ObjDisappearNtf);
    DECODE_QWORD(obj_guid);
    END_DECODE();
}

static int EncodeNpcAppearNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_NpcAppearNtf);
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
    BEGIN_DECODE_EX(ProtoClient3_NpcAppearNtf);
    DECODE_QWORD(npc_guid);
    DECODE_WORD(template_id);
    DECODE_WORD(dst_x);
    DECODE_WORD(dst_y);
    DECODE_BYTE(dir);
    DECODE_STRING(name);
    DECODE_DWORD(modelid);
    END_DECODE();
}

static int EncodeNpcSelect(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_NpcSelect);
    ENCODE_QWORD(npc_guid);
    END_ENCODE();
}

static int DecodeNpcSelect(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_NpcSelect);
    DECODE_QWORD(npc_guid);
    END_DECODE();
}

static int EncodeNpcTalkReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_NpcTalkReq);
    ENCODE_QWORD(npc_guid);
    ENCODE_STRING(func);
    END_ENCODE();
}

static int DecodeNpcTalkReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_NpcTalkReq);
    DECODE_QWORD(npc_guid);
    DECODE_STRING(func);
    END_DECODE();
}

static int EncodeTradeNpcBuy(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_TradeNpcBuy);
    ENCODE_WORD(shop_id);
    ENCODE_WORD(item_index);
    ENCODE_WORD(item_amount);
    ENCODE_BYTE(is_bind);
    END_ENCODE();
}

static int DecodeTradeNpcBuy(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_TradeNpcBuy);
    DECODE_WORD(shop_id);
    DECODE_WORD(item_index);
    DECODE_WORD(item_amount);
    DECODE_BYTE(is_bind);
    END_DECODE();
}

static int EncodeTradeNpcShopNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_TradeNpcShopNtf);
    ENCODE_WORD(shop_id);
    ENCODE_BYTE(item_count);
    for (uint8_t i = 0; i < pstIn->item_count; ++i)
        if (EnCodeSHOP_ITEM_INFO(pstIn->item_list + i, poNetData) == -1)
            return -1;
    END_ENCODE();
}

static int DecodeTradeNpcShopNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_TradeNpcShopNtf);
    DECODE_WORD(shop_id);
    DECODE_BYTE(item_count);
    for (uint8_t i = 0; i < pstOut->item_count; ++i)
        if (DeCodeSHOP_ITEM_INFO(pstOut->item_list + i, poNetData) == -1)
            return -1;
    END_DECODE();
}

static int EncodeMonsterAppearNtf6(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_MonsterAppearNtf6);
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
    ENCODE_DWORD(modelid);
    ENCODE_WORD(reserve_num);
    ENCODE_INTARRAY(reserve_values, pstIn->reserve_num);
    ENCODE_STRING(name_color);
    END_ENCODE();
}

static int DecodeMonsterAppearNtf6(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_MonsterAppearNtf6);
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
    DECODE_DWORD(modelid);
    DECODE_WORD(reserve_num);
    DECODE_INTARRAY(reserve_values, pstOut->reserve_num);
    DECODE_STRING(name_color);
    END_DECODE();
}


static int EncodeExitReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ExitGSReq);
    ENCODE_BYTE(exittype);
    END_ENCODE();
}

static int DecodeExitReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ExitGSReq);
    DECODE_BYTE(exittype);
    END_DECODE();
}

static int EncodeExitAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ExitGSAck);
    ENCODE_BYTE(exittype);
    ENCODE_INT(errcode);
    ENCODE_STRING(errmsg);   
    END_ENCODE();
}

static int DecodeExitAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ExitGSAck);
    DECODE_BYTE(exittype);
    DECODE_INT(errcode);
    DECODE_STRING(errmsg);
    END_DECODE();
}


static int EncodeMoveNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_MoveNtf);
    ENCODE_QWORD(guid);
    ENCODE_BYTE(type);
    ENCODE_WORD(dst_x);
    ENCODE_WORD(dst_y);
    END_ENCODE();
}

static int DecodeMoveNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_MoveNtf);
    DECODE_QWORD(guid);
    DECODE_BYTE(type);
    DECODE_WORD(dst_x);
    DECODE_WORD(dst_y);
 
    END_DECODE();
}

static int EncodeMoveReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_MoveReq);
    ENCODE_QWORD(role_guid);
    ENCODE_BYTE(type);
    ENCODE_WORD(dst_x);
    ENCODE_WORD(dst_y);
    ENCODE_DWORD(idx);
    END_ENCODE();
}

static int DecodeMoveReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_MoveReq);
    DECODE_QWORD(role_guid);
    DECODE_BYTE(type);
    DECODE_WORD(dst_x);
    DECODE_WORD(dst_y);
    DECODE_DWORD(idx);
    END_DECODE();
}

static int EncodeMoveAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_MoveAck);
    ENCODE_QWORD(role_guid);
    ENCODE_BYTE(ret);
    ENCODE_BYTE(type);
    ENCODE_WORD(dst_x);
    ENCODE_WORD(dst_y);
    ENCODE_DWORD(idx);
    END_ENCODE();
}

static int DecodeMoveAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_MoveAck);
    DECODE_QWORD(role_guid);
    DECODE_BYTE(ret);
    DECODE_BYTE(type);
    DECODE_WORD(dst_x);
    DECODE_WORD(dst_y);
    DECODE_DWORD(idx);
    END_DECODE();
}

static int EncodeTurnReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_TurnReq);
    ENCODE_QWORD(role_guid);
    ENCODE_BYTE(dir);
    END_ENCODE();
}

static int DecodeTurnReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_TurnReq);
    DECODE_QWORD(role_guid);
    DECODE_BYTE(dir);
    END_DECODE();
}

static int EncodeTurnNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_TurnNtf);
    ENCODE_QWORD(guid);
    ENCODE_BYTE(dir);
    END_ENCODE();
}

static int DecodeTurnNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_TurnNtf);
    DECODE_QWORD(guid);
    DECODE_BYTE(dir);
    END_DECODE();
}

static int EncodeObjDieNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ObjDieNtf);
    ENCODE_QWORD(die_guid);
    ENCODE_QWORD(kill_guid);
    ENCODE_STRING(kill_name);
    END_ENCODE();
}

static int DecodeObjDieNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ObjDieNtf);
    DECODE_QWORD(die_guid);
    DECODE_QWORD(kill_guid);
    DECODE_STRING(kill_name);
    END_DECODE();
}

static int EncodeSkillAddAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_SkillAddAck);
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
    BEGIN_DECODE_EX(ProtoClient3_SkillAddAck);
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
    BEGIN_ENCODE_EX(ProtoClient3_SkillDeleteAck);
    ENCODE_WORD(id);
    END_ENCODE();
}

static int DecodeSkillDeleteAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_SkillDeleteAck);
    DECODE_WORD(id);
    END_DECODE();
}

static int EncodeSkillSwitch(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_SkillSwitch);
    ENCODE_WORD(id);
    ENCODE_BYTE(active);
    END_ENCODE();
}

static int DecodeSkillSwitch(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_SkillSwitch);
    DECODE_WORD(id);
    DECODE_BYTE(active);
    END_DECODE();
}

static int EncodeSkillSwitchAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_SkillSwitchAck);
    ENCODE_WORD(id);
    ENCODE_BYTE(active);
    END_ENCODE();
}

static int DecodeSkillSwitchAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_SkillSwitchAck);
    DECODE_WORD(id);
    DECODE_BYTE(active);
    END_DECODE();
}

static int EncodeSkillProficiencyNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_SkillProficiencyNtf);
    ENCODE_WORD(id);
    ENCODE_DWORD(proficiency);
    END_ENCODE();
}

static int DecodeSkillProficiencyNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_SkillProficiencyNtf);
    DECODE_WORD(id);
    DECODE_DWORD(proficiency);
    END_DECODE();
}

static int EncodeBuffAddAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_BuffAddAck);
    ENCODE_QWORD(role_guid);
    ENCODE_WORD(num);

    for (uint16_t i = 0; i < pstIn->num; ++i)
        if (EnCodeBUFF_INFO(pstIn->info + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeBuffAddAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_BuffAddAck);
    DECODE_QWORD(role_guid);
    DECODE_WORD(num);

    for (uint16_t i = 0; i < pstOut->num; ++i)
        if (EnCodeBUFF_INFO(pstOut->info + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodeBuffDestroyAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_BuffDestroyAck);
    ENCODE_QWORD(role_guid);
    ENCODE_WORD(id);
    END_ENCODE();
}

static int DecodeBuffDestroyAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_BuffDestroyAck);
    DECODE_QWORD(role_guid);
    DECODE_WORD(id);
    END_DECODE();
}

static int EncodeSpellTarget(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_SpellTarget);
    ENCODE_QWORD(role_guid);
    ENCODE_WORD(id);
    ENCODE_QWORD(target);
    ENCODE_WORD(idx);
    END_ENCODE();
}

static int DecodeSpellTarget(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_SpellTarget);
    DECODE_QWORD(role_guid);
    DECODE_WORD(id);
    DECODE_QWORD(target);
    DECODE_WORD(idx);
    END_DECODE();
}

static int EncodeSpellGrid(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_SpellGrid);
    ENCODE_QWORD(role_guid);
    ENCODE_WORD(id);
    ENCODE_WORD(target_x);
    ENCODE_WORD(target_y);
    ENCODE_WORD(idx);
    ENCODE_QWORD(ref_target);
    ENCODE_BYTE(extra);
    END_ENCODE();
}

static int DecodeSpellGrid(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_SpellGrid);
    DECODE_QWORD(role_guid);
    DECODE_WORD(id);
    DECODE_WORD(target_x);
    DECODE_WORD(target_y);
    DECODE_WORD(idx);
    DECODE_QWORD(ref_target);
    DECODE_BYTE(extra);
    END_DECODE();
}

static int EncodeSpellAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_SpellAck);
    ENCODE_QWORD(role_guid);
    ENCODE_WORD(id);
    ENCODE_INT(ecode);
    ENCODE_STRING(detail);
    ENCODE_WORD(idx);
    END_ENCODE();
}

static int DecodeSpellAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_SpellAck);
    DECODE_QWORD(role_guid);
    DECODE_WORD(id);
    DECODE_INT(ecode);
    DECODE_STRING(detail);
    DECODE_WORD(idx);
    END_DECODE();
}

static int EncodeSpellNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_SpellNtf);
    ENCODE_QWORD(actor);
    ENCODE_WORD(id);
    ENCODE_WORD(target_x);
    ENCODE_WORD(target_y);
    ENCODE_WORD(num);
    for (uint16_t i = 0; i < pstIn->num; ++i) {
        ENCODE_QWORD(targets[i]);
    }
    ENCODE_BYTE(extra);
    END_ENCODE();
}

static int DecodeSpellNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_SpellNtf);
    DECODE_QWORD(actor);
    DECODE_WORD(id);
    DECODE_WORD(target_x);
    DECODE_WORD(target_y);
    DECODE_WORD(num);
    for (uint16_t i = 0; i < pstOut->num; ++i) {
        DECODE_QWORD(targets[i]);
    }
    DECODE_BYTE(extra);
    END_DECODE();
}

static  int EncodeEnterGSReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_EnterGSReq);
    ENCODE_CHAR(entertype);
    ENCODE_CHAR(fangchenmi);
    ENCODE_CHAR(clienttype);
    if (-1 == EnCodeROLE_BRIEF_INFO(&pstIn->roleBriefInfo, poNetData)) return -1;
    END_ENCODE();
}

static  int DecodeEnterGSReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_EnterGSReq);
    DECODE_CHAR(entertype);
    DECODE_CHAR(fangchenmi);
    DECODE_CHAR(clienttype);
    if (-1 == DeCodeROLE_BRIEF_INFO(&pstOut->roleBriefInfo, poNetData)) return -1;
    END_DECODE();
}


//unsigned char             entertype; //进入类型 0=上线 1=跳服
//uint64_t                  roleguid; //角色guid
//unsigned int              gsobjid; //客户端在GS上的objid
//int                       errcode; //错误码
//char                      errmsg[256]; //错误描述
static  int EncodeEnterGSACK(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_EnterMSAck);
    ENCODE_BYTE(entertype);
    ENCODE_QWORD(roleguid);
    ENCODE_DWORD(gsobjid);
    ENCODE_INT(errcode);
    ENCODE_STRING(errmsg);
    END_ENCODE();
}

static  int DecodeEnterGSACK(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_EnterMSAck);
    DECODE_BYTE(entertype);
    DECODE_QWORD(roleguid);
    DECODE_DWORD(gsobjid);
    DECODE_INT(errcode);
    DECODE_STRING(errmsg);
    END_DECODE();
}

static  int EncodeEnterGSNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_EnterGSNTF);
    ENCODE_QWORD(mapcode);
    ENCODE_STRING(logic);
    ENCODE_WORD(view_x);
    ENCODE_WORD(view_y);
    ENCODE_WORD(width);
    ENCODE_WORD(height);
    END_ENCODE();
}

static  int DecodeEnterGSNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_EnterGSNTF);
    DECODE_QWORD(mapcode);
    DECODE_STRING(logic);
    DECODE_WORD(view_x);
    DECODE_WORD(view_y);
    DECODE_WORD(width);
    DECODE_WORD(height);
    END_DECODE();
}


static int EncodePlayerAppearNtf3(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_PlayerAppearNtf3);
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
    END_ENCODE();
}

static int DecodePlayerAppearNtf3(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_PlayerAppearNtf3);
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
    END_DECODE();
}

static int EncodeAttrShowNtf2Ex2(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_AttrShowNtfEx2);
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
    for (uint16_t i = 0; i < pstIn->reserve_size; ++i)
        ENCODE_DWORD(reserve[i]);
    END_ENCODE();
}

static int DecodeAttrShowNtf2Ex2(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_AttrShowNtfEx2);
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
    for (uint16_t i = 0; i < pstOut->reserve_size; ++i)
        DECODE_DWORD(reserve[i]);
    END_DECODE();
}

static int EncodeKickRoleNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_KickRoleNtf);
    ENCODE_INT(errcode);
    ENCODE_STRING(errmsg);
    END_ENCODE();
}

static int DecodeKickRoleNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_KickRoleNtf);
    DECODE_INT(errcode);
    DECODE_STRING(errmsg);
    END_DECODE();
}

static int EncodeItemAttrNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ItemAttrNtf);
    ENCODE_QWORD(item_guid);
    ENCODE_DWORD(attr_name);
    ENCODE_INT(attr_value);
    END_ENCODE();
}

static int DecodeItemAttrNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ItemAttrNtf);
    DECODE_QWORD(item_guid);
    DECODE_DWORD(attr_name);
    DECODE_INT(attr_value);
    END_DECODE();
}

static int EncodeRoleAppNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_RoleAppNtf2);
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

static int DecodeRoleAppNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_RoleAppNtf2);
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

static int EncodeSkillCDChangedNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_SkillCDChangedNtf);
    ENCODE_WORD(skill_id);
    ENCODE_DWORD(new_cd);
    END_ENCODE();
}

static int DecodeSkillCDChangedNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_SkillCDChangedNtf);
    DECODE_WORD(skill_id);
    DECODE_DWORD(new_cd);
    END_DECODE();
}

static int EncodeSkillPropPermanentChangedNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_SkillPropPermanentChangedNtf);
    ENCODE_QWORD(player_guid);
    ENCODE_WORD(num);
    for (int i = 0; i < pstIn->num; ++i)
        if (EnCodeSKILL_INFO(pstIn->info + i, poNetData) == -1)
            return -1;
    END_ENCODE();
}

static int DecodeSkillPropPermanentChangedNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_SkillPropPermanentChangedNtf);
    DECODE_QWORD(player_guid);
    DECODE_WORD(num);
    for (int i = 0; i < pstOut->num; ++i)
        if (DeCodeSKILL_INFO(pstOut->info + i, poNetData) == -1)
            return -1;
    END_DECODE();
}

static int EncodeRunServScriptReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_RunServScriptReq);
    ENCODE_DWORD(form_count);
    ENCODE_BLOB(script_name, 256);
    ENCODE_BLOB(function_name, 256);
    ENCODE_WORD(num);

    for (uint16_t i = 0; i < pstIn->num; ++i)
        if (EnCodePARAM_INFO2(pstIn->info + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeRunServScriptReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_RunServScriptReq);
    DECODE_DWORD(form_count);
    DECODE_BLOB(script_name, 256);
    DECODE_BLOB(function_name, 256);
    DECODE_WORD(num);

    for (uint16_t i = 0; i < pstOut->num; ++i)
        if (DeCodePARAM_INFO2(pstOut->info + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodeRunServScriptAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_RunServScriptAck);
    ENCODE_STRING(script_name);
    ENCODE_STRING(result);
    END_ENCODE();
}

static int DecodeRunServScriptAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_RunServScriptAck);
    DECODE_STRING(script_name);
    DECODE_STRING(result);
    END_DECODE();
}

static int EncodeRunClientScript(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_RunClientScript);
    ENCODE_STRING(form_name);
    ENCODE_WORD(size);
    ENCODE_BLOB(form_content, pstIn->size);
    ENCODE_BYTE(comp);
    END_ENCODE();
}

static int DecodeRunClientScript(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_RunClientScript);
    DECODE_STRING(form_name);
    DECODE_WORD(size);
    DECODE_BLOB(form_content, pstOut->size);
    DECODE_BYTE(comp);
    END_DECODE();
}

static int EncodeTradeMallListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_TradeMallListReq);
    ENCODE_BYTE(page_id);
    END_ENCODE();
}

static int DecodeTradeMallListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_TradeMallListReq);
    DECODE_BYTE(page_id);
    END_DECODE();
}

static int EncodeTradeMallListAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_TradeMallListAck);
    ENCODE_BYTE(page_id);
    ENCODE_BYTE(item_count);

    int maxCount = std::min<int>((int)pstIn->item_count, (int)_countof(pstIn->item_list));
    for (int i = 0; i < pstIn->item_count; ++i) {
        if (-1 == EnCodeMALL_ITEM_INFO(&pstIn->item_list[i], poNetData))
            return -1;
    }

    END_ENCODE();
}

static int DecodeTradeMallListAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_TradeMallListAck);
    DECODE_BYTE(page_id);
    DECODE_BYTE(item_count);

    int maxCount = std::min<int>((int)pstOut->item_count, (int)_countof(pstOut->item_list));
    for (int i = 0; i < pstOut->item_count; ++i) {
        if (-1 == DeCodeMALL_ITEM_INFO(&pstOut->item_list[i], poNetData))
            return -1;
    }

    END_ENCODE();
}

static int EncodeTradeMallBuy(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_TradeMallBuy);
    ENCODE_DWORD(item_index);
    ENCODE_WORD(item_amount);
    END_ENCODE();
}

static int DecodeTradeMallBuy(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_TradeMallBuy);
    DECODE_DWORD(item_index);
    DECODE_WORD(item_amount);
    END_DECODE();
}

static int EncodeAtkModeReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_AtkModeReq);
    ENCODE_BYTE(atk_mode);
    END_ENCODE();
}

static int DecodeAtkModeReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_AtkModeReq);
    DECODE_BYTE(atk_mode);
    END_DECODE();
}

static int EncodeQuestQueryCanAccept(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_QuestQueryCanAccept);
    END_ENCODE();
}

static int DecodeQuestQueryCanAccept(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_QuestQueryCanAccept);
    END_DECODE();
}

static int EncodeQuestQueryCanAcceptNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_QuestQueryCanAcceptNtf);
    ENCODE_WORD(num);
    for (uint16_t i = 0; i < pstIn->num; ++i) {
        ENCODE_WORD(quests[i]);
    }
    END_ENCODE();
}

static int DecodeQuestQueryCanAcceptNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_QuestQueryCanAcceptNtf);
    DECODE_WORD(num);
    for (uint16_t i = 0; i < pstOut->num; ++i) {
        DECODE_WORD(quests[i]);
    }
    END_DECODE();
}

static int EncodeQuestAccept(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_QuestAccept);
    ENCODE_WORD(quest_id);
    END_ENCODE();
}

static int DecodeQuestAccept(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_QuestAccept);
    DECODE_WORD(quest_id);
    END_DECODE();
}

static int EncodeQuestAddNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_QuestAddNtf);
    ENCODE_WORD(quest_id);
    ENCODE_STRING(quest_name);
    ENCODE_BYTE(quest_type);

    ENCODE_WORD(group_huntings_len);
    for (uint16_t i = 0; i < pstIn->group_huntings_len; ++i)
        if (EnCodeQUEST_HUNTING_INFO(pstIn->group_huntings + i, poNetData) == -1)
            return -1;

    ENCODE_WORD(huntings_len);
    for (uint16_t i = 0; i < pstIn->huntings_len; ++i)
        if (EnCodeQUEST_HUNTING_INFO(pstIn->huntings + i, poNetData) == -1)
            return -1;

    ENCODE_WORD(huntlevels_len);
    for (uint16_t i = 0; i < pstIn->huntlevels_len; ++i)
        if (EnCodeQUEST_HUNTLEVEL_INFO(pstIn->huntlevels + i, poNetData) == -1)
            return -1;

    ENCODE_WORD(group_items_len);
    for (uint16_t i = 0; i < pstIn->group_items_len; ++i)
        if (EnCodeQUEST_ITEM_INFO(pstIn->group_items + i, poNetData) == -1)
            return -1;

    ENCODE_WORD(collect_items_len);
    for (uint16_t i = 0; i < pstIn->collect_items_len; ++i)
        if (EnCodeQUEST_ITEM_INFO(pstIn->collect_items + i, poNetData) == -1)
            return -1;

    ENCODE_WORD(apply_items_len);
    for (uint16_t i = 0; i < pstIn->apply_items_len; ++i)
        if (EnCodeQUEST_ITEM_INFO(pstIn->apply_items + i, poNetData) == -1)
            return -1;

    ENCODE_WORD(npcs_len);
    for (uint16_t i = 0; i < pstIn->npcs_len; ++i)
        if (EnCodeQUEST_NPC_INFO(pstIn->npcs + i, poNetData) == -1)
            return -1;

    ENCODE_BYTE(track_enabled);
    ENCODE_DWORD(life);
    ENCODE_STRING(progressing);
    ENCODE_STRING(accomplishing);
    END_ENCODE();
}

static int DecodeQuestAddNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_QuestAddNtf);
    DECODE_WORD(quest_id);
    DECODE_STRING(quest_name);
    DECODE_BYTE(quest_type);

    DECODE_WORD(group_huntings_len);
    for (uint16_t i = 0; i < pstOut->group_huntings_len; ++i)
        if (DeCodeQUEST_HUNTING_INFO(pstOut->group_huntings + i, poNetData) == -1)
            return -1;

    DECODE_WORD(huntings_len);
    for (uint16_t i = 0; i < pstOut->huntings_len; ++i)
        if (DeCodeQUEST_HUNTING_INFO(pstOut->huntings + i, poNetData) == -1)
            return -1;

    DECODE_WORD(huntlevels_len);
    for (uint16_t i = 0; i < pstOut->huntlevels_len; ++i)
        if (DeCodeQUEST_HUNTLEVEL_INFO(pstOut->huntlevels + i, poNetData) == -1)
            return -1;

    DECODE_WORD(group_items_len);
    for (uint16_t i = 0; i < pstOut->group_items_len; ++i)
        if (DeCodeQUEST_ITEM_INFO(pstOut->group_items + i, poNetData) == -1)
            return -1;

    DECODE_WORD(collect_items_len);
    for (uint16_t i = 0; i < pstOut->collect_items_len; ++i)
        if (DeCodeQUEST_ITEM_INFO(pstOut->collect_items + i, poNetData) == -1)
            return -1;

    DECODE_WORD(apply_items_len);
    for (uint16_t i = 0; i < pstOut->apply_items_len; ++i)
        if (DeCodeQUEST_ITEM_INFO(pstOut->apply_items + i, poNetData) == -1)
            return -1;

    DECODE_WORD(npcs_len);
    for (uint16_t i = 0; i < pstOut->npcs_len; ++i)
        if (DeCodeQUEST_NPC_INFO(pstOut->npcs + i, poNetData) == -1)
            return -1;

    DECODE_BYTE(track_enabled);
    DECODE_DWORD(life);
    DECODE_STRING(progressing);
    DECODE_STRING(accomplishing);
    END_DECODE();
}

static int EncodeQuestNpcTalkAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_QuestNpcTalkAck);
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
    BEGIN_DECODE_EX(ProtoClient3_QuestNpcTalkAck);
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
    BEGIN_ENCODE_EX(ProtoClient3_QuestTimeoutNtf);
    ENCODE_WORD(quest_id);
    END_ENCODE();
}

static int DecodeQuestTimeoutNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_QuestTimeoutNtf);
    DECODE_WORD(quest_id);
    END_DECODE();
}

static int EnCodePlayerSwitchReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_PlayerSwitchReq);
    ENCODE_BYTE(id);
    ENCODE_BYTE(value);
    END_ENCODE();
}

static int DeCodePlayerSwitchReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_PlayerSwitchReq);
    DECODE_BYTE(id);
    DECODE_BYTE(value);
    END_DECODE();
}

static int EnCodeGetAroundTeamReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_GetAroundTeamReq);
    END_ENCODE();
}

static int DeCodeGetAroundTeamReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_GetAroundTeamReq);
    END_DECODE();
}

static int EnCodeGetAroundTeamAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_GetAroundTeamAck);
    ENCODE_BYTE(list_size);

    for (uint8_t i = 0; i < pstIn->list_size; ++i)
        if (EnCodeTEAM_MEMBER(pstIn->list_data + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DeCodeGetAroundTeamAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_GetAroundTeamAck);
    DECODE_BYTE(list_size);

    for (uint8_t i = 0; i < pstOut->list_size; ++i)
        if (DeCodeTEAM_MEMBER(pstOut->list_data + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodeQuestUpdateNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_QuestUpdateNtf);
    ENCODE_WORD(quest_id);
    ENCODE_INT(data_type);
    ENCODE_INT(id);
    ENCODE_INT(value);
    END_ENCODE();
}

static int DecodeQuestUpdateNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_QuestUpdateNtf);
    DECODE_WORD(quest_id);
    DECODE_INT(data_type);
    DECODE_INT(id);
    DECODE_INT(value);
    END_DECODE();
}

static int EncodeQuestDrop(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_QuestDrop);
    ENCODE_WORD(quest_id);
    END_ENCODE();
}

static int DecodeQuestDrop(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_QuestDrop);
    DECODE_WORD(quest_id);
    END_DECODE();
}

static int EncodeQuestDropNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_QuestDropNtf);
    ENCODE_WORD(quest_id);
    END_ENCODE();
}

static int DecodeQuestDropNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_QuestDropNtf);
    DECODE_WORD(quest_id);
    END_DECODE();
}

static int EncodeQuestAccomplish(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_QuestAccomplish);
    ENCODE_WORD(quest_id);
    ENCODE_WORD(select_index);
    END_ENCODE();
}

static int DecodeQuestAccomplish(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_QuestAccomplish);
    DECODE_WORD(quest_id);
    DECODE_WORD(select_index);
    END_DECODE();
}

static int EncodeQuestStateNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_QuestStateNtf);
    ENCODE_WORD(quest_id);
    ENCODE_BYTE(state);
    END_ENCODE();
}

static int DecodeQuestStateNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_QuestStateNtf);
    DECODE_WORD(quest_id);
    DECODE_BYTE(state);
    END_DECODE();
}

static int EncodeQuestNpcStateNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_QuestNpcStateNtf);
    ENCODE_WORD(npc_id);
    ENCODE_BYTE(state);
    END_ENCODE();
}

static int DecodeQuestNpcStateNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_QuestNpcStateNtf);
    DECODE_WORD(npc_id);
    DECODE_BYTE(state);
    END_DECODE();
}

static int EncodeRoleAttrExtRefNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_RoleAttrExtRefNtf);
    ENCODE_WORD(attr_name);
    ENCODE_INT64(attr_value);
    END_ENCODE();
}

static int DecodeRoleAttrExtRefNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_RoleAttrExtRefNtf);
    DECODE_WORD(attr_name);
    DECODE_INT64(attr_value);
    END_DECODE();
}

static int EncodeLevelUpNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_LevelUpNtf);
    ENCODE_QWORD(player_guid);
    ENCODE_DWORD(level);
    END_ENCODE();
}

static int DecodeLevelUpNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_LevelUpNtf);
    DECODE_QWORD(player_guid);
    DECODE_DWORD(level);
    END_DECODE();
}

static int EncodePlayerQuery(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_PlayerQuery);
    ENCODE_STRING(player_name);
    END_ENCODE();
}

static int DecodePlayerQuery(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_PlayerQuery);
    DECODE_STRING(player_name);
    END_DECODE();
}

static int EncodePlayerQueryNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_PlayerQueryNtf);
    ENCODE_QWORD(player_guid);
    ENCODE_STRING(name);
    ENCODE_BYTE(gender);
    ENCODE_BYTE(job);
    ENCODE_DWORD(level);
    ENCODE_STRING(family_name);
    ENCODE_STRING(family_title);
    ENCODE_STRING(alias);
    ENCODE_WORD(item_num);
    ENCODE_BYTE(isFinalPack);

    for (uint16_t i = 0; i < pstIn->item_num; ++i)
        if (EnCodeITEM_INFO(pstIn->item_info + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodePlayerQueryNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_PlayerQueryNtf);
    DECODE_QWORD(player_guid);
    DECODE_STRING(name);
    DECODE_BYTE(gender);
    DECODE_BYTE(job);
    DECODE_DWORD(level);
    DECODE_STRING(family_name);
    DECODE_STRING(family_title);
    DECODE_STRING(alias);
    DECODE_WORD(item_num);
    DECODE_BYTE(isFinalPack);

    for (uint16_t i = 0; i < pstOut->item_num; ++i)
        if (DeCodeITEM_INFO(pstOut->item_info + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodeTitleAddAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_TitleAddAck);
    if (-1 == EnCodeTITLE_INFO(&pstIn->info, poNetData))
        return -1;
    END_ENCODE();
}

static int DecodeTitleAddAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_TitleAddAck);
    if (-1 == DeCodeTITLE_INFO(&pstOut->info, poNetData))
        return -1;
    END_DECODE();
}

static int EncodeTitleDel(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_TitleDel);
    ENCODE_DWORD(id);
    END_ENCODE();
}

static int DecodeTitleDel(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_TitleDel);
    DECODE_DWORD(id);
    END_DECODE();
}

static int EncodeTitleDelAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_TitleDelAck);
    ENCODE_DWORD(id);
    ENCODE_BYTE(err);
    END_ENCODE();
}

static int DecodeTitleDelAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_TitleDelAck);
    DECODE_DWORD(id);
    DECODE_BYTE(err);
    END_DECODE();
}

static int EncodeTitleWear(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_TitleWear);
    ENCODE_DWORD(id);
    END_ENCODE();
}

static int DecodeTitleWear(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_TitleWear);
    DECODE_DWORD(id);
    END_DECODE();
}

static int EncodeTitleUnWear(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_TitleUnWear);
    ENCODE_DWORD(id);
    END_ENCODE();
}

static int DecodeTitleUnWear(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_TitleUnWear);
    DECODE_DWORD(id);
    END_DECODE();
}

static int EncodeTitleWearNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_TitleWearNtf);
    ENCODE_DWORD(id);
    ENCODE_QWORD(guid);
    END_ENCODE();
}

static int DecodeTitleWearNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_TitleWearNtf);
    DECODE_DWORD(id);
    DECODE_QWORD(guid);
    END_DECODE();
}

static int EncodeTitleUnWearNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_TitleUnWearNtf);
    ENCODE_DWORD(id);
    ENCODE_QWORD(guid);
    END_ENCODE();
}

static int DecodeTitleUnWearNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_TitleUnWearNtf);
    DECODE_DWORD(id);
    DECODE_QWORD(guid);
    END_DECODE();
}

static int EncodeTitleList(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_TitleList);
    ENCODE_WORD(num);
    for (int i = 0; i < pstIn->num; ++i) {
        if (-1 == EnCodeTITLE_INFO(pstIn->info + i, poNetData))
            return -1;
    }
    END_ENCODE();
}

static int DecodeTitleList(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_TitleList);
    DECODE_WORD(num);
    for (int i = 0; i < pstOut->num; ++i) {
        if (-1 == DeCodeTITLE_INFO(pstOut->info + i, poNetData))
            return -1;
    }
    END_DECODE();
}

static int EncodePlayerFamilyChangeNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_PlayerFamilyChangeNtf);
    ENCODE_QWORD(player_guid);
    ENCODE_STRING(family_name);
    ENCODE_STRING(castle_name);
    ENCODE_BYTE(title);
    END_ENCODE();
}

static int DecodePlayerFamilyChangeNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_PlayerFamilyChangeNtf);
    DECODE_QWORD(player_guid);
    DECODE_STRING(family_name);
    DECODE_STRING(castle_name);
    DECODE_BYTE(title);
    END_DECODE();
}

static int EncodeRecordsMineReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_RecordsMineReq);
    ENCODE_QWORD(role_id);
    ENCODE_WORD(type);
    END_ENCODE();
}

static int DecodeRecordsMineReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_RecordsMineReq);
    DECODE_QWORD(role_id);
    DECODE_WORD(type);
    END_DECODE();
}

static int EncodeDelegateMineReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_DelegateMineReq);
    ENCODE_QWORD(role_id);
    END_ENCODE();
}

static int DecodeDelegateMineReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_DelegateMineReq);
    DECODE_QWORD(role_id);
    END_DECODE();
}

static int EncodeDelegateSellListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_DelegateSellListReq);
    ENCODE_DWORD(start);
    ENCODE_DWORD(count);
    ENCODE_WORD(type);
    ENCODE_WORD(subtype);
    ENCODE_STRING(item_name);
    ENCODE_BYTE(is_reverse);
    END_ENCODE();
}

static int DecodeDelegateSellListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_DelegateSellListReq);
    DECODE_DWORD(start);
    DECODE_DWORD(count);
    DECODE_WORD(type);
    DECODE_WORD(subtype);
    DECODE_STRING(item_name);
    DECODE_BYTE(is_reverse);
    END_DECODE();
}

static int EncodeDelegateBuyListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_DelegateBuyListReq);
    ENCODE_DWORD(start);
    ENCODE_DWORD(count);
    ENCODE_WORD(type);
    ENCODE_WORD(subtype);
    ENCODE_STRING(item_name);
    ENCODE_BYTE(is_reverse);
    END_ENCODE();
}

static int DecodeDelegateBuyListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_DelegateBuyListReq);
    DECODE_DWORD(start);
    DECODE_DWORD(count);
    DECODE_WORD(type);
    DECODE_WORD(subtype);
    DECODE_STRING(item_name);
    DECODE_BYTE(is_reverse);
    END_DECODE();
}

static int EncodeDelegateCancel(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_DelegateCancel);
    ENCODE_QWORD(trade_id);
    END_ENCODE();
}

static int DecodeDelegateCancel(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_DelegateCancel);
    DECODE_QWORD(trade_id);
    END_DECODE();
}

static int EncodeDelegateSellCmd(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_DelegateSellCmd);
    ENCODE_QWORD(item_guid);
    ENCODE_DWORD(item_value);
    ENCODE_DWORD(item_unit);
    ENCODE_BYTE(value_type);
    END_ENCODE();
}

static int DecodeDelegateSellCmd(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_DelegateSellCmd);
    DECODE_QWORD(item_guid);
    DECODE_DWORD(item_value);
    DECODE_DWORD(item_unit);
    DECODE_BYTE(value_type);
    END_DECODE();
}

static int EncodeDelegateBuyCmd(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_DelegateBuyCmd);
    ENCODE_WORD(item_id);
    ENCODE_DWORD(item_count);
    ENCODE_DWORD(item_value);
    ENCODE_DWORD(item_unit);
    ENCODE_BYTE(value_type);
    END_ENCODE();
}

static int DecodeDelegateBuyCmd(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_DelegateBuyCmd);
    DECODE_WORD(item_id);
    DECODE_DWORD(item_count);
    DECODE_DWORD(item_value);
    DECODE_DWORD(item_unit);
    DECODE_BYTE(value_type);
    END_DECODE();
}

static int EncodeMarketSellCmd(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_MarketSellCmd);
    ENCODE_QWORD(trade_id);
    ENCODE_QWORD(item_guid);
    END_ENCODE();
}

static int DecodeMarketSellCmd(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_MarketSellCmd);
    DECODE_QWORD(trade_id);
    DECODE_QWORD(item_guid);
    END_DECODE();
}

static int EncodeMarketBuyCmd(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_MarketBuyCmd);
    ENCODE_QWORD(trade_id);
    ENCODE_DWORD(count);
    END_ENCODE();
}

static int DecodeMarketBuyCmd(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_MarketBuyCmd);
    DECODE_QWORD(trade_id);
    DECODE_DWORD(count);
    END_DECODE();
}

static int EncodeRecordsMineAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_RecordsMineAck);
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
    END_ENCODE();
}

static int DecodeRecordsMineAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_RecordsMineAck);
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
    END_DECODE();
}

static int EncodeDelegateMineAck2(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_DelegateMineAck2);
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
    END_ENCODE();
}

static int DecodeDelegateMineAck2(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_DelegateMineAck2);
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
    END_DECODE();
}

static int EncodeDelegateSellListAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_DelegateSellListAck);
    ENCODE_WORD(type);
    ENCODE_WORD(subtype);
    ENCODE_DWORD(total);
    ENCODE_DWORD(start);
    ENCODE_DWORD(count);
    for (uint16_t i = 0; i < pstIn->count; ++i)
    {
        if (-1 == EnCodeDELEGATE_SELL_ITEM(&pstIn->items[i], poNetData))return -1;
    }
    END_ENCODE();
}

static int DecodeDelegateSellListAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_DelegateSellListAck);
    DECODE_WORD(type);
    DECODE_WORD(subtype);
    DECODE_DWORD(total);
    DECODE_DWORD(start);
    DECODE_DWORD(count);
    for (uint16_t i = 0; i < pstOut->count; ++i)
    {
        if (-1 == DeCodeDELEGATE_SELL_ITEM(&pstOut->items[i], poNetData))return -1;
    }
    END_DECODE();
}

static int EncodeDelegateBuyListAck2(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_DelegateBuyListAck2);
    ENCODE_WORD(type);
    ENCODE_WORD(subtype);
    ENCODE_DWORD(total);
    ENCODE_DWORD(start);
    ENCODE_DWORD(count);
    for (uint16_t i = 0; i < pstIn->count; ++i)
    {
        if (-1 == EnCodeDELEGATE_BUY_ITEM2(&pstIn->items[i], poNetData))return -1;
    }
    END_ENCODE();
}

static int DecodeDelegateBuyListAck2(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_DelegateBuyListAck2);
    DECODE_WORD(type);
    DECODE_WORD(subtype);
    DECODE_DWORD(total);
    DECODE_DWORD(start);
    DECODE_DWORD(count);
    for (uint16_t i = 0; i < pstOut->count; ++i)
    {
        if (-1 == DeCodeDELEGATE_BUY_ITEM2(&pstOut->items[i], poNetData))return -1;
    }
    END_DECODE();
}


static int EncodeMissNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_MissNtf);
    ENCODE_QWORD(actor);
    ENCODE_QWORD(target);
    ENCODE_WORD(skill_id);
    ENCODE_BYTE(type);
    END_ENCODE();
}

static int DecodeMissNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_MissNtf);
    DECODE_QWORD(actor);
    DECODE_QWORD(target);
    DECODE_WORD(skill_id);
    DECODE_BYTE(type);
    END_DECODE();
}

static int EncodeQueryEx(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_QueryEx);
    ENCODE_QWORD(role_id);
    END_ENCODE();
}

static int DecodeQueryEx(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_QueryEx);
    DECODE_QWORD(role_id);
    END_DECODE();
}

static int EncodeSkillStatusNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_SkillStatusNtf);
    ENCODE_WORD(id);
    ENCODE_BYTE(active);
    END_ENCODE();
}

static int DecodeSkillStatusNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_SkillStatusNtf);
    DECODE_WORD(id);
    DECODE_BYTE(active);
    END_DECODE();
}

static int EncodeShabakOwnerNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ShabakOwnerNtf);
    ENCODE_QWORD(role_guid);
    END_ENCODE();
}

static int DecodeShabakOwnerNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ShabakOwnerNtf);
    DECODE_QWORD(role_guid);
    END_DECODE();
}

static int EncodeShabakLossNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ShabakLossNtf);
    ENCODE_QWORD(role_guid);
    END_ENCODE();
}

static int DecodeShabakLossNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ShabakLossNtf);
    DECODE_QWORD(role_guid);
    END_DECODE();
}

static int EncodeShabakEngageNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ShabakEngageNtf);
    ENCODE_STRING(own_family);
    ENCODE_STRING(attack_families);
    END_ENCODE();
}

static int DecodeShabakEngageNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ShabakEngageNtf);
    DECODE_STRING(own_family);
    DECODE_STRING(attack_families);
    END_DECODE();
}

static int EncodeShabakEndNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ShabakEndNtf);
    END_ENCODE();
}

static int DecodeShabakEndNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ShabakEndNtf);
    END_DECODE();
}

static int EncodeRunningFamilyWarNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_RunningFamilyWarNtf);
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
    BEGIN_DECODE_EX(ProtoClient3_RunningFamilyWarNtf);
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

static int EncodeJumpMapReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_JumpMapReq);
    ENCODE_WORD(dst_x);
    ENCODE_WORD(dst_y);
    ENCODE_BYTE(type);
    END_ENCODE();
}

static int DecodeJumpMapReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_JumpMapReq);
    DECODE_WORD(dst_x);
    DECODE_WORD(dst_y);
    DECODE_BYTE(type);
    END_DECODE();
}

static int EncodeItemPickupNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ItemPickupNtf);
    ENCODE_QWORD(item_guid);
    ENCODE_QWORD(role_guid);
    END_ENCODE();
}

static int DecodeItemPickupNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ItemPickupNtf);
    DECODE_QWORD(item_guid);
    DECODE_QWORD(role_guid);
    END_DECODE();
}

static int EncodeAutoPickupSettingsNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_AutoPickupSettingsNtf);

    if (EncodeAUTO_PICKUP(&pstIn->auto_pickup, poNetData) == -1)
        return -1;

    END_ENCODE();
}

static int DecodeAutoPickupSettingsNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_AutoPickupSettingsNtf);

    if (DecodeAUTO_PICKUP(&pstOut->auto_pickup, poNetData) == -1)
        return -1;

    END_DECODE();
}

static int EncodeMonsterPursureAttackingNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_MonsterPursureAttackingNtf);
    ENCODE_QWORD(guid);
    ENCODE_WORD(status);
    END_ENCODE();
}

static int DecodeMonsterPursureAttackingNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_MonsterPursureAttackingNtf);
    DECODE_QWORD(guid);
    DECODE_WORD(status);
    END_DECODE();
}

static int EncodeStartDigReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_StartDigReq);
    ENCODE_QWORD(treasure_guid);
    END_ENCODE();
}

static int DecodeStartDigReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_StartDigReq);
    DECODE_QWORD(treasure_guid);
    END_DECODE();
}

static int EncodeStartDigAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_StartDigAck);
    ENCODE_QWORD(treasure_guid);
    ENCODE_BYTE(code);
    ENCODE_DWORD(dig_time);
    END_ENCODE();
}

static int DecodeStartDigAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_StartDigAck);
    DECODE_QWORD(treasure_guid);
    DECODE_BYTE(code);
    DECODE_DWORD(dig_time);
    END_DECODE();
}

static int EncodeStopDigNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_StopDigNtf);
    ENCODE_QWORD(treasure_guid);
    ENCODE_BYTE(reason);
    END_ENCODE();
}

static int DecodeStopDigNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_StopDigNtf);
    DECODE_QWORD(treasure_guid);
    DECODE_BYTE(reason);
    END_DECODE();
}

static int EncodeRoleAppearNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_RoleAppearNtf);
    ENCODE_QWORD(role_guid);
    ENCODE_BYTE(appear_type);
    END_ENCODE();
}

static int DecodeRoleAppearNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_RoleAppearNtf);
    DECODE_QWORD(role_guid);
    DECODE_BYTE(appear_type);
    END_DECODE();
}

static int EncodeSyncClientBaseSetting(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_SyncClientBaseSetting);
    ENCODE_WORD(type);
    ENCODE_INT(value);
    END_ENCODE();
}

static int DecodeSyncClientBaseSetting(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_SyncClientBaseSetting);
    DECODE_WORD(type);
    DECODE_INT(value);
    END_DECODE();
}

static int EncodeRangePickup(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_RangePickup);
    ENCODE_BYTE(posnum);
    ENCODE_CHECK_UPBOUND(posnum, pos);
    for (uint8_t i = 0; i < pstIn->posnum; ++i)
        if (EncodePoint(pstIn->pos + i, poNetData) == -1)
            return -1;
    END_ENCODE();
}

static int DecodeRangePickup(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_RangePickup);
    DECODE_BYTE(posnum);
    DECODE_CHECK_UPBOUND(posnum, pos);
    for (uint8_t i = 0; i < pstOut->posnum; ++i)
        if (DecodePoint(pstOut->pos + i, poNetData) == -1)
            return -1;
    END_DECODE();
}

static int EncodeVerifyBuyItemInfoReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_VerifyBuyItemInfoReq);
    ENCODE_DWORD(item_id);
    ENCODE_BYTE(item_count);
    ENCODE_DWORD(item_price);
    END_ENCODE();
}

static int DecodeVerifyBuyItemInfoReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_VerifyBuyItemInfoReq);
    DECODE_DWORD(item_id);
    DECODE_BYTE(item_count);
    DECODE_DWORD(item_price);
    END_DECODE();
}

static int EncodeVerifyBuyItemInfoAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_VerifyBuyItemInfoAck);
    ENCODE_DWORD(item_id);
    ENCODE_BYTE(status);
    END_ENCODE();
}

static int DecodeVerifyBuyItemInfoAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_VerifyBuyItemInfoAck);
    DECODE_DWORD(item_id);
    DECODE_BYTE(status);
    END_DECODE();
}

static int EncodePlayerSetNameNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_PlayerSetNameNtf);
    ENCODE_QWORD(guid);
    ENCODE_STRING(name);
    ENCODE_STRING(orgName);
    END_ENCODE();
}

static int DecodePlayerSetNameNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_PlayerSetNameNtf);
    DECODE_QWORD(guid);
    DECODE_STRING(name);
    DECODE_STRING(orgName);
    END_DECODE();
}

static int EncodeItemRefreshReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_ItemRefreshReq);
    END_ENCODE();
}

static int DecodeItemRefreshReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_ItemRefreshReq);
    END_DECODE();
}

static int EncodeSetAutoModeReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_SetAutoModeReq);
    ENCODE_QWORD(role_guid);
    ENCODE_BYTE(enable);
    END_ENCODE();
}

static int DecodeSetAutoModeReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_SetAutoModeReq);
    DECODE_QWORD(role_guid);
    DECODE_BYTE(enable);
    END_DECODE();
}

static int EncodeSetAutoModeAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_SetAutoModeAck);
    ENCODE_QWORD(role_guid);
    ENCODE_BYTE(enable);
    END_ENCODE();
}

static int DecodeSetAutoModeAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_SetAutoModeAck);
    DECODE_QWORD(role_guid);
    DECODE_BYTE(enable);
    END_DECODE();
}

static int EncodeSceneItemUpdateNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient3_SceneItemUpdateNtf);
    ENCODE_QWORD(item_guid);
    END_ENCODE();
}

static int DecodeSceneItemUpdateNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient3_SceneItemUpdateNtf);
    DECODE_QWORD(item_guid);
    END_DECODE();
}

ProtoClient3::ProtoClient3()
{
    for (int i = 0; i < PROTO_CLIENT3_MAX; ++i) {
        SET_ENCODER_DECODER(i, EncodeNotImpl, DecodeNotImpl);
    }

    SET_ENCODER_DECODER(PROTO_CLIENT3_GET_ARROUND_TEAM_ACK, EnCodeGetAroundTeamAck, DeCodeGetAroundTeamAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_GET_ARROUND_TEAM_REQ, EnCodeGetAroundTeamReq, DeCodeGetAroundTeamReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_PLAYER_SWITCH_REQ, EnCodePlayerSwitchReq, DeCodePlayerSwitchReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_RELIVE_REQ, EnCodePlayerReliveReq, DeCodePlayerReliveReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_RELIVE_ACK, EnCodePlayerReliveAck, EnCodePlayerReliveAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ROLE_APP_NTF, EncodeRoleAppNtf, DecodeRoleAppNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ITEM_ATTR_NTF, EncodeItemAttrNtf, DecodeItemAttrNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ITEM_MOVE, EncodeItemMove, DecodeItemMove);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ITEM_SPLIT, EncodeItemSplit, DecodeItemSplit);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ITEM_ARRANGE, EncodeItemArrange, DecodeItemArrange);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ITEM_PICK_UP, EncodeItemPickUp, DecodeItemPickUp);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ITEM_APPEAR_NTF4, EncodeItemAppearNtf4, DecodeItemAppearNtf4);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ITEM_DESTROY_ACK, EncodeItemDestroyAck, DecodeItemDestroyAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ITEM_UPDATE_NTF, EncodeItemUpdateNtf, DecodeItemUpdateNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ITEM_APPLY, EncodeItemApply, DecodeItemApply);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ITEM_DROP, EncodeItemDrop, DecodeItemDrop);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ROLE_ATTR_NTF, EnCodeRoleAttrNtf, DeCodeRoleAttrNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ROLE_ATTR_EXT_NTF, EnCodeRoleAttrExtNtf, DeCodeRoleAttrExtNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ROLE_DYN_ATTR_NTF, EnCodeRoleDynAttrNtf, DeCodeRoleDynAttrNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ROLE_CUST_VAR_NTF, EnCodeRoleCustVarNtf, DeCodeRoleCustVarNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ROLE_CUST_VAR_REQ, EnCodeRoleCustVarReq, DeCodeRoleCustVarReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ITEM_ACK, EncodeItemAck, DecodeItemAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_DISAPPEAR_NTF, EncodeObjdisAppearNtf, DecodeObjdisAppearNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_MOVE_NTF, EncodeMoveNtf, DecodeMoveNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_MOVE_REQ, EncodeMoveReq, DecodeMoveReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_MOVE_ACK, EncodeMoveAck, DecodeMoveAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_TURN_REQ, EncodeTurnReq, DecodeTurnReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_TURN_NTF, EncodeTurnNtf, DecodeTurnNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_OBJDIE_NTF, EncodeObjDieNtf, DecodeObjDieNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SKILL_ADD_ACK, EncodeSkillAddAck, DecodeSkillAddAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SKILL_DELETE_ACK, EncodeSkillDeleteAck, DecodeSkillDeleteAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SKILL_SWITCH, EncodeSkillSwitch, DecodeSkillSwitch);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SKILL_SWITCH_ACK, EncodeSkillSwitchAck, DecodeSkillSwitchAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SKILL_PROFICIENCY_NTF, EncodeSkillProficiencyNtf, DecodeSkillProficiencyNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_BUFF_ADD_ACK, EncodeBuffAddAck, DecodeBuffAddAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_BUFF_DESTROY_ACK, EncodeBuffDestroyAck, DecodeBuffDestroyAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SPELL_TARGET, EncodeSpellTarget, DecodeSpellTarget);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SPELL_GRID, EncodeSpellGrid, DecodeSpellGrid);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SPELL_ACK, EncodeSpellAck, DecodeSpellAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SPELL_NTF, EncodeSpellNtf, DecodeSpellNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ENTER_GS_REQ, EncodeEnterGSReq, DecodeEnterGSReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ENTER_GS_ACK, EncodeEnterGSACK, DecodeEnterGSACK);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ENTER_GS_NTF, EncodeEnterGSNtf, DecodeEnterGSNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_PLAYER_APPEAR_NTF3, EncodePlayerAppearNtf3, DecodePlayerAppearNtf3);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ATTR_SHOW_NTF2_EX2, EncodeAttrShowNtf2Ex2, DecodeAttrShowNtf2Ex2);
    SET_ENCODER_DECODER(PROTO_CLIENT3_EXIT_GS_REQ, EncodeExitReq, DecodeExitReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_EXIT_GS_ACK, EncodeExitAck, DecodeExitAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_NPC_APPEAR_NTF, EncodeNpcAppearNtf, DecodeNpcAppearNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_NPC_SELECT, EncodeNpcSelect, DecodeNpcSelect);
    SET_ENCODER_DECODER(PROTO_CLIENT3_NPC_TALK_REQ, EncodeNpcTalkReq, DecodeNpcTalkReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_TRADE_NPC_BUY, EncodeTradeNpcBuy, DecodeTradeNpcBuy);
    SET_ENCODER_DECODER(PROTO_CLIENT3_TRADE_NPC_SHOP_NTF, EncodeTradeNpcShopNtf, DecodeTradeNpcShopNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_MONSTER_APPEAR_NTF6, EncodeMonsterAppearNtf6, DecodeMonsterAppearNtf6);
    SET_ENCODER_DECODER(PROTO_CLIENT3_KICK_ROLE_NTF, EncodeKickRoleNtf, DecodeKickRoleNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SKILL_CD_CHANGED_NTF, EncodeSkillCDChangedNtf, DecodeSkillCDChangedNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SKILL_PROP_PERMANENT_CHANGED_NTF, EncodeSkillPropPermanentChangedNtf, DecodeSkillPropPermanentChangedNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_RUN_SERV_SCRIPT_REQ, EncodeRunServScriptReq, DecodeRunServScriptReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_RUN_SERV_SCRIPT_ACK, EncodeRunServScriptAck, DecodeRunServScriptAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_RUN_CLIENT_SCRIPT, EncodeRunClientScript, DecodeRunClientScript);
    SET_ENCODER_DECODER(PROTO_CLIENT3_TRADE_MALL_BUY, EncodeTradeMallBuy, DecodeTradeMallBuy);
    SET_ENCODER_DECODER(PROTO_CLIENT3_TRADE_MALL_LIST_REQ, EncodeTradeMallListReq, DecodeTradeMallListReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_TRADE_MALL_LIST_ACK, EncodeTradeMallListAck, DecodeTradeMallListAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ATK_MODE_REQ, EncodeAtkModeReq, DecodeAtkModeReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_QUEST_QUERY_CAN_ACCEPT, EncodeQuestQueryCanAccept, DecodeQuestQueryCanAccept);
    SET_ENCODER_DECODER(PROTO_CLIENT3_QUEST_QUERY_CAN_ACCEPT_NTF, EncodeQuestQueryCanAcceptNtf, DecodeQuestQueryCanAcceptNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_QUEST_ACCEPT, EncodeQuestAccept, DecodeQuestAccept);
    SET_ENCODER_DECODER(PROTO_CLIENT3_QUEST_ADD_NTF, EncodeQuestAddNtf, DecodeQuestAddNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_QUEST_NPC_TALK_ACK, EncodeQuestNpcTalkAck, DecodeQuestNpcTalkAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_QUEST_TIMEOUT_NTF, EncodeQuestTimeoutNtf, DecodeQuestTimeoutNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_QUEST_UPDATE_NTF, EncodeQuestUpdateNtf, DecodeQuestUpdateNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_QUEST_DROP, EncodeQuestDrop, DecodeQuestDrop);
    SET_ENCODER_DECODER(PROTO_CLIENT3_QUEST_DROP_NTF, EncodeQuestDropNtf, DecodeQuestDropNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_QUEST_ACCOMPLISH, EncodeQuestAccomplish, DecodeQuestAccomplish);
    SET_ENCODER_DECODER(PROTO_CLIENT3_QUEST_STATE_NTF, EncodeQuestStateNtf, DecodeQuestStateNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_QUEST_NPC_STATE_NTF, EncodeQuestNpcStateNtf, DecodeQuestNpcStateNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ROLE_ATTR_EXT_REF_NTF, EncodeRoleAttrExtRefNtf, DecodeRoleAttrExtRefNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_LEVEL_UP_NTF, EncodeLevelUpNtf, DecodeLevelUpNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_PLAYER_QUERY, EncodePlayerQuery, DecodePlayerQuery);
    SET_ENCODER_DECODER(PROTO_CLIENT3_PLAYER_QUERY_NTF, EncodePlayerQueryNtf, DecodePlayerQueryNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_QUICK_BAR_SET, EnCodeQuickBarSet, DeCodeQuickBarSet);
    SET_ENCODER_DECODER(PROTO_CLIENT3_QUICK_BAR_SET_NTF, EnCodeQuickBarSetNtf, DeCodeQuickBarSetNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_GLOBAL_NTF, EnCodeGlobalNtf, DeCodeGlobalNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_GOLD_TAKE, EnCodeGoldTake, DeCodeGoldTake);
    SET_ENCODER_DECODER(PROTO_CLIENT3_GOLD_DEPOSIT, EnCodeGoldDeposit, DeCodeGoldDeposit);
    SET_ENCODER_DECODER(PROTO_CLIENT3_GM_COMMAND_REQ, EnCodeGMCommandReq, DeCodeGMCommandReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_TITLE_ADD_ACK, EncodeTitleAddAck, DecodeTitleAddAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_TITLE_REMOVE, EncodeTitleDel, DecodeTitleDel);
    SET_ENCODER_DECODER(PROTO_CLINET3_TITLE_REMOVE_ACK, EncodeTitleDelAck, DecodeTitleDelAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_TITLE_APPLY, EncodeTitleWear, DecodeTitleWear);
    SET_ENCODER_DECODER(PROTO_CLIENT3_TITLE_UNAPPLY, EncodeTitleUnWear, DecodeTitleUnWear);
    SET_ENCODER_DECODER(PROTO_CLIENT3_TITLE_LIST, EncodeTitleList, DecodeTitleList);

    SET_ENCODER_DECODER(PROTO_CLIENT3_PLAYER_FAMILY_CHANGE_NTF, EncodePlayerFamilyChangeNtf, DecodePlayerFamilyChangeNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_MISS_NTF, EncodeMissNtf, DecodeMissNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_RECORDS_MIN_REQ, EncodeRecordsMineReq, DecodeRecordsMineReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_DELEGATE_MINE_REQ, EncodeDelegateMineReq, DecodeDelegateMineReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_DELEGATE_SELL_LIST_REQ, EncodeDelegateSellListReq, DecodeDelegateSellListReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_DELEGATE_BUY_LIST_REQ, EncodeDelegateBuyListReq, DecodeDelegateBuyListReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_DELEGATE_CANCEL, EncodeDelegateCancel, DecodeDelegateCancel);
    SET_ENCODER_DECODER(PROTO_CLIENT3_DELEGATE_SELL_CMD, EncodeDelegateSellCmd, DecodeDelegateSellCmd);
    SET_ENCODER_DECODER(PROTO_CLIENT3_DELEGATE_BUY_CMD, EncodeDelegateBuyCmd, DecodeDelegateBuyCmd);
    SET_ENCODER_DECODER(PROTO_CLIENT3_MARKET_SELL_CMD, EncodeMarketSellCmd, DecodeMarketSellCmd);
    SET_ENCODER_DECODER(PROTO_CLIENT3_MARKET_BUY_CMD, EncodeMarketBuyCmd, DecodeMarketBuyCmd);
    SET_ENCODER_DECODER(PROTO_CLIENT3_RECORDS_MINE_ACK, EncodeRecordsMineAck, DecodeRecordsMineAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_DELEGATE_MINE_ACK2, EncodeDelegateMineAck2, DecodeDelegateMineAck2);
    SET_ENCODER_DECODER(PROTO_CLIENT3_DELEGATE_SELL_LIST_ACK, EncodeDelegateSellListAck, DecodeDelegateSellListAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_DELEGATE_BUY_LIST_ACK2, EncodeDelegateBuyListAck2, DecodeDelegateBuyListAck2);
    SET_ENCODER_DECODER(PROTO_CLIENT3_QUERY_EX, EncodeQueryEx, DecodeQueryEx);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SKILL_STATUS_NTF, EncodeSkillStatusNtf, DecodeSkillStatusNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SHABAK_OWNER_NTF, EncodeShabakOwnerNtf, DecodeShabakOwnerNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SHABAK_LOSS_NTF, EncodeShabakLossNtf, DecodeShabakLossNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SHABAK_ENGAGE_NTF, EncodeShabakEngageNtf, DecodeShabakEngageNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SHABAK_END_NTF, EncodeShabakEndNtf, DecodeShabakEndNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_FAMILY_WAR_NTF, EncodeRunningFamilyWarNtf, DecodeRunningFamilyWarNtf);
    SET_ENCODER_DECODER(PROTO_CLINET3_TRADE_LIST_UPDATE, EncodeTradeMallListUpdate, DecodeTradeMallListUpdate);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ROLE_INFO_CHANGE_NTF, EnCodeRoleInfoChangeNtf, DeCodeRoleInfoChangeNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_JUMP_MAP_REQ, EncodeJumpMapReq, DecodeJumpMapReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ITEM_PICKUP_NTF, EncodeItemPickupNtf, DecodeItemPickupNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_AUTO_PICKUP_SETTINGS_NTF, EncodeAutoPickupSettingsNtf, DecodeAutoPickupSettingsNtf);
    SET_ENCODER_DECODER(PROTO_CLINET3_MONSTER_PURSURE_STATUS_CHANGE_NTF, EncodeMonsterPursureAttackingNtf, DecodeMonsterPursureAttackingNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_GET_NPC_POS_REQ, EncodeGetNpcPosReq, DecodeGetNpcPosReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_GET_NPC_POS_ACK, EncodeGetNpcPosAck, DecodeGetNpcPosAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_START_DIG_REQ, EncodeStartDigReq, DecodeStartDigReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_START_DIG_ACK, EncodeStartDigAck, DecodeStartDigAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_STOP_DIG_NTF, EncodeStopDigNtf, DecodeStopDigNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ROLE_APPEAR_NTF, EncodeRoleAppearNtf, DecodeRoleAppearNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_RANGE_PICKUP, EncodeRangePickup, DecodeRangePickup);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SYNC_CLIENT_BASE_SETTING, EncodeSyncClientBaseSetting, DecodeSyncClientBaseSetting);
    SET_ENCODER_DECODER(PROTO_CLIENT3_VERIFY_BUY_ITEM_INFO_REQ, EncodeVerifyBuyItemInfoReq, DecodeVerifyBuyItemInfoReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_VERIFY_BUY_ITEM_INFO_ACK, EncodeVerifyBuyItemInfoAck, DecodeVerifyBuyItemInfoAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_PLAYER_SET_NAME_NTF, EncodePlayerSetNameNtf, DecodePlayerSetNameNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ITEM_REFRESH_REQ, EncodeItemRefreshReq, DecodeItemRefreshReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ITEM_TIP, EncodeItemTip, DecodeItemTip);
    SET_ENCODER_DECODER(PROTO_CLIENT3_ITEM_TIP_NTF, EncodeItemTipNtf, DecodeItemTipNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_TITLE_APPLY_NTF, EncodeTitleWearNtf, DecodeTitleWearNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_TITLE_UNAPPLY_NTF, EncodeTitleUnWearNtf, DecodeTitleUnWearNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_MONSTER_BACK_NTF, EncodeMonsterBackNtf, DecodeMonsterBackNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SET_AUTO_MODE_REQ, EncodeSetAutoModeReq, DecodeSetAutoModeReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SET_AUTO_MODE_ACK, EncodeSetAutoModeAck, DecodeSetAutoModeAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_TITLE_GET_LIST_REQ, EncodeTitleGetListReq, DecodeTitleGetListReq);
    SET_ENCODER_DECODER(PROTO_CLIENT3_SCENE_ITEM_UPDATE_NTF, EncodeSceneItemUpdateNtf, DecodeSceneItemUpdateNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_Send_GOODS_POST_REOCRD_TO_CLIENT, EncodeSendGoodsPostRecordToClient, DecodeSendGoodsPostRecordToClient);
    SET_ENCODER_DECODER(PROTO_CLIENT3_GOODS_POST_RECORD_ACK, EncodeGoodsPostRecordAck, DecodeGoodsPostRecordAck);
    SET_ENCODER_DECODER(PROTO_CLIENT3_EFEECT_APPEAR_NTF, EncodeEffectAppearNtf, DecodeEffectAppearNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT3_EFFECT_DISAPPEAR_NTF, EncodeEffectDisAppearNtf, DecodeEffectDisAppearNtf);


}

ProtoClient3::~ProtoClient3()
{
}

int ProtoClient3::BuildProtocol(void* pHost, char* pNet, int iNetSize)
{
    unsigned short moduleid = *(unsigned short*)pHost;
    unsigned short protoid = *(unsigned short*)((char*)pHost + sizeof(unsigned short));
    if (moduleid != GetModuleID()) {
        return -1;
    }
    if (protoid >= PROTO_CLIENT3_MAX) {
        return -1;
    }

    CNetData m_oData;
    m_oData.Prepare(pNet, iNetSize);
    return m_EnCodeFuncArray[protoid](pHost, &m_oData);
}

int ProtoClient3::HandleProtocol(void* pNet, char* pHost, int iNetSize)
{
    unsigned short moduleid = *(unsigned short*)pNet;
    unsigned short protoid = *(unsigned short*)((char*)pNet + sizeof(unsigned short));

#ifndef _HIDE_PROTO_LOG
    LOG_TRACE("moduleid: %d, protoid: %d", moduleid, protoid);
#endif // !_HIDE_PROTO_LOG


    if (moduleid != GetModuleID()) {
        return -1;
    }
    if (protoid >= PROTO_CLIENT3_MAX) {
        return -1;
    }

    CNetData m_oData;
    m_oData.Prepare((char*)pNet, iNetSize);
    return m_DeCodeFuncArray[protoid](pHost, &m_oData);
}
