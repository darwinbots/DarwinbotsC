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
EyeGrid_Class::Setup(Vector3f Dimensions)
{
    Grid.resize((int)Dimensions.x());
    
    for(unsigned int x = 0; x < Grid.size(); x++)
    {
        Grid[x].resize((int)Dimensions.y());
    }
}

bool EyeGrid_Class::OutOfBounds(const Vector3f &GridIndex)
{
    if(GridIndex.x() < 0 || GridIndex.x() >= Grid.size())
        return true;

    if(GridIndex.y() < 0 || GridIndex.y() >= Grid[0].size())
        return true;

    return false;
}

//Insert bot into grid GridIndex
EyeGrid_Class::Insert(Robot *bot, Vector3f GridIndex)
{
    if(OutOfBounds(GridIndex))
        return false;

    Grid[(int)GridIndex.x()][(int)GridIndex.y()].push_back(bot);
    
    return true;
}

//Check what grids the bot can see and insert it into all such grids
EyeGrid_Class::Insert(Robot *me)
{
    Vector3f GridCenter = floor(me->findpos() / GRID_DIM);

    Vector3f xBounds(-1, 1), yBounds(-1, 1);
    
    for(int x = (int)xBounds[0]; x <= (int)xBounds[1]; x++)
        for(int y = (int)yBounds[0]; y <= (int)yBounds[1]; y++)
            Insert(me, GridCenter + Vector3f((float)x, (float)y));
}

EyeGrid_Class::Remove(Robot *bot, Vector3f GridCenter)
{
    Vector3f pos;

    for(int x = -1; x <= 1; x++)
        for(int y = -1; y <= 1; y++)
        {
            Vector3f GridIndex = GridCenter + Vector3f((float)x, (float)y);

            if(OutOfBounds(GridIndex))
                continue;
            
            Grid[(int)GridCenter.x() + x][(int)GridCenter.y() + y].remove(bot);
        }
}

EyeGrid_Class::Move(Robot *bot)
{
    if(!bot->View)
        return 0;
    
    Vector3f GridCenter;
    Vector3f leftover;
    Vector3f xBound, yBound;

    GridCenter = floor(bot->findpos() / GRID_DIM);
    leftover = bot->findpos() - GridCenter * GRID_DIM;
    
    if(leftover.x() < GRID_DIM / 2)
        xBound(0) = -1, xBound(1) = 0;
    else
        xBound(1) = 1, xBound(0) = 0;
    
    if(leftover.y() < GRID_DIM / 2)
        yBound(0) = -1, yBound(1) = 0;
    else
        yBound(1) = 1, yBound(0) = 0;

    Remove(bot, GridCenter);
    for(int x = (int)xBound(0); x <= (int)xBound(1); x++)
        for(int y = (int)yBound(0); y <= (int)yBound(1); y++)
            Insert(bot, GridCenter + Vector3f((float)x, (float)y));

    return 1;
}

//Modifies BotList to contain a list of all bots that can potentially see this bot.
//The bots returned will still need to be checked by CompareRobots
EyeGrid_Class::WhatCanSeeMe(Robot *me, list<Robot *> &BotList)
{
    Vector3f GridCenter = floor(me->findpos() / GRID_DIM);
    Vector3f LeftOver = me->findpos() - GridCenter * GRID_DIM;
    Vector3f xBounds, yBounds;
    list<Robot *> *InsertMe;

    xBounds.set(0,0,0);
    yBounds.set(0,0,0);

    if(LeftOver.x() - me->rad() < 0)
        xBounds(0) = -1; //check out left hand side
    if(LeftOver.x() + me->rad() >= GRID_DIM)
        xBounds(1) = 1; //check out right hand side
    if(LeftOver.y() + me->rad() >= GRID_DIM)
        yBounds(1) = 1; //check out top side
    if(LeftOver.y() - me->rad() < 0)
        yBounds(0) = -1 ;//check out bottom side

    Vector3f GridIndex;
    for(int x = (int)xBounds[0]; x <= (int)xBounds[1]; x++)
        for(int y = (int)yBounds[0]; y <= (int)yBounds[1]; y++)
        {
            GridIndex(0) = GridCenter.x() + x;
            GridIndex(1) = GridCenter.y() + y;

            //Don't check out of bounds
            if(OutOfBounds(GridIndex))
                continue;
            
            InsertMe = &Grid[(int)GridIndex[0]][(int)GridIndex[1]];
            BotList.insert(BotList.end(), InsertMe->begin(), InsertMe->end());
        }

    //remove duplicates from list
    BotList.sort();
    BotList.unique();
}