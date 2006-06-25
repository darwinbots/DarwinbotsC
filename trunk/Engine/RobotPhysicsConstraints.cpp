#include "RobotPhysics.h"

void RobotPhysics::SoftConstraints()
{
    //order is important, done from least to most important:
    
    VelocityCap();   
    FulfillTieConstraintsVel();
    BotCollisionsVel();
    FulfillTieConstraintsPos();
}

void RobotPhysics::VelocityCap()
{
    if (tempVel.LengthSquared() > SimOpts.MaxSpeed * SimOpts.MaxSpeed)
        this->vel += tempVel.Normal() * (float)SimOpts.MaxSpeed - tempVel;
}

void RobotPhysics::FulfillTieConstraintsVel()
{



}

void RobotPhysics::FulfillTieConstraintsPos()
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
"Real 2D Object-to-Object Collision Response (Advanced)"

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

void RobotPhysics::BotCollisionsVel()
{
    for(int x = 0; x <= MaxRobs; x++)
    {
        if(rob[x] != NULL && rob[x]->AbsNum < me->AbsNum)
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

                Vector3f V1 = (this->tempVel * normal) * normal;
                Vector3f V2 = (rob[x]->tempVel * normal) * normal;

                Vector3f V1f = ((e + 1.0f) * M2 * V2 + V1 * (M1 - e * M2))/
                            (M1 + M2);
                
                Vector3f V2f = ((e + 1.0f) * M1 * V1 + V2 * (M2 - e * M1))/
                            (M1 + M2);
                
                this->vel += V1f - V1;
                rob[x]->vel += V2f - V2;
            }
        }
    }
}

/************************************
Hard Constraints
************************************/

//sets a hard constraint that pulls bots that are too close to each other apart
//changes by angelo
float RobotPhysics::BotCollisionsPos()
{
    float maxoverlap = 0.0f;
    bool collide = false;
    for(int x = 0; x <= MaxRobs; x++)
    {
        if(rob[x] != NULL && rob[x]->AbsNum != me->AbsNum) //if i'm a robot, consider me
        {
            Vector3f normal = rob[x]->pos - this->pos;
            
            float mindist = me->radius + rob[x]->radius;
            mindist *= mindist;
                        
            float currdist = normal.LengthSquared();
            
            //The +1 is a fudge factor to take into account
            //floating point inacuracies
            if(currdist + 1 < mindist) //bots colliding...activate both bots
            {
                collide = true;
                rob[x]->CollisionActive = true;
				this->CollisionActive = true;
				
                if(currdist < 1)
                {
                    currdist = 1;
                    normal.set(0, 1);
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

    if(collide == false)
        CollisionActive = false;

    return maxoverlap;
}

void RobotPhysics::EdgeCollisions()
{
    //The Edges are perfectly damped springs that repel bots
        
    Vector3f dist;
    Vector3f radvec(this->radius, this->radius);
    
    dist = 
    VectorMin(
    VectorMax(this->pos, radvec),
    SimOpts.FieldDimensions - radvec); 
    
    const float CoefficientRestitution = 0.95f;
    
    if(this->pos.x() < this->radius - .1 ||
       this->pos.x() - .1 > SimOpts.FieldDimensions.x() - this->radius)
    {
        vel(0) = -ovel.x();
        vel *= CoefficientRestitution;
        CollisionActive = true;
    }

    if(this->pos.y() < this->radius - .1 ||
       this->pos.y() - .1 > SimOpts.FieldDimensions.y() - this->radius)
    {
        vel(1) = -ovel.y();
        vel *= CoefficientRestitution;
        CollisionActive = true;
    }

    //speed loss in non normal direction of wall
    //represents loss of energy due to friction or
    //rolling or something like that
    
    this->pos = dist;
}