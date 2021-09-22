#include "cuiksystem.h"

#include "error.h"
#include "boolean.h"
#include "defines.h"
#include "box_list.h"
#include "box_heap.h"
#include "simplex.h"
#include "random.h"
#include "filename.h"
#include "algebra.h"

#include <stdlib.h>

#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>
#if (_USE_MPI)
  #include <mpi.h>
  #include <sys/resource.h>
  #include <time.h>
  #include <unistd.h>
#endif



/** \file cuiksystem.c
    \brief Implementation of the functions operating on TCuikSystem.

    Implementation of the functions operating on TCuikSystem.

    \sa TCuikSystem, cuiksystem.h.
*/


/* Internal functions */

/** 
    \brief Adds an equation to the cuiksystem.

    Adds an equation to the cuiksystem taking into account the dummification
    level selected by the user when fixing the parameters. In the extreme
    dummification level, all quadratic and bilinear terms in the equations are
    replaced by a new (dummy) variable and the corresponding equation parabola
    or saddle equation is added to the system. In the other extreme (i.e., not
    to dummify anything) equations are added as given by the user to the system.
    <br>
    In any case, adding an equation with a degree higher than 2 produdes an error.

    \param p The set of parameters.
    \param eq The equation to add.
    \param cs The cuiksystem where to add the equation.
*/
void DummifyAndAddEquation(Tparameters *p,Tequation *eq,TCuikSystem *cs);

/** 
    \brief Apply the selected dummification level to a cuiksystem.

    Dummify all equations in the cuiksystem according to the parameters given
    by the user. 

    \param p The set of parameters.
    \param cs The cuiksystem where to add the equation.

    \sa DummifyAndAddEquation
*/
void DummifyCuikSystem(Tparameters *p,TCuikSystem *cs);


/** 
   \brief Evaluates the equation to minimize in a given box.

   Evaluates the equation to minimize when the search mode is set
   to \ref MINIMIZATION_SEARCH. In any other search mode the output
   is 0.
   
   Note that the input box is a box in the simplified system since,
   for efficiency, the equation to minimize is re-written into this 
   system too.
   
   \param b The box.
   \param cs The TCuikSystem structure storing the equation to
             use when evaluating

   \return The value of the equation to minimize in the given box.
*/
double EvaluateEqMin(void *b,void *cs);

/** 
    \brief Reduces a box considering one equation at a time.

    Reduces the ranges of a box considering one equation at a time. Linear equations
    are cropped directly and non-linear equations are linearized. Special treatement
    is implement for parabola, circle, sphere, and saddle equations since they appear
    frequently and the non-linear cropping is stronger than the one obtained via
    linearization.
    <br>
    Note that considering only one equation at a time we only obtaion local consistancy.

    \param p The set of parameters.
    \param b The box to be reduced.
    \param cs The cuiksystem with the equations to use.
    
    \return The status of the box after the reduction (EMPTY_BOX, REDUCED_BOX)

    \sa ReduceRange
*/
unsigned int ReduceBoxEquationWise(Tparameters *p,Tbox *b,TCuikSystem *cs);

/** 
    \brief Reduces a box as much as possible.

    Reduces the ranges of a box as much as possible applying first an equation-wise
    crop and then a simplex-based reduction. If the reduction is significative (i.e.,
    the reduction ratio is above paramter RHO) and the box is not smaller than SMALL_SIGMA,
    the reduction process is iterated.
    <br>
    Observe that SMALL_SIGMA can be much smaller that SIGMA (the parameter to accept a box
    as a solution). The idea here is that if a box contains a punctual solution it will
    be shrink till it has a size below SMALL_SIGMA and, if the box bounds a patch of
    a continuous solution set, the box will not be smaller more than SIGMA.<br>
    If the reduced box is fully included in the original box, then we can certify that
    the box has a solution.

    \param p The set of parameters.
    \param varMask The type of variables to reduce (SYSTEM_VAR, CARTESIAN_VAR, DUMMY_VAR,...). 
                   Different types of variables can be indicated using '|'. A good
		   option is to use ~DUMMY_VAR (this reduces for all variables except
		   for dummy ones).
    \param b The box to be reduced.
    \param cs The cuiksystem with the equations to use.
    
    \return The status of the box after the reduction (EMPTY_BOX, REDUCED_BOX, 
            REDUCED_BOX_WITH_SOLUTION, ERROR_IN_PROCESS).

    \sa ReduceBoxEquationWise ReduceRange
*/
unsigned int ReduceBox(Tparameters *p,unsigned int varMask,Tbox *b,TCuikSystem *cs);

/** 
    \brief Process a box after being reduced.

    After box reduction we have to decide what to do with the box. If it empty, we
    just discart it. If is small enough (smaller than SIGMA) we consider it as a
    solution. Finally, non-empty, non-small boxes are bisected and added to the list
    of boxes pending to be processed.

    \param p The set of parameters.
    \param c Output of ReduceBox (EMPTY_BOX, REDUCED_BOX, 
            REDUCED_BOX_WITH_SOLUTION, ERROR_IN_PROCESS).
    \param f_out File where to store solutions. If NULL solutions are to written to any file.
    \param sol List where to store solutions. If NULL solutions are not listed. Be aware that
           it makes few sense to solve a problem and use f_out=NULL and sol=NULL since there
	   will be no way to know the solutions.
    \param boxes Set of boxes pending to be processed.
    \param b The processed box.
    \param cs The cuiksystem used to process the box.
    
    \sa ReduceBox
*/
void PostProcessBox(Tparameters *p,unsigned int c,
		    FILE *f_out,
		    Tlist *sol,
		    Theap *boxes,
		    Tbox *b,
		    TCuikSystem *cs);

/** 
    \brief Removes non-used variables.

    Remove the variables that do not appear in the equation set.<br>
    This is one of the steps executed in the cuiksystem simplification.

    \param p The set of parameters.
    \param cs The cuiksystem to simplify.
    
    \sa SimplifyCuikSystem
*/
void CSRemoveUnusedVars(Tparameters *p,TCuikSystem *cs);


/** 
    \brief Removes variables with constant range.

    Variables with punctual range are constants that can be removed
    from the equations. If the variables was previously used to replace
    another variable in the cuiksystem then the replaced variable also
    becomes constant.<br>
    This is one of the steps executed in the cuiksystem simplification. 
    The simplification is the process of defining a new set of equations
    and variables from those given by the user but eliminating variables
    with trivial values or variables that are linearly related with other
    variables. In this process, all variable indexes are referred to those
    in the original cuiksystem (since the simplified one is still in
    construction).

    \param p The set of parameters.
    \param replaced TRUE if the <em>i</em>-th variable in the original
                    cuiksystem has been replaced.
    \param lc If replaced[i] is TRUE, lc[i] is the linear constraint giving
              the replacement of variable 'i' in function of the other variables.
    \param borig A box with the ranges for the variables in the original system. Those ranges
                 are updated as simplifications are introduce. At the end, the ranges are used
                 to set the ranges for the variables in the simplified system.
    \param cs The cuiksystem to simplify.
    
    \return TRUE if the cuiksystem still holds.

    \sa SimplifyCuikSystem
*/
boolean CSRemoveVarsWithCtRange(Tparameters *p,
				boolean *replaced,TLinearConstraint *lc,
				Tbox *borig,TCuikSystem *cs);

/** 
    \brief Removes variables that are linearly dependent on other variables.

    Detects equations of the form

    \f[ \sum_{i=1}{n} a_i\:x_i = c \f]

    From where a variable replacement can be defined

    \f[ x_j=\frac{1}{a_j}\left(\sum_{i \neq j} a_i\:x_i - c\right) \f]

    Note that if \f$x_j\f$ was used to replace another variable, \f$z\f$, the
    elimination of \f$x_j\f$ has to be propagated to the linear constraint
    replacing  \f$z\f$.

    This is one of the steps executed in the cuiksystem simplification. 
    The simplification is the process of defining a new set of equations
    and variables from those given by the user but eliminating variables
    with trivial values or variables that are linearly related with other
    variables. In this process, all variable indexes are referred to those
   in the original cuiksystem (since the simplified one is still in
    construction).

    \param p The set of parameters.
    \param simplificationLevel The simplification level.
    \param changed Is set to TRUE if this function makes any change into the cuiksystem.
    \param level Level (or complexity) of the simplification.
                 Maximum number of terms in the linear combination used to replace the variable.
                 It makes sense to first replace variables assigned to constants and then
	         variables assigned to another variable and so on. Therefore, this function
	         is used with increasing values of \e n.
    \param replaced TRUE if the <em>i</em>-th variable in the original
                    cuiksystem has been replaced.
    \param lc If replaced[i] is TRUE, lc[i] is the linear constraint giving
              the replacement of variable 'i' in function of the other variables.
    \param borig A box with the ranges for the variables in the original system. Those ranges
                 are updated as simplifications are introduce. At the end, the ranges are used
                 to set the ranges for the variables in the simplified system.
    \param cs The cuiksystem to simplify.
    
    \return TRUE if the cuiksystem still holds.

    \sa SimplifyCuikSystem
*/
boolean CSRemoveLCVars(Tparameters *p,unsigned int simplificationLevel,
		       unsigned int level,boolean *changed,
		       boolean *replaced,TLinearConstraint *lc,
		       Tbox *borig,TCuikSystem *cs);
/** 
   \brief Simplifies a cuiksystem.
   
   Generate a simplified version of a cuiksystem by eliminating variables with
   constant values from the equations and by replacing variables by other variables
   if there is a linear dependency between them.<br>
   Note that this is an iterative process (when a variable becomes constant it can
   trigger further simplifications). In extremely large systems this can be slow.

   Simplifications can introduce numerical issues. For instance to replace a variable
   that appear in a equation like<br>
    <center>\f[ a x = b, \f]</center>
   we have to operate <em>b/a</em> and this can introduce perturbations in the system
   due to floating point rounding. We try to do our best to avoid problems (for instance
   we only apply the above simplification if a=1) but small perturbation are unavoidable
   in general and for particularly ill-conditioned problems they can lead to simplified
   systems with a different set of solutions than the original system.
   If you encounter such a problem it would be safer to operate directly with the
   original system and not with the simplified one. This can be done, 
   setting the \ref CT_SIMPLIFICATION_LEVEL "SIMPLIFICATION_LEVEL" parameter to 0.

   \param p The set of parameters.   
   \param cs The cuiksystem to simplify.
*/
boolean SimplifyCuikSystem(Tparameters *p,TCuikSystem *cs);

/** 
   \brief Adds linear combination of the Jacobian to the system.

   This is the common part of \ref AddJacobianEquations and
   \ref AddSimplifiedJacobianEquations. It basically operates on a given
   Jacobian, independently of where this Jacobian comes from.

   Note that the new equations are to be added to the original system and therefore
   the input Jacobian MUST be expressed in this system of equations. 
   For instance, when adding equations from the simplified system we have to first
   re-write the equations in terms of the original variables.

   IMPORTANT: What we actually add is the product of the TRASPOSED Jacobian
   with a vector of new variables (lambdas). This generates as many new
   equations as variables in the problem. We can generate only a subset 
   of such variables with the 'selectedVars' paramater.

   \param p The set of parameters.
   \param selectedVars The variables to take into account. NULL to use all variables.
   \param J The Jacobian.
   \param cs The cuiksystem to modify.
*/
void AddJacobianEquationsInt(Tparameters *p,boolean *selectedVars,TJacobian *J,TCuikSystem *cs);

/** 
   \brief Updates the cached information for the cuiksystem.
   
   The cuiksystem stores some cached information about variables and
   equations. This information has to be re-computed everytime the
   cuiksystem is modified.<br>
   This functions takes care of re-computing the cached information.<br>
   Additionally, this functions triggers the cuiksystem simplification
   since we cache information both for the original and the simplified
   systems.

   \param p The set of parameters.   
   \param cs The cuiksystem to be updated.
   
   \sa UnUpdateCuikSystem SimplifyCuikSystem
*/
boolean UpdateCuikSystem(Tparameters *p,TCuikSystem *cs);

/** 
   \brief Removes the cached information for the cuiksystem.
   
   The cuiksystem stores some cached information about variables and
   equations. This information has to be re-computed everytime the
   cuiksystem is modified.<br>
   This functions takes care of removeing the cached information
   and the cuiksystem simplification.
  
   \param cs The cuiksystem to be un-updated.
   
   \sa UpdateCuikSystem SimplifyCuikSystem
*/
void UnUpdateCuikSystem(TCuikSystem *cs);

/** 
   \brief Computes the optimal split dimension for a given box.
   
   Selects and optimal split dimension for a given box.<br>
   The selection depent on the split policy determined by the user.
   If parameter SPLIT_ERROR is TRUE, we take select as split dimension
   the variable that introduces a higher linearization error for the
   different equations (i.e., the variable with a largest contribution to 
   the linearization error).
   Otherwise, we split dimension is the argest box side. <br>
   Only  dimensions corresponding to system variables are selected
   as split dimensions.
  
   \param p The set of parameters.
   \param b The box to be split.
   \param cs The cuiksystem.
   
   \return The preferred split dimension for the box.
*/
unsigned int ComputeSplitDimInt(Tparameters *p,Tbox *b,TCuikSystem *cs);

/** 
   \brief Saves internal the cuik solver state information to a file.
   
   While solving a problem, every STATE_PERIOD processed boxes we store
   the solver state into a file. In this way if the process crashes, we
   can re-start the solver from the last saved state.<br>
   The save information includes the solver statistics and the list of
   boxes pending to be processed. In the case of a parallel execution
   this last list includes also the boxes already send to the children
   processors but that are still in process.
   <br>
   If STATE_PERIOD is set to 0 no state information is saved.
   
   \param fname The name of the file where to write the information.
   \param lb The list of boxes pending to be processed.
   \param cs The cuiksystem.

   \sa LoadCSState
*/
void SaveCSState(char *fname,Tlist *lb,TCuikSystem *cs);

/** 
   \brief Retrives the internal the cuik solver state information from a file.
   
    Retrives the internal the cuik solver state information from a file previously
    saved by SaveCSState. This allows to init the solving process from a
    intermediate point (and not from scratch) after, for intance, a power failure.
  
   \param fname The name of the file from where to read the information.
   \param lb The list of boxes pending to be processed.
   \param cs The cuiksystem.

   \sa SaveCSState
*/
void LoadCSState(char *fname,Tlist *lb,TCuikSystem *cs);


/************************************************************************/
/************************************************************************/
/************************************************************************/

/*
  The equation is dummified and the resulting equations and new variables
  are added to the cuik system.

  Dummification is performed in the last step of the simplification and, thus,
  this function operates in the sets of simplified equations and variables

  Dummification consists in changing all monomials of type x^2 or x*y by new
  variables 'z' and adding the corresponding equations (z=x^2 or z=x*y) to
  the system.

  The level of dummification is controlled by the 'dummify' parameter.

  This internal function is hidden to the user. In this way dummification is
  applied only after the system simplification.
  See AddEquation2CS and SimplifyCuikSystem.
*/
void DummifyAndAddEquation(Tparameters *p,Tequation *eq,TCuikSystem *cs)
{
  if (eq!=NULL)
    {
      unsigned int nf;
      unsigned int i,nv,mv;
      Tvariable_set *vars;
      unsigned int dummify;
      unsigned int eqType;

      dummify=(unsigned int)(GetParameter(CT_DUMMIFY,p));

      vars=GetEquationVariables(eq);
      eqType=GetEquationType(eq);

      nv=VariableSetSize(vars);
      mv=NVariables(&(cs->variables));
      for(i=0;i<nv;i++)
	{
	  if (GetVariableN(i,vars)>=mv)
	    Error("Unknown variable in AddEquation2CS");
	}

      nf=GetNumMonomials(eq);
      if (nf>0)
	{
	  boolean keep=TRUE; /* True if the equation is kept in its original form */
	  
	  /* Dummy equations are not dummified again */
	  /*dummify equations with just one monomial introduce a
	    too simple variable x=ct that is not simplified since
	    the dummifications is performed after the simplification. */
	  if ((eqType==DUMMY_EQ)||(GetNumMonomials(eq)==1)||(GetEquationOrder(eq)>2))
	    keep=TRUE; 
	  else
	    {
	      switch (dummify)
		{
		case 0:
		  keep=TRUE;
		  break;
		case 1:
		  keep=((LinearEquation(eq))||
			(ParabolaEquation(eq))|| 
			(SaddleEquation(eq))|| 
			(CircleEquation(eq))|| 
			(SphereEquation(eq)));
		  break;
		case 2:
		  keep=((LinearEquation(eq))||
			(ParabolaEquation(eq))|| 
			(SaddleEquation(eq)));
		  break;
		case 3:
		  keep=((LinearEquation(eq))||
			(ParabolaEquation(eq))|| 
			(SaddleEquation(eq))|| 
			(CircleEquation(eq))|| 
			(SphereEquation(eq))||
			(GetEquationCmp(eq)!=EQU)); /*Inequalities are kept in original form*/
	    
		  break;
		case 4:
		  keep=((LinearEquation(eq))||
			(ParabolaEquation(eq))|| 
			(SaddleEquation(eq))||
			(GetEquationCmp(eq)!=EQU)); /*Inequalities are kept in original form*/
		  break;
		default:
		  Error("Undefined value for DUMMIFY parameter");
		}
	    }

	  if (keep)
	    AddEquation(eq,&(cs->equations));
	  else
	    {
	      unsigned int j,p,vid1,vid2,vid3;
	      Tmonomial *f,fnew;
	      Tequation eqnew; /* Bilinear and quadratic monomials produce new auxiliary equations */
	      Tequation eqlineal; /* The original equation is transformed into a lineal equation */
	      char *vname;
	      Tinterval range;
	      Tvariable v;
	      char *n1,*n2;

	      InitEquation(&eqlineal);
	      
	      for(j=0;j<nf;j++) /* For all monomials in the equation to be dummified */
		{

		  f=GetMonomial(j,eq);
		  vars=GetMonomialVariables(f);
		  nv=VariableSetSize(vars);

		  switch(nv)
		    {
		    case 1: /*A single variable in the monomial*/
		      if (GetVariableFunctionN(0,vars)!=NFUN)
			AddMonomial(f,&eqlineal);
		      else
			{
			  p=GetVariablePowerN(0,vars);

			  switch(p)
			    {
			    case 1: /*One variable with degree 1*/
			      /* A linear monomial: just add it to the linear equation*/
		      
			      AddMonomial(f,&eqlineal); /* A copy of monomial 'f' is stored in eqlineal*/
			      break;

			    case 2:/*One varialbe With degree 2*/		      
			      /* Add a linear monomial to eqlinear with a dummy variable
				 and add the corresponding parabola equation*/

			      vid1=GetVariableN(0,vars);

			      /* Generate a new variable dummy that will stand for  x^2 */
			      n1=GetVariableName(GetVariable(vid1,&(cs->variables)));
			      NEW(vname,strlen(n1)+20,char);
			      sprintf(vname,"dummy_%s_2",n1);
						    
			      vid2=GetVariableID(vname,&(cs->variables));

			      if (vid2==NO_UINT)
				{
				  /* if the dummy variable is a new one, add the corresponding
				     dummy equation to the system */

				  NewVariable(DUMMY_VAR,vname,&v);
				  IntervalPow(GetVariableInterval(GetVariable(vid1,&(cs->variables))),2,&range);
				  SetVariableInterval(&range,&v);
			      
				  vid2=AddVariable(&v,&(cs->variables));
				  DeleteVariable(&v);
			      
				  /* Generate a new equation x^2-dummy=0 */
				  InitEquation(&eqnew);
			      
				  InitMonomial(&fnew);
				  AddVariable2Monomial(NFUN,vid1,2,&fnew);
				  AddCt2Monomial( 1.0,&fnew);
				  AddMonomial(&fnew,&eqnew);
				  DeleteMonomial(&fnew);
			      
				  InitMonomial(&fnew);
				  AddVariable2Monomial(NFUN,vid2,1,&fnew);
				  AddCt2Monomial(-1.0,&fnew);
				  AddMonomial(&fnew,&eqnew);
				  DeleteMonomial(&fnew);
			      
				  SetEquationCmp(EQU,&eqnew);
				  SetEquationValue(0.0,&eqnew);
				  /*The derive equations is of the same type as the origiona one*/
				  SetEquationType(DUMMY_EQ,&eqnew);
			      
				  AddEquation(&eqnew,&(cs->equations));
				  DeleteEquation(&eqnew);
				}
			      free(vname);

			      /*Now add the lineal monomial using the new dummy variable to eqlineal*/
			      InitMonomial(&fnew);
			      AddVariable2Monomial(NFUN,vid2,1,&fnew);
			      AddCt2Monomial(GetMonomialCt(f),&fnew);
			      AddMonomial(&fnew,&eqlineal);
			      DeleteMonomial(&fnew);
			      break;

			    default:
			      Error("The input system to DummifyCuikSystem is not in canonical form");
			      break;
			    }
			}
		      break;

		    case 2: /*Two variables in the monomial*/
		      if ((GetVariableFunctionN(0,vars)!=NFUN)||
			  (GetVariableFunctionN(1,vars)!=NFUN))
			AddMonomial(f,&eqlineal);
		      else
			{
			  if ((GetVariablePowerN(0,vars)==1)&&
			      (GetVariablePowerN(1,vars)==1)) /*The two of them with degree 1*/
			    {
			      /*Get the two variables involved in the product we have to rewrite*/
			      vid1=GetVariableN(0,vars);
			      vid2=GetVariableN(1,vars);
			  
			      /*Generate a new dummy variable*/
			      n1=GetVariableName(GetVariable(vid1,&(cs->variables)));
			      n2=GetVariableName(GetVariable(vid2,&(cs->variables)));
			      NEW(vname,strlen(n1)+strlen(n2)+20,char);
			      sprintf(vname,"dummy_%s_%s",n1,n2);
					
			      vid3=GetVariableID(vname,&(cs->variables));
			      if (vid3==NO_UINT)
				{

				  NewVariable(DUMMY_VAR,vname,&v);
				  IntervalProduct(GetVariableInterval(GetVariable(vid1,&(cs->variables))),
						  GetVariableInterval(GetVariable(vid2,&(cs->variables))),
						  &range);
				  SetVariableInterval(&range,&v);
			      
				  vid3=AddVariable(&v,&(cs->variables));
				  DeleteVariable(&v);

				  /* Generate the dummy equation X*Y-dummy=0*/
				  InitEquation(&eqnew);
			      
				  InitMonomial(&fnew);
				  AddVariable2Monomial(NFUN,vid1,1,&fnew);
				  AddVariable2Monomial(NFUN,vid2,1,&fnew);
				  AddCt2Monomial( 1.0,&fnew);
				  AddMonomial(&fnew,&eqnew);
				  DeleteMonomial(&fnew);
			      
				  InitMonomial(&fnew);
				  AddVariable2Monomial(NFUN,vid3,1,&fnew);
				  AddCt2Monomial(-1.0,&fnew);
				  AddMonomial(&fnew,&eqnew);
				  DeleteMonomial(&fnew);
			      
				  SetEquationCmp(EQU,&eqnew);
				  SetEquationValue(0.0,&eqnew);
				  /*The derive equations is of the same type as the origiona one*/
				  SetEquationType(DUMMY_EQ,&eqnew);

				  AddEquation(&eqnew,&(cs->equations));
				  DeleteEquation(&eqnew);
				}
			      free(vname);

			      /*Now add the lineal monomial using the new dummy variable to eqlienal*/
			      InitMonomial(&fnew);
			      AddVariable2Monomial(NFUN,vid3,1,&fnew);
			      AddCt2Monomial(GetMonomialCt(f),&fnew);
			      AddMonomial(&fnew,&eqlineal);
			      DeleteMonomial(&fnew);
			    }
			  else
			    /* One of the 2 variables in the monomial has degree >1 */
			    /* Right now this should never happen since equations
			       with order>2 are directly added to the outpu system */
			    Error("The input system to DummifyCuikSystem is not in canonical form");
			}
		      break;

		    default:
		      /* A monomial with more than 2 variables */
		      /* Right now this should never happen since equations
			 with order>2 are directly added to the outpu system */
		      Error("The input system to DummifyCuikSystem is not in canonical form");
		    }

		} /* Proceed with next monomial in the under-dummification equation*/

	      /* The linearized original equation is added to the system */

	      SetEquationCmp(GetEquationCmp(eq),&eqlineal);
	      SetEquationValue(GetEquationValue(eq),&eqlineal);
	      /*The resulting lineal equation is of the same type as the original equation*/
	      SetEquationType(eqType,&eqlineal);

	      AddEquation(&eqlineal,&(cs->equations));
	      DeleteEquation(&eqlineal);
	    }
	}
    }
}

void DummifyCuikSystem(Tparameters *p,TCuikSystem *cs)
{
  if (cs->scalar)
    {
      unsigned int i,neq;
      Tequations eqs;

      CopyEquations(&eqs,&(cs->equations));
      DeleteEquations(&(cs->equations));
      InitEquations(&(cs->equations));

      neq=NEquations(&eqs);
      for(i=0;i<neq;i++)
	DummifyAndAddEquation(p,GetEquation(i,&eqs),cs);

      DeleteEquations(&eqs);
    }
}

unsigned int ReduceBoxEquationWise(Tparameters *p,Tbox *b,TCuikSystem *cs)
{
  boolean empty;
  boolean small;
  boolean significantReduction;
  Tbox b_orig;
  unsigned int i,j;
  double rho,smallSigma,epsilon;
  double mi_r;
  double reduction;

  rho=GetParameter(CT_RHO,p);
  epsilon=GetParameter(CT_EPSILON,p);
  smallSigma=GetParameter(CT_SMALL_SIGMA,p);

  /*default values*/
  empty=FALSE;
  significantReduction=FALSE;
  small=FALSE;

  #if (_DEBUG>2)
    printf("    Croping box: ");
    PrintBox(stdout,b);
    printf("      Size in: %g\n",GetBoxSize(cs->systemVar,b));
  #endif

  do {
    CopyBox(&b_orig,b);

    for(j=0;((!empty)&&(j<cs->nequations));j++)
      {
	#if (_DEBUG>5)
	  printf("          Croping with equation %u: \n",j);
	  printf("            Input box: "); 
	  PrintBox(stdout,b);
	  printf("            s: %g  v:%g\n",GetBoxSize(NULL,b),GetBoxVolume(NULL,b));
	#endif
	if (CropEquation(j,ANY_TYPE_VAR,epsilon,rho,b,&(cs->variables),&(cs->equations))==EMPTY_BOX)
	  empty=TRUE;
	#if (_DEBUG>5)
  	  if (empty)
	    printf("            Empty output box\n");
	  else
	    {
	      printf("            Output box: "); 
	      PrintBox(stdout,b);
	      printf("            s: %g  v:%g\n",GetBoxSize(NULL,b),GetBoxVolume(NULL,b));
	    }
	#endif
      }

    if (!empty)
      {
	mi_r=1.0;
	for(i=0;i<cs->nvariables;i++)
	  {
	    /*variables of all types are affected by crop*/
	    reduction=IntervalSize(GetBoxInterval(i,b))/IntervalSize(GetBoxInterval(i,&b_orig));
	    if (reduction<mi_r) mi_r=reduction; 
	  }

	significantReduction=(mi_r<rho);
	small=(GetBoxSize(cs->systemVar,b)<=smallSigma);

	#if (_DEBUG>2)
	  printf("      Crop reduction: %f\n",mi_r);
	  if (small)
	    printf("        Tiny boxes are not reduced any more\n");
	  else
	    {
	      if (significantReduction) 
		printf("        Large reduction. Cropping again\n");
	    }
	#endif
      }
    DeleteBox(&b_orig);
    
  } while ((!empty)&&(!small)&&(significantReduction));
  
  #if (_DEBUG>2)
    if (empty)
      printf("    Empty in Crop\n");
    else
      {
	printf("    Croped box: ");
	PrintBox(stdout,b);
	printf("      Size out: %g\n",GetBoxSize(cs->systemVar,b));
      }
  #endif
    
  if (empty)
    return(EMPTY_BOX);
  else
    return(REDUCED_BOX);
}

/*
  This is the basic function of the solver. This function includes the
  ShrinkBox procedure described in our papers plus a loop interating
  ShrinkBox as far as the box is significantly reduced (and still not empty).

  Thus, ReduceBox takes an input box 'b' and reduces it as much as possible by removing
  parts that do not include any solution point.
  It returns information about what happened in the box shrinking process

      ERROR_IN_PROCESS: When one of the simplex failed due to numerical inestabilities
                        The better the simplex implementation the less likely this
			output.

      EMPTY_BOX: The box includes no solution. In this case the output box is
                 undefined (it includes empty intervals).

      REDUCED_BOX: The box was reduced and it has to be processed further to determine
                   if it includes any solution.

      REDUCED_BOX_WITH_SOLUTION: The box was been reduced and one of the reduction
                                 steps was contractive. This indicates the box
				 includes a solution point.
 */
unsigned int ReduceBox(Tparameters *p,unsigned int varMask,Tbox *b,TCuikSystem *cs)
{
  /*The box can only be reduced if we have constraints*/
  if (cs->simp_nequations==0)
    return(REDUCED_BOX);
  else
    {
      boolean empty;
      boolean significantReduction;
      boolean small;
      boolean hasSolution;
      boolean err;
      boolean boxOK;
      unsigned int e;
      double mi_r,ma_s;
      double reduction,size;
      unsigned int i,j;
      Tbox b_orig;
      TSimplex lp;
      double epsilon,smallSigma,rho,lr2tm_q,lr2tm_s;
      unsigned int safeSimplex;
      boolean repeatLoop;

      if ((!cs->updated)||(!cs->consistent))
	Error("Non-updated/consistent CS in ReduceBox");

      epsilon=GetParameter(CT_EPSILON,p);
      smallSigma=GetParameter(CT_SMALL_SIGMA,p);
      rho=GetParameter(CT_RHO,p);
      lr2tm_q=GetParameter(CT_LR2TM_Q,p);
      lr2tm_s=GetParameter(CT_LR2TM_S,p);
      safeSimplex=(unsigned int)(GetParameter(CT_SAFE_SIMPLEX,p));

      /*default values*/
      empty=FALSE;
      hasSolution=FALSE;
      err=FALSE;		
      boxOK=TRUE;
      small=FALSE;
      significantReduction=FALSE;
      repeatLoop=FALSE;

      do { 
	#if (_DEBUG>2)
	  printf("\n  Go for box reduction via crop+simplex\n");	
	  printf("  InputBox: "); PrintBox(stdout,b);
	  printf("    s: %g  v:%g\n",GetBoxSize(NULL,b),GetBoxVolume(NULL,b));
	#endif

	/*****************************************************************/
	/* One step of box reduction */

	/*#if ((!_USE_MPI)&&(_DEBUG==1))*/
        #if ((!_USE_MPI)&&(_DEBUG>1))
	  fprintf(stderr,".");fflush(stderr);
	#endif

	NewBoxReduction(&(cs->st));

	/* First we do an equation wise reduction of the ranges -> Crop equation 
	   repeated for each equation as far as we get a significant box reduction */
   
	empty=(ReduceBoxEquationWise(p,b,cs)==EMPTY_BOX);
	
	/* If the equation-wise reduction gives a full box, proceed with the global
	   test based on linear programming */

	if (empty)
	  repeatLoop=FALSE; /*There is no need to iterate*/
	else
	  {
	    SimplexCreate(epsilon,cs->nvariables,&lp);
	    
	    /* Add the linear constraints bounding the equations. This include
	       croping the input ranges if necessary */

	    for(j=0;((!empty)&&(j<cs->nequations));j++)
	      {
		if (!AddEquation2Simplex(j,
					 lr2tm_q,lr2tm_s,
					 epsilon,safeSimplex,rho,
					 b,&(cs->variables),
					 &lp,&(cs->equations)))
		  empty=TRUE;
	      }
	    
            #if (_SIMPLEX_ENGINE==_GUROBI)
	      UpdateSimplex(&lp);
	    #endif
	    
	    boxOK=TRUE;
	    err=FALSE;
	    small=FALSE;
	    significantReduction=FALSE;

	    /* Use the simplex to reduce the ranges for the variables */
	    if ((!empty)&&(SimplexNRows(&lp)>0)) /* In extreme cases the simplex tableau can be empty 
						    and then nothings can be reduced*/
	      {	
		/* Store the original box to check the actual reduction */
		CopyBox(&b_orig,b);

		#if ((_SIMPLEX_ENGINE!=_CLP)&&(_SIMPLEX_ENGINE!=_GUROBI))
		  /* in CLP/Gurobi ResetSimplex has no effect */
		  ResetSimplex(&lp);
		#endif

		for(i=0;((boxOK)&&(i<cs->nvariables));i++)
		  {
		    /* The crop takes care of reducing the ranges of the dummy 
		       variables in function of the non dummy ones (system,
		       secondary and cartesian).
		    */

		    if ((cs->varType[i]&varMask)&&(!SimplexColEmpty(i,&lp)))
		      {
			/*Reduce the ranges for variable 'i'*/
			e=ReduceRange(epsilon,safeSimplex,i,b,&lp);
			boxOK=(e==REDUCED_BOX); 
		      }		    
		  }

		/* Analize the output out of the range reduction */
		if (boxOK)
		  {
		    /* Compute the minimum reduction ratio for all ranges. The smaller
		       the reductin ratio, the maximal the box shrink for that dimension*/
		    mi_r=1.0;
		    ma_s=0.0;
		    for(i=0;i<cs->nvariables;i++)
		      {
			if (cs->notDummyVar[i])
			  {
			    size=IntervalSize(GetBoxInterval(i,b));
			    if (size>ma_s) ma_s=size;

			    reduction=size/IntervalSize(GetBoxInterval(i,&b_orig));
			    if (reduction<mi_r) mi_r=reduction; 
			  }
		      }

		    /* If the output box is fully included in the input one this means
		       the box includes a solution (for sure) */
		    if ((ma_s<lr2tm_q)&&(ma_s<lr2tm_s)&&
			(BoxInclusion(cs->systemVar,b,&b_orig)))
		      {
			hasSolution=TRUE;
			#if (!_USE_MPI)
			  fprintf(stderr,"(>!<)");
			#endif
		      }

		    small=(ma_s<=smallSigma);
		    significantReduction=(mi_r<rho); 
		  }
		else
		  {
		    empty=(e==EMPTY_BOX);
		    err=(e==ERROR_IN_PROCESS);
		  }

		DeleteBox(&b_orig);
	      }
	    
	    repeatLoop=((!empty)&&(!err)&&(!small)&&(significantReduction));
	    
	    SimplexDelete(&lp);

	    #if (_DEBUG>2)
	    if (empty)
	      printf("    Empty\n");
	    else
	      {
		if (err)
		  printf("    Simplex Error\n");
		else
		  {
		    printf("  OutputBox: "); PrintBox(stdout,b);
		    printf("  Reduction ->  %f\n",mi_r);
		  
		    printf("  Size after reduction: %g\n ",GetBoxSize(cs->systemVar,b));
		    printf("  Volume after reduction: %g\n ",GetBoxVolume(cs->systemVar,b));
		  
		    if (significantReduction)
		      printf("    Large enough reduction-> Try again all equations\n");
		    else
		      printf("    Not enough reduction.\n");
		  }
	      }
	    #endif 
	    
	  } /* end if not empty after ReduceBoxEquationWise */


      } while(repeatLoop);
      
      if (err)
	e=ERROR_IN_PROCESS;
      else
	{
	  if (empty)
	    e=EMPTY_BOX;
	  else
	    {
	      /* If at least on step was a contraction this means
		 there is a solution inside the box*/
	      if (hasSolution)
		e=REDUCED_BOX_WITH_SOLUTION; 
	      else
		e=REDUCED_BOX;
	    }
	}

      return(e);
    }
}

/*
  This procedure is called just after using ReduceBox to analyzed what
  happened with the box and what to do next.ç

  'c' is the return code out of Reduce Box

  If the box is small (max side size smaller than sigma), we consider it 
  a solution and we store it in the list 'sol' (if defined), we save 
  the solution into 'f_out' (if defined).
  
  Otherwise, we split the box in two sub-boxes and we store them in list 'boxes'
  The dimension along which the box is splitte is determined  according to 
  parameter 'error_split'. The two sub-boxes are added to 'boxes' in the first
  of in the last position according to parameter 'depth_first'.
*/
void PostProcessBox(Tparameters *p,
		    unsigned int c,
		    FILE *f_out,
		    Tlist *sol,
		    Theap *boxes,Tbox *b,
		    TCuikSystem *cs)
{
  boolean empty,small;
  Tbox b_orig;
  double sigma;
  unsigned int nNewton;
  double epsilon;

  empty=(c==EMPTY_BOX);
	
  if (empty)
    {
      NewEmptyBox(&(cs->st));
      #if (_DEBUG>1)
        printf("  The box is empty -> deleted\n");
      #endif
      #if (_DEBUG>0)
        fprintf(stderr,"e\n");
      #endif
    }
  else
    {
      /* c==REDUCED_BOX or c==REDUCED_BOX_WITH_SOLUTION or c==ERROR_IN_PROCESS*/
      #if (_DEBUG>1)
        printf("  Resulting box: ");
	PrintBox(stdout,b);
      #endif
      #if (_DEBUG>0)
        fprintf(stderr,"<%g %g>",
		GetBoxVolume(cs->systemVar,b),
		GetBoxSize(cs->systemVar,b));
      #endif  
	
      /* We initialize a box in the original system and set the default ranges
         (ranges in case the variable in the original system is not in the
	 simplified one... this is not likely to occur here but in the system
	 to sybsystem relation but in this way the interface is the same)*/
      BoxFromVariables(&b_orig,&(cs->orig_variables)); 
      UpdateOriginalFromSimple(b,&b_orig,cs->orig2sd);
      #if (_DEBUG>1)
        printf("  Original box: ");
	PrintBox(stdout,&b_orig);
      #endif

      epsilon=GetParameter(CT_EPSILON,p);
	
      nNewton=(unsigned int)GetParameter(CT_MAX_NEWTON_ITERATIONS,p);
      if ((nNewton>0)&&(f_out!=NULL)&&(GetBoxSize(cs->systemVar,b)>epsilon))
	{
	  double *sol;
	  Tbox b_sol;
	  
	  NEW(sol,cs->orig_nvariables,double);
	  
	  if ((CuikNewtonInBox(p,&b_orig,sol,&b_sol,cs)&(CONVERGED_IN_BOX|CONVERGED_IN_GLOBAL))>0)
	    {
	      fprintf(f_out,"Newton [s:%f v:%g l:%u t:%g]: ",
		      GetBoxSize(cs->systemVar,b),
		      GetBoxVolume(cs->systemVar,b),
		      GetBoxLevel(b),
		      GetElapsedTime(&(cs->st)));
	      PrintBoxSubset(f_out,cs->orig_notDummyVar,cs->orig_varNames,&b_sol); 
	    }
	  
	  free(sol);
	  DeleteBox(&b_sol);
	  fflush(f_out);
	}

      sigma=GetParameter(CT_SIGMA,p);

      /*The original system can have variables not included in the simplified one. For instance, 
        variables not in the system equations due to the particular constants of the problem under
        analysis are eliminated, even though they appear in dummy equations (this is common
	when ROT_REP=1, see link.h). Those removed variables are never reduced and thus,
        the original box never reduces below sigma. This is why we use the simplified box
        (i.e., the one we actually reduce) to assess whether or not we have a solution. */
      small=(GetBoxSize(cs->systemVar,b)<=sigma);

      if (small)
	{
	  #if (_DEBUG>1)
	    printf("  The box is a solution (size %g vs [%g]) ->add to the list of solutions\n",
		   GetBoxSize(cs->orig_systemVar,&b_orig),sigma);
	  #endif

	  NewSolutionBox((c==REDUCED_BOX_WITH_SOLUTION),
			 GetBoxVolume(cs->orig_systemVar,&b_orig),
			 GetBoxDiagonal(cs->orig_systemVar,&b_orig),
			 &(cs->st));
	  
	  if(c==ERROR_IN_PROCESS)
	    NewRBError(&(cs->st));
 
	  #if (_DEBUG>0)
	    if(c==REDUCED_BOX_WITH_SOLUTION)
	      fprintf(stderr,"S\n");
	    else
	      fprintf(stderr,"s\n");
	  #endif	
	      
	  
	  if (f_out!=NULL)
	    {
	      if(c==ERROR_IN_PROCESS)
		fprintf(f_out," E");
	      
	      fprintf(f_out," %3u (err:%g",
		      GetNSolutionBoxes(&(cs->st)),
		      ErrorInSolution(&b_orig,cs));
	      #if (_DEBUG>1)
	        printf("    Solution number %u with erorr %g\n",
		       GetNSolutionBoxes(&(cs->st)),
		       ErrorInSolution(&b_orig,cs));
	      #endif

	      if (cs->searchMode==MINIMIZATION_SEARCH)
		fprintf(f_out," min:%g",EvaluateEqMin((void *)b,(void *)cs));

	      fprintf(f_out," tm:%g):",GetElapsedTime(&(cs->st)));

	      if (c==REDUCED_BOX_WITH_SOLUTION)
		fprintf(f_out," <S> ");

	      /*The output does not include the dummy variables (they are 
		not relevant any more)*/
	      PrintBoxSubset(f_out,cs->orig_notDummyVar,cs->orig_varNames,&b_orig); 
	      fflush(f_out);	      
	    }
	  if (sol!=NULL)
	    {
	      Tbox *sb;

	      NEW(sb,1,Tbox); 

	      CopyBox(sb,&b_orig);

	      AddLastElement((void *)sb,sol);
	    }

	  /*If we want to ad box to a solution list, we have to copy 'b' 
	    somewhere else ('b' is delete after this function !)*/
	}
      else
	{
	  /* Non empty large box or error in ReduceBox */

	  Tbox b1,b2;
	  unsigned int d;

	  #if (_DEBUG>1)
	    printf("  Box size : %g vs. %g\n",GetBoxSize(cs->orig_systemVar,&b_orig),sigma);
	    printf("  The box has to be splitted (and deleted)\n");
	  #endif

	  NewSplittedBox(&(cs->st));

	  d=ComputeSplitDimInt(p,b,cs);

	  SplitBox(d,CUT_POINT,&b1,&b2,b);

	  #if (_DEBUG>1)
	    printf("  Splitting along dimension %u (internal)\n",d);
	    if (cs->searchMode==MINIMIZATION_SEARCH)
	      printf("      Box penalgy : %g\n",EvaluateEqMin((void *)&b1,(void *)cs));
	    printf("        SubBox:"); PrintBox(stdout,&b1);
	    if (cs->searchMode==MINIMIZATION_SEARCH)
	      printf("      Box penalty : %g\n",EvaluateEqMin((void *)&b2,(void *)cs));
	    printf("        SubBox:"); PrintBox(stdout,&b2);
	  #endif

	  AddBox2HeapOfBoxes(&b1,boxes);
	  AddBox2HeapOfBoxes(&b2,boxes);
	  DeleteBox(&b1);
	  DeleteBox(&b2);
	 
	  if (c==ERROR_IN_PROCESS)
	    {
	      #if (_DEBUG>0)
	        fprintf(stderr,"E[%u]\n",d);
	      #endif
	      #if (_DEBUG>1)
	        printf("  Splitted due to simplex error\n");
	      #endif
	      NewRBError(&(cs->st));
	    }
	  #if (_DEBUG>0)
	  else
	    fprintf(stderr,"b[%u]\n",d);
	  #endif
	}

      DeleteBox(&b_orig);  
    }
}

void CSRemoveUnusedVars(Tparameters *p,TCuikSystem *cs)
{
  unsigned int i,vt;
  double epsilon;

  epsilon=GetParameter(CT_EPSILON,p);

  /*We proceed back to front because removing a variable change the
    indexes of variables above it.*/
  i=NVariables(&(cs->variables));
  while(i>0)
    {
      i--;
      vt=GetVariableTypeN(i,&(cs->variables));
      
      if ((!VarIncluded(i,GetEquationVariables(&(cs->orig_eqMin))))&&
	  (((vt==DUMMY_VAR)&&(!UsedVarInNonDummyEquations(i,&(cs->equations))))||
	   ((vt!=SYSTEM_VAR)&&(vt!=VELOCITY_VAR)&&(vt!=NON_DYNAMIC_VAR)
	    &&(!UsedVarInEquations(i,&(cs->equations))))))
	{
	  /* ... Therefore, we can still have dummy equations with the non-used variables*/
	  RemoveEquationsWithVar(epsilon,i,&(cs->equations)); 
	  RemoveVariable(i,&(cs->variables));
	}
    }
}

boolean CSRemoveVarsWithCtRange(Tparameters *p,
				boolean *replaced,TLinearConstraint *lc,
				Tbox *borig,TCuikSystem *cs)
{
  boolean found,hold;
  unsigned int nv,origID1;
  unsigned int id1;
  char *name1;
  double epsilon;
  double ct2;
  Tinterval *range;

  epsilon=GetParameter(CT_EPSILON,p);

  hold=TRUE;

  do {
    found=FALSE;

    /* A variable with a ct range can be removed */
    nv=NVariables(&(cs->variables));
    id1=0;
    while((!found)&&(id1<nv))
      {
	if (IsPositionVariable(id1,&(cs->variables)))
	  {
	    name1=GetVariableName(GetVariable(id1,&(cs->variables)));
	    origID1=GetVariableID(name1,&(cs->orig_variables));
	    if (origID1==NO_UINT)
	      Error("Undefined ID1 in CSRemoveVarsWithCtRange");

	    range=GetBoxInterval(origID1,borig);
	    if (IntervalSize(range)==0)
	      {
		ct2=LowerLimit(range); /* ==UpperLimit(range) */
		found=TRUE;
	      }
	  }
	if (!found)
	  id1++;
      }

    /*if we found something to simplify, apply it to the rest of equations
      (this creates a new set of equations that replaces the previous one)*/
    if (found)
      {
	replaced[origID1]=TRUE;
	AddCt2LinearConstraint(ct2,&(lc[origID1]));

        #if (_DEBUG>5) 
	  printf("Ct Range Replacement: %s [%u-%u] ->%.12g\n",name1,origID1,id1,ct2);
        #endif
	    
	if (hold)
	  {
	    TLinearConstraint lc;

	    InitLinearConstraint(&lc);
	    AddCt2LinearConstraint(ct2,&lc);
	    hold=ReplaceVariableInEquations(epsilon,id1,&lc,&(cs->equations));
	    DeleteLinearConstraint(&lc);
	    RemoveVariable(id1,&(cs->variables));
	    
	    #if (_DEBUG>6)
	    if(hold)
	      {
		char **varNames;
		
		
		printf("%%=======================================================\n");
		printf("%% One less variable (ct range)\n"); 
		printf("%%****************************************\n");
		PrintVariables(stdout,&(cs->variables));
		
		nv=NVariables(&(cs->variables));
		NEW(varNames,nv,char *);
		GetVariableNames(varNames,&(cs->variables));
		PrintEquations(stdout,varNames,&(cs->equations));
		free(varNames);
	      }
	    #endif
	  }
      }
  } while((hold)&&(found));

  return(hold);
}

boolean CSRemoveLCVars(Tparameters *p,unsigned int simplificationLevel,
		       unsigned int nTerms,boolean *changed,
		       boolean *replaced,TLinearConstraint *lc,
		       Tbox *borig,TCuikSystem *cs)
{
  boolean found,hold;
  unsigned int m,i,j,nv,neq,origID,origID1;
  Tequation *eq;
  unsigned int id;
  char *name,*name1;
  double epsilon;
  Tvariable *v;
  TLinearConstraint lcr,lcc;
  boolean *systemVars;
  Tinterval error;
  Tbox currentBox;
  boolean polynomial;
  #if (_DEBUG>5) 
    char **varNamesO;

    nv=NVariables(&(cs->orig_variables));
    NEW(varNamesO,nv,char *);
    GetVariableNames(varNamesO,&(cs->orig_variables));
  #endif
  polynomial=PolynomialEquations(&(cs->orig_equations));
  nv=NVariables(&(cs->variables));
  InitBox(nv,NULL,&currentBox);
  NEW(systemVars,nv,boolean);
  for(i=0;i<nv;i++)
    {
      systemVars[i]=IsSystemVariable(i,&(cs->variables));
      SetBoxInterval(i,GetVariableInterval(GetVariable(i,&(cs->variables))),&currentBox);
    }

  epsilon=GetParameter(CT_EPSILON,p);

  *changed=FALSE;
  hold=TRUE;
  
  /* Only scalar (non-velocity) equations can be used to generate simplifcation */
  found=FALSE;
  i=0;
  neq=NScalarEquations(&(cs->equations));
  while((!found)&&(i<neq))
    {
      eq=GetScalarEquation(i,&(cs->equations));
      found=IsSimplificable(simplificationLevel,nTerms,((cs->scalar)&&(polynomial)),
			    systemVars,&currentBox,&id,&lcr,eq); /* 't' is the type of simplification*/
      if (!found)
	i++;
    }
  DeleteBox(&currentBox);
  
  /*if we found something to simplify, apply it to the rest of equations
    (this creates a new set of equations that replaces the previous one)*/
  if (found)
    {
      *changed=TRUE;

      /* Translate the variables identifiers from local to global */
      v=GetVariable(id,&(cs->variables));
      name=GetVariableName(v);
      origID=GetVariableID(name,&(cs->orig_variables));
      if (origID==NO_UINT)
	Error("Undefined var in original system in CSRemoveLCVars");

      /* Translate the 'lcr' linear constraint that refers to the cuiksystem
         in the current state of simplification to the original system */
      m=GetNumTermsInLinearConstraint(&lcr);
      for(i=0;i<m;i++)
	{
	  v=GetVariable(GetLinearConstraintVariable(i,&lcr),&(cs->variables));
	  name1=GetVariableName(v);
	  origID1=GetVariableID(name1,&(cs->orig_variables));
	  if (origID1==NO_UINT)
	    Error("Undefined variable in original system in CSRemoveLCVars");
	  AddTerm2LinearConstraint(origID1,
				   GetLinearConstraintCoefficient(i,&lcr),
				   &(lc[origID]));
	}
      GetLinearConstraintError(&error,&lcr);
      if (IntervalSize(&error)>ZERO)
	Error("Linear constraint used for variable replacement must have ct right-hand");
      AddCt2LinearConstraint(-IntervalCenter(&error),&(lc[origID]));

      replaced[origID]=TRUE;

      #if (_DEBUG>5) 
        printf("Var Replacement: %s[%u-%u]->",name,origID,id);
	PrintLinearConstraint(stdout,FALSE,varNamesO,&(lc[origID]));
      #endif

      CopyLinearConstraint(&lcc,&(lc[origID]));
      AddTerm2LinearConstraint(origID,-1.0,&lcc);
      hold=CropLinearConstraint(ZERO,ANY_TYPE_VAR,borig,&(cs->orig_variables),&lcc);
      if (!hold)
	printf("\nNon intersecting ranges (I)\n");
      DeleteLinearConstraint(&lcc);

      /*If origID was used for the replacement of another variable
	we have to propagate the replacement of origID1 to this other
	variable*/
      nv=NVariables(&(cs->orig_variables));
      for(j=0;((hold)&&(j<nv));j++)
	{
	  if ((replaced[j])&&(LinearConstraintIncludes(origID,&(lc[j]))))
	    {
	      TLinearConstraint ltmp;
	      double ct;

	      ct=RemoveTermFromLinearConstraint(origID,&(lc[j]));
	      CopyLinearConstraint(&ltmp,&(lc[origID]));
	      ScaleLinearConstraint(ct,&ltmp);
	      AddLinearConstraints(&ltmp,&(lc[j]));
	      DeleteLinearConstraint(&ltmp);
	      
	      CopyLinearConstraint(&lcc,&(lc[j]));
	      AddTerm2LinearConstraint(j,-1.0,&lcc);
	      hold=CropLinearConstraint(ZERO,ANY_TYPE_VAR,borig,&(cs->orig_variables),&lcc);
	      if (!hold) 
		printf("\nNon intersecting ranges (II)\n");
	      DeleteLinearConstraint(&lcc);
	    }
	}

      if (hold)
	{
	  hold=ReplaceVariableInEquations(epsilon,id,&lcr,&(cs->equations));
	  RemoveVariable(id,&(cs->variables));

	  #if (_DEBUG>6)
	    if(hold)
	      {
		char **varNames;
		
		printf("%%=======================================================\n");
		printf("%% One less variable (replaced)\n"); 
		printf("%%****************************************\n");
		PrintVariables(stdout,&(cs->variables));
		
		nv=NVariables(&(cs->variables));
		NEW(varNames,nv,char *);
		GetVariableNames(varNames,&(cs->variables));
		PrintEquations(stdout,varNames,&(cs->equations));
		free(varNames);
	      }
	  #endif
	}

      DeleteLinearConstraint(&lcr);
    }
  #if (_DEBUG>5)
    free(varNamesO);
  #endif
  free(systemVars);
  return(hold);
}

/*
  Simplifies a CuikSystem removing variables have constant value and those
  that depend linearly on other variables. Moreover, a primitive (but numerically
  save) form of Gaussian elimination is performed to remove as more variables
  and equations as possible.
  More elaborate forms of system simplifications are not implemented because they
  result in numerical errors (that can change the system solutions).
  The output mappings give information about how the original and the simplified
  systems are related.

  This is part of the UpdateCuikSystem.
*/
boolean SimplifyCuikSystem(Tparameters *p,TCuikSystem *cs)
{
  unsigned int i,nv,nvn,newVarID;
  boolean *replaced;
  TLinearConstraint *lc,lcS;
  boolean changed,anyChange,hold;
  char *name1;
  Tbox borig,bsimp;
  unsigned int nTerms,m,k;
  Tinterval error;
  unsigned int simplificationLevel;
  
  simplificationLevel=(unsigned int)(GetParameter(CT_SIMPLIFICATION_LEVEL,p));

  /* Matrix equations or non-polynomial equations -> at most variable replacement */
  if ((!cs->scalar)||((!PolynomialEquations(&(cs->orig_equations)))&&(simplificationLevel>1)))
    simplificationLevel=(simplificationLevel>2?2:simplificationLevel); 

  #if (_DEBUG>6)
    {
      char **varNames;
      
      printf("%%=======================================================\n");
      printf("%% Original system\n"); 
      printf("%%****************************************\n");
      PrintVariables(stdout,&(cs->orig_variables));
      
      nv=NVariables(&(cs->orig_variables));
      NEW(varNames,nv,char *);
      GetVariableNames(varNames,&(cs->orig_variables));
      PrintEquations(stdout,varNames,&(cs->orig_equations));
      free(varNames);
    }
  #endif


  /* Get a copy of the original cuiksystem */
  CopyVariables(&(cs->variables),&(cs->orig_variables));
  CopyEquations(&(cs->equations),&(cs->orig_equations));

  nv=NVariables(&(cs->orig_variables)); /* number of variables in the original system */

  NEW(replaced,nv,boolean);
  NEW(lc,nv,TLinearConstraint);
  
  BoxFromVariables(&borig,&(cs->orig_variables)); /*original ranges to be possibly reduced during
						    simplification */
  for(i=0;i<nv;i++)
    {
      replaced[i]=FALSE;
      InitLinearConstraint(&(lc[i]));
    }

  hold=TRUE; /* in the simplification process we can discover that the input system
	        is inconsitent (i.e., that it does not hold)*/
 
  CSRemoveUnusedVars(p,cs); /* This is done even without simplification */

  if (simplificationLevel>0) /* For detailed debug, systems are not simplified */
    { 
      hold=CSRemoveVarsWithCtRange(p,replaced,lc,&borig,cs);
    
      anyChange=TRUE; /* Set to TRUE to trigger the simplification process */
      while((hold)&&(anyChange))
	{
	  anyChange=FALSE; /* Will be set to TRUE if at least one variable is removed
			      in the loop below */
	  nTerms=0; /* First we try to remove ct variables, then scaled ones,i.e., we
		       progressivelly increase the number of terms used in the
		       replacements. */
	  while((hold)&&(nTerms<=MAX_TERMS_SIMP)) /*hard-coded maximum complexity of the simplifications*/
	    {
	      hold=CSRemoveLCVars(p,simplificationLevel,nTerms,&changed,replaced,lc,&borig,cs);
	      anyChange=((anyChange)||(changed));
	      if (changed)
		nTerms=0;
	      else
		nTerms++;
	    }

	  /* At this point no more ct or scaled varibles can be removed. Try to
	     simplify the problem via Gaussian elimination*/
	  if ((hold)&&(anyChange))
	    {
	      anyChange=FALSE;
	      do {
		changed=GaussianElimination(&(cs->equations));
		anyChange=((anyChange)||(changed));
	      } while (changed);

	      #if (_DEBUG>6)
	      {
		char **varNames;
		unsigned int nvg;

		printf("%%=======================================================\n");
		printf("%% After gaussian elimination\n"); 
		printf("%%****************************************\n");
		PrintVariables(stdout,&(cs->variables));
	      
		nvg=NVariables(&(cs->variables));
		NEW(varNames,nvg,char *);
		GetVariableNames(varNames,&(cs->variables));
		PrintEquations(stdout,varNames,&(cs->equations));
		free(varNames);
	      }
	      #endif
	    }
	} 
    }

  #if(_DEBUG>4)
    if (hold)
      {
	char **varNames;
	unsigned int nvg;

	printf("%%=======================================================\n");
	printf("%%FINAL SIMPLIFIED SYSTEM\n"); 
	printf("%%****************************************\n");
	PrintVariables(stdout,&(cs->variables));
	
	nvg=NVariables(&(cs->variables));
	NEW(varNames,nvg,char *);
	GetVariableNames(varNames,&(cs->variables));
	PrintEquations(stdout,varNames,&(cs->equations));
	free(varNames);
      }
    else
      printf("Inconsistent input system\n");
  #endif

  if (hold)
    {
      /* Get a copy of the simplified but not still dummified cuiksystem */
      CopyVariables(&(cs->simp_variables),&(cs->variables));
      CopyEquations(&(cs->simp_equations),&(cs->equations));

      /*The final step is to dummify the cuiksystem*/
      DummifyCuikSystem(p,cs);
 
      /* Cache information in the simplified equations just
         in case we want to efficiently evalute its equalities.
         This is done, for instance, in the (cuik)gradient */
      CacheScalarEQUInfo(&(cs->simp_equations));
      
      /*define the mappings from the gathered information*/

      NEW(cs->orig2sd,1,Tmapping);
      NEW(cs->orig2s,1,Tmapping);

      InitMapping(&(cs->orig_variables),&(cs->variables),cs->orig2sd);
      InitMapping(&(cs->orig_variables),&(cs->simp_variables),cs->orig2s);

      /* now we complement the default initialization with the replacements computed above */
      for(i=0;i<nv;i++)
	{
	  if (replaced[i])
	    {
	      m=GetNumTermsInLinearConstraint(&(lc[i]));
	      InitLinearConstraint(&lcS);
	      for(k=0;k<m;k++)
		{
		  name1=GetVariableName(GetVariable(GetLinearConstraintVariable(k,&(lc[i])),&(cs->orig_variables)));
		  newVarID=GetVariableID(name1,&(cs->variables));
		  
		  AddTerm2LinearConstraint(newVarID,GetLinearConstraintCoefficient(k,&(lc[i])),&lcS);
		}
	      GetLinearConstraintError(&error,&(lc[i]));
	      AddCt2LinearConstraint(-IntervalCenter(&error),&lcS);
	      
	      SetOriginalVarRelation(i,&lcS,cs->orig2sd);
	      SetOriginalVarRelation(i,&lcS,cs->orig2s);

	      DeleteLinearConstraint(&lcS);
	    }
	}

      #if(_DEBUG>4)
        if (hold)
	  {
	    char **varNames;
	    unsigned int nvg;

	    fprintf(stderr,"%%=======================================================\n");
	    fprintf(stderr,"%%FINAL final SIMPLIFIED SYSTEM\n"); 
	    fprintf(stderr,"%%****************************************\n");
	    PrintVariables(stderr,&(cs->variables));
	
	    nvg=NVariables(&(cs->variables));
	    NEW(varNames,nvg,char *);
	    GetVariableNames(varNames,&(cs->variables));
	    PrintEquations(stderr,varNames,&(cs->equations));
	    free(varNames);
	    fprintf(stderr,"\n\n");
	  }
	else
	  printf("Inconsistent input system\n");
      #endif

      SimpleFromOriginal(&borig,&bsimp,cs->orig2s);
      nvn=NVariables(&(cs->simp_variables)); 
      for(i=0;i<nvn;i++)
	SetVariableInterval(GetBoxInterval(i,&bsimp),GetVariable(i,&(cs->simp_variables)));
      DeleteBox(&bsimp);

      SimpleFromOriginal(&borig,&bsimp,cs->orig2sd);
      nvn=NVariables(&(cs->variables)); 
      for(i=0;i<nvn;i++)
	SetVariableInterval(GetBoxInterval(i,&bsimp),GetVariable(i,&(cs->variables)));
      DeleteBox(&bsimp);
    }

  DeleteBox(&borig);

  /* free the information used for the mapping */
  for(i=0;i<nv;i++)
    DeleteLinearConstraint(&lc[i]);
  free(replaced);
  free(lc);

  return(hold);
}

/*
  Removes the information stored in the cuiksystem during the update
*/
void UnUpdateCuikSystem(TCuikSystem *cs)
{
  
  if (cs->updated)
    {
      /*Removes cached information that is used during solving*/
     
      /*Firt the box sorting information*/
      if (cs->searchMode==MINIMIZATION_SEARCH)
	{
	  DeleteEquation(&(cs->eqMin));
	  DeleteEquation(&(cs->simp_eqMin));
	}
      

      /*Now the information about the simplified+dummified system*/
      if (cs->orig2sd!=NULL)
	{
	  DeleteMapping(cs->orig2sd);
	  free(cs->orig2sd);
	  cs->orig2sd=NULL;
	}

      cs->nequations=0;
      cs->nvariables=0;  
      if (cs->systemVar!=NULL) 
	free(cs->systemVar);
      cs->systemVar=NULL;
      if (cs->notDummyVar!=NULL)
	free(cs->notDummyVar);
      cs->notDummyVar=NULL;
      if (cs->varType!=NULL)
	free(cs->varType);
      cs->varType=NULL;

      DeleteEquations(&(cs->equations));
      DeleteVariables(&(cs->variables));

      /*Now remove the information about the simplified system*/
      if (cs->orig2s!=NULL)
	{
	  DeleteMapping(cs->orig2s);
	  free(cs->orig2s);
	  cs->orig2s=NULL;
	}
      
      if (cs->simp_nequations>0)
	DeleteJacobian(&(cs->J));

      cs->simp_nequations=0;
      cs->simp_nvariables=0;;
      cs->simp_nee=0;

      DeleteEquations(&(cs->simp_equations));
      DeleteVariables(&(cs->simp_variables));

      if (cs->simp_tp!=NULL)
	free(cs->simp_tp);

      /*Finally remove the information about the original system*/ 
      cs->orig_nequations=0;
      cs->orig_nvariables=0;  
      if (cs->orig_systemVar!=NULL) 
	free(cs->orig_systemVar);
      cs->orig_systemVar=NULL;
      if (cs->orig_notDummyVar!=NULL)
	free(cs->orig_notDummyVar);
      cs->orig_notDummyVar=NULL;

      free(cs->orig_varNames);
      cs->orig_varNames=NULL;

      /*Mark the system as not updated*/
      cs->updated=FALSE;

      /*We assume the system to be consistent although this value is not
        used unless cs->update is TRUE*/
      cs->consistent=TRUE;
    }
}

/*
  Simplifies the CuikSystem and caches information that is useful during 
  solving (cached->faster access).
*/
boolean UpdateCuikSystem(Tparameters *p,TCuikSystem *cs)
{
  if (!cs->updated)
    { 
      unsigned int j;
      boolean found;

      /* we update even if we have no equations to be able to deal
	 with systems without equations (non constrained problems)
	 In this case cuik is a standard approximated cell decomposition 
	 approach
       */
      cs->consistent=SimplifyCuikSystem(p,cs);
      
      if (cs->consistent)
	{
	  /* Update the information in the original system */
	  cs->orig_nequations=NEquations(&(cs->orig_equations));
	  cs->orig_nvariables=NVariables(&(cs->orig_variables));

	  if ((cs->orig_nequations>0)&&(cs->orig_nvariables==0))
	    Error("System with equations but without variables");

	  if (cs->orig_nvariables==0)
	    {
	      cs->orig_systemVar=NULL;
	      cs->orig_notDummyVar=NULL;
	      cs->orig_varNames=NULL;
	    }
	  else
	    {
	      NEW(cs->orig_systemVar,cs->orig_nvariables,boolean);
	      NEW(cs->orig_notDummyVar,cs->orig_nvariables,boolean);
	  
	      /* Note that orig_systemVar include the secodary variables while
	         systemVar (the one for the simplified/dummified system) keeps
	         the difference between system and secondary variables */
	      for(j=0;j<cs->orig_nvariables;j++)
		{
		  cs->orig_systemVar[j]=((IsSystemVariable(j,&(cs->orig_variables)))||
					 (IsSecondaryVariable(j,&(cs->orig_variables)))||
					 (!IsPositionVariable(j,&(cs->orig_variables))));
		  cs->orig_notDummyVar[j]=!IsDummyVariable(j,&(cs->orig_variables));
		}

	      NEW(cs->orig_varNames,cs->orig_nvariables,char *);
	      GetVariableNames(cs->orig_varNames,&(cs->orig_variables));
	    }

	  /* Update the simplifed cuiksystem */
	  cs->simp_nequations=NEquations(&(cs->simp_equations));
	  cs->simp_nvariables=NVariables(&(cs->simp_variables));
	  cs->simp_nee=NEqualityEquations(&(cs->simp_equations));
	  cs->simp_empty=((cs->simp_nvariables==0)&&(cs->simp_nequations==0));

	  if (cs->simp_empty)
	    cs->simp_tp=NULL;
	  else
	    {
	      GetVariablesTopology(&(cs->simp_tp),&(cs->simp_variables));
	      found=FALSE;
	      j=0;
	      while ((!found)&&(j<cs->simp_nvariables))
		{
		  found=(cs->simp_tp[j]!=TOPOLOGY_R);
		  j++;
		}
	      if (!found)
		{
		  free(cs->simp_tp);
		  cs->simp_tp=NULL;
		}
	    }
	  
	  if (cs->simp_nequations>0)
	    InitJacobian(&(cs->simp_variables),&(cs->simp_equations),&(cs->J));

	  /* Update the information in the simplified+dummified cuiksystem*/
	  cs->nequations=NEquations(&(cs->equations));
	  cs->nvariables=NVariables(&(cs->variables));
	  cs->empty=((cs->nvariables==0)||(cs->nequations==0));

	  if (cs->nvariables==0)
	    {
	      cs->systemVar=NULL;
	      cs->notDummyVar=NULL;
	      cs->varType=NULL;
	    }
	  else
	    {
	      NEW(cs->systemVar,cs->nvariables,boolean);
	      NEW(cs->notDummyVar,cs->nvariables,boolean);
	      NEW(cs->varType,cs->nvariables,unsigned int);
	  
	      for(j=0;j<cs->nvariables;j++)
		{
		  cs->systemVar[j]=((IsSystemVariable(j,&(cs->variables)))||
				    (IsSecondaryVariable(j,&(cs->variables)))||
				    (!IsPositionVariable(j,&(cs->orig_variables))));
		  cs->notDummyVar[j]=!IsDummyVariable(j,&(cs->variables));
		  cs->varType[j]=GetVariableTypeN(j,&(cs->variables));
		}
	    }

	  /* Update the information about the sorting criteria for boxes */
	  if (cs->searchMode==MINIMIZATION_SEARCH)
	    {
	      if (GetNumMonomials(&(cs->orig_eqMin))==0)
		{
		  ResetEquation(&(cs->orig_eqMin));
		  cs->searchMode=DEPTH_FIRST_SEARCH;
		}
	      else
		{
		  RewriteEquation2Simp(GetParameter(CT_EPSILON,p),
				       cs->orig2sd,&(cs->eqMin),&(cs->orig_eqMin));
		  RewriteEquation2Simp(GetParameter(CT_EPSILON,p),
				       cs->orig2s,&(cs->simp_eqMin),&(cs->orig_eqMin));
		}
	    }

	  /* Mark the system as updated )(althogh it might not be consistent) */
	  cs->updated=TRUE;
	}
    }

  return(cs->consistent);
}

/*
  Selects one dimension along which to split box 'b'. The dimension can
  be selected according to the size or according to the error that each
  variable induce in each equation.
  The output is a index in the simplified system
 */
unsigned int ComputeSplitDimInt(Tparameters *p,Tbox *b,TCuikSystem *cs)
{
  
  if (!UpdateCuikSystem(p,cs))
    Error("Inconsistent cuiksystem in ComputeSplitDimInt");

  if (cs->nvariables==0)
    {
      Error("Splitting an empty cuiksystem");
      return(NO_UINT);
    }
  else
    {
      unsigned int i;
      Tinterval *is;
      double *splitDim;
      unsigned int *d;
      unsigned int n;
      double m,s;
      unsigned int splitType;
      double epsilon;

      epsilon=GetParameter(CT_EPSILON,p);
      splitType=(unsigned int)(GetParameter(CT_SPLIT_TYPE,p));

      NEW(splitDim,cs->nvariables,double);
      NEW(d,cs->nvariables,unsigned int);

      is=GetBoxIntervals(b);

      if ((cs->nequations>0)&&(splitType==1))
	{
	  /* Split based on the linearization error */
	  
	  for(i=0;i<cs->nvariables;i++)
	    splitDim[i]=0.0;
      
	  /*Add the error contribution*/
	  for(i=0;i<cs->nequations;i++)
	    UpdateSplitWeight(i,splitDim,b,&(cs->equations));

	  /*Do not split along unbounded or too small variables*/
	  for(i=0;i<cs->nvariables;i++)
	    {
	      s=IntervalSize(&(is[i]));
	      if ((s<10*epsilon)||(s>=INF))
		splitDim[i]=0.0;
	    }
	}
      else
	{
	  if (splitType!=2) 
	    {
	      /*size-based split or error-based split without any equation*/

	      for(i=0;i<cs->nvariables;i++)
		{
		  s=IntervalSize(&(is[i]));
		  if (s<INF)
		    splitDim[i]=s;
		  else
		    splitDim[i]=0.0;
		}
	    }
	  else
	    {
	      /*splitType==2 -> random selection of the split dimension */ 
	      for(i=0;i<cs->nvariables;i++)
		{
		  s=IntervalSize(&(is[i]));
		  if ((s>10*epsilon)&&(s<INF))
		    splitDim[i]=1.0;
		  else
		    splitDim[i]=0.0;
		}
	      
	    }
	}

      m=-1.0;
      n=0;
      for(i=0;i<cs->nvariables;i++)
	{
	  if (cs->systemVar[i])
	    {
	      if (splitDim[i]>m)
		{
		  m=splitDim[i];
		  d[0]=i;
		  n=1;
		}
	      else
		{
		  if (splitDim[i]==m)
		    {
		      d[n]=i;
		      n++;
		    }
		}
	    }
	}
 
      if (n>0) 
	{
          #if (RANDOMNESS)
	    i=d[randomMax(n-1)];
	  #else
	    i=d[0];
	  #endif
	}
      else
	{
	  Warning("There is no way where to bisect the box");
	  i=randomMax(cs->nvariables-1);
	}

      free(d);
      free(splitDim);

      return(i);
    }
}

void SaveCSState(char *fname,Tlist *lb,TCuikSystem *cs)
{  
  FILE *f;
  char *tmpName;
  double tm;

  /*We initially save to a temporary file and then we rename it
    This increases the atomiticy of this operation (if the state
    file is corrupted the recovery operation would fail) */
  NEW(tmpName,strlen(fname)+10,char);
  sprintf(tmpName,"%s.tmp",fname);
  
  /*open in binary mode*/
  f=fopen(tmpName,"wb");
  if (!f)
    Error("Could not open file for saving CSState");

  tm=GetElapsedTime(&(cs->st));
  fwrite(&tm,sizeof(double),1,f);
  SaveStatistics(f,&(cs->st));
  SaveListOfBoxes(f,lb);

  fclose(f);

  remove(fname);
  rename(tmpName,fname);
  free(tmpName);
}

void LoadCSState(char *fname,Tlist *lb,TCuikSystem *cs)
{
  FILE *f;
  double tm;
  Titerator it;
  
  f=fopen(fname,"rb");
  if (!f)
    Error("Could not open file for loading CSState");

  fread(&tm,sizeof(double),1,f);
  LoadStatistics(f,&(cs->st));
  LoadListOfBoxes(f,lb);

  fclose(f);
  
  InitIterator(&it,lb);
  First(&it);
  if (cs->nvariables!=GetBoxNIntervals((Tbox *)GetCurrent(&it)))
    Error("The saved .state and the problem dimensionality do not match");

  /*Pretend that the process was started tm seconds before now*/
  SetInitialTime(GetTime(&(cs->st))-tm,&(cs->st));
}


/************************************************************************/
/************************************************************************/
/************************************************************************/

/*
  Warms up the cuiksystem structure
*/
void InitCuikSystem(TCuikSystem *cs)
{
  InitConstants(&(cs->constants));

  InitVariables(&(cs->orig_variables));
  InitEquations(&(cs->orig_equations));

  /* cs->variables and cs->equations are initialized
     via Copy when simplifying the system*/ 
  cs->empty=TRUE;
  cs->simp_empty=TRUE;

  cs->updated=FALSE;
  cs->consistent=TRUE; /*this is not used unless updated=TRUE*/

  cs->scalar=TRUE;

  cs->nequations=0;
  cs->nvariables=0;

  cs->systemVar=NULL;
  cs->notDummyVar=NULL;
  cs->varType=NULL;

  cs->orig2sd=NULL;

  cs->orig2s=NULL;
  cs->simp_tp=NULL;

  cs->orig_nequations=0;
  cs->orig_nvariables=0;

  cs->orig_systemVar=NULL;
  cs->orig_notDummyVar=NULL;

  cs->searchMode=DEPTH_FIRST_SEARCH;
  InitEquation(&(cs->orig_eqMin));
}

void VerifyCuikSystem(Tparameters *p,TCuikSystem *cs)
{
  if (!UpdateCuikSystem(p,cs))
    Error("Inconsistent input cuiksystem");
}

/*
  Copies one cuiksystem structure into another (that is assumed as
  initialized but empty).
*/
void CopyCuikSystem(TCuikSystem *cs_dst,TCuikSystem *cs_src)
{
  CopyConstants(&(cs_dst->constants),&(cs_src->constants));

  cs_dst->updated=cs_src->updated; 
  cs_dst->consistent=cs_src->consistent;
  cs_dst->empty=cs_src->empty;  
  cs_dst->scalar=cs_src->scalar;

  CopyStatistics(&(cs_dst->st),&(cs_src->st));

  cs_dst->searchMode=cs_src->searchMode;
  CopyEquation(&(cs_dst->orig_eqMin),&(cs_src->orig_eqMin));

  CopyEquations(&(cs_dst->orig_equations),&(cs_src->orig_equations));
  CopyVariables(&(cs_dst->orig_variables),&(cs_src->orig_variables));
 
  if (cs_dst->updated)
    {
      /*The simplified dummified system*/
      NEW(cs_dst->orig2sd,1,Tmapping);
      CopyMapping(cs_dst->orig2sd,cs_src->orig2sd);

      CopyEquations(&(cs_dst->equations),&(cs_src->equations));
      CopyVariables(&(cs_dst->variables),&(cs_src->variables));

      cs_dst->nequations=cs_src->nequations;
      cs_dst->nvariables=cs_src->nvariables;
      
      if (cs_dst->nvariables==0)
	{
	  cs_dst->systemVar=NULL;
	  cs_dst->notDummyVar=NULL;
	  cs_dst->varType=NULL;
	}
      else
	{
	  NEW(cs_dst->systemVar,cs_dst->nvariables,boolean);
	  memcpy(cs_dst->systemVar,cs_src->systemVar,sizeof(boolean)*cs_dst->nvariables);
	  
	  NEW(cs_dst->notDummyVar,cs_dst->nvariables,boolean);
	  memcpy(cs_dst->notDummyVar,cs_src->notDummyVar,sizeof(boolean)*cs_dst->nvariables);
	  
	  NEW(cs_dst->varType,cs_dst->nvariables,unsigned int);
	  memcpy(cs_dst->varType,cs_src->varType,sizeof(unsigned int)*cs_dst->nvariables);
	}
	
      if (cs_dst->searchMode==MINIMIZATION_SEARCH)
	{
	  CopyEquation(&(cs_dst->eqMin),&(cs_src->eqMin));
	  CopyEquation(&(cs_dst->simp_eqMin),&(cs_src->simp_eqMin));
	}


      /*The simplified system*/ 
      NEW(cs_dst->orig2s,1,Tmapping);
      CopyMapping(cs_dst->orig2s,cs_src->orig2s);

      cs_dst->simp_empty=cs_src->simp_empty;
      
      CopyEquations(&(cs_dst->simp_equations),&(cs_src->simp_equations));
      CopyVariables(&(cs_dst->simp_variables),&(cs_src->simp_variables));

      cs_dst->simp_nequations=cs_src->simp_nequations;
      cs_dst->simp_nvariables=cs_src->simp_nvariables;
      cs_dst->simp_nee=cs_src->simp_nee;

      if (cs_src->simp_tp!=NULL)
	{
	  NEW(cs_dst->simp_tp,cs_dst->simp_nvariables,unsigned int);
	  memcpy(cs_dst->simp_tp,cs_src->simp_tp,sizeof(unsigned int)*cs_dst->simp_nvariables);
	}
      else
	cs_dst->simp_tp=NULL;

      CopyJacobian(&(cs_dst->J),&(cs_src->J));

      /*Cached elements from the original system*/
      cs_dst->orig_nequations=cs_src->orig_nequations;
      cs_dst->orig_nvariables=cs_src->orig_nvariables;

      if (cs_dst->orig_nvariables==0)
	{
	  cs_dst->orig_systemVar=NULL;
	  cs_dst->orig_notDummyVar=NULL;
	  cs_dst->orig_varNames=NULL;
	}
      else
	{
	  NEW(cs_dst->orig_systemVar,cs_dst->orig_nvariables,boolean);
	  memcpy(cs_dst->orig_systemVar,cs_src->orig_systemVar,cs_dst->orig_nvariables*sizeof(boolean));

	  NEW(cs_dst->orig_notDummyVar,cs_dst->orig_nvariables,boolean);
	  memcpy(cs_dst->orig_notDummyVar,cs_src->orig_notDummyVar,cs_dst->orig_nvariables*sizeof(boolean));
	  
	  NEW(cs_dst->orig_varNames,cs_dst->orig_nvariables,char *);
	  GetVariableNames(cs_dst->orig_varNames,&(cs_dst->orig_variables));
	}
    }
  else
    {
      cs_dst->orig2sd=NULL;
      cs_dst->orig2s=NULL;

      cs_dst->nequations=0;
      cs_dst->nvariables=0;
      cs_dst->systemVar=NULL;  
      cs_dst->notDummyVar=NULL;
      cs_dst->varType=NULL;
      cs_dst->simp_tp=NULL;

      cs_dst->orig_nequations=0;
      cs_dst->orig_nvariables=0;
      cs_dst->orig_systemVar=NULL;  
      cs_dst->orig_notDummyVar=NULL;
      cs_dst->orig_varNames=NULL;
    }
}

void CuikSystemMerge(Tparameters *p,TCuikSystem *cs1,TCuikSystem *cs2,TCuikSystem *cs)
{
  unsigned int nvar1,nvar2;
  unsigned int i;

  InitCuikSystem(cs);

  MergeConstants(&(cs1->constants),&(cs2->constants),&(cs->constants));
  
  cs->empty=((cs1->empty)&&(cs2->empty)); 
  cs->simp_empty=((cs1->simp_empty)&&(cs2->simp_empty));

  cs->updated=FALSE; 
  cs->consistent=TRUE; /*not used untill updated==TRUE*/

  cs->scalar=((ScalarEquations(&(cs1->orig_equations)))&&
	      (ScalarEquations(&(cs->orig_equations))));

  cs->orig2sd=NULL;
  
  cs->nequations=0;
  cs->nvariables=0;
  cs->systemVar=NULL;  
  cs->notDummyVar=NULL;
  cs->varType=NULL;
  
  cs->orig_nequations=0;
  cs->orig_nvariables=0;
  cs->orig_systemVar=NULL;  
  cs->orig_notDummyVar=NULL;

  /* One of the sets of variables is supposed to be a sub-set of the
     other.
     If nvar1 is larger than the larger set was in cs1 and nothing has
     to be done*/
  CopyVariables(&(cs->orig_variables),&(cs1->orig_variables));
  nvar1=NVariables(&(cs1->orig_variables));
  nvar2=NVariables(&(cs2->orig_variables));
  for(i=nvar1;i<nvar2;i++)
    AddVariable2CS(GetVariable(i,&(cs2->orig_variables)),cs);

  CopyEquations(&(cs->orig_equations),&(cs1->orig_equations));
  MergeEquations(&(cs2->orig_equations),&(cs->orig_equations));

  cs->searchMode=cs1->searchMode;
  CopyEquation(&(cs->orig_eqMin),&(cs1->orig_eqMin));
  AccumulateEquations(&(cs2->orig_eqMin),1,&(cs->orig_eqMin));
}

double EvaluateEqMin(void *b,void *cs)
{
  double v=0;

  if (!((TCuikSystem *)cs)->updated)
    Error("The CuikSystem must be updated before using EvaluateEqMin");

  if (!((TCuikSystem *)cs)->consistent)
    Error("The CuikSystem must be consistent before using EvaluateEqMin");

  if (((TCuikSystem *)cs)->searchMode==MINIMIZATION_SEARCH)
    {      
      #if (EQ_MIN_IN_CENTER)
	unsigned int nv;
	double *p;
	unsigned int i;
	
	nv=NVariables(&(((TCuikSystem *)cs)->variables));
		
	NEW(p,nv,double);
	
	for(i=0;i<nv;i++)
	  p[i]=IntervalCenter(GetBoxInterval(i,(Tbox *)b));

	v=EvaluateWholeEquation(p,&(((TCuikSystem *)cs)->eqMin)); 

	free(p);
      #else
        Tinterval ie;
	double ct;

	ct=GetEquationValue(&(((TCuikSystem *)cs)->eqMin));
	
	EvaluateEquationInt(GetBoxIntervals((Tbox *)b),&ie,&(((TCuikSystem *)cs)->eqMin));
	IntervalOffset(&ie,-ct,&ie);

	/*v=LowerLimit(&ie);*/
	/*v=UpperLimit(&ie);*/
	v=IntervalCenter(&ie);
      #endif
    }
  return(v);
}

boolean CmpBoxesEquation(void *b1,void *b2,void *cs)
{
  return(EvaluateEqMin(b1,cs)<EvaluateEqMin(b2,cs));
}

void SetCSSearchMode(unsigned int sm,Tequation *eqMin,TCuikSystem *cs)
{
  if (cs->updated)
    UnUpdateCuikSystem(cs);
  
  switch(sm)
    {
    case DEPTH_FIRST_SEARCH:
      cs->searchMode=DEPTH_FIRST_SEARCH;
      break;
    case BREADTH_FIRST_SEARCH:
      cs->searchMode=BREADTH_FIRST_SEARCH;
      break;
    case MINIMIZATION_SEARCH:
      cs->searchMode=MINIMIZATION_SEARCH;
      DeleteEquation(&(cs->orig_eqMin));
      CopyEquation(&(cs->orig_eqMin),eqMin);
      break;
    default:
      Error("Unkonwn search mode in SetCSSearchMode");
    }
}

void AddTerm2SearchCriterion(double w,unsigned int v,double val,TCuikSystem *cs)
{
  if (w!=0.0)
    {
      Tequation eq;
      Tmonomial m;
      
      if (cs->updated)
	UnUpdateCuikSystem(cs);
  
      InitEquation(&eq);
      SetEquationCmp(EQU,&eq);
      InitMonomial(&m);
      
      AddCt2Monomial(w,&m);
      AddVariable2Monomial(NFUN,v,2,&m);
      AddMonomial(&m,&eq);
      ResetMonomial(&m);
      
      AddCt2Monomial(-w*2*val,&m);
      AddVariable2Monomial(NFUN,v,1,&m);
      AddMonomial(&m,&eq);
      ResetMonomial(&m);
      
      AddCt2Monomial(w*val*val,&m);
      AddMonomial(&m,&eq);
      ResetMonomial(&m);
      
      if (cs->searchMode==MINIMIZATION_SEARCH)
	AccumulateEquations(&eq,1,&(cs->orig_eqMin));
      else
	SetCSSearchMode(MINIMIZATION_SEARCH,&eq,cs);
      
      DeleteMonomial(&m);
      DeleteEquation(&eq);
    }
}

/*
  Adds a equation to the CuikSystem. 
  Equations as added by the user are not dummified. This helps
  when simplifying the system (dummify variables can prevent some
  simplifications or make them more "obscure")
  The dummificitaion is applied after the simplification of the
  system (see SimplifyCuikSystem)
*/
void AddEquation2CS(Tparameters *p,Tequation *eq,TCuikSystem *cs)
{
  if (cs->updated)
    UnUpdateCuikSystem(cs);

  if (eq!=NULL)
    AddEquation(eq,&(cs->orig_equations));
}

void AddMatrixEquation2CS(Tparameters *p,TMequation *eq,TCuikSystem *cs)
{
  if (cs->updated)
    UnUpdateCuikSystem(cs);

  if (eq!=NULL)
    {
      cs->scalar=FALSE;
      if (!SimplifiedMEquation(eq))
	Error("Adding a non-simplified matrix equation to the cuiksystem");
      //SimplifyMEquation(eq);
      AddMatrixEquation(eq,&(cs->orig_equations));
    }
}

/*
  Checks if the system has a variable with the given name.
  If so, we return the variable identifier.
  If not, we create a new variable
 */
unsigned int AddVariable2CS(Tvariable *v,TCuikSystem *cs)
{
  unsigned int id;

  if (cs->updated)
    UnUpdateCuikSystem(cs);

  id=GetVariableID(GetVariableName(v),&(cs->orig_variables));

  if (id==NO_UINT)
    id=AddVariable(v,&(cs->orig_variables));

  return(id);
}

/*
  Returns a copy of the variables stored in the CuikSystem
*/
void GetCSVariables(Tvariables *vs,TCuikSystem *cs)
{
  CopyVariables(vs,&(cs->orig_variables));
}

void GetCSVariableNames(char **varNames,TCuikSystem *cs)
{
  /* We do not use the cached orig_varnames since the cs
     can be non-updated */
  GetVariableNames(varNames,&(cs->orig_variables));
}

/*
  Returns the number of variables in the CuikSystem
*/
unsigned int GetCSNumVariables(TCuikSystem *cs)
{
  return(NVariables(&(cs->orig_variables)));
}

unsigned int GetCSNumSystemVariables(TCuikSystem *cs)
{
  return(GetNumSystemVariables(&(cs->orig_variables))+
	 GetNumSecondaryVariables(&(cs->orig_variables))+
	 GetNumVelocityVariables(&(cs->orig_variables))+
	 GetNumNonDynamicVariables(&(cs->orig_variables))
	 );
}

unsigned int GetCSNumNonDynamicVariables(TCuikSystem *cs)
{
  return(GetNumNonDynamicVariables(&(cs->orig_variables)));
}

/*
  Returns the number of system variables in the CuikSystem
*/
unsigned int GetCSNumNonDummyVariables(TCuikSystem *cs)
{
  return(NVariables(&(cs->orig_variables))-GetNumDummyVariables(&(cs->orig_variables)));
}

boolean CuikHasVelocity(Tparameters *p,TCuikSystem *cs)
{
  if (!UpdateCuikSystem(p,cs))
    Error("Inconsistent input cuiksystem");
  
  return((GetNumVelocityVariables(&(cs->simp_variables))>0)&&
	 (NVelocityEquations(&(cs->simp_equations))>0));
}

/* 
   Gets a copy of variable with ID 'n'
*/
void GetCSVariable(unsigned int n,Tvariable *v,TCuikSystem *cs)
{
  CopyVariable(v,GetVariable(n,&(cs->orig_variables)));
}

/*
  Sets a new range for variable with ID 'n'
*/
void SetCSVariableRange(unsigned int n,Tinterval *r,TCuikSystem *cs)
{ 
  if (cs->updated)
    UnUpdateCuikSystem(cs); /* Variables with ct range are simplified in
			       the UpdateCuikSystem */

  SetVariableInterval(r,GetVariable(n,&(cs->orig_variables)));
}

/*
  Gets the ID of the variable with the given name
*/
unsigned int GetCSVariableID(char *name,TCuikSystem *cs)
{
  return(GetVariableID(name,&(cs->orig_variables)));
}

char *GetCSVariableName(unsigned int id,TCuikSystem *cs)
{
  return(VariableName(id,&(cs->orig_variables)));
}

char *GetCSSystemVariableName(unsigned int id,TCuikSystem *cs)
{
  unsigned int i,n,k;
  boolean found;
  char *name=NULL;
  
  n=NVariables(&(cs->orig_variables));

  k=0;
  found=FALSE;
  for(i=0;((!found)&&(i<n));i++)
    if ((IsSystemVariable(i,&(cs->orig_variables)))||
	(IsSecondaryVariable(i,&(cs->orig_variables)))||
	(!IsPositionVariable(i,&(cs->orig_variables))))
      {
	if (k==id)
	  {
	    name=VariableName(i,&(cs->orig_variables));
	    found=TRUE;
	  }
	k++;
      }
  return(name);
}

boolean IsSystemVarInSimpCS(Tparameters *p,char *v,TCuikSystem *cs)
{
  unsigned int n;

  if (!UpdateCuikSystem(p,cs))
    Error("Inconsistent input cuiksystem");
  
  n=GetVariableID(v,&(cs->simp_variables));
  return((n!=NO_UINT)&&
	 ((IsSystemVariable(n,&(cs->simp_variables)))||
	  (IsSecondaryVariable(n,&(cs->simp_variables)))||
	  (!IsPositionVariable(n,&(cs->simp_variables)))));
}

/*
  Returns an array of booleans with sv[i]=TRUE if variable
  'i' is a system variable.
  Also returns the number of variables in the CuikSystem
*/
unsigned int GetCSSystemVars(boolean **sv,TCuikSystem *cs)
{
  unsigned int i,n;

  n=NVariables(&(cs->orig_variables));
  NEW(*sv,n,boolean);

  for(i=0;i<n;i++)
    (*sv)[i]=((IsSystemVariable(i,&(cs->orig_variables)))||
	      (IsSecondaryVariable(i,&(cs->orig_variables)))||
	      (!IsPositionVariable(i,&(cs->orig_variables))));
  return(n);
}

unsigned int GetCSPositionVars(boolean **pv,TCuikSystem *cs)
{
  unsigned int i,n;

  n=NVariables(&(cs->orig_variables));
  NEW(*pv,n,boolean);

  for(i=0;i<n;i++)
    (*pv)[i]=IsPositionVariable(i,&(cs->orig_variables));
  
  return(n);
}

unsigned int GetCSPositionEqs(boolean **pe,TCuikSystem *cs)
{
  unsigned int i,n;

  n=NEquations(&(cs->orig_equations));
  if (n>0)
    {
      NEW(*pe,n,boolean);
      
      for(i=0;i<n;i++)
	(*pe)[i]=IsPositionEquation(i,&(cs->orig_equations));
    }
  else
    *pe=NULL;
  
  return(n);
}


unsigned int GetCSPositionVelocityVars(boolean **pv,TCuikSystem *cs)
{
  unsigned int i,n;

  n=NVariables(&(cs->orig_variables));
  NEW(*pv,n,boolean);

  for(i=0;i<n;i++)
    (*pv)[i]=(!IsNonDynamicVariable(i,&(cs->orig_variables)));
  
  return(n);
}

unsigned int GetCSPositionVelocityEqs(boolean **pe,TCuikSystem *cs)
{
  unsigned int i,n;

  n=NEquations(&(cs->orig_equations));
  if (n>0)
    {
      NEW(*pe,n,boolean);
      
      for(i=0;i<n;i++)
	(*pe)[i]=(!IsNonDynamicEquation(i,&(cs->orig_equations)));
    }
  else
    *pe=NULL;
  
  return(n);
}

unsigned int GetCSVarTopology(unsigned int vID,TCuikSystem *cs)
{
  return(GetVariableTopology(GetVariable(vID,&(cs->orig_variables))));
}

/*
  Returns a copy of the equations in the cuiksystem
*/
void GetCSEquations(Tequations *eqs,TCuikSystem *cs)
{
  CopyEquations(eqs,&(cs->orig_equations));
}

/*
  Returns a copy of equation 'n' in the CuikSystem
*/
void GetCSEquation(unsigned int n,Tequation *eq,TCuikSystem *cs)
{
  if (!cs->scalar)
    Error("GetCSEquation only operates on scalar systems");

  CopyEquation(eq,GetEquation(n,&(cs->orig_equations)));
}

boolean IsCSPolynomial(TCuikSystem *cs)
{
  return(PolynomialEquations(&(cs->orig_equations)));
}

boolean IsCSScalar(TCuikSystem *cs)
{
  return(cs->scalar);
}

/*
  Returns the number of equations in the CuikSytem
*/
unsigned int GetCSNumEquations(TCuikSystem *cs)
{
  return(NEquations(&(cs->orig_equations)));
}

void GetCSJacobian(TJacobian *J,TCuikSystem *cs)
{
  InitJacobian(&(cs->orig_variables),&(cs->orig_equations),J);
}

unsigned int GetSimpCSTopology(Tparameters *p,
			       unsigned int **t,TCuikSystem *cs)
{
  if (!UpdateCuikSystem(p,cs))
    Error("Inconsistent input cuiksystem");

  return(GetVariablesTopology(t,&(cs->simp_variables)));
}

unsigned int GetCSTopology(Tparameters *p,
			   unsigned int **t,TCuikSystem *cs)
{
  return(GetVariablesTopology(t,&(cs->orig_variables)));
}

void GetSimpCSJacobian(Tparameters *p,TJacobian *J,TCuikSystem *cs)
{
  if (!UpdateCuikSystem(p,cs))
    Error("Inconsistent input cuiksystem");
  InitJacobian(&(cs->simp_variables),&(cs->simp_equations),J);
}

boolean GetSimpCSNJacobian(Tparameters *p,TNJacobian *nJ,TCuikSystem *cs)
{
  if (!UpdateCuikSystem(p,cs))
    Error("Inconsistent input cuiksystem");
  
  return(InitNJacobian(&(cs->simp_variables),&(cs->simp_equations),nJ));
}

boolean GetSimpCSNHessian(Tparameters *p,TJacobian *sJ,TNHessian *nH,TCuikSystem *cs)
{
  if (!UpdateCuikSystem(p,cs))
    Error("Inconsistent input cuiksystem");
  return(InitNHessian(&(cs->simp_variables),&(cs->simp_equations),sJ,nH));
}
    
void AddJacobianEquationsInt(Tparameters *p,boolean *selectedVars,TJacobian *J,TCuikSystem *cs)
{
  Tinterval one_one,zero_one;
  unsigned int *nvl;
  Tvariable v;
  char vname[100];
  Tequation eq,eq1;
  unsigned int i,j,nvars,neqs;

  if (!cs->scalar)
    Error("AddJacobianEquationsInt assumes scalar equations");
  
  GetJacobianSize(&neqs,&nvars,J);
  
  NewInterval(-1.0,1.0,&one_one);
  NewInterval( 0.0,1.0,&zero_one);

  /*define the lambda/v variables*/
  NEW(nvl,neqs,unsigned int);
  for(i=0;i<neqs;i++)
    {
      sprintf(vname,"_lambda_%u",i);
      NewVariable(SYSTEM_VAR,vname,&v);
      SetVariableInterval((i==0?&zero_one:&one_one),&v);

      nvl[i]=AddVariable2CS(&v,cs);
      
      DeleteVariable(&v);
    }

  /* Lambdas must be normalized */
  GenerateGeneralNormEquation(neqs,nvl,1.0,&eq);
  AddEquation2CS(p,&eq,cs);
  DeleteEquation(&eq);
  
  /*define the linear combination using the lambda/v variables */
  for(j=0;j<nvars;j++)
    { 
      if ((selectedVars==NULL)||(selectedVars[j]))
	{
	  InitEquation(&eq);
	  SetEquationCmp(EQU,&eq);
	  SetEquationType(SYSTEM_EQ,&eq);
	      
	  for(i=0;i<neqs;i++)
	    {
	      CopyEquation(&eq1,GetJacobianEquation(i,j,J));
	      VarScaleEquation(nvl[i],&eq1);
	      AccumulateEquations(&eq1,1.0,&eq);
	      DeleteEquation(&eq1);
	    }
	      
	  AddEquation2CS(p,&eq,cs);
	  DeleteEquation(&eq);
	}
    }
}

void AddJacobianEquations(Tparameters *p,boolean *selectedVars,TCuikSystem *cs)
{
  unsigned int i,ns;
  TJacobian J;

  if (!cs->scalar)
    Error("AddJacobianEquations assumes scalar equations");
  
  if (!UpdateCuikSystem(p,cs))
    Error("Inconsistent input cuiksystem");

  if (selectedVars==NULL)
    ns=cs->orig_nvariables;
  else
    {
      ns=0;
      for(i=0;i<cs->orig_nvariables;i++)
	if (selectedVars[i]) ns++;
    }

  if ((cs->orig_nequations>0)&&(ns>0))
    {
      GetCSJacobian(&J,cs);
      AddJacobianEquationsInt(p,selectedVars,&J,cs);

      DeleteJacobian(&J);
      UnUpdateCuikSystem(cs);
    }
}

void AddVelocityEquations(Tparameters *p,double *vl,TCuikSystem *cs)
{
  TJacobian J;

  /* If dynamic systems dymmification is not necessary */
  ChangeParameter(CT_DUMMIFY,0,p);
  
  if (!UpdateCuikSystem(p,cs))
    Error("Inconsistent input cuiksystem");

   /* If the system is not empty (has some variables) and we
      do not have velocity equations (do not re-add them!)    */
  if ((cs->simp_nvariables>0)&& 
      (GetNumVelocityVariables(&(cs->simp_variables))==0)) 
    {
      Tinterval all;
      char vname[200],*vn;
      Tvariable v;
      unsigned int *nv;
      unsigned int i,nvs,nes;
      double mv;
      boolean *selectedVars;

      mv=GetParameter(CT_DEFAULT_MAX_VELOCITY,p);

      nvs=cs->simp_nvariables; /* keep the number. When inserting new variables
				  this value is reset (unupdated!).*/
      nes=cs->simp_nee; /* keep this for the same reason */

      /* We have to do this before adding varibles (i.e., while the simplified
         system is still defined) */
      if (nes>0)
	{
	  /*
	    Note that for open-loop systems the number of equality
	    equations can be zero (but not the number of variables),
	  */
	  InitPositionJacobian(&(cs->simp_variables),&(cs->simp_equations),&J);
	
	  /* encode the simplified Jacobian with the variables in the original system */
	  RewriteJacobian2Orig(cs->orig2s,&J);
	  /* Here we have to add J*v=0 not J^t*v=0 as it is done in AddJacobianEquationsInt !! */
	}
      
      /* maximum speed is encoded in the parameter file (may not be used if the joint
	 has it own maximum velocity) */
      NewInterval(-mv,+mv,&all); 
      
      NEW(nv,nvs,unsigned int);
      /* the variable mapping disappears as soon as we add a new variable to the system 
         and thus we have to cache the original variable identifiers */
      for(i=0;i<nvs;i++)
	nv[i]=GetVarIDInOriginal(i,cs->orig2s);

      /* Generate the differential variables */
      NEW(selectedVars,nvs,boolean);
      for(i=0;i<nvs;i++)
	{
	  /* May not consider secondary variables, but this is more an issue
	     than a solution. */
	  //selectedVars[i]=TRUE; //IsSystemVariable(nv[i],&(cs->orig_variables));
	  selectedVars[i]=IsPositionVariable(nv[i],&(cs->orig_variables)); 
	  if (selectedVars[i])
	    {
	      vn=VariableName(nv[i],&(cs->orig_variables));
	      if (vn[0]=='_')
		sprintf(vname,"_diff(%.150s)",&(vn[1]));
	      else
		sprintf(vname,"_diff(%.150s)",vn);
	      NewVariable(VELOCITY_VAR,vname,&v);
	      if (vl!=NULL)
		{
		  NewInterval(-vl[nv[i]],+vl[nv[i]],&all);
		  SetVariableInterval(&all,&v);
		}
	      else
		SetVariableInterval(&all,&v);

	      /* adding the diff variable */
	      nv[i]=AddVariable2CS(&v,cs);
	  
	      DeleteVariable(&v);
	    }
	}
      
      if (nes>0)
	{
	  /* Generate the velocity equations */
	  JacobianLinearCombination(selectedVars,nv,&(cs->orig_equations),&J);
	  DeleteJacobian(&J);
	}
      
      /* Release allocated memory */
      free(selectedVars);
      free(nv);
      UnUpdateCuikSystem(cs);
    }
}

void AddSimplifiedJacobianEquations(Tparameters *p,boolean *selectedVars,TCuikSystem *cs)
{
  unsigned int neqs,nvars,i,ns;
  boolean *simpSelectedVars;
  unsigned int simpID,nt;
  TLinearConstraint lc;
  TCuikSystem csOrig;
  
  if (!cs->scalar)
    Error("AddSimplifiedJacobianEquations assumes scalar equations");
  
  if (!UpdateCuikSystem(p,cs))
    Error("Inconsistent input cuiksystem");

  CopyCuikSystem(&csOrig,cs);

  neqs=cs->simp_nee;
  nvars=cs->simp_nvariables;

  NEW(simpSelectedVars,nvars,boolean);
  if (selectedVars==NULL)
    ns=nvars;
  else
    {
      /*Translated the selected vars from original to simplified*/
      for(i=0;i<nvars;i++)
	simpSelectedVars[i]=TRUE;

      ns=0;
      for(i=0;i<cs->orig_nvariables;i++)
	{
	  if (!selectedVars[i]) 
	    {
	      GetOriginalVarRelation(i,&lc,cs->orig2s);
	      nt=GetNumTermsInLinearConstraint(&lc);
	      /* if nt is zero the variable is set to constant
	         and must be not taken into account*/
	      if (nt>0)
		{
		  ns++;
		  /*We use the first variable in the simplified
		    system as equivalent to the original variable*/
		  simpID=GetLinearConstraintVariable(0,&lc);
		  simpSelectedVars[simpID]=FALSE;
	          #if (_DEBUG>0)
		    printf("  Var %s -> %s\n",cs->orig_varNames[i],
			   VariableName(simpID,&(cs->simp_variables)));
		  #endif
		}
	      #if (_DEBUG>0)
	      else
		printf("  Var %s -> constant (not considered)\n",cs->orig_varNames[i]);
	      #endif
	      DeleteLinearConstraint(&lc);
	    }
	}
    }

  if ((neqs>0)&&(ns>0))
    {
      TJacobian J;

      /* We have to translate the simplified Jacobian matrix to the original system */
      InitJacobian(&(csOrig.simp_variables),&(csOrig.simp_equations),&J);
      RewriteJacobian2Orig(cs->orig2s,&J);

      #if (_DEBUG>1)
      {
	char **varNames;
	unsigned int j;
	
	NEW(varNames,csOrig.orig_nvariables,char*);
	GetVariableNames(varNames,&(csOrig.orig_variables));
	for(j=0;j<nvars;j++)
	  {
	    for(i=0;i<neqs;i++)
	      {
		printf("J[%u,%u] ->",i,j);
		PrintEquation(stdout,varNames,GetJacobianEquation(i,j,&J));
	      }
	  }
	free(varNames);
      }
      #endif

      AddJacobianEquationsInt(p,simpSelectedVars,&J,cs);

      DeleteJacobian(&J);
    }
    
  UnUpdateCuikSystem(cs);
  DeleteCuikSystem(&csOrig);
}

/*
  Reduces a box as much as possible (according to parameters in 'p').
  If the set of parameters is undefined, we use a default set.
  This procedure is used in CuikPlan.
  
  This is basically another flavor of ReduceBox where parameters
  are given in one structure instead of as different inputs

  The input box and output boxes are refered to the original
  cuiksystem (the non-simplified one)
  
  The output can be EMPTY_BOX
                    REDUCED_BOX
		    REDUCED_BOX_WITH_SOLUTION
		    ERROR_IN_PROCESS
  
*/
unsigned int MaxReduction(Tparameters *p,unsigned int varMask,double *reduction,Tbox *b,TCuikSystem *cs)
{
  unsigned int e;

  if (!cs->scalar)
    Error("MaxReduction only operates on scalar systems");

  if (UpdateCuikSystem(p,cs))
    {
      Tbox bsimp;
      double sIn,sOut;

      SimpleFromOriginal(b,&bsimp,cs->orig2sd);
      sIn=GetBoxSize(cs->systemVar,&bsimp);
      e=ReduceBox(p,(varMask==0?(unsigned int)~DUMMY_VAR:varMask),&bsimp,cs);
      if (e==EMPTY_BOX)
	*reduction=0;
      else
	{
	  sOut=GetBoxSize(cs->systemVar,&bsimp);
	  *reduction=sOut/sIn;
	  /* ERROR_IN_PROCESS, REDUCED_BOX, REDUCED_BOX_WITH_SOLUTION*/
	  UpdateOriginalFromSimple(&bsimp,b,cs->orig2sd);
	}
      DeleteBox(&bsimp);
    }
  else
    e=EMPTY_BOX;

  return(e);
}


boolean SampleCuikSystem(Tparameters *p,char *fname,Tlist *sb,
			 unsigned int nsamples,unsigned int ntries,
			 unsigned int ndof,TCuikSystem *cs)
{
  Tbox init_box;
  boolean haveSample;

  if (!cs->scalar)
    Error("SampleCuikSystem only operates on scalar systems");

  GenerateInitialBox(&init_box,cs);

  haveSample=SampleCuikSystemInBox(p,fname,sb,nsamples,ntries,ndof,&init_box,cs);
  
  DeleteBox(&init_box);
  
  return(haveSample);
}

boolean SampleCuikSystemInBox(Tparameters *p,char *fname,Tlist *sb,
			      unsigned int nsamples,unsigned int ntries,
			      unsigned int ndof,
			      Tbox *init_box,TCuikSystem *cs)
{
  Tbox orig_ranges,b,*bAux,*box;
  Tlist solutions;
  unsigned int k,d,ns,nv,ne,i,nt;
  double v;
      
  Tfilename fsols_box;
  Tfilename fsols_point;

  FILE *f_out_box;  
  FILE *f_out_point;  

  Titerator it;
  boolean *systemVars;
  Tinterval *r;
  unsigned int spt;
  double ms;
  double reduction;

  boolean ok;
  boolean end;

  /* free var = variable not in equations -> must be fixed always */
  unsigned int *freeVars;
  unsigned int nFreeVars;

  unsigned int nsols;

  if (!cs->scalar)
    Error("SampleCuikSystemInBox only operates on scalar systems");

  /*Get a copy of the ranges in 'cs' for all the variables*/
  GenerateInitialBox(&orig_ranges,cs);
  
  /*Set the ranges for the 'cs' variables to those in the given box (init_box)*/
  if (cs->updated) 
    UnUpdateCuikSystem(cs);

  nv=NVariables(&(cs->orig_variables));
  for(k=0;k<nv;k++)
    SetVariableInterval(GetBoxInterval(k,init_box),GetVariable(k,&(cs->orig_variables)));

  NEW(freeVars,nv,unsigned int);
  nFreeVars=0;
  for(k=0;k<nv;k++)
    {
      if ((GetVariableTypeN(k,&(cs->orig_variables))==SYSTEM_VAR)&&
	  (!UsedVarInEquations(k,&(cs->orig_equations))))
	{
	  freeVars[nFreeVars]=k;
	  nFreeVars++;
	}
    }

  /*Change the SPLIT_TYPE parameter to random split*/
  spt=(unsigned int)GetParameter(CT_SPLIT_TYPE,p);
  ChangeParameter(CT_SPLIT_TYPE,2,p); /* select split dimentions at random */
  /*Change the SMALL_SIGMA parameter to ensure it is small enough.
    SMALL_SIGMA controls the precission of the isolated solutions and, thus, of the
    sampled points. */
  ms=GetParameter(CT_SMALL_SIGMA,p);
  ChangeParameter(CT_SMALL_SIGMA,100*GetParameter(CT_EPSILON,p),p);
  /*keep the original nsols parameter*/
  nsols=(unsigned int)GetParameter(CT_N_SOLUTIONS,p);

  if (fname==NULL)
    {
      f_out_box=NULL;
      f_out_point=NULL;
    }
  else
    {
      /* Check if we can create the output files */
      CreateFileName(NULL,fname,"_samples",SOL_EXT,&fsols_box);
      f_out_box=fopen(GetFileFullName(&fsols_box),"w"); 
      if (!f_out_box)
	Error("Could not open box sample output file");
      
      CreateFileName(NULL,fname,NULL,LINKS_EXT,&fsols_point);
      f_out_point=fopen(GetFileFullName(&fsols_point),"w"); 
      if (!f_out_point)
	Error("Could not open box sample output file");
    }

  if (sb!=NULL)
    InitListOfBoxes(sb);

  nv=GetCSNumVariables(cs);
  ne=GetCSNumEquations(cs);

  if (ndof==NO_UINT)
    {
      /* try to get the number of dof from the system (vars-equations) */
      if (ne>=nv)
	Error("Over/Well-constrained system. Please indicate the number of dof in the call");
      ndof=nv-ne;
    }

  if (MaxReduction(p,~DUMMY_VAR,&reduction,init_box,cs)==EMPTY_BOX)
    end=TRUE;
  else
    end=FALSE;

  if (nFreeVars>ndof)
    Error("More free vars than degrees of freedom");

  ns=0; /*samples already determined*/
  nt=0; /*number of tries so far*/
  while(!end)
    {
      do {
	ok=TRUE;

	/*fix 'ndof' variables*/
	CopyBox(&b,init_box);
	for(k=0;k<nv;k++)
	  SetCSVariableRange(k,GetBoxInterval(k,&b),cs);
	
	for(k=0;k<nFreeVars;k++)
	  {	
	    r=GetBoxInterval(freeVars[k],&b);
	    v=randomInInterval(r);
	    
	    #if (_DEBUG>1)
	      printf("[CS]->fixing %u to %f\n",freeVars[k],v);
	    #endif
	    
	    NewInterval(v,v,r);
	    
	    SetCSVariableRange(freeVars[k],r,cs);
	  }

	for(k=nFreeVars;((ok)&&(k<ndof));k++)
	  {
	    /*fix 'ndof' variables*/

	    /* This updates the system, including simplification */
	    d=ComputeSplitDim(p,&b,cs);

	    if (d==NO_UINT)
	      ok=FALSE;
	    else
	      {
		r=GetBoxInterval(d,&b);
		v=randomInInterval(r);
		
	        #if (_DEBUG>1)
	          printf("[CS]->fixing %u to %f\n",d,v);
	        #endif

		NewInterval(v,v,r);
		
		SetCSVariableRange(d,r,cs);
	      }
	  }

	#if (_DEBUG>1)
	  if (ok)
	    {printf("[CS]");PrintBox(stdout,&b);}
	  else
	    printf("Inconsistent system while sampling\n");
        #endif

	DeleteBox(&b);
     
	nt++;
	if ((ntries!=NO_UINT)&&(nt==ntries))
	  end=TRUE;
      } while((!ok)&&(!end));

      if (!end)
	{
	  /**/
	  InitListOfBoxes(&solutions);

	  /*See if there are solutions for the fixed ranges*/
	  ChangeParameter(CT_N_SOLUTIONS,nsamples-ns,p);
	  SolveCuikSystem(p,FALSE,NULL,NULL,f_out_box,&solutions,cs);
	  
	  /*We have to print the samples*/
	  GetCSSystemVars(&systemVars,cs);
	  InitIterator(&it,&solutions);
	  First(&it);
	  while((!EndOfList(&it))&&(!end))
	    {
	      bAux=(Tbox *)GetCurrent(&it);

	      if (f_out_point!=NULL)
		{
		  /* Print the center of the box into the point file */
		  /* We only print values for the system vars */
		  for(i=0;i<nv;i++)
		    {
		      if (systemVars[i])
			fprintf(f_out_point," %.12g",IntervalCenter(GetBoxInterval(i,bAux)));
		    }
		  fprintf(f_out_point,"\n");
		}
	      if (sb!=NULL)
		{
		  NEW(box,1,Tbox); 
	    
		  CopyBox(box,bAux);
	    
		  AddLastElement((void *)box,sb);
		}
	
	      ns++;
	      if (ns<nsamples)
		end=TRUE;
	      Advance(&it);
	    }
	  free(systemVars);

	  fflush(f_out_point);
	  fflush(f_out_box);

	  /*Remove all boxes from the list and the current box*/
	  DeleteListOfBoxes(&solutions);
	}
    } 

  if (f_out_box!=NULL)
    {
      DeleteFileName(&fsols_box);
      fclose(f_out_box);
    }
  if (f_out_point!=NULL)
    {
      fclose(f_out_point);
      DeleteFileName(&fsols_point);
    }

  /*Restore the user given split_type, min_sigma, and n_solutions*/
  ChangeParameter(CT_SPLIT_TYPE,spt,p);
  ChangeParameter(CT_SMALL_SIGMA,ms,p);
  ChangeParameter(CT_N_SOLUTIONS,nsols,p);

  /*Return the original ranges to the 'cs' variables*/
  if (cs->updated) 
    UnUpdateCuikSystem(cs);

  nv=NVariables(&(cs->orig_variables));
  for(k=0;k<nv;k++)
    SetVariableInterval(GetBoxInterval(k,&orig_ranges),GetVariable(k,&(cs->orig_variables)));

  free(freeVars);

  DeleteBox(&orig_ranges);
  
  return(!end);
}


boolean IncrementalSampleCuikSystem(Tparameters *p,char *fname,Tlist *sb,
				    boolean *fixVars,
				    unsigned int nsamples,unsigned int ntries,
				    unsigned int ndof,TCuikSystem *cs)
{
  Tbox init_box;
  boolean haveSample;

  if (!cs->scalar)
    Error("IncrementalSampleCuikSystem only operates on scalar systems");

  GenerateInitialBox(&init_box,cs);

  haveSample=IncrementalSampleCuikSystemInBox(p,fname,sb,fixVars,nsamples,ntries,ndof,&init_box,cs);
  
  DeleteBox(&init_box);
  
  return(haveSample);
}

boolean IncrementalSampleCuikSystemInBox(Tparameters *p,char *fname,Tlist *sb,
					 boolean *fixVars,
					 unsigned int nsamples,unsigned int ntries,
					 unsigned int ndof,
					 Tbox *init_box,TCuikSystem *cs)
{
  Tbox b,*bAux,*box;
  Tlist solutions;
  unsigned int k,d,ns,nv,ne,i,nt;
  double v;
      
  double smallSigma;

  Tfilename fsols_box;
  Tfilename fsols_point;

  FILE *f_out_box;
  FILE *f_out_point;  

  Titerator it;
  boolean *systemVars;
  Tinterval *r,newr;
  Tbox *bl;
  double ms;
  double reduction;

  boolean ok;
  boolean end;

  boolean *fv;
  unsigned int *ind2fv;
  unsigned int nfv;
  unsigned int newtonIterations;
  double *sol;
  Tbox b_sol;
  Tbox orig_ranges;
  unsigned int level,*attempts,maxAttemptsPerLevel;
  unsigned int nsols;

  if (!cs->scalar)
    Error("IncrementalSampleCuikSystemInBox only operates on scalar systems");

  /*Set the ranges for the 'cs' variables to those in the given box (init_box)*/

  if (!UpdateCuikSystem(p,cs))
    Error("Inconsistent cuiksystem in IncrementalSampleCuikSystemInBox");

  BoxFromVariables(&orig_ranges,&(cs->orig_variables));

  nv=NVariables(&(cs->orig_variables));

  NEW(sol,nv,double);

  ms=GetParameter(CT_SMALL_SIGMA,p);
  smallSigma=100*GetParameter(CT_EPSILON,p);
  ChangeParameter(CT_SMALL_SIGMA,smallSigma,p);

  nsols=(unsigned int)GetParameter(CT_N_SOLUTIONS,p);

  newtonIterations=(unsigned int)GetParameter(CT_MAX_NEWTON_ITERATIONS,p);

  /* Array of variables that can be fixed */
  NEW(fv,nv,boolean);
  NEW(ind2fv,nv,unsigned int);
  nfv=0;
  for(k=0;k<nv;k++)
    {
      if ((IntervalSize(GetBoxInterval(k,init_box))>smallSigma)&&
	  (IsInSimple(k,cs->orig2sd)))
	{
	  if (((fixVars!=NULL)&&(fixVars[k]))||
	      ((fixVars==NULL)&&(IsSystemVariable(k,&(cs->orig_variables)))))
	    {
	      fv[k]=TRUE;
	      ind2fv[nfv]=k;
	      nfv++;
	    }
	  else
	    fv[k]=FALSE;
	}
      else
	fv[k]=FALSE;
    }

  if (fname==NULL)
    {
      f_out_box=NULL;
      f_out_point=NULL;
    }
  else
    {
      /* Check if we can create the output files */
      CreateFileName(NULL,fname,"_samples",SOL_EXT,&fsols_box);
      f_out_box=fopen(GetFileFullName(&fsols_box),"w"); 
      if (!f_out_box)
	Error("Could not open box sample output file");
      
      CreateFileName(NULL,fname,NULL,LINKS_EXT,&fsols_point);
      f_out_point=fopen(GetFileFullName(&fsols_point),"w"); 
      if (!f_out_point)
	Error("Could not open box sample output file");
    }

  if (sb!=NULL)
    InitListOfBoxes(sb);

  nv=GetCSNumVariables(cs);
  ne=GetCSNumEquations(cs);

  if (ndof==NO_UINT)
    {
      /* try to get the number of dof from the system (vars-equations) */
      if (ne>=nv)
	Error("Over/Well-constrained system. Please indicate the number of dof in the call");
      ndof=nv-ne;
    }
  #if (_DEBUG>1)
    printf("Initial reduction (s:%g)\n",GetBoxSumSide(NULL,init_box));
  #endif
  if (MaxReduction(p,~DUMMY_VAR,&reduction,init_box,cs)==EMPTY_BOX)
    end=TRUE;
  else
    end=FALSE;

  #if (_DEBUG>1)
    if (!end)
      {
	printf("[CS] (s:%g)",GetBoxSumSide(NULL,init_box));
	PrintBox(stdout,init_box);
      }
    else
      printf("Inconsistent system while sampling\n");
    fflush(stdout);
  #endif

  NEW(attempts,ndof,unsigned int);
  NEW(bl,ndof,Tbox);
  maxAttemptsPerLevel=10;

  ns=0; /*samples already determined*/
  nt=0; /*time we tried to sample so far*/
  while((!end)&&(ns<nsamples))
    {
      ok=TRUE;

      CopyBox(&b,init_box);
      
      /*fix ndof variables*/
      level=0;
      for(k=0;k<ndof;k++)
	attempts[k]=0;

      while((level<ndof)&&(!end))
	{	
	  /*Keep a copy of the box BEFORE fixing the new variable at the current
	    'level'. This is used when backtracking to recover the state before this
	    assigment*/
	  CopyBox(&(bl[level]),&b);

	  do {
	    /*select one of the still not fixed variables*/
	    d=ind2fv[randomMax(nfv-1)];
	    r=GetBoxInterval(d,&b);
	  } while (IntervalSize(r)<=smallSigma);
	  
	  #if (_DEBUG>1)
	    printf("[CS](level %u/%u bs:%f)",level,ndof,GetBoxSumSide(NULL,&b));
	  #endif

	  {
	    Tinterval raux;
	    double c,l;
	    
	    c=IntervalCenter(r);
	    l=IntervalSize(r)/2;
	    
	    NewInterval(c-l,c+l,&raux);
	      
	    /*Now change the current box ,b*/
	    v=randomInInterval(&raux);
	  }
	  //v=randomInInterval(r);

	  NewInterval(v,v,&newr);
	    
	  SetBoxInterval(d,&newr,&b);

	  /* Change the variable ranges to those in b */ 
	  UnUpdateCuikSystem(cs);
	  VariablesFromBox(&b,&(cs->orig_variables));

	  attempts[level]++;

	  #if (_DEBUG>1)
	    printf("(attempts %u/%u)->fixing %u to %f \n", 
		   attempts[level],maxAttemptsPerLevel,d,v);
	  #endif

	  /* And reduce the systems as much as possible */
	  ok=((UpdateCuikSystem(p,cs))&&
	      (MaxReduction(p,~DUMMY_VAR,&reduction,&b,cs)!=EMPTY_BOX));
	 
	  if (ok)
	    {
	      if (newtonIterations>0)
		{
		  if ((CuikNewtonInBox(p,&b,sol,&b_sol,cs)&(CONVERGED_IN_GLOBAL|CONVERGED_IN_BOX))>0)
		    {
		      fprintf(f_out_box,"Newton (%g)",ErrorInSolution(&b_sol,cs));
		      PrintBoxSubset(f_out_box,cs->orig_notDummyVar,cs->orig_varNames,&b_sol); 
		      fflush(f_out_box);
		    }
		  DeleteBox(&b_sol);
		}
	      level++;

	      #if (_DEBUG>1)
	        printf("[CS] (l:%u s:%g)",level,GetBoxSumSide(NULL,&b));
	        PrintBox(stdout,&b);
	      #endif
	    }
	  else
	    {
              #if (_DEBUG>1)
	        printf("Inconsistent system while sampling. Backtracking\n");
	      #endif

	      /*Undo the last assigment*/
	      DeleteBox(&b);
	      CopyBox(&b,&(bl[level]));
	      DeleteBox(&(bl[level]));

	      if (attempts[level]>maxAttemptsPerLevel)
		{
		  attempts[level]=0;
		  if (level>0)
		    {
		      level--;
		      /*move to the state just before the assigment at leve-1*/
		      DeleteBox(&b);
		      CopyBox(&b,&(bl[level]));
		      DeleteBox(&(bl[level]));  
		    }
		}
	    }
	}

      if (ok)
	{
	  /* Last degree of freedom is not fixed but we solve the cuiksystem in the box */
	  InitListOfBoxes(&solutions);

	  /*See if there are solutions for the fixed ranges*/
	  ChangeParameter(CT_N_SOLUTIONS,nsamples-ns,p);
	  SolveCuikSystem(p,FALSE,NULL,&b,f_out_box,&solutions,cs);
	  
	  /*We have to print the samples*/
	  GetCSSystemVars(&systemVars,cs);
	  InitIterator(&it,&solutions);
	  First(&it);
	  while((!EndOfList(&it))&&(ns<nsamples))
	    {
	      bAux=(Tbox *)GetCurrent(&it);

	      if (f_out_point!=NULL)
		{
		  /* Print the center of the box into the point file */
		  /* We only print values for the system vars */
		  for(i=0;i<nv;i++)
		    {
		      if (systemVars[i])
			fprintf(f_out_point," %.12g",IntervalCenter(GetBoxInterval(i,bAux)));
		    }
		  fprintf(f_out_point,"\n");
		}
	      if (sb!=NULL)
		{
		  NEW(box,1,Tbox); 
	    
		  CopyBox(box,bAux);
	    
		  AddLastElement((void *)box,sb);
		}
	
	      ns++;
	      Advance(&it);
	    }
	  free(systemVars);

	  fflush(f_out_point);
	  fflush(f_out_box);

	  /*Remove all boxes from the list and the current box*/
	  DeleteListOfBoxes(&solutions);
	}

      DeleteBox(&b);
      
      nt++;
      if ((ntries!=NO_UINT)&&(nt==ntries))
	end=TRUE;

    }

  if (f_out_box!=NULL)
    {
      DeleteFileName(&fsols_box);
      fclose(f_out_box);
    }
  if (f_out_point!=NULL)
    {
      fclose(f_out_point);
      DeleteFileName(&fsols_point);
    }

  /*Restore the user given small_sigma and number of solutions*/
  ChangeParameter(CT_SMALL_SIGMA,ms,p);
  ChangeParameter(CT_N_SOLUTIONS,nsols,p);

  free(attempts);
  free(bl);

  free(fv);
  free(ind2fv);
  free(sol);
  
  UnUpdateCuikSystem(cs);
  VariablesFromBox(&orig_ranges,&(cs->orig_variables));
  DeleteBox(&orig_ranges);
  
  return(!end);
}

unsigned int CuikNewtonSimp(Tparameters *p,double *x,TCuikSystem *cs)
{
  boolean converged=FALSE;
  unsigned int out=DIVERGED;

  if (UpdateCuikSystem(p,cs))
    {
      if (cs->simp_nequations==0)
	{
	  out=CONVERGED_IN_BOX;
	}
      else
	{
	  TNewton newton;
	  double *Jx_d; 
	  double *b_d;

	  double epsilon,nullSingularValue;
	  double errorVal;
	  int err;
	  unsigned int nStep,nStepMax;

	 #if (_DEBUG>2)
	  {
	    unsigned int i;

	    printf("Starting Newton Iteration form: ["); 
	    for(i=0;i<cs->simp_nvariables;i++)
	      printf("%f ",x[i]);
	    printf("]\n");
	  }
	 #endif
	  InitNewton(cs->simp_nee,cs->simp_nvariables,&newton);
	  Jx_d=GetNewtonMatrixBuffer(&newton);
	  b_d=GetNewtonRHBuffer(&newton);

	  epsilon=GetParameter(CT_EPSILON,p);
	  nullSingularValue=epsilon/100;

	  nStepMax=(unsigned int)GetParameter(CT_MAX_NEWTON_ITERATIONS,p);
	  if (nStepMax==0)
	    Error("Parameter MAX_NEWTON_ITERATIONS must be larger than 0 to use CuikNewton");

	  nStep=0; 

	  while((!converged)&&(nStep<nStepMax)) 
	    {
	      EvaluateJacobianInVector(x,cs->simp_nee,cs->simp_nvariables,Jx_d,&(cs->J));
	      EvaluateEqualityEquations(FALSE,x,b_d,&(cs->simp_equations));

	      err=NewtonStep(nullSingularValue,x,&errorVal,&newton);
	      
	      if (err)
		nStep=nStepMax;
	      else
		{
                  #if (_DEBUG>2)
		  {
		    #if (_DEBUG>3)
		      unsigned int i;
		    #endif
		      
		    printf("  Iteration: %u  error: %g",nStep,errorVal);
                    #if (_DEBUG>3)
		      printf(" x: [\n");
		      for(i=0;i<cs->simp_nvariables;i++)
			printf("%f ",x[i]);
		      printf("]");
                    #endif
		    printf("\n");
		  }
                   #endif

		  /* stopCriterion test */
		  if(errorVal<epsilon) 
		    converged=TRUE;

		  nStep++;
		}
	    }
	
	  if (cs->simp_tp!=NULL)
	    ArrayPi2Pi(cs->simp_nvariables,cs->simp_tp,x);

	  DeleteNewton(&newton);

	  if ((converged)&&(ErrorInSimpCSEquations(p,x,cs)<epsilon))
	    out=CONVERGED_IN_GLOBAL; 
	  else
	    out=DIVERGED;
	}
    }
  else
    Error("Inconsistent input cuiksystem");

  return(out);
}

unsigned int CuikNewtonInBox(Tparameters *p,Tbox *bIn,double *sol,Tbox *b_sol,TCuikSystem *cs)
{ 
  boolean converged=FALSE;
  unsigned int out=DIVERGED;

  if (UpdateCuikSystem(p,cs))
    {
      if (cs->simp_nequations==0)
	{
	  unsigned int i;

	  /* The system of equations is empty -> just pic a random value for the variables */
	  for(i=0;i<cs->orig_nvariables;i++)
	    sol[i]=randomInInterval(GetBoxInterval(i,bIn));
	  InitBoxFromPoint(cs->orig_nvariables,sol,b_sol);
	  out=CONVERGED_IN_BOX;
	}
      else
	{
	  Tbox bsimp;
	  Tinterval c,*r;

	  unsigned int nv,ne,bs;
	  unsigned int i,j,k,l;

	  double *m,*h;
	  double *x;
	  double *Jx_d; 
	  double *b_d;

	  /* Newton required variables */  
	  TNewton newton;

	  double epsilon; 
	  double nullSingularValue;
	  double errorVal;
	  unsigned int nStep,nStepMax;
	  int err;
	  Tbox box;
      
	  bs=GetBoxNIntervals(bIn);
	  if (cs->orig_nvariables<bs)
	    Error("Box size missmatch in CuikNewtonInBox");
	  else
	    {
	      if (cs->orig_nvariables>bs)
		{
		  if (cs->orig_nvariables==(bs+GetNumDummyVariables(&(cs->orig_variables))))
		    {
		      /* We are given a solution box without the dummy vars */
		      /* We need to compute the values for the dummy vars from the system ones*/

		      GenerateInitialBox(&box,cs); /*all variables to initial ranges*/

		      SetBoxSubset(cs->orig_systemVar,bIn,&box); /* only dummies to initial ranges */
		      RegenerateSolution(p,&box,cs); /* define dummies from system variables */
		    }
		  else
		    Error("Box size missmatch in CuikNewtonInBox");
		}
	      else
		CopyBox(&box,bIn);
	    }

	  nStepMax=(unsigned int)GetParameter(CT_MAX_NEWTON_ITERATIONS,p);
	  if (nStepMax==0)
	    Error("Parameter MAX_NEWTON_ITERATIONS must be larger than 0 to use CuikNewton");	  

	  SimpleFromOriginal(&box,&bsimp,cs->orig2s);

	  /* We will add some variables and equations to deal with ranges */
	  #if (NEWTON_WITHIN_RANGES)
	    nv=cs->simp_nvariables+cs->simp_nvariables;
	    ne=cs->simp_nee+cs->simp_nvariables;
	  #else
	    nv=cs->simp_nvariables;
	    ne=cs->simp_nee;
	  #endif

	  /* Space for the variable ranges */
	  NEW(m,cs->simp_nvariables,double);
	  NEW(h,cs->simp_nvariables,double);
	  for(i=0;i<cs->simp_nvariables;i++)
	    {
	      r=GetBoxInterval(i,&bsimp);
	      m[i]=IntervalCenter(r);
	      h[i]=IntervalSize(r)/2.0;
	    }

	  /* Matrices and arrays used in the Newton iteration */
	  NEW(x,nv,double);
	  for(i=0;i<cs->simp_nvariables;i++)
	    x[i]=randomInInterval(GetBoxInterval(i,&bsimp));

	  for(i=cs->simp_nvariables,j=0;i<nv;i++,j++)
	    x[i]=asin((x[j]-m[j])/h[j]);

	  #if (_DEBUG>2)
	  {
	    printf("Starting Newton Iteration form: x=["); 
	    for(i=0;i<nv;i++)
	      printf("%f ",x[i]);
	    printf("]\n");
	  }
	  #endif
     
	  InitNewton(ne,nv,&newton);
	  Jx_d=GetNewtonMatrixBuffer(&newton);
	  
	  k=ne*nv;
	  if (k!=(cs->simp_nee*cs->simp_nvariables))
	    {
	      /* If we have limit constraints just init the full
	         buffer to zero. */
	      for(i=0;i<k;i++)
		Jx_d[i]=0;
	    }

	  b_d=GetNewtonRHBuffer(&newton);
     
	  epsilon=GetParameter(CT_EPSILON,p);
	  nullSingularValue=epsilon/100;

	  nStep=0; 
	  
	  while((!converged)&&(nStep<nStepMax)) 
	    {
 	      EvaluateJacobianInVector(x,ne,nv,Jx_d,&(cs->J));
	      EvaluateEqualityEquations(FALSE,x,b_d,&(cs->simp_equations));

	      for(i=cs->simp_nvariables,j=0,l=cs->simp_nee;i<nv;i++,j++,l++)
		{
		  /* 'j' is the index for the original variable 'v' */
		  /* 'i' is the index for the new variable 'q' */
		  NewtonSetMatrix(l,j,1,&newton);
		  NewtonSetMatrix(l,i,-h[j]*cos(x[i]),&newton);

		  NewtonSetRH(l,(x[j]-m[j]-h[j]*sin(x[i])),&newton);
		}

	      errorVal=Norm(ne,b_d);
	      
	      //fprintf(stderr,"%u Newton Error: %g\n",nStep,errorVal);

	      converged=(errorVal<epsilon);

	      if (!converged)
		{
		  err=NewtonStep(nullSingularValue,x,&errorVal,&newton);

		  if (err)
		    nStep=nStepMax;
		  else
		    {
		      #if (_DEBUG>2)
		        printf("  Iteration: %u  error: %g",nStep,errorVal);
		        #if (_DEBUG>3)
			  printf(" x: [\n");
			  for(i=0;i<cs->simp_nvariables;i++)
			    printf("%f ",x[i]);
			  printf("]");
		        #endif
			printf("\n");
		      #endif

		      nStep++;
		    }
		}
	    }
	  DeleteNewton(&newton);
	  
	  if (cs->simp_tp!=NULL)
	    ArrayPi2Pi(cs->simp_nvariables,cs->simp_tp,x);
	  
	  for(i=0;i<cs->simp_nvariables;i++) 
	    {
	      NewInterval(x[i],x[i],&c);
	      SetBoxInterval(i,&c,&bsimp);
	    }

	  CopyBox(b_sol,&box);
	  UpdateOriginalFromSimple(&bsimp,b_sol,cs->orig2s);
      
	  /* Some dummy variables in original system might not be present in 
	     the simplified system but their value can be trivially deduced
	     from the system variables*/
	  RegenerateSolution(p,b_sol,cs);

	  /*At this point b_sol must be a punctual box (fully defined) */
	  for(i=0;i<cs->orig_nvariables;i++) 
	    sol[i]=IntervalCenter(GetBoxInterval(i,b_sol));

	  if (!converged) //((!converged)||(ErrorInSolution(b_sol,cs)>epsilon))
	    out=DIVERGED;
	  else
	    {
	      Tbox init_box;
	  
	      GenerateInitialBox(&init_box,cs);
	  
	      if ((ErrorInInequalities(b_sol,cs)>epsilon)||
		  (!PointInBox(cs->orig_notDummyVar,cs->orig_nvariables,sol,epsilon,&init_box)))
		out=CONVERGED_OUTSIDE_GLOBAL;
	      else
		{
		  if (PointInBox(cs->orig_systemVar,cs->orig_nvariables,sol,epsilon,&box))
		    out=CONVERGED_IN_BOX;
		  else
		    out=CONVERGED_IN_GLOBAL; 
		}
	  
	      DeleteBox(&init_box);
	    }     

	  DeleteBox(&bsimp);
	  free(x);
	  free(m);
	  free(h);
	  DeleteBox(&box);
	}
    }
  else
    Error("Inconsistent input cuiksystem");

  return(out);
}

/*
  Find a solution of a cuiksystem set of equations
  using the Newton-Rhapson method. If the system is undetermined, 
  the method is based on the Moor-Penrose generalised inverse.
  The method can diverge if the initial point is far from the solutions of the system.
 */
boolean CuikNewton(Tparameters *p,double *sol,Tbox *b_sol,TCuikSystem *cs)
{ 
  Tbox init_box;
  boolean converged;

  GenerateInitialBox(&init_box,cs);

  converged=((CuikNewtonInBox(p,&init_box,sol,b_sol,cs)&(CONVERGED_IN_BOX|CONVERGED_IN_GLOBAL))>0);

  DeleteBox(&init_box);

  return(converged);
}

unsigned int CuikGradientInBox(Tparameters *p,
			       Tbox *bIn,double *sol,Tbox *b_sol,TCuikSystem *cs)
{
  boolean converged=FALSE;
  unsigned int out=DIVERGED;

  if (UpdateCuikSystem(p,cs))
    {
      if (cs->simp_nequations==0)
	{
	  unsigned int i;

	  /* The system of equations is empty -> just pic a random value for the variables */
	  for(i=0;i<cs->orig_nvariables;i++)
	    sol[i]=randomInInterval(GetBoxInterval(i,bIn));
	  InitBoxFromPoint(cs->orig_nvariables,sol,b_sol);
	  out=CONVERGED_IN_BOX;
	}
      else
	{
	  Tbox box,bsimp;
	  double *x,*nx,*f,*J,*g;
	  double alpha,c,t,tau;
	  unsigned int bs,i,k,nSteps,ne;
	  double error,e,epsilon,d;
	  boolean done,stalled;
	  Tinterval range,*is;
	  unsigned int bounds;

	  bounds=1; /* 0: do not consider 1: weigth  2:crop */

	  bs=GetBoxNIntervals(bIn);
	  if (cs->orig_nvariables<bs)
	    Error("Box size missmatch in CuikGradientInBox");
	  else
	    {
	      if (cs->orig_nvariables>bs)
		{
		  if (cs->orig_nvariables==(bs+GetNumDummyVariables(&(cs->orig_variables))))
		    {
		      /* We are given a solution box without the dummy vars */
		      /* We need to compute the values for the dummy vars from the system ones*/

		      GenerateInitialBox(&box,cs); /*all variables to initial ranges*/

		      SetBoxSubset(cs->orig_systemVar,bIn,&box); /* only dummies to initial ranges */
		      RegenerateSolution(p,&box,cs); /* define dummies from system variables */
		    }
		  else
		    Error("Box size missmatch in CuikGradientInBox");
		}
	      else
		CopyBox(&box,bIn);
	    }
	  
	  SimpleFromOriginal(&box,&bsimp,cs->orig2s);
	  is=GetBoxIntervals(&bsimp);

	  epsilon=GetParameter(CT_EPSILON,p);
	  
	  /* initial point */
	  NEW(x,cs->simp_nvariables,double);
	  for(i=0;i<cs->simp_nvariables;i++)
	    x[i]=randomInInterval(&(is[i]));

	  /* Space to evaluate the equations */
	  if (bounds==1)
	    ne=cs->simp_nee+cs->simp_nvariables;
	  else
	    ne=cs->simp_nee;
	  
	  NEW(nx,cs->simp_nvariables,double); /* new x */
	  NEW(f,ne,double); /* evaluation of equations */
	  NEW(g,cs->simp_nvariables,double); /* gradient at x */
	  NEWZ(J,ne*cs->simp_nvariables,double); /* Jacobian of the equations (initialized to 0) */
	  
	  nSteps=1;
	  converged=FALSE;
	  stalled=FALSE;
	  while((!converged)&&(!stalled))
	    {
	      EvaluateJacobianInVector(x,ne,cs->simp_nvariables,J,&(cs->J));
	      EvaluateEqualitySparseEquations(x,f,&(cs->simp_equations));
	      /* only enter the loop if bounds==1 */
	      for(k=cs->simp_nee,i=0;k<ne;k++,i++)
		{
		  d=DistanceToInterval(x[i],&(is[i]));
		  f[k]=d*d;
		  J[RC2INDEX(k,i,ne,cs->simp_nvariables)]=2*d;
		}
	      
	      error=Norm(ne,f);
	      if (nSteps%1000==1)
 	        fprintf(stderr,"  Error %u: %g\n",nSteps,error);
	      converged=(error<epsilon/10);
	      if (!converged)
		{
		  /* obtain the gradient of f1^2+...+f_nv^2 */
		  TMatrixVectorProduct(ne,cs->simp_nvariables,J,f,g);
		  e=Norm(cs->simp_nvariables,g);
		  if (e<epsilon/100)
		    {
		      fprintf(stderr,"     Gradient norm: %g\n",e);
		      stalled=TRUE;
		    }
		  else
		    {
		      /* Adjust alpha 
			 Apply backtracking line search with c=tau=0.5 and with p=-gradient
			 http://en.wikipedia.org/wiki/Backtracking_line_search
		       */
		      done=FALSE;
		      alpha=0.1; /* initial guess */
		      c=tau=0.5; /* set c,tau parameters */
		      t=-c*Norm(cs->simp_nvariables,g); /* t=-c*m, m=p^t*g=-g^t*g (with p=-g) */
		      while((!done)&&(!stalled))
			{
			  /* nx = x + alpha*p = x -alpha*g   (cropped to the box if required) */
			  SumVectorScale(cs->simp_nvariables,x,-alpha,g,nx); 
			  if (bounds==2)
			    Crop2Box(NULL,cs->simp_nvariables,nx,&bsimp);

			  /* evaluate f(nx) */
			  EvaluateEqualitySparseEquations(nx,f,&(cs->simp_equations));
			  /* only enter the loop if bounds==1 */
			  for(k=cs->simp_nee,i=0;k<ne;k++,i++)
			    {
			      d=DistanceToInterval(nx[i],&(is[i]));
			      f[k]=d*d;
			    }
			  e=Norm(ne,f);

			  /* Test if the decrease in error is enough using Armijo-Goldstein condition */
			  if ((error-e)<alpha*t)
			    {
			      alpha*=tau;
			      stalled=(alpha<epsilon);
			    }
			  else
			    done=TRUE;
			}
		      if (!stalled)
			memcpy(x,nx,cs->simp_nvariables*sizeof(double)); /* x<-nx */
		    }
		}
	      nSteps++;
	    }

	  if (cs->simp_tp!=NULL)
	    ArrayPi2Pi(cs->simp_nvariables,cs->simp_tp,x);
	  
	  for(i=0;i<cs->simp_nvariables;i++) 
	    {
	      NewInterval(x[i],x[i],&range);
	      SetBoxInterval(i,&range,&bsimp);
	    }

	  CopyBox(b_sol,&box);
	  UpdateOriginalFromSimple(&bsimp,b_sol,cs->orig2s);
      
	  /* Some dummy variables in original system might not be present in 
	     the simplified system but their value can be trivially deduced
	     from the system variables*/
	  RegenerateSolution(p,b_sol,cs);

	  /*At this point b_sol must be a punctual box (fully defined) */
	  for(i=0;i<cs->orig_nvariables;i++) 
	    sol[i]=IntervalCenter(GetBoxInterval(i,b_sol));

	  if (!converged) //((!converged)||(ErrorInSolution(b_sol,cs)>epsilon))
	    out=DIVERGED;
	  else
	    {
	      Tbox init_box;
	  
	      GenerateInitialBox(&init_box,cs);
	  
	      if ((ErrorInInequalities(b_sol,cs)>epsilon)||
		  (!PointInBox(cs->orig_notDummyVar,cs->orig_nvariables,sol,epsilon,&init_box)))
		out=CONVERGED_OUTSIDE_GLOBAL;
	      else
		{
		  if (PointInBox(cs->orig_systemVar,cs->orig_nvariables,sol,epsilon,&box))
		    out=CONVERGED_IN_BOX;
		  else
		    out=CONVERGED_IN_GLOBAL; 
		}
	  
	      DeleteBox(&init_box);
	    }     

	  free(x);
	  free(f);
	  free(g);
	  free(J);
	  DeleteBox(&box);
	  DeleteBox(&bsimp);
	  
	}
    }
  else
    Error("Inconsistent input cuiksystem");
  
  return(out);
}

/*
  Find a solution of a cuiksystem set of equations
  using a gradient descent method.
 */
boolean CuikGradient(Tparameters *p,double *sol,Tbox *b_sol,TCuikSystem *cs)
{ 
  Tbox init_box;
  boolean converged;

  GenerateInitialBox(&init_box,cs);

  converged=((CuikGradientInBox(p,&init_box,sol,b_sol,cs)&(CONVERGED_IN_BOX|CONVERGED_IN_GLOBAL))>0);

  DeleteBox(&init_box);

  return(converged);
}

/*
  Takes a cuik systema and returns all solutions. 
  Solutions are stored in file 'f_out' (if defined) and in list 'sol'
  (if defined), or both.

  This procedure is used for single-cpu versions of Cuik.
 */
void SolveCuikSystem(Tparameters *p,
		     boolean restart,char *fstate,Tbox *searchSpace,
		     FILE *f_out,Tlist *sol,TCuikSystem *cs)
{
  Theap boxes;
  #if (_DEBUG>1)
    unsigned int nbox=0;
  #endif 

  Tbox b;
  unsigned int c; /* output of ReduceBox */
  unsigned int current_level; /* level of the current box in the search three */
  Tbox init_box;
  boolean done;
  unsigned int nb; /*boxes for recovery mode*/
  unsigned int statePeriod;
  unsigned int nsols;

  if (!cs->scalar)
    Error("SolveCuikSystem only operates on scalar systems");

  /************************************************************************************/
  /************************************************************************************/
  /************************************************************************************/

  if (UpdateCuikSystem(p,cs))
    {
      if (cs->simp_empty)
	{
	  Tbox b;

	  /* The system of equations is empty -> just pic a random value for the variables */
	  InitBox(cs->simp_nvariables,NULL,&b);
	  PostProcessBox(p,REDUCED_BOX_WITH_SOLUTION,f_out,sol,&boxes,&b,cs); 
	  DeleteBox(&b);
	}
      else
	{
	  switch(cs->searchMode)
	    {
	    case DEPTH_FIRST_SEARCH:
	      InitHeapOfBoxes(CmpBoxDepthFirst,NULL,&boxes);
	      break;
	    case BREADTH_FIRST_SEARCH:
	      InitHeapOfBoxes(CmpBoxBreadthFirst,NULL,&boxes);
	      break;
	    case MINIMIZATION_SEARCH:
	      InitHeapOfBoxes(CmpBoxesEquation,(void *)cs,&boxes);
	      break;
	    }

	  if ((restart)&&(fstate!=NULL))
	    {
	      Tlist pboxes;

	      LoadCSState(fstate,&pboxes,cs);
	      AddList2Heap(&pboxes,&boxes);
	      DeleteListOfBoxes(&pboxes);
	    }
	  else
	    {
	      if (searchSpace==NULL)
		{
		  BoxFromVariables(&init_box,&(cs->variables)); 
		  AddBox2HeapOfBoxes(&init_box,&boxes);
		  DeleteBox(&init_box);
		}
	      else
		{
		  SimpleFromOriginal(searchSpace,&init_box,cs->orig2sd);
		  AddBox2HeapOfBoxes(&init_box,&boxes);
		}

	      InitStatistics(1,HeapOfBoxesVolume(cs->systemVar,&boxes),&(cs->st));
	    }

	  current_level=0;
	  nb=0;
	  statePeriod=(unsigned int)GetParameter(CT_STATE_PERIOD,p);
	  nsols=(unsigned int)GetParameter(CT_N_SOLUTIONS,p);

	  done=FALSE;

	  /*the cuik solve process itself*/
	  do {
	    if(!HeapEmpty(&boxes))
	      {
		/*Get a new box*/

		if ((statePeriod>0)&&(fstate!=NULL))
		  {
		    nb++;
		    if (nb==statePeriod)
		      {
			Tlist pboxes;

			Heap2List(&pboxes,&boxes);
			SaveCSState(fstate,&pboxes,cs);
			DeleteListOfBoxes(&pboxes);
			nb=0;
		      }
		  }

		NewBoxProcessed(&(cs->st));

		/*The box is extracted to avoid another process 
		  to get the same box*/
		ExtractMinElement(&b,&boxes); 

		current_level=GetBoxLevel(&b);

		NewMaxLevel(current_level,&(cs->st));

		#if (_DEBUG>0)
		  fprintf(stderr,"<%g %g>[%u]",
			  GetBoxVolume(cs->systemVar,&b),
			  GetBoxSize(cs->systemVar,&b),
			  current_level);
		#endif

		#if (_DEBUG>1)
		  printf("\n\n%u: Analizing box: ",nbox);
		  nbox++;
		  PrintBox(stdout,&b);
		  printf("      Box level   : %u\n",GetBoxLevel(&b));
		  printf("      Box volume  : %g\n",GetBoxVolume(cs->systemVar,&b));
		  printf("      Box size    : %g\n",GetBoxSize(cs->systemVar,&b));
		  if (cs->searchMode==MINIMIZATION_SEARCH)
		    printf("      Box penalty : %g\n",EvaluateEqMin((void *)&b,(void *)cs));
		#endif

		/* Reduce the box by all but dummy vars */;
		c=ReduceBox(p,~DUMMY_VAR,&b,cs);
	
		#if (_DEBUG>0)
		  fprintf(stderr,"  -> ");
		#endif  

		PostProcessBox(p,c,f_out,sol,&boxes,&b,cs);

		if (nsols>0)
		  done=(GetNSolutionBoxes(&(cs->st))>=nsols);

		DeleteBox(&b);
	      }
	  } while((!done)&&(!HeapEmpty(&boxes))); /*Until everything is completed*/

	  DeleteHeap(&boxes); /*for sanity we delete the empty list*/

	  PrintStatistics((f_out==NULL?stdout:f_out),&(cs->st));
	}
    }
}


#if (_USE_MPI)
/*
  In multi-cpu versions we use a MPI version of CuikSolve
  One of the CPUs takes the role of scheduler in charge of managing the
  lists of boxes pending to be processed and classifing boxes out of
  reduction process as solutions of boxes to be split.
  The rest of CPUs take the charge of reducing boxes (i.e., of executing
  ReduceBox to the boxes received from the scheduler) and of returning
  the resulting boxes (with the associated result code) to the
  scheduler.

  The scheduler has to take into account that some child nodes can
  'die' while reducing boxes. So it has to keep track of when a box was
  sent to a child and prediodically check whether a timeout was been reached.
  If so, the corresponding processor is considered as 'dead' the
  box sent is recovered and added to the list of boxes to be processed
  (i.e., send to other child nodes still alive).

  The scheduler should considere the extreme case where all child process die
  and should take care of "awakening" dead processors.
  This is not implemented.... till now.
*/
void MPI_SolveCuikSystem(Tparameters *p,
			 boolean restart,char *fstate,Tbox *searchSpace,
			 FILE *f_out,TCuikSystem *cs)
{
  Theap boxes;  /*queued boxes*/
  Tbox b;
  unsigned int c;
  unsigned int nr;
  unsigned int current_level;

  /*Variables to set up the parallelism*/
  unsigned int in_process; /* number of boxes send to child processors and still
			      in process */
  unsigned int available; /* number of child processors available */
  signed int np; /* number of processors used (np-1) is the number of childs (process
		    0 is the scheduler) */
  MPI_Status status; /* Output status of a MPI command */
  MPI_Request *request; /* Communication request. When the scheduller sends out a box
			   is starts a communication request */
  unsigned int buffer_size; /* Size of a buffer of doubles where we store the 
			       information of a box */
  double **buffers_out; /* boxes send to the child processors */
  double **buffers_in;  /* boxes returned by the child processors */
  signed int i,completed; /* MPI_Testany returns completed=1 if any of the pending 
			     communications requests has been replied (then, 'i' 
			     is the number of the compleated request)*/
  boolean *lost_packet; /* true if a box was never returned */
  time_t *time_stamp; /* time when we send out a box */
  time_t deadline; /* deadline (in seconds) used to compute the maximum expected
		      return time for a box*/
  Tbox init_box;  /* initial search space */
  unsigned int nb;
  unsigned int statePeriod;

  unsigned int nsols;
  boolean done;

  if (!cs->scalar)
    Error("MPI_SolveCuikSystem only operates on scalar systems");

  /*lowest possible priority but not as low as that of the children processors*/
  /*setpriority(PRIO_PROCESS,0,PRIO_MAX-1); */

  MPI_Comm_size(MPI_COMM_WORLD,&np); /*total number of processes (take into 
				       account that this routine is process number 0)*/

  if (UpdateCuikSystem(p,cs))
    {
      switch(cs->searchMode)
	{
	case DEPTH_FIRST_SEARCH:
	  InitHeapOfBoxes(CmpBoxDepthFirst,NULL,&boxes);
	  break;
	case BREADTH_FIRST_SEARCH:
	  InitHeapOfBoxes(CmpBoxBreadthFirst,NULL,&boxes);
	  break;
	case MINIMIZATION_SEARCH:
	  InitHeapOfBoxes(CmpBoxesEquation,(void *)cs,&boxes);
	  break;
	}

      BoxFromVariables(&init_box,&(cs->variables));
      
      /* Reserve space for the boxes sent/received and associated information */
      /*All boxes are the same size as the initial one*/	
      buffer_size=GetBoxBufferSize(&init_box);

      if ((restart)&&(fstate!=NULL))
	{
	  Tlist pboxes;

	  LoadCSState(fstate,&pboxes,cs);
	  AddList2Heap(&pboxes,&boxes);
	  DeleteListOfBoxes(&pboxes);
	}
      else
	{
	  if (searchSpace==NULL)
	    AddBox2HeapOfBoxes(&init_box,&boxes);
	  else
	    {
	      Tbox lb;

	      SimpleFromOriginal(searchSpace,&lb,cs->orig2sd);
	      AddBox2HeapOfBoxes(&lb,&boxes);
	      DeleteBox(&lb);
	    }
	    
	  InitStatistics(np,HeapOfBoxesVolume(cs->systemVar,&boxes),&(cs->st));
	}
      DeleteBox(&init_box);

      current_level=0;

      NEW(buffers_out,np,double*);
      NEW(buffers_in,np,double*);
    
      NEW(request,np,MPI_Request);
      NEW(lost_packet,np,boolean);
      NEW(time_stamp,np,time_t);

      for(i=1;i<np;i++)
	{
	  request[i]=MPI_REQUEST_NULL;
	  NEW(buffers_out[i],buffer_size,double);
	  NEW(buffers_in[i],buffer_size,double);
	  lost_packet[i]=FALSE;
	}

      request[0]=MPI_REQUEST_NULL; /* Processor 0 is the scheduler, do not use it as a child */
      in_process=0;
      available=(np-1);
	
      nb=0;
      statePeriod=GetParameter(CT_STATE_PERIOD,p);
      
      nsols=(unsigned int)GetParameter(CT_N_SOLUTIONS,p);

      done=FALSE;

      /*the cuik solve process itself*/
      do {

	if ((!done)&& /*we don't have enough solutions*/
	    (!HeapEmpty(&boxes))&& /* there is something to be processes */
	    (available>0)) /* and someone ready to process it */
	  {
	    /* Search for a free child (at least one must exists) */
	    i=1;
	    while ((i<np)&&(request[i]!=MPI_REQUEST_NULL)) i++;
		  
	    if (i==np)
	      Error("wrong number of available processors");
	    else
	      {
		if ((statePeriod>0)&&(fstate!=NULL))
		  {
		    nb++;
		    if (nb==statePeriod)
		      {
			Tbox btmp;
			unsigned int ctmp,ntmp;
			Tlist pboxes;
			unsigned int kk;

			Heap2List(&pboxes,&boxes);
			for(kk=1;kk<(unsigned int)np;kk++)
			  {
			    if (request[kk]!=MPI_REQUEST_NULL)
			      { 
				InitBox(cs->nvariables,NULL,&btmp);
				Buffer2Box(&ctmp,&ntmp,buffers_out[kk],&btmp);
				AddFirstElement((void *)&btmp,&pboxes);
			      }
			  }
			SaveCSState(fstate,&pboxes,cs);
			DeleteListOfBoxes(&pboxes);
			nb=0;
		      }
		  }

		/*Get a new box*/
		ExtractMinElement(&b,&boxes); 
	    
		/* Transform the box into a buffer of doubles */
		Box2Buffer(REDUCED_BOX,0,buffers_out[i],&b);
	    
		/* Send it to the iddle child processors */
		/* and start waiting for the reply (i.e., the reduced box) */
		if (MPI_Send(buffers_out[i],buffer_size,MPI_DOUBLE,i,20,MPI_COMM_WORLD)==MPI_SUCCESS)
		  {
		    /* The box is sent and now we start waiting for it */
		    if (MPI_Irecv(buffers_in[i],buffer_size,MPI_DOUBLE,i,20,MPI_COMM_WORLD,&(request[i]))==MPI_SUCCESS)
		      {

			current_level=GetBoxLevel(&b);
			
			NewBoxProcessed(&(cs->st));
			NewMaxLevel(current_level,&(cs->st));
			
			/* One more box is in process */
			in_process++;
			
			/* One less processor is available */
			available--;
			
			#if (_DEBUG>0)
			  /* Inform about the box launchig */
			  fprintf(stderr,"b<v:%g, s:%g, l:%u>-> %u\n",
				  GetBoxVolume(cs->systemVar,&b),
				  GetBoxSize(cs->systemVar,&b),
				  current_level,i);
			  /*
			  fprintf(stderr,"   A:%d   P:%d  Q:%u\n", 
				  available,in_process,HeapSize(&boxes));
			  */
			#endif  
			
			/* Store the time at which we sent out the box */
			time_stamp[i]=time(NULL);
			/* and, mark the sent box as not lost */
			lost_packet[i]=FALSE;
			
			#if (_DEBUG>1)
			  printf("Sending box to processors : %u (iddle -> %u box_in_list-> %u)\n",
				 i,np-in_process-1,HeapSize(&boxes));
			  printf("  Box: ");
			  PrintBox(stdout,&b);
			#endif
			
			DeleteBox(&b);
		      }
		    else
		      {
			/*The box will never be back: add it to the list and free the processor */
			#if (_DEBUG>0)
			  fprintf(stderr,"RF-> %u\n",i);
			#endif
			
			AddBox2HeapOfBoxes(&b,&boxes);
			request[i]=MPI_REQUEST_NULL;
		      }
		  }
		else
		  {
		    /* We didn't manage to send out the box, just return it to the boxes
		       to be processes*/ 
		    #if (_DEBUG>0)
		      fprintf(stderr,"SF-> %u\n",i);
		    #endif

		    AddBox2HeapOfBoxes(&b,&boxes);
		  }
	      }
	  }

	/* see if we already got any reply from the slaves :-) */
	if ((MPI_Testany(np,request,&i,&completed,&status)==MPI_SUCCESS)&&
	    (completed))
	  {
	    /* if 'completed' 'i' is the request completed */
	    #if (_DEBUG>1)
	      printf("Receiving box from processors : %u\n",i);
	    #endif

	    available++; /* either if lost or not, the processor becomes available from now  on */
	    request[i]=MPI_REQUEST_NULL; 

	    if (!lost_packet[i])
	      {
		/* If so, reconstruct the output box and analyze it */
		InitBox(cs->nvariables,NULL,&b);

		Buffer2Box(&c,&nr,buffers_in[i],&b);

		AddNBoxReductions(nr,&(cs->st));

		in_process--; /* lost ones are already discounted when classified as lost 
				 (to be able to finish even if lost ones exits)*/

		#if (_DEBUG>0)
		  fprintf(stderr,"  %u->b<v:%g s:%g l:%u>(t=%lu): ",
			  i,
			  GetBoxVolume(cs->systemVar,&b),
			  GetBoxSize(cs->systemVar,&b),
			  GetBoxLevel(&b),
			  time(NULL)-time_stamp[i]);
		  /*
		    fprintf(stderr,"   A:%d   P:%d  Q:%u\n", 
		    available,in_process,HeapSize(&boxes)); 
		  */
		#endif

		PostProcessBox(p,c,f_out,NULL,&boxes,&b,cs);

		if (nsols>0)
		  done=(GetNSolutionBoxes(&(cs->st))>=nsols);

		DeleteBox(&b);
	      }
	    #if (_DEBUG>0)
	    else
	      {
		/* We receive a box that was thought to be lost. The only think we
		   do is to mark the child as available again by setting request[i]=MPI_REQUEST_NULL;
		   below */
		fprintf(stderr,"  lb[%u](t=%lu > %u)\n",i,
			time(NULL)-time_stamp[i],MPI_TREAT_BOX_TIMEOUT(cs));
	      }
	    #endif
	  }


	/* See if one of the send boxes is lost.
	   All boxes sent before the deadline are considered lost.
	   Lost boxes are recovered and added to the list of pending boxes.
	   The processor to which the box was assigned is discarted for future
	   jobs.
	*/
	deadline=time(NULL)-(time_t)MPI_TREAT_BOX_TIMEOUT(cs);
	for(i=1;i<np;i++)
	  {
	    if ((!lost_packet[i])&& /*not already lost*/
		(request[i]!=MPI_REQUEST_NULL)&& /*and we are waiting for a reply*/
		(time_stamp[i]<deadline)) /*for too long actually*/
	      {
		/* we considere the sub-task as lost, we add the box for further process by 
		   another computer and we mark the current message as lost */

		lost_packet[i]=TRUE; /* mark the packet as lost */

		InitBox(cs->nvariables,NULL,&b); /*Recover it and put it again in the list of 
						   boxes to be processed*/
		Buffer2Box(&c,&nr,buffers_out[i],&b); /* Error code (c) and additional information
							 (nr) are empty (this is a box whose process 
							 was not concluded)*/
	    
		NewLostBox(&(cs->st));
		#if (_DEBUG>0)
		  fprintf(stderr,"  l[%u] (elapsed %lu)\n",i,time(NULL)-time_stamp[i]);
		#endif

		/* a time out tipically means a error in the simplex */
		PostProcessBox(p,ERROR_IN_PROCESS,f_out,NULL,&boxes,&b,cs);
	    
		DeleteBox(&b);

		in_process--; /* one less box is in process (Observe that the processors is
				 not marked as available) */
	      }
	  }

	fflush(stderr);

	/* Repeat until we don't have enough solutions and there are still some boxes from
	   where we can get solutions.
	   If we already have all the desired solutions but some boxes are in_process, we
	   wait untill their process finishes (so that all processors are ready to receive
	   the kill signal)
	*/
      } while(((!done)&&(!HeapEmpty(&boxes)))||(in_process>0)); 

      /* Send a magic packed to the child so that they kill themselves */
      
      for(i=1;i<np;i++)
	{
	  if (request[i]!=MPI_REQUEST_NULL)
	    {
	      /*we have a pending communication with this processor -> cancel it*/
	      MPI_Cancel(&(request[i]));
	    }
	  else
	    { 
	      /*nothing pending with this processors, just order it to die*/
	      buffers_out[i][0]=-1.0; 
	      MPI_Send(buffers_out[i],buffer_size,MPI_DOUBLE,i,20,MPI_COMM_WORLD); 
	    }
	}

      free(request);
      free(lost_packet);
      free(time_stamp);

      DeleteHeap(&boxes);

      if (f_out!=NULL)
	{
	  fprintf(f_out,"\n\nCuik executed in %u (%u) child processors\n",available,np-1);
	  PrintStatistics(f_out,&(cs->st));
	}

      DeleteStatistics(&(cs->st));

      for(i=1;i<np;i++)
	{
	  free(buffers_in[i]);
	  free(buffers_out[i]);
	}
	
      free(buffers_in);
      free(buffers_out);
    }
}

/*
  This is the process executed by each child process
*/
void MPI_TreatBox(Tparameters *p,TCuikSystem *cs)
{
  if (!cs->scalar)
    Error("MPI_TreatBox only operates on scalar systems");

  if (UpdateCuikSystem(p,cs))
    {
      boolean end;
      unsigned int n;
      double *buffer;
      unsigned int c,nr;
      Tbox b;
      MPI_Status status;

      InitBox(cs->nvariables,NULL,&b);
      n=GetBoxBufferSize(&b);
      NEW(buffer,n,double);

      /* A child can be in execution in computers not only devoted to cuik.
	 We reduce the priority of the cuik process to allow other processes
	 (those own by the owners of the machines) to run smoothly. 
	 This way we can enlarge the cluster of procesors to almost all
	 computers in our Lab.
	 In the future we have to develop programs to check which computers
	 are on and to add them into the machine list (i.e., the members of
	 the cluster)
      */
      /*setpriority(PRIO_PROCESS,0,PRIO_MAX); */

      end=FALSE; /* While the kill buffer is not received */
	 
      while(!end)
	{
	  /* Get new box from the master */
	  if (MPI_Recv(buffer,n,MPI_DOUBLE,0,20,MPI_COMM_WORLD,&status)==MPI_SUCCESS)
	    {
	      /* The first double is used to send control messages between the 
		 scheduler and the slave. If negative, the slave dies*/
	      if (buffer[0]<0) 
		end=TRUE;
	      else
		{
		  /* If not the kill buffer, recover the box out of the buffer */
		  Buffer2Box(&c,&nr,buffer,&b);

		  ResetNBoxReductions(&(cs->st)); /* Let's count the box reductions for this 
						     box shrink only*/

		  #if (_DEBUG>1)
		    printf("Box from main processor:");
		    PrintBox(stdout,&b);
		    fflush(stdout);
		  #endif

		  /* And reduce it */
		  c=ReduceBox(p,~DUMMY_VAR,&b,cs);

		  #if (_DEBUG>1)
		    printf("Box out of ReduceBox (%u):",c);
		    PrintBox(stdout,&b);
		    fflush(stdout);
		  #endif

		  /* Then pack the result into another buffer */
		  Box2Buffer(c,GetNBoxReductions(&(cs->st)),buffer,&b);

		  /* and send it back to the master */
	      
		  #if (_DEBUG>1)
		    if (MPI_Send(buffer,n,MPI_DOUBLE,0,20,MPI_COMM_WORLD)!=MPI_SUCCESS)
		      printf("Sending to master failed\n");
		  #else
		    MPI_Send(buffer,n,MPI_DOUBLE,0,20,MPI_COMM_WORLD);
		  #endif
		
		}
	    }
	  #if (_DEBUG>1)
	  else
	    printf("Receive from master failed\n");
	  #endif
	}

      DeleteBox(&b);
      free(buffer);
    }
}
#endif

/*
  Returns a box defined by the ranges for the variables given by the user in the
  input file. This is the initial search space.
 */
void GenerateInitialBox(Tbox *box,TCuikSystem *cs)
{
  BoxFromVariables(box,&(cs->orig_variables));
}

void GenerateSimpInitialBox(Tparameters *p,Tbox *box,TCuikSystem *cs)
{
  if (!UpdateCuikSystem(p,cs))
    Error("Inconsistent system in GenerateSimpInitialBox");

  BoxFromVariables(box,&(cs->simp_variables));
}

boolean RegenerateSolution(Tparameters *p,Tbox *b,TCuikSystem *cs)
{
  boolean ok;

  if (UpdateCuikSystem(p,cs))
    {
      unsigned int i;
      double epsilon,rho;
      Tinterval all;

      /* If we set the dummies to range [-INF,INF] they are not
         adjusted via crop. */
      NewInterval(-INF/2,INF/2,&all);

      epsilon=GetParameter(CT_EPSILON,p);
      rho=GetParameter(CT_RHO,p);

      /* System and secondary vars already have value in the input box but
         dummies and cartesian variables probably not. 
         These are set to inf range to avoid any limit
         in their value when regenerated (boxes commming from
         Newton can have extrange values in dummy variables. */
      for(i=0;i<cs->orig_nvariables;i++)
	{
	  if ((IsDummyVariable(i,&(cs->orig_variables)))||
	      (IsCartesianVariable(i,&(cs->orig_variables))))
	    SetBoxInterval(i,&all,b);
	}
      
      ok=TRUE;

      /* First we define the value of the dummy variables from the
         system ones. They are related by dymmy equations and, given
         the system varibles, the dummy variables can be easily defined
         via crop. */
      for(i=0;((ok)&&(i<cs->orig_nequations));i++)
	{
	  if (IsDummyEquation(i,&(cs->orig_equations)))
	    ok=(CropEquation(i,DUMMY_VAR,epsilon,rho,b,&(cs->orig_variables),&(cs->orig_equations))!=EMPTY_BOX);
	}
      
      /*
	Now we try to define the cartesian variables from the system
	and dummy ones.
	The separating plane cartesian variables can not be properly bounded 
	this way but the ones for body vertexes can (and they are the relevant
	ones)
       */
      for(i=0;((ok)&&(i<cs->orig_nequations));i++)
	{
	  if (IsCoordEquation(i,&(cs->orig_equations)))
	    ok=(CropEquation(i,CARTESIAN_VAR,epsilon,rho,b,&(cs->orig_variables),&(cs->orig_equations))!=EMPTY_BOX);
	}
    }
  else
    ok=FALSE;

  return(ok);
}

unsigned int RegenerateSolutionPoint(Tparameters *p,double *pt,double **rp,TCuikSystem *cs)
{
  unsigned int i,k;
  Tbox b;

  if (!UpdateCuikSystem(p,cs))
    Error("Inconsistent system in RegenerateSolutionPoint");

  NEW(*rp,cs->orig_nvariables,double);

  k=0;
  for(i=0;i<cs->orig_nvariables;i++)
    {
      /*The input box only has values for the input variables*/
      if (cs->orig_systemVar[i])
	{
	  (*rp)[i]=pt[k];
	  k++;
	}
      else
	(*rp)[i]=0.0; /*Non system variables are set to 0. This value is not used */
    }

  InitBoxFromPoint(cs->orig_nvariables,*rp,&b);

  if (!RegenerateSolution(p,&b,cs))
    Error("Invalid solution point in RegenerateSolutionPoint");

  k=0;
  for(i=0;i<cs->orig_nvariables;i++)
    {
      /*The input box only has values for the input variables (system and secondary)*/
      if (!cs->orig_systemVar[i])
	(*rp)[i]=IntervalCenter(GetBoxInterval(i,&b));
    }
  DeleteBox(&b);

  return(cs->orig_nvariables);
}
				     

void RegenerateOriginalBox(Tparameters *p,Tbox *boxS,Tbox *boxO,TCuikSystem *cs)
{
  if (UpdateCuikSystem(p,cs))
    {
      BoxFromVariables(boxO,&(cs->orig_variables)); 
      UpdateOriginalFromSimple(boxS,boxO,cs->orig2s); 
    }
  else
    Error("Inconsistent input cuiksystem");
}

unsigned int RegenerateOriginalPoint(Tparameters *p,double *s,double **o,
				     TCuikSystem *cs)
{
 if (UpdateCuikSystem(p,cs))
    {
      PointFromVariables(o,&(cs->orig_variables));
      UpdateOriginalPointFromSimple(s,*o,cs->orig2s);
    }
  else
    Error("Inconsistent input cuiksystem");

  return(cs->orig_nvariables);
}

unsigned int GenerateSimplifiedPoint(Tparameters *p,double *o,double **s,TCuikSystem *cs)
{
  if (UpdateCuikSystem(p,cs))
    SimplePointFromOriginal(o,s,cs->orig2s);
  else
    Error("Inconsistent input cuiksystem");

  return(cs->simp_nvariables);
}

unsigned int SimplifyBooleanArray(Tparameters *p,boolean *bo,boolean **bs,
				  TCuikSystem *cs)
{
  if (UpdateCuikSystem(p,cs))
    {
      unsigned int i,k;

      NEW(*bs,cs->simp_nvariables,boolean);

      k=0;
      for(i=0;i<cs->orig_nvariables;i++)
	{
	  if (IsInSimple(i,cs->orig2s))
	    {
	      (*bs)[k]=bo[i];
	      k++;
	    }
	}
      if (k!=cs->simp_nvariables)
	Error("Wrong number of variables in SimplifyBooleanArray");
    }
  else
    Error("Inconsistent input cuiksystem");
  
  return(cs->simp_nvariables);
}

/*
  Selects one dimension along which to split box 'b'. The dimension can
  be selected according to the size or according to the error that each
  variable induce in each equation.
  This is similar to ComputeSplitDimInt but the output is an index in 
  the original system and not in the simplified one
 */
unsigned int ComputeSplitDim(Tparameters *p,Tbox *b,TCuikSystem *cs)
{
  Tbox bsimp;
  unsigned int d;

  if (!cs->scalar)
    Error("ComputeSplitDim only operates on scalar systems");

  if (UpdateCuikSystem(p,cs))
    {
      SimpleFromOriginal(b,&bsimp,cs->orig2sd);
      d=GetVarIDInOriginal(ComputeSplitDimInt(p,&bsimp,cs),cs->orig2sd);
      DeleteBox(&bsimp);
    }
  else
    d=NO_UINT;

  return(d);
}

/*
  Returns TRUE if point stored in vector 'v' is included in box 'b'
  Dummy variables are not taken into account in this procedure.
*/
boolean PointInSystemBox(Tvector *v,Tbox *b,TCuikSystem *cs)
{
  unsigned int i,k,nv;
  double *val;
  boolean in;

  nv=NVariables(&(cs->orig_variables));

  if (nv!=GetBoxNIntervals(b))
    Error("Wrong box size in PointInSystemBox");
  
  k=0;
  in=TRUE;
  for(i=0;((in)&&(i<nv));i++)
    {
      if (!IsDummyVariable(i,&(cs->orig_variables)))
	{
	  val=(double *)GetVectorElement(k,v);
	  if (val==NULL) 
	    Error("Vector with incorrect number of elements in PointInSystemBox");
	  in=IsInside(*val,0.0,GetBoxInterval(i,b));
	  k++;
	}
    }
  return(in);
}

void EvaluateCSEquations(double *p,double *r,TCuikSystem *cs)
{
  EvaluateEqualityEquations(FALSE,p,r,&(cs->orig_equations));
}

void EvaluateSimpCSEquations(Tparameters *pr,double *p,double *r,TCuikSystem *cs)
{
  if (!UpdateCuikSystem(pr,cs))
    Error("Inconsistent input cuiksystem");

  EvaluateEqualityEquations(FALSE,p,r,&(cs->simp_equations));
}

void EvaluateSubSetSimpCSEquations(Tparameters *pr,boolean *se,double *p,double *r,TCuikSystem *cs)
{
  if (!UpdateCuikSystem(pr,cs))
    Error("Inconsistent input cuiksystem");

  EvaluateSubSetEqualityEquations(p,se,r,&(cs->simp_equations));
}

void EvaluateCSJacobian(double *p,double ***J,TCuikSystem *cs)
{
  TJacobian Ja;

  InitJacobian(&(cs->orig_variables),&(cs->orig_equations),&Ja);

  AllocateJacobianEvaluation(J,&Ja);
  EvaluateJacobian(p,*J,&Ja);

  DeleteJacobian(&Ja);
}

double ErrorInCSEquations(Tparameters *pr,double *p,TCuikSystem *cs)
{
  double *r,e;
  unsigned int neq;

  //PrintVector(stderr,"Point",NVariables(&(cs->orig_variables)),p);
  
  neq=NEqualityEquations(&(cs->orig_equations));
  if (neq>0)
    {
      NEW(r,neq,double);
      
      EvaluateEqualityEquations(FALSE,p,r,&(cs->orig_equations));
      e=Norm(neq,r);
      free(r);
    }
  else
    e=0.0;

  return(e);
}

double ErrorInSimpCSEquations(Tparameters *pr,double *p,TCuikSystem *cs)
{
  double *r,e;
  unsigned int neq;

  if (!UpdateCuikSystem(pr,cs))
    Error("Inconsistent input cuiksystem");

  neq=NEqualityEquations(&(cs->simp_equations));
  if (neq>0)
    {
      NEW(r,neq,double);
      EvaluateEqualityEquations(FALSE,p,r,&(cs->simp_equations));
      e=Norm(neq,r);
      free(r);
    }
  else
    e=0.0;

  return(e);
}

double EvaluateCSCost(Tparameters *p,boolean simp,double *s,void *cs)
{
  double v;

  if (simp)
    v=EvaluateWholeEquation(s,&(((TCuikSystem *)cs)->simp_eqMin)); 
  else
    v=EvaluateWholeEquation(s,&(((TCuikSystem *)cs)->orig_eqMin)); 

  return(v);
}

/*
  Takes the center of the box and computes the error of this
  point when replaced into the system of equations.
  We use this function to check the validity of the outputs
  of Cuik.
 */
double ErrorInSolution(Tbox *b,TCuikSystem *cs)
{
  double *p; /*central point of the box*/
  unsigned int i;
  double *r,maxError;
  //double e;
  unsigned int nv,neq;

  maxError=0;

  nv=NVariables(&(cs->orig_variables));
  neq=NEqualityEquations(&(cs->orig_equations));
  if ((nv>0)&&(neq>0))
    {
      if (nv!=GetBoxNIntervals(b))
	Error("Wrong box size in ErrorInSolution");

      NEW(p,nv,double);

      for(i=0;i<nv;i++)
	p[i]=IntervalCenter(GetBoxInterval(i,b));

      NEW(r,neq,double);
      EvaluateEqualityEquations(TRUE,p,r,&(cs->orig_equations));
      maxError=Norm(neq,r);
      /*
      for(i=0;i<neq;i++)
	{
	  e=fabs(r[i]);
	  if (e>maxError)
	    maxError=e;
	}
      */
      free(r);
      free(p);
    }
  return(maxError);
}

double ErrorInInequalities(Tbox *b,TCuikSystem *cs)
{
  unsigned int i,neq,nv;
  double maxError,*r,*p;

  nv=NVariables(&(cs->orig_variables));

  if (nv!=GetBoxNIntervals(b))
    Error("Wrong box size in ErrorInInequalities");

  neq=NInequalityEquations(&(cs->orig_equations));
  if (neq>0)
    {
      NEW(p,nv,double);
      for(i=0;i<cs->orig_nvariables;i++)
	p[i]=IntervalCenter(GetBoxInterval(i,b));

      NEW(r,neq,double);
      EvaluateInequalityEquations(p,r,&(cs->orig_equations));
      maxError=MaxVector(neq,r);
      free(r);
      free(p);
    }
  else
    maxError=0.0;

  return(maxError);
}

boolean InequalitiesHoldOnPoint(double *p,TCuikSystem *cs)
{
  unsigned int neq;
  boolean hold;
  double *r;

  neq=NInequalityEquations(&(cs->orig_equations));
  if (neq>0)
    {
      NEW(r,neq,double);
      EvaluateInequalityEquations(p,r,&(cs->orig_equations));
      hold=(MaxVector(neq,r)==0.0);
      free(r);
    }
  else
    hold=TRUE;

  return(hold);
}

boolean SimpInequalitiesHoldOnPoint(Tparameters *pr,double *p,TCuikSystem *cs)
{ 
  unsigned int neq;
  boolean hold;
  double *r;

  if (!UpdateCuikSystem(pr,cs))
    Error("Inconsistent input cuiksystem");

  neq=NInequalityEquations(&(cs->simp_equations));
  if (neq>0)
    {
      NEW(r,neq,double);
      EvaluateInequalityEquations(p,r,&(cs->simp_equations));
      hold=(MaxVector(neq,r)==0.0);
      free(r);
    }
  else
    hold=TRUE;

  return(hold);
}

double ErrorInSimpInequalitiesOnPoint(Tparameters *pr,double *p,TCuikSystem *cs)
{ 
  unsigned int neq;
  double e,*r;

  if (!UpdateCuikSystem(pr,cs))
    Error("Inconsistent input cuiksystem");

  neq=NInequalityEquations(&(cs->simp_equations));
  if (neq>0)
    {
      NEW(r,neq,double);
      EvaluateInequalityEquations(p,r,&(cs->simp_equations));
      e=MaxVector(neq,r);
      free(r);
    }
  else
    e=0.0;

  return(e);
}
unsigned int ManifoldDimension(Tparameters *pr,double *p,TCuikSystem *cs)
{
  double epsilon,*JT,error;
  double *pWithDummies,*pSimp;
  unsigned int nr,nc,k;

  if (!UpdateCuikSystem(pr,cs))
    Error("Inconsistent cuiksystem in ComputeSplitDimInt");

  if (cs->simp_nequations==0)
    Error("Empty simplified system in ManifoldDimension");
  
  epsilon=GetParameter(CT_EPSILON,pr);

  /* Convert from original point ot simplified point */
  RegenerateSolutionPoint(pr,p,&pWithDummies,cs);
  GenerateSimplifiedPoint(pr,pWithDummies,&pSimp,cs);

  /* We verify that the given point is a solution. Otherwise the rank estimation
     would be not valid. */
  error=ErrorInSimpCSEquations(pr,pSimp,cs);
  if (error>epsilon)
    Error("Point not in manifold");

  GetJacobianSize(&nr,&nc,&(cs->J));

  if ((nr==0)||(nc==0))
    Error("Empty jacobian in ManifoldDimension");
  
  NEW(JT,nc*nr,double);

  EvaluateTransposedJacobianInVector(pSimp,nc,nr,JT,&(cs->J));

  k=nc-FindRank(epsilon,nr,nc,JT);

  free(pWithDummies);
  free(pSimp);
  free(JT);
  
  return(k);
}


/*
  Prints the information stored in the cuiksystem
  It prints it in a form than can be parsed again.
*/
void PrintCuikSystem(Tparameters *p,FILE *f,TCuikSystem *cs)
{
  unsigned int nv;
  char **varNames;

  PrintVariables(f,&(cs->orig_variables));
  
  nv=NVariables(&(cs->orig_variables));
  NEW(varNames,nv,char *);
  GetVariableNames(varNames,&(cs->orig_variables));
  PrintEquations(f,varNames,&(cs->orig_equations));
  if (cs->searchMode==MINIMIZATION_SEARCH)
    {
      fprintf(f,"\n[SEARCH]\n\n MIN ");
      PrintMonomials(f,varNames,&(cs->orig_eqMin));
    }
  free(varNames);  
  fprintf(f,"\n\n");
}

/*
  Prints the information stored in the cuiksystem together with the simplified
  CuikSystem.
  It prints it in a form than can be parsed again.
*/
void PrintCuikSystemWithSimplification(Tparameters *p,FILE *f,TCuikSystem *cs)
{
  unsigned int nv;
  char **varNames;

  if (UpdateCuikSystem(p,cs))
    {
      fprintf(f,"%%****************************************\n");
      fprintf(f,"%% Simplified system \n");
      fprintf(f,"%% SIMPLIFICATION_LEVEL: %u\n",
	      (unsigned int)(GetParameter(CT_SIMPLIFICATION_LEVEL,p)));
      fprintf(f,"%% Variable reduction %u -> %u\n",cs->orig_nvariables,
	      cs->simp_nvariables);
      fprintf(f,"%% Num syst+secu+vel variables in original  : %u \n",
	      GetNumSystemVariables(&(cs->orig_variables))+
	      GetNumSecondaryVariables(&(cs->orig_variables))+
	      GetNumVelocityVariables(&(cs->orig_variables))+
	      GetNumNonDynamicVariables(&(cs->orig_variables)));
      fprintf(f,"%% Num syst+secu+ve variables in simplified: %u \n",
	      GetNumSystemVariables(&(cs->simp_variables))+
	      GetNumSecondaryVariables(&(cs->simp_variables))+
	      GetNumVelocityVariables(&(cs->simp_variables))+
	      GetNumNonDynamicVariables(&(cs->simp_variables)));
      PrintMapping(f,cs->orig2sd);
      PrintVariables(f,&(cs->variables));

      nv=NVariables(&(cs->variables));
      NEW(varNames,nv,char *);
      GetVariableNames(varNames,&(cs->variables));
      PrintEquations(f,varNames,&(cs->equations));
      if (cs->searchMode==MINIMIZATION_SEARCH)
	{
	  fprintf(f,"\n[SEARCH]\n\n MIN ");
	  PrintMonomials(f,varNames,&(cs->eqMin));
	}
      free(varNames);
    }
  else
    fprintf(f,"INCONSISTENT INPUT CUIK SYSTEM\n");
}

void SaveCuikSystemSimplification(Tparameters *p,FILE *f,TCuikSystem *cs)
{
  if (UpdateCuikSystem(p,cs))
    SaveMapping(f,cs->orig2sd);
  else
    fprintf(f,"INCONSISTENT INPUT CUIK SYSTEM\n");
}

/*
  Destructor of the cuiksystem structure.
*/
void DeleteCuikSystem(TCuikSystem *cs)
{ 
  DeleteConstants(&(cs->constants));

  DeleteVariables(&(cs->orig_variables));
  DeleteEquations(&(cs->orig_equations));  
  DeleteStatistics(&(cs->st)); 

  DeleteEquation(&(cs->orig_eqMin));

  UnUpdateCuikSystem(cs);

  cs->empty=TRUE;
  cs->simp_empty=TRUE;
}
