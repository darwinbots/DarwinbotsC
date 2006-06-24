#include "DNADebugFlowControls.h"

DNADebugFlowControls CurrBotDebugControls;

void DNADebugFlowControls::Clear()
{
    bot = NULL;
    currspot = 0;
    
    wait = false;    
    intStack = false;
    condStack = false;
    step = false;
}

void DNADebugFlowControls::UpdatePosition(int newloc, bool idle)
{
    if(step && !idle)
    {
        SetWait(true);
        step = false;
    }
    else if(IsBreakpoint(newloc))
        SetWait(true);
    else
        SetWait(false);
    
    currspot = newloc;
}

int DNADebugFlowControls::CurrSpot()
{
    return currspot;
}

Robot *DNADebugFlowControls::Bot()
{
    return bot;   
}

void DNADebugFlowControls::SetBot(Robot *bot)
{
    this->bot = bot;
}

//Wait controls
bool DNADebugFlowControls::Wait()
{
    return wait;
}

void DNADebugFlowControls::SetWait(bool val)
{
    wait = val;
}

//Step controls
bool DNADebugFlowControls::Step()
{
    return step;
}

void DNADebugFlowControls::SetStep(bool val)
{
    step = val;
}

//Interesting Sysvar Controls
void DNADebugFlowControls::AddSysvar(int sysvar)
{
    interestingSysvars.push_front(sysvar);
    interestingSysvars.sort();
    interestingSysvars.unique();
}

void DNADebugFlowControls::RemoveSysvar(int sysvar)
{
    interestingSysvars.remove(sysvar);
}

void DNADebugFlowControls::ClearSysvars()
{
    interestingSysvars.clear();
}

const list<int> &DNADebugFlowControls::Sysvars()
{
    return interestingSysvars;
}

//Breakpoints:
void DNADebugFlowControls::AddBreakpoints(int breakpoint)
{
    breakpoints.push_front(breakpoint);
    breakpoints.sort();
    breakpoints.unique();
}

void DNADebugFlowControls::RemoveBreakpoints(int breakpoint)
{
    breakpoints.remove(breakpoint);
}

void DNADebugFlowControls::ClearBreakpoints()
{
    breakpoints.clear();
}

const list<int> &DNADebugFlowControls::Breakpoints() const
{
    return breakpoints;
}

bool DNADebugFlowControls::IsBreakpoint(int loc)
{
    for(list<int>::iterator x = breakpoints.begin(); x != breakpoints.end(); x++ )
        if(*x == loc)
            return true;
    return false;
}