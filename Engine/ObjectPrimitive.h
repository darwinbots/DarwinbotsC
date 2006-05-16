#ifndef OBJECTPRIMITIVE_H
#define OBJECTPRIMITIVE_H

#include "../Common/Vectors.h"

class ObjectPrimitive
{
	protected:
	Vector3f pos, opos;
    Vector3f vel;
    unsigned long age;
	
    public:
    ObjectPrimitive(Vector3f pos = Vector3f(0,0,0),
                    Vector3f vel=Vector3f(0,0,0),
                    unsigned long age=0);
    Vector3f color;
    const Vector3f getPos() const;
};

inline const Vector3f ObjectPrimitive::getPos() const
{
    return pos;
}

////////////////////////////////////////////////////////////////////////////////
//                      Class SolidPrimitive:                                 //
//  for all physical objects who have definite position, orientation and size //
////////////////////////////////////////////////////////////////////////////////

class SolidPrimitive : public ObjectPrimitive
{
    protected:
    Vector3f aimvector;                     // Unit vector for aim
    float radius;
    
    public:
    SolidPrimitive( Vector3f pos = Vector3f(0,0,0),
                    Vector3f vel=Vector3f(0,0,0),
                    unsigned long age=0,
                    Vector3f startAimVec = Vector3f(1,0),
                    float startRadius = 60.0f);
    const float& getRadius() const;
    const Vector3f& getAimVector() const;
    const float getAim();
};

inline const float& SolidPrimitive::getRadius() const
{
    return radius;
}

inline const Vector3f& SolidPrimitive::getAimVector() const
{
    return aimvector;
}

#endif
