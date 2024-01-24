/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
struct InnerForce
{
    uint32_t      Level;                       /// ��ǰ�ȼ�
    uint8_t       Job;                         /// ְҵ
    uint64_t      UpgradeExp;                  /// �����ڹ�����
    uint32_t      InnerForceValue;             /// �����ڹ�ֵ
    uint32_t      InnerForceRec;               /// �ڹ��ָ��ٶ�
    uint32_t      Interval;                    /// �ڹ��ָ����
    uint16_t      DeratePct;                   /// �ڹ����˰ٷֱ�
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

