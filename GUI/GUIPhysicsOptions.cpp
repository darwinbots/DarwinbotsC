#include "OptionsForm.h"

long OptionsFormDialogBox::onAdvancedPhysics(FXObject *, FXSelector, void *){
	FXDialogBox AdvCon(this, "Advanced Physics Options", DECOR_TITLE|DECOR_BORDER,
 		0,0,0,0, 0,0,0,0, 0,0);
 		
        FXMatrix *LayoutMatrix1=new FXMatrix(&AdvCon,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
        
        FXMatrix *LayoutMatrix2=new FXMatrix(LayoutMatrix1,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
        
        FXMatrix *LayoutMatrix3=new FXMatrix(LayoutMatrix1,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        //group 1 start

        FXGroupBox *group1=new FXGroupBox(LayoutMatrix2,"Fluid Dynamics",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        FXMatrix *FluidMatrix=new FXMatrix(group1,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        new FXLabel(FluidMatrix,"Viscosity",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
        new FXTextField(FluidMatrix,10,new FXDataTarget(TmpOpts.Viscosity),FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
        new FXLabel(FluidMatrix,"E-5 Bangs per square twips",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        
        new FXLabel(FluidMatrix,"Density",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
        new FXTextField(FluidMatrix,10,new FXDataTarget(TmpOpts.Density),
            FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
        new FXLabel(FluidMatrix,"E-5 Mass per cubic twip",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);

        FXGroupBox *SubGroup1=new FXGroupBox(FluidMatrix,"Flow Type",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
        
        FXMatrix *SubMatrix=new FXMatrix(SubGroup1,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        //new FXRadioButton(SubMatrix,"Laminar",new FXDataTarget(TmpOpts.,FXDataTarget::ID_OPTION+0,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);

        //new FXRadioButton(SubMatrix,"Turbulent",0,FXDataTarget::ID_OPTION+1,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);

        //new FXRadioButton(SubMatrix,"Dynamic",0,FXDataTarget::ID_OPTION+2,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
        
        //FXGroupBox *SubGroup2=new FXGroupBox(FluidMatrix,"Reynold's Number",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
        //FXMatrix *SubMatrix2=new FXMatrix(SubGroup2,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
        
        //new FXLabel(SubMatrix2,"Reynold's Number for\n"" an average bot moving\n"" at 1 twip/cycle",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        
        //new FXTextField(SubMatrix2,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
        
        //group1 end
        
        //group 2 start


        FXGroupBox *group2=new FXGroupBox(LayoutMatrix2,"Misc",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        FXMatrix *MiscMatrix=new FXMatrix(group2,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        new FXLabel(MiscMatrix,"Bang Efficiency",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        FXSlider *slider1=new FXSlider(MiscMatrix,new FXDataTarget(TmpOpts.MovingEfficiency),
            FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
        slider1->setRange(0,100);
        new FXTextField(MiscMatrix,10,new FXDataTarget(TmpOpts.MovingEfficiency),
            FXDataTarget::ID_VALUE,JUSTIFY_RIGHT|LAYOUT_CENTER_Y|LAYOUT_CENTER_X|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_ROW);

        new FXLabel(MiscMatrix,"Y axis Gravity",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        FXRealSlider *slider2=new FXRealSlider(MiscMatrix,new FXDataTarget(TmpOpts.YGravity),
            FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
        slider2->setRange(0,10);
        new FXTextField(MiscMatrix,10,new FXDataTarget(TmpOpts.YGravity),
            FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);

        new FXLabel(MiscMatrix,"Brownian Motion",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        FXRealSlider *slider3=new FXRealSlider(MiscMatrix,new FXDataTarget(TmpOpts.Brownian),
            FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
        slider3->setRange(0,10);
        new FXTextField(MiscMatrix,10,new FXDataTarget(TmpOpts.Brownian),
            FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);


        FXGroupBox *MiscGroup=new FXGroupBox(MiscMatrix,"Toggles",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        FXMatrix *MiscMatrix2=new FXMatrix(MiscGroup,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        new FXLabel(MiscMatrix2,"Zero Momentum",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        
        new FXRadioButton(MiscMatrix2,"on",new FXDataTarget((FXbool &) TmpOpts.ZeroMomentum),
            FXDataTarget::ID_OPTION+true,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
        
        new FXRadioButton(MiscMatrix2,"off",new FXDataTarget((FXbool &) TmpOpts.ZeroMomentum),
            FXDataTarget::ID_OPTION+false,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);

        FXGroupBox *MiscGroup2=new FXGroupBox(MiscMatrix,"Planet Eaters",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        FXMatrix *MiscMatrix3=new FXMatrix(MiscGroup2,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        FXCheckButton *Check1 = new FXCheckButton(MiscMatrix3,"Planet Eaters",
            new FXDataTarget((FXbool &) TmpOpts.PlanetEaters),FXDataTarget::ID_VALUE,CHECKBUTTON_NORMAL);

        FXMatrix *MiscMatrix4=new FXMatrix(MiscMatrix3,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        new FXLabel(MiscMatrix4,"G:",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
        
        new FXTextField(MiscMatrix4,5,new FXDataTarget(TmpOpts.PlanetEatersG),
            FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
        
        new FXLabel(MiscMatrix4,"E+3",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        
        //group2 end
        
        
        //group3 strat
        FXGroupBox *group3=new FXGroupBox(LayoutMatrix2,"Friction",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        FXMatrix *FricMatrix=new FXMatrix(group3,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        new FXLabel(FricMatrix,"Z axis Gravity",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        FXRealSlider *slider4=new FXRealSlider(FricMatrix,new FXDataTarget(TmpOpts.ZGravity),
            FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
        slider4->setRange(0,10);
        new FXTextField(FricMatrix,10,new FXDataTarget(TmpOpts.ZGravity),FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
        
        new FXLabel(FricMatrix,"Static Coefficient",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        FXRealSlider *slider5=new FXRealSlider(FricMatrix,new FXDataTarget(TmpOpts.CoefficientStatic),
            FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
        slider5->setRange(0,1.5);
        new FXTextField(FricMatrix,10,new FXDataTarget(TmpOpts.CoefficientStatic),FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
        
        new FXLabel(FricMatrix,"Kinetic Coefficient",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        FXRealSlider *slider6=new FXRealSlider(FricMatrix,new FXDataTarget(TmpOpts.CoefficientKinetic),
            FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
        slider6->setRange(0,1.5);
        new FXTextField(FricMatrix,10,new FXDataTarget(TmpOpts.CoefficientKinetic),
            FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);

        FXGroupBox *FourthGroup = new FXGroupBox(LayoutMatrix2,"Constraints",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
        {
            FXMatrix *ConstraintsMatrix = new FXMatrix(FourthGroup, 3, MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
            new FXLabel(ConstraintsMatrix, "Max Speed");
            (new FXSlider(ConstraintsMatrix, new FXDataTarget(TmpOpts.MaxSpeed),
            FXDataTarget::ID_VALUE, LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH, 0, 0, 100))->setRange(0, 120);
            new FXTextField(ConstraintsMatrix,5,new FXDataTarget(TmpOpts.MaxSpeed),
            FXDataTarget::ID_VALUE,
            TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
        }
        
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

void OptionsFormDialogBox::PhysicsAndCosts(FXTabBook *TabBook)
{
    FXTabItem *PhysicsTab=new FXTabItem(TabBook,"&Physics",NULL);
    FXPacker *PhysicsPacker=new FXPacker(TabBook,FRAME_THICK|FRAME_RAISED);
        
    FXMatrix *MasterMatrix=new FXMatrix(PhysicsPacker,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXGroupBox *group1=new FXGroupBox(MasterMatrix,"Physics",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *matrix3=new FXMatrix(group1,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
     
    
    //Start of Medium group
    FXGroupBox *group2=new FXGroupBox(matrix3,"Medium properties",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *matrix=new FXMatrix(group2,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    new FXLabel(matrix,"The big blue screen is...",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXFrame(matrix,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
    
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
    new FXOption(popup3,"Ideal",NULL,NULL,FXDataTarget::ID_OPTION+0,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
    new FXOption(popup3,"Biological",NULL,NULL,FXDataTarget::ID_OPTION+1,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
    new FXOption(popup3,"Mechanical",NULL,NULL,FXDataTarget::ID_OPTION+2,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
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
    
    FXButton *button3 = new FXButton(matrix2, "Advanced Controls", NULL, this, this->ID_ADVANCEDPHYSICS,
        	BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
                0,0,0,0,10,10,0,0);
                
    FXGroupBox *group3=new FXGroupBox(MasterMatrix,"Costs and Returned Shots",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    {
        new FXLabel(group3,"Energy exchanged on hit",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        
        FXMatrix *matrix4=new FXMatrix(group3,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
        new FXRadioButton(matrix4,"Fixed",new FXDataTarget((FXbool &) TmpOpts.EnergyExType),
            FXDataTarget::ID_OPTION+false,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
    
        (new FXSpinner(matrix4,5,new FXDataTarget(TmpOpts.EnergyFix),
            FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW))->
            setRange(-10000, 10000);

        new FXLabel(matrix4, "nrg");

        new FXRadioButton(matrix4,"Propotional",new FXDataTarget((FXbool &) TmpOpts.EnergyExType),
            FXDataTarget::ID_OPTION+true,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);

        (new FXSpinner(matrix4,5,new FXDataTarget(TmpOpts.EnergyProp),
            FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW))->
            setRange(-10000, 10000);

        new FXLabel(matrix4, "%");
    }
}
