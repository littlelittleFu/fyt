#ifndef CXX_JOINHITTABLE_H
#define CXX_JOINHITTABLE_H




class CsvHelper;


enum
{
    JOINHITTYPE_ACTOR = 0,
    JOINHITTYPE_HELPER = 0,
};

namespace DATA
{

    struct JoinHitData
    {
        int ID;
        char Name[96];
        int ActorSkillID;
        int HelperSkillID;

        int ActorDelayTick;
        int HelperDelayTick;

        int ActorStiffTick;
        int HelperStiffTick;

        int HelperAttacToActor;
    };

    class JoinHitConfig : public TableBase<JoinHitData>
    {
        DECLARE_SINGLETON(JoinHitConfig)
    public:
        virtual void FillData(TItem* row, const CSV_HELPER::Row& InRow) override
        {
            CELL_PARAM_DEFINE;
            CELL_VALUE(InRow, "ID", row->ID, 0);
            CELL_VALUE(InRow, "ActorSkillID", row->ActorSkillID, 0);
            CELL_VALUE(InRow, "ActorDelayTick", row->ActorDelayTick, 0);
            CELL_VALUE(InRow, "ActorStiffTick", row->ActorStiffTick, 0);
            CELL_VALUE(InRow, "HelperSkillID", row->HelperSkillID, 0);
            CELL_VALUE(InRow, "HelperDelayTick", row->HelperDelayTick, 0);
            CELL_VALUE(InRow, "HelperStiffTick", row->HelperStiffTick, 0);
            CELL_VALUE(InRow, "HelperAttacToActor", row->HelperAttacToActor, 0);
            CELL_VALUE(InRow, "Name", row->Name, 1);
         }
        virtual void FillMapping(TItem* row) override
        {
            key_id_mappings_[row->ID] = row;
        }
    };
}
#endif