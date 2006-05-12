#ifndef SPECIE_H
#define SPECIE_H

#include <iostream>
#include "../Common/Vectors.h"

using namespace std;

struct MutationTypeInformationHolder
{
    unsigned long Prob;
    bool On;
    float Mean, StdDev;
    float DeltaValue; //used for Point and Copy Error

    MutationTypeInformationHolder::MutationTypeInformationHolder()
    {
        Prob = 1000000; // 1 in a million
        On = false;
        Mean = 0;
        StdDev = 1;
        DeltaValue = 80;
    }
};

struct mutationprobs
{
    MutationTypeInformationHolder
        Point,
        Delta,
        CopyError,
        Reversal,
        Translocation,
        Insertion,
        Amplification,
        Deletion;
    bool On; //Are Global Mutations On or Off?

    mutationprobs::mutationprobs(bool on = false)
    {
        On = on;
    }
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
    bool Fixed;
    
    Vector3f PosTopLeft, PosLowRight;
    
    string Comment;
    
    mutationprobs Mutables;
};

#endif
