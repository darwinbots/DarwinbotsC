#ifndef SPECIE_H
#define SPECIE_H

#include <iostream>
#include "../Common/Math3D.h"

using namespace std;
using namespace Math3D;

struct mutationprobs
{
    public:
    bool Mutations; //mutations on or off
    long mutarray[20];  //probs of different mutations
    float Mean[20];
    float StdDev[20];

    //Extras
    int PointWhatToChange;
    int CopyErrorWhatToChange;
};

struct datispecie
{
    public:
    int Skin[13];
    string path;
    string Name;

    unsigned int color;
    
    unsigned int qty;
    unsigned int nrg;
    unsigned int body;
    
    bool Veg;
    
    Vector4 PosTopLeft, PosLowRight;
    
    string Comment;
    
    mutationprobs Mutables;
};

#endif

