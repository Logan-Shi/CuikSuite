#include "njacobian.h"
#include "mequation.h"
#include "basic_algebra.h"
#include "error.h"

#include <string.h>
#ifdef _OPENMP
  #include <omp.h>
#endif
/** \file njacobian.c
    \brief Implementation of the functions operating on TNJacobian.

    Implementation of the functions operating on TNJacobian.

    \sa njacobian.h, TNJacobian.
*/

boolean InitNJacobian(Tvariables *vs,Tequations *eqs,TNJacobian *nj)
{
  unsigned int i,nvv,nve,nde,nse;
  boolean ok=TRUE;

  nj->m=NULL;
  nj->v=NULL;
  nj->f=NULL;
  nj->me=NULL;
  
  nvv=GetNumVelocityVariables(vs);
  nve=NVelocityEquations(eqs);
  
  /* We need velocity variables, velocity equations -> we have a system with dynamics */
  if ((nvv>0)&&(nve>0))
    {
      /* Only use the position variables. */
      nj->nvars=GetNumPositionVariables(vs);

      /* Direct pointer to the base equations (with all the equations, not only position) */
      nj->eqs=eqs;
      
      /* half of the scalar equations (if any and not including non-dynamic equations) are position eqs */
      nse=NScalarEquations(eqs);
      nde=NNonDynamicEquations(eqs);
      nj->nsEq=(nse-nde)/2;
      
      /* The first half matrix equations are position equations
         If this is null, it makes few sense to use the numerical
         Jacobian instead of the symbolic one. */
      nj->nmEq=NMatrixEquations(eqs)/2;
      
      if (nj->nsEq>0)
	InitScalarPositionJacobian(vs,eqs,&(nj->sJ));
                 
      /* Get the position equations (they are the first half of the set) */
      /* Note that we get direct pointers to the matrix equations */
      NEW(nj->me,nj->nmEq,TMequation*);
      for(i=0;((ok)&&(i<nj->nmEq));i++)
	{
	  /* The second half of the matrix equations are supposed to be velocity equations. Check it. */
	  if (!IsPositionEquation(nse+i,eqs))
	    Error("Wrong equation type in InitNJacobian");
	  
	  nj->me[i]=GetMatrixEquation(i,eqs);

	  ok=((MEquationNTerms(nj->me[i])==1)&&
	      (MEquationMaxVars(nj->me[i])<2)&&
	      (!MEquationHasRepeatedVar(nj->me[i])));
	}
      if (!ok)
	{
	  if (nj->nsEq>0)
	    DeleteJacobian(&(nj->sJ));
	  free(nj->me);
	  nj->me=NULL;
	  nj->nEq=0; /* empty jacobian */
	}
      else
	{
	  /* This includes both scalar/matrix position equations */
	  nj->nEq=(NEqualityEquations(eqs)-nde)/2; /* may be zero! */
	  
	  /* The system has the right form. Allocate space for evaluation. */
	  
	  NEW(nj->m,nj->nEq*nj->nvars,double);
	  
	  /* Space for the velocity vector */
	  NEW(nj->v,nj->nvars,double);
	  
	  /* 'f' includes the evaluation of both the postion and
	     the velocity equations. Actually only the independent
	     ones, but we allocate space for the evaluation of all
	     the equations. */
	  NEW(nj->f,nj->nEq*2,double);
	}
    }
  else
    ok=FALSE;

  return(ok);
}

TJacobian *GetScalarJacobian(TNJacobian *nj)
{
  #if (_DEBUG>0)
    if (nj->me==NULL)
      Error("Empty numerical Jacobian");
  #endif
    
  if (nj->nsEq>0)
    return(&(nj->sJ));
  else
    return(NULL);
}

void EvaluateSystemFromNJacobian(double *x,unsigned int *ndxV,unsigned int ne,unsigned int nie,
				 boolean *iE,boolean *ipE,boolean *pvEq,boolean *pEq,
				 double *o,double *f,TNJacobian *nj)
{
  #if (_DEBUG>0)
    if (nj->me==NULL)
      Error("Empty numerical Jacobian");
  #endif
  
  if (nj->nEq>0)
    {
      unsigned int k,ki,i,j,l;
      unsigned int kp,kv,ko;
      boolean any;
      double mv[MAX_EQ_MATRIX];

      /* We evaluate the position equations first and then the velocity equations.
	 They are all stored in nj->f
	 Only the independent equations are evaluated.
	 At the end, we re-order the computed values so that we have first the
	 scalar position and velocity equations and then the matrix and velocity
	 equations.
      */
  
      /* Evaluate position equations */
      if (nj->nsEq>0)
	ki=EvaluatePositionScalarEqs(x,ipE,nj->f,nj->eqs);
      else
	ki=0;

      k=nj->nsEq;
      for(i=0;i<nj->nmEq;i++)
	{
	  l=NumberScalarEquations(nj->me[i]);
      
	  any=(ipE==NULL);
	  for(j=0;((!any)&&(j<l));j++)
	    any=ipE[k+j];

	  if (any)
	    {
	      /*
	      fprintf(stderr,"Equation: %u\n",i);
	      PrintMEquation(stderr,x,NULL,nj->me[i]);
	      */
	      
	      EvaluateMEquation(x,mv,nj->me[i]);
	      for(j=0;j<l;j++)
		{
		  if ((ipE==NULL)||(ipE[k+j]))
		    {
		      nj->f[ki]=mv[j];
		      ki++;
		    }
		}
	    }
	  k+=l;
	}
  
      /* Evaluate velocity equations */
      EvaluateTransposedNJacobianSubSetInVector(x,nie,ipE,nj->m,nj);

      /* Get the velocity */
      for(i=0;i<nj->nvars;i++)
	nj->v[i]=x[ndxV[i]];
      
      TMatrixVectorProduct(nj->nvars,nie,nj->m,nj->v,&(nj->f[nie]));
      
      /* Re order */  
      kp=0;
      kv=nie;
      ko=0;
      k=0;
      for(i=0;i<ne;i++)
	{
	  if ((iE==NULL)||(iE[i]))
	    {
	      if (pvEq[i])
		{
		  if (pEq[i])
		    {
		      f[k]=nj->f[kp];
		      kp++;
		    }
		  else
		    {
		      f[k]=nj->f[kv];
		      kv++;
		    }
		}
	      else
		{
		  f[k]=o[ko];
		  ko++;
		}
	      k++;
	    }
	}
    }
}

void EvaluateTransposedNJacobianSubSetInVector(double *x,unsigned int nie,boolean *independentEq,
					       double *m,TNJacobian *nj)
{
  #if (_DEBUG>0)
    if (nj->me==NULL)
      Error("Empty numerical Jacobian");
  #endif
    
  if (nj->nEq>0)
    {
      unsigned int i,j,k,ki,l;
      boolean any;
	  
      memset(m,0,sizeof(double)*(nj->nvars*nie));
  
      if (nj->nsEq>0)
	{
	  EvaluateTransposedJacobianSubSetInVector(x,independentEq,nj->nvars,nie,m,&(nj->sJ));
	  if (independentEq==NULL)
	    ki=nj->nsEq;
	  else
	    {
	      ki=0;
	      for(i=0;i<nj->nsEq;i++)
		if (independentEq[i])
		  ki++;
	    }
	}
      else
	ki=0;
  
      k=nj->nsEq;
      for(i=0;i<nj->nmEq;i++)
	{
	  l=NumberScalarEquations(nj->me[i]);
	  any=(independentEq==NULL);
	  for(j=0;((!any)&&(j<l));j++)
	    any=independentEq[k+j];

	  if (any)
	    {
	      /* Numerical derivative of the matrix equation */
	      ki+=TNumericDMatrixEquation(nie,nj->nvars,k,ki,independentEq,x,m,nj->me[i]);
	    }
      
	  k+=l;
	}
    }
}

void DeleteNJacobian(TNJacobian *nj)
{
  if (nj->me!=NULL)
    {
      free(nj->m);
      free(nj->v);
      free(nj->f);
      free(nj->me);
      if (nj->nsEq>0)
	DeleteJacobian(&(nj->sJ));
    }
}
