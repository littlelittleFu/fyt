#include "stdafx.h"
#include "MailMgr.h"
#include "SessionFactory.h"
#include "CNetManager.h"
#include "Session.h"

void MailMgr::AddMailInfo(Session* session, Player* player, const MAIL_INFO& data)
{
	if (!player) return;
		
	auto& MailVector = player->GetMailInfo();
	MailVector.push_back(data);

	if (!(data.status & mail_status_unread))return;
	ProtoMS_NewMailNtf ack;
	ack.sessid = player->GetClSessionID();
	SendDataBySessionID(player->GetGsSessionID(), ack);
}

void MailMgr::GetMailList(Session* session, Player* player, uint64_t mailid, int32_t type)
{
	if (!player) return;
	if (!session) return;
	// 获取邮件列表
	auto& MailVector = player->GetMailInfo();
	// 按时间排序
	sort(MailVector.begin(), MailVector.end(), [](MAIL_INFO& a, MAIL_INFO& b) {return a.send_timesmap < b.send_timesmap; });
	// 获取传入邮件id时间戳后面的邮件
	auto it = MailVector.begin();
	if (mailid) {
		it = find_if(MailVector.begin(), MailVector.end(), [&mailid](MAIL_INFO& a) {return mailid == a.mail_id; });
	}
	if (it == MailVector.end())return;
	// 获取符合条件的邮件 未过期 类型相同 传入邮件id时间戳后
	int allMailNum = 0;
	std::vector<uint64_t>mailIdVec;
	for (; it != MailVector.end();)
	{
		if ((time(nullptr) - it->send_timesmap) > MAX_MAIL_REMAIN_DATE)
		{
			it = MailVector.erase(it);
			continue;
		}

		if (it->status & mail_status_delete) {
			it = MailVector.erase(it);
			continue;
		}

		// 获取邮件列表时不再区分原邮件类型 获取全部
		//if (type == mail_type_all)
		//{
		//	mailIdVec.push_back(it->mail_id);
		//	++it;
		//	++allMailNum;
		//	continue;
		//}
		//if (it->type == type)
		//{
		mailIdVec.push_back(it->mail_id);
		++it;
		++allMailNum;
		//}
		//++it;
	}
	ProtoMS_GetMailListAck msg;
	msg.sessid = player->GetClSessionID();
	msg.num = 0;
	msg.page_num = allMailNum % 100 == 0 ? allMailNum / 100 : allMailNum / 100 + 1;
	for (auto i : mailIdVec)
	{
		auto mailInfo = find_if(MailVector.begin(), MailVector.end(), [=](const MAIL_INFO& info) { return info.mail_id == i; });
		if (mailInfo == MailVector.end())continue;
		msg.mails[msg.num].mail_id = mailInfo->mail_id;
		strcpy_s(msg.mails[msg.num].title, sizeof(msg.mails[msg.num].title), mailInfo->title);
		msg.mails[msg.num].send_time = mailInfo->send_timesmap;
		msg.mails[msg.num].left_time = (MAX_MAIL_REMAIN_DATE - (time(nullptr) - mailInfo->send_timesmap));
		strcpy_s(msg.mails[msg.num].sender, sizeof(msg.mails[msg.num].sender), mailInfo->sendername);
		msg.mails[msg.num].status = mailInfo->status;
		msg.mails[msg.num].type = mailInfo->type;
		++msg.num;
		if (msg.num == 100)
		{
			++msg.cur_page;
			session->SendPkg(&msg, sizeof(msg));
			msg.num = 0;
			memset(msg.mails, 0, _countof(msg.mails));
		}
	}
	if (msg.num && msg.num != 100)
	{
		++msg.cur_page;
		session->SendPkg(&msg, sizeof(msg));
	}

}

void MailMgr::OpenMail(Session* session, Player* player, uint64_t mailid)
{
	if (!player) return;
	if (!session) return;

	MSG_BUFFER_DATA(ProtoMS_OpenMailAck, msg);
	msg.mail_id = mailid;
	msg.sessid = player->GetClSessionID();
	auto& MailVector = player->GetMailInfo();
	auto it = find_if(MailVector.begin(), MailVector.end(), [&mailid](MAIL_INFO& a) {return mailid == a.mail_id; });
	if (it != MailVector.end()) {
		it->status = it->status & ~mail_status_read;
		strcpy_s(msg.mail.text, sizeof(msg.mail.text), it->text);
		msg.mail.gold = (*it).GetCurrencyNum(role_gold);
		msg.mail.yuanbao = (*it).GetCurrencyNum(role_ingot);
		msg.mail.integral = (*it).GetCurrencyNum(role_integral);
		msg.mail.bind_gold = (*it).GetCurrencyNum(role_bind_gold);
		msg.mail.bind_yunabao= (*it).GetCurrencyNum(role_bind_ingot);
		msg.mail.count = it->addition_item_num;
		for (int32_t i = 0; i < it->addition_item_num; ++i) {
				auto itemcfg = sItemConfig.GetByID(it->mail_addition_item_info[i].item_id);
				if (itemcfg == nullptr) continue; 
				msg.mail.items[i].base_info.id = itemcfg->Id;
				strcpy_s(msg.mail.items[i].base_info.name, sizeof(msg.mail.items[i].base_info.name), it->mail_addition_item_info[i].item_name);
				msg.mail.items[i].base_info.amount = it->mail_addition_item_info[i].count;
				msg.mail.items[i].base_info.is_bound = it->mail_addition_item_info[i].bind_status;
				msg.mail.items[i].base_info.guid = it->mail_addition_item_info[i].item_guid;
		}
	}
	session->SendPkg(&msg, sizeof(msg));
}

void MailMgr::DeleteMail(Session* session, Player* player, uint64_t mailid)
{
	if (!player) return;
	if (!session) return;

	ProtoMS_DeleteMailAck msg;
	msg.mail_id = mailid;
	msg.sessid = player->GetClSessionID();
	msg.errcode = ERR_MAIL_NO_MAIL;

	auto& MailVector = player->GetMailInfo();
	auto it = find_if(MailVector.begin(), MailVector.end(), [&mailid](MAIL_INFO& a) {return mailid == a.mail_id; });
	if (it != MailVector.end()) {
		if (it->status & mail_status_non_delete) {
			msg.errcode = ERR_MAIL_NON_DEL;
			session->SendPkg(&msg, sizeof(msg));
			return;
		}

		it->status |= mail_status_delete;

		ProtoMS_DeleteMailReq req;
		req.id = mailid;
		req.playerguid = player->GetGUID();
		req.sessid = player->GetClSessionID();
		SendDataBySessionType(SESSION_TYPE_MS2CS, req);
		return;
	}
	session->SendPkg(&msg, sizeof(msg));
}

void MailMgr::AttachMentGet(Session* session, Player* player, uint64_t mailid, uint8_t _index)
{
	if (!player) return;
	auto roleAttr = player->GetRoleAttr();
	if (!roleAttr) return;

	ProtoMS_MailAttachmentGetAck msg;
	msg.mail_id = mailid;
	msg.index = _index;
	msg.errcode = ERR_OK;
	msg.sessid = player->GetClSessionID();

	auto& MailVector = player->GetMailInfo();
	if (_index < mail_status_bite_end && _index > 0)
	{
		auto it = find_if(MailVector.begin(), MailVector.end(), [&mailid](MAIL_INFO& a) {return mailid == a.mail_id; });
		if (it != MailVector.end())
		{
			std::string desc = "邮件领取-";
			desc += std::to_string(it->type);
			log_params lp{ desc };

			switch (_index) {
			case mail_status_bite_gold:
			{
				if (!(it->status & mail_status_gold)) {
					msg.errcode = ERR_MAIL_HAD_GETED_ATTACHMENT;
					break;
				}
				roleAttr->AddProp64(role_gold, (*it).GetCurrencyNum(role_gold), lp);
				it->status &= ~mail_status_gold;
				break;
			}
			case mail_status_bite_yuanbao:
			{
				if (!(it->status & mail_status_yuanbao)) {
					msg.errcode = ERR_MAIL_HAD_GETED_ATTACHMENT;
					break;
				}
				roleAttr->AddProp64(role_ingot, (*it).GetCurrencyNum(role_ingot), lp);
				it->status &= ~mail_status_yuanbao;
				break;
			}
			case mail_status_bite_integral:
			{
				if (!(it->status & mail_status_integral)) {
					msg.errcode = ERR_MAIL_HAD_GETED_ATTACHMENT;
					break;
				}
				roleAttr->AddProp64(role_integral, (*it).GetCurrencyNum(role_integral), lp);
				it->status &= ~mail_status_integral;
				break;
			}
			case mail_status_bite_bind_gold:
			{
				if (!(it->status & mail_status_bind_gold)) {
					msg.errcode = ERR_MAIL_HAD_GETED_ATTACHMENT;
					break;
				}
				roleAttr->AddProp64(role_bind_gold, (*it).GetCurrencyNum(role_bind_gold), lp);
				it->status &= ~mail_status_bind_gold;
				break;
			}
			case mail_status_bite_bind_yuanbao:
			{
				if (!(it->status & mail_status_bind_yuanbao)) {
					msg.errcode = ERR_MAIL_HAD_GETED_ATTACHMENT;
					break;
				}
				roleAttr->AddProp64(role_bind_ingot, (*it).GetCurrencyNum(role_bind_ingot), lp);
				it->status &= ~mail_status_bind_yuanbao;
				break;
			}
			default:
			{
				if (!(it->status & (0x0001 << (_index)))) {
					msg.errcode = ERR_MAIL_HAD_GETED_ATTACHMENT;
					break;
				}
				if (!it->mail_addition_item_info[_index - 3].item_guid) {
					auto itemcfg = sItemConfig.GetByID(it->mail_addition_item_info[(_index - 3)].item_id);
					if (itemcfg == nullptr) break;
					msg.errcode = player->AddItemByKeyName(itemcfg->KeyName,
						it->mail_addition_item_info[(_index - 3)].count, it->mail_addition_item_info[(_index - 3)].bind_status, 0, lp);
					if (msg.errcode == ERR_OK) { it->status &= ~(0x0001 << (_index)); }
				}
				else {
					//附件有guid的去获取物品
					msg.errcode = GetMailAttachment(player, mailid, it->mail_addition_item_info[(_index - 3)], _index);
				}
				break;
			}
			}
		}
		else
		{
			msg.errcode = ERR_MAIL_NO_MAIL;
		}
	}
	else
	{
		msg.errcode = ERR_MAIL_NON_ADDITION_INDEX;
	}
	session->SendPkg(&msg, sizeof(msg));
}

void MailMgr::GetMailAttachmentAck(Session* session, Player* player, ProtoCS_GetMailAttachmentAck& msg)
{
	auto fun = [&]()
	{
		if (!session) return;
		// 重新领取,将状态置为item_state_unaccalimed
		msg.err_type = 1;
		session->SendPkg(&msg, sizeof(msg));

		if (!player) return;
		ProtoMS_MailAttachmentGetAck ack;
		ack.mail_id = msg.mail_guid;
		ack.index = msg.index;
		ack.errcode = ERR_BAG_SPACE_NOT_ENOUGH;
		ack.sessid = player->GetClSessionID();

		SendDataBySessionID(player->GetGsSessionID(), ack);
		return;
	};
	if (!player) return fun();
	auto rolePack = player->GetRolePack();
	if (!rolePack) return fun();

	auto& MailVector = player->GetMailInfo();
	auto site = rolePack->GetIdleBagSite();
	if (site == INVALID_ITEM_SITE) return fun();

	std::string desc = "邮件领取-";
	auto it = find_if(MailVector.begin(), MailVector.end(), [&msg](MAIL_INFO& a) {return msg.mail_guid == a.mail_id; });
	if (it != MailVector.end())
	{
		desc += std::to_string(it->type);
		it->status &= ~(0x0001 << (msg.index));
	}

	msg.item.base_info.site = site;
	rolePack->AddItem(msg.item, log_params{ desc });
}

int MailMgr::FillCurrencyInfo(int type, int64_t value, MAIL_INFO& infos)
{
	if (value != 0) {
		switch (type)
		{
		case role_ingot:
			infos.status |= mail_status_yuanbao;
			break;
		case role_bind_ingot:
			infos.status |= mail_status_bind_yuanbao;
			break;
		case role_integral:
			infos.status |= mail_status_integral;
			break;
		case role_gold:
			infos.status |= mail_status_gold;
			break;
		case role_bind_gold:
			infos.status |= mail_status_bind_gold;
			break;
		default:
			return ERR_MAIL_ADD_CURRENCY_TYPE;
		}
	}
	if (infos.currency_type_num >= MAX_MAIL_CURRENCY_TYPE_NUM)return ERR_MAIL_ADD_CURRENCY_TYPE_NUM;
	infos.mail_currency_info[infos.currency_type_num].type = type;
	infos.mail_currency_info[infos.currency_type_num].num = value;
	++infos.currency_type_num;

	return ERR_OK;
}

int MailMgr::FillAddtionsInfo(const std::string& name, uint64_t guid, int num, int bind, MAIL_INFO& infos)
{
	auto pItemCfg = sItemConfig.GetByKeyName(name);
	if (!pItemCfg) return ERR_MAIL_ADD_NON_ITERMNAME;

	if (num > pItemCfg->Stack) return ERR_MAIL_ADD_NUM_MORE_THAN_STACK;

	if (infos.addition_item_num >= MAX_MAIL_CURRENCY_TYPE_NUM)return ERR_MAIL_ADDTION_ITEM_NUM;
	infos.status |= (mail_status_item1 << (infos.addition_item_num));
	infos.mail_addition_item_info[infos.addition_item_num].item_id = pItemCfg->Id;
	strcpy_s(infos.mail_addition_item_info[infos.addition_item_num].item_name, 
		sizeof(infos.mail_addition_item_info[infos.addition_item_num].item_name), name.c_str());
	infos.mail_addition_item_info[infos.addition_item_num].item_guid = guid;
	infos.mail_addition_item_info[infos.addition_item_num].count = num;
	infos.mail_addition_item_info[infos.addition_item_num].bind_status = bind;
	++infos.addition_item_num;
	return ERR_OK;
}

int32_t MailMgr::AddMailSys2Player(ProtoMS_AddSysNewMail& data)
{
	data.infos.send_timesmap = time(nullptr);
	auto ret = SendDataBySessionType(SESSION_TYPE_MS2CS, data);
	if (!ret)return ERR_MAIL_ADD_FAILED;
	return ERR_OK;
};

int MailMgr::ParseParamsByLua(const std::string& Rolename, uint64_t Guid, uint16_t addType, const std::string& title, const std::string& text, const CLuaObject& additions, const CLuaObject& currency, uint8_t type, ProtoMS_AddSysNewMail& data)
{
	strcpy_s(data.rolename, sizeof(data.rolename), Rolename);
	strcpy_s(data.infos.title, sizeof(data.infos.title), title);
	strcpy_s(data.infos.text, sizeof(data.infos.text), text);
	data.infos.status |= mail_status_unread;
	data.guid[0] = Guid;
	data.num = 1;
	data.addType = addType;
	data.infos.type = type;
	for (luabind::iterator it(currency), end; it != end; ++it)
	{
		if (luabind::type(*it) != LUA_TSTRING) return ERR_MAIL_ADD_CURRENCY_TYPE;
		auto currencyNumStr = luabind::object_cast<std::string>(*it);
		if (luabind::type(it.key()) != LUA_TSTRING) return ERR_MAIL_ADD_CURRENCY_TYPE;
		auto currencyTypeStr = luabind::object_cast<std::string>(it.key());
		int64_t currencyNum = 0;
		int currencyType = 0;
		try {
			currencyNum = std::stoll(currencyNumStr);
			currencyType = std::stoi(currencyTypeStr);
		}
		catch (...) { return ERR_MAIL_ADD_CURRENCY_TYPE; }

		auto err = MailMgr::FillCurrencyInfo(currencyType, currencyNum, data.infos);
		if(err != ERR_OK) return err;
	}

	for (luabind::iterator it(additions), end; it != end; ++it) {
		auto obj = *it;
		const auto& itemKeyName = obj[1];
		if (luabind::type(itemKeyName) != LUA_TSTRING) return ERR_MAIL_ADD_ITEMNAME_STYLE;
		auto sItemKeyName = luabind::object_cast<std::string>(itemKeyName);

		const auto& itemNum = obj[2];
		if (luabind::type(itemNum) != LUA_TNUMBER) return ERR_MAIL_ADD_ITEMNUM_STYLE;
		auto Num = luabind::object_cast<int32_t>(itemNum);

		const auto& bind = obj[3];
		if (luabind::type(bind) != LUA_TNUMBER) return ERR_MAIL_ADD_ITEMBIND_STYLLE;
		auto Bind = luabind::object_cast<int32_t>(bind);

		int err =  FillAddtionsInfo(sItemKeyName, 0, Num, Bind, data.infos);
		if (err != ERR_OK)return err;
	}
	return ERR_OK;
};

int MailMgr::ParseParamsByGM(const char* params, ProtoMS_AddSysNewMail& data)
{
	Json::Value root;
	Json::Reader reader;

	if (!reader.parse(params, params + strlen(params), root)) {
		LOG_ERROR("parse AddMail failed. param: %s", params);
		return ERR_EXEGMCMDFAIL;
	}
		
	if (!root["name"].isNull() && root["name"].isString()) {
		strcpy_s(data.rolename, sizeof(data.rolename), root["name"].asCString());
		data.addType = ProtoMS_AddSysNewMail::add_type_by_name;
	}

	if (!root["guid"].isNull() && root["guid"].isString()) {
		auto strGuid = root["guid"].asCString();

		auto guidList = str_split(strGuid, "|");
		try {
			for (auto i : guidList) {
				data.guid[data.num++] = std::stoull(i);
			}
			data.addType = ProtoMS_AddSysNewMail::add_type_by_guid;
		}
		catch (...) {
			return ERR_EXEGMCMDFAIL;
		};
	}
	data.infos.status += mail_status_unread;
	if (data.addType == ProtoMS_AddSysNewMail::add_type_non){
		return ERR_EXEGMCMDFAIL;
	}

	if (!root["title"].isNull() && root["title"].isString()) {
		strcpy_s(data.infos.title, sizeof(data.infos.title), root["title"].asCString());
	}

	if (!root["content"].isNull() && root["content"].isString()) {
		strcpy_s(data.infos.text, sizeof(data.infos.text), root["content"].asCString());
	}

	if (!root["addtions"].isNull() && root["addtions"].isString()) {
		std::string addtions = root["addtions"].asCString();
		auto addtionsInfos = str_split(addtions, ";");
		if(addtionsInfos.size()>MAX_ADDITION_NUM) return ERR_EXEGMCMDFAIL;
		for (int i = 0; i < addtionsInfos.size(); ++i)
		{
			auto infos = str_split(addtionsInfos[i], ":");
			if (infos.size() != 3) {
				return ERR_EXEGMCMDFAIL;
			}
			try {
				int err = FillAddtionsInfo(infos[0], 0, std::stoll(infos[1]), std::stoll(infos[2]), data.infos);
				if (err != ERR_OK)return err;
			}
			catch (...) {
				return ERR_EXEGMCMDFAIL;
			}
		}
	}

	if (!root["currencys"].isNull() && root["currencys"].isString()) {
		std::string currencys = root["currencys"].asCString();
		auto currencysInfos = str_split(currencys, ";");
		for (int i = 0; i < currencysInfos.size(); ++i)
		{
			auto infos = str_split(currencysInfos[i], ":");
			if (infos.size() != 2) {
				return ERR_EXEGMCMDFAIL;
			}
			try {
				int err = FillCurrencyInfo(std::stoll(infos[0]), std::stoll(infos[1]),data.infos);
				if (err != ERR_OK)return err;
			}
			catch (...) {
				return ERR_EXEGMCMDFAIL;
			}
		}
	}

	if (!root["type"].isNull() && root["type"].isString()) {
		auto type = root["type"].asCString();
		data.infos.type = atoi(type);
	}
	return ERR_OK;
};

int32_t MailMgr::GetMailAttachment(Player* player, uint64_t mailid, const ADDITION_ITEM_INFO& itemInfo, uint16_t idx)
{
	if (!player) return ERR_MAIL_NO_PLAYER;
	auto rolePack = player->GetRolePack();
	if (!rolePack) return ERR_MAIL_NO_PLAYER;

	if (rolePack->GetIdleBagSite() == INVALID_ITEM_SITE) return ERR_BAG_SPACE_NOT_ENOUGH;

	ProtoMS_GetMailAttachmentReq data;
	data.role_guid = player->GetGUID();
	data.mail_guid = mailid;
	data.item_guid = itemInfo.item_guid;
	data.index = idx;
	SendDataBySessionType(SESSION_TYPE_MS2CS, data);
	return ERR_OK;
}
