/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
#pragma pack(push, 1)
namespace DATA
{
struct Fashion
{
    uint32_t      Id;                /// ���
    uint32_t      ClothModelID;      /// ģ��ID
	uint32_t      WeapModelID;       /// ģ��ID
	uint32_t      HairModelID;       /// ģ��ID
	uint32_t      WingModelID;       /// ģ��ID
	uint32_t      ShadowID;          /// ģ��ID
	uint32_t      ClothBigIcon;      /// �·���ͼ����
	uint32_t      WeapBigIcon;       /// �·���ͼ����
	uint32_t      HairBigIcon;       /// �·���ͼ����
	uint32_t      WingBigIcon;       /// �·���ͼ���
	uint8_t       ClothShow;         /// �Ƿ���ʾ�·�
    uint8_t       HairShow;          /// �Ƿ���ʾͷ��
    uint8_t       WeaponsShow;       /// �Ƿ���ʾ����
    uint8_t       WingShow;          /// �Ƿ���ʾ���
    uint8_t       BigIconHairShow;    /// �Ƿ���ʾ�ڹ�ͷ��
    uint8_t       BigIconWeaponsShow; /// �Ƿ���ʾ�ڹ�����
    uint8_t       BigIconWingShow;    /// �Ƿ���ʾ�ڹ۳��
    uint8_t       UseXPAction;        /// �Ƿ������⶯��
	int16_t		WeapOffX;		   /// ����ͼƬ�������Xƫ��
	int16_t		WeapOffY;
	int16_t		HairOffX;			///ͷ��ƫ��
	int16_t		HairOffY;
	int16_t		WingOffX;			///���ƫ��
	int16_t		WingOffY;
	uint32_t		SheildID;			/// ����ģ��ID
	uint8_t		SheildShow;			/// �Ƿ���ʾ����
	uint32_t		SheildBigIcon;		/// ���ƴ�ͼ����
	uint8_t		BigIconSheildShow;	/// �Ƿ���ʾ�ڹ۶���
	int16_t		SheildOffX;			/// ����ƫ��
	int16_t		SheildOffY;			/// 
	uint32_t		HatID;				/// ����ģ��ID
	uint8_t		HatShow;			/// �Ƿ���ʾ����
	uint32_t		HatBigIcon;			/// �����ڹ۴�ͼ��
	uint8_t		BigIconHatShow;		/// �Ƿ���ʾ�ڹ۶���
	int16_t		HatOffX;			/// ����ƫ��
	int16_t		HatOffY;			/// 
};
#pragma pack(pop)


#pragma warning( push )
#pragma warning( disable : 4996 )

class FashionConfig : public TableBase<Fashion>
{
    DECLARE_SINGLETON(FashionConfig);
public:
    virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
    {
        CELL_PARAM_DEFINE;
        CELL_VALUE(InRow, "Id", row->Id, 0);
        CELL_VALUE(InRow, "ClothModelID", row->ClothModelID, 0);
        CELL_VALUE(InRow, "WeapModelID", row->WeapModelID, 0);
        CELL_VALUE(InRow, "HairModelID", row->HairModelID, 0);
        CELL_VALUE(InRow, "WingModelID", row->WingModelID, 0);
        CELL_VALUE(InRow, "ShadowID", row->ShadowID, 0);
        CELL_VALUE(InRow, "ClothBigIcon", row->ClothBigIcon, 0);
        CELL_VALUE(InRow, "WeapBigIcon", row->WeapBigIcon, 0);
        CELL_VALUE(InRow, "HairBigIcon", row->HairBigIcon, 0);
        CELL_VALUE(InRow, "WingBigIcon", row->WingBigIcon, 0);
        CELL_VALUE(InRow, "HairShow", row->HairShow, 0);
        CELL_VALUE(InRow, "WeaponsShow", row->WeaponsShow, 0);
        CELL_VALUE(InRow, "WingShow", row->WingShow, 0);
        CELL_VALUE(InRow, "BigIconHairShow", row->BigIconHairShow, 0);
        CELL_VALUE(InRow, "BigIconWeaponsShow", row->BigIconWeaponsShow, 0);
        CELL_VALUE(InRow, "BigIconWingShow", row->BigIconWingShow, 0);
        CELL_VALUE(InRow, "UseXPAction", row->UseXPAction, 0);
        CELL_VALUE(InRow, "WeapOffX", row->WeapOffX, 0);
        CELL_VALUE(InRow, "WeapOffY", row->WeapOffY, 0);
        CELL_VALUE(InRow, "HairOffX", row->HairOffX, 0);
        CELL_VALUE(InRow, "HairOffY", row->HairOffY, 0);
        CELL_VALUE(InRow, "WingOffX", row->WingOffX, 0);
        CELL_VALUE(InRow, "WingOffY", row->WingOffY, 0);
        CELL_VALUE(InRow, "SheildID", row->SheildID, 0);
        CELL_VALUE(InRow, "SheildShow", row->SheildShow, 0);
        CELL_VALUE(InRow, "SheildBigIcon", row->SheildBigIcon, 0);
        CELL_VALUE(InRow, "SheildOffX", row->SheildOffX, 0);
        CELL_VALUE(InRow, "SheildOffY", row->SheildOffY, 0);
        CELL_VALUE(InRow, "HatID", row->HatID, 0);
        CELL_VALUE(InRow, "HatShow", row->HatShow, 0);
        CELL_VALUE(InRow, "HatBigIcon", row->HatBigIcon, 0);
        CELL_VALUE(InRow, "BigIconHatShow", row->BigIconHatShow, 0);
        CELL_VALUE(InRow, "HatOffX", row->HatOffX, 0);
        CELL_VALUE(InRow, "HatOffY", row->HatOffY, 0);
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

#pragma warning( pop )

#define sFashionConfig (*DATA::FashionConfig::Instance())
}

