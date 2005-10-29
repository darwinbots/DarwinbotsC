/*****************************************
Class containing all the info for robots
******************************************/
#include <iostream>
#include <vector>
#include <cmath>
#include "../Common/Math3D.h"
#include "ObjectPrimitive.h"
#include "Tie.h"
#include "Block.h"
#include "Globals.h"
#include "../Common/Random.h"
#include "Specie.h"
#include "RobotSysvars.h"
#include "SimOptions.h"
#include "Robot.h"

using namespace std;
using namespace Math3D;

vector<Robot *> rob(1000, NULL);  //an array of pointers to Robots.  Default: let's create room for 1000 pointers
unsigned int MaxRobs; //how far into the robot array to go

void FindOpenSpace(Robot *me); //finds spot for robot in array, returns pointer to said robot

inline Robot::~Robot()
{
	this->KillRobot();
}

/****************************************
Sets up a truly BASIC robot
Does not even set up color, nrg, etc.
****************************************/
void Robot::BasicRobotSetup(datispecie *myspecies)
{
	memset(this, 0, sizeof(*this)); //clear out the Robot structure
	
	SimOpts.TotBorn++;
	this->AbsNum = SimOpts.TotBorn;
	
	//set random aim
	aim = DBrand() * PI * 200;
	aimvector.set(cos(aim), sin(aim));

	this->BirthCycle = SimOpts.TotRunCycle;
	(*this)[timersys] = frnd(-32000, 32000);

	if (myspecies == NULL)
		return;


	this->Veg = myspecies->Veg;
	this->Fixed = myspecies->Fixed;

	this->fname = myspecies->Name;

	//do I need to set up *.fixed?

	this->pos.set( frnd( myspecies->PosTopLeft[0], myspecies->PosLowRight[0]) ,
				  frnd((long)myspecies->PosTopLeft[1], (long)myspecies->PosLowRight[1]), 0.0f);
	this->opos = this->pos;

	this->nrg = myspecies->nrg;
	this->Body = 1000; //default body value

	this->UpdateRadius();
	this->UpdateMass();

	this->Dead = false;
	this->Mutables = myspecies->Mutables;

	this->color = myspecies->color;
}

Robot::Robot()
{
	FindOpenSpace(this);
	this->BasicRobotSetup(NULL);
	this->SetMems();
}

Robot::Robot(datispecie *myspecies)
{
	FindOpenSpace(this);
	this->BasicRobotSetup(myspecies);
	this->SetMems();
}

void Robot::UpdateRadius()
{
	if (Body < 1)
		radius = 1;
	else
		radius = pow((Body * CUBICTWIPPERBODY * 3 / 4 / PI), 1/3);
}

//be sure to call this when a bot is created and given stuff inside it
void Robot::UpdateMass()
{
	this->mass = (this->Body / 1000) + (this->Shell / 200);
	if (this->mass < 0)
		this->mass = .00000001f;

	mem[masssys] = iceil(mass * 100);
}

void Robot::UpdateAim()
{
	float Aim;

	if (mem[SetAim] == int(this->aim*200))
	{
		Aim = this->aim * 200.0 + mem[aimsx] - mem[aimdx];
	}
	else
	{
		Aim = mem[SetAim];
	}
	
	if (Aim > 1256)
		Aim = float(int(Aim) % 1256);
	if (Aim < 0)
		Aim = Aim + 1256;

	Aim = Aim / 200;
	this->aim = Aim;
	
	aimvector.set(cos(aim), sin(aim));

	mem[aimdx] = 0;
	mem[aimsx] = 0;
	mem[Aimsys] = iceil(this->aim * 200);
	mem[SetAim] = iceil(mem[Aimsys]);
}

void Robot::UpdatePosition()
{
	float vt;
	Vector4 temp;
  
	if (mem[fixpos] > 0) Fixed = true;
	else Fixed = false;

	if (mass + AddedMass < 0.1) // a fudge since Euler approximation can't handle it when mass -> 0.
		mass = 0.1 - AddedMass; // verlet(sp?) approximation might be better, if more complicated.		 
	
	if (Fixed==false)
	{
		//Euler Approximation of velocity and position
		vel = vel + (ImpulseInd * 1/(mass + AddedMass));  //delta velocity = Impulse / mass

		vt = LengthSquared3(vel);
		if (vt > SimOpts.MaxSpeed * SimOpts.MaxSpeed)
		{
			Normalize3(vel);
			vel = vel * SimOpts.MaxSpeed;
			vt = SimOpts.MaxSpeed * SimOpts.MaxSpeed;
		}
		
		pos = pos + vel;			
	}

	if (Fixed == true || SimOpts.ZeroMomentum == true)
		vel.set(0.0f, 0.0f, 0.0f);

	ImpulseInd.set(0.0, 0.0, 0.0);
	//ForceRes
	//ForceStatic

	//clear bang commands
	mem[dirup] = 0;
	mem[dirdn] = 0;
	mem[dirdx] = 0;
	mem[dirsx] = 0;
	
	//update velocity refvars
	//these might be reversed of what they need to be, I'll need to expirement later
	mem[velscalar] = iceil(sqrt(vt));
	mem[velup] = iceil(vel * aimvector); //dot product of direction
	mem[veldn] = -mem[velup];
	mem[veldx] = iceil((vel % aimvector)); //the magnitude for a 2D vector crossed in 3D is the Z element
	mem[velsx] = -mem[veldx];

	mem[xpos] = iceil(pos.x() / 120); //returns the grid square we're in
	mem[ypos] = iceil(pos.y() / 120); //likewise

	mem[maxvelsys] = SimOpts.MaxSpeed;
	mem[fixedsys] = Fixed;
}

void Robot::MakeShell()
{
	float oldshell;
	float cost;

	oldshell = Shell;
	if (mem[mkshell] * SimOpts.Costs[SHELLCOST] > nrg && nrg > 0)
		mem[mkshell] = (nrg / 2) / SimOpts.Costs[SHELLCOST];

	Shell = Shell + mem[mkshell];
	mem[mkshell] = 0;
	if (Shell < 0)
		Shell = 0;

	mem[shellsys] = iceil(Shell);

	cost = (Shell - oldshell) * SimOpts.Costs[SHELLCOST];
	if (cost < 0)
		cost = 0;

	nrg = nrg - cost;
	Waste = Waste + cost/10;
}

void Robot::MakeSlime()
{
	float oldslime;
	float cost;

	oldslime = Slime;
	if (mem[mkslime] * SimOpts.Costs[SLIMECOST] > nrg && nrg > 0)
		mem[mkslime] = (nrg / 2) / SimOpts.Costs[SLIMECOST];

	Slime = Slime + mem[mkslime];
	mem[mkslime] = 0;
	if (Slime < 0)
		Slime = 0;

	mem[slimesys] = iceil(Slime);
	
	cost = (Slime - oldslime) * SimOpts.Costs[SLIMECOST];
	if (cost < 0)
		cost = 0;

	nrg = nrg - cost;
	Waste = Waste + cost/10;
}

void Robot::MakeVenom()
{
	float oldvenom;
	float cost;

	oldvenom = Venom;
	if (mem[mkvenom] * SimOpts.Costs[VENOMCOST] > nrg && nrg > 0)
		mem[mkvenom] = (nrg / 2) / SimOpts.Costs[VENOMCOST];

	Venom = Venom + mem[mkvenom];
	mem[mkvenom] = 0;
	if (Venom < 0)
		Venom = 0;

	mem[venomsys] = iceil(Venom);

	cost = (Venom - oldvenom) * SimOpts.Costs[VENOMCOST];
	if (cost < 0)
		cost = 0;

	nrg = nrg - cost;
	Waste = Waste + cost/10 * 1.4;  //making venom or poison produces slightly more waste
}

void Robot::MakePoison()
{
	float oldpoison;
	float cost;

	oldpoison = Poison;
	if (mem[mkpoison] * SimOpts.Costs[POISONCOST] > nrg && nrg > 0)
		mem[mkpoison] = (nrg / 2) / SimOpts.Costs[POISONCOST];

	Poison = Poison + mem[mkpoison];
	mem[mkpoison] = 0;
	if (Poison < 0)
		Poison = 0;

	mem[poison] = iceil(Poison);

	cost = (Poison - oldpoison) * SimOpts.Costs[POISONCOST];
	if (cost < 0)
		cost = 0;

	nrg = nrg - cost;
	Waste = Waste + cost/10 * 1.4;  //making venom or poison produces slightly more waste
}

void Robot::WasteManagement()
{
	if (Waste > 0 && Veg == true)
		FeedVegWaste();

	if (SimOpts.BadWasteLevel != -1 && Pwaste + Waste > SimOpts.BadWasteLevel)
	{
		//Altzheimer's
		long loops;
		loops = (Pwaste + Waste - SimOpts.BadWasteLevel) / 4;

		for (long x = 1; x < loops; x++)
		{
			if (x % 25 == 0 && DBrand() > .999) //(very small) chance of random death for large waste levels
				Dead = true;					//note that this seems really small, but .999 ^ 693 < 50%, so after
												//693 chances for death, a bot is only half likely to still be alive
			mem[frnd(1,1000)] = frnd(-32000, 32000);
		}
	}

	if (Veg == false)
	{
		Pwaste = Waste * .01f;
		Waste *= .99f;
	}		

	mem[wastesys] = iceil(Waste);
	mem[pwastesys] = iceil(Pwaste);
}

void Robot::Upkeep()
{
    //'BODY UPKEEP
    nrg = nrg - Body * SimOpts.Costs[BODYUPKEEP];
	Waste = Waste + Body/10 * SimOpts.Costs[BODYUPKEEP];
    
    //'DNA upkeep cost
    nrg = nrg - (DnaLen - 1) * SimOpts.Costs[BPCYCCOST];
	Waste = Waste + (DnaLen - 1) * SimOpts.Costs[BPCYCCOST] / 10;
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
		mem[Vloc] = Vval;
		ParaCount--;
		if (ParaCount < 1)
		{
			Paralyzed = false;
			Vloc = 0;
			Vval = 0;
		}
		mem[paralyzed] = ParaCount;   //undocumented sysvar found during C++ port
										//(PY is terribly this way.  He likes to code sysvars as straight
										//numbers instead of using constants, resulting in either subtle
										//bugs or undocumented sysvars.  There was a virus bug that fell
										//into this category.  -Numsgil
	}

	if (Poisoned == true)
	{
		mem[Ploc] = 0;
		PoisonCount--;
		if (PoisonCount < 1)
		{
			Poisoned = false;
			Ploc = 0;
		}
		mem[poisoned] = PoisonCount;
	}
}

/*Private Sub UpdateCounters(n As Integer)
  With rob(n)
    TotalRobots = TotalRobots + 1
      If .Veg Then
        totvegs = totvegs + 1
      ElseIf .Corpse Then
        totcorpse = totcorpse + 1
        Decay n
      ElseIf .Wall Then
      Else
        totnvegs = totnvegs + 1
      End If
  End With
End Sub
*/

/*****************************************************************
Function for the construction management of basic substances that
aren't directly used in metabolism.  That is, slime goes here, but
body management doesn't.  Etc.
*****************************************************************/
void Robot::Construction()
{
	if (mem[mkvenom] != 0)
		MakeVenom();
	if (mem[mkpoison] != 0)
		MakePoison();
	if (mem[mkshell] != 0)
		MakeShell();
	if (mem[mkslime] != 0)
		MakeSlime();
}

void Robot::Aging()
{
	//aging
	age++;
	
	mem[robage] = iceil(age);
	
	//epigenetic timer.  It's okay if the robot modifies this memory location,
	//we only guarentee that it'll increment each cycle and that it's value
	//will be passed to children such that they stay in sync
	
	mem[timersys]++;  //update epigenetic timer
	if (mem[timersys] > 32000)
	{
		mem[timersys] -= 32000;//once we hit 32001, wrap around to -32000
		mem[timersys] -= 32001;
	}
}

void Robot::BodyManagement()
{
	obody = Body;

	DeltaBody(mem[strbody] - mem[fdbody]);
	mem[strbody] = 0;
	mem[fdbody] = 0;
	
	if (Wall == true)
		Body = 1;
	
	mem[bodysys] = Body;
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
													 // is stuff to do it and room for the new nrg
		{
			nrg = nrg + value; //increase nrg
			Body = Body - value / 10; //decrease body
		}
	}
}

void Robot::Shock()
{
	long temp;

	temp = onrg - nrg;
	if (temp > (onrg / 2))
	{
		Body = Body + nrg / 10;
		Body = iceil(Body);
		nrg = 0;
	}
}

void Robot::DeathManagement()
{
	if (nrg > 0 && Dead == false) return; //cut out if we are still alive

	if (SimOpts.CorpseEnabled == false)
	{
		Dead = true;
	}
	else
	{
		if (Corpse == false)
		{
			Corpse = true;
			fname = "Corpse";
			//delallties
			//color = WHITE;
			//delete DNA
			//reset all occurr arrays			
			Veg = false;
			Fixed = false;
		}
		else
		{
			nrg = 0;
		}
	}

	if (Dead == true)
		this->KillRobot();
}

/*Returns false if some really really weird error is occurring*/
bool Robot::KillRobot()
{
	/*If SimOpts.DBEnable Then
    If rob(n).Veg And SimOpts.DBExcludeVegs Then
    Else
      AddRecord n
    End If
  End If
  */
  
	unsigned int counter = 0;

	//find where in the array this robot is
	while(rob[counter] != this)
	{
		counter++;
		if (rob.capacity() < counter)
		{
			return false;
		}
	}

	if (MaxRobs == counter)
	{
		MaxRobs = 0;
		for(unsigned int x = counter-1; x >= 0; x--)
		{
			if (rob[counter] != NULL)
			{
				MaxRobs = x;
				break;
			}
		}
	}

	//delete all ties
	//delete DNA
	//remember that shots may still exist that think of us as the parents
	//remove bot from any eye grid squares

	//make poff
	return true;
}

//call this very last along with the death management above
void Robot::Reproduction()
{
	if (mem[Repro] > 0 || mem[mrepro] > 0)
	{
		if (mem[Repro] >= 100)
			mem[Repro] = 99;
		if (mem[Repro] < 0)
			mem[Repro] = 0;
		
		if (mem[mrepro] >= 100)
			mem[mrepro] = 99;
		if (mem[mrepro] < 0)
			mem[mrepro] = 0;

		this->Split((mem[Repro] + mem[mrepro])/100);

		//insert DNA into child bot
		//mutate DNA in child bot
		//update sysvars etc. for new DNA
		//makeoccurrlist
	}

	//If .mem(sexrepro) > 0 Then
    //If .lastopp > 0 And rob(.lastopp).mem(sexrepro) > 0 Then
    //  rep(rp) = -n
    //  rep(rp + 1) = -.lastopp
    //  rp = rp + 2
    //End If
	//End If
}

bool Robot::FireTie()
{
	Tie *temp;
	int tieport;

	tieport = mem[mtie];

	mem[mtie] = 0;	
	if (tieport > 0 && this->lastopp != NULL && SimOpts.DisableTies == false)
	{
		temp = new Tie;

		return temp->MakeTie(this, lastopp, tieport);
	}
	return false;
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
	//NetForces <-- all the physics stuff (calculates it, but does not move the bot)
	//EraseSenses
	//readtie t 'reads all of the tref variables from a given tie number  <---  Need to be sure we do this for all bots before ties are fired
}

/************************************************************
During their turn, impulses are applied to robots' positions,
they turn, etc.
*************************************************************/
void Robot::DuringTurn()
{
	this->UpdateAim();
    this->UpdatePosition();
	//Update_Ties t ' Carries out all tie routines
}

void Robot::PostTurn()
{
	//Mutate t <--- mutating by point cycle
	//BotDNAManipulation t <--- Things like delgene, making viruses, etc.
    this->Construction();
	this->ShotManagement();
	this->BodyManagement();
	this->FireTie();
	//feed veggies
	this->UpdateRadius();
	this->UpdateMass();
}

void Robot::TurnCleanup()
{
	this->Shock();
	this->DeathManagement();
	this->Reproduction();
}

void Robot::TurnEnd()
{
	this->WriteSenses();
}

/********************************
/////////////////////////////////
********************************/

void Robot::ShotManagement()
{
	int type, value;
	float multiplier;

	value = mem[shootval] + 1;  //since a value of 1 needs to be 2 to make equations below work
	type = mem[shoot];
	
	mem[shoot] = 0;
	mem[shootval] = 0;
	
	//range is invalid for creating a shot
	if (type == 0 || type > 1000 || type < -6 || type == -5)
		return;

	//set the multiplier given the expense
	if (abs(value) >= 2) multiplier = log(abs(value)) / log(2);
	else multiplier = 1.0f;

	/////////////////////////////////////////////////////
	////   CHARGE FOR THE SHOT                       ////
	/////////////////////////////////////////////////////
	if (type == -1 || type == -6)
	{
		unsigned long cost;

		cost = (pow(2, multiplier) - 1) * SimOpts.Costs[SHOTCOST];
		if (cost <= this->nrg)
		{
			nrg = nrg - cost;
			Waste = Waste + cost / 10;
		}
		else
		{
			multiplier = log((nrg / SimOpts.Costs[SHOTCOST]) + 1) / log(2);
			nrg = 0;
			Waste = Waste + nrg / 10;
		}
	}
	else
	{
		nrg = nrg - SimOpts.Costs[SHOTCOST];
		Waste = Waste + SimOpts.Costs[SHOTCOST] / 10;
	}
	//////////////////////////////////////////////////////

	switch(type)
	{
		//basic feeding shot
		case -1:
		break;
		//give nrg shot
		case -2:
		break;
		//Venom shot
		case -3:
		break;
		//Waste Shot
		case -4:
		break;
		//Body Shot
		case -6:
		break;
		//"Info" shots
		default:
		break;
	}
}

//sharing functions go here!

//Reproduce
//basic reproduction function that mitosis and "sexRepro" will call
//function does NOT:

//1.  Copy DNA, or set any DNA related sysvars or variables
//  a.  Mutate the DNA

//returns pointer to baby, or NULL if error
Robot *Robot::Split(float percentage)
{
	long sondist;
	Robot *baby;
	float babyradius;
	float thisradius;
	float Length;
	Vector4 babypos;
	Vector4 thispos;

	//walls can't reproduce
	if( Wall == true || Corpse == true || Dead == true)
		return NULL;
	
	if (Body <= 2)
		return NULL; //too small to repro

	//insert check for too many vegs

	if (percentage < .01f)
		percentage = .01f;
	if (percentage > .99f)
		percentage = .99f;
	
	/*****************************************************************
	Check for space for baby and parent.

	this's new pos = pos0 - percentage * Length * this->aimvector
	baby's pos = this's new pos + L * this->aimvector

	where L is the final length between baby and this, = radius of baby + radius of this after birth
	pos0 is the position of the birthing bot before birth
	radius of baby = radius of birthing bot before birth * percentage^(1/3)
	radius of this after birth = radius before birth * (1.0f - percentage) ^ (1/3)
	******************************************************************/
	babyradius = this->radius * pow(percentage, (1/3));
	thisradius = this->radius * pow((1.0f - percentage), (1/3));
	Length = babyradius + thisradius;

	thispos = this->pos - percentage * Length * this->aimvector;
	babypos = thispos + Length * this->aimvector;

	//now we check for collision with other bots:
	//with both the new babypos, radius and the new thispos, radius
	//if there is a collision,
	//return false;	
		
	baby = new Robot;
	
	baby->obody = baby->Body = this->Body * percentage;
	this->obody = this->Body *= (1.0f - percentage);
	
	baby->onrg = baby->nrg = this->nrg * percentage;
	this->onrg = this->nrg *= (1.0f - percentage);
	
	baby->aim = this->aim - PI;
	if (baby->aim < 0)
		baby->aim += 2 * PI;

	baby->aimvector.set(cos(baby->aim), sin(baby->aim));
		
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

	//memcpy(baby->vars, this->vars, sizeof(var) * 50);
	//baby->vnum = this->vnum;

	baby->Mutables = this->Mutables;
	
	this->SonNumber++;
	baby->Mutations = this->Mutations;
	
	baby->parent = this->AbsNum;
	baby->generation = this->generation + 1;
	baby->LastOwner = this->LastOwner;
	baby->fname = this->fname;
	baby->LastMutDetail = this->LastMutDetail;
	
	baby->vel = this->vel;

	baby->UpdateMass();
	this->UpdateMass();

	Robot tempa;
	__int16 a;

	a = tempa[0];

	this->UpdateRadius();
	baby->UpdateRadius();

	sondist = this->radius + baby->radius;
	this->pos = this->pos - percentage * sondist * this->aimvector;
	baby->pos = this->pos + Length * this->aimvector;

	this->opos = this->pos - this->vel;
	baby->opos = baby->pos - baby->vel;

	baby->color = this->color;

	baby->mem[timersys] = this->mem[timersys];//epigenetic timer

	/*rob(nuovo).mem(468) = 32000
    rob(nuovo).mem(480) = 32000
    rob(nuovo).mem(481) = 32000
    rob(nuovo).mem(482) = 32000
    rob(nuovo).mem(483) = 32000*/
	
	//make the birth tie
	Tie *temp;
	temp = new Tie;

	temp->MakeTie(this, baby, 0);

	baby->SetMems();
	this->SetMems();

	return baby;
}

void Robot::SetMems()
{
	/********************************
	Readbacks
	********************************/
	
	this->mem[xpos] = iceil(this->pos.x()/120);
	this->mem[ypos] = iceil(this->pos.y()/120);
	
	this->mem[maxvelsys] = iceil(SimOpts.MaxSpeed);

	this->mem[masssys] = iceil(this->mass * 100);

	this->mem[velscalar] = iceil(Length3(this->vel));
	this->mem[velup] = iceil(this->vel * this->aimvector); //dot product of direction
	this->mem[veldn] = iceil(-this->mem[velup]);
	this->mem[veldx] = iceil((this->vel % this->aimvector)); //the magnitude for a 2D vector crossed in 3D is the Z element
	this->mem[velsx] = iceil(-this->mem[veldx]);

	this->mem[wastesys] = iceil(this->Waste);
	this->mem[pwastesys] = iceil(this->Pwaste);
	this->mem[poison] = iceil(this->Poison);
	this->mem[venomsys] = iceil(this->Venom);
	this->mem[paralyzed] = iceil(this->ParaCount);
	this->mem[poisoned] = iceil(this->PoisonCount);

	this->mem[bodysys] = iceil(this->Body);
	this->mem[energy] = iceil(this->nrg);
	this->mem[SetAim] = iceil(this->aim * 200.0f);
	this->mem[Aimsys] = iceil(this->mem[SetAim]);
	this->mem[fixedsys] = iceil(this->Fixed);
	this->mem[shellsys] = iceil(this->Shell);
	this->mem[slimesys] = iceil(this->Slime);
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
	if (firstopenspot > rob.capacity())
		rob.resize(rob.capacity() + 1000, NULL);
	
	rob[firstopenspot] = me;
}

//sexreproduce
