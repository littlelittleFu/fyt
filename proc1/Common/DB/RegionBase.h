#pragma once




class CsvHelper;

template<class TItem>
class RegionBase : public TableBase<TItem>
{
public:
    using TRows = typename TableBase<TItem>::TRows;
    using TTItem = typename TableBase<TItem>::TItem;

    typedef std::map<std::string, TRows*>   TMapRows;
    typedef std::map<std::string, TTItem*>   TMapNameMaping;
public:
    virtual ~RegionBase()
    {
        Release();
    }

    virtual void Release()
    {
        for (auto &it : mappings_) {
            auto &row = it.second;
            if (row) delete row;
        }
        mappings_.clear();
        name_mappings_.clear();

        TableBase<TItem>::Release();
    }

    virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
    {
        CELL_PARAM_DEFINE;
        CELL_STRING_VALUE(InRow, "KeyName", row->m_Region.KeyName);
        CELL_VALUE(InRow, "left", row->m_Region.left, 0);
        CELL_VALUE(InRow, "top", row->m_Region.top, 0);
        CELL_VALUE(InRow, "width", row->m_Region.width, 0);
        CELL_VALUE(InRow, "height", row->m_Region.height, 0);
        CELL_VALUE(InRow, "top2", row->m_Region.top2, 0);
        CELL_VALUE(InRow, "left2", row->m_Region.left2, 0);
        CELL_VALUE(InRow, "BorderStyle", row->m_Region.BorderStyle, 0);
        CELL_VALUE(InRow, "RenderType", row->m_Region.RenderType, 0);
    }
    virtual bool CheckValid(TItem *row) override
    {
        if (row->m_Region.KeyName.empty()) return false;
        return true;
    }
    virtual void FillMapping(TItem* row) override
    {
        auto key = std::string(row->m_Region.KeyName) + "_" + std::to_string(row->m_Region.left) + "_" + std::to_string(row->m_Region.top);

        TMapRows *t0 = &mappings_;

        if (t0->find(key) == t0->end())
            (*t0)[key] = new TRows();
        TRows *&t1 = (*t0)[key];

        t1->push_back(row);

        name_mappings_[key] = row;
    }
    TRows * GetRows(const std::string& Name)
    {
        TMapRows *t0 = &mappings_;

        if (t0->find(Name) == t0->end())
            return 0;
        TRows *&t1 = (*t0)[Name];

        return t1;
    }

    TItem* Get(const std::string& Name)
    {
        TMapNameMaping* t0 = &name_mappings_;

        if (t0->find(Name) == t0->end())
            return nullptr;
        TItem*& t1 = (*t0)[Name];

        return t1;
    }

    TMapNameMaping& GetNameMaping()
    {
        return name_mappings_;
    }

    bool Has(const std::string& Name)
    {
        TMapRows *t0 = &mappings_;

        if (t0->find(Name) == t0->end())
            return false;

        return true;
    }

private:
    TMapRows       mappings_;
    TMapNameMaping name_mappings_;
};