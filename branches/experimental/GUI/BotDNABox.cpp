#include "BotDNABox.h"

FXDEFMAP(BotDNAWindow_Class) BotDNAWindow_ClassMap[] = {
  FXMAPFUNC(SEL_COMMAND, BotDNAWindow_Class::ID_STEP, BotDNAWindow_Class::onCmdStep),
  FXMAPFUNC(SEL_COMMAND, BotDNAWindow_Class::ID_CONTINUE, BotDNAWindow_Class::onCmdContinue),
  FXMAPFUNC(SEL_COMMAND, BotDNAWindow_Class::ID_BREAKPOINT, BotDNAWindow_Class::onCmdBreakpoint),
  FXMAPFUNC(SEL_COMMAND, BotDNAWindow_Class::ID_TOCURSOR, BotDNAWindow_Class::onCmdToCursor)
};

FXIMPLEMENT(BotDNAWindow_Class,FXDialogBox,BotDNAWindow_ClassMap,ARRAYNUMBER(BotDNAWindow_ClassMap))

BotDNAWindow_Class::BotDNAWindow_Class(Robot* bot, FXComposite *parent) :
    FXDialogBox(parent, "Bot DNA", DECOR_TITLE | DECOR_BORDER)
{
    if (bot != NULL)
    {
        this->detach();
        this->destroy();
        return;
    }

    FXMatrix *LayoutMatrix = new FXMatrix(this, 1, MATRIX_BY_ROWS | LAYOUT_SIDE_TOP | LAYOUT_FILL);

    //Setup Toolbar
    {
        FXDockSite *topdock = new FXDockSite(this);

        FXToolBarShell *dragshell = new FXToolBarShell(this, FRAME_RAISED);
        FXToolBar *toolbar = new FXToolBar(topdock, dragshell, FRAME_RAISED);

        new FXButton(toolbar, "Compile DNA");

        //new FXSeparator(toolbar);

        new FXButton(toolbar, "Toggle Breakpoint", 0, this,
        	         ID_BREAKPOINT, LAYOUT_FIX_WIDTH | BUTTON_TOOLBAR | FRAME_RAISED | FRAME_THICK,
                     0,0,100,0,10,10,0,0);

        new FXButton(toolbar, "Run to Breakpoint", 0, this,
        	         ID_CONTINUE, LAYOUT_FIX_WIDTH | BUTTON_TOOLBAR | FRAME_RAISED | FRAME_THICK,
                     0,0,100,0,10,10,0,0);

        new FXButton(toolbar, "Step", 0, this,
        	         ID_STEP, LAYOUT_FIX_WIDTH | BUTTON_TOOLBAR | FRAME_RAISED | FRAME_THICK,
                     0,0,100,0,10,10,0,0);

        new FXButton(toolbar, "Run to Cursor", 0, this,
        	         ID_TOCURSOR, LAYOUT_FIX_WIDTH | BUTTON_TOOLBAR | FRAME_RAISED | FRAME_THICK,
                     0,0,100,0,10,10,0,0);
    }

    //Setup DNA
    {

        FXGroupBox *DNAFrame=new FXGroupBox(LayoutMatrix,
            "Bot DNA",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y | LAYOUT_FILL_COLUMN);

        FXText *DNATextBox = new FXText(DNAFrame, DNAFrame, 0,
            TEXTFIELD_REAL|JUSTIFY_LEFT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|
            LAYOUT_FIX_WIDTH | LAYOUT_FIX_HEIGHT, 0,0,
            200,//width
            250);

        DNATextBox->setText(bot->getDnaText(NULL).c_str(),
                            strlen(bot->getDnaText(NULL).c_str()));

        DNATextBox->setDelimiters(" \n\t");

        //DNATextBox->disable();
    }

    this->create();
    this->show();
}
