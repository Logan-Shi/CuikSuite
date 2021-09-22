#include "equations.h"

#include "defines.h"
#include "error.h"
#include "geom.h"

#include <math.h>

/** \file equations.c
    \brief Implementation of the functions operating on sets of Tequations.

    Implementation of the functions operating on sets of Tequations.
 
   \sa Tequations, TequationInfo, equations.h.
*/

/** 
   \brief TequationInfo constructor.

   Defines all the information associated with a scalar equation.

   \param e The equation.
   \param ei The equation information to create..
   
   \sa TequationInfo
*/
void SetEquationInfo(Tequation *e,TequationInfo *ei);

/** 
   \brief Returns the equation stored in a TequationInfo.

    Returns the equation stored in a TequationInfo.
   
    \param ei The equation information.

    \return A pointer to the equation from which the equation information
            was created.

*/
Tequation *GetOriginalEquation(TequationInfo *ei);

/** 
   \brief TequationInfo copy constructor.

   Creates a TequationInfo copying data from another TequationInfo.

   \param ei_dst The equation information to create.
   \param ei_src The equation information from where to copy the data.

*/
void CopyEquationInfo(TequationInfo *ei_dst,TequationInfo *ei_src);

/** 
   \brief Gets a first order approximation to a given equation.

   Defines a first order approximation to a given equation from the information
   we have of this equation.<br>

   \param b The box with the ranges for the variables.
   \param c The linearization point.
   \param lc The linear constraint to be created.
   \param ei The equation information from which to create the linear approximation.

   \sa TlinearConstraint

*/
void GetFirstOrderApproximationToEquation(Tbox *b,double *c,
					  TLinearConstraint *lc,
					  TequationInfo *ei);
/** 
   \brief Computes the linealization error for a given equation for each variable
          involved in the equation.

   Computes the linealization error for a given equation for each variable
   involved in the equation.

   \param m Number of variables in the system of equations.
   \param c The linealization point.
   \param is Ranges for the variables in the system.
   \param ev Array of double where to add the linealization error induced by
             each variable for the equation.
   \param ei The equation information.
   
*/
void ErrorDueToVariable(unsigned int m,double *c,Tinterval *is,double *ev,TequationInfo *ei);

/** 
   \brief Produces a linear relaxation for a saddle equation.

    Produces a linear relaxation for a \ref SADDLE_EQUATION "saddle equations"
    of the form \f$x y + \alpha z =\beta\f$. 
    It consists of four planes each derived from a linealization of the 
    saddle funcion at the corners of the <em>x-y</em> box.

    The same routine is used to linearize \ref BILINEAL_MONOMIAL_EQUATION "single monomial bilineal"
    equations of the form \f$x y  =\beta\f$.

   \param epsilon Threshold to remove tiny terms in the generated linear constraints.
   \param safeSimplex Degree of numerical stability in the simplex as specified by
                      the user in the \ref CT_SAFE_SIMPLEX "SAFE SIMPLEX" parameter.
   \param b The box with the ranges for the varibles.
   \param lp The simplex where to add the linear constraints.
   \param ei The equation information to use.

   \return TRUE if the simplex is still feasible after adding the constraints.
*/
boolean  LinearizeSaddleEquation(double epsilon,
				 unsigned int safeSimplex,
				 Tbox *b,
				 TSimplex *lp,TequationInfo *ei);


/** 
   \brief Produces a linear relaxation for a bilienal monomial equation.

    Produces a linear relaxation for a \ref BILINEAL_MONOMIAL_EQUATION "bilineal monomial equations"
    of the form \f$x y =\beta\f$ (an equation formed by a single bilineal monomial).
    This equation can be seen as a degenerate saddle but a particular treatment
    results beneficial.
 
   \param epsilon Threshold to remove tiny terms in the generated linear constraints.
   \param lr2tm Maximum size to switch from linear relaxations to taylor models.
   \param safeSimplex Degree of numerical stability in the simplex as specified by
                      the user in the \ref CT_SAFE_SIMPLEX "SAFE SIMPLEX" parameter.
   \param b The box with the ranges for the varibles.
   \param lp The simplex where to add the linear constraints.
   \param ei The equation information to use.

   \return TRUE if the simplex is still feasible after adding the constraints.
*/
boolean  LinearizeBilinealMonomialEquation(double epsilon,
					   double lr2tm,
					   unsigned int safeSimplex,
					   Tbox *b,
					   TSimplex *lp,TequationInfo *ei);

/** 
   \brief Produces a linear relaxation for a parabola equation.

   Produces a linear relaxation for a parabola equation \f$x^2 + \alpha z =\beta\f$. 
   It consists of two lines derived from a linear approximation of
   the parabola at the center of the \e x interval. Additionaly,
   we define linear constraints on the extremes of the range of \e x.
   
   \param epsilon Threshold to remove tiny terms in the generated linear constraints.
   \param safeSimplex Degree of numerical stability in the simplex as specified by
                      the user in the \ref CT_SAFE_SIMPLEX "SAFE SIMPLEX" parameter.
   \param b The box with the ranges for the varibles.
   \param lp The simplex where to add the linear constraints.
   \param ei The equation information to use.

   \return TRUE if the simplex is still feasible after adding the constraints.
*/
boolean LinearizeParabolaEquation(double epsilon,
				  unsigned int safeSimplex,
				  Tbox *b,
				  TSimplex *lp,TequationInfo *ei);

/** 
   \brief Produces a linear relaxation for a circle equation.

   Produces a linear relaxation for a circle equation \f$x^2 + y^2 =r^2\f$. 
   It consists of two lines derived from a linear approximation of
   the circle at the center of the \e x-y box. Additionaly,
   we define linear constraints for the corners of the \e x-y box that
   are out of the circle. 
   
   \param epsilon Threshold to remove tiny terms in the generated linear constraints.
   \param safeSimplex Degree of numerical stability in the simplex as specified by
                      the user in the \ref CT_SAFE_SIMPLEX "SAFE SIMPLEX" parameter.
   \param b The box with the ranges for the varibles.
   \param lp The simplex where to add the linear constraints.
   \param ei The equation information to use.

   \return TRUE if the simplex is still feasible after adding the constraints.
*/
boolean LinearizeCircleEquation(double epsilon,
				unsigned int safeSimplex,
				Tbox *b,
				TSimplex *lp,TequationInfo *ei);

/** 
   \brief Produces a linear relaxation for a sphere equation.

   Produces a linear relaxation for a sphere equation \f$x^2 + y^2 + z^2=r^2\f$. 
   It consists of two lines derived from a linear approximation of
   the sphere at the center of the \e x-y-z box. Additionaly,
   we define linear constraints for the corners of the \e x-y-z box that
   are out of the sphere.
   
   \param epsilon Threshold to remove tiny terms in the generated linear constraints.
   \param safeSimplex Degree of numerical stability in the simplex as specified by
                      the user in the \ref CT_SAFE_SIMPLEX "SAFE SIMPLEX" parameter.
   \param b The box with the ranges for the varibles.
   \param lp The simplex where to add the linear constraints.
   \param ei The equation information to use.

   \return TRUE if the simplex is still feasible after adding the constraints.
*/
boolean LinearizeSphereEquation(double epsilon,
				unsigned int safeSimplex,
				Tbox *b,
				TSimplex *lp,TequationInfo *ei);

/** 
   \brief Produces a linear relaxation for a general equation at a given point.

   Produces a linear relaxation for a general equation. 
   It consists of two lines derived from a linear approximation of
   the equation at the given point.
   
   \param cmp LEQ, GEQ, EQU Used to select which one of the two linear constraints
              are to be added to the simplex.
   \param epsilon Threshold to remove tiny terms in the generated linear constraints.
   \param safeSimplex Degree of numerical stability in the simplex as specified by
                      the user in the \ref CT_SAFE_SIMPLEX "SAFE SIMPLEX" parameter.
   \param b The box with the ranges for the varibles.
   \param c The linearization point.
   \param lp The simplex where to add the linear constraints.
   \param ei The equation information to use.

   \return TRUE if the simplex is still feasible after adding the constraints.
*/
boolean LinearizeGeneralEquationInt(unsigned int cmp,
				    double epsilon,
				    unsigned int safeSimplex,
				    Tbox *b,
				    double *c,
				    TSimplex *lp,
				    TequationInfo *ei);
/** 
   \brief Produces a linear relaxation for a general equation at the central point
          of the sub-box defined by the variables involved in the equation.

   Produces a linear relaxation for a general equation at  the central point
   of the sub-box defined by the variables involved in the equation 
   using LinearizeGeneralEquationInt.
   
   \param epsilon Threshold to remove tiny terms in the generated linear constraints.
   \param safeSimplex Degree of numerical stability in the simplex as specified by
                      the user in the \ref CT_SAFE_SIMPLEX "SAFE SIMPLEX" parameter.
   \param b The box with the ranges for the varibles.
   \param lp The simplex where to add the linear constraints.
   \param ei The equation information to use.

   \return TRUE if the simplex is still feasible after adding the constraints.
*/
boolean LinearizeGeneralEquation(double epsilon,
				 unsigned int safeSimplex,
				 Tbox *b,
				 TSimplex *lp,TequationInfo *ei);

/** 
   \brief Destructor.

   Deletes the equation information stored in the and 
   frees the allocated memory space.

   \param ei The equation information to delete.
*/
void DeleteEquationInfo(TequationInfo *ei);

/** 
   \brief Adds an equation to a set.

   This is the same as \ref AddEquation but it does not take
   into accoun whether the added equation is empty or whether
   it is repeated. Moreover, it does not re-order equations in 
   the set.

   This is used as a sub-function of
   \ref AddEquation and also when deriving equation sets.
   In this case it is relevant to obtain an ordered set of
   equations with the correct size (the same as the input
   set of equations) even if they are repeated or empty.

   \param equation The equation to add.
   \param eqs The equation set.
*/
void AddEquationInt(Tequation *equation,Tequations *eqs);

/*******************************************************************************/

void SetEquationInfo(Tequation *eq,TequationInfo *ei)
{
  unsigned int i,j,nf;
  Tvariable_set *vars,*varsf;
  Tmonomial *f;
  unsigned int s;
  Tinterval bounds;
  double v;
  
  NEW(ei->equation,1,Tequation);
  CopyEquation(ei->equation,eq);

  if (GetNumMonomials(eq)==0)
    {
      ei->EqType=EMPTY_EQUATION;
      ei->n=0;
      ei->lc=NULL;
      ei->Jacobian=NULL;
      ei->Hessian=NULL;
    }
  else
    {
      if (LinearEquation(eq))
	ei->EqType=LINEAR_EQUATION;
      else
	{
	  if (ParabolaEquation(eq))
	    ei->EqType=PARABOLA_EQUATION;
	  else
	    {
	      if (SaddleEquation(eq))
		ei->EqType=SADDLE_EQUATION;
	      else
		{
		  if (BilinealMonomialEquation(eq))
		    ei->EqType=BILINEAL_MONOMIAL_EQUATION;
		  else
		    {
		      if (CircleEquation(eq))
			ei->EqType=CIRCLE_EQUATION;
		      else
			{
			  if (SphereEquation(eq))
			    ei->EqType=SPHERE_EQUATION;
			  else
			    ei->EqType=GENERAL_EQUATION;
			}
		    }
		}
	    }
	}

      vars=GetEquationVariables(eq);
      ei->n=VariableSetSize(vars);

      if (ei->EqType==LINEAR_EQUATION)
	{
	  /* Define a LinearConstraint from the Linear equation.
	     The linear constraint is the structure to be directly added to the simplex */

	  NEW(ei->lc,1,TLinearConstraint);
	  InitLinearConstraint(ei->lc);
	  v=GetEquationValue(eq);
	  NewInterval(v,v,&bounds);
	  SimplexExpandBounds(GetEquationCmp(eq),&bounds);
	  SetLinearConstraintError(&bounds,ei->lc);

	  nf=GetNumMonomials(eq);
	  for(i=0;i<nf;i++)
	    {
	      f=GetMonomial(i,eq);
	      varsf=GetMonomialVariables(f);
	      s=VariableSetSize(varsf);
	      if (s!=1) /* The ct terms of the equation are all in the right-hand part */
		Error("Non-linear equation disguised as linear (SetEquationInfo)");

	      AddTerm2LinearConstraint(GetVariableN(0,varsf),GetMonomialCt(f),ei->lc);
	    }

	  ei->Jacobian=NULL;
	  ei->Hessian=NULL;
	}
      else
	{
	  /*Compute the Jacobain/Hessian to be used in the linear approximation*/
	      
	  NEW(ei->Jacobian,ei->n,Tequation *);
	  for(i=0;i<ei->n;i++)
	    {
	      NEW(ei->Jacobian[i],1,Tequation);
	      DeriveEquation(GetVariableN(i,vars),ei->Jacobian[i],eq);
	    }
	      
	  NEW(ei->Hessian,ei->n,Tequation **);
	  for(i=0;i<ei->n;i++)
	    {
	      NEW(ei->Hessian[i],ei->n,Tequation*);
	      for(j=0;j<i;j++)
		ei->Hessian[i][j]=NULL;
	      for(j=i;j<ei->n;j++)
		{
		  NEW(ei->Hessian[i][j],1,Tequation);
		  DeriveEquation(GetVariableN(j,vars),ei->Hessian[i][j],ei->Jacobian[i]);
		}
	    }
	  ei->lc=NULL;  
	}
    }
}

inline Tequation *GetOriginalEquation(TequationInfo *ei)
{
  return(ei->equation);
}

void CopyEquationInfo(TequationInfo *ei_dst,TequationInfo *ei_src)
{
  unsigned int i,j;

  NEW(ei_dst->equation,1,Tequation);
  CopyEquation(ei_dst->equation,ei_src->equation);

  ei_dst->n=ei_src->n;

  ei_dst->EqType=ei_src->EqType;

  if (ei_dst->EqType==EMPTY_EQUATION)
    {
      ei_dst->lc=NULL;
      ei_dst->Jacobian=NULL;
      ei_dst->Hessian=NULL;
    }
  else
    {
      if (ei_dst->EqType==LINEAR_EQUATION)
	{
	  NEW(ei_dst->lc,1,TLinearConstraint);
	  CopyLinearConstraint(ei_dst->lc,ei_src->lc);

	  ei_dst->Jacobian=NULL;
	  ei_dst->Hessian=NULL;
	}
      else
	{
	  NEW(ei_dst->Jacobian,ei_dst->n,Tequation *);
	  for(i=0;i<ei_dst->n;i++)
	    {
	      NEW(ei_dst->Jacobian[i],1,Tequation);
	      CopyEquation(ei_dst->Jacobian[i],ei_src->Jacobian[i]);
	    }
      
	  if (ei_src->Hessian==NULL)
	    ei_dst->Hessian=NULL;
	  else
	    {
	      NEW(ei_dst->Hessian,ei_dst->n,Tequation **);
	      for(i=0;i<ei_dst->n;i++)
		{
		  NEW(ei_dst->Hessian[i],ei_dst->n,Tequation*);
	      
		  for(j=0;j<ei_dst->n;j++)
		    ei_dst->Hessian[i][j]=NULL;
		  for(j=i;j<ei_dst->n;j++)
		    {
		      NEW(ei_dst->Hessian[i][j],1,Tequation);
		      CopyEquation(ei_dst->Hessian[i][j],ei_src->Hessian[i][j]);
		    }
		}
	    }      
	  ei_dst->lc=NULL; 
	}
    }
}

void GetFirstOrderApproximationToEquation(Tbox *b,double *c,
					  TLinearConstraint *lc,
					  TequationInfo *ei)
{
  double d;
  Tinterval a,h;
  unsigned int i,j,k;
  Tvariable_set *vars;
  Tinterval *is,z,half;
  unsigned int m;
  Tinterval *cInt,error,dfc,o;
  double v;

  if (ei->Hessian==NULL)
    Error("Hessian required in GetFirstOrderApproximationToEquation");
  
  m=GetBoxNIntervals(b);
  is=GetBoxIntervals(b);
 
  /* f(x) = f(c) + df(c) (x-c) + E2 */
  /*     with E2 a quadratic error term */
  /* f(x) = df(c) x + f(c) - df(c) c + E2 */
  /*     f(c) and df(c) are evaluated UP and DOWN
         to avoid missing solutions */
  /* f(x) = [df(c)_l df(c)_u] x + [f(c)_l f(c)_u] - [df(c)_l df(c)_u] c + E2 */
  /* f(x) = df(c)_l x + [0 df(c)_u-df(c)_l] x + [f(c)_l f(c)_u] - [df(c)_l df(c)_u] c + E2  */
  /*     We accumulate all the intervals into one error term */
  /*     Error = [0 df(c)_u-df(c)_l] x + [f(c)_l f(c)_u] - [df(c)_l df(c)_u] c + E2  */
  /*     Error = [0 df(c)_u-df(c)_l] x + [f(c)_l f(c)_u] + [-df(c)_u -df(c)_l] c + E2  */
  /* f(x) = df(c)_l x +  Error */
  /**/

  /* To take into account floating point errors, we perform interval evaluation of the
     equations but on punctual intervals (defined from the given points).  */
  
  NewInterval(-ZERO,ZERO,&z);
  NewInterval(0.5-ZERO,0.5+ZERO,&half);

  vars=GetEquationVariables(ei->equation);

  #if (_DEBUG>5)
    printf("          First order approx to equation at [ ");
    for(i=0;i<ei->n;i++)
      {
	k=GetVariableN(i,vars);
	printf("%f ",c[k]);
      }
    printf("]\n");
  #endif

  NEW(cInt,m,Tinterval);
  for(i=0;i<ei->n;i++)
    {
      k=GetVariableN(i,vars);
      NewInterval(c[k]-ZERO,c[k]+ZERO,&(cInt[k]));
    }

  /* This function (GetFirstOrderApproximationToEquation) is typically used within cuik
     and in cuik, equations typically do not include cos/sin -> do not cache their
     evaluation. 
     The same applies to the all the uses of EvaluateEquationInt below. */
  EvaluateEquationInt(cInt,&error,ei->equation); 
  v=GetEquationValue(ei->equation);
  
  /* The coefficients and value of the equations can be affected by some noise
     due to floating point roundings when operating them. We add a small
     range (1e-11) to compensate for those possible errors. */
  NewInterval(-v-ZERO,-v+ZERO,&o);
  
  IntervalAdd(&error,&o,&error);      

  InitLinearConstraint(lc);

  for(i=0;i<ei->n;i++)
    {
      k=GetVariableN(i,vars);

      EvaluateEquationInt(cInt,&dfc,ei->Jacobian[i]); 
      v=GetEquationValue(ei->Jacobian[i]);
      /* The coefficients and value of the equations can be affected by some noise
	 due to floating point roundings when operating them. We add a small
	 range (1e-11) to compensate for those possible errors. */
      NewInterval(-v-ZERO,-v+ZERO,&o);

      IntervalAdd(&dfc,&o,&dfc);

      d=LowerLimit(&dfc);

      IntervalOffset(&dfc,-d,&a);
      IntervalProduct(&a,&(is[k]),&a);
      IntervalAdd(&error,&a,&error);

      IntervalInvert(&dfc,&a);
      IntervalScale(&a,c[k],&a);
      IntervalAdd(&error,&a,&error);

      AddTerm2LinearConstraint(k,d,lc);
    }
  
  /* Now we bound the error using interval arithmetics */
  /*   Error= 0.5 * \sum_{i,j} r[i] H_{i,j} r[j] */

  /* The interval-based bound is exact as far as the Hessian is ct (i.e., we only
     have quadratic functions) and if there are not repeated variables in the
     error expression ( 0.5 * \sum_{i,j} r[i] H_{i,j} r[j]). This is the case
     of the circle, vector product and scalar product that appear in our problems.
     In other cases we could over-estimate the error (this delays the convergence,
     but does not avoid it)
  */

  /* We re-use the cInt vector previously allocated. This is not a problem since cInt
     is not used any more and the size of cInt (num var in the problem) is larger than
     ei->n (number of variables in the current equation) */
  for(i=0;i<ei->n;i++)
    {
      k=GetVariableN(i,vars);
      IntervalOffset(&(is[k]),-c[k],&(cInt[i])); 
      IntervalAdd(&(cInt[i]),&z,&(cInt[i]));
    }

  for(i=0;i<ei->n;i++)
    {
      /* The Hessian is symmetric so we only evaluate the upper triangular part
         (In this way we already have the 0.5 scale factor in the error, 
	 except for the diagonal)*/
      for(j=i;j<ei->n;j++)
	{
	  if (i==j)
	    {
	      IntervalPow(&(cInt[i]),2,&a); /* r[i]^2 */
	      IntervalProduct(&a,&half,&a);
	    }
	  else
	    IntervalProduct(&(cInt[i]),&(cInt[j]),&a); /* r[i]*r[j] */ 
	  //IntervalAdd(&a,&z,&a);

	  EvaluateEquationInt(is,&h,ei->Hessian[i][j]);
	  IntervalOffset(&h,-GetEquationValue(ei->Hessian[i][j]),&h);
	  //IntervalAdd(&h,&z,&h); 

	  IntervalProduct(&a,&h,&a);
	  
	  IntervalAdd(&error,&a,&error);
	}
    }
  
  free(cInt);
  
  /*  If one of the input ranges infinite, we override the computed error
      (probably have overflow....) */
  if (GetBoxMaxSizeVarSet(vars,b)<INF)
    IntervalInvert(&error,&error);
  else
    NewInterval(-INF,INF,&error);

  SetLinearConstraintError(&error,lc);
}

void ErrorDueToVariable(unsigned int m,double *c,Tinterval *is,
			double *ev,TequationInfo *ei)
{
  if (ei->EqType==EMPTY_EQUATION)
    Error("ErrorDueToVariable on an empty equation");

  if (ei->EqType!=LINEAR_EQUATION)
    {
      Tvariable_set *vars;
      unsigned int i,k;
      Tinterval error;
      Tinterval *r,a,h;
      unsigned int j;

      if (ei->Hessian==NULL)
	Error("Hessian required in ErrorDueToVariable");

      /*
	Error= 1/2 * \sum_{i,j} r[i] * H_{i,j} * r[j] -> 
        Error= \sum{i} Error(i) 
	with
	Error(i)= 1/2 * r[i] * \sum_{j}  H_{i,j}* r[j]

	The output of this function is ev[i]=Error(i) (defined as above)
      */

      vars=GetEquationVariables(ei->equation);
  
      NEW(r,ei->n,Tinterval);

      for(i=0;i<ei->n;i++)
	{
	  k=GetVariableN(i,vars);
	  IntervalOffset(&(is[k]),-c[k],&(r[i])); 
	}

      for(i=0;i<ei->n;i++)
	{
	  NewInterval(0,0,&error);
	  for(j=i;j<ei->n;j++)
	    { 
	      if (i==j)
		{
		  IntervalPow(&(r[i]),2,&a);
		  IntervalScale(&a,0.5,&a);
		}
	      else
		IntervalProduct(&(r[i]),&(r[j]),&a);
		  
	      EvaluateEquationInt(is,&h,ei->Hessian[i][j]);
	      IntervalOffset(&h,-GetEquationValue(ei->Hessian[i][j]),&h);
	  
	      IntervalProduct(&a,&h,&a);
	  
	      IntervalAdd(&error,&a,&error);
	    }
	  
	  ev[i]=IntervalSize(&error);
	}

      free(r);  
    }
}

void DeleteEquationInfo(TequationInfo *ei)
{
  unsigned int i,j;

  DeleteEquation(ei->equation);
  free(ei->equation);

  if (ei->EqType!=EMPTY_EQUATION)
    {
      if (ei->EqType==LINEAR_EQUATION)
	{
	  DeleteLinearConstraint(ei->lc);
	  free(ei->lc);
	}
      else
	{
	  for(i=0;i<ei->n;i++)
	    {
	      DeleteEquation(ei->Jacobian[i]);
	      free(ei->Jacobian[i]);
	    }
	  free(ei->Jacobian);
      
	  if (ei->Hessian!=NULL)
	    {
	      for(i=0;i<ei->n;i++)
		{
		  for(j=i;j<ei->n;j++)
		    {
		      DeleteEquation(ei->Hessian[i][j]);
		      free(ei->Hessian[i][j]);
		    }
		  free(ei->Hessian[i]);
		}
	      free(ei->Hessian);
	    }
	}
    }
}

/**********************************************************************************/
/**********************************************************************************/
/**********************************************************************************/

void InitEquations(Tequations *eqs)
{
  unsigned int i;

  eqs->neq=0; /* Total equations */

  eqs->s=0; /* System equation */
  eqs->c=0; /* Coordinate equations */
  eqs->d=0; /* Dummy equations */
  eqs->v=0; /* Velocity equations */
  eqs->nd=0;/* Non dynamic equations */
  
  eqs->e=0; /* Equality equations */

  eqs->polynomial=TRUE;
  eqs->scalar=TRUE;

  /* Scalar equations */
  eqs->n=0;
  eqs->m=INIT_NUM_EQUATIONS;
  NEW(eqs->equation,eqs->m,TequationInfo *);
  
  for(i=0;i<eqs->m;i++)
    eqs->equation[i]=NULL;

  /* Matrix equations */
  eqs->nm=0;
  eqs->mm=INIT_NUM_EQUATIONS;
  NEW(eqs->mequation,eqs->mm,TMequation *);
  
  for(i=0;i<eqs->mm;i++)
    eqs->mequation[i]=NULL;

  /* The cached information about non-empty EQU equations: initially empty. */
  eqs->nsEQU=0;
  eqs->eqEQU=NULL;
}

void CopyEquations(Tequations *eqs_dst,Tequations *eqs_src)
{
  unsigned int i;

  eqs_dst->neq=eqs_src->neq;

  eqs_dst->s=eqs_src->s;
  eqs_dst->c=eqs_src->c;
  eqs_dst->d=eqs_src->d;
  eqs_dst->v=eqs_src->v;
  eqs_dst->nd=eqs_src->nd;
  
  eqs_dst->e=eqs_src->e;

  eqs_dst->polynomial=eqs_src->polynomial;
  eqs_dst->scalar=eqs_src->scalar;

  eqs_dst->m=eqs_src->m;
  eqs_dst->n=eqs_src->n;
  NEW(eqs_dst->equation,eqs_dst->m,TequationInfo *);
  for(i=0;i<eqs_src->m;i++)
    {
      if (eqs_src->equation[i]!=NULL)
	{
	  NEW(eqs_dst->equation[i],1,TequationInfo);
	  CopyEquationInfo(eqs_dst->equation[i],eqs_src->equation[i]);
	}
      else
	eqs_dst->equation[i]=NULL;
    }

  /* copy matrix equations */
  eqs_dst->mm=eqs_src->mm;
  eqs_dst->nm=eqs_src->nm;
  NEW(eqs_dst->mequation,eqs_dst->mm,TMequation *);
  for(i=0;i<eqs_src->mm;i++)
    {
      if (eqs_src->mequation[i]!=NULL)
	{
	  NEW(eqs_dst->mequation[i],1,TMequation);
	  CopyMEquation(eqs_dst->mequation[i],eqs_src->mequation[i]);
	}
      else
	eqs_dst->mequation[i]=NULL;
    }
  
  /* The cached information is not copied */
  eqs_dst->nsEQU=0;
  eqs_dst->eqEQU=NULL;
}

void CopyNonDynamicEquations(Tequations *eqs_dst,Tequations *eqs_orig,Tequations *eqs_src)
{
  unsigned int i;
  boolean isDis;

  InitEquations(eqs_dst);

  for(i=0;i<eqs_src->m;i++)
    {
      if (eqs_src->equation[i]!=NULL)
	{
	  if (eqs_orig!=NULL)
	    isDis=IsNonDynamicEquation(i,eqs_orig);
	  else
	    isDis=IsNonDynamicEquation(i,eqs_src);
	  
	  if (isDis)
	    AddEquationNoSimp(GetOriginalEquation(eqs_src->equation[i]),eqs_dst);
	}
    }
  
  for(i=0;i<eqs_src->nm;i++)
    {
      if (eqs_orig!=NULL)
	isDis=(IsNonDynamicMEquation(eqs_orig->mequation[i]));
      else
	isDis=(IsNonDynamicMEquation(eqs_src->mequation[i]));
      if (isDis) 
	AddMatrixEquation(eqs_src->mequation[i],eqs_dst);
    }
}

void CopyPositionEquations(Tequations *eqs_dst,Tequations *eqs_orig,Tequations *eqs_src)
{
  unsigned int i;
  boolean isPos;

  InitEquations(eqs_dst);

  for(i=0;i<eqs_src->m;i++)
    {
      if (eqs_src->equation[i]!=NULL)
	{
	  if (eqs_orig!=NULL)
	    isPos=IsPositionEquation(i,eqs_orig);
	  else
	    isPos=IsPositionEquation(i,eqs_src);
	  
	  if (isPos)
	    AddEquationNoSimp(GetOriginalEquation(eqs_src->equation[i]),eqs_dst);
	}
    }

  /* Add position equation (dynamic equations which are not velocity equations) */
  for(i=0;i<eqs_src->nm;i++)
    {
      if (eqs_orig!=NULL)
	isPos=((!IsVelocityMEquation(eqs_orig->mequation[i]))&&
	       (!IsNonDynamicMEquation(eqs_orig->mequation[i])));
      else
	isPos=(!IsVelocityMEquation(eqs_src->mequation[i])&&
	       (!IsNonDynamicMEquation(eqs_src->mequation[i])));
      if (isPos) 
	AddMatrixEquation(eqs_src->mequation[i],eqs_dst);
    }
}

void MergeEquations(Tequations *eqs1,Tequations *eqs)
{
  unsigned int i;

  for(i=0;i<eqs1->m;i++)
    {
      if (eqs1->equation[i]!=NULL)
	AddEquation(GetOriginalEquation(eqs1->equation[i]),eqs);
    }
  /* merge matrix equations */
  for(i=0;i<eqs1->mm;i++)
    {
      if (eqs1->mequation[i]!=NULL)
	AddMatrixEquation(eqs1->mequation[i],eqs);
    }

  /* Remove the cached information, if any */
  eqs->nsEQU=0;
  if (eqs->eqEQU!=NULL)
    free(eqs->eqEQU);
}

void RewriteEqs2Orig(Tmapping *map,Tequations *eqs)
{
  unsigned int i;

  for(i=0;i<eqs->n;i++)
    {
      if (eqs->equation[i]!=NULL)	
	RewriteEquation2Orig(map,GetOriginalEquation(eqs->equation[i]));
    }
  
   for(i=0;i<eqs->nm;i++)
     {
      if (eqs->mequation[i]!=NULL)
	RewriteMEquation2Orig(map,eqs->mequation[i]);
     }
}

boolean UsedVarInNonDummyEquations(unsigned int nv,Tequations *eqs)
{
  Tequation *eq;
  boolean found;
  unsigned int i;

  found=FALSE;
  /* used in scalar dummy equations? */
  i=0;
  while((i<eqs->n)&&(!found))
    {
      eq=GetOriginalEquation(eqs->equation[i]);
      if (GetEquationType(eq)!=DUMMY_EQ)
	found=VarIncluded(nv,GetEquationVariables(eq));
      if (!found) i++;
    }
  /* used in matrix equations? (all non-dummy) */
  i=0;
  while((i<eqs->nm)&&(!found))
    {
      found=VarIncludedinMEquation(nv,eqs->mequation[i]);
      if (!found) i++;
    }
  
  return(found);
}

boolean UsedVarInEquations(unsigned int nv,Tequations *eqs)
{
  boolean found;
  unsigned int i;

  found=FALSE;
  /* used in scalar dummy equations? */
  i=0;
  while((i<eqs->n)&&(!found))
    {
      found=VarIncluded(nv,GetEquationVariables(GetOriginalEquation(eqs->equation[i])));
      if (!found) i++;
    }
  /* used in matrix equations? */
  i=0;
  while((i<eqs->nm)&&(!found))
    {
      found=VarIncludedinMEquation(nv,eqs->mequation[i]);
      if (!found) i++;
    }

  return(found);
}

void RemoveEquationsWithVar(double epsilon,unsigned int nv,Tequations *eqs)
{
  Tequation *eq;
  Tequations newEqs;
  unsigned int j,i;
  boolean found;

  /* can not remove variables if used in matrix or kino equations */
  found=FALSE;
  i=0;
  while((i<eqs->nm)&&(!found))
    {
      found=VarIncludedinMEquation(nv,eqs->mequation[i]);
      if (!found) i++;
    }
  if (found)
    Error("Removing a variable used in matrix equations");

  InitEquations(&newEqs);
  for(j=0;j<eqs->n;j++)
    {
      
      eq=GetOriginalEquation(eqs->equation[j]);
      if (!VarIncluded(nv,GetEquationVariables(eq)))
	{
	  /*The equations with the given variables are not included in the new set*/
	  /*The given variables is to be removed from the problem (it is not used
	    any more!). Removing a variable causes a shift in all the variable
	    indexes above the removed one. This effect can be easily simulated
	    by fixing the variable-to-be-removed for the equations to be kept in 
	    the new set. */
	  FixVariableInEquation(epsilon,nv,1,eq);
	  AddEquation(eq,&newEqs);
	}
    }

  /* adjust variable indices in matrix equations */
  for(i=0;i<eqs->nm;i++)
    {
      ShiftVariablesInMEquation(nv,eqs->mequation[i]);
      AddMatrixEquation(eqs->mequation[i],&newEqs);
    }

  DeleteEquations(eqs);
  CopyEquations(eqs,&newEqs); /* cached info empty in copy */
  DeleteEquations(&newEqs);
}

boolean ReplaceVariableInEquations(double epsilon,
				   unsigned int nv,TLinearConstraint *lc,
				   Tequations *eqs)
{
  boolean hold;
  unsigned int j,r;
  Tequations newEqs;
  Tequation *eqn;
  unsigned int nTerms,nvNew;
  Tinterval error;
  double ct;
  

  if ((!eqs->scalar)||(!eqs->polynomial))
    {
      /* Matrix or trigonometric equations allow limited replacements */
      
      nTerms=GetNumTermsInLinearConstraint(lc);
      if (nTerms>1)
	Error("Wrong variable replacement for matrix/kino/trigonometric equations in ReplaceVariableInEquations: can not use general replacements");
      if (nTerms==0)
	nvNew=NO_UINT; /* replace nv by a ct */
      else
	{
	  /* nvNew is the other variable in the 'lc' */
	  nvNew=GetLinearConstraintVariable(0,lc);  /* replace nv by a var */
	  if (nvNew==nv)
	    Error("Self-replacement in ReplaceVariableInEquations");
	}
      
      GetLinearConstraintError(&error,lc);
      if (IntervalSize(&error)>ZERO)
	Error("Wrong variable replacement for matrix/kino/trigonometric equations in ReplaceVariableInEquations: the replacement must be constant");
      ct=-IntervalCenter(&error);
      
      if ((nvNew!=NO_UINT)&&(fabs(ct)>ZERO))
	Error("Wrong variable replacement for matrix/kino/trigonometric equations in ReplaceVariableInEquations: replacement can not have offset");
    }
  
  hold=TRUE;
  InitEquations(&newEqs);

  for(j=0;((hold)&(j<eqs->nm));j++)
    {
      if (nvNew==NO_UINT)
	r=FixVarInMEquation(nv,ct,eqs->mequation[j]);
      else
	{
	  ReplaceVarInMEquation(nv,nvNew,eqs->mequation[j]);
	  r=0;
	}
      if (r==0) /* normal that holds -> include in the new set */
	AddMatrixEquation(eqs->mequation[j],&newEqs);
      else
	hold=(r==1); /* no need to add ct that holds. if not holds -> error */
    }
  
  for(j=0;((hold)&&(j<eqs->n));j++)
    {
      eqn=GetOriginalEquation(eqs->equation[j]);

      r=ReplaceVariableInEquation(epsilon,nv,lc,eqn);

      if (r==2)
	hold=FALSE; /*the equation became ct and does not hold -> the whole system fails*/
      else
	{
	  if (r==0)
	    AddEquation(eqn,&newEqs);

	  /*if r==1, a ct equation that holds -> no need to add it to the new set*/
	}
    }

  DeleteEquations(eqs);
  CopyEquations(eqs,&newEqs); /* cache information to empty */
  DeleteEquations(&newEqs);

  return(hold);
}

boolean GaussianElimination(Tequations *eqs)
{
  unsigned int i,j,jMin,nfi,neq,neqn,meq;
  Tequation *eqi;
  Tequations newEqs;
  boolean changes;
  Tequation *localMin; /* simplest equation when operation eqi with
		          the rest of equations */
  unsigned int nmMin,nvMin,nm,nv;

  /*We try to get the simplest possible set of equations
    Simple equation = as less number of monomials as possible*/

  changes=FALSE;

  neq=NScalarEquations(eqs); /* Only affects the scalar equations */
  InitEquations(&newEqs);
  #if (_DEBUG>5)
    printf("Gaussian process:\n");
  #endif
  for(i=0;i<neq;i++)
    {
      eqi=GetOriginalEquation(eqs->equation[i]);

      if ((GetEquationCmp(eqi)!=EQU)||
	  (GetEquationType(eqi)==DUMMY_EQ)||
	  (GetEquationType(eqi)==VELOCITY_EQ)||
	  (GetEquationType(eqi)==NON_DYNAMIC_EQ))
	AddEquation(eqi,&newEqs);
      else
	{
	  nfi=GetNumMonomials(eqi);

	  /* We try to simplify eqi linearly operating it with the
	     already simplified equations and the equations still to be
	     simplified. */
	  neqn=NScalarEquations(&newEqs); /* only scalar but...*/
	  meq=neqn+(neq-i-1); /* equations already processed and equations pending to be processed */

	  /* For large systems, Gaussian elimination is very time consuming. 
	     Try to parallelize it if possible  */
	  NEW(localMin,meq,Tequation);

	  /* See what is the best (i.e., the simplest equation) we can get operating 
	     equation 'i' with all other equations (the already 'simplified' and those
	     still to be simplified) */
	  #pragma omp parallel for private(j) schedule(dynamic)
	  for(j=0;j<meq;j++)
	    {
	      /* private variables for the thread */
	      unsigned int k;
	      Tequation *eqj;
	      Tmonomial *fi,*fj;
	      unsigned int r;
	      double ct;
	      Tequation eqNew;
	      unsigned int nmNew,nvNew,nmLocalMin,nvLocalMin;

	      /* Initialize the 'simplest' equation with eqi and see
	         if we can improve from this point */
	      CopyEquation(&(localMin[j]),eqi);
	      nmLocalMin=GetNumMonomials(&(localMin[j]));
	      nvLocalMin=GetEquationNumVariables(&(localMin[j]));
		
	      if (j<neqn)
		/* equations already simplified */
		eqj=GetOriginalEquation(newEqs.equation[j]);
	      else
		/* equations still to be processed (with index larger than 'i') */
		eqj=GetOriginalEquation(eqs->equation[i+1+(j-neqn)]);
		
	      if ((GetEquationCmp(eqj)==EQU)&&
		  (GetEquationType(eqj)!=DUMMY_EQ)&&
		  (GetEquationType(eqj)!=VELOCITY_EQ)&&
		  (GetEquationType(eqj)!=NON_DYNAMIC_EQ))
		{
		  /* eqi = alpha_k * m_k + ...
		     with m_k a 'monomial' we have eqj = beta_k + m_k
		     if eqj also includes m_k we perform the operation
		        eq = eqi - eqj * alpha_k/beta_k
		     This elimiates monomial (alpha_k * m_k) from eqi and
		     possibly produces a simple eqi (assuming that the
		     above operation do not introduces additional terms).
		   */
		  for(k=0;k<nfi;k++)
		    {
		      fi=GetMonomial(k,eqi);
		      r=FindMonomial(fi,eqj);

		      if (r!=NO_UINT) 
			{
			  /*If the monomial of eqi is also in eqj*/
			  fj=GetMonomial(r,eqj);
			  ct=-GetMonomialCt(fi)/GetMonomialCt(fj);

			  CopyEquation(&eqNew,eqi);
			  AccumulateEquations(eqj,ct,&eqNew);
			    
			  nmNew=GetNumMonomials(&eqNew);
			  nvNew=GetEquationNumVariables(&eqNew);
			  
			  /*If the equation after operation has less monomials than
			    the minimal equation we have up to now -> we have a new
			    minimal */
			    
			  if ((nmNew<nmLocalMin)||
			      ((nmNew==nmLocalMin)&&(nvNew<nvLocalMin)))
			    {
			      #if (_DEBUG>5)
			        printf("\n   Original eq: ");
				PrintEquation(stdout,NULL,eqi);
				printf("   Original ct: %f\n",ct);
				printf("   Accumulated eq: ");
				PrintEquation(stdout,NULL,eqj);
				printf("   Result: ");
				PrintEquation(stdout,NULL,&eqNew);
			      #endif

			      DeleteEquation(&(localMin[j]));
			      CopyEquation(&(localMin[j]),&eqNew);
			      nmLocalMin=nmNew;
			      nvLocalMin=nvNew;
			    }
			  DeleteEquation(&eqNew);
			}
		    }
		}
	    }
	  /* End of the parallel execution */

	  /* find the simplest equation among the equation in localMin */
	  nmMin=GetNumMonomials(eqi);
	  nvMin=GetEquationNumVariables(eqi);
	  jMin=NO_UINT; /* it can be the case that no option is better than
			   the original variable */
	  for(j=0;j<meq;j++)
	    {	
	      nm=GetNumMonomials(&(localMin[j]));
	      nv=GetEquationNumVariables(&(localMin[j]));
	      
	      if ((nm<nmMin)||
		  ((nm==nmMin)&&(nv<nvMin)))
		{
		  jMin=j;
		  nmMin=nm;
		  nvMin=nv;
		}
	    }
	  if (jMin!=NO_UINT)
	    {
	      /* We managed to simplify equation 'i' */
	      AddEquation(&(localMin[jMin]),&newEqs);
	      changes=TRUE;
	    }
	  else
	    AddEquation(eqi,&newEqs);
	  
	  /* Release memory */
	  #pragma omp parallel for private(j) schedule(dynamic)
	  for(j=0;j<meq;j++)
	    DeleteEquation(&(localMin[j]));
	  free(localMin);
	}
    }
    
  /* The matrix equations are directly copied to the new set */
  for(i=0;i<eqs->nm;i++)
    AddMatrixEquation(eqs->mequation[i],&newEqs);
  
  /* Delete the previous set and keep the new one */
  DeleteEquations(eqs);
  CopyEquations(eqs,&newEqs); /* cache information reseted */
  DeleteEquations(&newEqs);

  return(changes);
}

unsigned int NEquations(Tequations *eqs)
{
  return(eqs->neq);
}

unsigned int NScalarEquations(Tequations *eqs)
{
  return(eqs->n);
}

unsigned int NSystemEquations(Tequations *eqs)
{
  return(eqs->s);
}

unsigned int NCoordEquations(Tequations *eqs)
{
  return(eqs->c);
}

unsigned int NDummyEquations(Tequations *eqs)
{
  return(eqs->d);
}

unsigned int NPositionEquations(Tequations *eqs)
{
  return(eqs->neq-eqs->v-eqs->nd);
}

unsigned int NVelocityEquations(Tequations *eqs)
{
  return(eqs->v);
}

unsigned int NNonDynamicEquations(Tequations *eqs)
{
  return(eqs->nd);
}

unsigned int NEqualityEquations(Tequations *eqs)
{
  return(eqs->e);
}

unsigned int NEqualityPositionEquations(Tequations *eqs)
{
  unsigned int i,n;

  n=0;
  for(i=0;i<eqs->neq;i++)
    {
      if ((IsPositionEquation(i,eqs))&&
	  (IsEqualityEquation(i,eqs)))
	n++;
    }
  return(n);
}

unsigned int NEqualityScalarPositionEquations(Tequations *eqs)
{
  unsigned int i,n;
  Tequation *eq;

  n=0;
  for(i=0;i<eqs->n;i++)
    {
      eq=GetOriginalEquation(eqs->equation[i]);
      if ((IsPositionEquation(i,eqs))&&
	  (GetEquationCmp(eq)==EQU))
	n++;
    }
  return(n);
}

unsigned int NInequalityEquations(Tequations *eqs)
{
  return(eqs->neq-eqs->e);
}

unsigned int NMatrixEquations(Tequations *eqs)
{
  return(eqs->nm);
}

boolean PolynomialEquations(Tequations *eqs)
{
  return(eqs->polynomial);
}

boolean ScalarEquations(Tequations *eqs)
{
  return(eqs->scalar);
}

boolean IsEqualityEquation(unsigned int i,Tequations *eqs)
{
  boolean isEquality;
  
  if (i>=eqs->neq)
    Error("Index out of range in IsEqualityEquation");

  if (i<eqs->n)
    {
      Tequation *eq;
      
      eq=GetOriginalEquation(eqs->equation[i]);
      isEquality=(GetEquationCmp(eq)==EQU);
    }
  else
    isEquality=TRUE; /* al matrix equations are equality equations */

  return(isEquality);
}

boolean IsSystemEquation(unsigned int i,Tequations *eqs)
{
  boolean isSystem;
  
  if (i>=eqs->neq)
    Error("Index out of range in IsSystemEquation");

  if (i<eqs->n)
    isSystem=(GetEquationType(GetOriginalEquation(eqs->equation[i]))==SYSTEM_EQ);
  else
    {
      unsigned int j,k,l;
      boolean found;
      
      k=eqs->n;
      j=0;
      found=FALSE;
      while((!found)&&(j<eqs->nm)&&(k<eqs->neq))
	{
	  l=NumberScalarEquations(eqs->mequation[j]);
	  if (i<k+l)
	    {
	      found=TRUE;
	      isSystem=(!IsVelocityMEquation(eqs->mequation[j]));
	    }
	  else
	    {
	      j++;
	      k+=l;
	    }
	}
      if (!found)
	Error("Index out of range in IsSystemEquation"); 
    }
  
  return(isSystem);
}

boolean IsCoordEquation(unsigned int i,Tequations *eqs)
{
  if (i>=eqs->neq)
    Error("Index out of range in IsCoordEquation");

  return((i<eqs->n)&&
	 (GetEquationType(GetOriginalEquation(eqs->equation[i]))==COORD_EQ));
}

boolean IsDummyEquation(unsigned int i,Tequations *eqs)
{
  if (i>=eqs->neq)
    Error("Index out of range in IsDummyEquation");

  return((i<eqs->n)&&
	 (GetEquationType(GetOriginalEquation(eqs->equation[i]))==DUMMY_EQ));
}

boolean IsPositionEquation(unsigned int i,Tequations *eqs)
{
  return((!IsVelocityEquation(i,eqs))&&(!IsNonDynamicEquation(i,eqs)));
}

boolean IsVelocityEquation(unsigned int i,Tequations *eqs)
{
  boolean isVelocity;
  
  if (i>=eqs->neq)
    Error("Index out of range in IsVelocityEquation");

  if (i<eqs->n)
    isVelocity=(GetEquationType(GetOriginalEquation(eqs->equation[i]))==VELOCITY_EQ);
  else
    {
      unsigned int j,k,l;
      boolean found;
      
      k=eqs->n;
      j=0;
      found=FALSE;
      while((!found)&&(j<eqs->nm)&&(k<eqs->neq))
	{
	  l=NumberScalarEquations(eqs->mequation[j]);
	  if (i<k+l)
	    {
	      found=TRUE;
	      isVelocity=IsVelocityMEquation(eqs->mequation[j]);
	    }
	  else
	    {
	      j++;
	      k+=l;
	    }
	}
      if (!found)
	Error("Index out of range in IsVelocityEquation");
    }
  
  return(isVelocity);
}

boolean IsNonDynamicEquation(unsigned int i,Tequations *eqs)
{
  if (i>=eqs->neq)
    Error("Index out of range in IsNonDynamicEquation");

  return((i<eqs->n)&&
	 (GetEquationType(GetOriginalEquation(eqs->equation[i]))==NON_DYNAMIC_EQ));
}


unsigned int GetEquationTypeN(unsigned int i,Tequations *eqs)
{
  if (i>=eqs->neq)
    Error("Index out of range in GetEquationTypeN");

  if (eqs->equation[i]==NULL)
    return(NOTYPE_EQ);
  else
    {
      if (i<eqs->n)
	return(GetEquationType(GetOriginalEquation(eqs->equation[i])));
      else
	{
	  unsigned int t,j,k,l;
	  boolean found;
      
	  k=eqs->n;
	  j=0;
	  found=FALSE;
	  while((!found)&&(j<eqs->nm)&&(k<eqs->neq))
	    {
	      l=NumberScalarEquations(eqs->mequation[j]);
	      if (i<k+l)
		{
		  found=TRUE;
		  if (IsVelocityMEquation(eqs->mequation[j]))
		    t=VELOCITY_EQ;
		  else
		    t=SYSTEM_EQ;
		}
	      else
		{
		  j++;
		  k+=l;
		}
	    }
	  if (!found)
	    Error("Index out of range in GetEquationTypeN");
	  
	  return(t);
	}
    }
}

boolean HasEquation(Tequation *equation,Tequations *eqs)
{
  boolean found;
  unsigned int i;
  
  i=0;
  found=FALSE;
  while((i<eqs->n)&&(!found))
    {
      found=(CmpEquations(equation,GetOriginalEquation(eqs->equation[i]))==0);
      if (!found) i++;
    }
  return(found);
}

unsigned int CropEquation(unsigned int ne,
			  unsigned int varType,
			  double epsilon,double rho,
			  Tbox *b,
			  Tvariables *vs,
			  Tequations *eqs)
{
  unsigned int status;
  TequationInfo *ei;
  unsigned int cmp;
  Tequation *eq;
  Tvariable_set *vars;
  
  double val,alpha,beta;
  Tvariable_set *varsf;;
  Tinterval x_new,y_new,z_new;
  unsigned int nx,ny,nz; 
  unsigned int m,i,j,k;
  Tinterval *is,bounds,range;
  Tbox bNew;
  Tinterval *isNew;
  boolean reduced;
  double l,u,c;
  unsigned int full;

  if (ne>=eqs->neq)
    Error("Index out of range in CropEquation");

  if (ne>=eqs->n)
    Error("CropEquation can only be used with scalar equations");

  ei=eqs->equation[ne];

  eq=GetOriginalEquation(ei);

  status=NOT_REDUCED_BOX;

  cmp=GetEquationCmp(eq);
  val=GetEquationValue(eq);
  m=GetBoxNIntervals(b);
  is=GetBoxIntervals(b);
  vars=GetEquationVariables(eq);

  #if (_DEBUG>6)
    printf("\n       Croping Equation: %u\n",ne);
  #endif

  /* Trivial consistancy check: Interval evaluation must hold */
  EvaluateEquationInt(is,&range,eq);
  GetEquationBounds(&bounds,eq);
  
  #if (_DEBUG>6)
    printf("         Whole box test:\n");
    printf("           Left vs Right hand side: ");
    PrintInterval(stdout,&range);
    printf("  ");
    PrintInterval(stdout,&bounds);
    printf("\n");
  #endif
  if (!Intersect(&bounds,&range))
    {
      status=EMPTY_BOX;
      #if (_DEBUG>6)
        printf("             No intersection -> Empty box.\n");
      #endif
    }
  /* Stronger cuts based on  EvaluateEquationInt could be implemented.
     Iterate considering only half of the interval for each variable (first
     the lower part, then the upper one) to check is any half can be
     trivially discarded. Repeat while there is any reduction. 
     All this is done without bisection -> avoid branching. This
     technique to avoid branching can be used also at higher levels. */
  if (status!=EMPTY_BOX)
    {
      #if (_DEBUG>6)
        printf("         Half range tests:\n");
      #endif
      CopyBox(&bNew,b);  
      isNew=GetBoxIntervals(&bNew);
      reduced=FALSE; /* eventually */
      do {
	status=NOT_REDUCED_BOX; /* at this loop, so far */ 
	for(i=0;((status!=EMPTY_BOX)&&(i<ei->n));i++)
	  {
	    k=GetVariableN(i,vars);
	    l=LowerLimit(&(isNew[k]));
	    u=UpperLimit(&(isNew[k]));
	    c=IntervalCenter(&(isNew[k]));
	    #if (_DEBUG>6)
	      printf("         Variable %u/%u -> [%f %f %f] s:%g  e:%g \n",k,ei->n,l,c,u,u-l,epsilon);
	    #endif
	    /* If the range is not too tiny */
	    if (((c-l)>=epsilon)&&((u-c)>=epsilon))
	      {
		full=0; /* binary flags to detect which of the halves is full */
		for(j=0;j<2;j++)
		  {
		    if (j==0)
		      NewInterval(l,c,&(isNew[k])); /* lower half */
		    else
		      NewInterval(c,u,&(isNew[k])); /* upper half */
		    #if (_DEBUG>6)
		      printf("           Considering range - [%f %f] (%u %u)\n",LowerLimit(&(isNew[k])),UpperLimit(&(isNew[k])),full,status);
		    #endif
		    EvaluateEquationInt(isNew,&range,eq); 
		    if (Intersect(&bounds,&range))
		      {
			full|=(1<<j);
			#if (_DEBUG>6)
			  printf("             Range is full (%u %u)\n",full,status);
			#endif
		      }
		    #if (_DEBUG>6)
		    else
		      printf("             Range is empty (%u %u)\n",full,status);
		    #endif
		  }
		#if (_DEBUG>6)
		  printf("           Full flag %u (%u)\n",full,status);
		#endif
		switch(full)
		  {
		  case 3:
		    /* keep both halves (restore original interval) */
		    NewInterval(l,u,&(isNew[k]));
		    break;
		  case 2:
		    /* keep upper half */ 
		    NewInterval(c,u,&(isNew[k]));
		    status=REDUCED_BOX;
		    reduced=TRUE;
		    break;
		  case 1:
		    /* keep lower half */ 
		    NewInterval(l,c,&(isNew[k]));
		    status=REDUCED_BOX;
		    reduced=TRUE;
		    break;
		  case 0:
		    /* keep no half */
		    status=EMPTY_BOX;
		    break;
		  }
	      }
	  }
      } while (status==REDUCED_BOX);
      if (reduced)
	{
	  for(i=0;i<m;i++)
	    CopyInterval(&(is[i]),&(isNew[i]));
	}
      DeleteBox(&bNew);
    }

  /* If the box is not already empty ->  crop using the linear approximation (or special functions). */
  if ((status==NOT_REDUCED_BOX)&&(cmp==EQU))
    {
      #if (_DEBUG>6)
        printf("         Eq: ");
	PrintEquation(stdout,NULL,eq);
	printf("         Input ranges: ");
	for(i=0;i<ei->n;i++)
	  {
	    k=GetVariableN(i,vars);
	    printf(" v[%u]=",k);PrintInterval(stdout,&(is[k]));printf(":%g  ",IntervalSize(&(is[k])));
	  }
	printf("\n");
      #endif

	    
      /* Special equations cropped with special functions that get tighter bounds
	 (they use non-linear functions) */
      switch(ei->EqType)
	{
	case LINEAR_EQUATION:
	  status=CropLinearConstraint(epsilon,varType,b,vs,ei->lc);
	  break;

	case PARABOLA_EQUATION:
	  /* x^2 + \alpha y = \beta */
	  nx=GetVariableN(0,GetMonomialVariables(GetMonomial(0,eq)));
	  ny=GetVariableN(0,GetMonomialVariables(GetMonomial(1,eq)));
	  alpha=GetMonomialCt(GetMonomial(1,eq));
	  beta=GetEquationValue(eq);

	  if (((IntervalSize(&(is[nx]))>=epsilon)||
	       (IntervalSize(&(is[ny]))>=epsilon))&&
	      (IntervalSize(&(is[nx]))<INF))
	    {
	      if (RectangleParabolaClipping(&(is[nx]),alpha,beta,&(is[ny]),&x_new,&y_new))
		{ 
		  status=REDUCED_BOX;

		  if (GetVariableTypeN(nx,vs)&varType)
		    CopyInterval(&(is[nx]),&x_new);

		  if (GetVariableTypeN(ny,vs)&varType)
		    CopyInterval(&(is[ny]),&y_new);
		}
	      else
		status=EMPTY_BOX;
	    }
	  break;

	case SADDLE_EQUATION:
	  /* x*y + \alpha z = \beta */
	  varsf=GetMonomialVariables(GetMonomial(0,eq));
	  alpha=GetMonomialCt(GetMonomial(1,eq));
	  beta=GetEquationValue(eq);

	  nx=GetVariableN(0,varsf);
	  ny=GetVariableN(1,varsf);
	  nz=GetVariableN(0,GetMonomialVariables(GetMonomial(1,eq)));
      
	  if (((IntervalSize(&(is[nx]))>=epsilon)||
	       (IntervalSize(&(is[ny]))>=epsilon)||
	       (IntervalSize(&(is[nz]))>=epsilon))&&
	      (IntervalSize(&(is[nx]))<INF)&&
	      (IntervalSize(&(is[ny]))<INF))
	    {
	      if (BoxSaddleClipping(&(is[nx]),&(is[ny]),alpha,beta,&(is[nz]),
				    &x_new,&y_new,&z_new))
		{ 
		  status=REDUCED_BOX;

		  if (GetVariableTypeN(nx,vs)&varType)
		    CopyInterval(&(is[nx]),&x_new);

		  if (GetVariableTypeN(ny,vs)&varType)
		    CopyInterval(&(is[ny]),&y_new);

		  if (GetVariableTypeN(nz,vs)&varType)
		    CopyInterval(&(is[nz]),&z_new);
		}
	      else
		status=EMPTY_BOX;
	    }
	  break;

	case BILINEAL_MONOMIAL_EQUATION:
	  /* xy=\beta is transformed to xy + \alpha z= \beta with z=[0,0]*/
	  nx=GetVariableN(0,vars);
	  ny=GetVariableN(1,vars);

	  if (((IntervalSize(&(is[nx]))>=epsilon)||
	       (IntervalSize(&(is[ny]))>=epsilon))&&
	      (IntervalSize(&(is[nx]))<INF)&&
	      (IntervalSize(&(is[ny]))<INF))
	    {
	      Tinterval r;

	      NewInterval(-ZERO,+ZERO,&r);

	      if (BoxSaddleClipping(&(is[nx]),&(is[ny]),1.0,val,&r,
				    &x_new,&y_new,&z_new))
		{
		  status=REDUCED_BOX;

		  if (GetVariableTypeN(nx,vs)&varType)
		    CopyInterval(&(is[nx]),&x_new);

		  if (GetVariableTypeN(ny,vs)&varType)
		    CopyInterval(&(is[ny]),&y_new);
		}
	      else
		status=EMPTY_BOX;
	    }
	  break;

	case CIRCLE_EQUATION:
	  /* x^2 + y^2 = val */
	  nx=GetVariableN(0,vars);
	  ny=GetVariableN(1,vars);

	  if ((IntervalSize(&(is[nx]))>=epsilon)||
	      (IntervalSize(&(is[ny]))>=epsilon))
	    {
	      if (RectangleCircleClipping(val,
					  &(is[nx]),&(is[ny]),
					  &x_new,&y_new))
		{ 
		  status=REDUCED_BOX;

		  if (GetVariableTypeN(nx,vs)&varType)
		    CopyInterval(&(is[nx]),&x_new);

		  if (GetVariableTypeN(ny,vs)&varType)
		    CopyInterval(&(is[ny]),&y_new);
		}
	      else
		status=EMPTY_BOX;
	    }
	  break;

	case SPHERE_EQUATION:
	  /* x^2 + y^2 + z^2 = val */
	  nx=GetVariableN(0,vars);
	  ny=GetVariableN(1,vars);
	  nz=GetVariableN(2,vars);
      
	  if ((IntervalSize(&(is[nx]))>=epsilon)||
	      (IntervalSize(&(is[ny]))>=epsilon)||
	      (IntervalSize(&(is[nz]))>=epsilon))
	    {
	      if (BoxSphereClipping(val,
				    &(is[nx]),&(is[ny]),&(is[nz]),
				    &x_new,&y_new,&z_new))
		{ 
		  status=REDUCED_BOX;

		  if (GetVariableTypeN(nx,vs)&varType)
		    CopyInterval(&(is[nx]),&x_new);

		  if (GetVariableTypeN(ny,vs)&varType)
		    CopyInterval(&(is[ny]),&y_new);

		  if (GetVariableTypeN(nz,vs)&varType)
		  CopyInterval(&(is[nz]),&z_new);
		}
	      else
		status=EMPTY_BOX;
	    }
	  break;

	case GENERAL_EQUATION:
	  /* When simplifying systems it is quite common to introduce equations
	     of type x^2=ct or x*y=ct. We treat them as special cases and taking into
	     accound the non-linealities -> stronger crop
	     Here we treat the case x^2=ct.
	     The case x*y=ct is treated as a BILINEAL_MONOMIAL_EQUATION above
	     (We differentiate this type of equations because they require not only
	     a different crop but also a different linalization).
	  */
	  if ((PolynomialEquation(eq))&&
	      (GetNumMonomials(eq)==1)&&
	      (GetMonomialCt(GetMonomial(0,eq))==1))
	    {
	      Tinterval r;
	      
	      if (VariableSetSize(vars)==1) /*only one variable in the equation*/
		{
		  /* Only one variable included in the equation-> x^2=ct
		     (the linal case x=ct is treated above (LINEAL_EQUATION) */
		  /* ax^2=ct is transformed to x^2+y=ct with y=[0,0] */
		  nx=GetVariableN(0,vars);

		  if ((IntervalSize(&(is[nx]))>=epsilon)&&
		      (IntervalSize(&(is[nx]))<INF)&&
		      (GetVariableTypeN(nx,vs)&varType))
		    {
		      NewInterval(-ZERO,+ZERO,&r);

		      if (RectangleParabolaClipping(&(is[nx]),1.0,val,&r,&x_new,&y_new))
			{ 
			  status=REDUCED_BOX;
			  CopyInterval(&(is[nx]),&x_new);
			}
		      else
			status=EMPTY_BOX;
		    }
		}
	      else
		Error("Three variables in a single monomial?");
	    }
	  else
	    {
	      double *c; /*central point*/
	      TLinearConstraint lc;

	      NEW(c,m,double); 

	      do {
		/*possible improvement -> use a random point inside the ranges
		  this will cut increase the crop */
		for(i=0;i<ei->n;i++)
		  {
		    k=GetVariableN(i,vars);
		    c[k]=IntervalCenter(&(is[k]));
		  }

		GetFirstOrderApproximationToEquation(b,c,&lc,ei);

		GetLinearConstraintError(&bounds,&lc);
		SimplexExpandBounds(cmp,&bounds);
		SetLinearConstraintError(&bounds,&lc);		

		status=CropLinearConstraint(epsilon,varType,b,vs,&lc);

		DeleteLinearConstraint(&lc);
	     
	      } while(status==REDUCED_BOX);

	      free(c);
	    }
	  break; 

	default:
	  Error("Unknown equation type in CropEquation");
	}
    }
  #if (_DEBUG>6)
  else
    {
      if (cmp!=EQU)
	printf("           Inequalities are not cropped\n");
    }
  if (status!=EMPTY_BOX)
    {
      printf("         Output ranges: ");
      for(i=0;i<ei->n;i++)
	{
	  k=GetVariableN(i,vars);
	  printf(" v[%u]=",k);PrintInterval(stdout,&(is[k]));printf("  ");
	}
      printf("\n         ");
    }
  #endif     
 
  return(status);
}

void AddEquationInt(Tequation *equation,Tequations *eqs)
{
  unsigned int t;

  if (eqs->n==eqs->m)
    {
      unsigned int i,k;

      k=eqs->m;
      MEM_DUP(eqs->equation,eqs->m,TequationInfo *);
      for(i=k;i<eqs->m;i++)
	eqs->equation[i]=NULL;
    }

  NEW(eqs->equation[eqs->n],1,TequationInfo);
  SetEquationInfo(equation,eqs->equation[eqs->n]);

  t=GetEquationType(equation);
  if (t==SYSTEM_EQ) eqs->s++;
  if (t==COORD_EQ) eqs->c++;
  if (t==DUMMY_EQ) eqs->d++;
  if (t==VELOCITY_EQ) eqs->v++;
  if (t==NON_DYNAMIC_EQ) eqs->nd++;
  
  if (GetEquationCmp(equation)==EQU) eqs->e++;
  eqs->polynomial=((eqs->polynomial)&&(PolynomialEquation(equation)));

  eqs->n++;
  eqs->neq++;

  /* Remove the cached information, if any */
  eqs->nsEQU=0;
  if (eqs->eqEQU!=NULL)
    free(eqs->eqEQU);
}

void AddEquation(Tequation *equation,Tequations *eqs)
{
  if ((GetEquationType(equation)==NOTYPE_EQ)||(GetEquationCmp(equation)==NOCMP))
    Error("Adding an equation with unknown type of cmp");

  NormalizeEquation(equation);

  if ((GetNumMonomials(equation)>0)&&(!HasEquation(equation,eqs)))
    {
      int j;
      TequationInfo *s;

      AddEquationInt(equation,eqs);

      j=eqs->n-1;
      while((j>0)&&(CmpEquations(GetOriginalEquation(eqs->equation[j-1]),
				 GetOriginalEquation(eqs->equation[j]))==1))
	{
	  s=eqs->equation[j-1];
	  eqs->equation[j-1]=eqs->equation[j];
	  eqs->equation[j]=s;

	  j--;
	}
    }
}

void AddEquationNoSimp(Tequation *equation,Tequations *eqs)
{
  if ((GetEquationType(equation)==NOTYPE_EQ)||(GetEquationCmp(equation)==NOCMP))
    Error("Adding an equation with unknown type of cmp");

  AddEquationInt(equation,eqs);
}


void AddMatrixEquation(TMequation *equation,Tequations *eqs)
{
  unsigned int k;

  eqs->scalar=FALSE;
  if (HasRotations(equation))
    eqs->polynomial=FALSE;

  if (eqs->nm==eqs->mm)
    {
      unsigned int i;

      k=eqs->mm;
      MEM_DUP(eqs->mequation,eqs->mm,TMequation*);
      for(i=k;i<eqs->mm;i++)
	eqs->mequation[i]=NULL;
    }
  NEW(eqs->mequation[eqs->nm],1,TMequation);
  CopyMEquation(eqs->mequation[eqs->nm],equation);
  eqs->nm++;

  k=NumberScalarEquations(equation);
  eqs->neq+=k;
  if (IsVelocityMEquation(equation))
    eqs->v+=k;
  else
    {
      if (IsNonDynamicMEquation(equation))
	eqs->nd+=k;
      else
	eqs->s+=k;
    }
  eqs->e+=k;

  /* Remove the cached information, if any */
  eqs->nsEQU=0;
  if (eqs->eqEQU!=NULL)
    free(eqs->eqEQU);
}

Tequation *GetEquation(unsigned int n,Tequations *eqs)
{
  if (!eqs->scalar)
    Error("GetEquation can only be used with scalar equations");

  return(GetScalarEquation(n,eqs));
}

Tequation *GetScalarEquation(unsigned int n,Tequations *eqs)
{
  if (n<eqs->n)
    return(GetOriginalEquation(eqs->equation[n]));
  else
    return(NULL);
}

TMequation *GetMatrixEquation(unsigned int n,Tequations *eqs)
{
  if (n<eqs->nm)
    return(eqs->mequation[n]);
  else
    return(NULL);
}

boolean LinearizeSaddleEquation(double epsilon,unsigned int safeSimplex,Tbox *b,
				TSimplex *lp,TequationInfo *ei)
{ 
  Tvariable_set *varsf;
  unsigned int nx,ny,nz;
  double x_min,x_max;
  double y_min,y_max;
  double *c;
  boolean full;
  Tequation *eq;
  Tinterval *is;
  unsigned int m;

  m=GetBoxNIntervals(b);
  is=GetBoxIntervals(b);
  eq=GetOriginalEquation(ei);

  /* x*y + \alpha z = \beta  where \alpha can be zero. 
     In this case the z variable is not used. */
  varsf=GetMonomialVariables(GetMonomial(0,eq));
  
  nx=GetVariableN(0,varsf);
  ny=GetVariableN(1,varsf);
  nz=GetVariableN(0,GetMonomialVariables(GetMonomial(1,eq)));

  x_min=LowerLimit(&(is[nx]));
  x_max=UpperLimit(&(is[nx]));

  y_min=LowerLimit(&(is[ny]));
  y_max=UpperLimit(&(is[ny]));
  
  if ((x_min<-epsilon)&&(x_max>epsilon))
    {
      double px[4]={x_min,x_min,x_max,x_max};
      double py[4]={y_min,y_max,y_min,y_max};
      unsigned int cmp[4]={LEQ,GEQ,GEQ,LEQ};
    
      unsigned int i; 
    
      NEW(c,m,double);

      full=TRUE;
      for(i=0;((full)&&(i<4));i++)
	{
	  c[nx]=px[i];
	  c[ny]=py[i];
	  c[nz]=0; /*This is actually not used in any case*/
	  
	  full=LinearizeGeneralEquationInt(cmp[i],epsilon,safeSimplex,b,c,lp,ei);
	}
      free(c);
    }
  else
    full=LinearizeGeneralEquation(epsilon,safeSimplex,b,lp,ei);
  
  return(full);
}

boolean LinearizeBilinealMonomialEquation(double epsilon,double lr2tm,
					  unsigned int safeSimplex,Tbox *b,
					  TSimplex *lp,TequationInfo *ei)
{ 
  Tvariable_set *varsf;
  unsigned int nx,ny;
  double x_min,x_max;
  double y_min,y_max;
  double *c;
  boolean full;
  Tequation *eq;
  Tinterval *is;
  unsigned int m;
  double val;

  m=GetBoxNIntervals(b);
  is=GetBoxIntervals(b);
  eq=GetOriginalEquation(ei);
 
  /* x*y = \beta */
  varsf=GetMonomialVariables(GetMonomial(0,eq));
  
  nx=GetVariableN(0,varsf);
  ny=GetVariableN(1,varsf);

  x_min=LowerLimit(&(is[nx]));
  x_max=UpperLimit(&(is[nx]));

  y_min=LowerLimit(&(is[ny]));
  y_max=UpperLimit(&(is[ny]));
  
  val=GetEquationValue(eq);
  if (fabs(val)<epsilon)
    {
      /* x*y=0 -> a constraint for each corner*/
      double px[4]={x_min,x_min,x_max,x_max};
      double py[4]={y_min,y_max,y_min,y_max};
      unsigned int cmp[4]={LEQ,GEQ,GEQ,LEQ};

      unsigned int i; 
    
      NEW(c,m,double);

      full=TRUE;
      for(i=0;((full)&&(i<4));i++)
	{
	  /* Only consider corners outside the curbe */ 
	  if (fabs(px[i]*py[i]-val)>epsilon)
	    {
	      c[nx]=px[i];
	      c[ny]=py[i];

	      full=LinearizeGeneralEquationInt(cmp[i],epsilon,safeSimplex,b,c,lp,ei);
	    }
	}
      free(c);
    }
  else
    {
      if (0) //(((x_max-x_min)<lr2tm)&&((y_max-y_min)<lr2tm))
	/* A small box in both dimensions */
	full=LinearizeGeneralEquation(epsilon,safeSimplex,b,lp,ei);
      else
	{
	  /* x*y=beta beta!=0  -> one constraint for each corner*/
	  /* we add epsilon to avoid numerical issues if the box intersects
	     the curbe in one corner */
	  double px[4]={x_min-epsilon,x_min-epsilon,x_max+epsilon,x_max+epsilon};
	  double py[4]={y_min-epsilon,y_max+epsilon,y_min-epsilon,y_max+epsilon};
	  unsigned int cmp[4]={LEQ,GEQ,GEQ,LEQ};

	  unsigned int i; 
    
	  NEW(c,m,double);

	  full=TRUE;
	  for(i=0;((full)&&(i<4));i++)
	    {
	      /* Only consider corners outside the curbe */ 
	      if (fabs(px[i]*py[i]-val)>epsilon)
		{
		  c[nx]=px[i];
		  c[ny]=py[i];

		  full=LinearizeGeneralEquationInt(cmp[i],epsilon,safeSimplex,b,c,lp,ei);
		}
	    }
	  
	  if ((x_max<0)||(x_min>0))
	    {
	      /* if the box is at one side of the Y axis -> one additional constraint
	         tangent to the curbe */ 
	      c[nx]=(x_max<0?-1.0:1.0)*sqrt(x_max*x_min);
	      c[ny]=val/c[nx];

	      full=LinearizeGeneralEquationInt((val>0?GEQ:LEQ),epsilon,safeSimplex,b,c,lp,ei);
	    }
	  free(c);
	}
	
    }

  return(full);
}

boolean LinearizeParabolaEquation(double epsilon,unsigned int safeSimplex,
				  Tbox *b,
				  TSimplex *lp,TequationInfo *ei)
{
  unsigned int nx,ny;
  double x_min,x_max,x_c;
  double *c;
  boolean full;
  Tequation *eq;
  Tinterval *is;
  unsigned int m;

  m=GetBoxNIntervals(b);
  is=GetBoxIntervals(b);
  eq=GetOriginalEquation(ei);

  /* x^2 + \alpha y = \beta  */
  nx=GetVariableN(0,GetMonomialVariables(GetMonomial(0,eq)));
  ny=GetVariableN(0,GetMonomialVariables(GetMonomial(1,eq)));

  x_min=LowerLimit(&(is[nx]));
  x_max=UpperLimit(&(is[nx]));
  x_c=IntervalCenter(&(is[nx]));

  NEW(c,m,double); 
  
  {
    double px[3]={x_c,x_min,x_max};
    unsigned int cmp[3]={EQU,LEQ,LEQ};
    unsigned int i;

    full=TRUE;
    for(i=0;((full)&&(i<3));i++)
      {
	c[nx]=px[i];
	c[ny]=0;  /*The value of 'y' is not used in the linealization*/
	
	full=LinearizeGeneralEquationInt(cmp[i],epsilon,safeSimplex,b,c,lp,ei);
      }
  }

  free(c);

  return(full);
}

boolean LinearizeCircleEquation(double epsilon,
				unsigned int safeSimplex,
				Tbox *b,
				TSimplex *lp,TequationInfo *ei)
{
  Tequation *eq;
  Tvariable_set *vars;
  unsigned int nx,ny;
  double x_min,x_max,x_c;
  double y_min,y_max,y_c;
  double *c;
  double r2; 
  /*At most 5 linearization points are selected (one
    for each box corner and one from the center of the
    interval x,y)*/
  double cx[5];
  double cy[5];
  unsigned int cmp[5];
  unsigned int i,nc; 
  boolean full;
  Tinterval *is;
  unsigned int m;
  unsigned int cmpEq;

  m=GetBoxNIntervals(b);
  is=GetBoxIntervals(b);
  eq=GetOriginalEquation(ei);
  cmpEq=GetEquationCmp(eq);

  vars=GetEquationVariables(eq);

  r2=GetEquationValue(eq);

  nx=GetVariableN(0,vars);
  ny=GetVariableN(1,vars);

  x_min=LowerLimit(&(is[nx]));
  x_max=UpperLimit(&(is[nx]));
  x_c=IntervalCenter(&(is[nx]));

  y_min=LowerLimit(&(is[ny]));
  y_max=UpperLimit(&(is[ny]));
  y_c=IntervalCenter(&(is[ny]));

  NEW(c,m,double); /* space for the linealization point */
  
  /* for large input ranges (both in x and y) we add linealization constraints
     from the corners of the box*/
  nc=0;
  if (cmpEq!=GEQ)
    {
      /* Check which of the 4 box corners are out of the circle.
	 For the external points we add a linealization point
	 selected on the circle: intersection of the circle and a 
	 line from the origin to the corner (a normalization of
	 point (x,y) to norm sqrt(r2))
      */
      double px[4]={x_min,x_min,x_max,x_max};
      double py[4]={y_min,y_max,y_min,y_max};
      double norm;
    
      for(i=0;i<4;i++)
	{
	  ROUNDDOWN;
	  norm=px[i]*px[i]+py[i]*py[i];
	  ROUNDNEAR;
	  if (norm>(r2+epsilon)) /*corner (clearly) out of the circle*/
	    {
	      norm=sqrt(r2/norm);
	      cx[nc]=px[i]*norm;
	      cy[nc]=py[i]*norm; 
	      cmp[nc]=LEQ;
	      nc++;
	    }
	}
    }
  
  /* A point selected from the center of x range is added always
     'y' is selected so that it is on the circle, if possible.
     If not, y is just the center of the y range
  */
  cx[nc]=x_c;
  cy[nc]=y_c;
  cmp[nc]=cmpEq;
  nc++;

  full=TRUE;
  for(i=0;((full)&&(i<nc));i++)
    {
      c[nx]=cx[i];
      c[ny]=cy[i];

      full=LinearizeGeneralEquationInt(cmp[i],epsilon,safeSimplex,b,c,lp,ei);
    }

  free(c);

  return(full);
}

boolean LinearizeSphereEquation(double epsilon,unsigned int safeSimplex,
				Tbox *b,
				TSimplex *lp,TequationInfo *ei)
{
  Tequation *eq;
  Tvariable_set *vars;
  unsigned int nx,ny,nz;
  double x_min,x_max,x_c;
  double y_min,y_max,y_c;
  double z_min,z_max,z_c;
  double *c;
  double r2; 
  /*At most 9 linearization points are selected (one
    for each box corner and one from the center of the
    interval x,y,z)*/
  double cx[9];
  double cy[9];
  double cz[9];
  unsigned int cmp[9];
  unsigned int i,nc; 
  boolean full;
  Tinterval *is;
  unsigned int m;
  unsigned int cmpEq;

  m=GetBoxNIntervals(b);
  is=GetBoxIntervals(b);
  eq=GetOriginalEquation(ei);
  cmpEq=GetEquationCmp(eq);

  vars=GetEquationVariables(eq);

  r2=GetEquationValue(eq);

  nx=GetVariableN(0,vars);
  ny=GetVariableN(1,vars);
  nz=GetVariableN(2,vars);

  x_min=LowerLimit(&(is[nx]));
  x_max=UpperLimit(&(is[nx]));
  x_c=IntervalCenter(&(is[nx]));

  y_min=LowerLimit(&(is[ny]));
  y_max=UpperLimit(&(is[ny]));
  y_c=IntervalCenter(&(is[ny]));

  z_min=LowerLimit(&(is[nz]));
  z_max=UpperLimit(&(is[nz]));
  z_c=IntervalCenter(&(is[nz]));

  NEW(c,m,double); /* space for the linealization point */
  
  /* for large input ranges (both in x and y) we add linealization constraints
     from the corners of the box*/
  nc=0;
  if (cmpEq!=GEQ)
  {
    /* Check which of the 8 box corners are out of the sphere.
       For the external points we add a linealization point
       selected on the sphere: intersection of the sphere and a 
       line from the origin to the corner (a normalization of
       point (x,y,z) to norm sqrt(r2))
    */
    double px[8]={x_min,x_min,x_min,x_min,x_max,x_max,x_max,x_max};
    double py[8]={y_min,y_min,y_max,y_max,y_min,y_min,y_max,y_max};
    double pz[8]={z_min,z_max,z_min,z_max,z_min,z_max,z_min,z_max};
    double norm;
    
    for(i=0;i<8;i++)
      {
	ROUNDDOWN;
	norm=px[i]*px[i]+py[i]*py[i]+pz[i]*pz[i];
	ROUNDNEAR;
	if (norm>(r2+epsilon)) /*corner (clearly) out of the sphere*/
	  {
	    norm=sqrt(r2/norm);
	    cx[nc]=px[i]*norm;
	    cy[nc]=py[i]*norm;
	    cz[nc]=pz[i]*norm; 
	    cmp[nc]=LEQ;
	    nc++;
	  }
      }
  }
  
  /* A point selected from the center of x range is added always
     'y' is selected so that it is on the circle, if possible.
     If not, y is just eh center of the y range
  */
  cx[nc]=x_c;
  cy[nc]=y_c;
  cz[nc]=z_c; 
  cmp[nc]=cmpEq;
  nc++;

  full=TRUE;
  for(i=0;((full)&&(i<nc));i++)
    {
      c[nx]=cx[i];
      c[ny]=cy[i];
      c[nz]=cz[i];

      full=LinearizeGeneralEquationInt(cmp[i],epsilon,safeSimplex,b,c,lp,ei);
    }

  free(c);

  return(full);
}

boolean LinearizeGeneralEquationInt(unsigned int cmp,
				    double epsilon,
				    unsigned int safeSimplex,
				    Tbox *b,double *c,
				    TSimplex *lp,TequationInfo *ei)
{  
  Tvariable_set *vars;
  TLinearConstraint lc;
  boolean full=TRUE;

  vars=GetEquationVariables(GetOriginalEquation(ei));

  if (GetBoxMaxSizeVarSet(vars,b)<INF)
    {
      GetFirstOrderApproximationToEquation(b,c,&lc,ei);

      full=SimplexAddNewConstraint(epsilon,safeSimplex,&lc,cmp,GetBoxIntervals(b),lp);

      DeleteLinearConstraint(&lc);
    }

  return(full);
}

boolean LinearizeGeneralEquation(double epsilon,
				 unsigned int safeSimplex,
				 Tbox *b,
				 TSimplex *lp,TequationInfo *ei)
{
  Tequation *eq;
  unsigned int i,k;
  Tvariable_set *vars;
  double *c;
  boolean full;
  Tinterval *is;
  unsigned int m;

  m=GetBoxNIntervals(b);
  is=GetBoxIntervals(b);

  eq=GetOriginalEquation(ei);

  vars=GetEquationVariables(eq);

  NEW(c,m,double); 
  for(i=0;i<ei->n;i++)
    {
      k=GetVariableN(i,vars);
      c[k]=IntervalCenter(&(is[k]));
    }

  full=LinearizeGeneralEquationInt(GetEquationCmp(eq),epsilon,safeSimplex,b,c,lp,ei);

  free(c);

  return(full);
}

boolean AddEquation2Simplex(unsigned int ne, /*eq identifier*/
			    double lr2tm_q,double lr2tm_s,
			    double epsilon,
			    unsigned int safeSimplex,
			    double rho,
			    Tbox *b,
			    Tvariables *vs,
			    TSimplex *lp,
			    Tequations *eqs)
{
  boolean full;

  full=TRUE;

  if (!eqs->scalar)
    Error("AddEquation2Simplex can only be used with scalar equations");

  if (ne<eqs->n)/* No equation -> nothing done */
    {
      TequationInfo *ei;
      Tequation *eq;
      Tinterval r;
      double val;
      double s;
      boolean ctEq;

      ei=eqs->equation[ne];
      eq=GetOriginalEquation(ei);

      #if (_DEBUG>4)
        printf("     Adding equation %u of type %u to the simplex \n",ne,ei->EqType);
	printf("       ");
	PrintEquation(stdout,NULL,eq);
      #endif

      #if (_DEBUG>4)
	printf("     Cropping equation\n");
      #endif

      if (CropEquation(ne,ANY_TYPE_VAR,epsilon,rho,b,vs,eqs)==EMPTY_BOX)
	{
	  #if ((!_USE_MPI)&&(_DEBUG>1))
	    fprintf(stderr,"C");
	  #endif
	  full=FALSE;
	}
      else
	{
	  /*There is no need to add constant equations to the simplex.
	    Thus, we evaluate the equations and if the result is almost
	    constant we just check if the equation holds or not.
	    If not, the system has no solution.
	    The same applies to inequalities that already hold
	  */

	  EvaluateEquationInt(GetBoxIntervals(b),&r,eq);
	  val=GetEquationValue(eq);
	  IntervalOffset(&r,-val,&r);
      
	  #if (_DEBUG>4)
	    printf("     Defining constraints for equation\n");
	    printf("          EvalIntEq (offset=%f): ",val);
	    PrintInterval(stdout,&r);
	    if (IntervalSize(&r)<INF)
	      printf(" -> %g\n",IntervalSize(&r));
	    else
	      printf(" -> +inf\n");
	  #endif

	  ctEq=FALSE;

	  switch(GetEquationCmp(eq))
	    {
	    case EQU:
	      if ((safeSimplex>1)&&(IntervalSize(&r)<=(10*epsilon)))
		{
		  /* We have an (almost) constant equation -> just check whether
		     it holds or not but do not add it to the simplex */
		  /* We allow for some numerical inestabilities: numerical values
		     below epsilon are converted to zero when defining the linear
		     constraints and, consequently, we have to admit epsilon-like
		     errors
		  */
		  ctEq=TRUE;
		  full=((IsInside(0.0,0.0,&r))||
			(fabs(LowerLimit(&r))<10*epsilon)||
			(fabs(UpperLimit(&r))<10*epsilon));

		}
	      break;

	    case LEQ:
	      if (UpperLimit(&r)<0.0)
		{
		  ctEq=TRUE;
		  full=TRUE;
		}
	      else
		{
		  if (LowerLimit(&r)>0.0)
		    {
		      ctEq=TRUE;
		      full=FALSE;
		    }
		}
	      break;
	    case GEQ:
	      if (UpperLimit(&r)<0.0)
		{
		  ctEq=TRUE;
		  full=FALSE;
		}
	      else
		{
		  if (LowerLimit(&r)>0.0)
		    {
		      ctEq=TRUE;
		      full=TRUE;
		    }
		}
	      break;
	    }
	  
	  #if (_DEBUG>4)
	    if (ctEq)
	      {
		printf("     Constant Equation\n");
		printf("       Eq eval:[%g %g] -> ",LowerLimit(&r),UpperLimit(&r));
		if (full) 
		  printf("ct full equation\n\n");
		else
		  printf("ct empty equation\n\n");
	      }
	  #endif

	  if (!ctEq)
	    {
	      Tequation eqClean;
	      boolean changed;

	      /* The equation is not constant, we proceed to add it into
		 the simplex tableau, linearizing if needed.*/

	      #if (_DEBUG>4)
	        printf("     Cleaning equation of inf \n");
	      #endif
	      if (CleanInfEquation(eq,GetBoxIntervals(b),&changed,&eqClean))
		{
		  TequationInfo *eiClean;
		  
		  if (changed)
		    {
		      #if (_DEBUG>4)
		        printf("       The equation changed when cleaning inf \n");
			printf("         New equation:");
			PrintEquation(stdout,NULL,&eqClean);
		      #endif
		      NEW(eiClean,1,TequationInfo);
		      SetEquationInfo(&eqClean,eiClean);
		      s=GetBoxMinSizeVarSet(GetEquationVariables(&eqClean),b);
		    }
		  else
		    {
		      #if (_DEBUG>4)
		        printf("       The equation remain the same when cleaning inf \n");
		      #endif
		      eiClean=ei;
		      s=GetBoxMinSizeVarSet(GetEquationVariables(eq),b);
		    }

		  /* Use a particular linear relaxation depending on the
		     equation type */
		  switch (ei->EqType)
		    {
		    case LINEAR_EQUATION:
		      full=SimplexAddNewConstraint(epsilon,
						   safeSimplex,
						   ei->lc,
						   GetEquationCmp(eq),
						   GetBoxIntervals(b),lp);
		      break;
		  
		    case SADDLE_EQUATION:
		      if (s<lr2tm_s)
			full=LinearizeGeneralEquation(epsilon,safeSimplex,b,lp,eiClean);
		      else
			full=LinearizeSaddleEquation(epsilon,safeSimplex,b,lp,eiClean);
		      break;

		    case BILINEAL_MONOMIAL_EQUATION:
		      full=LinearizeBilinealMonomialEquation(epsilon,lr2tm_s,safeSimplex,b,lp,eiClean);
		      break;

		    case PARABOLA_EQUATION:
		      if (s<lr2tm_q)
			full=LinearizeGeneralEquation(epsilon,safeSimplex,b,lp,eiClean);
		      else
			full=LinearizeParabolaEquation(epsilon,safeSimplex,b,lp,eiClean);
		      break;
		  
		    case CIRCLE_EQUATION:
		      /* This is de-activated since it was just a test and not very successful */
                      #if (0) // (_SIMPLEX_ENGINE==_GUROBI)
		      {
			unsigned int x,y;
			double ct;

			/* Add a non-linear constraint to the problem. Does not
			   help much. Slows down the optimization and reduces
			   accuracy (safe_simplex has to be set to 0). */
			x=GetVariableN(0,GetEquationVariables(&eqClean));
			y=GetVariableN(1,GetEquationVariables(&eqClean));
			ct=GetEquationValue(&eqClean);

			SimplexAddCircle(x,y,ct,lp);
		      }
		      #endif
		      if (s<lr2tm_q)
			full=LinearizeGeneralEquation(epsilon,safeSimplex,b,lp,eiClean);
		      else
			full=LinearizeCircleEquation(epsilon,safeSimplex,b,lp,eiClean);
		      break;
		      
		    case SPHERE_EQUATION:
		      if (s<lr2tm_q)
			full=LinearizeGeneralEquation(epsilon,safeSimplex,b,lp,eiClean);
		      else
			full=LinearizeSphereEquation(epsilon,safeSimplex,b,lp,eiClean);
		      break;
		  
		    case GENERAL_EQUATION:
		      full=LinearizeGeneralEquation(epsilon,safeSimplex,b,lp,eiClean);
		      break;
		  
		    default:
		      Error("Unknown equation type in AddEquation2Simplex");
		    }
		  
		  if (changed)
		    {
		      DeleteEquationInfo(eiClean);
		      free(eiClean);
		    }
		}
	      #if (_DEBUG>4)
	      else
		printf("       Useless equation after cleaning inf\n");
	      #endif

	      DeleteEquation(&eqClean);
	    } 
	  #if ((!_USE_MPI)&&(_DEBUG>1))
	    if (!full)
	      fprintf(stderr,"A");
	  #endif     
	}
    }

  return(full);
}

void UpdateSplitWeight(unsigned int ne,double *splitDim,
		       Tbox *b,Tequations *eqs)
{
  unsigned int i,k;
  TequationInfo *ei;
  Tvariable_set *vars;
  double *c,*ev;
  Tinterval *is;
  unsigned int m;

  if (!eqs->scalar)
    Error("UpdateSplitWeight can only be used with scalar equations");

  if (ne<eqs->n)
    {
      m=GetBoxNIntervals(b);
      is=GetBoxIntervals(b);

      ei=eqs->equation[ne];
 
      if (ei->EqType!=LINEAR_EQUATION)
	{
	  vars=GetEquationVariables(ei->equation);

	  NEW(c,m,double);
	  NEW(ev,m,double); 

	  for(i=0;i<ei->n;i++)
	    {
	      k=GetVariableN(i,vars);
	      c[k]=IntervalCenter(&(is[k]));
	    }

	  ErrorDueToVariable(m,c,is,ev,ei);

	  for(i=0;i<ei->n;i++)
	    {
	      k=GetVariableN(i,vars);
	      splitDim[k]+=ev[i];
	    }

	  free(c);
	  free(ev);
	}
    }
}

void VarScaleEqualityEquations(unsigned int nv,boolean velocity,Tequations *eqs)
{
  unsigned int i,t,k;
  Tequation *eq;
  
  for(i=0;i<eqs->n;i++)
    {
      eq=GetOriginalEquation(eqs->equation[i]);
      if (GetEquationCmp(eq)==EQU)
	{
	  VarScaleEquation(nv,eq);
	  t=GetEquationType(eq);
	  if ((velocity)&&(t!=VELOCITY_EQ))
	    {
	      if (t==SYSTEM_EQ) eqs->s--;
	      if (t==COORD_EQ) eqs->c--;
	      if (t==DUMMY_EQ) eqs->d--;
	      if (t==NON_DYNAMIC_EQ) eqs->nd--;
	      eqs->v++;
	      SetEquationType(VELOCITY_EQ,eq);
	    }
	}
      else
	Error("Applying VarScaleEqualityEquations to a system with inequalities");
    }
  for(i=0;i<eqs->nm;i++)
    {
      ScaleMEquation(nv,eqs->mequation[i]);
      if ((velocity)&&(!IsVelocityMEquation(eqs->mequation[i])))
	{
	  k=NumberScalarEquations(eqs->mequation[i]);
	  if (IsNonDynamicMEquation(eqs->mequation[i]))
	    eqs->nd-=k;
	  else
	    eqs->s-=k;
	  eqs->v+=k;
	  MarkAsVelocityMEquation(eqs->mequation[i]);
	}
    }
}

void VarAccumulateEqualityEquations(unsigned int nv,boolean velocity,
				    Tequations *eqs1,Tequations *eqs)
{
  unsigned int i;
  Tequation *eq,*eq1;

  if ((eqs1->n!=eqs->n)||(eqs1->nm!=eqs->nm))
    Error("Accumulating non-equivalent equation sets (1)");
  
  for(i=0;i<eqs->n;i++)
    {
      eq=GetOriginalEquation(eqs->equation[i]);
      eq1=GetOriginalEquation(eqs1->equation[i]);
      if (GetEquationCmp(eq)==EQU)
	{
	  if ((GetEquationCmp(eq1)!=EQU)||
	      ((!velocity)&&(GetEquationType(eq)!=GetEquationType(eq1))))
	    {
	      fprintf(stderr,"t: %u %u  eq: %u %u\n",GetEquationType(eq),GetEquationType(eq1),GetEquationCmp(eq),GetEquationCmp(eq1));
	      Error("Accumulating non-equivalent equation sets (2)");
	    }
	  VarAccumulateEquations(eq1,nv,eq);
	  if (velocity)
	    SetEquationType(VELOCITY_EQ,eq);
	}
      else
	Error("Applying VarAccumulateEqualityEquations to a system with inequalities");
    }
  for(i=0;i<eqs->nm;i++)
    {
      AccumulateMEquations(nv,eqs1->mequation[i],eqs->mequation[i]);
      if (velocity)
	MarkAsVelocityMEquation(eqs->mequation[i]);
    }
}

void EvaluateEqualityEquations(boolean systemOnly,double *v,double *r,Tequations *eqs)
{
  unsigned int i,k,l;
  Tequation *eq;

  k=0;
  for(i=0;i<eqs->n;i++)
    {
      eq=GetOriginalEquation(eqs->equation[i]);
	
      if (GetEquationCmp(eq)==EQU)
	{
	  if ((!systemOnly)||(GetEquationType(eq)==SYSTEM_EQ))
	    r[k]=EvaluateWholeEquation(v,eq);
	  else
	    r[k]=0.0;
	  k++;
	}
    }

  /* Evaluate the matrix equations (they are all equalities). */
  for(i=0;i<eqs->nm;i++)
    {
      l=EvaluateMEquation(v,&(r[k]),eqs->mequation[i]);
      k+=l;
    }
}

void EvaluateSubSetEqualityEquations(double *v,boolean *se,double *r,Tequations *eqs)
{
  unsigned int i,j,k,l,s;
  Tequation *eq;
  double mv[MAX_EQ_MATRIX];

  k=0;
  s=0;
  for(i=0;i<eqs->n;i++)
    {
      eq=GetOriginalEquation(eqs->equation[i]);
      if (GetEquationCmp(eq)==EQU)
	{
	  if ((se==NULL)||(se[s]))
	    {
	      r[k]=EvaluateWholeEquation(v,eq);
	      k++;
	    }
	  s++;
	}
    }
  /* all matrix equations are equalities */
  for(i=0;i<eqs->nm;i++)
    {
      l=EvaluateMEquation(v,mv,eqs->mequation[i]);
      for(j=0;j<l;j++,s++)
	{
	  if ((se==NULL)||(se[s]))
	    {
	      r[k]=mv[j];
	      k++;
	    }
	}
    }
}

unsigned int EvaluatePositionScalarEqs(double *v,boolean *se,double *r,Tequations *eqs)
{
  unsigned int i,k,s;
  Tequation *eq;

  k=0;
  s=0;
  for(i=0;i<eqs->n;i++)
    {
      eq=GetOriginalEquation(eqs->equation[i]);
      if (IsPositionEquation(i,eqs)&&
	  (GetEquationCmp(eq)==EQU))
	{
	  if ((se==NULL)||(se[s]))
	    {
	      r[k]=EvaluateWholeEquation(v,eq);
	      k++;
	    }
	  s++;
	}
    }
  
  return(k);
}

void CacheScalarEQUInfo(Tequations *eqs)
{
  /* we have to be sure that this is not executed
     in parallel over the same eqs structure.
     Only need to be executed once (typically at
     the system initialization). */
  #pragma omp critical
  {
    if ((eqs->nsEQU==0)&&(eqs->n>0))
      {
	unsigned int i;
	Tequation *eq;

	/* We have at most 'n' equality scalar equations */
	NEW(eqs->eqEQU,eqs->n,Tequation*);
	for(i=0;i<eqs->n;i++)
	  {
	    eq=GetOriginalEquation(eqs->equation[i]);
	
	    if (GetEquationCmp(eq)==EQU)
	      {
		if (EmptyEquation(eq))
		  eqs->eqEQU[eqs->nsEQU]=NULL;
		else
		  eqs->eqEQU[eqs->nsEQU]=eq;
		eqs->nsEQU++;
	      }
	  }
      }
  }
}

void EvaluateEqualitySparseEquations(double *v,double *r,Tequations *eqs)
{
  Tequation **eq;
  unsigned int i,k,l;

  /* The cache information is requiered */
  if ((eqs->nsEQU==0)&&(eqs->n>0))
    Error("User CacheScalarEQUInfo before calling EvaluateEqualitySparseEquations");
  
  /* Fast evaluation of the empty equations */
  eq=&(eqs->eqEQU[0]);
  for(k=0;k<eqs->nsEQU;k++,eq++)
    r[k]=(*eq?EvaluateWholeEquation(v,*eq):0.0);

  /* Evaluate the matrix equations (they are all equalities). */
  k=eqs->nsEQU;
  for(i=0;i<eqs->nm;i++)
    {
      l=EvaluateMEquation(v,&(r[k]),eqs->mequation[i]);
      k+=l;
    }
}

void EvaluateSubSetEqualitySparseEquations(double *v,boolean *se,double *r,Tequations *eqs)
{
  Tequation **eq;
  unsigned int i,j,l,k,s;
  double mv[MAX_EQ_MATRIX];

  /* Cache the information (without taking into account 'se') */
  if ((eqs->nsEQU==0)&&(eqs->n>0))
    Error("User CacheScalarEQUInfo before calling EvaluateSubSetEqualitySparseEquations");
 
  /* Evaluate the selected scalar equality equations */
  k=0;
  eq=&(eqs->eqEQU[0]);
  for(i=0;i<eqs->nsEQU;i++,eq++)
    {
      if ((se==NULL)||(se[i]))
	{
	  r[k]=(*eq?EvaluateWholeEquation(v,*eq):0.0);
	  k++;
	}
    }

  /* Evaluate the matrix equations (they are all equalities). */
  s=eqs->nsEQU;
  for(i=0;i<eqs->nm;i++)
    {
      l=EvaluateMEquation(v,mv,eqs->mequation[i]);
      for(j=0;j<l;j++,s++)
	{
	  if ((se==NULL)||(se[s]))
	    {
	      r[k]=mv[j];
	      k++;
	    }
	}
    }
}

void EvaluateEquationsXVectors(double *v,unsigned int ng,unsigned int *g,double *p,
			       double *r,Tequations *eqs)
{
  unsigned int i,s;
  
  if (eqs->n>0)
    Error("EvaluateEquationsXVectors can only be used on matrix-only equations");
  
  if (eqs->nm!=ng)
    Error("Num vectors-Equations missmatch in EvaluateEquationsXVectors");

  s=0;
  for(i=0;i<eqs->nm;i++)
    {
      EvaluateMEquationXVectors(v,g[i],&(p[3*s]),&(r[3*s]),eqs->mequation[i]);
      s+=g[i];
    }
}

void EvaluateInequalityEquations(double *v,double *r,Tequations *eqs)
{
  unsigned int i,k;
  Tequation *eq;
  double e,rhs;
  unsigned int cmp;

  k=0;
  for(i=0;i<eqs->n;i++)
    {
      eq=GetOriginalEquation(eqs->equation[i]);
      cmp=GetEquationCmp(eq);
      if (cmp!=EQU)
	{
	  e=EvaluateEquation(v,eq);
	  rhs=GetEquationValue(eq);
	  if (cmp==GEQ)
	    r[k]=(e>=rhs?0.0:rhs-e);
	  else
	    r[k]=(e<=rhs?0.0:e-rhs);
	  k++;
	}
    }
}

void DeriveEqualityScalarPositionEquations(unsigned int v,Tequations *deqs,Tequations *eqs)
{
  unsigned int i;
  Tequation *eq;
  Tequation deq;

  InitEquations(deqs);
  for(i=0;i<eqs->n;i++)
    { 
      eq=GetOriginalEquation(eqs->equation[i]);
      if ((IsPositionEquation(i,eqs))&&
	  (GetEquationCmp(eq)==EQU))
	{
	  DeriveEquation(v,&deq,eq);
	  AddEquationInt(&deq,deqs); /* Adding even if empty */
	  DeleteEquation(&deq);
	}
    }
}

void DeriveEqualityPositionEquations(unsigned int v,Tequations *deqs,Tequations *eqs)
{
  unsigned int i;
  Tequation *eq;
  Tequation deq;
  TMequation dmeq;

  InitEquations(deqs);
  for(i=0;i<eqs->n;i++)
    {
      eq=GetOriginalEquation(eqs->equation[i]);
      if ((IsPositionEquation(i,eqs))&&
	  (GetEquationCmp(eq)==EQU))
	{
	  DeriveEquation(v,&deq,eq);
	  AddEquationInt(&deq,deqs); /* Adding even if empty */
	  DeleteEquation(&deq);
	}
    }
  for(i=0;i<eqs->nm;i++)
    {
      if (IsPositionMEquation(eqs->mequation[i]))
	{
	  DeriveMEquation(v,&dmeq,eqs->mequation[i]);
	  AddMatrixEquation(&dmeq,deqs);
	  DeleteMEquation(&dmeq);
	}
    }
}

void DeriveEqualityEquations(unsigned int v,Tequations *deqs,Tequations *eqs)
{
  unsigned int i;
  Tequation *eq;
  Tequation deq;
  TMequation dmeq;

  InitEquations(deqs);
  for(i=0;i<eqs->n;i++)
    {
      eq=GetOriginalEquation(eqs->equation[i]);
      if (GetEquationCmp(eq)==EQU)
	{
	  DeriveEquation(v,&deq,eq);
	  AddEquationInt(&deq,deqs); /* Adding even if empty */
	  DeleteEquation(&deq);
	}
    }
  for(i=0;i<eqs->nm;i++)
    {
      DeriveMEquation(v,&dmeq,eqs->mequation[i]);
      AddMatrixEquation(&dmeq,deqs);
      DeleteMEquation(&dmeq);
    }
}

void PrintEquations(FILE *f,char **varNames,Tequations *eqs)
{
  unsigned int i;
  
  if (eqs->s>0)
    {
      fprintf(f,"\n[SYSTEM EQS]\n");
      for(i=0;i<eqs->n;i++)
	{
	  if (IsSystemEquation(i,eqs))
	    {
	      //fprintf(f,"%% %u\n",i);
	      PrintEquation(f,varNames,GetOriginalEquation(eqs->equation[i]));
	    }
	}

      /* Matrix equations can be system equations */
      if ((eqs->nm>0)&&(eqs->n>0))
	fprintf(f,"\n\n");
      
      for(i=0;i<eqs->nm;i++)
	{
	  if ((!IsVelocityMEquation(eqs->mequation[i]))&&
	      (!IsNonDynamicMEquation(eqs->mequation[i])))
	    PrintMEquation(f,NULL,varNames,eqs->mequation[i]);
	}
    }

  if (eqs->c>0)
    {
      fprintf(f,"\n[COORD EQS]\n");
      for(i=0;i<eqs->n;i++)
	{
	  if (IsCoordEquation(i,eqs))
	    {
	      //fprintf(f,"%% %u\n",i);
	      PrintEquation(f,varNames,GetOriginalEquation(eqs->equation[i]));
	    }
	}
    }

  if (eqs->d>0)
    {
      fprintf(f,"\n[DUMMY EQS]\n");
      for(i=0;i<eqs->n;i++)
	{
	  if (IsDummyEquation(i,eqs))
	    {
	      //fprintf(f,"%% %u\n",i);
	      PrintEquation(f,varNames,GetOriginalEquation(eqs->equation[i]));
	    }
	}
    }
  
  if (eqs->nd>0)
    {
      fprintf(f,"\n[NON DYNAMIC EQS]\n");
      for(i=0;i<eqs->n;i++)
	{
	  if (IsNonDynamicEquation(i,eqs))
	    {
	      //fprintf(f,"%% %u\n",i);
	      PrintEquation(f,varNames,GetOriginalEquation(eqs->equation[i]));
	    }
	}

      /* Matrix equations can be system equations */
      if ((eqs->nm>0)&&(eqs->n>0))
	fprintf(f,"\n\n");
      
      for(i=0;i<eqs->nm;i++)
	{
	  if (IsNonDynamicMEquation(eqs->mequation[i]))
	    PrintMEquation(f,NULL,varNames,eqs->mequation[i]);
	}
    }
    
  if (eqs->v>0)
    {
      fprintf(f,"\n[VELOCITY EQS]\n");
      for(i=0;i<eqs->n;i++)
	{
	  if (IsVelocityEquation(i,eqs))
	    {
	      //fprintf(f,"%% %u\n",i);
	      PrintEquation(f,varNames,GetOriginalEquation(eqs->equation[i]));
	    }
	}
      /* Matrix equations can be velocity equations */
      if ((eqs->nm>0)&&(eqs->n>0))
	fprintf(f,"\n\n");
      
      for(i=0;i<eqs->nm;i++)
	{
	  if (IsVelocityMEquation(eqs->mequation[i]))
	    {
	      //fprintf(f,"%% %u\n",i);
	      PrintMEquation(f,NULL,varNames,eqs->mequation[i]);
	    }
	}
    }
  
  // Scalar equations with unknown type (derived or type not set) generate an error
  for(i=0;i<eqs->n;i++)
    {
      if ((!IsSystemEquation(i,eqs))&&
	  (!IsCoordEquation(i,eqs))&&
	  (!IsDummyEquation(i,eqs))&&
	  (!IsVelocityEquation(i,eqs))&&
	  (!IsNonDynamicEquation(i,eqs)))
	{
	  Error("Equation with unkonwn type in PrintEquations");
	  //fprintf(f,"%% %u\n",i);
	  //PrintEquation(f,varNames,GetOriginalEquation(eqs->equation[i]));
	}
    }
}

void DeleteEquations(Tequations *eqs)
{
  unsigned int i;

  for(i=0;i<eqs->n;i++)
    { 	 
      if (eqs->equation[i]!=NULL)
	{
	  DeleteEquationInfo(eqs->equation[i]);
	  free(eqs->equation[i]);
	}
    }
  free(eqs->equation);

  for(i=0;i<eqs->nm;i++)
    { 	 
      if (eqs->mequation[i]!=NULL)
	{
	  DeleteMEquation(eqs->mequation[i]);
	  free(eqs->mequation[i]);
	}
    }
  free(eqs->mequation);
  
  /* Remove the cached information, if any */
  eqs->nsEQU=0;
  if (eqs->eqEQU!=NULL)
    free(eqs->eqEQU);
}
