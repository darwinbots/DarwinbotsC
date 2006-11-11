#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "../Common/Vectors.h"

void CreateCircle(Vector3f c, float radius, int bisections);
void CreatePoint(Vector3f c, float bigness);
void CreateBox(Vector3f min, Vector3f max);

#endif
