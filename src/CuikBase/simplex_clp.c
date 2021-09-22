#include "simplex.h"
#include "error.h"
#include "geom.h"
#include "defines.h"

#include <float.h>
#include <math.h>
#include <string.h>

/** 
   \file simplex_clp.c

   \brief Implementation of the functions operating on TSimplex using
          the <A HREF="http://www.coin-or.org/projects/Clp.xml">Clp</A>  backend. 

   Implementation of the functions operating on TSimplex using
   the <A HREF="http://www.coin-or.org/projects/Clp.xml">Clp</A>  backend.

   \sa TSimplex, simplex.h, simplex_glpk.c, simplex_lpsolve.c, simplex_gurobi.c.
*/

void SimplexCreate(double epsilon,unsigned int ncols,TSimplex *s)
{
  double ct;
  unsigned int i;

  /*Create the problem*/
  s->lp=Clp_newModel();

  /*Set the number of columns*/
  Clp_resize(s->lp,0,ncols);

  {
    /*We add a fake row to properly initialize the whole matrix*/
    double *v;
    unsigned int *e;

    double rl[1]={-INF};  
    double ru[1]={ INF}; 
    int rs[2]={0,ncols};  

    NEW(v,ncols,double);
    NEW(e,ncols,unsigned int);
    for(i=0;i<ncols;i++)
      {
	e[i]=i;
	v[i]=0;
      }

    Clp_addRows(s->lp,1,rl,ru,rs,(signed int *)e,v);

    free(v);
    free(e);

    s->fakeRows=1; /* number of fake rows in the tableau */
  }
  
  NEW(s->lower,ncols,double);
  NEW(s->upper,ncols,double);
  NEW(s->obj,ncols,double);
  for(i=0;i<ncols;i++)
    {
      s->lower[i]=-INF;
      s->upper[i]=+INF;
      s->obj[i]=0;
    }
  
  /*Set the verbosity level*/ 
  #if (_DEBUG<5)
    Clp_setLogLevel(s->lp,0);
  #endif

  /* LP: Adjust LP internal parameters */
  Clp_scaling(s->lp,0);

  ct=Clp_primalTolerance(s->lp);
  if (ct>(epsilon*1e-3))
    Clp_setPrimalTolerance(s->lp,epsilon*1e-3);

  ct=Clp_dualTolerance(s->lp);
  if (ct>(epsilon*1e-3))
    Clp_setDualTolerance(s->lp,epsilon*1e-3);

  ct=Clp_getSmallElementValue(s->lp);
  if (ct>epsilon)
    Clp_setSmallElementValue(s->lp,epsilon);

  /* LP: Minimize */
  Clp_setOptimizationDirection(s->lp,1);

  /* LP: Timeout in seconds*/
  Clp_setMaximumSeconds(s->lp,ncols*SIMPLEX_TIMEOUT);
}

/* LP: Reset the LP internal information */
void ResetSimplex(TSimplex *s)
{
  /* An empty ResetSimplex functions means that SAFE_SIMPLEX levels 
     1,2,and 3 are equivalent */
}

unsigned int SimplexNColumns(TSimplex *s)
{
  return((unsigned int)Clp_numberColumns(s->lp));
}

unsigned int SimplexNRows(TSimplex *s)
{
  return((unsigned int)Clp_numberRows(s->lp)-s->fakeRows); 
}

/* LP: set bounds for a given column */
void SimplexSetColBounds(unsigned int ncol,double epsilon,Tinterval *i,TSimplex *s)
{
  double l,u,w;
  
  l=LowerLimit(i);
  u=UpperLimit(i);
  
  w=u-l;
  if (w<epsilon)
    {
      w=(epsilon-w)/2.0;
      l-=w;
      u+=w;
    }
  s->lower[ncol]=l;
  s->upper[ncol]=u;

  
  Clp_chgColumnLower(s->lp,s->lower);
  Clp_chgColumnUpper(s->lp,s->upper);
}

/* LP: get bounds for a given column */
void SimplexGetColBounds(unsigned int ncol,Tinterval *i,TSimplex *s)
{
  double *colUpper,*colLower;

  colLower=Clp_columnLower(s->lp);
  colUpper=Clp_columnUpper(s->lp);

  NewInterval(colLower[ncol],colUpper[ncol],i);
}

void SimplexGetColConstraint(unsigned int ncol,TLinearConstraint *lc,TSimplex *s)
{
  Tinterval error;
  const double *elements;
  const int *rowIndices;
  const int *columnLengths;
  const CoinBigIndex *columnStarts;
  CoinBigIndex a,b,i;

  rowIndices=Clp_getIndices(s->lp);
  elements=Clp_getElements(s->lp);

  columnLengths=Clp_getVectorLengths(s->lp);
  columnStarts=Clp_getVectorStarts(s->lp);

  a=columnStarts[ncol];
  b=a+columnLengths[ncol];

  InitLinearConstraint(lc);
  for(i=a;i<b;++i)
    AddTerm2LinearConstraint((unsigned int)rowIndices[i],elements[i],lc);

  SimplexGetColBounds(ncol,&error,s);
  SetLinearConstraintError(&error,lc);
}

boolean SimplexColEmpty(unsigned int ncol,TSimplex *s)
{
  const int *columnLengths; 
  
  columnLengths=Clp_getVectorLengths(s->lp);

  return(columnLengths[ncol]==0);
}

void SimplexGetRowsLowerBounds(double *lower,TSimplex *s)
{
  unsigned int n;
  double *rowLower;

  n=SimplexNRows(s);
  rowLower=Clp_rowLower(s->lp);

  memcpy(lower,&(rowLower[s->fakeRows]),n*sizeof(double));
}

void SimplexGetRowsUpperBounds(double *upper,TSimplex *s)
{
  unsigned int n;
  double *rowUpper;

  n=SimplexNRows(s);
  rowUpper=Clp_rowUpper(s->lp);

  memcpy(upper,&(rowUpper[s->fakeRows]),n*sizeof(double));
}

double SimplexGetRowDual(unsigned int nrow,TSimplex *s)
{
  double *obj;

  obj=Clp_dualRowSolution(s->lp);

  return(obj[nrow+s->fakeRows]);
}

void SimplexGetDuals(double *duals,TSimplex *s)
{
  unsigned int n;
  double *obj;

  obj=Clp_dualRowSolution(s->lp);
  n=SimplexNRows(s);
  memcpy(duals,&(obj[s->fakeRows]),n*sizeof(double));
}

void SimplexAddNewConstraintRaw(TLinearConstraint *lc,TSimplex *s)
{
  Tinterval bounds;
  double rl[1];
  double ru[1]; 
  int rs[2]; /*row starts*/
      
  GetLinearConstraintError(&bounds,lc);

  rl[0]=LowerLimit(&bounds);
  ru[0]=UpperLimit(&bounds);

  rs[0]=0;
  rs[1]=GetNumTermsInLinearConstraint(lc);
      
  Clp_addRows(s->lp,1,rl,ru,rs,
	      (signed int *)GetLinearConstraintVariables(lc),
	      GetLinearConstraintCoefficients(lc));

  #if (_DEBUG>4)
    printf("          Setting Row %u with range ",SimplexNRows(s));
    PrintInterval(stdout,&bounds);
    printf(" [%g %g]\n            ",rl[0],ru[0]);
    PrintLinearConstraint(stdout,TRUE,NULL,lc);
  #endif
}

void SimplexAddCircle(unsigned int x,unsigned int y,double r2,TSimplex *s)
{
  Error("SimplexAddCircle is not implemented in clp");
}

void UpdateSimplex(TSimplex *s)
{
}

void SimplexSetOptimizationFunction(TLinearConstraint *obj,TSimplex *s)
{
  unsigned int i,n;

  n=SimplexNColumns(s);
  
  for(i=0;i<n;i++)
    s->obj[i]=0.0;
  
  n=GetNumTermsInLinearConstraint(obj);
  for(i=0;i<n;i++)
    {
      #if (_DEBUG>4)
      printf("+%f*v[%u]",
	     GetLinearConstraintCoefficient(i,obj),
	     GetLinearConstraintVariable(i,obj));
      #endif

      s->obj[GetLinearConstraintVariable(i,obj)]=GetLinearConstraintCoefficient(i,obj);
    } 
  #if (_DEBUG>4)
    printf("\n");
  #endif
  Clp_chgObjCoefficients(s->lp,s->obj);
}

void SimplexGetOptimizationCoefficients(double *coef,TSimplex *s)
{
  unsigned int n;
  double *obj_c;

  n=SimplexNColumns(s);
  obj_c=Clp_objective(s->lp);

  memcpy(coef,obj_c,n*sizeof(double));
} 

double SimplexGetOptimalValueRaw(TSimplex *s)
{
  return(Clp_objectiveValue(s->lp));
}

unsigned int SimplexSolve(TSimplex *s)
{
  int status;
  unsigned int e;
  
  if (s->fakeRows>0)
    {
      const int w[1]={0};

      Clp_deleteRows(s->lp,1,w);//Remove the initial fake row

      s->fakeRows=0;
    }
  
  Clp_primal(s->lp,1); /* 1 => something changed in the problem!*/

  status=Clp_status(s->lp);

  switch(status)
    {
    case 0: /* optimal */
      e=REDUCED_BOX;
      break;
    case 1: /* primal infeasible*/
      e=EMPTY_BOX;
      break;
    case 2: /* dual infeasible*/
      e=UNBOUNDED_BOX;
      break;
    default:
      e=ERROR_IN_PROCESS;
    }
  return(e);
}

void SimplexDelete(TSimplex *s)
{
  if (SimplexNRows(s)>0)
    Clp_deleteModel(s->lp);

  free(s->lower);
  free(s->upper);
  free(s->obj);
}


