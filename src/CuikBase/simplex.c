#include "simplex.h"

#include "defines.h"
#include "random.h"


/** 
   \file simplex.c

   \brief Implementation of the functions operating on TSimplex that are independent of
          the simplex backend. 

   Implementation of the functions operating on box TSimplex that are independent of
   the simplex backend. 

   \sa TSimplex, simplex.h, simplex_clp.c, simplex_glpk.c, simplex_lpsolve.c.
*/

void SimplexExpandBounds(unsigned int eq_type,Tinterval *b)
{
  double v1,v2;

  v1=LowerLimit(b);
  v2=UpperLimit(b);

  if (eq_type==LEQ)
    v1=-INF;
  else
    {
      if (eq_type==GEQ)
	v2=INF;
    }

  NewInterval(v1,v2,b);
}

/*
  Sets new ranges for the variables in the simplex
*/
void SetSimplexBounds(double epsilon,Tbox *b,TSimplex *lp)
{
  unsigned int i;
  Tinterval *is;
  unsigned int nv;

  #if (_DEBUG>4)
    printf("  Setting bound for columns (variable):\n");
  #endif

  nv=GetBoxNIntervals(b);
  is=GetBoxIntervals(b);
  for(i=0;i<nv;i++)
    {
      SimplexSetColBounds(i,0.0,&(is[i]),lp);

      #if (_DEBUG>4)
        printf("    %u: ",i);
	PrintInterval(stdout,&(is[i]));
	if (IntervalSize(&(is[i]))<INF)
	  printf(" -> %g\n",IntervalSize(&(is[i])));
	else
	  printf(" -> +inf\n");
      #endif
    }
}

boolean SimplexAddNewConstraint(double epsilon,
				unsigned int safeSimplex,
				TLinearConstraint *lc,
				unsigned int eq_type,
				Tinterval *is,
				TSimplex *s)
{ 
  boolean full;

  full=TRUE;

  if (BoundedLinearConstraint(lc))
    {
      TLinearConstraint lcInt;
      unsigned int n;
      Tinterval bounds;
      double es,ic;

      /*We avoid any modification in the given linear constraint. Modification
	can produce undesired side-effects out of this method*/
      CopyLinearConstraint(&lcInt,lc);

      #if (_DEBUG>4)
        printf("       Adding new constraint:\n         ");
	PrintLinearConstraint(stdout,TRUE,NULL,&lcInt);
      #endif

      /* Small ranges for the variables can produce simplex inestabilities.
	 To improve numerical stability we can subsume those small ranges in
	 the right-hand side of the equation.
	 For inequalities this operation is done for safeSimplex>=6.
	 For equalities this is only done for safeSimplex>=5. This is so to
	 minimize the risk of converting an equality into an inequality.
     
	 For GLPK it is compulsatory to use this. For the other simplex engines
	 a smaller threshold could be used.  */

      if ((safeSimplex>=6)||
	  ((safeSimplex>=5)&&(GetLinearConstraintErrorSize(&lcInt)>0)))
	CleanLinearConstraint((_SIMPLEX_ENGINE==_GLPK?epsilon:ZERO),is,&lcInt);

      #if (_DEBUG>4)
        printf("         Constraint after cleaning:\n           ");
	PrintLinearConstraint(stdout,TRUE,NULL,&lcInt);
      #endif

      n=GetNumTermsInLinearConstraint(&lcInt);
      /* If the input linear constraint involves at least one variable...*/
      if (n>0)
	{	  
	  /* linear constraint with very narrow range are converted to inequalities
	     (randomly selecting LEQ or GEQ). This is a conservative way to avoid
	     numerical issues. */
	  GetLinearConstraintError(&bounds,&lcInt);
	  SimplexExpandBounds(eq_type,&bounds);
	  SetLinearConstraintError(&bounds,&lcInt);

	  #if (_DEBUG>4)
	    printf("         Constraint after expanding bounds:\n           ");
	    PrintLinearConstraint(stdout,TRUE,NULL,&lcInt);
	  #endif

	  if (!SimplifyLinearConstraint(&full,is,&lcInt))
	    {
	      /*******************************************************************/
	      /* Extremely small ranges for equalities are not correctly processed
		 by the simplex engines (they convert the tiny ranges to a point and
		 then solutions might be lost) 
	     
		 Those small ranges are produced in problems where we use a tiny
		 epsilon or due to the CleanLinearConstraint process (possibly) used
		 above.
	      */
	      if (eq_type==EQU)
		{
		  es=IntervalSize(&bounds);
		  if(safeSimplex>=4)
		    {
		      if (es>0)
			{
			  if (es<=ZERO)
			    {
			      /*This is an equality that somehow has been converted in
				a double bounded constraint with very tiny range (or error).
				We convert it back to an equality.
				Note that with this we can lose solutions.
				Use safeSimplex<4 to avoid this process.*/
			      ic=IntervalCenter(&bounds);
			      NewInterval(ic,ic,&bounds);
			      SetLinearConstraintError(&bounds,&lcInt);
			    }
			  else
			    {
			      if ((safeSimplex>=7)&&(es<epsilon))
				{
				  /*For double bounded constraints with very tiny
				    error, we use only one of the constraints >= or <=
				    selected randomly. This is numerically safer.
				    However, if the user selected an epsilon below 1e-6
				    we assume she wants to be in the wild side and 
				    that constraint errors can be arbitrarily small.
				  */
				  SimplexExpandBounds((randomDouble()<0.5?LEQ:GEQ),&bounds);
				  SetLinearConstraintError(&bounds,&lcInt);
				}
			    }
			}
		    }
		  /*
		    else
		    {
		    if (es<epsilon)
		    {
		    SimplexExpandBounds((randomDouble()<0.5?LEQ:GEQ),&bounds);
		    SetLinearConstraintError(&bounds,&lcInt);
		    //Tinterval kk;
		      
		    //NewInterval(-epsilon/2.0,epsilon/2.0,&kk);
		    //IntervalAdd(&bounds,&kk,&bounds);
		    //SetLinearConstraintError(&bounds,&lcInt);
		    }
		    }
		  */
		}
	      /*******************************************************************/
	  
	      SimplexAddNewConstraintRaw(&lcInt,s);
	    }
	  #if (_DEBUG>4)
	  else
	    printf("           Empty simplified equation\n");
	  #endif
	}
      #if (_DEBUG>4)
      else
	printf("       Empty input equation\n");
      #endif

      DeleteLinearConstraint(&lcInt);
    }
  #if (_DEBUG>4)
  else
    printf("       Unbounded linear constraint. No constraint.\n");
  #endif
  return(full);
}

double SimplexGetOptimalValue(unsigned int safeSimplex,double m,Tbox *x,TSimplex *s)
{
  double o_safe;
 
  if (safeSimplex==0)
    o_safe=SimplexGetOptimalValueRaw(s);
  else
    {
      /*
	LP safe bounds taken from
	"Safe bounds in linear and mixed-integer linear programming"
	Arnold Neumaier and Oleg Shcherbina, 2003
      */

      double *lambda,*obj_c,*ct_l,*ct_u;
      double o,rl,ru;
      unsigned int n,m;
      unsigned int i,j,k;;
      Tinterval r,obj,a;
      TLinearConstraint lc;

      m=SimplexNRows(s);
      n=SimplexNColumns(s);

      NEW(lambda,3*m+n,double);
      ct_l=&(lambda[m]);
      ct_u=&(ct_l[m]);
      obj_c=&(ct_u[m]);
      
      SimplexGetDuals(lambda,s);
      SimplexGetOptimizationCoefficients(obj_c,s);

      /* o_safe = inf{  (\sum_j^m lambda[j]*b[j]) - (sum_i^n r[i]*x[i])}
	 with 
	 r[i] = - c[i] + sum_j^m A(j,i)*lambda[j]
	 Note that only the lower limit is necessary, thus
	 o_safe = inf{\sum_j^m lambda[j]*b[j]} -sup{sum_i^n r[i]*x[i]}
      */

      SimplexGetRowsLowerBounds(ct_l,s);
      SimplexGetRowsUpperBounds(ct_u,s);
      
      o_safe=0.0; /*= inf{\sum_j^m lambda[j]*b[j]} */
      ROUNDDOWN;
      for(j=0;j<m;j++)
	{
	  if ((ct_u[j]==INF)||(lambda[j]>0))
	    o_safe+=(lambda[j]*ct_l[j]);
	  else
	    o_safe+=(lambda[j]*ct_u[j]);
	}
      ROUNDNEAR;

      NewInterval(0.0,0.0,&obj); /*obj=sum_i^n r[i]*x[i]*/

      for(i=0;i<n;i++)
	{
	  /*Compute r[i] = -c[i] + sum_j^m A(j,i)*lambda[j] */
	  SimplexGetColConstraint(i,&lc,s);
	  k=GetNumTermsInLinearConstraint(&lc);

	  ROUNDDOWN;
	  rl=-obj_c[i];
	  for(j=0;j<k;j++)
	    rl+=(GetLinearConstraintCoefficient(j,&lc)*lambda[GetLinearConstraintVariable(j,&lc)]);
	    
	  ROUNDUP;
	  ru=-obj_c[i];
	  for(j=0;j<k;j++)
	    ru+=(GetLinearConstraintCoefficient(j,&lc)*lambda[GetLinearConstraintVariable(j,&lc)]);
      
	  ROUNDNEAR;
	  NewInterval(rl,ru,&r);

	  /*Compute r[i]*x[i]*/
	  IntervalProduct(&r,GetBoxInterval(i,x),&a);

	  /*Add to obj*/
	  IntervalAdd(&obj,&a,&obj);
	
	  DeleteLinearConstraint(&lc);
	}

      free(lambda);

      ROUNDDOWN;
      o_safe=o_safe-UpperLimit(&obj);
      ROUNDNEAR;

      o=SimplexGetOptimalValueRaw(s);

      o_safe=(o_safe<o?o_safe:o);
    }

  return((o_safe<m?m:o_safe));
}


/*
  Reduces a box along a given range. The reduction is based on minimizing
  the simplex problem with a objective function that only affects the given
  varible. 
*/
unsigned int ReduceRange(double epsilon,unsigned int safeSimplex,
			 unsigned int nv,Tbox *b,TSimplex *lp)
{
  unsigned int j;                        
  unsigned int r;    /*Simplex result*/
  boolean empty;     
  boolean err;       /*Simplex error*/
  Tinterval new_range;
  Tinterval *i_in;
  double s_in;
  double o;
  TLinearConstraint obj;
  
  empty=FALSE;
  err=FALSE;

  /* Add the most up to date bounds for the system/dummy variables to the simplex */
  SetSimplexBounds(epsilon,b,lp);
  
  #if ((_SIMPLEX_ENGINE!=_CLP)&&(_SIMPLEX_ENGINE!=_GUROBI))
    /* in CLP/Gurobi ResetSimplex has no effect */
    if (safeSimplex>=2)
      {
	/* This improves the numerical stability but slows down the process */
	ResetSimplex(lp);
      }
  #endif

  i_in=GetBoxInterval(nv,b);  /* Range to be reduced */

  s_in=IntervalSize(i_in);

  #if (_DEBUG>4)
    printf("  Reducing interval %u via simplex\n",nv);
    printf("    Original Interval ");
    PrintInterval(stdout,i_in);
    if (s_in>=INF) printf(" s: inf\n");
    else printf(" s:%g\n",s_in);
  #endif

  CopyInterval(&new_range,i_in); /* Default initialization used in case 
				    of ERROR_IN_PROCESS*/
  if (s_in>=epsilon)
    {
      InitLinearConstraint(&obj);
  
      for(j=0;((!empty)&&(!err)&&(j<2));j++) /*j=0 minimize j=1 maximize*/
	{
	  ResetLinearConstraint(&obj);
	  if (j==0)
	    {
	      AddTerm2LinearConstraint(nv,+1.0,&obj);

	      #if (_DEBUG>4)
	        printf("Determining lower bound for variable %u -> \n",nv);
	      #endif
	    }
	  else
	    {
	      AddTerm2LinearConstraint(nv,-1.0,&obj);

	      #if (_DEBUG>4)
	        printf("Determining upper bound for variable %u -> \n",nv);
	      #endif
	    }

	  SimplexSetOptimizationFunction(&obj,lp);

          #if ((_SIMPLEX_ENGINE!=_CLP)&&(_SIMPLEX_ENGINE!=_GUROBI))
	     /* in CLP/Gurobi ResetSimplex has no effect */
	    if ((safeSimplex>=3)&&(j==1))
	      {
		/* This improves (even more) the numerical stability but slows down (even more)
		   the process (See the use of ResetSimplex in ReduceBox) */
		ResetSimplex(lp);
	      }
	  #endif

	  /*Solve the simplex problem*/
	  #if (_DEBUG>4)
	    printf("==================================================================================\n");
	  #endif
	  r=SimplexSolve(lp);

          #if ((_SIMPLEX_ENGINE!=_CLP)&&(_SIMPLEX_ENGINE!=_GUROBI))
	    /* in CLP/Gurobi ResetSimplex has no effect */
	    if ((r==EMPTY_BOX)||
		(r==ERROR_IN_PROCESS)||
		((j==1)&&(r==REDUCED_BOX)&&(-o<LowerLimit(&new_range))))
	      {
		/* A second chance but with clean internal
		   structures. This minimizes que change of wrongly
		   classifying a box as empty */
		ResetSimplex(lp);
		r=SimplexSolve(lp);
	      }
          #endif

	  if (r==REDUCED_BOX)
	    {
	      if (IntervalSize(i_in)<INF)
		o=SimplexGetOptimalValue(safeSimplex,(j==0?LowerLimit(i_in):-UpperLimit(i_in)),b,lp);
	      else
		o=SimplexGetOptimalValueRaw(lp);
	    }

	  #if (_DEBUG>4)
	    printf("==================================================================================\n");
	  #endif

	  switch(r)
	    {
	    case REDUCED_BOX:
	      if (j==0) /*min*/
		{
		  /*a new lower: we only use the new lower limit if it is
		    higher than the current one. Lower lower limits can
		    appear due to numerical errors*/
		  UpdateLowerLimit(o,&new_range);
	      
		  #if (_DEBUG>4)
		    printf("   The new lower limit is %g\n",LowerLimit(&new_range));
		  #endif
		}
	      else /*max*/
		{
		  /*a new upper: we only use the new upper limit if it is
		    lower than the current one. Higer upper limits can
		    appear due to numerical errors*/
		  UpdateUpperLimit(-o,&new_range); 

		  #if (_DEBUG>4)
		    printf("   The new upper limit is %g\n",UpperLimit(&new_range));
		    fflush(stdout);
		  #endif
		}
	      break;

	    case EMPTY_BOX:
	      empty=TRUE;
	      break;

	    case UNBOUNDED_BOX: /* This should never happen... */
	    case ERROR_IN_PROCESS:
	      #if ((_SIMPLEX_ENGINE!=_CLP)&&(_SIMPLEX_ENGINE!=_GUROBI))
	        /* in CLP/Gurobi ResetSimplex has no effect */
	        ResetSimplex(lp);
	      #endif 
	      err=TRUE;
	      break;

	    default:
	      Error("Unknow Error in ReduceRange");
	    }
	} /*min/max*/

      DeleteLinearConstraint(&obj);
      

      #if (_DEBUG>4)
        if (!empty)
	  printf("   Interval out of simplex [%g %g] s:%g\n",
		 LowerLimit(&new_range),
		 UpperLimit(&new_range),
		 IntervalSize(&new_range));
	else
	  printf("   Empty Interval out of simplex\n");
      #endif

    
      if ((!empty)&&(!err))
	{
	  /*
	    In some cases the simplex return empty intervals. This occurs due to
	    numerical inestabilities in the simplex tableau monomialization process. 
	    We treat this as an error -> the box is bisected and a brand new
	    simplex-based reduction is triggered
	  */
	  if (EmptyInterval(&new_range))
	    err=TRUE;
	  else
	    CopyInterval(i_in,&new_range);
	}
    }
  #if (_DEBUG>4)
  else
    printf("  Input interval is too small to be reduced any more\n");
  #endif

  if (empty)
    return(EMPTY_BOX);
  else
    {
      if (err)
	return(ERROR_IN_PROCESS);
      else
	return(REDUCED_BOX);
    }
}
