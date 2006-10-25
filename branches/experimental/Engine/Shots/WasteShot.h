#ifndef WASTESHOT_H
#define WASTESHOT_H

#include "../Shot.h"

class WasteShot : public Shot
{
    public:
        WasteShot();
        explicit WasteShot(Robot *parent);
        virtual ~WasteShot();
        const float hit(Robot* target) const;
        const bool bouncesOff(const Robot *const target, const float &power) const;
        Shot* returnShot(const Robot* target, const float &power) const;

        WasteShot* clone()  const {return new WasteShot(*this);}
        WasteShot* create()  const {return new WasteShot();}
    protected:
    private:
};

#endif // WASTESHOT_H
