#ifndef BOTDNABOX_H
#define BOTDNABOX_H

#include <fx.h>
#include "../Engine/Robot.h"

class BotDNAWindow_Class : public FXDialogBox
{
    FXDECLARE(BotDNAWindow_Class)

    private:
    Robot *point;
    
    public:
    const Robot *ThatBot() const
    {
        return point;
    }
    
    long onCmdStep(FXObject*,FXSelector,void*) {return 0;}
    long onCmdContinue(FXObject*,FXSelector,void*) {return 0;}
    long onCmdBreakpoint(FXObject*,FXSelector,void*) {return 0;}
    long onCmdToCursor(FXObject*,FXSelector,void*) {return 0;}
    
    BotDNAWindow_Class(Robot *bot = NULL, FXComposite *parent = NULL);
    
    enum
    {
        ID_ME = FXDialogBox::ID_LAST,
        ID_BREAKPOINT,
        ID_CONTINUE,
        ID_STEP,
        ID_TOCURSOR
    };
};

#endif

