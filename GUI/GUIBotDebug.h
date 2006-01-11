#ifndef GUIBOTDEBUG_H
#define GUIBOTDEBUG_H

#include <fx.h>
#include "../Engine/Robot.h"

class BotDebug_Window : public FXDialogBox
{
    FXDECLARE(BotDebug_Window)

    private:
    Robot *point;
    FXMatrix *LayoutMatrix, *SideCheck;
    FXGroupBox *IntStackFrame;
    FXGroupBox *DNAFrame;
    FXGroupBox *SysvarsFrame;
    FXGroupBox *DetailsFrame;

    void SetupToolbar();
    void SetupLayout();
    void SetupSideBar();
    void SetupIntStackFrame();
    void SetupDNAFrame();
    void SetupSysvarsFrame();
    void SetupDetailsFrame();
    
    public:
    const Robot *ThatBot() const
    {
        return point;
    }

    void SetThatBot(Robot *bot)
    {
        point = bot;
    }
    
    
    long onCmdStep(FXObject*,FXSelector,void*) {return 0;}
    
    long onCmdShowIntStack(FXObject*,FXSelector,void *ptr);
    long onCmdShowDNA(FXObject*,FXSelector,void *ptr)     ;
    long onCmdShowSysvars(FXObject*,FXSelector,void *ptr) ;
    long onCmdShowDetails(FXObject*,FXSelector,void *ptr) ;
    

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

    vector<FXDataTarget> memory;
};//tempBot;

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

    vector<FXint> memory;

    Bottarget_typ target;
    Robot *thatbot;

    unsigned int DNA_pos;
}extern tempBot;

#endif