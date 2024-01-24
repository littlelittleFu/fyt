#include "stdafx.h"
#include "netdata.h"

CNetData::CNetData() {
    m_pBuf = nullptr;
    m_iSize = 0;
    m_iPos = 0;
}

CNetData::~CNetData() {}

void CNetData::Prepare(char *pNetData, int iSize) {
    m_pBuf = pNetData;
    m_iSize = iSize;
    m_iPos = 0;
}

void CNetData::Reset() { m_iPos = 0; }

char *CNetData::GetData() { return m_pBuf; }

int CNetData::GetDataLen() { return m_iPos; }

int CNetData::AddByte(unsigned char byByte) {
    if (m_iPos + (int)sizeof(byByte) > m_iSize)
        return -1;

    *(unsigned char *)(m_pBuf + m_iPos) = byByte;
    m_iPos += sizeof(byByte);

    return m_iPos;
}

int CNetData::DelByte(unsigned char &byByte) {
    if (m_iPos + (int)sizeof(byByte) > m_iSize)
        return -1;

    byByte = *(unsigned char *)(m_pBuf + m_iPos);
    m_iPos += sizeof(byByte);

    return m_iPos;
}

int CNetData::AddChar(char chChar) {
    if (m_iPos + (int)sizeof(chChar) > m_iSize)
        return -1;

    *(char *)(m_pBuf + m_iPos) = chChar;
    m_iPos += sizeof(chChar);

    return m_iPos;
}

int CNetData::DelChar(char &chChar) {
    if (m_iPos + (int)sizeof(chChar) > m_iSize)
        return -1;

    chChar = *(char *)(m_pBuf + m_iPos);
    m_iPos += sizeof(chChar);

    return m_iPos;
}

int CNetData::AddWord(unsigned short wWord) {
    if (m_iPos + (int)sizeof(wWord) > m_iSize)
        return -1;

    //*(unsigned short*)(m_pBuf + m_iPos) = htons(wWord);
    *(unsigned short *)(m_pBuf + m_iPos) = wWord;
    m_iPos += sizeof(wWord);

    return m_iPos;
}

int CNetData::DelWord(unsigned short &wWord) {
    if (m_iPos + (int)sizeof(wWord) > m_iSize)
        return -1;

    // wWord = ntohs(*(unsigned short*)(m_pBuf + m_iPos));
    wWord = *(unsigned short *)(m_pBuf + m_iPos);
    m_iPos += sizeof(wWord);

    return m_iPos;
}

int CNetData::AddShort(short shShort) {
    if (m_iPos + (int)sizeof(shShort) > m_iSize)
        return -1;

    //*(short*)(m_pBuf + m_iPos) = htons(shShort);
    *(short *)(m_pBuf + m_iPos) = shShort;
    m_iPos += sizeof(shShort);

    return m_iPos;
}

int CNetData::DelShort(short &shShort) {
    if (m_iPos + (int)sizeof(shShort) > m_iSize)
        return -1;

    // shShort = ntohs(*(short*)(m_pBuf + m_iPos));
    shShort = *(short *)(m_pBuf + m_iPos);
    m_iPos += sizeof(shShort);

    return m_iPos;
}

int CNetData::AddDword(unsigned int dwDword) {
    if (m_iPos + (int)sizeof(dwDword) > m_iSize)
        return -1;

    //*(unsigned int*)(m_pBuf + m_iPos) = htonl(dwDword);
    *(unsigned int *)(m_pBuf + m_iPos) = dwDword;
    m_iPos += sizeof(dwDword);

    return m_iPos;
}

int CNetData::DelDword(unsigned int &dwDword) {
    if (m_iPos + (int)sizeof(dwDword) > m_iSize)
        return -1;

    // dwDword = ntohl(*(unsigned int*)(m_pBuf + m_iPos));
    dwDword = *(unsigned int *)(m_pBuf + m_iPos);
    m_iPos += sizeof(dwDword);

    return m_iPos;
}

int CNetData::AddInt(int iInt) {
    if (m_iPos + (int)sizeof(iInt) > m_iSize)
        return -1;

    //*(int*)(m_pBuf + m_iPos) = htonl(iInt);
    *(int *)(m_pBuf + m_iPos) = iInt;
    m_iPos += sizeof(iInt);

    return m_iPos;
}

int CNetData::DelInt(int &iInt) {
    if (m_iPos + (int)sizeof(iInt) > m_iSize)
        return -1;

    // iInt = ntohl(*(int*)(m_pBuf + m_iPos));
    iInt = *(int *)(m_pBuf + m_iPos);
    m_iPos += sizeof(iInt);

    return m_iPos;
}

int CNetData::AddInt64(int64_t iInt64) {
    if (m_iPos + (int)sizeof(iInt64) > m_iSize)
        return -1;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    memcpy((char *)(m_pBuf + m_iPos), &iInt64, sizeof(int64_t));
#else
    *(INT64 *)(m_pBuf + m_iPos) = iInt64;
#endif
    m_iPos += sizeof(iInt64);

    return m_iPos;
}

int CNetData::DelInt64(int64_t&iInt64) {
    if (m_iPos + (int)sizeof(iInt64) > m_iSize)
        return -1;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    memcpy(&iInt64, (char *)(m_pBuf + m_iPos), sizeof(int64_t));
#else
    iInt64 = *(INT64 *)(m_pBuf + m_iPos);
#endif
    m_iPos += sizeof(iInt64);

    return m_iPos;
}

int CNetData::AddQword(uint64_t qwQword) {
    if (m_iPos + (int)sizeof(qwQword) > m_iSize)
        return -1;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    memcpy((char *)(m_pBuf + m_iPos), &qwQword, sizeof(uint64_t));
#else
    *(uint64_t *)(m_pBuf + m_iPos) = qwQword;
#endif
    m_iPos += sizeof(qwQword);

    return m_iPos;
}

int CNetData::DelQword(uint64_t &qwQword) {
    if (m_iPos + (int)sizeof(qwQword) > m_iSize)
        return -1;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    memcpy(&qwQword, (char *)(m_pBuf + m_iPos), sizeof(uint64_t));
#else
    qwQword = *(uint64_t *)(m_pBuf + m_iPos);
#endif
    m_iPos += sizeof(qwQword);

    return m_iPos;
}

int CNetData::AddString(const char *pszString, int iSize) {
    int iLen = Strnlen(pszString, iSize - 1);

    if (m_iPos + (int)sizeof(unsigned int) + iLen > m_iSize)
        return -1;

    if (-1 == AddDword((unsigned int)iLen))
        return -1;

    memcpy(m_pBuf + m_iPos, pszString, iLen);
    m_iPos += iLen;

    return m_iPos;
}

int CNetData::AddFixString(const char* pszString, int iSize) {
    int iLen = iSize;

    if (m_iPos + (int)sizeof(unsigned int) + iLen > m_iSize)
        return -1;

    if (-1 == AddDword((unsigned int)iLen))
        return -1;

    memcpy(m_pBuf + m_iPos, pszString, iLen);
    m_iPos += iLen;

    return m_iPos;
}

int CNetData::DelString(char *pszOut, int iSize) {
     unsigned int wLen = 0;
    if (-1 == DelDword(wLen))
        return -1;

    if (m_iPos + (int)wLen > m_iSize)
        return -1;

    if (int(wLen + 1) > iSize)
        return -1;

    memcpy(pszOut, m_pBuf + m_iPos, wLen);
    pszOut[wLen] = '\0';
    m_iPos += wLen;

    return m_iPos;
}

int CNetData::DelString(std::string& pszOut)
{
    unsigned int len = 0;
    if (DelDword(len) == -1) return -1;
    if (m_iPos + len > m_iSize) return -1;
    pszOut.assign(m_pBuf + m_iPos, len);
    m_iPos += len;
    return m_iPos;
}

int CNetData::AddBlob(const char *pszData, int iSize) {
    if (m_iPos + iSize > m_iSize)
        return -1;

    memcpy(m_pBuf + m_iPos, pszData, iSize);
    m_pBuf[m_iPos + iSize] = '\0';

    m_iPos += iSize;

    return m_iPos;
}

int CNetData::DelBlob(char *pszOut, int iSize) {
    if (m_iPos + iSize > m_iSize)
        return -1;

    memcpy(pszOut, m_pBuf + m_iPos, iSize);
    pszOut[iSize] = '\0';
    m_iPos += iSize;

    return m_iPos;
}

int CNetData::AddIntArray(const int* pszData, int iSize)
{
    if (m_iPos + iSize > m_iSize)
        return -1;
    for (size_t i = 0; i < iSize; i++) {
        m_iPos += CNetData::AddInt(pszData[i]);
    }
    return m_iPos;
}

int CNetData::DelIntArray(int* pszOut, int iSize)
{
    if (m_iPos + iSize > m_iSize)
        return -1;

    memcpy(pszOut, m_pBuf + m_iPos, iSize);
    m_iPos += iSize;

    return m_iPos;
}


// int CNetData::AddBlob( const blob & Blob )
//{
//    int iLen = (int)Blob.size();
//
//    if (m_iPos + (int)sizeof(int) + iLen > m_iSize)
//        return -1;
//
//    if (-1 == AddInt(iLen))
//        return -1;
//
//    memcpy(m_pBuf + m_iPos, Blob.c_str(), iLen);
//    m_iPos += iLen;
//
//    return m_iPos;
//}
//
// int CNetData::DelBlob( blob & Blob )
//{
//    int iLen = 0;
//    if (-1 == DelInt(iLen))
//        return -1;
//
//    if (m_iPos + iLen > m_iSize)
//        return -1;
//
//    Blob.clear();
//    Blob.append(m_pBuf+m_iPos, iLen);
//    m_iPos += iLen;
//
//    return m_iPos;
//}

int CNetData::Strnlen(const char *pszString, int iSize) {
    int i;
    const char *ptr = pszString;

    for (i = 0; i < iSize; i++) {
        if ('\0' == *ptr) {
            return i;
        }
        ptr++;
    }

    return iSize;
}
