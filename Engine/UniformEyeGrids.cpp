#include "UniformEyeGrids.h"
#include "Robot.h"

/*******************************
Basic idea:

Divide the world into 1440 sized grid cells that contain linked lists
of robot pointers.

For every robot that can see, put his pointer into all the grids'
linked list for every grid he can see.

During eye tests, check every bot against the cell(s) it's presently in
to see what bots can see it.  Since bots have radius and aren't just single points,
bots may need to test multiple grids
*//////////////////////////////////////////
EyeGrid_Class::EyeGrid_Class()
{
}

//call this whenever we either reset the sim
//or change dimensions
void EyeGrid_Class::Setup(Vector3i Dim)
{
    Grid.resize(Dim.x());
    
    for(unsigned int x = 0; x < Grid.size(); x++)
    {
        Grid[x].resize(Dim.y());
    }
}

bool EyeGrid_Class::OutOfBounds(const Vector3i &GridIndex)
{
    if(GridIndex.x() < 0 || GridIndex.x() >= (int)Grid.size())
        return true;

    if(GridIndex.y() < 0 || GridIndex.y() >= (int)Grid[0].size())
        return true;

    return false;
}

//Insert bot into grid GridIndex
void EyeGrid_Class::Insert(Robot *bot, Vector3i GridIndex)
{
    if(OutOfBounds(GridIndex))
        return;

    Grid[GridIndex.x()][GridIndex.y()].push_back(bot);
}

//Check what grids the bot can see and insert it into all such grids
void EyeGrid_Class::Insert(Robot *me)
{
    Vector3i GridCenter = Vector3i(int(me->getPos().x() / GRID_DIM),
                                   int(me->getPos().y() / GRID_DIM),
                                   int(me->getPos().z() / GRID_DIM));

    Vector3i xBounds(-1, 1), yBounds(-1, 1);
    
    for(int x = xBounds[0]; x <= (int)xBounds[1]; x++)
        for(int y = yBounds[0]; y <= (int)yBounds[1]; y++)
            Insert(me, GridCenter + Vector3i(x, y));
}

void EyeGrid_Class::Remove(Robot *bot, Vector3i GridCenter)
{
    for(int x = -1; x <= 1; x++)
        for(int y = -1; y <= 1; y++)
        {
            Vector3i GridIndex = GridCenter + Vector3i(x, y);

            if(OutOfBounds(GridIndex))
                continue;
            
            Grid[GridCenter.x() + x][GridCenter.y() + y].remove(bot);
        }
}

void EyeGrid_Class::Move(Robot *bot)
{
    if(!bot->View)
        return;
    
    Vector3i xBound, yBound;

    Vector3i GridCenter(int(bot->getPos().x() / GRID_DIM),
                        int(bot->getPos().y() / GRID_DIM),
                        int(bot->getPos().z() / GRID_DIM));
    
    Vector3f leftover(bot->getPos().x() - GridCenter.x() * GRID_DIM,
                      bot->getPos().y() - GridCenter.y() * GRID_DIM,
                      bot->getPos().z() - GridCenter.z() * GRID_DIM);
    
    if(leftover.x() < GRID_DIM / 2)
        xBound(0) = -1, xBound(1) = 0;
    else
        xBound(1) = 1, xBound(0) = 0;
    
    if(leftover.y() < GRID_DIM / 2)
        yBound(0) = -1, yBound(1) = 0;
    else
        yBound(1) = 1, yBound(0) = 0;

    Remove(bot, GridCenter);
    for(int x = xBound(0); x <= xBound(1); x++)
        for(int y = yBound(0); y <= yBound(1); y++)
            Insert(bot, GridCenter + Vector3i(x, y));
}

//Modifies BotList to contain a list of all bots that can potentially see this bot.
//The bots returned will still need to be checked by CompareRobots
void EyeGrid_Class::WhatCanSeeMe(Robot *me, list<Robot *> &BotList)
{
    Vector3i GridCenter(int(me->getPos().x() / GRID_DIM),
                        int(me->getPos().y() / GRID_DIM),
                        int(me->getPos().z() / GRID_DIM));
    
    Vector3f LeftOver(me->getPos().x() - GridCenter.x() * GRID_DIM,
                      me->getPos().y() - GridCenter.y() * GRID_DIM,
                      me->getPos().z() - GridCenter.z() * GRID_DIM);

    Vector3i xBounds(0,0), yBounds(0,0);
    list<Robot *> *InsertMe;

    if(LeftOver.x() - me->getRadius() < 0)
        xBounds(0) = -1; //check out left hand side
    if(LeftOver.x() + me->getRadius() >= GRID_DIM)
        xBounds(1) = 1; //check out right hand side
    if(LeftOver.y() + me->getRadius() >= GRID_DIM)
        yBounds(1) = 1; //check out top side
    if(LeftOver.y() - me->getRadius() < 0)
        yBounds(0) = -1 ;//check out bottom side

    Vector3i GridIndex;
    for(int x = xBounds[0]; x <= xBounds[1]; x++)
        for(int y = yBounds[0]; y <= yBounds[1]; y++)
        {
            GridIndex.set(GridCenter.x() + x, GridCenter.y() + y);

            //Don't check out of bounds
            if(OutOfBounds(GridIndex))
                continue;
            
            InsertMe = &Grid[GridIndex[0]][GridIndex[1]];
            BotList.insert(BotList.end(), InsertMe->begin(), InsertMe->end());
        }

    //remove duplicates from list
    BotList.sort();
    BotList.unique();
}
