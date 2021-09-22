#include "basic_algebra.h"

#include "defines.h"
#include "geom.h"

#include <math.h>
#include <string.h>

/** \file basic_algebra.c

    Definition of the basic lineal algebra routines used in the CuikSuite.

    These basic routines are implemented using BLAS, if available.
*/

inline void ClearVector(unsigned int n,double *v)
{
  memset(v,0,sizeof(double)*n);
}

void VectorAnd(unsigned int s,boolean *v1,boolean *v2,boolean *vo)
{
  unsigned int i;
  
  for(i=0;i<s;i++)
    vo[i]=(v1[i]&&v2[i]);
}

void VectorOr(unsigned int s,boolean *v1,boolean *v2,boolean *vo)
{
  unsigned int i;
  
  for(i=0;i<s;i++)
    vo[i]=(v1[i]||v2[i]);
}

CBLAS_INLINE double GeneralDotProduct(unsigned int s,double *v1,double *v2)
{
  #ifdef _CBLAS
    return(cblas_ddot(s,v1,1,v2,1));
  #else
    unsigned int i;
    double dp;
    
    dp=0.0;
    for(i=0;i<s;i++)
      dp+=(v1[i]*v2[i]);
    return(dp);
  #endif
}

CBLAS_INLINE double MatrixWeigthedDotProduct(unsigned int s,double *W,double *v1,double *v2)
{
  if (W==NULL)
    return(GeneralDotProduct(s,v1,v2));
  else
    {
      unsigned int i,j;
      double dp;
      
      dp=0.0;
      for(i=0;i<s;i++)
	{
	  dp+=(v1[i]*W[RC2INDEX(i,i,s,s)]*v2[i]);
	  for(j=i+1;j<s;j++)
	    dp+=2*(v1[i]*W[RC2INDEX(i,j,s,s)]*v2[j]);
	}
      return(dp);
    }
}

CBLAS_INLINE void ScaleVector(double f,unsigned int s,double *v)
{
  #ifdef _CBLAS
    cblas_dscal(s,f,v,1);
  #else
    unsigned int i;

    for(i=0;i<s;i++)
      v[i]*=f;
  #endif
}

CBLAS_INLINE void ScaleVector2(double f,unsigned int s,double *v,double *vout)
{
  #ifdef _CBLAS
    cblas_dcopy(s,v,1,vout,1);
    cblas_dscal(s,f,vout,1);
  #else
    unsigned int i;

    for(i=0;i<s;i++)
      vout[i]=v[i]*f;
  #endif
}

CBLAS_INLINE void OffsetVector(double o,unsigned int s,double *v)
{
  unsigned int i;

  for(i=0;i<s;i++)
    v[i]+=o;
}

CBLAS_INLINE void AccumulateVector(unsigned int s,double *v1,double *v2)
{
  #ifdef _CBLAS
    cblas_daxpy(s,1.0,v1,1,v2,1);
  #else
    unsigned int i;
    
    for(i=0;i<s;i++)
      v2[i]+=v1[i];
  #endif
}

CBLAS_INLINE void SumVector(unsigned int s,double *v1,double *v2,double *v)
{
  #ifdef _CBLAS
    /* If v==v2 and we copy v1 on v, v2 will be lost */
    if (v==v2)
      cblas_daxpy(s,1.0,v1,1,v,1);
    else
      {
	cblas_dcopy(s,v1,1,v,1); 
	cblas_daxpy(s,1.0,v2,1,v,1);
      }
  #else
    unsigned int i;
    
    for(i=0;i<s;i++)
      v[i]=(v1[i]+v2[i]);
  #endif
}

CBLAS_INLINE void SumVectorScale(unsigned int s,double *v1,double w,double *v2,double *v)
{
  #ifdef _CBLAS
    /* If v==v2 and we copy v1 on v, v2 will be lost */
    if (v==v2)
      {
	cblas_dscal(s,w,v2,1);
	cblas_daxpy(s,1.0,v1,1,v,1); /* v=v+v1=w*v2+v1 */
      }
    else
      {
	//cblas_dcopy(s,v1,1,v,1);
	if (v1!=v)
	  memcpy(v,v1,s*sizeof(double));
	cblas_daxpy(s,w,v2,1,v,1);
      }
  #else
    unsigned int i;

    for(i=0;i<s;i++)
      v[i]=(v1[i]+w*v2[i]);
  #endif
}

void CosVector(unsigned int s,double *v,double *co)
{
  unsigned int i;

  for(i=0;i<s;i++)
    co[i]=cos(v[i]);
}

void SinVector(unsigned int s,double *v,double *si)
{
  unsigned int i;

  for(i=0;i<s;i++)
    si[i]=sin(v[i]);
}

double AddVectorElements(unsigned int m,double *v)
{

  unsigned int i;
  double s;
  
  s=0;
  for(i=0;i<m;i++)
    s+=v[i];
  
  return(s);
}

double AddVectorPositiveElements(unsigned int m,double *v)
{

  unsigned int i;
  double s;
  
  s=0;
  for(i=0;i<m;i++)
    if (v[i]>0) s+=v[i];
  
  return(s);
}

unsigned int MaxVectorElement(unsigned int m,double *v)
{
  if (m==0)
    return(NO_UINT);
  else
    {
      unsigned int i;
      unsigned int me;
      double ma;
      
      me=0;
      ma=v[0];
      for(i=1;i<m;i++)
	{
	  if (v[i]>ma)
	    {
	      ma=v[i];
	      me=i;
	    }
	}
      return(me);
    }
}

double MaxVector(unsigned int m,double *v)
{
  if (m==0)
    return(0.0);
  else
    {
      unsigned int i;
      double ma;
      
      ma=v[0];
      for(i=1;i<m;i++)
	{
	  if (v[i]>ma)
	    ma=v[i];
	}
      return(ma);
    }
}

unsigned int MinVectorElement(unsigned int m,double *v)
{
  if (m==0)
    return(NO_UINT);
  else
    {
      unsigned int i;
      unsigned int me;
      double mi;
      
      me=0;
      mi=v[0];
      for(i=1;i<m;i++)
	{
	  if (v[i]<mi)
	    {
	      mi=v[i];
	      me=i;
	    }
	}
      return(me);
    }
}

double MinVector(unsigned int m,double *v)
{
  if (m==0)
    return(0.0);
  else
    {
      unsigned int i;
      double mi;
      
      mi=v[0];
      for(i=1;i<m;i++)
	{
	  if (v[i]<mi)
	    mi=v[i];
	}
      return(mi);
    }
}

void Vector2Range(double l,double u,double mode,
		  unsigned int m,double *v)
{
  if (m>0)
    {
      unsigned int i;
      double mi,ma,val;
      double s;
      
      if (l>u)
	Error("Lower can not be higher than upper in Vector2Range");
      s=u-l;
      if (s<ZERO)
	Error("Null range in Vector2Range");

      mi=pow(v[0],mode);
      ma=mi;
      for(i=1;i<m;i++)
	{
	  val=pow(v[i],mode);
	  
	  if (val<mi)
	    mi=val;
	  else
	    {
	      if (val>ma)
		ma=val;
	    }
	}

      if ((ma-mi)<ZERO)
	Error("Constant vector in Vector2Range");
      
      for(i=0;i<m;i++)
	{
	  val=pow(v[i],mode);
	  v[i]=(val-mi)/(ma-mi)*s+l;
	}
    }
}

CBLAS_INLINE void SubtractVector(unsigned int s,double *v1,double *v2)
{
  #ifdef _CBLAS
    cblas_daxpy(s,-1.0,v2,1,v1,1);
  #else
    unsigned int i;
    
    for(i=0;i<s;i++)
      v1[i]-=v2[i];
  #endif
}

/* We always inline DifferenceVector because it is used by other functions below */
inline void DifferenceVector(unsigned int s,double *v1,double *v2,double *v)
{
  #ifdef _CBLAS
    /* If v==v2 and we copy v1 on v, v2 will be lost */
    if (v==v2)
      {
	cblas_dscal(s,-1.0,v2,1);
	cblas_daxpy(s,1.0,v1,1,v,1); /* v=v+v1=-v2+v1 */
      }
    else
      {
	cblas_dcopy(s,v1,1,v,1);
	cblas_daxpy(s,-1.0,v2,1,v,1);
      }
  #else
    unsigned int i;

    for(i=0;i<s;i++)
      v[i]=(v1[i]-v2[i]);
  #endif
}

void DifferenceVectorSubset(unsigned int s,
			    boolean *subset,
			    double *v1,double *v2,double *v)
{
  if (subset==NULL)
    DifferenceVector(s,v1,v2,v);
  else
    {
      unsigned int i;

      for(i=0;i<s;i++)
	{
	  if (subset[i])
	    v[i]=(v1[i]-v2[i]);
	  else
	    v[i]=0.0;
	}
    }
}

void DifferenceVectorTopology(unsigned int s,unsigned int *tp,
			      double *v1,double *v2,double *v)
{
  if (tp==NULL)
    DifferenceVector(s,v1,v2,v);
  else
    {      
      unsigned int i;
      double d;
      
      for(i=0;i<s;i++)
	{
	  d=v1[i]-v2[i];
	  if (tp[i]==TOPOLOGY_S)
	    PI2PI(d);
	  v[i]=d;
	}
    }
}
void DifferenceVectorTopologySubset(unsigned int s,unsigned int *tp,
				    boolean *subset,
				    double *v1,double *v2,double *v)
{
  if (subset==NULL)
    DifferenceVectorTopology(s,tp,v1,v2,v);
  else
    {
      if (tp==NULL)
	DifferenceVectorSubset(s,subset,v1,v2,v);
      else
	{      
	  unsigned int i;
	  double d;
      
	  for(i=0;i<s;i++)
	    {
	      if (subset[i])
		{
		  d=v1[i]-v2[i];
		  if (tp[i]==TOPOLOGY_S)
		    PI2PI(d);
		  v[i]=d;
		}
	      else
		v[i]=0.0;
	    }
	}
    }
}

CBLAS_INLINE double Norm(unsigned int s,double *v)
{
  #ifdef _CBLAS
    return(cblas_dnrm2(s,v,1));
  #else
    unsigned int i;
    double n;

    n=0.0;
    for(i=0;i<s;i++)
      n+=(v[i]*v[i]);
    return(sqrt(n));
  #endif
}

CBLAS_INLINE double WeightedNorm(unsigned int s,double *w,double *v)
{
  if (w==NULL)
    return(Norm(s,v));
  else
    {
      unsigned int i;
      double n;

      n=0.0;
      for(i=0;i<s;i++)
	n+=w[i]*(v[i]*v[i]);
      return(sqrt(n));
    }
}

CBLAS_INLINE double MatrixWeightedNorm(unsigned int s,double *W,double *v)
{
  if (W==NULL)
    return(Norm(s,v));
  else
    {
      unsigned int i,j;
      double n;

      n=0.0;
      for(i=0;i<s;i++)
	{
	  n+=W[RC2INDEX(i,i,s,s)]*v[i]*v[i];
	  for(j=i+1;j<s;j++)
	    n+=2*W[RC2INDEX(i,j,s,s)]*v[i]*v[j];
	}
      return(sqrt(n));
    }
}

CBLAS_INLINE double NormWithStride(unsigned int s,unsigned int st,double *v)
{
  #ifdef _CBLAS
    return(cblas_dnrm2(s,v,st));
  #else
    unsigned int i,j;
    double n;

    n=0.0;
    for(i=0,j=0;i<s;i++,j+=st)
      n+=(v[j]*v[j]);
    return(sqrt(n));
  #endif
}

/* We inline SquaredDistance in all the cases, not just if CBLAS is present
   because it is used in functions below */
inline double SquaredDistance(unsigned int s,double *v1,double *v2)
{
  double n;
  unsigned int i;
  double v;

  n=0;
  for(i=0;i<s;i++)
    {
      v=v1[i]-v2[i];
      n+=(v*v);
    }
  
  return(n);
}

inline double WeightedSquaredDistance(unsigned int s,double *w,double *v1,double *v2)
{
  double n;
  unsigned int i;
  double v;

  if (w==NULL)
    n=SquaredDistance(s,v1,v2);
  else
    {
      n=0;
      for(i=0;i<s;i++)
	{
	  v=v1[i]-v2[i];
	  n+=w[i]*(v*v);
	}
    }
  
  return(n);
}

inline double MatrixWeightedSquaredDistance(unsigned int s,double *W,double *v1,double *v2)
{
  double n;
  unsigned int i,j;
  double v;

  if (W==NULL)
    n=SquaredDistance(s,v1,v2);
  else
    {
      n=0;
      for(i=0;i<s;i++)
	{
	  v=v1[i]-v2[i];
	  n+=W[RC2INDEX(i,i,s,s)]*(v*v);
	  for(j=i+1;j<s;j++)
	    {
	      v=v1[i]-v2[j];
	      n+=2*W[RC2INDEX(i,j,s,s)]*(v*v);
	    }
	}
    }
  
  return(n);
}

double SquaredDistanceSubset(unsigned int s,boolean *subset,double *v1,double *v2)
{
  double n;
  
  if (subset==NULL)
    n=SquaredDistance(s,v1,v2);
  else
    {
      unsigned int i;
      double v;
    
      n=0;
      for(i=0;i<s;i++)
	{
	  if (subset[i])
	    {
	      v=v1[i]-v2[i];
	      n+=(v*v);
	    }
	}
    }
  return(n);
}

double WeightedSquaredDistanceSubset(unsigned int s,boolean *subset,double *w,double *v1,double *v2)
{
  double n;
  
  if (subset==NULL)
    n=WeightedSquaredDistance(s,w,v1,v2);
  else
    {
      if (w==NULL)
	n=SquaredDistanceSubset(s,subset,v1,v2);
      else
	{
	  unsigned int i;
	  double v;
    
	  n=0;
	  for(i=0;i<s;i++)
	    {
	      if (subset[i])
		{
		  v=v1[i]-v2[i];
		  n+=w[i]*(v*v);
		}
	    }
	}
    }
  return(n);
} 

double MatrixWeightedSquaredDistanceSubset(unsigned int s,boolean *subset,double *W,double *v1,double *v2)
{
  double n;
  
  if (subset==NULL)
    n=MatrixWeightedSquaredDistance(s,W,v1,v2);
  else
    {
      if (W==NULL)
	n=SquaredDistanceSubset(s,subset,v1,v2);
      else
	{
	  unsigned int i,j;
	  double v;
    
	  n=0;
	  for(i=0;i<s;i++)
	    {
	      if (subset[i])
		{
		  v=v1[i]-v2[i];
		  n+=W[RC2INDEX(i,i,s,s)]*(v*v);
		  for(j=i+1;j<s;j++)
		    {
		      if (subset[j])
			{
			  v=v1[i]-v2[j];
			  n+=2*W[RC2INDEX(i,j,s,s)]*(v*v);
			}
		    }
		}
	    }
	}
    }
  return(n);
}

/* We inline Distance in all the cases, not just if CBLAS is present */
inline double Distance(unsigned int s,double *v1,double *v2)
{
  return(sqrt(SquaredDistance(s,v1,v2)));
}

inline double WeightedDistance(unsigned int s,double *w,double *v1,double *v2)
{
  return(sqrt(WeightedSquaredDistance(s,w,v1,v2)));
}

inline double MatrixWeightedDistance(unsigned int s,double *W,double *v1,double *v2)
{
  return(sqrt(MatrixWeightedSquaredDistance(s,W,v1,v2)));
}

double SquaredDistanceTopology(unsigned int s,unsigned int *tp,
			       double *v1,double *v2)
{
  double n;
  
  /* We in-line the DistanceTopology function, for efficiency reasons. */
  if (tp==NULL)
    n=SquaredDistance(s,v1,v2);
  else
    {
      unsigned int i;
      double v;

      n=0.0;
      for(i=0;i<s;i++)
	{
	  v=v1[i]-v2[i];
	  if ((tp[i]==TOPOLOGY_S)&&((v<-M_PI)||(v>M_PI)))
	    PI2PI(v);
	  n+=(v*v);
	}
    }
  return(n);
}

double WeightedSquaredDistanceTopology(unsigned int s,unsigned int *tp,double *w,
				       double *v1,double *v2)
{
  double n;
  
  /* We in-line the DistanceTopology function, for efficiency reasons. */
  if (tp==NULL)
    n=WeightedSquaredDistance(s,w,v1,v2);
  else
    {
      if (w==NULL)
	n=SquaredDistanceTopology(s,tp,v1,v2);
      else
	{
	  unsigned int i;
	  double v;

	  n=0.0;
	  for(i=0;i<s;i++)
	    {
	      v=v1[i]-v2[i];
	      if ((tp[i]==TOPOLOGY_S)&&((v<-M_PI)||(v>M_PI)))
		PI2PI(v);
	      n+=w[i]*(v*v);
	    }
	}
    }
  return(n);
}


double SquaredDistanceTopologyMin(double t2,unsigned int s,unsigned int *tp,
				  double *v1,double *v2)
{
  unsigned int i;
  double n,v;
 
  n=0.0;
  if (tp==NULL)
    {
      /* This is the Distance function inlined (and modified) here for
	 efficiency (avoid an additonal function call) */
      for(i=0;((i<s)&&(n<t2));i++)
	{
	  v=v1[i]-v2[i];
	  n+=(v*v);
	}

    }
  else
    {
      for(i=0;((i<s)&&(n<t2));i++)
	{
	  v=v1[i]-v2[i];
	  if ((tp[i]==TOPOLOGY_S)&&((v<-M_PI)||(v>M_PI)))
	    PI2PI(v);
	  n+=(v*v);
	}

    }
  return(n);
}

double WeightedSquaredDistanceTopologyMin(double t2,unsigned int s,unsigned int *tp,double *w,
					  double *v1,double *v2)
{
  unsigned int i;
  double n,v;
 
  n=0.0;
  
  if (w==NULL)
    n=SquaredDistanceTopologyMin(t2,s,tp,v1,v2);
  else
    {
      if (tp==NULL)
	{
	  /* This is the Distance function inlined (and modified) here for
	     efficiency (avoid an additonal function call) */
	  for(i=0;((i<s)&&(n<t2));i++)
	    {
	      v=v1[i]-v2[i];
	      n+=w[i]*(v*v);
	    }
	}
      else
	{
	  for(i=0;((i<s)&&(n<t2));i++)
	    {
	      v=v1[i]-v2[i];
	      if ((tp[i]==TOPOLOGY_S)&&((v<-M_PI)||(v>M_PI)))
		PI2PI(v);
	      n+=w[i]*(v*v);
	    }
	}
    }
  return(n);
}

double DistanceTopology(unsigned int s,unsigned int *tp,
			double *v1,double *v2)
{
  return(sqrt(SquaredDistanceTopology(s,tp,v1,v2)));
}

double WeightedDistanceTopology(unsigned int s,unsigned int *tp,double *w,
				double *v1,double *v2)
{
  return(sqrt(WeightedSquaredDistanceTopology(s,tp,w,v1,v2)));
}

double SquaredDistanceTopologySubset(unsigned int s,unsigned int *tp,
				     boolean *subset,
				     double *v1,double *v2)
{
  double n;
      
  if (subset==NULL)
    n=SquaredDistanceTopology(s,tp,v1,v2);
  else
    {
      if (tp==NULL)
	n=SquaredDistanceSubset(s,subset,v1,v2);
      else
	{
	  unsigned int i;
	  double v;
      
	  n=0.0;
	  for(i=0;i<s;i++)
	    {
	      if (subset[i])
		{
		  v=v1[i]-v2[i];
		  if ((tp[i]==TOPOLOGY_S)&&((v<-M_PI)||(v>M_PI)))
		    PI2PI(v);
		  n+=(v*v);
		}
	    }
	}
    }
  return(n);
}

double WeightedSquaredDistanceTopologySubset(unsigned int s,unsigned int *tp,
					     boolean *subset,double *w,
					     double *v1,double *v2)
{
  double n;
      
  if (subset==NULL)
    n=WeightedSquaredDistanceTopology(s,tp,w,v1,v2);
  else
    {
      if (tp==NULL)
	n=WeightedSquaredDistanceSubset(s,subset,w,v1,v2);
      else
	{
	  if (w==NULL)
	    n=SquaredDistanceTopologySubset(s,tp,subset,v1,v2);
	  else
	    {
	      unsigned int i;
	      double v;
      
	      n=0.0;
	      for(i=0;i<s;i++)
		{
		  if (subset[i])
		    {
		      v=v1[i]-v2[i];
		      if ((tp[i]==TOPOLOGY_S)&&((v<-M_PI)||(v>M_PI)))
			PI2PI(v);
		      n+=w[i]*(v*v);
		    }
		}
	    }
	}
    }
  return(n);
}

double DistanceTopologySubset(unsigned int s,unsigned int *tp,
			      boolean *subset,
			      double *v1,double *v2)
{
  return(sqrt(SquaredDistanceTopologySubset(s,tp,subset,v1,v2)));
}

double WeightedDistanceTopologySubset(unsigned int s,unsigned int *tp,
				      boolean *subset,double *w,
				      double *v1,double *v2)
{
  return(sqrt(WeightedSquaredDistanceTopologySubset(s,tp,subset,w,v1,v2)));
}

double DistanceTopologyMin(double t,unsigned int s,unsigned int *tp,
			   double *v1,double *v2)
{
  return(sqrt(SquaredDistanceTopologyMin(t*t,s,tp,v1,v2)));
}

double WeightedDistanceTopologyMin(double t,unsigned int s,unsigned int *tp,double *w,
				   double *v1,double *v2)
{
  return(sqrt(WeightedSquaredDistanceTopologyMin(t*t,s,tp,w,v1,v2)));
}

boolean CrossTopologyBorder(unsigned int s,unsigned int *tp,double *v1,double *v2)
{
  return(Distance(s,v1,v2)>DistanceTopology(s,tp,v1,v2));
}

CBLAS_INLINE void Normalize(unsigned int s,double *v)
{
  double n;

  #ifdef _CBLAS
    n=cblas_dnrm2(s,v,1);
    if (n>1e-6)
      cblas_dscal(s,1.0/n,v,1);
    else
      Error("Normalizing a null vector");
  #else
    unsigned int i;

    n=Norm(s,v);
    if (n>1e-6) /* avoid division by (almost) zero */
      {
	for(i=0;i<s;i++)
	  v[i]/=n;
      }
    else
      Error("Normalizing a null vector");
  #endif
}

double Mean(unsigned int s,double *v)
{
  unsigned int i;
  double m;
  
  m=0.0;
  for(i=0;i<s;i++)
    m+=v[i];
  
  return(m/((double)s));
}

double StdDev(unsigned int s,double m,double *v)
{
  unsigned int i;
  double sd,d;
  
  sd=0.0;
  for(i=0;i<s;i++)
    {
      d=v[i]-m;
      sd+=(d*d);
    }

  if (s>1)
    return(sqrt(sd/((double)s-1)));
  else
    return(sqrt(sd));
}

void ArrayPi2Pi(unsigned int n,unsigned int *t,double *a)
{
  unsigned int i;
  double *b;
  
  b=a;
  for(i=0;i<n;i++,b++)
    {
      if (t[i]==TOPOLOGY_S)
	PI2PI(*b);
    }
}

CBLAS_INLINE void GetRow(unsigned int k,unsigned int r,unsigned int c,double *m,double *v)
{
  #ifdef _CBLAS
    cblas_dcopy(c,&(m[RC2INDEX(k,0,r,c)]),(ROW_MAJOR?1:r),v,1);
  #else
    unsigned int i;
  
    for(i=0;i<c;i++)
      v[i]=m[RC2INDEX(k,i,r,c)];
  #endif
}

CBLAS_INLINE void GetColumn(unsigned int k,unsigned int r,unsigned int c,double *m,double *v)
{
  #ifdef _CBLAS
    cblas_dcopy(r,&(m[RC2INDEX(0,k,r,c)]),(ROW_MAJOR?c:1),v,1);
  #else
    unsigned int i;
  
    for(i=0;i<r;i++)
      v[i]=m[RC2INDEX(i,k,r,c)];
  #endif
}

CBLAS_INLINE void SetRow(double *v,unsigned int k,unsigned int r,unsigned int c,double *m)
{
  #ifdef _CBLAS
    cblas_dcopy(c,v,1,&(m[RC2INDEX(k,0,r,c)]),(ROW_MAJOR?1:r));
  #else
    unsigned int i;
  
    for(i=0;i<c;i++)
      m[RC2INDEX(k,i,r,c)]=v[i];
  #endif
}

CBLAS_INLINE void SetColumn(double *v,unsigned int k,unsigned int r,unsigned int c,double *m)
{
  #ifdef _CBLAS
    cblas_dcopy(r,v,1,&(m[RC2INDEX(0,k,r,c)]),(ROW_MAJOR?c:1));
  #else
    unsigned int i;
  
    for(i=0;i<r;i++)
      m[RC2INDEX(i,k,r,c)]=v[i];
  #endif
}


CBLAS_INLINE void ScaleRow(unsigned int k,double sc,unsigned int r,unsigned int c,double *m)
{
  #ifdef _CBLAS
    cblas_dscal(c,sc,&(m[RC2INDEX(k,0,r,c)]),(ROW_MAJOR?1:r));
  #else
    unsigned int i;
  
    for(i=0;i<c;i++)
      m[RC2INDEX(k,i,r,c)]*=sc;
  #endif
}

CBLAS_INLINE void ScaledAddRows(unsigned int r,unsigned int c,double *m,
				unsigned int n,unsigned int *sr,double *sc,
				unsigned int sv,double *v)
{
  if (n==0)
    {
      unsigned int i;
      
      for(i=0;i<c;i++)
	v[i*sv]=0;
    }
  else
    {
      #ifdef _CBLAS
        unsigned int i;

	for(i=0;i<c;i++)
	  v[i*sv]=0;
       
	for(i=0;i<n;i++)
	  cblas_daxpy(c,sc[i],&(m[RC2INDEX(sr[i],0,r,c)]),(ROW_MAJOR?1:r),v,sv); /* v=v+v1=w*v2+v1 */
      #else
        unsigned int i,j;
	
	for(j=0;j<c;j++)
	  {
	    v[j*sv]=0;
	    for(i=0;i<n;i++)
	      v[j*sv]+=sc[i]*m[RC2INDEX(sr[i],j,r,c)];
	  }
      #endif  
    }
}

CBLAS_INLINE void ScaleColumn(unsigned int k,double sc,unsigned int r,unsigned int c,double *m)
{
  #ifdef _CBLAS
    cblas_dscal(r,sc,&(m[RC2INDEX(0,k,r,c)]),(ROW_MAJOR?c:1));
  #else
    unsigned int i;
  
    for(i=0;i<r;i++)
      m[RC2INDEX(i,k,r,c)]*=sc;
  #endif
}

CBLAS_INLINE double RowsDotProduct(unsigned int i,unsigned int j,unsigned int r,unsigned int c,double *m)
{
  double s;
  unsigned int k;

  #ifdef _CBLAS
    unsigned int l;
  
    k=RC2INDEX(i,0,r,c);
    l=RC2INDEX(j,0,r,c);
    s=cblas_ddot(c,&(m[k]),(ROW_MAJOR?1:r),&(m[l]),(ROW_MAJOR?1:r));
  #else
    double v1,v2;

    s=0.0;
    for(k=0;k<c;k++)
      {
	v1=m[RC2INDEX(i,k,r,c)];
	v2=m[RC2INDEX(j,k,r,c)];
	s+=(v1*v2);
      }
  #endif
  return(s);
}

CBLAS_INLINE double ColumnsDotProduct(unsigned int i,unsigned int j,unsigned int r,unsigned int c,double *m)
{
  double s;
  unsigned int k;

  #ifdef _CBLAS
    unsigned int l;
  
    k=RC2INDEX(0,i,r,c);
    l=RC2INDEX(0,j,r,c);
    s=cblas_ddot(r,&(m[k]),(ROW_MAJOR?c:1),&(m[l]),(ROW_MAJOR?c:1));
  #else
    double v1,v2;

    s=0.0;
    for(k=0;k<r;k++)
      {
	v1=m[RC2INDEX(k,i,r,c)];
	v2=m[RC2INDEX(k,j,r,c)];
	s+=(v1*v2);
      }
  #endif
  return(s);
}

CBLAS_INLINE double RowSquaredNorm(unsigned int k,unsigned int r,unsigned int c,double *m)
{  
  double s;
  unsigned int i;

  #ifdef _CBLAS
    i=RC2INDEX(k,0,r,c);
    s=cblas_ddot(c,&(m[i]),(ROW_MAJOR?1:r),&(m[i]),(ROW_MAJOR?1:r));
  #else
    double v;

    s=0.0;
    for(i=0;i<c;i++)
      {
	v=m[RC2INDEX(k,i,r,c)];
	s+=(v*v);
      }
  #endif
  return(s);
}

CBLAS_INLINE double ColumnSquaredNorm(unsigned int k,unsigned int r,unsigned int c,double *m)
{
  double s;
  unsigned int i;

  #ifdef _CBLAS
    i=RC2INDEX(0,k,r,c);
    s=cblas_ddot(r,&(m[i]),(ROW_MAJOR?c:1),&(m[i]),(ROW_MAJOR?c:1));
  #else
    double v;

    s=0.0;
    for(i=0;i<r;i++)
      {
	v=m[RC2INDEX(i,k,r,c)];
	s+=(v*v);
      }
  #endif
  return(s);
}

CBLAS_INLINE void SumRowsScale(unsigned int i,double sc,unsigned int j,unsigned int r,unsigned int c,double *m)
{
  if (i==j)
    ScaleRow(i,1.0+sc,r,c,m);
  else
    {
      unsigned int k,l;

      #ifdef _CBLAS
        k=RC2INDEX(j,0,r,c);
	l=RC2INDEX(i,0,r,c);
	cblas_daxpy(c,sc,&(m[k]),(ROW_MAJOR?1:r),&(m[l]),(ROW_MAJOR?1:r));
      #else
	unsigned int n;

	for(n=0;n<c;n++)
	  {
	    k=RC2INDEX(i,n,r,c);
	    l=RC2INDEX(j,n,r,c);
	    m[k]+=sc*m[l];
	  }
      #endif
    }
}

CBLAS_INLINE void SumColumnsScale(unsigned int i,double sc,unsigned int j,unsigned int r,unsigned int c,double *m)
{
  if (i==j)
    ScaleColumn(i,1.0+sc,r,c,m);
  else
    {
      unsigned int k,l;

      #ifdef _CBLAS
        k=RC2INDEX(0,j,r,c);
	l=RC2INDEX(0,i,r,c);
	cblas_daxpy(r,sc,&(m[k]),(ROW_MAJOR?c:1),&(m[l]),(ROW_MAJOR?c:1));
      #else
	unsigned int n;

	for(n=0;n<c;n++)
	  {
	    k=RC2INDEX(n,i,r,c);
	    l=RC2INDEX(n,j,r,c);
	    m[k]+=sc*m[l];
	  }
      #endif
    }
}

CBLAS_INLINE void CopyRow(unsigned int i,unsigned int j,unsigned int r,unsigned int c,double *m)
{
  #ifdef _CBLAS
    cblas_dcopy(c,&(m[RC2INDEX(j,0,r,c)]),(ROW_MAJOR?1:r),&(m[RC2INDEX(i,0,r,c)]),(ROW_MAJOR?1:r));
  #else
    unsigned int k;
  
    for(k=0;k<c;k++)
      m[RC2INDEX(i,k,r,c)]=m[RC2INDEX(j,k,r,c)];
  #endif
}

CBLAS_INLINE void CopyColumn(unsigned int i,unsigned int j,unsigned int r,unsigned int c,double *m)
{
  #ifdef _CBLAS
    cblas_dcopy(r,&(m[RC2INDEX(0,j,r,c)]),(ROW_MAJOR?c:1),&(m[RC2INDEX(0,i,r,c)]),(ROW_MAJOR?c:1));
  #else
    unsigned int k;
  
    for(k=0;k<r;k++)
      m[RC2INDEX(k,i,r,c)]=m[RC2INDEX(k,j,r,c)];
  #endif
}

CBLAS_INLINE void IdentityMatrix(unsigned int n,double *M)
{
  unsigned int i;

  memset(M,0,sizeof(double)*n*n);
  for(i=0;i<n;i++)
    M[RC2INDEX(i,i,n,n)]=1.0;
}

CBLAS_INLINE void DiagonalMatrix(unsigned int n,double *v,double *M)
{
  unsigned int i;

  memset(M,0,sizeof(double)*n*n);
  for(i=0;i<n;i++)
    M[RC2INDEX(i,i,n,n)]=v[i];
}

void SymmetrizeMatrix(unsigned int n,double *M)
{
  unsigned int i,j,ndx1,ndx2;
  double v;

  for(i=0;i<n;i++)
    {
      for(j=i+1;j<n;j++)
	{
	  ndx1=RC2INDEX(i,j,n,n);
	  ndx2=RC2INDEX(j,i,n,n);
	  
	  v=(M[ndx1]+M[ndx2])/2.0;
	  
	  M[ndx1]=v;
	  M[ndx2]=v;
	}
    }
} 

CBLAS_INLINE void MatrixVectorProduct(unsigned int r,unsigned int c,double *A,double *b,double *o)
{
  double *out;
  
  if (b!=o)
    out=o;
  else
    {
      NEW(out,r,double);
    }
  
  #ifdef _CBLAS
    cblas_dgemv((ROW_MAJOR?CblasRowMajor:CblasColMajor),CblasNoTrans,r,c,1.0,A,(ROW_MAJOR?c:r),b,1,0.0,out,1);
  #else
    unsigned int i,j;

    for(i=0;i<r;i++)
      {
	out[i]=0.0;
	for(j=0;j<c;j++)
	  out[i]+=(A[RC2INDEX(i,j,r,c)]*b[j]);
      }
  #endif
    
  if (b==o)
    {
      memcpy(o,out,sizeof(double)*r);
      free(out);
    }
}

CBLAS_INLINE void MatrixVectorProductAccum(unsigned int r,unsigned int c,double *A,double *b,double *o)
{
  #if (_DEBUG>0)
    if (b==o)
      Error("Repeated input/output vector in MatrixVectorProductAccum");
  #endif
    
  #ifdef _CBLAS
    cblas_dgemv((ROW_MAJOR?CblasRowMajor:CblasColMajor),CblasNoTrans,r,c,1.0,A,(ROW_MAJOR?c:r),b,1,1.0,o,1);
  #else
    unsigned int i,j;

    for(i=0;i<r;i++)
      {
	for(j=0;j<c;j++)
	  o[i]+=(A[RC2INDEX(i,j,r,c)]*b[j]);
      }
  #endif
}
  
CBLAS_INLINE void TMatrixVectorProduct(unsigned int r,unsigned int c,double *A,double *b,double *o)
{
  double *out;
  
  if (b!=o)
    out=o;
  else
    {
      NEW(out,r,double);
    }
  
  #ifdef _CBLAS
    cblas_dgemv((ROW_MAJOR?CblasRowMajor:CblasColMajor),CblasTrans,r,c,1.0,A,(ROW_MAJOR?c:r),b,1,0.0,out,1);
  #else
    unsigned int i,j;
    
    for(i=0;i<c;i++)
      {
	out[i]=0.0;
	for(j=0;j<r;j++)
	  out[i]+=(A[RC2INDEX(j,i,r,c)]*b[j]);
      }
  #endif
    
  if (b==o)
    {
      memcpy(o,out,sizeof(double)*c);
      free(out);
    }
}
 
CBLAS_INLINE void TMatrixVectorProductAccum(unsigned int r,unsigned int c,double *A,double *b,double *o)
{  
  #if (_DEBUG>0)
    if (b==o)
      Error("Repeated input/output vector in TMatrixVectorProductAccum");
  #endif

  #ifdef _CBLAS
    cblas_dgemv((ROW_MAJOR?CblasRowMajor:CblasColMajor),CblasTrans,r,c,1.0,A,(ROW_MAJOR?c:r),b,1,1.0,o,1);
  #else
    unsigned int i,j;
    
    for(i=0;i<c;i++)
      {
	for(j=0;j<r;j++)
	  o[i]+=(A[RC2INDEX(j,i,r,c)]*b[j]);
      }
  #endif   
}
 
CBLAS_INLINE void TMatrixVectorStrideProduct(unsigned int r,unsigned int c,double *A,unsigned int s,double *b,double *o)
{
  double *out;
  
  if (b!=o)
    out=o;
  else
    {
      NEW(out,c,double);
    }
    
  #ifdef _CBLAS
    cblas_dgemv((ROW_MAJOR?CblasRowMajor:CblasColMajor),CblasTrans,r,c,1.0,A,(ROW_MAJOR?c:r),b,s,0.0,out,1);
  #else
    unsigned int i,j;

    for(i=0;i<c;i++)
      {
	out[i]=0.0;
	for(j=0;j<r;j++)
	  out[i]+=(A[RC2INDEX(j,i,r,c)]*b[j*s]);
      }
  #endif
    
  if (b==o)
    {
      memcpy(o,out,sizeof(double)*c);
      free(out);
    }
}

CBLAS_INLINE void AccumulateMatrix(unsigned int nr,unsigned int nc,double *B,double *A)
{
  AccumulateVector(nr*nc,B,A);
}

CBLAS_INLINE void AccumulateTMatrix(unsigned int nr,double *B,double *A)
{
  unsigned int i,j,ndx1,ndx2;
  double s;

  for(i=0;i<nr;i++)
    {
      ndx1=RC2INDEX(i,i,nr,nr);
      A[ndx1]+=B[ndx1];
      for(j=i+1;j<nr;j++)
	{
	  ndx1=RC2INDEX(i,j,nr,nr);
	  ndx2=RC2INDEX(j,i,nr,nr);
	  if (A==B)
	    {
	      s=A[ndx1]+B[ndx2];
	      A[ndx1]=s;
	      A[ndx2]=s;
	    }
	  else
	    {
	      A[ndx1]+=B[ndx2];
	      A[ndx2]+=B[ndx1];
	    }
	}
    }
}

CBLAS_INLINE void SubtractMatrix(unsigned int nr,unsigned int nc,double *A,double *B)
{
  SubtractVector(nr*nc,A,B);
}

CBLAS_INLINE void MatrixMatrixProduct(unsigned int ra,unsigned int ca,double *A,
				      unsigned int cb,double *B,double *C)
{
  double *out;

  if ((C==A)||(C==B))
    {
      NEW(out,ra*cb,double);
    }
  else
    out=C;
    
  #ifdef _CBLAS
    /* A is ra x ca
       B is ca x cb
       C is ra x cb */
    cblas_dgemm((ROW_MAJOR?CblasRowMajor:CblasColMajor),CblasNoTrans,CblasNoTrans,
		ra,cb,ca,1.0,A,(ROW_MAJOR?ca:ra),B,(ROW_MAJOR?cb:ca),0.0,out,(ROW_MAJOR?cb:ra));
  #else
    unsigned int i,j,k;
    
    /*  A * B */
    for(i=0;i<ra;i++)
      {
	for(j=0;j<cb;j++)
	  {
	    out[RC2INDEX(i,j,ra,cb)]=0.0;
	    for(k=0;k<ca;k++)
	      out[RC2INDEX(i,j,ra,cb)]+=(A[RC2INDEX(i,k,ra,ca)]*B[RC2INDEX(k,j,ca,cb)]);
	}
      }
  #endif
    
  if ((C==A)||(C==B))
    {
      memcpy(C,out,sizeof(double)*ra*cb);
      free(out);
    }
}

 CBLAS_INLINE void MatrixMatrixProductAccum(unsigned int ra,unsigned int ca,double *A,
                                            unsigned int cb,double *B,double *C)
{
  #if (_DEBUG>0)
    if ((A==C)||(B==C))
      Error("Repeated input/output matrix in MatrixMatrixProductAccum");
  #endif
    
  #ifdef _CBLAS
    /* A is ra x ca
       B is ca x cb
       C is ra x cb */
    cblas_dgemm((ROW_MAJOR?CblasRowMajor:CblasColMajor),CblasNoTrans,CblasNoTrans,
		ra,cb,ca,1.0,A,(ROW_MAJOR?ca:ra),B,(ROW_MAJOR?cb:ca),1.0,C,(ROW_MAJOR?cb:ra));
  #else
    unsigned int i,j,k;
    
    /*  A * B */
    for(i=0;i<ra;i++)
      {
	for(j=0;j<cb;j++)
	  {
	    for(k=0;k<ca;k++)
	      C[RC2INDEX(i,j,ra,cb)]+=(A[RC2INDEX(i,k,ra,ca)]*B[RC2INDEX(k,j,ca,cb)]);
	}
      }
  #endif    
}
 
CBLAS_INLINE void MatrixTMatrixProduct(unsigned int ra,unsigned int ca,double *A,
				       unsigned int rb,double *B,double *C)
{
  double *out;
  
  if ((C==A)||(C==B))
    {
      NEW(out,ra*rb,double);
    }
  else
    out=C;
  
  #ifdef _CBLAS
    /* A   is ra x ca
       B^t is ca x rb
       C   is ra x rb */
    cblas_dgemm((ROW_MAJOR?CblasRowMajor:CblasColMajor),CblasNoTrans,CblasTrans,
		ra,rb,ca,1.0,A,(ROW_MAJOR?ca:ra),B,(ROW_MAJOR?ca:rb),0.0,out,(ROW_MAJOR?rb:ra));
  #else
    unsigned int i,j,k;
    
    /*  A * B */
    for(i=0;i<ra;i++)
      {
	for(j=0;j<rb;j++)
	  {
	    out[RC2INDEX(i,j,ra,rb)]=0.0;
	    for(k=0;k<ca;k++)
	      out[RC2INDEX(i,j,ra,rb)]+=(A[RC2INDEX(i,k,ra,ca)]*B[RC2INDEX(j,k,rb,ca)]);
	}
      }
  #endif
    
  if ((C==A)||(C==B))
    {
      memcpy(C,out,sizeof(double)*ra*rb);
      free(out);
    }
}

CBLAS_INLINE void TMatrixMatrixProduct(unsigned int ra,unsigned int ca,double *A,
				       unsigned int cb,double *B,double *C)
{
  double *out;

  if ((C==A)||(C==B))
    {
      NEW(out,ca*cb,double);
    }
  else
    out=C;
    
  #ifdef _CBLAS
    /* A^t is ca x ra
       B   is ra x cb
       C   is ca x cb */
    cblas_dgemm((ROW_MAJOR?CblasRowMajor:CblasColMajor),CblasTrans,CblasNoTrans,
	        ca,cb,ra,1.0,A,(ROW_MAJOR?ca:ra),B,(ROW_MAJOR?cb:ra),0.0,out,(ROW_MAJOR?cb:ca));
  #else
    unsigned int i,j,k;
    
    /*  A^t * B */
    for(i=0;i<ca;i++)
      {
	for(j=0;j<cb;j++)
	  {
	    out[RC2INDEX(i,j,ca,cb)]=0.0;
	    for(k=0;k<ra;k++)
	      out[RC2INDEX(i,j,ca,cb)]+=(A[RC2INDEX(k,i,ra,ca)]*B[RC2INDEX(k,j,ra,cb)]);
	  }
      }
  #endif

  if ((C==A)||(C==B))
    {
      memcpy(C,out,sizeof(double)*ca*cb);
      free(out);
    }
}

double MinCosinusBetweenSubSpaces(unsigned int m,unsigned int k,double *T1,double *T2)
{
  unsigned int i;
  double c,cm;
  double *proj;
  #ifndef _CBLAS
    unsigned int s,j;
  #endif

  NEW(proj,k,double);
  
  cm=1; /*minimal cosinus*/
  for(i=0;i<k;i++)
    {
      #ifdef _CBLAS
        #if (ROW_MAJOR)
          TMatrixVectorStrideProduct(m,k,T1,k,&(T2[i]),proj);
        #else
          TMatrixVectorProduct(m,k,T1,&(T2[i*m]),proj);
        #endif
      #else
        for(j=0;j<k;j++)
	  {
	    proj[j]=0;
	    for(s=0;s<m;s++)
	      proj[j]+=(T1[RC2INDEX(s,j,m,k)]*T2[RC2INDEX(s,i,m,k)]);
	  }
      #endif
      /* Assuming vector of T1 and T2 orthonormal, c is the cosinus of
         the i-th vector of basis T2 with respect to the subspace defined
         by T1. Note that in the projection the angle can not be larger than
         pi/2 and, therefore, the cosinus is in [0,1]*/
      c=Norm(k,proj);
      
      /* We search for the minimum cosinus = maximum angle. This is a measure
         of the difference between the two subspaces.*/
      if (c<cm) cm=c;
    }
    
  free(proj);

  return(cm);
}

unsigned int OrthonormalizeRows(unsigned int r,unsigned int c,double *m)
{
  unsigned int i,j,k;
  double n,n1;

  k=0; /* number of independent orthonormalized rows so far */
  for(i=0;i<r;i++)
    {
      for(j=0;j<k;j++)
	{
	  n1=RowsDotProduct(j,i,r,c,m);
	  SumRowsScale(i,-n1,j,r,c,m);
	}
      
      n=sqrt(RowSquaredNorm(i,r,c,m));
      if (n>1e-6)
	{
	  ScaleRow(i,1.0/n,r,c,m);
	  if (k<i)
	    CopyRow(k,i,r,c,m);
	  k++;
	}
    }
  return(k);
}

unsigned int OrthonormalizeColumns(unsigned int r,unsigned int c,double *m)
{
  unsigned int i,j,k;
  double n,n1;

  k=0;  /* number of independent orthonormalized columns so far */
  for(i=0;i<c;i++)
    {
      /* some input vectors may be already null: skip them */
      n=sqrt(ColumnSquaredNorm(i,r,c,m));
      if (n>1e-6)
	{
	  /* substract the components in the already processed vectors */
	  for(j=0;j<k;j++)
	    {
	      n1=ColumnsDotProduct(j,i,r,c,m);
	      SumColumnsScale(i,-n1,j,r,c,m);
	    }

	  /* and normalize */
	  n=sqrt(ColumnSquaredNorm(i,r,c,m));
	  if (n>1e-6)
	    {
	      ScaleColumn(i,1.0/n,r,c,m);
	      if (k<i)
		CopyColumn(k,i,r,c,m);
	      k++;
	    }
	}
    }
  return(k);
}

void ProjectToColumnSubSpace(unsigned int rs,unsigned int cs,double *ms,
			     unsigned int c,double *m)
{
  double *p;

  NEW(p,cs*c,double);
  
  TMatrixMatrixProduct(rs,cs,ms,c,m,p);
  MatrixMatrixProduct(rs,cs,ms,c,p,m);
  
  free(p);
}

CBLAS_INLINE void RankOneUpdate(double sc,unsigned int nr,double *vr,
				unsigned int nc,double *vc,
				double *m)
{   
  #ifdef _CBLAS
    cblas_dger((ROW_MAJOR?CblasRowMajor:CblasColMajor),nr,nc,sc,vr,1,vc,1,m,(ROW_MAJOR?nc:nr));
  #else
    unsigned int i,j;

    for(i=0;i<nr;i++)
      {
	for(j=0;j<nc;j++)
	  m[RC2INDEX(i,j,nr,nc)]+=sc*(vr[i]*vc[j]);
      }
  #endif
}

CBLAS_INLINE void SubMatrixFromMatrix(unsigned int nr1,unsigned int nc1,double *m1,
				      unsigned int nri,unsigned int nci,
				      unsigned int nr,unsigned int nc,double *m)
{
  #ifdef _CBLAS
    unsigned int i,j,k;
    #if (ROW_MAJOR)
      if (nr1<nc1)
	{
	  /* copy row by row */
	  for(j=0,i=0,k=RC2INDEX(nri,nci,nr,nc);j<nr1;j++,i+=nc1,k+=nc)
	    cblas_dcopy(nc1,&(m1[i]),1,&(m[k]),1);
	}
      else
	{
	  /* copy column by column */
	  for(i=0,k=RC2INDEX(nri,nci,nr,nc);i<nc1;i++,k++)
	    cblas_dcopy(nr1,&(m1[i]),nc1,&(m[k]),nc);
	}
    #else
      if (nr1<nc1)
	{
	  /* copy row by row */
	  for(i=0,k=RC2INDEX(nri,nci,nr,nc);i<nr1;i++,k++)
	    cblas_dcopy(nc1,&(m1[i]),nr1,&(m[k]),nr);
	}
      else
	{
	  /* copy column by column */
	  for(j=0,i=0,k=RC2INDEX(nri,nci,nr,nc);j<nc1;j++,i+=nr1,k+=nr)
	    cblas_dcopy(nr1,&(m1[i]),1,&(m[k]),1);
	}
    #endif
  #else
    unsigned int i,j,k,l;
    
    for(i=0,k=nri;i<nr1;i++,k++)
      {
	for(j=0,l=nci;j<nc1;j++,l++)
	  m[RC2INDEX(k,l,nr,nc)]=m1[RC2INDEX(i,j,nr1,nc1)];
      }
  #endif
}

CBLAS_INLINE void AddSubMatrix(double sc,
			       unsigned int nr1,unsigned int nc1,double *m1,
			       unsigned int nri,unsigned int nci,
			       unsigned int nr,unsigned int nc,double *m)
{
  #ifdef _CBLAS
    unsigned int i,j,k;
    #if (ROW_MAJOR)
      if (nr1<nc1)
	{
	  /* copy row by row */
	  for(j=0,i=0,k=RC2INDEX(nri,nci,nr,nc);j<nr1;j++,i+=nc1,k+=nc)
	    cblas_daxpy(nc1,sc,&(m1[i]),1,&(m[k]),1);
	}
      else
	{
	  /* copy column by column */
	  for(i=0,k=RC2INDEX(nri,nci,nr,nc);i<nc1;i++,k++)
	    cblas_daxpy(nr1,sc,&(m1[i]),nc1,&(m[k]),nc);
	}
    #else
      if (nr1<nc1)
	{
	  /* copy row by row */
	  for(i=0,k=RC2INDEX(nri,nci,nr,nc);i<nr1;i++,k++)
	    cblas_daxpy(nc1,sc,&(m1[i]),nr1,&(m[k]),nr);
	}
      else
	{
	  /* copy column by column */
	  for(j=0,i=0,k=RC2INDEX(nri,nci,nr,nc);j<nc1;j++,i+=nr1,k+=nr)
	    cblas_daxpy(nr1,sc,&(m1[i]),1,&(m[k]),1);
	}
    #endif
  #else
    unsigned int i,j,k,l;
    
    for(i=0,k=nri;i<nr1;i++,k++)
      {
	for(j=0,l=nci;j<nc1;j++,l++)
	  m[RC2INDEX(k,l,nr,nc)]+=(sc*m1[RC2INDEX(i,j,nr1,nc1)]);
      }
  #endif
}

CBLAS_INLINE void SubMatrixFromSubMatrix(unsigned int nrs,unsigned int ncs,
					 unsigned int nrc,unsigned int ncc,
					 unsigned int nr1,unsigned int nc1,double *m1,
					 unsigned int nri,unsigned int nci,
					 boolean trans,
					 unsigned int nr,unsigned int nc,double *m)
{
  unsigned int rf,cf;

  /* final row/column to take from m1 (actually 1st row/column not to take :) */
  rf=nrs+nrc;
  cf=ncs+ncc;
  
  #ifdef _CBLAS
    unsigned int i,j,k;
    #if (ROW_MAJOR)
      if (nr1<nc1)
	{
	  /* copy row by row */
	  if (trans)
	    { 
	      for(j=nrs,i=RC2INDEX(nrs,ncs,nr1,nc1),k=RC2INDEX(nri,nci,nr,nc);j<rf;j++,i+=nc1,k+=1)
		cblas_dcopy(ncc,&(m1[i]),1,&(m[k]),nc);
	    }
	  else
	    {
	      for(j=nrs,i=RC2INDEX(nrs,ncs,nr1,nc1),k=RC2INDEX(nri,nci,nr,nc);j<rf;j++,i+=nc1,k+=nc)
		cblas_dcopy(ncc,&(m1[i]),1,&(m[k]),1);
	    }
	}
      else
	{
	  /* copy column by column */
	  if (trans)
	    {
	      for(j=ncs,i=RC2INDEX(nrs,ncs,nr1,nc1),k=RC2INDEX(nri,nci,nr,nc);j<cf;j++,i++,k+=nc)
		cblas_dcopy(nrc,&(m1[i]),nc1,&(m[k]),1);
	    }
	  else
	    {
	      for(j=ncs,i=RC2INDEX(nrs,ncs,nr1,nc1),k=RC2INDEX(nri,nci,nr,nc);j<cf;j++,i++,k++)
		cblas_dcopy(nrc,&(m1[i]),nc1,&(m[k]),nc);
	    }
	}
    #else
      /* column major */
      if (nr1<nc1)
	{
	  /* copy row by row */
	  if (trans)
	    {
	      for(j=nrs,i=RC2INDEX(nrs,ncs,nr1,nc1),k=RC2INDEX(nri,nci,nr,nc);j<rf;j++,i++,k+=nr)
		cblas_dcopy(ncc,&(m1[i]),nr1,&(m[k]),1);
	    }
	  else
	    {
	      for(j=nrs,i=RC2INDEX(nrs,ncs,nr1,nc1),k=RC2INDEX(nri,nci,nr,nc);j<rf;j++,i++,k++)
		cblas_dcopy(ncc,&(m1[i]),nr1,&(m[k]),nr);
	    }
	}
      else
	{
	  /* copy column by column */
	  if (trans)
	    {
	      for(j=ncs,i=RC2INDEX(nrs,ncs,nr1,nc1),k=RC2INDEX(nri,nci,nr,nc);j<cf;j++,i+=nr1,k+=1)
		cblas_dcopy(nrc,&(m1[i]),1,&(m[k]),nr);
	    }
	  else
	    {
	      for(j=ncs,i=RC2INDEX(nrs,ncs,nr1,nc1),k=RC2INDEX(nri,nci,nr,nc);j<cf;j++,i+=nr1,k+=nr)
		cblas_dcopy(nrc,&(m1[i]),1,&(m[k]),1);
	    }
	}
    #endif
  #else
    unsigned int i,j,k,l;

    if (trans)
      {
	for(i=nrs,l=nci;i<rf;i++,l++)
	  {
	    for(j=ncs,k=nri;j<cf;j++,k++)
	      m[RC2INDEX(k,l,nr,nc)]=m1[RC2INDEX(i,j,nr1,nc1)];
	  }
      }
    else
      {
	for(i=nrs,k=nri;i<rf;i++,k++)
	  {
	    for(j=ncs,l=nci;j<cf;j++,l++)
	      m[RC2INDEX(k,l,nr,nc)]=m1[RC2INDEX(i,j,nr1,nc1)];
	  }
      }
  #endif
}

CBLAS_INLINE void MatrixFromSubMatrix(unsigned int r_src,unsigned int c_src,double *m_src,
				      unsigned int rs,unsigned int cs,
				      unsigned int r_dst,unsigned int c_dst,double *m_dst)
{
  #ifdef _CBLAS
    unsigned int i,j,k;
    #if (ROW_MAJOR)
      if (r_dst<c_dst)
	{
	  /* copy row by row */
	  for(j=0,k=RC2INDEX(rs,cs,r_src,c_src),i=0;j<r_dst;j++,k+=c_src,i+=c_dst)
	    cblas_dcopy(c_dst,&(m_src[k]),1,&(m_dst[i]),1);
	}
      else
	{
	  /* copy column by column */
	  for(i=0,k=RC2INDEX(rs,cs,r_src,c_src);i<c_dst;i++,k++)
	    cblas_dcopy(r_dst,&(m_src[k]),c_src,&(m_dst[i]),c_dst);
	}
    #else
      if (r_dst<c_dst)
	{
	  /* copy row by row */
	  for(i=0,k=RC2INDEX(rs,cs,r_src,c_src);i<r_dst;i++,k++)
	    cblas_dcopy(c_dst,&(m_src[k]),r_src,&(m_dst[i]),r_dst);
	}
      else
	{
	  /* copy column by column */
	  for(j=0,k=RC2INDEX(rs,cs,r_src,c_src),i=0;j<c_dst;j++,k+=r_src,i+=r_dst)
	    cblas_dcopy(r_dst,&(m_src[k]),1,&(m_dst[i]),1);
	}
    #endif
  #else
    unsigned int i,j,k,l;
    
    for(i=0,k=rs;i<r_dst;i++,k++)
      {
	for(j=0,l=cs;j<c_dst;j++,l++)
	  m_dst[RC2INDEX(i,j,r_dst,c_dst)]=m_src[RC2INDEX(k,l,r_src,c_src)];
      }
  #endif
}

CBLAS_INLINE void SubMatrixFromTMatrix(unsigned int nr1,unsigned int nc1,double *m1,
				       unsigned int nri,unsigned int nci,
				       unsigned int nr,unsigned int nc,double *m)
{ 
  #ifdef _CBLAS
    unsigned int i,j,k;
    #if (ROW_MAJOR)
      if (nc1<nr1)
	{
	  /* copy row by row (of the transposed) */ 
	  for(i=0,k=RC2INDEX(nri,nci,nr,nc);i<nc1;i++,k+=nc)
	    cblas_dcopy(nr1,&(m1[i]),nc1,&(m[k]),1);
	}
      else
	{
	  /* copy column by column (of the transposed) */
	  for(j=0,i=0,k=RC2INDEX(nri,nci,nr,nc);j<nr1;j++,i+=nc1,k++)
	    cblas_dcopy(nc1,&(m1[i]),1,&(m[k]),nc);
	}
    #else
      if (nc1<nr1)
	{
	  /* copy row by row (of the transposed) */
	  for(j=0,i=0,k=RC2INDEX(nri,nci,nr,nc);j<nc1;j++,i+=nr1,k++)
	    cblas_dcopy(nr1,&(m1[i]),1,&(m[k]),nr);
	}
      else
	{
	  /* copy column by column (of the transposed) */
	  for(i=0,k=RC2INDEX(nri,nci,nr,nc);i<nr1;i++,k+=nr)
	    cblas_dcopy(nc1,&(m1[i]),nr1,&(m[k]),1);
	}    
    #endif
  #else
    unsigned int i,j,k,l;
    
    for(i=0,k=nri;i<nc1;i++,k++)
      {
	for(j=0,l=nci;j<nr1;j++,l++)
	  m[RC2INDEX(k,l,nr,nc)]=m1[RC2INDEX(j,i,nr1,nc1)];
      }
  #endif
}

CBLAS_INLINE void SelectMatrixColumns(boolean *sc,unsigned int nr,unsigned int nc,double *m)
{
  unsigned int i,k;
  
  #if (ROW_MAJOR)
    unsigned int l;

    k=0;
    for(i=0;i<nr;i++)
      {
	for(l=0;l<nc;l++)
	  {
	    if (sc[l])
	      m[k++]=m[RC2INDEX(i,l,nr,nc)];
	  }
      }
  #else
    #ifndef _CBLAS
      unsigned int l;
    #endif
    
    k=0;
    for(i=0;i<nc;i++)
      {
	if (sc[i])
	  {
	    if (i!=k)
	      {
	        #ifdef _CBLAS
	          cblas_dcopy(nr,&(m[RC2INDEX(0,i,nr,nc)]),1,&(m[RC2INDEX(0,k,nr,nc)]),1);
	        #else	
		  for(l=0;l<nr;l++)
		    m[RC2INDEX(l,k,nr,nc)]=m[RC2INDEX(l,i,nr,nc)];
	        #endif
	      } 
	    k++;
	  }
      }
  #endif
}

CBLAS_INLINE void SelectMatrixRows(boolean *sr,unsigned int nr,unsigned int nc,double *m)
{
  unsigned int i,k;
    
  #if (ROW_MAJOR)
    #ifndef _CBLAS
      unsigned int l;
    #endif

    k=0;
    for(i=0;i<nr;i++)
      {
	if (sr[i])
	  {
	    if (i!=k)
	      #ifdef _CBLAS
	        cblas_dcopy(nc,&(m[RC2INDEX(i,0,nr,nc)]),1,&(m[RC2INDEX(k,0,nr,nc)]),1);
	      #else
	        for(l=0;l<nc;l++)
		  m[RC2INDEX(k,l,nr,nc)]=m[RC2INDEX(i,l,nr,nc)];
	      #endif
	    k++;
	  }
      }
    
  #else
    unsigned int l;

    k=0;
    for(i=0;i<nc;i++)
      {
	for(l=0;l<nr;l++)
	  {
	    if (sr[l])
	      m[k++]=m[RC2INDEX(l,i,nr,nc)];
	  }
      }
    
  #endif
}

void PrintVector(FILE *f,char *label,unsigned int n,double *v)
{
  unsigned int i;

  if (label!=NULL)
    fprintf(f,"%s=",label);
  fprintf(f,"[ ");
  for(i=0;i<n;i++)
    fprintf(f,"%.19f ",v[i]);
  fprintf(f,"];\n");
}

void SaveVector(FILE *f,unsigned int n,double *v)
{
  unsigned int i;

  for(i=0;i<n;i++)
    fprintf(f,"%.16f\n",v[i]);
} 


void PrintMatrix(FILE *f,char *label,unsigned int r,unsigned int c,double *m)
{
  unsigned int i,j,l;

  if (label!=NULL)
    {
      l=strlen(label)+3;
      fprintf(f,"%s=",label);
    }
  else
    l=3;
  fprintf(f,"[ ");
  for(i=0;i<r;i++)
    {
      for(j=0;j<c;j++) 
	fprintf(f,"%.19f ",m[RC2INDEX(i,j,r,c)]);
      fprintf(f,"\n");
      for(j=0;j<l;j++)
	fprintf(f," ");
    }
  fprintf(f,"];\n");
}

void PrintTMatrix(FILE *f,char *label,unsigned int r,unsigned int c,double *m)
{
  unsigned int i,j,l;

  if (label!=NULL)
    {
      l=strlen(label)+3;
      fprintf(f,"%s=",label);
    }
  else
    l=3;
  fprintf(f,"[ ");
  for(i=0;i<c;i++)
    {
      for(j=0;j<r;j++) 
	fprintf(f,"%.19f ",m[RC2INDEX(j,i,r,c)]);
      fprintf(f,"\n");
      for(j=0;j<l;j++)
	fprintf(f," ");

    }
  fprintf(f,"];\n");
}
