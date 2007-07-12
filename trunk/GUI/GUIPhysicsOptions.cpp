#include "OptionsForm.h"

void OptionsFormDialogBox::PhysicsAndCosts(FXTabBook *TabBook)
{
    FXTabItem *PhysicsTab=new FXTabItem(TabBook,"&Physics",NULL);
    FXPacker *PhysicsPacker=new FXPacker(TabBook,FRAME_THICK|FRAME_RAISED);
    
    FXMatrix *MasterMatrix = new FXMatrix(PhysicsPacker,1,MATRIX_BY_ROWS|LAYOUT_SIDE_TOP);
    {    
        FXGroupBox *FluidFrame=new FXGroupBox(MasterMatrix,"Fluid Dynamics",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
        {
            FXMatrix *FluidMatrix=new FXMatrix(FluidFrame,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
            {
                new FXLabel(FluidMatrix,"Viscosity",NULL);
                new FXTextField(FluidMatrix,10,new FXDataTarget(TmpOpts.Viscosity),FXDataTarget::ID_VALUE,
                    TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
                new FXLabel(FluidMatrix,"E-5 Bangs / twips^2",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
    
                new FXLabel(FluidMatrix,"Density",NULL);
                new FXTextField(FluidMatrix,10,new FXDataTarget(TmpOpts.Density),
                    FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|
                    FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
                new FXLabel(FluidMatrix,"E-5 Mass / twip^3",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);

                new FXLabel(FluidMatrix,"Reynolds Number",NULL);
                new FXTextField(FluidMatrix,10,NULL /*new FXDataTarget()*/,
                    0,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
                new FXLabel(FluidMatrix,"(unitless)",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
            }
        }

        FXGroupBox *FrictionFrame = new FXGroupBox(MasterMatrix,"Friction",
            GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
        {
            FXMatrix *FrictionMatrix = new FXMatrix(FrictionFrame,3,
                MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
            {
                new FXLabel(FrictionMatrix,"Z axis Gravity",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
                (new FXRealSlider(FrictionMatrix,new FXDataTarget(TmpOpts.ZGravity),
                    FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100))->
                setRange(0,10);
                new FXTextField(FrictionMatrix,10,new FXDataTarget(TmpOpts.ZGravity),FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
    
                new FXLabel(FrictionMatrix,"Static Coefficient",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
                (new FXRealSlider(FrictionMatrix,new FXDataTarget(TmpOpts.CoefficientStatic),
                    FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100))->
                setRange(0,1.5);
                new FXTextField(FrictionMatrix,10,new FXDataTarget(TmpOpts.CoefficientStatic),FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
    
                new FXLabel(FrictionMatrix,"Kinetic Coefficient",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
                (new FXRealSlider(FrictionMatrix,new FXDataTarget(TmpOpts.CoefficientKinetic),
                    FXDataTarget::ID_VALUE,LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH,0,0,100))->
                setRange(0,1.5);
                new FXTextField(FrictionMatrix,10,new FXDataTarget(TmpOpts.CoefficientKinetic),
                    FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
            }        
        }
    }
    
    MasterMatrix = new FXMatrix(PhysicsPacker,1,MATRIX_BY_ROWS);
    
    FXMatrix *LeftMatrix = new FXMatrix(MasterMatrix,1,MATRIX_BY_COLUMNS | LAYOUT_FILL_ALL, 
        0,0,0,0,
        0,0,0,0);
    {
        FXMatrix *ConstraintsMatrix = new FXMatrix(
            new FXGroupBox(LeftMatrix,"Constraints",
            GROUPBOX_TITLE_LEFT|FRAME_RIDGE | LAYOUT_FILL_ALL),
            3, MATRIX_BY_COLUMNS | LAYOUT_FILL_ALL);
        {
            new FXLabel(ConstraintsMatrix, "Max Speed");
        
            (new FXRealSlider(ConstraintsMatrix, new FXDataTarget(TmpOpts.MaxSpeed),
            FXDataTarget::ID_VALUE,LAYOUT_FIX_WIDTH, 0, 0, 100))->setRange(0, 120);
        
            new FXTextField(ConstraintsMatrix,5,new FXDataTarget(TmpOpts.MaxSpeed), FXDataTarget::ID_VALUE,
            TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
        }

        //Returned Shots
        FXGroupBox *ReturnedShotsFrame = new FXGroupBox(LeftMatrix,"Returned Shots",
            GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
        {
            new FXLabel(ReturnedShotsFrame,"Energy exchanged on hit",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        
            FXMatrix *matrix4=new FXMatrix(ReturnedShotsFrame,
                3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
            {
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
    }

    FXGroupBox *group2=new FXGroupBox(MasterMatrix,"Misc",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_ALL);
    {
        FXMatrix *MiscMatrix=new FXMatrix(group2,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_ALL);

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


        //Toggles Group
        FXGroupBox *MiscGroup=new FXGroupBox(MiscMatrix,"Toggles",
            GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_ALL);
        {
            new FXCheckButton(MiscGroup, "Zero Momentum", new FXDataTarget((FXbool &) TmpOpts.ZeroMomentum),
                FXDataTarget::ID_VALUE,LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW|ICON_BEFORE_TEXT);
        }

        //Planet Eaters
        FXGroupBox *MiscGroup2=new FXGroupBox(MiscMatrix,"Planet Eaters",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_ALL);
        FXMatrix *MiscMatrix3=new FXMatrix(MiscGroup2,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_ALL);
        {

            FXMatrix *MiscMatrix4=new FXMatrix(MiscMatrix3,3,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

            new FXLabel(MiscMatrix4,"Constant:",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);

            new FXTextField(MiscMatrix4,5,new FXDataTarget(TmpOpts.PlanetEatersG),
                FXDataTarget::ID_VALUE,TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
    
            new FXLabel(MiscMatrix4,"E+3",NULL,LAYOUT_LEFT|JUSTIFY_LEFT);
        }
    }

    FXMatrix *ButtonToolbarMatrix = new FXMatrix(new FXGroupBox(PhysicsPacker, ""), 1, MATRIX_BY_ROWS);
    {    
        new FXButton(ButtonToolbarMatrix, "Help on Units", 0, NULL,
            0, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK,
            0,0,0,0,10,10,0,0);
    
        new FXButton(ButtonToolbarMatrix, "General Help", 0, NULL,
        	0, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK,
            0,0,0,0,10,10,0,0);
    }
}
