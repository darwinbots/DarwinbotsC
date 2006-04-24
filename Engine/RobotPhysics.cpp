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

#define CUBE(a) (a*a*a)

void Robot::NetForces()
{        
    this->UpdateAddedMass();
    this->UpdateMass();

    if (mass + AddedMass == 0)  // a catch to be sure that we don't have 0 mass
		mass = 0.1f;
    
    if(SimOpts.ZeroMomentum)
        this->vel.set(0,0,0);
    
    //INDEPENDANT FORCES
    this->VoluntaryForces();
    this->GravityForces();
    this->BouyancyForces();
    this->BrownianForces();
    if(SimOpts.PlanetEaters && SimOpts.PlanetEatersG > 0) this->PlanetEaters();

    this->SpringForces();
    //tie angles
    
        
    //RESISTIVE FORCES
    this->BotCollisionsVel();
    //drag from tie
    //drag from bot
    this->Friction();
    //gate forces
}

void Robot::Integrate()
{
    opos = pos;
    ovel = vel;

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
    Impulse.set(0,0,0);
    ImpulseStatic = 0;
}

//sets a hard constraint that pulls bots that are too close to each other apart
float Robot::BotCollisionsPos()
{
    float maxoverlap = 0.0f;
    for(int x = 0; x <= MaxRobs; x++)
    {
        if(rob[x] != NULL && rob[x]->AbsNum < this->AbsNum)
        {
            Vector3f normal = rob[x]->pos - this->pos;
            
            float mindist = this->radius + rob[x]->radius;
            mindist *= mindist;
                        
            float currdist = normal.LengthSquared();
            
            if(currdist < mindist)
            {
                if(currdist < 1)
                {
                    currdist = 1;
                    normal.set(1, 1);
                }

                float overlap = sqrtf(mindist / currdist) - 1.0f;
                
                //this below would be faster if we didn't do more than one iteration of position collision a cycle
                //float overlap = (mindist) / (currdist + mindist) - 0.5f;
                
                if(overlap > maxoverlap)
                    maxoverlap = overlap;
                
                //UPDATE POSITIONS
                normal *= overlap;
                
                //these need to be modified to deal with
                //fixed/unfixed pairs
                rob[x]->pos += normal * 0.5f;
                this->pos -= normal * 0.5f;
            }
        }
    }

    return maxoverlap;
}

void Robot::VelocityCap()
{
    if (this->vel.LengthSquared() > SimOpts.MaxSpeed * SimOpts.MaxSpeed)
        this->vel = this->vel.Normal() * (float)SimOpts.MaxSpeed;
}

void Robot::EdgeCollisions()
{
    //The Edges are perfectly damped springs that repel bots
        
    Vector3f dist;
    Vector3f radvec(this->radius, this->radius);
    
    dist = 
    VectorMin(
    VectorMax(this->pos, radvec),
    SimOpts.FieldDimensions - radvec); 
    
    const float CoefficientRestitution = 0.95f;
    
    if(this->pos.x() < this->radius ||
       this->pos.x() > SimOpts.FieldDimensions.x() - this->radius)
    {
        vel(0) = -ovel.x();
        vel *= CoefficientRestitution;            
    }

    if(this->pos.y() < this->radius ||
       this->pos.y() > SimOpts.FieldDimensions.y() - this->radius)
    {
        vel(1) = -ovel.y();
        vel *= CoefficientRestitution;            
    }

    //speed loss in non normal direction of wall
    //represents loss of energy due to friction or
    //rolling or something like that
    
    this->pos = dist;
}

void Robot::FulfillTieConstraints()
{



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
    for(int x = 0; x <= MaxRobs; x++)
    {
        if(rob[x] != NULL && rob[x]->AbsNum < this->AbsNum)
        {
            Vector3f normal = rob[x]->pos - this->pos;
            float mindist = this->radius + rob[x]->radius;
            mindist *= mindist;
                        
            float currdist = normal.LengthSquared();
            
            if(currdist < mindist)
            {
                //UPDATE CHANGES IN VELOCITY
                const float e  = SimOpts.ElasticCoefficient = 0.5f;
                const float M1 = this->mass;
                const float M2 = rob[x]->mass;
                
                normal /= sqrtf(currdist); //normalize normal vector

                Vector3f V1 = (this->vel * normal) * normal;
                Vector3f V2 = (rob[x]->vel * normal) * normal;

                Vector3f V1f = ((e + 1.0f) * M2 * V2 + V1 * (M1 - e * M2))/
                            (M1 + M2);
                
                Vector3f V2f = ((e + 1.0f) * M1 * V1 + V2 * (M2 - e * M1))/
                            (M1 + M2);
                
                this->vel = V1f + (this->vel - V1);
                rob[x]->vel = V2f + (rob[x]->vel - V2);
            }
        }
    }
}

//calculates new acceleration and energy values from robot's
//.up/.dn/.sx/.dx vars
void Robot::VoluntaryForces()
{
    float EnergyCost, mult;
    Vector3f NewAccel, dir;
    
    if (this->Corpse == true)
        return;
    
    if (this->NewMove == false)
        mult = this->mass;
    else
        mult = 1;
    
    dir.set(float((*this)[dirright] - (*this)[dirleft]),
            float((*this)[dirup] - (*this)[dirdn]), 0);
    
    dir = dir * mult;
    
    NewAccel.set(aimvector % dir, aimvector * dir);
    
    //NewAccel is the impulse vector formed by the robot's internal "engine".
    //Impulse is the integral of Force over time.
    
    this->Impulse += NewAccel * SimOpts.MovingEfficiency / 100.0f;
    EnergyCost = dir.Length() * SimOpts.Costs[MOVECOST];
    this->ChargeNRG(EnergyCost);
    
    (*this)[dirup] =
    (*this)[dirdn] =
    (*this)[dirright] =
    (*this)[dirleft] = 0;
}

void Robot::GravityForces()
{
    Vector3f temp(0,1,0);
    
    this->Impulse -= (this->mass * SimOpts.YGravity) * temp;
}

void Robot::BrownianForces()
{
    float Impulse = Gauss(SimOpts.Brownian / 2);
    float RandomAngle = frnd(1, 1256) / 200.0f;
    Vector3f temp(cosf(RandomAngle) * Impulse, sinf(RandomAngle) * Impulse);    
    this->Impulse += temp;
}

void Robot::BouyancyForces()
{
    if (SimOpts.YGravity == 0)
        return;

    double Impulse = -SimOpts.Density * CUBE((double)this->radius)
                                      * 4.0 / 3.0 * double(PI) * double(SimOpts.YGravity);
    Vector3f temp(0.0f, float(Impulse), 0.0f);
    this->Impulse += temp;
}

void Robot::PlanetEaters()
{
    for(int x = 0; x <= MaxRobs; x++)
    {
        if(rob[x] != NULL && rob[x]->AbsNum < this->AbsNum)
        {
            Vector3f PosDiff = rob[x]->pos - this->pos;
            float mag = PosDiff.LengthSquared();
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

void Robot::Friction()
{
    //the below uses the min of vel and ZGravity * CoefficientKinetic for
    //stability.  Bots that begin to reach 0 will still overjump 0 a little
    //bit, but it's a stable oscillation which approaches 0.
    if(vel.LengthSquared() > 0)
    {
        float length = vel.Length();
        if(SimOpts.ZGravity * SimOpts.CoefficientKinetic <= length)
            vel -= SimOpts.ZGravity * SimOpts.CoefficientKinetic * (vel / length);
        else
            vel.set(0,0,0);
        
    }
    else
    {
        this->ImpulseStatic = SimOpts.ZGravity *
                              this->mass *
                              SimOpts.CoefficientStatic;
    }
}

void Robot::SpringForces()
{
    for(unsigned int x = 0; x < Ties.size(); x++)
        if(Ties[x] != NULL)
        {
            if(Ties[x]->FindOther(this)->AbsNum < AbsNum)
            {
                Vector3f Imp = Ties[x]->SpringForces(this);
                Impulse += Imp;
                Ties[x]->FindOther(this)->Impulse -= Imp;
            }
        }
}

Vector3f Tie::SpringForces(Robot *caller)
{
    Vector3f dist = caller->pos - FindOther(caller)->pos;

    this->NaturalLength = max(sender->rad() + receiver->rad(), this->NaturalLength);

    if(dist.LengthSquared() == NaturalLength * NaturalLength)
        return Vector3f(0,0,0);

    float length = dist.Length();
    dist /= length;

    Vector3f Impulse(0,0,0);
    
    Impulse += k * (NaturalLength - length) * dist;
    Impulse += dist * (caller->vel - FindOther(caller)->vel) * -b * dist;

    return Impulse;
}