#ifndef BOTINFOWINDOW_H
#define BOTINFOWINDOW_H

#include <fx.h>
class Robot;

class BotInfoWindow : public FXDialogBox
{
    FXDECLARE(BotInfoWindow)

    private:
    Robot *_bot;

    public:
    BotInfoWindow(Robot *bot = NULL, FXComposite *parent = NULL);

    long onCmdStep(FXObject*,FXSelector,void*) {return 0;}

    enum
    {
        ID_ME = FXDialogBox::ID_LAST,
        ID_LAST
    };
};

FXDEFMAP(BotInfoWindow) BotInfoWindowMap[] = {
  FXMAPFUNC(SEL_COMMAND, BotInfoWindow::ID_LAST, BotInfoWindow::onCmdStep)
};
#endif

