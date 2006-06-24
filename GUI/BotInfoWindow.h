#ifndef BOTINFOWINDOW_H
#define BOTINFOWINDOW_H

#include <fx.h>
class Robot;

class BotInfoWindow_Class : public FXDialogBox
{
    FXDECLARE(BotInfoWindow_Class)
    
    private:
    Robot *bot;
    
    public:
    BotInfoWindow_Class(Robot *bot = NULL, FXComposite *parent = NULL);    
    
    long onCmdStep(FXObject*,FXSelector,void*) {return 0;}
    
    enum
    {
        ID_ME = FXDialogBox::ID_LAST,
        ID_LAST
    };
};

#endif