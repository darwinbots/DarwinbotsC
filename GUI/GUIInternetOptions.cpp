#include "GUImain.h"

long MainWindow::InternetOptions(FXTabBook *TabBook,FXDialogBox *Options){
    FXTabItem *linesTab6=new FXTabItem(TabBook,"&Internet",NULL);
    FXPacker *linesPage6=new FXPacker(TabBook,FRAME_THICK|FRAME_RAISED);
                
    FXMatrix *LayoutMatrix2=new FXMatrix(linesPage6,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXGroupBox *group1=new FXGroupBox(LayoutMatrix2,"Parameters",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *ParameterMatrix=new FXMatrix(group1,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXCheckButton *Check1 = new FXCheckButton(ParameterMatrix,"Use internet organisms sharing",0,0,CHECKBUTTON_NORMAL);
    
    FXMatrix *ParameterMatrix2=new FXMatrix(ParameterMatrix,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    new FXLabel(ParameterMatrix2,"Nickname",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    FXTextField *Text1 = new FXTextField(ParameterMatrix2,25,0,TEXTFIELD_NORMAL);
    
    new FXLabel(ParameterMatrix2,"FTP server",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    FXTextField *Text2 = new FXTextField(ParameterMatrix2,25,0,TEXTFIELD_NORMAL);
    
    new FXLabel(ParameterMatrix2,"Folder",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    FXTextField *Text3 = new FXTextField(ParameterMatrix2,25,0,TEXTFIELD_NORMAL);
    
    FXMatrix *ParameterMatrix3=new FXMatrix(ParameterMatrix,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXCheckButton *Check2 = new FXCheckButton(ParameterMatrix3,"but never transfer vegetables",0,0,CHECKBUTTON_NORMAL);
    
    FXMatrix *ParameterMatrix4=new FXMatrix(ParameterMatrix,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    new FXLabel(ParameterMatrix4,"Download organisms with at least",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    FXTextField *Text4 = new FXTextField(ParameterMatrix4,5,0,TEXTFIELD_NORMAL);
    new FXLabel(ParameterMatrix4,"cells",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    FXMatrix *ParameterMatrix5=new FXMatrix(ParameterMatrix,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    new FXLabel(ParameterMatrix5,"Download every",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    FXTextField *Text5 = new FXTextField(ParameterMatrix5,10,0,TEXTFIELD_NORMAL);
    new FXLabel(ParameterMatrix5,"cycles",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    FXCheckButton *Check3 = new FXCheckButton(ParameterMatrix,"and every time somthing is uploaded",0,0,CHECKBUTTON_NORMAL);
    
    new FXLabel(LayoutMatrix2,"DarwinBots will upload up to one\n""organism every 100,000 cycles to\n""the specified server. Also, the first\n""upload will be allowed at 100,000 cycles.",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    return 1;
}
