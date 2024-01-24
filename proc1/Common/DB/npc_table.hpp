/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;

namespace DATA
{
struct Npc
{
    uint16_t      Id                     = 0;   /// NPC的ID
    std::string   Name                   = "";  /// NPC名字
    std::string   Subname                = "";  /// NPC称号
    std::string   KeyName                = "";  /// 索引名
    uint32_t      Show                   = 0;   /// 大地图的图片显示
    uint32_t      PicId                  = 0;   /// 头顶图片资源ID
    uint16_t      Model                  = 0;   /// 模型ID
    std::string   Script                 = "";  /// 脚本名
    uint32_t      Speak                  = 0;   /// 语音资源ID
    uint16_t      Path                   = 0;   /// 行走路径ID
    uint8_t       Icontype               = 0;   /// ICON显示
    uint8_t       Configtype             = 0;   /// 初始化时是否要读配置文件
    uint8_t       HasRandomAction        = 0;   /// 是否有第二套随机待机动作
    uint32_t      HalfBody               = 0;   /// NPC的半身像图片
    uint8_t       FixDirection           = 0;   /// 是否固定方向
	int32_t	      NameVerticalOffset     = 0;	/// 名字垂直方向的偏移
    int32_t       NameHorizontalOffset   = 0;   /// 名字水平方向的偏移
	uint32_t	  NameImage              = 0;	/// npc名字图片
	uint32_t	  NameColor              = 0;	/// 名字颜色
	uint8_t       BodySize               = 0;   /// 体形
	int8_t		  XDrawOffset            = 0;	/// NPC在场景中绘制时的X偏移
	int8_t		  YDrawOffset            = 0;	/// NPC在场景中绘制时的Y偏移
	int32_t		  NameVerticalOffsetMobile = 0;	/// 手游名字垂直方向的偏移
	std::string   MobileName             = "";  ///手游名字
	int32_t       HeadPicOffsetY         = 0;	///头顶图片资源垂直方向的偏移

};


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma warning( push )
#pragma warning( disable : 4996 )
#endif

class NpcConfig  : public TableBase<Npc>
{
    DECLARE_SINGLETON(NpcConfig);
public:
    virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
    {
        CELL_PARAM_DEFINE;
        CELL_VALUE(InRow, "Id", row->Id, 0);
        CELL_STRING_VALUE(InRow, "Name", row->Name);
        CELL_STRING_VALUE(InRow, "Subname", row->Subname);
        CELL_STRING_VALUE(InRow, "KeyName", row->KeyName);
        CELL_VALUE(InRow, "Show", row->Show, 0);
        CELL_VALUE(InRow, "PicId", row->PicId, 0);
        CELL_VALUE(InRow, "Model", row->Model, 0);
        CELL_STRING_VALUE(InRow, "Script", row->Script);
        CELL_VALUE(InRow, "Speak", row->Speak, 0);
        CELL_VALUE(InRow, "Path", row->Path, 0);
        CELL_VALUE(InRow, "Icontype", row->Icontype, 0);
        CELL_VALUE(InRow, "Configtype", row->Configtype, 0);
        CELL_VALUE(InRow, "HasRandomAction", row->HasRandomAction, 0);
        CELL_VALUE(InRow, "HalfBody", row->HalfBody, 0);
        CELL_VALUE(InRow, "FixDirection", row->FixDirection, 0);
        CELL_VALUE(InRow, "NameVerticalOffset", row->NameVerticalOffset, 0);
        CELL_VALUE(InRow, "NameHorizontalOffset", row->NameHorizontalOffset, 0);
        CELL_VALUE(InRow, "NameImage", row->NameImage, 0);
        CELL_VALUE(InRow, "NameColor", row->NameColor, 0);
        CELL_VALUE(InRow, "BodySize", row->BodySize, 0);
        CELL_VALUE(InRow, "XDrawOffset", row->XDrawOffset, 0);
        CELL_VALUE(InRow, "YDrawOffset", row->YDrawOffset, 0);
        CELL_VALUE(InRow, "NameVerticalOffsetMObile", row->NameVerticalOffsetMobile, 0);
        CELL_STRING_VALUE(InRow, "MobileNPCName", row->MobileName);
        CELL_VALUE(InRow, "HeadPicOffsetY", row->HeadPicOffsetY, 0);
	}
    virtual bool CheckValid(TItem *row) override
    {
        if (row->Id == 0 || row->KeyName.empty()) return false;
        return true;
    }
    virtual void FillMapping(TItem *row) override
    {
        TKeyIDMapping *t0 = &key_id_mappings_;
        if (t0->find(row->Id) == t0->end())
            (*t0)[row->Id] = 0;
        TItem *&t1 = (*t0)[row->Id];
        t1 = row;
        key_name_mappings_[row->KeyName] = row;
    }
};


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma warning( pop )
#endif
#define sNpcConfig (*DATA::NpcConfig::Instance())
}

