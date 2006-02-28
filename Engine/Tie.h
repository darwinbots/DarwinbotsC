#ifndef TIE_H
#define TIE_H

//we stick these up here or else we create a semi-infinite loop fo including between this and robot.h
#include <iostream>
#include <list>

class Tie;

#include "../Common/Math3D.h"
#include "Robot.h"
class Robot;

enum substance_ID
{
    UNKNOWN = 0,
    BODY_ID,
    POISON_ID,
    WASTE_ID,
    VENOM_ID,
    NRG_ID,
    SHELL_ID,
    SLIME_ID
};

/*Creating and deleting ties can be tricky because we have to make sure that
both bots are simultaneously made aware of the tie's creation. Also, since only
bots at the end of a tie know of its existence, we must make sure that no tie is
left hanging around, unaccessible and wasting precious memory.*/

//remember to have ties being updated check for if port = 0 and age >= 100 (then we need to cut the tie, it's a birth tie)
class Tie
{
	int Port;  //the phase number the tie can be accessed with.  1 to 200
	Robot *sender; //robot that fired the tie
	Robot *receiver; //robot that received the tie
	
	long age;  //used for birth ties dissolving and regular ties hardening
	
	bool Sharing;		//is the tie sharing something?  Then lets color it appropriately | BLUE
	bool Communicating; //is the tie being used to send information back and forth?       | GREEN
	bool Feeding;       //is the tie being used for sending nrg?  Then color it.          | RED

	// Spring Force = -k*displacement - velocty * b
	// b and k are constants between 0 and 1

	float NaturalLength;
	float k;
	float b;
	
    int type;
    //'0 = damped spring, lower b and k values, birth ties here
    //'1 = string (only applies force if longer than
    //  "natural length", not if too short) b and k values high
    //'2 = bone (very high b and k values).  (Or perhaps something better?)
    //'3 = anti-rope - only applies force if shorter than
    //  '"natural length", not if too long) b and k values high

	//class Tie *next; //for linked list use with robots

	//Functions
public:
	static bool Tie::MakeTie(Robot* _sender, Robot* _receiver, int _port);
	~Tie();
private:
    Tie(Robot* _sender, Robot* _receiver, int _port,
                float _k = 0.005f, float _b = 0.01f, int _type=0);

    Robot *Tie::FindOther(Robot *me);
    __int16 Tie::ReadMem(Robot *me, __int16 loc);
    void Tie::WriteMem(Robot *me, __int16 loc, __int16 value);
    void Tie::ShareSubstance(Robot *me, substance_ID ID, float amount);
};

#endif