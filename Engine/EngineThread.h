#ifndef ENGINETHREAD_H
#define ENGINETHREAD_H

#include <fx.h>

//I haven't yet figured out how to get the Mutex controls to work right yet
class EngineThread_MasterFlowControl : public FXMutex
{
    private:
    long run_counter;

    public:
    long Add_Cycles(long cycles)
    {
        //we already have some cycles in reserve
        if(run_counter > 0)
        {
            if(run_counter + cycles > 0)
                run_counter += cycles;
            else
                run_counter = -1;
        }
        else if(run_counter == 0)
        {
            return 0;
        }
        else
        {
            if(cycles > 0)
                run_counter = cycles;
        }
        return run_counter;
    }

    long Pause()
    {
        return run_counter = -1;
    }

    long Play()
    {
        return run_counter = 0;
    }

    long Counter()
    {
        return run_counter;
    }
};

class EngineThread_Class : public FXThread
{
    public:
    int run();
    EngineThread_MasterFlowControl Flow;
    
}extern EngineThread;

#endif