#include "SimOptions.h"
#include "Robot.h"
#include "Engine.h"

bool ReadSett(const string &path, SimOptions &Options);

Engine_Class Engine;

void Engine_Class::UpdateSim(void)
{
	unsigned int counter;
	//ExecuteDNA
	//UpdateShots
	
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
	
	//seed the random number generator
	//Load script Lists

	//setup graphics engine

	SimOpts.MutCurrMult = 1;
	SimOpts.TotRunCycle = 0;
	SimOpts.TotBorn = 0;
	SimOpts.TotRunTime = 0;

	//reset graphs
	//initialize the robot pointer array
	rob.resize(1000, NULL);
	MaxRobs = 0;
	//maxshots = 0

	this->LoadRobots();
	//setfeed (?)

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

	//setup engine thread (just calls Engine::Update_Sim over and over
	//setup graphics thread
	//setup input thread

	unsigned long clocks;
	unsigned long counter=0;
	
	do
	{
///		clocks = GetTickCount();
		this->UpdateSim();
///		clocks = GetTickCount() - clocks;
///		clocks = (clocks);
		cout << clocks << endl;
	}while(++counter < 20);
}

void Engine_Class::LoadRobots(void)
{
	Robot *temp;
	for (unsigned int y = 0; y < SimOpts.SpeciesNum; y++)
	{
		for (unsigned int x = 0; x < SimOpts.Specie[y].qty; x++)
		{
			temp = new Robot(&SimOpts.Specie[y]);
			//pass species info to robot for creation process
			//robscriptload
		}
	}
}

