#include <cmath>
#include "Globals.h"

__int16 iceil(float value)
{
	if (fabs(value) > 32000.0f)
		return 32000;
	else
		return __int16(value);
}

float fsgn(float value)
{
    if (value < 0)
        return -1.0f;

    return 1.0f;
}

SCALAR_F minS(SCALAR_F a, SCALAR_F b)
{
    if (a > b)
        return b;
    return a;
}

SCALAR_F maxS(SCALAR_F a, SCALAR_F b)
{
    if (a < b)
        return b;
    return a;
}

Vector3f VectorMin(const Vector3f &a, const Vector3f &b)
{
    return Vector3f(minS(a.x(), b.x()), minS(a.y(), b.y()), minS(a.z(), b.z()));
}

Vector3f VectorMax(const Vector3f &a, const Vector3f &b)
{
    return Vector3f(maxS(a.x(), b.x()), maxS(a.y(), b.y()), maxS(a.z(), b.z()));
}