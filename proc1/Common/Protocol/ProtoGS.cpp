#include "stdafx.h"
#include "ProtoGS.h"

static int EncodeGoodsPostRecordAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_GoodsPostRecordAck);
    ENCODE_QWORD(guid);
    ENCODE_STRING(order_no);
    END_ENCODE();
}

static int DecodeGoodsPostRecordAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_GoodsPostRecordAck);
    DECODE_QWORD(guid);
    DECODE_STRING(order_no);
    END_ENCODE();
}

static int EncodeAfterReloginUpdateStatus(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_AfterReloginUpdateStatus);
    ENCODE_QWORD(guid);
    END_ENCODE();
}

static int DecodeAfterReloginUpdateStatus(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_AfterReloginUpdateStatus);
    DECODE_QWORD(guid);
    END_DECODE();
}

static int EncodeTitleGetListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TitleGetListReq);
    ENCODE_QWORD(guid);
    END_ENCODE();
}

static int DecodeTitleGetListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TitleGetListReq);
    DECODE_QWORD(guid);
    END_DECODE();
}

static int EncodeTitleAddAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TitleAddAck);
    if (-1 == EnCodeTITLE_INFO(&pstIn->info, poNetData))return -1;
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodeTitleAddAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TitleAddAck);
    if (-1 == DeCodeTITLE_INFO(&pstOut->info , poNetData))return -1;
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodeTitleDel(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TitleDel);
    ENCODE_QWORD(guid);
    ENCODE_DWORD(id);
    END_ENCODE();
}

static int DecodeTitleDel(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TitleDel);
    DECODE_QWORD(guid);
    DECODE_DWORD(id);
    END_DECODE();
}

static int EncodeTitleDelAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TitleDelAck);
    ENCODE_DWORD(id);
    ENCODE_BYTE(err);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodeTitleDelAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TitleDelAck);
    DECODE_DWORD(id);
    DECODE_BYTE(err);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodeTitleWear(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TitleWear);
    ENCODE_QWORD(guid);
    ENCODE_DWORD(id);
    END_ENCODE();
}

static int DecodeTitleWear(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TitleWear);
    DECODE_QWORD(guid);
    DECODE_DWORD(id);
    END_DECODE();
}

static int EncodeTitleWearNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TitleWearNtf);
    ENCODE_QWORD(guid);
    ENCODE_DWORD(id);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodeTitleWearNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TitleWearNtf);
    DECODE_QWORD(guid);
    DECODE_DWORD(id);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodeTitleUnWear(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TitleUnWear);
    ENCODE_QWORD(guid);
    ENCODE_DWORD(id);
    END_ENCODE();
}

static int DecodeTitleUnWear(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TitleUnWear);
    DECODE_QWORD(guid);
    DECODE_DWORD(id);
    END_DECODE();
}

static int EncodeTitleUnWearNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TitleUnWearNtf);
    ENCODE_QWORD(guid);
    ENCODE_DWORD(id);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodeTitleUnWearNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TitleUnWearNtf);
    DECODE_QWORD(guid);
    DECODE_DWORD(id);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodeTitleList(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TitleList);
    ENCODE_QWORD(guid);
    ENCODE_WORD(num);
    for (int i = 0; i < pstIn->num; ++i) {
        if (-1 == EnCodeTITLE_INFO(pstIn->info + i, poNetData))return -1;
    }
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodeTitleList(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TitleList);
    DECODE_QWORD(guid);
    DECODE_WORD(num);
    for (int i = 0; i < pstOut->num; ++i) {
        if (-1 == DeCodeTITLE_INFO(pstOut->info + i, poNetData))return -1;
    }
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodePlayerSetNameNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_PlayerSetNameNtf);
    ENCODE_QWORD(guid);
    ENCODE_STRING(name);
    ENCODE_STRING(orgName);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodePlayerSetNameNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_PlayerSetNameNtf);
    DECODE_QWORD(guid);
    DECODE_STRING(name);
    DECODE_STRING(orgName);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodeKickOutByLock(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_KickOutByLock);
    ENCODE_DWORD(sessionid);
    ENCODE_DWORD(token);
    ENCODE_BYTE(info);
    ENCODE_BYTE(type);
    END_ENCODE();
}

static int DecodeKickOutByLock(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_KickOutByLock);
    DECODE_DWORD(sessionid);
    DECODE_DWORD(token);
    DECODE_BYTE(info);
    DECODE_BYTE(type);
    END_DECODE();
}

static int EncodeSetMaintenanceStatus(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_SetMaintenanceStatus);
    ENCODE_BYTE(status);
    END_ENCODE();
}

static int DecodeSetMaintenanceStatus(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_SetMaintenanceStatus);
    DECODE_BYTE(status);
    END_DECODE();
}


static int EncodeTradeMallListUpdate(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TradeMallListUpdate);
    ENCODE_DWORD(sessionid);
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
    BEGIN_DECODE_EX(ProtoGS_TradeMallListUpdate);
    DECODE_DWORD(sessionid);
    DECODE_BYTE(item_count);

    int maxCount = std::min<int>((int)pstOut->item_count, (int)_countof(pstOut->item_list));
    for (int i = 0; i < pstOut->item_count; ++i) {
        if (-1 == DeCodeMALL_ITEM_INFO(&pstOut->item_list[i], poNetData))
            return -1;
    }

    END_DECODE();
}

static int EncodeSysMsgNtf2(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_SysMsgNtf2);
    if (-1 == EncodeSYSTEN_MESSAGE_NTF(&pstIn->info, poNetData))
        return -1;
    ENCODE_DWORD(sessid);
    ENCODE_BYTE(all);
    END_ENCODE();
}

static int DecodeSysMsgNtf2(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_SysMsgNtf2);
    if (-1 == DecodeSYSTEN_MESSAGE_NTF(&pstOut->info, poNetData))
        return -1;
    DECODE_DWORD(sessid);
    DECODE_BYTE(all);
    END_DECODE();
}

static int EncodeSceneDialogNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_SceneDialogNtf);
    if (-1 == EncodeSCENCE_DIALOG_NTF(&pstIn->info, poNetData))
        return -1;
    ENCODE_DWORD(sessid);
    END_ENCODE();
}

static int DecodeSceneDialogNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_SceneDialogNtf);
    if (-1 == DecodeSCENCE_DIALOG_NTF(&pstOut->info, poNetData))
        return -1;
    DECODE_DWORD(sessid);
    END_DECODE();
}

static int EncodeScrollText(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_ScrollText);
    if (-1 == EncodeSCROLL_TEXT(&pstIn->info, poNetData))
        return -1;
    ENCODE_DWORD(sessid);
    ENCODE_BYTE(all);
    END_ENCODE();
}

static int DecodeScrollText(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_ScrollText);
    if (-1 == DecodeSCROLL_TEXT(&pstOut->info, poNetData))
        return -1;
    DECODE_DWORD(sessid);
    DECODE_BYTE(all);
    END_DECODE();
}

static int EnCodeSessionIDNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_SessionIDNtf);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DeCodeSessionIDNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_SessionIDNtf);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EnCodePlayerReliveReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_PlayerReliveReq);
    ENCODE_BYTE(relive_type);
    ENCODE_DWORD(sessionid);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DeCodePlayerReliveReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_PlayerReliveReq);
    DECODE_BYTE(relive_type);
    DECODE_DWORD(sessionid);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EnCodePlayerReliveAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_PlayerReliveAck);
    ENCODE_BYTE(relive_type);
    ENCODE_INT(error_code);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DeCodePlayerReliveAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_PlayerReliveAck);
    DECODE_BYTE(relive_type);
    DECODE_INT(error_code);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodeReloginAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_ReloginAck);
    ENCODE_INT(errcode);
    ENCODE_STRING(errmsg);
    ENCODE_QWORD(player_guid);
    ENCODE_QWORD(role_guid);
    ENCODE_STRING(username);
    ENCODE_STRING(password);
    ENCODE_DWORD(token);
    ENCODE_STRING(randkey);
    ENCODE_DWORD(cl2gs_sessid);
    END_ENCODE();
}

static int DecodeReloginAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_ReloginAck);
    DECODE_INT(errcode);
    DECODE_STRING(errmsg);
    DECODE_QWORD(player_guid);
    DECODE_QWORD(role_guid);
    DECODE_STRING(username);
    DECODE_STRING(password);
    DECODE_DWORD(token);
    DECODE_STRING(randkey);
    DECODE_DWORD(cl2gs_sessid);
    END_DECODE();
}

static int EncodeItemApply(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_ItemApply);
    ENCODE_QWORD(item_guid);
    ENCODE_DWORD(num);
    ENCODE_DWORD(sessid);
    ENCODE_DWORD(token);
    ENCODE_QWORD(role_guid);
    END_ENCODE();

}

static int DecodeItemApply(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_ItemApply);
    DECODE_QWORD(item_guid);
    DECODE_DWORD(num);
    DECODE_DWORD(sessid);
    DECODE_DWORD(token);
    DECODE_QWORD(role_guid);
    END_DECODE();
}


static int EncodeItemDrop(void* pHost, CNetData* poNetData)
{

    BEGIN_ENCODE_EX(ProtoGS_ItemDrop);
    ENCODE_QWORD(item_guid);
    ENCODE_DWORD(sessid);
    ENCODE_DWORD(token);
    END_ENCODE();

}
static int DecodeItemDrop(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_ItemDrop);
    DECODE_QWORD(item_guid);
    DECODE_DWORD(sessid);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeItemArrange(void* pHost, CNetData* poNetData)
{

    BEGIN_ENCODE_EX(ProtoGS_ItemArrange);
    ENCODE_BYTE(type);
    ENCODE_DWORD(sessid);
    ENCODE_DWORD(token);
    END_ENCODE();

}
static int DecodeItemArrange(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_ItemArrange);
    DECODE_BYTE(type);
    DECODE_DWORD(sessid);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeHeartBeatReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_HeartBeatReq);
    END_ENCODE();
}

static int DecodeHeartBeatReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_HeartBeatReq);
    END_DECODE();
}

static int EncodeHeartBeatAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_HeartBeatAck);
    END_ENCODE();
}

static int DecodeHeartBeatAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_HeartBeatAck);
    END_DECODE();
}

static int EncodeExitReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_ExitGSReq);
    ENCODE_BYTE(exittype);
    ENCODE_DWORD(sessionid);
    ENCODE_QWORD(nrole_guid);
    END_ENCODE();
}

static int DecodeExitReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_ExitGSReq);
    DECODE_BYTE(exittype);
    DECODE_DWORD(sessionid);
    DECODE_QWORD(nrole_guid);
    END_DECODE();
}

static int EncodeExitAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_ExitGSAck);
    ENCODE_BYTE(exittype);
    ENCODE_INT(errcode);
    ENCODE_STRING(errmsg);
    ENCODE_DWORD(sessionid);
    ENCODE_QWORD(nrole_guid);
    END_ENCODE();
}

static int DecodeExitAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_ExitGSAck);
    DECODE_BYTE(exittype);
    DECODE_INT(errcode);
    DECODE_STRING(errmsg);
    DECODE_DWORD(sessionid);
    DECODE_QWORD(nrole_guid);
    END_DECODE();
}

static int EnCodeConfigReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_ConfigReq);
    END_ENCODE();
}

static int DeCodeConfigReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_ConfigReq);
    END_DECODE();
}

static int EnCodeConfigAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_ConfigAck);
    ENCODE_DWORD(loginServIp);
    ENCODE_DWORD(loginServPort);
    ENCODE_DWORD(mapServIp);
    ENCODE_DWORD(mapServPort);
    ENCODE_DWORD(centerServIp);
    ENCODE_DWORD(centerServPort);
    ENCODE_DWORD(logServIp);
    ENCODE_DWORD(logServPort);
    END_ENCODE();
}

static int DeCodeConfigAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_ConfigAck);
    DECODE_DWORD(loginServIp);
    DECODE_DWORD(loginServPort);
    DECODE_DWORD(mapServIp);
    DECODE_DWORD(mapServPort);
    DECODE_DWORD(centerServIp);
    DECODE_DWORD(centerServPort);
    DECODE_DWORD(logServIp);
    DECODE_DWORD(logServPort);
    END_DECODE();
}

static int EncodeLoginReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_LoginReq);
    ENCODE_DWORD(clsessid);
    ENCODE_STRING(username);
    ENCODE_STRING(password);
    ENCODE_DWORD(ip);
    ENCODE_STRING(hwid);
    END_ENCODE();
}

static int DecodeLoginReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_LoginReq);
    DECODE_DWORD(clsessid);
    DECODE_STRING(username);
    DECODE_STRING(password);
    DECODE_DWORD(ip);
    DECODE_STRING(hwid);
    END_DECODE();
}

static int EncodeLoginAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_LoginAck);
    ENCODE_DWORD(clsessid);
    ENCODE_INT(errcode);
    ENCODE_STRING(errmsg);
    ENCODE_STRING(username);
    ENCODE_QWORD(userid);
    ENCODE_DWORD(token);
    ENCODE_STRING(randkey);
    END_ENCODE();
}

static int DecodeLoginAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_LoginAck);
    DECODE_DWORD(clsessid);
    DECODE_INT(errcode);
    DECODE_STRING(errmsg);
    DECODE_STRING(username);
    DECODE_QWORD(userid);
    DECODE_DWORD(token);
    DECODE_STRING(randkey);
    END_DECODE();
}

static int EncodeThirdLoginReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_ThirdLoginReq);
    ENCODE_DWORD(sessionid);
    ENCODE_STRING(channel);
    ENCODE_DWORD(gameid);
    ENCODE_STRING(token);
    ENCODE_STRING(user_name);
    ENCODE_DWORD(login_ip);
    ENCODE_STRING(hwid);
    END_ENCODE();
}

static int DecodeThirdLoginReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_ThirdLoginReq);
    DECODE_DWORD(sessionid);
    DECODE_STRING(channel);
    DECODE_DWORD(gameid);
    DECODE_STRING(token);
    DECODE_STRING(user_name);
    DECODE_DWORD(login_ip);
    DECODE_STRING(hwid);
    END_DECODE();
}

static int EncodeLogoutReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_LogoutReq);
    ENCODE_DWORD(sessionid);
    ENCODE_DWORD(token);
    ENCODE_BYTE(info);
    END_ENCODE();
}

static int DecodeLogoutReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_LogoutReq);
    DECODE_DWORD(sessionid);
    DECODE_DWORD(token);
    DECODE_BYTE(info);
    END_DECODE();
}

static int EncodeReloginReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_ReloginReq);
    ENCODE_QWORD(player_guid);
    ENCODE_QWORD(role_guid);
    ENCODE_STRING(randkey);
    ENCODE_DWORD(cl2gs_sessid);
    ENCODE_DWORD(ip);
    ENCODE_STRING(hwid);
    END_ENCODE();
}

static int DecodeReloginReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_ReloginReq);
    DECODE_QWORD(player_guid);
    DECODE_QWORD(role_guid);
    DECODE_STRING(randkey);
    DECODE_DWORD(cl2gs_sessid);
    DECODE_DWORD(ip);
    DECODE_STRING(hwid);
    END_DECODE();
}

static  int EncodeEnterMapAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_EnterMapAck);
    ENCODE_DWORD(sessionid);
    ENCODE_STRING(username);
    ENCODE_WORD(id);
    END_ENCODE();
}

static  int DecodeEnterMapAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_EnterMapAck);
    DECODE_DWORD(sessionid);
    DECODE_STRING(username);
    DECODE_WORD(id);
    END_DECODE();
}

static int EncodeGetRoleListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_GS(ProtoGS_GetRoleListReq);
    END_ENCODE();
}

static int DecodeGetRoleListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_GS(ProtoGS_GetRoleListReq);
    END_DECODE();
}

static  int EncodeEnterGSReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_GS(ProtoGS_EnterGSReq);
    ENCODE_DWORD(MS2GSSessionID);
    ENCODE_CHAR(entertype);
    ENCODE_CHAR(fangchenmi);
    ENCODE_CHAR(clienttype);
    if (EnCodeROLE_BRIEF_INFO(&pstIn->roleBriefInfo, poNetData) == -1) return -1;
    END_ENCODE();
}

static  int DecodeEnterGSReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_GS(ProtoGS_EnterGSReq);
    DECODE_DWORD(MS2GSSessionID);
    DECODE_CHAR(entertype);
    DECODE_CHAR(fangchenmi);
    DECODE_CHAR(clienttype);
    if (DeCodeROLE_BRIEF_INFO(&pstOut->roleBriefInfo, poNetData) == -1) return -1;
    END_DECODE();
}

static  int EncodeEnterGSNtf(void* pHost, CNetData* poNetData)
{

    BEGIN_ENCODE_EX(ProtoGS_EnterGSNTF);
    ENCODE_QWORD(mapcode);
    ENCODE_STRING(logic);
    ENCODE_WORD(view_x);
    ENCODE_WORD(view_y);
    ENCODE_WORD(width);
    ENCODE_WORD(height);
    ENCODE_DWORD(sessionid);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static  int DecodeEnterGSNtf(void* pHost, CNetData* poNetData)
{

    BEGIN_DECODE_EX(ProtoGS_EnterGSNTF);
    DECODE_QWORD(mapcode);
    DECODE_STRING(logic);
    DECODE_WORD(view_x);
    DECODE_WORD(view_y);
    DECODE_WORD(width);
    DECODE_WORD(height);
    DECODE_DWORD(sessionid);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeGetRoleListAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_GS(ProtoGS_GetRoleListAck);
    ENCODE_INT(errcode);
    ENCODE_STRING(errmsg);
    ENCODE_BYTE(rolenum);
    ENCODE_QWORD(last_role);
    for (int i = 0; i < pstIn->rolenum; ++i) {
        EnCodeROLE_BRIEF_INFO(pstIn->rolelist + i, poNetData);
    }
    ENCODE_BYTE(needCode);
    END_ENCODE();
}

static int DecodeGetRoleListAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_GS(ProtoGS_GetRoleListAck);
    DECODE_INT(errcode);
    DECODE_STRING(errmsg);
    DECODE_BYTE(rolenum);
    DECODE_QWORD(last_role);
    for (int i = 0; i < pstOut->rolenum; ++i) {
        DeCodeROLE_BRIEF_INFO(pstOut->rolelist + i, poNetData);
    }
    DECODE_BYTE(needCode);
    END_DECODE();
}

static int EncodeCreateRoleReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_GS(ProtoGS_CreateRoleReq);
    EnCodeROLE_BRIEF_INFO(&pstIn->createrole, poNetData);
    ENCODE_BYTE(needCode);
    ENCODE_QWORD(digCode);
    END_ENCODE();
}

static int DecodeCreateRoleReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_GS(ProtoGS_CreateRoleReq);
    DeCodeROLE_BRIEF_INFO(&pstOut->createrole, poNetData);
    DECODE_BYTE(needCode);
    DECODE_QWORD(digCode);
    END_DECODE();
}

static int EncodeCreateRoleAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_GS(ProtoGS_CreateRoleAck);
    ENCODE_INT(errcode);
    ENCODE_STRING(errmsg);
    EnCodeROLE_BRIEF_INFO(&pstIn->newrole, poNetData);
    END_ENCODE();
}

static int DecodeCreateRoleAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_GS(ProtoGS_CreateRoleAck);
    DECODE_INT(errcode);
    DECODE_STRING(errmsg);
    DeCodeROLE_BRIEF_INFO(&pstOut->newrole, poNetData);
    END_DECODE();
}

static int EncodeDeleteRoleReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_GS(ProtoGS_DeleteRoleReq);
    ENCODE_QWORD(roleid);
    ENCODE_INT(status);
    END_ENCODE();
}

static int DecodeDeleteRoleReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_GS(ProtoGS_DeleteRoleReq);
    DECODE_QWORD(roleid);
    DECODE_INT(status);
    END_DECODE();
}

static int EncodeRestoreRoleReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_GS(ProtoGS_RestoreRoleReq);
    ENCODE_QWORD(roleid);
    ENCODE_INT(status);
    END_ENCODE();
}

static int DecodeRestoreRoleReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_GS(ProtoGS_RestoreRoleReq);
    DECODE_QWORD(roleid);
    DECODE_INT(status);
    END_DECODE();
}

static int EncodeDeleteRoleAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_GS(ProtoGS_DeleteRoleAck);
    ENCODE_QWORD(roleid);
    ENCODE_INT(errcode);
    ENCODE_STRING(errmsg);
    ENCODE_INT(status);
    END_ENCODE();
}

static int DecodeDeleteRoleAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_GS(ProtoGS_DeleteRoleAck);
    DECODE_QWORD(roleid);
    DECODE_INT(errcode);
    DECODE_STRING(errmsg);
    DECODE_INT(status);
    END_DECODE();
}

static int EncodeRestoreRoleAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_GS(ProtoGS_RestoreRoleAck);
    ENCODE_QWORD(roleid);
    ENCODE_INT(errcode);
    ENCODE_STRING(errmsg);
    EnCodeROLE_BRIEF_INFO(&pstIn->role, poNetData);
    END_ENCODE();
}

static int DecodeRestoreRoleAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_GS(ProtoGS_RestoreRoleAck);
    DECODE_QWORD(roleid);
    DECODE_INT(errcode);
    DECODE_STRING(errmsg);
    DeCodeROLE_BRIEF_INFO(&pstOut->role, poNetData);
    END_DECODE();
}

static int EncodeMoveReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_MoveReq);
    ENCODE_DWORD(clsessid);
    ENCODE_QWORD(role_guid);
    ENCODE_BYTE(type);
    ENCODE_WORD(dst_x);
    ENCODE_WORD(dst_y);
    ENCODE_DWORD(idx);
    ENCODE_QWORD(movetime);
    END_ENCODE();
}

static int DecodeMoveReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_MoveReq);
    DECODE_DWORD(clsessid);
    DECODE_QWORD(role_guid);
    DECODE_BYTE(type);
    DECODE_WORD(dst_x);
    DECODE_WORD(dst_y);
    DECODE_DWORD(idx);
    DECODE_QWORD(movetime);
    END_DECODE();
}

static int EncodeMoveAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_MoveAck);
    ENCODE_DWORD(clsessid);
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
    BEGIN_DECODE_EX(ProtoGS_MoveAck);
    DECODE_DWORD(clsessid);
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
    BEGIN_ENCODE_EX(ProtoGS_TurnReq);
    ENCODE_QWORD(role_guid);
    ENCODE_BYTE(dir);
    END_ENCODE();
}

static int DecodeTurnReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TurnReq);
    DECODE_QWORD(role_guid);
    DECODE_BYTE(dir);
    END_DECODE();
}

static int EncodeTurnNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_GS(ProtoGS_TurnNtf);
    ENCODE_QWORD(guid);
    ENCODE_BYTE(dir);
    END_ENCODE();
}

static int DecodeTurnNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_GS(ProtoGS_TurnNtf);
    DECODE_QWORD(guid);
    DECODE_BYTE(dir);
    END_DECODE();
}

static int EncodeSpellTarget(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_SpellTarget);
    ENCODE_QWORD(role_guid);
    ENCODE_WORD(id);
    ENCODE_QWORD(target);
    ENCODE_WORD(idx);
    END_ENCODE();
}

static int DecodeSpellTarget(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_SpellTarget);
    DECODE_QWORD(role_guid);
    DECODE_WORD(id);
    DECODE_QWORD(target);
    DECODE_WORD(idx);
    END_DECODE();
}

static int EncodeSpellGrid(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_SpellGrid);
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
    BEGIN_DECODE_EX(ProtoGS_SpellGrid);
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
    BEGIN_ENCODE_EX(ProtoGS_SpellAck);
    ENCODE_DWORD(sessionid);
    ENCODE_QWORD(role_guid);
    ENCODE_WORD(id);
    ENCODE_INT(ecode);
    ENCODE_STRING(detail);
    ENCODE_WORD(idx);
    END_ENCODE();
}

static int DecodeSpellAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_SpellAck);
    DECODE_DWORD(sessionid);
    DECODE_QWORD(role_guid);
    DECODE_WORD(id);
    DECODE_INT(ecode);
    DECODE_STRING(detail);
    DECODE_WORD(idx);
    END_DECODE();
}

static int EncodeSkillSwitch(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_SkillSwitch);
    ENCODE_DWORD(token);
    ENCODE_DWORD(clientSessionID);
    ENCODE_WORD(id);
    ENCODE_BYTE(active);
    END_ENCODE();
}

static int DecodeSkillSwitch(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_SkillSwitch);
    DECODE_DWORD(token);
    DECODE_DWORD(clientSessionID);
    DECODE_WORD(id);
    DECODE_BYTE(active);
    END_DECODE();
}

static int EncodeSkillSwitchAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_SkillSwitchAck);
    ENCODE_DWORD(token);
    ENCODE_DWORD(clientSessionID);
    ENCODE_WORD(id);
    ENCODE_BYTE(active);
    END_ENCODE();
}

static int DecodeSkillSwitchAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_SkillSwitchAck);
    DECODE_DWORD(token);
    DECODE_DWORD(clientSessionID);
    DECODE_WORD(id);
    DECODE_BYTE(active);
    END_DECODE();
}

static int EncodeCreatePlayerReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_CreatePlayerReq);
    ENCODE_DWORD(token);
    ENCODE_DWORD(clientSessionID);
    ENCODE_QWORD(playerid);
    ENCODE_QWORD(role_id);
    ENCODE_WORD(mapid);
    if (EnCodeROLE_BRIEF_INFO(&pstIn->roleBriefInfo, poNetData) == -1) return -1;
    END_ENCODE();
}

static int DecodeCreatePlayerReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_CreatePlayerReq);
    DECODE_DWORD(token);
    DECODE_DWORD(clientSessionID);
    DECODE_QWORD(playerid);
    DECODE_QWORD(role_id);
    DECODE_WORD(mapid);
    if (DeCodeROLE_BRIEF_INFO(&pstOut->roleBriefInfo, poNetData) == -1) return -1;
    END_DECODE();
}

static int EncodeKickRoleNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_KickRoleNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_QWORD(roleguid);
    ENCODE_INT(errcode);
    ENCODE_STRING(errmsg);
    END_ENCODE();
}

static int DecodeKickRoleNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_KickRoleNtf);
    DECODE_DWORD(sessionid);
    DECODE_QWORD(roleguid);
    DECODE_INT(errcode);
    DECODE_STRING(errmsg);
    END_DECODE();
}

static int EncodeSaveKey(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_SaveKeyNtf);
    ENCODE_STRING(key);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DecodeSaveKey(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_SaveKeyNtf);
    DECODE_STRING(key);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeItemPickUp(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_ItemPickUp);
    ENCODE_DWORD(sessid);
    ENCODE_DWORD(token);
    END_ENCODE();
}
static int DecodeItemPickUp(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_ItemPickUp);
    DECODE_DWORD(sessid);
    DECODE_DWORD(token);
    END_DECODE();
}
static int EncodeItemMove(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_ItemMove);
    ENCODE_QWORD(item_guid);
    ENCODE_WORD(dest_site);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DecodeItemMove(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_ItemMove);
    DECODE_QWORD(item_guid);
    DECODE_WORD(dest_site);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeItemSplit(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_ItemSplit);
    ENCODE_QWORD(item_guid);
    ENCODE_WORD(item_amount);
    ENCODE_WORD(dest_site);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DecodeItemSplit(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_ItemSplit);
    DECODE_QWORD(item_guid);
    DECODE_WORD(item_amount);
    DECODE_WORD(dest_site);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeRunServScriptReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_GS(ProtoGS_RunServScriptReq);
    ENCODE_DWORD(form_count);
    ENCODE_BLOB(script_name, 256);
    ENCODE_BLOB(function_name, 256);
    ENCODE_WORD(num);

    for (uint16_t i = 0; i < pstIn->num; ++i)
        if (EnCodePARAM_INFO2(pstIn->info + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeRunServScriptReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_GS(ProtoGS_RunServScriptReq);
    DECODE_DWORD(form_count);
    DECODE_BLOB(script_name, 256);
    DECODE_BLOB(function_name, 256);
    DECODE_WORD(num);

    for (uint16_t i = 0; i < pstOut->num; ++i)
        if (DeCodePARAM_INFO2(pstOut->info + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int EncodeRunServScriptAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_GS(ProtoGS_RunServScriptAck);
    ENCODE_STRING(script_name);
    ENCODE_STRING(result);
    END_ENCODE();
}

static int DecodeRunServScriptAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_GS(ProtoGS_RunServScriptAck);
    DECODE_STRING(script_name);
    DECODE_STRING(result);
    END_DECODE();
}

static int EncodeRelationChatReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_RelationChatReq);
    ENCODE_DWORD(token);
    ENCODE_BYTE(type);
    ENCODE_STRING(message);
    END_ENCODE();
}

static int DecodeRelationChatReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_RelationChatReq);
    DECODE_DWORD(token);
    DECODE_BYTE(type);
    DECODE_STRING(message);
    END_DECODE();
}

static int EncodeRelationChatAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_RelationChatAck);
    ENCODE_DWORD(sessionid);
    ENCODE_BYTE(type);
    if (EnCodeCHAT_MSG(&pstIn->chat_message, poNetData) == -1)
        return -1;
    ENCODE_STRING(font_color);
    ENCODE_STRING(background_color);
    ENCODE_BYTE(scroll_times);
    END_ENCODE();
}

static int DecodeRelationChatAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_RelationChatAck);
    DECODE_DWORD(sessionid);
    DECODE_BYTE(type);

    if (DeCodeCHAT_MSG(&pstOut->chat_message, poNetData) == -1)
        return -1;

    DECODE_STRING(font_color);
    DECODE_STRING(background_color);
    DECODE_BYTE(scroll_times);

    END_DECODE();
}

static int EncodeRelationChatNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_RelationChatNtf);
    if (EncodeRELATION_CHAT_NTF(&pstIn->info, poNetData) == -1)
        return -1;
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodeRelationChatNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_RelationChatNtf);
    if (DecodeRELATION_CHAT_NTF(&pstOut->info, poNetData) == -1)
        return -1;
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodePrivateChatNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_PrivateChatNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_DWORD(token);
    ENCODE_BYTE(type);

    if (EnCodeCHAT_MSG(&pstIn->chat_message, poNetData) == -1)
        return -1;

    END_ENCODE();
}

static int DecodePrivateChatNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_PrivateChatNtf);
    DECODE_DWORD(sessionid);
    DECODE_DWORD(token);
    DECODE_BYTE(type);

    if (DeCodeCHAT_MSG(&pstOut->chat_message, poNetData) == -1)
        return -1;

    END_DECODE();
}

static int EncodeSpeakerMsgReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_SpeakerMsgReq);
    ENCODE_DWORD(token);
    ENCODE_STRING(msg);
    END_ENCODE();
}

static int DecodeSpeakerMsgReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_SpeakerMsgReq);
    DECODE_DWORD(token);
    DECODE_STRING(msg);
    END_DECODE();
}

static int EncodeSpeakerMsgNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_SpeakerMsgNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_STRING(sender);
    ENCODE_STRING(msg);
    END_ENCODE();
}

static int DecodeSpeakerMsgNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_SpeakerMsgNtf);
    DECODE_DWORD(sessionid);
    DECODE_STRING(sender);
    DECODE_STRING(msg);
    END_DECODE();
}

static int EncodeTradeMallListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TradeMallListReq);
    ENCODE_DWORD(sessionid);
    ENCODE_DWORD(token);
    ENCODE_BYTE(page_id);
    END_ENCODE();
}

static int DecodeTradeMallListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TradeMallListReq);
    DECODE_DWORD(sessionid);
    DECODE_DWORD(token);
    DECODE_BYTE(page_id);
    END_DECODE();
}

static int EncodeTradeMallListAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TradeMallListAck);
    ENCODE_DWORD(sessionid);
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
    BEGIN_DECODE_EX(ProtoGS_TradeMallListAck);
    DECODE_DWORD(sessionid);
    DECODE_BYTE(page_id);
    DECODE_BYTE(item_count);

    int maxCount = std::min<int>((int)pstOut->item_count, (int)_countof(pstOut->item_list));
    for (int i = 0; i < pstOut->item_count; ++i) {
        if (-1 == DeCodeMALL_ITEM_INFO(&pstOut->item_list[i], poNetData))
            return -1;
    }

    END_DECODE();
}

static int EncodeTradeMallBuy(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TradeMallBuy);
    ENCODE_DWORD(sessionid);
    ENCODE_DWORD(token);
    ENCODE_DWORD(item_index);
    ENCODE_WORD(item_amount);
    END_ENCODE();
}

static int DecodeTradeMallBuy(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TradeMallBuy);
    DECODE_DWORD(sessionid);
    DECODE_DWORD(token);
    DECODE_DWORD(item_index);
    DECODE_WORD(item_amount);
    END_DECODE();
}

static int EncodeNpcSelect(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_NpcSelect);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    ENCODE_QWORD(npc_guid);
    END_ENCODE();
}

static int DecodeNpcSelect(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_NpcSelect);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    DECODE_QWORD(npc_guid);
    END_DECODE();
}

static int EncodeNpcTalkReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_NpcTalkReq);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    ENCODE_QWORD(npc_guid);
    ENCODE_STRING(func);
    END_ENCODE();
}

static int DecodeNpcTalkReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_NpcTalkReq);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    DECODE_QWORD(npc_guid);
    DECODE_STRING(func);
    END_DECODE();
}

static int EncodeTradeNpcBuy(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TradeNpcBuy);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    ENCODE_WORD(shop_id);
    ENCODE_WORD(item_index);
    ENCODE_WORD(item_amount);
    ENCODE_BYTE(is_bind);
    END_ENCODE();
}

static int DecodeTradeNpcBuy(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TradeNpcBuy);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    DECODE_WORD(shop_id);
    DECODE_WORD(item_index);
    DECODE_WORD(item_amount);
    DECODE_BYTE(is_bind);
    END_DECODE();
}

static int EncodeAtkModeReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_AtkModeReq);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    ENCODE_BYTE(atk_mode);
    END_ENCODE();
}

static int DecodeAtkModeReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_AtkModeReq);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    DECODE_BYTE(atk_mode);
    END_DECODE();
}

static int EncodeQuestQueryCanAccept(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_QuestQueryCanAccept);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DecodeQuestQueryCanAccept(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_QuestQueryCanAccept);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeQuestQueryCanAcceptNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_QuestQueryCanAcceptNtf);
    ENCODE_DWORD(sessionid);
    ENCODE_WORD(num);
    for (uint16_t i = 0; i < pstIn->num; ++i) {
        ENCODE_WORD(quests[i]);
    }
    END_ENCODE();
}

static int DecodeQuestQueryCanAcceptNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_QuestQueryCanAcceptNtf);
    DECODE_DWORD(sessionid);
    DECODE_WORD(num);
    for (uint16_t i = 0; i < pstOut->num; ++i) {
        DECODE_WORD(quests[i]);
    }
    END_DECODE();
}

static int EncodeQuestAccept(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_QuestAccept);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    ENCODE_WORD(quest_id);
    END_ENCODE();
}

static int DecodeQuestAccept(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_QuestAccept);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    DECODE_WORD(quest_id);
    END_DECODE();
}

static int EncodeQuestAddNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_QuestAddNtf);
    ENCODE_DWORD(sessionid);
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
    BEGIN_DECODE_EX(ProtoGS_QuestAddNtf);
    DECODE_DWORD(sessionid);
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

static int EncodeQuestDrop(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_QuestDrop);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    ENCODE_WORD(quest_id);
    END_ENCODE();
}

static int DecodeQuestDrop(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_QuestDrop);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    DECODE_WORD(quest_id);
    END_DECODE();
}

static int EncodeQuestAccomplish(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_QuestAccomplish);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    ENCODE_WORD(quest_id);
    ENCODE_WORD(select_index);
    END_ENCODE();
}

static int DecodeQuestAccomplish(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_QuestAccomplish);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    DECODE_WORD(quest_id);
    DECODE_WORD(select_index);
    END_DECODE();
}

static int EncodeTeamoperation(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_Teamoperation);
    ENCODE_DWORD(token);
    ENCODE_BYTE(operation);
    ENCODE_STRING(content);
    END_ENCODE();
}

static int DecodeTeamoperation(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_Teamoperation);
    DECODE_DWORD(token);
    DECODE_BYTE(operation);
    DECODE_STRING(content);
    END_DECODE();
}

static int EnCodePlayerSwitchReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_PlayerSwitchReq);
    ENCODE_BYTE(id);
    ENCODE_BYTE(value);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DeCodePlayerSwitchReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_PlayerSwitchReq);
    DECODE_BYTE(id);
    DECODE_BYTE(value);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeTeamInvite(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TeamInvite);
    ENCODE_STRING(invitee_name);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DecodeTeamInvite(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TeamInvite);
    DECODE_STRING(invitee_name);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeTeamInviteRsp(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TeamInviteRsp);
    ENCODE_STRING(inviter_name);
    ENCODE_BYTE(accepted);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DecodeTeamInviteRsp(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TeamInviteRsp);
    DECODE_STRING(inviter_name);
    DECODE_BYTE(accepted);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeTeamLeaveEx(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TeamLeaveEx);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DecodeTeamLeaveEx(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TeamLeaveEx);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeTeamKickEx(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TeamKickEx);
    ENCODE_STRING(name);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DecodeTeamKickEx(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TeamKickEx);
    DECODE_STRING(name);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeGetAroundTeamReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_GetAroundTeamReq);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DecodeGetAroundTeamReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_GetAroundTeamReq);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeTeamTeamJoin(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TeamJoin);
    ENCODE_STRING(team_member);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DecodeTeamTeamJoin(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TeamJoin);
    DECODE_STRING(team_member);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeTeamTeamJoinResponse(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TeamJoinResponse);
    ENCODE_STRING(joiner);
    ENCODE_BYTE(accepted);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DecodeTeamTeamJoinResponse(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TeamJoinResponse);
    DECODE_STRING(joiner);
    DECODE_BYTE(accepted);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeGetFamilyInfoReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_GetFamilyInfoReq);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    ENCODE_DWORD(reqType);
    ENCODE_DWORD(start_index);
    ENCODE_DWORD(req_count);
    ENCODE_DWORD(req_group);
    ENCODE_STRING(info);
    END_ENCODE();
}

static int DecodeGetFamilyInfoReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_GetFamilyInfoReq);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    DECODE_DWORD(reqType);
    DECODE_DWORD(start_index);
    DECODE_DWORD(req_count);
    DECODE_DWORD(req_group);
    DECODE_STRING(info);
    END_DECODE();
}

static int EncodePlayerQuery(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_PlayerQuery);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    ENCODE_STRING(player_name);
    END_ENCODE();
}

static int DecodePlayerQuery(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_PlayerQuery);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    DECODE_STRING(player_name);
    END_DECODE();
}

static int EncodeQuickBarSet(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_QuickBarSet);
    ENCODE_DWORD(sessionid);
    ENCODE_BYTE(type);
    ENCODE_BYTE(slot);
    ENCODE_WORD(id);
    ENCODE_QWORD(guid);
    ENCODE_QWORD(role_id);
    END_ENCODE();
}

static int DecodeQuickBarSet(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_QuickBarSet);
    DECODE_DWORD(sessionid);
    DECODE_BYTE(type);
    DECODE_BYTE(slot);
    DECODE_WORD(id);
    DECODE_QWORD(guid);
    DECODE_QWORD(role_id);
    END_DECODE();
}

static int EnCodeGoldTake(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProttoGS_GoldTake);
    ENCODE_INT64(gold);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DeCodeGoldTake(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_GoldDeposit);
    DECODE_INT64(gold);
    DECODE_QWORD(role_id);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EnCodeGoldDeposit(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProttoGS_GoldTake);
    ENCODE_INT64(gold);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DeCodeGoldDeposit(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProttoGS_GoldTake);
    DECODE_INT64(gold);
    DECODE_QWORD(role_id);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EnCodeGMCommandReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_GMCommandReq);
    ENCODE_INT(sn);
    ENCODE_STRING(cmd);
    ENCODE_STRING(param);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(sessionid);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DeCodeGMCommandReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_GMCommandReq);
    DECODE_INT(sn);
    DECODE_STRING(cmd);
    DECODE_STRING(param);
    DECODE_QWORD(role_id);
    DECODE_DWORD(sessionid);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeRoleCustVarReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_RoleCustVarReq);
    ENCODE_QWORD(role_guid);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodeRoleCustVarReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_RoleCustVarReq);
    DECODE_QWORD(role_guid);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodeRecordsMineReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_RecordsMineReq);
    ENCODE_QWORD(role_id);
    ENCODE_WORD(type);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodeRecordsMineReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_RecordsMineReq);
    DECODE_QWORD(role_id);
    DECODE_WORD(type);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodeDelegateMineReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_DelegateMineReq);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodeDelegateMineReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_DelegateMineReq);
    DECODE_QWORD(role_id);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodeDelegateListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_DelegateListReq);
    ENCODE_DWORD(start);
    ENCODE_DWORD(count);
    ENCODE_WORD(type);
    ENCODE_WORD(subtype);
    ENCODE_STRING(item_name);
    ENCODE_BYTE(is_reverse);
    ENCODE_BYTE(delegatetype);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodeDelegateListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_DelegateListReq);
    DECODE_DWORD(start);
    DECODE_DWORD(count);
    DECODE_WORD(type);
    DECODE_WORD(subtype);
    DECODE_STRING(item_name);
    DECODE_BYTE(is_reverse);
    DECODE_BYTE(delegatetype);
    DECODE_QWORD(role_id);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodeDelegateCancelReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_DelegateCancelReq);
    ENCODE_QWORD(trade_id);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodeDelegateCancelReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_DelegateCancelReq);
    DECODE_QWORD(trade_id);
    DECODE_QWORD(role_id);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodeDelegateSellCmd(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_DelegateSellCmd);
    ENCODE_QWORD(item_guid);
    ENCODE_DWORD(item_value);
    ENCODE_DWORD(item_unit);
    ENCODE_BYTE(value_type);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodeDelegateSellCmd(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_DelegateSellCmd);
    DECODE_QWORD(item_guid);
    DECODE_DWORD(item_value);
    DECODE_DWORD(item_unit);
    DECODE_BYTE(value_type);
    DECODE_QWORD(role_id);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodeDelegateBuyCmd(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_DelegateBuyCmd);
    ENCODE_WORD(item_id);
    ENCODE_DWORD(item_count);
    ENCODE_DWORD(item_value);
    ENCODE_DWORD(item_unit);
    ENCODE_BYTE(value_type);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodeDelegateBuyCmd(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_DelegateBuyCmd);
    DECODE_WORD(item_id);
    DECODE_DWORD(item_count);
    DECODE_DWORD(item_value);
    DECODE_DWORD(item_unit);
    DECODE_BYTE(value_type);
    DECODE_QWORD(role_id);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodeMarketSellCmd(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_MarketSellCmd);
    ENCODE_QWORD(trade_id);
    ENCODE_QWORD(item_guid);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodeMarketSellCmd(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_MarketSellCmd);
    DECODE_QWORD(trade_id);
    DECODE_QWORD(item_guid);
    DECODE_QWORD(role_id);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodeMarketBuyCmd(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_MarketBuyCmd);
    ENCODE_QWORD(trade_id);
    ENCODE_DWORD(count);
    ENCODE_QWORD(role_id);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodeMarketBuyCmd(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_MarketBuyCmd);
    DECODE_QWORD(trade_id);
    DECODE_DWORD(count);
    DECODE_QWORD(role_id);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EnCodeTopListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TopListReq);
    ENCODE_BYTE(type);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DeCodeTopListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TopListReq);
    DECODE_BYTE(type);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodeTopListAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_TopListAck);
    ENCODE_BYTE(type);
    ENCODE_DWORD(time);
    ENCODE_BYTE(num);
    ENCODE_DWORD(sessionid);
    for (uint8_t i = 0; i < pstIn->num; i++)
        if (-1 == EnCodeTOPLIST_INFO(pstIn->info + i, poNetData))
            return -1;
    END_ENCODE();
}

static int DecodeTopListAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_TopListAck);
    DECODE_BYTE(type);
    DECODE_DWORD(time);
    DECODE_BYTE(num);
    DECODE_DWORD(sessionid);
    for (uint8_t i = 0; i < pstOut->num; i++)
        if (-1 == DeCodeTOPLIST_INFO(pstOut->info + i, poNetData))
            return -1;
    END_DECODE();
}
static int EncodeFamilyJoinReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_FamilyJoinReq);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    ENCODE_QWORD(guid);
    END_ENCODE();
}

static int DecodeFamilyJoinReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_FamilyJoinReq);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    DECODE_QWORD(guid);
    END_DECODE();
}

static int EncodeCancelFamilyJoinReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_CancelFamilyJoinReq);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    ENCODE_QWORD(guid);
    END_ENCODE();
}

static int DecodeCancelFamilyJoinReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_CancelFamilyJoinReq);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    DECODE_QWORD(guid);
    END_DECODE();
}

static int EncodeFamilyJoinAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_FamilyJoinAck);
    ENCODE_QWORD(leader_guid);
    ENCODE_QWORD(player_guid);
    ENCODE_BYTE(is_allow);
    END_ENCODE();
}

static int DecodeFamilyJoinAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_FamilyJoinAck);
    DECODE_QWORD(leader_guid);
    DECODE_QWORD(player_guid);
    DECODE_BYTE(is_allow);
    END_DECODE();
}

static int EncodeFamilyTitleAwardReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_FamilyTitleAwardReq);
    ENCODE_QWORD(leader_guid);
    ENCODE_QWORD(player_guid);
    ENCODE_BYTE(title_id);
    END_ENCODE();
}

static int DecodeFamilyTitleAwardReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_FamilyTitleAwardReq);
    DECODE_QWORD(leader_guid);
    DECODE_QWORD(player_guid);
    DECODE_BYTE(title_id);
    END_DECODE();
}

static int EncodeFamilyExpellReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_FamilyExpellReq);
    ENCODE_QWORD(kicker_guid);
    ENCODE_QWORD(player_guid);
    END_ENCODE();
}

static int DecodeFamilyExpellReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_FamilyExpellReq);
    DECODE_QWORD(kicker_guid);
    DECODE_QWORD(player_guid);
    END_DECODE();
}
static int EnCodeMailListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_MaillistReq);
    ENCODE_BYTE(type);
    ENCODE_QWORD(mail_id);
    ENCODE_QWORD(role_id);
    END_ENCODE();
}

static int DeCodeMailListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_MaillistReq);
    DECODE_BYTE(type);
    DECODE_QWORD(mail_id);
    DECODE_QWORD(role_id);
    END_DECODE();
}
static int EnCodeMailOpenReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_MailOpenReq);
    ENCODE_QWORD(id);
    ENCODE_QWORD(role_id);
    END_ENCODE();
}

static int DeCodeMailOpenReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_MailOpenReq);
    DECODE_QWORD(id);
    DECODE_QWORD(role_id);
    END_DECODE();
}
static int EnCodeMailAttachmentGetQeq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_MailAttachmentGetReq);
    ENCODE_QWORD(mail_id);
    ENCODE_BYTE(index);
    ENCODE_QWORD(role_id);
    END_ENCODE();
}

static int DeCodeMailAttachmentGetQeq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_MailAttachmentGetReq);
    DECODE_QWORD(mail_id);
    DECODE_BYTE(index);
    DECODE_QWORD(role_id);
    END_DECODE();
}
static int EnCodeMailDelReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_MailDeleteReq);
    ENCODE_QWORD(id);
    ENCODE_QWORD(role_id);
    END_ENCODE();
}

static int DeCodeMailDelReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_MailDeleteReq);
    DECODE_QWORD(id);
    DECODE_QWORD(role_id);
    END_DECODE();
}

static int EncodeFamilyNoticeEditReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_FamilyNoticeEditReq);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    ENCODE_DWORD(notice_len);
    ENCODE_STRING(notice);
    END_ENCODE();
}

static int DecodeFamilyNoticeEditReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_FamilyNoticeEditReq);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    DECODE_DWORD(notice_len);
    DECODE_STRING(notice);
    END_DECODE();
}

static int EncodeFriendAddReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_FriendAddReq);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    ENCODE_STRING(player_name);
    END_ENCODE();
}

static int DecodeFriendAddReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_FriendAddReq);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    DECODE_STRING(player_name);
    END_DECODE();
}

static int EncodeFamilyLeaveOrLastMsgReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_FamilyLeaveOrLastMsgReq);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    ENCODE_STRING(byebye);
    END_ENCODE();
}

static int DecodeFamilyLeaveOrLastMsgReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_FamilyLeaveOrLastMsgReq);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    DECODE_STRING(byebye);
    END_DECODE();
}

static int EncodeFamilyDestroyReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_FamilyDestroyReq);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DecodeFamilyDestroyReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_FamilyDestroyReq);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeQueryEx(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_QueryEx);
    ENCODE_QWORD(role_id);
    ENCODE_QWORD(self_role_id);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DecodeQueryEx(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_QueryEx);
    DECODE_QWORD(role_id);
    DECODE_QWORD(self_role_id);
    DECODE_DWORD(token);
    END_DECODE();
}

static int EncodeUpdateOnlineState(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_UpdateOnlineState);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    ENCODE_BYTE(state);
    END_ENCODE();
}

static int DecodeUpdateOnlineState(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_UpdateOnlineState);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    DECODE_BYTE(state);
    END_DECODE();
}

static int EncodeSyncSessionID(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_SyncSessionID);
    ENCODE_QWORD(role_guid);
    ENCODE_DWORD(token);
    ENCODE_DWORD(cl2gs_sessid);
    END_ENCODE();
}

static int DecodeSyncSessionID(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_SyncSessionID);
    DECODE_QWORD(role_guid);
    DECODE_DWORD(token);
    DECODE_DWORD(cl2gs_sessid);
    END_DECODE();
}

static int EncodeJumpMapReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_JumpMapReq);
    ENCODE_QWORD(roleid);
    ENCODE_DWORD(token);
    ENCODE_WORD(dst_x);
    ENCODE_WORD(dst_y);
    ENCODE_BYTE(type);
    END_ENCODE();
}

static int DecodeJumpMapReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_JumpMapReq);
    DECODE_QWORD(roleid);
    DECODE_DWORD(token);
    DECODE_WORD(dst_x);
    DECODE_WORD(dst_y);
    DECODE_BYTE(type);
    END_DECODE();
}

static int EncodeGetNpcPosReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_GetNpcPosReq);
    ENCODE_QWORD(roleid);
    ENCODE_STRING(name);
    END_ENCODE();
}

static int DecodeGetNpcPosReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_GetNpcPosReq);
    DECODE_QWORD(roleid);
    DECODE_STRING(name);
    END_DECODE();
}

static int EncodeGetNpcPosAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_GetNpcPosAck);
    ENCODE_WORD(posx);
    ENCODE_WORD(posy);
    ENCODE_BYTE(result);
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodeGetNpcPosAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_GetNpcPosAck);
    DECODE_WORD(posx);
    DECODE_WORD(posy);
    DECODE_BYTE(result);
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodeStartDigReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_StartDigReq);
    ENCODE_QWORD(role_guid);
    ENCODE_QWORD(treasure_guid);
    END_ENCODE();
}

static int DecodeStartDigReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_StartDigReq);
    DECODE_QWORD(role_guid);
    DECODE_QWORD(treasure_guid);
    END_DECODE();
}

static int EncodeRangePickup(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_RangePickup);
    ENCODE_QWORD(role_guid);
    ENCODE_BYTE(posnum);
    ENCODE_CHECK_UPBOUND(posnum, pos);
    for (uint8_t i = 0; i < pstIn->posnum; ++i)
        if (EncodePoint(pstIn->pos + i, poNetData) == -1)
            return -1;
    END_ENCODE();
}

static int DecodeRangePickup(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_RangePickup);
    DECODE_QWORD(role_guid);
    DECODE_BYTE(posnum);
    DECODE_CHECK_UPBOUND(posnum, pos);
    for (uint8_t i = 0; i < pstOut->posnum; ++i)
        if (DecodePoint(pstOut->pos + i, poNetData) == -1)
            return -1;
    END_DECODE();
}

static int EncodeSyncClientBaseSetting(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_SyncClientBaseSetting);
    ENCODE_QWORD(role_guid);
    ENCODE_WORD(type);
    ENCODE_INT(value);
    END_ENCODE();
}

static int DecodeSyncClientBaseSetting(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_SyncClientBaseSetting);
    DECODE_QWORD(role_guid);
    DECODE_WORD(type);
    DECODE_INT(value);
    END_DECODE();
}

static int EncodeVerifyBuyItemInfoReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_VerifyBuyItemInfoReq);
    ENCODE_QWORD(role_guid);
    ENCODE_DWORD(item_id);
    ENCODE_BYTE(item_count);
    ENCODE_DWORD(item_price);
    END_ENCODE();
}

static int DecodeVerifyBuyItemInfoReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_VerifyBuyItemInfoReq);
    DECODE_QWORD(role_guid);
    DECODE_DWORD(item_id);
    DECODE_BYTE(item_count);
    DECODE_DWORD(item_price);
    END_DECODE();
}

static int EncodeItemRefreshReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_ItemRefreshReq);
    ENCODE_QWORD(role_guid);
    ENCODE_DWORD(token);
    END_ENCODE();
}

static int DecodeItemRefreshReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_ItemRefreshReq);
    DECODE_QWORD(role_guid);
    DECODE_DWORD(token);
    END_DECODE();
}
static int EncodeItemTip(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_ItemTip);
    ENCODE_QWORD(guid);
    ENCODE_QWORD(owner_guid);
    ENCODE_QWORD(item_guid);
    END_ENCODE();
}

static int DecodeItemTip(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_ItemTip);
    DECODE_QWORD(guid);
    DECODE_QWORD(owner_guid);
    DECODE_QWORD(item_guid);
    END_DECODE();
}

static int EncodeItemTipNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_ItemTipNtf);
    ENCODE_QWORD(guid);
    ENCODE_DWORD(sessionid);
    if (-1 == EnCodeITEM_INFO(&pstIn->infos, poNetData))
        return -1;
    END_ENCODE();
}

static int DecodeItemTipNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_ItemTipNtf);
    DECODE_QWORD(guid);
    DECODE_DWORD(sessionid);
    if (-1 == DeCodeITEM_INFO(&pstOut->infos, poNetData))
        return -1;
    END_DECODE();
}

static int EncodeCustMsgNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_CustMsgNtf);
    if (-1 == EncodeCUST_MSG_NTF(&pstIn->info, poNetData))
        return -1;
    ENCODE_DWORD(sessionid);
    END_ENCODE();
}

static int DecodeCustMsgNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_CustMsgNtf);
    if (-1 == DecodeCUST_MSG_NTF(&pstOut->info, poNetData))
        return -1;
    DECODE_DWORD(sessionid);
    END_DECODE();
}

static int EncodeSetAutoModeAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoGS_SetAutoModeAck);
    ENCODE_QWORD(role_guid);
    ENCODE_BYTE(enable);
    END_ENCODE();
}

static int DecodeSetAutoModeAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoGS_SetAutoModeAck);
    DECODE_QWORD(role_guid);
    DECODE_BYTE(enable);
    END_DECODE();
}

ProtoGS::ProtoGS()
{
    SET_ENCODER_DECODER(PROTO_GS_TEAM_JOIN, EncodeTeamTeamJoin, DecodeTeamTeamJoin);
    SET_ENCODER_DECODER(PROTO_GS_TEAM_JOIN_RSP, EncodeTeamTeamJoinResponse, DecodeTeamTeamJoinResponse);
    SET_ENCODER_DECODER(PROTO_GS_GET_ARROUND_TEAM_REQ, EncodeGetAroundTeamReq, DecodeGetAroundTeamReq);
    SET_ENCODER_DECODER(PROTO_GS_TEAM_KICK_REQ, EncodeTeamKickEx, DecodeTeamKickEx);
    SET_ENCODER_DECODER(PROTO_GS_TEAM_LEAVE_REQ, EncodeTeamLeaveEx, DecodeTeamLeaveEx);
    SET_ENCODER_DECODER(PROTO_GS_TEAM_INVITE, EncodeTeamInvite, DecodeTeamInvite);
    SET_ENCODER_DECODER(PROTO_GS_TEAM_INVITE_RSP, EncodeTeamInviteRsp, DecodeTeamInviteRsp);
    SET_ENCODER_DECODER(PROTO_GS_PLAYER_SWITCH_REQ, EnCodePlayerSwitchReq, DeCodePlayerSwitchReq);
    SET_ENCODER_DECODER(PROTO_SESSION_LS2GS_NTF, EnCodeSessionIDNtf, DeCodeSessionIDNtf);
    SET_ENCODER_DECODER(PROTO_SESSION_CS2GS_NTF, EnCodeSessionIDNtf, DeCodeSessionIDNtf);
    SET_ENCODER_DECODER(PROTO_SESSION_MS2GS_NTF, EnCodeSessionIDNtf, DeCodeSessionIDNtf);
    SET_ENCODER_DECODER(PROTO_GS_RELIVE_REQ, EnCodePlayerReliveReq, DeCodePlayerReliveReq);
    SET_ENCODER_DECODER(PROTO_GS_RELIVE_ACK, EnCodePlayerReliveAck, EnCodePlayerReliveAck);
    SET_ENCODER_DECODER(PROTO_GS_ITEM_MOVE, EncodeItemMove, DecodeItemMove);
    SET_ENCODER_DECODER(PROTO_GS_ITEM_SPLIT, EncodeItemSplit, DecodeItemSplit);
    SET_ENCODER_DECODER(PROTO_GS_ITEM_ARRANGE, EncodeItemArrange, DecodeItemArrange);
    SET_ENCODER_DECODER(PROTO_GS_ITEM_PICK_UP, EncodeItemPickUp, DecodeItemPickUp);
    SET_ENCODER_DECODER(PROTO_GS_SAVE_KEY_NTF, EncodeSaveKey, DecodeSaveKey);
    SET_ENCODER_DECODER(PROTO_GS_ITEM_APPLY, EncodeItemApply, DecodeItemApply);
    SET_ENCODER_DECODER(PROTO_GS_ITEM_DROP, EncodeItemDrop, DecodeItemDrop);
    SET_ENCODER_DECODER(PROTO_GS_HEART_BEAT_REQ, EncodeHeartBeatReq, DecodeHeartBeatReq);
    SET_ENCODER_DECODER(PROTO_GS_HEART_BEAT_ACK, EncodeHeartBeatAck, DecodeHeartBeatAck);
    SET_ENCODER_DECODER(PROTO_GS_CONFIG_REQ, EnCodeConfigReq, DeCodeConfigReq);
    SET_ENCODER_DECODER(PROTO_GS_CONFIG_ACK, EnCodeConfigAck, DeCodeConfigAck);
    SET_ENCODER_DECODER(PROTO_GS_LOGIN_REQ, EncodeLoginReq, DecodeLoginReq);
    SET_ENCODER_DECODER(PROTO_GS_LOGIN_ACK, EncodeLoginAck, DecodeLoginAck);
    SET_ENCODER_DECODER(PROTO_GS_THIRD_LOGIN_REQ, EncodeThirdLoginReq, DecodeThirdLoginReq);
    SET_ENCODER_DECODER(PROTO_GS_LOGOUT_REQ, EncodeLogoutReq, DecodeLogoutReq);
    SET_ENCODER_DECODER(PROTO_GS_RELOGIN_REQ, EncodeReloginReq, DecodeReloginReq);
    SET_ENCODER_DECODER(PROTO_GS_ENTER_MAP_ACK, EncodeEnterMapAck, DecodeEnterMapAck);
    SET_ENCODER_DECODER(PROTO_GS_GET_ROLE_LIST_REQ, EncodeGetRoleListReq, DecodeGetRoleListReq);
    SET_ENCODER_DECODER(PROTO_GS_GET_ROLE_LIST_ACK, EncodeGetRoleListAck, DecodeGetRoleListAck);
    SET_ENCODER_DECODER(PROTO_GS_ENTER_GS_REQ, EncodeEnterGSReq, DecodeEnterGSReq);
    SET_ENCODER_DECODER(PROTO_GS_ENTER_GS_NTF, EncodeEnterGSNtf, DecodeEnterGSNtf);
    SET_ENCODER_DECODER(PROTO_GS_CREATE_ROLE_REQ, EncodeCreateRoleReq, DecodeCreateRoleReq);
    SET_ENCODER_DECODER(PROTO_GS_CREATE_ROLE_ACK, EncodeCreateRoleAck, DecodeCreateRoleAck);
    SET_ENCODER_DECODER(PROTO_GS_DELETE_ROLE_REQ, EncodeDeleteRoleReq, DecodeDeleteRoleReq);
    SET_ENCODER_DECODER(PROTO_GS_DELETE_ROLE_ACK, EncodeDeleteRoleAck, DecodeDeleteRoleAck);
    SET_ENCODER_DECODER(PROTO_GS_RESTORE_ROLE_REQ, EncodeRestoreRoleReq, DecodeRestoreRoleReq);
    SET_ENCODER_DECODER(PROTO_GS_RESTORE_ROLE_ACK, EncodeRestoreRoleAck, DecodeRestoreRoleAck);
    SET_ENCODER_DECODER(PROTO_GS_MOVE_REQ, EncodeMoveReq, DecodeMoveReq);
    SET_ENCODER_DECODER(PROTO_GS_MOVE_ACK, EncodeMoveAck, DecodeMoveAck);
    SET_ENCODER_DECODER(PROTO_GS_TURN_REQ, EncodeTurnReq, DecodeTurnReq);
    SET_ENCODER_DECODER(PROTO_GS_TURN_NTF, EncodeTurnNtf, DecodeTurnNtf);
    SET_ENCODER_DECODER(PROTO_GS_SPELL_TARGET, EncodeSpellTarget, DecodeSpellTarget);
    SET_ENCODER_DECODER(PROTO_GS_SPELL_GRID, EncodeSpellGrid, DecodeSpellGrid);
    SET_ENCODER_DECODER(PROTO_GS_SPELL_ACK, EncodeSpellAck, DecodeSpellAck);
    SET_ENCODER_DECODER(PROTO_GS_EXIT_GS_REQ, EncodeExitReq, DecodeExitReq);
    SET_ENCODER_DECODER(PROTO_GS_EXIT_GS_ACK, EncodeExitAck, DecodeExitAck);
    SET_ENCODER_DECODER(PROTO_GS_SKILL_SWITCH, EncodeSkillSwitch, DecodeSkillSwitch);
    SET_ENCODER_DECODER(PROTO_GS_SKILL_SWITCH_ACK, EncodeSkillSwitchAck, DecodeSkillSwitchAck);
    SET_ENCODER_DECODER(PROTO_GS_CREATE_PLAYER_REQ, EncodeCreatePlayerReq, DecodeCreatePlayerReq);
    SET_ENCODER_DECODER(PROTO_GS_KICK_ROLE_NTF, EncodeKickRoleNtf, DecodeKickRoleNtf);
    SET_ENCODER_DECODER(PROTO_GS_RELOGIN_ACK, EncodeReloginAck, DecodeReloginAck);
    SET_ENCODER_DECODER(PROTO_GS_RUN_SERV_SCRIPT_REQ, EncodeRunServScriptReq, DecodeRunServScriptReq);
    SET_ENCODER_DECODER(PROTO_GS_RUN_SERV_SCRIPT_ACK, EncodeRunServScriptAck, DecodeRunServScriptAck);
    SET_ENCODER_DECODER(PROTO_GS_RELATION_CHAT_REQ, EncodeRelationChatReq, DecodeRelationChatReq);
    SET_ENCODER_DECODER(PROTO_GS_RELATION_CHAT_ACK, EncodeRelationChatAck, DecodeRelationChatAck);
    SET_ENCODER_DECODER(PROTO_GS_RELATION_CHAT_NTF, EncodeRelationChatNtf, DecodeRelationChatNtf);
    SET_ENCODER_DECODER(PROTO_GS_PRIVATE_CHAT_NTF, EncodePrivateChatNtf, DecodePrivateChatNtf);
    SET_ENCODER_DECODER(PROTO_GS_SPEAKER_MSG_REQ, EncodeSpeakerMsgReq, DecodeSpeakerMsgReq);
    SET_ENCODER_DECODER(PROTO_GS_SPEAKER_MSG_NTF, EncodeSpeakerMsgNtf, DecodeSpeakerMsgNtf);
    SET_ENCODER_DECODER(PROTO_GS_TRADE_MALL_BUY, EncodeTradeMallBuy, DecodeTradeMallBuy);
    SET_ENCODER_DECODER(PROTO_GS_TRADE_MALL_LIST_REQ, EncodeTradeMallListReq, DecodeTradeMallListReq);
    SET_ENCODER_DECODER(PROTO_GS_TRADE_MALL_LIST_ACK, EncodeTradeMallListAck, DecodeTradeMallListAck);
    SET_ENCODER_DECODER(PROTO_GS_NPC_SELECT, EncodeNpcSelect, DecodeNpcSelect);
    SET_ENCODER_DECODER(PROTO_GS_NPC_TALK_REQ, EncodeNpcTalkReq, DecodeNpcTalkReq);
    SET_ENCODER_DECODER(PROTO_GS_TRADE_NPC_BUY, EncodeTradeNpcBuy, DecodeTradeNpcBuy);
    SET_ENCODER_DECODER(PROTO_GS_ATK_MODE_REQ, EncodeAtkModeReq, DecodeAtkModeReq);
    SET_ENCODER_DECODER(PROTO_GS_QUEST_QUERY_CAN_ACCEPT, EncodeQuestQueryCanAccept, DecodeQuestQueryCanAccept);
    SET_ENCODER_DECODER(PROTO_GS_QUEST_QUERY_CAN_ACCEPT_NTF, EncodeQuestQueryCanAcceptNtf, DecodeQuestQueryCanAcceptNtf);
    SET_ENCODER_DECODER(PROTO_GS_QUEST_ACCEPT, EncodeQuestAccept, DecodeQuestAccept);
    SET_ENCODER_DECODER(PROTO_GS_QUEST_ADD_NTF, EncodeQuestAddNtf, DecodeQuestAddNtf);
    SET_ENCODER_DECODER(PROTO_GS_TEAM_OPERATION, EncodeTeamoperation, DecodeTeamoperation);
    SET_ENCODER_DECODER(PROTO_GS_QUEST_DROP, EncodeQuestDrop, DecodeQuestDrop);
    SET_ENCODER_DECODER(PROTO_GS_QUEST_ACCOMPLISH, EncodeQuestAccomplish, DecodeQuestAccomplish);
    SET_ENCODER_DECODER(PROTO_GS_GET_FAMILY_INFO_REQ, EncodeGetFamilyInfoReq, DecodeGetFamilyInfoReq);
    SET_ENCODER_DECODER(PROTO_GS_PLAYER_QUERY, EncodePlayerQuery, DecodePlayerQuery);
    SET_ENCODER_DECODER(PROTO_GS_QUICK_BAR_SET, EncodeQuickBarSet, DecodeQuickBarSet);
    SET_ENCODER_DECODER(PROTO_GS_QUICK_GOLD_TAKE, EnCodeGoldTake, DeCodeGoldTake);
    SET_ENCODER_DECODER(PROTO_GS_QUICK_GOLD_DEPOSIT, EnCodeGoldDeposit, DeCodeGoldDeposit);
    SET_ENCODER_DECODER(PROTO_GS_GM_COMMAND_REQ, EnCodeGMCommandReq, DeCodeGMCommandReq);
	SET_ENCODER_DECODER(PROTO_GS_TOPLIST_REQ, EnCodeTopListReq, DeCodeTopListReq);
    SET_ENCODER_DECODER(PROTO_GS_TOPLIST_ACK, EncodeTopListAck, DecodeTopListAck);
    SET_ENCODER_DECODER(PROTO_GS_FAMILY_JOIN_REQ, EncodeFamilyJoinReq, DecodeFamilyJoinReq);
    SET_ENCODER_DECODER(PROTO_GS_CANCEL_FAMILY_JOIN_REQ, EncodeCancelFamilyJoinReq, DecodeCancelFamilyJoinReq);
    SET_ENCODER_DECODER(PROTO_GS_FAMILY_JOIN_ACK, EncodeFamilyJoinAck, DecodeFamilyJoinAck);
    SET_ENCODER_DECODER(PROTO_GS_FAMILY_TITLE_AWARD_REQ, EncodeFamilyTitleAwardReq, DecodeFamilyTitleAwardReq);	
    SET_ENCODER_DECODER(PROTO_GS_MAIL_LIST_REQ, EnCodeMailListReq, DeCodeMailListReq);
    SET_ENCODER_DECODER(PROTO_GS_MAIL_OPEN_REQ, EnCodeMailOpenReq, DeCodeMailOpenReq);
    SET_ENCODER_DECODER(PROTO_GS_MAIL_ATTACHMENT_GET_REQ, EnCodeMailAttachmentGetQeq, DeCodeMailAttachmentGetQeq);
    SET_ENCODER_DECODER(PROTO_GS_MAIL_DEL_REQ, EnCodeMailDelReq, DeCodeMailDelReq);
    SET_ENCODER_DECODER(PROTO_GS_FRIEND_ADD_REQ, EncodeFriendAddReq, DecodeFriendAddReq);
    SET_ENCODER_DECODER(PROTO_GS_FAMILY_EXPELL_REQ, EncodeFamilyExpellReq, DecodeFamilyExpellReq);
    SET_ENCODER_DECODER(PROTO_GS_FAMILY_NOTICE_EDIT_REQ, EncodeFamilyNoticeEditReq, DecodeFamilyNoticeEditReq);
    SET_ENCODER_DECODER(PROTO_GS_FAMILY_LEAVE_OR_LAST_MSG_REQ, EncodeFamilyLeaveOrLastMsgReq, DecodeFamilyLeaveOrLastMsgReq);
    SET_ENCODER_DECODER(PROTO_GS_FAMILY_DESTROY_REQ, EncodeFamilyDestroyReq, DecodeFamilyDestroyReq);
    SET_ENCODER_DECODER(PROTO_GS_ROLE_CUST_VAR_REQ, EncodeRoleCustVarReq, DecodeRoleCustVarReq);
    SET_ENCODER_DECODER(PROTO_GS_RECORDS_MINE_REQ, EncodeRecordsMineReq, DecodeRecordsMineReq);
    SET_ENCODER_DECODER(PROTO_GS_DELEGATE_MINE_REQ, EncodeDelegateMineReq, DecodeDelegateMineReq);
    SET_ENCODER_DECODER(PROTO_GS_DELEGATE_LIST_REQ, EncodeDelegateListReq, DecodeDelegateListReq);
    SET_ENCODER_DECODER(PROTO_GS_DELEGATE_CANCEL_REQ, EncodeDelegateCancelReq, DecodeDelegateCancelReq);
    SET_ENCODER_DECODER(PROTO_GS_DELEGATE_SELL_CMD, EncodeDelegateSellCmd, DecodeDelegateSellCmd);
    SET_ENCODER_DECODER(PROTO_GS_DELEGATE_BUY_CMD, EncodeDelegateBuyCmd, DecodeDelegateBuyCmd);
    SET_ENCODER_DECODER(PROTO_GS_MARKET_SELL_CMD, EncodeMarketSellCmd, DecodeMarketSellCmd);
    SET_ENCODER_DECODER(PROTO_GS_MARKET_BUY_CMD, EncodeMarketBuyCmd, DecodeMarketBuyCmd);
    SET_ENCODER_DECODER(PROTO_GS_QUERY_EX, EncodeQueryEx, DecodeQueryEx);
    SET_ENCODER_DECODER(PROTO_GS_SYS_MSG_NTF2, EncodeSysMsgNtf2, DecodeSysMsgNtf2);
    SET_ENCODER_DECODER(PROTO_GS_SCENE_DIALOG_NTF, EncodeSceneDialogNtf, DecodeSceneDialogNtf);
    SET_ENCODER_DECODER(PROTO_GS_SCROLL_TEXT_NTF, EncodeScrollText, DecodeScrollText);
    SET_ENCODER_DECODER(PROTO_GS_UPDATE_ONLINE_STATE, EncodeUpdateOnlineState, DecodeUpdateOnlineState);
    SET_ENCODER_DECODER(PROTO_GS_SYNC_SESSION_ID, EncodeSyncSessionID, DecodeSyncSessionID);
    SET_ENCODER_DECODER(PROTO_GS_TRADE_LIST_UPDATE, EncodeTradeMallListUpdate, DecodeTradeMallListUpdate);
    SET_ENCODER_DECODER(PROTO_GS_SET_MAINTENANCE_STATUE, EncodeSetMaintenanceStatus, DecodeSetMaintenanceStatus);
    SET_ENCODER_DECODER(PROTO_GS_KICK_OUT_BY_LOCK, EncodeKickOutByLock, DecodeKickOutByLock);
    SET_ENCODER_DECODER(PROTO_GS_JUMP_MAP_REQ, EncodeJumpMapReq, DecodeJumpMapReq);
    SET_ENCODER_DECODER(PROTO_GS_GET_NPC_POS_REQ, EncodeGetNpcPosReq, DecodeGetNpcPosReq);
    SET_ENCODER_DECODER(PROTO_GS_GET_NPC_POS_ACK, EncodeGetNpcPosAck, DecodeGetNpcPosAck);
    SET_ENCODER_DECODER(PROTO_GS_START_DIG_REQ, EncodeStartDigReq, DecodeStartDigReq);
    SET_ENCODER_DECODER(PROTO_GS_RANGE_PICKUP, EncodeRangePickup, DecodeRangePickup);
    SET_ENCODER_DECODER(PROTO_GS_SYNC_CLIENT_BASE_SETTING, EncodeSyncClientBaseSetting, DecodeSyncClientBaseSetting);
    SET_ENCODER_DECODER(PROTO_GS_VERIFY_BUY_ITEM_INFO_REQ, EncodeVerifyBuyItemInfoReq, DecodeVerifyBuyItemInfoReq);
    SET_ENCODER_DECODER(PROTO_GS_PLAYER_SET_NAME_NTF, EncodePlayerSetNameNtf, DecodePlayerSetNameNtf);
    SET_ENCODER_DECODER(PROTO_GS_ITEM_REFRESH_REQ, EncodeItemRefreshReq, DecodeItemRefreshReq);
    SET_ENCODER_DECODER(PROTO_GS_ITEM_TIP, EncodeItemTip, DecodeItemTip);
    SET_ENCODER_DECODER(PROTO_GS_ITEM_TIP_NTF, EncodeItemTipNtf, DecodeItemTipNtf);
    SET_ENCODER_DECODER(PROTO_GS_CUST_MSG_NTF, EncodeCustMsgNtf, DecodeCustMsgNtf);
    SET_ENCODER_DECODER(PROTO_GS_TITLE_ADD_ACK, EncodeTitleAddAck, DecodeTitleAddAck);
    SET_ENCODER_DECODER(PROTO_GS_TITLE_DEL, EncodeTitleDel, DecodeTitleDel);
    SET_ENCODER_DECODER(PROTO_GS_TITLE_DEL_ACK, EncodeTitleDelAck, DecodeTitleDelAck);
    SET_ENCODER_DECODER(PROTO_GS_TITLE_WEAR, EncodeTitleWear, DecodeTitleWear);
    SET_ENCODER_DECODER(PROTO_GS_TITLE_WEAR_NTF, EncodeTitleWearNtf, DecodeTitleWearNtf);
    SET_ENCODER_DECODER(PROTO_GS_TITLE_UNWEAR, EncodeTitleUnWear, DecodeTitleUnWear);
    SET_ENCODER_DECODER(PROTO_GS_TITLE_UNWEAR_NTF, EncodeTitleUnWearNtf, DecodeTitleUnWearNtf);
    SET_ENCODER_DECODER(PROTO_GS_TITLE_LIST, EncodeTitleList, DecodeTitleList);
    SET_ENCODER_DECODER(PROTO_GS_SET_AUTO_MODE_ACK, EncodeSetAutoModeAck, DecodeSetAutoModeAck);
    SET_ENCODER_DECODER(PROTO_GS_TITLE_GET_LIST_REQ, EncodeTitleGetListReq, DecodeTitleGetListReq);
    SET_ENCODER_DECODER(PROTO_GS_AFTER_RELOGIN_UPDATE_STATUS, EncodeAfterReloginUpdateStatus, DecodeAfterReloginUpdateStatus);
    SET_ENCODER_DECODER(PROTO_GS_GOODS_POST_RECORD_ACK, EncodeGoodsPostRecordAck, DecodeGoodsPostRecordAck);

}

ProtoGS::~ProtoGS()
{

}

int ProtoGS::BuildProtocol(void* pHost, char* pNet, int iNetSize)
{
    unsigned short moduleid = *(unsigned short*)pHost;
    unsigned short protoid = *(unsigned short*)((char*)pHost + sizeof(unsigned short));
    if (moduleid != GetModuleID()) {
        return -1;
    }
    if (protoid >= PROTO_GS_MAX) {
        return -1;
    }

    CNetData m_oData;
    m_oData.Prepare(pNet, iNetSize);
    return m_EnCodeFuncArray[protoid](pHost, &m_oData);
}

int ProtoGS::HandleProtocol(void* pNet, char* pHost, int iNetSize)
{
    unsigned short moduleid = *(unsigned short*)pNet;
    unsigned short protoid = *(unsigned short*)((char*)pNet + sizeof(unsigned short));
    if (moduleid != GetModuleID()) {
        return -1;
    }
    if (protoid >= PROTO_GS_MAX) {
        return -1;
    }

    CNetData m_oData;
    m_oData.Prepare((char*)pNet, iNetSize);
    return m_DeCodeFuncArray[protoid](pHost, &m_oData);
}