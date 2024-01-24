/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
struct InnerForce
{
    uint32_t      Level;                       /// 当前等级
    uint8_t       Job;                         /// 职业
    uint64_t      UpgradeExp;                  /// 升级内功经验
    uint32_t      InnerForceValue;             /// 配置内功值
    uint32_t      InnerForceRec;               /// 内功恢复速度
    uint32_t      Interval;                    /// 内功恢复间隔
    uint16_t      DeratePct;                   /// 内功减伤百分比
};


#pragma warning( push )
#pragma warning( disable : 4996 )

class InnerForceConfig : public TableBase<InnerForce>
{
    DECLARE_SINGLETON(InnerForceConfig);
public:
    virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
    {
        CELL_PARAM_DEFINE;
        CELL_VALUE(InRow, "Level", row->Level, 0);
        CELL_VALUE(InRow, "Job", row->Job, 0);
        CELL_VALUE(InRow, "UpgradeExp", row->UpgradeExp, 0);
        CELL_VALUE(InRow, "InnerForceValue", row->InnerForceValue, 0);
        CELL_VALUE(InRow, "InnerForceRec", row->InnerForceRec, 0);
        CELL_VALUE(InRow, "Interval", row->Interval, 0);
        CELL_VALUE(InRow, "DeratePct", row->DeratePct, 0);

    }
    virtual void FillMapping(TItem *row) override
    {
        uint32_t keyId = (row->Level << 16) | row->Job;
        key_id_mappings_[keyId] = row;
    }
    TItem *Get(uint16_t Level, uint16_t Job)
    {
        uint32_t keyId = (Level << 16) | Job;

        if (key_id_mappings_.find(keyId) == key_id_mappings_.end())
            return 0;
        return key_id_mappings_[keyId];
    }
    bool Has(uint16_t Level, uint16_t Job)
    {
        uint32_t keyId = (Level << 16) | Job;

        if (key_id_mappings_.find(keyId) == key_id_mappings_.end())
            return false;
        return true;
    }
};

#pragma warning( pop )

#define sInnerForceConfig (*DATA::InnerForceConfig::Instance())
}

