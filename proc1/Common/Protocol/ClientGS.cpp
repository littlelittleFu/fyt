#include "stdafx.h"
#include "ClientGS.hpp"

int EnCodeEnterGSReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<EnterGSReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->entertype))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->roleguid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->fangchenmi))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeEnterGSReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<EnterGSReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->entertype))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->roleguid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->fangchenmi))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeEnterGSAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<EnterGSAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->entertype))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->roleguid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->gsobjid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->errcode))
		return -1;

	if(-1 == poNetData->AddString(pstIn->errmsg, sizeof(pstIn->errmsg)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeEnterGSAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<EnterGSAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->entertype))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->roleguid))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->gsobjid))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeExitGSReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ExitGSReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->exittype))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeExitGSReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ExitGSReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->exittype))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeExitGSAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ExitGSAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->exittype))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->errcode))
		return -1;

	if(-1 == poNetData->AddString(pstIn->errmsg, sizeof(pstIn->errmsg)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeExitGSAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ExitGSAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->exittype))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeJumpGSNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<JumpGSNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->jumptype))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->gssvrid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->mapcode))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeJumpGSNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<JumpGSNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->jumptype))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->gssvrid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->mapcode))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeKickRoleNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<KickRoleNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->roleguid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->errcode))
		return -1;

	if(-1 == poNetData->AddString(pstIn->errmsg, sizeof(pstIn->errmsg)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeKickRoleNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<KickRoleNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->roleguid))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeEnterMapNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<EnterMapNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->mapcode))
		return -1;

	if(-1 == poNetData->AddString(pstIn->logic, sizeof(pstIn->logic)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->view_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->view_y))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->width))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->height))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeEnterMapNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<EnterMapNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->mapcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->logic, sizeof(pstOut->logic)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->view_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->view_y))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->width))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->height))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMapRegionNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MapRegionNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->mapcode))
		return -1;

	if(-1 == poNetData->AddString(pstIn->logic, sizeof(pstIn->logic)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->rg_num))
		return -1;

	for(int i = 0; i < 255; i++)
	{
		if(i >= (int)pstIn->rg_num)
			break;
		if(-1 == EnCodeMAP_REGION_INFO(&pstIn->rg_info[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeMapRegionNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MapRegionNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->mapcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->logic, sizeof(pstOut->logic)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->rg_num))
		return -1;

	for(int i = 0; i < 255; i++)
	{
		if(i >= (int)pstOut->rg_num)
			break;
		if(-1 == DeCodeMAP_REGION_INFO(&pstOut->rg_info[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeSetRelivePT(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SetRelivePT*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSetRelivePT(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SetRelivePT*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePlayerReliveReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PlayerReliveReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->relive_type))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodePlayerReliveReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PlayerReliveReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->relive_type))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePlayerReliveAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PlayerReliveAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->relive_type))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->error_code))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodePlayerReliveAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PlayerReliveAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->relive_type))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->error_code))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePlayerAppearNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PlayerAppearNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->gender))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->job))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->status))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->head))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->level))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_y))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->dir))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->hair))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->hair_color))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->body))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->weapon))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->wings))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->mount))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->weapon_effect))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->body_effect))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->mount_effect))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->hp))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->max_hp))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->mp))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->max_mp))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->pk))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->move_speed))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->attack_speed))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->title))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->has_team))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->stall))
		return -1;

	if(-1 == poNetData->AddString(pstIn->stall_name, sizeof(pstIn->stall_name)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->buff_num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstIn->buff_num)
			break;
		if(-1 == EnCodeBUFF_INFO(&pstIn->buffs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddString(pstIn->family_name, sizeof(pstIn->family_name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->castle_name, sizeof(pstIn->castle_name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->family_title, sizeof(pstIn->family_title)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->alias, sizeof(pstIn->alias)))
		return -1;

	if(-1 == EnCodeCUSTOM_INFO(&pstIn->custom, poNetData))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->appear_type))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->amulet))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodePlayerAppearNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PlayerAppearNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->gender))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->job))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->status))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->head))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->level))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_y))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->dir))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->hair))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->hair_color))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->body))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->weapon))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->wings))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->mount))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->weapon_effect))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->body_effect))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->mount_effect))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->hp))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->max_hp))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->mp))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->max_mp))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->pk))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->move_speed))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->attack_speed))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->title))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->has_team))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->stall))
		return -1;

	if(-1 == poNetData->DelString(pstOut->stall_name, sizeof(pstOut->stall_name)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->buff_num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstOut->buff_num)
			break;
		if(-1 == DeCodeBUFF_INFO(&pstOut->buffs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelString(pstOut->family_name, sizeof(pstOut->family_name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->castle_name, sizeof(pstOut->castle_name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->family_title, sizeof(pstOut->family_title)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->alias, sizeof(pstOut->alias)))
		return -1;

	if(-1 == DeCodeCUSTOM_INFO(&pstOut->custom, poNetData))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->appear_type))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->amulet))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMonsterAppearNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MonsterAppearNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->monster_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->template_id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_y))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->dir))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->cur_hp))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->max_hp))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->status))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->servant_lv))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->move_speed))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->buff_num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstIn->buff_num)
			break;
		if(-1 == EnCodeBUFF_INFO(&pstIn->buffs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddString(pstIn->master_name, sizeof(pstIn->master_name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->appear_type))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMonsterAppearNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MonsterAppearNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->monster_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->template_id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_y))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->dir))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->cur_hp))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->max_hp))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->status))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->servant_lv))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->move_speed))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->buff_num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstOut->buff_num)
			break;
		if(-1 == DeCodeBUFF_INFO(&pstOut->buffs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelString(pstOut->master_name, sizeof(pstOut->master_name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->appear_type))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemAppearNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemAppearNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->template_id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_y))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->skill_id))
		return -1;

	if(-1 == poNetData->AddString(pstIn->item_name, sizeof(pstIn->item_name)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemAppearNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemAppearNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->template_id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_y))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->skill_id))
		return -1;

	if(-1 == poNetData->DelString(pstOut->item_name, sizeof(pstOut->item_name)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeNPCAppearNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<NPCAppearNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->npc_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->template_id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_y))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->dir))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeNPCAppearNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<NPCAppearNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->npc_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->template_id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_y))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->dir))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeObjDisappearNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ObjDisappearNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->obj_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeObjDisappearNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ObjDisappearNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->obj_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePlayerCreate(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PlayerCreate*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->sex))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->head))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->hair))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->hair_color))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->level))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->exp))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodePlayerCreate(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PlayerCreate*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->sex))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->head))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->hair))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->hair_color))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->level))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->exp))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMoveReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MoveReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_y))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->idx))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMoveReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MoveReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_y))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->idx))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMoveNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MoveNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_y))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMoveNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MoveNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_y))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMoveAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MoveAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->ret))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_y))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->idx))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMoveAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MoveAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->ret))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_y))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->idx))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTurnReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TurnReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->dir))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTurnReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TurnReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->dir))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTurnNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TurnNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->dir))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTurnNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TurnNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->dir))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTurnAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TurnAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->ret))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->dir))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTurnAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TurnAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->ret))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->dir))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeObjDieNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ObjDieNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->die_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->kill_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->kill_name, sizeof(pstIn->kill_name)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeObjDieNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ObjDieNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->die_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->kill_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->kill_name, sizeof(pstOut->kill_name)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeChatReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ChatReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == poNetData->AddString(pstIn->sender, sizeof(pstIn->sender)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->text, sizeof(pstIn->text)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeChatReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ChatReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == poNetData->DelString(pstOut->sender, sizeof(pstOut->sender)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->text, sizeof(pstOut->text)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeGMCommandReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GMCommandReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->cmd, sizeof(pstIn->cmd)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->param, sizeof(pstIn->param)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeGMCommandReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GMCommandReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->cmd, sizeof(pstOut->cmd)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->param, sizeof(pstOut->param)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeRoleAppNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<RoleAppNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->hair))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->hair_color))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->body))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->weapon))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->wings))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->mount))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->weapon_effect))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->body_effect))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->mount_effect))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->amulet))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeRoleAppNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<RoleAppNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->hair))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->hair_color))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->body))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->weapon))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->wings))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->mount))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->weapon_effect))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->body_effect))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->mount_effect))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->amulet))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeRoleAttrNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<RoleAttrNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->role_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->num))
		return -1;

	{
		int iCount = (((100) < ((int)pstIn->num)) ? (100) : ((int)pstIn->num));
		if(-1 == poNetData->AddBlob((char*)pstIn->attr_name, iCount*sizeof(unsigned short)))
			return -1;
	}
	{
		int iCount = (((100) < ((int)pstIn->num)) ? (100) : ((int)pstIn->num));
		if(-1 == poNetData->AddBlob((char*)pstIn->attr_value, iCount*sizeof(int)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeRoleAttrNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<RoleAttrNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->role_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->num))
		return -1;

	{
		int iCount = (((100) < ((int)pstOut->num)) ? (100) : ((int)pstOut->num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->attr_name, iCount*sizeof(unsigned short)))
			return -1;
	}
	{
		int iCount = (((100) < ((int)pstOut->num)) ? (100) : ((int)pstOut->num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->attr_value, iCount*sizeof(int)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeRoleAttrExtNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<RoleAttrExtNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->num))
		return -1;

	{
		int iCount = (((20) < ((int)pstIn->num)) ? (20) : ((int)pstIn->num));
		if(-1 == poNetData->AddBlob((char*)pstIn->attr_name, iCount*sizeof(unsigned short)))
			return -1;
	}
	{
		int iCount = (((20) < ((int)pstIn->num)) ? (20) : ((int)pstIn->num));
		if(-1 == poNetData->AddBlob((char*)pstIn->attr_value, iCount*sizeof(int64_t)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeRoleAttrExtNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<RoleAttrExtNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->num))
		return -1;

	{
		int iCount = (((20) < ((int)pstOut->num)) ? (20) : ((int)pstOut->num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->attr_name, iCount*sizeof(unsigned short)))
			return -1;
	}
	{
		int iCount = (((20) < ((int)pstOut->num)) ? (20) : ((int)pstOut->num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->attr_value, iCount*sizeof(int64_t)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeTeamMemberNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TeamMemberNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->member_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->y))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTeamMemberNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TeamMemberNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->member_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->y))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeShowFormNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ShowFormNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->form_name, sizeof(pstIn->form_name)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->size))
		return -1;

	{
		int iCount = (((7900) < ((int)pstIn->size)) ? (7900) : ((int)pstIn->size));
		if(-1 == poNetData->AddBlob((char*)pstIn->form_content, iCount*sizeof(char)))
			return -1;
	}
	if(-1 == poNetData->AddChar(pstIn->comp))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeShowFormNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ShowFormNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->form_name, sizeof(pstOut->form_name)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->size))
		return -1;

	{
		int iCount = (((7900) < ((int)pstOut->size)) ? (7900) : ((int)pstOut->size));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->form_content, iCount*sizeof(char)))
			return -1;
	}
	if(-1 == poNetData->DelChar(pstOut->comp))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSubmitForm(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SubmitForm*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->script_name, sizeof(pstIn->script_name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->function_name, sizeof(pstIn->function_name)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstIn->num)
			break;
		if(-1 == EnCodePARAM_INFO(&pstIn->info[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeSubmitForm(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SubmitForm*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->script_name, sizeof(pstOut->script_name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->function_name, sizeof(pstOut->function_name)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstOut->num)
			break;
		if(-1 == DeCodePARAM_INFO(&pstOut->info[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeItemAddReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemAddReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_id))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->item_amount))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->is_bind))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemAddReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemAddReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_id))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->item_amount))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->is_bind))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemAddAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemAddAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == EnCodeITEM_INFO(&pstIn->info, poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemAddAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemAddAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == DeCodeITEM_INFO(&pstOut->info, poNetData))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemDestroyReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemDestroyReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemDestroyReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemDestroyReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemDestroyAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemDestroyAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemDestroyAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemDestroyAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemMove(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemMove*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dest_site))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemMove(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemMove*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dest_site))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemSplit(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemSplit*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_amount))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dest_site))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemSplit(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemSplit*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_amount))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dest_site))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemAttrNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemAttrNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->attr_name))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->attr_value))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemAttrNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemAttrNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->attr_name))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->attr_value))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemUpdateNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemUpdateNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == EnCodeITEM_INFO(&pstIn->info, poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemUpdateNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemUpdateNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == DeCodeITEM_INFO(&pstOut->info, poNetData))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemBind(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemBind*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemBind(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemBind*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemApply(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemApply*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemApply(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemApply*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemApplyOnTarget(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemApplyOnTarget*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->target))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemApplyOnTarget(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemApplyOnTarget*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->target))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemApplyOnGrid(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemApplyOnGrid*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->target_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->target_y))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemApplyOnGrid(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemApplyOnGrid*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->target_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->target_y))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemArrange(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemArrange*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemArrange(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemArrange*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemPickUp(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemPickUp*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemPickUp(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemPickUp*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemDrop(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemDrop*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemDrop(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemDrop*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemTieUp(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemTieUp*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemTieUp(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemTieUp*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemTip(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemTip*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->owner_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemTip(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemTip*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->owner_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemTipBrd(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemTipBrd*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->owner_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->target_userid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemTipBrd(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemTipBrd*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->owner_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->target_userid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemTipNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemTipNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == EnCodeITEM_INFO(&pstIn->info, poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemTipNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemTipNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == DeCodeITEM_INFO(&pstOut->info, poNetData))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemEnhance(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemEnhance*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->items_num))
		return -1;

	{
		int iCount = (((100) < ((int)pstIn->items_num)) ? (100) : ((int)pstIn->items_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->items_info, iCount*sizeof(uint64_t)))
			return -1;
	}
	if(-1 == poNetData->AddWord(pstIn->materials_num))
		return -1;

	{
		int iCount = (((100) < ((int)pstIn->materials_num)) ? (100) : ((int)pstIn->materials_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->materials_info, iCount*sizeof(uint64_t)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeItemEnhance(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemEnhance*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->items_num))
		return -1;

	{
		int iCount = (((100) < ((int)pstOut->items_num)) ? (100) : ((int)pstOut->items_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->items_info, iCount*sizeof(uint64_t)))
			return -1;
	}
	if(-1 == poNetData->DelWord(pstOut->materials_num))
		return -1;

	{
		int iCount = (((100) < ((int)pstOut->materials_num)) ? (100) : ((int)pstOut->materials_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->materials_info, iCount*sizeof(uint64_t)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeItemDrill(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemDrill*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->material_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemDrill(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemDrill*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->material_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemSynthesis(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemSynthesis*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->material_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->gems_num))
		return -1;

	{
		int iCount = (((5) < ((int)pstIn->gems_num)) ? (5) : ((int)pstIn->gems_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->gems_info, iCount*sizeof(uint64_t)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeItemSynthesis(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemSynthesis*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->material_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->gems_num))
		return -1;

	{
		int iCount = (((5) < ((int)pstOut->gems_num)) ? (5) : ((int)pstOut->gems_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->gems_info, iCount*sizeof(uint64_t)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeItemEmbed(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemEmbed*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->material_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->gem_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemEmbed(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemEmbed*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->material_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->gem_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemDig(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemDig*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->material_guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->slot))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemDig(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemDig*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->material_guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->slot))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemIdentify(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemIdentify*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->material_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemIdentify(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemIdentify*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->material_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemRename(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemRename*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->new_name, sizeof(pstIn->new_name)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemRename(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemRename*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->new_name, sizeof(pstOut->new_name)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemRefine(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemRefine*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->material_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->lucky_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemRefine(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemRefine*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->material_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->lucky_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemRepairQuery(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemRepairQuery*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemRepairQuery(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemRepairQuery*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemRepairQueryNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemRepairQueryNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->gold))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemRepairQueryNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemRepairQueryNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->gold))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemRepair(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemRepair*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemRepair(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemRepair*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemSeg(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemSeg*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->begin_site))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->end_site))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemSeg(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemSeg*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->begin_site))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->end_site))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSkillAddReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SkillAddReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSkillAddReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SkillAddReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSkillAddAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SkillAddAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstIn->num)
			break;
		if(-1 == EnCodeSKILL_INFO(&pstIn->info[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeSkillAddAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SkillAddAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstOut->num)
			break;
		if(-1 == DeCodeSKILL_INFO(&pstOut->info[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeSkillDestroyReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SkillDestroyReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSkillDestroyReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SkillDestroyReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSkillDestroyAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SkillDestroyAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSkillDestroyAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SkillDestroyAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSkillSwitch(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SkillSwitch*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->active))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSkillSwitch(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SkillSwitch*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->active))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSkillSwitchAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SkillSwitchAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->active))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSkillSwitchAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SkillSwitchAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->active))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSkillProficiencyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SkillProficiencyNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->proficiency))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSkillProficiencyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SkillProficiencyNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->proficiency))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeBuffAddAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<BuffAddAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->role_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstIn->num)
			break;
		if(-1 == EnCodeBUFF_INFO(&pstIn->info[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeBuffAddAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<BuffAddAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->role_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstOut->num)
			break;
		if(-1 == DeCodeBUFF_INFO(&pstOut->info[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeBuffDestroyReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<BuffDestroyReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeBuffDestroyReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<BuffDestroyReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeBuffDestroyAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<BuffDestroyAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->role_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeBuffDestroyAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<BuffDestroyAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->role_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeBuffUpdateNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<BuffUpdateNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->role_guid))
		return -1;

	if(-1 == EnCodeBUFF_INFO(&pstIn->info, poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeBuffUpdateNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<BuffUpdateNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->role_guid))
		return -1;

	if(-1 == DeCodeBUFF_INFO(&pstOut->info, poNetData))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSpellTargetReadyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SpellTargetReadyNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->actor))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->target))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSpellTargetReadyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SpellTargetReadyNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->actor))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->target))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSpellGridReadyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SpellGridReadyNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->actor))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->target_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->target_y))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSpellGridReadyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SpellGridReadyNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->actor))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->target_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->target_y))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSpellTarget(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SpellTarget*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->target))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->idx))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSpellTarget(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SpellTarget*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->target))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->idx))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSpellGrid(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SpellGrid*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->target_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->target_y))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->idx))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->ref_target))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSpellGrid(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SpellGrid*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->target_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->target_y))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->idx))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->ref_target))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSpellAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SpellAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->ecode))
		return -1;

	if(-1 == poNetData->AddString(pstIn->detail, sizeof(pstIn->detail)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->idx))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSpellAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SpellAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->ecode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->detail, sizeof(pstOut->detail)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->idx))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSpellNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SpellNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->actor))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->target_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->target_y))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->num))
		return -1;

	{
		int iCount = (((50) < ((int)pstIn->num)) ? (50) : ((int)pstIn->num));
		if(-1 == poNetData->AddBlob((char*)pstIn->targets, iCount*sizeof(uint64_t)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeSpellNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SpellNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->actor))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->target_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->target_y))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->num))
		return -1;

	{
		int iCount = (((50) < ((int)pstOut->num)) ? (50) : ((int)pstOut->num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->targets, iCount*sizeof(uint64_t)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeAttrShowNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<AttrShowNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->actor))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->skill_id))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->target))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->actor_hp_ref))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->target_hp_ref))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->target_hp))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeAttrShowNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<AttrShowNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->actor))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->skill_id))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->target))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->actor_hp_ref))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->target_hp_ref))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->target_hp))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMissNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MissNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->actor))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->target))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->skill_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMissNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MissNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->actor))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->target))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->skill_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSpellDelayLostNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SpellDelayLostNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->actor))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->skill_id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->target_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->target_y))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSpellDelayLostNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SpellDelayLostNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->actor))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->skill_id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->target_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->target_y))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSpellDelayHitNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SpellDelayHitNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->actor))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->skill_id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->num))
		return -1;

	{
		int iCount = (((50) < ((int)pstIn->num)) ? (50) : ((int)pstIn->num));
		if(-1 == poNetData->AddBlob((char*)pstIn->targets, iCount*sizeof(uint64_t)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeSpellDelayHitNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SpellDelayHitNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->actor))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->skill_id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->num))
		return -1;

	{
		int iCount = (((50) < ((int)pstOut->num)) ? (50) : ((int)pstOut->num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->targets, iCount*sizeof(uint64_t)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeTradeNpcBuy(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeNpcBuy*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->shop_id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_index))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_amount))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->is_bind))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeNpcBuy(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeNpcBuy*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->shop_id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_index))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_amount))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->is_bind))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeNpcSell(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeNpcSell*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeNpcSell(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeNpcSell*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeNpcValueReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeNpcValueReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeNpcValueReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeNpcValueReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeNpcValueAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeNpcValueAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->value))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeNpcValueAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeNpcValueAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->value))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeNpcShopNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeNpcShopNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->shop_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->item_count))
		return -1;

	for(int i = 0; i < 250; i++)
	{
		if(i >= (int)pstIn->item_count)
			break;
		if(-1 == EnCodeSHOP_ITEM_INFO(&pstIn->item_list[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeTradeNpcShopNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeNpcShopNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->shop_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->item_count))
		return -1;

	for(int i = 0; i < 250; i++)
	{
		if(i >= (int)pstOut->item_count)
			break;
		if(-1 == DeCodeSHOP_ITEM_INFO(&pstOut->item_list[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeTradeP2PRequest(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeP2PRequest*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->responsor))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeP2PRequest(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeP2PRequest*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->responsor))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeP2PRequestNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeP2PRequestNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->requestor))
		return -1;

	if(-1 == poNetData->AddString(pstIn->requestor_name, sizeof(pstIn->requestor_name)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeP2PRequestNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeP2PRequestNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->requestor))
		return -1;

	if(-1 == poNetData->DelString(pstOut->requestor_name, sizeof(pstOut->requestor_name)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeP2PResponse(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeP2PResponse*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->requestor))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->accepted))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeP2PResponse(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeP2PResponse*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->requestor))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->accepted))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeP2POpenNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeP2POpenNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->requestor))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->responsor))
		return -1;

	if(-1 == poNetData->AddString(pstIn->requestor_name, sizeof(pstIn->requestor_name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->responsor_name, sizeof(pstIn->responsor_name)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeP2POpenNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeP2POpenNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->requestor))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->responsor))
		return -1;

	if(-1 == poNetData->DelString(pstOut->requestor_name, sizeof(pstOut->requestor_name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->responsor_name, sizeof(pstOut->responsor_name)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeP2PArrange(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeP2PArrange*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->remove))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeP2PArrange(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeP2PArrange*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->remove))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeP2PArrangeNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeP2PArrangeNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->remove))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_num))
		return -1;

	for(int i = 0; i < 1; i++)
	{
		if(i >= (int)pstIn->item_num)
			break;
		if(-1 == EnCodeITEM_INFO(&pstIn->item_info[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeTradeP2PArrangeNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeP2PArrangeNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->remove))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_num))
		return -1;

	for(int i = 0; i < 1; i++)
	{
		if(i >= (int)pstOut->item_num)
			break;
		if(-1 == DeCodeITEM_INFO(&pstOut->item_info[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeTradeP2PGold(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeP2PGold*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt64(pstIn->gold))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeP2PGold(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeP2PGold*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt64(pstOut->gold))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeP2PGoldNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeP2PGoldNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddInt64(pstIn->gold))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeP2PGoldNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeP2PGoldNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelInt64(pstOut->gold))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeP2PLock(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeP2PLock*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->locked))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeP2PLock(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeP2PLock*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->locked))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeP2PLockNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeP2PLockNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->locked))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeP2PLockNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeP2PLockNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->locked))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeP2PConfirme(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeP2PConfirme*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeP2PConfirme(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeP2PConfirme*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeP2PConfirmeNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeP2PConfirmeNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->confirmed))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeP2PConfirmeNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeP2PConfirmeNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->confirmed))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeP2PClose(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeP2PClose*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeP2PClose(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeP2PClose*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeP2PCloseNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeP2PCloseNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeP2PCloseNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeP2PCloseNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeStallReady(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeStallReady*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeStallReady(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeStallReady*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeStallReadyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeStallReadyNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeStallReadyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeStallReadyNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeStall(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeStall*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->stall_name, sizeof(pstIn->stall_name)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_num))
		return -1;

	{
		int iCount = (((25) < ((int)pstIn->item_num)) ? (25) : ((int)pstIn->item_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->item_guids, iCount*sizeof(uint64_t)))
			return -1;
	}
	{
		int iCount = (((25) < ((int)pstIn->item_num)) ? (25) : ((int)pstIn->item_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->price_types, iCount*sizeof(unsigned char)))
			return -1;
	}
	{
		int iCount = (((25) < ((int)pstIn->item_num)) ? (25) : ((int)pstIn->item_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->item_prices, iCount*sizeof(int64_t)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeTradeStall(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeStall*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->stall_name, sizeof(pstOut->stall_name)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_num))
		return -1;

	{
		int iCount = (((25) < ((int)pstOut->item_num)) ? (25) : ((int)pstOut->item_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->item_guids, iCount*sizeof(uint64_t)))
			return -1;
	}
	{
		int iCount = (((25) < ((int)pstOut->item_num)) ? (25) : ((int)pstOut->item_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->price_types, iCount*sizeof(unsigned char)))
			return -1;
	}
	{
		int iCount = (((25) < ((int)pstOut->item_num)) ? (25) : ((int)pstOut->item_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->item_prices, iCount*sizeof(int64_t)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeTradeStallNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeStallNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->stall_name, sizeof(pstIn->stall_name)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeStallNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeStallNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->stall_name, sizeof(pstOut->stall_name)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeStallArrange(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeStallArrange*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeStallArrange(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeStallArrange*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeStallQuery(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeStallQuery*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeStallQuery(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeStallQuery*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeStallQueryNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeStallQueryNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->stall_name, sizeof(pstIn->stall_name)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_num))
		return -1;

	{
		int iCount = (((25) < ((int)pstIn->item_num)) ? (25) : ((int)pstIn->item_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->item_prices, iCount*sizeof(int64_t)))
			return -1;
	}
	{
		int iCount = (((25) < ((int)pstIn->item_num)) ? (25) : ((int)pstIn->item_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->price_types, iCount*sizeof(unsigned char)))
			return -1;
	}
	for(int i = 0; i < 25; i++)
	{
		if(i >= (int)pstIn->item_num)
			break;
		if(-1 == EnCodeITEM_INFO(&pstIn->item_info[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeTradeStallQueryNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeStallQueryNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->stall_name, sizeof(pstOut->stall_name)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_num))
		return -1;

	{
		int iCount = (((25) < ((int)pstOut->item_num)) ? (25) : ((int)pstOut->item_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->item_prices, iCount*sizeof(int64_t)))
			return -1;
	}
	{
		int iCount = (((25) < ((int)pstOut->item_num)) ? (25) : ((int)pstOut->item_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->price_types, iCount*sizeof(unsigned char)))
			return -1;
	}
	for(int i = 0; i < 25; i++)
	{
		if(i >= (int)pstOut->item_num)
			break;
		if(-1 == DeCodeITEM_INFO(&pstOut->item_info[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeTradeStallBuy(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeStallBuy*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_amount))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeStallBuy(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeStallBuy*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_amount))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeStallBuyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeStallBuyNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->buyer_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->seller_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_amount))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->price_type))
		return -1;

	if(-1 == poNetData->AddInt64(pstIn->price))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeStallBuyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeStallBuyNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->buyer_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->seller_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_amount))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->price_type))
		return -1;

	if(-1 == poNetData->DelInt64(pstOut->price))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeStallClose(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeStallClose*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeStallClose(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeStallClose*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeStallCloseNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeStallCloseNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeStallCloseNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeStallCloseNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePlayerSwitch(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PlayerSwitch*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->value))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodePlayerSwitch(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PlayerSwitch*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->value))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeAtkModeReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<AtkModeReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->atk_mode))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeAtkModeReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<AtkModeReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->atk_mode))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeServantModeReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ServantModeReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeServantModeReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ServantModeReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeRoleAddPoint(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<RoleAddPoint*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->hp))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->mp))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->phy_atk))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->mag_atk))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->tao_atk))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->phy_def))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->mag_def))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeRoleAddPoint(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<RoleAddPoint*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->hp))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->mp))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->phy_atk))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->mag_atk))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->tao_atk))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->phy_def))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->mag_def))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeLevelUpNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<LevelUpNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->level))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeLevelUpNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<LevelUpNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->level))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePlayerQuery(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PlayerQuery*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->player_name, sizeof(pstIn->player_name)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodePlayerQuery(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PlayerQuery*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->player_name, sizeof(pstOut->player_name)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePlayerQueryBrd(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PlayerQueryBrd*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->target_name, sizeof(pstIn->target_name)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->target_userid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodePlayerQueryBrd(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PlayerQueryBrd*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->target_name, sizeof(pstOut->target_name)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->target_userid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePlayerQueryNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PlayerQueryNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->gender))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->job))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->level))
		return -1;

	if(-1 == poNetData->AddString(pstIn->family_name, sizeof(pstIn->family_name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->family_title, sizeof(pstIn->family_title)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->alias, sizeof(pstIn->alias)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_num))
		return -1;

	for(int i = 0; i < 45; i++)
	{
		if(i >= (int)pstIn->item_num)
			break;
		if(-1 == EnCodeITEM_INFO(&pstIn->item_info[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodePlayerQueryNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PlayerQueryNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->gender))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->job))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->level))
		return -1;

	if(-1 == poNetData->DelString(pstOut->family_name, sizeof(pstOut->family_name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->family_title, sizeof(pstOut->family_title)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->alias, sizeof(pstOut->alias)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_num))
		return -1;

	for(int i = 0; i < 45; i++)
	{
		if(i >= (int)pstOut->item_num)
			break;
		if(-1 == DeCodeITEM_INFO(&pstOut->item_info[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodePlayerSiteSeg(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PlayerSiteSeg*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodePlayerSiteSeg(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PlayerSiteSeg*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePlayerSiteSegBrd(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PlayerSiteSegBrd*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodePlayerSiteSegBrd(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PlayerSiteSegBrd*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePlayerSiteSegNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PlayerSiteSegNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodePlayerSiteSegNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PlayerSiteSegNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTitleAdd(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TitleAdd*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->title_id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTitleAdd(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TitleAdd*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->title_id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTitleRemove(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TitleRemove*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->title_id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTitleRemove(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TitleRemove*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->title_id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTitleApply(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TitleApply*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->title_id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTitleApply(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TitleApply*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->title_id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTitleAddAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TitleAddAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->title_num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstIn->title_num)
			break;
		if(-1 == EnCodeTITLE_INFO(&pstIn->titles[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeTitleAddAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TitleAddAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->title_num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstOut->title_num)
			break;
		if(-1 == DeCodeTITLE_INFO(&pstOut->titles[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeTitleRemoveAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TitleRemoveAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->title_id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTitleRemoveAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TitleRemoveAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->title_id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSysMsgNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SysMsgNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->msg_type))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->scroll_count))
		return -1;

	if(-1 == poNetData->AddString(pstIn->msg, sizeof(pstIn->msg)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSysMsgNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SysMsgNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->msg_type))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->scroll_count))
		return -1;

	if(-1 == poNetData->DelString(pstOut->msg, sizeof(pstOut->msg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeRelationChatNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<RelationChatNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == EnCodeCHAT_MSG(&pstIn->chat_message, poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeRelationChatNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<RelationChatNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == DeCodeCHAT_MSG(&pstOut->chat_message, poNetData))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeNpcSelect(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<NpcSelect*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->npc_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeNpcSelect(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<NpcSelect*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->npc_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeNpcTalkReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<NpcTalkReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->npc_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->func, sizeof(pstIn->func)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeNpcTalkReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<NpcTalkReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->npc_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->func, sizeof(pstOut->func)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeNpcTalkAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<NpcTalkAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->width))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->height))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->npc_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->talk_len))
		return -1;

	{
		int iCount = (((7500) < ((int)pstIn->talk_len)) ? (7500) : ((int)pstIn->talk_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->talk, iCount*sizeof(char)))
			return -1;
	}
	if(-1 == poNetData->AddWord(pstIn->quest_state_num))
		return -1;

	for(int i = 0; i < 2; i++)
	{
		if(i >= (int)pstIn->quest_state_num)
			break;
		if(-1 == EnCodeQUEST_STATE_INFO(&pstIn->quest_states[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddChar(pstIn->comp))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeNpcTalkAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<NpcTalkAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->width))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->height))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->npc_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->talk_len))
		return -1;

	{
		int iCount = (((7500) < ((int)pstOut->talk_len)) ? (7500) : ((int)pstOut->talk_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->talk, iCount*sizeof(char)))
			return -1;
	}
	if(-1 == poNetData->DelWord(pstOut->quest_state_num))
		return -1;

	for(int i = 0; i < 2; i++)
	{
		if(i >= (int)pstOut->quest_state_num)
			break;
		if(-1 == DeCodeQUEST_STATE_INFO(&pstOut->quest_states[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelChar(pstOut->comp))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuickBarSet(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuickBarSet*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

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
int DeCodeQuickBarSet(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuickBarSet*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

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
int EnCodeQuickBarSetNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuickBarSetNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->num))
		return -1;

	for(int i = 0; i < 30; ++i)
	{
		if(i >= (int)pstIn->num)
			break;
		if(-1 == EnCodeQUICK_BAR_INFO(&pstIn->info[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeQuickBarSetNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuickBarSetNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->num))
		return -1;

	for(int i = 0; i < 30; ++i)
	{
		if(i >= (int)pstOut->num)
			break;
		if(-1 == DeCodeQUICK_BAR_INFO(&pstOut->info[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeQuickBarRemove(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuickBarRemove*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->slot))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuickBarRemove(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuickBarRemove*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->slot))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuickBarRemoveNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuickBarRemoveNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->slot))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuickBarRemoveNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuickBarRemoveNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->slot))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuickBarMove(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuickBarMove*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->src_slot))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->dst_slot))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuickBarMove(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuickBarMove*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->src_slot))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->dst_slot))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeShortcutSet(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ShortcutSet*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	{
		int iCount = 16;
		if(-1 == poNetData->AddBlob((char*)pstIn->info, iCount*sizeof(unsigned short)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeShortcutSet(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ShortcutSet*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	{
		int iCount = 16;
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->info, iCount*sizeof(unsigned short)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeShortcutNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ShortcutNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	{
		int iCount = 16;
		if(-1 == poNetData->AddBlob((char*)pstIn->info, iCount*sizeof(unsigned short)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeShortcutNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ShortcutNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	{
		int iCount = 16;
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->info, iCount*sizeof(unsigned short)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeGoldDeposit(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GoldDeposit*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt64(pstIn->gold))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeGoldDeposit(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GoldDeposit*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt64(pstOut->gold))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeGoldTake(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GoldTake*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt64(pstIn->gold))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeGoldTake(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GoldTake*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt64(pstOut->gold))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeBeServantNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<BeServantNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->servant_guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->servant_level))
		return -1;

	if(-1 == poNetData->AddString(pstIn->master_name, sizeof(pstIn->master_name)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeBeServantNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<BeServantNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->servant_guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->servant_level))
		return -1;

	if(-1 == poNetData->DelString(pstOut->master_name, sizeof(pstOut->master_name)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeRoleAttrExtRefNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<RoleAttrExtRefNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->attr_name))
		return -1;

	if(-1 == poNetData->AddInt64(pstIn->attr_value))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeRoleAttrExtRefNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<RoleAttrExtRefNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->attr_name))
		return -1;

	if(-1 == poNetData->DelInt64(pstOut->attr_value))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeStartFamilyWarBrd(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<StartFamilyWarBrd*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->attack, sizeof(pstIn->attack)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->defence, sizeof(pstIn->defence)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeStartFamilyWarBrd(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<StartFamilyWarBrd*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->attack, sizeof(pstOut->attack)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->defence, sizeof(pstOut->defence)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeRunningFamilyWarNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<RunningFamilyWarNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstIn->num)
			break;
		if(-1 == EnCodeFAMILY_WAR_INFO(&pstIn->families[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeRunningFamilyWarNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<RunningFamilyWarNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstOut->num)
			break;
		if(-1 == DeCodeFAMILY_WAR_INFO(&pstOut->families[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeCastleNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<CastleNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->num))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstIn->num)
			break;
		if(-1 == EnCodeCASTLE_INFO(&pstIn->castles[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeCastleNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<CastleNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->num))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstOut->num)
			break;
		if(-1 == DeCodeCASTLE_INFO(&pstOut->castles[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeGoldDrop(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GoldDrop*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt64(pstIn->gold))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeGoldDrop(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GoldDrop*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt64(pstOut->gold))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePlayerFamilyChangeNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PlayerFamilyChangeNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->family_name, sizeof(pstIn->family_name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->castle_name, sizeof(pstIn->castle_name)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodePlayerFamilyChangeNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PlayerFamilyChangeNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->family_name, sizeof(pstOut->family_name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->castle_name, sizeof(pstOut->castle_name)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeNotifyMapEffect(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<NotifyMapEffect*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->effect_id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->effect_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->effect_y))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->effect_life))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeNotifyMapEffect(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<NotifyMapEffect*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->effect_id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->effect_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->effect_y))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->effect_life))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeRoleTalkNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<RoleTalkNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->role_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->msg, sizeof(pstIn->msg)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeRoleTalkNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<RoleTalkNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->role_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->msg, sizeof(pstOut->msg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeProgressStartNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ProgressStartNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->desc, sizeof(pstIn->desc)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->duration))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeProgressStartNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ProgressStartNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->desc, sizeof(pstOut->desc)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->duration))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeProgressCancelNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ProgressCancelNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->complete))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeProgressCancelNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ProgressCancelNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->complete))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeVerifyImageQuestion(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<VerifyImageQuestion*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->size))
		return -1;

	{
		int iCount = (((4096) < ((int)pstIn->size)) ? (4096) : ((int)pstIn->size));
		if(-1 == poNetData->AddBlob((char*)pstIn->buffer, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeVerifyImageQuestion(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<VerifyImageQuestion*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->size))
		return -1;

	{
		int iCount = (((4096) < ((int)pstOut->size)) ? (4096) : ((int)pstOut->size));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->buffer, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeVerifyImageAnswer(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<VerifyImageAnswer*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->answer, sizeof(pstIn->answer)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeVerifyImageAnswer(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<VerifyImageAnswer*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->answer, sizeof(pstOut->answer)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeVerifyImageReset(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<VerifyImageReset*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeVerifyImageReset(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<VerifyImageReset*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeVerifyImageResultNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<VerifyImageResultNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->fail_count))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeVerifyImageResultNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<VerifyImageResultNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->fail_count))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeMallBuy(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeMallBuy*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->item_index))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_amount))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeMallBuy(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeMallBuy*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->item_index))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_amount))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeMallListReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeMallListReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->page_id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeMallListReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeMallListReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->page_id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeMallListAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeMallListAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->page_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->item_count))
		return -1;

	for(int i = 0; i < 250; i++)
	{
		if(i >= (int)pstIn->item_count)
			break;
		if(-1 == EnCodeMALL_ITEM_INFO(&pstIn->item_list[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeTradeMallListAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeMallListAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->page_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->item_count))
		return -1;

	for(int i = 0; i < 250; i++)
	{
		if(i >= (int)pstOut->item_count)
			break;
		if(-1 == DeCodeMALL_ITEM_INFO(&pstOut->item_list[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeTradeMallItemDetailReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeMallItemDetailReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->item_index))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeMallItemDetailReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeMallItemDetailReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->item_index))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeMallItemDetailAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeMallItemDetailAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == EnCodeMALL_ITEM_DETAIL(&pstIn->item, poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeMallItemDetailAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeMallItemDetailAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == DeCodeMALL_ITEM_DETAIL(&pstOut->item, poNetData))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeMallChartsReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeMallChartsReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeMallChartsReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeMallChartsReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeMallChartsAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeMallChartsAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->item_count))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstIn->item_count)
			break;
		if(-1 == EnCodeMALL_ITEM_INFO(&pstIn->item_list[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeTradeMallChartsAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeMallChartsAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->item_count))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstOut->item_count)
			break;
		if(-1 == DeCodeMALL_ITEM_INFO(&pstOut->item_list[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeNpcTalkReqEx(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<NpcTalkReqEx*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->func, sizeof(pstIn->func)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeNpcTalkReqEx(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<NpcTalkReqEx*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->func, sizeof(pstOut->func)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeNpcTalkAckEx(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<NpcTalkAckEx*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->width))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->height))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->talk_len))
		return -1;

	{
		int iCount = (((8000) < ((int)pstIn->talk_len)) ? (8000) : ((int)pstIn->talk_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->talk, iCount*sizeof(char)))
			return -1;
	}
	if(-1 == poNetData->AddChar(pstIn->comp))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeNpcTalkAckEx(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<NpcTalkAckEx*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->width))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->height))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->talk_len))
		return -1;

	{
		int iCount = (((8000) < ((int)pstOut->talk_len)) ? (8000) : ((int)pstOut->talk_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->talk, iCount*sizeof(char)))
			return -1;
	}
	if(-1 == poNetData->DelChar(pstOut->comp))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestAccept(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestAccept*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->quest_id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuestAccept(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestAccept*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->quest_id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestAddNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestAddNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->quest_id))
		return -1;

	if(-1 == poNetData->AddString(pstIn->quest_name, sizeof(pstIn->quest_name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->quest_type))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->group_huntings_len))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstIn->group_huntings_len)
			break;
		if(-1 == EnCodeQUEST_HUNTING_INFO(&pstIn->group_huntings[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddWord(pstIn->huntings_len))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstIn->huntings_len)
			break;
		if(-1 == EnCodeQUEST_HUNTING_INFO(&pstIn->huntings[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddWord(pstIn->huntlevels_len))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstIn->huntlevels_len)
			break;
		if(-1 == EnCodeQUEST_HUNTLEVEL_INFO(&pstIn->huntlevels[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddWord(pstIn->group_items_len))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstIn->group_items_len)
			break;
		if(-1 == EnCodeQUEST_ITEM_INFO(&pstIn->group_items[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddWord(pstIn->collect_items_len))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstIn->collect_items_len)
			break;
		if(-1 == EnCodeQUEST_ITEM_INFO(&pstIn->collect_items[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddWord(pstIn->apply_items_len))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstIn->apply_items_len)
			break;
		if(-1 == EnCodeQUEST_ITEM_INFO(&pstIn->apply_items[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddWord(pstIn->npcs_len))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstIn->npcs_len)
			break;
		if(-1 == EnCodeQUEST_NPC_INFO(&pstIn->npcs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddByte(pstIn->track_enabled))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->life))
		return -1;

	if(-1 == poNetData->AddString(pstIn->progressing, sizeof(pstIn->progressing)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->accomplishing, sizeof(pstIn->accomplishing)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuestAddNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestAddNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->quest_id))
		return -1;

	if(-1 == poNetData->DelString(pstOut->quest_name, sizeof(pstOut->quest_name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->quest_type))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->group_huntings_len))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstOut->group_huntings_len)
			break;
		if(-1 == DeCodeQUEST_HUNTING_INFO(&pstOut->group_huntings[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelWord(pstOut->huntings_len))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstOut->huntings_len)
			break;
		if(-1 == DeCodeQUEST_HUNTING_INFO(&pstOut->huntings[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelWord(pstOut->huntlevels_len))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstOut->huntlevels_len)
			break;
		if(-1 == DeCodeQUEST_HUNTLEVEL_INFO(&pstOut->huntlevels[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelWord(pstOut->group_items_len))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstOut->group_items_len)
			break;
		if(-1 == DeCodeQUEST_ITEM_INFO(&pstOut->group_items[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelWord(pstOut->collect_items_len))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstOut->collect_items_len)
			break;
		if(-1 == DeCodeQUEST_ITEM_INFO(&pstOut->collect_items[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelWord(pstOut->apply_items_len))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstOut->apply_items_len)
			break;
		if(-1 == DeCodeQUEST_ITEM_INFO(&pstOut->apply_items[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelWord(pstOut->npcs_len))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstOut->npcs_len)
			break;
		if(-1 == DeCodeQUEST_NPC_INFO(&pstOut->npcs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelByte(pstOut->track_enabled))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->life))
		return -1;

	if(-1 == poNetData->DelString(pstOut->progressing, sizeof(pstOut->progressing)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->accomplishing, sizeof(pstOut->accomplishing)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestAccomplish(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestAccomplish*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->quest_id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->select_index))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuestAccomplish(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestAccomplish*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->quest_id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->select_index))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestUpdateNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestUpdateNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->quest_id))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->data_type))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->id))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->value))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuestUpdateNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestUpdateNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->quest_id))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->data_type))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->id))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->value))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestTrackChange(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestTrackChange*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->quest_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->track_enabled))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuestTrackChange(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestTrackChange*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->quest_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->track_enabled))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestTrackChangeNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestTrackChangeNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->quest_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->track_enabled))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuestTrackChangeNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestTrackChangeNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->quest_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->track_enabled))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestReadyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestReadyNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->quest_id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuestReadyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestReadyNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->quest_id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestCompleteNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestCompleteNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->quest_id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuestCompleteNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestCompleteNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->quest_id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestDrop(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestDrop*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->quest_id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuestDrop(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestDrop*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->quest_id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestDropNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestDropNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->quest_id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuestDropNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestDropNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->quest_id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestQueryCanAccept(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestQueryCanAccept*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuestQueryCanAccept(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestQueryCanAccept*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestQueryCanAcceptNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestQueryCanAcceptNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->num))
		return -1;

	{
		int iCount = (((500) < ((int)pstIn->num)) ? (500) : ((int)pstIn->num));
		if(-1 == poNetData->AddBlob((char*)pstIn->quests, iCount*sizeof(unsigned short)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeQuestQueryCanAcceptNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestQueryCanAcceptNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->num))
		return -1;

	{
		int iCount = (((500) < ((int)pstOut->num)) ? (500) : ((int)pstOut->num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->quests, iCount*sizeof(unsigned short)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeDelegateSellCmd(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<DelegateSellCmd*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->item_value))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->item_unit))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->value_type))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeDelegateSellCmd(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<DelegateSellCmd*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->item_value))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->item_unit))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->value_type))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeDelegateBuyCmd(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<DelegateBuyCmd*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_id))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->item_count))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->item_value))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->item_unit))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->value_type))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeDelegateBuyCmd(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<DelegateBuyCmd*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_id))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->item_count))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->item_value))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->item_unit))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->value_type))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeDelegateSellListReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<DelegateSellListReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->start))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->count))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->type))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->subtype))
		return -1;

	if(-1 == poNetData->AddString(pstIn->item_name, sizeof(pstIn->item_name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->is_reverse))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeDelegateSellListReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<DelegateSellListReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->start))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->count))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->type))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->subtype))
		return -1;

	if(-1 == poNetData->DelString(pstOut->item_name, sizeof(pstOut->item_name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->is_reverse))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeDelegateSellListAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<DelegateSellListAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->type))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->subtype))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->total))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->start))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->count))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstIn->count)
			break;
		if(-1 == EnCodeDELEGATE_SELL_ITEM(&pstIn->items[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeDelegateSellListAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<DelegateSellListAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->type))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->subtype))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->total))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->start))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->count))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstOut->count)
			break;
		if(-1 == DeCodeDELEGATE_SELL_ITEM(&pstOut->items[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeDelegateBuyListReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<DelegateBuyListReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->start))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->count))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->type))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->subtype))
		return -1;

	if(-1 == poNetData->AddString(pstIn->item_name, sizeof(pstIn->item_name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->is_reverse))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeDelegateBuyListReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<DelegateBuyListReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->start))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->count))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->type))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->subtype))
		return -1;

	if(-1 == poNetData->DelString(pstOut->item_name, sizeof(pstOut->item_name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->is_reverse))
		return -1;

	return sizeof(*pstOut);
}
/*
int EnCodeDelegateBuyListAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<DelegateBuyListAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->type))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->subtype))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->total))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->start))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->count))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstIn->count)
			break;
		if(-1 == EnCodeDELEGATE_BUY_ITEM(&pstIn->items[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeDelegateBuyListAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<DelegateBuyListAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->type))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->subtype))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->total))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->start))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->count))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstOut->count)
			break;
		if(-1 == DeCodeDELEGATE_BUY_ITEM(&pstOut->items[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
*/
int EnCodeMarketBuyCmd(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MarketBuyCmd*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->trade_id))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->count))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMarketBuyCmd(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MarketBuyCmd*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->trade_id))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->count))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMarketSellCmd(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MarketSellCmd*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->trade_id))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMarketSellCmd(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MarketSellCmd*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->trade_id))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeDelegateCancel(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<DelegateCancel*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->trade_id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeDelegateCancel(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<DelegateCancel*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->trade_id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeDelegateMineReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<DelegateMineReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeDelegateMineReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<DelegateMineReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
/*
int EnCodeDelegateMineAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<DelegateMineAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->count))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstIn->count)
			break;
		if(-1 == EnCodeDELEGATE_INFO(&pstIn->trade[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeDelegateMineAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<DelegateMineAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->count))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstOut->count)
			break;
		if(-1 == DeCodeDELEGATE_INFO(&pstOut->trade[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
*/
int EnCodeAttrShowExNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<AttrShowExNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->skill_id))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->target))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeAttrShowExNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<AttrShowExNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->skill_id))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->target))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeCampaignListReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<CampaignListReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeCampaignListReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<CampaignListReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeCampaignListAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<CampaignListAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->svr_time))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->count))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstIn->count)
			break;
		if(-1 == EnCodeCAMPAIGN_INFO(&pstIn->campaigns[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeCampaignListAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<CampaignListAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->svr_time))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->count))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstOut->count)
			break;
		if(-1 == DeCodeCAMPAIGN_INFO(&pstOut->campaigns[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeCampaignDetailReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<CampaignDetailReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeCampaignDetailReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<CampaignDetailReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeCampaignDetailAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<CampaignDetailAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->id))
		return -1;

	if(-1 == poNetData->AddString(pstIn->npc, sizeof(pstIn->npc)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->desc, sizeof(pstIn->desc)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->award, sizeof(pstIn->award)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeCampaignDetailAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<CampaignDetailAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->id))
		return -1;

	if(-1 == poNetData->DelString(pstOut->npc, sizeof(pstOut->npc)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->desc, sizeof(pstOut->desc)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->award, sizeof(pstOut->award)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeInputDlgReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<InputDlgReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->dlg_id))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->timeout))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->param_len))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->str_len))
		return -1;

	{
		int iCount = (((8000) < ((int)pstIn->str_len)) ? (8000) : ((int)pstIn->str_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->str, iCount*sizeof(char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeInputDlgReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<InputDlgReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->dlg_id))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->timeout))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->param_len))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->str_len))
		return -1;

	{
		int iCount = (((8000) < ((int)pstOut->str_len)) ? (8000) : ((int)pstOut->str_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->str, iCount*sizeof(char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeInputDlgAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<InputDlgAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->dlg_id))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->str_len))
		return -1;

	{
		int iCount = (((8000) < ((int)pstIn->str_len)) ? (8000) : ((int)pstIn->str_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->str, iCount*sizeof(char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeInputDlgAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<InputDlgAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->dlg_id))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->str_len))
		return -1;

	{
		int iCount = (((8000) < ((int)pstOut->str_len)) ? (8000) : ((int)pstOut->str_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->str, iCount*sizeof(char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeMsgDlgReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MsgDlgReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->dlg_id))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->timeout))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->str_len))
		return -1;

	{
		int iCount = (((8000) < ((int)pstIn->str_len)) ? (8000) : ((int)pstIn->str_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->str, iCount*sizeof(char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeMsgDlgReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MsgDlgReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->dlg_id))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->timeout))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->str_len))
		return -1;

	{
		int iCount = (((8000) < ((int)pstOut->str_len)) ? (8000) : ((int)pstOut->str_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->str, iCount*sizeof(char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeMsgDlgAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MsgDlgAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->dlg_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->key))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMsgDlgAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MsgDlgAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->dlg_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->key))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeWebDlgNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<WebDlgNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->title, sizeof(pstIn->title)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->parm, sizeof(pstIn->parm)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->url_len))
		return -1;

	{
		int iCount = (((2048) < ((int)pstIn->url_len)) ? (2048) : ((int)pstIn->url_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->url, iCount*sizeof(char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeWebDlgNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<WebDlgNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->title, sizeof(pstOut->title)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->parm, sizeof(pstOut->parm)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->url_len))
		return -1;

	{
		int iCount = (((2048) < ((int)pstOut->url_len)) ? (2048) : ((int)pstOut->url_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->url, iCount*sizeof(char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeOpenWebPageNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<OpenWebPageNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->url_len))
		return -1;

	{
		int iCount = (((2048) < ((int)pstIn->url_len)) ? (2048) : ((int)pstIn->url_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->url, iCount*sizeof(char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeOpenWebPageNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<OpenWebPageNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->url_len))
		return -1;

	{
		int iCount = (((2048) < ((int)pstOut->url_len)) ? (2048) : ((int)pstOut->url_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->url, iCount*sizeof(char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeGlobalNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GlobalNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->int_count))
		return -1;

	for(int i = 0; i < 256; i++)
	{
		if(i >= (int)pstIn->int_count)
			break;
		if(-1 == EnCodeIntData(&pstIn->int_data[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddWord(pstIn->str_count))
		return -1;

	for(int i = 0; i < 256; i++)
	{
		if(i >= (int)pstIn->str_count)
			break;
		if(-1 == EnCodeStrData(&pstIn->str_data[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeGlobalNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GlobalNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->int_count))
		return -1;

	for(int i = 0; i < 256; i++)
	{
		if(i >= (int)pstOut->int_count)
			break;
		if(-1 == DeCodeIntData(&pstOut->int_data[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelWord(pstOut->str_count))
		return -1;

	for(int i = 0; i < 256; i++)
	{
		if(i >= (int)pstOut->str_count)
			break;
		if(-1 == DeCodeStrData(&pstOut->str_data[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeSpeakerMsgAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SpeakerMsgAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->ret))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->ecode))
		return -1;

	if(-1 == poNetData->AddString(pstIn->msg, sizeof(pstIn->msg)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSpeakerMsgAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SpeakerMsgAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->ret))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->ecode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->msg, sizeof(pstOut->msg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeClientKeepAlive(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ClientKeepAlive*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeClientKeepAlive(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ClientKeepAlive*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeFamilyAllyTableNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<FamilyAllyTableNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->count))
		return -1;

	for(int i = 0; i < MAX_ALLY_NUM; i++)
	{
		if(i >= (int)pstIn->count)
			break;
		if(-1 == EnCodeFAMILY_ALLY_INFO(&pstIn->table[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeFamilyAllyTableNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<FamilyAllyTableNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->count))
		return -1;

	for(int i = 0; i < MAX_ALLY_NUM; i++)
	{
		if(i >= (int)pstOut->count)
			break;
		if(-1 == DeCodeFAMILY_ALLY_INFO(&pstOut->table[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePlayerCustomReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PlayerCustomReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodePlayerCustomReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PlayerCustomReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePlayerCustomAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PlayerCustomAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == EnCodeCUSTOM_INFO(&pstIn->info, poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodePlayerCustomAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PlayerCustomAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == DeCodeCUSTOM_INFO(&pstOut->info, poNetData))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeWebPageNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<WebPageNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->url_len))
		return -1;

	{
		int iCount = (((1024) < ((int)pstIn->url_len)) ? (1024) : ((int)pstIn->url_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->url, iCount*sizeof(char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeWebPageNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<WebPageNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->url_len))
		return -1;

	{
		int iCount = (((1024) < ((int)pstOut->url_len)) ? (1024) : ((int)pstOut->url_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->url, iCount*sizeof(char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeCustomNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<CustomNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == EnCodeKEY_VALUE_PAIR(&pstIn->info, poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeCustomNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<CustomNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == DeCodeKEY_VALUE_PAIR(&pstOut->info, poNetData))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeCustomBroadcast(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<CustomBroadcast*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == EnCodeKEY_VALUE_PAIR(&pstIn->info, poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeCustomBroadcast(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<CustomBroadcast*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == DeCodeKEY_VALUE_PAIR(&pstOut->info, poNetData))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemCustomNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemCustomNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->role_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == EnCodeCUSTOM_INFO(&pstIn->info, poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemCustomNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemCustomNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->role_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == DeCodeCUSTOM_INFO(&pstOut->info, poNetData))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTaobaoNpcBuy(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TaobaoNpcBuy*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->shop_id))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTaobaoNpcBuy(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TaobaoNpcBuy*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->shop_id))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTaobaoNpcShopReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TaobaoNpcShopReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->shop_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->item_index))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->item_count))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTaobaoNpcShopReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TaobaoNpcShopReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->shop_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->item_index))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->item_count))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTaobaoNpcShopAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TaobaoNpcShopAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->shop_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->total_count))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->item_index))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->item_count))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstIn->item_count)
			break;
		if(-1 == EnCodeTAOBAO_ITEM_INFO(&pstIn->item_list[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeTaobaoNpcShopAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TaobaoNpcShopAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->shop_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->total_count))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->item_index))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->item_count))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstOut->item_count)
			break;
		if(-1 == DeCodeTAOBAO_ITEM_INFO(&pstOut->item_list[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeRunClientScriptNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<RunClientScriptNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->lua_name, sizeof(pstIn->lua_name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->lua_func, sizeof(pstIn->lua_func)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->lua_params, sizeof(pstIn->lua_params)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeRunClientScriptNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<RunClientScriptNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->lua_name, sizeof(pstOut->lua_name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->lua_func, sizeof(pstOut->lua_func)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->lua_params, sizeof(pstOut->lua_params)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeObjCustomNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ObjCustomNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->obj_guid))
		return -1;

	if(-1 == EnCodeCUSTOM_INFO(&pstIn->info, poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeObjCustomNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ObjCustomNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->obj_guid))
		return -1;

	if(-1 == DeCodeCUSTOM_INFO(&pstOut->info, poNetData))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeCampaignJoinNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<CampaignJoinNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeCampaignJoinNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<CampaignJoinNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMapReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MapReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMapReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MapReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMapNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MapNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->count))
		return -1;

	for(int i = 0; i < 512; i++)
	{
		if(i >= (int)pstIn->count)
			break;
		if(-1 == EnCodeMAP_INFO(&pstIn->info[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeMapNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MapNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->count))
		return -1;

	for(int i = 0; i < 512; i++)
	{
		if(i >= (int)pstOut->count)
			break;
		if(-1 == DeCodeMAP_INFO(&pstOut->info[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeGridReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GridReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->logic, sizeof(pstIn->logic)))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->index))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->count))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeGridReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GridReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->logic, sizeof(pstOut->logic)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->index))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->count))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeGridNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GridNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->logic, sizeof(pstIn->logic)))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->index))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->count))
		return -1;

	{
		int iCount = (((1024) < ((int)pstIn->count)) ? (1024) : ((int)pstIn->count));
		if(-1 == poNetData->AddBlob((char*)pstIn->info, iCount*sizeof(unsigned int)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeGridNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GridNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->logic, sizeof(pstOut->logic)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->index))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->count))
		return -1;

	{
		int iCount = (((1024) < ((int)pstOut->count)) ? (1024) : ((int)pstOut->count));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->info, iCount*sizeof(unsigned int)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeTableReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TableReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTableReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TableReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTableNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TableNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->count))
		return -1;

	for(int i = 0; i < 256; i++)
	{
		if(i >= (int)pstIn->count)
			break;
		if(-1 == EnCodeTABLE_INFO(&pstIn->info[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeTableNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TableNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->count))
		return -1;

	for(int i = 0; i < 256; i++)
	{
		if(i >= (int)pstOut->count)
			break;
		if(-1 == DeCodeTABLE_INFO(&pstOut->info[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeTableDataReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TableDataReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->index))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->count))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTableDataReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TableDataReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->index))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->count))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTableDataNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TableDataNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->index))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->size))
		return -1;

	{
		int iCount = (((65536) < ((int)pstIn->size)) ? (65536) : ((int)pstIn->size));
		if(-1 == poNetData->AddBlob((char*)pstIn->buf, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeTableDataNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TableDataNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->index))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->size))
		return -1;

	{
		int iCount = (((65536) < ((int)pstOut->size)) ? (65536) : ((int)pstOut->size));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->buf, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeCampaignRunNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<CampaignRunNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeCampaignRunNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<CampaignRunNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeRideReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<RideReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->enable))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeRideReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<RideReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->enable))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeRideNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<RideNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->enable))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeRideNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<RideNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->enable))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePermissionReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PermissionReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->key, sizeof(pstIn->key)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->value, sizeof(pstIn->value)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodePermissionReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PermissionReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->key, sizeof(pstOut->key)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->value, sizeof(pstOut->value)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeVipItemListReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<VipItemListReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeVipItemListReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<VipItemListReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeVipItemListAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<VipItemListAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->vip_level))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->remain))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstIn->num)
			break;
		if(-1 == EnCodeVIP_ITEM(&pstIn->items[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeVipItemListAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<VipItemListAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->vip_level))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->remain))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstOut->num)
			break;
		if(-1 == DeCodeVIP_ITEM(&pstOut->items[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeVipLevelBuyReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<VipLevelBuyReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->vip_level))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeVipLevelBuyReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<VipLevelBuyReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->vip_level))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeVipLevelBuyAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<VipLevelBuyAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->vip_level))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->errcode))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeVipLevelBuyAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<VipLevelBuyAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->vip_level))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->errcode))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeVipItemBuyReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<VipItemBuyReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeVipItemBuyReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<VipItemBuyReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeVipItemBuyAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<VipItemBuyAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->errcode))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeVipItemBuyAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<VipItemBuyAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->errcode))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeVipItemApplyReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<VipItemApplyReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeVipItemApplyReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<VipItemApplyReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeVipItemApplyAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<VipItemApplyAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->errcode))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeVipItemApplyAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<VipItemApplyAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->errcode))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeVipExpireNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<VipExpireNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->vip_level))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeVipExpireNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<VipExpireNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->vip_level))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeVipLevelListReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<VipLevelListReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeVipLevelListReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<VipLevelListReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeVipLevelListAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<VipLevelListAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstIn->num)
			break;
		if(-1 == EnCodeVIP_LEVEL(&pstIn->levels[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeVipLevelListAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<VipLevelListAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstOut->num)
			break;
		if(-1 == DeCodeVIP_LEVEL(&pstOut->levels[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeTradeNpcShopNumNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeNpcShopNumNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->shop_id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_index))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_amount))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeNpcShopNumNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeNpcShopNumNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->shop_id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_index))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_amount))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSubmitFormAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SubmitFormAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->script_name, sizeof(pstIn->script_name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->result, sizeof(pstIn->result)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSubmitFormAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SubmitFormAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->script_name, sizeof(pstOut->script_name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->result, sizeof(pstOut->result)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemAttrReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemAttrReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->attr_name))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->attr_value))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemAttrReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemAttrReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->attr_name))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->attr_value))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestStateReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestStateReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->npc_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuestStateReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestStateReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->npc_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestStateNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestStateNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->npc_guid))
		return -1;

	if(-1 == EnCodeQUEST_STATE_INFO(&pstIn->info, poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuestStateNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestStateNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->npc_guid))
		return -1;

	if(-1 == DeCodeQUEST_STATE_INFO(&pstOut->info, poNetData))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestQueryReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestQueryReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->quest_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->use_context))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuestQueryReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestQueryReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->quest_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->use_context))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestQueryNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestQueryNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->quest_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->result_type))
		return -1;

	if(-1 == poNetData->AddString(pstIn->quest_name, sizeof(pstIn->quest_name)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->life))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuestQueryNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestQueryNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->quest_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->result_type))
		return -1;

	if(-1 == poNetData->DelString(pstOut->quest_name, sizeof(pstOut->quest_name)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->life))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeGloryFinishNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GloryFinishNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == EnCodeGLORY_STATE(&pstIn->status, poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeGloryFinishNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GloryFinishNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == DeCodeGLORY_STATE(&pstOut->status, poNetData))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeGloryStateQuery(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GloryStateQuery*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeGloryStateQuery(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GloryStateQuery*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeGloryStateAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GloryStateAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->count))
		return -1;

	for(int i = 0; i < 512; i++)
	{
		if(i >= (int)pstIn->count)
			break;
		if(-1 == EnCodeGLORY_STATE(&pstIn->glories[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeGloryStateAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GloryStateAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->count))
		return -1;

	for(int i = 0; i < 512; i++)
	{
		if(i >= (int)pstOut->count)
			break;
		if(-1 == DeCodeGLORY_STATE(&pstOut->glories[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeGloryAwardGet(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GloryAwardGet*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeGloryAwardGet(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GloryAwardGet*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTraceReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TraceReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->text, sizeof(pstIn->text)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTraceReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TraceReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->text, sizeof(pstOut->text)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestNpcStateNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestNpcStateNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->npc_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->state))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuestNpcStateNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestNpcStateNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->npc_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->state))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeClientKeepAliveRet(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ClientKeepAliveRet*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeClientKeepAliveRet(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ClientKeepAliveRet*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeRemoveClientNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<RemoveClientNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->user_name, sizeof(pstIn->user_name)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeRemoveClientNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<RemoveClientNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->user_name, sizeof(pstOut->user_name)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSceneMagicAppearNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SceneMagicAppearNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->scenemagic_guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->resource_type))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->resource_id))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->property))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSceneMagicAppearNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SceneMagicAppearNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->scenemagic_guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->resource_type))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->resource_id))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->property))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeDummyPackage(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<DummyPackage*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->dummy_guid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->package_len))
		return -1;

	{
		int iCount = (((65535) < ((int)pstIn->package_len)) ? (65535) : ((int)pstIn->package_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->package, iCount*sizeof(char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeDummyPackage(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<DummyPackage*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->dummy_guid))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->package_len))
		return -1;

	{
		int iCount = (((65535) < ((int)pstOut->package_len)) ? (65535) : ((int)pstOut->package_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->package, iCount*sizeof(char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeDummyItemMove(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<DummyItemMove*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->src_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->dst_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_site))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeDummyItemMove(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<DummyItemMove*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->src_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->dst_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_site))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeDummyControlNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<DummyControlNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->dummy_guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->is_open))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeDummyControlNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<DummyControlNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->dummy_guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->is_open))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeServantNumNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ServantNumNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->num))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeServantNumNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ServantNumNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->num))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeDummyStateSwitchReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<DummyStateSwitchReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->dummy_guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->state))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->y))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeDummyStateSwitchReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<DummyStateSwitchReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->dummy_guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->state))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->y))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeDummyStateSwitchAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<DummyStateSwitchAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->dummy_guid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->err_code))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->state))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeDummyStateSwitchAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<DummyStateSwitchAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->dummy_guid))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->err_code))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->state))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeHeroCreateNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<HeroCreateNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->dummy_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeHeroCreateNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<HeroCreateNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->dummy_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeHeroDestroyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<HeroDestroyNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->dummy_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeHeroDestroyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<HeroDestroyNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->dummy_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeAutoSetOptNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<AutoSetOptNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->is_auto_fight))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->is_auto_pick))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->auto_time))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeAutoSetOptNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<AutoSetOptNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->is_auto_fight))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->is_auto_pick))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->auto_time))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeAutoRunBeginNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<AutoRunBeginNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	{
		int iCount = 256;
		if(-1 == poNetData->AddBlob((char*)pstIn->opt, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeAutoRunBeginNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<AutoRunBeginNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	{
		int iCount = 256;
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->opt, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeAutoRunEndNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<AutoRunEndNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeAutoRunEndNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<AutoRunEndNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeNetCheckNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<NetCheckNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->opt))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeNetCheckNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<NetCheckNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->opt))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeHeroSkillSwitchReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<HeroSkillSwitchReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->hero_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->skill_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->disable))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeHeroSkillSwitchReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<HeroSkillSwitchReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->hero_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->skill_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->disable))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeHeroSkillSwitchAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<HeroSkillSwitchAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->hero_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->skill_num))
		return -1;

	{
		int iCount = (((64) < ((int)pstIn->skill_num)) ? (64) : ((int)pstIn->skill_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->skill_id, iCount*sizeof(unsigned short)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeHeroSkillSwitchAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<HeroSkillSwitchAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->hero_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->skill_num))
		return -1;

	{
		int iCount = (((64) < ((int)pstOut->skill_num)) ? (64) : ((int)pstOut->skill_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->skill_id, iCount*sizeof(unsigned short)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeMoveReqEx(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MoveReqEx*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_y))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->idx))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->tick))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMoveReqEx(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MoveReqEx*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_y))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->idx))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->tick))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSpellTargetEx(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SpellTargetEx*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->target))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->idx))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->tick))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSpellTargetEx(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SpellTargetEx*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->target))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->idx))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->tick))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSpellGridEx(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SpellGridEx*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->target_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->target_y))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->idx))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->ref_target))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->tick))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSpellGridEx(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SpellGridEx*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->target_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->target_y))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->idx))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->ref_target))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->tick))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeHeroLockTargetCmd(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<HeroLockTargetCmd*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->hero_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->target_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeHeroLockTargetCmd(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<HeroLockTargetCmd*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->hero_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->target_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeServantStatNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ServantStatNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->servant_guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->stat))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeServantStatNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ServantStatNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->servant_guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->stat))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeJointHitNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<JointHitNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->actor))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->helper))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->target_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->target_y))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->num))
		return -1;

	{
		int iCount = (((50) < ((int)pstIn->num)) ? (50) : ((int)pstIn->num));
		if(-1 == poNetData->AddBlob((char*)pstIn->targets, iCount*sizeof(uint64_t)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeJointHitNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<JointHitNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->actor))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->helper))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->target_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->target_y))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->num))
		return -1;

	{
		int iCount = (((50) < ((int)pstOut->num)) ? (50) : ((int)pstOut->num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->targets, iCount*sizeof(uint64_t)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeJointHit(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<JointHit*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->hero))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->target))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeJointHit(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<JointHit*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->hero))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->target))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestAcceptEx(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestAcceptEx*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->quest_id))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->npc_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuestAcceptEx(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestAcceptEx*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->quest_id))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->npc_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestAccomplishEx(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestAccomplishEx*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->quest_id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->select_index))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->npc_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuestAccomplishEx(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestAccomplishEx*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->quest_id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->select_index))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->npc_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeHeroLockTargetAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<HeroLockTargetAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->hero_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->target_guid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->err))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeHeroLockTargetAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<HeroLockTargetAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->hero_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->target_guid))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->err))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeShieldActiveNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ShieldActiveNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->role_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeShieldActiveNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ShieldActiveNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->role_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeShieldRemoveNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ShieldRemoveNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->role_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeShieldRemoveNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ShieldRemoveNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->role_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePlayerQueryEx(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PlayerQueryEx*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodePlayerQueryEx(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PlayerQueryEx*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePlayerQueryBrdEx(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PlayerQueryBrdEx*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->target_guid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->target_userid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodePlayerQueryBrdEx(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PlayerQueryBrdEx*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->target_guid))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->target_userid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeGSVersion(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GSVersion*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->version, sizeof(pstIn->version)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeGSVersion(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GSVersion*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->version, sizeof(pstOut->version)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeUpdateCheckCode(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<UpdateCheckCode*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->seed_1))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->seed_2))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeUpdateCheckCode(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<UpdateCheckCode*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->seed_1))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->seed_2))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMoveReq2(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MoveReq2*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_y))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->idx))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->tick))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->check))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMoveReq2(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MoveReq2*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_y))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->idx))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->tick))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->check))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSpellTarget2(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SpellTarget2*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->target))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->idx))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->tick))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->check))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSpellTarget2(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SpellTarget2*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->target))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->idx))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->tick))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->check))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSpellGrid2(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SpellGrid2*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->target_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->target_y))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->idx))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->ref_target))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->tick))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->check))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSpellGrid2(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SpellGrid2*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->target_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->target_y))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->idx))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->ref_target))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->tick))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->check))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeNpcSelect2(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<NpcSelect2*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->npc_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->check))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeNpcSelect2(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<NpcSelect2*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->npc_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->check))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeNpcTalkReq2(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<NpcTalkReq2*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->npc_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->func, sizeof(pstIn->func)))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->check))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeNpcTalkReq2(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<NpcTalkReq2*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->npc_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->func, sizeof(pstOut->func)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->check))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeClientVerNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ClientVerNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->seed_1))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->seed_2))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->client_ver))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeClientVerNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ClientVerNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->seed_1))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->seed_2))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->client_ver))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemApply2(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemApply2*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->check))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemApply2(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemApply2*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->check))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMonsterAppearNtf2(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MonsterAppearNtf2*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->monster_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->template_id))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->dst_x))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->dst_y))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->dir))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->cur_hp))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->max_hp))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->status))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->servant_lv))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->move_speed))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->buff_num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstIn->buff_num)
			break;
		if(-1 == EnCodeBUFF_INFO(&pstIn->buffs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddString(pstIn->master_name, sizeof(pstIn->master_name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->appear_type))
		return -1;

	if(-1 == poNetData->AddShort(pstIn->seed))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMonsterAppearNtf2(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MonsterAppearNtf2*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->monster_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->template_id))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->dst_x))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->dst_y))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->dir))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->cur_hp))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->max_hp))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->status))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->servant_lv))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->move_speed))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->buff_num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstOut->buff_num)
			break;
		if(-1 == DeCodeBUFF_INFO(&pstOut->buffs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelString(pstOut->master_name, sizeof(pstOut->master_name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->appear_type))
		return -1;

	if(-1 == poNetData->DelShort(pstOut->seed))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemAppearNtf2(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemAppearNtf2*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->template_id))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->dst_x))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->dst_y))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->skill_id))
		return -1;

	if(-1 == poNetData->AddString(pstIn->item_name, sizeof(pstIn->item_name)))
		return -1;

	if(-1 == poNetData->AddShort(pstIn->seed))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemAppearNtf2(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemAppearNtf2*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->template_id))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->dst_x))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->dst_y))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->skill_id))
		return -1;

	if(-1 == poNetData->DelString(pstOut->item_name, sizeof(pstOut->item_name)))
		return -1;

	if(-1 == poNetData->DelShort(pstOut->seed))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeClientKeepAliveEx(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ClientKeepAliveEx*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->seed))
		return -1;

	if(-1 == poNetData->AddShort(pstIn->opt_num))
		return -1;

	{
		int iCount = (((10) < ((int)pstIn->opt_num)) ? (10) : ((int)pstIn->opt_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->opt, iCount*sizeof(int)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeClientKeepAliveEx(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ClientKeepAliveEx*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->seed))
		return -1;

	if(-1 == poNetData->DelShort(pstOut->opt_num))
		return -1;

	{
		int iCount = (((10) < ((int)pstOut->opt_num)) ? (10) : ((int)pstOut->opt_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->opt, iCount*sizeof(int)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeGSVersionEx(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GSVersionEx*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	{
		int iCount = 256;
		if(-1 == poNetData->AddBlob((char*)pstIn->version, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeGSVersionEx(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GSVersionEx*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	{
		int iCount = 256;
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->version, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeClientVerReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ClientVerReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->seed_1))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->seed_2))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeClientVerReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ClientVerReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->seed_1))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->seed_2))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeNetDelayReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<NetDelayReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->gs_tick))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->gt_tick))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->sg_tick))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->ping))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeNetDelayReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<NetDelayReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->gs_tick))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->gt_tick))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->sg_tick))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->ping))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeNetDelayAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<NetDelayAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->sg_elpase))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->gt_elpase))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->gs_elpase))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->baidu_delay))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->taobao_delay))
		return -1;

	if(-1 == poNetData->AddString(pstIn->sg_id, sizeof(pstIn->sg_id)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeNetDelayAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<NetDelayAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->sg_elpase))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->gt_elpase))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->gs_elpase))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->baidu_delay))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->taobao_delay))
		return -1;

	if(-1 == poNetData->DelString(pstOut->sg_id, sizeof(pstOut->sg_id)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeClientVerNtfEx(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ClientVerNtfEx*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->seed_1))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->seed_2))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->client_ver))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeClientVerNtfEx(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ClientVerNtfEx*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->seed_1))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->seed_2))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->client_ver))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeClientVerReq2(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ClientVerReq2*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->version))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->data_len))
		return -1;

	{
		int iCount = (((4096) < ((int)pstIn->data_len)) ? (4096) : ((int)pstIn->data_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->data, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeClientVerReq2(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ClientVerReq2*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->version))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->data_len))
		return -1;

	{
		int iCount = (((4096) < ((int)pstOut->data_len)) ? (4096) : ((int)pstOut->data_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->data, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeClientVerAck2(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ClientVerAck2*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->version))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->data_len))
		return -1;

	{
		int iCount = (((4096) < ((int)pstIn->data_len)) ? (4096) : ((int)pstIn->data_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->data, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeClientVerAck2(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ClientVerAck2*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->version))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->data_len))
		return -1;

	{
		int iCount = (((4096) < ((int)pstOut->data_len)) ? (4096) : ((int)pstOut->data_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->data, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeNpcTalkReq3(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<NpcTalkReq3*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->npc_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->func, sizeof(pstIn->func)))
		return -1;

	{
		int iCount = 32;
		if(-1 == poNetData->AddBlob((char*)pstIn->check, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeNpcTalkReq3(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<NpcTalkReq3*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->npc_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->func, sizeof(pstOut->func)))
		return -1;

	{
		int iCount = 32;
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->check, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeNpcTalkAck3(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<NpcTalkAck3*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->width))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->height))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->npc_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->talk_len))
		return -1;

	{
		int iCount = (((7500) < ((int)pstIn->talk_len)) ? (7500) : ((int)pstIn->talk_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->talk, iCount*sizeof(char)))
			return -1;
	}
	if(-1 == poNetData->AddWord(pstIn->quest_state_num))
		return -1;

	for(int i = 0; i < 2; i++)
	{
		if(i >= (int)pstIn->quest_state_num)
			break;
		if(-1 == EnCodeQUEST_STATE_INFO(&pstIn->quest_states[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddChar(pstIn->comp))
		return -1;

	{
		int iCount = 32;
		if(-1 == poNetData->AddBlob((char*)pstIn->check, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeNpcTalkAck3(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<NpcTalkAck3*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->width))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->height))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->npc_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->talk_len))
		return -1;

	{
		int iCount = (((7500) < ((int)pstOut->talk_len)) ? (7500) : ((int)pstOut->talk_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->talk, iCount*sizeof(char)))
			return -1;
	}
	if(-1 == poNetData->DelWord(pstOut->quest_state_num))
		return -1;

	for(int i = 0; i < 2; i++)
	{
		if(i >= (int)pstOut->quest_state_num)
			break;
		if(-1 == DeCodeQUEST_STATE_INFO(&pstOut->quest_states[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelChar(pstOut->comp))
		return -1;

	{
		int iCount = 32;
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->check, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeAttrShowNtfEx(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<AttrShowNtfEx*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->actor))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->skill_id))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->target))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->actor_hp_ref))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->target_hp_ref))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->target_hp))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->actor_mp_ref))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->target_mp_ref))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeAttrShowNtfEx(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<AttrShowNtfEx*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->actor))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->skill_id))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->target))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->actor_hp_ref))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->target_hp_ref))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->target_hp))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->actor_mp_ref))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->target_mp_ref))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeEnterGSReqEx(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<EnterGSReqEx*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->entertype))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->roleguid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->fangchenmi))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->clienttype))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeEnterGSReqEx(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<EnterGSReqEx*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->entertype))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->roleguid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->fangchenmi))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->clienttype))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeReloginNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ReloginNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeReloginNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ReloginNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeBehaviorNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<BehaviorNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->version))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->zip))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->seed))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->size))
		return -1;

	{
		int iCount = (((7936) < ((int)pstIn->size)) ? (7936) : ((int)pstIn->size));
		if(-1 == poNetData->AddBlob((char*)pstIn->buf, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeBehaviorNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<BehaviorNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->version))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->zip))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->seed))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->size))
		return -1;

	{
		int iCount = (((7936) < ((int)pstOut->size)) ? (7936) : ((int)pstOut->size));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->buf, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeFashionReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<FashionReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->enable))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeFashionReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<FashionReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->enable))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeFashionNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<FashionNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->enable))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeFashionNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<FashionNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->enable))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeErrorNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ErrorNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->errmsg, sizeof(pstIn->errmsg)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeErrorNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ErrorNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeNpcTalkReqEx3(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<NpcTalkReqEx3*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->func, sizeof(pstIn->func)))
		return -1;

	{
		int iCount = 32;
		if(-1 == poNetData->AddBlob((char*)pstIn->check, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeNpcTalkReqEx3(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<NpcTalkReqEx3*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->func, sizeof(pstOut->func)))
		return -1;

	{
		int iCount = 32;
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->check, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeNpcTalkAckEx3(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<NpcTalkAckEx3*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->width))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->height))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->talk_len))
		return -1;

	{
		int iCount = (((8000) < ((int)pstIn->talk_len)) ? (8000) : ((int)pstIn->talk_len));
		if(-1 == poNetData->AddBlob((char*)pstIn->talk, iCount*sizeof(char)))
			return -1;
	}
	if(-1 == poNetData->AddChar(pstIn->comp))
		return -1;

	{
		int iCount = 32;
		if(-1 == poNetData->AddBlob((char*)pstIn->check, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeNpcTalkAckEx3(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<NpcTalkAckEx3*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->width))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->height))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->talk_len))
		return -1;

	{
		int iCount = (((8000) < ((int)pstOut->talk_len)) ? (8000) : ((int)pstOut->talk_len));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->talk, iCount*sizeof(char)))
			return -1;
	}
	if(-1 == poNetData->DelChar(pstOut->comp))
		return -1;

	{
		int iCount = 32;
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->check, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeSubmitForm2(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SubmitForm2*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->script_name, sizeof(pstIn->script_name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->function_name, sizeof(pstIn->function_name)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstIn->num)
			break;
		if(-1 == EnCodePARAM_INFO(&pstIn->info[i], poNetData))
			return -1;
	}

	{
		int iCount = 32;
		if(-1 == poNetData->AddBlob((char*)pstIn->check, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeSubmitForm2(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SubmitForm2*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->script_name, sizeof(pstOut->script_name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->function_name, sizeof(pstOut->function_name)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstOut->num)
			break;
		if(-1 == DeCodePARAM_INFO(&pstOut->info[i], poNetData))
			return -1;
	}

	{
		int iCount = 32;
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->check, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeSubmitFormAck2(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SubmitFormAck2*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->script_name, sizeof(pstIn->script_name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->result, sizeof(pstIn->result)))
		return -1;

	{
		int iCount = 32;
		if(-1 == poNetData->AddBlob((char*)pstIn->check, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeSubmitFormAck2(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SubmitFormAck2*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->script_name, sizeof(pstOut->script_name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->result, sizeof(pstOut->result)))
		return -1;

	{
		int iCount = 32;
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->check, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeRoleAddPointEx(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<RoleAddPointEx*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->hp))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->mp))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->phy_atk))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->mag_atk))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->tao_atk))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->phy_def))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->mag_def))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeRoleAddPointEx(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<RoleAddPointEx*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->hp))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->mp))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->phy_atk))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->mag_atk))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->tao_atk))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->phy_def))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->mag_def))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeGetClientCheckInfoReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GetClientCheckInfoReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeGetClientCheckInfoReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GetClientCheckInfoReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeGetClientCheckInfoAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GetClientCheckInfoAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->seed))
		return -1;

	if(-1 == poNetData->AddShort(pstIn->opt_num))
		return -1;

	{
		int iCount = (((128) < ((int)pstIn->opt_num)) ? (128) : ((int)pstIn->opt_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->opt, iCount*sizeof(int)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeGetClientCheckInfoAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GetClientCheckInfoAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->seed))
		return -1;

	if(-1 == poNetData->DelShort(pstOut->opt_num))
		return -1;

	{
		int iCount = (((128) < ((int)pstOut->opt_num)) ? (128) : ((int)pstOut->opt_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->opt, iCount*sizeof(int)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeGetMD5CheckListReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GetMD5CheckListReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->seed_1))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->seed_2))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->md5_list_num))
		return -1;

	for(int i = 0; i < 128; i++)
	{
		if(i >= (int)pstIn->md5_list_num)
			break;
		if(-1 == EnCodeCHECK_BUFF(&pstIn->md5_list[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeGetMD5CheckListReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GetMD5CheckListReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->seed_1))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->seed_2))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->md5_list_num))
		return -1;

	for(int i = 0; i < 128; i++)
	{
		if(i >= (int)pstOut->md5_list_num)
			break;
		if(-1 == DeCodeCHECK_BUFF(&pstOut->md5_list[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeGetMD5CheckListAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GetMD5CheckListAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->md5_list_num))
		return -1;

	{
		int iCount = (((128) < ((int)pstIn->md5_list_num)) ? (128) : ((int)pstIn->md5_list_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->check_num, iCount*sizeof(unsigned short)))
			return -1;
	}
	for(int i = 0; i < 128; i++)
	{
		if(i >= (int)pstIn->md5_list_num)
			break;
		if(-1 == EnCodeCHECK_BUFF(&pstIn->md5_list[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeGetMD5CheckListAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GetMD5CheckListAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->md5_list_num))
		return -1;

	{
		int iCount = (((128) < ((int)pstOut->md5_list_num)) ? (128) : ((int)pstOut->md5_list_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->check_num, iCount*sizeof(unsigned short)))
			return -1;
	}
	for(int i = 0; i < 128; i++)
	{
		if(i >= (int)pstOut->md5_list_num)
			break;
		if(-1 == DeCodeCHECK_BUFF(&pstOut->md5_list[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeDelayCloseNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<DelayCloseNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->delay))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeDelayCloseNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<DelayCloseNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->delay))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeFamilyJoinInviteReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<FamilyJoinInviteReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->action))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->family_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->invite_name, sizeof(pstIn->invite_name)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeFamilyJoinInviteReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<FamilyJoinInviteReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->action))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->family_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->invite_name, sizeof(pstOut->invite_name)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeFamilyJoinInviteAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<FamilyJoinInviteAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->action))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->family_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->invite_name, sizeof(pstIn->invite_name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->result))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeFamilyJoinInviteAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<FamilyJoinInviteAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->action))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->family_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->invite_name, sizeof(pstOut->invite_name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->result))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeFamilyRelationShipReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<FamilyRelationShipReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == poNetData->AddString(pstIn->family_name, sizeof(pstIn->family_name)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeFamilyRelationShipReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<FamilyRelationShipReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == poNetData->DelString(pstOut->family_name, sizeof(pstOut->family_name)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeFamilyRelationShipAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<FamilyRelationShipAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == poNetData->AddString(pstIn->family_name, sizeof(pstIn->family_name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->result))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeFamilyRelationShipAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<FamilyRelationShipAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == poNetData->DelString(pstOut->family_name, sizeof(pstOut->family_name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->result))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMonsterAppearNtf3(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MonsterAppearNtf3*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->monster_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->template_id))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->dst_x))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->dst_y))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->dir))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->cur_hp))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->max_hp))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->status))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->servant_lv))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->move_speed))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->buff_num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstIn->buff_num)
			break;
		if(-1 == EnCodeBUFF_INFO(&pstIn->buffs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddString(pstIn->master_name, sizeof(pstIn->master_name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->appear_type))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->attack_speed))
		return -1;

	if(-1 == EnCodeCUSTOM_INFO(&pstIn->custom, poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMonsterAppearNtf3(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MonsterAppearNtf3*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->monster_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->template_id))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->dst_x))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->dst_y))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->dir))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->cur_hp))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->max_hp))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->status))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->servant_lv))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->move_speed))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->buff_num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstOut->buff_num)
			break;
		if(-1 == DeCodeBUFF_INFO(&pstOut->buffs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelString(pstOut->master_name, sizeof(pstOut->master_name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->appear_type))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->attack_speed))
		return -1;

	if(-1 == DeCodeCUSTOM_INFO(&pstOut->custom, poNetData))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMonsterAppearNtf4(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MonsterAppearNtf4*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->monster_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->template_id))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->dst_x))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->dst_y))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->dir))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->cur_hp))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->max_hp))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->status))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->servant_lv))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->move_speed))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->buff_num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstIn->buff_num)
			break;
		if(-1 == EnCodeBUFF_INFO(&pstIn->buffs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddString(pstIn->master_name, sizeof(pstIn->master_name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->appear_type))
		return -1;

	if(-1 == poNetData->AddShort(pstIn->seed))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->attack_speed))
		return -1;

	if(-1 == EnCodeCUSTOM_INFO(&pstIn->custom, poNetData))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMonsterAppearNtf4(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MonsterAppearNtf4*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->monster_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->template_id))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->dst_x))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->dst_y))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->dir))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->cur_hp))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->max_hp))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->status))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->servant_lv))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->move_speed))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->buff_num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstOut->buff_num)
			break;
		if(-1 == DeCodeBUFF_INFO(&pstOut->buffs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelString(pstOut->master_name, sizeof(pstOut->master_name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->appear_type))
		return -1;

	if(-1 == poNetData->DelShort(pstOut->seed))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->attack_speed))
		return -1;

	if(-1 == DeCodeCUSTOM_INFO(&pstOut->custom, poNetData))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeGetAroundTeamReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GetAroundTeamReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeGetAroundTeamReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GetAroundTeamReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeGetAroundTeamAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GetAroundTeamAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->list_size))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstIn->list_size)
			break;
		if(-1 == EnCodeTEAM_MEMBER(&pstIn->list_data[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeGetAroundTeamAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GetAroundTeamAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->list_size))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstOut->list_size)
			break;
		if(-1 == DeCodeTEAM_MEMBER(&pstOut->list_data[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeMigrateRoleDataNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MigrateRoleDataNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->role_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->user_name, sizeof(pstIn->user_name)))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->dst_zone_id))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->status))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->errcode))
		return -1;

	if(-1 == poNetData->AddString(pstIn->errmsg, sizeof(pstIn->errmsg)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMigrateRoleDataNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MigrateRoleDataNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->role_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->user_name, sizeof(pstOut->user_name)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->dst_zone_id))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->status))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePlayerAppearNtf2(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PlayerAppearNtf2*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->gender))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->job))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->status))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->head))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->level))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_y))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->dir))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->hair))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->hair_color))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->body))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->weapon))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->wings))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->mount))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->weapon_effect))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->body_effect))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->mount_effect))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->hp))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->max_hp))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->mp))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->max_mp))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->pk))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->move_speed))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->attack_speed))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->title))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->has_team))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->stall))
		return -1;

	if(-1 == poNetData->AddString(pstIn->stall_name, sizeof(pstIn->stall_name)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->buff_num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstIn->buff_num)
			break;
		if(-1 == EnCodeBUFF_INFO(&pstIn->buffs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddString(pstIn->family_name, sizeof(pstIn->family_name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->castle_name, sizeof(pstIn->castle_name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->family_title, sizeof(pstIn->family_title)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->alias, sizeof(pstIn->alias)))
		return -1;

	if(-1 == EnCodeCUSTOM_INFO(&pstIn->custom, poNetData))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->appear_type))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->amulet))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->equip_num))
		return -1;

	for(int i = 0; i < 10; i++)
	{
		if(i >= (int)pstIn->equip_num)
			break;
		if(-1 == EnCodeEQUIP_INFO(&pstIn->equips[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodePlayerAppearNtf2(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PlayerAppearNtf2*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->gender))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->job))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->status))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->head))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->level))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_y))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->dir))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->hair))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->hair_color))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->body))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->weapon))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->wings))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->mount))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->weapon_effect))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->body_effect))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->mount_effect))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->hp))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->max_hp))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->mp))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->max_mp))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->pk))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->move_speed))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->attack_speed))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->title))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->has_team))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->stall))
		return -1;

	if(-1 == poNetData->DelString(pstOut->stall_name, sizeof(pstOut->stall_name)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->buff_num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstOut->buff_num)
			break;
		if(-1 == DeCodeBUFF_INFO(&pstOut->buffs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelString(pstOut->family_name, sizeof(pstOut->family_name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->castle_name, sizeof(pstOut->castle_name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->family_title, sizeof(pstOut->family_title)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->alias, sizeof(pstOut->alias)))
		return -1;

	if(-1 == DeCodeCUSTOM_INFO(&pstOut->custom, poNetData))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->appear_type))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->amulet))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->equip_num))
		return -1;

	for(int i = 0; i < 10; i++)
	{
		if(i >= (int)pstOut->equip_num)
			break;
		if(-1 == DeCodeEQUIP_INFO(&pstOut->equips[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeRoleAppNtf2(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<RoleAppNtf2*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->hair))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->hair_color))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->body))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->weapon))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->wings))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->mount))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->weapon_effect))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->body_effect))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->mount_effect))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->amulet))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->equip_num))
		return -1;

	for(int i = 0; i < 10; i++)
	{
		if(i >= (int)pstIn->equip_num)
			break;
		if(-1 == EnCodeEQUIP_INFO(&pstIn->equips[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeRoleAppNtf2(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<RoleAppNtf2*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->hair))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->hair_color))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->body))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->weapon))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->wings))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->mount))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->weapon_effect))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->body_effect))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->mount_effect))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->amulet))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->equip_num))
		return -1;

	for(int i = 0; i < 10; i++)
	{
		if(i >= (int)pstOut->equip_num)
			break;
		if(-1 == DeCodeEQUIP_INFO(&pstOut->equips[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeItemBatchDestroyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemBatchDestroyNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->num))
		return -1;

	{
		int iCount = (((200) < ((int)pstIn->num)) ? (200) : ((int)pstIn->num));
		if(-1 == poNetData->AddBlob((char*)pstIn->guids, iCount*sizeof(uint64_t)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeItemBatchDestroyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemBatchDestroyNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->num))
		return -1;

	{
		int iCount = (((200) < ((int)pstOut->num)) ? (200) : ((int)pstOut->num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->guids, iCount*sizeof(uint64_t)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeSubmitForm3(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SubmitForm3*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->form_count))
		return -1;

	{
		int iCount = 256;
		if(-1 == poNetData->AddBlob((char*)pstIn->script_name, iCount*sizeof(unsigned char)))
			return -1;
	}
	{
		int iCount = 256;
		if(-1 == poNetData->AddBlob((char*)pstIn->function_name, iCount*sizeof(unsigned char)))
			return -1;
	}
	if(-1 == poNetData->AddWord(pstIn->num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstIn->num)
			break;
		if(-1 == EnCodePARAM_INFO2(&pstIn->info[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeSubmitForm3(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SubmitForm3*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->form_count))
		return -1;

	{
		int iCount = 256;
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->script_name, iCount*sizeof(unsigned char)))
			return -1;
	}
	{
		int iCount = 256;
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->function_name, iCount*sizeof(unsigned char)))
			return -1;
	}
	if(-1 == poNetData->DelWord(pstOut->num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstOut->num)
			break;
		if(-1 == DeCodePARAM_INFO2(&pstOut->info[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeSubmitFormAck3(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SubmitFormAck3*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->script_name, sizeof(pstIn->script_name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->result, sizeof(pstIn->result)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSubmitFormAck3(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SubmitFormAck3*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->script_name, sizeof(pstOut->script_name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->result, sizeof(pstOut->result)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemAppearNtf3(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemAppearNtf3*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->template_id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_y))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->skill_id))
		return -1;

	if(-1 == poNetData->AddString(pstIn->item_name, sizeof(pstIn->item_name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->is_drop))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemAppearNtf3(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemAppearNtf3*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->template_id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_y))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->skill_id))
		return -1;

	if(-1 == poNetData->DelString(pstOut->item_name, sizeof(pstOut->item_name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->is_drop))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeItemAppearNtf4(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ItemAppearNtf4*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->template_id))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->dst_x))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->dst_y))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->skill_id))
		return -1;

	if(-1 == poNetData->AddString(pstIn->item_name, sizeof(pstIn->item_name)))
		return -1;

	if(-1 == poNetData->AddShort(pstIn->seed))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->is_drop))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeItemAppearNtf4(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ItemAppearNtf4*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->template_id))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->dst_x))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->dst_y))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->skill_id))
		return -1;

	if(-1 == poNetData->DelString(pstOut->item_name, sizeof(pstOut->item_name)))
		return -1;

	if(-1 == poNetData->DelShort(pstOut->seed))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->is_drop))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeInnerForceLevelUpReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<InnerForceLevelUpReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeInnerForceLevelUpReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<InnerForceLevelUpReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeInnerForceLevelUpAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<InnerForceLevelUpAck*>(pHost);

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
int DeCodeInnerForceLevelUpAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<InnerForceLevelUpAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeClientFangChenMiNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ClientFangChenMiNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeClientFangChenMiNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ClientFangChenMiNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeDelegateMineAck2(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<DelegateMineAck2*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->count_buy))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->count_sell))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstIn->count_buy)
			break;
		if(-1 == EnCodeDELEGATE_BUY_ITEM2(&pstIn->buy_items[i], poNetData))
			return -1;
	}

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstIn->count_sell)
			break;
		if(-1 == EnCodeDELEGATE_SELL_ITEM(&pstIn->sell_items[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeDelegateMineAck2(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<DelegateMineAck2*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->count_buy))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->count_sell))
		return -1;

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstOut->count_buy)
			break;
		if(-1 == DeCodeDELEGATE_BUY_ITEM2(&pstOut->buy_items[i], poNetData))
			return -1;
	}

	for(int i = 0; i < 5; i++)
	{
		if(i >= (int)pstOut->count_sell)
			break;
		if(-1 == DeCodeDELEGATE_SELL_ITEM(&pstOut->sell_items[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeDelegateBuyListAck2(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<DelegateBuyListAck2*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->type))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->subtype))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->total))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->start))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->count))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstIn->count)
			break;
		if(-1 == EnCodeDELEGATE_BUY_ITEM2(&pstIn->items[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeDelegateBuyListAck2(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<DelegateBuyListAck2*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->type))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->subtype))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->total))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->start))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->count))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstOut->count)
			break;
		if(-1 == DeCodeDELEGATE_BUY_ITEM2(&pstOut->items[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeFashionWeaponReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<FashionWeaponReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->enable))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeFashionWeaponReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<FashionWeaponReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->enable))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeFashionWeaponNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<FashionWeaponNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->enable))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeFashionWeaponNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<FashionWeaponNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->enable))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePlayerAppearNtf3(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PlayerAppearNtf3*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->name, sizeof(pstIn->name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->gender))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->job))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->status))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->head))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->level))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_x))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->dst_y))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->dir))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->hair))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->hair_color))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->body))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->weapon))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->wings))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->mount))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->weapon_effect))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->body_effect))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->mount_effect))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->hp))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->max_hp))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->mp))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->max_mp))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->pk))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->move_speed))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->attack_speed))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->title))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->has_team))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->stall))
		return -1;

	if(-1 == poNetData->AddString(pstIn->stall_name, sizeof(pstIn->stall_name)))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->buff_num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstIn->buff_num)
			break;
		if(-1 == EnCodeBUFF_INFO(&pstIn->buffs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddString(pstIn->family_name, sizeof(pstIn->family_name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->castle_name, sizeof(pstIn->castle_name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->family_title, sizeof(pstIn->family_title)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->alias, sizeof(pstIn->alias)))
		return -1;

	if(-1 == EnCodeCUSTOM_INFO(&pstIn->custom, poNetData))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->appear_type))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->amulet))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->equip_num))
		return -1;

	for(int i = 0; i < 10; i++)
	{
		if(i >= (int)pstIn->equip_num)
			break;
		if(-1 == EnCodeEQUIP_INFO(&pstIn->equips[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddDword(pstIn->inner_force))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->max_inner_force))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->reserve_num))
		return -1;

	{
		int iCount = (((10) < ((int)pstIn->reserve_num)) ? (10) : ((int)pstIn->reserve_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->reserve_values, iCount*sizeof(unsigned int)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodePlayerAppearNtf3(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PlayerAppearNtf3*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelString(pstOut->name, sizeof(pstOut->name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->gender))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->job))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->status))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->head))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->level))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_x))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->dst_y))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->dir))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->hair))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->hair_color))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->body))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->weapon))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->wings))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->mount))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->weapon_effect))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->body_effect))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->mount_effect))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->hp))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->max_hp))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->mp))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->max_mp))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->pk))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->move_speed))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->attack_speed))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->title))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->has_team))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->stall))
		return -1;

	if(-1 == poNetData->DelString(pstOut->stall_name, sizeof(pstOut->stall_name)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->buff_num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstOut->buff_num)
			break;
		if(-1 == DeCodeBUFF_INFO(&pstOut->buffs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelString(pstOut->family_name, sizeof(pstOut->family_name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->castle_name, sizeof(pstOut->castle_name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->family_title, sizeof(pstOut->family_title)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->alias, sizeof(pstOut->alias)))
		return -1;

	if(-1 == DeCodeCUSTOM_INFO(&pstOut->custom, poNetData))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->appear_type))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->amulet))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->equip_num))
		return -1;

	for(int i = 0; i < 10; i++)
	{
		if(i >= (int)pstOut->equip_num)
			break;
		if(-1 == DeCodeEQUIP_INFO(&pstOut->equips[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelDword(pstOut->inner_force))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->max_inner_force))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->reserve_num))
		return -1;

	{
		int iCount = (((10) < ((int)pstOut->reserve_num)) ? (10) : ((int)pstOut->reserve_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->reserve_values, iCount*sizeof(unsigned int)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeMonsterAppearNtf5(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MonsterAppearNtf5*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->monster_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->template_id))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->dst_x))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->dst_y))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->dir))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->cur_hp))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->max_hp))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->status))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->servant_lv))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->move_speed))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->buff_num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstIn->buff_num)
			break;
		if(-1 == EnCodeBUFF_INFO(&pstIn->buffs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddString(pstIn->master_name, sizeof(pstIn->master_name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->appear_type))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->attack_speed))
		return -1;

	if(-1 == EnCodeCUSTOM_INFO(&pstIn->custom, poNetData))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->inner_force))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->max_inner_force))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->reserve_num))
		return -1;

	{
		int iCount = (((10) < ((int)pstIn->reserve_num)) ? (10) : ((int)pstIn->reserve_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->reserve_values, iCount*sizeof(unsigned int)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeMonsterAppearNtf5(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MonsterAppearNtf5*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->monster_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->template_id))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->dst_x))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->dst_y))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->dir))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->cur_hp))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->max_hp))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->status))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->servant_lv))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->move_speed))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->buff_num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstOut->buff_num)
			break;
		if(-1 == DeCodeBUFF_INFO(&pstOut->buffs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelString(pstOut->master_name, sizeof(pstOut->master_name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->appear_type))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->attack_speed))
		return -1;

	if(-1 == DeCodeCUSTOM_INFO(&pstOut->custom, poNetData))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->inner_force))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->max_inner_force))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->reserve_num))
		return -1;

	{
		int iCount = (((10) < ((int)pstOut->reserve_num)) ? (10) : ((int)pstOut->reserve_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->reserve_values, iCount*sizeof(unsigned int)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeMonsterAppearNtf6(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MonsterAppearNtf6*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->monster_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->template_id))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->dst_x))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->dst_y))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->dir))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->cur_hp))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->max_hp))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->status))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->servant_lv))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->move_speed))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->buff_num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstIn->buff_num)
			break;
		if(-1 == EnCodeBUFF_INFO(&pstIn->buffs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddString(pstIn->master_name, sizeof(pstIn->master_name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->appear_type))
		return -1;

	if(-1 == poNetData->AddShort(pstIn->seed))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->attack_speed))
		return -1;

	if(-1 == EnCodeCUSTOM_INFO(&pstIn->custom, poNetData))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->inner_force))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->max_inner_force))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->reserve_num))
		return -1;

	{
		int iCount = (((10) < ((int)pstIn->reserve_num)) ? (10) : ((int)pstIn->reserve_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->reserve_values, iCount*sizeof(unsigned int)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeMonsterAppearNtf6(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MonsterAppearNtf6*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->monster_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->template_id))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->dst_x))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->dst_y))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->dir))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->cur_hp))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->max_hp))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->status))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->servant_lv))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->move_speed))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->buff_num))
		return -1;

	for(int i = 0; i < 50; i++)
	{
		if(i >= (int)pstOut->buff_num)
			break;
		if(-1 == DeCodeBUFF_INFO(&pstOut->buffs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelString(pstOut->master_name, sizeof(pstOut->master_name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->appear_type))
		return -1;

	if(-1 == poNetData->DelShort(pstOut->seed))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->attack_speed))
		return -1;

	if(-1 == DeCodeCUSTOM_INFO(&pstOut->custom, poNetData))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->inner_force))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->max_inner_force))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->reserve_num))
		return -1;

	{
		int iCount = (((10) < ((int)pstOut->reserve_num)) ? (10) : ((int)pstOut->reserve_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->reserve_values, iCount*sizeof(unsigned int)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeCaptchaReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<CaptchaReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->seed))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->type))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->timeout))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->qsize))
		return -1;

	{
		int iCount = (((256) < ((int)pstIn->qsize)) ? (256) : ((int)pstIn->qsize));
		if(-1 == poNetData->AddBlob((char*)pstIn->qvalue, iCount*sizeof(char)))
			return -1;
	}
	if(-1 == poNetData->AddWord(pstIn->size))
		return -1;

	{
		int iCount = (((4096) < ((int)pstIn->size)) ? (4096) : ((int)pstIn->size));
		if(-1 == poNetData->AddBlob((char*)pstIn->value, iCount*sizeof(char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeCaptchaReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<CaptchaReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->seed))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->type))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->timeout))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->qsize))
		return -1;

	{
		int iCount = (((256) < ((int)pstOut->qsize)) ? (256) : ((int)pstOut->qsize));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->qvalue, iCount*sizeof(char)))
			return -1;
	}
	if(-1 == poNetData->DelWord(pstOut->size))
		return -1;

	{
		int iCount = (((4096) < ((int)pstOut->size)) ? (4096) : ((int)pstOut->size));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->value, iCount*sizeof(char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeCaptchaAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<CaptchaAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->check1))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->size1))
		return -1;

	{
		int iCount = (((256) < ((int)pstIn->size1)) ? (256) : ((int)pstIn->size1));
		if(-1 == poNetData->AddBlob((char*)pstIn->value1, iCount*sizeof(char)))
			return -1;
	}
	if(-1 == poNetData->AddByte(pstIn->check2))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->size2))
		return -1;

	{
		int iCount = (((256) < ((int)pstIn->size2)) ? (256) : ((int)pstIn->size2));
		if(-1 == poNetData->AddBlob((char*)pstIn->value2, iCount*sizeof(char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeCaptchaAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<CaptchaAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->check1))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->size1))
		return -1;

	{
		int iCount = (((256) < ((int)pstOut->size1)) ? (256) : ((int)pstOut->size1));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->value1, iCount*sizeof(char)))
			return -1;
	}
	if(-1 == poNetData->DelByte(pstOut->check2))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->size2))
		return -1;

	{
		int iCount = (((256) < ((int)pstOut->size2)) ? (256) : ((int)pstOut->size2));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->value2, iCount*sizeof(char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeAgentKeyReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<AgentKeyReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeAgentKeyReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<AgentKeyReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeAgentKeyAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<AgentKeyAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->key, sizeof(pstIn->key)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeAgentKeyAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<AgentKeyAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->key, sizeof(pstOut->key)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodePlatformInfoNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<PlatformInfoNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->platform, sizeof(pstIn->platform)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->info, sizeof(pstIn->info)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodePlatformInfoNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<PlatformInfoNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->platform, sizeof(pstOut->platform)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->info, sizeof(pstOut->info)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeAttrShowNtf2(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<AttrShowNtf2*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->actor))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->skill_id))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->target))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->actor_hp_ref))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->target_hp_ref))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->target_hp))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->target_mp))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->reserve_size))
		return -1;

	{
		int iCount = (((10) < ((int)pstIn->reserve_size)) ? (10) : ((int)pstIn->reserve_size));
		if(-1 == poNetData->AddBlob((char*)pstIn->reserve, iCount*sizeof(int)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeAttrShowNtf2(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<AttrShowNtf2*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->actor))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->skill_id))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->target))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->actor_hp_ref))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->target_hp_ref))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->target_hp))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->target_mp))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->reserve_size))
		return -1;

	{
		int iCount = (((10) < ((int)pstOut->reserve_size)) ? (10) : ((int)pstOut->reserve_size));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->reserve, iCount*sizeof(int)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeAttrShowNtfEx2(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<AttrShowNtfEx2*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->actor))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->skill_id))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->target))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->actor_hp_ref))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->target_hp_ref))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->target_hp))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->target_mp))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->actor_mp_ref))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->target_mp_ref))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->reserve_size))
		return -1;

	{
		int iCount = (((10) < ((int)pstIn->reserve_size)) ? (10) : ((int)pstIn->reserve_size));
		if(-1 == poNetData->AddBlob((char*)pstIn->reserve, iCount*sizeof(int)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeAttrShowNtfEx2(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<AttrShowNtfEx2*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->actor))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->skill_id))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->target))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->actor_hp_ref))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->target_hp_ref))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->target_hp))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->target_mp))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->actor_mp_ref))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->target_mp_ref))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->reserve_size))
		return -1;

	{
		int iCount = (((10) < ((int)pstOut->reserve_size)) ? (10) : ((int)pstOut->reserve_size));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->reserve, iCount*sizeof(int)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeBehaviorReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<BehaviorReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->seed))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeBehaviorReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<BehaviorReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->seed))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeFangChenMiNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<FangChenMiNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->type))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeFangChenMiNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<FangChenMiNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->type))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeNpcShopIdsNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<NpcShopIdsNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->size))
		return -1;

	{
		int iCount = (((20) < ((int)pstIn->size)) ? (20) : ((int)pstIn->size));
		if(-1 == poNetData->AddBlob((char*)pstIn->shops, iCount*sizeof(unsigned short)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeNpcShopIdsNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<NpcShopIdsNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->size))
		return -1;

	{
		int iCount = (((20) < ((int)pstOut->size)) ? (20) : ((int)pstOut->size));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->shops, iCount*sizeof(unsigned short)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeCreateMobaRoomReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<CreateMobaRoomReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->room_mode))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->vs_num))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->map_id))
		return -1;

	if(-1 == poNetData->AddString(pstIn->room_pwd, sizeof(pstIn->room_pwd)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->room_name, sizeof(pstIn->room_name)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeCreateMobaRoomReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<CreateMobaRoomReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->room_mode))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->vs_num))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->map_id))
		return -1;

	if(-1 == poNetData->DelString(pstOut->room_pwd, sizeof(pstOut->room_pwd)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->room_name, sizeof(pstOut->room_name)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeCreateMobaRoomAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<CreateMobaRoomAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->room_id))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->errcode))
		return -1;

	if(-1 == poNetData->AddString(pstIn->errmsg, sizeof(pstIn->errmsg)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeCreateMobaRoomAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<CreateMobaRoomAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->room_id))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeEnterMobaRoomReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<EnterMobaRoomReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->room_id))
		return -1;

	if(-1 == poNetData->AddString(pstIn->room_pwd, sizeof(pstIn->room_pwd)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeEnterMobaRoomReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<EnterMobaRoomReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->room_id))
		return -1;

	if(-1 == poNetData->DelString(pstOut->room_pwd, sizeof(pstOut->room_pwd)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeEnterMobaRoomAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<EnterMobaRoomAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->room_id))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->errcode))
		return -1;

	if(-1 == poNetData->AddString(pstIn->errmsg, sizeof(pstIn->errmsg)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeEnterMobaRoomAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<EnterMobaRoomAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->room_id))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeExitMobaRoomReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ExitMobaRoomReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeExitMobaRoomReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ExitMobaRoomReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeExitMobaRoomAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ExitMobaRoomAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->room_id))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->errcode))
		return -1;

	if(-1 == poNetData->AddString(pstIn->errmsg, sizeof(pstIn->errmsg)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeExitMobaRoomAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ExitMobaRoomAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->room_id))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeGetMobaRoomListReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GetMobaRoomListReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->begin_pos))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeGetMobaRoomListReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GetMobaRoomListReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->begin_pos))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomListAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomListAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->begin_pos))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->all_pos))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->room_num))
		return -1;

	for(int i = 0; i < 64; i++)
	{
		if(i >= (int)pstIn->room_num)
			break;
		if(-1 == EnCodeMOBA_ROOM_INFO(&pstIn->room_list[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeMobaRoomListAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomListAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->begin_pos))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->all_pos))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->room_num))
		return -1;

	for(int i = 0; i < 64; i++)
	{
		if(i >= (int)pstOut->room_num)
			break;
		if(-1 == DeCodeMOBA_ROOM_INFO(&pstOut->room_list[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeMobaRoomMemberListNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomMemberListNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->room_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->member_num))
		return -1;

	for(int i = 0; i < 256; i++)
	{
		if(i >= (int)pstIn->member_num)
			break;
		if(-1 == EnCodeMOBA_ROOM_MEMBER_INFO(&pstIn->member_list[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeMobaRoomMemberListNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomMemberListNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->room_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->member_num))
		return -1;

	for(int i = 0; i < 256; i++)
	{
		if(i >= (int)pstOut->member_num)
			break;
		if(-1 == DeCodeMOBA_ROOM_MEMBER_INFO(&pstOut->member_list[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeGetMobaMemberListReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GetMobaMemberListReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->room_id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeGetMobaMemberListReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GetMobaMemberListReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->room_id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomKickReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomKickReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMobaRoomKickReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomKickReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomKickAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomKickAck*>(pHost);

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
int DeCodeMobaRoomKickAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomKickAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomKickedNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomKickedNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMobaRoomKickedNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomKickedNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomCampReadyReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomCampReadyReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMobaRoomCampReadyReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomCampReadyReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomCampReadyAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomCampReadyAck*>(pHost);

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
int DeCodeMobaRoomCampReadyAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomCampReadyAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomCampReadyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomCampReadyNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->camp))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->yes))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMobaRoomCampReadyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomCampReadyNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->camp))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->yes))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomGameStartNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomGameStartNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->room_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->success))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMobaRoomGameStartNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomGameStartNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->room_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->success))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomSetViceHostReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomSetViceHostReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMobaRoomSetViceHostReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomSetViceHostReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomSetViceHostAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomSetViceHostAck*>(pHost);

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
int DeCodeMobaRoomSetViceHostAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomSetViceHostAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomToggleCampReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomToggleCampReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMobaRoomToggleCampReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomToggleCampReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomToggleCampAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomToggleCampAck*>(pHost);

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
int DeCodeMobaRoomToggleCampAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomToggleCampAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomDestroyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomDestroyNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->room_id))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMobaRoomDestroyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomDestroyNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->room_id))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomMemberReadyReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomMemberReadyReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMobaRoomMemberReadyReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomMemberReadyReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomMemberReadyAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomMemberReadyAck*>(pHost);

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
int DeCodeMobaRoomMemberReadyAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomMemberReadyAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomMemberReadyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomMemberReadyNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->guid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->yes))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMobaRoomMemberReadyNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomMemberReadyNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->guid))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->yes))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomUpdateNameAndPasswordReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomUpdateNameAndPasswordReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->room_name, sizeof(pstIn->room_name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->room_pwd, sizeof(pstIn->room_pwd)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMobaRoomUpdateNameAndPasswordReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomUpdateNameAndPasswordReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->room_name, sizeof(pstOut->room_name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->room_pwd, sizeof(pstOut->room_pwd)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomUpdateNameAndPasswordAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomUpdateNameAndPasswordAck*>(pHost);

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
int DeCodeMobaRoomUpdateNameAndPasswordAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomUpdateNameAndPasswordAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomNameUpdateNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomNameUpdateNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddInt(pstIn->room_id))
		return -1;

	if(-1 == poNetData->AddString(pstIn->room_name, sizeof(pstIn->room_name)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMobaRoomNameUpdateNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomNameUpdateNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->room_id))
		return -1;

	if(-1 == poNetData->DelString(pstOut->room_name, sizeof(pstOut->room_name)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomChangeCampAndPosReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomChangeCampAndPosReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->change_camp))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->pos))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeMobaRoomChangeCampAndPosReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomChangeCampAndPosReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->change_camp))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->pos))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeMobaRoomChangeCampAndPosAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<MobaRoomChangeCampAndPosAck*>(pHost);

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
int DeCodeMobaRoomChangeCampAndPosAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<MobaRoomChangeCampAndPosAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelInt(pstOut->errcode))
		return -1;

	if(-1 == poNetData->DelString(pstOut->errmsg, sizeof(pstOut->errmsg)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeReloginRefreshReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<ReloginRefreshReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeReloginRefreshReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<ReloginRefreshReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeGameGuardReq(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GameGuardReq*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->size))
		return -1;

	{
		int iCount = (((4224) < ((int)pstIn->size)) ? (4224) : ((int)pstIn->size));
		if(-1 == poNetData->AddBlob((char*)pstIn->content, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeGameGuardReq(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GameGuardReq*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->size))
		return -1;

	{
		int iCount = (((4224) < ((int)pstOut->size)) ? (4224) : ((int)pstOut->size));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->content, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeGameGuardAck(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GameGuardAck*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->size))
		return -1;

	{
		int iCount = (((4224) < ((int)pstIn->size)) ? (4224) : ((int)pstIn->size));
		if(-1 == poNetData->AddBlob((char*)pstIn->content, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeGameGuardAck(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GameGuardAck*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->size))
		return -1;

	{
		int iCount = (((4224) < ((int)pstOut->size)) ? (4224) : ((int)pstOut->size));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->content, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeGameGuardCheckFailedNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GameGuardCheckFailedNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeGameGuardCheckFailedNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GameGuardCheckFailedNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeGameGuardHackRpt(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GameGuardHackRpt*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->size))
		return -1;

	{
		int iCount = (((4224) < ((int)pstIn->size)) ? (4224) : ((int)pstIn->size));
		if(-1 == poNetData->AddBlob((char*)pstIn->content, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeGameGuardHackRpt(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GameGuardHackRpt*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->size))
		return -1;

	{
		int iCount = (((4224) < ((int)pstOut->size)) ? (4224) : ((int)pstOut->size));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->content, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeGameGuardHeartBeat(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<GameGuardHeartBeat*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->seed))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->size))
		return -1;

	{
		int iCount = (((6144) < ((int)pstIn->size)) ? (6144) : ((int)pstIn->size));
		if(-1 == poNetData->AddBlob((char*)pstIn->content, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeGameGuardHeartBeat(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<GameGuardHeartBeat*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->seed))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->size))
		return -1;

	{
		int iCount = (((6144) < ((int)pstOut->size)) ? (6144) : ((int)pstOut->size));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->content, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeBangcleHeartBeat(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<BangcleHeartBeat*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->seed))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->size))
		return -1;

	{
		int iCount = (((6144) < ((int)pstIn->size)) ? (6144) : ((int)pstIn->size));
		if(-1 == poNetData->AddBlob((char*)pstIn->content, iCount*sizeof(unsigned char)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeBangcleHeartBeat(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<BangcleHeartBeat*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->seed))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->size))
		return -1;

	{
		int iCount = (((6144) < ((int)pstOut->size)) ? (6144) : ((int)pstOut->size));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->content, iCount*sizeof(unsigned char)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeTradeStallSetBuyList(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeStallSetBuyList*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->buy_num))
		return -1;

	{
		int iCount = (((25) < ((int)pstIn->buy_num)) ? (25) : ((int)pstIn->buy_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->item_ids, iCount*sizeof(unsigned short)))
			return -1;
	}
	{
		int iCount = (((25) < ((int)pstIn->buy_num)) ? (25) : ((int)pstIn->buy_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->item_nums, iCount*sizeof(unsigned short)))
			return -1;
	}
	{
		int iCount = (((25) < ((int)pstIn->buy_num)) ? (25) : ((int)pstIn->buy_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->price_types, iCount*sizeof(unsigned char)))
			return -1;
	}
	{
		int iCount = (((25) < ((int)pstIn->buy_num)) ? (25) : ((int)pstIn->buy_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->item_prices, iCount*sizeof(int64_t)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeTradeStallSetBuyList(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeStallSetBuyList*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->buy_num))
		return -1;

	{
		int iCount = (((25) < ((int)pstOut->buy_num)) ? (25) : ((int)pstOut->buy_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->item_ids, iCount*sizeof(unsigned short)))
			return -1;
	}
	{
		int iCount = (((25) < ((int)pstOut->buy_num)) ? (25) : ((int)pstOut->buy_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->item_nums, iCount*sizeof(unsigned short)))
			return -1;
	}
	{
		int iCount = (((25) < ((int)pstOut->buy_num)) ? (25) : ((int)pstOut->buy_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->price_types, iCount*sizeof(unsigned char)))
			return -1;
	}
	{
		int iCount = (((25) < ((int)pstOut->buy_num)) ? (25) : ((int)pstOut->buy_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->item_prices, iCount*sizeof(int64_t)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeTradeStallQueryBuyGoodsNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeStallQueryBuyGoodsNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->buy_num))
		return -1;

	{
		int iCount = (((25) < ((int)pstIn->buy_num)) ? (25) : ((int)pstIn->buy_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->item_ids, iCount*sizeof(unsigned short)))
			return -1;
	}
	{
		int iCount = (((25) < ((int)pstIn->buy_num)) ? (25) : ((int)pstIn->buy_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->item_nums, iCount*sizeof(unsigned short)))
			return -1;
	}
	{
		int iCount = (((25) < ((int)pstIn->buy_num)) ? (25) : ((int)pstIn->buy_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->price_types, iCount*sizeof(unsigned char)))
			return -1;
	}
	{
		int iCount = (((25) < ((int)pstIn->buy_num)) ? (25) : ((int)pstIn->buy_num));
		if(-1 == poNetData->AddBlob((char*)pstIn->item_prices, iCount*sizeof(int64_t)))
			return -1;
	}
	return poNetData->GetDataLen();
}
int DeCodeTradeStallQueryBuyGoodsNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeStallQueryBuyGoodsNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->buy_num))
		return -1;

	{
		int iCount = (((25) < ((int)pstOut->buy_num)) ? (25) : ((int)pstOut->buy_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->item_ids, iCount*sizeof(unsigned short)))
			return -1;
	}
	{
		int iCount = (((25) < ((int)pstOut->buy_num)) ? (25) : ((int)pstOut->buy_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->item_nums, iCount*sizeof(unsigned short)))
			return -1;
	}
	{
		int iCount = (((25) < ((int)pstOut->buy_num)) ? (25) : ((int)pstOut->buy_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->price_types, iCount*sizeof(unsigned char)))
			return -1;
	}
	{
		int iCount = (((25) < ((int)pstOut->buy_num)) ? (25) : ((int)pstOut->buy_num));
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->item_prices, iCount*sizeof(int64_t)))
			return -1;
	}
	return sizeof(*pstOut);
}
int EnCodeTradeStallSell(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeStallSell*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->player_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_amount))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeStallSell(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeStallSell*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->player_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_amount))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTradeStallSellNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TradeStallSellNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->buyer_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->seller_guid))
		return -1;

	if(-1 == poNetData->AddQword(pstIn->item_guid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_id))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->item_amount))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->price_type))
		return -1;

	if(-1 == poNetData->AddInt64(pstIn->price))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTradeStallSellNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TradeStallSellNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->buyer_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->seller_guid))
		return -1;

	if(-1 == poNetData->DelQword(pstOut->item_guid))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_id))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->item_amount))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->price_type))
		return -1;

	if(-1 == poNetData->DelInt64(pstOut->price))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTaobaoNpcShopReqEx(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TaobaoNpcShopReqEx*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->shop_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->item_type))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->item_index))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->item_count))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeTaobaoNpcShopReqEx(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TaobaoNpcShopReqEx*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->shop_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->item_type))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->item_index))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->item_count))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeTaobaoNpcShopAckEx(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<TaobaoNpcShopAckEx*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->shop_id))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->item_type))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->total_count))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->item_index))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->item_count))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstIn->item_count)
			break;
		if(-1 == EnCodeTAOBAO_ITEM_INFO(&pstIn->item_list[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeTaobaoNpcShopAckEx(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<TaobaoNpcShopAckEx*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->shop_id))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->item_type))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->total_count))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->item_index))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->item_count))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstOut->item_count)
			break;
		if(-1 == DeCodeTAOBAO_ITEM_INFO(&pstOut->item_list[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeSkillCDChangedNtf(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SkillCDChangedNtf*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->skill_id))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->new_cd))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSkillCDChangedNtf(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SkillCDChangedNtf*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->skill_id))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->new_cd))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSubmitForm4(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SubmitForm4*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->form_count))
		return -1;

	{
		int iCount = 256;
		if(-1 == poNetData->AddBlob((char*)pstIn->script_name, iCount*sizeof(unsigned char)))
			return -1;
	}
	{
		int iCount = 256;
		if(-1 == poNetData->AddBlob((char*)pstIn->function_name, iCount*sizeof(unsigned char)))
			return -1;
	}
	if(-1 == poNetData->AddWord(pstIn->num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstIn->num)
			break;
		if(-1 == EnCodePARAM_INFO2(&pstIn->info[i], poNetData))
			return -1;
	}

	return poNetData->GetDataLen();
}
int DeCodeSubmitForm4(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SubmitForm4*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->form_count))
		return -1;

	{
		int iCount = 256;
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->script_name, iCount*sizeof(unsigned char)))
			return -1;
	}
	{
		int iCount = 256;
		if(iCount < 0)
			return -1;
		if(-1 == poNetData->DelBlob((char*)pstOut->function_name, iCount*sizeof(unsigned char)))
			return -1;
	}
	if(-1 == poNetData->DelWord(pstOut->num))
		return -1;

	for(int i = 0; i < 100; i++)
	{
		if(i >= (int)pstOut->num)
			break;
		if(-1 == DeCodePARAM_INFO2(&pstOut->info[i], poNetData))
			return -1;
	}

	return sizeof(*pstOut);
}
int EnCodeSubmitFormAck4(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<SubmitFormAck4*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddString(pstIn->script_name, sizeof(pstIn->script_name)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->result, sizeof(pstIn->result)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeSubmitFormAck4(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<SubmitFormAck4*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->script_name, sizeof(pstOut->script_name)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->result, sizeof(pstOut->result)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeQuestAddNtf2(void* pHost, CNetData* poNetData)
{
	auto* pstIn = reinterpret_cast<QuestAddNtf2*>(pHost);

	if(-1==poNetData->AddWord(pstIn->moudleid))
		return -1;

	if(-1==poNetData->AddWord(pstIn->protocolid))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->quest_id))
		return -1;

	if(-1 == poNetData->AddString(pstIn->quest_name, sizeof(pstIn->quest_name)))
		return -1;

	if(-1 == poNetData->AddByte(pstIn->quest_type))
		return -1;

	if(-1 == poNetData->AddWord(pstIn->group_huntings_len))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstIn->group_huntings_len)
			break;
		if(-1 == EnCodeQUEST_HUNTING_INFO(&pstIn->group_huntings[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddWord(pstIn->huntings_len))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstIn->huntings_len)
			break;
		if(-1 == EnCodeQUEST_HUNTING_INFO(&pstIn->huntings[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddWord(pstIn->huntlevels_len))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstIn->huntlevels_len)
			break;
		if(-1 == EnCodeQUEST_HUNTLEVEL_INFO(&pstIn->huntlevels[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddWord(pstIn->group_items_len))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstIn->group_items_len)
			break;
		if(-1 == EnCodeQUEST_ITEM_INFO(&pstIn->group_items[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddWord(pstIn->collect_items_len))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstIn->collect_items_len)
			break;
		if(-1 == EnCodeQUEST_ITEM_INFO(&pstIn->collect_items[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddWord(pstIn->apply_items_len))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstIn->apply_items_len)
			break;
		if(-1 == EnCodeQUEST_ITEM_INFO(&pstIn->apply_items[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddWord(pstIn->npcs_len))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstIn->npcs_len)
			break;
		if(-1 == EnCodeQUEST_NPC_INFO(&pstIn->npcs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->AddByte(pstIn->track_enabled))
		return -1;

	if(-1 == poNetData->AddDword(pstIn->life))
		return -1;

	if(-1 == poNetData->AddString(pstIn->progressing, sizeof(pstIn->progressing)))
		return -1;

	if(-1 == poNetData->AddString(pstIn->accomplishing, sizeof(pstIn->accomplishing)))
		return -1;

	return poNetData->GetDataLen();
}
int DeCodeQuestAddNtf2(void* pHost, CNetData* poNetData)
{
	auto* pstOut = reinterpret_cast<QuestAddNtf2*>(pHost);

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
		return -1;

	if(-1==poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->quest_id))
		return -1;

	if(-1 == poNetData->DelString(pstOut->quest_name, sizeof(pstOut->quest_name)))
		return -1;

	if(-1 == poNetData->DelByte(pstOut->quest_type))
		return -1;

	if(-1 == poNetData->DelWord(pstOut->group_huntings_len))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstOut->group_huntings_len)
			break;
		if(-1 == DeCodeQUEST_HUNTING_INFO(&pstOut->group_huntings[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelWord(pstOut->huntings_len))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstOut->huntings_len)
			break;
		if(-1 == DeCodeQUEST_HUNTING_INFO(&pstOut->huntings[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelWord(pstOut->huntlevels_len))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstOut->huntlevels_len)
			break;
		if(-1 == DeCodeQUEST_HUNTLEVEL_INFO(&pstOut->huntlevels[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelWord(pstOut->group_items_len))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstOut->group_items_len)
			break;
		if(-1 == DeCodeQUEST_ITEM_INFO(&pstOut->group_items[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelWord(pstOut->collect_items_len))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstOut->collect_items_len)
			break;
		if(-1 == DeCodeQUEST_ITEM_INFO(&pstOut->collect_items[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelWord(pstOut->apply_items_len))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstOut->apply_items_len)
			break;
		if(-1 == DeCodeQUEST_ITEM_INFO(&pstOut->apply_items[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelWord(pstOut->npcs_len))
		return -1;

	for(int i = 0; i < 20; i++)
	{
		if(i >= (int)pstOut->npcs_len)
			break;
		if(-1 == DeCodeQUEST_NPC_INFO(&pstOut->npcs[i], poNetData))
			return -1;
	}

	if(-1 == poNetData->DelByte(pstOut->track_enabled))
		return -1;

	if(-1 == poNetData->DelDword(pstOut->life))
		return -1;

	if(-1 == poNetData->DelString(pstOut->progressing, sizeof(pstOut->progressing)))
		return -1;

	if(-1 == poNetData->DelString(pstOut->accomplishing, sizeof(pstOut->accomplishing)))
		return -1;

	return sizeof(*pstOut);
}
int EnCodeSkillCDPermenantChangedNtf(void* pHost, CNetData* poNetData)
{
    auto* pstIn = reinterpret_cast<SkillCDPermenantChangedNtf*>(pHost);

    if (-1 == poNetData->AddWord(pstIn->moudleid))
        return -1;

    if (-1 == poNetData->AddWord(pstIn->protocolid))
        return -1;

    if (-1 == poNetData->AddWord(pstIn->skill_id))
        return -1;

    if (-1 == poNetData->AddDword(pstIn->new_cd))
        return -1;

    return poNetData->GetDataLen();
}
int DeCodeSkillCDPermenantChangedNtf(void* pHost, CNetData* poNetData)
{
    auto* pstOut = reinterpret_cast<SkillCDPermenantChangedNtf*>(pHost);

    if (-1 == poNetData->DelWord(const_cast<unsigned short&>(pstOut->moudleid)))
        return -1;

    if (-1 == poNetData->DelWord(const_cast<unsigned short&>(pstOut->protocolid)))
        return -1;

    if (-1 == poNetData->DelWord(pstOut->skill_id))
        return -1;

    if (-1 == poNetData->DelDword(pstOut->new_cd))
        return -1;

    return sizeof(*pstOut);
}
CClientGS::CClientGS()
{
	m_EnCodeFuncArray[0] = &EnCodeEnterGSReq;
	m_DeCodeFuncArray[0] = &DeCodeEnterGSReq;

	m_EnCodeFuncArray[1] = &EnCodeEnterGSAck;
	m_DeCodeFuncArray[1] = &DeCodeEnterGSAck;

	m_EnCodeFuncArray[2] = &EnCodeExitGSReq;
	m_DeCodeFuncArray[2] = &DeCodeExitGSReq;

	m_EnCodeFuncArray[3] = &EnCodeExitGSAck;
	m_DeCodeFuncArray[3] = &DeCodeExitGSAck;

	m_EnCodeFuncArray[4] = &EnCodeJumpGSNtf;
	m_DeCodeFuncArray[4] = &DeCodeJumpGSNtf;

	m_EnCodeFuncArray[5] = &EnCodeKickRoleNtf;
	m_DeCodeFuncArray[5] = &DeCodeKickRoleNtf;

	m_EnCodeFuncArray[6] = &EnCodeEnterMapNtf;
	m_DeCodeFuncArray[6] = &DeCodeEnterMapNtf;

	m_EnCodeFuncArray[7] = &EnCodeMapRegionNtf;
	m_DeCodeFuncArray[7] = &DeCodeMapRegionNtf;

	m_EnCodeFuncArray[8] = &EnCodeSetRelivePT;
	m_DeCodeFuncArray[8] = &DeCodeSetRelivePT;

	m_EnCodeFuncArray[9] = &EnCodePlayerReliveReq;
	m_DeCodeFuncArray[9] = &DeCodePlayerReliveReq;

	m_EnCodeFuncArray[10] = &EnCodePlayerReliveAck;
	m_DeCodeFuncArray[10] = &DeCodePlayerReliveAck;

	m_EnCodeFuncArray[11] = &EnCodePlayerAppearNtf;
	m_DeCodeFuncArray[11] = &DeCodePlayerAppearNtf;

	m_EnCodeFuncArray[12] = &EnCodeMonsterAppearNtf;
	m_DeCodeFuncArray[12] = &DeCodeMonsterAppearNtf;

	m_EnCodeFuncArray[13] = &EnCodeItemAppearNtf;
	m_DeCodeFuncArray[13] = &DeCodeItemAppearNtf;

	m_EnCodeFuncArray[14] = &EnCodeNPCAppearNtf;
	m_DeCodeFuncArray[14] = &DeCodeNPCAppearNtf;

	m_EnCodeFuncArray[15] = &EnCodeObjDisappearNtf;
	m_DeCodeFuncArray[15] = &DeCodeObjDisappearNtf;

	m_EnCodeFuncArray[16] = &EnCodePlayerCreate;
	m_DeCodeFuncArray[16] = &DeCodePlayerCreate;

	m_EnCodeFuncArray[17] = &EnCodeMoveReq;
	m_DeCodeFuncArray[17] = &DeCodeMoveReq;

	m_EnCodeFuncArray[18] = &EnCodeMoveNtf;
	m_DeCodeFuncArray[18] = &DeCodeMoveNtf;

	m_EnCodeFuncArray[19] = &EnCodeMoveAck;
	m_DeCodeFuncArray[19] = &DeCodeMoveAck;

	m_EnCodeFuncArray[20] = &EnCodeTurnReq;
	m_DeCodeFuncArray[20] = &DeCodeTurnReq;

	m_EnCodeFuncArray[21] = &EnCodeTurnNtf;
	m_DeCodeFuncArray[21] = &DeCodeTurnNtf;

	m_EnCodeFuncArray[22] = &EnCodeTurnAck;
	m_DeCodeFuncArray[22] = &DeCodeTurnAck;

	m_EnCodeFuncArray[23] = &EnCodeObjDieNtf;
	m_DeCodeFuncArray[23] = &DeCodeObjDieNtf;

	m_EnCodeFuncArray[24] = &EnCodeChatReq;
	m_DeCodeFuncArray[24] = &DeCodeChatReq;

	m_EnCodeFuncArray[25] = &EnCodeGMCommandReq;
	m_DeCodeFuncArray[25] = &DeCodeGMCommandReq;

	m_EnCodeFuncArray[26] = &EnCodeRoleAppNtf;
	m_DeCodeFuncArray[26] = &DeCodeRoleAppNtf;

	m_EnCodeFuncArray[27] = &EnCodeRoleAttrNtf;
	m_DeCodeFuncArray[27] = &DeCodeRoleAttrNtf;

	m_EnCodeFuncArray[28] = &EnCodeRoleAttrExtNtf;
	m_DeCodeFuncArray[28] = &DeCodeRoleAttrExtNtf;

	m_EnCodeFuncArray[29] = &EnCodeTeamMemberNtf;
	m_DeCodeFuncArray[29] = &DeCodeTeamMemberNtf;

	m_EnCodeFuncArray[30] = &EnCodeShowFormNtf;
	m_DeCodeFuncArray[30] = &DeCodeShowFormNtf;

	m_EnCodeFuncArray[31] = &EnCodeSubmitForm;
	m_DeCodeFuncArray[31] = &DeCodeSubmitForm;

	m_EnCodeFuncArray[32] = &EnCodeItemAddReq;
	m_DeCodeFuncArray[32] = &DeCodeItemAddReq;

	m_EnCodeFuncArray[33] = &EnCodeItemAddAck;
	m_DeCodeFuncArray[33] = &DeCodeItemAddAck;

	m_EnCodeFuncArray[34] = &EnCodeItemDestroyReq;
	m_DeCodeFuncArray[34] = &DeCodeItemDestroyReq;

	m_EnCodeFuncArray[35] = &EnCodeItemDestroyAck;
	m_DeCodeFuncArray[35] = &DeCodeItemDestroyAck;

	m_EnCodeFuncArray[36] = &EnCodeItemMove;
	m_DeCodeFuncArray[36] = &DeCodeItemMove;

	m_EnCodeFuncArray[37] = &EnCodeItemSplit;
	m_DeCodeFuncArray[37] = &DeCodeItemSplit;

	m_EnCodeFuncArray[38] = &EnCodeItemAttrNtf;
	m_DeCodeFuncArray[38] = &DeCodeItemAttrNtf;

	m_EnCodeFuncArray[39] = &EnCodeItemUpdateNtf;
	m_DeCodeFuncArray[39] = &DeCodeItemUpdateNtf;

	m_EnCodeFuncArray[40] = &EnCodeItemBind;
	m_DeCodeFuncArray[40] = &DeCodeItemBind;

	m_EnCodeFuncArray[41] = &EnCodeItemApply;
	m_DeCodeFuncArray[41] = &DeCodeItemApply;

	m_EnCodeFuncArray[42] = &EnCodeItemApplyOnTarget;
	m_DeCodeFuncArray[42] = &DeCodeItemApplyOnTarget;

	m_EnCodeFuncArray[43] = &EnCodeItemApplyOnGrid;
	m_DeCodeFuncArray[43] = &DeCodeItemApplyOnGrid;

	m_EnCodeFuncArray[44] = &EnCodeItemArrange;
	m_DeCodeFuncArray[44] = &DeCodeItemArrange;

	m_EnCodeFuncArray[45] = &EnCodeItemPickUp;
	m_DeCodeFuncArray[45] = &DeCodeItemPickUp;

	m_EnCodeFuncArray[46] = &EnCodeItemDrop;
	m_DeCodeFuncArray[46] = &DeCodeItemDrop;

	m_EnCodeFuncArray[47] = &EnCodeItemTieUp;
	m_DeCodeFuncArray[47] = &DeCodeItemTieUp;

	m_EnCodeFuncArray[48] = &EnCodeItemTip;
	m_DeCodeFuncArray[48] = &DeCodeItemTip;

	m_EnCodeFuncArray[49] = &EnCodeItemTipBrd;
	m_DeCodeFuncArray[49] = &DeCodeItemTipBrd;

	m_EnCodeFuncArray[50] = &EnCodeItemTipNtf;
	m_DeCodeFuncArray[50] = &DeCodeItemTipNtf;

	m_EnCodeFuncArray[51] = &EnCodeItemEnhance;
	m_DeCodeFuncArray[51] = &DeCodeItemEnhance;

	m_EnCodeFuncArray[52] = &EnCodeItemDrill;
	m_DeCodeFuncArray[52] = &DeCodeItemDrill;

	m_EnCodeFuncArray[53] = &EnCodeItemSynthesis;
	m_DeCodeFuncArray[53] = &DeCodeItemSynthesis;

	m_EnCodeFuncArray[54] = &EnCodeItemEmbed;
	m_DeCodeFuncArray[54] = &DeCodeItemEmbed;

	m_EnCodeFuncArray[55] = &EnCodeItemDig;
	m_DeCodeFuncArray[55] = &DeCodeItemDig;

	m_EnCodeFuncArray[56] = &EnCodeItemIdentify;
	m_DeCodeFuncArray[56] = &DeCodeItemIdentify;

	m_EnCodeFuncArray[57] = &EnCodeItemRename;
	m_DeCodeFuncArray[57] = &DeCodeItemRename;

	m_EnCodeFuncArray[58] = &EnCodeItemRefine;
	m_DeCodeFuncArray[58] = &DeCodeItemRefine;

	m_EnCodeFuncArray[59] = &EnCodeItemRepairQuery;
	m_DeCodeFuncArray[59] = &DeCodeItemRepairQuery;

	m_EnCodeFuncArray[60] = &EnCodeItemRepairQueryNtf;
	m_DeCodeFuncArray[60] = &DeCodeItemRepairQueryNtf;

	m_EnCodeFuncArray[61] = &EnCodeItemRepair;
	m_DeCodeFuncArray[61] = &DeCodeItemRepair;

	m_EnCodeFuncArray[62] = &EnCodeItemSeg;
	m_DeCodeFuncArray[62] = &DeCodeItemSeg;

	m_EnCodeFuncArray[63] = &EnCodeSkillAddReq;
	m_DeCodeFuncArray[63] = &DeCodeSkillAddReq;

	m_EnCodeFuncArray[64] = &EnCodeSkillAddAck;
	m_DeCodeFuncArray[64] = &DeCodeSkillAddAck;

	m_EnCodeFuncArray[65] = &EnCodeSkillDestroyReq;
	m_DeCodeFuncArray[65] = &DeCodeSkillDestroyReq;

	m_EnCodeFuncArray[66] = &EnCodeSkillDestroyAck;
	m_DeCodeFuncArray[66] = &DeCodeSkillDestroyAck;

	m_EnCodeFuncArray[67] = &EnCodeSkillSwitch;
	m_DeCodeFuncArray[67] = &DeCodeSkillSwitch;

	m_EnCodeFuncArray[68] = &EnCodeSkillSwitchAck;
	m_DeCodeFuncArray[68] = &DeCodeSkillSwitchAck;

	m_EnCodeFuncArray[69] = &EnCodeSkillProficiencyNtf;
	m_DeCodeFuncArray[69] = &DeCodeSkillProficiencyNtf;

	m_EnCodeFuncArray[70] = &EnCodeBuffAddAck;
	m_DeCodeFuncArray[70] = &DeCodeBuffAddAck;

	m_EnCodeFuncArray[71] = &EnCodeBuffDestroyReq;
	m_DeCodeFuncArray[71] = &DeCodeBuffDestroyReq;

	m_EnCodeFuncArray[72] = &EnCodeBuffDestroyAck;
	m_DeCodeFuncArray[72] = &DeCodeBuffDestroyAck;

	m_EnCodeFuncArray[73] = &EnCodeBuffUpdateNtf;
	m_DeCodeFuncArray[73] = &DeCodeBuffUpdateNtf;

	m_EnCodeFuncArray[74] = &EnCodeSpellTargetReadyNtf;
	m_DeCodeFuncArray[74] = &DeCodeSpellTargetReadyNtf;

	m_EnCodeFuncArray[75] = &EnCodeSpellGridReadyNtf;
	m_DeCodeFuncArray[75] = &DeCodeSpellGridReadyNtf;

	m_EnCodeFuncArray[76] = &EnCodeSpellTarget;
	m_DeCodeFuncArray[76] = &DeCodeSpellTarget;

	m_EnCodeFuncArray[77] = &EnCodeSpellGrid;
	m_DeCodeFuncArray[77] = &DeCodeSpellGrid;

	m_EnCodeFuncArray[78] = &EnCodeSpellAck;
	m_DeCodeFuncArray[78] = &DeCodeSpellAck;

	m_EnCodeFuncArray[79] = &EnCodeSpellNtf;
	m_DeCodeFuncArray[79] = &DeCodeSpellNtf;

	m_EnCodeFuncArray[80] = &EnCodeAttrShowNtf;
	m_DeCodeFuncArray[80] = &DeCodeAttrShowNtf;

	m_EnCodeFuncArray[81] = &EnCodeMissNtf;
	m_DeCodeFuncArray[81] = &DeCodeMissNtf;

	m_EnCodeFuncArray[82] = &EnCodeSpellDelayLostNtf;
	m_DeCodeFuncArray[82] = &DeCodeSpellDelayLostNtf;

	m_EnCodeFuncArray[83] = &EnCodeSpellDelayHitNtf;
	m_DeCodeFuncArray[83] = &DeCodeSpellDelayHitNtf;

	m_EnCodeFuncArray[84] = &EnCodeTradeNpcBuy;
	m_DeCodeFuncArray[84] = &DeCodeTradeNpcBuy;

	m_EnCodeFuncArray[85] = &EnCodeTradeNpcSell;
	m_DeCodeFuncArray[85] = &DeCodeTradeNpcSell;

	m_EnCodeFuncArray[86] = &EnCodeTradeNpcValueReq;
	m_DeCodeFuncArray[86] = &DeCodeTradeNpcValueReq;

	m_EnCodeFuncArray[87] = &EnCodeTradeNpcValueAck;
	m_DeCodeFuncArray[87] = &DeCodeTradeNpcValueAck;

	m_EnCodeFuncArray[88] = &EnCodeTradeNpcShopNtf;
	m_DeCodeFuncArray[88] = &DeCodeTradeNpcShopNtf;

	m_EnCodeFuncArray[89] = &EnCodeTradeP2PRequest;
	m_DeCodeFuncArray[89] = &DeCodeTradeP2PRequest;

	m_EnCodeFuncArray[90] = &EnCodeTradeP2PRequestNtf;
	m_DeCodeFuncArray[90] = &DeCodeTradeP2PRequestNtf;

	m_EnCodeFuncArray[91] = &EnCodeTradeP2PResponse;
	m_DeCodeFuncArray[91] = &DeCodeTradeP2PResponse;

	m_EnCodeFuncArray[92] = &EnCodeTradeP2POpenNtf;
	m_DeCodeFuncArray[92] = &DeCodeTradeP2POpenNtf;

	m_EnCodeFuncArray[93] = &EnCodeTradeP2PArrange;
	m_DeCodeFuncArray[93] = &DeCodeTradeP2PArrange;

	m_EnCodeFuncArray[94] = &EnCodeTradeP2PArrangeNtf;
	m_DeCodeFuncArray[94] = &DeCodeTradeP2PArrangeNtf;

	m_EnCodeFuncArray[95] = &EnCodeTradeP2PGold;
	m_DeCodeFuncArray[95] = &DeCodeTradeP2PGold;

	m_EnCodeFuncArray[96] = &EnCodeTradeP2PGoldNtf;
	m_DeCodeFuncArray[96] = &DeCodeTradeP2PGoldNtf;

	m_EnCodeFuncArray[97] = &EnCodeTradeP2PLock;
	m_DeCodeFuncArray[97] = &DeCodeTradeP2PLock;

	m_EnCodeFuncArray[98] = &EnCodeTradeP2PLockNtf;
	m_DeCodeFuncArray[98] = &DeCodeTradeP2PLockNtf;

	m_EnCodeFuncArray[99] = &EnCodeTradeP2PConfirme;
	m_DeCodeFuncArray[99] = &DeCodeTradeP2PConfirme;

	m_EnCodeFuncArray[100] = &EnCodeTradeP2PConfirmeNtf;
	m_DeCodeFuncArray[100] = &DeCodeTradeP2PConfirmeNtf;

	m_EnCodeFuncArray[101] = &EnCodeTradeP2PClose;
	m_DeCodeFuncArray[101] = &DeCodeTradeP2PClose;

	m_EnCodeFuncArray[102] = &EnCodeTradeP2PCloseNtf;
	m_DeCodeFuncArray[102] = &DeCodeTradeP2PCloseNtf;

	m_EnCodeFuncArray[103] = &EnCodeTradeStallReady;
	m_DeCodeFuncArray[103] = &DeCodeTradeStallReady;

	m_EnCodeFuncArray[104] = &EnCodeTradeStallReadyNtf;
	m_DeCodeFuncArray[104] = &DeCodeTradeStallReadyNtf;

	m_EnCodeFuncArray[105] = &EnCodeTradeStall;
	m_DeCodeFuncArray[105] = &DeCodeTradeStall;

	m_EnCodeFuncArray[106] = &EnCodeTradeStallNtf;
	m_DeCodeFuncArray[106] = &DeCodeTradeStallNtf;

	m_EnCodeFuncArray[107] = &EnCodeTradeStallArrange;
	m_DeCodeFuncArray[107] = &DeCodeTradeStallArrange;

	m_EnCodeFuncArray[108] = &EnCodeTradeStallQuery;
	m_DeCodeFuncArray[108] = &DeCodeTradeStallQuery;

	m_EnCodeFuncArray[109] = &EnCodeTradeStallQueryNtf;
	m_DeCodeFuncArray[109] = &DeCodeTradeStallQueryNtf;

	m_EnCodeFuncArray[110] = &EnCodeTradeStallBuy;
	m_DeCodeFuncArray[110] = &DeCodeTradeStallBuy;

	m_EnCodeFuncArray[111] = &EnCodeTradeStallBuyNtf;
	m_DeCodeFuncArray[111] = &DeCodeTradeStallBuyNtf;

	m_EnCodeFuncArray[112] = &EnCodeTradeStallClose;
	m_DeCodeFuncArray[112] = &DeCodeTradeStallClose;

	m_EnCodeFuncArray[113] = &EnCodeTradeStallCloseNtf;
	m_DeCodeFuncArray[113] = &DeCodeTradeStallCloseNtf;

	m_EnCodeFuncArray[114] = &EnCodePlayerSwitch;
	m_DeCodeFuncArray[114] = &DeCodePlayerSwitch;

	m_EnCodeFuncArray[115] = &EnCodeAtkModeReq;
	m_DeCodeFuncArray[115] = &DeCodeAtkModeReq;

	m_EnCodeFuncArray[116] = &EnCodeServantModeReq;
	m_DeCodeFuncArray[116] = &DeCodeServantModeReq;

	m_EnCodeFuncArray[117] = &EnCodeRoleAddPoint;
	m_DeCodeFuncArray[117] = &DeCodeRoleAddPoint;

	m_EnCodeFuncArray[118] = &EnCodeLevelUpNtf;
	m_DeCodeFuncArray[118] = &DeCodeLevelUpNtf;

	m_EnCodeFuncArray[119] = &EnCodePlayerQuery;
	m_DeCodeFuncArray[119] = &DeCodePlayerQuery;

	m_EnCodeFuncArray[120] = &EnCodePlayerQueryBrd;
	m_DeCodeFuncArray[120] = &DeCodePlayerQueryBrd;

	m_EnCodeFuncArray[121] = &EnCodePlayerQueryNtf;
	m_DeCodeFuncArray[121] = &DeCodePlayerQueryNtf;

	m_EnCodeFuncArray[122] = &EnCodePlayerSiteSeg;
	m_DeCodeFuncArray[122] = &DeCodePlayerSiteSeg;

	m_EnCodeFuncArray[123] = &EnCodePlayerSiteSegBrd;
	m_DeCodeFuncArray[123] = &DeCodePlayerSiteSegBrd;

	m_EnCodeFuncArray[124] = &EnCodePlayerSiteSegNtf;
	m_DeCodeFuncArray[124] = &DeCodePlayerSiteSegNtf;

	m_EnCodeFuncArray[125] = &EnCodeTitleAdd;
	m_DeCodeFuncArray[125] = &DeCodeTitleAdd;

	m_EnCodeFuncArray[126] = &EnCodeTitleRemove;
	m_DeCodeFuncArray[126] = &DeCodeTitleRemove;

	m_EnCodeFuncArray[127] = &EnCodeTitleApply;
	m_DeCodeFuncArray[127] = &DeCodeTitleApply;

	m_EnCodeFuncArray[128] = &EnCodeTitleAddAck;
	m_DeCodeFuncArray[128] = &DeCodeTitleAddAck;

	m_EnCodeFuncArray[129] = &EnCodeTitleRemoveAck;
	m_DeCodeFuncArray[129] = &DeCodeTitleRemoveAck;

	m_EnCodeFuncArray[130] = &EnCodeSysMsgNtf;
	m_DeCodeFuncArray[130] = &DeCodeSysMsgNtf;

	m_EnCodeFuncArray[131] = &EnCodeRelationChatNtf;
	m_DeCodeFuncArray[131] = &DeCodeRelationChatNtf;

	m_EnCodeFuncArray[132] = &EnCodeNpcSelect;
	m_DeCodeFuncArray[132] = &DeCodeNpcSelect;

	m_EnCodeFuncArray[133] = &EnCodeNpcTalkReq;
	m_DeCodeFuncArray[133] = &DeCodeNpcTalkReq;

	m_EnCodeFuncArray[134] = &EnCodeNpcTalkAck;
	m_DeCodeFuncArray[134] = &DeCodeNpcTalkAck;

	m_EnCodeFuncArray[135] = &EnCodeQuickBarSet;
	m_DeCodeFuncArray[135] = &DeCodeQuickBarSet;

	m_EnCodeFuncArray[136] = &EnCodeQuickBarSetNtf;
	m_DeCodeFuncArray[136] = &DeCodeQuickBarSetNtf;

	m_EnCodeFuncArray[137] = &EnCodeQuickBarRemove;
	m_DeCodeFuncArray[137] = &DeCodeQuickBarRemove;

	m_EnCodeFuncArray[138] = &EnCodeQuickBarRemoveNtf;
	m_DeCodeFuncArray[138] = &DeCodeQuickBarRemoveNtf;

	m_EnCodeFuncArray[139] = &EnCodeQuickBarMove;
	m_DeCodeFuncArray[139] = &DeCodeQuickBarMove;

	m_EnCodeFuncArray[140] = &EnCodeShortcutSet;
	m_DeCodeFuncArray[140] = &DeCodeShortcutSet;

	m_EnCodeFuncArray[141] = &EnCodeShortcutNtf;
	m_DeCodeFuncArray[141] = &DeCodeShortcutNtf;

	m_EnCodeFuncArray[142] = &EnCodeGoldDeposit;
	m_DeCodeFuncArray[142] = &DeCodeGoldDeposit;

	m_EnCodeFuncArray[143] = &EnCodeGoldTake;
	m_DeCodeFuncArray[143] = &DeCodeGoldTake;

	m_EnCodeFuncArray[144] = &EnCodeBeServantNtf;
	m_DeCodeFuncArray[144] = &DeCodeBeServantNtf;

	m_EnCodeFuncArray[145] = &EnCodeRoleAttrExtRefNtf;
	m_DeCodeFuncArray[145] = &DeCodeRoleAttrExtRefNtf;

	m_EnCodeFuncArray[146] = &EnCodeStartFamilyWarBrd;
	m_DeCodeFuncArray[146] = &DeCodeStartFamilyWarBrd;

	m_EnCodeFuncArray[147] = &EnCodeRunningFamilyWarNtf;
	m_DeCodeFuncArray[147] = &DeCodeRunningFamilyWarNtf;

	m_EnCodeFuncArray[148] = &EnCodeCastleNtf;
	m_DeCodeFuncArray[148] = &DeCodeCastleNtf;

	m_EnCodeFuncArray[149] = &EnCodeGoldDrop;
	m_DeCodeFuncArray[149] = &DeCodeGoldDrop;

	m_EnCodeFuncArray[150] = &EnCodePlayerFamilyChangeNtf;
	m_DeCodeFuncArray[150] = &DeCodePlayerFamilyChangeNtf;

	m_EnCodeFuncArray[151] = &EnCodeNotifyMapEffect;
	m_DeCodeFuncArray[151] = &DeCodeNotifyMapEffect;

	m_EnCodeFuncArray[152] = &EnCodeRoleTalkNtf;
	m_DeCodeFuncArray[152] = &DeCodeRoleTalkNtf;

	m_EnCodeFuncArray[153] = &EnCodeProgressStartNtf;
	m_DeCodeFuncArray[153] = &DeCodeProgressStartNtf;

	m_EnCodeFuncArray[154] = &EnCodeProgressCancelNtf;
	m_DeCodeFuncArray[154] = &DeCodeProgressCancelNtf;

	m_EnCodeFuncArray[155] = &EnCodeVerifyImageQuestion;
	m_DeCodeFuncArray[155] = &DeCodeVerifyImageQuestion;

	m_EnCodeFuncArray[156] = &EnCodeVerifyImageAnswer;
	m_DeCodeFuncArray[156] = &DeCodeVerifyImageAnswer;

	m_EnCodeFuncArray[157] = &EnCodeVerifyImageReset;
	m_DeCodeFuncArray[157] = &DeCodeVerifyImageReset;

	m_EnCodeFuncArray[158] = &EnCodeVerifyImageResultNtf;
	m_DeCodeFuncArray[158] = &DeCodeVerifyImageResultNtf;

	m_EnCodeFuncArray[159] = &EnCodeTradeMallBuy;
	m_DeCodeFuncArray[159] = &DeCodeTradeMallBuy;

	m_EnCodeFuncArray[160] = &EnCodeTradeMallListReq;
	m_DeCodeFuncArray[160] = &DeCodeTradeMallListReq;

	m_EnCodeFuncArray[161] = &EnCodeTradeMallListAck;
	m_DeCodeFuncArray[161] = &DeCodeTradeMallListAck;

	m_EnCodeFuncArray[162] = &EnCodeTradeMallItemDetailReq;
	m_DeCodeFuncArray[162] = &DeCodeTradeMallItemDetailReq;

	m_EnCodeFuncArray[163] = &EnCodeTradeMallItemDetailAck;
	m_DeCodeFuncArray[163] = &DeCodeTradeMallItemDetailAck;

	m_EnCodeFuncArray[164] = &EnCodeTradeMallChartsReq;
	m_DeCodeFuncArray[164] = &DeCodeTradeMallChartsReq;

	m_EnCodeFuncArray[165] = &EnCodeTradeMallChartsAck;
	m_DeCodeFuncArray[165] = &DeCodeTradeMallChartsAck;

	m_EnCodeFuncArray[166] = &EnCodeNpcTalkReqEx;
	m_DeCodeFuncArray[166] = &DeCodeNpcTalkReqEx;

	m_EnCodeFuncArray[167] = &EnCodeNpcTalkAckEx;
	m_DeCodeFuncArray[167] = &DeCodeNpcTalkAckEx;

	m_EnCodeFuncArray[168] = &EnCodeQuestAccept;
	m_DeCodeFuncArray[168] = &DeCodeQuestAccept;

	m_EnCodeFuncArray[169] = &EnCodeQuestAddNtf;
	m_DeCodeFuncArray[169] = &DeCodeQuestAddNtf;

	m_EnCodeFuncArray[170] = &EnCodeQuestAccomplish;
	m_DeCodeFuncArray[170] = &DeCodeQuestAccomplish;

	m_EnCodeFuncArray[171] = &EnCodeQuestUpdateNtf;
	m_DeCodeFuncArray[171] = &DeCodeQuestUpdateNtf;

	m_EnCodeFuncArray[172] = &EnCodeQuestTrackChange;
	m_DeCodeFuncArray[172] = &DeCodeQuestTrackChange;

	m_EnCodeFuncArray[173] = &EnCodeQuestTrackChangeNtf;
	m_DeCodeFuncArray[173] = &DeCodeQuestTrackChangeNtf;

	m_EnCodeFuncArray[174] = &EnCodeQuestReadyNtf;
	m_DeCodeFuncArray[174] = &DeCodeQuestReadyNtf;

	m_EnCodeFuncArray[175] = &EnCodeQuestCompleteNtf;
	m_DeCodeFuncArray[175] = &DeCodeQuestCompleteNtf;

	m_EnCodeFuncArray[176] = &EnCodeQuestDrop;
	m_DeCodeFuncArray[176] = &DeCodeQuestDrop;

	m_EnCodeFuncArray[177] = &EnCodeQuestDropNtf;
	m_DeCodeFuncArray[177] = &DeCodeQuestDropNtf;

	m_EnCodeFuncArray[178] = &EnCodeQuestQueryCanAccept;
	m_DeCodeFuncArray[178] = &DeCodeQuestQueryCanAccept;

	m_EnCodeFuncArray[179] = &EnCodeQuestQueryCanAcceptNtf;
	m_DeCodeFuncArray[179] = &DeCodeQuestQueryCanAcceptNtf;

	m_EnCodeFuncArray[180] = &EnCodeDelegateSellCmd;
	m_DeCodeFuncArray[180] = &DeCodeDelegateSellCmd;

	m_EnCodeFuncArray[181] = &EnCodeDelegateBuyCmd;
	m_DeCodeFuncArray[181] = &DeCodeDelegateBuyCmd;

	m_EnCodeFuncArray[182] = &EnCodeDelegateSellListReq;
	m_DeCodeFuncArray[182] = &DeCodeDelegateSellListReq;

	m_EnCodeFuncArray[183] = &EnCodeDelegateSellListAck;
	m_DeCodeFuncArray[183] = &DeCodeDelegateSellListAck;

	m_EnCodeFuncArray[184] = &EnCodeDelegateBuyListReq;
	m_DeCodeFuncArray[184] = &DeCodeDelegateBuyListReq;

	//m_EnCodeFuncArray[185] = &EnCodeDelegateBuyListAck;
	//m_DeCodeFuncArray[185] = &DeCodeDelegateBuyListAck;

	m_EnCodeFuncArray[186] = &EnCodeMarketBuyCmd;
	m_DeCodeFuncArray[186] = &DeCodeMarketBuyCmd;

	m_EnCodeFuncArray[187] = &EnCodeMarketSellCmd;
	m_DeCodeFuncArray[187] = &DeCodeMarketSellCmd;

	m_EnCodeFuncArray[188] = &EnCodeDelegateCancel;
	m_DeCodeFuncArray[188] = &DeCodeDelegateCancel;

	m_EnCodeFuncArray[189] = &EnCodeDelegateMineReq;
	m_DeCodeFuncArray[189] = &DeCodeDelegateMineReq;

	//m_EnCodeFuncArray[190] = &EnCodeDelegateMineAck;
	//m_DeCodeFuncArray[190] = &DeCodeDelegateMineAck;

	m_EnCodeFuncArray[191] = &EnCodeAttrShowExNtf;
	m_DeCodeFuncArray[191] = &DeCodeAttrShowExNtf;

	m_EnCodeFuncArray[192] = &EnCodeCampaignListReq;
	m_DeCodeFuncArray[192] = &DeCodeCampaignListReq;

	m_EnCodeFuncArray[193] = &EnCodeCampaignListAck;
	m_DeCodeFuncArray[193] = &DeCodeCampaignListAck;

	m_EnCodeFuncArray[194] = &EnCodeCampaignDetailReq;
	m_DeCodeFuncArray[194] = &DeCodeCampaignDetailReq;

	m_EnCodeFuncArray[195] = &EnCodeCampaignDetailAck;
	m_DeCodeFuncArray[195] = &DeCodeCampaignDetailAck;

	m_EnCodeFuncArray[196] = &EnCodeInputDlgReq;
	m_DeCodeFuncArray[196] = &DeCodeInputDlgReq;

	m_EnCodeFuncArray[197] = &EnCodeInputDlgAck;
	m_DeCodeFuncArray[197] = &DeCodeInputDlgAck;

	m_EnCodeFuncArray[198] = &EnCodeMsgDlgReq;
	m_DeCodeFuncArray[198] = &DeCodeMsgDlgReq;

	m_EnCodeFuncArray[199] = &EnCodeMsgDlgAck;
	m_DeCodeFuncArray[199] = &DeCodeMsgDlgAck;

	m_EnCodeFuncArray[200] = &EnCodeWebDlgNtf;
	m_DeCodeFuncArray[200] = &DeCodeWebDlgNtf;

	m_EnCodeFuncArray[201] = &EnCodeOpenWebPageNtf;
	m_DeCodeFuncArray[201] = &DeCodeOpenWebPageNtf;

	m_EnCodeFuncArray[202] = &EnCodeGlobalNtf;
	m_DeCodeFuncArray[202] = &DeCodeGlobalNtf;

	m_EnCodeFuncArray[203] = &EnCodeSpeakerMsgAck;
	m_DeCodeFuncArray[203] = &DeCodeSpeakerMsgAck;

	m_EnCodeFuncArray[204] = &EnCodeClientKeepAlive;
	m_DeCodeFuncArray[204] = &DeCodeClientKeepAlive;

	m_EnCodeFuncArray[205] = &EnCodeFamilyAllyTableNtf;
	m_DeCodeFuncArray[205] = &DeCodeFamilyAllyTableNtf;

	m_EnCodeFuncArray[206] = &EnCodePlayerCustomReq;
	m_DeCodeFuncArray[206] = &DeCodePlayerCustomReq;

	m_EnCodeFuncArray[207] = &EnCodePlayerCustomAck;
	m_DeCodeFuncArray[207] = &DeCodePlayerCustomAck;

	m_EnCodeFuncArray[208] = &EnCodeWebPageNtf;
	m_DeCodeFuncArray[208] = &DeCodeWebPageNtf;

	m_EnCodeFuncArray[209] = &EnCodeCustomNtf;
	m_DeCodeFuncArray[209] = &DeCodeCustomNtf;

	m_EnCodeFuncArray[210] = &EnCodeCustomBroadcast;
	m_DeCodeFuncArray[210] = &DeCodeCustomBroadcast;

	m_EnCodeFuncArray[211] = &EnCodeItemCustomNtf;
	m_DeCodeFuncArray[211] = &DeCodeItemCustomNtf;

	m_EnCodeFuncArray[212] = &EnCodeTaobaoNpcBuy;
	m_DeCodeFuncArray[212] = &DeCodeTaobaoNpcBuy;

	m_EnCodeFuncArray[213] = &EnCodeTaobaoNpcShopReq;
	m_DeCodeFuncArray[213] = &DeCodeTaobaoNpcShopReq;

	m_EnCodeFuncArray[214] = &EnCodeTaobaoNpcShopAck;
	m_DeCodeFuncArray[214] = &DeCodeTaobaoNpcShopAck;

	m_EnCodeFuncArray[215] = &EnCodeRunClientScriptNtf;
	m_DeCodeFuncArray[215] = &DeCodeRunClientScriptNtf;

	m_EnCodeFuncArray[216] = &EnCodeObjCustomNtf;
	m_DeCodeFuncArray[216] = &DeCodeObjCustomNtf;

	m_EnCodeFuncArray[217] = &EnCodeCampaignJoinNtf;
	m_DeCodeFuncArray[217] = &DeCodeCampaignJoinNtf;

	m_EnCodeFuncArray[218] = &EnCodeMapReq;
	m_DeCodeFuncArray[218] = &DeCodeMapReq;

	m_EnCodeFuncArray[219] = &EnCodeMapNtf;
	m_DeCodeFuncArray[219] = &DeCodeMapNtf;

	m_EnCodeFuncArray[220] = &EnCodeGridReq;
	m_DeCodeFuncArray[220] = &DeCodeGridReq;

	m_EnCodeFuncArray[221] = &EnCodeGridNtf;
	m_DeCodeFuncArray[221] = &DeCodeGridNtf;

	m_EnCodeFuncArray[222] = &EnCodeTableReq;
	m_DeCodeFuncArray[222] = &DeCodeTableReq;

	m_EnCodeFuncArray[223] = &EnCodeTableNtf;
	m_DeCodeFuncArray[223] = &DeCodeTableNtf;

	m_EnCodeFuncArray[224] = &EnCodeTableDataReq;
	m_DeCodeFuncArray[224] = &DeCodeTableDataReq;

	m_EnCodeFuncArray[225] = &EnCodeTableDataNtf;
	m_DeCodeFuncArray[225] = &DeCodeTableDataNtf;

	m_EnCodeFuncArray[226] = &EnCodeCampaignRunNtf;
	m_DeCodeFuncArray[226] = &DeCodeCampaignRunNtf;

	m_EnCodeFuncArray[227] = &EnCodeRideReq;
	m_DeCodeFuncArray[227] = &DeCodeRideReq;

	m_EnCodeFuncArray[228] = &EnCodeRideNtf;
	m_DeCodeFuncArray[228] = &DeCodeRideNtf;

	m_EnCodeFuncArray[229] = &EnCodePermissionReq;
	m_DeCodeFuncArray[229] = &DeCodePermissionReq;

	m_EnCodeFuncArray[230] = &EnCodeVipItemListReq;
	m_DeCodeFuncArray[230] = &DeCodeVipItemListReq;

	m_EnCodeFuncArray[231] = &EnCodeVipItemListAck;
	m_DeCodeFuncArray[231] = &DeCodeVipItemListAck;

	m_EnCodeFuncArray[232] = &EnCodeVipLevelBuyReq;
	m_DeCodeFuncArray[232] = &DeCodeVipLevelBuyReq;

	m_EnCodeFuncArray[233] = &EnCodeVipLevelBuyAck;
	m_DeCodeFuncArray[233] = &DeCodeVipLevelBuyAck;

	m_EnCodeFuncArray[234] = &EnCodeVipItemBuyReq;
	m_DeCodeFuncArray[234] = &DeCodeVipItemBuyReq;

	m_EnCodeFuncArray[235] = &EnCodeVipItemBuyAck;
	m_DeCodeFuncArray[235] = &DeCodeVipItemBuyAck;

	m_EnCodeFuncArray[236] = &EnCodeVipItemApplyReq;
	m_DeCodeFuncArray[236] = &DeCodeVipItemApplyReq;

	m_EnCodeFuncArray[237] = &EnCodeVipItemApplyAck;
	m_DeCodeFuncArray[237] = &DeCodeVipItemApplyAck;

	m_EnCodeFuncArray[238] = &EnCodeVipExpireNtf;
	m_DeCodeFuncArray[238] = &DeCodeVipExpireNtf;

	m_EnCodeFuncArray[239] = &EnCodeVipLevelListReq;
	m_DeCodeFuncArray[239] = &DeCodeVipLevelListReq;

	m_EnCodeFuncArray[240] = &EnCodeVipLevelListAck;
	m_DeCodeFuncArray[240] = &DeCodeVipLevelListAck;

	m_EnCodeFuncArray[241] = &EnCodeTradeNpcShopNumNtf;
	m_DeCodeFuncArray[241] = &DeCodeTradeNpcShopNumNtf;

	m_EnCodeFuncArray[242] = &EnCodeSubmitFormAck;
	m_DeCodeFuncArray[242] = &DeCodeSubmitFormAck;

	m_EnCodeFuncArray[243] = &EnCodeItemAttrReq;
	m_DeCodeFuncArray[243] = &DeCodeItemAttrReq;

	m_EnCodeFuncArray[244] = &EnCodeQuestStateReq;
	m_DeCodeFuncArray[244] = &DeCodeQuestStateReq;

	m_EnCodeFuncArray[245] = &EnCodeQuestStateNtf;
	m_DeCodeFuncArray[245] = &DeCodeQuestStateNtf;

	m_EnCodeFuncArray[246] = &EnCodeQuestQueryReq;
	m_DeCodeFuncArray[246] = &DeCodeQuestQueryReq;

	m_EnCodeFuncArray[247] = &EnCodeQuestQueryNtf;
	m_DeCodeFuncArray[247] = &DeCodeQuestQueryNtf;

	m_EnCodeFuncArray[248] = &EnCodeGloryFinishNtf;
	m_DeCodeFuncArray[248] = &DeCodeGloryFinishNtf;

	m_EnCodeFuncArray[249] = &EnCodeGloryStateQuery;
	m_DeCodeFuncArray[249] = &DeCodeGloryStateQuery;

	m_EnCodeFuncArray[250] = &EnCodeGloryStateAck;
	m_DeCodeFuncArray[250] = &DeCodeGloryStateAck;

	m_EnCodeFuncArray[251] = &EnCodeGloryAwardGet;
	m_DeCodeFuncArray[251] = &DeCodeGloryAwardGet;

	m_EnCodeFuncArray[252] = &EnCodeTraceReq;
	m_DeCodeFuncArray[252] = &DeCodeTraceReq;

	m_EnCodeFuncArray[253] = &EnCodeQuestNpcStateNtf;
	m_DeCodeFuncArray[253] = &DeCodeQuestNpcStateNtf;

	m_EnCodeFuncArray[254] = &EnCodeClientKeepAliveRet;
	m_DeCodeFuncArray[254] = &DeCodeClientKeepAliveRet;

	m_EnCodeFuncArray[255] = &EnCodeRemoveClientNtf;
	m_DeCodeFuncArray[255] = &DeCodeRemoveClientNtf;

	m_EnCodeFuncArray[256] = &EnCodeSceneMagicAppearNtf;
	m_DeCodeFuncArray[256] = &DeCodeSceneMagicAppearNtf;

	m_EnCodeFuncArray[257] = &EnCodeDummyPackage;
	m_DeCodeFuncArray[257] = &DeCodeDummyPackage;

	m_EnCodeFuncArray[258] = &EnCodeDummyItemMove;
	m_DeCodeFuncArray[258] = &DeCodeDummyItemMove;

	m_EnCodeFuncArray[259] = &EnCodeDummyControlNtf;
	m_DeCodeFuncArray[259] = &DeCodeDummyControlNtf;

	m_EnCodeFuncArray[260] = &EnCodeServantNumNtf;
	m_DeCodeFuncArray[260] = &DeCodeServantNumNtf;

	m_EnCodeFuncArray[261] = &EnCodeDummyStateSwitchReq;
	m_DeCodeFuncArray[261] = &DeCodeDummyStateSwitchReq;

	m_EnCodeFuncArray[262] = &EnCodeDummyStateSwitchAck;
	m_DeCodeFuncArray[262] = &DeCodeDummyStateSwitchAck;

	m_EnCodeFuncArray[263] = &EnCodeHeroCreateNtf;
	m_DeCodeFuncArray[263] = &DeCodeHeroCreateNtf;

	m_EnCodeFuncArray[264] = &EnCodeHeroDestroyNtf;
	m_DeCodeFuncArray[264] = &DeCodeHeroDestroyNtf;

	m_EnCodeFuncArray[265] = &EnCodeAutoSetOptNtf;
	m_DeCodeFuncArray[265] = &DeCodeAutoSetOptNtf;

	m_EnCodeFuncArray[266] = &EnCodeAutoRunBeginNtf;
	m_DeCodeFuncArray[266] = &DeCodeAutoRunBeginNtf;

	m_EnCodeFuncArray[267] = &EnCodeAutoRunEndNtf;
	m_DeCodeFuncArray[267] = &DeCodeAutoRunEndNtf;

	m_EnCodeFuncArray[268] = &EnCodeNetCheckNtf;
	m_DeCodeFuncArray[268] = &DeCodeNetCheckNtf;

	m_EnCodeFuncArray[269] = &EnCodeHeroSkillSwitchReq;
	m_DeCodeFuncArray[269] = &DeCodeHeroSkillSwitchReq;

	m_EnCodeFuncArray[270] = &EnCodeHeroSkillSwitchAck;
	m_DeCodeFuncArray[270] = &DeCodeHeroSkillSwitchAck;

	m_EnCodeFuncArray[271] = &EnCodeMoveReqEx;
	m_DeCodeFuncArray[271] = &DeCodeMoveReqEx;

	m_EnCodeFuncArray[272] = &EnCodeSpellTargetEx;
	m_DeCodeFuncArray[272] = &DeCodeSpellTargetEx;

	m_EnCodeFuncArray[273] = &EnCodeSpellGridEx;
	m_DeCodeFuncArray[273] = &DeCodeSpellGridEx;

	m_EnCodeFuncArray[274] = &EnCodeHeroLockTargetCmd;
	m_DeCodeFuncArray[274] = &DeCodeHeroLockTargetCmd;

	m_EnCodeFuncArray[275] = &EnCodeServantStatNtf;
	m_DeCodeFuncArray[275] = &DeCodeServantStatNtf;

	m_EnCodeFuncArray[276] = &EnCodeJointHitNtf;
	m_DeCodeFuncArray[276] = &DeCodeJointHitNtf;

	m_EnCodeFuncArray[277] = &EnCodeJointHit;
	m_DeCodeFuncArray[277] = &DeCodeJointHit;

	m_EnCodeFuncArray[278] = &EnCodeQuestAcceptEx;
	m_DeCodeFuncArray[278] = &DeCodeQuestAcceptEx;

	m_EnCodeFuncArray[279] = &EnCodeQuestAccomplishEx;
	m_DeCodeFuncArray[279] = &DeCodeQuestAccomplishEx;

	m_EnCodeFuncArray[280] = &EnCodeHeroLockTargetAck;
	m_DeCodeFuncArray[280] = &DeCodeHeroLockTargetAck;

	m_EnCodeFuncArray[281] = &EnCodeShieldActiveNtf;
	m_DeCodeFuncArray[281] = &DeCodeShieldActiveNtf;

	m_EnCodeFuncArray[282] = &EnCodeShieldRemoveNtf;
	m_DeCodeFuncArray[282] = &DeCodeShieldRemoveNtf;

	m_EnCodeFuncArray[283] = &EnCodePlayerQueryEx;
	m_DeCodeFuncArray[283] = &DeCodePlayerQueryEx;

	m_EnCodeFuncArray[284] = &EnCodePlayerQueryBrdEx;
	m_DeCodeFuncArray[284] = &DeCodePlayerQueryBrdEx;

	m_EnCodeFuncArray[285] = &EnCodeGSVersion;
	m_DeCodeFuncArray[285] = &DeCodeGSVersion;

	m_EnCodeFuncArray[286] = &EnCodeUpdateCheckCode;
	m_DeCodeFuncArray[286] = &DeCodeUpdateCheckCode;

	m_EnCodeFuncArray[287] = &EnCodeMoveReq2;
	m_DeCodeFuncArray[287] = &DeCodeMoveReq2;

	m_EnCodeFuncArray[288] = &EnCodeSpellTarget2;
	m_DeCodeFuncArray[288] = &DeCodeSpellTarget2;

	m_EnCodeFuncArray[289] = &EnCodeSpellGrid2;
	m_DeCodeFuncArray[289] = &DeCodeSpellGrid2;

	m_EnCodeFuncArray[290] = &EnCodeNpcSelect2;
	m_DeCodeFuncArray[290] = &DeCodeNpcSelect2;

	m_EnCodeFuncArray[291] = &EnCodeNpcTalkReq2;
	m_DeCodeFuncArray[291] = &DeCodeNpcTalkReq2;

	m_EnCodeFuncArray[292] = &EnCodeClientVerNtf;
	m_DeCodeFuncArray[292] = &DeCodeClientVerNtf;

	m_EnCodeFuncArray[293] = &EnCodeItemApply2;
	m_DeCodeFuncArray[293] = &DeCodeItemApply2;

	m_EnCodeFuncArray[294] = &EnCodeMonsterAppearNtf2;
	m_DeCodeFuncArray[294] = &DeCodeMonsterAppearNtf2;

	m_EnCodeFuncArray[295] = &EnCodeItemAppearNtf2;
	m_DeCodeFuncArray[295] = &DeCodeItemAppearNtf2;

	m_EnCodeFuncArray[296] = &EnCodeClientKeepAliveEx;
	m_DeCodeFuncArray[296] = &DeCodeClientKeepAliveEx;

	m_EnCodeFuncArray[297] = &EnCodeGSVersionEx;
	m_DeCodeFuncArray[297] = &DeCodeGSVersionEx;

	m_EnCodeFuncArray[298] = &EnCodeClientVerReq;
	m_DeCodeFuncArray[298] = &DeCodeClientVerReq;

	m_EnCodeFuncArray[299] = &EnCodeNetDelayReq;
	m_DeCodeFuncArray[299] = &DeCodeNetDelayReq;

	m_EnCodeFuncArray[300] = &EnCodeNetDelayAck;
	m_DeCodeFuncArray[300] = &DeCodeNetDelayAck;

	m_EnCodeFuncArray[301] = &EnCodeClientVerNtfEx;
	m_DeCodeFuncArray[301] = &DeCodeClientVerNtfEx;

	m_EnCodeFuncArray[302] = &EnCodeClientVerReq2;
	m_DeCodeFuncArray[302] = &DeCodeClientVerReq2;

	m_EnCodeFuncArray[303] = &EnCodeClientVerAck2;
	m_DeCodeFuncArray[303] = &DeCodeClientVerAck2;

	m_EnCodeFuncArray[304] = &EnCodeNpcTalkReq3;
	m_DeCodeFuncArray[304] = &DeCodeNpcTalkReq3;

	m_EnCodeFuncArray[305] = &EnCodeNpcTalkAck3;
	m_DeCodeFuncArray[305] = &DeCodeNpcTalkAck3;

	m_EnCodeFuncArray[306] = &EnCodeAttrShowNtfEx;
	m_DeCodeFuncArray[306] = &DeCodeAttrShowNtfEx;

	m_EnCodeFuncArray[307] = &EnCodeEnterGSReqEx;
	m_DeCodeFuncArray[307] = &DeCodeEnterGSReqEx;

	m_EnCodeFuncArray[308] = &EnCodeReloginNtf;
	m_DeCodeFuncArray[308] = &DeCodeReloginNtf;

	m_EnCodeFuncArray[309] = &EnCodeBehaviorNtf;
	m_DeCodeFuncArray[309] = &DeCodeBehaviorNtf;

	m_EnCodeFuncArray[310] = &EnCodeFashionReq;
	m_DeCodeFuncArray[310] = &DeCodeFashionReq;

	m_EnCodeFuncArray[311] = &EnCodeFashionNtf;
	m_DeCodeFuncArray[311] = &DeCodeFashionNtf;

	m_EnCodeFuncArray[312] = &EnCodeErrorNtf;
	m_DeCodeFuncArray[312] = &DeCodeErrorNtf;

	m_EnCodeFuncArray[313] = &EnCodeNpcTalkReqEx3;
	m_DeCodeFuncArray[313] = &DeCodeNpcTalkReqEx3;

	m_EnCodeFuncArray[314] = &EnCodeNpcTalkAckEx3;
	m_DeCodeFuncArray[314] = &DeCodeNpcTalkAckEx3;

	m_EnCodeFuncArray[315] = &EnCodeSubmitForm2;
	m_DeCodeFuncArray[315] = &DeCodeSubmitForm2;

	m_EnCodeFuncArray[316] = &EnCodeSubmitFormAck2;
	m_DeCodeFuncArray[316] = &DeCodeSubmitFormAck2;

	m_EnCodeFuncArray[317] = &EnCodeRoleAddPointEx;
	m_DeCodeFuncArray[317] = &DeCodeRoleAddPointEx;

	m_EnCodeFuncArray[318] = &EnCodeGetClientCheckInfoReq;
	m_DeCodeFuncArray[318] = &DeCodeGetClientCheckInfoReq;

	m_EnCodeFuncArray[319] = &EnCodeGetClientCheckInfoAck;
	m_DeCodeFuncArray[319] = &DeCodeGetClientCheckInfoAck;

	m_EnCodeFuncArray[320] = &EnCodeGetMD5CheckListReq;
	m_DeCodeFuncArray[320] = &DeCodeGetMD5CheckListReq;

	m_EnCodeFuncArray[321] = &EnCodeGetMD5CheckListAck;
	m_DeCodeFuncArray[321] = &DeCodeGetMD5CheckListAck;

	m_EnCodeFuncArray[322] = &EnCodeDelayCloseNtf;
	m_DeCodeFuncArray[322] = &DeCodeDelayCloseNtf;

	m_EnCodeFuncArray[323] = &EnCodeFamilyJoinInviteReq;
	m_DeCodeFuncArray[323] = &DeCodeFamilyJoinInviteReq;

	m_EnCodeFuncArray[324] = &EnCodeFamilyJoinInviteAck;
	m_DeCodeFuncArray[324] = &DeCodeFamilyJoinInviteAck;

	m_EnCodeFuncArray[325] = &EnCodeFamilyRelationShipReq;
	m_DeCodeFuncArray[325] = &DeCodeFamilyRelationShipReq;

	m_EnCodeFuncArray[326] = &EnCodeFamilyRelationShipAck;
	m_DeCodeFuncArray[326] = &DeCodeFamilyRelationShipAck;

	m_EnCodeFuncArray[327] = &EnCodeMonsterAppearNtf3;
	m_DeCodeFuncArray[327] = &DeCodeMonsterAppearNtf3;

	m_EnCodeFuncArray[328] = &EnCodeMonsterAppearNtf4;
	m_DeCodeFuncArray[328] = &DeCodeMonsterAppearNtf4;

	m_EnCodeFuncArray[329] = &EnCodeGetAroundTeamReq;
	m_DeCodeFuncArray[329] = &DeCodeGetAroundTeamReq;

	m_EnCodeFuncArray[330] = &EnCodeGetAroundTeamAck;
	m_DeCodeFuncArray[330] = &DeCodeGetAroundTeamAck;

	m_EnCodeFuncArray[331] = &EnCodeMigrateRoleDataNtf;
	m_DeCodeFuncArray[331] = &DeCodeMigrateRoleDataNtf;

	m_EnCodeFuncArray[332] = &EnCodePlayerAppearNtf2;
	m_DeCodeFuncArray[332] = &DeCodePlayerAppearNtf2;

	m_EnCodeFuncArray[333] = &EnCodeRoleAppNtf2;
	m_DeCodeFuncArray[333] = &DeCodeRoleAppNtf2;

	m_EnCodeFuncArray[334] = &EnCodeItemBatchDestroyNtf;
	m_DeCodeFuncArray[334] = &DeCodeItemBatchDestroyNtf;

	m_EnCodeFuncArray[335] = &EnCodeSubmitForm3;
	m_DeCodeFuncArray[335] = &DeCodeSubmitForm3;

	m_EnCodeFuncArray[336] = &EnCodeSubmitFormAck3;
	m_DeCodeFuncArray[336] = &DeCodeSubmitFormAck3;

	m_EnCodeFuncArray[337] = &EnCodeItemAppearNtf3;
	m_DeCodeFuncArray[337] = &DeCodeItemAppearNtf3;

	m_EnCodeFuncArray[338] = &EnCodeItemAppearNtf4;
	m_DeCodeFuncArray[338] = &DeCodeItemAppearNtf4;

	m_EnCodeFuncArray[339] = &EnCodeInnerForceLevelUpReq;
	m_DeCodeFuncArray[339] = &DeCodeInnerForceLevelUpReq;

	m_EnCodeFuncArray[340] = &EnCodeInnerForceLevelUpAck;
	m_DeCodeFuncArray[340] = &DeCodeInnerForceLevelUpAck;

	m_EnCodeFuncArray[341] = &EnCodeClientFangChenMiNtf;
	m_DeCodeFuncArray[341] = &DeCodeClientFangChenMiNtf;

	m_EnCodeFuncArray[342] = &EnCodeDelegateMineAck2;
	m_DeCodeFuncArray[342] = &DeCodeDelegateMineAck2;

	m_EnCodeFuncArray[343] = &EnCodeDelegateBuyListAck2;
	m_DeCodeFuncArray[343] = &DeCodeDelegateBuyListAck2;

	m_EnCodeFuncArray[344] = &EnCodeFashionWeaponReq;
	m_DeCodeFuncArray[344] = &DeCodeFashionWeaponReq;

	m_EnCodeFuncArray[345] = &EnCodeFashionWeaponNtf;
	m_DeCodeFuncArray[345] = &DeCodeFashionWeaponNtf;

	m_EnCodeFuncArray[346] = &EnCodePlayerAppearNtf3;
	m_DeCodeFuncArray[346] = &DeCodePlayerAppearNtf3;

	m_EnCodeFuncArray[347] = &EnCodeMonsterAppearNtf5;
	m_DeCodeFuncArray[347] = &DeCodeMonsterAppearNtf5;

	m_EnCodeFuncArray[348] = &EnCodeMonsterAppearNtf6;
	m_DeCodeFuncArray[348] = &DeCodeMonsterAppearNtf6;

	m_EnCodeFuncArray[349] = &EnCodeCaptchaReq;
	m_DeCodeFuncArray[349] = &DeCodeCaptchaReq;

	m_EnCodeFuncArray[350] = &EnCodeCaptchaAck;
	m_DeCodeFuncArray[350] = &DeCodeCaptchaAck;

	m_EnCodeFuncArray[351] = &EnCodeAgentKeyReq;
	m_DeCodeFuncArray[351] = &DeCodeAgentKeyReq;

	m_EnCodeFuncArray[352] = &EnCodeAgentKeyAck;
	m_DeCodeFuncArray[352] = &DeCodeAgentKeyAck;

	m_EnCodeFuncArray[353] = &EnCodePlatformInfoNtf;
	m_DeCodeFuncArray[353] = &DeCodePlatformInfoNtf;

	m_EnCodeFuncArray[354] = &EnCodeAttrShowNtf2;
	m_DeCodeFuncArray[354] = &DeCodeAttrShowNtf2;

	m_EnCodeFuncArray[355] = &EnCodeAttrShowNtfEx2;
	m_DeCodeFuncArray[355] = &DeCodeAttrShowNtfEx2;

	m_EnCodeFuncArray[356] = &EnCodeBehaviorReq;
	m_DeCodeFuncArray[356] = &DeCodeBehaviorReq;

	m_EnCodeFuncArray[357] = &EnCodeFangChenMiNtf;
	m_DeCodeFuncArray[357] = &DeCodeFangChenMiNtf;

	m_EnCodeFuncArray[358] = &EnCodeNpcShopIdsNtf;
	m_DeCodeFuncArray[358] = &DeCodeNpcShopIdsNtf;

	m_EnCodeFuncArray[359] = &EnCodeCreateMobaRoomReq;
	m_DeCodeFuncArray[359] = &DeCodeCreateMobaRoomReq;

	m_EnCodeFuncArray[360] = &EnCodeCreateMobaRoomAck;
	m_DeCodeFuncArray[360] = &DeCodeCreateMobaRoomAck;

	m_EnCodeFuncArray[361] = &EnCodeEnterMobaRoomReq;
	m_DeCodeFuncArray[361] = &DeCodeEnterMobaRoomReq;

	m_EnCodeFuncArray[362] = &EnCodeEnterMobaRoomAck;
	m_DeCodeFuncArray[362] = &DeCodeEnterMobaRoomAck;

	m_EnCodeFuncArray[363] = &EnCodeExitMobaRoomReq;
	m_DeCodeFuncArray[363] = &DeCodeExitMobaRoomReq;

	m_EnCodeFuncArray[364] = &EnCodeExitMobaRoomAck;
	m_DeCodeFuncArray[364] = &DeCodeExitMobaRoomAck;

	m_EnCodeFuncArray[365] = &EnCodeGetMobaRoomListReq;
	m_DeCodeFuncArray[365] = &DeCodeGetMobaRoomListReq;

	m_EnCodeFuncArray[366] = &EnCodeMobaRoomListAck;
	m_DeCodeFuncArray[366] = &DeCodeMobaRoomListAck;

	m_EnCodeFuncArray[367] = &EnCodeMobaRoomMemberListNtf;
	m_DeCodeFuncArray[367] = &DeCodeMobaRoomMemberListNtf;

	m_EnCodeFuncArray[368] = &EnCodeGetMobaMemberListReq;
	m_DeCodeFuncArray[368] = &DeCodeGetMobaMemberListReq;

	m_EnCodeFuncArray[369] = &EnCodeMobaRoomKickReq;
	m_DeCodeFuncArray[369] = &DeCodeMobaRoomKickReq;

	m_EnCodeFuncArray[370] = &EnCodeMobaRoomKickAck;
	m_DeCodeFuncArray[370] = &DeCodeMobaRoomKickAck;

	m_EnCodeFuncArray[371] = &EnCodeMobaRoomKickedNtf;
	m_DeCodeFuncArray[371] = &DeCodeMobaRoomKickedNtf;

	m_EnCodeFuncArray[372] = &EnCodeMobaRoomCampReadyReq;
	m_DeCodeFuncArray[372] = &DeCodeMobaRoomCampReadyReq;

	m_EnCodeFuncArray[373] = &EnCodeMobaRoomCampReadyAck;
	m_DeCodeFuncArray[373] = &DeCodeMobaRoomCampReadyAck;

	m_EnCodeFuncArray[374] = &EnCodeMobaRoomCampReadyNtf;
	m_DeCodeFuncArray[374] = &DeCodeMobaRoomCampReadyNtf;

	m_EnCodeFuncArray[375] = &EnCodeMobaRoomGameStartNtf;
	m_DeCodeFuncArray[375] = &DeCodeMobaRoomGameStartNtf;

	m_EnCodeFuncArray[376] = &EnCodeMobaRoomSetViceHostReq;
	m_DeCodeFuncArray[376] = &DeCodeMobaRoomSetViceHostReq;

	m_EnCodeFuncArray[377] = &EnCodeMobaRoomSetViceHostAck;
	m_DeCodeFuncArray[377] = &DeCodeMobaRoomSetViceHostAck;

	m_EnCodeFuncArray[378] = &EnCodeMobaRoomToggleCampReq;
	m_DeCodeFuncArray[378] = &DeCodeMobaRoomToggleCampReq;

	m_EnCodeFuncArray[379] = &EnCodeMobaRoomToggleCampAck;
	m_DeCodeFuncArray[379] = &DeCodeMobaRoomToggleCampAck;

	m_EnCodeFuncArray[380] = &EnCodeMobaRoomDestroyNtf;
	m_DeCodeFuncArray[380] = &DeCodeMobaRoomDestroyNtf;

	m_EnCodeFuncArray[381] = &EnCodeMobaRoomMemberReadyReq;
	m_DeCodeFuncArray[381] = &DeCodeMobaRoomMemberReadyReq;

	m_EnCodeFuncArray[382] = &EnCodeMobaRoomMemberReadyAck;
	m_DeCodeFuncArray[382] = &DeCodeMobaRoomMemberReadyAck;

	m_EnCodeFuncArray[383] = &EnCodeMobaRoomMemberReadyNtf;
	m_DeCodeFuncArray[383] = &DeCodeMobaRoomMemberReadyNtf;

	m_EnCodeFuncArray[384] = &EnCodeMobaRoomUpdateNameAndPasswordReq;
	m_DeCodeFuncArray[384] = &DeCodeMobaRoomUpdateNameAndPasswordReq;

	m_EnCodeFuncArray[385] = &EnCodeMobaRoomUpdateNameAndPasswordAck;
	m_DeCodeFuncArray[385] = &DeCodeMobaRoomUpdateNameAndPasswordAck;

	m_EnCodeFuncArray[386] = &EnCodeMobaRoomNameUpdateNtf;
	m_DeCodeFuncArray[386] = &DeCodeMobaRoomNameUpdateNtf;

	m_EnCodeFuncArray[387] = &EnCodeMobaRoomChangeCampAndPosReq;
	m_DeCodeFuncArray[387] = &DeCodeMobaRoomChangeCampAndPosReq;

	m_EnCodeFuncArray[388] = &EnCodeMobaRoomChangeCampAndPosAck;
	m_DeCodeFuncArray[388] = &DeCodeMobaRoomChangeCampAndPosAck;

	m_EnCodeFuncArray[389] = &EnCodeReloginRefreshReq;
	m_DeCodeFuncArray[389] = &DeCodeReloginRefreshReq;

	m_EnCodeFuncArray[390] = &EnCodeGameGuardReq;
	m_DeCodeFuncArray[390] = &DeCodeGameGuardReq;

	m_EnCodeFuncArray[391] = &EnCodeGameGuardAck;
	m_DeCodeFuncArray[391] = &DeCodeGameGuardAck;

	m_EnCodeFuncArray[392] = &EnCodeGameGuardCheckFailedNtf;
	m_DeCodeFuncArray[392] = &DeCodeGameGuardCheckFailedNtf;

	m_EnCodeFuncArray[393] = &EnCodeGameGuardHackRpt;
	m_DeCodeFuncArray[393] = &DeCodeGameGuardHackRpt;

	m_EnCodeFuncArray[394] = &EnCodeGameGuardHeartBeat;
	m_DeCodeFuncArray[394] = &DeCodeGameGuardHeartBeat;

	m_EnCodeFuncArray[395] = &EnCodeBangcleHeartBeat;
	m_DeCodeFuncArray[395] = &DeCodeBangcleHeartBeat;

	m_EnCodeFuncArray[396] = &EnCodeTradeStallSetBuyList;
	m_DeCodeFuncArray[396] = &DeCodeTradeStallSetBuyList;

	m_EnCodeFuncArray[397] = &EnCodeTradeStallQueryBuyGoodsNtf;
	m_DeCodeFuncArray[397] = &DeCodeTradeStallQueryBuyGoodsNtf;

	m_EnCodeFuncArray[398] = &EnCodeTradeStallSell;
	m_DeCodeFuncArray[398] = &DeCodeTradeStallSell;

	m_EnCodeFuncArray[399] = &EnCodeTradeStallSellNtf;
	m_DeCodeFuncArray[399] = &DeCodeTradeStallSellNtf;

	m_EnCodeFuncArray[400] = &EnCodeTaobaoNpcShopReqEx;
	m_DeCodeFuncArray[400] = &DeCodeTaobaoNpcShopReqEx;

	m_EnCodeFuncArray[401] = &EnCodeTaobaoNpcShopAckEx;
	m_DeCodeFuncArray[401] = &DeCodeTaobaoNpcShopAckEx;

	m_EnCodeFuncArray[402] = &EnCodeSkillCDChangedNtf;
	m_DeCodeFuncArray[402] = &DeCodeSkillCDChangedNtf;

	m_EnCodeFuncArray[403] = &EnCodeSubmitForm4;
	m_DeCodeFuncArray[403] = &DeCodeSubmitForm4;

	m_EnCodeFuncArray[404] = &EnCodeSubmitFormAck4;
	m_DeCodeFuncArray[404] = &DeCodeSubmitFormAck4;

	m_EnCodeFuncArray[405] = &EnCodeQuestAddNtf2;
	m_DeCodeFuncArray[405] = &DeCodeQuestAddNtf2;

    m_EnCodeFuncArray[406] = &EnCodeSkillCDPermenantChangedNtf;
    m_DeCodeFuncArray[406] = &DeCodeSkillCDPermenantChangedNtf;
}

CClientGS::~CClientGS()
{
}

int CClientGS::BuildProtocol(void* pHost, char *pNet, int iNetSize)
{
	CNetData m_oData;
	m_oData.Prepare(pNet, iNetSize);
	if (*(unsigned short*)pHost != 3)
	{
		return -1;
	}
	if (*(unsigned short*)((char*)pHost+sizeof(unsigned short)) >= sizeof(m_EnCodeFuncArray)/sizeof(EnCodeFuncClientGS))
	{
		return -1;
	}
	return m_EnCodeFuncArray[*(unsigned short*)((char*)pHost+sizeof(unsigned short))](pHost, &m_oData);
}

bool CClientGS::HandleProtocol(char *pNet, int iNetSize, void* pHost)
{
	CNetData m_oData;
	m_oData.Prepare(pNet, iNetSize);

	unsigned short moudleid = 0;
	unsigned short protocolid = 0;
	if (m_oData.DelWord(moudleid) < 0)
	{
		return false;
	}
	if (moudleid != 3)
	{
		return false;
	}
	if (m_oData.DelWord(protocolid) < 0)
	{
		return false;
	}
	if (protocolid >= sizeof(m_DeCodeFuncArray)/sizeof(DeCodeFuncClientGS))
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
		OnRecv_EnterGSReq(*reinterpret_cast<EnterGSReq*>(pHost));
		break;
	case 1:
		OnRecv_EnterGSAck(*reinterpret_cast<EnterGSAck*>(pHost));
		break;
	case 2:
		OnRecv_ExitGSReq(*reinterpret_cast<ExitGSReq*>(pHost));
		break;
	case 3:
		OnRecv_ExitGSAck(*reinterpret_cast<ExitGSAck*>(pHost));
		break;
	case 4:
		OnRecv_JumpGSNtf(*reinterpret_cast<JumpGSNtf*>(pHost));
		break;
	case 5:
		OnRecv_KickRoleNtf(*reinterpret_cast<KickRoleNtf*>(pHost));
		break;
	case 6:
		OnRecv_EnterMapNtf(*reinterpret_cast<EnterMapNtf*>(pHost));
		break;
	case 7:
		OnRecv_MapRegionNtf(*reinterpret_cast<MapRegionNtf*>(pHost));
		break;
	case 8:
		OnRecv_SetRelivePT(*reinterpret_cast<SetRelivePT*>(pHost));
		break;
	case 9:
		OnRecv_PlayerReliveReq(*reinterpret_cast<PlayerReliveReq*>(pHost));
		break;
	case 10:
		OnRecv_PlayerReliveAck(*reinterpret_cast<PlayerReliveAck*>(pHost));
		break;
	case 11:
		OnRecv_PlayerAppearNtf(*reinterpret_cast<PlayerAppearNtf*>(pHost));
		break;
	case 12:
		OnRecv_MonsterAppearNtf(*reinterpret_cast<MonsterAppearNtf*>(pHost));
		break;
	case 13:
		OnRecv_ItemAppearNtf(*reinterpret_cast<ItemAppearNtf*>(pHost));
		break;
	case 14:
		OnRecv_NPCAppearNtf(*reinterpret_cast<NPCAppearNtf*>(pHost));
		break;
	case 15:
		OnRecv_ObjDisappearNtf(*reinterpret_cast<ObjDisappearNtf*>(pHost));
		break;
	case 16:
		OnRecv_PlayerCreate(*reinterpret_cast<PlayerCreate*>(pHost));
		break;
	case 17:
		OnRecv_MoveReq(*reinterpret_cast<MoveReq*>(pHost));
		break;
	case 18:
		OnRecv_MoveNtf(*reinterpret_cast<MoveNtf*>(pHost));
		break;
	case 19:
		OnRecv_MoveAck(*reinterpret_cast<MoveAck*>(pHost));
		break;
	case 20:
		OnRecv_TurnReq(*reinterpret_cast<TurnReq*>(pHost));
		break;
	case 21:
		OnRecv_TurnNtf(*reinterpret_cast<TurnNtf*>(pHost));
		break;
	case 22:
		OnRecv_TurnAck(*reinterpret_cast<TurnAck*>(pHost));
		break;
	case 23:
		OnRecv_ObjDieNtf(*reinterpret_cast<ObjDieNtf*>(pHost));
		break;
	case 24:
		OnRecv_ChatReq(*reinterpret_cast<ChatReq*>(pHost));
		break;
	case 25:
		OnRecv_GMCommandReq(*reinterpret_cast<GMCommandReq*>(pHost));
		break;
	case 26:
		OnRecv_RoleAppNtf(*reinterpret_cast<RoleAppNtf*>(pHost));
		break;
	case 27:
		OnRecv_RoleAttrNtf(*reinterpret_cast<RoleAttrNtf*>(pHost));
		break;
	case 28:
		OnRecv_RoleAttrExtNtf(*reinterpret_cast<RoleAttrExtNtf*>(pHost));
		break;
	case 29:
		OnRecv_TeamMemberNtf(*reinterpret_cast<TeamMemberNtf*>(pHost));
		break;
	case 30:
		OnRecv_ShowFormNtf(*reinterpret_cast<ShowFormNtf*>(pHost));
		break;
	case 31:
		OnRecv_SubmitForm(*reinterpret_cast<SubmitForm*>(pHost));
		break;
	case 32:
		OnRecv_ItemAddReq(*reinterpret_cast<ItemAddReq*>(pHost));
		break;
	case 33:
		OnRecv_ItemAddAck(*reinterpret_cast<ItemAddAck*>(pHost));
		break;
	case 34:
		OnRecv_ItemDestroyReq(*reinterpret_cast<ItemDestroyReq*>(pHost));
		break;
	case 35:
		OnRecv_ItemDestroyAck(*reinterpret_cast<ItemDestroyAck*>(pHost));
		break;
	case 36:
		OnRecv_ItemMove(*reinterpret_cast<ItemMove*>(pHost));
		break;
	case 37:
		OnRecv_ItemSplit(*reinterpret_cast<ItemSplit*>(pHost));
		break;
	case 38:
		OnRecv_ItemAttrNtf(*reinterpret_cast<ItemAttrNtf*>(pHost));
		break;
	case 39:
		OnRecv_ItemUpdateNtf(*reinterpret_cast<ItemUpdateNtf*>(pHost));
		break;
	case 40:
		OnRecv_ItemBind(*reinterpret_cast<ItemBind*>(pHost));
		break;
	case 41:
		OnRecv_ItemApply(*reinterpret_cast<ItemApply*>(pHost));
		break;
	case 42:
		OnRecv_ItemApplyOnTarget(*reinterpret_cast<ItemApplyOnTarget*>(pHost));
		break;
	case 43:
		OnRecv_ItemApplyOnGrid(*reinterpret_cast<ItemApplyOnGrid*>(pHost));
		break;
	case 44:
		OnRecv_ItemArrange(*reinterpret_cast<ItemArrange*>(pHost));
		break;
	case 45:
		OnRecv_ItemPickUp(*reinterpret_cast<ItemPickUp*>(pHost));
		break;
	case 46:
		OnRecv_ItemDrop(*reinterpret_cast<ItemDrop*>(pHost));
		break;
	case 47:
		OnRecv_ItemTieUp(*reinterpret_cast<ItemTieUp*>(pHost));
		break;
	case 48:
		OnRecv_ItemTip(*reinterpret_cast<ItemTip*>(pHost));
		break;
	case 49:
		OnRecv_ItemTipBrd(*reinterpret_cast<ItemTipBrd*>(pHost));
		break;
	case 50:
		OnRecv_ItemTipNtf(*reinterpret_cast<ItemTipNtf*>(pHost));
		break;
	case 51:
		OnRecv_ItemEnhance(*reinterpret_cast<ItemEnhance*>(pHost));
		break;
	case 52:
		OnRecv_ItemDrill(*reinterpret_cast<ItemDrill*>(pHost));
		break;
	case 53:
		OnRecv_ItemSynthesis(*reinterpret_cast<ItemSynthesis*>(pHost));
		break;
	case 54:
		OnRecv_ItemEmbed(*reinterpret_cast<ItemEmbed*>(pHost));
		break;
	case 55:
		OnRecv_ItemDig(*reinterpret_cast<ItemDig*>(pHost));
		break;
	case 56:
		OnRecv_ItemIdentify(*reinterpret_cast<ItemIdentify*>(pHost));
		break;
	case 57:
		OnRecv_ItemRename(*reinterpret_cast<ItemRename*>(pHost));
		break;
	case 58:
		OnRecv_ItemRefine(*reinterpret_cast<ItemRefine*>(pHost));
		break;
	case 59:
		OnRecv_ItemRepairQuery(*reinterpret_cast<ItemRepairQuery*>(pHost));
		break;
	case 60:
		OnRecv_ItemRepairQueryNtf(*reinterpret_cast<ItemRepairQueryNtf*>(pHost));
		break;
	case 61:
		OnRecv_ItemRepair(*reinterpret_cast<ItemRepair*>(pHost));
		break;
	case 62:
		OnRecv_ItemSeg(*reinterpret_cast<ItemSeg*>(pHost));
		break;
	case 63:
		OnRecv_SkillAddReq(*reinterpret_cast<SkillAddReq*>(pHost));
		break;
	case 64:
		OnRecv_SkillAddAck(*reinterpret_cast<SkillAddAck*>(pHost));
		break;
	case 65:
		OnRecv_SkillDestroyReq(*reinterpret_cast<SkillDestroyReq*>(pHost));
		break;
	case 66:
		OnRecv_SkillDestroyAck(*reinterpret_cast<SkillDestroyAck*>(pHost));
		break;
	case 67:
		OnRecv_SkillSwitch(*reinterpret_cast<SkillSwitch*>(pHost));
		break;
	case 68:
		OnRecv_SkillSwitchAck(*reinterpret_cast<SkillSwitchAck*>(pHost));
		break;
	case 69:
		OnRecv_SkillProficiencyNtf(*reinterpret_cast<SkillProficiencyNtf*>(pHost));
		break;
	case 70:
		OnRecv_BuffAddAck(*reinterpret_cast<BuffAddAck*>(pHost));
		break;
	case 71:
		OnRecv_BuffDestroyReq(*reinterpret_cast<BuffDestroyReq*>(pHost));
		break;
	case 72:
		OnRecv_BuffDestroyAck(*reinterpret_cast<BuffDestroyAck*>(pHost));
		break;
	case 73:
		OnRecv_BuffUpdateNtf(*reinterpret_cast<BuffUpdateNtf*>(pHost));
		break;
	case 74:
		OnRecv_SpellTargetReadyNtf(*reinterpret_cast<SpellTargetReadyNtf*>(pHost));
		break;
	case 75:
		OnRecv_SpellGridReadyNtf(*reinterpret_cast<SpellGridReadyNtf*>(pHost));
		break;
	case 76:
		OnRecv_SpellTarget(*reinterpret_cast<SpellTarget*>(pHost));
		break;
	case 77:
		OnRecv_SpellGrid(*reinterpret_cast<SpellGrid*>(pHost));
		break;
	case 78:
		OnRecv_SpellAck(*reinterpret_cast<SpellAck*>(pHost));
		break;
	case 79:
		OnRecv_SpellNtf(*reinterpret_cast<SpellNtf*>(pHost));
		break;
	case 80:
		OnRecv_AttrShowNtf(*reinterpret_cast<AttrShowNtf*>(pHost));
		break;
	case 81:
		OnRecv_MissNtf(*reinterpret_cast<MissNtf*>(pHost));
		break;
	case 82:
		OnRecv_SpellDelayLostNtf(*reinterpret_cast<SpellDelayLostNtf*>(pHost));
		break;
	case 83:
		OnRecv_SpellDelayHitNtf(*reinterpret_cast<SpellDelayHitNtf*>(pHost));
		break;
	case 84:
		OnRecv_TradeNpcBuy(*reinterpret_cast<TradeNpcBuy*>(pHost));
		break;
	case 85:
		OnRecv_TradeNpcSell(*reinterpret_cast<TradeNpcSell*>(pHost));
		break;
	case 86:
		OnRecv_TradeNpcValueReq(*reinterpret_cast<TradeNpcValueReq*>(pHost));
		break;
	case 87:
		OnRecv_TradeNpcValueAck(*reinterpret_cast<TradeNpcValueAck*>(pHost));
		break;
	case 88:
		OnRecv_TradeNpcShopNtf(*reinterpret_cast<TradeNpcShopNtf*>(pHost));
		break;
	case 89:
		OnRecv_TradeP2PRequest(*reinterpret_cast<TradeP2PRequest*>(pHost));
		break;
	case 90:
		OnRecv_TradeP2PRequestNtf(*reinterpret_cast<TradeP2PRequestNtf*>(pHost));
		break;
	case 91:
		OnRecv_TradeP2PResponse(*reinterpret_cast<TradeP2PResponse*>(pHost));
		break;
	case 92:
		OnRecv_TradeP2POpenNtf(*reinterpret_cast<TradeP2POpenNtf*>(pHost));
		break;
	case 93:
		OnRecv_TradeP2PArrange(*reinterpret_cast<TradeP2PArrange*>(pHost));
		break;
	case 94:
		OnRecv_TradeP2PArrangeNtf(*reinterpret_cast<TradeP2PArrangeNtf*>(pHost));
		break;
	case 95:
		OnRecv_TradeP2PGold(*reinterpret_cast<TradeP2PGold*>(pHost));
		break;
	case 96:
		OnRecv_TradeP2PGoldNtf(*reinterpret_cast<TradeP2PGoldNtf*>(pHost));
		break;
	case 97:
		OnRecv_TradeP2PLock(*reinterpret_cast<TradeP2PLock*>(pHost));
		break;
	case 98:
		OnRecv_TradeP2PLockNtf(*reinterpret_cast<TradeP2PLockNtf*>(pHost));
		break;
	case 99:
		OnRecv_TradeP2PConfirme(*reinterpret_cast<TradeP2PConfirme*>(pHost));
		break;
	case 100:
		OnRecv_TradeP2PConfirmeNtf(*reinterpret_cast<TradeP2PConfirmeNtf*>(pHost));
		break;
	case 101:
		OnRecv_TradeP2PClose(*reinterpret_cast<TradeP2PClose*>(pHost));
		break;
	case 102:
		OnRecv_TradeP2PCloseNtf(*reinterpret_cast<TradeP2PCloseNtf*>(pHost));
		break;
	case 103:
		OnRecv_TradeStallReady(*reinterpret_cast<TradeStallReady*>(pHost));
		break;
	case 104:
		OnRecv_TradeStallReadyNtf(*reinterpret_cast<TradeStallReadyNtf*>(pHost));
		break;
	case 105:
		OnRecv_TradeStall(*reinterpret_cast<TradeStall*>(pHost));
		break;
	case 106:
		OnRecv_TradeStallNtf(*reinterpret_cast<TradeStallNtf*>(pHost));
		break;
	case 107:
		OnRecv_TradeStallArrange(*reinterpret_cast<TradeStallArrange*>(pHost));
		break;
	case 108:
		OnRecv_TradeStallQuery(*reinterpret_cast<TradeStallQuery*>(pHost));
		break;
	case 109:
		OnRecv_TradeStallQueryNtf(*reinterpret_cast<TradeStallQueryNtf*>(pHost));
		break;
	case 110:
		OnRecv_TradeStallBuy(*reinterpret_cast<TradeStallBuy*>(pHost));
		break;
	case 111:
		OnRecv_TradeStallBuyNtf(*reinterpret_cast<TradeStallBuyNtf*>(pHost));
		break;
	case 112:
		OnRecv_TradeStallClose(*reinterpret_cast<TradeStallClose*>(pHost));
		break;
	case 113:
		OnRecv_TradeStallCloseNtf(*reinterpret_cast<TradeStallCloseNtf*>(pHost));
		break;
	case 114:
		OnRecv_PlayerSwitch(*reinterpret_cast<PlayerSwitch*>(pHost));
		break;
	case 115:
		OnRecv_AtkModeReq(*reinterpret_cast<AtkModeReq*>(pHost));
		break;
	case 116:
		OnRecv_ServantModeReq(*reinterpret_cast<ServantModeReq*>(pHost));
		break;
	case 117:
		OnRecv_RoleAddPoint(*reinterpret_cast<RoleAddPoint*>(pHost));
		break;
	case 118:
		OnRecv_LevelUpNtf(*reinterpret_cast<LevelUpNtf*>(pHost));
		break;
	case 119:
		OnRecv_PlayerQuery(*reinterpret_cast<PlayerQuery*>(pHost));
		break;
	case 120:
		OnRecv_PlayerQueryBrd(*reinterpret_cast<PlayerQueryBrd*>(pHost));
		break;
	case 121:
		OnRecv_PlayerQueryNtf(*reinterpret_cast<PlayerQueryNtf*>(pHost));
		break;
	case 122:
		OnRecv_PlayerSiteSeg(*reinterpret_cast<PlayerSiteSeg*>(pHost));
		break;
	case 123:
		OnRecv_PlayerSiteSegBrd(*reinterpret_cast<PlayerSiteSegBrd*>(pHost));
		break;
	case 124:
		OnRecv_PlayerSiteSegNtf(*reinterpret_cast<PlayerSiteSegNtf*>(pHost));
		break;
	case 125:
		OnRecv_TitleAdd(*reinterpret_cast<TitleAdd*>(pHost));
		break;
	case 126:
		OnRecv_TitleRemove(*reinterpret_cast<TitleRemove*>(pHost));
		break;
	case 127:
		OnRecv_TitleApply(*reinterpret_cast<TitleApply*>(pHost));
		break;
	case 128:
		OnRecv_TitleAddAck(*reinterpret_cast<TitleAddAck*>(pHost));
		break;
	case 129:
		OnRecv_TitleRemoveAck(*reinterpret_cast<TitleRemoveAck*>(pHost));
		break;
	case 130:
		OnRecv_SysMsgNtf(*reinterpret_cast<SysMsgNtf*>(pHost));
		break;
	case 131:
		OnRecv_RelationChatNtf(*reinterpret_cast<RelationChatNtf*>(pHost));
		break;
	case 132:
		OnRecv_NpcSelect(*reinterpret_cast<NpcSelect*>(pHost));
		break;
	case 133:
		OnRecv_NpcTalkReq(*reinterpret_cast<NpcTalkReq*>(pHost));
		break;
	case 134:
		OnRecv_NpcTalkAck(*reinterpret_cast<NpcTalkAck*>(pHost));
		break;
	case 135:
		OnRecv_QuickBarSet(*reinterpret_cast<QuickBarSet*>(pHost));
		break;
	case 136:
		OnRecv_QuickBarSetNtf(*reinterpret_cast<QuickBarSetNtf*>(pHost));
		break;
	case 137:
		OnRecv_QuickBarRemove(*reinterpret_cast<QuickBarRemove*>(pHost));
		break;
	case 138:
		OnRecv_QuickBarRemoveNtf(*reinterpret_cast<QuickBarRemoveNtf*>(pHost));
		break;
	case 139:
		OnRecv_QuickBarMove(*reinterpret_cast<QuickBarMove*>(pHost));
		break;
	case 140:
		OnRecv_ShortcutSet(*reinterpret_cast<ShortcutSet*>(pHost));
		break;
	case 141:
		OnRecv_ShortcutNtf(*reinterpret_cast<ShortcutNtf*>(pHost));
		break;
	case 142:
		OnRecv_GoldDeposit(*reinterpret_cast<GoldDeposit*>(pHost));
		break;
	case 143:
		OnRecv_GoldTake(*reinterpret_cast<GoldTake*>(pHost));
		break;
	case 144:
		OnRecv_BeServantNtf(*reinterpret_cast<BeServantNtf*>(pHost));
		break;
	case 145:
		OnRecv_RoleAttrExtRefNtf(*reinterpret_cast<RoleAttrExtRefNtf*>(pHost));
		break;
	case 146:
		OnRecv_StartFamilyWarBrd(*reinterpret_cast<StartFamilyWarBrd*>(pHost));
		break;
	case 147:
		OnRecv_RunningFamilyWarNtf(*reinterpret_cast<RunningFamilyWarNtf*>(pHost));
		break;
	case 148:
		OnRecv_CastleNtf(*reinterpret_cast<CastleNtf*>(pHost));
		break;
	case 149:
		OnRecv_GoldDrop(*reinterpret_cast<GoldDrop*>(pHost));
		break;
	case 150:
		OnRecv_PlayerFamilyChangeNtf(*reinterpret_cast<PlayerFamilyChangeNtf*>(pHost));
		break;
	case 151:
		OnRecv_NotifyMapEffect(*reinterpret_cast<NotifyMapEffect*>(pHost));
		break;
	case 152:
		OnRecv_RoleTalkNtf(*reinterpret_cast<RoleTalkNtf*>(pHost));
		break;
	case 153:
		OnRecv_ProgressStartNtf(*reinterpret_cast<ProgressStartNtf*>(pHost));
		break;
	case 154:
		OnRecv_ProgressCancelNtf(*reinterpret_cast<ProgressCancelNtf*>(pHost));
		break;
	case 155:
		OnRecv_VerifyImageQuestion(*reinterpret_cast<VerifyImageQuestion*>(pHost));
		break;
	case 156:
		OnRecv_VerifyImageAnswer(*reinterpret_cast<VerifyImageAnswer*>(pHost));
		break;
	case 157:
		OnRecv_VerifyImageReset(*reinterpret_cast<VerifyImageReset*>(pHost));
		break;
	case 158:
		OnRecv_VerifyImageResultNtf(*reinterpret_cast<VerifyImageResultNtf*>(pHost));
		break;
	case 159:
		OnRecv_TradeMallBuy(*reinterpret_cast<TradeMallBuy*>(pHost));
		break;
	case 160:
		OnRecv_TradeMallListReq(*reinterpret_cast<TradeMallListReq*>(pHost));
		break;
	case 161:
		OnRecv_TradeMallListAck(*reinterpret_cast<TradeMallListAck*>(pHost));
		break;
	case 162:
		OnRecv_TradeMallItemDetailReq(*reinterpret_cast<TradeMallItemDetailReq*>(pHost));
		break;
	case 163:
		OnRecv_TradeMallItemDetailAck(*reinterpret_cast<TradeMallItemDetailAck*>(pHost));
		break;
	case 164:
		OnRecv_TradeMallChartsReq(*reinterpret_cast<TradeMallChartsReq*>(pHost));
		break;
	case 165:
		OnRecv_TradeMallChartsAck(*reinterpret_cast<TradeMallChartsAck*>(pHost));
		break;
	case 166:
		OnRecv_NpcTalkReqEx(*reinterpret_cast<NpcTalkReqEx*>(pHost));
		break;
	case 167:
		OnRecv_NpcTalkAckEx(*reinterpret_cast<NpcTalkAckEx*>(pHost));
		break;
	case 168:
		OnRecv_QuestAccept(*reinterpret_cast<QuestAccept*>(pHost));
		break;
	case 169:
		OnRecv_QuestAddNtf(*reinterpret_cast<QuestAddNtf*>(pHost));
		break;
	case 170:
		OnRecv_QuestAccomplish(*reinterpret_cast<QuestAccomplish*>(pHost));
		break;
	case 171:
		OnRecv_QuestUpdateNtf(*reinterpret_cast<QuestUpdateNtf*>(pHost));
		break;
	case 172:
		OnRecv_QuestTrackChange(*reinterpret_cast<QuestTrackChange*>(pHost));
		break;
	case 173:
		OnRecv_QuestTrackChangeNtf(*reinterpret_cast<QuestTrackChangeNtf*>(pHost));
		break;
	case 174:
		OnRecv_QuestReadyNtf(*reinterpret_cast<QuestReadyNtf*>(pHost));
		break;
	case 175:
		OnRecv_QuestCompleteNtf(*reinterpret_cast<QuestCompleteNtf*>(pHost));
		break;
	case 176:
		OnRecv_QuestDrop(*reinterpret_cast<QuestDrop*>(pHost));
		break;
	case 177:
		OnRecv_QuestDropNtf(*reinterpret_cast<QuestDropNtf*>(pHost));
		break;
	case 178:
		OnRecv_QuestQueryCanAccept(*reinterpret_cast<QuestQueryCanAccept*>(pHost));
		break;
	case 179:
		OnRecv_QuestQueryCanAcceptNtf(*reinterpret_cast<QuestQueryCanAcceptNtf*>(pHost));
		break;
	case 180:
		OnRecv_DelegateSellCmd(*reinterpret_cast<DelegateSellCmd*>(pHost));
		break;
	case 181:
		OnRecv_DelegateBuyCmd(*reinterpret_cast<DelegateBuyCmd*>(pHost));
		break;
	case 182:
		OnRecv_DelegateSellListReq(*reinterpret_cast<DelegateSellListReq*>(pHost));
		break;
	case 183:
		OnRecv_DelegateSellListAck(*reinterpret_cast<DelegateSellListAck*>(pHost));
		break;
	case 184:
		OnRecv_DelegateBuyListReq(*reinterpret_cast<DelegateBuyListReq*>(pHost));
		break;
	//case 185:
	//	OnRecv_DelegateBuyListAck(*reinterpret_cast<DelegateBuyListAck*>(pHost));
	//	break;
	case 186:
		OnRecv_MarketBuyCmd(*reinterpret_cast<MarketBuyCmd*>(pHost));
		break;
	case 187:
		OnRecv_MarketSellCmd(*reinterpret_cast<MarketSellCmd*>(pHost));
		break;
	case 188:
		OnRecv_DelegateCancel(*reinterpret_cast<DelegateCancel*>(pHost));
		break;
	case 189:
		OnRecv_DelegateMineReq(*reinterpret_cast<DelegateMineReq*>(pHost));
		break;
	//case 190:
	//	OnRecv_DelegateMineAck(*reinterpret_cast<DelegateMineAck*>(pHost));
	//	break;
	case 191:
		OnRecv_AttrShowExNtf(*reinterpret_cast<AttrShowExNtf*>(pHost));
		break;
	case 192:
		OnRecv_CampaignListReq(*reinterpret_cast<CampaignListReq*>(pHost));
		break;
	case 193:
		OnRecv_CampaignListAck(*reinterpret_cast<CampaignListAck*>(pHost));
		break;
	case 194:
		OnRecv_CampaignDetailReq(*reinterpret_cast<CampaignDetailReq*>(pHost));
		break;
	case 195:
		OnRecv_CampaignDetailAck(*reinterpret_cast<CampaignDetailAck*>(pHost));
		break;
	case 196:
		OnRecv_InputDlgReq(*reinterpret_cast<InputDlgReq*>(pHost));
		break;
	case 197:
		OnRecv_InputDlgAck(*reinterpret_cast<InputDlgAck*>(pHost));
		break;
	case 198:
		OnRecv_MsgDlgReq(*reinterpret_cast<MsgDlgReq*>(pHost));
		break;
	case 199:
		OnRecv_MsgDlgAck(*reinterpret_cast<MsgDlgAck*>(pHost));
		break;
	case 200:
		OnRecv_WebDlgNtf(*reinterpret_cast<WebDlgNtf*>(pHost));
		break;
	case 201:
		OnRecv_OpenWebPageNtf(*reinterpret_cast<OpenWebPageNtf*>(pHost));
		break;
	case 202:
		OnRecv_GlobalNtf(*reinterpret_cast<GlobalNtf*>(pHost));
		break;
	case 203:
		OnRecv_SpeakerMsgAck(*reinterpret_cast<SpeakerMsgAck*>(pHost));
		break;
	case 204:
		OnRecv_ClientKeepAlive(*reinterpret_cast<ClientKeepAlive*>(pHost));
		break;
	case 205:
		OnRecv_FamilyAllyTableNtf(*reinterpret_cast<FamilyAllyTableNtf*>(pHost));
		break;
	case 206:
		OnRecv_PlayerCustomReq(*reinterpret_cast<PlayerCustomReq*>(pHost));
		break;
	case 207:
		OnRecv_PlayerCustomAck(*reinterpret_cast<PlayerCustomAck*>(pHost));
		break;
	case 208:
		OnRecv_WebPageNtf(*reinterpret_cast<WebPageNtf*>(pHost));
		break;
	case 209:
		OnRecv_CustomNtf(*reinterpret_cast<CustomNtf*>(pHost));
		break;
	case 210:
		OnRecv_CustomBroadcast(*reinterpret_cast<CustomBroadcast*>(pHost));
		break;
	case 211:
		OnRecv_ItemCustomNtf(*reinterpret_cast<ItemCustomNtf*>(pHost));
		break;
	case 212:
		OnRecv_TaobaoNpcBuy(*reinterpret_cast<TaobaoNpcBuy*>(pHost));
		break;
	case 213:
		OnRecv_TaobaoNpcShopReq(*reinterpret_cast<TaobaoNpcShopReq*>(pHost));
		break;
	case 214:
		OnRecv_TaobaoNpcShopAck(*reinterpret_cast<TaobaoNpcShopAck*>(pHost));
		break;
	case 215:
		OnRecv_RunClientScriptNtf(*reinterpret_cast<RunClientScriptNtf*>(pHost));
		break;
	case 216:
		OnRecv_ObjCustomNtf(*reinterpret_cast<ObjCustomNtf*>(pHost));
		break;
	case 217:
		OnRecv_CampaignJoinNtf(*reinterpret_cast<CampaignJoinNtf*>(pHost));
		break;
	case 218:
		OnRecv_MapReq(*reinterpret_cast<MapReq*>(pHost));
		break;
	case 219:
		OnRecv_MapNtf(*reinterpret_cast<MapNtf*>(pHost));
		break;
	case 220:
		OnRecv_GridReq(*reinterpret_cast<GridReq*>(pHost));
		break;
	case 221:
		OnRecv_GridNtf(*reinterpret_cast<GridNtf*>(pHost));
		break;
	case 222:
		OnRecv_TableReq(*reinterpret_cast<TableReq*>(pHost));
		break;
	case 223:
		OnRecv_TableNtf(*reinterpret_cast<TableNtf*>(pHost));
		break;
	case 224:
		OnRecv_TableDataReq(*reinterpret_cast<TableDataReq*>(pHost));
		break;
	case 225:
		OnRecv_TableDataNtf(*reinterpret_cast<TableDataNtf*>(pHost));
		break;
	case 226:
		OnRecv_CampaignRunNtf(*reinterpret_cast<CampaignRunNtf*>(pHost));
		break;
	case 227:
		OnRecv_RideReq(*reinterpret_cast<RideReq*>(pHost));
		break;
	case 228:
		OnRecv_RideNtf(*reinterpret_cast<RideNtf*>(pHost));
		break;
	case 229:
		OnRecv_PermissionReq(*reinterpret_cast<PermissionReq*>(pHost));
		break;
	case 230:
		OnRecv_VipItemListReq(*reinterpret_cast<VipItemListReq*>(pHost));
		break;
	case 231:
		OnRecv_VipItemListAck(*reinterpret_cast<VipItemListAck*>(pHost));
		break;
	case 232:
		OnRecv_VipLevelBuyReq(*reinterpret_cast<VipLevelBuyReq*>(pHost));
		break;
	case 233:
		OnRecv_VipLevelBuyAck(*reinterpret_cast<VipLevelBuyAck*>(pHost));
		break;
	case 234:
		OnRecv_VipItemBuyReq(*reinterpret_cast<VipItemBuyReq*>(pHost));
		break;
	case 235:
		OnRecv_VipItemBuyAck(*reinterpret_cast<VipItemBuyAck*>(pHost));
		break;
	case 236:
		OnRecv_VipItemApplyReq(*reinterpret_cast<VipItemApplyReq*>(pHost));
		break;
	case 237:
		OnRecv_VipItemApplyAck(*reinterpret_cast<VipItemApplyAck*>(pHost));
		break;
	case 238:
		OnRecv_VipExpireNtf(*reinterpret_cast<VipExpireNtf*>(pHost));
		break;
	case 239:
		OnRecv_VipLevelListReq(*reinterpret_cast<VipLevelListReq*>(pHost));
		break;
	case 240:
		OnRecv_VipLevelListAck(*reinterpret_cast<VipLevelListAck*>(pHost));
		break;
	case 241:
		OnRecv_TradeNpcShopNumNtf(*reinterpret_cast<TradeNpcShopNumNtf*>(pHost));
		break;
	case 242:
		OnRecv_SubmitFormAck(*reinterpret_cast<SubmitFormAck*>(pHost));
		break;
	case 243:
		OnRecv_ItemAttrReq(*reinterpret_cast<ItemAttrReq*>(pHost));
		break;
	case 244:
		OnRecv_QuestStateReq(*reinterpret_cast<QuestStateReq*>(pHost));
		break;
	case 245:
		OnRecv_QuestStateNtf(*reinterpret_cast<QuestStateNtf*>(pHost));
		break;
	case 246:
		OnRecv_QuestQueryReq(*reinterpret_cast<QuestQueryReq*>(pHost));
		break;
	case 247:
		OnRecv_QuestQueryNtf(*reinterpret_cast<QuestQueryNtf*>(pHost));
		break;
	case 248:
		OnRecv_GloryFinishNtf(*reinterpret_cast<GloryFinishNtf*>(pHost));
		break;
	case 249:
		OnRecv_GloryStateQuery(*reinterpret_cast<GloryStateQuery*>(pHost));
		break;
	case 250:
		OnRecv_GloryStateAck(*reinterpret_cast<GloryStateAck*>(pHost));
		break;
	case 251:
		OnRecv_GloryAwardGet(*reinterpret_cast<GloryAwardGet*>(pHost));
		break;
	case 252:
		OnRecv_TraceReq(*reinterpret_cast<TraceReq*>(pHost));
		break;
	case 253:
		OnRecv_QuestNpcStateNtf(*reinterpret_cast<QuestNpcStateNtf*>(pHost));
		break;
	case 254:
		OnRecv_ClientKeepAliveRet(*reinterpret_cast<ClientKeepAliveRet*>(pHost));
		break;
	case 255:
		OnRecv_RemoveClientNtf(*reinterpret_cast<RemoveClientNtf*>(pHost));
		break;
	case 256:
		OnRecv_SceneMagicAppearNtf(*reinterpret_cast<SceneMagicAppearNtf*>(pHost));
		break;
	case 257:
		OnRecv_DummyPackage(*reinterpret_cast<DummyPackage*>(pHost));
		break;
	case 258:
		OnRecv_DummyItemMove(*reinterpret_cast<DummyItemMove*>(pHost));
		break;
	case 259:
		OnRecv_DummyControlNtf(*reinterpret_cast<DummyControlNtf*>(pHost));
		break;
	case 260:
		OnRecv_ServantNumNtf(*reinterpret_cast<ServantNumNtf*>(pHost));
		break;
	case 261:
		OnRecv_DummyStateSwitchReq(*reinterpret_cast<DummyStateSwitchReq*>(pHost));
		break;
	case 262:
		OnRecv_DummyStateSwitchAck(*reinterpret_cast<DummyStateSwitchAck*>(pHost));
		break;
	case 263:
		OnRecv_HeroCreateNtf(*reinterpret_cast<HeroCreateNtf*>(pHost));
		break;
	case 264:
		OnRecv_HeroDestroyNtf(*reinterpret_cast<HeroDestroyNtf*>(pHost));
		break;
	case 265:
		OnRecv_AutoSetOptNtf(*reinterpret_cast<AutoSetOptNtf*>(pHost));
		break;
	case 266:
		OnRecv_AutoRunBeginNtf(*reinterpret_cast<AutoRunBeginNtf*>(pHost));
		break;
	case 267:
		OnRecv_AutoRunEndNtf(*reinterpret_cast<AutoRunEndNtf*>(pHost));
		break;
	case 268:
		OnRecv_NetCheckNtf(*reinterpret_cast<NetCheckNtf*>(pHost));
		break;
	case 269:
		OnRecv_HeroSkillSwitchReq(*reinterpret_cast<HeroSkillSwitchReq*>(pHost));
		break;
	case 270:
		OnRecv_HeroSkillSwitchAck(*reinterpret_cast<HeroSkillSwitchAck*>(pHost));
		break;
	case 271:
		OnRecv_MoveReqEx(*reinterpret_cast<MoveReqEx*>(pHost));
		break;
	case 272:
		OnRecv_SpellTargetEx(*reinterpret_cast<SpellTargetEx*>(pHost));
		break;
	case 273:
		OnRecv_SpellGridEx(*reinterpret_cast<SpellGridEx*>(pHost));
		break;
	case 274:
		OnRecv_HeroLockTargetCmd(*reinterpret_cast<HeroLockTargetCmd*>(pHost));
		break;
	case 275:
		OnRecv_ServantStatNtf(*reinterpret_cast<ServantStatNtf*>(pHost));
		break;
	case 276:
		OnRecv_JointHitNtf(*reinterpret_cast<JointHitNtf*>(pHost));
		break;
	case 277:
		OnRecv_JointHit(*reinterpret_cast<JointHit*>(pHost));
		break;
	case 278:
		OnRecv_QuestAcceptEx(*reinterpret_cast<QuestAcceptEx*>(pHost));
		break;
	case 279:
		OnRecv_QuestAccomplishEx(*reinterpret_cast<QuestAccomplishEx*>(pHost));
		break;
	case 280:
		OnRecv_HeroLockTargetAck(*reinterpret_cast<HeroLockTargetAck*>(pHost));
		break;
	case 281:
		OnRecv_ShieldActiveNtf(*reinterpret_cast<ShieldActiveNtf*>(pHost));
		break;
	case 282:
		OnRecv_ShieldRemoveNtf(*reinterpret_cast<ShieldRemoveNtf*>(pHost));
		break;
	case 283:
		OnRecv_PlayerQueryEx(*reinterpret_cast<PlayerQueryEx*>(pHost));
		break;
	case 284:
		OnRecv_PlayerQueryBrdEx(*reinterpret_cast<PlayerQueryBrdEx*>(pHost));
		break;
	case 285:
		OnRecv_GSVersion(*reinterpret_cast<GSVersion*>(pHost));
		break;
	case 286:
		OnRecv_UpdateCheckCode(*reinterpret_cast<UpdateCheckCode*>(pHost));
		break;
	case 287:
		OnRecv_MoveReq2(*reinterpret_cast<MoveReq2*>(pHost));
		break;
	case 288:
		OnRecv_SpellTarget2(*reinterpret_cast<SpellTarget2*>(pHost));
		break;
	case 289:
		OnRecv_SpellGrid2(*reinterpret_cast<SpellGrid2*>(pHost));
		break;
	case 290:
		OnRecv_NpcSelect2(*reinterpret_cast<NpcSelect2*>(pHost));
		break;
	case 291:
		OnRecv_NpcTalkReq2(*reinterpret_cast<NpcTalkReq2*>(pHost));
		break;
	case 292:
		OnRecv_ClientVerNtf(*reinterpret_cast<ClientVerNtf*>(pHost));
		break;
	case 293:
		OnRecv_ItemApply2(*reinterpret_cast<ItemApply2*>(pHost));
		break;
	case 294:
		OnRecv_MonsterAppearNtf2(*reinterpret_cast<MonsterAppearNtf2*>(pHost));
		break;
	case 295:
		OnRecv_ItemAppearNtf2(*reinterpret_cast<ItemAppearNtf2*>(pHost));
		break;
	case 296:
		OnRecv_ClientKeepAliveEx(*reinterpret_cast<ClientKeepAliveEx*>(pHost));
		break;
	case 297:
		OnRecv_GSVersionEx(*reinterpret_cast<GSVersionEx*>(pHost));
		break;
	case 298:
		OnRecv_ClientVerReq(*reinterpret_cast<ClientVerReq*>(pHost));
		break;
	case 299:
		OnRecv_NetDelayReq(*reinterpret_cast<NetDelayReq*>(pHost));
		break;
	case 300:
		OnRecv_NetDelayAck(*reinterpret_cast<NetDelayAck*>(pHost));
		break;
	case 301:
		OnRecv_ClientVerNtfEx(*reinterpret_cast<ClientVerNtfEx*>(pHost));
		break;
	case 302:
		OnRecv_ClientVerReq2(*reinterpret_cast<ClientVerReq2*>(pHost));
		break;
	case 303:
		OnRecv_ClientVerAck2(*reinterpret_cast<ClientVerAck2*>(pHost));
		break;
	case 304:
		OnRecv_NpcTalkReq3(*reinterpret_cast<NpcTalkReq3*>(pHost));
		break;
	case 305:
		OnRecv_NpcTalkAck3(*reinterpret_cast<NpcTalkAck3*>(pHost));
		break;
	case 306:
		OnRecv_AttrShowNtfEx(*reinterpret_cast<AttrShowNtfEx*>(pHost));
		break;
	case 307:
		OnRecv_EnterGSReqEx(*reinterpret_cast<EnterGSReqEx*>(pHost));
		break;
	case 308:
		OnRecv_ReloginNtf(*reinterpret_cast<ReloginNtf*>(pHost));
		break;
	case 309:
		OnRecv_BehaviorNtf(*reinterpret_cast<BehaviorNtf*>(pHost));
		break;
	case 310:
		OnRecv_FashionReq(*reinterpret_cast<FashionReq*>(pHost));
		break;
	case 311:
		OnRecv_FashionNtf(*reinterpret_cast<FashionNtf*>(pHost));
		break;
	case 312:
		OnRecv_ErrorNtf(*reinterpret_cast<ErrorNtf*>(pHost));
		break;
	case 313:
		OnRecv_NpcTalkReqEx3(*reinterpret_cast<NpcTalkReqEx3*>(pHost));
		break;
	case 314:
		OnRecv_NpcTalkAckEx3(*reinterpret_cast<NpcTalkAckEx3*>(pHost));
		break;
	case 315:
		OnRecv_SubmitForm2(*reinterpret_cast<SubmitForm2*>(pHost));
		break;
	case 316:
		OnRecv_SubmitFormAck2(*reinterpret_cast<SubmitFormAck2*>(pHost));
		break;
	case 317:
		OnRecv_RoleAddPointEx(*reinterpret_cast<RoleAddPointEx*>(pHost));
		break;
	case 318:
		OnRecv_GetClientCheckInfoReq(*reinterpret_cast<GetClientCheckInfoReq*>(pHost));
		break;
	case 319:
		OnRecv_GetClientCheckInfoAck(*reinterpret_cast<GetClientCheckInfoAck*>(pHost));
		break;
	case 320:
		OnRecv_GetMD5CheckListReq(*reinterpret_cast<GetMD5CheckListReq*>(pHost));
		break;
	case 321:
		OnRecv_GetMD5CheckListAck(*reinterpret_cast<GetMD5CheckListAck*>(pHost));
		break;
	case 322:
		OnRecv_DelayCloseNtf(*reinterpret_cast<DelayCloseNtf*>(pHost));
		break;
	case 323:
		OnRecv_FamilyJoinInviteReq(*reinterpret_cast<FamilyJoinInviteReq*>(pHost));
		break;
	case 324:
		OnRecv_FamilyJoinInviteAck(*reinterpret_cast<FamilyJoinInviteAck*>(pHost));
		break;
	case 325:
		OnRecv_FamilyRelationShipReq(*reinterpret_cast<FamilyRelationShipReq*>(pHost));
		break;
	case 326:
		OnRecv_FamilyRelationShipAck(*reinterpret_cast<FamilyRelationShipAck*>(pHost));
		break;
	case 327:
		OnRecv_MonsterAppearNtf3(*reinterpret_cast<MonsterAppearNtf3*>(pHost));
		break;
	case 328:
		OnRecv_MonsterAppearNtf4(*reinterpret_cast<MonsterAppearNtf4*>(pHost));
		break;
	case 329:
		OnRecv_GetAroundTeamReq(*reinterpret_cast<GetAroundTeamReq*>(pHost));
		break;
	case 330:
		OnRecv_GetAroundTeamAck(*reinterpret_cast<GetAroundTeamAck*>(pHost));
		break;
	case 331:
		OnRecv_MigrateRoleDataNtf(*reinterpret_cast<MigrateRoleDataNtf*>(pHost));
		break;
	case 332:
		OnRecv_PlayerAppearNtf2(*reinterpret_cast<PlayerAppearNtf2*>(pHost));
		break;
	case 333:
		OnRecv_RoleAppNtf2(*reinterpret_cast<RoleAppNtf2*>(pHost));
		break;
	case 334:
		OnRecv_ItemBatchDestroyNtf(*reinterpret_cast<ItemBatchDestroyNtf*>(pHost));
		break;
	case 335:
		OnRecv_SubmitForm3(*reinterpret_cast<SubmitForm3*>(pHost));
		break;
	case 336:
		OnRecv_SubmitFormAck3(*reinterpret_cast<SubmitFormAck3*>(pHost));
		break;
	case 337:
		OnRecv_ItemAppearNtf3(*reinterpret_cast<ItemAppearNtf3*>(pHost));
		break;
	case 338:
		OnRecv_ItemAppearNtf4(*reinterpret_cast<ItemAppearNtf4*>(pHost));
		break;
	case 339:
		OnRecv_InnerForceLevelUpReq(*reinterpret_cast<InnerForceLevelUpReq*>(pHost));
		break;
	case 340:
		OnRecv_InnerForceLevelUpAck(*reinterpret_cast<InnerForceLevelUpAck*>(pHost));
		break;
	case 341:
		OnRecv_ClientFangChenMiNtf(*reinterpret_cast<ClientFangChenMiNtf*>(pHost));
		break;
	case 342:
		OnRecv_DelegateMineAck2(*reinterpret_cast<DelegateMineAck2*>(pHost));
		break;
	case 343:
		OnRecv_DelegateBuyListAck2(*reinterpret_cast<DelegateBuyListAck2*>(pHost));
		break;
	case 344:
		OnRecv_FashionWeaponReq(*reinterpret_cast<FashionWeaponReq*>(pHost));
		break;
	case 345:
		OnRecv_FashionWeaponNtf(*reinterpret_cast<FashionWeaponNtf*>(pHost));
		break;
	case 346:
		OnRecv_PlayerAppearNtf3(*reinterpret_cast<PlayerAppearNtf3*>(pHost));
		break;
	case 347:
		OnRecv_MonsterAppearNtf5(*reinterpret_cast<MonsterAppearNtf5*>(pHost));
		break;
	case 348:
		OnRecv_MonsterAppearNtf6(*reinterpret_cast<MonsterAppearNtf6*>(pHost));
		break;
	case 349:
		OnRecv_CaptchaReq(*reinterpret_cast<CaptchaReq*>(pHost));
		break;
	case 350:
		OnRecv_CaptchaAck(*reinterpret_cast<CaptchaAck*>(pHost));
		break;
	case 351:
		OnRecv_AgentKeyReq(*reinterpret_cast<AgentKeyReq*>(pHost));
		break;
	case 352:
		OnRecv_AgentKeyAck(*reinterpret_cast<AgentKeyAck*>(pHost));
		break;
	case 353:
		OnRecv_PlatformInfoNtf(*reinterpret_cast<PlatformInfoNtf*>(pHost));
		break;
	case 354:
		OnRecv_AttrShowNtf2(*reinterpret_cast<AttrShowNtf2*>(pHost));
		break;
	case 355:
		OnRecv_AttrShowNtfEx2(*reinterpret_cast<AttrShowNtfEx2*>(pHost));
		break;
	case 356:
		OnRecv_BehaviorReq(*reinterpret_cast<BehaviorReq*>(pHost));
		break;
	case 357:
		OnRecv_FangChenMiNtf(*reinterpret_cast<FangChenMiNtf*>(pHost));
		break;
	case 358:
		OnRecv_NpcShopIdsNtf(*reinterpret_cast<NpcShopIdsNtf*>(pHost));
		break;
	case 359:
		OnRecv_CreateMobaRoomReq(*reinterpret_cast<CreateMobaRoomReq*>(pHost));
		break;
	case 360:
		OnRecv_CreateMobaRoomAck(*reinterpret_cast<CreateMobaRoomAck*>(pHost));
		break;
	case 361:
		OnRecv_EnterMobaRoomReq(*reinterpret_cast<EnterMobaRoomReq*>(pHost));
		break;
	case 362:
		OnRecv_EnterMobaRoomAck(*reinterpret_cast<EnterMobaRoomAck*>(pHost));
		break;
	case 363:
		OnRecv_ExitMobaRoomReq(*reinterpret_cast<ExitMobaRoomReq*>(pHost));
		break;
	case 364:
		OnRecv_ExitMobaRoomAck(*reinterpret_cast<ExitMobaRoomAck*>(pHost));
		break;
	case 365:
		OnRecv_GetMobaRoomListReq(*reinterpret_cast<GetMobaRoomListReq*>(pHost));
		break;
	case 366:
		OnRecv_MobaRoomListAck(*reinterpret_cast<MobaRoomListAck*>(pHost));
		break;
	case 367:
		OnRecv_MobaRoomMemberListNtf(*reinterpret_cast<MobaRoomMemberListNtf*>(pHost));
		break;
	case 368:
		OnRecv_GetMobaMemberListReq(*reinterpret_cast<GetMobaMemberListReq*>(pHost));
		break;
	case 369:
		OnRecv_MobaRoomKickReq(*reinterpret_cast<MobaRoomKickReq*>(pHost));
		break;
	case 370:
		OnRecv_MobaRoomKickAck(*reinterpret_cast<MobaRoomKickAck*>(pHost));
		break;
	case 371:
		OnRecv_MobaRoomKickedNtf(*reinterpret_cast<MobaRoomKickedNtf*>(pHost));
		break;
	case 372:
		OnRecv_MobaRoomCampReadyReq(*reinterpret_cast<MobaRoomCampReadyReq*>(pHost));
		break;
	case 373:
		OnRecv_MobaRoomCampReadyAck(*reinterpret_cast<MobaRoomCampReadyAck*>(pHost));
		break;
	case 374:
		OnRecv_MobaRoomCampReadyNtf(*reinterpret_cast<MobaRoomCampReadyNtf*>(pHost));
		break;
	case 375:
		OnRecv_MobaRoomGameStartNtf(*reinterpret_cast<MobaRoomGameStartNtf*>(pHost));
		break;
	case 376:
		OnRecv_MobaRoomSetViceHostReq(*reinterpret_cast<MobaRoomSetViceHostReq*>(pHost));
		break;
	case 377:
		OnRecv_MobaRoomSetViceHostAck(*reinterpret_cast<MobaRoomSetViceHostAck*>(pHost));
		break;
	case 378:
		OnRecv_MobaRoomToggleCampReq(*reinterpret_cast<MobaRoomToggleCampReq*>(pHost));
		break;
	case 379:
		OnRecv_MobaRoomToggleCampAck(*reinterpret_cast<MobaRoomToggleCampAck*>(pHost));
		break;
	case 380:
		OnRecv_MobaRoomDestroyNtf(*reinterpret_cast<MobaRoomDestroyNtf*>(pHost));
		break;
	case 381:
		OnRecv_MobaRoomMemberReadyReq(*reinterpret_cast<MobaRoomMemberReadyReq*>(pHost));
		break;
	case 382:
		OnRecv_MobaRoomMemberReadyAck(*reinterpret_cast<MobaRoomMemberReadyAck*>(pHost));
		break;
	case 383:
		OnRecv_MobaRoomMemberReadyNtf(*reinterpret_cast<MobaRoomMemberReadyNtf*>(pHost));
		break;
	case 384:
		OnRecv_MobaRoomUpdateNameAndPasswordReq(*reinterpret_cast<MobaRoomUpdateNameAndPasswordReq*>(pHost));
		break;
	case 385:
		OnRecv_MobaRoomUpdateNameAndPasswordAck(*reinterpret_cast<MobaRoomUpdateNameAndPasswordAck*>(pHost));
		break;
	case 386:
		OnRecv_MobaRoomNameUpdateNtf(*reinterpret_cast<MobaRoomNameUpdateNtf*>(pHost));
		break;
	case 387:
		OnRecv_MobaRoomChangeCampAndPosReq(*reinterpret_cast<MobaRoomChangeCampAndPosReq*>(pHost));
		break;
	case 388:
		OnRecv_MobaRoomChangeCampAndPosAck(*reinterpret_cast<MobaRoomChangeCampAndPosAck*>(pHost));
		break;
	case 389:
		OnRecv_ReloginRefreshReq(*reinterpret_cast<ReloginRefreshReq*>(pHost));
		break;
	case 390:
		OnRecv_GameGuardReq(*reinterpret_cast<GameGuardReq*>(pHost));
		break;
	case 391:
		OnRecv_GameGuardAck(*reinterpret_cast<GameGuardAck*>(pHost));
		break;
	case 392:
		OnRecv_GameGuardCheckFailedNtf(*reinterpret_cast<GameGuardCheckFailedNtf*>(pHost));
		break;
	case 393:
		OnRecv_GameGuardHackRpt(*reinterpret_cast<GameGuardHackRpt*>(pHost));
		break;
	case 394:
		OnRecv_GameGuardHeartBeat(*reinterpret_cast<GameGuardHeartBeat*>(pHost));
		break;
	case 395:
		OnRecv_BangcleHeartBeat(*reinterpret_cast<BangcleHeartBeat*>(pHost));
		break;
	case 396:
		OnRecv_TradeStallSetBuyList(*reinterpret_cast<TradeStallSetBuyList*>(pHost));
		break;
	case 397:
		OnRecv_TradeStallQueryBuyGoodsNtf(*reinterpret_cast<TradeStallQueryBuyGoodsNtf*>(pHost));
		break;
	case 398:
		OnRecv_TradeStallSell(*reinterpret_cast<TradeStallSell*>(pHost));
		break;
	case 399:
		OnRecv_TradeStallSellNtf(*reinterpret_cast<TradeStallSellNtf*>(pHost));
		break;
	case 400:
		OnRecv_TaobaoNpcShopReqEx(*reinterpret_cast<TaobaoNpcShopReqEx*>(pHost));
		break;
	case 401:
		OnRecv_TaobaoNpcShopAckEx(*reinterpret_cast<TaobaoNpcShopAckEx*>(pHost));
		break;
	case 402:
		OnRecv_SkillCDChangedNtf(*reinterpret_cast<SkillCDChangedNtf*>(pHost));
		break;
	case 403:
		OnRecv_SubmitForm4(*reinterpret_cast<SubmitForm4*>(pHost));
		break;
	case 404:
		OnRecv_SubmitFormAck4(*reinterpret_cast<SubmitFormAck4*>(pHost));
		break;
	case 405:
		OnRecv_QuestAddNtf2(*reinterpret_cast<QuestAddNtf2*>(pHost));
		break;
    case 406:
        OnRecv_SkillCDPermenantChangedNtf(*reinterpret_cast<SkillCDPermenantChangedNtf*>(pHost));
        break;
	default:
		return false;
	}

	return true;
}

