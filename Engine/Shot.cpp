/*************************************************************************************
Shots code is, despite my best efforts, terribly complicated.

Anyone who wants to pull up their sleeves and massage the below code to be smoother,
be my guest.

Numsgil Feb. 09 2006
**************************************************************************************/
#include "Engine.h"
#include "Shot.h"
#include "SimOptions.h"

/****************************************
Presently, shots have the following physical characteristics:

1.  Massless.  Shots have 0 mass
2.  Volumeless.  Shots exist purely as single points

******************************************/

void Shot::CreateShotBasic()
{
    parent = 0;

    range = 9;
    color = Vector3f(1,1,1);
    Memloc = Memval = 0;
    value = shottype = 0;
}

Shot::Shot():ObjectPrimitive()
{
    this->CreateShotBasic();
}

Shot::Shot( Vector3f startPos,
            Vector3f startVel,
            unsigned long startAge,
            const Robot* parent):ObjectPrimitive(startPos, startVel, startAge)
{
    this->CreateShotBasic();
    this->parent = parent->getAbsNum();
}

Shot::Shot(Robot *parent)
{
    this->CreateShotBasic();
    this->parent = parent->getAbsNum();
    this->color  = parent->color;

    float const AngleSpread = 0.35f;

// FIXME (Ronan#1#): Restore random shot direction
    this->pos = parent->getPos() + parent->getRadius() * parent->getAimVector();
    //float angle = (parent->getAim() + AngleSpread * (DBrand() - 0.5f));
    this->vel = parent->getVel() + 40 * parent->getAimVector();
    this->opos = this->pos - vel;
}

Shot::~Shot()
{

}

/**********************************
***********************************
***********************************/

void Shot::UpdatePos()
{
    //Euler integration
    this->opos = this->pos;
    this->vel += Vector3f(0.0f, SimOpts.YGravity);
    this->pos += this->vel;
    ++age;
}

bool Shot::isTooOld()
{
    return (age > range);
}

float Shot::collisionTime(const Robot *const target) const
{
    //check for and handle collisions

    Vector3f m = this->pos - this->vel - target->getPos();
    Vector3f v = this->vel;

        //(m + tv) dot (m + tv) = radius^2
        //(v dot v) t^2 + 2(m dot v) t + (m dot m - radius ^ 2) = 0

    float a = v * v;
    float b = m * v;
    float c = m * m - target->getRadius() * target->getRadius();
    float t = 0;

    float discriminant = b * b - a * c; //factor of 4 has been pre factored out

    if(discriminant >= 0)
    {
            //need to find the time of intersection using quadratic equation
            t = -b / a - discriminant;
            if(t < 0) t = 0; //for some reason the shot never actually entered the sphere
    }
    else throw;//this shouldn't happen, it would mean the shot never really collided

    return t;
}


void Shot::reflect(Robot* collide)
{
    assert(this != NULL && "Attempting to reflect a non existant shot");

    //check for and handle collisions

    Vector3f m = this->pos - this->vel - collide->getPos();
    Vector3f v = this->vel;

        //(m + tv) dot (m + tv) = radius^2
        //(v dot v) t^2 + 2(m dot v) t + (m dot m - radius ^ 2) = 0

    float a = v * v;
    float b = m * v;
    float c = m * m - collide->getRadius() * collide->getRadius();
    float t = 0;

    float discriminant = b * b - a * c; //factor of 4 has been pre factored out

    if(discriminant >= 0)
    {
            //need to find the time of intersection using quadratic equation
            t = -b / a - discriminant;
            if(t < 0) t = 0; //for some reason the shot never actually entered the sphere

            this->pos = this->opos + t * v; //pos = point of contact
            this->opos = this->pos;
    }
    else return;//this shouldn't happen, it would mean the shot never really collided

        //update new velocity
    this->range *= 2;
    this->vel = (collide->getVel() - this->vel / 2); //returned shots have this vector

    t = 1 - t;
        //time is now the remaining time step to move the shot
        //move the shot forward by the remaining time

    this->pos += this->vel * t;
        //this->opos = this->pos - this->vel;
}

Robot* Shot::ShotColl()
{
    //perform checks for torroidal edge wraparound
    Vector3f ab, ac, bc;
    float MagAB, dist;

    ab = this->pos - this->opos;
    MagAB = ab.Length();

    //search through all bots to find one that's collided with us
    for (RobotIterator bot = Engine.robotList->begin(); bot != Engine.robotList->end(); ++bot)
    {
        ac = (*bot)->getPos() - this->opos;
        bc = (*bot)->getPos() - this->pos;

        //The below looks simple and like it makes no sense.
        //It's from an algorithm I only understood when I coded it.
        //It should be error free, but I've had problems with it
        //twice already (once in the VB source, and once when I ported it over)
        //that stemed from me forgetting exactly what it is it's doing.
        //the algorithm is sound, but suspect my implementation if problems
        //are evident.
        //-Numsgil
        if (ab * ac > 0)
        {
                //if AB * AC > 0 then nearest point is point B (present position)
            dist = bc.LengthSquared();
        }
        else if(ab * bc <= 0)
        {
                //'if AB dot BC < 0 then nearest point is point A (older position)
            dist = ac.LengthSquared();
        }
        else if(MagAB > 0)
        {
            //this is only called when a shot was closest to a bot
            //during _transit_ from opos to pos.  As such, it is rarely
            //called
            dist = (ab % ac) * (ab % ac) / MagAB;
        }
        else
        {
            //this is rarely, if ever called.  Primarily
            //an error catching routine
            //the speed of the shot would have to be 0
            dist = bc.LengthSquared();
        }

        if (dist < (*bot)->getRadius() * (*bot)->getRadius() &&
                                            this->parent != (*bot)->getAbsNum())
            return *bot;
    }
    return NULL;
}
