#include "stdafx.h"
#include "ProtoCS.h"
#include "ProtoLog.h"
#include <memory>

static int EncodeSyncRoleInfo(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_SyncRoleInfo);
    ENCODE_QWORD(guid);
    ENCODE_INT(briefInfoNum);
    ENCODE_BYTE(setFlag);
    for (int i = 0; i < pstIn->briefInfoNum; ++i) {
        ENCODE_INT(briefInfoKey[i]);
    }

    for (int i = 0; i < pstIn->briefInfoNum; ++i) {
        ENCODE_INT(briefInfoVal[i]);
    }

    ENCODE_INT(extraInfoNum);
    for (int i = 0; i < pstIn->extraInfoNum; ++i) {
        ENCODE_INT(extraInfoKey[i]);
    }

    for (int i = 0; i < pstIn->extraInfoNum; ++i) {
        ENCODE_QWORD(extraInfoVal[i]);
    }
    if (pstIn->setFlag) {
        if (EncodeROLE_SETTINGS(&pstIn->roleset, poNetData) == -1) return -1;
    }
    END_ENCODE();
}

static int DecodeSyncRoleInfo(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_SyncRoleInfo);
    DECODE_QWORD(guid);
    DECODE_INT(briefInfoNum);
    DECODE_BYTE(setFlag);
    for (int i = 0; i < pstOut->briefInfoNum; ++i) {
        DECODE_INT(briefInfoKey[i]);
    }

    for (int i = 0; i < pstOut->briefInfoNum; ++i) {
        DECODE_INT(briefInfoVal[i]);
    }
    DECODE_INT(extraInfoNum);
    for (int i = 0; i < pstOut->extraInfoNum; ++i) {
        DECODE_INT(extraInfoKey[i]);
    }

    for (int i = 0; i < pstOut->extraInfoNum; ++i) {
        DECODE_QWORD(extraInfoVal[i]);
    }
    if (pstOut->setFlag) {
        if (DecodeROLE_SETTINGS(&pstOut->roleset, poNetData) == -1) return -1;
    }
    END_DECODE();
}

static int EncodeActivationCodeAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_ActivationCodeAck);
    ENCODE_QWORD(guid);
    ENCODE_WORD(err);
    ENCODE_WORD(type);
    ENCODE_STRING(gift_name);
    ENCODE_STRING(gift_content);
    ENCODE_STRING(err_desc);
    END_ENCODE();
}

static int DecodeActivationCodeAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_ActivationCodeAck);
    DECODE_QWORD(guid);
    DECODE_WORD(err);
    DECODE_WORD(type);
    DECODE_STRING(gift_name);
    DECODE_STRING(gift_content);
    DECODE_STRING(err_desc);
    END_DECODE();
}

static int EncodeAddProhibitChatInfo(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_AddProhibitChatInfo);
    ENCODE_BYTE(num);
    for (int i = 0; i < pstIn->num; ++i)
    {
        if (-1 == EnCodePROHIBIT_CHAT_DATA(&pstIn->infos[i], poNetData)) return -1;
    }
    END_ENCODE();
}

static int DecodeAddProhibitChatInfo(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_AddProhibitChatInfo);
    DECODE_BYTE(num);
    for (int i = 0; i < pstOut->num; ++i)
    {
        if (-1 == DeCodePROHIBIT_CHAT_DATA(&pstOut->infos[i], poNetData)) return -1;
    }
    END_DECODE();
}

static int EncodeDelProhibitInfo(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtocCS_DelProhibitInfo);
    ENCODE_BYTE(num);
    for (int i = 0; i < pstIn->num; ++i)
    {
        if (-1 == EnCodePROHIBIT_CHAT_DATA(&pstIn->infos[i], poNetData)) return -1;
    }
    END_ENCODE();
}

static int DecodeDelProhibitInfo(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtocCS_DelProhibitInfo);
    DECODE_BYTE(num);
    for (int i = 0; i < pstOut->num; ++i)
    {
        if (-1 == DeCodePROHIBIT_CHAT_DATA(&pstOut->infos[i], poNetData)) return -1;
    }
    END_DECODE();
}

static  int EncodeMallListUpdate(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_MallListUpdate);
    ENCODE_WORD(num);
    ENCODE_BYTE(limit_type);
    for (int i = 0; i < pstIn->num; ++i)
    {
        if (-1 == EncodeMALL_ITEM_INFO_BASE(&pstIn->data[i], poNetData))
            return -1;
    }
    END_ENCODE();
}

static  int DecodeMallListUpdate(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_MallListUpdate);
    DECODE_WORD(num);
    DECODE_BYTE(limit_type);
    for (int i = 0; i < pstOut->num; ++i)
    {
        if (-1 == DecodeMALL_ITEM_INFO_BASE(&pstOut->data[i], poNetData))
            return -1;
    }
    END_DECODE();
}

static  int EncodeGetMallLimitInfoSingleAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_GetMallLimitInfoSingleAck);
    ENCODE_QWORD(playerguid);
    ENCODE_BYTE(isFirstPkg);
    ENCODE_BYTE(isFinalPkg);

    ENCODE_WORD(num);
    for (int i = 0; i < pstIn->num; ++i)
    {
	if (-1 == poNetData->AddQword(pstIn->data[i].playerguid))
		return -1;
	if (-1 == poNetData->AddDword(pstIn->data[i].item_idx))
		return -1;
	if (-1 == poNetData->AddDword(pstIn->data[i].num))
		return -1;
    }
    END_ENCODE();
}

static  int DecodeGetMallLimitInfoSingleAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_GetMallLimitInfoSingleAck);
    DECODE_QWORD(playerguid);
    DECODE_BYTE(isFirstPkg);
    DECODE_BYTE(isFinalPkg);
    DECODE_WORD(num);
    for (int i = 0; i < pstOut->num; ++i)
    {
        if (-1 == poNetData->DelQword(pstOut->data[i].playerguid))
            return -1;
        if (-1 == poNetData->DelDword(pstOut->data[i].item_idx))
            return -1;
        if (-1 == poNetData->DelDword(pstOut->data[i].num))
            return -1;
    }
    END_DECODE();
}

static  int EncodeRunGmCmdAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_RunGmCmdAck);
    ENCODE_BYTE(result);
    ENCODE_INT(sn);
    ENCODE_STRING(cmd);
    ENCODE_STRING(param);
    ENCODE_DWORD(token);
    ENCODE_STRING(playername);
    END_ENCODE();
}

static  int DecodeRunGmCmdAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_RunGmCmdAck);
    DECODE_BYTE(result);
    DECODE_INT(sn);
    DECODE_STRING(cmd);
    DECODE_STRING(param);
    DECODE_DWORD(token);
    DECODE_STRING(playername);
    END_DECODE();
}

static  int EncodeAuctionGetFinishedInfoAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_AuctionGetFinishedInfoAck);
    ENCODE_STRING(func);
    ENCODE_WORD(num);
    for (auto i = 0; i < pstIn->num; ++i)
    {
        if (EnCodeAUCTION_HOUSE_ITEM_INFO(&pstIn->info[i], poNetData) == -1) return -1;
    }
    END_ENCODE();
}

static  int DecodeAuctionGetFinishedInfoAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_AuctionGetFinishedInfoAck);
    DECODE_STRING(func);
    DECODE_WORD(num);
    for (auto i = 0; i < pstOut->num; ++i)
    {
        if (DeCodeAUCTION_HOUSE_ITEM_INFO(&pstOut->info[i], poNetData) == -1) return -1;
    }
    END_DECODE();
}

static  int EncodeClearRoleInfoNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_ClearRoleInfoNtf);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static  int DecodeClearRoleInfoNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_ClearRoleInfoNtf);
    DECODE_QWORD(role_id);
    DECODE_DWORD(token);
    END_DECODE();
}

static  int EncodeDeleteRoleInfoNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_DeleteRoleInfoNtf);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(token);
    ENCODE_STRING(base_info);
    END_ENCODE();
}

static  int DecodeDeleteRoleInfoNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_DeleteRoleInfoNtf);
    DECODE_QWORD(role_id);
    DECODE_DWORD(token);
    DECODE_STRING(base_info);
    END_DECODE();
}

static  int EncodeUpdateRoleInfoNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_UpdateRoleInfoNtf);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(token);
    ENCODE_STRING(base_info);
    END_ENCODE();
}

static  int DecodeUpdateRoleInfoNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_UpdateRoleInfoNtf);
    DECODE_QWORD(role_id);
    DECODE_DWORD(token);
    DECODE_STRING(base_info);
    END_DECODE();
}

static  int EncodeInsertRoleInfoNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_InsertRoleInfoNtf);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(token);
    ENCODE_STRING(base_info);
    END_ENCODE();
}

static  int DecodeInsertRoleInfoNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_InsertRoleInfoNtf);
    DECODE_QWORD(role_id);
    DECODE_DWORD(token);
    DECODE_STRING(base_info);
    END_DECODE();
}

static int EncodeGetRoleInfoReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_GetRoleInfoReq);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DecodeGetRoleInfoReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_GetRoleInfoReq);
    DECODE_QWORD(role_id);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeGetRoleInfoAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_GetRoleInfoAck);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(token);
    ENCODE_STRING(base_info);
    END_ENCODE();
}

static int DecodeGetRoleInfoAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_GetRoleInfoAck);
    DECODE_QWORD(role_id);
    DECODE_DWORD(token);
    DECODE_STRING(base_info);
    END_DECODE();
}

static  int EncodeDeleteItemNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_DeleteItemNtf);
    ENCODE_QWORD(guid);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static  int DecodeDeleteItemNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_DeleteItemNtf);
    DECODE_QWORD(guid);
    DECODE_QWORD(role_id);
    DECODE_DWORD(token);
    END_DECODE();
}

static  int EncodeUpdateItemNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_UpdateItemNtf);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(token);
    if (EnCodeITEM_DB_INFO(&pstIn->base_info, poNetData) == -1) return -1;
    END_ENCODE();
}

static  int DecodeUpdateItemNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_UpdateItemNtf);
    DECODE_QWORD(role_id);
    DECODE_DWORD(token);
    if (DeCodeITEM_DB_INFO(&pstOut->base_info, poNetData) == -1) return -1;
    END_DECODE();
}

static  int EncodeInsertItemNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_InsertItemNtf);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(token);
    if (EnCodeITEM_DB_INFO(&pstIn->base_info, poNetData) == -1) return -1;
    END_ENCODE();
}

static  int DecodeInsertItemNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_InsertItemNtf);
    DECODE_QWORD(role_id);
    DECODE_DWORD(token);
    if (DeCodeITEM_DB_INFO(&pstOut->base_info, poNetData) == -1) return -1;
    END_DECODE();
}

static  int EncodeEnterMSReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_EnterMSReq);
    ENCODE_DWORD(sessionid);
    ENCODE_DWORD(nMS2GSSessionID);
    ENCODE_DWORD(token);
    ENCODE_QWORD(playerid);
    ENCODE_CHAR(entertype);
    ENCODE_CHAR(fangchenmi);
    ENCODE_CHAR(clienttype);
    if (EnCodeROLE_BRIEF_INFO(&pstIn->roleBriefInfo, poNetData) == -1) return -1;
    if (EnCodeROLE_EXTRA_INFO(&pstIn->roleExtraInfo, poNetData) == -1) return -1;
    if (EncodeROLE_SETTINGS(&pstIn->roleSettings, poNetData) == -1) return -1;
    if (EnCodeQUEST_INFO(&pstIn->questInfo, poNetData) == -1) return -1;

    ENCODE_BYTE(questAchievesNum);
    for (uint8_t i = 0; i < pstIn->questAchievesNum; ++i)
        if (EnCodeQUEST_ACHIEVE(pstIn->questAchieves + i, poNetData) == -1)
            return -1;
    ENCODE_INT64(isProhibitChat);
    ENCODE_BYTE(isSupport);
    ENCODE_STRING(playerName);

    END_ENCODE();
}

static  int DecodeEnterMSReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_EnterMSReq);
    DECODE_DWORD(sessionid);
    DECODE_DWORD(nMS2GSSessionID);
    DECODE_DWORD(token);
    DECODE_QWORD(playerid);
    DECODE_CHAR(entertype);
    DECODE_CHAR(fangchenmi);
    DECODE_CHAR(clienttype);
    if (DeCodeROLE_BRIEF_INFO(&pstOut->roleBriefInfo, poNetData) == -1) return -1;
    if (DeCodeROLE_EXTRA_INFO(&pstOut->roleExtraInfo, poNetData) == -1) return -1;
    if (DecodeROLE_SETTINGS(&pstOut->roleSettings, poNetData) == -1) return -1;
    if (DeCodeQUEST_INFO(&pstOut->questInfo, poNetData) == -1) return -1;

    DECODE_BYTE(questAchievesNum);
    for (uint8_t i = 0; i < pstOut->questAchievesNum; ++i)
        if (DeCodeQUEST_ACHIEVE(pstOut->questAchieves + i, poNetData) == -1)
            return -1;
    DECODE_INT64(isProhibitChat);
    DECODE_BYTE(isSupport);
    DECODE_STRING(playerName);

    END_DECODE();
}

static  int EncodeEnterMSNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_EnterMSNtf);
    ENCODE_DWORD(token);
    ENCODE_QWORD(player_id);
    ENCODE_QWORD(role_id);
    END_ENCODE();
}

static  int DecodeEnterMSNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_EnterMSNtf);
    DECODE_DWORD(token);
    DECODE_QWORD(player_id);
    DECODE_QWORD(role_id);
    END_DECODE();
}

static  int EncodeGetRoleDataReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_GetRoleDataReq);
    ENCODE_DWORD(token);
    ENCODE_QWORD(playerid);
    ENCODE_QWORD(roleid);
    END_ENCODE();
}

static  int DecodeGetRoleDataReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_GetRoleDataReq);
    DECODE_DWORD(token);
    DECODE_QWORD(playerid);
    DECODE_QWORD(roleid);
    END_DECODE();
}

static  int EncodeGetRoleDataAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_GetRoleDataAck);
    ENCODE_DWORD(token);
    ENCODE_QWORD(playerid);
    ENCODE_QWORD(roleid);
    END_ENCODE();
}

static  int DecodeGetRoleDataAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_GetRoleDataAck);
    DECODE_DWORD(token);
    DECODE_QWORD(playerid);
    DECODE_QWORD(roleid);
    END_DECODE();
}

static int EncodeGetItemAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_GetItemAck);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(token);
    ENCODE_WORD(item_num);
    for (int i = 0; i < (int)pstIn->item_num; i++)
    {
 
        EnCodeITEM_INFO(&pstIn->item_info[i], poNetData);
        
    }
    END_ENCODE();
}

static int DecodeGetItemAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_GetItemAck);
    DECODE_QWORD(role_id);
    DECODE_DWORD(token);
    DECODE_WORD(item_num);
    for (int i = 0; i < (int)pstOut->item_num; i++)
    {
   
        DeCodeITEM_INFO(&pstOut->item_info[i], poNetData);
    }
    END_DECODE();
}

static int EncodeSendItemNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_SendItemNtf);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(token);
    ENCODE_WORD(item_num);
    for (int i = 0; i < (int)pstIn->item_num; i++)
    {
         if (-1 == EnCodeITEM_INFO(&pstIn->item_info[i], poNetData))
             return -1;
  
    }
 
    END_ENCODE();
}

static int DecodeSendItemNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_SendItemNtf);
    DECODE_QWORD(role_id);
    DECODE_DWORD(token);
    DECODE_WORD(item_num);
    for (int i = 0; i < (int)pstOut->item_num; i++)
    {
         if (-1 == DeCodeITEM_INFO(&pstOut->item_info[i], poNetData))
             return -1;
    
    }
  
    END_DECODE();
}

static int EncodeHeartBeatReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_HeartBeatReq);
    END_ENCODE();
}

static int DecodeHeartBeatReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_HeartBeatReq);
    END_DECODE();
}

static int EncodeHeartBeatAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_HeartBeatAck);
    END_ENCODE();
}

static int DecodeHeartBeatAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_HeartBeatAck);
    END_DECODE();
}

static int EncodeUploadConfigReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_UploadConfigReq);
    ENCODE_DWORD(ip);
    ENCODE_DWORD(port);
    END_ENCODE();
}

static int DecodeUploadConfigReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_UploadConfigReq);
    DECODE_DWORD(ip);
    DECODE_DWORD(port);
    END_DECODE();
}

static int EncodeConfigReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_ConfigReq);
    END_ENCODE();
}

static int DecodeConfigReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_ConfigReq);
    END_DECODE();
}

static int EncodeConfigAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_ConfigAck);
    ENCODE_DWORD(dbServIp);
    ENCODE_DWORD(dbServPort);
    ENCODE_DWORD(logServIp);
    ENCODE_DWORD(logServPort);
    END_ENCODE();
}

static int DecodeConfigAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_ConfigAck);
    DECODE_DWORD(dbServIp);
    DECODE_DWORD(dbServPort);
    DECODE_DWORD(logServIp);
    DECODE_DWORD(logServPort);
    END_DECODE();
}

static int EncodeSendPlayerInfo(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_SendPlayerInfo);
    ENCODE_QWORD(player_id);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(mtoken);
    ENCODE_DWORD(msessid);
    //if (EnCodeROLE_BRIEF_INFO(&pstIn->roleBriefInfo, poNetData) == -1) return -1;
    ENCODE_DWORD(nGS2CSSessionID);
    END_ENCODE();
}

static int DecodeSendPlayerInfo(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_SendPlayerInfo);
    DECODE_QWORD(player_id);
    DECODE_QWORD(role_id);
    DECODE_DWORD(mtoken);
    DECODE_DWORD(msessid);
    //if (DeCodeROLE_BRIEF_INFO(&pstOut->roleBriefInfo, poNetData) == -1) return -1;
    DECODE_DWORD(nGS2CSSessionID);
    END_DECODE();
}

static int EncodeSendMapListNTF(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_SendMAPLISTINFO);
    ENCODE_STRING(maplist);
    END_ENCODE();
}

static int DecodeSendMapListNTF(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_SendMAPLISTINFO);
    DECODE_STRING(maplist);
    END_DECODE();
}

static int EncodeSyncSkillReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_SyncSkillReq);
    ENCODE_QWORD(roleid);
    ENCODE_WORD(removeSkillNum);
    for (uint16_t i = 0; i < pstIn->removeSkillNum; ++i)
        if (EnCodeSKILL_INFO(pstIn->removeSkillInfo + i, poNetData) == -1)
            return -1;

    ENCODE_WORD(addSkillNum);
    for (uint16_t i = 0; i < pstIn->addSkillNum; ++i)
        if (EnCodeSKILL_INFO(pstIn->addSkillInfo + i, poNetData) == -1)
            return -1;

    ENCODE_WORD(updateSkillNum);
    for (uint16_t i = 0; i < pstIn->updateSkillNum; ++i)
        if (EnCodeSKILL_INFO(pstIn->updateSkillInfo + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeSyncSkillReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_SyncSkillReq);
    DECODE_QWORD(roleid);
    DECODE_WORD(removeSkillNum);
    for (uint16_t i = 0; i < pstOut->removeSkillNum; ++i)
        if (DeCodeSKILL_INFO(pstOut->removeSkillInfo + i, poNetData) == -1)
            return -1;

    DECODE_WORD(addSkillNum);
    for (uint16_t i = 0; i < pstOut->addSkillNum; ++i)
        if (DeCodeSKILL_INFO(pstOut->addSkillInfo + i, poNetData) == -1)
            return -1;

    DECODE_WORD(updateSkillNum);
    for (uint16_t i = 0; i < pstOut->updateSkillNum; ++i)
        if (DeCodeSKILL_INFO(pstOut->updateSkillInfo + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodeSyncBuffReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_SyncBuffReq);
    ENCODE_QWORD(roleid);
    ENCODE_WORD(removeNum);
    for (uint16_t i = 0; i < pstIn->removeNum; ++i) {
        ENCODE_QWORD(removeIndex[i]);
    }

    ENCODE_WORD(addNum);
    for (uint16_t i = 0; i < pstIn->addNum; ++i)
        if (EnCodeBUFF_INFO_DB(pstIn->addBuffInfo + i, poNetData) == -1)
            return -1;

    ENCODE_WORD(updateNum);
    for (uint16_t i = 0; i < pstIn->updateNum; ++i)
        if (EnCodeBUFF_INFO_DB(pstIn->updateBuffInfo + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeSyncBuffReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_SyncBuffReq);
    DECODE_QWORD(roleid);
    DECODE_WORD(removeNum);
    for (uint16_t i = 0; i < pstOut->removeNum; ++i) {
        DECODE_QWORD(removeIndex[i]);
    }

    DECODE_WORD(addNum);
    for (uint16_t i = 0; i < pstOut->addNum; ++i)
        if (DeCodeBUFF_INFO_DB(pstOut->addBuffInfo + i, poNetData) == -1)
            return -1;

    DECODE_WORD(updateNum);
    for (uint16_t i = 0; i < pstOut->updateNum; ++i)
        if (DeCodeBUFF_INFO_DB(pstOut->updateBuffInfo + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodeRoleExtraInfoNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_RoleExtraInfoNtf);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    if (EnCodeROLE_EXTRA_INFO(&pstIn->roleExtraInfo, poNetData) == -1)
        return -1;
    if (EncodeROLE_SETTINGS(&pstIn->roleSettings, poNetData) == -1)
        return -1;
    END_ENCODE();
}

static int DecodeRoleExtraInfoNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_RoleExtraInfoNtf);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    if (DeCodeROLE_EXTRA_INFO(&pstOut->roleExtraInfo, poNetData) == -1)
        return -1;
    if (DecodeROLE_SETTINGS(&pstOut->roleSettings, poNetData) == -1)
        return -1;
    END_DECODE();
}

static int EncodeSyncQuestReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_SyncQuestReq);
    ENCODE_QWORD(roleid);

    if (EnCodeQUEST_INFO(&pstIn->quest_info, poNetData) == -1)
        return -1;

    ENCODE_BYTE(remove_num);
    for (uint8_t i = 0; i < pstIn->remove_num; ++i)
        if (EnCodeQUEST_ACHIEVE(pstIn->remove_achev + i, poNetData) == -1)
            return -1;

    ENCODE_BYTE(add_num);
    for (uint8_t i = 0; i < pstIn->add_num; ++i)
        if (EnCodeQUEST_ACHIEVE(pstIn->add_achev + i, poNetData) == -1)
            return -1;

    ENCODE_BYTE(update_num);
    for (uint8_t i = 0; i < pstIn->update_num; ++i)
        if (EnCodeQUEST_ACHIEVE(pstIn->update_achev + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeSyncQuestReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_SyncQuestReq);
    DECODE_QWORD(roleid);

    if (DeCodeQUEST_INFO(&pstOut->quest_info, poNetData) == -1)
        return -1;

    DECODE_BYTE(remove_num);
    for (uint8_t i = 0; i < pstOut->remove_num; ++i)
        if (DeCodeQUEST_ACHIEVE(pstOut->remove_achev + i, poNetData) == -1)
            return -1;

    DECODE_BYTE(add_num);
    for (uint8_t i = 0; i < pstOut->add_num; ++i)
        if (DeCodeQUEST_ACHIEVE(pstOut->add_achev + i, poNetData) == -1)
            return -1;

    DECODE_BYTE(update_num);
    for (uint8_t i = 0; i < pstOut->update_num; ++i)
        if (DeCodeQUEST_ACHIEVE(pstOut->update_achev + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodeGetConstantCfgAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_GetConstantCfgAck);

    if (-1 == EnCodeCUSTOM_INFO(&pstIn->custom, poNetData))
        return -1;

    END_ENCODE();
}

static int DecodeGetConstantCfgAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_GetConstantCfgAck);

    if (-1 == DeCodeCUSTOM_INFO(&pstOut->custom, poNetData))
        return -1;

    END_DECODE();
}

static int EncodeGetTradeBuyDelegateAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_GetTradeBuyDelegateAck);
    ENCODE_WORD(num);
    ENCODE_WORD(packIdx);

    for (uint16_t i = 0; i < pstIn->num; ++i)
    {
        if (EnCodeDELEGATE_BUY_ITEM2(&pstIn->delegateInfo[i], poNetData) == -1)
            return -1;
    }

    END_ENCODE();
}

static int DecodeGetTradeBuyDelegateAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_GetTradeBuyDelegateAck);
    DECODE_WORD(num);
    DECODE_WORD(packIdx);

    for (uint16_t i = 0; i < pstOut->num; ++i) 
    {
        if (DeCodeDELEGATE_BUY_ITEM2(&pstOut->delegateInfo[i], poNetData) == -1)
            return -1;
    }

    END_DECODE();
}

static int EncodeGetTradeSellDelegateAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_GetTradeSellDelegateAck);
    ENCODE_WORD(num);
    ENCODE_WORD(packIdx);

    for (uint16_t i = 0; i < pstIn->num; ++i)
    {
        if (EnCodeDELEGATE_SELL_ITEM(&pstIn->delegateInfo[i], poNetData) == -1)
            return -1;
    }

    END_ENCODE();
}

static int DecodeGetTradeSellDelegateAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_GetTradeSellDelegateAck);
    DECODE_WORD(num);
    DECODE_WORD(packIdx);

    for (uint16_t i = 0; i < pstOut->num; ++i)
    {
        if (DeCodeDELEGATE_SELL_ITEM(&pstOut->delegateInfo[i], poNetData) == -1)
            return -1;
    }

    END_DECODE();
}

static int EncodeGetTradeRecordsAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_GetTradeRecordsAck);
    ENCODE_WORD(num);
    ENCODE_WORD(packIdx);

    for (uint16_t i = 0; i < pstIn->num; ++i)
    {
        if (EnCodeLOGTRADE_DATA(&pstIn->trade_record[i].logTradeData, poNetData) == -1)
            return -1;
        if (EnCodeITEM_INFO(&pstIn->trade_record[i].item, poNetData) == -1)
            return -1;
    }

    END_ENCODE();
}

static int DecodeGetTradeRecordsAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_GetTradeRecordsAck);
    DECODE_WORD(num);
    DECODE_WORD(packIdx);

    for (uint16_t i = 0; i < pstOut->num; ++i)
    {
        if (DeCodeLOGTRADE_DATA(&pstOut->trade_record[i].logTradeData, poNetData) == -1)
            return -1;
        if (DeCodeITEM_INFO(&pstOut->trade_record[i].item, poNetData) == -1)
            return -1;
    }

    END_DECODE();
}


static int EncodeRecordsCancelReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_RecordsCancelAck);
    ENCODE_WORD(num);
    for (uint16_t i = 0; i < pstIn->num; ++i)
    {
        ENCODE_QWORD(trade_id[i]);
    }
    END_ENCODE();
}

static int DecodeRecordsCancelReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_RecordsCancelAck);
    DECODE_WORD(num);
    for (uint16_t i = 0; i < pstOut->num; ++i)
    {
        DECODE_QWORD(trade_id[i]);
    }
    END_DECODE();
}

static int EncodeDelegateCancelAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_DelegateCancelAck);
    ENCODE_WORD(err_type);
    ENCODE_BYTE(delegate_type);
    ENCODE_QWORD(player_guid);
    ENCODE_QWORD(trade_id);
    ENCODE_BYTE(reason);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DecodeDelegateCancelAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_DelegateCancelAck);
    DECODE_WORD(err_type);
    DECODE_BYTE(delegate_type);
    DECODE_QWORD(player_guid);
    DECODE_QWORD(trade_id);
    DECODE_BYTE(reason);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeDelegateSellAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_DelegateSellAck);
    ENCODE_WORD(err_type);
    ENCODE_DWORD(token);

    if (EnCodeDELEGATE_SELL_ITEM(&pstIn->sellItem, poNetData) == -1) return -1;

    END_ENCODE();
}

static int DecodeDelegateSellAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_DelegateSellAck);
    DECODE_WORD(err_type);
    DECODE_DWORD(token);

    if (DeCodeDELEGATE_SELL_ITEM(&pstOut->sellItem, poNetData) == -1) return -1;

    END_DECODE();
}

static int EncodeDelegateBuyAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_DelegateBuyAck);
    ENCODE_WORD(err_type);
    ENCODE_DWORD(token);

    if (EnCodeDELEGATE_BUY_ITEM2(&pstIn->buyItem, poNetData) == -1) return -1;

    END_ENCODE();
}

static int DecodeDelegateBuyAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_DelegateBuyAck);
    DECODE_WORD(err_type);
    DECODE_DWORD(token);

    if (DeCodeDELEGATE_BUY_ITEM2(&pstOut->buyItem, poNetData) == -1) return -1;

    END_DECODE();
}

static int EncodeMarketSellAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_MarketSellAck);
    ENCODE_QWORD(trade_id);
    ENCODE_QWORD(seller_guid);
    ENCODE_STRING(seller);
    ENCODE_DWORD(count);
    ENCODE_BYTE(remove);

    if (-1 == EnCodeITEM_INFO(&pstIn->item, poNetData)) return -1;

    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DecodeMarketSellAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_MarketSellAck);
    DECODE_QWORD(trade_id);
    DECODE_QWORD(seller_guid);
    DECODE_STRING(seller);
    DECODE_DWORD(count);
    DECODE_BYTE(remove);

    if (-1 == DeCodeITEM_INFO(&pstOut->item, poNetData)) return -1;

    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeMarketBuyAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_MarketBuyAck);
    ENCODE_QWORD(trade_id);
    ENCODE_QWORD(buyer_guid);
    ENCODE_STRING(buyer);
    ENCODE_DWORD(count);
    ENCODE_BYTE(remove);

    if (-1 == EnCodeITEM_INFO(&pstIn->item, poNetData)) return -1;

    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DecodeMarketBuyAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_MarketBuyAck);
    DECODE_QWORD(trade_id);
    DECODE_QWORD(buyer_guid);
    DECODE_STRING(buyer);
    DECODE_DWORD(count);
    DECODE_BYTE(remove);

    if (-1 == DeCodeITEM_INFO(&pstOut->item, poNetData)) return -1;

    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeGetMailAttachmentAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_GetMailAttachmentAck);
    ENCODE_QWORD(mail_guid);
    ENCODE_BYTE(index);

    if (-1 == EnCodeITEM_INFO(&pstIn->item, poNetData)) return -1;

    ENCODE_WORD(err_type);
    END_ENCODE();
}

static int DecodeGetMailAttachmentAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_GetMailAttachmentAck);
    DECODE_QWORD(mail_guid);
    DECODE_BYTE(index);

    if (-1 == DeCodeITEM_INFO(&pstOut->item, poNetData)) return -1;

    DECODE_WORD(err_type);
    END_DECODE();
}

static int EncodeGetGuildsAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_GetGuildsAck);

    auto count = static_cast<uint16_t>(pstIn->guilds.size());
    if (poNetData->AddWord(count) == -1) return -1;

    for (const auto &it : pstIn->guilds)
        if (EnCodeGUILD_INFO(it.second.get(), poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeGetGuildsAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(Proto_General);

    uint16_t count = 0;
    if (poNetData->DelWord(count) == -1) return -1;

    auto guilds = std::make_unique<GUILD_MAP>();

    for (uint16_t i = 0; i < count; ++i) {

        auto guild = std::make_shared<GUILD_INFO>();

        if (DeCodeGUILD_INFO(guild.get(), poNetData) == -1)
            return -1;

        guilds->emplace(guild->id, std::move(guild));
    }

    pstOut->data = guilds.release();

    END_DECODE();
}

static int EncodeGetGuildMembersAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_GetGuildMembersAck);

    auto count = static_cast<uint16_t>(pstIn->members.size());
    if (poNetData->AddWord(count) == -1) return -1;

    for (const auto &it : pstIn->members)
        if (EnCodeGUILD_MEMBER(it.second.get(), poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeGetGuildMembersAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(Proto_General);

    uint16_t count = 0;
    if (poNetData->DelWord(count) == -1) return -1;

    auto members = std::make_unique<GUILD_MEMBER_MAP>();

    for (uint16_t i = 0; i < count; ++i) {

        auto member = std::make_shared<GUILD_MEMBER>();

        if (DeCodeGUILD_MEMBER(member.get(), poNetData) == -1)
            return -1;

        members->emplace(member->player_id, std::move(member));
    }

    pstOut->data = members.release();

    END_DECODE();
}

static int EncodeGetGuildApplicantsAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_GetGuildApplicantsAck);

    auto count = static_cast<uint16_t>(pstIn->applicants.size());
    if (poNetData->AddWord(count) == -1) return -1;

    for (const auto &apply : pstIn->applicants)
        if (EnCodeGUILD_APPLY_INFO(apply.get(), poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeGetGuildApplicantsAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(Proto_General);

    uint16_t count = 0;
    if (poNetData->DelWord(count) == -1) return -1;

    auto applicants = std::make_unique<GUILD_APPLICANT_LIST>();

    for (uint16_t i = 0; i < count; ++i) {

        auto apply = std::make_shared<GUILD_APPLY_INFO>();

        if (DeCodeGUILD_APPLY_INFO(apply.get(), poNetData) == -1)
            return -1;

        applicants->emplace_back(std::move(apply));
    }

    pstOut->data = applicants.release();

    END_DECODE();
}

static int EncodeSyncPlayerCustVar(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_SyncPlayerCustVar);
    ENCODE_QWORD(roleid);

    if (!pstIn->add) return -1;

    auto count = static_cast<uint16_t>(pstIn->add->size());
    if (poNetData->AddWord(count) == -1) return -1;

    for (auto &var : *pstIn->add)
        if (EnCodeCUST_VAR(&var, poNetData) == -1)
            return -1;

    count = static_cast<uint16_t>(pstIn->remove->size());
    if (poNetData->AddWord(count) == -1) return -1;

    for (auto &var : *pstIn->remove)
        if (EnCodeCUST_VAR(&var, poNetData) == -1)
            return -1;

    count = static_cast<uint16_t>(pstIn->update->size());
    if (poNetData->AddWord(count) == -1) return -1;

    for (auto &var : *pstIn->update)
        if (EnCodeCUST_VAR(&var, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeSyncPlayerCustVar(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_SyncPlayerCustVar);
    DECODE_QWORD(roleid);

    auto add = std::make_unique<CUST_VAR_LIST>();

    uint16_t count = 0;
    if (poNetData->DelWord(count) == -1) return -1;

    for (uint16_t i = 0; i < count; ++i) {

        add->push_back(CUST_VAR());
        auto &var = add->back();

        if (DeCodeCUST_VAR(&var, poNetData) == -1) return -1;
    }

    auto remove = std::make_unique<CUST_VAR_LIST>();

    if (poNetData->DelWord(count) == -1) return -1;

    for (uint16_t i = 0; i < count; ++i) {

        remove->push_back(CUST_VAR());
        auto &var = remove->back();

        if (DeCodeCUST_VAR(&var, poNetData) == -1) return -1;
    }

    auto update = std::make_unique<CUST_VAR_LIST>();

    if (poNetData->DelWord(count) == -1) return -1;

    for (uint16_t i = 0; i < count; ++i) {

        update->push_back(CUST_VAR());
        auto &var = update->back();

        if (DeCodeCUST_VAR(&var, poNetData) == -1) return -1;
    }

    pstOut->add = add.release();
    pstOut->remove = remove.release();
    pstOut->update = update.release();

    END_DECODE();
}

static int EncodeSyncItemCustVar(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_SyncItemCustVar);

    if (EnCodeCUST_VAR_SP_LIST(pstIn->add, poNetData) == -1) return -1;

    if (EnCodeCUST_VAR_SP_LIST(pstIn->remove, poNetData) == -1) return -1;

    if (EnCodeCUST_VAR_SP_LIST(pstIn->update, poNetData) == -1) return -1;

    END_ENCODE();
}

static int DecodeSyncItemCustVar(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_SyncItemCustVar);

    auto add = std::make_unique<CUST_VAR_SP_LIST>();
    if (DeCodeCUST_VAR_SP_LIST(add.get(), poNetData) == -1) return -1;

    auto remove = std::make_unique<CUST_VAR_SP_LIST>();
    if (DeCodeCUST_VAR_SP_LIST(remove.get(), poNetData) == -1) return -1;

    auto update = std::make_unique<CUST_VAR_SP_LIST>();
    if (DeCodeCUST_VAR_SP_LIST(update.get(), poNetData) == -1) return -1;

    pstOut->add = add.release();
    pstOut->remove = remove.release();
    pstOut->update = update.release();

    END_DECODE();
}

static int EncodeSyncQuickBarSet(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_SyncQuickBarSet);
    ENCODE_WORD(num);

    for (uint8_t i = 0; i < pstIn->num; ++i)
    {
        if (-1 == EnCodeQUICK_BAR_LIST_INFO(&pstIn->info[i], poNetData))
            return -1;
    }
    END_ENCODE();
}

static int DecodeSyncQuickBarSet(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_SyncQuickBarSet);
    DECODE_WORD(num);

    for (uint8_t i = 0; i < pstOut->num; i++)
    {
        if (-1 == DeCodeQUICK_BAR_LIST_INFO(&pstOut->info[i], poNetData))
            return -1;
    }
    END_DECODE();
}

static int EncodeSyncQuickBarSetNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_QuickBarSetNtf);
    ENCODE_WORD(num);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(token);

    for (uint16_t i = 0; i < pstIn->num; ++i)
        if (EnCodeQUICK_BAR_INFO(pstIn->info + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeSyncQuickBarSetNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_QuickBarSetNtf);
    DECODE_WORD(num);
    DECODE_QWORD(role_id);
    DECODE_DWORD(token);

    for (uint16_t i = 0; i < pstOut->num; ++i)
        if (DeCodeQUICK_BAR_INFO(pstOut->info + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodeSyncDgnBindInfoNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_DgnBindInfoNtf);
    ENCODE_WORD(num);
    ENCODE_QWORD(roleId);
    ENCODE_DWORD(token);

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

static int DecodeSyncDgnBindInfoNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_DgnBindInfoNtf);
    DECODE_WORD(num);
    DECODE_QWORD(roleId);
    DECODE_DWORD(token);

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

static int EncodeSyncDgnBindInfo(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_SyncDgnBindInfo);
    ENCODE_WORD(packIdx);
    ENCODE_WORD(num);
    ENCODE_QWORD(roleId);

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

static int DecodeSyncDgnBindInf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_SyncDgnBindInfo);
    DECODE_WORD(packIdx);
    DECODE_WORD(num);
    DECODE_QWORD(roleId);

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

static int EncodeGlobalNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_GlobalNtf);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(token);
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
};

static int DecodeGlobalNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_GlobalNtf);
    DECODE_QWORD(role_id);
    DECODE_DWORD(token);
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
};

static int EncodeGMModLevel(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_GMModLevel);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(GMModLevel);
    END_ENCODE();
};

static int DecodeGMModLevel(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_GMModLevel);
    DECODE_QWORD(role_id);
    DECODE_DWORD(GMModLevel);
    END_DECODE();
};

static int EncodeTopListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_TopListReq);

    END_ENCODE();
}

static int DecodeTopListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_TopListReq);
    
    END_DECODE();
}

static int EncodeGetMailInfo(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_GetMailInfo);
    ENCODE_QWORD(playerguid);
    END_ENCODE();
}

static int DecodeGetMailInfo(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_GetMailInfo);
    DECODE_QWORD(playerguid);
    END_DECODE();
}

static int EncodeUpdateTables(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_UpdateTables);
    ENCODE_DWORD(len);
    ENCODE_BLOB(data, pstIn->len);
    END_ENCODE();
}

static int DecodeUpdateTables(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_UpdateTables);
    DECODE_DWORD(len);
    pstOut->data = (uint8_t *)poNetData->m_pBuf + poNetData->m_iPos;
    END_DECODE();
}


static int EncodeCustomHttpAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoCS_CustomHttpAck);
    ENCODE_STRING(func);
    ENCODE_STRING(data);
    END_ENCODE();
}

static int DecodeCustomHttpAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoCS_CustomHttpAck);
    DECODE_STRING(func);
    DECODE_STRING(data);
    END_DECODE();
}

ProtoCS::ProtoCS()
{
    SET_ENCODER_DECODER(PROTO_CS_GET_ROLE_DATA_REQ, EncodeGetRoleDataReq, DecodeGetRoleDataReq);
    SET_ENCODER_DECODER(PROTO_CS_GET_ROLE_DATA_ACK, EncodeGetRoleDataAck, DecodeGetRoleDataAck);

    SET_ENCODER_DECODER(PROTO_CS_CLEAR_ROLE_INFO_NTF, EncodeClearRoleInfoNtf, DecodeClearRoleInfoNtf);
    SET_ENCODER_DECODER(PROTO_CS_DELETE_ROLE_INFO_NTF, EncodeDeleteRoleInfoNtf, DecodeDeleteRoleInfoNtf);
    SET_ENCODER_DECODER(PROTO_CS_UPDATE_ROLE_INFO_NTF, EncodeUpdateRoleInfoNtf, DecodeUpdateRoleInfoNtf);
    SET_ENCODER_DECODER(PROTO_CS_INSERT_ROLE_INFO_NTF, EncodeInsertRoleInfoNtf, DecodeInsertRoleInfoNtf);
    SET_ENCODER_DECODER(PROTO_CS_GET_ROLE_INFO_REQ, EncodeGetRoleInfoReq, DecodeGetRoleInfoReq);
    SET_ENCODER_DECODER(PROTO_CS_GET_ROLE_INFO_ACK, EncodeGetRoleInfoAck, DecodeGetRoleInfoAck);

    SET_ENCODER_DECODER(PROTO_CS_DELETE_ITEM_NTF, EncodeDeleteItemNtf, DecodeDeleteItemNtf);
    SET_ENCODER_DECODER(PROTO_CS_UPDATE_ITEM_NTF, EncodeUpdateItemNtf, DecodeUpdateItemNtf);
    SET_ENCODER_DECODER(PROTO_CS_INSERT_ITEM_NTF, EncodeInsertItemNtf, DecodeInsertItemNtf);
    SET_ENCODER_DECODER(PROTO_CS_ENTER_MS_REQ, EncodeEnterMSReq, DecodeEnterMSReq);
    SET_ENCODER_DECODER(PROTO_CS_ENTER_MS_NTF, EncodeEnterMSNtf, DecodeEnterMSNtf);
    SET_ENCODER_DECODER(PROTO_CS_SEND_ITEM_NTF, EncodeSendItemNtf, DecodeSendItemNtf);
    SET_ENCODER_DECODER(PROTO_CS_GET_ITEM_ACK, EncodeGetItemAck, DecodeGetItemAck);

    SET_ENCODER_DECODER(PROTO_CS_HEART_BEAT_REQ, EncodeHeartBeatReq, DecodeHeartBeatReq);
    SET_ENCODER_DECODER(PROTO_CS_HEART_BEAT_ACK, EncodeHeartBeatAck, DecodeHeartBeatAck);
    SET_ENCODER_DECODER(PROTO_CS_UPLOAD_CONFIG_REQ, EncodeUploadConfigReq, DecodeUploadConfigReq);
    SET_ENCODER_DECODER(PROTO_CS_CONFIG_REQ, EncodeConfigReq, DecodeConfigReq);
    SET_ENCODER_DECODER(PROTO_CS_CONFIG_ACK, EncodeConfigAck, DecodeConfigAck);
    SET_ENCODER_DECODER(PROTO_CS_SEND_PLAYER_INFO, EncodeSendPlayerInfo, DecodeSendPlayerInfo);
    SET_ENCODER_DECODER(PROTO_CS_SEND_MAP_LIST_NTF, EncodeSendMapListNTF, DecodeSendMapListNTF);
    SET_ENCODER_DECODER(PROTO_CS_SYNC_SKILL_REQ, EncodeSyncSkillReq, DecodeSyncSkillReq);
    SET_ENCODER_DECODER(PROTO_CS_SYNC_BUFF_REQ, EncodeSyncBuffReq, DecodeSyncBuffReq);
    SET_ENCODER_DECODER(PROTO_CS_ROLE_EXTRA_INFO_NTF, EncodeRoleExtraInfoNtf, DecodeRoleExtraInfoNtf);
    SET_ENCODER_DECODER(PROTO_CS_SYNC_QUEST_REQ, EncodeSyncQuestReq, DecodeSyncQuestReq);
    SET_ENCODER_DECODER(PROTO_CS_GET_GUILDS_ACK, EncodeGetGuildsAck, DecodeGetGuildsAck);
    SET_ENCODER_DECODER(PROTO_CS_GET_GUILD_MEMBERS_ACK, EncodeGetGuildMembersAck, DecodeGetGuildMembersAck);
    SET_ENCODER_DECODER(PROTO_CS_GET_GUILD_APPLICANTS_ACK, EncodeGetGuildApplicantsAck, DecodeGetGuildApplicantsAck);
    SET_ENCODER_DECODER(PROTO_CS_SYNC_PLAYER_CUST_VAR, EncodeSyncPlayerCustVar, DecodeSyncPlayerCustVar);
    SET_ENCODER_DECODER(PROTO_CS_SYNC_ITEM_CUST_VAR, EncodeSyncItemCustVar, DecodeSyncItemCustVar);
    SET_ENCODER_DECODER(PROTO_CS_QUICK_BAR_SET, EncodeSyncQuickBarSet, DecodeSyncQuickBarSet);
    SET_ENCODER_DECODER(PROTO_CS_QUICK_BAR_SET_NTF, EncodeSyncQuickBarSetNtf, DecodeSyncQuickBarSetNtf);
    SET_ENCODER_DECODER(PROTO_CS_DGN_BIND_INFO_NTF, EncodeSyncDgnBindInfoNtf, DecodeSyncDgnBindInfoNtf);
    SET_ENCODER_DECODER(PROTO_CS_DGN_BIND_INFO, EncodeSyncDgnBindInfo, DecodeSyncDgnBindInf);
    SET_ENCODER_DECODER(PROTO_CS_GLOBAL_NTF, EncodeGlobalNtf, DecodeGlobalNtf);
    SET_ENCODER_DECODER(PROTO_CS_GM_MOD_LEVEL, EncodeGMModLevel, DecodeGMModLevel);
    SET_ENCODER_DECODER(PROTO_CS_TOPLIST_REQ, EncodeTopListReq, DecodeTopListReq);
    SET_ENCODER_DECODER(PROTO_CS_GET_MAIL_INFO, EncodeGetMailInfo, DecodeGetMailInfo);
    SET_ENCODER_DECODER(PROTO_CS_GET_TRADE_BUY_DELEGATE_ACK, EncodeGetTradeBuyDelegateAck, DecodeGetTradeBuyDelegateAck);
    SET_ENCODER_DECODER(PROTO_CS_GET_TRADE_SELL_DELEGATE_ACK, EncodeGetTradeSellDelegateAck, DecodeGetTradeSellDelegateAck);
    SET_ENCODER_DECODER(PROTO_CS_GET_TRADE_RECORDS_ACK, EncodeGetTradeRecordsAck, DecodeGetTradeRecordsAck);
    SET_ENCODER_DECODER(PROTO_CS_RECORDS_CANCEL_ACK, EncodeRecordsCancelReq, DecodeRecordsCancelReq);
    SET_ENCODER_DECODER(PROTO_CS_DELEGATE_CANCEL_ACK, EncodeDelegateCancelAck, DecodeDelegateCancelAck);
    SET_ENCODER_DECODER(PROTO_CS_DELEGATE_SELL_ACK, EncodeDelegateSellAck, DecodeDelegateSellAck);
    SET_ENCODER_DECODER(PROTO_CS_DELEGATE_BUY_ACK, EncodeDelegateBuyAck, DecodeDelegateBuyAck);
    SET_ENCODER_DECODER(PROTO_CS_MARKET_SELL_ACK, EncodeMarketSellAck, DecodeMarketSellAck);
    SET_ENCODER_DECODER(PROTO_CS_MARKET_BUY_ACK, EncodeMarketBuyAck, DecodeMarketBuyAck);
    SET_ENCODER_DECODER(PROTO_CS_GET_MAIL_ATTACHMENT_ACK, EncodeGetMailAttachmentAck, DecodeGetMailAttachmentAck);
    SET_ENCODER_DECODER(PROTO_CS_AUCTION_GET_FINISHED_INFO_ACK, EncodeAuctionGetFinishedInfoAck, DecodeAuctionGetFinishedInfoAck);
    SET_ENCODER_DECODER(PROTO_CS_RUN_GM_CMD_ACK, EncodeRunGmCmdAck, DecodeRunGmCmdAck);
    SET_ENCODER_DECODER(PROTO_CS_GET_CONSTANT_CFG_ACK, EncodeGetConstantCfgAck, DecodeGetConstantCfgAck);
    SET_ENCODER_DECODER(PROTO_CS_GET_MALL_LIMIT_INFO_SINGLE_ACK, EncodeGetMallLimitInfoSingleAck, DecodeGetMallLimitInfoSingleAck);
    SET_ENCODER_DECODER(PROTO_CS_MALL_LIST_UPDATE, EncodeMallListUpdate, DecodeMallListUpdate);
    SET_ENCODER_DECODER(PROTO_CS_ACTIVATION_CODE_ACK, EncodeActivationCodeAck, DecodeActivationCodeAck);
    SET_ENCODER_DECODER(PROTO_CS_SYNC_ROLE_INFO, EncodeSyncRoleInfo, DecodeSyncRoleInfo);
    SET_ENCODER_DECODER(PROTO_CS_UPDATE_TABLES, EncodeUpdateTables, DecodeUpdateTables);
    SET_ENCODER_DECODER(PROTO_CS_CUSTOM_HTTP_ACK, EncodeCustomHttpAck, DecodeCustomHttpAck);
}

ProtoCS::~ProtoCS()
{

}

int ProtoCS::BuildProtocol(void* pHost, char* pNet, int iNetSize)
{
    unsigned short moduleid = *(unsigned short*)pHost;
    unsigned short protoid = *(unsigned short*)((char*)pHost + sizeof(unsigned short));
    if (moduleid != GetModuleID()) {
        return -1;
    }
    if (protoid >= PROTO_CS_MAX) {
        return -1;
    }

    CNetData m_oData;
    m_oData.Prepare(pNet, iNetSize);
    return m_EnCodeFuncArray[protoid](pHost, &m_oData);
}

int ProtoCS::HandleProtocol(void* pNet, char* pHost, int iNetSize)
{
    unsigned short moduleid = *(unsigned short*)pNet;
    unsigned short protoid = *(unsigned short*)((char*)pNet + sizeof(unsigned short));
    if (moduleid != GetModuleID()) {
        return -1;
    }
    if (protoid >= PROTO_CS_MAX) {
        return -1;
    }

    CNetData m_oData;
    m_oData.Prepare((char*)pNet, iNetSize);
    return m_DeCodeFuncArray[protoid](pHost, &m_oData);
}