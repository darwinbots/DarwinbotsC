#include <direct.h>
#include <time.h>

#include <fstream>

#include "SimOptions.h"
#include "HardDriveRoutines.h"
#include "Shot.h"
#include "Block.h"

#include "Engine.h"

Simulation Engine;

Simulation::Simulation():robotList(new RobotList),shotList(new ShotList)
{
    char buffer[1024];
    this->mainDir = getcwd(buffer, 1024);
    ReadSett(this->mainDir + "\\settings\\lastexit.set", SimOpts);

    parser.buildSysvars(this->mainDir+"/sysvars2.5.txt");

    SetDNAMutationsBounds();
}

void Simulation::setup()
{
	if(SimOpts.UserSeedToggle)
        DBsrand(SimOpts.UserSeedNumber);
    else
        DBsrand((long)time(NULL));

    //Load script Lists

	SimOpts.MutCurrMult = 1;
	SimOpts.TotRunCycle = 0;
	SimOpts.TotBorn = 0;
	SimOpts.TotRunTime = 0;

	this->LoadRobots();

    EyeGrid.Setup(Vector3i(int(SimOpts.FieldDimensions.x() / GRID_DIM),
                           int(SimOpts.FieldDimensions.y() / GRID_DIM),
                           int(SimOpts.FieldDimensions.z() / GRID_DIM)) + Vector3i(1,1));

	//initalize the upload/download boxes for internet sharing

	//initialize F1 contest mode

	//initialize league mode

}

void Simulation::LoadRobots(void)
{
    DNA_Class* speciesDna;
    string truePath;
    for (unsigned int y = 0; y < SimOpts.SpeciesNum; y++)
    {
        truePath = SimOpts.Specie[y].path;
        if (truePath.substr(0,2)=="&#") //apparently, VB uses "&#" to represent app's directory
            truePath.replace(0,2,MainDir(),0,MainDir().length());
        truePath += "\\" + SimOpts.Specie[y].Name;
        speciesDna = new DNA_Class(parser.loadFile(truePath));
        for (unsigned int x = 0; x < SimOpts.Specie[y].qty; x++)
            robotList->push_back(new Robot(&parser,&SimOpts.Specie[y],speciesDna));
        delete speciesDna;
    }
}



void Simulation::UpdateSim(void)
{
    //std::cout<<"Turn "<<SimOpts.TotRunCycle<<":";
    //the order of functions here is very important. Don't idly add or (re)move
    //functions without _really_ thinking about how it changes the order of
    //other functions.

    this->ExecuteDNA();  //O(n)
    this->ExecuteShots(); //Checks every shot against every bot O(mn)

    ////////////////////
	//UpdateBots
	////////////////////
	RobotIterator currBot;
	//update counters

	//Before anything else...
	/* does nothing...
	for (currBot = robotList->begin(), currBot != robotList->end(), ++currBot)
	   *currBot->TurnGenesis();*/

	for (currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
	   (*currBot)->PreTurn();

	//Physics Steps:
    for (currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
	   (*currBot)->Integrate();

    //CONSTRAINTS (done after movement)

    //max tie length and rigid ties (if ties are hardened)

    for (currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
	   (*currBot)->VelocityCap();

    handleBotCollisions();

    for (currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
	    ManipulateEyeGrid(*currBot);

    //END CONSTRAINTS
    //END Physics steps
    //std::cout<<" phys,";
    for (currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
        (*currBot)->DuringTurn();

    //"PostTurn" phase
	for (currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
	{
        assert((*currBot)->dna!=NULL);
        (*currBot)->dna->Mutate(false); //<--- mutating by point cycle
        //this->BotDNAManipulation t <--- Things like delgene, making viruses, etc.
        (*currBot)->Construction();
        if ((*currBot)->isShooting())
            createShot(*currBot);
        (*currBot)->BodyManagement();
        (*currBot)->FireTie();
        (*currBot)->FeedVegSun();
        (*currBot)->UpdateRadius();
        (*currBot)->UpdateMass();
	}

    //Cleanup phase
    currBot = robotList->begin();
	while (currBot != robotList->end())
    {
        (*currBot)->Shock();
        if(!(*currBot)->DeathManagement())
            currBot=killBot(currBot);
        else
            ++currBot;
    }

    RobotList tempList;
    for (currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
    {
        if ((*currBot)->isReproducing())
            tempList.push_back((*currBot)->makeBaby());
    }
    robotList->splice(robotList->end(), tempList); //Merges the temporary list at the end
    //std::cout<<" repro,";
	RepopulateVeggies();

    for (currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
        (*currBot)->CheckVision();

	//Write senses
	for (currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
        (*currBot)->TurnEnd();

    //update cycle count
	++SimOpts.TotRunCycle;
	//std::cout<<" end."<<std::endl;
    //std::cout<<"Bot 105 has "<<getRobot(105)->nrg <<" energy at turn "<<SimOpts.TotRunCycle<<std::endl;
}



void Simulation::ExecuteDNA()
{
    RobotIterator currBot;
    for (currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
        (*currBot)->ExecuteDNA();

    /*for (currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
        for(TieList::iterator tie= (*currBot)->Ties.begin(); tie != (*currBot)->Ties.end(); ++tie)
            (*tie)->ApplyCQ(); //Apply the Command Queue

    for (currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
        (*currBot)->DNACommands.Apply();*/
}

void Simulation::ExecuteShots()
{
    ShotIterator shot;
    for (shot = shotList->begin(); shot != shotList->end(); ++shot)
    {
        assert(*shot != NULL);
        (*shot)->UpdatePos();
    }

    //Since returned shots are added at the end of shotList, they're also
    //checked by this loop.
// FIXME (Ronan#1#): Need to handle correctly returned shots on the turn they're created
    shot = shotList->begin();
	while (shot != shotList->end())
	{
	    if ((*shot)->isTooOld())
	    {
	        shot = killShot(shot);
	        continue;
	    }
	    Robot* target = (*shot)->ShotColl();
	    if (target != NULL)
	    {
// FIXME (Ronan#1#): Should clear shots when new bot is born instead
	        if (target->parent == (*shot)->parent && target->age == 0)
	        {
	            shot = killShot(shot); //baby bots immune to parents' shots at first
                continue;
            }
            const float power=(*shot)->hit(target);
            if((*shot)->bouncesOff(target, power))
                shotList->push_back((*shot)->returnShot(target, power));
            shot = killShot(shot);
            /*(*shot)->reflect(target);
            (*shot)->collide(target);*/
	    }
	    else
            ++shot;
	}
}

int cooldown = 0;
void Simulation::RepopulateVeggies()
{
    vector<int> VegSpeciesList;
    unsigned long veggcount=0;
    unsigned long notveggcount=0;

    for (RobotIterator currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
    {
        if((*currBot)->Veg)
            veggcount++;
        else
            notveggcount++;
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
            unsigned int spec = frnd(0, VegSpeciesList.size() - 1);
            std::string truePath = SimOpts.Specie[spec].path;
            if (truePath.substr(0,2)=="&#") //apparently, VB uses "&#" to represent app's directory
                truePath.replace(0,2,MainDir(),0,MainDir().length());
            truePath += "\\" + SimOpts.Specie[spec].Name;
            DNA_Class speciesDna = parser.loadFile(truePath);

            robotList->push_back(new Robot(&parser, &SimOpts.Specie[spec], &speciesDna));
            SimOpts.TotVegsNow++;
        }
        cooldown = SimOpts.RepopCooldown;
    }
}

void Simulation::ManipulateEyeGrid(Robot *bot)
{
    EyeGrid.Move(bot);
}

void Simulation::WhatCanSeeMe(Robot *me, list<Robot *> &BotList)
{
    EyeGrid.WhatCanSeeMe(me, BotList);
};

//find a robot with this serial number or return NULL
Robot* Simulation::getRobot(unsigned long serial) const
{
    for (RobotIterator currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
        if((*currBot)->getAbsNum() == serial)
            return *currBot;

    return NULL;
}

//sets a hard constraint that pulls bots that are too close to each other apart
//changes by angelo
float Simulation::BotCollisionsPos(Robot* bot)
{
    float maxoverlap = 0.0f;
    bool collide = false;
    for (RobotIterator otherBot = robotList->begin(); otherBot != robotList->end(); ++otherBot)
    {
        if((*otherBot)->absNum != bot->absNum) //if i'm a robot, consider me
        {
            Vector3f normal = (*otherBot)->pos - bot->pos;

            float mindist = bot->radius + (*otherBot)->radius;
            if(abs(normal.x())>mindist || abs(normal.y())>mindist) //Square test
                continue;
            mindist *= mindist;

            float currdist = normal.LengthSquared();

            //Circle test
            //The +1 is a fudge factor for floating point inaccuracies
            if(currdist + 1 < mindist) //bots colliding...activate both bots
            {
                collide = true;
                (*otherBot)->CollisionActive = true;
				bot->CollisionActive = true;

                if(currdist < 1)
                {
                    currdist = 1;
                    normal.set(0, 1);
                }

                float overlap = sqrtf(mindist / currdist) - 1.0f;

                //this below would be faster if we didn't do more than one iteration of position collision a cycle
                //float overlap = (mindist) / (currdist + mindist) - 0.5f;

                if(overlap > maxoverlap)
                    maxoverlap = overlap;

                //UPDATE POSITIONS
                normal *= overlap;

                //these need to be modified to deal with
                //fixed/unfixed pairs
                (*otherBot)->pos += normal * 0.5f;
                bot->pos -= normal * 0.5f;
            }
        }
    }

    if(collide == false)
        bot->CollisionActive = false;

    return maxoverlap;
}

//More iterations decreases overlap between bots when stacking, but
//it hardly seems practical.  A better solution must exist, which
//more intelligently offsets colliding bots.
//O(n^2)
void Simulation::handleBotCollisions()
{
    float maxoverlap = 0.0f;
    int loopcounter = 0;

    bool Continue = false;
    RobotIterator currBot;
    do
    {
        Continue = false;
        for (currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
        {
            if ((*currBot)->CollisionActive)
			{
				float overlap = BotCollisionsPos(*currBot);

				maxoverlap = max(maxoverlap, overlap);
			}
        }

        for (currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
	       (*currBot)->EdgeCollisions();

        unsigned int activecounter = 0;
        for (currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
        {
            if((*currBot)->CollisionActive)
            {
                activecounter++;
                Continue = true;
            }
        }

        //cout << activecounter << endl;

        //loopcounter++;

    }while(Continue);

}

void Simulation::getRobotDisplayList(std::vector<SolidPrimitive>& displayList) const
{
    displayList.clear();
    for (RobotIterator currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
    {
        assert(*currBot!=NULL && "bla");
        displayList.push_back(**currBot);
    }
}

void Simulation::getShotDisplayList(ShotList& displayList) const
{
    for (ShotIterator currShot = displayList.begin(); currShot != displayList.end(); ++currShot)
        delete *currShot;
    displayList.clear();
    for (ShotIterator currShot = shotList->begin(); currShot != shotList->end(); ++currShot)
    {
        displayList.push_back((*currShot)->clone());
    }
}

//Clears the sim, though it'd be better to destroy it.
void Simulation::clear()
{
    for (RobotIterator currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
        delete *currBot;
    robotList->clear();
    for (ShotIterator currShot = shotList->begin(); currShot != shotList->end(); ++currShot)
        delete *currShot;
    shotList->clear();
}

void Simulation::createShot(Robot* parent)
{
    shotList->push_back(parent->makeShot());
}

ShotIterator Simulation::killShot(ShotIterator shot)
{
    delete *shot;
    return shotList->erase(shot);
}

RobotIterator Simulation::killBot(RobotIterator currBot)
{
    assert(*currBot != NULL && "Trying to kill an already dead bot");
    for (RobotIterator otherBot = robotList->begin(); otherBot != robotList->end(); ++otherBot)
        if((*otherBot)->lastopp == *currBot)
            (*otherBot)->lastopp = NULL;
    EyeGrid.Remove(*currBot, Vector3i(int((*currBot)->getOldPos().x() / GRID_DIM),
                                      int((*currBot)->getOldPos().y() / GRID_DIM),
                                      int((*currBot)->getOldPos().z() / GRID_DIM)));
    delete *currBot;
    currBot = robotList->erase(currBot);

}

std::string Simulation::getDnaText(unsigned long serial) const
{
    Robot* bot = getRobot(serial);
    if (bot != NULL)
        return parser.getText(*(bot->dna));
    else
        return std::string();
}
