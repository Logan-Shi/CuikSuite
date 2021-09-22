#include "simplex.h"
#include "error.h"
#include "geom.h"
#include "defines.h"

#include <math.h>
#include <string.h>

/** 
   \file simplex_glpk.c

   \brief Implementation of the functions operating on TSimplex using
          the <A HREF="http://www.gnu.org/software/glpk/">Glpk</A> backend. 

   Implementation of the functions operating on TSimplex using
   the <A HREF="http://www.gnu.org/software/glpk/">Glpk</A> backend. 


   \sa TSimplex, simplex.h, simplex_clp.c, simplex_lpsolve.c, simplex_gurobi.c.
*/

void SimplexCreate(double epsilon,unsigned int ncols,TSimplex *s)
{
  double ct;

  /* LP: Create an empty LP problem */
  s->lp=lpx_create_prob();
  if (s->lp==NULL)
    Error("Problems creating LP tableau\n");
 

  /* LP: Add the columns to the LP problem */
  lpx_add_cols(s->lp,ncols);


  /* LP: Adjust the verbosity of the LP problem */
  #if (_DEBUG<5)
    lpx_set_int_parm(s->lp,LPX_K_MSGLEV,0);
  #endif


  /* LP: Adjust LP internal parameters */
  ct=lpx_get_real_parm(s->lp,LPX_K_TOLBND);
  if (ct>(epsilon*1e-2))
    lpx_set_real_parm(s->lp,LPX_K_TOLBND,epsilon*1e-2);
  
  ct=lpx_get_real_parm(s->lp,LPX_K_TOLDJ);
  if (ct>(epsilon*1e-2))
    lpx_set_real_parm(s->lp,LPX_K_TOLDJ,epsilon*1e-2);
  
  ct=lpx_get_real_parm(s->lp,LPX_K_TOLPIV);
  if (ct>(epsilon*1e-4))
    lpx_set_real_parm(s->lp,LPX_K_TOLPIV,epsilon*1e-4);


  /* LP: Minimize */
  lpx_set_obj_dir(s->lp,LPX_MIN); 


  /* LP: Timeout in seconds*/
  lpx_set_real_parm(s->lp,ncols*LPX_K_TMLIM,SIMPLEX_TIMEOUT); 
}

/* LP: Reset the LP internal information */
void ResetSimplex(TSimplex *s)
{
  lpx_adv_basis(s->lp);
}

unsigned int SimplexNColumns(TSimplex *s)
{
  return(lpx_get_num_cols(s->lp));
}

unsigned int SimplexNRows(TSimplex *s)
{
  return(lpx_get_num_rows(s->lp));
}

/* LP: set bounds for a given column */
void SimplexSetColBounds(unsigned int ncol,double epsilon,Tinterval *i,TSimplex *s)
{
  double l,u,w;

  l=LowerLimit(i);
  u=UpperLimit(i);
  
  if (l==-INF)
    {
      if (u==INF)
	lpx_set_col_bnds(s->lp,ncol+1,LPX_FR,0.0,0.0);
      else
	lpx_set_col_bnds(s->lp,ncol+1,LPX_UP,0.0,u);
    }
  else
    {
      if (u==INF)
	lpx_set_col_bnds(s->lp,ncol+1,LPX_LO,l,0.0);
      else
	{
	  if (u==l)
	    lpx_set_col_bnds(s->lp,ncol+1,LPX_FX,l,l);
	  else
	    {
	      w=u-l;
	      if (w<epsilon)
		{
		  w=(epsilon-w)/2.0;
		  l-=w;
		  u+=w;
		}
	      lpx_set_col_bnds(s->lp,ncol+1,LPX_DB,l,u);
	    }
	}
    }
}

/* LP: get bounds for a given column */
void SimplexGetColBounds(unsigned int ncol,Tinterval *i,TSimplex *s)
{
  unsigned int t;
  double l,u;

  t=lpx_get_col_type(s->lp,ncol+1);
  l=lpx_get_col_lb(s->lp,ncol+1);
  u=lpx_get_col_ub(s->lp,ncol+1);

  switch(t)
    {
    case LPX_FR:
      NewInterval(-INF,INF,i);
      break;
    case LPX_LO:
      NewInterval(l,INF,i);
      break;
    case LPX_UP:
      NewInterval(-INF,u,i);
      break;
    case LPX_FX:
    case LPX_DB:
      NewInterval(l,u,i); /*only columns of this type exists in our examples*/
      break;
    }
}

void SimplexGetColConstraint(unsigned int ncol,TLinearConstraint *lc,TSimplex *s)
{
  unsigned int m,k,i;
  signed int *ind;
  double *val;
  Tinterval error;

  m=SimplexNRows(s);

  NEW(val,m+1,double);
  NEW(ind,m+1,signed int);

  k=lpx_get_mat_col(s->lp,ncol+1,ind,val);

  InitLinearConstraint(lc);
  for(i=1;i<=k;i++)
    AddTerm2LinearConstraint(ind[i]-1,val[i],lc);
 
  SimplexGetColBounds(ncol,&error,s);
  SetLinearConstraintError(&error,lc);

  free(ind);
  free(val);
}

boolean SimplexColEmpty(unsigned int ncol,TSimplex *s)
{
  return((unsigned int)lpx_get_mat_col(s->lp,1+ncol,NULL,NULL)==0);
}

void SimplexGetRowsLowerBounds(double *lower,TSimplex *s)
{
  unsigned int i,n;
  unsigned int t;
  double l;
  
  n=SimplexNRows(s);
  for(i=1;i<=n;i++)
    {
      t=lpx_get_row_type(s->lp,i);
      l=lpx_get_row_lb(s->lp,i);
      switch(t)
	{
	case LPX_FR:
	case LPX_UP:
	  lower[i-1]=-INF;
	  break;
	case LPX_LO:
	case LPX_FX:
	case LPX_DB:
	  lower[i-1]=l;
	  break;
	}
    }
}

void SimplexGetRowsUpperBounds(double *upper,TSimplex *s)
{
  unsigned int i,n;
  unsigned int t;
  double u;

  n=SimplexNRows(s);
  for(i=1;i<=n;i++)
    {
      t=lpx_get_row_type(s->lp,i);
      u=lpx_get_row_ub(s->lp,i);
      switch(t)
	{
	case LPX_FR:
	case LPX_LO:
	  upper[i-1]=INF;
	  break;
	case LPX_UP:
	case LPX_FX:
	case LPX_DB:
	  upper[i-1]=u;
	  break;
	}
    }
}

  
double SimplexGetRowDual(unsigned int nrow,TSimplex *s)
{
  return(lpx_get_row_dual(s->lp,nrow+1));
}

void SimplexGetDuals(double *duals,TSimplex *s)
{
  unsigned int i,n;

  n=SimplexNRows(s);
  for(i=0;i<n;i++)
    duals[i]=lpx_get_row_dual(s->lp,i+1);
}

void SimplexAddNewConstraintRaw(TLinearConstraint *lc,TSimplex *s)
{
  Tinterval bounds;
  unsigned int nrow;
  unsigned int i;
  double l,u;
  signed int *ind;
  double *val;
  unsigned int n;

  /* LP: Add a row to the tableau */
  nrow=lpx_add_rows(s->lp,1);
  if (nrow==((unsigned int)(-1)))
    Error("Error adding constraint to simplex");

  n=GetNumTermsInLinearConstraint(lc);
  
  NEW(ind,n+1,signed int);
  NEW(val,n+1,double);

  for(i=0;i<n;i++)
    {
      ind[i+1]=GetLinearConstraintVariable(i,lc)+1;
      val[i+1]=GetLinearConstraintCoefficient(i,lc);
    }

  /* LP: set the row information  */
  lpx_set_mat_row(s->lp,nrow,n,ind,val);
      
  free(ind);
  free(val);
      
  /* Set row bounds */
  GetLinearConstraintError(&bounds,lc);
  l=LowerLimit(i);
  u=UpperLimit(i);

  if (l==-INF)
    {
      if (u==INF)
	lpx_set_row_bnds(s->lp,nrow,LPX_FR,0.0,0.0);
      else
	lpx_set_row_bnds(s->lp,nrow,LPX_UP,0.0,u);
    }
  else
    {
      if (u==INF)
	lpx_set_row_bnds(s->lp,nrow,LPX_LO,l,0.0);
      else
	{
	  if (u==l)
	    lpx_set_row_bnds(s->lp,nrow,LPX_FX,l,l);
	  else	
	    lpx_set_row_bnds(s->lp,nrow,LPX_DB,l,u);
	}
    }
      
#if (_DEBUG>4)
  printf("          Setting Row %u with range ",nrow-1);
  PrintInterval(stdout,&bounds);
  printf("\n            ");
  PrintLinearConstraint(stdout,TRUE,NULL,lc);
#endif
}

void SimplexAddCircle(unsigned int x,unsigned int y,double r2,TSimplex *s)
{
  Error("SimplexAddCircle is not implemented in glpx");
}

void UpdateSimplex(TSimplex *s)
{
}

void SimplexSetOptimizationFunction(TLinearConstraint *obj,TSimplex *s)
{
  unsigned int i,n;

  #if (_DEBUG>4)
    printf("Setting cost function: ");
  #endif

  n=SimplexNColumns(s);
  
  for(i=0;i<n;i++)
    lpx_set_obj_coef(s->lp,i+1,0.0);
  
  n=GetNumTermsInLinearConstraint(obj);
  for(i=0;i<n;i++)
    {
      #if (_DEBUG>4)
      printf("+%f*v[%u]",
	     GetLinearConstraintCoefficient(i,obj),
	     GetLinearConstraintVariable(i,obj));
      #endif
      lpx_set_obj_coef(s->lp,
		       GetLinearConstraintVariable(i,obj)+1,
		       GetLinearConstraintCoefficient(i,obj));
    } 
  #if (_DEBUG>4)
    printf("\n");
  #endif
}

void SimplexGetOptimizationCoefficients(double *coef,TSimplex *s)
{
  unsigned int i,n;

  n=SimplexNColumns(s);

  for(i=0;i<n;i++)
    coef[i]=lpx_get_obj_coef(s->lp,i+1);
}

double SimplexGetOptimalValueRaw(TSimplex *s)
{
  return(lpx_get_obj_val(s->lp));
}

unsigned int SimplexSolve(TSimplex *s)
{
  unsigned int r;

  r=lpx_simplex(s->lp);

  if (r==LPX_E_TMLIM)
    return(ERROR_IN_PROCESS);
  else
    {
      if (r==LPX_E_OK)
	{
	  r=lpx_get_status(s->lp);
	  
	  if (r==LPX_OPT)
	    return(REDUCED_BOX);
	  else
	    {
	      if (r==LPX_NOFEAS)
		return(EMPTY_BOX);
	      else
		{
		  if (r==LPX_UNBND)
		    return(UNBOUNDED_BOX);
		  else
		    return(ERROR_IN_PROCESS);
		}
	    }
	}
      else
	return(ERROR_IN_PROCESS);
    }
}

void SimplexDelete(TSimplex *s)
{
  lpx_delete_prob(s->lp);
}


