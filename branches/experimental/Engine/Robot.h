#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <vector>
#include <cmath>
#include "../Common/Vectors.h"
#include "../Common/Random.h"
#include "ObjectPrimitive.h"
#include "Tie.h"
#include "DNAClass.h"
#include "Globals.h"
#include "Specie.h"
#include "RobotSysvars.h"
#include "SimOptions.h"
#include "Shot.h"
#include "CommandQueue.h"

#include <fx.h>

//#include "../GUI/GUIBotDebug.h"
class BotDebug_Window;
class Shot;
typedef std::vector<Tie *> TieList;

using namespace std;

//////////CONSTANTS////////////
const int CUBICTWIPPERBODY = 905;
const int RobSize          = 120;

class Robot : public SolidPrimitive
{
    friend class Tie; //tie class has access to bot memory among other things
    friend class Simulation;
    friend void DrawTies(bool Perimeter);

public:     //temporary
	TieList Ties;                           //linked list of ties
private:
    __int16 currtie;                        //current port or phase that the bot is set to

	//Physics
	Vector3f ovel;
    Vector3f Impulse;                        // impulses that get divided by mass to get forces
    Vector3f oldImpulse;
	float ImpulseStatic;					// static force scalar (always opposes current forces)

    float aim;								// aim angle
    float AngularMomentum;
public:

	bool Veg;								// is it a vegetable?
	bool Wall;								// is it a wall?
	bool Corpse;
	bool Fixed;								// is it blocked?
	bool Dead;								// Allows program to define a robot; dead after a certain operation
	bool Multibot;        					// Is robot part of a multi-bot
    bool NewMove;                           // does this bot use the new movement controls or is it a pussy?
    bool active;                            // used in collision detection
    bool View;

private:
	int occurr[20];							// array with the ref* values

public:
	//Contents of cell
	float nrg;								// energy
	float onrg;								// old energy
	float Body;								// Body points. A corpse still has a body after all
	float obody;							// old body points, for use with pain pleas versions for body

	float AddedMass;						// From fluid displacement
	float mass;								// mass of robot

	float Shell;							// Hard shell. protection from shots 1-100 reduces each cycle
	float Slime;           					// slime layer. protection from ties 1-100 reduces each cycle
	float Waste;           					// waste buildup in a robot. Too much and he dies. some can be removed by various methods
	float Pwaste;          					// Permanent waste. cannot be removed. Builds up; waste is removed.
	float Poison;          					// How poisonous is robot
	float Venom;           					// How venomous is robot

private:
	//Other
	bool Paralyzed;       					// true when robot is paralyzed
	float ParaCount;        				// countdown until paralyzed robot is free to move again
	int Vloc;            					// Location for custom venom to strike
	int Vval;            					// Value to insert into venom location
public:
	bool Poisoned;        					// Is robot poisoned and confused
	float PoisonCount;     				    // Countdown till poison is out of his system
	int Ploc;            					// Location for custom poison to strike
private:
	int DecayTimer;      					// controls decay cycle
	long Kills;              				// How many other robots has it killed? Might not work properly

	// virtual machine
	__int16 mem[1000];       				// memory array

public:
    CommandQueueClass DNACommands;

private:
	DNA_Class* dna;        					// the DNA
public:
	Robot* lastopp;     	            // pointer to robot in eye5



    Robot::Robot(DnaParser* parser = NULL, datispecie *myspecies = NULL, DNA_Class* speciesDna = NULL);
    Robot::Robot(const Robot* mother);
    void init(DnaParser* parser = NULL, datispecie *myspecies = NULL, DNA_Class* speciesDna = NULL);      //be called whenever a bot is created


	~Robot();
	void TurnGenesis();
	void PreTurn();

    void Integrate();
    void EdgeCollisions();
    float BotCollisionsPos();
    void VelocityCap();

    void DuringTurn();
	void PostTurn();
	void Shock();
	bool DeathManagement();

    const bool isReproducing() const;
    Robot* makeBaby();

	void TurnEnd();
    void CheckVision();
	__int16 &operator[](const unsigned int i)
	{
		return mem[i-1];
	}
    const __int16 &operator[](const unsigned int i) const
	{
		return mem[i-1];
	}

    const float x() const {return pos.x();}
    const float y() const{return pos.y();}
    const float &findaim() const{return this->aim;}

    const std::string getDnaText(const DnaParser* parser) const;
    void ExecuteDNA();
    bool ChargeNRG(float amount);

    bool addEnergy(float amount);
    bool addWaste(float amount);
    bool addBody(float amount);

    bool isShooting();
    Shot* makeShot();

    void UpdateTies();
    bool FireTie();
    bool CanTie();
    void AddTie(Tie* tie);
    void RemoveTie(Robot *other); //remove ties to other if such ties exist
    void RemoveTie(Tie* tie);
    void RemoveAllTies();
    void SetTie(__int16 a);
    Tie *CurrTie();
    __int16 NextTie();
    void Robot::WriteTie(__int16 location, __int16 number, __int16 tienum = 0);
    __int16 Robot::ReadTie(__int16 loc, __int16 tienum = 0);
    void Robot::ApplyNewTieSysvars();

private:
	// informative
	unsigned int SonNumber;       			// number of sons
	unsigned long parent;      				// parent absolute number
	unsigned long BirthCycle;  				// birth cycle
	unsigned int genenum;      				// genes number
	unsigned int generation;				// generation
	string LastOwner;        				// last internet owner//s name
	string fname;            				// species name
	//unsigned int DnaLen;   					// dna length

	int virusshot;       					// the viral shot being stored
	int Vtimer;          					// Count down timer to produce a virus

	void UpdateRadius();
	void UpdateMass();
	void UpdateAim();
	void UpdatePosition();
	void MakeShell();
	void MakeSlime();
	void MakeVenom();
	void MakePoison();
	void WasteManagement();
	void Upkeep();
	void PoisonManagement();
	void Construction();
	void FeedVegWaste();
	void Aging();
	void BodyManagement();
	void RobShoot();
	void DeltaBody(int value);



	void ShotManagement();
	void SetMems();

	Robot* Split(float percentage);
	void BasicRobotSetup();
	void Setup(datispecie *myspecies, DnaParser*,DNA_Class* speciesDna);
	void scaleMaterials(float factor);

	//SENSES
	void FacingSun();
	void Touch(Robot *other, float distance);
	void Taste();
	void EraseSenses();
	Robot* BasicProximity();
    void EyeGridProximity();
	void WriteSenses();
	void WriteRefVars(const Robot *lastopp);
	void occurrList();
	inline void CompareRobots(Robot *const other, const unsigned int field);
	unsigned int EyeCells(const Vector3f &ab);

    //physics
    void NetForces();

    //subordinate physics functions
    void VoluntaryForces();
    void GravityForces();
    void BrownianForces();
    void BouyancyForces();
    void BotCollisionsVel();
    void PlanetEaters();
    void UpdateAddedMass();
    void Friction();
    void FulfillTieConstraintsPos();
    void FulfillTieConstraintsVel();
    void Robot::SpringForces();

    //veg controls
    void FeedVegSun();
};

inline void Robot::SetTie(__int16 a)
{
    currtie = (a > 0) ? ((a - 1)% 200) + 1 : a;
}

#endif
