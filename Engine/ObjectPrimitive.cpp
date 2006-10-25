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
            float startRadius,
            unsigned long id):
                    ObjectPrimitive(startPos, startVel, startAge),
                    aimVector(startAimVec),
                    radius(startRadius),
                    absNum(id)
{};

const float SolidPrimitive::getAim() const
{
    return atan2f(aimVector.x(),aimVector.y());
}
