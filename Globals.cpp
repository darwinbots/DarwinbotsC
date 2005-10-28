#include <math.h>
#include "Globals.h"

const __int16 iceil(float value)
{
	if (fabs(value) > 32000)
		return 32000;
	else
		return int(value);
}