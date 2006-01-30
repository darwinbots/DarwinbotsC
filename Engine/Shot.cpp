#include "Engine.h"
#include "Shots.h"
#include "SimOptions.h"

#define SHOTDECAY 40.0f //increase to have shots lose power slower

//this below is horribly complicated:  allow me to explain:
//nrg dissipates in a non-linear fashion.  Very little nrg disappears until you
//get near the last 10% of the journey or so.
#define POWERMULTIPLIER(age, range) (atanf(float(age)/float(range) * SHOTDECAY - SHOTDECAY) / atanf(-SHOTDECAY))

/****************************************
Presently, shots have the following physical characteristics:

1.  Massless.  Shots have 0 mass
2.  Volumeless.  Shots exist purely as single points

*/////////////////////////////////////////////////////////

#define SHOTCONST 40 //defines how fast shots decay

unsigned int MaxShots; //how far into the robot array to go
Shot *shots[5000];

void FindOpenSpace(Shot *me) //finds spot for robot in array, returns pointer to said robot
{
	unsigned int firstopenspot=0;

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
    parent = 0;

    range = 20;
    age = 0;
    pos.set(0,0);
    opos.set(0,0);
    vel.set(0,0);
    color = Vector4(0,0,1.0f);
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
    this->parent = parent->AbsNum;
    //this->color  = parent->color;
    
    this->pos = parent->pos + parent->rad() * parent->aimvector;
    float angle = (parent->aim * 200 + frnd(-20, 20)) / 200;
    this->vel = parent->vel + Vector4(cosf(angle), sinf(angle)) * 40;
    this->opos = this->pos;
}

Shot::~Shot()
{
    unsigned int counter = 0;
    
    while(shots[counter] != this && counter <= MaxShots)
	    counter++;

    if (counter > MaxShots)
        return; //this is bad, it means we couldn't find this shot in the shot array

    shots[counter] = NULL;

	if (MaxShots == counter)
	{
		MaxShots = 0;
		for(long x = counter; x >= 0; x--)
		{
			if (shots[x] != NULL)
			{
				MaxShots = x;
				break;
			}
		}
	}
}

void Shot::CreateNRGStealingShot(Robot *parent)
{
    this->shottype = -1;
}

void Shot::CreateNRGGivingShot(Robot *parent)
{
    this->shottype = -2;
    this->parent = parent->AbsNum;
    this->age = 0;
    this->range = 20;
    this->color.set(1.0f,1.0f, 1.0f);
}

void Shot::CreateVenomShot(Robot *parent)
{
    this->shottype = -3;
}

void Shot::CreateWasteShot(Robot *parent)
{
    this->shottype = -4;
}

void Shot::CreatePoisonShot(Robot *parent)
{
    this->shottype = -5;
}

void Shot::CreateBodyShot(Robot *parent)
{
    this->shottype = -6;
}

void Shot::CreateInfoShot(Robot *parent)
{
    this->shottype = (*parent)[shoot];
    this->value = (*parent)[shootval];
}

void Shot::UpdatePos()
{
    //If you're unaware of what's going on here, it's called
    //verlet integration, as opposed to Euler integration.    

    Vector4 temp;

    temp = this->pos;

    this->opos = this->pos;
    this->vel += Vector4(0, SimOpts.YGravity);
    this->pos += this->vel;
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
        if (collide->parent == this->parent && collide->age <= 1)
            return; //baby bots immune to parents' shots at first

        //taste shot

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
    for (unsigned int x = 0; x <= MaxRobs; x++)
    {
        if (rob[x] != NULL)
        {
            ac = rob[x]->pos - this->opos;
            bc = rob[x]->pos - this->pos;

            //The below looks simple and like it makes no sense.
            //It's from an algorithm I only understood when I coded it.
            //It should be error free, but I've had problems with it
            //twice already (once in the VB source, and once when I ported it over)
            //that stemed from me forgetting exactly what it is it's doing.
            //the algorithm is sound, but suspect my implementation if problems
            //are evident.
            //-Numsgil
            if (ab * ac > 0)
            {
                //if AB * AC > 0 then nearest point is point B (present position)
                dist = LengthSquared3(bc);
            }
            else if(ab * bc <= 0)
            {
                //'if AB dot BC < 0 then nearest point is point A (older position)
                dist = LengthSquared3(ac);
            }
            else if(MagAB > 0)
            {
                //this is only called when a shot was closest to a bot
                //during _transit_ from opos to pos.  As such, it is rarely
                //called
                dist = (ab % ac) * (ab % ac) / MagAB;
            }
            else
            {
                //this is rarely, if ever called.  Primarily
                //an error catching routine
                //the speed of the shot would have to be 0
                dist = LengthSquared3(bc);
            }

            if (dist < rob[x]->radius * rob[x]->radius)
                if (this->parent != rob[x]->AbsNum)
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
    
    nrg = atanf((this->age - 1)/ this->range * SHOTCONST - SHOTCONST) / atanf(-SHOTCONST);
    nrg *= this->value;

    if (nrg < collide->Poison * 2)
    {
        //poison is too strong to resist
        //create poison shot
    }
    else
    {
        (*collide)[this->shottype] = this->Memval; //info shot won out
    }
}

void Shot::CollideFeedingShot(Robot *collide)
{
    float power;
    
    
    //There might be a better vector to return the shot along, but if there is I don't know it.
    this->vel = -this->vel;
    this->age = 0; //reset the age of the returning shot

    CreateNRGGivingShot(collide);

    if(SimOpts.EnergyExType == true) power = this->value * 
        POWERMULTIPLIER(this->age, this->range) * SimOpts.EnergyProp;
    else power = (float)SimOpts.EnergyFix;

    if(collide->Corpse)
        power *= 0.5f; //half power against corpses.  Most of your shot is wasted

    if(power > collide->nrg / 0.9f + collide->Poison)
       power =  collide->nrg / 0.9f + collide->Poison;    

    if(collide->Poison > power)//create poison shot
    {
        collide->Poison -= power * 0.9f;
        if(collide->Poison < 0) collide->Poison = 0;
    }
    else //create energy shot
    {
        collide->nrg -= power * 0.9f;
        if(collide->nrg < 0)
            power += collide->nrg / 0.9f;

        collide->Body -= power * 0.01f;
        if(collide->Body < 0)
            power += collide->Body / 0.01f;

        if(power < 0)
            power = 0.0f;

        this->value = (__int16)power;
    }

    if(collide->Body <= 0 || collide->nrg <= 0)
        FindSerialNumber(this->parent)->Kills++;
}

void Shot::CollideNrgShot(Robot *collide)
{
    if(collide->Corpse)
        return;

    float partial = POWERMULTIPLIER(this->age, this->range) * this->value;

    collide->nrg += partial * 0.8f;
    collide->Body += partial * 0.019f;
    collide->Waste += partial * 0.01f;
    
    if(collide->nrg > 32000)
        collide->nrg = 32000;

    if(collide->Body > 32000)
        collide->Body = 32000;
    
    delete this;
}

void Shot::CollideVenomShot(Robot *collide)
{
    /*Dim power As Long
  
  power = Shots(t).nrg / (Shots(t).range * (RobSize / 3)) * Shots(t).value
  
  If Shots(t).Memloc = 340 Or power < 1 Then Exit Sub 'protection from delgene attacks
  
  If Shots(t).FromSpecie = rob(n).fname Then   'Robot is imune to venom from his own species
    rob(n).venom = rob(n).venom + power   'Robot absorbs venom fired by conspec
    rob(n).mem(825) = rob(n).venom
  Else
    If power < rob(n).Shell * ShellEffectiveness Then
      rob(n).Shell = rob(n).Shell - power / ShellEffectiveness
    Else
      Dim temp As Long
      temp = power
      power = power - rob(n).Shell * ShellEffectiveness
      rob(n).Shell = rob(n).Shell - temp / ShellEffectiveness
      If rob(n).Shell < 0 Then rob(n).Shell = 0
    End If
    
    If power < 0 Then Exit Sub
    
    rob(n).Paralyzed = True
    rob(n).Paracount = rob(n).Paracount + power
    
    If Shots(t).Memloc > 0 Then
      If Shots(t).Memloc > 1000 Then Shots(t).Memloc = (Shots(t).Memloc - 1) Mod 1000 + 1
      rob(n).Vloc = Shots(t).Memloc
    Else
      rob(n).Vloc = fRnd(1, 1000)
    End If
    
    rob(n).Vval = Shots(t).Memval
  End If
  Shots(t).Exist = False
  */
    
}

void Shot::CollideWasteShot(Robot *collide)
{
    /*Dim power As Long
  
  power = Shots(t).nrg / (Shots(t).range * (RobSize / 3)) * Shots(t).value
  If power < 0 Then Exit Sub
  rob(n).Waste = rob(n).Waste + power
  Shots(t).Exist = False*/
}

void Shot::CollidePoisonShot(Robot *collide)
{
    /*
    Dim power As Single
  
  power = Shots(t).nrg / (Shots(t).range * (RobSize / 3)) * Shots(t).value
  
  If Shots(t).FromSpecie = rob(n).fname Then    'Robot is imune to poison from his own species
    rob(n).poison = rob(n).poison + power 'Robot absorbs poison fired by conspecs
    If rob(n).poison > 32000 Then rob(n).poison = 32000
    rob(n).mem(827) = rob(n).poison
  Else
    rob(n).Poisoned = True
    rob(n).Poisoncount = rob(n).Poisoncount + power
    If rob(n).Poisoncount > 32000 Then rob(n).Poisoncount = 32000
    If Shots(t).Memloc > 0 Then
      rob(n).Ploc = (Shots(t).Memloc - 1 Mod 1000) + 1
    Else
      rob(n).Ploc = fRnd(1, 1000)
    End If
  End If
  Shots(t).Exist = False
  */    
}

void Shot::CollideBodyShot(Robot *collide)
{
    /*
    'much more effective against a corpse
  Dim vel As vector
  Dim range As Single
  Dim power As Long
  Dim Shell As Long
  
  vel = VectorScalar(VectorSub(rob(n).vel, Shots(t).velocity), 0.5) 'half the relative velocity of
                                                                     'the shot to the hit bot
  vel = VectorAdd(vel, rob(n).vel) 'then add in the velocity of hit robot
  
  If SimOpts.EnergyExType Then
    power = Shots(t).value * Shots(t).nrg / (Shots(t).range * (RobSize / 3)) * SimOpts.EnergyProp
  Else
    power = SimOpts.EnergyFix
  End If
  
  If rob(n).nrg <= 0 Then Exit Sub
  Shell = rob(n).Shell * ShellEffectiveness
  
  If power > ((rob(n).BODY * 10) / 0.8 + Shell) Then
    power = (rob(n).BODY * 10) / 0.8 + Shell
  End If
  
  If power < Shell Then
    rob(n).Shell = rob(n).Shell - power / ShellEffectiveness
    If rob(n).Shell < 0 Then rob(n).Shell = 0
    Exit Sub
  Else
    rob(n).Shell = rob(n).Shell - power / ShellEffectiveness
    If rob(n).Shell < 0 Then rob(n).Shell = 0
    power = power - Shell
  End If
  
  If power <= 0 Then Exit Sub
  
  range = Shots(t).range      'new range formula based on range of incoming shot
  
  ' create energy shot
  If rob(n).Corpse = True Then
    power = power * 4 'So effective against corpses it makes me siiiiiinnnnnggg
    If power > rob(n).BODY * 10 Then power = rob(n).BODY * 10
    rob(n).BODY = rob(n).BODY - power / 10      'all energy comes from body
    rob(n).radius = FindRadius(rob(n).BODY)
  Else
    Dim leftover As Long
    
    rob(n).nrg = rob(n).nrg - power * 0.2       'some of shot comes from nrg
    rob(n).BODY = rob(n).BODY - (power * 0.08)  'some of shot comes from body

    leftover = 0
    If rob(n).nrg < 0 Then
      leftover = leftover + (-rob(n).nrg)
      rob(n).nrg = 0
    End If
    If rob(n).BODY < 0 Then
      leftover = leftover + (-rob(n).BODY * 10)
      rob(n).BODY = 0
    End If

    With rob(n)
    If leftover > 0 Then
      If .nrg > 0 And .nrg > leftover Then
        .nrg = .nrg - leftover
        leftover = 0
      ElseIf .nrg > 0 And .nrg < leftover Then
        leftover = leftover - .nrg
        .nrg = 0
      End If

      If .BODY > 0 And .BODY * 10 > leftover Then
        .BODY = .BODY - leftover
        leftover = 0
      ElseIf rob(n).BODY > 0 And rob(n).BODY * 10 < leftover Then
        leftover = leftover - .BODY
        .BODY = 0
      End If
    End If
    End With
    rob(n).radius = FindRadius(rob(n).BODY)
  End If
  
  If rob(n).BODY < 0 Or rob(n).nrg < 0 Then
    rob(n).Dead = True
    rob(Shots(t).parent).Kills = rob(Shots(t).parent).Kills + 1
    rob(Shots(t).parent).mem(220) = rob(Shots(t).parent).Kills
  End If
  
  createshot Shots(t).pos.x, Shots(t).pos.y, vel.x, vel.y, -2, n, power, range * (RobSize / 3), vbWhite
  */
    
    
}
