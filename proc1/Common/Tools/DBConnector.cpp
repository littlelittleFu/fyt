#include "stdafx.h"
#include "DBConnector.h" 
#include "ILogHelper.h"


//namespace MysqlDWrapper
//{
	DBConnector::DBConnector():mysql_(NULL),myres_(NULL),/*fileds_(NULL),*/m_TotalRows_(0),m_TotalFields_(0),m_curRowIdx_(0),m_connState_(false)
{ 
}
DBConnector::~DBConnector()
{
    ClearRes();
	Clear();
}

bool DBConnector::ConnDb(const char *cpszDBHostIP,  const char	 *cpszUserName, const char *cpszUserUserPwd, const char *cpszDBName, int  nPort ){
	Clear();
	mysql_ = mysql_init( NULL ); 
	if( mysql_ == NULL )
	{ 
		LOG_ERROR("mysql failed! %s",GetErrorStr());
		return false;
	} 
	char value = 1;
	mysql_options(mysql_, MYSQL_OPT_RECONNECT, &value);
	mysql_options(mysql_, MYSQL_SET_CHARSET_NAME, "utf8");

	auto bFlag = mysql_real_connect(mysql_,cpszDBHostIP,cpszUserName,cpszUserUserPwd,cpszDBName,nPort,NULL,CLIENT_MULTI_STATEMENTS);
	if (!bFlag){
	
		LOG_ERROR("connect mysql failed! %s",GetErrorStr());
		return false;
	} 
	strcpy_s(m_DbIp_, _countof(m_DbIp_), cpszDBHostIP); 
    strcpy_s(m_DbUser_, _countof(m_DbUser_), cpszUserName);
    strcpy_s(m_DbPwd_, _countof(m_DbPwd_), cpszUserUserPwd); 
    strcpy_s(m_DbName_, _countof(m_DbName_), cpszDBName);

	nPort_ = nPort;
	m_connState_ = true;

	return true;
}

bool DBConnector::IsSelectSQL(const char *sql)
{
    if (!sql) return false;

    while (*sql == ' ' || *sql == '\t') ++sql;

    return _strnicmp(sql, "select", 6) == 0;
}

int DBConnector::ExecQuery(const char *sql)
{
    if (!sql || !sql[0]) return -1;

	if (mysql_ == NULL)
	{
		if(!ReConn())
		{ 
			return -1;
		}
	}   
	ClearRes();

	int  nRet =  mysql_real_query(mysql_, sql, strlen(sql));  
	if (nRet != 0)
	{
		return -1;
	}

	if (IsSelectSQL(sql))
	{   
		myres_ = mysql_store_result(mysql_);
		m_TotalFields_ = mysql_num_fields(myres_); 

		m_TotalRows_ = static_cast<int>(mysql_affected_rows(mysql_)); 

		GetQueryFields();  
	}  
	
	return nRet;
}

int DBConnector::ExecQuery(const char *sql, uint64_t &rows)
{
    if (!sql || !sql[0]) return -1;

	if (mysql_ == NULL)
	{
		if (!ReConn())
		{
			return -1;
		}
	}
	ClearRes();

	int  nRet = mysql_real_query(mysql_, sql, strlen(sql));
	if (nRet != 0)
	{
		return -1;
	}

	if (IsSelectSQL(sql))
	{
		myres_ = mysql_store_result(mysql_);
		m_TotalFields_ = mysql_num_fields(myres_);

		m_TotalRows_ = static_cast<int>(mysql_affected_rows(mysql_));
		GetQueryFields();
	}
	else
	{
		m_TotalRows_ = static_cast<int>(mysql_affected_rows(mysql_));
	}
	rows = m_TotalRows_;
	return nRet;
}

void	DBConnector::ClearRes()
{ 
	bool ifNeedQueryNext = (myres_ != nullptr);
	if (myres_){
		mysql_free_result(myres_);  
	}

	if (ifNeedQueryNext){
		while (mysql_next_result(mysql_) == 0){
			myres_ = mysql_store_result(mysql_);
			if (myres_){
				mysql_free_result(myres_); 
			}
		}
	}
	else{
		do 
		{
			myres_ = mysql_store_result(mysql_);
			if (myres_){
				mysql_free_result(myres_); 
			}
		} while (mysql_next_result(mysql_) == 0); 
	}

	myres_ = NULL;
}

void	DBConnector::Clear()
{ 
	m_connState_ = false;
	if (mysql_)
	{
		mysql_close(mysql_); 
		mysql_ = NULL; 
	} 

	if (myres_)
	{
		myres_ = NULL;
	}
} 

void DBConnector::GetQueryFieldData(const char* cpszFieldName, uint8_t& rn8Data)
{
    auto iter = m_FieldsValue.find(cpszFieldName);
    if (iter != m_FieldsValue.end()) {
        rn8Data = (uint8_t)atoi(iter->second.data());
    }
}

void DBConnector::GetQueryFieldData(const char* cpszFieldName, uint16_t& rn16Data)
{
    auto iter = m_FieldsValue.find(cpszFieldName);
    if (iter != m_FieldsValue.end()) {
        rn16Data = (uint16_t)atoi(iter->second.data());
    }
}

void	DBConnector::GetQueryFieldData(const char *cpszFieldName, int &rn32Data)
{ 
	auto iter = m_FieldsValue.find(cpszFieldName);
	if (iter != m_FieldsValue.end()){
		rn32Data = (int)atoi(iter->second.data()); 
	}
}
void	DBConnector::GetQueryFieldData(const char *cpszFieldName, unsigned int &rn32Data)
{
	auto iter = m_FieldsValue.find(cpszFieldName);
	if (iter != m_FieldsValue.end()){
		rn32Data = std::stoul(iter->second.data()); 
	}
}

void	DBConnector::GetQueryFieldData(const char *cpszFieldName, int64_t &rn64Data)
{
	auto iter = m_FieldsValue.find(cpszFieldName);
	if (iter != m_FieldsValue.end()){
		rn64Data = _atoi64(iter->second.data()); 
	}
}

void	DBConnector::GetQueryFieldData(const char *cpszFieldName, uint64_t &run64Data)
{
	auto iter = m_FieldsValue.find(cpszFieldName);
	if (iter != m_FieldsValue.end()){
		run64Data = strtoull(iter->second.data(), nullptr, 0);
	}
}

void	DBConnector::GetQueryFieldData(const char *cpszFieldName, char *  fileData, uint32_t buffSize, bool convert2GBK)
{
	auto iter = m_FieldsValue.find(cpszFieldName);
	if (iter != m_FieldsValue.end()){
		strcpy_s(fileData, buffSize, convert2GBK ? utf8_to_gbk(iter->second).c_str() : iter->second.data());
	}
}

void DBConnector::GetQueryFieldData(const char *cpszFieldName, string& fileData, bool convert2GBK){
	auto iter = m_FieldsValue.find(cpszFieldName);
	if (iter != m_FieldsValue.end()){
		fileData =  convert2GBK ? utf8_to_gbk(iter->second).c_str() : iter->second.data();
	}
}

void DBConnector::GetQueryFieldData(const char *cpszFieldName, std::vector<uint8_t> &binData)
{
	binData.clear();

	auto it = m_FieldsValue.find(cpszFieldName);
	if (it == m_FieldsValue.end()) return;

	binData.assign(it->second.begin(), it->second.end());
}

void	DBConnector::GetQueryFields()
{
	m_FieldsName.clear();
	m_FieldsValue.clear();

	MYSQL_ROW curRow = mysql_fetch_row(myres_);
	if (!curRow) return;

	auto *lengths = mysql_fetch_lengths(myres_);
	if (!lengths) return;

	int i = 0;
	MYSQL_FIELD *field = NULL;

	while (field = mysql_fetch_field(myres_))
	{   
		auto tempRes = curRow[i];
		auto length = lengths[i];

		if (tempRes){
			string fieldName(field->name, field->name_length);
			m_FieldsValue[fieldName] = std::string(tempRes, length);
			m_FieldsName.push_back(fieldName);
		}

		++i;
	}
}

void	DBConnector::QueryNext()
{ 
	m_FieldsValue.clear();

	MYSQL_ROW curRow = mysql_fetch_row(myres_);
	if (!curRow) return;

	auto *lengths = mysql_fetch_lengths(myres_);
	if (!lengths) return;

	int size = m_FieldsName.size();
	for (int i = 0; i < size; ++i){
		auto tempRes = curRow[i];
		auto length = lengths[i];

		if (tempRes){
			m_FieldsValue[m_FieldsName[i]] = std::string(tempRes, length);
		}
	}
}
 
void	DBConnector::CloseQuery()
{ 
	m_curRowIdx_ = 0;
	m_FieldsValue.clear();
}


 
bool	DBConnector::ReConn()
{
	mysql_ = mysql_init(NULL); 
	if( mysql_ == NULL )
	{ 
		return false;
	}  
	char value = 1;
	mysql_options(mysql_, MYSQL_OPT_RECONNECT, &value);
	mysql_options(mysql_, MYSQL_SET_CHARSET_NAME, "utf8");  

	return mysql_real_connect(mysql_,m_DbIp_,m_DbUser_,m_DbPwd_,m_DbName_,nPort_,NULL,CLIENT_MULTI_STATEMENTS); 
}
