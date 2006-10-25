#ifndef POISONSHOT_H
#define POISONSHOT_H

#include "../Shot.h"

class PoisonShot : public Shot
{
    public:
        PoisonShot();
        PoisonShot(Robot *parent, __int16 power);
        PoisonShot(Vector3f pos, Vector3f vel, unsigned long age,
                                            const Robot *parent, __int16 power);
        virtual ~PoisonShot();
        const float hit(Robot* target) const;
        const bool bouncesOff(const Robot *const target, const float &power) const;
        Shot* returnShot(const Robot* target, const float &power) const;

        PoisonShot* clone()  const {return new PoisonShot(*this);}
        PoisonShot* create()  const {return new PoisonShot();}
    protected:
    private:
};

#endif // POISONSHOT_H
