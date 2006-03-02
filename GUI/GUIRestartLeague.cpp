#include "OptionsForm.h"

void OptionsFormDialogBox::ReststartAndL(FXTabBook *TabBook)
{
    FXTabItem *linesTab5=new FXTabItem(TabBook,"&Restart and League",NULL);
    FXPacker *linesPage5=new FXPacker(TabBook,FRAME_THICK|FRAME_RAISED);
    
    FXMatrix *LayoutMatrix=new FXMatrix(linesPage5,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *LayoutMatrix2=new FXMatrix(linesPage5,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXGroupBox *group1=new FXGroupBox(LayoutMatrix2,"Contest Conditions",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *Matrix=new FXMatrix(group1,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXCheckButton *Check1 = new FXCheckButton(Matrix,"Use F1 Contest Conditions",0,0,CHECKBUTTON_NORMAL);
    new FXFrame(Matrix,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
    new FXLabel(Matrix,"Number of rounds in a Contest",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXSpinner(Matrix,5,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);
    new FXLabel(Matrix,"Sampling frequency",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXSpinner(Matrix,5,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);

    
    
    FXGroupBox *group2=new FXGroupBox(LayoutMatrix2,"General Restart Conditions",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    new FXCheckButton(group2,"Restart Sim when all robots are dead",0,0,CHECKBUTTON_NORMAL);
    
    FXGroupBox *group3=new FXGroupBox(LayoutMatrix,"Challenge League Conditions",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *Matrix2=new FXMatrix(group3,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *Matrix3=new FXMatrix(Matrix2,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *Matrix4=new FXMatrix(Matrix2,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    new FXRadioButton(Matrix4,"Challenge",0,FXDataTarget::ID_OPTION+0,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
    new FXRadioButton(Matrix4,"Ladder",0,FXDataTarget::ID_OPTION+1,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
    new FXRadioButton(Matrix4,"Last Man Standing",0,FXDataTarget::ID_OPTION+2,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
    new FXRadioButton(Matrix4,"Free-For-All Elimination",0,FXDataTarget::ID_OPTION+3,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
    
    
    FXMatrix *Matrix5=new FXMatrix(Matrix3,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXCheckButton *Check2 = new FXCheckButton(Matrix5,"Run League on Start",0,0,CHECKBUTTON_NORMAL);
    new FXFrame(Matrix5,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
    new FXLabel(Matrix5,"League Name",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    FXTextField *Text1 = new FXTextField(Matrix5,10,0,TEXTFIELD_NORMAL);
    new FXLabel(Matrix5,"Common Leagues",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    
    FXMatrix *Matrix6=new FXMatrix(Matrix3,4,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXButton *button1 = new FXButton(Matrix6, "F1", 0, NULL,
        	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
                0,0,0,0,10,10,0,0);
                
    FXButton *button2 = new FXButton(Matrix6, "F2", 0, NULL,
        	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
                0,0,0,0,10,10,0,0);

    FXButton *button3 = new FXButton(Matrix6, "SB", 0, NULL,
        	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
                0,0,0,0,10,10,0,0);
                
    FXButton *button4 = new FXButton(Matrix6, "MB", 0, NULL,
        	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
                0,0,0,0,10,10,0,0);
                
    FXCheckButton *Check3 = new FXCheckButton(Matrix3,"Rerun League",0,0,CHECKBUTTON_NORMAL);
}
