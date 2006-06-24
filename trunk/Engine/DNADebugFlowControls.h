#include <list>
class Robot;

using namespace std;

class DNADebugFlowControls
{
    int currspot; //where in the DNA we are
    Robot *bot; //bot being debugged
    
    list<int> breakpoints; //list of all the breakpoints in ascending order
    list<int> interestingSysvars;
    
    bool wait; //should the engine thread wait?  It'll wait until this is set to false
    bool step; //is there a single step pending?
    bool intStack; //display the stack?
    bool condStack; //display the conditions stack?    
    
    public:
    DNADebugFlowControls()
    {
        Clear();
    }
    
    void Clear();
    
    //Update Position
    void UpdatePosition(int newloc, bool idle);
    int CurrSpot();
    
    //Bot reference controls
    Robot *Bot();
    void SetBot(Robot *bot);
    
    //Wait state
    bool Wait();
    void SetWait(bool val);
    
    //Step
    bool Step();
    void SetStep(bool val);
        
    //Sysvar controls
    void AddSysvar(int sysvar);
    void RemoveSysvar(int sysvar);
    void ClearSysvars();
    const list<int> &Sysvars();
    
    //Breakpoint controls
    void AddBreakpoints(int breakpoint);
    void RemoveBreakpoints(int breakpoint);
    void ClearBreakpoints();
    const list<int> &Breakpoints() const;
    bool IsBreakpoint(int loc);
}extern CurrBotDebugControls;