#include "stdafx.h"
#include "ProtoClient2.h"
#include "ILogHelper.h"

static int EncodeCustMsgNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_CustMsgNtf);
    ENCODE_DWORD(size);
    if (-1 == poNetData->AddBlob(pstIn->message, pstIn->size))return -1;
    ENCODE_STRING(font_color);
    ENCODE_STRING(background_color);
    ENCODE_BYTE(comp);
    ENCODE_WORD(display_type);
    ENCODE_BYTE(scroll_times);
    END_ENCODE();
}

static int DecodeCustMsgNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_CustMsgNtf);
    DECODE_DWORD(size);
    if (-1 == poNetData->DelBlob(pstOut->message, pstOut->size))
        return -1;
    DECODE_STRING(font_color);
    DECODE_STRING(background_color);
    DECODE_BYTE(comp);
    DECODE_WORD(display_type);
    DECODE_BYTE(scroll_times);
    END_DECODE();
}

static int EncodeSysMsgNtf2(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_SysMsgNtf2);
    ENCODE_DWORD(size);
    if (-1 == poNetData->AddBlob(pstIn->message, pstIn->size))return -1;
    ENCODE_STRING(font_color);
    ENCODE_STRING(background_color);
    ENCODE_BYTE(comp);
    END_ENCODE();
}

static int DecodeSysMsgNtf2(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_SysMsgNtf2);
    DECODE_DWORD(size);
    if (-1 == poNetData->DelBlob(pstOut->message, pstOut->size))
        return -1;
    DECODE_STRING(font_color);
    DECODE_STRING(background_color);
    DECODE_BYTE(comp);
    END_DECODE();
}

static int EncodeSceneDialogNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_SceneDialogNtf);
    ENCODE_DWORD(size);
    if (-1 == poNetData->AddBlob(pstIn->message, pstIn->size))return -1;
    ENCODE_STRING(font_color);
    ENCODE_STRING(background_color);
    ENCODE_QWORD(objGuid);
    ENCODE_BYTE(isAppearSrcName);
    ENCODE_BYTE(comp);
    END_ENCODE();
}

static int DecodeSceneDialogNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_SceneDialogNtf);
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

static int EncodeScrollText(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_ScrollText);
    ENCODE_DWORD(size);
    ENCODE_BLOB(message,pstIn->size);
    ENCODE_STRING(font_color);
    ENCODE_STRING(background_color);
    ENCODE_BYTE(scroll_times);
    ENCODE_BYTE(comp);
    ENCODE_BYTE(type);
    END_ENCODE();
}

static int DecodeScrollText(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_ScrollText);
    DECODE_DWORD(size);
    DECODE_BLOB(message,pstOut->size);
    DECODE_STRING(font_color);
    DECODE_STRING(background_color);
    DECODE_BYTE(scroll_times);
    DECODE_BYTE(comp);
    DECODE_BYTE(type);
    END_DECODE();
}

static int EncodeMailAttachmentGetReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_MailAttachmentGetReq);
    ENCODE_QWORD(mail_id);
    ENCODE_BYTE(index);
    END_ENCODE();
}

static int DecodeMailAttachmentGetReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_MailAttachmentGetReq);
    DECODE_QWORD(mail_id);
    DECODE_BYTE(index);
    END_DECODE();
}

static int EncodeMailAttachmentGetAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_MailAttachmentGetAck);
    ENCODE_QWORD(mail_id);
    ENCODE_BYTE(index);
    ENCODE_DWORD(errcode);
    END_ENCODE();
}

static int DecodeMailAttachmentGetAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_MailAttachmentGetAck);
    DECODE_QWORD(mail_id);
    DECODE_BYTE(index);
    DECODE_DWORD(errcode);
    END_DECODE();
}

static int EncodeMailOpenReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_MailOpenReq);
    ENCODE_QWORD(id);
    END_ENCODE();
}

static int DecodeMailOpenReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_MailOpenReq);
    DECODE_QWORD(id);
    END_DECODE();
}

static int EncodeMailOpenAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_MailOpenAck);
    ENCODE_QWORD(mail_id);
    if (-1 == EnCodeMAIL_BODY_INFO(&pstIn->mail, poNetData))return -1;
    END_ENCODE();
}

static int DecodeMailOpenAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_MailOpenAck);
    DECODE_QWORD(mail_id);
    if (-1 == DeCodeMAIL_BODY_INFO(&pstOut->mail, poNetData))return -1;
    END_DECODE();
}

static int EncodeMailOpenAck2(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_MailOpenAck2);
    ENCODE_QWORD(mail_id);
    if (-1 == EnCodeMAIL_BODY_INFO2(&pstIn->mail, poNetData))return -1;
    END_ENCODE();
}

static int DecodeMailOpenAck2(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_MailOpenAck2);
    DECODE_QWORD(mail_id);
    if (-1 == DeCodeMAIL_BODY_INFO2(&pstOut->mail, poNetData))return -1;
    END_DECODE();
}

static int EncodeMailDelReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_MailDeleteReq);
    ENCODE_QWORD(id);
    END_ENCODE();
}

static int DecodeMailDelReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_MailDeleteReq);
    DECODE_QWORD(id);
    END_DECODE();
}

static int EncodeMailDelAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_MailDeleteAck);
    ENCODE_QWORD(id);
    ENCODE_DWORD(errcode);
    END_ENCODE();
}

static int DecodeMailDelAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_MailDeleteAck);
    DECODE_QWORD(id);
    DECODE_DWORD(errcode);
    END_DECODE();
}

static int EncodeMailListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_MaillistReq);
    ENCODE_BYTE(type);
    ENCODE_QWORD(mail_id);
    END_ENCODE();
}

static int DecodeMailListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_MaillistReq);
    DECODE_BYTE(type);
    DECODE_QWORD(mail_id);
    END_DECODE();
}

static int EncodeMailListAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_MaillistAck);
    ENCODE_WORD(cur_page);
    ENCODE_WORD(page_num);
    ENCODE_INT(num);
    for (uint16_t i = 0; i < pstIn->num; ++i) {
        if (-1 == EnCodeMAIL_HEADER_INFO(&pstIn->mails[i], poNetData))return -1;
    }
    END_ENCODE();
}

static int DecodeMailListAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_MaillistAck);
    DECODE_WORD(cur_page);
    DECODE_WORD(page_num);
    DECODE_INT(num);
    for (uint16_t i = 0; i < pstOut->num; ++i) {
        if (-1 == DeCodeMAIL_HEADER_INFO(&pstOut->mails[i], poNetData))return -1;
    }
    END_DECODE();
}

static int EncodeNewMailNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_NewMailNtf);
    END_ENCODE();
}

static int DecodeNewMailNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_NewMailNtf);
    END_DECODE();
}

static int EncodeTeamKickEx(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_TeamKickEx);
    ENCODE_STRING(name);
    END_ENCODE();
}

static int DecodeTeamKickEx(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_TeamKickEx);
    DECODE_STRING(name);
    END_DECODE();
}

static int EncodeTeamLeaveEx(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_TeamLeaveEx);
    END_ENCODE();
}

static int DecodeTeamLeaveEx(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_TeamLeaveEx);
    END_DECODE();
}

static int EncodeTeamInvite(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_TeamInvite);
    ENCODE_STRING(invitee_name);
    END_ENCODE();
}

static int DecodeTeamInvite(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_TeamInvite);
    DECODE_STRING(invitee_name);
    END_DECODE();
}

static int EncodeTeamInviteNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_TeamInviteNtf);
    ENCODE_STRING(inviter_name);
    ENCODE_BYTE(exist);
    ENCODE_WORD(num);
    EnCodeTEAM_INFO(&pstIn->info[0], poNetData);
    END_ENCODE();
}

static int DecodeTeamInviteNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_TeamInviteNtf);
    DECODE_STRING(inviter_name);
    DECODE_BYTE(exist);
    DECODE_WORD(num);
    DeCodeTEAM_INFO(&pstOut->info[0], poNetData);
    END_DECODE();
}

static int EncodeTeamInviteRsp(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_TeamInviteRsp);
    ENCODE_STRING(inviter_name);
    ENCODE_BYTE(accepted);
    END_ENCODE();
}

static int DecodeTeamInviteRsp(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_TeamInviteRsp);
    DECODE_STRING(inviter_name);
    DECODE_BYTE(accepted);
    END_DECODE();
}

static int EncodeMissTeamNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_TeamLeaveNtf);
    ENCODE_QWORD(player_guid);
    ENCODE_BYTE(type);
    END_ENCODE();
}

static int DecodeMissTeamNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_TeamLeaveNtf);
    DECODE_QWORD(player_guid);
    DECODE_BYTE(type);
    END_DECODE();
}

static int EncodeTeamNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_TeamNtf);
    EnCodeTEAM_INFO(&pstIn->info,  poNetData);
    END_ENCODE();
}

static int DecodeTeamNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_TeamNtf);
    DeCodeTEAM_INFO(&pstOut->info,  poNetData);
    END_DECODE();
}

static int EncodeTeamoperation(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_Teamoperation);
    ENCODE_BYTE(operation);
    ENCODE_STRING(content);
    END_ENCODE();
}

static int DecodeTeamoperation(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_Teamoperation);
    DECODE_BYTE(operation);
    DECODE_STRING(content);
    END_DECODE();
}

static int EncodePrivateChatNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_PrivateChatNtf);
    ENCODE_BYTE(type);

    if (EnCodeCHAT_MSG(&pstIn->chat_message, poNetData) == -1)
        return -1;

    END_ENCODE();
}

static int DecodePrivateChatNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_PrivateChatNtf);
    DECODE_BYTE(type);

    if (DeCodeCHAT_MSG(&pstOut->chat_message, poNetData) == -1)
        return -1;

    END_DECODE();
}

static int EncodeRelationChatReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_RelationChatReq);
    ENCODE_BYTE(type);
    ENCODE_STRING(message);
    END_ENCODE();
}

static int DecodeRelationChatReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_RelationChatReq);
    DECODE_BYTE(type);
    DECODE_STRING(message);
    END_DECODE();
}

static int EncodeRelationChatAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_RelationChatAck);
    ENCODE_BYTE(type);
    if (EnCodeCHAT_MSG(&pstIn->chat_message, poNetData) == -1)
        return -1;
    ENCODE_STRING(font_color);
    ENCODE_STRING(background_color);
    ENCODE_BYTE(scroll_times);

    END_ENCODE();
}

static int DecodeRelationChatAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_RelationChatAck);
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
    BEGIN_ENCODE_EX(ProtoClient2_RelationChatNtf);
    ENCODE_DWORD(size);
    ENCODE_BYTE(type);
    if (-1 == poNetData->AddString(pstIn->chat_message.role_name, _countof(pstIn->chat_message.role_name)))return -1;
    if (-1 == poNetData->AddBlob(pstIn->chat_message.message, pstIn->size))return -1;
    ENCODE_STRING(font_color);
    ENCODE_STRING(background_color);
    ENCODE_BYTE(scroll_times);
    ENCODE_BYTE(comp);
    END_ENCODE();
}

static int DecodeRelationChatNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_RelationChatNtf);
    DECODE_DWORD(size);
    DECODE_BYTE(type);
    if (-1 == poNetData->DelString(pstOut->chat_message.role_name, _countof(pstOut->chat_message.role_name)))
        return -1;
    if (-1 == poNetData->DelBlob(pstOut->chat_message.message, pstOut->size))
        return -1;
    DECODE_STRING(font_color);
    DECODE_STRING(background_color);
    DECODE_BYTE(scroll_times);
    DECODE_BYTE(comp);
    END_DECODE();
}

static int EncodeSysMsgNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_SysMsgNtf);
    ENCODE_BYTE(msg_type);
    ENCODE_BYTE(scroll_count);
    ENCODE_STRING(msg);
    END_ENCODE();
}

static int DecodeSysMsgNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_SysMsgNtf);
    DECODE_BYTE(msg_type);
    DECODE_BYTE(scroll_count);
    DECODE_STRING(msg);
    END_DECODE();
}

static int EncodeSpeakerMsgReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_SpeakerMsgReq);
    ENCODE_STRING(msg);
    END_ENCODE();
}

static int DecodeSpeakerMsgReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_SpeakerMsgReq);
    DECODE_STRING(msg);
    END_DECODE();
}

static int EncodeSpeakerMsgNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_SpeakerMsgNtf);
    ENCODE_STRING(sender);
    ENCODE_STRING(msg);
    END_ENCODE();
}

static int DecodeSpeakerMsgNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_SpeakerMsgNtf);
    DECODE_STRING(sender);
    DECODE_STRING(msg);
    END_DECODE();
}

static int EncodeTeamTeamJoin(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_TeamJoin);
    ENCODE_STRING(team_member);
    END_ENCODE();
}

static int DecodeTeamTeamJoin(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_TeamJoin);
    DECODE_STRING(team_member);
    END_DECODE();
}

static int EncodeTeamTeamJoinNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_TeamJoinNtf);
    ENCODE_STRING(joiner);
    END_ENCODE();
}

static int DecodeTeamTeamJoinNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_TeamJoinNtf);
    DECODE_STRING(joiner);
    END_DECODE();
}

static int EncodeTeamTeamJoinResponse(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_TeamJoinResponse);
    ENCODE_STRING(joiner);
    ENCODE_BYTE(accepted);
    END_ENCODE();
}

static int DecodeTeamTeamJoinResponse(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_TeamJoinResponse);
    DECODE_STRING(joiner);
    DECODE_BYTE(accepted);
    END_DECODE();
}

static int EncodeTeamLeaderNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_TeamLeaderNtf);
    ENCODE_QWORD(leader_guid);
    END_ENCODE();
}

static int DecodeTeamLeaderNtf(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_TeamLeaderNtf);
    DECODE_QWORD(leader_guid);
    END_DECODE();
}

static int EncodeFamilyJoinReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyJoinReq);
    ENCODE_QWORD(guid);
    END_ENCODE();
}

static int DecodeFamilyJoinReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyJoinReq);
    DECODE_QWORD(guid);
    END_DECODE();
}

static int EncodeFamilyJoinAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyJoinAck);
    ENCODE_QWORD(guid);
    ENCODE_BYTE(is_allow);
    END_ENCODE();
}

static int DecodeFamilyJoinAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyJoinAck);
    DECODE_QWORD(guid);
    DECODE_BYTE(is_allow);
    END_DECODE();
}

static int EncodeFamilyInviteReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyInviteReq);
    ENCODE_STRING(name);
    END_ENCODE();
}

static int DecodeFamilyInviteReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyInviteReq);
    DECODE_STRING(name);
    END_DECODE();
}

static int EncodeFamilyInviteVerify(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyInviteVerify);
    ENCODE_QWORD(guid);
    ENCODE_STRING(name);
    END_ENCODE();
}

static int DecodeFamilyInviteVerify(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyInviteVerify);
    DECODE_QWORD(guid);
    DECODE_STRING(name);
    END_DECODE();
}

static int EncodeFamilyInviteAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyInviteAck);
    ENCODE_QWORD(guid);
    ENCODE_BYTE(result);
    END_ENCODE();
}

static int DecodeFamilyInviteAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyInviteAck);
    DECODE_QWORD(guid);
    DECODE_BYTE(result);
    END_DECODE();
}

static int EncodeGetFamilyInfoReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_GetFamilyInfoReq);
    ENCODE_DWORD(reqType);
    ENCODE_DWORD(start_index);
    ENCODE_DWORD(req_count);
    ENCODE_DWORD(req_group);
    ENCODE_STRING(info);
    END_ENCODE();
}

static int DecodeGetFamilyInfoReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_GetFamilyInfoReq);
    DECODE_DWORD(reqType);
    DECODE_DWORD(start_index);
    DECODE_DWORD(req_count);
    DECODE_DWORD(req_group);
    DECODE_STRING(info);
    END_DECODE();
}

static int EncodeFamilyNoticeAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyNoticeAck);
    ENCODE_DWORD(notice_len);
    ENCODE_BLOB(notice, pstIn->notice_len);
    END_ENCODE();
}

static int DecodeFamilyNoticeAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyNoticeAck);
    DECODE_DWORD(notice_len);
    DECODE_BLOB(notice, pstOut->notice_len);
    END_DECODE();
}

static int EncodeFamilyMsgAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyMsgAck);
    ENCODE_DWORD(msg_len);
    ENCODE_STRING(sysmsgs);
    END_ENCODE();
}

static int DecodeFamilyMsgAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyMsgAck);
    DECODE_DWORD(msg_len);
    DECODE_STRING(sysmsgs);
    END_DECODE();
}

static int EncodeFamilyTitlesAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyTitlesAck);
    ENCODE_DWORD(titles_len);

    for (uint32_t i = 0; i < pstIn->titles_len; ++i)
        if (EnCodeFAMILY_TITLE(pstIn->titles + i, poNetData) == -1)
            return -1;

    END_ENCODE();
}

static int DecodeFamilyTitlesAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyTitlesAck);
    DECODE_DWORD(titles_len);

    for (uint32_t i = 0; i < pstOut->titles_len; ++i)
        if (DeCodeFAMILY_TITLE(pstOut->titles + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodeFamilyMembersAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyMembersAck);
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
    BEGIN_DECODE_EX(ProtoClient2_FamilyMembersAck);
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
    BEGIN_ENCODE_EX(ProtoClient2_FamilyEnemyAck);
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
    BEGIN_DECODE_EX(ProtoClient2_FamilyEnemyAck);
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
    BEGIN_ENCODE_EX(ProtoClient2_FamilyAllyAck);
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
    BEGIN_DECODE_EX(ProtoClient2_FamilyAllyAck);
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
    BEGIN_ENCODE_EX(ProtoClient2_FamilyJoinListAck);
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
    BEGIN_DECODE_EX(ProtoClient2_FamilyJoinListAck);
    DECODE_DWORD(total_num);
    DECODE_DWORD(first_index);
    DECODE_WORD(num);

    for (uint16_t i = 0; i < pstOut->num; ++i)
        if (DeCodeAPPLICANTS_INFO(pstOut->info + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodeFamilyTitleModifyReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyTitleModifyReq);
    ENCODE_BYTE(id);
    ENCODE_STRING(title);
    END_ENCODE();
}

static int DecodeFamilyTitleModifyReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyTitleModifyReq);
    DECODE_BYTE(id);
    DECODE_STRING(title);
    END_DECODE();
}

static int EncodeFamilyTitleAwardReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyTitleAwardReq);
    ENCODE_QWORD(guid);
    ENCODE_BYTE(title_id);
    END_ENCODE();
}

static int DecodeFamilyTitleAwardReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyTitleAwardReq);
    DECODE_QWORD(guid);
    DECODE_BYTE(title_id);
    END_DECODE();
}

static int EncodeFamilyLeaveOrLastMsgReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyLeaveOrLastMsgReq);
    ENCODE_STRING(byebye);
    END_ENCODE();
}

static int DecodeFamilyLeaveOrLastMsgReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyLeaveOrLastMsgReq);
    DECODE_STRING(byebye);
    END_DECODE();
}

static int EncodeFamilyExpellReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyExpellReq);
    ENCODE_QWORD(player_guid);
    END_ENCODE();
}

static int DecodeFamilyExpellReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyExpellReq);
    DECODE_QWORD(player_guid);
    END_DECODE();
}

static int EncodeFamilyLeaveNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyLeaveNtf);
    ENCODE_STRING(kicker_name);
    ENCODE_STRING(family_name);
    END_ENCODE();
}

static int DecodeFamilyLeaveNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyLeaveNtf);
    DECODE_STRING(kicker_name);
    DECODE_STRING(family_name);
    END_DECODE();
}

static int EncodeFamilyDestroyReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyDestroyReq);
    END_ENCODE();
}

static int DecodeFamilyDestroyReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyDestroyReq);
    END_DECODE();
}

static int EncodeFamilyAddAllyEnemyReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyAddAllyEnemyReq);
    ENCODE_BYTE(type);
    ENCODE_STRING(family_name);
    END_ENCODE();
}

static int DecodeFamilyAddAllyEnemyReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyAddAllyEnemyReq);
    DECODE_BYTE(type);
    DECODE_STRING(family_name);
    END_DECODE();
}

static int EncodeFamilyAddAllyVerify(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyAddAllyVerify);
    ENCODE_STRING(family_name);
    END_ENCODE();
}

static int DecodeFamilyAddAllyVerify(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyAddAllyVerify);
    DECODE_STRING(family_name);
    END_DECODE();
}

static int EncodeFamilyAddAllyAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyAddAllyAck);
    ENCODE_STRING(family_name);
    ENCODE_BYTE(result);
    END_ENCODE();
}

static int DecodeFamilyAddAllyAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyAddAllyAck);
    DECODE_STRING(family_name);
    DECODE_BYTE(result);
    END_DECODE();
}

static int EncodeFamilyDeleteAllyEnemyReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyDeleteAllyEnemyReq);
    ENCODE_QWORD(family_guid);
    END_ENCODE();
}

static int DecodeFamilyDeleteAllyEnemyReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyDeleteAllyEnemyReq);
    DECODE_QWORD(family_guid);
    END_DECODE();
}

static int EncodeFamilyNoticeEditReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyNoticeEditReq);
    ENCODE_DWORD(notice_len);
    ENCODE_BLOB(notice, pstIn->notice_len);
    END_ENCODE();
}

static int DecodeFamilyNoticeEditReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyNoticeEditReq);
    DECODE_DWORD(notice_len);
    DECODE_BLOB(notice, pstOut->notice_len);
    END_DECODE();
}

static int EncodeFamilyNameInputReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyNameInputReq);
    END_ENCODE();
}

static int DecodeFamilyNameInputReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyNameInputReq);
    END_DECODE();
}

static int EncodeFamilyNameInputAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyNameInputAck);
    ENCODE_STRING(family_name);
    END_ENCODE();
}

static int DecodeFamilyNameInputAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyNameInputAck);
    DECODE_STRING(family_name);
    END_DECODE();
}

static int EncodeFamilyListNtfAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyListNtfAck);
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
    BEGIN_DECODE_EX(ProtoClient2_FamilyListNtfAck);
    DECODE_DWORD(total_num);
    DECODE_DWORD(first_index);
    DECODE_DWORD(num);

    for (uint32_t i = 0; i < pstOut->num; ++i)
        if (DeCodeFAMILY_APPLY_INFO(pstOut->familys + i, poNetData) == -1)
            return -1;

    END_DECODE();
}

static int EncodeFamilyInfoNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyInfoNtf);
    ENCODE_DWORD(type);
    END_ENCODE();
}

static int DecodeFamilyInfoNtf(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyInfoNtf);
    DECODE_DWORD(type);
    END_DECODE();
}

static int EncodeFamilyBaseInfoAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FamilyBaseInfoAck);
    ENCODE_QWORD(family_guid);
    ENCODE_STRING(name);
    ENCODE_DWORD(members_num);
    ENCODE_QWORD(create_time);
    ENCODE_BYTE(self_title_id);
    END_ENCODE();
}

static int DecodeFamilyBaseInfoAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FamilyBaseInfoAck);
    DECODE_QWORD(family_guid);
    DECODE_STRING(name);
    DECODE_DWORD(members_num);
    DECODE_QWORD(create_time);
    DECODE_BYTE(self_title_id);
    END_DECODE();
}

static int EncodeCancelFamilyJoinReq(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_CancelFamilyJoinReq);
    ENCODE_QWORD(guid);
    END_ENCODE();
}

static int DecodeCancelFamilyJoinReq(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_CancelFamilyJoinReq);
    DECODE_QWORD(guid);
    END_DECODE();
}

static int EncodeCancelFamilyJoinAck(void *pHost, CNetData *poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_CancelFamilyJoinAck);
    ENCODE_QWORD(guid);
    ENCODE_DWORD(errcode);
    END_ENCODE();
}

static int DecodeCancelFamilyJoinAck(void *pHost, CNetData *poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_CancelFamilyJoinAck);
    DECODE_QWORD(guid);
    DECODE_DWORD(errcode);
    END_DECODE();
}

static int EncodeTopListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_TopListReq);
    ENCODE_BYTE(type);
    END_ENCODE();
}

static int DecodeTopListReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_TopListReq);
    DECODE_BYTE(type);
    END_DECODE();
}

static int EncodeTopListAck(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_TopListAck);
    ENCODE_BYTE(type);
    ENCODE_DWORD(time);
    ENCODE_BYTE(num);
    for (uint8_t i = 0; i < pstIn->num; i++)
        if (-1 == EnCodeTOPLIST_INFO(pstIn->info + i, poNetData))
            return -1;
    END_ENCODE();
}

static int DecodeTopListAck(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_TopListAck);
    DECODE_BYTE(type);
    DECODE_DWORD(time);
    DECODE_BYTE(num);
    for (uint8_t i = 0; i < pstOut->num; i++)
        if (-1 == DeCodeTOPLIST_INFO(pstOut->info + i, poNetData))
            return -1;
    END_DECODE();
}

static int EncodeFriendAddReq(void* pHost, CNetData* poNetData)
{
    BEGIN_ENCODE_EX(ProtoClient2_FriendAddReq);
    ENCODE_STRING(player_name);
    END_ENCODE();
}

static int DecodeFriendAddReq(void* pHost, CNetData* poNetData)
{
    BEGIN_DECODE_EX(ProtoClient2_FriendAddReq);
    DECODE_STRING(player_name);
    END_DECODE();
}

ProtoClient2::ProtoClient2()
{
    for (int i = 0; i < PROTO_CLIENT2_MAX; ++i) {
        SET_ENCODER_DECODER(i, EncodeNotImpl, DecodeNotImpl);
    }

    SET_ENCODER_DECODER(PROTO_CLIENT2_TEAM_LEADER_NTF, EncodeTeamLeaderNtf, DecodeTeamLeaderNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT2_TEAM_JOIN, EncodeTeamTeamJoin, DecodeTeamTeamJoin);
    SET_ENCODER_DECODER(PROTO_CLIENT2_TEAM_JOIN_NTF, EncodeTeamTeamJoinNtf, DecodeTeamTeamJoinNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT2_TEAM_JOIN_RSP, EncodeTeamTeamJoinResponse, DecodeTeamTeamJoinResponse);

    SET_ENCODER_DECODER(PROTO_CLIENT2_TEAM_KICK_REQ, EncodeTeamKickEx, DecodeTeamKickEx);
    SET_ENCODER_DECODER(PROTO_CLIENT2_TEAM_LEAVE_REQ, EncodeTeamLeaveEx, DecodeTeamLeaveEx);
    SET_ENCODER_DECODER(PROTO_CLIENT2_TEAM_INVITE, EncodeTeamInvite, DecodeTeamInvite);
    SET_ENCODER_DECODER(PROTO_CLIENT2_TEAM_INVITE_NTF, EncodeTeamInviteNtf, DecodeTeamInviteNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT2_TEAM_INVITE_RSP, EncodeTeamInviteRsp, DecodeTeamInviteRsp);
    SET_ENCODER_DECODER(PROTO_CLIENT2_TEAM_OPERATION, EncodeTeamoperation, DecodeTeamoperation);
    SET_ENCODER_DECODER(PROTO_CLIENT2_TEAM_NTF, EncodeTeamNtf, DecodeTeamNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT2_MISS_TEAM_NTF, EncodeMissTeamNtf, DecodeMissTeamNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT2_PRIVATE_CHAT_NTF, EncodePrivateChatNtf, DecodePrivateChatNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT2_RELATION_CHAT_REQ, EncodeRelationChatReq, DecodeRelationChatReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_RELATION_CHAT_ACK, EncodeRelationChatAck, DecodeRelationChatAck);
    SET_ENCODER_DECODER(PROTO_CLIENT2_RELATION_CHAT_NTF, EncodeRelationChatNtf, DecodeRelationChatNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT2_SYS_MSG_NTF, EncodeSysMsgNtf, DecodeSysMsgNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT2_SPEAKER_MSG_REQ, EncodeSpeakerMsgReq, DecodeSpeakerMsgReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_SPEAKER_MSG_NTF, EncodeSpeakerMsgNtf, DecodeSpeakerMsgNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_JOIN_REQ, EncodeFamilyJoinReq, DecodeFamilyJoinReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_JOIN_ACK, EncodeFamilyJoinAck, DecodeFamilyJoinAck);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_INVITE_REQ, EncodeFamilyInviteReq, DecodeFamilyInviteReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_INVITE_VERIFY, EncodeFamilyInviteVerify, DecodeFamilyInviteVerify);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_INVITE_ACK, EncodeFamilyInviteAck, DecodeFamilyInviteAck);
    SET_ENCODER_DECODER(PROTO_CLIENT2_GET_FAMILY_INFO_REQ, EncodeGetFamilyInfoReq, DecodeGetFamilyInfoReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_NOTICE_ACK, EncodeFamilyNoticeAck, DecodeFamilyNoticeAck);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_MSG_ACK, EncodeFamilyMsgAck, DecodeFamilyMsgAck);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_TITLES_ACK, EncodeFamilyTitlesAck, DecodeFamilyTitlesAck);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_MEMBERS_ACK, EncodeFamilyMembersAck, DecodeFamilyMembersAck);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_ENEMY_ACK, EncodeFamilyEnemyAck, DecodeFamilyEnemyAck);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_ALLY_ACK, EncodeFamilyAllyAck, DecodeFamilyAllyAck);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_JOIN_LIST_ACK, EncodeFamilyJoinListAck, DecodeFamilyJoinListAck);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_TITLE_MODIFY_REQ, EncodeFamilyTitleModifyReq, DecodeFamilyTitleModifyReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_TITLE_AWARD_REQ, EncodeFamilyTitleAwardReq, DecodeFamilyTitleAwardReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_LEAVE_OR_LAST_MSG_REQ, EncodeFamilyLeaveOrLastMsgReq, DecodeFamilyLeaveOrLastMsgReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_EXPELL_REQ, EncodeFamilyExpellReq, DecodeFamilyExpellReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_LEAVE_NTF, EncodeFamilyLeaveNtf, DecodeFamilyLeaveNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_DESTROY_REQ, EncodeFamilyDestroyReq, DecodeFamilyDestroyReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_ADD_ALLY_ENEMY_REQ, EncodeFamilyAddAllyEnemyReq, DecodeFamilyAddAllyEnemyReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_ADD_ALLY_VERIFY, EncodeFamilyAddAllyVerify, DecodeFamilyAddAllyVerify);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_ADD_ALLY_ACK, EncodeFamilyAddAllyAck, DecodeFamilyAddAllyAck);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_DEL_ALLY_ENEMY_REQ, EncodeFamilyDeleteAllyEnemyReq, DecodeFamilyDeleteAllyEnemyReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_NOTICE_EDIT_REQ, EncodeFamilyNoticeEditReq, DecodeFamilyNoticeEditReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_NAME_INPUT_REQ, EncodeFamilyNameInputReq, DecodeFamilyNameInputReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_NAME_INPUT_ACK, EncodeFamilyNameInputAck, DecodeFamilyNameInputAck);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_LIST_NTF_ACK, EncodeFamilyListNtfAck, DecodeFamilyListNtfAck);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_INFO_NTF, EncodeFamilyInfoNtf, DecodeFamilyInfoNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FAMILY_BASE_INFO_ACK, EncodeFamilyBaseInfoAck, DecodeFamilyBaseInfoAck);
    SET_ENCODER_DECODER(PROTO_CLIENT2_CANCEL_FAMILY_JOIN_REQ, EncodeCancelFamilyJoinReq, DecodeCancelFamilyJoinReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_CANCEL_FAMILY_JOIN_ACK, EncodeCancelFamilyJoinAck, DecodeCancelFamilyJoinAck);
    SET_ENCODER_DECODER(PROTO_CLIENT2_TOPLIST_REQ, EncodeTopListReq, DecodeTopListReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_TOPLIST_ACK, EncodeTopListAck, DecodeTopListAck);    
	SET_ENCODER_DECODER(PROTO_CLIENT2_NEW_MAIL_NTF, EncodeNewMailNtf, DecodeNewMailNtf);
    SET_ENCODER_DECODER(PROTO_CLIENT2_MAIL_LIST_REQ, EncodeMailListReq, DecodeMailListReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_MAIL_LIST_ACK, EncodeMailListAck, DecodeMailListAck);
    SET_ENCODER_DECODER(PROTO_CLIENT2_MAIL_DEL_REQ, EncodeMailDelReq, DecodeMailDelReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_MAIL_DEL_ACK, EncodeMailDelAck, DecodeMailDelAck);
    SET_ENCODER_DECODER(PROTO_CLIENT2_MAIL_OPEN_REQ, EncodeMailOpenReq, DecodeMailOpenReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_MAIL_OPEN_ACK, EncodeMailOpenAck, DecodeMailOpenAck);
    SET_ENCODER_DECODER(PROTO_CLIENT2_MAIL_OPEN_ACK2, EncodeMailOpenAck2, DecodeMailOpenAck2);
    SET_ENCODER_DECODER(PROTO_CLIENT2_MAIL_ATTACHMENT_GET_REQ, EncodeMailAttachmentGetReq, DecodeMailAttachmentGetReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_MAIL_ATTACHMENT_GET_ACK, EncodeMailAttachmentGetAck, DecodeMailAttachmentGetAck);
    SET_ENCODER_DECODER(PROTO_CLIENT2_FRIEND_ADD_REQ, EncodeFriendAddReq, DecodeFriendAddReq);
    SET_ENCODER_DECODER(PROTO_CLIENT2_SYS_MSG_NTF2, EncodeSysMsgNtf2, DecodeSysMsgNtf2);
    SET_ENCODER_DECODER(PROTO_CLIENT2_SCENE_DIALOG_NTF, EncodeSceneDialogNtf, DecodeSceneDialogNtf);
    SET_ENCODER_DECODER(PROTO_CLINET2_SCROLL_TEXT_NTF, EncodeScrollText, DecodeScrollText);
    SET_ENCODER_DECODER(PROTO_CLIENT2_CUST_MSG_NTF, EncodeCustMsgNtf, DecodeCustMsgNtf);


}


ProtoClient2::~ProtoClient2()
{
}

int ProtoClient2::BuildProtocol(void* pHost, char* pNet, int iNetSize)
{
    unsigned short moduleid = *(unsigned short*)pHost;
    unsigned short protoid = *(unsigned short*)((char*)pHost + sizeof(unsigned short));
    if (moduleid != GetModuleID()) {
          return -1;
      }
    if (protoid >= PROTO_CLIENT2_MAX) {
        return -1;
    }

    CNetData m_oData;
    m_oData.Prepare(pNet, iNetSize);
    if (m_EnCodeFuncArray[protoid] == nullptr)
    {
        LOG_ERROR("cur protoid:%d", protoid);
    }
        return m_EnCodeFuncArray[protoid](pHost, &m_oData);

}

int ProtoClient2::HandleProtocol(void* pNet, char* pHost, int iNetSize)
{
    unsigned short moduleid = *(unsigned short*)pNet;
    unsigned short protoid = *(unsigned short*)((char*)pNet + sizeof(unsigned short));

#ifndef _HIDE_PROTO_LOG
    LOG_TRACE("moduleid: %d, protoid: %d", moduleid, protoid);
#endif // !_HIDE_PROTO_LOG


    if (moduleid != GetModuleID()) {
          return -1;
      }
    if (protoid >= PROTO_CLIENT2_MAX) {
        return -1;
    }

    CNetData m_oData;
    m_oData.Prepare((char*)pNet, iNetSize);
    return m_DeCodeFuncArray[protoid](pHost, &m_oData);
}
