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
