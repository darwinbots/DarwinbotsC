#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "../Common/Math3d.h"

using namespace Math3D;

void CreateCircle(Vector4 c, float radius, long divisions);
void CreateSphere(Vector4 c,float r,int n = 5);
void CreatePoint(Vector4 c, float bigness);
void CreateBox(Vector4 min, Vector4 max);
void CreateCylinder(Vector4 p1, Vector4 p2, float radius);

#endif