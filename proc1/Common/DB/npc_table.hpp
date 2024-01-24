/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;

namespace DATA
{
struct Npc
{
    uint16_t      Id                     = 0;   /// NPC��ID
    std::string   Name                   = "";  /// NPC����
    std::string   Subname                = "";  /// NPC�ƺ�
    std::string   KeyName                = "";  /// ������
    uint32_t      Show                   = 0;   /// ���ͼ��ͼƬ��ʾ
    uint32_t      PicId                  = 0;   /// ͷ��ͼƬ��ԴID
    uint16_t      Model                  = 0;   /// ģ��ID
    std::string   Script                 = "";  /// �ű���
    uint32_t      Speak                  = 0;   /// ������ԴID
    uint16_t      Path                   = 0;   /// ����·��ID
    uint8_t       Icontype               = 0;   /// ICON��ʾ
    uint8_t       Configtype             = 0;   /// ��ʼ��ʱ�Ƿ�Ҫ�������ļ�
    uint8_t       HasRandomAction        = 0;   /// �Ƿ��еڶ��������������
    uint32_t      HalfBody               = 0;   /// NPC�İ�����ͼƬ
    uint8_t       FixDirection           = 0;   /// �Ƿ�̶�����
	int32_t	      NameVerticalOffset     = 0;	/// ���ִ�ֱ�����ƫ��
    int32_t       NameHorizontalOffset   = 0;   /// ����ˮƽ�����ƫ��
	uint32_t	  NameImage              = 0;	/// npc����ͼƬ
	uint32_t	  NameColor              = 0;	/// ������ɫ
	uint8_t       BodySize               = 0;   /// ����
	int8_t		  XDrawOffset            = 0;	/// NPC�ڳ����л���ʱ��Xƫ��
	int8_t		  YDrawOffset            = 0;	/// NPC�ڳ����л���ʱ��Yƫ��
	int32_t		  NameVerticalOffsetMobile = 0;	/// �������ִ�ֱ�����ƫ��
	std::string   MobileName             = "";  ///��������
	int32_t       HeadPicOffsetY         = 0;	///ͷ��ͼƬ��Դ��ֱ�����ƫ��

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

