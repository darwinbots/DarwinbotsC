#pragma once
//Inherited by Robot class, put here to help keep maintainability
//and readability up
#include <iostream>
#include "Vectors.h"
class Robot;

class RobotPhysics
{
    private:
    Robot *me;
    
    Vector3f tempPos, tempVel; //used for constraints, these are the original preconstraint values
    
protected:
    Vector3f pos, opos;
    
    Vector3f vel, ovel;//old and current velocity from last time step and this time step
    
    Vector3f oldImpulse; //old Impulse from last time step
   
    Vector3f ImpulseIndependant; //Impulse from forces independant of velocity
    Vector3f ImpulseResistive; //Impulses dependant upon velocity or other
                               //attributes that change during the course of integration
    
    //Scalars
	float ImpulseStatic;					// static force scalar (always opposes current forces)
	float DragScalar;                       // Sphere drag scalar (always opposes current velocity)
	
	//attributes
	float AddedMass;						// From fluid displacement
	float mass;
	float radius;
	
public:
    bool CollisionActive;                   // used in collision detection
    
    RobotPhysics()
    {
        ovel.set(0,0);
        oldImpulse.set(0,0);
        ImpulseIndependant.set(0,0);
        ImpulseResistive.set(0,0);
        ImpulseStatic = 0;
        DragScalar = 0;
        
        CollisionActive = true;
        AddedMass = 0;
        radius = 60;
        me = NULL;
        tempVel.set(0,0);
        tempPos.set(0,0);
    }
    
	void Integrate();
	void NetForces(Robot *me);	
	
	//Impulses
    private:
    void IndependantForces();
    void ResistiveForces();
    
    //subordinate Impulse functions
    void Drag();
    void VoluntaryForces();
    void GravityForces();
    void BrownianForces();
    void BouyancyForces();
    void PlanetEaters();
    void UpdateAddedMass();
    void Friction();
    
    void BotCollisionsVel();
    void FulfillTieConstraintsPos();
    void FulfillTieConstraintsVel();
    void VelocityCap();
    
    public:
    void SoftConstraints();    
    
    //Hard Contraints (must all be almost 100% satisfied
    void EdgeCollisions();
    float BotCollisionsPos();    
};