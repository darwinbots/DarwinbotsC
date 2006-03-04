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

    private:
    FXList *SpeciesList;
    void BottomToolbar(FXMatrix *LayoutMatrix);
    void Species                (FXTabBook *TabBook);
    void Veggy                  (FXTabBook *TabBook);
    void General                (FXTabBook *TabBook);
    void PhysicsAndCosts        (FXTabBook *TabBook);
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

    long onSelectNewSpecies     (FXObject *, FXSelector, void *);

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

        ID_SELECTSPECIES,
        ID_ADDSPECIES,
        ID_CLONESPECIES,
        ID_INHERITSPECIES,
        ID_DELETESPECIES,
        ID_DELETEALLSPECIES,

        ID_LAST
    };
};

FXDEFMAP(OptionsFormDialogBox) OptionsFormDialogBoxMap[] = {
    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_STARTNEW,   OptionsFormDialogBox::onStartNew),
    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_CHANGE,     OptionsFormDialogBox::onChange),
    FXMAPFUNC(SEL_COMMAND, OptionsFormDialogBox::ID_SELECTSPECIES,     OptionsFormDialogBox::onSelectNewSpecies)
};