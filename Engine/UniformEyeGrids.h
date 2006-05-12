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
    bool OutOfBounds(const Vector3i &GridIndex);
    
    public:
    void EyeGrid_Class::Setup(Vector3i Dim);
    EyeGrid_Class();
    void Insert(Robot *bot, Vector3i GridIndex);
    void Insert(Robot *me);
    void Remove(Robot *bot, Vector3i GridCenter);
    void Move(Robot *bot);
    void WhatCanSeeMe(Robot *me, list<Robot *> &BotList);        
};

#endif
