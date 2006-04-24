#ifndef UEG_H
#define UEG_H

#include <iostream>
#include <vector>
#include <list>

#include "../Common/Vectors.h"

using namespace std;

class Robot;

#define GRID_DIM 1440.0f //RobSize * 12.0f; //this is the eye sight range, which is capped here

class EyeGrid_Class
{
    #pragma warning(disable : 4786) //get rid of "identifier too long, name clipped" warning
    vector< vector< list<Robot *> > > Grid;
    bool OutOfBounds(const Vector3f &GridIndex);
    
    public:
    Setup(Vector3f Dimensions);
    EyeGrid_Class();
    Insert(Robot *bot, Vector3f GridIndex);
    Insert(Robot *me);
    Remove(Robot *bot, Vector3f GridCenter);
    Move(Robot *bot);
    WhatCanSeeMe(Robot *me, list<Robot *> &BotList);        
};

#endif