#ifndef OBJECTPRIMITIVE_H
#define OBJECTPRIMITIVE_H

#include "../Common/Math3D.h"

using Math3D::Vector4;

class ObjectPrimitive
{
	protected:
	Vector4 pos, opos;
    Vector4 vel;
    unsigned long age;
	
    public:
    Vector4 color;
};

#endif