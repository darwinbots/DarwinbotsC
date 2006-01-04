#ifndef GLOBALS_H
#define GLOBALS_H

#include "../Common/Math3D.h"

#ifndef PI
#define PI      3.1415926535897932384626433833f
#endif

using namespace Math3D;

__int16 iceil(float value);

extern float fsgn(float value);
extern SCALAR minS(SCALAR a, SCALAR b);
extern SCALAR maxS(SCALAR a, SCALAR b);
extern Vector4 VectorMin(const Vector4 &a, const Vector4 &b);
extern Vector4 VectorMax(const Vector4 &a, const Vector4 &b);

#endif
