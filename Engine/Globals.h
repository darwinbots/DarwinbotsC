#ifndef GLOBALS_H
#define GLOBALS_H

#include "../Common/Vectors.h"

#ifndef PI
#define PI      3.1415926535897932384626433833f
#endif

extern inline __int16 iceil(float value);

extern float fsgn(float value);
extern SCALAR_F minS(SCALAR_F a, SCALAR_F b);
extern SCALAR_F maxS(SCALAR_F a, SCALAR_F b);
extern Vector3f VectorMin(const Vector3f &a, const Vector3f &b);
extern Vector3f VectorMax(const Vector3f &a, const Vector3f &b);

#endif
