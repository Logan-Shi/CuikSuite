#ifndef EQUATIONSH
#define EQUATIONSH

#include "boolean.h"
#include "variables.h"
#include "equation.h"
#include "mequation.h"
#include "kequation.h"
#include "simplex.h"
#include "defines.h"

#include <stdio.h>

/** \file equations.h
    \brief Definition of the Tequations type and the associated functions.

    Definition of the Tequations type and the associated functions.

    \sa Tequations, equations.c.
*/
/************************************************************************************/

/************************************************************************************/

/** \brief Initial room for equations.

    Initial room for equations in an equation set. It will be enlarged if necessary.

    \sa Tequations
*/
#define INIT_NUM_EQUATIONS 10
/************************************************************************************/

/** 
   \brief Information associated with each scalar equation in the equation set.

   For each equation we store different information, including de number of
   variables, the Jacobian, the Hessian, etc.<br>
   This is a private type of Tequations. This information is not stored in
   Tequation since it can only be computed when the equation is completely
   defined (i.e., when it is added to the set of equations). 

   This is ONLY for scalar equations.

   Originally we only considered scalar equations but later on we added
   the matrix and kino equations. The scalar equations are all implemented
   in the \ref equations.c file and the matrix and kino equations have
   their own code (\ref mequation.c and \ref kequation.c). It may be 
   a good idea to separate the scalar equations in a hypothetical 
   sequation.c file.
   
   \sa Tequation
 */
typedef struct
{
  Tequation *equation; /**< The original equation*/

  unsigned int EqType; /**< Type of equation: LINEAR_EQUATION, SADDLE_EQUATION, PARABOLA_EQUATION, 
			    CIRCLE_EQUATION, SPHERE_EQUATION, GENERAL_EQUATION. */

  TLinearConstraint *lc; /**< For linear equations, we store a linear constraint ready 
			      to be added to the simplex*/

  unsigned int n;  /**< Number of variables in the equation used to compute the dimension of 
		        the Jacobian vector and Hessian matrix */
  Tequation **Jacobian; /**< Jacobian of the equation, i.e., derivative of the equation with 
			     respect to each of the variables involved in the equation.
			     Since we consider only quadratic and bilinear equations, the equations
			     in the Jacobian are, at most, linear.<br>
			     The Jacobian is computed only for non-linear equations. */
  Tequation ***Hessian;   /**< Hessian of the equation, i.e., derivative of the Jacobian equations with 
		 	       respect to each of the variables involved in the equation.
			       Since we consider only quadratic and bilinear equations, the entries
			       in the Hessian are constants.<br>
			       The Hessian is computed only for non-linear equations. */
} TequationInfo;


/** 
   \brief Set of equations.

   Set of equations including scalar and matrix equations.

   Note that the matrix equations are added recently so in most of the comments in the code
   "eauations" is used  instead of "scalar equations"

   The kino-equations are equations on the velocity. Thus, they do not play any relevant role
   in the normal evaluation of the equations, but they are used when computing the Jacobian
   of an equation set (they are directly transferred to the Jacobian),

   \see Tequation, TequationInfo, Tvector 
 */
typedef struct {
  unsigned int neq;         /**< Current number of equations (scalar+matrix but not kino). */

  unsigned int s;           /**< Number of system equations included in the set.*/
  unsigned int c;           /**< Number of coordenalization equations included in the set.*/
  unsigned int d;           /**< Number of dummy equations included in the set.*/
  unsigned int v;           /**< Number of velocity equations included in the set.*/
  unsigned int nd;          /**< Number if non-dynamic equations included in the set.*/
  
  unsigned int e;           /**< Number equalities included in the set.*/  

  boolean polynomial;       /**< TRUE if the equations in the set are polynomial. */  
  boolean scalar;           /**< TRUE for scalar only systems. */

  unsigned int m;           /**< Maximum number of scalar equations in the set.*/
  unsigned int n;           /**< Current number of scalar equations int the set.*/
  TequationInfo **equation; /**< Information particular for each equation in the set. \sa TequationInfo */

  unsigned int mm;          /**< Maximum number of matrix equations. */
  unsigned int nm;          /**< Current number of matrix equations. */
  TMequation **mequation;   /**< Set of matrix equations. */
  
  unsigned int nsEQU;       /**< Number of scalar equality equations.
			         We cache information about non-empty equality equations to speed up evaluation.
			         Some equation sets (i.e., Jacobian) include many empty equations and this
			         slows down the evaluation. This cached information does not affect matrix equations. */
  Tequation **eqEQU;        /**< Direct pointer to the non-empty EQU equation. */
} Tequations;

/** 
  \brief Constructor.
 
  Initializes a set of equations.

  \param eqs The equation set to be initialized.
*/
void InitEquations(Tequations *eqs);

/** 
  \brief Copy constructor.
 
  Initializes a set of equations from another set.

  \param eqs_dst The equation set to be initialized.
  \param eqs_src The equation set from where to get the information.
*/
void CopyEquations(Tequations *eqs_dst,Tequations *eqs_src);

/** 
  \brief Copy constructor.
 
  Initializes a set of equations with the non-dynamic part of another set.

  \param eqs_dst The equation set to be initialized.
  \param eqs_orig If the source equations are derived equations, we provide the
                  original set of equations (the ones before deriving).
  \param eqs_src The equation set from where to store the information.
*/
void CopyNonDynamicEquations(Tequations *eqs_dst,Tequations *eqs_orig,Tequations *eqs_src);

/** 
  \brief Copy constructor.
 
  Initializes a set of equations with the position part of another set.

  \param eqs_dst The equation set to be initialized.
  \param eqs_orig If the source equations are derived equations, we provide the
                  original set of equations (the ones before deriving).
  \param eqs_src The equation set from where to store the information.
*/
void CopyPositionEquations(Tequations *eqs_dst,Tequations *eqs_orig,Tequations *eqs_src);

/** 
   \brief Rewrites the equations to the original system.

   For a system of equations in a simplified form, we change the variable
   identifiers by those in the orignal system. Note that this is just
   a variable identifier replacement since all the variables in the
   simplified system are also in the original.
   
   \param map The map from the simplified system to the original.
   \param eqs The equations to map.
*/
void RewriteEqs2Orig(Tmapping *map,Tequations *eqs);

/** 
  \brief Copy constructor.
 
  Adds a set of equations to another.

  \param eqs1 The equation set to add.
  \param eqs The set where to add the equations.
*/
void MergeEquations(Tequations *eqs1,Tequations *eqs);

/** 
  \brief Checks if a variable is used in the set of equations.

  Checks if a variable is used in non-dummy equations of the set of equations.

  \param nv The identifier of the variable to look for.
  \param eqs The equation set from where to get the information.

  \return TRUE if the variable \e nv appears in any of the non-dummy equations of
          the set \e eqs.
*/
boolean UsedVarInNonDummyEquations(unsigned int nv,Tequations *eqs);

/** 
  \brief Checks if a variable is used in the set of equations.

  Checks if a variable is used in the set of equations.

  \param nv The identifier of the variable to look for.
  \param eqs The equation set from where to get the information.

  \return TRUE if the variable \e nv appears in the set \e eqs.
*/
boolean UsedVarInEquations(unsigned int nv,Tequations *eqs);


/** 
  \brief Removes all equations that include a given variable.

  Removes all equations that include a given variable. This is one of the
  steps to remove a non-used variable from a problem. Therefore,
  equations that do not include the given variable are also affected
  by this function: we have to shift all the variable indexes higher
  than the given one.

  Dummy equations using the variable are also removed. Hence the
  name of this function.

  The use of this function without using function \ref RemoveVariable
  right immediately after it leaves the cuiksystem in a incoherent
  state.

  \param epsilon Monomials with a constant below epsilon are eliminated.
  \param nv The identifier of the variable to remove.
  \param eqs The set of equations to update.
*/
void RemoveEquationsWithVar(double epsilon,unsigned int nv,Tequations *eqs);


/** 
  \brief Replaces a variable with a linear expression.

  Replaces a variable by linear combination of variables (including an offset).
  
  The use of this function without using function \ref RemoveVariable
  right immediately after it leaves the cuiksystem in a incoherent
  state.

  \param epsilon Monomials with a constant below epsilon are eliminated.
  \param nv The variable to replace.
  \param lc The linear constraint to use in the replacement.
  \param eqs The equation set from where to get the information.

  \return TRUE the equation set still holds after replacing the equation.
  
  \sa SimplifyCuikSystem
*/
boolean ReplaceVariableInEquations(double epsilon,unsigned int nv,
				   TLinearConstraint *lc,Tequations *eqs);

/** 
  \brief Perform Gaussian elimination on the set of equations.

  Operates linearly pairs of equations (scale one of the and then sum them)
  with the objective of getting a simpler equation (i.e., one with less monomials).
  The rationale is that equations with less monomials produce simpler problems and,
  in some cases, they can trigger simplifications that are not evident at first sight.
  
  The use of this function without using function \ref RemoveVariable
  right immediately after it leaves the cuiksystem in a incoherent
  state.

  \param eqs The equation set to be simplified.

  \return TRUE the equation set still holds after replacing the equation.
  
  \sa AccumulateEquations, SimplifyCuikSystem
*/
boolean GaussianElimination(Tequations *eqs);

/** 
  \brief Number of equations in the set.

  Number of equations in the set.

  \param eqs The equation set.

  \return The number of equations in the set.
*/
unsigned int NEquations(Tequations *eqs);

/** 
  \brief Number of scalar equations in the set.

  Number of scalar equations in the set.

  \param eqs The equation set.

  \return The number of scalar equations in the set.
*/
unsigned int NScalarEquations(Tequations *eqs);

/** 
  \brief Number of system equations in the set.

  Number of system equations in the set.

  \param eqs The equation set.

  \return The number of system equations in the set.
*/
unsigned int NSystemEquations(Tequations *eqs);

/** 
  \brief Number of coordenalization equations in the set.

  Number of coordenalization equations in the set.

  \param eqs The equation set.

  \return The number of coordenalization equations in the set.
*/
unsigned int NCoordEquations(Tequations *eqs);

/** 
  \brief Number of dummy equations in the set.

  Number of dummy equations in the set.

  \param eqs The equation set.

  \return The number of dummy equations in the set.
*/
unsigned int NDummyEquations(Tequations *eqs);

/** 
  \brief Number of position equations in the set.

  Number of position equations in the set.

  \param eqs The equation set.

  \return The number of position equations in the set.
*/
unsigned int NPositionEquations(Tequations *eqs);

/** 
  \brief Number of velocity equations in the set.

  Number of velocity equations in the set.

  \param eqs The equation set.

  \return The number of velocity equations in the set.
*/
unsigned int NVelocityEquations(Tequations *eqs);

/** 
  \brief Number of non dynamic equations in the set.

  Number of non dynamic equations in the set
  (equations not directly related with the position
  and velocity of the system).

  \param eqs The equation set.

  \return The number of non dynamic equations in the set.
*/
unsigned int NNonDynamicEquations(Tequations *eqs);

/** 
  \brief Number of equalities in the set.

  Number of equality equations in the set.

  \param eqs The equation set.

  \return The number of equality equations in the set.
*/
unsigned int NEqualityEquations(Tequations *eqs);

/** 
   \brief Number of equality position equations.

   Number of equality position equations.

   \param eqs The equation set.

   \return The number of position equality equations in the set.
*/
unsigned int NEqualityPositionEquations(Tequations *eqs);
  
/** 
   \brief Number of scalar equality position equations.

   Number of scalar equality position equations.

   \param eqs The equation set.

   \return The number of scalar position equality equations in the set.
*/
unsigned int NEqualityScalarPositionEquations(Tequations *eqs);

/** 
  \brief Number of inequalities in the set.

  Number of inequality equations in the set.

  \param eqs The equation set.

  \return The number of inequality equations in the set.
*/
unsigned int NInequalityEquations(Tequations *eqs);

/** 
  \brief Number of matrix equations in the set.

  Number of matrix equations in the set.

  \param eqs The equation set.

  \return The number of matrix equations in the set.
*/
unsigned int NMatrixEquations(Tequations *eqs);

/** 
  \brief Number of kino equations in the set.

  Number of kino-equations in the set.

  \param eqs The equation set.

  \return The number of kino-equations in the set.
*/
unsigned int NKinoEquations(Tequations *eqs);

/** 
   \brief Identify polynomial system of equations.

   Identify polynomial system of equations.

   \param eqs The equation set to query.

   \return TRUE if the set is composed only by polynomial equations.
*/
boolean PolynomialEquations(Tequations *eqs);

/** 
   \brief Identifies scalar systems.

  Identifies scalar systems (systems with no matrix equations).

  \param eqs The equation to check.
*/
boolean ScalarEquations(Tequations *eqs);

/** 
   \brief Identifies equality equations.

   Identifies equality equations.

   \param i The identifier of the equation to check.
   \param eqs The equation set.

   \return TRUE if the selecte equation is an equality equation.
*/
boolean IsEqualityEquation(unsigned int i,Tequations *eqs);

/** 
   \brief Identify system equations.

   Identify system equations.

   \param i The identifier of the equation to check.
   \param eqs The equation set.

   \return TRUE if the selecte equation is a system equation.
*/
boolean IsSystemEquation(unsigned int i,Tequations *eqs);

/** 
   \brief Identify coordenalization equations.

   Identify coordenalization equations.

   \param i The identifier of the equation to check.
   \param eqs The equation set.

   \return TRUE if the selected equation is a coordenalization equation.
*/
boolean IsCoordEquation(unsigned int i,Tequations *eqs);

/** 
   \brief Identify dummy equations.

   Identify dummy equations.

   \param i The identifier of the equation to check.
   \param eqs The equation set.

   \return TRUE if the selected equation is a dummy equation.
*/
boolean IsDummyEquation(unsigned int i,Tequations *eqs);

/**  
   \brief Identify position equations.

   Identify position equations. Position equaitons are equations
   that are neither velocity nor non-dynamic equations.

   \param i The identifier of the equation to check.
   \param eqs The equation set.

   \return TRUE if the selected equation is a position equation.
*/
boolean IsPositionEquation(unsigned int i,Tequations *eqs);

/** 
   \brief Identify velocity equations.

   Identify velocity equations.

   \param i The identifier of the equation to check.
   \param eqs The equation set.

   \return TRUE if the selected equation is a velocity equation.
*/
boolean IsVelocityEquation(unsigned int i,Tequations *eqs);

/** 
   \brief Identify non-dynamic equations.

   Identify non-dynamic equations.

   \param i The identifier of the equation to check.
   \param eqs The equation set.

   \return TRUE if the selected equation is a non-dynamic equation.
*/
boolean IsNonDynamicEquation(unsigned int i,Tequations *eqs);

/** 
   \brief Gets the type of a particular equation.

   Gets the type of a particular equation.

   \param i The identifier of the equation to check.
   \param eqs The equation set.

   \return The type of the selected eqution of NOTYPE_EQ if there is no
           equation with the given identifier in the set.
*/
unsigned int GetEquationTypeN(unsigned int i,Tequations *eqs);

/** 
   \brief Checks if a given equation is already in the set.

   Checks if a given equation is already in the set.

   \param equation The equation.
   \param eqs The equation set.

   \return TRUE if the given equation is already in the set.
*/
boolean HasEquation(Tequation *equation,Tequations *eqs);

/** 
   \brief Adds an equation to the set.

   Adds an equation to the set and computes its associated information.
   Empty equations (equations with no monomials) or repeated equations
   are not added to the set.
   Moreover, equations are sorted from  simplest to more complex.

   \param equation The equation to be added.
   \param eqs The equation set.

   \sa TequationInfo.
*/
void AddEquation(Tequation *equation,Tequations *eqs);

/** 
   \brief Adds an equation to the set.

   Adds an equation to the set and computes its associated information.
   This is like \ref AddEquation but all equations are considered
   (even the empty or repeated ones) and equations are not sorted.
   This must be used in equation sets where the order of the equations
   must be preserved. This happens for some equations sets defined
   in the \ref Tworld.

   \param equation The equation to be added.
   \param eqs The equation set.

   \sa TequationInfo.
*/
void AddEquationNoSimp(Tequation *equation,Tequations *eqs);

/** 
   \brief Adds a matrix equation to the set.

   Adds a matrix equation to the set and computes its associated information.

   \param equation The equation to be added.
   \param eqs The equation set.
*/
void AddMatrixEquation(TMequation *equation,Tequations *eqs);

/** 
   \brief Adds a kino equation to the set.

   Adds a kino equation to the set and computes its associated information.

   \param equation The equation to be added.
   \param eqs The equation set.
*/
void AddKinoEquation(TKequation *equation,Tequations *eqs);

/** 
   \brief Gets an equation from the set.

   Returns a pointer to the \e n-th equation stored in the set.

   \param n The number of equation to get.
   \param eqs The equation query.
*/
Tequation *GetEquation(unsigned int n,Tequations *eqs);

/** 
  \brief Gets a scalar equation from the set.

  Returns a pointer to the \e n-th scalar equation stored in the set.

  \param n The number of scalar equation to get.
  \param eqs The equation query.
*/
Tequation *GetScalarEquation(unsigned int n,Tequations *eqs);

/** 
  \brief Gets a matrix equation from the set.

  Returns a pointer to the \e n-th matrix equation stored in the set.

  \param n The number of matrix equation to get.
  \param eqs The equation query.
*/
TMequation *GetMatrixEquation(unsigned int n,Tequations *eqs);

/** 
  \brief Gets a kino equation from the set.

  Returns a pointer to the \e n-th kino equation stored in the set.

  \param n The number of kino equation to get.
  \param eqs The equation query.
*/
TKequation *GetKinoEquation(unsigned int n,Tequations *eqs);

/** 
  \brief Equation-wise crop.

  Gets a box (as an array of parameters \e is of size \e m) and
  uses the equation number \e ne to reduce the ranges of the variables
  involved in the equation as much as possible.<br>
  Only equalities are used for crop (LEQ and GEQ equations are not taken
  into account).<br>
  We use different crop procedures according to the type of equation:
  LINEAR_EQ, PARABOLA_EQ, SADDLE_EQ, CIRCLE_EQ, SPHERE_EQ or GENERAL_EQ.
  In the GENERAL_EQ  case, equations a the linear
  approximation is used for the crop. This does not produce the stronger
  possible crop. For this reason, we implemented non-linear crop for the
  non-linear equations that appear often in the systems of equations (due
  to dummification, for instance).

  \param ne The equation to use in the crop.
  \param varType The type of variables to which apply the crop. Use \ref ANY_TYPE_VAR
                 for the crop to affect all types of variables.
  \param epsilon Only ranges with a size larger than epsilon are reduced.
  \param rho The crop is repeated as far as the ranges for the variables in the equation
             reduce a ratio larger than \e rho.
  \param b The box with the ranges to crop.
  \param vs The variable set on which the equations are defined. Used to get the type 
            of variables.
  \param eqs The equation set.

  \return \ref NOT_REDUCED_BOX, \ref EMPTY_BOX, \ref REDUCED_BOX

  \sa ReduceBoxEquationWise
*/
unsigned int CropEquation(unsigned int ne,
			  unsigned int varType,
			  double epsilon,double rho,
			  Tbox *b,
			  Tvariables *vs,
			  Tequations *eqs);

/** 
  \brief Adds an equation to the simplex.

  Adds linear constraints representing the selected equation (i.e., a linear
  relaxation of the equation) to 
  a simplex tableau. Linear constraints are directly added to the
  simplex using the information cached in the TequationInfo
  structure. Non linear equations are linearized using the
  information stored in the Jacobian and Hessian fields in the
  corresponding TequationInfo too.
  Different equations are linearized in a different way
  - For Parabola equations y=x^2: Two planes defined at the center of
    the x range and, if the variables in the equation are larger
    than lr2tm_q, we add one plane at each one of the extremes of the x range.
  - For Circle equations x^2+y^2=r^2: Two planes defined at the center of
    the x-y range and, if the variables in the equation are larger
    than lr2tm_q, we add one plane tangent to the circle for the corners of
    the x-y box that are out of the circle. 
   - For Sphere equations x^2+y^2+z^2=r^2: Two planes defined at the center of
    the x-y-z range and, if the variables in the equation are larger
    than lr2tm_q, we add one plane tangent to the sphere for the corners of
    the x-y-z box that are out of the sphere.
  - For Saddle equations z=x*y: if the variables in the equation are larger
    than lr2tm_s, we add one plane for each corner of the x-y square.
    Otherwise we linearize the equation as a general equation (two planes
    defined at the center of the x,y,z box).
  - For the rest of equations, a couple of planes defined from the
    linearization of the equation at the center of the sub-box defined
    by the variables involved in the equation plus-less an error defined
    from the remainder of the linearization. For equalities we add the two
    planes defined in such a way but for inequalities only one plane is
    necessary.
  .

  By using small lr2tm_q and lr2tm_s we generate linear relaxations
  that tightly bound the functions and this reduces the number of iterations
  to found the solution. The drawnback is that we we add more constraints
  to the simplex and this slows downs each iteration. 

  Equations that define particular variables (cartesian or dummy ones) are
  only added to the simplex if the variable is used in any of the other
  constraints already in the simplex. Otherwise we will add useless constraints.
  This filter is implemented with the array of booleans \e usedVar. This
  array is updated as we add equations to the simplex and is checked to see
  if \e defined variables are used before adding the corresponding equation
  to the simplex. For this to be operative, equations are ordered so that
  system equations are added first to the simplex, then cartesian equations
  and, finally, dummyfications equations.

  There is no need to equations that involves almost constant variables 
  to the simplex.
  Thus, before adding an EQU equation to the simplex, 
  we evaluate the equations using interval arithmetics and if the result is almost
  constant(this occurs if the variables involved in the equation are have tiny
  ranges) we just check if the equation holds or not.
  If not, the system has no solution.

  The same applies to inequalities that already hold. An inequality (LEQ, GEQ equations)
  that trivially holds do not add any constrain to the simplex and, consequently
  we do not add it to the Tableau.
  

  \param ne The number of the equation to add.
  \param lr2tm_q Size of the variables in the equation to switch
                 between a specific linearization and a general one
		 for spheres, circles, and parabolas.
  \param lr2tm_s Size of the variables in the equation to switch
                 between a specific linearization and a general one
		 for saddle equations.
  \param epsilon When generating a linear constraints, coefficients
                 below epsilon are discarted, since the simplex
		 process has troubles with too small values.
  \param safeSimplex Degree of numerical stability in the simplex as specified by
                     the user in the \ref CT_SAFE_SIMPLEX "SAFE SIMPLEX" parameter.
  \param rho Before adding the equation to the simplex it is croped
             and the crop process is repeated as far as the variables
	     reduce more than rho.
             Ranges smaller than epsilon are not reduced any further.
  \param b The box with the variable ranges. It defines the area where
           to linearize the equations and where to compute the linearization
	   error, if necessary.
  \param vs The set of variables. Used to get the type of variables in
            GetDefinedVar 
  \param lp The simplex structure where to add the constraints.
  \param eqs The equation set.

  \sa CropEquation, GetDefinedVar

  \return TRUE if the simplex is still feasible after adding the linear constraints.
  
*/
boolean AddEquation2Simplex(unsigned int ne,
			    double lr2tm_q,double lr2tm_s,
			    double epsilon,unsigned int safeSimplex,double rho,
			    Tbox *b,Tvariables *vs,
			    TSimplex *lp,Tequations *eqs);

/** 
   \brief Computes the linearization error induced by the variables of
          a given equation.

   When the SPLIT_ERROR parameter is set to TRUE, we select the split variable 
   for a box from the linearization error induced by the variables. This
   function updates the error induced by the variables in a given equation.

   \param ne The equation to use in the update.
   \param splitDim The array with the linearization errors induced
                   by the variables to be updated.
   \param b The box with the ranges for the variables.
   \param eqs The equation set.
 */
void UpdateSplitWeight(unsigned int ne,double *splitDim,
		       Tbox *b,Tequations *eqs);

/** 
   \brief Multiplies all equality equations by a given variable.

   All equality equations (scalar and matrix equations) are scaled
   by a given variable.

   This is used when defining linear combinations of equations, for
   instance when defining the velocity equations from the Jacobian.
   Thus, all equations processed with this function are converted
   in \ref VELOCITY_EQ "velocity equations"

   \param nv The identifier of the variable to use in the scaling.
   \param velocity TRUE if we are defining a set of velocity equations.
                   The generated equations are marked as velocity equations.
   \param eqs The equation set with the equalities to scale.
*/
void VarScaleEqualityEquations(unsigned int nv,boolean velocity,Tequations *eqs);

/** 
   \brief Multiplies all equality equations by a given variable and
          accumulates them in another set.

   All equality equations (scalar and matrix equations) are scaled
   by a given variable and accumulated into another set.

   This is used when defining linear combinations of equations, for
   instance when defining the velocity equations from the Jacobian.
   Thus, all equations processed with this function are converted
   in \ref VELOCITY_EQ "velocity equations"

   \param nv The identifier of the variable to use in the scaling.
   \param eqs1 The equation set with the equalities to scale.
   \param velocity TRUE if we are defining a set of velocity equations.
                   The generated equations are marked as velocity equations.
   \param eqs The equation set where to add the scaled equations.
*/
void VarAccumulateEqualityEquations(unsigned int nv,boolean velocity,
				    Tequations *eqs1,Tequations *eqs);

/**  
   \brief Evaluates all equality equations in the set.

   Evaluates all equality equations in the set. This includes the equality
   scalar equations and all matrix equations.

   \param systemOnly TRUE to evaluate only the system equalities. The rest
                     are evalated to 0 (as if they hold).
   \param v The value for the variables.
   \param r the array where to store the result.
   \param eqs The equations to evaluate.
*/
void EvaluateEqualityEquations(boolean systemOnly,double *v,double *r,Tequations *eqs);

/** 
   \brief Evaluates a subset of the equality equations in the set.

   Evaluates a subset of the equality equations in the set. This includes the equality
   scalar equations and some of the matrix equations.

   \param v The value for the variables.
   \param se The selected equations. This is a subset of the equality equations, not
             of all equations. Thus the size of this boolean array must the one
	     returned by \ref NEqualityEquations.
   \param r the array where to store the result. The size of this array is the same
            as the number of TRUE entries in array 'se'. The space must be allocated
	    externally.
   \param eqs The equations to evaluate.
*/
void EvaluateSubSetEqualityEquations(double *v,boolean *se,double *r,Tequations *eqs);

/** 
   \brief Evaluates the a subset of the position scalar equations.

   \param v The evaluation point.
   \param se The subset of the position scalar equations to use. NOTE this array
             is over the equality position equations and the scalar equations are assumed
	     to be the first ones in the whole set of equations.
   \param r The array where to store the results.
   \param eqs The equation set.

   \return The space of the output vector actually used. Number of selected position
           scalar equations.
*/
unsigned int EvaluatePositionScalarEqs(double *v,boolean *se,double *r,Tequations *eqs);

/** 
   \brief Collects information about scalar equality equations.

    Collects information about scalar equality equations to accelerate
    the evaluation when the equation set is sparse. This happens quite
    often in the equation systems of the Jacobian. We collect the
    information with the aim of accelerating the evaluation of these
    equation systems, which is fundamental in atlas-based tools.

    \param eqs The equation system to analyse.
*/
void CacheScalarEQUInfo(Tequations *eqs);

/** 
   \brief Evaluates the set of equality equations for sparse systems.

   In sparse systems, many equations are empty. This function is a variant of
   \ref EvaluateEqualityEquations specialy efficient for this kind of
   systems.

   IMPORTANT: This function will not work if \ref CacheScalarEQUInfo
       has not been called before.

   \param v The value for the variables.
   \param r the array where to store the result.
   \param eqs The equations to evaluate.
*/
void EvaluateEqualitySparseEquations(double *v,double *r,Tequations *eqs);

/** 
   \brief Evaluates a subset of the set of equality equations for sparse systems.

   In sparse systems, many equations are empty. This function is a variant of
   \ref EvaluateSubSetEqualityEquations specialy efficient for this kind of
   systems.

   \param v The value for the variables.
   \param se The selected equations. This is a subset of the equality equations, not
             of all equations. Thus the size of this boolean array must the one
	     returned by \ref NEqualityEquations.
   \param r the array where to store the result. The size of this array is the same
            as the number of TRUE entries in array 'se'. The space must be allocated
	    externally.
   \param eqs The equations to evaluate.
*/
void EvaluateSubSetEqualitySparseEquations(double *v,boolean *se,double *r,Tequations *eqs);

/** 
    \brief  Evaluates the matrix equations multiplied by some given vectors.

    This is a funcition with a very particular purpose. It evaluates
    a matrix equation M, and it returns M*v[i]
    for a set of 3D vectors, v[i].

    See \ref EvaluateJacobianXVectors for more details on why
    this is necessary.

    This function triggeres an error if the equation set includes
    scalar equations.

    \param v The values for the variables.
    \param ng Number of groups of vectors. We must have one group for each
              matrix equation.
    \param g Number of vectors in each group.
    \param p The 3D vectors (stacked in one array).
    \param r The output vector.
    \param eqs The matrix equations to evaluate.
*/
void EvaluateEquationsXVectors(double *v,unsigned int ng,unsigned int *g,double *p,
			       double *r,Tequations *eqs);

/** 
   \brief Error in inequalities.

   Evaluates all inequalities and returns and array with the error
   in each of them. The error is 0 if the inequality hold.

   \param v The value for the variables.
   \param r the array where to store the result.
   \param eqs The equations to evaluate.
*/
void EvaluateInequalityEquations(double *v,double *r,Tequations *eqs);

/** 
   \brief Derives the position scalar equations in a set.

   Derives the subset of scalar position equation with respect to a given variable.
   The derivative is only computed for equality equations.

   \param v The derivation variable.
   \param deqs The resulting derived equations.
   \param eqs The equations to derive.
*/
void DeriveEqualityScalarPositionEquations(unsigned int v,Tequations *deqs,Tequations *eqs);

/** 
   \brief Derives the position equations in a set.

   Derives the subset of position equation with respect to a given variable.
   The derivative is only computed for equality equations.

   \param v The derivation variable.
   \param deqs The resulting derived equations.
   \param eqs The equations to derive.
*/
void DeriveEqualityPositionEquations(unsigned int v,Tequations *deqs,Tequations *eqs);

/** 
   \brief Derives an equation set.

   Derives an equation set with respect to a given variable.
   The derivative is only computed for equality equations.

   \param v The derivation variable.
   \param deqs The resulting derived equations.
   \param eqs The equations to derive.
*/
void DeriveEqualityEquations(unsigned int v,Tequations *deqs,Tequations *eqs);

/** 
   \brief Prints a set of equations.

   Writes a set of equations into a stream.

   \param f The stream where to write the equations.
   \param varNames The name of the variables.
	          If this parameter is NULL the printed
	          names for the variables are <em>v_X</em> with \e X the index
	          of the variable.
   \param eqs The equation set to print.

*/
void PrintEquations(FILE *f,char **varNames,Tequations *eqs);

/** 
  \brief Destructor
  
  Deletes the information stored in the set of equations and 
  frees the allocated memory space.
  
  \param eqs The set of equations to delete.
 */
void DeleteEquations(Tequations *eqs);

#endif
