#include "Robot.h"

/*******************************************
Vegies convert half of the waste in their bodies
to nrg each cycle
********************************************/
void Robot::FeedVegWaste()
{
	if (nrg < 32000)
	{
		nrg = nrg + Waste / 2;
		Waste = Waste / 2;
		if (nrg > 32000)
		{
			Waste = Waste + (nrg - 32000);
			nrg = 32000;
		}
	}
}

