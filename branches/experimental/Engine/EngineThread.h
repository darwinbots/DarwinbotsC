#ifndef ENGINETHREAD_H
#define ENGINETHREAD_H

#include <fx.h>
#include <time.h>
#include <map>

#include "Engine.h"
#include "SimOptions.h"

class EngineThread : public FXThread
{
    typedef std::map<unsigned long, Robot*> WatchMap;
    public:

    int run();
    EngineThread();

    long addCycles(long cycles);
    long pause();
    long play();
    long counter();
    //bool isRunning() const;

    std::vector<SolidPrimitive> getRobotDisplayList();
    ShotList getShotDisplayList();
    unsigned long findAbsNum(Vector3f pos);
    Robot* getRobot(unsigned long selection);
    void addWatch(unsigned long selection);

    private:
        Simulation* simulation;

        FXMutex botListMutex;
        long runCounter;
        std::vector<SolidPrimitive> botDisplayList;
        ShotList shotDisplayList;
        WatchMap watchedBots;

        void updateWatchedBots();
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

