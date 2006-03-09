#include <fx.h>
#include "SimOptions.h"
#include "..\Common\Random.h"

SimOptions SimOpts;  //for use in sims
SimOptions TmpOpts; //for use in GUI, gets copied to SimOpts

void SimOptions::AddSpecies(string path, string name)
{
    int x = 0;

    while(this->Specie[x].Name != "")
        x++;

    this->Specie[x].Name = name;
    this->Specie[x].path = path;

    this->Specie[x].qty = 5;
    this->Specie[x].nrg = 3000;
    this->Specie[x].body = 1000;

    this->Specie[x].Veg = false;

    this->Specie[x].color = FXRGB(frnd(0, 255), frnd(0, 255), frnd(0, 255));
}

void SimOptions::DeleteSpecies(string path, string name)
{
    int x = 0;
    while(this->Specie[x].Name != "")
    {
        if(this->Specie[x].Name == name &&
           this->Specie[x].path == path)
        {
            DeleteSpecies(x);
            return;
        }
    }
}

void SimOptions::DeleteSpecies(int x)
{
    while(this->Specie[x].Name != "")
    {
        this->Specie[x] = this->Specie[x+1];
        if(++x == 49)
        {
            this->Specie[x].Name = "";
            return;
        }
    }
}