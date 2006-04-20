#include "Robot.h"

__int16 CommandQueueClass::Add(__int16 location, __int16 value)
{
    for(unsigned int x = 0; x < Commands.size(); x++)
        if(Commands[x].loc == location)
        {
            Commands[x].val = value;
            return value;
        }

    Commands.push_back(MemPair(location, value));
    
    return value;
}

void CommandQueueClass::Clear()
{
    Commands.erase(Commands.begin(), Commands.end());
}

__int16 CommandQueueClass::FilterRead(__int16 location)
{
    if(location <= 0 || location > 1000)
        return 0;

    for(unsigned int x = 0; x < Commands.size(); x++)
        if(Commands[x].loc == location)
            return Commands[x].val;
    
    if(base != NULL)
        return (*base)[location];
    else
        return 0;
}

CommandQueueClass::CommandQueueClass()
{
    base = NULL;
}

void CommandQueueClass::SetBase(Robot *_base)
{
    base = _base;
}

CommandQueueClass::Apply()
{
    for(unsigned int x = 0; x < Commands.size(); x++)
        (*base)[Commands[x].loc] = Commands[x].val;

    Clear();
}