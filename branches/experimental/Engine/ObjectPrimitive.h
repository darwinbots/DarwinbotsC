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
    Vector3f color;
};

#endif
