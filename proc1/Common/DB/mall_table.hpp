/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct Mall
	{
		uint32_t      ID;                          /// 编号
		char        KeyName[32];                   /// 索引名
		uint32_t      Price;                       /// 原价格
		std::map<uint16_t,uint32_t> Discount;      /// 折扣
		std::map<uint16_t,uint32_t> Number;        /// 限购数量
		uint8_t       Hot;                         /// 是否热销
		uint8_t       Page;                        /// 页签分类
		uint8_t       CostType;                    /// 消费类型
		uint8_t       Chart;                       /// 排行
		char        textDesc[384];                 /// 文字说明
		uint32_t      CmageDescID;                 /// 图片说明
		uint8_t       NotSell;                     /// 是否不上架售卖
        uint8_t       LimitsType;                  /// 限购类型 1 全服限购 2 个人限购
        uint8_t       LimitsTime;                  /// 限购时间 1 每日限购 2 每周限购 3 每月限购 4 永久限购
	};


	class MallConfig : public TableBase<Mall>
	{
		DECLARE_SINGLETON(MallConfig);
    public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "ID", row->ID, 0);
            CELL_VALUE(InRow, "KeyName", row->KeyName, 1);
            CELL_VALUE(InRow, "Price", row->Price, 0);
            SPLIT_CELL_KEY_VALUE(InRow, "Discount","|",";", row->Discount);
            SPLIT_CELL_KEY_VALUE(InRow, "Number", "|", ";", row->Number);
            CELL_VALUE(InRow, "Hot", row->Hot, 0);
            CELL_VALUE(InRow, "Page", row->Page, 0);
            CELL_VALUE(InRow, "CostType", row->CostType, 0);
            CELL_VALUE(InRow, "Chart", row->Chart, 0);
            CELL_VALUE(InRow, "textDesc", row->textDesc, 1);
            CELL_VALUE(InRow, "CmageDescID", row->CmageDescID, 0);
            CELL_VALUE(InRow, "NotSell", row->NotSell, 0);
            CELL_VALUE(InRow, "LimitsType", row->LimitsType, 0);
            CELL_VALUE(InRow, "LimitsTime", row->LimitsTime, 0);

        }

        virtual bool CheckValid(TItem *row) override
        {
            if (row->ID == 0 || row->KeyName[0] == 0) return false;
            return true;
        }

        virtual void FillMapping(TItem* row) override
        {
            TKeyIDMapping *t0 = &key_id_mappings_;
            if (t0->find(row->ID) == t0->end())
                (*t0)[row->ID] = 0;
            TItem *&t1 = (*t0)[row->ID];
            t1 = row;
            key_name_mappings_[row->KeyName] = row;
        }
	};


#define sMallConfig (*DATA::MallConfig::Instance())
}