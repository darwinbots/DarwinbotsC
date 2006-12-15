#include "..\GUI\MainWindow.h"
#include "EngineThread.h"
#include<iostream>

inline float round(float value)
{
    return float(int(value * 100))/100;
}

EngineThread::EngineThread():runCounter(0),botDisplayList()
                                ,simulation(&Engine)
                                ,isCancelled(false)
{

}

int EngineThread::run()
{
    try
    {
        time_t elapsed_time = clock(), second_counter = time(NULL);
        int x = 0;
        simulation->setup();

        SimOpts.CycSec = 0;

        while(!isCancelled)
        {
            if(runCounter >= 0)
            {
                simulation->UpdateSim();
                botListMutex.lock();
                simulation->getRobotDisplayList(botDisplayList);
                simulation->getShotDisplayList(shotDisplayList);
                updateWatchedBots();
                //std::cout<<"Updated botDisplayList, "<<botDisplayList.size()<<" bots."<<std::endl;
                botListMutex.unlock();
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

        simulation->clear();
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

std::vector<SolidPrimitive> EngineThread::getRobotDisplayList()
{
    FXMutexLock lock(botListMutex);
    return botDisplayList;
}

ShotList EngineThread::getShotDisplayList()
{
    FXMutexLock lock(botListMutex);
    return shotDisplayList;
}

unsigned long EngineThread::findAbsNum(Vector3f pos)
{
    FXMutexLock lock(botListMutex);
    for (std::vector<SolidPrimitive>::iterator currBot = botDisplayList.begin(); currBot != botDisplayList.end(); ++currBot)
    {
        Vector3f diff = pos - currBot->getPos();
        if(diff.LengthSquared() <= currBot->getRadius() * currBot->getRadius())
        {
            return currBot->getAbsNum();
        }
    }
    return 0;  //if no robot matches the given position
}

Robot* EngineThread::getRobot(unsigned long selection)
{
    FXMutexLock lock(botListMutex);
    WatchMap::iterator entry = watchedBots.find(selection);
    if (entry != watchedBots.end())
        return entry->second;
    else
        return NULL;
}

void EngineThread::updateWatchedBots()
{
// FIXME (Ronan#1#): Need to handle bot's death properly
    for(WatchMap::iterator entry=watchedBots.begin(); entry != watchedBots.end(); ++entry)
    {
        Robot* bot= simulation->getRobot(entry->first);
        if (bot != NULL)
            *(entry->second) = Robot(*bot);
    }
}

void EngineThread::addWatch(unsigned long selection)
{
    FXMutexLock lock(botListMutex);
    Robot* bot= simulation->getRobot(selection);
    if (bot != NULL)
        watchedBots[selection] = new Robot(*bot);
}
