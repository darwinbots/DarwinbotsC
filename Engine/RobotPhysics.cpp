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

void Robot::NetForces()
{        
    this->UpdateAddedMass();
    this->UpdateMass();
    
    //INDEPENDANT FORCES
    this->VoluntaryForces();
    this->GravityForces();
    this->BouyancyForces();
    this->BrownianForces();
    this->PlanetEaters();

    //tie springs for elastic ties
    //tie angles
    //drag from tie
        
    //RESISTIVE FORCES
    this->BotCollisions();
    //drag from bot
    //friction on bots (no friction on ties)
    //gate forces
    //edge spring forces if edge springs enabled

    if (mass + AddedMass == 0)  // a catch to be sure that we don't have 0 mass
		mass = 0.1f - AddedMass;   
}

void Robot::Constraints()
{
    opos = pos;
    pos = temppos + vel + 0.5f * oldImpulse / (mass + AddedMass);
    vel += (oldImpulse + Impulse) / (2 * (mass + AddedMass));
    oldImpulse = Impulse;
    Impulse.set(0,0,0);

    //RESTRAINTS (done after movement)
    this->EdgeCollisions();  //collisions with edges (if rigid edges are selected)
    //max tie length and rigid ties (if ties are hardened)
    //max velocity restraint

    temppos = pos;
}

void Robot::BotCollisions()
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
                //relaxation collision technique
                //from http://www.gamasutra.com/resource_guide/20030121/jacobson_03.shtml

                /*float CoefficientRestitution = 0.0f;
                
                normal / sqrt(currdist);  //normalize the vector
                Vector4 tangent(normal.x(), -normal.y()); //the tangental vector to the collision plane

                Vector4 velONEInitial(this->pos * tangent, this->pos * normal);
                Vector4 velTWOInitial(rob[x]->pos * tangent, rob[x]->pos * normal);
                
                Vector4 elasticity(1+CoefficientRestitution,
                                   this->mass - CoefficientRestitution * rob[x]->mass);
                elasticity /= (this->mass + rob[x]->mass);

                float vafn = rob[x]->mass * velTWOInitial[1] * elasticity [0] + velONEInitial[1] * elasticity[1];
                float vbfn = this->mass * velONEInitial[1] * elasticity[0] - velTWOInitial[1];

                Vector4 velONEFinal(velONEInitial[0], vafn);
                Vector4 velTWOFinal(velTWOInitial[0], vbfn);

                Vector4 Xnabbytabby(normal.x(), normal.x());
                Vector4 Ynabbytabby(normal.y(), normal.y());

                this->vel.set(velONEFinal * Xnabbytabby, velONEFinal * Ynabbytabby);
                rob[x]->vel.set(velTWOFinal * Xnabbytabby, velTWOFinal * Ynabbytabby);*/

                Vector4 momentum;

                momentum = this->mass * this->vel + rob[x]->mass * rob[x]->vel;
                momentum /= this->mass + rob[x]->mass;

                rob[x]->vel = momentum;
                this->vel = momentum;

                normal *= sqrtf(mindist / currdist) - 1.0f;
                
                rob[x]->temppos += normal * 0.5f;
                this->temppos -= normal * 0.5f;
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

    double Impulse = -SimOpts.Density * (double)this->radius * (double)this->radius * (double)this->radius
                                      * 4.0 / 3.0 * double(PI) * double(SimOpts.YGravity);
    Vector4 temp(0, float(Impulse), 0);
    this->Impulse += temp;
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
        const float CoefficientRestitution = 0.94f;
        if(dist.x() <= this->radius ||
           dist.x() >= SimOpts.FieldDimensions.x() - this->radius)
        {
            //bounce off the wall with a 40% loss of speed
            //I don't know if this is accurate with any sort
            //of physical model, but it looks realistic

            //speed loss in non normal direction of wall
            //represents loss of energy due to friction or
            //rolling or something like that
            
            //set to rest if we're barely moving (stick to walls)
            if (fabs(vel.x()) <= 0.01f)
            {
                vel(0) = 0.0f;                
            }

            vel(0) = -vel.x();
            vel *= CoefficientRestitution;
        }

        if(dist.y() <= this->radius ||
           dist.y() >= SimOpts.FieldDimensions.x() - this->radius)
        {
            if(fabs(vel.y()) <= 0.01f)
                vel(1) = 0.0f;

            vel(1) = -vel.y();
            vel *= CoefficientRestitution;
        }

        this->pos = dist;
    }
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
                4.0 / 3.0 * double(PI) * double(radius * radius * radius));
}