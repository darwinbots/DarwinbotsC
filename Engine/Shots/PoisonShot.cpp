#include "../Robot.h"

#include "PoisonShot.h"

PoisonShot::PoisonShot()
{
    //ctor
}

PoisonShot::PoisonShot(Vector3f pos, Vector3f vel, unsigned long age,
                const Robot *parent, __int16 power):Shot(pos, vel, age, parent)
{
    this->shottype = -5;
    this->color.set(0, 1, 1);
    this->value = power;
}

PoisonShot::PoisonShot(Robot *parent, __int16 power):Shot(parent)
{
    this->age = 0;
    this->shottype = -5;
    this->color.set(0, 1, 1);

    this->value = min((__int16)parent->Poison, power);
    parent->Poison -= this->value;
}

PoisonShot::~PoisonShot()
{
    //dtor
}

const float PoisonShot::hit(Robot* target) const
{
    float partial = POWERMULTIPLIER(this->age, this->range) * this->value;

    /*

  If Shots(t).FromSpecie = rob(n).fname Then    'Robot is imune to poison from his own species
    rob(n).poison = rob(n).poison + power 'Robot absorbs poison fired by conspecs
    If rob(n).poison > 32000 Then rob(n).poison = 32000
    rob(n).mem(827) = rob(n).poison
  Else*/
    target->Poisoned = true;
    target->PoisonCount += partial;
    if (target->PoisonCount > 32000)
        target->PoisonCount = 32000;

    if (this->Memloc > 0)
        target->Ploc = (this->Memloc - 1 % 1000) + 1;
    else
        target->Ploc = frnd(1, 1000);

    return 0;
}

const bool PoisonShot::bouncesOff(const Robot *const target, const float &power) const
{
    return false;
}

Shot* PoisonShot::returnShot(const Robot* target, const float &power) const
{
    throw;
}

