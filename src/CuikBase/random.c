#include "random.h"

#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

/** 
   \file random.c

   \brief Implementation of the basic randomization functions. 

   Implementation of the basic randomization functions. 
   
   \sa random.h.
*/

void randomReset()
{
  randomSet((unsigned int)time(NULL));
}

void randomSet(unsigned int seed)
{
  #if (DEBUG_RANDOM)
    fprintf(stderr,"rand seed %u - - - - - - - - - - - - - - - - \n",seed);
  #endif
    
  srand(seed);
  rand(); /*useful to avoid first rands to be almost equals*/
  rand();

}

double randomDouble()
{
  double d=((double)rand()/(double)RAND_MAX);
  
  #if (DEBUG_RANDOM)
    fprintf(stderr,"rand double: %f - - - - - - - - - - - - - - - - \n",d);
  #endif
    
  return(d);
}

double randomNormal()
{
  static boolean oneCached=FALSE;
  double x1,x2,w;
  double y1;
  static double y2;

  if (oneCached)
    {
      oneCached=FALSE;
      #if (DEBUG_RANDOM)
        fprintf(stderr,"rand normal2: %f - - - - - - - - - - - - - - - - \n",y2);
      #endif
      return(y2);
    }
  else
    {
      do {
	x1=2.0*randomDouble()-1.0;
	x2=2.0*randomDouble()-1.0;
	w=x1*x1+x2*x2;
      } while (w>=1.0);
      
      w=sqrt((-2.0*log(w))/w);
      y1=x1*w;
      y2=x2*w;
 
      oneCached=TRUE;
      
      #if (DEBUG_RANDOM)
        fprintf(stderr,"rand normal1: %f - - - - - - - - - - - - - - - - \n",y1);
      #endif
	
      return(y1);
    }
}

double randomInInterval(Tinterval *t) 
{
  double a,b,r;

  a=LowerLimit(t);
  b=UpperLimit(t);

  r=a+randomDouble()*(b-a);
  
  #if (DEBUG_RANDOM)
    fprintf(stderr,"rand interval[%f %f]: %f - - - - - - - - - - - - - - - - \n",a,b,r);
  #endif
    
  return(r);
}

unsigned int randomMax(unsigned int m)
{
  if (m==0)
    return(0);
  else
    {
      unsigned int r;

      r=(unsigned int)floor(randomDouble()*(m+1));
      
      #if (DEBUG_RANDOM)
        fprintf(stderr,"rand max[%u]: %u - - - - - - - - - - - - - - - - \n",m,r);
      #endif
	
      return(r); /* in [0,m+1) -> all values in 0,m have same chances */
    }
}


unsigned int randomWithDistribution(unsigned int m,double s,double *d)
{
  double s1,r;
  unsigned int i;

  if (s==0.0)
    {
      for(i=0;i<m;i++)
	s+=d[i];
    }
 
  r=s*randomDouble();

  i=0;
  s1=d[0];
  while((r>s1)&&(i<(m-1)))
    {
      i++;
      s1+=d[i];
    }

  #if (DEBUG_RANDOM)
    fprintf(stderr,"rand distribution: %u - - - - - - - - - - - - - - - - \n",i);
  #endif
  
  return(i);
}

void randomOnBall(double r,unsigned int k,double *p)
{
  unsigned int i;
  double n;

  #if (DEBUG_RANDOM)
    fprintf(stderr,"rand on ball - - - - - - - - - - - - - - - - \n");
  #endif
    
  n=0.0;
  for(i=0;i<k;i++)
    {
      p[i]=randomNormal();
      n+=(p[i]*p[i]);
    }
  n=r/sqrt(n);
  for(i=0;i<k;i++)
    p[i]*=n;
}

void randomInBall(double r,unsigned int k,double *p)
{
  unsigned int i;
  double n;
  
  #if (DEBUG_RANDOM)
    fprintf(stderr,"rand in ball - - - - - - - - - - - - - - - - \n");
  #endif
    
  /* random on surface ... */
  n=0.0;
  for(i=0;i<k;i++)
    {
      p[i]=randomNormal();
      n+=(p[i]*p[i]);
    }
  /* ... but scaling to select points inside the ball too. */
  n=pow(randomDouble(),1/((double)k))*(r/sqrt(n)); 
  for(i=0;i<k;i++)
    p[i]*=n;
}


void randomVector(unsigned int n,double *v)
{
  unsigned int i;
  
  #if (DEBUG_RANDOM)
    fprintf(stderr,"rand vector - - - - - - - - - - - - - - - - \n");
  #endif
    
  for(i=0;i<n;i++)
    v[i]=randomDouble();
}
