#ifndef VECTORS_H
#define VECTORS_H

/***********************************************************
Vector class I swiped from some article and totally rewrote.

vector3 * Vector3 = 3D dot product = SCALAR
vector3 % vector3 = 2D cross product (ignores z) = SCALAR
vector3 ^ vector3 = 3D cross product = Vector3

************************************************************/

#include <math.h>

//the below pre processor directive groups sort of act like a template

#define VECTOR Vector3i
#define SCALAR int
#define SQRT(x) (int)sqrtf(float(x))
#define FLOOR(x) (int)floorf(float(x))
#define CEIL(x) (int)ceilf(float(x))
#include "RawVector.h"
#undef VECTOR
#undef SCALAR
#undef SQRT
#undef FLOOR
#undef CEIL

#define VECTOR Vector3f
#define SCALAR float
#define SQRT(x) sqrtf(x)
#define FLOOR(x) floorf(x)
#define CEIL(x) ceilf(x)
#include "RawVector.h"
#undef VECTOR
#undef SCALAR
#undef SQRT
#undef FLOOR
#undef CEIL

/*inline operator= (Vector3i &a, Vector3f &b)
{
    a(0) = (int)b[0];
    a(1) = (int)b[1];
    a(2) = (int)b[2];
}

inline operator= (Vector3f &a, Vector3i &b)
{
    a(0) = (float)b[0];
    a(1) = (float)b[1];
    a(2) = (float)b[2];
}*/

#endif
