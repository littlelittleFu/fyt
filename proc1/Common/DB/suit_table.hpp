/// Generate by table_gen tools, PLEASE DO NOT EDIT IT!

#pragma once




class CsvHelper;

namespace DATA
{
	struct Suit
	{
		uint16_t      Id;                          /// 物品编号
		char        Name[20];                    /// 名称
		char        KeyName[20];                 /// 索引名称
        uint16_t      SuitGroup;                   //套装组
        uint16_t      SuitLevel;                    //套装组内等级
        uint8_t       AttSize0;                    //激活需求套装件数
        int32_t       SuitBuffID;                  //套装buff
		uint8_t       AttSize1;                    /// 激活需求套装件数
        uint16_t       Att1;                        /// Att1
		int32_t       AttValue1;                   /// Att值1
		uint8_t       AttSize2;                    /// 激活需求套装件数
		uint16_t      Att2;                        /// Att2
		int32_t       AttValue2;                   /// Att值2
		uint8_t       AttSize3;                    /// 激活需求套装件数
		uint16_t      Att3;                        /// Att3
		int32_t       AttValue3;                   /// Att值3
		uint8_t       AttSize4;                    /// 激活需求套装件数
		uint16_t      Att4;                        /// Att4
		int32_t       AttValue4;                   /// Att值4
		uint8_t       AttSize5;                    /// 激活需求套装件数
		uint16_t      Att5;                        /// Att5
		int32_t       AttValue5;                   /// Att值5
		uint8_t       AttSize6;                    /// 激活需求套装件数
        uint16_t       Att6;                        /// Att6
		int32_t       AttValue6;                   /// Att值6
		uint8_t       AttSize7;                    /// 激活需求套装件数
		uint16_t      Att7;                        /// Att7
		int32_t       AttValue7;                   /// Att值7
		uint8_t       AttSize8;                    /// 激活需求套装件数
		uint16_t      Att8;                        /// Att8
		int32_t       AttValue8;                   /// Att值8
		uint8_t       AttSize9;                    /// 激活需求套装件数
		uint16_t      Att9;                        /// Att9
		int32_t       AttValue9;                   /// Att值9
		uint8_t       AttSize10;                   /// 激活需求套装件数
		uint16_t      Att10;                       /// Att10
		int32_t       AttValue10;                  /// Att值10
		uint8_t       AttSize11;                   /// 激活需求套装件数
		uint16_t      Att11;                       /// Att11
		int32_t       AttValue11;                  /// Att值11
		uint8_t       AttSize12;                   /// 激活需求套装件数
		uint16_t      Att12;                       /// Att12
		int32_t       AttValue12;                  /// Att值12
		uint8_t       AttSize13;                   /// 激活需求套装件数
		uint16_t      Att13;                       /// Att13
		int32_t       AttValue13;                  /// Att值13
		uint8_t       AttSize14;                   /// 激活需求套装件数
		uint16_t      Att14;                       /// Att14
		int32_t       AttValue14;                  /// Att值14
		uint8_t       AttSize15;                   /// 激活需求套装件数
		uint16_t      Att15;                       /// Att15
		int32_t       AttValue15;                  /// Att值15
		uint8_t       AttSize16;                   /// 激活需求套装件数
		uint16_t      Att16;                       /// Att16
		int32_t       AttValue16;                  /// Att值16
		uint8_t       AttSize17;                   /// 激活需求套装件数
		uint16_t      Att17;                       /// Att17
		int32_t       AttValue17;                  /// Att值17
		uint8_t       AttSize18;                   /// 激活需求套装件数
		uint16_t      Att18;                       /// Att18
		int32_t       AttValue18;                  /// Att值18
		uint8_t       AttSize19;                   /// 激活需求套装件数
		uint16_t      Att19;                       /// Att19
		int32_t       AttValue19;                  /// Att值19
		uint8_t       AttSize20;                   /// 激活需求套装件数
		uint16_t      Att20;                       /// Att20
		int32_t       AttValue20;                  /// Att值20
		uint8_t       AttSize21;                   /// 激活需求套装件数
		uint16_t      Att21;                       /// Att21
		int32_t       AttValue21;                  /// Att值21
		uint8_t       AttSize22;                   /// 激活需求套装件数
		uint16_t      Att22;                       /// Att22
		int32_t       AttValue22;                  /// Att值22
		uint8_t       AttSize23;                   /// 激活需求套装件数
		uint16_t      Att23;                       /// Att23
		int32_t       AttValue23;                  /// Att值23
		uint8_t       AttSize24;                   /// 激活需求套装件数
		uint16_t      Att24;                       /// Att24
		int32_t       AttValue24;                  /// Att值24
		uint8_t       AttSize25;                   /// 激活需求套装件数
		uint16_t      Att25;                       /// Att25
		int32_t       AttValue25;                  /// Att值25
		uint8_t       ESize1;                      /// 需求激活件数
		uint16_t      E1;                          /// 武器位置发光特效
		uint8_t       ESize2;                      /// 需求激活件数
		uint16_t      E2;                          /// 衣服位置发光特效
		uint8_t       ESize3;                      /// 需求激活件数
		uint16_t      E3;                          /// 马蹄位置发光特效
		uint8_t       SuitCountType;               /// 计算套装件数类型
	};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	#pragma warning( push )
	#pragma warning( disable : 4996 )
#endif


	class SuitConfig : public TableBase<Suit>
	{
		DECLARE_SINGLETON(SuitConfig);
    private:
        std::unordered_map<uint16_t, std::unordered_map<uint16_t, uint16_t>>   data_;
    public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "Id", row->Id, 0);
            CELL_VALUE(InRow, "Name", row->Name, 1);
            CELL_VALUE(InRow, "KeyName", row->KeyName, 1);
            CELL_VALUE(InRow, "SuitGroup", row->SuitGroup, 0);
            CELL_VALUE(InRow, "SuitLevel", row->SuitLevel, 0);
            CELL_VALUE(InRow, "AttSize0", row->AttSize0, 0);
            CELL_VALUE(InRow, "SuitBuffID", row->SuitBuffID, 0);
            CELL_VALUE(InRow, "AttSize1", row->AttSize1, 0);
            CELL_VALUE(InRow, "Att1", row->Att1, 0);
            CELL_VALUE(InRow, "AttValue1", row->AttValue1, 0);
            CELL_VALUE(InRow, "AttSize2", row->AttSize2, 0);
            CELL_VALUE(InRow, "Att2", row->Att2, 0);
            CELL_VALUE(InRow, "AttValue2", row->AttValue2, 0);
            CELL_VALUE(InRow, "AttSize3", row->AttSize3, 0);
            CELL_VALUE(InRow, "Att3", row->Att3, 0);
            CELL_VALUE(InRow, "AttValue3", row->AttValue3, 0);
            CELL_VALUE(InRow, "AttSize4", row->AttSize4, 0);
            CELL_VALUE(InRow, "Att4", row->Att4, 0);
            CELL_VALUE(InRow, "AttValue4", row->AttValue4, 0);
            CELL_VALUE(InRow, "AttSize5", row->AttSize5, 0);
            CELL_VALUE(InRow, "Att5", row->Att5, 0);
            CELL_VALUE(InRow, "AttValue5", row->AttValue5, 0);
            CELL_VALUE(InRow, "AttSize6", row->AttSize6, 0);
            CELL_VALUE(InRow, "Att6", row->Att6, 0);
            CELL_VALUE(InRow, "AttValue6", row->AttValue6, 0);
            CELL_VALUE(InRow, "AttSize7", row->AttSize7, 0);
            CELL_VALUE(InRow, "Att7", row->Att7, 0);
            CELL_VALUE(InRow, "AttValue7", row->AttValue7, 0);
            CELL_VALUE(InRow, "AttSize8", row->AttSize8, 0);
            CELL_VALUE(InRow, "Att8", row->Att8, 0);
            CELL_VALUE(InRow, "AttValue8", row->AttValue8, 0);
            CELL_VALUE(InRow, "AttSize9", row->AttSize9, 0);
            CELL_VALUE(InRow, "Att9", row->Att9, 0);
            CELL_VALUE(InRow, "AttValue9", row->AttValue9, 0);
            CELL_VALUE(InRow, "AttSize10", row->AttSize10, 0);
            CELL_VALUE(InRow, "Att10", row->Att10, 0);
            CELL_VALUE(InRow, "AttValue10", row->AttValue10, 0);
            CELL_VALUE(InRow, "AttSize11", row->AttSize11, 0);
            CELL_VALUE(InRow, "Att11", row->Att11, 0);
            CELL_VALUE(InRow, "AttValue11", row->AttValue11, 0);
            CELL_VALUE(InRow, "AttSize12", row->AttSize12, 0);
            CELL_VALUE(InRow, "Att12", row->Att12, 0);
            CELL_VALUE(InRow, "AttValue12", row->AttValue12, 0);
            CELL_VALUE(InRow, "AttSize13", row->AttSize13, 0);
            CELL_VALUE(InRow, "Att13", row->Att13, 0);
            CELL_VALUE(InRow, "AttValue13", row->AttValue13, 0);
            CELL_VALUE(InRow, "AttSize14", row->AttSize14, 0);
            CELL_VALUE(InRow, "Att14", row->Att14, 0);
            CELL_VALUE(InRow, "AttValue14", row->AttValue14, 0);
            CELL_VALUE(InRow, "AttSize15", row->AttSize15, 0);
            CELL_VALUE(InRow, "Att15", row->Att15, 0);
            CELL_VALUE(InRow, "AttValue15", row->AttValue15, 0);
            CELL_VALUE(InRow, "AttSize16", row->AttSize16, 0);
            CELL_VALUE(InRow, "Att16", row->Att16, 0);
            CELL_VALUE(InRow, "AttValue16", row->AttValue16, 0);
            CELL_VALUE(InRow, "AttSize17", row->AttSize17, 0);
            CELL_VALUE(InRow, "Att17", row->Att17, 0);
            CELL_VALUE(InRow, "AttValue17", row->AttValue17, 0);
            CELL_VALUE(InRow, "AttSize18", row->AttSize18, 0);
            CELL_VALUE(InRow, "Att18", row->Att18, 0);
            CELL_VALUE(InRow, "AttValue18", row->AttValue18, 0);
            CELL_VALUE(InRow, "AttSize19", row->AttSize19, 0);
            CELL_VALUE(InRow, "Att19", row->Att19, 0);
            CELL_VALUE(InRow, "AttValue19", row->AttValue19, 0);
            CELL_VALUE(InRow, "AttSize20", row->AttSize20, 0);
            CELL_VALUE(InRow, "Att20", row->Att20, 0);
            CELL_VALUE(InRow, "AttValue20", row->AttValue20, 0);
            CELL_VALUE(InRow, "AttSize21", row->AttSize21, 0);
            CELL_VALUE(InRow, "Att21", row->Att21, 0);
            CELL_VALUE(InRow, "AttValue21", row->AttValue21, 0);
            CELL_VALUE(InRow, "AttSize22", row->AttSize22, 0);
            CELL_VALUE(InRow, "Att22", row->Att22, 0);
            CELL_VALUE(InRow, "AttValue22", row->AttValue22, 0);
            CELL_VALUE(InRow, "AttSize23", row->AttSize23, 0);
            CELL_VALUE(InRow, "Att23", row->Att23, 0);
            CELL_VALUE(InRow, "AttValue23", row->AttValue23, 0);
            CELL_VALUE(InRow, "AttSize24", row->AttSize24, 0);
            CELL_VALUE(InRow, "Att24", row->Att24, 0);
            CELL_VALUE(InRow, "AttValue24", row->AttValue24, 0);
            CELL_VALUE(InRow, "AttSize25", row->AttSize25, 0);
            CELL_VALUE(InRow, "Att25", row->Att25, 0);
            CELL_VALUE(InRow, "AttValue25", row->AttValue25, 0);
            CELL_VALUE(InRow, "ESize1", row->ESize1, 0);
            CELL_VALUE(InRow, "E1", row->E1, 0);
            CELL_VALUE(InRow, "ESize2", row->ESize2, 0);
            CELL_VALUE(InRow, "E2", row->E2, 0);
            CELL_VALUE(InRow, "ESize3", row->ESize3, 0);
            CELL_VALUE(InRow, "E3", row->E3, 0);
            CELL_VALUE(InRow, "SuitCountType", row->SuitCountType, 0);
            data_[row->SuitGroup][row->SuitLevel] = row->Id;
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
        std::unordered_map<uint16_t, uint16_t> GetMapByGroup(uint16_t group)
        {
            return  data_[group];
        }
	};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma warning( pop )
#endif

#define sSuitConfig (*DATA::SuitConfig::Instance())
}

