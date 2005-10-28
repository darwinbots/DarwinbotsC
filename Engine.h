#ifndef ENGINE_H
#define ENGINE_H

class Engine_Class
{
	public:

	void UpdateSim(void);
	void SetupSim(void);
	
	private:
	void LoadRobots(void);
};

extern Engine_Class Engine;
#endif