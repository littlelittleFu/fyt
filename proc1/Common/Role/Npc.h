#pragma once
#include "Role.h"
#include "npc_table.hpp"

class Npc : public Role
{
public:
	Npc();
	virtual ~Npc();

	uint16_t NpcTalkReq(uint16_t id);
	uint16_t NpcTalkAck(const std::string &ack);

public:

    void Init(uint64_t guid, DATA::Npc *pConfig);
	DATA::Npc* GetConfig() { return sNpcConfig.Get(mNpcTemplateID); }
	void SetScriptName(const std::string& scriptName) override;
    bool MakeNpcAppearNtfData(ProtoMS_NpcAppearNtf &npcAppearNtf);

    uint16_t GetTemplateID() { return mNpcTemplateID; }
	std::string GetKeyName() { return GetConfig() ? GetConfig()->KeyName : ""; }

private:
    uint16_t    mNpcTemplateID  = 0;
};
