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
    Commands.clear();
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

CommandQueueClass::CommandQueueClass(Robot* robot):base(robot)
{

}

void CommandQueueClass::SetBase(Robot *_base)
{
    base = _base;
}

void CommandQueueClass::Apply()
{
    for(vector<MemPair>::iterator command = Commands.begin(); command != Commands.end(); ++command)
        (*base)[command->loc] = command->val;

    Clear();
}
