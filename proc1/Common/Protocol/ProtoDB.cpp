#include "stdafx.h"
#include "ProtoDB.h"

static int EncodeHeartBeatReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_HeartBeatReq);
    END_ENCODE();
}

static int DecodeHeartBeatReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_HeartBeatReq);
    END_DECODE();
}

static int EncodeHeartBeatAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_HeartBeatAck);
    END_ENCODE();
}

static int DecodeHeartBeatAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_HeartBeatAck);
    END_DECODE();
}

static int EncodeUploadConfigReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_UploadConfigReq);
    ENCODE_DWORD(ip);
    ENCODE_DWORD(port);
    END_ENCODE();
}

static int DecodeUploadConfigReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_UploadConfigReq);
    DECODE_DWORD(ip);
    DECODE_DWORD(port);
    END_DECODE();
}

static int EncodeConfigReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_ConfigReq);
    END_ENCODE();
}

static int DecodeConfigReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_ConfigReq);
    END_DECODE();
}

static int EncodeConfigAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_ConfigAck);
    ENCODE_DWORD(logServIp);
    ENCODE_DWORD(logServPort);
    END_ENCODE();
}

static int DecodeConfigAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_ConfigAck);
    DECODE_DWORD(logServIp);
    DECODE_DWORD(logServPort);
    END_DECODE();
}

static int EncodeQuestInfo(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_QuestInfo);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    if (EnCodeQUEST_INFO(&pstIn->quest_info, poNetData) == -1)
        return -1;

    ENCODE_BYTE(achev_data_num);
    for (uint8_t i = 0; i < pstIn->achev_data_num; ++i)
        if (EnCodeQUEST_ACHIEVE(pstIn->achev_data + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeQuestInfo(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_QuestInfo);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    if (DeCodeQUEST_INFO(&pstOut->quest_info, poNetData) == -1)
        return -1;

    DECODE_BYTE(achev_data_num);
    for (uint8_t i = 0; i < pstOut->achev_data_num; ++i)
        if (DeCodeQUEST_ACHIEVE(pstOut->achev_data + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodeGetCustVarAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_GetCustVarAck);

    if (EnCodeCUST_VAR_SP_LIST(pstIn->vars, poNetData) == -1) return -1;

    END_ENCODE();
}

static int DecodeGetCustVarAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_GetCustVarAck);

    auto vars = std::make_unique<CUST_VAR_SP_LIST>();
    if (DeCodeCUST_VAR_SP_LIST(vars.get(), poNetData) == -1) return -1;
    pstOut->vars = vars.release();

    END_DECODE();
}

static int EncodePlayerCustVar(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_PlayerCustVar);
    ENCODE_QWORD(playerid);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);

    if (!pstIn->vars) return -1;

    auto count = static_cast<uint16_t>(pstIn->vars->size());
    if (poNetData->AddWord(count) == -1) return -1;

    for (auto &it : *pstIn->vars)
        if (EnCodeCUST_VAR(&it.second, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodePlayerCustVar(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_PlayerCustVar);
    DECODE_QWORD(playerid);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);

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

static int EncodePlayerItemCustVar(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_PlayerItemCustVar);
    ENCODE_QWORD(playerid);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);

    if (EnCodeCUST_VAR_SP_LIST(pstIn->vars, poNetData) == -1) return -1;

    END_ENCODE();
}

static int DecodePlayerItemCustVar(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_PlayerItemCustVar);
    DECODE_QWORD(playerid);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);

    auto vars = std::make_unique<CUST_VAR_SP_LIST>();
    if (DeCodeCUST_VAR_SP_LIST(vars.get(), poNetData) == -1) return -1;
    pstOut->vars = vars.release();

    END_DECODE();
}

static int EncodePlayerQuickBarSetNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_QuickBarSetNtf);
    ENCODE_WORD(num);
    ENCODE_QWORD(role_id);
    ENCODE_QWORD(userid);

    for (uint16_t i = 0; i < pstIn->num; ++i)
        if (EnCodeQUICK_BAR_INFO(pstIn->info + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodePlayerQuickBarSetNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_QuickBarSetNtf);
    DECODE_WORD(num);
    DECODE_QWORD(role_id);
    DECODE_QWORD(userid);

    for (uint16_t i = 0; i < pstOut->num; ++i)
        if (DeCodeQUICK_BAR_INFO(pstOut->info + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodePlayerDgnBindInfoNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_DgnBindInfoNtf);
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

static int DecodePlayerDgnBindInfoNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_DgnBindInfoNtf);
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

static int EncodePlayerGlobalNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_GlobalNtf);
    ENCODE_QWORD(role_id);
    ENCODE_QWORD(userid);
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

static int DecodePlayerGlobalNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_GlobalNtf);
    DECODE_QWORD(role_id);
    DECODE_QWORD(userid);
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

static int EncodeTopListAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_GetTopListAck);
    ENCODE_BYTE(type);
    ENCODE_BYTE(TopListNum);
    for (uint8_t i = 0; i < pstIn->TopListNum; i++)
        ENCODE_QWORD(rolelist[i]);

    for (uint8_t i = 0; i < pstIn->TopListNum; i++)
        if (EnCodeTOPLIST_INFO(pstIn->TopList + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeTopListAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_GetTopListAck);
    DECODE_BYTE(type);
    DECODE_BYTE(TopListNum);
    for (uint8_t i = 0; i < pstOut->TopListNum; i++)
        DECODE_QWORD(rolelist[i]);

    for (uint8_t i = 0; i < pstOut->TopListNum; i++)
        if (DeCodeTOPLIST_INFO(pstOut->TopList + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodeAddMailAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_AddMailAck);
    ENCODE_WORD(err_type);
    ENCODE_BYTE(num);
    for (int i = 0; i < pstIn->num; ++i)
    {
        if (-1 == EnCodeMAIL_INFO(&pstIn->infos[i], poNetData))return -1;
    }
    END_ENCODE();
}

static int DecodeAddMailAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_AddMailAck);
    DECODE_WORD(err_type);
    DECODE_BYTE(num);
    for (int i = 0; i < pstOut->num; ++i)
    {
        if (-1 == DeCodeMAIL_INFO(&pstOut->infos[i], poNetData))return -1;
    }
    END_DECODE();
}

static int EncodeGetMailInfoAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_GetMailInfoAck);
    ENCODE_WORD(num);
    for (uint16_t i = 0; i < pstIn->num; ++i)
    {
        if (-1 == EnCodeMAIL_INFO(&pstIn->infos[i], poNetData))return -1;
    }
    END_ENCODE();
}

static int DecodeGetMailInfoAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_GetMailInfoAck);
    DECODE_WORD(num);
    for (uint16_t i = 0; i < pstOut->num; ++i)
    {
        if (-1 == DeCodeMAIL_INFO(&pstOut->infos[i], poNetData))return -1;
    }
    END_DECODE();
}

static int EncodeItemDynAttrNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_ItemDynAttrNtf);
    ENCODE_QWORD(playerid);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);

    if (EnCodeITEM_DYN_ATTRS_LIST(pstIn->item_dyn_attrs_list, poNetData) == -1) return -1;

    END_ENCODE();
}

static int DecodeItemDynAttrNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_ItemDynAttrNtf);
    DECODE_QWORD(playerid);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);

    auto itemDynAttrsList = std::make_unique<ITEM_DYN_ATTRS_LIST>();
    if (DeCodeITEM_DYN_ATTRS_LIST(itemDynAttrsList.get(), poNetData) == -1) return -1;

    pstOut->item_dyn_attrs_list = itemDynAttrsList.release();

    END_DECODE();
}

static int EncodeRoleDynAttrNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_RoleDynAttrNtf);
    ENCODE_QWORD(playerid);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);

    if (EnCodeITEM_DYN_ATTRS_LIST(pstIn->role_dyn_attrs_list, poNetData) == -1) return -1;

    END_ENCODE();
}

static int DecodeRoleDynAttrNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_RoleDynAttrNtf);
    DECODE_QWORD(playerid);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);

    auto roleDynAttrsList = std::make_unique<ROLE_DYN_ATTRS_LIST>();
    if (DeCodeITEM_DYN_ATTRS_LIST(roleDynAttrsList.get(), poNetData) == -1) return -1;

    pstOut->role_dyn_attrs_list = roleDynAttrsList.release();

    END_DECODE();
}

static int EncodeGetLoginIpAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_GetLoginIpAck);
    ENCODE_WORD(num);
    for (int i = 0; i < pstIn->num; ++i)
    {
        if (EnCodeLOGIN_IP_DATA(&pstIn->infos[i], poNetData) == -1) return -1;
    }


    END_ENCODE();
}

static int DecodeGetLoginIpAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_GetLoginIpAck);
    DECODE_WORD(num);
    for (int i = 0; i < pstOut->num; ++i)
    {
        if (DeCodeLOGIN_IP_DATA(&pstOut->infos[i], poNetData) == -1) return -1;
    }
    END_DECODE();
}


static int EncodeSyncLoginTypeToLS(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_SyncLoginTypeToLS);
    ENCODE_BYTE(num);
    ENCODE_BYTE(opt_type);
    for (int i = 0; i < pstIn->num; ++i)
    {
        if (EnCodeLOGIN_IP_DATA(&pstIn->infos[i], poNetData) == -1) return -1;
    }
    END_ENCODE();
}

static int DecodeSyncLoginTypeToLS(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_SyncLoginTypeToLS);
    DECODE_BYTE(num);
    DECODE_BYTE(opt_type);
    for (int i = 0; i < pstOut->num; ++i)
    {
        if (DeCodeLOGIN_IP_DATA(&pstOut->infos[i], poNetData) == -1) return -1;
    }
    END_DECODE();
}

static int EncodeGetProhibitChatInfofAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_GetProhibitChatInfoAck);
    ENCODE_BYTE(num);
    for (int i = 0; i < pstIn->num; ++i)
    {
        if (EnCodePROHIBIT_CHAT_DATA(&pstIn->infos[i], poNetData) == -1) return -1;
    }
    END_ENCODE();
}

static int DecodeGetProhibitChatInfofAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_GetProhibitChatInfoAck);
    DECODE_BYTE(num);
    for (int i = 0; i < pstOut->num; ++i)
    {
        if (DeCodePROHIBIT_CHAT_DATA(&pstOut->infos[i], poNetData) == -1) return -1;
    }
    END_DECODE();
}

static int EncodeGoodsNotIssuedRecordsNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_GoodsNotIssuedRecordsNtf);
    ENCODE_QWORD(player_guid);
    ENCODE_QWORD(role_guid);
    ENCODE_BYTE(num);
    ENCODE_CHECK_UPBOUND(num, records);
    for (uint8_t i = 0; i < pstIn->num; ++i)
        if (EncodeGOODS_ISSUE_RECORD(pstIn->records + i, poNetData) == -1)
            return -1;
    END_ENCODE();
}

static int DecodeGoodsNotIssuedRecordsNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_GoodsNotIssuedRecordsNtf);
    DECODE_QWORD(player_guid);
    DECODE_QWORD(role_guid);
    DECODE_BYTE(num);
    DECODE_CHECK_UPBOUND(num, records);
    for (uint8_t i = 0; i < pstOut->num; ++i)
        if (DecodeGOODS_ISSUE_RECORD(pstOut->records + i, poNetData) == -1)
            return -1;
    END_DECODE();
}

static int EncodeGoodsNotPostRecordsNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_GoodsNotPostRecordsNtf);
    ENCODE_QWORD(player_guid);
    ENCODE_QWORD(role_guid);
    ENCODE_BYTE(num);
    ENCODE_CHECK_UPBOUND(num, records);
    for (uint8_t i = 0; i < pstIn->num; ++i)
        if (EncodeGOODS_ISSUE_RECORD(pstIn->records + i, poNetData) == -1)
            return -1;
    END_ENCODE();
}

static int DecodeGoodsNotPostRecordsNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_GoodsNotPostRecordsNtf);
    DECODE_QWORD(player_guid);
    DECODE_QWORD(role_guid);
    DECODE_BYTE(num);
    DECODE_CHECK_UPBOUND(num, records);
    for (uint8_t i = 0; i < pstOut->num; ++i)
        if (DecodeGOODS_ISSUE_RECORD(pstOut->records + i, poNetData) == -1)
            return -1;
    END_DECODE();
}

static int EncodeRebateMoneyNotUsedRecordNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_RebateMoneyNotUsedRecordNtf);
    ENCODE_QWORD(role_guid);
    if (EncodeREBATE_MONEY_RECORD(&pstIn->record, poNetData) == -1)
        return -1;
    END_ENCODE();
}

static int DecodeRebateMoneyNotUsedRecordNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_RebateMoneyNotUsedRecordNtf);
    DECODE_QWORD(role_guid);
    if (DecodeREBATE_MONEY_RECORD(&pstOut->record, poNetData) == -1)
        return -1;
    END_DECODE();
}


static int EncodePlayerSetNameAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_PlayerSetNameAck);
    ENCODE_WORD(errcode);
    ENCODE_QWORD(guid);
    ENCODE_QWORD(userid);
    ENCODE_STRING(orgName);
    ENCODE_STRING(name);
    END_ENCODE();
}

static int DecodePlayerSetNameAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_PlayerSetNameAck);
    DECODE_WORD(errcode);
    DECODE_QWORD(guid);
    DECODE_QWORD(userid);
    DECODE_STRING(orgName);
    DECODE_STRING(name);
    END_DECODE();
}

static int EncodeGetTitleInfoAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_GetTitleInfoAck);
    ENCODE_QWORD(playerguid);
    ENCODE_QWORD(guid);
    ENCODE_WORD(num);
    for (int i = 0; i < pstIn->num; ++i) {
        if (-1 == EnCodeTITLE_INFO(&pstIn->info[i], poNetData))return -1;
    }
    END_ENCODE();
}

static int DecodeGetTitleInfoAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_GetTitleInfoAck);
    DECODE_QWORD(playerguid);
    DECODE_QWORD(guid);
    DECODE_WORD(num);
    for (int i = 0; i < pstOut->num; ++i) {
        if (-1 == DeCodeTITLE_INFO(&pstOut->info[i], poNetData))return -1;
    }
    END_DECODE();
}

static int EncodeDelLockRoleAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_DelLockRoleAck);
    ENCODE_WORD(num);
    for (int i = 0; i < pstIn->num; ++i) {
        ENCODE_QWORD(userID[i]);
    }
    for (int i = 0; i < pstIn->num; ++i) {
        ENCODE_QWORD(guid[i]);
    }
    END_ENCODE();
}

static int DecodeDelLockRoleAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_DelLockRoleAck);
    DECODE_WORD(num);
    for (int i = 0; i < pstOut->num; ++i) {
        DECODE_QWORD(userID[i]);
    }
    for (int i = 0; i < pstOut->num; ++i) {
        DECODE_QWORD(guid[i]);
    }
    END_DECODE();
}

static int EncodeGetCustListInfoAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoDB_GetCustListInfoAck);
    ENCODE_WORD(num);
    for (int i = 0; i < pstIn->num; ++i) {
        if (-1 == EncodeCUST_LIST_INFO(&pstIn->data[i], poNetData))return -1;
    }
    END_ENCODE();
}

static int DecodeGetCustListInfoAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoDB_GetCustListInfoAck);
    DECODE_WORD(num);
    for (int i = 0; i < pstOut->num; ++i) {
        if (-1 == DecodeCUST_LIST_INFO(&pstOut->data[i], poNetData))return -1;
    }
    END_DECODE();
}

ProtoDB::ProtoDB()
{
    SET_ENCODER_DECODER(PROTO_DB_HEART_BEAT_REQ, EncodeHeartBeatReq, DecodeHeartBeatReq);
    SET_ENCODER_DECODER(PROTO_DB_HEART_BEAT_ACK, EncodeHeartBeatAck, DecodeHeartBeatAck);
    SET_ENCODER_DECODER(PROTO_DB_UPLOAD_CONFIG_REQ, EncodeUploadConfigReq, DecodeUploadConfigReq);
    SET_ENCODER_DECODER(PROTO_DB_QUEST_INFO, EncodeQuestInfo, DecodeQuestInfo);
    SET_ENCODER_DECODER(PROTO_DB_GET_CUST_VAR_ACK, EncodeGetCustVarAck, DecodeGetCustVarAck);
    SET_ENCODER_DECODER(PROTO_DB_PLAYER_CUST_VAR, EncodePlayerCustVar, DecodePlayerCustVar);
    SET_ENCODER_DECODER(PROTO_DB_PLAYER_ITEM_CUST_VAR, EncodePlayerItemCustVar, DecodePlayerItemCustVar);
    SET_ENCODER_DECODER(PROTO_DB_QUICK_BAR_SET_NTF, EncodePlayerQuickBarSetNtf, DecodePlayerQuickBarSetNtf);
    SET_ENCODER_DECODER(PROTO_DB_DGN_BIND_INFO_NTF, EncodePlayerDgnBindInfoNtf, DecodePlayerDgnBindInfoNtf);
    SET_ENCODER_DECODER(PROTO_DB_GLOBAL_NTF, EncodePlayerGlobalNtf, DecodePlayerGlobalNtf);
    SET_ENCODER_DECODER(PROTO_DB_TOPLIST_ACK, EncodeTopListAck, DecodeTopListAck);
    SET_ENCODER_DECODER(PROTO_DB_ADD_MAIL_ACK, EncodeAddMailAck, DecodeAddMailAck);
    SET_ENCODER_DECODER(PROTO_DB_GET_MAIL_INFO_ACK, EncodeGetMailInfoAck, DecodeGetMailInfoAck);
    SET_ENCODER_DECODER(PROTO_DB_ITEM_DYN_ATTR_NTF, EncodeItemDynAttrNtf, DecodeItemDynAttrNtf);
    SET_ENCODER_DECODER(PROTO_DB_ROLE_DYN_ATTR_NTF, EncodeRoleDynAttrNtf, DecodeRoleDynAttrNtf);
    SET_ENCODER_DECODER(PROTO_DB_CONFIG_REQ, EncodeConfigReq, DecodeConfigReq);
    SET_ENCODER_DECODER(PROTO_DB_CONFIG_ACK, EncodeConfigAck, DecodeConfigAck);
    SET_ENCODER_DECODER(PROTO_DB_GET_LOGIN_IP_ACK, EncodeGetLoginIpAck, DecodeGetLoginIpAck);
    SET_ENCODER_DECODER(PROTO_DB_SYNC_LOGIN_TYPE_TO_LS, EncodeSyncLoginTypeToLS, DecodeSyncLoginTypeToLS);
    SET_ENCODER_DECODER(PROTO_DB_GET_PROHIBIT_CHAT_INFO_ACK, EncodeGetProhibitChatInfofAck, DecodeGetProhibitChatInfofAck);
    SET_ENCODER_DECODER(PROTO_DB_GOODS_NOT_ISSUED_RECORDS_NTF, EncodeGoodsNotIssuedRecordsNtf, DecodeGoodsNotIssuedRecordsNtf);
    SET_ENCODER_DECODER(PROTO_DB_REBATE_MONEY_NOT_USED_RECORD_NTF, EncodeRebateMoneyNotUsedRecordNtf, DecodeRebateMoneyNotUsedRecordNtf);
    SET_ENCODER_DECODER(PROTO_DB_PLAYER_SET_NAME_ACK, EncodePlayerSetNameAck, DecodePlayerSetNameAck);
    SET_ENCODER_DECODER(PROTO_DB_GET_TITLE_INFO_ACK, EncodeGetTitleInfoAck, DecodeGetTitleInfoAck);
    SET_ENCODER_DECODER(PROTO_DB_DEL_LOCK_ROlE_ACK, EncodeDelLockRoleAck, DecodeDelLockRoleAck);
    SET_ENCODER_DECODER(PROTO_DB_GET_CUST_LIST_INFO_ACK, EncodeGetCustListInfoAck, DecodeGetCustListInfoAck);
    SET_ENCODER_DECODER(PROTO_DB_GOODS_NOT_POST_RECORDS_NTF, EncodeGoodsNotPostRecordsNtf, DecodeGoodsNotPostRecordsNtf);


}

ProtoDB::~ProtoDB()
{

}

int ProtoDB::BuildProtocol(void* pHost, char* pNet, int iNetSize)
{
    unsigned short moduleid = *(unsigned short*)pHost;
    unsigned short protoid = *(unsigned short*)((char*)pHost + sizeof(unsigned short));
    if (moduleid != GetModuleID()) {
        return -1;
    }
    if (protoid >= PROTO_DB_MAX) {
        return -1;
    }

    CNetData m_oData;
    m_oData.Prepare(pNet, iNetSize);
    return m_EnCodeFuncArray[protoid](pHost, &m_oData);
}

int ProtoDB::HandleProtocol(void* pNet, char* pHost, int iNetSize)
{
    unsigned short moduleid = *(unsigned short*)pNet;
    unsigned short protoid = *(unsigned short*)((char*)pNet + sizeof(unsigned short));
    if (moduleid != GetModuleID()) {
        return -1;
    }
    if (protoid >= PROTO_DB_MAX) {
        return -1;
    }

    CNetData m_oData;
    m_oData.Prepare((char*)pNet, iNetSize);
    return m_DeCodeFuncArray[protoid](pHost, &m_oData);
}