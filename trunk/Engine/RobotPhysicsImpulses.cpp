#include "Robot.h"
#include "RobotPhysics.h"

#define CUBE(a) ((a)*(a)*(a))

//Calculates the forces on a robot, but not the constraints (which must be satisfied
//in a particular way to work properly)
void RobotPhysics::NetForces(Robot *me)
{        
    this->me = me;
    
    this->UpdateAddedMass();
    me->UpdateMass();

    if (mass + AddedMass == 0)  // a catch to be sure that we don't have 0 mass
		mass = 0.1f;
    
    IndependantForces();
    ResistiveForces();
}

void RobotPhysics::IndependantForces()
{
    if(!me->Corpse) this->VoluntaryForces();
    this->GravityForces();
    this->BouyancyForces();
    this->BrownianForces();
    if(SimOpts.PlanetEatersG != 0) this->PlanetEaters();
    
    //Tie Forces (if such things exist)
}

void RobotPhysics::ResistiveForces()
{
    if(SimOpts.ZeroMomentum)
        this->vel.set(0,0,0);
    
    //drag from tie
    this->Drag();
    this->Friction();
    //gate forces
}

//calculates new acceleration and energy values from robot's
//.up/.dn/.sx/.dx vars
void RobotPhysics::VoluntaryForces()
{
    float EnergyCost, mult;
    Vector3f NewAccel, dir;
    
    mult = me->NewMove ? mass : 1;
    
    dir.set(float((*me)[dirright] - (*me)[dirleft]),
            float((*me)[dirup] - (*me)[dirdn]), 0);
    
    dir = dir * mult;
    
    NewAccel.set(me->aimvector % dir, me->aimvector * dir);
    
    //NewAccel is the impulse vector formed by the robot's internal "engine".
    //Impulse is the integral of Force over time.
    
    this->ImpulseIndependant += NewAccel * SimOpts.MovingEfficiency / 100.0f;
    EnergyCost = dir.Length() * SimOpts.Costs[MOVECOST];
    me->ChargeNRG(EnergyCost);
    
    (*me)[dirup] =
    (*me)[dirdn] =
    (*me)[dirright] =
    (*me)[dirleft] = 0;
}

void RobotPhysics::GravityForces()
{
    this->ImpulseIndependant -= (this->mass * SimOpts.YGravity) * Vector3f(0,1);
}

void RobotPhysics::BrownianForces()
{
    float Impulse = Gauss(SimOpts.Brownian / 2);
    float RandomAngle = frnd(1, 1256) / 200.0f;
    this->ImpulseIndependant += Vector3f(cosf(RandomAngle) * Impulse, sinf(RandomAngle) * Impulse);
}

void RobotPhysics::BouyancyForces()
{
    if (SimOpts.YGravity == 0)
        return;

    double Impulse = -SimOpts.Density * CUBE((double)this->radius)
                                      * 4.0 / 3.0 * double(PI) * double(SimOpts.YGravity);
    
    this->ImpulseIndependant += Vector3f(0, float(Impulse));
}

void RobotPhysics::PlanetEaters()
{
    for(int x = 0; x <= MaxRobs; x++)
    {
        if(rob[x] != NULL && rob[x]->AbsNum < me->AbsNum)
        {
            Vector3f PosDiff = rob[x]->pos - this->pos;
            float mag = PosDiff.LengthSquared();
            if(mag != 0)
            {
                float force = (SimOpts.PlanetEatersG * 1000 * rob[x]->mass * this->mass) / mag;

                PosDiff = PosDiff / sqrtf(mag) * force;

                rob[x]->ImpulseIndependant -= PosDiff;
                this->ImpulseIndependant   += PosDiff;
            }            
        }
    }
}



void RobotPhysics::Friction()
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

float SphereCD(float mag, float rad)
{
    #pragma warning(disable : 4244)
    //computes the coeficient of drag for a spehre given the unit reynolds in simopts
    //totally ripped from an online drag calculator.
    //http://www.fluidmech.net/jscalc/cdre01.htm
    //could do with a double check from the source above

    if(SimOpts.Viscosity == 0)
        return 0;

    float Reynolds, y11, y12, y13, y1, y2, alpha;

    Reynolds = rad * rad * 2 * mag * SimOpts.Density / SimOpts.Viscosity;

    if(Reynolds == 0)
        return 0;

    y11 = 24 / (300000);
    y12 = 6 / (1 + sqrt(300000.0));
    y13 = 0.4f;

    y1 = y11 + y12 + y13;
    y2 = 0.09f;

    alpha = (y2 - y1) * pow(50000.0, -2.0);

    if(Reynolds < 300000)
        return 24 / Reynolds + 6 / (1 + sqrt(Reynolds)) + 0.4;
    else if(Reynolds < 350000)
        return alpha * pow((Reynolds - (300000)), 2) + y1;
    else if(Reynolds < 600000)
        return 0.09f;
    else if(Reynolds < 4000000)
        return powf(Reynolds / (600000.0), 0.55f) * y2;
    else
        return 0.255f;
    #pragma warning(default : 4244)
}

void RobotPhysics::Drag()
{
    if(vel == Vector3f(0,0,0))
        return;
    
    float magnitude = vel.LengthSquared();
    
    DragScalar = float(0.5 * (double)SphereCD(sqrt(magnitude), radius) * SimOpts.Density * 
                    (double)magnitude * (double)PI * double(radius * radius));
}