/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct Vipshop
	{
		uint16_t      Id;                          /// 流水号
		char        Name[32];                    /// 名称
		uint8_t       Type;                        /// 类型
		uint32_t      Icon;                        /// 按钮图标
		uint32_t      Dicon;                       /// 展示小图标
		uint32_t      Index;                       /// 面板排列
		uint8_t       Level;                       /// 功能等级
		char        desc[384];                   /// 功能描述
		uint32_t      Price;                       /// 价格
		uint32_t      Time;                        /// 购买持续时间
		char        Script[32];                  /// 脚本调用
		uint8_t       NotSell;                     /// 是否下架
	};


    class VipshopConfig : public TableBase<Vipshop>
    {
        DECLARE_SINGLETON(VipshopConfig)
    public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Id", row->Id, 0);
            CELL_VALUE(InRow, "Name", row->Name, 1);
            CELL_VALUE(InRow, "desc", row->desc, 1);
            CELL_VALUE(InRow, "Script", row->Script, 1);
            CELL_VALUE(InRow, "Type", row->Type, 0);
            CELL_VALUE(InRow, "Icon", row->Icon, 0);
            CELL_VALUE(InRow, "Dicon", row->Dicon, 0);
            CELL_VALUE(InRow, "Index", row->Index, 0);
            CELL_VALUE(InRow, "Level", row->Level, 0);
            CELL_VALUE(InRow, "Price", row->Price, 0);
            CELL_VALUE(InRow, "Time", row->Time, 0);
            CELL_VALUE(InRow, "NotSell", row->NotSell, 0);
        }

        virtual void FillMapping(TItem* row) override
        {
            TKeyIDMapping *t0 = &key_id_mappings_;
            if (t0->find(row->Id) == t0->end())
                (*t0)[row->Id] = 0;
            TItem *&t1 = (*t0)[row->Id];
            t1 = row;
        }
    };


#define sVipshopConfig (*DATA::VipshopConfig::Instance())
}