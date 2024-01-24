/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;
namespace DATA
{
	struct Hero
	{
		uint32_t      Level;                       /// ��ǰ�ȼ�
		uint8_t       Job;                         /// ְҵ
		uint64_t      UpgradeExp;                  /// ��������
		uint32_t      HP;                          /// ��������
		uint32_t      MP;                          /// ����ħ��
		uint16_t      Weight;                      /// ���ñ�������
		uint16_t      EquipWeight;                 /// ����װ������
		uint16_t      Brawn;                       /// ��������
		uint32_t      MaxPhyDef;                   /// �����������
		uint32_t      MinPhyDef;                   /// �����������
		uint32_t      MaxMagDef;                   /// ����ħ������
		uint32_t      MinMagDef;                   /// ����ħ������
		uint32_t      MaxPhyAtk;                   /// ���ù���������
		uint32_t      MinPhyAtk;                   /// ���ù���������
		uint32_t      MaxMagAtk;                   /// ����ħ������
		uint32_t      MinMagAtk;                   /// ����ħ������
		uint32_t      MaxTaoAtk;                   /// ���õ�������
		uint32_t      MinTaoAtk;                   /// ���õ�������
		uint32_t      Hit;                         /// ����׼ȷ�����У�
		uint32_t      Miss;                        /// �������ݣ����ܣ�
		uint8_t       LC;                          /// ��������/����
		uint8_t       Burst;                       /// ���ñ�����
		uint16_t      Poison;                      /// �����ж� �ظ��ٶ�
		uint16_t      HPRec;                       /// ���������ظ��ٶ�
		uint16_t      MPRec;                       /// ����ħ���ظ��ٶ�
		uint32_t      Interval;                    /// �ظ����
		uint16_t      MoveSpeed;                   /// �ƶ��ٶ�
		uint16_t      AttackSpeed;                 /// ��ͨ�����ٶ�
		uint32_t      HeroXp;                      /// ŭ��
		uint32_t      HeroXpMax;                   /// ŭ������
	};


	class HeroConfig : public TableBase<Hero>
	{
		DECLARE_SINGLETON(HeroConfig);
	public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Level", row->Level, 0);
            CELL_VALUE(InRow, "Job", row->Job, 0);
            CELL_VALUE(InRow, "UpgradeExp", row->UpgradeExp, 0);
            CELL_VALUE(InRow, "HP", row->HP, 0);
            CELL_VALUE(InRow, "MP", row->MP, 0);
            CELL_VALUE(InRow, "Weight", row->Weight, 0);
            CELL_VALUE(InRow, "EquipWeight", row->EquipWeight, 0);
            CELL_VALUE(InRow, "Brawn", row->Brawn, 0);
            CELL_VALUE(InRow, "MaxPhyDef", row->MaxPhyDef, 0);
            CELL_VALUE(InRow, "MinPhyDef", row->MinPhyDef, 0);
            CELL_VALUE(InRow, "MaxMagDef", row->MaxMagDef, 0);
            CELL_VALUE(InRow, "MinMagDef", row->MinMagDef, 0);
            CELL_VALUE(InRow, "MaxPhyAtk", row->MaxPhyAtk, 0);
            CELL_VALUE(InRow, "MinPhyAtk", row->MinPhyAtk, 0);
            CELL_VALUE(InRow, "MaxMagAtk", row->MaxMagAtk, 0);
            CELL_VALUE(InRow, "MinMagAtk", row->MinMagAtk, 0);
            CELL_VALUE(InRow, "MaxTaoAtk", row->MaxTaoAtk, 0);
            CELL_VALUE(InRow, "MinTaoAtk", row->MinTaoAtk, 0);
            CELL_VALUE(InRow, "Hit", row->Hit, 0);
            CELL_VALUE(InRow, "Miss", row->Miss, 0);
            CELL_VALUE(InRow, "LC", row->LC, 0);
            CELL_VALUE(InRow, "Burst", row->Burst, 0);
            CELL_VALUE(InRow, "Poison", row->Poison, 0);
            CELL_VALUE(InRow, "HPRec", row->HPRec, 0);
            CELL_VALUE(InRow, "MPRec", row->MPRec, 0);
            CELL_VALUE(InRow, "Interval", row->Interval, 0);
            CELL_VALUE(InRow, "MoveSpeed", row->MoveSpeed, 0);
            CELL_VALUE(InRow, "AttackSpeed", row->AttackSpeed, 0);
            CELL_VALUE(InRow, "HeroXp", row->HeroXp, 0);
            CELL_VALUE(InRow, "HeroXpMax", row->HeroXpMax, 0);
		}
        virtual void FillMapping(TItem *row) override
        {
            uint32_t keyId = (row->Level << 16) | row->Job;
            key_id_mappings_[keyId] = row;
        }
        TItem *Get(uint16_t Level, uint16_t Job)
        {
            uint32_t keyId = (Level << 16) | Job;

            if (key_id_mappings_.find(keyId) == key_id_mappings_.end())
                return 0;
            return key_id_mappings_[keyId];
        }
        bool Has(uint16_t Level, uint16_t Job)
        {
            uint32_t keyId = (Level << 16) | Job;

            if (key_id_mappings_.find(keyId) == key_id_mappings_.end())
                return false;
            return true;
        }
	};


#define sHeroConfig (*DATA::HeroConfig::Instance())
}