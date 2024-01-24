#include "stdafx.h"
#include"mail_table.h"
IMPL_SINGLETON(mail)
void mail::InitMail_table()
{
	//memset(&mail_map, 0,sizeof(mail_map));
}

void mail::AddMail(uint8_t num, const MAIL_INFO* data)
{
	for (int i = 0; i < num; ++i)
	{
		if (!mail_map.empty() && mail_map.find(data[i].playerguid) != mail_map.end()) {
			auto vmail_iter = mail_map.find(data[i].playerguid);
			auto& maildata = data[i];
			auto mailiter =find_if(vmail_iter->second.begin(), vmail_iter->second.end(), [&maildata](const MAIL_INFO&info) {
				if (info.mail_id == maildata.mail_id)return true;
				return false;
				});
			if (mailiter == vmail_iter->second.end())
			{
				vmail_iter->second.push_back(data[i]);
			}
		}
		else {
			vector<MAIL_INFO>maildata;
			maildata.push_back(data[i]);
			mail_map.insert(make_pair(data[i].playerguid, maildata));
		}
	}

}

void mail::AddMailToDB(uint64_t guid, const string& name, const MAIL_INFO& data, uint32_t token)
{
	MSG_BUFFER_DATA(ProtoMS_AddSysNewMail,msg);
	strcpy_s(msg.rolename, sizeof(msg.rolename), name.c_str());
	msg.guid[0] = guid;
	msg.num = 1;
	msg.infos = data;
	msg.addType = ProtoMS_AddSysNewMail::add_type::add_type_by_guid;
	SendDataBySessionType(SESSION_TYPE_CS2DB, msg);
}

void mail::DeleteMail(uint64_t playerguid, uint64_t mailid)
{
	auto vmail_iter = mail_map.find(playerguid);
	if (vmail_iter != mail_map.end()) {
		auto simple_mail_iter = find_if(vmail_iter->second.begin(), vmail_iter->second.end(), [&mailid](MAIL_INFO data) {return data.mail_id == mailid; });
		if (simple_mail_iter != vmail_iter->second.end()) {
			simple_mail_iter->status |= mail_status_delete;
		}
	}
}

int mail::GetMailCount(uint64_t playerguid)
{
	auto vmail_iter = mail_map.find(playerguid);
	if (vmail_iter != mail_map.end()) {
		return vmail_iter->second.size();
	}
	return 0;
}

void mail::DeleteMailInfoByRoleGUID(uint64_t playerguid)
{
	if (mail_map.empty()) { return; }
	auto it = mail_map.find(playerguid);
	if (it != mail_map.end()) {
		mail_map.erase(it);
	}
}

void mail::GetMailInfo(uint64_t playerguid, vector<MAIL_INFO>& data)
{
	auto it = mail_map.find(playerguid);
	if (it != mail_map.end()) {
		for (int i = 0; i < it->second.size(); ++i)
		{
			data.push_back(it->second[i]);
		}
	}
}

bool mail::FillCurrencyInfo(uint8_t type, int64_t value, MAIL_INFO& infos)
{
	if (infos.currency_type_num >= MAX_MAIL_CURRENCY_TYPE_NUM) return false;

	uint8_t ctype = role_gold;
	if (value != 0) {
	switch (type)
	{
	case stall_price_ingot:
		ctype = role_ingot;
		infos.status |= mail_status_yuanbao;
		break;
	case stall_price_bind_ingot:
		ctype = role_bind_ingot;
		infos.status |= mail_status_bind_yuanbao;
		break;
	case stall_price_integral:
		ctype = role_integral;
		infos.status |= mail_status_integral;
		break;
	case stall_price_gold:
		ctype = role_gold;
		infos.status |= mail_status_gold;
		break;
	case stall_price_bind_gold:
		ctype = role_bind_gold;
		infos.status |= mail_status_bind_gold;
		break;
	default:
		return false;
	}
	}
	infos.mail_currency_info[infos.currency_type_num].type = ctype;
	infos.mail_currency_info[infos.currency_type_num].num = value;
	++infos.currency_type_num;
	return true;
}
