#include "stdafx.h"
#include "ClientDB.hpp"

int EnCodeLoginReq(void* pHost, CNetData* poNetData)
{
	LoginReq* pstIn = (LoginReq*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->UserName, sizeof(pstIn->UserName)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->ip))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->pwd_len))
		return -1;

	{
		int iCount = (((128) < ((int)pstIn->pwd_len)) ? (128) : ((int)pstIn->pwd_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->password, iCount*sizeof(unsigned char)))
			return -1;
	}
	if(-1 == poNetData->AddString(pstIn->hwid, sizeof(pstIn->hwid)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeLoginReq(void* pHost, CNetData* poNetData)
{
	LoginReq* pstOut = (LoginReq*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->UserName, sizeof(pstOut->UserName)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->ip))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->pwd_len))
		return -1;

	{
		int iCount = (((128) < ((int)pstOut->pwd_len)) ? (128) : ((int)pstOut->pwd_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->password, iCount*sizeof(unsigned char)))
			return -1;
	}
	if(-1 == poNetData->DelString(pstOut->hwid, sizeof(pstOut->hwid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeLoginAck(void* pHost, CNetData* poNetData)
{
	LoginAck* pstIn = (LoginAck*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->dbobjid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->errcode))
		return -1;

	if(-1 == poNetData->AddString(pstIn->errmsg, sizeof(pstIn->errmsg)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeLoginAck(void* pHost, CNetData* poNetData)
{
	LoginAck* pstOut = (LoginAck*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->dbobjid))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeLogoutRpt(void* pHost, CNetData* poNetData)
{
	LogoutRpt* pstIn = (LogoutRpt*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->info))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeLogoutRpt(void* pHost, CNetData* poNetData)
{
	LogoutRpt* pstOut = (LogoutRpt*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->info))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeCreateRoleReq(void* pHost, CNetData* poNetData)
{
	CreateRoleReq* pstIn = (CreateRoleReq*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == EnCodeROLE_BRIEF_INFO(&pstIn->createrole, poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeCreateRoleReq(void* pHost, CNetData* poNetData)
{
	CreateRoleReq* pstOut = (CreateRoleReq*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == DeCodeROLE_BRIEF_INFO(&pstOut->createrole, poNetData))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeCreateRoleAck(void* pHost, CNetData* poNetData)
{
	CreateRoleAck* pstIn = (CreateRoleAck*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->errcode))
		return -1;

	if(-1 == poNetData->AddString(pstIn->errmsg, sizeof(pstIn->errmsg)))
		return -1;

	if(-1 == EnCodeROLE_BRIEF_INFO(&pstIn->newrole, poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeCreateRoleAck(void* pHost, CNetData* poNetData)
{
	CreateRoleAck* pstOut = (CreateRoleAck*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	if(-1 == DeCodeROLE_BRIEF_INFO(&pstOut->newrole, poNetData))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeDeleteRoleReq(void* pHost, CNetData* poNetData)
{
	DeleteRoleReq* pstIn = (DeleteRoleReq*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeDeleteRoleReq(void* pHost, CNetData* poNetData)
{
	DeleteRoleReq* pstOut = (DeleteRoleReq*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeDeleteRoleAck(void* pHost, CNetData* poNetData)
{
	DeleteRoleAck* pstIn = (DeleteRoleAck*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->errcode))
		return -1;

	if(-1 == poNetData->AddString(pstIn->errmsg, sizeof(pstIn->errmsg)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeDeleteRoleAck(void* pHost, CNetData* poNetData)
{
	DeleteRoleAck* pstOut = (DeleteRoleAck*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeRecoverRoleReq(void* pHost, CNetData* poNetData)
{
	RecoverRoleReq* pstIn = (RecoverRoleReq*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeRecoverRoleReq(void* pHost, CNetData* poNetData)
{
	RecoverRoleReq* pstOut = (RecoverRoleReq*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeRecoverRoleAck(void* pHost, CNetData* poNetData)
{
	RecoverRoleAck* pstIn = (RecoverRoleAck*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->errcode))
		return -1;

	if(-1 == poNetData->AddString(pstIn->errmsg, sizeof(pstIn->errmsg)))
		return -1;

	if(-1 == EnCodeROLE_BRIEF_INFO(&pstIn->recoverrole, poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeRecoverRoleAck(void* pHost, CNetData* poNetData)
{
	RecoverRoleAck* pstOut = (RecoverRoleAck*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	if(-1 == DeCodeROLE_BRIEF_INFO(&pstOut->recoverrole, poNetData))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeGetRoleListReq(void* pHost, CNetData* poNetData)
{
	GetRoleListReq* pstIn = (GetRoleListReq*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeGetRoleListReq(void* pHost, CNetData* poNetData)
{
	GetRoleListReq* pstOut = (GetRoleListReq*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeGetRoleListAck(void* pHost, CNetData* poNetData)
{
	GetRoleListAck* pstIn = (GetRoleListAck*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->errcode))
		return -1;

	if(-1 == poNetData->AddString(pstIn->errmsg, sizeof(pstIn->errmsg)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->rolenum))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->last_role))
		return -1;

	for(int i = 0; i < 10; i++)
	{
		if(i >= (int)pstIn->rolenum)
			break;
		if(-1 == EnCodeROLE_BRIEF_INFO(&pstIn->rolelist[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeGetRoleListAck(void* pHost, CNetData* poNetData)
{
	GetRoleListAck* pstOut = (GetRoleListAck*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->rolenum))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->last_role))
		return -1;

	for(int i = 0; i < 10; i++)
	{
		if(i >= (int)pstOut->rolenum)
			break;
		if(-1 == DeCodeROLE_BRIEF_INFO(&pstOut->rolelist[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeKickUserNtf(void* pHost, CNetData* poNetData)
{
	KickUserNtf* pstIn = (KickUserNtf*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->errcode))
		return -1;

	if(-1 == poNetData->AddString(pstIn->errmsg, sizeof(pstIn->errmsg)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeKickUserNtf(void* pHost, CNetData* poNetData)
{
	KickUserNtf* pstOut = (KickUserNtf*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeRandKeyNtf(void* pHost, CNetData* poNetData)
{
	RandKeyNtf* pstIn = (RandKeyNtf*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->code_len))
		return -1;

	{
		int iCount = (((128) < ((int)pstIn->code_len)) ? (128) : ((int)pstIn->code_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->code, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeRandKeyNtf(void* pHost, CNetData* poNetData)
{
	RandKeyNtf* pstOut = (RandKeyNtf*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->code_len))
		return -1;

	{
		int iCount = (((128) < ((int)pstOut->code_len)) ? (128) : ((int)pstOut->code_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->code, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeReLoginReq(void* pHost, CNetData* poNetData)
{
	ReLoginReq* pstIn = (ReLoginReq*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->user_id))
		return -1;

	if(-1 == poNetData->AddString(pstIn->session_key, sizeof(pstIn->session_key)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeReLoginReq(void* pHost, CNetData* poNetData)
{
	ReLoginReq* pstOut = (ReLoginReq*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->user_id))
		return -1;

	if(-1 == poNetData->DelString(pstOut->session_key, sizeof(pstOut->session_key)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeReLoginAck(void* pHost, CNetData* poNetData)
{
	ReLoginAck* pstIn = (ReLoginAck*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->errcode))
		return -1;

	if(-1 == poNetData->AddString(pstIn->errmsg, sizeof(pstIn->errmsg)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeReLoginAck(void* pHost, CNetData* poNetData)
{
	ReLoginAck* pstOut = (ReLoginAck*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeLoginReq3rd(void* pHost, CNetData* poNetData)
{
	LoginReq3rd* pstIn = (LoginReq3rd*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->user_name, sizeof(pstIn->user_name)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->token_len))
		return -1;

	{
		int iCount = (((16384) < ((int)pstIn->token_len)) ? (16384) : ((int)pstIn->token_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->token, iCount*sizeof(unsigned char)))
			return -1;
	}
	if(-1 == poNetData->AddString(pstIn->platform, sizeof(pstIn->platform)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->login_ip))
		return -1;

	if(-1 == poNetData->AddString(pstIn->hwid, sizeof(pstIn->hwid)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeLoginReq3rd(void* pHost, CNetData* poNetData)
{
	LoginReq3rd* pstOut = (LoginReq3rd*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->user_name, sizeof(pstOut->user_name)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->token_len))
		return -1;

	{
		int iCount = (((16384) < ((int)pstOut->token_len)) ? (16384) : ((int)pstOut->token_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->token, iCount*sizeof(unsigned char)))
			return -1;
	}
	if(-1 == poNetData->DelString(pstOut->platform, sizeof(pstOut->platform)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->login_ip))
		return -1;

	if(-1 == poNetData->DelString(pstOut->hwid, sizeof(pstOut->hwid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeEncryptNtf(void* pHost, CNetData* poNetData)
{
	EncryptNtf* pstIn = (EncryptNtf*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->encode_len))
		return -1;

	{
		int iCount = (((4096) < ((int)pstIn->encode_len)) ? (4096) : ((int)pstIn->encode_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->encode_data, iCount*sizeof(unsigned char)))
			return -1;
	}
	if(-1 == poNetData->AddDword(pstIn->decode_len))
		return -1;

	{
		int iCount = (((4096) < ((int)pstIn->decode_len)) ? (4096) : ((int)pstIn->decode_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->decode_data, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeEncryptNtf(void* pHost, CNetData* poNetData)
{
	EncryptNtf* pstOut = (EncryptNtf*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->encode_len))
		return -1;

	{
		int iCount = (((4096) < ((int)pstOut->encode_len)) ? (4096) : ((int)pstOut->encode_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->encode_data, iCount*sizeof(unsigned char)))
			return -1;
	}
	if(-1 == poNetData->DelDword(pstOut->decode_len))
		return -1;

	{
		int iCount = (((4096) < ((int)pstOut->decode_len)) ? (4096) : ((int)pstOut->decode_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->decode_data, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeKickUserReq(void* pHost, CNetData* poNetData)
{
	KickUserReq* pstIn = (KickUserReq*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->user_id))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->errcode))
		return -1;

	if(-1 == poNetData->AddString(pstIn->errmsg, sizeof(pstIn->errmsg)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeKickUserReq(void* pHost, CNetData* poNetData)
{
	KickUserReq* pstOut = (KickUserReq*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->user_id))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeKickUserAck(void* pHost, CNetData* poNetData)
{
	KickUserAck* pstIn = (KickUserAck*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->user_id))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->errcode))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeKickUserAck(void* pHost, CNetData* poNetData)
{
	KickUserAck* pstOut = (KickUserAck*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->user_id))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeHeartBeatReq(void* pHost, CNetData* poNetData)
{
	HeartBeatReq* pstIn = (HeartBeatReq*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeHeartBeatReq(void* pHost, CNetData* poNetData)
{
	HeartBeatReq* pstOut = (HeartBeatReq*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeHeartBeatAck(void* pHost, CNetData* poNetData)
{
	HeartBeatAck* pstIn = (HeartBeatAck*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeHeartBeatAck(void* pHost, CNetData* poNetData)
{
	HeartBeatAck* pstOut = (HeartBeatAck*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeClientTypeNtf(void* pHost, CNetData* poNetData)
{
	ClientTypeNtf* pstIn = (ClientTypeNtf*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeClientTypeNtf(void* pHost, CNetData* poNetData)
{
	ClientTypeNtf* pstOut = (ClientTypeNtf*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeGTLoginReq(void* pHost, CNetData* poNetData)
{
	GTLoginReq* pstIn = (GTLoginReq*)pHost;

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->UserName, sizeof(pstIn->UserName)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->ip))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->pwd_len))
		return -1;

	{
		int iCount = (((128) < ((int)pstIn->pwd_len)) ? (128) : ((int)pstIn->pwd_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->password, iCount*sizeof(unsigned char)))
			return -1;
	}
	if(-1 == poNetData->AddString(pstIn->hwid, sizeof(pstIn->hwid)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->platform, sizeof(pstIn->platform)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->platform_info, sizeof(pstIn->platform_info)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeGTLoginReq(void* pHost, CNetData* poNetData)
{
	GTLoginReq* pstOut = (GTLoginReq*)pHost;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->moudleid))
		return -1;

	if(-1==poNetData->DelWord((unsigned short&)pstOut->protocolid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->UserName, sizeof(pstOut->UserName)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->ip))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->pwd_len))
		return -1;

	{
		int iCount = (((128) < ((int)pstOut->pwd_len)) ? (128) : ((int)pstOut->pwd_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->password, iCount*sizeof(unsigned char)))
			return -1;
	}
	if(-1 == poNetData->DelString(pstOut->hwid, sizeof(pstOut->hwid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->platform, sizeof(pstOut->platform)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->platform_info, sizeof(pstOut->platform_info)))
		return -1;

	return sizeof(*pstOut);
}

CClientDB::CClientDB()
{
	m_EnCodeFuncArray[0] = &EnCodeLoginReq;
	m_DeCodeFuncArray[0] = &DeCodeLoginReq;

	m_EnCodeFuncArray[1] = &EnCodeLoginAck;
	m_DeCodeFuncArray[1] = &DeCodeLoginAck;

	m_EnCodeFuncArray[2] = &EnCodeLogoutRpt;
	m_DeCodeFuncArray[2] = &DeCodeLogoutRpt;

	m_EnCodeFuncArray[3] = &EnCodeCreateRoleReq;
	m_DeCodeFuncArray[3] = &DeCodeCreateRoleReq;

	m_EnCodeFuncArray[4] = &EnCodeCreateRoleAck;
	m_DeCodeFuncArray[4] = &DeCodeCreateRoleAck;

	m_EnCodeFuncArray[5] = &EnCodeDeleteRoleReq;
	m_DeCodeFuncArray[5] = &DeCodeDeleteRoleReq;

	m_EnCodeFuncArray[6] = &EnCodeDeleteRoleAck;
	m_DeCodeFuncArray[6] = &DeCodeDeleteRoleAck;

	m_EnCodeFuncArray[7] = &EnCodeRecoverRoleReq;
	m_DeCodeFuncArray[7] = &DeCodeRecoverRoleReq;

	m_EnCodeFuncArray[8] = &EnCodeRecoverRoleAck;
	m_DeCodeFuncArray[8] = &DeCodeRecoverRoleAck;

	m_EnCodeFuncArray[9] = &EnCodeGetRoleListReq;
	m_DeCodeFuncArray[9] = &DeCodeGetRoleListReq;

	m_EnCodeFuncArray[10] = &EnCodeGetRoleListAck;
	m_DeCodeFuncArray[10] = &DeCodeGetRoleListAck;

	m_EnCodeFuncArray[11] = &EnCodeKickUserNtf;
	m_DeCodeFuncArray[11] = &DeCodeKickUserNtf;

	m_EnCodeFuncArray[12] = &EnCodeRandKeyNtf;
	m_DeCodeFuncArray[12] = &DeCodeRandKeyNtf;

	m_EnCodeFuncArray[13] = &EnCodeReLoginReq;
	m_DeCodeFuncArray[13] = &DeCodeReLoginReq;

	m_EnCodeFuncArray[14] = &EnCodeReLoginAck;
	m_DeCodeFuncArray[14] = &DeCodeReLoginAck;

	m_EnCodeFuncArray[15] = &EnCodeLoginReq3rd;
	m_DeCodeFuncArray[15] = &DeCodeLoginReq3rd;

	m_EnCodeFuncArray[16] = &EnCodeEncryptNtf;
	m_DeCodeFuncArray[16] = &DeCodeEncryptNtf;

	m_EnCodeFuncArray[17] = &EnCodeKickUserReq;
	m_DeCodeFuncArray[17] = &DeCodeKickUserReq;

	m_EnCodeFuncArray[18] = &EnCodeKickUserAck;
	m_DeCodeFuncArray[18] = &DeCodeKickUserAck;

	m_EnCodeFuncArray[19] = &EnCodeHeartBeatReq;
	m_DeCodeFuncArray[19] = &DeCodeHeartBeatReq;

	m_EnCodeFuncArray[20] = &EnCodeHeartBeatAck;
	m_DeCodeFuncArray[20] = &DeCodeHeartBeatAck;

	m_EnCodeFuncArray[21] = &EnCodeClientTypeNtf;
	m_DeCodeFuncArray[21] = &DeCodeClientTypeNtf;

	m_EnCodeFuncArray[22] = &EnCodeGTLoginReq;
	m_DeCodeFuncArray[22] = &DeCodeGTLoginReq;

}

CClientDB::~CClientDB()
{
}

int CClientDB::BuildProtocol(void* pHost, char *pNet, int iNetSize)
{
	CNetData m_oData;
	m_oData.Prepare(pNet, iNetSize);
	if (*(unsigned short*)pHost != 1)
	{
		return -1;
	}
	if (*(unsigned short*)((char*)pHost+sizeof(unsigned short)) >= sizeof(m_EnCodeFuncArray)/sizeof(EnCodeFuncClientDB))
	{
		return -1;
	}
	return m_EnCodeFuncArray[*(unsigned short*)((char*)pHost+sizeof(unsigned short))](pHost, &m_oData);
}

bool CClientDB::HandleProtocol(char *pNet, int iNetSize, void* pHost)
{
	CNetData m_oData;
	m_oData.Prepare(pNet, iNetSize);

	unsigned short moudleid = 0;
	unsigned short protocolid = 0;
	if (m_oData.DelWord(moudleid) < 0)
	{
		return false;
	}
	if (moudleid != 1)
	{
		return false;
	}
	if (m_oData.DelWord(protocolid) < 0)
	{
		return false;
	}
	if (protocolid >= sizeof(m_DeCodeFuncArray)/sizeof(DeCodeFuncClientDB))
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
		OnRecv_LoginReq(*(LoginReq*)pHost);
		break;
	case 1:
		OnRecv_LoginAck(*(LoginAck*)pHost);
		break;
	case 2:
		OnRecv_LogoutRpt(*(LogoutRpt*)pHost);
		break;
	case 3:
		OnRecv_CreateRoleReq(*(CreateRoleReq*)pHost);
		break;
	case 4:
		OnRecv_CreateRoleAck(*(CreateRoleAck*)pHost);
		break;
	case 5:
		OnRecv_DeleteRoleReq(*(DeleteRoleReq*)pHost);
		break;
	case 6:
		OnRecv_DeleteRoleAck(*(DeleteRoleAck*)pHost);
		break;
	case 7:
		OnRecv_RecoverRoleReq(*(RecoverRoleReq*)pHost);
		break;
	case 8:
		OnRecv_RecoverRoleAck(*(RecoverRoleAck*)pHost);
		break;
	case 9:
		OnRecv_GetRoleListReq(*(GetRoleListReq*)pHost);
		break;
	case 10:
		OnRecv_GetRoleListAck(*(GetRoleListAck*)pHost);
		break;
	case 11:
		OnRecv_KickUserNtf(*(KickUserNtf*)pHost);
		break;
	case 12:
		OnRecv_RandKeyNtf(*(RandKeyNtf*)pHost);
		break;
	case 13:
		OnRecv_ReLoginReq(*(ReLoginReq*)pHost);
		break;
	case 14:
		OnRecv_ReLoginAck(*(ReLoginAck*)pHost);
		break;
	case 15:
		OnRecv_LoginReq3rd(*(LoginReq3rd*)pHost);
		break;
	case 16:
		OnRecv_EncryptNtf(*(EncryptNtf*)pHost);
		break;
	case 17:
		OnRecv_KickUserReq(*(KickUserReq*)pHost);
		break;
	case 18:
		OnRecv_KickUserAck(*(KickUserAck*)pHost);
		break;
	case 19:
		OnRecv_HeartBeatReq(*(HeartBeatReq*)pHost);
		break;
	case 20:
		OnRecv_HeartBeatAck(*(HeartBeatAck*)pHost);
		break;
	case 21:
		OnRecv_ClientTypeNtf(*(ClientTypeNtf*)pHost);
		break;
	case 22:
		OnRecv_GTLoginReq(*(GTLoginReq*)pHost);
		break;
	default:
		return false;
	}

	return true;
}

