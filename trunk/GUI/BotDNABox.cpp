/******************************************************
Controls to stepwise debug a bot

Red = breakpoints
Blue = current position
*******************************************************/

#include "BotDNABox.h"
#include "../ENgine/Robot.h"
#include "../Engine/DNADebugFlowControls.h"

int CursorDNAPos = 0;
int LastBreakpointPos = 0;

FXDEFMAP(BotDNAWindow_Class) BotDNAWindow_ClassMap[] = {
  FXMAPFUNC(SEL_COMMAND, BotDNAWindow_Class::ID_STEP, BotDNAWindow_Class::onCmdStep),
  FXMAPFUNC(SEL_COMMAND, BotDNAWindow_Class::ID_CONTINUE, BotDNAWindow_Class::onCmdContinue),
  FXMAPFUNC(SEL_COMMAND, BotDNAWindow_Class::ID_BREAKPOINT, BotDNAWindow_Class::onCmdBreakpoint),
  FXMAPFUNC(SEL_COMMAND, BotDNAWindow_Class::ID_TOCURSOR, BotDNAWindow_Class::onCmdToCursor),
  FXMAPFUNC(SEL_TIMEOUT, BotDNAWindow_Class::ID_UPDGUI, BotDNAWindow_Class::onUpdGUI)
};

FXIMPLEMENT(BotDNAWindow_Class,FXDialogBox,BotDNAWindow_ClassMap,ARRAYNUMBER(BotDNAWindow_ClassMap))

//********************
//Local Functions
//*********************
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
//******************************

BotDNAWindow_Class::BotDNAWindow_Class(Robot *bot, FXComposite *parent) : 
    FXDialogBox(parent, "Bot DNA", DECOR_TITLE | DECOR_BORDER)
{
    if (bot == NULL)
    {
        this->detach();
        this->destroy();
        return;
    }
    
    point = bot;
    CurrBotDebugControls.Clear();
    CurrBotDebugControls.SetBot(bot);

    FXMatrix *LayoutMatrix = new FXMatrix(this, 1, MATRIX_BY_COLUMNS | LAYOUT_SIDE_TOP | LAYOUT_FILL);

    //Setup Toolbar
    {
        FXGroupBox *ButtonGroup = new FXGroupBox(LayoutMatrix,NULL,FRAME_RIDGE | LAYOUT_FILL_X | LAYOUT_FILL_ROW);
        FXMatrix *ButtonMatrix = new FXMatrix(ButtonGroup, 1, MATRIX_BY_ROWS | LAYOUT_FILL_X | LAYOUT_FILL_ROW,
            0,0,0,0,0,0,0,0);
        
        //new FXSeparator(toolbar);
        
        new FXButton(ButtonMatrix, "Toggle Breakpoint", 0, this,
        	         ID_BREAKPOINT, LAYOUT_FIX_WIDTH | FRAME_RIDGE | FRAME_RAISED | FRAME_THICK,
                     0,0,100,0,10,10,0,0);
    
        new FXButton(ButtonMatrix, "Run", 0, this,
        	         ID_CONTINUE, LAYOUT_FIX_WIDTH | FRAME_RIDGE | FRAME_RAISED | FRAME_THICK,
                     0,0,100,0,10,10,0,0);
    
        new FXButton(ButtonMatrix, "Step", 0, this,
        	         ID_STEP, LAYOUT_FIX_WIDTH | FRAME_RIDGE | FRAME_RAISED | FRAME_THICK,
                     0,0,100,0,10,10,0,0);
    
        new FXButton(ButtonMatrix, "Run to Cursor", 0, this,
        	         ID_TOCURSOR, LAYOUT_FIX_WIDTH | FRAME_RIDGE | FRAME_RAISED | FRAME_THICK,
                     0,0,100,0,10,10,0,0);
    }
    
    //Setup Info Screen
    {
        FXGroupBox *InfoGroup = new FXGroupBox(LayoutMatrix,NULL,FRAME_RIDGE | LAYOUT_FILL_X | LAYOUT_FILL_ROW);
        FXMatrix *InfoMatrix = new FXMatrix(InfoGroup, 1, MATRIX_BY_ROWS | LAYOUT_FILL_X | LAYOUT_FILL_ROW,
            0,0,0,0,0,0,0,0);
        
        new FXLabel(InfoMatrix, "Cursor's DNA Position: ");
        new FXTextField(InfoMatrix, 4, new FXDataTarget((FXint &) CursorDNAPos), FXDataTarget::ID_VALUE);
        //Current Cursor DNA Position
        
        //Last Breakpoint DNA Position
    }

    //Setup DNA
    {

        FXGroupBox *DNAFrame=new FXGroupBox(LayoutMatrix,
            "Bot DNA",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y | LAYOUT_FILL_COLUMN);

        DNATextBox = new FXText(DNAFrame, NULL, 0, 
            TEXTFIELD_REAL | JUSTIFY_LEFT | FRAME_RIDGE | FRAME_RAISED | FRAME_THICK |
            LAYOUT_FILL_X | LAYOUT_FIX_HEIGHT, 0,0,
            200,//width
            250);
    
        DNATextBox->setText(point->DNA_Text().c_str(),
                            (int)strlen(point->DNA_Text().c_str()));
    
        DNATextBox->setDelimiters(" \n\t");
        DNATextBox->setEditable(false);
    }

    this->create();
    this->show();
    
    getApp()->addTimeout(this, ID_UPDGUI, 32);
}

long BotDNAWindow_Class::onCmdStep(FXObject*,FXSelector,void*)
{
    if(CurrBotDebugControls.Wait())
    {
        CurrBotDebugControls.SetStep(true);
        CurrBotDebugControls.SetWait(false);
        HighlightCurrStep();
    }
    
    return 0;
}

long BotDNAWindow_Class::onCmdContinue(FXObject*,FXSelector,void*)
{
    CurrBotDebugControls.SetWait(false);
    return 0;
}

long BotDNAWindow_Class::onCmdBreakpoint(FXObject*,FXSelector,void*)
{
    int y = this->CursorToDNAPosition(DNATextBox->getCursorPos());
    
    if(CurrBotDebugControls.IsBreakpoint(y))
        CurrBotDebugControls.RemoveBreakpoints(y);
    else
        CurrBotDebugControls.AddBreakpoints(y);
    
    HighlightBreakpoints();
    return 0;
}

long BotDNAWindow_Class::onCmdToCursor(FXObject*,FXSelector,void*)
{
    return 0;
}

long BotDNAWindow_Class::onUpdGUI(FXObject*,FXSelector,void*)
{
    static int oldcursor = -1;
    
    if(oldcursor != DNATextBox->getCursorPos())
        CursorDNAPos = CursorToDNAPosition(DNATextBox->getCursorPos());    
    
    oldcursor = DNATextBox->getCursorPos();
    
    getApp()->addTimeout(this, ID_UPDGUI, 100);
    return 0;
}

int BotDNAWindow_Class::CursorToDNAPosition(int pos)
{
    if(pos == 0)
        return 0;
    
    int returnme = 0;
    unsigned int currpos = 0;
    
    string Text = DNATextBox->getText().text();
    
    while(NextWord(Text, currpos) <= pos)
    {
        currpos = NextWord(Text, currpos);
        returnme++;        
    }
    
    return returnme;
}

int BotDNAWindow_Class::DNAPositionToCursor(int pos)
{
    string Text = DNATextBox->getText().text();
    int returnme = 0;
    
    for(int x = 0; x < pos; x++)
        returnme = NextWord(Text, returnme);
    
    return returnme;
}

void BotDNAWindow_Class::HighlightBreakpoints()
{
    DNATextBox->setText(point->DNA_Text().c_str(),
                        (int)strlen(point->DNA_Text().c_str()));
    
    list<int> Breakpoints = CurrBotDebugControls.Breakpoints();
    for(list<int>::iterator x = Breakpoints.begin(); x != Breakpoints.end(); x++)
    {
        int y = DNATextBox->wordStart(DNAPositionToCursor(*x));
        DNATextBox->insertText(y, "(", 1);
        DNATextBox->insertText(DNATextBox->wordEnd(y), ")", 1);
    }
}

void BotDNAWindow_Class::HighlightCurrStep()
{
    int y = DNAPositionToCursor(CurrBotDebugControls.CurrSpot());
    
    DNATextBox->killSelection();
    DNATextBox->setSelection(y, DNATextBox->wordEnd(y) - y);
}