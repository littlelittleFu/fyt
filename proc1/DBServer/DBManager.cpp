#include "stdafx.h"
#include "DBManager.h"
#include "IFileHelper.h"


#define MYSQL_FIELD_GUID				"guid"
#define MYSQL_FIELD_USER_NAME           "user_name"
#define MYSQL_FIELD_PASS_WORD           "pass_word"


CDBManager* CDBManager::s_Instance = NULL;

CDBManager* CDBManager::GetInstance()
{
	if (s_Instance == NULL) {
		s_Instance = new CDBManager;
	}

	return s_Instance;
}

CDBManager::CDBManager()
{

}

CDBManager::~CDBManager()
{

}

bool CDBManager::Init()
{
	ConfigInfo* pConfig = ConfigInfo::GetInstance();
	LOG_NORMAL("connect mysql ! %s,%s", pConfig->m_sMySQLServAddr.c_str(), pConfig->m_sMySQLServUserName.c_str());
	if (!m_DBConnector.ConnDb(pConfig->m_sMySQLServAddr.c_str(), pConfig->m_sMySQLServUserName.c_str(),
		pConfig->m_sMySQLServPassword.c_str(), pConfig->m_sMySQLServDBName.c_str(), pConfig->m_nMySQLServPort)) {
		LOG_ERROR("connect mysql failed!");
		return false;
	}

	return true;
}

int CDBManager::CheckAccount(const char* pUserName, const char* pPassword, uint64_t& playerid,uint8_t isThirdLogin, int64_t& isProhibitChat, uint8_t& isSupport)
{
    SAFE_BEGIN_EX;
    if (!isThirdLogin)
    {
        if (!pUserName || !pPassword || !pPassword[0]) return DBERR_PARAM;
    }
    else
    {
        if (!pUserName) return DBERR_PARAM;
    }

    const auto &globalDB = ConfigInfo::GetInstance()->m_sMySQLGlobalServDBName;

	char sql[256] = { 0 };
	FMT2BUF(sql, "select id, password, is_lock, is_prohibit_chat, is_support from {}.player where name = '{}'", globalDB, ESCA2UTF8(pUserName));

	if (!ExecuteSQL(sql)) return DBERR_EXESQL;

	int result = m_DBConnector.GetQueryRowNum();
	if (result == 0) return DBERR_EMPTY;

	m_DBConnector.GetQueryFieldData("id", playerid);

	std::string sPassword;
	m_DBConnector.GetQueryFieldData("password", sPassword);

    if (!isThirdLogin)
    {
        if (strcmp(pPassword, sPassword.c_str())) return DBERR_NOTMATCH;
    }
    uint8_t is_lock = 0;
    m_DBConnector.GetQueryFieldData("is_lock", is_lock);
    m_DBConnector.GetQueryFieldData("is_prohibit_chat", isProhibitChat);
    m_DBConnector.GetQueryFieldData("is_support", isSupport);
    
    if (is_lock)return ERR_FORBIDLOGIN_ACCOUNT;  // 判断是否封禁账号

	return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::InsertPlayer(uint64_t playerid, const char *username)
{
    SAFE_BEGIN_EX;

    if (!username) return DBERR_PARAM;

    const auto &globalDB = ConfigInfo::GetInstance()->m_sMySQLGlobalServDBName;

    char sql[256] = { 0 };
    FMT2BUF(sql, "select name from {}.player where id = {}", globalDB, playerid);
    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    auto num = m_DBConnector.GetQueryRowNum();
    if (num == 0) {
        FMT2BUF(sql, "insert into {}.player (id, name) values ({}, '{}')", globalDB, playerid, ESCA2UTF8(username));
        if (!ExecuteSQL(sql)) return DBERR_EXESQL;
    }
    else {
        std::string storedName;
        m_DBConnector.GetQueryFieldData("name", storedName);
        if (storedName != username) {
            FMT2BUF(sql, "update {}.player set name = '{}' where id = {}", globalDB, ESCA2UTF8(username), playerid);
            if (!ExecuteSQL(sql)) return DBERR_EXESQL;
        }
    }

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetLoginIpInfo(std::vector<LOGIN_IP_DATA>& vec)
{
    SAFE_BEGIN_EX;
    char sql[256] = { 0 };
    FMT2BUF(sql, "select ip,type from login_ip");

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    int num = m_DBConnector.GetQueryRowNum();

    for (auto i = 0; i < num; ++i) {

        LOGIN_IP_DATA info;
        try {
            m_DBConnector.GetQueryFieldData("ip", info.ip);
            m_DBConnector.GetQueryFieldData("type", info.type);
      
            vec.push_back(info);
        }
        catch (...) {
            LOG_ERROR("Exception occurred");
        }

        m_DBConnector.QueryNext();
    }
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetTopList(uint64_t* rolelist,TOPLIST_INFO* topList, uint8_t &topListNum, uint8_t type)
{
    SAFE_BEGIN_EX;

    // 获取所有玩家等级前100数据
    // 获取每个职业前100一定获取了总体前100，其他同理
    char sql[256] = { 0 };
    int num;

    switch (type){
    case 0: //查询等级榜
    case 1:
    case 2:
    case 3:
        if(0!=type) {
            FMT2BUF(sql, "select id,name, level, job, gender from role "
                    "where job = {} and status = {} order by level desc limit 100",
                    type, static_cast<int>(role_status_normal));
        }
        else {
            FMT2BUF(sql, "select id,name, level, job, gender from role "
                    "where status = {} order by level desc limit 100",
                    static_cast<int>(role_status_normal));
        }
        if (!ExecuteSQL(sql)) return DBERR_EXESQL;

        num = m_DBConnector.GetQueryRowNum();
        for (auto i = topListNum; i < topListNum + num; i++) {
            m_DBConnector.GetQueryFieldData("id", rolelist[i]);
            m_DBConnector.GetQueryFieldData("name", (topList + i)->player_name, _countof((topList + i)->player_name));
            m_DBConnector.GetQueryFieldData("level", (topList + i)->level);
            m_DBConnector.GetQueryFieldData("job", (topList + i)->job);
            m_DBConnector.GetQueryFieldData("gender", (topList + i)->gender);

            m_DBConnector.QueryNext();
        }
        topListNum += num;
        break;
    default:
        break;
    }
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetRoleBriefInfo(const uint64_t& nPlayerID, std::vector<ROLE_BRIEF_INFO>& vRoleBriefInfo, uint64_t& nLastSelectedRole)
{
    SAFE_BEGIN_EX;

    char sql[256] = { 0 };
	char sql1[256] = { 0 };
	FMT2BUF(sql1, "select id, name, head, level, vipLevel, status, job, hair, hair_color, gender, "
            "weapon, clothes, is_lock, update_time from role where pid = {} and (status = {} or status = {})",
            nPlayerID, static_cast<int>(role_status_new), static_cast<int>(role_status_normal));
    char sql2[256] = { 0 };
    FMT2BUF(sql2, "select id, name, head, level, vipLevel, status, job, hair, hair_color, gender, "
        "weapon, clothes, is_lock, update_time from role where pid = {} and (status = {} or status = {})",
            nPlayerID, static_cast<int>(role_status_deleted), static_cast<int>(role_status_new_deleted));
    char* sqlArr[2] = { sql1 , sql2 };
    vRoleBriefInfo.clear();

for (int i = 0;i < 2;++ i)
{
	if (!ExecuteSQL(sqlArr[i])) return DBERR_EXESQL;

	auto num = m_DBConnector.GetQueryRowNum();

	for (auto i = 0; i < num; ++i) {

        ROLE_BRIEF_INFO info;
        memset(&info, 0, sizeof(info));

        try {
            m_DBConnector.GetQueryFieldData("id", info.guid);
            m_DBConnector.GetQueryFieldData("name", info.name, _countof(info.name));
            m_DBConnector.GetQueryFieldData("head", info.head);
            m_DBConnector.GetQueryFieldData("level", info.level);
            m_DBConnector.GetQueryFieldData("vipLevel", info.vipLevel);
            m_DBConnector.GetQueryFieldData("status", info.status);
            m_DBConnector.GetQueryFieldData("job", info.job);
            m_DBConnector.GetQueryFieldData("hair", info.hair);
            m_DBConnector.GetQueryFieldData("hair_color", info.hair_color);
            m_DBConnector.GetQueryFieldData("gender", info.gender);
            m_DBConnector.GetQueryFieldData("weapon", info.weapon);
            m_DBConnector.GetQueryFieldData("clothes", info.clothes);
            m_DBConnector.GetQueryFieldData("is_lock", info.is_lock);
            m_DBConnector.GetQueryFieldData("update_time", info.updateTime);

            vRoleBriefInfo.push_back(info);
        }
        catch (...) {
            LOG_ERROR("Exception occurred");
        }

		m_DBConnector.QueryNext();
	}
}
    ////////////////////////////////////////////////////////////////////////////////

    const auto &globalDB = ConfigInfo::GetInstance()->m_sMySQLGlobalServDBName;

    FMT2BUF(sql, "select last_role from {}.player where id = {}", globalDB, nPlayerID);

    if (ExecuteSQL(sql) && m_DBConnector.GetQueryRowNum() == 1) {

        m_DBConnector.GetQueryFieldData("last_role", nLastSelectedRole);
    }

	return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetOneRoleBriefInfo(const uint64_t& nRoleID, ROLE_BRIEF_INFO& info)
{
    SAFE_BEGIN_EX;

    char sql[256] = { 0 };
    FMT2BUF(sql, "select id, name, head, level, vipLevel, status, job, hair, hair_color, gender, "
        "weapon, clothes, is_lock, update_time from role where id = {};", nRoleID);

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    auto num = m_DBConnector.GetQueryRowNum();
    if (!num) return DBERR_EMPTY;

    try {
        m_DBConnector.GetQueryFieldData("id", info.guid);
        m_DBConnector.GetQueryFieldData("name", info.name, _countof(info.name));
        m_DBConnector.GetQueryFieldData("head", info.head);
        m_DBConnector.GetQueryFieldData("level", info.level);
        m_DBConnector.GetQueryFieldData("vipLevel", info.vipLevel);
        m_DBConnector.GetQueryFieldData("status", info.status);
        m_DBConnector.GetQueryFieldData("job", info.job);
        m_DBConnector.GetQueryFieldData("hair", info.hair);
        m_DBConnector.GetQueryFieldData("hair_color", info.hair_color);
        m_DBConnector.GetQueryFieldData("gender", info.gender);
        m_DBConnector.GetQueryFieldData("weapon", info.weapon);
        m_DBConnector.GetQueryFieldData("clothes", info.clothes);
        m_DBConnector.GetQueryFieldData("is_lock", info.is_lock);
        m_DBConnector.GetQueryFieldData("update_time", info.updateTime);
    }
    catch (...) {
        LOG_ERROR("Exception occurred");
    }

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetItemInfo(const uint64_t& nguid, std::list<ITEM_DB_INFO>& vitemInfo, uint8_t state, std::string tableName)
{
    SAFE_BEGIN_EX;

	char sql[256] = { 0 };
	FMT2BUF(sql, "select * from {} where role = {} and state = {}", ESCA2UTF8(tableName.c_str()), nguid, state);// (0:玩家身上(背包\仓库) 1.上架(出售)中 2.未领取(邮件))

	if (!ExecuteSQL(sql)) return DBERR_EXESQL;

	int nRowNum = m_DBConnector.GetQueryRowNum();

	ITEM_DB_INFO itemDBInfo;
	for (int i = 0; i < nRowNum; ++i) {

        try {
            m_DBConnector.GetQueryFieldData("guid", itemDBInfo.guid);
            m_DBConnector.GetQueryFieldData("id", itemDBInfo.id);
            m_DBConnector.GetQueryFieldData("name", itemDBInfo.name, _countof(itemDBInfo.name));
            m_DBConnector.GetQueryFieldData("role", itemDBInfo.role);
            m_DBConnector.GetQueryFieldData("site", itemDBInfo.site);
            m_DBConnector.GetQueryFieldData("amount", itemDBInfo.amount);
            m_DBConnector.GetQueryFieldData("durability", itemDBInfo.durability);
            m_DBConnector.GetQueryFieldData("max_durability", itemDBInfo.max_durability);
            m_DBConnector.GetQueryFieldData("use_count", itemDBInfo.use_count);
            m_DBConnector.GetQueryFieldData("is_bound", itemDBInfo.is_bound);
            m_DBConnector.GetQueryFieldData("life", itemDBInfo.life);
            std::string cfg = "";
            m_DBConnector.GetQueryFieldData("cfg", cfg);
            JsonStyleDecode(cfg, itemDBInfo.item_cfg_var);
            itemDBInfo.ext_len = 0;
            memset(itemDBInfo.ext_data, 0, sizeof(itemDBInfo.ext_data));
            vitemInfo.push_back(itemDBInfo);
        }
        catch (...) {
            LOG_ERROR("Exception occurred");
        }
		m_DBConnector.QueryNext();
	}
	return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetItemInfoByItemGuid(uint64_t nguid, uint64_t itemGuid, ITEM_DB_INFO& vitemInfo, uint8_t state, std::string tableName)
{
    SAFE_BEGIN_EX;

    char sql[256] = { 0 };
    FMT2BUF(sql, "select * from {} where role = {} and state = {} and guid = {}", ESCA2UTF8(tableName.c_str()), nguid, state, itemGuid);// (0:玩家身上(背包\仓库) 1.上架(出售)中 2.未领取(邮件))

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    if (m_DBConnector.GetQueryRowNum()) {
        try {
            m_DBConnector.GetQueryFieldData("guid", vitemInfo.guid);
            m_DBConnector.GetQueryFieldData("id", vitemInfo.id);
            m_DBConnector.GetQueryFieldData("name", vitemInfo.name, _countof(vitemInfo.name));
            m_DBConnector.GetQueryFieldData("role", vitemInfo.role);
            m_DBConnector.GetQueryFieldData("site", vitemInfo.site);
            m_DBConnector.GetQueryFieldData("amount", vitemInfo.amount);
            m_DBConnector.GetQueryFieldData("durability", vitemInfo.durability);
            m_DBConnector.GetQueryFieldData("max_durability", vitemInfo.max_durability);
            m_DBConnector.GetQueryFieldData("use_count", vitemInfo.use_count);
            m_DBConnector.GetQueryFieldData("is_bound", vitemInfo.is_bound);
            m_DBConnector.GetQueryFieldData("life", vitemInfo.life);
            std::string cfg = "";
            m_DBConnector.GetQueryFieldData("cfg", cfg);
            JsonStyleDecode(cfg, vitemInfo.item_cfg_var);
            vitemInfo.ext_len = 0;
            memset(vitemInfo.ext_data, 0, sizeof(vitemInfo.ext_data));
        }
        catch (...) {
            LOG_ERROR("Exception occurred");
        }
        m_DBConnector.QueryNext();
    }

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::DeleteItemInfo(const uint64_t& roleguid, const uint64_t& guid)
{
    SAFE_BEGIN_EX;

	char sql[256] = { 0 };
	FMT2BUF(sql,
		"DELETE FROM item  WHERE guid={} AND role={} AND state = {};", roleguid, guid, (uint32_t)item_state_owner);// owner
	if (!ExecuteSQL(sql))
		return DBERR_EXESQL;
	return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}


int CDBManager::InsertItemInfo(const uint64_t& nguid, const ITEM_DB_INFO& Info, uint8_t state)
{
    SAFE_BEGIN_EX;
    auto cfg = JsonStyleEncode(Info.item_cfg_var);

	char sql[512] = { 0 };
	FMT2BUF(sql,
		"INSERT INTO item (guid, id, name, role,site,amount,durability, max_durability, use_count, is_bound, life, state , cfg) \
        VALUES({}, {}, '{}', {}, {}, {}, {}, {}, {}, {}, {} ,{}, '{}')",
		Info.guid, Info.id, ESCA2UTF8(Info.name), Info.role, Info.site, Info.amount, Info.durability,
		Info.max_durability, Info.use_count, Info.is_bound, Info.life, state, ESCA2UTF8(cfg.c_str()));
	if (!ExecuteSQL(sql))
		return DBERR_EXESQL;
	return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::InsertItemExtraData(const ITEM_INFO& itemInfo)
{
    SAFE_BEGIN_EX;
    ITEM_INFO item = itemInfo;
    CUST_VAR_LIST custVarsList;
    DYN_ATTRS dynAttrsList;
    item.custom >> custVarsList;
    item.custom >> dynAttrsList;
    // 自定义
    CUST_VAR_SP_LIST add;
    for (auto& var : custVarsList)
    {
        var.belong = itemInfo.base_info.guid;
        add.emplace_back(std::move(std::make_shared<CUST_VAR>(var)));
    }
    SyncItemCustVar(&add, nullptr, nullptr);
    // 动态数据
    if (!dynAttrsList.empty()) {
        ITEM_DYN_ATTRS_LIST attrsList;
        attrsList.emplace_back(itemInfo.base_info.guid, std::move(dynAttrsList));
        UpdateItemDynAttrs(attrsList);
    }

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

//gbk_to_utf8
int CDBManager::UpdateItemInfo(const uint64_t& nguid, const ITEM_DB_INFO& Info)
{
    SAFE_BEGIN_EX;
    auto cfg = JsonStyleEncode(Info.item_cfg_var);

	char sql[512] = { 0 };
	FMT2BUF(sql,
		"UPDATE item SET id = {},name='{}', site={}, amount={}, durability={}, max_durability={}, use_count={}, is_bound={}, life={}, cfg = '{}'\
        WHERE  guid = {} AND role = {};",
		Info.id, ESCA2UTF8(Info.name), Info.site, Info.amount, Info.durability,
		Info.max_durability, Info.use_count, Info.is_bound, Info.life, ESCA2UTF8(cfg.c_str()),Info.guid, Info.role);

	if (!ExecuteSQL(sql))
		return DBERR_EXESQL;
	return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetItemDynAttrsList(const uint64_t &roleid, ITEM_DYN_ATTRS_LIST &attrsList, uint8_t state, std::string tableName, std::string tName)
{
    SAFE_BEGIN_EX;

    char sql[200] = {0};
    FMT2BUF(sql,
        "select * from {} where item in (select guid from {} where role = {} and state = {}) order by item", ESCA2UTF8(tableName.c_str()), ESCA2UTF8(tName.c_str()), roleid, state);

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    auto num = m_DBConnector.GetQueryRowNum();
    uint64_t itemGUID, prevItemGUID = 0;
    DYN_ATTR dynAttr;
    ITEM_DYN_ATTRS itemDynAttrs;

    for (auto i = 0; i < num; ++i) {
        m_DBConnector.GetQueryFieldData("item", itemGUID);
        m_DBConnector.GetQueryFieldData("idx", dynAttr.index);
        m_DBConnector.GetQueryFieldData("attr", dynAttr.attr);
        m_DBConnector.GetQueryFieldData("value", dynAttr.value);

        if (itemGUID != prevItemGUID) {

            if (prevItemGUID != 0) {
                attrsList.emplace_back(std::move(itemDynAttrs));
            }

            itemDynAttrs.guid = itemGUID;
            itemDynAttrs.dyn_attrs.clear();

            prevItemGUID = itemGUID;
        }

        itemDynAttrs.dyn_attrs.emplace_back(dynAttr);

        m_DBConnector.QueryNext();
    }

    if (!itemDynAttrs.dyn_attrs.empty())
        attrsList.emplace_back(std::move(itemDynAttrs));

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetItemDynAttrs(const uint64_t itemGUID, DYN_ATTRS &attrs, uint8_t state,
                                const char *attrTable, const char *itemTable)
{
    SAFE_BEGIN_EX;

    char sql[200] = { 0 };
    FMT2BUF(sql, "select t.* from {} as t join {} as i on t.item = i.guid "
            "where guid = {} and state = {}", attrTable, itemTable, itemGUID, state);

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    auto num = m_DBConnector.GetQueryRowNum();
    DYN_ATTR dynAttr;

    for (auto i = 0; i < num; ++i) {
        m_DBConnector.GetQueryFieldData("idx", dynAttr.index);
        m_DBConnector.GetQueryFieldData("attr", dynAttr.attr);
        m_DBConnector.GetQueryFieldData("value", dynAttr.value);
        attrs.emplace_back(std::move(dynAttr));
        m_DBConnector.QueryNext();
    }

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::UpdateItemDynAttrs(const ITEM_DYN_ATTRS_LIST &attrsList)
{
    SAFE_BEGIN_EX;

    if (attrsList.empty()) return DBERR_OK;

    std::string sql = "insert ignore into item_dyn_attr (item, idx, attr, value) values ";
    char buff[100] = {0};

    for (const auto &dynAttrs : attrsList) {

        for (const auto &dynAttr : dynAttrs.dyn_attrs) {

            FMT2BUF(buff, "({}, {}, {}, {}), ",
                dynAttrs.guid, dynAttr.index, dynAttr.attr, dynAttr.value);

            sql += buff;
        }
    }

    if (!buff[0]) return DBERR_OK;

    sql.erase(sql.size() - 2);
    
    sql += " on duplicate key update attr = values(attr), value = values(value)";

    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}


int CDBManager::GetRoleDynAttrsList(const uint64_t& roleid, ROLE_DYN_ATTRS_LIST& attrsList)
{
    SAFE_BEGIN_EX;

    char sql[300] = { 0 };
    FMT2BUF(sql,
        "select * from role_dyn_attr where role = {}", roleid);

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    auto num = m_DBConnector.GetQueryRowNum();
    uint64_t roleGUID = 0;
    DYN_ATTR dynAttr;
    ROLE_DYN_ATTRS roleDynAttrs;
    roleDynAttrs.guid = roleid;
    for (auto i = 0; i < num; ++i) {
        m_DBConnector.GetQueryFieldData("role", roleGUID);
        m_DBConnector.GetQueryFieldData("idx", dynAttr.index);
        m_DBConnector.GetQueryFieldData("attr", dynAttr.attr);
        m_DBConnector.GetQueryFieldData("value", dynAttr.value);
        roleDynAttrs.dyn_attrs.emplace_back(dynAttr);

        m_DBConnector.QueryNext();
    }

    if (!roleDynAttrs.dyn_attrs.empty())
        attrsList.emplace_back(std::move(roleDynAttrs));

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::UpdateRoleDynAttrs(const ROLE_DYN_ATTRS_LIST& attrsList)
{
    SAFE_BEGIN_EX;

    if (attrsList.empty()) return DBERR_OK;

    std::string sql = "insert ignore into role_dyn_attr (role, idx, attr, value) values ";
    char buff[100] = { 0 };

    for (const auto& dynAttrs : attrsList) {

        for (const auto& dynAttr : dynAttrs.dyn_attrs) {

            FMT2BUF(buff, "({}, {}, {}, {}), ",
                dynAttrs.guid, dynAttr.index, dynAttr.attr, dynAttr.value);

            sql += buff;
        }
    }

    sql.erase(sql.size() - 2);
    sql += " on duplicate key update attr = values(attr), value = values(value)";

    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::UpdateOnlineState(const uint64_t &roleGUID, const uint8_t &state)
{
    SAFE_BEGIN_EX;
    char sql[256] = { 0 };
    FMT2BUF(sql, "update role set online_state = {}, online_duration = online_duration + (UNIX_TIMESTAMP() - update_time), update_time = UNIX_TIMESTAMP() where id = {}", state, roleGUID);
    if (!ExecuteSQL(sql)) return DBERR_EXESQL;
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::UpdateLastSelectedRole(const uint64_t &nPlayerID, const uint64_t& nRoleID)
{
    SAFE_BEGIN_EX;

    const auto &globalDB = ConfigInfo::GetInstance()->m_sMySQLGlobalServDBName;

	char sql[256] = { 0 };
	FMT2BUF(sql, "update {}.player set last_role = {}, last_login_time = UNIX_TIMESTAMP() where id = {}", globalDB, nRoleID, nPlayerID);

	if (!ExecuteSQL(sql)) return DBERR_EXESQL;
	return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::CreateRole(const uint64_t& nPlayerID, const ROLE_BRIEF_INFO& roleBriefInfo)
{
    SAFE_BEGIN_EX;
    std::string sqlStr("");
	char sql[1024] = { 0 };
    std::string createDate = ITimeHelper::GetInstance()->ConvertTimeToString(GUID_TIME_PART(roleBriefInfo.guid), DTFMTA3);
	FMT2BUF(sql, "insert into role (agent_area_server_id, id, pid, name, head, level, vipLevel ,status, job, hair, hair_color, "
		"gender, weapon, clothes ,is_lock, create_date, update_time) values ('{}', {}, {}, '{}', {}, {}, {}, {}, {}, {}, {}, {}, {}, {},{},'{}', UNIX_TIMESTAMP());",
        ConfigInfo::GetInstance()->m_sAgentAreaServerIdStr, roleBriefInfo.guid, nPlayerID, ESCA2UTF8(roleBriefInfo.name),
		roleBriefInfo.head, roleBriefInfo.level, roleBriefInfo.vipLevel, roleBriefInfo.status, roleBriefInfo.job,
		roleBriefInfo.hair, roleBriefInfo.hair_color, roleBriefInfo.gender, roleBriefInfo.weapon,
		roleBriefInfo.clothes, roleBriefInfo.is_lock, ESCA2UTF8(std::move(createDate)));
    sqlStr += sql; memset(sql, 0, sizeof(sql));
    FMT2BUF(sql, "insert into {}.unique_name(id, name) (select id, name from role where id = {}) on duplicate key update name = values(name);", ConfigInfo::GetInstance()->m_sMySQLGlobalServDBName.c_str(), roleBriefInfo.guid);
    sqlStr += sql; memset(sql, 0, sizeof(sql));

	if (!ExecuteSQL(sqlStr.c_str())) return DBERR_EXESQL;

	return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::DeleteRole(const uint64_t& nRoleID, int32_t& status)
{
    SAFE_BEGIN_EX;

	char sql[256] = { 0 };

	FMT2BUF(sql, "update role set status = {}, update_time = UNIX_TIMESTAMP() where id = {}",
        status, nRoleID);

	if (!ExecuteSQL(sql)) return DBERR_EXESQL;
	return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::RestoreRole(const uint64_t& nRoleID, int32_t& status)
{
    SAFE_BEGIN_EX;

    char sql[256] = { 0 };

    FMT2BUF(sql, "update role set status = {}, update_time = UNIX_TIMESTAMP() where id = {}",
        status, nRoleID);

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;
    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::CheckIfCreateRoleCode(uint8_t needCode, uint64_t digCode)
{
    SAFE_BEGIN_EX;
    // 不需要邀请码
    if (!needCode) return DBERR_OK;
    // 数字邀请码
    std::string sqlStr = "";
    char sql[256] = { 0 };
    if (1 == needCode)
    {
        FMT2BUF(sql, "select 1 from role_invite_code where code = {} and role = 0;", digCode);
        sqlStr += sql; memset(sql, 0, sizeof(sql));
    }

    if (!ExecuteSQL(sqlStr.c_str())) return DBERR_EXESQL;

    auto num = m_DBConnector.GetQueryRowNum();
    if (1 == num) return DBERR_OK;

    return DBERR_NOTMATCH;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::DeleteCreateRoleCode(uint8_t needCode, uint64_t digCode, uint64_t role)
{
    SAFE_BEGIN_EX;
    // 不需要邀请码
    if (!needCode) return DBERR_OK;
    // 数字邀请码
    std::string sqlStr = "";
    char sql[256] = { 0 };
    if (1 == needCode)
    {
        FMT2BUF(sql, "update role_invite_code set role = {} where code = {};", role, digCode);
        sqlStr += sql; memset(sql, 0, sizeof(sql));
    }

    if (!ExecuteSQL(sqlStr.c_str())) return DBERR_EXESQL;

    auto num = m_DBConnector.GetQueryRowNum();
    if (1 == num) return DBERR_OK;

    return DBERR_NOTMATCH;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::CheckIfRoleExistByName(const char *name, uint8_t &exist, uint64_t &guid, bool includingDeleted)
{
    SAFE_BEGIN_EX;

    if (!name || !name[0]) return DBERR_PARAM;

    char sql[256] = {0};

    if (includingDeleted) {
        FMT2BUF(sql, "select id from {}.unique_name where name = '{}';", ConfigInfo::GetInstance()->m_sMySQLGlobalServDBName.c_str(), ESCA2UTF8(name));
    }
    else {
        FMT2BUF(sql, "select id from role where name = '{}' and (status = {} or status = {})",
                ESCA2UTF8(name), static_cast<int>(role_status_new), static_cast<int>(role_status_normal));
    }

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    auto num = m_DBConnector.GetQueryRowNum();
    if (num > 0) {
        exist = 1;
        m_DBConnector.GetQueryFieldData("id", guid);
    }
    else {
        exist = 0;
    }

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::CheckIfRoleExistByGUID(uint64_t guid, uint8_t &exist, char *name, uint32_t bufsize)
{
    SAFE_BEGIN_EX;

    char sql[100] = {0};
    FMT2BUF(sql, "select name from role where id = {} and (status = {} or status = {})",
            guid, static_cast<int>(role_status_new), static_cast<int>(role_status_normal));

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    auto num = m_DBConnector.GetQueryRowNum();
    if (num > 0) {
        exist = 1;
        m_DBConnector.GetQueryFieldData("name", name, bufsize);
    }
    else {
        exist = 0;
    }

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetSkillInfo(const uint64_t& nRoleID, SKILL_INFO* pSkillInfo, uint16_t& num)
{
    SAFE_BEGIN_EX;

	char sql[256] = { 0 };
	FMT2BUF(sql, "select skill, active, proficiency, cfg from role_skill where role = {} limit {}", nRoleID, num);

	if (!ExecuteSQL(sql)) return DBERR_EXESQL;

	num = (uint16_t)m_DBConnector.GetQueryRowNum();

	for (uint16_t i = 0; i < num; ++i) {
		m_DBConnector.GetQueryFieldData("skill", pSkillInfo[i].id);
        m_DBConnector.GetQueryFieldData("active", pSkillInfo[i].active);
        m_DBConnector.GetQueryFieldData("proficiency", pSkillInfo[i].proficiency);
        m_DBConnector.GetQueryFieldData("cfg", pSkillInfo[i].cfg, _countof(pSkillInfo[i].cfg));
		m_DBConnector.QueryNext();
	}

	return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SyncSkillInfo(const uint64_t &nRoleID, const SKILL_INFO *pRemoveSkillInfo, uint16_t nRemoveSkillNum,
    const SKILL_INFO *pAddSkillInfo, uint16_t nAddSkillNum, const SKILL_INFO *pUpdateSkillInfo, uint16_t nUpdateSkillNum)
{
    SAFE_BEGIN_EX;

    std::string sql;
    char buff[1024] = { 0 };

    for (uint16_t i = 0; i < nRemoveSkillNum; ++i) {
        FMT2BUF(buff, "delete from role_skill where role = {} and skill = {};",
            nRoleID, pRemoveSkillInfo[i].id);
        sql += buff;
    }

    for (uint16_t i = 0; i < nAddSkillNum; ++i) {
        FMT2BUF(buff, "insert into role_skill (role, skill, active, proficiency, cfg) values ({}, {}, {}, {}, '{}');",
            nRoleID, pAddSkillInfo[i].id, pAddSkillInfo[i].active, pAddSkillInfo[i].proficiency, ESCA2UTF8(pAddSkillInfo[i].cfg));
        sql += buff;
    }

    for (uint16_t i = 0; i < nUpdateSkillNum; ++i) {
        FMT2BUF(buff, "update role_skill set active = {}, proficiency = {}, cfg = '{}' where role = {} and skill = {};",
            pUpdateSkillInfo[i].active, pUpdateSkillInfo[i].proficiency, ESCA2UTF8(pUpdateSkillInfo[i].cfg), nRoleID, pUpdateSkillInfo[i].id);
        sql += buff;
    }

    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetBuffInfo(const uint64_t& nRoleID, std::list<BUFF_INFO_DB>& li)
{
    SAFE_BEGIN_EX;

	char sql[256] = { 0 };
	FMT2BUF(sql,
		"select id, buff, stack, attr, timeleft, timestamp, actor_id, actor_name, actor_job, actor_level, actor_skill from role_buff where role = {} order by timestamp", nRoleID);

	if (!ExecuteSQL(sql)) return DBERR_EXESQL;

	uint16_t num = (uint16_t)m_DBConnector.GetQueryRowNum();
    uint16_t i = 0;

	for (uint16_t j = 0; j < num; ++j) {

        BUFF_INFO_DB pBuffInfo;
        try {
            m_DBConnector.GetQueryFieldData("id", pBuffInfo.index);
            m_DBConnector.GetQueryFieldData("buff", pBuffInfo.buffid);
            m_DBConnector.GetQueryFieldData("stack", pBuffInfo.stack);
            m_DBConnector.GetQueryFieldData("attr", pBuffInfo.attr, _countof(pBuffInfo.attr));
            m_DBConnector.GetQueryFieldData("timeleft", pBuffInfo.timeleft);
            m_DBConnector.GetQueryFieldData("timestamp", pBuffInfo.timestamp);
            m_DBConnector.GetQueryFieldData("actor_id", pBuffInfo.actor_id);
            m_DBConnector.GetQueryFieldData("actor_name", pBuffInfo.actor_name, _countof(pBuffInfo.actor_name));
            m_DBConnector.GetQueryFieldData("actor_job", pBuffInfo.actor_job);
            m_DBConnector.GetQueryFieldData("actor_level", pBuffInfo.actor_level);
            m_DBConnector.GetQueryFieldData("actor_skill", pBuffInfo.actor_skill);
            li.push_back(pBuffInfo);
            ++i;
        }
        catch (...) {
            LOG_ERROR("Exception occurred");
        }
		m_DBConnector.QueryNext();
	}

    num = i;

	return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SyncBuffInfo(const uint64_t &nRoleID, const uint64_t *pRemoveIndex, uint16_t nRemoveNum,
    const BUFF_INFO_DB *pAddBuffInfo, uint16_t nAddNum, const BUFF_INFO_DB *pUpdateBuffInfo, uint16_t nUpdateNum)
{
    SAFE_BEGIN_EX;

    std::string sql;
    char buff[1024] = { 0 };

    for (uint16_t i = 0; i < nRemoveNum; ++i) {
        FMT2BUF(buff, "delete from role_buff where id = {};", pRemoveIndex[i]);
        sql += buff;
    }

    for (uint16_t i = 0; i < nAddNum; ++i) {
        auto &info = pAddBuffInfo[i];
        FMT2BUF(buff, "insert into role_buff (id, role, buff, stack, attr, timeleft, timestamp, actor_id, actor_name, "
            "actor_job, actor_level, actor_skill) values ({}, {}, {}, {}, '{}', {}, {}, {}, '{}', {}, {}, {});",
            info.index, nRoleID, info.buffid, info.stack, ESCA2UTF8(info.attr), info.timeleft, info.timestamp, info.actor_id, ESCA2UTF8(info.actor_name), info.actor_job,
            info.actor_level, info.actor_skill);
        sql += buff;
    }

    for (uint16_t i = 0; i < nUpdateNum; ++i) {
        auto &info = pUpdateBuffInfo[i];
        FMT2BUF(buff, "update role_buff set stack = {}, timeleft = {}, timestamp = {}, actor_id = {}, "
            "actor_name = '{}', actor_job = {}, actor_level = {}, actor_skill = {} where id = {};",
            info.stack, info.timeleft, info.timestamp, info.actor_id, ESCA2UTF8(info.actor_name), info.actor_job, info.actor_level,
            info.actor_skill, info.index);
        sql += buff;
    }

    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

void SendDBSqlLog(const char* sql, bool success)
{
    if (success) return;
    //if (strncmp(sql, "select", 6) == 0) return;

    static uint64_t inc = 0;
    LOG_WARN("SQL LOG[%llu], result: %s, sql content: %s", inc++, success ? "success" : "failure", sql);
/*
    std::string s = "";
    LogDBSql log;
    log.beLastPack = 0;
    log.result = success ? 0 : 1;
    uint32_t len = strlen(sql);
    uint32_t size = _countof(log.dbSqlStr);
    for (uint32_t idx = 0; idx < len;)
    {
        uint32_t maxLen = len - idx;
        maxLen = maxLen < size ? maxLen : size - 1;

        strncpy_s(log.dbSqlStr, sql + idx, maxLen);
        idx += maxLen;
        
        if (idx >= len) log.beLastPack = 1;
        SendDBLogData(log_type_db_exesql, log);
        memset(log.dbSqlStr, 0, size);
    }
*/
}

bool CDBManager::ExecuteSQL(const char* sql)
{
    bool success = (m_DBConnector.ExecQuery(sql) == 0);
	if (!success) {
		LOG_ERROR("ExecQuery failed with error: %s\n", m_DBConnector.GetErrorStr());
	}
    SendDBSqlLog(sql, success);
    return success;
}

bool CDBManager::ExecuteSQL(const char* sql, uint64_t& rows)
{
    bool success = (m_DBConnector.ExecQuery(sql, rows) == 0);
	if (!success) {
		LOG_WARN("ExecQuery failed with error: %s\n", m_DBConnector.GetErrorStr());
	}
    SendDBSqlLog(sql, success);
    return success;
}

int CDBManager::UpdateRoleInfo(const uint64_t& nRoleID, const std::string &  info)
{
    SAFE_BEGIN_EX;

	char sql[256] = { 0 };

	char baseinfo[512] = "";
	GetRoleInfo(nRoleID, baseinfo, 512);
	string baseinfostr = baseinfo;
	if (string::npos != baseinfostr.find(info))
	{
		LOG_WARN("update same content!!!");
		return DBERR_OK;
	}

	std::vector<string>key_str;

	auto infos = str_split(info, ";");

	auto getpos = [](const std::string&ans,char delim=':') {
		return ans.find(delim);
	};
	for (auto& str : infos)
	{
		if (getpos(str) == std::string::npos) continue;
		auto substrs = str.substr(0,getpos(str));

		auto basepos1 = baseinfostr.find(substrs);
		if (basepos1 == std::string::npos) continue;

		auto base1 = baseinfostr.substr(basepos1);
		auto basepos2 = base1.find(';');

		if (basepos2 == std::string::npos) continue;
		auto base2 = baseinfostr.substr(basepos1, basepos2);

		FMT2BUF(sql,
			"UPDATE `role_info` SET `env`=REPLACE(env, '{}', '{}') WHERE  `id`={};", base2.c_str(), str.c_str(), nRoleID);
		if (!ExecuteSQL(sql))
		{
			LOG_WARN("%s failed!!!",sql);
		}

	}

	return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}


int CDBManager::InsertRoleInfo(const uint64_t& nRoleID, const std::string & info)
{
    SAFE_BEGIN_EX;

	char sql[256] = { 0 };

	//全部相同，避免重复插入
	char baseinfo[512] = "";
	uint64_t rows = 0;
	auto ret = GetRoleInfo(nRoleID, baseinfo,512, rows);
	if (ret == 0 && rows == 0)
	{
		FMT2BUF(sql,
			"INSERT INTO `role_info` (`id`, `env`) VALUES({}, '{}');", nRoleID, info.c_str());
		if (!ExecuteSQL(sql)) return DBERR_EXESQL;

		return DBERR_OK;
	}
	string baseinfostr = baseinfo;
	if (baseinfostr.empty())
	{
		FMT2BUF(sql,
			"UPDATE ROLE_INFO SET env = CONCAT(env, '{}') WHERE id = {};", info.c_str(), nRoleID);
		if (!ExecuteSQL(sql)) return DBERR_EXESQL;
		return DBERR_OK;
	}

	if (string::npos != baseinfostr.find(info))
	{
		LOG_WARN("insert same content!!!");
		return DBERR_OK;
	}

	//部分相同或者全部不同，避免局部重复插入
	auto infos = str_split(info, ";");
	auto getpos = [](const std::string& ans, char delim = ':') {
		return ans.find(delim);
	};
	for (auto& str : infos)
	{
		auto substrs = str.substr(0, getpos(str));
		auto basepos1 = baseinfostr.find(substrs);
		if (basepos1 != std::string::npos)
		{
			continue;
		}
		//尾插不同部分
		FMT2BUF(sql,
				"UPDATE ROLE_INFO SET env = CONCAT(env,';', '{}') WHERE id = {};", str.c_str(), nRoleID);

		if (!ExecuteSQL(sql, rows))
		{
			LOG_WARN("%s %d failed!!!", sql,rows);
		}
	}
	return DBERR_OK;
	
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetRoleInfo(const uint64_t& nRoleID, char* info, uint32_t buffSize)
{
    SAFE_BEGIN_EX;

	char sql[256] = { 0 };
	FMT2BUF(sql,
		"SELECT `id`, CAST(`env` AS CHAR) FROM `role_info` WHERE  `id`={} ;", nRoleID);
	if (!ExecuteSQL(sql)) return DBERR_EXESQL;
	m_DBConnector.GetQueryFieldData("CAST(`env` AS CHAR)", info, buffSize);
	//LOG_WARN("############:%s",info);
	return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetRoleInfo(const uint64_t& nRoleID, char* info, uint32_t buffSize, uint64_t& rows)
{
	SAFE_BEGIN_EX;

	char sql[256] = { 0 };
	FMT2BUF(sql,
		"SELECT `id`, CAST(`env` AS CHAR) FROM `role_info` WHERE  `id`={} ;", nRoleID);
	if (!ExecuteSQL(sql,rows)) return DBERR_EXESQL;
	m_DBConnector.GetQueryFieldData("CAST(`env` AS CHAR)", info, buffSize);
	//LOG_WARN("############:%s", info);
	return DBERR_OK;

	SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::ClearRoleInfo(const uint64_t& nRoleID)
{
	SAFE_BEGIN_EX;

	char sql[256] = { 0 };
	FMT2BUF(sql,
		"DELETE FROM `role_info` WHERE `id`={} ;", nRoleID);
	if (!ExecuteSQL(sql)) return DBERR_EXESQL;
	return DBERR_OK;

	SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::DeleteRoleInfo(const uint64_t& nRoleID, const std::string& info)
{
    SAFE_BEGIN_EX;

	char baseinfo[512] = "";
	GetRoleInfo(nRoleID, baseinfo, 512);
	string baseinfostr = baseinfo;
	if (baseinfostr.empty())
	{
		LOG_WARN("RoleInfo null!!!");
		return DBERR_OK;
	}
	auto it = baseinfostr.find(info);
	if (string::npos == it)
	{
		LOG_WARN("DeleteRoleInfo null!!!");
		return DBERR_OK;
	}
	auto& infos = (it + info.length() < baseinfostr.length() && baseinfostr.at(it + info.length()) == ';')?
		baseinfostr.erase(it, info.length() + 1): baseinfostr.erase(it, info.length());
	if (!infos.empty() && infos[infos.length() - 1] == ';') infos.erase(infos.begin()+ infos.length() - 1);
	char sql[256] = { 0 };
	FMT2BUF(sql,
		"UPDATE `role_info` SET `env`='{}' WHERE `id`={} ;",infos.c_str(), nRoleID);
	if (!ExecuteSQL(sql)) return DBERR_EXESQL;
	return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::CheckRoleAccount(const uint64_t& nRoleID, const uint64_t& playerid)
{
    SAFE_BEGIN_EX;
    char sql[500] = { 0 };
    FMT2BUF(sql,
        "select pid from role "
        "where id = {}", nRoleID);
    if (!ExecuteSQL(sql)) return DBERR_EXESQL;
    int nRowNum = m_DBConnector.GetQueryRowNum();
    if (nRowNum != 1) return DBERR_ROWNUM;
    uint64_t pid = 0;
    m_DBConnector.GetQueryFieldData("pid", pid);
    if(pid == playerid)
        return DBERR_OK;
    return DBERR_ROWNUM;
    SAFE_END_EX(DBERR_EXCEPT);
}


int CDBManager::GetRoleExtraInfo(const uint64_t &nRoleID, ROLE_EXTRA_INFO &roleExtraInfo, ROLE_SETTINGS &roleSettings)
{
    SAFE_BEGIN_EX;

    char sql[500] = { 0 };
    FMT2BUF(sql,
        "select hp, mp, exp, gold, bind_gold, ingot, bind_ingot, integral, deposit_gold, inner_force_exp, atk_mode,role_pk,"	
        "map, posx, posy, dir, birth_map, rebirth_map, redname_map, modelID, auto_pickup "
        "from role left join role_location as loc on id = loc.role left join role_settings as s on id = s.role "
        "where id = {}", nRoleID);

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    int nRowNum = m_DBConnector.GetQueryRowNum();
    if (nRowNum != 1) return DBERR_ROWNUM;

    m_DBConnector.GetQueryFieldData("hp", roleExtraInfo.hp);
    m_DBConnector.GetQueryFieldData("mp", roleExtraInfo.mp);
    m_DBConnector.GetQueryFieldData("exp", roleExtraInfo.exp);
	m_DBConnector.GetQueryFieldData("gold", roleExtraInfo.gold);
	m_DBConnector.GetQueryFieldData("bind_gold", roleExtraInfo.bindGold);
	m_DBConnector.GetQueryFieldData("ingot", roleExtraInfo.ingot);
	m_DBConnector.GetQueryFieldData("bind_ingot", roleExtraInfo.bindIngot);
	m_DBConnector.GetQueryFieldData("integral", roleExtraInfo.integral);
	m_DBConnector.GetQueryFieldData("deposit_gold", roleExtraInfo.depositGold);
	m_DBConnector.GetQueryFieldData("inner_force_exp", roleExtraInfo.innerForceExp);
    m_DBConnector.GetQueryFieldData("atk_mode", roleExtraInfo.atkMode);
    m_DBConnector.GetQueryFieldData("role_pk", roleExtraInfo.rolePk);
    m_DBConnector.GetQueryFieldData("map", roleExtraInfo.mapid);
    m_DBConnector.GetQueryFieldData("posx", roleExtraInfo.posx);
    m_DBConnector.GetQueryFieldData("posy", roleExtraInfo.posy);
    m_DBConnector.GetQueryFieldData("dir", roleExtraInfo.dir);
    m_DBConnector.GetQueryFieldData("birth_map", roleExtraInfo.birthMap);
    m_DBConnector.GetQueryFieldData("rebirth_map", roleExtraInfo.rebirthMap);
    m_DBConnector.GetQueryFieldData("redname_map", roleExtraInfo.redNameMap);
    m_DBConnector.GetQueryFieldData("modelID", roleExtraInfo.modelID);

    std::vector<uint8_t> autoPickupData;
    m_DBConnector.GetQueryFieldData("auto_pickup", autoPickupData);

    if (!autoPickupData.empty()) {

        const auto *pAutoPickItem = flatbuffers::GetRoot<AutoPickItem>(autoPickupData.data());
        flatbuffers::Verifier verifier(autoPickupData.data(), autoPickupData.size());

        if (pAutoPickItem->Verify(verifier)) {

            auto &autoPickupSettings = roleSettings.auto_pickup;
            autoPickupSettings.mode = pAutoPickItem->mode();
            autoPickupSettings.interval = pAutoPickItem->interval();

            if (autoPickupSettings.mode == auto_pick_item_mode_around) {
                autoPickupSettings.radius = pAutoPickItem->radius();
            }
            else if (autoPickupSettings.mode == auto_pick_item_mode_designated) {
                const auto *pRelPosAry = pAutoPickItem->relpos();
                autoPickupSettings.numpos = pRelPosAry->size();

                for (int i = 0; i < autoPickupSettings.numpos; ++i) {

                    auto &relpos = autoPickupSettings.relpos[i];
                    const auto *pRelPos = pRelPosAry->Get(i);

                    relpos.x = pRelPos->x();
                    relpos.y = pRelPos->y();
                }
            }
        }
    }

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SyncRoleInfo(const ROLE_BRIEF_INFO &brief, const ROLE_EXTRA_INFO &extra, const ROLE_SETTINGS &settings)
{
    SAFE_BEGIN_EX;

    char sql[1024] = { 0 };
    FMT2BUF(sql,
        "update role set head = {}, level = {}, vipLevel = {}, status = {}, hair = {}, hair_color = {}, weapon = {}, clothes = {}, is_lock = {},"
        "login_time = {}, hp = {}, mp = {}, exp = {}, gold = {}, bind_gold = {}, "
		"ingot = {}, bind_Ingot = {}, integral = {}, deposit_gold = {}, inner_force_exp = {}, "
        "atk_mode = {}, role_pk = {} ,modelID = {}, online_duration = online_duration + (UNIX_TIMESTAMP() - update_time), update_time = UNIX_TIMESTAMP() "
        "where id = {}",		brief.head, brief.level, brief.vipLevel, brief.status, brief.hair, brief.hair_color, brief.weapon, brief.clothes,brief.is_lock,
        extra.login_time, extra.hp, extra.mp, extra.exp, extra.gold, extra.bindGold,
		extra.ingot, extra.bindIngot, extra.integral, extra.depositGold, extra.innerForceExp,
		extra.atkMode,extra.rolePk, extra.modelID,
        brief.guid);

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    //////////////////////////////////////////////////////////////////////////////

    FMT2BUF(sql,
        "insert into role_location (role, map, posx, posy, dir, birth_map, rebirth_map, redname_map) "
        "values ({}, {}, {}, {}, {}, {}, {}, {}) "
        "on duplicate key update map = values(map), posx = values(posx), posy = values(posy), dir = values(dir), "
        "birth_map = values(birth_map), rebirth_map = values(rebirth_map), redname_map = values(redname_map)",
        brief.guid, extra.mapid, extra.posx, extra.posy, extra.dir,
        extra.birthMap, extra.rebirthMap, extra.redNameMap);

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    //////////////////////////////////////////////////////////////////////////////

    std::vector<Position> relpos;
    const auto &autoPickupSettings = settings.auto_pickup;

    for (int i = 0; i < autoPickupSettings.numpos; ++i) {
        const auto &pos = autoPickupSettings.relpos[i];
        relpos.emplace_back(pos.x, pos.y);
    }

    flatbuffers::FlatBufferBuilder builder;
    auto offset = CreateAutoPickItemDirect(builder, autoPickupSettings.mode, autoPickupSettings.radius, &relpos,
        autoPickupSettings.interval);
    builder.Finish(offset);

    auto *buf = builder.GetBufferPointer();
    auto bufsz = builder.GetSize();
    auto autoPickupData = hex2str(buf, bufsz);

    FMT2BUF(sql,
        "insert into role_settings (role, auto_pickup) values ({}, 0x{}) "
        "on duplicate key update auto_pickup = values(auto_pickup)",
        brief.guid, autoPickupData);

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SyncRoleInfo(const ProtoCS_SyncRoleInfo* info)
{
    SAFE_BEGIN_EX;

    std::string name_head = "head";
    std::string name_level = "level";
    std::string name_status = "status";
    std::string name_job = "job";
    std::string name_hair = "hair";
    std::string name_hair_color = "hair_color";
    std::string name_gender = "gender";
    std::string name_weapon = "weapon";
    std::string name_clothes = "clothes";
    std::string name_gssvrid = "gssvrid";
    std::string name_vipLevel = "vipLevel";
    std::string name_is_lock = "is_lock";

    std::string name_login_time = "login_time";
    std::string name_hp = "hp";
    std::string name_mp = "mp";
    std::string name_exp = "exp";
    std::string name_mapid = "map";
    std::string name_posx = "posx";
    std::string name_posy = "posy";
    std::string name_dir = "dir";
    std::string name_gold = "gold";
    std::string name_bindGold = "bind_gold";
    std::string name_ingot = "ingot";
    std::string name_bindIngot = "bind_ingot";
    std::string name_integral = "integral";
    std::string name_depositGold = "deposit_gold";
    std::string name_innerForceExp = "inner_force_exp";
    std::string name_atkMode = "atk_mode";
    std::string name_birthMap = "birth_map";
    std::string name_rebirthMap = "rebirth_map";
    std::string name_redNameMap = "redname_map";
    std::string name_rolePk = "role_pk";
    std::string name_modelID = "modelID";

    std::string sql = "update role set ";
    char mysql[256] = { 0 };

    uint8_t roleInfoFlag = 0;
    uint8_t roleLocationFlag = 0;

#define StartGenerate if(0){}
#define GenerateBriefInfo(member)\
    else if (info->briefInfoKey[i] == role_brief_info_flag::flag_brief_##member) {\
    roleInfoFlag = 1;\
    memset(mysql,0,_countof(mysql));\
    FMT2BUF(mysql, " {} = {},", name_##member.c_str(),info->briefInfoVal[i]);\
    sql += mysql;\
    }
#define GenerateExtraInfo(member)\
    else if (info->extraInfoKey[i] == role_extra_info_flag::flag_extra_##member) {\
    roleInfoFlag = 1;\
    memset(mysql,0,_countof(mysql));\
    FMT2BUF(mysql, " {} = {},", name_##member.c_str(),info->extraInfoVal[i]);\
    sql += mysql;\
    }
#define EndRoleInfoGenerate \
    memset(mysql,0,sizeof(mysql));\
    FMT2BUF(mysql, " online_duration = online_duration + (UNIX_TIMESTAMP() - update_time), "\
                  "update_time = UNIX_TIMESTAMP() where id = {} ", info->guid);\
    sql += mysql;

#define EndRoleLocationGenerate \
    keys.erase(--keys.end());\
    values.erase(--values.end());\
    names.erase(--names.end());\
    keys += values;\
    keys += names;


#define GenerateLocationInfo(member)\
    else if (info->extraInfoKey[i] == role_extra_info_flag::flag_extra_##member) {\
        roleLocationFlag = 1;\
        memset(mysql, 0, _countof(mysql)); \
        FMT2BUF(mysql, " {},", name_##member.c_str()); \
        keys += mysql;\
        memset(mysql, 0, _countof(mysql)); \
        FMT2BUF(mysql," {},", info->extraInfoVal[i]); \
        values += mysql; \
        memset(mysql, 0, _countof(mysql)); \
        FMT2BUF(mysql, "{} = values({}),", name_##member.c_str(), name_##member.c_str()); \
        names += mysql; \
    }

    std::string keys = "insert into role_location (role ,";
    memset(mysql, 0, sizeof(mysql));
    FMT2BUF(mysql, ") values({},", info->guid);
    std::string values = mysql;
    std::string names = ")on duplicate key update ";

    for (int i = 0; i < info->briefInfoNum; ++i) {
        StartGenerate
        GenerateBriefInfo(head)
        GenerateBriefInfo(level)
        GenerateBriefInfo(status)
        GenerateBriefInfo(job)
        GenerateBriefInfo(hair)
        GenerateBriefInfo(hair_color)
        GenerateBriefInfo(gender)
        GenerateBriefInfo(weapon)
        GenerateBriefInfo(clothes)
        GenerateBriefInfo(gssvrid)
        GenerateBriefInfo(vipLevel)
        GenerateBriefInfo(is_lock)
    }


    for (int i = 0; i < info->extraInfoNum; ++i) {
        StartGenerate
        GenerateExtraInfo(login_time)
        GenerateExtraInfo(hp)
        GenerateExtraInfo(mp)
        GenerateExtraInfo(exp)
        GenerateExtraInfo(gold)
        GenerateExtraInfo(bindGold)
        GenerateExtraInfo(ingot)
        GenerateExtraInfo(bindIngot)
        GenerateExtraInfo(integral)
        GenerateExtraInfo(depositGold)
        GenerateExtraInfo(innerForceExp)
        GenerateExtraInfo(atkMode)
        GenerateExtraInfo(rolePk)
        GenerateExtraInfo(modelID)

        GenerateLocationInfo(mapid)
        GenerateLocationInfo(posx)
        GenerateLocationInfo(posy)
        GenerateLocationInfo(dir)
        GenerateLocationInfo(birthMap)
        GenerateLocationInfo(rebirthMap)
        GenerateLocationInfo(redNameMap)
    }

    EndRoleInfoGenerate
    EndRoleLocationGenerate

    if (roleInfoFlag) {
        if (!ExecuteSQL(sql.c_str())) {
            LOG_ERROR("sync role info:%s", sql.c_str());
            return DBERR_EXESQL;
        }
    }

    if (roleLocationFlag) {
        if (!ExecuteSQL(keys.c_str())) {
            LOG_ERROR("sync role info:%s", keys.c_str());
            return DBERR_EXESQL;
        }
    }

    if (info->setFlag) {
        char setSql[1024] = { 0 };
        std::vector<Position> relpos;
        const auto& autoPickupSettings = info->roleset.auto_pickup;

        for (int i = 0; i < autoPickupSettings.numpos; ++i) {
            const auto& pos = autoPickupSettings.relpos[i];
            relpos.emplace_back(pos.x, pos.y);
        }

        flatbuffers::FlatBufferBuilder builder;
        auto offset = CreateAutoPickItemDirect(builder, autoPickupSettings.mode, autoPickupSettings.radius, &relpos,
            autoPickupSettings.interval);
        builder.Finish(offset);

        auto* buf = builder.GetBufferPointer();
        auto bufsz = builder.GetSize();
        auto autoPickupData = hex2str(buf, bufsz);

        FMT2BUF(setSql,
            "insert into role_settings (role, auto_pickup) values ({}, 0x{}) "
            "on duplicate key update auto_pickup = values(auto_pickup)",
            info->guid, autoPickupData);

        if (!ExecuteSQL(setSql)){
            LOG_ERROR("sync role info:%s", setSql);
            return DBERR_EXESQL;
        }
    }

    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetQuestInfo(const uint64_t &nRoleID, QUEST_INFO &questInfo)
{
    SAFE_BEGIN_EX;

    char sql[256] = {0};
    FMT2BUF(sql, "select * from quest_info where role = {}", nRoleID);
    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    int nRowNum = m_DBConnector.GetQueryRowNum();
    if (nRowNum == 0) return DBERR_EMPTY;
    else if (nRowNum != 1) return DBERR_ROWNUM;

    m_DBConnector.GetQueryFieldData("pre_quest", questInfo.pre_quest);
    m_DBConnector.GetQueryFieldData("cur_quest", questInfo.cur_quest);
    m_DBConnector.GetQueryFieldData("timeleft", questInfo.timeleft);
    m_DBConnector.GetQueryFieldData("timestamp", questInfo.timestamp);

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetQuestAchieve(const uint64_t &nRoleID, QUEST_ACHIEVE *pQuestAchieve, uint8_t &num)
{
    SAFE_BEGIN_EX;

    char sql[256] = {0};
    FMT2BUF(sql,
        "select quest, achev_type, achev_id, achev_num from quest_achieve where role = {}", nRoleID);

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    num = (uint8_t)std::min<uint8_t>((uint8_t)m_DBConnector.GetQueryRowNum(), num);

    for (uint8_t i = 0; i < num; ++i) {
        m_DBConnector.GetQueryFieldData("quest", pQuestAchieve[i].quest);
        m_DBConnector.GetQueryFieldData("achev_type", pQuestAchieve[i].achev_type);
        m_DBConnector.GetQueryFieldData("achev_id", pQuestAchieve[i].achev_id);
        m_DBConnector.GetQueryFieldData("achev_num", pQuestAchieve[i].achev_num);
        m_DBConnector.QueryNext();
    }

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SyncQuestInfo(const uint64_t &nRoleID, const QUEST_INFO &questInfo,
    const QUEST_ACHIEVE *pRemoveAchevs, uint8_t nRemoveNum, const QUEST_ACHIEVE *pAddAchevs, uint8_t nAddNum,
    const QUEST_ACHIEVE *pUpdateAchevs, uint8_t nUpdateNum)
{
    SAFE_BEGIN_EX;

    std::string sql;
    char buff[1024] = { 0 };

    FMT2BUF(buff,
        "insert into quest_info (role, pre_quest, cur_quest, timeleft, timestamp) values ({}, {}, {}, {}, {}) "
        "on duplicate key update pre_quest = values(pre_quest), cur_quest = values(cur_quest), timeleft = values(timeleft), "
        "timestamp = values(timestamp);",
        nRoleID, questInfo.pre_quest, questInfo.cur_quest, questInfo.timeleft, questInfo.timestamp);
    sql += buff;

    for (uint8_t i = 0; i < nRemoveNum; ++i) {
        auto &achev = pRemoveAchevs[i];
        FMT2BUF(buff, "delete from quest_achieve where role = {} and quest = {} "
            "and achev_type = {} and achev_id = {};", nRoleID, achev.quest, achev.achev_type, achev.achev_id);
        sql += buff;
    }

    for (uint8_t i = 0; i < nAddNum; ++i) {
        auto &achev = pAddAchevs[i];
        FMT2BUF(buff, "insert into quest_achieve (role, quest, achev_type, achev_id, achev_num) "
            "values ({}, {}, {}, {}, {});", nRoleID, achev.quest, achev.achev_type, achev.achev_id, achev.achev_num);
        sql += buff;
    }

    for (uint8_t i = 0; i < nUpdateNum; ++i) {
        auto &achev = pUpdateAchevs[i];
        FMT2BUF(buff, "update quest_achieve set achev_num = {} "
            "where role = {} and quest = {} and achev_type = {} and achev_id = {};",
            achev.achev_num, nRoleID, achev.quest, achev.achev_type, achev.achev_id);
        sql += buff;
    }

    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

void CDBManager::GetTradeRecords(uint32_t tradeRecordsExpireTime, std::list<TRADE_RECORD>& recordsList)
{
    SAFE_BEGIN;

    recordsList.clear();
    uint64_t curTimestampSeconds = (uint64_t)MS2S(TimeHelper::GetInstance()->GetTimeStamp());
    std::string curTime = "";
    std::string tableName = "";
    char sql[1024] = { 0 };

    //for (uint16_t i = 0; i <= 3; ++i)
    {
        //curTimestampSeconds -= i * 2592000;
        //curTime = ITimeHelper::GetInstance()->ConvertTimeToString(curTimestampSeconds, DTFMTA3);
        //tableName = std::string(TRADE_DATA_TEMPLATE_TABLE_NAME) + curTime.substr(0, 6);
        tableName = std::string(TRADE_DATA_LOG_TEMPLATE_TABLE_NAME);
        memset(sql, 0, sizeof(sql));
        FMT2BUF(sql, "select *, UNIX_TIMESTAMP(time) as timestamp from {}.{} where UNIX_TIMESTAMP(NOW()) - UNIX_TIMESTAMP(time) < {} order by time desc;", 
            ConfigInfo::GetInstance()->m_sMySQLServDBName.c_str(), ESCA2UTF8(tableName), tradeRecordsExpireTime);
        if (ExecuteSQL(sql))
        {
            auto num = m_DBConnector.GetQueryRowNum();
            TRADE_RECORD td;
            for (uint16_t i = 0; i < num; ++i)
            {
                m_DBConnector.GetQueryFieldData("trade_id", td.logTradeData.tradeId);
                m_DBConnector.GetQueryFieldData("trade_type", td.logTradeData.tradeType);
                m_DBConnector.GetQueryFieldData("value_type", td.logTradeData.valueType);
                m_DBConnector.GetQueryFieldData("item_guid", td.logTradeData.itemGuid);
                m_DBConnector.GetQueryFieldData("item_id", td.logTradeData.itemId);
                m_DBConnector.GetQueryFieldData("item_value", td.logTradeData.itemValue);
                m_DBConnector.GetQueryFieldData("item_num", td.logTradeData.itemNum);
                m_DBConnector.GetQueryFieldData("buyer_guid", td.logTradeData.buyerGuid);
                m_DBConnector.GetQueryFieldData("seller_guid", td.logTradeData.sellerGuid);
                m_DBConnector.GetQueryFieldData("timestamp", td.logTradeData.timestamp);
                m_DBConnector.QueryNext();

                recordsList.push_back(td);
            }
        }
        memset(sql, 0, sizeof(sql));
    }

    // tableName = ConfigInfo::GetInstance()->m_sMySQLLogServDBName + '.' + TRADE_ITEM_TEMPLATE_TABLE_NAME;
    tableName = TRADE_ITEM_LOG_TEMPLATE_TABLE_NAME;
    auto iter = recordsList.begin();
    for (; iter != recordsList.end(); ++iter)
    {
        GetItemInfoByItemGuid(iter->logTradeData.buyerGuid, iter->logTradeData.itemGuid, iter->item.base_info, item_state_unaccalimed, tableName);
        GetTradeItemExtraData(iter->logTradeData.buyerGuid, iter->logTradeData.itemGuid, iter->item);
    }
    return;
    SAFE_END;
}

void CDBManager::GetTradeDelegate(SP_BUY_DELEGATE_MAP& buy, SP_SELL_DELEGATE_MAP& sell)
{
    SAFE_BEGIN;
    {
    string sql = "";
    char buf[1024] = { 0 };
    FMT2BUF(buf, "select m.*, r.name as rolename from trade_item as m inner join role as r on m.roleid = r.id where delegatetype = {} order by tradetime;", (uint32_t)delegate_type_buy);
    sql += buf;

    if (ExecuteSQL(sql.c_str()))
    {
    auto num = m_DBConnector.GetQueryRowNum();

    for (auto i = 0; i < num; ++i) {

        auto info = std::make_shared<DELEGATE_BUY_ITEM2>();

        m_DBConnector.GetQueryFieldData("tradeguid", info->id);
        m_DBConnector.GetQueryFieldData("tradetime", info->trade_time);
        m_DBConnector.GetQueryFieldData("roleid", info->buyer_guid);
        m_DBConnector.GetQueryFieldData("rolename", info->buyer, sizeof(info->buyer));
        m_DBConnector.GetQueryFieldData("itemid", info->item_template_id);
        m_DBConnector.GetQueryFieldData("num", info->item_num);
        m_DBConnector.GetQueryFieldData("price", info->item_value);
        m_DBConnector.GetQueryFieldData("currencytype", info->value_type);
        m_DBConnector.GetQueryFieldData("tdtime", info->td_time);
        m_DBConnector.QueryNext();

        buy.emplace(info->id, std::move(info));
    }
    }
    }
    {
    string sql = "";
    char buf[1024] = { 0 };
    FMT2BUF(buf, "select m.*, r.name as rolename, i.*"
        " from trade_item as m"
        " inner join role as r on m.roleid = r.id"
        " inner join item as i on m.itemguid = i.guid"
        " where delegatetype = {} order by tradetime;", (uint32_t)delegate_type_sell);
    sql += buf;

    if (ExecuteSQL(sql.c_str()))
    {
    auto num = m_DBConnector.GetQueryRowNum();

    for (auto i = 0; i < num; ++i) {

        auto info = std::make_shared<DELEGATE_SELL_ITEM>();

        m_DBConnector.GetQueryFieldData("tradeguid", info->id);
        m_DBConnector.GetQueryFieldData("tradetime", info->trade_time);
        m_DBConnector.GetQueryFieldData("rolename", info->seller, sizeof(info->seller));
        m_DBConnector.GetQueryFieldData("roleid", info->seller_guid);

            m_DBConnector.GetQueryFieldData("guid", info->item.base_info.guid);
            m_DBConnector.GetQueryFieldData("id", info->item.base_info.id);
            m_DBConnector.GetQueryFieldData("name", info->item.base_info.name, _countof(info->item.base_info.name));
            m_DBConnector.GetQueryFieldData("role", info->item.base_info.role);
            m_DBConnector.GetQueryFieldData("site", info->item.base_info.site);
            m_DBConnector.GetQueryFieldData("amount", info->item.base_info.amount);
            m_DBConnector.GetQueryFieldData("durability", info->item.base_info.durability);
            m_DBConnector.GetQueryFieldData("max_durability", info->item.base_info.max_durability);
            m_DBConnector.GetQueryFieldData("use_count", info->item.base_info.use_count);
            m_DBConnector.GetQueryFieldData("is_bound", info->item.base_info.is_bound);
            m_DBConnector.GetQueryFieldData("life", info->item.base_info.life);
            std::string cfg = "";
            m_DBConnector.GetQueryFieldData("cfg", cfg);
            JsonStyleDecode(cfg, info->item.base_info.item_cfg_var);

        m_DBConnector.GetQueryFieldData("price", info->item_value);
        m_DBConnector.GetQueryFieldData("currencytype", info->value_type);
        m_DBConnector.GetQueryFieldData("tdtime", info->td_time);
        m_DBConnector.QueryNext();

        sell.emplace(info->id, std::move(info));
    }
    auto iter = sell.begin();
    for (; iter != sell.end(); ++iter)
    {
        GetItemExtraData(iter->second->seller_guid, iter->second->item.base_info.guid, iter->second->item, item_state_selling);
    }
    }
    }

    return;

    SAFE_END;
}

int CDBManager::TradeRecordsCancel(uint16_t num, uint64_t* trade_id)
{
    SAFE_BEGIN_EX;
    if (!num) return DBERR_OK;

    string sql = "";
    char buf[4096] = { 0 };
    std::string tradeIdstr = "";
    for (uint16_t n = 0; n < num; ++n)
    {
        tradeIdstr += std::to_string(trade_id[n]) + ',';
    }
    if (!tradeIdstr.empty()) tradeIdstr.pop_back();
    tradeIdstr = '(' + tradeIdstr + ')';

    // std::string tableName = ConfigInfo::GetInstance()->m_sMySQLLogServDBName + '.' + TRADE_ITEM_TEMPLATE_TABLE_NAME;
    std::string tableName = TRADE_ITEM_LOG_TEMPLATE_TABLE_NAME;
    FMT2BUF(buf, "delete from {} where guid in {};", ESCA2UTF8(tableName.c_str()), tradeIdstr.c_str());
    sql += buf;
    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::TradeDelegateCancel(uint64_t tradeid, uint8_t delegatetype)
{
    SAFE_BEGIN_EX;
    string sql = "";
    char buf[1024] = { 0 };
    if (delegatetype == delegate_type_sell)
    {
        FMT2BUF(buf, "update item set state = {} where guid = (Select itemguid from trade_item where tradeguid = {});", (uint32_t)item_state_unaccalimed, tradeid);
        sql += buf;
        memset(buf, 0, sizeof(buf));
    }
    FMT2BUF(buf, "delete from trade_item where tradeguid = {};", tradeid);
    sql += buf;
    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::TradeDelegateBuy(const ProtoMS_DelegateBuyCmd& cmd)
{
    SAFE_BEGIN_EX;
    string sql = "";
    char buf[1024] = { 0 };
    FMT2BUF(buf, "insert into trade_item(tradeguid, tradetime, roleid, itemguid, itemid, num, price, currencytype, delegatetype, tdtime) values"
        "({}, {}, {}, {}, {}, {}, {}, {}, {}, {});", cmd.buyItem.id, (uint64_t)cmd.buyItem.trade_time, cmd.buyItem.buyer_guid, (uint64_t)0, (uint32_t)cmd.buyItem.item_template_id,
        cmd.buyItem.item_num, cmd.buyItem.item_value, (uint32_t)cmd.buyItem.value_type, (uint32_t)delegate_type_buy, (uint32_t)cmd.buyItem.td_time);
    sql += buf;
    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::TradeDelegateSell(const ProtoMS_DelegateSellCmd& cmd)
{
    SAFE_BEGIN_EX;
    string sql = "";
    char buf[1024] = { 0 };
    FMT2BUF(buf, "select 1 from item where guid = {} and state = {};", cmd.sellItem.item.base_info.guid, (uint32_t)item_state_owner);
    sql += buf;
    memset(buf, 0, sizeof(buf));
    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;
    int num = m_DBConnector.GetQueryRowNum();
    if (num == 0) { return DBERR_NOTMATCH; }

    sql = "";
    FMT2BUF(buf, "update item set state = {} where guid = {};", (uint32_t)item_state_selling, cmd.sellItem.item.base_info.guid);
    sql += buf;
    memset(buf, 0, sizeof(buf));
    FMT2BUF(buf, "insert into trade_item(tradeguid, tradetime, roleid, itemguid, itemid, num, price, currencytype, delegatetype, tdtime) values"
        "({}, {}, {}, {}, {}, {}, {}, {}, {}, {});", cmd.sellItem.id, (uint64_t)cmd.sellItem.trade_time, cmd.sellItem.seller_guid, cmd.sellItem.item.base_info.guid, (uint32_t)0,
        (uint32_t)0, cmd.sellItem.item_value, (uint32_t)cmd.sellItem.value_type, (uint32_t)delegate_type_sell, (uint32_t)cmd.sellItem.td_time);
    sql += buf;

    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::TradeMarketBuy(const ProtoCS_MarketBuyAck& req)
{
    SAFE_BEGIN_EX;
    string sql = "";
    char buf[1024] = { 0 };
    InsertItemInfo(req.item.base_info.role, req.item.base_info, item_state_unaccalimed);
    InsertItemExtraData(req.item);
    if (1 == req.remove)
    {
        FMT2BUF(buf, "delete from item where guid = (Select itemguid from trade_item where tradeguid = {});", req.trade_id);
        sql += buf; memset(buf, 0, sizeof(buf));
        FMT2BUF(buf, "delete from trade_item where tradeguid = {};", req.trade_id);
        sql += buf; memset(buf, 0, sizeof(buf));
    }
    else if (0 == req.remove)
    {
        FMT2BUF(buf, "update item set amount = amount - {} where guid = (Select itemguid from trade_item where tradeguid = {});", req.count, req.trade_id); 
        sql += buf; memset(buf, 0, sizeof(buf));
    }
    else
    {
        return DBERR_OK;
    }
    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
    return 0;
}

int CDBManager::TradeMarketSell(const ProtoCS_MarketSellAck& req)
{
    SAFE_BEGIN_EX;
    string sql = "";
    char buf[1024] = { 0 };
    InsertItemInfo(req.item.base_info.role, req.item.base_info, item_state_unaccalimed);
    InsertItemExtraData(req.item);
    if (1 == req.remove)
    {
        FMT2BUF(buf, "delete from trade_item where tradeguid = {};", req.trade_id);
        sql += buf; memset(buf, 0, sizeof(buf));
    }
    else if (0 == req.remove)
    {
        FMT2BUF(buf, "update trade_item set num = num - {} where tradeguid = {};", req.count, req.trade_id);
        sql += buf; memset(buf, 0, sizeof(buf));
    }
    else
    {
        return DBERR_OK;
    }
    // 卖家扣除走原来的代码逻辑
    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
    return 0;
}

int CDBManager::GetGuilds(GUILD_MAP &guilds)
{
    SAFE_BEGIN_EX;

    const char *sql = "select * from guild";

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    auto num = m_DBConnector.GetQueryRowNum();

    for (auto i = 0; i < num; ++i) {

        auto guild = std::make_shared<GUILD_INFO>();

        m_DBConnector.GetQueryFieldData("id", guild->id);
        m_DBConnector.GetQueryFieldData("name", guild->name);
        m_DBConnector.GetQueryFieldData("level", guild->level);
        m_DBConnector.GetQueryFieldData("manifesto", guild->manifesto);
        m_DBConnector.GetQueryFieldData("notice", guild->notice);
        m_DBConnector.GetQueryFieldData("ctime", guild->ctime);
        m_DBConnector.GetQueryFieldData("creator_id", guild->creator_id);
        m_DBConnector.GetQueryFieldData("creator_name", guild->creator_name);
        m_DBConnector.GetQueryFieldData("chairman_id", guild->chairman_id);
        m_DBConnector.GetQueryFieldData("chairman_name", guild->chairman_name);
        m_DBConnector.GetQueryFieldData("autojoin_level", guild->autojoin_level);
        m_DBConnector.QueryNext();

        guilds.emplace(guild->id, std::move(guild));
    }

    ////////////////////////////////////////////////////////////////////////////////

    sql = "select * from guild_relation";

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    num = m_DBConnector.GetQueryRowNum();

    for (auto i = 0; i < num; ++i) {

        uint64_t id = 0;
        m_DBConnector.GetQueryFieldData("id", id);

        auto it = guilds.find(id);
        if (it == guilds.end()) continue;

        auto &guild = *it->second;

        uint64_t peer = 0;
        m_DBConnector.GetQueryFieldData("peer", peer);

        it = guilds.find(peer);
        if (it == guilds.end()) continue;

        auto &peerGuild = *it->second;

        uint8_t relation = 0;
        m_DBConnector.GetQueryFieldData("relation", relation);

        if (relation == guild_relation_ally) {
            guild.allies.push_back(peer);
            peerGuild.allies.push_back(id);
        }
        else if (relation == guild_relation_enemy) {
            guild.enemies.push_back(peer);
            peerGuild.enemies.push_back(id);
        }

        m_DBConnector.QueryNext();
    }

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetGuildMembers(GUILD_MEMBER_MAP &members)
{
    SAFE_BEGIN_EX;

    const char *sql = "select m.*, r.name, r.level, r.job, r.login_time "
        "from guild_member as m inner join role as r on m.id = r.id";

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    auto num = m_DBConnector.GetQueryRowNum();

    for (auto i = 0; i < num; ++i) {

        auto member = std::make_shared<GUILD_MEMBER>();

        m_DBConnector.GetQueryFieldData("id", member->player_id);
        m_DBConnector.GetQueryFieldData("guild", member->guild_id);
        m_DBConnector.GetQueryFieldData("title", member->title);
        m_DBConnector.GetQueryFieldData("new_title", member->new_title);
        m_DBConnector.GetQueryFieldData("join_time", member->join_time);
        m_DBConnector.GetQueryFieldData("cur_contrib", member->cur_contrib);
        m_DBConnector.GetQueryFieldData("total_contrib", member->total_contrib);
        m_DBConnector.GetQueryFieldData("kills", member->kills);
        m_DBConnector.GetQueryFieldData("combat_cap", member->combat_cap);
        m_DBConnector.GetQueryFieldData("status", member->status);
        m_DBConnector.GetQueryFieldData("kicked_by", member->kicked_by);
        m_DBConnector.GetQueryFieldData("name", member->player_name);
        m_DBConnector.GetQueryFieldData("level", member->level);
        m_DBConnector.GetQueryFieldData("job", member->job);
        m_DBConnector.GetQueryFieldData("login_time", member->login_time);
        m_DBConnector.QueryNext();

        members.emplace(member->player_id, std::move(member));
    }

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetGuildApplicants(GUILD_APPLICANT_LIST &applicants)
{
    SAFE_BEGIN_EX;

    const char *sql = "select a.*, r.name, r.level, r.job, r.login_time "
        "from guild_apply as a inner join role as r on a.role = r.id";

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    auto num = m_DBConnector.GetQueryRowNum();

    for (auto i = 0; i < num; ++i) {

        auto applicant = std::make_shared<GUILD_APPLY_INFO>();

        m_DBConnector.GetQueryFieldData("role", applicant->player_id);
        m_DBConnector.GetQueryFieldData("guild", applicant->guild_id);
        m_DBConnector.GetQueryFieldData("apply_time", applicant->apply_time);
        m_DBConnector.GetQueryFieldData("status", applicant->status);
        m_DBConnector.GetQueryFieldData("handled_by", applicant->handled_by);
        m_DBConnector.GetQueryFieldData("name", applicant->player_name);
        m_DBConnector.GetQueryFieldData("level", applicant->level);
        m_DBConnector.GetQueryFieldData("job", applicant->job);
        m_DBConnector.GetQueryFieldData("login_time", applicant->login_time);
        m_DBConnector.QueryNext();

        applicants.emplace_back(std::move(applicant));
    }

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SyncGuildApplicant(const SPGUILD_APPLICANT &applyInfo, uint8_t type)
{
    SAFE_BEGIN_EX;

    char sql[1024] = {0};

    switch (type) {

    case db_op_type_add:        // 增
        FMT2BUF(sql,
            "insert into guild_apply (role, guild, apply_time, status, handled_by) values ({}, {}, {}, {}, '{}')",
            applyInfo->player_id, applyInfo->guild_id, applyInfo->apply_time, applyInfo->status, ESCA2UTF8(applyInfo->handled_by));
        break;

    case db_op_type_del:        // 删
        FMT2BUF(sql, "delete from guild_apply where role = {} and guild = {}",
            applyInfo->player_id, applyInfo->guild_id);
        break;

    case db_op_type_update:     // 改
        FMT2BUF(sql,
            "update guild_apply set apply_time = {}, status = {}, handled_by = '{}' where role = {} and guild = {}",
            applyInfo->apply_time, applyInfo->status, ESCA2UTF8(applyInfo->handled_by), applyInfo->player_id, applyInfo->guild_id);
        break;

    default:
        break;
    }

    return ExecuteSQL(sql) ? DBERR_OK : DBERR_EXESQL;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SyncGuildMember(const SPGUILD_MEMBER &member, uint8_t type)
{
    SAFE_BEGIN_EX;

    char sql[1024] = {0};

    switch (type) {

    case db_op_type_add:        // 增
        FMT2BUF(sql,
            "insert into guild_member (id, guild, title, new_title, join_time, cur_contrib, total_contrib, "
            "kills, combat_cap, status, kicked_by) "
            "values ({}, {}, {}, {}, {}, {}, {}, {}, {}, {}, '{}')",
            member->player_id, member->guild_id, member->title, member->new_title, member->join_time,
            member->cur_contrib, member->total_contrib, member->kills, member->combat_cap, member->status,
            ESCA2UTF8(member->kicked_by));
        break;

    case db_op_type_del:        // 删
        FMT2BUF(sql, "delete from guild_member where id = {} and guild = {}",
            member->player_id, member->guild_id);
        break;

    case db_op_type_update:     // 改
        FMT2BUF(sql,
            "update guild_member set title = {}, new_title = {}, cur_contrib = {}, total_contrib = {}, "
            "kills = {}, combat_cap = {}, status = {}, kicked_by = '{}' where id = {} and guild = {}",
            member->title, member->new_title, member->cur_contrib, member->total_contrib,
            member->kills, member->combat_cap, member->status, ESCA2UTF8(member->kicked_by),
            member->player_id, member->guild_id);
        break;

    default:
        break;
    }

    return ExecuteSQL(sql) ? DBERR_OK : DBERR_EXESQL;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SyncGuildInfo(const SPGUILD &guild, uint8_t type)
{
    SAFE_BEGIN_EX;

    char sql[2048] = {0};

    switch (type) {

    case db_op_type_add:        // 增
        FMT2BUF(sql,
            "insert into guild (id, name, level, manifesto, notice, ctime, creator_id, "
            "creator_name, chairman_id, chairman_name, autojoin_level) "
            "values ({}, '{}', {}, '{}', '{}', {}, {}, '{}', {}, '{}', {})",
            guild->id, ESCA2UTF8(guild->name), guild->level, ESCA2UTF8(guild->manifesto),
            ESCA2UTF8(guild->notice), guild->ctime, guild->creator_id, ESCA2UTF8(guild->creator_name),
            guild->chairman_id, ESCA2UTF8(guild->chairman_name), guild->autojoin_level);
        break;

    case db_op_type_del:        // 删
        FMT2BUF(sql, "delete from guild where id = {}", guild->id);
        break;

    case db_op_type_update:     // 改
        FMT2BUF(sql,
            "update guild set level = {}, manifesto = '{}', notice = '{}', chairman_id = {}, "
            "chairman_name = '{}', autojoin_level = {} where id = {}",
            guild->level, ESCA2UTF8(guild->manifesto), ESCA2UTF8(guild->notice), guild->chairman_id,
            ESCA2UTF8(guild->chairman_name), guild->autojoin_level, guild->id);
        break;

    default:
        break;
    }

    return ExecuteSQL(sql) ? DBERR_OK : DBERR_EXESQL;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SyncGuildRelation(uint8_t type, uint64_t myGUID, uint64_t peerGUID, uint8_t relation)
{
    SAFE_BEGIN_EX;

    char sql[200] = {0};

    switch (type) {

    case db_op_type_add:
        FMT2BUF(sql, "insert into guild_relation (id, peer, relation) values ({}, {}, {})",
            myGUID, peerGUID, relation);
        break;

    case db_op_type_del:
        FMT2BUF(sql, "delete from guild_relation where (id = {} and peer = {}) or (id = {} and peer = {})",
            myGUID, peerGUID, peerGUID, myGUID);
        break;

    default:
        break;
    }

    return ExecuteSQL(sql) ? DBERR_OK : DBERR_EXESQL;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SyncAuctionItemInfo(const ProtoMS_SynAuctionItemInfo& info)
{
    SAFE_BEGIN_EX;

    std::string sql;
    switch (info.type) {
    case ProtoMS_SynAuctionItemInfo::add:        // 增
        for (uint16_t i = 0; i < info.num; ++i)
        {
            auto& data = info.info[i];
            char buf[1024] = { 0 };
            FMT2BUF(buf,
                "insert into auction_house (item_name, item_num, item_price, currency_type, start_time, keep_time, status, orderID, ownerID, ownerName) "
                "values ('{}', {}, {}, {}, {}, {}, {}, {}, {}, '{}');",
                ESCA2UTF8(data.item_name), data.item_num, data.item_price, data.currency_type,
                data.start_time,data.keep_time, data.status, data.orderID,
                data.ownerID, ESCA2UTF8(data.ownerName));
            sql += buf;
        }
        break;
    case ProtoMS_SynAuctionItemInfo::updata:        // 改
        for (uint16_t i = 0; i < info.num; ++i)
        {
            auto& data = info.info[i];
            char buf[1024] = { 0 };
            FMT2BUF(buf,
                "update auction_house set item_name = '{}', item_num = {}, item_price = {}, currency_type = {}, "
                "start_time = {}, keep_time = {}, status = {}, orderID = {},ownerID = {}, ownerName = '{}' where orderID = {};",
                ESCA2UTF8(data.item_name), data.item_num, data.item_price, data.currency_type,
                data.start_time, data.keep_time, data.status, data.orderID,
                data.ownerID, ESCA2UTF8(data.ownerName), data.orderID);
            sql += buf;
        }
        break;

    default:
        break;
    }

    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;
    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::UpdateMallInfo(const ProtoMS_MallLimitInfoUpdate& info)
{
    SAFE_BEGIN_EX;

    std::string sql;
    switch (info.opt_type) {
    case ProtoMS_MallLimitInfoUpdate::opt_type_add:        // 增
    {
        if (info.limit_type == mall_limit_type_all)
        {
            for (uint16_t i = 0; i < info.num; ++i)
            {
                auto& data = info.data[i];
                char buf[1024] = { 0 };
                FMT2BUF(buf,
                    "insert into mall_limit_all (id, num) values ({}, {});",data.item_idx,data.num);
                sql += buf;
            }
            break;
        }
        else if(info.limit_type == mall_limit_type_single)
        {
            for (uint16_t i = 0; i < info.num; ++i)
            {
                auto& data = info.data[i];
                char buf[1024] = { 0 };
                FMT2BUF(buf,
                    "insert into mall_limit_single (playerguid, id, num) values ({}, {}, {});",
                    data.playerguid,data.item_idx,data.num);
                sql += buf;
            }
            break;
        }
    }
    case ProtoMS_MallLimitInfoUpdate::opt_type_update:        // 改
    {
        if (info.limit_type == mall_limit_type_all)
        {
            for (uint16_t i = 0; i < info.num; ++i)
            {
                auto& data = info.data[i];
                char buf[1024] = { 0 };
                FMT2BUF(buf,
                    "update mall_limit_all set  num = {} where id = {};",data.num,data.item_idx);
                sql += buf;
            }
            break;
        }
        else if (info.limit_type == mall_limit_type_single)
        {
            for (uint16_t i = 0; i < info.num; ++i)
            {
                auto& data = info.data[i];
                char buf[1024] = { 0 };
                FMT2BUF(buf,
                    "update mall_limit_single set playerguid = {},id = {},  num = {} where id = {} and playerguid = {};", 
                    data.playerguid, data.item_idx, data.num,data.item_idx,data.playerguid);
                sql += buf;
            }
            break;
        }
    }
    default:
        return DBERR_OK;
    }

    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;
    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetCustVars(CUST_VAR_SP_LIST &vars)
{
    SAFE_BEGIN_EX;

    const char *sql = "select * from cust_var";
    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    auto num = m_DBConnector.GetQueryRowNum();

    for (auto i = 0; i < num; ++i) {

        auto var = std::make_shared<CUST_VAR>();

        m_DBConnector.GetQueryFieldData("belong", var->belong);
        m_DBConnector.GetQueryFieldData("name", var->name);
        m_DBConnector.GetQueryFieldData("value", var->value);
        m_DBConnector.GetQueryFieldData("type", var->type);
        m_DBConnector.GetQueryFieldData("expire", var->expire);
        m_DBConnector.GetQueryFieldData("mergeType", var->mergeType);

        vars.emplace_back(std::move(var));

        m_DBConnector.QueryNext();
    }

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SetCustVar(CUST_VAR var)
{
    SAFE_BEGIN_EX;

    std::string sql;

    if (var.value.empty()) {

        sql = fmt::format("delete from cust_var where belong = {} and name = '{}'",
                          var.belong, ESCA2UTF8(std::move(var.name)));
    }
    else {
        sql = fmt::format("insert into cust_var (belong, name, value, type, expire, mergeType) "
                          "values ({}, '{}', '{}', {}, {}, {}) "
                          "on duplicate key update value = values(value), type = values(type), "
                          "expire = values(expire), mergeType = values(mergeType)",
                          var.belong, ESCA2UTF8(std::move(var.name)), ESCA2UTF8(std::move(var.value)),
                          var.type, var.expire, var.mergeType);
    }

    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetPlayerCustVar(const uint64_t &roleid, CUST_VAR_MAP &vars)
{
    SAFE_BEGIN_EX;

    char sql[100] = {0};
    FMT2BUF(sql,
        "select name, value, type, expire from role_cust_var where belong = {}", roleid);

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    auto num = m_DBConnector.GetQueryRowNum();

    std::string name;

    for (auto i = 0; i < num; ++i) {

        m_DBConnector.GetQueryFieldData("name", name);

        auto &var = vars[name];
        var.belong = roleid;
        var.name = std::move(name);

        m_DBConnector.GetQueryFieldData("value", var.value);
        m_DBConnector.GetQueryFieldData("type", var.type);
        m_DBConnector.GetQueryFieldData("expire", var.expire);

        m_DBConnector.QueryNext();
    }

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SyncPlayerCustVar(CUST_VAR_LIST add, CUST_VAR_LIST remove, CUST_VAR_LIST update)
{
    return SyncCustVar("role_cust_var", add, remove, update);
}

int CDBManager::GetPlayerItemCustVar(const uint64_t &roleid, CUST_VAR_SP_LIST &vars, uint8_t state, std::string tableName, std::string tName)
{
    SAFE_BEGIN_EX;

    char sql[150];
    FMT2BUF(sql,
        "select * from {} where belong in (select guid from {} where role = {} and state = {})", ESCA2UTF8(tableName.c_str()), ESCA2UTF8(tName.c_str()), roleid, state);

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    auto num = m_DBConnector.GetQueryRowNum();

    for (auto i = 0; i < num; ++i) {

        auto var = std::make_shared<CUST_VAR>();

        m_DBConnector.GetQueryFieldData("belong", var->belong);
        m_DBConnector.GetQueryFieldData("name", var->name);
        m_DBConnector.GetQueryFieldData("value", var->value);
        m_DBConnector.GetQueryFieldData("type", var->type);
        m_DBConnector.GetQueryFieldData("expire", var->expire);

        vars.emplace_back(std::move(var));

        m_DBConnector.QueryNext();
    }

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetItemCustVars(uint64_t itemGUID, CUST_VAR_SP_LIST &vars, uint8_t state,
                                const char *varTable, const char *itemTable)
{
    SAFE_BEGIN_EX;

    char sql[200];
    FMT2BUF(sql, "select v.* from {} as v join {} as i on v.belong = i.guid "
            "where guid = {} and state = {}", varTable, itemTable, itemGUID, state);

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    auto num = m_DBConnector.GetQueryRowNum();

    for (auto i = 0; i < num; ++i) {

        auto var = std::make_shared<CUST_VAR>();

        m_DBConnector.GetQueryFieldData("belong", var->belong);
        m_DBConnector.GetQueryFieldData("name", var->name);
        m_DBConnector.GetQueryFieldData("value", var->value);
        m_DBConnector.GetQueryFieldData("type", var->type);
        m_DBConnector.GetQueryFieldData("expire", var->expire);

        vars.emplace_back(std::move(var));

        m_DBConnector.QueryNext();
    }

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SyncItemCustVar(CUST_VAR_SP_LIST *add, CUST_VAR_SP_LIST *remove, CUST_VAR_SP_LIST *update)
{
    return SyncCustVar("item_cust_var", add, remove, update);
}



int CDBManager::SyncCustVar(const char *table, CUST_VAR_LIST &add, CUST_VAR_LIST &remove, CUST_VAR_LIST &update)
{
    SAFE_BEGIN_EX;

    std::string sql;

    for (auto &var : add) {
        sql += fmt::format("insert ignore into {} (belong, name, value, type, expire) values ({}, '{}', '{}', {}, {});",
            table, var.belong, ESCA2UTF8(std::move(var.name)), ESCA2UTF8(std::move(var.value)), var.type, var.expire);
    }

    for (auto &var : remove) {
        sql += fmt::format("delete ignore from {} where belong = {} and name = '{}';",
            table, var.belong, ESCA2UTF8(std::move(var.name)));
    }

    for (auto &var : update) {
        sql += fmt::format("update ignore {} set value = '{}', type = {}, expire = {} where belong = {} and name = '{}';",
            table, ESCA2UTF8(std::move(var.value)), var.type, var.expire, var.belong, ESCA2UTF8(std::move(var.name)));
    }

    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SyncCustVar(const char *table, CUST_VAR_SP_LIST *add, CUST_VAR_SP_LIST *remove, CUST_VAR_SP_LIST *update)
{
    SAFE_BEGIN_EX;

    std::string sql;

    if (add) {
        for (auto &var : *add) {
            sql += fmt::format("insert ignore into {} (belong, name, value, type, expire) "
                               "values ({}, '{}', '{}', {}, {}) "
                               "on duplicate key update value = values(value), "
                               "type = values(type), expire = values(expire); ",
                               table, var->belong, ESCA2UTF8(std::move(var->name)),
                               ESCA2UTF8(std::move(var->value)), var->type, var->expire);
        }
    }

    if (remove) {
        for (auto &var : *remove) {
            sql += fmt::format("delete ignore from {} where belong = {} and name = '{}' and EXISTS (SELECT 1 FROM item WHERE guid = {} AND state = {});",
                table, var->belong, ESCA2UTF8(std::move(var->name)), var->belong, (uint8_t)item_state_owner);
        }
    }

    if (update) {
        for (auto &var : *update) {
            sql += fmt::format("update ignore {} set value = '{}', type = {}, expire = {} where belong = {} and name = '{}';",
                table, ESCA2UTF8(std::move(var->value)), var->type, var->expire, var->belong, ESCA2UTF8(std::move(var->name)));
        }
    }

    if (!sql.empty() && !ExecuteSQL(sql.c_str())) return DBERR_EXESQL;

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SyncQuickBar(const char* table, void *pData)
{
    SAFE_BEGIN_EX;
    QUICK_BAR_INFO_LIST vars;
    auto msg = (ProtoCS_SyncQuickBarSet*)(pData);
    char sql[300] = { 0 };
    FMT2BUF(sql,
        "select slot, type, id, guid from quick_bar_set where belong = {}", msg->info[0].role_id);
    if (!ExecuteSQL(sql)) return DBERR_EXESQL;
    auto num = m_DBConnector.GetQueryRowNum();
    QUICK_BAR_INFO var;
    for (auto i = 0; i < num; ++i) {
        try{
            m_DBConnector.GetQueryFieldData("slot", var.slot);
            m_DBConnector.GetQueryFieldData("id", var.id);
            m_DBConnector.GetQueryFieldData("guid", var.guid);
            m_DBConnector.GetQueryFieldData("type", var.type);
            vars.push_back(var);
        }
        catch (...) {
            LOG_ERROR("Exception occurred");
        }
        m_DBConnector.QueryNext();
    }
    std::string mysql = "";
    char buf[300] = { 0 };
    for (int i = 0; i < msg->num; ++i)
    {
        auto j = vars.begin();
        for (;j!=vars.end();++j)
        {
            if (j->slot == msg->info[i].quick.slot) {
                FMT2BUF(buf,
                "update {} set type = {}, id = {}, guid = {} where belong = {} and slot = {};",
                    table, msg->info[i].quick.type, msg->info[i].quick.id, msg->info[i].quick.guid, msg->info[i].role_id, msg->info[i].quick.slot);
                    mysql += buf;
                break;
            }
        }
        if (j == vars.end()){
            FMT2BUF(buf,
                "insert into {} (belong, slot, type, id, guid) values ({}, {}, {}, {}, {});",
                table, msg->info[i].role_id, msg->info[i].quick.slot, msg->info[i].quick.type, msg->info[i].quick.id, msg->info[i].quick.guid);
            mysql += buf;
        }
    }
    if (!ExecuteSQL(mysql.c_str())) return DBERR_EXESQL;
    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SyncQuickBarSet(void* pData)
{
    auto* msg = static_cast<ProtoCS_SyncQuickBarSet*>(pData);
    return SyncQuickBar("quick_bar_set", msg);
}

int CDBManager::GetQuickBarSetInfo(const uint64_t& nRoleID, QUICK_BAR_INFO_LIST& vars)
{
    SAFE_BEGIN_EX;
    char sql[300] = { 0 };
    FMT2BUF(sql,
        "select slot, type, id, guid from quick_bar_set where belong = {} HAVING (TYPE != 0 or id != 0 or guid !=0)", nRoleID);
    if (!ExecuteSQL(sql)) return DBERR_EXESQL;
    auto num = m_DBConnector.GetQueryRowNum();
    QUICK_BAR_INFO var;
    for (auto i = 0; i < std::min<int>(num, 30); ++i) {

        try
        {
            m_DBConnector.GetQueryFieldData("slot", var.slot);
            m_DBConnector.GetQueryFieldData("id", var.id);
            m_DBConnector.GetQueryFieldData("guid", var.guid);
            m_DBConnector.GetQueryFieldData("type", var.type);
            if (var.guid == 0 && var.id == 0 && var.type == 0)
            {
                continue;
            }
            vars.push_back(var);
        }
        catch (...) {
            LOG_ERROR("Exception occurred");
        }
        m_DBConnector.QueryNext();
    }
    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SyncDgnBindInfo(void* pData)
{
    auto* msg = static_cast<ProtoCS_SyncDgnBindInfo*>(pData);
    SAFE_BEGIN_EX;
    std::string sql = "";
    char buf[1024] = { 0 };
    if (0 == msg->packIdx)
    {
        FMT2BUF(buf, "delete from dgn_bind_info where roleId = {};", msg->roleId);
        sql += buf;
    }
    for (int i = 0; i < msg->num; ++i)
    {
        FMT2BUF(buf,
            "insert into dgn_bind_info (roleId, dgnkeyName, dgnId) values ({}, '{}', {});",
                msg->info[i].roleId, ESCA2UTF8(msg->info[i].dgnKeyName), msg->info[i].dgnId);
        sql += buf;
    }

    if (!sql.empty() && !ExecuteSQL(sql.c_str())) return DBERR_EXESQL;

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetDgnBindInfo(const uint64_t& nRoleID, DGN_BIND_INFO_LIST& vars)
{
    SAFE_BEGIN_EX;
    char sql[1024] = { 0 };
    FMT2BUF(sql,
        "select dgnKeyName, dgnId from dgn_bind_info where roleId = {}", nRoleID);
    if (!ExecuteSQL(sql)) return DBERR_EXESQL;
    auto num = m_DBConnector.GetQueryRowNum();
    DGN_BIND_INFO var;
    for (auto i = 0; i < num; ++i) 
    {
        try
        {
            var.roleId = nRoleID;
            m_DBConnector.GetQueryFieldData("dgnKeyName", var.dgnKeyName, sizeof(var.dgnKeyName), true);
            m_DBConnector.GetQueryFieldData("dgnId", var.dgnId);
            vars.push_back(var);
        }
        catch (...) {
            LOG_ERROR("Exception occurred");
        }
        m_DBConnector.QueryNext();
    }
    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}
 
int CDBManager::AddNewMail(const ProtoMS_AddSysNewMail& data, std::vector<std::pair<uint64_t, uint64_t>>&info)
{
    SAFE_BEGIN_EX;
    string addtioninfo = JsonStyleEncode(data.infos);
    addtioninfo = ESCA2UTF8(std::move(addtioninfo));
    
    string currencyinfo = JsonStyleEncode(data.infos, 0);
    currencyinfo = ESCA2UTF8(std::move(currencyinfo));

    std::string title = ESCA2UTF8(data.infos.title);
    std::string text = ESCA2UTF8(data.infos.text);
    std::string sender = ESCA2UTF8(data.infos.sendername);

    std::vector<uint64_t> mailsGuid;
    uint64_t mail_id = GenerateObjID(E_OBJ_MAIL, ConfigInfo::GetInstance());

    char sql[1024] = { 0 };
    auto addAllFunc = [&]() ->uint16_t{

            FMT2BUF(sql,"insert into mails_list_info (playerguid, mailID, title, text, currency_info,status ,item_info, addition_item_num,send_time,type,sendername,cpy_guid)"
                "values({}, {}, '{}', '{}', '{}', {}, '{}', {}, {}, {}, '{}', {})",
                0, mail_id, title, text,
                currencyinfo, data.infos.status, addtioninfo, data.infos.addition_item_num,
                data.infos.send_timesmap, data.infos.type, sender, 0);
            if (!ExecuteSQL(sql)) return DBERR_EXESQL;

            memset(sql, 0, _countof(sql));

            std::string mysql = "";
            // 给所有人添加 
            FMT2BUF(sql, "select id,name from role where online_state = {}", (uint16_t)online_state_logged_in);
            if (!ExecuteSQL(sql)) return DBERR_EXESQL;
            int num = m_DBConnector.GetQueryRowNum();
            //if (num == 0) { return ERR_MAIL_ADD_NONPLAYER; }//回调函数说明无该玩家 插入邮件失败
            uint64_t playerguid = 0;
            for (int i = 0; i < num; ++i)
            {
                try
                {
                    uint64_t mailID = GenerateObjID(E_OBJ_MAIL, ConfigInfo::GetInstance());

                    m_DBConnector.GetQueryFieldData("id", playerguid);
                    info.push_back(make_pair(playerguid, mailID));
                }
                catch (...) {
                    LOG_ERROR("Exception occurred");
                }
                m_DBConnector.QueryNext();
            }
            int addnum = 0;
            for (int i = 0; i < info.size(); ++i)
            {
                char tmpbuf[1024] = { 0 };
                if (addnum == 0)
                {
                    FMT2BUF(tmpbuf, "insert into mails_list_info (playerguid, mailID, title, text, currency_info,status ,item_info, addition_item_num,send_time,type,sendername, cpy_guid)values");
                    mysql += tmpbuf;
                }
                char buf[10240] = { 0 };
                FMT2BUF(buf, "({}, {}, '{}', '{}', '{}', {}, '{}', {},{},{},'{}',{}),", info[i].first, info[i].second, title, text,
                    currencyinfo, data.infos.status, addtioninfo, data.infos.addition_item_num,
                    data.infos.send_timesmap, data.infos.type, sender, mail_id);
                mysql += buf;

                mailsGuid.push_back(info[i].second);
                ++addnum;
                if (addnum == 1000)
                {
                    mysql.erase(--mysql.end());
                    bool res = ExecuteSQL(mysql.c_str());
                    SendDBLogData(log_type_mail_info, LogMailInfo(mailsGuid, LogMailInfo::LogMailUpdateFlag::LMUF_INSERT));
                    if (!res) return DBERR_EXESQL;
                    addnum = 0;
                    mysql.clear();
                    mailsGuid.clear();
                }
            }
            if (addnum > 0 && addnum < 1000)
            {
                mysql.erase(--mysql.end());
                bool res = ExecuteSQL(mysql.c_str());
                SendDBLogData(log_type_mail_info, LogMailInfo(mailsGuid, LogMailInfo::LogMailUpdateFlag::LMUF_INSERT));
                if (!res) return DBERR_EXESQL;
                mailsGuid.clear();
            }
            return DBERR_OK;

    };

    auto addBatchFunc = [&]()->uint16_t {
        std::string mysql = "";

        //// 验证guid是否正确
        //for (int i = 0; i < data.num; ++i)
        //{
        //    try
        //    {
        //        FMT2BUF(sql, "select id,name from role where id = {}",data.guid[i]);
        //        if (!ExecuteSQL(sql)) continue;
        //        uint64_t mail_id = GenerateObjID(E_OBJ_MAIL, ConfigInfo::GetInstance());
        //        info.push_back(make_pair(data.guid[i], mail_id));
        //    }
        //    catch (...) {
        //        LOG_ERROR("Exception occurred");
        //    }
        //}

        int addnum = 0;
        for (int i = 0; i < data.num; ++i)
        {
            char tmpbuf[1024] = { 0 };
            if (addnum == 0)
            {
                FMT2BUF(tmpbuf, "insert into mails_list_info (playerguid, mailID, title, text, currency_info,status ,item_info, addition_item_num,send_time,type,sendername)values");
                mysql += tmpbuf;
            }
            char buf[10240] = { 0 };

            uint64_t mail_id = GenerateObjID(E_OBJ_MAIL, ConfigInfo::GetInstance());
            info.push_back(make_pair(data.guid[i], mail_id));

            FMT2BUF(buf, "({}, {}, '{}', '{}', '{}', {}, '{}', {},{},{},'{}'),", data.guid[i], mail_id, title, text,
                currencyinfo, data.infos.status, addtioninfo, data.infos.addition_item_num,
                data.infos.send_timesmap, data.infos.type, sender);
            mysql += buf;

            mailsGuid.push_back(mail_id);
            ++addnum;
            if (addnum == 1000)
            {
                mysql.erase(--mysql.end());
                bool res = ExecuteSQL(mysql.c_str());
                SendDBLogData(log_type_mail_info, LogMailInfo(mailsGuid, LogMailInfo::LogMailUpdateFlag::LMUF_INSERT));
                if (!res) return DBERR_EXESQL;
                addnum = 0;
                mysql.clear();
                mailsGuid.clear();
            }
        }
        if (addnum > 0 && addnum < 1000)
        {
            mysql.erase(--mysql.end());
            bool res = ExecuteSQL(mysql.c_str());
            SendDBLogData(log_type_mail_info, LogMailInfo(mailsGuid, LogMailInfo::LogMailUpdateFlag::LMUF_INSERT));
            if (!res) return DBERR_EXESQL;
            mailsGuid.clear();
        }
        return DBERR_OK;
    };

    auto addSingleFunc = [&](uint64_t guid)->uint16_t {
        uint64_t mail_id = GenerateObjID(E_OBJ_MAIL, ConfigInfo::GetInstance());
        info.push_back(make_pair(guid, mail_id));

        char buf[10240] = { 0 };
        FMT2BUF(buf,
            "insert into mails_list_info (playerguid, mailID, title, text, currency_info,status ,item_info, addition_item_num,send_time,type,sendername)"
            "value ({}, {}, '{}', '{}', '{}', {}, '{}', {},{},{},'{}');",
            guid, mail_id, title, text, currencyinfo, data.infos.status,
            addtioninfo, data.infos.addition_item_num, data.infos.send_timesmap, data.infos.type, sender);
        bool res = ExecuteSQL(buf);
        mailsGuid.push_back(mail_id);
        SendDBLogData(log_type_mail_info, LogMailInfo(mailsGuid, LogMailInfo::LogMailUpdateFlag::LMUF_INSERT));
        if (!res) return DBERR_EXESQL;
        return DBERR_OK;
    };
    if (data.addType == ProtoMS_AddSysNewMail::add_type_by_name)
    {
        if (strcmp(data.rolename, "0") == 0)
        {
            return addAllFunc();
        }
        else
        {
            // 给单人加
            FMT2BUF(sql,
                "select id,name from role where name = '{}'", ESCA2UTF8(data.rolename));
            if (!ExecuteSQL(sql)) return DBERR_EXESQL;
            int num = m_DBConnector.GetQueryRowNum();
            if (num == 0) { return ERR_MAIL_ADD_NONPLAYER; }//回调函数说明无该玩家 插入邮件失败
            uint64_t playerguid = 0;
            try
            {
                m_DBConnector.GetQueryFieldData("id", playerguid);
            }
            catch (...) {
                LOG_ERROR("Exception occurred");
                return DBERR_EXCEPT;
            }
            return addSingleFunc(playerguid);

        }
    }
    else if (data.addType == ProtoMS_AddSysNewMail::add_type_by_guid)
    {
        // 给所有人加
        if (data.guid[0] == 0 && data.num == 1){
            return addAllFunc();
        }
        else if (data.num > 1) {
            return addBatchFunc();
        }
        else{
            // 给单人加
            FMT2BUF(sql,
                "select name from role where id = {}", data.guid[0]);
            if (!ExecuteSQL(sql)) return DBERR_EXESQL;
            int num = m_DBConnector.GetQueryRowNum();
            if (num == 0) { return ERR_MAIL_ADD_NONPLAYER; }//回调函数说明无该玩家 插入邮件失败
            return addSingleFunc(data.guid[0]);
        }
    }
    else
    {
        return ERR_MAIL_NO_ADD_TYPE;
    }

    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::DeleteMailByMailID(const uint64_t& MailID)
{
    SAFE_BEGIN_EX;

    char sql[256] = { 0 };
    FMT2BUF(sql, "select status,mailID from mails_list_info where mailID = {}",MailID);
    if (!ExecuteSQL(sql)) return DBERR_EXESQL;
    int num = m_DBConnector.GetQueryRowNum();
    if (!num)return ERR_MAIL_NO_MAIL;
    unsigned int status = 0;
    try{
        m_DBConnector.GetQueryFieldData("status", status);
    }
    catch (...) {
        LOG_ERROR("Exception occurred");
    }
    status |= mail_status_delete;
    memset(sql, 0, _countof(sql));
    FMT2BUF(sql, "update mails_list_info set status = {} where mailID = {}",status, MailID);
    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    SendDBLogData(log_type_mail_info, LogMailInfo({ MailID }, LogMailInfo::LogMailUpdateFlag::LMUF_DELETE));
    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SyncMailInfoStatus(uint64_t playerguid, uint16_t num, const Mail_Info_Status* info)
{
    SAFE_BEGIN_EX;
    if (num)
    {
        string sql = "";
        for (int i = 0; i < num; ++i) {
            char buf[300] = { 0 };
            FMT2BUF(buf,
                "update mails_list_info set status = {} where mailID = {} and playerguid = {};",
                info[i].status, info[i].mailid, playerguid);
            sql += buf;
        }
        bool res = ExecuteSQL(sql.c_str());
        SendDBLogData(log_type_mail_info, LogMailInfo(info, num));
        if (!res) return DBERR_EXESQL;
    }
    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetMailInfo(uint64_t playerguid, std::list<MAIL_INFO>& maillist)
{
    SAFE_BEGIN_EX;
    char sql[1024] = { 0 };
    FMT2BUF(sql,
        "select mailID,title,text,currency_info,status,item_info,addition_item_num,send_time,type,sendername from mails_list_info "
        "where playerguid = {} having UNIX_TIMESTAMP(NOW()) - send_time <= {} and !(status & {})"
        "order by send_time desc, status desc limit {}", playerguid, MAX_MAIL_REMAIN_DATE,(uint16_t)mail_status_delete, ADD_MAIL_MAX_NUM);
    if (!ExecuteSQL(sql)) return DBERR_EXESQL;
    
    int num = m_DBConnector.GetQueryRowNum();


    for (int i = 0; i < num; ++i)
    {
        MAIL_INFO data;
        data.playerguid = playerguid;
        try
        {
            m_DBConnector.GetQueryFieldData("mailID", data.mail_id);
            m_DBConnector.GetQueryFieldData("title", data.title,sizeof(data.title));
            m_DBConnector.GetQueryFieldData("text", data.text, sizeof(data.text));
            string currency_info;
            m_DBConnector.GetQueryFieldData("currency_info", currency_info);
            m_DBConnector.GetQueryFieldData("status", data.status);
            m_DBConnector.GetQueryFieldData("addition_item_num", data.addition_item_num);
            string addition_item_info;
            m_DBConnector.GetQueryFieldData("item_info", addition_item_info);

            m_DBConnector.GetQueryFieldData("send_time", data.send_timesmap);
            m_DBConnector.GetQueryFieldData("type", data.type);
            m_DBConnector.GetQueryFieldData("sendername", data.sendername, sizeof(data.sendername));
            JsonStyleDecode(addition_item_info, data);
            JsonStyleDecode(currency_info, data, 0);
            maillist.emplace_back(data);
        }
        catch (...) {
            LOG_ERROR("Exception occurred");
        }
        m_DBConnector.QueryNext();
    }

    memset(sql, 0, _countof(sql));

    std::list<MAIL_INFO> serverMail;
    FMT2BUF(sql,
        "select mailID,title,text,currency_info,status,item_info,addition_item_num,send_time,type,sendername from mails_list_info "
        "where playerguid = {} and cpy_guid = {} having (UNIX_TIMESTAMP(NOW()) - send_time <= {}) and !(status & {})", 0, 0, MAX_MAIL_REMAIN_DATE, (uint16_t)mail_status_delete);
    if (!ExecuteSQL(sql)) {
        LOG_ERROR("Get All Server Mail Failed!");
        return DBERR_OK;
    }

    int serverNum = m_DBConnector.GetQueryRowNum();
    for (int i = 0; i < serverNum; ++i) {

        MAIL_INFO data;
        data.playerguid = playerguid;
        try
        {
            m_DBConnector.GetQueryFieldData("mailID", data.mail_id);
            m_DBConnector.GetQueryFieldData("title", data.title, sizeof(data.title));
            m_DBConnector.GetQueryFieldData("text", data.text, sizeof(data.text));
            string currency_info;
            m_DBConnector.GetQueryFieldData("currency_info", currency_info);
            m_DBConnector.GetQueryFieldData("status", data.status);
            m_DBConnector.GetQueryFieldData("addition_item_num", data.addition_item_num);
            string addition_item_info;
            m_DBConnector.GetQueryFieldData("item_info", addition_item_info);

            m_DBConnector.GetQueryFieldData("send_time", data.send_timesmap);
            m_DBConnector.GetQueryFieldData("type", data.type);
            m_DBConnector.GetQueryFieldData("sendername", data.sendername, sizeof(data.sendername));
            JsonStyleDecode(addition_item_info, data);
            JsonStyleDecode(currency_info, data, 0);
            serverMail.emplace_back(data);
        }
        catch (...) {
            LOG_ERROR("Exception occurred");
        }
        m_DBConnector.QueryNext();
    
    }

    for (auto& i : serverMail) {
        memset(sql, 0, _countof(sql));

        FMT2BUF(sql,
            "select cpy_guid,status from mails_list_info where playerguid = {} and cpy_guid = {} ", playerguid, i.mail_id);

        if (!ExecuteSQL(sql)) {
            LOG_ERROR("Get Single Mail Failed!");
            continue;
        }

        int singleNum = m_DBConnector.GetQueryRowNum();
        if (singleNum == 0) {

            uint64_t mailID = GenerateObjID(E_OBJ_MAIL, ConfigInfo::GetInstance());

            std::string currency_info = JsonStyleEncode(i, 0);
            string addition_item_info = JsonStyleEncode(i);

            currency_info = ESCA2UTF8(std::move(currency_info));
            addition_item_info = ESCA2UTF8(std::move(addition_item_info));

            memset(sql, 0, _countof(sql));
            FMT2BUF(sql,
                "insert into mails_list_info (playerguid, mailID, title, text, currency_info,status ,item_info,"
                "addition_item_num, send_time, type, sendername, cpy_guid)"
                "values({}, {}, '{}', '{}', '{}', {}, '{}', {}, {}, {}, '{}', {}); ",
                playerguid, mailID, ESCA2UTF8(i.title), ESCA2UTF8(i.text),
                currency_info, i.status, addition_item_info, i.addition_item_num,
                i.send_timesmap, i.type, ESCA2UTF8(i.sendername), i.mail_id);

            if (!ExecuteSQL(sql)) {
                LOG_ERROR("Insert Single Mail Failed!");
                continue;
            }
            i.mail_id = mailID;
            i.playerguid = playerguid;
            maillist.push_back(i);
        }
    }

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::UpdateItemState(uint64_t itemGuid, uint32_t state)
{
    char buf[1024] = { 0 };
    FMT2BUF(buf, "update item set state = {} where guid = {};", state, itemGuid);

    if (!ExecuteSQL(buf)) return DBERR_EXESQL;
    return DBERR_OK;
}

void CDBManager::MailUpdateDay()
{
    char buf[1024] = { 0 };
    FMT2BUF(buf, "delete from mails_list_info where UNIX_TIMESTAMP(NOW()) - send_time >= {}", MAX_MAIL_REMAIN_DATE);
    if (!CDBManager::GetInstance()->ExecuteSQL(buf)) {
        LOG_ERROR("Mail Day Delete failed! Cur Time:%s", TimeHelper::GetInstance()->GetCurTimeStr().c_str());
    }
}

int CDBManager::GetMailAttachment(const ProtoMS_GetMailAttachmentReq& req, ProtoCS_GetMailAttachmentAck& ack)
{
    SAFE_BEGIN_EX;

    ITEM_INFO &item = ack.item;

    auto res = GetItemInfoByItemGuid(req.role_guid, req.item_guid, item.base_info, item_state_unaccalimed);
    if (res != DBERR_OK) return res;

    if (item.base_info.guid == 0) return DBERR_EMPTY;

    GetItemExtraData(req.role_guid, req.item_guid, item, item_state_unaccalimed);

    char buf[100] = { 0 };
    FMT2BUF(buf, "update item set state = {} where guid = {};", (uint32_t)item_state_owner, req.item_guid);

    if (!ExecuteSQL(buf)) return DBERR_EXESQL;
    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetAuctionHouseList(std::vector<AUCTION_HOUSE_ITEM_INFO>& req)
{
    SAFE_BEGIN_EX;
    auto stamp = time(nullptr);
    char sql[256] = { 0 };
    FMT2BUF(sql, "select item_name,item_num,item_price,currency_type,start_time, keep_time,status,orderID,ownerID,ownerName "
        "from auction_house having ({} - start_time) < {} ", stamp, MAX_AUCTION_HOUSE_REMAIN_DATE);// (0:玩家身上(背包\仓库) 1.上架(出售)中 2.未领取(邮件))

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    int nRowNum = m_DBConnector.GetQueryRowNum();
    for (int i = 0; i < nRowNum; ++i) {
        try {
            AUCTION_HOUSE_ITEM_INFO data;
            m_DBConnector.GetQueryFieldData("item_name", data.item_name, _countof(data.item_name));
            m_DBConnector.GetQueryFieldData("item_num", data.item_num);
            m_DBConnector.GetQueryFieldData("item_price", data.item_price);
            m_DBConnector.GetQueryFieldData("currency_type", data.currency_type);
            m_DBConnector.GetQueryFieldData("start_time", data.start_time);
            m_DBConnector.GetQueryFieldData("keep_time", data.keep_time);
            m_DBConnector.GetQueryFieldData("status", data.status);
            m_DBConnector.GetQueryFieldData("orderID", data.orderID);
            m_DBConnector.GetQueryFieldData("ownerID", data.ownerID);
            m_DBConnector.GetQueryFieldData("ownerName", data.ownerName,_countof(data.ownerName));
            req.push_back(data);
        }
        catch (...) {
            LOG_ERROR("Exception occurred");
        }
        m_DBConnector.QueryNext();
    }

    UpdateAuctionHouseInfo(req);
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

void CDBManager::UpdateAuctionHouseInfo(std::vector<AUCTION_HOUSE_ITEM_INFO>& req)
{
    ProtoMS_SynAuctionItemInfo updateinfo;
    updateinfo.type = ProtoMS_SynAuctionItemInfo::updata;
    int idx = 0;
    auto curtime = time(nullptr);
    for (auto iter = req.begin(); iter != req.end(); ++iter)
    {
        if (iter->status == AUCTION_HOUSE_ITEM_INFO::auction_status_type_wait)
        {
            if (curtime >= iter->start_time + iter->keep_time)
            {
                iter->status = AUCTION_HOUSE_ITEM_INFO::auction_status_type_passin;
                updateinfo.info[idx] = *iter;
                ++idx;
            }
            else if (curtime <= iter->start_time + iter->keep_time
                && curtime >= iter->start_time)
            {
                iter->status = AUCTION_HOUSE_ITEM_INFO::auction_status_type_ing;
                updateinfo.info[idx] = *iter;
                ++idx;
            }
        }
        else if (iter->status == AUCTION_HOUSE_ITEM_INFO::auction_status_type_ing)
        {
            if (curtime >= iter->start_time + iter->keep_time)
            {
                iter->status = AUCTION_HOUSE_ITEM_INFO::auction_status_type_passin;
                updateinfo.info[idx] = *iter;
                ++idx;
            }
        }
    }
    updateinfo.num = idx + 1;
    SyncAuctionItemInfo(updateinfo);
}

int CDBManager::GetMallLimitInfo(uint8_t limit_type, vector<MALL_ITEM_INFO_BASE>& data)
{
    SAFE_BEGIN_EX;
    char sql[256] = { 0 };
    switch (limit_type)
    {
    case mall_limit_type_all:
        {
            FMT2BUF(sql, "select id ,num from mall_limit_all");
            if (!ExecuteSQL(sql)) return DBERR_EXESQL;
            int nRowNum = m_DBConnector.GetQueryRowNum();
            for (int i = 0; i < nRowNum; ++i) {
                try {
                    MALL_ITEM_INFO_BASE info;
                    m_DBConnector.GetQueryFieldData("id", info.item_idx);
                    m_DBConnector.GetQueryFieldData("num", info.num);
                    data.emplace_back(info);
                }
                catch (...) {
                    LOG_ERROR("Exception occurred");
                }
                m_DBConnector.QueryNext();
            }
            break;
        }
    case mall_limit_type_single:
        {
            FMT2BUF(sql, "select playerguid,id ,num from mall_limit_single");
            if (!ExecuteSQL(sql)) return DBERR_EXESQL;
            int nRowNum = m_DBConnector.GetQueryRowNum();
            for (int i = 0; i < nRowNum; ++i) {
                try {
                    MALL_ITEM_INFO_BASE info;
                    m_DBConnector.GetQueryFieldData("playerguid", info.playerguid);
                    m_DBConnector.GetQueryFieldData("id", info.item_idx);
                    m_DBConnector.GetQueryFieldData("num", info.num);
                    data.emplace_back(info);
                }
                catch (...) {
                    LOG_ERROR("Exception occurred");
                }
                m_DBConnector.QueryNext();
            }
            break;
        }
    }

    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::DeleteMallRemainedData()
{
    SAFE_BEGIN_EX;
    char sql[1024] = { 0 };
    FMT2BUF(sql, "truncate table mall_limit_all;truncate table mall_limit_single");
    if (!ExecuteSQL(sql)) return DBERR_EXESQL;
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}
int CDBManager::AddLoginIpType(uint8_t num, uint32_t* ip, uint8_t ip_type)
{
    SAFE_BEGIN_EX;
    std::string sqlEx = "";
    for (int i = 0; i < num; ++i)
    {
        char sql[256] = { 0 };
        FMT2BUF(sql, "select ip,type from login_ip where ip ={}", ip[i]);
        if (!ExecuteSQL(sql))
        {
            LOG_ERROR("add login ip type::query ip failed,ip:%d", ip[i]);
            continue;
        }
        char buf[256] = { 0 };
        int nRowNum = m_DBConnector.GetQueryRowNum();
        if (nRowNum == 0)
        {
            FMT2BUF(buf, "insert into login_ip(ip,type)value({},{});", ip[i], ip_type);
            sqlEx += buf;
        }
        else
        {
            FMT2BUF(buf, "update login_ip set type = {} where ip = {};", ip_type, ip[i]);
            sqlEx += buf;
        }
    }
    if (!ExecuteSQL(sqlEx.c_str())) return DBERR_EXESQL;

    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::DelLoginIpType(uint8_t num, uint32_t* ip, uint8_t ip_type)
{
    SAFE_BEGIN_EX;
    std::string sqlEx = "";
    for (int i = 0; i < num; ++i)
    {
        char sql[256] = { 0 };
        FMT2BUF(sql, "select ip,type from login_ip where ip ={}", ip[i]);
        if (!ExecuteSQL(sql))
        {
            LOG_ERROR("add login ip type::query ip failed,ip:%d", ip[i]);
            continue;
        }

        char buf[256] = { 0 };
        int nRowNum = m_DBConnector.GetQueryRowNum();
        if (nRowNum == 0)
        {
            LOG_WARN("can't find ip from login_ip table ,del ip failed, ip:%d", ip[i]);
            continue;
        }
        else
        {
            FMT2BUF(buf, "delete from login_ip where type = {} and ip = {};", ip_type, ip[i]);
            sqlEx += buf;
        }
    }
    if (!ExecuteSQL(sqlEx.c_str())) return DBERR_EXESQL;

    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::UpdateSupportPlayer(uint8_t& num, uint8_t type, char name[100][32], uint64_t guid[100])
{
    SAFE_BEGIN_EX;
    const auto& globalDB = ConfigInfo::GetInstance()->m_sMySQLGlobalServDBName;
    std::string sqlEx = "";
    for (int i = 0; i < num; ++i)
    {
        if (name[i] == NULL || strlen(name[i]) == 0) {
            continue;
        }

        char sql[256] = { 0 };
        FMT2BUF(sql, "update {}.player set is_support = {} where name = '{}';", globalDB, type, ESCA2UTF8(name[i]));
        sqlEx += sql;
    }
    if (!ExecuteSQL(sqlEx.c_str())) return DBERR_EXESQL;

    int32_t idx = 0;
    for (int32_t i = 0; i < num; ++i)
    {
        if (name[i] == NULL || strlen(name[i]) == 0) {
            continue;
        }

        char sql[256] = { 0 };
        FMT2BUF(sql, "select id from {}.player where name = '{}';", globalDB, ESCA2UTF8(name[i]));
        if (!ExecuteSQL(sql)) return DBERR_EXESQL;

        int32_t n = m_DBConnector.GetQueryRowNum();
        if (n) m_DBConnector.GetQueryFieldData("id", guid[idx++]);
    }
    num = idx;
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::AddLockPlayer(uint8_t num, char name[100][32])
{
    SAFE_BEGIN_EX;
    const auto &globalDB = ConfigInfo::GetInstance()->m_sMySQLGlobalServDBName;
    std::string sqlEx = "";
    for (int i = 0; i < num; ++i)
    {
        if (name[i] == NULL || strlen(name[i]) == 0) {
            continue;
        }

        char sql[256] = { 0 };
        FMT2BUF(sql, "select name from {}.player where name ='{}'", globalDB, ESCA2UTF8(name[i]));
        if (!ExecuteSQL(sql))
        {
            LOG_ERROR("add lock player::query name failed,name:%s", name[i]);
            continue;
        }

        if (m_DBConnector.GetQueryRowNum() == 0)
        {
            LOG_WARN("not find lock player,player name:%s", name[i]);
            continue;
        }
        memset(sql, 0, _countof(sql));
        FMT2BUF(sql, "update {}.player set is_lock = {} where name = '{}';", globalDB, 1, ESCA2UTF8(name[i]));
        sqlEx += sql;
    }
    if (!ExecuteSQL(sqlEx.c_str())) return DBERR_EXESQL;
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::AddLockRole(uint8_t num, uint64_t guid[100])
{
    SAFE_BEGIN_EX;
    std::string sqlEx = "";
    for (int i = 0; i < num; ++i)
    {
        if (guid[i] == 0) {
            continue;
        }
        char sql[256] = { 0 };
        FMT2BUF(sql, "select * from role where id = {};", guid[i]);
        if (!ExecuteSQL(sql))
        {
            LOG_ERROR("add lock role::query id failed,id:%" PRIu64, guid[i]);
            continue;
        }

        if (m_DBConnector.GetQueryRowNum() == 0)
        {
            LOG_WARN("not find lock role,role id:%" PRIu64, guid[i]);
            continue;
        }

        LOG_WARN("Lock Role :%llu! time: %s",guid[i], TimeHelper::GetInstance()->GetCurTimeStr().c_str());
        memset(sql, 0, _countof(sql));
        FMT2BUF(sql, "update role set is_lock = {} where id = {};", 1, guid[i]);
        sqlEx += sql;
    }
    if (!ExecuteSQL(sqlEx.c_str())) return DBERR_EXESQL;

    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::DelLockPlayer(uint8_t num, char name[100][32])
{
    SAFE_BEGIN_EX;
    const auto &globalDB = ConfigInfo::GetInstance()->m_sMySQLGlobalServDBName;
    std::string sqlEx = "";
    for (int i = 0; i < num; ++i)
    {
        if (name[i] == NULL || strlen(name[i]) == 0) {
            continue;
        }
        char sql[256] = { 0 };
        FMT2BUF(sql, "select name from {}.player where name ='{}'", globalDB, ESCA2UTF8(name[i]));
        if (!ExecuteSQL(sql))
        {
            LOG_ERROR("del lock player::query name failed,name:%s", name[i]);
            continue;
        }

        if (m_DBConnector.GetQueryRowNum() == 0)
        {
            LOG_WARN("not find locked player,player name:%s", name[i]);
            continue;
        }
        memset(sql, 0, _countof(sql));
        FMT2BUF(sql, "update {}.player set is_lock = {} where name = '{}';", globalDB, 0, ESCA2UTF8(name[i]));
        sqlEx += sql;
    }
    if (!ExecuteSQL(sqlEx.c_str())) return DBERR_EXESQL;

    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::DelLockRole(uint8_t num, char name[100][32], ProtoDB_DelLockRoleAck& data)
{
    SAFE_BEGIN_EX;
    std::string sqlEx = "";
    for (int i = 0; i < num; ++i)
    {
        if (name[i] == NULL || strlen(name[i]) == 0) {
            continue;
        }
        char sql[256] = { 0 };
        FMT2BUF(sql, "select name,id,pid from role where name ='{}'", ESCA2UTF8(name[i]));
        if (!ExecuteSQL(sql))
        {
            LOG_ERROR("del lock role::query name failed,name:%s", name[i]);
            continue;
        }

        if (m_DBConnector.GetQueryRowNum() == 0)
        {
            LOG_WARN("not find locked role,role name:%s", name[i]);
            continue;
        }

        m_DBConnector.GetQueryFieldData("id", data.guid[data.num]);
        m_DBConnector.GetQueryFieldData("pid", data.userID[data.num]);
        ++data.num;

        memset(sql, 0, _countof(sql));
        FMT2BUF(sql, "update role set is_lock = {} where name = '{}';", 0, ESCA2UTF8(name[i]));
        sqlEx += sql;
    }
    if (!ExecuteSQL(sqlEx.c_str())) return DBERR_EXESQL;

    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetProhibitChatInfo(std::vector<PROHIBIT_CHAT_DATA>& vec)
{
    SAFE_BEGIN_EX;
    char sql[256] = { 0 };
    FMT2BUF(sql, "select guid,time from prohibit_chat");
    if (!ExecuteSQL(sql)) return DBERR_EXESQL;
    int nRowNum = m_DBConnector.GetQueryRowNum();
    for (int i = 0; i < nRowNum; ++i) {
        try {
            PROHIBIT_CHAT_DATA info;
            m_DBConnector.GetQueryFieldData("guid", info.playerguid);
            m_DBConnector.GetQueryFieldData("time", info.time);
            vec.emplace_back(info);
        }
        catch (...) {
            LOG_ERROR("Exception occurred");
        }
        m_DBConnector.QueryNext();
    }
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::DelProhibitChatInfo(uint8_t num, const PROHIBIT_CHAT_DATA* data)
{
    SAFE_BEGIN_EX;
    std::string sql = "";
    for (int i = 0; i < num; ++i)
    {
        char buf[256] = { 0 };
        FMT2BUF(buf, "delete from prohibit_chat where guid = {};",data[i].playerguid);
        sql += buf;
    }

    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::AddProhibitChatInfo(uint8_t num, const PROHIBIT_CHAT_DATA* data)
{
    SAFE_BEGIN_EX;
    std::vector<PROHIBIT_CHAT_DATA>vec;
    GetProhibitChatInfo(vec);
    std::string sql = "";
    for (int i = 0; i < num; ++i)
    {
        auto _data = data[i];
        char buf[256] = { 0 };
        if (find_if(vec.begin(), vec.end(), [&_data](const PROHIBIT_CHAT_DATA&info) {
            if (info.playerguid == _data.playerguid)return true;
            return false;
            }) == vec.end())
        {
            FMT2BUF(buf, " insert into prohibit_chat(guid, time)value({}, {});", data[i].playerguid, data[i].time);
        }
        else
        {
            FMT2BUF(buf, " update prohibit_chat set time = {} where guid = {};", data[i].time, data[i].playerguid);
        }
        sql += buf;
    }

    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}
string CDBManager::JsonStyleEncode(const MAIL_INFO& data) 
{
    Json::Value json_info(Json::arrayValue);
    for (int j = 0; j < data.addition_item_num; ++j)
    {
        Json::Value item_info;
        item_info["id"] = data.mail_addition_item_info[j].item_id;
        item_info["name"] = data.mail_addition_item_info[j].item_name;
        item_info["guid"] = (to_string(data.mail_addition_item_info[j].item_guid));
        item_info["count"] = data.mail_addition_item_info[j].count;
        item_info["bind_status"] = data.mail_addition_item_info[j].bind_status;
        json_info[j] = item_info;

    }
    return json_info.toFastString();
    //string str;
    //for (int i = 0; i < data.addition_item_num; ++i) {
    //    str += data.mail_addition_item_info[i].item_name;
    //    str += "|";
    //    str += to_string(data.mail_addition_item_info[i].item_guid);
    //    str += "|";
    //    str += to_string(data.mail_addition_item_info[i].item_id);
    //    str += "|";
    //    str += to_string(data.mail_addition_item_info[i].bind_status);
    //    str += "|";
    //    str += to_string(data.mail_addition_item_info[i].count);
    //    str += ";";
    //}
    //return str;
}

string CDBManager::JsonStyleEncode(const MAIL_INFO& data, int)
{
    Json::Value json_info;
    for (int j = 0; j < data.currency_type_num; ++j)
    {
        json_info[to_string(data.mail_currency_info[j].type)] = to_string(data.mail_currency_info[j].num);
    }
    return json_info.toFastString();
}

string CDBManager::JsonStyleEncode(const ITEM_CFG_VAR& data)
{
    Json::Value json_info;

    json_info["color"] = data.color;
    json_info["icon"] = to_string(data.icon);
    json_info["quality"] = data.quality;
    json_info["subtype"] = data.subtype;
    return json_info.toFastString();
}


void CDBManager::JsonStyleDecode(const string& json_info, MAIL_INFO& data)
{
    //auto group = str_split(json_info, ";");
    //int i = 0;
    //for (auto& itemInfo : group) {
    //    auto feild = str_split(itemInfo, "|");
    //    strcpy_s(data.mail_addition_item_info[i].item_name, sizeof(data.mail_addition_item_info[i].item_name), feild[0]);
    //    try {
    //        data.mail_addition_item_info[i].item_guid = std::stoull(feild[1]);
    //        data.mail_addition_item_info[i].item_id = std::stoul(feild[2]);
    //        data.mail_addition_item_info[i].bind_status = std::stoul(feild[3]);
    //        data.mail_addition_item_info[i].count = std::stoul(feild[4]);
    //    }catch(...){
    //        --data.addition_item_num;
    //        continue;
    //    }
    //    ++i;
    //    if (i >= data.addition_item_num) return;
    //}
    if (json_info.empty())return;
    Json::Value jsondata((Json::arrayValue));
    Json::Reader reader;
    reader.parse(json_info, jsondata);
    for (int i = 0; i < data.addition_item_num; ++i) {
        data.mail_addition_item_info[i].item_id = jsondata[i]["id"].asUInt();
        strcpy_s(data.mail_addition_item_info[i].item_name, sizeof(data.mail_addition_item_info[i].item_name), jsondata[i]["name"].asCString());
        data.mail_addition_item_info[i].count = jsondata[i]["count"].asUInt();
        data.mail_addition_item_info[i].item_guid = _atoi64(jsondata[i]["guid"].asCString());
        data.mail_addition_item_info[i].bind_status = jsondata[i]["bind_status"].asUInt();
    }

}

void CDBManager::JsonStyleDecode(const string& json_info, MAIL_INFO& data, int)
{
    if (json_info.empty())return;
    Json::Value jsondata((Json::arrayValue));
    Json::Reader reader;
    reader.parse(json_info, jsondata);
    for (int key = role_ingot; key <= role_bind_gold; ++key)
    {
        if (!jsondata[to_string(key)].isNull())
        {
            data.mail_currency_info[data.currency_type_num].type = key;
            data.mail_currency_info[data.currency_type_num].num = std::stoll(jsondata[to_string(key)].asCString());
            ++data.currency_type_num;
        }
    }

}

void CDBManager::JsonStyleDecode(const string& info, ITEM_CFG_VAR& data)
{
    if (info.empty())return;
    Json::Value jsondata;
    Json::Reader reader;
    reader.parse(info, jsondata);
    data.color = jsondata["color"].asUInt();
    data.icon = _atoi64(jsondata["icon"].asCString());
    data.quality = jsondata["quality"].asUInt();
    data.subtype = jsondata["subtype"].asUInt();

}


void CDBManager::GetItemExtraData(uint64_t role_guid, uint64_t item_guid, ITEM_INFO& item, uint8_t state)
{
    // 自定义属性
    CUST_VAR_SP_LIST vars;
    GetItemCustVars(item_guid, vars, state);
    item.custom << vars;

    // 动态属性
    DYN_ATTRS attrs;
    GetItemDynAttrs(item_guid, attrs, state);
    item.custom << attrs;
}

void CDBManager::GetTradeItemExtraData(uint64_t role_guid, uint64_t item_guid, ITEM_INFO& item)
{
    // 自定义属性
    //std::string tableName = ConfigInfo::GetInstance()->m_sMySQLLogServDBName + '.' + TRADE_ITEM_CUST_VAR_TEMPLATE_TABLE_NAME;
    //std::string tName = ConfigInfo::GetInstance()->m_sMySQLLogServDBName + '.' + TRADE_ITEM_TEMPLATE_TABLE_NAME;
    std::string tableName = TRADE_ITEM_CUST_VAR_LOG_TEMPLATE_TABLE_NAME;
    std::string tName = TRADE_ITEM_LOG_TEMPLATE_TABLE_NAME;

    CUST_VAR_SP_LIST itemVars;
    GetItemCustVars(item_guid, itemVars, item_state_unaccalimed, tableName.c_str(), tName.c_str());
    item.custom << itemVars;

    // 动态属性
   // tableName = ConfigInfo::GetInstance()->m_sMySQLLogServDBName + '.' + TRADE_ITEM_DYN_ATTR_TEMPLATE_TABLE_NAME;
    tableName = TRADE_ITEM_DYN_ATTR_LOG_TEMPLATE_TABLE_NAME;

    DYN_ATTRS attrs;
    GetItemDynAttrs(item_guid, attrs, item_state_unaccalimed, tableName.c_str(), tName.c_str());
    item.custom << attrs;
}


int CDBManager::GetConstantCfg(CONSTANT_CFG_MAP& constantCfgMap)
{
    SAFE_BEGIN_EX;

    const char* sql = "select * from constant_cfg";
    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    auto num = m_DBConnector.GetQueryRowNum();

    for (auto i = 0; i < num; ++i) {

        CONSTANT_CFG var;

        m_DBConnector.GetQueryFieldData("name", var.name);
        m_DBConnector.GetQueryFieldData("value", var.value);

        constantCfgMap.emplace(var.name, std::move(var));

        m_DBConnector.QueryNext();
    }

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetWantedList(WANTED_SP_LIST &wantedList)
{
    SAFE_BEGIN_EX;

    const char *sql =
        "select w.*, r1.name as wanted_name, r2.name as wanted_by_name "
        "from wanted_list as w left join role as r1 on w.wanted = r1.id "
        "left join role as r2 on w.wanted_by = r2.id order by w.wanted, w.ptime";

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    uint64_t nWantedGUID = 0;
    uint64_t nPrevWantedGUID = 0;
    WANTED_SP spWanted;

    auto num = m_DBConnector.GetQueryRowNum();
    for (auto i = 0; i < num; ++i) {

        m_DBConnector.GetQueryFieldData("wanted", nWantedGUID);
        if (nWantedGUID != nPrevWantedGUID) {

            spWanted = std::make_shared<WANTED>();
            spWanted->guid = nWantedGUID;
            m_DBConnector.GetQueryFieldData("wanted_name", spWanted->name);

            wantedList.emplace_back(spWanted);
            nPrevWantedGUID = nWantedGUID;
        }

        auto spWantedBy = std::make_shared<WANTED_BY>();
        m_DBConnector.GetQueryFieldData("idx", spWantedBy->index);
        m_DBConnector.GetQueryFieldData("wanted_by", spWantedBy->guid);
        m_DBConnector.GetQueryFieldData("wanted_by_name", spWantedBy->name);
        m_DBConnector.GetQueryFieldData("desc", spWantedBy->desc);
        m_DBConnector.GetQueryFieldData("bounty", spWantedBy->bounty);
        m_DBConnector.GetQueryFieldData("ptime", spWantedBy->ptime);

        spWanted->wanted_by_list.emplace_back(std::move(spWantedBy));
        m_DBConnector.QueryNext();
    }

    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::AddToWantedList(uint64_t nWantedByGUID, const char *pWantedName, uint32_t nBounty, const char *pDesc,
    uint64_t nTime, uint64_t &nWantedGUID, uint32_t &nIndex)
{
    SAFE_BEGIN_EX;

    if (!pWantedName) return DBERR_PARAM;
    if (!pDesc) pDesc = "";

    char sql[300];

    FMT2BUF(sql, "select id from role where name = '{}'", ESCA2UTF8(pWantedName));

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    auto num = m_DBConnector.GetQueryRowNum();
    if (num == 0) return DBERR_EMPTY;

    m_DBConnector.GetQueryFieldData("id", nWantedGUID);

    FMT2BUF(sql, "insert into wanted_list (wanted, wanted_by, `desc`, bounty, ptime) values ({}, {}, '{}', {}, {})",
        nWantedGUID, nWantedByGUID, ESCA2UTF8(pDesc), nBounty, nTime);

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    if (!ExecuteSQL("select last_insert_id() as idx")) return DBERR_EXESQL;

    m_DBConnector.GetQueryFieldData("idx", nIndex);

    return DBERR_OK;

    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SaveGoodsIssueRecord(const GOODS_ISSUE_RECORD &record)
{
    SAFE_BEGIN_EX;
    char sql[200];
    FMT2BUF(sql, "insert into issue_record (order_no, role, type, goods, count, amount, issued, isPost) "
        "values ({}, {}, {}, {}, {}, {}, {}, {})",
        record.order_no, record.role_guid, record.pay_type, record.goods_id, record.goods_num,
        record.pay_amount, record.issued, record.isPost);
    if (!ExecuteSQL(sql)) {
        LOG_ERROR("SaveGoodsIssueRecord failed. "
            "order_no: %s, role_guid: %llu, pay_type: %u, goods_id: %u, goods_num: %u, pay_amount: %u, issued: %u, isPost: %u",
            record.order_no, record.role_guid, record.pay_type, record.goods_id, record.goods_num, record.pay_amount,
            record.issued, record.isPost);
        return DBERR_EXESQL;
    }
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetGoodsNotIssuedRecords(uint64_t roleGUID, GOODS_ISSUE_RECORD *records, uint8_t &num)
{
    SAFE_BEGIN_EX;
    if (!records) return DBERR_PARAM;

    char sql[200];
    FMT2BUF(sql, "select order_no, type, goods, count, amount, isPost from issue_record "
        "where role = {} and issued = 0 limit {}", roleGUID, num);
    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    num = static_cast<uint8_t>(m_DBConnector.GetQueryRowNum());
    for (uint8_t i = 0; i < num; ++i) {
        auto &record = records[i];
        record.role_guid = roleGUID;
        record.issued = 0;
        m_DBConnector.GetQueryFieldData("order_no", record.order_no, _countof(record.order_no), false);
        m_DBConnector.GetQueryFieldData("type", record.pay_type);
        m_DBConnector.GetQueryFieldData("goods", record.goods_id);
        m_DBConnector.GetQueryFieldData("count", record.goods_num);
        m_DBConnector.GetQueryFieldData("amount", record.pay_amount);
        m_DBConnector.GetQueryFieldData("isPost", record.isPost);

        m_DBConnector.QueryNext();
    }

    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetGoodsNotPostRecords(uint64_t roleGUID, GOODS_ISSUE_RECORD* records, uint8_t& num)
{
    SAFE_BEGIN_EX;
    if (!records) return DBERR_PARAM;

    char sql[200];
    FMT2BUF(sql, "select order_no, type, goods, count, amount, isPost from issue_record "
        "where role = {} and isPost = 0 limit {}", roleGUID, num);
    if (!ExecuteSQL(sql)) return DBERR_EXESQL;

    num = static_cast<uint8_t>(m_DBConnector.GetQueryRowNum());
    for (uint8_t i = 0; i < num; ++i) {
        auto& record = records[i];
        record.role_guid = roleGUID;
        record.issued = 0;
        m_DBConnector.GetQueryFieldData("order_no", record.order_no, _countof(record.order_no), false);
        m_DBConnector.GetQueryFieldData("type", record.pay_type);
        m_DBConnector.GetQueryFieldData("goods", record.goods_id);
        m_DBConnector.GetQueryFieldData("count", record.goods_num);
        m_DBConnector.GetQueryFieldData("amount", record.pay_amount);
        m_DBConnector.GetQueryFieldData("isPost", record.isPost);

        m_DBConnector.QueryNext();
    }

    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SetGoodsIssuedFlag(const char orderNoList[MAX_GOODS_ISSUE_RECORD][ORDER_NO_BUFLEN], uint8_t num)
{
    SAFE_BEGIN_EX;
    num = std::min<uint8_t>(num, MAX_GOODS_ISSUE_RECORD);
    std::string sql;
    char buf[100];
    for (uint8_t i = 0; i < num; ++i) {
        FMT2BUF(buf, "update issue_record set issued = 1 where order_no = '{}';", orderNoList[i]);
        sql += buf;
    }
    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SyncGoodsPostRecord(const char orderNoList[MAX_GOODS_POST_RECORD][ORDER_NO_BUFLEN], uint8_t num)
{
    SAFE_BEGIN_EX;
    num = std::min<uint8_t>(num, MAX_GOODS_POST_RECORD);
    std::string sql;
    char buf[100];
    for (uint8_t i = 0; i < num; ++i) {
        FMT2BUF(buf, "update issue_record set isPost =  1 where order_no = '{}';", orderNoList[i]);
        sql += buf;
    }
    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::GetRebateMoneyNotUsedRecord(REBATE_MONEY_RECORD& record)
{
    SAFE_BEGIN_EX;

    const auto& globalDB = ConfigInfo::GetInstance()->m_sMySQLGlobalServDBName;

    record.is_use = 1;
    std::string sql("");
    char buf[256] = { 0 };
    int num = 0;
    FMT2BUF(buf, "select name from {}.player where id = {};", globalDB, record.account_id);
    sql += buf;
    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;

    sql = ""; memset(buf, 0, _countof(buf));
    num = static_cast<uint8_t>(m_DBConnector.GetQueryRowNum());
    if (num == 0)  return DBERR_OK;

    m_DBConnector.GetQueryFieldData("name", record.account_name, _countof(record.account_name));
    FMT2BUF(buf, "select id, rebate_money from {}.en_rebate_money where is_use = 0 and account_id = '{}';", globalDB,  ESCA2UTF8(record.account_name));
    sql += buf;
    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;

    num = static_cast<uint8_t>(m_DBConnector.GetQueryRowNum());
    if (num == 0)  return DBERR_OK;

    record.is_use = 0;
    m_DBConnector.GetQueryFieldData("id", record.inc_id);
    m_DBConnector.GetQueryFieldData("rebate_money", record.rebate_money);

    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::SetRebateMoneyUsedFlag(REBATE_MONEY_RECORD& record)
{
    SAFE_BEGIN_EX;
    const auto& globalDB = ConfigInfo::GetInstance()->m_sMySQLGlobalServDBName;

    std::string sql("");
    char buf[256] = { 0 };
    FMT2BUF(buf, "update {}.en_rebate_money set is_use = 1 where id = {};", globalDB, record.inc_id);
    // FMT2BUF(buf, "update en_rebate_money set is_use = 1 where account_id = '{}';", ESCA2UTF8(record.account));
    sql += buf;
    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;

    return DBERR_OK;
    SAFE_END_EX(DBERR_EXCEPT);
}

int CDBManager::PlayerSetName(const std::string& name, uint64_t guid, uint64_t &userid, std::string& orgName)
{
    SAFE_BEGIN_EX;
    uint8_t isExist = 0;
    uint64_t tmpGuid = 0;

    char mysql[300];
    FMT2BUF(mysql, "select id, pid, name from role where id = {}", guid);
    if (!ExecuteSQL(mysql)) return ERR_CHANGE_NAME_NOT_EXIST;
    if (m_DBConnector.GetQueryRowNum())
    {
        m_DBConnector.GetQueryFieldData("pid", userid);
        m_DBConnector.GetQueryFieldData("name", orgName);
    }

    CheckIfRoleExistByName(name.c_str(), isExist, tmpGuid, true);
    if (isExist)return ERR_CHANGE_NAME_REPEAT;

    // 检测非法字符
    if (Tools::IsContainIllegalCharacters(name.c_str()))return ERR_CHANGE_NAME_ILLEGAL_CHARACTERS;

    std::string sqlStr("");
    memset(mysql, _countof(mysql), 0);
    FMT2BUF(mysql, "update role set name = '{}' where id = {};", ESCA2UTF8(name), guid);
    sqlStr += mysql; memset(mysql, 0, _countof(mysql));
    FMT2BUF(mysql, "insert into {}.unique_name(id, name) (select id, name from role where id = {}) on duplicate key update name = values(name);", ConfigInfo::GetInstance()->m_sMySQLGlobalServDBName.c_str(), guid);
    sqlStr += mysql; memset(mysql, 0, _countof(mysql));

    if (!ExecuteSQL(sqlStr.c_str())) return ERR_CHANGE_NAME_NOT_EXIST;

    // 更改数据库中包含角色名字的数据
    UpdateNameInfoToTable("auction_house", "ownerID", "ownerName", guid, name);
    UpdateNameInfoToTable("guild", "creator_id", "creator_name", guid, name);
    UpdateNameInfoToTable("guild", "chairman_id", "chairman_name", guid, name);
    UpdateNameInfoToTable("role_buff", "actor_id", "actor_name", guid, name);

    return DBERR_OK;
    SAFE_END_EX(DBERR_EXESQL);
}

int CDBManager::UpdateRoleUpdateTime(uint64_t guid)
{
    SAFE_BEGIN_EX;

    char mysql[1024] = { 0 };
    FMT2BUF(mysql, "update role set update_time = UNIX_TIMESTAMP() where id = {};", guid);
    if (!ExecuteSQL(mysql)) return DBERR_EXESQL;

    return DBERR_OK;
    SAFE_END_EX(DBERR_EXESQL);
}

void CDBManager::UpdateNameInfoToTable(const std::string& tableName, const std::string& guidFeild, const std::string nameFeild,
    uint64_t guid, const std::string& changeName)
{
    SAFE_BEGIN;
    char mysql[300];
    FMT2BUF(mysql, "select {} from {} where {}  = {} ", ESCA2UTF8(nameFeild), ESCA2UTF8(tableName), ESCA2UTF8(guidFeild), guid);
    if (!ExecuteSQL(mysql)) return ;
    if (!m_DBConnector.GetQueryRowNum())return;

    memset(mysql, 0, _countof(mysql));
    FMT2BUF(mysql, "update {} set {} = '{}' where {}  = {} ", ESCA2UTF8(tableName), ESCA2UTF8(nameFeild), ESCA2UTF8(changeName), ESCA2UTF8(guidFeild), guid);
    if (!ExecuteSQL(mysql)) return;

    SAFE_END
}

int CDBManager::GetItemTipInfo(uint64_t orgGuid, uint64_t ownerGuid, uint64_t itemGuid, ITEM_INFO& info)
{
    SAFE_BEGIN_EX;
    auto result = GetItemInfoByItemGuid(ownerGuid, itemGuid, info.base_info);
    if (result != ERR_OK) {
        return result;
    }

    CUST_VAR_SP_LIST custs;
    GetItemCustVars(itemGuid, custs);
    if (!custs.empty()) {
        info.custom << custs;
    }

    DYN_ATTRS attrs;
    GetItemDynAttrs(itemGuid, attrs);
    if (!attrs.empty()) {
        info.custom << attrs;
    }
    return ERR_OK;
    SAFE_END_EX(ERR_OK)
}

int CDBManager::AddTitle(uint64_t guid, const TITLE_INFO& info)
{
    SAFE_BEGIN_EX;
    char mysql[256];
    FMT2BUF(mysql, "insert into title (guid, id, isWear, addTime, lifeTime, timeLimit)"
        "values({},{},{},{},{},{})", guid, info.Id, info.isWear, info.addTime, info.lifeTime, info.timeLimit);
    if (!ExecuteSQL(mysql)) return DBERR_EXESQL;
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXESQL);
}

int CDBManager::DelTitle(uint64_t guid, uint16_t num, const uint32_t* id)
{
    SAFE_BEGIN_EX;
    std::string strSql = "";
    char mysql[256];
    for (int i = 0; i < num; ++i) {
        FMT2BUF(mysql, "delete from title where guid = {} and id = {};", guid, id[i]);
        strSql += mysql;
        memset(mysql, 0, _countof(mysql));
    }

    if (!ExecuteSQL(strSql.c_str())) return DBERR_EXESQL;
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXESQL);
}

int CDBManager::ChangeTitleWearType(uint64_t guid, uint32_t id, uint16_t wearType)
{
    SAFE_BEGIN_EX;
    char mysql[256];
    FMT2BUF(mysql, "update title set isWear = {} where guid = {} and id = {}", wearType, guid, id);
    if (!ExecuteSQL(mysql)) return DBERR_EXESQL;
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXESQL);
}

int CDBManager::SyncTitleInfo(uint64_t guid, int num, const TITLE_INFO* info)
{
    SAFE_BEGIN_EX;
    std::string sqlStr = "";
    char mysql[300];
    for (int i = 0; i < num; ++i) {
        FMT2BUF(mysql, "update title set lifeTime = {} where guid = {} and id = {};", info[i].lifeTime, guid, info[i].Id);
        sqlStr += mysql; memset(mysql, 0, _countof(mysql));
    }
    if (!ExecuteSQL(sqlStr.c_str())) return DBERR_EXESQL;
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXESQL);
}

int CDBManager::GetPlayerTitleInfo(uint64_t guid, std::vector<TITLE_INFO>& vec)
{
    SAFE_BEGIN_EX;
    char mysql[300];
    FMT2BUF(mysql, "select guid, id, isWear, addTime, lifeTime, timeLimit from title where guid = {}", guid);
    if (!ExecuteSQL(mysql)) return DBERR_EXESQL;

    auto num = static_cast<uint16_t>(m_DBConnector.GetQueryRowNum());
    for (uint8_t i = 0; i < num; ++i) {
        TITLE_INFO data;
        m_DBConnector.GetQueryFieldData("id", data.Id);
        m_DBConnector.GetQueryFieldData("isWear", data.isWear);
        m_DBConnector.GetQueryFieldData("addTime", data.addTime);
        m_DBConnector.GetQueryFieldData("lifeTime", data.lifeTime);
        m_DBConnector.GetQueryFieldData("timeLimit", data.timeLimit);

        m_DBConnector.QueryNext();
        vec.push_back(std::move(data));
    }

    return DBERR_OK;
    SAFE_END_EX(DBERR_EXESQL);
}

int CDBManager::UpdateDBTables(const uint8_t *data, uint32_t len)
{
    flatbuffers::Verifier verifier(data, len);

    const auto *updateTables = flatbuffers::GetRoot<UpdateTables>(data);
    if (!updateTables->Verify(verifier)) return DBERR_PARAM;

    const auto *tables = updateTables->tables();

    for (auto i = 0; i < tables->size(); ++i) {

        const auto *table = tables->Get(i);

        switch (table->tid()) {

        case table_role:
            UpdateRole(table->key(), table->elems());
            break;

        case table_role_location:
            break;

        case table_role_settings:
            break;
        }
    }

    return DBERR_OK;
}

int CDBManager::AddPlayerProhibitChat(uint64_t userID, int64_t stamp)
{
    SAFE_BEGIN_EX;
    char mysql[300];
    FMT2BUF(mysql, "update player set is_prohibit_chat = {} where id = {}",stamp, userID);
    if (!ExecuteSQL(mysql)) return DBERR_EXESQL;
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXESQL);
}

int CDBManager::DelPlayerProhibitChat(uint64_t userID)
{
    SAFE_BEGIN_EX;
    char mysql[300];
    FMT2BUF(mysql, "update player set is_prohibit_chat = {} where id = {}", 0, userID);
    if (!ExecuteSQL(mysql)) return DBERR_EXESQL;
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXESQL);
}

int CDBManager::SyncCustListInfo(uint8_t optType, uint8_t num, const CUST_LIST_INFO* data)
{
    SAFE_BEGIN_EX;
    std::string sql;
    char mysql[2048] = {0};
    if (optType == ProtoMS_SyncCustList::OptType::optType_add) {
        sql += "insert into cust_list (id, guid, type, value, desc_info,stamp) values";
        for (int i = 0; i < num; ++i) {
            FMT2BUF(mysql, "({},{},{},{},'{}',{}),", data[i].ranking, data[i].guid, data[i].type, data[i].value, ESCA2UTF8(data[i].desc), data[i].stamp);
            sql += mysql;
            memset(mysql, 0, _countof(mysql));
        }
        sql.erase(--sql.end());
    }
    else if (optType == ProtoMS_SyncCustList::OptType::optType_update) {
        for (int i = 0; i < num; ++i) {
            FMT2BUF(mysql, "update cust_list set guid = {}, value = {}, desc_info = '{}',stamp = {} where id = {};",
                data[i].guid, data[i].value, ESCA2UTF8(data[i].desc), data[i].stamp, data[i].ranking);
            sql += mysql;
            memset(mysql, 0, _countof(mysql));
        }
    }

    if (!ExecuteSQL(sql.c_str())) return DBERR_EXESQL;
    return DBERR_OK;
    SAFE_END_EX(DBERR_EXESQL);
}

int CDBManager::SyncPlayerGender(uint64_t guid, uint8_t gender)
{
    SAFE_BEGIN_EX;
    char mysql[200] = { 0 };
    FMT2BUF(mysql, "update role set gender = {} where id = {}", gender, guid);
    if (!ExecuteSQL(mysql)) return DBERR_EXESQL;
    SAFE_END_EX(DBERR_EXESQL);
}

int CDBManager::GetCustListInfo(std::vector<CUST_LIST_INFO>* vec)
{
    SAFE_BEGIN_EX;
    char mysql[200] = { 0 };
    FMT2BUF(mysql, "select id, guid, type, value, desc_info, stamp from cust_list");
    if (!ExecuteSQL(mysql)) return DBERR_EXESQL;

    auto num = static_cast<uint16_t>(m_DBConnector.GetQueryRowNum());
    for (uint8_t i = 0; i < num; ++i) {
        CUST_LIST_INFO data;
        m_DBConnector.GetQueryFieldData("id", data.ranking);
        m_DBConnector.GetQueryFieldData("guid", data.guid);
        m_DBConnector.GetQueryFieldData("type", data.type);
        m_DBConnector.GetQueryFieldData("value", data.value);
        m_DBConnector.GetQueryFieldData("desc_info", data.desc, _countof(data.desc), true);
        m_DBConnector.GetQueryFieldData("stamp", data.stamp);
        m_DBConnector.QueryNext();
        vec[data.type].push_back(std::move(data));
    }

    return DBERR_OK;
    SAFE_END_EX(DBERR_EXESQL);
}

int CDBManager::UpdateRole(const flatbuffers::Vector<uint8_t> *key,
                           const flatbuffers::Vector<flatbuffers::Offset<DBElem>> *elems)
{
    auto elemNum = elems->size();
    if (elemNum == 0) return DBERR_OK;

    char sql[1024] = {0};
    char *p = sql;
    int left = _countof(sql);

    auto len = sprintf_s(p, left, "update role set ");
    p += len; left -= len;

    bool first = true;
    int ret = 0;

    for (auto i = 0; i < elemNum; ++i) {

        const auto *elem = elems->Get(i);
        const auto *data = elem->data()->data();

        switch (elem->eid()) {

        case role_eid_head:
            ret = UpdateAppendElem(p, left, "head", elem_type_uint16, data, first);
            break;

        // TODO: other elems

        default:
            break;
        }

        if (ret != DBERR_OK) return ret;
    }

    auto roleGUID = *reinterpret_cast<const uint64_t *>(key->data());
    len = sprintf_s(p, left, " where id = %llu", roleGUID);
    if (len < 0) return DBERR_BUFSZ;

    if (!ExecuteSQL(sql)) return DBERR_EXESQL;
    return DBERR_OK;
}

int CDBManager::UpdateAppendElem(char *&buf, int &bufsz, const char *elemName, DBElemType elemType,
                                 const uint8_t *data, bool &first)
{
    int len = 0;
    if (!first) {
        len = sprintf_s(buf, bufsz, ", ");
        if (len < 0) return DBERR_BUFSZ;
        buf += len; bufsz -= len;
    }

    len = 0;
    switch (elemType) {

    case elem_type_string:
        len = sprintf_s(buf, bufsz, "%s = '%s'", elemName, reinterpret_cast<const char *>(data));
        break;

    case elem_type_uint8:
        len = sprintf_s(buf, bufsz, "%s = %u", elemName, *data);
        break;

    case elem_type_uint16:
        len = sprintf_s(buf, bufsz, "%s = %u", elemName, *reinterpret_cast<const uint16_t *>(data));
        break;

    case elem_type_uint32:
        len = sprintf_s(buf, bufsz, "%s = %u", elemName, *reinterpret_cast<const uint32_t *>(data));
        break;

    case elem_type_uint64:
        len = sprintf_s(buf, bufsz, "%s = %llu", elemName, *reinterpret_cast<const uint64_t *>(data));
        break;

    default:
        break;
    }

    if (len < 0) return DBERR_BUFSZ;
    buf += len; bufsz -= len;

    first = false;
    return DBERR_OK;
}
