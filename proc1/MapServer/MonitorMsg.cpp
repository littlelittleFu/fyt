#include "stdafx.h"
#include "MonitorMsg.h"

IMPL_SINGLETON(MonitorMsg);

void MonitorMsg::SendMonitorChatMsg(Player* fromPlayer, Player* toPlayer, uint16_t type, const std::string& content)
{
	MSG_BUFFER_DATA(ProtoMS_MonitorChatMsg, data);
	if (!fromPlayer)return;
	if (!type && !toPlayer)return;

	auto channel = HostChatTypeToPlatform(type);
	if (!channel) {
		LOG_ERROR("MonitorChatMsg failed! non chat type");
		return;
	}
	data.info.channel = channel;
	strcpy_s(data.info.content, _countof(data.info.content), content.c_str());
	if (type == relation_chat_ntf_type_guild) {
		auto guild = fromPlayer->GetGuildDataMgr().GetGuild();
		if (!guild)return;
		strcpy_s(data.info.guild, _countof(data.info.guild), guild->name.c_str());
	}
	auto stamp = ITimeHelper::GetInstance()->GetCurTimeStrMS();
	strcpy_s(data.info.stamp, _countof(data.info.stamp), stamp.c_str());
	data.info.user_id = fromPlayer->GetUserID();
	strcpy_s(data.info.user_name, _countof(data.info.user_name), fromPlayer->GetName().c_str());
	if (toPlayer){
		data.info.to_user_id = toPlayer->GetUserID();
		strcpy_s(data.info.to_user_name, _countof(data.info.to_user_name), toPlayer->GetName().c_str());
	}

	SendDataBySessionType(SESSION_TYPE_MS2CS, data);
}

uint16_t MonitorMsg::HostChatTypeToPlatform(uint16_t type)
{
	switch (type) {
	case 0:
		return middle_platform_chat_type_private;
	case lua_chat_msg_dialog_current:
		return middle_platform_chat_type_near;
	case lua_chat_msg_dialog_team:
		return middle_platform_chat_type_team;
	case lua_chat_msg_dialog_guild:
		return middle_platform_chat_type_guild;
	case lua_chat_msg_dialog_world:
		return middle_platform_chat_type_map;
	case lua_chat_msg_dialog_trumpt:
		return middle_platform_chat_type_tumpt;
	case lua_chat_msg_dialog_whole:
		return middle_platform_chat_type_world;
	default:
		return middle_platform_chat_type_non;
	}
}
