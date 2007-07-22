#include "OptionsForm.h"

//in: GeneralMatrix
void OptionsFormDialogBox::Veggy(FXTabBook *TabBook)
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
                    new FXCheckButton(PondModeCheckMatrix, "", new FXDataTarget((FXbool &)TmpOpts.PondMode), FXDataTarget::ID_VALUE,
                        ICON_AFTER_TEXT, LAYOUT_FILL_ALL);
                }
        

                //Light Intensity
                FXMatrix *LightIntensityMatrix = new FXMatrix(PondMode, 1, MATRIX_BY_ROWS | LAYOUT_FILL_ALL,
                    0,0,0,0,
                    0,0,0,0);
                {
                    new FXLabel(LightIntensityMatrix, "Light Intensity");
                    new FXSeparator(LightIntensityMatrix, LAYOUT_FILL_ALL);
                    new FXTextField(LightIntensityMatrix, 6, new FXDataTarget(TmpOpts.LightIntensity), FXDataTarget::ID_VALUE,
                        FRAME_SUNKEN|FRAME_THICK);
                }

                //Sediment Level
                FXMatrix *SedimentLevelMatrix = new FXMatrix(PondMode, 1, MATRIX_BY_ROWS | LAYOUT_FILL_ALL,
                    0,0,0,0,
                    0,0,0,0);
                {
                    new FXLabel(SedimentLevelMatrix, "Sediment Level");
                    new FXSeparator(SedimentLevelMatrix, LAYOUT_FILL_ALL);
                    new FXTextField(SedimentLevelMatrix, 6, new FXDataTarget(TmpOpts.Gradient), FXDataTarget::ID_VALUE,
                        FRAME_SUNKEN|FRAME_THICK | LAYOUT_SIDE_RIGHT);
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
            (new FXSpinner(PopulationControlMatrix, 5, new FXDataTarget(TmpOpts.MaxPopulation),
                 FXDataTarget::ID_VALUE, FRAME_SUNKEN | FRAME_THICK))->setRange(0, 10000);
            new FXLabel(PopulationControlMatrix, "Maximum Vegetable Population");
            
            (new FXSpinner(PopulationControlMatrix, 5, new FXDataTarget(TmpOpts.MinVegs),
                 FXDataTarget::ID_VALUE, FRAME_SUNKEN | FRAME_THICK))->setRange(0, 10000);
            new FXLabel(PopulationControlMatrix, "Repopulation Threshold");

            (new FXSpinner(PopulationControlMatrix, 5, new FXDataTarget(TmpOpts.RepopAmount),
                 FXDataTarget::ID_VALUE, FRAME_SUNKEN | FRAME_THICK))->setRange(0, 10000);
            new FXLabel(PopulationControlMatrix, "Vegetables per Repopulation Event");

            (new FXSpinner(PopulationControlMatrix, 5, new FXDataTarget(TmpOpts.RepopCooldown),
                 FXDataTarget::ID_VALUE, FRAME_SUNKEN | FRAME_THICK))->setRange(0, 10000);
            new FXLabel(PopulationControlMatrix, "Repopulation Cooldown Period");
        }

        FXGroupBox *VegFeedingDistFrame = new FXGroupBox(LeftColumn, "Vegetable Feeding Distribution", FRAME_RIDGE | LAYOUT_FILL_ALL);
        FXMatrix *VegFeedingDistMatrix = new FXMatrix(VegFeedingDistFrame, 1, MATRIX_BY_ROWS | LAYOUT_FILL_ALL);
        {
            new FXLabel(VegFeedingDistMatrix, "Energy");
            new FXSeparator(VegFeedingDistMatrix, LAYOUT_FILL_ALL);
            new FXSlider(VegFeedingDistMatrix, new FXDataTarget(TmpOpts.VegFeedingToBody), FXDataTarget::ID_VALUE, LAYOUT_FILL_ALL);
            new FXSeparator(VegFeedingDistMatrix, LAYOUT_FILL_ALL);
            new FXLabel(VegFeedingDistMatrix, "Body");
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

                new FXTextField(VeggyEnergyTopLine, 5, new FXDataTarget(TmpOpts.LightIntensity), FXDataTarget::ID_VALUE);
                new FXLabel(VeggyEnergyTopLine, "energy per");
            }

            //Radio buttons
            {
                FXMatrix *VeggyFeedingMethodMatrix = new FXMatrix(VeggyEnergyFrame, 1, MATRIX_BY_COLUMNS,
                    0,0,0,0,
                    0,0,0,0);
        
                new FXRadioButton(VeggyFeedingMethodMatrix, "Veggy per cycle",
                    new FXDataTarget(TmpOpts.VegFeedingMethod),FXDataTarget::ID_OPTION + 0, ICON_BEFORE_TEXT);
                new FXRadioButton(VeggyFeedingMethodMatrix,"1000 body points per cycle",
                    new FXDataTarget(TmpOpts.VegFeedingMethod),FXDataTarget::ID_OPTION + 1, ICON_BEFORE_TEXT);
                new FXRadioButton(VeggyFeedingMethodMatrix,"A Polynomial Function of Body",
                    new FXDataTarget(TmpOpts.VegFeedingMethod),FXDataTarget::ID_OPTION + 2, ICON_BEFORE_TEXT);
				new FXRadioButton(VeggyFeedingMethodMatrix,"A set amount of energy evenly distributed",
                    new FXDataTarget(TmpOpts.VegFeedingMethod),FXDataTarget::ID_OPTION + 3, ICON_BEFORE_TEXT);

            }

            new FXText(VeggyEnergyFrame, NULL, 0, LAYOUT_FILL_ALL);
        }

        //Day/night cycles
        FXGroupBox *DayNightFrame = new FXGroupBox(RightColumn, "Day Cycles", FRAME_RIDGE | LAYOUT_FILL_ALL);
        {
            new FXCheckButton(DayNightFrame,"Enable Day Cycles", new FXDataTarget((FXbool &)TmpOpts.DayNight),
                FXDataTarget::ID_VALUE);

            FXMatrix *DayNightSubMatrix = new FXMatrix(DayNightFrame, 1, MATRIX_BY_ROWS | LAYOUT_FILL_ALL,
                0,0,0,0,
                0,0,0,0);

            new FXLabel(DayNightSubMatrix,"Period",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
            new FXSeparator(DayNightSubMatrix, LAYOUT_FILL_COLUMN);
            (new FXSpinner(DayNightSubMatrix,6,new FXDataTarget(TmpOpts.CycleLength),
                FXDataTarget::ID_VALUE,FRAME_SUNKEN | FRAME_THICK))->
                setRange(0, 100000);
        }
    }
}
