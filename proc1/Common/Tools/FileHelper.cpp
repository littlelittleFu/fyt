#include "stdafx.h"
#include "FileHelper.h"
#include "StringHelper.h"

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <direct.h> 
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <glob.h>
#endif

#include <stdint.h>
#include <string>
#include <fstream>

#define MAX_PATH_LEN 256

#ifdef _WIN32
#define ACCESS(fileName,accessMode) _access(fileName,accessMode)
#define MKDIR(path) _mkdir(path)
#else
#define ACCESS(fileName,accessMode) access(fileName,accessMode)
#define MKDIR(path) mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif

FileHelper::FileHelper() : m_CurPath("")
{

}

FileHelper::~FileHelper()
{

}

std::string FileHelper::GetCurWorkPath()
{
	if (m_CurPath == "") {
#ifdef _WIN32
		char _Path[256] = { 0 };
		GetModuleFileNameA(NULL, _Path, 256);
		char *p = strrchr(_Path, '\\');
		if (p) *(p + 1) = 0;
		m_CurPath = _Path;
#else
        char path[PATH_MAX] = {0};
        readlink("/proc/self/exe", path, _countof(path));
        char *p = strrchr(path, '/');
        if (p) *(p + 1) = 0;
        m_CurPath = path;
#endif
	}
	return m_CurPath;
}

bool FileHelper::IsDirExist(const std::string& _Dir)
{
	if (_Dir.empty()) {
		return false;
	}

#ifdef _WIN32
	auto _Attr = GetFileAttributesA(_Dir.c_str());
	if ((INVALID_FILE_ATTRIBUTES != _Attr) && (_Attr & FILE_ATTRIBUTE_DIRECTORY)) {
		return true;
	}
#else
    struct stat st;
    if (stat(_Dir.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
        return true;
    }
#endif

	return false;
}

bool FileHelper::IsFileExist(const std::string& _File)
{
	if (_File.empty()) {
		return false;
	}

#ifdef _WIN32
	auto _Attr = GetFileAttributesA(_File.c_str());
	if ((INVALID_FILE_ATTRIBUTES != _Attr) && !(_Attr & FILE_ATTRIBUTE_DIRECTORY)) {
		return true;
	}
#else
    struct stat st;
    if (stat(_File.c_str(), &st) == 0 && S_ISREG(st.st_mode)) {
        return true;
    }
#endif

	return false;
}

int FileHelper::CreateDir(const std::string& _Dir)
{
	uint32_t dirPathLen = _Dir.length();
	if (dirPathLen > MAX_PATH_LEN) {
		return -1;
	}

	char tmpDirPath[MAX_PATH_LEN] = { 0 };
	for (uint32_t i = 0; i < dirPathLen; ++i) {
		tmpDirPath[i] = _Dir[i];
		if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/') {
			if (ACCESS(tmpDirPath, 0) != 0) {
				int32_t ret = MKDIR(tmpDirPath);
				if (ret != 0) {
					return ret;
				}
			}
		}
	}

	return 0;
}

bool FileHelper::IsAbsolutePath(const std::string& _Path) const
{
#ifdef _WIN32
	if ((_Path.length() > 2
		&& ((_Path[0] >= 'a' && _Path[0] <= 'z') || (_Path[0] >= 'A' && _Path[0] <= 'Z'))
		&& _Path[1] == ':') || (_Path[0] == '/' && _Path[1] == '/')) {
		return true;
	}
#else
    if (!_Path.empty() && _Path[0] == '/') return true;
#endif
	return false;
}

std::string FileHelper::FullPathForFileName(const std::string &_FileName)
{
	if (_FileName.empty()) {
		return "";
	}

	if (IsAbsolutePath(_FileName)) {
		return _FileName;
	}

	auto _Iter = m_FullPathCache.find(_FileName);
	if (_Iter != m_FullPathCache.end()) {
		return _Iter->second;
	}

	std::string _FullPath;

	for (const auto& _Itr : m_SearchPath) {
		_FullPath = _Itr + _FileName;
		if (IsFileExist(_FullPath)) {
			m_FullPathCache.insert(std::make_pair(_FileName, _FullPath));
			return _FullPath;
		}
	}

	return "";
}

void FileHelper::AddSearchPath(const std::string& _Path, const bool _Front)
{
	std::string _Prefix;
	if (!IsAbsolutePath(_Path)) {
		_Prefix = GetCurWorkPath();
	}

	std::string _FullPath = _Prefix + _Path;
	if (!_FullPath.empty() 
		&& _FullPath[_FullPath.length() - 1] != '/'
		&& _FullPath[_FullPath.length() - 1] != '\\') {
#ifdef _WIN32
		_FullPath += "\\";
#else
        _FullPath += "/";
#endif
	}
	if (_Front) {
		m_SearchPath.insert(m_SearchPath.begin(), _FullPath);
	}
	else {
		m_SearchPath.push_back(_FullPath);
	}
}

bool FileHelper::LoadText(const std::string& _FileName, std::string& ret)
{
	if (_FileName.empty()) {
		return false;
	}

	std::string _FullPath = FullPathForFileName(_FileName);
	if (_FullPath.empty()) {
		return false;
	}

	FILE* _pFile = fopen(_FullPath.c_str(), "rt");
	if (!_pFile) {
		return false;
	}

	fseek(_pFile, 0, SEEK_END);
	size_t _Size = ftell(_pFile);
	fseek(_pFile, 0, SEEK_SET);

	if (0 == _Size) {
		return true;
	}

	char* _Buff = new char[_Size + 1];
	size_t _ReadSize = fread(_Buff, sizeof(char), _Size, _pFile);
	fclose(_pFile);

	_Buff[_Size] = '\0';
	if (_ReadSize < _Size) {
		_Buff[_ReadSize] = '\0';
	}

	ret = _Buff;
	SAFE_RELEASE_ARRAY(_Buff);

	return true;
}

unsigned char* FileHelper::LoadBinary(const std::string& _FileName, uint32_t& len)
{
	if (_FileName.empty()) {
		return nullptr;
	}

	std::string _FullPath = FullPathForFileName(_FileName);
	if (_FullPath.empty()) {
		return nullptr;
	}

	FILE* _pFile = fopen(_FullPath.c_str(), "rb");
	if (!_pFile) {
		return nullptr;
	}

	fseek(_pFile, 0, SEEK_END);
	size_t _Size = ftell(_pFile);
	fseek(_pFile, 0, SEEK_SET);

	unsigned char* _Buff = new unsigned char[_Size + 1];
	size_t _ReadSize = fread(_Buff, sizeof(char), _Size, _pFile);
	fclose(_pFile);

	_Buff[_Size] = '\0';
	if (_ReadSize < _Size) {
		_Buff[_ReadSize] = '\0';
	}

	len = _ReadSize;

	return _Buff;
}

bool FileHelper::LoadData(const std::string& _FileName, bool _Binary)
{
	m_Content = "";

	if (_FileName.empty()) {
		return false;
	}

	std::string _FullPath = FullPathForFileName(_FileName);
	if (_FullPath.empty()) {
		return false;
	}

	std::string _Mode = _Binary ? "rb" : "rt";
	FILE* _pFile = fopen(_FullPath.c_str(), _Mode.c_str());
	if (!_pFile) {
		return false;
	}

	fseek(_pFile, 0, SEEK_END);
	size_t _Size = ftell(_pFile);
	fseek(_pFile, 0, SEEK_SET);

	if (0 == _Size) {
		return true;
	}

	char* _Buff = _Binary? new char[_Size] : new char[_Size + 1];
	size_t _ReadSize = fread(_Buff, sizeof(char), _Size, _pFile);
	fclose(_pFile);

	if (!_Binary) {
		_Buff[_Size] = '\0';
		if (_ReadSize < _Size) {
			_Buff[_ReadSize] = '\0';
		}
	}

	m_Content = std::string((const char*)_Buff);
	delete _Buff;
	
	return true;
}

std::string FileHelper::GetConfigFilePath()
{
	return GetCurWorkPath() + "config.ini";
}

bool FileHelper::GetFileAllLines(const char* filePath, std::list<std::string>& retList)
{
	if (nullptr == filePath) return false;

	std::ifstream input_file(filePath);
	if (!input_file.is_open()) return false;

	retList.clear();
	std::string line;
	while (std::getline(input_file, line)) {
		retList.push_back(line);
	}
	input_file.close();
	return true;
}

std::list<std::string> FileHelper::GetAllFilesInDir(const char *dir, const char *pattern)
{
    std::list<std::string> files;

    if (!dir) return files;

    std::string dirPath = dir;
    if (dirPath.empty()) return files;

#ifdef _WIN32
    const auto &c = dirPath.back();
    if (c != '/' && c != '\\') dirPath += '\\';

    std::string findPattern = dirPath;

    if (!pattern) pattern = "*";
    findPattern += pattern;

    WIN32_FIND_DATAA findData;
    HANDLE findHandle = FindFirstFileA(findPattern.c_str(), &findData);
    if (findHandle == INVALID_HANDLE_VALUE) return files;

    do {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
        string filePath = dirPath + findData.cFileName;
        files.emplace_back(std::move(filePath));

    } while (FindNextFileA(findHandle, &findData));

    FindClose(findHandle);
#else
    const auto &c = dirPath.back();
    if (c != '/') dirPath += '/';

    std::string findPattern = dirPath;

    if (!pattern) pattern = "*";
    findPattern += pattern;

    glob_t result;
    glob(findPattern.c_str(), GLOB_TILDE | GLOB_MARK, nullptr, &result);

    for (size_t i = 0; i < result.gl_pathc; ++i) {
        std::string file = result.gl_pathv[i];
        if (file.back() == '/') continue;       // Ìø¹ýÄ¿Â¼
        files.emplace_back(std::move(file));
    }

    globfree(&result);
#endif

    return files;
}

std::list<std::string> FileHelper::GetAllFilesInDir(const std::string &dir, const char *pattern)
{
    return GetAllFilesInDir(dir.c_str(), pattern);
}

std::list<std::string> FileHelper::GetAllFilesInDirRecursive(const char *dir, const char *pattern)
{
    auto allPath = GetAllFoldersInDir(dir, true);
    allPath.emplace(allPath.begin(), dir);

    std::list<std::string> files;
    for (const auto &path : allPath) {
        files.splice(files.end(), GetAllFilesInDir(path, pattern));
    }

    return files;
}

std::list<std::string> FileHelper::GetAllFilesInDirRecursive(const std::string &dir, const char *pattern)
{
    return GetAllFilesInDirRecursive(dir.c_str(), pattern);
}

std::list<std::string> FileHelper::GetAllFoldersInDir(const char *dir, bool recursive)
{
    std::list<std::string> folders;
    if (!dir || strlen(dir) == 0) return folders;

    std::string dirPath = dir;

#ifdef _WIN32
    const auto &c = dirPath.back();
    if (c != '/' && c != '\\') dirPath += '\\';

    std::string findPattern = dirPath + '*';

    WIN32_FIND_DATAA findData;
    HANDLE findHandle = FindFirstFileA(findPattern.c_str(), &findData);
    if (findHandle == INVALID_HANDLE_VALUE) return folders;

    do {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) continue;

        if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0) continue;

        string folderPath = dirPath + findData.cFileName;
        folders.emplace_back(std::move(folderPath));

        if (!recursive) continue;

        auto subFolders = GetAllFoldersInDir(folders.back().c_str(), true);
        folders.splice(folders.end(), subFolders);

    } while (FindNextFileA(findHandle, &findData));

    FindClose(findHandle);
#else
    if (dirPath.back() != '/') dirPath += '/';

    std::string findPattern = dirPath + '*';

    glob_t result;
    glob(findPattern.c_str(), GLOB_TILDE | GLOB_MARK, nullptr, &result);

    for (size_t i = 0; i < result.gl_pathc; ++i) {
        std::string folder = result.gl_pathv[i];
        if (folder.back() != '/') continue;

        folders.emplace_back(std::move(folder));

        if (!recursive) continue;

        auto subFolders = GetAllFoldersInDir(folders.back().c_str(), true);
        folders.splice(folders.end(), subFolders);
    }

    globfree(&result);
#endif
    return folders;
}
