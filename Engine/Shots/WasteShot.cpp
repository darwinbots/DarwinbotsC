#include "../Robot.h"

#include "WasteShot.h"

WasteShot::WasteShot()
{
    //ctor
}

WasteShot::WasteShot(Robot *parent):Shot(parent)
{
    this->shottype = -4;
    this->color.set(0,0,0); //waste is black

    this->value = min((__int16)parent->Waste, (*parent)[shootval]);
    parent->Waste -= this->value;
}

WasteShot::~WasteShot()
{
    //dtor
}

const float WasteShot::hit(Robot* target) const
{
    float partial = POWERMULTIPLIER(this->age, this->range) * this->value;

    target->Waste += partial;
    return 0;
}

const bool WasteShot::bouncesOff(const Robot *const target, const float &power) const
{
    return false;
}

Shot* WasteShot::returnShot(const Robot* target, const float &power) const
{
    throw;
}

