#include "OptionsForm.h"
#include "../Engine/HardDriveRoutines.h"
#include "../Engine/Engine.h"
#include "../Engine/EngineThread.h"

FXIMPLEMENT(OptionsFormDialogBox, FXDialogBox,
    OptionsFormDialogBoxMap, ARRAYNUMBER(OptionsFormDialogBoxMap))

OptionsFormDialogBox::OptionsFormDialogBox(FXComposite *parent) : 
    FXDialogBox(parent, "Sim Options", DECOR_TITLE | DECOR_BORDER)
{
    FXMatrix *LayoutMatrix = new FXMatrix(this, 1, MATRIX_BY_COLUMNS |
        LAYOUT_FILL_X | LAYOUT_FILL_Y | LAYOUT_FILL_ROW | LAYOUT_FILL_COLUMN,
        0,0,0,0,
        0,0,0,0);
    
    FXTabBook *tabbook=new FXTabBook(LayoutMatrix,NULL,0,
        LAYOUT_FILL_X | LAYOUT_FILL_Y | LAYOUT_FILL_ROW | LAYOUT_FILL_COLUMN);
    
    Species(tabbook);
    General(tabbook);
    Veggy(tabbook);
    PhysicsAndCosts(tabbook);
    CostsOptions(tabbook);
    //Mutations(tabbook);
    //ReststartAndL(tabbook);
    //InternetOptions(tabbook);
    //Recording(tabbook);
    
    BottomToolbar(LayoutMatrix);
}

void OptionsFormDialogBox::BottomToolbar(FXMatrix *LayoutMatrix)
{
    FXGroupBox *ButtonGroup=new FXGroupBox(LayoutMatrix,NULL,FRAME_RIDGE | LAYOUT_FILL_X | LAYOUT_FILL_ROW);
    FXMatrix *ButtonMatrix = new FXMatrix(ButtonGroup, 1, MATRIX_BY_ROWS | LAYOUT_FILL_X | LAYOUT_FILL_ROW,
        0,0,0,0,0,0,0,0);
    
    new FXButton(ButtonMatrix, "Load Settings", 0, this, OptionsFormDialogBox::ID_LOADSETTINGS);
    new FXButton(ButtonMatrix, "Save Settings", 0, this, OptionsFormDialogBox::ID_SAVESETTINGS);
    
    new FXSeparator(ButtonMatrix, LAYOUT_FILL_X|LAYOUT_FILL_COLUMN);
    new FXButton(ButtonMatrix, "Cancel", 0, this, FXDialogBox::ID_CANCEL);
    new FXSeparator(ButtonMatrix, LAYOUT_FILL_X|LAYOUT_FILL_COLUMN);
    
    new FXButton(ButtonMatrix, "Pause", 0, NULL, 0);
    new FXButton(ButtonMatrix, "Start New", 0, this, OptionsFormDialogBox::ID_STARTNEW);
    new FXButton(ButtonMatrix, "Change", 0, this, OptionsFormDialogBox::ID_CHANGE);
}

long OptionsFormDialogBox::onChange(FXObject *, FXSelector, void *)
{
    SimOpts = TmpOpts;
    this->hide();
    return 1;
}

long OptionsFormDialogBox::onStartNew(FXObject *, FXSelector, void *)
{
    EngineThread.cancel();
    SimOpts = TmpOpts;
    EngineThread.start();
    this->hide();
    return 1;
}

long OptionsFormDialogBox::onSaveSettings(FXObject *, FXSelector, void *)
{
    WriteSett(Engine.MainDir() + "\\settings\\savesett.set", TmpOpts);
    return 1;
}

long OptionsFormDialogBox::onLoadSettings(FXObject *, FXSelector, void *)
{
    ReadSett(Engine.MainDir() + "\\settings\\savesett.set", TmpOpts);
    SpeciesList->clearItems(true);
    for(int x = 0; x < (int)TmpOpts.SpeciesNum; x++)
        SpeciesList->appendItem(TmpOpts.Specie[x].Name.c_str());

    SpeciesList->setCurrentItem(0);
    onSelectNewSpecies(NULL, 0, NULL);
    return 1;
}