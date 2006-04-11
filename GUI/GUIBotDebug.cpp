/*#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif*/

//STILL UNDER DEVELOPMENT

#include <iostream>
#include <vector>
#include "GUIMain.h"
#include "../Engine/Robot.h"
#include <FXToolBarShell.h>

#include "GUIBotDebug.h"
#include "BotDNABox.h"

bool GUIWINDOW = false;

using namespace std;

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
    FXDialogBox(parent, "Bot Debug Controls", DECOR_TITLE | DECOR_BORDER, 0, 0, 600, 800)
{
    if (bot == NULL)
    {
        this->detach();
        this->destroy();
        return;
    }
    
    point = bot;
    
    //LinkBotTarget();
    
    SetupToolbar();
    SetupLayout();
    //SetupSideBar();
    SetupIntStackFrame();
    //SetupDNAFrame();
    //SetupSysvarsFrame();
    //SetupDetailsFrame();

    this->create();
    this->show();

    DEBUGMODE = true;
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

    FXMatrix *StackMatrix=new FXMatrix(IntStackFrame,2,MATRIX_BY_COLUMNS|LAYOUT_SIDE_LEFT|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    int x = 5;

    char buffer[256];

    for(x = 1; x <= 20; x++)
    {
        new FXLabel(StackMatrix,strcat(itoa(x, buffer, 10), "th"),NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
        IntStackTextField[x-1] = new FXTextField(StackMatrix,10,&BotTargetInfo.datatargets.stack[x-1],
            FXDataTarget::ID_VALUE,
            TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);

        /*new FXLabel(StackMatrix,strcat(itoa(x-10, buffer, 10), "th"),NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
        IntStackTextField[x-11] = new FXTextField(StackMatrix,10,&BotTargetInfo.datatargets.stack[x-11],
            FXDataTarget::ID_VALUE,
            TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);*/
    }    
}

void BotDebug_Window::SetupDNAFrame()
{
    DNAFrame=new FXGroupBox(LayoutMatrix,
        "Bot DNA",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y | LAYOUT_FILL_COLUMN);

    DNATextBox = new FXText(DNAFrame, DNAFrame, 0, 
        TEXTFIELD_REAL|JUSTIFY_LEFT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|
        LAYOUT_FIX_WIDTH | LAYOUT_FIX_HEIGHT, 0,0,
        200,//width
        250);
    
    DNATextBox->setText(point->DNA_Text().c_str(),
                        strlen(point->DNA_Text().c_str()));
    
    DNATextBox->setDelimiters(" \n");

    DNATextBox->disable();
}

void BotDebug_Window::SetupSysvarsFrame()
{
    //INTERESTING SYSVARS LIST:

    SysvarsFrame = new FXGroupBox(LayoutMatrix,
        "Bot Memory",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y | LAYOUT_FILL_COLUMN);

    SysvarsMatrix = new FXMatrix(SysvarsFrame,4,MATRIX_BY_COLUMNS|LAYOUT_SIDE_LEFT|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    for(int x = 0; x < 20; x++)
    {
        SysvarsLabel[x] = new FXLabel(SysvarsMatrix,"",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
        //SysvarsLabel[x]->hide();
        SysvarsTextField[x] = new FXTextField(SysvarsMatrix,10,NULL,
            0,
            TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
        //SysvarsTextField[x]->hide();
    }
}

void BotDebug_Window::AddInterestingSysvars(int number)
{
    char buffer[256];

    for(int x = 0; x < BotTargetInfo.lastmem; x++)
    {
        if (BotTargetInfo.memory[x] == number)
            return;
    }
    SysvarsTextField[BotTargetInfo.lastmem]->show();
    SysvarsLabel[BotTargetInfo.lastmem]->setText(itoa(number, buffer, 10));
    SysvarsLabel[BotTargetInfo.lastmem]->show();
    BotTargetInfo.memory[BotTargetInfo.lastmem] = number;
    
    BotTargetInfo.lastmem++;
    //SysvarsTextField[BotTargetInfo.memory.size() - 1]->setText(itoa(BotTargetInfo[number], buffer, 10));
    
    /*new FXLabel(StackMatrix,"Yellow",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(StackMatrix,10,NULL,
            0,
            TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);*/
}

void BotDebug_Window::SetupDetailsFrame()
{
    DetailsFrame=new FXGroupBox(LayoutMatrix,
        "Bot Details",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y | LAYOUT_FILL_COLUMN);

    FXMatrix *DetailsMatrix=new FXMatrix(DetailsFrame,4,MATRIX_BY_COLUMNS|LAYOUT_SIDE_LEFT|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    new FXLabel(DetailsMatrix,"Age",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    
    new FXTextField(DetailsMatrix,10,&BotTargetInfo.datatargets.age,FXDataTarget::ID_VALUE,
        TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);   

    new FXLabel(DetailsMatrix,"nrg",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(DetailsMatrix,10,&BotTargetInfo.datatargets.nrg,FXDataTarget::ID_VALUE,
        TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);   

    new FXLabel(DetailsMatrix,"Generation",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(DetailsMatrix,10,&BotTargetInfo.datatargets.generation,FXDataTarget::ID_VALUE,
        TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);   

    new FXLabel(DetailsMatrix,"Body",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(DetailsMatrix,10,&BotTargetInfo.datatargets.body,FXDataTarget::ID_VALUE,
        TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);   

    new FXLabel(DetailsMatrix,"New Mutations",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(DetailsMatrix,10,&BotTargetInfo.datatargets.newmutations,FXDataTarget::ID_VALUE,
        TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);

    new FXLabel(DetailsMatrix,"Shell",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(DetailsMatrix,10,&BotTargetInfo.datatargets.shell,FXDataTarget::ID_VALUE,
        TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);   

    new FXLabel(DetailsMatrix,"Total Mutations",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(DetailsMatrix,10,&BotTargetInfo.datatargets.mutations,FXDataTarget::ID_VALUE,
        TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);   

    new FXLabel(DetailsMatrix,"Slime",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(DetailsMatrix,10,&BotTargetInfo.datatargets.slime,FXDataTarget::ID_VALUE,
        TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);   

    new FXLabel(DetailsMatrix,"DNA Length",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(DetailsMatrix,10,&BotTargetInfo.datatargets.dnalength,FXDataTarget::ID_VALUE,
        TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);   

    new FXLabel(DetailsMatrix,"Poison",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(DetailsMatrix,10,&BotTargetInfo.datatargets.poison,FXDataTarget::ID_VALUE,
        TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);   

    new FXLabel(DetailsMatrix,"# of Genes",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(DetailsMatrix,10,&BotTargetInfo.datatargets.numgenes,FXDataTarget::ID_VALUE,
        TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);   

    new FXLabel(DetailsMatrix,"Venom",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(DetailsMatrix,10,&BotTargetInfo.datatargets.venom,FXDataTarget::ID_VALUE,
        TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);   

    new FXLabel(DetailsMatrix,"Waste",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(DetailsMatrix,10,&BotTargetInfo.datatargets.waste,FXDataTarget::ID_VALUE,
        TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);   

    new FXLabel(DetailsMatrix,"PWaste",NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
    new FXTextField(DetailsMatrix,10,&BotTargetInfo.datatargets.pwaste,FXDataTarget::ID_VALUE,
        TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
}

void BotDebug_Window::LinkBotTarget()
{
    BotTargetInfo.Linkup();
    
    
    //for (int y = 0; y < BotTargetInfo.stack.
    //
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

void BotDebug_Window::hide()
{
    DEBUGMODE = false;
    FXDialogBox::hide();   
}

void BotDebug_Window::show(FXuint placement)
{
    DEBUGMODE = true;
    FXDialogBox::show(placement);
}

void BotDebug_Window::Update()
{
    for(int x = 0; x < 20; x++)
        IntStackTextField[x]->setBackColor(0xFFFFFF);
    
    //color in the stack boxes that are currently on top
    if (BotTargetInfo.IntStack_pos > 0)    
        IntStackTextField[BotTargetInfo.IntStack_pos-1]->setBackColor(0xFFAAAA);
}

long MainWindow::onBotDebug()
{
    //set to bot 0

    /*if (MainWindowHandle->BotDebug == NULL)
        BotDebug = new BotDebug_Window(rob[0], mainview);        
    else
        BotDebug->show();*/

    new BotDNAWindow_Class(rob[0], this);

    return 1;
}


/////////////////////////////////////////////////////
bool iswhitespace(char c)
{
    if (isspace(c) ||
        c == '\r' ||
        c == '\f' ||
        c == '\t' ||
        c == '\n')
    return true;
    
    return false;
}


int NextWord(string &text, unsigned int pos = 0)
{
    while(text.size() != pos && !iswhitespace(text.at(pos)))
        pos++;
    
    while(text.size() != pos && iswhitespace(text.at(pos)))
        pos++;

    return pos;
}

void tempBot_typ::Update(Robot *bot)
{
    age = bot->age;
    nrg = bot->nrg;
    body = bot->Body;
    newmutations = bot->DNA->LastMut;
    mutations    = bot->DNA->Mutations;
    shell = bot->Shell;
    slime = bot->Slime;
    poison = bot->Poison;
    venom = bot->Venom;
    waste = bot->Waste;
    pwaste = bot->Pwaste;

    dnalength = bot->DNA->length();
    //numgenes

    for (int x = 0; x < 20; x++)
        stack[x] = IntStack.val[x];

    //char buffer[256];
    
    //for (int y = 0; y < lastmem; y++)
    //    MainWindowHandle->BotDebug->SysvarsTextField[y]->setText(itoa( (*bot)[memory[y]], buffer, 10));

    //string text = MainWindowHandle->BotDebug->DNATextBox->getText().text();
    
    int text_position = 0;
    
    //if(iswhitespace(text.at(0)))
    //    text_position = NextWord(text);
    
    //for(unsigned int z = 0; z < this->DNA_pos; z++)
    //    text_position = NextWord(text, text_position);
    
    //while(MainWindowHandle->BotDebug->DNATextBox->
    
    //unsigned int length = NextWord(text, text_position) - text_position;

    //while(iswhitespace(text.at(length + text_position - 1)))
    //    length--;
    
    //MainWindowHandle->BotDebug->DNATextBox->killSelection();
    //MainWindowHandle->BotDebug->DNATextBox->setSelection(text_position, length);

    this->IntStack_pos = IntStack.pos;
}

void tempBot_typ::Initialize(Robot *bot)
{
    this->DNA.assign(bot->DNA_Text().c_str());
    this->generation = bot->generation;
    this->name.assign(bot->fname.c_str());
}

void tempBot_typ::Linkup()
{
    datatargets.age.connect(age);
    datatargets.body.connect(body);
    datatargets.DNA.connect(DNA);
    datatargets.dnalength.connect(dnalength);
    datatargets.generation.connect(generation);
    datatargets.mutations.connect(mutations);
    datatargets.name.connect(name);
    datatargets.newmutations.connect(newmutations);
    datatargets.nrg.connect(nrg);
    datatargets.numgenes.connect(numgenes);
    datatargets.poison.connect(poison);
    datatargets.pwaste.connect(pwaste);
    datatargets.shell.connect(shell);
    datatargets.slime.connect(slime);
    datatargets.venom.connect(venom);
    datatargets.waste.connect(waste);

    lastmem = 0;
    
    
    age = 50;

    for (int x = 0; x < 20; x++)
    {
        datatargets.stack[x].connect(stack[x]);
        stack[x] = 0;
    }

    for(int y = 0; y < 20; y ++)
    {
        memory[y] = 0;
    }
}
