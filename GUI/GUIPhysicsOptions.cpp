#include "GUImain.h"

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
        new FXTextField(FluidMatrix,10,&Viscosity_Tar,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
        new FXLabel(FluidMatrix,"E-5 Bangs per square twips",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        
        new FXLabel(FluidMatrix,"Density",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
        new FXTextField(FluidMatrix,10,&Density_Tar,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
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
        FXRealSlider *slider2=new FXRealSlider(MiscMatrix,&YGravity_Tar,FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
        slider2->setRange(0,10);
        new FXTextField(MiscMatrix,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);

        new FXLabel(MiscMatrix,"Brownian Motion",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        FXRealSlider *slider3=new FXRealSlider(MiscMatrix,&Brownian_Tar,FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
        slider3->setRange(0,10);
        new FXTextField(MiscMatrix,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);


        FXGroupBox *MiscGroup=new FXGroupBox(MiscMatrix,"Toggles",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        FXMatrix *MiscMatrix2=new FXMatrix(MiscGroup,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        new FXLabel(MiscMatrix2,"Zero Momentum",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        
        new FXRadioButton(MiscMatrix2,"on",0,FXDataTarget::ID_OPTION+0,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
        
        new FXRadioButton(MiscMatrix2,"off",0,FXDataTarget::ID_OPTION+1,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);

        FXGroupBox *MiscGroup2=new FXGroupBox(MiscMatrix,"Planet Eaters",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        FXMatrix *MiscMatrix3=new FXMatrix(MiscGroup2,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        FXCheckButton *Check1 = new FXCheckButton(MiscMatrix3,"Planet Eaters",&PlanetEaters_Tar,FXDataTarget::ID_VALUE,CHECKBUTTON_NORMAL);

        FXMatrix *MiscMatrix4=new FXMatrix(MiscMatrix3,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        new FXLabel(MiscMatrix4,"G:",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
        
        new FXTextField(MiscMatrix4,5,&PlanetEatersG_Tar,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
        
        new FXLabel(MiscMatrix4,"E+3",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        
        //group2 end
        
        
        //group3 strat
        FXGroupBox *group3=new FXGroupBox(LayoutMatrix2,"Friction",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        FXMatrix *FricMatrix=new FXMatrix(group3,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

        new FXLabel(FricMatrix,"Z axis Gravity",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        FXRealSlider *slider4=new FXRealSlider(FricMatrix,&YGravity_Tar,FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
        slider4->setRange(0,10);
        new FXTextField(FricMatrix,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
        
        new FXLabel(FricMatrix,"Static Coefficient",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        FXRealSlider *slider5=new FXRealSlider(FricMatrix,&CoefficientStatic_Tar,FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
        slider5->setRange(0,1.5);
        new FXTextField(FricMatrix,10,0,FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
        
        new FXLabel(FricMatrix,"Kinetic Coefficient",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        FXRealSlider *slider6=new FXRealSlider(FricMatrix,&CoefficientKinetic_Tar,FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100);
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
    
    FXMatrix *LayoutMatrixMain=new FXMatrix(linesPage3,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *LayoutMatrix=new FXMatrix(LayoutMatrixMain,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    FXGroupBox *group1=new FXGroupBox(LayoutMatrix,"Physics",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    FXMatrix *matrix3=new FXMatrix(group1,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
     
    
    //Start of Medium group
    FXGroupBox *group2=new FXGroupBox(matrix3,"Medium properties",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *matrix=new FXMatrix(group2,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    new FXLabel(matrix,"The big blue screen is a...",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
    new FXFrame(matrix,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
    
    new FXRadioButton(matrix,"Fluid",0,FXDataTarget::ID_OPTION+0,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
    
    new FXRadioButton(matrix,"Solid",0,FXDataTarget::ID_OPTION+1,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
                
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
    new FXOption(popup3,"Ideal",NULL,&MovingEfficiency_Tar,FXDataTarget::ID_OPTION+0,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
    new FXOption(popup3,"Biological",NULL,&MovingEfficiency_Tar,FXDataTarget::ID_OPTION+1,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
    new FXOption(popup3,"Mechanical",NULL,&MovingEfficiency_Tar,FXDataTarget::ID_OPTION+2,JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
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
    
    new FXRadioButton(matrix4,"Fixed",0,FXDataTarget::ID_OPTION+0,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
    
    new FXSpinner(matrix4,5,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);

    new FXRadioButton(matrix4,"Propotional",0,FXDataTarget::ID_OPTION+1,LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);

    new FXSpinner(matrix4,5,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);

    FXGroupBox *buttongroup=new FXGroupBox(LayoutMatrixMain,0,GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    FXMatrix *GroupMatrix=new FXMatrix(buttongroup,6,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    FXButton *button5 = new FXButton(GroupMatrix, "Load Settings", 0, Options,
        	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
                0,0,0,0,10,10,0,0);

    FXButton *button6 = new FXButton(GroupMatrix, "Save Settings", 0, Options,
        	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
                0,0,0,0,10,10,0,0);
                
    FXButton *button7 = new FXButton(GroupMatrix, "Cancel", 0, Options,
        	FXDialogBox::ID_CANCEL, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
                0,0,0,0,10,10,0,0);
                
    FXButton *button8 = new FXButton(GroupMatrix, "Pause", 0, Options,
        	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
                0,0,0,0,10,10,0,0);
                
    FXButton *button9 = new FXButton(GroupMatrix, "Start New", 0, Options,
        	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
                0,0,0,0,10,10,0,0);
                
    FXButton *button10 = new FXButton(GroupMatrix, "Change", 0, Options,
        	FXDialogBox::ID_ACCEPT, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
                0,0,0,0,10,10,0,0);

	return 1;
}
