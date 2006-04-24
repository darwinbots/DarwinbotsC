#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>

#include "UniformEyeGrids.h"
class Robot;

using namespace std;

class Engine_Class
{
	//friend void DrawEyeGrid();
    
    public:

	void ProgramInitialize(void);
    void UpdateSim(void);
	void SetupSim(void);
    const string &MainDir(void)
    {
        return maindir;    
    }    
	void SetMainDir(string newDir)
    {
        maindir=newDir;
    };

    WhatCanSeeMe(Robot *me, list<Robot *> &BotList);
    EyeGridRemoveDeadBot(Robot *bot);
	
	private:
	void LoadRobots(void);
    void ExecuteDNA();
    void ExecuteShots();
    void RepopulateVeggies();
    string maindir;
    EyeGrid_Class EyeGrid;
    ManipulateEyeGrid(Robot *bot);
    
}extern Engine;

void FindOpenSpace(Robot *me); //finds spot for robot in array, returns pointer to said robot
Robot *FindSerialNumber(unsigned long serial);  //find a robot with this serial number or return NULL

#endif
