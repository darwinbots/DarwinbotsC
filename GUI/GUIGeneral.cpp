#include "GUImain.h"

long MainWindow::General(FXTabBook *TabBook,FXDialogBox *Options){
    FXTabItem *linesTab2=new FXTabItem(TabBook,"&General",NULL);
    FXPacker *linesPage2=new FXPacker(TabBook,FRAME_THICK|FRAME_RAISED);  
  
    FXMatrix *LayoutMatrix1=new FXMatrix(linesPage2,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  
    FXGroupBox *GeneralGroup=new FXGroupBox(LayoutMatrix1,"General Properties",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  
    FXMatrix *GeneralMatrix=new FXMatrix(GeneralGroup,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  
    FXMatrix *GeneralMatrix2=new FXMatrix(GeneralMatrix,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  
    FXGroupBox *WidthConGroup=new FXGroupBox(GeneralMatrix2,"Width control",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *WConMatrix=new FXMatrix(WidthConGroup,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    new FXLabel(WConMatrix,"Field Size",NULL,LAYOUT_LEFT|JUSTIFY_RIGHT);
    new FXLabel(WConMatrix,"Field Width",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(WConMatrix,5,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
    FXSlider *slider1=new FXSlider(WConMatrix,0,FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
    slider1->setRange(0,12);
    new FXLabel(WConMatrix,"Field Height",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(WConMatrix,5,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
  
    FXMatrix *GeneralMatrix3=new FXMatrix(GeneralMatrix2,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *GeneralMatrix4=new FXMatrix(GeneralMatrix3,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXGroupBox *Group1=new FXGroupBox(GeneralMatrix4,"Random Numbers",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *RNMatrix=new FXMatrix(Group1,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    new FXCheckButton(RNMatrix,"Enable User Seed",0,0,CHECKBUTTON_NORMAL);
    
    FXMatrix *RNMatrix2=new FXMatrix(RNMatrix,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    new FXLabel(RNMatrix2,"Seed Value",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    
    new FXTextField(RNMatrix2,5,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
    
    FXGroupBox *Group2=new FXGroupBox(GeneralMatrix4,"Wrap around",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *WAMatrix=new FXMatrix(Group2,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    new FXCheckButton(WAMatrix,"Toroidal",0,0,CHECKBUTTON_NORMAL);
    new FXCheckButton(WAMatrix,"Top/Down Wrap",0,0,CHECKBUTTON_NORMAL);
    new FXCheckButton(WAMatrix,"Left/Right Wrap",0,0,CHECKBUTTON_NORMAL);
    
    FXGroupBox *Group3=new FXGroupBox(GeneralMatrix4,"Waste",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *WMatrix=new FXMatrix(Group3,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    new FXLabel(WMatrix,"Treshold",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    
    new FXSpinner(WMatrix,4,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);
    
    FXGroupBox *Group4=new FXGroupBox(GeneralMatrix4,"Misc. Controls",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *WCMatrix=new FXMatrix(Group4,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    new FXCheckButton(WCMatrix,"Disable ties",0,0,CHECKBUTTON_NORMAL);
    
    FXGroupBox *Group5=new FXGroupBox(GeneralMatrix3,"Corpse Mode",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *CMMatrix=new FXMatrix(Group5,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    new FXCheckButton(CMMatrix,"Enable",0,0,CHECKBUTTON_NORMAL);
    FXGroupBox *DTGroup=new FXGroupBox(CMMatrix,"Decay Type",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *DTMatrix=new FXMatrix(DTGroup,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    new FXRadioButton(DTMatrix,"None",0,FXDataTarget::ID_OPTION+0,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
    new FXRadioButton(DTMatrix,"Waste",0,FXDataTarget::ID_OPTION+0,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
    new FXRadioButton(DTMatrix,"NRG",0,FXDataTarget::ID_OPTION+0,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
    
    FXGroupBox *DRGroup=new FXGroupBox(CMMatrix,"Decay Rate",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *DRMatrix=new FXMatrix(DRGroup,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    new FXLabel(DRMatrix,"Size",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXSpinner(DRMatrix,4,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);
    new FXLabel(DRMatrix,"Period",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXSpinner(DRMatrix,4,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);
 
    
    FXGroupBox *PopulationGroup=new FXGroupBox(GeneralMatrix,"Population control",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *PopMatrix=new FXMatrix(PopulationGroup,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *PopMatrix2=new FXMatrix(PopMatrix,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *PopMatrix4=new FXMatrix(PopMatrix2,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXGroupBox *PopulationGroup3=new FXGroupBox(PopMatrix2,"Veggy Energy",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *VEMatrix=new FXMatrix(PopulationGroup3,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    new FXLabel(VEMatrix,"NRG",NULL,LAYOUT_CENTER_X);
    new FXTextField(VEMatrix,5,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(VEMatrix,"per",NULL,LAYOUT_CENTER_X);
    new FXRadioButton(VEMatrix,"Veggy per cycle",0,FXDataTarget::ID_OPTION+0,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
    new FXRadioButton(VEMatrix,"Kilobody point",0,FXDataTarget::ID_OPTION+0,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
    new FXRadioButton(VEMatrix,"Quadratically\nbased on body",0,FXDataTarget::ID_OPTION+0,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
    
    
    FXGroupBox *PopulationGroup4=new FXGroupBox(PopMatrix4,"Pond Mode",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *PMMatrix=new FXMatrix(PopulationGroup4,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *PMMatrix2=new FXMatrix(PMMatrix,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    new FXCheckButton(PMMatrix2,"Pond mode",0,0,CHECKBUTTON_NORMAL);
    new FXFrame(PMMatrix2,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
    new FXLabel(PMMatrix2,"Light intensity",NULL,LAYOUT_CENTER_X);
    new FXSpinner(PMMatrix2,4,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);
    new FXLabel(PMMatrix2,"Sediment Level",NULL,LAYOUT_CENTER_X);
    new FXSpinner(PMMatrix2,4,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);
    FXGroupBox *PMGroup=new FXGroupBox(PMMatrix,"Light",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *PMMatrix3=new FXMatrix(PMGroup,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    new FXLabel(PMMatrix3,"Energy\nScaling\nFactor",NULL,LAYOUT_CENTER_X);
    new FXSpinner(PMMatrix3,4,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);
    
    FXGroupBox *PopulationGroup5=new FXGroupBox(PopMatrix4,"Population Control",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *PCMatrix=new FXMatrix(PopulationGroup5,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    new FXSpinner(PCMatrix,4,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);
    new FXLabel(PCMatrix,"Max number of Veggies",NULL,LAYOUT_LEFT|JUSTIFY_RIGHT);
    new FXSpinner(PCMatrix,4,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);
    new FXLabel(PCMatrix,"Repopulation Threshold",NULL,LAYOUT_LEFT|JUSTIFY_RIGHT);
    new FXSpinner(PCMatrix,4,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);
    new FXLabel(PCMatrix,"Veggies per repopulation event",NULL,LAYOUT_LEFT|JUSTIFY_RIGHT);
    new FXSpinner(PCMatrix,4,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);
    new FXLabel(PCMatrix,"Repopulation cooldown period",NULL,LAYOUT_LEFT|JUSTIFY_RIGHT);
    
    FXMatrix *PopMatrix3=new FXMatrix(PopMatrix,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXGroupBox *PopulationGroup1=new FXGroupBox(PopMatrix3,"Day Cycles",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *DCMatrix=new FXMatrix(PopulationGroup1,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    new FXCheckButton(DCMatrix,"Enable",0,0,CHECKBUTTON_NORMAL);
    new FXFrame(DCMatrix,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
    new FXLabel(DCMatrix,"Period",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXSpinner(DCMatrix,4,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);
    
    FXGroupBox *PopulationGroup2=new FXGroupBox(PopMatrix3,"Veg Body/NRG Distribution",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *VBMatrix=new FXMatrix(PopulationGroup2,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    new FXLabel(VBMatrix,"NRG",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    FXSlider *slider2=new FXSlider(VBMatrix,0,FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
    slider2->setRange(0,100);
    new FXLabel(VBMatrix,"Body",NULL,LAYOUT_LEFT|JUSTIFY_RIGHT);
    
    FXGroupBox *ButtonGroup=new FXGroupBox(LayoutMatrix1,0,GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *ButtonMatrix=new FXMatrix(ButtonGroup,6,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXButton *button5 = new FXButton(ButtonMatrix, "Load Settings", 0, Options,
        	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
                0,0,0,0,10,10,0,0);

    FXButton *button6 = new FXButton(ButtonMatrix, "Save Settings", 0, Options,
        	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
                0,0,0,0,10,10,0,0);
                
    FXButton *button7 = new FXButton(ButtonMatrix, "Cancel", 0, Options,
        	FXDialogBox::ID_CANCEL, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
                0,0,0,0,10,10,0,0);
                
    FXButton *button8 = new FXButton(ButtonMatrix, "Pause", 0, Options,
        	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
                0,0,0,0,10,10,0,0);
                
    FXButton *button9 = new FXButton(ButtonMatrix, "Start New", 0, Options,
        	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
                0,0,0,0,10,10,0,0);
                
    FXButton *button10 = new FXButton(ButtonMatrix, "Change", 0, Options,
        	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
                0,0,0,0,10,10,0,0);    

    return 1;
}