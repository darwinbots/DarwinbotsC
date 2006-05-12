/*************************************************************************
The coding style of the options forms is very much in flux.
The goal is to make them as readable and maintainable as possible.

For this reason, especially with regards to data targets, some probably
non kosher methods might lead to minor memory leaks, among other things.

-Numsgil May 6 2006
***************************************************************************/

#include "OptionsForm.h"


FXIMPLEMENT(OptionsFormDialogBox, FXDialogBox,
    OptionsFormDialogBoxMap, ARRAYNUMBER(OptionsFormDialogBoxMap))

OptionsFormDialogBox::OptionsFormDialogBox(FXComposite *parent) : 
    FXDialogBox(parent, "Sim Options", DECOR_TITLE | DECOR_BORDER),
    currentMutationMode(mode)
{
    FXMatrix *LayoutMatrix = new FXMatrix(this, 1, MATRIX_BY_COLUMNS |
        LAYOUT_FILL_X | LAYOUT_FILL_Y | LAYOUT_FILL_ROW | LAYOUT_FILL_COLUMN,
        0,0,0,0,
        0,0,0,0);
    
    FXTabBook *tabbook=new FXTabBook(LayoutMatrix,NULL,0,
        LAYOUT_FILL_X | LAYOUT_FILL_Y | LAYOUT_FILL_ROW | LAYOUT_FILL_COLUMN);
    
    Species(tabbook);
    General(tabbook);
    Veggy(tabbook);
    PhysicsAndCosts(tabbook);
    CostsOptions(tabbook);
    Mutations(tabbook);
    //ReststartAndL(tabbook);
    //InternetOptions(tabbook);
    //Recording(tabbook);
    
    BottomToolbar(LayoutMatrix);
}

void OptionsFormDialogBox::BottomToolbar(FXMatrix *LayoutMatrix)
{
    FXGroupBox *ButtonGroup=new FXGroupBox(LayoutMatrix,NULL,FRAME_RIDGE | LAYOUT_FILL_X | LAYOUT_FILL_ROW);
    FXMatrix *ButtonMatrix = new FXMatrix(ButtonGroup, 1, MATRIX_BY_ROWS | LAYOUT_FILL_X | LAYOUT_FILL_ROW,
        0,0,0,0,0,0,0,0);
    
    new FXButton(ButtonMatrix, "Load Settings", 0, this, OptionsFormDialogBox::ID_LOADSETTINGS);
    new FXButton(ButtonMatrix, "Save Settings", 0, this, OptionsFormDialogBox::ID_SAVESETTINGS);
    
    new FXSeparator(ButtonMatrix, LAYOUT_FILL_X|LAYOUT_FILL_COLUMN);
    new FXButton(ButtonMatrix, "Cancel", 0, this, FXDialogBox::ID_CANCEL);
    new FXSeparator(ButtonMatrix, LAYOUT_FILL_X|LAYOUT_FILL_COLUMN);
    
    new FXButton(ButtonMatrix, "Pause", 0, NULL, 0);
    new FXButton(ButtonMatrix, "Start New", 0, this, OptionsFormDialogBox::ID_STARTNEW);
    new FXButton(ButtonMatrix, "Change", 0, this, OptionsFormDialogBox::ID_CHANGE);
}

long OptionsFormDialogBox::onChange(FXObject *, FXSelector, void *)
{
    SimOpts = TmpOpts;
    this->hide();
    return 1;
}

long OptionsFormDialogBox::onStartNew(FXObject *, FXSelector, void *)
{
    EngineThread.cancel();
    SimOpts = TmpOpts;
    EngineThread.start();
    this->hide();
    return 1;
}

long OptionsFormDialogBox::onSaveSettings(FXObject *, FXSelector, void *)
{
    WriteSett(Engine.MainDir() + "\\settings\\savesett.set", TmpOpts);
    return 1;
}

long OptionsFormDialogBox::onLoadSettings(FXObject *, FXSelector, void *)
{
    ReadSett(Engine.MainDir() + "\\settings\\savesett.set", TmpOpts);
    SpeciesList->clearItems(true);
    for(int x = 0; x < (int)TmpOpts.SpeciesNum; x++)
        SpeciesList->appendItem(TmpOpts.Specie[x].Name.c_str());

    SpeciesList->setCurrentItem(0);
    onSelectNewSpecies(NULL, 0, NULL);
    return 1;
}

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
                //Per Cycle mutations
                FXGroupBox *MutationsPerCycleFrame = new FXGroupBox(MutationsTypeMatrix, "Per Cycle",
                    FRAME_RIDGE | LAYOUT_FILL_ALL);
                {
                    new FXButton(MutationsPerCycleFrame, "Point", NULL,&currentMutationMode,FXDataTarget::ID_OPTION + PointUP,BUTTON_NORMAL|LAYOUT_FILL_X);
                    new FXButton(MutationsPerCycleFrame, "Delta", NULL,&currentMutationMode,FXDataTarget::ID_OPTION + DeltaUP,BUTTON_NORMAL|LAYOUT_FILL_X);
                }

                //Per Reproduction mutations
                FXGroupBox *MutationsPerReproFrame = new FXGroupBox(MutationsTypeMatrix, "Per Reproduction",
                    FRAME_RIDGE | LAYOUT_FILL_ALL);
                {
                    new FXButton(MutationsPerReproFrame,"Copy Error"   ,NULL,&currentMutationMode,FXDataTarget::ID_OPTION + CopyErrorUP    ,BUTTON_NORMAL|LAYOUT_FILL_X);
                    new FXButton(MutationsPerReproFrame,"Translocation",NULL,&currentMutationMode,FXDataTarget::ID_OPTION + TranslocationUP,BUTTON_NORMAL|LAYOUT_FILL_X);
                    new FXButton(MutationsPerReproFrame,"Reversal"     ,NULL,&currentMutationMode,FXDataTarget::ID_OPTION + ReversalUP     ,BUTTON_NORMAL|LAYOUT_FILL_X);
                    new FXButton(MutationsPerReproFrame,"Amplification",NULL,&currentMutationMode,FXDataTarget::ID_OPTION + AmplificationUP,BUTTON_NORMAL|LAYOUT_FILL_X);
                    new FXButton(MutationsPerReproFrame,"Insertion"    ,NULL,&currentMutationMode,FXDataTarget::ID_OPTION + InsertionUP    ,BUTTON_NORMAL|LAYOUT_FILL_X);
                    new FXButton(MutationsPerReproFrame,"Deletion"     ,NULL,&currentMutationMode,FXDataTarget::ID_OPTION + DeletionUP     ,BUTTON_NORMAL|LAYOUT_FILL_X);
                }
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
