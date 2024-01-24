#ifndef TABLE_BASE_H_
#define TABLE_BASE_H_

#include <map>
#include <vector>
#include <set>
#include <string>
#include <utility>

#include "ILogHelper.h"
#include "IFileHelper.h"


#define SAVE_CSV_TO_UTF8 0
#define SAVE_CSV_TO_GBK  1
#define SAVE_CSV_NOT     2
#define SAVE_CSV         SAVE_CSV_TO_GBK

template<class TableItem>
class TableBase
{
public:
    typedef TableItem                               TItem;
    typedef std::vector<TItem*>                     TRows;
    typedef std::map<uint32_t, TItem *>             TKeyIDMapping;
    typedef std::map<std::string, TItem*>           TKeyNameMapping;
	typedef std::map<std::string, TRows *>          TKeyNameMappingTRows;

    typedef std::map<uint16_t, TKeyIDMapping*>      TKeyIDMappingKeyIDMapping;
    
public:
    TableBase() = default;
    virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) = 0;
    virtual bool CheckValid(TItem *row) { return true; }
    virtual void PushData(TItem* row)
    {
        data_.push_back(row);
    }
    virtual void FillMapping(TItem* row)
    {
    }
    virtual ~TableBase()
    {
        Release();
    }

    virtual void Release()
    {
        key_id_mappings_.clear();
        key_name_mappings_.clear();
        for (int32_t i = 0; i < data_.size(); i++)
        {
            if (nullptr != data_[i])
            {
                delete data_[i];
                data_[i] = nullptr;
            }
        }

        key_name_mappings_rows.clear();
        key_id_mappings_key_id_mappings_.clear();
        TRows().swap(data_);
    }

    virtual bool LoadFromStr(const std::string& InStr)
    {
        if (InStr.empty())
        {
            return false;
        }

        CSV_HELPER::CsvHelper csv;
        csv.Parser(InStr);
        if (0 != csv.GetError())
        {
            return false;
        }

        int headerIndex = csv.GetHeaderIndex();
        const CSV_HELPER::Rows& rows = csv.GetRows();
        for (int rowIndex = headerIndex + 1; rowIndex < rows.size(); rowIndex++)
        {
            TItem * row = new TItem();
            FillData(row, rows[rowIndex]);
            if (!CheckValid(row)) {
                delete row;
                continue;
            }
            PushData(row);
            FillMapping(row);
        }

        return true;
    }

    virtual bool Load(const std::string& path)
    {
        LOG_NORMAL("load %s begin.", path.c_str());

        if (!IFileHelper::GetInstance()->IsFileExist(path.c_str())) 
        {
            return false;
        }

        CSV_HELPER::CsvHelper csv;
        csv.Parser(csv.LoadFile(path, CSV_HELPER::CsvEncoding::e_ANSI), 1);
        if (0 != csv.GetError())
        {
            LOG_NORMAL(u8"csv parse error: %s", path.c_str());
            throw std::runtime_error("csv parse error");
        }

        int headerIndex = csv.GetHeaderIndex();
        const CSV_HELPER::Rows& rows = csv.GetRows();
        for (int rowIndex = headerIndex + 1; rowIndex < rows.size(); rowIndex++)
        {
            TItem * row = new TItem();
            FillData(row, rows[rowIndex]);
            if (!CheckValid(row)) {
                delete row;
                continue;
            }
            PushData(row);
            FillMapping(row);
        }


        LOG_NORMAL("load %s end.", path.c_str());
#ifdef SAVE_CSV
        CSV_HELPER::CsvEncoding encodeing = csv.GetEncoding();
        if (SAVE_CSV == SAVE_CSV_TO_UTF8)
        {
            csv.ReSaveFile(CSV_HELPER::CsvEncoding::e_UTF8);
        }
        else if (SAVE_CSV == SAVE_CSV_TO_GBK)
        {
            csv.ReSaveFile(CSV_HELPER::CsvEncoding::e_ANSI);
        }
#endif // SAVE_CSV


        return true;
    }
    virtual bool ReLoad(const std::string& path, bool is_release_old = false)
    {
        LOG_NORMAL("reload %s begin.", path.c_str());

        if (is_release_old)
            this->Release();

        if (!IFileHelper::GetInstance()->IsFileExist(path.c_str()))
        {
            return false;
        }

        CSV_HELPER::CsvHelper csv;
        csv.Parser(csv.LoadFile(path, CSV_HELPER::CsvEncoding::e_ANSI), 1);
        if (0 != csv.GetError())
        {
            LOG_NORMAL(u8"csv parse error: %s", path.c_str());
            throw std::runtime_error("csv parse error");
        }

        key_id_mappings_.clear();
        key_name_mappings_.clear();
        int headerIndex = csv.GetHeaderIndex();
        const CSV_HELPER::Rows& rows = csv.GetRows();
        int oldSize = this->GetSize();
        int curItem = 0;
        for (int rowIndex = headerIndex + 1; rowIndex < rows.size(); rowIndex++, curItem++)
        {
            do
            {
                TItem* row = nullptr;
                if (curItem < oldSize)
                {
                    row = this->At(curItem);
                    if (nullptr != row)
                    {
                        FillData(row, rows[rowIndex]);
                        if (!CheckValid(row)) continue;
                        PushData(row);
                        FillMapping(row);
                        break;
                    }
                }

                row = new TItem();
                FillData(row, rows[rowIndex]);
                if (!CheckValid(row)) {
                    delete row;
                    continue;
                }
                PushData(row);
                FillMapping(row);
            } while (false);
        }

        LOG_NORMAL("reload %s end.", path.c_str());
#ifdef SAVE_CSV
        CSV_HELPER::CsvEncoding encodeing = csv.GetEncoding();
        if (SAVE_CSV == SAVE_CSV_TO_UTF8)
        {
            csv.ReSaveFile(CSV_HELPER::CsvEncoding::e_UTF8);
        }
        else if (SAVE_CSV == SAVE_CSV_TO_GBK)
        {
            csv.ReSaveFile(CSV_HELPER::CsvEncoding::e_ANSI);
        }
#endif // SAVE_CSV

        return true;
    }
  //////////////////////////////////////////////////////////////////////////
    TRows *GetRows(const std::string& Name)
    {
        TKeyNameMappingTRows *t0 = &key_name_mappings_rows;

        if (t0->find(Name) == t0->end())
            return 0;
        TRows *&t1 = (*t0)[Name];

        return t1;
    }

    virtual TItem *Get(uint16_t Id)
    {
        TKeyIDMapping *t0 = &key_id_mappings_;

        if (t0->find(Id) == t0->end())
            return nullptr;
        TItem *&t1 = (*t0)[Id];

        return t1;
    }
    virtual bool Has(uint16_t Id)
    {
        TKeyIDMapping *t0 = &key_id_mappings_;

        if (t0->find(Id) == t0->end())
            return false;

        return true;
    }
    virtual TItem *Get(const std::string& Name)
    {
        TKeyNameMapping *t0 = &key_name_mappings_;

        if (t0->find(Name) == t0->end())
            return nullptr;
        TItem *&t1 = (*t0)[Name];

        return t1;
    }
    virtual bool Has(const std::string& Name)
    {
        TKeyNameMapping *t0 = &key_name_mappings_;

        if (t0->find(Name) == t0->end())
            return false;

        return true;
    }
    virtual TItem *At(int32_t index)
    {
        return data_[index];
    }
    virtual int GetSize(void)
    {
        return data_.size();
    }
    virtual TRows &GetData(void)
    {
        return data_;
    }
    virtual TKeyIDMapping &GetIDMappings(void)
    {
        return key_id_mappings_;
    }
    virtual TKeyNameMapping &GetNameMappings(void)
    {
        return key_name_mappings_;
    }
	
	virtual TKeyNameMappingTRows &GetMappings(void)
    {
        return key_name_mappings_rows;
    }
    virtual TItem *GetByID(int32_t ID)
    {
        if (key_id_mappings_.find(ID) == key_id_mappings_.end())
            return nullptr;

        return key_id_mappings_[ID];
    }
    virtual TItem *GetByKeyName(const std::string &key_name)
    {
        std::string name = key_name;
    
        if (key_name_mappings_.find(name) == key_name_mappings_.end())
            return nullptr;

        return key_name_mappings_[name];
    }

protected:
    TRows                 data_;
    TKeyIDMapping         key_id_mappings_;
    TKeyNameMapping       key_name_mappings_;
	TKeyNameMappingTRows  key_name_mappings_rows;
    TKeyIDMappingKeyIDMapping key_id_mappings_key_id_mappings_;
};

TABLE_BASE_H_

#endif // !TABLE_BASE_H_
