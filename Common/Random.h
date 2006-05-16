#ifndef RANDOM_H
#define RANDOM_H

#include <cstdio>
#include <cmath>

/****************************************************
Function prototypes for our random number generator
*******************************************************/

//These are the functions visible to modules outside this one
void DBsrand(long seed);
float DBrand();
float Gauss();
float Gauss(float StdDev);
float Gauss(const float &StdDev,const float &Mean);
long frnd(long low, long hi);

#endif
