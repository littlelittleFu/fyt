#pragma once
#include "MailMgr.h"
#include "LuaHost.h"
class Player;

class GMCmdHandler
{
public:
    static void HandleCmd(Player *admin, const char *cmd, const char *param, int32_t sn);

private:
    GMCmdHandler() = delete;

    static int32_t HandleCmd_closeS(Player *admin, const char *param);
    static int32_t HandleCmd_maintenanceS(Player *admin, const char *param);
    static int32_t HandleCmd_ResetmaintenanceS(Player *admin, const char *param);
    static int32_t HandleCmd_AddWhiteIP(Player *admin, const char *param);
    static int32_t HandleCmd_DelWhiteIP(Player *admin, const char *param);
    static int32_t HandleCmd_AddBlackIP(Player *admin, const char *param);
    static int32_t HandleCmd_DelBlackIP(Player *admin, const char *param);
    static int32_t HandleCmd_support_player(Player* admin, const char* param);
    static int32_t HandleCmd_un_support_player(Player* admin, const char* param);
    static int32_t HandleCmd_lock_player(Player *admin, const char *param);
    static int32_t HandleCmd_unlock_player(Player *admin, const char *param);
    static int32_t HandleCmd_lock_role(Player *admin, const char *param);
    static int32_t HandleCmd_DeleteRole(Player* admin, const char* param);
    static int32_t HandleCmd_unlock_role(Player *admin, const char *param);
    static int32_t HandleCmd_prohibit_chat(Player *admin, const char *param);
    static int32_t HandleCmd_unprohibit_chat(Player *admin, const char *param);
    static int32_t HandleCmd_ReloadScript(Player *admin, const char *param);
    static int32_t HandleCmd_ReloadGameCfg(Player *admin, const char *param);
    static int32_t HandleCmd_IssueGoods(Player *admin, const char *param);
    static int32_t HandleCmd_mail(Player *admin, const char *param);
    static int32_t HandleCmd_add64(Player *admin, const char *param);
    static int32_t HandleCmd_sendmsg(Player *admin, const char *param);
    static int32_t HandleCmd_AddItem(Player *admin, const char *param);
    static int32_t HandleCmd_RemoveItem(Player *admin, const char *param);
    static int32_t HandleCmd_SetPlayerProp(Player *admin, const char *param);
    static int32_t HandleCmd_SetPlayerCustVar(Player* admin, const char* param);
    static int32_t HandleCmd_AddBuff(Player* admin, const char* param);
    static int32_t HandleCmd_AddLuaGM(Player* admin, const char* param);
    static int32_t HandleCmd_DelLuaGM(Player* admin, const char* param);
    static int32_t HandleCmd_AddPlayerProhibitChat(Player* admin, const char* param);
    static int32_t HandleCmd_DelPlayerProhibitChat(Player* admin, const char* param);
    static int32_t HandleCmd_RunScript(Player* admin, const char* param);
    static int32_t HandleCmd_DeleteMail(Player* admin, const char* param);
    static int32_t HandleCmd_KickOut(Player* admin, const char* param);


    

    static void RecordOperation(Player *admin, const char *cmd, const char *param);

    static bool IsNeedSendToCS(const char *cmd, const char *param);
    static void SendRunGMCmdToCS(const char *cmd, const char *param);
};
