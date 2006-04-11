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

	int counter;
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

	//Physics Steps:    
    for(counter = 0; counter<=MaxRobs; counter++)
		if (rob[counter] != NULL)
			rob[counter]->Integrate();

    //CONSTRAINTS (done after movement)

    //max tie length and rigid ties (if ties are hardened)

    for(counter = 0; counter<=MaxRobs; counter++)
		if (rob[counter] != NULL)
            rob[counter]->VelocityCap();

    //More iterations decreases overlap between bots when stacking, but
    //it hardly seems practical.  A better solution must exist, which
    //more intelligently offsets colliding bots.

    //perhaps collisions with edges offsets the whole world as well (or rather,
    //offsets all objects in the world an opposite amount)
    //or conversely, bot collisions have one of the bots moving 100%
    //of the distance

    float maxoverlap;
    int loopcounter = 0;
    do
    {
        maxoverlap = 0.0f;
        for(counter = 0; counter<=MaxRobs; counter++)
		    if (rob[counter] != NULL)
            {
                float overlap = rob[counter]->BotCollisionsPos();
                if (overlap > maxoverlap)
                    maxoverlap = overlap;
            }

        for(counter = 0; counter<=MaxRobs; counter++)
		    if (rob[counter] != NULL)
                rob[counter]->EdgeCollisions();

        counter++;
    
    }while(maxoverlap > 0.01f && loopcounter <= 4);

    //END CONSTRAINTS
    //END Physics steps
    
    for(counter = 0; counter<=MaxRobs; counter++)
		if (rob[counter] != NULL)
			rob[counter]->DuringTurn();

	for(counter = 0; counter<=MaxRobs; counter++)
		if (rob[counter] != NULL)
			rob[counter]->PostTurn();

	for(counter = 0; counter<=MaxRobs; counter++)
		if (rob[counter] != NULL)
			rob[counter]->TurnCleanup();

    for(counter = 0; counter<=MaxRobs; counter++)
		if (rob[counter] != NULL)
			rob[counter]->Reproduce();

	RepopulateVeggies();
	
	//Write senses
	for(counter = 0; counter<=MaxRobs; counter++)
		if (rob[counter] != NULL)
			rob[counter]->TurnEnd();

    //update cycle count
	SimOpts.TotRunCycle++;
}

void Engine_Class::ProgramInitialize(void)
{
    ReadSett("c:\\DarwinbotsII\\settings\\lastexit.set", SimOpts);
    this->maindir = "C:\\DarwinbotsII\\";

    BuildSysvars();

    //initialize the robot and shot pointer array
	for (unsigned int x = 0; x < 5000; x++)
    {
        rob[x] = NULL;
        shots[x] = NULL;
    }

	MaxRobs = -1;
    MaxShots = -1;
}

void Engine_Class::SetupSim(void)
{	
	DBsrand(800741);
	
    //Load script Lists

	SimOpts.MutCurrMult = 1;
	SimOpts.TotRunCycle = 0;
	SimOpts.TotBorn = 0;
	SimOpts.TotRunTime = 0;

	MaxRobs = -1;
    MaxShots = -1;

	this->LoadRobots();

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
    for (int x = 0; x <= MaxRobs; x++)
        if (rob[x] != NULL)
            rob[x]->ExecuteDNA();
}

void Engine_Class::ExecuteShots()
{   
	for(int counter = 0; counter <= MaxShots; counter++)
        if(shots[counter] != NULL)
            shots[counter]->UpdateShot();
}

void Engine_Class::RepopulateVeggies()
{
    static int cooldown=0;
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

    if(SimOpts.MinVegs > veggcount && cooldown <= 0)
    {
        for(unsigned int x = 0; x < SimOpts.MinVegs - veggcount; x++)
        {
            //this needs to be changed later into something that uses all species with vegs turned on
            new Robot(&SimOpts.Specie[0]);            
            SimOpts.TotVegsNow++;
        }
        cooldown = SimOpts.RepopCooldown;
    }
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
    for(int x = 0; x <= MaxRobs; x++)
        if(rob[x] != NULL && rob[x]->findAbsNum() == serial)
            return rob[x];
    
    return NULL;
}