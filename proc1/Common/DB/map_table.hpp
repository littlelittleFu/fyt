/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;

enum EMapType
{
    EMT_TOWN = 0,   // �����ͼ
    EMT_DGN,        // ����
};

namespace DATA
{
	struct Map
	{
		uint16_t      Id;                          /// ��ͼ����
		uint8_t       GSIndex;                     /// Game Server����
		char        KeyName[32];                 /// �ؼ�������
		char        Logic[32];                   /// ��ͼ�߼����ļ���
		uint8_t       MapType;                     /// ��ͼ����
		char        Name[32];                    /// ��ͼ����
		char        Script[32];                  /// ��ͼ�ű�
		int32_t       MaxLevel;                    /// �������ȼ�
		int32_t       MinLevel;                    /// ������С�ȼ�
		int32_t       PKMax;                       /// PKֵ�������
		int32_t       PKMin;                       /// PKֵ��С����
		uint8_t       Job;                         /// ְҵ����
		uint8_t       Gender;                      /// �Ա�����
		char        TOffline[32];                /// �����Զ�����
		uint16_t      TX;                          /// ��Ӧ��ͼ��X����
		uint16_t      TY;                          /// ��Ӧ��ͼ��Y����
		char        ItemType[384];               /// ���������
		char        ItemId[512];                 /// ���õ�������
		char        SkillType[384];              /// �����༼��
		char        SkillId[384];                /// ����ID����
		uint8_t       Hero;                        /// �ɷ��ٻ�Ӣ��
		uint8_t       Riding;                      /// �ɷ�����
		uint8_t       Team;                        /// �ɷ����
		uint16_t      LightXr;                     /// ��Ұ��Χ
		uint16_t      LightYr;                     /// ��Ұ��Χ
		uint8_t       BagDrop;                     /// �����Ƿ��а�������
		uint8_t       EquipDrop;                   /// �����Ƿ���װ������
		uint8_t       Talk;                        /// �ɷ�����
		uint8_t       Dropable;                    /// �ɷ�����Ʒ
		uint8_t       Option;                      /// ��������
		uint16_t      ShowUI;                      /// �����ͼ�Ƿ�UI
		uint16_t      BackPic;                     /// ����ͼ��Դ���
		uint16_t      EnterEffect;                 /// ���볡����Ч
		uint16_t      LeftEffect;                  /// �뿪������Ч
		uint32_t      MiniMap;                     /// ����ͼ��ԴID
		uint8_t       CanTalk;                     /// ��ֹ����
		uint8_t       KillPk;                      /// ɱ���Ƿ�����PKֵ
		uint8_t       CrossHuman;                  /// �Ƿ�������
		uint8_t       CrossMonster;                /// �Ƿ�������
		uint8_t       Ride;                        /// �Ƿ���������
		uint8_t       Mask;                        /// �Ƿ�������
		char        CustomMiniMap[96];           /// С��ͼ��
		uint32_t		MapBg;
		uint8_t       ShowBigThumbnail;
		char		SoundInfo[64];
		uint8_t		AddKillerToBlackList;		//�Ƿ�ѻ�ɱ�ҵ���Ҽӵ�������
        uint8_t     AutoPickItem;               /// �Ƿ��Զ�����
	};


	class MapConfig : public TableBase<Map>
	{
		DECLARE_SINGLETON(MapConfig);
	public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Id", row->Id, 0);
            CELL_VALUE(InRow, "GSIndex", row->GSIndex, 0);
            CELL_VALUE(InRow, "Name", row->Name, 1);
            CELL_VALUE(InRow, "KeyName", row->KeyName, 1);
            CELL_VALUE(InRow, "Script", row->Script, 1);
            CELL_VALUE(InRow, "Logic", row->Logic, 1);
            CELL_VALUE(InRow, "MapType", row->MapType, 0);
            CELL_VALUE(InRow, "MaxLevel", row->MaxLevel, 0);
            CELL_VALUE(InRow, "MinLevel", row->MinLevel, 0);
            CELL_VALUE(InRow, "PKMax", row->PKMax, 0);
            CELL_VALUE(InRow, "PKMin", row->PKMin, 0);
            CELL_VALUE(InRow, "Job", row->Job, 0);
            CELL_VALUE(InRow, "Gender", row->Gender, 0);
            CELL_VALUE(InRow, "TOffline", row->TOffline, 1);
            CELL_VALUE(InRow, "TX", row->TX, 0);
            CELL_VALUE(InRow, "TY", row->TY, 0);
            CELL_VALUE(InRow, "ItemType", row->ItemType, 1);
            CELL_VALUE(InRow, "ItemId", row->ItemId, 1);
            CELL_VALUE(InRow, "SkillType", row->SkillType, 1);
            CELL_VALUE(InRow, "SkillId", row->SkillId, 1);
            CELL_VALUE(InRow, "Hero", row->Hero, 0);
            CELL_VALUE(InRow, "Riding", row->Riding, 0);
            CELL_VALUE(InRow, "Team", row->Team, 0);
            CELL_VALUE(InRow, "LightXr", row->LightXr, 0);
            CELL_VALUE(InRow, "LightYr", row->LightYr, 0);
            CELL_VALUE(InRow, "BagDrop", row->BagDrop, 0);
            CELL_VALUE(InRow, "EquipDrop", row->EquipDrop, 0);
            CELL_VALUE(InRow, "Talk", row->Talk, 0);
            CELL_VALUE(InRow, "Dropable", row->Dropable, 0);
            CELL_VALUE(InRow, "Option", row->Option, 0);
            CELL_VALUE(InRow, "ShowUI", row->ShowUI, 0);
            CELL_VALUE(InRow, "BackPic", row->BackPic, 0);
            CELL_VALUE(InRow, "EnterEffect", row->EnterEffect, 0);
            CELL_VALUE(InRow, "LeftEffect", row->LeftEffect, 0);
            CELL_VALUE(InRow, "MiniMap", row->MiniMap, 0);
            CELL_VALUE(InRow, "CanTalk", row->CanTalk, 0);
            CELL_VALUE(InRow, "KillPk", row->KillPk, 0);
            CELL_VALUE(InRow, "CrossHuman", row->CrossHuman, 0);
            CELL_VALUE(InRow, "CrossMonster", row->CrossMonster, 0);
            CELL_VALUE(InRow, "Ride", row->Ride, 0);
            CELL_VALUE(InRow, "Mask", row->Mask, 0);
            CELL_VALUE(InRow, "CustomMiniMap", row->CustomMiniMap, 1);
            CELL_VALUE(InRow, "ShowBigThumbnail", row->ShowBigThumbnail, 0);
            CELL_VALUE(InRow, "SoundInfo", row->SoundInfo, 1);
            CELL_VALUE(InRow, "MapBg", row->MapBg, 0);
            CELL_VALUE(InRow, "PKeffectsocial", row->AddKillerToBlackList, 0);
            CELL_VALUE(InRow, "AutoPickItem", row->AutoPickItem, 0);
        }

        virtual bool CheckValid(TItem *row) override
        {
            if (row->Id == 0 || row->KeyName[0] == 0) return false;
            return true;
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


#define sMapConfig (*DATA::MapConfig::Instance())
}