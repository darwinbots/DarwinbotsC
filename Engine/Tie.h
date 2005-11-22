#ifndef TIE_H
#define TIE_H

class Robot;

//remember to have ties being updated check for if port = 0 and age >= 100 (then we need to cut the tie, it's a birth tie)
class Tie
{
	int Port;  //the phase number the tie can be accessed with.  1 to 200
	Robot *sender; //robot that fired the tie
	Robot *reciever; //robot that recieved the tie
	
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

	class Tie *next; //for linked list use with robots

	//Functions
	public:
	bool Tie::MakeTie(Robot *sender, Robot *reciever, int port);
};
#endif
