#include <time.h>
#include "EngineThread.h"
#include "Engine.h"

EngineThread_Class EngineThread;

inline float round(float value)
{
    return float(int(value * 100))/100;
}

int EngineThread_Class::run()
{
    time_t elapsed_time = clock(), second_counter = time(NULL);
    int x = 0;
    Engine.SetupSim();
    
    while(true)
    {
        if(this->Flow.Counter() >= 0)
        {
            Engine.UpdateSim();
            Flow.Add_Cycles(-1);
            x++;
        }
        this->sleep(0, 5000000);
        
        //update cyc/sec calculation at most once every quarter second
        if(float(clock() - elapsed_time) / float(CLOCKS_PER_SEC) >= .25f)
        {
            SimOpts.CycSec = round(x * float(CLOCKS_PER_SEC) / float(clock() - elapsed_time));
            elapsed_time = clock();
            x = 0;
        }
    }

    return 1;
}

/*
Important Note:

Presently (though you should check to be sure if you're interested
since it's possible that I've forgotten to get rid of this comment)
the engine and GFX both read from the world data without mutual ex-
clusion.  This isn't a technical problem, since the GFX engine
doesn't update anything, only reads data.  However, some display
abnormalities are possible unless some thread-safe devices (mutex's
for example) are used to limit access to world data.
*/