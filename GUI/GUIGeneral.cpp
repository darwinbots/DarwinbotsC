#include "OptionsForm.h"

FXSlider *FieldSizeSlider;

void OptionsFormDialogBox::General(FXTabBook *TabBook)
{
    
    
    FXTabItem *linesTab2=new FXTabItem(TabBook,"&General",NULL);
    FXPacker *linesPage2=new FXPacker(TabBook,FRAME_THICK|FRAME_RAISED);  
    
    FXGroupBox *GeneralGroup=new FXGroupBox(linesPage2,"General Properties",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  
    FXMatrix *GeneralMatrix=new FXMatrix(GeneralGroup,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,
        0,0,0,0,
        0,0,0,0);
    FXMatrix *GeneralMatrix2=new FXMatrix(GeneralMatrix,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,
        0,0,0,0,
        0,0,0,0);
  
    FXGroupBox *WidthConGroup=new FXGroupBox(GeneralMatrix2,"Width control",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *WConMatrix=new FXMatrix(WidthConGroup,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,
        0,0,0,0,
        0,0,0,0);
    new FXLabel(WConMatrix,"Field Size",NULL,LAYOUT_LEFT|JUSTIFY_RIGHT);
    new FXLabel(WConMatrix,"Field Width",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(WConMatrix,6,new FXDataTarget(TmpOpts.FieldDimensions(0)),FXDataTarget::ID_VALUE,
        TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
    
    FieldSizeSlider = new FXSlider(WConMatrix, new FXDataTarget(TmpOpts.FieldSize, this, ID_WORLDDIMENSIONSLIDER), FXDataTarget::ID_VALUE,
        SLIDER_TICKS_TOP | SLIDER_TICKS_BOTTOM | LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
    {
        FieldSizeSlider->setRange(1,12); //position at 0 means a custom one
    }
    
    new FXLabel(WConMatrix,"Field Height",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(WConMatrix,6,new FXDataTarget(TmpOpts.FieldDimensions(1)),FXDataTarget::ID_VALUE,
        TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
  
    FXMatrix *GeneralMatrix3=new FXMatrix(GeneralMatrix2,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,
        0,0,0,0,
        0,0,0,0);
    
    FXMatrix *GeneralMatrix4=new FXMatrix(GeneralMatrix3,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,
        0,0,0,0,
        0,0,0,0);
    
    FXGroupBox *Group1=new FXGroupBox(GeneralMatrix4,"Random Numbers",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *RNMatrix=new FXMatrix(Group1,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,
        0,0,0,0,
        0,0,0,0);
    
    new FXCheckButton(RNMatrix,"Enable User Seed",new FXDataTarget((FXbool &) TmpOpts.UserSeedToggle),FXDataTarget::ID_VALUE,CHECKBUTTON_NORMAL);
    
    FXMatrix *RNMatrix2=new FXMatrix(RNMatrix,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,
        0,0,0,0,
        0,0,0,0);
    
    new FXLabel(RNMatrix2,"Seed Value",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    
    new FXTextField(RNMatrix2,5,new FXDataTarget((FXlong &)TmpOpts.UserSeedNumber),FXDataTarget::ID_VALUE,
        JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
    
    FXGroupBox *Group2=new FXGroupBox(GeneralMatrix4,"Wrap around",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *WAMatrix=new FXMatrix(Group2,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,
        0,0,0,0,
        0,0,0,0);
    
    new FXCheckButton(WAMatrix,"Top/Down Wrap",new FXDataTarget((FXbool &)TmpOpts.Updnconnected),FXDataTarget::ID_VALUE,CHECKBUTTON_NORMAL);
    new FXCheckButton(WAMatrix,"Left/Right Wrap",new FXDataTarget((FXbool &)TmpOpts.Dxsxconnected),FXDataTarget::ID_VALUE,CHECKBUTTON_NORMAL);
    
    FXGroupBox *Group3=new FXGroupBox(GeneralMatrix4,"Waste",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *WMatrix=new FXMatrix(Group3,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,
        0,0,0,0,
        0,0,0,0);
    
    new FXLabel(WMatrix,"Treshold",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    
    new FXSpinner(WMatrix,4,new FXDataTarget(TmpOpts.BadWasteLevel),FXDataTarget::ID_VALUE,
        FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);
    
    FXGroupBox *Group5=new FXGroupBox(GeneralMatrix3,"Corpse Mode",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *CMMatrix=new FXMatrix(Group5,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,
        0,0,0,0,
        0,0,0,0);
    new FXCheckButton(CMMatrix,"Enable",new FXDataTarget((FXbool &) TmpOpts.CorpseEnabled),FXDataTarget::ID_VALUE,CHECKBUTTON_NORMAL);
    FXGroupBox *DTGroup=new FXGroupBox(CMMatrix,"Decay Type",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *DTMatrix=new FXMatrix(DTGroup,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,
        0,0,0,0,
        0,0,0,0);
    new FXRadioButton(DTMatrix,"None",new FXDataTarget(TmpOpts.DecayType),FXDataTarget::ID_OPTION+0,
        LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
    new FXRadioButton(DTMatrix,"Waste",new FXDataTarget(TmpOpts.DecayType),FXDataTarget::ID_OPTION+1,
        LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
    new FXRadioButton(DTMatrix,"NRG",new FXDataTarget(TmpOpts.DecayType),FXDataTarget::ID_OPTION+2,
        LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
    
    FXGroupBox *DRGroup=new FXGroupBox(CMMatrix,"Decay Rate",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *DRMatrix=new FXMatrix(DRGroup,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,
        0,0,0,0,
        0,0,0,0);
    new FXLabel(DRMatrix,"Size",NULL);
    new FXTextField(DRMatrix,6,new FXDataTarget(TmpOpts.DecaySize),FXDataTarget::ID_VALUE);
    new FXLabel(DRMatrix,"Period",NULL);
    new FXSpinner(DRMatrix,4,new FXDataTarget(TmpOpts.DecayDelay),FXDataTarget::ID_VALUE,
        SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);
}

long OptionsFormDialogBox::onWorldDimensionSlider (FXObject *, FXSelector, void *)
{
    if (TmpOpts.FieldSize >= 2)
    {
        TmpOpts.FieldDimensions.set(8000, 6000);

        TmpOpts.FieldDimensions *= float(TmpOpts.FieldSize);
    }
    else if (TmpOpts.FieldSize == 1)
    {
        TmpOpts.FieldDimensions.set(9327, 6928);
    }

    return 1;
}
