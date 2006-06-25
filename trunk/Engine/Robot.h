#ifndef ROBOT_H
#define ROBOT_H

#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

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
#include "Shots.h"
#include "CommandQueue.h"
#include "Engine.h"
#include "RobotPhysics.h"

//#include "../GUI/GUIBotDebug.h"
class BotDebug_Window;
typedef vector<Tie *> TieList;

using namespace std;

//////////CONSTANTS////////////
const int CUBICTWIPPERBODY = 905;
const int RobSize          = 120;

class Robot : public RobotPhysics
{
    friend class Tie; //tie class has access to bot memory among other things
    friend class Shot;
    friend class BotInfoWindow_Class; //GUI display to show bot details
    friend class RobotPhysics;        //Subordinate class wrapping the physics details
        
    #ifdef _MSC_VER
    friend class Robot; //instances of the Robot class can access each other
                        //please do not unfriend Robot class with itself.
    #endif

    friend void DrawTies(bool Perimeter);
    friend void Engine_Class::ExecuteDNA();

private:

	//Physical Attributes
	unsigned long age;
		
	float aim;								// aim angle
    float AngularMomentum;
    Vector3f aimvector;                      // the unit vector for aim

	TieList Ties;                           //linked list of ties
    __int16 currtie;                        //current port or phase that the bot is set to
    
public:	
	Vector3f color;
	
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
    public: CommandQueueClass DNACommands;
    private:
	DNA_Class *DNA;        					// the DNA

	Robot *lastopp;         	            // pointer to robot in eye5
	unsigned long AbsNum;             		// absolute robot number

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
	bool DeathManagement();
	bool KillRobot();
	void Reproduction();
	
	void ShotManagement();
	void SetMems();
    
	Robot *Split(float percentage);
	void BasicRobotSetup();
	void Setup(datispecie *myspecies);
    
	//SENSES
	void FacingSun();
	void Touch(Robot *other, float distance);
	void Taste();
	void EraseSenses();
	Robot *BasicProximity();
    void EyeGridProximity();
	void WriteSenses();
	void WriteRefVars(const Robot *lastopp);
	void occurrList();
	inline void CompareRobots(Robot *const other, const unsigned int field);
	unsigned int EyeCells(const Vector3f &ab);

    //veg controls
    void FeedVegSun();

public:
    bool View;

    Robot::Robot(datispecie *myspecies = NULL):
                aim(0.0f),AngularMomentum(0.0f), 
                aimvector(cosf(aim),sinf(aim)),
                Ties(),
                Veg(false),Wall(false),Corpse(false),Fixed(false),
                Dead(false),Multibot(false),NewMove(false),
                nrg(1000.0f),onrg(nrg),
                Body(1000.0f),obody(Body),
                Shell(0.0f),Slime(0.0f),Waste(0.0f),Pwaste(0.0f),Poison(0.0f),Venom(0.0f),
                Paralyzed(false),ParaCount(0),Vloc(0),Vval(0),
                Poisoned(false),PoisonCount(0),Ploc(0),
                DecayTimer(0),Kills(0),
                DNA(NULL),
                lastopp(0),AbsNum(0),
                SonNumber(0),parent(0),BirthCycle(0),genenum(0),generation(0),
                LastOwner(""),fname(""),DnaLen(0),
                virusshot(0),Vtimer(0),
                View(false),
                currtie(0)
    {
        age = 0;
        memset(&mem[0], 0, sizeof(mem));
        memset(&occurr[0], 0, sizeof(occurr));
        init(myspecies);
        DNACommands.SetBase(this);
    }

    void init(datispecie *myspecies = NULL);      //be called whenever a bot is created
	
	
	~Robot();
	void TurnGenesis();
	void PreTurn();
	
    void DuringTurn();
	void PostTurn();
	void TurnCleanup();
    void Reproduce();
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

    const Vector3f &findpos() const
    {
        return this->pos;
    }

    const Vector3f &findopos() const
    {
        return this->opos;
    }

    const float &findaim() const
    {
        return this->aim;
    }

    unsigned long findAbsNum()
    {
        return AbsNum;
    }

    void Robot::DrawRobotEye();
    
    void Robot::UpdateTies();
    bool FireTie();
    bool CanTie();
    void AddTie(Tie* tie);
    void RemoveTie(Robot *other); //remove ties to other if such ties exist
    void RemoveTie(Tie* tie);
    void RemoveAllTies();
    void SetTie(__int16 a)
    {
        currtie = (a > 0) ? ((a - 1)% 200) + 1 : a;
    }
    Tie *CurrTie();
    __int16 NextTie();
    void WriteTie(__int16 location, __int16 number, __int16 tienum = 0);
    __int16 ReadTie(__int16 loc, __int16 tienum = 0);
    void ApplyNewTieSysvars();
};

extern vector<Robot *> rob;  //an array of pointers to Robots.
extern int MaxRobs; //how far into the robot array to go (we use this instead of downsizing the Robot array to save time)

#endif
