#include "..\GUI\MainWindow.h"
#include "EngineThread.h"

inline float round(float value)
{
    return float(int(value * 100))/100;
}

EngineThread::EngineThread():runCounter(0)
{
    Engine.ProgramInitialize();
}

int EngineThread::run()
{
    try
    {    
        time_t elapsed_time = clock(), second_counter = time(NULL);
        int x = 0;
        Engine.SetupSim();

        SimOpts.CycSec = 0;

        while(true)
        {
            if(runCounter >= 0)
            {
                Engine.UpdateSim();
                addCycles(-1);
                x++;
            }
            
            //update cyc/sec calculation at most once every half second
            if(float(clock() - elapsed_time) / float(CLOCKS_PER_SEC) >= .5f)
            {
                SimOpts.CycSec = round(x * float(CLOCKS_PER_SEC) / float(clock() - elapsed_time));
                elapsed_time = clock();
                x = 0;
            }

            //release control back to the simulation to execute GUI commands, etc. 
            this->sleep(0, 0);
        }

        return 1;
    }
    catch(...)
    {
        //FXMessageBox::warning(MainWindowHandle, MBOX_OK, "Error!", "Error!");
        assert(!"Exception Thrown");
        throw;
        //int a;

        
        
        //MaxRobs = 0;
        /*MaxShots = 0;

        for (unsigned int x = 0; x < 5000; x++)
        {
            if(rob[x])
            {
                delete rob[x];
                rob[x] = NULL;
            }

            if(rob[x])
            {
                delete shots[x];
                shots[x] = NULL;
            }
        }
        throw;*/

    }

    return 0;
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
