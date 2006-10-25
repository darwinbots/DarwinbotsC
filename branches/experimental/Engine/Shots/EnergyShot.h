#ifndef ENERGYSHOT_H
#define ENERGYSHOT_H

#include "../Shot.h"

class EnergyShot : public Shot
{
    public:
        EnergyShot();
        explicit EnergyShot(Robot *parent);
        EnergyShot(Vector3f pos, Vector3f vel, unsigned long age,
                                            const Robot *parent, float power);
        virtual ~EnergyShot();
        const float hit(Robot* target) const;
        const bool bouncesOff(const Robot *const target, const float &power) const;
        Shot* returnShot(const Robot* target, const float &power) const;

        EnergyShot* clone()  const {return new EnergyShot(*this);}
        EnergyShot* create()  const {return new EnergyShot();}
    protected:
    private:
};

#endif // ENERGYSHOT_H
