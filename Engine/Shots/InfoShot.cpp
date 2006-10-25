#include "InfoShot.h"

InfoShot::InfoShot()
{
    //ctor
}

InfoShot::InfoShot(Robot *parent)
{
    this->shottype = (*parent)[shoot];
    this->value = (*parent)[shootval];
    this->parent = parent->getAbsNum();
    this->color.set(0, 1, 0); //Green
}

InfoShot::~InfoShot()
{
    //dtor
}

const float InfoShot::hit(Robot* target) const
{
    float nrg = 0;

    //cap large values in certain memory locations
    /*if ((this->shottype == fdbody || this->shottype == strbody ||
        this->shottype == mkvenom || this->shottype == mkpoison) &&
        this->value > 100)
        this->value = 100;*/

    nrg = value*POWERMULTIPLIER(age, range);

    if (nrg < target->Poison * 2 && false)
    {
        //poison is too strong to resist
        //create poison shot
    }
    else
    {
        (*target)[this->shottype] = this->Memval; //info shot won out
    }
    return 0;
}

const bool InfoShot::bouncesOff(const Robot *const target, const float &power) const
{
    return false;
}

Shot* InfoShot::returnShot(const Robot* target, const float &power) const
{
    throw;
}

