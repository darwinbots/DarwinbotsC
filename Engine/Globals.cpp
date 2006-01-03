#include <cmath>
#include "Globals.h"

inline __int16 iceil(float value)
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