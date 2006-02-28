#include "GUImain.h"

long MainWindow::Species(FXTabBook *TabBook,FXDialogBox *Options)
{
    FXTabItem *linesTab=new FXTabItem(TabBook,"&Species",NULL);
    FXPacker *linesPage=new FXPacker(TabBook,FRAME_THICK|FRAME_RAISED);

    FXMatrix *SpeciesMasterMatrix = new FXMatrix(linesPage, 2,
        MATRIX_BY_COLUMNS|LAYOUT_FILL_ALL);

    //Species List, left hand box
    FXMatrix *SpeciesListMasterMatrix = new FXMatrix(SpeciesMasterMatrix, 2,
        MATRIX_BY_ROWS|LAYOUT_FILL_ALL,
        0,0,0,0,
        0,0,0,0);

    /////////////////////////////////////////////////////////////////
    FXGroupBox *SpeciesListFrame = new FXGroupBox(SpeciesListMasterMatrix,
                                                  "Loaded Species",
                                                  FRAME_RIDGE);

    FXMatrix *SpeciesListMatrix = new FXMatrix(SpeciesListFrame, 2,
        MATRIX_BY_COLUMNS|LAYOUT_FILL_XY);

    FXList *SpeciesList = new FXList(SpeciesListMatrix, NULL, 0,
        LIST_BROWSESELECT | LAYOUT_FIX_WIDTH | LAYOUT_FIX_HEIGHT,
        0, 0, //x, y
        135,  //width
        135);

    //////STRICLTY FOR TESTING PURPOSES ////
    SpeciesList->appendItem("item 1");      
    SpeciesList->appendItem("item 2");      
    SpeciesList->appendItem("item 3");      
    SpeciesList->appendItem("item 4");      
    SpeciesList->appendItem("item 5");      
    SpeciesList->appendItem("item 6");      
    SpeciesList->appendItem("item 7");      
    SpeciesList->appendItem("item 8");      
    SpeciesList->appendItem("item 9");      
    SpeciesList->appendItem("item 10");     
    ////////////////////////////////////////

    //                   icon, tgt, sel, options
    #define BUTTON_STUFF NULL, NULL, 0, BUTTON_NORMAL | LAYOUT_FILL_X

    FXMatrix *SpeciesListButtonMatrix = new FXMatrix(SpeciesListMatrix, 1,
        MATRIX_BY_COLUMNS|LAYOUT_FILL_ALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_SPACING / 2);

    FXButton *AddSpeciesButton = new FXButton(SpeciesListButtonMatrix, "Add Species", BUTTON_STUFF);
    FXButton *CloneSpeciesButton = new FXButton(SpeciesListButtonMatrix, "Clone Species", BUTTON_STUFF);
    FXButton *InheritSettingsSpeciesButton = new FXButton(SpeciesListButtonMatrix, "Inherit Settings", BUTTON_STUFF);
    FXButton *DeleteSpeciesButton = new FXButton(SpeciesListButtonMatrix, "Delete Species", BUTTON_STUFF);
    new FXSeparator(SpeciesListButtonMatrix, LAYOUT_FILL_ALL);
    FXButton *DeleteAllSpeciesButton = new FXButton(SpeciesListButtonMatrix, "Clear List", BUTTON_STUFF | LAYOUT_BOTTOM);
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    FXGroupBox *CommentBoxFrame = new FXGroupBox(SpeciesListMasterMatrix,
                                              "Comments and Help",
                                              FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXText *CommentBox = new FXText(CommentBoxFrame, NULL, 0,
        FRAME_SUNKEN|FRAME_THICK|TEXT_WORDWRAP|
        LAYOUT_FILL_X | LAYOUT_FIX_HEIGHT, 0, 0,
        0, //width (dynamcially set)
        121);

    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////
    
    //Species List, left hand box
    FXMatrix *SpeciesDetailsMasterMatrix = new FXMatrix(SpeciesMasterMatrix, 2,
        MATRIX_BY_COLUMNS|LAYOUT_FILL_ALL,
        0,0,0,0,
        0,0,0,0);

    FXMatrix *SpeciesDetailsMasterMatrixLeft = new FXMatrix(SpeciesDetailsMasterMatrix, 2,
        MATRIX_BY_ROWS|LAYOUT_FILL_ALL,
        0,0,0,0,
        0,DEFAULT_SPACING,0,0);

    ///////////////////////////////////////////////////////////////////////
    FXGroupBox *SpeciesAppearanceFrame = new FXGroupBox(SpeciesDetailsMasterMatrixLeft,
                                         "Appearance",
                                         FRAME_RIDGE|LAYOUT_FILL_ALL);
    
    FXMatrix *AppearanceMatrix = new FXMatrix(SpeciesAppearanceFrame, 1, MATRIX_BY_ROWS);
    
    new FXLabel(AppearanceMatrix, "Color");
    FXColorWell *SpeciesColor = new FXColorWell(AppearanceMatrix, FXRGB(255,0,0), NULL,
                                0, COLORWELL_NORMAL | LAYOUT_FIX_WIDTH, 0, 0, 50, 0);

    ///////////////////////////////////////////////////////////////////////
    FXGroupBox *SpeciesPositionControlFrame = new FXGroupBox(SpeciesDetailsMasterMatrixLeft,
                                              "Position Control",
                                              FRAME_RIDGE|LAYOUT_FILL_ALL);
    
    ///////////////////////////////////////////////////////////////////////
    FXGroupBox *SpeciesInitializationFrame = new FXGroupBox(SpeciesDetailsMasterMatrix,
                                             "Species Initial Settings",
                                             FRAME_RIDGE|LAYOUT_FILL_ALL);
    
    
    ///////////////////
    FXMatrix *InitialPopulationMatrix = new FXMatrix(SpeciesInitializationFrame, 2, MATRIX_BY_ROWS);
    FXMatrix *InitialPopulationTopRow = new FXMatrix(InitialPopulationMatrix, 1, MATRIX_BY_ROWS | LAYOUT_FILL_ALL,
        0,0,0,0,
        0,0,0,0);
    
    new FXLabel(InitialPopulationTopRow, "Initial Population");
    new FXSeparator(InitialPopulationTopRow, LAYOUT_FILL_ALL);
    FXSpinner *InitialPopulationSpinner = new FXSpinner(InitialPopulationTopRow, 4, NULL, 0,
                                          SPIN_NORMAL | FRAME_SUNKEN | FRAME_THICK | LAYOUT_RIGHT);
    
    InitialPopulationSpinner->setRange(0, 5000);

    FXMatrix *InitialPopulationButtonMatrix = new FXMatrix(InitialPopulationMatrix, 1, MATRIX_BY_ROWS,
        0,0,0,0,
        0,0,0,0,
        0,0);
    
    new FXButton(InitialPopulationButtonMatrix, "0", BUTTON_STUFF | LAYOUT_FIX_WIDTH, 0, 0, 33);
    new FXButton(InitialPopulationButtonMatrix, "1", BUTTON_STUFF | LAYOUT_FIX_WIDTH, 0, 0, 33);
    new FXButton(InitialPopulationButtonMatrix, "5", BUTTON_STUFF | LAYOUT_FIX_WIDTH, 0, 0, 33);
    new FXButton(InitialPopulationButtonMatrix, "10", BUTTON_STUFF | LAYOUT_FIX_WIDTH, 0, 0, 33);
    new FXButton(InitialPopulationButtonMatrix, "30", BUTTON_STUFF | LAYOUT_FIX_WIDTH, 0, 0, 33);
    new FXButton(InitialPopulationButtonMatrix, "100", BUTTON_STUFF | LAYOUT_FIX_WIDTH, 0, 0, 33);
    
    ///////
    new FXSeparator(SpeciesInitializationFrame);

    FXMatrix *InitialEnergyMatrix = new FXMatrix(SpeciesInitializationFrame, 2, MATRIX_BY_ROWS);
    FXMatrix *InitialEnergyTopRow = new FXMatrix(InitialEnergyMatrix, 1, MATRIX_BY_ROWS | LAYOUT_FILL_ALL,
        0,0,0,0,
        0,0,0,0);
    
    new FXLabel(InitialEnergyTopRow, "Initial Energy");
    new FXSeparator(InitialEnergyTopRow, LAYOUT_FILL_ALL);
    FXSpinner *InitialEnergySpinner = new FXSpinner(InitialEnergyTopRow, 4, NULL, 0,
                                          SPIN_NORMAL | FRAME_SUNKEN | FRAME_THICK | LAYOUT_RIGHT);
    
    InitialEnergySpinner->setRange(0, 32000);

    FXMatrix *InitialEnergyButtonMatrix = new FXMatrix(InitialEnergyMatrix, 1, MATRIX_BY_ROWS,
        0,0,0,0,
        0,0,0,0,
        0,0);
    
    new FXButton(InitialEnergyButtonMatrix, "2K", BUTTON_STUFF | LAYOUT_FIX_WIDTH, 0, 0, 33);
    new FXButton(InitialEnergyButtonMatrix, "3K", BUTTON_STUFF | LAYOUT_FIX_WIDTH, 0, 0, 33);
    new FXButton(InitialEnergyButtonMatrix, "5K", BUTTON_STUFF | LAYOUT_FIX_WIDTH, 0, 0, 33);
    new FXButton(InitialEnergyButtonMatrix, "10K", BUTTON_STUFF | LAYOUT_FIX_WIDTH, 0, 0, 33);
    new FXButton(InitialEnergyButtonMatrix, "20K", BUTTON_STUFF | LAYOUT_FIX_WIDTH, 0, 0, 33);
    new FXButton(InitialEnergyButtonMatrix, "30K", BUTTON_STUFF | LAYOUT_FIX_WIDTH, 0, 0, 33);

    //////////
    new FXSeparator(SpeciesInitializationFrame);

    FXMatrix *InitialBodyMatrix = new FXMatrix(SpeciesInitializationFrame, 2, MATRIX_BY_ROWS);
    FXMatrix *InitialBodyTopRow = new FXMatrix(InitialBodyMatrix, 1, MATRIX_BY_ROWS | LAYOUT_FILL_ALL,
        0,0,0,0,
        0,0,0,0);
    
    new FXLabel(InitialBodyTopRow, "Initial Body");
    new FXSeparator(InitialBodyTopRow, LAYOUT_FILL_ALL);
    FXSpinner *InitialBodySpinner = new FXSpinner(InitialBodyTopRow, 4, NULL, 0,
                                          SPIN_NORMAL | FRAME_SUNKEN | FRAME_THICK | LAYOUT_RIGHT);
    
    InitialBodySpinner->setRange(0, 32000);

    FXMatrix *InitialBodyButtonMatrix = new FXMatrix(InitialBodyMatrix, 1, MATRIX_BY_ROWS,
        0,0,0,0,
        0,0,0,0,
        0,0);
    
    new FXButton(InitialBodyButtonMatrix, "100", BUTTON_STUFF | LAYOUT_FIX_WIDTH, 0, 0, 33);
    new FXButton(InitialBodyButtonMatrix, "1K", BUTTON_STUFF | LAYOUT_FIX_WIDTH, 0, 0, 33);
    new FXButton(InitialBodyButtonMatrix, "3K", BUTTON_STUFF | LAYOUT_FIX_WIDTH, 0, 0, 33);
    new FXButton(InitialBodyButtonMatrix, "8K", BUTTON_STUFF | LAYOUT_FIX_WIDTH, 0, 0, 33);
    new FXButton(InitialBodyButtonMatrix, "15K", BUTTON_STUFF | LAYOUT_FIX_WIDTH, 0, 0, 33);
    new FXButton(InitialBodyButtonMatrix, "30K", BUTTON_STUFF | LAYOUT_FIX_WIDTH, 0, 0, 33);


    return 1;
}

void SetupSpeciesList()
{



}

/*
1 matrix over all

first subdivision is split thusly:

<--1--><----2---->

where 1 is the species list and comment box
2 is the species appearance and starting details box*/