//#include <windows.h>
#include "SimOptions.h"
#include "HardDriveRoutines.h"
#include "Shots.h"

#include "Engine.h"

Engine_Class Engine;

void Engine_Class::UpdateSim(void)
{
    //the order of functions here is very important.
    //don't idley add or (re)move functions without
    //_really_ thinking about how it changes the
    //order of other functions

	unsigned int counter;
	this->ExecuteDNA();
    this->ExecuteShots();
	
	////////////////////
	//UpdateBots
	////////////////////
	
	//update counters

	//Before anything else...
	for(counter = 0; counter<=MaxRobs; counter++)
		if (rob[counter] != NULL)
			rob[counter]->TurnGenesis();

	for(counter = 0; counter<=MaxRobs; counter++)
		if (rob[counter] != NULL)
			rob[counter]->PreTurn();

	for(counter = 0; counter<=MaxRobs; counter++)
		if (rob[counter] != NULL)
			rob[counter]->DuringTurn();

	for(counter = 0; counter<=MaxRobs; counter++)
		if (rob[counter] != NULL)
			rob[counter]->PostTurn();

	for(counter = 0; counter<=MaxRobs; counter++)
		if (rob[counter] != NULL)
			rob[counter]->TurnCleanup();

	//repopulate veggies
	
	//Write senses
	for(counter = 0; counter<=MaxRobs; counter++)
		if (rob[counter] != NULL)
			rob[counter]->TurnEnd();

    //update cycle count
	SimOpts.TotRunCycle++;
}

void Engine_Class::SetupSim(void)
{
	ReadSett("c:\\DarwinbotsII\\settings\\lastexit.set", SimOpts);
    this->maindir = "C:\\DarwinbotsII\\";

    BuildSysvars();
	
	//seed the random number generator
	DBsrand(800741);
	//Load script Lists

	//setup graphics engine

	SimOpts.MutCurrMult = 1;
	SimOpts.TotRunCycle = 0;
	SimOpts.TotBorn = 0;
	SimOpts.TotRunTime = 0;

	//reset graphs
	
    //initialize the robot and shot pointer array
	for (unsigned int x = 0; x < 5000; x++)
    {
        rob[x] = NULL;
        shots[x] = NULL;
    }

	MaxRobs = 0;
    MaxShots = 0;

	this->LoadRobots();

	//draw first frame

	//MDIForm.enablesim(?)

	//create archive if database recording is on

	//initalize the upload/download boxes for internet sharing

	//initialize F1 contest mode

	//initialize league mode

	/*  
	If SimOpts.MaxEnergy > 1000 Then
		If MsgBox("Your nrg allotment is set to" + Str(SimOpts.MaxEnergy) + ".  A correct value " + _
			      "is in the neighborhood of about 10 or so.  Do you want to change your energy allotment " + _
				  "to 10?", vbYesNo, "Energy allotment suspicously high.") = vbYes Then
			SimOpts.MaxEnergy = 10
		End If
	End If
	*/

	//setup engine thread (just calls Engine::Update_Sim over and over)
	//setup graphics thread
	//setup input thread

	/*unsigned long clocks;
	unsigned long counter=0;

    cout << rob[0]->DNA_Text();
	
	do
	{
		clocks = GetTickCount();
		this->UpdateSim();
		clocks = GetTickCount() - clocks;
		clocks = (clocks);
		cout << clocks << endl;
	}while(++counter < 5);*/
}

void Engine_Class::LoadRobots(void)
{
	Robot *temp;
	for (unsigned int y = 0; y < SimOpts.SpeciesNum; y++)
	{
		for (unsigned int x = 0; x < SimOpts.Specie[y].qty; x++)
		{
			temp = new Robot;
			temp->init(&(SimOpts.Specie[y]));
		}
	}
}

void Engine_Class::ExecuteDNA()
{
    for (unsigned long x = 0; x <= MaxRobs; x++)
        if (rob[x] != NULL)
            rob[x]->ExecuteDNA();
}

void Engine_Class::ExecuteShots()
{   
	for(unsigned long counter = 0; counter <= MaxShots; counter++)
        if(shots[counter] != NULL)
            shots[counter]->UpdateShot();
}

void FindOpenSpace(Robot *me) //finds spot for robot in array, returns pointer to said robot
{
	int firstopenspot=0;

	while(rob[firstopenspot] != NULL && firstopenspot <= MaxRobs)
	{
		firstopenspot++;
	}

	//push back MaxRobs if we need to
	if (firstopenspot > MaxRobs)
		MaxRobs = firstopenspot;

	//expand dynamic array if we need to
	//we go by 1000s
	//if (firstopenspot >= rob.capacity())
	//	//rob.resize(rob.capacity() + 1000, NULL);

	rob[firstopenspot] = me;
}

Robot *FindSerialNumber(unsigned long serial)
{
    for(unsigned int x = 0; x <= MaxRobs; x++)
        if(rob[x] != NULL && rob[x]->findAbsNum() == serial)
            return rob[x];
    return NULL;
}