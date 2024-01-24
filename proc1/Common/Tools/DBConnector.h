#pragma once 

#include <map> 
#include <string>
#include <stdint.h>
#include "mysql.h"
#include <string>
#include <vector>
using namespace std;


const	int		valueLen = 256;
const	int		arrayLen = 32;

struct tagTableInfo 
{ 
	char columName[arrayLen];
	char valueType[arrayLen];
	char valueContent[valueLen];

	tagTableInfo(){memset(this,0,sizeof(*this));}
	~tagTableInfo(){memset(this,0,sizeof(*this));}
};

class DBConnector
{ 
public:
		DBConnector();
		~DBConnector(); 
		 
        int                     ExecQuery(const char *sql);
        int                     ExecQuery(const char *sql, uint64_t &rows);

        void                    GetQueryFieldData(const char *cpszFieldName, uint8_t &rn8Data);
        void                    GetQueryFieldData(const char* cpszFieldName, uint16_t& rn16Data);

		void					GetQueryFieldData(const char *cpszFieldName, int &rn32Data);
		void					GetQueryFieldData(const char *cpszFieldName, unsigned int &rn32Data);
		 
		void					GetQueryFieldData(const char *cpszFieldName, int64_t &rn64Data);
		void					GetQueryFieldData(const char *cpszFieldName, uint64_t &run64Data); 

		void					GetQueryFieldData(const char *cpszFieldName, char *  fileData, uint32_t buffSize, bool convert2GBK = true);
		void					GetQueryFieldData(const char *cpszFieldName, string&  fileData, bool convert2GBK = true);

		void					GetQueryFieldData(const char *cpszFieldName, std::vector<uint8_t> &binData);

		void					GetQueryFields();   
		void					QueryNext();   
		void					CloseQuery();  
public:
		bool					ConnDb(const char *cpszDBHostIP,  const char	 *cpszUserName, const char *cpszUserUserPwd, const char *cpszDBName, int  nPort = 3306); 
 
		void					Clear();
		bool					ReConn();
		void					ClearRes();


		int						GetErrorCode()				{	return mysql_errno( mysql_ );}
		const char*				GetErrorStr()				{	return mysql_error( mysql_ ); }

		int						GetQueryRowNum()			{	return m_TotalRows_;	}
		int						GetQueryFieldNum()			{	return m_TotalFields_;	}

		MYSQL *					GetMySql()					{	return mysql_;}
		MYSQL_RES	*			GetMyRes()					{	return myres_;}

		std::string				GetDbIP()					{ return m_DbIp_; }
		int						GetDbPort()					{ return nPort_; }

        bool                    IsSelectSQL(const char *sql);

private:
	MYSQL * mysql_; 
	MYSQL_RES	*myres_;
	int		m_TotalRows_;
	int       m_TotalFields_;
	int		m_curRowIdx_;
	std::vector<std::string> m_FieldsName;

	char m_DbIp_[arrayLen];
	char m_DbUser_[arrayLen];
	char m_DbPwd_[arrayLen];
	char m_DbName_[arrayLen];  
	int  nPort_; 
	bool		m_connState_;

	std::map<string, std::string>  m_FieldsValue;// columValue
};
 
//}
