/****************************************************
Function prototypes for our random number generator
*******************************************************/

//These are the functions visible to modules outside this one
void DBsrand(long seed);
inline float DBrand();
inline float Gauss();
float Gauss(float StdDev);
inline float Gauss(const float &StdDev,const float &Mean);
long frnd(long low, long hi);
