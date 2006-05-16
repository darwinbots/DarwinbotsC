#include "MainWindow.h"
#include "OptionsForm.h"

void OptionsFormDialogBox::Mutations(FXTabBook *TabBook)
{
    FXTabItem *linesTab = new FXTabItem(TabBook,"&Mutations",NULL);
    FXPacker *linesPage = new FXPacker(TabBook,FRAME_THICK|FRAME_RAISED);
    
    FXMatrix *MutationsPageMasterMatrix = new FXMatrix(linesPage, 1, MATRIX_BY_COLUMNS | LAYOUT_FILL_ALL);

    FXGroupBox *OscillationMultiplierFrame = new FXGroupBox(MutationsPageMasterMatrix, "Mutation Multiplier", FRAME_RIDGE);
    {
        new FXLabel(OscillationMultiplierFrame, "Global Multiplier =\nA * cos(B * 2PI) + C");
        FXMatrix *OscillationInternalMatrix = new FXMatrix(OscillationMultiplierFrame, 2, MATRIX_BY_COLUMNS | LAYOUT_FILL_ALL,
                                              0,0,0,0,
                                              0,0,0,0);
        {
            new FXLabel(OscillationInternalMatrix, "A = ");
            new FXTextField(OscillationInternalMatrix, 10);
            
            new FXLabel(OscillationInternalMatrix, "B = ");
            new FXTextField(OscillationInternalMatrix, 10);

            new FXLabel(OscillationInternalMatrix, "C = ");
            new FXTextField(OscillationInternalMatrix, 10);
        }
    }

    FXGroupBox *MutationProbabilities = new FXGroupBox(MutationsPageMasterMatrix, "Mutation Probabilities", LAYOUT_FILL_ALL | FRAME_RIDGE);
    {
        FXMatrix *ProbabilitiesMatrix = new FXMatrix(MutationProbabilities, 3, MATRIX_BY_ROWS | LAYOUT_FILL_ALL,
                                              0,0,0,0,
                                              0,0,0,0);
        {
            new FXLabel(ProbabilitiesMatrix, "100%", NULL, LAYOUT_CENTER_X);
            (new FXSlider(ProbabilitiesMatrix, NULL, 0, SLIDER_VERTICAL | LAYOUT_CENTER_X | 
                LAYOUT_FILL_ALL | SLIDER_INSIDE_BAR | LAYOUT_FIX_WIDTH,0,0,45));
            new FXLabel(ProbabilitiesMatrix, ".number");

            new FXLabel(ProbabilitiesMatrix, "100%", NULL, LAYOUT_CENTER_X);
            (new FXSlider(ProbabilitiesMatrix, NULL, 0, SLIDER_VERTICAL | LAYOUT_CENTER_X | 
                LAYOUT_FILL_ALL | SLIDER_INSIDE_BAR | LAYOUT_FIX_WIDTH,0,0,45));
            new FXLabel(ProbabilitiesMatrix, "*.number");

            new FXLabel(ProbabilitiesMatrix, "100%", NULL, LAYOUT_CENTER_X);
            (new FXSlider(ProbabilitiesMatrix, NULL, 0, SLIDER_VERTICAL | LAYOUT_CENTER_X | 
                LAYOUT_FILL_ALL | SLIDER_INSIDE_BAR | LAYOUT_FIX_WIDTH,0,0,45));
            new FXLabel(ProbabilitiesMatrix, "Basic");

            new FXLabel(ProbabilitiesMatrix, "100%", NULL, LAYOUT_CENTER_X);
            (new FXSlider(ProbabilitiesMatrix, NULL, 0, SLIDER_VERTICAL | LAYOUT_CENTER_X | 
                LAYOUT_FILL_ALL | SLIDER_INSIDE_BAR | LAYOUT_FIX_WIDTH,0,0,45));
            new FXLabel(ProbabilitiesMatrix, "Advanced");

            new FXLabel(ProbabilitiesMatrix, "100%", NULL, LAYOUT_CENTER_X);
            (new FXSlider(ProbabilitiesMatrix, NULL, 0, SLIDER_VERTICAL | LAYOUT_CENTER_X | 
                LAYOUT_FILL_ALL | SLIDER_INSIDE_BAR | LAYOUT_FIX_WIDTH,0,0,45));
            new FXLabel(ProbabilitiesMatrix, "Bitwise");

            new FXLabel(ProbabilitiesMatrix, "100%", NULL, LAYOUT_CENTER_X);
            (new FXSlider(ProbabilitiesMatrix, NULL, 0, SLIDER_VERTICAL | LAYOUT_CENTER_X | 
                LAYOUT_FILL_ALL | SLIDER_INSIDE_BAR | LAYOUT_FIX_WIDTH,0,0,45));
            new FXLabel(ProbabilitiesMatrix, "Condition");

            new FXLabel(ProbabilitiesMatrix, "100%", NULL, LAYOUT_CENTER_X);
            (new FXSlider(ProbabilitiesMatrix, NULL, 0, SLIDER_VERTICAL | LAYOUT_CENTER_X | 
                LAYOUT_FILL_ALL | SLIDER_INSIDE_BAR | LAYOUT_FIX_WIDTH,0,0,45));
            new FXLabel(ProbabilitiesMatrix, "Logic");

            new FXLabel(ProbabilitiesMatrix, "100%", NULL, LAYOUT_CENTER_X);
            (new FXSlider(ProbabilitiesMatrix, NULL, 0, SLIDER_VERTICAL | LAYOUT_CENTER_X | 
                LAYOUT_FILL_ALL | SLIDER_INSIDE_BAR | LAYOUT_FIX_WIDTH,0,0,45));
            new FXLabel(ProbabilitiesMatrix, "Stores");

            new FXLabel(ProbabilitiesMatrix, "100%", NULL, LAYOUT_CENTER_X);
            (new FXSlider(ProbabilitiesMatrix, NULL, 0, SLIDER_VERTICAL | LAYOUT_CENTER_X | 
                LAYOUT_FILL_ALL | SLIDER_INSIDE_BAR | LAYOUT_FIX_WIDTH,0,0,45));
            new FXLabel(ProbabilitiesMatrix, "Flow");
        }
    }
    


    
    /*FXMatrix *MainMatrix=new FXMatrix(linesPage,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *MainMatrix2=new FXMatrix(MainMatrix,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXGroupBox *group1=new FXGroupBox(MainMatrix2,"Current Multiplier",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *GroupMatrix1=new FXMatrix(group1,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    new FXTextField(GroupMatrix1,8,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    
    FXRealSlider *slider1=new FXRealSlider(GroupMatrix1,0,FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,200);
    slider1->setRange(0.03125,32);
    
    new FXLabel(GroupMatrix1,"Here you can set a multiplier of the global\n"
                                                     "mutation rates. Useful to increase genetic\n"
                                                     "variability (rate high) or to reduce it via\n"
                                                     "selection (rate low).",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    FXGroupBox *group2=new FXGroupBox(MainMatrix2,"Oscillation Frequency",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *MainMatrix3=new FXMatrix(group2,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *GroupMatrix2=new FXMatrix(MainMatrix3,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *GroupMatrix3=new FXMatrix(MainMatrix3,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    
    new FXCheckButton(GroupMatrix2,"Make mutation frequency oscillating\n"
                                                                 "between 16x and 1/16x",0,0,CHECKBUTTON_NORMAL);
    
    new FXLabel(GroupMatrix3,"Cycles at 16x",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXSpinner(GroupMatrix3,5,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);
    
    new FXLabel(GroupMatrix3,"Cycles at 1/16x",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXSpinner(GroupMatrix3,5,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);
    
    FXGroupBox *group3=new FXGroupBox(MainMatrix,"Scripts",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *GroupMatrix4=new FXMatrix(group3,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *GroupMatrix5=new FXMatrix(GroupMatrix4,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    new FXLabel(GroupMatrix5,"Select a condition, and item and an action, then click on 'Add Script'\nto add the script to the list. Select a script from the list and click\non 'Delete Selected Script' to remove it from the list",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXCheckButton(GroupMatrix5,"DNA Scripts Enabled",0,0,CHECKBUTTON_NORMAL);
    
    FXMatrix *GroupMatrix6=new FXMatrix(GroupMatrix4,5,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *GroupMatrix7=new FXMatrix(GroupMatrix4,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);*/
}
