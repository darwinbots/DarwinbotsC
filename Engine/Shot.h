#ifndef SHOTS_H
#define SHOTS_H

#include "ObjectPrimitive.h"

const float minShotPower = 0.1f;
const float returnShotVelocityFactor = 0.5f;
#define SHOTDECAY 40.0f //increase to have shots lose power slower
#define SHELLEFFECTIVENESS 20

//this POWERMUTLIPLIER below is horribly complicated:  allow me to explain:
//nrg dissipates in a non-linear fashion.  Very little nrg disappears until you
//get near the last 10% of the journey or so.
//here's what the graph would look like for nrg with respect to time:
/*
|________
|        \
|          \
|           \
|            |
|            |
|____________|
*/
#define POWERMULTIPLIER(age, range) (atanf(float(age)/float(range) * SHOTDECAY - SHOTDECAY) / atanf(-SHOTDECAY))



class Robot;

class Shot : public ObjectPrimitive
{
    public:
        Shot();
        Shot(Vector3f pos, Vector3f vel, unsigned long age, const Robot* parent);
        explicit Shot(Robot *parent);
        virtual ~Shot();

        void UpdatePos();
        void reflect(Robot* collide);
        Robot *ShotColl();

        bool isTooOld();

//I would do a pointer for this, except Robots come and go, but their serial numbers
//are unique to a robot over the entire life of a sim.
        unsigned long parent;   // parent absolute number

        //Virtual Constructor Idiom
        virtual Shot* clone()  const = 0;
        virtual Shot* create() const = 0;

    //protected:


        float range;        // max age the shot can exist

        __int16 value;      //power of a shot for negative shots, value to write for > 0
        __int16 shottype;   //shot type (memloc spot for > 0)

        __int16 Memloc;
        __int16 Memval;     //for poison and venom

        //DNA() As block         ' Somewhere to store genetic code for a virus
        //genenum As Integer     ' which gene to copy in host bot
        //stored As Boolean      ' for virus shots (and maybe future types) this shot is stored
                             //' inside the bot until it's ready to be launched
        float collisionTime(const Robot *const target) const;

    private:
        void CreateShotBasic();


    public:
        //virtual void collide(Robot* target) = 0;
        virtual const float hit(Robot* target) const = 0;
        virtual const bool bouncesOff(const Robot *const target, const float &power) const = 0;
        virtual Shot* returnShot(const Robot* target, const float &power) const = 0;
};

//extern vector<Shot *> shots;
//extern int MaxShots; //how far into the shot array to go

#include "Shots/BodyShot.h"
#include "Shots/EnergyShot.h"
#include "Shots/FeedingShot.h"
#include "Shots/InfoShot.h"
#include "Shots/PoisonShot.h"
#include "Shots/VenomShot.h"
#include "Shots/WasteShot.h"

#endif //SHOTS_H
