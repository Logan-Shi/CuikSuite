#ifndef RANDOMH
#define RANDOMH

#include "interval.h"


/** \brief Debug the radom generation of numbers.

    Used to debug the random generation of numbers. 
*/
#define DEBUG_RANDOM  (_DEBUG>4?1:0)

/** 
   \file random.h

   \brief Definition of  basic randomization functions. 

   Definition of basic randomization functions. 
   
   \sa random.c.
*/


/** 
   \brief Resets the random seed.

   Resets the random seed using the current time so, in principle,
   the reset is hard to predict.
*/
void randomReset();

/** 
   \brief Sets the random seed.

   Sets the random to the given value. This is used to get
   repetitive sequences of \e random numbers in order to debug
   mainly.

   Please, note that when using advanced numerical libraries
   (BLAS) the result of numerical computations can be different
   at each run (https://bebop.cs.berkeley.edu/reproblas). The
   differences are tiny (at the machine precision) but in some
   systems (specially with dynamics) such errors can accumulate
   and produce a different result in each run.

   To avoid this, you can increase the DEBUG level (in
   the main CMake file) since then BLAS is not used. However,
   parallelism will not be used either and the execution will be
   much slower.

   \param seed The new random seed.
*/
void randomSet(unsigned int seed);

/** 
   \brief Returns a random double in the [0,1] interval.

   Returns a random number in the [0,1] interval selected with a uniform distribution.

   \return A random double in [0,1].
*/
double randomDouble();

/** 
   \brief Returns a random double acording to a normal distribution.

   Returns a random number following a normal distribution with mean 0 and standard deviation 1.

   \return A random double.
*/
double randomNormal();

/** 
   \brief Returns a random double in the given interval.

   Returns a random number in the given interval selected with a uniform distribution.

   \param t The interval where to drawn the random sample.
   
   \return A random double in the given interval.
*/
double randomInInterval(Tinterval *t);

/** 
   \brief Returns a random integer in the range [0,m].

   Returns a random integer in the range [0,m] selected with a uniform distribution.
   Observe that \e m is included as a possible outcome.

   \param m The upper limit for the random generator.

   \return The randomly selected integer in [0,m].
*/
unsigned int randomMax(unsigned int m);

/** 
   \brief Random number with a given discrete distribution.

   Gets a random number following an arbitrary random discrete distribution.

   \param m The size of the distribution (number of options).
   \param s Sum of the values in \e d. If zero the sum is computed inside 
            this function.
   \param d The value for each option. The values in \e d are assume possitive
            but not normalized.
*/
unsigned int randomWithDistribution(unsigned int m,double s,double *d);
 
/** 
   \brief Random number on a \e k dimensional ball.

   Selects a random point on the surface of a  \e k dimensional ball
   with uniform distribution.
   
   \param r Radius of the ball.
   \param k Dimension of the space where the ball is defiend.
   \param p Space for the output point. Must be allocated externally.
*/
void randomOnBall(double r,unsigned int k,double *p);

/** 
   \brief Random number in a \e k dimensional ball.

   Selects a random point inside a  \e k dimensional ball
   with uniform distribution.
   
   \param r Radius of the ball.
   \param k Dimension of the space where the ball is defiend.
   \param p Space for the output point. Must be allocated externally.
*/
void randomInBall(double r,unsigned int k,double *p);

/** 
   \brief Random vector.

   Random vector with numbers uniformly distributed in the [0,1] interval.

   \param n The size fo the vector.
   \param v The vector to fill. 
*/
void randomVector(unsigned int n,double *v);

#endif
