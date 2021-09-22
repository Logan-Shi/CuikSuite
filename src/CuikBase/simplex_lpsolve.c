#include "simplex.h"
#include "error.h"
#include "geom.h"
#include "defines.h"

#include <math.h>
#include <string.h>

/** 
   \file simplex_lpsolve.c

   \brief Implementation of the functions operating on TSimplex using
          the <A HREF="http://sourceforge.net/projects/lpsolve">Lp_solve</A>  
	  backend.
 
   Implementation of the functions operating on TSimplex using
   the <A HREF="http://sourceforge.net/projects/lpsolve">Lp_solve</A>  
   backend. 

   \sa TSimplex, simplex.h, simplex_clp.c, simplex_glpk.c, simplex_gurobi.c.
*/

void SimplexCreate(double epsilon,unsigned int ncols,TSimplex *s)
{
  double ct;

  /* LP: Create an empty LP problem */
  s->lp=make_lp(0,ncols);
  if (s->lp==NULL)
    Error("Error creating the simplex (simplex_lpsolve)");

  /* LP: Adjust the verbosity of the LP problem */
  #if (_DEBUG<5)
    set_verbose(s->lp,NEUTRAL);
  #endif

  s->inf=get_infinite(s->lp);

  /* LP: Adjust LP internal parameters */
  set_presolve(s->lp,PRESOLVE_NONE,0);
  set_scaling(s->lp,SCALE_NONE);
  
  ct=get_epsb(s->lp);
  if (ct>(epsilon*1e-2))
    set_epsb(s->lp,ct*1e-2);

  ct=get_epsd(s->lp);
  if (ct>(epsilon*1e-2))
    set_epsd(s->lp,ct*1e-2);
  
  ct=get_epsel(s->lp);
  if (ct>(epsilon*1e-2))
    set_epsel(s->lp,ct*1e-2);

  ct=get_epspivot(s->lp);
  if (ct>(epsilon*1e-4))
    set_epspivot(s->lp,ct*1e-4);
  
  /* LP: Minimize */
  set_minim(s->lp);

  /* LP: Timeout in seconds*/
  set_timeout(s->lp,ncols*SIMPLEX_TIMEOUT); 
}

/* LP: Reset the LP internal information */
void ResetSimplex(TSimplex *s)
{
  default_basis(s->lp);
}

unsigned int SimplexNColumns(TSimplex *s)
{
  return(get_Ncolumns(s->lp));
}

unsigned int SimplexNRows(TSimplex *s)
{
  return(get_Nrows(s->lp));
}

/* LP: set bounds for a given column */
void SimplexSetColBounds(unsigned int ncol,double epsilon,Tinterval *i,TSimplex *s)
{
  double l,u,w;
  unsigned int ncolInt;

  ncolInt=ncol+1;

  l=LowerLimit(i);
  u=UpperLimit(i);
  
  w=u-l;
  if (w<epsilon)
    {
      w=(epsilon-w)/2.0;
      l-=w;
      u+=w;
    }

  if (l==-INF) l=-s->inf;
  if (l== INF) l= s->inf;
  if (u==-INF) u=-s->inf;
  if (u== INF) u= s->inf;
  
  set_lowbo(s->lp,ncolInt,l);
  set_upbo(s->lp,ncolInt,u);
}

/* LP: get bounds for a given column */
void SimplexGetColBounds(unsigned int ncol,Tinterval *i,TSimplex *s)
{
  double l,u;
  unsigned int ncolInt;

  ncolInt=ncol+1;

  l=get_lowbo(s->lp,ncolInt);
  u=get_upbo(s->lp,ncolInt);

  if (l==-s->inf) l=-INF;
  if (l== s->inf) l= INF;
  if (u==-s->inf) u=-INF;
  if (u== s->inf) u= INF;  

  NewInterval(l,u,i);
}

void SimplexGetColConstraint(unsigned int ncol,TLinearConstraint *lc,TSimplex *s)
{
  unsigned int m,i,k;
  double *val;
  signed int *ind;
  Tinterval error;

  m=SimplexNRows(s);

  NEW(val,m+1,double);
  NEW(ind,m+1,signed int);

  k=get_columnex(s->lp,ncol+1,val,ind);

  InitLinearConstraint(lc);
  for(i=0;i<k;i++)
    AddTerm2LinearConstraint(ind[i]-1,val[i],lc);
 
  SimplexGetColBounds(ncol,&error,s);
  SetLinearConstraintError(&error,lc);

  free(val);
  free(ind);
}

boolean SimplexColEmpty(unsigned int ncol,TSimplex *s)
{  
  unsigned int m;
  double *val;
  signed int *ind;
  signed int k;

  m=SimplexNRows(s);

  NEW(val,m+1,double);
  NEW(ind,m+1,signed int);

  k=get_columnex(s->lp,ncol+1,val,ind);

  free(val);
  free(ind);

  return(k==0);
}

void SimplexGetRowsLowerBounds(double *lower,TSimplex *s)
{
  unsigned int i,n;
  signed int t;
  double rhs,size,v;
¡
  n=SimplexNRows(s);
  for(i=1;i<=n;i++)
    {
      t=get_constr_type(s->lp,i);
      rhs=get_rh(s->lp,i);
      size=get_rh_range(s->lp,i);

      switch(t)
	{
	case LE:
	  if (size==s->inf)
	    v=-INF;
	  else
	    v=rhs-size;
	  break;
	case GE:
	  if (size==s->inf)
	    {
	      if (rhs==-s->inf)
		v=-INF;
	      else
		v=rhs;
	    }
	  else
	    v=rhs;
	  break;
	case EQ:
	  v=rhs;
	  break;
	}
      
      lower[i-1]=v;
    }
}

void SimplexGetRowsUpperBounds(double *upper,TSimplex *s)
{
  unsigned int i,n;
  signed int t;
  double rhs,size,v;
¡
  n=SimplexNRows(s);
  for(i=1;i<=n;i++)
    {
      t=get_constr_type(s->lp,i);
      rhs=get_rh(s->lp,i);
      size=get_rh_range(s->lp,i);

      switch(t)
	{
	case LE:
	  v=rhs;
	case GE:
	  if (size==s->inf)
	    v=INF;
	  else
	    v=rhs+size;
	  break;
	case EQ:
	  if (size==s->inf)
	    v=rhs;
	  else
	    v=rhs+size;
	  break;
	}
      
      upper[i-1]=v;
    }
}

double SimplexGetRowDual(unsigned int nrow,TSimplex *s)
{
  return(get_var_dualresult(s->lp,1+nrow));
}

void SimplexGetDuals(double *duals,TSimplex *s)
{
  unsigned int i,n;

  n=SimplexNRows(s);
  for(i=0;i<n;i++)
    duals[i]=get_var_dualresult(s->lp,1+i);
}

void SimplexAddNewConstraintRaw(TLinearConstraint *lc,TSimplex *s)
{
  Tinterval bounds;
  unsigned int nrow,nrowInt;
  unsigned int i;
  double l,u;
  signed int *ind;

  /* LP: Add a row to the tableau */
  nrow=SimplexNRows(s); /* number of the row to be added next */

  n=(int)GetNumTermsInLinearConstraint(lc);
  NEW(ind,n,signed int);
  for(i=0;i<n;i++)
    ind[i]=(signed int)GetLinearConstraintVariable(i,lc)+1; /* numbered from 1 */
	
  /* LP: set the row information  */
  add_constraintex(s->lp,n,
		   GetLinearConstraintCoefficients(lc),
		   ind,
		   EQ,0);

  free(ind);

  GetLinearConstraintError(&bounds,lc);
  nrowInt=nrow+1; /* numbered from 1 */

  t=get_constr_type(s->lp,nrowInt);

  l=LowerLimit(i);
  u=UpperLimit(i);

  if (l==-INF)
    {
      if (u==INF)
	{
	  set_constr_type(s->lp,nrowInt,GE);
	  set_rh(s->lp,nrowInt,-s->inf);
	  set_rh_range(s->lp,nrowInt,s->inf);
	}
      else
	{
	  set_constr_type(s->lp,nrowInt,LE);
	  set_rh(s->lp,nrowInt,u);
	}
    }
  else
    {
      if (u==INF)
	{
	  set_constr_type(s->lp,nrowInt,GE);
	  set_rh(s->lp,nrowInt,l);
	}
      else
	{
	  if (u==l)
	    {
	      set_constr_type(s->lp,nrowInt,EQ);
	      set_rh(s->lp,nrowInt,l);
	    }
	  else	
	    {
	      set_constr_type(s->lp,nrowInt,GE);
	      set_rh(s->lp,nrowInt,l);
	      set_rh_range(s->lp,nrowInt,IntervalSize(i));
	    }
	}
    }

#if (_DEBUG>4)
  printf("          Setting Row %u with range ",nrow);
  PrintInterval(stdout,&bounds);
  printf("\n            ");
  PrintLinearConstraint(stdout,TRUE,NULL,lc);
#endif
}

void SimplexAddCircle(unsigned int x,unsigned int y,double r2,TSimplex *s)
{
  Error("SimplexAddCircle is not implemented in lp_solve");
}

void UpdateSimplex(TSimplex *s)
{
}

void SimplexSetOptimizationFunction(TLinearConstraint *obj,TSimplex *s)
{
  unsigned int i,n;
  signed int *ind;

  #if (_DEBUG>4)
    printf("Setting cost function: ");
  #endif

  n=GetNumTermsInLinearConstraint(obj);

  #if (_DEBUG>4) 
    for(i=0;i<n;i++)
      {
	printf("+%f*v[%u]",
	       GetLinearConstraintCoefficient(i,obj),
	       GetLinearConstraintVariable(i,obj));
      }
  #endif

  NEW(ind,n,signed int);
  for(i=0;i<n;i++)
    ind[i]=(signed int)GetLinearConstraintVariable(i,obj)+1;

  set_obj_fnex(s->lp,n,
	       GetLinearConstraintCoefficients(obj),
	       ind);
  free(ind);

  #if (_DEBUG>4)
    printf("\n");
  #endif
}

void SimplexGetOptimizationCoefficients(double *coef,TSimplex *s)
{
  unsigned int i,n,m;
  double *val;

  n=SimplexNColumns(s);
  m=SimplexNRows(s);

  NEW(val,m+1,double);
  for(i=1;i<=n;i++)
    {
      get_column(s->lp,i,val);
      coef[i]=val[0];
    }
  free(val);
}
  
double SimplexGetOptimalValueRaw(TSimplex *s)
{
  return(get_objective(s->lp));
}

unsigned int SimplexSolve(TSimplex *s)
{
  unsigned int r;

  /*print_lp(s->lp); exit(0);*/

  r=solve(s->lp);

  if (r==OPTIMAL)
    return(REDUCED_BOX);
  else
    {
      if (r==INFEASIBLE)
	return(EMPTY_BOX);
      else
	{
	  if (r==UNBOUNDED)
	    return(UNBOUNDED_BOX);
	  else
	    return(ERROR_IN_PROCESS);
	}
    }
}

void SimplexDelete(TSimplex *s)
{
  delete_lp(s->lp);
}


