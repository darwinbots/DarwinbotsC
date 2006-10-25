#ifndef ENGINETHREAD_H
#define ENGINETHREAD_H

#include <fx.h>
#include <time.h>

#include "Engine.h"
#include "SimOptions.h"

class EngineThread : public FXThread
{
    public:

    Simulation* simulation;

    int run();
    EngineThread();

    long addCycles(long cycles);
    long pause();
    long play();
    long counter();

    std::vector<SolidPrimitive> getRobotDisplayList();
    ShotList getShotDisplayList();
    unsigned long findAbsNum(Vector3f pos);
    Robot* getRobot(unsigned long selection);

    private:
        FXMutex botListMutex;
        long runCounter;
        std::vector<SolidPrimitive> botDisplayList;
        ShotList shotDisplayList;
    public:
    bool isCancelled;
};

inline long EngineThread::addCycles(long cycles)
{
    //we already have some cycles in reserve
    if(runCounter > 0)
    {
        if(runCounter + cycles > 0)
            runCounter += cycles;
        else
            runCounter = -1;
    }
    else if(runCounter == 0)
    {
        return 0;
    }
    else
    {
        if(cycles > 0)
            runCounter = cycles;
    }
    return runCounter;
};

inline long EngineThread::pause()
{
    return runCounter = -1;
};

inline long EngineThread::play()
{
    return runCounter = 0;
};

inline long EngineThread::counter()
{
    return runCounter;
};

#endif

