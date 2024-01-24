#pragma once 



#include "CNetManager.h"
#include "ProtoCS.h"
#include "ProtoMS.h"
#include "SessionFactory.h"
enum {
	expriation_time = 2592000      //邮件过期时间 30天
};
class mail
{
	DECL_SINGLETON(mail);
private:
	mail() {};
	~mail() {};
public:
	void InitMail_table();
	int GetMailCount(uint64_t playerguid);
	void AddMail(uint8_t num,const MAIL_INFO* data);
	void AddMailToDB(uint64_t guid, const string& name, const MAIL_INFO& data, uint32_t token);
	void DeleteMail(uint64_t playerguid, uint64_t mailid);
	void DeleteMailInfoByRoleGUID(uint64_t playerguid);
	void GetMailInfo(uint64_t playerguid, vector<MAIL_INFO>& data);
	static bool FillCurrencyInfo(uint8_t type, int64_t value, MAIL_INFO& infos);
private:
	//vector<mail_info>v_mail_info;
	std::map<uint64_t, vector<MAIL_INFO>>mail_map;
};