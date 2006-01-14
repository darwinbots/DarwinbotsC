#include "EngineThread.h"
#include "Engine.h"

EngineThread_Class EngineThread;

int EngineThread_Class::run()
{
    Engine.SetupSim();
    
    while(true)
    {
        Engine.UpdateSim();
        this->sleep(0, 8000000);
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