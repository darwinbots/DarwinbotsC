#ifndef SPECIE_H
#define SPECIE_H

#include <iostream>
#include "../Common/Vectors.h"
#include "Mutations.h"

using namespace std;

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
