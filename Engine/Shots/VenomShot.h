#ifndef VENOMSHOT_H
#define VENOMSHOT_H

#include "../Shot.h"

class VenomShot : public Shot
{
    public:
        VenomShot();
        explicit VenomShot(Robot *parent);
        virtual ~VenomShot();
        const float hit(Robot* target) const;
        const bool bouncesOff(const Robot *const target, const float &power) const;
        Shot* returnShot(const Robot* target, const float &power) const;

        VenomShot* clone()  const {return new VenomShot(*this);}
        VenomShot* create()  const {return new VenomShot();}
    protected:
    private:
};

#endif // VENOMSHOT_H
