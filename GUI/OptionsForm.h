#ifndef OPTIONSFORM_H
#define OPTIONSFORM_H

#include <fx.h>
#include "../Engine/SimOptions.h"

#define LAYOUT_FILL_XY LAYOUT_FILL_X|LAYOUT_FILL_Y
#define LAYOUT_FILL_RC LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW
#define LAYOUT_FILL_ALL LAYOUT_FILL_XY | LAYOUT_FILL_RC
#define LAYOUT_FILL_YC LAYOUT_FILL_COLUMN | LAYOUT_FILL_Y
#define LAYOUT_FILL_XR LAYOUT_FILL_ROW | LAYOUT_FILL_X

class OptionsFormDialogBox : public FXDialogBox
{
    FXDECLARE(OptionsFormDialogBox)

    public:
    FXList *SpeciesList;

    private:    
    void BottomToolbar(FXMatrix *LayoutMatrix);
    void Species                (FXTabBook *TabBook);
    void Veggy                  (FXTabBook *TabBook);
    void General                (FXTabBook *TabBook);
    void PhysicsAndCosts        (FXTabBook *TabBook);
    void CostsOptions           (FXTabBook *TabBook);
    void Mutations              (FXTabBook *TabBook);
    void ReststartAndL          (FXTabBook *TabBook);
    void InternetOptions        (FXTabBook *TabBook);
    void Recording              (FXTabBook *TabBook);

    long ReConnectToSpecies(unsigned int SpeciesNumber);    

    public:
    OptionsFormDialogBox(FXComposite *parent = NULL);

    //Commands
    
    long onStartNew             (FXObject *, FXSelector, void *);
    long onChange               (FXObject *, FXSelector, void *);
    long onSaveSettings         (FXObject *, FXSelector, void *);
    long onLoadSettings         (FXObject *, FXSelector, void *);

    long onSelectNewSpecies     (FXObject *, FXSelector, void *);
    long onAddNewSpecies        (FXObject *, FXSelector, void *);
    long onDeleteSpecies        (FXObject *, FXSelector, void *);
    long onClearListSpecies     (FXObject *, FXSelector, void *);
    long onCloneSpecies        (FXObject *, FXSelector, void *);
    long onInheritSpecies        (FXObject *, FXSelector, void *);
    
    long onNrgButton20K         (FXObject *, FXSelector, void *);
    long onNrgButton30K         (FXObject *, FXSelector, void *);

    long onBodyButton15K        (FXObject *, FXSelector, void *);
    long onBodyButton30K        (FXObject *, FXSelector, void *);

    long onWorldDimensionSlider (FXObject *, FXSelector, void *);

    long onMutationsSpecies     (FXObject *, FXSelector, void *);

    long onClearCosts           (FXObject *, FXSelector, void *);
    long onCostsF1Default       (FXObject *, FXSelector, void *);
    long onCostsDecentGuess     (FXObject *, FXSelector, void *);


    void hide()
    {
        FXDialogBox::hide();
    }

    void show(FXuint placement)
    {
        SpeciesList->clearItems();
        for (int x = 0; x < 50; x++)
        {
            if(!strcmp(TmpOpts.Specie[x].Name.c_str(), ""))
                break;
            SpeciesList->appendItem(TmpOpts.Specie[x].Name.c_str());
            ReConnectToSpecies(0);
        }

        FXDialogBox::show(placement);
    }

    enum
    {
        ID_STARTNEW = FXDialogBox::ID_LAST,
        ID_CHANGE,
        ID_SAVESETTINGS,
        ID_LOADSETTINGS,

        ID_SELECTSPECIES,
        ID_ADDSPECIES,
        ID_CLONESPECIES,
        ID_INHERITSPECIES,
        ID_DELETESPECIES,
        ID_DELETEALLSPECIES,

        ID_NRG_20K,
        ID_NRG_30K,

        ID_BODY_15K,
        ID_BODY_30K,

        ID_WORLDDIMENSIONSLIDER,
        ID_MUTATIONSPECIES,

        ID_CLEARCOSTS,
        ID_COSTSF1DEFAULT,
        ID_COSTSGUESS,

        ID_LAST
    };
};

FXDEFMAP(OptionsFormDialogBox) OptionsFormDialogBoxMap[] = {
    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_STARTNEW,   OptionsFormDialogBox::onStartNew),
    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_CHANGE,     OptionsFormDialogBox::onChange),
    
    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_SAVESETTINGS,   OptionsFormDialogBox::onSaveSettings),
    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_LOADSETTINGS,   OptionsFormDialogBox::onLoadSettings),
    
    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_SELECTSPECIES,     OptionsFormDialogBox::onSelectNewSpecies),
    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_DELETESPECIES,     OptionsFormDialogBox::onDeleteSpecies),
    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_DELETEALLSPECIES,     OptionsFormDialogBox::onClearListSpecies),
    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_CLONESPECIES,     OptionsFormDialogBox::onCloneSpecies),    
    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_INHERITSPECIES,     OptionsFormDialogBox::onInheritSpecies),    
    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_ADDSPECIES,     OptionsFormDialogBox::onAddNewSpecies),    
    
    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_NRG_20K,     OptionsFormDialogBox::onNrgButton20K),
    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_NRG_30K,     OptionsFormDialogBox::onNrgButton30K),

    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_BODY_15K,     OptionsFormDialogBox::onBodyButton15K),
    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_BODY_30K,     OptionsFormDialogBox::onBodyButton30K),

    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_WORLDDIMENSIONSLIDER,     OptionsFormDialogBox::onWorldDimensionSlider),

    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_MUTATIONSPECIES,     OptionsFormDialogBox::onMutationsSpecies),
    
    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_CLEARCOSTS,     OptionsFormDialogBox::onClearCosts),
    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_COSTSF1DEFAULT,     OptionsFormDialogBox::onCostsF1Default),
    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_COSTSGUESS,     OptionsFormDialogBox::onCostsDecentGuess)
};

#endif