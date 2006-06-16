/*****************************************
Class containing all the info for robots
******************************************/

#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

#include "../Common/Random.h"
#include "Robot.h"
#include "Engine.h"
#include "Shots.h"
#include <fx.h>

using namespace std;

vector<Robot *> rob(5000, (Robot *)NULL);
int MaxRobs; //how far into the robot array to go

inline Robot::~Robot()
{
	this->KillRobot();
}

/****************************************
Sets up a truly BASIC robot
Does not even set up color, nrg, etc.
****************************************/
void Robot::BasicRobotSetup()
{
    SimOpts.TotBorn++;
	this->AbsNum = SimOpts.TotBorn;
	
	//set random aim
	aim = DBrand() * PI * 2;
    AngularMomentum = 0.0f;
	aimvector.set(cosf(aim), sinf(aim));

	this->BirthCycle = SimOpts.TotRunCycle;
	(*this)[timersys] = (__int16)frnd(-32000, 32000);

    this->View = false;
}

void Robot::Setup(datispecie *myspecies)
{
	this->Veg = myspecies->Veg;
    this->Fixed = myspecies->Fixed;
	
	this->fname = myspecies->Name;

	//do I need to set up *.fixed?

	this->Impulse.set(0,0,0);
    this->oldImpulse.set(0,0,0);
    this->vel.set(0,0,0);

	this->nrg = (float)myspecies->nrg;
	this->Body = (float)myspecies->body;
    if(this->Body <= 0)
        this->Body = 1000;
    
    this->color = Vector3f(float(FXREDVAL(myspecies->color))   / 255.0f,
                           float(FXGREENVAL(myspecies->color)) / 255.0f,
                           float(FXBLUEVAL(myspecies->color))  / 255.0f);    

	this->UpdateRadius();
	this->UpdateMass();

    float x = (const float)frnd(long(myspecies->PosLowRight[0] * SimOpts.FieldDimensions[0] - this->radius),
                                long(myspecies->PosTopLeft[0]  * SimOpts.FieldDimensions[0] + this->radius));

    float y = (const float)frnd(long(myspecies->PosLowRight[1] * SimOpts.FieldDimensions[1] - this->radius),
                                long(myspecies->PosTopLeft[1]  * SimOpts.FieldDimensions[1] + this->radius));
    
    this->pos.set(x, y, 0);
	this->opos = this->pos;
    
	this->Dead = false;

	//this->color = myspecies->color;

    this->DNA = new DNA_Class;
    
    string truePath(myspecies->path);
    if (truePath.substr(0,2)=="&#") //apparently, VB uses "&#" to represent app's directory
        truePath.replace(0,2,Engine.MainDir(),0,(Engine.MainDir()).length());

    this->DNA->LoadDNA(truePath + "\\" + myspecies->Name);
    this->DNA->Mutables = myspecies->Mutables;
    this->occurrList();
}

void Robot::init(datispecie *myspecies)
{
	FindOpenSpace(this);
	this->BasicRobotSetup();
	if(myspecies != NULL)
        this->Setup(myspecies);
	this->SetMems();
}

void Robot::ExecuteDNA()
{
    assert(this != NULL && "Attempting to access non existant bot's DNA in Robot::ExecuteDNA()");
    assert(this->DNA != NULL && "Attempting to access non existant DNA in Robot::ExecuteDNA()");
    this->DNA->Execute(this);
}

void Robot::UpdateRadius()
{
	if (Body < 1)
		radius = 1;
	else
		radius = powf((Body * CUBICTWIPPERBODY * 3 / 4 / PI), 1.0f / 3.0f);
}

//be sure to call this when a bot is created and given stuff inside it
void Robot::UpdateMass()
{
	this->mass = (this->Body / 1000) + (this->Shell / 200);
	
    //massless bots would wreak havoc
    if (this->mass < 0)
		this->mass = .00000001f;

	(*this)[masssys] = iceil(mass * 100);
}

//returns true if the bot is alive, false if it died
bool Robot::ChargeNRG(float amount)
{
    this->nrg = this->nrg - amount;
    this->Waste = this->Waste + amount / 10;
    
    return true;
}

void Robot::UpdateAim()
{
	float W, NewW, Aim, DeltaW;
    float Force;
    float I;
    float Cost;

	if ((*this)[SetAim] == (*this)[Aimsys])
	{
		Aim = this->aim * 200.0f + (*this)[aimleft] - (*this)[aimright];
	}
	else
	{
		Aim = (*this)[SetAim];
	}

    Aim /= 200.0f;
    
    I = this->mass * this->radius * this->radius * 2.0f/5.0f;
    W = AngularMomentum / I; //in bot angles
    
    NewW = Aim - this->aim;

    DeltaW = (NewW - W);
    DeltaW = (float)fmod(DeltaW, 2.0f * PI);
    Force = I * (float)fabs(DeltaW) / this->radius;
    Cost = Force * SimOpts.Costs[TURNCOST];
    
	Aim = (float)fmod(Aim, 2.0f * PI);
    
    if(Aim < 0)
        Aim += 2.0f * PI;

    this->aim = Aim;
    this->AngularMomentum = NewW * I;

    //I'm not sure if costs are being done right
    //for cases when it going in the oposite direction
    //would be cheaper
    if(Cost > 0)
        this->ChargeNRG(Cost);
	
	aimvector.set(cosf(aim), sinf(aim));

	(*this)[aimright] = 0;
	(*this)[aimleft] = 0;
	(*this)[Aimsys] = iceil(this->aim * 200);
	(*this)[SetAim] = iceil((*this)[Aimsys]);
}

void Robot::UpdatePosition()
{
	if ((*this)[fixpos] > 0) Fixed = true;
	else Fixed = false;
	
	if (Fixed==true)
	{
		pos = opos;
        vel.set(0,0,0);
	}

	//clear bang commands
	(*this)[dirup] = 0;
	(*this)[dirdn] = 0;
	(*this)[dirright] = 0;
	(*this)[dirleft] = 0;
	
	(*this)[velscalar] = iceil(this->vel.Length());
	(*this)[velup] = iceil(vel * aimvector); //dot product of direction
	(*this)[veldn] = -(*this)[velup];
	(*this)[veldx] = iceil((vel % aimvector)); //the magnitude for a 2D vector crossed in 3D is the Z element
	(*this)[velsx] = -(*this)[veldx];

	(*this)[xpos] = iceil(pos.x() / 120); //returns the grid square we're in
	(*this)[ypos] = iceil(pos.y() / 120); //likewise

	(*this)[maxvelsys] = SimOpts.MaxSpeed;
	(*this)[fixedsys] = Fixed;
}

void Robot::MakeShell()
{
	float oldshell;
	float cost;

	oldshell = Shell;
	if ((*this)[mkshell] * SimOpts.Costs[SHELLCOST] > nrg && nrg > 0)
		(*this)[mkshell] = iceil((nrg / 2) / SimOpts.Costs[SHELLCOST]);

	Shell = Shell + (*this)[mkshell];
	(*this)[mkshell] = 0;
	if (Shell < 0)
		Shell = 0;

	(*this)[shellsys] = iceil(Shell);

	cost = (Shell - oldshell) * SimOpts.Costs[SHELLCOST];
	if (cost < 0)
		cost = 0;
    
    this->ChargeNRG(cost);
}

void Robot::MakeSlime()
{
	float oldslime;
	float cost;

	oldslime = Slime;
	if ((*this)[mkslime] * SimOpts.Costs[SLIMECOST] > nrg && nrg > 0)
		(*this)[mkslime] = iceil((nrg / 2) / SimOpts.Costs[SLIMECOST]);

	Slime = Slime + (*this)[mkslime];
	(*this)[mkslime] = 0;
	if (Slime < 0)
		Slime = 0;

	(*this)[slimesys] = iceil(Slime);
	
	cost = (Slime - oldslime) * SimOpts.Costs[SLIMECOST];
	if (cost < 0)
		cost = 0;

	this->ChargeNRG(cost);
}

void Robot::MakeVenom()
{
	float oldvenom;
	float cost;

	oldvenom = Venom;
	if ((*this)[mkvenom] * SimOpts.Costs[VENOMCOST] > nrg && nrg > 0)
		(*this)[mkvenom] = iceil((nrg / 2) / SimOpts.Costs[VENOMCOST]);

	Venom = Venom + (*this)[mkvenom];
	(*this)[mkvenom] = 0;
	if (Venom < 0)
		Venom = 0;

	(*this)[venomsys] = iceil(Venom);

	cost = (Venom - oldvenom) * SimOpts.Costs[VENOMCOST];
	if (cost < 0)
		cost = 0;

	this->ChargeNRG(cost);
	Waste += cost/10 * 0.4f;  //making venom or poison produces slightly more waste
}

void Robot::MakePoison()
{
	float oldpoison;
	float cost;

	oldpoison = Poison;
	if ((*this)[mkpoison] * SimOpts.Costs[POISONCOST] > nrg && nrg > 0)
		(*this)[mkpoison] = iceil((nrg / 2) / SimOpts.Costs[POISONCOST]);

	Poison = Poison + (*this)[mkpoison];
	(*this)[mkpoison] = 0;
	if (Poison < 0)
		Poison = 0;

	(*this)[poison] = iceil(Poison);

	cost = (Poison - oldpoison) * SimOpts.Costs[POISONCOST];
	if (cost < 0)
		cost = 0;

	this->ChargeNRG(cost);
	Waste += cost/10.0f * 0.4f;  //making venom or poison produces slightly more waste
}

void Robot::WasteManagement()
{
	if (Waste > 0 && Veg == true)
		FeedVegWaste();

	if (SimOpts.BadWasteLevel != -1 && Pwaste + Waste > SimOpts.BadWasteLevel)
	{
		//Altzheimer's
		long loops;
		loops = long((Pwaste + Waste - SimOpts.BadWasteLevel) / 4);

		for (long x = 1; x < loops; x++)
		{
			if (x % 25 == 0 && DBrand() > .999) //(very small) chance of random death for large waste levels
				Dead = true;					//note that this seems really small, but .999 ^ 693 < 50%, so after
												//693 chances for death, a bot is only half likely to still be alive
			(*this)[(int)frnd(1,1000)] = (__int16)frnd(-32000, 32000);
		}
	}

	if (Veg == false)
	{
		Pwaste = Waste * .01f;
		Waste *= .99f;
	}		

	(*this)[wastesys] = iceil(Waste);
	(*this)[pwastesys] = iceil(Pwaste);
}

void Robot::Upkeep()
{
    //'BODY UPKEEP
    this->ChargeNRG(Body * SimOpts.Costs[BODYUPKEEP]);
    
    //'DNA upkeep cost
    if(this->DNA != NULL)
        this->ChargeNRG(this->DNA->length() * SimOpts.Costs[BPCYCCOST]);
}

/*
Robot::GeneLength()
{


}*/

/*Robot::DNAManipulation()
{


}*/

void Robot::PoisonManagement()
{
	//Paralyzed means venomized

	if (Paralyzed == true)
	{
		(*this)[Vloc] = Vval;
		ParaCount--;
		if (ParaCount < 1)
		{
			Paralyzed = false;
			Vloc = 0;
			Vval = 0;
		}
		(*this)[paralyzed] = iceil(ParaCount);   //undocumented sysvar found during C++ port
	}

	if (Poisoned == true)
	{
		(*this)[Ploc] = 0;
		PoisonCount--;
		if (PoisonCount < 1)
		{
			Poisoned = false;
			Ploc = 0;
		}
		(*this)[poisoned] = iceil(PoisonCount);
	}
}

/*****************************************************************
Function for the construction management of basic substances that
aren't directly used in metabolism.  That is, slime goes here, but
body management doesn't.  Etc.
*****************************************************************/
void Robot::Construction()
{
	if ((*this)[mkvenom] != 0)
		MakeVenom();
	if ((*this)[mkpoison] != 0)
		MakePoison();
	if ((*this)[mkshell] != 0)
		MakeShell();
	if ((*this)[mkslime] != 0)
		MakeSlime();
}

void Robot::Aging()
{
	//aging
	age++;
	
	(*this)[robage] = iceil(float(age));
	
	//epigenetic timer.  It's okay if the robot modifies this memory location,
	//we only guarentee that it'll increment each cycle and that it's value
	//will be passed to children such that they stay in sync
	
	(*this)[timersys]++;  //update epigenetic timer
	if ((*this)[timersys] > 32000)
	{
		(*this)[timersys] -= 32000;//once we hit 32001, wrap around to -32000
		(*this)[timersys] -= 32001;
	}
}

void Robot::BodyManagement()
{
	obody = Body;

	DeltaBody((*this)[strbody] - (*this)[fdbody]);
	(*this)[strbody] = 0;
	(*this)[fdbody] = 0;
	
	if (Wall == true)
		Body = 1;
	
	(*this)[bodysys] = iceil(Body);
	UpdateRadius();
}

void Robot::DeltaBody(int value)
{
	//only 100 nrg can be spent/gained at a time max
	
	if (abs(value) > 100)
		value = 100 * value / abs(value);

	if (value > 0 && nrg > value && Body + value/10 <= 32000) //increase body points
	{
        nrg = nrg - value;
		Body = Body + value / 10;  //10 nrg = 1 body
	}

	if (value < 0)
	{
		value = abs(value);
		if(Body > value * 10 && nrg + value <= 32000)//decrease body points only if there
													 //is stuff to do it and room for the new nrg
		{
			nrg = nrg + value; //increase nrg
			Body = Body - value / 10; //decrease body
		}
	}
}

void Robot::Shock()
{
	long temp;

	temp = long(this->onrg - this->nrg);
	if (temp > (onrg / 2) )
	{
		Body = Body + nrg / 10;
		Body = iceil(Body);
		nrg = 0;
	}
}

//returns if we are still alive or not
bool Robot::DeathManagement()
{
	if (nrg > 0 && Body > 0 && Dead == false) return true; //cut out if we are still alive

	if (SimOpts.CorpseEnabled == false)
	{
		Dead = true;
	}
	else
	{
		if (Corpse == false && Body > 0)
		{
			Corpse = true;
			fname = "Corpse";
			RemoveAllTies();
			this->color.set(1,1,1); //corpses are white
            if(this->DNA != NULL)
            {
                delete this->DNA;
                this->DNA = NULL;
            }

            this->occurrList();
            memset(this->occurr, 0, sizeof(this->occurr));
			Veg = false;
			Fixed = false;
		}
		else
		{
			nrg = 0;
		}

        if (Body <= 0)
        {
            Dead = true;
        }
	}

	if (Dead == true)
	{
    	this->KillRobot();
        return false;
    }

    return true;    
}

/*Returns false if some really really weird error is occurring*/
bool Robot::KillRobot()
{
	assert(this != NULL && "Trying to kill an already dead bot");
    
	int counter = 0;
    
	//find where in the array this robot is
	while(rob[counter] != this && counter <= MaxRobs)
	    counter++;
    
    if (counter > MaxRobs)
        return false;
    
	if (MaxRobs == counter)
	{
		MaxRobs = -1;
		for(int x = counter-1; x >= 0; x--)
		{
			if (rob[x] != NULL)
			{
				MaxRobs = x;
				break;
			}
		}
	}

    for(int x = 0; x <= MaxRobs; x++)
        if(rob[x] && rob[x]->lastopp == this)
            rob[x]->lastopp = NULL;
    
    if (this->DNA != NULL)
    {
        delete this->DNA;
        this->DNA = NULL;
    }
    rob[counter] = NULL;
    
	RemoveAllTies();
    Engine.EyeGridRemoveDeadBot(this);
	
    //remember that shots may still exist that think of us as the parents
	//make poff

    delete this;
    
    return true;
}

//call this very last along with the death management above
void Robot::Reproduction()
{
	Robot *baby=NULL;
    float mutmult, costmult;
    assert(!this->Corpse && "Corpse attempting to reproduce");
    assert(this != NULL && "Non existant bot trying to reproduce");
    
    if ((*this)[Repro] > 0)
	{
		if ((*this)[Repro] >= 100)
			(*this)[Repro] = 99;
		
        if((*this)[mrepro] == 0)
        {
            mutmult = 1;
            costmult = 1;
        }
        else if((*this)[mrepro] < 0)
        {
            costmult = 1.0f + abs((*this)[mrepro]) / 100;
            mutmult = float (log(35000.0 / fabs((double)(*this)[mrepro])) / log(2.0) / 15.1);
        }
        else
        {
            mutmult = 1.0f + abs((*this)[mrepro]) / 100;
            costmult = float (log(35000.0 / fabs((double)(*this)[mrepro])) / log(2.0) / 15.1);
        }
        
        float percentage = (*this)[Repro]/100.0f;
        if (this->nrg > SimOpts.Costs[BPCOPYCOST] * (float)this->DNA->length() * costmult)
        {
            baby = this->Split(percentage);
            if (baby != NULL)
            {
                assert(this->DNA != NULL && "Bot with no DNA trying to reproduce");
                baby->DNA = new DNA_Class((*this->DNA));
                baby->occurrList();
                //still need to program code for mrepro
                baby->DNA->Mutate(true, mutmult);
                baby->occurrList();
                this->ChargeNRG(SimOpts.Costs[BPCOPYCOST] * (float)this->DNA->length() * (1 - percentage) * costmult);
                baby->ChargeNRG(SimOpts.Costs[BPCOPYCOST] * (float)this->DNA->length() * percentage * costmult);
                (*this)[Repro] = 0;
            }            
        }    
    }
}
    

/********************************
/////////////////////////////////
********************************/
//6 Turn phases.
//We cannot combine them any more, this is the best way to keep it all working right

//these functions MUST go before all others, -and-
//these functions CANNOT interact in anyway
void Robot::TurnGenesis()
{
    //tieportcom t 'transfer data through ties
}

void Robot::PreTurn()
{
	this->WasteManagement();
	this->Upkeep();
	this->Aging();
    this->NetForces(); //<-- all the physics stuff (calculates it, but does not move the bot)
	this->EraseSenses();
	//readtie t 'reads all of the tref variables from a given tie number  <---  Need to be sure we do this for all bots before ties are fired
}

void Robot::DuringTurn()
{
	this->UpdateAim();
    this->UpdatePosition();
	this->UpdateTies(); //Carries out all tie routines (but not physics)
}

void Robot::PostTurn()
{
	if(this->DNA != NULL)
        this->DNA->Mutate(false); //<--- mutating by point cycle
	//this->BotDNAManipulation t <--- Things like delgene, making viruses, etc.
    this->Construction();
	this->ShotManagement();
	this->BodyManagement();
	this->FireTie();
    this->FeedVegSun();
	this->UpdateRadius();
	this->UpdateMass();
}

void Robot::TurnCleanup()
{
	this->Shock();
	this->DeathManagement();        
}

void Robot::Reproduce()
{
    assert(this != NULL && "Non existant bot attempting to replicate");
    if(!this->Corpse)
        this->Reproduction();
}

void Robot::CheckVision()
{
    //this->BasicProximity(); //O(n^2)
    assert(this != NULL && "Non existant bot checking vision");
    this->EyeGridProximity(); //Uses uniform grids to achieve a (supposed) O(n)
}

void Robot::TurnEnd()
{
    this->WriteSenses();
}

/********************************
/////////////////////////////////
********************************/

//sharing functions go here!

//Reproduce
//basic reproduction function that mitosis and "sexRepro" will call
//function does NOT:

//1.  Copy DNA, or set any DNA related sysvars or variables
//  a.  Mutate the DNA

//returns pointer to baby, or NULL if error
Robot* Robot::Split(float percentage)
{
	long sondist;
	Vector3f babypos;
	Vector3f thispos;

	if( Wall == true || Corpse == true || Dead == true)
		return NULL;
	
	if (Body <= 2)
		return NULL; //too small to repro (this prevents effects of cancer from being so totally
                     //debilitating to game speed

	//insert check for too many vegs

	if (percentage < .01f)
		percentage = .01f;
	if (percentage > .99f)
		percentage = .99f;
	
	Robot *baby = new Robot();
	
	baby->obody = baby->Body = this->Body * percentage;
	this->obody = this->Body = this->Body * (1.0f - percentage);
	
	baby->onrg = baby->nrg = this->nrg * percentage;
	this->onrg = this->nrg = this->nrg * (1.0f - percentage);
	
	baby->aim = this->aim - PI;
    baby->AngularMomentum = 0;
    if (baby->aim < 0)
		baby->aim += 2 * PI;

	baby->aimvector.set(cosf(baby->aim), sinf(baby->aim));
		
	baby->Veg = this->Veg;
	baby->Fixed = this->Fixed;
	
	baby->Shell = baby->Shell = this->Shell * percentage;
	this->Shell = this->Shell *= (1.0f - percentage);
	
	baby->Slime = baby->Slime = this->Slime * percentage;
	this->Slime = this->Slime *= (1.0f - percentage);

	baby->Waste = baby->Waste = this->Waste * percentage;
	this->Waste = this->Waste *= (1.0f - percentage);

	baby->Pwaste = baby->Pwaste = this->Pwaste * percentage;
	this->Pwaste = this->Pwaste *= (1.0f - percentage);

	baby->Poison = baby->Poison = this->Poison * percentage;
	this->Poison = this->Poison *= (1.0f - percentage);

	baby->Venom = baby->Venom = this->Venom * percentage;
	this->Venom = this->Venom *= (1.0f - percentage);

	baby->Paralyzed = this->Paralyzed;
	baby->ParaCount = baby->ParaCount = this->ParaCount * percentage;
	this->ParaCount = this->ParaCount *= (1.0f - percentage);
	baby->Vloc = this->Vloc;
	baby->Vval = this->Vval;

	baby->Poisoned = this->Poisoned;
	baby->Ploc = this->Ploc;
	baby->PoisonCount = baby->PoisonCount = this->PoisonCount * percentage;
	this->PoisonCount = this->PoisonCount *= (1.0f - percentage);

	this->SonNumber++;
	
    baby->parent = this->AbsNum;
	baby->generation = this->generation + 1;
	baby->LastOwner = this->LastOwner;
	baby->fname = this->fname;
	
	baby->UpdateMass();
	this->UpdateMass();

	this->UpdateRadius();
	baby->UpdateRadius();

	sondist = long(this->radius + baby->radius);
	Vector3f vel = this->pos - this->opos;
    
    this->pos = this->pos - percentage * sondist * this->aimvector;
	baby->pos = this->pos + float(sondist) * this->aimvector;

	this->opos = this->pos - vel;
	baby->opos = baby->pos - vel;

    baby->vel = this->vel;
    baby->oldImpulse.set(0,0,0);
    baby->Impulse.set(0,0,0);
    baby->ImpulseStatic = 0.0f;
    
	baby->color = this->color;

	(*baby)[timersys] = (*this)[timersys];//epigenetic timer

	//make the birth tie
	//Tie::MakeTie(this, baby, -1);

    baby->fname = this->fname;

	baby->SetMems();
	this->SetMems();
    
    return baby;
}

void Robot::SetMems()
{
	/********************************
	Readbacks
	********************************/
	
	(*this)[xpos] = iceil(this->pos.x()/120);
	(*this)[ypos] = iceil(this->pos.y()/120);
	
	(*this)[maxvelsys] = iceil(float(SimOpts.MaxSpeed));

	(*this)[masssys] = iceil(this->mass * 100);

	Vector3f vel = this->pos - this->opos;
    (*this)[velscalar] = iceil(vel.Length());
	(*this)[velup] = iceil(vel * this->aimvector); //dot product of direction
	(*this)[veldn] = -(*this)[velup];
	(*this)[veldx] = iceil(vel % this->aimvector); //the magnitude for a 2D vector crossed in 3D is the Z element
	(*this)[velsx] = -(*this)[veldx];

	(*this)[wastesys] = iceil(this->Waste);
	(*this)[pwastesys] = iceil(this->Pwaste);
	(*this)[poison] = iceil(this->Poison);
	(*this)[venomsys] = iceil(this->Venom);
	(*this)[paralyzed] = iceil(this->ParaCount);
	(*this)[poisoned] = iceil(this->PoisonCount);

	(*this)[bodysys] = iceil(this->Body);
	(*this)[energy] = iceil(this->nrg);
	(*this)[SetAim] = iceil(this->aim * 200.0f);
	(*this)[Aimsys] = (*this)[SetAim];
	(*this)[fixedsys] = iceil(this->Fixed);
	(*this)[shellsys] = iceil(this->Shell);
	(*this)[slimesys] = iceil(this->Slime);
}

//sexreproduce
