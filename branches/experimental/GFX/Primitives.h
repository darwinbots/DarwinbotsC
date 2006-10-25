#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "../Common/Vectors.h"

void CreateCircle(Vector3f c, float radius, int bisections);
void CreateSphere(Vector3f c,float r,int n = 5);
void CreatePoint(Vector3f c, float bigness);
void CreateBox(Vector3f min, Vector3f max);
void CreateCylinder(Vector3f p1, Vector3f p2, float radius);

#endif
