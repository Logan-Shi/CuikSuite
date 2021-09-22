#include "hessian.h"

#include "error.h"
#include "basic_algebra.h"

#ifdef _OPENMP
  #include <omp.h>
#endif

/** 
    \file hessian.c

    \brief Implementation of the THessian type and the associated functions.

    Implementation of the THessian type and the associated functions.

    \sa THessian, hessian.h.
*/


void InitHessian(TJacobian *j,THessian *h)
{
  unsigned int i,k;
  Tequations *d;

  GetJacobianSize(&(h->neqs),&(h->nvars),j);

  NEW(h->H,h->nvars,Tequations*);
  for(i=0;i<h->nvars;i++)
    {
      NEW(h->H[i],h->nvars,Tequations);
      d=GetJacobianColumn(i,j);
      for(k=0;k<h->nvars;k++)
	{
	  DeriveEqualityEquations(k,&(h->H[i][k]),d);
	  CacheScalarEQUInfo(&(h->H[i][k]));
	}
    }
}

unsigned int GetHessianNVars(THessian *h)
{
  return(h->nvars);
}

unsigned int GetHessianNEqs(THessian *h)
{
  return(h->neqs);
}


void AllocateHessianEvaluation(double ****m,THessian *h)
{
  unsigned int i,k;
  
  NEW(*m,h->neqs,double **);
  for(i=0;i<h->neqs;i++)
    {
      NEW((*m)[i],h->nvars,double *);
      for(k=0;k<h->nvars;k++)
	NEW((*m)[i][k],h->nvars,double);
    }
}

void AllocateHessianEvaluationAsVectors(unsigned int nie,double ***m,THessian *h)
{
  unsigned int i,ne;

  if ((nie!=NO_UINT)&&(nie>h->neqs))
    Error("More independent equations than equations");
  
  ne=(nie==NO_UINT?h->neqs:nie);
  
  NEW(*m,h->nvars,double *);
  for(i=0;i<h->nvars;i++)
    NEW((*m)[i],ne*h->nvars,double);
}

void EvaluateHessian(double *v,double ***m,THessian *h)
{
  unsigned int i,k,l;
  double *r;

  NEW(r,h->neqs,double);
  for(i=0;i<h->nvars;i++)
    {
      for(k=0;k<h->nvars;k++)
	{
	  EvaluateEqualityEquations(FALSE,v,r,&(h->H[i][k]));
	  for(l=0;l<h->neqs;l++)
	    m[l][i][k]=r[l];
	}
    }
  free(r);
}

unsigned int EvaluateScalarHessian(double *v,
				   boolean *independentEq,
				   unsigned int neq,double **m,THessian *h)
{
  unsigned int i,k,l,ni;
  double *r;

  if (independentEq==NULL)
    ni=h->neqs; /* This is the number of scalar eqs. */
  else
    {
      ni=0;
      for(l=0;l<h->neqs;l++)
	{
	  if (independentEq[l])
	    ni++;  
	}
    }

  NEW(r,ni,double);
  for(i=0;i<h->nvars;i++)
    {
      for(k=0;k<h->nvars;k++)
	{
	  EvaluateSubSetEqualitySparseEquations(v,independentEq,r,&(h->H[i][k]));
	  for(l=0;l<ni;l++)
	    m[i][RC2INDEX(l,k,neq,h->nvars)]=r[l];
	}
    }
  free(r);
  
  return(ni);
}

void EvaluateHessianVector(double *x,double*v,
			   unsigned int nie,boolean *independentEq,
			   double **m,double *mf,THessian *h)
{
  unsigned int i,k,ne;
  double *r;
  double **m1;
  double *mf1;
  boolean all;
  
  all=((nie==NO_UINT)||(independentEq==NULL)||(nie==h->neqs));
  ne=(all?h->neqs:nie);

  if (m==NULL)
    AllocateHessianEvaluationAsVectors(ne,&m1,h);
  else
    m1=m;

  if (mf==NULL)
    { NEW(mf,ne*h->nvars,double); }
  else
    mf1=mf;
  
  #pragma omp parallel for private(i,k,r) schedule(dynamic) if ((!omp_in_parallel())&&(h->nvars>14))
  for(i=0;i<h->nvars;i++)
    {
      NEW(r,ne,double);
      for(k=0;k<h->nvars;k++)
	{
	  if (all)
	    EvaluateEqualitySparseEquations(x,r,&(h->H[i][k]));
	  else
	    EvaluateSubSetEqualitySparseEquations(x,independentEq,r,&(h->H[i][k]));
	  SetColumn(r,k,ne,h->nvars,m1[i]);
	}

      MatrixVectorProduct(ne,h->nvars,m1[i],v,r);
      SetColumn(r,i,ne,h->nvars,mf1);
      free(r);
    }
  
  if (m==NULL)
    FreeHessianEvaluationAsVectors(m1,h);
  if (mf==NULL)
    free(mf1);
}

void EvaluateHessianVector2(double *x,double*v,
			    unsigned int nie,boolean *independentEq,
			    double **m,double *mf,double *o,THessian *h)
{
  double **m1;
  double *mf1;
  boolean all;
  unsigned int ne;
  
  all=((nie==NO_UINT)||(independentEq==NULL)||(nie==h->neqs));
  ne=(all?h->neqs:nie);

  if (m==NULL)
    AllocateHessianEvaluationAsVectors(ne,&m1,h);
  else
    m1=m;

  if (mf==NULL)
    { NEW(mf1,ne*h->nvars,double); }
  else
    mf1=mf;

  EvaluateHessianVector(x,v,ne,independentEq,m1,mf1,h);
  MatrixVectorProduct(ne,h->nvars,mf1,v,o);
  
  if (m==NULL)
    FreeHessianEvaluationAsVectors(m1,h);
  if (mf==NULL)
    free(mf1);
}

void FreeHessianEvaluation(double ***m,THessian *h)
{
  unsigned int i,k;
  
  for(i=0;i<h->neqs;i++)
    {
      for(k=0;k<h->nvars;k++)
	free(m[i][k]);
      free(m[i]);
    } 
  free(m);
}

void FreeHessianEvaluationAsVectors(double **m,THessian *h)
{
  unsigned int i;

  for(i=0;i<h->nvars;i++)
    free(m[i]);
  free(m);
}
  
void DeleteHessian(THessian *h)
{
  unsigned int i,k;

  for(i=0;i<h->nvars;i++)
    {
      for(k=0;k<h->nvars;k++)
	DeleteEquations(&(h->H[i][k]));
      free(h->H[i]);
    }
  free(h->H);
}
