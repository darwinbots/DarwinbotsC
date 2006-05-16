#include "ObjectPrimitive.h"

ObjectPrimitive::ObjectPrimitive(   Vector3f startPos,
                                    Vector3f startVel,
                                    unsigned long startAge):
                                                    pos(startPos),
                                                    vel(startVel),
                                                    age(startAge)
{
    opos = pos - vel;
}

////////////////////////////////////////////////////////////////////////////////
//                    Implementation of class SolidPrimitive:                 //
//  for all physical objects who have definite position, orientation and size //
////////////////////////////////////////////////////////////////////////////////

SolidPrimitive::SolidPrimitive
            (Vector3f startPos,
            Vector3f startVel,
            unsigned long startAge,
            Vector3f startAimVec,
            float startRadius):
                    ObjectPrimitive(startPos, startVel, startAge),
                    aimvector(startAimVec),
                    radius(startRadius)
{};

const float SolidPrimitive::getAim()
{
    return atan2f(aimvector.x(),aimvector.y());
}
