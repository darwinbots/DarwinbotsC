#include "OptionsForm.h"
#include "..\Engine\SimOptions.h"

FXDataTarget *Speciesqty =   new FXDataTarget;//(TmpOpts.Specie[0].qty);
FXDataTarget *Speciesnrg =   new FXDataTarget;//(TmpOpts.Specie[0].nrg);
FXDataTarget *Speciesbody =  new FXDataTarget;//(TmpOpts.Specie[0].body);
FXDataTarget *Speciescolor = new FXDataTarget;//(TmpOpts.Specie[0].color);
FXDataTarget *Speciesveggy = new FXDataTarget;
FXDataTarget *Speciesfixed = new FXDataTarget;

void OptionsFormDialogBox::Species(FXTabBook *TabBook)
{
    FXTabItem *linesTab=new FXTabItem(TabBook,"&Species",NULL);
    FXPacker *linesPage=new FXPacker(TabBook,FRAME_THICK|FRAME_RAISED);

    FXMatrix *SpeciesMasterMatrix = new FXMatrix(linesPage, 2,
        MATRIX_BY_COLUMNS|LAYOUT_FILL_ALL,
        0,0,0,0,
        0,0,0,0);
    {

        //Species List, left hand box
        FXMatrix *SpeciesListMasterMatrix = new FXMatrix(SpeciesMasterMatrix, 2,
            MATRIX_BY_ROWS|LAYOUT_FILL_ALL,
            0,0,0,0,
            0,0,0,0);

        //Species list and interface buttons
        FXGroupBox *SpeciesListFrame = new FXGroupBox(SpeciesListMasterMatrix, "Loaded Species", FRAME_RIDGE);
        {
        
            //Species List
            FXMatrix *SpeciesListMatrix = new FXMatrix(SpeciesListFrame, 2,
                MATRIX_BY_COLUMNS|LAYOUT_FILL_XY,
                0,0,0,0,
                0,0,0,0);
            {
                SpeciesList = new FXList(SpeciesListMatrix, this, OptionsFormDialogBox::ID_SELECTSPECIES,
                    LIST_BROWSESELECT | LAYOUT_FIX_WIDTH | LAYOUT_FIX_HEIGHT, 0, 0, 135, 135);
            }

            //Species List interface buttons
            FXMatrix *SpeciesListButtonMatrix = new FXMatrix(SpeciesListMatrix, 1,
                MATRIX_BY_COLUMNS|LAYOUT_FILL_ALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_SPACING / 2);
            {
                //                           icon, tgt, sel, options
                #define BUTTON_STUFF(signal) NULL, this, signal, BUTTON_NORMAL | LAYOUT_FILL_X
                FXButton *AddSpeciesButton = new FXButton(SpeciesListButtonMatrix, "Add Species", BUTTON_STUFF(this->ID_ADDSPECIES));
                FXButton *CloneSpeciesButton = new FXButton(SpeciesListButtonMatrix, "Clone Species", BUTTON_STUFF(this->ID_CLONESPECIES));
                FXButton *InheritSettingsSpeciesButton = new FXButton(SpeciesListButtonMatrix, "Inherit Settings", BUTTON_STUFF(this->ID_INHERITSPECIES));
                FXButton *DeleteSpeciesButton = new FXButton(SpeciesListButtonMatrix, "Delete Species", BUTTON_STUFF(this->ID_DELETESPECIES));
                new FXSeparator(SpeciesListButtonMatrix, LAYOUT_FILL_ALL);
                FXButton *DeleteAllSpeciesButton = new FXButton(SpeciesListButtonMatrix, "Clear List", BUTTON_STUFF(this->ID_DELETEALLSPECIES) | LAYOUT_BOTTOM);
                #undef BUTTON_STUFF
            }
        }
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
        FXColorWell *SpeciesColor = new FXColorWell(AppearanceMatrix, FXRGB(255,0,0), Speciescolor,
                                    FXDataTarget::ID_VALUE, COLORWELL_NORMAL | LAYOUT_FIX_WIDTH, 0, 0, 50, 0);

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
        FXSpinner *InitialPopulationSpinner = new FXSpinner(InitialPopulationTopRow, 5, Speciesqty,
                                              FXDataTarget::ID_VALUE, SPIN_NORMAL | FRAME_SUNKEN | FRAME_THICK | LAYOUT_RIGHT);
    
        InitialPopulationSpinner->setRange(0, 32000);

        FXMatrix *InitialPopulationButtonMatrix = new FXMatrix(InitialPopulationMatrix, 1, MATRIX_BY_ROWS,
            0,0,0,0,
            0,0,0,0,
            0,0);
    
        #undef BUTTON_STUFF
        //                   icon, tgt, sel, options
        #define BUTTON_STUFF(amt) NULL, Speciesqty, FXDataTarget::ID_OPTION + amt, BUTTON_NORMAL | LAYOUT_FILL_X
        
        new FXButton(InitialPopulationButtonMatrix, "0", BUTTON_STUFF(0) | LAYOUT_FIX_WIDTH, 0, 0, 33);
        new FXButton(InitialPopulationButtonMatrix, "1", BUTTON_STUFF(1) | LAYOUT_FIX_WIDTH, 0, 0, 33);
        new FXButton(InitialPopulationButtonMatrix, "5", BUTTON_STUFF(5) | LAYOUT_FIX_WIDTH, 0, 0, 33);
        new FXButton(InitialPopulationButtonMatrix, "10", BUTTON_STUFF(10) | LAYOUT_FIX_WIDTH, 0, 0, 33);
        new FXButton(InitialPopulationButtonMatrix, "30", BUTTON_STUFF(30) | LAYOUT_FIX_WIDTH, 0, 0, 33);
        new FXButton(InitialPopulationButtonMatrix, "100", BUTTON_STUFF(100) | LAYOUT_FIX_WIDTH, 0, 0, 33);
    
        ///////
        new FXSeparator(SpeciesInitializationFrame);

        FXMatrix *InitialEnergyMatrix = new FXMatrix(SpeciesInitializationFrame, 2, MATRIX_BY_ROWS);
        FXMatrix *InitialEnergyTopRow = new FXMatrix(InitialEnergyMatrix, 1, MATRIX_BY_ROWS | LAYOUT_FILL_ALL,
            0,0,0,0,
            0,0,0,0);
    
        new FXLabel(InitialEnergyTopRow, "Initial Energy");
        new FXSeparator(InitialEnergyTopRow, LAYOUT_FILL_ALL);
        FXSpinner *InitialEnergySpinner = new FXSpinner(InitialEnergyTopRow, 5, Speciesnrg,
                                          FXDataTarget::ID_VALUE, SPIN_NORMAL | FRAME_SUNKEN | FRAME_THICK | LAYOUT_RIGHT);
    
        InitialEnergySpinner->setRange(0, 32000);

        FXMatrix *InitialEnergyButtonMatrix = new FXMatrix(InitialEnergyMatrix, 1, MATRIX_BY_ROWS,
            0,0,0,0,
            0,0,0,0,
            0,0);
        
        #undef BUTTON_STUFF
        //                   icon, tgt, sel, options
        #define BUTTON_STUFF(amt) NULL, Speciesnrg, FXDataTarget::ID_OPTION + amt, BUTTON_NORMAL | LAYOUT_FILL_X
        
        new FXButton(InitialEnergyButtonMatrix, "2K", BUTTON_STUFF(2000) | LAYOUT_FIX_WIDTH, 0, 0, 33);
        new FXButton(InitialEnergyButtonMatrix, "3K", BUTTON_STUFF(3000) | LAYOUT_FIX_WIDTH, 0, 0, 33);
        new FXButton(InitialEnergyButtonMatrix, "5K", BUTTON_STUFF(5000) | LAYOUT_FIX_WIDTH, 0, 0, 33);
        new FXButton(InitialEnergyButtonMatrix, "10K", BUTTON_STUFF(10000) | LAYOUT_FIX_WIDTH, 0, 0, 33);
        new FXButton(InitialEnergyButtonMatrix, "20K", NULL, this, OptionsFormDialogBox::ID_NRG_20K,
            BUTTON_NORMAL | LAYOUT_FILL_X | LAYOUT_FIX_WIDTH, 0, 0, 33);
        new FXButton(InitialEnergyButtonMatrix, "30K", NULL, this, OptionsFormDialogBox::ID_NRG_30K,
            BUTTON_NORMAL | LAYOUT_FILL_X | LAYOUT_FIX_WIDTH, 0, 0, 33);

        //////////
        new FXSeparator(SpeciesInitializationFrame);

        FXMatrix *InitialBodyMatrix = new FXMatrix(SpeciesInitializationFrame, 2, MATRIX_BY_ROWS);
        FXMatrix *InitialBodyTopRow = new FXMatrix(InitialBodyMatrix, 1, MATRIX_BY_ROWS | LAYOUT_FILL_ALL,
            0,0,0,0,
            0,0,0,0);
    
        new FXLabel(InitialBodyTopRow, "Initial Body");
        new FXSeparator(InitialBodyTopRow, LAYOUT_FILL_ALL);
        FXSpinner *InitialBodySpinner = new FXSpinner(InitialBodyTopRow, 5, Speciesbody, FXDataTarget::ID_VALUE,
                                              SPIN_NORMAL | FRAME_SUNKEN | FRAME_THICK | LAYOUT_RIGHT);
        
        InitialBodySpinner->setRange(0, 32000);

        FXMatrix *InitialBodyButtonMatrix = new FXMatrix(InitialBodyMatrix, 1, MATRIX_BY_ROWS,
            0,0,0,0,
            0,0,0,0,
            0,0);
    
        #undef BUTTON_STUFF
        //                   icon, tgt, sel, options
        #define BUTTON_STUFF(amt) NULL, Speciesbody, FXDataTarget::ID_OPTION + amt, BUTTON_NORMAL | LAYOUT_FILL_X
        
        new FXButton(InitialBodyButtonMatrix, "100", BUTTON_STUFF(100) | LAYOUT_FIX_WIDTH, 0, 0, 33);
        new FXButton(InitialBodyButtonMatrix, "1K", BUTTON_STUFF(1000) | LAYOUT_FIX_WIDTH, 0, 0, 33);
        new FXButton(InitialBodyButtonMatrix, "3K", BUTTON_STUFF(3000) | LAYOUT_FIX_WIDTH, 0, 0, 33);
        new FXButton(InitialBodyButtonMatrix, "8K", BUTTON_STUFF(8000) | LAYOUT_FIX_WIDTH, 0, 0, 33);
        new FXButton(InitialBodyButtonMatrix, "15K", NULL, this, OptionsFormDialogBox::ID_BODY_15K,
            BUTTON_NORMAL | LAYOUT_FILL_X | LAYOUT_FIX_WIDTH, 0, 0, 33);
        new FXButton(InitialBodyButtonMatrix, "30K", NULL, this, OptionsFormDialogBox::ID_BODY_30K,
            BUTTON_NORMAL | LAYOUT_FILL_X | LAYOUT_FIX_WIDTH, 0, 0, 33);

        //////////
        ///////////////////////////////////////////////////////////////////

        new FXSeparator(SpeciesInitializationFrame);
        new FXLabel(SpeciesInitializationFrame, "Misc Species Details:");
        new FXCheckButton(SpeciesInitializationFrame, "Autotroph", Speciesveggy, FXDataTarget::ID_VALUE);
        new FXCheckButton(SpeciesInitializationFrame, "Fixed", Speciesfixed, FXDataTarget::ID_VALUE);
    }
}

long OptionsFormDialogBox::ReConnectToSpecies(unsigned int SpeciesNumber)
{
    Speciesqty->connect(TmpOpts.Specie[SpeciesNumber].qty);
    Speciesnrg->connect(TmpOpts.Specie[SpeciesNumber].nrg);
    Speciesbody->connect(TmpOpts.Specie[SpeciesNumber].body);
    Speciescolor->connect(TmpOpts.Specie[SpeciesNumber].color);
    Speciesveggy->connect((FXbool &)TmpOpts.Specie[SpeciesNumber].Veg);
    Speciesfixed->connect((FXbool &)TmpOpts.Specie[SpeciesNumber].Fixed);
    
    return 1;
}

long OptionsFormDialogBox::onSelectNewSpecies(FXObject *, FXSelector, void *)
{
    ReConnectToSpecies(SpeciesList->getCurrentItem());
    return 1;
}

long OptionsFormDialogBox::onAddNewSpecies(FXObject *, FXSelector, void *)
{
    const FXchar patterns[]="DNA Files (*.txt)\nAll Files (*)";
    FXFileDialog open(this,"Add Species");
    open.setPatternList(patterns);

    if(open.execute())
    {
        string fullpath = open.getFilename().text();
        string directory = open.getDirectory().text();

        fullpath.erase(0, directory.length() + 1);

        TmpOpts.AddSpecies(directory, fullpath);
        SpeciesList->appendItem(fullpath.c_str());

        SpeciesList->setCurrentItem(SpeciesList->getNumItems() - 1);

        onSelectNewSpecies(NULL, 0, NULL);
    }   
    
    return 1;
}

long OptionsFormDialogBox::onDeleteSpecies        (FXObject *, FXSelector, void *)
{
    TmpOpts.DeleteSpecies(SpeciesList->getCurrentItem());
    SpeciesList->removeItem(SpeciesList->getCurrentItem(), true);
    onSelectNewSpecies(NULL, 0, NULL);
    return 1;
}

long OptionsFormDialogBox::onClearListSpecies     (FXObject *, FXSelector, void *)
{
    //maybe ask for confirmation?

    if(MBOX_CLICKED_YES == FXMessageBox::warning(this,  FX::MBOX_YES_NO,
                     "Erasure Confirmation",
                     "Are you sure you want to clear the species list?"))
    {
        //delete list
        SpeciesList->clearItems(true);
        for(int x = 0; x < 50; x++)
            TmpOpts.DeleteSpecies(0);
    }
    
    return 1;
}

long OptionsFormDialogBox::onCloneSpecies        (FXObject *, FXSelector, void *)
{
    int x = 0;

    while(TmpOpts.Specie[x].Name != "")
        x++;

    TmpOpts.Specie[x] = TmpOpts.Specie[SpeciesList->getCurrentItem()];
    SpeciesList->appendItem(TmpOpts.Specie[x].Name.c_str());

    SpeciesList->setCurrentItem(SpeciesList->getNumItems() - 1);
    onSelectNewSpecies(NULL, 0, NULL);
    return 1;
}

long OptionsFormDialogBox::onInheritSpecies        (FXObject *, FXSelector, void *)
{
    int x = 0;

    while(TmpOpts.Specie[x].Name != "")
        x++;

    TmpOpts.Specie[x] = TmpOpts.Specie[SpeciesList->getCurrentItem()];

    const FXchar patterns[]="DNA Files (*.txt)\nAll Files (*)";
    FXFileDialog open(this,"Add Species with Inherited Settings");
    open.setPatternList(patterns);

    if(open.execute())
    {
        string fullpath = open.getFilename().text();
        string directory = open.getDirectory().text();

        fullpath.erase(0, directory.length() + 1);

        TmpOpts.Specie[x].Name = fullpath;
        TmpOpts.Specie[x].path = directory;

        SpeciesList->appendItem(fullpath.c_str());
        SpeciesList->setCurrentItem(SpeciesList->getNumItems() - 1);
        onSelectNewSpecies(NULL, 0, NULL);
    }   
    
    return 1;
}

long OptionsFormDialogBox::onNrgButton20K(FXObject *, FXSelector amt, void *)
{
    TmpOpts.Specie[SpeciesList->getCurrentItem()].nrg = 20000;
    return 1;
}

long OptionsFormDialogBox::onNrgButton30K(FXObject *, FXSelector amt, void *)
{
    TmpOpts.Specie[SpeciesList->getCurrentItem()].nrg = 30000;
    return 1;
}

long OptionsFormDialogBox::onBodyButton15K(FXObject *, FXSelector amt, void *)
{
    TmpOpts.Specie[SpeciesList->getCurrentItem()].body = 15000;
    return 1;
}

long OptionsFormDialogBox::onBodyButton30K(FXObject *, FXSelector amt, void *)
{
    TmpOpts.Specie[SpeciesList->getCurrentItem()].body = 30000;
    return 1;
}
