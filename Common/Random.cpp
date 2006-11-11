/***********************************************
Contains all the functions that produce various
random distributions

We code our own random number generator because we
are pendantic and want the program to work the same
in this critical manner on every platform and environment

Also, library random functions must _always_ be suspect
for scientific use, as many are not nearly as "random"
as they claim.

Many functions below have been taken from the book:
"Numerical Recipes in C", which everyone should pick up
***********************************************/

#include "Random.h"

/***********************************************
This page is broken up into three sections:

  1.  Uniform Distributions
  2.  Special Distributions
  3.  Binary Distributions

Do not intermingle their purposes.  An especially bad
attempt might be to do ran1(some value) %2 to produce
a binary distribution.  This is quite wrong and the
distribution will be skewed and the results unstatistically
sound
*************************************************/

/**********************************************
UNIFORM DEVIATES

Several functions are presented for random number generation.
Not all are used.  The unused ones are presented for reference purposes.
**********************************************/

/*******************************************************************
Quoted from "Numerical Recipes in C"

"It is not hard to think of situations where successive random numbers might be used
in a way that accidentally conflicts with th[is] generation algorithm. For example,
since successive numbers differ by a multiple of only 1.6 × 10^4 out of a modulus of
more than 2 × 10^9, very small random numbers will tend to be followed by smaller
than average values. One time in 10^6, for example, there will be a value < 10^-6
returned (as there should be), but this will always be followed by a value less than
about 0.0168. One can easily think of applications involving rare events where this
property would lead to wrong results.

"There are other, more subtle, serial correlations present in ran0. For example,
if successive points (Ii, Ii+1) are binned into a two-dimensional plane for i =
1, 2, . . .,N, then the resulting distribution fails the Chi-Squared test when N is
greater than a few ×10^7, much less than the period m-2. Since low-order serial
correlations have historically been such a bugaboo, and since there is a very
simple way to remove them, we think that it is prudent to do so."

Which is what ran1 does.


====== ran0 specifications ======

"Minimal" random number generator of Park and Miller. Returns a uniform random deviate
between 0.0 and 1.0.  Set or reset idum to any integer value (except the unlikely value MASK)
to initialize the sequence; idum must not be altered between calls for successive deviates in
a sequence

The period (before it repeats) is: 2 ^ 31 - 1 = 2.1 * 10^9 = 2.1 Billion
Note that the constants used above are not picked "randomly", they are very specific!
There are only a _SMALL_ handful of other values that will produce adequate random deviates successfully
However, the values above have been tested thoroughly by many computer scientists over many years, and
pass an amazing number of tests, so why should we try to find other, less tested values?
DO NOT alter the constants used without some SERIOUS research, or you will make this function less random
ie: more predictable.
********************************************************************/
#define IA 16807
#define IM 2147483647
#define AM (1.0f/IM)
#define IQ 127773
#define IR 2836
#define MASK 123459876

float ran0 (long *idum)
{
    long k;
    float ans;
    *idum ^= MASK; //XOR-ing with MASK allows use of zero and other simple bit patterns for idum.
    k = (*idum) / IQ;
    *idum = IA * (*idum -k * IQ) -IR * k; //Compute idum = (IA * idum)%IM without overflows by Schrage’s method.
    if (*idum < 0)
        *idum += IM;
    ans = AM * (*idum);//Convert idum to a floating result
    *idum ^= MASK; //Unmask before return.
    return ans;
}

/********************************************************************
From "Numerical Recipes in C":

"The following routine, ran1, uses the Minimal Standard for its random value,
but it shuffles the output to remove low-order serial correlations. A random deviate
derived from the jth value in the sequence, Ij , is output not on the jth call, but rather
on a randomized later call, j +32 on average.

"The routine ran1 passes those statistical tests that ran0 is known to fail. In
fact, we do not know of any statistical test that ran1 fails to pass, except when the
number of calls starts to become on the order of the period m, say > 10^8 or roughly m/20."

That is, this function works fine for under about 100 Million calls

Period is still the same as ran0 at 2 ^ 31 - 1 = 2.1 * 10^9 = 2.1 Billion

"Minimal" random number generator of Park and Miller with Bays-Durham shuffle and added
safeguards. Returns a uniform random deviate between 0.0 and 1.0 (exclusive of the endpoint
values).  That is, (0,1) instead of [0,1].  Call with idum a negative integer to initialize;
thereafter, do not alter idum between successive deviates in a sequence. RNMX should approximate
the largest floating value that is less than 1.
**********************************************************************/

//some constants are defined above that are shared with ran0
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS (float)1.2e-7
#define RNMX (1.0f-EPS)

float ran1(long *idum)
{
	__int16 j;
	long k;
	static long iy=0;
	static long iv[NTAB];
	float temp;
	if (*idum <= 0 || !iy) //Initialize.
	{ 
		if (-(*idum) < 1)
			*idum=1;// Be sure to prevent idum = 0.
		else
			*idum = -(*idum);
		for (j=NTAB+7;j>=0;j--) //Load the shuffle table (after 8 warm-ups).
		{ 
			k= (*idum) /IQ;
			*idum = IA * (*idum -k * IQ) -IR * k;
			if (*idum < 0)
				*idum += IM;
			if (j < NTAB)
				iv[j] = *idum;
		}
		iy=iv[0];
	}
	
	// Start here when not initializing.
	k = (*idum) / IQ;
	*idum = IA * (*idum -k * IQ) - IR * k;  //Compute idum=(IA*idum) % IM without over-
											//flows by Schrage’s method.
	if (*idum < 0)
		*idum += IM;
	
	j=(__int16)iy/NDIV;  //Will be in the range 0..NTAB-1.
	iy=iv[j];   //Output previously stored value and refill the
				//shuffle table.
	iv[j] = *idum;
	
	if ((temp=AM*iy) > RNMX)
		return RNMX; //Because users don’t expect endpoint values.
	else
		return temp;
}

/*************************************************************************
From "Numerical Recipes in C"

"For situations when even longer random sequences are needed, L’Ecuyer [6] has
given a good way of combining two different sequences with different periods so
as to obtain a new sequence whose period is the least common multiple of the two
periods. The basic idea is simply to add the two sequences, modulo the modulus of
either of them (call it m).

"A trick to avoid an intermediate value that overflows the integer wordsize is to
subtract rather than add, and then add back the constant m-1 if the result is = 0,
so as to wrap around into the desired interval 0 .. m -1

...

"As a practical matter it is only necessary that the second sequence have a range covering
substantially all of the range of the first. L’Ecuyer recommends the use of the two
generators m1 = 2147483563 (with a1 = 40014, q1 = 53668, r1 = 12211) and
m2 = 2147483399 (with a2 = 40692, q2 = 52774, r2 = 3791). Both moduli
are slightly less than 231. The periods m1 - 1 = 2 × 3 × 7 × 631 × 81031 and
m2 -1 = 2 × 19 × 31 × 1019 × 1789 share only the factor 2, so the period of
the combined generator is 2.3 × 10^18.

"For present computers, period exhaustion is a practical impossibility.

...

"We think that, within the limits of its floating-point precision, ran2 provides
perfect random numbers; a practical definition of "perfect" is that we will pay
$1000 to the first reader who convinces us otherwise (by finding a statistical
test that ran2 fails in a nontrivial way, excluding the ordinary limitations
of a machine’s floating-point representation)."

Well, I'm convinced.  And random number generation is not a bottleneck in Darwinbots,
so I'm more than happy to incur the slight overhead for a "perfect" random number generator.

Period: 2.3 * 10^18 = 2.3 Billion Billion.  That's huge!
******************************************************************************/

//some constants are defined for above functions
#define IM1 2147483563
#define IM2 2147483399
#define AM2 (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV2 (1+IMM1/NTAB)
#define RNMX (1.0f-EPS)

//Long period (> 2 × 1018) random number generator of L’Ecuyer with Bays-Durham shuffle
//and added safeguards. Returns a uniform random deviate between 0.0 and 1.0 (exclusive of
//the endpoint values) (that is, (0,1) and not [0,1]) Call with idum a negative integer to
//initialize; thereafter, do not alter idum between successive deviates in a sequence.
//RNMX should approximate the largest floating value that is less than 1.

float ran2(long *idum)
{
	__int16 j;
	long k;
	static long idum2 = 123456789;
	static long iy = 0;
	static long iv[NTAB];
	float temp;
	
	if (*idum <= 0) //Initialize.
	{
		if ( -(*idum) < 1) *idum=1; //Be sure to prevent idum = 0.
		else *idum = -(*idum);

		idum2 = (*idum);

		for (j=NTAB+7;j>=0;j--) // Load the shuffle table (after 8 warm-ups).
		{
			k = (*idum) / IQ1;
			*idum = IA1 * (*idum -k * IQ1) - k * IR1;
			if (*idum < 0) *idum += IM1;
			if (j < NTAB) iv[j] = *idum;
		}
		iy=iv[0];
	}

	k = (*idum) / IQ1; //Start here when not initializing.
	*idum = IA1 * (*idum -k * IQ1) -k * IR1; //Compute idum=(IA1*idum) % IM1 without
											 //overflows by Schrage’s method.
	if (*idum < 0) *idum += IM1;
	k = idum2 / IQ2;
	idum2 = IA2 * (idum2 - k * IQ2) - k * IR2; // Compute idum2=(IA2*idum) % IM2 likewise.
	if (idum2 < 0) idum2 += IM2;
	j=(__int16)iy/NDIV; // Will be in the range 0..NTAB-1.
	iy=iv[j]-idum2; // Here idum is shuffled, idum and idum2 are
					//combined to generate output. iv[j] = *idum;
	if (iy < 1) iy += IMM1;
	if ((temp=AM*iy) > RNMX) temp = RNMX; //Because users don’t expect endpoint values.

	return temp;
}

/****************************************************************************************
Notes on speeds of the above generators.  From "Numerical Recipes in C"

"Relative Timings and Recommendations
Timings are inevitably machine dependent. Nevertheless the following table is indicative
of the relative timings, for typical machines, of the various uniform generators [above].

Generator Relative Execution Time
ran0 = 1.0
ran1 = 1.3
ran2 = 2.0

"On balance, we recommend ran1 for general use. It is portable, based on
Park and Miller's Minimal Standard generator with an additional shuffle, and has no
known (to us) flaws other than period exhaustion.

"If you are generating more than 100,000,000 random numbers in a single
calculation (that is, more than about 5% of ran1's period), we recommend the use
of ran2, with its much longer period."

ran2 is probably overkill for Darwinbots' needs, but I see no reason not to use it, since the
speed hit will be negligable.  Future programmers: feel free to use another random number
function if random number generation becomes a primary concern.
******************************************************************************************/

/*******************************************************
SPECIAL DISTRIUBTIONS
********************************************************/

//Returns a normally distributed deviate with zero mean and unit variance.
//Uses DBrand(idum) for random calls
//Be sure to seed the random number generator 

float gset; //gasdev produces two random deviates each time it iterates, so one is saved for a later time
int iset = 0;

//library function
float gasdev()
{
    float fac,rsq,v1,v2;

    if (iset==0) //Initialize.
    {
        do
        {
            v1 = 2.0f * DBrand() - 1.0f; //pick two uniform numbers in the square ex-
            v2 = 2.0f * DBrand() - 1.0f; //tending from -1 to +1 in each direction
            rsq = v1 * v1 + v2 * v2;       //see if they are in the unit circle
        }while(rsq >= 1.0f || rsq == 0.0f);//and if they are not, try again
    
        fac = (float) sqrt(-2.0f * log(rsq) / rsq);

        //Now make the Box - Muller Transformation to get to two normal deviates
        //Return one and save the other for next time

        gset = v1 * fac;
        iset = 1; //Setflag
        return v2 * fac;
    }
    else
    {
        //We have the devite from last iteration
        iset = 0; //Unset the flag
        return gset; //return the deviate;
    }
}

/*********************************************
The following code is the front end that will be accessible to other DB
modules.  This way, we can change the way the program uses random numbers
by just changing these.
*********************************************/

long seedholder; //holds the value passed to the ranom number generator each call
				 //(the generator modifies this value for the next call)
				 //only should be modified by functions in this module

void DBsrand(long seed)
{
	if (seed < 0) seed = -seed;
	seedholder = -1 * seed;  //instruct the random number generator to seed itself
	
	//reset the gauss distribution too
	iset = 0;
	gset = 0;
}

float DBrand()
{
	return ran2(&seedholder);
}

float Gauss()
{
	return gasdev();
}

float Gauss(float StdDev)
{
	return gasdev() * StdDev;	
}

float Gauss(float const &StdDev, float const &Mean)
{
	return gasdev() * StdDev + Mean;	
}

long frnd(long low, long hi)
{
	return int(DBrand() * (hi - low + 1) + low);
}

/***************************************************************
#include <iostream>
#include <math.h>
#include "Random.h"

#define TRIALS 10000000

using namespace std;

void main(void)
{
	float mean=0.0f;
	float variance=0.0f;
	float value = 0.0f;

	DBsrand(800741);
	
	for (long trials = 1; trials <= TRIALS ;  trials++)
	{
		value = Gauss() * 5;
		mean = mean + (value - mean)/trials;
		variance = variance + (value * value)/(TRIALS - 1);
	}

	cout << "After a million trials:" << endl <<
			"Mean:     " << mean << endl <<
			"Variance: " << variance << endl <<
			"StdDev:   " << sqrt(variance) << endl;
}

The above is a good way to show how the gasdev function works, that it works, etc.
********************************************************************/
