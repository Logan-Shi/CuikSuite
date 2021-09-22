#ifndef LINEARCONSTRAINT
#define LINEARCONSTRAINT

#include "interval.h"
#include "boolean.h"
#include "variables.h"
#include "box.h"

#include <stdio.h>


/** \file linear_constraint.h
    \brief Definition of the TLinearConstraint type and the associated functions.

    Definition of the TLinearConstraint type and the associated functions.

    \todo It might be possible to joint into a single type Tequation and TLinearConstraint.
          Some of the functions in the simplex could be slightly solwer but we could
	  simplify a little the \b CuikSuite structure.

    \sa TLinearConstraint, linear_constraint.c.
*/

/************************************************************************************/
/** \brief Initial room for terms in a linear constraint. 

    Initial room for terms in a linear constraint. It will be enlarged if necessary.

    \sa TLinearConstraint
*/
#define INIT_NUM_TERMS_LC 100
/************************************************************************************/

/** 
    \brief A linear constraint with an associated error.

    A linear constraint is a sum of weighted variables equated to a right-hand value. 
    In this implementation, the right-hand value is an interval and, thus, linear
    constraints are to be in the given range. By representing linear constraints in
    this way we can easily add them to the simplex tableaus.
    
    Obseve that when operating linear constraints (scale, add, etc.) some numerical
    errors are introduced. Therefore the scale factors for each variable (i.e., the values
    stored in the \e val field) are only approximations to the correct values. To try to
    compensate for such numerical errors, every time we have to evalute (crop,...) a linear
    constraint, we treat the scale factors as tiny intervals adding them a [-\ref ZERO,\ref ZERO]
    interval (\ref ZERO is about 1e-11).

    \sa linear_constraint.h, linear_constraint.c
*/
typedef struct {
  unsigned int n;    /**< Current number of variables in the linear constraint.*/
  unsigned int max;  /**< Maximum number of variables in the linear constraint.*/
  unsigned int *ind; /**< Indexes of the variables involved in the linear constraint.*/
  double *val;       /**< Scale factors for each variable. */
  Tinterval error;   /**< Interval representing the right-hand side of the linear constraint. */
} TLinearConstraint;


/** 
   \brief Constructor.

   Creates a new, empty linear constraint.

   \param lc The linear constraint to initialize.
*/
void InitLinearConstraint(TLinearConstraint *lc);


/** 
   \brief Resets a linear constraint.

   Deletes the information stored in a linear constrain, but does not frees the memory.
   It is more efficient to use ResetLinearConstraint instead of DeleteLinearConstraint plus 
   InitLinearConstraint again.

   \param lc The linear constraint to be reseted.
*/
void ResetLinearConstraint(TLinearConstraint *lc);

/** 
   \brief Copy constructor.

   Creates a new linear constraint from another one.

   \param lc_dst The linear constraint to initialize.
   \param lc_src The linear constraint from where to copy.
*/
void CopyLinearConstraint(TLinearConstraint *lc_dst,TLinearConstraint *lc_src);

/** 
   \brief Test if the constraint is bounded.
   
   Test if the linear constraint actually constraint anything.
   This happens when the error of the linear constraint is not [-INF,+INF].
   Unbounded constraints typically appear in equations including tangents o secants.

   Only ounded linear constraints are added to the simplex.

   \param lc The linear constraint to check.

   \return TRUE if the error of the linear constrint is not [-INF,INF].
*/
boolean BoundedLinearConstraint(TLinearConstraint *lc);

/** 
   \brief Number of variables in a linear constraint.

   Returns the number of variables involved in a linear constraint.

   \param lc The linear constraint.

   \return The number of variables involved in a linear constraint.
*/
unsigned int GetNumTermsInLinearConstraint(TLinearConstraint *lc);


/** 
   \brief Gets the linear constraint coefficients.

   Returns the coefficients (i.e., the scale factors) in a linear constraint.

   \param lc The linear constraint.

   \return A pointer to an array of doubles with the variable scale factors.
*/
double *GetLinearConstraintCoefficients(TLinearConstraint *lc);


/** 
   \brief Gets the a particular linear constraint coefficient.

   Returns the coefficient (i.e., the scale factor) for a particular
   variable in a linear constraint. Note that the index of the variable
   refers to its position in the linear constraint and it is not the
   global identifier of the variable.<br>
   If the linear constraint has less than \e i variables this function
   triggers an error.
   
   \param i The index of the variable in the linear constraint.
   \param lc The linear constraint.

   \return The variable scale factor. 
*/
double GetLinearConstraintCoefficient(unsigned int i,TLinearConstraint *lc);

/** 
   \brief Gets the linear constraint variables.

   Returns the variables in a linear constraint.

   \param lc The linear constraint.

   \return A pointer to an array with the index of the variables involved in the
           linear constraint.
*/
unsigned int *GetLinearConstraintVariables(TLinearConstraint *lc);

/** 
   \brief Gets the a particular variable index.

   Returns the identifier of the \e i-th variable involved in the linear
   constraint. 
   
   \param i The index of the variable in the linear constraint.
   \param lc The linear constraint.

   \return The global identifier of the \e i-th variable in the linear constraint. 
*/
unsigned int GetLinearConstraintVariable(unsigned int i,TLinearConstraint *lc);

/** 
   \brief Gets the right-hand side interval for the linear constraint.

   Returns the right-hand side interval for the linear constraint.
   
   \param error Output interval with the right-hand side of the linear constraint.
   \param lc The linear constraint.
*/
void GetLinearConstraintError(Tinterval *error,TLinearConstraint *lc);

/** 
   \brief Gets the size of the right-hand side interval for the linear constraint.

   Returns the size of the right-hand side interval for the linear constraint.
   
   \param lc The linear constraint.

   \return The size of the error interval for the linear equation.
*/
double GetLinearConstraintErrorSize(TLinearConstraint *lc);

/** 
   \brief Sets a new righ-hand side error of the linear constraint.

   Sets a new righ-hand side error of the linear constraint. 
   
   \param error The new linear constraint error.
   \param lc The linear constraint.
*/
void SetLinearConstraintError(Tinterval *error,TLinearConstraint *lc);

/** 
   \brief Adds a constant term to the linear constraint.

   Shifts the righ-hand side error of the linear constraint by the given value
   (changing the sign to move it to the righ-hand side).
   
   \param ct The ct to add to the linear constraint.
   \param lc The linear constraint.
*/
void AddCt2LinearConstraint(double ct,TLinearConstraint *lc);

/** 
   \brief Adds a scaled variable to the linear constraint.

   Adds a scaled variable to the linear constraint. If the varaible was already
   present in  the constraint, we just add the scale factors.
  
   \param ind Global identifier of the variable to add to the linear constraint.
   \param val Scale factor for the variable.
   \param lc The linear constraint.
*/
void AddTerm2LinearConstraint(unsigned int ind,double val,TLinearConstraint *lc);

/** 
   \brief Removes a variable from a linear constraint.

   Removes a variable from a linear constraint.
   
   \param ind Identifier of the variable to remove from the linear constraint.
   \param lc The linear constraint to update.

   \return The scale factor associated with the removed variable.
*/
double RemoveTermFromLinearConstraint(unsigned int ind,TLinearConstraint *lc);

/** 
   \brief Checks if a variable is included in a linear constraint.

   Checks if a variable is included in a linear constraint.

   \param ind Identifier of the variable.
   \param lc The linear constraint to check.

   \return TRUE if the variable is included in the linear constraint.
*/
boolean LinearConstraintIncludes(unsigned int ind,TLinearConstraint *lc);

/** 
   \brief Determines the factor of a given variable in a linear constraint.

   Checks if a variable is included in a linear constraint and returns
   its factor. Note that the returned factor can be seen as the
   derivative of the linear constraint w.r.t. the given variable.

   \param ind Identifier of the variable.
   \param lc The linear constraint to check.

   \return The scale factor associated with the removed variable. 0 if the
           variable is not included in the linear constraint.
*/
double LinearConstraintFactor(unsigned int ind,TLinearConstraint *lc);

/** 
   \brief Changes the sign of a linear constraint.

   Changes the sign of a linear constraint.

   \param lc The linear constraint to invert.
*/
void InvertLinearConstraint(TLinearConstraint *lc);

/** 
   \brief Scales  a linear constraint.

   Scales a linear constraint.

   \param a the scale factor.
   \param lc The linear constraint to be scaled.
*/
void ScaleLinearConstraint(double a,TLinearConstraint *lc);

/** 
   \brief Adds one linear constraint to another.

   Adds two a linear constraints.

   \param lc1 The first linear constraint to add.
   \param lc The second linear constraint to add and the place where the output is stored.
*/
void AddLinearConstraints(TLinearConstraint *lc1,TLinearConstraint *lc);

/** 
   \brief Removes terms in the linear constraint that give too small ranges.

   Variables in the linear constraint with very narrow range or scaled by tiny
   scale factors  can be removed and
   added to the error term. This enhances the numerical robustness of the system. 

   This can lead to tiny error ranges. If the

   When using GLPK it is \b compulsatory to use


   \param epsilon Used to purge variables with a tiny scale factors. This is done
                  as a requirement of the simplex implementations that are unstables
		  for tiny coefficients.
   \param is Ranges for all the variables in the problem.
   \param lc The linear constraint to clean.
*/
void CleanLinearConstraint(double epsilon,Tinterval *is,TLinearConstraint *lc);

/** 
   \brief Apply linear constraints to reduce the ranges of the problem variables.

   Linear constraints involving only one variable can be directly used to
   reduce the variable range. We compute the range for the variable as<br>
   <center><em>ct x = error</em></center><br>
   <center><em>x = error/ct</em></center><br>
   and we intersect this with the given range for variable \e x.

   Only linear equations with just one variable are feasible to be used to 
   directly reduce variable ranges.

   Linear constraints that can be directly applied do not need to be added to the simplex.

   \param full If the applied simplification, if any, produces a feasible system (i.e., if
               the intersection of the previous range for the variable and the new one
	       is not empty).
   \param is Ranges for all the variables in the problem. If the linear constriant triggers
             a simplification, the range for the variable in the constraint is updated.
   \param lc The linear constraint.

   \return TRUE if the constraint actually triggered a simplification (i.e., if the
   linear constraint involves only one variable).
*/
boolean SimplifyLinearConstraint(boolean *full,Tinterval *is,TLinearConstraint *lc);

/** 
   \brief Reduce the ranges for.

    We have that a linear constraint can be manipulated as
    <em>
    <center>
    Sum_i k_i x_i = error, <br>
    Sum_i k_i x_i - k_j x_j + k_j x_j = error,  <br>
    k_j x_j= error - Sum_(i!=k) k_i x_i,   <br>
    x_j = (error + Sum_(i!=k) - k_i x_i))/ k_j, <br>
    </center>
    </em>
    that can be evaluated using interval arithmetics.

    Thus, a linear constraint can be used to compute a new range for
    all the variables in the constraint that can be intersected with
    the given range, possibly producing a range reduction.


   This can be seen as a generalization of SimplifyLinearConstraint for the
   case where the linear constraint involves more than one variable.

   \param epsilon Numerical tolerance.
   \param varType The type of variables to which apply the crop. Use \ref ANY_TYPE_VAR
                  for the crop to affect all types of variables.
   \param b The box with the ranges for the varibles. 
   \param vs The variable set on which the equations are defined. Used to get the type 
             of variables.
   \param lc The linear constraint.
*/
unsigned int CropLinearConstraint(double epsilon,
				  unsigned int varType,
				  Tbox *b,
				  Tvariables *vs,
				  TLinearConstraint *lc);

/** 
   \brief Compares two linear constraints.

   We compare the linear constraints first checking if they involve  the
   same sub-set of variables, and then computing
   the cosinus of the angle between them (i.e., between
   the vectors defining the hyperplane of the constraint).

   The output \e scaleOne2Two gives the constant so that lc1*scaleOne2Two=lc2

   \param scaleOne2Two gives ct so that lc1*scale=lc2. Only valid if the function returns TRUE.
   \param lc1 The first linear constraint to compare.
   \param lc2 The second linear constraint to compare.

   \return TRUE if the linear constrants are equivalent: if they invove the same set of
           variables and the cosinus between the vectors is close (up to \ref ZERO) to 1 or to -1.
*/
boolean CmpLinearConstraints(double *scaleOne2Two,TLinearConstraint *lc1,TLinearConstraint *lc2);

/** 
   \brief Evaluates a linear combination for a given point

  Evaluates a linear combination for a given point
 
  \b NOTE: The right-hand side of the linear constraint (represented as a
  error interval) is not taken into account in the evaluation.

  \param varValues Values defining the point where to evaluate the equation. The
                   array must include values for \b all the variables in the system 
		   (from where the function selects the values for the variables 
		   included in the equation).
  \param lc The linear constraint to evaluate.

  \return The value of the linear constraint.
*/
double EvaluateLinearConstraint(double *varValues,TLinearConstraint *lc);

/** 
  \brief Interval evaluation of a linear constraint.

  Evaluates a linear constaint for a given ranges of the variables using interval
  arithmetics.<br>
  \b NOTE: The right-hand side value of the linear constraint is not used in the evaluation.

  \param varValues Intervals for the variables in the system of equations. This
                   function only uses the ranges for the variables in the equation.
  \param i_out The result of the evalution.
  \param lc The equation.
*/
void EvaluateLinearConstraintInt(Tinterval *varValues,Tinterval *i_out,TLinearConstraint *lc);

/** 
   \brief Prints a linear constraint.

   Writes a linear constraint into a given stream, that can be \e stdout.

   \param f The stream where to write the constraint.
   \param eq TRUE if the linear constraint has to be printed in the form of an equation
             or FALSE to print it as a simple sum of scaled variables.
   \param varName The name of the variables.
	          If this parameter is NULL the printed
	          names for the variables are <em>v_X</em> with \e X the index
	          of the variable.
   \param lc The linear constraint.
*/
void PrintLinearConstraint(FILE *f,boolean eq,char **varName,TLinearConstraint *lc);

/** 
   \brief Saves the linear constraint into a file.

   Saves the linear constraint into a file.
   
   \param f The file where to store the linear constraint.
   \param lc The linear constraint to store.
*/
void SaveLinearConstraint(FILE *f,TLinearConstraint *lc);

/** 
   \brief Constructor. Loads the linear constraint from a file.

   Defines a linear constraint from a file.
   
   \param f The file from where to read the linear constraint.
   \param lc The linear constraint to define.
*/
void LoadLinearConstraint(FILE *f,TLinearConstraint *lc);

/** 
   \brief Destructor.

   Deletes the information stored in a linear constraint and frees the allocated memory.

   \param lc The linear constraint to be deleted.
*/
void DeleteLinearConstraint(TLinearConstraint *lc);

#endif
