#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <vector>
#include <cmath>
#include "../Common/Math3D.h"
#include "../Common/Random.h"
#include "ObjectPrimitive.h"
#include "Tie.h"
//#include "Block.h"
#include "DNAClass.h"
#include "Globals.h"
#include "Specie.h"
#include "RobotSysvars.h"
#include "SimOptions.h"
#include "Shots.h"

using namespace std;

//////////CONSTANTS////////////
const int CUBICTWIPPERBODY = 905;
const int RobSize          = 120;

///////GLOBALS/////////////////
extern unsigned int MaxRobs; //how far into the robot array to go

class Robot : public ObjectPrimitive
{
	friend class Tie; //tie class has access to bot memory among other things
  friend class Shot;
	//friend Robot; //instances of the Robot class can access each other

private:

	//Physical Attributes
	float radius; 
	//int Shape;                            // shape of the robot, how many sides

	//int Skin[13];        					// skin definition
	//int OSkin[13];       					// Old skin definition

	float aim;								// aim angle
	Vector4 aimvector;                      // the unit vector for aim

	Tie HeadTie;                            // linked list of ties (this is the head, head is never addressed except as through Headtie->next)
	int numties;
	
	//Physics
	Vector4 ImpulseInd;                     // independant forces vector
	Vector4 ImpulseRes;					    // Resistive forces vector
	float ImpulseStatic;					// static force scalar (always opposes current forces)

	bool Veg;								// is it a vegetable?
	bool Wall;								// is it a wall?
	bool Corpse; 
	bool Fixed;								// is it blocked?
	bool Dead;								// Allows program to define a robot; dead after a certain operation
	bool Multibot;        					// Is robot part of a multi-bot
    bool NewMove;                           // does this bot use the new movement controls or is it a pussy?

	int occurr[20];							// array with the ref* values
	
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

	//Other
	bool Paralyzed;       					// true when robot is paralyzed
	float ParaCount;        				// countdown until paralyzed robot is free to move again
	int Vloc;            					// Location for custom venom to strike
	int Vval;            					// Value to insert into venom location
	
	bool Poisoned;        					// Is robot poisoned and confused
	float PoisonCount;     				    // Countdown till poison is out of his system
	int Ploc;            					// Location for custom poison to strike

	int DecayTimer;      					// controls decay cycle
	long Kills;              				// How many other robots has it killed? Might not work properly

	// virtual machine
	__int16 mem[1000];       				// memory array
	DNA_Class *DNA;        					// the DNA

	class Robot *lastopp;         			// last robot in eye5
	long AbsNum;             				// absolute robot number

	//console; Consoleform    				// console object;sociated to the robot

	// informative
	unsigned int SonNumber;       			// number of sons
	unsigned long parent;      				// parent absolute number
	unsigned long BirthCycle;  				// birth cycle
	unsigned int genenum;      				// genes number
	unsigned int generation;				// generation
	string LastOwner;        				// last internet owner//s name
	string fname;            				// species name
	unsigned int DnaLen;   					// dna length

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
	void Shock();
	void DeathManagement();
	bool KillRobot();
	void Reproduction();
	bool FireTie();
	void ShotManagement();
	void SetMems();

	Robot *Robot::Split(float percentage);
	void BasicRobotSetup(datispecie *myspecies);

	//SENSES
	void FacingSun();
	void Touch(Robot *other, float distance);
	void Taste();
	void EraseSenses();
	Robot *BasicProximity();
	void WriteSenses();
	void WriteRefVars(Robot *lastopp);
	void occurrList();
	inline void CompareRobots(Robot *other, unsigned int field);
	unsigned int EyeCells(const Vector4 &ab);

    //physics
    void NetForces();
    
    //subordinate physics functions
    void VoluntaryForces();
    void GravityForces();
    void BrownianForces();
    void BouyancyForces();

    //veg controls
    void FeedVegSun();

public:
    bool View;


    Robot();
	Robot(datispecie *myspecies);
	~Robot();
	void TurnGenesis();
	void PreTurn();
	void DuringTurn();
	void PostTurn();
	void TurnCleanup();
	void TurnEnd();
	inline __int16 &operator[](const unsigned int i)
	{
		return mem[i-1];
	}

    string &DNA_Text()
    {
        return this->DNA->text();
    }

    const float x()
    {
        return pos.x();
    }

    const float y()
    {
        return pos.y();
    }

    void ExecuteDNA();
    bool ChargeNRG(float amount);
    float rad()
    {
        return radius;
    }

    const Vector4 &findpos() const
    {
        return this->pos;
    }

    void Robot::DrawRobotEye();
};

extern Robot *rob[5000];  //an array of pointers to Robots.

#endif

