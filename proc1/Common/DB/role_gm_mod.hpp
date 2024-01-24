/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
    struct RoleMGMod
    {
        uint32_t     ID;                        ///编号
        char        Role_name[32];             ///用户名
        char        Role_account[32];          /// 账号
        uint32_t     MOD;                       /// MG权限 
    };


    class RoleMGModConfig : public TableBase<RoleMGMod>
    {
        DECLARE_SINGLETON(RoleMGModConfig);
    public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "ID", row->ID, 0);
            CELL_VALUE(InRow, "Role_name", row->Role_name, 1);
            CELL_VALUE(InRow, "Role_account", row->Role_account, 1);
            CELL_VALUE(InRow, "MOD", row->MOD, 0);
        }

        virtual bool CheckValid(TItem *row) override
        {
            if (row->ID == 0 || row->Role_account[0] == 0) return false;
            return true;
        }

        virtual void FillMapping(TItem* row) override
        {
            TKeyIDMapping* t0 = &key_id_mappings_;
            if (t0->find(row->ID) == t0->end())
                (*t0)[row->ID] = 0;
            TItem*& t1 = (*t0)[row->ID];
            t1 = row;
            key_name_mappings_[row->Role_account] = row;
        }
    };


#define sROLE_GM_MOD_Config (*DATA::RoleMGModConfig::Instance())
}

