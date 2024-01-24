/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once

class CsvHelper;

enum BuffGroupRelationInline
{
    BGRI_0 = 0,  // ��������BUFF
    BGRI_1,      // ���Ⱥ�˳������滻(�滻�����)
    BGRI_2,      // ���ȼ��滻
    BGRI_3,      // ˢ��ʱ�䲢���Ӳ���
    BGRI_4,      // ʱ�����
};
enum BuffTimeType
{
    BTT_ASB = 0,    // 0:����ʱ��(ʱ���)
    BTT_RELA ,      // 1:���ʱ��(�ۼ�ʱ��)
};
enum BuffOfflineSaveType
{
    BOST_NOTSAVE = 0,       // 0:������
    BOST_SAVE,              // 1:����
};
enum BuffRoleDieDeleteType
{
    BRDDT_NOTDELETE = 0,       // 0:��ɾ��
    BRDDT_DELETE,              // 1:ɾ��
};
enum BuffRoleMoveDeleteType
{
    BUFF_MOVE_NODELETE = 0,
    BUFF_MOVE_DELETE,
};
namespace DATA
{
	struct Buff
	{
        int32_t             Id = 0;							/// ���
        std::string         Name = "";						/// ����
        std::string         KeyName = "";					/// ������
        uint32_t            Icon = 0;                       /// ͼ��
        int32_t             ShowIcon = 0;                   /// �Ƿ�ui��ʾ(0:����ʾ;1:��ʾ)
        int32_t             Index = 0;                      /// ����
        int32_t             MagicID = 0;                    /// ��ЧID
        std::string         Desc = "";                      /// ����
        int32_t             Type = 0;				        /// buff����
        int32_t             GroupId = 0;				    /// ��id
        int32_t             GroupRelation = 0;			    /// ���ڹ�ϵBuffGroupRelationInline
        int32_t             Stack = 0;						/// ���Ӳ���
        int32_t             Level = 0;						/// �ȼ�
        int32_t             TimeType = 0;					/// ʱ������(0:����ʱ��(ʱ���);1:���ʱ��(�ۼ�ʱ��))BuffTimeType
        int32_t             Interval = 0;			        /// �������(ms)
        int32_t             Duration = 0;					/// ����ʱ��(ms)
        int32_t             TimeFactor = 0;					/// ����ʱ��ϵ��(��ֱ�)
        std::map<int32_t, std::vector<int32_t>> Attr;       /// key:�����ֶ�,value: first����ֵ,second:�ӳ�ϵ��
        std::string         Script = "";			        /// �ص��ű�
        int32_t             OfflineSave = 0;			    /// �Ƿ����߱���BuffOfflineSaveType(0:������;1:����)
        int32_t             DieDelete = 0;					/// ����ɾ��BuffRoleDieDeleteType(0:��ɾ��;1:ɾ��)
        uint8_t             MoveDelete = 0;                 /// �ƶ��Ƿ�ɾ��buff ��0:��ɾ����1:ɾ����
	};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma warning( push )
#pragma warning( disable : 4996 )
#endif

	class BuffConfig  : public TableBase<Buff>
	{
		DECLARE_SINGLETON(BuffConfig);
	public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Id", row->Id, 0);
            CELL_STRING_VALUE(InRow, "Name", row->Name);
            CELL_STRING_VALUE(InRow, "KeyName", row->KeyName);
            CELL_VALUE(InRow, "Icon", row->Icon, 0);
            CELL_VALUE(InRow, "ShowIcon", row->ShowIcon, 0);
            CELL_VALUE(InRow, "Index", row->Index, 0);
            CELL_VALUE(InRow, "MagicID", row->MagicID, 0);
            CELL_STRING_VALUE(InRow, "Desc", row->Desc);
            CELL_VALUE(InRow, "Type", row->Type, 0);
            CELL_VALUE(InRow, "GroupId", row->GroupId, 0);
            CELL_VALUE(InRow, "GroupRelation", row->GroupRelation, 0);
            CELL_VALUE(InRow, "Stack", row->Stack, 0);
            CELL_VALUE(InRow, "Level", row->Level, 0);
            CELL_VALUE(InRow, "TimeType", row->TimeType, 0);
            CELL_VALUE(InRow, "Interval", row->Interval, 0);
            CELL_VALUE(InRow, "Duration", row->Duration, 0);
            CELL_VALUE(InRow, "TimeFactor", row->TimeFactor, 0);
            SPLIT_CELL_KEY_MULTIPLE_VALUE(InRow, "Attr", "|", ";", 3, row->Attr);
            CELL_STRING_VALUE(InRow, "Script", row->Script);
            CELL_VALUE(InRow, "OfflineSave", row->OfflineSave, 0);
            CELL_VALUE(InRow, "DieDelete", row->DieDelete, 0);
            CELL_VALUE(InRow, "MoveDelete", row->MoveDelete, 0);
        }
        virtual bool CheckValid(TItem *row) override
        {
            if (row->Id == 0 || row->KeyName.empty()) return false;
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


#if defined(_WIN32)
#pragma warning( pop )
#endif

#define sBuffConfig (*DATA::BuffConfig::Instance())
}

