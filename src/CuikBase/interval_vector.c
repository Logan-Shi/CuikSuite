#include "interval_vector.h"

/** \file interval_vector.c

    \brief Definition of the functions operating on interval vectors.

    Definition of the functions operating on vectors of intervals.

    \sa interval_vector.h interval.c interval.h
*/


void IntervalVectFromVector(unsigned int s,double *v,Tinterval *vi)
{
  unsigned int i;

  for(i=0;i<s;i++)
    NewInterval(v[i],v[i],&(vi[i]));
}


void IntCosVector(unsigned int s,Tinterval *vi,Tinterval *ci)
{
  unsigned int i;

  for(i=0;i<s;i++)
    IntervalCosine(&(vi[i]),&(ci[i]));
}

void IntSinVector(unsigned int s,Tinterval *vi,Tinterval *si)
{
  unsigned int i;

  for(i=0;i<s;i++)
    IntervalCosine(&(vi[i]),&(si[i]));
}

void IntervalVectSumVectorScale(unsigned int s,Tinterval *v1,Tinterval *w,double *v2,Tinterval *v)
{
  unsigned int i;
  Tinterval a;

  for(i=0;i<s;i++)
    {
      IntervalScale(w,v2[i],&a);
      IntervalAdd(&(v1[i]),&a,&(v[i]));
    }
}

void IntervalVectDotProduct(unsigned int s,Tinterval *v1,Tinterval *v2,Tinterval *dp)
{
  unsigned int i;
  Tinterval a;
  
  NewInterval(0,0,dp);
  for(i=0;i<s;i++)
    {
      IntervalProduct(&(v1[i]),&(v2[i]),&a);
      IntervalAdd(dp,&a,dp);
    }
}
