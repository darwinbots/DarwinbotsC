#include "BodyShot.h"
#include "../Engine.h"

BodyShot::BodyShot()
{
    //ctor
}

BodyShot::BodyShot(Robot *parent)
{
    this->shottype = -6;
    this->color = parent->color;

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
        rangemultiplier = logf((*parent)[shootval]) / logf(3);
        extracost = float((*parent)[shootval] - 2);
    }

    parent->ChargeNRG(extracost);

    this->range *= rangemultiplier;

    if(parent->Body > 1000)
        this->value = iceil(powermultiplier * (logf(parent->Body / 100 - 8) / logf(2) * 200.0f));
    else
        this->value = iceil(powermultiplier * (parent->Body / 5));
}

BodyShot::~BodyShot()
{
    //dtor
}

const float BodyShot::hit(Robot* target) const
{
    float power;

    if(SimOpts.EnergyExType == true) power = this->value *
        POWERMULTIPLIER(this->age, this->range) * SimOpts.EnergyProp / 100;
    else power = (float)SimOpts.EnergyFix;

    float Shell = target->Shell * SHELLEFFECTIVENESS;

    if (power > (target->Body * 10) / 0.8f + Shell)
        power = (target->Body * 10) / 0.8f + Shell;

    target->Shell -= power / SHELLEFFECTIVENESS;
    if(target->Shell < 0)
        target->Shell = 0;

    if (power <= Shell)
    {
        return 0;
    }

    power -= Shell;

    if (target->Corpse == true)
    {
        power *= 4; //these shots rock against corpses
        if (power * 0.08f > target->Body)
            power = target->Body / 0.08f;
    }
    else
    {
        target->nrg -= power * 0.2f;
        target->Body -= power * 0.08f;

        if (target->nrg <= 0.0f)
            power += target->nrg;

        if (target->Body <= 0.0f)
            power += target->Body;
    }

    /*if (target->Body <= 0 || target->nrg <= 0)
    {
        Robot *temp = Engine.getRobot(this->parent);
        if(temp)
            temp->Kills++;
    }*/

    return power;
}

const bool BodyShot::bouncesOff(const Robot *const target, const float &power) const
{
    return (abs(power) > minShotPower);
}

Shot* BodyShot::returnShot(const Robot* target, const float &power) const
{
    Vector3f newVel = target->getVel()
                        + returnShotVelocityFactor * (target->getVel() - vel);
    float t = collisionTime(target);
    Vector3f newPos = opos + t * vel + (1-t) * newVel;
    return new EnergyShot(newPos, newVel, 0, target, power);
}
