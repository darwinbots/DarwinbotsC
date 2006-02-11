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
#include "..\Common\Math3D.h"
#include "..\Common\Random.h"

#define CUBE(a) (a*a*a)

void Robot::NetForces()
{        
    this->UpdateAddedMass();
    this->UpdateMass();

    if (mass + AddedMass == 0)  // a catch to be sure that we don't have 0 mass
		mass = 0.1f - AddedMass;
    
    //INDEPENDANT FORCES
    this->VoluntaryForces();
    this->GravityForces();
    this->BouyancyForces();
    this->BrownianForces();
    this->PlanetEaters();

    //tie springs for elastic ties (ie: young ties)
    //tie angles
    //drag from tie
        
    //RESISTIVE FORCES
    this->BotCollisionsVel();
    //drag from bot
    //friction on bots (no friction on ties)
    //gate forces
    //edge spring forces if edge springs enabled
}

void Robot::Integrate()
{
    opos = pos;
    ovel = vel;

    //velocity verlet integration
    pos = opos + vel + 0.5f * oldImpulse / (mass + AddedMass);
    vel += (oldImpulse + Impulse) / (2 * (mass + AddedMass));
    oldImpulse = Impulse;
    Impulse.set(0,0,0);
}

//sets a hard constraint that pulls bots that are too close to each other apart
void Robot::BotCollisionsPos()
{
    for(unsigned int x = 0; x <= MaxRobs; x++)
    {
        if(rob[x] != NULL && rob[x]->AbsNum < this->AbsNum)
        {
            Vector4 normal = rob[x]->pos - this->pos;
            float mindist = this->radius + rob[x]->radius;
            mindist *= mindist;
                        
            float currdist = LengthSquared3(normal);
            
            if(currdist < mindist)
            {
                //UPDATE POSITIONS
                normal *= sqrtf(mindist / currdist) - 1.0f;
                
                //these need to be modified to deal with differences in mass
                //and fixed/unfixed pairs
                rob[x]->pos += normal * 0.51f;
                this->pos -= normal * 0.51f;
            }
        }
    }
}

void Robot::VelocityCap()
{
    //if (LengthSquared3(this->vel) > SimOpts.MaxSpeed * SimOpts.MaxSpeed)
    //    this->vel = Normalize3(this->vel) * (float)SimOpts.MaxSpeed;
}

void Robot::EdgeCollisions()
{
    //The Edges are perfectly damped springs that repel bots
        
    Vector4 dist;
    Vector4 radvec(this->radius, this->radius, 0);
    
    dist = 
    VectorMin(
    VectorMax(this->pos, radvec),
    SimOpts.FieldDimensions - radvec); 
    
    if (LengthSquared3(dist) > 0)
    {
        const float CoefficientRestitution = 0.99f;
        //any coefficients > 0.5 results in perpetual bouncing
        //I'm not sure exactly how to fix this problem

        if(dist.x() <= this->radius ||
           dist.x() >= SimOpts.FieldDimensions.x() - this->radius)
        {
            vel(0) = -ovel.x();
            vel *= CoefficientRestitution;            
        }

        if(dist.y() <= this->radius ||
           dist.y() >= SimOpts.FieldDimensions.x() - this->radius)
        {
            vel(1) = -ovel.y();
            vel *= CoefficientRestitution;            
        }

        //bounce off the wall with a loss of speed
        //I don't know if this is accurate with any sort
        //of physical model, but it looks realistic

        //speed loss in non normal direction of wall
        //represents loss of energy due to friction or
        //rolling or something like that
        
        this->pos = dist;
    }
}

/*Collisions are modified by a slider
that changes the value of e between [0,1].

e = (V2Final - V1Final)
    -----------------------
    (V2Initial - V1Initial)

where velocities are along vector between bot1 and bot2

e = 0 represents inelastic collisions
e = 1 represents perfectly elastic collisions

the algorithm for implementing this is detailed in
Tricks of the Windows game programming gurus 2nd edition
by Andre LaMothe
page 847
"Real 2D Object-to-Object Collision Response (Advanced)

Basically, the algorithm looks like:
1.  Compute normal and tangent unit vectors to collision (n and t)
2.  Transform the spheres' velocities into velocities along
    n and t.

3.  V1final = (e+1)M2V2 + V1(M1 - eM2)
              ------------------------
                        M1 + M2
    V2final = (e+1)M1V1 - V2(M1 - eM2)
              ------------------------
                        M1 + M2

4.  De-transform the velocities from n and t back into the cartesian
    system.

SimOpts.ElasticCoefficient represents e

Also, see http://en.wikipedia.org/wiki/Coefficient_of_restitution
which Numsgil heavily contributed to.
*/

//unresolved question: should I use added mass
//as part of the momentum equation for collisions?
void Robot::BotCollisionsVel()
{
    for(unsigned int x = 0; x <= MaxRobs; x++)
    {
        if(rob[x] != NULL && rob[x]->AbsNum < this->AbsNum)
        {
            Vector4 normal = rob[x]->pos - this->pos;
            float mindist = this->radius + rob[x]->radius;
            mindist *= mindist;
                        
            float currdist = LengthSquared3(normal);
            
            if(currdist < mindist)
            {
                //UPDATE CHANGES IN VELOCITY
                const float e  = SimOpts.ElasticCoefficient = 0.0f;
                const float M1 = this->mass;
                const float M2 = rob[x]->mass;
                
                normal /= sqrtf(currdist); //normalize normal vector

                Vector4 V1 = this->vel;// * normal;
                Vector4 V2 = rob[x]->vel;// * normal;

                Vector4 V1f = (M1 * V1 + M2 * V2) / (M1 + M2);
                Vector4 V2f = V1f;
                
                /*float V1f = (e + 1.0f) * M2 * V2 + V1 * (M1 - e * M2)/
                            (M1 + M2);
                
                float V2f = (e + 1.0f) * M1 * V1 + V2 * (M2 - e * M1)/
                            (M1 + M2);*/
                
                this->vel = V1f;
                rob[x]->vel = V2f;

                /*
                this->Impulse   = this->mass   * (V1f - V1);// * normal;
                rob[x]->Impulse = rob[x]->mass * (V2f - V2);// * normal;
                */
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

    dir.set(float( (*this)[dirup] - (*this)[dirdn]), float((*this)[dirdx] - (*this)[dirsx]));
    dir = dir * mult;

    NewAccel.set(this->aimvector * dir, this->aimvector % dir);

    //NewAccel is the impulse vector formed by the robot's internal "engine".
    //Impulse is the integral of Force over time.

    this->Impulse += NewAccel * SimOpts.MovingEfficiency;
    EnergyCost = Length3(NewAccel) * SimOpts.Costs[MOVECOST];
    this->ChargeNRG(EnergyCost);

    (*this)[dirup] =
    (*this)[dirdn] =
    (*this)[dirdx] =
    (*this)[dirsx] = 0;
}

void Robot::GravityForces()
{
    Vector4 temp(0,1,0);
    
    this->Impulse -= (this->mass * SimOpts.YGravity) * temp;
}

void Robot::BrownianForces()
{
    float Impulse = Gauss(SimOpts.Brownian / 2);
    float RandomAngle = frnd(1, 1256) / 200.0f;
    Vector4 temp(cosf(RandomAngle) * Impulse, sinf(RandomAngle) * Impulse);    
    this->Impulse += temp;
}

void Robot::BouyancyForces()
{
    if (SimOpts.YGravity == 0)
        return;

    double Impulse = -SimOpts.Density * CUBE((double)this->radius)
                                      * 4.0 / 3.0 * double(PI) * double(SimOpts.YGravity);
    Vector4 temp(0, float(Impulse), 0);
    this->Impulse += temp;
}

void Robot::PlanetEaters()
{
    for(unsigned int x = 0; x <= MaxRobs; x++)
    {
        if(rob[x] != NULL && rob[x]->AbsNum < this->AbsNum)
        {
            Vector4 PosDiff = rob[x]->pos - this->pos;
            float mag = LengthSquared3(PosDiff);
            if(mag != 0)
            {
                float force = (SimOpts.PlanetEatersG * rob[x]->mass * this->mass) / (mag);

                PosDiff = PosDiff / sqrtf(mag) * force;

                rob[x]->Impulse -= PosDiff;
                this->Impulse   += PosDiff;
            }            
        }
    }
}

void Robot::UpdateAddedMass()
{
    //added mass is a simple enough concept.
    //To move an object through a liquid, you must also move
    //that liquid out of the way.
  
    const double AddedMassCoefficientForASphere = 0.5;
    AddedMass = float(AddedMassCoefficientForASphere * SimOpts.Density * 
                4.0 / 3.0 * double(PI) * CUBE(double(radius)));
}