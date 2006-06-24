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

    void ExecuteDNA();
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

    void WhatCanSeeMe(Robot *me, list<Robot *> &BotList);
    void EyeGridRemoveDeadBot(Robot *bot);
	
	private:
	void LoadRobots(void);
    void ExecuteShots();
    void RepopulateVeggies();
    string maindir;
    EyeGrid_Class EyeGrid;
    void ManipulateEyeGrid(Robot *bot);
    void Constraints();
    
}extern Engine;

void FindOpenSpace(Robot *me); //finds spot for robot in array, returns pointer to said robot
Robot *FindSerialNumber(unsigned long serial);  //find a robot with this serial number or return NULL

#endif
