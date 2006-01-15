#include "Shots.h"

#define SHOTCONST 40 //defines how fast shots decay

unsigned int MaxShots; //how far into the robot array to go
Shot *shots[5000];

void FindOpenSpace(Shot *me) //finds spot for robot in array, returns pointer to said robot
{
	int firstopenspot=0;

	while(shots[firstopenspot] != NULL && firstopenspot <= MaxShots)
	{
		firstopenspot++;
	}

	//push back MaxRobs if we need to
	if (firstopenspot > MaxShots)
		MaxShots = firstopenspot;
	
	//expand dynamic array if we need to
	//we go by 1000s
	//if (firstopenspot >= rob.capacity())
	//	//rob.resize(rob.capacity() + 1000, NULL);
	
	shots[firstopenspot] = me;
}

void Shot::CreateShotBasic()
{
    parent = NULL;

    range = 20;
    age = 0;
    pos.set(0,0);
    opos.set(0,0);
    vel.set(0,0);
    color = Vector4(0,0,0);
    Memloc = Memval = 0;
    value = shottype = 0;
    FindOpenSpace(this);
}

Shot::Shot()
{
    this->CreateShotBasic();    
}

Shot::Shot(Robot *parent)
{
    this->CreateShotBasic();
    this->parent = parent;
    this->color  = parent->color;
    
    //we don't need velocity.  Verlet integration handles all that
    this->pos = parent->pos + parent->rad() * parent->aimvector;
    this->opos = parent->opos + parent->rad() * parent->aimvector;
    
    float angle = (parent->aim * 200 + frnd(-20, 20)) / 200;
    this->opos = this->opos - Vector4(cos(angle), sin(angle)) * 40;
}

Shot::~Shot()
{
    unsigned int counter = 0;
    while(shots[counter] != this && counter <= MaxShots)
	    counter++;

    shots[counter] = NULL;
    
    if (counter > MaxShots)
        return;

	if (MaxShots == counter)
	{
		MaxShots = 0;
		for(unsigned int x = counter-1; x >= 0; x--)
		{
			if (shots[x] != NULL)
			{
				MaxShots = x;
				break;
			}
		}
	}
}

//create nrg stealing shot
//create nrg giving shot
//create poison shot
//create venom shot
//create waste shot
//create "body" shot

void Shot::UpdatePos()
{
    //If you're unaware of what's going on here, it's called
    //verlet integration, as opposed to Euler integration.    
    
    Vector4 temp;

    temp = this->pos;

    this->pos = 2 * this->pos - this->opos;
    this->opos = temp;
}

void Shot::UpdateShot()
{
    Robot *collide=NULL;
    
    this->UpdatePos();
    this->age++;

    if (this->age > this->range)
    {
        //this shot is dead
        delete this;
        return;
    }
    
    //check for and handle collisions
    if((collide = this->ShotColl()) != NULL)
    {
        //baby bots are immune to preexisting shots of its parent

        //this code looks suspicious to me as I look at it again -Numsgil
        if (this->parent == collide && collide->age <= 1) return;

        //taste shot

        //mod values to be in the right range
        if (this->shottype > 1000)
            this->shottype = (this->shottype - 1) % 1000 + 1;

        if (this->shottype < -10)
            this->shottype = (this->shottype + 1) % 10 - 1;

        //Infoshots
        if (this->shottype > 0 && this->shottype != DelgeneSys)
            this->CollideInfoShot(collide);

        //negative shots
        switch(this->shottype)
        {
            case -1:
                this->CollideFeedingShot(collide);
                break;
            case -2:
                this->CollideNrgShot(collide);
                break;
            case -3:
                this->CollideVenomShot(collide);
                break;
            case -4:
                this->CollideWasteShot(collide);
                break;
            case -5:
                this->CollidePoisonShot(collide);
                break;
            case -6:
                this->CollideBodyShot(collide);
        }
    }
}

Robot *Shot::ShotColl()
{
    //perform checks for torroidal edge wraparound
    Vector4 ab, ac, bc;
    float MagAB, dist;

    ab = this->pos - this->opos;
    MagAB = Length3(ab);
    
    //search through all bots to find one that's collided with us
    for (int x = 0; x <= MaxRobs; x++)
    {
        if (rob[x] != NULL)
        {
            ac = rob[x]->pos - this->opos;
            bc = rob[x]->pos - this->pos;

            //'The below looks simple and like it makes no sense.  Trust me, it's accurate,
            if (ab * ac > 0)
            {
                //if AB * AC > 0 then nearest point is point B
                dist = Length3(bc);
            }
            else if(ab * bc <= 0)
            {
                //'if AB dot BC < 0 then nearest point is point A
                dist = Length3(ac);
            }
            else if(MagAB > 0)
            {
                dist = (ab % ac) * (ab % ac) / MagAB;
            }
            else
            {
                dist = Length3(bc);
            }

            if (dist <= rob[x]->radius * rob[x]->radius)
                if (this->parent != rob[x])
                    return rob[x];
        }
    }
    return NULL;
}

void Shot::CollideInfoShot(Robot *collide)
{
    float nrg = 0;
    
    //cap large values in certain memory locations
    if ((this->shottype == fdbody || this->shottype == strbody ||
        this->shottype == mkvenom || this->shottype == mkpoison) &&
        this->value > 100)
        this->value = 100;
    
    nrg = atan((this->age - 1)/ this->range * SHOTCONST - SHOTCONST) / atan(-SHOTCONST);
    nrg *= this->value;

    if (nrg < collide->Poison * 2)
    {
        //poison is too strong
        //create poison shot
    }
    else
    {
        (*collide)[this->shottype] = this->Memval; //info shot won out
    }
}

void Shot::CollideFeedingShot(Robot *collide)
{
    
}

void Shot::CollideNrgShot(Robot *collide)
{
    
}

void Shot::CollideVenomShot(Robot *collide)
{
    
}

void Shot::CollideWasteShot(Robot *collide)
{
    
}

void Shot::CollidePoisonShot(Robot *collide)
{
    
}

void Shot::CollideBodyShot(Robot *collide)
{
    
}
