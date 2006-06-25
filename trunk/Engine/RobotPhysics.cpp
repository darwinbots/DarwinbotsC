/***************************************************
Presently, robot physics use something called 'velocity
verlet', which is a technique for integration.

The standard (Euler) method would look like:

vel += Impulse / mass;
pos += vel;

Velocity Verlet (with time step 1) looks like:
pos += vel + 1/2 old Impulse / mass;
vel += (old Impulse + new Impulse) / (2 * mass);

It's supposed to be less explosively unstable.

This technique seems more used in molecular dynamics than
game simulations.  I find very little reference to it
(other than by name as 'another verlet method') in the
video game literature.
*****************************************************/
#include "Robot.h"
#include "..\Common\Vectors.h"
#include "..\Common\Random.h"

//could be implemented as an inline, but this way I don't have to
//worry about type safety
#define CUBE(a) ((a)*(a)*(a))

void RobotPhysics::Integrate()
{
    opos = pos;
    ovel = vel;
    
    Vector3f Impulse = ImpulseIndependant - ImpulseResistive;    
    
    //Resistive Forces are overpowering 
    
    /*if(Impulse.x() > 0)
        ImpulseResistive.setX(0);
    if(Impulse.y() < 0)
        ImpulseResistive.setY(0);
    if(Impulse.z() < 0)
        ImpulseResistive.setZ(0);*/

    /*if(ImpulseStatic > 0)
    {
        Vector4 olddir = Impulse / Length3(Impulse);
        Vector4 newdir;
        Vector4 Static = ImpulseStatic * olddir;
        Impulse -= Static;
        newdir = Impulse / Length3(Impulse);
        if(newdir.x() != olddir.x() ||
           newdir.y() != olddir.y() ||
           newdir.z() != olddir.z())
            Impulse.set(0,0,0);
    }*/
    
    //velocity verlet integration
    pos = opos + vel + 0.5f * oldImpulse / (mass + AddedMass);
    vel += (oldImpulse + Impulse) / (2 * (mass + AddedMass));
    
    oldImpulse = Impulse;
    
    //Used for the fast local search during constraints after physics
    //if(vel == Vector3f(0,0,0))
    //    CollisionActive = false;
    //else
    
    CollisionActive = true;
    
    ImpulseIndependant.set(0,0,0);
    ImpulseResistive.set(0,0,0);
    Impulse.set(0,0,0);
    ImpulseStatic = 0;
    DragScalar = 0;
    
    tempPos = pos;
    tempVel = vel;
}



void RobotPhysics::UpdateAddedMass()
{
    //added mass is a simple enough concept.
    //To move an object through a liquid, you must also move
    //that liquid out of the way.
  
    const double AddedMassCoefficientForASphere = 0.5;
    AddedMass = float(AddedMassCoefficientForASphere * SimOpts.Density * 
                4.0 / 3.0 * double(PI) * CUBE(double(radius)));
}