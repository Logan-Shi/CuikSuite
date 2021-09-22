#ifndef VARIABLESETH
#define VARIABLESETH 

#include "boolean.h"
#include "interval.h"

#include <stdlib.h>
#include <stdio.h>


/**
   \file variable_set.h

   \brief Definition of the Tvariable_set type and the associated functions. 
   
   Definition of the Tvariable_set type and the associated functions. 

   \sa Tvariable_set, variable_set.c
*/

/************************************************************************************/
/** \brief Initial room for variables.

    Initial room for variables. It will be enlarged if necessary.

    \sa Tvariables
*/
#define INIT_NUM_VARIABLES 10
/************************************************************************************/

/** 
   \brief No trigonometric function for the variable.
   
   Indicates variables that are used without any trigonometric function.
 */
#define NFUN 0

/** 
   \brief Sine of the variable.
   
   Do not use the variable but its sine.
 */
#define SINV 1

/** 
   \brief Cosine of the variable.
   
   Do not use the variable but its cosine.
 */
#define COSV 2

/** 
   \brief Tangent of the variable.
   
   Do not use the variable but its tangent.
 */
#define TANV 3

/** 
   \brief Squared secant of the variable.
   
   Do not use the variable but its squared secant (1/cos)^2.
   This only appears in the derivative of a tangent.
 */
#define SEC2V 4

/** 
   \brief Squared secant per tangent.

   Do not use the variable but its squared secand per tangent.
   This appears in the derivative of a squared secant (SEC2V),
   i.e., the second derivative of a tangent (TANV).
*/
#define SEC2TANV 5

/** 
   \brief Derivative of \ref SEC2TANV

   Derivative of sec(x)^2*tan(x) (i.e., of \ref SEC2TANV).
*/
#define dSEC2TANV 6

/** 
   \brief Exponential of the variable.

   Do not use the variable but its exponential.
*/
#define EXPV 7

/** 
   \brief Squared of the variable, if it is negative.

   This is a conditional function that evaluates to the squared
   of the variable if it is negative and to 0 otherwise.
*/
#define PWPV 8

/** 
   \brief Derivative of PWPV.

   Derivative of \ref PWPV. This is a line for the negative values
   and 0 for the positive.
*/
#define PWLV 9

/** 
   \brief Derivative of PWLV.

   Derivative of \ref PWLV. This is a constant for the negative values
   and 0 for the positive.
*/
#define PWCV 10


/** 
   \brief A set of variable indexes with powers. 

   A set of variable indexes. This is used to implement the set of power variables
   in a monomial or just a colletion of variable indexes (in this case the powers
   are not used).

   The structure also supports funtions applied to each individual variable (typically
   trigonometric functions: sin/cos). This can be combined
   with the powers to yield exponentials of the functions (e.g. sin(x)^n or cos(x)^n).

   Note that this \b is \b not a set of variables with information for each variable
   (see Tvariables) but merely a set of variable indexes.

   This is basically a vector (see \ref Tvector) 
   and is not implemented using the generic
   Tvector just for legacy reasons (\ref Tvariable_set was implemented 
   much before that the generic structure \ref Tvector). Moreover,
   to use a generic vector we need to implement a basic type including
   the variable identifier and the variable power (and the associated
   constructor, destructor, copy operator, etc).

   \sa variable_set.h, variable_set.c, Tmonomial
*/
typedef struct {
  unsigned int nvars;   /**< Number of variables indexes in the set. */
  unsigned int maxvars; /**< Maximum number of the variables in the set. */
  unsigned int *var_id; /**< Variable indexes. */
  unsigned int *power;  /**< Power for each variable. */
  unsigned int *fun;    /**< (Trigonometric) Function for each variable. */
} Tvariable_set;

/** 
   \brief Constructor.

   Creates an empty set of variable indexes.

   \param vs The variable set to create.
*/
void InitVarSet(Tvariable_set *vs);


/** 
   \brief Resets the information stored in a variable set.

   Removes the information stored in a variable set (variable identifiers
   and powers) but not the allocated memory. To re-use a Tvariable_set it is more 
   efficient to reset the variable to re-use instead of deleting it and constructing
   a new set.

   \param vs The variable set to ber eset.
*/
void ResetVarSet(Tvariable_set *vs);

/** 
   \brief Copy constructor.

   Creates a set of variable from the informatin stored in another set.

   \param vs_dst The variable set to create.
   \param vs_orig The variable set from where to copy.
*/
void CopyVarSet(Tvariable_set *vs_dst,Tvariable_set *vs_orig);

/** 
   \brief Reduces the variable indexes above a given index.

   When eliminating a variable from a problem, the indexes of the variables
   with an identifier above the removed varaible need to be decreased by one.
   This function performs this opearation for a single variable set.
   
   The variable that we are removing from the problem need to be removed before
   applying this operation. If the variable set still includes the variable to be
   removed this function triggers and error.

   \param nv The index of the variable we removed from the problem. Variable indexes
             above it need to be shifted.
   \param vs The variable set to update.
*/
void ShiftVarIndexes(unsigned int nv,Tvariable_set *vs);

/** 
  \brief Variable set comparison.

  Compare two given variable sets. Variable sets are compared first
  taking into account the numver of indexes they include, then the
  powers of the variables and, finally, the indexes of the variables.

  \param vs1 The first set to compare.
  \param vs2 The second set to compare.

  \return 1 if \e vs1 is larger than \e vs2, 0 if they are equal and
          2 if \e vs2 is larger than \e vs1.
*/
unsigned int CmpVarSet(Tvariable_set *vs1,Tvariable_set *vs2);

/** 
   \brief Identifies polynomial variable sets.

   Identifies variable sets formed only by products of variables, i.e.
   without functions in the variables.

   \param vs The variable set to query.

   \return TRUE for polynomial variable sets.
*/
boolean PolynomialVarSet(Tvariable_set *vs);

/** 
  \brief Gets the position of a variable index in a set of variable indexes.

  Gets the position of a variable index in a set of variable indexes.

  \param id The index of the variable.
  \param vs The set of variable indexes.

  \return The position of the variable in the set or NO_UINT if the
          index is not included in the set.
*/
unsigned int GetPlaceinSet(unsigned int id,Tvariable_set *vs);

/** 
  \brief Checks if a variable index is included in a set of variable indexes.

  Determines if a variable index is included in a set of variable indexes.

  \param id The index of the variable.
  \param vs The set of variable indexes.

  \return TRUE if \e id is included in \e vs.
*/
boolean VarIncluded(unsigned int id,Tvariable_set *vs);

/** 
  \brief Checks if a variable index is included in a set of variable indexes with
         a given power.

  Determines if a variable index is included in a set of variable indexes with a given
  power and function.

  \param id The index of the variable.
  \param f The function for the variable (possibly \ref NFUN).
  \param p The power of the variable.
  \param vs The set of variables.

  \return TRUE if \e id is included in \e vs with power \e p.
*/
boolean Included(unsigned int id,unsigned int f,
		 unsigned int p,Tvariable_set *vs);

/** 
  \brief Checks if a variable set is empty.

  Checks if a variable set is empty.

  \param vs The set of variables.

  \return TRUE if \e vs is empty.
*/
boolean EmptyVarSet(Tvariable_set *vs);

/** 
  \brief Adds an element to a variable set.

  Adds a variable index with a given power to a variable set.

  \param f Function to apply to the variable (if any).
  \param varid The index of the variable to be added to the set.
  \param p The power for this variable
  \param vs The set of variables to update.
*/
void AddVariable2Set(unsigned int f,unsigned int varid,unsigned int p,Tvariable_set *vs);

/** 
  \brief Product of two variable sets.

  Accumulates two variable sets in one.
  Note that this is different from \ref UnionVarSet since here we keep the sum
  of the exponentionals (not the maximum one).
  
  \param vs1 The first variable set.
  \param vs2 The second variable set.
  \param v_out The resulting set of variables.
*/
void ProductVarSet(Tvariable_set *vs1,Tvariable_set *vs2,Tvariable_set *v_out);

/** 
  \brief Removes an element to a variable set.

  Removes a variable index from a variable set.
  This operates indepedently of the function/power applied to the variable.

  \param varid The index of the variable to be removed to the set.
  \param vs The set of variables to update.
*/
void RemoveVariableFromSet(unsigned int varid,Tvariable_set *vs);

/** 
   \brief Replaces a variable by a constant.

   Replaces a variable by a constant.

   \param varid The identifier of the variable to replace.
   \param ct The constat value.
   \param vs The variable set to update

   \return The constant value resulting from the variable substitution.
*/
double FixVariableInVarSet(unsigned int varid,double ct,Tvariable_set *vs);

/** 
   \brief Replaces a variable by another variable.

   Replaces a variable by a scaled variable.

   Note that variables inside functions can only be replaced with a scale factor
   set to 1.

   \param varid The identifier of the variable to replace.
   \param ct The scale factor.
   \param newID The identifier of the new variable.
   \param vs The variable set to update.
*/
double ReplaceVariableInVarSet(unsigned int varid,
			       double ct,unsigned int newID,Tvariable_set *vs);

/** 
  \brief Gets the order of a variable set.

  Returns the order of a variable set: the sum of the powers of the variables
  in the set.

  \param vs The set of variables to query.

  \return The variable set order.
*/
unsigned int VarSetOrder(Tvariable_set *vs);


/** 
  \brief Gets the number of elements of a variable set.

  Returns the number of elements of a variable set.

  \param vs The set of variables to query.

  \return The number of elements of a variable set.
*/
unsigned int VariableSetSize(Tvariable_set *vs);

/** 
  \brief Gets a variable identifier from a variable set.

  Returns the identifier for the \e n-th  variable in the set.

  If the set has less than \e n elements this functions triggers an error.

  \param n The position for the index to retrive.
  \param vs The set of variables to query.

  \return The index of the variable at position \e n.
*/
unsigned int GetVariableN(unsigned int n,Tvariable_set *vs);

/** 
  \brief Gets the variable identifiers stored in a variable set.

  Returns the variable identifiers stored in a variable set.

  \param vs The set of variables to query.

  \return The a pointer to the array of variable indexes.
*/
unsigned int *GetVariables(Tvariable_set *vs);

/** 
  \brief Gets a variable power from a variable set.

  Returns the power for the \e n-th  variable in the set.

  If the set has less than \e n elements this functions triggers an error.

  \param n The position for the variable whose power we want to retrive.
  \param vs The set of variables to query.

  \return The power of the variable at position \e n.
*/
unsigned int GetVariablePowerN(unsigned int n,Tvariable_set *vs);

/** 
  \brief Gets a variable function from a variable set.

  Returns the function applied to the \e n-th  variable in the set.

  If the set has less than \e n elements this functions triggers an error.

  \param n The position for the variable whose function we want to retrive.
  \param vs The set of variables to query.

  \return The function of the variable at position \e n (\ref NFUN if
          no function is actually applied to the variable).
*/
unsigned int GetVariableFunctionN(unsigned int n,Tvariable_set *vs);

/** 
  \brief Gets the variable powers stored in a variable set.

  Returns the variable powers stored in a variable set.

  \param vs The set of variables to query.

  \return The a pointer to the array of variable powers.
*/
unsigned int *GetPowers(Tvariable_set *vs);

/** 
  \brief Checks if two variable sets have elements in common.

  Determines if two variable sets have any element in common.
  To determine if two variable set elements are the same we
  take into account bot the variable index, its power, and its
  associated function (if any).

  \param vs1 The first set of variables to intersect.
  \param vs2 The second set of variables to intersect.

  \return TRUE if the intersection between the sets is non-empty.
*/
boolean VarSetIntersect(Tvariable_set *vs1,Tvariable_set *vs2);

/** 
  \brief Produces a variable set that is the union of two variable sets.

  Produces a variable set that is the union of two variable sets: i.e., it includes
  the variables in both sets.
  
  \param fun TRUE if the same variable with different functions has to be considered
                  differnt instances. FALSE if the variable indentifier is the
		  only criterion used.
  \param vs_new The variable set to add to 'vs'
  \param vs The set of variables to modify.
*/
void UnionVarSet(boolean fun,Tvariable_set *vs_new,Tvariable_set *vs);


/** 
  \brief Evaluates a variable set for a given set of value for the variables.
  
  Evaluates a variable set for a given set of value for the variables.

  \param varValues An array of doubles with the values for the variables in the problem.
  \param vs The variable set to evaluate.

  \return The value of the variable set.
*/
double EvaluateVarSet(double *varValues,Tvariable_set *vs);

/** 
  \brief Evaluates a variable set for a given set of ranges for the variables.
  
  Evaluates a variable set for a given set of ranges for the variables using interval
  arithmetics.

  \param varValues An array with the ranges for the variables in the problem.
  \param i_out The output interval.
  \param vs The variable set to evaluate.
*/
void EvaluateVarSetInt(Tinterval *varValues,Tinterval *i_out,Tvariable_set *vs);

/** 
  \brief Derives an variable set.

  Derives a variable set with respect to a given variable.

  \param nv Identifier of the variable with respect to the one we have to derive.
  \param dvs Output variable set with the derived variable set.
  \param vs The variable set to derive.

  \return The constant term sub-product of the derivation, if any.
*/
double DeriveVarSet(unsigned int nv,Tvariable_set *dvs,Tvariable_set *vs);


/** 
  \brief Prints a variable set.

  Writes a variable set to a given stream.

  \param f The stream where to print the variable set.
  \param varNames The name of the variables.
	          If this parameter is NULL the printed
	          names for the variables are <em>v_X</em> with \e X the index
	          of the variable.
  \param vs The variable set to print.
*/
void PrintVarSet(FILE *f,char **varNames,Tvariable_set *vs);

/** 
  \brief Destructor.

  Deletes the information stored in the variable set and frees the allocated memory space.
  
  \param vs The variable set to be deleted.
*/
void DeleteVarSet(Tvariable_set *vs);

#endif
