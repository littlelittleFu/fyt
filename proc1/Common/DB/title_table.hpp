/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct Title
	{
		uint32_t     Id;                          /// ID
		char         Name[32];                    /// ����
		char         KeyName[32];                 /// ������
        uint16_t     type;                        /// ����
        uint32_t     Icon;                        /// ͼƬ���
        uint32_t     BigIconEffect;               /// �ڹ���Чͼ
        uint32_t     Effect;                      /// �����Ч
		uint8_t      Size;                        /// ���ṹλ��
		uint8_t      Priority;                    /// ���ȼ�
		uint8_t      Unique;                      /// ȫ��Ψһ
		uint16_t     BuffID;                      /// BUFFID
		uint8_t      MergeDel;                    /// �Ϸ��Ƿ�ɾ��
		char         Tips[296];                   /// ����
		char         TipsSource[296];             /// �ƺ���Դ����
		uint8_t      TetelShow;                   /// �Ƿ����δ��óƺ���ʾ
		uint8_t      Color;                       /// ������ɫ
		uint8_t      HasShowName;                 /// �Ƿ���ʾͷ���γƺ�
		uint32_t     TimeLimit;                   /// ����ʱ��
		uint8_t      UseAbsTime;                  /// ����ʱ������ʱ��
		char	     ColorString[96];             /// ��ɫ
        uint32_t     HP;                          /// ����
        uint32_t     MP;                          /// ħ��
        uint32_t     MinPhyDef;                   /// �������
        uint32_t     MaxPhyDef;                   /// �������
        uint32_t     MinMagDef;                   /// ħ������
        uint32_t     MaxMagDef;                   /// ħ������
        uint32_t     MinPhyAtk;                   /// ����������
        uint32_t     MaxPhyAtk;                   /// ����������
        uint32_t     MinMagAtk;                   /// ħ������
        uint32_t     MaxMagAtk;                   /// ħ������
        uint32_t     MinTaoAtk;                   /// ��������
        uint32_t     MaxTaoAtk;                   /// ��������
        uint32_t     Hit;                         /// ����׼ȷ
        uint32_t     Miss;                        /// ��������
        std::map<int,int> SpecialAttr;            /// ��������
        uint32_t     SkillId;                     /// ��������ID

	};


	class TitleConfig : public TableBase<Title>
	{
		DECLARE_SINGLETON(TitleConfig);
    public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Id", row->Id, 0);
            CELL_VALUE(InRow, "Name", row->Name, 1);
            CELL_VALUE(InRow, "KeyName", row->KeyName, 1);
            CELL_VALUE(InRow, "type", row->type, 0);
            CELL_VALUE(InRow, "Icon", row->Icon, 0);
            CELL_VALUE(InRow, "BigIconEffect", row->BigIconEffect, 0);
            CELL_VALUE(InRow, "Effect", row->Effect, 0);
            CELL_VALUE(InRow, "Size", row->Size, 0);
            CELL_VALUE(InRow, "Priority", row->Priority, 0);
            CELL_VALUE(InRow, "Unique", row->Unique, 0);
            CELL_VALUE(InRow, "BuffId", row->BuffID, 0);
            CELL_VALUE(InRow, "MergeDel", row->MergeDel, 0);
            CELL_VALUE(InRow, "Tips", row->Tips, 1);
            CELL_VALUE(InRow, "TipsSource", row->TipsSource, 1);
            CELL_VALUE(InRow, "TetelShow", row->TetelShow, 0);
            CELL_VALUE(InRow, "Color", row->Color, 0);
            CELL_VALUE(InRow, "HasShowName", row->HasShowName, 0);
            CELL_VALUE(InRow, "TimeLimit", row->TimeLimit, 0);
            CELL_VALUE(InRow, "UseAbsTime", row->UseAbsTime, 0);
            CELL_VALUE(InRow, "ColorString", row->ColorString, 1);
            CELL_VALUE(InRow, "HP", row->HP, 0);
            CELL_VALUE(InRow, "MP", row->MP, 0);
            CELL_VALUE(InRow, "MinPhyDef", row->MinPhyDef, 0);
            CELL_VALUE(InRow, "MaxPhyDef", row->MaxPhyDef, 0);
            CELL_VALUE(InRow, "MinMagDef", row->MinMagDef, 0);
            CELL_VALUE(InRow, "MaxMagDef", row->MaxMagDef, 0);
            CELL_VALUE(InRow, "MinPhyAtk", row->MinPhyAtk, 0);
            CELL_VALUE(InRow, "MaxPhyAtk", row->MaxPhyAtk, 0);
            CELL_VALUE(InRow, "MinMagAtk", row->MinMagAtk, 0);
            CELL_VALUE(InRow, "MaxMagAtk", row->MaxMagAtk, 0);
            CELL_VALUE(InRow, "MinTaoAtk", row->MinTaoAtk, 0);
            CELL_VALUE(InRow, "MaxTaoAtk", row->MaxTaoAtk, 0);
            CELL_VALUE(InRow, "Hit", row->Hit, 0);
            CELL_VALUE(InRow, "Miss", row->Miss, 0);
            SPLIT_CELL_KEY_VALUE(InRow, "SpecialAttr", "|", ":", row->SpecialAttr);
            CELL_VALUE(InRow, "SkillId", row->SkillId, 0);
        }

        virtual void FillMapping(TItem* row) override
        {
            TKeyIDMapping *t0 = &key_id_mappings_;
            if (t0->find(row->Id) == t0->end())
                (*t0)[row->Id] = 0;
            TItem *&t1 = (*t0)[row->Id];
            t1 = row;
            key_name_mappings_[row->KeyName] = row;
        }
	};


#define sTitleConfig (*DATA::TitleConfig::Instance())
}