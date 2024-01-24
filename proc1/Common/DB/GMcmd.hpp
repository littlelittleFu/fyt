/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
    struct GMcmdInfo
    {
        uint8_t     ID;                        ///编号
        char        GmCmdName[32];             ///命令
        uint8_t     mod_level;          /// 命令所需权限等级
    };


    class GMCmdConfig : public TableBase<GMcmdInfo>
    {
        DECLARE_SINGLETON(GMCmdConfig);
    public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "ID", row->ID, 0);
            CELL_VALUE(InRow, "GmCmdName", row->GmCmdName, 1);
            CELL_VALUE(InRow, "mod_level", row->mod_level, 0);
        }

        virtual bool CheckValid(TItem *row) override
        {
            if (row->ID == 0 || row->GmCmdName[0] == 0) return false;
            return true;
        }

        virtual void FillMapping(TItem* row) override
        {
            TKeyIDMapping* t0 = &key_id_mappings_;
            if (t0->find(row->ID) == t0->end())
                (*t0)[row->ID] = 0;
            TItem*& t1 = (*t0)[row->ID];
            t1 = row;
            key_name_mappings_[row->GmCmdName] = row;
        }
    };


#define sGM_CMD_Config (*DATA::GMCmdConfig::Instance())
}