/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct Avatar
	{
		uint32_t      ID;                          /// 编号
		uint8_t       AvatarType;                  /// 模型类型
		uint8_t       ModelShow;                   /// 是否显示模型
		uint32_t      ModelID;                     /// 模型ID
		char        Name[32];                    /// 名称
		uint8_t       HpShow;                      /// 是否显示血条
		uint8_t       ModifyHead;                  /// 是否改变头像
		uint32_t      Head;                        /// 小头像
		uint8_t       NameShow;                    /// 是否显示名称
		uint8_t       ModifyName;                  /// 是否改名
		uint8_t       VIPShow;                     /// 是否显示VIP
		uint8_t       GuildShow;                   /// 是否显示行会
		uint8_t       SpouseShow;                  /// 是否显示配偶信息
		uint8_t       MasterApprenticeShow;        /// 是否显示师徒信息
		uint8_t       TitleShow;                   /// 是否显示称号
		uint8_t       HairShow;                    /// 是否显示头发
		uint32_t      HairID;                      /// 头发ID
		uint8_t       ShadowShow;                  /// 是否显示影子
		uint32_t      ShadowID;                    /// 影子ID
		uint8_t       WingShow;                    /// 是否显示翅膀
		uint32_t      WingID;                      /// 翅膀ID
		uint8_t       WeaponsShow;                 /// 是否显示武器
		uint32_t      WeaponsID;                   /// 武器ID
		uint8_t       WeaponType;                  /// 武器类型
		uint8_t       RightClikMenuShow;           /// 右键菜单是否显示
		uint32_t      ChangeLevel;                 /// 等级变化
		uint16_t      Bodysize;                    /// 体型
		char        Remarks[32];                 /// 备注
		char        Type[32];                    /// 类型
		uint8_t		ShieldShow;				///是否显示盾牌
		uint32_t	ShieldID;						///盾牌ID
	};


	class AvatarConfig : public TableBase<Avatar>
	{
		DECLARE_SINGLETON(AvatarConfig);
    public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "ID", row->ID, 0);
            CELL_VALUE(InRow, "Name", row->Name, 1);
            CELL_VALUE(InRow, "Remarks", row->Remarks, 1);
            CELL_VALUE(InRow, "Type", row->Type, 1);
            CELL_VALUE(InRow, "AvatarType", row->AvatarType, 0);
            CELL_VALUE(InRow, "ModelShow", row->ModelShow, 0);
            CELL_VALUE(InRow, "ModelID", row->ModelID, 0);
            CELL_VALUE(InRow, "HpShow", row->HpShow, 0);
            CELL_VALUE(InRow, "ModifyHead", row->ModifyHead, 0);
            CELL_VALUE(InRow, "Head", row->Head, 0);
            CELL_VALUE(InRow, "NameShow", row->NameShow, 0);
            CELL_VALUE(InRow, "ModifyName", row->ModifyName, 0);
            CELL_VALUE(InRow, "VIPShow", row->VIPShow, 0);
            CELL_VALUE(InRow, "GuildShow", row->GuildShow, 0);
            CELL_VALUE(InRow, "SpouseShow", row->SpouseShow, 0);
            CELL_VALUE(InRow, "MasterApprenticeShow", row->MasterApprenticeShow, 0);
            CELL_VALUE(InRow, "TitleShow", row->TitleShow, 0);
            CELL_VALUE(InRow, "HairShow", row->HairShow, 0);
            CELL_VALUE(InRow, "HairID", row->HairID, 0);
            CELL_VALUE(InRow, "ShadowShow", row->ShadowShow, 0);
            CELL_VALUE(InRow, "ShadowID", row->ShadowID, 0);
            CELL_VALUE(InRow, "WingShow", row->WingShow, 0);
            CELL_VALUE(InRow, "WingID", row->WingID, 0);
            CELL_VALUE(InRow, "WeaponsShow", row->WeaponsShow, 0);
            CELL_VALUE(InRow, "WeaponsID", row->WeaponsID, 0);
            CELL_VALUE(InRow, "WeaponType", row->WeaponType, 0);
            CELL_VALUE(InRow, "RightClikMenuShow", row->RightClikMenuShow, 0);
            CELL_VALUE(InRow, "ChangeLevel", row->ChangeLevel, 0);
            CELL_VALUE(InRow, "Bodysize", row->Bodysize, 0);
            CELL_VALUE(InRow, "ShieldShow", row->ShieldShow, 0);
            CELL_VALUE(InRow, "ShieldID", row->ShieldID, 0);
        }

        virtual void FillMapping(TItem* row) override
        {
            TKeyIDMapping *t0 = &key_id_mappings_;
            if (t0->find(row->ID) == t0->end())
                (*t0)[row->ID] = 0;
            TItem *&t1 = (*t0)[row->ID];
            t1 = row;
        }
	};


#define sAvatarConfig (*DATA::AvatarConfig::Instance())
}