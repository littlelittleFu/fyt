/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct Castle
	{
		char        Name[32];                    /// �Ǳ���
		char        DstMap[32];                  /// �Ǳ����ڵ�ͼ
		char        BasilicaMap[32];             /// �ʹ���ͼ
		char        ReliveMap[32];               /// ������ͼ
		uint16_t      ReliveX;                     /// �����X����
		uint16_t      ReliveY;                     /// �����Y����
		uint16_t      ReliveR;                     /// �����뾶
	};


	class CastleConfig : public TableBase<Castle>
	{
		DECLARE_SINGLETON(CastleConfig);
    public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Name", row->Name, 1);
            CELL_VALUE(InRow, "DstMap", row->DstMap, 1);
            CELL_VALUE(InRow, "BasilicaMap", row->BasilicaMap, 1);
            CELL_VALUE(InRow, "ReliveMap", row->ReliveMap, 1);
            CELL_VALUE(InRow, "ReliveX", row->ReliveX, 0);
            CELL_VALUE(InRow, "ReliveY", row->ReliveY, 0);
            CELL_VALUE(InRow, "ReliveR", row->ReliveR, 0);
        }

        virtual void FillMapping(TItem* row) override
        {
            key_name_mappings_[row->Name] = row;
        }
	};


#define sCastleConfig (*DATA::CastleConfig::Instance())
}