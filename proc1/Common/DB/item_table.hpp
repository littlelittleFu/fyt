/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once


#include <map>
#include <utility>


class CsvHelper;
namespace DATA
{
	struct Item
	{
		bool CheckEnable(int32_t enableType)
		{
			if (Enable.empty()) return false;
			return Enable.find(enableType) != Enable.end();
		}
		int32_t      			Id = 0;							/// ��Ʒ���
		std::string        		Name = "";						/// ����
		std::string        		KeyName = "";					///	��������
		std::string        		Desc = "";						/// ��Ʒ˵��
		int32_t       			Type = 0;                      	/// ������
		int32_t       			SubType = 0;                   	/// ������
		int32_t					WeaponType = 0;					/// ��������
		uint32_t        		Color = 0;                 		/// ������ɫ
		uint64_t      			Icon = 0;                       /// ͼ����
		uint64_t      			BigIcon = 0;               		/// ��ɫģ��ͼƬ
		uint64_t				BigIconEffect = 0;				/// �ڹ���ЧͼƬ
		int32_t      			AvatarMan = 0;                  /// ������
		int32_t      			AvatarWomen = 0;               	/// ����Ů
		int32_t					AvatarEffect = 0;				/// �����Ч
		int32_t					DropEffect = 0;					/// ������Ч	
		int32_t      			Quality = 0;                   	/// Ʒ��	
		int32_t      			Level = 0;                     	/// ʹ�õȼ�
		int32_t       			Gender = 0;                    	/// ʹ���Ա�	
		int32_t       			Job = 0;                       	/// ʹ��ְҵ
		int32_t       			PhyLimit = 0;                  	/// �﹥����
		int32_t       			MagLimit = 0;                  	/// ħ������
		int32_t       			TaoLimit = 0;                  	/// ��������
		int32_t      			Stack = 0;                     	/// ��������
		std::string     		Script = "";               		/// �ű���
		std::set<int32_t>		DropType;						/// ��������		
		int32_t       			HP = 0;                        	/// ����
		int32_t       			MP = 0;                        	/// ħ��
		int32_t       			MaxPhyDef = 0;                 	/// �������
		int32_t       			MinPhyDef = 0;                 	/// �������
		int32_t       			MaxMagDef = 0;                 	/// ħ������
		int32_t       			MinMagDef = 0;                 	/// ħ������
		int32_t       			MaxPhyAtk = 0;                	/// ����������
		int32_t       			MinPhyAtk = 0;                 	/// ����������
		int32_t       			MaxMagAtk = 0;                 	/// ħ������
		int32_t       			MinMagAtk = 0;                 	/// ħ������
		int32_t       			MaxTaoAtk = 0;                 	/// ��������
		int32_t       			MinTaoAtk = 0;                  /// ��������
		int32_t        			Hit = 0;                        /// ׼ȷ(����)
		int32_t        			Miss = 0;                       /// ����(����)
		std::map<int32_t, int32_t>		SpecialAttr;			/// ��������
		int32_t    				SkillId = 0;                    /// ��������
		std::set<int32_t> 		BuffId;                     	/// ��������Я����Buff				
		int32_t      			LS2 = 0;                        /// ��������				
		int32_t       			BindType = 0;					/// ������
		std::set<int32_t>		Enable;							/// �ɲ�������,item_enable_type
		int32_t      			UseCount = 0;					/// ʹ������
		int32_t       			JuJuType = 0;					/// �������
		int32_t      			TimeLimit = 0;					/// ����ʱ��
		int32_t      			TimeType = 0;					/// ʱ������(��Ի��Ǿ���)
		int32_t      			Suit = 0;						/// ��װ���
		int32_t       			BagSize = 0;					/// ��������������
		int32_t       			WarehouseSize = 0;				/// �����ֿ������
		int32_t        			Burst = 0;						/// ������
		int32_t       			AttackSpeed = 0;				/// �����ٶ�
		int32_t       			User = 0;						/// ʹ���߷���
		int32_t					FashionId = 0;					/// ʱװID

		int32_t					Durability = 0;					/// �����;ö�
		int32_t					Track = 0;						/// ����
	};

	class ItemConfig : public TableBase<Item>
	{
	public:
		DECLARE_SINGLETON(ItemConfig);
	public:
		virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
		{
			CELL_PARAM_DEFINE;
			CELL_VALUE(InRow, "Id", row->Id, 0);
			CELL_STRING_VALUE(InRow, "Name", row->Name);
			CELL_STRING_VALUE(InRow, "KeyName", row->KeyName);
			CELL_STRING_VALUE(InRow, "Desc", row->Desc);
			CELL_VALUE(InRow, "Type", row->Type, 0);
			CELL_VALUE(InRow, "SubType", row->SubType, 0);
			CELL_VALUE(InRow, "WeaponType", row->WeaponType, 0);
			CELL_COLOR(InRow, "Color", row->Color);
			CELL_VALUE(InRow, "Icon", row->Icon, 0);
			CELL_VALUE(InRow, "BigIcon", row->BigIcon, 0);
			CELL_VALUE(InRow, "BigIconEffect", row->BigIconEffect, 0);
			CELL_VALUE(InRow, "AvatarMan", row->AvatarMan, 0);
			CELL_VALUE(InRow, "AvatarWomen", row->AvatarWomen, 0);
			CELL_VALUE(InRow, "AvatarEffect", row->AvatarEffect, 0);
			CELL_VALUE(InRow, "DropEffect", row->DropEffect, 0);
			CELL_VALUE(InRow, "Quality", row->Quality, 0);
			CELL_VALUE(InRow, "Level", row->Level, 0);
			CELL_VALUE(InRow, "Gender", row->Gender, 0);
			CELL_VALUE(InRow, "Job", row->Job, 0);
			CELL_VALUE(InRow, "PhyLimit", row->PhyLimit, 0);
			CELL_VALUE(InRow, "MagLimit", row->MagLimit, 0);
			CELL_VALUE(InRow, "TaoLimit", row->TaoLimit, 0);
			CELL_VALUE(InRow, "Stack", row->Stack, 0);
			CELL_STRING_VALUE(InRow, "Script", row->Script);
			SPLIT_CELL_SET_VALUE(InRow, "DropType", "|", row->DropType);
			CELL_VALUE(InRow, "HP", row->HP, 0);
			CELL_VALUE(InRow, "MP", row->MP, 0);
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
			SPLIT_CELL_KEY_VALUE(InRow, "SpecialAttr", "|", ":", row->SpecialAttr);
			CELL_VALUE(InRow, "SkillId", row->SkillId, 0);
			SPLIT_CELL_SET_VALUE(InRow, "BuffId", "|", row->BuffId);
			CELL_VALUE(InRow, "LS2", row->LS2, 0);
			CELL_VALUE(InRow, "BindType", row->BindType, 0);
			SPLIT_CELL_SET_VALUE(InRow, "Enable", "|", row->Enable);
			CELL_VALUE(InRow, "UseCount", row->UseCount, 0);
			CELL_VALUE(InRow, "JuJuType", row->JuJuType, 0);
			CELL_PAIR_INT_VALUE(InRow, "TimeLimit", "|", row->TimeLimit, row->TimeType);
			CELL_VALUE(InRow, "Suit", row->Suit, 0);
			CELL_VALUE(InRow, "BagSize", row->BagSize, 0);
			CELL_VALUE(InRow, "WarehouseSize", row->WarehouseSize, 0);
			CELL_VALUE(InRow, "Burst", row->Burst, 0);
			CELL_VALUE(InRow, "AttackSpeed", row->AttackSpeed, 0);
			CELL_VALUE(InRow, "User", row->User, 0);
			CELL_VALUE(InRow, "FashionId", row->FashionId, 0);
			CELL_VALUE(InRow, "Durability", row->Durability, 0);
			CELL_VALUE(InRow, "Track", row->Track, 0);

			if (row->Stack <= 0 || row->Stack > UINT16_MAX) row->Stack = UINT16_MAX;
		}
		virtual bool CheckValid(TItem *row) override
		{
			if (row->Id == 0 || row->KeyName.empty()) return false;
			return true;
		}
		virtual void FillMapping(TItem* row) override
		{
			TKeyIDMapping* t0 = &key_id_mappings_;
			if (t0->find(row->Id) == t0->end())
				(*t0)[row->Id] = 0;
			TItem*& t1 = (*t0)[row->Id];
			t1 = row;
			key_name_mappings_[row->KeyName] = row;
		}
	};

#define sItemConfig (*DATA::ItemConfig::Instance())
}