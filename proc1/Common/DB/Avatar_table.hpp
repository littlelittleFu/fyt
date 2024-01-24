/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct Avatar
	{
		uint32_t      ID;                          /// ���
		uint8_t       AvatarType;                  /// ģ������
		uint8_t       ModelShow;                   /// �Ƿ���ʾģ��
		uint32_t      ModelID;                     /// ģ��ID
		char        Name[32];                    /// ����
		uint8_t       HpShow;                      /// �Ƿ���ʾѪ��
		uint8_t       ModifyHead;                  /// �Ƿ�ı�ͷ��
		uint32_t      Head;                        /// Сͷ��
		uint8_t       NameShow;                    /// �Ƿ���ʾ����
		uint8_t       ModifyName;                  /// �Ƿ����
		uint8_t       VIPShow;                     /// �Ƿ���ʾVIP
		uint8_t       GuildShow;                   /// �Ƿ���ʾ�л�
		uint8_t       SpouseShow;                  /// �Ƿ���ʾ��ż��Ϣ
		uint8_t       MasterApprenticeShow;        /// �Ƿ���ʾʦͽ��Ϣ
		uint8_t       TitleShow;                   /// �Ƿ���ʾ�ƺ�
		uint8_t       HairShow;                    /// �Ƿ���ʾͷ��
		uint32_t      HairID;                      /// ͷ��ID
		uint8_t       ShadowShow;                  /// �Ƿ���ʾӰ��
		uint32_t      ShadowID;                    /// Ӱ��ID
		uint8_t       WingShow;                    /// �Ƿ���ʾ���
		uint32_t      WingID;                      /// ���ID
		uint8_t       WeaponsShow;                 /// �Ƿ���ʾ����
		uint32_t      WeaponsID;                   /// ����ID
		uint8_t       WeaponType;                  /// ��������
		uint8_t       RightClikMenuShow;           /// �Ҽ��˵��Ƿ���ʾ
		uint32_t      ChangeLevel;                 /// �ȼ��仯
		uint16_t      Bodysize;                    /// ����
		char        Remarks[32];                 /// ��ע
		char        Type[32];                    /// ����
		uint8_t		ShieldShow;				///�Ƿ���ʾ����
		uint32_t	ShieldID;						///����ID
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