#ifndef SHOTS_H
#define SHOTS_H

#include "ObjectPrimitive.h"
#include "Robot.h"

class Robot;

class Shot : ObjectPrimitive
{
    #ifdef _MSC_VER
    friend class Shot;
    #endif

    private:
    Robot* parent; //pointer to parent

    float range;        // max age the shot can exist
    
    __int16 value;      //power of a shot for negative shots, value to write for > 0
    __int16 shottype;   //shot type (memloc spot for > 0)
    
    __int16 Memloc;
    __int16 Memval;     //for poison and venom
    
    //DNA() As block         ' Somewhere to store genetic code for a virus
    //genenum As Integer     ' which gene to copy in host bot
    //stored As Boolean      ' for virus shots (and maybe future types) this shot is stored
                             //' inside the bot until it's ready to be launched
    public:
    Shot();
    Shot(Robot *parent);
    ~Shot();
    const Vector4 &findpos() const
    {
        return pos;
    }

    void UpdateShot();

    private:
    void CreateShotBasic();

    void UpdatePos();
    Robot *ShotColl();

    void CreatePoisonShot(Robot *inherit);
    
    void CollideInfoShot(Robot *collide);
    void CollideFeedingShot(Robot *collide);
    void CollideNrgShot(Robot *collide);
    void CollideVenomShot(Robot *collide);
    void CollideWasteShot(Robot *collide);
    void CollidePoisonShot(Robot *collide);
    void CollideBodyShot(Robot *collide);
};

extern Shot *shots[5000];
extern unsigned int MaxShots; //how far into the shot array to go

#endif //SHOTS_H
