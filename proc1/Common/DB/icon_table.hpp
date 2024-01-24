/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;

namespace DATA
{
struct Icon
{
    unsigned short      IconID;                      /// Í¼±êID
    unsigned int      ImageID1;                    /// Í¼Æ¬1
    unsigned short      Param1;                      /// ²ÎÊý1
    unsigned short      Left1;                       /// ×ó1
    unsigned short      Top1;                        /// ¶¥1
    unsigned short      Right1;                      /// ÓÒ1
    unsigned int      Bottom1;                     /// µ×1
    unsigned int      ImageID2;                    /// Í¼Æ¬2
    unsigned short      Param2;                      /// ²ÎÊý2
    unsigned short      Left2;                       /// ×ó2
    unsigned short      Top2;                        /// ¶¥2
    unsigned short      Right2;                      /// ÓÒ2
    unsigned int      Bottom2;                     /// µ×2
    unsigned int      ImageID3;                    /// Í¼Æ¬3
    unsigned short      Param3;                      /// ²ÎÊý3
    unsigned short      Left3;                       /// ×ó3
    unsigned short      Top3;                        /// ¶¥3
    unsigned short      Right3;                      /// ÓÒ3
    unsigned int      Bottom3;                     /// µ×3
    unsigned int      ImageID4;                    /// Í¼Æ¬4
    unsigned short      Param4;                      /// ²ÎÊý4
    unsigned short      Left4;                       /// ×ó4
    unsigned short      Top4;                        /// ¶¥4
    unsigned short      Right4;                      /// ÓÒ4
    unsigned int      Bottom4;                     /// µ×4
    unsigned int      ImageID5;                    /// Í¼Æ¬5
    unsigned short      Param5;                      /// ²ÎÊý5
    unsigned short      Left5;                       /// ×ó5
    unsigned short      Top5;                        /// ¶¥5
    unsigned short      Right5;                      /// ÓÒ5
    unsigned int      Bottom5;                     /// µ×5
    char        Text[50];                    /// ÎÄ×Ö
};


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma warning( push )
#pragma warning( disable : 4996 )
#endif

class IconConfig : public TableBase<Icon>
{
    DECLARE_SINGLETON(IconConfig);
public:
    virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
    {
        CELL_PARAM_DEFINE;
        CELL_VALUE(InRow, "IconID", row->IconID, 0);
        CELL_VALUE(InRow, "ImageID1", row->ImageID1, 0);
        CELL_VALUE(InRow, "Param1", row->Param1, 0);
        CELL_VALUE(InRow, "Left1", row->Left1, 0);
        CELL_VALUE(InRow, "Top1", row->Top1, 0);
        CELL_VALUE(InRow, "Right1", row->Right1, 0);
        CELL_VALUE(InRow, "Bottom1", row->Bottom1, 0);
        CELL_VALUE(InRow, "ImageID2", row->ImageID2, 0);
        CELL_VALUE(InRow, "Param2", row->Param2, 0);
        CELL_VALUE(InRow, "Left2", row->Left2, 0);
        CELL_VALUE(InRow, "Top2", row->Top2, 0);
        CELL_VALUE(InRow, "Right2", row->Right2, 0);
        CELL_VALUE(InRow, "Bottom2", row->Bottom2, 0);
        CELL_VALUE(InRow, "ImageID3", row->ImageID3, 0);
        CELL_VALUE(InRow, "Param3", row->Param3, 0);
        CELL_VALUE(InRow, "Left3", row->Left3, 0);
        CELL_VALUE(InRow, "Top3", row->Top3, 0);
        CELL_VALUE(InRow, "Right3", row->Right3, 0);
        CELL_VALUE(InRow, "Bottom3", row->Bottom3, 0);
        CELL_VALUE(InRow, "ImageID4", row->ImageID4, 0);
        CELL_VALUE(InRow, "Param4", row->Param4, 0);
        CELL_VALUE(InRow, "Left4", row->Left4, 0);
        CELL_VALUE(InRow, "Top4", row->Top4, 0);
        CELL_VALUE(InRow, "Right4", row->Right4, 0);
        CELL_VALUE(InRow, "Bottom4", row->Bottom4, 0);
        CELL_VALUE(InRow, "ImageID5", row->ImageID5, 0);
        CELL_VALUE(InRow, "Param5", row->Param5, 0);
        CELL_VALUE(InRow, "Left5", row->Left5, 0);
        CELL_VALUE(InRow, "Top5", row->Top5, 0);
        CELL_VALUE(InRow, "Right5", row->Right5, 0);
        CELL_VALUE(InRow, "Bottom5", row->Bottom5, 0);
        CELL_VALUE(InRow, "Text", row->Text, 1);
    }

    virtual void FillMapping(TItem* row) override
    {
        TKeyIDMapping *t0 = &key_id_mappings_;
        if (t0->find(row->IconID) == t0->end())
            (*t0)[row->IconID] = 0;
        TItem *&t1 = (*t0)[row->IconID];
        t1 = row;
    }
};


#if defined(_WIN32)
#pragma warning( pop )
#endif
#define sIconConfig (*DATA::IconConfig::Instance())
}

