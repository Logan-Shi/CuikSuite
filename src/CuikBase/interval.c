#include "interval.h"

#include "error.h"
#include "defines.h"
#include "geom.h"

#include <math.h>

/** \file interval.c
    \brief Implementation of the functions operating on Tinterval.

    Implementation of the functions operating on Tinterval.

    \sa Tinterval, interval.h.
 */

/** 
   \brief Normalizes a angular value so that it is included in [0,2Pi].
   
   Normalizes a angular value so that it is included in [0,2Pi].

   \param a The input angular value.
   
   \return The normalized angular value.
*/
double NormalizeAngle(double a);

/*
 * moves the angle 'a' but in the interval [0,2pi]
 */
double NormalizeAngle(double a)
{
  double new_a;

  new_a=a;
  if ((new_a>M_PI)||(new_a<-M_PI))
    new_a=atan2(sin(new_a),cos(new_a));

  if (new_a<0.0) new_a+=M_2PI;

  return(new_a);
}

/*
 * Defines a new interval with limits: lower and upper
 */
void NewInterval(double lower,      /*lower limit of the new interval*/
		 double upper,      /*upper limit of the new interval*/
		 Tinterval *i       /*new interval*/
		 )
{
  i->lower_limit=INF_CUT(lower);
  i->upper_limit=INF_CUT(upper);
}

/*
 * Copies i_org into i_dst.
 */
void CopyInterval(Tinterval *i_dst,Tinterval *i_org)
{
  i_dst->lower_limit=i_org->lower_limit;
  i_dst->upper_limit=i_org->upper_limit;
}

/*
 * Returns true if i1 and i2 are exactly the same.
 * This only works for intervals that are exactly the same (copies, the same
 * initialization,....)
 */
boolean CmpIntervals(Tinterval *i1,Tinterval *i2)
{
  return((i1->lower_limit==i2->lower_limit)&&
	 (i1->upper_limit==i2->upper_limit));
}

/*
 * Returns the lower limit of interval 'i'.
 */
inline double LowerLimit(Tinterval *i)
{
  return(i->lower_limit);
}

/*
 * Returns the upper limit of interval 'i'.
 */
inline double UpperLimit(Tinterval *i)
{
  return(i->upper_limit);
}

/*
 * Returns the size of interval 'i'.
 * NOTE: For empty intervals it can return a negative size
 */
double IntervalSize(Tinterval *i)
{
  double s;

  if (IS_INF(i->lower_limit)||IS_INF(i->upper_limit))
    s=INF;
  else
    {
      ROUNDUP;
      s=i->upper_limit-i->lower_limit;
      ROUNDNEAR;
    }
  
  return(s);
}

double DistanceToInterval(double p,Tinterval *i)
{
  double d=0.0;

  if (p<i->lower_limit)
    d=i->lower_limit-p;
  else
    {
      if (p>i->upper_limit)
	d=p-i->upper_limit;
    }
  return(d);
}

/*
 * Returns the center of the interval
 */
double IntervalCenter(Tinterval *i)
{
  double c;

  if (i->upper_limit==i->lower_limit)
    c=i->upper_limit;
  else
    { 
      if (IS_INF(i->lower_limit)&&(IS_INF(i->upper_limit)))
	c=0.0;
      else
	{
	  if (IS_INF(i->lower_limit))
	    c=i->upper_limit;
	  else
	    {
	      if (IS_INF(i->upper_limit))
		c=i->lower_limit;
	      else
		{
		  c=(i->upper_limit+i->lower_limit)/2.0;
		  
		  /* Conditions below can occur because of roundings */
		  if (c<i->lower_limit) c=i->lower_limit;
		  if (c>i->upper_limit) c=i->upper_limit;
		}
	    }
	}
    }
  return(c);
}

/*
 * Returns the point in the interval by linear interpolation between the extremes.
 */
double PointInInterval(double r,Tinterval *i)
{
  double p;

  if (i->upper_limit==i->lower_limit)
    p=i->upper_limit;
  else
    { 
      if (IS_INF(i->lower_limit)&&(IS_INF(i->upper_limit)))
	p=0.0;
      else
	{
	  if (IS_INF(i->lower_limit))
	    p=i->upper_limit-1;
	  else
	    {
	      if (IS_INF(i->upper_limit))
		p=i->lower_limit+1;
	      else
		{
		  p=i->lower_limit+(i->upper_limit-i->lower_limit)*(r<0?0:(r>1?1:r));
		  
		  /* Conditions below can occur because of roundings */
		  if (p<i->lower_limit) p=i->lower_limit;
		  if (p>i->upper_limit) p=i->upper_limit;
		}
	    }
	}
    }
  return(p);
}

void SetLowerLimit(double v,Tinterval *i)
{
  i->lower_limit=INF_CUT(v);
}

void SetUpperLimit(double v,Tinterval *i)
{
  i->upper_limit=INF_CUT(v);
}

void EnlargeInterval(double lo,double uo,Tinterval *i)
{
  double v;

  if (IS_NOT_INF(i->lower_limit))
    {
      if (IS_INF(lo))
	i->lower_limit=lo;
      else
	{
	  ROUNDDOWN;
	  v=i->lower_limit+lo;
	  i->lower_limit=INF_CUT(v);
	}
    }

  if (IS_NOT_INF(i->upper_limit))
    {
      if (IS_INF(uo))
	i->upper_limit=uo;
      else
	{
	  ROUNDUP;
	  v=i->upper_limit+uo;
	  i->upper_limit=INF_CUT(v);
	}
    }
  ROUNDNEAR;
}

void ExpandInterval(double v,Tinterval *i)
{
  if (v<i->lower_limit)
    i->lower_limit=INF_CUT(v);
  else
    {
      if (v>i->upper_limit)
	i->upper_limit=INF_CUT(v);
    }
}

void UpdateLowerLimit(double v,Tinterval *i)
{
  if (v>i->lower_limit)
    i->lower_limit=INF_CUT(v);
}

void UpdateUpperLimit(double v,Tinterval *i)
{
  if (v<i->upper_limit)
    i->upper_limit=INF_CUT(v);
}

/*
 * Returns TRUE if i1 is fully included in i2
 */
boolean IntervalInclusion(Tinterval *i1,Tinterval *i2)
{
  return((i2->lower_limit<i1->lower_limit)&&(i1->upper_limit<i2->upper_limit));
}

/*
 * Returns TRUE if intervals 'i1' and 'i2' actually intersect.
 * NOTE: This rutine is only valid for intervals where lower_limit<upper_limit
 * and thus it fails in the intersection between certain rotational intervals.
 */
boolean Intersect(Tinterval *i1,Tinterval *i2)
{
  Tinterval i3;

  return(Intersection(i1,i2,&i3));
}

/*
 * Returns in 'i_out' the intersection of intervals 'i1' and 'i2'.
 * NOTE: This rutine is only valid for intervals where lower_limit<upper_limit
 * and thus it can fail for intersection between certain rotational intervals.
 * RETURNS true if the intersection is NOT EMPTY
 */
boolean Intersection(Tinterval *i1,Tinterval *i2,Tinterval *i_out)
{
  i_out->lower_limit=(i1->lower_limit>i2->lower_limit?i1->lower_limit:i2->lower_limit);
  i_out->upper_limit=(i1->upper_limit<i2->upper_limit?i1->upper_limit:i2->upper_limit);
  
  return(i_out->lower_limit<=i_out->upper_limit);
}

/*
 * Returns in i_out the union of i1 and i2
 * Returns false if the the input intervals are empty
*/
boolean Union(Tinterval *i1,Tinterval *i2,Tinterval *i_out)
{ 
  boolean full;

  full=TRUE;

  if (i1->lower_limit>i1->upper_limit) /*i1 empty*/
    {
      if (i2->lower_limit>i2->upper_limit)/*i2 empty*/
	full=FALSE;
      else
	{
	  i_out->lower_limit=i2->lower_limit;
	  i_out->upper_limit=i2->upper_limit;
	}
    }
  else
    {
      if (i2->lower_limit>i2->upper_limit) /*i2 empty*/
	{
	  i_out->lower_limit=i1->lower_limit;
	  i_out->upper_limit=i1->upper_limit;
	}
      else
	{  
	  i_out->lower_limit=(i1->lower_limit<i2->lower_limit?i1->lower_limit:i2->lower_limit);
	  i_out->upper_limit=(i1->upper_limit>i2->upper_limit?i1->upper_limit:i2->upper_limit);
	}
    }
  return(full);
}


/*
 * Returns TRUE if interval 'i' is empty
 * NOTE: This rutine is only valid for intervals where lower_limit<upper_limit
 * and thus it can return wrong results for certain rotational intervals.
 */
boolean EmptyInterval(Tinterval *i)
{
  return(i->lower_limit>i->upper_limit);
}

boolean ZeroInterval(Tinterval *i)
{
  return((fabs(i->lower_limit)<ZERO)&&(fabs(i->upper_limit)<ZERO));
}

/*
 * returns true if p is inside the interval i
 */ 
boolean IsInside(double p,double tol,Tinterval *i)
{
  double v;

  v=INF_CUT(p);
  return((v>=(i->lower_limit-tol))&&(v<=(i->upper_limit+tol)));
}

/*
 * Products and interval and a scalar
 * Be carefull i_out can be i1 or i2!!!!!
 */
void IntervalScale(Tinterval *i1,double e,Tinterval *i_out)
{
  double e1,e2;
      
  if (e>0)
    {
      ROUNDDOWN;
      e1=INF_SCALE(e,i1->lower_limit);
      ROUNDUP; 
      e2=INF_SCALE(e,i1->upper_limit);
    }
  else
    {
      /*The sign is changed: extremes are swap */
      ROUNDDOWN;
      e1=INF_SCALE(e,i1->upper_limit);
      ROUNDUP; 
      e2=INF_SCALE(e,i1->lower_limit);
    }
  ROUNDNEAR;

  i_out->lower_limit=INF_CUT(e1);
  i_out->upper_limit=INF_CUT(e2);
}

/*
 * Product of two intervals
 * Be carefull i_out can be i1 or i2!!!!!
 */
void IntervalProduct(Tinterval *i1,Tinterval *i2,Tinterval *i_out)
{
  double e[3];
  unsigned int i;
  double a,b;

  ROUNDDOWN;
  e[0]=INF_PROD(i1->lower_limit,i2->upper_limit,TRUE);
  e[1]=INF_PROD(i1->upper_limit,i2->lower_limit,TRUE);
  e[2]=INF_PROD(i1->upper_limit,i2->upper_limit,TRUE);

  a=INF_PROD(i1->lower_limit,i2->lower_limit,TRUE);
  for(i=0;i<3;i++)
    if (e[i]<a) a=e[i];

  ROUNDUP; 
  e[0]=INF_PROD(i1->lower_limit,i2->upper_limit,FALSE);
  e[1]=INF_PROD(i1->upper_limit,i2->lower_limit,FALSE);
  e[2]=INF_PROD(i1->upper_limit,i2->upper_limit,FALSE);

  b=INF_PROD(i1->lower_limit,i2->lower_limit,FALSE);
  for(i=0;i<3;i++)
    if (e[i]>b) b=e[i];
   
  ROUNDNEAR;

  i_out->lower_limit=INF_CUT(a);
  i_out->upper_limit=INF_CUT(b);
}

/*
 * Additon of two intervals
 * Be carefull i_out can be i1 or i2!!!!!
 */
void IntervalAdd(Tinterval *i1,Tinterval *i2,Tinterval *i_out)
{
  double a,b;

  ROUNDDOWN;
  a=INF_ADD(i1->lower_limit,i2->lower_limit,TRUE);
	 
  ROUNDUP;
  b=INF_ADD(i1->upper_limit,i2->upper_limit,FALSE);

  ROUNDNEAR;

  i_out->lower_limit=INF_CUT(a);
  i_out->upper_limit=INF_CUT(b);
}

/*
 * i_out=i1-i2;
 */
void IntervalSubstract(Tinterval *i1,Tinterval *i2,Tinterval *i_out)
{ 
  double a,b;

  ROUNDDOWN;
  a=INF_SUBS(i1->lower_limit,i2->upper_limit,TRUE);
  
  ROUNDUP;
  b=INF_SUBS(i1->upper_limit,i2->lower_limit,FALSE);

  ROUNDNEAR;

  i_out->lower_limit=INF_CUT(a);
  i_out->upper_limit=INF_CUT(b);
}

/*
 * Changes the sign of a given interval
 */
void IntervalInvert(Tinterval *i,Tinterval *i_out)
{  
  double a,b;
  
  a=-i->upper_limit;
  b=-i->lower_limit;

  i_out->lower_limit=a;
  i_out->upper_limit=b;
}

/*
 * i_out=exo(i)
 */
void IntervalExp(Tinterval *i,Tinterval *i_out)
{
  double a,b;

  ROUNDDOWN;
  a=INF_EXP(i->lower_limit);

  ROUNDUP;
  b=INF_EXP(i->upper_limit);
  
  ROUNDNEAR;

  i_out->lower_limit=INF_CUT(a);
  i_out->upper_limit=INF_CUT(b);
}

/*
 * i_out=i^p
 */
void IntervalPow(Tinterval *i,unsigned int p,Tinterval *i_out)
{
  double a,b,e1,e2;

  ROUNDDOWN;
  e1=INF_POW(i->lower_limit,p);
  e2=INF_POW(i->upper_limit,p);

  if (e1<e2)
    a=e1;
  else
    a=e2;
 
  ROUNDUP;
  e1=INF_POW(i->lower_limit,p);
  e2=INF_POW(i->upper_limit,p);

  if (e1>e2)
    b=e1;
  else
    b=e2;

  ROUNDNEAR;

  if (((p%2)==0)&&(IsInside(0,0,i)))
    a=0;  /*x^p with p=2*n always have a minimum at 0  (if included in the input interval)*/

  i_out->lower_limit=INF_CUT(a);
  i_out->upper_limit=INF_CUT(b);
}



/*
 * Square root 
 */
boolean IntervalSqrt(Tinterval *i,Tinterval *i_out)
{
  double a,b;

  if (i->upper_limit<0.0)
    return(FALSE);
  else
    {
      ROUNDDOWN;
      a=INF_SQRT(i->lower_limit);
      
      ROUNDUP;
      b=INF_SQRT(i->upper_limit);
      
      ROUNDNEAR;
      
      i_out->lower_limit=INF_CUT(a);
      i_out->upper_limit=INF_CUT(b);
      
      return(TRUE);
    }
}

/*
 *  i_out = i1/i2
 */
void IntervalDivision(Tinterval *i1,Tinterval *i2,Tinterval *i_out)
{
  double a,b;
  
  if (IsInside(0,0,i2))
    {
      if ((i2->lower_limit==0.0)&&(i2->upper_limit>0.0))
	{
	  ROUNDDOWN;
	  a=i1->lower_limit/i2->upper_limit;
	  b=i1->upper_limit/i2->upper_limit;
	  a=(a<b?a:b);
	  ROUNDNEAR;
	  i_out->lower_limit=INF_CUT(a);

	  i_out->upper_limit=+INF;
	}
      else
	{
	  if ((i2->lower_limit<0.0)&&(i2->upper_limit==0.0))
	    {
	      i_out->lower_limit=-INF;  

	      ROUNDUP;
	      a=i1->lower_limit/i2->lower_limit;
	      b=i1->upper_limit/i2->lower_limit;
	      b=(b>a?b:a);
	      ROUNDNEAR;
	      i_out->upper_limit=INF_CUT(b);
	      
	    }
	  else
	    {
	      i_out->lower_limit=-INF;
	      i_out->upper_limit=+INF;
	    }
	}
    }
  else
    {
      double e[3];
      unsigned int i;
  
      ROUNDDOWN;
      e[0]=i1->lower_limit/i2->upper_limit;
      e[1]=i1->upper_limit/i2->lower_limit;
      e[2]=i1->upper_limit/i2->upper_limit;
      
      a=i1->lower_limit/i2->lower_limit;
      for(i=0;i<3;i++)
	if (e[i]<a) a=e[i];
      
      ROUNDUP;
      e[0]=i1->lower_limit/i2->upper_limit;
      e[1]=i1->upper_limit/i2->lower_limit;
      e[2]=i1->upper_limit/i2->upper_limit;
      
      b=i1->lower_limit/i2->lower_limit;
      for(i=0;i<3;i++)
	if (e[i]>b) b=e[i];
      
      ROUNDNEAR;
      
      i_out->lower_limit=INF_CUT(a);
      i_out->upper_limit=INF_CUT(b);
    }
}

/*
 * Shifts a interval
*/
void IntervalOffset(Tinterval *i,double offset,Tinterval *i_out)
{
  double a,b;

  ROUNDDOWN;
  a=INF_ADD(i->lower_limit,offset,TRUE);

  ROUNDUP;
  b=INF_ADD(i->upper_limit,offset,FALSE);

  ROUNDNEAR;

  i_out->lower_limit=INF_CUT(a);
  i_out->upper_limit=INF_CUT(b);
}


/*
 * Computes the sinus of an interval
 */
void IntervalSine(Tinterval *i,Tinterval *i_out)
{
  double l,u;

  if (IntervalSize(i)>=M_2PI)
    NewInterval(-1,1,i_out);
  else
    {
      l=NormalizeAngle(i->lower_limit);
      u=NormalizeAngle(i->upper_limit);
  
      if (u<l)
	{
	  Tinterval i_in;
	  Tinterval i_out1,i_out2;

	  i_in.lower_limit=l;
	  i_in.upper_limit=M_2PI;

	  IntervalSine(&i_in,&i_out1);

	  i_in.lower_limit=0.0;
	  i_in.upper_limit=u;

	  IntervalSine(&i_in,&i_out2);

	  i_out->lower_limit=(i_out1.lower_limit<i_out2.lower_limit?i_out1.lower_limit:i_out2.lower_limit);
	  i_out->upper_limit=(i_out1.upper_limit>i_out2.upper_limit?i_out1.upper_limit:i_out2.upper_limit);
	}
      else
	{
	  double a,b;

	  a=sin(l);
	  b=sin(u);

	  if ((l<=M_PI_2)&&(M_PI_2<=u))
	    i_out->upper_limit=1.0;
	  else
	    /* We +/- 1e-6 to compensate for possible errors 
	       introduced by the NormalizeAngle and the
	       computation of trigonometric functions. */
	    i_out->upper_limit=(a>b?a:b)+1e-6;

	  if ((l<=(3.0*M_PI_2))&&((3.0*M_PI_2)<=u))
	    i_out->lower_limit=-1.0;
	  else
	    i_out->lower_limit=(a<b?a:b)-1e-6;
	}
    }
}

/*
 * Computes the cosinus of an interval
 */
void IntervalCosine(Tinterval *i,Tinterval *i_out)
{
  double l,u;

  if (IntervalSize(i)>=M_2PI)
    NewInterval(-1,1,i_out);
  else
    {
      l=NormalizeAngle(i->lower_limit);
      u=NormalizeAngle(i->upper_limit);
  
      if (u<l)
	{
	  Tinterval i_in;
	  Tinterval i_out1,i_out2;

	  i_in.lower_limit=l;
	  i_in.upper_limit=M_2PI;

	  IntervalCosine(&i_in,&i_out1);

	  i_in.lower_limit=0.0;
	  i_in.upper_limit=u;

	  IntervalCosine(&i_in,&i_out2);

	  i_out->lower_limit=(i_out1.lower_limit<i_out2.lower_limit?i_out1.lower_limit:i_out2.lower_limit);
	  i_out->upper_limit=(i_out1.upper_limit>i_out2.upper_limit?i_out1.upper_limit:i_out2.upper_limit);
	}
      else
	{
	  double a,b;

	  a=cos(l);
	  b=cos(u);

	  if ((l<=0.0)&&(0.0<=u))
	    i_out->upper_limit=1.0;
	  else
	    /* We +/- 1e-6 to compensate for possible errors 
	       introduced by the NormalizeAngle and the
	       computation of trigonometric functions. */
	    i_out->upper_limit=(a>b?a:b)+1e-6;

	  if ((l<=M_PI)&&(M_PI<=u))
	    i_out->lower_limit=-1.0;
	  else
	    i_out->lower_limit=(a<b?a:b)-1e-6;
	}
    }
}

void IntervalTangent(Tinterval *i,Tinterval *i_out)
{
  double l,u;

  if (IntervalSize(i)>=M_2PI)
    NewInterval(-INF,INF,i_out);
  else
    {
      l=NormalizeAngle(i->lower_limit);
      u=NormalizeAngle(i->upper_limit);
  
      if (u<l)
	{
	  Tinterval i_in;
	  Tinterval i_out1,i_out2;

	  i_in.lower_limit=l;
	  i_in.upper_limit=M_2PI;

	  IntervalTangent(&i_in,&i_out1);

	  i_in.lower_limit=0.0;
	  i_in.upper_limit=u;

	  IntervalTangent(&i_in,&i_out2);

	  i_out->lower_limit=(i_out1.lower_limit<i_out2.lower_limit?i_out1.lower_limit:i_out2.lower_limit);
	  i_out->upper_limit=(i_out1.upper_limit>i_out2.upper_limit?i_out1.upper_limit:i_out2.upper_limit);
	}
      else
	{
	  if (((l<=M_PI_2)&&(M_PI_2<=u))||((l<=3*M_PI_2)&&(3*M_PI_2<=u)))
	    {
	      /* If the range includes one of the singular points, check
	         if the range is upper/lower bounded by the singularity */
	      if (u==M_PI_2)
		{
		  i_out->lower_limit=tan(l)-1e-6;
		  i_out->upper_limit=+INF;
		}
	      else
		{
		  if (l==3*M_PI_2)
		    {
		      i_out->lower_limit=-INF;
		      i_out->upper_limit=tan(u)+1e-6;
		    }
		  else
		    {
		      if (l==M_PI_2)
			{
			  if (u==3*M_PI_2)
			    {
			      i_out->lower_limit=-INF;
			      i_out->upper_limit=+INF; 
			    }
			  else
			    {
			      i_out->lower_limit=-INF;
			      i_out->upper_limit=tan(u)+1e-6;
			    }
			}
		      else
			{
			   if (u==3*M_PI_2)
			     {
			       i_out->lower_limit=tan(l)-1e-6;
			       i_out->upper_limit=+INF;
			     }
			   else
			     {
			       i_out->lower_limit=-INF;
			       i_out->upper_limit=+INF; 
			     }
			}
		    }
		}
	    }
	  else
	    {
	      double a,b;

	      a=tan(l);
	      b=tan(u);

	      i_out->lower_limit=(a<b?a:b)-1e-6;
	      i_out->upper_limit=(a>b?a:b)+1e-6;
	    }
	}
    }
}

void IntervalSecant2(Tinterval *i,Tinterval *i_out)
{
  Tinterval c,one;
  
  NewInterval(1,1,&one);
  IntervalCosine(i,&c);
  IntervalPow(&c,2,&c);
  IntervalDivision(&one,&c,i_out);
}

void IntervalSecant2Tangent(Tinterval *i,Tinterval *i_out)
{
  double l,u;

  if (IntervalSize(i)>=M_2PI)
    NewInterval(-INF,INF,i_out);
  else
    {
      l=NormalizeAngle(i->lower_limit);
      u=NormalizeAngle(i->upper_limit);
  
      if (u<l)
	{
	  Tinterval i_in;
	  Tinterval i_out1,i_out2;

	  i_in.lower_limit=l;
	  i_in.upper_limit=M_2PI;

	  IntervalTangent(&i_in,&i_out1);

	  i_in.lower_limit=0.0;
	  i_in.upper_limit=u;

	  IntervalTangent(&i_in,&i_out2);

	  i_out->lower_limit=(i_out1.lower_limit<i_out2.lower_limit?i_out1.lower_limit:i_out2.lower_limit);
	  i_out->upper_limit=(i_out1.upper_limit>i_out2.upper_limit?i_out1.upper_limit:i_out2.upper_limit);
	}
      else
	{
	  double c;

	  if (((l<=M_PI_2)&&(M_PI_2<=u))||((l<=3*M_PI_2)&&(3*M_PI_2<=u)))
	    {
	      /* If the range includes one of the singular points, check
	         if the range is upper/lower bounded by the singularity */
	      if (u==M_PI_2)
		{
		  c=cos(l);
		  i_out->lower_limit=tan(l)/(c*c)-1e-6;
		  i_out->upper_limit=+INF;
		}
	      else
		{
		  if (l==3*M_PI_2)
		    {
		      c=cos(u);
		      i_out->lower_limit=-INF;
		      i_out->upper_limit=tan(u)/(c*c)+1e-6;
		    }
		  else
		    {
		      if (l==M_PI_2)
			{
			  if (u==3*M_PI_2)
			    {
			      i_out->lower_limit=-INF;
			      i_out->upper_limit=+INF; 
			    }
			  else
			    {
			      c=cos(u);
			      i_out->lower_limit=-INF;
			      i_out->upper_limit=tan(u)/(c*c)+1e-6;
			    }
			}
		      else
			{
			   if (u==3*M_PI_2)
			     {
			       c=cos(l);
			       i_out->lower_limit=tan(l)/(c*c)-1e-6;
			       i_out->upper_limit=+INF;
			     }
			   else
			     {
			       i_out->lower_limit=-INF;
			       i_out->upper_limit=+INF; 
			     }
			}
		    }
		}
	    }
	  else
	    {
	      double a,b;

	      c=cos(l);
	      a=tan(l)/(c*c);

	      c=cos(u);
	      b=tan(u)/(c*c);
	      
	      i_out->lower_limit=(a<b?a:b)-1e-6;
	      i_out->upper_limit=(a>b?a:b)+1e-6;
	    }
	}
    }
}

void IntervalAtan2(Tinterval *is,Tinterval *ic,Tinterval *i_out)
{
  double a[4];
  unsigned int i;  
  double t1,t2;

  if ((IntervalSize(is)>0.5)||(IntervalSize(ic)>0.5)) 
    Error ("Interval atan2 only works for small intervals");

  a[0]=atan2(is->lower_limit,ic->lower_limit);
  a[1]=atan2(is->lower_limit,ic->upper_limit);
  a[2]=atan2(is->upper_limit,ic->lower_limit);
  a[3]=atan2(is->upper_limit,ic->upper_limit);
    
  t1=t2=a[0];
  for(i=1;i<4;i++)
    {
      if (a[i]<t1) t1=a[i];
      else {if (a[i]>t2) t2=a[i];}
    }
  
  i_out->lower_limit=t1;
  i_out->upper_limit=t2;

  if ((i_out->upper_limit-i_out->lower_limit)>M_PI) 
    {
      double d;
      
      d=i_out->lower_limit;
      i_out->lower_limit=i_out->upper_limit;
      i_out->upper_limit=d+M_2PI;
    }
}

void PrintSymbolInterval(FILE *f,Tinterval *i)
{
  if (EmptyInterval(i))
    fprintf(f,"(Empty Interval)");

  fprintf(f,"[");
  SYMBOL_PRINT(f,i->lower_limit);
  fprintf(f,",");
  SYMBOL_PRINT(f,i->upper_limit);
  fprintf(f,"]");
}

/*
 * Prints the contents of interval 'i' on file 'f'.
 */
void PrintInterval(FILE *f,Tinterval *i)
{
  if (EmptyInterval(i))
    fprintf(f,"(Empty Interval)");

  fprintf(f,"[");
  INF_PRINT(f,i->lower_limit);
  fprintf(f,",");
  INF_PRINT(f,i->upper_limit);
  fprintf(f,"]");
}

/*
 * Deletes the internal structures of interval 'i'.
 */
void DeleteInterval(Tinterval *i)
{
}
