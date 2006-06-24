#include <time.h>
#include "..\GUI\GUIMain.h"
#include "EngineThread.h"
#include "Engine.h"
#include "SimOptions.h"

EngineThread_Class EngineThread;

inline float round(float value)
{
    return float(int(value * 100))/100;
}

int EngineThread_Class::run()
{
    try
    {    
        time_t elapsed_time = clock(), second_counter = time(NULL);
        int x = 0;
        Engine.SetupSim();

        SimOpts.CycSec = 0;

        while(true)
        {
            if(this->Flow.Counter() >= 0)
            {
                Engine.UpdateSim();
                Flow.Add_Cycles(-1);
                x++;
            }
            
            //update cyc/sec calculation at most once every tenth second
            if(float(clock() - elapsed_time) / float(CLOCKS_PER_SEC) >= .1f)
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

void EngineThread_Class::ProgramInitialize()
{
    Engine.ProgramInitialize();
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
