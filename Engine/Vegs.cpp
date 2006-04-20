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

void Robot::FeedVegSun()
{
    static unsigned long counter=0;
    int daymod;
    float depth=0, tok=0;

    const float QuadConstant = .00000005859375f;
    
    counter++;

    if (counter > SimOpts.CycleLength && SimOpts.DayNight)
    {
        SimOpts.Daytime = !SimOpts.Daytime;
        counter = 0;
    }

    if (SimOpts.Daytime)
    {
        //display day picture;
    }
    else
    {
        //display night picture
    }

    if (SimOpts.Daytime) daymod = 1;
    else daymod = 0;
    
    if (SimOpts.DayNight && SimOpts.Daytime == false)
        return;

    if (Veg && nrg > 0)
    {
        if (SimOpts.PondMode)
        {
            depth = this->pos.y() / 2000 + 1;
            if (depth < 1)
                depth = 1;

            tok = (SimOpts.LightIntensity / powf(depth, SimOpts.Gradient) * daymod + 1);
        }
        else
        {
            tok = SimOpts.LightIntensity;
        }

        if (tok < 0)
            tok = 0;

        switch(SimOpts.VegFeedingMethod)
        {
            case 0: //per veg
            {
                this->nrg += tok * (1 - SimOpts.VegFeedingToBody / 100);
                this->Body += tok * (SimOpts.VegFeedingToBody / 100) / 10;
            }break;
            case 1: //per kilobody
            {
                this->nrg += tok * (1 - SimOpts.VegFeedingToBody / 100) * this->Body / 1000;
                this->Body += tok * (SimOpts.VegFeedingToBody / 100) / 10 * this->Body / 1000;
            }break;
            case 2: //quadtratically based on body.  Close to type 0 near 1000 body points, but quickly diverges at about 5K body points
            {
                tok *= ((this->Body * this->Body * QuadConstant) + (1 - QuadConstant * 1000 * 1000));
                this->nrg += tok * (1 - SimOpts.VegFeedingToBody / 100);
                this->Body += tok * (SimOpts.VegFeedingToBody / 100) / 10;
            }break;
        }

        if (this->nrg > 32000)
            this->nrg = 32000;
        if (this->Body > 32000)
            this->Body = 32000;

        this->UpdateRadius();
        this->UpdateMass();
    }
}
