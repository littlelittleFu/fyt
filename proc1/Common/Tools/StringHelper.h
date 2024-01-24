#pragma once

#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdint>

#include <iconv.h>


using std::string;
using std::stringstream;

inline bool isChar(char c1, char c2) { return c1 == c2; }

inline string& remove_char(string& str, char c) {
    str.erase(std::remove_if(str.begin(), str.end(), std::bind2nd(std::function<bool(char, char)>(isChar), c)), str.end()); // 去掉字符
    return str;
}

inline string& remove_space(string& t) { return remove_char(t, ' '); }

inline string& trans_tolower(string& t) {
    std::transform(t.begin(), t.end(), t.begin(), ::tolower);
    return t;
}

inline string& trans_toupper(string& t) {
    std::transform(t.begin(), t.end(), t.begin(), ::toupper);
    return t;
}

inline string & trim_left(string &str, const char *pTrimedChars = " \t") {
    auto pos = str.find_first_not_of(pTrimedChars);
    (pos != std::string::npos) ? str.erase(0, pos) : str.erase(0);
    return str;
}

inline string & trim_right(string &str, const char *pTrimedChars = " \t") {
    auto pos = str.find_last_not_of(pTrimedChars);
    (pos != std::string::npos) ? str.erase(pos + 1) : str.erase(0);
    return str;
}

inline string & trim(string &str, const char *pTrimedChars = " \t") {
    trim_right(str, pTrimedChars);
    trim_left(str, pTrimedChars);
    return str;
}

const char * stristr(const char *haystack, const char *needle);

#ifdef __linux__

inline int strcpy_s(char *dst, size_t dstsz, const char *src)
{
    if (!dst || !src || dstsz == 0) return -1;

    int ret = 0;
    auto len = strlen(src);

    if (dstsz <= len)
    {
        len = dstsz - 1;
        ret = 1;
    }

    strncpy(dst, src, len);
    dst[len] = 0;

    return ret;
}

template <size_t size>
int strcpy_s(char (&dst)[size], const char *src)
{
    if (!dst || size == 0 || !src) return -1;

    int ret = 0;
    auto len = strlen(src);

    if (size <= len)
    {
        len = size - 1;
        ret = 1;
    }

    strncpy(dst, src, len);
    dst[len] = 0;

    return ret;
}

template <size_t size>
int strncpy_s(char (&dst)[size], const char *src, size_t count)
{
    if (!dst || size == 0 || !src) return -1;
    auto len = strlen(src);
    len = std::min<size_t>({len, size - 1, count});
    strncpy(dst, src, len);
    dst[len] = 0;
    return len == count ? 0 : 1;
}

#endif

inline int strcpy_s(char *dst, size_t dstsz, const std::string &src)
{
    return strcpy_s(dst, dstsz, src.c_str());
}

template <size_t size>
int strcpy_s(char (&dst)[size], const std::string &src)
{
    return strcpy_s(dst, src.c_str());
}

inline uint64_t stoull_s(const std::string &s)
{
    try { return std::stoull(s); }
    catch (...) { return 0; }
}

inline std::string hex2str(const unsigned char *data, unsigned len, bool lower = true)
{
    static const char a[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    static const char b[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    const char *t = lower ? a : b;

    std::string s(2 * len, 0);
    char *p = (char *)s.data();

    for (int i = 0; i < len; ++i) {

        *p++ = t[data[i] >> 4];
        *p++ = t[data[i] & 0x0f];
    }

    return s;
}


template <typename T> struct IsAllToStrSupport {
    enum { Support = true };
};
template <> struct IsAllToStrSupport<uint8_t> {
    enum { Support = false };
};
template <> struct IsAllToStrSupport<int8_t> {
    enum { Support = false };
};
template <> struct IsAllToStrSupport<uint16_t> {
    enum { Support = false };
};
template <> struct IsAllToStrSupport<int16_t> {
    enum { Support = false };
};

template <class T> inline string AllToStr(T t, bool bHex = false) {
    string strTemp;
    stringstream convt;
    if (bHex) {
        convt << std::hex;
    }
    if (IsAllToStrSupport<T>::Support) {
        convt << t;
    }
    else {
        convt << (int)t;
    }
    convt >> strTemp;
    convt.clear();
    return strTemp;
}

template <class T> inline T StrToAll(string t) {
    T r;
    stringstream convt;
    convt << t;
    convt >> r;
    convt.clear();
    return r;
}

// 重载
inline string AllToStr(string t) { return t; }

inline string AllToStr(bool t) {
    if (t == true)
        return "true";
    else
        return "false";
}

template <typename T> string AllToStr(T* t) {
    string strTemp;
    stringstream convt;

    convt << (unsigned long)t;

    convt >> strTemp;
    convt.clear();
    return strTemp;
}

template <> inline int StrToAll(string t) {
    int r;
    stringstream convt;
    if (find_if(t.begin(), t.end(), std::bind2nd(std::ptr_fun(isChar), 'x')) != t.end() ||
        find_if(t.begin(), t.end(), std::bind2nd(std::ptr_fun(isChar), 'X')) != t.end())
        convt << std::hex;

    convt << t;
    convt >> r;
    convt.clear();
    return r;
}

template <> inline string StrToAll(string t) { return t; }


template <> inline bool StrToAll(string _String)
{
    _String.erase(std::remove_if(_String.begin(),
        _String.end(),
        std::bind2nd(std::ptr_fun(isChar), ' ')),
        _String.end());
    std::transform(_String.begin(), _String.end(), _String.begin(), ::tolower);                                      // 转小写

    if (_String == string("true")) {
        return true;
    }
    else {
        return false;
    }
}

inline string ExtractFileName(string strPathName) {
    auto _Index = strPathName.find_last_of("/\\");
    if (_Index != string::npos) {
        return strPathName.substr(_Index + 1);
    }
    else {
        return string();
    }
}

inline void ReplaceAll(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty()) return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

inline std::string SQLEscape(std::string str)
{
    ReplaceAll(str, "'", "''");
    return str;
}

inline std::vector<std::string> str_split(std::string str, const char *delims)
{
    std::vector<std::string> tokens;

    char *context = nullptr;
    auto *token = strtok_s((char *)str.data(), delims, &context);

    while (token) {
        tokens.emplace_back(token);
        token = strtok_s(nullptr, delims, &context);
    }

    return tokens;
}

inline std::string utf8_to_gbk(const std::string &str)
{
    auto inleft = str.length();
    auto outleft = inleft + 1;

    std::string gbkstr(outleft, '\0');

    auto *inbuf = (char *)str.data();
    auto *outbuf = (char *)gbkstr.data();

    auto cd = iconv_open("GBK", "UTF-8");
    iconv(cd, &inbuf, &inleft, &outbuf, &outleft);
    iconv_close(cd);

    gbkstr.erase(gbkstr.size() - outleft, outleft);
    return gbkstr;
}

inline std::string utf8_to_gbk(const char *str)
{
    if (!str || !str[0]) return "";

    auto inleft = strlen(str);
    auto outleft = inleft + 1;

    std::string gbkstr(outleft, '\0');

    auto *inbuf = (char *)str;
    auto *outbuf = (char *)gbkstr.data();

    auto cd = iconv_open("GBK", "UTF-8");
    iconv(cd, &inbuf, &inleft, &outbuf, &outleft);
    iconv_close(cd);

    gbkstr.erase(gbkstr.size() - outleft, outleft);
    return gbkstr;
}

inline std::string gbk_to_utf8(const std::string &str)
{
    auto inleft = str.length();
    auto outleft = inleft * 2 + 1;

    std::string utf8str(outleft, '\0');

    auto *inbuf = (char *)str.data();
    auto *outbuf = (char *)utf8str.data();

    auto cd = iconv_open("UTF-8", "GBK");
    iconv(cd, &inbuf, &inleft, &outbuf, &outleft);
    iconv_close(cd);

    utf8str.erase(utf8str.size() - outleft, outleft);
    return utf8str;
}

inline std::string gbk_to_utf8(const char *str)
{
    if (!str || !str[0]) return "";

    auto inleft = strlen(str);
    auto outleft = inleft * 2 + 1;

    std::string utf8str(outleft, '\0');

    auto *inbuf = (char *)str;
    auto *outbuf = (char *)utf8str.data();

    auto cd = iconv_open("UTF-8", "GBK");
    iconv(cd, &inbuf, &inleft, &outbuf, &outleft);
    iconv_close(cd);

    utf8str.erase(utf8str.size() - outleft, outleft);
    return utf8str;
}

#define ESCA2UTF8(str) gbk_to_utf8(SQLEscape(str))
#define ESCA2UTF8P(str) gbk_to_utf8(SQLEscape(str)).c_str()

#define FMT2BUF(buf, ...) { \
    size_t n = _countof(buf); \
    auto ret = fmt::format_to_n(buf, n, ##__VA_ARGS__); \
    ret.size < n ? buf[ret.size] = 0 : buf[n - 1] = 0; \
}
