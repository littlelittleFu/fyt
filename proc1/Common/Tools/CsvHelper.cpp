#include "stdafx.h"
#include "CsvHelper.h"
#include "StringHelper.h"

namespace CSV_HELPER
{
static Cell s_DummyCell(nullptr);
static Row  s_DummyRow;
static Rows s_DummyRows;

template<class SrcT, class DesT>
std::string CsvUtils::Codecvt(const std::string& InSrc)
{
    if (typeid(SrcT) == typeid(DesT))
    {
        return InSrc;
    }

    if (typeid(SrcT) == typeid(ANSI_T) && typeid(DesT) == typeid(UTF8_T))
    {
        return gbk_to_utf8(InSrc);
    }
    else if (typeid(SrcT) == typeid(UTF8_T) && typeid(DesT) == typeid(ANSI_T))
    {
        return utf8_to_gbk(InSrc);
    }
    else if (typeid(SrcT) == typeid(UTF16_T) && typeid(DesT) == typeid(UTF8_T))
    {
    }
    else if (typeid(SrcT) == typeid(UTF8_T) && typeid(DesT) == typeid(UTF16_T))
    {
    }
    else if (typeid(SrcT) == typeid(UTF16_T) && typeid(DesT) == typeid(ANSI_T))
    {
    }
    else if (typeid(SrcT) == typeid(ANSI_T) && typeid(DesT) == typeid(UTF16_T))
    {
    }
    else
    {
        /* error */
    }

    return std::string();
}

CsvEncoding CsvUtils::CheckEncoding(const std::string& InFile)
{
    ifstream fin(InFile, ios::binary);
    if (!fin.good())
    {
        return CsvEncoding::e_Unknown;
    }

    CsvEncoding result = CheckEncoding(fin);
    fin.close();

    return result;
}

CsvEncoding CsvUtils::CheckEncoding(std::ifstream& InFstream)
{
    if (!InFstream.good())
    {
        return CsvEncoding::e_Unknown;
    }

    streampos sp = InFstream.tellg();
    InFstream.seekg(0, std::ios::beg);

    CsvEncoding result = CsvEncoding::e_Unknown;
    uint8_t ch;
    InFstream.read((CHAR*)&ch, sizeof(uint8_t));
    int32_t code = ch << 8;
    InFstream.read((CHAR*)&ch, sizeof(uint8_t));
    code |= ch;
    InFstream.read((CHAR*)&ch, sizeof(uint8_t));
    InFstream.seekg(sp);

    switch (code)
    {
    case 0xFFFE:
        result = CsvEncoding::e_UnicodeLittle;
        break;
    case 0xFeFF:
        result = CsvEncoding::e_UnicodeBig;
        break;
    case 0xEFBB:
        if (ch == 0xBF)
        {
            result = CsvEncoding::e_UTF8BOM;
            break;
        }
    default:
        if (true == CheckFileIsUTF8(InFstream))
        {
            result = CsvEncoding::e_UTF8;
        }
        else if(true == CheckFileIsANSI(InFstream))
        {
            result = CsvEncoding::e_ANSI;
        }
        else
        {
            result = CsvEncoding::e_Unknown;
        }
        break;
    }

    return result;
}

bool CsvUtils::CheckFileIsUTF8(const std::string& InFile)
{
    ifstream fin(InFile, ios::binary);

    if (!fin.good())
    {
        return false;
    }

    bool result = CheckFileIsUTF8(fin);
    fin.close();

    return result;
}

bool CsvUtils::CheckFileIsUTF8(std::ifstream& InFstream)
{
    if (!InFstream.good())
    {
        return false;
    }

    streampos sp = InFstream.tellg();
    InFstream.seekg(0, std::ios::beg);

    stringstream buffer;
    buffer << InFstream.rdbuf();
    InFstream.seekg(sp);
    string str = buffer.str();

    return StrIsUTF8(str);
}

bool CsvUtils::CheckFileIsANSI(const std::string& InFile)
{
    ifstream fin(InFile, ios::binary);

    if (!fin.good())
    {
        return false;
    }

    bool result = CheckFileIsANSI(fin);
    fin.close();

    return result;
}

bool CsvUtils::CheckFileIsANSI(std::ifstream& InFstream)
{
    if (!InFstream.good())
    {
        return false;
    }

    streampos sp = InFstream.tellg();
    InFstream.seekg(0, std::ios::beg);

    stringstream buffer;
    buffer << InFstream.rdbuf();
    InFstream.seekg(sp);
    string str = buffer.str();

    return StrIsANSI(str);
}

bool CsvUtils::StrIsUTF8(const std::string& InSrc)
{
    size_t i = 0;
    size_t len = InSrc.size();
    uint8_t *str = (uint8_t *)InSrc.c_str();
    bool containOverlap = false;
    bool hasUTF8Char = false;
    while (i < len)
    {
        if (str[i] <= 0x7F)
        {
            i += 1;
            continue;
        }
        else if (str[i] >= 0xC2 && str[i] <= 0xDF)
        {
            if (i + 1 < len)
            {
                if (str[i + 1] >= 0xA0 && str[i + 1] <= 0xBF)
                {
                    containOverlap = true;
                    i += 2;
                    continue;
                }
                else if (str[i + 1] < 0x80 || str[i + 1] > 0xBF)
                {
                    return false;
                }
            } 
            else
            {
                return false;
            }
            i += 2;
        }
        else if (str[i] == 0xE0)
        {
            if (i + 2 < len)
            {
                if (str[i + 1] < 0xA0 || str[i + 1] > 0xBF)
                {
                    return false;
                }
                if (str[i + 2] < 0x80 || str[i + 2] > 0xBF)
                {
                    return false;
                }
            } 
            else
            {
                return false;
            }
            i += 3;
        }
        else if (str[i] >= 0xE1 && str[i] <= 0xEC)
        {
            if (i + 2 < len)
            {
                if (str[i + 1] < 0x80 || str[i + 1] > 0xBF)
                {
                    return false;
                }
                if (str[i + 2] < 0x80 || str[i + 2] > 0xBF)
                {
                    return false;
                }
            } 
            else
            {
                return false;
            }
            i += 3;
        } 
        else if (str[i] == 0xED)
        {
            if (i + 2 < len)
            {
                if (str[i + 1] < 0x80 || str[i + 1] > 0x9F)
                {
                    return false;
                }
                if (str[i + 2] < 0x80 || str[i + 2] > 0xBF)
                {
                    return false;
                }
            } 
            else
            {
                return false;
            }
            i += 3;
        } 
        else if (str[i] >= 0xEE && str[i] <= 0xEF)
        {
            if (i + 2 < len)
            {
                if (str[i + 1] < 0x80 || str[i + 1] > 0xBF)
                {
                    return false;
                }
                if (str[i + 2] < 0x80 || str[i + 2] > 0xBF)
                {
                    return false;
                }
            } 
            else
            {
                return false;
            }
            i += 3;
        } 
        else
        {
            return false;
        }

        hasUTF8Char = true;
    }

    if (containOverlap) 
    {
        return hasUTF8Char;
    }

    return true;
}

bool CsvUtils::StrIsANSI(const std::string& InSrc)
{
    return false == StrIsUTF8(InSrc);
}

void CsvUtils::StrSafeCopy(char* InDest, const char* InSrc, size_t InDestLen)
{
    if(nullptr == InSrc)
    {
        InDest[0] = '\0';
        return;
    }

    strcpy_s(InDest, InDestLen, InSrc);
    InDest[InDestLen - 1] = '\0';
}

bool Cell::GetCellAttr(uint8_t InAttr, uint8_t InType)
{
    return ((InAttr & (1 << InType)) > 0) ? true : false;
}

Cell::operator const CHAR* () const
{
    return m_Value;
}

Cell::operator int32_t() const
{
    if (nullptr == m_Value)
    {
        return 0;
    }
    return atoi(m_Value);
}

Cell::operator int8_t() const
{
    if (nullptr == m_Value)
    {
        return 0;
    }
    return static_cast<int8_t>(atoi(m_Value));
}

Cell::operator std::string() const
{
    if (nullptr == m_Value)
    {
        return std::string();
    }
    return std::string(m_Value);
}

Cell::operator int16_t() const
{
    if (nullptr == m_Value)
    {
        return 0;
    }
    return static_cast<int16_t>(atoi(m_Value));
}

Cell::operator int64_t() const
{
    if (nullptr == m_Value)
    {
        return 0;
    }
    return atoll(m_Value);
}

Cell::operator uint16_t() const
{
    if (nullptr == m_Value)
    {
        return 0;
    }
    return static_cast<uint16_t>(atoi(m_Value));
}

Cell::operator uint8_t() const
{
    if (nullptr == m_Value)
    {
        return 0;
    }
    return static_cast<uint8_t>(atoi(m_Value));
}

Cell::operator uint32_t() const
{
    if (nullptr == m_Value)
    {
        return 0;
    }
    return static_cast<uint32_t>(atoll(m_Value));
}

Cell::operator uint64_t() const
{
    if (nullptr == m_Value)
    {
        return 0;
    }
    return static_cast<uint64_t>(atoll(m_Value));
}

bool Cell::IsNull() const
{
    return (m_Value == nullptr);
}

const CHAR* Cell::Value() const
{
    return m_Value;
}

uint8_t Cell::Attribute() const
{
    return m_Attribute;
}

void Cell::SetAttribute(uint8_t InAttr)
{
    m_Attribute = InAttr;
}

void Cell::SetValue(const char* InValue)
{
    m_Value = InValue;
}

const Cell& Row::operator[](const CHAR* InValueName) const
{
    if (m_Cells.empty())
    {
        return s_DummyCell;
    }
    Header::const_iterator iter = m_Header->find(InValueName);
    if (iter != m_Header->end())
    {
        return m_Cells[iter->second];
    }

    return s_DummyCell;
}

const Cell& Row::operator[](const std::string& InValueName) const
{
    if (m_Cells.empty())
    {
        return s_DummyCell;
    }

    Header::const_iterator iter = m_Header->find(InValueName.c_str());
    if (iter != m_Header->end())
    {
        return m_Cells[iter->second];
    }

    return s_DummyCell;
}

const Cell& Row::operator[](int32_t InValueAt) const
{
    if (m_Cells.empty())
    {
        return s_DummyCell;
    }

    return m_Cells[InValueAt];
}

int32_t Row::Size() const
{
    return m_Cells.size();
}

const Cells& Row::GetCells() const
{
    return m_Cells;
}

void Row::PushBack(Cell InValue)
{
    m_Cells.push_back(InValue);
}

void Row::SetHeader(const Header* InHeader)
{
    m_Header = InHeader;
}

CsvCore::CsvCore(std::string InSourceStr, int32_t InHeaderIndex /*= 0*/) :
    m_HeaderIndex(InHeaderIndex),
    m_ReadAt(nullptr), m_BufferStart(nullptr),
    m_SourceStr(std::move(InSourceStr))
{
    if (!m_SourceStr.empty())
    {
        ParseRows();
        ParseHeader();
    }
}

CsvCore::CsvCore(CHAR* InSourceStr, int32_t InHeaderIndex /*= 0*/) :
    m_HeaderIndex(InHeaderIndex),
    m_ReadAt(nullptr), m_BufferStart(nullptr),
    m_SourceStr(InSourceStr)
{
    if (!m_SourceStr.empty())
    {
        ParseRows();
        ParseHeader();
    }
}

CsvCore::~CsvCore()
{
}

const Row& CsvCore::operator[](int32_t InValueAt) const
{
    if (InValueAt < m_Rows.size())
    {
        return m_Rows[InValueAt];
    }
    return s_DummyRow;
}

Row* CsvCore::operator[](int32_t InValueAt)
{
    return nullptr;
}

const Rows& CsvCore::GetRows() const
{
    return m_Rows;
}

int32_t CsvCore::GetHeaderIndex()
{
    return m_HeaderIndex;
}

void CsvCore::SetHeaderIndex(int32_t InValue)
{
    m_HeaderIndex = InValue;
    ParseHeader();
}

void CsvCore::CellAppend(std::string& DestStr, const CHAR* SrcPtr, uint8_t InAttr)
{
    if (nullptr == SrcPtr)
    {
        return;
    }

    const CHAR* appendAt = SrcPtr;
    bool bQuoted = Cell::GetCellAttr(InAttr, 0);
    bool bEndRow = Cell::GetCellAttr(InAttr, 1);

    if (true == bQuoted)
    {
        DestStr += '"';
        while (*appendAt)
        {
            if (*appendAt == '\r' && *(appendAt + 1) == '\n')
            {
                appendAt++;
            }
            if (*appendAt == '"')
            {
                DestStr += '"';
            }
            DestStr += *appendAt;
            appendAt++;
        }
        DestStr += '"';
    }
    else
    {
        while (*appendAt)
        {
            if (*appendAt == '\r' && *(appendAt + 1) == '\n')
            {
                appendAt++;
            }
            if (*appendAt == '"')
            {
                DestStr += '"';
            }
            DestStr += *appendAt;
            appendAt++;
        }
    }

    true == bEndRow ? DestStr += '\n' : DestStr += ',';
}

const Header& CsvCore::GetHeader() const
{
    return m_Header;
}

void CsvCore::ParseRows()
{
    m_BufferStart = (CHAR*)m_SourceStr.c_str();
    if (m_BufferStart != nullptr)
    {
        m_ReadAt = m_BufferStart;
        ParseResult result;
        do
        {
            result = ParseRow();
        } while (result != ParseResult::EndOfString);
    }
}

void CsvCore::ParseHeader()
{
    if (!m_Header.empty())
    {
        m_Header.clear();
    }
    if (m_HeaderIndex > -1 && m_HeaderIndex < m_Rows.size())
    {
        const Row& row = m_Rows[m_HeaderIndex];
        for (int32_t cellIndex = 0; cellIndex < row.Size(); ++cellIndex)
        {
            m_Header.insert(std::make_pair(row[cellIndex].Value(), cellIndex));
        }
    }

    for (int32_t i = 0; i < m_Rows.size(); i++)
    {
        m_Rows[i].SetHeader(&m_Header);
    }
}

CsvCore::ParseResult CsvCore::ParseRow()
{
    const char newLineSize = MeasureNewLine(m_ReadAt);
    if (newLineSize)
    {
        m_ReadAt += newLineSize;
        return *m_ReadAt ? ParseResult::EndOfRow : ParseResult::EndOfString;
    }
    m_Rows.push_back(Row());

    ParseResult result;

    do
    {
        result = ParseCell();
    } while (result == ParseResult::EndOfCell);

    return result;
}

CsvCore::ParseResult CsvCore::ParseCell()
{
    CHAR* writeAt = m_BufferStart + (m_ReadAt - m_BufferStart);
    bool bQuoted = (*m_ReadAt == '"');
    if (bQuoted)
    {
        m_ReadAt = ++writeAt;
    }
    const CHAR* cellAddr = m_ReadAt;
    uint8_t cellAttr = bQuoted ? 1 << 0 : 0;

    while (*m_ReadAt)
    {
        if (bQuoted)
        {
            if (*m_ReadAt == '"')
            {
                int32_t numQuotes = 0;
                while (*(m_ReadAt + numQuotes) == '"') ++numQuotes;
                if (numQuotes % 2 != 0) bQuoted = false;

                m_ReadAt += numQuotes;
                numQuotes /= 2;
                while (numQuotes-- > 0) *(writeAt++) = '"';
                *writeAt = '\0';
                continue;
            }
        }
        else
        {
            const char newLineSize = MeasureNewLine(m_ReadAt);
            if (newLineSize != 0)
            {
                *writeAt = '\0';
                m_ReadAt += newLineSize;
                *m_ReadAt ? cellAttr |= 1 << 1 : cellAttr ;
                m_Rows.back().PushBack(Cell(cellAddr, cellAttr));
                return *m_ReadAt ? ParseResult::EndOfRow : ParseResult::EndOfString;
            }
            else if (*m_ReadAt == ',')
            {
                *writeAt = '\0';
                ++m_ReadAt;
                m_Rows.back().PushBack(Cell(cellAddr, cellAttr));
                return ParseResult::EndOfCell;
            }
        }

        if (writeAt != m_ReadAt) (*writeAt++) = (*m_ReadAt++);
        else m_ReadAt = ++writeAt;
    }

    m_Rows.back().PushBack(Cell(cellAddr, cellAttr));
    return ParseResult::EndOfString;
}

char CsvCore::MeasureNewLine(const CHAR* At)
{
    switch (*At)
    {
    case '\r':
        if (*(At + 1) == '\n') return 2;
        return 1;
    case '\n':
        return 1;
    default:
        return 0;
    }
}

CsvHelper::CsvHelper() :
    m_SrcFile(std::string()),
    m_CsvCore(nullptr),
    m_OldEncoding(CsvEncoding::e_Unknown),
    m_Encoding(CsvEncoding::e_Unknown),
    m_error(CsvError::e_ErrorCount)
{

}

CsvHelper::CsvHelper(std::string InFile) :
    m_SrcFile(std::move(InFile)),
    m_CsvCore(nullptr),
    m_OldEncoding(CsvEncoding::e_Unknown),
    m_Encoding(CsvEncoding::e_Unknown),
    m_error(CsvError::e_ErrorCount)
{
    if (!m_SrcFile.empty())
    {
        Parser(LoadFile(m_SrcFile));
    }
}

CsvHelper::~CsvHelper()
{
    if (nullptr != m_CsvCore)
    {
        delete m_CsvCore;
        m_CsvCore = nullptr;
    }
}

const Header& CsvHelper::GetHeader() const
{
    return m_CsvCore->GetHeader();
}

CsvError CsvHelper::GetError()
{
    return m_error;
}

CsvEncoding CsvHelper::GetEncoding()
{
    return m_Encoding;
}

void CsvHelper::Append(std::string& DestStr, const CHAR* SrcPtr, uint8_t InAttr)
{
    if (nullptr == SrcPtr || nullptr == m_CsvCore)
    {
        m_error = CsvError::e_WriteError;
        return;
    }
    m_CsvCore->CellAppend(DestStr, SrcPtr, InAttr);
}

void CsvHelper::Parser(const std::string& InSourceStr, int32_t InHeaderIndex)
{
    if (nullptr != m_CsvCore)
    {
        delete m_CsvCore;
        m_CsvCore = nullptr;
    }
    m_CsvCore = new CsvCore(InSourceStr, InHeaderIndex);
}

std::string CsvHelper::LoadFile(const std::string& InFile, CsvEncoding InEncoding/* = CsvEncoding::e_UTF8*/)
{
    std::ifstream fin(InFile, std::ios::binary);
    if (!fin.good())
    {
        m_error = CsvError::e_FileError;
        return std::string();
    }

    m_SrcFile = InFile;
    m_Encoding = CsvUtils::CheckEncoding(fin);
    m_OldEncoding = m_Encoding;

    std::string buf((fin.seekg(0, std::ios::end).tellg()), '\0');
    fin.seekg(0, std::ios::beg);
    fin.read(&buf[0], static_cast<std::streamsize>(buf.size())); 
    fin.close();

    if (m_Encoding != InEncoding && m_Encoding != CsvEncoding::e_Unknown)
    {
        if (m_Encoding == CsvEncoding::e_ANSI && InEncoding == CsvEncoding::e_UTF8)
        {
            m_Encoding = CsvEncoding::e_UTF8;
            buf = CSV_G2U(buf);
        }
        else if (m_Encoding == CsvEncoding::e_UTF8 && InEncoding == CsvEncoding::e_ANSI)
        {
            m_Encoding = CsvEncoding::e_ANSI;
            buf = CSV_U2G(buf);
        }
        else
        {
            m_Encoding = CsvEncoding::e_Unknown;
            m_error = CsvError::e_EncodingError;
        }
    }
    if (!buf.empty())
    {
        m_error = CsvError::e_Success;
    }
    else
    {
        m_error = CsvError::e_EncodingError;
    }
    return buf;
}

bool CsvHelper::SaveFile(const std::string& OutFile, CsvEncoding OutEncoding/* = CsvEncoding::e_UTF8*/)
{
    if (nullptr == m_CsvCore)
    {
        m_error = CsvError::e_DataError;
        return false;
    }

    if (OutFile.empty())
    {
        m_error = CsvError::e_FileError;
        return false;
    }

    if (m_Encoding != OutEncoding)
    {
        Parser(LoadFile(m_SrcFile, OutEncoding));
        if (nullptr == m_CsvCore && m_error != CsvError::e_Success)
        {
            return false;
        }
    }

    std::string outStr;
    const Rows& rows = this->GetRows();
    for (int32_t rowIndex = 0; rowIndex < rows.size(); rowIndex++)
    {
        int32_t cellSize = rows[rowIndex].Size();
        for (int32_t cellIndex = 0; cellIndex < cellSize; cellIndex++)
        {
            const Cell& cell = rows[rowIndex][cellIndex];
            Append(outStr, cell.Value(), cell.Attribute());
            if (m_error != CsvError::e_Success)
            {
                return false;
            }
        }
    }

    if (outStr.empty())
    {
        m_error = CsvError::e_DataError;
        return true;
    }

    std::ofstream fout(OutFile/*, std::ofstream::ate | std::ofstream::app*/);
    if (!fout.good())
    {
        m_error = CsvError::e_FileError;
        return false;
    }
    outStr.erase(outStr.end() - 1);
    fout << outStr;
    fout.close();

    m_error = CsvError::e_Success;
    return true;
}

bool CsvHelper::ReSaveFile(CsvEncoding OutEncoding)
{
    if (m_OldEncoding != OutEncoding)
    {
        SaveFile(m_SrcFile, OutEncoding);
        return m_error == CsvError::e_Success;
    }
    return false;
}

bool CsvHelper::ReSaveFile(const std::string& OutFile, CsvEncoding OutEncoding)
{
    if (m_OldEncoding != OutEncoding)
    {
        SaveFile(OutFile, OutEncoding);
        return m_error == CsvError::e_Success;
    }
    return false;
}

void CsvHelper::SetHeaderIndex(int32_t InIndex)
{
    if (nullptr != m_CsvCore)
    {
        return m_CsvCore->SetHeaderIndex(InIndex);
    }
}

int32_t CsvHelper::GetHeaderIndex()
{
    if (nullptr != m_CsvCore)
    {
        return m_CsvCore->GetHeaderIndex();
    }

    return 0;
}

const Rows& CsvHelper::GetRows() const
{
    if (nullptr != m_CsvCore)
    {
        return m_CsvCore->GetRows();
    }

    return s_DummyRows;
}

}