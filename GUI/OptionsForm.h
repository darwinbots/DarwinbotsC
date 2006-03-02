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
    void BottomToolbar(FXMatrix *LayoutMatrix);
    void Species                (FXTabBook *TabBook);
    void Veggy                  (FXTabBook *TabBook);
    void General                (FXTabBook *TabBook);
    void PhysicsAndCosts        (FXTabBook *TabBook);
    void Mutations              (FXTabBook *TabBook);
    void ReststartAndL          (FXTabBook *TabBook);
    void InternetOptions        (FXTabBook *TabBook);
    void Recording              (FXTabBook *TabBook);

    public:
    OptionsFormDialogBox(FXComposite *parent = NULL);

    //Commands
    long onStartNew             (FXObject *, FXSelector, void *) {return 1;}
    long onChange               (FXObject *, FXSelector, void *);

    void hide()
    {
        FXDialogBox::hide();
    }

    void show(FXuint placement)
    {
        FXDialogBox::show(placement);
    }

    enum
    {
        ID_STARTNEW = FXDialogBox::ID_LAST,
        ID_CHANGE,

        ID_LAST
    };
};