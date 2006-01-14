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
        this->BotCollisions();
        this->EdgeCollisions();  //collisions with edges (if rigid edges are selected)
        //max tie length and rigid ties (if ties are hardened)

        this->ImpulseInd = this->ImpulseInd - this->ImpulseRes;
        this->ImpulseRes.set(0,0,0);
}

void Robot::BotCollisions()
{
    for(int x = 0; x < MaxRobs; x++)
    {
        if(rob[x] != NULL && rob[x] != this &&
            rob[x]->AbsNum < this->AbsNum)
        {
            Vector4 ab = rob[x]->pos - this->pos;
            float mindist = this->radius + rob[x]->radius;
            mindist *= mindist;
            
            if(float currdist = LengthSquared3(ab) < mindist)
            {
                //relaxation collision technique
                //from http://www.gamasutra.com/resource_guide/20030121/jacobson_03.shtml
                //velocity changes should be handled wherever position is changed
                //(that is, it's autohandled by verlet integration)

                //I don't know how to incorporate relative masses into this
                ab = ab * ((mindist / (mindist + currdist)) - .9);//this->mass/(this->mass + rob[x]->mass));
                
                //this->pos = this->pos - ab - this->pos;
                //rob[x]->pos = rob[x]->pos + ab;
            }
        }
    }
}

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
    
    this->ImpulseInd = this->ImpulseInd - (this->mass * SimOpts.YGravity) * temp;
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

void Robot::EdgeCollisions()
{
    //'treat the borders as spongy ground
    //'that makes you bounce off.
    
    Vector4 dist;
    
    dist = this->pos - 
    VectorMin(
    VectorMax(this->pos, Vector4(0,0,0)),
    SimOpts.FieldDimensions); 
    
    if (LengthSquared3(dist) > 0)
        this->ImpulseRes -= dist * -.1f;
}
