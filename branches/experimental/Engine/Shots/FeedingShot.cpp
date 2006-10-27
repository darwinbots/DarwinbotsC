#include "../Robot.h"

#include "FeedingShot.h"

FeedingShot::FeedingShot():Shot()
{
    //ctor
}

FeedingShot::FeedingShot(Robot* parent):Shot(parent)
{
    this->shottype = -1;

    float rangemultiplier = 1.0f;
    float powermultiplier = 1.0f;
    float extracost = 0.0f;

    if((*parent)[shootval] > 2)
    {
        powermultiplier = logf((*parent)[shootval]) / logf(2);
        extracost = float((*parent)[shootval] - 2);
    }
    else if((*parent)[shootval] < -2)
    {
        (*parent)[shootval] = abs((*parent)[shootval]);
        rangemultiplier = logf((*parent)[shootval]) / logf(2);
        extracost = float((*parent)[shootval] - 2);
    }

    parent->ChargeNRG(extracost);

    this->range *= rangemultiplier;

    if(parent->Body > 1000)
        this->value = iceil(powermultiplier * (logf(parent->Body / 100 - 8) / logf(2) * 200.0f));
    else
        this->value = iceil(powermultiplier * (parent->Body / 5));
}

FeedingShot::~FeedingShot()
{
    //dtor
}

const float FeedingShot::hit(Robot* target) const
{
    float power;

    if(SimOpts.EnergyExType == true) power = this->value *
        POWERMULTIPLIER(this->age, this->range) * SimOpts.EnergyProp / 100;
    else power = (float)SimOpts.EnergyFix;

    if(power < 0)
        return 0;
    if(target->Corpse)
        power *= 0.5f; //half power against corpses.  Most of your shot is wasted

    if(power > target->nrg / 0.9f + target->Poison)
       power =  target->nrg / 0.9f + target->Poison;

    if(target->Poison > power)//create poison shot
    {
        target->Poison -= power * 0.9f;
        if(target->Poison < 0) assert(false);
        power *= -1;   //negative power means poisoning
    }
    else
    {
        target->nrg -= power * 0.9f;
        if(target->nrg < 0)
            power += target->nrg / 0.9f;

        target->Body -= power * 0.01f;
        if(target->Body < 0)
            power += target->Body / 0.01f;

        if(power < 0)       //Shouldn't happen !
            power = 0.0f;
    }
    /*if (collide->Body <= 0 || collide->nrg <= 0)
    {
        Robot *temp = Engine.getRobot(this->parent);
        if(temp)
            temp->Kills++;
    }*/
    return power;
}

const bool FeedingShot::bouncesOff(const Robot *const target, const float &power) const
{
    return (abs(power) > minShotPower);
}

Shot* FeedingShot::returnShot(const Robot* target, const float &power) const
{
    if (power < 0)
        return returnPoison(target, -power);
    else
        return returnEnergy(target, power);
}

PoisonShot* FeedingShot::returnPoison(const Robot* target, const float &power) const
{
    Vector3f newVel = target->getVel()
                        + returnShotVelocityFactor * (target->getVel() - vel);
    float t = collisionTime(target);
    Vector3f newPos = opos + t * vel + (1-t) * newVel;
    return new PoisonShot(newPos, newVel, 0, target, power);
}

EnergyShot* FeedingShot::returnEnergy(const Robot* target, const float &power) const
{
    Vector3f newVel = target->getVel()
                        + returnShotVelocityFactor * (target->getVel() - vel);
    float t = collisionTime(target);
    Vector3f newPos = opos + t * vel + (1-t) * newVel;
    return new EnergyShot(newPos, newVel, 0, target, power);
}