#ifndef SHOTS_H
#define SHOTS_H

#include "ObjectPrimitive.h"
#include "Robot.h"

class Robot;

class Shot : public ObjectPrimitive
{
    friend void DrawShots();
    #ifdef _MSC_VER
    friend class Shot;
    #endif

    private:
    //I would do a pointer for this, except Robots come and go, but their serial numbers
    //are unique to a robot over the entire life of a sim.
    unsigned long parent;   // parent absolute number
    Vector3f color;
    unsigned long age;

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
    const Vector3f &findpos() const
    {
        return pos;
    }

    const Vector3f &findopos() const
    {
        return opos;
    }

    void UpdateShot(bool again);
    void UpdatePos();

    private:
    void CreateShotBasic();

    Robot *ShotColl();

    public:
    void Shot::CreatePoisonShot(Robot *parent, __int16 power);
    void CreateNRGStealingShot(Robot *parent);
    void CreateNRGGivingShot(Robot *parent);
    void CreateVenomShot(Robot *parent);
    void CreateWasteShot(Robot *parent);
    void CreateBodyShot(Robot *parent);
    void CreateInfoShot(Robot *parent);
    
    private:
    void CollideInfoShot(Robot *collide);
    void CollideFeedingShot(Robot *collide);
    void CollideNrgShot(Robot *collide);
    void CollideVenomShot(Robot *collide);
    void CollideWasteShot(Robot *collide);
    void CollidePoisonShot(Robot *collide);
    void CollideBodyShot(Robot *collide);
};

extern vector<Shot *> shots;
extern int MaxShots; //how far into the shot array to go

#endif //SHOTS_H
