/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct Vipshop
	{
		uint16_t      Id;                          /// ��ˮ��
		char        Name[32];                    /// ����
		uint8_t       Type;                        /// ����
		uint32_t      Icon;                        /// ��ťͼ��
		uint32_t      Dicon;                       /// չʾСͼ��
		uint32_t      Index;                       /// �������
		uint8_t       Level;                       /// ���ܵȼ�
		char        desc[384];                   /// ��������
		uint32_t      Price;                       /// �۸�
		uint32_t      Time;                        /// �������ʱ��
		char        Script[32];                  /// �ű�����
		uint8_t       NotSell;                     /// �Ƿ��¼�
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