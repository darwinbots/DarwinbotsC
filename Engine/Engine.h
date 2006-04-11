#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>
#include "Robot.h"

using namespace std;

class Engine_Class
{
	public:

	void ProgramInitialize(void);
    void UpdateSim(void);
	void SetupSim(void);
    const string &MainDir(void)
    {
        return maindir;    
    }    
	void SetMainDir(std::string newDir){maindir=newDir;};
	
	private:
	void LoadRobots(void);
    void ExecuteDNA();
    void ExecuteShots();
    void RepopulateVeggies();
    string maindir;
};

void FindOpenSpace(Robot *me); //finds spot for robot in array, returns pointer to said robot
Robot *FindSerialNumber(unsigned long serial);  //find a robot with this serial number or return NULL

extern Engine_Class Engine;
#endif
