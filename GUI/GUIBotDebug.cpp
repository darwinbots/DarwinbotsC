#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

//STILL UNDER DEVELOPMENT

#include <iostream>
#include <vector>
#include "GUIMain.h"
#include "../Engine/Robot.h"
#include "../Engine/DNA_Execution.h"
#include <FXToolBarShell.h>

#include "GUIBotDebug.h"

bool GUIWINDOW = false;

using namespace std;

char *BotDetails[] = {
"Age",
"nrg",
"Generation",
"Body",
"New Mutations",
"Shell",
"Total Mutations",
"Slime",
"DNA Length",
"Poison",
"# of Genes",
"Venom",
"Waste",
"PWaste",
""};

tempBot_typ tempBot;


FXDEFMAP(BotDebug_Window) BotDebug_WindowMap[] = {
  FXMAPFUNC(SEL_COMMAND, BotDebug_Window::ID_STEP, BotDebug_Window::onCmdStep),

  FXMAPFUNC(SEL_COMMAND, BotDebug_Window::ID_SHOWINTSTACK, BotDebug_Window::onCmdShowIntStack),
  FXMAPFUNC(SEL_COMMAND, BotDebug_Window::ID_SHOWDNA,      BotDebug_Window::onCmdShowDNA), 
  FXMAPFUNC(SEL_COMMAND, BotDebug_Window::ID_SHOWSYSVARS,  BotDebug_Window::onCmdShowSysvars),
  FXMAPFUNC(SEL_COMMAND, BotDebug_Window::ID_SHOWDETAILS,  BotDebug_Window::onCmdShowDetails)
};

// Object implementation
FXIMPLEMENT(BotDebug_Window,FXDialogBox,BotDebug_WindowMap,ARRAYNUMBER(BotDebug_WindowMap))

BotDebug_Window::BotDebug_Window(Robot *bot, FXComposite *parent) : 
    FXDialogBox(parent, "Bot Debug Controls", DECOR_TITLE | DECOR_BORDER | LAYOUT_FILL)
{
    if (bot == NULL)
    {
        this->detach();
        this->destroy();
        return;
    }

    point = bot;

    SetupToolbar();
    SetupLayout();
    SetupSideBar();
    SetupIntStackFrame();
    SetupDNAFrame();
    SetupSysvarsFrame();
    SetupDetailsFrame();

    this->create();
    this->show();

    GUIWINDOW = true;
}

void BotDebug_Window::SetupToolbar()
{
    // Site where to dock
    FXDockSite *topdock = new FXDockSite(this);

    FXToolBarShell *dragshell = new FXToolBarShell(this, FRAME_RAISED);
    FXToolBar *toolbar = new FXToolBar(topdock, dragshell, FRAME_RAISED);
    
    FXButton *button1 = new FXButton(toolbar, "Toggle Breakpoints", 0, this,
        	     ID_BREAKPOINT, LAYOUT_FIX_WIDTH | BUTTON_TOOLBAR | FRAME_RAISED | FRAME_THICK,
                        0,0,100,0,10,10,0,0);
    
    FXButton *button2 = new FXButton(toolbar, "Run to Breakpoint", 0, this,
        	     ID_CONTINUE, LAYOUT_FIX_WIDTH | BUTTON_TOOLBAR | FRAME_RAISED | FRAME_THICK,
                        0,0,100,0,10,10,0,0);
    
    FXButton *button3 = new FXButton(toolbar, "Step", 0, this,
        	     ID_STEP, LAYOUT_FIX_WIDTH | BUTTON_TOOLBAR | FRAME_RAISED | FRAME_THICK,
                        0,0,100,0,10,10,0,0);
    
    FXButton *button4 = new FXButton(toolbar, "Run to Cursor", 0, this,
        	     ID_TOCURSOR, LAYOUT_FIX_WIDTH | BUTTON_TOOLBAR | FRAME_RAISED | FRAME_THICK,
                        0,0,100,0,10,10,0,0);
}

void BotDebug_Window::SetupLayout()
{
    LayoutMatrix = new FXMatrix(this, 1, MATRIX_BY_ROWS | LAYOUT_SIDE_TOP | LAYOUT_FILL);
    SideCheck = new FXMatrix(LayoutMatrix, 1, MATRIX_BY_COLUMNS | LAYOUT_FILL | LAYOUT_FILL_COLUMN);
}

void BotDebug_Window::SetupSideBar()
{
    new FXCheckButton(SideCheck, "Integer Stack", this,
        ID_SHOWINTSTACK, BUTTON_NORMAL | LAYOUT_CENTER_X | LAYOUT_FIX_WIDTH, 0, 0, 100);

    new FXCheckButton(SideCheck, "DNA", this,
        ID_SHOWDNA, BUTTON_NORMAL | LAYOUT_CENTER_X | LAYOUT_FIX_WIDTH, 0, 0, 100);

    new FXCheckButton(SideCheck, "Sysvars", this,
        ID_SHOWSYSVARS, BUTTON_NORMAL | LAYOUT_CENTER_X | LAYOUT_FIX_WIDTH, 0, 0, 100);

    new FXCheckButton(SideCheck, "Bot Details", this,
        ID_SHOWDETAILS, BUTTON_NORMAL | LAYOUT_CENTER_X | LAYOUT_FIX_WIDTH, 0, 0, 100);
}

void BotDebug_Window::SetupIntStackFrame()
{
    //the frame
    IntStackFrame = new FXGroupBox(LayoutMatrix,
        "Bot Stack",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y | LAYOUT_FILL_COLUMN);

    FXMatrix *StackMatrix=new FXMatrix(IntStackFrame,4,MATRIX_BY_COLUMNS|LAYOUT_SIDE_LEFT|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    int x = 5;

    char buffer[256];

    for(x = 20; x > 10; x--)
    {
        tempBot.target.stack[x-1].connect(tempBot.stack[x-1]);
        tempBot.target.stack[x-11].connect(tempBot.stack[x-11]);

        new FXLabel(StackMatrix,strcat(itoa(x, buffer, 10), "th"),NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
        new FXTextField(StackMatrix,10,&tempBot.target.stack[x-1],FXDataTarget::ID_VALUE,
            TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);

        new FXLabel(StackMatrix,strcat(itoa(x-10, buffer, 10), "th"),NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
        new FXTextField(StackMatrix,10,&tempBot.target.stack[x-11],FXDataTarget::ID_VALUE,
            TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
    }
}

void BotDebug_Window::SetupDNAFrame()
{
    DNAFrame=new FXGroupBox(LayoutMatrix,
        "Bot DNA",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y | LAYOUT_FILL_COLUMN);

    FXText *DNATextBox = new FXText(DNAFrame, DNAFrame, 0, 
        TEXTFIELD_REAL|JUSTIFY_LEFT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|
        LAYOUT_FIX_WIDTH | LAYOUT_FIX_HEIGHT, 0,0,
        200,//width
        250);
    
    DNATextBox->setText(point->DNA_Text().c_str(),
                        strlen(point->DNA_Text().c_str()));

    DNATextBox->disable();
}

void BotDebug_Window::SetupSysvarsFrame()
{
    //INTERESTING SYSVARS LIST:
    SysvarsFrame = new FXGroupBox(LayoutMatrix,
        "Bot Memory",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y | LAYOUT_FILL_COLUMN);
}

void BotDebug_Window::SetupDetailsFrame()
{
    DetailsFrame=new FXGroupBox(LayoutMatrix,
        "Bot Details",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y | LAYOUT_FILL_COLUMN);

    FXMatrix *DetailsMatrix=new FXMatrix(DetailsFrame,4,MATRIX_BY_COLUMNS|LAYOUT_SIDE_LEFT|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    int x = 0;
    while( strcmp(BotDetails[x++], "") != 0)
    {
        new FXLabel(DetailsMatrix,BotDetails[x-1],NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
        new FXTextField(DetailsMatrix,10,NULL,0,
            TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);   
    }
}

long BotDebug_Window::onCmdShowIntStack(FXObject*,FXSelector,void *ptr)
{
    if (ptr)
        IntStackFrame->show();
    else
        IntStackFrame->hide();
    
    return 1;
}
long BotDebug_Window::onCmdShowDNA(FXObject*,FXSelector,void *ptr)
{
    if (ptr)
        DNAFrame->show();
    else
        DNAFrame->hide();

    return 1;
}
long BotDebug_Window::onCmdShowSysvars(FXObject*,FXSelector,void *ptr)
{
    if (ptr)
        SysvarsFrame->show();
    else
        SysvarsFrame->hide();

    return 1;
}
long BotDebug_Window::onCmdShowDetails(FXObject*,FXSelector,void *ptr)
{
    if (ptr)
        DetailsFrame->show();
    else
        DetailsFrame->hide();    

    return 1;
}

long MainWindow::onBotDebug()
{
    //set to bot 0

    if (!GUIWINDOW)
        BotDebug = new BotDebug_Window(rob[8], mainview);        
    else
        BotDebug->show();

    return 1;
}