#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>

using namespace std;

class Engine_Class
{
	public:

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
    string maindir;
};

extern Engine_Class Engine;
#endif
