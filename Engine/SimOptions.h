#ifndef SIMOPTIONS_H
#define SIMOPTIONS_H

#include <iostream>
#include "Specie.h"

using namespace std;

const int CONDCOST = 5;
const int COSTSTORE = 7;

const int MOVECOST = 21;
const int TURNCOST = 22;
const int TIECOST = 23;
const int SHOTCOST = 24;
const int BPCYCCOST = 25;
const int BPCOPYCOST = 26;
const int VENOMCOST = 27;
const int POISONCOST = 28;
const int SLIMECOST = 29;
const int SHELLCOST = 30;
const int BODYUPKEEP = 31;
const int COSTMAX = 32;

/*********************************
Contains all the constants for physics (obviously)
SimOptsions aboves inherits from this
*********************************/

struct PhysicsConstants
{
    public:
    float CoefficientStatic;
    float CoefficientKinetic;
    float ZGravity;
    float YGravity;
    double Density;
    double Viscosity;

    float Brownian;
    float MovingEfficiency;

    bool PlanetEaters;
    float PlanetEatersG;

    float ElasticCoefficient; //coefficient used in bot to bot collisions

    bool ZeroMomentum;		  //bool, is ZeroMomentum mode enabled?
};

//definition of the SimOpts structure

//'BE VERY CAREFUL changing the TYPE of a variable
//'the read/write functions for saving sim settings/bots/simulations are
//'very particular about variable TYPE
struct SimOptions: PhysicsConstants
{

    public:
    string SimName;             //string
    unsigned long TotRunCycle;  //unsigned long
    float CycSec;               //float
    unsigned long TotRunTime;	//unsigned long
    unsigned long TotBorn;		//unsigned long
    unsigned long TotBotsNow;
    unsigned long TotVegsNow;
    unsigned long TotObjects;
    unsigned int SpeciesNum;	//unsigned int
    datispecie Specie[50];		//datispecie
    unsigned int FieldSize;     //unsigned int
    
    Vector4 FieldDimensions;	//Vector4

    unsigned int MaxPopulation; //unsigned int
    unsigned int MinVegs;		//unsigned int
    bool KillDistVegs;			//bool

    //toroidal is updnconnected = dxsxconected = true
    bool Toroidal;				//bool
    bool Updnconnected;			//bool
    bool Dxsxconnected;			//bool

    string AutoSimPath;			//string
    unsigned int AutoSimTime;	//unsigned int

    string AutoRobPath;			//string
    unsigned int AutoRobTime;	//unsigned int

    float MutCurrMult;  //current mutation multiple (float)

    bool MutOscill; //mutation oscillation in effect? (bool)
    unsigned long MutCycMax;	//unsigned long
    unsigned long MutCycMin;	//unsigned long

    //bot database.  Hugely expensive in terms of disk space
    string DBName;				//string
    bool DBEnable;				//bool
    bool DBExcludeVegs;			//bool
    bool DBRecDNA;				//bool

	bool F1;			        //f1 contest (bool)
    bool League;				//run league mode (a batch of F1 modes) (bool)
    bool Restart;				//restart the sim when all bots are dead? (doesn't count veggies) (bool)
    
    bool UserSeedToggle;		//bool
    long UserSeedNumber;		//long
    
    float Costs[70];            //costs for various activities (float)

    float LightIntensity;		//float
	bool PondMode;				//bool
    float Gradient;				//bool
    bool DayNight;				//daynight mode? (bool)
    bool Daytime;				//is it day? (bool)
    unsigned int CycleLength;	//unsigned int

    bool CorpseEnabled;			//bool
    
    float DecaySize;		    //float
    unsigned int DecayDelay;	//unsigned int
    unsigned int DecayType;		//unsigned int
    
    //how shots return energy
    unsigned int EnergyProp;	//unsigned int
    unsigned int EnergyFix;		//unsigned int
    bool EnergyExType;			//bool

    unsigned int RepopCooldown;	//unsigned int
    unsigned int RepopAmount;	//unsigned int

    unsigned int VegFeedingMethod;//unsigned int
    float VegFeedingToBody;		  //how much nrg given to vegs gets put into body? (float)

	unsigned int BadWasteLevel;  //be sure to save in settings files
                                 // (wasn't in 2.4VB) and be sure to catch if this is set to 0
	unsigned int MaxSpeed;		 //Same as above

    void AddSpecies(string path, string name);
    void DeleteSpecies(int x);
    void DeleteSpecies(string path, string name);
};

extern SimOptions SimOpts;  //for use in sims
extern SimOptions TmpOpts; //for use in GUI, gets copied to SimOpts

#endif