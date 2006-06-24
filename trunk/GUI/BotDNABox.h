#ifndef BOTDNABOX_H
#define BOTDNABOX_H

#include <fx.h>
class Robot;

class BotDNAWindow_Class : public FXDialogBox
{
    FXDECLARE(BotDNAWindow_Class)

    private:
    Robot *point;
    FXText *DNATextBox;
    
    public:
    const Robot *ThatBot() const
    {
        return point;
    }
    
    long onCmdStep(FXObject*,FXSelector,void*);
    long onCmdContinue(FXObject*,FXSelector,void*);
    long onCmdBreakpoint(FXObject*,FXSelector,void*);
    long onCmdToCursor(FXObject*,FXSelector,void*);
    long onUpdGUI(FXObject*,FXSelector,void*);
    
    int CursorToDNAPosition(int pos); //convert between cursor position and DNA position
    int DNAPositionToCursor(int pos); //returns the text position of the current DNA position
    
    //update graphics
    void HighlightBreakpoints();
    void HighlightCurrStep();
    
    BotDNAWindow_Class(Robot *bot = NULL, FXComposite *parent = NULL);
    
    enum
    {
        ID_ME = FXDialogBox::ID_LAST,
        ID_BREAKPOINT,
        ID_CONTINUE,
        ID_STEP,
        ID_TOCURSOR,
        ID_UPDGUI,
        ID_LAST
    };
};

#endif

