/*****************************************
Class containing all the info for robots
******************************************/

#include "Robot.h"
#include "Engine.h"

using namespace std;

//vector<Robot *> rob(5000, (Robot *)NULL);
//int MaxRobs; //how far into the robot array to go

Robot::Robot(DnaParser* parser, datispecie *myspecies):
                SolidPrimitive(),
                aim(0.0f),AngularMomentum(0.0f),
                Ties(),currtie(0),
                Impulse(0,0,0), ImpulseStatic(0.0f), oldImpulse(0.0f,0.0f,0.0f),
                ovel(vel),
                Veg(false),Wall(false),Corpse(false),Fixed(false),
                Dead(false),Multibot(false),NewMove(false),
                nrg(1000.0f),onrg(nrg),
                Body(1000.0f),obody(Body),
                AddedMass(0.0f),mass(1.0f),
                Shell(0.0f),Slime(0.0f),Waste(0.0f),Pwaste(0.0f),Poison(0.0f),Venom(0.0f),
                Paralyzed(false),ParaCount(0),Vloc(0),Vval(0),
                Poisoned(false),PoisonCount(0),Ploc(0),
                DecayTimer(0),Kills(0),
                dna(NULL),
                lastopp(0),
                SonNumber(0),parent(0),BirthCycle(0),genenum(0),generation(0),
                LastOwner(""),fname(""),
                virusshot(0),Vtimer(0),
                View(false),
                DNACommands(this)
{
    memset(&mem[0], 0, sizeof(mem));
    memset(&occurr[0], 0, sizeof(occurr));
    init(parser, myspecies);
}

Robot::Robot(const Robot* mother):SolidPrimitive(*mother),
                Ties(),currtie(0),
                ovel(vel),
                Impulse(0,0,0), ImpulseStatic(0.0f), oldImpulse(0.0f,0.0f,0.0f),
                Veg(mother->Veg), Wall(mother->Wall), Corpse(mother->Corpse),Fixed(mother->Corpse),
                Dead(mother->Dead),Multibot(mother->Multibot),NewMove(mother->NewMove),
                nrg(mother->nrg),onrg(nrg),
                Body(mother->Body),obody(Body),
                AddedMass(mother->AddedMass),mass(mother->mass),
                Shell(mother->Shell),Slime(mother->Slime),
                Waste(mother->Waste),Pwaste(mother->Pwaste),
                Poison(mother->Poison),Venom(mother->Venom),
                Paralyzed(mother->Paralyzed),ParaCount(mother->ParaCount),
                Vloc(mother->Vloc),Vval(mother->Vval),
                Poisoned(mother->Poisoned),PoisonCount(mother->PoisonCount),Ploc(mother->Ploc),
                DecayTimer(0),Kills(0),
                dna(new DNA_Class(*(mother->dna))),
                lastopp(NULL),
                SonNumber(0),parent(mother->getAbsNum()),BirthCycle(SimOpts.TotRunCycle),
                genenum(mother->genenum),generation(mother->generation + 1),
                LastOwner(mother->LastOwner),fname(mother->fname),
                virusshot(0),Vtimer(0),
                View(mother->View),
                DNACommands(this)
{
    memset(&mem[0], 0, sizeof(mem));
    memset(&occurr[0], 0, sizeof(occurr));
    this->absNum = ++SimOpts.TotBorn;
}

Robot::~Robot()
{
	if (this->dna != NULL)
    {
        delete this->dna;
        this->dna = NULL;
    }

	RemoveAllTies();
    Engine.EyeGridRemoveDeadBot(this);
}


void Robot::init(DnaParser* parser,datispecie *myspecies)
{
	this->BasicRobotSetup();
	if(myspecies != NULL)
        this->Setup(myspecies,parser);
	this->SetMems();
}

/* Sets up a truly BASIC robot
Does not even set up color, nrg, etc.*/
void Robot::BasicRobotSetup()
{
    SimOpts.TotBorn++;
	this->absNum = SimOpts.TotBorn;

	//set random aim
	aim = DBrand() * PI * 2;
    AngularMomentum = 0.0f;
	aimVector.set(cosf(aim), sinf(aim));

	this->BirthCycle = SimOpts.TotRunCycle;
	(*this)[timersys] = (__int16)frnd(-32000, 32000);

    this->View = false;
}

void Robot::Setup(datispecie *myspecies, DnaParser* parser)
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

    string truePath(myspecies->path);
    if (truePath.substr(0,2)=="&#") //apparently, VB uses "&#" to represent app's directory
        truePath.replace(0,2,Engine.MainDir(),0,(Engine.MainDir()).length());
    truePath += "\\" + myspecies->Name;
    dna = new DNA_Class(parser->loadFile(truePath));
    this->dna->Mutables = myspecies->Mutables;
    this->occurrList();
}

void Robot::ExecuteDNA()
{
    assert(this != NULL && "Attempting to access non existant bot's DNA in Robot::ExecuteDNA()");
    assert(this->dna != NULL && "Attempting to access non existant DNA in Robot::ExecuteDNA()");
    this->dna->Execute(this);
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

void Robot::UpdateAddedMass()
{
    //added mass is a simple enough concept.
    //To move an object through a liquid, you must also move
    //that liquid out of the way.

    const double AddedMassCoefficientForASphere = 0.5;
    AddedMass = float(AddedMassCoefficientForASphere * SimOpts.Density *
                        Body * CUBICTWIPPERBODY);
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

	aimVector.set(cosf(aim), sinf(aim));

	(*this)[aimright] = 0;
	(*this)[aimleft] = 0;
	(*this)[Aimsys] = iceil(this->aim * 200);
	(*this)[SetAim] = iceil((*this)[Aimsys]);
}

void Robot::UpdatePosition()
{
	if ((*this)[fixpos] > 0)
        Fixed = true;
	else
        Fixed = false;

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
	(*this)[velup] = iceil(vel * aimVector); //dot product of direction
	(*this)[veldn] = -(*this)[velup];
	(*this)[veldx] = iceil((vel % aimVector)); //the magnitude for a 2D vector crossed in 3D is the Z element
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
		//Alzheimer's
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
    if(this->dna != NULL)
        this->ChargeNRG(this->dna->length() * SimOpts.Costs[BPCYCCOST]);
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
		Body += nrg / 10;
		nrg = 0;
		Dead = true;
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
            if(this->dna != NULL)
            {
                delete dna;
                dna = NULL;
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

    return (!Dead);
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

/*void Robot::PostTurn()
{
	if(this->dna != NULL)
        this->dna->Mutate(false); //<--- mutating by point cycle
	//this->BotDNAManipulation t <--- Things like delgene, making viruses, etc.
    this->Construction();
	this->ShotManagement();
	this->BodyManagement();
	this->FireTie();
    this->FeedVegSun();
	this->UpdateRadius();
	this->UpdateMass();
}*/

/*void Robot::TurnCleanup()
{
	this->Shock();
	this->DeathManagement();
}*/

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
	(*this)[velup] = iceil(vel * this->aimVector); //dot product of direction
	(*this)[veldn] = -(*this)[velup];
	(*this)[veldx] = iceil(vel % this->aimVector); //the magnitude for a 2D vector crossed in 3D is the Z element
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

/*******************************************
Vegies convert half of the waste in their bodies
to nrg each cycle
********************************************/
void Robot::FeedVegWaste()
{
	if (nrg < 32000)
	{
		nrg = nrg + Waste / 2;
		Waste = Waste / 2;
		if (nrg > 32000)
		{
			Waste = Waste + (nrg - 32000);
			nrg = 32000;
		}
	}
}

void Robot::FeedVegSun()
{
    static unsigned long counter=0;
    int daymod;
    float depth=0, tok=0;

    const float QuadConstant = .00000005859375f;

    counter++;

    if (counter > SimOpts.CycleLength && SimOpts.DayNight)
    {
        SimOpts.Daytime = !SimOpts.Daytime;
        counter = 0;
    }

    if (SimOpts.Daytime)
    {
        //display day picture;
    }
    else
    {
        //display night picture
    }

    if (SimOpts.Daytime) daymod = 1;
    else daymod = 0;

    if (SimOpts.DayNight && SimOpts.Daytime == false)
        return;

    if (Veg && nrg > 0)
    {
        if (SimOpts.PondMode)
        {
            depth = this->pos.y() / 2000 + 1;
            if (depth < 1)
                depth = 1;

            tok = (SimOpts.LightIntensity / powf(depth, SimOpts.Gradient) * daymod + 1);
        }
        else
        {
            tok = SimOpts.LightIntensity;
        }

        if (tok < 0)
            tok = 0;

        switch(SimOpts.VegFeedingMethod)
        {
            case 0: //per veg
            {
                this->nrg += tok * (1 - SimOpts.VegFeedingToBody / 100);
                this->Body += tok * (SimOpts.VegFeedingToBody / 100) / 10;
            }break;
            case 1: //per kilobody
            {
                this->nrg += tok * (1 - SimOpts.VegFeedingToBody / 100) * this->Body / 1000;
                this->Body += tok * (SimOpts.VegFeedingToBody / 100) / 10 * this->Body / 1000;
            }break;
            case 2: //quadtratically based on body.  Close to type 0 near 1000 body points, but quickly diverges at about 5K body points
            {
                tok *= ((this->Body * this->Body * QuadConstant) + (1 - QuadConstant * 1000 * 1000));
                this->nrg += tok * (1 - SimOpts.VegFeedingToBody / 100);
                this->Body += tok * (SimOpts.VegFeedingToBody / 100) / 10;
            }break;
        }

        if (this->nrg > 32000)
            this->nrg = 32000;
        if (this->Body > 32000)
            this->Body = 32000;

        this->UpdateRadius();
        this->UpdateMass();
    }
}

const std::string Robot::getDnaText(const DnaParser* parser) const
{
    if (parser == NULL)
        return std::string("");
    else
        return parser->getText(*dna);
}

/*********************************************
        Shooting
*********************************************/

//As a side effect, this normalises the 'shoot' memval
bool Robot::isShooting()
{
    __int16 type = (*this)[shoot];

    //mod values to be in the right range
    if (type > 1000)
        type = (type - 1) % 1000 + 1;

    if (type < -10)
        type = (type + 1) % 10 - 1;

	//range is invalid for creating a shot
	if (type == 0 || type < -6 || type == -5)
		return false;

    (*this)[shoot] = type;
    return true;
}

Shot* Robot::makeShot()
{
    assert(this->isShooting());
    this->ChargeNRG(SimOpts.Costs[SHOTCOST]);
	//////////////////////////////////////////////////////

    Shot *temp;
    switch((*this)[shoot])
	{
		//basic feeding shot
		case -1:
            temp = new FeedingShot(this);
		break;
		//give nrg shot
		case -2:
            temp = new EnergyShot(this);
		break;
		//Venom shot
		case -3:
            temp = new VenomShot(this);
		break;
		//Waste Shot
		case -4:
            temp = new WasteShot(this);
		break;
		//Body Shot
		case -6:
            temp = new BodyShot(this);
		break;
		//"Info" shots
		default:
            temp = new InfoShot(this);
		break;
	}
    (*this)[shoot] = 0;
	(*this)[shootval] = 0;
	return temp;
}

/***********************************
        Reproduction
***********************************/

const bool Robot::isReproducing() const
{
    /*if(this==(const Robot* const)0xfeeefeee)
        throw;*/
    return (((*this)[Repro] > 0) &&
            !Corpse && !Wall && !Dead
            && (Body > 2)); //too small to repro (this prevents effects of cancer
                            //from being so totally debilitating to game speed)
}

//call this very last along with the death management above
Robot* Robot::makeBaby()
{
	std::cout<<"Bot#"<<absNum;
	assert(this != NULL && "Non existant bot trying to reproduce");
    assert(!this->Corpse && "Corpse attempting to reproduce");
    assert((*this)[Repro] > 0 );
    assert(this->dna != NULL && "Bot with no DNA trying to reproduce");

    if ((*this)[Repro] >= 100)
        (*this)[Repro] = 99;

    float mutmult = 1.;
    float costmult = 1.;

    if((*this)[mrepro] != 0)
    {
        costmult = 1.0f + abs((*this)[mrepro]) / 100;
        mutmult = float (log(35000 / fabs((*this)[mrepro])) / log(2) / 15.1);
    }

    ChargeNRG(SimOpts.Costs[BPCOPYCOST] * (float)dna->length() * costmult);

    float percentage = (*this)[Repro]/100.0f;
    (*this)[Repro] = 0;

    Robot* baby = this->Split(percentage);

    baby->dna = new DNA_Class((*this->dna));
        //still need to program code for mrepro
    baby->dna->Mutate(true, mutmult);
    baby->occurrList();
    std::cout<<" reproduced on turn "<<SimOpts.TotRunCycle<<std::endl;
    return baby;
}

//Reproduce
//basic reproduction function that mitosis and "sexRepro" will call
//function does NOT:

//1.  Copy DNA, or set any DNA related sysvars or variables
//  a.  Mutate the DNA

//returns pointer to baby, or NULL if error
Robot* Robot::Split(float percentage)
{
	//insert check for too many vegs

	Robot *baby = new Robot(this);
	this->scaleMaterials(1-percentage);
	baby->scaleMaterials(percentage);

	this->SonNumber++;

	baby->UpdateMass();
	this->UpdateMass();

	this->UpdateRadius();
	baby->UpdateRadius();

	long sondist = long(this->radius + baby->radius);
	Vector3f vel = this->pos - this->opos;

    this->pos = this->pos - percentage * sondist * this->aimVector;
	baby->pos = this->pos + float(sondist) * this->aimVector;

	this->opos = this->pos - vel;
	baby->opos = baby->pos - vel;

    baby->oldImpulse.set(0,0,0);
    baby->Impulse.set(0,0,0);
    baby->ImpulseStatic = 0.0f;

	(*baby)[timersys] = (*this)[timersys];//epigenetic timer

	//make the birth tie
	//Tie::MakeTie(this, baby, -1);

    baby->fname = this->fname;

	baby->SetMems();
	this->SetMems();

    return baby;
}

void Robot::scaleMaterials(float factor)
{
    nrg *= factor;
	onrg *= factor;
	Body *= factor;
	obody *= factor;
	AddedMass *= factor;
	mass *= factor;
	Shell *= factor;
	Slime *= factor;
	Waste *= factor;
	Pwaste *= factor;
	Poison *= factor;
	Venom *= factor;
}