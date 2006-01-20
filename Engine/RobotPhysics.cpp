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

        this->ImpulseInd = this->ImpulseInd - this->ImpulseRes;
                       
        if (mass + AddedMass == 0)  // a catch to be sure that we don't have 0 mass
		    mass = 0.1 - AddedMass;
        
        //we update to a temporary vector instead of the position vector
        //so robots which update after us aren't updating against
        //inivalid information on our position.
        temppos = pos * 2 - opos + ImpulseInd / (mass + AddedMass);

        this->ImpulseInd.set(0,0,0);
        this->ImpulseRes.set(0,0,0);
}

void Robot::Constraints()
{
    //RESTRAINTS (done after movement)
    this->BotCollisions();
    this->EdgeCollisions();  //collisions with edges (if rigid edges are selected)
    //max tie length and rigid ties (if ties are hardened)
    //max velocity restraint
}

/*/*Vector4 vel = opos - pos;
        vt = LengthSquared3(vel);
        SimOpts.MaxSpeed = 60;
		if (vt > SimOpts.MaxSpeed * SimOpts.MaxSpeed)
		{
			vel = vel / sqrt(vt);
			vel = vel * SimOpts.MaxSpeed;
			vt = SimOpts.MaxSpeed * SimOpts.MaxSpeed;
		}*/

void Robot::BotCollisions()
{
    for(int x = 0; x <= MaxRobs; x++)
    {
        if(rob[x] != NULL && rob[x] != this &&
            rob[x]->AbsNum < this->AbsNum)
        {
            Vector4 ab = rob[x]->temppos - this->temppos;
            float mindist = this->radius + rob[x]->radius;
            mindist *= mindist;
            
            if(float currdist = LengthSquared3(ab) < mindist)
            {
                //relaxation collision technique
                //from http://www.gamasutra.com/resource_guide/20030121/jacobson_03.shtml
                
                ab = ab * (mindist / (mindist + currdist));

                //ab is the distance vector that is being overlapped
                
                this->temppos = this->temppos - ab * .5;
                rob[x]->temppos = rob[x]->temppos + ab * .5;
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
    //The Edges are perfectly damped springs that repel bots
        
    Vector4 dist;
    Vector4 radvec(this->radius, this->radius, this->radius);
    
    dist = 
    VectorMin(
    VectorMax(this->temppos, radvec),
    SimOpts.FieldDimensions - radvec); 
    
    if (LengthSquared3(dist) > 0)
        this->temppos = dist;
}
