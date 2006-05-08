#include <fx.h>
#include "OptionsForm.h"
#include "..\Engine\Mutations.h"

int mode;
FXDataTarget CurrentMutationMode(mode);

class SpeciesMutationsDialogBox : public FXDialogBox
{
    FXDECLARE(SpeciesMutationsDialogBox)

    public:
    
    //SpeciesMutationsDialogBox::SpeciesMutationsDialogBox(Mutationprobs *MutateMe);

    void hide()
    {
        FXDialogBox::hide();
    }

    void show(FXuint placement)
    {
        /*SpeciesList->clearItems();
        for (int x = 0; x < 50; x++)
        {
            if(!strcmp(TmpOpts.Specie[x].Name.c_str(), ""))
                break;
            SpeciesList->appendItem(TmpOpts.Specie[x].Name.c_str());
            ReConnectToSpecies(0);
        }*/

        FXDialogBox::show(placement);
    }

    long onChangeMode(FXObject *, FXSelector, void *);

    enum
    {
        ID_CHANGEMODE = FXDialogBox::ID_LAST,

        ID_LAST
    };
};

FXDEFMAP(SpeciesMutationsDialogBox) SpeciesMutationsDialogBoxMap[] = {
    FXMAPFUNC(SEL_COMMAND, SpeciesMutationsDialogBox::ID_CHANGEMODE,     SpeciesMutationsDialogBox::onChangeMode)
};

long OptionsFormDialogBox::onMutationsSpecies(FXObject *, FXSelector, void *)
{
    FXDialogBox *MutationsBox = new FXDialogBox(this, "Species Mutation Options", DECOR_TITLE|DECOR_BORDER,
        0,0,0,0, 0,0,0,0, 0,0);

    FXMatrix *LayoutMatrix = new FXMatrix(MutationsBox, 1, MATRIX_BY_COLUMNS);
    {
        //First row: mutation type selector and description frame
        FXMatrix *MutationTypeAndDetailsMatrix = new FXMatrix(LayoutMatrix, 1, MATRIX_BY_ROWS | LAYOUT_FILL_ALL,
            0,0,0,0,
            0,0,0,0);
        {
            //Mutation type matrix            
            FXMatrix *MutationsTypeMatrix = new FXMatrix(MutationTypeAndDetailsMatrix, 1, MATRIX_BY_COLUMNS);
            {
                #define BUTTON_STUFF(option) \
                    &CurrentMutationMode, FXDataTarget::ID_OPTION + option, BUTTON_NORMAL | LAYOUT_FILL_X
                
                //Per Cycle mutations
                FXGroupBox *MutationsPerCycleFrame = new FXGroupBox(MutationsTypeMatrix, "Per Cycle",
                    FRAME_RIDGE | LAYOUT_FILL_ALL);
                {
                    new FXButton(MutationsPerCycleFrame, "Point", NULL, BUTTON_STUFF(PointUP));
                    new FXButton(MutationsPerCycleFrame, "Delta", NULL, BUTTON_STUFF(DeltaUP));
                }

                //Per Reproduction mutations
                FXGroupBox *MutationsPerReproFrame = new FXGroupBox(MutationsTypeMatrix, "Per Reproduction",
                    FRAME_RIDGE | LAYOUT_FILL_ALL);
                {
                    new FXButton(MutationsPerReproFrame, "Copy Error", NULL, BUTTON_STUFF(CopyErrorUP));
                    new FXButton(MutationsPerReproFrame, "Translocation", NULL, BUTTON_STUFF(TranslocationUP));
                    new FXButton(MutationsPerReproFrame, "Reversal", NULL, BUTTON_STUFF(ReversalUP));
                    new FXButton(MutationsPerReproFrame, "Amplification", NULL, BUTTON_STUFF(AmplificationUP));
                    new FXButton(MutationsPerReproFrame, "Insertion", NULL, BUTTON_STUFF(InsertionUP));
                    new FXButton(MutationsPerReproFrame, "Deletion", NULL, BUTTON_STUFF(DeletionUP));
                }
                #undef BUTTON_STUFF
            }

            FXMatrix *MutationsDetailsMatrix = new FXMatrix(MutationTypeAndDetailsMatrix, 1,
                MATRIX_BY_COLUMNS | LAYOUT_FILL_ALL);
            {
                FXGroupBox *MutationsDetailsFrame = new FXGroupBox(MutationsDetailsMatrix, "Details",
                    FRAME_RIDGE | LAYOUT_FILL_ALL);
                {
                    new FXText(MutationsDetailsFrame, NULL, 0, FRAME_RIDGE | LAYOUT_FILL_X);

                    FXMatrix *EnabledAndChanceMatrix = 
                        new FXMatrix(MutationsDetailsFrame, 1, MATRIX_BY_ROWS | LAYOUT_FILL_X);
                    {
                        new FXCheckButton(EnabledAndChanceMatrix, "Mutation Enabled", NULL, 0);//,
                            //LAYOUT_FILL_ALL | JUSTIFY_LEFT);
                        
                        new FXLabel(EnabledAndChanceMatrix, "1 in ");
                        
                        new FXTextField(EnabledAndChanceMatrix, 9);

                        new FXLabel(EnabledAndChanceMatrix, "per cycle");
                    }

                    FXMatrix *ChangeMeanMatrix = 
                        new FXMatrix(MutationsDetailsFrame, 1, MATRIX_BY_ROWS | LAYOUT_FILL_X);

                    {
                        new FXLabel(ChangeMeanMatrix, "Mean Length");
                        new FXHorizontalSeparator(ChangeMeanMatrix, LAYOUT_FILL_X|LAYOUT_FILL_COLUMN);
                        new FXTextField(ChangeMeanMatrix, 9, NULL, 0,
                            JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT);
                    }

                    FXMatrix *ChangeStdDevMatrix = 
                        new FXMatrix(MutationsDetailsFrame, 1, MATRIX_BY_ROWS | LAYOUT_FILL_X);
                    {
                        new FXLabel(ChangeStdDevMatrix, "Standard Deviation");
                        new FXHorizontalSeparator(ChangeStdDevMatrix, LAYOUT_FILL_X|LAYOUT_FILL_COLUMN);
                        new FXTextField(ChangeStdDevMatrix, 9, NULL, 0,
                            JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT);
                    }

                    FXMatrix *ChangeTypeOrValueMatrix = 
                        new FXMatrix(MutationsDetailsFrame, 1, MATRIX_BY_ROWS | LAYOUT_FILL_X);
                    {
                        new FXLabel(ChangeTypeOrValueMatrix, "Change Type");

                        (new FXRealSlider(ChangeTypeOrValueMatrix, NULL, 0, SLIDER_NORMAL | LAYOUT_FILL_ALL))->setRange(0, 1);
                        
                        new FXLabel(ChangeTypeOrValueMatrix, "Change Value");
                    }                    

                    FXGroupBox *ApproximateChancesFrame = new FXGroupBox(MutationsDetailsFrame,
                        "Approximate Mutation Chances", FRAME_RIDGE | LAYOUT_FILL_ALL);
                    {                    
                        FXMatrix *PerCycleMatrix = 
                            new FXMatrix(ApproximateChancesFrame, 1, MATRIX_BY_ROWS | LAYOUT_FILL_X);
                        {
                            new FXLabel(PerCycleMatrix, "1 in ");

                            new FXTextField(PerCycleMatrix, 12);
                        
                            new FXLabel(PerCycleMatrix, "per cycle");
                        }

                        FXMatrix *PerReproMatrix = 
                            new FXMatrix(ApproximateChancesFrame, 1, MATRIX_BY_ROWS | LAYOUT_FILL_X);
                        {
                            new FXLabel(PerReproMatrix, "1 in ");

                            new FXTextField(PerReproMatrix, 12);
                        
                            new FXLabel(PerReproMatrix, "per BP replication");
                        }

                        FXMatrix *PerRepro2Matrix = 
                            new FXMatrix(ApproximateChancesFrame, 1, MATRIX_BY_ROWS | LAYOUT_FILL_X);
                        {
                            new FXLabel(PerRepro2Matrix, "1 in ");

                            new FXTextField(PerRepro2Matrix, 12);
                        
                            new FXLabel(PerRepro2Matrix, "per bot per reproduction");
                        }
                    }                    
                }
            }
        }

        //Third Row: "Toolbar"
        FXGroupBox *ToolbarFrame = new FXGroupBox(LayoutMatrix,
                NULL, FRAME_RIDGE | LAYOUT_FILL_ALL);
        {
            FXMatrix *ToolbarMatrix = new FXMatrix(ToolbarFrame, 1, MATRIX_BY_ROWS | LAYOUT_FILL_ALL);
            {
                new FXCheckButton(ToolbarMatrix, "Enable Mutations");
                //new FXHorizontalSeparator(ToolbarMatrix);
                new FXButton(ToolbarMatrix, "Cancel");
                new FXButton(ToolbarMatrix, "Apply to Bots in World");
                new FXButton(ToolbarMatrix, "Apply to Species Template");
            }
        }        
    }

    MutationsBox->execute(PLACEMENT_OWNER);
    delete MutationsBox;

    return 1;
}
