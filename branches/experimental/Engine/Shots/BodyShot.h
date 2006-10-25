#ifndef BODYSHOT_H
#define BODYSHOT_H

#include "../Shot.h"

class BodyShot : public Shot
{
    public:
        BodyShot();
        explicit BodyShot(Robot *parent);
        virtual ~BodyShot();
        const float hit(Robot* target) const;
        const bool bouncesOff(const Robot *const target, const float &power) const;
        Shot* returnShot(const Robot* target, const float &power) const;

        BodyShot* clone()  const {return new BodyShot(*this);}
        BodyShot* create()  const {return new BodyShot();}
    protected:
    private:
};

#endif // BODYSHOT_H
