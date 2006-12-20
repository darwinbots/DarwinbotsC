#ifndef PARSERWINDOW_H
#define PARSERWINDOW_H

#include <fx.h>
#include <fx3d.h>
#include "../Engine/DnaParser.h"
#include "../Engine/DNAClass.h"

#define PROJECT_NAME "DarwinBots Parser"
#define PROJECT_VERSION "0.1"

class ParserWindow : public FXMainWindow
{
    FXDECLARE(ParserWindow);
    FXMenuPane *fileMenu;
    FXText* editor;
    DnaParser parser;
    Dna dna;
    public:
        ParserWindow(FXApp *app);
        ~ParserWindow();
        enum {
        ID_Quit = FXMainWindow::ID_LAST,
        ID_Load,
        ID_Text,
        ID_LAST
        };
        long onCmdQuit  (FXObject *, FXSelector, void *);
        long onCmdLoad  (FXObject *, FXSelector, void *);

    protected:
        ParserWindow(){};
    private:

};

FXDEFMAP(ParserWindow) ParserWindowMap[] = {
  //FXMAPFUNC(SEL_SIGNAL,    ParserWindow::ID_Quit,             ParserWindow::onCmdQuit),
    FXMAPFUNC(SEL_COMMAND,   ParserWindow::ID_Quit,             ParserWindow::onCmdQuit),
    FXMAPFUNC(SEL_COMMAND,   ParserWindow::ID_Load,             ParserWindow::onCmdLoad)
};



#endif // PARSERWINDOW_H
