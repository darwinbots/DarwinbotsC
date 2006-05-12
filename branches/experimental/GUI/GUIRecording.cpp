#include "OptionsForm.h"

void OptionsFormDialogBox::Recording(FXTabBook *TabBook)
{
    FXTabItem *linesTab7=new FXTabItem(TabBook,"&Recording",NULL);
    FXPacker *linesPage7=new FXPacker(TabBook,FRAME_THICK|FRAME_RAISED);
    
    FXMatrix *LayoutMatrix=new FXMatrix(linesPage7,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXGroupBox *group1=new FXGroupBox(LayoutMatrix,"Autosave",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *LayoutMatrix4=new FXMatrix(group1,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *GroupMatrix2=new FXMatrix(LayoutMatrix4,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    new FXLabel(LayoutMatrix4,"You can set a periodical\nsaving of the whole simulation"
    "or of\nthe best robots. Files are saved with\nincreasing index number.",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    FXMatrix *GroupMatrix3=new FXMatrix(GroupMatrix2,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    new FXLabel(GroupMatrix3,"Save whole simulation every",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXSpinner(GroupMatrix3,5,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);
    
    new FXLabel(GroupMatrix3,"Minutes",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    FXMatrix *GroupMatrix4=new FXMatrix(GroupMatrix2,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    new FXLabel(GroupMatrix4,"File name",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXTextField(GroupMatrix4,15,0,TEXTFIELD_NORMAL);
    
    FXMatrix *GroupMatrix5=new FXMatrix(GroupMatrix2,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    new FXLabel(GroupMatrix5,"Save best robot every",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXSpinner(GroupMatrix5,5,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);
    
    new FXLabel(GroupMatrix5,"Minutes",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    FXMatrix *GroupMatrix6=new FXMatrix(GroupMatrix2,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    new FXLabel(GroupMatrix6,"File name",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXTextField(GroupMatrix6,15,0,TEXTFIELD_NORMAL);
    
    FXMatrix *LayoutMatrix2=new FXMatrix(LayoutMatrix,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXGroupBox *group2=new FXGroupBox(LayoutMatrix2,"Database",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *DatabaseMatrix=new FXMatrix(group2,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    new FXCheckButton(DatabaseMatrix,"Enable database recording",0,0,CHECKBUTTON_NORMAL);
    
    new FXButton(DatabaseMatrix, "Stop database\nrecording", 0, NULL,
        FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,0,0,0,0,10,10,0,0);
        
    new FXLabel(DatabaseMatrix,"Database name",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXTextField(DatabaseMatrix,15,0,TEXTFIELD_NORMAL);
        
    new FXCheckButton(DatabaseMatrix,"Exclude vegs from recording",0,0,CHECKBUTTON_NORMAL);
    
    new FXButton(DatabaseMatrix, "browse", 0, NULL,
        FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,0,0,0,0,10,10,0,0);
    
    FXGroupBox *group3=new FXGroupBox(LayoutMatrix2,"Future Recording Method",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
}
