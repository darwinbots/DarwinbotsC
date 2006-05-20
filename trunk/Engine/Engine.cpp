#include <direct.h>
#include <time.h>

#include "SimOptions.h"
#include "HardDriveRoutines.h"
#include "Shots.h"
#include "Block.h"

#include "Engine.h"

Engine_Class Engine;

int counter;
#define FORALLROBOTS \
    for(counter = 0; counter <= MaxRobs; counter++) \
        if(rob[counter] != NULL)

void Engine_Class::UpdateSim(void)
{
    //the order of functions here is very important.
    //don't idley add or (re)move functions without
    //_really_ thinking about how it changes the
    //order of other functions	

    this->ExecuteDNA();  //O(n)
    this->ExecuteShots(); //Checks every shot against every bot O(mn)

    ////////////////////
	//UpdateBots
	////////////////////
	
	//update counters

	//Before anything else...
	FORALLROBOTS rob[counter]->TurnGenesis();

	FORALLROBOTS rob[counter]->PreTurn();

	//Physics Steps:    
    FORALLROBOTS rob[counter]->Integrate();

    //CONSTRAINTS (done after movement)

    //max tie length and rigid ties (if ties are hardened)

    FORALLROBOTS rob[counter]->VelocityCap();

    //More iterations decreases overlap between bots when stacking, but
    //it hardly seems practical.  A better solution must exist, which
    //more intelligently offsets colliding bots.

    //perhaps collisions with edges offsets the whole world as well (or rather,
    //offsets all objects in the world an opposite amount)
    //or conversely, bot collisions have one of the bots moving 100%
    //of the distance

    //O(n^2)
    
    float maxoverlap;
    int loopcounter = 0;
    
    #define ANGELOCOLLISION
    #ifndef ANGELOCOLLISION
    do
    {
        maxoverlap = 0.0f;
        FORALLROBOTS
        {
            float overlap = rob[counter]->BotCollisionsPos();
            maxoverlap = max(maxoverlap, overlap);
        }

        FORALLROBOTS rob[counter]->EdgeCollisions();

        loopcounter++;
    
    }while(maxoverlap > 0.1f && loopcounter <= 5);

    #else
    bool Continue;
    do
    {
        Continue = false;
        maxoverlap = 0.0f;
        
        FORALLROBOTS //for all robots 
        {
            if (rob[counter]->active)
			{			 
				float overlap = rob[counter]->BotCollisionsPos(); 
				maxoverlap = __max(maxoverlap, overlap);
			}

            
        }

        FORALLROBOTS rob[counter]->EdgeCollisions();

        unsigned int activecounter = 0;
        FORALLROBOTS
        {
            if(rob[counter]->active)
            {
                activecounter++;
                Continue = true;
            }
        }
    
    }while(Continue);

    #endif

    FORALLROBOTS ManipulateEyeGrid(rob[counter]);
    
    //END CONSTRAINTS
    //END Physics steps
    
    FORALLROBOTS rob[counter]->DuringTurn();
    
	FORALLROBOTS rob[counter]->PostTurn();
    
	FORALLROBOTS rob[counter]->TurnCleanup();
    
    FORALLROBOTS rob[counter]->Reproduce();
    
	RepopulateVeggies();
    
    FORALLROBOTS rob[counter]->CheckVision();
	
	//Write senses
	FORALLROBOTS rob[counter]->TurnEnd();
    
    //update cycle count
	SimOpts.TotRunCycle++;
}

void Engine_Class::ProgramInitialize(void)
{
    char buffer[1028];
    this->maindir = getcwd(buffer, 1028);
    ReadSett(this->maindir + "\\settings\\lastexit.set", SimOpts);

    BuildSysvars();

    //initialize the robot and shot pointer array
	for (unsigned int x = 0; x < 5000; x++)
    {
        rob[x] = NULL;
        shots[x] = NULL;
    }

	MaxRobs = -1;
    MaxShots = -1;

    SetDNAMutationsBounds();
}

void Engine_Class::SetupSim(void)
{	
	if(SimOpts.UserSeedToggle)
        DBsrand(SimOpts.UserSeedNumber);
    else
        DBsrand(time(NULL));
	
    //Load script Lists

	SimOpts.MutCurrMult = 1;
	SimOpts.TotRunCycle = 0;
	SimOpts.TotBorn = 0;
	SimOpts.TotRunTime = 0;

	MaxRobs = -1;
    MaxShots = -1;

	this->LoadRobots();

    EyeGrid.Setup(Vector3i(int(SimOpts.FieldDimensions.x() / GRID_DIM),
                           int(SimOpts.FieldDimensions.y() / GRID_DIM),
                           int(SimOpts.FieldDimensions.z() / GRID_DIM)) + Vector3i(1,1));

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
}

void Engine_Class::LoadRobots(void)
{
    for (unsigned int y = 0; y < SimOpts.SpeciesNum; y++)
        for (unsigned int x = 0; x < SimOpts.Specie[y].qty; x++)
            new Robot(&SimOpts.Specie[y]);
}

void Engine_Class::ExecuteDNA()
{
    FORALLROBOTS
        if(rob[counter]->DNA != NULL)
            rob[counter]->ExecuteDNA();

    FORALLROBOTS for(unsigned int x = 0; x < rob[counter]->Ties.size(); x++)
        if(rob[counter]->Ties[x] != NULL)
            rob[counter]->Ties[x]->ApplyCQ(); //Apply the Command Queue

    FORALLROBOTS
        if(rob[counter]->DNA != NULL)
            rob[counter]->DNACommands.Apply();
}

void Engine_Class::ExecuteShots()
{   
	int counter;
    for(counter = 0; counter <= MaxShots; counter++)
        if(shots[counter] != NULL)
            shots[counter]->UpdatePos();

    //first iteration checks for initial collision
    
    for(counter = 0; counter <= MaxShots; counter++)
        if(shots[counter] != NULL)
            shots[counter]->UpdateShot(false);

    //second iteration checks for collision of returned shots
    for(counter = 0; counter <= MaxShots; counter++)
        if(shots[counter] != NULL)
            shots[counter]->UpdateShot(true);
}

int cooldown = 0;
void Engine_Class::RepopulateVeggies()
{
    vector<int> VegSpeciesList;
    unsigned long veggcount=0;
    unsigned long notveggcount=0;

    for(int x = 0; x <= MaxRobs; x++)
    {
        if(rob[x] != NULL)
        {
            if(rob[x]->Veg)
                veggcount++;
            if(!rob[x]->Veg)
                notveggcount++;
        }
    }

    SimOpts.TotBotsNow = notveggcount;
    SimOpts.TotVegsNow = veggcount;
    SimOpts.TotObjects = veggcount + notveggcount;
    
    if(--cooldown <= 0)
        cooldown = 0;

    if(SimOpts.TotVegsNow < SimOpts.MinVegs &&
       SimOpts.RepopAmount > 0 && cooldown == 0)
    {
        unsigned int x;

        for(x = 0; x < SimOpts.SpeciesNum; x++)
            if(SimOpts.Specie[x].Veg)
            {
                VegSpeciesList.push_back(x);
            }

        if(VegSpeciesList.size() == 0)
            return;
        
        for(x = 0; x < SimOpts.RepopAmount; x++)
        {
            //this needs to be changed later into something that uses all species with vegs turned on
            unsigned int spec = frnd(0, VegSpeciesList.size() - 1);            
            
            new Robot(&SimOpts.Specie[spec]);            
            SimOpts.TotVegsNow++;
        }
        cooldown = SimOpts.RepopCooldown;
    }
}

void Engine_Class::ManipulateEyeGrid(Robot *bot)
{
    EyeGrid.Move(bot);
}

void Engine_Class::EyeGridRemoveDeadBot(Robot *bot)
{
    EyeGrid.Remove(bot, Vector3i(int(bot->findopos().x() / GRID_DIM),
                                 int(bot->findopos().y() / GRID_DIM),
                                 int(bot->findopos().z() / GRID_DIM)));
}

void Engine_Class::WhatCanSeeMe(Robot *me, list<Robot *> &BotList)
{
    EyeGrid.WhatCanSeeMe(me, BotList);
};

void FindOpenSpace(Robot *me) //finds spot for robot in array, returns pointer to said robot
{
	int firstopenspot=0;

	while(rob[firstopenspot] != NULL && firstopenspot <= MaxRobs)
	{
		firstopenspot++;
	}

    if(firstopenspot >= (int)rob.capacity())
    {
        unsigned int oldcapacity = rob.capacity();
        rob.reserve(oldcapacity + 10);
        for(unsigned int x = oldcapacity; x < oldcapacity + 10; x++)
        {
            rob[x] = NULL;
        }
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
    for(int x = 0; x <= MaxRobs; x++)
        if(rob[x] != NULL && rob[x]->findAbsNum() == serial)
            return rob[x];
    
    return NULL;
}
