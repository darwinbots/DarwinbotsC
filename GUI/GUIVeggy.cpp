#include "GUIMain.h"

//in: GeneralMatrix
long MainWindow::Veggy(FXTabBook *TabBook,FXDialogBox *Options)
{
    FXTabItem *Tab = new FXTabItem(TabBook,"&Veggy Controls",NULL);
    FXPacker *Page = new FXPacker(TabBook,FRAME_THICK|FRAME_RAISED);

    FXGroupBox *VeggyGroup = new FXGroupBox(Page,"Veggy Controls",
        GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    FXMatrix *MasterMatrix = new FXMatrix(VeggyGroup, 1, MATRIX_BY_ROWS | LAYOUT_FILL_ALL,
        0,0,0,0,
        0,0,0,0);

    //////////////////////////////////////////////////////////////////////
    FXMatrix *LeftColumn = new FXMatrix(MasterMatrix, 1, MATRIX_BY_COLUMNS | LAYOUT_FILL_ROW | LAYOUT_FILL_Y,
        0,0,0,0,
        0,0,0,0);
    {
        //Pond Mode Frame
        FXGroupBox *PondModeFrame = new FXGroupBox(LeftColumn, "Pond Mode", FRAME_RIDGE | LAYOUT_FILL_ALL);
        FXMatrix *UberPondMode = new FXMatrix(PondModeFrame, 1, MATRIX_BY_ROWS | LAYOUT_FILL_XR);
        {
        
            FXMatrix *PondMode = new FXMatrix(UberPondMode, 1, MATRIX_BY_COLUMNS | LAYOUT_FILL_XR,
                0,0,0,0,
                0,0,0,0);
            {

                //Pond Mode Check
                FXMatrix *PondModeCheckMatrix = new FXMatrix(PondMode, 1, MATRIX_BY_ROWS | LAYOUT_FILL_ALL,
                    0,0,0,0,
                    0,0,0,0);
                {
                    new FXLabel(PondModeCheckMatrix, "Pond Mode");
                    new FXSeparator(PondModeCheckMatrix, LAYOUT_FILL_ALL);
                    new FXCheckButton(PondModeCheckMatrix, "", NULL, 0, ICON_AFTER_TEXT, LAYOUT_FILL_ALL);
                }
        

                //Light Intensity
                FXMatrix *LightIntensityMatrix = new FXMatrix(PondMode, 1, MATRIX_BY_ROWS | LAYOUT_FILL_ALL,
                    0,0,0,0,
                    0,0,0,0);
                {
                    new FXLabel(LightIntensityMatrix, "Light Intensity");
                    new FXSeparator(LightIntensityMatrix, LAYOUT_FILL_ALL);
                    new FXSpinner(LightIntensityMatrix, 4, NULL, 0, FRAME_SUNKEN|FRAME_THICK);
                }

                //Light Intensity
                FXMatrix *SedimentLevelMatrix = new FXMatrix(PondMode, 1, MATRIX_BY_ROWS | LAYOUT_FILL_ALL,
                    0,0,0,0,
                    0,0,0,0);
                {
                    new FXLabel(SedimentLevelMatrix, "Sediment Level");
                    new FXSeparator(SedimentLevelMatrix, LAYOUT_FILL_ALL);
                    new FXSpinner(SedimentLevelMatrix, 4, NULL, 0, FRAME_SUNKEN|FRAME_THICK | LAYOUT_SIDE_RIGHT);
                }
            }

            FXMatrix *DepthGraphMatrix = new FXMatrix(UberPondMode, 1, MATRIX_BY_COLUMNS | LAYOUT_FILL_ALL,
                0,0,0,0,
                0,0,0,0);
            {
                new FXGroupBox(DepthGraphMatrix, "Light", FRAME_RIDGE | LAYOUT_FILL_ALL);

                //LATER: we need to create a light intensity gradient and place it here
            }
        }//end pond mode frame        

        FXGroupBox *PopulationControlFrame = new FXGroupBox(LeftColumn, "Population Control", FRAME_RIDGE | LAYOUT_FILL_ALL);
        FXMatrix *PopulationControlMatrix = new FXMatrix(PopulationControlFrame, 2, MATRIX_BY_COLUMNS,
            0,0,0,0,
            0,0,0,0);
        {
            new FXSpinner(PopulationControlMatrix, 5, NULL, 0, FRAME_SUNKEN | FRAME_THICK);
            new FXLabel(PopulationControlMatrix, "Maximum Vegetable Population");
            
            new FXSpinner(PopulationControlMatrix, 5, NULL, 0, FRAME_SUNKEN | FRAME_THICK);
            new FXLabel(PopulationControlMatrix, "Repopulation Threshold");

            new FXSpinner(PopulationControlMatrix, 5, NULL, 0, FRAME_SUNKEN | FRAME_THICK);
            new FXLabel(PopulationControlMatrix, "Vegetables per Repopulation Event");

            new FXSpinner(PopulationControlMatrix, 5, NULL, 0, FRAME_SUNKEN | FRAME_THICK);
            new FXLabel(PopulationControlMatrix, "Repopulation Cooldown Period");
        }

        FXGroupBox *VegFeedingDistFrame = new FXGroupBox(LeftColumn, "Vegetable Feeding Distribution", FRAME_RIDGE | LAYOUT_FILL_ALL);
        FXMatrix *VegFeedingDistMatrix = new FXMatrix(VegFeedingDistFrame, 1, MATRIX_BY_ROWS);
        {
            new FXLabel(VegFeedingDistMatrix, "Hi");
            new FXLabel(VegFeedingDistMatrix, "Hi");
            new FXLabel(VegFeedingDistMatrix, "Hi");
        }
    }

    ///////////////////////////////////////////////////////////////////////
    FXMatrix *RightColumn = new FXMatrix(MasterMatrix, 1, MATRIX_BY_COLUMNS | LAYOUT_FILL_ROW | LAYOUT_FILL_Y,
        0,0,0,0,
        0,0,0,0);
    {

        //Veggy Energy
        FXGroupBox *VeggyEnergyFrame = new FXGroupBox(RightColumn, "Veggy Energy", FRAME_RIDGE | LAYOUT_FILL_ALL);
        {

            //XXXXX nrg per
            {
                FXMatrix *VeggyEnergyTopLine = new FXMatrix(VeggyEnergyFrame, 1, MATRIX_BY_ROWS,
                    0,0,0,0,
                    0,0,0,0);

                new FXTextField(VeggyEnergyTopLine, 5);
                new FXLabel(VeggyEnergyTopLine, "energy per");
            }

            //Radio buttons
            {
                FXMatrix *VeggyFeedingMethodMatrix = new FXMatrix(VeggyEnergyFrame, 1, MATRIX_BY_COLUMNS,
                    0,0,0,0,
                    0,0,0,0);
        
                new FXRadioButton(VeggyFeedingMethodMatrix, "Veggy per cycle",0,0, ICON_BEFORE_TEXT);
                new FXRadioButton(VeggyFeedingMethodMatrix,"1000 body points per cycle",0,0, ICON_BEFORE_TEXT);
                new FXRadioButton(VeggyFeedingMethodMatrix,"A Polynomial Function of Body",0,0, ICON_BEFORE_TEXT);
            }

            new FXText(VeggyEnergyFrame, NULL, 0, LAYOUT_FILL_ALL);
        }

        //Day/night cycles
        FXGroupBox *DayNightFrame = new FXGroupBox(RightColumn, "Day Cycles", FRAME_RIDGE | LAYOUT_FILL_ALL);
        {
            new FXCheckButton(DayNightFrame,"Enable Day Cycles");

            FXMatrix *DayNightSubMatrix = new FXMatrix(DayNightFrame, 1, MATRIX_BY_ROWS | LAYOUT_FILL_ALL,
                0,0,0,0,
                0,0,0,0);

            new FXLabel(DayNightSubMatrix,"Period",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
            new FXSeparator(DayNightSubMatrix, LAYOUT_FILL_COLUMN);
            new FXSpinner(DayNightSubMatrix,6,0,FXDataTarget::ID_VALUE,SPIN_CYCLIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW);
        }
    }





    
/*


















    FXMatrix *PopMatrix=new FXMatrix(PopulationGroup,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *PopMatrix2=new FXMatrix(PopMatrix,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMatrix *PopMatrix4=new FXMatrix(PopMatrix2,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXGroupBox *PopulationGroup4=new FXGroupBox(PopMatrix4,"Pond Mode",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
       
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
    new FXLabel(VBMatrix,"Body",NULL,LAYOUT_LEFT|JUSTIFY_RIGHT);*/
    return 1;
}