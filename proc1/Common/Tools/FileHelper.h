#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "IFileHelper.h"

class FileHelper : public IFileHelper
{
public:
	FileHelper();
	~FileHelper();

public:
	virtual std::string GetCurWorkPath() override;
	virtual bool IsDirExist(const std::string& _Dir) override;
	virtual bool IsFileExist(const std::string& _File) override;
	virtual int CreateDir(const std::string& _Dir) override;
	virtual bool IsAbsolutePath(const std::string& _Path) const override;
	virtual bool LoadText(const std::string& _FileName, std::string& ret)override;
	virtual unsigned char* LoadBinary(const std::string& _FileName, uint32_t& len)override;
	virtual void ClearContent() override { m_Content = ""; }
	virtual std::string FullPathForFileName(const std::string &_FileName) override;
	virtual std::string GetConfigFilePath() override;
    virtual bool GetFileAllLines(const char* filePath, std::list<std::string>& retList) override;
	void AddSearchPath(const std::string& _Path, const bool _Front = false);
	const std::unordered_map<std::string, std::string>& GetFullPathCache() const { return m_FullPathCache; }
    virtual std::list<std::string> GetAllFilesInDir(const char *dir, const char *pattern) override;
    virtual std::list<std::string> GetAllFilesInDir(const std::string &dir, const char *pattern) override;
    virtual std::list<std::string> GetAllFilesInDirRecursive(const char *dir, const char *pattern) override;
    virtual std::list<std::string> GetAllFilesInDirRecursive(const std::string &dir, const char *pattern) override;
    virtual std::list<std::string> GetAllFoldersInDir(const char *dir, bool recursive) override;

protected:
	bool LoadData(const std::string& _FileName, bool _Binary = false);
private:
	std::string m_CurPath;
	std::vector<std::string> m_SearchPath;
	mutable std::unordered_map<std::string, std::string> m_FullPathCache;

	std::string m_Content;
};
