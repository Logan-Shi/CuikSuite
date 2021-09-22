#include "jacobian.h"

#include "error.h"
#include "basic_algebra.h"

#ifdef _OPENMP
  #include <omp.h>
#endif

/** 
    \file jacobian.c

    \brief Implementation of the TJacobian type and the associated functions.

    Implementation of the TJacobian type and the associated functions.

    \sa TJacobian, jacobian.h.
*/

void InitJacobian(Tvariables *vs,Tequations *eqs,TJacobian *j)
{
  unsigned int i;

  j->eqs=eqs;
  j->vars=vs;
  
  j->neqs=NEqualityEquations(eqs);
  j->nvars=NVariables(vs);

  if (j->nvars==0)
    Error("Empty problem in InitJacobian");
  
  if (j->neqs==0)
    j->J=NULL;
  else
    {
      NEW(j->J,j->nvars,Tequations);
      for(i=0;i<j->nvars;i++)
	{
	  DeriveEqualityEquations(i,&(j->J[i]),eqs);
	  CacheScalarEQUInfo(&(j->J[i]));
	}
    }
}

void InitPositionJacobian(Tvariables *vs,Tequations *eqs,TJacobian *j)
{
  unsigned int i,nv,k;

  j->eqs=eqs;
  j->vars=vs;
  
  j->neqs=NEqualityPositionEquations(eqs);
  j->nvars=GetNumPositionVariables(vs); // Keep only the position variables
  

  if (j->nvars==0)
    Error("Empty problem in InitPositionJacobian");

  if (j->neqs==0)
    j->J=NULL;
  else
    {
      nv=NVariables(vs);
      
      NEW(j->J,j->nvars,Tequations);
      k=0;
      for(i=0;i<nv;i++)
	{
	  if (IsPositionVariable(i,vs))
	    {
	      DeriveEqualityPositionEquations(i,&(j->J[k]),eqs);
	      CacheScalarEQUInfo(&(j->J[k]));
	      k++;
	    }
	}
      if (k!=j->nvars)
	Error("Wong number of position variables (InitPositionJacobian)");
    }
}

void InitScalarPositionJacobian(Tvariables *vs,Tequations *eqs,TJacobian *j)
{
  unsigned int i,nv,k;

  j->eqs=eqs;
  j->vars=vs;
  
  j->neqs=NEqualityScalarPositionEquations(eqs);
  j->nvars=GetNumPositionVariables(vs); // Keep only the position variables
  

  if (j->nvars==0)
    Error("Empty problem in InitScalarPositionJacobian");

  if (j->neqs==0)
    j->J=NULL;
  else
    {
      nv=NVariables(vs);
      
      NEW(j->J,j->nvars,Tequations);
      k=0;
      for(i=0;i<nv;i++)
	{
	  if (IsPositionVariable(i,vs))
	    {
	      DeriveEqualityScalarPositionEquations(i,&(j->J[k]),eqs);
	      CacheScalarEQUInfo(&(j->J[k]));
	      k++;
	    }
	}
      if (k!=j->nvars)
	Error("Wong number of position variables (InitScalarPositionJacobian)");
    }
}

void CopyJacobian(TJacobian *j_dst,TJacobian *j_src)
{
  unsigned int i;
  
  j_dst->eqs=j_src->eqs;
  j_dst->vars=j_src->vars;

  j_dst->neqs=j_src->neqs;
  j_dst->nvars=j_src->nvars;

  if (j_src->neqs==0)
    j_dst->J=NULL;
  else
    {
      NEW(j_dst->J,j_dst->nvars,Tequations);
      for(i=0;i<j_dst->nvars;i++)
	{
	  CopyEquations(&(j_dst->J[i]),&(j_src->J[i]));
	  CacheScalarEQUInfo(&(j_dst->J[i]));
	}
    }
}


void CopyNonDynamicsJacobian(TJacobian *j_dstP,
			     TJacobian *j_dstO,
			     TJacobian *j_src)
{
  unsigned int i,kp,ko;
  
  j_dstP->eqs=j_src->eqs;
  j_dstP->vars=j_src->vars;

  j_dstO->eqs=j_src->eqs;
  j_dstO->vars=j_src->vars;
  
  j_dstP->neqs=NNonDynamicEquations(j_src->eqs);
  j_dstP->nvars=GetNumPositionVariables(j_src->vars);
  
  j_dstO->neqs=NNonDynamicEquations(j_src->eqs);
  j_dstO->nvars=GetNumNonDynamicVariables(j_src->vars);

  if (j_src->neqs==0)
    {
      j_dstP->J=NULL;
      j_dstO->J=NULL;
    }
  else
    {
      NEW(j_dstP->J,j_dstP->nvars,Tequations);
      NEW(j_dstO->J,j_dstO->nvars,Tequations);
      kp=0;
      ko=0;
      for(i=0;i<j_src->nvars;i++)
	{
	  if (IsPositionVariable(i,j_src->vars))
	    {
	      CopyNonDynamicEquations(&(j_dstP->J[kp]),j_src->eqs,&(j_src->J[i]));
	      CacheScalarEQUInfo(&(j_dstP->J[kp]));
	      kp++;
	    }
	  else
	    {
	      if (!IsVelocityVariable(i,j_src->vars)) /* no position, no velocity -> non dynamics */
		{
		  CopyNonDynamicEquations(&(j_dstO->J[ko]),j_src->eqs,&(j_src->J[i]));
		  CacheScalarEQUInfo(&(j_dstO->J[ko]));
		  ko++;
		}
	    }
	}
    }
}

void CopyPositionJacobian(TJacobian *j_dst,
			  TJacobian *j_src)
{
  unsigned int i,k;
  
  j_dst->eqs=j_src->eqs;
  j_dst->vars=j_src->vars;

  j_dst->neqs=NPositionEquations(j_src->eqs);
  j_dst->nvars=GetNumPositionVariables(j_src->vars);

  if (j_src->neqs==0)
    j_dst->J=NULL;
  else
    {
      NEW(j_dst->J,j_dst->nvars,Tequations);
      k=0;
      for(i=0;i<j_src->nvars;i++)
	{
	  if (IsPositionVariable(i,j_src->vars))
	    {
	      CopyPositionEquations(&(j_dst->J[k]),j_src->eqs,&(j_src->J[i]));
	      CacheScalarEQUInfo(&(j_dst->J[k]));
	      k++;
	    }
	}
    }
}

void GetJacobianSize(unsigned int *nr,unsigned int *nc,TJacobian *j)
{
  *nr=j->neqs;
  *nc=j->nvars;
}

Tequations *GetJacobianColumn(unsigned int nv,TJacobian *j)
{
  if (nv>=j->nvars)
    Error("Index out of range in GetJacobianColumn");

  if (j->neqs==0)
    Error("Empty Jacobian");
  
  return(&(j->J[nv]));
}

Tequation *GetJacobianEquation(unsigned int r,unsigned int c,TJacobian *j)
{
  if (j->neqs==0)
    Error("Empty Jacobian");
    
  if ((r>=j->neqs)||(c>=j->nvars))
    Error("Index out of range in GetJacobianEquation");

  return(GetEquation(r,&(j->J[c])));
}

void RewriteJacobian2Orig(Tmapping *map,TJacobian *j)
{
  unsigned int i;

  if (j->neqs>0)
    {
      for(i=0;i<j->nvars;i++)
	RewriteEqs2Orig(map,&(j->J[i]));
    }
}

void JacobianLinearCombination(boolean *selectedVars,unsigned int *nv,
			       Tequations *eqs,TJacobian *j)
{
  if ((j->neqs>0)&&(j->nvars>0))
    {
      Tequations ceqs;
      unsigned int i,k;
      boolean init;

      init=FALSE;
      k=0;
      while ((!init)&&(k<j->nvars))
	{
	  if ((selectedVars==NULL)||(selectedVars[k]))
	    {
	      CopyEquations(&ceqs,&(j->J[k]));
	      VarScaleEqualityEquations(nv[k],TRUE,&ceqs);
	      init=TRUE;
	    }
	  k++;
	}
      if (!init)
	Error("Empty Jacobian linear combination");
      
      for(i=k;i<j->nvars;i++)
	{
	  if ((selectedVars==NULL)||(selectedVars[i]))
	    VarAccumulateEqualityEquations(nv[i],TRUE,&(j->J[i]),&ceqs);
	}

      MergeEquations(&ceqs,eqs);
      DeleteEquations(&ceqs);
    }	
}

void AllocateJacobianEvaluation(double ***m,TJacobian *j)
{
  if (j->neqs>0)
    {
      unsigned int i;
  
      NEW(*m,j->neqs,double *);
      for(i=0;i<j->neqs;i++)
	{
	  NEW((*m)[i],j->nvars,double);
	}
    }
}

void EvaluateJacobian(double *v,double **m,TJacobian *j)
{
  if (j->neqs>0)
    {
      unsigned int i,k;
      double *e;

      NEW(e,j->neqs,double);
      for(i=0;i<j->nvars;i++)
	{
	  EvaluateEqualityEquations(FALSE,v,e,&(j->J[i]));
	  for(k=0;k<j->neqs;k++)
	    m[k][i]=e[k];
	}
      free(e);
    }
}

void EvaluateJacobianInVector(double *v,unsigned int nr,unsigned int nc,double *m,TJacobian *j)
{
  if (j->neqs>0)
    {
      unsigned int i;
      double *e;

      NEW(e,j->neqs,double);
      for(i=0;i<j->nvars;i++)
	{
	  EvaluateEqualitySparseEquations(v,e,&(j->J[i]));
	  SubMatrixFromMatrix(j->neqs,1,e,0,i,nr,nc,m);
	}
      free(e);
    }
}

void EvaluateJacobianSubSetInVector(double *v,boolean *sr,unsigned int nr,unsigned int nc,double *m,TJacobian *j)
{
  if (j->neqs>0)
    {
      unsigned int i,l;
      double *e;
  
      l=0;
      for(i=0;i<j->neqs;i++)
	{
	  if (sr[i]) l++;
	}
      #ifdef _OPENMP
      if ((!omp_in_parallel())&&(j->nvars>14))
	{
	  #pragma omp parallel for private(i,e) schedule(dynamic) 
	  for(i=0;i<j->nvars;i++)
	    {
	      NEW(e,l,double);
	      EvaluateSubSetEqualitySparseEquations(v,sr,e,&(j->J[i]));
	      SubMatrixFromMatrix(l,1,e,0,i,nr,nc,m);
	      free(e);
	    }
	}
      else
	{
      #endif
	  NEW(e,l,double);
	  for(i=0;i<j->nvars;i++)
	    {
	      EvaluateSubSetEqualitySparseEquations(v,sr,e,&(j->J[i]));
	      SubMatrixFromMatrix(l,1,e,0,i,nr,nc,m);
	    }
	  free(e);
      #ifdef _OPENMP	  
	}
      #endif
    }
}

void EvaluateTransposedJacobianInVector(double *v,unsigned int nr,unsigned int nc,double *m,TJacobian *j)
{
  if (j->neqs>0)
    {
      unsigned int i;
      double *e;

      NEW(e,j->neqs,double);
      for(i=0;i<j->nvars;i++)
	{
	  EvaluateEqualitySparseEquations(v,e,&(j->J[i]));
	  SubMatrixFromMatrix(1,j->neqs,e,i,0,nr,nc,m);
	}
      free(e);
    }
}

void EvaluateTransposedJacobianSubSetInVector(double *v,boolean *sr,unsigned int nr,unsigned int nc,double *m,TJacobian *j)
{
  if (j->neqs>0)
    {
      unsigned int i,l;
      double *e;

      if (sr==NULL)
	l=j->neqs;
      else
	{
	  l=0;
	  for(i=0;i<j->neqs;i++)
	    {
	      if (sr[i]) l++;
	    }
	}
      if (j->nvars>14)
	{
	  #pragma omp parallel for private(i,e) schedule(dynamic)
	  for(i=0;i<j->nvars;i++)
	    {
	      NEW(e,l,double);
	      EvaluateSubSetEqualitySparseEquations(v,sr,e,&(j->J[i]));
	      SubMatrixFromMatrix(1,l,e,i,0,nr,nc,m);
	      free(e);
	    }
	}
      else
	{
	  NEW(e,l,double);
	  for(i=0;i<j->nvars;i++)
	    {
	      EvaluateSubSetEqualitySparseEquations(v,sr,e,&(j->J[i]));
	      SubMatrixFromMatrix(1,l,e,i,0,nr,nc,m);
	    }
	  free(e);
	}
    }
}

void PrintJacobianEvaluation(FILE *f,double **m,TJacobian *j)
{
  unsigned int i,k;

  if (j->neqs>0)
    {
      fprintf(f,"[");
      for(i=0;i<j->neqs;i++)
	{
	  for(k=0;k<j->nvars;k++)
	    {
	      fprintf(f,"%.16f ",m[i][k]);
	    }
	  fprintf(f,"\n");
	}
      fprintf(f,"];\n");
    }
}


void FreeJacobianEvaluation(double **m,TJacobian *j)
{
  if (j->neqs>0)
    {
      unsigned int i;

      for(i=0;i<j->neqs;i++)
	free(m[i]);
      free(m);
    }
}

void EvaluateJacobianXVectors(double *p,
			      unsigned int n,unsigned int ng,unsigned int *g,double *v,
			      unsigned int *nr,unsigned int *nc,double ***m,
			      TJacobian *j)
{
  if (j->neqs>0)
    {
      unsigned int i,k;
      double *e;

      /* Size of the output matrix */
      *nr=3*n;
      *nc=j->nvars;

      /* Allocate the output matrix. */
      NEW(*m,3*n,double*);
      for(i=0;i<*nr;i++)
	{ NEW((*m)[i],*nc,double); }

      /* Space for the evaluation of each column */
      NEW(e,*nr,double);

      /* Evaluate column-wise */
      for(i=0;i<j->nvars;i++)
	{
	  EvaluateEquationsXVectors(p,ng,g,v,e,&(j->J[i]));
	  for(k=0;k<(*nr);k++)
	    (*m)[k][i]=e[k];
	}

      /* Release space */
      free(e);
    }
}

void PrintJacobian(FILE *f,char **varNames,TJacobian *j)
{
  unsigned int i;

  if (j->neqs>0)
    {
      for(i=0;i<j->nvars;i++)
	{
	  fprintf(f,"Jacobian column %u\n",i);
	  PrintEquations(f,varNames,&(j->J[i]));
	}
    }
}

void DeleteJacobian(TJacobian *j)
{
  unsigned int i;

  if (j->neqs>0)
    {
      for(i=0;i<j->nvars;i++)
	DeleteEquations(&(j->J[i]));
      free(j->J);
    }
}
