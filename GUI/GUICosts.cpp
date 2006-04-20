#include "OptionsForm.h"
#include "../Engine/SimOptions.h"
#include "../Engine/Block.h"

void OptionsFormDialogBox::CostsOptions(FXTabBook *TabBook)
{
    FXTabItem *CostsTab=new FXTabItem(TabBook,"&Costs",NULL);
    FXPacker *CostsPacker=new FXPacker(TabBook,FRAME_THICK|FRAME_RAISED);

    FXMatrix *CostsUberAllesMatrix = new FXMatrix(CostsPacker, 1,
        MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *CostsMasterMatrix = new FXMatrix(CostsUberAllesMatrix, 2 ,MATRIX_BY_ROWS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    new FXLabel(CostsMasterMatrix, "DNA Type:", NULL);
    FXMatrix *DNAEntryMatrix = new FXMatrix(CostsMasterMatrix, 3, MATRIX_BY_COLUMNS);
    {
        #define NEWCOSTSFIELD(name, arrayindex, caption) \
            new FXLabel(DNAEntryMatrix,name,NULL); \
            new FXTextField(DNAEntryMatrix,7,new FXDataTarget(TmpOpts.Costs[arrayindex]),FXDataTarget::ID_VALUE, \
            TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW); \
            new FXLabel(DNAEntryMatrix, caption, NULL);

        NEWCOSTSFIELD("Numbers", btValue, "nrg/cycle/instance");
        NEWCOSTSFIELD("*Numbers", btPointer, "nrg/cycle/instance");
        NEWCOSTSFIELD("Basic Commands", btBasicCommand, "nrg/cycle/instance");
        NEWCOSTSFIELD("Advanced Commands", btAdvancedCommand, "nrg/cycle/instance");
        NEWCOSTSFIELD("Bitwise Commands", btBitwiseCommand, "nrg/cycle/instance");
        NEWCOSTSFIELD("Conditions", btCondition, "nrg/cycle/instance");
        NEWCOSTSFIELD("Logic Operators", btLogic, "nrg/cycle/instance");
        NEWCOSTSFIELD("Stores", btStores, "nrg/cycle/instance");
        NEWCOSTSFIELD("Flow Commands", btFlow, "nrg/cycle/instance");
        
        #undef NEWCOSTSFIELD
    }

    new FXLabel(CostsMasterMatrix, "Miscelaneous:", NULL);
    FXMatrix *MiscEntryMatrix = new FXMatrix(CostsMasterMatrix, 3, MATRIX_BY_COLUMNS);
    {
        #define NEWCOSTSFIELD(name, arrayindex, caption) \
            new FXLabel(MiscEntryMatrix,name,NULL); \
            new FXTextField(MiscEntryMatrix,7,new FXDataTarget(TmpOpts.Costs[arrayindex]),FXDataTarget::ID_VALUE, \
            TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW); \
            new FXLabel(MiscEntryMatrix, caption, NULL);

        NEWCOSTSFIELD("Translational Bang", MOVECOST, "nrg/bang");
        NEWCOSTSFIELD("Turning", TURNCOST, "nrg/bang");
        NEWCOSTSFIELD("Tieing", TIECOST, "nrg to fire");
        NEWCOSTSFIELD("Shooting", SHOTCOST, "nrg to fire");
        NEWCOSTSFIELD("Body Upkeep", BODYUPKEEP, "nrg/body/cycle");
        NEWCOSTSFIELD("DNA Upkeep", BPCYCCOST, "nrg/bp/cycle");
        NEWCOSTSFIELD("DNA Copy Cost", BPCOPYCOST, "nrg/bp");
        NEWCOSTSFIELD("Venom Cost", VENOMCOST, "nrg/constructed");
        NEWCOSTSFIELD("Poison Cost", POISONCOST, "nrg/constructed");
        NEWCOSTSFIELD("Slime Cost", SLIMECOST, "nrg/constructed");
        NEWCOSTSFIELD("Shell Cost", SHELLCOST, "nrg/unit constructed");
        
        #undef NEWCOSTSFIELD
    }

    FXMatrix *CostsToolbar = new FXMatrix(CostsUberAllesMatrix, 1,
        MATRIX_BY_ROWS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    {
        new FXButton(CostsToolbar, "All 0s", NULL, this, ID_CLEARCOSTS);
        new FXButton(CostsToolbar, "F1 Default", NULL, this, ID_COSTSF1DEFAULT);
        new FXButton(CostsToolbar, "Decent Guess", NULL, this, ID_COSTSGUESS);
    }


}

long OptionsFormDialogBox::onClearCosts(FXObject *, FXSelector, void *)
{
    memset(TmpOpts.Costs, 0, sizeof(TmpOpts.Costs));
    return 1;
}

long OptionsFormDialogBox::onCostsF1Default(FXObject *, FXSelector, void *)
{
    onClearCosts(NULL, 0, NULL);
    TmpOpts.Costs[btStores] = 0.04f;
    TmpOpts.Costs[btCondition] = 0.004f;
    TmpOpts.Costs[MOVECOST] = 0.05f;
    TmpOpts.Costs[TIECOST] = 2.0f;
    TmpOpts.Costs[SHOTCOST] = 2.0f;
    TmpOpts.Costs[VENOMCOST] = 
    TmpOpts.Costs[SLIMECOST] = 
    TmpOpts.Costs[POISONCOST] = 
    TmpOpts.Costs[SHELLCOST] = 1.0f;

    return 1;
}

long OptionsFormDialogBox::onCostsDecentGuess(FXObject *, FXSelector, void *)
{
    onClearCosts(NULL, 0, NULL);
    TmpOpts.Costs[btValue] = .004f;
    TmpOpts.Costs[btLogic] = .004f;
    TmpOpts.Costs[btBitwiseCommand] = .004f;
    TmpOpts.Costs[btAdvancedCommand] = .004f;
    TmpOpts.Costs[btBasicCommand] = .004f;
    TmpOpts.Costs[btPointer] = .004f;
    TmpOpts.Costs[btLogic] = .004f;
    TmpOpts.Costs[btCondition] = .004f;
    TmpOpts.Costs[btStores] = .04f;
    TmpOpts.Costs[btFlow] = .004f;

    TmpOpts.Costs[MOVECOST] =
    TmpOpts.Costs[TURNCOST] = 0.05f;

    TmpOpts.Costs[VENOMCOST] = 
    TmpOpts.Costs[SLIMECOST] = 
    TmpOpts.Costs[POISONCOST] = 
    TmpOpts.Costs[SHELLCOST] = 1.0f;

    TmpOpts.Costs[BPCOPYCOST] = 0.1f;
    TmpOpts.Costs[TIECOST] = 2.0f;
    TmpOpts.Costs[SHOTCOST] = 2.0f;

    TmpOpts.Costs[BODYUPKEEP] = .00001f;
    TmpOpts.Costs[BPCYCCOST] = .001f;

    return 1;
}