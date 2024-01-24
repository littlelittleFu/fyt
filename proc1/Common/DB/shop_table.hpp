/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct Shop
	{
		uint16_t      Id;                          /// 商店编号
		uint32_t      Icon;                        /// 商店名字
		char        Name[32];                    /// 中文备注
		uint8_t       Index;                       /// 商品序号
		char        ItemKeyName[32];             /// 道具索引名
		uint8_t       NotSell;                     /// 是否上架
		uint16_t      ItemNum;                     /// 商品数量
		uint32_t      Time;                        /// 刷新时间
		uint32_t      Discount;                    /// 价格折扣
	};


	class ShopConfig : public TableBase<Shop>
	{
		DECLARE_SINGLETON(ShopConfig);



	public:
        virtual ~ShopConfig()
        {
            Release();
        }

        virtual void Release()
        {
            for (auto &it : key_id_mappings_key_id_mappings_) {
                auto &mapping = it.second;
                if (mapping) delete mapping;
            }

            TableBase<Shop>::Release();
        }

        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Id", row->Id, 0);
            CELL_VALUE(InRow, "Icon", row->Icon, 0);
            CELL_VALUE(InRow, "Name", row->Name, 1);
            CELL_VALUE(InRow, "ItemKeyName", row->ItemKeyName, 1);
            CELL_VALUE(InRow, "Index", row->Index, 0);
            CELL_VALUE(InRow, "NotSell", row->NotSell, 0);
            CELL_VALUE(InRow, "ItemNum", row->ItemNum, 0);
            CELL_VALUE(InRow, "Time", row->Time, 0);
            CELL_VALUE(InRow, "Discount", row->Discount, 0);
        }
        virtual bool CheckValid(TItem *row) override
        {
            if (row->Id == 0 || row->Index == 0) return false;
            return true;
        }
        virtual void FillMapping(TItem *row) override
        {
          /*  uint32_t keyId = (row->Id << 16) | row->Index;
            key_id_mappings_[keyId] = row;*/

            auto* t0 = &key_id_mappings_key_id_mappings_;
            if (t0->find(row->Id) == t0->end())
                (*t0)[row->Id] = new TKeyIDMapping();
            auto & t1 = (*t0)[row->Id];

            if (t1->find(row->Index) == t1->end())
                (*t1)[row->Index] = 0;
            auto *& t2 = (*t1)[row->Index];
            t2 = row;
        }

        TKeyIDMapping* GetShop(uint16_t Id)
        {
            auto * t0 = &key_id_mappings_key_id_mappings_;

            if (t0->find(Id) == t0->end())
                return 0;
           auto *& t1 = (*t0)[Id];
           return t1;
        }

        TItem *Get(uint16_t Id, uint16_t Index)
        {
            uint32_t keyId = (Id << 16) | Index;

            if (key_id_mappings_.find(keyId) == key_id_mappings_.end())
                return 0;
            return key_id_mappings_[keyId];
        }
        bool Has(uint16_t Id, uint16_t Index)
        {
            uint32_t keyId = (Id << 16) | Index;

            if (key_id_mappings_.find(keyId) == key_id_mappings_.end())
                return false;
            return true;
        }
	};


#define sShopConfig (*DATA::ShopConfig::Instance())
}