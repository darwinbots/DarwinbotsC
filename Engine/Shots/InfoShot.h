#ifndef INFOSHOT_H
#define INFOSHOT_H

#include "../Shot.h"

class InfoShot : public Shot
{
    public:
        InfoShot();
        explicit InfoShot(Robot *parent);
        virtual ~InfoShot();
        const float hit(Robot* target) const;
        const bool bouncesOff(const Robot *const target, const float &power) const;
        Shot* returnShot(const Robot* target, const float &power) const;

        InfoShot* clone()  const {return new InfoShot(*this);}
        InfoShot* create()  const {return new InfoShot();}
    protected:
    private:
};

#endif // INFOSHOT_H
