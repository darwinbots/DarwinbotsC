#ifndef ROBOT_H
#define ROBOT_H

#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

//we stick this up here or else we get a semi-infinite loop of including between this and tie.h
//class Robot;

#include <iostream>
#include <vector>
#include <cmath>
#include "../Common/Math3D.h"
#include "../Common/Random.h"
#include "ObjectPrimitive.h"
#include "Tie.h"
#include "DNAClass.h"
#include "Globals.h"
#include "Specie.h"
#include "RobotSysvars.h"
#include "SimOptions.h"
#include "Shots.h"

//#include "../GUI/GUIBotDebug.h"
class BotDebug_Window;
typedef std::list<Tie*> TieList; //we may have to change this later

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
    friend struct tempBot_typ;

    #ifdef _MSC_VER
    friend class Robot; //instances of the Robot class can access each other
                        //please do not unfriend Robot class with itself.
    #endif

private:

	//Physical Attributes
	float radius;
    
	float aim;								// aim angle
	Vector4 aimvector;                      // the unit vector for aim

	TieList Ties;                           //linked list of ties
	
	//Physics
	Vector4 Impulse;                        // impulses that get divided by mass to get forces
    Vector4 oldImpulse;
	float ImpulseStatic;					// static force scalar (always opposes current forces)
    Vector4 temppos;                        // a temporary vector to store for projection collision
public:

	bool Veg;								// is it a vegetable?
	bool Wall;								// is it a wall?
	bool Corpse; 
	bool Fixed;								// is it blocked?
	bool Dead;								// Allows program to define a robot; dead after a certain operation
	bool Multibot;        					// Is robot part of a multi-bot
    bool NewMove;                           // does this bot use the new movement controls or is it a pussy?
private:
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

	class Robot *lastopp;         	// pointer to const (last robot in eye5)
	unsigned long AbsNum;             				// absolute robot number

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
	void removeAllTies();
	void ShotManagement();
	void SetMems();

	Robot *Robot::Split(float percentage);
	void BasicRobotSetup();
	void Setup(datispecie *myspecies);

	//SENSES
	void FacingSun();
	void Touch(Robot *other, float distance);
	void Taste();
	void EraseSenses();
	Robot *BasicProximity();
	void WriteSenses();
	void WriteRefVars(const Robot *lastopp);
	void occurrList();
	inline void CompareRobots(Robot *const other, const unsigned int field);
	unsigned int EyeCells(const Vector4 &ab);

    //physics
    void NetForces();
    
    //subordinate physics functions
    void VoluntaryForces();
    void GravityForces();
    void BrownianForces();
    void BouyancyForces();
    void EdgeCollisions();
    void BotCollisions();
    void PlanetEaters();
    void UpdateAddedMass();

    //veg controls
    void FeedVegSun();

public:
    bool View;

    Robot::Robot(datispecie *myspecies = NULL):radius(60.0f),
                aim(0.0f),aimvector(cosf(aim),sinf(aim)),
                Ties(),
                Impulse(), ImpulseStatic(0.0f), oldImpulse(0.0f,0.0f,0.0f),
                Veg(false),Wall(false),Corpse(false),Fixed(false),
                Dead(false),Multibot(false),NewMove(false),
                nrg(1000.0f),onrg(nrg),
                Body(1000.0f),obody(Body),
                AddedMass(0.0f),mass(1.0f),
                Shell(0.0f),Slime(0.0f),Waste(0.0f),Pwaste(0.0f),Poison(0.0f),Venom(0.0f),
                Paralyzed(false),ParaCount(0),Vloc(0),Vval(0),
                Poisoned(false),PoisonCount(0),Ploc(0),
                DecayTimer(0),Kills(0),
                DNA(NULL),
                lastopp(0),AbsNum(0),
                SonNumber(0),parent(0),BirthCycle(0),genenum(0),generation(0),
                LastOwner(""),fname(""),DnaLen(0),
                virusshot(0),Vtimer(0),
                View(false)
    {
        memset(&mem[0], 0, sizeof(mem));
        memset(&occurr[0], 0, sizeof(occurr));
        init(myspecies);        
    }

    void init(datispecie *myspecies = NULL);      //be called whenever a bot is created
	
	
	~Robot();
	void TurnGenesis();
	void PreTurn();
	void Constraints();
    void DuringTurn();
	void PostTurn();
	void TurnCleanup();
	void TurnEnd();
	__int16 &operator[](const unsigned int i)
	{
		return mem[i-1];
	}
    const __int16 &operator[](const unsigned int i) const
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

    unsigned long findAbsNum()
    {
        return AbsNum;
    }

    void Robot::DrawRobotEye();
    
    bool canTie();
    void addTie(Tie* tie);
    void removeTie(Tie* tie);
};

extern Robot *rob[5000];  //an array of pointers to Robots.

#endif
