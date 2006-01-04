#include "Robot.h"
#include "..\Common\Math3D.h"
#include "..\Common\Random.h"

void Robot::NetForces()
{    
    //INDEPENDANT FORCES
        this->VoluntaryForces();
        this->GravityForces();
        this->BouyancyForces();
        this->BrownianForces();
        
        //tie springs for elastic ties
        //tie angles
        //drag from tie
        
    //RESISTIVE FORCES
        //drag from bot
        //friction on bots (no friction on ties)
        //gate forces
        //edge spring forces if edge springs enabled

    //RESTRAINTS (done after movement)
        //collisions with bots
        //collisions with walls
        //collisions with edges (if rigid edges are selected)
        //max tie length and rigid ties (if ties are hardened)
}

//collisions with bots:

//delta = x2-x1
//delta *= restlength^2 / (delta^2 + restlength^2) - botsmass/(our combined mass)
//x1 -= delta;
//x2 += delta;

//above also works for rigid ties

//calculates new acceleration and energy values from robot's
//.up/.dn/.sx/.dx vars
void Robot::VoluntaryForces()
{
    float EnergyCost, mult;
    Vector4 NewAccel, dir;

    if (this->Corpse == true)
        return;

    if (this->NewMove == false)
        mult = this->mass;
    else
        mult = 1;

    dir.set((*this)[dirup] - (*this)[dirdn], (*this)[dirdx] - (*this)[dirsx]);
    dir = dir * mult;

    NewAccel.set(this->aimvector * dir, this->aimvector % dir);

    //NewAccel is the impulse vector formed by the robot's internal "engine".
    //Impulse is the integral of Force over time.

    this->ImpulseInd = this->ImpulseInd + NewAccel * SimOpts.MovingEfficiency;
    EnergyCost = Length3(NewAccel) * SimOpts.Costs[MOVECOST];

    (*this)[dirup] =
    (*this)[dirdn] =
    (*this)[dirdx] =
    (*this)[dirsx] = 0;
}

void Robot::GravityForces()
{
    Vector4 temp(0,1,0);
    
    this->ImpulseInd = this->ImpulseInd + (this->mass * SimOpts.YGravity) * temp;
}

void Robot::BrownianForces()
{
    float Impulse = Gauss(SimOpts.Brownian / 2);
    float RandomAngle = frnd(1, 1256) / 200.0f;
    Vector4 temp(cos(RandomAngle) * Impulse, sin(RandomAngle) * Impulse);    
    this->ImpulseInd += temp;
}

void Robot::BouyancyForces()
{
    if (SimOpts.YGravity == 0)
        return;

    float Impulse = -SimOpts.Density * this->radius * this->radius * this->radius * 4 / 3 * PI * SimOpts.YGravity;
    Vector4 temp(0, Impulse, 0);
    this->ImpulseInd += temp;
}
