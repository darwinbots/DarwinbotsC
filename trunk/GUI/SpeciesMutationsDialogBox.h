#include <fx.h>
#include "OptionsForm.h"
#include "..\Engine\Mutations.h"



class SpeciesMutationsDialogBox : public FXDialogBox
{
    FXDECLARE(SpeciesMutationsDialogBox)

    public:
    
    //SpeciesMutationsDialogBox::SpeciesMutationsDialogBox(Mutationprobs *MutateMe);

    void hide()
    {
        FXDialogBox::hide();
    }

    void show(FXuint placement)
    {
        /*SpeciesList->clearItems();
        for (int x = 0; x < 50; x++)
        {
            if(!strcmp(TmpOpts.Specie[x].Name.c_str(), ""))
                break;
            SpeciesList->appendItem(TmpOpts.Specie[x].Name.c_str());
            ReConnectToSpecies(0);
        }*/

        FXDialogBox::show(placement);
    }

    long onChangeMode(FXObject *, FXSelector, void *){};

    enum
    {
        ID_CHANGEMODE = FXDialogBox::ID_LAST,

        ID_LAST
    };
};

FXDEFMAP(SpeciesMutationsDialogBox) SpeciesMutationsDialogBoxMap[] = {
    FXMAPFUNC(SEL_COMMAND, SpeciesMutationsDialogBox::ID_CHANGEMODE,     SpeciesMutationsDialogBox::onChangeMode)
};

