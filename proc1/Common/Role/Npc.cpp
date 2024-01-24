#include "stdafx.h"
#include "Npc.h"
#include "RoleMove.h"
#include "Map.h"

Npc::Npc() : Role(role_type_npc)
{
}

Npc::~Npc()
{

}

uint16_t Npc::NpcTalkReq(uint16_t id) 
{
	uint16_t ret = 0;
	LuaBindCallRet(ret, LUA_SCRIPT_FUNC(this, "OnNpcTalkReq"), GetGUIDAsString(), id);
	return ret;
}

uint16_t Npc::NpcTalkAck(const std::string& ack)
{
	if (ack.empty()) {
		LOG_NORMAL("talk ack is error!!!");
	}
	/**/

	//unsigned int session_id;
	//SEND_PKG_GC(session_id,ack.c_str(),ack.length());
	return 0;
}

void Npc::SetScriptName(const std::string& scriptName)
{
	if (!scriptName.empty() && scriptName != "0") {
		Role::SetScriptName(scriptName);
	}
	else {
		Role::SetScriptName("Npc");
	}
}

void Npc::Init(uint64_t guid, DATA::Npc *pConfig)
{
    if (!pConfig) return;

    SetGUID(guid);
    SetName(pConfig->Name);
    SetScriptName(pConfig->Script);

    mRoleAttr = new RoleAttr(this);
    mRoleState = new RoleState(this);

	Role::Init();
	Role::InitRoleProp(pConfig);
    mNpcTemplateID = pConfig->Id;
}

bool Npc::MakeNpcAppearNtfData(ProtoMS_NpcAppearNtf &npcAppearNtf)
{
    auto *cfg = GetConfig();
    if (!cfg) return false;

    npcAppearNtf.npc_guid = GetGUID();
    npcAppearNtf.template_id = cfg->Id;
    npcAppearNtf.dst_x = GetRolePosX();
    npcAppearNtf.dst_y = GetRolePosY();
    npcAppearNtf.dir = GetRoleDir();
    strcpy_s(npcAppearNtf.name, _countof(npcAppearNtf.name), GetName().c_str());
	npcAppearNtf.modelid = GetRoleProp(role_changed_modelid);
    return true;
}

