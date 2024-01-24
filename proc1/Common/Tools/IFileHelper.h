#pragma once
#include <string>
#include <list>

class IFileHelper
{
public:
	static void SetInstance(IFileHelper* inst) { m_instance = inst; };
	static IFileHelper* GetInstance() { return m_instance; };

	virtual std::string GetCurWorkPath() = 0;
	virtual bool IsDirExist(const std::string& _Dir) = 0;
	virtual bool IsFileExist(const std::string& _File) = 0;
	virtual int CreateDir(const std::string& _Dir) = 0;
	virtual bool IsAbsolutePath(const std::string& _Path) const = 0;
	virtual bool LoadText(const std::string& _FileName, std::string& ret) = 0;
	virtual unsigned char* LoadBinary(const std::string& _FileName, uint32_t& len) = 0;
	virtual void ClearContent() = 0;
	virtual std::string FullPathForFileName(const std::string& _FileName) = 0;
	//get map file path according the map name
	virtual std::string GetConfigFilePath() = 0;
	virtual bool GetFileAllLines(const char* filePath, std::list<std::string>& retList) = 0;
    virtual std::list<std::string> GetAllFilesInDir(const char *dir, const char *pattern) = 0;
    virtual std::list<std::string> GetAllFilesInDir(const std::string &dir, const char *pattern) = 0;
    virtual std::list<std::string> GetAllFilesInDirRecursive(const char *dir, const char *pattern) = 0;
    virtual std::list<std::string> GetAllFilesInDirRecursive(const std::string &dir, const char *pattern) = 0;
    virtual std::list<std::string> GetAllFoldersInDir(const char *dir, bool recursive) = 0;

private:
	static IFileHelper* m_instance;
};
