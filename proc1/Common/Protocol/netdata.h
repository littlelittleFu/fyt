#ifndef CODER_H_INCLUDE
#define CODER_H_INCLUDE

#include <string>

typedef std::string blob;

class CNetData
{
public:
	CNetData();
	virtual ~CNetData();

	void Prepare(char *pNetData, int iSize);
	void Reset();

	char * GetData();
	int GetDataLen();

	int AddByte(unsigned char byByte);
	int DelByte(unsigned char &byByte);

	int AddChar(char chChar);
	int DelChar(char &chChar);

	int AddWord(unsigned short wWord);
	int DelWord(unsigned short &wWord);

	int AddShort(short shShort);
	int DelShort(short &shShort);

	int AddDword(unsigned int dwDword);
	int DelDword(unsigned int &dwDword);

	int AddInt(int iInt);
	int DelInt(int &iInt);

	int AddInt64(int64_t iInt64);
	int DelInt64(int64_t&iInt64);

	int AddQword(uint64_t qwQword);
	int DelQword(uint64_t &qwQword);

	int AddString(const char *pszString, int iSize);
	int AddFixString(const char* pszString, int iSize);
	int DelString(char *pszOut, int iSize);

    int AddString(const std::string &str) { return AddString(str.c_str(), str.length() + 1); }
	int DelString(std::string& str);

	//int AddBlob(const blob & Blob);
	//int DelBlob(blob & Blob);
	int AddBlob(const char *pszData, int iSize);
	int DelBlob(char *pszOut, int iSize);

	int AddIntArray(const int * pszData,int iSize);
	int DelIntArray(int* pszOut, int iSize);

	int Strnlen(const char *pszString, int iSize);

public:
	char * m_pBuf;
	int m_iSize;
	int m_iPos;
};

#endif
