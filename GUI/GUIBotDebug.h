#ifndef GUIBOTDEBUG_H
#define GUIBOTDEBUG_H

#include <fx.h>
#include "../Engine/Robot.h"
#include "../Engine/DNA_Execution.h"

/*struct PairOInts
{
    int value;
    int location;
};

struct Bottarget_typ
{
    FXDataTarget DNA;
    FXDataTarget name;

    FXDataTarget age;
    FXDataTarget nrg;
    FXDataTarget body;
    FXDataTarget newmutations;
    FXDataTarget generation;
    FXDataTarget mutations; 
    
    FXDataTarget shell;
    FXDataTarget slime;
    FXDataTarget poison;
    FXDataTarget venom;
    FXDataTarget waste;
    FXDataTarget pwaste;

    FXDataTarget dnalength;
    FXDataTarget numgenes;

    FXDataTarget stack[20];

    FXDataTarget memory[20];
};

struct tempBot_typ
{
    FXString DNA;
    FXString name;

    FXint age;
    FXfloat nrg;
    FXfloat body;
    FXint newmutations;
    FXint generation;
    FXint mutations; 
    
    FXfloat shell;
    FXfloat slime;
    FXfloat poison;
    FXfloat venom;
    FXfloat waste;
    FXfloat pwaste;

    FXint dnalength;
    FXint numgenes;

    FXint stack[20];

    int memory[20];
    int lastmem;

    Bottarget_typ datatargets;

    unsigned int DNA_pos;
    unsigned int IntStack_pos;

    void Update(Robot *bot);
    void Linkup();
    void Initialize(Robot *bot);
};*/

class BotDebug_Window : public FXDialogBox
{
    FXDECLARE(BotDebug_Window)

    //friend tempBot_typ;

    private:
    bool DEBUGMODE;
    Robot *point;
    FXMatrix *LayoutMatrix, *SideCheck;
    FXGroupBox *IntStackFrame;
    FXGroupBox *DNAFrame;
    FXText     *DNATextBox;
    FXGroupBox *SysvarsFrame;
    FXMatrix *SysvarsMatrix;
    FXLabel  *SysvarsLabel[20];
    FXGroupBox *DetailsFrame;
    FXTextField *SysvarsTextField[20];
    FXTextField *IntStackTextField[20];

    public:
    //tempBot_typ BotTargetInfo;

    private:
    void SetupToolbar();
    void SetupLayout();
    void SetupSideBar();
    void SetupIntStackFrame();
    void SetupDNAFrame();
    void SetupSysvarsFrame();
    void SetupDetailsFrame();

    void LinkBotTarget();
    
    public:
    void AddInterestingSysvars(int number);
    const Robot *ThatBot() const
    {
        return point;
    }

    void SetThatBot(Robot *bot)
    {
        point = bot;
    }

    bool DebugMode()
    {
        return DEBUGMODE;
    }
    
    
    long onCmdStep(FXObject*,FXSelector,void*) {return 0;}
    
    long onCmdShowIntStack(FXObject*,FXSelector,void *ptr);
    long onCmdShowDNA(FXObject*,FXSelector,void *ptr)     ;
    long onCmdShowSysvars(FXObject*,FXSelector,void *ptr) ;
    long onCmdShowDetails(FXObject*,FXSelector,void *ptr) ;

    void hide();
    void show(FXuint placement = 0);

    void Update();    

    BotDebug_Window(Robot *bot = NULL, FXComposite *parent = NULL);
    
    enum
    {
        ID_ME = FXDialogBox::ID_LAST,
        ID_BREAKPOINT,
        ID_CONTINUE,
        ID_STEP,
        ID_TOCURSOR,
        
        ID_SHOWINTSTACK,
        ID_SHOWDNA,
        ID_SHOWSYSVARS,
        ID_SHOWDETAILS
    };
};

#endif
