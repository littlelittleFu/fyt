/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
#pragma pack(push, 1)
namespace DATA
{
struct Fashion
{
    uint32_t      Id;                /// 编号
    uint32_t      ClothModelID;      /// 模型ID
	uint32_t      WeapModelID;       /// 模型ID
	uint32_t      HairModelID;       /// 模型ID
	uint32_t      WingModelID;       /// 模型ID
	uint32_t      ShadowID;          /// 模型ID
	uint32_t      ClothBigIcon;      /// 衣服大图标编号
	uint32_t      WeapBigIcon;       /// 衣服大图标编号
	uint32_t      HairBigIcon;       /// 衣服大图标编号
	uint32_t      WingBigIcon;       /// 衣服大图标编
	uint8_t       ClothShow;         /// 是否显示衣服
    uint8_t       HairShow;          /// 是否显示头发
    uint8_t       WeaponsShow;       /// 是否显示武器
    uint8_t       WingShow;          /// 是否显示翅膀
    uint8_t       BigIconHairShow;    /// 是否显示内观头发
    uint8_t       BigIconWeaponsShow; /// 是否显示内观武器
    uint8_t       BigIconWingShow;    /// 是否显示内观翅膀
    uint8_t       UseXPAction;        /// 是否有特殊动作
	int16_t		WeapOffX;		   /// 武器图片相对身体X偏移
	int16_t		WeapOffY;
	int16_t		HairOffX;			///头发偏移
	int16_t		HairOffY;
	int16_t		WingOffX;			///翅膀偏移
	int16_t		WingOffY;
	uint32_t		SheildID;			/// 盾牌模型ID
	uint8_t		SheildShow;			/// 是否显示盾牌
	uint32_t		SheildBigIcon;		/// 盾牌大图标编号
	uint8_t		BigIconSheildShow;	/// 是否显示内观盾牌
	int16_t		SheildOffX;			/// 盾牌偏移
	int16_t		SheildOffY;			/// 
	uint32_t		HatID;				/// 斗笠模型ID
	uint8_t		HatShow;			/// 是否显示斗笠
	uint32_t		HatBigIcon;			/// 斗笠内观大图标
	uint8_t		BigIconHatShow;		/// 是否显示内观斗笠
	int16_t		HatOffX;			/// 斗笠偏移
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

