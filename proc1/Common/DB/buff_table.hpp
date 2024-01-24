/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once

class CsvHelper;

enum BuffGroupRelationInline
{
    BGRI_0 = 0,  // 无视新增BUFF
    BGRI_1,      // 按先后顺序进行替换(替换最早的)
    BGRI_2,      // 按等级替换
    BGRI_3,      // 刷新时间并增加层数
    BGRI_4,      // 时间叠加
};
enum BuffTimeType
{
    BTT_ASB = 0,    // 0:绝对时间(时间戳)
    BTT_RELA ,      // 1:相对时间(累计时长)
};
enum BuffOfflineSaveType
{
    BOST_NOTSAVE = 0,       // 0:不保存
    BOST_SAVE,              // 1:保存
};
enum BuffRoleDieDeleteType
{
    BRDDT_NOTDELETE = 0,       // 0:不删除
    BRDDT_DELETE,              // 1:删除
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
        int32_t             Id = 0;							/// 编号
        std::string         Name = "";						/// 名称
        std::string         KeyName = "";					/// 索引名
        uint32_t            Icon = 0;                       /// 图标
        int32_t             ShowIcon = 0;                   /// 是否ui显示(0:不显示;1:显示)
        int32_t             Index = 0;                      /// 序列
        int32_t             MagicID = 0;                    /// 特效ID
        std::string         Desc = "";                      /// 描述
        int32_t             Type = 0;				        /// buff类型
        int32_t             GroupId = 0;				    /// 组id
        int32_t             GroupRelation = 0;			    /// 组内关系BuffGroupRelationInline
        int32_t             Stack = 0;						/// 叠加层数
        int32_t             Level = 0;						/// 等级
        int32_t             TimeType = 0;					/// 时间类型(0:绝对时间(时间戳);1:相对时间(累计时长))BuffTimeType
        int32_t             Interval = 0;			        /// 触发间隔(ms)
        int32_t             Duration = 0;					/// 持续时间(ms)
        int32_t             TimeFactor = 0;					/// 持续时间系数(万分比)
        std::map<int32_t, std::vector<int32_t>> Attr;       /// key:属性字段,value: first属性值,second:加成系数
        std::string         Script = "";			        /// 回调脚本
        int32_t             OfflineSave = 0;			    /// 是否下线保存BuffOfflineSaveType(0:不保存;1:保存)
        int32_t             DieDelete = 0;					/// 死亡删除BuffRoleDieDeleteType(0:不删除;1:删除)
        uint8_t             MoveDelete = 0;                 /// 移动是否删除buff （0:不删除，1:删除）
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

