#ifndef FEEDINGSHOT_H
#define FEEDINGSHOT_H

#include "../Shot.h"
class PoisonShot;
class EnergyShot;


class FeedingShot : public Shot
{
    public:
        FeedingShot();
        explicit FeedingShot(Robot *parent);
        virtual ~FeedingShot();

        const float hit(Robot* target) const;
        const bool bouncesOff(const Robot *const target, const float &power) const;
        Shot* returnShot(const Robot* target, const float &power) const;

        FeedingShot* clone()  const {return new FeedingShot(*this);}
        FeedingShot* create()  const {return new FeedingShot();}
    protected:
    private:
        PoisonShot* returnPoison(const Robot* target, const float &power) const;
        EnergyShot* returnEnergy(const Robot* target, const float &power) const;
};

#endif // FEEDINGSHOT_H
