/*************************************************************************************
Shots code is, despite my best efforts, terribly complicated.

Anyone who wants to pull up their sleeves and massage the below code to be smoother,
be my guest.

Numsgil Feb. 09 2006
**************************************************************************************/
#include "Engine.h"
#include "Shot.h"
#include "SimOptions.h"
#include "Robot.h"
#include "../Common/Math2D.h"

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

    const float AngleSpread = 0.35f;

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


float Shot::collisionTime(const Robot *const target, float maxSpeed) const
{
    static const float noCollision = 2.;
    if (target->getAbsNum() == this->parent ) //bots don't collide with their own shots
    {
        return noCollision;
    }

    Vector2 shotStart = this->opos;


    Vector2 r = shotStart - Vector2(target->getPos());
        //(r + tv) dot (r + tv) = radius^2
        //(v dot v) t^2 + 2(r dot v) t + (r dot r - radius ^ 2) = 0
    float maxDist = target->getRadius() + maxSpeed;
    if (abs(r.x()) >= maxDist || abs(r.y()) >= maxDist )
    {
        return noCollision;
    }
    float c = r.lengthSquared() - target->getRadius() * target->getRadius();
    if (c <= 0)  //means that the shot was already inside
    {
        return 0.;
    }

    Vector2 v = this->vel - target->getVel();
    float rv = r * v;
    if (rv >= 0) //Shot is moving away from the bot, so no collision
    {
        return noCollision;
    }
    float v2 = v.lengthSquared();

    float discriminant = rv * rv - v2 * c; //factor of 4 has been pre factored out

    if(discriminant > 0)
    {
        //need to find the time of intersection using quadratic equation
        float t = (-rv - sqrt(discriminant))/ v2;
        if(t < 0 || t > 1 ) t = noCollision; //for some reason the shot never actually entered the sphere
        return t;
    }
    else assert("Illogical shot collision");//shouldn't happen

    return noCollision;
}
/*
Robot* Shot::ShotColl()
{
    Vector2 shotStart = this->opos;
    Vector2 shotVel = this->vel;
    Robot* target = NULL;
    float minTime = 2.;
    float diffVelMajorant = shotVel.length() + SimOpts.MaxSpeed;
    for (RobotIterator bot = Engine.robotList->begin(); bot != Engine.robotList->end(); ++bot)
    {
        Vector2 botStart = (*bot)->getOldPos();
        Vector2 diffStart = shotStart - botStart;
        float maxDist = (*bot)->getRadius() + diffVelMajorant;
        if (abs(diffStart.x()) > maxDist || abs(diffStart.y()) > maxDist ||
            (*bot)->getAbsNum() == this->parent)
            continue;
        float dsSquared = diffStart.lengthSquared();
        if (dsSquared < (*bot)->getRadius() * (*bot)->getRadius())
        {
            target = *bot;
            minTime = 0.;
            break;
        }
        else
        {
            Vector2 botVel = (*bot)->getVel();
            Vector2 diffVel = shotVel - botVel;
            float pScal = diffVel*diffStart;
            if (pScal >= 0)
                continue;
            float dvSquared = diffVel.lengthSquared();
            if (pScal < - dvSquared ||
                    sqrt(dvSquared) + sqrt(dsSquared) > (*bot)->getRadius() ||
                    dvSquared <.0001f)
                continue;
            if ((dsSquared - (pScal*pScal)/dvSquared) < (*bot)->getRadius() * (*bot)->getRadius())
            {
                float thisTime = -pScal/dvSquared;
                if (thisTime < minTime)
                {
                    minTime = thisTime;
                    target = *bot;
                }
            }
        }
    }
    return target;
}
*/
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
