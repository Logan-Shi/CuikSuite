#ifndef INTERVALVECTORH
#define INTERVALVECTORH

#include "interval.h"

/** \file interval_vector.h

    \brief Headers of the functions operating on interval vectors.

    Headers of the functions operating on vectors of intervals.

    \sa interval_vector.c interval.c interval.h
*/

/** 
   \brief Creates a vector of intervals.

   Creates a vector of intervals from a contant vector.
   
   \param s Number of elements in the vector.
   \param v The vector of from where to get the initial values.
   \param vi The interval vector to initialize. The space for this vector
             must be allocated externally.
*/
void IntervalVectFromVector(unsigned int s,double *v,Tinterval *vi);


/** 
   \brief Interval cosine on a vector.

   Compputes the interval cosine for all the elements of an interval vector.

   \param s Number of elements in the vector.
   \param vi The interval vector.
   \param ci The vector with the interval cosines (output, allocated externally).
*/
void IntCosVector(unsigned int s,Tinterval *vi,Tinterval *ci);

/** 
   \brief Interval sine on a vector.

   Compputes the interval sine for all the elements of an interval vector.

   \param s Number of elements in the vector.
   \param vi The interval vector.
   \param si The vector with the interval sines (output, allocated externally).
*/
void IntSinVector(unsigned int s,Tinterval *vi,Tinterval *si);

/** 
   \brief Adds a scaled constant vector an an interval vector.

   Adds a scaled constant vector an an interval vector (v=v1+w*v2)
   
   \param s Number of elements in the vector.
   \param v1 The interval vector to add.
   \param w The interval scale factor for \e v2. 
   \param v2 The constant vector to add.
   \param v The resulting vector.
*/
void IntervalVectSumVectorScale(unsigned int s,Tinterval *v1,Tinterval *w,double *v2,Tinterval *v);

/** 
   \brief Dot product between two interval vectors.

   Dot product between two interval vectors.

   \param s Number of elements in the vector.
   \param v1 The first interval vector to operate.
   \param v2 The second interval vector to operate.
   \param dp The resulting interval.
*/
void IntervalVectDotProduct(unsigned int s,Tinterval *v1,Tinterval *v2,Tinterval *dp);

#endif
