#include "nhessian.h"
#include "mequation.h"
#include "basic_algebra.h"
#include "error.h"

#include <string.h>
#ifdef _OPENMP
  #include <omp.h>
#endif

/** \file nhessian.c
    \brief Implementation of the functions operating on TNHessian.

    Implementation of the functions operating on TNHessian.

    \sa nhessian.h, TNHessian.
*/

boolean InitNHessian(Tvariables *vs,Tequations *eqs,TJacobian *sJ,TNHessian *nh)
{
  unsigned int i,nvv,nve,ndv,nde,nse;
  boolean ok=TRUE;

  nh->h=NULL;
  nh->me=NULL;
  
  nvv=GetNumVelocityVariables(vs);
  nve=NVelocityEquations(eqs);
  ndv=GetNumNonDynamicVariables(vs);
  nde=NNonDynamicEquations(eqs);
  
  /* We need velocity variables, velocity equations -> we have a system with dynamics
     Moreover, all equations must be matrix equations. */
  if ((nvv>0)&&(nve>0))
    {
      nh->nvars=NVariables(vs)-nvv-ndv;

      /* half of the non-discriminant equations are position equations */
      nse=NScalarEquations(eqs);
      nh->nsEq=(nse-ndv)/2; /* all discriminant equations, if any, are scalar */
      nh->nmEq=NMatrixEquations(eqs)/2; /* half of the matrix equations are position equations */

      if (nh->nsEq>0)
	InitHessian(sJ,&(nh->sH));
      
      /* Get the position equations (they are the first one in the set) */
      /* Note that we get direct pointers to the matrix equations */
      NEW(nh->me,nh->nmEq,TMequation*);
      for(i=0;((ok)&&(i<nh->nmEq));i++)
	{
	  if (!IsPositionEquation(nse+i,eqs))
	    Error("Wrong equation type in InitNHessian");
	  
	  nh->me[i]=GetMatrixEquation(i,eqs);

	  ok=((MEquationNTerms(nh->me[i])==1)&&
	      (MEquationMaxVars(nh->me[i])<2)&&
	      (!MEquationHasRepeatedVar(nh->me[i])));
	}
      if (!ok)
	{
	  free(nh->me);
	  nh->me=NULL;
	}
      else
	{
	  /* This includes both scalar and matrix equations */
	  nh->nEq=(NEqualityEquations(eqs)-nde)/2;
	  
	  /* The system has the right form. Allocate space for evaluation. */
	  
	  NEW(nh->h,nh->nvars,double*);
	  for(i=0;i<nh->nvars;i++)
	    {
	      NEW(nh->h[i],nh->nEq*nh->nvars,double);
	    }
	}
    }
  else
    ok=FALSE;

  return(ok);
}

void EvaluateNHessianVector2(double *x,double *v,
			     unsigned int nie,boolean *independentEq,
			     double *m,double *o,TNHessian *nh)
{
  unsigned int i,j,k,ki,l;
  boolean any;
  double *r;
	  
  for(i=0;i<nh->nvars;i++)
    memset(nh->h[i],0,sizeof(double)*(nh->nEq*nh->nvars));

  /* Fill in the different matrices, one per variable */
  if (nh->nsEq>0)
    ki=EvaluateScalarHessian(x,independentEq,nie,nh->h,&(nh->sH));
  else
    ki=0;
  
  k=nh->nsEq;
  for(i=0;i<nh->nmEq;i++)
    {
      l=NumberScalarEquations(nh->me[i]);
      any=(independentEq==NULL);
      for(j=0;((!any)&&(j<l));j++)
	any=independentEq[k+j];

      if (any)
	{
	  /* Numerical double derivative of the matrix equation */
	  ki+=NumericDDMatrixEquation(nie,nh->nvars,k,ki,independentEq,x,nh->h,nh->me[i]);
	}
      k+=l;
    }

  /* Product of the matrices and the vectors to produce a matrix (one column at a time) */
  #pragma omp parallel for private(i,r) schedule(dynamic) if ((!omp_in_parallel())&&(nh->nvars>14))
  for(i=0;i<nh->nvars;i++)
    {
      NEW(r,nie,double);
      MatrixVectorProduct(nie,nh->nvars,nh->h[i],v,r);
      SetColumn(r,i,nie,nh->nvars,m);
      free(r);
    }
  /* Final matrix vector product */
  MatrixVectorProduct(nie,nh->nvars,m,v,o);
}

void DeleteNHessian(TNHessian *nh)
{
  if (nh->h!=NULL)
    {
      unsigned int i;

      for(i=0;i<nh->nvars;i++)
	free(nh->h[i]);
      free(nh->h);
      free(nh->me);
      if (nh->nsEq>0)
	DeleteHessian(&(nh->sH));
    }
}
