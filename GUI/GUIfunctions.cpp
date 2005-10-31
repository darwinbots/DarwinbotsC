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

long MainWindow::onCmdPCAdvancedControls(FXObject *, FXSelector, void *){
	FXDialogBox AdvCon(this, "Advanced Physics Options", DECOR_TITLE|DECOR_BORDER,
 		0,0,0,0, 0,0,0,0, 0,0);
 		
 	FXMatrix *LayoutMatrix1=new FXMatrix(&AdvCon,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *LayoutMatrix2=new FXMatrix(LayoutMatrix1,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *LayoutMatrix3=new FXMatrix(LayoutMatrix1,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    //group 1 start

    FXGroupBox *group1=new FXGroupBox(LayoutMatrix2,"Fluid Dynamics",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    FXMatrix *FluidMatrix=new FXMatrix(group1,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    new FXLabel(FluidMatrix,"Viscosity",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(FluidMatrix,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(FluidMatrix,"E-5 Bangs per square twips",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXLabel(FluidMatrix,"Density",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(FluidMatrix,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(FluidMatrix,"E-5 Mass per cubic twip",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);

    FXGroupBox *SubGroup1=new FXGroupBox(FluidMatrix,"Flow Type",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *SubMatrix=new FXMatrix(SubGroup1,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    new FXRadioButton(SubMatrix,"Laminar",0,FXDataTarget::ID_OPTION+0,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);

    new FXRadioButton(SubMatrix,"Turbulent",0,FXDataTarget::ID_OPTION+1,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);

    new FXRadioButton(SubMatrix,"Dynamic",0,FXDataTarget::ID_OPTION+2,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
    
    FXGroupBox *SubGroup2=new FXGroupBox(FluidMatrix,"Reynold's Number",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *SubMatrix2=new FXMatrix(SubGroup2,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    new FXLabel(SubMatrix2,"Reynold's Number for\n"" an average bot moving\n"" at 1 twip/cycle",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXTextField(SubMatrix2,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
    
    //group1 end
    
    //group 2 start


    FXGroupBox *group2=new FXGroupBox(LayoutMatrix2,"Misc",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    FXMatrix *MiscMatrix=new FXMatrix(group2,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    new FXLabel(MiscMatrix,"Bang Efficiency",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    FXSlider *slider1=new FXSlider(MiscMatrix,0,FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
    slider1->setRange(0,100);
    new FXTextField(MiscMatrix,10,0,FXDataTarget::ID_VALUE,JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);

    new FXLabel(MiscMatrix,"Y axis Gravity",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    FXRealSlider *slider2=new FXRealSlider(MiscMatrix,0,FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
    slider2->setRange(0,10);
    new FXTextField(MiscMatrix,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);

    new FXLabel(MiscMatrix,"Brownian Motion",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    FXRealSlider *slider3=new FXRealSlider(MiscMatrix,0,FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
    slider3->setRange(0,10);
    new FXTextField(MiscMatrix,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);


    FXGroupBox *MiscGroup=new FXGroupBox(MiscMatrix,"Toggles",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    FXMatrix *MiscMatrix2=new FXMatrix(MiscGroup,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    new FXLabel(MiscMatrix2,"Zero Momentum",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXRadioButton(MiscMatrix2,"on",0,FXDataTarget::ID_OPTION+0,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
    
    new FXRadioButton(MiscMatrix2,"off",0,FXDataTarget::ID_OPTION+1,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);

    FXGroupBox *MiscGroup2=new FXGroupBox(MiscMatrix,"Planet Eaters",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    FXMatrix *MiscMatrix3=new FXMatrix(MiscGroup2,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    FXCheckButton *Check1 = new FXCheckButton(MiscMatrix3,"Planet Eaters",0,0,CHECKBUTTON_NORMAL);

    FXMatrix *MiscMatrix4=new FXMatrix(MiscMatrix3,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    new FXLabel(MiscMatrix4,"G:",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    
    new FXTextField(MiscMatrix4,5,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
    
    new FXLabel(MiscMatrix4,"E+3",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    //group2 end
    
    
    //group3 strat
    FXGroupBox *group3=new FXGroupBox(LayoutMatrix2,"Friction",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    FXMatrix *FricMatrix=new FXMatrix(group3,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    new FXLabel(FricMatrix,"Z axis Gravity",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    FXRealSlider *slider4=new FXRealSlider(FricMatrix,0,FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
    slider4->setRange(0,10);
    new FXTextField(FricMatrix,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
    
    new FXLabel(FricMatrix,"Static Coefficient",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    FXRealSlider *slider5=new FXRealSlider(FricMatrix,0,FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
    slider5->setRange(0,1.5);
    new FXTextField(FricMatrix,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
    
    new FXLabel(FricMatrix,"Kinetic Coefficient",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    FXRealSlider *slider6=new FXRealSlider(FricMatrix,0,FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
    slider6->setRange(0,1.5);
    new FXTextField(FricMatrix,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
    
    //group3 end
    
    //buttons start
    
    FXButton *button = new FXButton(LayoutMatrix3, "Help on Units", 0, &AdvCon,
    	   FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
            0,0,0,0,10,10,0,0);
    
    FXButton *button3 = new FXButton(LayoutMatrix3, "General Help", 0, &AdvCon,
    	   FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
            0,0,0,0,10,10,0,0);
    
    FXButton *button2 = new FXButton(LayoutMatrix3, "Okay", 0, &AdvCon,
    	   FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
            0,0,0,0,10,10,0,0);
            
    //buttons end
    
    AdvCon.execute(PLACEMENT_OWNER);
    return 1;
}

long MainWindow::onCmdPAndCAdv(FXObject *, FXSelector, void *){
	FXDialogBox AdvCosts(this, "Advanced Costs", DECOR_TITLE|DECOR_BORDER,
 		0,0,0,0, 0,0,0,0, 0,0);
 		
 	FXMatrix *LayoutMatrix=new FXMatrix(&AdvCosts,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    FXGroupBox *group1=new FXGroupBox(LayoutMatrix,"DNA Command Costs",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *Matrix1=new FXMatrix(group1,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXGroupBox *group2=new FXGroupBox(LayoutMatrix,"Ability Costs",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *Matrix2=new FXMatrix(group2,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    new FXLabel(Matrix1,"number",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXTextField(Matrix1,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(Matrix1,"nrg per instance",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);

    new FXLabel(Matrix1,"*number",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXTextField(Matrix1,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(Matrix1,"nrg per instance",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXLabel(Matrix1,"Basic Command",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXTextField(Matrix1,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(Matrix1,"nrg per instance",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXLabel(Matrix1,"Advanced Command",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXTextField(Matrix1,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(Matrix1,"nrg per instance",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXLabel(Matrix1,"Bitwize Command",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXTextField(Matrix1,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(Matrix1,"nrg per instance",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXLabel(Matrix1,"condition",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXTextField(Matrix1,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(Matrix1,"nrg per instance",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXLabel(Matrix1,"Logic",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXTextField(Matrix1,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(Matrix1,"nrg per instance",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXLabel(Matrix1,"Stores",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXTextField(Matrix1,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(Matrix1,"nrg per instance",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);

    new FXFrame(Matrix1,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
    new FXFrame(Matrix1,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
    new FXFrame(Matrix1,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);

    new FXLabel(Matrix1,"Flow Command",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXTextField(Matrix1,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(Matrix1,"nrg per instance",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);

    new FXLabel(Matrix2,"Translational Bang",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXTextField(Matrix2,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(Matrix2,"nrg per bang",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXLabel(Matrix2,"Rotational Bang",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXTextField(Matrix2,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(Matrix2,"nrg per bang",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);

    new FXLabel(Matrix2,"Tie Formation",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXTextField(Matrix2,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(Matrix2,"nrg per bang",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);

    new FXLabel(Matrix2,"Shot Formation",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXTextField(Matrix2,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(Matrix2,"base nrg per shot",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);

    new FXLabel(Matrix2,"DNA UpKeep",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXTextField(Matrix2,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(Matrix2,"nrg per bp per cycle",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXFrame(Matrix2,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
    new FXFrame(Matrix2,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
    new FXFrame(Matrix2,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
    
    new FXFrame(Matrix2,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
    new FXFrame(Matrix2,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
    new FXFrame(Matrix2,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
    
    new FXFrame(Matrix2,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
    new FXFrame(Matrix2,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
    new FXFrame(Matrix2,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
    
    new FXLabel(Matrix2,"Venom Cost",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXTextField(Matrix2,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(Matrix2,"nrg per unit constructed",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXLabel(Matrix2,"Poison Cost",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXTextField(Matrix2,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(Matrix2,"nrg per unit constructed",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXLabel(Matrix2,"Slime Cost",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXTextField(Matrix2,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(Matrix2,"nrg per unit constructed",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXLabel(Matrix2,"Shell Cost",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXTextField(Matrix2,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(Matrix2,"nrg per unit constructed",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXLabel(Matrix2,"Body UpKeep",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    new FXTextField(Matrix2,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);
    new FXLabel(Matrix2,"nrg per body per turn",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);

  FXButton *button1 = new FXButton(LayoutMatrix, "F1 Default", 0, &AdvCosts,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button2 = new FXButton(LayoutMatrix, "Okay", 0, &AdvCosts,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);

    AdvCosts.execute(PLACEMENT_OWNER);
    return 1;
}

long MainWindow::PhysicsAndCosts(FXTabBook *TabBook,FXDialogBox *Options){
  FXTabItem *linesTab3=new FXTabItem(TabBook,"&Physics and Costs",NULL);
  FXPacker *linesPage3=new FXPacker(TabBook,FRAME_THICK|FRAME_RAISED);

  FXMatrix *LayoutMatrix=new FXMatrix(linesPage3,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

  FXGroupBox *group1=new FXGroupBox(LayoutMatrix,"Physics",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FXMatrix *matrix3=new FXMatrix(group1,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
   
  
  //Start of Medium group
  FXGroupBox *group2=new FXGroupBox(matrix3,"Medium properties",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  
  FXMatrix *matrix=new FXMatrix(group2,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  
  new FXLabel(matrix,"The big blue screen is a...",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
  
  new FXFrame(matrix,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
  
  new FXRadioButton(matrix,"Fluid",&SolidOrFluid_Target,FXDataTarget::ID_OPTION+0,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
  
  new FXRadioButton(matrix,"Solid",&SolidOrFluid_Target,FXDataTarget::ID_OPTION+1,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
        
  FXPopup *popup=new FXPopup(this);
  new FXOption(popup,"Thick fluid",NULL,0,FXDataTarget::ID_OPTION+0,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
  new FXOption(popup,"Transitory",NULL,0,FXDataTarget::ID_OPTION+1,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
  new FXOption(popup,"Thin fluid",NULL,0,FXDataTarget::ID_OPTION+2,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
  FXOptionMenu *options=new FXOptionMenu(matrix,popup,LAYOUT_TOP|FRAME_RAISED|FRAME_THICK|JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
  options->setTarget(0);
  options->setSelector(FXDataTarget::ID_VALUE);
  
  FXPopup *popup2=new FXPopup(this);
  new FXOption(popup2,"Sandpaper",NULL,0,FXDataTarget::ID_OPTION+0,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
  new FXOption(popup2,"Metal",NULL,0,FXDataTarget::ID_OPTION+1,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
  new FXOption(popup2,"Teflon",NULL,0,FXDataTarget::ID_OPTION+2,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
  FXOptionMenu *options2=new FXOptionMenu(matrix,popup2,LAYOUT_TOP|FRAME_RAISED|FRAME_THICK|JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
  options2->setTarget(0);
  options2->setSelector(FXDataTarget::ID_VALUE);
  //end of Medium group
  
  //start the physics group
  FXMatrix *matrix2=new FXMatrix(matrix3,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  
  new FXLabel(matrix2,"Movement Efficiency",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
  
  new FXLabel(matrix2,"Brownian Movement",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
  
  FXPopup *popup3=new FXPopup(this);
  new FXOption(popup3,"Ideal",NULL,0,FXDataTarget::ID_OPTION+0,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
  new FXOption(popup3,"Biological",NULL,0,FXDataTarget::ID_OPTION+1,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
  new FXOption(popup3,"Mechanical",NULL,0,FXDataTarget::ID_OPTION+2,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
  FXOptionMenu *options3=new FXOptionMenu(matrix2,popup3,LAYOUT_TOP|FRAME_RAISED|FRAME_THICK|JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
  options2->setTarget(0);
  options2->setSelector(FXDataTarget::ID_VALUE);
  
  FXPopup *popup4=new FXPopup(this);
  new FXOption(popup4,"Bacteria",NULL,0,FXDataTarget::ID_OPTION+0,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
  new FXOption(popup4,"Animal",NULL,0,FXDataTarget::ID_OPTION+1,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
  FXOptionMenu *options4=new FXOptionMenu(matrix2,popup4,LAYOUT_TOP|FRAME_RAISED|FRAME_THICK|JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
  options2->setTarget(0);
  options2->setSelector(FXDataTarget::ID_VALUE);
  
  new FXLabel(matrix2,"Vertical Gravity",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
  
  new FXFrame(matrix2,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
  
  FXPopup *popup5=new FXPopup(this);
  new FXOption(popup5,"none",NULL,0,FXDataTarget::ID_OPTION+0,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
  new FXOption(popup5,"Moon",NULL,0,FXDataTarget::ID_OPTION+1,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
  new FXOption(popup5,"Earth",NULL,0,FXDataTarget::ID_OPTION+2,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
  FXOptionMenu *options5=new FXOptionMenu(matrix2,popup5,LAYOUT_TOP|FRAME_RAISED|FRAME_THICK|JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
  options2->setTarget(0);
  options2->setSelector(FXDataTarget::ID_VALUE);
  
  FXButton *button3 = new FXButton(matrix2, "Advanced Controls", 0, this,
    	ID_PCAdvancedControls, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  new FXLabel(matrix2,"Swimming Factor",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
  
  FXRealSlider *slider=new FXRealSlider(matrix2,0,FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
  slider->setRange(0.0,0.8);

  FXGroupBox *group3=new FXGroupBox(LayoutMatrix,"Costs and Returned Shots",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  
  FXMatrix *matrix4=new FXMatrix(group3,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  
  FXButton *button4 = new FXButton(matrix4, "Advanced Costs", 0, this,
    	ID_PAndCAdv, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  new FXFrame(matrix4,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
  
  new FXLabel(matrix4,"Energy exchanged on hit",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
  
  new FXFrame(matrix4,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
  
  new FXRadioButton(matrix4,"Fixed",&ProOrFixed_Target,FXDataTarget::ID_OPTION+0,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
  
  new FXSpinner(matrix4,5,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);

  new FXRadioButton(matrix4,"Propotional",&ProOrFixed_Target,FXDataTarget::ID_OPTION+1,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);

  new FXSpinner(matrix4,5,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);

  FXMatrix *matrix5=new FXMatrix(LayoutMatrix,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  
  FXMatrix *matrix6=new FXMatrix(LayoutMatrix,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

  FXButton *button5 = new FXButton(matrix5, "Load Settings", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);

  FXButton *button6 = new FXButton(matrix5, "Save Settings", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button7 = new FXButton(matrix5, "Cancel", 0, Options,
    	FXDialogBox::ID_CANCEL, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button8 = new FXButton(matrix6, "Pause", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button9 = new FXButton(matrix6, "Start New", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button10 = new FXButton(matrix6, "Change", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
}

long MainWindow::Mutations(FXTabBook *TabBook,FXDialogBox *Options){
  FXTabItem *linesTab4=new FXTabItem(TabBook,"&Mutations",NULL);
  FXPacker *linesPage4=new FXPacker(TabBook,FRAME_THICK|FRAME_RAISED);
  
  FXMatrix *MainMatrix=new FXMatrix(linesPage4,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
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
  
  FXMatrix *GroupMatrix7=new FXMatrix(GroupMatrix4,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  
  
  FXGroupBox *group4=new FXGroupBox(MainMatrix,0,GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FXMatrix *GroupMatrix8=new FXMatrix(group4,6,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

  FXButton *button5 = new FXButton(GroupMatrix8, "Load Settings", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);

  FXButton *button6 = new FXButton(GroupMatrix8, "Save Settings", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button7 = new FXButton(GroupMatrix8, "Cancel", 0, Options,
    	FXDialogBox::ID_CANCEL, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button8 = new FXButton(GroupMatrix8, "Pause", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button9 = new FXButton(GroupMatrix8, "Start New", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button10 = new FXButton(GroupMatrix8, "Change", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);


  return 1;
  
}

long MainWindow::ReststartAndL(FXTabBook *TabBook,FXDialogBox *Options){
  FXTabItem *linesTab5=new FXTabItem(TabBook,"&Restart and League",NULL);
  FXPacker *linesPage5=new FXPacker(TabBook,FRAME_THICK|FRAME_RAISED);
  
  FXMatrix *LayoutMatrix=new FXMatrix(linesPage5,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FXMatrix *LayoutMatrix2=new FXMatrix(LayoutMatrix,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  
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
  new FXRadioButton(Matrix4,"Challenge",&SolidOrFluid_Target,FXDataTarget::ID_OPTION+0,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
  new FXRadioButton(Matrix4,"Ladder",&SolidOrFluid_Target,FXDataTarget::ID_OPTION+1,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
  new FXRadioButton(Matrix4,"Last Man Standing",&SolidOrFluid_Target,FXDataTarget::ID_OPTION+2,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
  new FXRadioButton(Matrix4,"Free-For-All Elimination",&SolidOrFluid_Target,FXDataTarget::ID_OPTION+3,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
  
  
  FXMatrix *Matrix5=new FXMatrix(Matrix3,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FXCheckButton *Check2 = new FXCheckButton(Matrix5,"Run League on Start",0,0,CHECKBUTTON_NORMAL);
  new FXFrame(Matrix5,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
  new FXLabel(Matrix5,"League Name",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
  FXTextField *Text1 = new FXTextField(Matrix5,10,0,TEXTFIELD_NORMAL);
  new FXLabel(Matrix5,"Common Leagues",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
  
  
  FXMatrix *Matrix6=new FXMatrix(Matrix3,4,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FXButton *button1 = new FXButton(Matrix6, "F1", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button2 = new FXButton(Matrix6, "F2", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);

  FXButton *button3 = new FXButton(Matrix6, "SB", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button4 = new FXButton(Matrix6, "MB", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXCheckButton *Check3 = new FXCheckButton(Matrix3,"Rerun League",0,0,CHECKBUTTON_NORMAL);
  
  FXGroupBox *group4=new FXGroupBox(LayoutMatrix,0,GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FXMatrix *Matrix7=new FXMatrix(group4,6,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FXButton *button5 = new FXButton(Matrix7, "Load Settings", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);

  FXButton *button6 = new FXButton(Matrix7, "Save Settings", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button7 = new FXButton(Matrix7, "Cancel", 0, Options,
    	FXDialogBox::ID_CANCEL, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button8 = new FXButton(Matrix7, "Pause", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button9 = new FXButton(Matrix7, "Start New", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button10 = new FXButton(Matrix7, "Change", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);


  return 1;
}

long MainWindow::InternetOptions(FXTabBook *TabBook,FXDialogBox *Options){
  FXTabItem *linesTab6=new FXTabItem(TabBook,"&Internet",NULL);
  FXPacker *linesPage6=new FXPacker(TabBook,FRAME_THICK|FRAME_RAISED);
        
  FXMatrix *LayoutMatrix=new FXMatrix(linesPage6,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FXMatrix *LayoutMatrix2=new FXMatrix(LayoutMatrix,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
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
  
  FXMatrix *LayoutMatrix3=new FXMatrix(LayoutMatrix,6,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  
  FXButton *button5 = new FXButton(LayoutMatrix3, "Load Settings", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);

  FXButton *button6 = new FXButton(LayoutMatrix3, "Save Settings", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button7 = new FXButton(LayoutMatrix3, "Cancel", 0, Options,
    	FXDialogBox::ID_CANCEL, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button8 = new FXButton(LayoutMatrix3, "Pause", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button9 = new FXButton(LayoutMatrix3, "Start New", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button10 = new FXButton(LayoutMatrix3, "Change", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
  
  return 1;
}

long MainWindow::Recording(FXTabBook *TabBook,FXDialogBox *Options){
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
  
  new FXButton(DatabaseMatrix, "Stop database\nrecording", 0, Options,
    FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,0,0,0,0,10,10,0,0);
    
  new FXLabel(DatabaseMatrix,"Database name",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
  
  new FXTextField(DatabaseMatrix,15,0,TEXTFIELD_NORMAL);
    
  new FXCheckButton(DatabaseMatrix,"Exclude vegs from recording",0,0,CHECKBUTTON_NORMAL);
  
  new FXButton(DatabaseMatrix, "browse", 0, Options,
    FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,0,0,0,0,10,10,0,0);
  
  FXGroupBox *group3=new FXGroupBox(LayoutMatrix2,"Future Recording Method",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  
  FXGroupBox *group4=new FXGroupBox(LayoutMatrix,0,GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FXMatrix *LayoutMatrix3=new FXMatrix(group4,6,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  
  FXButton *button5 = new FXButton(LayoutMatrix3, "Load Settings", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);

  FXButton *button6 = new FXButton(LayoutMatrix3, "Save Settings", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button7 = new FXButton(LayoutMatrix3, "Cancel", 0, Options,
    	FXDialogBox::ID_CANCEL, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button8 = new FXButton(LayoutMatrix3, "Pause", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button9 = new FXButton(LayoutMatrix3, "Start New", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
        
  FXButton *button10 = new FXButton(LayoutMatrix3, "Change", 0, Options,
    	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
        0,0,0,0,10,10,0,0);
  
  return 1;
}

long MainWindow::onCmdQuit(FXObject *, FXSelector, void *)
{
    getApp()->exit(0);
    return 1;
}
long MainWindow::onCmdNewSimulation(FXObject *, FXSelector, void *){
	FXDialogBox Options(this, "Sim options ", DECOR_TITLE|DECOR_BORDER,
 		0,0,0,0, 0,0,0,0, 0,0);
 		
  FXTabBook *tabbook=new FXTabBook(&Options,NULL,0,LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_RIGHT);
  
  FXTabItem *linesTab=new FXTabItem(tabbook,"&Species",NULL);
  FXPacker *linesPage=new FXPacker(tabbook,FRAME_THICK|FRAME_RAISED);
  
  General(tabbook, &Options);
  
  PhysicsAndCosts(tabbook, &Options);
  
  Mutations(tabbook, &Options);
  
  ReststartAndL(tabbook, &Options);
  
  InternetOptions(tabbook, &Options);
  
  Recording(tabbook, &Options);
  
  Options.execute(PLACEMENT_OWNER);
  
  return 1;
    
}
long MainWindow::onCmdSaveSimulation(FXObject *, FXSelector, void *){return 1;}
long MainWindow::onCmdLoadSimulation(FXObject *, FXSelector, void *){return 1;}
long MainWindow::onCmdAutoSave(FXObject *, FXSelector, void *){return 1;}
long MainWindow::onCmdAbout(FXObject *, FXSelector, void *)
{
	FXDialogBox about(this, "About " PROJECT_NAME, DECOR_TITLE|DECOR_BORDER,
 		0,0,0,0, 0,0,0,0, 0,0);

  	FXVerticalFrame *contents =
        	new FXVerticalFrame(&about, LAYOUT_SIDE_LEFT|LAYOUT_FILL_X|LAYOUT_FILL_Y,
       	 		0,0,0,0, 10,10,10,10, 0,0);
        new FXLabel(contents,
            PROJECT_NAME " Version " PROJECT_VERSION ".\n\n",
      		0, JUSTIFY_LEFT|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        FXButton *button = new FXButton(contents, "OK", 0, this,
    	    ID_Quit, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
         	0,0,0,0, 32,32,5,5);
         	
        button->setFocus();
        about.execute(PLACEMENT_OWNER);

	return 1;
}
long MainWindow::onCmdShowOptions(FXObject *, FXSelector, void *){return 1;}
long MainWindow::onCmdShowLog(FXObject *, FXSelector, void *){return 1;}
