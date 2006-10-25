#include "EnergyShot.h"

EnergyShot::EnergyShot()
{
    //ctor
}

EnergyShot::EnergyShot(Robot *parent):Shot(parent)
{
    this->shottype = -2;
    this->color.set(1.0f,1.0f, 1.0f);

    this->value = min((__int16)parent->nrg, (*parent)[shootval]);
    parent->nrg -= this->value;
}

EnergyShot::EnergyShot(Vector3f pos, Vector3f vel, unsigned long age,
                const Robot *parent, float power):Shot(pos, vel, age, parent)
{
    this->shottype = -2;
    this->color.set(0, 1, 1);
    this->value = (__int16) power;
}

EnergyShot::~EnergyShot()
{
    //dtor
}

const float EnergyShot::hit(Robot* target) const
{
    if(!target->Corpse)
    {
        float partial = POWERMULTIPLIER(this->age, this->range) * this->value;

        target->nrg += partial * 0.8f;
        target->Body += partial * 0.019f;
        target->Waste += partial * 0.01f;

        if(target->nrg > 32000)
            target->nrg = 32000;

        if(target->Body > 32000)
            target->Body = 32000;
    }
    return 0;
}

const bool EnergyShot::bouncesOff(const Robot *const target, const float &power) const
{
    return false;
}

Shot* EnergyShot::returnShot(const Robot* target, const float &power) const
{
    throw;
}
