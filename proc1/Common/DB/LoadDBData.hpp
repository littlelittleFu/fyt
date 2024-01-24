#ifndef CXX_LOADDBDATA_H
#define CXX_LOADDBDATA_H

#include "MD5.h"
#include "ILogHelper.h"
#include "IFileHelper.h"

const int MD5OFFSET = 16;

string GetReadCSVPath(const string& _DBDir, const string& _CSVName)
{
    string _DBXMLPath = _DBDir;
    _DBXMLPath += "/";
    _DBXMLPath += _CSVName;
    _DBXMLPath += ".csv";
	if (!IFileHelper::GetInstance()->IsFileExist(_DBXMLPath.c_str())) {
		_DBXMLPath = IFileHelper::GetInstance()->GetCurWorkPath();
		_DBXMLPath += "res/db/";
		_DBXMLPath += _CSVName;
		_DBXMLPath += ".csv";
	}
    return _DBXMLPath;
}


string GetReadXMLPath(const string& _DBDir, const string& _XMLName)
{
	string _DBXMLPath = _DBDir;
	_DBXMLPath += "/";
	_DBXMLPath += _XMLName;
	_DBXMLPath += ".xml";
	if(!IFileHelper::GetInstance()->IsFileExist(_DBXMLPath.c_str())){
		_DBXMLPath = IFileHelper::GetInstance()->GetCurWorkPath();
		_DBXMLPath += "res/db/";
		_DBXMLPath += _XMLName;
		_DBXMLPath += ".xml";
	}
	return _DBXMLPath;
}

template<class Table, class TableConfig>
class LoadXMLData
{
public:
	LoadXMLData(const string& _DBDir, const string& _XMLName, const string& _CacheKey, bool& _LoadSuccess)
	{
		// CDB文件是否存在
		m_CachedDBName = _XMLName + ".cdb";
		string _FilePath = IFileHelper::GetInstance()->GetCurWorkPath() + "res/db/" + m_CachedDBName;
		if(!IFileHelper::GetInstance()->IsFileExist(_FilePath.c_str())){
			LOG_WARN("[DB] : XML cache %s not exist , Load Xml %s", _FilePath.c_str(), _XMLName.c_str());
			_LoadSuccess = false;
			return;
		}

		int _RecordNum = 0;
		uint32_t _CDBFileSize = 0;
		unsigned char* _pCDBFileData = IFileHelper::GetInstance()->LoadBinary(_FilePath, _CDBFileSize);
		if (!_pCDBFileData) {
			_LoadSuccess = false;
			return;
		}

		if(_CDBFileSize < static_cast<ssize_t>(16 + sizeof(_RecordNum))){
			LOG_WARN("[DB] : XML cache %s length unmatch , Load Xml %s", _FilePath.c_str(), _XMLName.c_str());
			_LoadSuccess = false;
			SAFE_RELEASE_ARRAY(_pCDBFileData);
			return;
		}

		_FilePath = _DBDir + _XMLName + ".xml";
		if(!IFileHelper::GetInstance()->IsFileExist(_FilePath.c_str())){
			_FilePath = IFileHelper::GetInstance()->GetCurWorkPath();
			_FilePath += "res/db/" + _XMLName + ".xml";
		}
		
		unsigned int _XMLFileSize = 0;
		unsigned char* _pXMLFileData = nullptr;
		_pXMLFileData = IFileHelper::GetInstance()->LoadBinary(_FilePath, _XMLFileSize);
		if (!_pXMLFileData) {
			_LoadSuccess = false;
			SAFE_RELEASE_ARRAY(_pCDBFileData);
			return;
		}

		MD5 _MD5Process;
		unsigned char _MD5Data[16];
		_MD5Process.MDData((char*)_pXMLFileData, _XMLFileSize, _MD5Data);
		if(memcmp(_pCDBFileData, _MD5Data, 16) != 0){
			LOG_WARN("[DB] : XML cache %s md5 unmatch , Load Xml %s", _FilePath.c_str(), _XMLName.c_str());
			_LoadSuccess = false;
			SAFE_RELEASE_ARRAY(_pCDBFileData);
			SAFE_RELEASE_ARRAY(_pXMLFileData);
			return;
		}
		
		_RecordNum = *((int*)(_pCDBFileData + MD5OFFSET));
		if(_CDBFileSize != static_cast<ssize_t>(MD5OFFSET + sizeof(_RecordNum) + _RecordNum * sizeof(Table))){
			_LoadSuccess = false;
			SAFE_RELEASE_ARRAY(_pCDBFileData);
			SAFE_RELEASE_ARRAY(_pXMLFileData);
			return;
		}

		TableConfig::DestoryInstance();
		TableConfig::CreateInstance();

		// 填充数据
		for(int i = 0; i < _RecordNum; i++){
			Table* temp = reinterpret_cast<Table*>(_pCDBFileData + MD5OFFSET + sizeof(_RecordNum) + i * sizeof(Table));
			Table* tableData = new Table;
			*tableData = *temp;
			TableConfig::Instance()->FillMapping(tableData);
		}
		LOG_NORMAL("[DB] : XML = %s, Load cache %s success", _XMLName.c_str(), _FilePath.c_str());
		_LoadSuccess = true;

		SAFE_RELEASE_ARRAY(_pCDBFileData);
		SAFE_RELEASE_ARRAY(_pXMLFileData);
	}

	void OnDBLoadError(char* _DBName)
	{
		LOG_ERROR("DB加载失败: %s", _DBName);
	}

	bool LoadDataFromXML(const string& _DBDir, const string& _XMLName, bool _NeedStopWhenErr)
	{
		TableConfig::DestoryInstance();
		TableConfig::CreateInstance();
		bool _LoadSucess = false;

		string _FilePath = _DBDir + _XMLName + ".xml";
		if (!IFileHelper::GetInstance()->IsFileExist(_FilePath.c_str())){
			_FilePath = IFileHelper::GetInstance()->GetCurWorkPath();
			_FilePath += "res/db/" + _XMLName + ".xml";
		}

		_LoadSucess = TableConfig::Instance()->Load(_FilePath);
		if(!_LoadSucess){
			if(_NeedStopWhenErr){
				OnDBLoadError((char*)_XMLName.c_str());
			}
		}
		else{
			uint32_t _XMLFileSize = 0;
			unsigned char* _pXMLFileData = nullptr;
			_pXMLFileData = IFileHelper::GetInstance()->LoadBinary(_FilePath, _XMLFileSize);
			if(_pXMLFileData && _XMLFileSize > 0){
				MD5 _MD5Process;
				unsigned char _MD5Data[16];
				_MD5Process.MDData((char*)_pXMLFileData, _XMLFileSize, _MD5Data);

				string _DirPath = IFileHelper::GetInstance()->GetCurWorkPath() + "res/db/";
				if(!IFileHelper::GetInstance()->IsDirExist(_DirPath.c_str())){
					if(IFileHelper::GetInstance()->CreateDir(_DirPath.c_str())){
						LOG_ERROR("DB table directory do not exist and failed to create it");
						SAFE_RELEASE_ARRAY(_pXMLFileData);
						return false;
					}
				}

				string _FilePath = _DirPath + m_CachedDBName;
				FILE* _pFile = fopen(_FilePath.c_str(), "wb");
				if(_pFile != NULL){ 
					vector<Table*>& _TableData = TableConfig::Instance()->GetData();
					int _RecordNum = _TableData.size();
					size_t _SaveSize = MD5OFFSET + sizeof(_RecordNum) + _RecordNum * sizeof(Table);
					char* _BuffData = new char[_SaveSize];
					if(_BuffData){
						memcpy(_BuffData, _MD5Data, 16);
						memcpy(_BuffData + 16, &_RecordNum, sizeof(_RecordNum));
						for(int _Idx = 0; _Idx < _RecordNum; _Idx++){
							memcpy(_BuffData + 16 + sizeof(_RecordNum) + _Idx * sizeof(Table), _TableData[_Idx], sizeof(Table));
						}

						fwrite(_BuffData, _SaveSize, 1, _pFile);
						LOG_NORMAL("[DB] : 更新cache,  %s ", _FilePath.c_str());
						delete[]_BuffData;
					}
					fclose(_pFile);
				}
				else{
					LOG_ERROR("Failed to save cached DB file %s\n", _FilePath.c_str());
					SAFE_RELEASE_ARRAY(_pXMLFileData);
					return false;
				}

				SAFE_RELEASE_ARRAY(_pXMLFileData);
			}
			
			LOG_NORMAL("[DB]: Load %s Success", _FilePath.c_str());
		}
		return _LoadSucess;
	}

private:
	string m_CachedDBName;
};



template<class Table, class TableConfig>
class LoadCSVData
{
public:
    LoadCSVData(const string& _DBDir, const string& _CSVName, const string& _CacheKey, bool& _LoadSuccess)
    {
	try
	{
        // CDB文件是否存在
        m_CachedDBName = _CSVName + ".cdb";
        string _FilePath = IFileHelper::GetInstance()->GetCurWorkPath() + "res/db/" + m_CachedDBName;
		if (!IFileHelper::GetInstance()->IsFileExist(_FilePath.c_str())) {
            LOG_NORMAL("[DB] : CSV cache %s not exist , Load csv %s", _FilePath.c_str(), _CSVName.c_str());
            _LoadSuccess = false;
            return;
        }

        int _RecordNum = 0;
        unsigned int _CDBFileSize = 0;
        unsigned char* _pCDBFileData = IFileHelper::GetInstance()->LoadBinary(_FilePath,  _CDBFileSize);
        if(_CDBFileSize < static_cast<ssize_t>(16 + sizeof(_RecordNum))){
            LOG_NORMAL("[DB] : CSV cache %s length unmatch , Load csv %s", _FilePath.c_str(), _CSVName.c_str());
            _LoadSuccess = false;
            return;
        }

        _FilePath = _DBDir + _CSVName + ".csv";
		if (!IFileHelper::GetInstance()->IsDirExist(_FilePath.c_str())) {
            _FilePath = IFileHelper::GetInstance()->GetCurWorkPath();
            _FilePath += "res/db/" + _CSVName + ".csv";
        }

        unsigned int _CSVFileSize = 0;
		unsigned char* _pCSVFileData = IFileHelper::GetInstance()->LoadBinary(_FilePath, _CSVFileSize);
        MD5 _MD5Process;
        unsigned char _MD5Data[16];
        _MD5Process.MDData((char*)_pCSVFileData, _CSVFileSize, _MD5Data);
        if(memcmp(_pCDBFileData, _MD5Data, 16) != 0){
            LOG_NORMAL("[DB] : CSV cache %s md5 unmatch , Load csv %s", _FilePath.c_str(), _CSVName.c_str());
            _LoadSuccess = false;
            return;
        }

        _RecordNum = *((int*)(_pCDBFileData + MD5OFFSET));
        if(_CDBFileSize != static_cast<ssize_t>(MD5OFFSET + sizeof(_RecordNum) + _RecordNum * sizeof(Table))){
            _LoadSuccess = false;
            return;
        }

        TableConfig::DestoryInstance();
        TableConfig::CreateInstance();

        // 填充数据
        for(int i = 0; i < _RecordNum; i++){
            Table* temp = reinterpret_cast<Table*>(_pCDBFileData + MD5OFFSET + sizeof(_RecordNum) + i * sizeof(Table));
            Table* tableData = new Table;
            *tableData = *temp;
			TableConfig::Instance()->PushData(tableData);
            TableConfig::Instance()->FillMapping(tableData);
        }
        LOG_NORMAL("[DB] : CSV = %s, Load cache %s success", _CSVName.c_str(), _FilePath.c_str());
        _LoadSuccess = true;
	}
	catch (...)
	{
		TableConfig::DestoryInstance();
		_LoadSuccess = false;
	}
    }

    void OnDBLoadError(char* _DBName)
    {
        char _Message[256] = { 0 };
        sprintf(_Message, "DB加载失败: %s", _DBName);
    }

    bool LoadDataFromCSV(const string& _DBDir, const string& _CSVName, bool _NeedStopWhenErr, bool createDBFile = true)
    {
        TableConfig::DestoryInstance();
        TableConfig::CreateInstance();
        bool _LoadSucess = false;

		try
		{
        string _FilePath = _DBDir + _CSVName + ".csv";
        if (!
			(_FilePath.c_str())){
            _FilePath = IFileHelper::GetInstance()->GetCurWorkPath();
            _FilePath += "res/db/" + _CSVName + ".csv";
        }

        _LoadSucess = TableConfig::Instance()->Load(_FilePath);
        if(!_LoadSucess){
            if(_NeedStopWhenErr){
                OnDBLoadError((char*)_CSVName.c_str());
            }
        }
        else if (createDBFile){
            unsigned int _CSVFileSize = 0;
            unsigned char* _pCSVFileData = IFileHelper::GetInstance()->LoadBinary(_FilePath,  _CSVFileSize);
            if(_CSVFileSize > 0){
                MD5 _MD5Process;
                unsigned char _MD5Data[16];
                _MD5Process.MDData((char*)_pCSVFileData, _CSVFileSize, _MD5Data);

             

				string _DirPath = IFileHelper::GetInstance()->GetCurWorkPath() + "res/db/";
				if (!IFileHelper::GetInstance()->IsDirExist(_DirPath.c_str())) {
					if (IFileHelper::GetInstance()->CreateDir(_DirPath.c_str())) {
						LOG_ERROR("DB table directory do not exist and failed to create it");
						SAFE_RELEASE_ARRAY(_pCSVFileData);
						return false;
					}
				}

                string _FilePath = _DirPath + m_CachedDBName;
                FILE* _pFile = fopen(_FilePath.c_str(), "wb");
                if(_pFile != NULL){ 
                    vector<Table*>& _TableData = TableConfig::Instance()->GetData();
                    int _RecordNum = _TableData.size();
                    size_t _SaveSize = MD5OFFSET + sizeof(_RecordNum) + _RecordNum * sizeof(Table);
                    char* _BuffData = new char[_SaveSize];
                    if(_BuffData){
                        memcpy(_BuffData, _MD5Data, 16);
                        memcpy(_BuffData + 16, &_RecordNum, sizeof(_RecordNum));
                        for(int _Idx = 0; _Idx < _RecordNum; _Idx++){
                            memcpy(_BuffData + 16 + sizeof(_RecordNum) + _Idx * sizeof(Table), _TableData[_Idx], sizeof(Table));
                        }

                        fwrite(_BuffData, _SaveSize, 1, _pFile);
                        LOG_NORMAL(u8"[DB] : 更新cache,  %s ", _FilePath.c_str());
                        delete[]_BuffData;
                    }
                    fclose(_pFile);
                }
                else{
                    LOG_NORMAL("Failed to save cached DB file %s\n", _FilePath.c_str());
                    return false;
                }
            }

            LOG_NORMAL("[DB]: Load %s Success", _FilePath.c_str());
        }
		}
		catch (...)
		{
			TableConfig::DestoryInstance();
			_LoadSucess = false;
		}
        return _LoadSucess;
    }

private:
    string m_CachedDBName;
};


#endif