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

SCALAR minS(SCALAR a, SCALAR b)
{
    if (a > b)
        return b;
    return a;
}

SCALAR maxS(SCALAR a, SCALAR b)
{
    if (a < b)
        return b;
    return a;
}

Vector4 VectorMin(const Vector4 &a, const Vector4 &b)
{
    return Vector4(minS(a.x(), b.x()), minS(a.y(), b.y()), minS(a.z(), b.z()), minS(a.w(), b.w()));
}

Vector4 VectorMax(const Vector4 &a, const Vector4 &b)
{
    return Vector4(maxS(a.x(), b.x()), maxS(a.y(), b.y()), maxS(a.z(), b.z()), maxS(a.w(), b.w()));
}
