#include <fx.h>
#include "../Engine/Robot.h"

class BotConsole_Class : public FXDialogBox
{
    FXDECLARE(BotConsole_Class)
    Robot *bot;

    public:
    BotConsole_Class(FXComposite *parent, Robot *bot);

}