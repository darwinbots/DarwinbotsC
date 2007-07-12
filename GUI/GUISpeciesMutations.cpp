#include <fx.h>
#include "OptionsForm.h"
#include "..\Engine\Mutations.h"
#include "..\Engine\Specie.h"

int g_mutationmode = PointUP;
FXDataTarget CurrentMutationMode(g_mutationmode);

FXDataTarget CurrentMutationProb;

char *MutationDetailsArray[] = {
"Point Mutation",
"Delta Mutation",
"Copy Error Mutation",
"Reversal Mutation",
"Translocation Mutation",
"Insertion Mutation",
"Amplification Mutation",
"Deletion Mutation"};

char *MutationProbSuffixArray[] = {
"per bp per cycle",
"per cycle",
"per bp per bot",
"per bot",
"per bot",
"per bot",
"per bot",
"per bot"};

class SpeciesMutationsDialogBox : public FXDialogBox
{
    FXDECLARE(SpeciesMutationsDialogBox)

    private:
    mutationprobs WorkingCopy;
    mutationprobs *RealCopy;

    FXString MutationInformation;
    FXString MutationProbSuffix;

    FXDataTarget MutationEnabledDT;
    FXDataTarget MeanDT;
    FXDataTarget StdDevDT; //standard deviation data target

    FXGroupBox *ChangeTypeValueFrame;
    FXGroupBox *GaussFrame;

    public:
    
    SpeciesMutationsDialogBox::SpeciesMutationsDialogBox() {};
    
    SpeciesMutationsDialogBox::SpeciesMutationsDialogBox(FXComposite *parent, mutationprobs *Muts);

    void hide()
    {
        FXDialogBox::hide();
    }

    void show(FXuint placement)
    {
        FXDialogBox::show(placement);
    }

    long onChangeMode       (FXObject *, FXSelector newmode, void *);
    long onApplyToTemplate  (FXObject *, FXSelector newmode, void *);

    enum
    {
        ID_CHANGEMODE = FXDialogBox::ID_LAST,
        ID_MUTATIONMODE,
        ID_MUTATIONMODELAST = ID_MUTATIONMODE + 20,

        ID_APPLYTOTEMPLATE,

        ID_LAST
    };
};

FXDEFMAP(SpeciesMutationsDialogBox) SpeciesMutationsDialogBoxMap[] = {
    FXMAPFUNCS(SEL_COMMAND, SpeciesMutationsDialogBox::ID_MUTATIONMODE,
                            SpeciesMutationsDialogBox::ID_MUTATIONMODELAST,
                            SpeciesMutationsDialogBox::onChangeMode),
    FXMAPFUNC(SEL_COMMAND, SpeciesMutationsDialogBox::ID_APPLYTOTEMPLATE, SpeciesMutationsDialogBox::onApplyToTemplate)
};

FXIMPLEMENT(SpeciesMutationsDialogBox, FXDialogBox,
    SpeciesMutationsDialogBoxMap, ARRAYNUMBER(SpeciesMutationsDialogBoxMap))

SpeciesMutationsDialogBox::SpeciesMutationsDialogBox(FXComposite *parent, mutationprobs *Muts) :
    FXDialogBox(parent, "Species mutation options", DECOR_TITLE|DECOR_BORDER,
        0,0,0,0, 0,0,0,0, 0,0)
{

    RealCopy = Muts;
    WorkingCopy = (*RealCopy);
    
    FXMatrix *LayoutMatrix = new FXMatrix(this, 1, MATRIX_BY_COLUMNS);
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
                    this, SpeciesMutationsDialogBox::ID_MUTATIONMODE + option, BUTTON_NORMAL | LAYOUT_FILL_X
                
                //Per Cycle mutations
                FXGroupBox *MutationsPerCycleFrame = new FXGroupBox(MutationsTypeMatrix, "Per cycle",
                    FRAME_RIDGE | LAYOUT_FILL_ALL);
                {
                    new FXButton(MutationsPerCycleFrame, "Point", NULL, BUTTON_STUFF(PointUP));
                    new FXButton(MutationsPerCycleFrame, "Delta", NULL, BUTTON_STUFF(DeltaUP));
                }

                //Per Reproduction mutations
                FXGroupBox *MutationsPerReproFrame = new FXGroupBox(MutationsTypeMatrix, "Per reproduction",
                    FRAME_RIDGE | LAYOUT_FILL_ALL);
                {
                    new FXButton(MutationsPerReproFrame, "Copy Error", NULL, BUTTON_STUFF(CopyErrorUP));
                    new FXButton(MutationsPerReproFrame, "Reversal", NULL, BUTTON_STUFF(ReversalUP));
                    new FXButton(MutationsPerReproFrame, "Translocation", NULL, BUTTON_STUFF(TranslocationUP));
                    new FXButton(MutationsPerReproFrame, "Insertion", NULL, BUTTON_STUFF(InsertionUP));
                    new FXButton(MutationsPerReproFrame, "Amplification", NULL, BUTTON_STUFF(AmplificationUP));
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
                    new FXText(MutationsDetailsFrame, new FXDataTarget((FXString &)MutationInformation), 
                        FXDataTarget::ID_VALUE, FRAME_RIDGE | LAYOUT_FILL_X | TEXT_READONLY);

                    FXMatrix *EnabledAndChanceMatrix = 
                        new FXMatrix(MutationsDetailsFrame, 1, MATRIX_BY_ROWS | LAYOUT_FILL_X);
                    {
                        new FXCheckButton(EnabledAndChanceMatrix, "Mutation enabled",
                            &MutationEnabledDT, FXDataTarget::ID_VALUE);
                        
                        new FXLabel(EnabledAndChanceMatrix, "1 in ");
                        
                        new FXTextField(EnabledAndChanceMatrix, 9, &CurrentMutationProb, FXDataTarget::ID_VALUE);

                        new FXTextField(EnabledAndChanceMatrix, 13, new FXDataTarget(MutationProbSuffix),
                            FXDataTarget::ID_VALUE,TEXTFIELD_READONLY);
                    }

                    GaussFrame = new FXGroupBox(MutationsDetailsFrame, 
                        "Gaussian distribution", FRAME_RIDGE | LAYOUT_FILL_X);
                    {
                    
                        FXMatrix *ChangeMeanMatrix = 
                            new FXMatrix(GaussFrame, 1, MATRIX_BY_ROWS | LAYOUT_FILL_X);

                        {
                            new FXLabel(ChangeMeanMatrix, "Mean length");
                            new FXHorizontalSeparator(ChangeMeanMatrix, LAYOUT_FILL_X|LAYOUT_FILL_COLUMN);
                            new FXTextField(ChangeMeanMatrix, 9, &MeanDT, FXDataTarget::ID_VALUE,
                                JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT);
                        }

                        FXMatrix *ChangeStdDevMatrix = 
                            new FXMatrix(GaussFrame, 1, MATRIX_BY_ROWS | LAYOUT_FILL_X);
                        {
                            new FXLabel(ChangeStdDevMatrix, "Standard deviation");
                            new FXHorizontalSeparator(ChangeStdDevMatrix, LAYOUT_FILL_X|LAYOUT_FILL_COLUMN);
                            new FXTextField(ChangeStdDevMatrix, 9, &StdDevDT, FXDataTarget::ID_VALUE,
                                JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT);
                        }
                    }

                    
                    ChangeTypeValueFrame = new FXGroupBox(MutationsDetailsFrame,
                        "Change type/value", FRAME_RIDGE | LAYOUT_FILL_X);
                    
                    FXMatrix *ChangeTypeOrValueMatrix = 
                        new FXMatrix(ChangeTypeValueFrame, 1, MATRIX_BY_ROWS | LAYOUT_FILL_X);
                    {
                        new FXLabel(ChangeTypeOrValueMatrix, "Change type");

                        (new FXRealSlider(ChangeTypeOrValueMatrix, NULL, 0, SLIDER_NORMAL | LAYOUT_FILL_ALL))->setRange(0, 1);
                        
                        new FXLabel(ChangeTypeOrValueMatrix, "Change value");
                    }                    

                    FXGroupBox *ApproximateChancesFrame = new FXGroupBox(MutationsDetailsFrame,
                        "Approximate mutation chances", FRAME_RIDGE | LAYOUT_FILL_ALL);
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
                "", NULL, FRAME_RIDGE | LAYOUT_FILL_ALL);
        {
            FXMatrix *ToolbarMatrix = new FXMatrix(ToolbarFrame, 1, MATRIX_BY_ROWS | LAYOUT_FILL_ALL);
            {
                new FXCheckButton(ToolbarMatrix, "Enable mutations");
                //new FXHorizontalSeparator(ToolbarMatrix);
                new FXButton(ToolbarMatrix, "Cancel", NULL, this, FXDialogBox::ID_CANCEL);
                new FXButton(ToolbarMatrix, "Apply to bots in world");
                new FXButton(ToolbarMatrix, "Apply to species template", NULL, this,
                    SpeciesMutationsDialogBox::ID_APPLYTOTEMPLATE);
            }
        }        
    }
}

long SpeciesMutationsDialogBox::onChangeMode(FXObject *, FXSelector newmode, void *)
{
    g_mutationmode = FXSELID(newmode) - ID_MUTATIONMODE;
    
    MutationTypeInformationHolder *currentmutation = NULL;
    
    currentmutation = WorkingCopy[g_mutationmode];

    if(currentmutation != NULL)
    {
        MutationInformation = MutationDetailsArray[g_mutationmode - 1];
        MutationProbSuffix = MutationProbSuffixArray[g_mutationmode - 1];
        CurrentMutationProb.connect((FXulong &) currentmutation->Prob);    
        MutationEnabledDT.connect((FXbool &)currentmutation->On);
        MeanDT.connect(currentmutation->Mean);
        StdDevDT.connect(currentmutation->StdDev);

        if(g_mutationmode == PointUP ||
           g_mutationmode == CopyErrorUP)
        {
            ChangeTypeValueFrame->show();
        }
        else
        {
            ChangeTypeValueFrame->hide();
        }

        if(g_mutationmode == PointUP ||
           g_mutationmode == CopyErrorUP)
        {
            GaussFrame->hide();
        }
        else
        {
            GaussFrame->show();
        }    
    }
    
    return 1;
}

long SpeciesMutationsDialogBox::onApplyToTemplate(FXObject *, FXSelector newmode, void *)
{
    (*RealCopy) = WorkingCopy;        

    return 1;
}

long OptionsFormDialogBox::onMutationsSpecies(FXObject *, FXSelector, void *)
{
    SpeciesMutationsDialogBox *temp = new SpeciesMutationsDialogBox(this,
        &TmpOpts.Specie[SpeciesList->getCurrentItem()].Mutables);
    temp->execute(PLACEMENT_OWNER);
    delete temp;
    return true;
}
