#ifndef CSV_HELPER_H_
#define CSV_HELPER_H_

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <codecvt>
#include <iostream>
#include <unordered_map>

using namespace std;


#define CSV_U2G(InSrc) CSV_HELPER::CsvUtils::Codecvt<CsvUtils::UTF8_T, CsvUtils::ANSI_T>(InSrc);
#define CSV_G2U(InSrc) CSV_HELPER::CsvUtils::Codecvt<CsvUtils::ANSI_T, CsvUtils::UTF8_T>(InSrc);

#define GET_CELL_VALUE_INT(field) row->field = InRow[#field]
#define GET_CELL_VALUE_STRING(field) { const char *temp = InRow[#field]; if (temp) row->field = temp; }

#define CELL_PARAM_DEFINE                                                   \
static char Value[1024] = {0};

#define CELL_VALUE(InRow, InIndex, OutValue, OutType)                       \
    CELL_VALUE_##OutType(InRow, InIndex, OutValue)

#define CELL_VALUE_0(InRow, InIndex, OutValue)                              \
{                                                                           \
    OutValue = InRow[InIndex];                                              \
}

#define CELL_VALUE_1(InRow, InIndex, OutValue)                              \
{                                                                           \
    const CSV_HELPER::CHAR* temp = InRow[InIndex];                                      \
    if(nullptr != temp)                                                     \
    {                                                                       \
        CSV_HELPER::CsvUtils::StrSafeCopy(OutValue, temp, sizeof(OutValue));\
    }                                                                       \
    else                                                                    \
    {                                                                       \
        memset(OutValue, 0, sizeof(OutValue));                              \
    }                                                                       \
}

#define SPLIT_CELL_KEY_VALUE(InRow, InIndex, groupDelim, kvDelim, OutValue)				\
{        																	\
    std::string v;                                                          \
    CELL_STRING_VALUE(InRow, InIndex, v);                                   \
	auto groupVec = str_split(v, groupDelim);						        \
	for (auto iter = groupVec.begin();iter != groupVec.end();++iter)		\
	{																		\
		auto kvVec = str_split(*iter, kvDelim);						        \
		if (kvVec.size() != 2) continue;									\
		OutValue[atoi(kvVec[0].c_str())] = atoi(kvVec[1].c_str());			\
	}																		\
}

#define SPLIT_CELL_KEY_VALUE_AUTO_PAD(InRow, InIndex, groupDelim, kvDelim, OutValue)				\
{        																	\
    std::string v;                                                          \
    CELL_STRING_VALUE(InRow, InIndex, v);                                   \
	auto groupVec = str_split(v, groupDelim);						        \
    if(groupVec.size() == 1){                                               \
        OutValue[atoi(groupVec[0].c_str())] = 1;                            \
    }                                                                       \
    else {                                                                  \
        for (auto iter = groupVec.begin(); iter != groupVec.end(); ++iter)	\
        {																	\
            auto kvVec = str_split(*iter, kvDelim);						    \
            if (kvVec.size() != 2) continue;								\
                OutValue[atoi(kvVec[0].c_str())] = atoi(kvVec[1].c_str());	\
        }                                                                   \
    }																	    \
}

#define SPLIT_STRING_KEY_MULTIPLE_VALUE(Str, groupDelim, kvDelim, AttrNum, OutValue)				\
{        																	\
	auto groupVec = str_split(Str, groupDelim);						        \
	for (auto iter = groupVec.begin();iter != groupVec.end();++iter)		\
	{																		\
		auto kvVec = str_split(*iter, kvDelim);						        \
		if (kvVec.size() != AttrNum || AttrNum <= 1) continue;			    \
        OutValue[atoi(kvVec[0].c_str())].resize(AttrNum - 1);               \
        for (int32_t i = 0;i < AttrNum - 1;++ i)                            \
        {                                                                   \
           OutValue[atoi(kvVec[0].c_str())][i] = atoi(kvVec[i + 1].c_str());\
        }                                                                   \
	}																		\
}

#define SPLIT_CELL_KEY_MULTIPLE_VALUE(InRow, InIndex, groupDelim, kvDelim, AttrNum, OutValue)				\
{        																	\
    std::string v;                                                          \
    CELL_STRING_VALUE(InRow, InIndex, v);                                   \
	SPLIT_STRING_KEY_MULTIPLE_VALUE(v, groupDelim, kvDelim, AttrNum, OutValue);\
}

#define SPLIT_CELL_KEY_MUTIBAG_PAIR_VALUE(Str, bagDelim, groupDelim, kvDelim, OutValue)\
{                                                                           \
    auto bagVec = str_split(Str, bagDelim);                                 \
    int index = 0;                                                          \
    for(auto iter = bagVec.begin();iter!=bagVec.end();++iter)               \
    {                                                                       \
        auto groupVec = str_split(*iter,groupDelim);                        \
        std::vector<std::pair<int,int>>valueVec;                            \
        for(auto it = groupVec.begin();it!=groupVec.end();++it)             \
        {                                                                   \
            auto kvVec = str_split(*it,kvDelim);                          \
            if(kvVec.size()!=2)continue;                                    \
            valueVec.emplace_back(std::make_pair(atoi(kvVec[0].c_str()),atoi(kvVec[1].c_str())));\
        }                                                                   \
        OutValue[index] = valueVec;                                         \
        ++index;                                                            \
    }                                                                       \
}

#define SPLIT_CELL_KEY_MUTIBAG_VALUE(InRow, InIndex, bagDelim ,groupDelim, kvDelim, OutValue)\
{\
    std::string v;                                                          \
    CELL_STRING_VALUE(InRow, InIndex, v);                                   \
    SPLIT_CELL_KEY_MUTIBAG_PAIR_VALUE(v, bagDelim, groupDelim, kvDelim, OutValue);   \
}

#define SPLIT_CELL_SET_VALUE(InRow, InIndex, groupDelim, OutValue)		    \
{                                                                           \
    std::string v;                                                          \
    CELL_STRING_VALUE(InRow, InIndex, v);                                   \
	auto groupVec = str_split(v, groupDelim);						        \
	for (auto iter = groupVec.begin();iter != groupVec.end();++iter)		\
	{																		\
		OutValue.insert(atoi(iter->c_str()));								\
	}																		\
}

#define CELL_STRING_VALUE(InRow, InIndex, OutValue)							\
{                                                                           \
    memset(Value, 0, sizeof(Value));                                        \
	CELL_VALUE(InRow, InIndex, Value, 1);									\
	OutValue = Value;														\
}

#define CELL_PAIR_INT_VALUE(InRow, InIndex, groupDelim, OutValueFirst, OutValueSecond)	\
{                                                                           \
    std::string v;                                                          \
    CELL_STRING_VALUE(InRow, InIndex, v);                                   \
    auto groupVec = str_split(v, groupDelim);					            \
	if (groupVec.size() == 2){	                                            \
        OutValueFirst = atoi(groupVec[0].c_str());                         \
        OutValueSecond = atoi(groupVec[1].c_str());			                \
    }                                                                       \
}

inline uint32_t Bit_Move_Right(uint32_t val, int n)
{
    uint32_t size = sizeof(val) * 8;
    n = n % size;
    return (val << (size - n) | (val >> n));
}

#define CELL_COLOR(InRow, InIndex, OutValue)                                \
{                                                                           \
    std::string v;                                                          \
    CELL_STRING_VALUE(InRow, InIndex, v);                                   \
    if(!v.empty())                                                        \
    {                                                                       \
        OutValue = std::stoul(v, 0, 16);                                    \
        if(v.size() < 8)                                                    \
            OutValue |= 0xFF000000;                                         \
        else                                                                \
            OutValue = Bit_Move_Right(OutValue, 24);                        \
    }                                                                       \
    else                                                                    \
        OutValue = 0xFFFFFFFF;                                              \
}

#define OPERATOR_ENUM(enum_name) \
static bool operator < (int32_t left, enum_name value) \
{ \
    return left < static_cast<int32_t>(value); \
} \
static bool operator <= (int32_t left, enum_name value) \
{ \
    return left <= static_cast<int32_t>(value); \
} \
static bool operator > (int32_t left, enum_name value) \
{ \
    return left > static_cast<int32_t>(value); \
} \
static bool operator >= (int32_t left, enum_name value) \
{ \
    return left >= static_cast<int32_t>(value); \
} \
static bool operator == (int32_t left, enum_name value) \
{ \
    return left == static_cast<int32_t>(value); \
} \
static bool operator != (int32_t left, enum_name value) \
{ \
    return left != static_cast<int32_t>(value); \
}



namespace CSV_HELPER
{
class Row;
class Cell;
class CsvParser;
class CsvHelper;
struct CsvUtils;
struct UMapHash;
struct UMapEqual;

typedef char                     CHAR;

typedef std::vector<Row>         Rows;
typedef std::vector<Cell>        Cells;
typedef std::unordered_map<const CHAR*, int32_t, UMapHash, UMapEqual> Header;

enum class CsvEncoding
{
    e_ANSI,
    e_UTF8,
    e_UTF8BOM,
    e_UnicodeLittle,
    e_UnicodeBig,
    e_Unknown
};

enum class CsvError {
    e_Success = 0,
    e_DataError,
    e_FileError,
    e_EncodingError,
    e_WriteError,
    e_HeadError,

    e_ErrorCount
};

OPERATOR_ENUM(CsvEncoding);
OPERATOR_ENUM(CsvError);

struct UMapHash
{
    size_t operator()(const CHAR* InStr) const
    {
#ifdef _WIN32
        int32_t strLength = 0;
        for (; *(InStr + strLength) != '\0'; ++strLength);
        return std::_Hash_array_representation(InStr, strLength);
#else
        std::hash<std::string> hash_fn;
        return hash_fn(InStr);
#endif
    }
};

struct UMapEqual
{
    bool operator() (const CHAR* LStr, const CHAR* RStr) const
    {
        return strcmp(LStr, RStr) == 0;
    }
};

struct CsvUtils
{
    typedef std::codecvt_utf8<wchar_t>  UTF8_T;
    typedef std::codecvt_utf16<wchar_t> UTF16_T;
    typedef std::codecvt_byname<wchar_t, char, std::mbstate_t> ANSI_T;

    static CsvEncoding CheckEncoding(const std::string& InFile);
    static CsvEncoding CheckEncoding(std::ifstream& InFstream);
    static bool CheckFileIsUTF8(const std::string& InFile);
    static bool CheckFileIsUTF8(std::ifstream& InFstream);
    static bool CheckFileIsANSI(const std::string& InFile);
    static bool CheckFileIsANSI(std::ifstream& InFstream);
    static bool StrIsUTF8(const std::string& InSrc);
    static bool StrIsANSI(const std::string& InSrc);
    static void StrSafeCopy(char* InDest, const char* InSrc, size_t InDestLen);

    template<class SrcT, class DesT>
    static std::string Codecvt(const std::string& InSrc);
};


class Cell
{
public:
    Cell(const CHAR* InCell, uint8_t InAttr = 0) :
        m_Value(InCell), m_Attribute(InAttr) {}
    operator const CHAR*() const;
    operator int32_t() const;
    operator int8_t() const;
    operator std::string() const;
    operator int16_t() const;
    operator int64_t() const;
    operator uint8_t() const;
    operator uint16_t() const;
    operator uint32_t() const;
    operator uint64_t() const;
    bool IsNull() const;

    const CHAR* Value() const;
    uint8_t Attribute() const;
    void SetAttribute(uint8_t InAttr);
    void SetValue(const char* InValue);

    static bool GetCellAttr(uint8_t InAttr, uint8_t InType);
private:
    const CHAR* m_Value;
    uint8_t m_Attribute;
};


class Row
{
public:
    Row() : m_Header(nullptr) {}
    const Cell& operator[](const CHAR* InValueName) const;
    const Cell& operator[](const std::string& InValueName) const;
    const Cell& operator[](int32_t InValueAt) const;

    int32_t Size() const;
    void PushBack(Cell InValue);
    const Cells& GetCells() const;
    void SetHeader(const Header* InHeader);

private:
    Cells m_Cells;
    const Header* m_Header;
};

class CsvCore
{
public:
    CsvCore(std::string InSourceStr, int32_t InHeaderIndex = 0);
    CsvCore(CHAR* InSourceStr, int32_t InHeaderIndex = 0);
    virtual ~CsvCore();

    const Row& operator[](int32_t InValueAt) const;
    Row* operator[](int32_t InValueAt);

    const Rows& GetRows() const;
    const Header& GetHeader() const;
    int32_t GetHeaderIndex();
    void SetHeaderIndex(int32_t InValue);
    void CellAppend(std::string& DestStr, const CHAR* SrcPtr, uint8_t InAttr);

private:
    CsvCore(const CsvCore&) = delete;
    CsvCore& operator=(const CsvCore&) = delete;
    enum class ParseResult { EndOfCell, EndOfRow, EndOfString };

    void ParseRows();
    void ParseHeader();
    ParseResult ParseRow();
    ParseResult ParseCell();
    char MeasureNewLine(const CHAR* At);

private:
    int32_t m_HeaderIndex;
    Header m_Header;
    const CHAR* m_ReadAt;
    CHAR* m_BufferStart;
    std::string m_SourceStr;
    Rows m_Rows;
};


class CsvHelper 
{
public:
    CsvHelper();
    CsvHelper(std::string InFile);
    virtual ~CsvHelper();

    int32_t GetHeaderIndex();
    bool ReSaveFile(CsvEncoding OutEncoding);
    bool ReSaveFile(const std::string& OutFile, CsvEncoding OutEncoding);
    void Parser(const std::string& InSourceStr, int32_t InHeaderIndex = 0);
    bool SaveFile(const std::string& OutFile, CsvEncoding OutEncoding = CsvEncoding::e_UTF8);
    std::string LoadFile(const std::string& InFile, CsvEncoding InEncoding = CsvEncoding::e_UTF8);

    void SetHeaderIndex(int32_t InIndex);
    const Rows& GetRows() const;
    const Header& GetHeader() const;
    CsvError GetError();
    CsvEncoding GetEncoding();

private:
    CsvHelper(const CsvHelper&) = delete;
    CsvHelper& operator=(const CsvHelper&) = delete;

    void Append(std::string& DestStr, const CHAR* SrcPtr, uint8_t InAttr);

private:
    std::string m_SrcFile;
    CsvCore* m_CsvCore;
    CsvEncoding m_OldEncoding;
    CsvEncoding m_Encoding;
    CsvError m_error;
};

} // ! namespace CSV_HELPER

#endif // !CSV_HELPER_H_
