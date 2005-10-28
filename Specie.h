#ifndef SPECIE_H
#define SPECIE_H

#include <iostream>
#include "Math3D.h"

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
    float nrg;
    bool Veg;
    bool Fixed;
    unsigned long color;
    Vector4 PosTopLeft, PosLowRight;
    unsigned int qty;
    string Comment;
    string LeaguefileComment;
    
    mutationprobs Mutables;
};

#endif

