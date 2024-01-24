#pragma once
#include "Types.h"
#include "DataInfo.hpp"
#include "ProtoCS.h"
#include "ProtoMS.h"

class Session;
class Player;

// ” º˛π‹¿Ì
class MailMgr
{
    MailMgr() = default;
    ~MailMgr() = default;
public:
    static void AddMailInfo(Session* session, Player* player, const MAIL_INFO& data);
    static void GetMailList(Session* session, Player* player, uint64_t mailid, int32_t type);
    static void OpenMail(Session* session, Player* player, uint64_t mailid);
    static void DeleteMail(Session* session, Player* player, uint64_t mailid);
    static void AttachMentGet(Session* session, Player* player, uint64_t mailid, uint8_t index);
    static void GetMailAttachmentAck(Session* session, Player* player, ProtoCS_GetMailAttachmentAck& msg);
    static int FillCurrencyInfo(int type, int64_t value, MAIL_INFO& infos);
    static int FillAddtionsInfo(const std::string& name, uint64_t guid, int num, int bind, MAIL_INFO& infos);
    static int32_t AddMailSys2Player(ProtoMS_AddSysNewMail& data);
    static int ParseParamsByLua(const std::string& Rolename, uint64_t Guid, uint16_t addType, const std::string& title, const std::string& text, 
        const CLuaObject& additions, const CLuaObject& currency, uint8_t type, ProtoMS_AddSysNewMail& data);
    static int ParseParamsByGM(const char* params,ProtoMS_AddSysNewMail& data);

private:
    static int32_t GetMailAttachment(Player* player, uint64_t mailid, const ADDITION_ITEM_INFO& itemInfo, uint16_t idx);
};
