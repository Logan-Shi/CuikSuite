#include "simplex.h"
#include "error.h"
#include "geom.h"
#include "defines.h"

#include <float.h>
#include <math.h>
#include <string.h>

/** 
   \file simplex_gurobi.c

   \brief Implementation of the functions operating on TSimplex using
          the <A HREF="http://www.gurobi.com">Gurobi</A> backend. 

   Implementation of the functions operating on TSimplex using
   the <A HREF="http://www.gurobi.com">Gurobi</A> backend.

   \sa TSimplex, simplex.h, simplex_glpk.c, simplex_lpsolve.c, simplex_clp.c.
*/

void SimplexCreate(double epsilon,unsigned int ncols,TSimplex *s)
{
  NEW(s->lp,1,Tgurobi);
  
  s->lp->env=NULL;
  s->lp->model=NULL;
  s->lp->ncols=ncols;
  s->lp->nAdded=0;
  s->lp->nrows=0;

  InitVector(sizeof(unsigned int),CopyID,NULL,100,&(s->lp->rangeVar));
  
  if (GRBloadenv(&s->lp->env,NULL))
    Error("Error creating the Gurobi environment");
  
  /* Environment parameters must be set before creating the model !! */
  if (epsilon<1e-9)
    epsilon=1e-9; /* This is the smallest possible value in Gurobi */
  if (GRBsetdblparam(s->lp->env,GRB_DBL_PAR_FEASIBILITYTOL,epsilon))
    Error("Error setting the tolernace");
  
  #if (_DEBUG<5)
    if (GRBsetintparam(s->lp->env,GRB_INT_PAR_OUTPUTFLAG,0)) /* disable output */
      Error("Error dissabling Gurobi output");
  #endif
    
  if (GRBsetintparam(s->lp->env,GRB_INT_PAR_METHOD,GRB_METHOD_DUAL)) /* dual simplex */
    Error("Error selecting the simplex method");

  if (GRBsetdblparam(s->lp->env,GRB_DBL_PAR_TIMELIMIT,ncols*SIMPLEX_TIMEOUT)) /* timeout */
    Error("Error setting the timeout");

  /* Cancel scaling? Might improve accuracy but increase execution time */
      
  /* Create the model */
  if (GRBnewmodel(s->lp->env,&s->lp->model,"lp",ncols,NULL,NULL,NULL,NULL,NULL))
    Error("Error creating the Gurobi model");
  
  if (GRBsetintattr(s->lp->model,GRB_INT_ATTR_MODELSENSE,1)) /*minimize*/
    Error("Error setting the optimization direction");
}

/* LP: Reset the LP internal information */
void ResetSimplex(TSimplex *s)
{
}

inline unsigned int SimplexNColumns(TSimplex *s)
{
  return(s->lp->ncols);
}

inline unsigned int SimplexNRows(TSimplex *s)
{
  return(s->lp->nrows);
}

/* LP: set bounds for a given column */
void SimplexSetColBounds(unsigned int ncol,double epsilon,Tinterval *i,TSimplex *s)
{
  double l,u,w;
  
  if (ncol>s->lp->ncols)
    Error("Variable index out of range in SimplexSetColBounds");

  l=LowerLimit(i);
  u=UpperLimit(i);
  w=u-l;
  if (w<epsilon)
    {
      w=(epsilon-w)/2.0;
      l-=w;
      u+=w;
    }
  
  if (GRBsetdblattrelement(s->lp->model,GRB_DBL_ATTR_LB,ncol,l))
    Error("Error calling GRBsetdblattrelement (SimplexSetColBounds 1)");
  
  if (GRBsetdblattrelement(s->lp->model,GRB_DBL_ATTR_UB,ncol,u))
    Error("Error calling GRBsetdblattrelement (SimplexSetColBounds 2)");
}

/* LP: get bounds for a given column */
void SimplexGetColBounds(unsigned int ncol,Tinterval *i,TSimplex *s)
{
  double l,u;
  
  if (ncol>s->lp->ncols)
    Error("Variable index out of range in SimplexGetColBounds");
  
  if (GRBgetdblattrelement(s->lp->model,GRB_DBL_ATTR_LB,ncol,&l))
    Error("Error calling GRBgetdblattrelement (SimplexGetColBounds 1)");
  
  if (GRBgetdblattrelement(s->lp->model,GRB_DBL_ATTR_UB,ncol,&u))
    Error("Error calling GRBgetdblattrelement (SimplexGetColBounds 2)");

  NewInterval(l,u,i);
}

void SimplexGetColConstraint(unsigned int ncol,TLinearConstraint *lc,TSimplex *s)
{
  unsigned int i,k;
  double v;
  Tinterval error;

  if (ncol>s->lp->ncols)
    Error("Variable index out of range in SimplexGetColConstraint");
  
  k=SimplexNRows(s);
  
  InitLinearConstraint(lc);
  for(i=0;i<k;i++)
    {
      if (GRBgetcoeff(s->lp->model,i,ncol,&v))
	Error("Error calling GRBgetcoeff (SimplexGetColConstraint)");
      if (fabs(v)>ZERO)
	AddTerm2LinearConstraint(i,v,lc);
    }
 
  SimplexGetColBounds(ncol,&error,s);
  SetLinearConstraintError(&error,lc);
}

boolean SimplexColEmpty(unsigned int ncol,TSimplex *s)
{
  unsigned int i,k;
  double v;
  boolean empty;
  
  k=SimplexNRows(s); 

  empty=TRUE;
  for(i=0;((i<k)&&(empty));i++)
    {
      if (GRBgetcoeff(s->lp->model,i,ncol,&v))
	Error("Error calling GRBgetcoeff (SimplexColEmpty)");
      if (fabs(v)>ZERO)
	empty=FALSE;
    }
  return(empty);
}

void SimplexGetRowsLowerBounds(double *lower,TSimplex *s)
{
  char *sense;
  double *rhs;
  unsigned int i;
  unsigned int *nv;
  double u;
  
  NEW(sense,s->lp->nrows,char);
  NEW(rhs,s->lp->nrows,double);
  
  if (GRBgetcharattrarray(s->lp->model,GRB_CHAR_ATTR_SENSE,0,s->lp->nrows,sense))
    Error("Error calling GRBgetcharattrarray (SimplexGetRowsLowerBounds 1)");

  if (GRBgetdblattrarray(s->lp->model,GRB_DBL_ATTR_RHS,0,s->lp->nrows,rhs))
    Error("Error calling GRBgetdblattrarray (SimplexGetRowsLowerBounds 2)");
      
  for(i=0;i<s->lp->nrows;i++)
    {
      switch(sense[i])
	{
	case GRB_EQUAL:
	  nv=(unsigned int *)GetVectorElement(i,&(s->lp->rangeVar));
	  if (*nv!=NO_UINT)
	    {
	      if (GRBgetdblattrelement(s->lp->model,GRB_DBL_ATTR_UB,*nv,&u))
		Error("Error calling GRBgetdblattrelement (SimplexGetRowBounds 2)");

	      lower[i]=rhs[i]-u;
	    }
	  else
	    lower[i]=rhs[i];
	  break;
	case GRB_GREATER_EQUAL:
	  lower[i]=rhs[i];
	  break;
	case GRB_LESS_EQUAL:
	  lower[i]=-INF;
	  break;
	default:
	  Error("Unknown sense (SimplexGetRowsLowerBounds)"); 
	}
    }
  
  free(sense);
  free(rhs);
}

void SimplexGetRowsUpperBounds(double *upper,TSimplex *s)
{
  char *sense;
  double *rhs;
  unsigned int i;
  unsigned int *nv;
  double l;
  
  NEW(sense,s->lp->nrows,char);
  NEW(rhs,s->lp->nrows,double);
  
  if (GRBgetcharattrarray(s->lp->model,GRB_CHAR_ATTR_SENSE,0,s->lp->nrows,sense))
    Error("Error calling GRBgetcharattrarray (SimplexGetRowsLowerBounds 1)");

  if (GRBgetdblattrarray(s->lp->model,GRB_DBL_ATTR_RHS,0,s->lp->nrows,rhs))
    Error("Error calling GRBgetdblattrarray (SimplexGetRowsLowerBounds 2)");
      
  for(i=0;i<s->lp->nrows;i++)
    {
      switch(sense[i])
	{
	case GRB_EQUAL:
	  nv=(unsigned int *)GetVectorElement(i,&(s->lp->rangeVar));
	  if (*nv!=NO_UINT)
	    {
	      if (GRBgetdblattrelement(s->lp->model,GRB_DBL_ATTR_LB,*nv,&l))
		Error("Error calling GRBgetdblattrelement (SimplexGetRowBounds 2)");

	      upper[i]=rhs[i]-l;
	    }
	  else
	    upper[i]=rhs[i];
	  break;
	case GRB_GREATER_EQUAL:
	  upper[i]=INF;
	  break;
	case GRB_LESS_EQUAL:
	  upper[i]=rhs[i];
	  break;
	default:
	  Error("Unknown sense (SimplexGetRowsUpperBounds)"); 
	}
    }
  
  free(sense);
  free(rhs);
}

double SimplexGetRowDual(unsigned int nrow,TSimplex *s)
{
  double v;

  if (GRBgetdblattrelement(s->lp->model,GRB_DBL_ATTR_PI,nrow,&v))
    Error("Error calling GRBgetdblattrelement (SimplexGetRowDual)");
  
  return(v);
}

void SimplexGetDuals(double *duals,TSimplex *s)
{
  if (GRBgetdblattrarray(s->lp->model,GRB_DBL_ATTR_PI,0,s->lp->nrows,duals))
    Error("Error calling GRBgetdblattrarray (SimplexGetDuals)");
}

void SimplexAddNewConstraintRaw(TLinearConstraint *lc,TSimplex *s)
{
  int nt,nv;
  Tinterval error;
  int *vars;
  double *coef;

  nt=(int)GetNumTermsInLinearConstraint(lc);
  vars=(int *)GetLinearConstraintVariables(lc);
  coef=GetLinearConstraintCoefficients(lc);
  GetLinearConstraintError(&error,lc);
  
  nv=NO_UINT; /* default: no variable added */
  if (IntervalSize(&error)<ZERO)
    { 
      if (GRBaddconstr(s->lp->model,nt,vars,coef,GRB_EQUAL,IntervalCenter(&error),NULL))
	Error("Error calling GRBaddconstr (SimplexAddNewConstraintRaw EQU)"); 
      s->lp->nrows++;
    }
  else
    {
      double l,u;
      
      l=LowerLimit(&error);
      u=UpperLimit(&error);
      
      if ((l>-INF)&&(u<INF))
	{
	  if (GRBaddrangeconstr(s->lp->model,nt,vars,coef,l,u,NULL))
	    Error("Error calling GRBaddrangeconstr (SimplexAddNewConstraintRaw)");

	  nv=s->lp->ncols+s->lp->nAdded;
	  s->lp->nAdded++;
	  s->lp->nrows++;
	}
      else
	{
	  if (l>-INF)
	    {
	      if (GRBaddconstr(s->lp->model,nt,vars,coef,GRB_GREATER_EQUAL,l,NULL))
		Error("Error calling GRBaddconstr (SimplexAddNewConstraintRaw GEQ)");
	      s->lp->nrows++;
	    }
	  else
	    {
	      if (u<INF)
		{
		  if (GRBaddconstr(s->lp->model,nt,vars,coef,GRB_LESS_EQUAL,u,NULL))
		    Error("Error calling GRBaddconstr (SimplexAddNewConstraintRaw LEQ)");
		  s->lp->nrows++;
		}
	    }
	}
    }

  NewVectorElement(&nv,&(s->lp->rangeVar));

}

void SimplexAddCircle(unsigned int x,unsigned int y,double r2,TSimplex *s)
{
  double coef[2]={1.0,1.0};
  int ndx[2]={(int)x,(int)y};
  
  if (GRBaddqconstr(s->lp->model,0,NULL,NULL,2,ndx,ndx,coef,GRB_LESS_EQUAL,r2,NULL))
    Error("Error calling GRBaddrangeconstr (SimplexAddNewConstraintRaw)");
}

void UpdateSimplex(TSimplex *s)
{
  /* Integrate all the recently added information into the model */
  if (GRBupdatemodel(s->lp->model))
    Error("Inconsistend model (UpdateSimplex)");
}

void SimplexSetOptimizationFunction(TLinearConstraint *obj,TSimplex *s)
{
  int i,nt;
  int *vars;
  double *coef;
  Tinterval error;

  nt=(int)SimplexNColumns(s);  
  for (i=0;i<nt;i++)
    {
      if (GRBsetdblattrelement(s->lp->model,GRB_DBL_ATTR_OBJ,i,0.0))
	Error("Error calling GRBsetdblattrelement (SimplexSetOptimizationFunction 1)");
    }
  
  nt=(int)GetNumTermsInLinearConstraint(obj);
  vars=(int *)GetLinearConstraintVariables(obj);
  coef=GetLinearConstraintCoefficients(obj);
  GetLinearConstraintError(&error,obj);
   
  if (GRBsetdblattr(s->lp->model,GRB_DBL_ATTR_OBJCON,IntervalCenter(&error)))
    Error("Error calling GRBsetdblattr (SimplexSetOptimizationFunction)");
  for (i=0;i<nt;i++)
    {
      if (GRBsetdblattrelement(s->lp->model,GRB_DBL_ATTR_OBJ,vars[i],coef[i]))
	Error("Error calling GRBsetdblattrelement (SimplexSetOptimizationFunction 2)");
    }
}

void SimplexGetOptimizationCoefficients(double *coef,TSimplex *s)
{
  if (GRBgetdblattrarray(s->lp->model,GRB_DBL_ATTR_OBJ,0,s->lp->ncols,coef))
    Error("Error calling GRBgetdblattrarray (SimplexGetOptimizationCoefficients)");
}

double SimplexGetOptimalValueRaw(TSimplex *s)
{
  double v;
  
  if (GRBgetdblattr(s->lp->model,GRB_DBL_ATTR_OBJVAL,&v))
    Error("Error calling GRBgetdblattr (SimplexGetOptimalValueRaw)");

  return(v);
}

unsigned int SimplexSolve(TSimplex *s)
{
  unsigned int e;
  int status;
  
  if (GRBoptimize(s->lp->model))
    e=ERROR_IN_PROCESS;
  else
    {
      if (GRBgetintattr(s->lp->model,GRB_INT_ATTR_STATUS,&status))
	Error("Error calling GRBgetdblattr (SimplexSolve)");
	
      switch(status)
	{
	case GRB_OPTIMAL:
	  e=REDUCED_BOX;
	  break;
	case GRB_INFEASIBLE:
	  e=EMPTY_BOX;
	  break;
	case GRB_INF_OR_UNBD:
	case GRB_UNBOUNDED:
	  e=UNBOUNDED_BOX;
	  break;
	default:  
	  e=ERROR_IN_PROCESS;
	  break;  
	}
    }
  return(e);
}

void SimplexDelete(TSimplex *s)
{
  if (GRBfreemodel(s->lp->model))
    Error("Error calling GRBfreemodel (SimplexDelete)");
  GRBfreeenv(s->lp->env);
  free(s->lp);
}


