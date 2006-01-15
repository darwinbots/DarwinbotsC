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

using namespace std;
using namespace Math3D;

Robot *rob[5000];     // (1000, NULL);  //an array of pointers to Robots.  Default: let's create room for 1000 pointers
unsigned int MaxRobs; //how far into the robot array to go

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
    //I find mixed answers as to how valid memsetting a new structure to 0 is.
    //barring any problems, or an easier, more correct way to do the below that's not setting each
    //field manually, I'd like continue to do it this way.
    
    //DO NOT NOT NOT NOT NOT NOT NOT NOT NOT NOT NOT NOT NOT NOT NOT NOT NOT!
    //get rid of this memset UNLESS you find some other way to initialize all the variables to
    //all 0 bits.  DO NOT!  DON'T EVEN THINK IT!
    //I'M WARNING YOU!
    
    memset(this, 0, sizeof(*this)); //clear out the Robot structure

	SimOpts.TotBorn++;
	this->AbsNum = SimOpts.TotBorn;
	
	//set random aim
	aim = DBrand() * PI * 200;
	aimvector.set(cos(aim), sin(aim));

	this->BirthCycle = SimOpts.TotRunCycle;
	(*this)[timersys] = frnd(-32000, 32000);

    this->View = false;

	if (myspecies == NULL)
		return;

	this->Veg = myspecies->Veg;
	this->Fixed = myspecies->Fixed;

	this->fname = myspecies->Name;

	//do I need to set up *.fixed?

	this->pos.set( frnd((long)myspecies->PosTopLeft[0], (long)myspecies->PosLowRight[0]) ,
				  frnd((long)myspecies->PosTopLeft[1], (long)myspecies->PosLowRight[1]), 0.0f);
	this->opos = this->pos;

	this->nrg = myspecies->nrg;
	this->Body = 1000; //default body value

	this->UpdateRadius();
	this->UpdateMass();

	this->Dead = false;

	this->color = myspecies->color;

    this->DNA = new DNA_Class;
    
    string truePath(myspecies->path);
    if (truePath.substr(0,2)=="&#") //apparently, vB uses "&#" to represent app's directory
      truePath.replace(0,2,Engine.MainDir(),0,(Engine.MainDir()).length());

    this->DNA->LoadDNA(truePath + "\\" + myspecies->Name);
    this->DNA->Mutables = myspecies->Mutables;
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
		radius = pow((Body * CUBICTWIPPERBODY * 3 / 4 / PI), .3333333333333333f);
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
    
    //conceptually it needs to be checked if killing a bot during the turn
    //instead of at the end isn't fair to the bot
    /*if (this->nrg < 0)
    {
        this->nrg = 0;
        this->Dead = true;
        return false;
    }*/

    return true;
}

void Robot::UpdateAim()
{
	float Aim;

	if ((*this)[SetAim] == (*this)[Aimsys])
	{
		Aim = this->aim * 200.0 + (*this)[aimsx] - (*this)[aimdx];
	}
	else
	{
		Aim = (*this)[SetAim];
	}
	
	if (Aim > 1256)
		Aim = float(int(Aim) % 1256);
	if (Aim < 0)
		Aim = Aim + 1256;

	Aim = Aim / 200;
	this->aim = Aim;
	
	aimvector.set(cos(aim), sin(aim));

	(*this)[aimdx] = 0;
	(*this)[aimsx] = 0;
	(*this)[Aimsys] = iceil(this->aim * 200);
	(*this)[SetAim] = iceil((*this)[Aimsys]);
}

void Robot::UpdatePosition()
{
	float vt;
	Vector4 temp;
  
	if ((*this)[fixpos] > 0) Fixed = true;
	else Fixed = false;

	if (mass + AddedMass < 0.1) // a fudge since Euler approximation can't handle it when mass -> 0.
		mass = 0.1 - AddedMass; // verlet(sp?) approximation might be better, if more complicated.		 
	
	if (Fixed==false)
	{
		//verlet scheme:

        Vector4 temp = pos;
        pos = pos * 2 - opos + ImpulseInd / (mass + AddedMass);
        opos = temp;

        /*Vector4 vel = opos - pos;
        vt = LengthSquared3(vel);
        SimOpts.MaxSpeed = 60;
		if (vt > SimOpts.MaxSpeed * SimOpts.MaxSpeed)
		{
			vel = vel / sqrt(vt);
			vel = vel * SimOpts.MaxSpeed;
			vt = SimOpts.MaxSpeed * SimOpts.MaxSpeed;
		}*/
	}

	if (Fixed == true || SimOpts.ZeroMomentum == true)
		vel.set(0.0f, 0.0f, 0.0f);

	ImpulseInd.set(0.0, 0.0, 0.0);
	//ForceRes
	//ForceStatic

	//clear bang commands
	(*this)[dirup] = 0;
	(*this)[dirdn] = 0;
	(*this)[dirdx] = 0;
	(*this)[dirsx] = 0;
	
	//update velocity refvars
	//these might be reversed of what they need to be, I'll need to expirement later
	(*this)[velscalar] = iceil(sqrt(vt));
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
	Waste += cost/10 * 0.4;  //making venom or poison produces slightly more waste
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
	Waste += cost/10 * 0.4;  //making venom or poison produces slightly more waste
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
			(*this)[frnd(1,1000)] = frnd(-32000, 32000);
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
	
	(*this)[robage] = iceil(age);
	
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

	temp = long(this->onrg - this->nrg);
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
			removeAllTies();
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

    if (this == NULL)
        return false;
  
	unsigned int counter = 0;

	//find where in the array this robot is
	while(rob[counter] != this && counter <= MaxRobs)
	    counter++;

    if (counter > MaxRobs)
        return false;

	if (MaxRobs == counter)
	{
		MaxRobs = 0;
		for(unsigned int x = counter-1; x >= 0; x--)
		{
			if (rob[x] != NULL)
			{
				MaxRobs = x;
				break;
			}
		}
	}
    
    if (this->DNA != NULL)
    {
        delete this->DNA;
        this->DNA = NULL;
    }
    rob[counter] = NULL;
    
	removeAllTies();
	
    //remember that shots may still exist that think of us as the parents
	//make poff
    
    return true;
}

//call this very last along with the death management above
void Robot::Reproduction()
{
	Robot *baby=NULL;
    
    if ((*this)[Repro] > 0 || (*this)[mrepro] > 0)
	{
		if ((*this)[Repro] >= 100)
			(*this)[Repro] = 99;
		if ((*this)[Repro] < 0)
			(*this)[Repro] = 0;
		
		if ((*this)[mrepro] >= 100)
			(*this)[mrepro] = 99;
		if ((*this)[mrepro] < 0)
			(*this)[mrepro] = 0;
        
        if ( (*this)[Repro] + (*this)[mrepro] > 0)
        {
            baby = this->Split( ( (*this)[Repro] + (*this)[mrepro] )/100.0f);
            if (baby != NULL)
            {
                baby->DNA = new DNA_Class((*this->DNA));
                baby->DNA->Mutables = this->DNA->Mutables;
                baby->DNA->Mutations = this->DNA->Mutations;
                baby->DNA->LastMutDetail = this->DNA->LastMutDetail;

                //mutate DNA
		        //mutate DNA in child bot
		        //update sysvars etc. for new DNA
		        //makeoccurrlist
            }
            (*this)[Repro] = 0;
            (*this)[mrepro] = 0;
        }    
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
	int tieport = (*this)[mtie];

	(*this)[mtie] = 0;	
	if (tieport > 0 && this->lastopp != NULL && SimOpts.DisableTies == false)
	{
		return Tie::MakeTie(this, lastopp, tieport);
	}
	return false;
}

bool Robot::canTie()
{
    return !Corpse && this != NULL;
};

void Robot::addTie(Tie *tie)
{
    if(!this->Ties)
        Ties = new TieList;

    this->Ties->push_back(tie);
}
    
void Robot::removeTie(Tie* tie)
{
    delete tie; //the Tie's destructor takes care of the tieLists
}

void Robot::removeAllTies()
{
    //while(!this->tieList.empty())
    //    removeTie(tieList.begin());
    
    
    if (Ties != NULL && !Ties->empty())
    {
        TieList::iterator iter;
        for(iter=Ties->begin(); iter!=Ties->end(); ++iter)
            {removeTie(*iter);}
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

/************************************************************
During their turn, impulses are applied to robots' positions,
they turn, etc.
*************************************************************/
void Robot::DuringTurn()
{
	this->UpdateAim();
    this->UpdatePosition();
	//Update_Ties t ' Carries out all tie routines (but not physics)
}

void Robot::PostTurn()
{
	this->DNA->Mutate(false); //<--- mutating by point cycle
	//BotDNAManipulation t <--- Things like delgene, making viruses, etc.
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

	value = (*this)[shootval] + 1;  //since a value of 1 needs to be 2 to make equations below work
	type = (*this)[shoot];
	
	(*this)[shoot] = 0;
	(*this)[shootval] = 0;
	
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

		cost = long((pow(2, multiplier) - 1) * SimOpts.Costs[SHOTCOST]);
		if (cost <= this->nrg)
		{
			this->ChargeNRG(cost);
		}
		else
		{
			multiplier = log((nrg / SimOpts.Costs[SHOTCOST]) + 1) / log(2);
			this->ChargeNRG(this->nrg);
		}
	}
	else
	{
		this->ChargeNRG(SimOpts.Costs[SHOTCOST]);
	}
	//////////////////////////////////////////////////////

	switch(type)
	{
		//basic feeding shot
		case -1:
            new Shot(this);
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
Robot* Robot::Split(float percentage)
{
	if(this->generation > 0)
        return NULL;
    
    long sondist;
	float babyradius;
	float thisradius;
	float Length;
	Vector4 babypos;
	Vector4 thispos;

	//walls can't reproduce
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

	thispos = this->pos - (percentage * Length * this->aimvector);
	babypos = thispos + (Length * this->aimvector);

	//now we check for collision with other bots:
	//with both the new babypos, radius and the new thispos, radius
	//if there is a collision,
	//return false;	
		
	Robot *baby = new Robot();
	
	baby->obody = baby->Body = this->Body * percentage;
	this->obody = this->Body = this->Body * (1.0f - percentage);
	
	baby->onrg = baby->nrg = this->nrg * percentage;
	this->onrg = this->nrg = this->nrg * (1.0f - percentage);
	
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

	this->SonNumber++;
	
    baby->parent = this->AbsNum;
	baby->generation = this->generation + 1;
	baby->LastOwner = this->LastOwner;
	baby->fname = this->fname;
	
	baby->vel = this->vel;

	baby->UpdateMass();
	this->UpdateMass();

	this->UpdateRadius();
	baby->UpdateRadius();

	sondist = long(this->radius + baby->radius);
	this->pos = this->pos - percentage * sondist * this->aimvector;
	baby->pos = this->pos + Length * this->aimvector;

	this->opos = this->pos - this->vel;
	baby->opos = baby->pos - baby->vel;

	baby->color = this->color;

	(*baby)[timersys] = (*this)[timersys];//epigenetic timer

	//make the birth tie
	if (!Tie::MakeTie(this, baby, 0))
    {
        delete baby;
        return NULL;
    }

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
	
	(*this)[maxvelsys] = iceil(SimOpts.MaxSpeed);

	(*this)[masssys] = iceil(this->mass * 100);

	(*this)[velscalar] = iceil(Length3(this->vel));
	(*this)[velup] = iceil(this->vel * this->aimvector); //dot product of direction
	(*this)[veldn] = -(*this)[velup];
	(*this)[veldx] = iceil((this->vel % this->aimvector)); //the magnitude for a 2D vector crossed in 3D is the Z element
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
